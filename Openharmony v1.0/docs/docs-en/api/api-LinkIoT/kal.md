# KAL<a name="EN-US_TOPIC_0000001054948171"></a>

## **Overview**<a name="section9787238090250"></a>

Defines the kernel adaptation layer \(KAL\), which provides compatible interfaces across different types of OpenHarmony devices.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section279585292090250"></a>

## Files<a name="files"></a>

<a name="table769629198090250"></a>
<table><thead align="left"><tr id="row1279671087090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p168151700090250"><a name="p168151700090250"></a><a name="p168151700090250"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2010788671090250"><a name="p2010788671090250"></a><a name="p2010788671090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row946968834090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p899763654090250"><a name="p899763654090250"></a><a name="p899763654090250"></a><a href="kal-h.md">kal.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291437502090250"><a name="p291437502090250"></a><a name="p291437502090250"></a>Defines the kernel adaptation layer (KAL), which provides compatible interfaces across different types of OpenHarmony devices.</p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table865544571090250"></a>
<table><thead align="left"><tr id="row1539818328090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1619231771090250"><a name="p1619231771090250"></a><a name="p1619231771090250"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p18258118090250"><a name="p18258118090250"></a><a name="p18258118090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1588051321090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1568692327090250"><a name="p1568692327090250"></a><a name="p1568692327090250"></a><a href="threadinfo.md">ThreadInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1172898798090250"><a name="p1172898798090250"></a><a name="p1172898798090250"></a>Describes a thread.</p>
</td>
</tr>
<tr id="row1594931788090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638947350090250"><a name="p1638947350090250"></a><a name="p1638947350090250"></a><a href="meminfo.md">MemInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743878453090250"><a name="p743878453090250"></a><a name="p743878453090250"></a>Describes a memory pool.</p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1022359110090250"></a>
<table><thead align="left"><tr id="row2024385192090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1733199826090250"><a name="p1733199826090250"></a><a name="p1733199826090250"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1608692438090250"><a name="p1608692438090250"></a><a name="p1608692438090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row837841792090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p972708954090250"><a name="p972708954090250"></a><a name="p972708954090250"></a><em id="ga5c36b53bd6e8cbdbcd79f702eda94fdc"><a name="ga5c36b53bd6e8cbdbcd79f702eda94fdc"></a><a name="ga5c36b53bd6e8cbdbcd79f702eda94fdc"></a></em>KAL_TASK_NAME_LEN    32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p875345772090250"><a name="p875345772090250"></a><a name="p875345772090250"></a>Indicates the maximum length of a thread name.</p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1121915395090250"></a>
<table><thead align="left"><tr id="row876615543090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p39172838090250"><a name="p39172838090250"></a><a name="p39172838090250"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1647185032090250"><a name="p1647185032090250"></a><a name="p1647185032090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row51807949090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1155384547090250"><a name="p1155384547090250"></a><a name="p1155384547090250"></a><a href="kal.md#gacde4b0c553c297f66311b87c4bbbb27d">KalTimerType</a> { <a href="kal.md#ggacde4b0c553c297f66311b87c4bbbb27da688371f74e2f623cf61c26200389a45a">KAL_TIMER_ONCE</a> = 0, <a href="kal.md#ggacde4b0c553c297f66311b87c4bbbb27da867ee8b661da91a61c698e408181f2bb">KAL_TIMER_PERIODIC</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925187365090250"><a name="p1925187365090250"></a><a name="p1925187365090250"></a>Enumerates timer types.</p>
</td>
</tr>
<tr id="row62757079090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496220096090250"><a name="p496220096090250"></a><a name="p496220096090250"></a><a href="kal.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a> { <a href="kal.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228">KAL_OK</a> = 0, <a href="kal.md#gga595e811b5dcad5dc834be507d6839c36a399d6abae8b6ac5d890724065ee9c82e">KAL_ERR_PARA</a> = 1, <a href="kal.md#gga595e811b5dcad5dc834be507d6839c36a3a7b733b01330946173b23b5b03e5522">KAL_ERR_INNER</a> = 2, <a href="kal.md#gga595e811b5dcad5dc834be507d6839c36ae785550a7f8875e47da1e614f08299f0">KAL_ERR_TIMER_STATE</a> = 0x100 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1470168769090250"><a name="p1470168769090250"></a><a name="p1470168769090250"></a>Enumerates return values of the KAL function.</p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1652885666090250"></a>
<table><thead align="left"><tr id="row1485283083090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p160108447090250"><a name="p160108447090250"></a><a name="p160108447090250"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p661992638090250"><a name="p661992638090250"></a><a name="p661992638090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1341192174090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773017751090250"><a name="p773017751090250"></a><a name="p773017751090250"></a><a href="kal.md#gaa1d5775963bc9a90985a130aa2dbe899">KalThreadGetInfo</a> (unsigned int threadId, <a href="threadinfo.md">ThreadInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p143674785090250"><a name="p143674785090250"></a><a name="p143674785090250"></a>unsigned int</p>
<p id="p349672349090250"><a name="p349672349090250"></a><a name="p349672349090250"></a>Obtains thread information.</p>
</td>
</tr>
<tr id="row193746428090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091595061090250"><a name="p2091595061090250"></a><a name="p2091595061090250"></a><a href="kal.md#ga2eda397de96acde3491ffa2b29438e65">KalDelayUs</a> (unsigned int us)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673294868090250"><a name="p1673294868090250"></a><a name="p1673294868090250"></a>void</p>
<p id="p1083838878090250"><a name="p1083838878090250"></a><a name="p1083838878090250"></a>Delays a thread.</p>
</td>
</tr>
<tr id="row1582032518090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392107112090250"><a name="p1392107112090250"></a><a name="p1392107112090250"></a><a href="kal.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a> (KalTimerProc func, <a href="kal.md#gacde4b0c553c297f66311b87c4bbbb27d">KalTimerType</a> type, void *arg, unsigned int ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327550482090250"><a name="p1327550482090250"></a><a name="p1327550482090250"></a>KalTimerId</p>
<p id="p1323777792090250"><a name="p1323777792090250"></a><a name="p1323777792090250"></a>Creates a timer.</p>
</td>
</tr>
<tr id="row1051518793090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p387785760090250"><a name="p387785760090250"></a><a name="p387785760090250"></a><a href="kal.md#gae94992c955be6145feea86b3cba55312">KalTimerStart</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705703207090250"><a name="p705703207090250"></a><a name="p705703207090250"></a><a href="kal.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p1110952124090250"><a name="p1110952124090250"></a><a name="p1110952124090250"></a>Starts a timer.</p>
</td>
</tr>
<tr id="row1708085358090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571623932090250"><a name="p1571623932090250"></a><a name="p1571623932090250"></a><a href="kal.md#ga5210849c643e4668fec74bfc75693a66">KalTimerChange</a> (KalTimerId timerId, unsigned int ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405299670090250"><a name="p405299670090250"></a><a name="p405299670090250"></a><a href="kal.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p1724878930090250"><a name="p1724878930090250"></a><a name="p1724878930090250"></a>Changes the duration of a timer.</p>
</td>
</tr>
<tr id="row583760966090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p369584604090250"><a name="p369584604090250"></a><a name="p369584604090250"></a><a href="kal.md#ga78940610f4a74baa2d299a8cc8508ad9">KalTimerStop</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p747521935090250"><a name="p747521935090250"></a><a name="p747521935090250"></a><a href="kal.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p2004415637090250"><a name="p2004415637090250"></a><a name="p2004415637090250"></a>Stops a timer.</p>
</td>
</tr>
<tr id="row1980928763090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1283503038090250"><a name="p1283503038090250"></a><a name="p1283503038090250"></a><a href="kal.md#ga47739bc7600a8d2d9d7e34e4999de01c">KalTimerDelete</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1706798424090250"><a name="p1706798424090250"></a><a name="p1706798424090250"></a><a href="kal.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p1346894623090250"><a name="p1346894623090250"></a><a name="p1346894623090250"></a>Deletes a timer.</p>
</td>
</tr>
<tr id="row409991002090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836721559090250"><a name="p1836721559090250"></a><a name="p1836721559090250"></a><a href="kal.md#ga599f352072c5277cba62a38415db05be">KalTimerIsRunning</a> (KalTimerId timerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858486404090250"><a name="p858486404090250"></a><a name="p858486404090250"></a>unsigned int</p>
<p id="p2113773278090250"><a name="p2113773278090250"></a><a name="p2113773278090250"></a>Checks whether a timer is running.</p>
</td>
</tr>
<tr id="row2137173366090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1918730907090250"><a name="p1918730907090250"></a><a name="p1918730907090250"></a><a href="kal.md#ga1c585e669082ff0484213c59850ea363">KalTickToMs</a> (unsigned int ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459689953090250"><a name="p459689953090250"></a><a name="p459689953090250"></a>unsigned int</p>
<p id="p1285882106090250"><a name="p1285882106090250"></a><a name="p1285882106090250"></a>Converts system ticks into milliseconds.</p>
</td>
</tr>
<tr id="row468227279090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328827607090250"><a name="p328827607090250"></a><a name="p328827607090250"></a><a href="kal.md#ga1c0dc1fc474e4b46bd51e7d89415d7d0">KalMsToTick</a> (unsigned int millisec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p722263099090250"><a name="p722263099090250"></a><a name="p722263099090250"></a>unsigned int</p>
<p id="p472525132090250"><a name="p472525132090250"></a><a name="p472525132090250"></a>Converts milliseconds into system ticks.</p>
</td>
</tr>
<tr id="row716309176090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713488711090250"><a name="p1713488711090250"></a><a name="p1713488711090250"></a><a href="kal.md#ga6285f6e40a345d9d785eb34367c25b12">KalGetMemInfo</a> (<a href="meminfo.md">MemInfo</a> *pmemInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801026788090250"><a name="p801026788090250"></a><a name="p801026788090250"></a><a href="kal.md#ga595e811b5dcad5dc834be507d6839c36">KalErrCode</a></p>
<p id="p1090848409090250"><a name="p1090848409090250"></a><a name="p1090848409090250"></a>Obtains memory information.</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1918040133090250"></a>

## **Enumeration Type Documentation**<a name="section1088813391090250"></a>

## KalErrCode<a name="ga595e811b5dcad5dc834be507d6839c36"></a>

```
enum [KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36)
```

**Description:**

Enumerates return values of the KAL function.

<a name="table2033252657090250"></a>
<table><thead align="left"><tr id="row288199108090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1657223263090250"><a name="p1657223263090250"></a><a name="p1657223263090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2016480901090250"><a name="p2016480901090250"></a><a name="p2016480901090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row781539680090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1587560209090250p0"><a name="entry1587560209090250p0"></a><a name="entry1587560209090250p0"></a><strong id="gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228"><a name="gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228"></a><a name="gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228"></a></strong>KAL_OK</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497584006090250"><a name="p497584006090250"></a><a name="p497584006090250"></a>A successful execution</p>
<p id="p11440164110316"><a name="p11440164110316"></a><a name="p11440164110316"></a></p>
</td>
</tr>
<tr id="row1485168917090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry21551412090250p0"><a name="entry21551412090250p0"></a><a name="entry21551412090250p0"></a><strong id="gga595e811b5dcad5dc834be507d6839c36a399d6abae8b6ac5d890724065ee9c82e"><a name="gga595e811b5dcad5dc834be507d6839c36a399d6abae8b6ac5d890724065ee9c82e"></a><a name="gga595e811b5dcad5dc834be507d6839c36a399d6abae8b6ac5d890724065ee9c82e"></a></strong>KAL_ERR_PARA</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2070007331090250"><a name="p2070007331090250"></a><a name="p2070007331090250"></a>Incorrect parameter</p>
<p id="p1144010419313"><a name="p1144010419313"></a><a name="p1144010419313"></a></p>
</td>
</tr>
<tr id="row1406949664090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry641308078090250p0"><a name="entry641308078090250p0"></a><a name="entry641308078090250p0"></a><strong id="gga595e811b5dcad5dc834be507d6839c36a3a7b733b01330946173b23b5b03e5522"><a name="gga595e811b5dcad5dc834be507d6839c36a3a7b733b01330946173b23b5b03e5522"></a><a name="gga595e811b5dcad5dc834be507d6839c36a3a7b733b01330946173b23b5b03e5522"></a></strong>KAL_ERR_INNER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p539868235090250"><a name="p539868235090250"></a><a name="p539868235090250"></a>Internal execution error</p>
<p id="p1544015411732"><a name="p1544015411732"></a><a name="p1544015411732"></a></p>
</td>
</tr>
<tr id="row1850551987090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry592386261090250p0"><a name="entry592386261090250p0"></a><a name="entry592386261090250p0"></a><strong id="gga595e811b5dcad5dc834be507d6839c36ae785550a7f8875e47da1e614f08299f0"><a name="gga595e811b5dcad5dc834be507d6839c36ae785550a7f8875e47da1e614f08299f0"></a><a name="gga595e811b5dcad5dc834be507d6839c36ae785550a7f8875e47da1e614f08299f0"></a></strong>KAL_ERR_TIMER_STATE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1767284033090250"><a name="p1767284033090250"></a><a name="p1767284033090250"></a>Timer status error</p>
<p id="p6440241631"><a name="p6440241631"></a><a name="p6440241631"></a></p>
</td>
</tr>
</tbody>
</table>

## KalTimerType<a name="gacde4b0c553c297f66311b87c4bbbb27d"></a>

```
enum [KalTimerType](kal.md#gacde4b0c553c297f66311b87c4bbbb27d)
```

**Description:**

Enumerates timer types.

<a name="table490807404090250"></a>
<table><thead align="left"><tr id="row329519887090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p627432540090250"><a name="p627432540090250"></a><a name="p627432540090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1360280359090250"><a name="p1360280359090250"></a><a name="p1360280359090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row323851035090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1676693334090250p0"><a name="entry1676693334090250p0"></a><a name="entry1676693334090250p0"></a><strong id="ggacde4b0c553c297f66311b87c4bbbb27da688371f74e2f623cf61c26200389a45a"><a name="ggacde4b0c553c297f66311b87c4bbbb27da688371f74e2f623cf61c26200389a45a"></a><a name="ggacde4b0c553c297f66311b87c4bbbb27da688371f74e2f623cf61c26200389a45a"></a></strong>KAL_TIMER_ONCE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1919223126090250"><a name="p1919223126090250"></a><a name="p1919223126090250"></a>One-shot timer</p>
<p id="p1544854112318"><a name="p1544854112318"></a><a name="p1544854112318"></a></p>
</td>
</tr>
<tr id="row232535340090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1464454772090250p0"><a name="entry1464454772090250p0"></a><a name="entry1464454772090250p0"></a><strong id="ggacde4b0c553c297f66311b87c4bbbb27da867ee8b661da91a61c698e408181f2bb"><a name="ggacde4b0c553c297f66311b87c4bbbb27da867ee8b661da91a61c698e408181f2bb"></a><a name="ggacde4b0c553c297f66311b87c4bbbb27da867ee8b661da91a61c698e408181f2bb"></a></strong>KAL_TIMER_PERIODIC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168641856090250"><a name="p1168641856090250"></a><a name="p1168641856090250"></a>Repetitive timer</p>
<p id="p6448841430"><a name="p6448841430"></a><a name="p6448841430"></a></p>
</td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1870600102090250"></a>

## KalDelayUs\(\)<a name="ga2eda397de96acde3491ffa2b29438e65"></a>

```
void KalDelayUs (unsigned int us)
```

**Description:**

Delays a thread.

The delay unit is microsecond. The actual delay precision can reach only the tick level.

**Parameters:**

<a name="table1072222572090250"></a>
<table><thead align="left"><tr id="row357148926090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p956450764090250"><a name="p956450764090250"></a><a name="p956450764090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1134305722090250"><a name="p1134305722090250"></a><a name="p1134305722090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row45825837090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry537415473090250p0"><a name="entry537415473090250p0"></a><a name="entry537415473090250p0"></a>us</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry104061947090250p0"><a name="entry104061947090250p0"></a><a name="entry104061947090250p0"></a>Indicates the number of microseconds to delay. The actual delay precision is one tick.</p>
</td>
</tr>
</tbody>
</table>

## KalGetMemInfo\(\)<a name="ga6285f6e40a345d9d785eb34367c25b12"></a>

```
[KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36) KalGetMemInfo ([MemInfo](meminfo.md) * pmemInfo)
```

**Description:**

Obtains memory information.

**Parameters:**

<a name="table1015244821090250"></a>
<table><thead align="left"><tr id="row991660390090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p299526827090250"><a name="p299526827090250"></a><a name="p299526827090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1383934611090250"><a name="p1383934611090250"></a><a name="p1383934611090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1222934779090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1937117894090250p0"><a name="entry1937117894090250p0"></a><a name="entry1937117894090250p0"></a>pmemInfo</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry315786093090250p0"><a name="entry315786093090250p0"></a><a name="entry315786093090250p0"></a>Indicates the pointer to the memory information.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns an enumerated value defined by  [KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36), where  [KAL\_OK](kal.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228)  indicates a success.

## KalMsToTick\(\)<a name="ga1c0dc1fc474e4b46bd51e7d89415d7d0"></a>

```
unsigned int KalMsToTick (unsigned int millisec)
```

**Description:**

Converts milliseconds into system ticks.

**Parameters:**

<a name="table1674882159090250"></a>
<table><thead align="left"><tr id="row1808476861090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p195586487090250"><a name="p195586487090250"></a><a name="p195586487090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2029168273090250"><a name="p2029168273090250"></a><a name="p2029168273090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1612627690090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry229984854090250p0"><a name="entry229984854090250p0"></a><a name="entry229984854090250p0"></a>millisec</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry62392545090250p0"><a name="entry62392545090250p0"></a><a name="entry62392545090250p0"></a>Indicates the milliseconds to convert.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the system ticks generated.

## KalThreadGetInfo\(\)<a name="gaa1d5775963bc9a90985a130aa2dbe899"></a>

```
unsigned int KalThreadGetInfo (unsigned int threadId, [ThreadInfo](threadinfo.md) * info )
```

**Description:**

Obtains thread information.

**Parameters:**

<a name="table1265205112090250"></a>
<table><thead align="left"><tr id="row157772410090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p517328145090250"><a name="p517328145090250"></a><a name="p517328145090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p320788349090250"><a name="p320788349090250"></a><a name="p320788349090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row635552821090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1075927755090250p0"><a name="entry1075927755090250p0"></a><a name="entry1075927755090250p0"></a>threadId</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry559539319090250p0"><a name="entry559539319090250p0"></a><a name="entry559539319090250p0"></a>Indicates the thread ID.</p>
</td>
</tr>
<tr id="row1074772122090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry750154741090250p0"><a name="entry750154741090250p0"></a><a name="entry750154741090250p0"></a>info</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1525186157090250p0"><a name="entry1525186157090250p0"></a><a name="entry1525186157090250p0"></a>Indicates the pointer to the buffer for storing the obtained thread information.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the thread information is obtained; returns a negative value otherwise.

## KalTickToMs\(\)<a name="ga1c585e669082ff0484213c59850ea363"></a>

```
unsigned int KalTickToMs (unsigned int ticks)
```

**Description:**

Converts system ticks into milliseconds.

**Parameters:**

<a name="table1501067531090250"></a>
<table><thead align="left"><tr id="row1394740911090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1405376294090250"><a name="p1405376294090250"></a><a name="p1405376294090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1399565358090250"><a name="p1399565358090250"></a><a name="p1399565358090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1086265717090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1312544656090250p0"><a name="entry1312544656090250p0"></a><a name="entry1312544656090250p0"></a>ticks</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry387467238090250p0"><a name="entry387467238090250p0"></a><a name="entry387467238090250p0"></a>Indicates the number of ticks to convert.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the milliseconds generated.

## KalTimerChange\(\)<a name="ga5210849c643e4668fec74bfc75693a66"></a>

```
[KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36) KalTimerChange (KalTimerId timerId, unsigned int ticks )
```

**Description:**

Changes the duration of a timer.

The timer duration can be changed only before the timer is started.

**Parameters:**

<a name="table118094358090250"></a>
<table><thead align="left"><tr id="row837457968090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p306638110090250"><a name="p306638110090250"></a><a name="p306638110090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1010028081090250"><a name="p1010028081090250"></a><a name="p1010028081090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row221792356090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry794316212090250p0"><a name="entry794316212090250p0"></a><a name="entry794316212090250p0"></a>timerId</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry632643054090250p0"><a name="entry632643054090250p0"></a><a name="entry632643054090250p0"></a>Indicates the ID of the timer whose duration is to change, which is the value returned by <a href="kal.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a>.</p>
</td>
</tr>
<tr id="row1115890167090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry166423821090250p0"><a name="entry166423821090250p0"></a><a name="entry166423821090250p0"></a>ticks</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry763994554090250p0"><a name="entry763994554090250p0"></a><a name="entry763994554090250p0"></a>Indicates the new duration of the timer.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns an enumerated value defined by  [KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36), where  [KAL\_OK](kal.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228)  indicates a success.

## KalTimerCreate\(\)<a name="ga8b4739a501ebc18746f9be5f077a78d7"></a>

```
KalTimerId KalTimerCreate (KalTimerProc func, [KalTimerType](kal.md#gacde4b0c553c297f66311b87c4bbbb27d) type, void * arg, unsigned int ticks )
```

**Description:**

Creates a timer.

**Parameters:**

<a name="table77425435090250"></a>
<table><thead align="left"><tr id="row495685141090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1356842829090250"><a name="p1356842829090250"></a><a name="p1356842829090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1517717949090250"><a name="p1517717949090250"></a><a name="p1517717949090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1666700858090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry226656396090250p0"><a name="entry226656396090250p0"></a><a name="entry226656396090250p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry580079398090250p0"><a name="entry580079398090250p0"></a><a name="entry580079398090250p0"></a>Indicates the entry to timer callback. The callback is triggered when the timer expires.</p>
</td>
</tr>
<tr id="row1723323089090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1477381166090250p0"><a name="entry1477381166090250p0"></a><a name="entry1477381166090250p0"></a>type</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1519720414090250p0"><a name="entry1519720414090250p0"></a><a name="entry1519720414090250p0"></a>Indicates the timer type.</p>
</td>
</tr>
<tr id="row572683528090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry786468104090250p0"><a name="entry786468104090250p0"></a><a name="entry786468104090250p0"></a>arg</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1024218162090250p0"><a name="entry1024218162090250p0"></a><a name="entry1024218162090250p0"></a>Indicates the pointer to the argument used in timer callback.</p>
</td>
</tr>
<tr id="row638953725090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry807210750090250p0"><a name="entry807210750090250p0"></a><a name="entry807210750090250p0"></a>ticks</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1544463044090250p0"><a name="entry1544463044090250p0"></a><a name="entry1544463044090250p0"></a>Indicates the duration of the timer to create.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the timer ID; returns  **NULL**  in the case of an error.

## KalTimerDelete\(\)<a name="ga47739bc7600a8d2d9d7e34e4999de01c"></a>

```
[KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36) KalTimerDelete (KalTimerId timerId)
```

**Description:**

Deletes a timer.

**Parameters:**

<a name="table1448518894090250"></a>
<table><thead align="left"><tr id="row241534207090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1478794303090250"><a name="p1478794303090250"></a><a name="p1478794303090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1618646052090250"><a name="p1618646052090250"></a><a name="p1618646052090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1064898631090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry194406456090250p0"><a name="entry194406456090250p0"></a><a name="entry194406456090250p0"></a>timerId</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1655546368090250p0"><a name="entry1655546368090250p0"></a><a name="entry1655546368090250p0"></a>Indicates the ID of the timer to delete, which is the value returned by <a href="kal.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a>.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns an enumerated value defined by  [KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36), where  [KAL\_OK](kal.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228)  indicates a success.

## KalTimerIsRunning\(\)<a name="ga599f352072c5277cba62a38415db05be"></a>

```
unsigned int KalTimerIsRunning (KalTimerId timerId)
```

**Description:**

Checks whether a timer is running.

**Parameters:**

<a name="table1091018981090250"></a>
<table><thead align="left"><tr id="row1285460878090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1575744244090250"><a name="p1575744244090250"></a><a name="p1575744244090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1006271401090250"><a name="p1006271401090250"></a><a name="p1006271401090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1453707987090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1047186589090250p0"><a name="entry1047186589090250p0"></a><a name="entry1047186589090250p0"></a>timerId</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1421223117090250p0"><a name="entry1421223117090250p0"></a><a name="entry1421223117090250p0"></a>Indicates the ID of the timer to check, which is the value returned by <a href="kal.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a>.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **1**  if the timer is running; returns  **0**  if the timer is not running or the input parameter is incorrect.

## KalTimerStart\(\)<a name="gae94992c955be6145feea86b3cba55312"></a>

```
[KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36) KalTimerStart (KalTimerId timerId)
```

**Description:**

Starts a timer.

**Parameters:**

<a name="table1090689722090250"></a>
<table><thead align="left"><tr id="row15726364090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p313569381090250"><a name="p313569381090250"></a><a name="p313569381090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p792177544090250"><a name="p792177544090250"></a><a name="p792177544090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row91856712090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry385879940090250p0"><a name="entry385879940090250p0"></a><a name="entry385879940090250p0"></a>timerId</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry377521522090250p0"><a name="entry377521522090250p0"></a><a name="entry377521522090250p0"></a>Indicates the ID of the timer to start, which is the value returned by <a href="kal.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a>.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns an enumerated value defined by  [KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36), where  [KAL\_OK](kal.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228)  indicates a success.

## KalTimerStop\(\)<a name="ga78940610f4a74baa2d299a8cc8508ad9"></a>

```
[KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36) KalTimerStop (KalTimerId timerId)
```

**Description:**

Stops a timer.

**Parameters:**

<a name="table2024397108090250"></a>
<table><thead align="left"><tr id="row1103151354090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1293557509090250"><a name="p1293557509090250"></a><a name="p1293557509090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2106193107090250"><a name="p2106193107090250"></a><a name="p2106193107090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row560498489090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry334876843090250p0"><a name="entry334876843090250p0"></a><a name="entry334876843090250p0"></a>timerId</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1806602586090250p0"><a name="entry1806602586090250p0"></a><a name="entry1806602586090250p0"></a>Indicates the ID of the timer to stop, which is the value returned by <a href="kal.md#ga8b4739a501ebc18746f9be5f077a78d7">KalTimerCreate</a>.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns an enumerated value defined by  [KalErrCode](kal.md#ga595e811b5dcad5dc834be507d6839c36), where  [KAL\_OK](kal.md#gga595e811b5dcad5dc834be507d6839c36a249642877a22187565c646fcb4c43228)  indicates a success.

## **Variable Documentation**<a name="section1676204574090250"></a>

## bottomOfStack<a name="ga9782002d7ff296063c57521353df67fe"></a>

```
unsigned int ThreadInfo::bottomOfStack
```

**Description:**

Thread stack bottom

## currUsed<a name="ga0a57d18c5ea4b55301b070c14bcfec60"></a>

```
unsigned int ThreadInfo::currUsed
```

**Description:**

Current stack space usage

## eventMask<a name="gae92f3f338fe0daeee86bf24205d029f4"></a>

```
unsigned int ThreadInfo::eventMask
```

**Description:**

Thread event mask

## eventStru<a name="ga1424ad853216d3a422ad7ce7626225cd"></a>

```
unsigned int ThreadInfo::eventStru[3]
```

**Description:**

Thread event

## free<a name="gab75adae81df2237c560b49f5faa91b1a"></a>

```
unsigned int MemInfo::free
```

**Description:**

Available space of the memory pool, in bytes

## freeLmp<a name="ga21a8267ffdef5300c9158f7f23c19d68"></a>

```
unsigned int MemInfo::freeLmp
```

**Description:**

Available space of the small memory pool, in bytes

## freeNodeNum<a name="gab6d8b14505fd8c1d8eac6067c4f88119"></a>

```
unsigned int MemInfo::freeNodeNum
```

**Description:**

Number of available nodes in the memory pool

## id<a name="gac764c6a73d29bd0730350f81f4594a9f"></a>

```
unsigned int ThreadInfo::id
```

**Description:**

Thread ID

## mallocFailCount<a name="gae0d28e6e11877301350a97630d06c682"></a>

```
unsigned int MemInfo::mallocFailCount
```

**Description:**

Number of memory allocation failures

## maxFreeNodeSize<a name="ga217b3f6710fe68d1d66fd5cd2650a7be"></a>

```
unsigned int MemInfo::maxFreeNodeSize
```

**Description:**

Size of the largest available node in the memory pool, in bytes

## mepc<a name="ga443d3e54ba44e2528c482c206997de94"></a>

```
unsigned int ThreadInfo::mepc
```

**Description:**

Current thread MEPC

## mstatus<a name="gae7d1ec2921ba3fd0d2d4009f76f73f3f"></a>

```
unsigned int ThreadInfo::mstatus
```

**Description:**

Current thread status

## name<a name="ga13a2aab39a8c95bf10c135207b15f851"></a>

```
char ThreadInfo::name[[KAL_TASK_NAME_LEN](kal.md#ga5c36b53bd6e8cbdbcd79f702eda94fdc)]
```

**Description:**

Thread name

## overflowFlag<a name="gac28ecdda9bd5ba304bfcb4437c729e9f"></a>

```
unsigned int ThreadInfo::overflowFlag
```

**Description:**

Thread stack overflow flag

## peakUsed<a name="ga2416d243f06063f759aea86e793417dc"></a>

```
unsigned int ThreadInfo::peakUsed
```

**Description:**

Peak stack space usage

## peekSize<a name="gada0d8e9b692e9000fe0db02db6567d4a"></a>

```
unsigned int MemInfo::peekSize
```

**Description:**

Peak memory usage of the memory pool

## priority<a name="ga5eb18799436289247d58027508924bf9"></a>

```
unsigned short ThreadInfo::priority
```

**Description:**

Thread priority

## ra<a name="gae011035df8be3da14189c65a0028a137"></a>

```
unsigned int ThreadInfo::ra
```

**Description:**

Current thread RA

## sp<a name="gae2812d96da0c6a7580f5161663af418a"></a>

```
unsigned int ThreadInfo::sp
```

**Description:**

Thread stack pointer

## stackSize<a name="ga3948edc6f57a3afbdaf45347d29a85c8"></a>

```
unsigned int ThreadInfo::stackSize
```

**Description:**

Thread stack size

## status<a name="ga0ab6ed527e0c49b254e7e6764fd99c09"></a>

```
unsigned short ThreadInfo::status
```

**Description:**

Thread status

## taskMutex<a name="ga2001b2a08dea8277c36d7e8f6cfb09f5"></a>

```
void* ThreadInfo::taskMutex
```

**Description:**

Thread mutex

## taskSem<a name="gabce57039bcba8c3c5941e11fc13908e1"></a>

```
void* ThreadInfo::taskSem
```

**Description:**

Thread semaphore

## topOfStack<a name="ga3a22f2522b3d5cdd6063f2f57d4206ea"></a>

```
unsigned int ThreadInfo::topOfStack
```

**Description:**

Thread stack top

## total<a name="gae36bc4b5086df8b29ba9c93239bb4aa3"></a>

```
unsigned int MemInfo::total
```

**Description:**

Total space of the memory pool, in bytes

## totalLmp<a name="ga86cf478f001bad014a3566b9db7e3a43"></a>

```
unsigned int MemInfo::totalLmp
```

**Description:**

Total space of the small memory pool, in bytes

## tp<a name="ga782cce4041f34c75829b862b32e19ca1"></a>

```
unsigned int ThreadInfo::tp
```

**Description:**

Current thread TP

## used<a name="gacf6bd852bfcb83e11793eba2d59979cf"></a>

```
unsigned int MemInfo::used
```

**Description:**

Used space of the memory pool, in bytes

## usedLmp<a name="gacd3c292e8445268150881cb18c2f8f6d"></a>

```
unsigned int MemInfo::usedLmp
```

**Description:**

Used space of the small memory pool, in bytes

## usedNodeNum<a name="gab25a44d9fdb8150ca4e9544a7061556c"></a>

```
unsigned int MemInfo::usedNodeNum
```

**Description:**

Number of used nodes in the memory pool

