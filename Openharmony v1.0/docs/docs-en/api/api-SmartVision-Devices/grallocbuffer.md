# GrallocBuffer<a name="EN-US_TOPIC_0000001054718125"></a>

## **Overview**<a name="section1186105809093530"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Defines the memory buffer, including the buffer handle, memory type, memory size, and virtual memory address. 

## **Summary**<a name="section253494518093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table812987329093530"></a>
<table><thead align="left"><tr id="row1143531398093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1465700321093530"><a name="p1465700321093530"></a><a name="p1465700321093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p483416696093530"><a name="p483416696093530"></a><a name="p483416696093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row270476948093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907419132093530"><a name="p907419132093530"></a><a name="p907419132093530"></a><a href="grallocbuffer.md#a6bdce5004be0cb1c41326c0621581fff">hdl</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884763561093530"><a name="p1884763561093530"></a><a name="p1884763561093530"></a><a href="bufferhandle.md">BufferHandle</a> </p>
</td>
</tr>
<tr id="row1926374375093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1877122654093530"><a name="p1877122654093530"></a><a name="p1877122654093530"></a><a href="grallocbuffer.md#ad66bdf06909350cd1a4e5c45349e72ae">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100881722093530"><a name="p100881722093530"></a><a name="p100881722093530"></a><a href="display.md#gabd31f838aefffa46191d0d7dc36a96b2">MemType</a> </p>
</td>
</tr>
<tr id="row865172974093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031616094093530"><a name="p1031616094093530"></a><a name="p1031616094093530"></a><a href="grallocbuffer.md#a756f3d9e23d7e97a28a5228765cb8cf3">size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p31920768093530"><a name="p31920768093530"></a><a name="p31920768093530"></a>uint32_t </p>
</td>
</tr>
<tr id="row169732798093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p101958938093530"><a name="p101958938093530"></a><a name="p101958938093530"></a><a href="grallocbuffer.md#a3196376b8b938cf96e008152f1ddceee">virAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1686541328093530"><a name="p1686541328093530"></a><a name="p1686541328093530"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1801065956093530"></a>

## **Field Documentation**<a name="section594351810093530"></a>

## hdl<a name="a6bdce5004be0cb1c41326c0621581fff"></a>

```
[BufferHandle](bufferhandle.md) GrallocBuffer::hdl
```

 **Description:**

Buffer handle 

## size<a name="a756f3d9e23d7e97a28a5228765cb8cf3"></a>

```
uint32_t GrallocBuffer::size
```

 **Description:**

Size of the requested memory 

## type<a name="ad66bdf06909350cd1a4e5c45349e72ae"></a>

```
[MemType](display.md#gabd31f838aefffa46191d0d7dc36a96b2) GrallocBuffer::type
```

 **Description:**

Type of the requested memory 

## virAddr<a name="a3196376b8b938cf96e008152f1ddceee"></a>

```
void* GrallocBuffer::virAddr
```

 **Description:**

Virtual address of the requested memory 

