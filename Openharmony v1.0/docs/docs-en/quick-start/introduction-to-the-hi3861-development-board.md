# Introduction to the Hi3861 Development Board<a name="EN-US_TOPIC_0000001053142605"></a>

This document describes how to quickly start with the Hi3861 WLAN module, including the development environment setup, version compiling and building, device burning, source code modification, debugging and verification. Following this guide, you can start developing services with the basic understanding of the Hi3861 WLAN module.

## Hi3861<a name="section187215231809"></a>

The Hi3861 WLAN module is a development board with 2 x 5 cm form factor. It contains a 2.4 GHz WLAN SoC chip that highly integrates the IEEE 802.11b/g/n baseband and radio frequency \(RF\) circuit. This module provides open and easy-to-use development and debugging environments for running OpenHarmony.

**Figure  1**  Appearance of Hi3861 WLAN module<a name="fig74884420237"></a>  
![](figures/appearance-of-hi3861-wlan-module.png "appearance-of-hi3861-wlan-module")

The Hi3861 WLAN module can also be connected to the Hi3861 mother board to expand its peripheral capabilities. The following figure shows the Hi3861 mother board.

**Figure  2**  Appearance of the Hi3861 mother board<a name="fig16947112194216"></a>  
![](figures/appearance-of-the-hi3861-mother-board.png "appearance-of-the-hi3861-mother-board")

-   The RF circuit includes modules such as the power amplifier \(PA\), low noise amplifier \(LNA\), RF Balun, antenna switch, and power management. It supports a standard bandwidth of 20 MHz and a narrow bandwidth of 5 MHz or 10 MHz, and provides a maximum rate of 72.2 Mbit/s at the physical layer.
-   The Hi3861 WLAN baseband supports the orthogonal frequency division multiplexing \(OFDM\) technology and is backward compatible with the direct sequence spread spectrum \(DSSS\) and complementary code keying \(CCK\) technologies. In addition, the Hi3861 WLAN baseband supports various data rates complying with the IEEE 802.11 b/g/n protocol.
-   The Hi3861 chip integrates the high-performance 32-bit microprocessor, hardware security engine, and various peripheral interfaces. The peripheral interfaces include the Synchronous Peripheral Interface \(SPI\), Universal Asynchronous Receiver & Transmitter \(UART\), the Inter Integrated Circuit \(I2C\), Pulse Width Modulation \(PWM\), General Purpose Input/Output \(GPIO\) interface, and Analog to Digital Converter \(ADC\). The Hi3861 chip also supports the high-speed Secure Digital Input/Output \(SDIO\) 2.0 interface, with a maximum clock frequency of 50 MHz. This chip has a built-in static random access memory \(SRAM\) and flash memory, which can run programs independently or run from a flash drive.
-   The Hi3861 chip applies to Internet of Things \(IoT\) devices such as smart home appliances.

    **Figure  3**  Hi3861 functions<a name="f0d52fa2f3b094c688c805a373a6ec970"></a>  
    

    ![](figures/en-us_image_0000001055187339.png)


## Resources and Constraints<a name="section82610215014"></a>

As the Hi3861 only offers 2 MB Flash and 352 KB RAM, use them efficiently when compiling code.

## Development Board Specifications<a name="section169054431017"></a>

**Table  1**  Hi3861 WLAN module specifications

