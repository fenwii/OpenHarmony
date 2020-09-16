# TaskConfig<a name="ZH-CN_TOPIC_0000001054796539"></a>

## **Overview**<a name="section1792389030090255"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines task configurations for a service. 

This structure defines task configurations for a service, including the task priority, stack size, queue size, task type, and shared task ID. 

## **Summary**<a name="section574723903090255"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1230061886090255"></a>
<table><thead align="left"><tr id="row883721523090255"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1791143567090255"><a name="p1791143567090255"></a><a name="p1791143567090255"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p460996410090255"><a name="p460996410090255"></a><a name="p460996410090255"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row410307518090255"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p747688210090255"><a name="p747688210090255"></a><a name="p747688210090255"></a><a href="TaskConfig.md#a9578c14c10691d7f1cbd8c34210630e7">level</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209657823090255"><a name="p209657823090255"></a><a name="p209657823090255"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row173924934090255"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p851130563090255"><a name="p851130563090255"></a><a name="p851130563090255"></a><a href="TaskConfig.md#abbfc4d996107bc34e0443e1a32d46b6d">priority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1340393325090255"><a name="p1340393325090255"></a><a name="p1340393325090255"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row2120633073090255"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p660746283090255"><a name="p660746283090255"></a><a name="p660746283090255"></a><a href="TaskConfig.md#a4a4fb5ce45d9ea90f42faa6573a03a61">stackSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1498456645090255"><a name="p1498456645090255"></a><a name="p1498456645090255"></a>uint16&nbsp;</p>
</td>
</tr>
<tr id="row2061001614090255"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1612846575090255"><a name="p1612846575090255"></a><a name="p1612846575090255"></a><a href="TaskConfig.md#ae8fd2e3f9bc0937c09e07944cc9a5d30">queueSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388550675090255"><a name="p1388550675090255"></a><a name="p1388550675090255"></a>uint16&nbsp;</p>
</td>
</tr>
<tr id="row85214692090255"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p449890526090255"><a name="p449890526090255"></a><a name="p449890526090255"></a><a href="TaskConfig.md#afab151dbf2f1b02ec14e3e7f83207396">taskFlags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2062989225090255"><a name="p2062989225090255"></a><a name="p2062989225090255"></a>uint8&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1067497280090255"></a>

## **Field Documentation**<a name="section1000707037090255"></a>

## level<a name="a9578c14c10691d7f1cbd8c34210630e7"></a>

```
int16 TaskConfig::level
```

 **Description:**

ID of a multi-service sharing task. For details about the level definition, see  [SpecifyTag](Samgr.md#gae9c7eed07272a46851d61e646b6e86d5). 

## priority<a name="abbfc4d996107bc34e0443e1a32d46b6d"></a>

```
int16 TaskConfig::priority
```

 **Description:**

Task priority. For details about the definition of priority, see  [TaskPriority](Samgr.md#gaef69bbb3353ea484414c3bbaf8ec362b). 

## queueSize<a name="ae8fd2e3f9bc0937c09e07944cc9a5d30"></a>

```
uint16 TaskConfig::queueSize
```

 **Description:**

Size of a task queue 

## stackSize<a name="a4a4fb5ce45d9ea90f42faa6573a03a61"></a>

```
uint16 TaskConfig::stackSize
```

 **Description:**

Size of a task stack 

## taskFlags<a name="afab151dbf2f1b02ec14e3e7f83207396"></a>

```
uint8 TaskConfig::taskFlags
```

 **Description:**

Task type. For details about the taskFlags definition, see  [TaskType](Samgr.md#gab265648f2dbef93878ad8c383712b43a). 

