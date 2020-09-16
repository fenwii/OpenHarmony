# itimerspec<a name="ZH-CN_TOPIC_0000001055039562"></a>

## **Overview**<a name="section115829779093538"></a>

**Related Modules:**

[TIME](zh-cn_topic_0000001054879478.md)

**Description:**

Sets a timer. 

## **Summary**<a name="section1948660128093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table301618212093538"></a>
<table><thead align="left"><tr id="row603186155093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1274043331093538"><a name="p1274043331093538"></a><a name="p1274043331093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p386738490093538"><a name="p386738490093538"></a><a name="p386738490093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1614808679093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p305066662093538"><a name="p305066662093538"></a><a name="p305066662093538"></a><a href="itimerspec.md#a27cedae552e2b2fe0993c1b2c4ff1889">it_interval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p251977946093538"><a name="p251977946093538"></a><a name="p251977946093538"></a>struct <a href="timespec.md">timespec</a>&nbsp;</p>
</td>
</tr>
<tr id="row15776621093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p619502835093538"><a name="p619502835093538"></a><a name="p619502835093538"></a><a href="itimerspec.md#a754dda918053251c24558b07571d6e8f">it_value</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p102722309093538"><a name="p102722309093538"></a><a name="p102722309093538"></a>struct <a href="timespec.md">timespec</a>&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2109962747093538"></a>

## **Field Documentation**<a name="section371662540093538"></a>

## it\_interval<a name="a27cedae552e2b2fe0993c1b2c4ff1889"></a>

```
struct [timespec](timespec.md) itimerspec::it_interval
```

 **Description:**

Interval between two consecutive timer triggers 

## it\_value<a name="a754dda918053251c24558b07571d6e8f"></a>

```
struct [timespec](timespec.md) itimerspec::it_value
```

 **Description:**

Initial timeout duration 

