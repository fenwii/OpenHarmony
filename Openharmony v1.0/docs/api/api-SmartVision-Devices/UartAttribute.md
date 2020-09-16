# UartAttribute<a name="ZH-CN_TOPIC_0000001054918195"></a>

## **Overview**<a name="section1327230780093537"></a>

**Related Modules:**

[UART](UART.md)

**Description:**

Defines basic attributes of the UART port. 

You can configure the attributes via  [UartSetAttribute](UART.md#gadb447d9e1624cf778175af2d827c9d67). If the parameters are not set, default attributes are used.

**Since:**

1.0

## **Summary**<a name="section685821487093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table142583102093537"></a>
<table><thead align="left"><tr id="row1560365944093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1464940442093537"><a name="p1464940442093537"></a><a name="p1464940442093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1854642542093537"><a name="p1854642542093537"></a><a name="p1854642542093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row158356718093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1337506667093537"><a name="p1337506667093537"></a><a name="p1337506667093537"></a><a href="UartAttribute.md#a884f85f5c82f063596a52f43c12af1a8">dataBits</a>: 4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041455986093537"><a name="p1041455986093537"></a><a name="p1041455986093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row1936377303093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953849139093537"><a name="p1953849139093537"></a><a name="p1953849139093537"></a><a href="UartAttribute.md#abc4eefd31616175d469bc41d24b5b37b">parity</a>: 4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356133400093537"><a name="p356133400093537"></a><a name="p356133400093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row912771107093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p891953042093537"><a name="p891953042093537"></a><a name="p891953042093537"></a><a href="UartAttribute.md#a29782a670eaf734ed02955eff0cdd4b9">stopBits</a>: 4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326062776093537"><a name="p1326062776093537"></a><a name="p1326062776093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row1114824399093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2064086954093537"><a name="p2064086954093537"></a><a name="p2064086954093537"></a><a href="UartAttribute.md#a5ebfed49568aa4717b72d89084a13f3a">rts</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p63455751093537"><a name="p63455751093537"></a><a name="p63455751093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row107871753093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960446291093537"><a name="p960446291093537"></a><a name="p960446291093537"></a><a href="UartAttribute.md#a8c2ec715ce735b87619440004a5816f3">cts</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588331601093537"><a name="p1588331601093537"></a><a name="p1588331601093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row1228797079093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1194378236093537"><a name="p1194378236093537"></a><a name="p1194378236093537"></a><a href="UartAttribute.md#a171de31a6414563a1b8ca13c6209e52a">fifoRxEn</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1905727204093537"><a name="p1905727204093537"></a><a name="p1905727204093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row2009505166093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1885560042093537"><a name="p1885560042093537"></a><a name="p1885560042093537"></a><a href="UartAttribute.md#a12cd3afb4dfbc5ed70578e0fcee0700d">fifoTxEn</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2096712909093537"><a name="p2096712909093537"></a><a name="p2096712909093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row1488998606093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143688788093537"><a name="p143688788093537"></a><a name="p143688788093537"></a><a href="UartAttribute.md#a415c8237e3a34dfe812e6c6cc7a7a1fa">reserved</a>: 16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093946507093537"><a name="p1093946507093537"></a><a name="p1093946507093537"></a>unsigned int&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1577815570093537"></a>

## **Field Documentation**<a name="section257187406093537"></a>

## cts<a name="a8c2ec715ce735b87619440004a5816f3"></a>

```
unsigned int UartAttribute::cts
```

## dataBits<a name="a884f85f5c82f063596a52f43c12af1a8"></a>

```
unsigned int UartAttribute::dataBits
```

## fifoRxEn<a name="a171de31a6414563a1b8ca13c6209e52a"></a>

```
unsigned int UartAttribute::fifoRxEn
```

## fifoTxEn<a name="a12cd3afb4dfbc5ed70578e0fcee0700d"></a>

```
unsigned int UartAttribute::fifoTxEn
```

## parity<a name="abc4eefd31616175d469bc41d24b5b37b"></a>

```
unsigned int UartAttribute::parity
```

## reserved<a name="a415c8237e3a34dfe812e6c6cc7a7a1fa"></a>

```
unsigned int UartAttribute::reserved
```

 **Description:**

Reserved bits 

## rts<a name="a5ebfed49568aa4717b72d89084a13f3a"></a>

```
unsigned int UartAttribute::rts
```

## stopBits<a name="a29782a670eaf734ed02955eff0cdd4b9"></a>

```
unsigned int UartAttribute::stopBits
```

