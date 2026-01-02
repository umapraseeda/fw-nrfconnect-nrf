.. _ncs_release_notes_322:

|NCS| v3.2.2 Release Notes
##########################

.. contents::
   :local:
   :depth: 2

|NCS| delivers reference software and supporting libraries for developing low-power wireless applications with Nordic Semiconductor products in the nRF52, nRF53, nRF54, nRF70, and nRF91 Series.
The SDK includes open source projects (TF-M, MCUboot, OpenThread, Matter, and the Zephyr RTOS), which are continuously integrated and redistributed with the SDK.

Release notes might refer to "experimental" support for features, which indicates that the feature is incomplete in functionality or verification, and can be expected to change in future releases.
To learn more, see :ref:`software_maturity`.

Highlights
**********

This patch release adds the following changes on top of the :ref:`nRF Connect SDK v3.2.1 <ncs_release_notes_321>` and :ref:`nRF Connect SDK v3.2.0 <ncs_release_notes_320>`:
#TODO

Release tag
***********

The release tag for the |NCS| manifest repository (|ncs_repo|) is **v3.2.2**.
Check the :file:`west.yml` file for the corresponding tags in the project repositories.

To use this release, check out the tag in the manifest repository and run ``west update``.
See :ref:`cloning_the_repositories` and :ref:`gs_updating_repos_examples` for more information.

For information on the included repositories and revisions, see `Repositories and revisions for v3.2.2`_.

IDE and tool support
********************

`nRF Connect extension for Visual Studio Code <nRF Connect for Visual Studio Code_>`_ is the recommended IDE for |NCS| v3.2.2.
See the :ref:`installation` section for more information about supported operating systems and toolchain.

Supported modem firmware
************************

See the following documentation for an overview of which modem firmware versions have been tested with this version of the |NCS|:

* `Modem firmware compatibility matrix for the nRF9151 SoC`_
* `Modem firmware compatibility matrix for the nRF9160 SoC`_

Use the latest version of the `Programmer app`_ of `nRF Connect for Desktop`_ to update the modem firmware.
See :ref:`nrf9160_gs_updating_fw_modem` for instructions.

Modem-related libraries and versions
====================================

.. list-table:: Modem-related libraries and versions
   :widths: 15 10
   :header-rows: 1

   * - Library name
     - Version information
   * - Modem library
     - `Changelog <Modem library changelog for v3.2.2_>`_
   * - LwM2M carrier library
     - `Changelog <LwM2M carrier library changelog for v3.2.2_>`_

Known issues
************

Known issues are only tracked for the latest official release.
See `known issues for nRF Connect SDK v3.2.2`_ for the list of issues valid for the latest release.

.. _ncs_release_notes_322_changelog:

Changelog
*********

The following sections provide detailed lists of changes by component.

#TODO
Security
========

* Added:

  * Support for the WPA3-SAE and WPA3-SAE-PT in the :ref:`CRACEN driver <crypto_drivers_cracen>`.
  * Support for the HMAC KDF algorithm in the CRACEN driver.
    The algorithm implementation is conformant to the NIST SP 800-108 Rev. 1 recommendation.

Protocols
=========

This section provides detailed lists of changes by :ref:`protocol <protocols>`.
See `Samples`_ for lists of changes for the protocol-related samples.

Enhanced ShockBurst (ESB)
-------------------------

* Fixed invalid radio configuration for legacy ESB protocol.

Matter
------

* Updated the :ref:`matter_test_event_triggers_default_test_event_triggers` section with the new Closure Control cluster test event triggers.

Applications
============

This section provides detailed lists of changes by :ref:`application <applications>`.

nRF5340 Audio
-------------

* Added dynamic configuration of the number of channels for the encoder based on the configured audio locations.
  The number of channels is set during runtime using the :c:func:`audio_system_encoder_num_ch_set` function.
  This allows configuring mono or stereo encoding depending on the configured audio locations, potentially saving CPU and memory resources.
* Added high CPU load callback using the Zephyr CPU load subsystem.
  The callback uses a :c:func:`printk` function, as the logging subsystem is scheduled out if higher priority threads take all CPU time.
  This makes debugging high CPU load situations easier in the application.
  The threshold for high CPU load is set in :file:`peripherals.c` using :c:macro:`CPU_LOAD_HIGH_THRESHOLD_PERCENT`.
* Updated the buildprog/programming script.
  Devices are now halted before programming.
  Furthermore, the devices are kept halted until they are all programmed, and then started together
  with the headsets starting first.
  This eases sniffing of advertisement packets.

nRF Desktop
-----------

* Updated the :option:`CONFIG_DESKTOP_BT` Kconfig option to no longer select the deprecated :kconfig:option:`CONFIG_BT_SIGNING` Kconfig option.
  Application relies on Bluetooth LE security mode 1 and security level of at least 2 to ensure data confidentiality through encryption.

Samples
=======

This section provides detailed lists of changes by :ref:`sample <samples>`.

Cryptography samples
--------------------

* :ref:`crypto_aes_ccm` sample:

  * Added support for the ``nrf54lm20dk/nrf54lm20a/cpuapp`` board target.

Matter samples
--------------

* :ref:`matter_manufacturer_specific_sample`:

  * Added support for the ``NRF_MATTER_CLUSTER_INIT`` macro.
* :ref:`matter_closure_sample`:

  * Added support for the Closure Control cluster test event triggers.

Libraries
=========

This section provides detailed lists of changes by :ref:`library <libraries>`.

Modem libraries
---------------

* :ref:`lte_lc_readme` library:

  * Added support for new PDN events :c:enumerator:`LTE_LC_EVT_PDN_SUSPENDED` and :c:enumerator:`LTE_LC_EVT_PDN_RESUMED`.

Other libraries
---------------

* :ref:`lib_hw_id` library:

  * The ``CONFIG_HW_ID_LIBRARY_SOURCE_BLE_MAC`` Kconfig option has been renamed to :kconfig:option:`CONFIG_HW_ID_LIBRARY_SOURCE_BT_DEVICE_ADDRESS`.

Integrations
============

This section provides detailed lists of changes by :ref:`integration <integrations>`.

Memfault integration
--------------------

* Added:

  * The option ``CONFIG_MEMFAULT_NCS_POST_INITIAL_HEARTBEAT_ON_NETWORK_CONNECTED`` to control whether an initial heartbeat is sent when the device connects to a network.
    Useful to be able to show device status and initial metrics in the Memfault dashboard as soon as possible after boot.

Zephyr
======

The Zephyr fork in |NCS| (``sdk-zephyr``) contains all commits from the upstream Zephyr repository up to and including ``911b3da1394dc6846c706868b1d407495701926f``.

For a complete list of |NCS| specific commits and cherry-picked commits since v3.2.0, run the following command:

.. code-block:: none

   git log --oneline manifest-rev ^ncs-v3.2.0
