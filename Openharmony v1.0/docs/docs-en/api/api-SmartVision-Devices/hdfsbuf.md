# HdfSBuf<a name="EN-US_TOPIC_0000001055039516"></a>

## **Overview**<a name="section2102911516093530"></a>

**Related Modules:**

[Core](core.md)

**Description:**

Defines a  **[HdfSBuf](hdfsbuf.md)**. 

**Since:**

1.0

## **Summary**<a name="section1719315604093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1785607504093530"></a>
<table><thead align="left"><tr id="row351962591093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298932174093530"><a name="p1298932174093530"></a><a name="p1298932174093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p382699885093530"><a name="p382699885093530"></a><a name="p382699885093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1601611605093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40857423093530"><a name="p40857423093530"></a><a name="p40857423093530"></a><a href="hdfsbuf.md#a0de2284b2d9921bdd47e598e0b71a440">writePos</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p109803708093530"><a name="p109803708093530"></a><a name="p109803708093530"></a>size_t </p>
</td>
</tr>
<tr id="row1577669277093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1192326677093530"><a name="p1192326677093530"></a><a name="p1192326677093530"></a><a href="hdfsbuf.md#a34756aefb83171abc63d0b5684597542">readPos</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249620941093530"><a name="p249620941093530"></a><a name="p249620941093530"></a>size_t </p>
</td>
</tr>
<tr id="row1406442862093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1948413449093530"><a name="p1948413449093530"></a><a name="p1948413449093530"></a><a href="hdfsbuf.md#a4b8ee04fe9c107abec005bc3828a135d">capacity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139771281093530"><a name="p1139771281093530"></a><a name="p1139771281093530"></a>size_t </p>
</td>
</tr>
<tr id="row1921397456093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048235094093530"><a name="p1048235094093530"></a><a name="p1048235094093530"></a><a href="hdfsbuf.md#a72274990ce3144c476b74734413d8564">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p34340048093530"><a name="p34340048093530"></a><a name="p34340048093530"></a>uint8_t * </p>
</td>
</tr>
<tr id="row1544394478093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p937294470093530"><a name="p937294470093530"></a><a name="p937294470093530"></a><a href="hdfsbuf.md#a3c130cb993cd738efaf14c3f45d085b2">isBind</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1171798566093530"><a name="p1171798566093530"></a><a name="p1171798566093530"></a>bool </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section670835798093530"></a>

## **Field Documentation**<a name="section1876558460093530"></a>

## capacity<a name="a4b8ee04fe9c107abec005bc3828a135d"></a>

```
size_t HdfSBuf::capacity
```

 **Description:**

Storage capacity, at most 512 KB. 

## data<a name="a72274990ce3144c476b74734413d8564"></a>

```
uint8_t* HdfSBuf::data
```

 **Description:**

Pointer to data storage 

## isBind<a name="a3c130cb993cd738efaf14c3f45d085b2"></a>

```
bool HdfSBuf::isBind
```

 **Description:**

Whether to bind the externally transferred pointer for data storage 

## readPos<a name="a34756aefb83171abc63d0b5684597542"></a>

```
size_t HdfSBuf::readPos
```

 **Description:**

Current read position 

## writePos<a name="a0de2284b2d9921bdd47e598e0b71a440"></a>

```
size_t HdfSBuf::writePos
```

 **Description:**

Current write position 

