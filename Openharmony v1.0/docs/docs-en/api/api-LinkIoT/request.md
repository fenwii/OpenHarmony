# Request<a name="EN-US_TOPIC_0000001055195068"></a>

## **Overview**<a name="section1195241627191901"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Defines a request. 

You can use this structure to define the request that will be sent to a feature through the asynchronous function of  [IUnknown](iunknown.md).  [Request](request.md), which is data that is packed to send to a feature. If the data is not empty and the length is not 0, the system automatically releases the data. 

## **Summary**<a name="section1338895616191901"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2045070367191901"></a>
<table><thead align="left"><tr id="row606956699191901"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p443258536191901"><a name="p443258536191901"></a><a name="p443258536191901"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p24841288191901"><a name="p24841288191901"></a><a name="p24841288191901"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1070774659191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p957282410191901"><a name="p957282410191901"></a><a name="p957282410191901"></a><a href="request.md#a3449d55dccf5271f417df1450bac652e">msgId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1759527002191901"><a name="p1759527002191901"></a><a name="p1759527002191901"></a>int16 </p>
</td>
</tr>
<tr id="row1742682225191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838968708191901"><a name="p838968708191901"></a><a name="p838968708191901"></a><a href="request.md#a4fd475107279d3cc090d7a383719ab3d">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2052881918191901"><a name="p2052881918191901"></a><a name="p2052881918191901"></a>int16 </p>
</td>
</tr>
<tr id="row1904136455191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1531158573191901"><a name="p1531158573191901"></a><a name="p1531158573191901"></a><a href="request.md#a04b0cc187654cc20a1d036917bcad878">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757258586191901"><a name="p757258586191901"></a><a name="p757258586191901"></a>void * </p>
</td>
</tr>
<tr id="row574708317191901"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1083926258191901"><a name="p1083926258191901"></a><a name="p1083926258191901"></a><a href="request.md#ae26e2e2c6d456140217167550372a5bd">msgValue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p357420516191901"><a name="p357420516191901"></a><a name="p357420516191901"></a>uint32 </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1687280086191901"></a>

## **Field Documentation**<a name="section174245105191901"></a>

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

