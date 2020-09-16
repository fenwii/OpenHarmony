# OHOS::AnimatorManager<a name="EN-US_TOPIC_0000001054799617"></a>

## **Overview**<a name="section346202971093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents the animator manager. 

This is a singleton class used to manage  **[Animator](ohos-animator.md)**  instances.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section368357259093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table225855339093533"></a>
<table><thead align="left"><tr id="row770858527093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1724912350093533"><a name="p1724912350093533"></a><a name="p1724912350093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p211534954093533"><a name="p211534954093533"></a><a name="p211534954093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row954887438093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535420209093533"><a name="p1535420209093533"></a><a name="p1535420209093533"></a><a href="graphic.md#gadfc9e9cf812f172fb1b6ca7efb7ba099">Init</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367563359093533"><a name="p367563359093533"></a><a name="p367563359093533"></a> void </p>
<p id="p17979688093533"><a name="p17979688093533"></a><a name="p17979688093533"></a>Initializes this task. </p>
</td>
</tr>
<tr id="row2106032140093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985755771093533"><a name="p1985755771093533"></a><a name="p1985755771093533"></a><a href="graphic.md#ga8b60ed045dc2a3370498a3e6922d5400">Add</a> (<a href="ohos-animator.md">Animator</a> *animator)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p202529236093533"><a name="p202529236093533"></a><a name="p202529236093533"></a>void </p>
<p id="p1947021255093533"><a name="p1947021255093533"></a><a name="p1947021255093533"></a>Adds the <strong id="b142800092093533"><a name="b142800092093533"></a><a name="b142800092093533"></a><a href="ohos-animator.md">Animator</a></strong> instance to the <strong id="b648962386093533"><a name="b648962386093533"></a><a name="b648962386093533"></a><a href="ohos-animatormanager.md">AnimatorManager</a></strong> linked list for management, so that the <strong id="b243149516093533"><a name="b243149516093533"></a><a name="b243149516093533"></a>Run</strong> function of the <strong id="b562479584093533"><a name="b562479584093533"></a><a name="b562479584093533"></a><a href="ohos-animator.md">Animator</a></strong> class is called once for each frame. </p>
</td>
</tr>
<tr id="row1072683168093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p770927516093533"><a name="p770927516093533"></a><a name="p770927516093533"></a><a href="graphic.md#ga493d53a9e4a47b79d30c0d37f96a69da">Remove</a> (const <a href="ohos-animator.md">Animator</a> *animator)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314260256093533"><a name="p1314260256093533"></a><a name="p1314260256093533"></a>void </p>
<p id="p1821058985093533"><a name="p1821058985093533"></a><a name="p1821058985093533"></a>Removes the <strong id="b1197758963093533"><a name="b1197758963093533"></a><a name="b1197758963093533"></a><a href="ohos-animator.md">Animator</a></strong> instance from the <strong id="b1092469560093533"><a name="b1092469560093533"></a><a name="b1092469560093533"></a><a href="ohos-animatormanager.md">AnimatorManager</a></strong> linked list. </p>
</td>
</tr>
<tr id="row2094524023093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1751383365093533"><a name="p1751383365093533"></a><a name="p1751383365093533"></a><a href="graphic.md#ga8a7c3d733fc2112171a2e075dd425a5c">Callback</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1123800467093533"><a name="p1123800467093533"></a><a name="p1123800467093533"></a> void </p>
<p id="p1551878621093533"><a name="p1551878621093533"></a><a name="p1551878621093533"></a>Called when this task is executed. </p>
</td>
</tr>
<tr id="row1812527650093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039665737093533"><a name="p1039665737093533"></a><a name="p1039665737093533"></a><a href="graphic.md#gad94964a9139150b967ad640ea2076312">Task</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p170938497093533"><a name="p170938497093533"></a><a name="p170938497093533"></a>  </p>
<p id="p2124397183093533"><a name="p2124397183093533"></a><a name="p2124397183093533"></a>A constructor used to create a <strong id="b867401028093533"><a name="b867401028093533"></a><a name="b867401028093533"></a><a href="ohos-task.md">Task</a></strong> instance. </p>
</td>
</tr>
<tr id="row51177651093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015795844093533"><a name="p2015795844093533"></a><a name="p2015795844093533"></a><a href="graphic.md#gaa7c50eb360b6a4478b5332b8bf565940">Task</a> (uint32_t period)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588570952093533"><a name="p1588570952093533"></a><a name="p1588570952093533"></a> </p>
<p id="p991039763093533"><a name="p991039763093533"></a><a name="p991039763093533"></a>A constructor used to create a <strong id="b2031159055093533"><a name="b2031159055093533"></a><a name="b2031159055093533"></a><a href="ohos-task.md">Task</a></strong> instance with the specified running period. </p>
</td>
</tr>
<tr id="row942347399093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463804929093533"><a name="p463804929093533"></a><a name="p463804929093533"></a><a href="graphic.md#ga293d4e1533ea98cdebbbffe1afed38ef">~Task</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443200735093533"><a name="p443200735093533"></a><a name="p443200735093533"></a> virtual </p>
<p id="p1902405927093533"><a name="p1902405927093533"></a><a name="p1902405927093533"></a>A destructor used to delete the <strong id="b1501558375093533"><a name="b1501558375093533"></a><a name="b1501558375093533"></a><a href="ohos-task.md">Task</a></strong> instance. </p>
</td>
</tr>
<tr id="row449703037093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p862144329093533"><a name="p862144329093533"></a><a name="p862144329093533"></a><a href="graphic.md#gac6e9fe7bde72bf506558a6f0d0287a92">SetPeriod</a> (uint32_t period)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p126358557093533"><a name="p126358557093533"></a><a name="p126358557093533"></a>void </p>
<p id="p990924806093533"><a name="p990924806093533"></a><a name="p990924806093533"></a>Sets the running period for this task. </p>
</td>
</tr>
<tr id="row420857871093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1863720069093533"><a name="p1863720069093533"></a><a name="p1863720069093533"></a><a href="graphic.md#gabdbfe69d5f5da3cc5bbb1749d281af62">SetLastRun</a> (uint32_t lastRun)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p532516848093533"><a name="p532516848093533"></a><a name="p532516848093533"></a>void </p>
<p id="p136101983093533"><a name="p136101983093533"></a><a name="p136101983093533"></a>Sets the end time for this task. </p>
</td>
</tr>
<tr id="row1121626971093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1107668480093533"><a name="p1107668480093533"></a><a name="p1107668480093533"></a><a href="graphic.md#gabd53b86c63b41172af155b8a7f86b84c">GetPeriod</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075357122093533"><a name="p2075357122093533"></a><a name="p2075357122093533"></a>uint32_t </p>
<p id="p699998033093533"><a name="p699998033093533"></a><a name="p699998033093533"></a>Obtains the running period of this task. </p>
</td>
</tr>
<tr id="row561375979093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892648586093533"><a name="p1892648586093533"></a><a name="p1892648586093533"></a><a href="graphic.md#ga2d4c9fbb026686623ff4d6e0b19d4960">GetLastRun</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121740476093533"><a name="p1121740476093533"></a><a name="p1121740476093533"></a>uint32_t </p>
<p id="p282326573093533"><a name="p282326573093533"></a><a name="p282326573093533"></a>Obtains the end time of this task. </p>
</td>
</tr>
<tr id="row1955133182093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1812211053093533"><a name="p1812211053093533"></a><a name="p1812211053093533"></a><a href="graphic.md#ga96ed6680b2b9ad667e51d60554013020">TaskExecute</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p659117163093533"><a name="p659117163093533"></a><a name="p659117163093533"></a> void </p>
<p id="p1115722560093533"><a name="p1115722560093533"></a><a name="p1115722560093533"></a>Executes this task. </p>
</td>
</tr>
<tr id="row254601850093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1607328664093533"><a name="p1607328664093533"></a><a name="p1607328664093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p975490804093533"><a name="p975490804093533"></a><a name="p975490804093533"></a>void * </p>
<p id="p1869234078093533"><a name="p1869234078093533"></a><a name="p1869234078093533"></a>Overrides the <strong id="b1592884485093533"><a name="b1592884485093533"></a><a name="b1592884485093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row2039819565093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2011716326093533"><a name="p2011716326093533"></a><a name="p2011716326093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p12672142093533"><a name="p12672142093533"></a><a name="p12672142093533"></a>void </p>
<p id="p48565194093533"><a name="p48565194093533"></a><a name="p48565194093533"></a>Overrides the <strong id="b181488528093533"><a name="b181488528093533"></a><a name="b181488528093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table958497988093533"></a>
<table><thead align="left"><tr id="row1598899871093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1012947615093533"><a name="p1012947615093533"></a><a name="p1012947615093533"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1620998358093533"><a name="p1620998358093533"></a><a name="p1620998358093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row224524857093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1674860804093533"><a name="p1674860804093533"></a><a name="p1674860804093533"></a><a href="graphic.md#ga3ed818079b3501922f422b150f891d13">GetInstance</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p47091306093533"><a name="p47091306093533"></a><a name="p47091306093533"></a>static <a href="ohos-animatormanager.md">AnimatorManager</a> * </p>
<p id="p164464888093533"><a name="p164464888093533"></a><a name="p164464888093533"></a>Obtains the <strong id="b269360519093533"><a name="b269360519093533"></a><a name="b269360519093533"></a><a href="ohos-animatormanager.md">AnimatorManager</a></strong> instance. </p>
</td>
</tr>
</tbody>
</table>

