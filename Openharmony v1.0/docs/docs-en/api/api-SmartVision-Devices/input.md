# Input<a name="EN-US_TOPIC_0000001054879480"></a>

## **Overview**<a name="section1462253682093521"></a>

Provides driver interfaces for the input service. 

These driver interfaces can be used to open and close input device files, get input events, query device information, register callback functions, and control the feature status.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section885026033093521"></a>

## Files<a name="files"></a>

<a name="table1334895442093521"></a>
<table><thead align="left"><tr id="row1291015321093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p34968664093521"><a name="p34968664093521"></a><a name="p34968664093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1981326954093521"><a name="p1981326954093521"></a><a name="p1981326954093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row480012093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628546853093521"><a name="p1628546853093521"></a><a name="p1628546853093521"></a><a href="input_controller-h.md">input_controller.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1675647555093521"><a name="p1675647555093521"></a><a name="p1675647555093521"></a>Declares the driver interfaces for controlling the business process of input devices. </p>
</td>
</tr>
<tr id="row1959367983093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031155770093521"><a name="p1031155770093521"></a><a name="p1031155770093521"></a><a href="input_manager-h.md">input_manager.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196941925093521"><a name="p1196941925093521"></a><a name="p1196941925093521"></a>Declares the driver interfaces for managing input devices. </p>
</td>
</tr>
<tr id="row999861989093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875002160093521"><a name="p1875002160093521"></a><a name="p1875002160093521"></a><a href="input_reporter-h.md">input_reporter.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938518955093521"><a name="p938518955093521"></a><a name="p938518955093521"></a>Declares the driver interfaces for reporting data of input devices. </p>
</td>
</tr>
<tr id="row1107981454093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p258775427093521"><a name="p258775427093521"></a><a name="p258775427093521"></a><a href="input_type-h.md">input_type.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511552637093521"><a name="p1511552637093521"></a><a name="p1511552637093521"></a>Declares types of input devices as well as the structure and enumeration types used by driver interfaces. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table408223832093521"></a>
<table><thead align="left"><tr id="row1928864115093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p230222347093521"><a name="p230222347093521"></a><a name="p230222347093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1400954065093521"><a name="p1400954065093521"></a><a name="p1400954065093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row686685272093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1880181295093521"><a name="p1880181295093521"></a><a name="p1880181295093521"></a><a href="inputcontroller.md">InputController</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1115372927093521"><a name="p1115372927093521"></a><a name="p1115372927093521"></a>Provides interfaces for controlling the business process of input devices. </p>
</td>
</tr>
<tr id="row1155173298093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1843511868093521"><a name="p1843511868093521"></a><a name="p1843511868093521"></a><a href="inputmanager.md">InputManager</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1107714449093521"><a name="p1107714449093521"></a><a name="p1107714449093521"></a>Provides interfaces for managing input devices. </p>
</td>
</tr>
<tr id="row1850430516093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328519994093521"><a name="p328519994093521"></a><a name="p328519994093521"></a><a href="iinputinterface.md">IInputInterface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1190257110093521"><a name="p1190257110093521"></a><a name="p1190257110093521"></a>Defines interfaces for providing driver capabilities of input devices. </p>
</td>
</tr>
<tr id="row37816377093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997420388093521"><a name="p1997420388093521"></a><a name="p1997420388093521"></a><a href="inputreporter.md">InputReporter</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029423535093521"><a name="p1029423535093521"></a><a name="p1029423535093521"></a>Provides interfaces for reporting event data of input devices. </p>
</td>
</tr>
<tr id="row1640058573093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2059472768093521"><a name="p2059472768093521"></a><a name="p2059472768093521"></a><a href="inputextracmd.md">InputExtraCmd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2142392607093521"><a name="p2142392607093521"></a><a name="p2142392607093521"></a>Defines the extra commands. </p>
</td>
</tr>
<tr id="row1891005807093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146405421093521"><a name="p2146405421093521"></a><a name="p2146405421093521"></a><a href="inputeventdata.md">InputEventData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p529292841093521"><a name="p529292841093521"></a><a name="p529292841093521"></a>Describes the input event data. </p>
</td>
</tr>
<tr id="row745524620093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1153444177093521"><a name="p1153444177093521"></a><a name="p1153444177093521"></a><a href="inputreporteventcb.md">InputReportEventCb</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p31752164093521"><a name="p31752164093521"></a><a name="p31752164093521"></a>Describes the input event callback registered by the input service. </p>
</td>
</tr>
<tr id="row1589016503093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658759939093521"><a name="p1658759939093521"></a><a name="p1658759939093521"></a><a href="deviceinfo.md">DeviceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175077999093521"><a name="p175077999093521"></a><a name="p175077999093521"></a>Describes basic device information of the input device. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1175678542093521"></a>
<table><thead align="left"><tr id="row513912053093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1438599650093521"><a name="p1438599650093521"></a><a name="p1438599650093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p675051281093521"><a name="p675051281093521"></a><a name="p675051281093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row985704535093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755858894093521"><a name="p1755858894093521"></a><a name="p1755858894093521"></a><a href="input.md#ga85d58a5185669daa4995e332b63eba7a">RetStatus</a> {   <a href="input.md#gga85d58a5185669daa4995e332b63eba7aa4b6c3821e689826c4323c4eb759b4d3a">INPUT_SUCCESS</a>, <a href="input.md#gga85d58a5185669daa4995e332b63eba7aa2b90cc2935e5f41dfe3c2deb64bf5b7d">INPUT_EINVAL</a>, <a href="input.md#gga85d58a5185669daa4995e332b63eba7aa53d87c9b8af7f40db9749009897f51c6">INPUT_EFAULT</a>, <a href="input.md#gga85d58a5185669daa4995e332b63eba7aafdde805f755166272b7ad0032519061d">INPUT_ENOMEM</a>,   <a href="input.md#gga85d58a5185669daa4995e332b63eba7aa24ea43cc8f7bdc8845ce70377d5a03a3">INPUT_ETIMEOUT</a>, <a href="input.md#gga85d58a5185669daa4995e332b63eba7aa3b5144f6e7cfd213e63a9220e60a681f">INPUT_EUNSUPPORT</a>, <a href="input.md#gga85d58a5185669daa4995e332b63eba7aa9ce09ddb5727168672050bb75da9460c">INPUT_EUNKNOWN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p574307570093521"><a name="p574307570093521"></a><a name="p574307570093521"></a>Enumerates return values. </p>
</td>
</tr>
<tr id="row603616157093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524069505093521"><a name="p524069505093521"></a><a name="p524069505093521"></a><a href="input.md#gaa8225ba155dfa1ef2c4119c832bc4dd3">InputDevType</a> {   <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a621678554aac2b37ac244b80fc33da0d">INDEV_TYPE_TOUCH</a>, <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a4c4c8407342021cc06a95aa13ebeaca1">INDEV_TYPE_KEY</a>, <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a3a4137efe666a3aaccf267d597879fdc">INDEV_TYPE_KEYBOARD</a>, <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3abe68740c1d125d3d474fdadc7d31d11c">INDEV_TYPE_MOUSE</a>,   <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a2815a25dde3e56e1f8eb57f20049e8c0">INDEV_TYPE_BUTTON</a>, <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a4ef2ab6bc355e2321664709716d1d04f">INDEV_TYPE_CROWN</a>, <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a8cd6b27ac631b9d3fa89a17ddca37291">INDEV_TYPE_ENCODER</a>, <a href="input.md#ggaa8225ba155dfa1ef2c4119c832bc4dd3a4097247eba52062f47a1aa99414033de">INDEV_TYPE_UNKNOWN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1189509690093521"><a name="p1189509690093521"></a><a name="p1189509690093521"></a>Enumerates input device types. </p>
</td>
</tr>
<tr id="row1311707740093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1904266837093521"><a name="p1904266837093521"></a><a name="p1904266837093521"></a><a href="input.md#ga65e6bb4d942c22dba9975253b0a1d73f">PowerStatus</a> { <a href="input.md#gga65e6bb4d942c22dba9975253b0a1d73fa5edb1acdc509659046de9cb61bd9508a">INPUT_RESUME</a>, <a href="input.md#gga65e6bb4d942c22dba9975253b0a1d73fa2a6aab1b3d50dae2b6ba43779e185ea5">INPUT_SUSPEND</a>, <a href="input.md#gga65e6bb4d942c22dba9975253b0a1d73fa8895c64802d558830d46bcd921830e9d">INPUT_LOW_POWER</a>, <a href="input.md#gga65e6bb4d942c22dba9975253b0a1d73fa728020b31c626f749d426cbe8f0f92fe">INPUT_POWER_STATUS_UNKNOWN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1493329394093521"><a name="p1493329394093521"></a><a name="p1493329394093521"></a>Enumerates power statuses. </p>
</td>
</tr>
<tr id="row123927109093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p81059806093521"><a name="p81059806093521"></a><a name="p81059806093521"></a><a href="input.md#gae96e484cfd64ea37b5b7782f57f38a21">CapacitanceTest</a> {   <a href="input.md#ggae96e484cfd64ea37b5b7782f57f38a21aedd31f50c79a36cc8e084d69a3fc695b">BASE_TEST</a>, <a href="input.md#ggae96e484cfd64ea37b5b7782f57f38a21abfe92c879dc84b5b071899a7ec5cc41d">FULL_TEST</a>, <a href="input.md#ggae96e484cfd64ea37b5b7782f57f38a21a93335d88212604ade3b0bfe7e619916f">MMI_TEST</a>, <a href="input.md#ggae96e484cfd64ea37b5b7782f57f38a21a31afc25da895db4eaa2af6cec1d6b37c">RUNNING_TEST</a>,   <a href="input.md#ggae96e484cfd64ea37b5b7782f57f38a21a9d739cecefd291b39152e3815445aa20">TEST_TYPE_UNKNOWN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1796058856093521"><a name="p1796058856093521"></a><a name="p1796058856093521"></a>Enumerates types of capacitance tests. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table970672070093521"></a>
<table><thead align="left"><tr id="row770818903093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p737432863093521"><a name="p737432863093521"></a><a name="p737432863093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p138780162093521"><a name="p138780162093521"></a><a name="p138780162093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1718150285093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1075744901093521"><a name="p1075744901093521"></a><a name="p1075744901093521"></a><a href="input.md#ga3ca3e6b9bb859ba407b00a2175309cd3">GetInputInterface</a> (<a href="iinputinterface.md">IInputInterface</a> **interface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985019241093521"><a name="p1985019241093521"></a><a name="p1985019241093521"></a>int </p>
<p id="p1249586838093521"><a name="p1249586838093521"></a><a name="p1249586838093521"></a>Gets all interfaces for performing operations on input devices. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section104384331093521"></a>

## **Enumeration Type Documentation**<a name="section2012509089093521"></a>

## CapacitanceTest<a name="gae96e484cfd64ea37b5b7782f57f38a21"></a>

```
enum [CapacitanceTest](input.md#gae96e484cfd64ea37b5b7782f57f38a21)
```

 **Description:**

Enumerates types of capacitance tests. 

<a name="table581382910093521"></a>
<table><thead align="left"><tr id="row570201330093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1259381386093521"><a name="p1259381386093521"></a><a name="p1259381386093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p692107487093521"><a name="p692107487093521"></a><a name="p692107487093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1347408957093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae96e484cfd64ea37b5b7782f57f38a21aedd31f50c79a36cc8e084d69a3fc695b"><a name="ggae96e484cfd64ea37b5b7782f57f38a21aedd31f50c79a36cc8e084d69a3fc695b"></a><a name="ggae96e484cfd64ea37b5b7782f57f38a21aedd31f50c79a36cc8e084d69a3fc695b"></a></strong>BASE_TEST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1234082599093521"><a name="p1234082599093521"></a><a name="p1234082599093521"></a>Basic capacitance test </p>
 </td>
</tr>
<tr id="row531177954093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae96e484cfd64ea37b5b7782f57f38a21abfe92c879dc84b5b071899a7ec5cc41d"><a name="ggae96e484cfd64ea37b5b7782f57f38a21abfe92c879dc84b5b071899a7ec5cc41d"></a><a name="ggae96e484cfd64ea37b5b7782f57f38a21abfe92c879dc84b5b071899a7ec5cc41d"></a></strong>FULL_TEST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1822899676093521"><a name="p1822899676093521"></a><a name="p1822899676093521"></a>Full capacitance self-test </p>
 </td>
</tr>
<tr id="row222539108093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae96e484cfd64ea37b5b7782f57f38a21a93335d88212604ade3b0bfe7e619916f"><a name="ggae96e484cfd64ea37b5b7782f57f38a21a93335d88212604ade3b0bfe7e619916f"></a><a name="ggae96e484cfd64ea37b5b7782f57f38a21a93335d88212604ade3b0bfe7e619916f"></a></strong>MMI_TEST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p438998241093521"><a name="p438998241093521"></a><a name="p438998241093521"></a>Man-Machine Interface (MMI) capacitance test </p>
 </td>
</tr>
<tr id="row499071916093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae96e484cfd64ea37b5b7782f57f38a21a31afc25da895db4eaa2af6cec1d6b37c"><a name="ggae96e484cfd64ea37b5b7782f57f38a21a31afc25da895db4eaa2af6cec1d6b37c"></a><a name="ggae96e484cfd64ea37b5b7782f57f38a21a31afc25da895db4eaa2af6cec1d6b37c"></a></strong>RUNNING_TEST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1297796444093521"><a name="p1297796444093521"></a><a name="p1297796444093521"></a>Running capacitance test </p>
 </td>
</tr>
<tr id="row176779973093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae96e484cfd64ea37b5b7782f57f38a21a9d739cecefd291b39152e3815445aa20"><a name="ggae96e484cfd64ea37b5b7782f57f38a21a9d739cecefd291b39152e3815445aa20"></a><a name="ggae96e484cfd64ea37b5b7782f57f38a21a9d739cecefd291b39152e3815445aa20"></a></strong>TEST_TYPE_UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005018539093521"><a name="p2005018539093521"></a><a name="p2005018539093521"></a>Unknown test type </p>
 </td>
</tr>
</tbody>
</table>

## InputDevType<a name="gaa8225ba155dfa1ef2c4119c832bc4dd3"></a>

```
enum [InputDevType](input.md#gaa8225ba155dfa1ef2c4119c832bc4dd3)
```

 **Description:**

Enumerates input device types. 

<a name="table1405825474093521"></a>
<table><thead align="left"><tr id="row307711537093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p312033278093521"><a name="p312033278093521"></a><a name="p312033278093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p370907807093521"><a name="p370907807093521"></a><a name="p370907807093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row303292884093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a621678554aac2b37ac244b80fc33da0d"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a621678554aac2b37ac244b80fc33da0d"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a621678554aac2b37ac244b80fc33da0d"></a></strong>INDEV_TYPE_TOUCH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420334005093521"><a name="p1420334005093521"></a><a name="p1420334005093521"></a>Touchscreen </p>
 </td>
</tr>
<tr id="row1119095263093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4c4c8407342021cc06a95aa13ebeaca1"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4c4c8407342021cc06a95aa13ebeaca1"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4c4c8407342021cc06a95aa13ebeaca1"></a></strong>INDEV_TYPE_KEY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1951833540093521"><a name="p1951833540093521"></a><a name="p1951833540093521"></a>Physical key </p>
 </td>
</tr>
<tr id="row1619561019093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a3a4137efe666a3aaccf267d597879fdc"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a3a4137efe666a3aaccf267d597879fdc"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a3a4137efe666a3aaccf267d597879fdc"></a></strong>INDEV_TYPE_KEYBOARD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487811131093521"><a name="p1487811131093521"></a><a name="p1487811131093521"></a>Keyboard </p>
 </td>
</tr>
<tr id="row1390590525093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3abe68740c1d125d3d474fdadc7d31d11c"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3abe68740c1d125d3d474fdadc7d31d11c"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3abe68740c1d125d3d474fdadc7d31d11c"></a></strong>INDEV_TYPE_MOUSE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779444054093521"><a name="p779444054093521"></a><a name="p779444054093521"></a>Mouse </p>
 </td>
</tr>
<tr id="row1235728584093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a2815a25dde3e56e1f8eb57f20049e8c0"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a2815a25dde3e56e1f8eb57f20049e8c0"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a2815a25dde3e56e1f8eb57f20049e8c0"></a></strong>INDEV_TYPE_BUTTON </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p160673463093521"><a name="p160673463093521"></a><a name="p160673463093521"></a>Virtual button </p>
 </td>
</tr>
<tr id="row222013037093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4ef2ab6bc355e2321664709716d1d04f"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4ef2ab6bc355e2321664709716d1d04f"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4ef2ab6bc355e2321664709716d1d04f"></a></strong>INDEV_TYPE_CROWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p736578015093521"><a name="p736578015093521"></a><a name="p736578015093521"></a>Watch crown </p>
 </td>
</tr>
<tr id="row1967333411093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a8cd6b27ac631b9d3fa89a17ddca37291"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a8cd6b27ac631b9d3fa89a17ddca37291"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a8cd6b27ac631b9d3fa89a17ddca37291"></a></strong>INDEV_TYPE_ENCODER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1137156216093521"><a name="p1137156216093521"></a><a name="p1137156216093521"></a>Customized type of a specific function or event </p>
 </td>
</tr>
<tr id="row2107773705093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4097247eba52062f47a1aa99414033de"><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4097247eba52062f47a1aa99414033de"></a><a name="ggaa8225ba155dfa1ef2c4119c832bc4dd3a4097247eba52062f47a1aa99414033de"></a></strong>INDEV_TYPE_UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1213954649093521"><a name="p1213954649093521"></a><a name="p1213954649093521"></a>Unknown input device type </p>
 </td>
</tr>
</tbody>
</table>

## PowerStatus<a name="ga65e6bb4d942c22dba9975253b0a1d73f"></a>

```
enum [PowerStatus](input.md#ga65e6bb4d942c22dba9975253b0a1d73f)
```

 **Description:**

Enumerates power statuses. 

<a name="table1663697266093521"></a>
<table><thead align="left"><tr id="row1178534901093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p475568361093521"><a name="p475568361093521"></a><a name="p475568361093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1095716803093521"><a name="p1095716803093521"></a><a name="p1095716803093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1405178815093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga65e6bb4d942c22dba9975253b0a1d73fa5edb1acdc509659046de9cb61bd9508a"><a name="gga65e6bb4d942c22dba9975253b0a1d73fa5edb1acdc509659046de9cb61bd9508a"></a><a name="gga65e6bb4d942c22dba9975253b0a1d73fa5edb1acdc509659046de9cb61bd9508a"></a></strong>INPUT_RESUME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129758942093521"><a name="p129758942093521"></a><a name="p129758942093521"></a>Resume status </p>
 </td>
</tr>
<tr id="row594660733093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga65e6bb4d942c22dba9975253b0a1d73fa2a6aab1b3d50dae2b6ba43779e185ea5"><a name="gga65e6bb4d942c22dba9975253b0a1d73fa2a6aab1b3d50dae2b6ba43779e185ea5"></a><a name="gga65e6bb4d942c22dba9975253b0a1d73fa2a6aab1b3d50dae2b6ba43779e185ea5"></a></strong>INPUT_SUSPEND </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p501855247093521"><a name="p501855247093521"></a><a name="p501855247093521"></a>Suspend status </p>
 </td>
</tr>
<tr id="row1430884329093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga65e6bb4d942c22dba9975253b0a1d73fa8895c64802d558830d46bcd921830e9d"><a name="gga65e6bb4d942c22dba9975253b0a1d73fa8895c64802d558830d46bcd921830e9d"></a><a name="gga65e6bb4d942c22dba9975253b0a1d73fa8895c64802d558830d46bcd921830e9d"></a></strong>INPUT_LOW_POWER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021550211093521"><a name="p2021550211093521"></a><a name="p2021550211093521"></a>Low-power status </p>
 </td>
</tr>
<tr id="row1606483390093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga65e6bb4d942c22dba9975253b0a1d73fa728020b31c626f749d426cbe8f0f92fe"><a name="gga65e6bb4d942c22dba9975253b0a1d73fa728020b31c626f749d426cbe8f0f92fe"></a><a name="gga65e6bb4d942c22dba9975253b0a1d73fa728020b31c626f749d426cbe8f0f92fe"></a></strong>INPUT_POWER_STATUS_UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67206200093521"><a name="p67206200093521"></a><a name="p67206200093521"></a>Unknown power status </p>
 </td>
</tr>
</tbody>
</table>

## RetStatus<a name="ga85d58a5185669daa4995e332b63eba7a"></a>

```
enum [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)
```

 **Description:**

Enumerates return values. 

<a name="table2039130554093521"></a>
<table><thead align="left"><tr id="row2065535124093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1884671552093521"><a name="p1884671552093521"></a><a name="p1884671552093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p841668617093521"><a name="p841668617093521"></a><a name="p841668617093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row238066575093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aa4b6c3821e689826c4323c4eb759b4d3a"><a name="gga85d58a5185669daa4995e332b63eba7aa4b6c3821e689826c4323c4eb759b4d3a"></a><a name="gga85d58a5185669daa4995e332b63eba7aa4b6c3821e689826c4323c4eb759b4d3a"></a></strong>INPUT_SUCCESS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p888997134093521"><a name="p888997134093521"></a><a name="p888997134093521"></a>Success </p>
 </td>
</tr>
<tr id="row617537058093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aa2b90cc2935e5f41dfe3c2deb64bf5b7d"><a name="gga85d58a5185669daa4995e332b63eba7aa2b90cc2935e5f41dfe3c2deb64bf5b7d"></a><a name="gga85d58a5185669daa4995e332b63eba7aa2b90cc2935e5f41dfe3c2deb64bf5b7d"></a></strong>INPUT_EINVAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p7677412093521"><a name="p7677412093521"></a><a name="p7677412093521"></a>Invalid value </p>
 </td>
</tr>
<tr id="row1227079089093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aa53d87c9b8af7f40db9749009897f51c6"><a name="gga85d58a5185669daa4995e332b63eba7aa53d87c9b8af7f40db9749009897f51c6"></a><a name="gga85d58a5185669daa4995e332b63eba7aa53d87c9b8af7f40db9749009897f51c6"></a></strong>INPUT_EFAULT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979310382093521"><a name="p979310382093521"></a><a name="p979310382093521"></a>Runtime error </p>
 </td>
</tr>
<tr id="row617761695093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aafdde805f755166272b7ad0032519061d"><a name="gga85d58a5185669daa4995e332b63eba7aafdde805f755166272b7ad0032519061d"></a><a name="gga85d58a5185669daa4995e332b63eba7aafdde805f755166272b7ad0032519061d"></a></strong>INPUT_ENOMEM </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p682938402093521"><a name="p682938402093521"></a><a name="p682938402093521"></a>Failed to apply for memory </p>
 </td>
</tr>
<tr id="row1043836327093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aa24ea43cc8f7bdc8845ce70377d5a03a3"><a name="gga85d58a5185669daa4995e332b63eba7aa24ea43cc8f7bdc8845ce70377d5a03a3"></a><a name="gga85d58a5185669daa4995e332b63eba7aa24ea43cc8f7bdc8845ce70377d5a03a3"></a></strong>INPUT_ETIMEOUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p660897164093521"><a name="p660897164093521"></a><a name="p660897164093521"></a>Execution timed out </p>
 </td>
</tr>
<tr id="row100106034093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aa3b5144f6e7cfd213e63a9220e60a681f"><a name="gga85d58a5185669daa4995e332b63eba7aa3b5144f6e7cfd213e63a9220e60a681f"></a><a name="gga85d58a5185669daa4995e332b63eba7aa3b5144f6e7cfd213e63a9220e60a681f"></a></strong>INPUT_EUNSUPPORT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p643344970093521"><a name="p643344970093521"></a><a name="p643344970093521"></a>The feature is not supported </p>
 </td>
</tr>
<tr id="row87971554093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga85d58a5185669daa4995e332b63eba7aa9ce09ddb5727168672050bb75da9460c"><a name="gga85d58a5185669daa4995e332b63eba7aa9ce09ddb5727168672050bb75da9460c"></a><a name="gga85d58a5185669daa4995e332b63eba7aa9ce09ddb5727168672050bb75da9460c"></a></strong>INPUT_EUNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p310027441093521"><a name="p310027441093521"></a><a name="p310027441093521"></a>Unknown error </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section165109931093521"></a>

## GetInputInterface\(\)<a name="ga3ca3e6b9bb859ba407b00a2175309cd3"></a>

```
int GetInputInterface ([IInputInterface](iinputinterface.md) ** interface)
```

 **Description:**

Gets all interfaces for performing operations on input devices. 

You can call this function after the input service is started.

**Parameters:**

<a name="table165763219093521"></a>
<table><thead align="left"><tr id="row1738463284093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1761280872093521"><a name="p1761280872093521"></a><a name="p1761280872093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2128166700093521"><a name="p2128166700093521"></a><a name="p2128166700093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row774489238093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">interface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the interface for performing operations on input devices. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [RetStatus](input.md#ga85d58a5185669daa4995e332b63eba7a)  otherwise. 



