.. _ncs_release_notes_340:

|NCS| v3.4.0 Release Notes
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

Added the following features as supported:
#TODO

Added the following features as experimental:
#TODO



Sign up for the `nRF Connect SDK v3.4.0 webinar`_ to learn more about the new features.

Release tag
***********

The release tag for the |NCS| manifest repository (|ncs_repo|) is **v3.4.0**.
Check the :file:`west.yml` file for the corresponding tags in the project repositories.

To use this release, check out the tag in the manifest repository and run ``west update``.
See :ref:`cloning_the_repositories` and :ref:`gs_updating_repos_examples` for more information.

For information on the included repositories and revisions, see `Repositories and revisions for v3.4.0`_.

        
Integration test results
************************

The integration test results for this tag can be found in the following external artifactory:

* `Twister test report for nRF Connect SDK v3.4.0`_
* `Hardware test report for nRF Connect SDK v3.4.0`_

IDE and tool support
********************

`nRF Connect extension for Visual Studio Code <nRF Connect for Visual Studio Code_>`_ is the recommended IDE for |NCS| v3.4.0.
See the :ref:`installation` section for more information about supported operating systems and toolchain.

Supported modem firmware
************************

See the following documentation for an overview of which modem firmware versions have been tested with this version of the |NCS|:

* `Modem firmware compatibility matrix for the nRF9151 SoC`_
* `Modem firmware compatibility matrix for the nRF9160 SoC`_

Use the latest version of the `Programmer app`_ of `nRF Connect for Desktop`_ to update the modem firmware.
See `Programming nRF91 Series DK firmware`_ for instructions.

Modem-related libraries and versions
====================================

.. list-table:: Modem-related libraries and versions
   :widths: 15 10
   :header-rows: 1

   * - Library name
     - Version information
   * - Modem library
     - `Changelog <Modem library changelog for v3.4.0_>`_
   * - LwM2M carrier library
     - `Changelog <LwM2M carrier library changelog for v3.4.0_>`_

Migration notes
***************

See the `Migration notes for nRF Connect SDK v3.4.0`_ for the changes required or recommended when migrating your application from |NCS| v3.3.0 to |NCS| v3.4.0.

Known issues
************

Known issues are only tracked for the latest official release.
See `known issues for nRF Connect SDK v3.4.0`_ for the list of issues valid for the latest release.

.. _ncs_release_notes_340_changelog:

Changelog
*********

The following sections provide detailed lists of changes by component.

#TODO
Bootloaders and DFU
===================

* Added the hidden :kconfig:option:`CONFIG_NCS_MCUBOOT_ENCRYPTION_HMAC_SHA256` to select HMAC-SHA256 with X25519 for compatibility with existing projects that use it.
  The option is hidden and requires addition of Kconfig override in your project.
  This is intentional as HMAC-SHA512 is recommended over HMAC-SHA256.
|no_changes_yet_note|

Developing with nRF54L Series
=============================

* Added:

  * The :kconfig:option:`CONFIG_SB_CRACEN_KMU_INVALIDATE_PROTECTED_RAM_SLOTS` sysbuild Kconfig option to populate the Key Management Unit (KMU) slots for invalidation of the CRACEN-protected RAM using nrfutil.
    This option requires ``nrfutil device`` version 2.15.4 or later to work.
    When enabled, the :kconfig:option:`CONFIG_CRACEN_PROVISION_PROT_RAM_INV_SLOTS_ON_INIT` and :kconfig:option:`CONFIG_CRACEN_PROVISION_PROT_RAM_INV_SLOTS_WITH_IMPORT` Kconfig options become unavailable, as they implement the same feature through alternative provisioning paths.

Security
========

* Added:

  * Support for the X25519 key pair storage in the :ref:`Key Management Unit (KMU) <ug_kmu_guides_supported_key_types>`.
  * The :kconfig:option:`CONFIG_TFM_LOG_NS_MEMORY_LAYOUT` Kconfig option, which allows printing the configuration of the Secure Attribution Unit (SAU) and the Memory Protection Controller (MPC) during the initialization of TF-M on the nRF54L Series devices.
    See also :ref:`ug_tfm_logging` for more information.
