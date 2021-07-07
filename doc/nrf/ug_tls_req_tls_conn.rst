.. _ug_tls_req_tls_conn:

Requirements for a TLS connection
#################################

For establishing a secure connection, the client and the server must meet some requirements.
This section focuses on the client-side requirements.

A server certificate is mandatory for all TLS connections.

Following are some of the additional common requirements for typical IoT servers like AWS IoT, Azure IoT Hub, and others:

* Client certificate
* Private key of the client

See the documentation on the respective server for information on the exact requirements of certificates and keys.

Server certificate
******************

For nearly all TLS connections, the root certificate of the server must be known to the client.
This is also true in the case of web browsers (that act as clients in a TCP/TLS connection), but mostly the browser includes a bundle of commonly used root certificates hence preventing the need to provide them explicitly.
In the case of embedded platforms, where memory space must be reserved for all the certificates, the root certificate on the server side must be provisioned as and when needed.

It is common that the server sends a chain of certificates in the TLS handshake.
You need not provision the whole chain of certificates to the client, but you need to provision the root certificate that provides the root of trust in the chain.
When the root certificate is provisioned, the client can verify the signatures of the certificates in the chain and confirm that it has connected to the correct peer.
Each certificate in the chain is signed by the previous certificate belonging to the chain.

A closer look at the certificates provides the following information: 

* Common Name (CN) - An example is ``aws.amazon.com``.
* Issuer - The Certificate Authority (CA) that issued and signed a certificate.
* Valid to - The date upto which the certificate is valid.

The signature on each certificate in the chain can be verified by using the information contained in the certificate of the issuer.

The following figure (to be updated) shows the relationship between the certificates in a certificate chain:

.. figure:: images/tls_ug_chain_of_trust_example.png
      :scale: 50 %
      :alt: Chain of trust example


Following are the key concepts of certificate validation:

* A root certificate is defined as a root of trust. It is typically issued by one of the few companies that are widely accepted as the trusted `Certificate authorities <Certificate authority_>`_.

   * The root certificate is signed by the private key that is created alongside the public key that is part of the certificate.

* The signature of the certificates must be verified.

   * The signature algorithm that is used for signing, is part of the certificate.
   * Initially, a hash algorithm (also part of the certificate) is applied to the entire content of the certificate.
   * As the next step, the signature algorithm is applied to the hash, using the private key. The result is a signature that can be decrypted using the public key and compared to a hash of the certificate content.
   * If the decrypted hash and the calculated hash are equal, the integrity of the public key is verified, and it is established that the signature was created using the private key that corresponds to the public key. Hence, the entity that signed the certificate is in possession of the private key of this trusted certificate.

* For the subsequent certificates, the following actions are performed:

   * The signature is created using the private key of the preceding certificate in the chain.
   * The public key of the preceding certificate is used to decrypt and verify the signature.


Client certificate
******************

The client can use the same rule as the server to allow its peer verify its identity against a trusted certificate.
The client certificate is signed by a root CA or intermediate CA that must be uploaded to the server for the verification to succeed.

In contrast to a server certificate, client certificates are often self-signed by manufacturers or other parties.
While this is often the case, you can also purchase certificates from a trusted provider in the same way as it is done in the case of server certificates.

The client certificate must be provisioned to the ``Client certificate`` slot of a security tag.

Client private key
******************

The private key that was used when creating the client certificate, is used to authenticate the client that presents a client certificate.
The client does that by signing a hash of all messages that has been sent during a TLS handshake and sending it to the server.
The server then computes the hash on its side, decrypt the encrypted hash from the client and compare the values.

The private key must be provisioned to the ``Client private key`` slot of the security tag.
If the private key is encrypted, the password must also be provisioned.