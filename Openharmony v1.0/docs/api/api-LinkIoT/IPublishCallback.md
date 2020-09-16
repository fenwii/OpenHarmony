# IPublishCallback<a name="ZH-CN_TOPIC_0000001054915093"></a>

## **Overview**<a name="section1305755903191859"></a>

**Related Modules:**

[Softbus](Softbus.md)

**Description:**

Defines the callbacks for successful and failed service publishing. 

## **Summary**<a name="section1445080536191859"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2105675329191859"></a>
<table><thead align="left"><tr id="row76584977191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p524981378191859"><a name="p524981378191859"></a><a name="p524981378191859"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1947577598191859"><a name="p1947577598191859"></a><a name="p1947577598191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1033040761191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1576250764191859"><a name="p1576250764191859"></a><a name="p1576250764191859"></a><a href="Softbus.md#gade0a74f5ae9b16a1fa7f03df5d9fbdf1">onPublishSuccess</a> )(int publishId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313521954191859"><a name="p1313521954191859"></a><a name="p1313521954191859"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row1675598662191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1148398614191859"><a name="p1148398614191859"></a><a name="p1148398614191859"></a><a href="Softbus.md#ga0f84feec4640c176938bbce26b8f25c8">onPublishFail</a> )(int publishId, <a href="Softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620">PublishFailReason</a> reason)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1272313502191859"><a name="p1272313502191859"></a><a name="p1272313502191859"></a>void(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

