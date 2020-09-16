# MultiMedia\_CameraConfig<a name="EN-US_TOPIC_0000001054879486"></a>

## **Overview**<a name="section2065693153084827"></a>

Defines the  **CameraConfig**  class for operations on camera configurations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section650735462084827"></a>

## Files<a name="files"></a>

<a name="table772330619084827"></a>
<table><thead align="left"><tr id="row1226836154084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p267224960084827"><a name="p267224960084827"></a><a name="p267224960084827"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p22340430084827"><a name="p22340430084827"></a><a name="p22340430084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1310624425084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1072440167084827"><a name="p1072440167084827"></a><a name="p1072440167084827"></a><a href="camera_config-h.md">camera_config.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27621879084827"><a name="p27621879084827"></a><a name="p27621879084827"></a>Declares functions in the <strong id="b924191132084827"><a name="b924191132084827"></a><a name="b924191132084827"></a>CameraConfig</strong> class. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1447572612084827"></a>
<table><thead align="left"><tr id="row1604257412084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1387809056084827"><a name="p1387809056084827"></a><a name="p1387809056084827"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2098853569084827"><a name="p2098853569084827"></a><a name="p2098853569084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row773803074084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870179372084827"><a name="p870179372084827"></a><a name="p870179372084827"></a><a href="ohos-media-cameraconfig.md">OHOS::Media::CameraConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1651535233084827"><a name="p1651535233084827"></a><a name="p1651535233084827"></a>Provides functions to configure camera parameters. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1301233553084827"></a>
<table><thead align="left"><tr id="row158537118084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1625645276084827"><a name="p1625645276084827"></a><a name="p1625645276084827"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p477934866084827"><a name="p477934866084827"></a><a name="p477934866084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row925804857084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065902135084827"><a name="p1065902135084827"></a><a name="p1065902135084827"></a><a href="multimedia_cameraconfig.md#ga6730b1ff3808a97fe7095c1cd016d47c">OHOS::Media::CameraConfig::~CameraConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p16776385084827"><a name="p16776385084827"></a><a name="p16776385084827"></a>virtual </p>
<p id="p1467157836084827"><a name="p1467157836084827"></a><a name="p1467157836084827"></a>A destructor used to delete the <strong id="b123502847084827"><a name="b123502847084827"></a><a name="b123502847084827"></a><a href="ohos-media-cameraability.md">CameraAbility</a></strong> instance. </p>
</td>
</tr>
<tr id="row1577641454084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584734280084827"><a name="p584734280084827"></a><a name="p584734280084827"></a><a href="multimedia_cameraconfig.md#ga26f37610abb783b48d3e94662523fa94">OHOS::Media::CameraConfig::CreateCameraConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847989033084827"><a name="p1847989033084827"></a><a name="p1847989033084827"></a>static <a href="ohos-media-cameraconfig.md">CameraConfig</a> * </p>
<p id="p561520279084827"><a name="p561520279084827"></a><a name="p561520279084827"></a>Creates the <strong id="b1658171158084827"><a name="b1658171158084827"></a><a name="b1658171158084827"></a><a href="ohos-media-cameraconfig.md">CameraConfig</a></strong> instance of this singleton class to configure and read the required parameters. </p>
</td>
</tr>
<tr id="row1156821085084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288373410084827"><a name="p1288373410084827"></a><a name="p1288373410084827"></a><a href="multimedia_cameraconfig.md#gaf6d7f82e9439dce13b0213f84a35ab59">OHOS::Media::CameraConfig::SetFrameStateCallback</a> (<a href="ohos-media-framestatecallback.md">FrameStateCallback</a> *callback, EventHandler *handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492603334084827"><a name="p1492603334084827"></a><a name="p1492603334084827"></a>virtual void </p>
<p id="p1811954312084827"><a name="p1811954312084827"></a><a name="p1811954312084827"></a>Sets a frame state callback to responds to state changes. </p>
</td>
</tr>
<tr id="row782651004084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1444855945084827"><a name="p1444855945084827"></a><a name="p1444855945084827"></a><a href="multimedia_cameraconfig.md#ga65d8bb0bd5d996e51e4c6fa12a33931b">OHOS::Media::CameraConfig::GetEventHandler</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090826937084827"><a name="p1090826937084827"></a><a name="p1090826937084827"></a>virtual EventHandler * </p>
<p id="p982317400084827"><a name="p982317400084827"></a><a name="p982317400084827"></a>Obtains the <strong id="b194259803084827"><a name="b194259803084827"></a><a name="b194259803084827"></a>EventHandler</strong> object. </p>
</td>
</tr>
<tr id="row909311608084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31463626084827"><a name="p31463626084827"></a><a name="p31463626084827"></a><a href="multimedia_cameraconfig.md#gae4864312836d34b9ad56675ed3e523a1">OHOS::Media::CameraConfig::GetFrameStateCb</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510514141084827"><a name="p1510514141084827"></a><a name="p1510514141084827"></a>virtual <a href="ohos-media-framestatecallback.md">FrameStateCallback</a> * </p>
<p id="p1595165756084827"><a name="p1595165756084827"></a><a name="p1595165756084827"></a>Obtains a <strong id="b239668642084827"><a name="b239668642084827"></a><a name="b239668642084827"></a><a href="ohos-media-framestatecallback.md">FrameStateCallback</a></strong> object. </p>
</td>
</tr>
<tr id="row1835173130084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1459313853084827"><a name="p1459313853084827"></a><a name="p1459313853084827"></a><a href="multimedia_cameraconfig.md#ga6cca70f5dea34d6ede94d0b258c0a350">OHOS::Media::CameraConfig::CameraConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436664204084827"><a name="p436664204084827"></a><a name="p436664204084827"></a> </p>
<p id="p2027514996084827"><a name="p2027514996084827"></a><a name="p2027514996084827"></a>A constructor used to create a <strong id="b1876827907084827"><a name="b1876827907084827"></a><a name="b1876827907084827"></a><a href="ohos-media-cameraconfig.md">CameraConfig</a></strong> instance. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section357875270084827"></a>

## **Function Documentation**<a name="section1003437333084827"></a>

## CameraConfig\(\)<a name="ga6cca70f5dea34d6ede94d0b258c0a350"></a>

```
OHOS::Media::CameraConfig::CameraConfig ()
```

 **Description:**

A constructor used to create a  **[CameraConfig](ohos-media-cameraconfig.md)**  instance. 

## CreateCameraConfig\(\)<a name="ga26f37610abb783b48d3e94662523fa94"></a>

```
static [CameraConfig](ohos-media-cameraconfig.md)* OHOS::Media::CameraConfig::CreateCameraConfig ()
```

 **Description:**

Creates the  **[CameraConfig](ohos-media-cameraconfig.md)**  instance of this singleton class to configure and read the required parameters. 

**Returns:**

Returns the  **[CameraConfig](ohos-media-cameraconfig.md)**  instance if created; returns  **NULL**  otherwise. 



## GetEventHandler\(\)<a name="ga65d8bb0bd5d996e51e4c6fa12a33931b"></a>

```
virtual EventHandler* OHOS::Media::CameraConfig::GetEventHandler () const
```

 **Description:**

Obtains the  **EventHandler**  object. 

**Returns:**

Returns the pointer to the  **EventHandler**  object if obtained; returns  **NULL**  otherwise. 



## GetFrameStateCb\(\)<a name="gae4864312836d34b9ad56675ed3e523a1"></a>

```
virtual [FrameStateCallback](ohos-media-framestatecallback.md)* OHOS::Media::CameraConfig::GetFrameStateCb () const
```

 **Description:**

Obtains a  **[FrameStateCallback](ohos-media-framestatecallback.md)**  object. 

**Returns:**

Returns the pointer to the  **[FrameStateCallback](ohos-media-framestatecallback.md)**  object if obtained; returns  **NULL**  otherwise. 



## SetFrameStateCallback\(\)<a name="gaf6d7f82e9439dce13b0213f84a35ab59"></a>

```
virtual void OHOS::Media::CameraConfig::SetFrameStateCallback ([FrameStateCallback](ohos-media-framestatecallback.md) * callback, EventHandler * handler )
```

 **Description:**

Sets a frame state callback to responds to state changes. 

**Parameters:**

<a name="table2045311558084827"></a>
<table><thead align="left"><tr id="row721560332084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1944190132084827"><a name="p1944190132084827"></a><a name="p1944190132084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1911600946084827"><a name="p1911600946084827"></a><a name="p1911600946084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row894139932084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">callback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frame state callback. </td>
</tr>
<tr id="row1840249745084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event handler. </td>
</tr>
</tbody>
</table>

## \~CameraConfig\(\)<a name="ga6730b1ff3808a97fe7095c1cd016d47c"></a>

```
virtual OHOS::Media::CameraConfig::~CameraConfig ()
```

 **Description:**

A destructor used to delete the  **[CameraAbility](ohos-media-cameraability.md)**  instance. 

