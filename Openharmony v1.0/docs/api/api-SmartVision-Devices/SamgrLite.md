# SamgrLite<a name="ZH-CN_TOPIC_0000001054918193"></a>

## **Overview**<a name="section274955831093537"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Represents the system ability management class. 

This class is used for registering and discovering services, features, and functions. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1275379325093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1137586150093537"></a>
<table><thead align="left"><tr id="row1943316437093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1433154528093537"><a name="p1433154528093537"></a><a name="p1433154528093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p568620750093537"><a name="p568620750093537"></a><a name="p568620750093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row618651053093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p783614388093537"><a name="p783614388093537"></a><a name="p783614388093537"></a><a href="SamgrLite.md#a9adf6d526e11688ad318229487cfc0b4">RegisterService</a> )(<a href="Service.md">Service</a> *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p640823767093537"><a name="p640823767093537"></a><a name="p640823767093537"></a>BOOL(*&nbsp;</p>
<p id="p58045053093537"><a name="p58045053093537"></a><a name="p58045053093537"></a>Registers a service. </p>
</td>
</tr>
<tr id="row1228885183093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p30998759093537"><a name="p30998759093537"></a><a name="p30998759093537"></a><a href="SamgrLite.md#a3cebb3773860e67de745ac24021e63b0">UnregisterService</a> )(const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1376752355093537"><a name="p1376752355093537"></a><a name="p1376752355093537"></a><a href="Service.md">Service</a> *(*&nbsp;</p>
<p id="p546356478093537"><a name="p546356478093537"></a><a name="p546356478093537"></a>Unregisters a service. </p>
</td>
</tr>
<tr id="row61266697093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496176291093537"><a name="p496176291093537"></a><a name="p496176291093537"></a><a href="SamgrLite.md#a05153cf073a1373bac53a0a1c2030ba0">RegisterFeature</a> )(const char *serviceName, <a href="Feature.md">Feature</a> *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334915669093537"><a name="p334915669093537"></a><a name="p334915669093537"></a>BOOL(*&nbsp;</p>
<p id="p1457141640093537"><a name="p1457141640093537"></a><a name="p1457141640093537"></a>Registers a feature. </p>
</td>
</tr>
<tr id="row707923108093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340786842093537"><a name="p1340786842093537"></a><a name="p1340786842093537"></a><a href="SamgrLite.md#a03c53143dae167f685d796f3a806a574">UnregisterFeature</a> )(const char *serviceName, const char *featureName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1118792976093537"><a name="p1118792976093537"></a><a name="p1118792976093537"></a><a href="Feature.md">Feature</a> *(*&nbsp;</p>
<p id="p267327638093537"><a name="p267327638093537"></a><a name="p267327638093537"></a>Unregisters a feature. </p>
</td>
</tr>
<tr id="row959987111093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911546301093537"><a name="p1911546301093537"></a><a name="p1911546301093537"></a><a href="SamgrLite.md#aafa34cfe11f389b208e90ba451000c1d">RegisterDefaultFeatureApi</a> )(const char *service, <a href="IUnknown.md">IUnknown</a> *publicApi)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475664184093537"><a name="p475664184093537"></a><a name="p475664184093537"></a>BOOL(*&nbsp;</p>
<p id="p356776235093537"><a name="p356776235093537"></a><a name="p356776235093537"></a>Registers the API for the default feature of a service. </p>
</td>
</tr>
<tr id="row1450104036093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1016863281093537"><a name="p1016863281093537"></a><a name="p1016863281093537"></a><a href="SamgrLite.md#a46f630c5a037c569a5b7806b4f8804ad">UnregisterDefaultFeatureApi</a> )(const char *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p212748246093537"><a name="p212748246093537"></a><a name="p212748246093537"></a><a href="IUnknown.md">IUnknown</a> *(*&nbsp;</p>
<p id="p1091787029093537"><a name="p1091787029093537"></a><a name="p1091787029093537"></a>Unregisters the API from the default feature of a service. </p>
</td>
</tr>
<tr id="row672556310093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p628328212093537"><a name="p628328212093537"></a><a name="p628328212093537"></a><a href="SamgrLite.md#a9c1a5452e501478a984a1220f550efba">RegisterFeatureApi</a> )(const char *service, const char *feature, <a href="IUnknown.md">IUnknown</a> *publicApi)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452872425093537"><a name="p452872425093537"></a><a name="p452872425093537"></a>BOOL(*&nbsp;</p>
<p id="p693129069093537"><a name="p693129069093537"></a><a name="p693129069093537"></a>Registers the API for a feature. </p>
</td>
</tr>
<tr id="row1811976353093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1410339976093537"><a name="p1410339976093537"></a><a name="p1410339976093537"></a><a href="SamgrLite.md#a2e33f34b97159b6673dff37e675ed844">UnregisterFeatureApi</a> )(const char *service, const char *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389366755093537"><a name="p1389366755093537"></a><a name="p1389366755093537"></a><a href="IUnknown.md">IUnknown</a> *(*&nbsp;</p>
<p id="p454184845093537"><a name="p454184845093537"></a><a name="p454184845093537"></a>Unregisters the API from a feature. </p>
</td>
</tr>
<tr id="row2099357360093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1114449991093537"><a name="p1114449991093537"></a><a name="p1114449991093537"></a><a href="SamgrLite.md#ac9d054e649b089ce256128ea4731cf57">GetDefaultFeatureApi</a> )(const char *service)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623245025093537"><a name="p623245025093537"></a><a name="p623245025093537"></a><a href="IUnknown.md">IUnknown</a> *(*&nbsp;</p>
<p id="p1706014366093537"><a name="p1706014366093537"></a><a name="p1706014366093537"></a>Obtains the API specific to the default feature. </p>
</td>
</tr>
<tr id="row536225684093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453851631093537"><a name="p1453851631093537"></a><a name="p1453851631093537"></a><a href="SamgrLite.md#aad5c8419acea291e00059f79f8e6c8d1">GetFeatureApi</a> )(const char *serviceName, const char *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9337167093537"><a name="p9337167093537"></a><a name="p9337167093537"></a><a href="IUnknown.md">IUnknown</a> *(*&nbsp;</p>
<p id="p90192133093537"><a name="p90192133093537"></a><a name="p90192133093537"></a>Obtains the API specific to the feature. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section134012088093537"></a>

## **Field Documentation**<a name="section11130688093537"></a>

## GetDefaultFeatureApi<a name="ac9d054e649b089ce256128ea4731cf57"></a>

```
[IUnknown](IUnknown.md)*(* SamgrLite::GetDefaultFeatureApi) (const char *service)
```

 **Description:**

Obtains the API specific to the default feature. 

You need to call this function before using the system capabilities of the service involved. 

**Parameters:**

<a name="table1871000344093537"></a>
<table><thead align="left"><tr id="row1793391960093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p414885184093537"><a name="p414885184093537"></a><a name="p414885184093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1487441917093537"><a name="p1487441917093537"></a><a name="p1487441917093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1104928820093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service to which the default feature belongs. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **[IUnknown](IUnknown.md)  \***  object that can be called if the operation is successful; returns  **NULL**  if the operation fails. 



## GetFeatureApi<a name="aad5c8419acea291e00059f79f8e6c8d1"></a>

```
[IUnknown](IUnknown.md)*(* SamgrLite::GetFeatureApi) (const char *serviceName, const char *feature)
```

 **Description:**

Obtains the API specific to the feature. 

You need to call this function before using the system capabilities of the service involved. 

**Parameters:**

<a name="table527600956093537"></a>
<table><thead align="left"><tr id="row1825291866093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p581675938093537"><a name="p581675938093537"></a><a name="p581675938093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p461444820093537"><a name="p461444820093537"></a><a name="p461444820093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row389149808093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service to which the feature belongs. </td>
</tr>
<tr id="row218108669093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature whose API will be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **[IUnknown](IUnknown.md)  \***  object that can be called if the operation is successful; returns  **NULL**  if the operation fails. 



## RegisterDefaultFeatureApi<a name="aafa34cfe11f389b208e90ba451000c1d"></a>

```
BOOL(* SamgrLite::RegisterDefaultFeatureApi) (const char *service, [IUnknown](IUnknown.md) *publicApi)
```

 **Description:**

Registers the API for the default feature of a service. 

You need to call this function after the service is registered. The pointers to the  [IUnknown](IUnknown.md)  and  [IUnknown](IUnknown.md)  members to be registered cannot be empty. 

**Parameters:**

<a name="table1024843243093537"></a>
<table><thead align="left"><tr id="row1708279366093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p608997258093537"><a name="p608997258093537"></a><a name="p608997258093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1610165492093537"><a name="p1610165492093537"></a><a name="p1610165492093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1419184743093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose default feature's API will be registered. </td>
</tr>
<tr id="row614462528093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">publicApi</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the API to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## RegisterFeature<a name="a05153cf073a1373bac53a0a1c2030ba0"></a>

```
BOOL(* SamgrLite::RegisterFeature) (const char *serviceName, [Feature](Feature.md) *feature)
```

 **Description:**

Registers a feature. 

You need to call this function in the startup entry of each feature.  [Feature](Feature.md)  and  [Feature](Feature.md)  structure members to be registered cannot be empty. 

**Parameters:**

<a name="table335745524093537"></a>
<table><thead align="left"><tr id="row1697845200093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1735608225093537"><a name="p1735608225093537"></a><a name="p1735608225093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p613000058093537"><a name="p613000058093537"></a><a name="p613000058093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row586272207093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the feature to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## RegisterFeatureApi<a name="a9c1a5452e501478a984a1220f550efba"></a>

```
BOOL(* SamgrLite::RegisterFeatureApi) (const char *service, const char *feature, [IUnknown](IUnknown.md) *publicApi)
```

 **Description:**

Registers the API for a feature. 

You can call this function only if the feature has been registered. The pointers to the  [IUnknown](IUnknown.md)  and  [IUnknown](IUnknown.md)  members to be registered cannot be empty. 

**Parameters:**

<a name="table965359820093537"></a>
<table><thead align="left"><tr id="row1655599050093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p987446952093537"><a name="p987446952093537"></a><a name="p987446952093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p679650700093537"><a name="p679650700093537"></a><a name="p679650700093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1428448578093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose API will be registered. </td>
</tr>
<tr id="row2023687729093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature whose API will be registered. </td>
</tr>
<tr id="row1428111623093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">publicApi</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the API to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## RegisterService<a name="a9adf6d526e11688ad318229487cfc0b4"></a>

```
BOOL(* SamgrLite::RegisterService) ([Service](Service.md) *service)
```

 **Description:**

Registers a service. 

You need to call this function in the startup entry of each service.  [Service](Service.md)  and  [Service](Service.md)  structure members to be registered cannot be empty. 

**Parameters:**

<a name="table250377511093537"></a>
<table><thead align="left"><tr id="row886522953093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1407710681093537"><a name="p1407710681093537"></a><a name="p1407710681093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1267449487093537"><a name="p1267449487093537"></a><a name="p1267449487093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1984524551093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the service to be registered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the registration is successful; returns  **FALSE**  if the registration fails. 



## UnregisterDefaultFeatureApi<a name="a46f630c5a037c569a5b7806b4f8804ad"></a>

```
[IUnknown](IUnknown.md)*(* SamgrLite::UnregisterDefaultFeatureApi) (const char *service)
```

 **Description:**

Unregisters the API from the default feature of a service. 

You need to call this function to unregister  [IUnknown](IUnknown.md)  if the service to which the default feature belongs is no longer required. 

**Parameters:**

<a name="table845264915093537"></a>
<table><thead align="left"><tr id="row1369581526093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1369031874093537"><a name="p1369031874093537"></a><a name="p1369031874093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1141562795093537"><a name="p1141562795093537"></a><a name="p1141562795093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2064803223093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose default feature's API will be unregistered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the unregistered function object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



## UnregisterFeature<a name="a03c53143dae167f685d796f3a806a574"></a>

```
[Feature](Feature.md)*(* SamgrLite::UnregisterFeature) (const char *serviceName, const char *featureName)
```

 **Description:**

Unregisters a feature. 

You need to call this function when the feature is no longer required. 

**Parameters:**

<a name="table1167498328093537"></a>
<table><thead align="left"><tr id="row167750449093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2035087748093537"><a name="p2035087748093537"></a><a name="p2035087748093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p801677310093537"><a name="p801677310093537"></a><a name="p801677310093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1368026482093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">serviceName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose feature will be unregistered. </td>
</tr>
<tr id="row1070205882093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">featureName</td>
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
[IUnknown](IUnknown.md)*(* SamgrLite::UnregisterFeatureApi) (const char *service, const char *feature)
```

 **Description:**

Unregisters the API from a feature. 

You must call this function before unregistering the feature no longer required. 

**Parameters:**

<a name="table416655057093537"></a>
<table><thead align="left"><tr id="row2066047855093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2084776537093537"><a name="p2084776537093537"></a><a name="p2084776537093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1296516676093537"><a name="p1296516676093537"></a><a name="p1296516676093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row155246309093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">service</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service whose API will be unregistered. </td>
</tr>
<tr id="row1796399631093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the feature whose API will be unregistered. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the unregistered function object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



## UnregisterService<a name="a3cebb3773860e67de745ac24021e63b0"></a>

```
[Service](Service.md)*(* SamgrLite::UnregisterService) (const char *name)
```

 **Description:**

Unregisters a service. 

You need to call this function when the service is no longer required. 

**Parameters:**

<a name="table494372439093537"></a>
<table><thead align="left"><tr id="row578354547093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1169089698093537"><a name="p1169089698093537"></a><a name="p1169089698093537"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p51176289093537"><a name="p51176289093537"></a><a name="p51176289093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1664126631093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the service to be unregistered. </td>
</tr>
</tbody>
</table>

**Attention:**

Before unregistering the service, you must unregister its features and functions. 

**Returns:**

Returns the unregistered service object if the unregistration is successful. The memory is released by the caller. Returns  **NULL**  if the unregistration fails. 



