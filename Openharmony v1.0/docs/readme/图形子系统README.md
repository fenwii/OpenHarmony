# 图形子系统<a name="ZH-CN_TOPIC_0000001051979319"></a>

## 简介<a name="section5243712115918"></a>

图形子系统主要包括UI组件、布局、动画、字体、输入事件、窗口管理、渲染绘制等模块，构建基于轻量OS的应用框架，满足硬件资源较小的物联网设备的OpenHarmony系统应用开发。

各模块介绍：

-   Components: 应用组件，包括UIView、UIViewGoup、UIButton、UILabel、UILabelButton、UIList、UISlider等。
-   Layout：布局控件，包括Flexlayout、GridLayout、ListLayout等。
-   Animator：动画模块，开发者可以自定义动画。
-   Font：字体处理模块。
-   Event：事件模块，包括click、press、drag、long press等基础事件。
-   Task：任务管理模块。
-   Input：输入事件处理模块。
-   Display：显示处理模块。
-   Render：渲染绘制模块。
-   Draw2d：2d绘制模块，包括直线、矩形、圆、弧、图片、文字等绘制。包括软件绘制和硬件加速能力对接。
-   Surface：共享内存。
-   Window：窗口管理模块，包括窗口创建、显示隐藏、合成等处理。
-   Adapter：适配层，对接底层适配层接口。

## 目录<a name="section99241319175914"></a>

**表 1**  图形子系统源代码目录结构

<a name="table2977131081412"></a>
<table><thead align="left"><tr id="row7977610131417"><th class="cellrowborder" valign="top" width="17.7%" id="mcps1.2.3.1.1"><p id="p18792459121314"><a name="p18792459121314"></a><a name="p18792459121314"></a>名称</p>
</th>
<th class="cellrowborder" valign="top" width="82.3%" id="mcps1.2.3.1.2"><p id="p77921459191317"><a name="p77921459191317"></a><a name="p77921459191317"></a>描述</p>
</th>
</tr>
</thead>
<tbody><tr id="row17977171010144"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p2793159171311"><a name="p2793159171311"></a><a name="p2793159171311"></a>config</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p879375920132"><a name="p879375920132"></a><a name="p879375920132"></a>配置文件目录。</p>
</td>
</tr>
<tr id="row6978161091412"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p37931659101311"><a name="p37931659101311"></a><a name="p37931659101311"></a>frameworks/surface</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p6793059171318"><a name="p6793059171318"></a><a name="p6793059171318"></a>Surface共享内存。</p>
</td>
</tr>
<tr id="row6978201031415"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p117935599130"><a name="p117935599130"></a><a name="p117935599130"></a>frameworks/ui</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p0793185971316"><a name="p0793185971316"></a><a name="p0793185971316"></a>UI模块，包括UI控件、动画、字体等功能。</p>
</td>
</tr>
<tr id="row1897841071415"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p16793185961315"><a name="p16793185961315"></a><a name="p16793185961315"></a>hals</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p14793959161317"><a name="p14793959161317"></a><a name="p14793959161317"></a>HAL适配层逻辑。</p>
</td>
</tr>
<tr id="row1420633124613"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p16207133194613"><a name="p16207133194613"></a><a name="p16207133194613"></a>interfaces/ui</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p182076317465"><a name="p182076317465"></a><a name="p182076317465"></a>UI模块对外接口头文件。</p>
</td>
</tr>
<tr id="row1679114715461"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p1079120477466"><a name="p1079120477466"></a><a name="p1079120477466"></a>interfaces/utils</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p1279144754611"><a name="p1279144754611"></a><a name="p1279144754611"></a>图形子系统公共库头文件。</p>
</td>
</tr>
<tr id="row1534591617478"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p43456161472"><a name="p43456161472"></a><a name="p43456161472"></a>services/ims</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p23451616124717"><a name="p23451616124717"></a><a name="p23451616124717"></a>输入管理服务，处理点击、按键等输入事件处理、分发。</p>
</td>
</tr>
<tr id="row1044522874716"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p644516283476"><a name="p644516283476"></a><a name="p644516283476"></a>services/wms</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p194451528144716"><a name="p194451528144716"></a><a name="p194451528144716"></a>窗口管理服务，处理窗口的创建、管理和合成。</p>
</td>
</tr>
<tr id="row48471930154713"><td class="cellrowborder" valign="top" width="17.7%" headers="mcps1.2.3.1.1 "><p id="p4847830134713"><a name="p4847830134713"></a><a name="p4847830134713"></a>utils</p>
</td>
<td class="cellrowborder" valign="top" width="82.3%" headers="mcps1.2.3.1.2 "><p id="p8847193074715"><a name="p8847193074715"></a><a name="p8847193074715"></a>图形子系统公共库。</p>
</td>
</tr>
</tbody>
</table>

## 约束<a name="section37625514114"></a>

-   语言版本
    -   C++11版本或以上

-   框架针对不同的芯片平台和底层OS能力，规格有所区别
    -   Cortex-M RAM/ROM：
        -   RAM：建议大于100K
        -   ROM:  \> 300K

    -   Cortex-A RAM/ROM:
        -   RAM：建议大于1M
        -   ROM：\> 1M



## 新增一个UI控件<a name="section266451716115"></a>

所有的控件都继承UIView，有通用的属性和样式。UI控件分为两大类：普通控件和容器控件。普通控件不能添加子节点，容器控件作为父容器可以添加子节点。

新增控件头文件放到interfaces/ui/components，cpp文件放到frameworks/ui/src/components目录。组件Override OnDraw绘制接口，在这个接口里实现本控件的绘制流程。在frameworks/ui/BUILD.gn添加对应的新增文件，构建时会编译到libui.so。

## 涉及仓<a name="section78781240113620"></a>

graphic\_lite

