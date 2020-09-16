# codec\_type.h<a name="EN-US_TOPIC_0000001055678056"></a>

## **Overview**<a name="section941650635084828"></a>

**Related Modules:**

[Codec](codec.md)

**Description:**

Declares custom data types used in API declarations for the Codec module, including the codec types, audio and video parameters, input and output data, and callbacks.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section156486532084828"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1797538828084828"></a>
<table><thead align="left"><tr id="row1960046574084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2016152428084828"><a name="p2016152428084828"></a><a name="p2016152428084828"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p320254296084828"><a name="p320254296084828"></a><a name="p320254296084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1507323575084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p959172643084828"><a name="p959172643084828"></a><a name="p959172643084828"></a><a href="en-us_topic_0000001054718161.md">Param</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135408201084828"><a name="p2135408201084828"></a><a name="p2135408201084828"></a>Describes the dynamic parameter structure, which is mainly used by <a href="codec.md#ga74aa0395a51f004390f7a92fb68faddd">CodecCreate</a> and <a href="codec.md#gaa080cf23aa5f77b30f3b90a026d97cc0">CodecSetParameter</a>.</p>
</td>
</tr>
<tr id="row1575246798084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037143404084828"><a name="p2037143404084828"></a><a name="p2037143404084828"></a><a href="en-us_topic_0000001054918147.md">BufferHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223091105084828"><a name="p1223091105084828"></a><a name="p1223091105084828"></a>Defines the buffer handle type. The virtual address of a handle maps to its physical address.</p>
</td>
</tr>
<tr id="row529450492084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1668235956084828"><a name="p1668235956084828"></a><a name="p1668235956084828"></a><a href="en-us_topic_0000001054879526.md">CodecBufferInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p815791496084828"><a name="p815791496084828"></a><a name="p815791496084828"></a>Describes buffer information.</p>
</td>
</tr>
<tr id="row492461023084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416751397084828"><a name="p416751397084828"></a><a name="p416751397084828"></a><a href="en-us_topic_0000001054879536.md">InputInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030849217084828"><a name="p1030849217084828"></a><a name="p1030849217084828"></a>Describes input information.</p>
</td>
</tr>
<tr id="row734818250084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2068273710084828"><a name="p2068273710084828"></a><a name="p2068273710084828"></a><a href="en-us_topic_0000001054918167.md">OutputInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p576393773084828"><a name="p576393773084828"></a><a name="p576393773084828"></a>Describes output information.</p>
</td>
</tr>
<tr id="row1044254700084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1117144018084828"><a name="p1117144018084828"></a><a name="p1117144018084828"></a><a href="en-us_topic_0000001054879568.md">ResizableArray</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946005268084828"><a name="p1946005268084828"></a><a name="p1946005268084828"></a>Defines a variable-length queue.</p>
</td>
</tr>
<tr id="row1156818827084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994543800084828"><a name="p1994543800084828"></a><a name="p1994543800084828"></a><a href="en-us_topic_0000001054598149.md">Alginment</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478497806084828"><a name="p478497806084828"></a><a name="p478497806084828"></a>Defines the alignment.</p>
</td>
</tr>
<tr id="row1962880116084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256269643084828"><a name="p256269643084828"></a><a name="p256269643084828"></a><a href="en-us_topic_0000001055198166.md">Rect</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623223572084828"><a name="p623223572084828"></a><a name="p623223572084828"></a>Defines a rectangle.</p>
</td>
</tr>
<tr id="row540426967084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p273022189084828"><a name="p273022189084828"></a><a name="p273022189084828"></a><a href="en-us_topic_0000001055198124.md">Capbility</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1482088597084828"><a name="p1482088597084828"></a><a name="p1482088597084828"></a>Defines the codec capability.</p>
</td>
</tr>
<tr id="row1557846678084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p172338824084828"><a name="p172338824084828"></a><a name="p172338824084828"></a><a href="en-us_topic_0000001055358102.md">CodecCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1116375387084828"><a name="p1116375387084828"></a><a name="p1116375387084828"></a>Defines callbacks and their parameters.</p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1370158063084828"></a>
<table><thead align="left"><tr id="row197878477084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p638249996084828"><a name="p638249996084828"></a><a name="p638249996084828"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p314751089084828"><a name="p314751089084828"></a><a name="p314751089084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1565602250084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933748438084828"><a name="p1933748438084828"></a><a name="p1933748438084828"></a><a href="codec.md#gab34cc95c32c06b8d63cfbe62247eb6e2">ELEMENT_MAX_LEN</a>   50</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086700054084828"><a name="p1086700054084828"></a><a name="p1086700054084828"></a>Indicates the maximum number of reserved parameters in the array.</p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1370201259084828"></a>
<table><thead align="left"><tr id="row341673077084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1026937632084828"><a name="p1026937632084828"></a><a name="p1026937632084828"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p565447302084828"><a name="p565447302084828"></a><a name="p565447302084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2029720066084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275951800084828"><a name="p275951800084828"></a><a name="p275951800084828"></a><a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844129728084828"><a name="p844129728084828"></a><a name="p844129728084828"></a>typedef void *</p>
<p id="p1234196025084828"><a name="p1234196025084828"></a><a name="p1234196025084828"></a>Defines the pointer to the codec handle, which is the context information for function calls.</p>
</td>
</tr>
<tr id="row1492830448084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140046084084828"><a name="p1140046084084828"></a><a name="p1140046084084828"></a><a href="codec.md#gadfdccaf7fd554ae1df6169bb622deb1d">ValueType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348147151084828"><a name="p348147151084828"></a><a name="p348147151084828"></a>typedef void *</p>
<p id="p88834049084828"><a name="p88834049084828"></a><a name="p88834049084828"></a>Defines the pointer to the type of the dynamic parameter value.</p>
</td>
</tr>
<tr id="row1979929749084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638176761084828"><a name="p1638176761084828"></a><a name="p1638176761084828"></a><a href="codec.md#ga5571ad9c720096768c508f1f38e2ef41">BufferHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2080957391084828"><a name="p2080957391084828"></a><a name="p2080957391084828"></a>typedef struct <a href="en-us_topic_0000001054918147.md">BufferHandle</a></p>
<p id="p1134054336084828"><a name="p1134054336084828"></a><a name="p1134054336084828"></a>Defines the buffer handle type. The virtual address of a handle maps to its physical address.</p>
</td>
</tr>
<tr id="row136474467084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1465066640084828"><a name="p1465066640084828"></a><a name="p1465066640084828"></a><a href="codec.md#ga8dc4e7c329ad589f25019ca03aed9925">BufferType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643176806084828"><a name="p1643176806084828"></a><a name="p1643176806084828"></a>typedef enum <a href="codec.md#gadf8e136713c0691010d2bec6ba63e9cf">BufferType</a></p>
<p id="p383458095084828"><a name="p383458095084828"></a><a name="p383458095084828"></a>Enumerates buffer types.</p>
</td>
</tr>
<tr id="row1619920573084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1125196664084828"><a name="p1125196664084828"></a><a name="p1125196664084828"></a><a href="codec.md#gab32442ed7057b2e9bd6b20ad35154cb8">OutputInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147926780084828"><a name="p1147926780084828"></a><a name="p1147926780084828"></a>typedef struct <a href="en-us_topic_0000001054918167.md">OutputInfo</a></p>
<p id="p931230207084828"><a name="p931230207084828"></a><a name="p931230207084828"></a>Describes output information.</p>
</td>
</tr>
<tr id="row613779929084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1746544163084828"><a name="p1746544163084828"></a><a name="p1746544163084828"></a><a href="codec.md#gaf59a3505491b6f0b5dff5d62372a9679">AllocateBufferMode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p134804684084828"><a name="p134804684084828"></a><a name="p134804684084828"></a>typedef enum <a href="codec.md#gaeae808d52153b2e33c6815162bbd11e0">AllocateBufferMode</a></p>
<p id="p2105226579084828"><a name="p2105226579084828"></a><a name="p2105226579084828"></a>Enumerates allocation modes of input and output buffers.</p>
</td>
</tr>
<tr id="row88912696084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p512745999084828"><a name="p512745999084828"></a><a name="p512745999084828"></a><a href="codec.md#ga09af5b0a9d5134ad4d44cbe8cbe7b887">CapsMask</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p661530515084828"><a name="p661530515084828"></a><a name="p661530515084828"></a>typedef enum <a href="codec.md#gae5751aa8514dcaf2217df12db5ef57a1">CapsMask</a></p>
<p id="p641914122084828"><a name="p641914122084828"></a><a name="p641914122084828"></a>Enumerates playback capabilities.</p>
</td>
</tr>
<tr id="row1795589246084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1784177652084828"><a name="p1784177652084828"></a><a name="p1784177652084828"></a><a href="codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3">CodecCapbility</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1623346095084828"><a name="p1623346095084828"></a><a name="p1623346095084828"></a>typedef struct <a href="en-us_topic_0000001055198124.md">Capbility</a></p>
<p id="p246137123084828"><a name="p246137123084828"></a><a name="p246137123084828"></a>Defines the codec capability.</p>
</td>
</tr>
<tr id="row282520749084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647005390084828"><a name="p647005390084828"></a><a name="p647005390084828"></a><a href="codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519963950084828"><a name="p519963950084828"></a><a name="p519963950084828"></a>typedef uintptr_t</p>
<p id="p405786549084828"><a name="p405786549084828"></a><a name="p405786549084828"></a>Redefines the unsigned pointer type, which is used for pointer conversion.</p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table462386074084828"></a>
<table><thead align="left"><tr id="row1723425185084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1364626928084828"><a name="p1364626928084828"></a><a name="p1364626928084828"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p247993325084828"><a name="p247993325084828"></a><a name="p247993325084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row140371928084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p212602410084828"><a name="p212602410084828"></a><a name="p212602410084828"></a><a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a> {   <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79a19c3c7765c55583a64e21938e2439261">VIDEO_DECODER</a>, <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79ad8044bc5b7d871723be90b5b6a094992">VIDEO_ENCODER</a>, <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79ae4ade329585f6c202847138e3f9cd4a4">AUDIO_DECODER</a>, <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79a7f7f3d3880168089c1de6d1ebc3dbb54">AUDIO_ENCODER</a>,   <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79a7314b0d0e4638eaaeb8690b8555a6546">INVALID_TYPE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175896515084828"><a name="p175896515084828"></a><a name="p175896515084828"></a>Enumerates codec types.</p>
</td>
</tr>
<tr id="row1605822419084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280070827084828"><a name="p280070827084828"></a><a name="p280070827084828"></a><a href="codec.md#ga575c56a2d6b42c48881cf47b0008d5a6">ParamKey</a> {   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6aef2a08e0112230b41df402fd38efc1ed">KEY_MIMETYPE</a> = 0x01, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a2c86d69eb4995dbadfdb6d289834f7f2">KEY_BUFFERSIZE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a4c97de4e44d3c9778530ddd2cffe1728">KEY_LEFT_STREAM_FRAMES</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ac3e2aece8c07c078567996464d654e5a">KEY_CODEC_TYPE</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ac1ff343954a9a979fd49bf6ef80d2589">KEY_DIRECTION_TYPE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ad8c37ded7037d0e1eeb6e477ff72492f">KEY_BITRATE</a> = 0x500, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6adab65ac6751535b13f6275dbfa1ba90e">KEY_WIDTH</a> = 0x1000, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a78fd0c2ba5fb7894ec4a164ff2b119b8">KEY_HEIGHT</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ad25b08a51da92cb8928402bd2a99ec60">KEY_STRIDE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ae45fd20d699c2a40110d510c26e2b0bb">KEY_VIDEO_FIELD</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a8b4fdf85f17f5bb549236a6280e36328">KEY_PIXEL_FORMAT</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6abed5c9737ae85a1771f6d065692fdab1">KEY_VIDEO_RC_MODE</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6aae6cd2e1f70f313300e8579d2c6befbc">KEY_VIDEO_GOP_MODE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a19a23598acca8b0d1dfa8bb48f58a7ef">KEY_VIDEO_PIC_SIZE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ab05b2fdf7c66accbce8bd4c5689dbe31">KEY_VIDEO_PROFILE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6acdfdfbe59769faa9eb22c7fabf99ab77">KEY_VIDEO_FRAME_RATE</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a513f3e7cbf10667949bd2f276b43227e">KEY_SAMPLE_RATE</a> = 0x1500, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a1a00600fff0e7a378bc0c690451f1040">KEY_AUDIO_PROFILE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a8c791931da4303642db329af0bb383a8">KEY_CHANNEL_COUNT</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ae054dfca35dd75e795aa9af83390a4fd">KEY_BITWITH</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ade681ad9e4e270d52ed2127dc86a90c7">KEY_SOUND_MODE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ab6ca06e65b7ee9808e07389507555b48">KEY_POINT_NUM_PER_FRAME</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a15bf33195ec3c6067084aa3fa047cad2">KEY_DEVICE_ID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2078294378084828"><a name="p2078294378084828"></a><a name="p2078294378084828"></a>Enumerates indexes of parameter types.</p>
</td>
</tr>
<tr id="row180755901084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237903691084828"><a name="p1237903691084828"></a><a name="p1237903691084828"></a><a href="codec.md#ga94267d7ba495136561e1c65686b240f7">VenCodeRcMode</a> {   <a href="codec.md#gga94267d7ba495136561e1c65686b240f7af65e058f6076a39b864a5e5351c508a8">VENCOD_RC_CBR</a> = 0, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ad40974ef1c63cc0fcef1106a69dc696a">VENCOD_RC_VBR</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ae4e2d1f85e783430a12ad412edf21ddc">VENCOD_RC_AVBR</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7aa3294f73cd0cd078618ef9db4d3cb6f5">VENCOD_RC_QVBR</a>,   <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ad43d98e7b3b42efa4cc6d4d1a2298024">VENCOD_RC_CVBR</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7a3e89e3affbe63967e5cdfc3b162d8ac9">VENCOD_RC_QPMAP</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ae9a1e0b19d79f1c2bdada4c5830e2584">VENCOD_RC_FIXQP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p937983449084828"><a name="p937983449084828"></a><a name="p937983449084828"></a>Enumerates control modes of the channel encoding rate.</p>
</td>
</tr>
<tr id="row1570166870084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p625185968084828"><a name="p625185968084828"></a><a name="p625185968084828"></a><a href="codec.md#ga94981b885085085ed5f9dea406519b48">PicSize</a> {   <a href="codec.md#gga94981b885085085ed5f9dea406519b48a373065e30654b1d097cb9725bec88962">Resolution_CIF</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48af6b390500e92b07d1c8829c7ce13fc9b">Resolution_360P</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48a7662d5257ffca575be7f343015f3e6ab">Resolution_D1_PAL</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48ae2644966a8e6b6595f90bc950fa9673d">Resolution_D1_NTSC</a>,   <a href="codec.md#gga94981b885085085ed5f9dea406519b48ae6d83a5bdf1b754df6dc23b07d781a5e">Resolution_720P</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48a460ffc02a1f90e6194fca5f1fcfb513b">Resolution_1080P</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48ae26dfcd8b806ea2ec7236f5a43dba1a2">Resolution_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1772718533084828"><a name="p1772718533084828"></a><a name="p1772718533084828"></a>Enumerates resolutions.</p>
</td>
</tr>
<tr id="row1767642137084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p404857669084828"><a name="p404857669084828"></a><a name="p404857669084828"></a><a href="codec.md#ga9532f651a003219a262c440f5621d129">VenCodeGopMode</a> {   <a href="codec.md#gga9532f651a003219a262c440f5621d129a1f3b41538fdbdbb9f920f740f89c7c95">VENCOD_GOPMODE_NORMALP</a> = 0, <a href="codec.md#gga9532f651a003219a262c440f5621d129a6b063f65ef8ec77e360bbbd56c7b233f">VENCOD_GOPMODE_DUALP</a> = 1, <a href="codec.md#gga9532f651a003219a262c440f5621d129a37226f50b4e07586d8bd8e22114e2324">VENCOD_GOPMODE_SMARTP</a> = 2, <a href="codec.md#gga9532f651a003219a262c440f5621d129a8caa9e9fae7ca1d041ccb163bbcf92c6">VENCOD_GOPMODE_ADVSMARTP</a> = 3,   <a href="codec.md#gga9532f651a003219a262c440f5621d129a7a120c500828b79e7a87e4f8a9d4378c">VENCOD_GOPMODE_BIPREDB</a> = 4, <a href="codec.md#gga9532f651a003219a262c440f5621d129ae02038b7e71cb65c991676da17a11a73">VENCOD_GOPMODE_LOWDELAYB</a> = 5, <a href="codec.md#gga9532f651a003219a262c440f5621d129a6b54943891a852da1b3e37cac4893b55">VENCOD_GOPMODE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897799670084828"><a name="p897799670084828"></a><a name="p897799670084828"></a>Enumerates types of group of pictures (GOP).</p>
</td>
</tr>
<tr id="row548895589084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1051765026084828"><a name="p1051765026084828"></a><a name="p1051765026084828"></a><a href="codec.md#ga1420ddfb066b941fb55a153b869d9ccf">VideoField</a> {   <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfadf9934801550e7c45e395d8e4704aff9">VID_FIELD_TOP</a> = 0x1, <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfa3de04ce552cc5a52d977256efed8611a">VID_FIELD_BOTTOM</a> = 0x2, <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfa9c3bffc837d46ece68154c98bfc4c303">VID_FIELD_INTERLACED</a> = 0x3, <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfaaf092a3bb1b706a47a425e7eff683526">VID_FIELD_FRAME</a> = 0x4,   <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfaedd6cdcd59983317521c2ac717884405">VID_FIELD_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1082574900084828"><a name="p1082574900084828"></a><a name="p1082574900084828"></a>Enumerates video frame fields.</p>
</td>
</tr>
<tr id="row1514169514084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p357738938084828"><a name="p357738938084828"></a><a name="p357738938084828"></a><a href="codec.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> {   <a href="codec.md#entry232666425084825p0">YVU_SEMIPLANAR_420</a> = 0, <a href="codec.md#entry513985664084825p0">YVU_SEMIPLANAR_420_TILE</a>, <a href="codec.md#entry1929427153084825p0">PIX_FORMAT_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733135871084828"><a name="p733135871084828"></a><a name="p733135871084828"></a>Enumerates pixel formats.</p>
</td>
</tr>
<tr id="row1208501526084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924100610084828"><a name="p924100610084828"></a><a name="p924100610084828"></a><a href="codec.md#gacecb40e35c431a27385f7b439fc7a76c">AudioSoundMode</a> { <a href="codec.md#ggacecb40e35c431a27385f7b439fc7a76caef98cd29f4639de89778f1be521a1676">AUD_SOUND_MODE_MONO</a> = 0, <a href="codec.md#ggacecb40e35c431a27385f7b439fc7a76ca9437f9e5186f7095fb50775eddc439d6">AUD_SOUND_MODE_STEREO</a> = 1, <a href="codec.md#ggacecb40e35c431a27385f7b439fc7a76ca53160e7e334a8629bec602c42d2ee5e6">AUD_SOUND_MODE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1224989200084828"><a name="p1224989200084828"></a><a name="p1224989200084828"></a>Enumerates audio channel modes.</p>
</td>
</tr>
<tr id="row1086290988084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973405699084828"><a name="p973405699084828"></a><a name="p973405699084828"></a><a href="codec.md#gaa0280074adafe6d2581d31f71512b842">AudioSampleRate</a> {   <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a65d5a1e4d1f048a33d29c9a3b6f540bd">AUD_SAMPLE_RATE_8000</a> = 8000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842ac8379e14b05cdac5edfcc931ac8b33a9">AUD_SAMPLE_RATE_12000</a> = 12000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a57b1853b1e309bf1aa5b3a35b06b0f81">AUD_SAMPLE_RATE_11025</a> = 11025, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a43395f0fe94ae2949778468e4488c3ee">AUD_SAMPLE_RATE_16000</a> = 16000,   <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a5e8155ecfa865686a66e004e37ce1e54">AUD_SAMPLE_RATE_22050</a> = 22050, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842abd4c09d52f3da25adb108e9aa503119d">AUD_SAMPLE_RATE_24000</a> = 24000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a1f94827fe757ad2857d970638b6f8d66">AUD_SAMPLE_RATE_32000</a> = 32000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842ac880553f2ee154a240d9414598e006a2">AUD_SAMPLE_RATE_44100</a> = 44100,   <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842ade6dd509c28b66127c42d2634866b89c">AUD_SAMPLE_RATE_48000</a> = 48000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a925218c15bb8522796e623a09d99dbc3">AUD_SAMPLE_RATE_64000</a> = 64000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a48336a808a2ebcf5956995140e2d73dd">AUD_SAMPLE_RATE_96000</a> = 96000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a0cb82ce52fb70b359a0b2232f7f465a2">AUD_SAMPLE_RATE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846866403084828"><a name="p846866403084828"></a><a name="p846866403084828"></a>Enumerates audio sampling rates.</p>
</td>
</tr>
<tr id="row354208705084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1127681718084828"><a name="p1127681718084828"></a><a name="p1127681718084828"></a><a href="codec.md#gac8cc627a9912e6a338396a6f19bbba5d">AudioBitRate</a> {   <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da1b31811befaf84b164684a38fa022f43">AUD_AAC_BPS_8K</a> = 8000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5dab71f0668b9fc4955fe059339ea663e8e">AUD_AAC_BPS_16K</a> = 16000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da3cc22f17e3fddb9d081aa3d826d31ac9">AUD_AAC_BPS_22K</a> = 22000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5dadb78faf7877b6f70fd9b55406dcbd6b0">AUD_AAC_BPS_24K</a> = 24000,   <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da974bd8a79bb6004f84b670f2496a33b9">AUD_AAC_BPS_32K</a> = 32000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da7d330b118800e19500f2f4a9b6af38f8">AUD_AAC_BPS_48K</a> = 48000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da2b8757624080a60f39d848dac7820e99">AUD_AAC_BPS_64K</a> = 64000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da5ff13a09a232327578c69159f7564da8">AUD_AAC_BPS_96K</a> = 96000,   <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da8806920e563eca6c76b225185f24f191">AUD_AAC_BPS_128K</a> = 128000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da7584ca8ebd583c448c5e2ff4957448f7">AUD_AAC_BPS_256K</a> = 256000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5dade0faf8053bab953b55bc3e4d20341d5">AUD_AAC_BPS_320K</a> = 320000 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563716701084828"><a name="p1563716701084828"></a><a name="p1563716701084828"></a>Enumerates audio bit rates.</p>
</td>
</tr>
<tr id="row1577287092084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683029431084828"><a name="p1683029431084828"></a><a name="p1683029431084828"></a><a href="codec.md#ga8a15793172118d64d8adeba0c8544e84">StreamFlagType</a> {   <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84ae0da6ed262d36cb4de4b63cd25889ea2">STREAM_FLAG_KEYFRAME</a> = 1, <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84a9a06fdc891d28272ba6651ca9791d166">STREAM_FLAG_CODEC_SPECIFIC_INF</a> = 2, <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84abe40ab8f6da71b5a7d6a382954dc5d4f">STREAM_FLAG_EOS</a> = 4, <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84a7809fe65541dc27f50ba4952685c34bd">STREAM_FLAG_PART_OF_FRAME</a> = 8,   <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84abb9a3fba052c516ac141e34ea9fa6dca">STREAM_FLAG_END_OF_FRAME</a> = 16 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340411416084828"><a name="p340411416084828"></a><a name="p340411416084828"></a>Enumerates stream flags.</p>
</td>
</tr>
<tr id="row1919450765084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842862263084828"><a name="p842862263084828"></a><a name="p842862263084828"></a><a href="codec.md#gadf8e136713c0691010d2bec6ba63e9cf">BufferType</a> { <a href="codec.md#ggadf8e136713c0691010d2bec6ba63e9cfabc56eeb37d99d582a14b44fb0ef4cabc">BUFFER_TYPE_VIRTUAL</a> = 0, <a href="codec.md#ggadf8e136713c0691010d2bec6ba63e9cfa4583aeaa2921c629ee785dbee184f421">BUFFER_TYPE_FD</a>, <a href="codec.md#ggadf8e136713c0691010d2bec6ba63e9cfa4bc0e24b5ce589d284b1771fc27c3d09">BUFFER_TYPE_HANDLE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1514920033084828"><a name="p1514920033084828"></a><a name="p1514920033084828"></a>Enumerates buffer types.</p>
</td>
</tr>
<tr id="row1169831936084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p233498868084828"><a name="p233498868084828"></a><a name="p233498868084828"></a><a href="codec.md#ga1bee586eafa91dfb60f94ba40fc95faa">AvCodecMime</a> {   <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaa4deff5e22cd5e2e83b6042880ad31863">MEDIA_MIMETYPE_IMAGE_JPEG</a> = 0, <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaa3db11a46c7f4bb848e6f0604268e41e3">MEDIA_MIMETYPE_VIDEO_AVC</a>, <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaaaf430209c9262e6fcd5cd8f97dafe614">MEDIA_MIMETYPE_VIDEO_HEVC</a>, <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaac03eb65aaf7aff393e223346feb30415">MEDIA_MIMETYPE_AUDIO_AAC</a>,   <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaaa2fa953bd51d8ee18191315c7187fc96">MEDIA_MIMETYPE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1953687794084828"><a name="p1953687794084828"></a><a name="p1953687794084828"></a>Enumerates MIME types.</p>
</td>
</tr>
<tr id="row1579357354084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p860864683084828"><a name="p860864683084828"></a><a name="p860864683084828"></a><a href="codec.md#ga85b10143618f300ff4f5bc6d45c72c01">Profile</a> {   <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a6d67944b4958ad33b0eeb851bbcd169f">INVALID_PROFILE</a> = 0, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ad91765d6dcad7253a924d3cb30501e44">AAC_LC_PROFILE</a> = 0x1000, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01aada4d857818cd9aa1ad62cdf608dab6b">AAC_MAIN_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ab4255dc0e7450af4f526b85acbabfd3e">AAC_HE_V1_PROFILE</a>,   <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a9b54f7a8c45ea6d4804133d8de4b8dd8">AAC_HE_V2_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01afaaacd4f6bdadac28b5cf49ae8f8470a">AAC_LD_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a7c8028283d1ff60e486b3305bf8c1adc">AAC_ELD_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a5bab002f00d3d7281aedc4807123a47a">AVC_BASELINE_PROFILE</a> = 0x2000,   <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a323c1d6e02363f1717f7e6b33fd9a646">AVC_MAIN_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ab9406e6bf30a0c128c3639cce51fe246">AVC_HIGH_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ae0d37dc2c7d39753a80f6e0ba64e5e22">HEVC_MAIN_PROFILE</a> = 0x3000, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a811b9e02d8b0afa93e7ab8d2aa7e5de6">HEVC_MAIN_10_PROFILE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1872553901084828"><a name="p1872553901084828"></a><a name="p1872553901084828"></a>Enumerates codec profiles.</p>
</td>
</tr>
<tr id="row753920041084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p197613531084828"><a name="p197613531084828"></a><a name="p197613531084828"></a><a href="codec.md#ga221b779e6bb7b8d40677d7642bfefac5">Level</a> { <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5a6ab1f388a1a94d680bcbe808ec45a082">INVALID_LEVEL</a> = 0, <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5aee353b803bd93ba9e01e99e67b8afb49">AVC_LEVEL_1</a> = 0x1000, <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5a25819fec0bd7476c85122100b61536bb">HEVC_LEVEL_MAIN_1</a> = 0x2000, <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5ab21d7836b0849b87149b7cdd7924d862">HEVC_LEVEL_MAIN_2</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225904752084828"><a name="p1225904752084828"></a><a name="p1225904752084828"></a>Enumerates codec levels.</p>
</td>
</tr>
<tr id="row366970145084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2078544098084828"><a name="p2078544098084828"></a><a name="p2078544098084828"></a><a href="codec.md#gaeae808d52153b2e33c6815162bbd11e0">AllocateBufferMode</a> { <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0ae8110d24a63ec0b86785ea48c8ecca42">ALLOCATE_INPUT_BUFFER_CODEC</a> = 0x1, <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0ae09681fcb839aa54acd974d872e3020d">ALLOCATE_INPUT_BUFFER_USER</a> = 0x2, <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0a73f74ceb227e306dbe940289a138bdf9">ALLOCATE_OUTPUT_BUFFER_CODEC</a> = 0x4, <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0a81113cd1f553c8e05eb9bd59fdb58bed">ALLOCATE_OUTPUT_BUFFER_USER</a> = 0x8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1436062262084828"><a name="p1436062262084828"></a><a name="p1436062262084828"></a>Enumerates allocation modes of input and output buffers.</p>
</td>
</tr>
<tr id="row2029179647084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1575698171084828"><a name="p1575698171084828"></a><a name="p1575698171084828"></a><a href="codec.md#gae5751aa8514dcaf2217df12db5ef57a1">CapsMask</a> { <a href="codec.md#ggae5751aa8514dcaf2217df12db5ef57a1afe6e93325882ea7c27503f79d0b2dcae">ADAPTIVE_PLAYBACK</a> = 0x1, <a href="codec.md#ggae5751aa8514dcaf2217df12db5ef57a1ad0c1ab7c365efc53a4de146b91f1a10f">SECURE_PLAYBACK</a> = 0x2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635958155084828"><a name="p635958155084828"></a><a name="p635958155084828"></a>Enumerates playback capabilities.</p>
</td>
</tr>
<tr id="row1309274616084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1976349612084828"><a name="p1976349612084828"></a><a name="p1976349612084828"></a><a href="codec.md#ga2628ea8d12e8b2563c32f05dc7fff6fa">EventType</a> {   <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faa71cf6bf1e591a86cb536668cda0f2a00">EventError</a>, <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faaab9f6e22232b045b85118bdda8aac6db">EventFlushCompelte</a>, <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faa864f301176ff05ad003bc6e89eb2cb93">EventStopCompelte</a>, <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faaeb0fb0bb31b20a141d015d9a92c629ac">EventOutFormatChanged</a>,   <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faa70203255ab263a903886b8f774d5c4aa">EventMax</a> = 0x1FFFFFFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315226659084828"><a name="p315226659084828"></a><a name="p315226659084828"></a>Enumerates event types.</p>
</td>
</tr>
<tr id="row1292577953084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p834540765084828"><a name="p834540765084828"></a><a name="p834540765084828"></a><a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> { <a href="codec.md#gga8ef30fa9c08e08c8706653571f9f5b81a833326d0b04dd281eaf006c46842250d">INPUT_TYPE</a>, <a href="codec.md#gga8ef30fa9c08e08c8706653571f9f5b81a9e3da5a3721894f1552c2715c1fbe95c">OUTPUT_TYPE</a>, <a href="codec.md#gga8ef30fa9c08e08c8706653571f9f5b81a46bcae2d9d2268e6a0c9259b9aebfc2f">ALL_TYPE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p361460391084828"><a name="p361460391084828"></a><a name="p361460391084828"></a>Enumerates input and output types.</p>
</td>
</tr>
<tr id="row1591436891084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2074968568084828"><a name="p2074968568084828"></a><a name="p2074968568084828"></a><a href="codec.md#gacc0fd55192fd9f663121b037b06f41e8">BufferMode</a> { <a href="codec.md#ggacc0fd55192fd9f663121b037b06f41e8adc7588f17692aa631f375290d50a2c8e">INTERNAL</a>, <a href="codec.md#ggacc0fd55192fd9f663121b037b06f41e8a63fbb9fe7b9a695d3a65541465cb99d5">EXTERNAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p947308506084828"><a name="p947308506084828"></a><a name="p947308506084828"></a>Enumerates allocation types.</p>
</td>
</tr>
<tr id="row1002400018084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p366437149084828"><a name="p366437149084828"></a><a name="p366437149084828"></a>{ <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a750142c991cfbb45e81a11453c757cd8">CODEC_ERR_STREAM_BUF_FULL</a> = 100, <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a07abd749dca99a6cde8e4d03acc075f6">CODEC_ERR_FRAME_BUF_EMPTY</a>, <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a504a9ea3cbe78aa1ba2423ee702151ac">CODEC_RECEIVE_EOS</a>, <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a969385c1fbe6b30ab16b87775b06a074">CODEC_ERR_INVALID_OP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1419488241084828"><a name="p1419488241084828"></a><a name="p1419488241084828"></a>Enumerates codec error types.</p>
</td>
</tr>
</tbody>
</table>