<a name="t672b053e2ac94cbdb5244857fed4764e"></a>
<table><thead align="left"><tr id="r54b3810e43d24e1887c1d6a41394996b"><th class="cellrowborder" valign="top" width="18.02%" id="mcps1.2.3.1.1"><p id="a2b235e9ed55f4338886788f140e648a0"><a name="a2b235e9ed55f4338886788f140e648a0"></a><a name="a2b235e9ed55f4338886788f140e648a0"></a>Type</p>
</th>
<th class="cellrowborder" valign="top" width="81.98%" id="mcps1.2.3.1.2"><p id="a95c4ba2e404f4a45b65984746aaa56ab"><a name="a95c4ba2e404f4a45b65984746aaa56ab"></a><a name="a95c4ba2e404f4a45b65984746aaa56ab"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="r71f534ea66af4191b020408df5978f41"><td class="cellrowborder" valign="top" width="18.02%" headers="mcps1.2.3.1.1 "><p id="a0531f1bb62d5443880576cc5de23f2e6"><a name="a0531f1bb62d5443880576cc5de23f2e6"></a><a name="a0531f1bb62d5443880576cc5de23f2e6"></a>General specifications</p>
</td>
<td class="cellrowborder" valign="top" width="81.98%" headers="mcps1.2.3.1.2 "><a name="u2a0d06f28d454d30818ced9a0432211b"></a><a name="u2a0d06f28d454d30818ced9a0432211b"></a><ul id="u2a0d06f28d454d30818ced9a0432211b"><li>Operates over 1×1 2.4 GHz frequency band (ch1-ch14).</li><li>The physical layer (PHY) complies with the IEEE 802.11b/g/n protocol.</li><li>The media access control (MAC) layer complies with the IEEE802.11 d/e/h/i/k/v/w protocol.</li></ul>
<a name="ul1452913133017"></a><a name="ul1452913133017"></a><ul id="ul1452913133017"><li>Includes the built-in public address (PA) and local area network (LAN); integrates transmit-receive (Tx/Rx) switch and Balun. </li><li>Supports the station (STA) and access point (AP) modes. When the Hi3861 WLAN module functions as an AP, a maximum of six STAs are supported.</li><li>Supports WPA and WPA2 from WFA (personal), and WPS 2.0.</li><li>Supports three kinds of packet traffic arbiter (PTA) (2- , 3- , or 4-wire PTA), each of which coexists with the BT or BLE chip.</li><li>The input voltage ranges from 2.3 V to 3.6 V.</li></ul>
<a name="ul15885141153113"></a><a name="ul15885141153113"></a><ul id="ul15885141153113"><li>The input/output (I/O) power voltage can be 1.8 V or 3.3 V.</li></ul>
<a name="ul128863113316"></a><a name="ul128863113316"></a><ul id="ul128863113316"><li>Supports self-calibration for RF hardware.</li><li>Performs with low power consumption:<a name="ul1588651114317"></a><a name="ul1588651114317"></a><ul id="ul1588651114317"><li>Ultra deep sleep mode: 5 μA@3.3</li><li>VDTIM1: 1.5mA@3.3V</li><li>DTIM3: 0.8mA@3.3V</li></ul>
</li></ul>
</td>
</tr>
<tr id="rd9b56e759af34950b6887ca1bf5bb7cf"><td class="cellrowborder" valign="top" width="18.02%" headers="mcps1.2.3.1.1 "><p id="a0aed3860a78a4b50bedf60699afd3996"><a name="a0aed3860a78a4b50bedf60699afd3996"></a><a name="a0aed3860a78a4b50bedf60699afd3996"></a>PHY features</p>
</td>
<td class="cellrowborder" valign="top" width="81.98%" headers="mcps1.2.3.1.2 "><a name="u6568aa052152432aa1f44372445ca634"></a><a name="u6568aa052152432aa1f44372445ca634"></a><ul id="u6568aa052152432aa1f44372445ca634"><li>Supports all data rates of the single antenna required by the IEEE802.11b/g/n protocol.</li><li>Supports a maximum rate of 72.2 Mbit/s@HT20 MCS7.</li><li>Supports the standard bandwidth (20 MHz) and narrow bandwidth (5 MHz or 10 MHz).</li><li>Supports space-time block coding (STBC).</li><li>Supports short guard interval (Short-GI).</li></ul>
</td>
</tr>
<tr id="r3563f9df9759486794952d46c5d2d03f"><td class="cellrowborder" valign="top" width="18.02%" headers="mcps1.2.3.1.1 "><p id="afd48a2d879dc4aada8b60bebb96523c7"><a name="afd48a2d879dc4aada8b60bebb96523c7"></a><a name="afd48a2d879dc4aada8b60bebb96523c7"></a>MAC features</p>
</td>
<td class="cellrowborder" valign="top" width="81.98%" headers="mcps1.2.3.1.2 "><a name="uca57d799e7814925a5bf1b891335bd79"></a><a name="uca57d799e7814925a5bf1b891335bd79"></a><ul id="uca57d799e7814925a5bf1b891335bd79"><li>Supports aggregate MAC service data unit (A-MPDU) and aggregate MAC protocol data unit (A-MSDU). </li><li>Supports block acknowledgment (Blk-ACK).</li><li>Supports quality of service (QoS), meeting customer's service requirements.</li></ul>
</td>
</tr>
<tr id="r3e1c86e5f6cd4df0a1b30a08fb8481a2"><td class="cellrowborder" valign="top" width="18.02%" headers="mcps1.2.3.1.1 "><p id="a57086ea97a1b46cdb21953bf0fc22d94"><a name="a57086ea97a1b46cdb21953bf0fc22d94"></a><a name="a57086ea97a1b46cdb21953bf0fc22d94"></a>CPU subsystem</p>
</td>
<td class="cellrowborder" valign="top" width="81.98%" headers="mcps1.2.3.1.2 "><a name="u612cc2cd0cfe40229263c4f506c0c69c"></a><a name="u612cc2cd0cfe40229263c4f506c0c69c"></a><ul id="u612cc2cd0cfe40229263c4f506c0c69c"><li>Integrates a high-performance 32-bit microprocessor with a maximum operating frequency of 160 MHz.</li><li>Includes built-in 352 KB SRAM and 288 KB ROM.</li><li>Includes a built-in 2 MB flash memory.</li></ul>
</td>
</tr>
<tr id="rae93c5236b084cd2a2c0d5c29027b40e"><td class="cellrowborder" valign="top" width="18.02%" headers="mcps1.2.3.1.1 "><p id="a9b14a9e95b3849278c332259d8add1b2"><a name="a9b14a9e95b3849278c332259d8add1b2"></a><a name="a9b14a9e95b3849278c332259d8add1b2"></a>Peripheral interfaces</p>
</td>
<td class="cellrowborder" valign="top" width="81.98%" headers="mcps1.2.3.1.2 "><a name="u7c73ebffd89e4092bd65f0d878d59b22"></a><a name="u7c73ebffd89e4092bd65f0d878d59b22"></a><ul id="u7c73ebffd89e4092bd65f0d878d59b22"><li>Include one SDIO interface, two SPI interfaces, two I2C interfaces, three UART interfaces, 15 GPIO interfaces, seven ADC inputs, six PWM interfaces, and one I2S interface (Note: These interfaces are all multiplexed.)</li><li>The frequency of the external primary crystal oscillator is 40 MHz or 24 MHz.</li></ul>
</td>
</tr>
<tr id="r18810701aafe42ad8d9a7d882730c210"><td class="cellrowborder" valign="top" width="18.02%" headers="mcps1.2.3.1.1 "><p id="ae8f47db913724e458c265e858409950b"><a name="ae8f47db913724e458c265e858409950b"></a><a name="ae8f47db913724e458c265e858409950b"></a>Other information</p>
</td>
<td class="cellrowborder" valign="top" width="81.98%" headers="mcps1.2.3.1.2 "><a name="u25f28919a3b044c5af50f9f5f5616083"></a><a name="u25f28919a3b044c5af50f9f5f5616083"></a><ul id="u25f28919a3b044c5af50f9f5f5616083"><li>Package: QFN-32, 5 mm x 5 mm</li><li>Operating temperature: –40&deg;C to +85&deg;C</li></ul>
</td>
</tr>
</tbody>
</table>

