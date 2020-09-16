# Provider<a name="EN-US_TOPIC_0000001054476501"></a>

## **Overview**<a name="section663067880191900"></a>

**Related Modules:**

[Broadcast](broadcast.md)

**Description:**

Defines the provider of events and data of a topic. 

## **Summary**<a name="section1487115097191900"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1289206452191900"></a>
<table><thead align="left"><tr id="row984823785191900"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1804219399191900"><a name="p1804219399191900"></a><a name="p1804219399191900"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2057048956191900"><a name="p2057048956191900"></a><a name="p2057048956191900"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row408495216191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p590873746191900"><a name="p590873746191900"></a><a name="p590873746191900"></a><a href="provider.md#afbce5ffb04137a55e45161a7ba8577b7">Publish</a> )(<a href="iunknown.md">IUnknown</a> *iUnknown, const <a href="broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, uint8 *data, int16 len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1186582569191900"><a name="p1186582569191900"></a><a name="p1186582569191900"></a>BOOL(* </p>
<p id="p1651551524191900"><a name="p1651551524191900"></a><a name="p1651551524191900"></a>Publishes events and data of a specified topic. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1379136952191900"></a>

## **Field Documentation**<a name="section1071721486191900"></a>

## Publish<a name="afbce5ffb04137a55e45161a7ba8577b7"></a>

```
BOOL(* Provider::Publish) ([IUnknown](iunknown.md) *iUnknown, const [Topic](broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic, uint8 *data, int16 len)
```

 **Description:**

Publishes events and data of a specified topic. 

The events or data is published by the publisher, sent to all consumers who have subscribed to the topic, and processed by the consumers. 

**Parameters:**

<a name="table319141948191900"></a>
<table><thead align="left"><tr id="row999890591191900"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p840475230191900"><a name="p840475230191900"></a><a name="p840475230191900"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p439353547191900"><a name="p439353547191900"></a><a name="p439353547191900"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1788395504191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. </td>
</tr>
<tr id="row1450382891191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic to publish. </td>
</tr>
<tr id="row253019304191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to publish. </td>
</tr>
<tr id="row755808410191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to be published. The length must be the same as the <strong id="b1136706137191900"><a name="b1136706137191900"></a><a name="b1136706137191900"></a>data</strong> length. The caller must ensure the validity of this parameter. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the topic is successfully published; returns  **FALSE**  otherwise. 



