.. _azure_fota_sample:

nRF9160: Azure FOTA
#################

The Azure Firmware Over The Air (Azure FOTA) sample shows how to perform an over-the-air firmware update of an nRF9160 device using the Azure IoT Hub and Azure FOTA libraries of the nRF Connect SDK.


Overview
*********

The sample connects to the configured `Azure IoT Hub`_ and waits for incoming device twin updates containing firmware update information.
By default, the device twin document is requested upon connecting to the IoT Hub, so any existing firmware information in the ``desired`` property will be parsed.
See :ref:`lib_azure_fota` for more details on the content of the firmware information in the device twin.

.. note::
   A file server instance that hosts the new firmware image is required for this sample.
   The Azure FOTA library does not require a specific host, but has been tested using `Azure Blob Storage`_ that shares the same root certificate as the Azure IoT Hub.

Requirements
************

The sample supports the following development kit:

.. include:: /includes/boardname_tables/sample_boardnames.txt
   :start-after: set6_start
   :end-before: set6_end

The sample requires an Azure IoT Hub, and optionally an Azure IoT Hub Device Provisioning Service instance if the device is not already registered with the IoT hub.

.. _certificates:

Certificates for using TLS
==========================

If TLS is used as the transport layer, certificates have to be provisioned to the device.
Which certificates that need to be provisioned depends on where the FOTA image is hosted, and which TLS settings are configured at the endpoint where the file is downloaded from.
If, for instance, `Azure Blob Storage` is used for hosting, the same root certificate (`Baltimore CyberTrust Root certificate`_) as for `Azure IoT Hub`_ connection can be used.
See `connect_to_azure_iot_hub`_ for more details on how Azure IoT Hub certificates are provisioned.

If another host than Azure is used, it's likely that it has other certificate requirements.
Consult the host's documentation to find the right certificates.
The certificates can be provisioned using the same procedure as for Azure ioT Hub certificates, described here: `azure_iot_hub_flash_certs`_

.. include:: /includes/spm.txt


Building and running
********************

.. |sample path| replace:: :file:`samples/nrf9160/azure_fota`

.. include:: /includes/build_and_run_nrf9160.txt

.. _configuring:

Sample configuration
====================

Before you build the sample, check and update the following configuration options:

.. option:: AZURE_FOTA_APP_VERSION - Application version

   The version string is printed when the sample starts.
   Use this information to verify that the FOTA update worked.

.. option:: AZURE_FOTA_TLS - Use HTTPS for downloads.

   By default TLS is enabled for downloads.
   Currently, the transport protocol must be configured at compile-time.

.. option:: AZURE_FOTA_SEC_TAG - Security tag for TLS credentials

   If HTTPS is used as the transport layer, certificates must be provisioned to the device and the sec tag option must be set accordingly.
   A sec tag is a positive integer that serves as pointer to where in the device's certificate storage the relevant certificates are stored.
   See `_certificates`_ for more details.

.. option:: AZURE_IOT_HUB_HOSTNAME - Azure IoT Hub hostname.

   By default DPS is not used, and the Azure IoT Hub hostname must therefore be set using Kconfig.

.. option:: AZURE_IOT_HUB_DEVICE_ID - Device ID.

   The Azure IoT Hub device ID must be set unless :option:`AZURE_IOT_HUB_DEVICE_ID_APP` is enabled and the ID is provided at runtime in the configuration struct.


Testing
=======

After programming the sample to the board, test it by performing the following steps:

1. |connect_terminal|
#. Reset the board.
#. Confirm that the sample prints the configured application version and connects to the Azure IoT Hub.
   You should see output like the following::

      *** Booting Zephyr OS build v2.3.0-rc1-ncs1-1453-gf41496cd30d5  ***
      Traces enabled
      Azure FOTA sample started, v2.0
      Initializing BSDlib
      This may take a while if a modem firmware update is pending
      BSDlib initialized
      Connecting to LTE network
      AZURE_IOT_HUB_EVT_CONNECTING
      AZURE_IOT_HUB_EVT_CONNECTED
      AZURE_IOT_HUB_EVT_READY


#. Log on to the `Azure Portal`_, go to **IoT Hub** and select your IoT Hub.
#. Navigate to **IoT devies** and select the device to update.
#. In the device view, click the **Device Twin** button.
#. Create a `firmware` JSON object inside the `desired` object of the device twin document, containing information about the binary to download:

   .. parsed-literal::
      :class: highlight

	{
	    "firmware": {
	        "fwVersion": "v0.0.0-dev",
	        "fwLocation": {
	            "host": "my-storage-account.blob.core.windows.net",
	            "path": "my-app-update.bin"
	        },
	        "fwFragmentSize" : 1800
	    }
	}

   See :ref:`lib_azure_fota` for more details.
#. Apply the changes to the device twin by clicking **Save**.
#. Updating the device twin will cause a message to be sent to the device, containing the updates to the `desired` object.
#. In the terminal emulator, observe that the new firmware image is downloaded and installed.
   You should see output similar to the following::

      ...
      [00:00:20.089,416] <inf> download_client: Downloaded 19800/300860 bytes (6%)
      [00:00:20.338,653] <inf> download_client: Downloaded 21600/300860 bytes (7%)
      [00:00:20.359,924] <inf> STREAM_FLASH: Erasing page at offset 0x0008c000
      [00:00:20.729,644] <inf> download_client: Downloaded 23400/300860 bytes (7%)
      [00:00:20.979,675] <inf> download_client: Downloaded 25200/300860 bytes (8%)
      [00:00:21.007,385] <inf> STREAM_FLASH: Erasing page at offset 0x0008d000
      ...
      [00:01:22.750,946] <inf> download_client: Download complete
      [00:01:22.761,657] <inf> STREAM_FLASH: Erasing page at offset 0x000fd000
      [00:01:22.857,238] <inf> dfu_target_mcuboot: MCUBoot image upgrade scheduled. Reset the device to apply
      [2020-08-28 00:38:18] [00:01:15.665,679] <inf> azure_fota: FOTA download completed evt received
      [2020-08-28 00:38:18] AZURE_IOT_HUB_EVT_FOTA_DONE
      [2020-08-28 00:38:18] The device will reboot in 5 seconds to apply update

#. When the board reboots, observe that the sample prints logs from the new application.
#. In Azure Portal, confirm that the device twin now contains the updated application version in the `reported.firmware.fwVersion` field.


Dependencies
************

This sample uses the following libraries:

From |NCS|
  * :ref:`lib_azure_fota`
  * :ref:`lib_azure_iot_hub`
  * ``drivers/lte_link_control``

From nrfxlib
  * :ref:`nrfxlib:bsdlib`

From Zephyr
  * :ref:`MQTT <zephyr:networking_api>`

In addition it uses the following samples:

From |NCS|
  * :ref:`secure_partition_manager`
