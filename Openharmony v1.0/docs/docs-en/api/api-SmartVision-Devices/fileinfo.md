# FileInfo<a name="EN-US_TOPIC_0000001054479561"></a>

## **Overview**<a name="section290268220093530"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines movie file information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2073134810093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2062453253093530"></a>
<table><thead align="left"><tr id="row624031907093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p469257558093530"><a name="p469257558093530"></a><a name="p469257558093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1083353932093530"><a name="p1083353932093530"></a><a name="p1083353932093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1140521081093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091484620093530"><a name="p1091484620093530"></a><a name="p1091484620093530"></a><a href="fileinfo.md#a38797d4349538f098d6f14b94446bee7">formatName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1738966893093530"><a name="p1738966893093530"></a><a name="p1738966893093530"></a>char * </p>
</td>
</tr>
<tr id="row458451661093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p254342205093530"><a name="p254342205093530"></a><a name="p254342205093530"></a><a href="fileinfo.md#ac6afb3ba1891e7fd02c3b2c942d2525f">bitrate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770872799093530"><a name="p1770872799093530"></a><a name="p1770872799093530"></a>uint32_t </p>
</td>
</tr>
<tr id="row1104639130093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p98231340093530"><a name="p98231340093530"></a><a name="p98231340093530"></a><a href="fileinfo.md#a1373e3d2662f2112eb58078c7ef7e2a2">programNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p116201288093530"><a name="p116201288093530"></a><a name="p116201288093530"></a>uint32_t </p>
</td>
</tr>
<tr id="row839933401093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730441336093530"><a name="p730441336093530"></a><a name="p730441336093530"></a><a href="fileinfo.md#aeb2b662b1dd525c9b56f2ddca1013058">programInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1140115281093530"><a name="p1140115281093530"></a><a name="p1140115281093530"></a><a href="programinfo.md">ProgramInfo</a> * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section7338217093530"></a>

## **Field Documentation**<a name="section597530444093530"></a>

## bitrate<a name="ac6afb3ba1891e7fd02c3b2c942d2525f"></a>

```
uint32_t FileInfo::bitrate
```

 **Description:**

Bit rate of the movie file 

## formatName<a name="a38797d4349538f098d6f14b94446bee7"></a>

```
char* FileInfo::formatName
```

 **Description:**

Pointer to the name of the movie file container format 

## programInfo<a name="aeb2b662b1dd525c9b56f2ddca1013058"></a>

```
[ProgramInfo](programinfo.md)* FileInfo::programInfo
```

 **Description:**

Pointer to the array of information about the movie file program 

## programNum<a name="a1373e3d2662f2112eb58078c7ef7e2a2"></a>

```
uint32_t FileInfo::programNum
```

 **Description:**

Number of programs 

