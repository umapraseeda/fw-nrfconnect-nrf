.. _azure_fota_sample:

nRF9160: Azure FOTA
###################

The Azure firmware over-the-air (Azure FOTA) sample demonstrates how to perform an over-the-air firmware update of an nRF9160 device using the :ref:`lib_azure_fota` and :ref:`lib_azure_iot_hub` libraries of |NCS|.

Requirements
************

The sample supports the following development kits:

.. include:: /includes/boardname_tables/sample_boardnames.txt
   :start-after: set6_start
   :end-before: set6_end

The sample also requires an Azure IoT Hub, and optionally an Azure IoT Hub Device Provisioning Service instance, if the device is not already registered with the IoT hub.

.. include:: /includes/spm.txt

Overview
********

The sample connects to the configured `Azure IoT Hub`_ and waits for incoming `Azure IOT hub device twin messages`_ that contain the firmware update information.
By default, the device twin document is requested upon connecting to the IoT Hub.
Thus, any existing firmware information in the *desired* property will be parsed.
See :ref:`lib_azure_fota` for more details on the content of the firmware information in the device twin.

.. note::
   This sample requires a file server instance that hosts the new firmware image.
   The :ref:`lib_azure_fota` library does not require a specific host, but it has been tested using `Azure Blob Storage`_ that shares the same root certificate as the Azure IoT Hub.

.. _certificates:

Certificates for using TLS
==========================

If TLS is used as the transport layer, the required certificates must be provisioned to the device.
The certificates that need to be provisioned depends on the location of the hosted FOTA image, and the TLS settings that are configured at the endpoint from where the file is downloaded.
If, for instance, Azure Blob Storage is used for hosting, the same root certificate (`Baltimore CyberTrust Root certificate`_) used in the `Azure IoT Hub`_ connection can be used.
See :ref:`connect_to_azure_iot_hub` for more information.

If a host other than Azure is used, the certificate requirements might be different.
See the documentation for the respective host to locate the correct certificates.
The certificates can be provisioned using the same procedure as described in :ref:`azure_iot_hub_flash_certs`.

Configuration
*************
|config|

.. _configuring_azure_fota_sample:

Configuration options
=====================

Check and configure the following configuration options for the sample:

.. option:: CONFIG_AZURE_FOTA_APP_VERSION - Application version

This configuration option is used to define the application version string.
The application version is reported to the device twin as the currently running firmware on the board.
Is is also when a *firmware* object is received in the device twin, to decide if the firmware image should be downloaded or not.
In the current version of `lib_azure_fota`_, a firmware update will be downloaded if it has a different version string than the running firmware.

.. option:: CONFIG_AZURE_FOTA_APP_VERSION_AUTO - Automatic generation of application version

This configuration option is used to enable automatic generation of the application version string.
The git command *git describe* is used to generate the string.
If the configuration is enabled, :option:`CONFIG_AZURE_FOTA_APP_VERSION` will be ignored.
By default this option is disabled.

.. option:: CONFIG_AZURE_FOTA_TLS - Use HTTPS for downloads

This configuration option is used to enable HTTPS for downloads.
By default, TLS is enabled and currently, the transport protocol must be configured at compile-time.

.. option:: CONFIG_AZURE_FOTA_SEC_TAG - Security tag for TLS credentials

This configuration option sets the security tag for TLS credentials.
If HTTPS is used as the transport layer, certificates must be provisioned to the device and the security tag option must be set accordingly.
A security tag is a positive integer that serves as pointer to the location of the relevant certificates in the certificate storage the certificate storage of the device.
See :ref:`certificates` for more details.

.. option:: CONFIG_AZURE_IOT_HUB_HOSTNAME - Azure IoT Hub host name

This configuration option sets the Azure IoT Hub hostname.
By default, DPS is not used, and therefore the Azure IoT Hub hostname must be set using Kconfig.

.. option:: CONFIG_AZURE_IOT_HUB_DEVICE_ID - Device ID

This configuration option sets the device ID.
The Azure IoT Hub device ID must be set unless :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID_APP` is enabled, and the ID is provided at runtime in the configuration struct.

Building and running
********************

.. |sample path| replace:: :file:`samples/nrf9160/azure_fota`

.. include:: /includes/build_and_run_nrf9160.txt



Testing
=======

After programming the sample to your development kit, test it by performing the following steps:

#. |connect_kit|
#. |connect_terminal|
#. Reset the development kit.
#. Observe that the sample displays the configured application version in the terminal and connects to the Azure IoT Hub as shown below::

      *** Booting Zephyr OS build v2.3.0-rc1-ncs1-1453-gf41496cd30d5  ***
      Traces enabled
      Azure FOTA sample started
      Initializing BSDlib
      This may take a while if a modem firmware update is pending
      BSDlib initialized
      Connecting to LTE network
      AZURE_IOT_HUB_EVT_CONNECTING
      AZURE_IOT_HUB_EVT_CONNECTED
      AZURE_IOT_HUB_EVT_READY


#. Log on to the `Azure Portal`_, navigate to :guilabel:`IoT Hub` and select your IoT Hub.
#. Navigate to :guilabel:`IoT devices` and select the device to update.
#. In the device view, click the :guilabel:`Device Twin` button.
#. Create a `firmware` JSON object inside the *desired* object of the device twin document, containing information about the binary to download:

   .. parsed-literal::
      :class: highlight

	{
	    "firmware": {
	        "fwVersion": "v0.0.0-dev",
	        "fwLocation": {
	            "host": "my-storage-account.blob.core.windows.net",
	            "path": "my-app-update.bin"
	        },
	        "fwFragmentSize": 1800
	    }
	}

   See the documentation on :ref:`lib_azure_fota` library for more details.
#. Apply the changes to the device twin by clicking :guilabel:`Save`.
#. Updating the device twin causes a message to be sent to the device, containing the updates to the *desired* object.
#. In the terminal emulator, observe that the new firmware image is downloaded and installed as shown below::

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

#. When the development kit reboots, observe that the sample displays the logs from the new application.
#. In Azure Portal, confirm that the device twin now contains the updated application version in the ``reported.firmware.fwVersion`` field.


Dependencies
************

This sample uses the following |NCS| libraries:

* :ref:`lib_azure_fota`
* :ref:`lib_azure_iot_hub`
* :ref:`lte_lc_readme`

It uses the following `nrfxlib`_ libraries:

* :ref:`nrfxlib:bsdlib`


It uses the following Zephyr libraries:

* :ref:`MQTT <zephyr:networking_api>`

In addition, it uses the following |NCS| sample:

* :ref:`secure_partition_manager`
