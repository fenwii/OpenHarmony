# IUnknownEntry<a name="ZH-CN_TOPIC_0000001055515028"></a>

## **Overview**<a name="section314966837191900"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines the  **[IUnknown](IUnknown.md)**  implementation class. 

You need to inherit this structure when developing a subclass of the  **[IUnknown](IUnknown.md)**  implementation class. Each  **[IUnknown](IUnknown.md)**  interface must correspond to one or more  **[IUnknown](IUnknown.md)**  implementation classes. 

## **Summary**<a name="section559713923191900"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table905727140191900"></a>
<table><thead align="left"><tr id="row828602909191900"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1902887869191900"><a name="p1902887869191900"></a><a name="p1902887869191900"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p971681458191900"><a name="p971681458191900"></a><a name="p971681458191900"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1967679010191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p279045397191900"><a name="p279045397191900"></a><a name="p279045397191900"></a><a href="IUnknownEntry.md#a5d0fd097aeef2c3a9766a47cf148d8b9">ver</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1191850188191900"><a name="p1191850188191900"></a><a name="p1191850188191900"></a>uint16&nbsp;</p>
</td>
</tr>
<tr id="row156820516191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p538806403191900"><a name="p538806403191900"></a><a name="p538806403191900"></a><a href="IUnknownEntry.md#afdf52f5e2c624790ab558ffb0c8aa9a9">ref</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p472559174191900"><a name="p472559174191900"></a><a name="p472559174191900"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row1863572732191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p234661748191900"><a name="p234661748191900"></a><a name="p234661748191900"></a><a href="IUnknownEntry.md#adb0c9a5863f934471bb2edf853690bb9">iUnknown</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684288046191900"><a name="p684288046191900"></a><a name="p684288046191900"></a><a href="IUnknown.md">IUnknown</a>&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1639010056191900"></a>

## **Field Documentation**<a name="section268299301191900"></a>

## iUnknown<a name="adb0c9a5863f934471bb2edf853690bb9"></a>

```
[IUnknown](IUnknown.md) IUnknownEntry::iUnknown
```

 **Description:**

Implementation of  **[IUnknown](IUnknown.md)**  interface, which is related to the specific definition implementation. 

## ref<a name="afdf52f5e2c624790ab558ffb0c8aa9a9"></a>

```
int16 IUnknownEntry::ref
```

 **Description:**

Reference count of  **[IUnknown](IUnknown.md)**  interface. 

## ver<a name="a5d0fd097aeef2c3a9766a47cf148d8b9"></a>

```
uint16 IUnknownEntry::ver
```

 **Description:**

Version information of  **[IUnknown](IUnknown.md)**  interface. 

