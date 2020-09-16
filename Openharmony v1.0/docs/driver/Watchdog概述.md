# Watchdog概述<a name="ZH-CN_TOPIC_0000001052935969"></a>

## 简介<a name="section3579126111816"></a>

看门狗（Watchdog），又叫看门狗计时器（Watchdog timer），是一种硬件的计时设备，当系统的主程序发生某些错误时，导致未及时清除看门狗计时器的计时值，这时看门狗计时器就会对系统发出复位信号，使系统从悬停状态恢复到正常运作状态。

## 接口说明<a name="section17429111981812"></a>

**表 1**  Watchdog API接口功能介绍

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="26.619999999999997%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>功能分类</p>
</th>
<th class="cellrowborder" valign="top" width="32.800000000000004%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>接口名</p>
</th>
<th class="cellrowborder" valign="top" width="40.58%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row837081981712"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p681292481718"><a name="p681292481718"></a><a name="p681292481718"></a>打开/关闭看门狗</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p183701419141710"><a name="p183701419141710"></a><a name="p183701419141710"></a>WatchdogOpen</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p17370161911710"><a name="p17370161911710"></a><a name="p17370161911710"></a>打开看门狗设备</p>
</td>
</tr>
<tr id="row5610415171719"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p661171510173"><a name="p661171510173"></a><a name="p661171510173"></a>WatchdogClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p11611715161713"><a name="p11611715161713"></a><a name="p11611715161713"></a>关闭看门狗设备</p>
</td>
</tr>
<tr id="row337105133315"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p07631557153319"><a name="p07631557153319"></a><a name="p07631557153319"></a>启动/停止看门狗</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p163765113337"><a name="p163765113337"></a><a name="p163765113337"></a>WatchdogStart</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p18376517332"><a name="p18376517332"></a><a name="p18376517332"></a>启动看门狗</p>
</td>
</tr>
<tr id="row18399184610337"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1740010461335"><a name="p1740010461335"></a><a name="p1740010461335"></a>WatchdogStop</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p19400194633318"><a name="p19400194633318"></a><a name="p19400194633318"></a>停止看门狗</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>设置/获取超时时间</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p8296182221219"><a name="p8296182221219"></a><a name="p8296182221219"></a>WatchdogSetTimeout</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p16297172213125"><a name="p16297172213125"></a><a name="p16297172213125"></a>设置看门狗超时时间</p>
</td>
</tr>
<tr id="row11585016539"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1095722493616"><a name="p1095722493616"></a><a name="p1095722493616"></a>WatchdogGetTimeout</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p15297162215122"><a name="p15297162215122"></a><a name="p15297162215122"></a>获取看门狗超时时间</p>
</td>
</tr>
<tr id="row105701653185811"><td class="cellrowborder" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p2571145325819"><a name="p2571145325819"></a><a name="p2571145325819"></a>获取看门狗状态</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p175711953195814"><a name="p175711953195814"></a><a name="p175711953195814"></a>WatchdogGetStatus</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p331961319210"><a name="p331961319210"></a><a name="p331961319210"></a>获取看门狗状态</p>
</td>
</tr>
<tr id="row1028182217215"><td class="cellrowborder" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p182818227214"><a name="p182818227214"></a><a name="p182818227214"></a>清除看门狗定时器</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p17281223219"><a name="p17281223219"></a><a name="p17281223219"></a>WatchdogFeed</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p62815221125"><a name="p62815221125"></a><a name="p62815221125"></a>清除看门狗定时器(喂狗)</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>本文涉及的所有接口，仅限内核态使用，不支持在用户态使用。

