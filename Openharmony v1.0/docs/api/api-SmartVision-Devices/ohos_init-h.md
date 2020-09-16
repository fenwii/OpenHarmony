# ohos\_init.h<a name="ZH-CN_TOPIC_0000001055078113"></a>

## **Overview**<a name="section1892310462093526"></a>

**Related Modules:**

[OHOS Init](OHOS-Init.md)

**Description:**

Provides the entries for initializing and starting services and features. 

This file provides the entries for initializing services and features during service development. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section262872391093526"></a>

## Macros<a name="define-members"></a>

<a name="table1572902509093526"></a>
<table><thead align="left"><tr id="row749973758093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p74558831093526"><a name="p74558831093526"></a><a name="p74558831093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p503801721093526"><a name="p503801721093526"></a><a name="p503801721093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row218325400093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451184989093526"><a name="p451184989093526"></a><a name="p451184989093526"></a><a href="OHOS-Init.md#ga97a9cae685c8fe08b3ed438c4de4419d">CORE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, core, "core")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388090032093526"><a name="p388090032093526"></a><a name="p388090032093526"></a>Identifies the entry for initializing and starting a core phase by the priority 2. </p>
</td>
</tr>
<tr id="row1011716350093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897384748093526"><a name="p897384748093526"></a><a name="p897384748093526"></a><a href="OHOS-Init.md#ga028481fe849c821d876df662158d5122">CORE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, core, "core", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1905048285093526"><a name="p1905048285093526"></a><a name="p1905048285093526"></a>Identifies the entry for initializing and starting a core phase by the specified priority. </p>
</td>
</tr>
<tr id="row647194641093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26785873093526"><a name="p26785873093526"></a><a name="p26785873093526"></a><a href="OHOS-Init.md#gaeecafaa1e903880d1d8570dc6b09aec7">SYS_SERVICE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, sys_service, "sys.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498779501093526"><a name="p498779501093526"></a><a name="p498779501093526"></a>Identifies the entry for initializing and starting a core system service by the priority 2. </p>
</td>
</tr>
<tr id="row386970852093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776817758093526"><a name="p776817758093526"></a><a name="p776817758093526"></a><a href="OHOS-Init.md#ga8200637c1413a8ddfb2997668d325ba7">SYS_SERVICE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, sys_service, "sys.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p957721203093526"><a name="p957721203093526"></a><a name="p957721203093526"></a>Identifies the entry for initializing and starting a core system service by the specified priority. </p>
</td>
</tr>
<tr id="row539074129093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044175285093526"><a name="p2044175285093526"></a><a name="p2044175285093526"></a><a href="OHOS-Init.md#ga0ade3a78723c48748ae5fbbb261538a2">SYS_FEATURE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, sys_feature, "sys.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1547539166093526"><a name="p1547539166093526"></a><a name="p1547539166093526"></a>Identifies the entry for initializing and starting a core system feature by the priority 2. </p>
</td>
</tr>
<tr id="row983141388093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826193627093526"><a name="p1826193627093526"></a><a name="p1826193627093526"></a><a href="OHOS-Init.md#ga561c8a47e7b929c7300a0c2acb458459">SYS_FEATURE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, sys_feature, "sys.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141886644093526"><a name="p1141886644093526"></a><a name="p1141886644093526"></a>Identifies the entry for initializing and starting a core system feature by the specified priority. </p>
</td>
</tr>
<tr id="row1372832944093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p707375152093526"><a name="p707375152093526"></a><a name="p707375152093526"></a><a href="OHOS-Init.md#gaa6d9a034e9ee034240a023e8cb9c2c78">SYS_RUN</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, run, "run")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p988455953093526"><a name="p988455953093526"></a><a name="p988455953093526"></a>Identifies the entry for initializing and starting a system running phase by the priority 2. </p>
</td>
</tr>
<tr id="row2032443816093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096016738093526"><a name="p1096016738093526"></a><a name="p1096016738093526"></a><a href="OHOS-Init.md#ga2371a43afede3e4840893448c9f97843">SYS_RUN_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, run, "run", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223408016093526"><a name="p223408016093526"></a><a name="p223408016093526"></a>Identifies the entry for initializing and starting a system running phase by the specified priority. </p>
</td>
</tr>
<tr id="row1957682397093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1844306194093526"><a name="p1844306194093526"></a><a name="p1844306194093526"></a><a href="OHOS-Init.md#ga0e8322b3ab1975d234bd7275b79ed7eb">SYSEX_SERVICE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090538380093526"><a name="p2090538380093526"></a><a name="p2090538380093526"></a>Identifies the entry for initializing and starting a system service by the priority 2. </p>
</td>
</tr>
<tr id="row1262150850093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p144240897093526"><a name="p144240897093526"></a><a name="p144240897093526"></a><a href="OHOS-Init.md#gae0c14aff58448d4a428ad55cfee7c89b">SYSEX_SERVICE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864659662093526"><a name="p1864659662093526"></a><a name="p1864659662093526"></a>Identifies the entry for initializing and starting a system service by the specified priority. </p>
</td>
</tr>
<tr id="row1416062449093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550239749093526"><a name="p1550239749093526"></a><a name="p1550239749093526"></a><a href="OHOS-Init.md#ga7e321122cb4bfc41bfd266c39108e7c0">SYSEX_FEATURE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1793512322093526"><a name="p1793512322093526"></a><a name="p1793512322093526"></a>Identifies the entry for initializing and starting a system feature by the priority 2. </p>
</td>
</tr>
<tr id="row1444157910093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259463423093526"><a name="p1259463423093526"></a><a name="p1259463423093526"></a><a href="OHOS-Init.md#gabb08dfd40bae014ab94f4a3a0ff2180b">SYSEX_FEATURE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785120111093526"><a name="p785120111093526"></a><a name="p785120111093526"></a>Identifies the entry for initializing and starting a system feature by the specified priority. </p>
</td>
</tr>
<tr id="row11394331093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1676748056093526"><a name="p1676748056093526"></a><a name="p1676748056093526"></a><a href="OHOS-Init.md#gacd89f8f7d2c1e7490ae285f99f3a9d42">APP_SERVICE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_service, "app.service")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84215837093526"><a name="p84215837093526"></a><a name="p84215837093526"></a>Identifies the entry for initializing and starting an application-layer service by the priority 2. </p>
</td>
</tr>
<tr id="row131121114093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1868678366093526"><a name="p1868678366093526"></a><a name="p1868678366093526"></a><a href="OHOS-Init.md#gac678e25b6b7d9949220139741ffa4233">APP_SERVICE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_service, "app.service", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550621980093526"><a name="p1550621980093526"></a><a name="p1550621980093526"></a>Identifies the entry for initializing and starting an application-layer service by the specified priority. </p>
</td>
</tr>
<tr id="row217857140093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p896175556093526"><a name="p896175556093526"></a><a name="p896175556093526"></a><a href="OHOS-Init.md#ga6ae79099e42a2ee7680cc9d5ae4817d6">APP_FEATURE_INIT</a>(func)&nbsp;&nbsp;&nbsp;LAYER_INITCALL_DEF(func, app_feature, "app.feature")</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1938490580093526"><a name="p1938490580093526"></a><a name="p1938490580093526"></a>Identifies the entry for initializing and starting an application-layer feature by the priority 2. </p>
</td>
</tr>
<tr id="row1257636279093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564277412093526"><a name="p1564277412093526"></a><a name="p1564277412093526"></a><a href="OHOS-Init.md#ga16168eb42790a913932f1ebd92a76fc1">APP_FEATURE_INIT_PRI</a>(func, priority)&nbsp;&nbsp;&nbsp;LAYER_INITCALL(func, app_feature, "app.feature", priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p887112744093526"><a name="p887112744093526"></a><a name="p887112744093526"></a>Identifies the entry for initializing and starting an application-layer feature by the specified priority. </p>
</td>
</tr>
</tbody>
</table>

