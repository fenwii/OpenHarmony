# HiLog<a name="ZH-CN_TOPIC_0000001055198086"></a>

## **Overview**<a name="section1287276398084827"></a>

Provides logging functions. 

For example, you can use these functions to output logs of the specified log type, service domain, log tag, and log level.

**Since:**

1.1

**Version:**

1.0

## **Summary**<a name="section1874268711084827"></a>

## Macros<a name="define-members"></a>

<a name="table310729094084827"></a>
<table><thead align="left"><tr id="row1597104279084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p360427726084827"><a name="p360427726084827"></a><a name="p360427726084827"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p781327426084827"><a name="p781327426084827"></a><a name="p781327426084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row494168097084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087081212084827"><a name="p2087081212084827"></a><a name="p2087081212084827"></a><a href="HiLog.md#ga95a1d08c807e0aada863b5298a61d08d">LOG_DOMAIN</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p432230658084827"><a name="p432230658084827"></a><a name="p432230658084827"></a>Defines the service domain for a log file. </p>
</td>
</tr>
<tr id="row1457448999084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346078490084827"><a name="p346078490084827"></a><a name="p346078490084827"></a><a href="HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6">LOG_TAG</a>&nbsp;&nbsp;&nbsp;<a href="UTILS.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4">NULL</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35795194084827"><a name="p35795194084827"></a><a name="p35795194084827"></a>Defines a string constant used to identify the class, file, or service behavior. </p>
</td>
</tr>
<tr id="row2089815523084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1984128748084827"><a name="p1984128748084827"></a><a name="p1984128748084827"></a><a href="HiLog.md#ga131e23e4dd8a01f7871851ac23ce3cfc">HILOG_DEBUG</a>(type, ...)&nbsp;&nbsp;&nbsp;((void)<a href="HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f">HiLogPrint</a>(LOG_CORE, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ab9f002c6ffbfd511da8090213227454e">LOG_DEBUG</a>, <a href="HiLog.md#ga95a1d08c807e0aada863b5298a61d08d">LOG_DOMAIN</a>, <a href="HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6">LOG_TAG</a>, __VA_ARGS__))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p476398349084827"><a name="p476398349084827"></a><a name="p476398349084827"></a>Outputs debug logs. This is a function-like macro. </p>
</td>
</tr>
<tr id="row1192149447084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1525739635084827"><a name="p1525739635084827"></a><a name="p1525739635084827"></a><a href="HiLog.md#ga54d6ebdb0a272e51e3dc2e5cc9775677">HILOG_INFO</a>(type, ...)&nbsp;&nbsp;&nbsp;((void)<a href="HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f">HiLogPrint</a>(LOG_CORE, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9a6e98ff471e3ce6c4ef2d75c37ee51837">LOG_INFO</a>, <a href="HiLog.md#ga95a1d08c807e0aada863b5298a61d08d">LOG_DOMAIN</a>, <a href="HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6">LOG_TAG</a>, __VA_ARGS__))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124421452084827"><a name="p1124421452084827"></a><a name="p1124421452084827"></a>Outputs informational logs. This is a function-like macro. </p>
</td>
</tr>
<tr id="row1216563751084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933426784084827"><a name="p1933426784084827"></a><a name="p1933426784084827"></a><a href="HiLog.md#gab6e05f702fa067419ab6d2b241f70d96">HILOG_WARN</a>(type, ...)&nbsp;&nbsp;&nbsp;((void)<a href="HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f">HiLogPrint</a>(LOG_CORE, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ac8041ffa22bc823d4726701cdb13fc13">LOG_WARN</a>, <a href="HiLog.md#ga95a1d08c807e0aada863b5298a61d08d">LOG_DOMAIN</a>, <a href="HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6">LOG_TAG</a>, __VA_ARGS__))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325637840084827"><a name="p1325637840084827"></a><a name="p1325637840084827"></a>Outputs warning logs. This is a function-like macro. </p>
</td>
</tr>
<tr id="row245554825084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p157471024084827"><a name="p157471024084827"></a><a name="p157471024084827"></a><a href="HiLog.md#ga90b1019911094577057834ab3208e454">HILOG_ERROR</a>(type, ...)&nbsp;&nbsp;&nbsp;((void)<a href="HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f">HiLogPrint</a>(LOG_CORE, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9a230506cce5c68c3bac5a821c42ed3473">LOG_ERROR</a>, <a href="HiLog.md#ga95a1d08c807e0aada863b5298a61d08d">LOG_DOMAIN</a>, <a href="HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6">LOG_TAG</a>, __VA_ARGS__))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577267807084827"><a name="p577267807084827"></a><a name="p577267807084827"></a>Outputs error logs. This is a function-like macro. </p>
</td>
</tr>
<tr id="row251719571084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489444690084827"><a name="p1489444690084827"></a><a name="p1489444690084827"></a><a href="HiLog.md#gac76a098606b7f1e2f73b14158abe0b25">HILOG_FATAL</a>(type, ...)&nbsp;&nbsp;&nbsp;((void)<a href="HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f">HiLogPrint</a>(LOG_CORE, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ac630750884d91cb9767ef2200bbb048b">LOG_FATAL</a>, <a href="HiLog.md#ga95a1d08c807e0aada863b5298a61d08d">LOG_DOMAIN</a>, <a href="HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6">LOG_TAG</a>, __VA_ARGS__))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313270110084827"><a name="p313270110084827"></a><a name="p313270110084827"></a>Outputs fatal logs. This is a function-like macro. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1850328428084827"></a>
<table><thead align="left"><tr id="row291960135084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p671438605084827"><a name="p671438605084827"></a><a name="p671438605084827"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p205870319084827"><a name="p205870319084827"></a><a name="p205870319084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2019900190084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112840239084827"><a name="p112840239084827"></a><a name="p112840239084827"></a><a href="HiLog.md#ga125ab0014dcc2b2152e0be2e39e31b9e">HiLogModuleType</a> { &nbsp;&nbsp;<a href="HiLog.md#gga125ab0014dcc2b2152e0be2e39e31b9ea6eef5ce03266c8d2f0ef2ff63e86230b">HILOG_MODULE_HIVIEW</a> = 0, <a href="HiLog.md#gga125ab0014dcc2b2152e0be2e39e31b9eac1f60668255cfb6314d4fb8083f50ea3">HILOG_MODULE_SAMGR</a>, <a href="HiLog.md#gga125ab0014dcc2b2152e0be2e39e31b9ea7dd731467818fc45a8474442af2f3302">HILOG_MODULE_ACE</a>, <a href="HiLog.md#gga125ab0014dcc2b2152e0be2e39e31b9ea7194cace682dfd6f7cce00a6a7f96ac3">HILOG_MODULE_APP</a>, &nbsp;&nbsp;<a href="HiLog.md#gga125ab0014dcc2b2152e0be2e39e31b9ea746b8468c1657750bf0d5487a3cbbb33">HILOG_MODULE_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2056166851084827"><a name="p2056166851084827"></a><a name="p2056166851084827"></a>Enumerates logging module types. </p>
</td>
</tr>
<tr id="row42520667084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p212367100084827"><a name="p212367100084827"></a><a name="p212367100084827"></a><a href="HiLog.md#gaf67907baa897e9fb84df0cb89795b87c">LogType</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053177400084827"><a name="p2053177400084827"></a><a name="p2053177400084827"></a>Enumerates log types. </p>
</td>
</tr>
<tr id="row907974405084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2130828095084827"><a name="p2130828095084827"></a><a name="p2130828095084827"></a><a href="HiLog.md#gaca1fd1d8935433e6ba2e3918214e07f9">LogLevel</a> { &nbsp;&nbsp;<a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ab9f002c6ffbfd511da8090213227454e">LOG_DEBUG</a> = 3, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9a6e98ff471e3ce6c4ef2d75c37ee51837">LOG_INFO</a> = 4, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ac8041ffa22bc823d4726701cdb13fc13">LOG_WARN</a> = 5, <a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9a230506cce5c68c3bac5a821c42ed3473">LOG_ERROR</a> = 6, &nbsp;&nbsp;<a href="HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ac630750884d91cb9767ef2200bbb048b">LOG_FATAL</a> = 7 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p889425769084827"><a name="p889425769084827"></a><a name="p889425769084827"></a>Enumerates log levels. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table164528313084827"></a>
<table><thead align="left"><tr id="row1004807576084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p600572699084827"><a name="p600572699084827"></a><a name="p600572699084827"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1685310778084827"><a name="p1685310778084827"></a><a name="p1685310778084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row746524058084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1468624123084827"><a name="p1468624123084827"></a><a name="p1468624123084827"></a><a href="HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f">HiLogPrint</a> (<a href="HiLog.md#gaf67907baa897e9fb84df0cb89795b87c">LogType</a> type, <a href="HiLog.md#gaca1fd1d8935433e6ba2e3918214e07f9">LogLevel</a> level, unsigned int domain, const char *tag, const char *fmt,...) __attribute__((format(os_log</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715696236084827"><a name="p1715696236084827"></a><a name="p1715696236084827"></a>int&nbsp;</p>
<p id="p1106796328084827"><a name="p1106796328084827"></a><a name="p1106796328084827"></a>Outputs logs. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section247168304084827"></a>

## **Macro Definition Documentation**<a name="section601644983084827"></a>

## HILOG\_DEBUG<a name="ga131e23e4dd8a01f7871851ac23ce3cfc"></a>

```
#define HILOG_DEBUG( type,  ... )   ((void)[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f)(LOG_CORE, [LOG_DEBUG](HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ab9f002c6ffbfd511da8090213227454e), [LOG_DOMAIN](HiLog.md#ga95a1d08c807e0aada863b5298a61d08d), [LOG_TAG](HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6), __VA_ARGS__))
```

 **Description:**

Outputs debug logs. This is a function-like macro. 

Before calling this function, define the log service domain and log tag. Generally, you need to define them at the beginning of the source file. 

**Parameters:**

<a name="table342658881084827"></a>
<table><thead align="left"><tr id="row1678536392084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2008776417084827"><a name="p2008776417084827"></a><a name="p2008776417084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1493622621084827"><a name="p1493622621084827"></a><a name="p1493622621084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row417851097084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log type. The type for third-party applications is defined by <strong id="b1452329828084827"><a name="b1452329828084827"></a><a name="b1452329828084827"></a>LOG_APP</strong>. </td>
</tr>
<tr id="row1266446706084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fmt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the format string, which is an enhancement of a printf format string and supports the privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each parameter. </td>
</tr>
<tr id="row875858090084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">...</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a list of parameters. The number and type of parameters must map onto the format specifiers in the format string. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  or a larger value if the operation is successful; returns a value smaller than  **0**  otherwise. 

**See also:**

[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f) 

## HILOG\_ERROR<a name="ga90b1019911094577057834ab3208e454"></a>

```
#define HILOG_ERROR( type,  ... )   ((void)[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f)(LOG_CORE, [LOG_ERROR](HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9a230506cce5c68c3bac5a821c42ed3473), [LOG_DOMAIN](HiLog.md#ga95a1d08c807e0aada863b5298a61d08d), [LOG_TAG](HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6), __VA_ARGS__))
```

 **Description:**

Outputs error logs. This is a function-like macro. 

Before calling this function, define the log service domain and log tag. Generally, you need to define them at the beginning of the source file. 

**Parameters:**

<a name="table1328016281084827"></a>
<table><thead align="left"><tr id="row63496823084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p133184696084827"><a name="p133184696084827"></a><a name="p133184696084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p497802116084827"><a name="p497802116084827"></a><a name="p497802116084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row597599697084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log type. The type for third-party applications is defined by <strong id="b1457943210084827"><a name="b1457943210084827"></a><a name="b1457943210084827"></a>LOG_APP</strong>. </td>
</tr>
<tr id="row369424745084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fmt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the format string, which is an enhancement of a printf format string and supports the privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each parameter. </td>
</tr>
<tr id="row1729814713084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">...</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a list of parameters. The number and type of parameters must map onto the format specifiers in the format string. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  or a larger value if the operation is successful; returns a value smaller than  **0**  otherwise. 

**See also:**

[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f) 

## HILOG\_FATAL<a name="gac76a098606b7f1e2f73b14158abe0b25"></a>

```
#define HILOG_FATAL( type,  ... )   ((void)[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f)(LOG_CORE, [LOG_FATAL](HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ac630750884d91cb9767ef2200bbb048b), [LOG_DOMAIN](HiLog.md#ga95a1d08c807e0aada863b5298a61d08d), [LOG_TAG](HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6), __VA_ARGS__))
```

 **Description:**

Outputs fatal logs. This is a function-like macro. 

Before calling this function, define the log service domain and log tag. Generally, you need to define them at the beginning of the source file. 

**Parameters:**

<a name="table1720158233084827"></a>
<table><thead align="left"><tr id="row1501940866084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2132286342084827"><a name="p2132286342084827"></a><a name="p2132286342084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p431657838084827"><a name="p431657838084827"></a><a name="p431657838084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1613055158084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log type. The type for third-party applications is defined by <strong id="b2112058753084827"><a name="b2112058753084827"></a><a name="b2112058753084827"></a>LOG_APP</strong>. </td>
</tr>
<tr id="row926439810084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fmt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the format string, which is an enhancement of a printf format string and supports the privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each parameter. </td>
</tr>
<tr id="row858238183084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">...</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a list of parameters. The number and type of parameters must map onto the format specifiers in the format string. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  or a larger value if the operation is successful; returns a value smaller than  **0**  otherwise. 

**See also:**

[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f) 

## HILOG\_INFO<a name="ga54d6ebdb0a272e51e3dc2e5cc9775677"></a>

```
#define HILOG_INFO( type,  ... )   ((void)[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f)(LOG_CORE, [LOG_INFO](HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9a6e98ff471e3ce6c4ef2d75c37ee51837), [LOG_DOMAIN](HiLog.md#ga95a1d08c807e0aada863b5298a61d08d), [LOG_TAG](HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6), __VA_ARGS__))
```

 **Description:**

Outputs informational logs. This is a function-like macro. 

Before calling this function, define the log service domain and log tag. Generally, you need to define them at the beginning of the source file. 

**Parameters:**

<a name="table410774674084827"></a>
<table><thead align="left"><tr id="row517106689084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p21771485084827"><a name="p21771485084827"></a><a name="p21771485084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1802927426084827"><a name="p1802927426084827"></a><a name="p1802927426084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2019006136084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log type. The type for third-party applications is defined by <strong id="b722852449084827"><a name="b722852449084827"></a><a name="b722852449084827"></a>LOG_APP</strong>. </td>
</tr>
<tr id="row730545452084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fmt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the format string, which is an enhancement of a printf format string and supports the privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each parameter. </td>
</tr>
<tr id="row1224188890084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">...</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a list of parameters. The number and type of parameters must map onto the format specifiers in the format string. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  or a larger value if the operation is successful; returns a value smaller than  **0**  otherwise. 

**See also:**

[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f) 

## HILOG\_WARN<a name="gab6e05f702fa067419ab6d2b241f70d96"></a>

```
#define HILOG_WARN( type,  ... )   ((void)[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f)(LOG_CORE, [LOG_WARN](HiLog.md#ggaca1fd1d8935433e6ba2e3918214e07f9ac8041ffa22bc823d4726701cdb13fc13), [LOG_DOMAIN](HiLog.md#ga95a1d08c807e0aada863b5298a61d08d), [LOG_TAG](HiLog.md#ga7ce0df38eb467e59f209470c8f5ac4e6), __VA_ARGS__))
```

 **Description:**

Outputs warning logs. This is a function-like macro. 

Before calling this function, define the log service domain and log tag. Generally, you need to define them at the beginning of the source file. 

**Parameters:**

<a name="table2058944172084827"></a>
<table><thead align="left"><tr id="row1820236389084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p417644358084827"><a name="p417644358084827"></a><a name="p417644358084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2031018500084827"><a name="p2031018500084827"></a><a name="p2031018500084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1949269778084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log type. The type for third-party applications is defined by <strong id="b1422772181084827"><a name="b1422772181084827"></a><a name="b1422772181084827"></a>LOG_APP</strong>. </td>
</tr>
<tr id="row406823050084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fmt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the format string, which is an enhancement of a printf format string and supports the privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each parameter. </td>
</tr>
<tr id="row71363213084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">...</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a list of parameters. The number and type of parameters must map onto the format specifiers in the format string. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  or a larger value if the operation is successful; returns a value smaller than  **0**  otherwise. 

**See also:**

[HiLogPrint](HiLog.md#ga4c59c13fccc59c5821b23865fbc6380f) 

## LOG\_DOMAIN<a name="ga95a1d08c807e0aada863b5298a61d08d"></a>

```
#define LOG_DOMAIN   0
```

 **Description:**

Defines the service domain for a log file. 

The service domain is used to identify the subsystem and module of a service. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFFF. If the value is beyond the range, its significant bits are automatically truncated. The recommended format is 0xAAABB, where AAA indicates the subsystem and BB indicates the module. 

## LOG\_TAG<a name="ga7ce0df38eb467e59f209470c8f5ac4e6"></a>

```
#define LOG_TAG   [NULL](UTILS.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4)
```

 **Description:**

Defines a string constant used to identify the class, file, or service behavior. 

## **Enumeration Type Documentation**<a name="section839005125084827"></a>

## HiLogModuleType<a name="ga125ab0014dcc2b2152e0be2e39e31b9e"></a>

```
enum [HiLogModuleType](HiLog.md#ga125ab0014dcc2b2152e0be2e39e31b9e)
```

 **Description:**

Enumerates logging module types. 

The module type must be globally unique. A maximum of 64 module types can be defined.

<a name="table2026434072084827"></a>
<table><thead align="left"><tr id="row1219911279084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p442036558084827"><a name="p442036558084827"></a><a name="p442036558084827"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p122844742084827"><a name="p122844742084827"></a><a name="p122844742084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1535133220084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga125ab0014dcc2b2152e0be2e39e31b9ea6eef5ce03266c8d2f0ef2ff63e86230b"><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea6eef5ce03266c8d2f0ef2ff63e86230b"></a><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea6eef5ce03266c8d2f0ef2ff63e86230b"></a></strong>HILOG_MODULE_HIVIEW&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p280027297084827"><a name="p280027297084827"></a><a name="p280027297084827"></a>DFX </p>
 </td>
</tr>
<tr id="row2060924800084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga125ab0014dcc2b2152e0be2e39e31b9eac1f60668255cfb6314d4fb8083f50ea3"><a name="gga125ab0014dcc2b2152e0be2e39e31b9eac1f60668255cfb6314d4fb8083f50ea3"></a><a name="gga125ab0014dcc2b2152e0be2e39e31b9eac1f60668255cfb6314d4fb8083f50ea3"></a></strong>HILOG_MODULE_SAMGR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p602131848084827"><a name="p602131848084827"></a><a name="p602131848084827"></a>System Ability Manager </p>
 </td>
</tr>
<tr id="row1065924164084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga125ab0014dcc2b2152e0be2e39e31b9ea7dd731467818fc45a8474442af2f3302"><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea7dd731467818fc45a8474442af2f3302"></a><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea7dd731467818fc45a8474442af2f3302"></a></strong>HILOG_MODULE_ACE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1568512999084827"><a name="p1568512999084827"></a><a name="p1568512999084827"></a>Update </p>
 </td>
</tr>
<tr id="row2091650652084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga125ab0014dcc2b2152e0be2e39e31b9ea7194cace682dfd6f7cce00a6a7f96ac3"><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea7194cace682dfd6f7cce00a6a7f96ac3"></a><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea7194cace682dfd6f7cce00a6a7f96ac3"></a></strong>HILOG_MODULE_APP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121223202084827"><a name="p1121223202084827"></a><a name="p1121223202084827"></a>Third-party applications </p>
 </td>
</tr>
<tr id="row1602445119084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga125ab0014dcc2b2152e0be2e39e31b9ea746b8468c1657750bf0d5487a3cbbb33"><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea746b8468c1657750bf0d5487a3cbbb33"></a><a name="gga125ab0014dcc2b2152e0be2e39e31b9ea746b8468c1657750bf0d5487a3cbbb33"></a></strong>HILOG_MODULE_MAX&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1372799855084827"><a name="p1372799855084827"></a><a name="p1372799855084827"></a>Maximum number of modules </p>
 </td>
</tr>
</tbody>
</table>

## LogLevel<a name="gaca1fd1d8935433e6ba2e3918214e07f9"></a>

```
enum [LogLevel](HiLog.md#gaca1fd1d8935433e6ba2e3918214e07f9)
```

 **Description:**

Enumerates log levels. 

You are advised to select log levels based on their respective usage scenarios: 

 

<a name="table1865337280084827"></a>
<table><thead align="left"><tr id="row1139806334084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1832212840084827"><a name="p1832212840084827"></a><a name="p1832212840084827"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1787015858084827"><a name="p1787015858084827"></a><a name="p1787015858084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1783454580084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaca1fd1d8935433e6ba2e3918214e07f9ab9f002c6ffbfd511da8090213227454e"><a name="ggaca1fd1d8935433e6ba2e3918214e07f9ab9f002c6ffbfd511da8090213227454e"></a><a name="ggaca1fd1d8935433e6ba2e3918214e07f9ab9f002c6ffbfd511da8090213227454e"></a></strong>LOG_DEBUG&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405042248084827"><a name="p405042248084827"></a><a name="p405042248084827"></a>Debug level to be used by <a href="HiLog.md#ga131e23e4dd8a01f7871851ac23ce3cfc">HILOG_DEBUG</a> </p>
 </td>
</tr>
<tr id="row527818007084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaca1fd1d8935433e6ba2e3918214e07f9a6e98ff471e3ce6c4ef2d75c37ee51837"><a name="ggaca1fd1d8935433e6ba2e3918214e07f9a6e98ff471e3ce6c4ef2d75c37ee51837"></a><a name="ggaca1fd1d8935433e6ba2e3918214e07f9a6e98ff471e3ce6c4ef2d75c37ee51837"></a></strong>LOG_INFO&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2121325691084827"><a name="p2121325691084827"></a><a name="p2121325691084827"></a>Informational level to be used by <a href="HiLog.md#ga54d6ebdb0a272e51e3dc2e5cc9775677">HILOG_INFO</a> </p>
 </td>
</tr>
<tr id="row1761459427084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaca1fd1d8935433e6ba2e3918214e07f9ac8041ffa22bc823d4726701cdb13fc13"><a name="ggaca1fd1d8935433e6ba2e3918214e07f9ac8041ffa22bc823d4726701cdb13fc13"></a><a name="ggaca1fd1d8935433e6ba2e3918214e07f9ac8041ffa22bc823d4726701cdb13fc13"></a></strong>LOG_WARN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p465774437084827"><a name="p465774437084827"></a><a name="p465774437084827"></a>Warning level to be used by <a href="HiLog.md#gab6e05f702fa067419ab6d2b241f70d96">HILOG_WARN</a> </p>
 </td>
</tr>
<tr id="row1700369515084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaca1fd1d8935433e6ba2e3918214e07f9a230506cce5c68c3bac5a821c42ed3473"><a name="ggaca1fd1d8935433e6ba2e3918214e07f9a230506cce5c68c3bac5a821c42ed3473"></a><a name="ggaca1fd1d8935433e6ba2e3918214e07f9a230506cce5c68c3bac5a821c42ed3473"></a></strong>LOG_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327730145084827"><a name="p1327730145084827"></a><a name="p1327730145084827"></a>Error level to be used by <a href="HiLog.md#ga90b1019911094577057834ab3208e454">HILOG_ERROR</a> </p>
 </td>
</tr>
<tr id="row440800791084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaca1fd1d8935433e6ba2e3918214e07f9ac630750884d91cb9767ef2200bbb048b"><a name="ggaca1fd1d8935433e6ba2e3918214e07f9ac630750884d91cb9767ef2200bbb048b"></a><a name="ggaca1fd1d8935433e6ba2e3918214e07f9ac630750884d91cb9767ef2200bbb048b"></a></strong>LOG_FATAL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1927959394084827"><a name="p1927959394084827"></a><a name="p1927959394084827"></a>Fatal level to be used by <a href="HiLog.md#gac76a098606b7f1e2f73b14158abe0b25">HILOG_FATAL</a> </p>
 </td>
</tr>
</tbody>
</table>

## LogType<a name="gaf67907baa897e9fb84df0cb89795b87c"></a>

```
enum [LogType](HiLog.md#gaf67907baa897e9fb84df0cb89795b87c)
```

 **Description:**

Enumerates log types. 

Currently,  **LOG\_APP**  is available. 

## **Function Documentation**<a name="section1745233638084827"></a>

## HiLogPrint\(\)<a name="ga4c59c13fccc59c5821b23865fbc6380f"></a>

```
int HiLogPrint ([LogType](HiLog.md#gaf67907baa897e9fb84df0cb89795b87c) type, [LogLevel](HiLog.md#gaca1fd1d8935433e6ba2e3918214e07f9) level, unsigned int domain, const char * tag, const char * fmt,  ... )
```

 **Description:**

Outputs logs. 

You can use this function to output logs based on the specified log type, log level, service domain, log tag, and variable parameters determined by the format specifier and privacy identifier in the printf format.

**Parameters:**

<a name="table216133327084827"></a>
<table><thead align="left"><tr id="row753631955084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1401461885084827"><a name="p1401461885084827"></a><a name="p1401461885084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p926523287084827"><a name="p926523287084827"></a><a name="p926523287084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1063972814084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log type. The type for third-party applications is defined by <strong id="b699177403084827"><a name="b699177403084827"></a><a name="b699177403084827"></a>LOG_APP</strong>. </td>
</tr>
<tr id="row417439105084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">level</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log level, which can be <strong id="b198981689084827"><a name="b198981689084827"></a><a name="b198981689084827"></a>LOG_DEBUG</strong>, <strong id="b676262890084827"><a name="b676262890084827"></a><a name="b676262890084827"></a>LOG_INFO</strong>, <strong id="b246593418084827"><a name="b246593418084827"></a><a name="b246593418084827"></a>LOG_WARN</strong>, <strong id="b1020045040084827"><a name="b1020045040084827"></a><a name="b1020045040084827"></a>LOG_ERROR</strong>, and <strong id="b2086809510084827"><a name="b2086809510084827"></a><a name="b2086809510084827"></a>LOG_FATAL</strong>. </td>
</tr>
<tr id="row1294437284084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">domain</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the service domain of logs. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFFF. The recommended format is 0xAAABB, where AAA indicates the subsystem and BB indicates the module. </td>
</tr>
<tr id="row394419364084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tag</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the log tag, which is a string used to identify the class, file, or service behavior. </td>
</tr>
<tr id="row1915564046084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fmt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the format string, which is an enhancement of a printf format string and supports the privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each parameter. </td>
</tr>
<tr id="row1555026651084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">...</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a list of parameters. The number and type of parameters must map onto the format specifiers in the format string. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  or a larger value if the operation is successful; returns a value smaller than  **0**  otherwise. 



