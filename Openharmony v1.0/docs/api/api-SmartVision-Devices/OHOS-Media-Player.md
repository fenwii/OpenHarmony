# OHOS::Media::Player<a name="ZH-CN_TOPIC_0000001055518100"></a>

## **Overview**<a name="section1568874129093532"></a>

**Related Modules:**

[MultiMedia\_Player](MultiMedia_Player.md)

**Description:**

Provides functions for playing online movies, offline movies, and streams, for example, playing local movies and advanced audio coding \(AAC\) streams. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1950864612093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1771125029093532"></a>
<table><thead align="left"><tr id="row961264618093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1046140620093532"><a name="p1046140620093532"></a><a name="p1046140620093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1845271014093532"><a name="p1845271014093532"></a><a name="p1845271014093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1651721594093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p679711223093532"><a name="p679711223093532"></a><a name="p679711223093532"></a><a href="MultiMedia_Player.md#gacce284eac910970e405151fd3a1963c0">SetSource</a> (const <a href="OHOS-Media-Source.md">Source</a> &amp;source)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1617342267093532"><a name="p1617342267093532"></a><a name="p1617342267093532"></a>int32_t&nbsp;</p>
<p id="p1987273262093532"><a name="p1987273262093532"></a><a name="p1987273262093532"></a>Sets the playback source for the player. The corresponding source can be the file descriptor (FD) of the local file, local file URI, network URI, or media stream. </p>
</td>
</tr>
<tr id="row1922237064093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p944666344093532"><a name="p944666344093532"></a><a name="p944666344093532"></a><a href="MultiMedia_Player.md#gade9bff3268e1c409273749a90700e056">Prepare</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p777581616093532"><a name="p777581616093532"></a><a name="p777581616093532"></a>int32_t&nbsp;</p>
<p id="p164263961093532"><a name="p164263961093532"></a><a name="p164263961093532"></a>Prepares the playback environment and buffers media data. </p>
</td>
</tr>
<tr id="row408652213093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p579165159093532"><a name="p579165159093532"></a><a name="p579165159093532"></a><a href="MultiMedia_Player.md#gafecbbfe85c70cf4983f52d55b7205e3f">Play</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397554218093532"><a name="p397554218093532"></a><a name="p397554218093532"></a>int32_t&nbsp;</p>
<p id="p1200987988093532"><a name="p1200987988093532"></a><a name="p1200987988093532"></a>Starts or resumes playback. </p>
</td>
</tr>
<tr id="row1523278232093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035199649093532"><a name="p2035199649093532"></a><a name="p2035199649093532"></a><a href="MultiMedia_Player.md#gaad6b2c35b1d5dfe453d158f7ff9e1379">IsPlaying</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1992325009093532"><a name="p1992325009093532"></a><a name="p1992325009093532"></a>bool&nbsp;</p>
<p id="p1832025519093532"><a name="p1832025519093532"></a><a name="p1832025519093532"></a>Checks whether the player is playing. </p>
</td>
</tr>
<tr id="row1806317422093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516701848093532"><a name="p1516701848093532"></a><a name="p1516701848093532"></a><a href="MultiMedia_Player.md#gae1d2225ce60a9737cc902e586138a44f">Pause</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106355433093532"><a name="p106355433093532"></a><a name="p106355433093532"></a>int32_t&nbsp;</p>
<p id="p467674694093532"><a name="p467674694093532"></a><a name="p467674694093532"></a>Pauses playback. </p>
</td>
</tr>
<tr id="row786945770093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1277292481093532"><a name="p1277292481093532"></a><a name="p1277292481093532"></a><a href="MultiMedia_Player.md#gafe518a5b909ac0f0f066781caa3b55aa">Stop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p617140000093532"><a name="p617140000093532"></a><a name="p617140000093532"></a>int32_t&nbsp;</p>
<p id="p1588246548093532"><a name="p1588246548093532"></a><a name="p1588246548093532"></a>Stops playback. </p>
</td>
</tr>
<tr id="row2056198647093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723570447093532"><a name="p723570447093532"></a><a name="p723570447093532"></a><a href="MultiMedia_Player.md#ga406b6277d1e160e691d01f5f740480b3">Rewind</a> (int64_t mSeconds, int32_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1009332232093532"><a name="p1009332232093532"></a><a name="p1009332232093532"></a>int32_t&nbsp;</p>
<p id="p915851422093532"><a name="p915851422093532"></a><a name="p915851422093532"></a>Changes the playback position. </p>
</td>
</tr>
<tr id="row806393118093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024992340093532"><a name="p1024992340093532"></a><a name="p1024992340093532"></a><a href="MultiMedia_Player.md#ga23ca57f0b1a288980e37153274c5f8b3">SetVolume</a> (float leftVolume, float rightVolume)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p138191549093532"><a name="p138191549093532"></a><a name="p138191549093532"></a>int32_t&nbsp;</p>
<p id="p1002727884093532"><a name="p1002727884093532"></a><a name="p1002727884093532"></a>Sets the volume of the player. </p>
</td>
</tr>
<tr id="row1336130244093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1710755856093532"><a name="p1710755856093532"></a><a name="p1710755856093532"></a><a href="MultiMedia_Player.md#gac9d62210915ebcf3b462574302018501">SetVideoSurface</a> (<a href="OHOS-Surface.md">Surface</a> *surface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2793992093532"><a name="p2793992093532"></a><a name="p2793992093532"></a>int32_t&nbsp;</p>
<p id="p1643496323093532"><a name="p1643496323093532"></a><a name="p1643496323093532"></a>Sets a surface for video playback. </p>
</td>
</tr>
<tr id="row626375792093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1967297420093532"><a name="p1967297420093532"></a><a name="p1967297420093532"></a><a href="MultiMedia_Player.md#gae19989aa6e80b768acd4eb019a2b60d2">EnableSingleLooping</a> (bool loop)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225100372093532"><a name="p225100372093532"></a><a name="p225100372093532"></a>int32_t&nbsp;</p>
<p id="p1797948204093532"><a name="p1797948204093532"></a><a name="p1797948204093532"></a>Sets loop playback. </p>
</td>
</tr>
<tr id="row522787513093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102572308093532"><a name="p1102572308093532"></a><a name="p1102572308093532"></a><a href="MultiMedia_Player.md#gae4dd5d8fb92c836f5304f181a40b34d2">IsSingleLooping</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1083642666093532"><a name="p1083642666093532"></a><a name="p1083642666093532"></a>bool&nbsp;</p>
<p id="p85334602093532"><a name="p85334602093532"></a><a name="p85334602093532"></a>Checks whether the player is looping. </p>
</td>
</tr>
<tr id="row1585411512093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1591081908093532"><a name="p1591081908093532"></a><a name="p1591081908093532"></a><a href="MultiMedia_Player.md#ga8474b117a4c1bf5749406f26056b4802">GetCurrentTime</a> (int64_t &amp;<a href="zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p525090828093532"><a name="p525090828093532"></a><a name="p525090828093532"></a>int32_t&nbsp;</p>
<p id="p583202032093532"><a name="p583202032093532"></a><a name="p583202032093532"></a>Obtains the playback position, accurate to millisecond. </p>
</td>
</tr>
<tr id="row1658211964093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479438749093532"><a name="p1479438749093532"></a><a name="p1479438749093532"></a><a href="MultiMedia_Player.md#ga24ae07f65da4dafc4ec5aa28321625d8">GetDuration</a> (int64_t &amp;duration) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p62322052093532"><a name="p62322052093532"></a><a name="p62322052093532"></a>int32_t&nbsp;</p>
<p id="p1139280088093532"><a name="p1139280088093532"></a><a name="p1139280088093532"></a>Obtains the total duration of media files, in milliseconds. </p>
</td>
</tr>
<tr id="row1679192363093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p156569053093532"><a name="p156569053093532"></a><a name="p156569053093532"></a><a href="MultiMedia_Player.md#ga9ed94bd43d896fa10066497377d7fbda">GetVideoWidth</a> (int32_t &amp;videoWidth)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p47549936093532"><a name="p47549936093532"></a><a name="p47549936093532"></a>int32_t&nbsp;</p>
<p id="p1597890244093532"><a name="p1597890244093532"></a><a name="p1597890244093532"></a>Obtains the width of the video. </p>
</td>
</tr>
<tr id="row396430689093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1136743561093532"><a name="p1136743561093532"></a><a name="p1136743561093532"></a><a href="MultiMedia_Player.md#ga726adc32a34134b30aabfbdb389c8357">GetVideoHeight</a> (int32_t &amp;videoHeight)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1431877720093532"><a name="p1431877720093532"></a><a name="p1431877720093532"></a>int32_t&nbsp;</p>
<p id="p163575576093532"><a name="p163575576093532"></a><a name="p163575576093532"></a>Obtains the height of the video. </p>
</td>
</tr>
<tr id="row179664111093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p514863979093532"><a name="p514863979093532"></a><a name="p514863979093532"></a><a href="MultiMedia_Player.md#ga75e17ee0068d46d44a30709609821b85">Reset</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1966138983093532"><a name="p1966138983093532"></a><a name="p1966138983093532"></a>int32_t&nbsp;</p>
<p id="p187547161093532"><a name="p187547161093532"></a><a name="p187547161093532"></a>Restores the player to the initial state. </p>
</td>
</tr>
<tr id="row1347758172093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218790427093532"><a name="p218790427093532"></a><a name="p218790427093532"></a><a href="MultiMedia_Player.md#ga00e24c0faed483c9d54e416ec2ffe6ac">Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1933072309093532"><a name="p1933072309093532"></a><a name="p1933072309093532"></a>int32_t&nbsp;</p>
<p id="p911394099093532"><a name="p911394099093532"></a><a name="p911394099093532"></a>Releases player resources. </p>
</td>
</tr>
<tr id="row158413708093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p110289079093532"><a name="p110289079093532"></a><a name="p110289079093532"></a><a href="MultiMedia_Player.md#gabb6eca611514d5fc0b66df5ff2d70c2b">SetPlayerCallback</a> (const std::shared_ptr&lt; <a href="OHOS-Media-PlayerCallback.md">PlayerCallback</a> &gt; &amp;cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543192358093532"><a name="p1543192358093532"></a><a name="p1543192358093532"></a>void&nbsp;</p>
<p id="p1503878473093532"><a name="p1503878473093532"></a><a name="p1503878473093532"></a>Registers a listener to receive events and exception notifications from the player. </p>
</td>
</tr>
</tbody>
</table>

