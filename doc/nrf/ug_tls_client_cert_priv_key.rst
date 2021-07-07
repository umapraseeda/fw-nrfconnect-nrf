.. _ug_tls_client_cert_priv_key:

Client certificate and private key generation
#############################################

The following subsections describe how the client-side certificates and the private key are generated.

Root certificate
****************

You must generate a root certificate and a private key that are used to sign a client certificate.
The root certificate and private key can be used to create new intermediate and client certificates.
The private key must therefore be kept confidential.
It is recommended to protect the private key with a strong password.

Also, use the root certificate to sign intermediate certificates instead of using the root certificate to sign client certificates directly.

 <expand on this with explanation of why this is the case>

Depending on the type of service, the root certificate (or preferably, an intermediate certificate signed by the private key of the root certificate), must be uploaded to the server, where it will be used to authenticate the certificate that the client presents during the TLS handshake.

To generate password-protected private key for the root certificate, run the command below.

.. code-block:: console

   openssl genrsa -des3 -out test-only.root.ca.key 4096

The password must be entered and confirmed when prompted.
If you do not prefer to encrypt and protect your private key with a password, you can omit the ``-des3`` option.

The next step is to create root certificate using the generated private key.
The password of the key must be entered when prompted.

The ``-nodes`` option indicates that the certificate itself will not be encrypted and password-protected.
Omit this option to encrypt the certificate.

.. code-block:: console

   openssl req -x509 -nodes -sha256 -days 365 -key test-only.root.ca.key -out test-only.root.ca.pem

Verification certificate
************************

When uploading the root or intermediate certificate to a cloud service, it is common that a verification certificate is required.
The cloud service might then provide a verification code or string that will be used as the part of a new certificate signed by the private key of the root certificate.

When the signed verification certificate is uploaded to the cloud service, it is confirmed that the user has the private root key.
The verification code can be entered when creating the certificate signing request, usually in the common name entry of the certificate.
This must be done as per the instructions of the cloud service.

Complete the following steps to generate and sign the verification certificate:

1. Create private key for verification certificate by running the following command:

   .. code-block:: console

      openssl genrsa -out verification.key 2048

#. Create certificate signing request for the verification certificate and to provide the verification code according to instructions from your service by running the following command:

   .. code-block:: console

      openssl req -new -key verification.key -out verification.csr

#. Sign the verification certificate with the root private key:

   .. code-block:: console

      openssl x509 -req -sha256 -days 365 -CAcreateserial \
             -in verification.csr -out verification.pem \
             -CA test-only.root.ca.pem -CAkey test-only.root.ca.key

Client certificate
******************

Complete the following steps to generate and sign the private key for the device:

1. Generate the private key for the device by running the following command:

   .. code-block:: console

      openssl genrsa -out my-device.key 2048

#. Create certificate signing request for the device:

   .. code-block:: console

      openssl req -new -key my-device.key -out my-device.csr   

#. Sign device certificate:

   .. code-block:: console

      
      openssl x509 -req -sha256 -days 365 -CAcreateserial \
                   -in my-device.csr -out my-device.pem \
                   -CA test-only.root.ca.pem -CAkey test-only.root.ca.key
