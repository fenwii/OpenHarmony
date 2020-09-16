# Application Security<a name="EN-US_TOPIC_0000001052170788"></a>

## Mechanism<a name="section18423515354"></a>

-   Application signature management

    After developing and debugging an OpenHarmony application, sign the application installation package using a private key, which matches a public key. Generally, the OEM generates a public/private key pair, presets the public key in the device, and stores the private key on a local server that is not connected to the Internet to prevent private key leakage. After you finish developing an application, you can use an external device \(such as a USB flash drive\) to upload the installation package to the server where the private key is stored, calculate the signature, and download the signature to the external device. During application installation, the hash value of the bundle is calculated using the SHA-256 algorithm. The hash value, together with the signature and preset public key, is used for authentication. The application can be installed only after the authentication is successful.

    In addition, the application source must be verified to ensure that the application is from a valid developer. As a developer, you must apply for a development certificate and use it to sign the application you have developed. During application installation, the upper-level certificate stored on the device is used to verify the signature to ensure validity of the developer.

-   Application permission control

    OpenHarmony allows users to install third-party applications and controls calls made by third-party applications to sensitive permissions. When developing an application, you need to declare the sensitive permissions that the application may invoke in the  **profile.json**  file. The permissions include static and dynamic ones. Static permissions need to be registered during application installation, and dynamic permissions can be invoked only upon user authorization. Authorization modes include system settings, manual authorization by applications, and others. In addition, application signature control is used to ensure that the application installation package has been confirmed by the device vendor.

    **Table  1**  OpenHarmony system permissions

    <a name="table1936715265268"></a>
    <table><thead align="left"><tr id="row736832612616"><th class="cellrowborder" valign="top" width="40.574057405740575%" id="mcps1.2.4.1.1"><p id="p19859181913610"><a name="p19859181913610"></a><a name="p19859181913610"></a><strong id="b13859919203615"><a name="b13859919203615"></a><a name="b13859919203615"></a><span id="text1855471020132"><a name="text1855471020132"></a><a name="text1855471020132"></a>OpenHarmony</span> System Permission</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="23.052305230523054%" id="mcps1.2.4.1.2"><p id="p1985961983610"><a name="p1985961983610"></a><a name="p1985961983610"></a><strong id="b927316391599"><a name="b927316391599"></a><a name="b927316391599"></a>Authorization Mode</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="36.37363736373638%" id="mcps1.2.4.1.3"><p id="p78592196368"><a name="p78592196368"></a><a name="p78592196368"></a><strong id="b238034711910"><a name="b238034711910"></a><a name="b238034711910"></a>Description</strong></p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row2036892662618"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p196912621513"><a name="p196912621513"></a><a name="p196912621513"></a>ohos.permission.LISTEN_BUNDLE_CHANGE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p158591919143612"><a name="p158591919143612"></a><a name="p158591919143612"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p138591019133617"><a name="p138591019133617"></a><a name="p138591019133617"></a>Allows an application to listen for application changes.</p>
    </td>
    </tr>
    <tr id="row836872652610"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p12859141903614"><a name="p12859141903614"></a><a name="p12859141903614"></a>ohos.permission.GET_BUNDLE_INFO</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p73429411292"><a name="p73429411292"></a><a name="p73429411292"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p486021918369"><a name="p486021918369"></a><a name="p486021918369"></a>Allows an application to obtain application information.</p>
    </td>
    </tr>
    <tr id="row143694264267"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p1386031918365"><a name="p1386031918365"></a><a name="p1386031918365"></a>ohos.permission.INSTALL_BUNDLE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p5356164112915"><a name="p5356164112915"></a><a name="p5356164112915"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p1786016192367"><a name="p1786016192367"></a><a name="p1786016192367"></a>Allows an application to install applications.</p>
    </td>
    </tr>
    <tr id="row1836942652617"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p178601196361"><a name="p178601196361"></a><a name="p178601196361"></a>ohos.permission.CAMERA</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p123691246291"><a name="p123691246291"></a><a name="p123691246291"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p18860151923618"><a name="p18860151923618"></a><a name="p18860151923618"></a>Allows an application to use the camera to take photos and record videos at any time.</p>
    </td>
    </tr>
    <tr id="row23691426132616"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p586011195362"><a name="p586011195362"></a><a name="p586011195362"></a>ohos.permission.MODIFY_AUDIO_SETTINGS</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p14868849111715"><a name="p14868849111715"></a><a name="p14868849111715"></a>system_grant (static permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p6860121943619"><a name="p6860121943619"></a><a name="p6860121943619"></a>Allows an application to modify global audio settings, such as the volume and speaker for output.</p>
    </td>
    </tr>
    <tr id="row83692026202610"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p1686071913363"><a name="p1686071913363"></a><a name="p1686071913363"></a>ohos.permission.READ_MEDIA</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p1837524122914"><a name="p1837524122914"></a><a name="p1837524122914"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p118604196369"><a name="p118604196369"></a><a name="p118604196369"></a>Allows an application to read users' favorite videos.</p>
    </td>
    </tr>
    <tr id="row0369192616265"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p2807144613213"><a name="p2807144613213"></a><a name="p2807144613213"></a>ohos.permission.MICROPHONE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p113782462914"><a name="p113782462914"></a><a name="p113782462914"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p13860119103612"><a name="p13860119103612"></a><a name="p13860119103612"></a>Allows an application to use the microphone for audio recording at any time.</p>
    </td>
    </tr>
    <tr id="row626918467266"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p1860181943619"><a name="p1860181943619"></a><a name="p1860181943619"></a>ohos.permission.WRITE_MEDIA</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p13381442297"><a name="p13381442297"></a><a name="p13381442297"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p9860919163615"><a name="p9860919163615"></a><a name="p9860919163615"></a>Allows an application to write users' favorite music.</p>
    </td>
    </tr>
    <tr id="row6270164602610"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p1326132832215"><a name="p1326132832215"></a><a name="p1326132832215"></a>ohos.permission.DISTRIBUTED_DATASYNC</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p4861101915365"><a name="p4861101915365"></a><a name="p4861101915365"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p15861161973614"><a name="p15861161973614"></a><a name="p15861161973614"></a>Allows an application to manage distributed data transmission.</p>
    </td>
    </tr>
    <tr id="row62701646182614"><td class="cellrowborder" valign="top" width="40.574057405740575%" headers="mcps1.2.4.1.1 "><p id="p15247193132317"><a name="p15247193132317"></a><a name="p15247193132317"></a>com.huawei.permission.DISTRIBUTED_VIRTUALDEVICE</p>
    </td>
    <td class="cellrowborder" valign="top" width="23.052305230523054%" headers="mcps1.2.4.1.2 "><p id="p1081717542913"><a name="p1081717542913"></a><a name="p1081717542913"></a>user_grant (dynamic permission)</p>
    </td>
    <td class="cellrowborder" valign="top" width="36.37363736373638%" headers="mcps1.2.4.1.3 "><p id="p11861119123617"><a name="p11861119123617"></a><a name="p11861119123617"></a>Allows an application to use distributed virtualization features.</p>
    </td>
    </tr>
    </tbody>
    </table>


## Recommended Practices<a name="section1959128183614"></a>

When developing an application, determine what permissions your application needs and register the permissions in the  **profile.json**  file. Sign the application to ensure that the devices on which the application will be installed can verify its integrity and source.

