# MultiMedia\_Camera<a name="ZH-CN_TOPIC_0000001055039470"></a>

## **Overview**<a name="section856510642084827"></a>

Defines the  **Camera**  class for camera-related operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1695418025084827"></a>

## Files<a name="files"></a>

<a name="table1191060477084827"></a>
<table><thead align="left"><tr id="row556418638084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p439646740084827"><a name="p439646740084827"></a><a name="p439646740084827"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1419641004084827"><a name="p1419641004084827"></a><a name="p1419641004084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1195358678084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386961104084827"><a name="p386961104084827"></a><a name="p386961104084827"></a><a href="camera-h.md">camera.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970304108084827"><a name="p1970304108084827"></a><a name="p1970304108084827"></a>Declares functions in the <strong id="b270869705084827"><a name="b270869705084827"></a><a name="b270869705084827"></a>Camera</strong> class to implement camera operations. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table266506589084827"></a>
<table><thead align="left"><tr id="row1371850475084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1147925292084827"><a name="p1147925292084827"></a><a name="p1147925292084827"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1853686083084827"><a name="p1853686083084827"></a><a name="p1853686083084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row558515897084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905275131084827"><a name="p1905275131084827"></a><a name="p1905275131084827"></a><a href="OHOS-Media-Camera.md">OHOS::Media::Camera</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p934468959084827"><a name="p934468959084827"></a><a name="p934468959084827"></a>Provides functions in the <strong id="b602519847084827"><a name="b602519847084827"></a><a name="b602519847084827"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> class to implement camera operations. operations. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table290411624084827"></a>
<table><thead align="left"><tr id="row209230622084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p874604836084827"><a name="p874604836084827"></a><a name="p874604836084827"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1355810737084827"><a name="p1355810737084827"></a><a name="p1355810737084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1628072791084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1736470196084827"><a name="p1736470196084827"></a><a name="p1736470196084827"></a><a href="MultiMedia_Camera.md#gab24c0e4ca1e15bb2a481fb1550955611">OHOS::Media::Camera::~Camera</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218600620084827"><a name="p218600620084827"></a><a name="p218600620084827"></a>virtual&nbsp;</p>
<p id="p640990420084827"><a name="p640990420084827"></a><a name="p640990420084827"></a>A destructor used to delete the <strong id="b1540017561084827"><a name="b1540017561084827"></a><a name="b1540017561084827"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> instance. </p>
</td>
</tr>
<tr id="row724054503084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645995091084827"><a name="p645995091084827"></a><a name="p645995091084827"></a><a href="MultiMedia_Camera.md#ga4b6fec3c9290e7d388147dcdd288b918">OHOS::Media::Camera::GetCameraId</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462751851084827"><a name="p1462751851084827"></a><a name="p1462751851084827"></a>virtual std::string&nbsp;</p>
<p id="p1918879995084827"><a name="p1918879995084827"></a><a name="p1918879995084827"></a>Obtains the camera ID. </p>
</td>
</tr>
<tr id="row1256935035084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1604180431084827"><a name="p1604180431084827"></a><a name="p1604180431084827"></a><a href="MultiMedia_Camera.md#ga04cc021b827824d0363037b630326264">OHOS::Media::Camera::GetCameraConfig</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519118055084827"><a name="p519118055084827"></a><a name="p519118055084827"></a>virtual const <a href="OHOS-Media-CameraConfig.md">CameraConfig</a> *&nbsp;</p>
<p id="p816403533084827"><a name="p816403533084827"></a><a name="p816403533084827"></a>Obtains the camera configuration. You can use the obtained <strong id="b544489032084827"><a name="b544489032084827"></a><a name="b544489032084827"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> object to configure the camera. </p>
</td>
</tr>
<tr id="row532846220084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1818245845084827"><a name="p1818245845084827"></a><a name="p1818245845084827"></a><a href="MultiMedia_Camera.md#ga4e3f97ac484b85cd221a996689a3de61">OHOS::Media::Camera::GetFrameConfig</a> (int32_t type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246791770084827"><a name="p246791770084827"></a><a name="p246791770084827"></a>virtual <a href="OHOS-Media-FrameConfig.md">FrameConfig</a> *&nbsp;</p>
<p id="p1657103706084827"><a name="p1657103706084827"></a><a name="p1657103706084827"></a>Obtains the frame configuration. </p>
</td>
</tr>
<tr id="row891780585084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p354461499084827"><a name="p354461499084827"></a><a name="p354461499084827"></a><a href="MultiMedia_Camera.md#ga5f240a74fefa168cbf94b4603b76ef7b">OHOS::Media::Camera::Configure</a> (<a href="OHOS-Media-CameraConfig.md">CameraConfig</a> &amp;config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p853646593084827"><a name="p853646593084827"></a><a name="p853646593084827"></a>virtual void&nbsp;</p>
<p id="p4046432084827"><a name="p4046432084827"></a><a name="p4046432084827"></a>Configures the camera using the <strong id="b319916701084827"><a name="b319916701084827"></a><a name="b319916701084827"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> object. </p>
</td>
</tr>
<tr id="row1303477917084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1002446667084827"><a name="p1002446667084827"></a><a name="p1002446667084827"></a><a href="MultiMedia_Camera.md#ga1cd68b1b385da5224dbfdb6993c5cf08">OHOS::Media::Camera::TriggerLoopingCapture</a> (<a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1704363650084827"><a name="p1704363650084827"></a><a name="p1704363650084827"></a>virtual int32_t&nbsp;</p>
<p id="p232411056084827"><a name="p232411056084827"></a><a name="p232411056084827"></a>Triggers looping-frame capture. </p>
</td>
</tr>
<tr id="row34772695084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1026540319084827"><a name="p1026540319084827"></a><a name="p1026540319084827"></a><a href="MultiMedia_Camera.md#ga564c26b845affb1dbe05d4d7982ed1ad">OHOS::Media::Camera::StopLoopingCapture</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p666626720084827"><a name="p666626720084827"></a><a name="p666626720084827"></a>virtual void&nbsp;</p>
<p id="p1961259597084827"><a name="p1961259597084827"></a><a name="p1961259597084827"></a>Stops looping-frame capture. </p>
</td>
</tr>
<tr id="row1886153005084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1844442938084827"><a name="p1844442938084827"></a><a name="p1844442938084827"></a><a href="MultiMedia_Camera.md#gac05d783b1655fe505a4afa23496d7e84">OHOS::Media::Camera::TriggerSingleCapture</a> (<a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456476069084827"><a name="p1456476069084827"></a><a name="p1456476069084827"></a>virtual int32_t&nbsp;</p>
<p id="p2074319233084827"><a name="p2074319233084827"></a><a name="p2074319233084827"></a>Starts single-frame capture. The frame parameters are set through the <strong id="b337054500084827"><a name="b337054500084827"></a><a name="b337054500084827"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> object, and the captured image data is stored in the surface of the <strong id="b2085080791084827"><a name="b2085080791084827"></a><a name="b2085080791084827"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> object. </p>
</td>
</tr>
<tr id="row1672174510084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2072359526084827"><a name="p2072359526084827"></a><a name="p2072359526084827"></a><a href="MultiMedia_Camera.md#ga7986d17e54fe9cd77df9465287fa5643">OHOS::Media::Camera::Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p425542048084827"><a name="p425542048084827"></a><a name="p425542048084827"></a>virtual void&nbsp;</p>
<p id="p90303236084827"><a name="p90303236084827"></a><a name="p90303236084827"></a>Releases the <strong id="b165918348084827"><a name="b165918348084827"></a><a name="b165918348084827"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> object and associated resources. </p>
</td>
</tr>
<tr id="row32036374084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339246978084827"><a name="p339246978084827"></a><a name="p339246978084827"></a><a href="MultiMedia_Camera.md#ga7df4eba3316a6fe7c623e420c0a295e5">OHOS::Media::Camera::Camera</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010712204084827"><a name="p2010712204084827"></a><a name="p2010712204084827"></a>&nbsp;</p>
<p id="p421972722084827"><a name="p421972722084827"></a><a name="p421972722084827"></a>A constructor used to create a <strong id="b2013534300084827"><a name="b2013534300084827"></a><a name="b2013534300084827"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> instance. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1410779650084827"></a>

## **Function Documentation**<a name="section592882430084827"></a>

## Camera\(\)<a name="ga7df4eba3316a6fe7c623e420c0a295e5"></a>

```
OHOS::Media::Camera::Camera ()
```

 **Description:**

A constructor used to create a  **[Camera](OHOS-Media-Camera.md)**  instance. 

## Configure\(\)<a name="ga5f240a74fefa168cbf94b4603b76ef7b"></a>

```
virtual void OHOS::Media::Camera::Configure ([CameraConfig](OHOS-Media-CameraConfig.md) & config)
```

 **Description:**

Configures the camera using the  **[CameraConfig](OHOS-Media-CameraConfig.md)**  object. 

**Parameters:**

<a name="table530741413084827"></a>
<table><thead align="left"><tr id="row350703700084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p602019674084827"><a name="p602019674084827"></a><a name="p602019674084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p242499538084827"><a name="p242499538084827"></a><a name="p242499538084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1333502601084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">config</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1227317408084827"><a name="b1227317408084827"></a><a name="b1227317408084827"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> object. </td>
</tr>
</tbody>
</table>

## GetCameraConfig\(\)<a name="ga04cc021b827824d0363037b630326264"></a>

```
virtual const [CameraConfig](OHOS-Media-CameraConfig.md)* OHOS::Media::Camera::GetCameraConfig () const
```

 **Description:**

Obtains the camera configuration. You can use the obtained  **[CameraConfig](OHOS-Media-CameraConfig.md)**  object to configure the camera. 

**Returns:**

Returns the pointer to the  **[CameraConfig](OHOS-Media-CameraConfig.md)**  object if obtained; returns  **NULL**  otherwise. 



## GetCameraId\(\)<a name="ga4b6fec3c9290e7d388147dcdd288b918"></a>

```
virtual std::string OHOS::Media::Camera::GetCameraId ()
```

 **Description:**

Obtains the camera ID. 

**Returns:**

Returns the camera ID if obtained; returns the "Error" string if the camera fails to be created. 



## GetFrameConfig\(\)<a name="ga4e3f97ac484b85cd221a996689a3de61"></a>

```
virtual [FrameConfig](OHOS-Media-FrameConfig.md)* OHOS::Media::Camera::GetFrameConfig (int32_t type)
```

 **Description:**

Obtains the frame configuration. 

**Parameters:**

<a name="table269252482084827"></a>
<table><thead align="left"><tr id="row1990731937084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p193687814084827"><a name="p193687814084827"></a><a name="p193687814084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1670727326084827"><a name="p1670727326084827"></a><a name="p1670727326084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1389033079084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the frame configuration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the  **[FrameConfig](OHOS-Media-FrameConfig.md)**  object if obtained; returns  **NULL**  otherwise. 



## Release\(\)<a name="ga7986d17e54fe9cd77df9465287fa5643"></a>

```
virtual void OHOS::Media::Camera::Release ()
```

 **Description:**

Releases the  **[Camera](OHOS-Media-Camera.md)**  object and associated resources. 

## StopLoopingCapture\(\)<a name="ga564c26b845affb1dbe05d4d7982ed1ad"></a>

```
virtual void OHOS::Media::Camera::StopLoopingCapture ()
```

 **Description:**

Stops looping-frame capture. 

**Returns:**

Returns  **true**  if the looping-frame capture is successfully stopped; returns  **false**  otherwise. 



## TriggerLoopingCapture\(\)<a name="ga1cd68b1b385da5224dbfdb6993c5cf08"></a>

```
virtual int32_t OHOS::Media::Camera::TriggerLoopingCapture ([FrameConfig](OHOS-Media-FrameConfig.md) & frameConfig)
```

 **Description:**

Triggers looping-frame capture. 

**Parameters:**

<a name="table1344774064084827"></a>
<table><thead align="left"><tr id="row1141631070084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1718951211084827"><a name="p1718951211084827"></a><a name="p1718951211084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1336002590084827"><a name="p1336002590084827"></a><a name="p1336002590084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row134835942084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fc</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frame configuration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the looping-frame capture is successfully started; returns  **false**  otherwise. 



## TriggerSingleCapture\(\)<a name="gac05d783b1655fe505a4afa23496d7e84"></a>

```
virtual int32_t OHOS::Media::Camera::TriggerSingleCapture ([FrameConfig](OHOS-Media-FrameConfig.md) & frameConfig)
```

 **Description:**

Starts single-frame capture. The frame parameters are set through the  **[FrameConfig](OHOS-Media-FrameConfig.md)**  object, and the captured image data is stored in the surface of the  **[FrameConfig](OHOS-Media-FrameConfig.md)**  object. 

**Parameters:**

<a name="table1005782263084827"></a>
<table><thead align="left"><tr id="row230903783084827"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p629992173084827"><a name="p629992173084827"></a><a name="p629992173084827"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p678279672084827"><a name="p678279672084827"></a><a name="p678279672084827"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row594595840084827"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fc</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frame configuration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the single-frame capture is successfully started and the data is stored; returns  **false**  otherwise. 



## \~Camera\(\)<a name="gab24c0e4ca1e15bb2a481fb1550955611"></a>

```
virtual OHOS::Media::Camera::~Camera ()
```

 **Description:**

A destructor used to delete the  **[Camera](OHOS-Media-Camera.md)**  instance. 

