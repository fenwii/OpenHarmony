# AbilitySlice<a name="ZH-CN_TOPIC_0000001054652843"></a>

## **Overview**<a name="section1996298409113032"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)

**Description:**

Provides ability slice-related functions, including ability slice lifecycle callbacks and functions for connecting to or disconnecting from ability slices. 

**[AbilitySlice](AbilitySlice.md)**  instances, which are specific to FAs \(abilities using the Page template\), are used to present different screens on an application's user interface. An FA can have multiple ability slices.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1991055886113032"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gad3ffda54b710b0b86e54bd6c13efae98">OnStart</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when this ability slice is started. You must override this function if you want to perform some initialization operations during ability slice startup. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gae050b00aa885765bb6808374be772615">OnInactive</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when this ability slice enters the <strong>STATE_INACTIVE</strong> state. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#ga1a588eb6635e42979e18ac8013f9ea61">OnActive</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when this ability slice enters the <strong>STATE_ACTIVE</strong> state. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#ga19217479f8468b525460be156827a524">OnBackground</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when this ability slice enters the <strong>STATE_BACKGROUND</strong> state. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#ga4e1556b780a1271e61328e659fc30eb9">OnStop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when this ability slice enters the <strong>STATE_STOP</strong> state. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gab2ec8b885edd0d5818b4c60541c1875f">Present</a> (<a href="AbilitySlice.md">AbilitySlice</a> &amp;abilitySlice, const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Presents another ability slice, which can be an ability slice that is not started or an existing ability slice in the host ability. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gaf424e47c7980ff92093c6b7b75888639">Terminate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Destroys this ability slice. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#ga050a81cda49edb471594447f8f4cdaac">SetUIContent</a> (<a href="RootView.md">RootView</a> *rootView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the UI layout for the host ability of this ability slice. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gab11d708d5eaa1eca54828fa88625681a">StartAbility</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Starts an <a href="OHOS-Ability.md">Ability</a> based on the specified <a href="Want.md">Want</a> information. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gadc670d5f6df0d485ee3062b70b3ffe99">StopAbility</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Stops an <a href="OHOS-Ability.md">Ability</a> based on the specified <a href="Want.md">Want</a> information. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#gac4a36f03c60fcbeca3b47192ccab1d24">TerminateAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Destroys this <a href="OHOS-Ability.md">Ability</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#ga4da460ac085a8da1c665f317fcde2ba1">ConnectAbility</a> (const <a href="Want.md">Want</a> &amp;want, const <a href="IAbilityConnection.md">IAbilityConnection</a> &amp;conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Connects to a <a href="Service.md">Service</a> ability based on the specified <a href="Want.md">Want</a> information. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="AbilityKit.md#ga1d9023597a9889dbb4015565a10f3470">DisconnectAbility</a> (const <a href="IAbilityConnection.md">IAbilityConnection</a> &amp;conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Disconnects from a <a href="Service.md">Service</a> ability. </p>
</td>
</tr>
</tbody>
</table>

