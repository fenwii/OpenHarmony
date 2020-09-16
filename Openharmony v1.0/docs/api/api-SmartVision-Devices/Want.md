# Want<a name="ZH-CN_TOPIC_0000001055039558"></a>

## **Overview**<a name="section1213502433093537"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)

**Description:**

Defines the abstract description of an operation, including information about the ability and the extra data to carry. 

## **Summary**<a name="section660161946093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1142858405093537"></a>
<table><thead align="left"><tr id="row2123467526093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p310873626093537"><a name="p310873626093537"></a><a name="p310873626093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1167934680093537"><a name="p1167934680093537"></a><a name="p1167934680093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1117687800093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564909556093537"><a name="p564909556093537"></a><a name="p564909556093537"></a><a href="Want.md#a0ca9d0b3a71d92dec9a14468787afbf8">element</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p312199064093537"><a name="p312199064093537"></a><a name="p312199064093537"></a><a href="ElementName.md">ElementName</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1039094166093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p661288433093537"><a name="p661288433093537"></a><a name="p661288433093537"></a><a href="Want.md#a08a6438e5a2630cbefde052834869b3c">sid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416990508093537"><a name="p416990508093537"></a><a name="p416990508093537"></a>SvcIdentity *&nbsp;</p>
</td>
</tr>
<tr id="row2071984267093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111140556093537"><a name="p111140556093537"></a><a name="p111140556093537"></a><a href="Want.md#a47c0d5e886bb5cb0b7c9fdb32fa903fa">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038422073093537"><a name="p1038422073093537"></a><a name="p1038422073093537"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row1096945539093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p939246477093537"><a name="p939246477093537"></a><a name="p939246477093537"></a><a href="Want.md#a9175a7f7f1c7d84e11042b2d17a2d3f4">dataLength</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113191417093537"><a name="p113191417093537"></a><a name="p113191417093537"></a>uint16_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section802818219093537"></a>

## **Field Documentation**<a name="section1092664135093537"></a>

## data<a name="a47c0d5e886bb5cb0b7c9fdb32fa903fa"></a>

```
void* Want::data
```

 **Description:**

Pointer to the carried data 

## dataLength<a name="a9175a7f7f1c7d84e11042b2d17a2d3f4"></a>

```
uint16_t Want::dataLength
```

 **Description:**

Data length 

## element<a name="a0ca9d0b3a71d92dec9a14468787afbf8"></a>

```
[ElementName](ElementName.md)* Want::element
```

 **Description:**

Pointer to the ability information, including the device ID, bundle name, and class name. 

## sid<a name="a08a6438e5a2630cbefde052834869b3c"></a>

```
SvcIdentity* Want::sid
```

 **Description:**

Pointer to the ID of the server that listens for ability startup. After the ability is started, the callback function corresponding to the server will be invoked. 

