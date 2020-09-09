.. _lib_azure_iot_hub:

Azure IoT Hub
#############

The Azure IoT Hub library provides an API to connect to an `Azure IoT Hub`_ instance and interact with it.
It connects to the IoT Hub using MQTT over TLS.

The library supports `Azure IoT Hub Device Provisioning Service (DPS)`_.
DPS can be enabled at compile-time to make use of the device provisioning services for onboarding of devices to an Azure IoT Hub.
When the device provisioning is complete, the library automatically connects to the assigned IoT Hub.

The library also has integrated support for Azure FOTA.
For more information on Azure FOTA, see the documentation on :ref:`lib_azure_fota` library and :ref:`azure_fota_sample` sample.

.. _connect_to_azure_iot_hub:

Prerequisites for connecting to Azure IoT Hub
*********************************************

In order to connect to Azure IoT Hub, an Azure IoT Hub account and an IoT Hub must first be created and configured.
See `Creating an IoT Hub using the Azure portal`_ for more information.

The connection to an Azure IoT Hub using MQTT is secured using TLS.
The Azure IoT Hub library requires the provisioning of the following certificates and key for a successful TLS connection:

1. `Baltimore CyberTrust Root certificate`_
#. Device certificate
#. Private key of the device

For testing purposes, see `Creating Azure IoT Hub certificates`_ for the steps to create certificates and private key, and to the register the generated test root certificate to be used with an IoT hub.

.. _azure_iot_hub_flash_certs:

Provisioning of the certificates
=============================

To provision the certificates to the nRF9160 modem, complete the following steps:

1. `Download nRF Connect for Desktop`_.
#. Update the modem firmware on the on-board modem of the nRF9160-based device to the latest version by following the steps in `Updating the nRF9160 DK cellular modem`_.
#. Build and program the :ref:`at_client_sample` sample to the nRF9160-based device as explained in :ref:`gs_programming`.
#. Launch the `LTE Link Monitor`_ application, which is part of `nRF Connect for Desktop`_.
#. Click :guilabel:`Certificate manager` located at the top right corner.
#. Copy the Baltimore CyberTrust Root certificate into the ``CA certificate`` entry.
#. Copy and paste the device certificate and the key created using the scripts located in `Creating Azure IoT Hub certificates`_, into the respective entries (``Client certificate``, ``Private key``).
#. Select a desired security tag (Any positive integer. For example, ``42``.) and click :guilabel:`Update certificates`.

.. note::
   The chosen security tag while provisioning the certificates must be same as the security tag configured by the :option:`CONFIG_AZURE_IOT_HUB_SEC_TAG` option.


Configuring the library options
===============================

To connect to Azure IoT Hub without using DPS, complete the following minimum required configuration:

1. In the `Azure Portal`_, navigate to :guilabel:`IoT Hub` and select the desired IoT Hub.
#. In the overview page, locate and copy the ``Hostname`` and configure :option:`CONFIG_AZURE_IOT_HUB_HOSTNAME` to this address.
#. Set the option :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID` to the device ID. The device ID must match the device ID used while creating the certificates.
#. Set :option:`CONFIG_AZURE_IOT_HUB_SEC_TAG` to the security tag used while :ref:`azure_iot_hub_flash_certs`.


.. _dps_config:

Configuring Device Provisioning Service (DPS)
=============================================

To connect to an Azure IoT Hub using DPS, complete the following steps:

1. `Set up an Azure IoT Hub Device Provisioning Service (DPS) instance`_ and obtain the ID scope.
#. Enable :option:`CONFIG_AZURE_IOT_HUB_DPS`.
#. In the `Azure Portal`_, click :guilabel:`Device Provisioning Services` and select the DPS instance to use.
#. In the overview page, locate and copy the ``ID Scope`` and configure :option:`CONFIG_AZURE_IOT_HUB_DPS_ID_SCOPE` to this string.
#. Set the :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID` option to device ID, unless :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID_APP` is enabled. The device ID must match the device ID used while creating the certificates.
#. Set :option:`CONFIG_AZURE_IOT_HUB_SEC_TAG` to the security tag used while :ref:`azure_iot_hub_flash_certs`.


Initializing the library
************************

The library is initialized by calling the :cpp:func:`azure_iot_hub_init` function.
If the initialization fails, the application cannot use any APIs of the library.
Optionally, you can include a pointer to a :cpp:type:`azure_iot_hub_config` structure in the :cpp:func:`azure_iot_hub_init` function call.
If :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID_APP` is enabled, the :cpp:func:`azure_iot_hub_init` function call must include a pointer to a :cpp:type:`azure_iot_hub_config` structure containing the device ID.
Otherwise, it can be ``NULL``.

Below is an example for setting the device ID at run-time instead of compile-time by configuring the :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID` option:

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

Connecting to Azure IoT Hub
***************************

After the initialization, a :cpp:func:`azure_iot_hub_connect` function call connects the device to the configured IoT Hub or DPS instance, depending on the configuration.
The initial TLS handshake takes some time to complete, typically in the range of few seconds, depending on the network conditions and the TLS cipher suite used.
For the duration of the TLS handshake, :cpp:func:`azure_iot_hub_connect` blocks, so care must be taken when deciding the context from which the API is called.

After a successful connection, the library automatically subscribes to the following standard Azure IoT Hub MQTT topics (See `Azure IoT Hub MQTT protocol support`_ for details):

* ``devices/<device ID>/messages/devicebound/#`` (cloud-to-device messages)
* ``$iothub/twin/PATCH/properties/desired/#`` (desired properties update notifications)
* ``$iothub/twin/res/#`` (operation responses)
* ``$iothub/methods/POST/#`` (direct method requests)

Currently, the library does not support persistent MQTT sessions.
Hence subscriptions are requested for each connection to the IoT Hub.


API documentation
*****************

| Header file: :file:`include/net/azure_iot_hub.h`
| Source files: :file:`subsys/net/lib/azur_iot_hub/src/`

.. doxygengroup:: azure_iot_hub
   :project: nrf
   :members:
