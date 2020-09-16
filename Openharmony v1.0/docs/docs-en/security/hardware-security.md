# Hardware Security<a name="EN-US_TOPIC_0000001051930809"></a>

## Mechanism<a name="section1312953842210"></a>

-   Boot root of trust

    OpenHarmony devices use the public key infrastructure \(PKI\) to protect software integrity and ensure that the software source is valid and the software is not tampered with.

    In the device boot process, software signature verification is performed at each phase to form a secure boot chain. If signature verification fails at any phase, the device boot will be terminated. The hardware or software entity that initially performs signature verification in the secure boot chain is the boot root of trust. It must be valid and should not be tampered with. The boot root of trust can be a built-in code segment in the read-only memory \(ROM\). This code segment is written in the chip during the chip manufacturing and cannot be modified later. When the device is powered on and initialized, this code segment is executed first and used to verify software signatures.

    When you use the code for signature verification, ensure the validity of the PKI public keys. OpenHarmony devices use a storage medium such as eFUSE and one-time password \(OTP\) to store the public keys \(for example, their hash values\) and guarantee their validity. A public key is usually programed into the eFuse or OTP of a device during device manufacturing.

-   Hardware-isolated trusted environment

    The hardware-isolated trusted environment complies with the design concept of the trusted computing system. There is a clear boundary between the trusted environment and untrusted one. OpenHarmony devices protect core sensitive data in the trusted environment. Even if OS vulnerabilities in the untrusted environment are exploited, sensitive data in the trusted environment is secure.

    The trusted environment of OpenHarmony devices is built based on a hardware security isolation mechanism. The chip isolation mechanism varies slightly on different OpenHarmony devices, and the most common mechanism is Arm TrustZone. On some RISC-V chip platforms, independent security cores may also be used to build a trusted environment.

    A specific, simplified OS iTrustee lite runs in the trusted environment to manage resources and schedule tasks in the environment and provide security services for OpenHarmony devices. Key management and data security are the most common security services in the trusted environment. A device has a unique hardware root key in the eFuse/OTP. Based on this root key and service context, the trusted environment generates multiple keys that provide key management and data encryption/decryption services for applications. During their whole lifecycle, core keys of devices stay in the trusted environment. The trusted environment also provides security services such as identity authentication, system status monitoring, and secure data storage to enhance device security.

-   Hardware key engine

    Cryptography is the basis of information security. Data encryption/decryption requires high efficiency and security of computing devices. Hardware encryption/decryption technologies use computer hardware to assist or even replace software to encrypt or decrypt data. Hardware-based encryption/decryption is more efficient and secure than software-based encryption/decryption.

    Since some dedicated hardware resources are used for data encryption/decryption, the CPU can concurrently execute other computing tasks, which greatly improves performance and reduces the CPU load. In addition, a well-designed hardware key engine protects keys from leak even if the software is cracked and even defends against electromagnetic and radiation attacks from physical channels.

    OpenHarmony devices support the hardware key engine, which allows OpenHarmony to perform computing tasks such as data encryption and decryption, certificate signature verification, and hash value calculation. The hardware key engine supports popular algorithms such as Advanced Encryption Standard \(AES\) and Rivest-Shamir-Adleman \(RSA\).


## Recommended Practices<a name="section37901319112311"></a>

-   The boot root of trust consists of a built-in code segment in the chip and the root key of the device. The root of trust is written into the chip during manufacturing and cannot be modified in the device lifecycle. It is used to verify software certificates in the device boot process. The root key is the public key matching the private key of the device certificate signature. The private key is maintained on the PKI signature server and the public key is written to the device. To prevent attackers from tampering with the public key to bypass signature authentication, you can write the public key to media such as fuses on OpenHarmony devices. Considering that the fuse space is limited, you can store only the hash value of the public key in the fuse and verify the validity of the public key using the boot code.
-   Generally, a trusted execution environment \(TEE\) is built based on the Arm TrustZone technology, and can also adopt other isolation mechanisms, such as TrustZone-M and independent security cores, depending on the device form. A TEE OS must be deployed in the TEE to manage resources and schedule tasks. OpenHarmony provides iTrustee as the TEE OS. You can develop and deploy security services based on iTrustee.

    Not all OpenHarmony devices need to support the TEE, for example, some devices with thin resources that run less sensitive services may not need the TEE. You can choose whether to support the TEE and how to implement the TEE based on service requirements.

-   The hardware key engine must provide key algorithms related to true random numbers, public keys, symmetric keys, and hash values. By deploying required drivers in OpenHarmony, you can provide unified key management and key algorithms for applications.

