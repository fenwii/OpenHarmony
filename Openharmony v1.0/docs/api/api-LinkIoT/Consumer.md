# Consumer<a name="ZH-CN_TOPIC_0000001054476499"></a>

## **Overview**<a name="section367884173191858"></a>

**Related Modules:**

[Broadcast](Broadcast.md)

**Description:**

Defines the topic consumer used to receive events and push data. You need to implement this struct for your application. 

## **Summary**<a name="section1229562524191858"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table494404447191858"></a>
<table><thead align="left"><tr id="row1177098769191858"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1510694763191858"><a name="p1510694763191858"></a><a name="p1510694763191858"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p359040708191858"><a name="p359040708191858"></a><a name="p359040708191858"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row541337055191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p664636100191858"><a name="p664636100191858"></a><a name="p664636100191858"></a><a href="Consumer.md#ac6e98b3361e6be922804e8c459fe303b">identity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788137349191858"><a name="p788137349191858"></a><a name="p788137349191858"></a>const <a href="Identity.md">Identity</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1891627096191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p830646910191858"><a name="p830646910191858"></a><a name="p830646910191858"></a><a href="Consumer.md#a57b8ea7ff05c30832af06804a0526765">Notify</a> )(<a href="Consumer.md">Consumer</a> *consumer, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, const <a href="Request.md">Request</a> *origin)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1596993159191858"><a name="p1596993159191858"></a><a name="p1596993159191858"></a>void(*&nbsp;</p>
<p id="p711307819191858"><a name="p711307819191858"></a><a name="p711307819191858"></a>Defines how the consumer will process the events or data of a released topic. </p>
</td>
</tr>
<tr id="row551589053191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381665072191858"><a name="p381665072191858"></a><a name="p381665072191858"></a><a href="Consumer.md#a38ab45549e981dc8c8c0a90883a6bac8">Equal</a> )(const <a href="Consumer.md">Consumer</a> *current, const <a href="Consumer.md">Consumer</a> *other)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1685313723191858"><a name="p1685313723191858"></a><a name="p1685313723191858"></a>BOOL(*&nbsp;</p>
<p id="p886417998191858"><a name="p886417998191858"></a><a name="p886417998191858"></a>Checks whether two consumers are equal. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1372276845191858"></a>

## **Field Documentation**<a name="section77297961191858"></a>

## Equal<a name="a38ab45549e981dc8c8c0a90883a6bac8"></a>

```
BOOL(* Consumer::Equal) (const [Consumer](Consumer.md) *current, const [Consumer](Consumer.md) *other)
```

 **Description:**

Checks whether two consumers are equal. 

You need to implement this function to prevent repeated topic subscription. 

**Parameters:**

<a name="table1614659320191858"></a>
<table><thead align="left"><tr id="row900903701191858"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1944786767191858"><a name="p1944786767191858"></a><a name="p1944786767191858"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1202034969191858"><a name="p1202034969191858"></a><a name="p1202034969191858"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row486662959191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">current</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the current consumer. </td>
</tr>
<tr id="row1035514191191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">other</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target consumer to compare. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the two consumers are equal; returns  **FALSE**  otherwise. 



## identity<a name="ac6e98b3361e6be922804e8c459fe303b"></a>

```
const [Identity](Identity.md)* Consumer::identity
```

 **Description:**

[Consumer](Consumer.md)  ID 

## Notify<a name="a57b8ea7ff05c30832af06804a0526765"></a>

```
void(* Consumer::Notify) ([Consumer](Consumer.md) *consumer, const [Topic](Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic, const [Request](Request.md) *origin)
```

 **Description:**

Defines how the consumer will process the events or data of a released topic. 

You can implement this function for consumers to process topics associated with the them. Note that the passed topic must have been subscribed by the consumer. Otherwise, the function does nothing. 

**Parameters:**

<a name="table930491084191858"></a>
<table><thead align="left"><tr id="row549325055191858"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1507178705191858"><a name="p1507178705191858"></a><a name="p1507178705191858"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2034406603191858"><a name="p2034406603191858"></a><a name="p2034406603191858"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row358410277191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">consumer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates <strong id="b602146788191858"><a name="b602146788191858"></a><a name="b602146788191858"></a>this</strong> pointer of the consumer. </td>
</tr>
<tr id="row1998990578191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic to be processed. </td>
</tr>
<tr id="row2068793086191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">origin</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to be processed. </td>
</tr>
</tbody>
</table>

