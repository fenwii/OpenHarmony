# session.h<a name="EN-US_TOPIC_0000001055195060"></a>

## **Overview**<a name="section347263415191850"></a>

**Related Modules:**

[Softbus](softbus.md)

**Description:**

Declares unified data transmission interfaces. 

This file provides data transmission capabilities, including creating and removing a session server, opening and closing sessions, receiving data, and querying basic session information. After multiple nearby devices are discovered and networked, these interfaces can be used to transmit data across devices. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1201786925191850"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table464755308191850"></a>
<table><thead align="left"><tr id="row2109716048191850"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1165991245191850"><a name="p1165991245191850"></a><a name="p1165991245191850"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p670551981191850"><a name="p670551981191850"></a><a name="p670551981191850"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2001288377191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p765293961191850"><a name="p765293961191850"></a><a name="p765293961191850"></a><a href="isessionlistener.md">ISessionListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p52010906191850"><a name="p52010906191850"></a><a name="p52010906191850"></a>Defines session callbacks. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table269468650191850"></a>
<table><thead align="left"><tr id="row509631151191850"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1107812792191850"><a name="p1107812792191850"></a><a name="p1107812792191850"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2099590694191850"><a name="p2099590694191850"></a><a name="p2099590694191850"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1345238350191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339485991191850"><a name="p339485991191850"></a><a name="p339485991191850"></a><a href="softbus.md#gad7e95cced3378e8f489553d70b121392">CreateSessionServer</a> (const char *mouduleName, const char *sessionName, struct <a href="isessionlistener.md">ISessionListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2138475678191850"><a name="p2138475678191850"></a><a name="p2138475678191850"></a>int </p>
<p id="p1547580346191850"><a name="p1547580346191850"></a><a name="p1547580346191850"></a>Creates a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row1621694930191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076630316191850"><a name="p2076630316191850"></a><a name="p2076630316191850"></a><a href="softbus.md#ga225a1e178544457263d94078e638b7b5">RemoveSessionServer</a> (const char *mouduleName, const char *sessionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309083734191850"><a name="p309083734191850"></a><a name="p309083734191850"></a>int </p>
<p id="p952645970191850"><a name="p952645970191850"></a><a name="p952645970191850"></a>Removes a session server based on a module name and session name. </p>
</td>
</tr>
<tr id="row1498725396191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723045014191850"><a name="p723045014191850"></a><a name="p723045014191850"></a><a href="softbus.md#ga0333c76724dbef71bca48fb2a82e6980">SendBytes</a> (int sessionId, const void *data, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181959608191850"><a name="p181959608191850"></a><a name="p181959608191850"></a>int </p>
<p id="p1493334283191850"><a name="p1493334283191850"></a><a name="p1493334283191850"></a>Sends data based on a session ID. </p>
</td>
</tr>
<tr id="row11177390191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p168975478191850"><a name="p168975478191850"></a><a name="p168975478191850"></a><a href="softbus.md#ga00611f717919f4156c74b7919b28c7d8">GetMySessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1528791458191850"><a name="p1528791458191850"></a><a name="p1528791458191850"></a>int </p>
<p id="p1728371366191850"><a name="p1728371366191850"></a><a name="p1728371366191850"></a>Obtains the session name registered by the local device based on the session ID. </p>
</td>
</tr>
<tr id="row1374836815191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047475709191850"><a name="p1047475709191850"></a><a name="p1047475709191850"></a><a href="softbus.md#ga92d5a47fcdf97a0e01797c77e644033e">GetPeerSessionName</a> (int sessionId, char *sessionName, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1794515787191850"><a name="p1794515787191850"></a><a name="p1794515787191850"></a>int </p>
<p id="p2097384205191850"><a name="p2097384205191850"></a><a name="p2097384205191850"></a>Obtains the session name registered by the peer device based on the session ID. </p>
</td>
</tr>
<tr id="row167905559191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1975444409191850"><a name="p1975444409191850"></a><a name="p1975444409191850"></a><a href="softbus.md#ga21b9a889069eea6e7fe653820e601c04">GetPeerDeviceId</a> (int sessionId, char *devId, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p429008240191850"><a name="p429008240191850"></a><a name="p429008240191850"></a>int </p>
<p id="p1249024965191850"><a name="p1249024965191850"></a><a name="p1249024965191850"></a>Obtains the peer device ID based on a session ID. </p>
</td>
</tr>
<tr id="row1035797152191850"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1093811689191850"><a name="p1093811689191850"></a><a name="p1093811689191850"></a><a href="softbus.md#ga5b0c0b334f387f9c2753146ee0890780">CloseSession</a> (int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910693025191850"><a name="p1910693025191850"></a><a name="p1910693025191850"></a>void </p>
<p id="p1171631554191850"><a name="p1171631554191850"></a><a name="p1171631554191850"></a>Closes a connected session based on a session ID. </p>
</td>
</tr>
</tbody>
</table>

