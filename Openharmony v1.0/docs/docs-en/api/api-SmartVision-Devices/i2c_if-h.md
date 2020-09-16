# i2c\_if.h<a name="EN-US_TOPIC_0000001054479535"></a>

## **Overview**<a name="section1136701475093525"></a>

**Related Modules:**

[I2C](i2c.md)

**Description:**

Declares the standard I2C interface functions. 

**Since:**

1.0

## **Summary**<a name="section487381195093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table491107091093525"></a>
<table><thead align="left"><tr id="row571139557093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2010388261093525"><a name="p2010388261093525"></a><a name="p2010388261093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p908546142093525"><a name="p908546142093525"></a><a name="p908546142093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row322315665093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380607614093525"><a name="p380607614093525"></a><a name="p380607614093525"></a><a href="i2cmsg.md">I2cMsg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1892381275093525"><a name="p1892381275093525"></a><a name="p1892381275093525"></a>Defines the I2C transfer message used during custom transfers. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1386422173093525"></a>
<table><thead align="left"><tr id="row609810457093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1228505214093525"><a name="p1228505214093525"></a><a name="p1228505214093525"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1645970392093525"><a name="p1645970392093525"></a><a name="p1645970392093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1507224824093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p639916108093525"><a name="p639916108093525"></a><a name="p639916108093525"></a><a href="i2c.md#ga32b58f021632085445d80c80e382a546">I2cFlag</a> {   <a href="i2c.md#gga32b58f021632085445d80c80e382a546a65c5829d919f53dbc00b4c4e3f5a2f7a">I2C_FLAG_READ</a> = (0x1 &lt;&lt; 0), <a href="i2c.md#gga32b58f021632085445d80c80e382a546a830aec226b260e4624fb81f355e4fbd6">I2C_FLAG_ADDR_10BIT</a> = (0x1 &lt;&lt; 4), <a href="i2c.md#gga32b58f021632085445d80c80e382a546a801a2ec0dcf3069ba412311d00e45356">I2C_FLAG_READ_NO_ACK</a> = (0x1 &lt;&lt; 11), <a href="i2c.md#gga32b58f021632085445d80c80e382a546a6c8d6f7ba01b0e45fb73ee5883ba311c">I2C_FLAG_IGNORE_NO_ACK</a> = (0x1 &lt;&lt; 12),   <a href="i2c.md#gga32b58f021632085445d80c80e382a546a87b7c3b732260789c5acd9245171ad25">I2C_FLAG_NO_START</a> = (0x1 &lt;&lt; 14), <a href="i2c.md#gga32b58f021632085445d80c80e382a546a641c29990d13fe5f840b495dca8e21e9">I2C_FLAG_STOP</a> = (0x1 &lt;&lt; 15) }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p821424072093525"><a name="p821424072093525"></a><a name="p821424072093525"></a>Enumerates flags used for transferring I2C messages. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1745353040093525"></a>
<table><thead align="left"><tr id="row1660433423093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p808506890093525"><a name="p808506890093525"></a><a name="p808506890093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1645299341093525"><a name="p1645299341093525"></a><a name="p1645299341093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row802887134093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691901043093525"><a name="p691901043093525"></a><a name="p691901043093525"></a><a href="i2c.md#ga7551f766dcabd70e96dbfe5e6585c6fb">I2cOpen</a> (int16_t number)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375705581093525"><a name="p1375705581093525"></a><a name="p1375705581093525"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1022451773093525"><a name="p1022451773093525"></a><a name="p1022451773093525"></a>Obtains the handle of an I2C controller. </p>
</td>
</tr>
<tr id="row590097537093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p439170874093525"><a name="p439170874093525"></a><a name="p439170874093525"></a><a href="i2c.md#ga3dbd2556b29861859b360693f355df1f">I2cClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266240643093525"><a name="p1266240643093525"></a><a name="p1266240643093525"></a>void </p>
<p id="p1992705447093525"><a name="p1992705447093525"></a><a name="p1992705447093525"></a>Releases the handle of an I2C controller. </p>
</td>
</tr>
<tr id="row853562770093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170051827093525"><a name="p170051827093525"></a><a name="p170051827093525"></a><a href="i2c.md#ga2fbc639bd3c5f9e5e9657c64d88bcbc9">I2cTransfer</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="i2cmsg.md">I2cMsg</a> *msgs, int16_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1215025722093525"><a name="p1215025722093525"></a><a name="p1215025722093525"></a>int32_t </p>
<p id="p185292374093525"><a name="p185292374093525"></a><a name="p185292374093525"></a>Launches a custom transfer to an I2C device. </p>
</td>
</tr>
</tbody>
</table>

