# BundleStatusCallback<a name="ZH-CN_TOPIC_0000001054652845"></a>

## **Overview**<a name="section1322371244113032"></a>

**Related Modules:**

[BundleManager](BundleManager.md)

**Description:**

Defines the application state callback information. 

## **Summary**<a name="section1627618283113032"></a>

## Data Fields<a name="pub-attribs"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="BundleStatusCallback.md#ad92bee444c17e378809065e23d6d796a">bundleName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>char *&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="BundleStatusCallback.md#ae6bd742d12d3c9034471299d69ba374a">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void *&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="BundleStatusCallback.md#a5e6bccc1fb386a428ae77271e5b21354">callBack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p><a href="BundleManager.md#gad7ea6d0bf78db2d59e6d339c31819885">BundleStateCallback</a>&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1597588585113032"></a>

## **Field Documentation**<a name="section422044125113032"></a>

## bundleName<a name="ad92bee444c17e378809065e23d6d796a"></a>

```
char* BundleStatusCallback::bundleName
```

 **Description:**

Pointer to the bundle name of the application that the callback listens to. If this parameter is set to  **nullptr**, the callback listens to all applications in the system. 

## callBack<a name="a5e6bccc1fb386a428ae77271e5b21354"></a>

```
[BundleStateCallback](BundleManager.md#gad7ea6d0bf78db2d59e6d339c31819885) BundleStatusCallback::callBack
```

 **Description:**

Callback to be invoked upon application state changes. 

## data<a name="ae6bd742d12d3c9034471299d69ba374a"></a>

```
void* BundleStatusCallback::data
```

 **Description:**

Pointer to the registered data that will be used by  [BundleStateCallback](BundleManager.md#gad7ea6d0bf78db2d59e6d339c31819885). 