## Key Features<a name="section1317173016507"></a>

OpenHarmony provides a series of available capabilities based on the Hi3861 platform. The following table describes the available key components.

**Table  2**  Key components

<a name="table1659013482514"></a>
<table><thead align="left"><tr id="row1368918486512"><th class="cellrowborder" valign="top" width="22.56%" id="mcps1.2.3.1.1"><p id="p668914812516"><a name="p668914812516"></a><a name="p668914812516"></a>Component</p>
</th>
<th class="cellrowborder" valign="top" width="77.44%" id="mcps1.2.3.1.2"><p id="p9689154855115"><a name="p9689154855115"></a><a name="p9689154855115"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row868910487517"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p13689248165114"><a name="p13689248165114"></a><a name="p13689248165114"></a>wlan</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p11689144816511"><a name="p11689144816511"></a><a name="p11689144816511"></a>Provides WLAN service, such as connecting to or disconnecting from a station or hotspot, and querying the state of a station or hotspot.</p>
</td>
</tr>
<tr id="row568964819514"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p5689548175113"><a name="p5689548175113"></a><a name="p5689548175113"></a>iot controller</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p176893480517"><a name="p176893480517"></a><a name="p176893480517"></a>Provides the capability of operating peripherals, including the I2C, I2S, ADC, UART, SPI, SDIO, GPIO, PWM and FLASH.</p>
</td>
</tr>
<tr id="row143420119366"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p1737117331480"><a name="p1737117331480"></a><a name="p1737117331480"></a>soft bus</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p1037123314485"><a name="p1037123314485"></a><a name="p1037123314485"></a>Provides the capabilities of device discovery and data transmission in the distributed network.</p>
</td>
</tr>
<tr id="row1383559163617"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p2379233113914"><a name="p2379233113914"></a><a name="p2379233113914"></a>hichainsdk</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p5809349205012"><a name="p5809349205012"></a><a name="p5809349205012"></a>Provides the capability of securely transferring data between devices when they are interconnected.</p>
</td>
</tr>
<tr id="row54428163612"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p3775133619587"><a name="p3775133619587"></a><a name="p3775133619587"></a>huks</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p11304151710555"><a name="p11304151710555"></a><a name="p11304151710555"></a>Provides capabilities of key management, encryption, and decryption.</p>
</td>
</tr>
<tr id="row12690548135110"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p176901648115111"><a name="p176901648115111"></a><a name="p176901648115111"></a>system ability manager</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p1181353173111"><a name="p1181353173111"></a><a name="p1181353173111"></a>Provides a unified <span id="text10778141516322"><a name="text10778141516322"></a><a name="text10778141516322"></a>OpenHarmony</span> service development framework based on the service-oriented architecture.</p>
</td>
</tr>
<tr id="row1657310121587"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p730664220114"><a name="p730664220114"></a><a name="p730664220114"></a>bootstrap</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p39689262310"><a name="p39689262310"></a><a name="p39689262310"></a>Provides the entry identifier for starting a system service. When the system service management is started, the function identified by <strong id="b1954132834115"><a name="b1954132834115"></a><a name="b1954132834115"></a>bootstrap</strong> is called to start a system service.</p>
</td>
</tr>
<tr id="row15763812165616"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p17171118128"><a name="p17171118128"></a><a name="p17171118128"></a>syspara</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p12763912125617"><a name="p12763912125617"></a><a name="p12763912125617"></a>Provides capabilities of obtaining and setting system attributes.</p>
</td>
</tr>
<tr id="row121911343566"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p1097517270361"><a name="p1097517270361"></a><a name="p1097517270361"></a>utils</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p6848159569"><a name="p6848159569"></a><a name="p6848159569"></a>Provides basic and public capabilities, such as file operations and key-value (KV) storage management.</p>
</td>
</tr>
<tr id="row144219192579"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p8333104843714"><a name="p8333104843714"></a><a name="p8333104843714"></a>DFX</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p65111025155711"><a name="p65111025155711"></a><a name="p65111025155711"></a>Provides the DFX capabilities, such as logging and printing.</p>
</td>
</tr>
<tr id="row16159522125710"><td class="cellrowborder" valign="top" width="22.56%" headers="mcps1.2.3.1.1 "><p id="p18835202765718"><a name="p18835202765718"></a><a name="p18835202765718"></a>XTS</p>
</td>
<td class="cellrowborder" valign="top" width="77.44%" headers="mcps1.2.3.1.2 "><p id="p3835192795717"><a name="p3835192795717"></a><a name="p3835192795717"></a>Provides a set of <span id="text1482414523409"><a name="text1482414523409"></a><a name="text1482414523409"></a>OpenHarmony</span> certification test suites.</p>
</td>
</tr>
</tbody>
</table>

