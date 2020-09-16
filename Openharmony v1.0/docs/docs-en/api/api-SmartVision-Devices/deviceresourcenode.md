# DeviceResourceNode<a name="EN-US_TOPIC_0000001054598157"></a>

## **Overview**<a name="section2026262039093530"></a>

**Related Modules:**

[DriverConfig](driverconfig.md)

**Description:**

Defines a tree node in the configuration tree. 

The tree node information includes the node name, unique node ID, node attributes, parent node, child nodes, and sibling nodes. 

## **Summary**<a name="section2083342424093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table977610610093530"></a>
<table><thead align="left"><tr id="row1333611540093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2015307058093530"><a name="p2015307058093530"></a><a name="p2015307058093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1120460249093530"><a name="p1120460249093530"></a><a name="p1120460249093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row564285136093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p485907697093530"><a name="p485907697093530"></a><a name="p485907697093530"></a><a href="deviceresourcenode.md#a991fdfa13e2af8b63c2506d9ed31fc0b">name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1286895611093530"><a name="p1286895611093530"></a><a name="p1286895611093530"></a>const char * </p>
</td>
</tr>
<tr id="row1207950926093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p400245931093530"><a name="p400245931093530"></a><a name="p400245931093530"></a><a href="deviceresourcenode.md#a133894c208928b8ade08efb53beca314">hashValue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268184540093530"><a name="p268184540093530"></a><a name="p268184540093530"></a>uint32_t </p>
</td>
</tr>
<tr id="row322436001093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1099006682093530"><a name="p1099006682093530"></a><a name="p1099006682093530"></a><a href="deviceresourcenode.md#a7da5b6d00ceb2cd33d881a678bdb262b">attrData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p421392153093530"><a name="p421392153093530"></a><a name="p421392153093530"></a>struct <a href="deviceresourceattr.md">DeviceResourceAttr</a> * </p>
</td>
</tr>
<tr id="row1779169561093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390915533093530"><a name="p1390915533093530"></a><a name="p1390915533093530"></a><a href="deviceresourcenode.md#a765c15b3be1bfb1178173e1ed0df4062">parent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2116158528093530"><a name="p2116158528093530"></a><a name="p2116158528093530"></a>struct <a href="deviceresourcenode.md">DeviceResourceNode</a> * </p>
</td>
</tr>
<tr id="row1912312184093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1682661094093530"><a name="p1682661094093530"></a><a name="p1682661094093530"></a><a href="deviceresourcenode.md#ae6104929f3cd35e811975ada3005fca9">child</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45534946093530"><a name="p45534946093530"></a><a name="p45534946093530"></a>struct <a href="deviceresourcenode.md">DeviceResourceNode</a> * </p>
</td>
</tr>
<tr id="row595349807093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p57216953093530"><a name="p57216953093530"></a><a name="p57216953093530"></a><a href="deviceresourcenode.md#a484324bd4df5f2f9998ed0d58222e5ba">sibling</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1470962291093530"><a name="p1470962291093530"></a><a name="p1470962291093530"></a>struct <a href="deviceresourcenode.md">DeviceResourceNode</a> * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1560046980093530"></a>

## **Field Documentation**<a name="section109451992093530"></a>

## attrData<a name="a7da5b6d00ceb2cd33d881a678bdb262b"></a>

```
struct [DeviceResourceAttr](deviceresourceattr.md)* DeviceResourceNode::attrData
```

 **Description:**

Pointer to the node attributes 

## child<a name="ae6104929f3cd35e811975ada3005fca9"></a>

```
struct [DeviceResourceNode](deviceresourcenode.md)* DeviceResourceNode::child
```

 **Description:**

Pointer to a child node 

## hashValue<a name="a133894c208928b8ade08efb53beca314"></a>

```
uint32_t DeviceResourceNode::hashValue
```

 **Description:**

Unique ID of a node 

## name<a name="a991fdfa13e2af8b63c2506d9ed31fc0b"></a>

```
const char* DeviceResourceNode::name
```

 **Description:**

Pointer to the node name 

## parent<a name="a765c15b3be1bfb1178173e1ed0df4062"></a>

```
struct [DeviceResourceNode](deviceresourcenode.md)* DeviceResourceNode::parent
```

 **Description:**

Pointer to the parent node 

## sibling<a name="a484324bd4df5f2f9998ed0d58222e5ba"></a>

```
struct [DeviceResourceNode](deviceresourcenode.md)* DeviceResourceNode::sibling
```

 **Description:**

Pointer to a sibling node 

