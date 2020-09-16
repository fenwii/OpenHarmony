# Response<a name="ZH-CN_TOPIC_0000001055355046"></a>

## **Overview**<a name="section1679533437191901"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines a response. 

This structure is used to send a response after the message processing function of a service or feature processes a request. If the data is not empty and the length is not 0, the system automatically releases the data. 

## **Summary**<a name="section755864192191901"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table199745053191901"></a>
<table><thead align="left"><tr id="row1601124212191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1724101383191901"><a name="p1724101383191901"></a><a name="p1724101383191901"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p321092216191901"><a name="p321092216191901"></a><a name="p321092216191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1551085938191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p565777687191901"><a name="p565777687191901"></a><a name="p565777687191901"></a><a href="Response.md#a771bd5a2dd1f2d8be9928af7c0fe37a0">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284300732191901"><a name="p284300732191901"></a><a name="p284300732191901"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row524105329191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871742611191901"><a name="p871742611191901"></a><a name="p871742611191901"></a><a href="Response.md#a7a20e7a28a2be1427111d8f03828bb7e">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458648403191901"><a name="p1458648403191901"></a><a name="p1458648403191901"></a>int16&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1634049126191901"></a>

## **Field Documentation**<a name="section877253065191901"></a>

## data<a name="a771bd5a2dd1f2d8be9928af7c0fe37a0"></a>

```
void* Response::data
```

 **Description:**

Data content 

## len<a name="a7a20e7a28a2be1427111d8f03828bb7e"></a>

```
int16 Response::len
```

 **Description:**

Data length 

