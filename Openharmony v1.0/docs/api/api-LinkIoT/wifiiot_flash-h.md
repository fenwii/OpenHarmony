# wifiiot\_flash.h<a name="ZH-CN_TOPIC_0000001054715055"></a>

## **Overview**<a name="section822936109191855"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the flash interface functions. 

These functions are used to initialize or deinitialize a flash device, and read data from or write data to a flash memory. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1393862488191855"></a>

## Functions<a name="func-members"></a>

<a name="table637716428191855"></a>
<table><thead align="left"><tr id="row1007090266191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p533890011191855"><a name="p533890011191855"></a><a name="p533890011191855"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1107307501191855"><a name="p1107307501191855"></a><a name="p1107307501191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1032298164191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176763016191855"><a name="p176763016191855"></a><a name="p176763016191855"></a><a href="Wifiiot.md#ga710155ea010eab98ef503abc7b0d7d2c">FlashRead</a> (const unsigned int flashOffset, const unsigned int size, unsigned char *ramData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p93943427191855"><a name="p93943427191855"></a><a name="p93943427191855"></a>unsigned int&nbsp;</p>
<p id="p72030646191855"><a name="p72030646191855"></a><a name="p72030646191855"></a>Reads data from a flash memory address. </p>
</td>
</tr>
<tr id="row1488485958191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p27770823191855"><a name="p27770823191855"></a><a name="p27770823191855"></a><a href="Wifiiot.md#gaf565413854f5b2581aa93a5e6143b04a">FlashWrite</a> (const unsigned int flashOffset, unsigned int size, const unsigned char *ramData, unsigned char doErase)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1395221162191855"><a name="p1395221162191855"></a><a name="p1395221162191855"></a>unsigned int&nbsp;</p>
<p id="p1523366519191855"><a name="p1523366519191855"></a><a name="p1523366519191855"></a>Writes data to a flash memory address. </p>
</td>
</tr>
<tr id="row1099101665191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264969645191855"><a name="p264969645191855"></a><a name="p264969645191855"></a><a href="Wifiiot.md#ga4f8879ba35704afb014eab657f2a6b29">FlashErase</a> (const unsigned int flashOffset, const unsigned int size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616084278191855"><a name="p1616084278191855"></a><a name="p1616084278191855"></a>unsigned int&nbsp;</p>
<p id="p663563768191855"><a name="p663563768191855"></a><a name="p663563768191855"></a>Erases data in a specified flash memory address. </p>
</td>
</tr>
<tr id="row637592275191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255052770191855"><a name="p255052770191855"></a><a name="p255052770191855"></a><a href="Wifiiot.md#ga1cf4ab1534ea2b52787838b59dd752cb">FlashInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p811947776191855"><a name="p811947776191855"></a><a name="p811947776191855"></a>unsigned int&nbsp;</p>
<p id="p997910155191855"><a name="p997910155191855"></a><a name="p997910155191855"></a>Initializes the flash device. </p>
</td>
</tr>
<tr id="row762449382191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683838301191855"><a name="p1683838301191855"></a><a name="p1683838301191855"></a><a href="Wifiiot.md#ga5241dc71f2e9fd54acb65ef52575740a">FlashDeinit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213415972191855"><a name="p213415972191855"></a><a name="p213415972191855"></a>unsigned int&nbsp;</p>
<p id="p871095654191855"><a name="p871095654191855"></a><a name="p871095654191855"></a>Deinitializes the flash device. </p>
</td>
</tr>
</tbody>
</table>

