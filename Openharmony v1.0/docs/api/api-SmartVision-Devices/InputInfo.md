# InputInfo<a name="ZH-CN_TOPIC_0000001054879536"></a>

## **Overview**<a name="section511833735093531"></a>

**Related Modules:**

[Codec](Codec.md)

**Description:**

Describes input information. 

## **Summary**<a name="section1541725750093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1012028454093531"></a>
<table><thead align="left"><tr id="row69252047093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1824613706093531"><a name="p1824613706093531"></a><a name="p1824613706093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1295114853093531"><a name="p1295114853093531"></a><a name="p1295114853093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1343883992093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370046274093531"><a name="p1370046274093531"></a><a name="p1370046274093531"></a><a href="InputInfo.md#adf0831b639d3e7e3b99c5cb2de16fad5">bufferCnt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519379954093531"><a name="p519379954093531"></a><a name="p519379954093531"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row2058237168093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960702536093531"><a name="p960702536093531"></a><a name="p960702536093531"></a><a href="InputInfo.md#ad759a3e9cef5806ffbf9dbff601d3897">buffers</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333331975093531"><a name="p333331975093531"></a><a name="p333331975093531"></a><a href="CodecBufferInfo.md">CodecBufferInfo</a> *&nbsp;</p>
</td>
</tr>
<tr id="row638800538093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302066625093531"><a name="p302066625093531"></a><a name="p302066625093531"></a><a href="InputInfo.md#acc69e5b615cd5fbe52626fb52cb1b90e">pts</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331730356093531"><a name="p1331730356093531"></a><a name="p1331730356093531"></a>int64_t&nbsp;</p>
</td>
</tr>
<tr id="row725257484093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p326480471093531"><a name="p326480471093531"></a><a name="p326480471093531"></a><a href="InputInfo.md#a80d14d367be6484c1487d4fd2cef7e5f">flag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087919664093531"><a name="p1087919664093531"></a><a name="p1087919664093531"></a>int32_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1381757839093531"></a>

## **Field Documentation**<a name="section290707522093531"></a>

## bufferCnt<a name="adf0831b639d3e7e3b99c5cb2de16fad5"></a>

```
uint32_t InputInfo::bufferCnt
```

 **Description:**

Number of buffers 

## buffers<a name="ad759a3e9cef5806ffbf9dbff601d3897"></a>

```
[CodecBufferInfo](CodecBufferInfo.md)* InputInfo::buffers
```

 **Description:**

Pointer to the buffer description. For details, see  [CodecBufferInfo](CodecBufferInfo.md). 

## flag<a name="a80d14d367be6484c1487d4fd2cef7e5f"></a>

```
int32_t InputInfo::flag
```

 **Description:**

Input flag. For details, see  [StreamFlagType](Codec.md#ga8a15793172118d64d8adeba0c8544e84). 

## pts<a name="acc69e5b615cd5fbe52626fb52cb1b90e"></a>

```
int64_t InputInfo::pts
```

 **Description:**

Input timestamp 

