# format\_interface.h<a name="EN-US_TOPIC_0000001054598127"></a>

## **Overview**<a name="section1343270091093525"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Declares format-related APIs. 

For example, you use the functions provided in this file to define custom data types and to initialize, create, destroy the muxer and demuxer, and set their parameters. Also, you can read demuxer data frames, select demuxer tracks, add muxer tracks, and write data frames into a container.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1346413899093525"></a>

## Functions<a name="func-members"></a>

<a name="table462971281093525"></a>
<table><thead align="left"><tr id="row1538455717093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1242387238093525"><a name="p1242387238093525"></a><a name="p1242387238093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1045218669093525"><a name="p1045218669093525"></a><a name="p1045218669093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row263925225093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p135038706093525"><a name="p135038706093525"></a><a name="p135038706093525"></a><a href="format.md#gae10a50c8f3de6e54ee0dc3937f755920">FormatInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801704731093525"><a name="p801704731093525"></a><a name="p801704731093525"></a>void </p>
<p id="p1311348807093525"><a name="p1311348807093525"></a><a name="p1311348807093525"></a>Initializes the format. </p>
</td>
</tr>
<tr id="row136008339093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p406548937093525"><a name="p406548937093525"></a><a name="p406548937093525"></a><a href="format.md#gabb574933ebb4f3d1d2ed299e79aeee2c">FormatDeInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025731462093525"><a name="p2025731462093525"></a><a name="p2025731462093525"></a>void </p>
<p id="p1744658667093525"><a name="p1744658667093525"></a><a name="p1744658667093525"></a>Deinitializes the format. </p>
</td>
</tr>
<tr id="row1139696505093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1484244721093525"><a name="p1484244721093525"></a><a name="p1484244721093525"></a><a href="format.md#ga183fbc31f2c9877ef56464abcccef374">FormatDemuxerCreate</a> (const <a href="formatsource.md">FormatSource</a> *source, void **handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131066849093525"><a name="p2131066849093525"></a><a name="p2131066849093525"></a>int32_t </p>
<p id="p894103992093525"><a name="p894103992093525"></a><a name="p894103992093525"></a>Creates a demuxer component and returns its context handle. </p>
</td>
</tr>
<tr id="row1340019463093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1332230191093525"><a name="p1332230191093525"></a><a name="p1332230191093525"></a><a href="format.md#ga92d859ba4745ce26b94595daaa40462d">FormatDemuxerSetParameter</a> (const void *handle, int32_t trackId, const <a href="parameteritem.md">ParameterItem</a> *metaData, int32_t metaDataCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669796469093525"><a name="p669796469093525"></a><a name="p669796469093525"></a>int32_t </p>
<p id="p630887961093525"><a name="p630887961093525"></a><a name="p630887961093525"></a>Sets demuxer attributes. </p>
</td>
</tr>
<tr id="row1041317145093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496463729093525"><a name="p1496463729093525"></a><a name="p1496463729093525"></a><a href="format.md#ga6c2a1aa9fdf1db8e2f14a3a92ffa23d5">FormatDemuxerGetParameter</a> (const void *handle, int32_t trackId, <a href="parameteritem.md">ParameterItem</a> *metaData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1631422337093525"><a name="p1631422337093525"></a><a name="p1631422337093525"></a>int32_t </p>
<p id="p1784435051093525"><a name="p1784435051093525"></a><a name="p1784435051093525"></a>Obtains demuxer attributes. </p>
</td>
</tr>
<tr id="row1333595594093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789398042093525"><a name="p1789398042093525"></a><a name="p1789398042093525"></a><a href="format.md#ga9ef126fc3132b556d49a275799e7753b">FormatDemuxerSetCallBack</a> (void *handle, const <a href="formatcallback.md">FormatCallback</a> *callBack)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242005970093525"><a name="p1242005970093525"></a><a name="p1242005970093525"></a>int32_t </p>
<p id="p2099380810093525"><a name="p2099380810093525"></a><a name="p2099380810093525"></a>Sets a callback for the demuxer. </p>
</td>
</tr>
<tr id="row1968765507093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390730323093525"><a name="p1390730323093525"></a><a name="p1390730323093525"></a><a href="format.md#gad2a15f3fa640f3f9e8e684d71b3a12cb">FormatDemuxerSetBufferConfig</a> (void *handle, const <a href="formatbuffersetting.md">FormatBufferSetting</a> *setting)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1298977598093525"><a name="p1298977598093525"></a><a name="p1298977598093525"></a>int32_t </p>
<p id="p310316681093525"><a name="p310316681093525"></a><a name="p310316681093525"></a>Sets buffer information for the demuxer. </p>
</td>
</tr>
<tr id="row686836975093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224933785093525"><a name="p224933785093525"></a><a name="p224933785093525"></a><a href="format.md#ga565cbb52c95a95aab4dcc957fe998b5f">FormatDemuxerGetBufferConfig</a> (const void *handle, <a href="formatbuffersetting.md">FormatBufferSetting</a> *setting)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2054962615093525"><a name="p2054962615093525"></a><a name="p2054962615093525"></a>int32_t </p>
<p id="p1037553586093525"><a name="p1037553586093525"></a><a name="p1037553586093525"></a>Obtains the buffer information of the demuxer. </p>
</td>
</tr>
<tr id="row783075667093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p435615739093525"><a name="p435615739093525"></a><a name="p435615739093525"></a><a href="format.md#gacfcf40d869a48125bd67d17f8a4fc3ce">FormatDemuxerPrepare</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1811188556093525"><a name="p1811188556093525"></a><a name="p1811188556093525"></a>int32_t </p>
<p id="p808165404093525"><a name="p808165404093525"></a><a name="p808165404093525"></a>Makes preparations for the demuxer. </p>
</td>
</tr>
<tr id="row2044150739093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p578784752093525"><a name="p578784752093525"></a><a name="p578784752093525"></a><a href="format.md#gad807d61c65e89629c7eed8f97426fd5a">FormatDemuxerGetFileInfo</a> (void *handle, <a href="fileinfo.md">FileInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67685368093525"><a name="p67685368093525"></a><a name="p67685368093525"></a>int32_t </p>
<p id="p1429334524093525"><a name="p1429334524093525"></a><a name="p1429334524093525"></a>Obtains the attributes of a media file. </p>
</td>
</tr>
<tr id="row846509491093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1013272868093525"><a name="p1013272868093525"></a><a name="p1013272868093525"></a><a href="format.md#ga1d9cb94614e207def34f13eaa16ef2b7">FormatDemuxerSelectTrack</a> (const void *handle, int32_t programId, int32_t trackId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1716686996093525"><a name="p1716686996093525"></a><a name="p1716686996093525"></a>int32_t </p>
<p id="p2130643253093525"><a name="p2130643253093525"></a><a name="p2130643253093525"></a>Selects a specified media track. </p>
</td>
</tr>
<tr id="row2106581450093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636204752093525"><a name="p636204752093525"></a><a name="p636204752093525"></a><a href="format.md#gaf5fd5bab9613d133827054f157d5520e">FormatDemuxerUnselectTrack</a> (const void *handle, int32_t programId, int32_t trackId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459149720093525"><a name="p459149720093525"></a><a name="p459149720093525"></a>int32_t </p>
<p id="p12979640093525"><a name="p12979640093525"></a><a name="p12979640093525"></a>Unselects a specified media track from which the demuxer reads data frames. </p>
</td>
</tr>
<tr id="row1442754661093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160821416093525"><a name="p160821416093525"></a><a name="p160821416093525"></a><a href="format.md#ga08544b1ba3373bf5cb211586e8195673">FormatDemuxerStart</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075535456093525"><a name="p2075535456093525"></a><a name="p2075535456093525"></a>int32_t </p>
<p id="p1434346919093525"><a name="p1434346919093525"></a><a name="p1434346919093525"></a>Starts the demuxer. </p>
</td>
</tr>
<tr id="row1469784849093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1248365814093525"><a name="p1248365814093525"></a><a name="p1248365814093525"></a><a href="format.md#gab6ef68051ee2ed0015e721bedb1af61c">FormatDemuxerGetSelectedTrack</a> (const void *handle, int32_t *programId, int32_t trackId[], int32_t *nums)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1250513482093525"><a name="p1250513482093525"></a><a name="p1250513482093525"></a>int32_t </p>
<p id="p1118682269093525"><a name="p1118682269093525"></a><a name="p1118682269093525"></a>Obtains the ID of the media track selected by the demuxer for output. </p>
</td>
</tr>
<tr id="row282486069093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1948155308093525"><a name="p1948155308093525"></a><a name="p1948155308093525"></a><a href="format.md#ga7b20e1b88413d20a348d7f796917cd94">FormatDemuxerReadFrame</a> (const void *handle, <a href="formatframe.md">FormatFrame</a> *frame, int32_t timeOutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1364772757093525"><a name="p1364772757093525"></a><a name="p1364772757093525"></a>int32_t </p>
<p id="p1949527375093525"><a name="p1949527375093525"></a><a name="p1949527375093525"></a>Reads data frames. </p>
</td>
</tr>
<tr id="row216778346093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1775033422093525"><a name="p1775033422093525"></a><a name="p1775033422093525"></a><a href="format.md#ga291b805de194c695b72eb5ad721103d5">FormatDemuxerFreeFrame</a> (void *handle, <a href="formatframe.md">FormatFrame</a> *frame)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p942919539093525"><a name="p942919539093525"></a><a name="p942919539093525"></a>int32_t </p>
<p id="p1237371044093525"><a name="p1237371044093525"></a><a name="p1237371044093525"></a>Frees data frames. </p>
</td>
</tr>
<tr id="row1327297166093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2086028677093525"><a name="p2086028677093525"></a><a name="p2086028677093525"></a><a href="format.md#gad53f1e848f3c2e0c8fa056a312b2ed6c">FormatDemuxerSeek</a> (const void *handle, int32_t streamIndex, int64_t timeStampUs, <a href="format.md#ga14aa9d18a71eff4a0b70f748f0377c94">FormatSeekMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1891025701093525"><a name="p1891025701093525"></a><a name="p1891025701093525"></a>int32_t </p>
<p id="p870706021093525"><a name="p870706021093525"></a><a name="p870706021093525"></a>Seeks for a specified position for the demuxer. </p>
</td>
</tr>
<tr id="row1959908101093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1498624057093525"><a name="p1498624057093525"></a><a name="p1498624057093525"></a><a href="format.md#ga8a693d8be0b4b688d99e513608884e91">FormatDemuxerStop</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2128677001093525"><a name="p2128677001093525"></a><a name="p2128677001093525"></a>int32_t </p>
<p id="p167453307093525"><a name="p167453307093525"></a><a name="p167453307093525"></a>Stops the demuxer from working. </p>
</td>
</tr>
<tr id="row446141999093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p775663381093525"><a name="p775663381093525"></a><a name="p775663381093525"></a><a href="format.md#ga98fd9a5a5d1ffd275fc46f898ca08413">FormatDemuxerDestory</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p707157808093525"><a name="p707157808093525"></a><a name="p707157808093525"></a>int32_t </p>
<p id="p1501171793093525"><a name="p1501171793093525"></a><a name="p1501171793093525"></a>Destroys demuxer resources. </p>
</td>
</tr>
<tr id="row503605676093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1441820349093525"><a name="p1441820349093525"></a><a name="p1441820349093525"></a><a href="format.md#ga9c390276cb90f4753c32af5aa5c600ad">FormatMuxerCreate</a> (void **handle, <a href="formatoutputconfig.md">FormatOutputConfig</a> *outputConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p641496722093525"><a name="p641496722093525"></a><a name="p641496722093525"></a>int32_t </p>
<p id="p520862712093525"><a name="p520862712093525"></a><a name="p520862712093525"></a>Creates a muxer and returns its context handle. </p>
</td>
</tr>
<tr id="row1283754400093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p749722125093525"><a name="p749722125093525"></a><a name="p749722125093525"></a><a href="format.md#gaa41d46cef6d5e81c85614edbf824d803">FormatMuxerDestory</a> (const void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p653976905093525"><a name="p653976905093525"></a><a name="p653976905093525"></a>int32_t </p>
<p id="p1974355959093525"><a name="p1974355959093525"></a><a name="p1974355959093525"></a>Destroys a muxer and release its resources created by calling <a href="format.md#ga9c390276cb90f4753c32af5aa5c600ad">FormatMuxerCreate</a>. </p>
</td>
</tr>
<tr id="row942239204093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p544008354093525"><a name="p544008354093525"></a><a name="p544008354093525"></a><a href="format.md#ga94e9ab3e534b69a358b7cc16e4f79b78">FormatMuxerAddTrack</a> (void *handle, const <a href="tracksource.md">TrackSource</a> *trackSource)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2080637403093525"><a name="p2080637403093525"></a><a name="p2080637403093525"></a>int32_t </p>
<p id="p2064277535093525"><a name="p2064277535093525"></a><a name="p2064277535093525"></a>Adds a media track source for the muxer. For details about track sources, see <a href="tracksource.md">TrackSource</a>. </p>
</td>
</tr>
<tr id="row2021749016093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1100523117093525"><a name="p1100523117093525"></a><a name="p1100523117093525"></a><a href="format.md#ga108cd7e319ade568f71890d57585f153">FormatMuxerSetCallBack</a> (void *handle, const <a href="formatcallback.md">FormatCallback</a> *callBack)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p102646293093525"><a name="p102646293093525"></a><a name="p102646293093525"></a>int32_t </p>
<p id="p648745064093525"><a name="p648745064093525"></a><a name="p648745064093525"></a>Sets a callback for the muxer. For details about the callback, see <a href="formatcallback.md">FormatCallback</a>. </p>
</td>
</tr>
<tr id="row1173189058093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p539694840093525"><a name="p539694840093525"></a><a name="p539694840093525"></a><a href="format.md#ga96fc57913c3202d2d23704c69d660be5">FormatMuxerSetOrientation</a> (void *handle, int degrees)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1552017061093525"><a name="p1552017061093525"></a><a name="p1552017061093525"></a>int32_t </p>
<p id="p1991023384093525"><a name="p1991023384093525"></a><a name="p1991023384093525"></a>Sets the orientation of the video track for the muxer. </p>
</td>
</tr>
<tr id="row1563625249093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p379115392093525"><a name="p379115392093525"></a><a name="p379115392093525"></a><a href="format.md#ga967ba14fa1231eed2942b87a09deb953">FormatMuxerSetLocation</a> (const void *handle, int latitude, int longitude)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1244292331093525"><a name="p1244292331093525"></a><a name="p1244292331093525"></a>int32_t </p>
<p id="p1077359986093525"><a name="p1077359986093525"></a><a name="p1077359986093525"></a>Sets the geographical information for the output file of the muxer. </p>
</td>
</tr>
<tr id="row236020162093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410001718093525"><a name="p410001718093525"></a><a name="p410001718093525"></a><a href="format.md#ga6f3ba422c9bbca4c1d5a7a3fe85dd9b9">FormatMuxerSetMaxFileSize</a> (void *handle, int64_t bytes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p730765350093525"><a name="p730765350093525"></a><a name="p730765350093525"></a>int32_t </p>
<p id="p858959435093525"><a name="p858959435093525"></a><a name="p858959435093525"></a>Sets the maximum size (in bytes) for the output file of the muxer. </p>
</td>
</tr>
<tr id="row1736560375093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2067206325093525"><a name="p2067206325093525"></a><a name="p2067206325093525"></a><a href="format.md#gae931061d822c4ffe447e9ba40a991597">FormatMuxerSetMaxFileDuration</a> (void *handle, int64_t durationUs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1580650549093525"><a name="p1580650549093525"></a><a name="p1580650549093525"></a>int32_t </p>
<p id="p1782647218093525"><a name="p1782647218093525"></a><a name="p1782647218093525"></a>Sets the maximum duration (in seconds) for the output file. </p>
</td>
</tr>
<tr id="row107240351093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1416329148093525"><a name="p1416329148093525"></a><a name="p1416329148093525"></a><a href="format.md#ga6eed6b5e7522e102f2d79d0dd33fd2a9">FormatMuxerSetFileSplitDuration</a> (const void *handle, <a href="format.md#ga10d9833450f29129d249c41d9acb4bc4">ManualSplitType</a> type, int64_t timestampUs, uint32_t durationUs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1442376136093525"><a name="p1442376136093525"></a><a name="p1442376136093525"></a>int32_t </p>
<p id="p859237519093525"><a name="p859237519093525"></a><a name="p859237519093525"></a>Manually splits a file. </p>
</td>
</tr>
<tr id="row1531743155093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1018559465093525"><a name="p1018559465093525"></a><a name="p1018559465093525"></a><a href="format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b">FormatMuxerStart</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1979208818093525"><a name="p1979208818093525"></a><a name="p1979208818093525"></a>int32_t </p>
<p id="p2140955923093525"><a name="p2140955923093525"></a><a name="p2140955923093525"></a>Starts the muxer. </p>
</td>
</tr>
<tr id="row429198830093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p914879852093525"><a name="p914879852093525"></a><a name="p914879852093525"></a><a href="format.md#ga82037d271e77da206e16582e774ee048">FormatMuxerWriteFrame</a> (const void *handle, const <a href="formatframe.md">FormatFrame</a> *frameData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925850954093525"><a name="p1925850954093525"></a><a name="p1925850954093525"></a>int32_t </p>
<p id="p2112153899093525"><a name="p2112153899093525"></a><a name="p2112153899093525"></a>Writes data frames into the muxer. </p>
</td>
</tr>
<tr id="row2130525149093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1882564330093525"><a name="p1882564330093525"></a><a name="p1882564330093525"></a><a href="format.md#gaa936b56996294d76977537267fef058c">FormatMuxerSetNextOutputFile</a> (const void *handle, int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021835675093525"><a name="p1021835675093525"></a><a name="p1021835675093525"></a>int32_t </p>
<p id="p622054733093525"><a name="p622054733093525"></a><a name="p622054733093525"></a>Sets the descriptor for the next output file. </p>
</td>
</tr>
<tr id="row1019192794093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1310665170093525"><a name="p1310665170093525"></a><a name="p1310665170093525"></a><a href="format.md#ga66a3a5a1ec6d01fcbd6339f7eee1151b">FormatMuxerStop</a> (const void *handle, bool block)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508182387093525"><a name="p508182387093525"></a><a name="p508182387093525"></a>int32_t </p>
<p id="p1527667267093525"><a name="p1527667267093525"></a><a name="p1527667267093525"></a>Stops the muxer that was started by calling <a href="format.md#ga9a2af831a6f4a63dc85d2c23b5c7c81b">FormatMuxerStart</a>. </p>
</td>
</tr>
<tr id="row339413666093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875493085093525"><a name="p1875493085093525"></a><a name="p1875493085093525"></a><a href="format.md#gad4335ebaa7c165b885a00fe61aae0cd9">FormatMuxerSetParameter</a> (void *handle, int32_t trackId, const <a href="parameteritem.md">ParameterItem</a> *item, int32_t itemNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025648227093525"><a name="p1025648227093525"></a><a name="p1025648227093525"></a>int32_t </p>
<p id="p1500975867093525"><a name="p1500975867093525"></a><a name="p1500975867093525"></a>Sets muxer attributes. </p>
</td>
</tr>
<tr id="row1474673960093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027363824093525"><a name="p1027363824093525"></a><a name="p1027363824093525"></a><a href="format.md#ga67dd7361dedf335496afef19d54e4138">FormatMuxerGetParameter</a> (void *handle, int32_t trackId, <a href="parameteritem.md">ParameterItem</a> *item, int32_t itemNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628994625093525"><a name="p1628994625093525"></a><a name="p1628994625093525"></a>int32_t </p>
<p id="p682568633093525"><a name="p682568633093525"></a><a name="p682568633093525"></a>Obtains muxer attributes. </p>
</td>
</tr>
</tbody>
</table>

