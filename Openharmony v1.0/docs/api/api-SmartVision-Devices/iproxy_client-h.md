# iproxy\_client.h<a name="ZH-CN_TOPIC_0000001055518060"></a>

## **Overview**<a name="section945175763093525"></a>

**Related Modules:**

[Registry](Registry.md)

**Description:**

Provides the client proxy class. 

When you need to call system capabilities of other processes, obtain the class from Samgr. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1771582204093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1189857256093525"></a>
<table><thead align="left"><tr id="row869660288093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1746347505093525"><a name="p1746347505093525"></a><a name="p1746347505093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p409416514093525"><a name="p409416514093525"></a><a name="p409416514093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row960292497093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620376044093525"><a name="p620376044093525"></a><a name="p620376044093525"></a><a href="IClientProxy.md">IClientProxy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1008634076093525"><a name="p1008634076093525"></a><a name="p1008634076093525"></a>Defines the client proxy object. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1401714948093525"></a>
<table><thead align="left"><tr id="row1729310996093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p137817022093525"><a name="p137817022093525"></a><a name="p137817022093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1629461448093525"><a name="p1629461448093525"></a><a name="p1629461448093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row145346739093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344309714093525"><a name="p344309714093525"></a><a name="p344309714093525"></a><a href="Registry.md#ga86734e6a03eb089309e87ec628002034">INHERIT_CLIENT_IPROXY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1214417876093525"><a name="p1214417876093525"></a><a name="p1214417876093525"></a>Indicates the inherited macro of the client proxy. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table688085312093525"></a>
<table><thead align="left"><tr id="row709015421093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1764537935093525"><a name="p1764537935093525"></a><a name="p1764537935093525"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1327403089093525"><a name="p1327403089093525"></a><a name="p1327403089093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1238681677093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460915970093525"><a name="p1460915970093525"></a><a name="p1460915970093525"></a><a href="Registry.md#ga362a17c1bda1aace88d42dcbc88bdfac">INotify</a>) (IOwner owner, int code, IpcIo *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1107281460093525"><a name="p1107281460093525"></a><a name="p1107281460093525"></a>typedef int(*&nbsp;</p>
<p id="p987410381093525"><a name="p987410381093525"></a><a name="p987410381093525"></a>Called when a client request is responded. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1163481891093525"></a>
<table><thead align="left"><tr id="row587039938093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1665296112093525"><a name="p1665296112093525"></a><a name="p1665296112093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1542950662093525"><a name="p1542950662093525"></a><a name="p1542950662093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1335221835093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328162326093525"><a name="p328162326093525"></a><a name="p328162326093525"></a><a href="Registry.md#gaa9bb385bfe593f4377a83cf513189bf1">SAMGR_GetRemoteIdentity</a> (const char *service, const char *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246328476093525"><a name="p246328476093525"></a><a name="p246328476093525"></a>SvcIdentity&nbsp;</p>
<p id="p1476705355093525"><a name="p1476705355093525"></a><a name="p1476705355093525"></a>Obtains the IPC address of a remote service and feature based on the service name and feature name. </p>
</td>
</tr>
</tbody>
</table>

