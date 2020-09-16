# Identity<a name="EN-US_TOPIC_0000001054918159"></a>

## **Overview**<a name="section1343018722093531"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Identifies a service and feature. 

You can use this structure to identity a  [IUnknown](iunknown.md)  feature to which messages will be sent through the asynchronous function of  [IUnknown](iunknown.md). 

## **Summary**<a name="section1824797420093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1748022383093531"></a>
<table><thead align="left"><tr id="row2052152275093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1481014007093531"><a name="p1481014007093531"></a><a name="p1481014007093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p769463198093531"><a name="p769463198093531"></a><a name="p769463198093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1286229000093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969044496093531"><a name="p1969044496093531"></a><a name="p1969044496093531"></a><a href="identity.md#a062375b8be3ad40e72263a7ce2268af3">serviceId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p960446457093531"><a name="p960446457093531"></a><a name="p960446457093531"></a>int16 </p>
</td>
</tr>
<tr id="row19291431093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p356234182093531"><a name="p356234182093531"></a><a name="p356234182093531"></a><a href="identity.md#a8a76b43d4bb4e3d861ff63e0716f178d">featureId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660692455093531"><a name="p1660692455093531"></a><a name="p1660692455093531"></a>int16 </p>
</td>
</tr>
<tr id="row882116413093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p364936547093531"><a name="p364936547093531"></a><a name="p364936547093531"></a><a href="identity.md#ad34d38c75a24903672bb64f29c1b1132">queueId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105074094093531"><a name="p105074094093531"></a><a name="p105074094093531"></a>MQueueId </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1478877640093531"></a>

## **Field Documentation**<a name="section1578139542093531"></a>

## featureId<a name="a8a76b43d4bb4e3d861ff63e0716f178d"></a>

```
int16 Identity::featureId
```

 **Description:**

[Feature](feature.md)  ID 

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

[Service](service.md)  ID 

