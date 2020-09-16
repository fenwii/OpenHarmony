# OHOS::SysInfo<a name="EN-US_TOPIC_0000001054479597"></a>

## **Overview**<a name="section2107799714093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Obtains the system information. Currently, the FPS information can be obtained. To enable the FPS feature, enable the  **ENABLE\_FPS\_SUPPORT**  macro. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section349930310093535"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1203424237093535"></a>
<table><thead align="left"><tr id="row380288312093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1996558095093535"><a name="p1996558095093535"></a><a name="p1996558095093535"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p253492962093535"><a name="p253492962093535"></a><a name="p253492962093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row845199684093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102758927093535"><a name="p2102758927093535"></a><a name="p2102758927093535"></a><a href="ohos-sysinfo-onfpschangedlistener.md">OnFPSChangedListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448771921093535"><a name="p448771921093535"></a><a name="p448771921093535"></a>Called when the FPS changes. </p>
</td>
</tr>
</tbody>
</table>

## Public Types<a name="pub-types"></a>

<a name="table1335547248093535"></a>
<table><thead align="left"><tr id="row139909591093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p941530515093535"><a name="p941530515093535"></a><a name="p941530515093535"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1188156453093535"><a name="p1188156453093535"></a><a name="p1188156453093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row66397851093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p948593759093535"><a name="p948593759093535"></a><a name="p948593759093535"></a><a href="graphic.md#ga75d850e3abff6c2f617b689a0cb9a3d1">FPSCalculateType</a> { <a href="graphic.md#gga75d850e3abff6c2f617b689a0cb9a3d1a26a841fb9a10881591dc79dae38e2d7f">FPS_CT_FIXED_TIME</a>, <a href="graphic.md#gga75d850e3abff6c2f617b689a0cb9a3d1a17fdb75ff7e9afb4165349a3d8300f3c">FPS_CT_AVERAGE_SAMPLING</a>, <a href="graphic.md#gga75d850e3abff6c2f617b689a0cb9a3d1afcc7226b2c9012f2993b7044a80cbed5">FPS_CT_PRECISE_SAMPLING</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034530996093535"><a name="p2034530996093535"></a><a name="p2034530996093535"></a>Enumerates the FPS capture types. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table280318415093535"></a>
<table><thead align="left"><tr id="row696166894093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p989370801093535"><a name="p989370801093535"></a><a name="p989370801093535"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1309430905093535"><a name="p1309430905093535"></a><a name="p1309430905093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row58323152093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620654596093535"><a name="p620654596093535"></a><a name="p620654596093535"></a><a href="graphic.md#gaa028189de9bf2968948578c8e09a9101">GetFPS</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p939111994093535"><a name="p939111994093535"></a><a name="p939111994093535"></a>static float </p>
<p id="p21690755093535"><a name="p21690755093535"></a><a name="p21690755093535"></a>Obtains the FPS data. </p>
</td>
</tr>
<tr id="row471157190093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1539597808093535"><a name="p1539597808093535"></a><a name="p1539597808093535"></a><a href="graphic.md#gac885a43e87f57ae57e0d8b6d213e9fa1">RegisterFPSChangedListener</a> (<a href="ohos-sysinfo-onfpschangedlistener.md">OnFPSChangedListener</a> *onFPSChangedListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510311445093535"><a name="p1510311445093535"></a><a name="p1510311445093535"></a>static void </p>
<p id="p729904004093535"><a name="p729904004093535"></a><a name="p729904004093535"></a>Registers the listener for notifying the FPS changes. </p>
</td>
</tr>
</tbody>
</table>