* Updated:

  * Oberon PSA Crypto from v1.5.4 to v2.0.0.
    The new version aligns with TF-PSA-Crypto v1.1.0.
  * How the :kconfig:option:`CONFIG_NRF_SECURITY` and :kconfig:option:`CONFIG_PSA_CRYPTO` interact with each other.
    :kconfig:option:`CONFIG_NRF_SECURITY` is now promptless and auto-enabled indirectly by :kconfig:option:`CONFIG_PSA_CRYPTO`.
  * Approach to store keys in the KMU so that AEAD algorithms with non-default (shortened) tag lengths are supported.
* Fixed issues with incorrect support status on the :ref:`ug_crypto_supported_features` page:

  * The :kconfig:option:`CONFIG_PSA_WANT_ALG_GCM` Kconfig option is now correctly listed as unsupported for SoCs with Arm CryptoCell CC310.
  * The tables for supported AES key wrapping algorithms for nRF54L Series devices now list the nRF54LS05 device (not supported in the CRACEN driver; experimental in the nrf_oberon driver).
  * The post-quantum cryptography algorithms for nrf_oberon under Key types and key management are now correctly listed as experimental instead of supported.
  * The SPAKE2+ for Matter is now correctly listed as supported instead of experimental.
  * The WPA3-SAE hash-to-element algorithm is now correctly listed as a KDF algorithm, not a PAKE algorithm.
  * The SHA-256/192 and SHAKE hashing algorithms are now correctly listed as not supported in the CRACEN driver and Experimental in the nrf_oberon driver.
    The only exception is the SHAKE256 512 bits algorithm, which is supported in both the CRACEN and nrf_oberon drivers.
* Removed the ``CONFIG_NRF_SECURITY_ADVANCED`` Kconfig option.

Security libraries
------------------

* :ref:`nrf_security_readme` library:

  * Updated the documentation to one library page with sections for PSA Crypto, TLS and X.509, dependencies, and API documentation.
    The page includes information about how :kconfig:option:`CONFIG_PSA_CRYPTO` and :kconfig:option:`CONFIG_MBEDTLS` are used after the Mbed TLS v4.1 update.
  * Removed the configuration page for the deprecated legacy crypto backend (:file:`libraries/security/nrf_security/doc/backend_config`).
    Configure cryptographic features using :ref:`psa_crypto_support` and :ref:`ug_crypto_supported_features` instead.

Mbed TLS
--------

* Updated Mbed TLS to v4.1.0 (from v3.6.6).
  For an overview of the changes brought by this update in Mbed TLS and Zephyr, see the following pages:

  * The Mbed TLS sections of the Zephyr v4.4 :ref:`release notes <zephyr_4.4>` and :ref:`migration guide <migration_4.4>`.
  * The release notes from upstream Mbed TLS:

    * https://github.com/Mbed-TLS/mbedtls/releases/tag/mbedtls-4.0.0
    * https://github.com/Mbed-TLS/TF-PSA-Crypto/releases/tag/tf-psa-crypto-1.0.0
    * https://github.com/Mbed-TLS/mbedtls/releases/tag/mbedtls-4.1.0
    * https://github.com/Mbed-TLS/TF-PSA-Crypto/releases/tag/tf-psa-crypto-1.1.0
  As part of this update, the following changes were made:

  * Removed support for legacy, deprecated Mbed TLS Crypto APIs and related tests.
  * Rearranged Kconfig options related to Mbed TLS in various files under :ref:`nrf_security`.
  * Removed outdated Kconfig options related to Mbed TLS in various files under :ref:`nrf_security`.
  * :ref:`nrf_security` now uses the Mbed TLS integration from Zephyr as-is (:kconfig:option:`CONFIG_MBEDTLS_BUILTIN`) while replacing upstream TF-PSA-Crypto with Oberon PSA Crypto (:kconfig:option:`CONFIG_TF_PSA_CRYPTO_CUSTOM`).
  From this update onwards:

  * Enable :kconfig:option:`CONFIG_MBEDTLS` only if you use TLS or X.509.
  * For cryptographic operations, enable only :kconfig:option:`CONFIG_PSA_CRYPTO`.

