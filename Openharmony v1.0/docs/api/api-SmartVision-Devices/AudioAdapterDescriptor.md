# AudioAdapterDescriptor<a name="ZH-CN_TOPIC_0000001055518080"></a>

## **Overview**<a name="section1904948640093529"></a>

**Related Modules:**

[Audio](Audio.md)

**Description:**

Defines the audio adapter descriptor. 

An audio adapter is a set of port drivers for a sound card, including the output and input ports. One port corresponds to multiple pins, and each pin belongs to a physical component \(such as a speaker or a wired headset\). 

## **Summary**<a name="section680143796093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1658179936093529"></a>
<table><thead align="left"><tr id="row606276817093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1594580551093529"><a name="p1594580551093529"></a><a name="p1594580551093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1858548344093529"><a name="p1858548344093529"></a><a name="p1858548344093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row435125776093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2028291411093529"><a name="p2028291411093529"></a><a name="p2028291411093529"></a><a href="Audio.md#gadbe46bc7d9b4c20c409e30942ad794cf">adapterName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073059048093529"><a name="p2073059048093529"></a><a name="p2073059048093529"></a>const char *&nbsp;</p>
</td>
</tr>
<tr id="row1988902656093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1276541088093529"><a name="p1276541088093529"></a><a name="p1276541088093529"></a><a href="Audio.md#ga2bef8f9b5ea3c1e30639fcb3ec8dd717">portNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91333119093529"><a name="p91333119093529"></a><a name="p91333119093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row148788291093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315421344093529"><a name="p315421344093529"></a><a name="p315421344093529"></a><a href="Audio.md#ga64d0c55b881fb0a3bc15b2fecea86f24">ports</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238762385093529"><a name="p238762385093529"></a><a name="p238762385093529"></a>struct <a href="AudioPort.md">AudioPort</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

