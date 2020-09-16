# Provider<a name="EN-US_TOPIC_0000001055678128"></a>

## **Overview**<a name="section476743158093536"></a>

**Related Modules:**

[Broadcast](broadcast.md)

**Description:**

Defines the provider of events and data of a topic. 

## **Summary**<a name="section458893021093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2124153862093536"></a>
<table><thead align="left"><tr id="row530865901093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1496523514093536"><a name="p1496523514093536"></a><a name="p1496523514093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1710665468093536"><a name="p1710665468093536"></a><a name="p1710665468093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1807139675093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224461453093536"><a name="p224461453093536"></a><a name="p224461453093536"></a><a href="provider.md#afbce5ffb04137a55e45161a7ba8577b7">Publish</a> )(<a href="iunknown.md">IUnknown</a> *iUnknown, const <a href="broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542">Topic</a> *topic, uint8 *data, int16 len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418622423093536"><a name="p418622423093536"></a><a name="p418622423093536"></a>BOOL(* </p>
<p id="p1217497016093536"><a name="p1217497016093536"></a><a name="p1217497016093536"></a>Publishes events and data of a specified topic. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1864469955093536"></a>

## **Field Documentation**<a name="section690909188093536"></a>

## Publish<a name="afbce5ffb04137a55e45161a7ba8577b7"></a>

```
BOOL(* Provider::Publish) ([IUnknown](iunknown.md) *iUnknown, const [Topic](broadcast.md#gaf03f5bc94cad32ab628a6cdee09b0542) *topic, uint8 *data, int16 len)
```

 **Description:**

Publishes events and data of a specified topic. 

The events or data is published by the publisher, sent to all consumers who have subscribed to the topic, and processed by the consumers. 

**Parameters:**

<a name="table347162493093536"></a>
<table><thead align="left"><tr id="row1710828622093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1788075064093536"><a name="p1788075064093536"></a><a name="p1788075064093536"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1513251560093536"><a name="p1513251560093536"></a><a name="p1513251560093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1008023136093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iUnknown</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates external interface of the pub/sub feature. </td>
</tr>
<tr id="row1286161531093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">topic</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the topic to publish. </td>
</tr>
<tr id="row1252265065093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to publish. </td>
</tr>
<tr id="row2110765212093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to be published. The length must be the same as the <strong id="b1980544555093536"><a name="b1980544555093536"></a><a name="b1980544555093536"></a>data</strong> length. The caller must ensure the validity of this parameter. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the topic is successfully published; returns  **FALSE**  otherwise. 



