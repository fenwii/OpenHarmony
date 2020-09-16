# wifiiot\_adc.h<a name="EN-US_TOPIC_0000001055075073"></a>

## **Overview**<a name="section112078328191854"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the ADC interface functions for you to read data. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section233919436191854"></a>

## Enumerations<a name="enum-members"></a>

<a name="table2054246429191854"></a>
<table><thead align="left"><tr id="row204622648191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p608306791191854"><a name="p608306791191854"></a><a name="p608306791191854"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1968974614191854"><a name="p1968974614191854"></a><a name="p1968974614191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1887911635191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859368802191854"><a name="p1859368802191854"></a><a name="p1859368802191854"></a><a href="wifiiot.md#ga4c8b663163c7b23071914947a2bca73b">WifiIotAdcChannelIndex</a> {   <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73bafe850394965c1431bf6fa82471a12540">WIFI_IOT_ADC_CHANNEL_0</a>, <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73bab418db8068026df85efc38e86543b2f8">WIFI_IOT_ADC_CHANNEL_1</a>, <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73ba9fb27592172d4ed7652afb7eb67df4f7">WIFI_IOT_ADC_CHANNEL_2</a>, <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73ba80a93121e6990776a192d0e2a25f4420">WIFI_IOT_ADC_CHANNEL_3</a>,   <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73bae5516e741e66cab4fac522aac5a4cd13">WIFI_IOT_ADC_CHANNEL_4</a>, <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73ba462ea6a6767d412e7599fe1c258bd277">WIFI_IOT_ADC_CHANNEL_5</a>, <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73bac973eb63cc515666c23bd2a743aaeab9">WIFI_IOT_ADC_CHANNEL_6</a>, <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73bab6811d77d85f9280fb12ab02de1ed784">WIFI_IOT_ADC_CHANNEL_7</a>,   <a href="wifiiot.md#gga4c8b663163c7b23071914947a2bca73bab50fa87c837f92c0c93b4b24ca7b6a04">WIFI_IOT_ADC_CHANNEL_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075408095191854"><a name="p1075408095191854"></a><a name="p1075408095191854"></a>Enumerates ADC channel indexes. </p>
</td>
</tr>
<tr id="row1215506408191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1517257063191854"><a name="p1517257063191854"></a><a name="p1517257063191854"></a><a href="wifiiot.md#gaac161eb7075f815f6d39a63615bfa82d">WifiIotAdcCurBais</a> {   <a href="wifiiot.md#ggaac161eb7075f815f6d39a63615bfa82da610431a53604392e121dbd6b760de1b0">WIFI_IOT_ADC_CUR_BAIS_DEFAULT</a>, <a href="wifiiot.md#ggaac161eb7075f815f6d39a63615bfa82da0b63185aa983959d4fdc6158d23dbb82">WIFI_IOT_ADC_CUR_BAIS_AUTO</a>, <a href="wifiiot.md#ggaac161eb7075f815f6d39a63615bfa82dafd16a8f9dbcebb676d920e7708782ff0">WIFI_IOT_ADC_CUR_BAIS_1P8V</a>, <a href="wifiiot.md#ggaac161eb7075f815f6d39a63615bfa82da28c17a3bb256e352492c06421b890bc9">WIFI_IOT_ADC_CUR_BAIS_3P3V</a>,   <a href="wifiiot.md#ggaac161eb7075f815f6d39a63615bfa82da7f2ef39248469813c6e99bdc6a1f5b25">WIFI_IOT_ADC_CUR_BAIS_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p490616047191854"><a name="p490616047191854"></a><a name="p490616047191854"></a>Enumerates analog power control modes. </p>
</td>
</tr>
<tr id="row578226971191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1754310665191854"><a name="p1754310665191854"></a><a name="p1754310665191854"></a><a href="wifiiot.md#gafb9992ebf1655f994dc56883c8fe4b2e">WifiIotAdcEquModelSel</a> {   <a href="wifiiot.md#ggafb9992ebf1655f994dc56883c8fe4b2ea4e277052ddc958f8cbbe3476061bb08c">WIFI_IOT_ADC_EQU_MODEL_1</a>, <a href="wifiiot.md#ggafb9992ebf1655f994dc56883c8fe4b2ea1607975f67fcf1ecd9a12c2ff8007a73">WIFI_IOT_ADC_EQU_MODEL_2</a>, <a href="wifiiot.md#ggafb9992ebf1655f994dc56883c8fe4b2ea2ebb62372c9b0ecd305d5833f8ebee32">WIFI_IOT_ADC_EQU_MODEL_4</a>, <a href="wifiiot.md#ggafb9992ebf1655f994dc56883c8fe4b2eac1d53c7c2cdc479296e2adfec8f7de6b">WIFI_IOT_ADC_EQU_MODEL_8</a>,   <a href="wifiiot.md#ggafb9992ebf1655f994dc56883c8fe4b2ea6c73c22db275621900ad3594106af20c">WIFI_IOT_ADC_EQU_MODEL_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1332022793191854"><a name="p1332022793191854"></a><a name="p1332022793191854"></a>Enumerates equation models. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table766518734191854"></a>
<table><thead align="left"><tr id="row919310821191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1293845767191854"><a name="p1293845767191854"></a><a name="p1293845767191854"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p272062378191854"><a name="p272062378191854"></a><a name="p272062378191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row873072958191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896691631191854"><a name="p1896691631191854"></a><a name="p1896691631191854"></a><a href="wifiiot.md#ga6e43b3c41859efd279c9a539a4e38731">AdcRead</a> (<a href="wifiiot.md#ga4c8b663163c7b23071914947a2bca73b">WifiIotAdcChannelIndex</a> channel, unsigned short *data, <a href="wifiiot.md#gafb9992ebf1655f994dc56883c8fe4b2e">WifiIotAdcEquModelSel</a> equModel, <a href="wifiiot.md#gaac161eb7075f815f6d39a63615bfa82d">WifiIotAdcCurBais</a> curBais, unsigned short rstCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p562999549191854"><a name="p562999549191854"></a><a name="p562999549191854"></a>unsigned int </p>
<p id="p1376349906191854"><a name="p1376349906191854"></a><a name="p1376349906191854"></a>Reads a piece of sampled data from a specified ADC channel based on the input parameters. </p>
</td>
</tr>
</tbody>
</table>

