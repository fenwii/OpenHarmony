# Feature<a name="ZH-CN_TOPIC_0000001055075077"></a>

## **Overview**<a name="section641091163191859"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines the base class of a feature. 

You need to implement the pointer to the feature. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section254447348191859"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1185251834191859"></a>
<table><thead align="left"><tr id="row1192735128191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p192074553191859"><a name="p192074553191859"></a><a name="p192074553191859"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1573389215191859"><a name="p1573389215191859"></a><a name="p1573389215191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row889802731191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p520701418191859"><a name="p520701418191859"></a><a name="p520701418191859"></a><a href="Feature.md#ab30dc9677abd4aaa18ec88254e90b139">GetName</a> )(<a href="Feature.md">Feature</a> *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p950751226191859"><a name="p950751226191859"></a><a name="p950751226191859"></a>const char *(*&nbsp;</p>
<p id="p790418287191859"><a name="p790418287191859"></a><a name="p790418287191859"></a>Obtains a feature name. </p>
</td>
</tr>
<tr id="row754926357191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p573792740191859"><a name="p573792740191859"></a><a name="p573792740191859"></a><a href="Feature.md#adb3f9401f41e2309006568ef6e78fd43">OnInitialize</a> )(<a href="Feature.md">Feature</a> *feature, <a href="Service.md">Service</a> *parent, <a href="Identity.md">Identity</a> identity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p542788653191859"><a name="p542788653191859"></a><a name="p542788653191859"></a>void(*&nbsp;</p>
<p id="p1333784828191859"><a name="p1333784828191859"></a><a name="p1333784828191859"></a>Initializes a feature. </p>
</td>
</tr>
<tr id="row1569510463191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037399587191859"><a name="p2037399587191859"></a><a name="p2037399587191859"></a><a href="Feature.md#ab0a4b92d867106b10f3fd3c4761338ba">OnStop</a> )(<a href="Feature.md">Feature</a> *feature, <a href="Identity.md">Identity</a> identity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1217121673191859"><a name="p1217121673191859"></a><a name="p1217121673191859"></a>void(*&nbsp;</p>
<p id="p86055290191859"><a name="p86055290191859"></a><a name="p86055290191859"></a>Stops a feature. </p>
</td>
</tr>
<tr id="row152488638191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1993118767191859"><a name="p1993118767191859"></a><a name="p1993118767191859"></a><a href="Feature.md#adf249c7a1b07eb47d51f046c5c8a5f6b">OnMessage</a> )(<a href="Feature.md">Feature</a> *feature, <a href="Request.md">Request</a> *request)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p921531254191859"><a name="p921531254191859"></a><a name="p921531254191859"></a>BOOL(*&nbsp;</p>
<p id="p873550085191859"><a name="p873550085191859"></a><a name="p873550085191859"></a>Processes a feature message. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section74045155191859"></a>

## **Field Documentation**<a name="section1081675570191859"></a>

## GetName<a name="ab30dc9677abd4aaa18ec88254e90b139"></a>

```
const char*(* Feature::GetName) ([Feature](Feature.md) *feature)
```

 **Description:**

Obtains a feature name. 

This function is implemented by developers and called by Samgr during feature registration and startup. 

**Parameters:**

<a name="table956027843191859"></a>
<table><thead align="left"><tr id="row411967358191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1970088446191859"><a name="p1970088446191859"></a><a name="p1970088446191859"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1197047403191859"><a name="p1197047403191859"></a><a name="p1197047403191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1602321254191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a constant character string less than 16 bytes if the operation is successful; returns  **NULL**  if the operation fails.



## OnInitialize<a name="adb3f9401f41e2309006568ef6e78fd43"></a>

```
void(* Feature::OnInitialize) ([Feature](Feature.md) *feature, [Service](Service.md) *parent, [Identity](Identity.md) identity)
```

 **Description:**

Initializes a feature. 

This function is implemented by developers. After Samgr dispatches tasks to a service, the service calls this function in its own tasks. 

**Parameters:**

<a name="table1561129475191859"></a>
<table><thead align="left"><tr id="row24119258191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p764184387191859"><a name="p764184387191859"></a><a name="p764184387191859"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2084685651191859"><a name="p2084685651191859"></a><a name="p2084685651191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1210462227191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
<tr id="row2070722405191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">parent</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="Service.md">Service</a> to which the feature belongs. </td>
</tr>
<tr id="row1438612557191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the identity of a feature dispatched by the system.</td>
</tr>
</tbody>
</table>

## OnMessage<a name="adf249c7a1b07eb47d51f046c5c8a5f6b"></a>

```
BOOL(* Feature::OnMessage) ([Feature](Feature.md) *feature, [Request](Request.md) *request)
```

 **Description:**

Processes a feature message. 

This function is implemented by developers to process requests sent by callers through  [IUnknown](IUnknown.md). 

**Parameters:**

<a name="table1605201037191859"></a>
<table><thead align="left"><tr id="row193736922191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1169685648191859"><a name="p1169685648191859"></a><a name="p1169685648191859"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p726955922191859"><a name="p726955922191859"></a><a name="p726955922191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1019747092191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
<tr id="row305839513191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the request message. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **TRUE**  if the processing is successful; returns  **FALSE**  if the processing fails.



## OnStop<a name="ab0a4b92d867106b10f3fd3c4761338ba"></a>

```
void(* Feature::OnStop) ([Feature](Feature.md) *feature, [Identity](Identity.md) identity)
```

 **Description:**

Stops a feature. 

This function is implemented by developers and is called by Samgr when a feature is deregistered to stop running services. 

**Parameters:**

<a name="table929779141191859"></a>
<table><thead align="left"><tr id="row1680085306191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p937601161191859"><a name="p937601161191859"></a><a name="p937601161191859"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1503028611191859"><a name="p1503028611191859"></a><a name="p1503028611191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1960920096191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
<tr id="row1462550270191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="Identity.md">Identity</a> of the feature to be stopped. </td>
</tr>
</tbody>
</table>

