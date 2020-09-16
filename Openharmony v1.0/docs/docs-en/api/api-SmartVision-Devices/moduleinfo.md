# ModuleInfo<a name="EN-US_TOPIC_0000001054879540"></a>

## **Overview**<a name="section1969160110093531"></a>

**Related Modules:**

[BundleManager](bundlemanager.md)

**Description:**

Defines the HAP information. 

## **Summary**<a name="section1587448516093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table495810351093531"></a>
<table><thead align="left"><tr id="row1369833218093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p621298909093531"><a name="p621298909093531"></a><a name="p621298909093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1394719063093531"><a name="p1394719063093531"></a><a name="p1394719063093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1463733266093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2090626801093531"><a name="p2090626801093531"></a><a name="p2090626801093531"></a><a href="moduleinfo.md#ae194862e3cf07df40e0d41b3aa9eb1c0">moduleName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832941727093531"><a name="p832941727093531"></a><a name="p832941727093531"></a>char * </p>
</td>
</tr>
<tr id="row1758359257093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464051724093531"><a name="p1464051724093531"></a><a name="p1464051724093531"></a><a href="moduleinfo.md#af7211393306adaa07ad32c642539b7f6">description</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277270426093531"><a name="p277270426093531"></a><a name="p277270426093531"></a>char * </p>
</td>
</tr>
<tr id="row321808345093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p401049134093531"><a name="p401049134093531"></a><a name="p401049134093531"></a><a href="moduleinfo.md#adb9af8c6739aaf550e91119b146eb44e">name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874969909093531"><a name="p874969909093531"></a><a name="p874969909093531"></a>char * </p>
</td>
</tr>
<tr id="row1373482227093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p326888256093531"><a name="p326888256093531"></a><a name="p326888256093531"></a><a href="moduleinfo.md#af8f4264764394fb20c75a18a1a816ac6">moduleType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p855302876093531"><a name="p855302876093531"></a><a name="p855302876093531"></a>char * </p>
</td>
</tr>
<tr id="row988432845093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p411966164093531"><a name="p411966164093531"></a><a name="p411966164093531"></a><a href="moduleinfo.md#a6e76e2eb535e0d92a9e49652486c35ec">isDeliveryInstall</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649685388093531"><a name="p649685388093531"></a><a name="p649685388093531"></a>bool </p>
</td>
</tr>
<tr id="row707939899093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1160818772093531"><a name="p1160818772093531"></a><a name="p1160818772093531"></a><a href="moduleinfo.md#a7166c89b6815875afcafaca7cec21ae0">deviceType</a> [DEVICE_TYPE_SIZE]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1865079715093531"><a name="p1865079715093531"></a><a name="p1865079715093531"></a>char * </p>
</td>
</tr>
<tr id="row1703716018093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035507019093531"><a name="p2035507019093531"></a><a name="p2035507019093531"></a><a href="moduleinfo.md#a6731b378fc6b34c7e94ab3c0d8d08e5b">metaData</a> [METADATA_SIZE]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870159657093531"><a name="p1870159657093531"></a><a name="p1870159657093531"></a><a href="metadata.md">MetaData</a> * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section802739757093531"></a>

## **Field Documentation**<a name="section734487900093531"></a>

## description<a name="af7211393306adaa07ad32c642539b7f6"></a>

```
char* ModuleInfo::description
```

 **Description:**

Pointer to the description of the HAP package 

## deviceType<a name="a7166c89b6815875afcafaca7cec21ae0"></a>

```
char* ModuleInfo::deviceType[DEVICE_TYPE_SIZE]
```

 **Description:**

Pointer to the types of devices that can run the application. The maximum size of the device type array is  **DEVICE\_TYPE\_SIZE**. 

## isDeliveryInstall<a name="a6e76e2eb535e0d92a9e49652486c35ec"></a>

```
bool ModuleInfo::isDeliveryInstall
```

 **Description:**

Whether the HAP package is installed while the user is installing the application 

## metaData<a name="a6731b378fc6b34c7e94ab3c0d8d08e5b"></a>

```
[MetaData](metadata.md)* ModuleInfo::metaData[METADATA_SIZE]
```

 **Description:**

Pointer to the metadata array whose maximum size is  **METADATA\_SIZE** 

## moduleName<a name="ae194862e3cf07df40e0d41b3aa9eb1c0"></a>

```
char* ModuleInfo::moduleName
```

 **Description:**

Pointer to the HAP package name 

## moduleType<a name="af8f4264764394fb20c75a18a1a816ac6"></a>

```
char* ModuleInfo::moduleType
```

 **Description:**

Type of the HAP package, either  **Entry.hap**  or  **Feature.hap** 

## name<a name="adb9af8c6739aaf550e91119b146eb44e"></a>

```
char* ModuleInfo::name
```

 **Description:**

Pointer to the class name of the HAP package 

