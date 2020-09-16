# OHOS::AbilityEventHandler<a name="ZH-CN_TOPIC_0000001055198142"></a>

## **Overview**<a name="section90272495093532"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)

**Description:**

Declares functions for performing operations during inter-thread communication, including running and quitting the event loop of the current thread and posting tasks to an asynchronous thread. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2120892625093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1951068639093532"></a>
<table><thead align="left"><tr id="row1399590274093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1817970662093532"><a name="p1817970662093532"></a><a name="p1817970662093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p735360986093532"><a name="p735360986093532"></a><a name="p735360986093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row211418208093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056062494093532"><a name="p2056062494093532"></a><a name="p2056062494093532"></a><a href="AbilityKit.md#gac534b1e3746d252944475b3ed9cb5bc7">Run</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p511900645093532"><a name="p511900645093532"></a><a name="p511900645093532"></a> void&nbsp;</p>
<p id="p1692153107093532"><a name="p1692153107093532"></a><a name="p1692153107093532"></a>Starts running the event loop of the current thread. </p>
</td>
</tr>
<tr id="row1495298790093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p705772753093532"><a name="p705772753093532"></a><a name="p705772753093532"></a><a href="AbilityKit.md#gad4d0911a8bccd5aca32464bad867cb13">PostTask</a> (const Task &amp;task)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1040255573093532"><a name="p1040255573093532"></a><a name="p1040255573093532"></a>void&nbsp;</p>
<p id="p1730118572093532"><a name="p1730118572093532"></a><a name="p1730118572093532"></a>Posts a task to an asynchronous thread. </p>
</td>
</tr>
<tr id="row567847854093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1132178717093532"><a name="p1132178717093532"></a><a name="p1132178717093532"></a><a href="AbilityKit.md#ga075bfbf9e5c9c2178f3183efd664dbaf">PostQuit</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193057756093532"><a name="p1193057756093532"></a><a name="p1193057756093532"></a> void&nbsp;</p>
<p id="p519478969093532"><a name="p519478969093532"></a><a name="p519478969093532"></a>Quits the event loop of the current thread. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table1374208507093532"></a>
<table><thead align="left"><tr id="row1513292655093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2065334934093532"><a name="p2065334934093532"></a><a name="p2065334934093532"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1309680386093532"><a name="p1309680386093532"></a><a name="p1309680386093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1902520199093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472868636093532"><a name="p1472868636093532"></a><a name="p1472868636093532"></a><a href="AbilityKit.md#gad26d144aaecd3185be6902e6d7399b9e">GetCurrentHandler</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1490409888093532"><a name="p1490409888093532"></a><a name="p1490409888093532"></a>static <a href="OHOS-AbilityEventHandler.md">AbilityEventHandler</a> *&nbsp;</p>
<p id="p499924834093532"><a name="p499924834093532"></a><a name="p499924834093532"></a>Obtains the event handler of the current thread. </p>
</td>
</tr>
</tbody>
</table>

