# OsalThreadParam<a name="ZH-CN_TOPIC_0000001054479579"></a>

## **Overview**<a name="section395146536093532"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Describes thread parameters. 

## **Summary**<a name="section32478110093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1289607295093532"></a>
<table><thead align="left"><tr id="row1115112182093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1420515964093532"><a name="p1420515964093532"></a><a name="p1420515964093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p395519267093532"><a name="p395519267093532"></a><a name="p395519267093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row633502102093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p495845124093532"><a name="p495845124093532"></a><a name="p495845124093532"></a><a href="OsalThreadParam.md#a6bd1010a71ee937fa5fdbcbf11e733ab">name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291972232093532"><a name="p291972232093532"></a><a name="p291972232093532"></a>char *&nbsp;</p>
</td>
</tr>
<tr id="row1641853829093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773919582093532"><a name="p773919582093532"></a><a name="p773919582093532"></a><a href="OsalThreadParam.md#a658a540a5c27b8bbe7feb8f143364b18">stackSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p691256000093532"><a name="p691256000093532"></a><a name="p691256000093532"></a>size_t&nbsp;</p>
</td>
</tr>
<tr id="row198251916093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1196053700093532"><a name="p1196053700093532"></a><a name="p1196053700093532"></a><a href="OsalThreadParam.md#a11ba2334842664dce682fef5cadfbf30">priority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p500318598093532"><a name="p500318598093532"></a><a name="p500318598093532"></a><a href="OSAL.md#gab8c099a9c39fdde73c74b3f7367be5d0">OSAL_THREAD_PRIORITY</a>&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section936760503093532"></a>

## **Field Documentation**<a name="section1468905692093532"></a>

## name<a name="a6bd1010a71ee937fa5fdbcbf11e733ab"></a>

```
char* OsalThreadParam::name
```

 **Description:**

Thread name 

## priority<a name="a11ba2334842664dce682fef5cadfbf30"></a>

```
[OSAL_THREAD_PRIORITY](OSAL.md#gab8c099a9c39fdde73c74b3f7367be5d0) OsalThreadParam::priority
```

 **Description:**

Thread priority 

## stackSize<a name="a658a540a5c27b8bbe7feb8f143364b18"></a>

```
size_t OsalThreadParam::stackSize
```

 **Description:**

Stack size of a thread 

