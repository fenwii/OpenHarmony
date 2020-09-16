# Utils\_config<a name="ZH-CN_TOPIC_0000001055678050"></a>

## **Overview**<a name="section1790453951093523"></a>

Represents the configuration file of the utils subsystem. 

Vendors can set their desired items in the configuration file.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1137910732093523"></a>

## Files<a name="files"></a>

<a name="table862764260093523"></a>
<table><thead align="left"><tr id="row1917513445093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p649377550093523"><a name="p649377550093523"></a><a name="p649377550093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p87477274093523"><a name="p87477274093523"></a><a name="p87477274093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1680994110093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p421011102093523"><a name="p421011102093523"></a><a name="p421011102093523"></a><a href="utils_config-h.md">utils_config.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p80963278093523"><a name="p80963278093523"></a><a name="p80963278093523"></a>Represents the configuration file of the utils subsystem. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1652114126093523"></a>
<table><thead align="left"><tr id="row1348853757093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p410276341093523"><a name="p410276341093523"></a><a name="p410276341093523"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p634250847093523"><a name="p634250847093523"></a><a name="p634250847093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1144836931093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1996128270093523"><a name="p1996128270093523"></a><a name="p1996128270093523"></a><a href="Utils_config.md#gad3d71669516ef0bb50e2b105507a6b29">FEATURE_KV_CACHE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873605413093523"><a name="p873605413093523"></a><a name="p873605413093523"></a>Specifies whether the KV store supports cache. </p>
</td>
</tr>
<tr id="row889740115093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467218612093523"><a name="p1467218612093523"></a><a name="p1467218612093523"></a><a href="Utils_config.md#ga6c8469dfe973ac952cf40394bd2c160b">MAX_CACHE_SIZE</a>&nbsp;&nbsp;&nbsp;10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832415633093523"><a name="p832415633093523"></a><a name="p832415633093523"></a>Indicates the number of data items that can be stored in the KV store cache. </p>
</td>
</tr>
<tr id="row204600337093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969752162093523"><a name="p1969752162093523"></a><a name="p1969752162093523"></a><a href="Utils_config.md#ga4f258bd7d7d52c6770cce77f3e16ce72">MAX_KV_SUM</a>&nbsp;&nbsp;&nbsp;50</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1210161734093523"><a name="p1210161734093523"></a><a name="p1210161734093523"></a>Indicates the number of data items that can be stored for each application. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section845860777093523"></a>

## **Macro Definition Documentation**<a name="section1167482200093523"></a>

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

