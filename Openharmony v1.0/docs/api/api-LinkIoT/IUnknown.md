# IUnknown<a name="ZH-CN_TOPIC_0000001055675024"></a>

## **Overview**<a name="section950816859191859"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines the  **[IUnknown](IUnknown.md)**  class. 

You need to inherit this structure when developing a subclass of the  **[IUnknown](IUnknown.md)**  interface. 

## **Summary**<a name="section306881384191859"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1742900833191859"></a>
<table><thead align="left"><tr id="row1678375430191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2017711537191859"><a name="p2017711537191859"></a><a name="p2017711537191859"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1568541144191859"><a name="p1568541144191859"></a><a name="p1568541144191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row11611545191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p592990921191859"><a name="p592990921191859"></a><a name="p592990921191859"></a><a href="IUnknown.md#ab1eebb31d61b815123d65764134de2bc">QueryInterface</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, int version, void **target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1475394127191859"><a name="p1475394127191859"></a><a name="p1475394127191859"></a>int(*&nbsp;</p>
</td>
</tr>
<tr id="row376148288191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390499131191859"><a name="p1390499131191859"></a><a name="p1390499131191859"></a><a href="IUnknown.md#a4d778cd58b81b5f35f7704cbfc5fb3ef">AddRef</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p76427524191859"><a name="p76427524191859"></a><a name="p76427524191859"></a>int(*&nbsp;</p>
</td>
</tr>
<tr id="row764487513191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872573147191859"><a name="p1872573147191859"></a><a name="p1872573147191859"></a><a href="IUnknown.md#a5b8e564aec30767170a2c27380277715">Release</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1009077144191859"><a name="p1009077144191859"></a><a name="p1009077144191859"></a>int(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1355923748191859"></a>

## **Field Documentation**<a name="section1508185285191859"></a>

## AddRef<a name="a4d778cd58b81b5f35f7704cbfc5fb3ef"></a>

```
int(* IUnknown::AddRef) ([IUnknown](IUnknown.md) *iUnknown)
```

 **Description:**

Adds the reference count. 

## QueryInterface<a name="ab1eebb31d61b815123d65764134de2bc"></a>

```
int(* IUnknown::QueryInterface) ([IUnknown](IUnknown.md) *iUnknown, int version, void **target)
```

 **Description:**

Queries the subclass object of the  **[IUnknown](IUnknown.md)**  interface of a specified version \(downcasting\). 

## Release<a name="a5b8e564aec30767170a2c27380277715"></a>

```
int(* IUnknown::Release) ([IUnknown](IUnknown.md) *iUnknown)
```

 **Description:**

Release the reference to an  **[IUnknown](IUnknown.md)**  interface. 

