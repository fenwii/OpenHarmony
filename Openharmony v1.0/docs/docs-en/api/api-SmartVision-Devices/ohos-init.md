# OHOS Init<a name="EN-US_TOPIC_0000001054598113"></a>

## **Overview**<a name="section1615191618093523"></a>

Provides the entries for initializing and starting services and features.

This module provides the entries for initializing services and features during service development. Services and features are initialized in the following sequence: core phase, core system service, core system feature, system startup, system service, system feature, application-layer service, and application-layer feature.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section828669244093523"></a>

## Files<a name="files"></a>

<a name="table1715457416093523"></a>
<table><thead align="left"><tr id="row86023170093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p752888153093523"><a name="p752888153093523"></a><a name="p752888153093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p293902167093523"><a name="p293902167093523"></a><a name="p293902167093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row928201639093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p546307975093523"><a name="p546307975093523"></a><a name="p546307975093523"></a><a href="ohos_init-h.md">ohos_init.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96610083093523"><a name="p96610083093523"></a><a name="p96610083093523"></a>Provides the entries for initializing and starting services and features.</p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1533040353093523"></a>
<table><thead align="left"><tr id="row1724028123093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1713947486093523"><a name="p1713947486093523"></a><a name="p1713947486093523"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p171166147093523"><a name="p171166147093523"></a><a name="p171166147093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1777005326093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497967328093523"><a name="p1497967328093523"></a><a name="p1497967328093523"></a><a href="ohos-init.md#ga97a9cae685c8fe08b3ed438c4de4419d">CORE_INIT</a>(func)   LAYER_INITCALL_DEF(func, core, "core")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967903341093523"><a name="p967903341093523"></a><a name="p967903341093523"></a>Identifies the entry for initializing and starting a core phase by the priority 2.</p>
</td>
</tr>
<tr id="row1951185531093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015619469093523"><a name="p2015619469093523"></a><a name="p2015619469093523"></a><a href="ohos-init.md#ga028481fe849c821d876df662158d5122">CORE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, core, "core", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p973669687093523"><a name="p973669687093523"></a><a name="p973669687093523"></a>Identifies the entry for initializing and starting a core phase by the specified priority.</p>
</td>
</tr>
<tr id="row255480547093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422114389093523"><a name="p422114389093523"></a><a name="p422114389093523"></a><a href="ohos-init.md#gaeecafaa1e903880d1d8570dc6b09aec7">SYS_SERVICE_INIT</a>(func)   LAYER_INITCALL_DEF(func, sys_service, "sys.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p200665586093523"><a name="p200665586093523"></a><a name="p200665586093523"></a>Identifies the entry for initializing and starting a core system service by the priority 2.</p>
</td>
</tr>
<tr id="row168294316093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p775271865093523"><a name="p775271865093523"></a><a name="p775271865093523"></a><a href="ohos-init.md#ga8200637c1413a8ddfb2997668d325ba7">SYS_SERVICE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, sys_service, "sys.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70358375093523"><a name="p70358375093523"></a><a name="p70358375093523"></a>Identifies the entry for initializing and starting a core system service by the specified priority.</p>
</td>
</tr>
<tr id="row1596986318093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p675024695093523"><a name="p675024695093523"></a><a name="p675024695093523"></a><a href="ohos-init.md#ga0ade3a78723c48748ae5fbbb261538a2">SYS_FEATURE_INIT</a>(func)   LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81125398093523"><a name="p81125398093523"></a><a name="p81125398093523"></a>Identifies the entry for initializing and starting a core system feature by the priority 2.</p>
</td>
</tr>
<tr id="row274299909093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755282983093523"><a name="p1755282983093523"></a><a name="p1755282983093523"></a><a href="ohos-init.md#ga561c8a47e7b929c7300a0c2acb458459">SYS_FEATURE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, sys_feature, "sys.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1661838838093523"><a name="p1661838838093523"></a><a name="p1661838838093523"></a>Identifies the entry for initializing and starting a core system feature by the specified priority.</p>
</td>
</tr>
<tr id="row9404465093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603805639093523"><a name="p603805639093523"></a><a name="p603805639093523"></a><a href="ohos-init.md#gaa6d9a034e9ee034240a023e8cb9c2c78">SYS_RUN</a>(func)   LAYER_INITCALL_DEF(func, run, "run")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135033391093523"><a name="p2135033391093523"></a><a name="p2135033391093523"></a>Identifies the entry for initializing and starting a system running phase by the priority 2.</p>
</td>
</tr>
<tr id="row105052340093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p384049268093523"><a name="p384049268093523"></a><a name="p384049268093523"></a><a href="ohos-init.md#ga2371a43afede3e4840893448c9f97843">SYS_RUN_PRI</a>(func, priority)   LAYER_INITCALL(func, run, "run", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1519132482093523"><a name="p1519132482093523"></a><a name="p1519132482093523"></a>Identifies the entry for initializing and starting a system running phase by the specified priority.</p>
</td>
</tr>
<tr id="row1722633890093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p947799775093523"><a name="p947799775093523"></a><a name="p947799775093523"></a><a href="ohos-init.md#ga0e8322b3ab1975d234bd7275b79ed7eb">SYSEX_SERVICE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827702130093523"><a name="p1827702130093523"></a><a name="p1827702130093523"></a>Identifies the entry for initializing and starting a system service by the priority 2.</p>
</td>
</tr>
<tr id="row94712223093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960863157093523"><a name="p960863157093523"></a><a name="p960863157093523"></a><a href="ohos-init.md#gae0c14aff58448d4a428ad55cfee7c89b">SYSEX_SERVICE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p725956314093523"><a name="p725956314093523"></a><a name="p725956314093523"></a>Identifies the entry for initializing and starting a system service by the specified priority.</p>
</td>
</tr>
<tr id="row429113150093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p926940551093523"><a name="p926940551093523"></a><a name="p926940551093523"></a><a href="ohos-init.md#ga7e321122cb4bfc41bfd266c39108e7c0">SYSEX_FEATURE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1490662042093523"><a name="p1490662042093523"></a><a name="p1490662042093523"></a>Identifies the entry for initializing and starting a system feature by the priority 2.</p>
</td>
</tr>
<tr id="row2015024535093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648625980093523"><a name="p1648625980093523"></a><a name="p1648625980093523"></a><a href="ohos-init.md#gabb08dfd40bae014ab94f4a3a0ff2180b">SYSEX_FEATURE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1069456657093523"><a name="p1069456657093523"></a><a name="p1069456657093523"></a>Identifies the entry for initializing and starting a system feature by the specified priority.</p>
</td>
</tr>
<tr id="row1929895396093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p420087746093523"><a name="p420087746093523"></a><a name="p420087746093523"></a><a href="ohos-init.md#gacd89f8f7d2c1e7490ae285f99f3a9d42">APP_SERVICE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897135755093523"><a name="p897135755093523"></a><a name="p897135755093523"></a>Identifies the entry for initializing and starting an application-layer service by the priority 2.</p>
</td>
</tr>
<tr id="row86214033093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315068246093523"><a name="p315068246093523"></a><a name="p315068246093523"></a><a href="ohos-init.md#gac678e25b6b7d9949220139741ffa4233">APP_SERVICE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1353431649093523"><a name="p1353431649093523"></a><a name="p1353431649093523"></a>Identifies the entry for initializing and starting an application-layer service by the specified priority.</p>
</td>
</tr>
<tr id="row512673364093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521841518093523"><a name="p521841518093523"></a><a name="p521841518093523"></a><a href="ohos-init.md#ga6ae79099e42a2ee7680cc9d5ae4817d6">APP_FEATURE_INIT</a>(func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p815750158093523"><a name="p815750158093523"></a><a name="p815750158093523"></a>Identifies the entry for initializing and starting an application-layer feature by the priority 2.</p>
</td>
</tr>
<tr id="row297658267093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p932053270093523"><a name="p932053270093523"></a><a name="p932053270093523"></a><a href="ohos-init.md#ga16168eb42790a913932f1ebd92a76fc1">APP_FEATURE_INIT_PRI</a>(func, priority)   LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1819925757093523"><a name="p1819925757093523"></a><a name="p1819925757093523"></a>Identifies the entry for initializing and starting an application-layer feature by the specified priority.</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1274632302093523"></a>

## **Macro Definition Documentation**<a name="section2039569822093523"></a>

## APP\_FEATURE\_INIT<a name="ga6ae79099e42a2ee7680cc9d5ae4817d6"></a>

```
#define APP_FEATURE_INIT( func)   LAYER_INITCALL_DEF(func, app_feature, "app.feature")
```

**Description:**

Identifies the entry for initializing and starting an application-layer feature by the priority 2.

This macro is used to identify the entry called at the priority 2 of the application-layer feature phase of the startup process.

**Parameters:**

<a name="table868770017093523"></a>
<table><thead align="left"><tr id="row615086960093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1167611061093523"><a name="p1167611061093523"></a><a name="p1167611061093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1239238512093523"><a name="p1239238512093523"></a><a name="p1239238512093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1293393387093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1859298814093523p0"><a name="entry1859298814093523p0"></a><a name="entry1859298814093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry478764054093523p0"><a name="entry478764054093523p0"></a><a name="entry478764054093523p0"></a>Indicates the entry function for initializing and starting an application-layer feature. The type is void (*)(void).</p>
</td>
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

<a name="table547509837093523"></a>
<table><thead align="left"><tr id="row930532097093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p214149723093523"><a name="p214149723093523"></a><a name="p214149723093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1830975928093523"><a name="p1830975928093523"></a><a name="p1830975928093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row39705249093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2085395691093523p0"><a name="entry2085395691093523p0"></a><a name="entry2085395691093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1189745328093523p0"><a name="entry1189745328093523p0"></a><a name="entry1189745328093523p0"></a>Indicates the entry function for initializing and starting an application-layer feature. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row851257968093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1607782328093523p0"><a name="entry1607782328093523p0"></a><a name="entry1607782328093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry300654329093523p0"><a name="entry300654329093523p0"></a><a name="entry300654329093523p0"></a>Indicates the calling priority when starting the application-layer feature. The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table1514555484093523"></a>
<table><thead align="left"><tr id="row790418964093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p525753748093523"><a name="p525753748093523"></a><a name="p525753748093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p79506021093523"><a name="p79506021093523"></a><a name="p79506021093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1313813722093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry600625524093523p0"><a name="entry600625524093523p0"></a><a name="entry600625524093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1252917716093523p0"><a name="entry1252917716093523p0"></a><a name="entry1252917716093523p0"></a>Indicates the entry function for initializing and starting an application-layer service. The type is void (*)(void).</p>
</td>
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

<a name="table780306060093523"></a>
<table><thead align="left"><tr id="row1892096765093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p12931696093523"><a name="p12931696093523"></a><a name="p12931696093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p916456971093523"><a name="p916456971093523"></a><a name="p916456971093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row319520909093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry632118457093523p0"><a name="entry632118457093523p0"></a><a name="entry632118457093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry2106185128093523p0"><a name="entry2106185128093523p0"></a><a name="entry2106185128093523p0"></a>Indicates the entry function for initializing and starting an application-layer service. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row2110715672093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1991752079093523p0"><a name="entry1991752079093523p0"></a><a name="entry1991752079093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1056534897093523p0"><a name="entry1056534897093523p0"></a><a name="entry1056534897093523p0"></a>Indicates the calling priority when starting the application-layer service phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table1134967752093523"></a>
<table><thead align="left"><tr id="row262193099093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p670585961093523"><a name="p670585961093523"></a><a name="p670585961093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2142198735093523"><a name="p2142198735093523"></a><a name="p2142198735093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row891728510093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry810739254093523p0"><a name="entry810739254093523p0"></a><a name="entry810739254093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1016002077093523p0"><a name="entry1016002077093523p0"></a><a name="entry1016002077093523p0"></a>Indicates the entry function for initializing and starting a core phase. The type is void (*)(void).</p>
</td>
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

<a name="table56746516093523"></a>
<table><thead align="left"><tr id="row1881862794093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p619775315093523"><a name="p619775315093523"></a><a name="p619775315093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2114300801093523"><a name="p2114300801093523"></a><a name="p2114300801093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1028740922093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1851501234093523p0"><a name="entry1851501234093523p0"></a><a name="entry1851501234093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry246171493093523p0"><a name="entry246171493093523p0"></a><a name="entry246171493093523p0"></a>Indicates the entry function for initializing and starting a core phase. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row172886715093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1661244325093523p0"><a name="entry1661244325093523p0"></a><a name="entry1661244325093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry795122812093523p0"><a name="entry795122812093523p0"></a><a name="entry795122812093523p0"></a>Indicates the calling priority when starting the core phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table438126407093523"></a>
<table><thead align="left"><tr id="row1364825200093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1938724790093523"><a name="p1938724790093523"></a><a name="p1938724790093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p289308730093523"><a name="p289308730093523"></a><a name="p289308730093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row875972074093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1374436358093523p0"><a name="entry1374436358093523p0"></a><a name="entry1374436358093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry977145750093523p0"><a name="entry977145750093523p0"></a><a name="entry977145750093523p0"></a>Indicates the entry function for initializing and starting a core system service. The type is void (*)(void).</p>
</td>
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

<a name="table661384878093523"></a>
<table><thead align="left"><tr id="row259877324093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p871235296093523"><a name="p871235296093523"></a><a name="p871235296093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p943613044093523"><a name="p943613044093523"></a><a name="p943613044093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row961109280093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1923060665093523p0"><a name="entry1923060665093523p0"></a><a name="entry1923060665093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1698791388093523p0"><a name="entry1698791388093523p0"></a><a name="entry1698791388093523p0"></a>Indicates the entry function for initializing and starting a core system feature. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row413058345093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry803127459093523p0"><a name="entry803127459093523p0"></a><a name="entry803127459093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1131366901093523p0"><a name="entry1131366901093523p0"></a><a name="entry1131366901093523p0"></a>Indicates the calling priority when starting the core system feature phase. The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table1974945387093523"></a>
<table><thead align="left"><tr id="row1677916450093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1306613414093523"><a name="p1306613414093523"></a><a name="p1306613414093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1130181539093523"><a name="p1130181539093523"></a><a name="p1130181539093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row919772572093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry481845454093523p0"><a name="entry481845454093523p0"></a><a name="entry481845454093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1905989512093523p0"><a name="entry1905989512093523p0"></a><a name="entry1905989512093523p0"></a>Indicates the entry function for initializing and starting a system running phase. The type is void (*)(void).</p>
</td>
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

<a name="table1140799325093523"></a>
<table><thead align="left"><tr id="row1171823793093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p285609488093523"><a name="p285609488093523"></a><a name="p285609488093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p3032240093523"><a name="p3032240093523"></a><a name="p3032240093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1100358574093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry862975208093523p0"><a name="entry862975208093523p0"></a><a name="entry862975208093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1974430439093523p0"><a name="entry1974430439093523p0"></a><a name="entry1974430439093523p0"></a>Indicates the entry function for initializing and starting a system running phase. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row1238417497093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1321139959093523p0"><a name="entry1321139959093523p0"></a><a name="entry1321139959093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1624875255093523p0"><a name="entry1624875255093523p0"></a><a name="entry1624875255093523p0"></a>Indicates the calling priority when starting the system startup phase. The value range is [0, 5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table959679446093523"></a>
<table><thead align="left"><tr id="row1647757142093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p560973040093523"><a name="p560973040093523"></a><a name="p560973040093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p900420361093523"><a name="p900420361093523"></a><a name="p900420361093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2104360098093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry313645853093523p0"><a name="entry313645853093523p0"></a><a name="entry313645853093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1420922315093523p0"><a name="entry1420922315093523p0"></a><a name="entry1420922315093523p0"></a>Indicates the entry function for initializing and starting a core system service. The type is void (*)(void).</p>
</td>
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

<a name="table1722270371093523"></a>
<table><thead align="left"><tr id="row1956557936093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1438344572093523"><a name="p1438344572093523"></a><a name="p1438344572093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1066465100093523"><a name="p1066465100093523"></a><a name="p1066465100093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1356599194093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1758378074093523p0"><a name="entry1758378074093523p0"></a><a name="entry1758378074093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry876395549093523p0"><a name="entry876395549093523p0"></a><a name="entry876395549093523p0"></a>Indicates the entry function for initializing and starting a core system service. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row423473512093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1429990546093523p0"><a name="entry1429990546093523p0"></a><a name="entry1429990546093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1716961560093523p0"><a name="entry1716961560093523p0"></a><a name="entry1716961560093523p0"></a>Indicates the calling priority when starting the core system service in the startup phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table840211327093523"></a>
<table><thead align="left"><tr id="row1436436273093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1303207793093523"><a name="p1303207793093523"></a><a name="p1303207793093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p380223331093523"><a name="p380223331093523"></a><a name="p380223331093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row357102457093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1312883732093523p0"><a name="entry1312883732093523p0"></a><a name="entry1312883732093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1181709854093523p0"><a name="entry1181709854093523p0"></a><a name="entry1181709854093523p0"></a>Indicates the entry function for initializing and starting a system feature. The type is void (*)(void).</p>
</td>
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

<a name="table201819569093523"></a>
<table><thead align="left"><tr id="row1499395329093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1182672899093523"><a name="p1182672899093523"></a><a name="p1182672899093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p144122749093523"><a name="p144122749093523"></a><a name="p144122749093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1363441588093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1618553386093523p0"><a name="entry1618553386093523p0"></a><a name="entry1618553386093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry907065381093523p0"><a name="entry907065381093523p0"></a><a name="entry907065381093523p0"></a>Indicates the entry function for initializing and starting a system feature. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row1838864983093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry462587887093523p0"><a name="entry462587887093523p0"></a><a name="entry462587887093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry821526274093523p0"><a name="entry821526274093523p0"></a><a name="entry821526274093523p0"></a>Indicates the calling priority when starting the system feature phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
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

<a name="table1072151574093523"></a>
<table><thead align="left"><tr id="row699825704093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1165529626093523"><a name="p1165529626093523"></a><a name="p1165529626093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p483914617093523"><a name="p483914617093523"></a><a name="p483914617093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1817393890093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1329348650093523p0"><a name="entry1329348650093523p0"></a><a name="entry1329348650093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry6664896093523p0"><a name="entry6664896093523p0"></a><a name="entry6664896093523p0"></a>Indicates the entry function for initializing and starting a system service. The type is void (*)(void).</p>
</td>
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

<a name="table224494575093523"></a>
<table><thead align="left"><tr id="row343331039093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p713504134093523"><a name="p713504134093523"></a><a name="p713504134093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1800982632093523"><a name="p1800982632093523"></a><a name="p1800982632093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1275694982093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1635765759093523p0"><a name="entry1635765759093523p0"></a><a name="entry1635765759093523p0"></a>func</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry225991997093523p0"><a name="entry225991997093523p0"></a><a name="entry225991997093523p0"></a>Indicates the entry function for initializing and starting a system service. The type is void (*)(void).</p>
</td>
</tr>
<tr id="row302166720093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1861742437093523p0"><a name="entry1861742437093523p0"></a><a name="entry1861742437093523p0"></a>priority</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1089479779093523p0"><a name="entry1089479779093523p0"></a><a name="entry1089479779093523p0"></a>Indicates the calling priority when starting the system service phase. The value range is [0,5), and the calling sequence is 0, 1, 2, 3, and 4.</p>
</td>
</tr>
</tbody>
</table>

