# CodecBufferInfo<a name="ZH-CN_TOPIC_0000001054879526"></a>

## **Overview**<a name="section235147149084835"></a>

**Related Modules:**

[Codec](Codec.md)

**Description:**

Describes buffer information. 

## **Summary**<a name="section1580410091084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table856834695084835"></a>
<table><thead align="left"><tr id="row485573464084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1095548666084835"><a name="p1095548666084835"></a><a name="p1095548666084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p654846566084835"><a name="p654846566084835"></a><a name="p654846566084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2127133339084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612834128084835"><a name="p612834128084835"></a><a name="p612834128084835"></a><a href="CodecBufferInfo.md#a9b30909c247d03dfc94e4cfdcb69b13a">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p869857992084835"><a name="p869857992084835"></a><a name="p869857992084835"></a><a href="Codec.md#gadf8e136713c0691010d2bec6ba63e9cf">BufferType</a>&nbsp;</p>
</td>
</tr>
<tr id="row1360068031084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p792741990084835"><a name="p792741990084835"></a><a name="p792741990084835"></a><em id="ab1c584c3d34bf9d028c9daa97722812f"><a name="ab1c584c3d34bf9d028c9daa97722812f"></a><a name="ab1c584c3d34bf9d028c9daa97722812f"></a></em></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078207800084835"><a name="p1078207800084835"></a><a name="p1078207800084835"></a><strong id="ab1c584c3d34bf9d028c9daa97722812f_1"><a name="ab1c584c3d34bf9d028c9daa97722812f_1"></a><a name="ab1c584c3d34bf9d028c9daa97722812f_1"></a></strong> union {</p>
</td>
</tr>
<tr id="row1691745931084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061780509084835"><a name="p1061780509084835"></a><a name="p1061780509084835"></a>&nbsp;&nbsp;&nbsp;uint8_t *&nbsp;&nbsp;&nbsp;<a href="CodecBufferInfo.md#ac41289afc743bdc85b266166d612e244">addr</a></p>
</td>
</tr>
<tr id="row1021604359084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1343803291084835"><a name="p1343803291084835"></a><a name="p1343803291084835"></a>&nbsp;&nbsp;&nbsp;int32_t&nbsp;&nbsp;&nbsp;<a href="CodecBufferInfo.md#a8cad2128f76788aed9de86e69e78dd15">fd</a></p>
</td>
</tr>
<tr id="row1772543833084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453093659084835"><a name="p1453093659084835"></a><a name="p1453093659084835"></a>&nbsp;&nbsp;&nbsp;<a href="BufferHandle.md">BufferHandle</a>&nbsp;&nbsp;&nbsp;<a href="CodecBufferInfo.md#a11122e64c16864ce1d8129102905982a">handle</a></p>
</td>
</tr>
<tr id="row638335713084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1314343236084835"><a name="p1314343236084835"></a><a name="p1314343236084835"></a><em id="ab1c584c3d34bf9d028c9daa97722812f_2"><a name="ab1c584c3d34bf9d028c9daa97722812f_2"></a><a name="ab1c584c3d34bf9d028c9daa97722812f_2"></a></em></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526677862084835"><a name="p1526677862084835"></a><a name="p1526677862084835"></a>};&nbsp;</p>
<p id="p1120640815084835"><a name="p1120640815084835"></a><a name="p1120640815084835"></a>Describes the buffer address. </p>
</td>
</tr>
<tr id="row774575245084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p805218848084835"><a name="p805218848084835"></a><a name="p805218848084835"></a><a href="CodecBufferInfo.md#a6c0b23a5f242d80924f2e8689c83b3ae">offset</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1396926107084835"><a name="p1396926107084835"></a><a name="p1396926107084835"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1782695706084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p409199745084835"><a name="p409199745084835"></a><a name="p409199745084835"></a><a href="CodecBufferInfo.md#ac179611206a69c89d7c638e221ea159d">length</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715663595084835"><a name="p1715663595084835"></a><a name="p1715663595084835"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1771366974084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1810649543084835"><a name="p1810649543084835"></a><a name="p1810649543084835"></a><a href="CodecBufferInfo.md#a9f02e97d2724dd93324d8e70793357b4">size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p540597057084835"><a name="p540597057084835"></a><a name="p540597057084835"></a>uint32_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section820432735084835"></a>

## **Field Documentation**<a name="section246054964084835"></a>

## addr<a name="ac41289afc743bdc85b266166d612e244"></a>

```
uint8_t* CodecBufferInfo::addr
```

 **Description:**

Virtual address 

## fd<a name="a8cad2128f76788aed9de86e69e78dd15"></a>

```
int32_t CodecBufferInfo::fd
```

 **Description:**

File descriptor 

## handle<a name="a11122e64c16864ce1d8129102905982a"></a>

```
[BufferHandle](BufferHandle.md) CodecBufferInfo::handle
```

 **Description:**

Data handle. For details, see  [BufferHandle](BufferHandle.md) 

## length<a name="ac179611206a69c89d7c638e221ea159d"></a>

```
uint32_t CodecBufferInfo::length
```

 **Description:**

Length of valid data 

## offset<a name="a6c0b23a5f242d80924f2e8689c83b3ae"></a>

```
uint32_t CodecBufferInfo::offset
```

 **Description:**

Buffer offset 

## size<a name="a9f02e97d2724dd93324d8e70793357b4"></a>

```
uint32_t CodecBufferInfo::size
```

 **Description:**

Total size of buffer blocks 

## type<a name="a9b30909c247d03dfc94e4cfdcb69b13a"></a>

```
[BufferType](Codec.md#gadf8e136713c0691010d2bec6ba63e9cf) CodecBufferInfo::type
```

 **Description:**

Buffer type 

