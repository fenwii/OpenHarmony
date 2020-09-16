# Subscriber<a name="ZH-CN_TOPIC_0000001055078177"></a>

## **Overview**<a name="section1050269424093537"></a>

**Related Modules:**

[Broadcast](Broadcast.md)

**Description:**

Defines the subscriber for external interfaces to subsribe to events and data of a topic. 

## **Summary**<a name="section862661270093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1539514791093537"></a>
<table><thead align="left"><tr id="row1788803926093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p766026475093537"><a name="p766026475093537"></a><a name="p766026475093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1823566822093537"><a name="p1823566822093537"></a><a name="p1823566822093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1359810130093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p63729988093537"><a name="p63729988093537"></a><a name="p63729988093537"></a><a href="Subscriber.md#afc91fc1255ae42cba3d037bbe27096fd">AddTopic</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1063501753093537"><a name="p1063501753093537"></a><a name="p1063501753093537"></a>int(*&nbsp;</p>
<p id="p1008725260093537"><a name="p1008725260093537"></a><a name="p1008725260093537"></a>Adds a specified topic to the Broadcast service. </p>
</td>
</tr>
<tr id="row754507280093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570727750093537"><a name="p570727750093537"></a><a name="p570727750093537"></a><a href="Subscriber.md#a963e7a8519c854662e8ba901d08838ee">Subscribe</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, <a href="Consumer.md">Consumer</a> *consumer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432510775093537"><a name="p1432510775093537"></a><a name="p1432510775093537"></a>int(*&nbsp;</p>
<p id="p1859182098093537"><a name="p1859182098093537"></a><a name="p1859182098093537"></a>Subscribes to a specified topic for consumers. </p>
</td>
</tr>
<tr id="row920432738093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p718608506093537"><a name="p718608506093537"></a><a name="p718608506093537"></a><a href="Subscriber.md#ab61beca9e502b1f6098ed49956a9ad51">ModifyConsumer</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, <a href="Consumer.md">Consumer</a> *old, <a href="Consumer.md">Consumer</a> *current)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p847062150093537"><a name="p847062150093537"></a><a name="p847062150093537"></a><a href="Consumer.md">Consumer</a> *(*&nbsp;</p>
<p id="p2104975475093537"><a name="p2104975475093537"></a><a name="p2104975475093537"></a>Modifies the consumer of a specified topic. </p>
</td>
</tr>
<tr id="row665590722093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856891713093537"><a name="p1856891713093537"></a><a name="p1856891713093537"></a><a href="Subscriber.md#a37a99e64f59194d8f2191b91f566f0f4">Unsubscribe</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, const <a href="Consumer.md">Consumer</a> *consumer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423667569093537"><a name="p423667569093537"></a><a name="p423667569093537"></a><a href="Consumer.md">Consumer</a> *(*&nbsp;</p>
<p id="p2100116055093537"><a name="p2100116055093537"></a><a name="p2100116055093537"></a>Unsubscribes from a specified topic. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section363792219093537"></a>

## **Field Documentation**<a name="section1277719032093537"></a>

## AddTopic<a name="afc91fc1255ae42cba3d037bbe27096fd"></a>

```
int(* Subscriber::AddTopic) ([IUnknown](IUnknown.md) *iUnknown, const [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic)
```

 **Description:**

Adds a specified topic to the Broadcast service. 

The specified topic is added by the subscriber. A topic can be subscribed to only after being added. 

**Parameters:**

<a name="table619493823093537"></a>
<table><thead align="left"><tr id="row508902310093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1926447983093537"><a name="p1926447983093537"></a><a name="p1926447983093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p522244406093537"><a name="p522244406093537"></a><a name="p522244406093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1010057299093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. </td>
</tr>
<tr id="row1345178850093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the topic to be subscribed to. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the topic is successfully added; returns other error codes if the topic fails to be added. 



## ModifyConsumer<a name="ab61beca9e502b1f6098ed49956a9ad51"></a>

```
[Consumer](Consumer.md)*(* Subscriber::ModifyConsumer) ([IUnknown](IUnknown.md) *iUnknown, const [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic, [Consumer](Consumer.md) *old, [Consumer](Consumer.md) *current)
```

 **Description:**

Modifies the consumer of a specified topic. 

**Parameters:**

<a name="table431343910093537"></a>
<table><thead align="left"><tr id="row1092943418093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p717556086093537"><a name="p717556086093537"></a><a name="p717556086093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1268419718093537"><a name="p1268419718093537"></a><a name="p1268419718093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row809148142093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the external interface of the pub/sub feature. </td>
</tr>
<tr id="row1022001506093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic whose consumer will be modified. </td>
</tr>
<tr id="row1070989152093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">old</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original consumer of the topic. </td>
</tr>
<tr id="row789008962093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">current</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the new consumer of the topic. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer of the original consumer if the modification is successful; returns  **NULL**  otherwise. 



## Subscribe<a name="a963e7a8519c854662e8ba901d08838ee"></a>

```
int(* Subscriber::Subscribe) ([IUnknown](IUnknown.md) *iUnknown, const [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic, [Consumer](Consumer.md) *consumer)
```

 **Description:**

Subscribes to a specified topic for consumers. 

Call this function on the subscriber. The topic to be subscribed to must have been added to the Broadcast service. 

**Parameters:**

<a name="table1365385974093537"></a>
<table><thead align="left"><tr id="row960410165093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p453290414093537"><a name="p453290414093537"></a><a name="p453290414093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p290403823093537"><a name="p290403823093537"></a><a name="p290403823093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2130324417093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. </td>
</tr>
<tr id="row549974218093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the topic to be subscribed to. </td>
</tr>
<tr id="row1304112894093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">consumer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the consumer who subscribes to the topic. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **EC\_SUCCESS**  if the subscription is successful; returns other error codes if the subscription fails. 



## Unsubscribe<a name="a37a99e64f59194d8f2191b91f566f0f4"></a>

```
[Consumer](Consumer.md)*(* Subscriber::Unsubscribe) ([IUnknown](IUnknown.md) *iUnknown, const [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic, const [Consumer](Consumer.md) *consumer)
```

 **Description:**

Unsubscribes from a specified topic. 

This function cancels the subscription relationship between the specified topic and consumer. 

**Parameters:**

<a name="table404416365093537"></a>
<table><thead align="left"><tr id="row2104038101093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1745005420093537"><a name="p1745005420093537"></a><a name="p1745005420093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1356431644093537"><a name="p1356431644093537"></a><a name="p1356431644093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1253016869093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. This parameter is used to obtain subscription relationships. </td>
</tr>
<tr id="row304806786093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic to unsubscribe from. </td>
</tr>
<tr id="row403672097093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">consumer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the consumer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer of the consumer if the unsubscription is successful; returns  **NULL**  otherwise. 



