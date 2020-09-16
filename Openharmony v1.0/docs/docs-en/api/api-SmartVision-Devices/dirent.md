# dirent<a name="EN-US_TOPIC_0000001055198174"></a>

## **Overview**<a name="section1573299253084842"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Defines the content of the directory. 

## **Summary**<a name="section2114563876084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table293740774084842"></a>
<table><thead align="left"><tr id="row589022430084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1722567970084842"><a name="p1722567970084842"></a><a name="p1722567970084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1589253956084842"><a name="p1589253956084842"></a><a name="p1589253956084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row664778421084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793487391084842"><a name="p793487391084842"></a><a name="p793487391084842"></a><a href="dirent.md#aaea0878aa0629630d94e180f5dbc22c5">d_ino</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p186970390084842"><a name="p186970390084842"></a><a name="p186970390084842"></a>ino_t </p>
</td>
</tr>
<tr id="row1353510526084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1749996258084842"><a name="p1749996258084842"></a><a name="p1749996258084842"></a><a href="dirent.md#af812e4ed54eeb48e843efa6fb9a5465f">d_off</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267291785084842"><a name="p267291785084842"></a><a name="p267291785084842"></a>off_t </p>
</td>
</tr>
<tr id="row2129608265084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1481018326084842"><a name="p1481018326084842"></a><a name="p1481018326084842"></a><a href="dirent.md#a90dc47836e8ef510437317876368859e">d_reclen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p471115584084842"><a name="p471115584084842"></a><a name="p471115584084842"></a>unsigned short </p>
</td>
</tr>
<tr id="row1214863963084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p88074759084842"><a name="p88074759084842"></a><a name="p88074759084842"></a><a href="dirent.md#adca3b20d5a245f0d8b9f2aa84844b1ff">d_type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970868130084842"><a name="p1970868130084842"></a><a name="p1970868130084842"></a>unsigned char </p>
</td>
</tr>
<tr id="row1043847798084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762942817084842"><a name="p1762942817084842"></a><a name="p1762942817084842"></a><a href="dirent.md#ae52d525c8057131d7f1155fe7039910d">d_name</a> [256]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p674230706084842"><a name="p674230706084842"></a><a name="p674230706084842"></a>char </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section480199535084842"></a>

## **Field Documentation**<a name="section1962921150084842"></a>

## d\_ino<a name="aaea0878aa0629630d94e180f5dbc22c5"></a>

```
ino_t dirent::d_ino
```

 **Description:**

Inode number 

## d\_name<a name="ae52d525c8057131d7f1155fe7039910d"></a>

```
char dirent::d_name[256]
```

 **Description:**

File name 

## d\_off<a name="af812e4ed54eeb48e843efa6fb9a5465f"></a>

```
off_t dirent::d_off
```

 **Description:**

Offset in the directory stream 

## d\_reclen<a name="a90dc47836e8ef510437317876368859e"></a>

```
unsigned short dirent::d_reclen
```

 **Description:**

File name length 

## d\_type<a name="adca3b20d5a245f0d8b9f2aa84844b1ff"></a>

```
unsigned char dirent::d_type
```

 **Description:**

File type 

