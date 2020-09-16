# Consumer<a name="ZH-CN_TOPIC_0000001055078133"></a>

## **Overview**<a name="section546609585093529"></a>

**Related Modules:**

[Broadcast](Broadcast.md)

**Description:**

Defines the topic consumer used to receive events and push data. You need to implement this struct for your application. 

## **Summary**<a name="section181714182093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table513070777093529"></a>
<table><thead align="left"><tr id="row1285104842093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p555966821093529"><a name="p555966821093529"></a><a name="p555966821093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p36634247093529"><a name="p36634247093529"></a><a name="p36634247093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1809371865093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1114172460093529"><a name="p1114172460093529"></a><a name="p1114172460093529"></a><a href="Consumer.md#ac6e98b3361e6be922804e8c459fe303b">identity</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1747706975093529"><a name="p1747706975093529"></a><a name="p1747706975093529"></a>const <a href="Identity.md">Identity</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1298748789093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p6498987093529"><a name="p6498987093529"></a><a name="p6498987093529"></a><a href="Consumer.md#a57b8ea7ff05c30832af06804a0526765">Notify</a> )(<a href="Consumer.md">Consumer</a> *consumer, const <a href="Broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, const <a href="Request.md">Request</a> *origin)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2004502863093529"><a name="p2004502863093529"></a><a name="p2004502863093529"></a>void(*&nbsp;</p>
<p id="p1020109672093529"><a name="p1020109672093529"></a><a name="p1020109672093529"></a>Defines how the consumer will process the events or data of a released topic. </p>
</td>
</tr>
<tr id="row1359859583093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p268105192093529"><a name="p268105192093529"></a><a name="p268105192093529"></a><a href="Consumer.md#a38ab45549e981dc8c8c0a90883a6bac8">Equal</a> )(const <a href="Consumer.md">Consumer</a> *current, const <a href="Consumer.md">Consumer</a> *other)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p156571843093529"><a name="p156571843093529"></a><a name="p156571843093529"></a>BOOL(*&nbsp;</p>
<p id="p1472546537093529"><a name="p1472546537093529"></a><a name="p1472546537093529"></a>Checks whether two consumers are equal. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section858939676093529"></a>

## **Field Documentation**<a name="section1869506993093529"></a>

## Equal<a name="a38ab45549e981dc8c8c0a90883a6bac8"></a>

```
BOOL(* Consumer::Equal) (const [Consumer](Consumer.md) *current, const [Consumer](Consumer.md) *other)
```

 **Description:**

Checks whether two consumers are equal. 

You need to implement this function to prevent repeated topic subscription. 

**Parameters:**

<a name="table2059435556093529"></a>
<table><thead align="left"><tr id="row106012644093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1699721759093529"><a name="p1699721759093529"></a><a name="p1699721759093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1797424450093529"><a name="p1797424450093529"></a><a name="p1797424450093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1500729193093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">current</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the current consumer. </td>
</tr>
<tr id="row1855267687093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">other</td>
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

<a name="table1146310509093529"></a>
<table><thead align="left"><tr id="row94293384093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1967543641093529"><a name="p1967543641093529"></a><a name="p1967543641093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p154436163093529"><a name="p154436163093529"></a><a name="p154436163093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row910283182093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">consumer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates <strong id="b774168409093529"><a name="b774168409093529"></a><a name="b774168409093529"></a>this</strong> pointer of the consumer. </td>
</tr>
<tr id="row392843084093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic to be processed. </td>
</tr>
<tr id="row974577217093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">origin</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to be processed. </td>
</tr>
</tbody>
</table>

