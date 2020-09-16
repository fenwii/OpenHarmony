# WifiIotUartAttribute<a name="EN-US_TOPIC_0000001055195072"></a>

## **Overview**<a name="section895034200191907"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Defines the basic attributes of a UART device. 

## **Summary**<a name="section2002770127191907"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table767975011191907"></a>
<table><thead align="left"><tr id="row1363015517191907"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p469740634191907"><a name="p469740634191907"></a><a name="p469740634191907"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1079253337191907"><a name="p1079253337191907"></a><a name="p1079253337191907"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1414307585191907"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841772715191907"><a name="p1841772715191907"></a><a name="p1841772715191907"></a><a href="wifiiotuartattribute.md#add2d93f84bb9f23f9bad2acd53f29a11">baudRate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914780851191907"><a name="p1914780851191907"></a><a name="p1914780851191907"></a>unsigned int </p>
</td>
</tr>
<tr id="row1662787794191907"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p77405086191907"><a name="p77405086191907"></a><a name="p77405086191907"></a><a href="wifiiotuartattribute.md#ac039441e60c8cba5dff6f7e2fb602b10">dataBits</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1668264227191907"><a name="p1668264227191907"></a><a name="p1668264227191907"></a>unsigned char </p>
</td>
</tr>
<tr id="row612501233191907"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636631006191907"><a name="p636631006191907"></a><a name="p636631006191907"></a><a href="wifiiotuartattribute.md#a6dba371c26a3fccae162b39c4f72eef1">stopBits</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805202621191907"><a name="p805202621191907"></a><a name="p805202621191907"></a>unsigned char </p>
</td>
</tr>
<tr id="row316551294191907"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1645596224191907"><a name="p1645596224191907"></a><a name="p1645596224191907"></a><a href="wifiiotuartattribute.md#a7b4598cd072e44d1009b3e2fb34c7df3">parity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804019856191907"><a name="p804019856191907"></a><a name="p804019856191907"></a>unsigned char </p>
</td>
</tr>
<tr id="row948039313191907"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p689206378191907"><a name="p689206378191907"></a><a name="p689206378191907"></a><a href="wifiiotuartattribute.md#a044e97edf672f9a7f00147a0e7a6cf06">pad</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884259483191907"><a name="p1884259483191907"></a><a name="p1884259483191907"></a>unsigned char </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1402286933191907"></a>

## **Field Documentation**<a name="section1090245148191907"></a>

## baudRate<a name="add2d93f84bb9f23f9bad2acd53f29a11"></a>

```
unsigned int WifiIotUartAttribute::baudRate
```

 **Description:**

Baud rate 

## dataBits<a name="ac039441e60c8cba5dff6f7e2fb602b10"></a>

```
unsigned char WifiIotUartAttribute::dataBits
```

 **Description:**

Data bits. The value range is specified in  [WifiIotUartIdxDataBit](wifiiot.md#gafdf1adfc0e0ed18282aa3006300b12b4). 

## pad<a name="a044e97edf672f9a7f00147a0e7a6cf06"></a>

```
unsigned char WifiIotUartAttribute::pad
```

 **Description:**

Padding bit 

## parity<a name="a7b4598cd072e44d1009b3e2fb34c7df3"></a>

```
unsigned char WifiIotUartAttribute::parity
```

 **Description:**

Parity bit. The value range is specified in  [WifiIotUartParity](wifiiot.md#ga9cee98ab295d2e42ab7f0fb614268602). 

## stopBits<a name="a6dba371c26a3fccae162b39c4f72eef1"></a>

```
unsigned char WifiIotUartAttribute::stopBits
```

 **Description:**

Stop bits. The value range is specified in  [WifiIotUartStopBit](wifiiot.md#gab0a1b43e8e98b028717e6557003b3172). 

