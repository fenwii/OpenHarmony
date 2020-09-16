# Security Guidelines<a name="EN-US_TOPIC_0000001052530786"></a>

## Overview<a name="section1521410017353"></a>

OpenHarmony is an open OS that allows you to easily develop services and applications. It provides an execution environment to ensure security of application data and user data.

This environment combines chip security and system security features with upper-layer security services to secure hardware, the system, data, device interconnection, applications, and updates.

**Figure  1**  Security assurance framework<a name="fig1045114523114"></a>  


![](figures/en-us_image_0000001054058325.png)

## Hardware Security<a name="section2558121318351"></a>

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

## System Security<a name="section87802111361"></a>

## Mechanism<a name="section1654963052914"></a>

For device with 128 KB to 128 MB of memory, the HarmonyOS lite kernel is recommended.

-   Process isolation

    Process isolation prevents processes from reading and writing memory data of each other. Generally, virtual address space mapping is used for process isolation. The virtual addresses of two processes are mapped to physical address segments using the memory management unit \(MMU\). In this way, the non-shared memory data that can be accessed by one of the two processes through the virtual address is inaccessible to the other process.

    Due to limited resources, OpenHarmony adopts different mechanisms for kernel-level and user-level processes. All kernel-level processes share the same VMM space, that is, kernel-level processes are not isolated from each other. When the OS is booted, two basic kernel-level processes KProcess and KIdle are created. KProcess is the root process of kernel-level process, and KIdle is the subprocess of KProcess. Each user-level process has its own VMM space that is invisible to other processes, and user-level processes are isolated from each other.

-   Discretionary access control

    Discretionary access control \(DAC\) means that the file owner determines access permissions of other roles. There are three granularities of permission control: user, group, and other \(UGO\). The file owner can classify any user into one of the three dimensions and adopt a control policy to perform DAC permission verification.

    DAC depends on the attributes of processes, such as the UID and GID, which are used as feature IDs during file creation and access. When creating a file, the creator writes its UID into the file. When a file is accessed, the UID is used for classifying the file.

    Each application has a UID. When creating a file, an application adds its UID to the metadata of the file and sets permissions of the user, group, and other. When an application tries to access the file, the UID and permissions in the metadata of the file are used to verify the application UID.

    The following figure shows how DAC works when a process accesses a file. The DAC first matches the process UID with the file UID, and then the process GID with the file GID. If the UID and GID both fail to match, DAC checks the  **other**  attribute of the file to determine whether the process is allowed to read, write, or execute the file. In addition, the system supports a privileged capability that is not subject to DAC mechanism \(read, write, and execute\) and can access files directly. Services with high permissions \(such as system services\) can manage files of applications with low permissions \(such as third-party applications\).

    **Figure  2**  How DAC works<a name="fig77437429496"></a>  
    

    ![](figures/en-us_image_0000001055079849.png)

-   Capability mechanism

    The capability mechanism is a subdivision of the root permission. A multi-user computer system usually has a special role that has all system permissions, that is, the system administrator with the root permission. OpenHarmony needs to support kernels of the third-party application ecosystem, and privileged access to the system must be controlled. The system needs to restrict privileged system calls made by users to access the kernel. Only some applications with high-level permissions are allowed to perform privileged operations. To be specific, the kernel spawns the first user program INIT that has all privileged permissions. Then INIT starts other application framework services and retains only privileged permissions necessary for each application. When an application requests to call a privileged API, the kernel checks whether the application has the permission to access the API based on the process ID.

