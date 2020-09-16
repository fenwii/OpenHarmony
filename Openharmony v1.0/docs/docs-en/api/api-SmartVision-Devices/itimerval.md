# itimerval<a name="EN-US_TOPIC_0000001054799645"></a>

## **Overview**<a name="section2080369893093538"></a>

**Related Modules:**

[TIME-SYS](en-us_topic_0000001055078085.md)

**Description:**

Describes a timer. 

## **Summary**<a name="section1142350768093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2021639423093538"></a>
<table><thead align="left"><tr id="row558688224093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1072587408093538"><a name="p1072587408093538"></a><a name="p1072587408093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2105009117093538"><a name="p2105009117093538"></a><a name="p2105009117093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1532849109093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665390251093538"><a name="p665390251093538"></a><a name="p665390251093538"></a><a href="itimerval.md#ae37e5edff9a3efa2841f5e614e2c2efb">it_interval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871340386093538"><a name="p1871340386093538"></a><a name="p1871340386093538"></a>struct <a href="timeval.md">timeval</a> </p>
</td>
</tr>
<tr id="row2009426634093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851175126093538"><a name="p1851175126093538"></a><a name="p1851175126093538"></a><a href="itimerval.md#a2dc8aae1b0b2e57a7ec8f7d33834495d">it_value</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1772505243093538"><a name="p1772505243093538"></a><a name="p1772505243093538"></a>struct <a href="timeval.md">timeval</a> </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1260361936093538"></a>

## **Field Documentation**<a name="section210263653093538"></a>

## it\_interval<a name="ae37e5edff9a3efa2841f5e614e2c2efb"></a>

```
struct [timeval](timeval.md) itimerval::it_interval
```

 **Description:**

Timer interval. The value  **0**  indicates a one-shot timer. 

## it\_value<a name="a2dc8aae1b0b2e57a7ec8f7d33834495d"></a>

```
struct [timeval](timeval.md) itimerval::it_value
```

 **Description:**

Timer value 

