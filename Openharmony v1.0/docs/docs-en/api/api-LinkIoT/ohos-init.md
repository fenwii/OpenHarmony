# OHOS Init<a name="EN-US_TOPIC_0000001055675012"></a>

## **Overview**<a name="section442648666191845"></a>

Provides the entries for initializing and starting services and features. 

This module provides the entries for initializing services and features during service development. Services and features are initialized in the following sequence: core phase, core system service, core system feature, system startup, system service, system feature, application-layer service, and application-layer feature. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section712059027191845"></a>

## Files<a name="files"></a>

<a name="table232299585191845"></a>
<table><thead align="left"><tr id="row1214291623191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p814403877191845"><a name="p814403877191845"></a><a name="p814403877191845"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1186663877191845"><a name="p1186663877191845"></a><a name="p1186663877191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row637039494191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1824833518191845"><a name="p1824833518191845"></a><a name="p1824833518191845"></a><a href="ohos_init-h.md">ohos_init.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459376320191845"><a name="p1459376320191845"></a><a name="p1459376320191845"></a>Provides the entries for initializing and starting services and features. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1494822977191845"></a>
<table><thead align="left"><tr id="row1137277414191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1327489110191845"><a name="p1327489110191845"></a><a name="p1327489110191845"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1826143645191845"><a name="p1826143645191845"></a><a name="p1826143645191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row644476734191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082143032191845"><a name="p2082143032191845"></a><a name="p2082143032191845"></a><a href="ohos-init.md#ga97a9cae685c8fe08b3ed438c4de4419d">CORE_INIT</a>(func)   LAYER_INITCALL_DEF(func, core, "core")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146382851191845"><a name="p146382851191845"></a><a name="p146382851191845"></a>Identifies the entry for initializing and starting a core phase by the priority 2. </p>
</td>
</tr>
<tr id="row1412101591191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1914191941191845"><a name="p1914191941191845"></a><a name="p1914191941191845"></a><a href="ohos-init.md#ga028481fe849c821d876df662158d5122">CORE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, core, "core", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746104609191845"><a name="p746104609191845"></a><a name="p746104609191845"></a>Identifies the entry for initializing and starting a core phase by the specified priority. </p>
</td>
</tr>
<tr id="row1972860042191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p933607152191845"><a name="p933607152191845"></a><a name="p933607152191845"></a><a href="ohos-init.md#gaeecafaa1e903880d1d8570dc6b09aec7">SYS_SERVICE_INIT</a>(func)   LAYER_INITCALL_DEF(func, sys_service, "sys.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1068428690191845"><a name="p1068428690191845"></a><a name="p1068428690191845"></a>Identifies the entry for initializing and starting a core system service by the priority 2. </p>
</td>
</tr>
<tr id="row783119080191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900639325191845"><a name="p1900639325191845"></a><a name="p1900639325191845"></a><a href="ohos-init.md#ga8200637c1413a8ddfb2997668d325ba7">SYS_SERVICE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, sys_service, "sys.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1231113233191845"><a name="p1231113233191845"></a><a name="p1231113233191845"></a>Identifies the entry for initializing and starting a core system service by the specified priority. </p>
</td>
</tr>
<tr id="row1804187674191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149651683191845"><a name="p1149651683191845"></a><a name="p1149651683191845"></a><a href="ohos-init.md#ga0ade3a78723c48748ae5fbbb261538a2">SYS_FEATURE_INIT</a>(func)   LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420977347191845"><a name="p420977347191845"></a><a name="p420977347191845"></a>Identifies the entry for initializing and starting a core system feature by the priority 2. </p>
</td>
</tr>
<tr id="row1950489897191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1835432883191845"><a name="p1835432883191845"></a><a name="p1835432883191845"></a><a href="ohos-init.md#ga561c8a47e7b929c7300a0c2acb458459">SYS_FEATURE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, sys_feature, "sys.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1478029925191845"><a name="p1478029925191845"></a><a name="p1478029925191845"></a>Identifies the entry for initializing and starting a core system feature by the specified priority. </p>
</td>
</tr>
<tr id="row546820583191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907337039191845"><a name="p907337039191845"></a><a name="p907337039191845"></a><a href="ohos-init.md#gaa6d9a034e9ee034240a023e8cb9c2c78">SYS_RUN</a>(func)   LAYER_INITCALL_DEF(func, run, "run")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424904580191845"><a name="p1424904580191845"></a><a name="p1424904580191845"></a>Identifies the entry for initializing and starting a system running phase by the priority 2. </p>
</td>
</tr>
<tr id="row1739537617191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131161377191845"><a name="p2131161377191845"></a><a name="p2131161377191845"></a><a href="ohos-init.md#ga2371a43afede3e4840893448c9f97843">SYS_RUN_PRI</a>(func, priority)   LAYER_INITCALL(func, run, "run", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757728920191845"><a name="p757728920191845"></a><a name="p757728920191845"></a>Identifies the entry for initializing and starting a system running phase by the specified priority. </p>
</td>
</tr>
<tr id="row2145089636191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851334409191845"><a name="p1851334409191845"></a><a name="p1851334409191845"></a><a href="ohos-init.md#ga0e8322b3ab1975d234bd7275b79ed7eb">SYSEX_SERVICE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3333963191845"><a name="p3333963191845"></a><a name="p3333963191845"></a>Identifies the entry for initializing and starting a system service by the priority 2. </p>
</td>
</tr>
<tr id="row2005337879191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p156101169191845"><a name="p156101169191845"></a><a name="p156101169191845"></a><a href="ohos-init.md#gae0c14aff58448d4a428ad55cfee7c89b">SYSEX_SERVICE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221499692191845"><a name="p221499692191845"></a><a name="p221499692191845"></a>Identifies the entry for initializing and starting a system service by the specified priority. </p>
</td>
</tr>
<tr id="row16732651191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p119315162191845"><a name="p119315162191845"></a><a name="p119315162191845"></a><a href="ohos-init.md#ga7e321122cb4bfc41bfd266c39108e7c0">SYSEX_FEATURE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1614190776191845"><a name="p1614190776191845"></a><a name="p1614190776191845"></a>Identifies the entry for initializing and starting a system feature by the priority 2. </p>
</td>
</tr>
<tr id="row1105039585191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1443077942191845"><a name="p1443077942191845"></a><a name="p1443077942191845"></a><a href="ohos-init.md#gabb08dfd40bae014ab94f4a3a0ff2180b">SYSEX_FEATURE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025617223191845"><a name="p1025617223191845"></a><a name="p1025617223191845"></a>Identifies the entry for initializing and starting a system feature by the specified priority. </p>
</td>
</tr>
<tr id="row130089840191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1512960625191845"><a name="p1512960625191845"></a><a name="p1512960625191845"></a><a href="ohos-init.md#gacd89f8f7d2c1e7490ae285f99f3a9d42">APP_SERVICE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788319372191845"><a name="p788319372191845"></a><a name="p788319372191845"></a>Identifies the entry for initializing and starting an application-layer service by the priority 2. </p>
</td>
</tr>
<tr id="row1622111628191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2004748196191845"><a name="p2004748196191845"></a><a name="p2004748196191845"></a><a href="ohos-init.md#gac678e25b6b7d9949220139741ffa4233">APP_SERVICE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p950935457191845"><a name="p950935457191845"></a><a name="p950935457191845"></a>Identifies the entry for initializing and starting an application-layer service by the specified priority. </p>
</td>
</tr>
<tr id="row1801330733191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348071436191845"><a name="p348071436191845"></a><a name="p348071436191845"></a><a href="ohos-init.md#ga6ae79099e42a2ee7680cc9d5ae4817d6">APP_FEATURE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1843927554191845"><a name="p1843927554191845"></a><a name="p1843927554191845"></a>Identifies the entry for initializing and starting an application-layer feature by the priority 2. </p>
</td>
</tr>
<tr id="row90664968191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p650535727191845"><a name="p650535727191845"></a><a name="p650535727191845"></a><a href="ohos-init.md#ga16168eb42790a913932f1ebd92a76fc1">APP_FEATURE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939850534191845"><a name="p1939850534191845"></a><a name="p1939850534191845"></a>Identifies the entry for initializing and starting an application-layer feature by the specified priority. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1637273525191845"></a>

## **Macro Definition Documentation**<a name="section963246688191845"></a>

## APP\_FEATURE\_INIT<a name="ga6ae79099e42a2ee7680cc9d5ae4817d6"></a>

```
#define APP_FEATURE_INIT( func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")
```

 **Description:**

Identifies the entry for initializing and starting an application-layer feature by the priority 2. 

This macro is used to identify the entry called at the priority 2 of the application-layer feature phase of the startup process. 

**Parameters:**

<a name="table1909388886191845"></a>
<table><thead align="left"><tr id="row585849634191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1412486733191845"><a name="p1412486733191845"></a><a name="p1412486733191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p699598846191845"><a name="p699598846191845"></a><a name="p699598846191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1353880036191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting an application-layer feature. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## APP\_FEATURE\_INIT\_PRI<a name="ga16168eb42790a913932f1ebd92a76fc1"></a>

```
#define APP_FEATURE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, app_feature, "app.feature", priority)
```

 **Description:**

Identifies the entry for initializing and starting an application-layer feature by the specified priority. 

This macro is used to identify the entry called at the specified priority of the application-layer feature phase of the startup process. 

**Parameters:**

<a name="table311687955191845"></a>
<table><thead align="left"><tr id="row1369954586191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2072914972191845"><a name="p2072914972191845"></a><a name="p2072914972191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1147041127191845"><a name="p1147041127191845"></a><a name="p1147041127191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row581782414191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting an application-layer feature. The type is void (*)(void). </td>
</tr>
<tr id="row1103685232191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the application-layer feature. The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## APP\_SERVICE\_INIT<a name="gacd89f8f7d2c1e7490ae285f99f3a9d42"></a>

```
#define APP_SERVICE_INIT( func)   LAYER_INITCALL_DEF(func, app_service, "app.service")
```

 **Description:**

Identifies the entry for initializing and starting an application-layer service by the priority 2. 

This macro is used to identify the entry called at the priority 2 of the application-layer service phase of the startup process. 

**Parameters:**

<a name="table953892178191845"></a>
<table><thead align="left"><tr id="row1548929863191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1697545830191845"><a name="p1697545830191845"></a><a name="p1697545830191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p653280305191845"><a name="p653280305191845"></a><a name="p653280305191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1831029785191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting an application-layer service. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## APP\_SERVICE\_INIT\_PRI<a name="gac678e25b6b7d9949220139741ffa4233"></a>

```
#define APP_SERVICE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, app_service, "app.service", priority)
```

 **Description:**

Identifies the entry for initializing and starting an application-layer service by the specified priority. 

This macro is used to identify the entry called at the specified priority of the application-layer service phase of the startup process. 

**Parameters:**

<a name="table1902118297191845"></a>
<table><thead align="left"><tr id="row2126570908191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1062477014191845"><a name="p1062477014191845"></a><a name="p1062477014191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1829473694191845"><a name="p1829473694191845"></a><a name="p1829473694191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row608722976191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting an application-layer service. The type is void (*)(void). </td>
</tr>
<tr id="row556700025191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the application-layer service phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## CORE\_INIT<a name="ga97a9cae685c8fe08b3ed438c4de4419d"></a>

```
#define CORE_INIT( func)   LAYER_INITCALL_DEF(func, core, "core")
```

 **Description:**

Identifies the entry for initializing and starting a core phase by the priority 2. 

This macro is used when Samgr is initialized and started. This macro is used to identify the entry called at the priority 2 of the core phase of the startup process. 

**Parameters:**

<a name="table1876234086191845"></a>
<table><thead align="left"><tr id="row1166445296191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p373110655191845"><a name="p373110655191845"></a><a name="p373110655191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p499002756191845"><a name="p499002756191845"></a><a name="p499002756191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row367788116191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a core phase. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## CORE\_INIT\_PRI<a name="ga028481fe849c821d876df662158d5122"></a>

```
#define CORE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, core, "core", priority)
```

 **Description:**

Identifies the entry for initializing and starting a core phase by the specified priority. 

This macro is used when Samgr is initialized and started. This macro is used to identify the entry called at the specified priority of the core phase of the startup process. 

**Parameters:**

<a name="table1850758535191845"></a>
<table><thead align="left"><tr id="row1766917880191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p912363549191845"><a name="p912363549191845"></a><a name="p912363549191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p897684620191845"><a name="p897684620191845"></a><a name="p897684620191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1392880718191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a core phase. The type is void (*)(void). </td>
</tr>
<tr id="row2110068619191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the core phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## SYS\_FEATURE\_INIT<a name="ga0ade3a78723c48748ae5fbbb261538a2"></a>

```
#define SYS_FEATURE_INIT( func)   LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")
```

 **Description:**

Identifies the entry for initializing and starting a core system feature by the priority 2. 

This macro is used to identify the entry called at the priority 2 in the core system feature phase of the startup process. 

**Parameters:**

<a name="table2024815856191845"></a>
<table><thead align="left"><tr id="row1789918088191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2101354622191845"><a name="p2101354622191845"></a><a name="p2101354622191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p992847138191845"><a name="p992847138191845"></a><a name="p992847138191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1684543614191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a core system service. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## SYS\_FEATURE\_INIT\_PRI<a name="ga561c8a47e7b929c7300a0c2acb458459"></a>

```
#define SYS_FEATURE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, sys_feature, "sys.feature", priority)
```

 **Description:**

Identifies the entry for initializing and starting a core system feature by the specified priority. 

This macro is used to identify the entry called at the specified priority in the core system feature phase of the startup process. 

**Parameters:**

<a name="table363782146191845"></a>
<table><thead align="left"><tr id="row747274558191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p577144596191845"><a name="p577144596191845"></a><a name="p577144596191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1627590453191845"><a name="p1627590453191845"></a><a name="p1627590453191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1346244609191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a core system feature. The type is void (*)(void). </td>
</tr>
<tr id="row716561583191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the core system feature phase. The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## SYS\_RUN<a name="gaa6d9a034e9ee034240a023e8cb9c2c78"></a>

```
#define SYS_RUN( func)   LAYER_INITCALL_DEF(func, run, "run")
```

 **Description:**

Identifies the entry for initializing and starting a system running phase by the priority 2. 

This macro is used to identify the entry called at the priority 2 in the system startup phase of the startup process. 

**Parameters:**

<a name="table701936517191845"></a>
<table><thead align="left"><tr id="row233443193191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1697643627191845"><a name="p1697643627191845"></a><a name="p1697643627191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1062176826191845"><a name="p1062176826191845"></a><a name="p1062176826191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row440036309191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a system running phase. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## SYS\_RUN\_PRI<a name="ga2371a43afede3e4840893448c9f97843"></a>

```
#define SYS_RUN_PRI( func,  priority )   LAYER_INITCALL(func, run, "run", priority)
```

 **Description:**

Identifies the entry for initializing and starting a system running phase by the specified priority. 

This macro is used to identify the entry called at the specified priority in the system startup phase of the startup process. 

**Parameters:**

<a name="table57346702191845"></a>
<table><thead align="left"><tr id="row1687952735191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p951944046191845"><a name="p951944046191845"></a><a name="p951944046191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p778819589191845"><a name="p778819589191845"></a><a name="p778819589191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1791072130191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a system running phase. The type is void (*)(void). </td>
</tr>
<tr id="row636898093191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the system startup phase. The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## SYS\_SERVICE\_INIT<a name="gaeecafaa1e903880d1d8570dc6b09aec7"></a>

```
#define SYS_SERVICE_INIT( func)   LAYER_INITCALL_DEF(func, sys_service, "sys.service")
```

 **Description:**

Identifies the entry for initializing and starting a core system service by the priority 2. 

This macro is used to identify the entry called at the priority 2 in the core system service phase of the startup process. 

**Parameters:**

<a name="table1577601505191845"></a>
<table><thead align="left"><tr id="row266786254191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p151439265191845"><a name="p151439265191845"></a><a name="p151439265191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p918679705191845"><a name="p918679705191845"></a><a name="p918679705191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1071682457191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a core system service. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## SYS\_SERVICE\_INIT\_PRI<a name="ga8200637c1413a8ddfb2997668d325ba7"></a>

```
#define SYS_SERVICE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, sys_service, "sys.service", priority)
```

 **Description:**

Identifies the entry for initializing and starting a core system service by the specified priority. 

This macro is used to identify the entry called at the specified priority in the core system service phase of the startup process. 

**Parameters:**

<a name="table1504371390191845"></a>
<table><thead align="left"><tr id="row153703885191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p630550925191845"><a name="p630550925191845"></a><a name="p630550925191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1062869780191845"><a name="p1062869780191845"></a><a name="p1062869780191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1471124163191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a core system service. The type is void (*)(void). </td>
</tr>
<tr id="row485961245191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the core system service in the startup phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## SYSEX\_FEATURE\_INIT<a name="ga7e321122cb4bfc41bfd266c39108e7c0"></a>

```
#define SYSEX_FEATURE_INIT( func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")
```

 **Description:**

Identifies the entry for initializing and starting a system feature by the priority 2. 

This macro is used to identify the entry called at the priority 2 of the system feature phase of the startup process. 

**Parameters:**

<a name="table992053214191845"></a>
<table><thead align="left"><tr id="row1918156059191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p248081866191845"><a name="p248081866191845"></a><a name="p248081866191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p94332251191845"><a name="p94332251191845"></a><a name="p94332251191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1233022424191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a system feature. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## SYSEX\_FEATURE\_INIT\_PRI<a name="gabb08dfd40bae014ab94f4a3a0ff2180b"></a>

```
#define SYSEX_FEATURE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, app_feature, "app.feature", priority)
```

 **Description:**

Identifies the entry for initializing and starting a system feature by the specified priority. 

This macro is used to identify the entry called at the specified priority of the system feature phase of the startup process. 

**Parameters:**

<a name="table970991869191845"></a>
<table><thead align="left"><tr id="row1603817448191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p297101734191845"><a name="p297101734191845"></a><a name="p297101734191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p83056217191845"><a name="p83056217191845"></a><a name="p83056217191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1948719340191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a system feature. The type is void (*)(void). </td>
</tr>
<tr id="row537900620191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the system feature phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

## SYSEX\_SERVICE\_INIT<a name="ga0e8322b3ab1975d234bd7275b79ed7eb"></a>

```
#define SYSEX_SERVICE_INIT( func)   LAYER_INITCALL_DEF(func, app_service, "app.service")
```

 **Description:**

Identifies the entry for initializing and starting a system service by the priority 2. 

This macro is used to identify the entry called at the priority 2 in the system service phase of the startup process. 

**Parameters:**

<a name="table308094690191845"></a>
<table><thead align="left"><tr id="row963512400191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1433290147191845"><a name="p1433290147191845"></a><a name="p1433290147191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p436554000191845"><a name="p436554000191845"></a><a name="p436554000191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1505430025191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a system service. The type is void (*)(void). </td>
</tr>
</tbody>
</table>

## SYSEX\_SERVICE\_INIT\_PRI<a name="gae0c14aff58448d4a428ad55cfee7c89b"></a>

```
#define SYSEX_SERVICE_INIT_PRI( func,  priority )   LAYER_INITCALL(func, app_service, "app.service", priority)
```

 **Description:**

Identifies the entry for initializing and starting a system service by the specified priority. 

This macro is used to identify the entry called at the specified priority of the system service phase of the startup process. 

**Parameters:**

<a name="table1148876457191845"></a>
<table><thead align="left"><tr id="row1858139523191845"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1067649507191845"><a name="p1067649507191845"></a><a name="p1067649507191845"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p14729466191845"><a name="p14729466191845"></a><a name="p14729466191845"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1652699705191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry function for initializing and starting a system service. The type is void (*)(void). </td>
</tr>
<tr id="row623063613191845"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the calling priority when starting the system service phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4. </td>
</tr>
</tbody>
</table>

