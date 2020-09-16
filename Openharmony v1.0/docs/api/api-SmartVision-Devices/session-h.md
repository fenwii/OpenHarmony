# session.h<a name="ZH-CN_TOPIC_0000001054598139"></a>

## **Overview**<a name="section1667447351093527"></a>

**Related Modules:**

[Softbus](Softbus.md)

**Description:**

Declares unified data transmission interfaces. 

This file provides data transmission capabilities, including creating and removing a session server, opening and closing sessions, receiving data, and querying basic session information. After multiple nearby devices are discovered and networked, these interfaces can be used to transmit data across devices. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1630199358093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table639746548093527"></a>
<table><thead align="left"><tr id="row1867246581093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p254656588093527"><a name="p254656588093527"></a><a name="p254656588093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1762605445093527"><a name="p1762605445093527"></a><a name="p1762605445093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row436490196093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256475113093527"><a name="p256475113093527"></a><a name="p256475113093527"></a><a href="ISessionListener.md">ISessionListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340183982093527"><a name="p340183982093527"></a><a name="p340183982093527"></a>Defines session callbacks. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table926769668093527"></a>
<table><thead align="left"><tr id="row1576684144093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p365294529093527"><a name="p365294529093527"></a><a name="p365294529093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p643376664093527"><a name="p643376664093527"></a><a name="p643376664093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row539377878093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p399980539093527"><a name="p399980539093527"></a><a name="p399980539093527"></a><a href="Softbus.md#gad7e95cced3378e8f489553d70b121392">CreateSessionServer</a> (const char *mouduleName, const char *sessionName, struct <a href="ISessionListener.md">ISessionListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225262999093527"><a name="p1225262999093527"></a><a name="p1225262999093527"></a>int&nbsp;</p>
<p id="p1298987652093527"><a name="p1298987652093527"></a><a name="p1298987652093527"></a>Creates a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row794663138093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1941819865093527"><a name="p1941819865093527"></a><a name="p1941819865093527"></a><a href="Softbus.md#ga225a1e178544457263d94078e638b7b5">RemoveSessionServer</a> (const char *mouduleName, const char *sessionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743903286093527"><a name="p1743903286093527"></a><a name="p1743903286093527"></a>int&nbsp;</p>
<p id="p904861188093527"><a name="p904861188093527"></a><a name="p904861188093527"></a>Removes a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row562117958093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1056800926093527"><a name="p1056800926093527"></a><a name="p1056800926093527"></a><a href="Softbus.md#ga0333c76724dbef71bca48fb2a82e6980">SendBytes</a> (int sessionId, const void *data, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71006655093527"><a name="p71006655093527"></a><a name="p71006655093527"></a>int&nbsp;</p>
<p id="p1634408307093527"><a name="p1634408307093527"></a><a name="p1634408307093527"></a>Sends data based on a session ID. </p>
</td>
</tr>
<tr id="row568203204093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221364836093527"><a name="p221364836093527"></a><a name="p221364836093527"></a><a href="Softbus.md#ga00611f717919f4156c74b7919b28c7d8">GetMySessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1986607613093527"><a name="p1986607613093527"></a><a name="p1986607613093527"></a>int&nbsp;</p>
<p id="p116137201093527"><a name="p116137201093527"></a><a name="p116137201093527"></a>Obtains the session name registered by the local device based on the session ID. </p>
</td>
</tr>
<tr id="row56595884093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1877715681093527"><a name="p1877715681093527"></a><a name="p1877715681093527"></a><a href="Softbus.md#ga92d5a47fcdf97a0e01797c77e644033e">GetPeerSessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p116277374093527"><a name="p116277374093527"></a><a name="p116277374093527"></a>int&nbsp;</p>
<p id="p1664502173093527"><a name="p1664502173093527"></a><a name="p1664502173093527"></a>Obtains the session name registered by the peer device based on the session ID. </p>
</td>
</tr>
<tr id="row810995636093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906323485093527"><a name="p1906323485093527"></a><a name="p1906323485093527"></a><a href="Softbus.md#ga21b9a889069eea6e7fe653820e601c04">GetPeerDeviceId</a> (int sessionId, char *devId, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p144362874093527"><a name="p144362874093527"></a><a name="p144362874093527"></a>int&nbsp;</p>
<p id="p455189900093527"><a name="p455189900093527"></a><a name="p455189900093527"></a>Obtains the peer device ID based on a session ID. </p>
</td>
</tr>
<tr id="row86043893093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230413151093527"><a name="p1230413151093527"></a><a name="p1230413151093527"></a><a href="Softbus.md#ga5b0c0b334f387f9c2753146ee0890780">CloseSession</a> (int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1618214093093527"><a name="p1618214093093527"></a><a name="p1618214093093527"></a>void&nbsp;</p>
<p id="p692018681093527"><a name="p692018681093527"></a><a name="p692018681093527"></a>Closes a connected session based on a session ID. </p>
</td>
</tr>
</tbody>
</table>

