/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/sys/util.h>
#include <zephyr/logging/log.h>
#include <mbedtls/platform_util.h>
LOG_MODULE_REGISTER(internal_secure_aead, CONFIG_SECURE_STORAGE_LOG_LEVEL);

#include <string.h>

#include "../secure_storage_backend.h"
#include "../storage_backend.h"
#include "aead_key.h"
#include "aead_nonce.h"
#include "aead_crypt.h"

/*
 * AEAD based Authenticated Encrypted trust implementation
 *
 * Actual implementation uses:
 * - Hexadecimal UID imported as KEY
 * - Flags+Size as additional parameter
 * - Nonce is a number that is incremented for each encryption.
 * - Tag is left at the end of output data
 */

#define AEAD_NONCE_SIZE 12
#define AEAD_TAG_SIZE	16

#define STORAGE_MAX_ASSET_SIZE CONFIG_SECURE_STORAGE_BACKEND_AEAD_MAX_DATA_SIZE
#define AEAD_MAX_BUF_SIZE      ROUND_UP(STORAGE_MAX_ASSET_SIZE + AEAD_TAG_SIZE, AEAD_TAG_SIZE)

/** Header of stored object. Supplied as additional data when encrypting. */
typedef struct stored_object_header {
	psa_storage_create_flags_t create_flags;
	size_t data_size;
} stored_object_header;

typedef struct stored_object {
	stored_object_header header;
	uint8_t nonce[AEAD_NONCE_SIZE];
	uint8_t data[AEAD_MAX_BUF_SIZE];
} stored_object;

psa_status_t secure_get_info(const psa_storage_uid_t uid, const char *prefix,
			     struct psa_storage_info_t *p_info)
{
	psa_status_t status;
	size_t out_length;
	stored_object_header header;

	if (p_info == NULL) {
		return PSA_ERROR_INVALID_ARGUMENT;
	}

	/* Get size & flags */
	status = storage_get_object(uid, prefix, (void *)&header, sizeof(header), &out_length);
	if (status != PSA_SUCCESS) {
		return status;
	}

	p_info->capacity = header.data_size;
	p_info->size = header.data_size;
	p_info->flags = header.create_flags;

	return PSA_SUCCESS;
}

psa_status_t secure_get(const psa_storage_uid_t uid, const char *prefix, size_t data_offset,
			size_t data_length, void *p_data, size_t *p_data_length)
{
	psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
	uint8_t key_buf[AEAD_KEY_SIZE + 1];
	size_t out_length;
	stored_object object_data;

	if (data_length == 0 || p_data == NULL || p_data_length == NULL) {
		return PSA_ERROR_INVALID_ARGUMENT;
	}

	if ((data_offset + data_length) > STORAGE_MAX_ASSET_SIZE) {
		return PSA_ERROR_NOT_SUPPORTED;
	}

	/* Get AEAD key */
	status = secure_storage_get_key(uid, key_buf, AEAD_KEY_SIZE);
	if (status != PSA_SUCCESS) {
		return status;
	}

	/* Retrieve object from storage */
	status = storage_get_object(uid, prefix, (void *)&object_data, sizeof(object_data),
				    &out_length);
	if (status != PSA_SUCCESS) {
		return status;
	}

	status = secure_storage_aead_decrypt(key_buf, AEAD_KEY_SIZE, object_data.nonce,
					     AEAD_NONCE_SIZE, (void *)&object_data.header,
					     sizeof(object_data.header), object_data.data,
					     out_length - offsetof(stored_object, data),
					     object_data.data, STORAGE_MAX_ASSET_SIZE, &out_length);

	if (status != PSA_SUCCESS) {
		goto clean_up;
	}

	if ((data_offset + data_length) > out_length) {
		status = PSA_ERROR_INVALID_ARGUMENT;
	} else {
		memcpy(p_data, object_data.data + data_offset, data_length);
		*p_data_length = data_length;
	}

clean_up:
	/* Clean up */
	mbedtls_platform_zeroize(key_buf, sizeof(key_buf));
	mbedtls_platform_zeroize(&object_data, sizeof(object_data));

	return status;
}

