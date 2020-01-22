.. _cloud_simple:

nRF9160: Cloud Simple
#####################

Sample that connects to and communicates with a compatible cloud service using the respective firmware cloud backend. The sample connects via cellular network (LTE) and publishes a custom string in intervals or upon a button trigger, to the cloud service.

Overview
********

The ``cloud_simple`` sample demonstrates how to use the generic cloud API ``subsys/net/lib/cloud`` to interface with multiple cloud backends. The current version of the ``cloud_simple`` sample supports the following libraries as cloud backends:

 -  :ref:`lib_nrf_cloud`
 -  :ref:`lib_aws_iot`

To swap between cloud backends simply change the option ``CONFIG_CLOUD_BACKEND`` to match the configuration string of a compatible cloud backend. The identifying string for the different cloud backends are listed below.

 - **NRF Cloud**, configuration string ->"NRF_CLOUD"
 - **AWS IoT**, configuration string -> "AWS_IOT"

Requirements
************

* One of the following development boards:

 * nRF9160 Development Kit board (PCA_20035)(Thingy:91)
 * nRF9160 Development Kit board (PCA_10090)(nRF9160 DK)


Building and running
********************

The sample can be found under ``samples/cloud_simple`` in the nRF Connect SDK folder structure.

See :ref:`gs_programming` for information about how to build and program the application.

The sample is configured to compile and run as a non-secure application on nRF91’s Cortex-M33. Therefore, it automatically includes the :ref:`secure_partition_manager` that prepares the required peripherals to be available for the application.

Setup
*****

For setting up the different cloud backends please see the corresponding documentations. Each cloud backend has spesific setup steps that must be executed before it can be used. These setup steps cover generating and flashing *certificates* used for the cloud connection, setting up the correct connection *endpoint* etc..

.. note::
   The nRF9160 DK and Thingy:91 comes stock with certificates required for connection to NRF Cloud. For NRF Cloud no extra setup steps are required to use the ``cloud_simple`` sample. See `NRF Cloud web interface <https://nrfcloud.com/#/>`_ for more information.


Configurations
**************

The configurations for the sample are located in ``cloud_simple/src/prj.conf``

.. option:: CONFIG_CLOUD_BACKEND
 
Decides the cloud backend to be used.

.. option:: CONFIG_CLOUD_PUBLICATION_SEQUENTIAL

Publishes custom messages to cloud sequentially.

.. option:: CONFIG_CLOUD_PUBLICATION_BUTTON_PRESS

Publishes custom messages to cloud upon a button press.

.. option:: CONFIG_CLOUD_MESSAGE

Modifies the message published to the cloud service.

.. option:: CONFIG_CLOUD_MESSAGE_PUBLICATION_INTERVAL
    
Modifies the interval within which the message should be published to the cloud service.

.. note::
   To output data in the terminal window located in the `NRF Cloud web interface <https://nrfcloud.com/#/>`_ the data format must be in JSON format.

Functionality and Supported Technologies
****************************************

The communicaton protocol supported by the sample is dependent on the cloud backend that is used. Please see the documentation for the individual cloud backend libraries.

Functions
=========

* :cpp:func:`cloud_get_binding()` : Binds to a desired cloud backend using a identifiable string


* :cpp:func:`cloud_init()` : Sets up the cloud connection


* :cpp:func:`cloud_connect()` : Connects to the cloud service


* :cpp:func:`cloud_ping()` : Keeps the cloud connection alive by periodically pinging the server.


* :cpp:func:`cloud_input()` : Retrieve data from the cloud service.


* :cpp:func:`cloud_send()` : Send data to the cloud service.

Cloud events used in the sample
===============================

* :cpp:enumerator:`CLOUD_EVT_CONNECTED <cloud_api::CLOUD_EVT_CONNECTED>` : Connected to the cloud service


* :cpp:enumerator:`CLOUD_EVT_READY<cloud_api::CLOUD_EVT_READY>` : Cloud connection established and ready to communicate


* :cpp:enumerator:`CLOUD_EVT_DISCONNECTED<cloud_api::CLOUD_EVT_DISCONNECTED>` : Disconnected from the cloud service


* :cpp:enumerator:`CLOUD_EVT_DATA_RECEIVED<cloud_api::CLOUD_EVT_DATA_RECEIVED>` : Receive data from the cloud service

.. note::
   Not all functionality present in the generic cloud API are used by the different cloud backends.


Current dependencies
********************

This sample uses the following |NCS| libraries and drivers:

    * :ref:`lib_nrf_cloud`
    * :ref:`lib_aws_iot`
    * :ref:`dk_buttons_and_leds_readme`
    * ``lib/bsd_lib``
    * ``subsys/net/lib/cloud``
    * ``lib/lte_link_control``

In addition, it uses the Secure Partition Manager sample:

* :ref:`secure_partition_manager`
