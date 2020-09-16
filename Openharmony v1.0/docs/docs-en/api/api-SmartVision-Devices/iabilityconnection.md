# IAbilityConnection<a name="EN-US_TOPIC_0000001054479567"></a>

## **Overview**<a name="section1135888675093531"></a>

**Related Modules:**

[AbilityKit](abilitykit.md)

**Description:**

Provides callbacks to be invoked when a remote  [Service](service.md)  ability is connected or disconnected. 

## **Summary**<a name="section495081729093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table668467472093531"></a>
<table><thead align="left"><tr id="row1519684370093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p447945243093531"><a name="p447945243093531"></a><a name="p447945243093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p69779550093531"><a name="p69779550093531"></a><a name="p69779550093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1852392276093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636655364093531"><a name="p1636655364093531"></a><a name="p1636655364093531"></a><a href="abilitykit.md#ga3b9bfacbcf1564c83cffbfff7889998a">OnAbilityConnectDone</a> )(<a href="elementname.md">ElementName</a> *elementName, SvcIdentity *serviceSid, int resultCode, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p384130105093531"><a name="p384130105093531"></a><a name="p384130105093531"></a>void(* </p>
<p id="p998948282093531"><a name="p998948282093531"></a><a name="p998948282093531"></a>Called when a client is connected to a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
<tr id="row1262690490093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1055921306093531"><a name="p1055921306093531"></a><a name="p1055921306093531"></a><a href="abilitykit.md#gaba7cf0abb517890ef1a3949e398aaf1d">OnAbilityDisconnectDone</a> )(<a href="elementname.md">ElementName</a> *elementName, int resultCode, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594567871093531"><a name="p594567871093531"></a><a name="p594567871093531"></a>void(* </p>
<p id="p1012132056093531"><a name="p1012132056093531"></a><a name="p1012132056093531"></a>Called after all connections to a <a href="service.md">Service</a> ability are disconnected. </p>
</td>
</tr>
</tbody>
</table>

