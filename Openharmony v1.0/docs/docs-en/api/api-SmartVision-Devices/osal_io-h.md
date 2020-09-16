# osal\_io.h<a name="EN-US_TOPIC_0000001055678068"></a>

## **Overview**<a name="section428040482093526"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Declares I/O interfaces. 

This file provides operations, such as reading data from and writing data into an I/O address space, remapping an I/O address space to its virtual address space, and unmapping an I/O virtual address associated with the physical address.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1039163540093526"></a>

## Macros<a name="define-members"></a>

<a name="table190469039093526"></a>
<table><thead align="left"><tr id="row1779970672093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1615172992093526"><a name="p1615172992093526"></a><a name="p1615172992093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p387252933093526"><a name="p387252933093526"></a><a name="p387252933093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1901884043093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p376041805093526"><a name="p376041805093526"></a><a name="p376041805093526"></a><a href="osal.md#ga48e1f404639550c229aee3ec35a06d79">OSAL_WRITEB</a>(value, address)   writeb(value, address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288077492093526"><a name="p1288077492093526"></a><a name="p1288077492093526"></a>Writes one byte of data into an I/O address space. </p>
</td>
</tr>
<tr id="row864202717093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617020137093526"><a name="p617020137093526"></a><a name="p617020137093526"></a><a href="osal.md#ga3358a86c6bbb6f02ab108964962f441f">OSAL_WRITEW</a>(value, address)   writew(value, address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374592629093526"><a name="p374592629093526"></a><a name="p374592629093526"></a>Writes a short integer into an I/O address space. </p>
</td>
</tr>
<tr id="row1372929390093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p110463917093526"><a name="p110463917093526"></a><a name="p110463917093526"></a><a href="osal.md#gaba47d67efad3ad9d1a33a35d2982bd49">OSAL_WRITEL</a>(value, address)   writel(value, address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419702826093526"><a name="p419702826093526"></a><a name="p419702826093526"></a>Writes an integer into an I/O address space. </p>
</td>
</tr>
<tr id="row1068585139093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p787309305093526"><a name="p787309305093526"></a><a name="p787309305093526"></a><a href="osal.md#ga3de1529efbdabd4fb2f144c6f48df70b">OSAL_READB</a>(address)   readb(address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p179849500093526"><a name="p179849500093526"></a><a name="p179849500093526"></a>Reads one byte of data from an I/O address space. </p>
</td>
</tr>
<tr id="row1694590374093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451208429093526"><a name="p1451208429093526"></a><a name="p1451208429093526"></a><a href="osal.md#ga8bd523f234f24415fe733addd113e60b">OSAL_READW</a>(address)   readw(address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135206069093526"><a name="p135206069093526"></a><a name="p135206069093526"></a>Reads a short integer from an I/O address space. </p>
</td>
</tr>
<tr id="row1023687216093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1977372155093526"><a name="p1977372155093526"></a><a name="p1977372155093526"></a><a href="osal.md#ga14ce14451b2484b2e268a38757237f41">OSAL_READL</a>(address)   readl(address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p940032863093526"><a name="p940032863093526"></a><a name="p940032863093526"></a>Reads an integer from an I/O address space. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table758465826093526"></a>
<table><thead align="left"><tr id="row1728421980093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p434399920093526"><a name="p434399920093526"></a><a name="p434399920093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2075244436093526"><a name="p2075244436093526"></a><a name="p2075244436093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1629480282093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p22373789093526"><a name="p22373789093526"></a><a name="p22373789093526"></a><a href="osal.md#ga281757438906600ef89a13362151d955">OsalIoRemap</a> (unsigned long phys_addr, unsigned long size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p460837631093526"><a name="p460837631093526"></a><a name="p460837631093526"></a>static void * </p>
<p id="p1906768333093526"><a name="p1906768333093526"></a><a name="p1906768333093526"></a>Remaps an I/O physical address to its virtual address. </p>
</td>
</tr>
<tr id="row2059635121093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1721845640093526"><a name="p1721845640093526"></a><a name="p1721845640093526"></a><a href="osal.md#ga0a845edb56df0a35beeea338dc5121aa">OsalIoUnmap</a> (void *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p544001242093526"><a name="p544001242093526"></a><a name="p544001242093526"></a>static void </p>
<p id="p1604352631093526"><a name="p1604352631093526"></a><a name="p1604352631093526"></a>Unmaps an I/O virtual address associated with the physical address. </p>
</td>
</tr>
</tbody>
</table>

