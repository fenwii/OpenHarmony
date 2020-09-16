# bundle\_status\_callback.h<a name="ZH-CN_TOPIC_0000001054652830"></a>

## **Overview**<a name="section1912477999113024"></a>

**Related Modules:**

[BundleManager](BundleManager.md)

**Description:**

Declares the callback invoked upon state changes of an application and the structure defining the callback information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2069742751113024"></a>

## Data Structures<a name="nested-classes"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="BundleStatusCallback.md">BundleStatusCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the application state callback information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="BundleManager.md#gad7ea6d0bf78db2d59e6d339c31819885">BundleStateCallback</a>) (const uint8_t installType, const uint8_t resultCode, const void *resultMessage, const char *bundleName, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>typedef void(*&nbsp;</p>
<p>Called when the installation, update, or uninstallation state of an application changes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="BundleManager.md#gae5e0593438f073199bf6d69e47a84975">ClearBundleStatusCallback</a> (<a href="BundleStatusCallback.md">BundleStatusCallback</a> *bundleStatusCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Clears and releases the memory occupied by the <a href="BundleStatusCallback.md">BundleStatusCallback</a> structure. </p>
</td>
</tr>
</tbody>
</table>

