# SubImageInfo<a name="ZH-CN_TOPIC_0000001054718165"></a>

## **Overview**<a name="section1951653386093537"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines image information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section78560086093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1360295485093537"></a>
<table><thead align="left"><tr id="row1264339816093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1156486902093537"><a name="p1156486902093537"></a><a name="p1156486902093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p889627347093537"><a name="p889627347093537"></a><a name="p889627347093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1545581721093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658960146093537"><a name="p658960146093537"></a><a name="p658960146093537"></a><a href="SubImageInfo.md#a1ac1278b26a2e7a99b71d302c9c6ed14">format</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087725676093537"><a name="p1087725676093537"></a><a name="p1087725676093537"></a><a href="Format.md#gaf7ed135f15d4b218d41705bac0122ba7">CodecFormat</a>&nbsp;</p>
</td>
</tr>
<tr id="row1438721374093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131011814093537"><a name="p2131011814093537"></a><a name="p2131011814093537"></a><a href="SubImageInfo.md#aef3b2ab41d5ff1e928b02fbba76fef36">width</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1092856448093537"><a name="p1092856448093537"></a><a name="p1092856448093537"></a>uint16_t&nbsp;</p>
</td>
</tr>
<tr id="row614706971093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p820936606093537"><a name="p820936606093537"></a><a name="p820936606093537"></a><a href="SubImageInfo.md#a81833417dd54630e8d6ce888e2bcebaf">height</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679881319093537"><a name="p1679881319093537"></a><a name="p1679881319093537"></a>uint16_t&nbsp;</p>
</td>
</tr>
<tr id="row1221722132093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p117664268093537"><a name="p117664268093537"></a><a name="p117664268093537"></a><a href="SubImageInfo.md#a101a202043f054757b7b24ff48cb1095">rotate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440996622093537"><a name="p440996622093537"></a><a name="p440996622093537"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row301907539093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998147696093537"><a name="p1998147696093537"></a><a name="p1998147696093537"></a><a href="SubImageInfo.md#a6a56c46ceb0f503a7b1c3c70276a84ac">dataLength</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1156162736093537"><a name="p1156162736093537"></a><a name="p1156162736093537"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1637388746093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712592391093537"><a name="p1712592391093537"></a><a name="p1712592391093537"></a><a href="SubImageInfo.md#a27cce274c2816cd851be6eb21b2d6324">thumbnail</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029003665093537"><a name="p1029003665093537"></a><a name="p1029003665093537"></a>bool&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section106677725093537"></a>

## **Field Documentation**<a name="section1669022260093537"></a>

## dataLength<a name="a6a56c46ceb0f503a7b1c3c70276a84ac"></a>

```
uint32_t SubImageInfo::dataLength
```

 **Description:**

Image size 

## format<a name="a1ac1278b26a2e7a99b71d302c9c6ed14"></a>

```
[CodecFormat](Format.md#gaf7ed135f15d4b218d41705bac0122ba7) SubImageInfo::format
```

 **Description:**

Image encoding format. For details, see  [CodecFormat](Format.md#gaf7ed135f15d4b218d41705bac0122ba7). 

## height<a name="a81833417dd54630e8d6ce888e2bcebaf"></a>

```
uint16_t SubImageInfo::height
```

 **Description:**

Height, in pixels 

## rotate<a name="a101a202043f054757b7b24ff48cb1095"></a>

```
uint32_t SubImageInfo::rotate
```

 **Description:**

Image rotation angle. The value can be  **90**,  **180**, or  **270**. The default value is  **0**. 

## thumbnail<a name="a27cce274c2816cd851be6eb21b2d6324"></a>

```
bool SubImageInfo::thumbnail
```

 **Description:**

Thumbnail flag 

## width<a name="aef3b2ab41d5ff1e928b02fbba76fef36"></a>

```
uint16_t SubImageInfo::width
```

 **Description:**

Width, in pixels 