-   Secure boot

    Secure boot is the basis of system security. A digital signature and integrity verification mechanism is used to verify the integrity and validity of software at each layer, starting from the boot root of trust in the chip. This ensures that a correct and valid OS is booted, preventing attackers from tampering with or implanting system software and providing a secure, basic running environment.

    The chip does not need to be verified after it is powered on because the on-chip ROM code cannot be modified. The on-chip ROM verifies the bootloader based on the public key hash value which is calculated using the asymmetric algorithm in eFuse. The verification is performed based on the hardware trust root and is fully trusted. The bootloader that passes this verification is deemed to be trusted for subsequent use. This is the process of constructing a trust chain. Bootloader initializes the execution environment, including initializing the double data rate \(DDR\) and reading and writing the flash memory, to prepare for loading modules and executing more complex logic. After the bootloader is initialized, it verifies the integrity of the X.509 certificate and verifies image packages \(**kernel.bin**,  **teeOS.bin**, and  **rootfs.bin**\) using the public key of the X.509 certificate.


## Recommended Practices<a name="section45821048173613"></a>

-   DAC and the capability mechanism are used to control who can access resources. It is recommended that the minimum permissions are granted.
-   Secure boot must be enabled, and the trusted root must be in the chip and cannot be modified. In addition, you must consider the impact of secure upgrade \(if available\) on secure boot, that is, the signature or hash value of an image file must be updated after a secure upgrade.

## Data Security<a name="section2468927364"></a>

## Mechanism<a name="section11192175813293"></a>

Huawei Universal Keystore Service \(HUKS\) provides certificate management, key management, secure storage, and key authentication services. For OpenHarmony, it mainly provides key management and secure storage, as well as the basic device certification feature for HiChain \(device certification platform\). The following figure shows the functions of HUKS

**Figure  3**  HUKS functions<a name="fig34395461507"></a>  


![](figures/en-us_image_0000001054599869.png)

The following algorithms are supported:

Authentication and encryption: AES-128/192/256-GCM

Signature verification: ED25519

Key negotiation: X25519

Message authentication: HMAC-SHA256/512

Data digest: SHA256/512

HUKS has the following restrictions:

-   Secure storage of keys: Keys must be stored in a secure area and cannot be modified. When factory settings are restored, preset keys are not deleted.
-   Key access security: OpenHarmony stores different data of an application separately to implement data isolation in the application, and includes the UID and process ID in the parameter structure to implement data isolation between different applications.
-   Concurrent access is not supported, that is, multiple applications cannot invoke HUKS simultaneously. As HUKS is a single library, resource exclusion is not a concern. If multiple applications need to use HUKS, each of them needs to connect to a HUKS library and pass a path for storing data. Data is stored in the directory of each application.

## Recommended Practices<a name="section174640713306"></a>

To use the device certification function, it is recommended that you use HiChain to interconnect with HUKS. HUKS provides applications such as HiChain with key generation, import, export, encryption/decryption, storage, and destruction, certificate import and query, and secret information storage.

## Device Interconnection Security<a name="section26153183616"></a>

To transmit user data securely between devices, ensure that the devices are trusted by each other. A trust relationship and a secure data transmission channel must be established between the devices. This section describes how an IoT controller and IoT device establish a trust relationship. The following figure shows how an IoT controller and an IoT device establish a trust relationship.

**Figure  4**  How an IoT controller and an IoT device establish a trust relationship<a name="fig1939920919510"></a>  
![](figures/how-an-iot-controller-and-an-iot-device-establish-a-trust-relationship.png "how-an-iot-controller-and-an-iot-device-establish-a-trust-relationship")

-   **IoT device interconnection security**

    A trust relationship can be established between an IoT device that runs OpenHarmony \(such as an AI speaker, smart home device, and wearable\) and an IoT controller. Encrypted user data is transmitted between the IoT device and IoT controller through a secure connection.


-   **IoT service identifier of the IoT controller**

    An IoT controller generates different identifiers for different IoT device management services to isolate these services. The identifier can be used for authentication and communication between an IoT controller and an IoT device. It is an Ed25519 public/private key pair generated using the elliptic curve cryptography.


-   **IoT device identifier**

    An IoT device can generate its own device identifier for communicating with the IoT controller. It is also an Ed25519 public/private key pair generated using elliptic curve cryptography, with the private key stored on the IoT device. Each time the device is restored to factory settings, the public/private key pair will be reset.

    The identifier can be used for secure communication between the IoT controller and IoT device. After the devices exchange the service identifier or device identifier, they can negotiate the key and establish a secure communication channel.


