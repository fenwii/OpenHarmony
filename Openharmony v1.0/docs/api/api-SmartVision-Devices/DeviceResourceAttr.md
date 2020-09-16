# DeviceResourceAttr<a name="ZH-CN_TOPIC_0000001055078135"></a>

## **Overview**<a name="section1323288071093530"></a>

**Related Modules:**

[DriverConfig](DriverConfig.md)

**Description:**

Defines the attributes of a tree node in the configuration tree. 

The tree node attributes are saved in a linked list. The information about each node in the linked list contains the attribute name, attribute value, and pointer that points to the next attribute. 

## **Summary**<a name="section1220095819093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table542265561093530"></a>
<table><thead align="left"><tr id="row1952213772093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p344172980093530"><a name="p344172980093530"></a><a name="p344172980093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p369322893093530"><a name="p369322893093530"></a><a name="p369322893093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row274957916093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p657999526093530"><a name="p657999526093530"></a><a name="p657999526093530"></a><a href="DeviceResourceAttr.md#aadf17a5e450feda1a2ccb043fc94f907">name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p263142317093530"><a name="p263142317093530"></a><a name="p263142317093530"></a>const char *&nbsp;</p>
</td>
</tr>
<tr id="row1792781234093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1277250323093530"><a name="p1277250323093530"></a><a name="p1277250323093530"></a><a href="DeviceResourceAttr.md#a2a9e9a433e8197aaf4863efe468ffdd2">value</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287668714093530"><a name="p287668714093530"></a><a name="p287668714093530"></a>const char *&nbsp;</p>
</td>
</tr>
<tr id="row724779627093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280417370093530"><a name="p280417370093530"></a><a name="p280417370093530"></a><a href="DeviceResourceAttr.md#ac806f1957696cfecba92937d8b25409f">next</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p887153464093530"><a name="p887153464093530"></a><a name="p887153464093530"></a>struct <a href="DeviceResourceAttr.md">DeviceResourceAttr</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1483230794093530"></a>

## **Field Documentation**<a name="section871574207093530"></a>

## name<a name="aadf17a5e450feda1a2ccb043fc94f907"></a>

```
const char* DeviceResourceAttr::name
```

 **Description:**

Pointer to the attribute name 

## next<a name="ac806f1957696cfecba92937d8b25409f"></a>

```
struct [DeviceResourceAttr](DeviceResourceAttr.md)* DeviceResourceAttr::next
```

 **Description:**

Pointer to the next attribute of the node in the configuration tree. 

## value<a name="a2a9e9a433e8197aaf4863efe468ffdd2"></a>

```
const char* DeviceResourceAttr::value
```

 **Description:**

Pointer to the attribute value 

