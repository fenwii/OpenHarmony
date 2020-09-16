# IUnknown<a name="EN-US_TOPIC_0000001055078143"></a>

## **Overview**<a name="section522992911093531"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Defines the  **[IUnknown](iunknown.md)**  class. 

You need to inherit this structure when developing a subclass of the  **[IUnknown](iunknown.md)**  interface. 

## **Summary**<a name="section1405449152093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1888907989093531"></a>
<table><thead align="left"><tr id="row1303094412093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p301732032093531"><a name="p301732032093531"></a><a name="p301732032093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p726590490093531"><a name="p726590490093531"></a><a name="p726590490093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row819109846093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p445531470093531"><a name="p445531470093531"></a><a name="p445531470093531"></a><a href="iunknown.md#ab1eebb31d61b815123d65764134de2bc">QueryInterface</a> )(<a href="iunknown.md">IUnknown</a> *iUnknown, int version, void **target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1257835675093531"><a name="p1257835675093531"></a><a name="p1257835675093531"></a>int(* </p>
</td>
</tr>
<tr id="row238531176093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p272463919093531"><a name="p272463919093531"></a><a name="p272463919093531"></a><a href="iunknown.md#a4d778cd58b81b5f35f7704cbfc5fb3ef">AddRef</a> )(<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p255583741093531"><a name="p255583741093531"></a><a name="p255583741093531"></a>int(* </p>
</td>
</tr>
<tr id="row645403520093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2016818788093531"><a name="p2016818788093531"></a><a name="p2016818788093531"></a><a href="iunknown.md#a5b8e564aec30767170a2c27380277715">Release</a> )(<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1337216336093531"><a name="p1337216336093531"></a><a name="p1337216336093531"></a>int(* </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1438440606093531"></a>

## **Field Documentation**<a name="section1272271730093531"></a>

## AddRef<a name="a4d778cd58b81b5f35f7704cbfc5fb3ef"></a>

```
int(* IUnknown::AddRef) ([IUnknown](iunknown.md) *iUnknown)
```

 **Description:**

Adds the reference count. 

## QueryInterface<a name="ab1eebb31d61b815123d65764134de2bc"></a>

```
int(* IUnknown::QueryInterface) ([IUnknown](iunknown.md) *iUnknown, int version, void **target)
```

 **Description:**

Queries the subclass object of the  **[IUnknown](iunknown.md)**  interface of a specified version \(downcasting\). 

## Release<a name="a5b8e564aec30767170a2c27380277715"></a>

```
int(* IUnknown::Release) ([IUnknown](iunknown.md) *iUnknown)
```

 **Description:**

Release the reference to an  **[IUnknown](iunknown.md)**  interface. 

