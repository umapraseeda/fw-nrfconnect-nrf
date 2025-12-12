.. _ncs_release_notes_321:

|NCS| v3.2.1 Release Notes
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

This patch release adds the following changes on top of the :ref:`nRF Connect SDK v3.2.0 <ncs_release_notes_320>`:
#TODO

Sign up for the `nRF Connect SDK v3.2.1 webinar`_ to learn more about the new features.

Release tag
***********

The release tag for the |NCS| manifest repository (|ncs_repo|) is **v3.2.1**.
Check the :file:`west.yml` file for the corresponding tags in the project repositories.

To use this release, check out the tag in the manifest repository and run ``west update``.
See :ref:`cloning_the_repositories` and :ref:`gs_updating_repos_examples` for more information.

For information on the included repositories and revisions, see `Repositories and revisions for v3.2.1`_.

Integration test results
************************

The integration test results for this tag can be found in the following external artifactory:

* `Twister test report for nRF Connect SDK v3.2.1`_
* `Hardware test report for nRF Connect SDK v3.2.1`_

IDE and tool support
********************

`nRF Connect extension for Visual Studio Code <nRF Connect for Visual Studio Code_>`_ is the recommended IDE for |NCS| v3.2.1.
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
     - `Changelog <Modem library changelog for v3.2.1_>`_
   * - LwM2M carrier library
     - `Changelog <LwM2M carrier library changelog for v3.2.1_>`_

Migration notes
***************

See the `Migration guide for nRF Connect SDK v3.2.1`_ for the changes required or recommended when migrating your application from |NCS| v3.1.1 to |NCS| v3.2.1.

Known issues
************

Known issues are only tracked for the latest official release.
See `known issues for nRF Connect SDK v3.2.1`_ for the list of issues valid for the latest release.

.. _ncs_release_notes_321_changelog:

Changelog
*********

The following sections provide detailed lists of changes by component.

#TODO
Samples
=======

This section provides detailed lists of changes by :ref:`sample <samples>`.

Drivers
=======

This section provides detailed lists of changes by :ref:`driver <drivers>`.

Libraries
=========

This section provides detailed lists of changes by :ref:`library <libraries>`.

sdk-nrfxlib
-----------

See the changelog for each library in the :doc:`nrfxlib documentation <nrfxlib:README>` for additional information.

Integrations
============

This section provides detailed lists of changes by :ref:`integration <integrations>`.

Memfault integration
--------------------

* Updated:

  * The ``CONFIG_MEMFAULT_DEVICE_INFO_CUSTOM`` Kconfig option has been renamed to :kconfig:option:`CONFIG_MEMFAULT_NCS_DEVICE_INFO_CUSTOM`.
  * The ``CONFIG_MEMFAULT_DEVICE_INFO_BUILTIN`` Kconfig option has been renamed to :kconfig:option:`CONFIG_MEMFAULT_NCS_DEVICE_INFO_BUILTIN`.

MCUboot
=======

The MCUboot fork in |NCS| (``sdk-mcuboot``) contains all commits from the upstream MCUboot repository up to and including ``8d14eebfe0b7402ebdf77ce1b99ba1a3793670e9``, with some |NCS| specific additions.

The code for integrating MCUboot into |NCS| is located in the :file:`ncs/nrf/modules/mcuboot` folder.

The following list summarizes both the main changes inherited from upstream MCUboot and the main changes applied to the |NCS| specific additions:

|no_changes_yet_note|

Zephyr
======

.. NOTE TO MAINTAINERS: All the Zephyr commits in the below git commands must be handled specially after each upmerge and each nRF Connect SDK release.

The Zephyr fork in |NCS| (``sdk-zephyr``) contains all commits from the upstream Zephyr repository up to and including ``911b3da1394dc6846c706868b1d407495701926f``, with some |NCS| specific additions.

For the list of upstream Zephyr commits (not including cherry-picked commits) incorporated into |NCS| since the most recent release, run the following command from the :file:`ncs/zephyr` repository (after running ``west update``):

.. code-block:: none

   git log --oneline 911b3da139 ^0fe59bf1e4

For the list of |NCS| specific commits, including commits cherry-picked from upstream, run:

.. code-block:: none

   git log --oneline manifest-rev ^911b3da139

The current |NCS| main branch is based on revision ``0fe59bf1e4`` of Zephyr.

.. note::
   For possible breaking changes and changes between the latest Zephyr release and the current Zephyr version, refer to the :ref:`Zephyr release notes <zephyr_release_notes>`.

Documentation
=============

