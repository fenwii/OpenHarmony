# wifiiot\_at.h<a name="ZH-CN_TOPIC_0000001054595097"></a>

## **Overview**<a name="section1823080756191855"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the AT interface functions. 

These functions are used for AT initialization as well as command line registration and printing. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section858458225191855"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table238022306191855"></a>
<table><thead align="left"><tr id="row1737813744191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p61493960191855"><a name="p61493960191855"></a><a name="p61493960191855"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1830355177191855"><a name="p1830355177191855"></a><a name="p1830355177191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1618849200191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479779477191855"><a name="p1479779477191855"></a><a name="p1479779477191855"></a><a href="AtCmdTbl.md">AtCmdTbl</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029517333191855"><a name="p2029517333191855"></a><a name="p2029517333191855"></a>Defines the AT command registration structure. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table899337354191855"></a>
<table><thead align="left"><tr id="row1725129521191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p850319775191855"><a name="p850319775191855"></a><a name="p850319775191855"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p512719526191855"><a name="p512719526191855"></a><a name="p512719526191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row518880617191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748954265191855"><a name="p1748954265191855"></a><a name="p1748954265191855"></a><a href="Wifiiot.md#ga2967ccc90396327f31df7365f3bb8501">AtRegisterCmd</a> (const <a href="AtCmdTbl.md">AtCmdTbl</a> *cmdTbl, unsigned short cmdNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225347295191855"><a name="p225347295191855"></a><a name="p225347295191855"></a>unsigned int&nbsp;</p>
<p id="p542224688191855"><a name="p542224688191855"></a><a name="p542224688191855"></a>Registers a certain number of AT commands. </p>
</td>
</tr>
<tr id="row1770804199191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1321827026191855"><a name="p1321827026191855"></a><a name="p1321827026191855"></a><a href="Wifiiot.md#ga73b1bb803919e709a2a9a4a21530cf7b">AtSysCmdRegister</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p629187148191855"><a name="p629187148191855"></a><a name="p629187148191855"></a>void&nbsp;</p>
<p id="p289192225191855"><a name="p289192225191855"></a><a name="p289192225191855"></a>Registers a system AT command. </p>
</td>
</tr>
<tr id="row111850049191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p130659657191855"><a name="p130659657191855"></a><a name="p130659657191855"></a><a href="Wifiiot.md#gad03e3a92ab85a6ee0660df82272be5e9">AtPrintf</a> (const char *fmt,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763120867191855"><a name="p763120867191855"></a><a name="p763120867191855"></a>int&nbsp;</p>
<p id="p329542504191855"><a name="p329542504191855"></a><a name="p329542504191855"></a>Formats data and outputs it to the AT command terminal. </p>
</td>
</tr>
<tr id="row223957271191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292788752191855"><a name="p1292788752191855"></a><a name="p1292788752191855"></a><a href="Wifiiot.md#gaa72b05261c0b633751d7bd4e10db4870">AtInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131988623191855"><a name="p2131988623191855"></a><a name="p2131988623191855"></a>unsigned int&nbsp;</p>
<p id="p2109185863191855"><a name="p2109185863191855"></a><a name="p2109185863191855"></a>Initializes an AT command task. </p>
</td>
</tr>
<tr id="row1129175107191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p708425511191855"><a name="p708425511191855"></a><a name="p708425511191855"></a><a href="Wifiiot.md#ga9068fd445d529fbc468fd27c336f1c43">AtCheckUartBusy</a> (unsigned char enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p706599539191855"><a name="p706599539191855"></a><a name="p706599539191855"></a>void&nbsp;</p>
<p id="p1678729234191855"><a name="p1678729234191855"></a><a name="p1678729234191855"></a>Sets whether to check the UART busy status during low-power voting. </p>
</td>
</tr>
</tbody>
</table>