-   **P2P trusted binding between devices**

    When an IoT controller and an IOT device establish a trust relationship, they exchange identifiers.

    During this process, the user needs to enter or scan the PIN provided by the IoT device on the IoT controller. PIN is either dynamically generated if the IoT device has a screen, or preset by the manufacturer if it does not have a screen. A PIN can be a number or a QR code. Then the IoT controller and IoT device perform authentication and session key exchange based on password authenticated key exchange \(PAKE\), and use the session key to encrypt the channel for exchanging identity public keys.


-   **Secure communication between the IoT controller and IoT device**

    When an IoT controller and an IoT device communicate with each other after establishing a trust relationship, they authenticate each other by using the locally stored identity public key of the peer. Bidirectional identity authentication and session key exchange are performed using the Station-to-Station \(STS\) protocol during each communication. The session key is used to encrypt the data transmission channel between the devices.


## Application Security<a name="section852593153614"></a>

## Mechanism<a name="section12125105014377"></a>

-   Application signature management

    After developing and debugging an OpenHarmony application, sign the application installation package using a private key, which matches a public key. Generally, the OEM generates a public/private key pair, presets the public key in the device, and stores the private key on a local server that is not connected to the Internet to prevent private key leakage. After you finish developing an application, you can use an external device \(such as a USB flash drive\) to upload the installation package to the server where the private key is stored, calculate the signature, and download the signature to the external device. During application installation, the hash value of the bundle is calculated using the SHA-256 algorithm. The hash value, together with the signature and preset public key, is used for authentication. The application can be installed only after the authentication is successful.

    In addition, the application source must be verified to ensure that the application is from a valid developer. As a developer, you must apply for a development certificate and use it to sign the application you have developed. During application installation, the upper-level certificate stored on the device is used to verify the signature to ensure validity of the developer.

