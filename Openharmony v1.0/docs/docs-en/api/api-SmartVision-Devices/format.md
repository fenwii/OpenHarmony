# Format<a name="EN-US_TOPIC_0000001055358056"></a>

## **Overview**<a name="section1851676465093521"></a>

Defines format-related APIs. 

For example, you use this module to define custom data types and to initialize, create, destroy the muxer and demuxer, and set their parameters. Also, you can read demuxer data frames, select demuxer tracks, add muxer tracks, and write data frames into a container.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1361415037093521"></a>

## Files<a name="files"></a>

<a name="table1833293450093521"></a>
<table><thead align="left"><tr id="row638214969093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p247122714093521"><a name="p247122714093521"></a><a name="p247122714093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1667622116093521"><a name="p1667622116093521"></a><a name="p1667622116093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2077994214093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1959078295093521"><a name="p1959078295093521"></a><a name="p1959078295093521"></a><a href="format_interface-h.md">format_interface.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1603799306093521"><a name="p1603799306093521"></a><a name="p1603799306093521"></a>Declares format-related APIs. </p>
</td>
</tr>
<tr id="row676100656093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437007947093521"><a name="p1437007947093521"></a><a name="p1437007947093521"></a><a href="format_type-h.md">format_type.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p235441970093521"><a name="p235441970093521"></a><a name="p235441970093521"></a>Declares format-related structures and enumerations, including custom data types for file information, programs, information about audio and video subtitle tracks, source data types, output data types, split types, and data frames. </p>
</td>
</tr>
<tr id="row1983780095093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1549267639093521"><a name="p1549267639093521"></a><a name="p1549267639093521"></a><a href="parameter_item-h.md">parameter_item.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p90548250093521"><a name="p90548250093521"></a><a name="p90548250093521"></a>Defines format-related structures and enumerations used to configure and obtain dynamic parameters. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1397055722093521"></a>
<table><thead align="left"><tr id="row937732531093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p853967639093521"><a name="p853967639093521"></a><a name="p853967639093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1496503714093521"><a name="p1496503714093521"></a><a name="p1496503714093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row287841140093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1365283850093521"><a name="p1365283850093521"></a><a name="p1365283850093521"></a><a href="formatbuffersetting.md">FormatBufferSetting</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91525837093521"><a name="p91525837093521"></a><a name="p91525837093521"></a>Defines the buffer configuration. </p>
</td>
</tr>
<tr id="row1187937624093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1003490207093521"><a name="p1003490207093521"></a><a name="p1003490207093521"></a><a href="formatframe.md">FormatFrame</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2040661257093521"><a name="p2040661257093521"></a><a name="p2040661257093521"></a>Defines the data frame, which is used for data transferring. </p>
</td>
</tr>
<tr id="row1085316598093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1086196194093521"><a name="p1086196194093521"></a><a name="p1086196194093521"></a><a href="audiotrackinfo.md">AudioTrackInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p520928596093521"><a name="p520928596093521"></a><a name="p520928596093521"></a>Defines audio track information. </p>
</td>
</tr>
<tr id="row3290813093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1067739875093521"><a name="p1067739875093521"></a><a name="p1067739875093521"></a><a href="videotrackinfo.md">VideoTrackInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p200921807093521"><a name="p200921807093521"></a><a name="p200921807093521"></a>Defines video track information. </p>
</td>
</tr>
<tr id="row671099031093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217712984093521"><a name="p1217712984093521"></a><a name="p1217712984093521"></a><a href="subimageinfo.md">SubImageInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p227222736093521"><a name="p227222736093521"></a><a name="p227222736093521"></a>Defines image information. </p>
</td>
</tr>
<tr id="row1245074283093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p615586867093521"><a name="p615586867093521"></a><a name="p615586867093521"></a><a href="imagetrackinfo.md">ImageTrackInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813720634093521"><a name="p813720634093521"></a><a name="p813720634093521"></a>Defines image stream information. </p>
</td>
</tr>
<tr id="row1709699868093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795360768093521"><a name="p795360768093521"></a><a name="p795360768093521"></a><a href="subtitletrackinfo.md">SubtitleTrackInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987303772093521"><a name="p987303772093521"></a><a name="p987303772093521"></a>Defines subtitle stream information. </p>
</td>
</tr>
<tr id="row1269758060093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275159568093521"><a name="p275159568093521"></a><a name="p275159568093521"></a><a href="trackinfo.md">TrackInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780657234093521"><a name="p780657234093521"></a><a name="p780657234093521"></a>Defines track information. </p>
</td>
</tr>
<tr id="row488653628093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753517072093521"><a name="p753517072093521"></a><a name="p753517072093521"></a><a href="programinfo.md">ProgramInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511229383093521"><a name="p1511229383093521"></a><a name="p1511229383093521"></a>Defines program information. </p>
</td>
</tr>
<tr id="row1908008872093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1316959594093521"><a name="p1316959594093521"></a><a name="p1316959594093521"></a><a href="fileinfo.md">FileInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841659599093521"><a name="p1841659599093521"></a><a name="p1841659599093521"></a>Defines movie file information. </p>
</td>
</tr>
<tr id="row46222188093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p685413704093521"><a name="p685413704093521"></a><a name="p685413704093521"></a><a href="bufferstream.md">BufferStream</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1319880722093521"><a name="p1319880722093521"></a><a name="p1319880722093521"></a>Defines the function for reading stream data. </p>
</td>
</tr>
<tr id="row1401394108093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242360624093521"><a name="p1242360624093521"></a><a name="p1242360624093521"></a><a href="formatsource.md">FormatSource</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731030773093521"><a name="p731030773093521"></a><a name="p731030773093521"></a>Defines the demuxer data source. </p>
</td>
</tr>
<tr id="row1877214793093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50597532093521"><a name="p50597532093521"></a><a name="p50597532093521"></a><a href="formatoutputconfig.md">FormatOutputConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774332318093521"><a name="p1774332318093521"></a><a name="p1774332318093521"></a>Defines the muxer output configuration. </p>
</td>
</tr>
<tr id="row1784534222093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434988957093521"><a name="p1434988957093521"></a><a name="p1434988957093521"></a><a href="videotracksourceinfo.md">VideoTrackSourceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1658927860093521"><a name="p1658927860093521"></a><a name="p1658927860093521"></a>Defines information about the muxer video source. </p>
</td>
</tr>
<tr id="row473380924093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237611149093521"><a name="p237611149093521"></a><a name="p237611149093521"></a><a href="audiotracksourceinfo.md">AudioTrackSourceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1081000509093521"><a name="p1081000509093521"></a><a name="p1081000509093521"></a>Defines information about the muxer audio source. </p>
</td>
</tr>
<tr id="row2081778612093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1256466691093521"><a name="p1256466691093521"></a><a name="p1256466691093521"></a><a href="datatracksourceinfo.md">DataTrackSourceInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973985708093521"><a name="p1973985708093521"></a><a name="p1973985708093521"></a>Defines information about the muxer data source. </p>
</td>
</tr>
<tr id="row1582909074093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155065589093521"><a name="p155065589093521"></a><a name="p155065589093521"></a><a href="tracksource.md">TrackSource</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p742931391093521"><a name="p742931391093521"></a><a name="p742931391093521"></a>Defines information about the muxer source. </p>
</td>
</tr>
<tr id="row1964049761093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p259301225093521"><a name="p259301225093521"></a><a name="p259301225093521"></a><a href="formatcallback.md">FormatCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798342768093521"><a name="p1798342768093521"></a><a name="p1798342768093521"></a>Defines listener callbacks for the format. </p>
</td>
</tr>
<tr id="row791804825093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647591619093521"><a name="p647591619093521"></a><a name="p647591619093521"></a><a href="parameteritem.md">ParameterItem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823382949093521"><a name="p823382949093521"></a><a name="p823382949093521"></a>Defines a structure for configuring and obtaining dynamic parameters. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1916215897093521"></a>
<table><thead align="left"><tr id="row1032651165093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1356402461093521"><a name="p1356402461093521"></a><a name="p1356402461093521"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p835093719093521"><a name="p835093719093521"></a><a name="p835093719093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1598104646093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221039464093521"><a name="p221039464093521"></a><a name="p221039464093521"></a><a href="format.md#gac2d2d077edb8e9bb9f85ab6350015c5b">FORMAT_MAX_LANGUAGE_NUM</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row1237423426093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p800664238093521"><a name="p800664238093521"></a><a name="p800664238093521"></a><a href="format.md#gaa70508bb1089c99f9aa3d59fcbdfa8eb">FORMAT_LANGUAGE_LEN</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row1727782591093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1557502555093521"><a name="p1557502555093521"></a><a name="p1557502555093521"></a><a href="format.md#gadb635fac84a9d62e99c69e75d4de85c3">FORMAT_TITLE_LEN</a>   64</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row449231297093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1822443341093521"><a name="p1822443341093521"></a><a name="p1822443341093521"></a><a href="format.md#ga62037bb16334896e1bb6d35a71618881">FORMAT_INVALID_TRACK_ID</a>   -1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row113730725093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1261768047093521"><a name="p1261768047093521"></a><a name="p1261768047093521"></a><a href="format.md#gab4007b017f1edad143959af034e32bf7">FORMAT_INVALID_PROGRAM_ID</a>   -1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row1283658340093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1067253908093521"><a name="p1067253908093521"></a><a name="p1067253908093521"></a><a href="format.md#ga1ac54dd3b9b49c1800b5f502a87650be">URL_LEN</a>   4096</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1407396971093521"></a>
<table><thead align="left"><tr id="row275828192093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1904519834093521"><a name="p1904519834093521"></a><a name="p1904519834093521"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p758921936093521"><a name="p758921936093521"></a><a name="p758921936093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row556079247093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1344956635093521"><a name="p1344956635093521"></a><a name="p1344956635093521"></a><a href="format.md#gab928f39c359734527bda3fd160f89331">CALLBACK_HANDLE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1421453848093521"><a name="p1421453848093521"></a><a name="p1421453848093521"></a>typedef void * </p>
<p id="p423246327093521"><a name="p423246327093521"></a><a name="p423246327093521"></a>Indicates the pointer to the callback handle for listening the muxer. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table123601445093521"></a>
<table><thead align="left"><tr id="row1456716602093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p217864040093521"><a name="p217864040093521"></a><a name="p217864040093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1788230645093521"><a name="p1788230645093521"></a><a name="p1788230645093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1146092110093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1621857316093521"><a name="p1621857316093521"></a><a name="p1621857316093521"></a><a href="format.md#gad495a9f61af7fff07d7e97979d1ab854">FrameType</a> {   <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a54c4b682d718fd6c8e5f224ee2fad841">FRAME_TYPE_NONE</a>, <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a709dd5ff367a8ff7669fda5386291796">FRAME_TYPE_AUDIO</a>, <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a7670f4378c84a94fb65f6c30c4b1a096">FRAME_TYPE_VIDEO</a>, <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a90bb6db5c310d60ccd4a6ec1b172e9e5">FRAME_TYPE_IMAGE</a>,   <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a3b43393b8fff68297e4daf0c32193704">FRAME_TYPE_SUB</a>, <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a75641aebcb420f0f661dc8acefdc9b30">FRAME_TYPE_DATA</a>, <a href="format.md#ggad495a9f61af7fff07d7e97979d1ab854a7afc81a56325cb4a7356663ccd270931">FRAME_TYPE_BUT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281712905093521"><a name="p1281712905093521"></a><a name="p1281712905093521"></a>Enumerates data frame types. </p>
</td>
</tr>
<tr id="row709108317093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1050630264093521"><a name="p1050630264093521"></a><a name="p1050630264093521"></a><a href="format.md#ga14aa9d18a71eff4a0b70f748f0377c94">FormatSeekMode</a> { <a href="format.md#gga14aa9d18a71eff4a0b70f748f0377c94a59c30f44f3b65ff91ee18441315dbbcc">FORMAT_SEEK_MODE_FORWARD_KEY</a>, <a href="format.md#gga14aa9d18a71eff4a0b70f748f0377c94a00f9ebeb7f829675bde8cad3832efcdd">FORMAT_SEEK_MODE_BACKWARD_KEY</a>, <a href="format.md#gga14aa9d18a71eff4a0b70f748f0377c94a605cab737a9cfc0a06f911efa117646d">FORMAT_SEEK_MODE_CLOSEST_KEY</a>, <a href="format.md#gga14aa9d18a71eff4a0b70f748f0377c94a1a87eaf0f3e52132aba4563232a6f248">SEEK_MODE_BUT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105675189093521"><a name="p1105675189093521"></a><a name="p1105675189093521"></a>Enumerates seek modes. </p>
</td>
</tr>
<tr id="row368991771093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p474729880093521"><a name="p474729880093521"></a><a name="p474729880093521"></a><a href="format.md#gaf7ed135f15d4b218d41705bac0122ba7">CodecFormat</a> {   <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7aa0c89a6d185559b38e63265976dde7f4">CODEC_H264</a> = 0, <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7a4adc0c5e441be1b1a642f481e3111cae">CODEC_H265</a>, <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7ab6432cb3fb17152277af1f486e182612">CODEC_JPEG</a>, <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7a8a0888876671d503c2c5e15059461c06">CODEC_AAC</a>,   <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7a44fd5227148450a7870e202d50110509">CODEC_G711A</a>, <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7a3ac447dc6b8707c70f6fc6d4e0c552d5">CODEC_G711U</a>, <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7ae3014fa1161193bc92227ea0895e1dfb">CODEC_PCM</a>, <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7a2a0119a66bcbe797c1bac3057a802c9a">CODEC_MP3</a>,   <a href="format.md#ggaf7ed135f15d4b218d41705bac0122ba7a0bccf3a2f309d8c485283d386322f07b">CODEC_BUT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p745669234093521"><a name="p745669234093521"></a><a name="p745669234093521"></a>Enumerates audio, video, and image encoding formats. </p>
</td>
</tr>
<tr id="row1362146568093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p724930020093521"><a name="p724930020093521"></a><a name="p724930020093521"></a><a href="format.md#gadf0700999998f587f0017c4d02977b22">AudioSampleFmt</a> {   <a href="format.md#ggadf0700999998f587f0017c4d02977b22a650b7f83085e55b6e728fd3ec5beec50">AUDIO_SAMPLE_FMT_S8</a> = 0, <a href="format.md#ggadf0700999998f587f0017c4d02977b22a40335eaa7ca378540941909ed02b51a0">AUDIO_SAMPLE_FMT_S16</a>, <a href="format.md#ggadf0700999998f587f0017c4d02977b22af55ab2a69453af86f0c1602d3645f5f9">AUDIO_SAMPLE_FMT_S24</a>, <a href="format.md#ggadf0700999998f587f0017c4d02977b22ab98feafb8396c0190a4fb719a15ab7c5">AUDIO_SAMPLE_FMT_S32</a>,   <a href="format.md#ggadf0700999998f587f0017c4d02977b22ac2fb27a42b3f79e51dd71ce05b42f9db">AUDIO_SAMPLE_FMT_FLOAT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601216951093521"><a name="p1601216951093521"></a><a name="p1601216951093521"></a>Enumerates audio sampling formats. </p>
</td>
</tr>
<tr id="row337470855093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p53988292093521"><a name="p53988292093521"></a><a name="p53988292093521"></a><a href="format.md#ga43b7f046e365a89697272d850b0517b7">SubtitleFrameType</a> { <a href="format.md#gga43b7f046e365a89697272d850b0517b7a6bc8b3dca40c75f6dd22feea62cbdac7">HI_SVR_SUBTITLE_BITMAP</a> = 0x0, <a href="format.md#gga43b7f046e365a89697272d850b0517b7a3ee7a0476e395ec2689f754e58d512a0">HI_SVR_SUBTITLE_TEXT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1195175135093521"><a name="p1195175135093521"></a><a name="p1195175135093521"></a>Enumerates subtitle frame types. </p>
</td>
</tr>
<tr id="row1114182104093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p16034525093521"><a name="p16034525093521"></a><a name="p16034525093521"></a><a href="format.md#gadac45ce4731516c262292c15433439b3">SubtitleFormat</a> {   <a href="format.md#ggadac45ce4731516c262292c15433439b3abe03cb7d3bb87dcfc197b9e9db7a66f6">FORMAT_SUB_ASS</a> = 0x0, <a href="format.md#ggadac45ce4731516c262292c15433439b3a569e5e22b1c3bf5b9f4cc3f596cfc6db">FORMAT_SUB_LRC</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3a26f41cfe561866b43a9757b5902c7609">FORMAT_SUB_SRT</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3ac6665b95ccb70e7a7d87dda6370821ff">FORMAT_SUB_SMI</a>,   <a href="format.md#ggadac45ce4731516c262292c15433439b3a07a0a164bb0081359639cfdef57aa2c2">FORMAT_SUB_SUB</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3a5ad9a3ec464416e8395e3e0f6595c253">FORMAT_SUB_TXT</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3a9f573cd39fab8fc143480bf1eb973574">FORMAT_SUB_HDMV_PGS</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3a641b27aab74dbbcd88d7d8612b60caad">FORMAT_SUB_DVB_SUB</a>,   <a href="format.md#ggadac45ce4731516c262292c15433439b3a91ab0e8c1931fc3b4f2350a8e18672a6">FORMAT_SUB_DVD_SUB</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3a0750bc81000513246d5785d0ef2c0099">FORMAT_SUB_TTML</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3ad9de45a6ae50e5443e2d0418b1cdde61">FORMAT_SUB_WEBVTT</a>, <a href="format.md#ggadac45ce4731516c262292c15433439b3a52ed4b60bc3d33d43753555e1edf50d7">FORMAT_SUB_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167567041093521"><a name="p1167567041093521"></a><a name="p1167567041093521"></a>Enumerates subtitle file formats. </p>
</td>
</tr>
<tr id="row267589919093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p59408838093521"><a name="p59408838093521"></a><a name="p59408838093521"></a><a href="format.md#gad80740dd555f7d3688d2c4d9f44d3b04">TrackType</a> {   <a href="format.md#ggad80740dd555f7d3688d2c4d9f44d3b04aae00a139d1f3bbfef9dbda6803497b62">TRACK_TYPE_VIDEO</a>, <a href="format.md#ggad80740dd555f7d3688d2c4d9f44d3b04aab84be45f332c1bd8ab31d9404c6d944">TRACK_TYPE_AUDIO</a>, <a href="format.md#ggad80740dd555f7d3688d2c4d9f44d3b04a3c834b6afb84a38aa490253a3abc5f66">TRACK_TYPE_IMAGE</a>, <a href="format.md#ggad80740dd555f7d3688d2c4d9f44d3b04aff6cb64c75689ea5b11063e0984956f4">TRACK_TYPE_SUB</a>,   <a href="format.md#ggad80740dd555f7d3688d2c4d9f44d3b04abe0c58f8c0a492959631b8f41dbe2af7">TRACK_TYPE_DATA</a>, <a href="format.md#ggad80740dd555f7d3688d2c4d9f44d3b04ad3a1729659a9a6453a2d2bda67cb2c22">TRACK_TYPE_BUT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p849035113093521"><a name="p849035113093521"></a><a name="p849035113093521"></a>Enumerates track types. </p>
</td>
</tr>
<tr id="row435375912093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p333813026093521"><a name="p333813026093521"></a><a name="p333813026093521"></a><a href="format.md#gacff079fdf8427c743f9197ea5be33a7f">DataFlags</a> {   <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7faf5d58e6ec118e0660b53c7a7df2fdc8b">DATA_FLAG_NONE</a> = 0, <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7fad000cf60ee0b16f1ea7fedbcdb1a9fa0">DATA_FLAG_SYNCFRAME</a> = 1, <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7fa9200ae4b5fc3c72f2e70c9a49c2ebbb0">DATA_FLAG_CODECCONFIG</a> = 2, <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7fabaa169afc64ef32b743217c8194fd8b9">DATA_FLAG_EOS</a> = 4,   <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7fa26019220bb1298308f5c3dcd8a071f63">DATA_FLAG_PARTIAL_FRAME</a> = 8, <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7fa5fd5b55061c6e94a8a12f9cf9d2009a7">DATA_FLAG_ENDOFFRAME</a> = 16, <a href="format.md#ggacff079fdf8427c743f9197ea5be33a7faeb92d052f544e6cde910fb669790a804">DATA_FLAG_MUXER_DATA</a> = 32 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p808038792093521"><a name="p808038792093521"></a><a name="p808038792093521"></a>Enumerates flags of raw stream data. </p>
</td>
</tr>
<tr id="row1775607264093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p493529403093521"><a name="p493529403093521"></a><a name="p493529403093521"></a><a href="format.md#ga3ae727773c367ac1041d72ac770a0ab1">SourceType</a> { <a href="format.md#gga3ae727773c367ac1041d72ac770a0ab1a126568132b92d49365d94c4aa00cdde4">SOURCE_TYPE_FD</a> = 0, <a href="format.md#gga3ae727773c367ac1041d72ac770a0ab1a70d32ea5aeaa325764508722ba31403c">SOURCE_TYPE_URI</a>, <a href="format.md#gga3ae727773c367ac1041d72ac770a0ab1a7f632a791d8f6dfbe5940b5648d29e6c">SOURCE_TYPE_STREAM</a>, <a href="format.md#gga3ae727773c367ac1041d72ac770a0ab1ad41c2f0bdca46364d6cd86fc5d4710d3">SOURCE_TYPE_BUT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1381354528093521"><a name="p1381354528093521"></a><a name="p1381354528093521"></a>Enumerates types of the demuxer data source. </p>
</td>
</tr>
<tr id="row1958608708093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p749118387093521"><a name="p749118387093521"></a><a name="p749118387093521"></a><a href="format.md#gaeb712c6c6c0a8af0dfd79f451ecb9277">OutputFormat</a> {   <a href="format.md#ggaeb712c6c6c0a8af0dfd79f451ecb9277a5a01488de2f310872db03b7a6ad26423">OUTPUT_FORMAT_MPEG_4</a> = 0, <a href="format.md#ggaeb712c6c6c0a8af0dfd79f451ecb9277a9eaec301329c61d07d2fe19ca473abc2">OUTPUT_FORMAT_TS</a> = 1, <a href="format.md#ggaeb712c6c6c0a8af0dfd79f451ecb9277a3a0cc99ed9dcc44245dd91591b7accac">OUTPUT_FORMAT_THREE_GPP</a> = 2, <a href="format.md#ggaeb712c6c6c0a8af0dfd79f451ecb9277a68afc7e60f3cdacd5e1fb9a5dcf0ebdb">OUTPUT_FORMAT_HEIF</a> = 3,   <a href="format.md#ggaeb712c6c6c0a8af0dfd79f451ecb9277abb34ec8353ace07dbfd698c05343800d">OUTPUT_FORMAT_OGG</a> = 4, <a href="format.md#ggaeb712c6c6c0a8af0dfd79f451ecb9277a00eb675fb0d802a5143f4f718ea854e3">OUTPUT_FORMAT_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1162833644093521"><a name="p1162833644093521"></a><a name="p1162833644093521"></a>Enumerates output file formats. </p>
</td>
</tr>
<tr id="row116504192093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p408854802093521"><a name="p408854802093521"></a><a name="p408854802093521"></a><a href="format.md#ga6f00342925d3d5e586c76f8695985cad">FormatInfoType</a> {   <a href="format.md#gga6f00342925d3d5e586c76f8695985cadaf6214216fd62faa4fc5e20d0d0ba60bf">MUXER_INFO_MAX_DURATION_APPROACHING</a> = 0, <a href="format.md#gga6f00342925d3d5e586c76f8695985cadafc74f41e73f13a29a83b3a13ea6e66e1">MUXER_INFO_MAX_FILESIZE_APPROACHING</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cada9722ce52063f6247d5fb17470eb9559e">MUXER_INFO_MAX_DURATION_REACHED</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cada71704a053cf3e30c7bf91522b27da8c2">MUXER_INFO_MAX_FILESIZE_REACHED</a>,   <a href="format.md#gga6f00342925d3d5e586c76f8695985cadae63cbc02cf7dc61073b739c08cc58ff4">MUXER_INFO_NEXT_OUTPUT_FILE_STARTED</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cada3cf56a06f5990ab657d61bd7e57c1783">MUXER_INFO_FILE_SPLIT_FINISHED</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cada5d3901c368e7a4f719134c98c4fa8313">MUXER_INFO_FILE_START_TIME_MS</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cadaeb00ffb6342b7ede6b5efe81fa842374">DEMUXER_INFO_PREPARED</a> = 10000,   <a href="format.md#gga6f00342925d3d5e586c76f8695985cada929a71c6b58dfcd974e960b99139a758">DEMUXER_INFO_SEEK_COMPLETE</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cada2c4b1c086d55b4d5bf3fedbbf115cf63">DEMUXER_INFO_NETWORK_DISCONNECTED</a>, <a href="format.md#gga6f00342925d3d5e586c76f8695985cadac157e535a1828f3b87c9cc3e6fd8773b">DEMUXER_INFO_NETWORK_RECONNECTED</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782228268093521"><a name="p782228268093521"></a><a name="p782228268093521"></a>Enumerates types of callback information. </p>
</td>
</tr>
<tr id="row1232127687093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1763299312093521"><a name="p1763299312093521"></a><a name="p1763299312093521"></a><a href="format.md#ga31e7fcf42722fa15e4e5489c2fef9092">FormatErrorType</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1180091108093521"><a name="p1180091108093521"></a><a name="p1180091108093521"></a>Enumerates callback error types. </p>
</td>
</tr>
<tr id="row725958705093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p572939498093521"><a name="p572939498093521"></a><a name="p572939498093521"></a><a href="format.md#ga4e0517338e6c4a31a2addafc06d4f3a3">OutputType</a> { <a href="format.md#gga4e0517338e6c4a31a2addafc06d4f3a3a14ea73c5ea45e0f9b6976d24ac1119e9">OUTPUT_TYPE_FD</a> = 0, <a href="format.md#gga4e0517338e6c4a31a2addafc06d4f3a3a67f14fbe9f23ae5acd2ffc7b00fd6740">OUTPUT_TYPE_URI</a>, <a href="format.md#gga4e0517338e6c4a31a2addafc06d4f3a3a169d19953026c9c3fed4e4433624ca7c">OUTPUT_TYPE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1161668273093521"><a name="p1161668273093521"></a><a name="p1161668273093521"></a>Enumerates muxer output types. </p>
</td>
</tr>
<tr id="row1319827254093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1148224368093521"><a name="p1148224368093521"></a><a name="p1148224368093521"></a><a href="format.md#ga10d9833450f29129d249c41d9acb4bc4">ManualSplitType</a> { <a href="format.md#gga10d9833450f29129d249c41d9acb4bc4ad283396b08ef486b6615977c881a8724">MANUAL_SPLIT_POST</a> = 0, <a href="format.md#gga10d9833450f29129d249c41d9acb4bc4ae1c9eea90aaf796ffc5932cc50548716">MANUAL_SPLIT_PRE</a>, <a href="format.md#gga10d9833450f29129d249c41d9acb4bc4a2b3ef6d50352019e54db9736e6dde05e">MANUAL_SPLIT_NORMAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1734167380093521"><a name="p1734167380093521"></a><a name="p1734167380093521"></a>Enumerates manual split types for the muxer. </p>
</td>
</tr>
<tr id="row811883861093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1525627023093521"><a name="p1525627023093521"></a><a name="p1525627023093521"></a><a href="format.md#ga953bc46f95d7b2d8866838d792f8f6aa">TrackSourceType</a> { <a href="format.md#gga953bc46f95d7b2d8866838d792f8f6aaa59d8c33314397a4ae8c1ca7b9e4eb40f">TRACK_SOURCE_TYPE_VIDEO</a> = 0, <a href="format.md#gga953bc46f95d7b2d8866838d792f8f6aaa5e9f39cae59134e444907af8b372b7a4">TRACK_SOURCE_TYPE_AUDIO</a>, <a href="format.md#gga953bc46f95d7b2d8866838d792f8f6aaa5d0d794425327268d08990d26a21f50c">TRACK_SOURCE_TYPE_DATA</a>, <a href="format.md#gga953bc46f95d7b2d8866838d792f8f6aaa0fae189aab417f7c9756523f15a20cca">TRACK_SOURCE_TYPE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071590730093521"><a name="p2071590730093521"></a><a name="p2071590730093521"></a>Enumerates types of the muxer source track. </p>
</td>
</tr>
<tr id="row1424532839093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1257347436093521"><a name="p1257347436093521"></a><a name="p1257347436093521"></a><a href="format.md#gaab0feaba617470cb4aa830dc5935238c">KeyType</a> { <a href="format.md#ggaab0feaba617470cb4aa830dc5935238ca5a467ebeae7cb5f1568c3d881f545e70">KEY_TYPE_MIME</a> = 0x6d696d65, <a href="format.md#ggaab0feaba617470cb4aa830dc5935238ca9e29390ad126492d6aeb3a96fe60dfd0">KEY_TYPE_HTTP_HEADERS</a> = 0x68706864, <a href="format.md#ggaab0feaba617470cb4aa830dc5935238ca493efb89298fa6070eb02f4a4e1dc3da">KEY_TYPE_LANGUAGE</a> = 0x6c616e67, <a href="format.md#ggaab0feaba617470cb4aa830dc5935238ca1208cc2b99c8ac61f8fb68fd743cb231">KEY_TYPE_PRE_CACHE</a> = 0x70726361 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p863976279093521"><a name="p863976279093521"></a><a name="p863976279093521"></a>Enumerates key types used for setting and obtaining parameters. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1939831726093521"></a>
<table><thead align="left"><tr id="row1719560079093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1499655246093521"><a name="p1499655246093521"></a><a name="p1499655246093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1389957649093521"><a name="p1389957649093521"></a><a name="p1389957649093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row859046519093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158610810093521"><a name="p158610810093521"></a><a name="p158610810093521"></a><a href="format.md#gae10a50c8f3de6e54ee0dc3937f755920">FormatInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466079153093521"><a name="p1466079153093521"></a><a name="p1466079153093521"></a>void </p>
<p id="p646592996093521"><a name="p646592996093521"></a><a name="p646592996093521"></a>Initializes the format. </p>
</td>
</tr>
<tr id="row1811379226093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550997094093521"><a name="p1550997094093521"></a><a name="p1550997094093521"></a><a href="format.md#gabb574933ebb4f3d1d2ed299e79aeee2c">FormatDeInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1001017225093521"><a name="p1001017225093521"></a><a name="p1001017225093521"></a>void </p>
<p id="p898240311093521"><a name="p898240311093521"></a><a name="p898240311093521"></a>Deinitializes the format. </p>
</td>
</tr>
<tr id="row692590308093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813361837093521"><a name="p813361837093521"></a><a name="p813361837093521"></a><a href="format.md#ga183fbc31f2c9877ef56464abcccef374">FormatDemuxerCreate</a> (const <a href="formatsource.md">FormatSource</a> *source, void **handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p234082961093521"><a name="p234082961093521"></a><a name="p234082961093521"></a>int32_t </p>
<p id="p1259929089093521"><a name="p1259929089093521"></a><a name="p1259929089093521"></a>Creates a demuxer component and returns its context handle. </p>
</td>
</tr>
<tr id="row331133364093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479482199093521"><a name="p1479482199093521"></a><a name="p1479482199093521"></a><a href="format.md#ga92d859ba4745ce26b94595daaa40462d">FormatDemuxerSetParameter</a> (const void *handle, int32_t trackId, const <a href="parameteritem.md">ParameterItem</a> *metaData, int32_t metaDataCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p57918253093521"><a name="p57918253093521"></a><a name="p57918253093521"></a>int32_t </p>
<p id="p2111307591093521"><a name="p2111307591093521"></a><a name="p2111307591093521"></a>Sets demuxer attributes. </p>
</td>
</tr>
<tr id="row51131790093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p359032817093521"><a name="p359032817093521"></a><a name="p359032817093521"></a><a href="format.md#ga6c2a1aa9fdf1db8e2f14a3a92ffa23d5">FormatDemuxerGetParameter</a> (const void *handle, int32_t trackId, <a href="parameteritem.md">ParameterItem</a> *metaData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p621105903093521"><a name="p621105903093521"></a><a name="p621105903093521"></a>int32_t </p>
<p id="p108534306093521"><a name="p108534306093521"></a><a name="p108534306093521"></a>Obtains demuxer attributes. </p>
</td>
</tr>
<tr id="row1219868785093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1581246732093521"><a name="p1581246732093521"></a><a name="p1581246732093521"></a><a href="format.md#ga9ef126fc3132b556d49a275799e7753b">FormatDemuxerSetCallBack</a> (void *handle, const <a href="formatcallback.md">FormatCallback</a> *callBack)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1845587077093521"><a name="p1845587077093521"></a><a name="p1845587077093521"></a>int32_t </p>
<p id="p962160619093521"><a name="p962160619093521"></a><a name="p962160619093521"></a>Sets a callback for the demuxer. </p>
</td>
</tr>
<tr id="row677040066093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1452067094093521"><a name="p1452067094093521"></a><a name="p1452067094093521"></a><a href="format.md#gad2a15f3fa640f3f9e8e684d71b3a12cb">FormatDemuxerSetBufferConfig</a> (void *handle, const <a href="formatbuffersetting.md">FormatBufferSetting</a> *setting)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1589293972093521"><a name="p1589293972093521"></a><a name="p1589293972093521"></a>int32_t </p>
<p id="p1998230666093521"><a name="p1998230666093521"></a><a name="p1998230666093521"></a>Sets buffer information for the demuxer. </p>
</td>
</tr>
<tr id="row1625644382093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1163961406093521"><a name="p1163961406093521"></a><a name="p1163961406093521"></a><a href="format.md#ga565cbb52c95a95aab4dcc957fe998b5f">FormatDemuxerGetBufferConfig</a> (const void *handle, <a href="formatbuffersetting.md">FormatBufferSetting</a> *setting)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075586504093521"><a name="p1075586504093521"></a><a name="p1075586504093521"></a>int32_t </p>
<p id="p1019243560093521"><a name="p1019243560093521"></a><a name="p1019243560093521"></a>Obtains the buffer information of the demuxer. </p>
</td>
</tr>
<tr id="row581263133093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1507115950093521"><a name="p1507115950093521"></a><a name="p1507115950093521"></a><a href="format.md#gacfcf40d869a48125bd67d17f8a4fc3ce">FormatDemuxerPrepare</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2078002482093521"><a name="p2078002482093521"></a><a name="p2078002482093521"></a>int32_t </p>
<p id="p664098533093521"><a name="p664098533093521"></a><a name="p664098533093521"></a>Makes preparations for the demuxer. </p>
</td>
</tr>
<tr id="row1732197718093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1108735710093521"><a name="p1108735710093521"></a><a name="p1108735710093521"></a><a href="format.md#gad807d61c65e89629c7eed8f97426fd5a">FormatDemuxerGetFileInfo</a> (void *handle, <a href="fileinfo.md">FileInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1944561549093521"><a name="p1944561549093521"></a><a name="p1944561549093521"></a>int32_t </p>
<p id="p1189386484093521"><a name="p1189386484093521"></a><a name="p1189386484093521"></a>Obtains the attributes of a media file. </p>
</td>
</tr>
<tr id="row1421156431093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160038344093521"><a name="p160038344093521"></a><a name="p160038344093521"></a><a href="format.md#ga1d9cb94614e207def34f13eaa16ef2b7">FormatDemuxerSelectTrack</a> (const void *handle, int32_t programId, int32_t trackId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472728064093521"><a name="p1472728064093521"></a><a name="p1472728064093521"></a>int32_t </p>
<p id="p55569832093521"><a name="p55569832093521"></a><a name="p55569832093521"></a>Selects a specified media track. </p>
</td>
</tr>
<tr id="row1880113838093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p367253246093521"><a name="p367253246093521"></a><a name="p367253246093521"></a><a href="format.md#gaf5fd5bab9613d133827054f157d5520e">FormatDemuxerUnselectTrack</a> (const void *handle, int32_t programId, int32_t trackId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238373850093521"><a name="p1238373850093521"></a><a name="p1238373850093521"></a>int32_t </p>
<p id="p260708209093521"><a name="p260708209093521"></a><a name="p260708209093521"></a>Unselects a specified media track from which the demuxer reads data frames. </p>
</td>
</tr>
<tr id="row88687480093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1053065715093521"><a name="p1053065715093521"></a><a name="p1053065715093521"></a><a href="format.md#ga08544b1ba3373bf5cb211586e8195673">FormatDemuxerStart</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327905445093521"><a name="p327905445093521"></a><a name="p327905445093521"></a>int32_t </p>
<p id="p963552498093521"><a name="p963552498093521"></a><a name="p963552498093521"></a>Starts the demuxer. </p>
</td>
</tr>
<tr id="row496630091093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676323919093521"><a name="p676323919093521"></a><a name="p676323919093521"></a><a href="format.md#gab6ef68051ee2ed0015e721bedb1af61c">FormatDemuxerGetSelectedTrack</a> (const void *handle, int32_t *programId, int32_t trackId[], int32_t *nums)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p864237664093521"><a name="p864237664093521"></a><a name="p864237664093521"></a>int32_t </p>
<p id="p286873732093521"><a name="p286873732093521"></a><a name="p286873732093521"></a>Obtains the ID of the media track selected by the demuxer for output. </p>
</td>
</tr>
<tr id="row1133487224093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620731428093521"><a name="p1620731428093521"></a><a name="p1620731428093521"></a><a href="format.md#ga7b20e1b88413d20a348d7f796917cd94">FormatDemuxerReadFrame</a> (const void *handle, <a href="formatframe.md">FormatFrame</a> *frame, int32_t timeOutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734058558093521"><a name="p734058558093521"></a><a name="p734058558093521"></a>int32_t </p>
<p id="p1506054494093521"><a name="p1506054494093521"></a><a name="p1506054494093521"></a>Reads data frames. </p>
</td>
</tr>
<tr id="row2028168319093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76929873093521"><a name="p76929873093521"></a><a name="p76929873093521"></a><a href="format.md#ga291b805de194c695b72eb5ad721103d5">FormatDemuxerFreeFrame</a> (void *handle, <a href="formatframe.md">FormatFrame</a> *frame)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462293332093521"><a name="p1462293332093521"></a><a name="p1462293332093521"></a>int32_t </p>
<p id="p1649582317093521"><a name="p1649582317093521"></a><a name="p1649582317093521"></a>Frees data frames. </p>
</td>
</tr>
<tr id="row1754629280093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1269673606093521"><a name="p1269673606093521"></a><a name="p1269673606093521"></a><a href="format.md#gad53f1e848f3c2e0c8fa056a312b2ed6c">FormatDemuxerSeek</a> (const void *handle, int32_t streamIndex, int64_t timeStampUs, <a href="format.md#ga14aa9d18a71eff4a0b70f748f0377c94">FormatSeekMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508518409093521"><a name="p508518409093521"></a><a name="p508518409093521"></a>int32_t </p>
<p id="p484360537093521"><a name="p484360537093521"></a><a name="p484360537093521"></a>Seeks for a specified position for the demuxer. </p>
</td>
</tr>
<tr id="row403656741093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836567296093521"><a name="p1836567296093521"></a><a name="p1836567296093521"></a><a href="format.md#ga8a693d8be0b4b688d99e513608884e91">FormatDemuxerStop</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1651744877093521"><a name="p1651744877093521"></a><a name="p1651744877093521"></a>int32_t </p>
<p id="p819884744093521"><a name="p819884744093521"></a><a name="p819884744093521"></a>Stops the demuxer from working. </p>
</td>
</tr>
<tr id="row167205576093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410570327093521"><a name="p410570327093521"></a><a name="p410570327093521"></a><a href="format.md#ga98fd9a5a5d1ffd275fc46f898ca08413">FormatDemuxerDestory</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182575283093521"><a name="p182575283093521"></a><a name="p182575283093521"></a>int32_t </p>
<p id="p301481497093521"><a name="p301481497093521"></a><a name="p301481497093521"></a>Destroys demuxer resources. </p>
</td>
</tr>
<tr id="row1491814882093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1523108479093521"><a name="p1523108479093521"></a><a name="p1523108479093521"></a><a href="format.md#ga9c390276cb90f4753c32af5aa5c600ad">FormatMuxerCreate</a> (void **handle, <a href="formatoutputconfig.md">FormatOutputConfig</a> *outputConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1353850247093521"><a name="p1353850247093521"></a><a name="p1353850247093521"></a>int32_t </p>
<p id="p1637412764093521"><a name="p1637412764093521"></a><a name="p1637412764093521"></a>Creates a muxer and returns its context handle. </p>
</td>
</tr>
<tr id="row28465424093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p495238821093521"><a name="p495238821093521"></a><a name="p495238821093521"></a><a href="format.md#gaa41d46cef6d5e81c85614edbf824d803">FormatMuxerDestory</a> (const void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1083851557093521"><a name="p1083851557093521"></a><a name="p1083851557093521"></a>int32_t </p>
<p id="p574140425093521"><a name="p574140425093521"></a><a name="p574140425093521"></a>Destroys a muxer and release its resources created by calling <a href="format.md#ga9c390276cb90f4753c32af5aa5c600ad">FormatMuxerCreate</a>. </p>
</td>
</tr>
<tr id="row852177305093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p855014994093521"><a name="p855014994093521"></a><a name="p855014994093521"></a><a href="format.md#ga94e9ab3e534b69a358b7cc16e4f79b78">FormatMuxerAddTrack</a> (void *handle, const <a href="tracksource.md">TrackSource</a> *trackSource)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649850289093521"><a name="p649850289093521"></a><a name="p649850289093521"></a>int32_t </p>
<p id="p1804129790093521"><a name="p1804129790093521"></a><a name="p1804129790093521"></a>Adds a media track source for the muxer. For details about track sources, see <a href="tracksource.md">TrackSource</a>. </p>
</td>
</tr>
<tr id="row544124608093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1061927492093521"><a name="p1061927492093521"></a><a name="p1061927492093521"></a><a href="format.md#ga108cd7e319ade568f71890d57585f153">FormatMuxerSetCallBack</a> (void *handle, const <a href="formatcallback.md">FormatCallback</a> *callBack)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p232699723093521"><a name="p232699723093521"></a><a name="p232699723093521"></a>int32_t </p>
<p id="p1342771037093521"><a name="p1342771037093521"></a><a name="p1342771037093521"></a>Sets a callback for the muxer. For details about the callback, see <a href="formatcallback.md">FormatCallback</a>. </p>
</td>
</tr>
<tr id="row1142480063093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1060807975093521"><a name="p1060807975093521"></a><a name="p1060807975093521"></a><a href="format.md#ga96fc57913c3202d2d23704c69d660be5">FormatMuxerSetOrientation</a> (void *handle, int degrees)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p434888784093521"><a name="p434888784093521"></a><a name="p434888784093521"></a>int32_t </p>
<p id="p101681644093521"><a name="p101681644093521"></a><a name="p101681644093521"></a>Sets the orientation of the video track for the muxer. </p>
</td>
</tr>
<tr id="row376640218093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p756079189093521"><a name="p756079189093521"></a><a name="p756079189093521"></a><a href="format.md#ga967ba14fa1231eed2942b87a09deb953">FormatMuxerSetLocation</a> (const void *handle, int latitude, int longitude)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p502043158093521"><a name="p502043158093521"></a><a name="p502043158093521"></a>int32_t </p>
<p id="p70701905093521"><a name="p70701905093521"></a><a name="p70701905093521"></a>Sets the geographical information for the output file of the muxer. </p>
</td>
</tr>
<tr id="row1880303264093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994233454093521"><a name="p1994233454093521"></a><a name="p1994233454093521"></a><a href="format.md#ga6f3ba422c9bbca4c1d5a7a3fe85dd9b9">FormatMuxerSetMaxFileSize</a> (void *handle, int64_t bytes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1217804614093521"><a name="p1217804614093521"></a><a name="p1217804614093521"></a>int32_t </p>
<p id="p193740414093521"><a name="p193740414093521"></a><a name="p193740414093521"></a>Sets the maximum size (in bytes) for the output file of the muxer. </p>
</td>
</tr>
<tr id="row915634191093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p966199151093521"><a name="p966199151093521"></a><a name="p966199151093521"></a><a href="format.md#gae931061d822c4ffe447e9ba40a991597">FormatMuxerSetMaxFileDuration</a> (void *handle, int64_t durationUs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979275665093521"><a name="p979275665093521"></a><a name="p979275665093521"></a>int32_t </p>
<p id="p1975891033093521"><a name="p1975891033093521"></a><a name="p1975891033093521"></a>Sets the maximum duration (in seconds) for the output file. </p>
</td>
</tr>
<tr id="row1399588307093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1333938121093521"><a name="p1333938121093521"></a><a name="p1333938121093521"></a><a href="format.md#ga6eed6b5e7522e102f2d79d0dd33fd2a9">FormatMuxerSetFileSplitDuration</a> (const void *handle, <a href="format.md#ga10d9833450f29129d249c41d9acb4bc4">ManualSplitType</a> type, int64_t timestampUs, uint32_t durationUs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p771112803093521"><a name="p771112803093521"></a><a name="p771112803093521"></a>int32_t </p>
<p id="p333133591093521"><a name="p333133591093521"></a><a name="p333133591093521"></a>Manually splits a file. </p>
</td>
</tr>
<tr id="row770128984093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p914405381093521"><a name="p914405381093521"></a><a name="p914405381093521"></a><a href="format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b">FormatMuxerStart</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669991615093521"><a name="p669991615093521"></a><a name="p669991615093521"></a>int32_t </p>
<p id="p718432015093521"><a name="p718432015093521"></a><a name="p718432015093521"></a>Starts the muxer. </p>
</td>
</tr>
<tr id="row1305196220093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1466783541093521"><a name="p1466783541093521"></a><a name="p1466783541093521"></a><a href="format.md#ga82037d271e77da206e16582e774ee048">FormatMuxerWriteFrame</a> (const void *handle, const <a href="formatframe.md">FormatFrame</a> *frameData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59644135093521"><a name="p59644135093521"></a><a name="p59644135093521"></a>int32_t </p>
<p id="p1600461512093521"><a name="p1600461512093521"></a><a name="p1600461512093521"></a>Writes data frames into the muxer. </p>
</td>
</tr>
<tr id="row1519741104093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1035081221093521"><a name="p1035081221093521"></a><a name="p1035081221093521"></a><a href="format.md#gaa936b56996294d76977537267fef058c">FormatMuxerSetNextOutputFile</a> (const void *handle, int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1374483493093521"><a name="p1374483493093521"></a><a name="p1374483493093521"></a>int32_t </p>
<p id="p1126769406093521"><a name="p1126769406093521"></a><a name="p1126769406093521"></a>Sets the descriptor for the next output file. </p>
</td>
</tr>
<tr id="row1462486203093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062980499093521"><a name="p1062980499093521"></a><a name="p1062980499093521"></a><a href="format.md#ga66a3a5a1ec6d01fcbd6339f7eee1151b">FormatMuxerStop</a> (const void *handle, bool block)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056445150093521"><a name="p1056445150093521"></a><a name="p1056445150093521"></a>int32_t </p>
<p id="p740669376093521"><a name="p740669376093521"></a><a name="p740669376093521"></a>Stops the muxer that was started by calling <a href="format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b">FormatMuxerStart</a>. </p>
</td>
</tr>
<tr id="row1649355356093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p251126297093521"><a name="p251126297093521"></a><a name="p251126297093521"></a><a href="format.md#gad4335ebaa7c165b885a00fe61aae0cd9">FormatMuxerSetParameter</a> (void *handle, int32_t trackId, const <a href="parameteritem.md">ParameterItem</a> *item, int32_t itemNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082779476093521"><a name="p2082779476093521"></a><a name="p2082779476093521"></a>int32_t </p>
<p id="p352556141093521"><a name="p352556141093521"></a><a name="p352556141093521"></a>Sets muxer attributes. </p>
</td>
</tr>
<tr id="row1659055422093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p90075810093521"><a name="p90075810093521"></a><a name="p90075810093521"></a><a href="format.md#ga67dd7361dedf335496afef19d54e4138">FormatMuxerGetParameter</a> (void *handle, int32_t trackId, <a href="parameteritem.md">ParameterItem</a> *item, int32_t itemNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1217885946093521"><a name="p1217885946093521"></a><a name="p1217885946093521"></a>int32_t </p>
<p id="p1748397282093521"><a name="p1748397282093521"></a><a name="p1748397282093521"></a>Obtains muxer attributes. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section203090199093521"></a>

## **Macro Definition Documentation**<a name="section910824588093521"></a>

## FORMAT\_INVALID\_PROGRAM\_ID<a name="gab4007b017f1edad143959af034e32bf7"></a>

```
#define FORMAT_INVALID_PROGRAM_ID   -1
```

 **Description:**

Indicates an invalid program ID. 

## FORMAT\_INVALID\_TRACK\_ID<a name="ga62037bb16334896e1bb6d35a71618881"></a>

```
#define FORMAT_INVALID_TRACK_ID   -1
```

 **Description:**

Indicates an invalid track ID. 

## FORMAT\_LANGUAGE\_LEN<a name="gaa70508bb1089c99f9aa3d59fcbdfa8eb"></a>

```
#define FORMAT_LANGUAGE_LEN   4
```

 **Description:**

Indicates the number of characters contained in the language description. 

## FORMAT\_MAX\_LANGUAGE\_NUM<a name="gac2d2d077edb8e9bb9f85ab6350015c5b"></a>

```
#define FORMAT_MAX_LANGUAGE_NUM   4
```

 **Description:**

Indicates the number of languages in the subtitle file. 

## FORMAT\_TITLE\_LEN<a name="gadb635fac84a9d62e99c69e75d4de85c3"></a>

```
#define FORMAT_TITLE_LEN   64
```

 **Description:**

Indicates the number of title characters. 

## URL\_LEN<a name="ga1ac54dd3b9b49c1800b5f502a87650be"></a>

```
#define URL_LEN   4096
```

 **Description:**

Indicates the URL length. 

## **Typedef Documentation**<a name="section1837281045093521"></a>

## CALLBACK\_HANDLE<a name="gab928f39c359734527bda3fd160f89331"></a>

```
typedef void* [CALLBACK_HANDLE](format.md#gab928f39c359734527bda3fd160f89331)
```

 **Description:**

Indicates the pointer to the callback handle for listening the muxer. 

## **Enumeration Type Documentation**<a name="section363176878093521"></a>

## AudioSampleFmt<a name="gadf0700999998f587f0017c4d02977b22"></a>

```
enum [AudioSampleFmt](format.md#gadf0700999998f587f0017c4d02977b22)
```

 **Description:**

Enumerates audio sampling formats. 

<a name="table95006721093521"></a>
<table><thead align="left"><tr id="row995313103093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1414905922093521"><a name="p1414905922093521"></a><a name="p1414905922093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p825449265093521"><a name="p825449265093521"></a><a name="p825449265093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row142652456093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadf0700999998f587f0017c4d02977b22a650b7f83085e55b6e728fd3ec5beec50"><a name="ggadf0700999998f587f0017c4d02977b22a650b7f83085e55b6e728fd3ec5beec50"></a><a name="ggadf0700999998f587f0017c4d02977b22a650b7f83085e55b6e728fd3ec5beec50"></a></strong>AUDIO_SAMPLE_FMT_S8 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1257877867093521"><a name="p1257877867093521"></a><a name="p1257877867093521"></a>8-bit integer for a single sample </p>
 </td>
</tr>
<tr id="row241666779093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadf0700999998f587f0017c4d02977b22a40335eaa7ca378540941909ed02b51a0"><a name="ggadf0700999998f587f0017c4d02977b22a40335eaa7ca378540941909ed02b51a0"></a><a name="ggadf0700999998f587f0017c4d02977b22a40335eaa7ca378540941909ed02b51a0"></a></strong>AUDIO_SAMPLE_FMT_S16 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1789108074093521"><a name="p1789108074093521"></a><a name="p1789108074093521"></a>16-bit integer for a single sample </p>
 </td>
</tr>
<tr id="row780110453093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadf0700999998f587f0017c4d02977b22af55ab2a69453af86f0c1602d3645f5f9"><a name="ggadf0700999998f587f0017c4d02977b22af55ab2a69453af86f0c1602d3645f5f9"></a><a name="ggadf0700999998f587f0017c4d02977b22af55ab2a69453af86f0c1602d3645f5f9"></a></strong>AUDIO_SAMPLE_FMT_S24 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687836901093521"><a name="p1687836901093521"></a><a name="p1687836901093521"></a>24-bit integer for a single sample </p>
 </td>
</tr>
<tr id="row384646312093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadf0700999998f587f0017c4d02977b22ab98feafb8396c0190a4fb719a15ab7c5"><a name="ggadf0700999998f587f0017c4d02977b22ab98feafb8396c0190a4fb719a15ab7c5"></a><a name="ggadf0700999998f587f0017c4d02977b22ab98feafb8396c0190a4fb719a15ab7c5"></a></strong>AUDIO_SAMPLE_FMT_S32 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395537646093521"><a name="p395537646093521"></a><a name="p395537646093521"></a>32-bit integer for a single sample </p>
 </td>
</tr>
<tr id="row1466358585093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadf0700999998f587f0017c4d02977b22ac2fb27a42b3f79e51dd71ce05b42f9db"><a name="ggadf0700999998f587f0017c4d02977b22ac2fb27a42b3f79e51dd71ce05b42f9db"></a><a name="ggadf0700999998f587f0017c4d02977b22ac2fb27a42b3f79e51dd71ce05b42f9db"></a></strong>AUDIO_SAMPLE_FMT_FLOAT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27517539093521"><a name="p27517539093521"></a><a name="p27517539093521"></a>Single-precision floating point number for a single sample </p>
 </td>
</tr>
</tbody>
</table>

## CodecFormat<a name="gaf7ed135f15d4b218d41705bac0122ba7"></a>

```
enum [CodecFormat](format.md#gaf7ed135f15d4b218d41705bac0122ba7)
```

 **Description:**

Enumerates audio, video, and image encoding formats. 

<a name="table563713522093521"></a>
<table><thead align="left"><tr id="row514391967093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p463646786093521"><a name="p463646786093521"></a><a name="p463646786093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p538901090093521"><a name="p538901090093521"></a><a name="p538901090093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row499685312093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7aa0c89a6d185559b38e63265976dde7f4"><a name="ggaf7ed135f15d4b218d41705bac0122ba7aa0c89a6d185559b38e63265976dde7f4"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7aa0c89a6d185559b38e63265976dde7f4"></a></strong>CODEC_H264 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543988183093521"><a name="p1543988183093521"></a><a name="p1543988183093521"></a>H264 or AVC </p>
 </td>
</tr>
<tr id="row1092418994093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7a4adc0c5e441be1b1a642f481e3111cae"><a name="ggaf7ed135f15d4b218d41705bac0122ba7a4adc0c5e441be1b1a642f481e3111cae"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7a4adc0c5e441be1b1a642f481e3111cae"></a></strong>CODEC_H265 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554768152093521"><a name="p1554768152093521"></a><a name="p1554768152093521"></a>H265 or HEVC </p>
 </td>
</tr>
<tr id="row709084506093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7ab6432cb3fb17152277af1f486e182612"><a name="ggaf7ed135f15d4b218d41705bac0122ba7ab6432cb3fb17152277af1f486e182612"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7ab6432cb3fb17152277af1f486e182612"></a></strong>CODEC_JPEG </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653141955093521"><a name="p1653141955093521"></a><a name="p1653141955093521"></a>JPEG </p>
 </td>
</tr>
<tr id="row1846765727093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7a8a0888876671d503c2c5e15059461c06"><a name="ggaf7ed135f15d4b218d41705bac0122ba7a8a0888876671d503c2c5e15059461c06"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7a8a0888876671d503c2c5e15059461c06"></a></strong>CODEC_AAC </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1764458286093521"><a name="p1764458286093521"></a><a name="p1764458286093521"></a>AAC </p>
 </td>
</tr>
<tr id="row2090088587093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7a44fd5227148450a7870e202d50110509"><a name="ggaf7ed135f15d4b218d41705bac0122ba7a44fd5227148450a7870e202d50110509"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7a44fd5227148450a7870e202d50110509"></a></strong>CODEC_G711A </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p971715022093521"><a name="p971715022093521"></a><a name="p971715022093521"></a>G711A </p>
 </td>
</tr>
<tr id="row1114102458093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7a3ac447dc6b8707c70f6fc6d4e0c552d5"><a name="ggaf7ed135f15d4b218d41705bac0122ba7a3ac447dc6b8707c70f6fc6d4e0c552d5"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7a3ac447dc6b8707c70f6fc6d4e0c552d5"></a></strong>CODEC_G711U </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803051484093521"><a name="p1803051484093521"></a><a name="p1803051484093521"></a>G711u </p>
 </td>
</tr>
<tr id="row1977463941093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7ae3014fa1161193bc92227ea0895e1dfb"><a name="ggaf7ed135f15d4b218d41705bac0122ba7ae3014fa1161193bc92227ea0895e1dfb"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7ae3014fa1161193bc92227ea0895e1dfb"></a></strong>CODEC_PCM </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350528423093521"><a name="p1350528423093521"></a><a name="p1350528423093521"></a>PCM </p>
 </td>
</tr>
<tr id="row1069486894093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7a2a0119a66bcbe797c1bac3057a802c9a"><a name="ggaf7ed135f15d4b218d41705bac0122ba7a2a0119a66bcbe797c1bac3057a802c9a"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7a2a0119a66bcbe797c1bac3057a802c9a"></a></strong>CODEC_MP3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331158148093521"><a name="p1331158148093521"></a><a name="p1331158148093521"></a>MP3 </p>
 </td>
</tr>
<tr id="row445487857093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf7ed135f15d4b218d41705bac0122ba7a0bccf3a2f309d8c485283d386322f07b"><a name="ggaf7ed135f15d4b218d41705bac0122ba7a0bccf3a2f309d8c485283d386322f07b"></a><a name="ggaf7ed135f15d4b218d41705bac0122ba7a0bccf3a2f309d8c485283d386322f07b"></a></strong>CODEC_BUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1386672946093521"><a name="p1386672946093521"></a><a name="p1386672946093521"></a>Undefined format </p>
 </td>
</tr>
</tbody>
</table>

## DataFlags<a name="gacff079fdf8427c743f9197ea5be33a7f"></a>

```
enum [DataFlags](format.md#gacff079fdf8427c743f9197ea5be33a7f)
```

 **Description:**

Enumerates flags of raw stream data. 

<a name="table911606734093521"></a>
<table><thead align="left"><tr id="row1475559647093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1139927798093521"><a name="p1139927798093521"></a><a name="p1139927798093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1742020083093521"><a name="p1742020083093521"></a><a name="p1742020083093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row609296170093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7faf5d58e6ec118e0660b53c7a7df2fdc8b"><a name="ggacff079fdf8427c743f9197ea5be33a7faf5d58e6ec118e0660b53c7a7df2fdc8b"></a><a name="ggacff079fdf8427c743f9197ea5be33a7faf5d58e6ec118e0660b53c7a7df2fdc8b"></a></strong>DATA_FLAG_NONE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913419081093521"><a name="p1913419081093521"></a><a name="p1913419081093521"></a>None </p>
 </td>
</tr>
<tr id="row1473389835093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7fad000cf60ee0b16f1ea7fedbcdb1a9fa0"><a name="ggacff079fdf8427c743f9197ea5be33a7fad000cf60ee0b16f1ea7fedbcdb1a9fa0"></a><a name="ggacff079fdf8427c743f9197ea5be33a7fad000cf60ee0b16f1ea7fedbcdb1a9fa0"></a></strong>DATA_FLAG_SYNCFRAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46732691093521"><a name="p46732691093521"></a><a name="p46732691093521"></a>Synchronization frame </p>
 </td>
</tr>
<tr id="row230562051093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7fa9200ae4b5fc3c72f2e70c9a49c2ebbb0"><a name="ggacff079fdf8427c743f9197ea5be33a7fa9200ae4b5fc3c72f2e70c9a49c2ebbb0"></a><a name="ggacff079fdf8427c743f9197ea5be33a7fa9200ae4b5fc3c72f2e70c9a49c2ebbb0"></a></strong>DATA_FLAG_CODECCONFIG </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012502667093521"><a name="p1012502667093521"></a><a name="p1012502667093521"></a>Codec configuration information </p>
 </td>
</tr>
<tr id="row1612947259093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7fabaa169afc64ef32b743217c8194fd8b9"><a name="ggacff079fdf8427c743f9197ea5be33a7fabaa169afc64ef32b743217c8194fd8b9"></a><a name="ggacff079fdf8427c743f9197ea5be33a7fabaa169afc64ef32b743217c8194fd8b9"></a></strong>DATA_FLAG_EOS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1984063168093521"><a name="p1984063168093521"></a><a name="p1984063168093521"></a>End of a single stream </p>
 </td>
</tr>
<tr id="row2098979085093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7fa26019220bb1298308f5c3dcd8a071f63"><a name="ggacff079fdf8427c743f9197ea5be33a7fa26019220bb1298308f5c3dcd8a071f63"></a><a name="ggacff079fdf8427c743f9197ea5be33a7fa26019220bb1298308f5c3dcd8a071f63"></a></strong>DATA_FLAG_PARTIAL_FRAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831628170093521"><a name="p1831628170093521"></a><a name="p1831628170093521"></a>Partial synchronization frame. This flag is used for multiple segments (except for the last one) into which a single frame is divided. </p>
 </td>
</tr>
<tr id="row285435004093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7fa5fd5b55061c6e94a8a12f9cf9d2009a7"><a name="ggacff079fdf8427c743f9197ea5be33a7fa5fd5b55061c6e94a8a12f9cf9d2009a7"></a><a name="ggacff079fdf8427c743f9197ea5be33a7fa5fd5b55061c6e94a8a12f9cf9d2009a7"></a></strong>DATA_FLAG_ENDOFFRAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833444118093521"><a name="p833444118093521"></a><a name="p833444118093521"></a>End of a frame. This flag is used in pair with <strong id="b760481914093521"><a name="b760481914093521"></a><a name="b760481914093521"></a>DATA_FLAG_PARTIAL_FRAME</strong> for the last segment of the frame. </p>
 </td>
</tr>
<tr id="row278471952093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacff079fdf8427c743f9197ea5be33a7faeb92d052f544e6cde910fb669790a804"><a name="ggacff079fdf8427c743f9197ea5be33a7faeb92d052f544e6cde910fb669790a804"></a><a name="ggacff079fdf8427c743f9197ea5be33a7faeb92d052f544e6cde910fb669790a804"></a></strong>DATA_FLAG_MUXER_DATA </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p384267497093521"><a name="p384267497093521"></a><a name="p384267497093521"></a>Encapsulated data with its container </p>
 </td>
</tr>
</tbody>
</table>

## FormatErrorType<a name="ga31e7fcf42722fa15e4e5489c2fef9092"></a>

```
enum [FormatErrorType](format.md#ga31e7fcf42722fa15e4e5489c2fef9092)
```

 **Description:**

Enumerates callback error types. 

## FormatInfoType<a name="ga6f00342925d3d5e586c76f8695985cad"></a>

```
enum [FormatInfoType](format.md#ga6f00342925d3d5e586c76f8695985cad)
```

 **Description:**

Enumerates types of callback information. 

<a name="table1086668767093521"></a>
<table><thead align="left"><tr id="row264059071093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p204214856093521"><a name="p204214856093521"></a><a name="p204214856093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1267901941093521"><a name="p1267901941093521"></a><a name="p1267901941093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row888097793093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cadaf6214216fd62faa4fc5e20d0d0ba60bf"><a name="gga6f00342925d3d5e586c76f8695985cadaf6214216fd62faa4fc5e20d0d0ba60bf"></a><a name="gga6f00342925d3d5e586c76f8695985cadaf6214216fd62faa4fc5e20d0d0ba60bf"></a></strong>MUXER_INFO_MAX_DURATION_APPROACHING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268141386093521"><a name="p268141386093521"></a><a name="p268141386093521"></a>The capturing duration is reaching the threshold specified by <a href="format.md#gae931061d822c4ffe447e9ba40a991597">FormatMuxerSetMaxFileDuration</a>. This information is reported when only one second or 10% is left to reach the allowed duration. </p>
 </td>
</tr>
<tr id="row456790013093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cadafc74f41e73f13a29a83b3a13ea6e66e1"><a name="gga6f00342925d3d5e586c76f8695985cadafc74f41e73f13a29a83b3a13ea6e66e1"></a><a name="gga6f00342925d3d5e586c76f8695985cadafc74f41e73f13a29a83b3a13ea6e66e1"></a></strong>MUXER_INFO_MAX_FILESIZE_APPROACHING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p301792517093521"><a name="p301792517093521"></a><a name="p301792517093521"></a>The captured file size is reaching the threshold specified by <a href="format.md#ga6f3ba422c9bbca4c1d5a7a3fe85dd9b9">FormatMuxerSetMaxFileSize</a>. This information is reported when only 100 KB or 10% is left to reach the allowed size. </p>
 </td>
</tr>
<tr id="row2050673571093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cada9722ce52063f6247d5fb17470eb9559e"><a name="gga6f00342925d3d5e586c76f8695985cada9722ce52063f6247d5fb17470eb9559e"></a><a name="gga6f00342925d3d5e586c76f8695985cada9722ce52063f6247d5fb17470eb9559e"></a></strong>MUXER_INFO_MAX_DURATION_REACHED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005504051093521"><a name="p2005504051093521"></a><a name="p2005504051093521"></a>The capturing duration reached the threshold specified by <a href="format.md#gae931061d822c4ffe447e9ba40a991597">FormatMuxerSetMaxFileDuration</a>, and the capturing is ended. If the file is set by a file descriptor, the caller needs to close the file. </p>
 </td>
</tr>
<tr id="row2090836213093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cada71704a053cf3e30c7bf91522b27da8c2"><a name="gga6f00342925d3d5e586c76f8695985cada71704a053cf3e30c7bf91522b27da8c2"></a><a name="gga6f00342925d3d5e586c76f8695985cada71704a053cf3e30c7bf91522b27da8c2"></a></strong>MUXER_INFO_MAX_FILESIZE_REACHED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1587908724093521"><a name="p1587908724093521"></a><a name="p1587908724093521"></a>The captured file size reached the threshold specified by <a href="format.md#ga6f3ba422c9bbca4c1d5a7a3fe85dd9b9">FormatMuxerSetMaxFileSize</a>, and the capturing is ended. If the file is set by a file descriptor, the caller needs to close the file. </p>
 </td>
</tr>
<tr id="row160837749093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cadae63cbc02cf7dc61073b739c08cc58ff4"><a name="gga6f00342925d3d5e586c76f8695985cadae63cbc02cf7dc61073b739c08cc58ff4"></a><a name="gga6f00342925d3d5e586c76f8695985cadae63cbc02cf7dc61073b739c08cc58ff4"></a></strong>MUXER_INFO_NEXT_OUTPUT_FILE_STARTED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p898127442093521"><a name="p898127442093521"></a><a name="p898127442093521"></a>The capturing started for the next output file. </p>
 </td>
</tr>
<tr id="row986400207093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cada3cf56a06f5990ab657d61bd7e57c1783"><a name="gga6f00342925d3d5e586c76f8695985cada3cf56a06f5990ab657d61bd7e57c1783"></a><a name="gga6f00342925d3d5e586c76f8695985cada3cf56a06f5990ab657d61bd7e57c1783"></a></strong>MUXER_INFO_FILE_SPLIT_FINISHED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p940191868093521"><a name="p940191868093521"></a><a name="p940191868093521"></a>Manual file split is completed. </p>
 </td>
</tr>
<tr id="row1944192314093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cada5d3901c368e7a4f719134c98c4fa8313"><a name="gga6f00342925d3d5e586c76f8695985cada5d3901c368e7a4f719134c98c4fa8313"></a><a name="gga6f00342925d3d5e586c76f8695985cada5d3901c368e7a4f719134c98c4fa8313"></a></strong>MUXER_INFO_FILE_START_TIME_MS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p845426130093521"><a name="p845426130093521"></a><a name="p845426130093521"></a>Start time of the captured file </p>
 </td>
</tr>
<tr id="row1846348047093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cadaeb00ffb6342b7ede6b5efe81fa842374"><a name="gga6f00342925d3d5e586c76f8695985cadaeb00ffb6342b7ede6b5efe81fa842374"></a><a name="gga6f00342925d3d5e586c76f8695985cadaeb00ffb6342b7ede6b5efe81fa842374"></a></strong>DEMUXER_INFO_PREPARED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1444840561093521"><a name="p1444840561093521"></a><a name="p1444840561093521"></a>The prepare function is asynchronously executed. This information is reported after the execution is complete. </p>
 </td>
</tr>
<tr id="row15371093093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cada929a71c6b58dfcd974e960b99139a758"><a name="gga6f00342925d3d5e586c76f8695985cada929a71c6b58dfcd974e960b99139a758"></a><a name="gga6f00342925d3d5e586c76f8695985cada929a71c6b58dfcd974e960b99139a758"></a></strong>DEMUXER_INFO_SEEK_COMPLETE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p111784993093521"><a name="p111784993093521"></a><a name="p111784993093521"></a>The seek function is asynchronously executed. This information is reported after the execution is complete. </p>
 </td>
</tr>
<tr id="row672883370093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cada2c4b1c086d55b4d5bf3fedbbf115cf63"><a name="gga6f00342925d3d5e586c76f8695985cada2c4b1c086d55b4d5bf3fedbbf115cf63"></a><a name="gga6f00342925d3d5e586c76f8695985cada2c4b1c086d55b4d5bf3fedbbf115cf63"></a></strong>DEMUXER_INFO_NETWORK_DISCONNECTED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2056675389093521"><a name="p2056675389093521"></a><a name="p2056675389093521"></a>The network is disconnected during network playback. </p>
 </td>
</tr>
<tr id="row2119448927093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6f00342925d3d5e586c76f8695985cadac157e535a1828f3b87c9cc3e6fd8773b"><a name="gga6f00342925d3d5e586c76f8695985cadac157e535a1828f3b87c9cc3e6fd8773b"></a><a name="gga6f00342925d3d5e586c76f8695985cadac157e535a1828f3b87c9cc3e6fd8773b"></a></strong>DEMUXER_INFO_NETWORK_RECONNECTED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p972685301093521"><a name="p972685301093521"></a><a name="p972685301093521"></a>The network is automatically reconnected during network playback. </p>
 </td>
</tr>
</tbody>
</table>

## FormatSeekMode<a name="ga14aa9d18a71eff4a0b70f748f0377c94"></a>

```
enum [FormatSeekMode](format.md#ga14aa9d18a71eff4a0b70f748f0377c94)
```

 **Description:**

Enumerates seek modes. 

<a name="table708943638093521"></a>
<table><thead align="left"><tr id="row1339621874093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1808974563093521"><a name="p1808974563093521"></a><a name="p1808974563093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1582882632093521"><a name="p1582882632093521"></a><a name="p1582882632093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row780323944093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga14aa9d18a71eff4a0b70f748f0377c94a59c30f44f3b65ff91ee18441315dbbcc"><a name="gga14aa9d18a71eff4a0b70f748f0377c94a59c30f44f3b65ff91ee18441315dbbcc"></a><a name="gga14aa9d18a71eff4a0b70f748f0377c94a59c30f44f3b65ff91ee18441315dbbcc"></a></strong>FORMAT_SEEK_MODE_FORWARD_KEY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1763467037093521"><a name="p1763467037093521"></a><a name="p1763467037093521"></a>Seeks forwards for the keyframe closest to specified position. </p>
 </td>
</tr>
<tr id="row199795335093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga14aa9d18a71eff4a0b70f748f0377c94a00f9ebeb7f829675bde8cad3832efcdd"><a name="gga14aa9d18a71eff4a0b70f748f0377c94a00f9ebeb7f829675bde8cad3832efcdd"></a><a name="gga14aa9d18a71eff4a0b70f748f0377c94a00f9ebeb7f829675bde8cad3832efcdd"></a></strong>FORMAT_SEEK_MODE_BACKWARD_KEY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946931078093521"><a name="p946931078093521"></a><a name="p946931078093521"></a>Seeks backwards for the keyframe closest to specified position. </p>
 </td>
</tr>
<tr id="row520604414093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga14aa9d18a71eff4a0b70f748f0377c94a605cab737a9cfc0a06f911efa117646d"><a name="gga14aa9d18a71eff4a0b70f748f0377c94a605cab737a9cfc0a06f911efa117646d"></a><a name="gga14aa9d18a71eff4a0b70f748f0377c94a605cab737a9cfc0a06f911efa117646d"></a></strong>FORMAT_SEEK_MODE_CLOSEST_KEY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314241651093521"><a name="p1314241651093521"></a><a name="p1314241651093521"></a>Seeks for the keyframe closest to specified position. </p>
 </td>
</tr>
<tr id="row400664660093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga14aa9d18a71eff4a0b70f748f0377c94a1a87eaf0f3e52132aba4563232a6f248"><a name="gga14aa9d18a71eff4a0b70f748f0377c94a1a87eaf0f3e52132aba4563232a6f248"></a><a name="gga14aa9d18a71eff4a0b70f748f0377c94a1a87eaf0f3e52132aba4563232a6f248"></a></strong>SEEK_MODE_BUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1671282352093521"><a name="p1671282352093521"></a><a name="p1671282352093521"></a>Undefined mode </p>
 </td>
</tr>
</tbody>
</table>

## FrameType<a name="gad495a9f61af7fff07d7e97979d1ab854"></a>

```
enum [FrameType](format.md#gad495a9f61af7fff07d7e97979d1ab854)
```

 **Description:**

Enumerates data frame types. 

<a name="table916719481093521"></a>
<table><thead align="left"><tr id="row1383565375093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2003587545093521"><a name="p2003587545093521"></a><a name="p2003587545093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1723211395093521"><a name="p1723211395093521"></a><a name="p1723211395093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1608175641093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a54c4b682d718fd6c8e5f224ee2fad841"><a name="ggad495a9f61af7fff07d7e97979d1ab854a54c4b682d718fd6c8e5f224ee2fad841"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a54c4b682d718fd6c8e5f224ee2fad841"></a></strong>FRAME_TYPE_NONE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833656462093521"><a name="p833656462093521"></a><a name="p833656462093521"></a>Unknown type, which can be used for transport stream (TS) packets </p>
 </td>
</tr>
<tr id="row690348683093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a709dd5ff367a8ff7669fda5386291796"><a name="ggad495a9f61af7fff07d7e97979d1ab854a709dd5ff367a8ff7669fda5386291796"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a709dd5ff367a8ff7669fda5386291796"></a></strong>FRAME_TYPE_AUDIO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722568530093521"><a name="p1722568530093521"></a><a name="p1722568530093521"></a>Audio frame </p>
 </td>
</tr>
<tr id="row1174183993093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a7670f4378c84a94fb65f6c30c4b1a096"><a name="ggad495a9f61af7fff07d7e97979d1ab854a7670f4378c84a94fb65f6c30c4b1a096"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a7670f4378c84a94fb65f6c30c4b1a096"></a></strong>FRAME_TYPE_VIDEO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1247231659093521"><a name="p1247231659093521"></a><a name="p1247231659093521"></a>Video frame </p>
 </td>
</tr>
<tr id="row607111081093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a90bb6db5c310d60ccd4a6ec1b172e9e5"><a name="ggad495a9f61af7fff07d7e97979d1ab854a90bb6db5c310d60ccd4a6ec1b172e9e5"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a90bb6db5c310d60ccd4a6ec1b172e9e5"></a></strong>FRAME_TYPE_IMAGE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p411847570093521"><a name="p411847570093521"></a><a name="p411847570093521"></a>Image frame </p>
 </td>
</tr>
<tr id="row1989354109093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a3b43393b8fff68297e4daf0c32193704"><a name="ggad495a9f61af7fff07d7e97979d1ab854a3b43393b8fff68297e4daf0c32193704"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a3b43393b8fff68297e4daf0c32193704"></a></strong>FRAME_TYPE_SUB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783706636093521"><a name="p783706636093521"></a><a name="p783706636093521"></a>Subtitle frame </p>
 </td>
</tr>
<tr id="row2137216778093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a75641aebcb420f0f661dc8acefdc9b30"><a name="ggad495a9f61af7fff07d7e97979d1ab854a75641aebcb420f0f661dc8acefdc9b30"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a75641aebcb420f0f661dc8acefdc9b30"></a></strong>FRAME_TYPE_DATA </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572608919093521"><a name="p572608919093521"></a><a name="p572608919093521"></a>Data </p>
 </td>
</tr>
<tr id="row1947122066093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad495a9f61af7fff07d7e97979d1ab854a7afc81a56325cb4a7356663ccd270931"><a name="ggad495a9f61af7fff07d7e97979d1ab854a7afc81a56325cb4a7356663ccd270931"></a><a name="ggad495a9f61af7fff07d7e97979d1ab854a7afc81a56325cb4a7356663ccd270931"></a></strong>FRAME_TYPE_BUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184735482093521"><a name="p1184735482093521"></a><a name="p1184735482093521"></a>Undefined type </p>
 </td>
</tr>
</tbody>
</table>

## KeyType<a name="gaab0feaba617470cb4aa830dc5935238c"></a>

```
enum [KeyType](format.md#gaab0feaba617470cb4aa830dc5935238c)
```

 **Description:**

Enumerates key types used for setting and obtaining parameters. 

<a name="table700639851093521"></a>
<table><thead align="left"><tr id="row1954819580093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p925093377093521"><a name="p925093377093521"></a><a name="p925093377093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1649612756093521"><a name="p1649612756093521"></a><a name="p1649612756093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1870813679093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaab0feaba617470cb4aa830dc5935238ca5a467ebeae7cb5f1568c3d881f545e70"><a name="ggaab0feaba617470cb4aa830dc5935238ca5a467ebeae7cb5f1568c3d881f545e70"></a><a name="ggaab0feaba617470cb4aa830dc5935238ca5a467ebeae7cb5f1568c3d881f545e70"></a></strong>KEY_TYPE_MIME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p895977101093521"><a name="p895977101093521"></a><a name="p895977101093521"></a>MIME type. The value type is <strong id="b2098160036093521"><a name="b2098160036093521"></a><a name="b2098160036093521"></a>cstring</strong>. </p>
 </td>
</tr>
<tr id="row592286137093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaab0feaba617470cb4aa830dc5935238ca9e29390ad126492d6aeb3a96fe60dfd0"><a name="ggaab0feaba617470cb4aa830dc5935238ca9e29390ad126492d6aeb3a96fe60dfd0"></a><a name="ggaab0feaba617470cb4aa830dc5935238ca9e29390ad126492d6aeb3a96fe60dfd0"></a></strong>KEY_TYPE_HTTP_HEADERS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p99679331093521"><a name="p99679331093521"></a><a name="p99679331093521"></a>HTTP header. The value type is <strong id="b1188952866093521"><a name="b1188952866093521"></a><a name="b1188952866093521"></a>cstring</strong>. </p>
 </td>
</tr>
<tr id="row1744945803093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaab0feaba617470cb4aa830dc5935238ca493efb89298fa6070eb02f4a4e1dc3da"><a name="ggaab0feaba617470cb4aa830dc5935238ca493efb89298fa6070eb02f4a4e1dc3da"></a><a name="ggaab0feaba617470cb4aa830dc5935238ca493efb89298fa6070eb02f4a4e1dc3da"></a></strong>KEY_TYPE_LANGUAGE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1228765348093521"><a name="p1228765348093521"></a><a name="p1228765348093521"></a>Track language, which is usually the language of audio and subtitles. The value type is <strong id="b1370538692093521"><a name="b1370538692093521"></a><a name="b1370538692093521"></a>cstring</strong>. </p>
 </td>
</tr>
<tr id="row1939080916093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaab0feaba617470cb4aa830dc5935238ca1208cc2b99c8ac61f8fb68fd743cb231"><a name="ggaab0feaba617470cb4aa830dc5935238ca1208cc2b99c8ac61f8fb68fd743cb231"></a><a name="ggaab0feaba617470cb4aa830dc5935238ca1208cc2b99c8ac61f8fb68fd743cb231"></a></strong>KEY_TYPE_PRE_CACHE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79455067093521"><a name="p79455067093521"></a><a name="p79455067093521"></a>Precapture cache size. The value type is <strong id="b1294686213093521"><a name="b1294686213093521"></a><a name="b1294686213093521"></a>int</strong> </p>
 </td>
</tr>
</tbody>
</table>

## ManualSplitType<a name="ga10d9833450f29129d249c41d9acb4bc4"></a>

```
enum [ManualSplitType](format.md#ga10d9833450f29129d249c41d9acb4bc4)
```

 **Description:**

Enumerates manual split types for the muxer. 

<a name="table1416186359093521"></a>
<table><thead align="left"><tr id="row828851819093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1022007680093521"><a name="p1022007680093521"></a><a name="p1022007680093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p643654761093521"><a name="p643654761093521"></a><a name="p643654761093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1069674031093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga10d9833450f29129d249c41d9acb4bc4ad283396b08ef486b6615977c881a8724"><a name="gga10d9833450f29129d249c41d9acb4bc4ad283396b08ef486b6615977c881a8724"></a><a name="gga10d9833450f29129d249c41d9acb4bc4ad283396b08ef486b6615977c881a8724"></a></strong>MANUAL_SPLIT_POST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159312674093521"><a name="p159312674093521"></a><a name="p159312674093521"></a>Search forwards from the current I-frame and split the file at the closest I-frame. </p>
 </td>
</tr>
<tr id="row2026613663093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga10d9833450f29129d249c41d9acb4bc4ae1c9eea90aaf796ffc5932cc50548716"><a name="gga10d9833450f29129d249c41d9acb4bc4ae1c9eea90aaf796ffc5932cc50548716"></a><a name="gga10d9833450f29129d249c41d9acb4bc4ae1c9eea90aaf796ffc5932cc50548716"></a></strong>MANUAL_SPLIT_PRE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1119727078093521"><a name="p1119727078093521"></a><a name="p1119727078093521"></a>Search backwards from the current I-frame and split the file at the closest I-frame. </p>
 </td>
</tr>
<tr id="row1811217090093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga10d9833450f29129d249c41d9acb4bc4a2b3ef6d50352019e54db9736e6dde05e"><a name="gga10d9833450f29129d249c41d9acb4bc4a2b3ef6d50352019e54db9736e6dde05e"></a><a name="gga10d9833450f29129d249c41d9acb4bc4a2b3ef6d50352019e54db9736e6dde05e"></a></strong>MANUAL_SPLIT_NORMAL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508482109093521"><a name="p508482109093521"></a><a name="p508482109093521"></a>Normal split </p>
 </td>
</tr>
</tbody>
</table>

## OutputFormat<a name="gaeb712c6c6c0a8af0dfd79f451ecb9277"></a>

```
enum [OutputFormat](format.md#gaeb712c6c6c0a8af0dfd79f451ecb9277)
```

 **Description:**

Enumerates output file formats. 

<a name="table1228312093093521"></a>
<table><thead align="left"><tr id="row355702899093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p276409929093521"><a name="p276409929093521"></a><a name="p276409929093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1010427283093521"><a name="p1010427283093521"></a><a name="p1010427283093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row656689565093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeb712c6c6c0a8af0dfd79f451ecb9277a5a01488de2f310872db03b7a6ad26423"><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a5a01488de2f310872db03b7a6ad26423"></a><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a5a01488de2f310872db03b7a6ad26423"></a></strong>OUTPUT_FORMAT_MPEG_4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p978609002093521"><a name="p978609002093521"></a><a name="p978609002093521"></a>MP4 </p>
 </td>
</tr>
<tr id="row1467869679093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeb712c6c6c0a8af0dfd79f451ecb9277a9eaec301329c61d07d2fe19ca473abc2"><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a9eaec301329c61d07d2fe19ca473abc2"></a><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a9eaec301329c61d07d2fe19ca473abc2"></a></strong>OUTPUT_FORMAT_TS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p550406472093521"><a name="p550406472093521"></a><a name="p550406472093521"></a>TS </p>
 </td>
</tr>
<tr id="row182194698093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeb712c6c6c0a8af0dfd79f451ecb9277a3a0cc99ed9dcc44245dd91591b7accac"><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a3a0cc99ed9dcc44245dd91591b7accac"></a><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a3a0cc99ed9dcc44245dd91591b7accac"></a></strong>OUTPUT_FORMAT_THREE_GPP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389811354093521"><a name="p1389811354093521"></a><a name="p1389811354093521"></a>3GPP </p>
 </td>
</tr>
<tr id="row528766304093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeb712c6c6c0a8af0dfd79f451ecb9277a68afc7e60f3cdacd5e1fb9a5dcf0ebdb"><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a68afc7e60f3cdacd5e1fb9a5dcf0ebdb"></a><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a68afc7e60f3cdacd5e1fb9a5dcf0ebdb"></a></strong>OUTPUT_FORMAT_HEIF </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460064084093521"><a name="p1460064084093521"></a><a name="p1460064084093521"></a>HEIF </p>
 </td>
</tr>
<tr id="row697398658093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeb712c6c6c0a8af0dfd79f451ecb9277abb34ec8353ace07dbfd698c05343800d"><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277abb34ec8353ace07dbfd698c05343800d"></a><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277abb34ec8353ace07dbfd698c05343800d"></a></strong>OUTPUT_FORMAT_OGG </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1505506870093521"><a name="p1505506870093521"></a><a name="p1505506870093521"></a>Ogg </p>
 </td>
</tr>
<tr id="row179866407093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaeb712c6c6c0a8af0dfd79f451ecb9277a00eb675fb0d802a5143f4f718ea854e3"><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a00eb675fb0d802a5143f4f718ea854e3"></a><a name="ggaeb712c6c6c0a8af0dfd79f451ecb9277a00eb675fb0d802a5143f4f718ea854e3"></a></strong>OUTPUT_FORMAT_INVALID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p715204200093521"><a name="p715204200093521"></a><a name="p715204200093521"></a>Invalid format </p>
 </td>
</tr>
</tbody>
</table>

## OutputType<a name="ga4e0517338e6c4a31a2addafc06d4f3a3"></a>

```
enum [OutputType](format.md#ga4e0517338e6c4a31a2addafc06d4f3a3)
```

 **Description:**

Enumerates muxer output types. 

<a name="table302632683093521"></a>
<table><thead align="left"><tr id="row95070812093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p953771372093521"><a name="p953771372093521"></a><a name="p953771372093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p352211687093521"><a name="p352211687093521"></a><a name="p352211687093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1924644014093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga4e0517338e6c4a31a2addafc06d4f3a3a14ea73c5ea45e0f9b6976d24ac1119e9"><a name="gga4e0517338e6c4a31a2addafc06d4f3a3a14ea73c5ea45e0f9b6976d24ac1119e9"></a><a name="gga4e0517338e6c4a31a2addafc06d4f3a3a14ea73c5ea45e0f9b6976d24ac1119e9"></a></strong>OUTPUT_TYPE_FD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417686610093521"><a name="p417686610093521"></a><a name="p417686610093521"></a>File descriptor </p>
 </td>
</tr>
<tr id="row531698574093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga4e0517338e6c4a31a2addafc06d4f3a3a67f14fbe9f23ae5acd2ffc7b00fd6740"><a name="gga4e0517338e6c4a31a2addafc06d4f3a3a67f14fbe9f23ae5acd2ffc7b00fd6740"></a><a name="gga4e0517338e6c4a31a2addafc06d4f3a3a67f14fbe9f23ae5acd2ffc7b00fd6740"></a></strong>OUTPUT_TYPE_URI </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363482708093521"><a name="p1363482708093521"></a><a name="p1363482708093521"></a>Local file URI </p>
 </td>
</tr>
<tr id="row429416132093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga4e0517338e6c4a31a2addafc06d4f3a3a169d19953026c9c3fed4e4433624ca7c"><a name="gga4e0517338e6c4a31a2addafc06d4f3a3a169d19953026c9c3fed4e4433624ca7c"></a><a name="gga4e0517338e6c4a31a2addafc06d4f3a3a169d19953026c9c3fed4e4433624ca7c"></a></strong>OUTPUT_TYPE_INVALID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1904293850093521"><a name="p1904293850093521"></a><a name="p1904293850093521"></a>Undefined type </p>
 </td>
</tr>
</tbody>
</table>

## SourceType<a name="ga3ae727773c367ac1041d72ac770a0ab1"></a>

```
enum [SourceType](format.md#ga3ae727773c367ac1041d72ac770a0ab1)
```

 **Description:**

Enumerates types of the demuxer data source. 

<a name="table879791208093521"></a>
<table><thead align="left"><tr id="row333172576093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1863822342093521"><a name="p1863822342093521"></a><a name="p1863822342093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2067333260093521"><a name="p2067333260093521"></a><a name="p2067333260093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row265501713093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3ae727773c367ac1041d72ac770a0ab1a126568132b92d49365d94c4aa00cdde4"><a name="gga3ae727773c367ac1041d72ac770a0ab1a126568132b92d49365d94c4aa00cdde4"></a><a name="gga3ae727773c367ac1041d72ac770a0ab1a126568132b92d49365d94c4aa00cdde4"></a></strong>SOURCE_TYPE_FD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1304416880093521"><a name="p1304416880093521"></a><a name="p1304416880093521"></a>File descriptor </p>
 </td>
</tr>
<tr id="row1678394546093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3ae727773c367ac1041d72ac770a0ab1a70d32ea5aeaa325764508722ba31403c"><a name="gga3ae727773c367ac1041d72ac770a0ab1a70d32ea5aeaa325764508722ba31403c"></a><a name="gga3ae727773c367ac1041d72ac770a0ab1a70d32ea5aeaa325764508722ba31403c"></a></strong>SOURCE_TYPE_URI </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1355637244093521"><a name="p1355637244093521"></a><a name="p1355637244093521"></a>URI, which can be a network address or a local file path </p>
 </td>
</tr>
<tr id="row1024254742093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3ae727773c367ac1041d72ac770a0ab1a7f632a791d8f6dfbe5940b5648d29e6c"><a name="gga3ae727773c367ac1041d72ac770a0ab1a7f632a791d8f6dfbe5940b5648d29e6c"></a><a name="gga3ae727773c367ac1041d72ac770a0ab1a7f632a791d8f6dfbe5940b5648d29e6c"></a></strong>SOURCE_TYPE_STREAM </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858902887093521"><a name="p858902887093521"></a><a name="p858902887093521"></a>Streams </p>
 </td>
</tr>
<tr id="row1188740499093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3ae727773c367ac1041d72ac770a0ab1ad41c2f0bdca46364d6cd86fc5d4710d3"><a name="gga3ae727773c367ac1041d72ac770a0ab1ad41c2f0bdca46364d6cd86fc5d4710d3"></a><a name="gga3ae727773c367ac1041d72ac770a0ab1ad41c2f0bdca46364d6cd86fc5d4710d3"></a></strong>SOURCE_TYPE_BUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p328123464093521"><a name="p328123464093521"></a><a name="p328123464093521"></a>Undefined source </p>
 </td>
</tr>
</tbody>
</table>

## SubtitleFormat<a name="gadac45ce4731516c262292c15433439b3"></a>

```
enum [SubtitleFormat](format.md#gadac45ce4731516c262292c15433439b3)
```

 **Description:**

Enumerates subtitle file formats. 

<a name="table1120695254093521"></a>
<table><thead align="left"><tr id="row1862933837093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p333514096093521"><a name="p333514096093521"></a><a name="p333514096093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2146415089093521"><a name="p2146415089093521"></a><a name="p2146415089093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row661493732093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3abe03cb7d3bb87dcfc197b9e9db7a66f6"><a name="ggadac45ce4731516c262292c15433439b3abe03cb7d3bb87dcfc197b9e9db7a66f6"></a><a name="ggadac45ce4731516c262292c15433439b3abe03cb7d3bb87dcfc197b9e9db7a66f6"></a></strong>FORMAT_SUB_ASS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1486000511093521"><a name="p1486000511093521"></a><a name="p1486000511093521"></a>ASS </p>
 </td>
</tr>
<tr id="row11129794093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a569e5e22b1c3bf5b9f4cc3f596cfc6db"><a name="ggadac45ce4731516c262292c15433439b3a569e5e22b1c3bf5b9f4cc3f596cfc6db"></a><a name="ggadac45ce4731516c262292c15433439b3a569e5e22b1c3bf5b9f4cc3f596cfc6db"></a></strong>FORMAT_SUB_LRC </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232793156093521"><a name="p1232793156093521"></a><a name="p1232793156093521"></a>LRC </p>
 </td>
</tr>
<tr id="row1947082313093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a26f41cfe561866b43a9757b5902c7609"><a name="ggadac45ce4731516c262292c15433439b3a26f41cfe561866b43a9757b5902c7609"></a><a name="ggadac45ce4731516c262292c15433439b3a26f41cfe561866b43a9757b5902c7609"></a></strong>FORMAT_SUB_SRT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p809455324093521"><a name="p809455324093521"></a><a name="p809455324093521"></a>SRT </p>
 </td>
</tr>
<tr id="row2112108078093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3ac6665b95ccb70e7a7d87dda6370821ff"><a name="ggadac45ce4731516c262292c15433439b3ac6665b95ccb70e7a7d87dda6370821ff"></a><a name="ggadac45ce4731516c262292c15433439b3ac6665b95ccb70e7a7d87dda6370821ff"></a></strong>FORMAT_SUB_SMI </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1756238200093521"><a name="p1756238200093521"></a><a name="p1756238200093521"></a>SMI </p>
 </td>
</tr>
<tr id="row103492605093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a07a0a164bb0081359639cfdef57aa2c2"><a name="ggadac45ce4731516c262292c15433439b3a07a0a164bb0081359639cfdef57aa2c2"></a><a name="ggadac45ce4731516c262292c15433439b3a07a0a164bb0081359639cfdef57aa2c2"></a></strong>FORMAT_SUB_SUB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1131399377093521"><a name="p1131399377093521"></a><a name="p1131399377093521"></a>SUB </p>
 </td>
</tr>
<tr id="row518733011093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a5ad9a3ec464416e8395e3e0f6595c253"><a name="ggadac45ce4731516c262292c15433439b3a5ad9a3ec464416e8395e3e0f6595c253"></a><a name="ggadac45ce4731516c262292c15433439b3a5ad9a3ec464416e8395e3e0f6595c253"></a></strong>FORMAT_SUB_TXT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275842944093521"><a name="p1275842944093521"></a><a name="p1275842944093521"></a>RAW UTF-8 </p>
 </td>
</tr>
<tr id="row1925508674093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a9f573cd39fab8fc143480bf1eb973574"><a name="ggadac45ce4731516c262292c15433439b3a9f573cd39fab8fc143480bf1eb973574"></a><a name="ggadac45ce4731516c262292c15433439b3a9f573cd39fab8fc143480bf1eb973574"></a></strong>FORMAT_SUB_HDMV_PGS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370672065093521"><a name="p370672065093521"></a><a name="p370672065093521"></a>HDMV PGS </p>
 </td>
</tr>
<tr id="row1475065770093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a641b27aab74dbbcd88d7d8612b60caad"><a name="ggadac45ce4731516c262292c15433439b3a641b27aab74dbbcd88d7d8612b60caad"></a><a name="ggadac45ce4731516c262292c15433439b3a641b27aab74dbbcd88d7d8612b60caad"></a></strong>FORMAT_SUB_DVB_SUB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1079583032093521"><a name="p1079583032093521"></a><a name="p1079583032093521"></a>DVB </p>
 </td>
</tr>
<tr id="row329597240093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a91ab0e8c1931fc3b4f2350a8e18672a6"><a name="ggadac45ce4731516c262292c15433439b3a91ab0e8c1931fc3b4f2350a8e18672a6"></a><a name="ggadac45ce4731516c262292c15433439b3a91ab0e8c1931fc3b4f2350a8e18672a6"></a></strong>FORMAT_SUB_DVD_SUB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485361007093521"><a name="p1485361007093521"></a><a name="p1485361007093521"></a>DVD </p>
 </td>
</tr>
<tr id="row152497887093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a0750bc81000513246d5785d0ef2c0099"><a name="ggadac45ce4731516c262292c15433439b3a0750bc81000513246d5785d0ef2c0099"></a><a name="ggadac45ce4731516c262292c15433439b3a0750bc81000513246d5785d0ef2c0099"></a></strong>FORMAT_SUB_TTML </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1148031142093521"><a name="p1148031142093521"></a><a name="p1148031142093521"></a>TTML </p>
 </td>
</tr>
<tr id="row1597362424093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3ad9de45a6ae50e5443e2d0418b1cdde61"><a name="ggadac45ce4731516c262292c15433439b3ad9de45a6ae50e5443e2d0418b1cdde61"></a><a name="ggadac45ce4731516c262292c15433439b3ad9de45a6ae50e5443e2d0418b1cdde61"></a></strong>FORMAT_SUB_WEBVTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p456906527093521"><a name="p456906527093521"></a><a name="p456906527093521"></a>WebVTT </p>
 </td>
</tr>
<tr id="row1977553526093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggadac45ce4731516c262292c15433439b3a52ed4b60bc3d33d43753555e1edf50d7"><a name="ggadac45ce4731516c262292c15433439b3a52ed4b60bc3d33d43753555e1edf50d7"></a><a name="ggadac45ce4731516c262292c15433439b3a52ed4b60bc3d33d43753555e1edf50d7"></a></strong>FORMAT_SUB_BUTT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735265631093521"><a name="p735265631093521"></a><a name="p735265631093521"></a>Undefined format </p>
 </td>
</tr>
</tbody>
</table>

## SubtitleFrameType<a name="ga43b7f046e365a89697272d850b0517b7"></a>

```
enum [SubtitleFrameType](format.md#ga43b7f046e365a89697272d850b0517b7)
```

 **Description:**

Enumerates subtitle frame types. 

<a name="table1601809220093521"></a>
<table><thead align="left"><tr id="row1376359339093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1152436085093521"><a name="p1152436085093521"></a><a name="p1152436085093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p183068191093521"><a name="p183068191093521"></a><a name="p183068191093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row83643393093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga43b7f046e365a89697272d850b0517b7a6bc8b3dca40c75f6dd22feea62cbdac7"><a name="gga43b7f046e365a89697272d850b0517b7a6bc8b3dca40c75f6dd22feea62cbdac7"></a><a name="gga43b7f046e365a89697272d850b0517b7a6bc8b3dca40c75f6dd22feea62cbdac7"></a></strong>HI_SVR_SUBTITLE_BITMAP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p848227290093521"><a name="p848227290093521"></a><a name="p848227290093521"></a>Bitmap (BMP) </p>
 </td>
</tr>
<tr id="row477023337093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga43b7f046e365a89697272d850b0517b7a3ee7a0476e395ec2689f754e58d512a0"><a name="gga43b7f046e365a89697272d850b0517b7a3ee7a0476e395ec2689f754e58d512a0"></a><a name="gga43b7f046e365a89697272d850b0517b7a3ee7a0476e395ec2689f754e58d512a0"></a></strong>HI_SVR_SUBTITLE_TEXT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488152462093521"><a name="p1488152462093521"></a><a name="p1488152462093521"></a>Text </p>
 </td>
</tr>
</tbody>
</table>

## TrackSourceType<a name="ga953bc46f95d7b2d8866838d792f8f6aa"></a>

```
enum [TrackSourceType](format.md#ga953bc46f95d7b2d8866838d792f8f6aa)
```

 **Description:**

Enumerates types of the muxer source track. 

<a name="table1685841594093521"></a>
<table><thead align="left"><tr id="row1562723278093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p321066869093521"><a name="p321066869093521"></a><a name="p321066869093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p793678213093521"><a name="p793678213093521"></a><a name="p793678213093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row870872573093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga953bc46f95d7b2d8866838d792f8f6aaa59d8c33314397a4ae8c1ca7b9e4eb40f"><a name="gga953bc46f95d7b2d8866838d792f8f6aaa59d8c33314397a4ae8c1ca7b9e4eb40f"></a><a name="gga953bc46f95d7b2d8866838d792f8f6aaa59d8c33314397a4ae8c1ca7b9e4eb40f"></a></strong>TRACK_SOURCE_TYPE_VIDEO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p377890486093521"><a name="p377890486093521"></a><a name="p377890486093521"></a>Video track </p>
 </td>
</tr>
<tr id="row1065474942093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga953bc46f95d7b2d8866838d792f8f6aaa5e9f39cae59134e444907af8b372b7a4"><a name="gga953bc46f95d7b2d8866838d792f8f6aaa5e9f39cae59134e444907af8b372b7a4"></a><a name="gga953bc46f95d7b2d8866838d792f8f6aaa5e9f39cae59134e444907af8b372b7a4"></a></strong>TRACK_SOURCE_TYPE_AUDIO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700365975093521"><a name="p1700365975093521"></a><a name="p1700365975093521"></a>Audio track </p>
 </td>
</tr>
<tr id="row113708797093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga953bc46f95d7b2d8866838d792f8f6aaa5d0d794425327268d08990d26a21f50c"><a name="gga953bc46f95d7b2d8866838d792f8f6aaa5d0d794425327268d08990d26a21f50c"></a><a name="gga953bc46f95d7b2d8866838d792f8f6aaa5d0d794425327268d08990d26a21f50c"></a></strong>TRACK_SOURCE_TYPE_DATA </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p666165779093521"><a name="p666165779093521"></a><a name="p666165779093521"></a>Data track </p>
 </td>
</tr>
<tr id="row303401902093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga953bc46f95d7b2d8866838d792f8f6aaa0fae189aab417f7c9756523f15a20cca"><a name="gga953bc46f95d7b2d8866838d792f8f6aaa0fae189aab417f7c9756523f15a20cca"></a><a name="gga953bc46f95d7b2d8866838d792f8f6aaa0fae189aab417f7c9756523f15a20cca"></a></strong>TRACK_SOURCE_TYPE_INVALID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p957810827093521"><a name="p957810827093521"></a><a name="p957810827093521"></a>Invalid type </p>
 </td>
</tr>
</tbody>
</table>

## TrackType<a name="gad80740dd555f7d3688d2c4d9f44d3b04"></a>

```
enum [TrackType](format.md#gad80740dd555f7d3688d2c4d9f44d3b04)
```

 **Description:**

Enumerates track types. 

<a name="table674253725093521"></a>
<table><thead align="left"><tr id="row1892745297093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2057949081093521"><a name="p2057949081093521"></a><a name="p2057949081093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p504682618093521"><a name="p504682618093521"></a><a name="p504682618093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row141950187093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad80740dd555f7d3688d2c4d9f44d3b04aae00a139d1f3bbfef9dbda6803497b62"><a name="ggad80740dd555f7d3688d2c4d9f44d3b04aae00a139d1f3bbfef9dbda6803497b62"></a><a name="ggad80740dd555f7d3688d2c4d9f44d3b04aae00a139d1f3bbfef9dbda6803497b62"></a></strong>TRACK_TYPE_VIDEO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871227671093521"><a name="p1871227671093521"></a><a name="p1871227671093521"></a>Video track </p>
 </td>
</tr>
<tr id="row1922287066093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad80740dd555f7d3688d2c4d9f44d3b04aab84be45f332c1bd8ab31d9404c6d944"><a name="ggad80740dd555f7d3688d2c4d9f44d3b04aab84be45f332c1bd8ab31d9404c6d944"></a><a name="ggad80740dd555f7d3688d2c4d9f44d3b04aab84be45f332c1bd8ab31d9404c6d944"></a></strong>TRACK_TYPE_AUDIO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p681765589093521"><a name="p681765589093521"></a><a name="p681765589093521"></a>Audio track </p>
 </td>
</tr>
<tr id="row1483349535093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad80740dd555f7d3688d2c4d9f44d3b04a3c834b6afb84a38aa490253a3abc5f66"><a name="ggad80740dd555f7d3688d2c4d9f44d3b04a3c834b6afb84a38aa490253a3abc5f66"></a><a name="ggad80740dd555f7d3688d2c4d9f44d3b04a3c834b6afb84a38aa490253a3abc5f66"></a></strong>TRACK_TYPE_IMAGE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209483762093521"><a name="p1209483762093521"></a><a name="p1209483762093521"></a>Image track </p>
 </td>
</tr>
<tr id="row190291793093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad80740dd555f7d3688d2c4d9f44d3b04aff6cb64c75689ea5b11063e0984956f4"><a name="ggad80740dd555f7d3688d2c4d9f44d3b04aff6cb64c75689ea5b11063e0984956f4"></a><a name="ggad80740dd555f7d3688d2c4d9f44d3b04aff6cb64c75689ea5b11063e0984956f4"></a></strong>TRACK_TYPE_SUB </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p576970682093521"><a name="p576970682093521"></a><a name="p576970682093521"></a>Subtitle track </p>
 </td>
</tr>
<tr id="row528123334093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad80740dd555f7d3688d2c4d9f44d3b04abe0c58f8c0a492959631b8f41dbe2af7"><a name="ggad80740dd555f7d3688d2c4d9f44d3b04abe0c58f8c0a492959631b8f41dbe2af7"></a><a name="ggad80740dd555f7d3688d2c4d9f44d3b04abe0c58f8c0a492959631b8f41dbe2af7"></a></strong>TRACK_TYPE_DATA </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572080364093521"><a name="p572080364093521"></a><a name="p572080364093521"></a>Data track </p>
 </td>
</tr>
<tr id="row1210200829093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad80740dd555f7d3688d2c4d9f44d3b04ad3a1729659a9a6453a2d2bda67cb2c22"><a name="ggad80740dd555f7d3688d2c4d9f44d3b04ad3a1729659a9a6453a2d2bda67cb2c22"></a><a name="ggad80740dd555f7d3688d2c4d9f44d3b04ad3a1729659a9a6453a2d2bda67cb2c22"></a></strong>TRACK_TYPE_BUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140642713093521"><a name="p140642713093521"></a><a name="p140642713093521"></a>Undefined track </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section820948805093521"></a>

## FormatDeInit\(\)<a name="gabb574933ebb4f3d1d2ed299e79aeee2c"></a>

```
void FormatDeInit (void )
```

 **Description:**

Deinitializes the format. 

You can call this function to deinitialize the demuxer and muxer. This function works in pair with  [FormatInit](format.md#gae10a50c8f3de6e54ee0dc3937f755920).

## FormatDemuxerCreate\(\)<a name="ga183fbc31f2c9877ef56464abcccef374"></a>

```
int32_t FormatDemuxerCreate (const [FormatSource](formatsource.md) * source, void ** handle )
```

 **Description:**

Creates a demuxer component and returns its context handle. 

This function returns the demuxer context handle without probing the container format or obtaining stream information.

**Parameters:**

<a name="table903508472093521"></a>
<table><thead align="left"><tr id="row2081201673093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p646955537093521"><a name="p646955537093521"></a><a name="p646955537093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1342044817093521"><a name="p1342044817093521"></a><a name="p1342044817093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row774244071093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">source</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the format source of the demuxer. For details, see <a href="formatsource.md">FormatSource</a>. </td>
</tr>
<tr id="row253113825093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the demuxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerDestory\(\)<a name="ga98fd9a5a5d1ffd275fc46f898ca08413"></a>

```
int32_t FormatDemuxerDestory (void * handle)
```

 **Description:**

Destroys demuxer resources. 

This function works in pair with  [FormatDemuxerCreate](format.md#ga183fbc31f2c9877ef56464abcccef374). If you do not call this function, resource leakage may occur.

**Parameters:**

<a name="table618996537093521"></a>
<table><thead align="left"><tr id="row2003564781093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p436641008093521"><a name="p436641008093521"></a><a name="p436641008093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1629568207093521"><a name="p1629568207093521"></a><a name="p1629568207093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1179224034093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerFreeFrame\(\)<a name="ga291b805de194c695b72eb5ad721103d5"></a>

```
int32_t FormatDemuxerFreeFrame (void * handle, [FormatFrame](formatframe.md) * frame )
```

 **Description:**

Frees data frames. 

You can call this function to free the data frames obtained by calling  [FormatDemuxerReadFrame](format.md#ga7b20e1b88413d20a348d7f796917cd94).

**Parameters:**

<a name="table420248842093521"></a>
<table><thead align="left"><tr id="row1564451630093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p469401256093521"><a name="p469401256093521"></a><a name="p469401256093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1628269329093521"><a name="p1628269329093521"></a><a name="p1628269329093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1054859146093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row544531747093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frame</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data structure <a href="formatframe.md">FormatFrame</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerGetBufferConfig\(\)<a name="ga565cbb52c95a95aab4dcc957fe998b5f"></a>

```
int32_t FormatDemuxerGetBufferConfig (const void * handle, [FormatBufferSetting](formatbuffersetting.md) * setting )
```

 **Description:**

Obtains the buffer information of the demuxer. 

If there is a buffer mechanism in the demuxer, you can call this function to obtain the maximum buffer size and time.

**Parameters:**

<a name="table905200657093521"></a>
<table><thead align="left"><tr id="row1829403889093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1813619492093521"><a name="p1813619492093521"></a><a name="p1813619492093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1197733245093521"><a name="p1197733245093521"></a><a name="p1197733245093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1076818207093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row1680407064093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">setting</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the maximum demuxer buffer size and time, as defined in <a href="formatbuffersetting.md">FormatBufferSetting</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerGetFileInfo\(\)<a name="gad807d61c65e89629c7eed8f97426fd5a"></a>

```
int32_t FormatDemuxerGetFileInfo (void * handle, [FileInfo](fileinfo.md) * info )
```

 **Description:**

Obtains the attributes of a media file. 

The attributes contain file, program, and stream attributes. This function should be called after  [FormatDemuxerPrepare](format.md#gacfcf40d869a48125bd67d17f8a4fc3ce)  is called.

**Parameters:**

<a name="table610798607093521"></a>
<table><thead align="left"><tr id="row1658936772093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p538384659093521"><a name="p538384659093521"></a><a name="p538384659093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1307434399093521"><a name="p1307434399093521"></a><a name="p1307434399093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row106529412093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row323668174093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the source attributes, as defined in <a href="fileinfo.md">FileInfo</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerGetParameter\(\)<a name="ga6c2a1aa9fdf1db8e2f14a3a92ffa23d5"></a>

```
int32_t FormatDemuxerGetParameter (const void * handle, int32_t trackId, [ParameterItem](parameteritem.md) * metaData )
```

 **Description:**

Obtains demuxer attributes. 

You can call this function to obtain the HTTP header, HTTP referer, and other extension items for the demuxer after  [FormatDemuxerCreate](format.md#ga183fbc31f2c9877ef56464abcccef374)  is called. The demuxer will store the value in the  **metaData**  based on the key.If the demuxer has allocated memory for the  **metaData**  to store the value, the caller should manually free the memory.

**Parameters:**

<a name="table222394511093521"></a>
<table><thead align="left"><tr id="row1063373121093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1353297617093521"><a name="p1353297617093521"></a><a name="p1353297617093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p896443166093521"><a name="p896443166093521"></a><a name="p896443166093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1309599707093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row1691491931093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the track. If the value is an invalid value (<strong id="b1129925489093521"><a name="b1129925489093521"></a><a name="b1129925489093521"></a>-1</strong>), this parameter identifies the file or program. </td>
</tr>
<tr id="row548928144093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">metaData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the parameters values that the demuxer has searched for based on the input key. For details, see <a href="parameteritem.md">ParameterItem</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerGetSelectedTrack\(\)<a name="gab6ef68051ee2ed0015e721bedb1af61c"></a>

```
int32_t FormatDemuxerGetSelectedTrack (const void * handle, int32_t * programId, int32_t trackId[], int32_t * nums )
```

 **Description:**

Obtains the ID of the media track selected by the demuxer for output. 

The demuxer automatically selects the default program and its media tracks. However, if the program and media tracks have changed after  [FormatDemuxerSelectTrack](format.md#ga1d9cb94614e207def34f13eaa16ef2b7)  and  [FormatDemuxerUnselectTrack](format.md#gaf5fd5bab9613d133827054f157d5520e)  are called, you can obtain the currently selected program and media tracks by calling this function \(**FormatDemuxerGetSelectedTrack**.

**Parameters:**

<a name="table2009069363093521"></a>
<table><thead align="left"><tr id="row187318541093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p36423678093521"><a name="p36423678093521"></a><a name="p36423678093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1584917809093521"><a name="p1584917809093521"></a><a name="p1584917809093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row63976565093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row2111989750093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">programId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the pointer to the program. </td>
</tr>
<tr id="row1882217386093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the array of selected media tracks. This parameter works in pair with <strong id="b1226444471093521"><a name="b1226444471093521"></a><a name="b1226444471093521"></a>nums</strong>. </td>
</tr>
<tr id="row1813159984093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nums</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the total number of selected media tracks. This parameter works in pair with <strong id="b1354223737093521"><a name="b1354223737093521"></a><a name="b1354223737093521"></a>trackId</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerPrepare\(\)<a name="gacfcf40d869a48125bd67d17f8a4fc3ce"></a>

```
int32_t FormatDemuxerPrepare (void * handle)
```

 **Description:**

Makes preparations for the demuxer. 

This function triggers the demuxer to probe the media file container format and parse stream information. You can obtain media file attributes only after this function is called.

**Parameters:**

<a name="table1909333750093521"></a>
<table><thead align="left"><tr id="row1258043956093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p212297568093521"><a name="p212297568093521"></a><a name="p212297568093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1627796086093521"><a name="p1627796086093521"></a><a name="p1627796086093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1224727419093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerReadFrame\(\)<a name="ga7b20e1b88413d20a348d7f796917cd94"></a>

```
int32_t FormatDemuxerReadFrame (const void * handle, [FormatFrame](formatframe.md) * frame, int32_t timeOutMs )
```

 **Description:**

Reads data frames. 

After the data frames are read, you need to call  **FormatDemuxerFreeFame**  to free them.

**Parameters:**

<a name="table142168173093521"></a>
<table><thead align="left"><tr id="row1461813216093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p745043148093521"><a name="p745043148093521"></a><a name="p745043148093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1620522714093521"><a name="p1620522714093521"></a><a name="p1620522714093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1176443378093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row175602781093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frame</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data structure <a href="formatframe.md">FormatFrame</a>. </td>
</tr>
<tr id="row393216243093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOutMs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the time required for waiting data frame read. The value <strong id="b1455491238093521"><a name="b1455491238093521"></a><a name="b1455491238093521"></a>0</strong> indicates that data frames are immediately read without any wait. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerSeek\(\)<a name="gad53f1e848f3c2e0c8fa056a312b2ed6c"></a>

```
int32_t FormatDemuxerSeek (const void * handle, int32_t streamIndex, int64_t timeStampUs, [FormatSeekMode](format.md#ga14aa9d18a71eff4a0b70f748f0377c94) mode )
```

 **Description:**

Seeks for a specified position for the demuxer. 

After being started, the demuxer seeks for a specified position to read data frames. You can specify the position close to the time specified by  **streamIndex**.

**Parameters:**

<a name="table1707705507093521"></a>
<table><thead align="left"><tr id="row546524079093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1809222127093521"><a name="p1809222127093521"></a><a name="p1809222127093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1820561013093521"><a name="p1820561013093521"></a><a name="p1820561013093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row772313307093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row1864622593093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">streamIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the stream in the media file. </td>
</tr>
<tr id="row209380853093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeStampUs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target position, in microseconds. </td>
</tr>
<tr id="row1067525581093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the seek mode, as defined in <a href="format.md#ga14aa9d18a71eff4a0b70f748f0377c94">FormatSeekMode</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerSelectTrack\(\)<a name="ga1d9cb94614e207def34f13eaa16ef2b7"></a>

```
int32_t FormatDemuxerSelectTrack (const void * handle, int32_t programId, int32_t trackId )
```

 **Description:**

Selects a specified media track. 

The media tracks to select must belong to the same program. If you do not call this function, the default media tracks of the default program are selected. If  **programId**  is valid but  **trackId**  is invalid, the default media track of the specified program is used.

**Parameters:**

<a name="table1576752950093521"></a>
<table><thead align="left"><tr id="row1757970985093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p598499828093521"><a name="p598499828093521"></a><a name="p598499828093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1843588570093521"><a name="p1843588570093521"></a><a name="p1843588570093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row690881194093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row449824731093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">programId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the program. </td>
</tr>
<tr id="row1299496694093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the media track. If a valid value is passed, the media track must belong to the specified program. If an invalid value is passed, the default media track of the specified program is used. If multiple audio tracks are specified, the player determines which audio track to use. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerSetBufferConfig\(\)<a name="gad2a15f3fa640f3f9e8e684d71b3a12cb"></a>

```
int32_t FormatDemuxerSetBufferConfig (void * handle, const [FormatBufferSetting](formatbuffersetting.md) * setting )
```

 **Description:**

Sets buffer information for the demuxer. 

If there is a buffer mechanism in the demuxer, you can call this function to set the maximum buffer size and time. Alternatively, you can disable the buffer mechanism by setting the buffer size and time to  **0**  in the  **setting**  parameter. If there is no buffer mechanism or the default setting is retained, you can skip this function.

**Parameters:**

<a name="table582699172093521"></a>
<table><thead align="left"><tr id="row387097499093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p773708452093521"><a name="p773708452093521"></a><a name="p773708452093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p849426307093521"><a name="p849426307093521"></a><a name="p849426307093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row320941209093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row1190675639093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">setting</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the maximum demuxer buffer size and time, as defined in <a href="formatbuffersetting.md">FormatBufferSetting</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerSetCallBack\(\)<a name="ga9ef126fc3132b556d49a275799e7753b"></a>

```
int32_t FormatDemuxerSetCallBack (void * handle, const [FormatCallback](formatcallback.md) * callBack )
```

 **Description:**

Sets a callback for the demuxer. 

The callback will be invoked to notify the upper layer of internal events of the demuxer.

**Parameters:**

<a name="table1705403403093521"></a>
<table><thead align="left"><tr id="row1731354315093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1814793033093521"><a name="p1814793033093521"></a><a name="p1814793033093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p36906236093521"><a name="p36906236093521"></a><a name="p36906236093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1232371777093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row230507732093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">callBack</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the callback, as defined in <a href="formatcallback.md">FormatCallback</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerSetParameter\(\)<a name="ga92d859ba4745ce26b94595daaa40462d"></a>

```
int32_t FormatDemuxerSetParameter (const void * handle, int32_t trackId, const [ParameterItem](parameteritem.md) * metaData, int32_t metaDataCnt )
```

 **Description:**

Sets demuxer attributes. 

You can call this function to set the HTTP header, HTTP referer, and other extension items for the demuxer after  [FormatDemuxerCreate](format.md#ga183fbc31f2c9877ef56464abcccef374)  is called.

**Parameters:**

<a name="table2142454451093521"></a>
<table><thead align="left"><tr id="row1598288618093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p836161466093521"><a name="p836161466093521"></a><a name="p836161466093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1471754921093521"><a name="p1471754921093521"></a><a name="p1471754921093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row869253735093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row1605439720093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the track. If the value is an invalid value (<strong id="b305790532093521"><a name="b305790532093521"></a><a name="b305790532093521"></a>-1</strong>), this parameter identifies the file or program. </td>
</tr>
<tr id="row604154816093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">metaData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to an array of key-value pairs representing parameter names and values. For details, see <a href="parameteritem.md">ParameterItem</a>. </td>
</tr>
<tr id="row1810194904093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">metaDataCnt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of key-value pairs in the array. This parameter works in pair with <strong id="b1864258358093521"><a name="b1864258358093521"></a><a name="b1864258358093521"></a>metaData</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerStart\(\)<a name="ga08544b1ba3373bf5cb211586e8195673"></a>

```
int32_t FormatDemuxerStart (void * handle)
```

 **Description:**

Starts the demuxer. 

After being started, the caller can read data frames from the demuxer. This function should be called after  [FormatDemuxerPrepare](format.md#gacfcf40d869a48125bd67d17f8a4fc3ce)  is called.

**Parameters:**

<a name="table86396872093521"></a>
<table><thead align="left"><tr id="row1322053758093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1959406771093521"><a name="p1959406771093521"></a><a name="p1959406771093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1254408359093521"><a name="p1254408359093521"></a><a name="p1254408359093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1956217074093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerStop\(\)<a name="ga8a693d8be0b4b688d99e513608884e91"></a>

```
int32_t FormatDemuxerStop (void * handle)
```

 **Description:**

Stops the demuxer from working. 

After this function is called, the demuxer cannot resume decapsulation.

**Parameters:**

<a name="table1885182939093521"></a>
<table><thead align="left"><tr id="row945193171093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1300333337093521"><a name="p1300333337093521"></a><a name="p1300333337093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p742285199093521"><a name="p742285199093521"></a><a name="p742285199093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row51553721093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatDemuxerUnselectTrack\(\)<a name="gaf5fd5bab9613d133827054f157d5520e"></a>

```
int32_t FormatDemuxerUnselectTrack (const void * handle, int32_t programId, int32_t trackId )
```

 **Description:**

Unselects a specified media track from which the demuxer reads data frames. 

The demuxer can read all media tracks of the default program. You can call this function to unselect all or certain tracks of a specified program that the demuxer is expected not to read. If  **trackId**  is invalid, the demuxer will read none of the tracks of the specified program.

**Parameters:**

<a name="table563886415093521"></a>
<table><thead align="left"><tr id="row143205687093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p983760709093521"><a name="p983760709093521"></a><a name="p983760709093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p730938207093521"><a name="p730938207093521"></a><a name="p730938207093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1316106637093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the demuxer context handle. </td>
</tr>
<tr id="row165090765093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">programId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the program. </td>
</tr>
<tr id="row549662481093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the media track that the demuxer will unselect. This parameter works in pair with <strong id="b898973719093521"><a name="b898973719093521"></a><a name="b898973719093521"></a>programId</strong>. If a valid value is passed, the media track must belong to the program specified by <strong id="b1163308561093521"><a name="b1163308561093521"></a><a name="b1163308561093521"></a>programId</strong>. If an invalid value is passed, and all media tracks of the specified program are unselected. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatInit\(\)<a name="gae10a50c8f3de6e54ee0dc3937f755920"></a>

```
void FormatInit (void )
```

 **Description:**

Initializes the format. 

You can call this function to initialize the demuxer and muxer. This function should always be called before other format-specific functions, and it can be called only once within a process.

## FormatMuxerAddTrack\(\)<a name="ga94e9ab3e534b69a358b7cc16e4f79b78"></a>

```
int32_t FormatMuxerAddTrack (void * handle, const [TrackSource](tracksource.md) * trackSource )
```

 **Description:**

Adds a media track source for the muxer. For details about track sources, see  [TrackSource](tracksource.md). 

This function must be called after  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad)  is successfully called and before  [FormatMuxerStart](format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b)  is called.

**Parameters:**

<a name="table1228496829093521"></a>
<table><thead align="left"><tr id="row307039005093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2056716226093521"><a name="p2056716226093521"></a><a name="p2056716226093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1556510704093521"><a name="p1556510704093521"></a><a name="p1556510704093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row350111152093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row796634555093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackSource</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the track source. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerCreate\(\)<a name="ga9c390276cb90f4753c32af5aa5c600ad"></a>

```
int32_t FormatMuxerCreate (void ** handle, [FormatOutputConfig](formatoutputconfig.md) * outputConfig )
```

 **Description:**

Creates a muxer and returns its context handle. 

**Parameters:**

<a name="table1635625006093521"></a>
<table><thead align="left"><tr id="row513172560093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p594078721093521"><a name="p594078721093521"></a><a name="p594078721093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1205638004093521"><a name="p1205638004093521"></a><a name="p1205638004093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1146849950093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the muxer context handle. </td>
</tr>
<tr id="row1144722840093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">outputConfig</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer output configuration, as defined in <a href="formatoutputconfig.md">FormatOutputConfig</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerDestory\(\)<a name="gaa41d46cef6d5e81c85614edbf824d803"></a>

```
int32_t FormatMuxerDestory (const void * handle)
```

 **Description:**

Destroys a muxer and release its resources created by calling  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad). 

**Parameters:**

<a name="table1818608399093521"></a>
<table><thead align="left"><tr id="row1059922786093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1037934378093521"><a name="p1037934378093521"></a><a name="p1037934378093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2056456973093521"><a name="p2056456973093521"></a><a name="p2056456973093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2109920811093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerGetParameter\(\)<a name="ga67dd7361dedf335496afef19d54e4138"></a>

```
int32_t FormatMuxerGetParameter (void * handle, int32_t trackId, [ParameterItem](parameteritem.md) * item, int32_t itemNum )
```

 **Description:**

Obtains muxer attributes. 

This is an extended function that can be used to obtain muxer or track attributes. The demuxer then obtains the muxer attributes based on the key contained in  **item**.

**Parameters:**

<a name="table511495710093521"></a>
<table><thead align="left"><tr id="row1253132050093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1994365580093521"><a name="p1994365580093521"></a><a name="p1994365580093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2079592545093521"><a name="p2079592545093521"></a><a name="p2079592545093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2074663183093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row1476381890093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the media track. If the value is <a href="format.md#ga62037bb16334896e1bb6d35a71618881">FORMAT_INVALID_TRACK_ID</a>, this function obtains the muxer attributes. </td>
</tr>
<tr id="row742812185093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">item</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the items carrying muxer attributes. You can specify multiple items at a time in this parameter, which works in pair with <strong id="b1143205717093521"><a name="b1143205717093521"></a><a name="b1143205717093521"></a>itemNum</strong>. </td>
</tr>
<tr id="row1694976947093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">itemNum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of attributes set at a time. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value if any requested attribute fails to be obtained or is not found. 



## FormatMuxerSetCallBack\(\)<a name="ga108cd7e319ade568f71890d57585f153"></a>

```
int32_t FormatMuxerSetCallBack (void * handle, const [FormatCallback](formatcallback.md) * callBack )
```

 **Description:**

Sets a callback for the muxer. For details about the callback, see  [FormatCallback](formatcallback.md). 

This function should be called after  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad)  is successfully called.

**Parameters:**

<a name="table2036908084093521"></a>
<table><thead align="left"><tr id="row1219082513093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1741583344093521"><a name="p1741583344093521"></a><a name="p1741583344093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1729757828093521"><a name="p1729757828093521"></a><a name="p1729757828093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1410778355093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row141731826093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><a href="formatcallback.md">FormatCallback</a></td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer callback to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetFileSplitDuration\(\)<a name="ga6eed6b5e7522e102f2d79d0dd33fd2a9"></a>

```
int32_t FormatMuxerSetFileSplitDuration (const void * handle, [ManualSplitType](format.md#ga10d9833450f29129d249c41d9acb4bc4) type, int64_t timestampUs, uint32_t durationUs )
```

 **Description:**

Manually splits a file. 

This function can be called after  [FormatMuxerStart](format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b)  is called. Once this function is called, the file is split based on the manual split type. After manual split is complete, file split will proceed to use the initially set split type. You can call this function again only after the  [MUXER\_INFO\_FILE\_SPLIT\_FINISHED](format.md#gga6f00342925d3d5e586c76f8695985cada3cf56a06f5990ab657d61bd7e57c1783)  event is reported.

**Parameters:**

<a name="table321022873093521"></a>
<table><thead align="left"><tr id="row983058427093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p503082523093521"><a name="p503082523093521"></a><a name="p503082523093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1465417157093521"><a name="p1465417157093521"></a><a name="p1465417157093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row673875171093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row2142075788093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file split type, as defined in <strong id="b1289302831093521"><a name="b1289302831093521"></a><a name="b1289302831093521"></a>FileSplitType</strong>. </td>
</tr>
<tr id="row1218065118093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timestamp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file split timestamp. This parameter is not supported currently. The value <strong id="b556340058093521"><a name="b556340058093521"></a><a name="b556340058093521"></a>�C1</strong> indicates that the file is split at the time this function is called. </td>
</tr>
<tr id="row1343763417093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">duration</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the period from the file split time to the time the next output file starts. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetLocation\(\)<a name="ga967ba14fa1231eed2942b87a09deb953"></a>

```
int32_t FormatMuxerSetLocation (const void * handle, int latitude, int longitude )
```

 **Description:**

Sets the geographical information for the output file of the muxer. 

This function should be called after  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad)  is successfully called.

**Parameters:**

<a name="table643021851093521"></a>
<table><thead align="left"><tr id="row971599791093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p679255550093521"><a name="p679255550093521"></a><a name="p679255550093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1631607735093521"><a name="p1631607735093521"></a><a name="p1631607735093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1798240557093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row1141781246093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">latitude</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the latitude, within the range [-90,90]. </td>
</tr>
<tr id="row1816025769093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">longitude</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the longitude, within the range [-180,180]. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetMaxFileDuration\(\)<a name="gae931061d822c4ffe447e9ba40a991597"></a>

```
int32_t FormatMuxerSetMaxFileDuration (void * handle, int64_t durationUs )
```

 **Description:**

Sets the maximum duration \(in seconds\) for the output file. 

You need to call this function before calling  [FormatMuxerStart](format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b). If the maximum duration you set is valid and capturing is approaching 90% of that duration or the remaining duration is 1s, the message  [MUXER\_INFO\_MAX\_DURATION\_APPROACHING](format.md#gga6f00342925d3d5e586c76f8695985cadaf6214216fd62faa4fc5e20d0d0ba60bf)  is reported via  **OnInfo**  of  [FormatCallback](formatcallback.md). If the output file has been set by calling  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad), you need to call  [FormatMuxerSetNextOutputFile](format.md#gaa936b56996294d76977537267fef058c)  to set the next output file. Otherwise, the current output file will be overwritten when the capturing reaches the maximum duration you set.

**Parameters:**

<a name="table765949930093521"></a>
<table><thead align="left"><tr id="row875063661093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p253110482093521"><a name="p253110482093521"></a><a name="p253110482093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1787627792093521"><a name="p1787627792093521"></a><a name="p1787627792093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row13207541093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row611550830093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">duration</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum duration to set, in seconds. If the value is <strong id="b2054127657093521"><a name="b2054127657093521"></a><a name="b2054127657093521"></a>0</strong> or negative, the operation fails. In this case, the default duration (60 seconds) will be used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetMaxFileSize\(\)<a name="ga6f3ba422c9bbca4c1d5a7a3fe85dd9b9"></a>

```
int32_t FormatMuxerSetMaxFileSize (void * handle, int64_t bytes )
```

 **Description:**

Sets the maximum size \(in bytes\) for the output file of the muxer. 

This function should be called after  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad)  is successfully called.

**Parameters:**

<a name="table2094637839093521"></a>
<table><thead align="left"><tr id="row1492776530093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p970918027093521"><a name="p970918027093521"></a><a name="p970918027093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1829474965093521"><a name="p1829474965093521"></a><a name="p1829474965093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1520856586093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row479514251093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bytes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum size of a file, in bytes. If the value is <strong id="b1906363215093521"><a name="b1906363215093521"></a><a name="b1906363215093521"></a>0</strong> or negative, the operation fails and the maximum size does not take effect. In this case, the maximum size of a single file supported by the current file system is used as the value of this parameter. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetNextOutputFile\(\)<a name="gaa936b56996294d76977537267fef058c"></a>

```
int32_t FormatMuxerSetNextOutputFile (const void * handle, int32_t fd )
```

 **Description:**

Sets the descriptor for the next output file. 

If  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad)  is successfully called and the file descriptor involved is valid, you can call this function \(**FormatMuxerSetNextOutputFile**\) upon receiving the message  [MUXER\_INFO\_MAX\_FILESIZE\_APPROACHING](format.md#gga6f00342925d3d5e586c76f8695985cadafc74f41e73f13a29a83b3a13ea6e66e1)  or  [MUXER\_INFO\_MAX\_DURATION\_APPROACHING](format.md#gga6f00342925d3d5e586c76f8695985cadaf6214216fd62faa4fc5e20d0d0ba60bf).

**Parameters:**

<a name="table1628553210093521"></a>
<table><thead align="left"><tr id="row599892512093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1446641828093521"><a name="p1446641828093521"></a><a name="p1446641828093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1207360919093521"><a name="p1207360919093521"></a><a name="p1207360919093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row469866897093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row1733651160093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetOrientation\(\)<a name="ga96fc57913c3202d2d23704c69d660be5"></a>

```
int32_t FormatMuxerSetOrientation (void * handle, int degrees )
```

 **Description:**

Sets the orientation of the video track for the muxer. 

This function should be called after  [FormatMuxerAddTrack](format.md#ga94e9ab3e534b69a358b7cc16e4f79b78)  is successfully called. The following degrees are supported: 0, 90, 180, and 270.

**Parameters:**

<a name="table1730451498093521"></a>
<table><thead align="left"><tr id="row825094109093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1707875236093521"><a name="p1707875236093521"></a><a name="p1707875236093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p847160608093521"><a name="p847160608093521"></a><a name="p847160608093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row53794740093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row1256147855093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">degrees</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the clockwise angle of the video track. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerSetParameter\(\)<a name="gad4335ebaa7c165b885a00fe61aae0cd9"></a>

```
int32_t FormatMuxerSetParameter (void * handle, int32_t trackId, const [ParameterItem](parameteritem.md) * item, int32_t itemNum )
```

 **Description:**

Sets muxer attributes. 

This is an extended function that can be used to add MP4-dedicated boxes and tags \(such as  **exif**\).

**Parameters:**

<a name="table1055756941093521"></a>
<table><thead align="left"><tr id="row197173739093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p993072037093521"><a name="p993072037093521"></a><a name="p993072037093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p457848852093521"><a name="p457848852093521"></a><a name="p457848852093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row803478731093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row1754490102093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">trackId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the media track. If the value is <a href="format.md#ga62037bb16334896e1bb6d35a71618881">FORMAT_INVALID_TRACK_ID</a>, this function sets the muxer attributes. </td>
</tr>
<tr id="row598846850093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">item</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the items carrying muxer attributes. You can specify multiple items at a time in this parameter, which works in pair with <strong id="b273674747093521"><a name="b273674747093521"></a><a name="b273674747093521"></a>itemNum</strong>. </td>
</tr>
<tr id="row1594883835093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">itemNum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of attributes set at a time. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerStart\(\)<a name="ga9a2af831a6f4a63dc85d2c23b5c7c81b"></a>

```
int32_t FormatMuxerStart (void * handle)
```

 **Description:**

Starts the muxer. 

You can call this function to encapsulate media data after the muxer is created, media tracks are added, and related parameters are set.

**Parameters:**

<a name="table1793533263093521"></a>
<table><thead align="left"><tr id="row1436229310093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2084861128093521"><a name="p2084861128093521"></a><a name="p2084861128093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2086156535093521"><a name="p2086156535093521"></a><a name="p2086156535093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row847430936093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerStop\(\)<a name="ga66a3a5a1ec6d01fcbd6339f7eee1151b"></a>

```
int32_t FormatMuxerStop (const void * handle, bool block )
```

 **Description:**

Stops the muxer that was started by calling  [FormatMuxerStart](format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b). 

**Parameters:**

<a name="table111029770093521"></a>
<table><thead align="left"><tr id="row1534923412093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p914048312093521"><a name="p914048312093521"></a><a name="p914048312093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1327723944093521"><a name="p1327723944093521"></a><a name="p1327723944093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1109495250093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row634009895093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">block</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates how to stop the muxer. The value <strong id="b176316962093521"><a name="b176316962093521"></a><a name="b176316962093521"></a>true</strong> indicates that the muxer is stopped after all buffered data is processed, and <strong id="b232082587093521"><a name="b232082587093521"></a><a name="b232082587093521"></a>false</strong> indicates that the buffered data is discarded and the muxer is immediately stopped. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## FormatMuxerWriteFrame\(\)<a name="ga82037d271e77da206e16582e774ee048"></a>

```
int32_t FormatMuxerWriteFrame (const void * handle, const [FormatFrame](formatframe.md) * frameData )
```

 **Description:**

Writes data frames into the muxer. 

This function should be called after  [FormatMuxerCreate](format.md#ga9c390276cb90f4753c32af5aa5c600ad)  is successfully called.

**Parameters:**

<a name="table1490466188093521"></a>
<table><thead align="left"><tr id="row1609620565093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1835437629093521"><a name="p1835437629093521"></a><a name="p1835437629093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p444628819093521"><a name="p444628819093521"></a><a name="p444628819093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1095595979093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the muxer context handle. </td>
</tr>
<tr id="row1972668650093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frameData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data structure <a href="formatframe.md">FormatFrame</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



