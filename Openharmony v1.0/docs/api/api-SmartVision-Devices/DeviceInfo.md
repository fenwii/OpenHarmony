# DeviceInfo<a name="ZH-CN_TOPIC_0000001055678088"></a>

## **Overview**<a name="section1535659843093529"></a>

**Related Modules:**

[Input](Input.md)

**Description:**

Describes basic device information of the input device. 

## **Summary**<a name="section409750682093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table971268846093529"></a>
<table><thead align="left"><tr id="row970273462093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2091062555093529"><a name="p2091062555093529"></a><a name="p2091062555093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1561579757093529"><a name="p1561579757093529"></a><a name="p1561579757093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row795195298093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897304273093529"><a name="p897304273093529"></a><a name="p897304273093529"></a><a href="DeviceInfo.md#a1582f8d7e63ac2a2c1a1511bb73aeafd">devIndex</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858450759093529"><a name="p858450759093529"></a><a name="p858450759093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1652250745093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p969033194093529"><a name="p969033194093529"></a><a name="p969033194093529"></a><a href="DeviceInfo.md#a8be40a9da438bed3c2f13bf2bf07217b">fd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p94945599093529"><a name="p94945599093529"></a><a name="p94945599093529"></a>int32_t&nbsp;</p>
</td>
</tr>
<tr id="row1017790068093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p546928465093529"><a name="p546928465093529"></a><a name="p546928465093529"></a><a href="DeviceInfo.md#aec5bff7e9a51ba2fc149156d83154448">devType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1180439288093529"><a name="p1180439288093529"></a><a name="p1180439288093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row232789043093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550354030093529"><a name="p550354030093529"></a><a name="p550354030093529"></a><a href="DeviceInfo.md#adcedf378ddac2489b2a6abc1970807df">powerStatus</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1714389050093529"><a name="p1714389050093529"></a><a name="p1714389050093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row222344885093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1599036742093529"><a name="p1599036742093529"></a><a name="p1599036742093529"></a><a href="DeviceInfo.md#a39b8ad5d23fb776ec333adbd64025691">chipInfo</a> [CHIP_INFO_LEN]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1676930840093529"><a name="p1676930840093529"></a><a name="p1676930840093529"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row590997148093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301613518093529"><a name="p301613518093529"></a><a name="p301613518093529"></a><a href="DeviceInfo.md#a24b2b30666e776c0637d7c3f2805bb04">vendorName</a> [VENDOR_NAME_LEN]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p219000273093529"><a name="p219000273093529"></a><a name="p219000273093529"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row1681502846093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386821713093529"><a name="p386821713093529"></a><a name="p386821713093529"></a><a href="DeviceInfo.md#ad6458f297131a4f3a9dba820e069d525">chipName</a> [CHIP_NAME_LEN]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764070093093529"><a name="p764070093093529"></a><a name="p764070093093529"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row980161667093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230478634093529"><a name="p230478634093529"></a><a name="p230478634093529"></a><a href="DeviceInfo.md#a47e7d5536f061f3e11934fd1ff4cf61b">devNodePath</a> [DEV_NODE_PATH]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p148856172093529"><a name="p148856172093529"></a><a name="p148856172093529"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row1134169526093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916430122093529"><a name="p1916430122093529"></a><a name="p1916430122093529"></a><a href="DeviceInfo.md#aba81fb331433f16cfcf435dd05c6e3c3">solutionX</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1033716316093529"><a name="p1033716316093529"></a><a name="p1033716316093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row217329566093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1012582925093529"><a name="p1012582925093529"></a><a name="p1012582925093529"></a><a href="DeviceInfo.md#a90174e4a421db368c2d179ab1bbb0f96">solutionY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549001088093529"><a name="p549001088093529"></a><a name="p549001088093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row666503704093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220179088093529"><a name="p1220179088093529"></a><a name="p1220179088093529"></a><a href="DeviceInfo.md#a90b6d7e07aa21e507a7b16f380df4fb8">callback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504307321093529"><a name="p504307321093529"></a><a name="p504307321093529"></a><a href="InputReportEventCb.md">InputReportEventCb</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section881067031093529"></a>

## **Field Documentation**<a name="section2035264712093529"></a>

## callback<a name="a90b6d7e07aa21e507a7b16f380df4fb8"></a>

```
[InputReportEventCb](InputReportEventCb.md)* DeviceInfo::callback
```

 **Description:**

Callback  [InputReportEventCb](InputReportEventCb.md)  for reporting data 

## chipInfo<a name="a39b8ad5d23fb776ec333adbd64025691"></a>

```
char DeviceInfo::chipInfo[CHIP_INFO_LEN]
```

 **Description:**

Driver chip information 

## chipName<a name="ad6458f297131a4f3a9dba820e069d525"></a>

```
char DeviceInfo::chipName[CHIP_NAME_LEN]
```

 **Description:**

Driver chip name 

## devIndex<a name="a1582f8d7e63ac2a2c1a1511bb73aeafd"></a>

```
uint32_t DeviceInfo::devIndex
```

 **Description:**

Device index 

## devNodePath<a name="a47e7d5536f061f3e11934fd1ff4cf61b"></a>

```
char DeviceInfo::devNodePath[DEV_NODE_PATH]
```

 **Description:**

Device file path 

## devType<a name="aec5bff7e9a51ba2fc149156d83154448"></a>

```
uint32_t DeviceInfo::devType
```

 **Description:**

Device type 

## fd<a name="a8be40a9da438bed3c2f13bf2bf07217b"></a>

```
int32_t DeviceInfo::fd
```

 **Description:**

File descriptor of the device 

## powerStatus<a name="adcedf378ddac2489b2a6abc1970807df"></a>

```
uint32_t DeviceInfo::powerStatus
```

 **Description:**

Power status 

## solutionX<a name="aba81fb331433f16cfcf435dd05c6e3c3"></a>

```
uint32_t DeviceInfo::solutionX
```

 **Description:**

Resolution in the X axis 

## solutionY<a name="a90174e4a421db368c2d179ab1bbb0f96"></a>

```
uint32_t DeviceInfo::solutionY
```

 **Description:**

Resolution in the Y axis 

## vendorName<a name="a24b2b30666e776c0637d7c3f2805bb04"></a>

```
char DeviceInfo::vendorName[VENDOR_NAME_LEN]
```

 **Description:**

Module vendor name 

