# osal\_timer.h<a name="ZH-CN_TOPIC_0000001055078115"></a>

## **Overview**<a name="section1870994479093526"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Declares timer types and interfaces. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1037124455093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table89940375093526"></a>
<table><thead align="left"><tr id="row309763686093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p191455963093526"><a name="p191455963093526"></a><a name="p191455963093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1276542208093526"><a name="p1276542208093526"></a><a name="p1276542208093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row868727425093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228665686093526"><a name="p228665686093526"></a><a name="p228665686093526"></a><a href="OsalTimer.md">OsalTimer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p981961793093526"><a name="p981961793093526"></a><a name="p981961793093526"></a>Describes a timer. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table377551050093526"></a>
<table><thead align="left"><tr id="row1641765431093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2135617258093526"><a name="p2135617258093526"></a><a name="p2135617258093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1538463449093526"><a name="p1538463449093526"></a><a name="p1538463449093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1204774168093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1126117850093526"><a name="p1126117850093526"></a><a name="p1126117850093526"></a><a href="OSAL.md#ga556360caa9ece72fcbbc6aef5fc648f1">OSAL_DECLARE_TIMER</a>(timer)&nbsp;&nbsp;&nbsp;<a href="OsalTimer.md">OsalTimer</a> timer</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p72501071093526"><a name="p72501071093526"></a><a name="p72501071093526"></a>Defines a timer macro. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1183128307093526"></a>
<table><thead align="left"><tr id="row388741668093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p822769755093526"><a name="p822769755093526"></a><a name="p822769755093526"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p511163394093526"><a name="p511163394093526"></a><a name="p511163394093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row903842177093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p69053713093526"><a name="p69053713093526"></a><a name="p69053713093526"></a><a href="OSAL.md#gaf3e7a12075b25df5971049d8cd77c25c">OsalTimerFunc</a>) (uintptr_t arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1652158200093526"><a name="p1652158200093526"></a><a name="p1652158200093526"></a> typedef void(*&nbsp;</p>
<p id="p185718772093526"><a name="p185718772093526"></a><a name="p185718772093526"></a>Describes a timer execution function type. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1281848753093526"></a>
<table><thead align="left"><tr id="row1200583708093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2074394930093526"><a name="p2074394930093526"></a><a name="p2074394930093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p137986723093526"><a name="p137986723093526"></a><a name="p137986723093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1956949844093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778400112093526"><a name="p778400112093526"></a><a name="p778400112093526"></a><a href="OSAL.md#ga879d9a437e1423021f95cb9341f0d6af">OsalTimerCreate</a> (<a href="OsalTimer.md">OsalTimer</a> *timer, uint32_t interval, <a href="OSAL.md#gaf3e7a12075b25df5971049d8cd77c25c">OsalTimerFunc</a> func, uintptr_t arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p201646993093526"><a name="p201646993093526"></a><a name="p201646993093526"></a>int32_t&nbsp;</p>
<p id="p1364168080093526"><a name="p1364168080093526"></a><a name="p1364168080093526"></a>Creates a timer. </p>
</td>
</tr>
<tr id="row164095846093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1566739570093526"><a name="p1566739570093526"></a><a name="p1566739570093526"></a><a href="OSAL.md#gab754f3522245e6b2f9ee1cdecae62b52">OsalTimerDelete</a> (<a href="OsalTimer.md">OsalTimer</a> *timer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601400963093526"><a name="p1601400963093526"></a><a name="p1601400963093526"></a>int32_t&nbsp;</p>
<p id="p1055756346093526"><a name="p1055756346093526"></a><a name="p1055756346093526"></a>Deletes a timer. </p>
</td>
</tr>
<tr id="row1869464049093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1656544771093526"><a name="p1656544771093526"></a><a name="p1656544771093526"></a><a href="OSAL.md#gaf2e49d5b01b49e5f64a7701da8667141">OsalTimerStartOnce</a> (<a href="OsalTimer.md">OsalTimer</a> *timer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1100153253093526"><a name="p1100153253093526"></a><a name="p1100153253093526"></a>int32_t&nbsp;</p>
<p id="p1770564991093526"><a name="p1770564991093526"></a><a name="p1770564991093526"></a>Starts a timer. </p>
</td>
</tr>
<tr id="row81008697093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527400658093526"><a name="p1527400658093526"></a><a name="p1527400658093526"></a><a href="OSAL.md#ga575e4f41359c737ab9690ab28838b99f">OsalTimerStartLoop</a> (<a href="OsalTimer.md">OsalTimer</a> *timer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1637415613093526"><a name="p1637415613093526"></a><a name="p1637415613093526"></a>int32_t&nbsp;</p>
<p id="p28970819093526"><a name="p28970819093526"></a><a name="p28970819093526"></a>Starts a periodic timer. </p>
</td>
</tr>
<tr id="row246787403093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1517224763093526"><a name="p1517224763093526"></a><a name="p1517224763093526"></a><a href="OSAL.md#ga49c2fe3f54d548fe5ec0d03a79691376">OsalTimerSetTimeout</a> (<a href="OsalTimer.md">OsalTimer</a> *timer, uint32_t interval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012634065093526"><a name="p1012634065093526"></a><a name="p1012634065093526"></a>int32_t&nbsp;</p>
<p id="p1489223050093526"><a name="p1489223050093526"></a><a name="p1489223050093526"></a>Sets the interval of a timer. </p>
</td>
</tr>
</tbody>
</table>

