# timeb<a name="ZH-CN_TOPIC_0000001054879582"></a>

## **Overview**<a name="section1239581725093538"></a>

**Related Modules:**

[TIME](zh-cn_topic_0000001054879478.md)

**Description:**

Describes the time, accurate to millisecond. 

## **Summary**<a name="section1328968830093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table385226102093538"></a>
<table><thead align="left"><tr id="row1578918808093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p722719667093538"><a name="p722719667093538"></a><a name="p722719667093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1926247550093538"><a name="p1926247550093538"></a><a name="p1926247550093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row388147229093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091846420093538"><a name="p2091846420093538"></a><a name="p2091846420093538"></a><a href="timeb.md#a6f298f9fb1327aba639d457f2989b859">time</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343386499093538"><a name="p343386499093538"></a><a name="p343386499093538"></a>time_t&nbsp;</p>
</td>
</tr>
<tr id="row400602972093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p167252260093538"><a name="p167252260093538"></a><a name="p167252260093538"></a><a href="timeb.md#aa459454ab48c84566d6b1fa72bafebe7">millitm</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1667502269093538"><a name="p1667502269093538"></a><a name="p1667502269093538"></a>unsigned short&nbsp;</p>
</td>
</tr>
<tr id="row828001166093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977499506093538"><a name="p977499506093538"></a><a name="p977499506093538"></a><a href="timeb.md#aa1c6a12ca2a9150c5002bdfb0331bf0b">timezone</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989267538093538"><a name="p989267538093538"></a><a name="p989267538093538"></a>short&nbsp;</p>
</td>
</tr>
<tr id="row1891619161093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p426310741093538"><a name="p426310741093538"></a><a name="p426310741093538"></a><a href="timeb.md#a951ede614d33eed486224c381df15f4e">dstflag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495737605093538"><a name="p495737605093538"></a><a name="p495737605093538"></a>short&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1252638936093538"></a>

## **Field Documentation**<a name="section1701178996093538"></a>

## dstflag<a name="a951ede614d33eed486224c381df15f4e"></a>

```
short timeb::dstflag
```

 **Description:**

Whether DST is observed 

## millitm<a name="aa459454ab48c84566d6b1fa72bafebe7"></a>

```
unsigned short timeb::millitm
```

 **Description:**

Number of milliseconds in the current time 

## time<a name="a6f298f9fb1327aba639d457f2989b859"></a>

```
time_t timeb::time
```

 **Description:**

Total number of seconds elapsed since January 1, 1970 00:00:00 \(UTC\) 

## timezone<a name="aa1c6a12ca2a9150c5002bdfb0331bf0b"></a>

```
short timeb::timezone
```

 **Description:**

Time zone 

