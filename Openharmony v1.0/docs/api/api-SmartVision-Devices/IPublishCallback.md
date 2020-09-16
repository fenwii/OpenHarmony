# IPublishCallback<a name="ZH-CN_TOPIC_0000001055078141"></a>

## **Overview**<a name="section1653533395093530"></a>

**Related Modules:**

[Softbus](Softbus.md)

**Description:**

Defines the callbacks for successful and failed service publishing. 

## **Summary**<a name="section1588073722093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1690634323093530"></a>
<table><thead align="left"><tr id="row1737360635093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p882164672093530"><a name="p882164672093530"></a><a name="p882164672093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p528471949093530"><a name="p528471949093530"></a><a name="p528471949093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1772376330093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p968567016093530"><a name="p968567016093530"></a><a name="p968567016093530"></a><a href="Softbus.md#gade0a74f5ae9b16a1fa7f03df5d9fbdf1">onPublishSuccess</a> )(int publishId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073950876093530"><a name="p2073950876093530"></a><a name="p2073950876093530"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row952983023093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p625471377093530"><a name="p625471377093530"></a><a name="p625471377093530"></a><a href="Softbus.md#ga0f84feec4640c176938bbce26b8f25c8">onPublishFail</a> )(int publishId, <a href="Softbus.md#ga6632fcae1db4a3a13370e3fb49e5e620">PublishFailReason</a> reason)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918584622093530"><a name="p1918584622093530"></a><a name="p1918584622093530"></a>void(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

