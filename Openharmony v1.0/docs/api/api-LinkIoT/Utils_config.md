# Utils\_config<a name="ZH-CN_TOPIC_0000001055515018"></a>

## **Overview**<a name="section1843701815191846"></a>

Represents the configuration file of the utils subsystem. 

Vendors can set their desired items in the configuration file.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1694083447191846"></a>

## Files<a name="files"></a>

<a name="table1890727405191846"></a>
<table><thead align="left"><tr id="row353183276191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1129897927191846"><a name="p1129897927191846"></a><a name="p1129897927191846"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1358928501191846"><a name="p1358928501191846"></a><a name="p1358928501191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row705672577191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904554909191846"><a name="p904554909191846"></a><a name="p904554909191846"></a><a href="utils_config-h.md">utils_config.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2048228695191846"><a name="p2048228695191846"></a><a name="p2048228695191846"></a>Represents the configuration file of the utils subsystem. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table448810751191846"></a>
<table><thead align="left"><tr id="row1082995962191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1907032404191846"><a name="p1907032404191846"></a><a name="p1907032404191846"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1973323971191846"><a name="p1973323971191846"></a><a name="p1973323971191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1797247169191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34374802191846"><a name="p34374802191846"></a><a name="p34374802191846"></a><a href="Utils_config.md#gad3d71669516ef0bb50e2b105507a6b29">FEATURE_KV_CACHE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350513232191846"><a name="p1350513232191846"></a><a name="p1350513232191846"></a>Specifies whether the KV store supports cache. </p>
</td>
</tr>
<tr id="row670155005191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p821752142191846"><a name="p821752142191846"></a><a name="p821752142191846"></a><a href="Utils_config.md#ga6c8469dfe973ac952cf40394bd2c160b">MAX_CACHE_SIZE</a>&nbsp;&nbsp;&nbsp;10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1055248294191846"><a name="p1055248294191846"></a><a name="p1055248294191846"></a>Indicates the number of data items that can be stored in the KV store cache. </p>
</td>
</tr>
<tr id="row654483972191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1862764481191846"><a name="p1862764481191846"></a><a name="p1862764481191846"></a><a href="Utils_config.md#ga4f258bd7d7d52c6770cce77f3e16ce72">MAX_KV_SUM</a>&nbsp;&nbsp;&nbsp;50</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1667135483191846"><a name="p1667135483191846"></a><a name="p1667135483191846"></a>Indicates the number of data items that can be stored for each application. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1101286426191846"></a>

## **Macro Definition Documentation**<a name="section862288960191846"></a>

## FEATURE\_KV\_CACHE<a name="gad3d71669516ef0bb50e2b105507a6b29"></a>

```
#define FEATURE_KV_CACHE
```

 **Description:**

Specifies whether the KV store supports cache. 

If this variable is defined, the KV store supports cache. Vendors determine whether to enable this feature. It is enabled by default. 

## MAX\_CACHE\_SIZE<a name="ga6c8469dfe973ac952cf40394bd2c160b"></a>

```
#define MAX_CACHE_SIZE   10
```

 **Description:**

Indicates the number of data items that can be stored in the KV store cache. 

Default value: 10 

## MAX\_KV\_SUM<a name="ga4f258bd7d7d52c6770cce77f3e16ce72"></a>

```
#define MAX_KV_SUM   50
```

 **Description:**

Indicates the number of data items that can be stored for each application. 

Default value: 50 

