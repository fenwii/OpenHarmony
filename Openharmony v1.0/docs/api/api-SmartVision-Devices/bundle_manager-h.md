# bundle\_manager.h<a name="ZH-CN_TOPIC_0000001055358070"></a>

## **Overview**<a name="section979879720093524"></a>

**Related Modules:**

[BundleManager](BundleManager.md)

**Description:**

Declares functions used for managing application bundles and obtaining bundle information. 

You can use functions provided in this file to install, update, or uninstall an application, obtain  [AbilityInfo](AbilityInfo.md)  and  [BundleInfo](BundleInfo.md)  about an application, obtain the bundle name of an application based on the application's user ID \(UID\), and obtain  [BundleInfo](BundleInfo.md)  objects of all applications or keep-alive applications in the system.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section957582331093524"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table2121713546093524"></a>
<table><thead align="left"><tr id="row1578854507093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1119954181093524"><a name="p1119954181093524"></a><a name="p1119954181093524"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1395542995093524"><a name="p1395542995093524"></a><a name="p1395542995093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1989341526093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p715104919093524"><a name="p715104919093524"></a><a name="p715104919093524"></a><a href="BundleManager.md#ga00f021e76d728d2d44e1a28887ccc3af">InstallerCallback</a>) (const uint8_t resultCode, const void *resultMessage)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p201537064093524"><a name="p201537064093524"></a><a name="p201537064093524"></a>typedef void(*&nbsp;</p>
<p id="p398651634093524"><a name="p398651634093524"></a><a name="p398651634093524"></a>Called when an application is installed, updated, or uninstalled. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1286707292093524"></a>
<table><thead align="left"><tr id="row104506316093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1252524407093524"><a name="p1252524407093524"></a><a name="p1252524407093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1314004158093524"><a name="p1314004158093524"></a><a name="p1314004158093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row684537882093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782456800093524"><a name="p1782456800093524"></a><a name="p1782456800093524"></a><a href="BundleManager.md#ga5c49620ca8b752cd6f43fabc5d5c7416">RegisterCallback</a> (BundleStatusCallback *BundleStatusCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1672981302093524"><a name="p1672981302093524"></a><a name="p1672981302093524"></a>int32_t&nbsp;</p>
<p id="p703890370093524"><a name="p703890370093524"></a><a name="p703890370093524"></a>Registers a callback to monitor the installation, update, and uninstallation state changes of an application. </p>
</td>
</tr>
<tr id="row1918818587093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28868020093524"><a name="p28868020093524"></a><a name="p28868020093524"></a><a href="BundleManager.md#ga095eee592eff6ce71a2a67a1a0e3e344">UnregisterCallback</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51573455093524"><a name="p51573455093524"></a><a name="p51573455093524"></a>int32_t&nbsp;</p>
<p id="p1932701562093524"><a name="p1932701562093524"></a><a name="p1932701562093524"></a>Unregisters a callback previously registered for monitoring the installation, update, and uninstallation state changes of an application. </p>
</td>
</tr>
<tr id="row338895256093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577833894093524"><a name="p577833894093524"></a><a name="p577833894093524"></a><a href="BundleManager.md#gaf1f1521a64cc98f076b0082df6c0abdd">Install</a> (const char *hapPath, const InstallParam *installParam, <a href="BundleManager.md#ga00f021e76d728d2d44e1a28887ccc3af">InstallerCallback</a> installerCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679552401093524"><a name="p679552401093524"></a><a name="p679552401093524"></a>bool&nbsp;</p>
<p id="p1200763507093524"><a name="p1200763507093524"></a><a name="p1200763507093524"></a>Installs or updates an application. </p>
</td>
</tr>
<tr id="row322610870093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p708888161093524"><a name="p708888161093524"></a><a name="p708888161093524"></a><a href="BundleManager.md#gaa117e44378315a61b4e71fd252b2e496">Uninstall</a> (const char *bundleName, const InstallParam *installParam, <a href="BundleManager.md#ga00f021e76d728d2d44e1a28887ccc3af">InstallerCallback</a> installerCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598571794093524"><a name="p1598571794093524"></a><a name="p1598571794093524"></a>bool&nbsp;</p>
<p id="p139496451093524"><a name="p139496451093524"></a><a name="p139496451093524"></a>Uninstalls an application. </p>
</td>
</tr>
<tr id="row455369973093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035346100093524"><a name="p2035346100093524"></a><a name="p2035346100093524"></a><a href="BundleManager.md#ga4360375d15224d89632f59ee110b74c9">QueryAbilityInfo</a> (const <a href="Want.md">Want</a> *want, <a href="AbilityInfo.md">AbilityInfo</a> *abilityInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p940481416093524"><a name="p940481416093524"></a><a name="p940481416093524"></a>uint8_t&nbsp;</p>
<p id="p1297071093093524"><a name="p1297071093093524"></a><a name="p1297071093093524"></a>Queries the <a href="AbilityInfo.md">AbilityInfo</a> of an ability based on the information carried in the <a href="Want.md">Want</a> structure. </p>
</td>
</tr>
<tr id="row589755105093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p194060647093524"><a name="p194060647093524"></a><a name="p194060647093524"></a><a href="BundleManager.md#ga5e81134e037911654e34cc8a7ba01a2f">GetBundleInfo</a> (const char *bundleName, int32_t flags, <a href="BundleInfo.md">BundleInfo</a> *bundleInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060241240093524"><a name="p1060241240093524"></a><a name="p1060241240093524"></a>uint8_t&nbsp;</p>
<p id="p1976563097093524"><a name="p1976563097093524"></a><a name="p1976563097093524"></a>Obtains the <a href="BundleInfo.md">BundleInfo</a> of an application based on the specified bundle name. </p>
</td>
</tr>
<tr id="row2111378669093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437306654093524"><a name="p1437306654093524"></a><a name="p1437306654093524"></a><a href="BundleManager.md#ga2469dafbc61ba8e98b69041c13044cad">GetBundleInfos</a> (const int flags, <a href="BundleInfo.md">BundleInfo</a> **bundleInfos, int32_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938588569093524"><a name="p938588569093524"></a><a name="p938588569093524"></a>uint8_t&nbsp;</p>
<p id="p174585517093524"><a name="p174585517093524"></a><a name="p174585517093524"></a>Obtains the <a href="BundleInfo.md">BundleInfo</a> of all bundles in the system. </p>
</td>
</tr>
<tr id="row24683789093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087923994093524"><a name="p2087923994093524"></a><a name="p2087923994093524"></a><a href="BundleManager.md#ga0c1cb00194993ecba7337fdf0a203314">QueryKeepAliveBundleInfos</a> (<a href="BundleInfo.md">BundleInfo</a> **bundleInfos, int32_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576599104093524"><a name="p1576599104093524"></a><a name="p1576599104093524"></a>uint8_t&nbsp;</p>
<p id="p2096697820093524"><a name="p2096697820093524"></a><a name="p2096697820093524"></a>Obtains the <a href="BundleInfo.md">BundleInfo</a> of all keep-alive applications in the system. </p>
</td>
</tr>
<tr id="row1578630687093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791884562093524"><a name="p1791884562093524"></a><a name="p1791884562093524"></a><a href="BundleManager.md#ga711965038390aef4fa0a6b6a98f6998b">GetBundleInfosByMetaData</a> (const char *metaDataKey, <a href="BundleInfo.md">BundleInfo</a> **bundleInfos, int32_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p26245787093524"><a name="p26245787093524"></a><a name="p26245787093524"></a>uint8_t&nbsp;</p>
<p id="p1084706552093524"><a name="p1084706552093524"></a><a name="p1084706552093524"></a>Obtains the <a href="BundleInfo.md">BundleInfo</a> of application bundles based on the specified <a href="MetaData.md">MetaData</a>. </p>
</td>
</tr>
<tr id="row978035039093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1041508641093524"><a name="p1041508641093524"></a><a name="p1041508641093524"></a><a href="BundleManager.md#ga4afdc08ba78506fce95a066e137ac46d">GetBundleNameForUid</a> (int32_t uid, char **bundleName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p165039705093524"><a name="p165039705093524"></a><a name="p165039705093524"></a>uint8_t&nbsp;</p>
<p id="p411537936093524"><a name="p411537936093524"></a><a name="p411537936093524"></a>Obtains the bundle name of an application based on the specified UID. </p>
</td>
</tr>
</tbody>
</table>

