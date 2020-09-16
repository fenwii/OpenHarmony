# ISurface<a name="EN-US_TOPIC_0000001055518092"></a>

## **Overview**<a name="section77468637093531"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Stores surface information for hardware acceleration, such as draw image, and bit blit. 

## **Summary**<a name="section1578109880093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2101552479093531"></a>
<table><thead align="left"><tr id="row1374822588093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1433976373093531"><a name="p1433976373093531"></a><a name="p1433976373093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p480426308093531"><a name="p480426308093531"></a><a name="p480426308093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1975690753093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702709694093531"><a name="p702709694093531"></a><a name="p702709694093531"></a><a href="isurface.md#aeac36e064994bcf2f2f1acc4b0f6a1ea">phyAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1595665026093531"><a name="p1595665026093531"></a><a name="p1595665026093531"></a>uint64_t </p>
</td>
</tr>
<tr id="row771586060093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000998757093531"><a name="p1000998757093531"></a><a name="p1000998757093531"></a><a href="isurface.md#ae68d2e393fe150b1bde8c312c36945c6">height</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517024595093531"><a name="p517024595093531"></a><a name="p517024595093531"></a>int32_t </p>
</td>
</tr>
<tr id="row28891287093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065052171093531"><a name="p1065052171093531"></a><a name="p1065052171093531"></a><a href="isurface.md#a3cc2e909bab924936e8273a237ddbb65">width</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259781867093531"><a name="p1259781867093531"></a><a name="p1259781867093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1420795017093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1209673488093531"><a name="p1209673488093531"></a><a name="p1209673488093531"></a><a href="isurface.md#a61ea4da3897aac944042e60df73554be">stride</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064065301093531"><a name="p2064065301093531"></a><a name="p2064065301093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1333787393093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p172889621093531"><a name="p172889621093531"></a><a name="p172889621093531"></a><a href="isurface.md#a260d540d41736284edc5a27c1ff46963">enColorFmt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p850338836093531"><a name="p850338836093531"></a><a name="p850338836093531"></a><a href="codec.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> </p>
</td>
</tr>
<tr id="row1621633371093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484630293093531"><a name="p484630293093531"></a><a name="p484630293093531"></a><a href="isurface.md#ad2693b11b0cefeed40070364f9e31e84">bYCbCrClut</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293511898093531"><a name="p293511898093531"></a><a name="p293511898093531"></a>bool </p>
</td>
</tr>
<tr id="row676301000093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564589565093531"><a name="p564589565093531"></a><a name="p564589565093531"></a><a href="isurface.md#a17f87b9850f83633f427eeceb74c93a7">bAlphaMax255</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p955676931093531"><a name="p955676931093531"></a><a name="p955676931093531"></a>bool </p>
</td>
</tr>
<tr id="row41002544093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829266267093531"><a name="p1829266267093531"></a><a name="p1829266267093531"></a><a href="isurface.md#a9d9ba9ee72ae25c0e84bfba10fe52f9a">bAlphaExt1555</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2017820989093531"><a name="p2017820989093531"></a><a name="p2017820989093531"></a>bool </p>
</td>
</tr>
<tr id="row211353025093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1198919755093531"><a name="p1198919755093531"></a><a name="p1198919755093531"></a><a href="isurface.md#ac2aa13d6c25df5d1a1fcfa92da425d29">alpha0</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807663949093531"><a name="p807663949093531"></a><a name="p807663949093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row399389261093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2105545223093531"><a name="p2105545223093531"></a><a name="p2105545223093531"></a><a href="isurface.md#a4fd217bfeb9d0a73992c797a900ba632">alpha1</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970331055093531"><a name="p1970331055093531"></a><a name="p1970331055093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row1136911060093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1466106312093531"><a name="p1466106312093531"></a><a name="p1466106312093531"></a><a href="isurface.md#adc8bc02eb42a881adf57caf06ddff243">cbcrPhyAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p850433995093531"><a name="p850433995093531"></a><a name="p850433995093531"></a>uint64_t </p>
</td>
</tr>
<tr id="row578373665093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082248186093531"><a name="p2082248186093531"></a><a name="p2082248186093531"></a><a href="isurface.md#a835f95df55db296dbf92061da1aa9627">cbcrStride</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564567463093531"><a name="p564567463093531"></a><a name="p564567463093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1256661903093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226955095093531"><a name="p226955095093531"></a><a name="p226955095093531"></a><a href="isurface.md#a98bca93c426df8030c0a67b8fba02525">clutPhyAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289686027093531"><a name="p289686027093531"></a><a name="p289686027093531"></a>uint64_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section670846132093531"></a>

## **Field Documentation**<a name="section2027447232093531"></a>

## alpha0<a name="ac2aa13d6c25df5d1a1fcfa92da425d29"></a>

```
uint8_t ISurface::alpha0
```

 **Description:**

Value of alpha0, ranging from 0 to 255 

## alpha1<a name="a4fd217bfeb9d0a73992c797a900ba632"></a>

```
uint8_t ISurface::alpha1
```

 **Description:**

Value of alpha1, ranging from 0 to 255 

## bAlphaExt1555<a name="a9d9ba9ee72ae25c0e84bfba10fe52f9a"></a>

```
bool ISurface::bAlphaExt1555
```

 **Description:**

ARGB1555 alpha extension enable bit 

## bAlphaMax255<a name="a17f87b9850f83633f427eeceb74c93a7"></a>

```
bool ISurface::bAlphaMax255
```

 **Description:**

Maximum alpha value of an image \(255 or 128\) 

## bYCbCrClut<a name="ad2693b11b0cefeed40070364f9e31e84"></a>

```
bool ISurface::bYCbCrClut
```

 **Description:**

Whether the color lookup table \(CLUT\) is in the YCbCr space 

## cbcrPhyAddr<a name="adc8bc02eb42a881adf57caf06ddff243"></a>

```
uint64_t ISurface::cbcrPhyAddr
```

 **Description:**

CbCr physical address 

## cbcrStride<a name="a835f95df55db296dbf92061da1aa9627"></a>

```
int32_t ISurface::cbcrStride
```

 **Description:**

CbCr stride 

## clutPhyAddr<a name="a98bca93c426df8030c0a67b8fba02525"></a>

```
uint64_t ISurface::clutPhyAddr
```

 **Description:**

Start physical address of the CLUT, used for color extension or correction 

## enColorFmt<a name="a260d540d41736284edc5a27c1ff46963"></a>

```
[PixelFormat](codec.md#ga60883d4958a60b91661e97027a85072a) ISurface::enColorFmt
```

 **Description:**

Image format 

## height<a name="ae68d2e393fe150b1bde8c312c36945c6"></a>

```
int32_t ISurface::height
```

 **Description:**

Image height 

## phyAddr<a name="aeac36e064994bcf2f2f1acc4b0f6a1ea"></a>

```
uint64_t ISurface::phyAddr
```

 **Description:**

Start physical address of an image 

## stride<a name="a61ea4da3897aac944042e60df73554be"></a>

```
int32_t ISurface::stride
```

 **Description:**

Image stride 

## width<a name="a3cc2e909bab924936e8273a237ddbb65"></a>

```
int32_t ISurface::width
```

 **Description:**

Image width 

