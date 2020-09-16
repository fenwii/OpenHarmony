# Introduction to the Hi3516 Development Board<a name="EN-US_TOPIC_0000001053666242"></a>

Hi3516DV300 is a new-generation SoC designed for the industry-dedicated smart HD IP camera. It introduces a new-generation ISP, the latest H.265 video compression encoder, and a high-performance NNIE engine, enabling Hi3516C V500 to lead the industry in terms of low bit rate, high image quality, intelligent processing and analysis, and low power consumption. Integrated with the POR, RTC, audio codec, and standby wakeup circuit, Hi3516DV300 can greatly reduce the EBOM costs for customers.

**Figure  1**  Front view of the Hi3516 board<a name="fig14733910122619"></a>  
![](figures/front-view-of-the-hi3516-board.png "front-view-of-the-hi3516-board")

**Figure  2**  Rear view of the Hi3516 board<a name="fig09411014103"></a>  
![](figures/rear-view-of-the-hi3516-board.png "rear-view-of-the-hi3516-board")

## Software Environment of the Development Board<a name="section25411622111510"></a>

**Table  1**  Description of the software environment

<a name="table857411917716"></a>
<table><thead align="left"><tr id="row10572391876"><th class="cellrowborder" valign="top" width="12.96129612961296%" id="mcps1.2.4.1.1"><p id="p15721991076"><a name="p15721991076"></a><a name="p15721991076"></a>Hardware</p>
</th>
<th class="cellrowborder" valign="top" width="13.451345134513451%" id="mcps1.2.4.1.2"><p id="p12572992711"><a name="p12572992711"></a><a name="p12572992711"></a>Software</p>
</th>
<th class="cellrowborder" valign="top" width="73.5873587358736%" id="mcps1.2.4.1.3"><p id="p157259675"><a name="p157259675"></a><a name="p157259675"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row257399674"><td class="cellrowborder" rowspan="4" valign="top" width="12.96129612961296%" headers="mcps1.2.4.1.1 "><p id="p6573491873"><a name="p6573491873"></a><a name="p6573491873"></a>Hi3516DV300</p>
<p id="p1557309778"><a name="p1557309778"></a><a name="p1557309778"></a>IoT camera board</p>
</td>
<td class="cellrowborder" valign="top" width="13.451345134513451%" headers="mcps1.2.4.1.2 "><p id="p1457312911712"><a name="p1457312911712"></a><a name="p1457312911712"></a>bootstrap program</p>
</td>
<td class="cellrowborder" valign="top" width="73.5873587358736%" headers="mcps1.2.4.1.3 "><p id="p557314918720"><a name="p557314918720"></a><a name="p557314918720"></a>U-Boot</p>
</td>
</tr>
<tr id="row12574209673"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p115735914711"><a name="p115735914711"></a><a name="p115735914711"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p12574891579"><a name="p12574891579"></a><a name="p12574891579"></a>Huawei-developed operating system HOSP (including the OHOS kernel, application framework, and service framework)</p>
</td>
</tr>
<tr id="row8574109778"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p105741291677"><a name="p105741291677"></a><a name="p105741291677"></a>Application software</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p175745912715"><a name="p175745912715"></a><a name="p175745912715"></a>Shell (Starts as the system boots)</p>
</td>
</tr>
<tr id="row10574691678"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1357420914719"><a name="p1357420914719"></a><a name="p1357420914719"></a>Program development library</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p195747915717"><a name="p195747915717"></a><a name="p195747915717"></a>musl 1.x</p>
</td>
</tr>
</tbody>
</table>

## Development Board Specifications<a name="section15192203316533"></a>

**Table  2**  Specification list of the Hi3516 development board

<a name="table31714894311"></a>
<table><thead align="left"><tr id="row10171198194310"><th class="cellrowborder" valign="top" width="14.77%" id="mcps1.2.3.1.1"><p id="a2b235e9ed55f4338886788f140e648a0"><a name="a2b235e9ed55f4338886788f140e648a0"></a><a name="a2b235e9ed55f4338886788f140e648a0"></a>Type</p>
</th>
<th class="cellrowborder" valign="top" width="85.22999999999999%" id="mcps1.2.3.1.2"><p id="p9702458104014"><a name="p9702458104014"></a><a name="p9702458104014"></a>Specification</p>
</th>
</tr>
</thead>
<tbody><tr id="row0171168114311"><td class="cellrowborder" valign="top" width="14.77%" headers="mcps1.2.3.1.1 "><p id="p1698185431418"><a name="p1698185431418"></a><a name="p1698185431418"></a><strong id="b157831068243"><a name="b157831068243"></a><a name="b157831068243"></a>Processor and internal memory</strong></p>
</td>
<td class="cellrowborder" valign="top" width="85.22999999999999%" headers="mcps1.2.3.1.2 "><a name="ul1147113537186"></a><a name="ul1147113537186"></a><ul id="ul1147113537186"><li>Hi3516D V300</li><li>2 pieces of 16-bit-width DDR3, with 4 Gb capacity each particle</li><li>eMMC with 8 GB capacity</li></ul>
</td>
</tr>
<tr id="row21721687435"><td class="cellrowborder" valign="top" width="14.77%" headers="mcps1.2.3.1.1 "><p id="p817216810435"><a name="p817216810435"></a><a name="p817216810435"></a><strong id="b927893617261"><a name="b927893617261"></a><a name="b927893617261"></a>External Components</strong></p>
</td>
<td class="cellrowborder" valign="top" width="85.22999999999999%" headers="mcps1.2.3.1.2 "><a name="ul179543016208"></a><a name="ul179543016208"></a><ul id="ul179543016208"><li>Ethernet port</li><li>Audio and video<a name="ul5941311869"></a><a name="ul5941311869"></a><ul id="ul5941311869"><li>1-channel voice input</li><li>1-channel (AC_L) mono output, connected to a 3 W power amplifier (LM4871)</li><li>MicroHDMI (1-channel HDMI 1.4)</li></ul>
</li><li>Camera<a name="ul924263620"></a><a name="ul924263620"></a><ul id="ul924263620"><li>Sensor IMX335</li><li>M12 lens with a focal length of 4 mm and an aperture of 1.4</li></ul>
</li><li>Display<a name="ul101471711667"></a><a name="ul101471711667"></a><ul id="ul101471711667"><li>2.35-inch LCD connector</li><li>5.5-inch LCD connector</li></ul>
</li><li>External components and interfaces<a name="ul089255556"></a><a name="ul089255556"></a><ul id="ul089255556"><li>microSD card port circuit</li><li>JTAG/I2S interface</li><li>ADC interface</li><li>Steer gear interface</li><li>Grove connector</li><li>USB2.0(Type C)</li><li>Three function keys: two customized keys and one update key</li><li>LED indicator (including green and red)</li></ul>
</li></ul>
</td>
</tr>
</tbody>
</table>

