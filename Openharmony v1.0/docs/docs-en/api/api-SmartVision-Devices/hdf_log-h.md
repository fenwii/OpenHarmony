# hdf\_log.h<a name="EN-US_TOPIC_0000001054918123"></a>

## **Overview**<a name="section1518799958093525"></a>

**Related Modules:**

[DriverUtils](driverutils.md)

**Description:**

Declares log printing functions of the driver module. This module provides functions for printing logs at the verbose, debug, information, warning, and error levels. 

To use these functions, you must define  **HDF\_LOG\_TAG**, for example, \#define HDF\_LOG\_TAG evt.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1710176096093525"></a>

## Macros<a name="define-members"></a>

<a name="table474190013093525"></a>
<table><thead align="left"><tr id="row1540299786093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1375405289093525"><a name="p1375405289093525"></a><a name="p1375405289093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p831903220093525"><a name="p831903220093525"></a><a name="p831903220093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2016145204093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567601529093525"><a name="p1567601529093525"></a><a name="p1567601529093525"></a><a href="driverutils.md#ga7e862bda9f0b95d1628f6f62598f1f42">LOG_TAG_MARK_EXTEND</a>(HDF_TAG)   #HDF_TAG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row2052661276093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1717711828093525"><a name="p1717711828093525"></a><a name="p1717711828093525"></a><a href="driverutils.md#ga4abebfca1aaeb8125f85800425caf304">HDF_LOGV</a>(fmt, arg...)   <a href="en-us_topic_0000001054799545.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:V/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201297239093525"><a name="p1201297239093525"></a><a name="p1201297239093525"></a>Prints logs at the verbose level. </p>
</td>
</tr>
<tr id="row1026030118093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571404864093525"><a name="p1571404864093525"></a><a name="p1571404864093525"></a><a href="driverutils.md#gaa0411582f697619cdb045ae61ac42539">HDF_LOGD</a>(fmt, arg...)   <a href="en-us_topic_0000001054799545.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:D/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1903141057093525"><a name="p1903141057093525"></a><a name="p1903141057093525"></a>Prints logs at the debug level. </p>
</td>
</tr>
<tr id="row1310544128093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p656632918093525"><a name="p656632918093525"></a><a name="p656632918093525"></a><a href="driverutils.md#ga369d56841d17e6908fc6885fcb814b80">HDF_LOGI</a>(fmt, arg...)   <a href="en-us_topic_0000001054799545.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:I/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2142371427093525"><a name="p2142371427093525"></a><a name="p2142371427093525"></a>Prints logs at the information level. </p>
</td>
</tr>
<tr id="row1863126406093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256499208093525"><a name="p256499208093525"></a><a name="p256499208093525"></a><a href="driverutils.md#ga72f232dade88b85aff2d8c0e42b82df0">HDF_LOGW</a>(fmt, arg...)   <a href="en-us_topic_0000001054799545.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:W/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508076966093525"><a name="p508076966093525"></a><a name="p508076966093525"></a>Prints logs at the warning level. </p>
</td>
</tr>
<tr id="row1258814462093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898504596093525"><a name="p1898504596093525"></a><a name="p1898504596093525"></a><a href="driverutils.md#gaacd0eb778948960a7f97af155287ce8c">HDF_LOGE</a>(fmt, arg...)   <a href="en-us_topic_0000001054799545.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:E/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443792214093525"><a name="p1443792214093525"></a><a name="p1443792214093525"></a>Prints logs at the error level. </p>
</td>
</tr>
</tbody>
</table>

