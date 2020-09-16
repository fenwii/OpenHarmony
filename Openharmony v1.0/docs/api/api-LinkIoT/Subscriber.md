# Subscriber<a name="ZH-CN_TOPIC_0000001055075079"></a>

## **Overview**<a name="section1985408182191901"></a>

**Related Modules:**

[Broadcast](Broadcast.md)

**Description:**

Defines the subscriber for external interfaces to subsribe to events and data of a topic. 

## **Summary**<a name="section994484897191901"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table617257847191901"></a>
<table><thead align="left"><tr id="row793054636191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2053834074191901"><a name="p2053834074191901"></a><a name="p2053834074191901"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1542419435191901"><a name="p1542419435191901"></a><a name="p1542419435191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row73835256191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977548559191901"><a name="p977548559191901"></a><a name="p977548559191901"></a><a href="Subscriber.md#afc91fc1255ae42cba3d037bbe27096fd">AddTopic</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182636881191901"><a name="p182636881191901"></a><a name="p182636881191901"></a>int(*&nbsp;</p>
<p id="p1636490029191901"><a name="p1636490029191901"></a><a name="p1636490029191901"></a>Adds a specified topic to the Broadcast service. </p>
</td>
</tr>
<tr id="row879002791191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p3536074191901"><a name="p3536074191901"></a><a name="p3536074191901"></a><a href="Subscriber.md#a963e7a8519c854662e8ba901d08838ee">Subscribe</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, <a href="Consumer.md">Consumer</a> *consumer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1368124651191901"><a name="p1368124651191901"></a><a name="p1368124651191901"></a>int(*&nbsp;</p>
<p id="p577740974191901"><a name="p577740974191901"></a><a name="p577740974191901"></a>Subscribes to a specified topic for consumers. </p>
</td>
</tr>
<tr id="row129508358191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1879553092191901"><a name="p1879553092191901"></a><a name="p1879553092191901"></a><a href="Subscriber.md#ab61beca9e502b1f6098ed49956a9ad51">ModifyConsumer</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, <a href="Consumer.md">Consumer</a> *old, <a href="Consumer.md">Consumer</a> *current)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435328711191901"><a name="p1435328711191901"></a><a name="p1435328711191901"></a><a href="Consumer.md">Consumer</a> *(*&nbsp;</p>
<p id="p440067533191901"><a name="p440067533191901"></a><a name="p440067533191901"></a>Modifies the consumer of a specified topic. </p>
</td>
</tr>
<tr id="row938418524191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670171341191901"><a name="p670171341191901"></a><a name="p670171341191901"></a><a href="Subscriber.md#a37a99e64f59194d8f2191b91f566f0f4">Unsubscribe</a> )(<a href="IUnknown.md">IUnknown</a> *iUnknown, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, const <a href="Consumer.md">Consumer</a> *consumer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1964848560191901"><a name="p1964848560191901"></a><a name="p1964848560191901"></a><a href="Consumer.md">Consumer</a> *(*&nbsp;</p>
<p id="p982919372191901"><a name="p982919372191901"></a><a name="p982919372191901"></a>Unsubscribes from a specified topic. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section295221812191901"></a>

## **Field Documentation**<a name="section87464860191901"></a>

## AddTopic<a name="afc91fc1255ae42cba3d037bbe27096fd"></a>

```
int(* Subscriber::AddTopic) ([IUnknown](IUnknown.md) *iUnknown, const [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic)
```

 **Description:**

Adds a specified topic to the Broadcast service. 

The specified topic is added by the subscriber. A topic can be subscribed to only after being added. 

**Parameters:**

<a name="table317522568191901"></a>
<table><thead align="left"><tr id="row443025122191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1650234996191901"><a name="p1650234996191901"></a><a name="p1650234996191901"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p669596765191901"><a name="p669596765191901"></a><a name="p669596765191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1371096085191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. </td>
</tr>
<tr id="row1188292776191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
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

<a name="table2138923035191901"></a>
<table><thead align="left"><tr id="row426699676191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1134444984191901"><a name="p1134444984191901"></a><a name="p1134444984191901"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1984167644191901"><a name="p1984167644191901"></a><a name="p1984167644191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1219988108191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the external interface of the pub/sub feature. </td>
</tr>
<tr id="row1898871028191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic whose consumer will be modified. </td>
</tr>
<tr id="row676132765191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">old</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original consumer of the topic. </td>
</tr>
<tr id="row845103709191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">current</td>
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

<a name="table1833147061191901"></a>
<table><thead align="left"><tr id="row1110680017191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2134889524191901"><a name="p2134889524191901"></a><a name="p2134889524191901"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p416711325191901"><a name="p416711325191901"></a><a name="p416711325191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1449959915191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. </td>
</tr>
<tr id="row1429944102191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the topic to be subscribed to. </td>
</tr>
<tr id="row1836273387191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">consumer</td>
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

<a name="table147804101191901"></a>
<table><thead align="left"><tr id="row1327649552191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p386422130191901"><a name="p386422130191901"></a><a name="p386422130191901"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1951005052191901"><a name="p1951005052191901"></a><a name="p1951005052191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1206373518191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. This parameter is used to obtain subscription relationships. </td>
</tr>
<tr id="row810080714191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic to unsubscribe from. </td>
</tr>
<tr id="row745803517191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">consumer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the consumer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer of the consumer if the unsubscription is successful; returns  **NULL**  otherwise. 



