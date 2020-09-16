# Power<a name="EN-US_TOPIC_0000001055075067"></a>

## **Overview**<a name="section1698468874191846"></a>

Provides device power management functions. 

This module is used to reboot the device and set low power consumption for the device. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1156846601191846"></a>

## Files<a name="files"></a>

<a name="table1989239798191846"></a>
<table><thead align="left"><tr id="row1882369618191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p501024172191846"><a name="p501024172191846"></a><a name="p501024172191846"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1584938409191846"><a name="p1584938409191846"></a><a name="p1584938409191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1698897072191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1022350585191846"><a name="p1022350585191846"></a><a name="p1022350585191846"></a><a href="lowpower-h.md">lowpower.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985219732191846"><a name="p985219732191846"></a><a name="p985219732191846"></a>Sets low power consumption for the device. </p>
</td>
</tr>
<tr id="row505880659191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p249703024191846"><a name="p249703024191846"></a><a name="p249703024191846"></a><a href="reset-h.md">reset.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48170559191846"><a name="p48170559191846"></a><a name="p48170559191846"></a>Reboots the device. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table535211222191846"></a>
<table><thead align="left"><tr id="row1518440064191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1386195491191846"><a name="p1386195491191846"></a><a name="p1386195491191846"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1342155005191846"><a name="p1342155005191846"></a><a name="p1342155005191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row765843043191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155946825191846"><a name="p155946825191846"></a><a name="p155946825191846"></a><a href="power.md#gaa6139ca73fa81742134fe74345ccb748">LpcType</a> { <a href="power.md#ggaa6139ca73fa81742134fe74345ccb748a79dbeab2cc1e9d820df3b261984ffdf9">NO_SLEEP</a>, <a href="power.md#ggaa6139ca73fa81742134fe74345ccb748a84d5857ff1535c751c3b15fea913ae40">LIGHT_SLEEP</a>, <a href="power.md#ggaa6139ca73fa81742134fe74345ccb748a3c282494db59c58249a6b608e20050bf">DEEP_SLEEP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802232860191846"><a name="p1802232860191846"></a><a name="p1802232860191846"></a>Enumerates low power consumption modes. </p>
</td>
</tr>
<tr id="row137049048191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p881550911191846"><a name="p881550911191846"></a><a name="p881550911191846"></a><a href="power.md#gaeac1b873015f5b0a8aa7f3c068507426">RebootCause</a> {   <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426a04a0e86a44ea0d7600cd026650b5ffe7">SYS_REBOOT_CAUSE_UNKNOWN</a> = 0, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426ab49da9db95acfa014af9f23d78dbb1a4">SYS_REBOOT_CAUSE_CMD</a>, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426a7c1427e708ac62940fa085be165d8f85">SYS_REBOOT_CAUSE_UPG</a>, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426aa88786682350e9f0a17f7a23554bd8d1">SYS_REBOOT_CAUSE_UPG_B</a>,   <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426aeff008205aabb73ffa286cd4c0eaad89">SYS_REBOOT_CAUSE_WIFI_MODE</a>, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426af1e3a68edd40db56d76067ed1e24b85b">SYS_REBOOT_CAUSE_USR_NORMAL_REBOOT</a>, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426acb3dfe8998e30cc72aa0a6b70e2c5bcf">SYS_REBOOT_CAUSE_USR0</a>, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426aa523e821f1c3f0917f08db5a2aad782c">SYS_REBOOT_CAUSE_USR1</a>,   <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426af96d2c4f5a95fb704ec5296f0c417dbf">SYS_REBOOT_CAUSE_AT_BUSY</a>, <a href="power.md#ggaeac1b873015f5b0a8aa7f3c068507426a14fea85ad30317c373b6609d33d36bde">SYS_REBOOT_CAUSE_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p385100433191846"><a name="p385100433191846"></a><a name="p385100433191846"></a>Enumerates reboot causes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1864079017191846"></a>
<table><thead align="left"><tr id="row482209266191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2110875106191846"><a name="p2110875106191846"></a><a name="p2110875106191846"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p99326340191846"><a name="p99326340191846"></a><a name="p99326340191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row234286184191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1058368950191846"><a name="p1058368950191846"></a><a name="p1058368950191846"></a><a href="power.md#gac4363d7384c17fd7dcc0b70b432ca750">LpcInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404917060191846"><a name="p404917060191846"></a><a name="p404917060191846"></a>unsigned int </p>
<p id="p179724906191846"><a name="p179724906191846"></a><a name="p179724906191846"></a>Initializes low power consumption. </p>
</td>
</tr>
<tr id="row1575652139191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049881832191846"><a name="p1049881832191846"></a><a name="p1049881832191846"></a><a href="power.md#ga6a7b9016d6742e82a044369b3f960554">LpcSetType</a> (<a href="power.md#gaa6139ca73fa81742134fe74345ccb748">LpcType</a> type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418483883191846"><a name="p418483883191846"></a><a name="p418483883191846"></a>unsigned int </p>
<p id="p137651742191846"><a name="p137651742191846"></a><a name="p137651742191846"></a>Sets low power consumption for the device. </p>
</td>
</tr>
<tr id="row1779133799191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1374313162191846"><a name="p1374313162191846"></a><a name="p1374313162191846"></a><a href="power.md#ga3653c23553991eac26fa69f6a23e8987">RebootDevice</a> (<a href="power.md#gaeac1b873015f5b0a8aa7f3c068507426">RebootCause</a> cause)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1380036526191846"><a name="p1380036526191846"></a><a name="p1380036526191846"></a>void </p>
<p id="p1165499843191846"><a name="p1165499843191846"></a><a name="p1165499843191846"></a>Reboots the device using different causes. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section451223610191846"></a>

## **Enumeration Type Documentation**<a name="section978369075191846"></a>

## LpcType<a name="gaa6139ca73fa81742134fe74345ccb748"></a>

```
enum [LpcType](power.md#gaa6139ca73fa81742134fe74345ccb748)
```

 **Description:**

Enumerates low power consumption modes. 

<a name="table164126278191846"></a>
<table><thead align="left"><tr id="row1392435691191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p301533492191846"><a name="p301533492191846"></a><a name="p301533492191846"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1074452775191846"><a name="p1074452775191846"></a><a name="p1074452775191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row515055975191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa6139ca73fa81742134fe74345ccb748a79dbeab2cc1e9d820df3b261984ffdf9"><a name="ggaa6139ca73fa81742134fe74345ccb748a79dbeab2cc1e9d820df3b261984ffdf9"></a><a name="ggaa6139ca73fa81742134fe74345ccb748a79dbeab2cc1e9d820df3b261984ffdf9"></a></strong>NO_SLEEP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1764523222191846"><a name="p1764523222191846"></a><a name="p1764523222191846"></a>No sleep </p>
 </td>
</tr>
<tr id="row637262573191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa6139ca73fa81742134fe74345ccb748a84d5857ff1535c751c3b15fea913ae40"><a name="ggaa6139ca73fa81742134fe74345ccb748a84d5857ff1535c751c3b15fea913ae40"></a><a name="ggaa6139ca73fa81742134fe74345ccb748a84d5857ff1535c751c3b15fea913ae40"></a></strong>LIGHT_SLEEP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698915899191846"><a name="p1698915899191846"></a><a name="p1698915899191846"></a>Light sleep </p>
 </td>
</tr>
<tr id="row2107551857191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa6139ca73fa81742134fe74345ccb748a3c282494db59c58249a6b608e20050bf"><a name="ggaa6139ca73fa81742134fe74345ccb748a3c282494db59c58249a6b608e20050bf"></a><a name="ggaa6139ca73fa81742134fe74345ccb748a3c282494db59c58249a6b608e20050bf"></a></strong>DEEP_SLEEP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985952559191846"><a name="p985952559191846"></a><a name="p985952559191846"></a>Deep sleep </p>
 </td>
</tr>
</tbody>
</table>

## RebootCause<a name="gaeac1b873015f5b0a8aa7f3c068507426"></a>

```
enum [RebootCause](power.md#gaeac1b873015f5b0a8aa7f3c068507426)
```

 **Description:**

Enumerates reboot causes. 

<a name="table1520862138191846"></a>
<table><thead align="left"><tr id="row1755977744191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p125099925191846"><a name="p125099925191846"></a><a name="p125099925191846"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p426671321191846"><a name="p426671321191846"></a><a name="p426671321191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row397976864191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426a04a0e86a44ea0d7600cd026650b5ffe7"><a name="ggaeac1b873015f5b0a8aa7f3c068507426a04a0e86a44ea0d7600cd026650b5ffe7"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426a04a0e86a44ea0d7600cd026650b5ffe7"></a></strong>SYS_REBOOT_CAUSE_UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85723376191846"><a name="p85723376191846"></a><a name="p85723376191846"></a>Unknown cause </p>
 </td>
</tr>
<tr id="row2029532973191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426ab49da9db95acfa014af9f23d78dbb1a4"><a name="ggaeac1b873015f5b0a8aa7f3c068507426ab49da9db95acfa014af9f23d78dbb1a4"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426ab49da9db95acfa014af9f23d78dbb1a4"></a></strong>SYS_REBOOT_CAUSE_CMD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245930844191846"><a name="p1245930844191846"></a><a name="p1245930844191846"></a>System reboot </p>
 </td>
</tr>
<tr id="row1283519104191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426a7c1427e708ac62940fa085be165d8f85"><a name="ggaeac1b873015f5b0a8aa7f3c068507426a7c1427e708ac62940fa085be165d8f85"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426a7c1427e708ac62940fa085be165d8f85"></a></strong>SYS_REBOOT_CAUSE_UPG </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882530980191846"><a name="p882530980191846"></a><a name="p882530980191846"></a>Reboot upon an upgrade </p>
 </td>
</tr>
<tr id="row1676343887191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426aa88786682350e9f0a17f7a23554bd8d1"><a name="ggaeac1b873015f5b0a8aa7f3c068507426aa88786682350e9f0a17f7a23554bd8d1"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426aa88786682350e9f0a17f7a23554bd8d1"></a></strong>SYS_REBOOT_CAUSE_UPG_B </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699007623191846"><a name="p699007623191846"></a><a name="p699007623191846"></a>Reboot upon an upgrade on the backup partition </p>
 </td>
</tr>
<tr id="row364670150191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426aeff008205aabb73ffa286cd4c0eaad89"><a name="ggaeac1b873015f5b0a8aa7f3c068507426aeff008205aabb73ffa286cd4c0eaad89"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426aeff008205aabb73ffa286cd4c0eaad89"></a></strong>SYS_REBOOT_CAUSE_WIFI_MODE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p696976054191846"><a name="p696976054191846"></a><a name="p696976054191846"></a>Reboot in Wi-Fi mode </p>
 </td>
</tr>
<tr id="row1938796584191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426af1e3a68edd40db56d76067ed1e24b85b"><a name="ggaeac1b873015f5b0a8aa7f3c068507426af1e3a68edd40db56d76067ed1e24b85b"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426af1e3a68edd40db56d76067ed1e24b85b"></a></strong>SYS_REBOOT_CAUSE_USR_NORMAL_REBOOT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p117889563191846"><a name="p117889563191846"></a><a name="p117889563191846"></a>Normal reboot </p>
 </td>
</tr>
<tr id="row1412054671191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426acb3dfe8998e30cc72aa0a6b70e2c5bcf"><a name="ggaeac1b873015f5b0a8aa7f3c068507426acb3dfe8998e30cc72aa0a6b70e2c5bcf"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426acb3dfe8998e30cc72aa0a6b70e2c5bcf"></a></strong>SYS_REBOOT_CAUSE_USR0 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477093412191846"><a name="p1477093412191846"></a><a name="p1477093412191846"></a>Custom cause 0 </p>
 </td>
</tr>
<tr id="row1468600672191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426aa523e821f1c3f0917f08db5a2aad782c"><a name="ggaeac1b873015f5b0a8aa7f3c068507426aa523e821f1c3f0917f08db5a2aad782c"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426aa523e821f1c3f0917f08db5a2aad782c"></a></strong>SYS_REBOOT_CAUSE_USR1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681745455191846"><a name="p1681745455191846"></a><a name="p1681745455191846"></a>Custom cause 1 </p>
 </td>
</tr>
<tr id="row269370156191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426af96d2c4f5a95fb704ec5296f0c417dbf"><a name="ggaeac1b873015f5b0a8aa7f3c068507426af96d2c4f5a95fb704ec5296f0c417dbf"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426af96d2c4f5a95fb704ec5296f0c417dbf"></a></strong>SYS_REBOOT_CAUSE_AT_BUSY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287286510191846"><a name="p287286510191846"></a><a name="p287286510191846"></a>Reboot upon busy AT commands </p>
 </td>
</tr>
<tr id="row918915771191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeac1b873015f5b0a8aa7f3c068507426a14fea85ad30317c373b6609d33d36bde"><a name="ggaeac1b873015f5b0a8aa7f3c068507426a14fea85ad30317c373b6609d33d36bde"></a><a name="ggaeac1b873015f5b0a8aa7f3c068507426a14fea85ad30317c373b6609d33d36bde"></a></strong>SYS_REBOOT_CAUSE_MAX </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p688922184191846"><a name="p688922184191846"></a><a name="p688922184191846"></a>Maximum value </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section455533125191846"></a>

## LpcInit\(\)<a name="gac4363d7384c17fd7dcc0b70b432ca750"></a>

```
unsigned int LpcInit (void )
```

 **Description:**

Initializes low power consumption. 

**Returns:**

Returns  [WIFI\_IOT\_SUCCESS](wifiiot.md#gae70eaf627c0370cc271dcb8060aee861)  if the operation is successful; Returns an error code defined in  [wifiiot\_errno.h](wifiiot_errno-h.md)  otherwise. 



## LpcSetType\(\)<a name="ga6a7b9016d6742e82a044369b3f960554"></a>

```
unsigned int LpcSetType ([LpcType](power.md#gaa6139ca73fa81742134fe74345ccb748) type)
```

 **Description:**

Sets low power consumption for the device. 

**Parameters:**

<a name="table1216468474191846"></a>
<table><thead align="left"><tr id="row185072552191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1822856225191846"><a name="p1822856225191846"></a><a name="p1822856225191846"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p868366359191846"><a name="p868366359191846"></a><a name="p868366359191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row752733970191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the low power consumption mode to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [WIFI\_IOT\_SUCCESS](wifiiot.md#gae70eaf627c0370cc271dcb8060aee861)  if the operation is successful; Returns an error code defined in  [wifiiot\_errno.h](wifiiot_errno-h.md)  otherwise. 



## RebootDevice\(\)<a name="ga3653c23553991eac26fa69f6a23e8987"></a>

```
void RebootDevice ([RebootCause](power.md#gaeac1b873015f5b0a8aa7f3c068507426) cause)
```

 **Description:**

Reboots the device using different causes. 

**Parameters:**

<a name="table1246673451191846"></a>
<table><thead align="left"><tr id="row1294716830191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p997432359191846"><a name="p997432359191846"></a><a name="p997432359191846"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p867733004191846"><a name="p867733004191846"></a><a name="p867733004191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row612548614191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cause</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the reboot cause. </td>
</tr>
</tbody>
</table>

