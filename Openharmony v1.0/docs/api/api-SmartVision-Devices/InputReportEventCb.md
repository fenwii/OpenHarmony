# InputReportEventCb<a name="ZH-CN_TOPIC_0000001055358110"></a>

## **Overview**<a name="section306009713093530"></a>

**Related Modules:**

[Input](Input.md)

**Description:**

Describes the input event callback registered by the input service. 

## **Summary**<a name="section285004506093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table555771748093530"></a>
<table><thead align="left"><tr id="row1967068550093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p891805004093530"><a name="p891805004093530"></a><a name="p891805004093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p861625448093530"><a name="p861625448093530"></a><a name="p861625448093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1078231235093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014235093093530"><a name="p2014235093093530"></a><a name="p2014235093093530"></a><a href="InputReportEventCb.md#a458c9d1bae3f36937db2977fcc777136">ReportEventCallback</a> )(const <a href="InputEventData.md">InputEventData</a> *eventData, uint32_t count, uint32_t devIndex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p286590896093530"><a name="p286590896093530"></a><a name="p286590896093530"></a>void(*&nbsp;</p>
<p id="p2057518916093530"><a name="p2057518916093530"></a><a name="p2057518916093530"></a>Reports input event data by the registered callback. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1069162285093530"></a>

## **Field Documentation**<a name="section1142011640093530"></a>

## ReportEventCallback<a name="a458c9d1bae3f36937db2977fcc777136"></a>

```
void(* InputReportEventCb::ReportEventCallback) (const [InputEventData](InputEventData.md) *eventData, uint32_t count, uint32_t devIndex)
```

 **Description:**

Reports input event data by the registered callback. 

**Parameters:**

<a name="table638359772093530"></a>
<table><thead align="left"><tr id="row648975372093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1114379095093530"><a name="p1114379095093530"></a><a name="p1114379095093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1554617536093530"><a name="p1554617536093530"></a><a name="p1554617536093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1273904259093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">eventData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the input event data reported by the input driver. </td>
</tr>
<tr id="row1445131425093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of input event data packets. </td>
</tr>
<tr id="row2003016940093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of an input device. A maximum of 32 input devices are supported. The value ranges from 0 to 31, and value <strong id="b1653505514093530"><a name="b1653505514093530"></a><a name="b1653505514093530"></a>0</strong> represents the first input device.</td>
</tr>
</tbody>
</table>

