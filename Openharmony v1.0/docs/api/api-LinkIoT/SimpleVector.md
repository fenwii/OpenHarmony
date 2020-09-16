# SimpleVector<a name="ZH-CN_TOPIC_0000001054915095"></a>

## **Overview**<a name="section905664574191902"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines the simplified vector class, which is extended by four elements. 

This class is applicable to the C language development scenario where the data volume is small and dynamic expansion is required. 

## **Summary**<a name="section170792302191902"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2013518143191902"></a>
<table><thead align="left"><tr id="row892301954191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1637365117191902"><a name="p1637365117191902"></a><a name="p1637365117191902"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2106505235191902"><a name="p2106505235191902"></a><a name="p2106505235191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1027384244191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p43536580191902"><a name="p43536580191902"></a><a name="p43536580191902"></a><a href="SimpleVector.md#a68140ca4cc59df48c63963f1eda3f35c">max</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388909585191902"><a name="p388909585191902"></a><a name="p388909585191902"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row104796443191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p896549823191902"><a name="p896549823191902"></a><a name="p896549823191902"></a><a href="SimpleVector.md#ac699cefa0c1003b8babbe2c0ea3134db">top</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673451602191902"><a name="p1673451602191902"></a><a name="p1673451602191902"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row1452363460191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927883846191902"><a name="p927883846191902"></a><a name="p927883846191902"></a><a href="SimpleVector.md#a1ff1e71311df432f11fd2613cdbc1b16">free</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p769088377191902"><a name="p769088377191902"></a><a name="p769088377191902"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row755767846191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p688517779191902"><a name="p688517779191902"></a><a name="p688517779191902"></a><a href="SimpleVector.md#a4674672209ae411544383a5399aee85b">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1479598675191902"><a name="p1479598675191902"></a><a name="p1479598675191902"></a>void **&nbsp;</p>
</td>
</tr>
<tr id="row302785264191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726606967191902"><a name="p726606967191902"></a><a name="p726606967191902"></a><a href="SimpleVector.md#a3e5edc51c8c7ef2536da2853986981ff">key</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p251220075191902"><a name="p251220075191902"></a><a name="p251220075191902"></a>VECTOR_Key&nbsp;</p>
</td>
</tr>
<tr id="row950368254191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p493190593191902"><a name="p493190593191902"></a><a name="p493190593191902"></a><a href="SimpleVector.md#a7661926c6a5d659ec2bff6533a7389fa">compare</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733481715191902"><a name="p1733481715191902"></a><a name="p1733481715191902"></a>VECTOR_Compare&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section950804675191902"></a>

## **Field Documentation**<a name="section471823310191902"></a>

## compare<a name="a7661926c6a5d659ec2bff6533a7389fa"></a>

```
VECTOR_Compare SimpleVector::compare
```

 **Description:**

Compares the sizes of key1 and key2, which are provided by users. The value  **1**  indicates that key1 is greater than key2, the value  **0**  indicates that key1 is equal to key2, and the value  **-1**  indicates that key1 is less than key2. The default value is  **NULL**. 

## data<a name="a4674672209ae411544383a5399aee85b"></a>

```
void** SimpleVector::data
```

 **Description:**

Data storage pointer 

## free<a name="a1ff1e71311df432f11fd2613cdbc1b16"></a>

```
int16 SimpleVector::free
```

 **Description:**

Number of data records that have been released. The initial value is  **0**. 

## key<a name="a3e5edc51c8c7ef2536da2853986981ff"></a>

```
VECTOR_Key SimpleVector::key
```

 **Description:**

Converts a data element into a key for comparison. The key is provided by users, and the default value is  **NULL**. 

## max<a name="a68140ca4cc59df48c63963f1eda3f35c"></a>

```
int16 SimpleVector::max
```

 **Description:**

Maximum number of data records that can be stored. The initial value is  **0**. 

## top<a name="ac699cefa0c1003b8babbe2c0ea3134db"></a>

```
int16 SimpleVector::top
```

 **Description:**

Peak value of the number of stored data records. The initial value is  **0**. 

