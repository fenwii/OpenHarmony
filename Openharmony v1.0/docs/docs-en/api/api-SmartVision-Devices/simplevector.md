# SimpleVector<a name="EN-US_TOPIC_0000001054598199"></a>

## **Overview**<a name="section58580887093537"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Defines the simplified vector class, which is extended by four elements. 

This class is applicable to the C language development scenario where the data volume is small and dynamic expansion is required. 

## **Summary**<a name="section110296731093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1389855274093537"></a>
<table><thead align="left"><tr id="row561221744093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p366578840093537"><a name="p366578840093537"></a><a name="p366578840093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p574936315093537"><a name="p574936315093537"></a><a name="p574936315093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row694861042093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1465704935093537"><a name="p1465704935093537"></a><a name="p1465704935093537"></a><a href="simplevector.md#a68140ca4cc59df48c63963f1eda3f35c">max</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p885332762093537"><a name="p885332762093537"></a><a name="p885332762093537"></a>int16 </p>
</td>
</tr>
<tr id="row1173663396093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1777222871093537"><a name="p1777222871093537"></a><a name="p1777222871093537"></a><a href="simplevector.md#ac699cefa0c1003b8babbe2c0ea3134db">top</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p329177610093537"><a name="p329177610093537"></a><a name="p329177610093537"></a>int16 </p>
</td>
</tr>
<tr id="row2072992746093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037843975093537"><a name="p2037843975093537"></a><a name="p2037843975093537"></a><a href="simplevector.md#a1ff1e71311df432f11fd2613cdbc1b16">free</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p507309671093537"><a name="p507309671093537"></a><a name="p507309671093537"></a>int16 </p>
</td>
</tr>
<tr id="row354275890093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685897098093537"><a name="p1685897098093537"></a><a name="p1685897098093537"></a><a href="simplevector.md#a4674672209ae411544383a5399aee85b">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363667010093537"><a name="p1363667010093537"></a><a name="p1363667010093537"></a>void ** </p>
</td>
</tr>
<tr id="row341919456093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p515992841093537"><a name="p515992841093537"></a><a name="p515992841093537"></a><a href="simplevector.md#a3e5edc51c8c7ef2536da2853986981ff">key</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647264670093537"><a name="p647264670093537"></a><a name="p647264670093537"></a>VECTOR_Key </p>
</td>
</tr>
<tr id="row2022612634093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152124569093537"><a name="p152124569093537"></a><a name="p152124569093537"></a><a href="simplevector.md#a7661926c6a5d659ec2bff6533a7389fa">compare</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p43893625093537"><a name="p43893625093537"></a><a name="p43893625093537"></a>VECTOR_Compare </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1058350055093537"></a>

## **Field Documentation**<a name="section891374100093537"></a>

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

