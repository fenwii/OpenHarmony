# SpiMsg<a name="EN-US_TOPIC_0000001054479601"></a>

## **Overview**<a name="section2079544464093536"></a>

**Related Modules:**

[SPI](spi.md)

**Description:**

Defines the custom SPI transfer message. 

**Since:**

1.0

## **Summary**<a name="section1213620650093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1609528174093536"></a>
<table><thead align="left"><tr id="row357767770093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1093377675093536"><a name="p1093377675093536"></a><a name="p1093377675093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1493338772093536"><a name="p1493338772093536"></a><a name="p1493338772093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row737067882093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p640836062093536"><a name="p640836062093536"></a><a name="p640836062093536"></a><a href="spimsg.md#ae2aed8b3bd1d75a50f82c880a45cf521">wbuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1656640498093536"><a name="p1656640498093536"></a><a name="p1656640498093536"></a>uint8_t * </p>
</td>
</tr>
<tr id="row2088683402093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p70418755093536"><a name="p70418755093536"></a><a name="p70418755093536"></a><a href="spimsg.md#a575755ef9506c10199c47f636f1de1de">rbuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p242213128093536"><a name="p242213128093536"></a><a name="p242213128093536"></a>uint8_t * </p>
</td>
</tr>
<tr id="row1113072598093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p397782377093536"><a name="p397782377093536"></a><a name="p397782377093536"></a><a href="spimsg.md#acb96c50b34d79d00277cbea9881b701a">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281651279093536"><a name="p1281651279093536"></a><a name="p1281651279093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row1630423946093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2063294090093536"><a name="p2063294090093536"></a><a name="p2063294090093536"></a><a href="spimsg.md#adff9e15325aab2afb066a1f3489b55d5">speed</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p55600477093536"><a name="p55600477093536"></a><a name="p55600477093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row467009160093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133361194093536"><a name="p1133361194093536"></a><a name="p1133361194093536"></a><a href="spimsg.md#a443b7f63c6b33719759eacf600da3aab">delayUs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1732082272093536"><a name="p1732082272093536"></a><a name="p1732082272093536"></a>uint16_t </p>
</td>
</tr>
<tr id="row2135809515093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157342109093536"><a name="p1157342109093536"></a><a name="p1157342109093536"></a><a href="spimsg.md#a1a38a03e30428aca7054cc8555b749a9">csChange</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303965571093536"><a name="p1303965571093536"></a><a name="p1303965571093536"></a>uint8_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1174205876093536"></a>

## **Field Documentation**<a name="section1091996063093536"></a>

## csChange<a name="a1a38a03e30428aca7054cc8555b749a9"></a>

```
uint8_t SpiMsg::csChange
```

 **Description:**

Whether to switch off the CS before the next transfer when the current transfer has been completed.  **1**  indicates to switch off the CS;  **0**  indicates to switch on the CS. 

## delayUs<a name="a443b7f63c6b33719759eacf600da3aab"></a>

```
uint16_t SpiMsg::delayUs
```

 **Description:**

Delay \(in microseconds\) before starting the next transfer. The value  **0**  indicates there is no delay between transfers. 

## len<a name="acb96c50b34d79d00277cbea9881b701a"></a>

```
uint32_t SpiMsg::len
```

 **Description:**

Length of the read and write buffers. The read buffer and the write buffer have the same length. 

## rbuf<a name="a575755ef9506c10199c47f636f1de1de"></a>

```
uint8_t* SpiMsg::rbuf
```

 **Description:**

Address of the read buffer 

## speed<a name="adff9e15325aab2afb066a1f3489b55d5"></a>

```
uint32_t SpiMsg::speed
```

 **Description:**

Current message transfer speed 

## wbuf<a name="ae2aed8b3bd1d75a50f82c880a45cf521"></a>

```
uint8_t* SpiMsg::wbuf
```

 **Description:**

Address of the write buffer 

