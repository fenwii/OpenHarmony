# OHOS::Ability<a name="EN-US_TOPIC_0000001054479575"></a>

## **Overview**<a name="section227593243084837"></a>

**Related Modules:**

[AbilityKit](abilitykit.md)

**Description:**

Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or disconnecting from Particle Abilities. 

As the fundamental unit of OpenHarmony applications, abilities are classified into  [Feature](feature.md)  Abilities and Particle Abilities.  [Feature](feature.md)  Abilities support the Page template, and Particle Abilities support the  [Service](service.md)  template. An ability using the Page template is called Page ability for short and that using the  [Service](service.md)  template is called  [Service](service.md)  ability.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section596716020084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table555765185084837"></a>
<table><thead align="left"><tr id="row747119158084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1495269378084837"><a name="p1495269378084837"></a><a name="p1495269378084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p767278114084837"><a name="p767278114084837"></a><a name="p767278114084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row971666805084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p690889432084837"><a name="p690889432084837"></a><a name="p690889432084837"></a><a href="abilitykit.md#ga4d016d42397f33c7710db8544581c757">OnStart</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1788330887084837"><a name="p1788330887084837"></a><a name="p1788330887084837"></a>virtual void </p>
<p id="p145900818084837"><a name="p145900818084837"></a><a name="p145900818084837"></a>Called when this ability is started. You must override this function if you want to perform some initialization operations during ability startup. </p>
</td>
</tr>
<tr id="row1338585118084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112623444084837"><a name="p112623444084837"></a><a name="p112623444084837"></a><a href="abilitykit.md#gae251a38aa7c0aebd7498eef86deab7c1">OnInactive</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386250391084837"><a name="p386250391084837"></a><a name="p386250391084837"></a>virtual void </p>
<p id="p599241652084837"><a name="p599241652084837"></a><a name="p599241652084837"></a>Called when this ability enters the <strong id="b140742035084837"><a name="b140742035084837"></a><a name="b140742035084837"></a>STATE_INACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row671970770084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2031938534084837"><a name="p2031938534084837"></a><a name="p2031938534084837"></a><a href="abilitykit.md#ga3135bfa435f5aaa185f21014a9e86e59">OnActive</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174036397084837"><a name="p174036397084837"></a><a name="p174036397084837"></a>virtual void </p>
<p id="p752864652084837"><a name="p752864652084837"></a><a name="p752864652084837"></a>Called when this ability enters the <strong id="b1803202087084837"><a name="b1803202087084837"></a><a name="b1803202087084837"></a>STATE_ACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row1070790822084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469568606084837"><a name="p469568606084837"></a><a name="p469568606084837"></a><a href="abilitykit.md#ga8185ad517d94ca99a00917d3d1f10620">OnBackground</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p663751035084837"><a name="p663751035084837"></a><a name="p663751035084837"></a>virtual void </p>
<p id="p1310143183084837"><a name="p1310143183084837"></a><a name="p1310143183084837"></a>Called when this ability enters the <strong id="b1529611245084837"><a name="b1529611245084837"></a><a name="b1529611245084837"></a>STATE_BACKGROUND</strong> state. </p>
</td>
</tr>
<tr id="row2094378171084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144839750084837"><a name="p2144839750084837"></a><a name="p2144839750084837"></a><a href="abilitykit.md#gaa4145b360bbe5cdb5d267b17ac12af6a">OnStop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p875820415084837"><a name="p875820415084837"></a><a name="p875820415084837"></a>virtual void </p>
<p id="p1581105768084837"><a name="p1581105768084837"></a><a name="p1581105768084837"></a>Called when this ability enters the <strong id="b860809944084837"><a name="b860809944084837"></a><a name="b860809944084837"></a>STATE_STOP</strong> state. </p>
</td>
</tr>
<tr id="row405658473084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1188587476084837"><a name="p1188587476084837"></a><a name="p1188587476084837"></a><a href="abilitykit.md#ga88e9dbaaa083be9f06adeea27680ef76">OnConnect</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1748393321084837"><a name="p1748393321084837"></a><a name="p1748393321084837"></a>virtual const SvcIdentity * </p>
<p id="p1835864863084837"><a name="p1835864863084837"></a><a name="p1835864863084837"></a>Called when this <a href="service.md">Service</a> ability is connected for the first time. </p>
</td>
</tr>
<tr id="row1313397070084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377842411084837"><a name="p1377842411084837"></a><a name="p1377842411084837"></a><a href="abilitykit.md#gac17d2b81d661134b63ee74b0212eace6">OnDisconnect</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1005398939084837"><a name="p1005398939084837"></a><a name="p1005398939084837"></a>virtual void </p>
<p id="p512605013084837"><a name="p512605013084837"></a><a name="p512605013084837"></a>Called when all abilities connected to this <a href="service.md">Service</a> ability are disconnected. </p>
</td>
</tr>
<tr id="row1920744543084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221374941084837"><a name="p221374941084837"></a><a name="p221374941084837"></a><a href="abilitykit.md#gac83a9af046458b7f6bfaf85071b093f4">SetMainRoute</a> (const std::string &amp;<a href="entry.md">entry</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108282235084837"><a name="p1108282235084837"></a><a name="p1108282235084837"></a>void </p>
<p id="p122714624084837"><a name="p122714624084837"></a><a name="p122714624084837"></a>Sets the main route for this ability. </p>
</td>
</tr>
<tr id="row2121053054084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p266775000084837"><a name="p266775000084837"></a><a name="p266775000084837"></a><a href="abilitykit.md#ga9b734c2ad8ad52f906d676f0c897a4aa">SetUIContent</a> (<a href="ohos-rootview.md">RootView</a> *rootView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p818064272084837"><a name="p818064272084837"></a><a name="p818064272084837"></a>void </p>
<p id="p1617442157084837"><a name="p1617442157084837"></a><a name="p1617442157084837"></a>Sets the UI layout for this ability. You can call <strong id="b1427412066084837"><a name="b1427412066084837"></a><a name="b1427412066084837"></a>GetWindowRootView()</strong> to create a layout and add controls. </p>
</td>
</tr>
<tr id="row1066046894084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1499633864084837"><a name="p1499633864084837"></a><a name="p1499633864084837"></a><a href="abilitykit.md#gab2d208621c7236c3608afb77d8a02966">MsgHandle</a> (uint32_t funcId, IpcIo *request, IpcIo *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694861028084837"><a name="p1694861028084837"></a><a name="p1694861028084837"></a>virtual void </p>
<p id="p457647083084837"><a name="p457647083084837"></a><a name="p457647083084837"></a>Handles a message sent by the client to this <a href="service.md">Service</a> ability. </p>
</td>
</tr>
<tr id="row886288679084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620451875084837"><a name="p1620451875084837"></a><a name="p1620451875084837"></a><a href="abilitykit.md#ga5330624843c776ebe61366540d32eb92">Dump</a> (const std::string &amp;extra)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p555050195084837"><a name="p555050195084837"></a><a name="p555050195084837"></a>virtual void </p>
<p id="p1486207241084837"><a name="p1486207241084837"></a><a name="p1486207241084837"></a>Prints ability information to the console. </p>
</td>
</tr>
<tr id="row816190004084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274908703084837"><a name="p274908703084837"></a><a name="p274908703084837"></a><a href="abilitykit.md#gab11d708d5eaa1eca54828fa88625681a">StartAbility</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980821791084837"><a name="p980821791084837"></a><a name="p980821791084837"></a>int </p>
<p id="p1612307854084837"><a name="p1612307854084837"></a><a name="p1612307854084837"></a>Starts an <a href="ohos-ability.md">Ability</a> based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1580946774084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740363199084837"><a name="p740363199084837"></a><a name="p740363199084837"></a><a href="abilitykit.md#gadc670d5f6df0d485ee3062b70b3ffe99">StopAbility</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2113552500084837"><a name="p2113552500084837"></a><a name="p2113552500084837"></a>int </p>
<p id="p384412316084837"><a name="p384412316084837"></a><a name="p384412316084837"></a>Stops an <a href="ohos-ability.md">Ability</a> based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1579162740084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p572465098084837"><a name="p572465098084837"></a><a name="p572465098084837"></a><a href="abilitykit.md#gac4a36f03c60fcbeca3b47192ccab1d24">TerminateAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1794873218084837"><a name="p1794873218084837"></a><a name="p1794873218084837"></a>int </p>
<p id="p1333508519084837"><a name="p1333508519084837"></a><a name="p1333508519084837"></a>Destroys this <a href="ohos-ability.md">Ability</a>. </p>
</td>
</tr>
<tr id="row1231299292084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1811799733084837"><a name="p1811799733084837"></a><a name="p1811799733084837"></a><a href="abilitykit.md#ga4da460ac085a8da1c665f317fcde2ba1">ConnectAbility</a> (const <a href="want.md">Want</a> &amp;want, const <a href="iabilityconnection.md">IAbilityConnection</a> &amp;conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832510986084837"><a name="p832510986084837"></a><a name="p832510986084837"></a>int </p>
<p id="p1452465091084837"><a name="p1452465091084837"></a><a name="p1452465091084837"></a>Connects to a <a href="service.md">Service</a> ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row276336280084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647846189084837"><a name="p647846189084837"></a><a name="p647846189084837"></a><a href="abilitykit.md#ga1d9023597a9889dbb4015565a10f3470">DisconnectAbility</a> (const <a href="iabilityconnection.md">IAbilityConnection</a> &amp;conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575274384084837"><a name="p1575274384084837"></a><a name="p1575274384084837"></a>int </p>
<p id="p1808052809084837"><a name="p1808052809084837"></a><a name="p1808052809084837"></a>Disconnects from a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
</tbody>
</table>

