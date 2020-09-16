# WifiIotFlashPartitionInfo<a name="EN-US_TOPIC_0000001054715063"></a>

## **Overview**<a name="section830134891191904"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Describes an entry in a flash partition table. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1085370107191904"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table71744788191904"></a>
<table><thead align="left"><tr id="row1467171073191904"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1499576484191904"><a name="p1499576484191904"></a><a name="p1499576484191904"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p552637054191904"><a name="p552637054191904"></a><a name="p552637054191904"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row139026019191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563284465191904"><a name="p1563284465191904"></a><a name="p1563284465191904"></a><a href="wifiiotflashpartitioninfo.md#a15e1bae27d30c2e172896a6e06f0b985">addr</a>: 24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45112654191904"><a name="p45112654191904"></a><a name="p45112654191904"></a>unsigned int </p>
</td>
</tr>
<tr id="row1081659668191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1631959337191904"><a name="p1631959337191904"></a><a name="p1631959337191904"></a><a href="wifiiotflashpartitioninfo.md#a292b0ba43e300582b6386147df706dce">id</a>: 7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751693897191904"><a name="p751693897191904"></a><a name="p751693897191904"></a>unsigned int </p>
</td>
</tr>
<tr id="row804343942191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1987121546191904"><a name="p1987121546191904"></a><a name="p1987121546191904"></a><a href="wifiiotflashpartitioninfo.md#a4cf8fbe5e14481e2756fbac07bd9fae0">dir</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1724781905191904"><a name="p1724781905191904"></a><a name="p1724781905191904"></a>unsigned int </p>
</td>
</tr>
<tr id="row890124548191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442486640191904"><a name="p442486640191904"></a><a name="p442486640191904"></a><a href="wifiiotflashpartitioninfo.md#ad08e5d1f89cf2a9953ea62515ed98160">size</a>: 24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675437366191904"><a name="p675437366191904"></a><a name="p675437366191904"></a>unsigned int </p>
</td>
</tr>
<tr id="row1120539936191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1132989049191904"><a name="p1132989049191904"></a><a name="p1132989049191904"></a><a href="wifiiotflashpartitioninfo.md#a770fa3b6cdd34ca0f60de1f10f4f647c">reserve</a>: 8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007229934191904"><a name="p2007229934191904"></a><a name="p2007229934191904"></a>unsigned int </p>
</td>
</tr>
<tr id="row2129350402191904"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844083830191904"><a name="p844083830191904"></a><a name="p844083830191904"></a><a href="wifiiotflashpartitioninfo.md#ae2d2789851df733e469574a8d1c7436a">addition</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852016843191904"><a name="p852016843191904"></a><a name="p852016843191904"></a>unsigned int </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section685331230191904"></a>

## **Field Documentation**<a name="section1109557315191904"></a>

## addition<a name="ae2d2789851df733e469574a8d1c7436a"></a>

```
unsigned int WifiIotFlashPartitionInfo::addition
```

 **Description:**

Custom flash partition information 

## addr<a name="a15e1bae27d30c2e172896a6e06f0b985"></a>

```
unsigned int WifiIotFlashPartitionInfo::addr
```

 **Description:**

Address of a flash partition. The value is 16 MB. If the address is in reverse order, the value is the end low address. 

## dir<a name="a4cf8fbe5e14481e2756fbac07bd9fae0"></a>

```
unsigned int WifiIotFlashPartitionInfo::dir
```

 **Description:**

Storage direction of the flash partition. The value  **0**  indicates the regular order, and  **1**  indicates the reverse order. 

## id<a name="a292b0ba43e300582b6386147df706dce"></a>

```
unsigned int WifiIotFlashPartitionInfo::id
```

 **Description:**

Flash partition ID 

## reserve<a name="a770fa3b6cdd34ca0f60de1f10f4f647c"></a>

```
unsigned int WifiIotFlashPartitionInfo::reserve
```

 **Description:**

Padding bit 

## size<a name="ad08e5d1f89cf2a9953ea62515ed98160"></a>

```
unsigned int WifiIotFlashPartitionInfo::size
```

 **Description:**

Size of the flash partition 

