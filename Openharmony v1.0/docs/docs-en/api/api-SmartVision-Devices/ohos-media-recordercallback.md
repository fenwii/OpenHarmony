# OHOS::Media::RecorderCallback<a name="EN-US_TOPIC_0000001055078155"></a>

## **Overview**<a name="section968353643093532"></a>

**Related Modules:**

[MultiMedia\_Recorder](multimedia_recorder.md)

**Description:**

Provides listeners for recording errors and information events. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1813437046093532"></a>

## Public Types<a name="pub-types"></a>

<a name="table1032254018093532"></a>
<table><thead align="left"><tr id="row51456326093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1493995875093532"><a name="p1493995875093532"></a><a name="p1493995875093532"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1661704413093532"><a name="p1661704413093532"></a><a name="p1661704413093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1579989538093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p862931213093532"><a name="p862931213093532"></a><a name="p862931213093532"></a><a href="multimedia_recorder.md#ga0db5cf9cc68d4b468e921a563248ffe0">RecorderInfoType</a> : int32_t {   <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0af47b2244ca5d4a906657ace804c62ab5">RECORDER_INFO_MAX_DURATION_APPROACHING</a> = 0, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0ace19eeffeb7bfd809c0eecd831dfc4c8">RECORDER_INFO_MAX_FILESIZE_APPROACHING</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0aa67fb963e882f4e45405e52a525d617e">RECORDER_INFO_MAX_DURATION_REACHED</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0ad33be678eb5f4ec5c5db92d324ec0b27">RECORDER_INFO_MAX_FILESIZE_REACHED</a>,   <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0ae27acecf4dec639f993091e2b4983d99">RECORDER_INFO_NEXT_OUTPUT_FILE_STARTED</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0a0a2e4851229314e2d019b7418a13ce82">RECORDER_INFO_FILE_SPLIT_FINISHED</a>, <a href="multimedia_recorder.md#gga0db5cf9cc68d4b468e921a563248ffe0abd5ed874b180a67a39c0edaa83a9e4d5">RECORDER_INFO_FILE_START_TIME_MS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1982573338093532"><a name="p1982573338093532"></a><a name="p1982573338093532"></a>Enumerates recording information types. </p>
</td>
</tr>
<tr id="row1474918733093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1588399266093532"><a name="p1588399266093532"></a><a name="p1588399266093532"></a><a href="multimedia_recorder.md#ga5132172c298fc1497d12040b6bd511cf">RecorderErrorType</a> : int32_t { <a href="multimedia_recorder.md#gga5132172c298fc1497d12040b6bd511cfa0e5cc2daf43191929754b01659128d79">RECORDER_ERROR_UNKNOWN</a> = 0 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1356198941093532"><a name="p1356198941093532"></a><a name="p1356198941093532"></a>Enumerates recording error types. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1217068578093532"></a>
<table><thead align="left"><tr id="row520248573093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1820897863093532"><a name="p1820897863093532"></a><a name="p1820897863093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1476141329093532"><a name="p1476141329093532"></a><a name="p1476141329093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row832564524093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p71832540093532"><a name="p71832540093532"></a><a name="p71832540093532"></a><a href="multimedia_recorder.md#ga822c915f1bfab8c380919f24f2ee4f54">OnError</a> (int32_t errorType, int32_t errorCode)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p828046576093532"><a name="p828046576093532"></a><a name="p828046576093532"></a>virtual void </p>
<p id="p1219123514093532"><a name="p1219123514093532"></a><a name="p1219123514093532"></a>Called when an error occurs during recording. This callback is used to report recording errors. </p>
</td>
</tr>
<tr id="row721137417093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1610441009093532"><a name="p1610441009093532"></a><a name="p1610441009093532"></a><a href="multimedia_recorder.md#gac1f8bb191d90aac50119ea7ae4108407">OnInfo</a> (int32_t type, int32_t extra)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918975100093532"><a name="p1918975100093532"></a><a name="p1918975100093532"></a>virtual void </p>
<p id="p1938686582093532"><a name="p1938686582093532"></a><a name="p1938686582093532"></a>Called when an information event occurs during recording. This callback is used to report recording information. </p>
</td>
</tr>
</tbody>
</table>

