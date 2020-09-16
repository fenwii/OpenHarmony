# OHOS::AbilitySlice<a name="ZH-CN_TOPIC_0000001055078151"></a>

## **Overview**<a name="section285090019084837"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)

**Description:**

Provides ability slice-related functions, including ability slice lifecycle callbacks and functions for connecting to or disconnecting from ability slices. 

**[AbilitySlice](OHOS-AbilitySlice.md)**  instances, which are specific to  [Feature](Feature.md)  Abilities \(abilities using the Page template\), are used to present different screens on an application's user interface. A  [Feature](Feature.md) [Ability](OHOS-Ability.md)  can have multiple ability slices.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1634425776084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1924804839084837"></a>
<table><thead align="left"><tr id="row1663949583084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1400812627084837"><a name="p1400812627084837"></a><a name="p1400812627084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p37910540084837"><a name="p37910540084837"></a><a name="p37910540084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1798588639084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440301970084837"><a name="p440301970084837"></a><a name="p440301970084837"></a><a href="AbilityKit.md#gad3ffda54b710b0b86e54bd6c13efae98">OnStart</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p239140390084837"><a name="p239140390084837"></a><a name="p239140390084837"></a>virtual void&nbsp;</p>
<p id="p1082765598084837"><a name="p1082765598084837"></a><a name="p1082765598084837"></a>Called when this ability slice is started. You must override this function if you want to perform some initialization operations during ability slice startup. </p>
</td>
</tr>
<tr id="row785531619084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1167683978084837"><a name="p1167683978084837"></a><a name="p1167683978084837"></a><a href="AbilityKit.md#gae050b00aa885765bb6808374be772615">OnInactive</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p26951404084837"><a name="p26951404084837"></a><a name="p26951404084837"></a>virtual void&nbsp;</p>
<p id="p1926189375084837"><a name="p1926189375084837"></a><a name="p1926189375084837"></a>Called when this ability slice enters the <strong id="b535724708084837"><a name="b535724708084837"></a><a name="b535724708084837"></a>STATE_INACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row2041052019084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1128450966084837"><a name="p1128450966084837"></a><a name="p1128450966084837"></a><a href="AbilityKit.md#ga1a588eb6635e42979e18ac8013f9ea61">OnActive</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804268137084837"><a name="p804268137084837"></a><a name="p804268137084837"></a>virtual void&nbsp;</p>
<p id="p488575188084837"><a name="p488575188084837"></a><a name="p488575188084837"></a>Called when this ability slice enters the <strong id="b384631799084837"><a name="b384631799084837"></a><a name="b384631799084837"></a>STATE_ACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row1397836391084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1112691662084837"><a name="p1112691662084837"></a><a name="p1112691662084837"></a><a href="AbilityKit.md#ga19217479f8468b525460be156827a524">OnBackground</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069355139084837"><a name="p2069355139084837"></a><a name="p2069355139084837"></a>virtual void&nbsp;</p>
<p id="p714500478084837"><a name="p714500478084837"></a><a name="p714500478084837"></a>Called when this ability slice enters the <strong id="b363089575084837"><a name="b363089575084837"></a><a name="b363089575084837"></a>STATE_BACKGROUND</strong> state. </p>
</td>
</tr>
<tr id="row839857209084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571662574084837"><a name="p1571662574084837"></a><a name="p1571662574084837"></a><a href="AbilityKit.md#ga4e1556b780a1271e61328e659fc30eb9">OnStop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1668413999084837"><a name="p1668413999084837"></a><a name="p1668413999084837"></a>virtual void&nbsp;</p>
<p id="p1122191287084837"><a name="p1122191287084837"></a><a name="p1122191287084837"></a>Called when this ability slice enters the <strong id="b1611579884084837"><a name="b1611579884084837"></a><a name="b1611579884084837"></a>STATE_STOP</strong> state. </p>
</td>
</tr>
<tr id="row1810241435084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730939495084837"><a name="p730939495084837"></a><a name="p730939495084837"></a><a href="AbilityKit.md#gab2ec8b885edd0d5818b4c60541c1875f">Present</a> (<a href="OHOS-AbilitySlice.md">AbilitySlice</a> &amp;abilitySlice, const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403061833084837"><a name="p403061833084837"></a><a name="p403061833084837"></a>void&nbsp;</p>
<p id="p521673685084837"><a name="p521673685084837"></a><a name="p521673685084837"></a>Presents another ability slice, which can be an ability slice that is not started or an existing ability slice in the host ability. </p>
</td>
</tr>
<tr id="row1629409147084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895415330084837"><a name="p895415330084837"></a><a name="p895415330084837"></a><a href="AbilityKit.md#gaf424e47c7980ff92093c6b7b75888639">Terminate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1855681230084837"><a name="p1855681230084837"></a><a name="p1855681230084837"></a>void&nbsp;</p>
<p id="p907666617084837"><a name="p907666617084837"></a><a name="p907666617084837"></a>Destroys this ability slice. </p>
</td>
</tr>
<tr id="row2139516602084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836873660084837"><a name="p1836873660084837"></a><a name="p1836873660084837"></a><a href="AbilityKit.md#ga050a81cda49edb471594447f8f4cdaac">SetUIContent</a> (<a href="OHOS-RootView.md">RootView</a> *rootView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p192529349084837"><a name="p192529349084837"></a><a name="p192529349084837"></a>void&nbsp;</p>
<p id="p794702795084837"><a name="p794702795084837"></a><a name="p794702795084837"></a>Sets the UI layout for the host ability of this ability slice. </p>
</td>
</tr>
<tr id="row1604649440084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1949670601084837"><a name="p1949670601084837"></a><a name="p1949670601084837"></a><a href="AbilityKit.md#gab11d708d5eaa1eca54828fa88625681a">StartAbility</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1945616858084837"><a name="p1945616858084837"></a><a name="p1945616858084837"></a>int&nbsp;</p>
<p id="p1003237868084837"><a name="p1003237868084837"></a><a name="p1003237868084837"></a>Starts an <a href="OHOS-Ability.md">Ability</a> based on the specified <a href="Want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row245696537084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p200603645084837"><a name="p200603645084837"></a><a name="p200603645084837"></a><a href="AbilityKit.md#gadc670d5f6df0d485ee3062b70b3ffe99">StopAbility</a> (const <a href="Want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p677624737084837"><a name="p677624737084837"></a><a name="p677624737084837"></a>int&nbsp;</p>
<p id="p141337593084837"><a name="p141337593084837"></a><a name="p141337593084837"></a>Stops an <a href="OHOS-Ability.md">Ability</a> based on the specified <a href="Want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row765954399084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1947372190084837"><a name="p1947372190084837"></a><a name="p1947372190084837"></a><a href="AbilityKit.md#gac4a36f03c60fcbeca3b47192ccab1d24">TerminateAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746424397084837"><a name="p746424397084837"></a><a name="p746424397084837"></a>int&nbsp;</p>
<p id="p516007695084837"><a name="p516007695084837"></a><a name="p516007695084837"></a>Destroys this <a href="OHOS-Ability.md">Ability</a>. </p>
</td>
</tr>
<tr id="row2094164944084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1287441996084837"><a name="p1287441996084837"></a><a name="p1287441996084837"></a><a href="AbilityKit.md#ga4da460ac085a8da1c665f317fcde2ba1">ConnectAbility</a> (const <a href="Want.md">Want</a> &amp;want, const <a href="IAbilityConnection.md">IAbilityConnection</a> &amp;conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1468268496084837"><a name="p1468268496084837"></a><a name="p1468268496084837"></a>int&nbsp;</p>
<p id="p229887534084837"><a name="p229887534084837"></a><a name="p229887534084837"></a>Connects to a <a href="Service.md">Service</a> ability based on the specified <a href="Want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1366261528084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p864633735084837"><a name="p864633735084837"></a><a name="p864633735084837"></a><a href="AbilityKit.md#ga1d9023597a9889dbb4015565a10f3470">DisconnectAbility</a> (const <a href="IAbilityConnection.md">IAbilityConnection</a> &amp;conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1585533684084837"><a name="p1585533684084837"></a><a name="p1585533684084837"></a>int&nbsp;</p>
<p id="p1418375839084837"><a name="p1418375839084837"></a><a name="p1418375839084837"></a>Disconnects from a <a href="Service.md">Service</a> ability. </p>
</td>
</tr>
</tbody>
</table>

