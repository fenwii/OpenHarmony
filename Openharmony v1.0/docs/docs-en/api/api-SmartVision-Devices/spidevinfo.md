# SpiDevInfo<a name="EN-US_TOPIC_0000001055039554"></a>

## **Overview**<a name="section548624705093536"></a>

**Related Modules:**

[SPI](spi.md)

**Description:**

Defines the general SPI device descriptor, which can be used as the unique identifier of an SPI device. When operating an SPI device, you need to specify a descriptor of the  [SpiDevInfo](spidevinfo.md)  type, and obtain the handle of the SPI device by calling  [SpiOpen](spi.md#ga073b44f262ca3b99fa632a1468bc1190). 

**Since:**

1.0

## **Summary**<a name="section246154454093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1425820810093536"></a>
<table><thead align="left"><tr id="row2040461848093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1924535466093536"><a name="p1924535466093536"></a><a name="p1924535466093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2134373422093536"><a name="p2134373422093536"></a><a name="p2134373422093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row820036119093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025411341093536"><a name="p2025411341093536"></a><a name="p2025411341093536"></a><a href="spidevinfo.md#a317656e748a353d8520d891e77c7b111">busNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540348039093536"><a name="p1540348039093536"></a><a name="p1540348039093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row1505882433093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933620294093536"><a name="p1933620294093536"></a><a name="p1933620294093536"></a><a href="spidevinfo.md#aff59a847b2a6144dd93047fff7841ec7">csNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443849757093536"><a name="p1443849757093536"></a><a name="p1443849757093536"></a>uint32_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1844358508093536"></a>

## **Field Documentation**<a name="section627503592093536"></a>

## busNum<a name="a317656e748a353d8520d891e77c7b111"></a>

```
uint32_t SpiDevInfo::busNum
```

 **Description:**

SPI bus number 

## csNum<a name="aff59a847b2a6144dd93047fff7841ec7"></a>

```
uint32_t SpiDevInfo::csNum
```

 **Description:**

SPI device chip select \(CS\) 

