# HdfDevEventlistener<a name="EN-US_TOPIC_0000001055358108"></a>

## **Overview**<a name="section1354886981093530"></a>

**Related Modules:**

[Core](core.md)

**Description:**

Defines a driver event listener object. 

**Since:**

1.0

## **Summary**<a name="section1141881144093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table863373559093530"></a>
<table><thead align="left"><tr id="row2080041501093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p564551246093530"><a name="p564551246093530"></a><a name="p564551246093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1720531512093530"><a name="p1720531512093530"></a><a name="p1720531512093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1820004472093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1151442397093530"><a name="p1151442397093530"></a><a name="p1151442397093530"></a><a href="hdfdeveventlistener.md#ab242c593bb5f92f775087c86b7b6bba4">callBack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229804691093530"><a name="p229804691093530"></a><a name="p229804691093530"></a><a href="core.md#gae314b850ba4b0927007038cf8cc32580">OnEventReceived</a> </p>
</td>
</tr>
<tr id="row694112990093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1375664416093530"><a name="p1375664416093530"></a><a name="p1375664416093530"></a><a href="hdfdeveventlistener.md#a4cf02802e185796f2d373f7c938f8e24">listNode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1757990560093530"><a name="p1757990560093530"></a><a name="p1757990560093530"></a>struct <a href="dlisthead.md">DListHead</a> </p>
</td>
</tr>
<tr id="row747875971093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p974264585093530"><a name="p974264585093530"></a><a name="p974264585093530"></a><a href="hdfdeveventlistener.md#a518808817b32cbb1e70a96f7009cbf5f">priv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527636839093530"><a name="p527636839093530"></a><a name="p527636839093530"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section481429423093530"></a>

## **Field Documentation**<a name="section1585454478093530"></a>

## callBack<a name="ab242c593bb5f92f775087c86b7b6bba4"></a>

```
[OnEventReceived](core.md#gae314b850ba4b0927007038cf8cc32580) HdfDevEventlistener::callBack
```

 **Description:**

Callback invoked when the monitored device reports an event 

## listNode<a name="a4cf02802e185796f2d373f7c938f8e24"></a>

```
struct [DListHead](dlisthead.md) HdfDevEventlistener::listNode
```

 **Description:**

Intrusive list node used by the HDF to manage listeners. You can ignore this node. 

## priv<a name="a518808817b32cbb1e70a96f7009cbf5f"></a>

```
void* HdfDevEventlistener::priv
```

 **Description:**

Private data of the listener, which is passed as the first input parameter in  **callback** 

