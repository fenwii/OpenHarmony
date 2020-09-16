# Distributed Remote Startup<a name="EN-US_TOPIC_0000001051071561"></a>

## Overview<a name="section186634310418"></a>

The Distributed Manager Service sets up a distributed service platform in OpenHarmony by using a proxy between the primary and secondary devices. With the Distributed Manager Service, the primary device \(OpenHarmony-powered smart TV\) can start a Feature Ability \(FA\) deployed on the secondary device \(a memory-constrained OpenHarmony device such as an IP camera or a lite wearable\).

For example, if a user presses the  **Remind Me**  button for a TV program on the smart TV, the smart TV will start the corresponding reminder FA on the lite wearable to remind the user when the particular TV program is available.

## Basic Concepts<a name="section982651246"></a>

-   FA

    Feature Ability, representing an ability with a UI for interacting with users


-   Remote startup

    Cross-device FA startup, which is the counterpart of local FA startup


## Available APIs<a name="section125479541744"></a>

The following table describes the API that can be used by smart TVs to remotely start an FA. This API is provided in the  **AbilitySlice**  class. For details, see the Java API reference for OpenHarmony application development.

**Table  1**  API for remotely starting an FA on the distributed network

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="57.38999999999999%" id="mcps1.2.3.1.1"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>Method</p>
</th>
<th class="cellrowborder" valign="top" width="42.61%" id="mcps1.2.3.1.2"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row34145016535"><td class="cellrowborder" valign="top" width="57.38999999999999%" headers="mcps1.2.3.1.1 "><p id="p1682733119213"><a name="p1682733119213"></a><a name="p1682733119213"></a>void startAbility(Want want)</p>
</td>
<td class="cellrowborder" valign="top" width="42.61%" headers="mcps1.2.3.1.2 "><p id="p13562171015712"><a name="p13562171015712"></a><a name="p13562171015712"></a>Remotely starts an FA based on the specified <strong id="b8984536181113"><a name="b8984536181113"></a><a name="b8984536181113"></a>Want</strong> information. If the name of the <strong id="b599520304618"><a name="b599520304618"></a><a name="b599520304618"></a>want</strong> parameter is different from that used in the integrated development environment (IDE), use the parameter name in the IDE.</p>
</td>
</tr>
</tbody>
</table>

**Table  2**  Description of the want parameter

<a name="table02120432364"></a>
<table><thead align="left"><tr id="row172294315361"><th class="cellrowborder" valign="top" width="14.000000000000002%" id="mcps1.2.4.1.1"><p id="p722144318360"><a name="p722144318360"></a><a name="p722144318360"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="17%" id="mcps1.2.4.1.2"><p id="p10227434363"><a name="p10227434363"></a><a name="p10227434363"></a>Type</p>
</th>
<th class="cellrowborder" valign="top" width="69%" id="mcps1.2.4.1.3"><p id="p22284383616"><a name="p22284383616"></a><a name="p22284383616"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row3228436365"><td class="cellrowborder" valign="top" width="14.000000000000002%" headers="mcps1.2.4.1.1 "><p id="p1391227193713"><a name="p1391227193713"></a><a name="p1391227193713"></a>want</p>
</td>
<td class="cellrowborder" valign="top" width="17%" headers="mcps1.2.4.1.2 "><p id="p20993611193719"><a name="p20993611193719"></a><a name="p20993611193719"></a>ohos.aafwk.content.Want</p>
</td>
<td class="cellrowborder" valign="top" width="69%" headers="mcps1.2.4.1.3 "><p id="p10555172211377"><a name="p10555172211377"></a><a name="p10555172211377"></a>When you use <strong id="b1013275220199"><a name="b1013275220199"></a><a name="b1013275220199"></a>startAbility(Want want)</strong> to remotely start an FA, you must first specify the <strong id="b1125035416223"><a name="b1125035416223"></a><a name="b1125035416223"></a>deviceId</strong>, <strong id="b16473135811222"><a name="b16473135811222"></a><a name="b16473135811222"></a>bundleName</strong>, and <strong id="b157931324230"><a name="b157931324230"></a><a name="b157931324230"></a>abilityName</strong> attributes of the target FA in the <strong id="b34832152239"><a name="b34832152239"></a><a name="b34832152239"></a>Want</strong> object.</p>
</td>
</tr>
</tbody>
</table>

## Limitations and Constraints<a name="section1165911177314"></a>

-   The primary device can remotely start an FA of the secondary device, but the secondary device cannot remotely start an FA of the primary device.
-   Before the remote startup, ensure that the two OpenHarmony devices are on the same network segment and can ping each other on the distributed network. Otherwise, the remote startup fails.
-   Currently, only the FAs that have the same public key \(that is, the same Huawei certificate\) can be started between the primary and secondary devices.

## How to Develop<a name="section34171333656"></a>

To enable the primary device \(smart TV\) to start an FA of the secondary device \(assuming that the target FA has been developed\), perform the following steps:

1.  Complete FA development for the smart TV on DevEco Studio.
2.  Obtain the IDs of online secondary devices.

    ```
    // Import the header files required for device selection.
    import ohos.distributedschedule.interwork.DeviceInfo;
    import ohos.distributedschedule.interwork.DeviceManager;
    
    // Obtain the online device list.
    List<DeviceInfo> deviceInfoListOnline = DeviceManager.getDmsDeviceList(DeviceInfo.FLAG_GET_ONLINE_DEVICE);
    String remote_device_id;
    if (deviceInfoListOnline.size() > 0)
    {
        remote_device_id = deviceInfoListOnline[0].GetDeviceId(); // Obtain the ID of the first device in the online device list.
    }
    ```

3.  Create a  **Want**  instance. You should first create an  **ElementName**  object with  **deviceID**,  **bundleName**,  **abilityName**  specified and add this object to the  **Want**  instance. Then, set the multi-device startup flag  **Want.FLAG\_ABILITYSLICE\_MULTI\_DEVICE**  to the  **Want**  instance to enable remote FA startup.

    ```
    // Import related header files.
    import ohos.aafwk.ability.Ability;
    import ohos.aafwk.content.Want;
    import ohos.bundle.ElementName;
    
    // Start the remote FA on the secondary device.
    Want want = new Want(); // Create a Want instance that encapsulates information about the remote FA to start.
    // Use the device ID obtained in step 2 and specify the FA information.
    ElementName name = new ElementName(remote_device_id, "com.huawei.remote_package_name", "remote_class_name"); 
    want.setElement(name); // Add information about the target FA for startup to the Want instance.
    want.setFlags(Want.FLAG_ABILITYSLICE_MULTI_DEVICE); // Set the multi-device startup flag. If this flag is not set, remote FA startup will be unavailable.
    startAbility(want); // Start the specified FA based on the want parameter. If the name of the want parameter is different from that used in the IDE, use the parameter name in the IDE.
    ```


