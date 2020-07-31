.. _azure_iot_hub:

nRF9160: Azure IoT Hub
######################

The Azure IoT Hub sample shows the communication of an nRF9160-based device with an `Azure IoT Hub`_.
This sample uses the :ref:`lib_azure_iot_hub` library to communicate with the IoT hub.

Overview
********

The sample supports connecting to an Azure IoT Hub directly for an already registered IoT device, or by using `Azure IoT Hub DPS`_ to first provision the device to an IoT Hub.
More details on this can be found in :ref:`lib_azure_iot_hub`.

The sample periodically publishes telemetry messages (events) to the connected Azure IoT Hub.
Telemetry messages are by default sent every 20 seconds.
The default interval can be configured by setting the device twin property `desired.telemetryInterval`, which will be interpreted by the sample in units of seconds.
A telemetry message is formatted like this:

.. parsed-literal::
:class: highlight

    {
        "temperature" : 25.2,
	"timestamp": 151325
    }

where `temperature` is a value between 25.0 and 25.9, and `timestamp` is the board's uptime in milliseconds.

The sample has implemented handling of `Azure IoT Hub direct method`_ with name `led`.
If the device receives a direct method invocation with name `led` and payload `1` or `0`, LED 1 on the board will be turned on or off, respectively.


Requirements
************

An Azure IoT Hub instance must be set up and configured per the instructions in `_configuration_options`_ for the sample to work as intended.
The device needs to have certificates provisioned for the TLS connection to Azure IoT Hub to successfully be established.
Follow the instructions in `_connect_to_azure_iot_hub`_ to set up an Azure IoT Hub and provision required certificates to the device.

The sample supports the following development kits:

.. include:: /includes/boardname_tables/sample_boardnames.txt
   :start-after: set6_start
   :end-before: set6_end

.. include:: /includes/spm.txt


.. _configure_options:

Configuration
*************

The minimum :ref:`lib_azure_iot_hub` Kconfig options needed to be configured in this sample are the following:

.. option:: :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID`

Sets the device ID to be used when connecting to Azure IoT Hub.
The device ID is also needed if DPS is used.
An alternative to setting the device ID in Kconfig is to enable :option:`CONFIG_AZURE_IOT_HUB_DEVICE_ID_APP` and set the device ID at runtime in the configuration struct passed to :cpp:func:`azure_iot_hub_init`.


.. option:: :option:`CONFIG_AZURE_IOT_HUB_HOSTNAME`

Sets the Azure IoT Hub hostname.
If `Azure IoT Hub DPS`_ is used, it's assumed the IoT hub hostname is unknown, and the configuration will be ignored.


.. option:: :option:`CONFIG_AZURE_IOT_HUB_DPS`

Enables `Azure IoT Hub DPS`_, and makes the library connect to the DPS server to provision the device and receive IoT hub name and hostname.


.. option:: :option:`CONFIG_AZURE_IOT_HUB_DPS_ID_SCOPE`

Sets the `Azure IoT Hub DPS`_ ID scope to use when provisioning the device.


Building and running
********************

.. |sample path| replace:: :file:`samples/nrf9160/azure_iot_hub`
.. include:: /includes/build_and_run_nrf9160.txt
.. include:: /includes/spm.txt

Testing
=======

Microsoft have created `Azure IoT Explorer`_ to interact and test devices connected to an Azure IoT Hub.
Optionally, follow the instructions at `Azure IoT Explorer`_ to install and configure the tool and use it where mentioned in the below instructions.

1. |connect_terminal|
#. Reset the board.
#. Observe the log output and verify that it's similar to the sample output below.
#. Use the `Azure IoT Explorer`_, or log in to the `Azure Portal`_, select the connected IoT Hub and IoT device. Change (or add if it doesn't exist) the device twin's desired property ``telemetryInterval`` to a new value, for instance ``10`` and save the updated device twin.
#. Observe that the device receives the updated ``telemetryInterval`` value, applies it and starts sending new telemetry events every 10 seconds.
   Verify that the ``reported`` object in the device twin now has a ``telemetryInterval`` property with the correct value reported back from the device.
#. In the `Azure IoT Explorer`_ or device page in `Azure Portal`_, go to the ``Direct method` tab. Enter the method name ``led``. In the payload, enter the value ``1`` (or ``0``). Click `Invoke method`.
#. Observe that LED 1 on the board lights up (or switches off if ``0`` was entered as the payload). In `Azure IoT Explorer`_, a notification should open up in the top right corner stating if the direct method was successfully invoked or not based on the report back from the device.
#. If using the `Azure IoT Explorer`_, navigate to the ``Telemetry`` tab. Click ``start``.
#. Observe event messages coming in from the device at the specified telemetry interval.


Sample Output
=============

When the sample runs, the device boots, and the sample displays similar output to the following in the terminal over UART:

.. code-block:: console

	*** Booting Zephyr OS build v2.3.0-rc1-ncs1-1453-gf41496cd30d5  ***
	Azure IoT Hub sample started
	Connecting to LTE network
	Connected to LTE network
	AZURE_IOT_HUB_EVT_CONNECTING
	AZURE_IOT_HUB_EVT_CONNECTED
	AZURE_IOT_HUB_EVT_READY
	AZURE_IOT_HUB_EVT_TWIN_RECEIVED
	No 'telemetryInterval' object in the device twin
	Sending event:
	{"temperature":25.9,"timestamp":16849}
	Event was successfully sent
	Next event will be sent in 20 seconds

	...

	AZURE_IOT_HUB_EVT_TWIN_DESIRED_RECEIVED
	New telemetry interval has been applied: 60
	AZURE_IOT_HUB_EVT_TWIN_RESULT_SUCCESS, ID: 42740
	Sending event:
	{"temperature":25.5,"timestamp":47585}
	Event was successfully sent
	Next event will be sent in 60 seconds


Dependencies
************

This sample uses the following |NCS| libraries and drivers:

* :ref:`lib_azure_iot_hub`
* ``lib/bsd_lib``
* ``lib/lte_link_control``

In addition it uses the Secure Partition Manager sample:

* :ref:`secure_partition_manager`
