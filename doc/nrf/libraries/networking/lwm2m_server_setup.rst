.. _server_setup_lwm2m:

Server setup
------------

The following instructions describe how to register your device to `Leshan Demo Server`_ or `Coiote Device Management server`_:

1. For adding the device to the LwM2M server, complete the following steps and for adding the device to an LwM2M bootstrap server, see the procedure in :ref:`registering the device to an LwM2M bootstrap server <bootstrap_server_reg>`:

   .. tabs::

      .. tab:: Leshan Demo Server

         1. Open the `Leshan Demo Server web UI`_.
         #. Click :guilabel:`SECURITY` in the upper right corner in the UI.
         #. Click :guilabel:`ADD SECURITY INFORMATION`.
         #. Enter the following data and click :guilabel:`ADD`:

            * Endpoint - urn\:imei\:*your Device IMEI*
            * Security Mode - psk
            * Identity: - urn\:imei\:*your Device IMEI*
            * Key - 000102030405060708090a0b0c0d0e0f

      .. tab:: Coiote Device Management

         1. Open `Coiote Device Management server`_.
         #. Click :guilabel:`Device inventory` in the left menu in the UI.
         #. Click :guilabel:`Add new device`.
         #. Click :guilabel:`Connect your LwM2M device directly via the management server`.
         #. Enter the following data and click :guilabel:`Add device`:

            * Endpoint - urn\:imei\:*your Device IMEI*
            * Friendly Name - *recognizable name*
            * Security mode - psk (Pre-Shared Key)
            * Key - 000102030405060708090a0b0c0d0e0f

            Also, make sure to select the :guilabel:`Key in hexadecimal` checkbox.

   .. _bootstrap_server_reg:

   For registering the device to an LwM2M bootstrap server, complete the following steps:

   .. tabs::

      .. tab:: Leshan Demo Server

         1. Open the `Leshan Bootstrap Server Demo web UI <public Leshan Bootstrap Server Demo_>`_.
         #. Click :guilabel:`BOOTSTRAP` in the upper right corner.
         #. In the :guilabel:`BOOTSTRAP` tab, click :guilabel:`ADD CLIENTS CONFIGURATION`.
         #. Click :guilabel:`Add clients configuration`.
         #. Enter your Client Endpoint name - urn\:imei\:*your device IMEI*.
         #. Click :guilabel:`NEXT` and select :guilabel:`Using (D)TLS` and enter following data:

            * Identity - urn\:imei\:*your device IMEI*
            * Key - ``000102030405060708090a0b0c0d0e0f``
         #. Click :guilabel:`NEXT` and leave default paths to be deleted.
         #. Click :guilabel:`NEXT` and in the **LWM2M Server Configuration** section, enter the following data:

            * Server URL - ``coaps://leshan.eclipseprojects.io:5684``
            * Select :guilabel:`Pre-shared Key` as the **Security Mode**
            * Identity - urn\:imei\:*your device IMEI*
            * Key - ``000102030405060708090a0b0c0d0e0f``

            This information is used when your client connects to the server.
            If you choose :guilabel:`Pre-shared Key`, you must add the values for :guilabel:`Identity` and :guilabel:`Key` fields (the configured Key need not match the Bootstrap Server configuration).
            The same credentials must be provided in the **Leshan Demo Server Security configuration** page (see :ref:`dtls_support` for instructions).

         #. Click :guilabel:`NEXT` and do not select :guilabel:`Add a Bootstrap Server`.
         #. Click :guilabel:`ADD`.


      .. tab:: Coiote Device Management

         1. Open `Coiote Device Management server`_.
         #. Click :guilabel:`Device inventory` in the menu on the left.
         #. Click :guilabel:`Add new device`.
         #. Click :guilabel:`Connect your LwM2M device via the Bootstrap server`.
         #. Enter the following data and click :guilabel:`Configuration`:

            * Endpoint - urn\:imei\:*your Device IMEI*
            * Friendly Name - *recognisable name*
            * Security mode - psk (Pre-Shared Key)
            * Key - 000102030405060708090a0b0c0d0e0f

            Also, make sure to select the :guilabel:`Key in hexadecimal` checkbox.

            The Coiote bootstrap server automatically creates an account for the LwM2M server using the same device endpoint name and random PSK key.

         #. Click :guilabel:`Add device`.

.. note::

   The **Client Configuration** page of the LwM2M Bootstrap server and the **Registered Clients** page of the LwM2M server display only a limited number of devices by default.
   You can increase the number of displayed devices from the drop-down menu associated with **Rows per page**.
   In both cases, the menu is displayed at the bottom-right corner of the **Client Configuration** pages.
