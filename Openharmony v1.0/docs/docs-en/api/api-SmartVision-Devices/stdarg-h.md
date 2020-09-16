# stdarg.h<a name="EN-US_TOPIC_0000001055308039"></a>

## **Overview**<a name="section1367822294084832"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Provides functions and data structures, such as applying for and ending a variable-length argument list and obtaining an argument type. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section44891477084832"></a>

## Macros<a name="define-members"></a>

<a name="table1578931489084832"></a>
<table><thead align="left"><tr id="row979316951084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1969905467084832"><a name="p1969905467084832"></a><a name="p1969905467084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p556548738084832"><a name="p556548738084832"></a><a name="p556548738084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row401913439084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p281237105084832"><a name="p281237105084832"></a><a name="p281237105084832"></a><a href="utils.md#gaa0628ab596c3d7e78f5e08c2d98e24da">va_start</a>(v, l)   __builtin_va_start(v,l)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1381109055084832"><a name="p1381109055084832"></a><a name="p1381109055084832"></a>Defines the start position of the variable-length argument list. </p>
</td>
</tr>
<tr id="row1301035759084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1767349447084832"><a name="p1767349447084832"></a><a name="p1767349447084832"></a><a href="utils.md#ga823b205416e9129825841b74c3bf8484">va_end</a>(v)   __builtin_va_end(v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989034284084832"><a name="p989034284084832"></a><a name="p989034284084832"></a>Ends a variable-length argument list. </p>
</td>
</tr>
<tr id="row62038322084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1811302566084832"><a name="p1811302566084832"></a><a name="p1811302566084832"></a><a href="utils.md#ga9cfd655f1203c9a345ddd90446f0bcee">va_arg</a>(v, l)   __builtin_va_arg(v,l)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449508136084832"><a name="p449508136084832"></a><a name="p449508136084832"></a>Obtains the next argument in the variable-length argument list. </p>
</td>
</tr>
<tr id="row1884256272084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1289152123084832"><a name="p1289152123084832"></a><a name="p1289152123084832"></a><a href="utils.md#ga23a32070bb5595761e7ed3884a84eb4a">va_copy</a>(d, s)   __builtin_va_copy(d,s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415189649084832"><a name="p415189649084832"></a><a name="p415189649084832"></a>Copies the previously initialized variable argument list <strong id="b612471070084832"><a name="b612471070084832"></a><a name="b612471070084832"></a>s</strong> to <strong id="b1163383689084832"><a name="b1163383689084832"></a><a name="b1163383689084832"></a>d</strong>. </p>
</td>
</tr>
</tbody>
</table>

