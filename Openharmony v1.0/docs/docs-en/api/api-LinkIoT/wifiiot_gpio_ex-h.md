# wifiiot\_gpio\_ex.h<a name="EN-US_TOPIC_0000001054796533"></a>

## **Overview**<a name="section714291261191855"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the extended GPIO interface functions. 

These functions are used for settings GPIO pulls and driver strength. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1699297835191855"></a>

## Enumerations<a name="enum-members"></a>

<a name="table1346680983191855"></a>
<table><thead align="left"><tr id="row1923223240191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p463847437191855"><a name="p463847437191855"></a><a name="p463847437191855"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1541683396191855"><a name="p1541683396191855"></a><a name="p1541683396191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row941234300191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p227114784191855"><a name="p227114784191855"></a><a name="p227114784191855"></a><a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> {   <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a97963c85f73b7efc5df2b4e791518dd6">WIFI_IOT_IO_NAME_GPIO_0</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a5a7f8f802106534ed2fcff69e70d5223">WIFI_IOT_IO_NAME_GPIO_1</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415ab491c9b7b4854b1bed8fe93fb1d1c039">WIFI_IOT_IO_NAME_GPIO_2</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a294203a8cfbf7effec255f87c8e58781">WIFI_IOT_IO_NAME_GPIO_3</a>,   <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a8d055a5e935871680109ca2e9ceb3d86">WIFI_IOT_IO_NAME_GPIO_4</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a2a7792d90d0fd908967bb8b116b7a72d">WIFI_IOT_IO_NAME_GPIO_5</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415aad36530a39eb4cfa2faa2903b41c2adc">WIFI_IOT_IO_NAME_GPIO_6</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415aa2d160d6184312c399dc5c6e0453a499">WIFI_IOT_IO_NAME_GPIO_7</a>,   <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a5795930c51751bdac0acb70fe2f78225">WIFI_IOT_IO_NAME_GPIO_8</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a3aa2a8978276384c825dc55f386b6aa6">WIFI_IOT_IO_NAME_GPIO_9</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a10c27fe57a83adc596834140b497a318">WIFI_IOT_IO_NAME_GPIO_10</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a9490124d4cb5c76607c3c7eaf4a3f388">WIFI_IOT_IO_NAME_GPIO_11</a>,   <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415ae4a090169da74a374b2f693d42e8d22c">WIFI_IOT_IO_NAME_GPIO_12</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415ada638b112db327afb19b352a27ba4649">WIFI_IOT_IO_NAME_GPIO_13</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a42eb2173954adcd9a3eed481df2d4bd2">WIFI_IOT_IO_NAME_GPIO_14</a>, <a href="wifiiot.md#gga2f42c70f1dd8a04746e30a97b3dfc415a736421d5c5f92bae9262a8bf1058dfd8">WIFI_IOT_IO_NAME_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827688024191855"><a name="p1827688024191855"></a><a name="p1827688024191855"></a>Enumerates GPIO hardware pin IDs. </p>
</td>
</tr>
<tr id="row748543777191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p672095043191855"><a name="p672095043191855"></a><a name="p672095043191855"></a><a href="wifiiot.md#ga2b08eb2a302e2c4fa216a1373bea4a01">WifiIotIoFuncGpio0</a> {   <a href="wifiiot.md#gga2b08eb2a302e2c4fa216a1373bea4a01afb74c7f71f79f223937187b960cd5366">WIFI_IOT_IO_FUNC_GPIO_0_GPIO</a>, <a href="wifiiot.md#gga2b08eb2a302e2c4fa216a1373bea4a01a56f807eaf7e6c867430756964f5fd895">WIFI_IOT_IO_FUNC_GPIO_0_UART1_TXD</a> = 2, <a href="wifiiot.md#gga2b08eb2a302e2c4fa216a1373bea4a01aa918b50f788a9260b8f76d3e3122b113">WIFI_IOT_IO_FUNC_GPIO_0_SPI1_CK</a>, <a href="wifiiot.md#gga2b08eb2a302e2c4fa216a1373bea4a01a5f47990c1eac7597fe91c101ce0a1925">WIFI_IOT_IO_FUNC_GPIO_0_JTAG_TDO</a>,   <a href="wifiiot.md#gga2b08eb2a302e2c4fa216a1373bea4a01ace60a126e858f4281a4cc7d7a2cd4e0c">WIFI_IOT_IO_FUNC_GPIO_0_PWM3_OUT</a>, <a href="wifiiot.md#gga2b08eb2a302e2c4fa216a1373bea4a01a17f92e6fa9b18b21f0749889fdb2a827">WIFI_IOT_IO_FUNC_GPIO_0_I2C1_SDA</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931018453191855"><a name="p931018453191855"></a><a name="p931018453191855"></a>Enumerates the functions of GPIO hardware pin 0. </p>
</td>
</tr>
<tr id="row818982764191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099804926191855"><a name="p2099804926191855"></a><a name="p2099804926191855"></a><a href="wifiiot.md#gae9c6ae0f852d8701036823a6223adf7e">WifiiIotIoFuncGpio1</a> { <a href="wifiiot.md#ggae9c6ae0f852d8701036823a6223adf7ea97ed23afc3bd351f4592d10203104983">WIFI_IOT_IO_FUNC_GPIO_1_GPIO</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2129370089191855"><a name="p2129370089191855"></a><a name="p2129370089191855"></a>Enumerates the functions of GPIO hardware pin 1. </p>
</td>
</tr>
<tr id="row754706440191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1378806986191855"><a name="p1378806986191855"></a><a name="p1378806986191855"></a><a href="wifiiot.md#gac9d0974184776d35ca9b0f73829f317b">WifiIotIoFuncGpio2</a> {   <a href="wifiiot.md#ggac9d0974184776d35ca9b0f73829f317ba9e9e5978a41b3e8a98afc8341d8118aa">WIFI_IOT_IO_FUNC_GPIO_2_GPIO</a>, <a href="wifiiot.md#ggac9d0974184776d35ca9b0f73829f317ba43585a8b91976d3e6ab9ab24f78be34e">WIFI_IOT_IO_FUNC_GPIO_2_UART1_RTS_N</a> = 2, <a href="wifiiot.md#ggac9d0974184776d35ca9b0f73829f317ba57c97e076eed823905fa8a0dcc48a95d">WIFI_IOT_IO_FUNC_GPIO_2_SPI1_TXD</a>, <a href="wifiiot.md#ggac9d0974184776d35ca9b0f73829f317ba930dbfc4b167e2952ee27edb5affacc2">WIFI_IOT_IO_FUNC_GPIO_2_JTAG_TRSTN</a>,   <a href="wifiiot.md#ggac9d0974184776d35ca9b0f73829f317ba33d45d0432d5a5d59c92526c1567e3a8">WIFI_IOT_IO_FUNC_GPIO_2_PWM2_OUT</a>, <a href="wifiiot.md#ggac9d0974184776d35ca9b0f73829f317bacedc367f8cfcfa29a326e83a35bf7cb4">WIFI_IOT_IO_FUNC_GPIO_2_SSI_CLK</a> = 7 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1306968485191855"><a name="p1306968485191855"></a><a name="p1306968485191855"></a>Enumerates the functions of GPIO hardware pin 2. </p>
</td>
</tr>
<tr id="row1204772861191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p243258400191855"><a name="p243258400191855"></a><a name="p243258400191855"></a><a href="wifiiot.md#gaca745c98fc2ef9994e67444c9aa53db8">WifiIotIoFuncGpio3</a> {   <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8a900852cb44e4e5683293935b1638542c">WIFI_IOT_IO_FUNC_GPIO_3_GPIO</a>, <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8ab73e5c02208920999b8b90563cef3966">WIFI_IOT_IO_FUNC_GPIO_3_UART0_TXD</a>, <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8a9781f77096742039e4179f2c7bf5bcc9">WIFI_IOT_IO_FUNC_GPIO_3_UART1_CTS_N</a>, <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8acad4b35de5675ce4e0e4d182e93e024a">WIFI_IOT_IO_FUNC_GPIO_3_SPI1_CSN</a>,   <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8acbe7ac3fc1f3b7885c6fab1b349b530f">WIFI_IOT_IO_FUNC_GPIO_3_JTAG_TDI</a>, <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8ab6fc7d2ba28c9541492fa5b9242f489f">WIFI_IOT_IO_FUNC_GPIO_3_PWM5_OUT</a>, <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8aefe458d1134ebc716c4f0ac4a0a7e87f">WIFI_IOT_IO_FUNC_GPIO_3_I2C1_SDA</a>, <a href="wifiiot.md#ggaca745c98fc2ef9994e67444c9aa53db8ae1f7cb6f32e78a2f4f676c154b26a84a">WIFI_IOT_IO_FUNC_GPIO_3_SSI_DATA</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141988592191855"><a name="p1141988592191855"></a><a name="p1141988592191855"></a>Enumerates the functions of GPIO hardware pin 3. </p>
</td>
</tr>
<tr id="row1874411640191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832690429191855"><a name="p832690429191855"></a><a name="p832690429191855"></a><a href="wifiiot.md#ga70218b6740d703737739ce4372e2f1e2">WifiIotIoFuncGpio4</a> {   <a href="wifiiot.md#gga70218b6740d703737739ce4372e2f1e2addbb34e879ddba03407a4229116c23ac">WIFI_IOT_IO_FUNC_GPIO_4_GPIO</a>, <a href="wifiiot.md#gga70218b6740d703737739ce4372e2f1e2a1fc155f21a4132b19f63559bcff1f7f9">WIFI_IOT_IO_FUNC_GPIO_4_UART0_RXD</a> = 2, <a href="wifiiot.md#gga70218b6740d703737739ce4372e2f1e2a6acf3b98636223ca6978c72954b62003">WIFI_IOT_IO_FUNC_GPIO_4_JTAG_TMS</a> = 4, <a href="wifiiot.md#gga70218b6740d703737739ce4372e2f1e2a32dd2cc66001ab46db29bb846c52197e">WIFI_IOT_IO_FUNC_GPIO_4_PWM1_OUT</a>,   <a href="wifiiot.md#gga70218b6740d703737739ce4372e2f1e2ae543e2931a4f36ac0325c1540855d661">WIFI_IOT_IO_FUNC_GPIO_4_I2C1_SCL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1413819347191855"><a name="p1413819347191855"></a><a name="p1413819347191855"></a>Enumerates the functions of GPIO hardware pin 4. </p>
</td>
</tr>
<tr id="row2043658420191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116967066191855"><a name="p2116967066191855"></a><a name="p2116967066191855"></a><a href="wifiiot.md#ga6cbed71f3a94f8e7513c4b91ae1e54ce">WifiIotIoFuncGpio5</a> {   <a href="wifiiot.md#gga6cbed71f3a94f8e7513c4b91ae1e54cea2627264cdc21a54b73d0f7e3d21c3b5f">WIFI_IOT_IO_FUNC_GPIO_5_GPIO</a>, <a href="wifiiot.md#gga6cbed71f3a94f8e7513c4b91ae1e54cea20e6b45cd687dee2ebb1dde55cf02860">WIFI_IOT_IO_FUNC_GPIO_5_UART1_RXD</a> = 2, <a href="wifiiot.md#gga6cbed71f3a94f8e7513c4b91ae1e54cea314bb175969cdf4b56dd38ef648fc409">WIFI_IOT_IO_FUNC_GPIO_5_SPI0_CSN</a>, <a href="wifiiot.md#gga6cbed71f3a94f8e7513c4b91ae1e54cea4944d83dcad39cfdbbc75bd2a72cb4ea">WIFI_IOT_IO_FUNC_GPIO_5_PWM2_OUT</a> = 5,   <a href="wifiiot.md#gga6cbed71f3a94f8e7513c4b91ae1e54cea5aaf6d79a5325bba396a32e240ee689e">WIFI_IOT_IO_FUNC_GPIO_5_I2S0_MCLK</a>, <a href="wifiiot.md#gga6cbed71f3a94f8e7513c4b91ae1e54ceaef4ff12208ea1aec33b99924f1d31f7e">WIFI_IOT_IO_FUNC_GPIO_5_BT_STATUS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221900176191855"><a name="p1221900176191855"></a><a name="p1221900176191855"></a>Enumerates the functions of GPIO hardware pin 5. </p>
</td>
</tr>
<tr id="row2125104688191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1248045812191855"><a name="p1248045812191855"></a><a name="p1248045812191855"></a><a href="wifiiot.md#ga42008386d7791b97dbfa1fa6b6c4dc1d">WifiIotIoFuncGpio6</a> {   <a href="wifiiot.md#gga42008386d7791b97dbfa1fa6b6c4dc1dab62d9164a716b5adb9e19e8836ab7a86">WIFI_IOT_IO_FUNC_GPIO_6_GPIO</a>, <a href="wifiiot.md#gga42008386d7791b97dbfa1fa6b6c4dc1da2ddce114a7cc5e36018dbcccc51aa18f">WIFI_IOT_IO_FUNC_GPIO_6_UART1_TXD</a> = 2, <a href="wifiiot.md#gga42008386d7791b97dbfa1fa6b6c4dc1da135b58a503fcb9597cc6dc121a31ce20">WIFI_IOT_IO_FUNC_GPIO_6_SPI0_CK</a>, <a href="wifiiot.md#gga42008386d7791b97dbfa1fa6b6c4dc1da592f96e2859ccd5d12df5395a32d7960">WIFI_IOT_IO_FUNC_GPIO_6_PWM3_OUT</a> = 5,   <a href="wifiiot.md#gga42008386d7791b97dbfa1fa6b6c4dc1dad35204fd9982ec2bc34e8b6761ccf6b1">WIFI_IOT_IO_FUNC_GPIO_6_I2S0_TX</a>, <a href="wifiiot.md#gga42008386d7791b97dbfa1fa6b6c4dc1da57cca649a73e43ba821859c3a70c0c4f">WIFI_IOT_IO_FUNC_GPIO_6_COEX_SWITCH</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1903805650191855"><a name="p1903805650191855"></a><a name="p1903805650191855"></a>Enumerates the functions of GPIO hardware pin 6. </p>
</td>
</tr>
<tr id="row394032662191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901842529191855"><a name="p1901842529191855"></a><a name="p1901842529191855"></a><a href="wifiiot.md#gac66dc390f39e0933c051790b20552b7c">WifiIotIoFuncGpio7</a> {   <a href="wifiiot.md#ggac66dc390f39e0933c051790b20552b7ca73da6d7633e44681a31b770f10b06aed">WIFI_IOT_IO_FUNC_GPIO_7_GPIO</a>, <a href="wifiiot.md#ggac66dc390f39e0933c051790b20552b7cae1c90084d66c48ebadc657e7b41d4d5a">WIFI_IOT_IO_FUNC_GPIO_7_UART1_CTS_N</a> = 2, <a href="wifiiot.md#ggac66dc390f39e0933c051790b20552b7ca5ef6f43f43355ff8fd9c2fefa53081b4">WIFI_IOT_IO_FUNC_GPIO_7_SPI0_RXD</a>, <a href="wifiiot.md#ggac66dc390f39e0933c051790b20552b7ca06bc301e0d776922e9d4b236d3a30e99">WIFI_IOT_IO_FUNC_GPIO_7_PWM0_OUT</a> = 5,   <a href="wifiiot.md#ggac66dc390f39e0933c051790b20552b7ca23fe50b89ddd6af8cafff14a58cba4bb">WIFI_IOT_IO_FUNC_GPIO_7_I2S0_BCLK</a>, <a href="wifiiot.md#ggac66dc390f39e0933c051790b20552b7ca20325d806adef2ddbb4c553662b1da55">WIFI_IOT_IO_FUNC_GPIO_7_BT_ACTIVE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673206689191855"><a name="p1673206689191855"></a><a name="p1673206689191855"></a>Enumerates the functions of GPIO hardware pin 7. </p>
</td>
</tr>
<tr id="row1131072795191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527128916191855"><a name="p1527128916191855"></a><a name="p1527128916191855"></a><a href="wifiiot.md#gae63cd3d5c677fac3b01a3c67e8faf0fb">WifiIotIoFuncGpio8</a> {   <a href="wifiiot.md#ggae63cd3d5c677fac3b01a3c67e8faf0fba6539bffea7913b2a60021c181a0594ef">WIFI_IOT_IO_FUNC_GPIO_8_GPIO</a>, <a href="wifiiot.md#ggae63cd3d5c677fac3b01a3c67e8faf0fba2da69d8ed888cc62f9a2f1b51a011fe8">WIFI_IOT_IO_FUNC_GPIO_8_UART1_RTS_N</a> = 2, <a href="wifiiot.md#ggae63cd3d5c677fac3b01a3c67e8faf0fba13aeec689990e7dc07081faabe165350">WIFI_IOT_IO_FUNC_GPIO_8_SPI0_TXD</a>, <a href="wifiiot.md#ggae63cd3d5c677fac3b01a3c67e8faf0fba7567a0979b39fdc708d5162920260749">WIFI_IOT_IO_FUNC_GPIO_8_PWM1_OUT</a> = 5,   <a href="wifiiot.md#ggae63cd3d5c677fac3b01a3c67e8faf0fba8d67e0d5b97a805d6b080fe280998c9e">WIFI_IOT_IO_FUNC_GPIO_8_I2S0_WS</a>, <a href="wifiiot.md#ggae63cd3d5c677fac3b01a3c67e8faf0fbae605af66f479ef031dccf609f2b38d44">WIFI_IOT_IO_FUNC_GPIO_8_WLAN_ACTIVE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298400775191855"><a name="p298400775191855"></a><a name="p298400775191855"></a>Enumerates the functions of GPIO hardware pin 8. </p>
</td>
</tr>
<tr id="row1263273151191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396515134191855"><a name="p1396515134191855"></a><a name="p1396515134191855"></a><a href="wifiiot.md#ga641da9889bd5a8a758e1a4eb2a5a19e4">WifiIotIoFuncGpio9</a> {   <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4a350d1fbb9b4821c4b0145245cc1b20ae">WIFI_IOT_IO_FUNC_GPIO_9_GPIO</a>, <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4a619cf8d896cf5567dae216d51cb941d7">WIFI_IOT_IO_FUNC_GPIO_9_I2C0_SCL</a>, <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4aafa2a6520f7d641e640675ab6a3b020d">WIFI_IOT_IO_FUNC_GPIO_9_UART2_RTS_N</a>, <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4a1988d957b5d66e06cd649849d59eaaf6">WIFI_IOT_IO_FUNC_GPIO_9_SDIO_D2</a>,   <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4a5a92c3f1f65d07814ce0c9ddce14d321">WIFI_IOT_IO_FUNC_GPIO_9_SPI0_TXD</a>, <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4ae35b5602e39b9168dc52d6f4bdf027fd">WIFI_IOT_IO_FUNC_GPIO_9_PWM0_OUT</a>, <a href="wifiiot.md#gga641da9889bd5a8a758e1a4eb2a5a19e4a2408d710172cf78129e56f729083c855">WIFI_IOT_IO_FUNC_GPIO_9_I2S0_MCLK</a> = 7 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327261295191855"><a name="p1327261295191855"></a><a name="p1327261295191855"></a>Enumerates the functions of GPIO hardware pin 9. </p>
</td>
</tr>
<tr id="row671900722191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p347001875191855"><a name="p347001875191855"></a><a name="p347001875191855"></a><a href="wifiiot.md#gad4670688ad729f40424bccfeb1afc3b2">WifiIotIoFuncGpio10</a> {   <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2a980bb121945c694bbe897de946945267">WIFI_IOT_IO_FUNC_GPIO_10_GPIO</a>, <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2acfb8d0df44e655a80d5788dddd08804b">WIFI_IOT_IO_FUNC_GPIO_10_I2C0_SDA</a>, <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2a71e59d7f1ef0e39a776a9b2513bf4542">WIFI_IOT_IO_FUNC_GPIO_10_UART2_CTS_N</a>, <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2aa0b0898a65f7ac13a733fcba77bc21d0">WIFI_IOT_IO_FUNC_GPIO_10_SDIO_D3</a>,   <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2aaf71bf6e3ffc24dfa41be0ef7d30a7a4">WIFI_IOT_IO_FUNC_GPIO_10_SPI0_CK</a>, <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2a273d2a5cc021d3f70de7598706da190b">WIFI_IOT_IO_FUNC_GPIO_10_PWM1_OUT</a>, <a href="wifiiot.md#ggad4670688ad729f40424bccfeb1afc3b2a3659f2aa6eda13221af2782569b7f7ba">WIFI_IOT_IO_FUNC_GPIO_10_I2S0_TX</a> = 7 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139072309191855"><a name="p1139072309191855"></a><a name="p1139072309191855"></a>Enumerates the functions of GPIO hardware pin 10. </p>
</td>
</tr>
<tr id="row1161784794191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916899317191855"><a name="p1916899317191855"></a><a name="p1916899317191855"></a><a href="wifiiot.md#ga5099248aa82355e85ba5a6227f2ab1a7">WifiIotIoFuncGpio11</a> {   <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7aa4116d6aa72f96dd5b9ef648ef642be3">WIFI_IOT_IO_FUNC_GPIO_11_GPIO</a>, <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7a6a1f4f4f8d97c39820c4d2b0a41d8e57">WIFI_IOT_IO_FUNC_GPIO_11_UART2_TXD</a> = 2, <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7aa9313853653525a833917ed4d964741d">WIFI_IOT_IO_FUNC_GPIO_11_SDIO_CMD</a>, <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7a144ce7df4661202d80898acb2ade8b24">WIFI_IOT_IO_FUNC_GPIO_11_SPI0_RXD</a>,   <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7a51f2c16d8b2df9e730fb919db696c3dc">WIFI_IOT_IO_FUNC_GPIO_11_PWM2_OUT</a>, <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7aa6da0b5b2e9c8ba7657e995969f0db7b">WIFI_IOT_IO_FUNC_GPIO_11_RF_TX_EN_EXT</a>, <a href="wifiiot.md#gga5099248aa82355e85ba5a6227f2ab1a7a04954f86710fcfd0ddf5cc7bcb5e09ee">WIFI_IOT_IO_FUNC_GPIO_11_I2S0_RX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910803656191855"><a name="p1910803656191855"></a><a name="p1910803656191855"></a>Enumerates the functions of GPIO hardware pin 11. </p>
</td>
</tr>
<tr id="row71608615191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1059426275191855"><a name="p1059426275191855"></a><a name="p1059426275191855"></a><a href="wifiiot.md#gaed0008f886fc864d90f6d1c2ae9677a0">WifiIotIoFuncGpio12</a> {   <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0a51521f4b32e2bf093ac6d1adf2489ad3">WIFI_IOT_IO_FUNC_GPIO_12_GPIO</a>, <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0a72cfe0d59218319d28b82c996e8061dc">WIFI_IOT_IO_FUNC_GPIO_12_UART2_RXD</a> = 2, <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0adb573f70a428b79007c934637f954f45">WIFI_IOT_IO_FUNC_GPIO_12_SDIO_CLK</a>, <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0a5b8d84bb7b7729bb039d1d862064a505">WIFI_IOT_IO_FUNC_GPIO_12_SPI0_CSN</a>,   <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0a6ec0171f11721b9c27b7182167de4ca7">WIFI_IOT_IO_FUNC_GPIO_12_PWM3_OUT</a>, <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0a93a3914b6cf990c5a31ba21fc68b37c8">WIFI_IOT_IO_FUNC_GPIO_12_RF_RX_EN_EXT</a>, <a href="wifiiot.md#ggaed0008f886fc864d90f6d1c2ae9677a0a42708c43bf265eae320df358fd737146">WIFI_IOT_IO_FUNC_GPIO_12_I2S0_BCLK</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p358111920191855"><a name="p358111920191855"></a><a name="p358111920191855"></a>Enumerates the functions of GPIO hardware pin 12. </p>
</td>
</tr>
<tr id="row1265377075191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14034757191855"><a name="p14034757191855"></a><a name="p14034757191855"></a><a href="wifiiot.md#ga364b7c7cc88086ad40c4c3d2dd098648">WifiIotIoFuncGpio13</a> {   <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a0f2b57575a4463b8cb0141f2313f5ad7">WIFI_IOT_IO_FUNC_GPIO_13_SSI_DATA</a>, <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a8605c5abf1d51e5f279345cb1b7ee93b">WIFI_IOT_IO_FUNC_GPIO_13_UART0_TXD</a>, <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a6300109a97003b70942f0157bdbd93a2">WIFI_IOT_IO_FUNC_GPIO_13_UART2_RTS_N</a>, <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a041cef6b72032e671fa448e2ccd87c0d">WIFI_IOT_IO_FUNC_GPIO_13_SDIO_D0</a>,   <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a5fa81c0c0bc86f0c7af184b0da088f70">WIFI_IOT_IO_FUNC_GPIO_13_GPIO</a>, <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a3ee8f8ce9db21a7752af81d023f02700">WIFI_IOT_IO_FUNC_GPIO_13_PWM4_OUT</a>, <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648ac9ee6ac9fae28de25c222350db957be3">WIFI_IOT_IO_FUNC_GPIO_13_I2C0_SDA</a>, <a href="wifiiot.md#gga364b7c7cc88086ad40c4c3d2dd098648a68d69347b2c3e25ed68ee56672789c70">WIFI_IOT_IO_FUNC_GPIO_13_I2S0_WS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338189786191855"><a name="p1338189786191855"></a><a name="p1338189786191855"></a>Enumerates the functions of GPIO hardware pin 13. </p>
</td>
</tr>
<tr id="row1693674190191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1611461836191855"><a name="p1611461836191855"></a><a name="p1611461836191855"></a><a href="wifiiot.md#gafcf6d4cb0113b803d834bac89af8d9b8">WifiIotIoFuncGpio14</a> {   <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8ad3c279c96d416bb679a12632e043c869">WIFI_IOT_IO_FUNC_GPIO_14_SSI_CLK</a>, <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8a74b51226f0832c4e8e178098ca5b52da">WIFI_IOT_IO_FUNC_GPIO_14_UART0_RXD</a>, <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8a41d571aaeb611fedd801d2623b53ed3b">WIFI_IOT_IO_FUNC_GPIO_14_UART2_CTS_N</a>, <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8a02e3f6f241d4088eb5245726c528705e">WIFI_IOT_IO_FUNC_GPIO_14_SDIO_D1</a>,   <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8adc43efa86c4218d6749732899cfff9bd">WIFI_IOT_IO_FUNC_GPIO_14_GPIO</a>, <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8acd2191145a6a0aeac212036d8c763a88">WIFI_IOT_IO_FUNC_GPIO_14_PWM5_OUT</a>, <a href="wifiiot.md#ggafcf6d4cb0113b803d834bac89af8d9b8aa2b4ea5f2d923bb163ad52a8d6bece2c">WIFI_IOT_IO_FUNC_GPIO_14_I2C0_SCL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p696172478191855"><a name="p696172478191855"></a><a name="p696172478191855"></a>Enumerates the functions of GPIO hardware pin 14. </p>
</td>
</tr>
<tr id="row493352952191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p733664900191855"><a name="p733664900191855"></a><a name="p733664900191855"></a><a href="wifiiot.md#gae97ab4109f511ceeee889dba9e79a968">WifiIotIoDriverStrength</a> {   <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a3640019ffd659132e3cb7ca0d91451b0">WIFI_IOT_IO_DRIVER_STRENGTH_0</a> = 0, <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a1c4db14256c5ad110440d2b124f104bd">WIFI_IOT_IO_DRIVER_STRENGTH_1</a>, <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a6626c0ecb0ac767493f3705d91045c33">WIFI_IOT_IO_DRIVER_STRENGTH_2</a>, <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a1eb7957f7c27f4e347ee9779fa5cf525">WIFI_IOT_IO_DRIVER_STRENGTH_3</a>,   <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968ab073c01bd41de1e31b8850e7c927a9c0">WIFI_IOT_IO_DRIVER_STRENGTH_4</a>, <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a0daaac21180250d6f49dfc4de4c441fb">WIFI_IOT_IO_DRIVER_STRENGTH_5</a>, <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968ae966a5dd645a6699507b6901c2a02734">WIFI_IOT_IO_DRIVER_STRENGTH_6</a>, <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a048d5db3385e0e40561af665b6dc914f">WIFI_IOT_IO_DRIVER_STRENGTH_7</a>,   <a href="wifiiot.md#ggae97ab4109f511ceeee889dba9e79a968a6a751b7c9907d1ac9eb89be807c13506">WIFI_IOT_IO_DRIVER_STRENGTH_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1940553004191855"><a name="p1940553004191855"></a><a name="p1940553004191855"></a>Enumerates I/O driver strength levels. </p>
</td>
</tr>
<tr id="row188735532191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1929724730191855"><a name="p1929724730191855"></a><a name="p1929724730191855"></a><a href="wifiiot.md#gacc20a5c6456ec381ed931232c29d1c4f">WifiIotIoPull</a> { <a href="wifiiot.md#ggacc20a5c6456ec381ed931232c29d1c4fa8699edd19f2fe1c8e2e0f843c100b665">WIFI_IOT_IO_PULL_NONE</a>, <a href="wifiiot.md#ggacc20a5c6456ec381ed931232c29d1c4fa101a6db99a7c37721ee35dfdb93bf705">WIFI_IOT_IO_PULL_UP</a>, <a href="wifiiot.md#ggacc20a5c6456ec381ed931232c29d1c4fa61e259c36a0567f7ca43ff7abd1b1d81">WIFI_IOT_IO_PULL_DOWN</a>, <a href="wifiiot.md#ggacc20a5c6456ec381ed931232c29d1c4fa4d8b63c757a91e4dc317fb4e9b8e2955">WIFI_IOT_IO_PULL_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1626436920191855"><a name="p1626436920191855"></a><a name="p1626436920191855"></a>Enumerates GPIO pull-up or pull-down settings. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table700213932191855"></a>
<table><thead align="left"><tr id="row1135034810191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1705089723191855"><a name="p1705089723191855"></a><a name="p1705089723191855"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1557842670191855"><a name="p1557842670191855"></a><a name="p1557842670191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1431638042191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1436768789191855"><a name="p1436768789191855"></a><a name="p1436768789191855"></a><a href="wifiiot.md#ga372f6e774614f5b4e7280c9e564be5a2">IoSetPull</a> (<a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> id, <a href="wifiiot.md#gacc20a5c6456ec381ed931232c29d1c4f">WifiIotIoPull</a> val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1212835318191855"><a name="p1212835318191855"></a><a name="p1212835318191855"></a>unsigned int </p>
<p id="p143088046191855"><a name="p143088046191855"></a><a name="p143088046191855"></a>Sets the pull for a GPIO pin. </p>
</td>
</tr>
<tr id="row1214420909191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1986833851191855"><a name="p1986833851191855"></a><a name="p1986833851191855"></a><a href="wifiiot.md#ga706a98bedbef79002c43efcb98b841ab">IoSetFunc</a> (<a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> id, unsigned char val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749841875191855"><a name="p749841875191855"></a><a name="p749841875191855"></a>unsigned int </p>
<p id="p953474949191855"><a name="p953474949191855"></a><a name="p953474949191855"></a>Sets the multiplexing function for a GPIO pin. </p>
</td>
</tr>
<tr id="row1808513915191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1973366603191855"><a name="p1973366603191855"></a><a name="p1973366603191855"></a><a href="wifiiot.md#ga899a2d8d5a058bcd9d32dbce43a9dbb2">IoGetPull</a> (<a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> id, <a href="wifiiot.md#gacc20a5c6456ec381ed931232c29d1c4f">WifiIotIoPull</a> *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327149614191855"><a name="p1327149614191855"></a><a name="p1327149614191855"></a>unsigned int </p>
<p id="p38986411191855"><a name="p38986411191855"></a><a name="p38986411191855"></a>Obtains the pull type of a GPIO pin. </p>
</td>
</tr>
<tr id="row279108655191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p847359784191855"><a name="p847359784191855"></a><a name="p847359784191855"></a><a href="wifiiot.md#ga4131898393c55a07abf254dc7f2a9541">IoGetFunc</a> (<a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> id, unsigned char *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p240121022191855"><a name="p240121022191855"></a><a name="p240121022191855"></a>unsigned int </p>
<p id="p283154257191855"><a name="p283154257191855"></a><a name="p283154257191855"></a>Obtains the multiplexing function for a GPIO pin. </p>
</td>
</tr>
<tr id="row716609789191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1677140020191855"><a name="p1677140020191855"></a><a name="p1677140020191855"></a><a href="wifiiot.md#ga64e637417c653b431c67cf4445fc8e65">IOGetDriverStrength</a> (<a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> id, <a href="wifiiot.md#gae97ab4109f511ceeee889dba9e79a968">WifiIotIoDriverStrength</a> *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785812322191855"><a name="p785812322191855"></a><a name="p785812322191855"></a>unsigned int </p>
<p id="p717161299191855"><a name="p717161299191855"></a><a name="p717161299191855"></a>Obtains the driver strength of a GPIO pin. </p>
</td>
</tr>
<tr id="row802220655191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p114466196191855"><a name="p114466196191855"></a><a name="p114466196191855"></a><a href="wifiiot.md#ga631065a13f9794dc0b4de4870e62cfaa">IOSetDriverStrength</a> (<a href="wifiiot.md#ga2f42c70f1dd8a04746e30a97b3dfc415">WifiIotIoName</a> id, <a href="wifiiot.md#gae97ab4109f511ceeee889dba9e79a968">WifiIotIoDriverStrength</a> val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970081170191855"><a name="p1970081170191855"></a><a name="p1970081170191855"></a>unsigned int </p>
<p id="p1172105982191855"><a name="p1172105982191855"></a><a name="p1172105982191855"></a>Sets the driver strength of a GPIO pin. </p>
</td>
</tr>
</tbody>
</table>

