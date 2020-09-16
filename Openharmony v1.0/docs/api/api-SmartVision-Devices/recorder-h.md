# recorder.h<a name="ZH-CN_TOPIC_0000001054479541"></a>

## **Overview**<a name="section1679889952093527"></a>

**Related Modules:**

[MultiMedia\_Recorder](MultiMedia_Recorder.md)

**Description:**

Declares the  **Recorder**  class for audio and video recording. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1156184171093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table220530568093527"></a>
<table><thead align="left"><tr id="row1605377126093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1472239587093527"><a name="p1472239587093527"></a><a name="p1472239587093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1164107257093527"><a name="p1164107257093527"></a><a name="p1164107257093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row717727843093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p513355808093527"><a name="p513355808093527"></a><a name="p513355808093527"></a><a href="OHOS-Media-RecorderCallback.md">OHOS::Media::RecorderCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416659442093527"><a name="p416659442093527"></a><a name="p416659442093527"></a>Provides listeners for recording errors and information events. </p>
</td>
</tr>
<tr id="row377929857093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946350653093527"><a name="p946350653093527"></a><a name="p946350653093527"></a><a href="OHOS-Media-Recorder.md">OHOS::Media::Recorder</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1981212427093527"><a name="p1981212427093527"></a><a name="p1981212427093527"></a>Provides functions for audio and video recording. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1877764910093527"></a>
<table><thead align="left"><tr id="row476515626093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1189525788093527"><a name="p1189525788093527"></a><a name="p1189525788093527"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1207567795093527"><a name="p1207567795093527"></a><a name="p1207567795093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1107530473093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522208532093527"><a name="p1522208532093527"></a><a name="p1522208532093527"></a><a href="MultiMedia_Recorder.md#gad252d27f9ce4b6ae0756bfeaa5f34490">OHOS::Media::VideoSourceType</a> : int32_t { <a href="MultiMedia_Recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490ad137c55cd463c87ff8ea66c116da2e57">OHOS::Media::VIDEO_SOURCE_SURFACE_YUV</a> = 0, <a href="MultiMedia_Recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490afcca9aba53005db99434c74f62803d6d">OHOS::Media::VIDEO_SOURCE_SURFACE_RGB</a>, <a href="MultiMedia_Recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490a9316951d19d2ed845d2c0ef92c541eb8">OHOS::Media::VIDEO_SOURCE_SURFACE_ES</a>, <a href="MultiMedia_Recorder.md#ggad252d27f9ce4b6ae0756bfeaa5f34490af19a30a10d95948a7dab0317a4e2447b">OHOS::Media::VIDEO_SOURCE_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638836144093527"><a name="p1638836144093527"></a><a name="p1638836144093527"></a>Enumerates video source types. </p>
</td>
</tr>
<tr id="row2046666134093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p10191372093527"><a name="p10191372093527"></a><a name="p10191372093527"></a><a href="MultiMedia_Recorder.md#gaccc05bb178cecd760369ea096dceae4c">OHOS::Media::DataSourceType</a> : int32_t { <a href="MultiMedia_Recorder.md#ggaccc05bb178cecd760369ea096dceae4ca18ab16c027cd6de93c4e64be806caed0">OHOS::Media::IMAGE</a> = 0 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1624917631093527"><a name="p1624917631093527"></a><a name="p1624917631093527"></a>Enumerates data source types. </p>
</td>
</tr>
<tr id="row86848911093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685857601093527"><a name="p1685857601093527"></a><a name="p1685857601093527"></a><a href="MultiMedia_Recorder.md#ga3dfe2e61369bf1c081ce569e235354df">OHOS::Media::OutputFormatType</a> : int32_t { <a href="MultiMedia_Recorder.md#gga3dfe2e61369bf1c081ce569e235354dfa5f2bb1abd7404320dcd46e7540a22586">OHOS::Media::FORMAT_DEFAULT</a> = 0, <a href="MultiMedia_Recorder.md#gga3dfe2e61369bf1c081ce569e235354dfac7e010e743dca6fc60780bb745707d57">OHOS::Media::FORMAT_MPEG_4</a>, <a href="MultiMedia_Recorder.md#gga3dfe2e61369bf1c081ce569e235354dfa2abf22281e8d5a30da1f0700d9bf45a3">OHOS::Media::FORMAT_TS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144724507093527"><a name="p2144724507093527"></a><a name="p2144724507093527"></a>Enumerates output file formats. </p>
</td>
</tr>
<tr id="row151412647093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1439887322093527"><a name="p1439887322093527"></a><a name="p1439887322093527"></a><a href="MultiMedia_Recorder.md#ga8759c7e5a74964a584a716f4ec0b7edb">OHOS::Media::FileSplitType</a> : int32_t { <a href="MultiMedia_Recorder.md#gga8759c7e5a74964a584a716f4ec0b7edba9010fd43e012d61772ff5db3a9bdaf02">OHOS::Media::FILE_SPLIT_POST</a> = 0, <a href="MultiMedia_Recorder.md#gga8759c7e5a74964a584a716f4ec0b7edba01981748b792c27773467ea70099be65">OHOS::Media::FILE_SPLIT_PRE</a>, <a href="MultiMedia_Recorder.md#gga8759c7e5a74964a584a716f4ec0b7edbae05fb41e422f91399d2e2efc3e84943b">OHOS::Media::FILE_SPLIT_NORMAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090973363093527"><a name="p1090973363093527"></a><a name="p1090973363093527"></a>Enumerates file split types. </p>
</td>
</tr>
</tbody>
</table>

