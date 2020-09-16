# tms<a name="EN-US_TOPIC_0000001055198180"></a>

## **Overview**<a name="section927522708093538"></a>

**Related Modules:**

[TIME](en-us_topic_0000001054879478.md)

**Description:**

Describes CPU time of a process and its child processes. 

## **Summary**<a name="section298547471093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table976339550093538"></a>
<table><thead align="left"><tr id="row926698744093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1884241095093538"><a name="p1884241095093538"></a><a name="p1884241095093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p937446622093538"><a name="p937446622093538"></a><a name="p937446622093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row491803566093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p287670132093538"><a name="p287670132093538"></a><a name="p287670132093538"></a><a href="tms.md#a2522ba0b91f98baeb8f2b7249f367b7c">tms_utime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p704153314093538"><a name="p704153314093538"></a><a name="p704153314093538"></a>clock_t </p>
</td>
</tr>
<tr id="row568974398093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p990477133093538"><a name="p990477133093538"></a><a name="p990477133093538"></a><a href="tms.md#a60d97d80205a34858387314fb00cc4c0">tms_stime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1603443599093538"><a name="p1603443599093538"></a><a name="p1603443599093538"></a>clock_t </p>
</td>
</tr>
<tr id="row156009039093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1739332958093538"><a name="p1739332958093538"></a><a name="p1739332958093538"></a><a href="tms.md#adc1a7576a7287de70b7611047829ab6f">tms_cutime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985470188093538"><a name="p985470188093538"></a><a name="p985470188093538"></a>clock_t </p>
</td>
</tr>
<tr id="row1256889727093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1086417827093538"><a name="p1086417827093538"></a><a name="p1086417827093538"></a><a href="tms.md#ad21f41a18aff2813fe6154154f1f9522">tms_cstime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837961682093538"><a name="p837961682093538"></a><a name="p837961682093538"></a>clock_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1419161611093538"></a>

## **Field Documentation**<a name="section1865762855093538"></a>

## tms\_cstime<a name="ad21f41a18aff2813fe6154154f1f9522"></a>

```
clock_t tms::tms_cstime
```

 **Description:**

Child process's system time 

## tms\_cutime<a name="adc1a7576a7287de70b7611047829ab6f"></a>

```
clock_t tms::tms_cutime
```

 **Description:**

Child process's user time 

## tms\_stime<a name="a60d97d80205a34858387314fb00cc4c0"></a>

```
clock_t tms::tms_stime
```

 **Description:**

System time 

## tms\_utime<a name="a2522ba0b91f98baeb8f2b7249f367b7c"></a>

```
clock_t tms::tms_utime
```

 **Description:**

User time 

