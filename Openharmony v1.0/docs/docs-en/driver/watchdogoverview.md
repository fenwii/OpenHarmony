# Watchdog Overview<a name="EN-US_TOPIC_0000001052935969"></a>

## Introduction<a name="section3579126111816"></a>

A watchdog, also called a watchdog timer, is a hardware timing device. If an error occurs in the main program of the system and fails to reset the watchdog timer, the watchdog timer sends a reset signal to restore the system to a normal state.

## Available APIs<a name="section17429111981812"></a>

**Table  1**  Watchdog APIs

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="26.619999999999997%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>Capability</p>
</th>
<th class="cellrowborder" valign="top" width="32.800000000000004%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="40.58%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row837081981712"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p681292481718"><a name="p681292481718"></a><a name="p681292481718"></a>Open/Close</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p183701419141710"><a name="p183701419141710"></a><a name="p183701419141710"></a>WatchdogOpen</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p17370161911710"><a name="p17370161911710"></a><a name="p17370161911710"></a>Opens a watchdog.</p>
</td>
</tr>
<tr id="row5610415171719"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p661171510173"><a name="p661171510173"></a><a name="p661171510173"></a>WatchdogClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p11611715161713"><a name="p11611715161713"></a><a name="p11611715161713"></a>Closes a watchdog.</p>
</td>
</tr>
<tr id="row337105133315"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p07631557153319"><a name="p07631557153319"></a><a name="p07631557153319"></a>Start/Stop</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p163765113337"><a name="p163765113337"></a><a name="p163765113337"></a>WatchdogStart</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p18376517332"><a name="p18376517332"></a><a name="p18376517332"></a>Starts a watchdog.</p>
</td>
</tr>
<tr id="row18399184610337"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1740010461335"><a name="p1740010461335"></a><a name="p1740010461335"></a>WatchdogStop</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p19400194633318"><a name="p19400194633318"></a><a name="p19400194633318"></a>Stops a watchdog.</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>Timeout duration</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p8296182221219"><a name="p8296182221219"></a><a name="p8296182221219"></a>WatchdogSetTimeout</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p16297172213125"><a name="p16297172213125"></a><a name="p16297172213125"></a>Sets the watchdog timeout duration.</p>
</td>
</tr>
<tr id="row11585016539"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1095722493616"><a name="p1095722493616"></a><a name="p1095722493616"></a>WatchdogGetTimeout</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p15297162215122"><a name="p15297162215122"></a><a name="p15297162215122"></a>Obtains the watchdog timeout duration.</p>
</td>
</tr>
<tr id="row105701653185811"><td class="cellrowborder" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p2571145325819"><a name="p2571145325819"></a><a name="p2571145325819"></a>Status</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p175711953195814"><a name="p175711953195814"></a><a name="p175711953195814"></a>WatchdogGetStatus</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p331961319210"><a name="p331961319210"></a><a name="p331961319210"></a>Obtains the watchdog status.</p>
</td>
</tr>
<tr id="row1028182217215"><td class="cellrowborder" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p182818227214"><a name="p182818227214"></a><a name="p182818227214"></a>Feeding</p>
</td>
<td class="cellrowborder" valign="top" width="32.800000000000004%" headers="mcps1.2.4.1.2 "><p id="p17281223219"><a name="p17281223219"></a><a name="p17281223219"></a>WatchdogFeed</p>
</td>
<td class="cellrowborder" valign="top" width="40.58%" headers="mcps1.2.4.1.3 "><p id="p62815221125"><a name="p62815221125"></a><a name="p62815221125"></a>Feeds a watchdog, or resets a watchdog timer.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel mode.