psa_status_t secure_set(const psa_storage_uid_t uid, const char *prefix, size_t data_length,
			const void *p_data, psa_storage_create_flags_t create_flags)
{
	psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
	uint8_t key_buf[AEAD_KEY_SIZE + 1];
	size_t out_length = 0;
	stored_object object_data;

	if (data_length == 0 || p_data == NULL) {
		return PSA_ERROR_INVALID_ARGUMENT;
	}

	if (create_flags != PSA_STORAGE_FLAG_NONE && create_flags != PSA_STORAGE_FLAG_WRITE_ONCE) {
		return PSA_ERROR_NOT_SUPPORTED;
	}

	if (data_length > STORAGE_MAX_ASSET_SIZE) {
		return PSA_ERROR_NOT_SUPPORTED;
	}

	/* Get flags */
	status = storage_get_object(uid, prefix, (void *)&object_data.header,
				    sizeof(object_data.header), &out_length);

	if (status != PSA_SUCCESS && status != PSA_ERROR_DOES_NOT_EXIST) {
		return status;
	}

	/* Do not allow to write new values if WRITE_ONCE flag is set */
	if (status == PSA_SUCCESS &&
	    (object_data.header.create_flags & PSA_STORAGE_FLAG_WRITE_ONCE) != 0) {
		return PSA_ERROR_NOT_PERMITTED;
	}

	/* Get AEAD key */
	status = secure_storage_get_key(uid, key_buf, AEAD_KEY_SIZE);
	if (status != PSA_SUCCESS) {
		goto cleanup_objects;
	}

	/* Get new nonce at each set */
	status = secure_storage_get_nonce(object_data.nonce, AEAD_NONCE_SIZE);
	if (status != PSA_SUCCESS) {
		goto cleanup_objects;
	}

	object_data.header.create_flags = create_flags;
	object_data.header.data_size = data_length;

	status = secure_storage_aead_encrypt(key_buf, AEAD_KEY_SIZE, object_data.nonce,
					     AEAD_NONCE_SIZE, (void *)&object_data.header,
					     sizeof(object_data.header), p_data, data_length,
					     object_data.data, AEAD_MAX_BUF_SIZE, &out_length);

	mbedtls_platform_zeroize(key_buf, sizeof(key_buf));

	if (status != PSA_SUCCESS) {
		goto cleanup;
	}

	/* Write data */
	status = storage_set_object(uid, prefix, &object_data,
				    offsetof(stored_object, data) + out_length);
	if (status != PSA_SUCCESS) {
		goto cleanup_objects;
	}

	goto cleanup;

cleanup_objects:
	/* Remove object if an error occurs */
	LOG_DBG("secure_set cleanup. status %d", status);
	storage_remove_object(uid, prefix);

cleanup:
	mbedtls_platform_zeroize(&object_data, sizeof(object_data));

	return status;
}

psa_status_t secure_remove(const psa_storage_uid_t uid, const char *prefix)
{
	psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
	size_t out_length;
	stored_object_header header;

	/* Get flags */
	status = storage_get_object(uid, prefix, (void *)&header, sizeof(header), &out_length);
	if (status != PSA_SUCCESS) {
		return status;
	}

	if (status == PSA_SUCCESS && (header.create_flags & PSA_STORAGE_FLAG_WRITE_ONCE) != 0) {
		return PSA_ERROR_NOT_PERMITTED;
	}

	return storage_remove_object(uid, prefix);
}

uint32_t secure_get_support(void)
{
	return 0;
}

psa_status_t secure_create(const psa_storage_uid_t uid, size_t capacity,
			   psa_storage_create_flags_t create_flags)
{

	ARG_UNUSED(uid);
	ARG_UNUSED(capacity);
	ARG_UNUSED(create_flags);
	return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t secure_set_extended(const psa_storage_uid_t uid, size_t data_offset,
				 size_t data_length, const void *p_data)
{
	ARG_UNUSED(uid);
	ARG_UNUSED(data_offset);
	ARG_UNUSED(data_length);
	ARG_UNUSED(p_data);
	return PSA_ERROR_NOT_SUPPORTED;
}
