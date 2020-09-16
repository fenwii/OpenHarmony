# HdfDeviceIoClient<a name="EN-US_TOPIC_0000001054879532"></a>

## **Overview**<a name="section1912604495093530"></a>

**Related Modules:**

[Core](core.md)

**Description:**

Defines the client object structure of the I/O service. 

This structure describes the invoker information of the I/O servcie.

**Since:**

1.0

## **Summary**<a name="section1276896680093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1510062269093530"></a>
<table><thead align="left"><tr id="row1906562505093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p667230729093530"><a name="p667230729093530"></a><a name="p667230729093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p110881848093530"><a name="p110881848093530"></a><a name="p110881848093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1932942023093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541284460093530"><a name="p541284460093530"></a><a name="p541284460093530"></a><a href="hdfdeviceioclient.md#a49e622cbc385f17b3800580157558031">device</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p921367322093530"><a name="p921367322093530"></a><a name="p921367322093530"></a>struct <a href="hdfdeviceobject.md">HdfDeviceObject</a> * </p>
</td>
</tr>
<tr id="row160462647093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087352196093530"><a name="p1087352196093530"></a><a name="p1087352196093530"></a><a href="hdfdeviceioclient.md#aef6d8dd955ee8305554d89d1c64486c7">priv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p558418362093530"><a name="p558418362093530"></a><a name="p558418362093530"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section872830340093530"></a>

## **Field Documentation**<a name="section436280893093530"></a>

## device<a name="a49e622cbc385f17b3800580157558031"></a>

```
struct [HdfDeviceObject](hdfdeviceobject.md)* HdfDeviceIoClient::device
```

 **Description:**

Device object corresponding to the client object 

## priv<a name="aef6d8dd955ee8305554d89d1c64486c7"></a>

```
void* HdfDeviceIoClient::priv
```

 **Description:**

Private data of the client object. The driver can use  **priv**  to bind the internal data with the client. 

