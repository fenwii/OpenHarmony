# hwi<a name="EN-US_TOPIC_0000001051690311"></a>

## Command Function<a name="section445335110416"></a>

This command is used to query information about the current interrupts.

## Syntax<a name="section1795712553416"></a>

hwi

## Parameter Description<a name="section92544592410"></a>

None

## Usage<a name="section104151141252"></a>

-   Enter  **hwi**  to display the current interrupt ID, count of interrupts, and registered interrupt name.
-   If  **LOSCFG\_CPUP\_INCLUDE\_IRQ**  is enabled, the processing time \(cycles\), CPU usage, and interrupt type of each interrupt are displayed.

## Example<a name="section11545171957"></a>

Enter  **hwi**.

## Output<a name="section075617368542"></a>

1.  Interrupt information \(with  **LOSCFG\_CPUP\_INCLUDE\_IRQ**  disabled\)

    ![](figures/en-us_image_0000001053826366.png)

2.  Interrupt information \(with  **LOSCFG\_CPUP\_INCLUDE\_IRQ**  enabled\)

    ![](figures/en-us_image_0000001052810304.png)

    **Table  1**  Output description

    <a name="table809mcpsimp"></a>
    <table><thead align="left"><tr id="row814mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p816mcpsimp"><a name="p816mcpsimp"></a><a name="p816mcpsimp"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p818mcpsimp"><a name="p818mcpsimp"></a><a name="p818mcpsimp"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row20360171311398"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p172391401402"><a name="p172391401402"></a><a name="p172391401402"></a>InterruptNo</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p42381940174013"><a name="p42381940174013"></a><a name="p42381940174013"></a>Indicates the interrupt ID.</p>
    </td>
    </tr>
    <tr id="row262535153913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1823824014402"><a name="p1823824014402"></a><a name="p1823824014402"></a>Count</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p14237040144018"><a name="p14237040144018"></a><a name="p14237040144018"></a>Indicates the count of interrupts.</p>
    </td>
    </tr>
    <tr id="row9683953153916"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p6236124084018"><a name="p6236124084018"></a><a name="p6236124084018"></a>Name</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p18235164014401"><a name="p18235164014401"></a><a name="p18235164014401"></a>Indicates the registered interrupt name.</p>
    </td>
    </tr>
    <tr id="row85721136402"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1123434017409"><a name="p1123434017409"></a><a name="p1123434017409"></a>CYCLECOST</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2023424094014"><a name="p2023424094014"></a><a name="p2023424094014"></a>Indicates the interrupt processing time (cycles).</p>
    </td>
    </tr>
    <tr id="row19180126151415"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p6233040164020"><a name="p6233040164020"></a><a name="p6233040164020"></a>CPUUSE</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p5232840104015"><a name="p5232840104015"></a><a name="p5232840104015"></a>Indicates the CPU usage.</p>
    </td>
    </tr>
    <tr id="row511517331702"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p14231040164014"><a name="p14231040164014"></a><a name="p14231040164014"></a>CPUUSE10s</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1323011409405"><a name="p1323011409405"></a><a name="p1323011409405"></a>Indicates CPU usage within the last 10 seconds.</p>
    </td>
    </tr>
    <tr id="row1868124415413"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p9681144414114"><a name="p9681144414114"></a><a name="p9681144414114"></a>CPUUSE1s</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p76814443417"><a name="p76814443417"></a><a name="p76814443417"></a>Indicates CPU usage within the last 1 second.</p>
    </td>
    </tr>
    <tr id="row7681164454112"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1968124412411"><a name="p1968124412411"></a><a name="p1968124412411"></a>mode</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p268134415419"><a name="p268134415419"></a><a name="p268134415419"></a>Indicates the interrupt mode.</p>
    <a name="ul682912412419"></a><a name="ul682912412419"></a><ul id="ul682912412419"><li><strong id="b1211610663719"><a name="b1211610663719"></a><a name="b1211610663719"></a>normal</strong>: non-shared interrupt.</li><li><strong id="b65931332173920"><a name="b65931332173920"></a><a name="b65931332173920"></a>shared</strong>: shared interrupt.</li></ul>
    </td>
    </tr>
    </tbody>
    </table>


