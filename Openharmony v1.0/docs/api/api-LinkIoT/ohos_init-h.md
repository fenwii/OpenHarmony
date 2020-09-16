# ohos\_init.h<a name="ZH-CN_TOPIC_0000001055036446"></a>

## **Overview**<a name="section630801640191849"></a>

**Related Modules:**

[OHOS Init](OHOS-Init.md)

**Description:**

Provides the entries for initializing and starting services and features. 

This file provides the entries for initializing services and features during service development. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1806225695191849"></a>

## Macros<a name="define-members"></a>

<a name="table101426188191849"></a>
<table><thead align="left"><tr id="row164002302191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p217770372191849"><a name="p217770372191849"></a><a name="p217770372191849"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p252612233191849"><a name="p252612233191849"></a><a name="p252612233191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1922848477191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119149839191849"><a name="p1119149839191849"></a><a name="p1119149839191849"></a><a href="OHOS-Init.md#ga97a9cae685c8fe08b3ed438c4de4419d">CORE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, core, "core")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1410972172191849"><a name="p1410972172191849"></a><a name="p1410972172191849"></a>Identifies the entry for initializing and starting a core phase by the priority 2. </p>
</td>
</tr>
<tr id="row1555167002191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p940194577191849"><a name="p940194577191849"></a><a name="p940194577191849"></a><a href="OHOS-Init.md#ga028481fe849c821d876df662158d5122">CORE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, core, "core", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833258469191849"><a name="p833258469191849"></a><a name="p833258469191849"></a>Identifies the entry for initializing and starting a core phase by the specified priority. </p>
</td>
</tr>
<tr id="row787093568191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1469958520191849"><a name="p1469958520191849"></a><a name="p1469958520191849"></a><a href="OHOS-Init.md#gaeecafaa1e903880d1d8570dc6b09aec7">SYS_SERVICE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, sys_service, "sys.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404433023191849"><a name="p404433023191849"></a><a name="p404433023191849"></a>Identifies the entry for initializing and starting a core system service by the priority 2. </p>
</td>
</tr>
<tr id="row390675495191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p294678321191849"><a name="p294678321191849"></a><a name="p294678321191849"></a><a href="OHOS-Init.md#ga8200637c1413a8ddfb2997668d325ba7">SYS_SERVICE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, sys_service, "sys.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89628523191849"><a name="p89628523191849"></a><a name="p89628523191849"></a>Identifies the entry for initializing and starting a core system service by the specified priority. </p>
</td>
</tr>
<tr id="row1239877623191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329397403191849"><a name="p329397403191849"></a><a name="p329397403191849"></a><a href="OHOS-Init.md#ga0ade3a78723c48748ae5fbbb261538a2">SYS_FEATURE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1096917725191849"><a name="p1096917725191849"></a><a name="p1096917725191849"></a>Identifies the entry for initializing and starting a core system feature by the priority 2. </p>
</td>
</tr>
<tr id="row1960669313191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160225957191849"><a name="p160225957191849"></a><a name="p160225957191849"></a><a href="OHOS-Init.md#ga561c8a47e7b929c7300a0c2acb458459">SYS_FEATURE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, sys_feature, "sys.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p130720635191849"><a name="p130720635191849"></a><a name="p130720635191849"></a>Identifies the entry for initializing and starting a core system feature by the specified priority. </p>
</td>
</tr>
<tr id="row1974480954191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687331644191849"><a name="p687331644191849"></a><a name="p687331644191849"></a><a href="OHOS-Init.md#gaa6d9a034e9ee034240a023e8cb9c2c78">SYS_RUN</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, run, "run")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275765093191849"><a name="p1275765093191849"></a><a name="p1275765093191849"></a>Identifies the entry for initializing and starting a system running phase by the priority 2. </p>
</td>
</tr>
<tr id="row1725062089191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049561833191849"><a name="p1049561833191849"></a><a name="p1049561833191849"></a><a href="OHOS-Init.md#ga2371a43afede3e4840893448c9f97843">SYS_RUN_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, run, "run", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563751234191849"><a name="p1563751234191849"></a><a name="p1563751234191849"></a>Identifies the entry for initializing and starting a system running phase by the specified priority. </p>
</td>
</tr>
<tr id="row510108503191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2027141685191849"><a name="p2027141685191849"></a><a name="p2027141685191849"></a><a href="OHOS-Init.md#ga0e8322b3ab1975d234bd7275b79ed7eb">SYSEX_SERVICE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093306903191849"><a name="p1093306903191849"></a><a name="p1093306903191849"></a>Identifies the entry for initializing and starting a system service by the priority 2. </p>
</td>
</tr>
<tr id="row1598796512191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1262248221191849"><a name="p1262248221191849"></a><a name="p1262248221191849"></a><a href="OHOS-Init.md#gae0c14aff58448d4a428ad55cfee7c89b">SYSEX_SERVICE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p958648135191849"><a name="p958648135191849"></a><a name="p958648135191849"></a>Identifies the entry for initializing and starting a system service by the specified priority. </p>
</td>
</tr>
<tr id="row1702331821191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1299232675191849"><a name="p1299232675191849"></a><a name="p1299232675191849"></a><a href="OHOS-Init.md#ga7e321122cb4bfc41bfd266c39108e7c0">SYSEX_FEATURE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209145042191849"><a name="p209145042191849"></a><a name="p209145042191849"></a>Identifies the entry for initializing and starting a system feature by the priority 2. </p>
</td>
</tr>
<tr id="row670210352191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422519285191849"><a name="p422519285191849"></a><a name="p422519285191849"></a><a href="OHOS-Init.md#gabb08dfd40bae014ab94f4a3a0ff2180b">SYSEX_FEATURE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p90962093191849"><a name="p90962093191849"></a><a name="p90962093191849"></a>Identifies the entry for initializing and starting a system feature by the specified priority. </p>
</td>
</tr>
<tr id="row783289964191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413340348191849"><a name="p1413340348191849"></a><a name="p1413340348191849"></a><a href="OHOS-Init.md#gacd89f8f7d2c1e7490ae285f99f3a9d42">APP_SERVICE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1607067506191849"><a name="p1607067506191849"></a><a name="p1607067506191849"></a>Identifies the entry for initializing and starting an application-layer service by the priority 2. </p>
</td>
</tr>
<tr id="row225431347191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1614607352191849"><a name="p1614607352191849"></a><a name="p1614607352191849"></a><a href="OHOS-Init.md#gac678e25b6b7d9949220139741ffa4233">APP_SERVICE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p163268100191849"><a name="p163268100191849"></a><a name="p163268100191849"></a>Identifies the entry for initializing and starting an application-layer service by the specified priority. </p>
</td>
</tr>
<tr id="row1480552667191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870322597191849"><a name="p1870322597191849"></a><a name="p1870322597191849"></a><a href="OHOS-Init.md#ga6ae79099e42a2ee7680cc9d5ae4817d6">APP_FEATURE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p678955127191849"><a name="p678955127191849"></a><a name="p678955127191849"></a>Identifies the entry for initializing and starting an application-layer feature by the priority 2. </p>
</td>
</tr>
<tr id="row699585392191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p84599443191849"><a name="p84599443191849"></a><a name="p84599443191849"></a><a href="OHOS-Init.md#ga16168eb42790a913932f1ebd92a76fc1">APP_FEATURE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67324389191849"><a name="p67324389191849"></a><a name="p67324389191849"></a>Identifies the entry for initializing and starting an application-layer feature by the specified priority. </p>
</td>
</tr>
</tbody>
</table>

