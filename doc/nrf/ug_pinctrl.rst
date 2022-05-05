.. _ug_pinctrl:

Pin control
###########

.. contents::
   :local:
   :depth: 2

Pin controllers are the hardware blocks that control pin multiplexing and pin configuration.
They are helpful to configure SoC hardware peripherals and to map peripheral signals to the required pins.
Another use of pin controller is configuring certain pin settings for proper functioning of a hardware peripheral.

Following are the configurations that can be set for Nordic SoCs:

* 
*

For more general information, see the :ref:`Zephyr documentation on pin controllers <pinctrl-guide>`.


Migration of the devicetree files
*********************************

The device tree files contain the hardware description or the initial hardware configuration of a development kit.
See :ref:`devicetree-intro` for understanding more about devicetree.

To migrate the devicetree files associated with Nordic development kits, you must complete the following steps:

//check

1. Create a :file:`board-pinctrl.dtsi` file in your project folder or determine the overlay file in the application folder, which needs to be migrated by replacing the existing information with pin control information.
#. Replace old pin-related properties with the new pinctrl states.

States of a device driver
=========================

For a device driver to function properly, it must be in a particular state that is defined by a set of configurations.
The configurations can be set during initialization time or runtime.
For more information, see `Device driver state models`_.
The states are standardized as ``default`` and ``sleep``.

.. note::

   The ``sleep`` state is required only when the Kconfig option :kconfig:option:`CONFIG_PM_DEVICE` is set to ``y``.

nRF pin controller
******************

The nRF pin controller is a singleton node responsible for controlling pin function selection and pin properties.
For example, you can use this node to route UART0 RX to pin **P0.1** and enable the pull-up resistor on the pin.

The node has the ``pinctrl`` node label set in your SoC's devicetree, and you can modify the code as shown in the following snippet:

.. code-block::

   &pinctrl {
           /* your modifications go here */
   };

All device pin configurations must be placed in child nodes of the ``pinctrl`` node, as shown in the following example:

.. code-block::

   &pinctrl {
     /* configuration for uart0 device, default state */
     uart0_default: uart0_default {
       /* group 1 ('group1' name is arbitrary) */
       group1 {
         /* configure P0.1 as UART_TX and P0.2 as UART_RTS */
         psels = <NRF_PSEL(UART_TX, 0, 1)>, <NRF_PSEL(UART_RTS, 0, 2)>;
       };
       /* group 2 */
       group2 {
         /* configure P0.3 as UART_RX and P0.4 as UART_CTS */
         psels = <NRF_PSEL(UART_RX, 0, 3)>, <NRF_PSEL(UART_CTS, 0, 4)>;
         /* both P0.3 and P0.4 are configured with pull-up */
         bias-pull-up;
       };
     };
   };


You can put the previous code in a :file:`board-pinctrl.dtsi` file in your board directory, or a devicetree overlay in your application.

The ``uart0_default`` child node encodes the pin configurations for a particular state of a device; in this case, the default active state.
You can specify the low-power configuration for the same device in a separate child node.

As shown in the code snippet, the pin configurations are organized in groups within each child node.
Each group can specify a list of pin function selections in the ``psels`` property.
The ``NRF_PSEL`` macro is used to specify a pin function selection. 
Available pin functions can be found in the :file:`include/dt-bindings/pinctrl/nrf-pinctrl.h` header file in the `Zephyr repository`_.

A group can also specify shared pin properties common to all the specified pins, such as the ``bias-pull-up`` property in group 2.
Here is a list of the supported standard pin properties:

* bias-disable - Disable pull-up/down (default behavior, not required).
* bias-pull-up - Enable pull-up resistor.
* bias-pull-down - Enable pull-down resistor.
* low-power-enable - Configure pin as an input with input buffer disconnected.

.. note::

   The bias options are mutually exclusive.

To link this pin configuration with a device, use a pinctrl-N property where N is the state index starting from zero.
You can add the code in your board's DTS file as shown in the following code snippet:

.. code-block::

   #include "board-pinctrl.dtsi"

   &uart0 {
         pinctrl-0 = <&uart0_default>;
         pinctrl-names = "default";
   };


See `Nordic nrf-pinctrl node properties`_ for information on the top level properties and child node properties that apply to``nordic,nrf-pinctrl`` nodes.







Pinctrl Migration Utility Script for Nordic development kits
============================================================

This script can be used to automatically migrate the devicetree files of Nordic development kits using the old <signal>-pin properties to select peripheral pins.
The script parses a board devicetree file.
It modifies the file initially by removing old pin-related properties replacing them with pinctrl states.
A :file:`board-pinctrl.dtsi` file containing the configuration for all pinctrl states is generated.

.. note::

   The script also works on files that have been partially ported.

   This script uses a basic line based parser, therefore not all valid devicetree files will be converted correctly. The adjusted/generated files must be manually reviewed.


The script has a known limitation that all SPI nodes will be assumed to be a master device.


Usage 
-----

The script is located at :file:`zephyr/scripts/utils/` folder.
You can use the script in the following way:

 .. code-block::

     python3 pinctrl_nrf_migrate.py
            -i path/to/board.dts
            [--no-backup]
            [--skip-nrf-check]
            [--header ""]

The following example shows the conversion of a devicetree file:

.. code-block:: devicetree

   /* Old board.dts */
       ...
       &uart0 {
           ...
           tx-pin = <5>;
           rx-pin = <33>;
           rx-pull-up;
           ...
       };
   /* Adjusted board.dts */
       ...
        #include "board-pinctrl.dtsi"
       ...
       &uart0 {
           ...
           pinctrl-0 = <&uart0_default>;
           pinctrl-1 = <&uart0_sleep>;
           pinctrl-names = "default", "sleep";
           ...
       };
   /* Generated board-pinctrl.dtsi */
       &pinctrl {
           uart0_default: uart0_default {
               group1 {
                   psels = <NRF_PSEL(UART_TX, 0, 5);
               };
               group2 {
                   psels = <NRF_PSEL(UART_RX, 1, 1)>;
                   bias-pull-up;
               };
           };
           uart0_sleep: uart0_sleep {
               group1 {
                   psels = <NRF_PSEL(UART_TX, 0, 5)>,
                           <NRF_PSEL(UART_RX, 1, 1)>;
                   low-power-enable;
               };
           };
       };


Configuring overlays
********************

 (examples and explanation)
   



