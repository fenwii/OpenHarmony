# WLAN开发概述<a name="ZH-CN_TOPIC_0000001051643558"></a>

## 简介<a name="section23087361515"></a>

WLAN是基于统一驱动平台（以下简称HDF）开发的模块，该模块可实现跨操作系统迁移，自适应器件差异，模块化拼装编译等功能。各WLAN厂商驱动开发人员可根据WLAN模块提供的向下统一接口适配各自的驱动代码，HAL层开发人员可根据WLAN模块提供的向上统一接口获取如下能力：建立/关闭WLAN热点，扫描，关联WLAN热点等等。WLAN模块框架图如下：

**图 1**  WLAN框架<a name="fig967034316227"></a>  


![](figures/WIFI框架2.png)

## WLAN驱动接口架构<a name="section1533192516212"></a>

WLAN模块有三部分对外开放的API接口，如下图所示：

1、对HAL层提供的能力接口；

2、驱动直接调用WLAN模块能力接口；

3、提供给各厂商实现的能力接口，本章节以下内容将从以初始化为例进行开发指导。

**图 2**  WLAN模块开放能力分布图<a name="fig15016395217"></a>  


![](figures/接口分布图1.png)

## 接口说明<a name="section87491484213"></a>

WLAN驱动模块对HAL层开发人员提供的接口功能有：建立/关闭WLAN热点、扫描WLAN、开始关联、断开连接等等。

WLAN驱动模块提供了驱动开发人员可直接调用的能力接口，主要功能有：创建/释放WifiModule、关联/取消关联、申请/释放net buf、lwip的pbuf和netbuf的相互转换等等。

表1 提供了部分接口说明如下：

**表 1**  可直接调用的接口

