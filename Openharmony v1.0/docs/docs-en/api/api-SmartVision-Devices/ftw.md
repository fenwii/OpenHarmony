# FTW<a name="EN-US_TOPIC_0000001055078137"></a>

## **Overview**<a name="section1418735577084835"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Defines the file tree walker \([FTW](ftw.md)\). 

**[ftw.h](ftw-h.md)**  describes the  **[FTW](ftw.md)**  structure. The file location can be determined based on the offset and the depth relative to the root node. 

## **Summary**<a name="section1015573237084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table836897485084835"></a>
<table><thead align="left"><tr id="row22107749084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p857818101084835"><a name="p857818101084835"></a><a name="p857818101084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1467767275084835"><a name="p1467767275084835"></a><a name="p1467767275084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row692950021084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p783428867084835"><a name="p783428867084835"></a><a name="p783428867084835"></a><a href="ftw.md#adc64b6d8f0f13269fdb026b67c1a6b11">base</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p252123679084835"><a name="p252123679084835"></a><a name="p252123679084835"></a>int </p>
</td>
</tr>
<tr id="row135648385084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p405357929084835"><a name="p405357929084835"></a><a name="p405357929084835"></a><a href="ftw.md#af3d03dada9fed0c37d2cb30ff742c130">level</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224402268084835"><a name="p224402268084835"></a><a name="p224402268084835"></a>int </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section278781884084835"></a>

## **Field Documentation**<a name="section1811223826084835"></a>

## base<a name="adc64b6d8f0f13269fdb026b67c1a6b11"></a>

```
int FTW::base
```

 **Description:**

Offset of the file name in the path name 

## level<a name="af3d03dada9fed0c37d2cb30ff742c130"></a>

```
int FTW::level
```

 **Description:**

Depth of the file name, relative to the root node of the tree 

