# hdf\_base.h<a name="EN-US_TOPIC_0000001055078107"></a>

## **Overview**<a name="section143162094093525"></a>

**Related Modules:**

[DriverUtils](driverutils.md)

**Description:**

Declares driver common types, including the enumerated values returned by the function and the macro for obtaining the array size. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1046580048093525"></a>

## Macros<a name="define-members"></a>

<a name="table1737256895093525"></a>
<table><thead align="left"><tr id="row2118604838093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1322089123093525"><a name="p1322089123093525"></a><a name="p1322089123093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p635166416093525"><a name="p635166416093525"></a><a name="p635166416093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1393879724093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496276738093525"><a name="p496276738093525"></a><a name="p496276738093525"></a><a href="hdf_base-h.md#aa6370acad4a8ca2031370c833f2ff51f">HDF_BSP_ERR_START</a>   (-100)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row827781206093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730909232093525"><a name="p730909232093525"></a><a name="p730909232093525"></a><a href="hdf_base-h.md#a4891335de9aeb07e88903a5e2931002e">HDF_BSP_ERR_NUM</a>(v)   (<a href="hdf_base-h.md#aa6370acad4a8ca2031370c833f2ff51f">HDF_BSP_ERR_START</a> + (v))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row566130850093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875782812093525"><a name="p1875782812093525"></a><a name="p1875782812093525"></a><a href="hdf_base-h.md#afdce96b5c938acadb74cdcb09d53cfaf">HDF_DEV_ERR_START</a>   (-200)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row988444295093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328098433093525"><a name="p328098433093525"></a><a name="p328098433093525"></a><a href="hdf_base-h.md#a6d41cf53f1ba974869f4d992563e413b">HDF_DEV_ERR_NUM</a>(v)   (<a href="hdf_base-h.md#afdce96b5c938acadb74cdcb09d53cfaf">HDF_DEV_ERR_START</a> + (v))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row636327610093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1037030001093525"><a name="p1037030001093525"></a><a name="p1037030001093525"></a><a href="driverutils.md#ga4dc11d1abeb6b0d2a40e20a553f491f4">HDF_WAIT_FOREVER</a>   0xFFFFFFFF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756235527093525"><a name="p756235527093525"></a><a name="p756235527093525"></a>Indicates that the function keeps waiting to obtain a semaphore or mutex. </p>
</td>
</tr>
<tr id="row1557370852093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2124546032093525"><a name="p2124546032093525"></a><a name="p2124546032093525"></a><a href="driverutils.md#ga5255c6a1e2a87df682c1c0ed36fc1b2f">HDF_ARRAY_SIZE</a>(a)   (sizeof(a) / sizeof((a)[0]))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1865018801093525"><a name="p1865018801093525"></a><a name="p1865018801093525"></a>Defines the array size. </p>
</td>
</tr>
<tr id="row1541401837093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1286312222093525"><a name="p1286312222093525"></a><a name="p1286312222093525"></a><a href="driverutils.md#ga8f2520dfc5a6cd0bac044845318b020c">HDF_KILO_UNIT</a>   1000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105498480093525"><a name="p2105498480093525"></a><a name="p2105498480093525"></a>Defines a time conversion unit, for example, the unit for converting from second to millisecond. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table748401408093525"></a>
<table><thead align="left"><tr id="row1069882028093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1523920182093525"><a name="p1523920182093525"></a><a name="p1523920182093525"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1621099188093525"><a name="p1621099188093525"></a><a name="p1621099188093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1073408598093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894603558093525"><a name="p894603558093525"></a><a name="p894603558093525"></a><a href="driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67">HDF_STATUS</a> {   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a66cefc3d8cb74728358899034d8d141f">HDF_SUCCESS</a> = 0, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a454a8a08dd1a4b166b2aff6af90266d0">HDF_FAILURE</a> = -1, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67ac6e0c4313436d7222b7dc9bf21e092ed">HDF_ERR_NOT_SUPPORT</a> = -2, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a87e9e0ca4600bc8967556e668abf6718">HDF_ERR_INVALID_PARAM</a> = -3,   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a14a42b17e53bbd65b4f15d56df41ae70">HDF_ERR_INVALID_OBJECT</a> = -4, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0ad904f070baaf23e6a4bf8fbdf928f5">HDF_ERR_MALLOC_FAIL</a> = -6, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0c698c789d0dec0b054d5f1cf10003d7">HDF_ERR_TIMEOUT</a> = -7, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a77fd634e04dc131c2ca0435372c1f13b">HDF_ERR_THREAD_CREATE_FAIL</a> = -10,   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a44e8f39984cb2b4f7790b2ceab8b7670">HDF_ERR_QUEUE_FULL</a> = -15, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a9c98586b0a30928afdd3f8fee5083e9b">HDF_ERR_DEVICE_BUSY</a> = -16, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a79c1aa5fb70b16b6b62b9f92e06b76d8">HDF_ERR_IO</a> = -17, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a140804bae8a12c1ae2f3bbb07dd942d9">HDF_ERR_BAD_FD</a> = -18,   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0d6ae6ce941fe02f540dc38897e9aac6">HDF_BSP_ERR_OP</a> = HDF_BSP_ERR_NUM(-1), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a6005454a71463ece52e0aa518f5032c2">HDF_ERR_BSP_PLT_API_ERR</a> = HDF_BSP_ERR_NUM(-2), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a520a898768b87a190ead33e693196946">HDF_PAL_ERR_DEV_CREATE</a> = HDF_BSP_ERR_NUM(-3), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0cd3b31917d5ebb591bcbc7bd1099d55">HDF_PAL_ERR_INNER</a> = HDF_BSP_ERR_NUM(-4),   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67ac7475bfa5f540b4324e551f5e7d7b2bd">HDF_DEV_ERR_NO_MEMORY</a> = HDF_DEV_ERR_NUM(-1), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67abde6ef565b453d3fc7734338db4db62d">HDF_DEV_ERR_NO_DEVICE</a> = HDF_DEV_ERR_NUM(-2), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a7d31e3b26c26010b0b1cf64596982005">HDF_DEV_ERR_NO_DEVICE_SERVICE</a> = HDF_DEV_ERR_NUM(-3), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a50fbd0d6fba63406ee384eb0c2ddaab5">HDF_DEV_ERR_DEV_INIT_FAIL</a> = HDF_DEV_ERR_NUM(-4),   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a318d4f725c1e85fb8c55acac7ed80112">HDF_DEV_ERR_PUBLISH_FAIL</a> = HDF_DEV_ERR_NUM(-5), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a676ff9d5ba402e93f44465d309cf4f94">HDF_DEV_ERR_ATTACHDEV_FAIL</a> = HDF_DEV_ERR_NUM(-6), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a4cfc60685fac5ac921651fdaea845c1a">HDF_DEV_ERR_NODATA</a> = HDF_DEV_ERR_NUM(-7), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67adbecc6285acfc5030abff4612b9cf916">HDF_DEV_ERR_NORANGE</a> = HDF_DEV_ERR_NUM(-8),   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67aace3a9148b526f670290e7829f3dd9df">HDF_DEV_ERR_OP</a> = HDF_DEV_ERR_NUM(-10) }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1950238103093525"><a name="p1950238103093525"></a><a name="p1950238103093525"></a>Enumerates HDF return value types. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section937485289093525"></a>