Protocols
=========

This section provides detailed lists of changes by :ref:`protocol <protocols>`.
See `Samples`_ for lists of changes for the protocol-related samples.

Bluetooth Mesh
--------------

* Added the :ref:`dfu_conf` guide on how to configure DFU for Bluetooth Mesh samples.

Wi-Fi®
------

* Updated the Connection Manager Wi-Fi connectivity layer to defer the connect request to its dedicated work queue (``wifi_conn_wq``) instead of running it synchronously in the context of the caller of :c:func:`conn_mgr_if_connect()`.
  This allows the stacks of the application, shell, and Connection Manager monitor threads to be reduced, as they no longer need to accommodate the Wi-Fi connect call chain.

Applications
============

This section provides detailed lists of changes by :ref:`application <applications>`.

High-Performance Framework (HPF)
--------------------------------

* Added support for the nRF54LC10A SoC.

nRF Desktop
-----------

* Added support for the ``nrf54lc10dk/nrf54lc10a/cpuapp`` board target.

Thingy:53: Matter weather station
---------------------------------

|no_changes_yet_note|
Installer (MCUboot Firmware Loader installer)

-----------------------------------------------
|no_changes_yet_note|

Samples
=======

This section provides detailed lists of changes by :ref:`sample <samples>`.

Bluetooth samples
-----------------

* Added support for the ``nrf54lc10dk/nrf54lc10a/cpuapp`` board target in the :ref:`bluetooth_central_hids`, :ref:`peripheral_hids_keyboard`, and :ref:`peripheral_hids_mouse` samples.

Bluetooth Fast Pair samples
---------------------------

* :ref:`fast_pair_locator_tag` sample:

  * Updated the references to the deleted ``CONFIG_CRACEN_LIB_KMU`` Kconfig option with the :kconfig:option:`CONFIG_CRACEN_KMU` replacement.

Cellular samples
----------------

* Updated Kconfig configuration fragment and devicetree overlay naming by removing the ``overlay-`` prefix for the following samples:

  * :ref:`gnss_sample`
  * :ref:`http_application_update_sample`
  * :ref:`location_sample`
  * :ref:`modem_shell_application`
* :ref:`nrf_cloud_coap_fota_sample` sample:

  * Updated the sample to use the new nRF Cloud CoAP FOTA API.

Cryptography samples
--------------------

* :ref:`crypto_tls` sample:

  * Updated the TLS version support section after the Mbed TLS v4.1.0 update.

Enhanced ShockBurst samples
---------------------------

* Added support for the ``nrf54lc10dk/nrf54lc10a/cpuapp`` board target in all samples.

Peripheral samples
------------------

* Added the :ref:`ppi_seq_spi_sample` sample that demonstrates use of :ref:`ppi_seq_i2c_spi`.

Drivers
=======

This section provides detailed lists of changes by :ref:`driver <drivers>`.

* Added:

  * The :ref:`ppi_seq` driver for triggering periodic hardware tasks using PPI.
  * The :ref:`ppi_seq_i2c_spi` driver, which is using :ref:`ppi_seq` to perform batches of periodic I2C/SPI transfers without waking up the CPU.
  * The :ref:`vtf_monitoring` for battery voltage, temperature, and frequency monitoring.

SPI drivers
-----------

* SPIM:

  * RTIO based device driver for SPIM has been introduced. This device driver is selected if
    :kconfig:option:`CONFIG_SPI_RTIO` is enabled.

Libraries
=========

This section provides detailed lists of changes by :ref:`library <libraries>`.

Modem libraries
---------------

