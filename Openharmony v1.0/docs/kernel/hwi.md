# hwi<a name="ZH-CN_TOPIC_0000001051690311"></a>

## 命令功能<a name="section445335110416"></a>

hwi命令查询当前中断信息

## 命令格式<a name="section1795712553416"></a>

hwi

## 参数说明<a name="section92544592410"></a>

无。

## 使用指南<a name="section104151141252"></a>

-   输入hwi即显示当前中断号、中断次数及注册中断名称。
-   若开关LOSCFG\_CPUP\_INCLUDE\_IRQ打开，则还会显示各个中断的处理时间（cycles）、CPU占用率以及中断类型。

## 使用实例<a name="section11545171957"></a>

举例：输入hwi

## 输出说明<a name="section075617368542"></a>

1.  显示中断信息（LOSCFG\_CPUP\_INCLUDE\_IRQ关闭）

    ![](figures/zh-cn_image_0000001053826366.png)

2.  显示中断信息（LOSCFG\_CPUP\_INCLUDE\_IRQ打开）

    ![](figures/zh-cn_image_0000001052810304.png)

    **表 1**  输出说明

    <a name="table809mcpsimp"></a>
    <table><thead align="left"><tr id="row814mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p816mcpsimp"><a name="p816mcpsimp"></a><a name="p816mcpsimp"></a>输出</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p818mcpsimp"><a name="p818mcpsimp"></a><a name="p818mcpsimp"></a>说明</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row20360171311398"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p172391401402"><a name="p172391401402"></a><a name="p172391401402"></a>InterruptNo</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p42381940174013"><a name="p42381940174013"></a><a name="p42381940174013"></a>中断号。</p>
    </td>
    </tr>
    <tr id="row262535153913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1823824014402"><a name="p1823824014402"></a><a name="p1823824014402"></a>Count</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p14237040144018"><a name="p14237040144018"></a><a name="p14237040144018"></a>中断次数。</p>
    </td>
    </tr>
    <tr id="row9683953153916"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p6236124084018"><a name="p6236124084018"></a><a name="p6236124084018"></a>Name</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p18235164014401"><a name="p18235164014401"></a><a name="p18235164014401"></a>注册中断名称。</p>
    </td>
    </tr>
    <tr id="row85721136402"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1123434017409"><a name="p1123434017409"></a><a name="p1123434017409"></a>CYCLECOST</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2023424094014"><a name="p2023424094014"></a><a name="p2023424094014"></a>中断的处理时间（cycles）。</p>
    </td>
    </tr>
    <tr id="row19180126151415"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p6233040164020"><a name="p6233040164020"></a><a name="p6233040164020"></a>CPUUSE</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p5232840104015"><a name="p5232840104015"></a><a name="p5232840104015"></a>CPU占用率。</p>
    </td>
    </tr>
    <tr id="row511517331702"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p14231040164014"><a name="p14231040164014"></a><a name="p14231040164014"></a>CPUUSE10s</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1323011409405"><a name="p1323011409405"></a><a name="p1323011409405"></a>最近10s CPU占用率。</p>
    </td>
    </tr>
    <tr id="row1868124415413"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p9681144414114"><a name="p9681144414114"></a><a name="p9681144414114"></a>CPUUSE1s</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p76814443417"><a name="p76814443417"></a><a name="p76814443417"></a>最近1s CPU占用率。</p>
    </td>
    </tr>
    <tr id="row7681164454112"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1968124412411"><a name="p1968124412411"></a><a name="p1968124412411"></a>mode</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p268134415419"><a name="p268134415419"></a><a name="p268134415419"></a>中断类型:</p>
    <a name="ul682912412419"></a><a name="ul682912412419"></a><ul id="ul682912412419"><li>normal:  非共享中断。</li><li>shared:  共享中断。</li></ul>
    </td>
    </tr>
    </tbody>
    </table>


