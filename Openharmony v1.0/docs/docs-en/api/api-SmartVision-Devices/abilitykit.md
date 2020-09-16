# AbilityKit<a name="EN-US_TOPIC_0000001054598111"></a>

## **Overview**<a name="section2016236233084826"></a>

Provides ability-related functions, including ability lifecycle callbacks and functions for connecting to or disconnecting from Particle Abilities. 

Abilities are classified into  [Feature](feature.md)  Abilities and Particle Abilities.  [Feature](feature.md)  Abilities support the Page template, and Particle Abilities support the  [Service](service.md)  template. An ability using the Page template is called a Page ability for short and that using the  [Service](service.md)  template is called a  [Service](service.md)  ability.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1910925661084826"></a>

## Files<a name="files"></a>

<a name="table886926561084826"></a>
<table><thead align="left"><tr id="row682506385084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p437511755084826"><a name="p437511755084826"></a><a name="p437511755084826"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1811701959084826"><a name="p1811701959084826"></a><a name="p1811701959084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row695788423084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p149520577084826"><a name="p149520577084826"></a><a name="p149520577084826"></a><a href="ability-h.md">ability.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057425132084826"><a name="p1057425132084826"></a><a name="p1057425132084826"></a>Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or disconnecting from Particle Abilities. </p>
</td>
</tr>
<tr id="row78293266084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p459262142084826"><a name="p459262142084826"></a><a name="p459262142084826"></a><a href="ability_connection-h.md">ability_connection.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1107926653084826"><a name="p1107926653084826"></a><a name="p1107926653084826"></a>Declares callbacks to be invoked when a remote <a href="service.md">Service</a> ability is connected or disconnected. </p>
</td>
</tr>
<tr id="row906150925084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p86524253084826"><a name="p86524253084826"></a><a name="p86524253084826"></a><a href="ability_context-h.md">ability_context.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283386691084826"><a name="p1283386691084826"></a><a name="p1283386691084826"></a>Declares functions for starting and stopping an ability. </p>
</td>
</tr>
<tr id="row2025487054084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p325116773084826"><a name="p325116773084826"></a><a name="p325116773084826"></a><a href="ability_env-h.md">ability_env.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314289883084826"><a name="p1314289883084826"></a><a name="p1314289883084826"></a>Declares functions for obtaining information about the runtime environment of the application to which the ability belongs, including the bundle name, source code path, and data path. </p>
</td>
</tr>
<tr id="row1586899208084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927954948084826"><a name="p927954948084826"></a><a name="p927954948084826"></a><a href="ability_errors-h.md">ability_errors.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1595511687084826"><a name="p1595511687084826"></a><a name="p1595511687084826"></a>Declares error codes returned by ability management functions. </p>
</td>
</tr>
<tr id="row1028981383084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1877810552084826"><a name="p1877810552084826"></a><a name="p1877810552084826"></a><a href="ability_event_handler-h.md">ability_event_handler.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1570920821084826"><a name="p1570920821084826"></a><a name="p1570920821084826"></a>Declares functions for performing operations during inter-thread communication, including running and quitting the event loop of the current thread and posting tasks to an asynchronous thread. </p>
</td>
</tr>
<tr id="row1811410565084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652046073084826"><a name="p1652046073084826"></a><a name="p1652046073084826"></a><a href="ability_loader-h.md">ability_loader.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p857449528084826"><a name="p857449528084826"></a><a name="p857449528084826"></a>Declares functions for registering the class names of <strong id="b1570043909084826"><a name="b1570043909084826"></a><a name="b1570043909084826"></a>Ability</strong> and <strong id="b1999236234084826"><a name="b1999236234084826"></a><a name="b1999236234084826"></a>AbilitySlice</strong> with the ability management framework. </p>
</td>
</tr>
<tr id="row1092610545084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1332616133084826"><a name="p1332616133084826"></a><a name="p1332616133084826"></a><a href="ability_manager-h.md">ability_manager.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513323168084826"><a name="p1513323168084826"></a><a name="p1513323168084826"></a>Declares ability-related functions, including functions for starting, stopping, connecting to, and disconnecting from an ability, registering a callback, and unregistering a callback. </p>
</td>
</tr>
<tr id="row359456009084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1457176477084826"><a name="p1457176477084826"></a><a name="p1457176477084826"></a><a href="ability_slice-h.md">ability_slice.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1188978306084826"><a name="p1188978306084826"></a><a name="p1188978306084826"></a>Declares ability slice-related functions, including ability slice lifecycle callbacks and functions for connecting to or disconnecting from ability slices. </p>
</td>
</tr>
<tr id="row229023428084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635449979084826"><a name="p635449979084826"></a><a name="p635449979084826"></a><a href="ability_state-h.md">ability_state.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p450055606084826"><a name="p450055606084826"></a><a name="p450055606084826"></a>Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or disconnecting from Particle Abilities. As the fundamental unit of OpenHarmony applications, abilities are classified into <a href="feature.md">Feature</a> Abilities and Particle Abilities. <a href="feature.md">Feature</a> Abilities support the Page template, and Particle Abilities support the <a href="service.md">Service</a> template. An ability using the Page template is called a Page ability for short and that using the <a href="service.md">Service</a> template is called a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
<tr id="row1126022793084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197102033084826"><a name="p1197102033084826"></a><a name="p1197102033084826"></a><a href="want-h.md">want.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58596940084826"><a name="p58596940084826"></a><a name="p58596940084826"></a>Declares the structure that provides abstract description of the operation to be performed, including the ability information and the carried data, and functions for setting data in the structure. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table583674011084826"></a>
<table><thead align="left"><tr id="row1915529785084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1470170846084826"><a name="p1470170846084826"></a><a name="p1470170846084826"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p187987864084826"><a name="p187987864084826"></a><a name="p187987864084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row333365679084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260607733084826"><a name="p260607733084826"></a><a name="p260607733084826"></a><a href="ohos-ability.md">OHOS::Ability</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1593988899084826"><a name="p1593988899084826"></a><a name="p1593988899084826"></a>Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or disconnecting from Particle Abilities. </p>
</td>
</tr>
<tr id="row160371709084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1686903509084826"><a name="p1686903509084826"></a><a name="p1686903509084826"></a><a href="iabilityconnection.md">IAbilityConnection</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120723653084826"><a name="p1120723653084826"></a><a name="p1120723653084826"></a>Provides callbacks to be invoked when a remote <a href="service.md">Service</a> ability is connected or disconnected. </p>
</td>
</tr>
<tr id="row154603181084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1663909876084826"><a name="p1663909876084826"></a><a name="p1663909876084826"></a><a href="ohos-abilitycontext.md">OHOS::AbilityContext</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p432553166084826"><a name="p432553166084826"></a><a name="p432553166084826"></a>Provides functions for starting and stopping an ability. </p>
</td>
</tr>
<tr id="row835366184084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032310325084826"><a name="p2032310325084826"></a><a name="p2032310325084826"></a><a href="ohos-abilityeventhandler.md">OHOS::AbilityEventHandler</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1532677325084826"><a name="p1532677325084826"></a><a name="p1532677325084826"></a>Declares functions for performing operations during inter-thread communication, including running and quitting the event loop of the current thread and posting tasks to an asynchronous thread. </p>
</td>
</tr>
<tr id="row98658998084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509277445084826"><a name="p509277445084826"></a><a name="p509277445084826"></a><a href="ohos-abilityloader.md">OHOS::AbilityLoader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199679902084826"><a name="p1199679902084826"></a><a name="p1199679902084826"></a>Declares functions for registering the class names of <a href="ohos-ability.md">Ability</a> and <a href="ohos-abilityslice.md">AbilitySlice</a> with the ability management framework. </p>
</td>
</tr>
<tr id="row422186675084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1678115560084826"><a name="p1678115560084826"></a><a name="p1678115560084826"></a><a href="ohos-abilityslice.md">OHOS::AbilitySlice</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p33415605084826"><a name="p33415605084826"></a><a name="p33415605084826"></a>Provides ability slice-related functions, including ability slice lifecycle callbacks and functions for connecting to or disconnecting from ability slices. </p>
</td>
</tr>
<tr id="row2119891640084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2708633084826"><a name="p2708633084826"></a><a name="p2708633084826"></a><a href="want.md">Want</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p371816199084826"><a name="p371816199084826"></a><a name="p371816199084826"></a>Defines the abstract description of an operation, including information about the ability and the extra data to carry. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1519902016084826"></a>
<table><thead align="left"><tr id="row1769615134084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p219966494084826"><a name="p219966494084826"></a><a name="p219966494084826"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p647676814084826"><a name="p647676814084826"></a><a name="p647676814084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row644301737084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1596850586084826"><a name="p1596850586084826"></a><a name="p1596850586084826"></a><a href="abilitykit.md#ga2c5bd891b502a92f937ae4bff3f80cad">REGISTER_AA</a>(className)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p719239067084826"><a name="p719239067084826"></a><a name="p719239067084826"></a>Registers the class name of an <strong id="b112863442084826"><a name="b112863442084826"></a><a name="b112863442084826"></a>Ability</strong> child class. </p>
</td>
</tr>
<tr id="row2015357167084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1344588669084826"><a name="p1344588669084826"></a><a name="p1344588669084826"></a><a href="abilitykit.md#ga8e811999b2b7780e67cb746d045ab5b8">REGISTER_AS</a>(className)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1413417073084826"><a name="p1413417073084826"></a><a name="p1413417073084826"></a>Registers the class name of an <strong id="b1329720385084826"><a name="b1329720385084826"></a><a name="b1329720385084826"></a>AbilitySlice</strong> child class. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1079622719084826"></a>
<table><thead align="left"><tr id="row1822962985084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1762495587084826"><a name="p1762495587084826"></a><a name="p1762495587084826"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p898508991084826"><a name="p898508991084826"></a><a name="p898508991084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2125681440084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p610278971084826"><a name="p610278971084826"></a><a name="p610278971084826"></a>{   <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55baa26c163b80b1f6786ca81dadc14b00fb">ERR_OK</a> = 0, <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55baa07793543807276aa96a35f35385266e">PARAM_NULL_ERROR</a>, <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55bac6fa7d9ef451bee4ccabaf54a2d1dfc2">MEMORY_MALLOC_ERROR</a>, <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55ba9d4a52497266a38e4636693bb6cf965c">DUMP_ABILITIES_ERROR</a>,   <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55ba95357b37369351e52b2244efb3af4cbc">IPC_REQUEST_ERROR</a>, <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55ba05d12b70f719b309d4c6234a6bbc4214">SERIALIZE_ERROR</a>, <a href="abilitykit.md#gga06fc87d81c62e9abb8790b6e5713c55ba0cfd5af1f777f6919ddef94e81b94b00">COMMAND_ERROR</a> = 0x7fff }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1361039995084826"><a name="p1361039995084826"></a><a name="p1361039995084826"></a>Declares error codes returned by ability management functions. </p>
</td>
</tr>
<tr id="row243411662084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p917221280084826"><a name="p917221280084826"></a><a name="p917221280084826"></a><a href="abilitykit.md#ga5d74787dedbc4e11c1ab15bf487e61f8">State</a> {   <a href="abilitykit.md#gga5d74787dedbc4e11c1ab15bf487e61f8a36e8e2958c7f6a4505cb8e8782717530">STATE_UNINITIALIZED</a>, <a href="abilitykit.md#gga5d74787dedbc4e11c1ab15bf487e61f8a24ac4e25affdf1bcda765d59e6cabcfd">STATE_INITIAL</a>, <a href="abilitykit.md#gga5d74787dedbc4e11c1ab15bf487e61f8a39e9fc11b119db5acccb179004077657">STATE_INACTIVE</a>, <a href="abilitykit.md#gga5d74787dedbc4e11c1ab15bf487e61f8a5f1f347a14f3373f19eb61973636f1a6">STATE_ACTIVE</a>,   <a href="abilitykit.md#gga5d74787dedbc4e11c1ab15bf487e61f8a701f6c0d2f4df7e2e37b07dacd0f514c">STATE_BACKGROUND</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730594498084826"><a name="p1730594498084826"></a><a name="p1730594498084826"></a>Enumerates all lifecycle states that an ability will go through over the course of its lifetime. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1107213947084826"></a>
<table><thead align="left"><tr id="row1295982960084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p992159363084826"><a name="p992159363084826"></a><a name="p992159363084826"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2088696987084826"><a name="p2088696987084826"></a><a name="p2088696987084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1852674362084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1709322972084826"><a name="p1709322972084826"></a><a name="p1709322972084826"></a><a href="abilitykit.md#ga4d016d42397f33c7710db8544581c757">OHOS::Ability::OnStart</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551051740084826"><a name="p551051740084826"></a><a name="p551051740084826"></a>virtual void </p>
<p id="p102305890084826"><a name="p102305890084826"></a><a name="p102305890084826"></a>Called when this ability is started. You must override this function if you want to perform some initialization operations during ability startup. </p>
</td>
</tr>
<tr id="row1876990348084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935900478084826"><a name="p1935900478084826"></a><a name="p1935900478084826"></a><a href="abilitykit.md#gae251a38aa7c0aebd7498eef86deab7c1">OHOS::Ability::OnInactive</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2012742851084826"><a name="p2012742851084826"></a><a name="p2012742851084826"></a>virtual void </p>
<p id="p1701083518084826"><a name="p1701083518084826"></a><a name="p1701083518084826"></a>Called when this ability enters the <strong id="b1248301982084826"><a name="b1248301982084826"></a><a name="b1248301982084826"></a>STATE_INACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row266334173084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p954540438084826"><a name="p954540438084826"></a><a name="p954540438084826"></a><a href="abilitykit.md#ga3135bfa435f5aaa185f21014a9e86e59">OHOS::Ability::OnActive</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670139456084826"><a name="p1670139456084826"></a><a name="p1670139456084826"></a>virtual void </p>
<p id="p357716365084826"><a name="p357716365084826"></a><a name="p357716365084826"></a>Called when this ability enters the <strong id="b1340796609084826"><a name="b1340796609084826"></a><a name="b1340796609084826"></a>STATE_ACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row335289907084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416927441084826"><a name="p416927441084826"></a><a name="p416927441084826"></a><a href="abilitykit.md#ga8185ad517d94ca99a00917d3d1f10620">OHOS::Ability::OnBackground</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1265439534084826"><a name="p1265439534084826"></a><a name="p1265439534084826"></a>virtual void </p>
<p id="p405243174084826"><a name="p405243174084826"></a><a name="p405243174084826"></a>Called when this ability enters the <strong id="b323284110084826"><a name="b323284110084826"></a><a name="b323284110084826"></a>STATE_BACKGROUND</strong> state. </p>
</td>
</tr>
<tr id="row141328699084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987394380084826"><a name="p987394380084826"></a><a name="p987394380084826"></a><a href="abilitykit.md#gaa4145b360bbe5cdb5d267b17ac12af6a">OHOS::Ability::OnStop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1068230111084826"><a name="p1068230111084826"></a><a name="p1068230111084826"></a>virtual void </p>
<p id="p1713253784084826"><a name="p1713253784084826"></a><a name="p1713253784084826"></a>Called when this ability enters the <strong id="b1401370211084826"><a name="b1401370211084826"></a><a name="b1401370211084826"></a>STATE_STOP</strong> state. </p>
</td>
</tr>
<tr id="row24276794084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1939128052084826"><a name="p1939128052084826"></a><a name="p1939128052084826"></a><a href="abilitykit.md#ga88e9dbaaa083be9f06adeea27680ef76">OHOS::Ability::OnConnect</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p986140165084826"><a name="p986140165084826"></a><a name="p986140165084826"></a>virtual const SvcIdentity * </p>
<p id="p667294227084826"><a name="p667294227084826"></a><a name="p667294227084826"></a>Called when this <a href="service.md">Service</a> ability is connected for the first time. </p>
</td>
</tr>
<tr id="row991109123084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363471228084826"><a name="p1363471228084826"></a><a name="p1363471228084826"></a><a href="abilitykit.md#gac17d2b81d661134b63ee74b0212eace6">OHOS::Ability::OnDisconnect</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923817086084826"><a name="p923817086084826"></a><a name="p923817086084826"></a>virtual void </p>
<p id="p1037110448084826"><a name="p1037110448084826"></a><a name="p1037110448084826"></a>Called when all abilities connected to this <a href="service.md">Service</a> ability are disconnected. </p>
</td>
</tr>
<tr id="row787619568084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872558517084826"><a name="p1872558517084826"></a><a name="p1872558517084826"></a><a href="abilitykit.md#gac83a9af046458b7f6bfaf85071b093f4">OHOS::Ability::SetMainRoute</a> (const std::string &amp;<a href="entry.md">entry</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731414156084826"><a name="p731414156084826"></a><a name="p731414156084826"></a>void </p>
<p id="p1748176623084826"><a name="p1748176623084826"></a><a name="p1748176623084826"></a>Sets the main route for this ability. </p>
</td>
</tr>
<tr id="row37156315084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1678353557084826"><a name="p1678353557084826"></a><a name="p1678353557084826"></a><a href="abilitykit.md#ga9b734c2ad8ad52f906d676f0c897a4aa">OHOS::Ability::SetUIContent</a> (<a href="ohos-rootview.md">RootView</a> *rootView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776608318084826"><a name="p776608318084826"></a><a name="p776608318084826"></a>void </p>
<p id="p1216706333084826"><a name="p1216706333084826"></a><a name="p1216706333084826"></a>Sets the UI layout for this ability. You can call <strong id="b1519134256084826"><a name="b1519134256084826"></a><a name="b1519134256084826"></a>GetWindowRootView()</strong> to create a layout and add controls. </p>
</td>
</tr>
<tr id="row218594545084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p464916870084826"><a name="p464916870084826"></a><a name="p464916870084826"></a><a href="abilitykit.md#gab2d208621c7236c3608afb77d8a02966">OHOS::Ability::MsgHandle</a> (uint32_t funcId, IpcIo *request, IpcIo *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323252736084826"><a name="p1323252736084826"></a><a name="p1323252736084826"></a>virtual void </p>
<p id="p610619120084826"><a name="p610619120084826"></a><a name="p610619120084826"></a>Handles a message sent by the client to this <a href="service.md">Service</a> ability. </p>
</td>
</tr>
<tr id="row502831346084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1188886391084826"><a name="p1188886391084826"></a><a name="p1188886391084826"></a><a href="abilitykit.md#ga5330624843c776ebe61366540d32eb92">OHOS::Ability::Dump</a> (const std::string &amp;extra)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142564647084826"><a name="p142564647084826"></a><a name="p142564647084826"></a>virtual void </p>
<p id="p1573360053084826"><a name="p1573360053084826"></a><a name="p1573360053084826"></a>Prints ability information to the console. </p>
</td>
</tr>
<tr id="row1164569676084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1983790527084826"><a name="p1983790527084826"></a><a name="p1983790527084826"></a><a href="abilitykit.md#gab11d708d5eaa1eca54828fa88625681a">OHOS::AbilityContext::StartAbility</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650507759084826"><a name="p650507759084826"></a><a name="p650507759084826"></a>int </p>
<p id="p1862089690084826"><a name="p1862089690084826"></a><a name="p1862089690084826"></a>Starts an <a href="ohos-ability.md">Ability</a> based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row751573235084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051669371084826"><a name="p2051669371084826"></a><a name="p2051669371084826"></a><a href="abilitykit.md#gadc670d5f6df0d485ee3062b70b3ffe99">OHOS::AbilityContext::StopAbility</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p593724019084826"><a name="p593724019084826"></a><a name="p593724019084826"></a>int </p>
<p id="p1970600528084826"><a name="p1970600528084826"></a><a name="p1970600528084826"></a>Stops an <a href="ohos-ability.md">Ability</a> based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row502760368084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587109232084826"><a name="p1587109232084826"></a><a name="p1587109232084826"></a><a href="abilitykit.md#gac4a36f03c60fcbeca3b47192ccab1d24">OHOS::AbilityContext::TerminateAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p794160501084826"><a name="p794160501084826"></a><a name="p794160501084826"></a>int </p>
<p id="p2089985039084826"><a name="p2089985039084826"></a><a name="p2089985039084826"></a>Destroys this <a href="ohos-ability.md">Ability</a>. </p>
</td>
</tr>
<tr id="row537420540084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p85426800084826"><a name="p85426800084826"></a><a name="p85426800084826"></a><a href="abilitykit.md#ga4da460ac085a8da1c665f317fcde2ba1">OHOS::AbilityContext::ConnectAbility</a> (const <a href="want.md">Want</a> &amp;want, const <a href="iabilityconnection.md">IAbilityConnection</a> &amp;conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798390949084826"><a name="p1798390949084826"></a><a name="p1798390949084826"></a>int </p>
<p id="p825031128084826"><a name="p825031128084826"></a><a name="p825031128084826"></a>Connects to a <a href="service.md">Service</a> ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row318774616084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935276695084826"><a name="p1935276695084826"></a><a name="p1935276695084826"></a><a href="abilitykit.md#ga1d9023597a9889dbb4015565a10f3470">OHOS::AbilityContext::DisconnectAbility</a> (const <a href="iabilityconnection.md">IAbilityConnection</a> &amp;conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p784998007084826"><a name="p784998007084826"></a><a name="p784998007084826"></a>int </p>
<p id="p833849980084826"><a name="p833849980084826"></a><a name="p833849980084826"></a>Disconnects from a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
<tr id="row879691540084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1446732982084826"><a name="p1446732982084826"></a><a name="p1446732982084826"></a><a href="abilitykit.md#gac893d7c01fabee34f80294e3e026c37d">GetBundleName</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1906886882084826"><a name="p1906886882084826"></a><a name="p1906886882084826"></a>const char * </p>
<p id="p1534122358084826"><a name="p1534122358084826"></a><a name="p1534122358084826"></a>Obtains the bundle name of the application to which this ability belongs. </p>
</td>
</tr>
<tr id="row280903984084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p102414646084826"><a name="p102414646084826"></a><a name="p102414646084826"></a><a href="abilitykit.md#ga7cead123e67bea6db8a34c8ae100e6c5">GetSrcPath</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1898952048084826"><a name="p1898952048084826"></a><a name="p1898952048084826"></a>const char * </p>
<p id="p2028227380084826"><a name="p2028227380084826"></a><a name="p2028227380084826"></a>Obtains the source code path of this ability. </p>
</td>
</tr>
<tr id="row194058941084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687843307084826"><a name="p687843307084826"></a><a name="p687843307084826"></a><a href="abilitykit.md#ga9be6a002714f3fb61b2335dd13ed9787">GetDataPath</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1195516737084826"><a name="p1195516737084826"></a><a name="p1195516737084826"></a>const char * </p>
<p id="p1129325260084826"><a name="p1129325260084826"></a><a name="p1129325260084826"></a>Obtains the data path of this ability. </p>
</td>
</tr>
<tr id="row361931267084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p611289150084826"><a name="p611289150084826"></a><a name="p611289150084826"></a><em id="gac534b1e3746d252944475b3ed9cb5bc7"><a name="gac534b1e3746d252944475b3ed9cb5bc7"></a><a name="gac534b1e3746d252944475b3ed9cb5bc7"></a></em>OHOS::AbilityEventHandler::Run ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673046067084826"><a name="p1673046067084826"></a><a name="p1673046067084826"></a><strong id="b1558825927"><a name="b1558825927"></a><a name="b1558825927"></a></strong> void </p>
<p id="p1051007477084826"><a name="p1051007477084826"></a><a name="p1051007477084826"></a>Starts running the event loop of the current thread. </p>
</td>
</tr>
<tr id="row1866519490084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998341919084826"><a name="p1998341919084826"></a><a name="p1998341919084826"></a><a href="abilitykit.md#gad4d0911a8bccd5aca32464bad867cb13">OHOS::AbilityEventHandler::PostTask</a> (const Task &amp;task)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141145190084826"><a name="p1141145190084826"></a><a name="p1141145190084826"></a>void </p>
<p id="p543848956084826"><a name="p543848956084826"></a><a name="p543848956084826"></a>Posts a task to an asynchronous thread. </p>
</td>
</tr>
<tr id="row89371309084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778215807084826"><a name="p778215807084826"></a><a name="p778215807084826"></a><em id="ga075bfbf9e5c9c2178f3183efd664dbaf"><a name="ga075bfbf9e5c9c2178f3183efd664dbaf"></a><a name="ga075bfbf9e5c9c2178f3183efd664dbaf"></a></em>OHOS::AbilityEventHandler::PostQuit ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p236025897084826"><a name="p236025897084826"></a><a name="p236025897084826"></a><strong id="b173226659"><a name="b173226659"></a><a name="b173226659"></a></strong> void </p>
<p id="p1233755306084826"><a name="p1233755306084826"></a><a name="p1233755306084826"></a>Quits the event loop of the current thread. </p>
</td>
</tr>
<tr id="row2011747835084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p309650610084826"><a name="p309650610084826"></a><a name="p309650610084826"></a><a href="abilitykit.md#gad26d144aaecd3185be6902e6d7399b9e">OHOS::AbilityEventHandler::GetCurrentHandler</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p641320528084826"><a name="p641320528084826"></a><a name="p641320528084826"></a>static <a href="ohos-abilityeventhandler.md">AbilityEventHandler</a> * </p>
<p id="p1076763691084826"><a name="p1076763691084826"></a><a name="p1076763691084826"></a>Obtains the event handler of the current thread. </p>
</td>
</tr>
<tr id="row759555782084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2039669508084826"><a name="p2039669508084826"></a><a name="p2039669508084826"></a><a href="abilitykit.md#gae79800c4077afdc2851d5a74d8964111">StartAbility</a> (const <a href="want.md">Want</a> *want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999949620084826"><a name="p1999949620084826"></a><a name="p1999949620084826"></a>int </p>
<p id="p1291536613084826"><a name="p1291536613084826"></a><a name="p1291536613084826"></a>Starts an ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1127862320084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601019297084826"><a name="p1601019297084826"></a><a name="p1601019297084826"></a><a href="abilitykit.md#gaba99bbd4ff6da4fb072338f5ce95e6ae">StopAbility</a> (const <a href="want.md">Want</a> *want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858372684084826"><a name="p858372684084826"></a><a name="p858372684084826"></a>int </p>
<p id="p807741003084826"><a name="p807741003084826"></a><a name="p807741003084826"></a>Stops an ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1085815641084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2023470994084826"><a name="p2023470994084826"></a><a name="p2023470994084826"></a><a href="abilitykit.md#gaae6c2bbb6ab0df92e39c1daad2bd901f">ConnectAbility</a> (const <a href="want.md">Want</a> *want, const <a href="iabilityconnection.md">IAbilityConnection</a> *conn, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p944813616084826"><a name="p944813616084826"></a><a name="p944813616084826"></a>int </p>
<p id="p623549456084826"><a name="p623549456084826"></a><a name="p623549456084826"></a>Connects to a <a href="service.md">Service</a> ability based on the specified <a href="want.md">Want</a> information. </p>
</td>
</tr>
<tr id="row1811707256084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p52091808084826"><a name="p52091808084826"></a><a name="p52091808084826"></a><a href="abilitykit.md#ga2769216a4c2654d3297a2fdb4011ea7a">DisconnectAbility</a> (const <a href="iabilityconnection.md">IAbilityConnection</a> *conn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897268242084826"><a name="p897268242084826"></a><a name="p897268242084826"></a>int </p>
<p id="p94956509084826"><a name="p94956509084826"></a><a name="p94956509084826"></a>Disconnects from a <a href="service.md">Service</a> ability. </p>
</td>
</tr>
<tr id="row141545836084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p387334636084826"><a name="p387334636084826"></a><a name="p387334636084826"></a><a href="abilitykit.md#gad3ffda54b710b0b86e54bd6c13efae98">OHOS::AbilitySlice::OnStart</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2092756129084826"><a name="p2092756129084826"></a><a name="p2092756129084826"></a>virtual void </p>
<p id="p2076998981084826"><a name="p2076998981084826"></a><a name="p2076998981084826"></a>Called when this ability slice is started. You must override this function if you want to perform some initialization operations during ability slice startup. </p>
</td>
</tr>
<tr id="row1755120161084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935920105084826"><a name="p935920105084826"></a><a name="p935920105084826"></a><a href="abilitykit.md#gae050b00aa885765bb6808374be772615">OHOS::AbilitySlice::OnInactive</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1270742156084826"><a name="p1270742156084826"></a><a name="p1270742156084826"></a>virtual void </p>
<p id="p127260684084826"><a name="p127260684084826"></a><a name="p127260684084826"></a>Called when this ability slice enters the <strong id="b633187215084826"><a name="b633187215084826"></a><a name="b633187215084826"></a>STATE_INACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row1255287785084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709764363084826"><a name="p709764363084826"></a><a name="p709764363084826"></a><a href="abilitykit.md#ga1a588eb6635e42979e18ac8013f9ea61">OHOS::AbilitySlice::OnActive</a> (const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501093131084826"><a name="p1501093131084826"></a><a name="p1501093131084826"></a>virtual void </p>
<p id="p745201654084826"><a name="p745201654084826"></a><a name="p745201654084826"></a>Called when this ability slice enters the <strong id="b664222502084826"><a name="b664222502084826"></a><a name="b664222502084826"></a>STATE_ACTIVE</strong> state. </p>
</td>
</tr>
<tr id="row514390883084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149260715084826"><a name="p1149260715084826"></a><a name="p1149260715084826"></a><a href="abilitykit.md#ga19217479f8468b525460be156827a524">OHOS::AbilitySlice::OnBackground</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p78393522084826"><a name="p78393522084826"></a><a name="p78393522084826"></a>virtual void </p>
<p id="p1247859302084826"><a name="p1247859302084826"></a><a name="p1247859302084826"></a>Called when this ability slice enters the <strong id="b695737357084826"><a name="b695737357084826"></a><a name="b695737357084826"></a>STATE_BACKGROUND</strong> state. </p>
</td>
</tr>
<tr id="row896730358084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1837537345084826"><a name="p1837537345084826"></a><a name="p1837537345084826"></a><a href="abilitykit.md#ga4e1556b780a1271e61328e659fc30eb9">OHOS::AbilitySlice::OnStop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p526331905084826"><a name="p526331905084826"></a><a name="p526331905084826"></a>virtual void </p>
<p id="p344435690084826"><a name="p344435690084826"></a><a name="p344435690084826"></a>Called when this ability slice enters the <strong id="b1677856937084826"><a name="b1677856937084826"></a><a name="b1677856937084826"></a>STATE_STOP</strong> state. </p>
</td>
</tr>
<tr id="row1807150483084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092208121084826"><a name="p2092208121084826"></a><a name="p2092208121084826"></a><a href="abilitykit.md#gab2ec8b885edd0d5818b4c60541c1875f">OHOS::AbilitySlice::Present</a> (<a href="ohos-abilityslice.md">AbilitySlice</a> &amp;abilitySlice, const <a href="want.md">Want</a> &amp;want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p465433061084826"><a name="p465433061084826"></a><a name="p465433061084826"></a>void </p>
<p id="p430684497084826"><a name="p430684497084826"></a><a name="p430684497084826"></a>Presents another ability slice, which can be an ability slice that is not started or an existing ability slice in the host ability. </p>
</td>
</tr>
<tr id="row1753248205084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p698748451084826"><a name="p698748451084826"></a><a name="p698748451084826"></a><a href="abilitykit.md#gaf424e47c7980ff92093c6b7b75888639">OHOS::AbilitySlice::Terminate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459426083084826"><a name="p459426083084826"></a><a name="p459426083084826"></a>void </p>
<p id="p854786090084826"><a name="p854786090084826"></a><a name="p854786090084826"></a>Destroys this ability slice. </p>
</td>
</tr>
<tr id="row558726944084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p502101967084826"><a name="p502101967084826"></a><a name="p502101967084826"></a><a href="abilitykit.md#ga050a81cda49edb471594447f8f4cdaac">OHOS::AbilitySlice::SetUIContent</a> (<a href="ohos-rootview.md">RootView</a> *rootView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p141103960084826"><a name="p141103960084826"></a><a name="p141103960084826"></a>void </p>
<p id="p1918171636084826"><a name="p1918171636084826"></a><a name="p1918171636084826"></a>Sets the UI layout for the host ability of this ability slice. </p>
</td>
</tr>
<tr id="row174490230084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2039154290084826"><a name="p2039154290084826"></a><a name="p2039154290084826"></a><a href="abilitykit.md#ga62ca448e092c81497ffdd1f0b1c56938">ClearWant</a> (<a href="want.md">Want</a> *want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265556677084826"><a name="p265556677084826"></a><a name="p265556677084826"></a>void </p>
<p id="p1624405791084826"><a name="p1624405791084826"></a><a name="p1624405791084826"></a>Clears the memory of a specified <strong id="b347324884084826"><a name="b347324884084826"></a><a name="b347324884084826"></a><a href="want.md">Want</a></strong> object. </p>
</td>
</tr>
<tr id="row711143342084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p376948082084826"><a name="p376948082084826"></a><a name="p376948082084826"></a><a href="abilitykit.md#ga65f4d2eab99497e496dcd493bd0d047e">SetWantElement</a> (<a href="want.md">Want</a> *want, <a href="elementname.md">ElementName</a> element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1829268797084826"><a name="p1829268797084826"></a><a name="p1829268797084826"></a>bool </p>
<p id="p1403427084826"><a name="p1403427084826"></a><a name="p1403427084826"></a>Sets the <strong id="b2001678480084826"><a name="b2001678480084826"></a><a name="b2001678480084826"></a>element</strong> variable for a specified <strong id="b1646388638084826"><a name="b1646388638084826"></a><a name="b1646388638084826"></a><a href="want.md">Want</a></strong> object. </p>
</td>
</tr>
<tr id="row1402833281084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1459846866084826"><a name="p1459846866084826"></a><a name="p1459846866084826"></a><a href="abilitykit.md#ga89a719b5f730bc5fde9f637a5ed630c9">SetWantData</a> (<a href="want.md">Want</a> *want, const void *data, uint16_t dataLength)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p285333855084826"><a name="p285333855084826"></a><a name="p285333855084826"></a>bool </p>
<p id="p379581519084826"><a name="p379581519084826"></a><a name="p379581519084826"></a>Sets data to carry in a specified <strong id="b559775063084826"><a name="b559775063084826"></a><a name="b559775063084826"></a><a href="want.md">Want</a></strong> object for starting a particular ability. </p>
</td>
</tr>
<tr id="row1424001388084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p418634425084826"><a name="p418634425084826"></a><a name="p418634425084826"></a><a href="abilitykit.md#gab8e5fac952fc6407f20cd9b7185d3a65">SetWantSvcIdentity</a> (<a href="want.md">Want</a> *want, SvcIdentity sid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323391201084826"><a name="p323391201084826"></a><a name="p323391201084826"></a>bool </p>
<p id="p1012920675084826"><a name="p1012920675084826"></a><a name="p1012920675084826"></a>Sets the <strong id="b66890027084826"><a name="b66890027084826"></a><a name="b66890027084826"></a>sid</strong> member variable for a specified <strong id="b318840415084826"><a name="b318840415084826"></a><a name="b318840415084826"></a><a href="want.md">Want</a></strong> object. </p>
</td>
</tr>
<tr id="row337623062084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782014997084826"><a name="p1782014997084826"></a><a name="p1782014997084826"></a><a href="abilitykit.md#ga31adc60981c10b22d0e9bbdc7126d17c">WantToUri</a> (<a href="want.md">Want</a> want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1160931032084826"><a name="p1160931032084826"></a><a name="p1160931032084826"></a>const char * </p>
<p id="p1992001618084826"><a name="p1992001618084826"></a><a name="p1992001618084826"></a>Converts a specified <strong id="b1183154051084826"><a name="b1183154051084826"></a><a name="b1183154051084826"></a><a href="want.md">Want</a></strong> object into a character string. </p>
</td>
</tr>
<tr id="row912505287084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p55585929084826"><a name="p55585929084826"></a><a name="p55585929084826"></a><a href="abilitykit.md#ga43226d0858faa92e83bea33aaf4b614c">WantParseUri</a> (const char *uri)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1838093337084826"><a name="p1838093337084826"></a><a name="p1838093337084826"></a><a href="want.md">Want</a> * </p>
<p id="p680310441084826"><a name="p680310441084826"></a><a name="p680310441084826"></a>Converts a specified character string into a <strong id="b629925827084826"><a name="b629925827084826"></a><a name="b629925827084826"></a><a href="want.md">Want</a></strong> object. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1230639092084826"></a>

## **Macro Definition Documentation**<a name="section586724089084826"></a>

## REGISTER\_AA<a name="ga2c5bd891b502a92f937ae4bff3f80cad"></a>

```
#define REGISTER_AA( className)
```

```
Values: __attribute__((constructor)) void RegisterAA##className() { \

 AbilityLoader::GetInstance().RegisterAbility(#className, []()->Ability* { \

 return new className; \

 }); \

 }


```

 **Description:**

Registers the class name of an  **Ability**  child class. 

After implementing your own  **Ability**  class, you should call this function so that the ability management framework can create  **Ability**  instances when loading your  **Ability**  class.

**Parameters:**

<a name="table801925035084826"></a>
<table><thead align="left"><tr id="row1323190368084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1858995974084826"><a name="p1858995974084826"></a><a name="p1858995974084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p724204665084826"><a name="p724204665084826"></a><a name="p724204665084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row121594805084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">className</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b442262768084826"><a name="b442262768084826"></a><a name="b442262768084826"></a>Ability</strong> class name to register. </td>
</tr>
</tbody>
</table>

## REGISTER\_AS<a name="ga8e811999b2b7780e67cb746d045ab5b8"></a>

```
#define REGISTER_AS( className)
```

```
Values: __attribute__((constructor)) void RegisterAS##className() { \

 AbilityLoader::GetInstance().RegisterAbilitySlice(#className, []()->AbilitySlice* { \

 return new className; \

 }); \

 }


```

 **Description:**

Registers the class name of an  **AbilitySlice**  child class. 

After implementing your own  **AbilitySlice**  class, you should call this function so that the ability management framework can create  **AbilitySlice**  instances when loading your  **AbilitySlice**  class.

**Parameters:**

<a name="table1325879296084826"></a>
<table><thead align="left"><tr id="row364951137084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1245290674084826"><a name="p1245290674084826"></a><a name="p1245290674084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p294982802084826"><a name="p294982802084826"></a><a name="p294982802084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row410633070084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">className</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b497793534084826"><a name="b497793534084826"></a><a name="b497793534084826"></a>AbilitySlice</strong> class name to register. </td>
</tr>
</tbody>
</table>

## **Enumeration Type Documentation**<a name="section787241006084826"></a>

## anonymous enum<a name="ga06fc87d81c62e9abb8790b6e5713c55b"></a>

```
anonymous enum
```

 **Description:**

Declares error codes returned by ability management functions. 

<a name="table1769137476084826"></a>
<table><thead align="left"><tr id="row1409712056084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1889132472084826"><a name="p1889132472084826"></a><a name="p1889132472084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p583588157084826"><a name="p583588157084826"></a><a name="p583588157084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row420510995084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55baa26c163b80b1f6786ca81dadc14b00fb"><a name="gga06fc87d81c62e9abb8790b6e5713c55baa26c163b80b1f6786ca81dadc14b00fb"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55baa26c163b80b1f6786ca81dadc14b00fb"></a></strong>ERR_OK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p460296708084826"><a name="p460296708084826"></a><a name="p460296708084826"></a>The function is successfully called. </p>
 </td>
</tr>
<tr id="row655330575084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55baa07793543807276aa96a35f35385266e"><a name="gga06fc87d81c62e9abb8790b6e5713c55baa07793543807276aa96a35f35385266e"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55baa07793543807276aa96a35f35385266e"></a></strong>PARAM_NULL_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667875312084826"><a name="p667875312084826"></a><a name="p667875312084826"></a>The parameter is null. </p>
 </td>
</tr>
<tr id="row1172848270084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55bac6fa7d9ef451bee4ccabaf54a2d1dfc2"><a name="gga06fc87d81c62e9abb8790b6e5713c55bac6fa7d9ef451bee4ccabaf54a2d1dfc2"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55bac6fa7d9ef451bee4ccabaf54a2d1dfc2"></a></strong>MEMORY_MALLOC_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1157898880084826"><a name="p1157898880084826"></a><a name="p1157898880084826"></a>Memory allocation error. </p>
 </td>
</tr>
<tr id="row2103468729084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55ba9d4a52497266a38e4636693bb6cf965c"><a name="gga06fc87d81c62e9abb8790b6e5713c55ba9d4a52497266a38e4636693bb6cf965c"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55ba9d4a52497266a38e4636693bb6cf965c"></a></strong>DUMP_ABILITIES_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1073545251084826"><a name="p1073545251084826"></a><a name="p1073545251084826"></a>An error occurred during the execution of the <strong id="b870237534084826"><a name="b870237534084826"></a><a name="b870237534084826"></a>Dump</strong> function. </p>
 </td>
</tr>
<tr id="row144473577084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55ba95357b37369351e52b2244efb3af4cbc"><a name="gga06fc87d81c62e9abb8790b6e5713c55ba95357b37369351e52b2244efb3af4cbc"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55ba95357b37369351e52b2244efb3af4cbc"></a></strong>IPC_REQUEST_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1714775496084826"><a name="p1714775496084826"></a><a name="p1714775496084826"></a>IPC request error. </p>
 </td>
</tr>
<tr id="row1625120457084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55ba05d12b70f719b309d4c6234a6bbc4214"><a name="gga06fc87d81c62e9abb8790b6e5713c55ba05d12b70f719b309d4c6234a6bbc4214"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55ba05d12b70f719b309d4c6234a6bbc4214"></a></strong>SERIALIZE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1318496554084826"><a name="p1318496554084826"></a><a name="p1318496554084826"></a>Serialization error. </p>
 </td>
</tr>
<tr id="row1403863367084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga06fc87d81c62e9abb8790b6e5713c55ba0cfd5af1f777f6919ddef94e81b94b00"><a name="gga06fc87d81c62e9abb8790b6e5713c55ba0cfd5af1f777f6919ddef94e81b94b00"></a><a name="gga06fc87d81c62e9abb8790b6e5713c55ba0cfd5af1f777f6919ddef94e81b94b00"></a></strong>COMMAND_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1294352256084826"><a name="p1294352256084826"></a><a name="p1294352256084826"></a>Command error. </p>
 </td>
</tr>
</tbody>
</table>

## State<a name="ga5d74787dedbc4e11c1ab15bf487e61f8"></a>

```
enum [State](abilitykit.md#ga5d74787dedbc4e11c1ab15bf487e61f8)
```

 **Description:**

Enumerates all lifecycle states that an ability will go through over the course of its lifetime. 

<a name="table2008870595084826"></a>
<table><thead align="left"><tr id="row989195496084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p44555629084826"><a name="p44555629084826"></a><a name="p44555629084826"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p884429213084826"><a name="p884429213084826"></a><a name="p884429213084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row610264197084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga5d74787dedbc4e11c1ab15bf487e61f8a36e8e2958c7f6a4505cb8e8782717530"><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a36e8e2958c7f6a4505cb8e8782717530"></a><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a36e8e2958c7f6a4505cb8e8782717530"></a></strong>STATE_UNINITIALIZED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857045550084826"><a name="p1857045550084826"></a><a name="p1857045550084826"></a>Uninitialized state: An ability is in this state when it has not been initialized after being created. </p>
 </td>
</tr>
<tr id="row1547626527084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga5d74787dedbc4e11c1ab15bf487e61f8a24ac4e25affdf1bcda765d59e6cabcfd"><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a24ac4e25affdf1bcda765d59e6cabcfd"></a><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a24ac4e25affdf1bcda765d59e6cabcfd"></a></strong>STATE_INITIAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1943472071084826"><a name="p1943472071084826"></a><a name="p1943472071084826"></a>Initial state: An ability is in this state after it is initialized or stopped. </p>
 </td>
</tr>
<tr id="row1021214556084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga5d74787dedbc4e11c1ab15bf487e61f8a39e9fc11b119db5acccb179004077657"><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a39e9fc11b119db5acccb179004077657"></a><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a39e9fc11b119db5acccb179004077657"></a></strong>STATE_INACTIVE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1678643098084826"><a name="p1678643098084826"></a><a name="p1678643098084826"></a>Inactive state: An ability is in this state when it is switched to the foreground but is not interactive. </p>
 </td>
</tr>
<tr id="row892018807084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga5d74787dedbc4e11c1ab15bf487e61f8a5f1f347a14f3373f19eb61973636f1a6"><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a5f1f347a14f3373f19eb61973636f1a6"></a><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a5f1f347a14f3373f19eb61973636f1a6"></a></strong>STATE_ACTIVE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1486519301084826"><a name="p1486519301084826"></a><a name="p1486519301084826"></a>Active state: An ability is in this state when it is switched to the foreground and is interactive. </p>
 </td>
</tr>
<tr id="row1571284603084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga5d74787dedbc4e11c1ab15bf487e61f8a701f6c0d2f4df7e2e37b07dacd0f514c"><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a701f6c0d2f4df7e2e37b07dacd0f514c"></a><a name="gga5d74787dedbc4e11c1ab15bf487e61f8a701f6c0d2f4df7e2e37b07dacd0f514c"></a></strong>STATE_BACKGROUND </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p214708488084826"><a name="p214708488084826"></a><a name="p214708488084826"></a>Background state: An ability is in this state after it returns to the background. </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1784141011084826"></a>

## ClearWant\(\)<a name="ga62ca448e092c81497ffdd1f0b1c56938"></a>

```
void ClearWant ([Want](want.md) * want)
```

 **Description:**

Clears the memory of a specified  **[Want](want.md)**  object. 

After calling functions such as  [SetWantElement](abilitykit.md#ga65f4d2eab99497e496dcd493bd0d047e), you should call this function to clear the memory.

**Parameters:**

<a name="table1493880633084826"></a>
<table><thead align="left"><tr id="row109519538084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p765186619084826"><a name="p765186619084826"></a><a name="p765186619084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1107990477084826"><a name="p1107990477084826"></a><a name="p1107990477084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1734568138084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1001703783084826"><a name="b1001703783084826"></a><a name="b1001703783084826"></a><a href="want.md">Want</a></strong> object whose memory is to be released. </td>
</tr>
</tbody>
</table>

## ConnectAbility\(\) \[1/2\]<a name="ga4da460ac085a8da1c665f317fcde2ba1"></a>

```
int OHOS::AbilityContext::ConnectAbility (const [Want](want.md) & want, const [IAbilityConnection](iabilityconnection.md) & conn, void * data )
```

 **Description:**

Connects to a  [Service](service.md)  ability based on the specified  [Want](want.md)  information. 

After the  [Service](service.md)  ability is connected, the  [Ability](ohos-ability.md)  Manager  [Service](service.md)  invokes a particular callback and returns the ID of the  [Service](service.md)  ability. The client can use this ID to communicate with the connected  [Service](service.md)  ability.

**Parameters:**

<a name="table775652436084826"></a>
<table><thead align="left"><tr id="row1183605625084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1572749253084826"><a name="p1572749253084826"></a><a name="p1572749253084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1506534041084826"><a name="p1506534041084826"></a><a name="p1506534041084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1100950139084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure containing information about the <a href="service.md">Service</a> ability to connect. </td>
</tr>
<tr id="row719962878084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">conn</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to be invoked when the connection is successful. </td>
</tr>
<tr id="row1943619680084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to be passed to the callback. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if this function is successfully called; returns another value otherwise. 



## ConnectAbility\(\) \[2/2\]<a name="gaae6c2bbb6ab0df92e39c1daad2bd901f"></a>

```
int ConnectAbility (const [Want](want.md) * want, const [IAbilityConnection](iabilityconnection.md) * conn, void * data )
```

 **Description:**

Connects to a  [Service](service.md)  ability based on the specified  [Want](want.md)  information. 

After the  [Service](service.md)  ability is connected, the AMS invokes the particular callback and returns the ID of the  [Service](service.md)  ability. The client can use this ID to communicate with the connected  [Service](service.md)  ability.

**Parameters:**

<a name="table1253404157084826"></a>
<table><thead align="left"><tr id="row1250764545084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1825720735084826"><a name="p1825720735084826"></a><a name="p1825720735084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2030283194084826"><a name="p2030283194084826"></a><a name="p2030283194084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row272791548084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure containing information about the <a href="service.md">Service</a> ability to connect. </td>
</tr>
<tr id="row141353901084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">conn</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback object when the <a href="service.md">Service</a> ability is connected. </td>
</tr>
<tr id="row1895676717084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to be passed to the callback. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if this function is successfully called; returns another value otherwise. 



## DisconnectAbility\(\) \[1/2\]<a name="ga1d9023597a9889dbb4015565a10f3470"></a>

```
int OHOS::AbilityContext::DisconnectAbility (const [IAbilityConnection](iabilityconnection.md) & conn)
```

 **Description:**

Disconnects from a  [Service](service.md)  ability. 

**Parameters:**

<a name="table2055293880084826"></a>
<table><thead align="left"><tr id="row1466332497084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1068843051084826"><a name="p1068843051084826"></a><a name="p1068843051084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1832928260084826"><a name="p1832928260084826"></a><a name="p1832928260084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1574061693084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">conn</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to be invoked when the connection is successful. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if this function is successfully called; returns another value otherwise. 



## DisconnectAbility\(\) \[2/2\]<a name="ga2769216a4c2654d3297a2fdb4011ea7a"></a>

```
int DisconnectAbility (const [IAbilityConnection](iabilityconnection.md) * conn)
```

 **Description:**

Disconnects from a  [Service](service.md)  ability. 

**Parameters:**

<a name="table794849665084826"></a>
<table><thead align="left"><tr id="row1249476211084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p723715600084826"><a name="p723715600084826"></a><a name="p723715600084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1216935478084826"><a name="p1216935478084826"></a><a name="p1216935478084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row563288504084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">conn</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback object when the <a href="service.md">Service</a> ability is connected. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if this function is successfully called; returns another value otherwise. 



## Dump\(\)<a name="ga5330624843c776ebe61366540d32eb92"></a>

```
virtual void OHOS::Ability::Dump (const std::string & extra)
```

 **Description:**

Prints ability information to the console. 

You can override this function to obtain or print extra parameters.

**Parameters:**

<a name="table1781626905084826"></a>
<table><thead align="left"><tr id="row1990562000084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1393393681084826"><a name="p1393393681084826"></a><a name="p1393393681084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1255706018084826"><a name="p1255706018084826"></a><a name="p1255706018084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1720399280084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">extra</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the extra parameter to be obtained or printed to the console. </td>
</tr>
</tbody>
</table>

## GetBundleName\(\)<a name="gac893d7c01fabee34f80294e3e026c37d"></a>

```
const char* GetBundleName ()
```

 **Description:**

Obtains the bundle name of the application to which this ability belongs. 

**Returns:**

Returns the pointer to the bundle name if the operation is successful; returns a null pointer otherwise. 



## GetCurrentHandler\(\)<a name="gad26d144aaecd3185be6902e6d7399b9e"></a>

```
static [AbilityEventHandler](ohos-abilityeventhandler.md)* OHOS::AbilityEventHandler::GetCurrentHandler ()
```

 **Description:**

Obtains the event handler of the current thread. 

**Returns:**

Returns the pointer to the  [AbilityEventHandler](ohos-abilityeventhandler.md)  object of the current thread. 



## GetDataPath\(\)<a name="ga9be6a002714f3fb61b2335dd13ed9787"></a>

```
const char* GetDataPath ()
```

 **Description:**

Obtains the data path of this ability. 

**Returns:**

Returns the pointer to the data path of this ability. 



## GetSrcPath\(\)<a name="ga7cead123e67bea6db8a34c8ae100e6c5"></a>

```
const char* GetSrcPath ()
```

 **Description:**

Obtains the source code path of this ability. 

**Returns:**

Returns the pointer to the source code path of this ability. 



## MsgHandle\(\)<a name="gab2d208621c7236c3608afb77d8a02966"></a>

```
virtual void OHOS::Ability::MsgHandle (uint32_t funcId, IpcIo * request, IpcIo * reply )
```

 **Description:**

Handles a message sent by the client to this  [Service](service.md)  ability. 

**Parameters:**

<a name="table1363731700084826"></a>
<table><thead align="left"><tr id="row46417640084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p255008973084826"><a name="p255008973084826"></a><a name="p255008973084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p326004179084826"><a name="p326004179084826"></a><a name="p326004179084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row979348565084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">funcId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the message sent by the client. </td>
</tr>
<tr id="row984641626084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the serialized request parameters sent by the client. </td>
</tr>
<tr id="row360720208084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">reply</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the serialized result returned to the client. </td>
</tr>
</tbody>
</table>

## OnActive\(\) \[1/2\]<a name="ga1a588eb6635e42979e18ac8013f9ea61"></a>

```
virtual void OHOS::AbilitySlice::OnActive (const [Want](want.md) & want)
```

 **Description:**

Called when this ability slice enters the  **STATE\_ACTIVE**  state. 

The ability slice in the  **STATE\_ACTIVE**  state is visible and has focus. You can override this function to implement your own processing logic.

**Parameters:**

<a name="table1689637047084826"></a>
<table><thead align="left"><tr id="row613808386084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p226729612084826"><a name="p226729612084826"></a><a name="p226729612084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p734696491084826"><a name="p734696491084826"></a><a name="p734696491084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row75414449084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing activation information about the ability slice. </td>
</tr>
</tbody>
</table>

## OnActive\(\) \[2/2\]<a name="ga3135bfa435f5aaa185f21014a9e86e59"></a>

```
virtual void OHOS::Ability::OnActive (const [Want](want.md) & want)
```

 **Description:**

Called when this ability enters the  **STATE\_ACTIVE**  state. 

The ability in the  **STATE\_ACTIVE**  state is visible and has focus. You can override this function to implement your own processing logic.

**Parameters:**

<a name="table1264836503084826"></a>
<table><thead align="left"><tr id="row2074210916084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p920763233084826"><a name="p920763233084826"></a><a name="p920763233084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p605465239084826"><a name="p605465239084826"></a><a name="p605465239084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1557777390084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing activation information about the ability. </td>
</tr>
</tbody>
</table>

## OnBackground\(\) \[1/2\]<a name="ga19217479f8468b525460be156827a524"></a>

```
virtual void OHOS::AbilitySlice::OnBackground ()
```

 **Description:**

Called when this ability slice enters the  **STATE\_BACKGROUND**  state. 

The ability slice in the  **STATE\_BACKGROUND**  state is invisible. You can override this function to implement your own processing logic. 

## OnBackground\(\) \[2/2\]<a name="ga8185ad517d94ca99a00917d3d1f10620"></a>

```
virtual void OHOS::Ability::OnBackground ()
```

 **Description:**

Called when this ability enters the  **STATE\_BACKGROUND**  state. 

The ability in the  **STATE\_BACKGROUND**  state is invisible. You can override this function to implement your own processing logic. 

## OnConnect\(\)<a name="ga88e9dbaaa083be9f06adeea27680ef76"></a>

```
virtual const SvcIdentity* OHOS::Ability::OnConnect (const [Want](want.md) & want)
```

 **Description:**

Called when this  [Service](service.md)  ability is connected for the first time. 

You can override this function to implement your own processing logic.

**Parameters:**

<a name="table219057049084826"></a>
<table><thead align="left"><tr id="row42580261084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p44731320084826"><a name="p44731320084826"></a><a name="p44731320084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p478438402084826"><a name="p478438402084826"></a><a name="p478438402084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2074257973084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing connection information about the <a href="service.md">Service</a> ability. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a pointer to the  **sid**  of the connected  [Service](service.md)  ability. 



## OnDisconnect\(\)<a name="gac17d2b81d661134b63ee74b0212eace6"></a>

```
virtual void OHOS::Ability::OnDisconnect (const [Want](want.md) & want)
```

 **Description:**

Called when all abilities connected to this  [Service](service.md)  ability are disconnected. 

You can override this function to implement your own processing logic.

**Parameters:**

<a name="table1691019618084826"></a>
<table><thead align="left"><tr id="row894791778084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p355669002084826"><a name="p355669002084826"></a><a name="p355669002084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1195991113084826"><a name="p1195991113084826"></a><a name="p1195991113084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row295781002084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing disconnection information about the <a href="service.md">Service</a> ability. </td>
</tr>
</tbody>
</table>

## OnInactive\(\) \[1/2\]<a name="gae050b00aa885765bb6808374be772615"></a>

```
virtual void OHOS::AbilitySlice::OnInactive ()
```

 **Description:**

Called when this ability slice enters the  **STATE\_INACTIVE**  state. 

**STATE\_INACTIVE**  is an instantaneous state. The ability slice in this state may be visible but does not have focus. You can override this function to implement your own processing logic. 

## OnInactive\(\) \[2/2\]<a name="gae251a38aa7c0aebd7498eef86deab7c1"></a>

```
virtual void OHOS::Ability::OnInactive ()
```

 **Description:**

Called when this ability enters the  **STATE\_INACTIVE**  state. 

**STATE\_INACTIVE**  is an instantaneous state. The ability in this state may be visible but does not have focus. You can override this function to implement your own processing logic. 

## OnStart\(\) \[1/2\]<a name="gad3ffda54b710b0b86e54bd6c13efae98"></a>

```
virtual void OHOS::AbilitySlice::OnStart (const [Want](want.md) & want)
```

 **Description:**

Called when this ability slice is started. You must override this function if you want to perform some initialization operations during ability slice startup. 

This function can be called only once in the entire lifecycle of an ability slice. You can override this function to implement your own processing logic. 

**Parameters:**

<a name="table715234981084826"></a>
<table><thead align="left"><tr id="row1248988080084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p921013983084826"><a name="p921013983084826"></a><a name="p921013983084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p28150133084826"><a name="p28150133084826"></a><a name="p28150133084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1818781738084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing startup information about the ability slice. </td>
</tr>
</tbody>
</table>

## OnStart\(\) \[2/2\]<a name="ga4d016d42397f33c7710db8544581c757"></a>

```
virtual void OHOS::Ability::OnStart (const [Want](want.md) & want)
```

 **Description:**

Called when this ability is started. You must override this function if you want to perform some initialization operations during ability startup. 

This function can be called only once in the entire lifecycle of an ability. 

**Parameters:**

<a name="table1859637574084826"></a>
<table><thead align="left"><tr id="row1099520288084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1537916566084826"><a name="p1537916566084826"></a><a name="p1537916566084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1552361685084826"><a name="p1552361685084826"></a><a name="p1552361685084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row25918164084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing startup information about the ability. </td>
</tr>
</tbody>
</table>

## OnStop\(\) \[1/2\]<a name="ga4e1556b780a1271e61328e659fc30eb9"></a>

```
virtual void OHOS::AbilitySlice::OnStop ()
```

 **Description:**

Called when this ability slice enters the  **STATE\_STOP**  state. 

The ability slice in the  **STATE\_STOP**  state is being destroyed. You can override this function to implement your own processing logic. 

## OnStop\(\) \[2/2\]<a name="gaa4145b360bbe5cdb5d267b17ac12af6a"></a>

```
virtual void OHOS::Ability::OnStop ()
```

 **Description:**

Called when this ability enters the  **STATE\_STOP**  state. 

The ability in the  **STATE\_STOP**  is being destroyed. You can override this function to implement your own processing logic. 

## PostTask\(\)<a name="gad4d0911a8bccd5aca32464bad867cb13"></a>

```
void OHOS::AbilityEventHandler::PostTask (const Task & task)
```

 **Description:**

Posts a task to an asynchronous thread. 

**Parameters:**

<a name="table890460423084826"></a>
<table><thead align="left"><tr id="row2119782823084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p924389977084826"><a name="p924389977084826"></a><a name="p924389977084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1459797179084826"><a name="p1459797179084826"></a><a name="p1459797179084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row426722068084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">task</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the task to post. </td>
</tr>
</tbody>
</table>

## Present\(\)<a name="gab2ec8b885edd0d5818b4c60541c1875f"></a>

```
void OHOS::AbilitySlice::Present ([AbilitySlice](ohos-abilityslice.md) & abilitySlice, const [Want](want.md) & want )
```

 **Description:**

Presents another ability slice, which can be an ability slice that is not started or an existing ability slice in the host ability. 

**Parameters:**

<a name="table628616221084826"></a>
<table><thead align="left"><tr id="row390258325084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1446805221084826"><a name="p1446805221084826"></a><a name="p1446805221084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p378587379084826"><a name="p378587379084826"></a><a name="p378587379084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row479106266084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">abilitySlice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target ability slice. This parameter cannot be null. </td>
</tr>
<tr id="row1142102340084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="want.md">Want</a> structure containing startup information about the target ability slice. </td>
</tr>
</tbody>
</table>

**Attention:**

This function can be called only when both of the following conditions are met: 

-    The host ability is in the  **STATE\_ACTIVE**  state. 
-    The target ability slice is not started or destroyed.

## SetMainRoute\(\)<a name="gac83a9af046458b7f6bfaf85071b093f4"></a>

```
void OHOS::Ability::SetMainRoute (const std::string & entry)
```

 **Description:**

Sets the main route for this ability. 

The main route, also called main entry, refers to the default  **[AbilitySlice](ohos-abilityslice.md)**  to present for this ability. This function should be called only on  [Feature](feature.md)  Abilities. If this function is not called in the  [OnStart\(const Want &want\)](abilitykit.md#ga4d016d42397f33c7710db8544581c757)  function for a  [Feature](feature.md) [Ability](ohos-ability.md), the  [Feature](feature.md) [Ability](ohos-ability.md)  will fail to start.

**Parameters:**

<a name="table1165499954084826"></a>
<table><thead align="left"><tr id="row122852329084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1884864326084826"><a name="p1884864326084826"></a><a name="p1884864326084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1829252446084826"><a name="p1829252446084826"></a><a name="p1829252446084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row991575334084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">entry</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the main entry, which is the class name of the <strong id="b753897700084826"><a name="b753897700084826"></a><a name="b753897700084826"></a><a href="ohos-abilityslice.md">AbilitySlice</a></strong> instance to start. </td>
</tr>
</tbody>
</table>

## SetUIContent\(\) \[1/2\]<a name="ga050a81cda49edb471594447f8f4cdaac"></a>

```
void OHOS::AbilitySlice::SetUIContent ([RootView](ohos-rootview.md) * rootView)
```

 **Description:**

Sets the UI layout for the host ability of this ability slice. 

You can call  **GetWindowRootView\(\)**  to create a layout and add controls.

**Parameters:**

<a name="table1899030605084826"></a>
<table><thead align="left"><tr id="row1601581194084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1674940809084826"><a name="p1674940809084826"></a><a name="p1674940809084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1228646333084826"><a name="p1228646333084826"></a><a name="p1228646333084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row214566105084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rootView</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the custom layout view you have created. </td>
</tr>
</tbody>
</table>

## SetUIContent\(\) \[2/2\]<a name="ga9b734c2ad8ad52f906d676f0c897a4aa"></a>

```
void OHOS::Ability::SetUIContent ([RootView](ohos-rootview.md) * rootView)
```

 **Description:**

Sets the UI layout for this ability. You can call  **GetWindowRootView\(\)**  to create a layout and add controls. 

**Parameters:**

<a name="table302042170084826"></a>
<table><thead align="left"><tr id="row820835500084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1895746812084826"><a name="p1895746812084826"></a><a name="p1895746812084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1913918789084826"><a name="p1913918789084826"></a><a name="p1913918789084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1440265219084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rootView</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the custom layout view you have created. </td>
</tr>
</tbody>
</table>

## SetWantData\(\)<a name="ga89a719b5f730bc5fde9f637a5ed630c9"></a>

```
bool SetWantData ([Want](want.md) * want, const void * data, uint16_t dataLength )
```

 **Description:**

Sets data to carry in a specified  **[Want](want.md)**  object for starting a particular ability. 

**Parameters:**

<a name="table188334966084826"></a>
<table><thead align="left"><tr id="row889715207084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p711274391084826"><a name="p711274391084826"></a><a name="p711274391084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p60431617084826"><a name="p60431617084826"></a><a name="p60431617084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1648451259084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1993271695084826"><a name="b1993271695084826"></a><a name="b1993271695084826"></a><a href="want.md">Want</a></strong> object to set. </td>
</tr>
<tr id="row919468022084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to set. </td>
</tr>
<tr id="row1004180691084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dataLength</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data length to set. The length must be the same as that of the data specified in <strong id="b1554687435084826"><a name="b1554687435084826"></a><a name="b1554687435084826"></a>data</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the setting is successful; returns  **false**  otherwise. 



## SetWantElement\(\)<a name="ga65f4d2eab99497e496dcd493bd0d047e"></a>

```
bool SetWantElement ([Want](want.md) * want, [ElementName](elementname.md) element )
```

 **Description:**

Sets the  **element**  variable for a specified  **[Want](want.md)**  object. 

To start a specified ability, you should call this function to set the  [ElementName](elementname.md)  required for starting the ability.

**Parameters:**

<a name="table41764794084826"></a>
<table><thead align="left"><tr id="row2140412967084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p268842212084826"><a name="p268842212084826"></a><a name="p268842212084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p328716582084826"><a name="p328716582084826"></a><a name="p328716582084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1065041189084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b900791841084826"><a name="b900791841084826"></a><a name="b900791841084826"></a><a href="want.md">Want</a></strong> object to set. </td>
</tr>
<tr id="row1194824114084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="elementname.md">ElementName</a> containing information required for starting the ability.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the setting is successful; returns  **false**  otherwise. 



## SetWantSvcIdentity\(\)<a name="gab8e5fac952fc6407f20cd9b7185d3a65"></a>

```
bool SetWantSvcIdentity ([Want](want.md) * want, SvcIdentity sid )
```

 **Description:**

Sets the  **sid**  member variable for a specified  **[Want](want.md)**  object. 

When starting an ability, you should call this function to set an  **SvcIdentity**  object if a callback needs to be invoked after the ability is started successfully.

**Parameters:**

<a name="table572002187084826"></a>
<table><thead align="left"><tr id="row1591334474084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1397106141084826"><a name="p1397106141084826"></a><a name="p1397106141084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1584519936084826"><a name="p1584519936084826"></a><a name="p1584519936084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1942996133084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b879746033084826"><a name="b879746033084826"></a><a name="b879746033084826"></a><a href="want.md">Want</a></strong> object to set. </td>
</tr>
<tr id="row685518785084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b893321005084826"><a name="b893321005084826"></a><a name="b893321005084826"></a>SvcIdentity</strong> object to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the setting is successful; returns  **false**  otherwise. 



## StartAbility\(\) \[1/2\]<a name="gab11d708d5eaa1eca54828fa88625681a"></a>

```
int OHOS::AbilityContext::StartAbility (const [Want](want.md) & want)
```

 **Description:**

Starts an  [Ability](ohos-ability.md)  based on the specified  [Want](want.md)  information. 

**Parameters:**

<a name="table668993576084826"></a>
<table><thead align="left"><tr id="row51153604084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1248899895084826"><a name="p1248899895084826"></a><a name="p1248899895084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1474436812084826"><a name="p1474436812084826"></a><a name="p1474436812084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row271327458084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure containing information about the ability to start. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## StartAbility\(\) \[2/2\]<a name="gae79800c4077afdc2851d5a74d8964111"></a>

```
int StartAbility (const [Want](want.md) * want)
```

 **Description:**

Starts an ability based on the specified  [Want](want.md)  information. 

**Parameters:**

<a name="table170144545084826"></a>
<table><thead align="left"><tr id="row505881632084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p277017768084826"><a name="p277017768084826"></a><a name="p277017768084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p128989750084826"><a name="p128989750084826"></a><a name="p128989750084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row782986196084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure containing information about the ability to start. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if this function is successfully called; returns another value otherwise. 



## StopAbility\(\) \[1/2\]<a name="gadc670d5f6df0d485ee3062b70b3ffe99"></a>

```
int OHOS::AbilityContext::StopAbility (const [Want](want.md) & want)
```

 **Description:**

Stops an  [Ability](ohos-ability.md)  based on the specified  [Want](want.md)  information. 

This function takes effect only on  [Service](service.md)  abilities.

**Parameters:**

<a name="table251826298084826"></a>
<table><thead align="left"><tr id="row2066735937084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2124423487084826"><a name="p2124423487084826"></a><a name="p2124423487084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p289943859084826"><a name="p289943859084826"></a><a name="p289943859084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1683193855084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure containing information about the ability to stop. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## StopAbility\(\) \[2/2\]<a name="gaba99bbd4ff6da4fb072338f5ce95e6ae"></a>

```
int StopAbility (const [Want](want.md) * want)
```

 **Description:**

Stops an ability based on the specified  [Want](want.md)  information. 

This function takes effect only on  [Service](service.md)  abilities.

**Parameters:**

<a name="table862059183084826"></a>
<table><thead align="left"><tr id="row1922228483084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1140583862084826"><a name="p1140583862084826"></a><a name="p1140583862084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p265735715084826"><a name="p265735715084826"></a><a name="p265735715084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row234675245084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure containing information about the ability to stop. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if this function is successfully called; returns another value otherwise. 



## Terminate\(\)<a name="gaf424e47c7980ff92093c6b7b75888639"></a>

```
void OHOS::AbilitySlice::Terminate ()
```

 **Description:**

Destroys this ability slice. 

This ability slice can call this function to destroy itself. If the ability slice to destroy is the only running one in the host ability, the host ability will also be destroyed. Otherwise, the host ability will not be affected. 

## TerminateAbility\(\)<a name="gac4a36f03c60fcbeca3b47192ccab1d24"></a>

```
int OHOS::AbilityContext::TerminateAbility ()
```

 **Description:**

Destroys this  [Ability](ohos-ability.md). 

This function can be called only by this ability.

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## WantParseUri\(\)<a name="ga43226d0858faa92e83bea33aaf4b614c"></a>

```
[Want](want.md)* WantParseUri (const char * uri)
```

 **Description:**

Converts a specified character string into a  **[Want](want.md)**  object. 

**Parameters:**

<a name="table265926381084826"></a>
<table><thead align="left"><tr id="row1104318665084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1885381001084826"><a name="p1885381001084826"></a><a name="p1885381001084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1324622337084826"><a name="p1324622337084826"></a><a name="p1324622337084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1647357916084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">uri</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the character string to convert.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the converted  **[Want](want.md)**  object if the operation is successful; returns  **nullptr**  otherwise. 



## WantToUri\(\)<a name="ga31adc60981c10b22d0e9bbdc7126d17c"></a>

```
const char* WantToUri ([Want](want.md) want)
```

 **Description:**

Converts a specified  **[Want](want.md)**  object into a character string. 

**Parameters:**

<a name="table995744370084826"></a>
<table><thead align="left"><tr id="row1384003424084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p218605391084826"><a name="p218605391084826"></a><a name="p218605391084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1512458671084826"><a name="p1512458671084826"></a><a name="p1512458671084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2117893746084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b674064124084826"><a name="b674064124084826"></a><a name="b674064124084826"></a><a href="want.md">Want</a></strong> object to convert.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the converted character string if the operation is successful; returns  **nullptr**  otherwise. 



## **Variable Documentation**<a name="section464589331084826"></a>

## OnAbilityConnectDone<a name="ga3b9bfacbcf1564c83cffbfff7889998a"></a>

```
void(* IAbilityConnection::OnAbilityConnectDone) ([ElementName](elementname.md) *elementName, SvcIdentity *serviceSid, int resultCode, void *data)
```

 **Description:**

Called when a client is connected to a  [Service](service.md)  ability. 

This callback is invoked to receive the connection result after a client is connected to a  [Service](service.md)  ability.

**Parameters:**

<a name="table1715844585084826"></a>
<table><thead align="left"><tr id="row2063992169084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p623143633084826"><a name="p623143633084826"></a><a name="p623143633084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1482129589084826"><a name="p1482129589084826"></a><a name="p1482129589084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row649098413084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">elementName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the information about the connected <a href="service.md">Service</a> ability. </td>
</tr>
<tr id="row2030545530084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">serviceSid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the remote proxy object of the <a href="service.md">Service</a> ability. </td>
</tr>
<tr id="row416533819084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">resultCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the connection result code. The value <strong id="b318371812084826"><a name="b318371812084826"></a><a name="b318371812084826"></a>0</strong> indicates a successful connection, and any other value indicates a connection failure. </td>
</tr>
<tr id="row2055112374084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data stored during the connection. </td>
</tr>
</tbody>
</table>

## OnAbilityDisconnectDone<a name="gaba7cf0abb517890ef1a3949e398aaf1d"></a>

```
void(* IAbilityConnection::OnAbilityDisconnectDone) ([ElementName](elementname.md) *elementName, int resultCode, void *data)
```

 **Description:**

Called after all connections to a  [Service](service.md)  ability are disconnected. 

This callback is invoked to receive the disconnection result after the connected  [Service](service.md)  ability crashes or is killed. If the  [Service](service.md)  ability exits unexpectedly, all its connections are disconnected, and each ability previously connected to it will call  **OnAbilityDisconnectDone\(ElementName \*elementName, int resultCode, void \*data\)**.

**Parameters:**

<a name="table1155960212084826"></a>
<table><thead align="left"><tr id="row349075666084826"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p391080385084826"><a name="p391080385084826"></a><a name="p391080385084826"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p494853109084826"><a name="p494853109084826"></a><a name="p494853109084826"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1769297326084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">elementName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the information about the disconnected <a href="service.md">Service</a> ability. </td>
</tr>
<tr id="row1767884180084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">resultCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the disconnection result code. The value <strong id="b1831434892084826"><a name="b1831434892084826"></a><a name="b1831434892084826"></a>0</strong> indicates a successful disconnection, and any other value indicates a disconnection failure. </td>
</tr>
<tr id="row1318714727084826"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data stored during the connection. </td>
</tr>
</tbody>
</table>

