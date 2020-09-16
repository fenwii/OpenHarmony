# OHOS::Vector2< T \><a name="EN-US_TOPIC_0000001055518120"></a>

## **Overview**<a name="section1560304356093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the two-dimensional vector, and provides basic mathematical operations such as vector assignment, scalar product, cross product, addition, and subtraction. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1926822297093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1736791605093535"></a>
<table><thead align="left"><tr id="row1208136868093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p189835713093535"><a name="p189835713093535"></a><a name="p189835713093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p144698745093535"><a name="p144698745093535"></a><a name="p144698745093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row171243440093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p22850565093535"><a name="p22850565093535"></a><a name="p22850565093535"></a><a href="graphic.md#ga7fd378c8c6c9fcf7325fa354f182865c">Vector2</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083316353093535"><a name="p2083316353093535"></a><a name="p2083316353093535"></a> </p>
<p id="p1339255112093535"><a name="p1339255112093535"></a><a name="p1339255112093535"></a>A constructor used to create a <strong id="b2087969706093535"><a name="b2087969706093535"></a><a name="b2087969706093535"></a><a href="ohos-vector2-t.md">Vector2</a></strong> instance. </p>
</td>
</tr>
<tr id="row1185622599093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144038719093535"><a name="p2144038719093535"></a><a name="p2144038719093535"></a><a href="graphic.md#gada601fe3518d7bb489010370f1db9903">Vector2</a> (T x, T y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1531116351093535"><a name="p1531116351093535"></a><a name="p1531116351093535"></a> </p>
<p id="p1531833493093535"><a name="p1531833493093535"></a><a name="p1531833493093535"></a>A constructor used to create a <strong id="b1082784137093535"><a name="b1082784137093535"></a><a name="b1082784137093535"></a><a href="ohos-vector2-t.md">Vector2</a></strong> instance based on the X and Y coordinates. </p>
</td>
</tr>
<tr id="row878926565093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807726792093535"><a name="p1807726792093535"></a><a name="p1807726792093535"></a><a href="graphic.md#ga1cc5130b89192fc1403eb29dd4504cbb">~Vector2</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036294894093535"><a name="p2036294894093535"></a><a name="p2036294894093535"></a> </p>
<p id="p409227133093535"><a name="p409227133093535"></a><a name="p409227133093535"></a>A destructor used to delete the <strong id="b501713615093535"><a name="b501713615093535"></a><a name="b501713615093535"></a><a href="ohos-vector2-t.md">Vector2</a></strong> instance. </p>
</td>
</tr>
<tr id="row1388834850093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1158341573093535"><a name="p1158341573093535"></a><a name="p1158341573093535"></a><a href="graphic.md#gae45c198b5bcb73ecac8d654c281bc21a">Dot</a> (const <a href="ohos-vector2-t.md">Vector2</a>&lt; T &gt; &amp;other) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114263943093535"><a name="p114263943093535"></a><a name="p114263943093535"></a>T </p>
<p id="p168645963093535"><a name="p168645963093535"></a><a name="p168645963093535"></a>Calculates the scalar product of the two-dimensional vector and another two-dimensional vector. </p>
</td>
</tr>
<tr id="row2126933454093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1369759043093535"><a name="p1369759043093535"></a><a name="p1369759043093535"></a><a href="graphic.md#gac1c8e01fd488d5f8aea6bddad1dec206">Cross</a> (const <a href="ohos-vector2-t.md">Vector2</a>&lt; T &gt; &amp;other) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2060087872093535"><a name="p2060087872093535"></a><a name="p2060087872093535"></a>T </p>
<p id="p880620888093535"><a name="p880620888093535"></a><a name="p880620888093535"></a>Calculates the cross product of the two-dimensional vector and another two-dimensional vector. </p>
</td>
</tr>
<tr id="row477833229093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496257659093535"><a name="p1496257659093535"></a><a name="p1496257659093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809771377093535"><a name="p1809771377093535"></a><a name="p1809771377093535"></a>void * </p>
<p id="p392867903093535"><a name="p392867903093535"></a><a name="p392867903093535"></a>Overrides the <strong id="b336421270093535"><a name="b336421270093535"></a><a name="b336421270093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row549894201093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220262647093535"><a name="p220262647093535"></a><a name="p220262647093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555062835093535"><a name="p1555062835093535"></a><a name="p1555062835093535"></a>void </p>
<p id="p2091638154093535"><a name="p2091638154093535"></a><a name="p2091638154093535"></a>Overrides the <strong id="b1875852679093535"><a name="b1875852679093535"></a><a name="b1875852679093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

