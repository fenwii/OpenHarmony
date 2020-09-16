# IPowerEventListener<a name="EN-US_TOPIC_0000001055358112"></a>

## **Overview**<a name="section777723692084836"></a>

**Related Modules:**

[Core](core.md)

**Description:**

Defines the power management functions provided by the HDF for the driver. 

To use the power management mechanism provided by the HDF, implement operations of  **[IPowerEventListener](ipowereventlistener.md)**  and invoke \{@linkHdfDeviceRegisterPowerListener\} to register the operations with the HDF.

**Since:**

1.0

## **Summary**<a name="section148404377084836"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1139214822084836"></a>
<table><thead align="left"><tr id="row2128190757084836"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p992424525084836"><a name="p992424525084836"></a><a name="p992424525084836"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2144368095084836"><a name="p2144368095084836"></a><a name="p2144368095084836"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1538457787084836"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1723737934084836"><a name="p1723737934084836"></a><a name="p1723737934084836"></a><a href="ipowereventlistener.md#ad8501d377d185a998803ad84cacf80d7">Resume</a> )(struct <a href="hdfdeviceobject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p371636822084836"><a name="p371636822084836"></a><a name="p371636822084836"></a>void(* </p>
</td>
</tr>
<tr id="row1309463335084836"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1016947868084836"><a name="p1016947868084836"></a><a name="p1016947868084836"></a><a href="ipowereventlistener.md#a42104ba0f92462db12a13e6b40c40d52">Suspend</a> )(struct <a href="hdfdeviceobject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279061906084836"><a name="p279061906084836"></a><a name="p279061906084836"></a>void(* </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section827948696084836"></a>

## **Field Documentation**<a name="section975064062084836"></a>

## Resume<a name="ad8501d377d185a998803ad84cacf80d7"></a>

```
void(* IPowerEventListener::Resume) (struct [HdfDeviceObject](hdfdeviceobject.md) *deviceObject)
```

 **Description:**

Wakes up the driver device. The driver developer implements the operation. 

## Suspend<a name="a42104ba0f92462db12a13e6b40c40d52"></a>

```
void(* IPowerEventListener::Suspend) (struct [HdfDeviceObject](hdfdeviceobject.md) *deviceObject)
```

 **Description:**

Hibernates the driver device. The driver developer implements the operation. 

