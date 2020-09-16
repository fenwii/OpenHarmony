# OHOS::Task<a name="EN-US_TOPIC_0000001054718145"></a>

## **Overview**<a name="section64450249093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents the  **[Task](ohos-task.md)**  class of the graphics module. This class provides functions for setting the running period and time of a task. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section266659078093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1496393334093533"></a>
<table><thead align="left"><tr id="row328726370093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p860373005093533"><a name="p860373005093533"></a><a name="p860373005093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p900460030093533"><a name="p900460030093533"></a><a name="p900460030093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1861160261093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1423502182093533"><a name="p1423502182093533"></a><a name="p1423502182093533"></a><a href="graphic.md#gad94964a9139150b967ad640ea2076312">Task</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179419579093533"><a name="p1179419579093533"></a><a name="p1179419579093533"></a>  </p>
<p id="p1277980744093533"><a name="p1277980744093533"></a><a name="p1277980744093533"></a>A constructor used to create a <strong id="b283772139093533"><a name="b283772139093533"></a><a name="b283772139093533"></a><a href="ohos-task.md">Task</a></strong> instance. </p>
</td>
</tr>
<tr id="row311591764093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p826543941093533"><a name="p826543941093533"></a><a name="p826543941093533"></a><a href="graphic.md#gaa7c50eb360b6a4478b5332b8bf565940">Task</a> (uint32_t period)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201193459093533"><a name="p1201193459093533"></a><a name="p1201193459093533"></a> </p>
<p id="p1145245928093533"><a name="p1145245928093533"></a><a name="p1145245928093533"></a>A constructor used to create a <strong id="b1703053939093533"><a name="b1703053939093533"></a><a name="b1703053939093533"></a><a href="ohos-task.md">Task</a></strong> instance with the specified running period. </p>
</td>
</tr>
<tr id="row915410997093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p786957563093533"><a name="p786957563093533"></a><a name="p786957563093533"></a><a href="graphic.md#ga293d4e1533ea98cdebbbffe1afed38ef">~Task</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1328726864093533"><a name="p1328726864093533"></a><a name="p1328726864093533"></a> virtual </p>
<p id="p2124379341093533"><a name="p2124379341093533"></a><a name="p2124379341093533"></a>A destructor used to delete the <strong id="b835308172093533"><a name="b835308172093533"></a><a name="b835308172093533"></a><a href="ohos-task.md">Task</a></strong> instance. </p>
</td>
</tr>
<tr id="row62147019093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1729503680093533"><a name="p1729503680093533"></a><a name="p1729503680093533"></a><a href="graphic.md#gac6e9fe7bde72bf506558a6f0d0287a92">SetPeriod</a> (uint32_t period)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670255241093533"><a name="p1670255241093533"></a><a name="p1670255241093533"></a>void </p>
<p id="p26183870093533"><a name="p26183870093533"></a><a name="p26183870093533"></a>Sets the running period for this task. </p>
</td>
</tr>
<tr id="row605017871093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p227950913093533"><a name="p227950913093533"></a><a name="p227950913093533"></a><a href="graphic.md#gabdbfe69d5f5da3cc5bbb1749d281af62">SetLastRun</a> (uint32_t lastRun)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331098297093533"><a name="p1331098297093533"></a><a name="p1331098297093533"></a>void </p>
<p id="p622409863093533"><a name="p622409863093533"></a><a name="p622409863093533"></a>Sets the end time for this task. </p>
</td>
</tr>
<tr id="row2135482609093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645165799093533"><a name="p645165799093533"></a><a name="p645165799093533"></a><a href="graphic.md#gabd53b86c63b41172af155b8a7f86b84c">GetPeriod</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073868552093533"><a name="p2073868552093533"></a><a name="p2073868552093533"></a>uint32_t </p>
<p id="p73656471093533"><a name="p73656471093533"></a><a name="p73656471093533"></a>Obtains the running period of this task. </p>
</td>
</tr>
<tr id="row1284695304093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p447858590093533"><a name="p447858590093533"></a><a name="p447858590093533"></a><a href="graphic.md#ga2d4c9fbb026686623ff4d6e0b19d4960">GetLastRun</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093645160093533"><a name="p1093645160093533"></a><a name="p1093645160093533"></a>uint32_t </p>
<p id="p1050107678093533"><a name="p1050107678093533"></a><a name="p1050107678093533"></a>Obtains the end time of this task. </p>
</td>
</tr>
<tr id="row521354853093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2103775246093533"><a name="p2103775246093533"></a><a name="p2103775246093533"></a><a href="graphic.md#ga96ed6680b2b9ad667e51d60554013020">TaskExecute</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p252765035093533"><a name="p252765035093533"></a><a name="p252765035093533"></a> void </p>
<p id="p1793209728093533"><a name="p1793209728093533"></a><a name="p1793209728093533"></a>Executes this task. </p>
</td>
</tr>
<tr id="row837139094093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p644494540093533"><a name="p644494540093533"></a><a name="p644494540093533"></a><a href="graphic.md#gad1ddf68898304dad1f912f750ace8281">Callback</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p991254688093533"><a name="p991254688093533"></a><a name="p991254688093533"></a> virtual void </p>
<p id="p1833080758093533"><a name="p1833080758093533"></a><a name="p1833080758093533"></a>Called when this task is executed. </p>
</td>
</tr>
<tr id="row747382018093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p798918838093533"><a name="p798918838093533"></a><a name="p798918838093533"></a><a href="graphic.md#gab9968727a3d5e8b6270f5efd0eb1cff6">Init</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264316266093533"><a name="p264316266093533"></a><a name="p264316266093533"></a> virtual void </p>
<p id="p1120507311093533"><a name="p1120507311093533"></a><a name="p1120507311093533"></a>Initializes this task. </p>
</td>
</tr>
<tr id="row645385314093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p941144008093533"><a name="p941144008093533"></a><a name="p941144008093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403737936093533"><a name="p1403737936093533"></a><a name="p1403737936093533"></a>void * </p>
<p id="p1228822117093533"><a name="p1228822117093533"></a><a name="p1228822117093533"></a>Overrides the <strong id="b1357377853093533"><a name="b1357377853093533"></a><a name="b1357377853093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row176189584093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p405677011093533"><a name="p405677011093533"></a><a name="p405677011093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491567895093533"><a name="p491567895093533"></a><a name="p491567895093533"></a>void </p>
<p id="p742404380093533"><a name="p742404380093533"></a><a name="p742404380093533"></a>Overrides the <strong id="b1608174315093533"><a name="b1608174315093533"></a><a name="b1608174315093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

