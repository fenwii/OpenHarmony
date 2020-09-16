# Response<a name="ZH-CN_TOPIC_0000001055078175"></a>

## **Overview**<a name="section812021307093536"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines a response. 

This structure is used to send a response after the message processing function of a service or feature processes a request. If the data is not empty and the length is not 0, the system automatically releases the data. 

## **Summary**<a name="section362920928093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table138705109093536"></a>
<table><thead align="left"><tr id="row1324730489093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1957193235093536"><a name="p1957193235093536"></a><a name="p1957193235093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p78978382093536"><a name="p78978382093536"></a><a name="p78978382093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1713029392093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709523019093536"><a name="p709523019093536"></a><a name="p709523019093536"></a><a href="Response.md#a771bd5a2dd1f2d8be9928af7c0fe37a0">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p766737551093536"><a name="p766737551093536"></a><a name="p766737551093536"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row264797450093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2027538195093536"><a name="p2027538195093536"></a><a name="p2027538195093536"></a><a href="Response.md#a7a20e7a28a2be1427111d8f03828bb7e">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027526177093536"><a name="p1027526177093536"></a><a name="p1027526177093536"></a>int16&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section291141284093536"></a>

## **Field Documentation**<a name="section1688759805093536"></a>

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

