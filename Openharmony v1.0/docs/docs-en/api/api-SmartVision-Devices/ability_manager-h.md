# ability\_manager.h<a name="EN-US_TOPIC_0000001055518048"></a>

## **Overview**<a name="section513584010093524"></a>

**Related Modules:**

[AbilityKit](abilitykit.md)

**Description:**

Declares ability-related functions, including functions for starting, stopping, connecting to, and disconnecting from an ability, registering a callback, and unregistering a callback. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1287042840093524"></a>

## Functions<a name="func-members"></a>

<a name="table97416767093524"></a>
<table><thead align="left"><tr id="row1228537297093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p827942874093524"><a name="p827942874093524"></a><a name="p827942874093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p381870644093524"><a name="p381870644093524"></a><a name="p381870644093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1729282724093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1938698321093524"><a name="p1938698321093524"></a><a name="p1938698321093524"></a><a href="abilitykit.md#gae79800c4077afdc2851d5a74d8964111">StartAbility</a> (const <a href="want.md">Want</a> *want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p795271234093524"><a name="p795271234093524"></a><a name="p795271234093524"></a>int </p>
<p id="p951476652093524"><a name="p951476652093524"></a><a name="p951476652093524"></a>Starts an ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row772489552093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p289381149093524"><a name="p289381149093524"></a><a name="p289381149093524"></a><a href="abilitykit.md#gaba99bbd4ff6da4fb072338f5ce95e6ae">StopAbility</a> (const <a href="want.md">Want</a> *want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580152575093524"><a name="p580152575093524"></a><a name="p580152575093524"></a>int </p>
<p id="p1598594007093524"><a name="p1598594007093524"></a><a name="p1598594007093524"></a>Stops an ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row952212808093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p446844864093524"><a name="p446844864093524"></a><a name="p446844864093524"></a><a href="abilitykit.md#gaae6c2bbb6ab0df92e39c1daad2bd901f">ConnectAbility</a> (const <a href="want.md">Want</a> *want, const <a href="iabilityconnection.md">IAbilityConnection</a> *conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775343770093524"><a name="p775343770093524"></a><a name="p775343770093524"></a>int </p>
<p id="p1256423755093524"><a name="p1256423755093524"></a><a name="p1256423755093524"></a>Connects to a <a href="service.md">Service</a> ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row2079329424093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p991918151093524"><a name="p991918151093524"></a><a name="p991918151093524"></a><a href="abilitykit.md#ga2769216a4c2654d3297a2fdb4011ea7a">DisconnectAbility</a> (const <a href="iabilityconnection.md">IAbilityConnection</a> *conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1882600029093524"><a name="p1882600029093524"></a><a name="p1882600029093524"></a>int </p>
<p id="p139240257093524"><a name="p139240257093524"></a><a name="p139240257093524"></a>Disconnects from a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
</tbody>
</table>

