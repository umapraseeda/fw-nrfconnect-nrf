.. _ug_tls_est_sec_conn:

Establishing a secure connection
################################

After establishing a TCP connection, the client can negotiate for a TLS connection with the server.
This negotiation, which is called a TLS handshake, is always initiated by the client.
During the TLS handshake, messages are exchanged between the server and the client.
The client and the server agree on parameters required for the TLS connection, and send information through the messages exchanged during the TLS handshake.
This information is used to verify the identities of the client and the server.
Following are some of the most important data that are shared and agreed upon during the TLS handshake:

* Cipher suite used for key exchange, encryption, and signing, and the parameters that are needed for these algorithms.
* Server certificate sent from the server. Used by the client to verify the identity of the server.
* Client certificate sent from the client to the server. Used by the server to verify the identity of the client. The client certificate is not part of all TLS handshakes.

If the TLS handshake succeeds, the subsequent communication is encrypted using keys that are known only to the client and the server.
Most commonly, these keys are generated on each side based on parts of information that is shared in the handshake.

If the handshake fails, the connection is terminated.
