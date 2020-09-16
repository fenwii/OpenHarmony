# Audio and Video Recording Development Guide<a name="EN-US_TOPIC_0000001052170566"></a>

## When to Use<a name="section186634310418"></a>

Audio and video recording is used to record audio and video and encapsulate output files based on the configured encoding format, sampling rate, and bit rate.

## Available APIs<a name="section125479541744"></a>

The audio and video recording APIs are as follows. For details about the APIs, see the interface document.

**Table  1**  Audio and Video Recording APIs

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="7.5200000000000005%" id="mcps1.2.4.1.1"><p id="p531591918714"><a name="p531591918714"></a><a name="p531591918714"></a>API</p>
</th>
<th class="cellrowborder" valign="top" width="53.06999999999999%" id="mcps1.2.4.1.2"><p id="p1325118401591"><a name="p1325118401591"></a><a name="p1325118401591"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="39.410000000000004%" id="mcps1.2.4.1.3"><p id="p1251184013912"><a name="p1251184013912"></a><a name="p1251184013912"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row34145016535"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p113157191379"><a name="p113157191379"></a><a name="p113157191379"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p425115401998"><a name="p425115401998"></a><a name="p425115401998"></a>static Recorder *CreateRecorder()</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p225104017920"><a name="p225104017920"></a><a name="p225104017920"></a>Creates a Recorder instance.</p>
</td>
</tr>
<tr id="row1746172917474"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p1712917411310"><a name="p1712917411310"></a><a name="p1712917411310"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p925111401895"><a name="p925111401895"></a><a name="p925111401895"></a>int32_t SetVideoSource(VideoSourceType source, int32_t &amp;sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p152511640691"><a name="p152511640691"></a><a name="p152511640691"></a>Setting a Video Source for Recording</p>
</td>
</tr>
<tr id="row10992232154714"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p8129156111319"><a name="p8129156111319"></a><a name="p8129156111319"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p1776173711119"><a name="p1776173711119"></a><a name="p1776173711119"></a>int32_t SetVideoEncoder(int32_t sourceId, VideoCodecFormat encoder)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p127623791116"><a name="p127623791116"></a><a name="p127623791116"></a>Sets the type of the video encoder for recording.</p>
</td>
</tr>
<tr id="row933265824817"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p944717831310"><a name="p944717831310"></a><a name="p944717831310"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p6769371110"><a name="p6769371110"></a><a name="p6769371110"></a>int32_t SetVideoSize(int32_t sourceId, int32_t width, int32_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p17761137181115"><a name="p17761137181115"></a><a name="p17761137181115"></a>Sets the width and height of the recorded video.</p>
</td>
</tr>
<tr id="row124766591190"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p18795111319132"><a name="p18795111319132"></a><a name="p18795111319132"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p476113791113"><a name="p476113791113"></a><a name="p476113791113"></a>int32_t SetVideoFrameRate(int32_t sourceId, int32_t frameRate)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p107613711114"><a name="p107613711114"></a><a name="p107613711114"></a>Sets the frame rate of the video to be recorded.</p>
</td>
</tr>
<tr id="row0260140101"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p149767151136"><a name="p149767151136"></a><a name="p149767151136"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p1076203717112"><a name="p1076203717112"></a><a name="p1076203717112"></a>int32_t SetVideoEncodingBitRate(int32_t sourceId, int32_t rate)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p0761637141116"><a name="p0761637141116"></a><a name="p0761637141116"></a>Sets the encoding bit rate of the recorded video.</p>
</td>
</tr>
<tr id="row22024106107"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p177997175138"><a name="p177997175138"></a><a name="p177997175138"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p5761737171112"><a name="p5761737171112"></a><a name="p5761737171112"></a>int32_t SetCaptureRate(int32_t sourceId, double fps)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1761737151111"><a name="p1761737151111"></a><a name="p1761737151111"></a>Sets the frame capture rate of video frames.</p>
</td>
</tr>
<tr id="row82261213191012"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p94271121181318"><a name="p94271121181318"></a><a name="p94271121181318"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p1129110237225"><a name="p1129110237225"></a><a name="p1129110237225"></a>std::shared_ptr&lt;OHOS::Surface&gt; GetSurface(int32_t sourceId);</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1876163710115"><a name="p1876163710115"></a><a name="p1876163710115"></a>Obtains the surface of the corresponding input source.</p>
</td>
</tr>
<tr id="row1366261518102"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p13158202312139"><a name="p13158202312139"></a><a name="p13158202312139"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p4761377117"><a name="p4761377117"></a><a name="p4761377117"></a>int32_t SetAudioSource(AudioSourceType source, int32_t &amp;sourceId)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p5765377117"><a name="p5765377117"></a><a name="p5765377117"></a>Set the audio source for recording.</p>
</td>
</tr>
<tr id="row7142161861017"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p2897162514139"><a name="p2897162514139"></a><a name="p2897162514139"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p8766372113"><a name="p8766372113"></a><a name="p8766372113"></a>int32_t SetAudioEncoder(int32_t sourceId, AudioCodecFormat encoder)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p127693731115"><a name="p127693731115"></a><a name="p127693731115"></a>Sets the type of the audio encoder for recording.</p>
</td>
</tr>
<tr id="row2053832071012"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p952618270132"><a name="p952618270132"></a><a name="p952618270132"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p976937141112"><a name="p976937141112"></a><a name="p976937141112"></a>int32_t SetAudioSampleRate(int32_t sourceId, int32_t rate)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1476183781110"><a name="p1476183781110"></a><a name="p1476183781110"></a>Sets the audio sampling rate for recording.</p>
</td>
</tr>
<tr id="row55394243108"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p677717304137"><a name="p677717304137"></a><a name="p677717304137"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p47703781114"><a name="p47703781114"></a><a name="p47703781114"></a>int32_t SetAudioChannels(int32_t sourceId, int32_t num)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p16772037121111"><a name="p16772037121111"></a><a name="p16772037121111"></a>Sets the number of audio channels to be recorded.</p>
</td>
</tr>
<tr id="row191791427121015"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p1759610327139"><a name="p1759610327139"></a><a name="p1759610327139"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p37723781118"><a name="p37723781118"></a><a name="p37723781118"></a>int32_t SetAudioEncodingBitRate(int32_t sourceId, int32_t bitRate)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p17771378113"><a name="p17771378113"></a><a name="p17771378113"></a>Sets the encoding bit rate of the recorded audio.</p>
</td>
</tr>
<tr id="row83478305107"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p16968193391311"><a name="p16968193391311"></a><a name="p16968193391311"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p1536305312114"><a name="p1536305312114"></a><a name="p1536305312114"></a>int32_t SetMaxDuration(int32_t duration)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p93634532118"><a name="p93634532118"></a><a name="p93634532118"></a>Sets the maximum duration of a recorded file.</p>
</td>
</tr>
<tr id="row592711339103"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p947593614139"><a name="p947593614139"></a><a name="p947593614139"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p1436314531119"><a name="p1436314531119"></a><a name="p1436314531119"></a>int32_t SetOutputFormat(OutputFormatType format)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1936315331119"><a name="p1936315331119"></a><a name="p1936315331119"></a>Sets the output file format.</p>
</td>
</tr>
<tr id="row15219377106"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p552463917132"><a name="p552463917132"></a><a name="p552463917132"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p33631253121116"><a name="p33631253121116"></a><a name="p33631253121116"></a>int32_t SetOutputFile(int32_t fd)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p336335351111"><a name="p336335351111"></a><a name="p336335351111"></a>Sets the FD of the output file.</p>
</td>
</tr>
<tr id="row18755438101013"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p121613438137"><a name="p121613438137"></a><a name="p121613438137"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p14363175317114"><a name="p14363175317114"></a><a name="p14363175317114"></a>int32_t SetNextOutputFile(int32_t fd);</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p236375361119"><a name="p236375361119"></a><a name="p236375361119"></a>Sets the fd of the next output file.</p>
</td>
</tr>
<tr id="row14480241101010"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p07641457131"><a name="p07641457131"></a><a name="p07641457131"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p2363145317112"><a name="p2363145317112"></a><a name="p2363145317112"></a>int32_t SetMaxFileSize(int64_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p43646539114"><a name="p43646539114"></a><a name="p43646539114"></a>Sets the maximum file size of a recording session.</p>
</td>
</tr>
<tr id="row835564418101"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p2104174817136"><a name="p2104174817136"></a><a name="p2104174817136"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p15364195315118"><a name="p15364195315118"></a><a name="p15364195315118"></a>int32_t SetRecorderCallback(const std::shared_ptr&lt;RecorderCallback&gt; &amp;callback)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1636412538119"><a name="p1636412538119"></a><a name="p1636412538119"></a>Registers the recording listener callback function.</p>
</td>
</tr>
<tr id="row780144661014"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p098351816145"><a name="p098351816145"></a><a name="p098351816145"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p173641153151110"><a name="p173641153151110"></a><a name="p173641153151110"></a>int32_t Prepare()</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p636495341115"><a name="p636495341115"></a><a name="p636495341115"></a>Prepare for recording.</p>
</td>
</tr>
<tr id="row11537184971012"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p12815320121418"><a name="p12815320121418"></a><a name="p12815320121418"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p53641053151113"><a name="p53641053151113"></a><a name="p53641053151113"></a>int32_t Start()</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p53642536114"><a name="p53642536114"></a><a name="p53642536114"></a>Starts recording.</p>
</td>
</tr>
<tr id="row158225271018"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p132682201410"><a name="p132682201410"></a><a name="p132682201410"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p936485351112"><a name="p936485351112"></a><a name="p936485351112"></a>int32_t Pause()</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p183641253141110"><a name="p183641253141110"></a><a name="p183641253141110"></a>Pauses recording.</p>
</td>
</tr>
<tr id="row15938254131016"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p12615824111414"><a name="p12615824111414"></a><a name="p12615824111414"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p123641153191115"><a name="p123641153191115"></a><a name="p123641153191115"></a>int32_t Resume()</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p0364195331116"><a name="p0364195331116"></a><a name="p0364195331116"></a>Resumes recording.</p>
</td>
</tr>
<tr id="row193212569102"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p15373202761415"><a name="p15373202761415"></a><a name="p15373202761415"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p63641653101116"><a name="p63641653101116"></a><a name="p63641653101116"></a>int32_t Stop(bool block)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1364053171112"><a name="p1364053171112"></a><a name="p1364053171112"></a>Stops recording.</p>
</td>
</tr>
<tr id="row1392185911103"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p199881728181420"><a name="p199881728181420"></a><a name="p199881728181420"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p143641539114"><a name="p143641539114"></a><a name="p143641539114"></a>int32_t Reset();</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p20364353131115"><a name="p20364353131115"></a><a name="p20364353131115"></a>Resets recording.</p>
</td>
</tr>
<tr id="row816014171116"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p193259303141"><a name="p193259303141"></a><a name="p193259303141"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p183649535111"><a name="p183649535111"></a><a name="p183649535111"></a>int32_t Release()</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p1036420534111"><a name="p1036420534111"></a><a name="p1036420534111"></a>Releasing Recording Resources</p>
</td>
</tr>
<tr id="row115981253112"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p1466416312142"><a name="p1466416312142"></a><a name="p1466416312142"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p17364053171110"><a name="p17364053171110"></a><a name="p17364053171110"></a>int32_t SetFileSplitDuration(FileSplitType type, int64_t timestamp, uint32_t duration)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p8364205361117"><a name="p8364205361117"></a><a name="p8364205361117"></a>Setting Split Recording</p>
</td>
</tr>
<tr id="row1677310915111"><td class="cellrowborder" valign="top" width="7.5200000000000005%" headers="mcps1.2.4.1.1 "><p id="p1028316364149"><a name="p1028316364149"></a><a name="p1028316364149"></a>Recorder</p>
</td>
<td class="cellrowborder" valign="top" width="53.06999999999999%" headers="mcps1.2.4.1.2 "><p id="p1936411531111"><a name="p1936411531111"></a><a name="p1936411531111"></a>int32_t SetParameter(int32_t sourceId, const Format &amp;format)</p>
</td>
<td class="cellrowborder" valign="top" width="39.410000000000004%" headers="mcps1.2.4.1.3 "><p id="p13657530118"><a name="p13657530118"></a><a name="p13657530118"></a>Sets the extended recording parameters.</p>
</td>
</tr>
</tbody>
</table>

## Limitations and Constraints<a name="section1165911177314"></a>

None

## How to Develop<a name="section34171333656"></a>

1.  This API is used to create a Recorder instance.

    ```
    Recorder *recorder = Recorder::CreateRecorder();
    ```

2.  Sets Recorder parameters, including the audio and video source information, audio and video encoding format, sampling rate, bit rate, and video width and height.

    ```
    int32_t sampleRate = 48000; 
    int32_t channelCount = 1;
    AudioCodecFormat audioFormat = AAC_LC;
    AudioSourceType inputSource = AUDIO_MIC;
    int32_t audioEncodingBitRate = sampleRate;
    VideoSourceType source = VIDEO_SOURCE_SURFACE_ES;
    int32_t frameRate = 30;
    float fps = 30;
    int32_t rate = 4096;
    int32_t sourceId = 0;
    int32_t audioSourceId = 0;
    int32_t width = 1920;
    int32_t height = 1080;
    VideoCodecFormat encoder = H264;
    recorder->SetVideoSource(source, sourceId); // Set the video source and obtain the sourceId.
    recorder->SetVideoEncoder(sourceId, encoder); // Set the video encoding format.
    recorder->SetVideoSize(sourceId, width, height); // Set the video width and height.
    recorder->SetVideoFrameRate(sourceId, frameRate); // Set the video frame rate.
    recorder->SetVideoEncodingBitRate(sourceId, rate); //: Sets the video encoding bit rate.
    recorder->SetCaptureRate(sourceId, frameRate); //: Sets the frame capture rate of video frames.
    recorder->SetAudioSource(inputSource, audioSourceId); // Set the audio source and obtain audioSourceId.
    recorder->SetAudioEncoder(audioSourceId, audioFormat); // Set the audio encoding format.
    recorder->SetAudioSampleRate(audioSourceId, sampleRate); // Set the audio sampling rate.
    recorder->SetAudioChannels(audioSourceId, channelCount); // Set the number of audio channels.
    recorder->SetAudioEncodingBitRate(audioSourceId, audioEncodingBitRate); // Set the audio encoding bit rate.
    ```

3.  Prepare for the recording. The Recorder prepares for the recording.

    ```
    recorder->Prepare(); // Prepares for recording.
    ```

4.  The Recorder starts recording based on the configured audio and video sources.

    ```
    recorder->Start(); // Start recording.
    ```

5.  Stop recording and release resources.

    ```
    recorder->Stop(); // Stop recording.
    recorder->Release(); // Release recording resources.
    ```


