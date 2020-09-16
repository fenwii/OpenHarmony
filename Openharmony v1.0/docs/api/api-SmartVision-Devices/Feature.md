# Feature<a name="ZH-CN_TOPIC_0000001055518086"></a>

## **Overview**<a name="section989380084093530"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Defines the base class of a feature. 

You need to implement the pointer to the feature. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section991844430093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2147361412093530"></a>
<table><thead align="left"><tr id="row11144604093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1021013427093530"><a name="p1021013427093530"></a><a name="p1021013427093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p811718199093530"><a name="p811718199093530"></a><a name="p811718199093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row909205846093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1537706196093530"><a name="p1537706196093530"></a><a name="p1537706196093530"></a><a href="Feature.md#ab30dc9677abd4aaa18ec88254e90b139">GetName</a> )(<a href="Feature.md">Feature</a> *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635690443093530"><a name="p1635690443093530"></a><a name="p1635690443093530"></a>const char *(*&nbsp;</p>
<p id="p868669120093530"><a name="p868669120093530"></a><a name="p868669120093530"></a>Obtains a feature name. </p>
</td>
</tr>
<tr id="row1955292831093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807171937093530"><a name="p1807171937093530"></a><a name="p1807171937093530"></a><a href="Feature.md#adb3f9401f41e2309006568ef6e78fd43">OnInitialize</a> )(<a href="Feature.md">Feature</a> *feature, <a href="Service.md">Service</a> *parent, <a href="Identity.md">Identity</a> identity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424984730093530"><a name="p1424984730093530"></a><a name="p1424984730093530"></a>void(*&nbsp;</p>
<p id="p1928763897093530"><a name="p1928763897093530"></a><a name="p1928763897093530"></a>Initializes a feature. </p>
</td>
</tr>
<tr id="row1433344278093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1907551590093530"><a name="p1907551590093530"></a><a name="p1907551590093530"></a><a href="Feature.md#ab0a4b92d867106b10f3fd3c4761338ba">OnStop</a> )(<a href="Feature.md">Feature</a> *feature, <a href="Identity.md">Identity</a> identity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1945442908093530"><a name="p1945442908093530"></a><a name="p1945442908093530"></a>void(*&nbsp;</p>
<p id="p2002872179093530"><a name="p2002872179093530"></a><a name="p2002872179093530"></a>Stops a feature. </p>
</td>
</tr>
<tr id="row1597329360093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1206771491093530"><a name="p1206771491093530"></a><a name="p1206771491093530"></a><a href="Feature.md#adf249c7a1b07eb47d51f046c5c8a5f6b">OnMessage</a> )(<a href="Feature.md">Feature</a> *feature, <a href="Request.md">Request</a> *request)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725262940093530"><a name="p1725262940093530"></a><a name="p1725262940093530"></a>BOOL(*&nbsp;</p>
<p id="p1752420691093530"><a name="p1752420691093530"></a><a name="p1752420691093530"></a>Processes a feature message. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1969258885093530"></a>

## **Field Documentation**<a name="section107628635093530"></a>

## GetName<a name="ab30dc9677abd4aaa18ec88254e90b139"></a>

```
const char*(* Feature::GetName) ([Feature](Feature.md) *feature)
```

 **Description:**

Obtains a feature name. 

This function is implemented by developers and called by Samgr during feature registration and startup. 

**Parameters:**

<a name="table1555701909093530"></a>
<table><thead align="left"><tr id="row1426312071093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1930084727093530"><a name="p1930084727093530"></a><a name="p1930084727093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1057242264093530"><a name="p1057242264093530"></a><a name="p1057242264093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1948162938093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
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

<a name="table497358319093530"></a>
<table><thead align="left"><tr id="row1904700960093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1751017937093530"><a name="p1751017937093530"></a><a name="p1751017937093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p604188105093530"><a name="p604188105093530"></a><a name="p604188105093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row286353037093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
<tr id="row1073291468093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">parent</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="Service.md">Service</a> to which the feature belongs. </td>
</tr>
<tr id="row32670223093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
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

<a name="table713809527093530"></a>
<table><thead align="left"><tr id="row1802353114093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1321034633093530"><a name="p1321034633093530"></a><a name="p1321034633093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1860585962093530"><a name="p1860585962093530"></a><a name="p1860585962093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1674520627093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
<tr id="row754750198093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">request</td>
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

<a name="table320452396093530"></a>
<table><thead align="left"><tr id="row2052276470093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1690570197093530"><a name="p1690570197093530"></a><a name="p1690570197093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1113049211093530"><a name="p1113049211093530"></a><a name="p1113049211093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1130713780093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">feature</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature. </td>
</tr>
<tr id="row440071074093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identity</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <a href="Identity.md">Identity</a> of the feature to be stopped. </td>
</tr>
</tbody>
</table>

