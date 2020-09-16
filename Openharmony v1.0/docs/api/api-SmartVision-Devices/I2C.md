# I2C<a name="ZH-CN_TOPIC_0000001054718075"></a>

## **Overview**<a name="section771321035093521"></a>

Provides standard Inter-Integrated Circuit \(I2C\) interfaces. 

This module allows a driver to perform operations on an I2C controller for accessing devices on the I2C bus, including creating and destroying I2C controller handles as well as reading and writing data.

**Since:**

1.0

## **Summary**<a name="section1793289897093521"></a>

## Files<a name="files"></a>

<a name="table577401317093521"></a>
<table><thead align="left"><tr id="row1339561465093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p134507873093521"><a name="p134507873093521"></a><a name="p134507873093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p125520971093521"><a name="p125520971093521"></a><a name="p125520971093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1719987627093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830565802093521"><a name="p1830565802093521"></a><a name="p1830565802093521"></a><a href="i2c_if-h.md">i2c_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p222000624093521"><a name="p222000624093521"></a><a name="p222000624093521"></a>Declares the standard I2C interface functions. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table885230810093521"></a>
<table><thead align="left"><tr id="row868015724093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1601606332093521"><a name="p1601606332093521"></a><a name="p1601606332093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p958751248093521"><a name="p958751248093521"></a><a name="p958751248093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1343108931093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132724779093521"><a name="p2132724779093521"></a><a name="p2132724779093521"></a><a href="I2cMsg.md">I2cMsg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131270386093521"><a name="p2131270386093521"></a><a name="p2131270386093521"></a>Defines the I2C transfer message used during custom transfers. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2142951558093521"></a>
<table><thead align="left"><tr id="row258946991093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1178064003093521"><a name="p1178064003093521"></a><a name="p1178064003093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1364001668093521"><a name="p1364001668093521"></a><a name="p1364001668093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2063760607093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1499520753093521"><a name="p1499520753093521"></a><a name="p1499520753093521"></a><a href="I2C.md#ga32b58f021632085445d80c80e382a546">I2cFlag</a> { &nbsp;&nbsp;<a href="I2C.md#gga32b58f021632085445d80c80e382a546a65c5829d919f53dbc00b4c4e3f5a2f7a">I2C_FLAG_READ</a> = (0x1 &lt;&lt; 0), <a href="I2C.md#gga32b58f021632085445d80c80e382a546a830aec226b260e4624fb81f355e4fbd6">I2C_FLAG_ADDR_10BIT</a> = (0x1 &lt;&lt; 4), <a href="I2C.md#gga32b58f021632085445d80c80e382a546a801a2ec0dcf3069ba412311d00e45356">I2C_FLAG_READ_NO_ACK</a> = (0x1 &lt;&lt; 11), <a href="I2C.md#gga32b58f021632085445d80c80e382a546a6c8d6f7ba01b0e45fb73ee5883ba311c">I2C_FLAG_IGNORE_NO_ACK</a> = (0x1 &lt;&lt; 12), &nbsp;&nbsp;<a href="I2C.md#gga32b58f021632085445d80c80e382a546a87b7c3b732260789c5acd9245171ad25">I2C_FLAG_NO_START</a> = (0x1 &lt;&lt; 14), <a href="I2C.md#gga32b58f021632085445d80c80e382a546a641c29990d13fe5f840b495dca8e21e9">I2C_FLAG_STOP</a> = (0x1 &lt;&lt; 15) }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2108984994093521"><a name="p2108984994093521"></a><a name="p2108984994093521"></a>Enumerates flags used for transferring I2C messages. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table518168816093521"></a>
<table><thead align="left"><tr id="row286320677093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p101781086093521"><a name="p101781086093521"></a><a name="p101781086093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p451901561093521"><a name="p451901561093521"></a><a name="p451901561093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1049258410093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1559398664093521"><a name="p1559398664093521"></a><a name="p1559398664093521"></a><a href="I2C.md#ga7551f766dcabd70e96dbfe5e6585c6fb">I2cOpen</a> (int16_t number)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456279160093521"><a name="p1456279160093521"></a><a name="p1456279160093521"></a>struct <a href="DevHandle.md">DevHandle</a> *&nbsp;</p>
<p id="p1330477400093521"><a name="p1330477400093521"></a><a name="p1330477400093521"></a>Obtains the handle of an I2C controller. </p>
</td>
</tr>
<tr id="row1641181979093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p371209067093521"><a name="p371209067093521"></a><a name="p371209067093521"></a><a href="I2C.md#ga3dbd2556b29861859b360693f355df1f">I2cClose</a> (struct <a href="DevHandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p557150999093521"><a name="p557150999093521"></a><a name="p557150999093521"></a>void&nbsp;</p>
<p id="p40693930093521"><a name="p40693930093521"></a><a name="p40693930093521"></a>Releases the handle of an I2C controller. </p>
</td>
</tr>
<tr id="row1426258782093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841497269093521"><a name="p1841497269093521"></a><a name="p1841497269093521"></a><a href="I2C.md#ga2fbc639bd3c5f9e5e9657c64d88bcbc9">I2cTransfer</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, struct <a href="I2cMsg.md">I2cMsg</a> *msgs, int16_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p643933962093521"><a name="p643933962093521"></a><a name="p643933962093521"></a>int32_t&nbsp;</p>
<p id="p768016873093521"><a name="p768016873093521"></a><a name="p768016873093521"></a>Launches a custom transfer to an I2C device. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section402060402093521"></a>

## **Enumeration Type Documentation**<a name="section401123901093521"></a>

## I2cFlag<a name="ga32b58f021632085445d80c80e382a546"></a>

```
enum [I2cFlag](I2C.md#ga32b58f021632085445d80c80e382a546)
```

 **Description:**

Enumerates flags used for transferring I2C messages. 

Multiple flags can be used to jointly control a single I2C message transfer. If a bit is set to  **1**, the corresponding feature is enabled. If a bit is set to  **0**, the corresponding feature is disabled.

<a name="table1563739106093521"></a>
<table><thead align="left"><tr id="row205759369093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p8089216093521"><a name="p8089216093521"></a><a name="p8089216093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1705455711093521"><a name="p1705455711093521"></a><a name="p1705455711093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1516222167093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga32b58f021632085445d80c80e382a546a65c5829d919f53dbc00b4c4e3f5a2f7a"><a name="gga32b58f021632085445d80c80e382a546a65c5829d919f53dbc00b4c4e3f5a2f7a"></a><a name="gga32b58f021632085445d80c80e382a546a65c5829d919f53dbc00b4c4e3f5a2f7a"></a></strong>I2C_FLAG_READ&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69676394093521"><a name="p69676394093521"></a><a name="p69676394093521"></a>Read flag. The value <strong id="b588630802093521"><a name="b588630802093521"></a><a name="b588630802093521"></a>1</strong> indicates the read operation, and <strong id="b1295362403093521"><a name="b1295362403093521"></a><a name="b1295362403093521"></a>0</strong> indicates the write operation. </p>
 </td>
</tr>
<tr id="row337489791093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga32b58f021632085445d80c80e382a546a830aec226b260e4624fb81f355e4fbd6"><a name="gga32b58f021632085445d80c80e382a546a830aec226b260e4624fb81f355e4fbd6"></a><a name="gga32b58f021632085445d80c80e382a546a830aec226b260e4624fb81f355e4fbd6"></a></strong>I2C_FLAG_ADDR_10BIT&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1659840093093521"><a name="p1659840093093521"></a><a name="p1659840093093521"></a>10-bit addressing flag. The value <strong id="b1716998957093521"><a name="b1716998957093521"></a><a name="b1716998957093521"></a>1</strong> indicates that a 10-bit address is used. </p>
 </td>
</tr>
<tr id="row585044920093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga32b58f021632085445d80c80e382a546a801a2ec0dcf3069ba412311d00e45356"><a name="gga32b58f021632085445d80c80e382a546a801a2ec0dcf3069ba412311d00e45356"></a><a name="gga32b58f021632085445d80c80e382a546a801a2ec0dcf3069ba412311d00e45356"></a></strong>I2C_FLAG_READ_NO_ACK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824702609093521"><a name="p1824702609093521"></a><a name="p1824702609093521"></a>Non-ACK read flag. The value <strong id="b1137615017093521"><a name="b1137615017093521"></a><a name="b1137615017093521"></a>1</strong> indicates that no ACK signal is sent during the read process. </p>
 </td>
</tr>
<tr id="row1666729230093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga32b58f021632085445d80c80e382a546a6c8d6f7ba01b0e45fb73ee5883ba311c"><a name="gga32b58f021632085445d80c80e382a546a6c8d6f7ba01b0e45fb73ee5883ba311c"></a><a name="gga32b58f021632085445d80c80e382a546a6c8d6f7ba01b0e45fb73ee5883ba311c"></a></strong>I2C_FLAG_IGNORE_NO_ACK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1889781993093521"><a name="p1889781993093521"></a><a name="p1889781993093521"></a>Ignoring no-ACK flag. The value <strong id="b1774805214093521"><a name="b1774805214093521"></a><a name="b1774805214093521"></a>1</strong> indicates that the non-ACK signal is ignored. </p>
 </td>
</tr>
<tr id="row698573661093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga32b58f021632085445d80c80e382a546a87b7c3b732260789c5acd9245171ad25"><a name="gga32b58f021632085445d80c80e382a546a87b7c3b732260789c5acd9245171ad25"></a><a name="gga32b58f021632085445d80c80e382a546a87b7c3b732260789c5acd9245171ad25"></a></strong>I2C_FLAG_NO_START&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1609444969093521"><a name="p1609444969093521"></a><a name="p1609444969093521"></a>No START condition flag. The value <strong id="b1608644006093521"><a name="b1608644006093521"></a><a name="b1608644006093521"></a>1</strong> indicates that there is no START condition for the message transfer. </p>
 </td>
</tr>
<tr id="row709279988093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga32b58f021632085445d80c80e382a546a641c29990d13fe5f840b495dca8e21e9"><a name="gga32b58f021632085445d80c80e382a546a641c29990d13fe5f840b495dca8e21e9"></a><a name="gga32b58f021632085445d80c80e382a546a641c29990d13fe5f840b495dca8e21e9"></a></strong>I2C_FLAG_STOP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448004687093521"><a name="p448004687093521"></a><a name="p448004687093521"></a>STOP condition flag. The value <strong id="b271728836093521"><a name="b271728836093521"></a><a name="b271728836093521"></a>1</strong> indicates that the current transfer ends with a STOP condition. </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1729597184093521"></a>

## I2cClose\(\)<a name="ga3dbd2556b29861859b360693f355df1f"></a>

```
void I2cClose (struct [DevHandle](DevHandle.md) * handle)
```

 **Description:**

Releases the handle of an I2C controller. 

If you no longer need to access the I2C controller, you should call this function to close its handle so as to release unused memory resources.

**Parameters:**

<a name="table621981245093521"></a>
<table><thead align="left"><tr id="row1574786335093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1830738933093521"><a name="p1830738933093521"></a><a name="p1830738933093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p932213578093521"><a name="p932213578093521"></a><a name="p932213578093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row233111949093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the I2C controller.</td>
</tr>
</tbody>
</table>

## I2cOpen\(\)<a name="ga7551f766dcabd70e96dbfe5e6585c6fb"></a>

```
struct [DevHandle](DevHandle.md)* I2cOpen (int16_t number)
```

 **Description:**

Obtains the handle of an I2C controller. 

You must call this function before accessing the I2C bus.

**Parameters:**

<a name="table533952458093521"></a>
<table><thead align="left"><tr id="row562495108093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1278707212093521"><a name="p1278707212093521"></a><a name="p1278707212093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1559750722093521"><a name="p1559750722093521"></a><a name="p1559750722093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row522485289093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">number</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the I2C controller ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the  [DevHandle](DevHandle.md)  of the I2C controller if the operation is successful; returns  **NULL**  otherwise. 



## I2cTransfer\(\)<a name="ga2fbc639bd3c5f9e5e9657c64d88bcbc9"></a>

```
int32_t I2cTransfer (struct [DevHandle](DevHandle.md) * handle, struct [I2cMsg](I2cMsg.md) * msgs, int16_t count )
```

 **Description:**

Launches a custom transfer to an I2C device. 

**Parameters:**

<a name="table235220543093521"></a>
<table><thead align="left"><tr id="row1678461343093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1822125765093521"><a name="p1822125765093521"></a><a name="p1822125765093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2055865060093521"><a name="p2055865060093521"></a><a name="p2055865060093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1021210314093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the I2C controller obtained via <a href="I2C.md#ga7551f766dcabd70e96dbfe5e6585c6fb">I2cOpen</a>. </td>
</tr>
<tr id="row23726528093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msgs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the I2C transfer message structure array. </td>
</tr>
<tr id="row203526861093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the message structure array.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of transferred message structures if the operation is successful; returns a negative value otherwise. 

**See also:**

[I2cMsg](I2cMsg.md) 

**Attention:**

This function does not limit the number of message structures specified by  **count**  or the data length of each message structure. The specific I2C controller determines the maximum number and data length allowed.



