# IUnknownEntry<a name="EN-US_TOPIC_0000001054598165"></a>

## **Overview**<a name="section1652913639093531"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Defines the  **[IUnknown](iunknown.md)**  implementation class. 

You need to inherit this structure when developing a subclass of the  **[IUnknown](iunknown.md)**  implementation class. Each  **[IUnknown](iunknown.md)**  interface must correspond to one or more  **[IUnknown](iunknown.md)**  implementation classes. 

## **Summary**<a name="section1618238775093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table479716047093531"></a>
<table><thead align="left"><tr id="row532394617093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p730791076093531"><a name="p730791076093531"></a><a name="p730791076093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p878143413093531"><a name="p878143413093531"></a><a name="p878143413093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2020912165093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430810122093531"><a name="p430810122093531"></a><a name="p430810122093531"></a><a href="iunknownentry.md#a5d0fd097aeef2c3a9766a47cf148d8b9">ver</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2012629044093531"><a name="p2012629044093531"></a><a name="p2012629044093531"></a>uint16 </p>
</td>
</tr>
<tr id="row1854649993093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367444824093531"><a name="p1367444824093531"></a><a name="p1367444824093531"></a><a href="iunknownentry.md#afdf52f5e2c624790ab558ffb0c8aa9a9">ref</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59859821093531"><a name="p59859821093531"></a><a name="p59859821093531"></a>int16 </p>
</td>
</tr>
<tr id="row1445247195093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049938361093531"><a name="p1049938361093531"></a><a name="p1049938361093531"></a><a href="iunknownentry.md#adb0c9a5863f934471bb2edf853690bb9">iUnknown</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844458256093531"><a name="p844458256093531"></a><a name="p844458256093531"></a><a href="iunknown.md">IUnknown</a> </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1531658094093531"></a>

## **Field Documentation**<a name="section1738406174093531"></a>

## iUnknown<a name="adb0c9a5863f934471bb2edf853690bb9"></a>

```
[IUnknown](iunknown.md) IUnknownEntry::iUnknown
```

 **Description:**

Implementation of  **[IUnknown](iunknown.md)**  interface, which is related to the specific definition implementation. 

## ref<a name="afdf52f5e2c624790ab558ffb0c8aa9a9"></a>

```
int16 IUnknownEntry::ref
```

 **Description:**

Reference count of  **[IUnknown](iunknown.md)**  interface. 

## ver<a name="a5d0fd097aeef2c3a9766a47cf148d8b9"></a>

```
uint16 IUnknownEntry::ver
```

 **Description:**

Version information of  **[IUnknown](iunknown.md)**  interface. 

