# WLAN Overview<a name="EN-US_TOPIC_0000001051643558"></a>

## Introduction<a name="section23087361515"></a>

The WLAN module is developed based on the OpenHarmony Driver Foundation. It supports cross-OS migration, component adaptation, and modular assembly and compilation. Based on the unified APIs provided by the WLAN module, driver developers of WLAN vendors can adapt their driver code and developers of the hardware abstraction layer \(HAL\) are capable of creating, disabling, scanning, and connecting to WLAN hotspots. The following figure shows the framework of the WLAN module:

**Figure  1**  WLAN framework<a name="fig967034316227"></a>  


![](figures/wifi框架2.png)

## WLAN Driver API Architecture<a name="section1533192516212"></a>

The WLAN module provides the following three types of APIs:

-   APIs for HAL developers
-   APIs that can be called directly by driver developers
-   APIs for driver developers of different vendors to implement

This document provides guidelines on how to initialize a WLAN module.

**Figure  2**  Available APIs of the WLAN module<a name="fig15016395217"></a>  


![](figures/接口分布图1.png)

## Available APIs<a name="section87491484213"></a>

The WLAN driver module provides APIs for HAL developers, such as creating, disabling, scanning, connecting to or disconnecting from WLAN hotpots.

The WLAN driver module provides APIs that can be directly called by driver developers, such as creating/releasing a  **WifiModule**, connecting to/disconnecting from a WLAN hotspot, applying for/releasing a network data buffer, and converting between the  **pbuf**  structure of Lightweight TCP/IP Stack \(lwIP\) and a network data buffer.

Table 1 describes some APIs.

**Table  1**  APIs that can be directly called by driver developers