<a name="table1521573319472"></a>
<table><thead align="left"><tr id="row121519334474"><th class="cellrowborder" valign="top" width="15.079999999999998%" id="mcps1.2.4.1.1"><p id="p1221510339475"><a name="p1221510339475"></a><a name="p1221510339475"></a>头文件</p>
</th>
<th class="cellrowborder" valign="top" width="60.33%" id="mcps1.2.4.1.2"><p id="p0215153344716"><a name="p0215153344716"></a><a name="p0215153344716"></a>接口名称</p>
</th>
<th class="cellrowborder" valign="top" width="24.59%" id="mcps1.2.4.1.3"><p id="p1421503315478"><a name="p1421503315478"></a><a name="p1421503315478"></a>功能描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row112150333476"><td class="cellrowborder" rowspan="4" valign="top" width="15.079999999999998%" headers="mcps1.2.4.1.1 "><p id="p2155710125317"><a name="p2155710125317"></a><a name="p2155710125317"></a>wifi_module.h</p>
<p id="p189132019183"><a name="p189132019183"></a><a name="p189132019183"></a></p>
</td>
<td class="cellrowborder" valign="top" width="60.33%" headers="mcps1.2.4.1.2 "><p id="p363110387399"><a name="p363110387399"></a><a name="p363110387399"></a>struct WifiModule *WifiModuleCreate(const struct HdfConfigWifiModuleConfig *config);</p>
</td>
<td class="cellrowborder" valign="top" width="24.59%" headers="mcps1.2.4.1.3 "><p id="p1363012387393"><a name="p1363012387393"></a><a name="p1363012387393"></a>基于HDF开发WLAN驱动时，创建一个WifiModule。</p>
</td>
</tr>
<tr id="row112151233194714"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p7629163817393"><a name="p7629163817393"></a><a name="p7629163817393"></a>void WifiModuleDelete(struct WifiModule *module);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p2627638173917"><a name="p2627638173917"></a><a name="p2627638173917"></a>基于HDF开发WLAN驱动时，删除并释放WifiModule所有数据。</p>
</td>
</tr>
<tr id="row1121533316475"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p12626103814399"><a name="p12626103814399"></a><a name="p12626103814399"></a>int32_t DelFeature(struct WifiModule *module, uint16_t featureType);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1162543816393"><a name="p1162543816393"></a><a name="p1162543816393"></a>基于HDF开发WLAN驱动时，从WifiModule删除一个功能组件。</p>
</td>
</tr>
<tr id="row172153335473"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p162433816392"><a name="p162433816392"></a><a name="p162433816392"></a>int32_t AddFeature(struct WifiModule *module, uint16_t featureType, struct WifiFeature *featureData);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p186235383393"><a name="p186235383393"></a><a name="p186235383393"></a>基于HDF开发WLAN驱动时，注册一个功能组件到WifiModule。</p>
</td>
</tr>
<tr id="row451796205011"><td class="cellrowborder" rowspan="4" valign="top" width="15.079999999999998%" headers="mcps1.2.4.1.1 "><p id="p2659417135013"><a name="p2659417135013"></a><a name="p2659417135013"></a>wifi_mac80211_ops.h</p>
</td>
<td class="cellrowborder" valign="top" width="60.33%" headers="mcps1.2.4.1.2 "><p id="p175181615011"><a name="p175181615011"></a><a name="p175181615011"></a>int32_t (*startAp)(NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" width="24.59%" headers="mcps1.2.4.1.3 "><p id="p195182610507"><a name="p195182610507"></a><a name="p195182610507"></a>启动AP。</p>
</td>
</tr>
<tr id="row5518663503"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p125181260501"><a name="p125181260501"></a><a name="p125181260501"></a>int32_t (*stopAp)(NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1151815635014"><a name="p1151815635014"></a><a name="p1151815635014"></a>停止AP。</p>
</td>
</tr>
<tr id="row851915617503"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p20519865500"><a name="p20519865500"></a><a name="p20519865500"></a>int32_t (*connect)(NetDevice *netDev, WifiConnectParams *param);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14519469509"><a name="p14519469509"></a><a name="p14519469509"></a>开始连接。</p>
</td>
</tr>
<tr id="row18519136185016"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p145195620502"><a name="p145195620502"></a><a name="p145195620502"></a>int32_t (*disconnect)(NetDevice *netDev, uint16_t reasonCode);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p175191863503"><a name="p175191863503"></a><a name="p175191863503"></a>断开连接。</p>
</td>
</tr>
<tr id="row176421942125016"><td class="cellrowborder" rowspan="5" valign="top" width="15.079999999999998%" headers="mcps1.2.4.1.1 "><p id="p7937165012500"><a name="p7937165012500"></a><a name="p7937165012500"></a>hdf_netbuf.h</p>
</td>
<td class="cellrowborder" valign="top" width="60.33%" headers="mcps1.2.4.1.2 "><p id="p1964211423505"><a name="p1964211423505"></a><a name="p1964211423505"></a>static inline void NetBufQueueInit(struct NetBufQueue *q);</p>
</td>
<td class="cellrowborder" valign="top" width="24.59%" headers="mcps1.2.4.1.3 "><p id="p364254211507"><a name="p364254211507"></a><a name="p364254211507"></a>初始化net buffer队列。</p>
</td>
</tr>
<tr id="row664264225020"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p166421942115017"><a name="p166421942115017"></a><a name="p166421942115017"></a>struct NetBuf *NetBufAlloc(uint32_t size);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p3642164215501"><a name="p3642164215501"></a><a name="p3642164215501"></a>申请net buffer。</p>
</td>
</tr>
<tr id="row19642134215018"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p964310425501"><a name="p964310425501"></a><a name="p964310425501"></a>void NetBufFree(struct NetBuf *nb);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1464312427503"><a name="p1464312427503"></a><a name="p1464312427503"></a>释放net buffer。</p>
</td>
</tr>
<tr id="row7643194215013"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p20643164218508"><a name="p20643164218508"></a><a name="p20643164218508"></a>struct NetBuf *Pbuf2NetBuf(const struct NetDevice *netdev, struct pbuf *lwipBuf);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p186437429509"><a name="p186437429509"></a><a name="p186437429509"></a>lwip的pbuf转换为net buffer。</p>
</td>
</tr>
<tr id="row7657132317518"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p86576231557"><a name="p86576231557"></a><a name="p86576231557"></a>struct pbuf *NetBuf2Pbuf(const struct NetBuf *nb);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1965702312510"><a name="p1965702312510"></a><a name="p1965702312510"></a>net buffer转换为lwip的pbuf。</p>
</td>
</tr>
</tbody>
</table>

WLAN驱动模块提供了需驱动开发人员实现的能力接口，主要功能有：初始化/注销net device、打开/关闭net device、获取net device的状态等等。

表2 提供了部分接口说明如下：

**表 2**  需要开发人员实现的接口

<a name="table74613501475"></a>
<table><thead align="left"><tr id="row194625016476"><th class="cellrowborder" valign="top" width="20.75%" id="mcps1.2.4.1.1"><p id="p10468502479"><a name="p10468502479"></a><a name="p10468502479"></a>头文件</p>
</th>
<th class="cellrowborder" valign="top" width="52.75%" id="mcps1.2.4.1.2"><p id="p184615501477"><a name="p184615501477"></a><a name="p184615501477"></a>接口名称</p>
</th>
<th class="cellrowborder" valign="top" width="26.5%" id="mcps1.2.4.1.3"><p id="p1146135044719"><a name="p1146135044719"></a><a name="p1146135044719"></a>功能描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row04616509472"><td class="cellrowborder" rowspan="6" valign="top" width="20.75%" headers="mcps1.2.4.1.1 "><p id="p14615017477"><a name="p14615017477"></a><a name="p14615017477"></a>net_device.h</p>
</td>
<td class="cellrowborder" valign="top" width="52.75%" headers="mcps1.2.4.1.2 "><p id="p144943564611"><a name="p144943564611"></a><a name="p144943564611"></a>int32_t (*init)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" width="26.5%" headers="mcps1.2.4.1.3 "><p id="p18822442135411"><a name="p18822442135411"></a><a name="p18822442135411"></a>初始化net device。</p>
</td>
</tr>
<tr id="row1546250114713"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1490010315564"><a name="p1490010315564"></a><a name="p1490010315564"></a>struct NetDevStats *(*getStats)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p5900163115564"><a name="p5900163115564"></a><a name="p5900163115564"></a>获取net device的状态。</p>
</td>
</tr>
<tr id="row1646165010470"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p16909135319564"><a name="p16909135319564"></a><a name="p16909135319564"></a>int32_t (*setMacAddr)(struct NetDevice *netDev, void *addr);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p122001431115713"><a name="p122001431115713"></a><a name="p122001431115713"></a>设置mac地址。</p>
</td>
</tr>
<tr id="row12471250184711"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p154213655215"><a name="p154213655215"></a><a name="p154213655215"></a>void (*deInit)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14845675719"><a name="p14845675719"></a><a name="p14845675719"></a>注销net device。</p>
</td>
</tr>
<tr id="row13471050104719"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p16686131655218"><a name="p16686131655218"></a><a name="p16686131655218"></a>int32_t (*open)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p164825613576"><a name="p164825613576"></a><a name="p164825613576"></a>打开net device。</p>
</td>
</tr>
<tr id="row1747125054714"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2310615407"><a name="p2310615407"></a><a name="p2310615407"></a>int32_t (*stop)(struct NetDevice *netDev);</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1982212428542"><a name="p1982212428542"></a><a name="p1982212428542"></a>关闭net device。</p>
</td>
</tr>
</tbody>
</table>

