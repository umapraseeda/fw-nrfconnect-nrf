.. _ug_tls_prov_credentials_ncs:

Provisioning of credentials in |NCS|
####################################

The way of provisioning the certificates and keys to the client varies from device to device.
For the TLS implementation in the nRF9160's modem, you can provision the certificates in the following ways:

   * Using the :ref:`modem_key_mgmt` library in |NCS|.
   * Using AT commands and `LTE Link Monitor`_ application for nRF Connect for Desktop, which offers a graphical user interface.
     See `Managing credentials`_ for more information.
     
Note that the certificates must be in PEM format.

If the native Zephyr TLS stack is used, the provisioning is done with a separate API.
In the case of :ref:`modem_key_mgmt` API and Zephyr API, the certificates and keys are provisioned to a ``security tag``.
A ``security tag`` is an identifier of a slot to the location where the associated certificates and keys are stored.

.. note::
   If you are using the LTE Link Monitor application, provisioning cannot be done if the modem is in the ``normal`` functional mode.
   In practice, it implies that LTE and GPS cannot be enabled when provisioning certificates.
   You can verify this by sending AT commands ``AT+CFUN=4`` or ``AT+CFUN=0``.

If the native Zephyr stack is used, the following code snippet can be used to provision a CA certificate to security tag 10:

.. code-block:: console

   int err = tls_credential_add(10, TLS_CREDENTIAL_CA_CERTIFICATE, ca_certificate, sizeof(ca_certificate));
 
   if (err < 0) {
           LOG_ERR("Failed to register CA certificate, error: %d", err);
           return err;
                 }

The credential types for the client certificate and the private key are ``TLS_CREDENTIAL_SERVER_CERTIFICATE`` and ``TLS_CREDENTIAL_PRIVATE_KEY`` respectively.

When configuring a socket to use TLS, the security tag must be set with a socket option.
It is possible to provide a list of security tags to support more than one root certificate if the server has more than one certificate.
The following code snippet shows how to configure security tag 10 for a socket:

.. code-block:: console

   const sec_tag_t tls_sec_tag[] = { 10 };
 
   int err = setsockopt(fd, SOL_TLS, TLS_SEC_TAG_LIST, tls_sec_tag, sizeof(tls_sec_tag));
 
   if (err < 0) {
           LOG_ERR("Failed to setup TLS sec tag, error: %d\n", errno);
           return err;
                  }