## **Macro Definition Documentation**<a name="section253802237093525"></a>

## HDF\_BSP\_ERR\_NUM<a name="a4891335de9aeb07e88903a5e2931002e"></a>

```
#define HDF_BSP_ERR_NUM( v)   ([HDF_BSP_ERR_START](hdf_base-h.md#aa6370acad4a8ca2031370c833f2ff51f) + (v))
```

 **Description:**

Defines the BSP module error codes. 

## HDF\_BSP\_ERR\_START<a name="aa6370acad4a8ca2031370c833f2ff51f"></a>

```
#define HDF_BSP_ERR_START   (-100)
```

 **Description:**

Defines the start of the Board Support Package \(BSP\) module error codes. 

## HDF\_DEV\_ERR\_NUM<a name="a6d41cf53f1ba974869f4d992563e413b"></a>

```
#define HDF_DEV_ERR_NUM( v)   ([HDF_DEV_ERR_START](hdf_base-h.md#afdce96b5c938acadb74cdcb09d53cfaf) + (v))
```

 **Description:**

Defines the device module error codes. 

## HDF\_DEV\_ERR\_START<a name="afdce96b5c938acadb74cdcb09d53cfaf"></a>

```
#define HDF_DEV_ERR_START   (-200)
```

 **Description:**

Defines the start of the device module error codes. 

