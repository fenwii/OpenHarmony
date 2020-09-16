# samgr\_lite.h<a name="EN-US_TOPIC_0000001055075071"></a>

## **Overview**<a name="section696965233090253"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Manages system capabilities. 

This is used when services, features, and functions are registered with and discovered by Samgr. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section449916741090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table514640323090253"></a>
<table><thead align="left"><tr id="row1812624726090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p627255482090253"><a name="p627255482090253"></a><a name="p627255482090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2064010266090253"><a name="p2064010266090253"></a><a name="p2064010266090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row53220462090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1767198632090253"><a name="p1767198632090253"></a><a name="p1767198632090253"></a><a href="samgrlite.md">SamgrLite</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1861477102090253"><a name="p1861477102090253"></a><a name="p1861477102090253"></a>Represents the system ability management class. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1072769486090253"></a>
<table><thead align="left"><tr id="row259248365090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1607994552090253"><a name="p1607994552090253"></a><a name="p1607994552090253"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1785401428090253"><a name="p1785401428090253"></a><a name="p1785401428090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1314410697090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1117200671090253"><a name="p1117200671090253"></a><a name="p1117200671090253"></a><a href="samgr.md#gadc00f0568236d4538c867ed7194d8960">BOOTSTRAP_SERVICE</a>   "Bootstrap"</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p110792691090253"><a name="p110792691090253"></a><a name="p110792691090253"></a>Starts a bootstrap service, which is used by samgr and implemented by system service developers. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1427059114090253"></a>
<table><thead align="left"><tr id="row84049056090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2012675259090253"><a name="p2012675259090253"></a><a name="p2012675259090253"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p685492771090253"><a name="p685492771090253"></a><a name="p685492771090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1914925278090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725433223090253"><a name="p725433223090253"></a><a name="p725433223090253"></a><a href="samgr.md#gadc486c8d2698eab8a9f26f0eb6cc63c8">BootMessage</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p936784254090253"><a name="p936784254090253"></a><a name="p936784254090253"></a>typedef enum <a href="samgr.md#gaf39e482610dca95f0dba85613755eb40">BootMessage</a> </p>
<p id="p2024967608090253"><a name="p2024967608090253"></a><a name="p2024967608090253"></a>Enumerates the IDs of the message to be processed for starting the bootstrap service. </p>
</td>
</tr>
<tr id="row69240873090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993305250090253"><a name="p993305250090253"></a><a name="p993305250090253"></a><a href="samgr.md#gaad729fe4f36b7b42a122349af334fb28">SamgrLite</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2129538984090253"><a name="p2129538984090253"></a><a name="p2129538984090253"></a>typedef struct <a href="samgrlite.md">SamgrLite</a> </p>
<p id="p145519679090253"><a name="p145519679090253"></a><a name="p145519679090253"></a>Represents the system ability management class. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1622005629090253"></a>
<table><thead align="left"><tr id="row1503453677090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1418597615090253"><a name="p1418597615090253"></a><a name="p1418597615090253"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1334054930090253"><a name="p1334054930090253"></a><a name="p1334054930090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1031422213090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935341135090253"><a name="p1935341135090253"></a><a name="p1935341135090253"></a><a href="samgr.md#gaf39e482610dca95f0dba85613755eb40">BootMessage</a> { <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40aee5f1e07de9a8e2e167f97dd2cc0c2d7">BOOT_SYS_COMPLETED</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a8b0613200e2b05f9309175fe9bd30ca1">BOOT_APP_COMPLETED</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a9aff5f5b8378e898076ee326da5cd572">BOOT_REG_SERVICE</a>, <a href="samgr.md#ggaf39e482610dca95f0dba85613755eb40a515e06399df48a6d93435e7c30745eec">BOOTSTRAP_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p193149598090253"><a name="p193149598090253"></a><a name="p193149598090253"></a>Enumerates the IDs of the message to be processed for starting the bootstrap service. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1829830163090253"></a>
<table><thead align="left"><tr id="row1781647726090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p206544876090253"><a name="p206544876090253"></a><a name="p206544876090253"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p789173288090253"><a name="p789173288090253"></a><a name="p789173288090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1295335253090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062239812090253"><a name="p1062239812090253"></a><a name="p1062239812090253"></a><a href="samgr.md#ga21f168d6f97d6991115ae1cf8bbd8deb">SAMGR_GetInstance</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229329515090253"><a name="p1229329515090253"></a><a name="p1229329515090253"></a><a href="samgrlite.md">SamgrLite</a> * </p>
<p id="p1347353119090253"><a name="p1347353119090253"></a><a name="p1347353119090253"></a>Obtains the singleton Samgr instance. </p>
</td>
</tr>
<tr id="row633634734090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p967102476090253"><a name="p967102476090253"></a><a name="p967102476090253"></a><a href="samgr.md#ga756ac1f5376c72aa5d14b855a302d7b6">SAMGR_Bootstrap</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466680898090253"><a name="p1466680898090253"></a><a name="p1466680898090253"></a>void </p>
<p id="p449143157090253"><a name="p449143157090253"></a><a name="p449143157090253"></a>Starts system services and features. </p>
</td>
</tr>
</tbody>
</table>

