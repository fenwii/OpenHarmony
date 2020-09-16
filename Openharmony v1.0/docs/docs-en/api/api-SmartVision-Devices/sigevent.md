# sigevent<a name="EN-US_TOPIC_0000001054879580"></a>

## **Overview**<a name="section697691712084843"></a>

**Related Modules:**

[IPC](ipc.md)

**Description:**

Describes asynchronous notifications. 

## **Summary**<a name="section528163887084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1405092078084843"></a>
<table><thead align="left"><tr id="row1827659141084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1112463468084843"><a name="p1112463468084843"></a><a name="p1112463468084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1235038993084843"><a name="p1235038993084843"></a><a name="p1235038993084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1621300315084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p494951084084843"><a name="p494951084084843"></a><a name="p494951084084843"></a><a href="sigevent.md#a757af1e34b87e3f66bbc08c514017a2c">sigev_value</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140877997084843"><a name="p2140877997084843"></a><a name="p2140877997084843"></a>union <a href="sigval.md">sigval</a> </p>
</td>
</tr>
<tr id="row990247626084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1074694251084843"><a name="p1074694251084843"></a><a name="p1074694251084843"></a><a href="sigevent.md#a5c645ec1d12bb46efc3f4097c52b665d">sigev_signo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037849145084843"><a name="p1037849145084843"></a><a name="p1037849145084843"></a>int </p>
</td>
</tr>
<tr id="row306322598084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1780965683084843"><a name="p1780965683084843"></a><a name="p1780965683084843"></a><a href="sigevent.md#aae9a19d879c38e0c4e8a9bf738c5081e">sigev_notify</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1063265224084843"><a name="p1063265224084843"></a><a name="p1063265224084843"></a>int </p>
</td>
</tr>
<tr id="row298021705084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044634858084843"><a name="p1044634858084843"></a><a name="p1044634858084843"></a><a href="sigevent.md#ac3d9f1ee55173d6da3ff2929c7215061">sigev_notify_function</a> )(unionsigval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749711185084843"><a name="p1749711185084843"></a><a name="p1749711185084843"></a>void(* </p>
</td>
</tr>
<tr id="row1218219809084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1956857551084843"><a name="p1956857551084843"></a><a name="p1956857551084843"></a><a href="sigevent.md#a5a687d2092b237d76eb08e2d46a5115f">sigev_notify_attributes</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061388435084843"><a name="p2061388435084843"></a><a name="p2061388435084843"></a>pthread_attr_t * </p>
</td>
</tr>
<tr id="row500430039084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785400515084843"><a name="p785400515084843"></a><a name="p785400515084843"></a><a href="sigevent.md#afefb1d2489fc37345bc4923c99d667c8">char__pad</a> [56-3 *sizeof(long)]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1687288411084843"></a>

## **Field Documentation**<a name="section1457378230084843"></a>

## char\_\_pad<a name="afefb1d2489fc37345bc4923c99d667c8"></a>

```
sigevent::char__pad[56-3 *sizeof(long)]
```

 **Description:**

A reserved field 

## sigev\_notify<a name="aae9a19d879c38e0c4e8a9bf738c5081e"></a>

```
int sigevent::sigev_notify
```

 **Description:**

Notification method, which can be set to  [SIGEV\_SIGNAL](ipc.md#ga06d5881eeb84e6ac35f5b801c380dbb6),  [SIGEV\_NONE](ipc.md#gaced9a66610d9d61756999ce4f103740e), or  [SIGEV\_THREAD](ipc.md#ga29ccb6a17fa90a1357b478f62af7fca0) 

## sigev\_notify\_attributes<a name="a5a687d2092b237d76eb08e2d46a5115f"></a>

```
pthread_attr_t* sigevent::sigev_notify_attributes
```

 **Description:**

Attributes for notification thread 

## sigev\_notify\_function<a name="ac3d9f1ee55173d6da3ff2929c7215061"></a>

```
void(* sigevent::sigev_notify_function) (unionsigval)
```

 **Description:**

Function used for thread notification 

## sigev\_signo<a name="a5c645ec1d12bb46efc3f4097c52b665d"></a>

```
int sigevent::sigev_signo
```

 **Description:**

Notification signal 

## sigev\_value<a name="a757af1e34b87e3f66bbc08c514017a2c"></a>

```
union [sigval](sigval.md) sigevent::sigev_value
```

 **Description:**

Data passed with notification 

