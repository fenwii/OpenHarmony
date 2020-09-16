# wifiiot\_uart\_ex.h<a name="ZH-CN_TOPIC_0000001055675022"></a>

## **Overview**<a name="section2110750127191857"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the extended UART interface functions. 

These functions are used to obtain UART attributes and check the busy status. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1878710384191857"></a>

## Functions<a name="func-members"></a>

<a name="table607723669191857"></a>
<table><thead align="left"><tr id="row1530551244191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1962480631191857"><a name="p1962480631191857"></a><a name="p1962480631191857"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p683249721191857"><a name="p683249721191857"></a><a name="p683249721191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1931861273191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p433539417191857"><a name="p433539417191857"></a><a name="p433539417191857"></a><a href="Wifiiot.md#gafcea2c43c0f614ec9a02bcc1eaf81da1">UartIsBufEmpty</a> (<a href="Wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, unsigned char *empty)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1525479007191857"><a name="p1525479007191857"></a><a name="p1525479007191857"></a>unsigned int&nbsp;</p>
<p id="p1942596765191857"><a name="p1942596765191857"></a><a name="p1942596765191857"></a>Checks whether the buffer on a UART device is empty. </p>
</td>
</tr>
<tr id="row1917804071191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241702151191857"><a name="p241702151191857"></a><a name="p241702151191857"></a><a href="Wifiiot.md#gab6630d50726f5c57e726c3465fc0eb96">UartWriteImmediately</a> (<a href="Wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, const unsigned char *data, unsigned int dataLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257856808191857"><a name="p257856808191857"></a><a name="p257856808191857"></a>int&nbsp;</p>
<p id="p1943283127191857"><a name="p1943283127191857"></a><a name="p1943283127191857"></a>Writes data to be sent to a UART device in polling mode. </p>
</td>
</tr>
<tr id="row2005564057191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497429976191857"><a name="p1497429976191857"></a><a name="p1497429976191857"></a><a href="Wifiiot.md#gabc811333b8add98cd2eabb0ee2d726a3">UartGetAttribute</a> (<a href="Wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, <a href="WifiIotUartAttribute.md">WifiIotUartAttribute</a> *attr, <a href="WifiIotUartExtraAttr.md">WifiIotUartExtraAttr</a> *extraAttr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303570073191857"><a name="p303570073191857"></a><a name="p303570073191857"></a>unsigned int&nbsp;</p>
<p id="p519475016191857"><a name="p519475016191857"></a><a name="p519475016191857"></a>Obtains UART attributes. </p>
</td>
</tr>
<tr id="row1386030566191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p553846961191857"><a name="p553846961191857"></a><a name="p553846961191857"></a><a href="Wifiiot.md#ga67d7b274aaddc162c0140e32f6bc4486">UartIsBusy</a> (<a href="Wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, unsigned char *busy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733396072191857"><a name="p733396072191857"></a><a name="p733396072191857"></a>unsigned int&nbsp;</p>
<p id="p1525110239191857"><a name="p1525110239191857"></a><a name="p1525110239191857"></a>Checks whether the buffer on a UART device is busy. </p>
</td>
</tr>
</tbody>
</table>

