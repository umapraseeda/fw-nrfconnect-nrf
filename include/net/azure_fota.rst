.. _lib_azure_fota:

Azure FOTA
##########

The Azure Firmware Over The Air (Azure FOTA) library provides a way to parse Azure IoT Hub device twin messages for firmware upgrade information and perform FOTA downloads.
The JSON format and content that's used in this library, are based on the recommendations found here: `Azure Firmware Over The Air (FOTA)`_.

The library works by processing the incoming JSON string and looking for a specific object containing firmware update information in the device twin.
The expected format of a ``firmware`` object is the following:

.. parsed-literal::
   :class: highlight

   {
   	"firmware": {
		"fwVersion": "v1.0.3",
		"fwLocation": {
       			"protocol": "https:",
			"host": "<hostname>",
			"path": "<filename>.bin"
		},
		"fwFragmentSize" : 1800
	}
   }

``fwVersion`` is used by the library to determine whether the the firmware should be downloaded or not.
Currently, the only requirement to download and apply the firmware is that the version is not equal to the running firmware.

In the current application, the ``protocol`` field is not used. Instead the :option:`CONFIG_AZURE_FOTA_TLS` is used at compile-time to decide which transport protocol to use.

The ``fwFragmentSize`` field describes how large fragment of the file should be downloaded in each HTTP request.
If TLS is used the maximum total fragment size which also includes the HTTP header is about 2 KB. Without TLS it is about 4 KB.
``fwFragmentSize`` should therefore be set lower than the maximum buffer size to also keep space for the HTTP header.

It is up to the application that uses the library to restart the device when the FOTA is complete and an :cpp:enumerator:`AZURE_FOTA_EVT_DONE` event is received.

The Azure FOTA library is used in the :ref:`azure_fota_sample` sample.

.. note::
   The current implementation is experimental and may change and improve
in future releases.

Configuration
*************

Configure the following parameters when using this library:

* :option:`CONFIG_AZURE_FOTA_APP_VERSION` or :option:`CONFIG_AZURE_FOTA_APP_VERSION_AUTO` to set the application version
* :option:`CONFIG_AZURE_FOTA_TLS`
* :option:`CONFIG_AZURE_FOTA_PAYLOAD_SIZE`
* :option:`CONFIG_AZURE_FOTA_HOSTNAME_MAX_LEN`
* :option:`CONFIG_AZURE_FOTA_FILE_PATH_MAX_LEN`


Limitations
***********

* The library requires a Content-Range header to be present in the HTTP response from the server.
  This limitation is inherited from the :ref:`lib_download_client` library.

API documentation
*****************

| Header file: :file:`include/net/azure_fota.h`
| Source files: :file:`subsys/net/lib/azure_fota/`

.. doxygengroup:: azure_fota
   :project: nrf
   :members:
