# OHOS::SurfaceBuffer<a name="ZH-CN_TOPIC_0000001054718143"></a>

## **Overview**<a name="section913605657093532"></a>

**Related Modules:**

[Surface](Surface.md)

**Description:**

Provides functions such as setting the virtual address, size, and additional attributes of shared memory. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section951082090093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table716726653093532"></a>
<table><thead align="left"><tr id="row770161509093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1889762361093532"><a name="p1889762361093532"></a><a name="p1889762361093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p581033731093532"><a name="p581033731093532"></a><a name="p581033731093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1021508952093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419003701093532"><a name="p419003701093532"></a><a name="p419003701093532"></a><a href="Surface.md#ga623d6c8ced742a36017bb71f6441b2a7">GetVirAddr</a> () const =0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666296938093532"><a name="p1666296938093532"></a><a name="p1666296938093532"></a>virtual void *&nbsp;</p>
<p id="p718787854093532"><a name="p718787854093532"></a><a name="p718787854093532"></a>Obtains the virtual address of shared memory for producers and consumers. </p>
</td>
</tr>
<tr id="row559769922093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709042030093532"><a name="p709042030093532"></a><a name="p709042030093532"></a><a href="Surface.md#ga5d797958fed83fdea15b3f6ad5ddf97e">GetPhyAddr</a> () const =0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257223158093532"><a name="p257223158093532"></a><a name="p257223158093532"></a>virtual uint64_t&nbsp;</p>
<p id="p1947960189093532"><a name="p1947960189093532"></a><a name="p1947960189093532"></a>Obtains the physical address of shared memory. </p>
</td>
</tr>
<tr id="row87859895093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2046034225093532"><a name="p2046034225093532"></a><a name="p2046034225093532"></a><a href="Surface.md#gaad9d0ca349b3f398b31c38ac9a650138">GetSize</a> () const =0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p721443069093532"><a name="p721443069093532"></a><a name="p721443069093532"></a>virtual uint32_t&nbsp;</p>
<p id="p1795252399093532"><a name="p1795252399093532"></a><a name="p1795252399093532"></a>Obtains the size of shared memory. </p>
</td>
</tr>
<tr id="row1522347830093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044836631093532"><a name="p1044836631093532"></a><a name="p1044836631093532"></a><a href="Surface.md#ga818ee9015ff03d536b9a73d52f36b4f2">SetSize</a> (uint32_t size)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293931224093532"><a name="p293931224093532"></a><a name="p293931224093532"></a>virtual void&nbsp;</p>
<p id="p512715012093532"><a name="p512715012093532"></a><a name="p512715012093532"></a>Sets the size of shared memory. </p>
</td>
</tr>
<tr id="row558839103093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851443823093532"><a name="p1851443823093532"></a><a name="p1851443823093532"></a><a href="Surface.md#gaf4b467cb2d7015d00f4bcf77c5b19875">SetInt32</a> (uint32_t key, int32_t value)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p302474096093532"><a name="p302474096093532"></a><a name="p302474096093532"></a>virtual int32_t&nbsp;</p>
<p id="p74608160093532"><a name="p74608160093532"></a><a name="p74608160093532"></a>Sets an extra attribute value of the int32 type. </p>
</td>
</tr>
<tr id="row1133847304093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p784386909093532"><a name="p784386909093532"></a><a name="p784386909093532"></a><a href="Surface.md#ga54a916606158a8799fe421eb3842848e">GetInt32</a> (uint32_t key, int32_t &amp;value)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1498493024093532"><a name="p1498493024093532"></a><a name="p1498493024093532"></a>virtual int32_t&nbsp;</p>
<p id="p1703501545093532"><a name="p1703501545093532"></a><a name="p1703501545093532"></a>Obtains an extra attribute value of the int32 type. </p>
</td>
</tr>
<tr id="row1449273791093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p580021002093532"><a name="p580021002093532"></a><a name="p580021002093532"></a><a href="Surface.md#ga479eea3722e4d8448ead051c2f11cec5">SetInt64</a> (uint32_t key, int64_t value)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1065380095093532"><a name="p1065380095093532"></a><a name="p1065380095093532"></a>virtual int32_t&nbsp;</p>
<p id="p264818791093532"><a name="p264818791093532"></a><a name="p264818791093532"></a>Sets an extra attribute value of the int64 type. </p>
</td>
</tr>
<tr id="row332537190093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p853672703093532"><a name="p853672703093532"></a><a name="p853672703093532"></a><a href="Surface.md#ga3a442c71aee865c7b7a9bb6505ce800a">GetInt64</a> (uint32_t key, int64_t &amp;value)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492421200093532"><a name="p1492421200093532"></a><a name="p1492421200093532"></a>virtual int32_t&nbsp;</p>
<p id="p921437593093532"><a name="p921437593093532"></a><a name="p921437593093532"></a>Obtains an extra attribute value of the int64 type. </p>
</td>
</tr>
</tbody>
</table>

