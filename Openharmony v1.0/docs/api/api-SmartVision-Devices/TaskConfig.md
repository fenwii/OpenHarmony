# TaskConfig<a name="ZH-CN_TOPIC_0000001055198170"></a>

## **Overview**<a name="section1014853173084842"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines task configurations for a service. 

This structure defines task configurations for a service, including the task priority, stack size, queue size, task type, and shared task ID. 

## **Summary**<a name="section481811103084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1509619256084842"></a>
<table><thead align="left"><tr id="row456962000084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p852867492084842"><a name="p852867492084842"></a><a name="p852867492084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p764079300084842"><a name="p764079300084842"></a><a name="p764079300084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row798630723084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p203090809084842"><a name="p203090809084842"></a><a name="p203090809084842"></a><a href="TaskConfig.md#a9578c14c10691d7f1cbd8c34210630e7">level</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647595442084842"><a name="p647595442084842"></a><a name="p647595442084842"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row755076195084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637323488084842"><a name="p637323488084842"></a><a name="p637323488084842"></a><a href="TaskConfig.md#abbfc4d996107bc34e0443e1a32d46b6d">priority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485766601084842"><a name="p1485766601084842"></a><a name="p1485766601084842"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row1713563028084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725483622084842"><a name="p1725483622084842"></a><a name="p1725483622084842"></a><a href="TaskConfig.md#a4a4fb5ce45d9ea90f42faa6573a03a61">stackSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929844346084842"><a name="p929844346084842"></a><a name="p929844346084842"></a>uint16&nbsp;</p>
</td>
</tr>
<tr id="row1011965447084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1192900850084842"><a name="p1192900850084842"></a><a name="p1192900850084842"></a><a href="TaskConfig.md#ae8fd2e3f9bc0937c09e07944cc9a5d30">queueSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1814048466084842"><a name="p1814048466084842"></a><a name="p1814048466084842"></a>uint16&nbsp;</p>
</td>
</tr>
<tr id="row1683978059084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p696887827084842"><a name="p696887827084842"></a><a name="p696887827084842"></a><a href="TaskConfig.md#afab151dbf2f1b02ec14e3e7f83207396">taskFlags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p612716008084842"><a name="p612716008084842"></a><a name="p612716008084842"></a>uint8&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1835853447084842"></a>

## **Field Documentation**<a name="section1873793850084842"></a>

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

