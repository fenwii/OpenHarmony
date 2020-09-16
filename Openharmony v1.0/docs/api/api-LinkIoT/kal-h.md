# kal.h<a name="ZH-CN_TOPIC_0000001054715051"></a>

## **Overview**<a name="section1820908794090253"></a>

**Related Modules:**

[KAL](KAL.md)

**Description:**

Defines the kernel adaptation layer \(KAL\), which provides compatible interfaces across different types of OpenHarmony devices.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1097549548090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1816054893090253"></a>
<table><thead align="left"><tr id="row404188315090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p321089680090253"><a name="p321089680090253"></a><a name="p321089680090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1562807747090253"><a name="p1562807747090253"></a><a name="p1562807747090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1894767546090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p39084838090253"><a name="p39084838090253"></a><a name="p39084838090253"></a><a href="ThreadInfo.md">ThreadInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1559806079090253"><a name="p1559806079090253"></a><a name="p1559806079090253"></a>Describes a thread.</p>
</td>
</tr>
<tr id="row863787615090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1927252681090253"><a name="p1927252681090253"></a><a name="p1927252681090253"></a><a href="MemInfo.md">MemInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1987865632090253"><a name="p1987865632090253"></a><a name="p1987865632090253"></a>Describes a memory pool.</p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1061997897090253"></a>
<table><thead align="left"><tr id="row788335080090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p899119998090253"><a name="p899119998090253"></a><a name="p899119998090253"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p266249916090253"><a name="p266249916090253"></a><a name="p266249916090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1617979724090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2023404214090253"><a name="p2023404214090253"></a><a name="p2023404214090253"></a><a href="KAL.md#ga5c36b53bd6e8cbdbcd79f702eda94fdc">KAL_TASK_NAME_LEN</a>   32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p212690775090253"><a name="p212690775090253"></a><a name="p212690775090253"></a>Indicates the maximum length of a thread name.</p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1245352044090253"></a>
<table><thead align="left"><tr id="row564814656090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1377751869090253"><a name="p1377751869090253"></a><a name="p1377751869090253"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p85963224090253"><a name="p85963224090253"></a><a name="p85963224090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1167137464090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087638916090253"><a name="p2087638916090253"></a><a name="p2087638916090253"></a><a href="KAL.md#gacde4b0c553c297f66311b87c4bbbb27d">KalTimerType</a> { <a href="KAL.md#ggacde4b0c553c297f66311b87c4bbbb27da688371f74e2f623cf61c26200389a45a">KAL_TIMER_ONCE</a> = 0, <a href="KAL.md#ggacde4b0c553c297f66311b87c4bbbb27da867ee8b661da91a61c698e408181f2bb">KAL_TIMER_PERIODIC</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p26310895090253"><a name="p26310895090253"></a><a name="p26310895090253"></a>Enumerates timer types.</p>
</td>
</tr>
<tr id="row667873585090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1410678834090253"><a name="p1410678834090253"></a><a name="p1410678834090253"></a><a href="KAL.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a> { <a href="KAL.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228">KAL_OK</a> = 0, <a href="KAL.md#gga595e811b5dcad5dc834be507d6839c36a399d6abae8b6ac5d890724065ee9c82e">KAL_ERR_PARA</a> = 1, <a href="KAL.md#gga595e811b5dcad5dc834be507d6839c36a3a7b733b01330946173b23b5b03e5522">KAL_ERR_INNER</a> = 2, <a href="KAL.md#gga595e811b5dcad5dc834be507d6839c36ae785550a7f8875e47da1e614f08299f0">KAL_ERR_TIMER_STATE</a> = 0x100 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1134221822090253"><a name="p1134221822090253"></a><a name="p1134221822090253"></a>Enumerates return values of the KAL function.</p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1865435390090253"></a>
<table><thead align="left"><tr id="row632748539090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p442643316090253"><a name="p442643316090253"></a><a name="p442643316090253"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1123700939090253"><a name="p1123700939090253"></a><a name="p1123700939090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row17209455090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p427413352090253"><a name="p427413352090253"></a><a name="p427413352090253"></a><a href="KAL.md#gaa1d5775963bc9a90985a130aa2dbe899">KalThreadGetInfo</a> (unsigned int threadId, <a href="ThreadInfo.md">ThreadInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1415645723090253"><a name="p1415645723090253"></a><a name="p1415645723090253"></a>unsigned int</p>
<p id="p850737189090253"><a name="p850737189090253"></a><a name="p850737189090253"></a>Obtains thread information.</p>
</td>
</tr>
<tr id="row1670841451090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1742200963090253"><a name="p1742200963090253"></a><a name="p1742200963090253"></a><a href="KAL.md#ga2eda397de96acde3491ffa2b29438e65">KalDelayUs</a> (unsigned int us)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p133130094090253"><a name="p133130094090253"></a><a name="p133130094090253"></a>void</p>
<p id="p1954589163090253"><a name="p1954589163090253"></a><a name="p1954589163090253"></a>Delays a thread.</p>
</td>
</tr>
<tr id="row1844109992090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881913301090253"><a name="p1881913301090253"></a><a name="p1881913301090253"></a><a href="KAL.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a> (KalTimerProc func, <a href="KAL.md#gacde4b0c553c297f66311b87c4bbbb27d">KalTimerType</a> type, void *arg, unsigned int ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861002106090253"><a name="p861002106090253"></a><a name="p861002106090253"></a>KalTimerId</p>
<p id="p1793783535090253"><a name="p1793783535090253"></a><a name="p1793783535090253"></a>Creates a timer.</p>
</td>
</tr>
<tr id="row1648465270090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778594456090253"><a name="p778594456090253"></a><a name="p778594456090253"></a><a href="KAL.md#gae94992c955be6145feea86b3cba55312">KalTimerStart</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p619461507090253"><a name="p619461507090253"></a><a name="p619461507090253"></a><a href="KAL.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p2015605451090253"><a name="p2015605451090253"></a><a name="p2015605451090253"></a>Starts a timer.</p>
</td>
</tr>
<tr id="row2086431181090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291826078090253"><a name="p291826078090253"></a><a name="p291826078090253"></a><a href="KAL.md#ga5210849c643e4668fec74bfc75693a66">KalTimerChange</a> (KalTimerId timerId, unsigned int ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327975643090253"><a name="p327975643090253"></a><a name="p327975643090253"></a><a href="KAL.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p843582347090253"><a name="p843582347090253"></a><a name="p843582347090253"></a>Changes the duration of a timer.</p>
</td>
</tr>
<tr id="row1695486021090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092618090090253"><a name="p2092618090090253"></a><a name="p2092618090090253"></a><a href="KAL.md#ga78940610f4a74baa2d299a8cc8508ad9">KalTimerStop</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p581413607090253"><a name="p581413607090253"></a><a name="p581413607090253"></a><a href="KAL.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p90786480090253"><a name="p90786480090253"></a><a name="p90786480090253"></a>Stops a timer.</p>
</td>
</tr>
<tr id="row390305589090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933688119090253"><a name="p1933688119090253"></a><a name="p1933688119090253"></a><a href="KAL.md#ga47739bc7600a8d2d9d7e34e4999de01c">KalTimerDelete</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088421267090253"><a name="p2088421267090253"></a><a name="p2088421267090253"></a><a href="KAL.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p980958829090253"><a name="p980958829090253"></a><a name="p980958829090253"></a>Deletes a timer.</p>
</td>
</tr>
<tr id="row1660146321090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680238357090253"><a name="p680238357090253"></a><a name="p680238357090253"></a><a href="KAL.md#ga599f352072c5277cba62a38415db05be">KalTimerIsRunning</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029238561090253"><a name="p2029238561090253"></a><a name="p2029238561090253"></a>unsigned int</p>
<p id="p1914481500090253"><a name="p1914481500090253"></a><a name="p1914481500090253"></a>Checks whether a timer is running.</p>
</td>
</tr>
<tr id="row1848707406090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716818417090253"><a name="p716818417090253"></a><a name="p716818417090253"></a><a href="KAL.md#ga1c585e669082ff0484213c59850ea363">KalTickToMs</a> (unsigned int ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1345244610090253"><a name="p1345244610090253"></a><a name="p1345244610090253"></a>unsigned int</p>
<p id="p1668147945090253"><a name="p1668147945090253"></a><a name="p1668147945090253"></a>Converts system ticks into milliseconds.</p>
</td>
</tr>
<tr id="row1981267446090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2104118499090253"><a name="p2104118499090253"></a><a name="p2104118499090253"></a><a href="KAL.md#ga1c0dc1fc474e4b46bd51e7d89415d7d0">KalMsToTick</a> (unsigned int millisec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488490032090253"><a name="p1488490032090253"></a><a name="p1488490032090253"></a>unsigned int</p>
<p id="p838294547090253"><a name="p838294547090253"></a><a name="p838294547090253"></a>Converts milliseconds into system ticks.</p>
</td>
</tr>
<tr id="row579375264090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p384239589090253"><a name="p384239589090253"></a><a name="p384239589090253"></a><a href="KAL.md#ga6285f6e40a345d9d785eb34367c25b12">KalGetMemInfo</a> (<a href="MemInfo.md">MemInfo</a> *pmemInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1782121023090253"><a name="p1782121023090253"></a><a name="p1782121023090253"></a><a href="KAL.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p190962442090253"><a name="p190962442090253"></a><a name="p190962442090253"></a>Obtains memory information.</p>
</td>
</tr>
</tbody>
</table>

