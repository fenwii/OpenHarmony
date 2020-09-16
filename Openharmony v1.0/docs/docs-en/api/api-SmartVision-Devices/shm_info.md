# shm\_info<a name="EN-US_TOPIC_0000001054479611"></a>

## **Overview**<a name="section1672785788093538"></a>

**Related Modules:**

[MEM](en-us_topic_0000001055518034.md)

**Description:**

Describes system resource information about the shared memory. 

## **Summary**<a name="section814576518093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table449437193093538"></a>
<table><thead align="left"><tr id="row1806523370093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1750914627093538"><a name="p1750914627093538"></a><a name="p1750914627093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2005467569093538"><a name="p2005467569093538"></a><a name="p2005467569093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1674404748093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817262537093538"><a name="p1817262537093538"></a><a name="p1817262537093538"></a><a href="shm_info.md#aa2de99231240b0e9e36cb1720bba0ef5">__used_ids</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p706503774093538"><a name="p706503774093538"></a><a name="p706503774093538"></a>int </p>
</td>
</tr>
<tr id="row1824459761093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1582138130093538"><a name="p1582138130093538"></a><a name="p1582138130093538"></a><a href="shm_info.md#a68b58013a245638488a89c6026a757a5">shm_tot</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649921206093538"><a name="p649921206093538"></a><a name="p649921206093538"></a>unsigned long </p>
</td>
</tr>
<tr id="row287529763093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p426284264093538"><a name="p426284264093538"></a><a name="p426284264093538"></a><a href="shm_info.md#a677b785fd7c65a72a2a3e5c361ced94f">shm_rss</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2115824094093538"><a name="p2115824094093538"></a><a name="p2115824094093538"></a>unsigned long </p>
</td>
</tr>
<tr id="row2016084985093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898504398093538"><a name="p898504398093538"></a><a name="p898504398093538"></a><a href="shm_info.md#a55655441c2480741960372b4ae5aa76b">shm_swp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601576732093538"><a name="p601576732093538"></a><a name="p601576732093538"></a>unsigned long </p>
</td>
</tr>
<tr id="row611398233093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196142302093538"><a name="p196142302093538"></a><a name="p196142302093538"></a><a href="shm_info.md#a994182b446373fe20ba4392fac1608df">__swap_attempts</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p438966992093538"><a name="p438966992093538"></a><a name="p438966992093538"></a>unsigned long </p>
</td>
</tr>
<tr id="row1198261781093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p531525287093538"><a name="p531525287093538"></a><a name="p531525287093538"></a><a href="shm_info.md#a612f7346d1f84cd756fa9ee4ba68cc14">__swap_successes</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959123138093538"><a name="p959123138093538"></a><a name="p959123138093538"></a>unsigned long </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1104858548093538"></a>

## **Field Documentation**<a name="section1681939417093538"></a>

## \_\_swap\_attempts<a name="a994182b446373fe20ba4392fac1608df"></a>

```
unsigned long shm_info::__swap_attempts
```

 **Description:**

Number of swap attempts 

## \_\_swap\_successes<a name="a612f7346d1f84cd756fa9ee4ba68cc14"></a>

```
unsigned long shm_info::__swap_successes
```

 **Description:**

Number of successful swap attempts 

## \_\_used\_ids<a name="aa2de99231240b0e9e36cb1720bba0ef5"></a>

```
int shm_info::__used_ids
```

 **Description:**

Number of existing shared memory segments 

## shm\_rss<a name="a677b785fd7c65a72a2a3e5c361ced94f"></a>

```
unsigned long shm_info::shm_rss
```

 **Description:**

Number of resident shared memory pages 

## shm\_swp<a name="a55655441c2480741960372b4ae5aa76b"></a>

```
unsigned long shm_info::shm_swp
```

 **Description:**

Number of shared memory pages in the swap partition 

## shm\_tot<a name="a68b58013a245638488a89c6026a757a5"></a>

```
unsigned long shm_info::shm_tot
```

 **Description:**

Total number of shared memory pages 