<a name="table1521573319472"></a>
<table><thead align="left"><tr id="row121519334474"><th class="cellrowborder" valign="top" width="15.079999999999998%" id="mcps1.2.4.1.1"><p id="p1221510339475"><a name="p1221510339475"></a><a name="p1221510339475"></a>File</p>
</th>
<th class="cellrowborder" valign="top" width="60.33%" id="mcps1.2.4.1.2"><p id="p0215153344716"><a name="p0215153344716"></a><a name="p0215153344716"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="24.59%" id="mcps1.2.4.1.3"><p id="p1421503315478"><a name="p1421503315478"></a><a name="p1421503315478"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row112150333476"><td class="cellrowborder" rowspan="4" valign="top" width="15.079999999999998%" headers="mcps1.2.4.1.1 "><p id="p2155710125317"><a name="p2155710125317"></a><a name="p2155710125317"></a>wifi_module.h</p>
<p id="p189132019183"><a name="p189132019183"></a><a name="p189132019183"></a></p>
</td>
<td class="cellrowborder" valign="top" width="60.33%" headers="mcps1.2.4.1.2 "><p id="p363110387399"><a name="p363110387399"></a><a name="p363110387399"></a>struct WifiModule *WifiModuleCreate(const struct HdfConfigWifiModuleConfig *config);</p>
</td>
<td class="cellrowborder" valign="top" width="24.59%" headers="mcps1.2.4.1.3 "><p id="p1363012387393"><a name="p1363012387393"></a><a name="p1363012387393"></a>Creates a <strong id="b17218103820131"><a name="b17218103820131"></a><a name="b17218103820131"></a>WifiModule</strong>.</p>
</td>
</tr>
<tr id="row112151233194714"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p7629163817393"><a name="p7629163817393"></a><a name="p7629163817393"></a>void WifiModuleDelete(struct WifiModule *module);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p2627638173917"><a name="p2627638173917"></a><a name="p2627638173917"></a>Deletes and releases data of a <strong id="b17674114211319"><a name="b17674114211319"></a><a name="b17674114211319"></a>WifiModule</strong>.</p>
</td>
</tr>
<tr id="row1121533316475"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p12626103814399"><a name="p12626103814399"></a><a name="p12626103814399"></a>int32_t DelFeature(struct WifiModule *module, uint16_t featureType);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1162543816393"><a name="p1162543816393"></a><a name="p1162543816393"></a>Deletes a feature from a <strong id="b12747104710136"><a name="b12747104710136"></a><a name="b12747104710136"></a>WifiModule</strong>.</p>
</td>
</tr>
<tr id="row172153335473"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p162433816392"><a name="p162433816392"></a><a name="p162433816392"></a>int32_t AddFeature(struct WifiModule *module, uint16_t featureType, struct WifiFeature *featureData);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p186235383393"><a name="p186235383393"></a><a name="p186235383393"></a>Adds a feature to a <strong id="b61351114111410"><a name="b61351114111410"></a><a name="b61351114111410"></a>WifiModule</strong>.</p>
</td>
</tr>
<tr id="row451796205011"><td class="cellrowborder" rowspan="4" valign="top" width="15.079999999999998%" headers="mcps1.2.4.1.1 "><p id="p2659417135013"><a name="p2659417135013"></a><a name="p2659417135013"></a>wifi_mac80211_ops.h</p>
</td>
<td class="cellrowborder" valign="top" width="60.33%" headers="mcps1.2.4.1.2 "><p id="p175181615011"><a name="p175181615011"></a><a name="p175181615011"></a>int32_t (*startAp)(NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" width="24.59%" headers="mcps1.2.4.1.3 "><p id="p195182610507"><a name="p195182610507"></a><a name="p195182610507"></a>Starts an AP.</p>
</td>
</tr>
<tr id="row5518663503"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p125181260501"><a name="p125181260501"></a><a name="p125181260501"></a>int32_t (*stopAp)(NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1151815635014"><a name="p1151815635014"></a><a name="p1151815635014"></a>Stops an AP.</p>
</td>
</tr>
<tr id="row851915617503"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p20519865500"><a name="p20519865500"></a><a name="p20519865500"></a>int32_t (*connect)(NetDevice *netDev, WifiConnectParams *param);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14519469509"><a name="p14519469509"></a><a name="p14519469509"></a>Starts a connection.</p>
</td>
</tr>
<tr id="row18519136185016"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p145195620502"><a name="p145195620502"></a><a name="p145195620502"></a>int32_t (*disconnect)(NetDevice *netDev, uint16_t reasonCode);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p175191863503"><a name="p175191863503"></a><a name="p175191863503"></a>Cancels a connection.</p>
</td>
</tr>
<tr id="row176421942125016"><td class="cellrowborder" rowspan="5" valign="top" width="15.079999999999998%" headers="mcps1.2.4.1.1 "><p id="p7937165012500"><a name="p7937165012500"></a><a name="p7937165012500"></a>hdf_netbuf.h</p>
</td>
<td class="cellrowborder" valign="top" width="60.33%" headers="mcps1.2.4.1.2 "><p id="p1964211423505"><a name="p1964211423505"></a><a name="p1964211423505"></a>static inline void NetBufQueueInit(struct NetBufQueue *q);</p>
</td>
<td class="cellrowborder" valign="top" width="24.59%" headers="mcps1.2.4.1.3 "><p id="p364254211507"><a name="p364254211507"></a><a name="p364254211507"></a>Initializes a network data buffer queue.</p>
</td>
</tr>
<tr id="row664264225020"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p166421942115017"><a name="p166421942115017"></a><a name="p166421942115017"></a>struct NetBuf *NetBufAlloc(uint32_t size);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p3642164215501"><a name="p3642164215501"></a><a name="p3642164215501"></a>Applies for a network data buffer.</p>
</td>
</tr>
<tr id="row19642134215018"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p964310425501"><a name="p964310425501"></a><a name="p964310425501"></a>void NetBufFree(struct NetBuf *nb);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1464312427503"><a name="p1464312427503"></a><a name="p1464312427503"></a>Releases a network data buffer.</p>
</td>
</tr>
<tr id="row7643194215013"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p20643164218508"><a name="p20643164218508"></a><a name="p20643164218508"></a>struct NetBuf *Pbuf2NetBuf(const struct NetDevice *netdev, struct pbuf *lwipBuf);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p186437429509"><a name="p186437429509"></a><a name="p186437429509"></a>Converts the <strong id="b108101241316"><a name="b108101241316"></a><a name="b108101241316"></a>pbuf</strong> structure of <strong id="b148154412318"><a name="b148154412318"></a><a name="b148154412318"></a>lwIP</strong> to a network data buffer.</p>
</td>
</tr>
<tr id="row7657132317518"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p86576231557"><a name="p86576231557"></a><a name="p86576231557"></a>struct pbuf *NetBuf2Pbuf(const struct NetBuf *nb);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1965702312510"><a name="p1965702312510"></a><a name="p1965702312510"></a>Converts a network data buffer to the <strong id="b993215663110"><a name="b993215663110"></a><a name="b993215663110"></a>pbuf</strong> structure of <strong id="b10933563310"><a name="b10933563310"></a><a name="b10933563310"></a>lwIP</strong>.</p>
</td>
</tr>
</tbody>
</table>

The WLAN driver module provides APIs for driver developers to implement capabilities, such as initializing/deregistering, opening/stopping a network device, and obtaining the state of a network device.

Table 2 describes some APIs.

**Table  2**  APIs for driver developers of WLAN vendors to implement

<a name="table74613501475"></a>
<table><thead align="left"><tr id="row194625016476"><th class="cellrowborder" valign="top" width="20.75%" id="mcps1.2.4.1.1"><p id="p10468502479"><a name="p10468502479"></a><a name="p10468502479"></a>File</p>
</th>
<th class="cellrowborder" valign="top" width="52.75%" id="mcps1.2.4.1.2"><p id="p184615501477"><a name="p184615501477"></a><a name="p184615501477"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="26.5%" id="mcps1.2.4.1.3"><p id="p1146135044719"><a name="p1146135044719"></a><a name="p1146135044719"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row04616509472"><td class="cellrowborder" rowspan="6" valign="top" width="20.75%" headers="mcps1.2.4.1.1 "><p id="p14615017477"><a name="p14615017477"></a><a name="p14615017477"></a>net_device.h</p>
</td>
<td class="cellrowborder" valign="top" width="52.75%" headers="mcps1.2.4.1.2 "><p id="p144943564611"><a name="p144943564611"></a><a name="p144943564611"></a>int32_t (*init)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" width="26.5%" headers="mcps1.2.4.1.3 "><p id="p18822442135411"><a name="p18822442135411"></a><a name="p18822442135411"></a>Initializes a network device.</p>
</td>
</tr>
<tr id="row1546250114713"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1490010315564"><a name="p1490010315564"></a><a name="p1490010315564"></a>struct NetDevStats *(*getStats)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p5900163115564"><a name="p5900163115564"></a><a name="p5900163115564"></a>Obtains the state of a network device.</p>
</td>
</tr>
<tr id="row1646165010470"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p16909135319564"><a name="p16909135319564"></a><a name="p16909135319564"></a>int32_t (*setMacAddr)(struct NetDevice *netDev, void *addr);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p122001431115713"><a name="p122001431115713"></a><a name="p122001431115713"></a>Sets the MAC address.</p>
</td>
</tr>
<tr id="row12471250184711"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p154213655215"><a name="p154213655215"></a><a name="p154213655215"></a>void (*deInit)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14845675719"><a name="p14845675719"></a><a name="p14845675719"></a>Deinitializes a network device.</p>
</td>
</tr>
<tr id="row13471050104719"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p16686131655218"><a name="p16686131655218"></a><a name="p16686131655218"></a>int32_t (*open)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p164825613576"><a name="p164825613576"></a><a name="p164825613576"></a>Opens a network device.</p>
</td>
</tr>
<tr id="row1747125054714"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2310615407"><a name="p2310615407"></a><a name="p2310615407"></a>int32_t (*stop)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1982212428542"><a name="p1982212428542"></a><a name="p1982212428542"></a>Stops a network device.</p>
</td>
</tr>
</tbody>
</table>

