# Broadcast<a name="ZH-CN_TOPIC_0000001054915081"></a>

## **Overview**<a name="section90862446191845"></a>

Provides data subscription and data push for services. 

With this module, the  [Service](Service.md),  [Feature](Feature.md), or other modules can broadcast events or data. All services that listen to these events or data can receive these broadcasts. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section39159338191845"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table815182793191845"></a>
<table><thead align="left"><tr id="row929837741191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2113461367191845"><a name="p2113461367191845"></a><a name="p2113461367191845"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p350454567191845"><a name="p350454567191845"></a><a name="p350454567191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row69659156191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1020437120191845"><a name="p1020437120191845"></a><a name="p1020437120191845"></a><a href="Consumer.md">Consumer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284648885191845"><a name="p284648885191845"></a><a name="p284648885191845"></a>Defines the topic consumer used to receive events and push data. You need to implement this struct for your application. </p>
</td>
</tr>
<tr id="row174673196191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1481395820191845"><a name="p1481395820191845"></a><a name="p1481395820191845"></a><a href="Provider.md">Provider</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1674464760191845"><a name="p1674464760191845"></a><a name="p1674464760191845"></a>Defines the provider of events and data of a topic. </p>
</td>
</tr>
<tr id="row581420147191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p820203572191845"><a name="p820203572191845"></a><a name="p820203572191845"></a><a href="Subscriber.md">Subscriber</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1794404163191845"><a name="p1794404163191845"></a><a name="p1794404163191845"></a>Defines the subscriber for external interfaces to subsribe to events and data of a topic. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1730218341191845"></a>
<table><thead align="left"><tr id="row549173102191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1387307071191845"><a name="p1387307071191845"></a><a name="p1387307071191845"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p487914743191845"><a name="p487914743191845"></a><a name="p487914743191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1500756878191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p958619328191845"><a name="p958619328191845"></a><a name="p958619328191845"></a><a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1642576192191845"><a name="p1642576192191845"></a><a name="p1642576192191845"></a>typedef uint32&nbsp;</p>
<p id="p2122631873191845"><a name="p2122631873191845"></a><a name="p2122631873191845"></a>Indicates the topic of an event or data, which is used to distinguish different types of events or data. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1248040671191845"></a>
<table><thead align="left"><tr id="row1816210621191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p408800661191845"><a name="p408800661191845"></a><a name="p408800661191845"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1878578353191845"><a name="p1878578353191845"></a><a name="p1878578353191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1942908505191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1066227017191845"><a name="p1066227017191845"></a><a name="p1066227017191845"></a><a href="Broadcast.md#ga98f7a28020aa045ad049d116e1ca666d">BroadcastErrCode</a> { <a href="Broadcast.md#gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b">EC_ALREADY_SUBSCRIBED</a> = EC_SUCCESS + 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p998342336191845"><a name="p998342336191845"></a><a name="p998342336191845"></a>Enumerates error codes unique to the Broadcast service. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section299824655191845"></a>

## **Typedef Documentation**<a name="section1378812707191845"></a>

## Topic<a name="gaf03f5bc94cad32ab628a6cdee09b0542"></a>

```
typedef uint32 [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542)
```

 **Description:**

Indicates the topic of an event or data, which is used to distinguish different types of events or data. 

## **Enumeration Type Documentation**<a name="section1322993724191845"></a>

## BroadcastErrCode<a name="ga98f7a28020aa045ad049d116e1ca666d"></a>

```
enum [BroadcastErrCode](Broadcast.md#ga98f7a28020aa045ad049d116e1ca666d)
```

 **Description:**

Enumerates error codes unique to the Broadcast service. 

<a name="table1373728565191845"></a>
<table><thead align="left"><tr id="row126275586191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2055022088191845"><a name="p2055022088191845"></a><a name="p2055022088191845"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1062641564191845"><a name="p1062641564191845"></a><a name="p1062641564191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row596776902191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b"><a name="gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b"></a><a name="gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b"></a></strong>EC_ALREADY_SUBSCRIBED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p299418997191845"><a name="p299418997191845"></a><a name="p299418997191845"></a>Error code showing that a topic has been subscribed to </p>
 </td>
</tr>
</tbody>
</table>