-   Application permission control

    OpenHarmony allows users to install third-party applications and controls calls made by third-party applications to sensitive permissions. When developing an application, you need to declare the sensitive permissions that the application may invoke in the  **profile.json**  file. The permissions include static and dynamic ones. Static permissions need to be registered during application installation, and dynamic permissions can be invoked only upon user authorization. Authorization modes include system settings, manual authorization by applications, and others. In addition, application signature control is used to ensure that the application installation package has been confirmed by the device vendor.

    **Table  1**  OpenHarmony system permissions

    <a name="table17172125003717"></a>
    <table><thead align="left"><tr id="row131699507374"><th class="cellrowborder" valign="top" width="40.574057405740575%" id="mcps1.2.4.1.1"><p id="p5169105013374"><a name="p5169105013374"></a><a name="p5169105013374"></a><strong id="b7169115015374"><a name="b7169115015374"></a><a name="b7169115015374"></a><span id="text916965043710"><a name="text916965043710"></a><a name="text916965043710"></a>OpenHarmony</span> System Permission</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="23.052305230523054%" id="mcps1.2.4.1.2"><p id="p1916915509373"><a name="p1916915509373"></a><a name="p1916915509373"></a><strong id="b13169650193711"><a name="b13169650193711"></a><a name="b13169650193711"></a>Authorization Mode</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="36.37363736373638%" id="mcps1.2.4.1.3"><p id="p7169125083714"><a name="p7169125083714"></a><a name="p7169125083714"></a><strong id="b316955018372"><a name="b316955018372"></a><a name="b316955018372"></a>Description</strong></p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row2170165019374"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p616905083715"><a name="p616905083715"></a><a name="p616905083715"></a>ohos.permission.LISTEN_BUNDLE_CHANGE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p1116975013371"><a name="p1116975013371"></a><a name="p1116975013371"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p416915505376"><a name="p416915505376"></a><a name="p416915505376"></a>Allows an application to listen for application changes.</p>
    </td>
    </tr>
    <tr id="row61701250123714"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p9170165014377"><a name="p9170165014377"></a><a name="p9170165014377"></a>ohos.permission.GET_BUNDLE_INFO</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p1217012507372"><a name="p1217012507372"></a><a name="p1217012507372"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p181704502378"><a name="p181704502378"></a><a name="p181704502378"></a>Allows an application to obtain application information.</p>
    </td>
    </tr>
    <tr id="row1617035014373"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p1517065012379"><a name="p1517065012379"></a><a name="p1517065012379"></a>ohos.permission.INSTALL_BUNDLE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p18170155014374"><a name="p18170155014374"></a><a name="p18170155014374"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p14170750163714"><a name="p14170750163714"></a><a name="p14170750163714"></a>Allows an application to install applications.</p>
    </td>
    </tr>
    <tr id="row171708506378"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p4170155093718"><a name="p4170155093718"></a><a name="p4170155093718"></a>ohos.permission.CAMERA</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p111704508372"><a name="p111704508372"></a><a name="p111704508372"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p16170050173713"><a name="p16170050173713"></a><a name="p16170050173713"></a>Allows an application to use the camera to take photos and record videos at any time.</p>
    </td>
    </tr>
    <tr id="row01711150173720"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p3170185083713"><a name="p3170185083713"></a><a name="p3170185083713"></a>ohos.permission.MODIFY_AUDIO_SETTINGS</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p141701950153710"><a name="p141701950153710"></a><a name="p141701950153710"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p131701850103714"><a name="p131701850103714"></a><a name="p131701850103714"></a>Allows an application to modify global audio settings, such as the volume and speaker for output.</p>
    </td>
    </tr>
    <tr id="row131710500376"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p1517195013372"><a name="p1517195013372"></a><a name="p1517195013372"></a>ohos.permission.READ_MEDIA</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p10171185010378"><a name="p10171185010378"></a><a name="p10171185010378"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p121711350123716"><a name="p121711350123716"></a><a name="p121711350123716"></a>Allows an application to read users' favorite videos.</p>
    </td>
    </tr>
    <tr id="row1171650203714"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p151711850113713"><a name="p151711850113713"></a><a name="p151711850113713"></a>ohos.permission.MICROPHONE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p19171650133716"><a name="p19171650133716"></a><a name="p19171650133716"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p11171250183718"><a name="p11171250183718"></a><a name="p11171250183718"></a>Allows an application to use the microphone for audio recording at any time.</p>
    </td>
    </tr>
    <tr id="row15171105083711"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p11711550123713"><a name="p11711550123713"></a><a name="p11711550123713"></a>ohos.permission.WRITE_MEDIA</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p10171350183710"><a name="p10171350183710"></a><a name="p10171350183710"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p517112501375"><a name="p517112501375"></a><a name="p517112501375"></a>Allows an application to write users' favorite music.</p>
    </td>
    </tr>
    <tr id="row1217211504379"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p131711850173719"><a name="p131711850173719"></a><a name="p131711850173719"></a>ohos.permission.DISTRIBUTED_DATASYNC</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p1317113504377"><a name="p1317113504377"></a><a name="p1317113504377"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p6172105015372"><a name="p6172105015372"></a><a name="p6172105015372"></a>Allows an application to manage distributed data transmission.</p>
    </td>
    </tr>
    <tr id="row13172185053711"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p4172145033712"><a name="p4172145033712"></a><a name="p4172145033712"></a>ohos.permission.DISTRIBUTED_VIRTUALDEVICE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p161729503378"><a name="p161729503378"></a><a name="p161729503378"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p17172105010371"><a name="p17172105010371"></a><a name="p17172105010371"></a>Allows an application to use distributed virtualization features.</p>
    </td>
    </tr>
    </tbody>
    </table>


## Recommended Practices<a name="section1641420155381"></a>

When developing an application, determine what permissions your application needs and register the permissions in the  **profile.json**  file. Sign the application to ensure that the devices on which the application will be installed can verify its integrity and source.

