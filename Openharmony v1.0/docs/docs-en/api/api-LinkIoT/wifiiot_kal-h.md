# wifiiot\_kal.h<a name="EN-US_TOPIC_0000001055195064"></a>

## **Overview**<a name="section470708619090254"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the KAL interface functions. 

These functions are used to register the idle task and CPU tick callbacks. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1520833113090254"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table414821254090254"></a>
<table><thead align="left"><tr id="row1784319960090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p740782656090254"><a name="p740782656090254"></a><a name="p740782656090254"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1095900775090254"><a name="p1095900775090254"></a><a name="p1095900775090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1004274949090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973589052090254"><a name="p973589052090254"></a><a name="p973589052090254"></a><a href="wifiiot.md#ga8be54bbf12f538188db10aaaf4bdbdf9">TickIdleKalCallback</a>) (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376547943090254"><a name="p376547943090254"></a><a name="p376547943090254"></a>typedef void(* </p>
<p id="p1196839691090254"><a name="p1196839691090254"></a><a name="p1196839691090254"></a>Indicates the idle task and CPU tick callbacks. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2018264606090254"></a>
<table><thead align="left"><tr id="row1798411320090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1026325930090254"><a name="p1026325930090254"></a><a name="p1026325930090254"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1843108828090254"><a name="p1843108828090254"></a><a name="p1843108828090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1792903999090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265273396090254"><a name="p1265273396090254"></a><a name="p1265273396090254"></a><a href="wifiiot.md#ga08e802255973f1fe58cbe59f03e1e2a8">KalTickRegisterCallback</a> (<a href="wifiiot.md#ga8be54bbf12f538188db10aaaf4bdbdf9">TickIdleKalCallback</a> cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059778956090254"><a name="p1059778956090254"></a><a name="p1059778956090254"></a>void </p>
<p id="p671729634090254"><a name="p671729634090254"></a><a name="p671729634090254"></a>Registers the CPU tick callback. </p>
</td>
</tr>
<tr id="row292864368090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1222114961090254"><a name="p1222114961090254"></a><a name="p1222114961090254"></a><a href="wifiiot.md#ga2cb2a204b7f242f4b387896924883de2">KalThreadRegisterIdleCallback</a> (<a href="wifiiot.md#ga8be54bbf12f538188db10aaaf4bdbdf9">TickIdleKalCallback</a> cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p328699696090254"><a name="p328699696090254"></a><a name="p328699696090254"></a>void </p>
<p id="p220227996090254"><a name="p220227996090254"></a><a name="p220227996090254"></a>Registers the idle task callback. </p>
</td>
</tr>
</tbody>
</table>

