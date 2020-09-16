# Kv\_store<a name="EN-US_TOPIC_0000001054715049"></a>

## **Overview**<a name="section113896978191846"></a>

Provides functions for obtaining, setting, and deleting a key-value pair. 

Key-value pairs can be permanently stored in the file system. If  [FEATURE\_KV\_CACHE](utils_config.md#gad3d71669516ef0bb50e2b105507a6b29)  is enabled, key-value pairs can be stored in the cache. For details about cache specifications, see  [MAX\_CACHE\_SIZE](utils_config.md#ga6c8469dfe973ac952cf40394bd2c160b). For details about the number of key-value pairs that can be stored in an application, see  [MAX\_KV\_SUM](utils_config.md#ga4f258bd7d7d52c6770cce77f3e16ce72). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section64797286191846"></a>

## Files<a name="files"></a>

<a name="table631312252191846"></a>
<table><thead align="left"><tr id="row1317969192191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p853491129191846"><a name="p853491129191846"></a><a name="p853491129191846"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1691065680191846"><a name="p1691065680191846"></a><a name="p1691065680191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2026991670191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2104701827191846"><a name="p2104701827191846"></a><a name="p2104701827191846"></a><a href="kv_store-h.md">kv_store.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p695426248191846"><a name="p695426248191846"></a><a name="p695426248191846"></a>Provides functions for obtaining, setting, and deleting a key-value pair. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table443064751191846"></a>
<table><thead align="left"><tr id="row1408440465191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2106692517191846"><a name="p2106692517191846"></a><a name="p2106692517191846"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p142071045191846"><a name="p142071045191846"></a><a name="p142071045191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1470532809191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274503458191846"><a name="p1274503458191846"></a><a name="p1274503458191846"></a><a href="kv_store.md#ga6e7d17b85aeb91c0cfa912ac141d41eb">UtilsGetValue</a> (const char *key, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060800865191846"><a name="p1060800865191846"></a><a name="p1060800865191846"></a>int </p>
<p id="p137925662191846"><a name="p137925662191846"></a><a name="p137925662191846"></a>Obtains the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row310590851191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1592840664191846"><a name="p1592840664191846"></a><a name="p1592840664191846"></a><a href="kv_store.md#ga32e7222aed175357499f5ced0e85775f">UtilsSetValue</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79371101191846"><a name="p79371101191846"></a><a name="p79371101191846"></a>int </p>
<p id="p1977818844191846"><a name="p1977818844191846"></a><a name="p1977818844191846"></a>Adds or updates the value matching a specified key in the file system or cache. </p>
</td>
</tr>
<tr id="row390654639191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648430121191846"><a name="p1648430121191846"></a><a name="p1648430121191846"></a><a href="kv_store.md#ga803cc2bcb5206b0378ec25df7a179834">UtilsDeleteValue</a> (const char *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p17612581191846"><a name="p17612581191846"></a><a name="p17612581191846"></a>int </p>
<p id="p895957757191846"><a name="p895957757191846"></a><a name="p895957757191846"></a>Deletes the value matching a specified key from the file system or cache. </p>
</td>
</tr>
<tr id="row424625219191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p891276486191846"><a name="p891276486191846"></a><a name="p891276486191846"></a><a href="kv_store.md#gaebe12bab9a2e181d1fea1095a5ce4d5a">ClearKVCache</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p835387577191846"><a name="p835387577191846"></a><a name="p835387577191846"></a>int </p>
<p id="p1549086329191846"><a name="p1549086329191846"></a><a name="p1549086329191846"></a>Clears all key-value pairs from the cache. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section289580228191846"></a>

## **Function Documentation**<a name="section1825019836191846"></a>

## ClearKVCache\(\)<a name="gaebe12bab9a2e181d1fea1095a5ce4d5a"></a>

```
int ClearKVCache (void )
```

 **Description:**

Clears all key-value pairs from the cache. 

**Attention:**

This function is available only if  [FEATURE\_KV\_CACHE](utils_config.md#gad3d71669516ef0bb50e2b105507a6b29)  is enabled. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## UtilsDeleteValue\(\)<a name="ga803cc2bcb5206b0378ec25df7a179834"></a>

```
int UtilsDeleteValue (const char * key)
```

 **Description:**

Deletes the value matching a specified key from the file system or cache. 

**Parameters:**

<a name="table1730489746191846"></a>
<table><thead align="left"><tr id="row1240795193191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2087199046191846"><a name="p2087199046191846"></a><a name="p2087199046191846"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p130877684191846"><a name="p130877684191846"></a><a name="p130877684191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1879498308191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key whose value is to be deleted. It allows only lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



## UtilsGetValue\(\)<a name="ga6e7d17b85aeb91c0cfa912ac141d41eb"></a>

```
int UtilsGetValue (const char * key, char * value, unsigned int len )
```

 **Description:**

Obtains the value matching a specified key from the file system or cache. 

**Parameters:**

<a name="table1847958804191846"></a>
<table><thead align="left"><tr id="row547793876191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1050426889191846"><a name="p1050426889191846"></a><a name="p1050426889191846"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p381107983191846"><a name="p381107983191846"></a><a name="p381107983191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row860807149191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key to be indexed. It allows only lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row4403956191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer for storing the value that matches the key. This is an output parameter. </td>
</tr>
<tr id="row2029730397191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the value space in the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the length of the value if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios; returns  **0**  if the value is obtained from the cache. 



## UtilsSetValue\(\)<a name="ga32e7222aed175357499f5ced0e85775f"></a>

```
int UtilsSetValue (const char * key, const char * value )
```

 **Description:**

Adds or updates the value matching a specified key in the file system or cache. 

**Parameters:**

<a name="table374320042191846"></a>
<table><thead align="left"><tr id="row1862089610191846"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1112333845191846"><a name="p1112333845191846"></a><a name="p1112333845191846"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p274851841191846"><a name="p274851841191846"></a><a name="p274851841191846"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row19044626191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key whose value is to be added or updated. It allows only lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row1269967808191846"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to be added or updated. Its length cannot exceed 128 bytes (including the end-of-text character in the string). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



