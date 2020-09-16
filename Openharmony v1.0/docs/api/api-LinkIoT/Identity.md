# Identity<a name="ZH-CN_TOPIC_0000001054796537"></a>

## **Overview**<a name="section950175188191900"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Identifies a service and feature. 

You can use this structure to identity a  [IUnknown](IUnknown.md)  feature to which messages will be sent through the asynchronous function of  [IUnknown](IUnknown.md). 

## **Summary**<a name="section589956340191900"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table9722272191900"></a>
<table><thead align="left"><tr id="row516228669191900"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1797782894191900"><a name="p1797782894191900"></a><a name="p1797782894191900"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p134693634191900"><a name="p134693634191900"></a><a name="p134693634191900"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2050965711191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1815511345191900"><a name="p1815511345191900"></a><a name="p1815511345191900"></a><a href="Identity.md#a062375b8be3ad40e72263a7ce2268af3">serviceId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p571977163191900"><a name="p571977163191900"></a><a name="p571977163191900"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row1783301586191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p184991736191900"><a name="p184991736191900"></a><a name="p184991736191900"></a><a href="Identity.md#a8a76b43d4bb4e3d861ff63e0716f178d">featureId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2016708199191900"><a name="p2016708199191900"></a><a name="p2016708199191900"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row1972222286191900"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2008731916191900"><a name="p2008731916191900"></a><a name="p2008731916191900"></a><a href="Identity.md#ad34d38c75a24903672bb64f29c1b1132">queueId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657919581191900"><a name="p1657919581191900"></a><a name="p1657919581191900"></a>MQueueId&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section107323322191900"></a>

## **Field Documentation**<a name="section1141630383191900"></a>

## featureId<a name="a8a76b43d4bb4e3d861ff63e0716f178d"></a>

```
int16 Identity::featureId
```

 **Description:**

[Feature](Feature.md)  ID 

## queueId<a name="ad34d38c75a24903672bb64f29c1b1132"></a>

```
MQueueId Identity::queueId
```

 **Description:**

Message queue ID 

## serviceId<a name="a062375b8be3ad40e72263a7ce2268af3"></a>

```
int16 Identity::serviceId
```

 **Description:**

[Service](Service.md)  ID 

