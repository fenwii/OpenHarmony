# HdfDeviceObject<a name="ZH-CN_TOPIC_0000001054479563"></a>

## **Overview**<a name="section1444276924093530"></a>

**Related Modules:**

[Core](Core.md)

**Description:**

Defines the device object. 

This structure is a device object defined by the HDF and is used to store private data and interface information of a device.

**Since:**

1.0

## **Summary**<a name="section1754487750093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table175649058093530"></a>
<table><thead align="left"><tr id="row1875104412093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1551462123093530"><a name="p1551462123093530"></a><a name="p1551462123093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1473070531093530"><a name="p1473070531093530"></a><a name="p1473070531093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row38863795093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544003134093530"><a name="p1544003134093530"></a><a name="p1544003134093530"></a><a href="HdfDeviceObject.md#a4a56df841dab2ca990594daea3ad0107">service</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273525541093530"><a name="p1273525541093530"></a><a name="p1273525541093530"></a>struct <a href="IDeviceIoService.md">IDeviceIoService</a> *&nbsp;</p>
</td>
</tr>
<tr id="row30442975093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1236820803093530"><a name="p1236820803093530"></a><a name="p1236820803093530"></a><a href="HdfDeviceObject.md#aff597a0d23dbf2c6581a4ea6f261e953">property</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p411993944093530"><a name="p411993944093530"></a><a name="p411993944093530"></a>const struct <a href="DeviceResourceNode.md">DeviceResourceNode</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1910064437093530"></a>

## **Field Documentation**<a name="section555642502093530"></a>

## property<a name="aff597a0d23dbf2c6581a4ea6f261e953"></a>

```
const struct [DeviceResourceNode](DeviceResourceNode.md)* HdfDeviceObject::property
```

 **Description:**

Pointer to the private data of the device, which is read by the HDF from the configuration file and transmitted to the driver. 

## service<a name="a4a56df841dab2ca990594daea3ad0107"></a>

```
struct [IDeviceIoService](IDeviceIoService.md)* HdfDeviceObject::service
```

 **Description:**

Pointer to the service interface object, which is registered with the HDF by the driver 

