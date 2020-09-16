# MultiMedia\_Player<a name="EN-US_TOPIC_0000001055518042"></a>

## **Overview**<a name="section500839534093523"></a>

Defines the  **Player**  class and provides functions related to media playback. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1516346393093523"></a>

## Files<a name="files"></a>

<a name="table454139680093523"></a>
<table><thead align="left"><tr id="row940251758093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2058768290093523"><a name="p2058768290093523"></a><a name="p2058768290093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p35845808093523"><a name="p35845808093523"></a><a name="p35845808093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1878757213093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p998897416093523"><a name="p998897416093523"></a><a name="p998897416093523"></a><a href="player-h.md">player.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703897286093523"><a name="p1703897286093523"></a><a name="p1703897286093523"></a>Declares the <strong id="b1094446532093523"><a name="b1094446532093523"></a><a name="b1094446532093523"></a>Player</strong> class, which is used to implement player-related operations. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1987907920093523"></a>
<table><thead align="left"><tr id="row281962858093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1567208909093523"><a name="p1567208909093523"></a><a name="p1567208909093523"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p120748523093523"><a name="p120748523093523"></a><a name="p120748523093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1104027601093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1768302336093523"><a name="p1768302336093523"></a><a name="p1768302336093523"></a><a href="ohos-media-playercallback.md">OHOS::Media::PlayerCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p799610645093523"><a name="p799610645093523"></a><a name="p799610645093523"></a>Provides listeners for events and exception notifications that occur during media playback. </p>
</td>
</tr>
<tr id="row327366035093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2026957602093523"><a name="p2026957602093523"></a><a name="p2026957602093523"></a><a href="ohos-media-player.md">OHOS::Media::Player</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825133925093523"><a name="p1825133925093523"></a><a name="p1825133925093523"></a>Provides functions for playing online movies, offline movies, and streams, for example, playing local movies and advanced audio coding (AAC) streams. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1543208623093523"></a>
<table><thead align="left"><tr id="row346100919093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1715950935093523"><a name="p1715950935093523"></a><a name="p1715950935093523"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p630438291093523"><a name="p630438291093523"></a><a name="p630438291093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row551851306093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1956730746093523"><a name="p1956730746093523"></a><a name="p1956730746093523"></a><a href="multimedia_player.md#gad1574e5769b3174c2103a2a8b49e20d4">OHOS::Media::PlayerSeekMode</a> : int32_t {   <a href="multimedia_player.md#ggad1574e5769b3174c2103a2a8b49e20d4a08be30187c1d180d77b375af6f35966c">OHOS::Media::PLAYER_SEEK_PREVIOUS_SYNC</a> = 0, <a href="multimedia_player.md#ggad1574e5769b3174c2103a2a8b49e20d4a98aa52abc293a28728ef9d2e9019ae7d">OHOS::Media::PLAYER_SEEK_NEXT_SYNC</a>, <a href="multimedia_player.md#ggad1574e5769b3174c2103a2a8b49e20d4ae6257ed93e90e2231eb3369a36027872">OHOS::Media::PLAYER_SEEK_CLOSEST_SYNC</a>, <a href="multimedia_player.md#ggad1574e5769b3174c2103a2a8b49e20d4a0f6165a7f22f44f78bbb9004f2a55428">OHOS::Media::PLAYER_SEEK_CLOSEST</a>,   <a href="multimedia_player.md#ggad1574e5769b3174c2103a2a8b49e20d4ada8db6c3cb45acbc0ff09cb3fe65fd94">OHOS::Media::PLAYER_SEEK_FRAME_INDEX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1562349895093523"><a name="p1562349895093523"></a><a name="p1562349895093523"></a>Enumerates player seek modes. You can move the current playback position of the media to a given time position using the specified mode. </p>
</td>
</tr>
<tr id="row1726178255093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1804569146093523"><a name="p1804569146093523"></a><a name="p1804569146093523"></a><a href="multimedia_player.md#ga8b1147e57c4a67f63f193836302da2b7">OHOS::Media::PlayerStates</a> : uint32_t {   <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a53755dd964e67b38f2b20a73043c6a15">OHOS::Media::PLAYER_STATE_ERROR</a> = 0, <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a422de416a9d98b7a11334080277e5a91">OHOS::Media::PLAYER_IDLE</a> = 1 &lt;&lt; 0, <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a9b85bb17a31e74c8913d3344a9890968">OHOS::Media::PLAYER_INITIALIZED</a> = 1 &lt;&lt; 1, <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a5f58beea6c3cfd9faf9d9dacb6d0de43">OHOS::Media::PLAYER_PREPARING</a> = 1 &lt;&lt; 2,   <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a992920b7152bf85ce28b0cbc2204a01b">OHOS::Media::PLAYER_PREPARED</a> = 1 &lt;&lt; 3, <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7ab59f150a877432470b368cb6ae3c01d6">OHOS::Media::PLAYER_STARTED</a> = 1 &lt;&lt; 4, <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a865415ef0c33b942431a1814e84dd848">OHOS::Media::PLAYER_PAUSED</a> = 1 &lt;&lt; 5, <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7a0d79ba704b9048d53deee264f6e6546d">OHOS::Media::PLAYER_STOPPED</a> = 1 &lt;&lt; 6,   <a href="multimedia_player.md#gga8b1147e57c4a67f63f193836302da2b7ac5e465735c926d57e1bcb39eff208e51">OHOS::Media::PLAYER_PLAYBACK_COMPLETE</a> = 1 &lt;&lt; 7 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2138216958093523"><a name="p2138216958093523"></a><a name="p2138216958093523"></a>Enumerates player states. </p>
</td>
</tr>
<tr id="row1944427446093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875642596093523"><a name="p875642596093523"></a><a name="p875642596093523"></a><a href="multimedia_player.md#ga7dac9dac65cbbea7e411adcf2c314ac5">OHOS::Media::PlayerCallback::PlayerInfoType</a> : int32_t { <a href="multimedia_player.md#gga7dac9dac65cbbea7e411adcf2c314ac5ab5ccacbb568a9b3ce5fedc0ced4e683d">OHOS::Media::PlayerCallback::PLAYER_INFO_RENDER_START</a> = 0 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table115287410093523"></a>
<table><thead align="left"><tr id="row1033040725093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p26931857093523"><a name="p26931857093523"></a><a name="p26931857093523"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1423099871093523"><a name="p1423099871093523"></a><a name="p1423099871093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row978257349093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795983879093523"><a name="p795983879093523"></a><a name="p795983879093523"></a><a href="multimedia_player.md#ga3b56f618340bf9a5590e6142b2311302">OHOS::Media::PlayerCallback::OnPlaybackComplete</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p753045791093523"><a name="p753045791093523"></a><a name="p753045791093523"></a>virtual void </p>
<p id="p1020935871093523"><a name="p1020935871093523"></a><a name="p1020935871093523"></a>Called when the playback is complete. </p>
</td>
</tr>
<tr id="row2015922353093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381630073093523"><a name="p381630073093523"></a><a name="p381630073093523"></a><a href="multimedia_player.md#ga3d0fdad57045f5e049b56de031d3e0fb">OHOS::Media::PlayerCallback::OnError</a> (int32_t errorType, int32_t errorCode)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052425660093523"><a name="p1052425660093523"></a><a name="p1052425660093523"></a>virtual void </p>
<p id="p1972512509093523"><a name="p1972512509093523"></a><a name="p1972512509093523"></a>Called when a playback error occurs. </p>
</td>
</tr>
<tr id="row1745825056093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p100510161093523"><a name="p100510161093523"></a><a name="p100510161093523"></a><a href="multimedia_player.md#gad2d3466c8a17ee4d622b87fa6a31b2bb">OHOS::Media::PlayerCallback::OnInfo</a> (int type, int extra)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p930178547093523"><a name="p930178547093523"></a><a name="p930178547093523"></a>virtual void </p>
<p id="p1572435330093523"><a name="p1572435330093523"></a><a name="p1572435330093523"></a>Called when playback information is received. </p>
</td>
</tr>
<tr id="row1107334357093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61110873093523"><a name="p61110873093523"></a><a name="p61110873093523"></a><a href="multimedia_player.md#gac5b641f93621d90e616d18adaa016e8a">OHOS::Media::PlayerCallback::OnVideoSizeChanged</a> (int width, int height)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p94048654093523"><a name="p94048654093523"></a><a name="p94048654093523"></a>virtual void </p>
<p id="p2038018477093523"><a name="p2038018477093523"></a><a name="p2038018477093523"></a>Called when the video image size changes. </p>
</td>
</tr>
<tr id="row774248463093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p497241702093523"><a name="p497241702093523"></a><a name="p497241702093523"></a><a href="multimedia_player.md#ga765c499e47dfaad5e557197e964eaca3">OHOS::Media::PlayerCallback::OnRewindToComplete</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995563775093523"><a name="p1995563775093523"></a><a name="p1995563775093523"></a>virtual void </p>
<p id="p1108546394093523"><a name="p1108546394093523"></a><a name="p1108546394093523"></a>Called when the rewind is complete. </p>
</td>
</tr>
<tr id="row1068233450093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1545954917093523"><a name="p1545954917093523"></a><a name="p1545954917093523"></a><a href="multimedia_player.md#gacce284eac910970e405151fd3a1963c0">OHOS::Media::Player::SetSource</a> (const <a href="ohos-media-source.md">Source</a> &amp;source)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987122347093523"><a name="p987122347093523"></a><a name="p987122347093523"></a>int32_t </p>
<p id="p202690401093523"><a name="p202690401093523"></a><a name="p202690401093523"></a>Sets the playback source for the player. The corresponding source can be the file descriptor (FD) of the local file, local file URI, network URI, or media stream. </p>
</td>
</tr>
<tr id="row1167655812093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p60510999093523"><a name="p60510999093523"></a><a name="p60510999093523"></a><a href="multimedia_player.md#gade9bff3268e1c409273749a90700e056">OHOS::Media::Player::Prepare</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844410571093523"><a name="p1844410571093523"></a><a name="p1844410571093523"></a>int32_t </p>
<p id="p328452748093523"><a name="p328452748093523"></a><a name="p328452748093523"></a>Prepares the playback environment and buffers media data. </p>
</td>
</tr>
<tr id="row2109130093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p999299209093523"><a name="p999299209093523"></a><a name="p999299209093523"></a><a href="multimedia_player.md#gafecbbfe85c70cf4983f52d55b7205e3f">OHOS::Media::Player::Play</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601998199093523"><a name="p601998199093523"></a><a name="p601998199093523"></a>int32_t </p>
<p id="p1657015634093523"><a name="p1657015634093523"></a><a name="p1657015634093523"></a>Starts or resumes playback. </p>
</td>
</tr>
<tr id="row1564517685093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090913022093523"><a name="p1090913022093523"></a><a name="p1090913022093523"></a><a href="multimedia_player.md#gaad6b2c35b1d5dfe453d158f7ff9e1379">OHOS::Media::Player::IsPlaying</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852652549093523"><a name="p852652549093523"></a><a name="p852652549093523"></a>bool </p>
<p id="p1971319082093523"><a name="p1971319082093523"></a><a name="p1971319082093523"></a>Checks whether the player is playing. </p>
</td>
</tr>
<tr id="row2010011437093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1355589821093523"><a name="p1355589821093523"></a><a name="p1355589821093523"></a><a href="multimedia_player.md#gae1d2225ce60a9737cc902e586138a44f">OHOS::Media::Player::Pause</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1804963677093523"><a name="p1804963677093523"></a><a name="p1804963677093523"></a>int32_t </p>
<p id="p1101320598093523"><a name="p1101320598093523"></a><a name="p1101320598093523"></a>Pauses playback. </p>
</td>
</tr>
<tr id="row42335008093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029782500093523"><a name="p1029782500093523"></a><a name="p1029782500093523"></a><a href="multimedia_player.md#gafe518a5b909ac0f0f066781caa3b55aa">OHOS::Media::Player::Stop</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1319131259093523"><a name="p1319131259093523"></a><a name="p1319131259093523"></a>int32_t </p>
<p id="p184239133093523"><a name="p184239133093523"></a><a name="p184239133093523"></a>Stops playback. </p>
</td>
</tr>
<tr id="row780754947093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1447393020093523"><a name="p1447393020093523"></a><a name="p1447393020093523"></a><a href="multimedia_player.md#ga406b6277d1e160e691d01f5f740480b3">OHOS::Media::Player::Rewind</a> (int64_t mSeconds, int32_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p752273112093523"><a name="p752273112093523"></a><a name="p752273112093523"></a>int32_t </p>
<p id="p2043404731093523"><a name="p2043404731093523"></a><a name="p2043404731093523"></a>Changes the playback position. </p>
</td>
</tr>
<tr id="row1891229384093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1810673828093523"><a name="p1810673828093523"></a><a name="p1810673828093523"></a><a href="multimedia_player.md#ga23ca57f0b1a288980e37153274c5f8b3">OHOS::Media::Player::SetVolume</a> (float leftVolume, float rightVolume)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723718152093523"><a name="p723718152093523"></a><a name="p723718152093523"></a>int32_t </p>
<p id="p1052023723093523"><a name="p1052023723093523"></a><a name="p1052023723093523"></a>Sets the volume of the player. </p>
</td>
</tr>
<tr id="row899813511093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p948523604093523"><a name="p948523604093523"></a><a name="p948523604093523"></a><a href="multimedia_player.md#gac9d62210915ebcf3b462574302018501">OHOS::Media::Player::SetVideoSurface</a> (<a href="ohos-surface.md">Surface</a> *surface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p188092244093523"><a name="p188092244093523"></a><a name="p188092244093523"></a>int32_t </p>
<p id="p1250230867093523"><a name="p1250230867093523"></a><a name="p1250230867093523"></a>Sets a surface for video playback. </p>
</td>
</tr>
<tr id="row1971269955093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906480078093523"><a name="p1906480078093523"></a><a name="p1906480078093523"></a><a href="multimedia_player.md#gae19989aa6e80b768acd4eb019a2b60d2">OHOS::Media::Player::EnableSingleLooping</a> (bool loop)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149217079093523"><a name="p149217079093523"></a><a name="p149217079093523"></a>int32_t </p>
<p id="p2038114744093523"><a name="p2038114744093523"></a><a name="p2038114744093523"></a>Sets loop playback. </p>
</td>
</tr>
<tr id="row2013340823093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027837038093523"><a name="p1027837038093523"></a><a name="p1027837038093523"></a><a href="multimedia_player.md#gae4dd5d8fb92c836f5304f181a40b34d2">OHOS::Media::Player::IsSingleLooping</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229502323093523"><a name="p1229502323093523"></a><a name="p1229502323093523"></a>bool </p>
<p id="p1273987837093523"><a name="p1273987837093523"></a><a name="p1273987837093523"></a>Checks whether the player is looping. </p>
</td>
</tr>
<tr id="row1763533017093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p750468801093523"><a name="p750468801093523"></a><a name="p750468801093523"></a><a href="multimedia_player.md#ga8474b117a4c1bf5749406f26056b4802">OHOS::Media::Player::GetCurrentTime</a> (int64_t &amp;<a href="en-us_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027985022093523"><a name="p1027985022093523"></a><a name="p1027985022093523"></a>int32_t </p>
<p id="p486895101093523"><a name="p486895101093523"></a><a name="p486895101093523"></a>Obtains the playback position, accurate to millisecond. </p>
</td>
</tr>
<tr id="row841617905093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p455370646093523"><a name="p455370646093523"></a><a name="p455370646093523"></a><a href="multimedia_player.md#ga24ae07f65da4dafc4ec5aa28321625d8">OHOS::Media::Player::GetDuration</a> (int64_t &amp;duration) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1923697119093523"><a name="p1923697119093523"></a><a name="p1923697119093523"></a>int32_t </p>
<p id="p498396780093523"><a name="p498396780093523"></a><a name="p498396780093523"></a>Obtains the total duration of media files, in milliseconds. </p>
</td>
</tr>
<tr id="row1958633865093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1314839790093523"><a name="p1314839790093523"></a><a name="p1314839790093523"></a><a href="multimedia_player.md#ga9ed94bd43d896fa10066497377d7fbda">OHOS::Media::Player::GetVideoWidth</a> (int32_t &amp;videoWidth)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1258313814093523"><a name="p1258313814093523"></a><a name="p1258313814093523"></a>int32_t </p>
<p id="p440752019093523"><a name="p440752019093523"></a><a name="p440752019093523"></a>Obtains the width of the video. </p>
</td>
</tr>
<tr id="row935297588093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687659981093523"><a name="p687659981093523"></a><a name="p687659981093523"></a><a href="multimedia_player.md#ga726adc32a34134b30aabfbdb389c8357">OHOS::Media::Player::GetVideoHeight</a> (int32_t &amp;videoHeight)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2098032216093523"><a name="p2098032216093523"></a><a name="p2098032216093523"></a>int32_t </p>
<p id="p16632305093523"><a name="p16632305093523"></a><a name="p16632305093523"></a>Obtains the height of the video. </p>
</td>
</tr>
<tr id="row188316947093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1198004368093523"><a name="p1198004368093523"></a><a name="p1198004368093523"></a><a href="multimedia_player.md#ga75e17ee0068d46d44a30709609821b85">OHOS::Media::Player::Reset</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437493524093523"><a name="p437493524093523"></a><a name="p437493524093523"></a>int32_t </p>
<p id="p1078592919093523"><a name="p1078592919093523"></a><a name="p1078592919093523"></a>Restores the player to the initial state. </p>
</td>
</tr>
<tr id="row119798024093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440601246093523"><a name="p440601246093523"></a><a name="p440601246093523"></a><a href="multimedia_player.md#ga00e24c0faed483c9d54e416ec2ffe6ac">OHOS::Media::Player::Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279302897093523"><a name="p279302897093523"></a><a name="p279302897093523"></a>int32_t </p>
<p id="p130266954093523"><a name="p130266954093523"></a><a name="p130266954093523"></a>Releases player resources. </p>
</td>
</tr>
<tr id="row1164097492093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464822735093523"><a name="p1464822735093523"></a><a name="p1464822735093523"></a><a href="multimedia_player.md#gabb6eca611514d5fc0b66df5ff2d70c2b">OHOS::Media::Player::SetPlayerCallback</a> (const std::shared_ptr&lt; <a href="ohos-media-playercallback.md">PlayerCallback</a> &gt; &amp;cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475761426093523"><a name="p475761426093523"></a><a name="p475761426093523"></a>void </p>
<p id="p1002934121093523"><a name="p1002934121093523"></a><a name="p1002934121093523"></a>Registers a listener to receive events and exception notifications from the player. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section465813334093523"></a>

## **Enumeration Type Documentation**<a name="section2114763496093523"></a>

## PlayerInfoType<a name="ga7dac9dac65cbbea7e411adcf2c314ac5"></a>

```
enum [OHOS::Media::PlayerCallback::PlayerInfoType](multimedia_player.md#ga7dac9dac65cbbea7e411adcf2c314ac5) : int32_t
```

<a name="table461228490093523"></a>
<table><thead align="left"><tr id="row1071397369093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2019190983093523"><a name="p2019190983093523"></a><a name="p2019190983093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p520458109093523"><a name="p520458109093523"></a><a name="p520458109093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row92855382093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7dac9dac65cbbea7e411adcf2c314ac5ab5ccacbb568a9b3ce5fedc0ced4e683d"><a name="gga7dac9dac65cbbea7e411adcf2c314ac5ab5ccacbb568a9b3ce5fedc0ced4e683d"></a><a name="gga7dac9dac65cbbea7e411adcf2c314ac5ab5ccacbb568a9b3ce5fedc0ced4e683d"></a></strong>PLAYER_INFO_RENDER_START </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298509692093523"><a name="p298509692093523"></a><a name="p298509692093523"></a>Pushed the first video frame for rendering </p>
 </td>
</tr>
</tbody>
</table>

## PlayerSeekMode<a name="gad1574e5769b3174c2103a2a8b49e20d4"></a>

```
enum [OHOS::Media::PlayerSeekMode](multimedia_player.md#gad1574e5769b3174c2103a2a8b49e20d4) : int32_t
```

 **Description:**

Enumerates player seek modes. You can move the current playback position of the media to a given time position using the specified mode. 

<a name="table926479139093523"></a>
<table><thead align="left"><tr id="row1402548709093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1439611410093523"><a name="p1439611410093523"></a><a name="p1439611410093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1820702284093523"><a name="p1820702284093523"></a><a name="p1820702284093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row908320971093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad1574e5769b3174c2103a2a8b49e20d4a08be30187c1d180d77b375af6f35966c"><a name="ggad1574e5769b3174c2103a2a8b49e20d4a08be30187c1d180d77b375af6f35966c"></a><a name="ggad1574e5769b3174c2103a2a8b49e20d4a08be30187c1d180d77b375af6f35966c"></a></strong>PLAYER_SEEK_PREVIOUS_SYNC </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120701881093523"><a name="p120701881093523"></a><a name="p120701881093523"></a>Moves the media position to the latest synchronization frame located before the given time position. </p>
 </td>
</tr>
<tr id="row639009217093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad1574e5769b3174c2103a2a8b49e20d4a98aa52abc293a28728ef9d2e9019ae7d"><a name="ggad1574e5769b3174c2103a2a8b49e20d4a98aa52abc293a28728ef9d2e9019ae7d"></a><a name="ggad1574e5769b3174c2103a2a8b49e20d4a98aa52abc293a28728ef9d2e9019ae7d"></a></strong>PLAYER_SEEK_NEXT_SYNC </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1161989491093523"><a name="p1161989491093523"></a><a name="p1161989491093523"></a>Moves the media position to the latest synchronization frame located after the given time position. </p>
 </td>
</tr>
<tr id="row784950949093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad1574e5769b3174c2103a2a8b49e20d4ae6257ed93e90e2231eb3369a36027872"><a name="ggad1574e5769b3174c2103a2a8b49e20d4ae6257ed93e90e2231eb3369a36027872"></a><a name="ggad1574e5769b3174c2103a2a8b49e20d4ae6257ed93e90e2231eb3369a36027872"></a></strong>PLAYER_SEEK_CLOSEST_SYNC </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p407822785093523"><a name="p407822785093523"></a><a name="p407822785093523"></a>Moves the media position to the latest synchronization frame located before or after the given time position. </p>
 </td>
</tr>
<tr id="row1368108200093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad1574e5769b3174c2103a2a8b49e20d4a0f6165a7f22f44f78bbb9004f2a55428"><a name="ggad1574e5769b3174c2103a2a8b49e20d4a0f6165a7f22f44f78bbb9004f2a55428"></a><a name="ggad1574e5769b3174c2103a2a8b49e20d4a0f6165a7f22f44f78bbb9004f2a55428"></a></strong>PLAYER_SEEK_CLOSEST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720863966093523"><a name="p1720863966093523"></a><a name="p1720863966093523"></a>Moves the media position to the latest frame located before or after the given time position. </p>
 </td>
</tr>
<tr id="row1815321141093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad1574e5769b3174c2103a2a8b49e20d4ada8db6c3cb45acbc0ff09cb3fe65fd94"><a name="ggad1574e5769b3174c2103a2a8b49e20d4ada8db6c3cb45acbc0ff09cb3fe65fd94"></a><a name="ggad1574e5769b3174c2103a2a8b49e20d4ada8db6c3cb45acbc0ff09cb3fe65fd94"></a></strong>PLAYER_SEEK_FRAME_INDEX </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334033132093523"><a name="p334033132093523"></a><a name="p334033132093523"></a>Moves the media position to a given frame index. </p>
 </td>
</tr>
</tbody>
</table>

## PlayerStates<a name="ga8b1147e57c4a67f63f193836302da2b7"></a>

```
enum [OHOS::Media::PlayerStates](multimedia_player.md#ga8b1147e57c4a67f63f193836302da2b7) : uint32_t
```

 **Description:**

Enumerates player states. 

<a name="table2034249172093523"></a>
<table><thead align="left"><tr id="row1076103015093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p410408610093523"><a name="p410408610093523"></a><a name="p410408610093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p888885027093523"><a name="p888885027093523"></a><a name="p888885027093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row130615901093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a53755dd964e67b38f2b20a73043c6a15"><a name="gga8b1147e57c4a67f63f193836302da2b7a53755dd964e67b38f2b20a73043c6a15"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a53755dd964e67b38f2b20a73043c6a15"></a></strong>PLAYER_STATE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1649030850093523"><a name="p1649030850093523"></a><a name="p1649030850093523"></a>Error </p>
 </td>
</tr>
<tr id="row116772091093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a422de416a9d98b7a11334080277e5a91"><a name="gga8b1147e57c4a67f63f193836302da2b7a422de416a9d98b7a11334080277e5a91"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a422de416a9d98b7a11334080277e5a91"></a></strong>PLAYER_IDLE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1961211234093523"><a name="p1961211234093523"></a><a name="p1961211234093523"></a>Idle </p>
 </td>
</tr>
<tr id="row2047290680093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a9b85bb17a31e74c8913d3344a9890968"><a name="gga8b1147e57c4a67f63f193836302da2b7a9b85bb17a31e74c8913d3344a9890968"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a9b85bb17a31e74c8913d3344a9890968"></a></strong>PLAYER_INITIALIZED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p695559566093523"><a name="p695559566093523"></a><a name="p695559566093523"></a>Initialized </p>
 </td>
</tr>
<tr id="row229961965093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a5f58beea6c3cfd9faf9d9dacb6d0de43"><a name="gga8b1147e57c4a67f63f193836302da2b7a5f58beea6c3cfd9faf9d9dacb6d0de43"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a5f58beea6c3cfd9faf9d9dacb6d0de43"></a></strong>PLAYER_PREPARING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308499566093523"><a name="p1308499566093523"></a><a name="p1308499566093523"></a>Preparing </p>
 </td>
</tr>
<tr id="row1623422409093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a992920b7152bf85ce28b0cbc2204a01b"><a name="gga8b1147e57c4a67f63f193836302da2b7a992920b7152bf85ce28b0cbc2204a01b"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a992920b7152bf85ce28b0cbc2204a01b"></a></strong>PLAYER_PREPARED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417216778093523"><a name="p1417216778093523"></a><a name="p1417216778093523"></a>Prepared </p>
 </td>
</tr>
<tr id="row1077135938093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7ab59f150a877432470b368cb6ae3c01d6"><a name="gga8b1147e57c4a67f63f193836302da2b7ab59f150a877432470b368cb6ae3c01d6"></a><a name="gga8b1147e57c4a67f63f193836302da2b7ab59f150a877432470b368cb6ae3c01d6"></a></strong>PLAYER_STARTED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519597822093523"><a name="p519597822093523"></a><a name="p519597822093523"></a>Playback started </p>
 </td>
</tr>
<tr id="row754091465093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a865415ef0c33b942431a1814e84dd848"><a name="gga8b1147e57c4a67f63f193836302da2b7a865415ef0c33b942431a1814e84dd848"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a865415ef0c33b942431a1814e84dd848"></a></strong>PLAYER_PAUSED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p627741319093523"><a name="p627741319093523"></a><a name="p627741319093523"></a>Playback paused </p>
 </td>
</tr>
<tr id="row1755931028093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7a0d79ba704b9048d53deee264f6e6546d"><a name="gga8b1147e57c4a67f63f193836302da2b7a0d79ba704b9048d53deee264f6e6546d"></a><a name="gga8b1147e57c4a67f63f193836302da2b7a0d79ba704b9048d53deee264f6e6546d"></a></strong>PLAYER_STOPPED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424606401093523"><a name="p424606401093523"></a><a name="p424606401093523"></a>Playback stopped </p>
 </td>
</tr>
<tr id="row137059613093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga8b1147e57c4a67f63f193836302da2b7ac5e465735c926d57e1bcb39eff208e51"><a name="gga8b1147e57c4a67f63f193836302da2b7ac5e465735c926d57e1bcb39eff208e51"></a><a name="gga8b1147e57c4a67f63f193836302da2b7ac5e465735c926d57e1bcb39eff208e51"></a></strong>PLAYER_PLAYBACK_COMPLETE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p828944934093523"><a name="p828944934093523"></a><a name="p828944934093523"></a>Playback completed </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section259107024093523"></a>

## EnableSingleLooping\(\)<a name="gae19989aa6e80b768acd4eb019a2b60d2"></a>

```
int32_t OHOS::Media::Player::EnableSingleLooping (bool loop)
```

 **Description:**

Sets loop playback. 

**Parameters:**

<a name="table1802830390093523"></a>
<table><thead align="left"><tr id="row2018496823093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p158502029093523"><a name="p158502029093523"></a><a name="p158502029093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1520042485093523"><a name="p1520042485093523"></a><a name="p1520042485093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1141966282093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">loop</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to enable loop playback. The value <strong id="b1222046246093523"><a name="b1222046246093523"></a><a name="b1222046246093523"></a>true</strong> means to enable loop playback, and <strong id="b385426198093523"><a name="b385426198093523"></a><a name="b385426198093523"></a>false</strong> means to disable loop playback. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns  **-1**  otherwise. 



## GetCurrentTime\(\)<a name="ga8474b117a4c1bf5749406f26056b4802"></a>

```
int32_t OHOS::Media::Player::GetCurrentTime (int64_t & time) const
```

 **Description:**

Obtains the playback position, accurate to millisecond. 

**Parameters:**

<a name="table1329249651093523"></a>
<table><thead align="left"><tr id="row1222280905093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p942358197093523"><a name="p942358197093523"></a><a name="p942358197093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p529273312093523"><a name="p529273312093523"></a><a name="p529273312093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1663229171093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the playback position. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the playback position is obtained; returns  **-1**  otherwise. 



## GetDuration\(\)<a name="ga24ae07f65da4dafc4ec5aa28321625d8"></a>

```
int32_t OHOS::Media::Player::GetDuration (int64_t & duration) const
```

 **Description:**

Obtains the total duration of media files, in milliseconds. 

**Parameters:**

<a name="table1058459693093523"></a>
<table><thead align="left"><tr id="row482664770093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p982140462093523"><a name="p982140462093523"></a><a name="p982140462093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1954739454093523"><a name="p1954739454093523"></a><a name="p1954739454093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row248554127093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">duration</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the total duration of media files. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the total duration is obtained; returns  **-1**  otherwise. 



## GetVideoHeight\(\)<a name="ga726adc32a34134b30aabfbdb389c8357"></a>

```
int32_t OHOS::Media::Player::GetVideoHeight (int32_t & videoHeight)
```

 **Description:**

Obtains the height of the video. 

**Parameters:**

<a name="table1104202973093523"></a>
<table><thead align="left"><tr id="row1453849581093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p692123080093523"><a name="p692123080093523"></a><a name="p692123080093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p808693851093523"><a name="p808693851093523"></a><a name="p808693851093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2016033280093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">videoHeight</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video height. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the video height is obtained; returns  **-1**  otherwise. 



## GetVideoWidth\(\)<a name="ga9ed94bd43d896fa10066497377d7fbda"></a>

```
int32_t OHOS::Media::Player::GetVideoWidth (int32_t & videoWidth)
```

 **Description:**

Obtains the width of the video. 

**Parameters:**

<a name="table811241808093523"></a>
<table><thead align="left"><tr id="row149212346093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p851477523093523"><a name="p851477523093523"></a><a name="p851477523093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2020134962093523"><a name="p2020134962093523"></a><a name="p2020134962093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row479614329093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">videoWidth</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video width. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the video width is obtained; returns  **-1**  otherwise. 



## IsPlaying\(\)<a name="gaad6b2c35b1d5dfe453d158f7ff9e1379"></a>

```
bool OHOS::Media::Player::IsPlaying ()
```

 **Description:**

Checks whether the player is playing. 

**Returns:**

Returns  **true**  if the player is playing; returns  **false**  otherwise. 



## IsSingleLooping\(\)<a name="gae4dd5d8fb92c836f5304f181a40b34d2"></a>

```
bool OHOS::Media::Player::IsSingleLooping ()
```

 **Description:**

Checks whether the player is looping. 

**Returns:**

Returns  **true**  if the player is looping; returns  **false**  otherwise. 



## OnError\(\)<a name="ga3d0fdad57045f5e049b56de031d3e0fb"></a>

```
virtual void OHOS::Media::PlayerCallback::OnError (int32_t errorType, int32_t errorCode )
```

 **Description:**

Called when a playback error occurs. 

**Parameters:**

<a name="table1401251150093523"></a>
<table><thead align="left"><tr id="row194672112093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1526285333093523"><a name="p1526285333093523"></a><a name="p1526285333093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1729468952093523"><a name="p1729468952093523"></a><a name="p1729468952093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1104451189093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error type. For details, see <strong id="b912868517093523"><a name="b912868517093523"></a><a name="b912868517093523"></a>PlayerErrorType</strong>. </td>
</tr>
<tr id="row987208970093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error code. </td>
</tr>
</tbody>
</table>

## OnInfo\(\)<a name="gad2d3466c8a17ee4d622b87fa6a31b2bb"></a>

```
virtual void OHOS::Media::PlayerCallback::OnInfo (int type, int extra )
```

 **Description:**

Called when playback information is received. 

**Parameters:**

<a name="table738581735093523"></a>
<table><thead align="left"><tr id="row504349483093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p760321514093523"><a name="p760321514093523"></a><a name="p760321514093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p331578673093523"><a name="p331578673093523"></a><a name="p331578673093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1714126022093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the information type. For details, see <a href="multimedia_player.md#ga7dac9dac65cbbea7e411adcf2c314ac5">PlayerInfoType</a>. </td>
</tr>
<tr id="row222619207093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">extra</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the information code. </td>
</tr>
</tbody>
</table>

## OnPlaybackComplete\(\)<a name="ga3b56f618340bf9a5590e6142b2311302"></a>

```
virtual void OHOS::Media::PlayerCallback::OnPlaybackComplete ()
```

 **Description:**

Called when the playback is complete. 

## OnRewindToComplete\(\)<a name="ga765c499e47dfaad5e557197e964eaca3"></a>

```
virtual void OHOS::Media::PlayerCallback::OnRewindToComplete ()
```

 **Description:**

Called when the rewind is complete. 

## OnVideoSizeChanged\(\)<a name="gac5b641f93621d90e616d18adaa016e8a"></a>

```
virtual void OHOS::Media::PlayerCallback::OnVideoSizeChanged (int width, int height )
```

 **Description:**

Called when the video image size changes. 

**Parameters:**

<a name="table1865748940093523"></a>
<table><thead align="left"><tr id="row1364061419093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p62663619093523"><a name="p62663619093523"></a><a name="p62663619093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p810514317093523"><a name="p810514317093523"></a><a name="p810514317093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1216700828093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">width</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video width. </td>
</tr>
<tr id="row2107565558093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">height</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the video height. </td>
</tr>
</tbody>
</table>

## Pause\(\)<a name="gae1d2225ce60a9737cc902e586138a44f"></a>

```
int32_t OHOS::Media::Player::Pause ()
```

 **Description:**

Pauses playback. 

**Returns:**

Returns  **0**  if the playback is paused; returns  **-1**  otherwise. 



## Play\(\)<a name="gafecbbfe85c70cf4983f52d55b7205e3f"></a>

```
int32_t OHOS::Media::Player::Play ()
```

 **Description:**

Starts or resumes playback. 

This function must be called after  [Prepare](multimedia_player.md#gade9bff3268e1c409273749a90700e056). If the player state is  **Prepared**, this function is called to start playback. If the player state is  **Playback paused**, this function is called to resume playback. If the media is playing in an abnormal speed, this function is called to restore the playback speed to normal.

**Returns:**

Returns  **0**  if the playback starts or resumes; returns  **-1**  otherwise. 



## Prepare\(\)<a name="gade9bff3268e1c409273749a90700e056"></a>

```
int32_t OHOS::Media::Player::Prepare ()
```

 **Description:**

Prepares the playback environment and buffers media data. 

This function must be called after  [SetSource](multimedia_player.md#gacce284eac910970e405151fd3a1963c0).

**Returns:**

Returns  **0**  if the playback environment is prepared and media data is buffered; returns  **-1**  otherwise. 



## Release\(\)<a name="ga00e24c0faed483c9d54e416ec2ffe6ac"></a>

```
int32_t OHOS::Media::Player::Release ()
```

 **Description:**

Releases player resources. 

**Returns:**

Returns  **0**  if player resources are released; returns  **-1**  otherwise. 



## Reset\(\)<a name="ga75e17ee0068d46d44a30709609821b85"></a>

```
int32_t OHOS::Media::Player::Reset ()
```

 **Description:**

Restores the player to the initial state. 

**Returns:**

Returns  **0**  if the player is restored; returns  **-1**  otherwise. 



## Rewind\(\)<a name="ga406b6277d1e160e691d01f5f740480b3"></a>

```
int32_t OHOS::Media::Player::Rewind (int64_t mSeconds, int32_t mode )
```

 **Description:**

Changes the playback position. 

This function can be used during playback or pause.

**Parameters:**

<a name="table1120276694093523"></a>
<table><thead align="left"><tr id="row568175111093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p312047219093523"><a name="p312047219093523"></a><a name="p312047219093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1427646125093523"><a name="p1427646125093523"></a><a name="p1427646125093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1210777311093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mSeconds</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target playback position, accurate to second. </td>
</tr>
<tr id="row1961722149093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the player seek mode. For details, see <strong id="b922371288093523"><a name="b922371288093523"></a><a name="b922371288093523"></a>PlayerSeekMode</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the playback position is changed; returns  **-1**  otherwise. 



## SetPlayerCallback\(\)<a name="gabb6eca611514d5fc0b66df5ff2d70c2b"></a>

```
void OHOS::Media::Player::SetPlayerCallback (const std::shared_ptr< [PlayerCallback](ohos-media-playercallback.md) > & cb)
```

 **Description:**

Registers a listener to receive events and exception notifications from the player. 

**Parameters:**

<a name="table102551059093523"></a>
<table><thead align="left"><tr id="row767685888093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1580801889093523"><a name="p1580801889093523"></a><a name="p1580801889093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p565006343093523"><a name="p565006343093523"></a><a name="p565006343093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1236656378093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the listener to register. For details, see <a href="ohos-media-playercallback.md">PlayerCallback</a>. </td>
</tr>
</tbody>
</table>

## SetSource\(\)<a name="gacce284eac910970e405151fd3a1963c0"></a>

```
int32_t OHOS::Media::Player::SetSource (const [Source](ohos-media-source.md) & source)
```

 **Description:**

Sets the playback source for the player. The corresponding source can be the file descriptor \(FD\) of the local file, local file URI, network URI, or media stream. 

**Parameters:**

<a name="table39316010093523"></a>
<table><thead align="left"><tr id="row1583669962093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1296645382093523"><a name="p1296645382093523"></a><a name="p1296645382093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p294894130093523"><a name="p294894130093523"></a><a name="p294894130093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row839137170093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">source</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the playback source. Currently, only local file URIs and media streams are supported. For details, see <a href="ohos-media-source.md">Source</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns  **-1**  otherwise. 



## SetVideoSurface\(\)<a name="gac9d62210915ebcf3b462574302018501"></a>

```
int32_t OHOS::Media::Player::SetVideoSurface ([Surface](ohos-surface.md) * surface)
```

 **Description:**

Sets a surface for video playback. 

**Parameters:**

<a name="table2011638761093523"></a>
<table><thead align="left"><tr id="row1276407228093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1970847770093523"><a name="p1970847770093523"></a><a name="p1970847770093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p393747016093523"><a name="p393747016093523"></a><a name="p393747016093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2091612498093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">surface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the surface to set. For details, see <a href="surface.md">Surface</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns  **-1**  otherwise. 



## SetVolume\(\)<a name="ga23ca57f0b1a288980e37153274c5f8b3"></a>

```
int32_t OHOS::Media::Player::SetVolume (float leftVolume, float rightVolume )
```

 **Description:**

Sets the volume of the player. 

This function can be used during playback or pause. The value  **0**  indicates no sound, and  **100**  indicates the original volume. If no audio device is started or no audio stream exists, the value  **-1**  is returned.

**Parameters:**

<a name="table2078609562093523"></a>
<table><thead align="left"><tr id="row611036490093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p309215691093523"><a name="p309215691093523"></a><a name="p309215691093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1070953914093523"><a name="p1070953914093523"></a><a name="p1070953914093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1630938742093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">leftVolume</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target volume of the left audio channel to set, ranging from 0 to 300. </td>
</tr>
<tr id="row326345371093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rightVolume</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target volume of the right audio channel to set, ranging from 0 to 300. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns  **-1**  otherwise. 



## Stop\(\)<a name="gafe518a5b909ac0f0f066781caa3b55aa"></a>

```
int32_t OHOS::Media::Player::Stop ()
```

 **Description:**

Stops playback. 

**Returns:**

Returns  **0**  if the playback is stopped; returns  **-1**  otherwise. 



