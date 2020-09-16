# hdf\_io\_service\_if.h<a name="ZH-CN_TOPIC_0000001055518058"></a>

## **Overview**<a name="section2087263703093525"></a>

**Related Modules:**

[Core](Core.md)

**Description:**

Declares the structures defining driver service objects and event listeners, as well as the functions for obtaining a driver service object, dispatching a driver service call, and registering or unregistering an event listener. 

**Since:**

1.0

## **Summary**<a name="section1544679303093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1803405693093525"></a>
<table><thead align="left"><tr id="row619663730093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p508279954093525"><a name="p508279954093525"></a><a name="p508279954093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1511266878093525"><a name="p1511266878093525"></a><a name="p1511266878093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row309574442093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897574905093525"><a name="p897574905093525"></a><a name="p897574905093525"></a><a href="HdfDevEventlistener.md">HdfDevEventlistener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p167464633093525"><a name="p167464633093525"></a><a name="p167464633093525"></a>Defines a driver event listener object. </p>
</td>
</tr>
<tr id="row741690646093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p899400775093525"><a name="p899400775093525"></a><a name="p899400775093525"></a><a href="HdfIoDispatcher.md">HdfIoDispatcher</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075442381093525"><a name="p2075442381093525"></a><a name="p2075442381093525"></a>Defines a driver service call dispatcher. </p>
</td>
</tr>
<tr id="row544569376093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1508109323093525"><a name="p1508109323093525"></a><a name="p1508109323093525"></a><a href="HdfIoService.md">HdfIoService</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2038653863093525"><a name="p2038653863093525"></a><a name="p2038653863093525"></a>Defines a driver service object. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1088357162093525"></a>
<table><thead align="left"><tr id="row1191733093093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1659059184093525"><a name="p1659059184093525"></a><a name="p1659059184093525"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1386681085093525"><a name="p1386681085093525"></a><a name="p1386681085093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row382897056093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1362779265093525"><a name="p1362779265093525"></a><a name="p1362779265093525"></a><a href="Core.md#gae314b850ba4b0927007038cf8cc32580">OnEventReceived</a>) (void *priv, uint32_t id, struct <a href="HdfSBuf.md">HdfSBuf</a> *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526111774093525"><a name="p1526111774093525"></a><a name="p1526111774093525"></a>typedef int(*&nbsp;</p>
<p id="p578126877093525"><a name="p578126877093525"></a><a name="p578126877093525"></a>Called when a driver event occurs. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1898022409093525"></a>
<table><thead align="left"><tr id="row698066779093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1721626945093525"><a name="p1721626945093525"></a><a name="p1721626945093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p623829764093525"><a name="p623829764093525"></a><a name="p623829764093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1994641261093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148048190093525"><a name="p148048190093525"></a><a name="p148048190093525"></a><a href="Core.md#gac250f27d434eafce709a7e03411ef4d1">HdfIoServiceBind</a> (const char *serviceName, mode_t permission)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p104237592093525"><a name="p104237592093525"></a><a name="p104237592093525"></a>struct <a href="HdfIoService.md">HdfIoService</a> *&nbsp;</p>
<p id="p771593888093525"><a name="p771593888093525"></a><a name="p771593888093525"></a>Obtains a driver service object. </p>
</td>
</tr>
<tr id="row743734134093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p918367668093525"><a name="p918367668093525"></a><a name="p918367668093525"></a><a href="Core.md#gada2867af690aac9e6c3b2c8812b3037c">HdfIoServiceRecycle</a> (struct <a href="HdfIoService.md">HdfIoService</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p281509426093525"><a name="p281509426093525"></a><a name="p281509426093525"></a>void&nbsp;</p>
<p id="p165116629093525"><a name="p165116629093525"></a><a name="p165116629093525"></a>Destroys a specified driver service object to release resources if it is no longer required. </p>
</td>
</tr>
<tr id="row851598842093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453956779093525"><a name="p1453956779093525"></a><a name="p1453956779093525"></a><a href="Core.md#gaa7855b3930b5378954927548e5623663">HdfDeviceRegisterEventListener</a> (struct <a href="HdfIoService.md">HdfIoService</a> *target, struct <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p860066972093525"><a name="p860066972093525"></a><a name="p860066972093525"></a>int&nbsp;</p>
<p id="p1445536873093525"><a name="p1445536873093525"></a><a name="p1445536873093525"></a>Registers a custom <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> for listening for events reported by a specified driver service object. </p>
</td>
</tr>
<tr id="row1016349764093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799581470093525"><a name="p799581470093525"></a><a name="p799581470093525"></a><a href="Core.md#gab95668359f0b6a47f48c47541caed7fd">HdfDeviceUnregisterEventListener</a> (struct <a href="HdfIoService.md">HdfIoService</a> *target, struct <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1591502664093525"><a name="p1591502664093525"></a><a name="p1591502664093525"></a>int&nbsp;</p>
<p id="p1606733924093525"><a name="p1606733924093525"></a><a name="p1606733924093525"></a>Unregisters a previously registered <a href="HdfDevEventlistener.md">HdfDevEventlistener</a> to release resources if it is no longer required. </p>
</td>
</tr>
</tbody>
</table>

