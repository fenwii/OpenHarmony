# kv\_store.h<a name="ZH-CN_TOPIC_0000001054598133"></a>

## **Overview**<a name="section2056011355093526"></a>

**Related Modules:**

[Kv\_store](Kv_store.md)

**Description:**

Provides functions for obtaining, setting, and deleting a key-value pair. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section215662945093526"></a>

## Functions<a name="func-members"></a>

<a name="table1365930524093526"></a>
<table><thead align="left"><tr id="row1156282946093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p85675766093526"><a name="p85675766093526"></a><a name="p85675766093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1948917368093526"><a name="p1948917368093526"></a><a name="p1948917368093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row106045953093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1170605543093526"><a name="p1170605543093526"></a><a name="p1170605543093526"></a><a href="Kv_store.md#ga6e7d17b85aeb91c0cfa912ac141d41eb">UtilsGetValue</a> (const char *key, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399071295093526"><a name="p1399071295093526"></a><a name="p1399071295093526"></a>int&nbsp;</p>
<p id="p1990597741093526"><a name="p1990597741093526"></a><a name="p1990597741093526"></a>Obtains the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row34719917093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236479000093526"><a name="p236479000093526"></a><a name="p236479000093526"></a><a href="Kv_store.md#ga32e7222aed175357499f5ced0e85775f">UtilsSetValue</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1795174666093526"><a name="p1795174666093526"></a><a name="p1795174666093526"></a>int&nbsp;</p>
<p id="p902571311093526"><a name="p902571311093526"></a><a name="p902571311093526"></a>Adds or updates the value matching a specified key in the file system or cache. </p>
</td>
</tr>
<tr id="row1610366144093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892065630093526"><a name="p892065630093526"></a><a name="p892065630093526"></a><a href="Kv_store.md#ga803cc2bcb5206b0378ec25df7a179834">UtilsDeleteValue</a> (const char *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p357158510093526"><a name="p357158510093526"></a><a name="p357158510093526"></a>int&nbsp;</p>
<p id="p667877869093526"><a name="p667877869093526"></a><a name="p667877869093526"></a>Deletes the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row1796615477093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789583879093526"><a name="p1789583879093526"></a><a name="p1789583879093526"></a><a href="Kv_store.md#gaebe12bab9a2e181d1fea1095a5ce4d5a">ClearKVCache</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p16311993093526"><a name="p16311993093526"></a><a name="p16311993093526"></a>int&nbsp;</p>
<p id="p38436260093526"><a name="p38436260093526"></a><a name="p38436260093526"></a>Clears all key-value pairs from the cache. </p>
</td>
</tr>
</tbody>
</table>

