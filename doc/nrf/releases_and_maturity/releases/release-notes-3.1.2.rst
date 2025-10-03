.. _ncs_release_notes_312:

|NCS| v3.1.2 Release Notes
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

This patch release adds the following changes on top of the :ref:`nRF Connect SDK v3.1.1 <ncs_release_notes_311>` and :ref:`nRF Connect SDK v3.1.0 <ncs_release_notes_310>`:
#TODO

Release tag
***********

The release tag for the |NCS| manifest repository (|ncs_repo|) is **v3.1.2**.
Check the :file:`west.yml` file for the corresponding tags in the project repositories.

To use this release, check out the tag in the manifest repository and run ``west update``.
See :ref:`cloning_the_repositories` and :ref:`gs_updating_repos_examples` for more information.

For information on the included repositories and revisions, see `Repositories and revisions for v3.1.2`_.

IDE and tool support
********************

`nRF Connect extension for Visual Studio Code <nRF Connect for Visual Studio Code_>`_ is the recommended IDE for |NCS| v3.1.2.
See the :ref:`installation` section for more information about supported operating systems and toolchain.

Supported modem firmware
************************

See `Modem firmware compatibility matrix`_ for an overview of which modem firmware versions have been tested with this version of the |NCS|.

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
     - `Changelog <Modem library changelog for v3.1.2_>`_
   * - LwM2M carrier library
     - `Changelog <LwM2M carrier library changelog for v3.1.2_>`_

Known issues
************

Known issues are only tracked for the latest official release.
See `known issues for nRF Connect SDK v3.1.2`_ for the list of issues valid for the latest release.

.. _ncs_release_notes_312_changelog:

Changelog
*********

The following sections provide detailed lists of changes by component.

#TODO
Changelog
*********
Build and configuration system
==============================

|no_changes_yet_note|

Developing with nRF91 Series
============================

|no_changes_yet_note|

Developing with nRF70 Series
============================

|no_changes_yet_note|

Developing with nRF54L Series
=============================

|no_changes_yet_note|

Developing with nRF54H Series
=============================

|no_changes_yet_note|

Developing with nRF53 Series
============================

|no_changes_yet_note|

Developing with nRF52 Series
============================

|no_changes_yet_note|

Developing with Thingy:91 X
===========================

|no_changes_yet_note|

Developing with Thingy:53
=========================

|no_changes_yet_note|

Developing with PMICs
=====================

|no_changes_yet_note|

Developing with Front-End Modules
=================================

|no_changes_yet_note|

Developing with custom boards
=============================

|no_changes_yet_note|

Developing with coprocessors
============================

|no_changes_yet_note|

Protocols
=========

|no_changes_yet_note|

Amazon Sidewalk
---------------

|no_changes_yet_note|

Bluetooth® LE
-------------

|no_changes_yet_note|

DECT NR+
--------

|no_changes_yet_note|

Gazell
------

|no_changes_yet_note|

Matter
------

|no_changes_yet_note|

Matter fork
+++++++++++

|no_changes_yet_note|

nRF IEEE 802.15.4 radio driver
------------------------------

|no_changes_yet_note|

Wi-Fi®
------

|no_changes_yet_note|

Applications
============

|no_changes_yet_note|

Connectivity bridge
-------------------

|no_changes_yet_note|

IPC radio firmware
------------------

|no_changes_yet_note|

Thingy:53: Matter weather station
---------------------------------

|no_changes_yet_note|

Amazon Sidewalk samples
-----------------------

|no_changes_yet_note|

Debug samples
-------------

|no_changes_yet_note|

DECT NR+ samples
----------------

|no_changes_yet_note|

Edge Impulse samples
--------------------

|no_changes_yet_note|

Gazell samples
--------------

|no_changes_yet_note|

Keys samples
------------

|no_changes_yet_note|

NFC samples
-----------

|no_changes_yet_note|

nRF5340 samples
---------------

|no_changes_yet_note|

Peripheral samples
------------------

|no_changes_yet_note|

PMIC samples
------------

|no_changes_yet_note|

Protocol serialization samples
------------------------------

|no_changes_yet_note|

SDFW samples
------------

|no_changes_yet_note|

Sensor samples
--------------

|no_changes_yet_note|

SUIT samples
------------

|no_changes_yet_note|

Trusted Firmware-M (TF-M) samples
---------------------------------

|no_changes_yet_note|

Thread samples
--------------

|no_changes_yet_note|

Wi-Fi drivers
-------------

|no_changes_yet_note|

Flash drivers
-------------

|no_changes_yet_note|

Binary libraries
----------------

|no_changes_yet_note|

Common Application Framework
----------------------------

|no_changes_yet_note|

Debug libraries
---------------

|no_changes_yet_note|

DFU libraries
-------------

|no_changes_yet_note|

Gazell libraries
----------------

|no_changes_yet_note|

Security libraries
------------------

|no_changes_yet_note|

Multiprotocol Service Layer libraries
-------------------------------------

|no_changes_yet_note|

Libraries for NFC
-----------------

|no_changes_yet_note|

nRF RPC libraries
-----------------

|no_changes_yet_note|

Shell libraries
---------------

|no_changes_yet_note|

Edge Impulse integration
------------------------

|no_changes_yet_note|

Memfault integration
--------------------

|no_changes_yet_note|

AVSystem integration
--------------------

|no_changes_yet_note|

nRF Cloud integration
---------------------

|no_changes_yet_note|

CoreMark integration
--------------------

|no_changes_yet_note|

DULT integration
----------------

|no_changes_yet_note|

MCUboot
=======

The MCUboot fork in |NCS| (``sdk-mcuboot``) contains all commits from the upstream MCUboot repository up to and including ``81315483fcbdf1f1524c2b34a1fd4de6c77cd0f4``, with some |NCS| specific additions.

The code for integrating MCUboot into |NCS| is located in the :file:`ncs/nrf/modules/mcuboot` folder.

The following list summarizes both the main changes inherited from upstream MCUboot and the main changes applied to the |NCS| specific additions:

|no_changes_yet_note|

Zephyr
======

.. NOTE TO MAINTAINERS: All the Zephyr commits in the below git commands must be handled specially after each upmerge and each nRF Connect SDK release.

The Zephyr fork in |NCS| (``sdk-zephyr``) contains all commits from the upstream Zephyr repository up to and including ``0fe59bf1e4b96122c3467295b09a034e399c5ee6``, with some |NCS| specific additions.

For the list of upstream Zephyr commits (not including cherry-picked commits) incorporated into |NCS| since the most recent release, run the following command from the :file:`ncs/zephyr` repository (after running ``west update``):

.. code-block:: none

   git log --oneline 0fe59bf1e4 ^fdeb735017

For the list of |NCS| specific commits, including commits cherry-picked from upstream, run:

.. code-block:: none

   git log --oneline manifest-rev ^0fe59bf1e4

The current |NCS| main branch is based on revision ``0fe59bf1e4`` of Zephyr.

.. note::
   For possible breaking changes and changes between the latest Zephyr release and the current Zephyr version, refer to the :ref:`Zephyr release notes <zephyr_release_notes>`.

Additions specific to |NCS|
---------------------------

|no_changes_yet_note|

zcbor
=====

|no_changes_yet_note|

