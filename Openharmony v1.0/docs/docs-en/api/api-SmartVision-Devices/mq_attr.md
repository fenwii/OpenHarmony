# mq\_attr<a name="EN-US_TOPIC_0000001054918201"></a>

## **Overview**<a name="section359813737084843"></a>

**Related Modules:**

[IPC](ipc.md)

**Description:**

Describes message queue attributes. 

## **Summary**<a name="section1006406431084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2147109705084843"></a>
<table><thead align="left"><tr id="row1480201756084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p183165188084843"><a name="p183165188084843"></a><a name="p183165188084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p330320798084843"><a name="p330320798084843"></a><a name="p330320798084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1429242645084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898355248084843"><a name="p1898355248084843"></a><a name="p1898355248084843"></a><a href="mq_attr.md#a19c05fa88c6d1126120d800647ddb0dd">mq_flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343016345084843"><a name="p343016345084843"></a><a name="p343016345084843"></a>long </p>
</td>
</tr>
<tr id="row228694236084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1610182639084843"><a name="p1610182639084843"></a><a name="p1610182639084843"></a><a href="mq_attr.md#aa535e1fa6c07c1d189e720ba15f9af08">mq_maxmsg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725864122084843"><a name="p1725864122084843"></a><a name="p1725864122084843"></a>long </p>
</td>
</tr>
<tr id="row1472391295084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1462604437084843"><a name="p1462604437084843"></a><a name="p1462604437084843"></a><a href="mq_attr.md#ae975d1d907081c1e53b079c981c32209">mq_msgsize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310877323084843"><a name="p1310877323084843"></a><a name="p1310877323084843"></a>long </p>
</td>
</tr>
<tr id="row41055012084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p767017531084843"><a name="p767017531084843"></a><a name="p767017531084843"></a><a href="mq_attr.md#a08cfd508cef817ba351c1af8d9af50f5">mq_curmsgs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1262220326084843"><a name="p1262220326084843"></a><a name="p1262220326084843"></a>long </p>
</td>
</tr>
<tr id="row261664943084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p824872703084843"><a name="p824872703084843"></a><a name="p824872703084843"></a><a href="mq_attr.md#a65ed70c4a33bc709487bfa801ab21964">__unused</a> [4]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1054574888084843"><a name="p1054574888084843"></a><a name="p1054574888084843"></a>long </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section763157884084843"></a>

## **Field Documentation**<a name="section946328182084843"></a>

## \_\_unused<a name="a65ed70c4a33bc709487bfa801ab21964"></a>

```
long mq_attr::__unused[4]
```

 **Description:**

A reserved field 

## mq\_curmsgs<a name="a08cfd508cef817ba351c1af8d9af50f5"></a>

```
long mq_attr::mq_curmsgs
```

 **Description:**

Number of messages currently queued 

## mq\_flags<a name="a19c05fa88c6d1126120d800647ddb0dd"></a>

```
long mq_attr::mq_flags
```

 **Description:**

Message queue flags: 0 or  **O\_NONBLOCK** 

## mq\_maxmsg<a name="aa535e1fa6c07c1d189e720ba15f9af08"></a>

```
long mq_attr::mq_maxmsg
```

 **Description:**

Maximum number of messages on queue 

## mq\_msgsize<a name="ae975d1d907081c1e53b079c981c32209"></a>

```
long mq_attr::mq_msgsize
```

 **Description:**

Maximum length of a message 

