# OHOS::AbilityContext<a name="EN-US_TOPIC_0000001054879544"></a>

## **Overview**<a name="section98713746093532"></a>

**Related Modules:**

[AbilityKit](abilitykit.md)

**Description:**

Provides functions for starting and stopping an ability. 

The  [Ability](ohos-ability.md)  and  [AbilitySlice](ohos-abilityslice.md)  classes are inherited from the  **[AbilityContext](ohos-abilitycontext.md)**  class for you to call functions in this class for application development.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1965639043093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table2140727025093532"></a>
<table><thead align="left"><tr id="row1951624956093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2047882633093532"><a name="p2047882633093532"></a><a name="p2047882633093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1766728167093532"><a name="p1766728167093532"></a><a name="p1766728167093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row539783697093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1699247331093532"><a name="p1699247331093532"></a><a name="p1699247331093532"></a><a href="abilitykit.md#gab11d708d5eaa1eca54828fa88625681a">StartAbility</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167527852093532"><a name="p1167527852093532"></a><a name="p1167527852093532"></a>int </p>
<p id="p1397772020093532"><a name="p1397772020093532"></a><a name="p1397772020093532"></a>Starts an <a href="ohos-ability.md">Ability</a> based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row22741312093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509873809093532"><a name="p1509873809093532"></a><a name="p1509873809093532"></a><a href="abilitykit.md#gadc670d5f6df0d485ee3062b70b3ffe99">StopAbility</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1869656781093532"><a name="p1869656781093532"></a><a name="p1869656781093532"></a>int </p>
<p id="p1973588908093532"><a name="p1973588908093532"></a><a name="p1973588908093532"></a>Stops an <a href="ohos-ability.md">Ability</a> based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row467580899093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1368693110093532"><a name="p1368693110093532"></a><a name="p1368693110093532"></a><a href="abilitykit.md#gac4a36f03c60fcbeca3b47192ccab1d24">TerminateAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1636616406093532"><a name="p1636616406093532"></a><a name="p1636616406093532"></a>int </p>
<p id="p1227956947093532"><a name="p1227956947093532"></a><a name="p1227956947093532"></a>Destroys this <a href="ohos-ability.md">Ability</a>. </p>
</td>
</tr>
<tr id="row1310567668093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p151092082093532"><a name="p151092082093532"></a><a name="p151092082093532"></a><a href="abilitykit.md#ga4da460ac085a8da1c665f317fcde2ba1">ConnectAbility</a> (const <a href="want.md">Want</a> &amp;want, const <a href="iabilityconnection.md">IAbilityConnection</a> &amp;conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p552703846093532"><a name="p552703846093532"></a><a name="p552703846093532"></a>int </p>
<p id="p241097262093532"><a name="p241097262093532"></a><a name="p241097262093532"></a>Connects to a <a href="service.md">Service</a> ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1350989020093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2124436470093532"><a name="p2124436470093532"></a><a name="p2124436470093532"></a><a href="abilitykit.md#ga1d9023597a9889dbb4015565a10f3470">DisconnectAbility</a> (const <a href="iabilityconnection.md">IAbilityConnection</a> &amp;conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1905236657093532"><a name="p1905236657093532"></a><a name="p1905236657093532"></a>int </p>
<p id="p1797129850093532"><a name="p1797129850093532"></a><a name="p1797129850093532"></a>Disconnects from a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
</tbody>
</table>

