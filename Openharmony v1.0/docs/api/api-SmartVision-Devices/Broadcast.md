# Broadcast<a name="ZH-CN_TOPIC_0000001055198082"></a>

## **Overview**<a name="section2020099446093522"></a>

Provides data subscription and data push for services. 

With this module, the  [Service](Service.md),  [Feature](Feature.md), or other modules can broadcast events or data. All services that listen to these events or data can receive these broadcasts. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2076539719093522"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table972607761093522"></a>
<table><thead align="left"><tr id="row432682251093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1384427568093522"><a name="p1384427568093522"></a><a name="p1384427568093522"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p778329317093522"><a name="p778329317093522"></a><a name="p778329317093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1103888900093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p660514569093522"><a name="p660514569093522"></a><a name="p660514569093522"></a><a href="Consumer.md">Consumer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2023059778093522"><a name="p2023059778093522"></a><a name="p2023059778093522"></a>Defines the topic consumer used to receive events and push data. You need to implement this struct for your application. </p>
</td>
</tr>
<tr id="row915327678093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076462525093522"><a name="p1076462525093522"></a><a name="p1076462525093522"></a><a href="Provider.md">Provider</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1216124156093522"><a name="p1216124156093522"></a><a name="p1216124156093522"></a>Defines the provider of events and data of a topic. </p>
</td>
</tr>
<tr id="row1464638215093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419476025093522"><a name="p419476025093522"></a><a name="p419476025093522"></a><a href="Subscriber.md">Subscriber</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1366955182093522"><a name="p1366955182093522"></a><a name="p1366955182093522"></a>Defines the subscriber for external interfaces to subsribe to events and data of a topic. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1460594825093522"></a>
<table><thead align="left"><tr id="row2086331267093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1510119509093522"><a name="p1510119509093522"></a><a name="p1510119509093522"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p158903531093522"><a name="p158903531093522"></a><a name="p158903531093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row31813721093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953732136093522"><a name="p953732136093522"></a><a name="p953732136093522"></a><a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880909842093522"><a name="p1880909842093522"></a><a name="p1880909842093522"></a>typedef uint32&nbsp;</p>
<p id="p876040854093522"><a name="p876040854093522"></a><a name="p876040854093522"></a>Indicates the topic of an event or data, which is used to distinguish different types of events or data. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table731636903093522"></a>
<table><thead align="left"><tr id="row783586877093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1780021043093522"><a name="p1780021043093522"></a><a name="p1780021043093522"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p279308087093522"><a name="p279308087093522"></a><a name="p279308087093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1289387733093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p134192101093522"><a name="p134192101093522"></a><a name="p134192101093522"></a><a href="Broadcast.md#ga98f7a28020aa045ad049d116e1ca666d">BroadcastErrCode</a> { <a href="Broadcast.md#gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b">EC_ALREADY_SUBSCRIBED</a> = EC_SUCCESS + 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488765190093522"><a name="p1488765190093522"></a><a name="p1488765190093522"></a>Enumerates error codes unique to the Broadcast service. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1659243352093522"></a>

## **Typedef Documentation**<a name="section1835074243093522"></a>

## Topic<a name="gaf03f5bc94cad32ab628a6cdee09b0542"></a>

```
typedef uint32 [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542)
```

 **Description:**

Indicates the topic of an event or data, which is used to distinguish different types of events or data. 

## **Enumeration Type Documentation**<a name="section1985271405093522"></a>

## BroadcastErrCode<a name="ga98f7a28020aa045ad049d116e1ca666d"></a>

```
enum [BroadcastErrCode](Broadcast.md#ga98f7a28020aa045ad049d116e1ca666d)
```

 **Description:**

Enumerates error codes unique to the Broadcast service. 

<a name="table1771556048093522"></a>
<table><thead align="left"><tr id="row364557440093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p948047427093522"><a name="p948047427093522"></a><a name="p948047427093522"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p675399713093522"><a name="p675399713093522"></a><a name="p675399713093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row903452516093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b"><a name="gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b"></a><a name="gga98f7a28020aa045ad049d116e1ca666da200821a903aa0ca4df7e25d2a0a3186b"></a></strong>EC_ALREADY_SUBSCRIBED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p430124273093522"><a name="p430124273093522"></a><a name="p430124273093522"></a>Error code showing that a topic has been subscribed to </p>
 </td>
</tr>
</tbody>
</table>

