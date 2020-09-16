# osal\_irq.h<a name="EN-US_TOPIC_0000001055518064"></a>

## **Overview**<a name="section1495226693093526"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Declares interrupt request \(IRQ\) interfaces and common IRQ trigger modes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1731476760093526"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table816742061093526"></a>
<table><thead align="left"><tr id="row1078491321093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1954525282093526"><a name="p1954525282093526"></a><a name="p1954525282093526"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p347864437093526"><a name="p347864437093526"></a><a name="p347864437093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1864391902093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1275343886093526"><a name="p1275343886093526"></a><a name="p1275343886093526"></a><a href="osal.md#gab671a9e177f622a98af9ca1bd93198eb">OsalIRQHandle</a>) (uint32_t irqId, void *dev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p895514354093526"><a name="p895514354093526"></a><a name="p895514354093526"></a> typedef uint32_t(* </p>
<p id="p1668063614093526"><a name="p1668063614093526"></a><a name="p1668063614093526"></a>Defines an IRQ type. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table338191407093526"></a>
<table><thead align="left"><tr id="row189569813093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p995667522093526"><a name="p995667522093526"></a><a name="p995667522093526"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p649928570093526"><a name="p649928570093526"></a><a name="p649928570093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1787093183093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p814441613093526"><a name="p814441613093526"></a><a name="p814441613093526"></a><a href="osal.md#ga78cd126b10424753db6f39f9b72ea124">OSAL_IRQ_TRIGGER_MODE</a> {   <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124aa0252cbf1f560b1d9951da4dfe896a1d">OSAL_IRQF_TRIGGER_NONE</a> = 0, <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124ab98297946a624d99a3fad6adac899f2c">OSAL_IRQF_TRIGGER_RISING</a> = 1, <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124a3088c6875fb44d05fd3a64a3d158295b">OSAL_IRQF_TRIGGER_FALLING</a> = 2, <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124a9a997189554c568f66dd994a9f9e203d">OSAL_IRQF_TRIGGER_HIGH</a> = 4,   <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124a7768ec0b5be5e88cfeb07dea96cd5865">OSAL_IRQF_TRIGGER_LOW</a> = 8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p385065924093526"><a name="p385065924093526"></a><a name="p385065924093526"></a>Enumerates interrupt trigger modes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1071017897093526"></a>
<table><thead align="left"><tr id="row1109452271093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2062141931093526"><a name="p2062141931093526"></a><a name="p2062141931093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1706525191093526"><a name="p1706525191093526"></a><a name="p1706525191093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1089929089093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1696559929093526"><a name="p1696559929093526"></a><a name="p1696559929093526"></a><a href="osal.md#gade084a1942c1672f2148ccf8f6c06331">OsalRegisterIrq</a> (uint32_t irqId, uint32_t config, <a href="osal.md#gab671a9e177f622a98af9ca1bd93198eb">OsalIRQHandle</a> handle, const char *name, void *dev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417775522093526"><a name="p417775522093526"></a><a name="p417775522093526"></a>int32_t </p>
<p id="p1667728089093526"><a name="p1667728089093526"></a><a name="p1667728089093526"></a>Registers an IRQ. </p>
</td>
</tr>
<tr id="row1602165270093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2059163434093526"><a name="p2059163434093526"></a><a name="p2059163434093526"></a><a href="osal.md#gade4ec4496eb07f1ff0610b53ba419dba">OsalUnregisterIrq</a> (uint32_t irqId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1290653203093526"><a name="p1290653203093526"></a><a name="p1290653203093526"></a>int32_t </p>
<p id="p1567335420093526"><a name="p1567335420093526"></a><a name="p1567335420093526"></a>Unregisters an IRQ. </p>
</td>
</tr>
<tr id="row2041175022093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584547079093526"><a name="p584547079093526"></a><a name="p584547079093526"></a><a href="osal.md#ga7f27c6171678ab8cf925660068ac38ff">OsalEnableIrq</a> (uint32_t irqId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893625939093526"><a name="p893625939093526"></a><a name="p893625939093526"></a>int32_t </p>
<p id="p1801038846093526"><a name="p1801038846093526"></a><a name="p1801038846093526"></a>Enables an IRQ. </p>
</td>
</tr>
<tr id="row1701068151093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p126128305093526"><a name="p126128305093526"></a><a name="p126128305093526"></a><a href="osal.md#gaf6ae039d209e46d45c683aeda3e7cd28">OsalDisableIrq</a> (uint32_t irqId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932167892093526"><a name="p1932167892093526"></a><a name="p1932167892093526"></a>int32_t </p>
<p id="p626282413093526"><a name="p626282413093526"></a><a name="p626282413093526"></a>Disables an IRQ. </p>
</td>
</tr>
</tbody>
</table>

