# Request<a name="ZH-CN_TOPIC_0000001055358144"></a>

## **Overview**<a name="section852892155093536"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines a request. 

You can use this structure to define the request that will be sent to a feature through the asynchronous function of  [IUnknown](IUnknown.md).  [Request](Request.md), which is data that is packed to send to a feature. If the data is not empty and the length is not 0, the system automatically releases the data. 

## **Summary**<a name="section1271087635093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1450802742093536"></a>
<table><thead align="left"><tr id="row241182586093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1115751746093536"><a name="p1115751746093536"></a><a name="p1115751746093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p111085741093536"><a name="p111085741093536"></a><a name="p111085741093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1720302738093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559654988093536"><a name="p559654988093536"></a><a name="p559654988093536"></a><a href="Request.md#a3449d55dccf5271f417df1450bac652e">msgId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288375354093536"><a name="p288375354093536"></a><a name="p288375354093536"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row148147326093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1518484544093536"><a name="p1518484544093536"></a><a name="p1518484544093536"></a><a href="Request.md#a4fd475107279d3cc090d7a383719ab3d">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440854617093536"><a name="p440854617093536"></a><a name="p440854617093536"></a>int16&nbsp;</p>
</td>
</tr>
<tr id="row1757930789093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2043618734093536"><a name="p2043618734093536"></a><a name="p2043618734093536"></a><a href="Request.md#a04b0cc187654cc20a1d036917bcad878">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p509851672093536"><a name="p509851672093536"></a><a name="p509851672093536"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row16167081093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p362814768093536"><a name="p362814768093536"></a><a name="p362814768093536"></a><a href="Request.md#ae26e2e2c6d456140217167550372a5bd">msgValue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2074965600093536"><a name="p2074965600093536"></a><a name="p2074965600093536"></a>uint32&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2063311219093536"></a>

## **Field Documentation**<a name="section1454784101093536"></a>

## data<a name="a04b0cc187654cc20a1d036917bcad878"></a>

```
void* Request::data
```

 **Description:**

Data content 

## len<a name="a4fd475107279d3cc090d7a383719ab3d"></a>

```
int16 Request::len
```

 **Description:**

Data length 

## msgId<a name="a3449d55dccf5271f417df1450bac652e"></a>

```
int16 Request::msgId
```

 **Description:**

Message ID 

## msgValue<a name="ae26e2e2c6d456140217167550372a5bd"></a>

```
uint32 Request::msgValue
```

 **Description:**

Message value, which is defined by developers 

