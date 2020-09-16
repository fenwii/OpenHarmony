# WifiModule<a name="ZH-CN_TOPIC_0000001054718169"></a>

## **Overview**<a name="section751494372093537"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Defines the WLAN module. 

The structure contains private data, APIs, module configurations, a module that communicates with user-level processes, and WLAN features.

**Since:**

1.0

## **Summary**<a name="section2012042037093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1904493751093537"></a>
<table><thead align="left"><tr id="row1963792943093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p371476430093537"><a name="p371476430093537"></a><a name="p371476430093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1523629343093537"><a name="p1523629343093537"></a><a name="p1523629343093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2127526392093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p990988185093537"><a name="p990988185093537"></a><a name="p990988185093537"></a><a href="WLAN.md#gab8c955bd3dd2cb79c3c0c3dfdc3b08f5">modulePrivate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p276199024093537"><a name="p276199024093537"></a><a name="p276199024093537"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row953428140093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1814918554093537"><a name="p1814918554093537"></a><a name="p1814918554093537"></a><a href="WLAN.md#ga8666b5068c46aa89a3cae49b7a31c224">iface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p408182664093537"><a name="p408182664093537"></a><a name="p408182664093537"></a>struct <a href="WifiModuleIface.md">WifiModuleIface</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1575450011093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894866296093537"><a name="p894866296093537"></a><a name="p894866296093537"></a><a href="WLAN.md#gaa54566af9b7dda68e119649b3510c858">moduleConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p347154537093537"><a name="p347154537093537"></a><a name="p347154537093537"></a>struct <a href="WifiModuleConfig.md">WifiModuleConfig</a>&nbsp;</p>
</td>
</tr>
<tr id="row1610607216093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p865966912093537"><a name="p865966912093537"></a><a name="p865966912093537"></a><a href="WLAN.md#ga347d5b39c9a96835ae85358ba0895cc3">feList</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p127023223093537"><a name="p127023223093537"></a><a name="p127023223093537"></a>struct <a href="WifiFeatureList.md">WifiFeatureList</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

