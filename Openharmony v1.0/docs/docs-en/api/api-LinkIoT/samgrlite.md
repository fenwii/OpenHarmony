# SamgrLite<a name="EN-US_TOPIC_0000001054715061"></a>

## **Overview**<a name="section1510016748191902"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Represents the system ability management class. 

This class is used for registering and discovering services, features, and functions. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1568160545191902"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1561242866191902"></a>
<table><thead align="left"><tr id="row1480266822191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1080945785191902"><a name="p1080945785191902"></a><a name="p1080945785191902"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1169936587191902"><a name="p1169936587191902"></a><a name="p1169936587191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row666891972191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28254504191902"><a name="p28254504191902"></a><a name="p28254504191902"></a><a href="samgrlite.md#a9adf6d526e11688ad318229487cfc0b4">RegisterService</a> )(<a href="service.md">Service</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1176137938191902"><a name="p1176137938191902"></a><a name="p1176137938191902"></a>BOOL(* </p>
<p id="p453578191191902"><a name="p453578191191902"></a><a name="p453578191191902"></a>Registers a service. </p>
</td>
</tr>
<tr id="row505064318191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p185172735191902"><a name="p185172735191902"></a><a name="p185172735191902"></a><a href="samgrlite.md#a3cebb3773860e67de745ac24021e63b0">UnregisterService</a> )(const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221763412191902"><a name="p1221763412191902"></a><a name="p1221763412191902"></a><a href="service.md">Service</a> *(* </p>
<p id="p1819617721191902"><a name="p1819617721191902"></a><a name="p1819617721191902"></a>Unregisters a service. </p>
</td>
</tr>
<tr id="row2056945644191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160927838191902"><a name="p160927838191902"></a><a name="p160927838191902"></a><a href="samgrlite.md#a05153cf073a1373bac53a0a1c2030ba0">RegisterFeature</a> )(const char *serviceName, <a href="feature.md">Feature</a> *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p903410167191902"><a name="p903410167191902"></a><a name="p903410167191902"></a>BOOL(* </p>
<p id="p1624746274191902"><a name="p1624746274191902"></a><a name="p1624746274191902"></a>Registers a feature. </p>
</td>
</tr>
<tr id="row2089803697191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p803136681191902"><a name="p803136681191902"></a><a name="p803136681191902"></a><a href="samgrlite.md#a03c53143dae167f685d796f3a806a574">UnregisterFeature</a> )(const char *serviceName, const char *featureName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351296528191902"><a name="p351296528191902"></a><a name="p351296528191902"></a><a href="feature.md">Feature</a> *(* </p>
<p id="p1712255351191902"><a name="p1712255351191902"></a><a name="p1712255351191902"></a>Unregisters a feature. </p>
</td>
</tr>
<tr id="row905118797191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365148318191902"><a name="p365148318191902"></a><a name="p365148318191902"></a><a href="samgrlite.md#aafa34cfe11f389b208e90ba451000c1d">RegisterDefaultFeatureApi</a> )(const char *service, <a href="iunknown.md">IUnknown</a> *publicApi)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782875770191902"><a name="p782875770191902"></a><a name="p782875770191902"></a>BOOL(* </p>
<p id="p358547394191902"><a name="p358547394191902"></a><a name="p358547394191902"></a>Registers the API for the default feature of a service. </p>
</td>
</tr>
<tr id="row224811708191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p830301644191902"><a name="p830301644191902"></a><a name="p830301644191902"></a><a href="samgrlite.md#a46f630c5a037c569a5b7806b4f8804ad">UnregisterDefaultFeatureApi</a> )(const char *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757459967191902"><a name="p757459967191902"></a><a name="p757459967191902"></a><a href="iunknown.md">IUnknown</a> *(* </p>
<p id="p652315344191902"><a name="p652315344191902"></a><a name="p652315344191902"></a>Unregisters the API from the default feature of a service. </p>
</td>
</tr>
<tr id="row580067704191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1665251963191902"><a name="p1665251963191902"></a><a name="p1665251963191902"></a><a href="samgrlite.md#a9c1a5452e501478a984a1220f550efba">RegisterFeatureApi</a> )(const char *service, const char *feature, <a href="iunknown.md">IUnknown</a> *publicApi)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1434382851191902"><a name="p1434382851191902"></a><a name="p1434382851191902"></a>BOOL(* </p>
<p id="p914837261191902"><a name="p914837261191902"></a><a name="p914837261191902"></a>Registers the API for a feature. </p>
</td>
</tr>
<tr id="row370826871191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1696869011191902"><a name="p1696869011191902"></a><a name="p1696869011191902"></a><a href="samgrlite.md#a2e33f34b97159b6673dff37e675ed844">UnregisterFeatureApi</a> )(const char *service, const char *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1967525699191902"><a name="p1967525699191902"></a><a name="p1967525699191902"></a><a href="iunknown.md">IUnknown</a> *(* </p>
<p id="p1042359407191902"><a name="p1042359407191902"></a><a name="p1042359407191902"></a>Unregisters the API from a feature. </p>
</td>
</tr>
<tr id="row658237333191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737113098191902"><a name="p737113098191902"></a><a name="p737113098191902"></a><a href="samgrlite.md#ac9d054e649b089ce256128ea4731cf57">GetDefaultFeatureApi</a> )(const char *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2128960922191902"><a name="p2128960922191902"></a><a name="p2128960922191902"></a><a href="iunknown.md">IUnknown</a> *(* </p>
<p id="p1381434416191902"><a name="p1381434416191902"></a><a name="p1381434416191902"></a>Obtains the API specific to the default feature. </p>
</td>
</tr>
<tr id="row1932913955191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1266034714191902"><a name="p1266034714191902"></a><a name="p1266034714191902"></a><a href="samgrlite.md#aad5c8419acea291e00059f79f8e6c8d1">GetFeatureApi</a> )(const char *serviceName, const char *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1022661748191902"><a name="p1022661748191902"></a><a name="p1022661748191902"></a><a href="iunknown.md">IUnknown</a> *(* </p>
<p id="p1380717807191902"><a name="p1380717807191902"></a><a name="p1380717807191902"></a>Obtains the API specific to the feature. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section252809633191902"></a>

## **Field Documentation**<a name="section1729103753191902"></a>

## GetDefaultFeatureApi<a name="ac9d054e649b089ce256128ea4731cf57"></a>

```
[IUnknown](iunknown.md)*(* SamgrLite::GetDefaultFeatureApi) (const char *service)
```

 **Description:**

Obtains the API specific to the default feature. 

You need to call this function before using the system capabilities of the service involved. 

**Parameters:**

<a name="table1788380607191902"></a>
<table><thead align="left"><tr id="row618200135191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p632363945191902"><a name="p632363945191902"></a><a name="p632363945191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p548744153191902"><a name="p548744153191902"></a><a name="p548744153191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row554823556191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service to which the default feature belongs. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **[IUnknown](iunknown.md)  \***  object that can be called if the operation is successful; returns  **NULL**  if the operation fails. 



## GetFeatureApi<a name="aad5c8419acea291e00059f79f8e6c8d1"></a>

```
[IUnknown](iunknown.md)*(* SamgrLite::GetFeatureApi) (const char *serviceName, const char *feature)
```

 **Description:**

Obtains the API specific to the feature. 

You need to call this function before using the system capabilities of the service involved. 

**Parameters:**

<a name="table1657150021191902"></a>
<table><thead align="left"><tr id="row277904128191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p590398134191902"><a name="p590398134191902"></a><a name="p590398134191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1202083862191902"><a name="p1202083862191902"></a><a name="p1202083862191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row672115234191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service to which the feature belongs. </td>
</tr>
<tr id="row369827874191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature whose API will be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **[IUnknown](iunknown.md)  \***  object that can be called if the operation is successful; returns  **NULL**  if the operation fails. 



## RegisterDefaultFeatureApi<a name="aafa34cfe11f389b208e90ba451000c1d"></a>

```
BOOL(* SamgrLite::RegisterDefaultFeatureApi) (const char *service, [IUnknown](iunknown.md) *publicApi)
```

 **Description:**

Registers the API for the default feature of a service. 

You need to call this function after the service is registered. The pointers to the  [IUnknown](iunknown.md)  and  [IUnknown](iunknown.md)  members to be registered cannot be empty. 

**Parameters:**

<a name="table1951936200191902"></a>
<table><thead align="left"><tr id="row832543473191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p166006287191902"><a name="p166006287191902"></a><a name="p166006287191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1348210671191902"><a name="p1348210671191902"></a><a name="p1348210671191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row372668695191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose default feature's API will be registered. </td>
</tr>
<tr id="row1516468890191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">publicApi</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the API to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## RegisterFeature<a name="a05153cf073a1373bac53a0a1c2030ba0"></a>

```
BOOL(* SamgrLite::RegisterFeature) (const char *serviceName, [Feature](feature.md) *feature)
```

 **Description:**

Registers a feature. 

You need to call this function in the startup entry of each feature.  [Feature](feature.md)  and  [Feature](feature.md)  structure members to be registered cannot be empty. 

**Parameters:**

<a name="table1688575286191902"></a>
<table><thead align="left"><tr id="row1881341116191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1577133623191902"><a name="p1577133623191902"></a><a name="p1577133623191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1178100785191902"><a name="p1178100785191902"></a><a name="p1178100785191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1883386770191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the feature to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## RegisterFeatureApi<a name="a9c1a5452e501478a984a1220f550efba"></a>

```
BOOL(* SamgrLite::RegisterFeatureApi) (const char *service, const char *feature, [IUnknown](iunknown.md) *publicApi)
```

 **Description:**

Registers the API for a feature. 

You can call this function only if the feature has been registered. The pointers to the  [IUnknown](iunknown.md)  and  [IUnknown](iunknown.md)  members to be registered cannot be empty. 

**Parameters:**

<a name="table335567755191902"></a>
<table><thead align="left"><tr id="row1851264905191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298347107191902"><a name="p1298347107191902"></a><a name="p1298347107191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p266113133191902"><a name="p266113133191902"></a><a name="p266113133191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row648631718191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose API will be registered. </td>
</tr>
<tr id="row2131564110191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature whose API will be registered. </td>
</tr>
<tr id="row389246187191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">publicApi</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the API to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## RegisterService<a name="a9adf6d526e11688ad318229487cfc0b4"></a>

```
BOOL(* SamgrLite::RegisterService) ([Service](service.md) *service)
```

 **Description:**

Registers a service. 

You need to call this function in the startup entry of each service.  [Service](service.md)  and  [Service](service.md)  structure members to be registered cannot be empty. 

**Parameters:**

<a name="table1874593579191902"></a>
<table><thead align="left"><tr id="row1266052573191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1948964622191902"><a name="p1948964622191902"></a><a name="p1948964622191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p763242621191902"><a name="p763242621191902"></a><a name="p763242621191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1938770928191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the service to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## UnregisterDefaultFeatureApi<a name="a46f630c5a037c569a5b7806b4f8804ad"></a>

```
[IUnknown](iunknown.md)*(* SamgrLite::UnregisterDefaultFeatureApi) (const char *service)
```

 **Description:**

Unregisters the API from the default feature of a service. 

You need to call this function to unregister  [IUnknown](iunknown.md)  if the service to which the default feature belongs is no longer required. 

**Parameters:**

<a name="table1359465447191902"></a>
<table><thead align="left"><tr id="row1011747203191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1133218058191902"><a name="p1133218058191902"></a><a name="p1133218058191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2004581117191902"><a name="p2004581117191902"></a><a name="p2004581117191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1417023856191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose default feature's API will be unregistered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the unregistered function object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



## UnregisterFeature<a name="a03c53143dae167f685d796f3a806a574"></a>

```
[Feature](feature.md)*(* SamgrLite::UnregisterFeature) (const char *serviceName, const char *featureName)
```

 **Description:**

Unregisters a feature. 

You need to call this function when the feature is no longer required. 

**Parameters:**

<a name="table970103163191902"></a>
<table><thead align="left"><tr id="row686879998191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p102529882191902"><a name="p102529882191902"></a><a name="p102529882191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p210575969191902"><a name="p210575969191902"></a><a name="p210575969191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row79965982191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">serviceName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose feature will be unregistered. </td>
</tr>
<tr id="row462792492191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">featureName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature to be unregistered. </td>
</tr>
</tbody>
</table>

**Attention:**

Before unregistering the feature, you must unregister its functions. Otherwise, the unregistration fails. 

**Returns:**

Returns the unregistered feature object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



## UnregisterFeatureApi<a name="a2e33f34b97159b6673dff37e675ed844"></a>

```
[IUnknown](iunknown.md)*(* SamgrLite::UnregisterFeatureApi) (const char *service, const char *feature)
```

 **Description:**

Unregisters the API from a feature. 

You must call this function before unregistering the feature no longer required. 

**Parameters:**

<a name="table1589609589191902"></a>
<table><thead align="left"><tr id="row367841170191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p146208844191902"><a name="p146208844191902"></a><a name="p146208844191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p65964215191902"><a name="p65964215191902"></a><a name="p65964215191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1365918878191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose API will be unregistered. </td>
</tr>
<tr id="row1194290159191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature whose API will be unregistered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the unregistered function object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



## UnregisterService<a name="a3cebb3773860e67de745ac24021e63b0"></a>

```
[Service](service.md)*(* SamgrLite::UnregisterService) (const char *name)
```

 **Description:**

Unregisters a service. 

You need to call this function when the service is no longer required. 

**Parameters:**

<a name="table926891733191902"></a>
<table><thead align="left"><tr id="row1283707651191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1326015908191902"><a name="p1326015908191902"></a><a name="p1326015908191902"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1332962490191902"><a name="p1332962490191902"></a><a name="p1332962490191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1466336705191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service to be unregistered. </td>
</tr>
</tbody>
</table>

**Attention:**

Before unregistering the service, you must unregister its features and functions. 

**Returns:**

Returns the unregistered service object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



