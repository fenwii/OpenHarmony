# reset.h<a name="ZH-CN_TOPIC_0000001054876468"></a>

## **Overview**<a name="section1768350754191850"></a>

**Related Modules:**

[Power](Power.md)

**Description:**

Reboots the device. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1839431681191850"></a>

## Enumerations<a name="enum-members"></a>

<a name="table1292592086191850"></a>
<table><thead align="left"><tr id="row2038669060191850"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1740412485191850"><a name="p1740412485191850"></a><a name="p1740412485191850"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1081550326191850"><a name="p1081550326191850"></a><a name="p1081550326191850"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1344552052191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1040218533191850"><a name="p1040218533191850"></a><a name="p1040218533191850"></a><a href="Power.md#gaeac1b873015f5b0a8aa7f3c068507426">RebootCause</a> { &nbsp;&nbsp;<a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426a04a0e86a44ea0d7600cd026650b5ffe7">SYS_REBOOT_CAUSE_UNKNOWN</a> = 0, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426ab49da9db95acfa014af9f23d78dbb1a4">SYS_REBOOT_CAUSE_CMD</a>, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426a7c1427e708ac62940fa085be165d8f85">SYS_REBOOT_CAUSE_UPG</a>, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426aa88786682350e9f0a17f7a23554bd8d1">SYS_REBOOT_CAUSE_UPG_B</a>, &nbsp;&nbsp;<a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426aeff008205aabb73ffa286cd4c0eaad89">SYS_REBOOT_CAUSE_WIFI_MODE</a>, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426af1e3a68edd40db56d76067ed1e24b85b">SYS_REBOOT_CAUSE_USR_NORMAL_REBOOT</a>, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426acb3dfe8998e30cc72aa0a6b70e2c5bcf">SYS_REBOOT_CAUSE_USR0</a>, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426aa523e821f1c3f0917f08db5a2aad782c">SYS_REBOOT_CAUSE_USR1</a>, &nbsp;&nbsp;<a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426af96d2c4f5a95fb704ec5296f0c417dbf">SYS_REBOOT_CAUSE_AT_BUSY</a>, <a href="Power.md#ggaeac1b873015f5b0a8aa7f3c068507426a14fea85ad30317c373b6609d33d36bde">SYS_REBOOT_CAUSE_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1371959254191850"><a name="p1371959254191850"></a><a name="p1371959254191850"></a>Enumerates reboot causes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table894156323191850"></a>
<table><thead align="left"><tr id="row1661105463191850"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p335484545191850"><a name="p335484545191850"></a><a name="p335484545191850"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p38630697191850"><a name="p38630697191850"></a><a name="p38630697191850"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1122026798191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730309420191850"><a name="p730309420191850"></a><a name="p730309420191850"></a><a href="Power.md#ga3653c23553991eac26fa69f6a23e8987">RebootDevice</a> (<a href="Power.md#gaeac1b873015f5b0a8aa7f3c068507426">RebootCause</a> cause)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p787406874191850"><a name="p787406874191850"></a><a name="p787406874191850"></a>void&nbsp;</p>
<p id="p819083551191850"><a name="p819083551191850"></a><a name="p819083551191850"></a>Reboots the device using different causes. </p>
</td>
</tr>
</tbody>
</table>

