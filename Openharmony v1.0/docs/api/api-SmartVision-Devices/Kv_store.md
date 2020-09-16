# Kv\_store<a name="ZH-CN_TOPIC_0000001054918111"></a>

## **Overview**<a name="section593471048093523"></a>

Provides functions for obtaining, setting, and deleting a key-value pair. 

Key-value pairs can be permanently stored in the file system. If  [FEATURE\_KV\_CACHE](Utils_config.md#gad3d71669516ef0bb50e2b105507a6b29)  is enabled, key-value pairs can be stored in the cache. For details about cache specifications, see  [MAX\_CACHE\_SIZE](Utils_config.md#ga6c8469dfe973ac952cf40394bd2c160b). For details about the number of key-value pairs that can be stored in an application, see  [MAX\_KV\_SUM](Utils_config.md#ga4f258bd7d7d52c6770cce77f3e16ce72). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section317679160093523"></a>

## Files<a name="files"></a>

<a name="table1898070112093523"></a>
<table><thead align="left"><tr id="row81307356093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p116958531093523"><a name="p116958531093523"></a><a name="p116958531093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p776670871093523"><a name="p776670871093523"></a><a name="p776670871093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1372341472093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p423909580093523"><a name="p423909580093523"></a><a name="p423909580093523"></a><a href="kv_store-h.md">kv_store.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550572442093523"><a name="p1550572442093523"></a><a name="p1550572442093523"></a>Provides functions for obtaining, setting, and deleting a key-value pair. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2124430438093523"></a>
<table><thead align="left"><tr id="row823031703093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1509346248093523"><a name="p1509346248093523"></a><a name="p1509346248093523"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2057405299093523"><a name="p2057405299093523"></a><a name="p2057405299093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1417798153093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49307475093523"><a name="p49307475093523"></a><a name="p49307475093523"></a><a href="Kv_store.md#ga6e7d17b85aeb91c0cfa912ac141d41eb">UtilsGetValue</a> (const char *key, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p760301107093523"><a name="p760301107093523"></a><a name="p760301107093523"></a>int&nbsp;</p>
<p id="p864377394093523"><a name="p864377394093523"></a><a name="p864377394093523"></a>Obtains the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row716465020093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116782841093523"><a name="p2116782841093523"></a><a name="p2116782841093523"></a><a href="Kv_store.md#ga32e7222aed175357499f5ced0e85775f">UtilsSetValue</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699128253093523"><a name="p699128253093523"></a><a name="p699128253093523"></a>int&nbsp;</p>
<p id="p1288990351093523"><a name="p1288990351093523"></a><a name="p1288990351093523"></a>Adds or updates the value matching a specified key in the file system or cache. </p>
</td>
</tr>
<tr id="row233503164093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1246843873093523"><a name="p1246843873093523"></a><a name="p1246843873093523"></a><a href="Kv_store.md#ga803cc2bcb5206b0378ec25df7a179834">UtilsDeleteValue</a> (const char *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071196472093523"><a name="p2071196472093523"></a><a name="p2071196472093523"></a>int&nbsp;</p>
<p id="p1007290304093523"><a name="p1007290304093523"></a><a name="p1007290304093523"></a>Deletes the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row1184754742093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p807683216093523"><a name="p807683216093523"></a><a name="p807683216093523"></a><a href="Kv_store.md#gaebe12bab9a2e181d1fea1095a5ce4d5a">ClearKVCache</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p952916897093523"><a name="p952916897093523"></a><a name="p952916897093523"></a>int&nbsp;</p>
<p id="p778710835093523"><a name="p778710835093523"></a><a name="p778710835093523"></a>Clears all key-value pairs from the cache. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1440649253093523"></a>

## **Function Documentation**<a name="section1113495519093523"></a>

## ClearKVCache\(\)<a name="gaebe12bab9a2e181d1fea1095a5ce4d5a"></a>

```
int ClearKVCache (void )
```

 **Description:**

Clears all key-value pairs from the cache. 

**Attention:**

This function is available only if  [FEATURE\_KV\_CACHE](Utils_config.md#gad3d71669516ef0bb50e2b105507a6b29)  is enabled. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## UtilsDeleteValue\(\)<a name="ga803cc2bcb5206b0378ec25df7a179834"></a>

```
int UtilsDeleteValue (const char * key)
```

 **Description:**

Deletes the value matching a specified key from the file system or cache. 

**Parameters:**

<a name="table874459384093523"></a>
<table><thead align="left"><tr id="row1250017617093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p985174083093523"><a name="p985174083093523"></a><a name="p985174083093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p202472848093523"><a name="p202472848093523"></a><a name="p202472848093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1208464879093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key whose value is to be deleted. It allows only lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



## UtilsGetValue\(\)<a name="ga6e7d17b85aeb91c0cfa912ac141d41eb"></a>

```
int UtilsGetValue (const char * key, char * value, unsigned int len )
```

 **Description:**

Obtains the value matching a specified key from the file system or cache. 

**Parameters:**

<a name="table1704156806093523"></a>
<table><thead align="left"><tr id="row12309113093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1746431943093523"><a name="p1746431943093523"></a><a name="p1746431943093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2127740613093523"><a name="p2127740613093523"></a><a name="p2127740613093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row986534756093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key to be indexed. It allows only lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row2092775733093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer for storing the value that matches the key. This is an output parameter. </td>
</tr>
<tr id="row835142831093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the value space in the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the length of the value if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios; returns  **0**  if the value is obtained from the cache. 



## UtilsSetValue\(\)<a name="ga32e7222aed175357499f5ced0e85775f"></a>

```
int UtilsSetValue (const char * key, const char * value )
```

 **Description:**

Adds or updates the value matching a specified key in the file system or cache. 

**Parameters:**

<a name="table1787136669093523"></a>
<table><thead align="left"><tr id="row2083405762093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1384099041093523"><a name="p1384099041093523"></a><a name="p1384099041093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p946705848093523"><a name="p946705848093523"></a><a name="p946705848093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1964164400093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key whose value is to be added or updated. It allows only lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row946893244093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to be added or updated. Its length cannot exceed 128 bytes (including the end-of-text character in the string). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



