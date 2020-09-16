# BufferHandle<a name="EN-US_TOPIC_0000001054918147"></a>

## **Overview**<a name="section1923418595084835"></a>

**Related Modules:**

[Codec](codec.md)  |  [Display](display.md)

**Description:**

Defines the buffer handle type. The virtual address of a handle maps to its physical address. 

Defines the buffer handle, including the shared memory key, shared memory ID, and physical memory address.

## **Summary**<a name="section589691394084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table754497797084835"></a>
<table><thead align="left"><tr id="row1996998810084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p143275635084835"><a name="p143275635084835"></a><a name="p143275635084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2004303552084835"><a name="p2004303552084835"></a><a name="p2004303552084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row894971223084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1747721388084835"><a name="p1747721388084835"></a><a name="p1747721388084835"></a><a href="bufferhandle.md#ad6dd19ba3f81e8a71607a62da61eee94">virAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007766773084835"><a name="p1007766773084835"></a><a name="p1007766773084835"></a>uint8_t * </p>
</td>
</tr>
<tr id="row2108646019084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2020691017084835"><a name="p2020691017084835"></a><a name="p2020691017084835"></a><a href="bufferhandle.md#a28ebaf90f9e4e04a8fa5bae04dbf8851">handle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591148396084835"><a name="p591148396084835"></a><a name="p591148396084835"></a>uintptr_t </p>
</td>
</tr>
<tr id="row1265745130084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p822184997084835"><a name="p822184997084835"></a><a name="p822184997084835"></a><a href="bufferhandle.md#a9bc55ed9347418af6092399549ee0ff2">key</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090284180084835"><a name="p1090284180084835"></a><a name="p1090284180084835"></a>int32_t </p>
</td>
</tr>
<tr id="row97725899084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451541654084835"><a name="p1451541654084835"></a><a name="p1451541654084835"></a><a href="bufferhandle.md#acef4311b898b393d4473cc77d9ba0c63">shmid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1801953091084835"><a name="p1801953091084835"></a><a name="p1801953091084835"></a>int32_t </p>
</td>
</tr>
<tr id="row2032012856084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p251953505084835"><a name="p251953505084835"></a><a name="p251953505084835"></a><a href="bufferhandle.md#a0c8b61e872a3565f4e9e68ea8de6a669">phyAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1434973307084835"><a name="p1434973307084835"></a><a name="p1434973307084835"></a>uint64_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1770649048084835"></a>

## **Field Documentation**<a name="section626200358084835"></a>

## handle<a name="a28ebaf90f9e4e04a8fa5bae04dbf8851"></a>

```
uintptr_t BufferHandle::handle
```

 **Description:**

Physical address 

## key<a name="a9bc55ed9347418af6092399549ee0ff2"></a>

```
int32_t BufferHandle::key
```

 **Description:**

Shared memory key 

## phyAddr<a name="a0c8b61e872a3565f4e9e68ea8de6a669"></a>

```
uint64_t BufferHandle::phyAddr
```

 **Description:**

Physical address 

## shmid<a name="acef4311b898b393d4473cc77d9ba0c63"></a>

```
int32_t BufferHandle::shmid
```

 **Description:**

Unique ID of the shared memory 

## virAddr<a name="ad6dd19ba3f81e8a71607a62da61eee94"></a>

```
uint8_t* BufferHandle::virAddr
```

 **Description:**

Virtual address 