* :ref:`lib_location` library:

  * Updated the library to always use the chosen ``zephyr,wifi`` node instead of ``ncs,location-wifi`` to find the used Wi-Fi device.

Integrations
============

This section provides detailed lists of changes by :ref:`integration <integrations>`.

Memfault integration
--------------------

* Removed the ``CONFIG_MEMFAULT_NCS_PROVISION_CERTIFICATES`` Kconfig option from nRF91x targets.
  Certificate provisioning for nRF91x targets is now handled automatically by the `Memfault firmware SDK`_.
  The option remains available for nRF7002 targets, which do not have automatic certificate provisioning.

MCUboot
=======

The MCUboot fork in |NCS| (``sdk-mcuboot``) contains all commits from the upstream MCUboot repository up to and including ``8d14eebfe0b7402ebdf77ce1b99ba1a3793670e9``, with some |NCS| specific additions.

The code for integrating MCUboot into |NCS| is located in the :file:`ncs/nrf/modules/mcuboot` folder.

The following list summarizes both the main changes inherited from upstream MCUboot and the main changes applied to the |NCS| specific additions:

* Added support for the nRF54LC10A SoC.

* The following non-PSA Crypto implementations were deprecated:

  * :kconfig:option:`CONFIG_BOOT_ECDSA_NRF_OBERON`
  * :kconfig:option:`CONFIG_BOOT_ECDSA_TINYCRYPT`
  * :kconfig:option:`CONFIG_BOOT_ECDSA_CC310`
  * :kconfig:option:`CONFIG_BOOT_ED25519_TINYCRYPT`
  * :kconfig:option:`CONFIG_BOOT_ED25519_MBEDTLS`

  Use their PSA Crypto counterparts instead.

Zephyr
======

.. NOTE TO MAINTAINERS: All the Zephyr commits in the below git commands must be handled specially after each upmerge and each nRF Connect SDK release.

The Zephyr fork in |NCS| (``sdk-zephyr``) contains all commits from the upstream Zephyr repository up to and including ``684c9e8f32e4373a21098559f748f06915f950c9``, with some |NCS| specific additions.

For the list of upstream Zephyr commits (not including cherry-picked commits) incorporated into |NCS| since the most recent release, run the following command from the :file:`ncs/zephyr` repository (after running ``west update``):

.. code-block:: none

   git log --oneline 684c9e8f32 ^911b3da139

For the list of |NCS| specific commits, including commits cherry-picked from upstream, run:

.. code-block:: none

   git log --oneline manifest-rev ^684c9e8f32

The current |NCS| main branch is based on revision ``684c9e8f32`` of Zephyr.

.. note::
   For possible breaking changes and changes between the latest Zephyr release and the current Zephyr version, refer to the :ref:`Zephyr release notes <zephyr_release_notes>`.

Zephyr
======

.. NOTE TO MAINTAINERS: All the Zephyr commits in the below git commands must be handled specially after each upmerge and each nRF Connect SDK release.
The Zephyr fork in |NCS| (``sdk-zephyr``) contains all commits from the upstream Zephyr repository up to and including ``684c9e8f32e4373a21098559f748f06915f950c9``, with some |NCS| specific additions.
For the list of upstream Zephyr commits (not including cherry-picked commits) incorporated into |NCS| since the most recent release, run the following command from the :file:`ncs/zephyr` repository (after running ``west update``):
.. code-block:: none
   git log --oneline 684c9e8f32 ^911b3da139
For the list of |NCS| specific commits, including commits cherry-picked from upstream, run:
.. code-block:: none
   git log --oneline manifest-rev ^684c9e8f32
The current |NCS| main branch is based on revision ``684c9e8f32`` of Zephyr.
.. note::
   For possible breaking changes and changes between the latest Zephyr release and the current Zephyr version, refer to the :ref:`Zephyr release notes <zephyr_release_notes>`.

Additions specific to |NCS|
---------------------------

* Updated the :file:`VERSION` file to follow the common version format structure.
  The common version file format structure is extended with a ``VERSION_METADATA`` field for |NCS|.
