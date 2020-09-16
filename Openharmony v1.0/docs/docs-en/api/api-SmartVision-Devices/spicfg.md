# SpiCfg<a name="EN-US_TOPIC_0000001054879570"></a>

## **Overview**<a name="section1832731980093536"></a>

**Related Modules:**

[SPI](spi.md)

**Description:**

Defines the configuration of an SPI device. 

**Since:**

1.0

## **Summary**<a name="section1045912211093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1524085202093536"></a>
<table><thead align="left"><tr id="row1591948315093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1900822034093536"><a name="p1900822034093536"></a><a name="p1900822034093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1452336588093536"><a name="p1452336588093536"></a><a name="p1452336588093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row605127639093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1410244348093536"><a name="p1410244348093536"></a><a name="p1410244348093536"></a><a href="spicfg.md#a81369e5879c93f2747375dffbd5f975d">maxSpeedHz</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287571163093536"><a name="p287571163093536"></a><a name="p287571163093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row11235886093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813205940093536"><a name="p1813205940093536"></a><a name="p1813205940093536"></a><a href="spicfg.md#a48b7732e7d6e53d5af6ad5ce36cb96d3">mode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798402484093536"><a name="p1798402484093536"></a><a name="p1798402484093536"></a>uint16_t </p>
</td>
</tr>
<tr id="row958582605093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p211305601093536"><a name="p211305601093536"></a><a name="p211305601093536"></a><a href="spicfg.md#a4193f45f83d1501f5e0ead393e1e55a1">transferMode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1272984649093536"><a name="p1272984649093536"></a><a name="p1272984649093536"></a>uint8_t </p>
</td>
</tr>
<tr id="row1528771526093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p37181509093536"><a name="p37181509093536"></a><a name="p37181509093536"></a><a href="spicfg.md#ac671a8fc23e2998243695c7bd27232f3">bitsPerWord</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492783748093536"><a name="p492783748093536"></a><a name="p492783748093536"></a>uint8_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section601892321093536"></a>

## **Field Documentation**<a name="section1068126293093536"></a>

## bitsPerWord<a name="ac671a8fc23e2998243695c7bd27232f3"></a>

```
uint8_t SpiCfg::bitsPerWord
```

 **Description:**

Data transfer bit width 

## maxSpeedHz<a name="a81369e5879c93f2747375dffbd5f975d"></a>

```
uint32_t SpiCfg::maxSpeedHz
```

 **Description:**

Maximum clock frequency 

## mode<a name="a48b7732e7d6e53d5af6ad5ce36cb96d3"></a>

```
uint16_t SpiCfg::mode
```

## transferMode<a name="a4193f45f83d1501f5e0ead393e1e55a1"></a>

```
uint8_t SpiCfg::transferMode
```

 **Description:**

Data transfer mode, as defined in  [SpiTransferMode](spi.md#ga55946d1d895fc2b7b33007019de1668f). 

