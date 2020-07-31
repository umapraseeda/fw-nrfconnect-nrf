.. _lib_azure_iot_hub:

Azure IoT Hub
#############

The Azure IoT Hub library provides an API to connect to an `Azure IoT Hub`_ instance and interact with it.
It connects to the IoT Hub using MQTT over TLS.

The library has support for `Azure IoT Hub Device Provisioning Service (DPS)`_.
DPS can be enabled at compile-time to make use of the device provisioning services for onboarding devices to an Azure IoT Hub.
When the device provisioning is done, the library will automatically connect to the assigned IoT Hub.

The library also has integrated support for Azure FOTA. For more information on Azure FOTA, see the documentation on :ref:`lib_azure_fota` library and :ref:`azure_fota_sample` sample.

.. _connect_to_azure_iot_hub:

Preparations to connect to Azure IoT Hub
****************************************

In order to connect to `Azure IoT Hub`_, an account and IoT Hub must first be created and configured.
This can be achieved by following the instructions at `Create an IoT Hub using the Azure portal`_.

The connection to an Azure IoT Hub using MQTT is secured using TLS.
The Azure IoT Hub library expects the following certificates and key to be provisioned for the TLS connection to be successfully established:

1. `Baltimore CyberTrust Root certificate`_
#. Device certificate
#. Device's private key

For testing purposes, certificates and private key can be created using the instructions found here: `Create Azure IoT Hub certificates`_.
The linked page also contains instructions on how to register the generated test root certificate to be used with an IoT hub.

.. _azure_iot_hub_flash_certs:

Provision the certificates to the nRF9160 modem
===============================================

1. `Download nRF Connect for Desktop`_
#. Update the modem firmware on the on-board modem of the nRF9160 based board to the latest version by following the steps in `Updating the nRF9160 DK cellular modem`_.
#. Build and program the  :ref:`at_client_sample` sample to the nRF9160 based board as explained in :ref:`gs_programming`.
#. Launch the `LTE Link Monitor`_ application, which is part of `nRF Connect for Desktop`_.
#. Click **Certificate manager** located at the top right corner.
#. Copy the Baltimore CyberTrust Root certificate into the ``CA certificate`` entry.
#. Copy and paste the device certificate and key created using the scripts found at `Create Azure IoT Hub certificates`_, into the respective entries (``Client certificate``, ``Private key``).
#. Select a desired security tag (can be any positive integer, e.g. ``42``) and click **Update certificates**.

.. note::
   The chosen security tag when provisioning the certificates must be equal to the security tag configured by :option:`CONFIG_AZURE_IOT_HUB_SEC_TAG`.


Configuring library options
===========================

The following steps are the minimal required configuration to be able to connect to Azure IoT Hub without using DPS:

1. In the `Azure Portal`_, navigate to **IoT Hub** and select the desired IoT Hub.
#. On the overwiew page, locate and copy the ``Hostname`` and configure :option:`CONFIG_AZURE_IOT_HUB_HOSTNAME` to this address.
#. Set the option :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID` to device ID. The device ID must match the device ID used when creating certificates.
#. Set :option:`CONFIG_AZURE_IOT_HUB_SEC_TAG` to the security tag where certificates were provisioned in the steps under :ref:`_azure_iot_hub_flash_certs`.


.. _dps_config:

Configure Device Provisioning Service (DPS)
===========================================
The following steps are required to connect to an Azure IoT Hub using DPS:

1. Follow the instruction to set up a DPS instance and obtain the ID scope required in a later step: `Azure IoT Hub Device Provisioning Service (DPS) setup`_.
#. Enable :option:`CONFIG_AZURE_IOT_DPS`.
#. In the `Azure Portal`_, navigate to **Device Provisioning Services
** and select the DPS instance to use.
#. On the overwiew page, locate and copy the ``ID Scope`` and configure :option:`CONFIG_AZURE_IOT_DPS_ID_SCOPE` to this string.
#. Set the option :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID` to device ID, unless :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID_APP` is enabled. The device ID must match the device ID used when creating certificates.
#. Set :option:`CONFIG_AZURE_IOT_HUB_SEC_TAG` to the security tag where certificates were provisioned in the steps under :ref:`_azure_iot_hub_flash_certs`.


Initializing
************

The library is initialized by calling the :cpp:func:`azure_iot_hub_init` function.
If the initialization fails, the application can not use any APIs of the library.
In the call to :cpp:func:`azure_iot_hub_init`, it's optional to include a pointer to a :cpp:type:`azure_iot_hub_config` structure.
If :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID_APP` is enabled, the call to :cpp:func:`azure_iot_hub_init` must include a pointer to a :cpp:type:`azure_iot_hub_config` structure containing the device ID.
Otherwise, it can be ``NULL``.

Below is an example of how the device ID can be set at run-time instead of the compile-time by configuring :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID`.

   .. code-block:: c
	struct azure_iot_hub_config cfg = {
	   .device_id = "my-device",
	   .device_id_len = sizeof("my-device") - 1,
	};

         err = azure_iot_hub_init(&cfg, event_handler);
         if (err) {
            printk("azure_iot_hub_init failed: %d\n", err);
	    return err;
         }

Connecting
**********

After initialization, calling :cpp:func:`azure_iot_hub_connect` will connect the device to the configured IoT Hub or DPS instance, depending on the configuration.
The initial TLS handshake takes some time to complete, usually in the range of seconds up to the low tens of seconds, depending on the network conditions.
For the duration of the TLS handshake, :cpp:func:`azure_iot_hub_connect` blocks, so care must be taken when deciding from which context the API is called.

After a successful connection, the library automatically subscribes to the following standard Azure IoT Hub MQTT topics (see `Azure IoT Hub MQTT protocol support`_ for details):
- ``devices/<device ID>/messages/devicebound/#`` (cloud-to-device messages)
- ``$iothub/twin/PATCH/properties/desired/#`` (desired properties update notifications)
- ``$iothub/twin/res/#`` (operation responses)
- ``$iothub/methods/POST/#`` (direct method requests)

Currently, the library does not persistent MQTT sessions, so subscriptions are requested on each connection to the IoT Hub.


API documentation
*****************

| Header file: :file:`include/net/azure_iot_hub.h`
| Source files: :file:`subsys/net/lib/azur_iot_hub/src/`

.. doxygengroup:: azure_iot_hub
   :project: nrf
   :members:
