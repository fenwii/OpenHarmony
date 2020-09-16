# kv\_store.h<a name="ZH-CN_TOPIC_0000001055675016"></a>

## **Overview**<a name="section1181517300191849"></a>

**Related Modules:**

[Kv\_store](Kv_store.md)

**Description:**

Provides functions for obtaining, setting, and deleting a key-value pair. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section546131460191849"></a>

## Functions<a name="func-members"></a>

<a name="table120991609191849"></a>
<table><thead align="left"><tr id="row2010138619191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1567615331191849"><a name="p1567615331191849"></a><a name="p1567615331191849"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1548862712191849"><a name="p1548862712191849"></a><a name="p1548862712191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1477519391191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1291049549191849"><a name="p1291049549191849"></a><a name="p1291049549191849"></a><a href="Kv_store.md#ga6e7d17b85aeb91c0cfa912ac141d41eb">UtilsGetValue</a> (const char *key, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1002320909191849"><a name="p1002320909191849"></a><a name="p1002320909191849"></a>int&nbsp;</p>
<p id="p1221211069191849"><a name="p1221211069191849"></a><a name="p1221211069191849"></a>Obtains the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row587604163191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p444071453191849"><a name="p444071453191849"></a><a name="p444071453191849"></a><a href="Kv_store.md#ga32e7222aed175357499f5ced0e85775f">UtilsSetValue</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749875925191849"><a name="p1749875925191849"></a><a name="p1749875925191849"></a>int&nbsp;</p>
<p id="p759613673191849"><a name="p759613673191849"></a><a name="p759613673191849"></a>Adds or updates the value matching a specified key in the file system or cache. </p>
</td>
</tr>
<tr id="row574717620191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222394885191849"><a name="p222394885191849"></a><a name="p222394885191849"></a><a href="Kv_store.md#ga803cc2bcb5206b0378ec25df7a179834">UtilsDeleteValue</a> (const char *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705066652191849"><a name="p1705066652191849"></a><a name="p1705066652191849"></a>int&nbsp;</p>
<p id="p1381760924191849"><a name="p1381760924191849"></a><a name="p1381760924191849"></a>Deletes the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row2009513778191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p833866556191849"><a name="p833866556191849"></a><a name="p833866556191849"></a><a href="Kv_store.md#gaebe12bab9a2e181d1fea1095a5ce4d5a">ClearKVCache</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278150909191849"><a name="p1278150909191849"></a><a name="p1278150909191849"></a>int&nbsp;</p>
<p id="p1183134623191849"><a name="p1183134623191849"></a><a name="p1183134623191849"></a>Clears all key-value pairs from the cache. </p>
</td>
</tr>
</tbody>
</table>

