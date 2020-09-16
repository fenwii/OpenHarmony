# source.h<a name="ZH-CN_TOPIC_0000001055678072"></a>

## **Overview**<a name="section1166002983093527"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Declares the  **Source**  class, which is used to implement source-related operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section575785260093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table506336857093527"></a>
<table><thead align="left"><tr id="row1597018083093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p445776319093527"><a name="p445776319093527"></a><a name="p445776319093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p443033099093527"><a name="p443033099093527"></a><a name="p443033099093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1836265077093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282352419093527"><a name="p1282352419093527"></a><a name="p1282352419093527"></a><a href="OHOS-Media-StreamCallback.md">OHOS::Media::StreamCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647913880093527"><a name="p647913880093527"></a><a name="p647913880093527"></a>Provides functions to obtain the address of a buffer memory and write the filled buffers into the playback queue. You need to implement the <strong id="b1994133423093527"><a name="b1994133423093527"></a><a name="b1994133423093527"></a><a href="OHOS-Media-StreamCallback.md">StreamCallback</a></strong> functions in a player object. </p>
</td>
</tr>
<tr id="row1546647718093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806409482093527"><a name="p806409482093527"></a><a name="p806409482093527"></a><a href="OHOS-Media-StreamSource.md">OHOS::Media::StreamSource</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1092085429093527"><a name="p1092085429093527"></a><a name="p1092085429093527"></a>Provides functions related to the stream source for upper-layer applications. </p>
</td>
</tr>
<tr id="row731707142093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817093640093527"><a name="p1817093640093527"></a><a name="p1817093640093527"></a><a href="OHOS-Media-Source.md">OHOS::Media::Source</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1413986596093527"><a name="p1413986596093527"></a><a name="p1413986596093527"></a>Provides functions to implement source-related operations. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table242914013093527"></a>
<table><thead align="left"><tr id="row764350416093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1088246854093527"><a name="p1088246854093527"></a><a name="p1088246854093527"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p789096477093527"><a name="p789096477093527"></a><a name="p789096477093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1942321663093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1910821246093527"><a name="p1910821246093527"></a><a name="p1910821246093527"></a><a href="MultiMedia_MediaCommon.md#ga4052b7b55dfd94f1d07678e79d80b507">OHOS::Media::SourceType</a> : int32_t { <a href="MultiMedia_MediaCommon.md#gga4052b7b55dfd94f1d07678e79d80b507ae456eda14b2359e13cc36f77af92c11b">OHOS::Media::SourceType::SOURCE_TYPE_URI</a> = 0, <a href="MultiMedia_MediaCommon.md#gga4052b7b55dfd94f1d07678e79d80b507a4134c6ec0b1a7fda26c38b8932e606e5">OHOS::Media::SourceType::SOURCE_TYPE_FD</a>, <a href="MultiMedia_MediaCommon.md#gga4052b7b55dfd94f1d07678e79d80b507a538f01f856d995123459a44642a7dc86">OHOS::Media::SourceType::SOURCE_TYPE_STREAM</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p870578219093527"><a name="p870578219093527"></a><a name="p870578219093527"></a>Enumerates media source types. </p>
</td>
</tr>
</tbody>
</table>

