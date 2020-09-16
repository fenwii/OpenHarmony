# OsalFwBlock<a name="EN-US_TOPIC_0000001055678108"></a>

## **Overview**<a name="section2040744613093532"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Defines the data structure for reading a firmware file. 

This structure declares the firmware block to read each time. The firmware file can be read in split mode. 

## **Summary**<a name="section338478603093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table453803561093532"></a>
<table><thead align="left"><tr id="row976824361093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p813584768093532"><a name="p813584768093532"></a><a name="p813584768093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1059333392093532"><a name="p1059333392093532"></a><a name="p1059333392093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1444999155093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292974856093532"><a name="p292974856093532"></a><a name="p292974856093532"></a><a href="osalfwblock.md#affee01298d0388b9e14da67fd17e6eba">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2065889232093532"><a name="p2065889232093532"></a><a name="p2065889232093532"></a>uint8_t * </p>
</td>
</tr>
<tr id="row1536852899093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530751176093532"><a name="p530751176093532"></a><a name="p530751176093532"></a><a href="osalfwblock.md#ada578cbe9c02da3ebef4e70835d42774">endFlag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522046781093532"><a name="p522046781093532"></a><a name="p522046781093532"></a>bool </p>
</td>
</tr>
<tr id="row1346380648093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p657244243093532"><a name="p657244243093532"></a><a name="p657244243093532"></a><a href="osalfwblock.md#a383d93123b0d78a8031132d06ff035c5">dataSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p365282814093532"><a name="p365282814093532"></a><a name="p365282814093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row353417031093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790704361093532"><a name="p790704361093532"></a><a name="p790704361093532"></a><a href="osalfwblock.md#a74631bb4d6242a21146e6465c9640fa8">curOffset</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592101638093532"><a name="p1592101638093532"></a><a name="p1592101638093532"></a>int32_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section525058055093532"></a>

## **Field Documentation**<a name="section191404529093532"></a>

## curOffset<a name="a74631bb4d6242a21146e6465c9640fa8"></a>

```
int32_t OsalFwBlock::curOffset
```

 **Description:**

Offset in the firmware file 

## data<a name="affee01298d0388b9e14da67fd17e6eba"></a>

```
uint8_t* OsalFwBlock::data
```

 **Description:**

Firmware content read this time. You do not need to allocate space. 

## dataSize<a name="a383d93123b0d78a8031132d06ff035c5"></a>

```
uint32_t OsalFwBlock::dataSize
```

 **Description:**

Firmware block size read this time 

## endFlag<a name="ada578cbe9c02da3ebef4e70835d42774"></a>

```
bool OsalFwBlock::endFlag
```

 **Description:**

Whether the firmware file is read completely 

