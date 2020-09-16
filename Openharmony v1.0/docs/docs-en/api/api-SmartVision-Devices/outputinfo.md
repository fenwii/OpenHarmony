# OutputInfo<a name="EN-US_TOPIC_0000001054918167"></a>

## **Overview**<a name="section605306868093532"></a>

**Related Modules:**

[Codec](codec.md)

**Description:**

Describes output information. 

## **Summary**<a name="section479671022093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table311810044093532"></a>
<table><thead align="left"><tr id="row1025482634093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p657816759093532"><a name="p657816759093532"></a><a name="p657816759093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p161283140093532"><a name="p161283140093532"></a><a name="p161283140093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1437131849093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p967973582093532"><a name="p967973582093532"></a><a name="p967973582093532"></a><a href="outputinfo.md#ac131b4abc43415f000a0750e82bb881d">bufferCnt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847666802093532"><a name="p1847666802093532"></a><a name="p1847666802093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row1039262690093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2093995554093532"><a name="p2093995554093532"></a><a name="p2093995554093532"></a><a href="outputinfo.md#a5a8cc2acb5f2918dde6fa60562e54d00">buffers</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1680222932093532"><a name="p1680222932093532"></a><a name="p1680222932093532"></a><a href="codecbufferinfo.md">CodecBufferInfo</a> * </p>
</td>
</tr>
<tr id="row1365635255093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292100481093532"><a name="p1292100481093532"></a><a name="p1292100481093532"></a><a href="outputinfo.md#ac160a64994059683a0fc0547ab734a87">timeStamp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p736026581093532"><a name="p736026581093532"></a><a name="p736026581093532"></a>int64_t </p>
</td>
</tr>
<tr id="row549821317093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p493824876093532"><a name="p493824876093532"></a><a name="p493824876093532"></a><a href="outputinfo.md#a6ad161decc8e676690c66d2a6dbde468">sequence</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274540511093532"><a name="p274540511093532"></a><a name="p274540511093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row831763929093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453927018093532"><a name="p1453927018093532"></a><a name="p1453927018093532"></a><a href="outputinfo.md#a56f914be981dd3a2f0ee8c65e501d8f1">flag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1842901618093532"><a name="p1842901618093532"></a><a name="p1842901618093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row1267157875093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2023979434093532"><a name="p2023979434093532"></a><a name="p2023979434093532"></a><a href="outputinfo.md#ad3d70960789585a3b2014d83dddc448b">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1721404135093532"><a name="p1721404135093532"></a><a name="p1721404135093532"></a><a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a> </p>
</td>
</tr>
<tr id="row1987735178093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p180292519093532"><a name="p180292519093532"></a><a name="p180292519093532"></a><a href="outputinfo.md#a751ecb0c55401f130bf1a5b6492e1f38">vendorPrivate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27469826093532"><a name="p27469826093532"></a><a name="p27469826093532"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2107077654093532"></a>

## **Field Documentation**<a name="section461520368093532"></a>

## bufferCnt<a name="ac131b4abc43415f000a0750e82bb881d"></a>

```
uint32_t OutputInfo::bufferCnt
```

 **Description:**

Number of buffers 

## buffers<a name="a5a8cc2acb5f2918dde6fa60562e54d00"></a>

```
[CodecBufferInfo](codecbufferinfo.md)* OutputInfo::buffers
```

 **Description:**

Pointer to the buffer description. For details, see  [CodecBufferInfo](codecbufferinfo.md). 

## flag<a name="a56f914be981dd3a2f0ee8c65e501d8f1"></a>

```
uint32_t OutputInfo::flag
```

 **Description:**

Output flag 

## sequence<a name="a6ad161decc8e676690c66d2a6dbde468"></a>

```
uint32_t OutputInfo::sequence
```

 **Description:**

Corresponding input sequence number 

## timeStamp<a name="ac160a64994059683a0fc0547ab734a87"></a>

```
int64_t OutputInfo::timeStamp
```

 **Description:**

Output timestamp 

## type<a name="ad3d70960789585a3b2014d83dddc448b"></a>

```
[CodecType](codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79) OutputInfo::type
```

 **Description:**

Codec type 

## vendorPrivate<a name="a751ecb0c55401f130bf1a5b6492e1f38"></a>

```
void* OutputInfo::vendorPrivate
```

 **Description:**

Private information about a device vendor 

