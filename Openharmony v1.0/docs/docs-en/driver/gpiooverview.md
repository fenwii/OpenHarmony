# GPIO Overview<a name="EN-US_TOPIC_0000001051777586"></a>

## Introduction<a name="section15318165672215"></a>

GPIO is short for general-purpose input/output. Generally, a GPIO controller manages all GPIO pins by group. Each group of GPIO pins is associated with one or more registers. The GPIO pins are operated by reading data from and writing data to the registers.

The GPIO APIs define a set of standard functions for performing operations on GPIO pins, including:

-   Setting the pin direction, which can be input or output \(High impedance is not supported currently.\)

-   Reading and writing level values, which can be low or high
-   Setting an interrupt service routine \(ISR\) function and interrupt trigger mode for a pin
-   Enabling or disabling a pin interrupt

## Available APIs<a name="section18977142162418"></a>

**Table  1**  APIs available for the GPIO driver

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="19.74%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>Capability</p>
</th>
<th class="cellrowborder" valign="top" width="32.36%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="47.9%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="19.74%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>GPIO read/write</p>
</td>
<td class="cellrowborder" valign="top" width="32.36%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>GpioRead</p>
</td>
<td class="cellrowborder" valign="top" width="47.9%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>Reads the level value of a GPIO pin.</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>GpioWrite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p67306152404"><a name="p67306152404"></a><a name="p67306152404"></a>Writes the level value of a GPIO pin.</p>
</td>
</tr>
<tr id="row17493124814141"><td class="cellrowborder" rowspan="2" valign="top" width="19.74%" headers="mcps1.2.4.1.1 "><p id="p321814526178"><a name="p321814526178"></a><a name="p321814526178"></a>GPIO settings</p>
</td>
<td class="cellrowborder" valign="top" width="32.36%" headers="mcps1.2.4.1.2 "><p id="p16390153015156"><a name="p16390153015156"></a><a name="p16390153015156"></a>GpioSetDir</p>
</td>
<td class="cellrowborder" valign="top" width="47.9%" headers="mcps1.2.4.1.3 "><p id="p1873761519408"><a name="p1873761519408"></a><a name="p1873761519408"></a>Sets the direction for a GPIO pin.</p>
</td>
</tr>
<tr id="row10681146181417"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p15390153014151"><a name="p15390153014151"></a><a name="p15390153014151"></a>GpioGetDir</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p974061515406"><a name="p974061515406"></a><a name="p974061515406"></a>Obtains the direction for a GPIO pin.</p>
</td>
</tr>
<tr id="row10288191441518"><td class="cellrowborder" rowspan="4" valign="top" width="19.74%" headers="mcps1.2.4.1.1 "><p id="p13927416134716"><a name="p13927416134716"></a><a name="p13927416134716"></a>GPIO interrupt settings</p>
<p id="p738165912472"><a name="p738165912472"></a><a name="p738165912472"></a></p>
<p id="p151691515483"><a name="p151691515483"></a><a name="p151691515483"></a></p>
<p id="p6742119204820"><a name="p6742119204820"></a><a name="p6742119204820"></a></p>
</td>
<td class="cellrowborder" valign="top" width="32.36%" headers="mcps1.2.4.1.2 "><p id="p17390113013158"><a name="p17390113013158"></a><a name="p17390113013158"></a>GpioSetIrq</p>
</td>
<td class="cellrowborder" valign="top" width="47.9%" headers="mcps1.2.4.1.3 "><p id="p10314104354416"><a name="p10314104354416"></a><a name="p10314104354416"></a>Sets the ISR function for a GPIO pin.</p>
</td>
</tr>
<tr id="row163795912473"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p523618345323"><a name="p523618345323"></a><a name="p523618345323"></a>GpioUnSetIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1138195912478"><a name="p1138195912478"></a><a name="p1138195912478"></a>Cancels the setting of the ISR function for a GPIO pin.</p>
</td>
</tr>
<tr id="row155161515124816"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p657344273218"><a name="p657344273218"></a><a name="p657344273218"></a>GpioEnableIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p115163154488"><a name="p115163154488"></a><a name="p115163154488"></a>Enables a GPIO interrupt.</p>
</td>
</tr>
<tr id="row1742119174820"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1865114616324"><a name="p1865114616324"></a><a name="p1865114616324"></a>GpioDisableIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p97421219174820"><a name="p97421219174820"></a><a name="p97421219174820"></a>Disables a GPIO interrupt.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel mode.

