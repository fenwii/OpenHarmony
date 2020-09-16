# Codec<a name="EN-US_TOPIC_0000001055078087"></a>

## **Overview**<a name="section477591642084825"></a>

Defines codec-related APIs.

including custom data types and functions for initializing audio and video codecs, setting parameters, and controlling and transferring data.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section294253067084825"></a>

## Files<a name="files"></a>

<a name="table485638422084825"></a>
<table><thead align="left"><tr id="row931013690084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2131853560084825"><a name="p2131853560084825"></a><a name="p2131853560084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1963581622084825"><a name="p1963581622084825"></a><a name="p1963581622084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row232372906084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1411745893084825"><a name="p1411745893084825"></a><a name="p1411745893084825"></a><a href="en-us_topic_0000001054718089.md">codec_interface.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901258628084825"><a name="p1901258628084825"></a><a name="p1901258628084825"></a>Declares codec-related APIs, including functions for initializing audio and video codecs, setting parameters, and controlling and transferring data.</p>
</td>
</tr>
<tr id="row1451916915084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1478882620084825"><a name="p1478882620084825"></a><a name="p1478882620084825"></a><a href="codec_type-h.md">codec_type.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673213240084825"><a name="p1673213240084825"></a><a name="p1673213240084825"></a>Declares custom data types used in API declarations for the Codec module, including the codec types, audio and video parameters, input and output data, and callbacks.</p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1934936053084825"></a>
<table><thead align="left"><tr id="row385707180084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1955176103084825"><a name="p1955176103084825"></a><a name="p1955176103084825"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1493964099084825"><a name="p1493964099084825"></a><a name="p1493964099084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row806576042084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p784385128084825"><a name="p784385128084825"></a><a name="p784385128084825"></a><a href="en-us_topic_0000001054718161.md">Param</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p956872203084825"><a name="p956872203084825"></a><a name="p956872203084825"></a>Describes the dynamic parameter structure, which is mainly used by <a href="codec.md#ga74aa0395a51f004390f7a92fb68faddd">CodecCreate</a> and <a href="codec.md#gaa080cf23aa5f77b30f3b90a026d97cc0">CodecSetParameter</a>.</p>
</td>
</tr>
<tr id="row2102154003084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460290732084825"><a name="p1460290732084825"></a><a name="p1460290732084825"></a><a href="en-us_topic_0000001054918147.md">BufferHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061371849084825"><a name="p2061371849084825"></a><a name="p2061371849084825"></a>Defines the buffer handle type. The virtual address of a handle maps to its physical address.</p>
</td>
</tr>
<tr id="row1039653278084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1747713956084825"><a name="p1747713956084825"></a><a name="p1747713956084825"></a><a href="en-us_topic_0000001054879526.md">CodecBufferInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368434160084825"><a name="p368434160084825"></a><a name="p368434160084825"></a>Describes buffer information.</p>
</td>
</tr>
<tr id="row1456567052084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1768304372084825"><a name="p1768304372084825"></a><a name="p1768304372084825"></a><a href="en-us_topic_0000001054879536.md">InputInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1195054178084825"><a name="p1195054178084825"></a><a name="p1195054178084825"></a>Describes input information.</p>
</td>
</tr>
<tr id="row950671813084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p739482010084825"><a name="p739482010084825"></a><a name="p739482010084825"></a><a href="en-us_topic_0000001054918167.md">OutputInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859755170084825"><a name="p859755170084825"></a><a name="p859755170084825"></a>Describes output information.</p>
</td>
</tr>
<tr id="row972012178084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1979264842084825"><a name="p1979264842084825"></a><a name="p1979264842084825"></a><a href="en-us_topic_0000001054879568.md">ResizableArray</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p25554524084825"><a name="p25554524084825"></a><a name="p25554524084825"></a>Defines a variable-length queue.</p>
</td>
</tr>
<tr id="row1035501438084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115529256084825"><a name="p2115529256084825"></a><a name="p2115529256084825"></a><a href="en-us_topic_0000001054598149.md">Alginment</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1882880057084825"><a name="p1882880057084825"></a><a name="p1882880057084825"></a>Defines the alignment.</p>
</td>
</tr>
<tr id="row1621077115084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116073694084825"><a name="p2116073694084825"></a><a name="p2116073694084825"></a><a href="en-us_topic_0000001055198166.md">Rect</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880957287084825"><a name="p1880957287084825"></a><a name="p1880957287084825"></a>Defines a rectangle.</p>
</td>
</tr>
<tr id="row1629567070084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2010498248084825"><a name="p2010498248084825"></a><a name="p2010498248084825"></a><a href="en-us_topic_0000001055198124.md">Capbility</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p903621114084825"><a name="p903621114084825"></a><a name="p903621114084825"></a>Defines the codec capability.</p>
</td>
</tr>
<tr id="row75922913084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242282655084825"><a name="p242282655084825"></a><a name="p242282655084825"></a><a href="en-us_topic_0000001055358102.md">CodecCallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1822155979084825"><a name="p1822155979084825"></a><a name="p1822155979084825"></a>Defines callbacks and their parameters.</p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1657850542084825"></a>
<table><thead align="left"><tr id="row633771618084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1003431115084825"><a name="p1003431115084825"></a><a name="p1003431115084825"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1524117745084825"><a name="p1524117745084825"></a><a name="p1524117745084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row785377014084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806213532084825"><a name="p806213532084825"></a><a name="p806213532084825"></a><em id="gab34cc95c32c06b8d63cfbe62247eb6e2"><a name="gab34cc95c32c06b8d63cfbe62247eb6e2"></a><a name="gab34cc95c32c06b8d63cfbe62247eb6e2"></a></em>ELEMENT_MAX_LEN    50</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p233185775084825"><a name="p233185775084825"></a><a name="p233185775084825"></a>Indicates the maximum number of reserved parameters in the array.</p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1271838210084825"></a>
<table><thead align="left"><tr id="row406278849084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2038463467084825"><a name="p2038463467084825"></a><a name="p2038463467084825"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1987396123084825"><a name="p1987396123084825"></a><a name="p1987396123084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row822233507084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1617339760084825"><a name="p1617339760084825"></a><a name="p1617339760084825"></a><em id="ga9381a619f36ac8d5d7f467d2f0404183"><a name="ga9381a619f36ac8d5d7f467d2f0404183"></a><a name="ga9381a619f36ac8d5d7f467d2f0404183"></a></em>CODEC_HANDLETYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p433120678084825"><a name="p433120678084825"></a><a name="p433120678084825"></a><strong id="b1942821351"><a name="b1942821351"></a><a name="b1942821351"></a></strong> typedef void *</p>
<p id="p1387539468084825"><a name="p1387539468084825"></a><a name="p1387539468084825"></a>Defines the pointer to the codec handle, which is the context information for function calls.</p>
</td>
</tr>
<tr id="row1155169467084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1435218965084825"><a name="p1435218965084825"></a><a name="p1435218965084825"></a><em id="gadfdccaf7fd554ae1df6169bb622deb1d"><a name="gadfdccaf7fd554ae1df6169bb622deb1d"></a><a name="gadfdccaf7fd554ae1df6169bb622deb1d"></a></em>ValueType</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2046635579084825"><a name="p2046635579084825"></a><a name="p2046635579084825"></a><strong id="b1388840119"><a name="b1388840119"></a><a name="b1388840119"></a></strong> typedef void *</p>
<p id="p731443521084825"><a name="p731443521084825"></a><a name="p731443521084825"></a>Defines the pointer to the type of the dynamic parameter value.</p>
</td>
</tr>
<tr id="row1705062934084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494895603084825"><a name="p1494895603084825"></a><a name="p1494895603084825"></a><em id="ga5571ad9c720096768c508f1f38e2ef41"><a name="ga5571ad9c720096768c508f1f38e2ef41"></a><a name="ga5571ad9c720096768c508f1f38e2ef41"></a></em>BufferHandle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p824616914084825"><a name="p824616914084825"></a><a name="p824616914084825"></a><strong id="b1757956952"><a name="b1757956952"></a><a name="b1757956952"></a></strong> typedef struct <a href="en-us_topic_0000001054918147.md">BufferHandle</a></p>
<p id="p1335816592084825"><a name="p1335816592084825"></a><a name="p1335816592084825"></a>Defines the buffer handle type. The virtual address of a handle maps to its physical address.</p>
</td>
</tr>
<tr id="row710137908084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1402879350084825"><a name="p1402879350084825"></a><a name="p1402879350084825"></a><em id="ga8dc4e7c329ad589f25019ca03aed9925"><a name="ga8dc4e7c329ad589f25019ca03aed9925"></a><a name="ga8dc4e7c329ad589f25019ca03aed9925"></a></em>BufferType</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929462260084825"><a name="p929462260084825"></a><a name="p929462260084825"></a><strong id="b1017482589"><a name="b1017482589"></a><a name="b1017482589"></a></strong> typedef enum <a href="codec.md#gadf8e136713c0691010d2bec6ba63e9cf">BufferType</a></p>
<p id="p1279167201084825"><a name="p1279167201084825"></a><a name="p1279167201084825"></a>Enumerates buffer types.</p>
</td>
</tr>
<tr id="row542325243084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207701376084825"><a name="p1207701376084825"></a><a name="p1207701376084825"></a><em id="gab32442ed7057b2e9bd6b20ad35154cb8"><a name="gab32442ed7057b2e9bd6b20ad35154cb8"></a><a name="gab32442ed7057b2e9bd6b20ad35154cb8"></a></em>OutputInfo</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125795072084825"><a name="p2125795072084825"></a><a name="p2125795072084825"></a><strong id="b911723590"><a name="b911723590"></a><a name="b911723590"></a></strong> typedef struct <a href="en-us_topic_0000001054918167.md">OutputInfo</a></p>
<p id="p164144484084825"><a name="p164144484084825"></a><a name="p164144484084825"></a>Describes output information.</p>
</td>
</tr>
<tr id="row23770413084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1418747284084825"><a name="p1418747284084825"></a><a name="p1418747284084825"></a><em id="gaf59a3505491b6f0b5dff5d62372a9679"><a name="gaf59a3505491b6f0b5dff5d62372a9679"></a><a name="gaf59a3505491b6f0b5dff5d62372a9679"></a></em>AllocateBufferMode</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1885165320084825"><a name="p1885165320084825"></a><a name="p1885165320084825"></a><strong id="b1697971013"><a name="b1697971013"></a><a name="b1697971013"></a></strong> typedef enum <a href="codec.md#gaeae808d52153b2e33c6815162bbd11e0">AllocateBufferMode</a></p>
<p id="p1195042159084825"><a name="p1195042159084825"></a><a name="p1195042159084825"></a>Enumerates allocation modes of input and output buffers.</p>
</td>
</tr>
<tr id="row582231134084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p789236950084825"><a name="p789236950084825"></a><a name="p789236950084825"></a><em id="ga09af5b0a9d5134ad4d44cbe8cbe7b887"><a name="ga09af5b0a9d5134ad4d44cbe8cbe7b887"></a><a name="ga09af5b0a9d5134ad4d44cbe8cbe7b887"></a></em>CapsMask</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p50635516084825"><a name="p50635516084825"></a><a name="p50635516084825"></a><strong id="b1878923724"><a name="b1878923724"></a><a name="b1878923724"></a></strong> typedef enum <a href="codec.md#gae5751aa8514dcaf2217df12db5ef57a1">CapsMask</a></p>
<p id="p1918071660084825"><a name="p1918071660084825"></a><a name="p1918071660084825"></a>Enumerates playback capabilities.</p>
</td>
</tr>
<tr id="row2126156125084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1593503427084825"><a name="p1593503427084825"></a><a name="p1593503427084825"></a><em id="ga1876710b1f2fe1d80e8b9de9ff28e0e3"><a name="ga1876710b1f2fe1d80e8b9de9ff28e0e3"></a><a name="ga1876710b1f2fe1d80e8b9de9ff28e0e3"></a></em>CodecCapbility</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592299814084825"><a name="p1592299814084825"></a><a name="p1592299814084825"></a><strong id="b2083416965"><a name="b2083416965"></a><a name="b2083416965"></a></strong> typedef struct <a href="en-us_topic_0000001055198124.md">Capbility</a></p>
<p id="p1582860246084825"><a name="p1582860246084825"></a><a name="p1582860246084825"></a>Defines the codec capability.</p>
</td>
</tr>
<tr id="row452828196084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p668618539084825"><a name="p668618539084825"></a><a name="p668618539084825"></a><em id="ga58d2f4a8d12daa1dcf4eb297f3ebaabc"><a name="ga58d2f4a8d12daa1dcf4eb297f3ebaabc"></a><a name="ga58d2f4a8d12daa1dcf4eb297f3ebaabc"></a></em>UINTPTR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71133958084825"><a name="p71133958084825"></a><a name="p71133958084825"></a><strong id="b634814220"><a name="b634814220"></a><a name="b634814220"></a></strong> typedef uintptr_t</p>
<p id="p146145397084825"><a name="p146145397084825"></a><a name="p146145397084825"></a>Redefines the unsigned pointer type, which is used for pointer conversion.</p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table353563757084825"></a>
<table><thead align="left"><tr id="row727300270084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1105118593084825"><a name="p1105118593084825"></a><a name="p1105118593084825"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1992455849084825"><a name="p1992455849084825"></a><a name="p1992455849084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1973247310084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1800047081084825"><a name="p1800047081084825"></a><a name="p1800047081084825"></a><a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a> {   <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79a19c3c7765c55583a64e21938e2439261">VIDEO_DECODER</a>, <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79ad8044bc5b7d871723be90b5b6a094992">VIDEO_ENCODER</a>, <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79ae4ade329585f6c202847138e3f9cd4a4">AUDIO_DECODER</a>, <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79a7f7f3d3880168089c1de6d1ebc3dbb54">AUDIO_ENCODER</a>,   <a href="codec.md#gga03b4b6ae5fb82af68d46aaea3d3e4d79a7314b0d0e4638eaaeb8690b8555a6546">INVALID_TYPE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p205466047084825"><a name="p205466047084825"></a><a name="p205466047084825"></a>Enumerates codec types.</p>
</td>
</tr>
<tr id="row282856854084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244174509084825"><a name="p1244174509084825"></a><a name="p1244174509084825"></a><a href="codec.md#ga575c56a2d6b42c48881cf47b0008d5a6">ParamKey</a> {   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6aef2a08e0112230b41df402fd38efc1ed">KEY_MIMETYPE</a> = 0x01, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a2c86d69eb4995dbadfdb6d289834f7f2">KEY_BUFFERSIZE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a4c97de4e44d3c9778530ddd2cffe1728">KEY_LEFT_STREAM_FRAMES</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ac3e2aece8c07c078567996464d654e5a">KEY_CODEC_TYPE</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ac1ff343954a9a979fd49bf6ef80d2589">KEY_DIRECTION_TYPE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ad8c37ded7037d0e1eeb6e477ff72492f">KEY_BITRATE</a> = 0x500, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6adab65ac6751535b13f6275dbfa1ba90e">KEY_WIDTH</a> = 0x1000, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a78fd0c2ba5fb7894ec4a164ff2b119b8">KEY_HEIGHT</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ad25b08a51da92cb8928402bd2a99ec60">KEY_STRIDE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ae45fd20d699c2a40110d510c26e2b0bb">KEY_VIDEO_FIELD</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a8b4fdf85f17f5bb549236a6280e36328">KEY_PIXEL_FORMAT</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6abed5c9737ae85a1771f6d065692fdab1">KEY_VIDEO_RC_MODE</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6aae6cd2e1f70f313300e8579d2c6befbc">KEY_VIDEO_GOP_MODE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a19a23598acca8b0d1dfa8bb48f58a7ef">KEY_VIDEO_PIC_SIZE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ab05b2fdf7c66accbce8bd4c5689dbe31">KEY_VIDEO_PROFILE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6acdfdfbe59769faa9eb22c7fabf99ab77">KEY_VIDEO_FRAME_RATE</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a513f3e7cbf10667949bd2f276b43227e">KEY_SAMPLE_RATE</a> = 0x1500, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a1a00600fff0e7a378bc0c690451f1040">KEY_AUDIO_PROFILE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a8c791931da4303642db329af0bb383a8">KEY_CHANNEL_COUNT</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ae054dfca35dd75e795aa9af83390a4fd">KEY_BITWITH</a>,   <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ade681ad9e4e270d52ed2127dc86a90c7">KEY_SOUND_MODE</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6ab6ca06e65b7ee9808e07389507555b48">KEY_POINT_NUM_PER_FRAME</a>, <a href="codec.md#gga575c56a2d6b42c48881cf47b0008d5a6a15bf33195ec3c6067084aa3fa047cad2">KEY_DEVICE_ID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p632406918084825"><a name="p632406918084825"></a><a name="p632406918084825"></a>Enumerates indexes of parameter types.</p>
</td>
</tr>
<tr id="row2086535437084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1187132007084825"><a name="p1187132007084825"></a><a name="p1187132007084825"></a><a href="codec.md#ga94267d7ba495136561e1c65686b240f7">VenCodeRcMode</a> {   <a href="codec.md#gga94267d7ba495136561e1c65686b240f7af65e058f6076a39b864a5e5351c508a8">VENCOD_RC_CBR</a> = 0, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ad40974ef1c63cc0fcef1106a69dc696a">VENCOD_RC_VBR</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ae4e2d1f85e783430a12ad412edf21ddc">VENCOD_RC_AVBR</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7aa3294f73cd0cd078618ef9db4d3cb6f5">VENCOD_RC_QVBR</a>,   <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ad43d98e7b3b42efa4cc6d4d1a2298024">VENCOD_RC_CVBR</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7a3e89e3affbe63967e5cdfc3b162d8ac9">VENCOD_RC_QPMAP</a>, <a href="codec.md#gga94267d7ba495136561e1c65686b240f7ae9a1e0b19d79f1c2bdada4c5830e2584">VENCOD_RC_FIXQP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p642240445084825"><a name="p642240445084825"></a><a name="p642240445084825"></a>Enumerates control modes of the channel encoding rate.</p>
</td>
</tr>
<tr id="row1714292970084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772677282084825"><a name="p1772677282084825"></a><a name="p1772677282084825"></a><a href="codec.md#ga94981b885085085ed5f9dea406519b48">PicSize</a> {   <a href="codec.md#gga94981b885085085ed5f9dea406519b48a373065e30654b1d097cb9725bec88962">Resolution_CIF</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48af6b390500e92b07d1c8829c7ce13fc9b">Resolution_360P</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48a7662d5257ffca575be7f343015f3e6ab">Resolution_D1_PAL</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48ae2644966a8e6b6595f90bc950fa9673d">Resolution_D1_NTSC</a>,   <a href="codec.md#gga94981b885085085ed5f9dea406519b48ae6d83a5bdf1b754df6dc23b07d781a5e">Resolution_720P</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48a460ffc02a1f90e6194fca5f1fcfb513b">Resolution_1080P</a>, <a href="codec.md#gga94981b885085085ed5f9dea406519b48ae26dfcd8b806ea2ec7236f5a43dba1a2">Resolution_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223443556084825"><a name="p1223443556084825"></a><a name="p1223443556084825"></a>Enumerates resolutions.</p>
</td>
</tr>
<tr id="row985778408084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1975664228084825"><a name="p1975664228084825"></a><a name="p1975664228084825"></a><a href="codec.md#ga9532f651a003219a262c440f5621d129">VenCodeGopMode</a> {   <a href="codec.md#gga9532f651a003219a262c440f5621d129a1f3b41538fdbdbb9f920f740f89c7c95">VENCOD_GOPMODE_NORMALP</a> = 0, <a href="codec.md#gga9532f651a003219a262c440f5621d129a6b063f65ef8ec77e360bbbd56c7b233f">VENCOD_GOPMODE_DUALP</a> = 1, <a href="codec.md#gga9532f651a003219a262c440f5621d129a37226f50b4e07586d8bd8e22114e2324">VENCOD_GOPMODE_SMARTP</a> = 2, <a href="codec.md#gga9532f651a003219a262c440f5621d129a8caa9e9fae7ca1d041ccb163bbcf92c6">VENCOD_GOPMODE_ADVSMARTP</a> = 3,   <a href="codec.md#gga9532f651a003219a262c440f5621d129a7a120c500828b79e7a87e4f8a9d4378c">VENCOD_GOPMODE_BIPREDB</a> = 4, <a href="codec.md#gga9532f651a003219a262c440f5621d129ae02038b7e71cb65c991676da17a11a73">VENCOD_GOPMODE_LOWDELAYB</a> = 5, <a href="codec.md#gga9532f651a003219a262c440f5621d129a6b54943891a852da1b3e37cac4893b55">VENCOD_GOPMODE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p927709032084825"><a name="p927709032084825"></a><a name="p927709032084825"></a>Enumerates types of group of pictures (GOP).</p>
</td>
</tr>
<tr id="row812972854084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p65869194084825"><a name="p65869194084825"></a><a name="p65869194084825"></a><a href="codec.md#ga1420ddfb066b941fb55a153b869d9ccf">VideoField</a> {   <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfadf9934801550e7c45e395d8e4704aff9">VID_FIELD_TOP</a> = 0x1, <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfa3de04ce552cc5a52d977256efed8611a">VID_FIELD_BOTTOM</a> = 0x2, <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfa9c3bffc837d46ece68154c98bfc4c303">VID_FIELD_INTERLACED</a> = 0x3, <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfaaf092a3bb1b706a47a425e7eff683526">VID_FIELD_FRAME</a> = 0x4,   <a href="codec.md#gga1420ddfb066b941fb55a153b869d9ccfaedd6cdcd59983317521c2ac717884405">VID_FIELD_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880423289084825"><a name="p880423289084825"></a><a name="p880423289084825"></a>Enumerates video frame fields.</p>
</td>
</tr>
<tr id="row1772001772084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p652055962084825"><a name="p652055962084825"></a><a name="p652055962084825"></a><a href="codec.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> {   <a href="#entry232666425084825p0">YVU_SEMIPLANAR_420</a> = 0, <a href="#entry513985664084825p0">YVU_SEMIPLANAR_420_TILE</a>, <a href="#entry1929427153084825p0">PIX_FORMAT_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p907609685084825"><a name="p907609685084825"></a><a name="p907609685084825"></a>Enumerates pixel formats.</p>
</td>
</tr>
<tr id="row591813974084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1533082319084825"><a name="p1533082319084825"></a><a name="p1533082319084825"></a><a href="codec.md#gacecb40e35c431a27385f7b439fc7a76c">AudioSoundMode</a> { <a href="codec.md#ggacecb40e35c431a27385f7b439fc7a76caef98cd29f4639de89778f1be521a1676">AUD_SOUND_MODE_MONO</a> = 0, <a href="codec.md#ggacecb40e35c431a27385f7b439fc7a76ca9437f9e5186f7095fb50775eddc439d6">AUD_SOUND_MODE_STEREO</a> = 1, <a href="codec.md#ggacecb40e35c431a27385f7b439fc7a76ca53160e7e334a8629bec602c42d2ee5e6">AUD_SOUND_MODE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p721190361084825"><a name="p721190361084825"></a><a name="p721190361084825"></a>Enumerates audio channel modes.</p>
</td>
</tr>
<tr id="row1101377102084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1863122086084825"><a name="p1863122086084825"></a><a name="p1863122086084825"></a><a href="codec.md#gaa0280074adafe6d2581d31f71512b842">AudioSampleRate</a> {   <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a65d5a1e4d1f048a33d29c9a3b6f540bd">AUD_SAMPLE_RATE_8000</a> = 8000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842ac8379e14b05cdac5edfcc931ac8b33a9">AUD_SAMPLE_RATE_12000</a> = 12000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a57b1853b1e309bf1aa5b3a35b06b0f81">AUD_SAMPLE_RATE_11025</a> = 11025, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a43395f0fe94ae2949778468e4488c3ee">AUD_SAMPLE_RATE_16000</a> = 16000,   <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a5e8155ecfa865686a66e004e37ce1e54">AUD_SAMPLE_RATE_22050</a> = 22050, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842abd4c09d52f3da25adb108e9aa503119d">AUD_SAMPLE_RATE_24000</a> = 24000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a1f94827fe757ad2857d970638b6f8d66">AUD_SAMPLE_RATE_32000</a> = 32000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842ac880553f2ee154a240d9414598e006a2">AUD_SAMPLE_RATE_44100</a> = 44100,   <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842ade6dd509c28b66127c42d2634866b89c">AUD_SAMPLE_RATE_48000</a> = 48000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a925218c15bb8522796e623a09d99dbc3">AUD_SAMPLE_RATE_64000</a> = 64000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a48336a808a2ebcf5956995140e2d73dd">AUD_SAMPLE_RATE_96000</a> = 96000, <a href="codec.md#ggaa0280074adafe6d2581d31f71512b842a0cb82ce52fb70b359a0b2232f7f465a2">AUD_SAMPLE_RATE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1410767136084825"><a name="p1410767136084825"></a><a name="p1410767136084825"></a>Enumerates audio sampling rates.</p>
</td>
</tr>
<tr id="row754869616084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1450246180084825"><a name="p1450246180084825"></a><a name="p1450246180084825"></a><a href="codec.md#gac8cc627a9912e6a338396a6f19bbba5d">AudioBitRate</a> {   <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da1b31811befaf84b164684a38fa022f43">AUD_AAC_BPS_8K</a> = 8000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5dab71f0668b9fc4955fe059339ea663e8e">AUD_AAC_BPS_16K</a> = 16000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da3cc22f17e3fddb9d081aa3d826d31ac9">AUD_AAC_BPS_22K</a> = 22000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5dadb78faf7877b6f70fd9b55406dcbd6b0">AUD_AAC_BPS_24K</a> = 24000,   <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da974bd8a79bb6004f84b670f2496a33b9">AUD_AAC_BPS_32K</a> = 32000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da7d330b118800e19500f2f4a9b6af38f8">AUD_AAC_BPS_48K</a> = 48000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da2b8757624080a60f39d848dac7820e99">AUD_AAC_BPS_64K</a> = 64000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da5ff13a09a232327578c69159f7564da8">AUD_AAC_BPS_96K</a> = 96000,   <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da8806920e563eca6c76b225185f24f191">AUD_AAC_BPS_128K</a> = 128000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5da7584ca8ebd583c448c5e2ff4957448f7">AUD_AAC_BPS_256K</a> = 256000, <a href="codec.md#ggac8cc627a9912e6a338396a6f19bbba5dade0faf8053bab953b55bc3e4d20341d5">AUD_AAC_BPS_320K</a> = 320000 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417246485084825"><a name="p1417246485084825"></a><a name="p1417246485084825"></a>Enumerates audio bit rates.</p>
</td>
</tr>
<tr id="row872409214084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2114769925084825"><a name="p2114769925084825"></a><a name="p2114769925084825"></a><a href="codec.md#ga8a15793172118d64d8adeba0c8544e84">StreamFlagType</a> {   <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84ae0da6ed262d36cb4de4b63cd25889ea2">STREAM_FLAG_KEYFRAME</a> = 1, <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84a9a06fdc891d28272ba6651ca9791d166">STREAM_FLAG_CODEC_SPECIFIC_INF</a> = 2, <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84abe40ab8f6da71b5a7d6a382954dc5d4f">STREAM_FLAG_EOS</a> = 4, <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84a7809fe65541dc27f50ba4952685c34bd">STREAM_FLAG_PART_OF_FRAME</a> = 8,   <a href="codec.md#gga8a15793172118d64d8adeba0c8544e84abb9a3fba052c516ac141e34ea9fa6dca">STREAM_FLAG_END_OF_FRAME</a> = 16 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052639450084825"><a name="p1052639450084825"></a><a name="p1052639450084825"></a>Enumerates stream flags.</p>
</td>
</tr>
<tr id="row1922850897084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793073483084825"><a name="p793073483084825"></a><a name="p793073483084825"></a><a href="codec.md#gadf8e136713c0691010d2bec6ba63e9cf">BufferType</a> { <a href="codec.md#ggadf8e136713c0691010d2bec6ba63e9cfabc56eeb37d99d582a14b44fb0ef4cabc">BUFFER_TYPE_VIRTUAL</a> = 0, <a href="codec.md#ggadf8e136713c0691010d2bec6ba63e9cfa4583aeaa2921c629ee785dbee184f421">BUFFER_TYPE_FD</a>, <a href="codec.md#ggadf8e136713c0691010d2bec6ba63e9cfa4bc0e24b5ce589d284b1771fc27c3d09">BUFFER_TYPE_HANDLE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1475771307084825"><a name="p1475771307084825"></a><a name="p1475771307084825"></a>Enumerates buffer types.</p>
</td>
</tr>
<tr id="row791373551084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037329082084825"><a name="p2037329082084825"></a><a name="p2037329082084825"></a><a href="codec.md#ga1bee586eafa91dfb60f94ba40fc95faa">AvCodecMime</a> {   <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaa4deff5e22cd5e2e83b6042880ad31863">MEDIA_MIMETYPE_IMAGE_JPEG</a> = 0, <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaa3db11a46c7f4bb848e6f0604268e41e3">MEDIA_MIMETYPE_VIDEO_AVC</a>, <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaaaf430209c9262e6fcd5cd8f97dafe614">MEDIA_MIMETYPE_VIDEO_HEVC</a>, <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaac03eb65aaf7aff393e223346feb30415">MEDIA_MIMETYPE_AUDIO_AAC</a>,   <a href="codec.md#gga1bee586eafa91dfb60f94ba40fc95faaaa2fa953bd51d8ee18191315c7187fc96">MEDIA_MIMETYPE_INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135616550084825"><a name="p135616550084825"></a><a name="p135616550084825"></a>Enumerates MIME types.</p>
</td>
</tr>
<tr id="row152160414084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2030807974084825"><a name="p2030807974084825"></a><a name="p2030807974084825"></a><a href="codec.md#ga85b10143618f300ff4f5bc6d45c72c01">Profile</a> {   <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a6d67944b4958ad33b0eeb851bbcd169f">INVALID_PROFILE</a> = 0, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ad91765d6dcad7253a924d3cb30501e44">AAC_LC_PROFILE</a> = 0x1000, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01aada4d857818cd9aa1ad62cdf608dab6b">AAC_MAIN_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ab4255dc0e7450af4f526b85acbabfd3e">AAC_HE_V1_PROFILE</a>,   <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a9b54f7a8c45ea6d4804133d8de4b8dd8">AAC_HE_V2_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01afaaacd4f6bdadac28b5cf49ae8f8470a">AAC_LD_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a7c8028283d1ff60e486b3305bf8c1adc">AAC_ELD_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a5bab002f00d3d7281aedc4807123a47a">AVC_BASELINE_PROFILE</a> = 0x2000,   <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a323c1d6e02363f1717f7e6b33fd9a646">AVC_MAIN_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ab9406e6bf30a0c128c3639cce51fe246">AVC_HIGH_PROFILE</a>, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01ae0d37dc2c7d39753a80f6e0ba64e5e22">HEVC_MAIN_PROFILE</a> = 0x3000, <a href="codec.md#gga85b10143618f300ff4f5bc6d45c72c01a811b9e02d8b0afa93e7ab8d2aa7e5de6">HEVC_MAIN_10_PROFILE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673073625084825"><a name="p673073625084825"></a><a name="p673073625084825"></a>Enumerates codec profiles.</p>
</td>
</tr>
<tr id="row242015648084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424980982084825"><a name="p424980982084825"></a><a name="p424980982084825"></a><a href="codec.md#ga221b779e6bb7b8d40677d7642bfefac5">Level</a> { <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5a6ab1f388a1a94d680bcbe808ec45a082">INVALID_LEVEL</a> = 0, <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5aee353b803bd93ba9e01e99e67b8afb49">AVC_LEVEL_1</a> = 0x1000, <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5a25819fec0bd7476c85122100b61536bb">HEVC_LEVEL_MAIN_1</a> = 0x2000, <a href="codec.md#gga221b779e6bb7b8d40677d7642bfefac5ab21d7836b0849b87149b7cdd7924d862">HEVC_LEVEL_MAIN_2</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1324514104084825"><a name="p1324514104084825"></a><a name="p1324514104084825"></a>Enumerates codec levels.</p>
</td>
</tr>
<tr id="row1335129901084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1617710549084825"><a name="p1617710549084825"></a><a name="p1617710549084825"></a><a href="codec.md#gaeae808d52153b2e33c6815162bbd11e0">AllocateBufferMode</a> { <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0ae8110d24a63ec0b86785ea48c8ecca42">ALLOCATE_INPUT_BUFFER_CODEC</a> = 0x1, <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0ae09681fcb839aa54acd974d872e3020d">ALLOCATE_INPUT_BUFFER_USER</a> = 0x2, <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0a73f74ceb227e306dbe940289a138bdf9">ALLOCATE_OUTPUT_BUFFER_CODEC</a> = 0x4, <a href="codec.md#ggaeae808d52153b2e33c6815162bbd11e0a81113cd1f553c8e05eb9bd59fdb58bed">ALLOCATE_OUTPUT_BUFFER_USER</a> = 0x8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257026739084825"><a name="p257026739084825"></a><a name="p257026739084825"></a>Enumerates allocation modes of input and output buffers.</p>
</td>
</tr>
<tr id="row1588778024084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1195273270084825"><a name="p1195273270084825"></a><a name="p1195273270084825"></a><a href="codec.md#gae5751aa8514dcaf2217df12db5ef57a1">CapsMask</a> { <a href="codec.md#ggae5751aa8514dcaf2217df12db5ef57a1afe6e93325882ea7c27503f79d0b2dcae">ADAPTIVE_PLAYBACK</a> = 0x1, <a href="codec.md#ggae5751aa8514dcaf2217df12db5ef57a1ad0c1ab7c365efc53a4de146b91f1a10f">SECURE_PLAYBACK</a> = 0x2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1395353889084825"><a name="p1395353889084825"></a><a name="p1395353889084825"></a>Enumerates playback capabilities.</p>
</td>
</tr>
<tr id="row1214105481084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8419219084825"><a name="p8419219084825"></a><a name="p8419219084825"></a><a href="codec.md#ga2628ea8d12e8b2563c32f05dc7fff6fa">EventType</a> {   <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faa71cf6bf1e591a86cb536668cda0f2a00">EventError</a>, <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faaab9f6e22232b045b85118bdda8aac6db">EventFlushCompelte</a>, <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faa864f301176ff05ad003bc6e89eb2cb93">EventStopCompelte</a>, <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faaeb0fb0bb31b20a141d015d9a92c629ac">EventOutFormatChanged</a>,   <a href="codec.md#gga2628ea8d12e8b2563c32f05dc7fff6faa70203255ab263a903886b8f774d5c4aa">EventMax</a> = 0x1FFFFFFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1671423658084825"><a name="p1671423658084825"></a><a name="p1671423658084825"></a>Enumerates event types.</p>
</td>
</tr>
<tr id="row2036786231084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p543230122084825"><a name="p543230122084825"></a><a name="p543230122084825"></a><a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> { <a href="codec.md#gga8ef30fa9c08e08c8706653571f9f5b81a833326d0b04dd281eaf006c46842250d">INPUT_TYPE</a>, <a href="codec.md#gga8ef30fa9c08e08c8706653571f9f5b81a9e3da5a3721894f1552c2715c1fbe95c">OUTPUT_TYPE</a>, <a href="codec.md#gga8ef30fa9c08e08c8706653571f9f5b81a46bcae2d9d2268e6a0c9259b9aebfc2f">ALL_TYPE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p173869113084825"><a name="p173869113084825"></a><a name="p173869113084825"></a>Enumerates input and output types.</p>
</td>
</tr>
<tr id="row1677779007084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1411241237084825"><a name="p1411241237084825"></a><a name="p1411241237084825"></a><a href="codec.md#gacc0fd55192fd9f663121b037b06f41e8">BufferMode</a> { <a href="codec.md#ggacc0fd55192fd9f663121b037b06f41e8adc7588f17692aa631f375290d50a2c8e">INTERNAL</a>, <a href="codec.md#ggacc0fd55192fd9f663121b037b06f41e8a63fbb9fe7b9a695d3a65541465cb99d5">EXTERNAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p991783187084825"><a name="p991783187084825"></a><a name="p991783187084825"></a>Enumerates allocation types.</p>
</td>
</tr>
<tr id="row735889262084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356864074084825"><a name="p1356864074084825"></a><a name="p1356864074084825"></a>{ <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a750142c991cfbb45e81a11453c757cd8">CODEC_ERR_STREAM_BUF_FULL</a> = 100, <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a07abd749dca99a6cde8e4d03acc075f6">CODEC_ERR_FRAME_BUF_EMPTY</a>, <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a504a9ea3cbe78aa1ba2423ee702151ac">CODEC_RECEIVE_EOS</a>, <a href="codec.md#gga99fb83031ce9923c84392b4e92f956b5a969385c1fbe6b30ab16b87775b06a074">CODEC_ERR_INVALID_OP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p112850911084825"><a name="p112850911084825"></a><a name="p112850911084825"></a>Enumerates codec error types.</p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table469446116084825"></a>
<table><thead align="left"><tr id="row735381581084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p675116051084825"><a name="p675116051084825"></a><a name="p675116051084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1471115424084825"><a name="p1471115424084825"></a><a name="p1471115424084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row808720248084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8536025084825"><a name="p8536025084825"></a><a name="p8536025084825"></a><a href="codec.md#gadb2714f1e7a69419cefd38a2ad1f9829">CodecInit</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881610208084825"><a name="p881610208084825"></a><a name="p881610208084825"></a>int32_t</p>
<p id="p879240661084825"><a name="p879240661084825"></a><a name="p879240661084825"></a>Initializes the internal audio and video submodules of the codec.</p>
</td>
</tr>
<tr id="row2134246526084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1894269238084825"><a name="p1894269238084825"></a><a name="p1894269238084825"></a><a href="codec.md#ga2d6eb231ca7766990cfa8c1841637245">CodecDeinit</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549072631084825"><a name="p549072631084825"></a><a name="p549072631084825"></a>int32_t</p>
<p id="p1483140872084825"><a name="p1483140872084825"></a><a name="p1483140872084825"></a>Deinitializes the internal audio and video submodules of the codec.</p>
</td>
</tr>
<tr id="row593920580084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250701233084825"><a name="p250701233084825"></a><a name="p250701233084825"></a><a href="codec.md#gaf0bb69d2f8c5ad0fec6959b353ee1acd">CodecEnumerateCapbility</a> (uint32_t <a href="en-us_topic_0000001055308029.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, <a href="codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3">CodecCapbility</a> *cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538626264084825"><a name="p1538626264084825"></a><a name="p1538626264084825"></a>int32_t</p>
<p id="p431378113084825"><a name="p431378113084825"></a><a name="p431378113084825"></a>Obtains the capabilities of a specified media type based on an index.</p>
</td>
</tr>
<tr id="row50243688084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p335863823084825"><a name="p335863823084825"></a><a name="p335863823084825"></a><a href="codec.md#ga1a6fbf6e84e01fdc1af59caa4203ce8e">CodecGetCapbility</a> (<a href="codec.md#ga1bee586eafa91dfb60f94ba40fc95faa">AvCodecMime</a> mime, <a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a> type, uint32_t flags, <a href="codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3">CodecCapbility</a> *cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1678024178084825"><a name="p1678024178084825"></a><a name="p1678024178084825"></a>int32_t</p>
<p id="p686644790084825"><a name="p686644790084825"></a><a name="p686644790084825"></a>Obtains the capabilities of a specified media type.</p>
</td>
</tr>
<tr id="row1550062079084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1949185423084825"><a name="p1949185423084825"></a><a name="p1949185423084825"></a><a href="codec.md#ga74aa0395a51f004390f7a92fb68faddd">CodecCreate</a> (const char *name, const <a href="en-us_topic_0000001054718161.md">Param</a> *attr, int len, <a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2086818545084825"><a name="p2086818545084825"></a><a name="p2086818545084825"></a>int32_t</p>
<p id="p157882726084825"><a name="p157882726084825"></a><a name="p157882726084825"></a>Creates a specific codec component and returns the component context through a handle.</p>
</td>
</tr>
<tr id="row1240223260084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402985881084825"><a name="p402985881084825"></a><a name="p402985881084825"></a><a href="codec.md#ga1bc0592b05e4f687e2bef2ffb83102b8">CodecDestroy</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444415920084825"><a name="p444415920084825"></a><a name="p444415920084825"></a>int32_t</p>
<p id="p235999774084825"><a name="p235999774084825"></a><a name="p235999774084825"></a>Destroys a codec component.</p>
</td>
</tr>
<tr id="row98085139084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p285289782084825"><a name="p285289782084825"></a><a name="p285289782084825"></a><a href="codec.md#ga36a994c5f9f4d104aad0c24b5e8cbd37">CodecSetPortMode</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> type, <a href="codec.md#gacc0fd55192fd9f663121b037b06f41e8">BufferMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134406707084825"><a name="p2134406707084825"></a><a name="p2134406707084825"></a>int32_t</p>
<p id="p1045563105084825"><a name="p1045563105084825"></a><a name="p1045563105084825"></a>Sets the input or output buffer mode.</p>
</td>
</tr>
<tr id="row308345671084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1796874869084825"><a name="p1796874869084825"></a><a name="p1796874869084825"></a><a href="codec.md#gaa080cf23aa5f77b30f3b90a026d97cc0">CodecSetParameter</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, const <a href="en-us_topic_0000001054718161.md">Param</a> *params, int paramCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p234480367084825"><a name="p234480367084825"></a><a name="p234480367084825"></a>int32_t</p>
<p id="p655663887084825"><a name="p655663887084825"></a><a name="p655663887084825"></a>Sets parameters required by a codec component.</p>
</td>
</tr>
<tr id="row1673580638084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505906453084825"><a name="p1505906453084825"></a><a name="p1505906453084825"></a><a href="codec.md#ga1d812eac032e3e05cf5bf71b03e93f65">CodecGetParameter</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="en-us_topic_0000001054718161.md">Param</a> *params, int paramCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946506095084825"><a name="p1946506095084825"></a><a name="p1946506095084825"></a>int32_t</p>
<p id="p345258983084825"><a name="p345258983084825"></a><a name="p345258983084825"></a>Obtains parameters from a codec component.</p>
</td>
</tr>
<tr id="row1835052957084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p796230034084825"><a name="p796230034084825"></a><a name="p796230034084825"></a><a href="codec.md#ga38c1744b0b4be5817ef49556ae665d18">CodecStart</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699466772084825"><a name="p699466772084825"></a><a name="p699466772084825"></a>int32_t</p>
<p id="p2060212103084825"><a name="p2060212103084825"></a><a name="p2060212103084825"></a>Starts a codec component.</p>
</td>
</tr>
<tr id="row1387072533084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431348343084825"><a name="p1431348343084825"></a><a name="p1431348343084825"></a><a href="codec.md#ga8e7913c052c2e45e193fb0aab3f5c7fd">CodecStop</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1728487306084825"><a name="p1728487306084825"></a><a name="p1728487306084825"></a>int32_t</p>
<p id="p815804141084825"><a name="p815804141084825"></a><a name="p815804141084825"></a>Stops a codec component.</p>
</td>
</tr>
<tr id="row992939075084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1844650421084825"><a name="p1844650421084825"></a><a name="p1844650421084825"></a><a href="codec.md#gaa6ed6c24e29f8fdfbbb0a3d562260a6a">CodecFlush</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> directType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2024973804084825"><a name="p2024973804084825"></a><a name="p2024973804084825"></a>int32_t</p>
<p id="p1870204130084825"><a name="p1870204130084825"></a><a name="p1870204130084825"></a>Clears the cache when the codec component is the running state.</p>
</td>
</tr>
<tr id="row350278506084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p750669691084825"><a name="p750669691084825"></a><a name="p750669691084825"></a><a href="codec.md#ga0daece8dbf22da84f926761c994819bc">CodecQueueInput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, const <a href="en-us_topic_0000001054879536.md">InputInfo</a> *inputData, uint32_t timeoutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1876284945084825"><a name="p1876284945084825"></a><a name="p1876284945084825"></a>int32_t</p>
<p id="p1670575027084825"><a name="p1670575027084825"></a><a name="p1670575027084825"></a>Queues input data.</p>
</td>
</tr>
<tr id="row936542099084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p345775572084825"><a name="p345775572084825"></a><a name="p345775572084825"></a><a href="codec.md#ga91d7e1566c90d7cb9ac846eecad0024f">CodecDequeInput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, uint32_t timeoutMs, <a href="en-us_topic_0000001054879536.md">InputInfo</a> *inputData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1558651954084825"><a name="p1558651954084825"></a><a name="p1558651954084825"></a>int32_t</p>
<p id="p302088596084825"><a name="p302088596084825"></a><a name="p302088596084825"></a>Dequeues input data that has been used.</p>
</td>
</tr>
<tr id="row1275990819084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p536001415084825"><a name="p536001415084825"></a><a name="p536001415084825"></a><a href="codec.md#gac98f3505082c3cb2413d9e95eef9c804">CodecQueueOutput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="en-us_topic_0000001054918167.md">OutputInfo</a> *outInfo, uint32_t timeoutMs, int releaseFenceFd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1599284982084825"><a name="p1599284982084825"></a><a name="p1599284982084825"></a>int32_t</p>
<p id="p927826917084825"><a name="p927826917084825"></a><a name="p927826917084825"></a>Queues output data.</p>
</td>
</tr>
<tr id="row200259352084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029505027084825"><a name="p1029505027084825"></a><a name="p1029505027084825"></a><a href="codec.md#gab575752467517eb8e6766773c1e3fb23">CodecDequeueOutput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, uint32_t timeoutMs, int *acquireFd, <a href="en-us_topic_0000001054918167.md">OutputInfo</a> *outInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p271461663084825"><a name="p271461663084825"></a><a name="p271461663084825"></a>int32_t</p>
<p id="p804939849084825"><a name="p804939849084825"></a><a name="p804939849084825"></a>Dequeues output data.</p>
</td>
</tr>
<tr id="row616284644084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1751143957084825"><a name="p1751143957084825"></a><a name="p1751143957084825"></a><a href="codec.md#ga28ec6149d05765ee75f4836e0b092406">CodecSetCallback</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, const <a href="en-us_topic_0000001055358102.md">CodecCallback</a> *cb, <a href="codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> instance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p546794689084825"><a name="p546794689084825"></a><a name="p546794689084825"></a>int32_t</p>
<p id="p1749795797084825"><a name="p1749795797084825"></a><a name="p1749795797084825"></a>Sets the callback function.</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section266862787084825"></a>

## **Enumeration Type Documentation**<a name="section645767794084825"></a>

## anonymous enum<a name="ga99fb83031ce9923c84392b4e92f956b5"></a>

```
anonymous enum
```

**Description:**

Enumerates codec error types.

<a name="table1821042936084825"></a>
<table><thead align="left"><tr id="row327443372084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p179775494084825"><a name="p179775494084825"></a><a name="p179775494084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p255849094084825"><a name="p255849094084825"></a><a name="p255849094084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1082572682084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry819846878084825p0"><a name="entry819846878084825p0"></a><a name="entry819846878084825p0"></a><strong id="gga99fb83031ce9923c84392b4e92f956b5a750142c991cfbb45e81a11453c757cd8"><a name="gga99fb83031ce9923c84392b4e92f956b5a750142c991cfbb45e81a11453c757cd8"></a><a name="gga99fb83031ce9923c84392b4e92f956b5a750142c991cfbb45e81a11453c757cd8"></a></strong>CODEC_ERR_STREAM_BUF_FULL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p245342642084825"><a name="p245342642084825"></a><a name="p245342642084825"></a>Elementary stream buffer queue is full.</p>
<p id="p135902149155"><a name="p135902149155"></a><a name="p135902149155"></a></p>
</td>
</tr>
<tr id="row1590505081084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry757892643084825p0"><a name="entry757892643084825p0"></a><a name="entry757892643084825p0"></a><strong id="gga99fb83031ce9923c84392b4e92f956b5a07abd749dca99a6cde8e4d03acc075f6"><a name="gga99fb83031ce9923c84392b4e92f956b5a07abd749dca99a6cde8e4d03acc075f6"></a><a name="gga99fb83031ce9923c84392b4e92f956b5a07abd749dca99a6cde8e4d03acc075f6"></a></strong>CODEC_ERR_FRAME_BUF_EMPTY</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007217813084825"><a name="p2007217813084825"></a><a name="p2007217813084825"></a>Frame buffer queue is empty.</p>
<p id="p13590161417156"><a name="p13590161417156"></a><a name="p13590161417156"></a></p>
</td>
</tr>
<tr id="row688211139084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1131956328084825p0"><a name="entry1131956328084825p0"></a><a name="entry1131956328084825p0"></a><strong id="gga99fb83031ce9923c84392b4e92f956b5a504a9ea3cbe78aa1ba2423ee702151ac"><a name="gga99fb83031ce9923c84392b4e92f956b5a504a9ea3cbe78aa1ba2423ee702151ac"></a><a name="gga99fb83031ce9923c84392b4e92f956b5a504a9ea3cbe78aa1ba2423ee702151ac"></a></strong>CODEC_RECEIVE_EOS</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1218037147084825"><a name="p1218037147084825"></a><a name="p1218037147084825"></a>End of streams</p>
<p id="p059091418155"><a name="p059091418155"></a><a name="p059091418155"></a></p>
</td>
</tr>
<tr id="row823846759084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry933841346084825p0"><a name="entry933841346084825p0"></a><a name="entry933841346084825p0"></a><strong id="gga99fb83031ce9923c84392b4e92f956b5a969385c1fbe6b30ab16b87775b06a074"><a name="gga99fb83031ce9923c84392b4e92f956b5a969385c1fbe6b30ab16b87775b06a074"></a><a name="gga99fb83031ce9923c84392b4e92f956b5a969385c1fbe6b30ab16b87775b06a074"></a></strong>CODEC_ERR_INVALID_OP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343155531084825"><a name="p343155531084825"></a><a name="p343155531084825"></a>Invalid operation</p>
<p id="p1659041421520"><a name="p1659041421520"></a><a name="p1659041421520"></a></p>
</td>
</tr>
</tbody>
</table>

## AllocateBufferMode<a name="gaeae808d52153b2e33c6815162bbd11e0"></a>

```
enum [AllocateBufferMode](codec.md#gaeae808d52153b2e33c6815162bbd11e0)
```

**Description:**

Enumerates allocation modes of input and output buffers.

<a name="table535921715084825"></a>
<table><thead align="left"><tr id="row1871440056084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p946272779084825"><a name="p946272779084825"></a><a name="p946272779084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1555113777084825"><a name="p1555113777084825"></a><a name="p1555113777084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row344281322084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1104700900084825p0"><a name="entry1104700900084825p0"></a><a name="entry1104700900084825p0"></a><strong id="ggaeae808d52153b2e33c6815162bbd11e0ae8110d24a63ec0b86785ea48c8ecca42"><a name="ggaeae808d52153b2e33c6815162bbd11e0ae8110d24a63ec0b86785ea48c8ecca42"></a><a name="ggaeae808d52153b2e33c6815162bbd11e0ae8110d24a63ec0b86785ea48c8ecca42"></a></strong>ALLOCATE_INPUT_BUFFER_CODEC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619610869084825"><a name="p1619610869084825"></a><a name="p1619610869084825"></a>Input buffer allocated within the Codec module</p>
<p id="p859641431512"><a name="p859641431512"></a><a name="p859641431512"></a></p>
</td>
</tr>
<tr id="row2114911947084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1414200091084825p0"><a name="entry1414200091084825p0"></a><a name="entry1414200091084825p0"></a><strong id="ggaeae808d52153b2e33c6815162bbd11e0ae09681fcb839aa54acd974d872e3020d"><a name="ggaeae808d52153b2e33c6815162bbd11e0ae09681fcb839aa54acd974d872e3020d"></a><a name="ggaeae808d52153b2e33c6815162bbd11e0ae09681fcb839aa54acd974d872e3020d"></a></strong>ALLOCATE_INPUT_BUFFER_USER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p5438702084825"><a name="p5438702084825"></a><a name="p5438702084825"></a>Input buffer allocated by an external user</p>
<p id="p13596314171518"><a name="p13596314171518"></a><a name="p13596314171518"></a></p>
</td>
</tr>
<tr id="row836504789084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry645800844084825p0"><a name="entry645800844084825p0"></a><a name="entry645800844084825p0"></a><strong id="ggaeae808d52153b2e33c6815162bbd11e0a73f74ceb227e306dbe940289a138bdf9"><a name="ggaeae808d52153b2e33c6815162bbd11e0a73f74ceb227e306dbe940289a138bdf9"></a><a name="ggaeae808d52153b2e33c6815162bbd11e0a73f74ceb227e306dbe940289a138bdf9"></a></strong>ALLOCATE_OUTPUT_BUFFER_CODEC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521606275084825"><a name="p1521606275084825"></a><a name="p1521606275084825"></a>Output buffer allocated within the Codec module</p>
<p id="p1159661415151"><a name="p1159661415151"></a><a name="p1159661415151"></a></p>
</td>
</tr>
<tr id="row1330558922084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry459222374084825p0"><a name="entry459222374084825p0"></a><a name="entry459222374084825p0"></a><strong id="ggaeae808d52153b2e33c6815162bbd11e0a81113cd1f553c8e05eb9bd59fdb58bed"><a name="ggaeae808d52153b2e33c6815162bbd11e0a81113cd1f553c8e05eb9bd59fdb58bed"></a><a name="ggaeae808d52153b2e33c6815162bbd11e0a81113cd1f553c8e05eb9bd59fdb58bed"></a></strong>ALLOCATE_OUTPUT_BUFFER_USER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1190376983084825"><a name="p1190376983084825"></a><a name="p1190376983084825"></a>Output buffer allocated by an external user</p>
<p id="p25961014121517"><a name="p25961014121517"></a><a name="p25961014121517"></a></p>
</td>
</tr>
</tbody>
</table>

## AudioBitRate<a name="gac8cc627a9912e6a338396a6f19bbba5d"></a>

```
enum [AudioBitRate](codec.md#gac8cc627a9912e6a338396a6f19bbba5d)
```

**Description:**

Enumerates audio bit rates.

<a name="table1957715759084825"></a>
<table><thead align="left"><tr id="row1361795940084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1007629460084825"><a name="p1007629460084825"></a><a name="p1007629460084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p551523172084825"><a name="p551523172084825"></a><a name="p551523172084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row853757827084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1861987848084825p0"><a name="entry1861987848084825p0"></a><a name="entry1861987848084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da1b31811befaf84b164684a38fa022f43"><a name="ggac8cc627a9912e6a338396a6f19bbba5da1b31811befaf84b164684a38fa022f43"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da1b31811befaf84b164684a38fa022f43"></a></strong>AUD_AAC_BPS_8K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868302489084825"><a name="p1868302489084825"></a><a name="p1868302489084825"></a>8 kbit/s</p>
<p id="p66001214111514"><a name="p66001214111514"></a><a name="p66001214111514"></a></p>
</td>
</tr>
<tr id="row1940620436084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2084328120084825p0"><a name="entry2084328120084825p0"></a><a name="entry2084328120084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5dab71f0668b9fc4955fe059339ea663e8e"><a name="ggac8cc627a9912e6a338396a6f19bbba5dab71f0668b9fc4955fe059339ea663e8e"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5dab71f0668b9fc4955fe059339ea663e8e"></a></strong>AUD_AAC_BPS_16K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1486350351084825"><a name="p1486350351084825"></a><a name="p1486350351084825"></a>16 kbit/s</p>
<p id="p1160031416156"><a name="p1160031416156"></a><a name="p1160031416156"></a></p>
</td>
</tr>
<tr id="row479815560084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2074686340084825p0"><a name="entry2074686340084825p0"></a><a name="entry2074686340084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da3cc22f17e3fddb9d081aa3d826d31ac9"><a name="ggac8cc627a9912e6a338396a6f19bbba5da3cc22f17e3fddb9d081aa3d826d31ac9"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da3cc22f17e3fddb9d081aa3d826d31ac9"></a></strong>AUD_AAC_BPS_22K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088321943084825"><a name="p2088321943084825"></a><a name="p2088321943084825"></a>22 kbit/s</p>
<p id="p1260021431510"><a name="p1260021431510"></a><a name="p1260021431510"></a></p>
</td>
</tr>
<tr id="row1744364639084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1361802956084825p0"><a name="entry1361802956084825p0"></a><a name="entry1361802956084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5dadb78faf7877b6f70fd9b55406dcbd6b0"><a name="ggac8cc627a9912e6a338396a6f19bbba5dadb78faf7877b6f70fd9b55406dcbd6b0"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5dadb78faf7877b6f70fd9b55406dcbd6b0"></a></strong>AUD_AAC_BPS_24K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1104801004084825"><a name="p1104801004084825"></a><a name="p1104801004084825"></a>24 kbit/s</p>
<p id="p96003145158"><a name="p96003145158"></a><a name="p96003145158"></a></p>
</td>
</tr>
<tr id="row2117078763084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1879061325084825p0"><a name="entry1879061325084825p0"></a><a name="entry1879061325084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da974bd8a79bb6004f84b670f2496a33b9"><a name="ggac8cc627a9912e6a338396a6f19bbba5da974bd8a79bb6004f84b670f2496a33b9"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da974bd8a79bb6004f84b670f2496a33b9"></a></strong>AUD_AAC_BPS_32K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983437982084825"><a name="p983437982084825"></a><a name="p983437982084825"></a>32 kbit/s</p>
<p id="p56007147154"><a name="p56007147154"></a><a name="p56007147154"></a></p>
</td>
</tr>
<tr id="row973181921084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1883335901084825p0"><a name="entry1883335901084825p0"></a><a name="entry1883335901084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da7d330b118800e19500f2f4a9b6af38f8"><a name="ggac8cc627a9912e6a338396a6f19bbba5da7d330b118800e19500f2f4a9b6af38f8"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da7d330b118800e19500f2f4a9b6af38f8"></a></strong>AUD_AAC_BPS_48K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1835589899084825"><a name="p1835589899084825"></a><a name="p1835589899084825"></a>48 kbit/s</p>
<p id="p360081414155"><a name="p360081414155"></a><a name="p360081414155"></a></p>
</td>
</tr>
<tr id="row1835658936084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1201879719084825p0"><a name="entry1201879719084825p0"></a><a name="entry1201879719084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da2b8757624080a60f39d848dac7820e99"><a name="ggac8cc627a9912e6a338396a6f19bbba5da2b8757624080a60f39d848dac7820e99"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da2b8757624080a60f39d848dac7820e99"></a></strong>AUD_AAC_BPS_64K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1885489845084825"><a name="p1885489845084825"></a><a name="p1885489845084825"></a>64 kbit/s</p>
<p id="p76009144153"><a name="p76009144153"></a><a name="p76009144153"></a></p>
</td>
</tr>
<tr id="row135933632084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1792010900084825p0"><a name="entry1792010900084825p0"></a><a name="entry1792010900084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da5ff13a09a232327578c69159f7564da8"><a name="ggac8cc627a9912e6a338396a6f19bbba5da5ff13a09a232327578c69159f7564da8"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da5ff13a09a232327578c69159f7564da8"></a></strong>AUD_AAC_BPS_96K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2147384432084825"><a name="p2147384432084825"></a><a name="p2147384432084825"></a>96 kbit/s</p>
<p id="p060061461514"><a name="p060061461514"></a><a name="p060061461514"></a></p>
</td>
</tr>
<tr id="row1823953190084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1613151548084825p0"><a name="entry1613151548084825p0"></a><a name="entry1613151548084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da8806920e563eca6c76b225185f24f191"><a name="ggac8cc627a9912e6a338396a6f19bbba5da8806920e563eca6c76b225185f24f191"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da8806920e563eca6c76b225185f24f191"></a></strong>AUD_AAC_BPS_128K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711818533084825"><a name="p711818533084825"></a><a name="p711818533084825"></a>128 kbit/s</p>
<p id="p860001411518"><a name="p860001411518"></a><a name="p860001411518"></a></p>
</td>
</tr>
<tr id="row354062632084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1423921915084825p0"><a name="entry1423921915084825p0"></a><a name="entry1423921915084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5da7584ca8ebd583c448c5e2ff4957448f7"><a name="ggac8cc627a9912e6a338396a6f19bbba5da7584ca8ebd583c448c5e2ff4957448f7"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5da7584ca8ebd583c448c5e2ff4957448f7"></a></strong>AUD_AAC_BPS_256K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p64179345084825"><a name="p64179345084825"></a><a name="p64179345084825"></a>256 kbit/s</p>
<p id="p18600141451515"><a name="p18600141451515"></a><a name="p18600141451515"></a></p>
</td>
</tr>
<tr id="row691113962084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry815786393084825p0"><a name="entry815786393084825p0"></a><a name="entry815786393084825p0"></a><strong id="ggac8cc627a9912e6a338396a6f19bbba5dade0faf8053bab953b55bc3e4d20341d5"><a name="ggac8cc627a9912e6a338396a6f19bbba5dade0faf8053bab953b55bc3e4d20341d5"></a><a name="ggac8cc627a9912e6a338396a6f19bbba5dade0faf8053bab953b55bc3e4d20341d5"></a></strong>AUD_AAC_BPS_320K</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740759212084825"><a name="p740759212084825"></a><a name="p740759212084825"></a>320 kbit/s</p>
<p id="p2060001411153"><a name="p2060001411153"></a><a name="p2060001411153"></a></p>
</td>
</tr>
</tbody>
</table>

## AudioSampleRate<a name="gaa0280074adafe6d2581d31f71512b842"></a>

```
enum [AudioSampleRate](codec.md#gaa0280074adafe6d2581d31f71512b842)
```

**Description:**

Enumerates audio sampling rates.

<a name="table1621955776084825"></a>
<table><thead align="left"><tr id="row108801228084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p62049588084825"><a name="p62049588084825"></a><a name="p62049588084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p8639499084825"><a name="p8639499084825"></a><a name="p8639499084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row402974449084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry112806518084825p0"><a name="entry112806518084825p0"></a><a name="entry112806518084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a65d5a1e4d1f048a33d29c9a3b6f540bd"><a name="ggaa0280074adafe6d2581d31f71512b842a65d5a1e4d1f048a33d29c9a3b6f540bd"></a><a name="ggaa0280074adafe6d2581d31f71512b842a65d5a1e4d1f048a33d29c9a3b6f540bd"></a></strong>AUD_SAMPLE_RATE_8000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1860230265084825"><a name="p1860230265084825"></a><a name="p1860230265084825"></a>8 KHz</p>
<p id="p960931417157"><a name="p960931417157"></a><a name="p960931417157"></a></p>
</td>
</tr>
<tr id="row148832421084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1622415059084825p0"><a name="entry1622415059084825p0"></a><a name="entry1622415059084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842ac8379e14b05cdac5edfcc931ac8b33a9"><a name="ggaa0280074adafe6d2581d31f71512b842ac8379e14b05cdac5edfcc931ac8b33a9"></a><a name="ggaa0280074adafe6d2581d31f71512b842ac8379e14b05cdac5edfcc931ac8b33a9"></a></strong>AUD_SAMPLE_RATE_12000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p550267174084825"><a name="p550267174084825"></a><a name="p550267174084825"></a>12 KHz</p>
<p id="p11609171413151"><a name="p11609171413151"></a><a name="p11609171413151"></a></p>
</td>
</tr>
<tr id="row1832215132084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry779334533084825p0"><a name="entry779334533084825p0"></a><a name="entry779334533084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a57b1853b1e309bf1aa5b3a35b06b0f81"><a name="ggaa0280074adafe6d2581d31f71512b842a57b1853b1e309bf1aa5b3a35b06b0f81"></a><a name="ggaa0280074adafe6d2581d31f71512b842a57b1853b1e309bf1aa5b3a35b06b0f81"></a></strong>AUD_SAMPLE_RATE_11025</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p887354951084825"><a name="p887354951084825"></a><a name="p887354951084825"></a>11.025 KHz</p>
<p id="p560931414155"><a name="p560931414155"></a><a name="p560931414155"></a></p>
</td>
</tr>
<tr id="row1979805813084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1568403772084825p0"><a name="entry1568403772084825p0"></a><a name="entry1568403772084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a43395f0fe94ae2949778468e4488c3ee"><a name="ggaa0280074adafe6d2581d31f71512b842a43395f0fe94ae2949778468e4488c3ee"></a><a name="ggaa0280074adafe6d2581d31f71512b842a43395f0fe94ae2949778468e4488c3ee"></a></strong>AUD_SAMPLE_RATE_16000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878085285084825"><a name="p878085285084825"></a><a name="p878085285084825"></a>16 KHz</p>
<p id="p9609114161510"><a name="p9609114161510"></a><a name="p9609114161510"></a></p>
</td>
</tr>
<tr id="row407653513084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry406818953084825p0"><a name="entry406818953084825p0"></a><a name="entry406818953084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a5e8155ecfa865686a66e004e37ce1e54"><a name="ggaa0280074adafe6d2581d31f71512b842a5e8155ecfa865686a66e004e37ce1e54"></a><a name="ggaa0280074adafe6d2581d31f71512b842a5e8155ecfa865686a66e004e37ce1e54"></a></strong>AUD_SAMPLE_RATE_22050</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036507236084825"><a name="p2036507236084825"></a><a name="p2036507236084825"></a>22.050 KHz</p>
<p id="p260911431519"><a name="p260911431519"></a><a name="p260911431519"></a></p>
</td>
</tr>
<tr id="row1050666201084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1384251628084825p0"><a name="entry1384251628084825p0"></a><a name="entry1384251628084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842abd4c09d52f3da25adb108e9aa503119d"><a name="ggaa0280074adafe6d2581d31f71512b842abd4c09d52f3da25adb108e9aa503119d"></a><a name="ggaa0280074adafe6d2581d31f71512b842abd4c09d52f3da25adb108e9aa503119d"></a></strong>AUD_SAMPLE_RATE_24000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229207187084825"><a name="p1229207187084825"></a><a name="p1229207187084825"></a>24 KHz</p>
<p id="p1260991419153"><a name="p1260991419153"></a><a name="p1260991419153"></a></p>
</td>
</tr>
<tr id="row373596996084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2120019889084825p0"><a name="entry2120019889084825p0"></a><a name="entry2120019889084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a1f94827fe757ad2857d970638b6f8d66"><a name="ggaa0280074adafe6d2581d31f71512b842a1f94827fe757ad2857d970638b6f8d66"></a><a name="ggaa0280074adafe6d2581d31f71512b842a1f94827fe757ad2857d970638b6f8d66"></a></strong>AUD_SAMPLE_RATE_32000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790954681084825"><a name="p790954681084825"></a><a name="p790954681084825"></a>32 KHz</p>
<p id="p1960931411155"><a name="p1960931411155"></a><a name="p1960931411155"></a></p>
</td>
</tr>
<tr id="row1981976942084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1897231833084825p0"><a name="entry1897231833084825p0"></a><a name="entry1897231833084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842ac880553f2ee154a240d9414598e006a2"><a name="ggaa0280074adafe6d2581d31f71512b842ac880553f2ee154a240d9414598e006a2"></a><a name="ggaa0280074adafe6d2581d31f71512b842ac880553f2ee154a240d9414598e006a2"></a></strong>AUD_SAMPLE_RATE_44100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833393859084825"><a name="p833393859084825"></a><a name="p833393859084825"></a>44.1 KHz</p>
<p id="p1260941414153"><a name="p1260941414153"></a><a name="p1260941414153"></a></p>
</td>
</tr>
<tr id="row1260445510084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry520044653084825p0"><a name="entry520044653084825p0"></a><a name="entry520044653084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842ade6dd509c28b66127c42d2634866b89c"><a name="ggaa0280074adafe6d2581d31f71512b842ade6dd509c28b66127c42d2634866b89c"></a><a name="ggaa0280074adafe6d2581d31f71512b842ade6dd509c28b66127c42d2634866b89c"></a></strong>AUD_SAMPLE_RATE_48000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597774182084825"><a name="p1597774182084825"></a><a name="p1597774182084825"></a>48 KHz</p>
<p id="p16091714101510"><a name="p16091714101510"></a><a name="p16091714101510"></a></p>
</td>
</tr>
<tr id="row1434182360084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1781741112084825p0"><a name="entry1781741112084825p0"></a><a name="entry1781741112084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a925218c15bb8522796e623a09d99dbc3"><a name="ggaa0280074adafe6d2581d31f71512b842a925218c15bb8522796e623a09d99dbc3"></a><a name="ggaa0280074adafe6d2581d31f71512b842a925218c15bb8522796e623a09d99dbc3"></a></strong>AUD_SAMPLE_RATE_64000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1719542457084825"><a name="p1719542457084825"></a><a name="p1719542457084825"></a>64 KHz</p>
<p id="p86091814161516"><a name="p86091814161516"></a><a name="p86091814161516"></a></p>
</td>
</tr>
<tr id="row1698890021084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1925156062084825p0"><a name="entry1925156062084825p0"></a><a name="entry1925156062084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a48336a808a2ebcf5956995140e2d73dd"><a name="ggaa0280074adafe6d2581d31f71512b842a48336a808a2ebcf5956995140e2d73dd"></a><a name="ggaa0280074adafe6d2581d31f71512b842a48336a808a2ebcf5956995140e2d73dd"></a></strong>AUD_SAMPLE_RATE_96000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1398526396084825"><a name="p1398526396084825"></a><a name="p1398526396084825"></a>96 KHz</p>
<p id="p560981431510"><a name="p560981431510"></a><a name="p560981431510"></a></p>
</td>
</tr>
<tr id="row357724845084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry411670410084825p0"><a name="entry411670410084825p0"></a><a name="entry411670410084825p0"></a><strong id="ggaa0280074adafe6d2581d31f71512b842a0cb82ce52fb70b359a0b2232f7f465a2"><a name="ggaa0280074adafe6d2581d31f71512b842a0cb82ce52fb70b359a0b2232f7f465a2"></a><a name="ggaa0280074adafe6d2581d31f71512b842a0cb82ce52fb70b359a0b2232f7f465a2"></a></strong>AUD_SAMPLE_RATE_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67299404084825"><a name="p67299404084825"></a><a name="p67299404084825"></a>Invalid sampling rate</p>
<p id="p9609141415156"><a name="p9609141415156"></a><a name="p9609141415156"></a></p>
</td>
</tr>
</tbody>
</table>

## AudioSoundMode<a name="gacecb40e35c431a27385f7b439fc7a76c"></a>

```
enum [AudioSoundMode](codec.md#gacecb40e35c431a27385f7b439fc7a76c)
```

**Description:**

Enumerates audio channel modes.

<a name="table877423857084825"></a>
<table><thead align="left"><tr id="row321759144084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p871320715084825"><a name="p871320715084825"></a><a name="p871320715084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1983005398084825"><a name="p1983005398084825"></a><a name="p1983005398084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row916939266084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1382527730084825p0"><a name="entry1382527730084825p0"></a><a name="entry1382527730084825p0"></a><strong id="ggacecb40e35c431a27385f7b439fc7a76caef98cd29f4639de89778f1be521a1676"><a name="ggacecb40e35c431a27385f7b439fc7a76caef98cd29f4639de89778f1be521a1676"></a><a name="ggacecb40e35c431a27385f7b439fc7a76caef98cd29f4639de89778f1be521a1676"></a></strong>AUD_SOUND_MODE_MONO</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897943873084825"><a name="p897943873084825"></a><a name="p897943873084825"></a>Mono channel</p>
<p id="p1161917144151"><a name="p1161917144151"></a><a name="p1161917144151"></a></p>
</td>
</tr>
<tr id="row380521822084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry267915595084825p0"><a name="entry267915595084825p0"></a><a name="entry267915595084825p0"></a><strong id="ggacecb40e35c431a27385f7b439fc7a76ca9437f9e5186f7095fb50775eddc439d6"><a name="ggacecb40e35c431a27385f7b439fc7a76ca9437f9e5186f7095fb50775eddc439d6"></a><a name="ggacecb40e35c431a27385f7b439fc7a76ca9437f9e5186f7095fb50775eddc439d6"></a></strong>AUD_SOUND_MODE_STEREO</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941014567084825"><a name="p941014567084825"></a><a name="p941014567084825"></a>Stereo mode</p>
<p id="p13619141419150"><a name="p13619141419150"></a><a name="p13619141419150"></a></p>
</td>
</tr>
<tr id="row2124052993084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1945113715084825p0"><a name="entry1945113715084825p0"></a><a name="entry1945113715084825p0"></a><strong id="ggacecb40e35c431a27385f7b439fc7a76ca53160e7e334a8629bec602c42d2ee5e6"><a name="ggacecb40e35c431a27385f7b439fc7a76ca53160e7e334a8629bec602c42d2ee5e6"></a><a name="ggacecb40e35c431a27385f7b439fc7a76ca53160e7e334a8629bec602c42d2ee5e6"></a></strong>AUD_SOUND_MODE_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1254170621084825"><a name="p1254170621084825"></a><a name="p1254170621084825"></a>Invalid mode</p>
<p id="p156191814161515"><a name="p156191814161515"></a><a name="p156191814161515"></a></p>
</td>
</tr>
</tbody>
</table>

## AvCodecMime<a name="ga1bee586eafa91dfb60f94ba40fc95faa"></a>

```
enum [AvCodecMime](codec.md#ga1bee586eafa91dfb60f94ba40fc95faa)
```

**Description:**

Enumerates MIME types.

<a name="table1001750912084825"></a>
<table><thead align="left"><tr id="row1307259854084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p350541657084825"><a name="p350541657084825"></a><a name="p350541657084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p357649224084825"><a name="p357649224084825"></a><a name="p357649224084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row983394740084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry621379236084825p0"><a name="entry621379236084825p0"></a><a name="entry621379236084825p0"></a><strong id="gga1bee586eafa91dfb60f94ba40fc95faaa4deff5e22cd5e2e83b6042880ad31863"><a name="gga1bee586eafa91dfb60f94ba40fc95faaa4deff5e22cd5e2e83b6042880ad31863"></a><a name="gga1bee586eafa91dfb60f94ba40fc95faaa4deff5e22cd5e2e83b6042880ad31863"></a></strong>MEDIA_MIMETYPE_IMAGE_JPEG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1392981897084825"><a name="p1392981897084825"></a><a name="p1392981897084825"></a>JPEG image</p>
<p id="p3623161420159"><a name="p3623161420159"></a><a name="p3623161420159"></a></p>
</td>
</tr>
<tr id="row285865484084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2069373147084825p0"><a name="entry2069373147084825p0"></a><a name="entry2069373147084825p0"></a><strong id="gga1bee586eafa91dfb60f94ba40fc95faaa3db11a46c7f4bb848e6f0604268e41e3"><a name="gga1bee586eafa91dfb60f94ba40fc95faaa3db11a46c7f4bb848e6f0604268e41e3"></a><a name="gga1bee586eafa91dfb60f94ba40fc95faaa3db11a46c7f4bb848e6f0604268e41e3"></a></strong>MEDIA_MIMETYPE_VIDEO_AVC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036417206084825"><a name="p1036417206084825"></a><a name="p1036417206084825"></a>H.264 video</p>
<p id="p562361416154"><a name="p562361416154"></a><a name="p562361416154"></a></p>
</td>
</tr>
<tr id="row107225279084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry141159181084825p0"><a name="entry141159181084825p0"></a><a name="entry141159181084825p0"></a><strong id="gga1bee586eafa91dfb60f94ba40fc95faaaaf430209c9262e6fcd5cd8f97dafe614"><a name="gga1bee586eafa91dfb60f94ba40fc95faaaaf430209c9262e6fcd5cd8f97dafe614"></a><a name="gga1bee586eafa91dfb60f94ba40fc95faaaaf430209c9262e6fcd5cd8f97dafe614"></a></strong>MEDIA_MIMETYPE_VIDEO_HEVC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p831373645084825"><a name="p831373645084825"></a><a name="p831373645084825"></a>H.265 video</p>
<p id="p16623131431515"><a name="p16623131431515"></a><a name="p16623131431515"></a></p>
</td>
</tr>
<tr id="row1623509828084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1058863544084825p0"><a name="entry1058863544084825p0"></a><a name="entry1058863544084825p0"></a><strong id="gga1bee586eafa91dfb60f94ba40fc95faaac03eb65aaf7aff393e223346feb30415"><a name="gga1bee586eafa91dfb60f94ba40fc95faaac03eb65aaf7aff393e223346feb30415"></a><a name="gga1bee586eafa91dfb60f94ba40fc95faaac03eb65aaf7aff393e223346feb30415"></a></strong>MEDIA_MIMETYPE_AUDIO_AAC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p494699263084825"><a name="p494699263084825"></a><a name="p494699263084825"></a>AAC audio</p>
<p id="p156232140158"><a name="p156232140158"></a><a name="p156232140158"></a></p>
</td>
</tr>
<tr id="row1550791408084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry637348088084825p0"><a name="entry637348088084825p0"></a><a name="entry637348088084825p0"></a><strong id="gga1bee586eafa91dfb60f94ba40fc95faaaa2fa953bd51d8ee18191315c7187fc96"><a name="gga1bee586eafa91dfb60f94ba40fc95faaaa2fa953bd51d8ee18191315c7187fc96"></a><a name="gga1bee586eafa91dfb60f94ba40fc95faaaa2fa953bd51d8ee18191315c7187fc96"></a></strong>MEDIA_MIMETYPE_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1442720542084825"><a name="p1442720542084825"></a><a name="p1442720542084825"></a>Invalid MIME type</p>
<p id="p17623111401519"><a name="p17623111401519"></a><a name="p17623111401519"></a></p>
</td>
</tr>
</tbody>
</table>

## BufferMode<a name="gacc0fd55192fd9f663121b037b06f41e8"></a>

```
enum [BufferMode](codec.md#gacc0fd55192fd9f663121b037b06f41e8)
```

**Description:**

Enumerates allocation types.

<a name="table2026923806084825"></a>
<table><thead align="left"><tr id="row160543977084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1796567435084825"><a name="p1796567435084825"></a><a name="p1796567435084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1258870989084825"><a name="p1258870989084825"></a><a name="p1258870989084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row423333749084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry343470639084825p0"><a name="entry343470639084825p0"></a><a name="entry343470639084825p0"></a><strong id="ggacc0fd55192fd9f663121b037b06f41e8adc7588f17692aa631f375290d50a2c8e"><a name="ggacc0fd55192fd9f663121b037b06f41e8adc7588f17692aa631f375290d50a2c8e"></a><a name="ggacc0fd55192fd9f663121b037b06f41e8adc7588f17692aa631f375290d50a2c8e"></a></strong>INTERNAL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1322642101084825"><a name="p1322642101084825"></a><a name="p1322642101084825"></a>Internal</p>
<p id="p16628514201511"><a name="p16628514201511"></a><a name="p16628514201511"></a></p>
</td>
</tr>
<tr id="row1034237233084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1556406386084825p0"><a name="entry1556406386084825p0"></a><a name="entry1556406386084825p0"></a><strong id="ggacc0fd55192fd9f663121b037b06f41e8a63fbb9fe7b9a695d3a65541465cb99d5"><a name="ggacc0fd55192fd9f663121b037b06f41e8a63fbb9fe7b9a695d3a65541465cb99d5"></a><a name="ggacc0fd55192fd9f663121b037b06f41e8a63fbb9fe7b9a695d3a65541465cb99d5"></a></strong>EXTERNAL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765662723084825"><a name="p765662723084825"></a><a name="p765662723084825"></a>External</p>
<p id="p262931461516"><a name="p262931461516"></a><a name="p262931461516"></a></p>
</td>
</tr>
</tbody>
</table>

## BufferType<a name="gadf8e136713c0691010d2bec6ba63e9cf"></a>

```
enum [BufferType](codec.md#gadf8e136713c0691010d2bec6ba63e9cf)
```

**Description:**

Enumerates buffer types.

<a name="table1907768176084825"></a>
<table><thead align="left"><tr id="row196051890084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p401735413084825"><a name="p401735413084825"></a><a name="p401735413084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p845521738084825"><a name="p845521738084825"></a><a name="p845521738084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1892229509084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1865003813084825p0"><a name="entry1865003813084825p0"></a><a name="entry1865003813084825p0"></a><strong id="ggadf8e136713c0691010d2bec6ba63e9cfabc56eeb37d99d582a14b44fb0ef4cabc"><a name="ggadf8e136713c0691010d2bec6ba63e9cfabc56eeb37d99d582a14b44fb0ef4cabc"></a><a name="ggadf8e136713c0691010d2bec6ba63e9cfabc56eeb37d99d582a14b44fb0ef4cabc"></a></strong>BUFFER_TYPE_VIRTUAL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325889023084825"><a name="p1325889023084825"></a><a name="p1325889023084825"></a>Virtual memory</p>
<p id="p106321614171519"><a name="p106321614171519"></a><a name="p106321614171519"></a></p>
</td>
</tr>
<tr id="row1534603158084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry790892939084825p0"><a name="entry790892939084825p0"></a><a name="entry790892939084825p0"></a><strong id="ggadf8e136713c0691010d2bec6ba63e9cfa4583aeaa2921c629ee785dbee184f421"><a name="ggadf8e136713c0691010d2bec6ba63e9cfa4583aeaa2921c629ee785dbee184f421"></a><a name="ggadf8e136713c0691010d2bec6ba63e9cfa4583aeaa2921c629ee785dbee184f421"></a></strong>BUFFER_TYPE_FD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354113490084825"><a name="p1354113490084825"></a><a name="p1354113490084825"></a>File descriptor, which can be used cross processes</p>
<p id="p5632181461519"><a name="p5632181461519"></a><a name="p5632181461519"></a></p>
</td>
</tr>
<tr id="row1775247341084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry134810548084825p0"><a name="entry134810548084825p0"></a><a name="entry134810548084825p0"></a><strong id="ggadf8e136713c0691010d2bec6ba63e9cfa4bc0e24b5ce589d284b1771fc27c3d09"><a name="ggadf8e136713c0691010d2bec6ba63e9cfa4bc0e24b5ce589d284b1771fc27c3d09"></a><a name="ggadf8e136713c0691010d2bec6ba63e9cfa4bc0e24b5ce589d284b1771fc27c3d09"></a></strong>BUFFER_TYPE_HANDLE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p212667123084825"><a name="p212667123084825"></a><a name="p212667123084825"></a>Handle, which can be used cross processes</p>
<p id="p963241471515"><a name="p963241471515"></a><a name="p963241471515"></a></p>
</td>
</tr>
</tbody>
</table>

## CapsMask<a name="gae5751aa8514dcaf2217df12db5ef57a1"></a>

```
enum [CapsMask](codec.md#gae5751aa8514dcaf2217df12db5ef57a1)
```

**Description:**

Enumerates playback capabilities.

<a name="table1456928373084825"></a>
<table><thead align="left"><tr id="row1341222212084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1830187420084825"><a name="p1830187420084825"></a><a name="p1830187420084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p625393792084825"><a name="p625393792084825"></a><a name="p625393792084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1102820964084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1391082515084825p0"><a name="entry1391082515084825p0"></a><a name="entry1391082515084825p0"></a><strong id="ggae5751aa8514dcaf2217df12db5ef57a1afe6e93325882ea7c27503f79d0b2dcae"><a name="ggae5751aa8514dcaf2217df12db5ef57a1afe6e93325882ea7c27503f79d0b2dcae"></a><a name="ggae5751aa8514dcaf2217df12db5ef57a1afe6e93325882ea7c27503f79d0b2dcae"></a></strong>ADAPTIVE_PLAYBACK</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2127759984084825"><a name="p2127759984084825"></a><a name="p2127759984084825"></a>Adaptive playback</p>
<p id="p196351114141512"><a name="p196351114141512"></a><a name="p196351114141512"></a></p>
</td>
</tr>
<tr id="row471543167084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2055021574084825p0"><a name="entry2055021574084825p0"></a><a name="entry2055021574084825p0"></a><strong id="ggae5751aa8514dcaf2217df12db5ef57a1ad0c1ab7c365efc53a4de146b91f1a10f"><a name="ggae5751aa8514dcaf2217df12db5ef57a1ad0c1ab7c365efc53a4de146b91f1a10f"></a><a name="ggae5751aa8514dcaf2217df12db5ef57a1ad0c1ab7c365efc53a4de146b91f1a10f"></a></strong>SECURE_PLAYBACK</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615313754084825"><a name="p615313754084825"></a><a name="p615313754084825"></a>Secure playback</p>
<p id="p19635131431518"><a name="p19635131431518"></a><a name="p19635131431518"></a></p>
</td>
</tr>
</tbody>
</table>

## CodecType<a name="ga03b4b6ae5fb82af68d46aaea3d3e4d79"></a>

```
enum [CodecType](codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79)
```

**Description:**

Enumerates codec types.

<a name="table9080495084825"></a>
<table><thead align="left"><tr id="row2029202752084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1306955038084825"><a name="p1306955038084825"></a><a name="p1306955038084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p990298539084825"><a name="p990298539084825"></a><a name="p990298539084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1725941759084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1809406230084825p0"><a name="entry1809406230084825p0"></a><a name="entry1809406230084825p0"></a><strong id="gga03b4b6ae5fb82af68d46aaea3d3e4d79a19c3c7765c55583a64e21938e2439261"><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79a19c3c7765c55583a64e21938e2439261"></a><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79a19c3c7765c55583a64e21938e2439261"></a></strong>VIDEO_DECODER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p559301971084825"><a name="p559301971084825"></a><a name="p559301971084825"></a>Video decoding</p>
<p id="p12639314171519"><a name="p12639314171519"></a><a name="p12639314171519"></a></p>
</td>
</tr>
<tr id="row744900828084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1057615070084825p0"><a name="entry1057615070084825p0"></a><a name="entry1057615070084825p0"></a><strong id="gga03b4b6ae5fb82af68d46aaea3d3e4d79ad8044bc5b7d871723be90b5b6a094992"><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79ad8044bc5b7d871723be90b5b6a094992"></a><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79ad8044bc5b7d871723be90b5b6a094992"></a></strong>VIDEO_ENCODER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1230828192084825"><a name="p1230828192084825"></a><a name="p1230828192084825"></a>Video encoding</p>
<p id="p1763914145152"><a name="p1763914145152"></a><a name="p1763914145152"></a></p>
</td>
</tr>
<tr id="row2121829927084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1352641210084825p0"><a name="entry1352641210084825p0"></a><a name="entry1352641210084825p0"></a><strong id="gga03b4b6ae5fb82af68d46aaea3d3e4d79ae4ade329585f6c202847138e3f9cd4a4"><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79ae4ade329585f6c202847138e3f9cd4a4"></a><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79ae4ade329585f6c202847138e3f9cd4a4"></a></strong>AUDIO_DECODER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756803990084825"><a name="p756803990084825"></a><a name="p756803990084825"></a>Audio decoding</p>
<p id="p19639101461511"><a name="p19639101461511"></a><a name="p19639101461511"></a></p>
</td>
</tr>
<tr id="row1376965400084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry540526485084825p0"><a name="entry540526485084825p0"></a><a name="entry540526485084825p0"></a><strong id="gga03b4b6ae5fb82af68d46aaea3d3e4d79a7f7f3d3880168089c1de6d1ebc3dbb54"><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79a7f7f3d3880168089c1de6d1ebc3dbb54"></a><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79a7f7f3d3880168089c1de6d1ebc3dbb54"></a></strong>AUDIO_ENCODER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238598249084825"><a name="p238598249084825"></a><a name="p238598249084825"></a>Audio encoding</p>
<p id="p9639914151512"><a name="p9639914151512"></a><a name="p9639914151512"></a></p>
</td>
</tr>
<tr id="row1217702030084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry61123077084825p0"><a name="entry61123077084825p0"></a><a name="entry61123077084825p0"></a><strong id="gga03b4b6ae5fb82af68d46aaea3d3e4d79a7314b0d0e4638eaaeb8690b8555a6546"><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79a7314b0d0e4638eaaeb8690b8555a6546"></a><a name="gga03b4b6ae5fb82af68d46aaea3d3e4d79a7314b0d0e4638eaaeb8690b8555a6546"></a></strong>INVALID_TYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p677646055084825"><a name="p677646055084825"></a><a name="p677646055084825"></a>Invalid type</p>
<p id="p106395148155"><a name="p106395148155"></a><a name="p106395148155"></a></p>
</td>
</tr>
</tbody>
</table>

## DirectionType<a name="ga8ef30fa9c08e08c8706653571f9f5b81"></a>

```
enum [DirectionType](codec.md#ga8ef30fa9c08e08c8706653571f9f5b81)
```

**Description:**

Enumerates input and output types.

<a name="table1398789652084825"></a>
<table><thead align="left"><tr id="row305724406084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p77554346084825"><a name="p77554346084825"></a><a name="p77554346084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p560150861084825"><a name="p560150861084825"></a><a name="p560150861084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row507643508084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry643038624084825p0"><a name="entry643038624084825p0"></a><a name="entry643038624084825p0"></a><strong id="gga8ef30fa9c08e08c8706653571f9f5b81a833326d0b04dd281eaf006c46842250d"><a name="gga8ef30fa9c08e08c8706653571f9f5b81a833326d0b04dd281eaf006c46842250d"></a><a name="gga8ef30fa9c08e08c8706653571f9f5b81a833326d0b04dd281eaf006c46842250d"></a></strong>INPUT_TYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1377153475084825"><a name="p1377153475084825"></a><a name="p1377153475084825"></a>Input</p>
<p id="p2064441418151"><a name="p2064441418151"></a><a name="p2064441418151"></a></p>
</td>
</tr>
<tr id="row1793535718084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry360911312084825p0"><a name="entry360911312084825p0"></a><a name="entry360911312084825p0"></a><strong id="gga8ef30fa9c08e08c8706653571f9f5b81a9e3da5a3721894f1552c2715c1fbe95c"><a name="gga8ef30fa9c08e08c8706653571f9f5b81a9e3da5a3721894f1552c2715c1fbe95c"></a><a name="gga8ef30fa9c08e08c8706653571f9f5b81a9e3da5a3721894f1552c2715c1fbe95c"></a></strong>OUTPUT_TYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1745966376084825"><a name="p1745966376084825"></a><a name="p1745966376084825"></a>Output</p>
<p id="p186447141151"><a name="p186447141151"></a><a name="p186447141151"></a></p>
</td>
</tr>
<tr id="row56973028084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1631583157084825p0"><a name="entry1631583157084825p0"></a><a name="entry1631583157084825p0"></a><strong id="gga8ef30fa9c08e08c8706653571f9f5b81a46bcae2d9d2268e6a0c9259b9aebfc2f"><a name="gga8ef30fa9c08e08c8706653571f9f5b81a46bcae2d9d2268e6a0c9259b9aebfc2f"></a><a name="gga8ef30fa9c08e08c8706653571f9f5b81a46bcae2d9d2268e6a0c9259b9aebfc2f"></a></strong>ALL_TYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994509106084825"><a name="p994509106084825"></a><a name="p994509106084825"></a>Input and output</p>
<p id="p17644121441519"><a name="p17644121441519"></a><a name="p17644121441519"></a></p>
</td>
</tr>
</tbody>
</table>

## EventType<a name="ga2628ea8d12e8b2563c32f05dc7fff6fa"></a>

```
enum [EventType](codec.md#ga2628ea8d12e8b2563c32f05dc7fff6fa)
```

**Description:**

Enumerates event types.

<a name="table839600434084825"></a>
<table><thead align="left"><tr id="row1248151793084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p182062505084825"><a name="p182062505084825"></a><a name="p182062505084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1397830817084825"><a name="p1397830817084825"></a><a name="p1397830817084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2126629401084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry619650396084825p0"><a name="entry619650396084825p0"></a><a name="entry619650396084825p0"></a><strong id="gga2628ea8d12e8b2563c32f05dc7fff6faa71cf6bf1e591a86cb536668cda0f2a00"><a name="gga2628ea8d12e8b2563c32f05dc7fff6faa71cf6bf1e591a86cb536668cda0f2a00"></a><a name="gga2628ea8d12e8b2563c32f05dc7fff6faa71cf6bf1e591a86cb536668cda0f2a00"></a></strong>EventError</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1578105777084825"><a name="p1578105777084825"></a><a name="p1578105777084825"></a>Event error</p>
<p id="p176481514181516"><a name="p176481514181516"></a><a name="p176481514181516"></a></p>
</td>
</tr>
<tr id="row8874555084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry561306601084825p0"><a name="entry561306601084825p0"></a><a name="entry561306601084825p0"></a><strong id="gga2628ea8d12e8b2563c32f05dc7fff6faaab9f6e22232b045b85118bdda8aac6db"><a name="gga2628ea8d12e8b2563c32f05dc7fff6faaab9f6e22232b045b85118bdda8aac6db"></a><a name="gga2628ea8d12e8b2563c32f05dc7fff6faaab9f6e22232b045b85118bdda8aac6db"></a></strong>EventFlushCompelte</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p474771922084825"><a name="p474771922084825"></a><a name="p474771922084825"></a>Buffer flush completed</p>
<p id="p4648101410151"><a name="p4648101410151"></a><a name="p4648101410151"></a></p>
</td>
</tr>
<tr id="row661178453084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1490415499084825p0"><a name="entry1490415499084825p0"></a><a name="entry1490415499084825p0"></a><strong id="gga2628ea8d12e8b2563c32f05dc7fff6faa864f301176ff05ad003bc6e89eb2cb93"><a name="gga2628ea8d12e8b2563c32f05dc7fff6faa864f301176ff05ad003bc6e89eb2cb93"></a><a name="gga2628ea8d12e8b2563c32f05dc7fff6faa864f301176ff05ad003bc6e89eb2cb93"></a></strong>EventStopCompelte</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938478273084825"><a name="p938478273084825"></a><a name="p938478273084825"></a>Codec stopped</p>
<p id="p1264841417159"><a name="p1264841417159"></a><a name="p1264841417159"></a></p>
</td>
</tr>
<tr id="row1203753734084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1882095410084825p0"><a name="entry1882095410084825p0"></a><a name="entry1882095410084825p0"></a><strong id="gga2628ea8d12e8b2563c32f05dc7fff6faaeb0fb0bb31b20a141d015d9a92c629ac"><a name="gga2628ea8d12e8b2563c32f05dc7fff6faaeb0fb0bb31b20a141d015d9a92c629ac"></a><a name="gga2628ea8d12e8b2563c32f05dc7fff6faaeb0fb0bb31b20a141d015d9a92c629ac"></a></strong>EventOutFormatChanged</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149324602084825"><a name="p149324602084825"></a><a name="p149324602084825"></a>Output format changed</p>
<p id="p06484141154"><a name="p06484141154"></a><a name="p06484141154"></a></p>
</td>
</tr>
<tr id="row2133321335084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1139037690084825p0"><a name="entry1139037690084825p0"></a><a name="entry1139037690084825p0"></a><strong id="gga2628ea8d12e8b2563c32f05dc7fff6faa70203255ab263a903886b8f774d5c4aa"><a name="gga2628ea8d12e8b2563c32f05dc7fff6faa70203255ab263a903886b8f774d5c4aa"></a><a name="gga2628ea8d12e8b2563c32f05dc7fff6faa70203255ab263a903886b8f774d5c4aa"></a></strong>EventMax</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1397345572084825"><a name="p1397345572084825"></a><a name="p1397345572084825"></a>Maximum event value</p>
<p id="p8648201414155"><a name="p8648201414155"></a><a name="p8648201414155"></a></p>
</td>
</tr>
</tbody>
</table>

## Level<a name="ga221b779e6bb7b8d40677d7642bfefac5"></a>

```
enum [Level](codec.md#ga221b779e6bb7b8d40677d7642bfefac5)
```

**Description:**

Enumerates codec levels.

<a name="table1961497877084825"></a>
<table><thead align="left"><tr id="row587311648084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1155074175084825"><a name="p1155074175084825"></a><a name="p1155074175084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1814215367084825"><a name="p1814215367084825"></a><a name="p1814215367084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row963651770084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1090345425084825p0"><a name="entry1090345425084825p0"></a><a name="entry1090345425084825p0"></a><strong id="gga221b779e6bb7b8d40677d7642bfefac5a6ab1f388a1a94d680bcbe808ec45a082"><a name="gga221b779e6bb7b8d40677d7642bfefac5a6ab1f388a1a94d680bcbe808ec45a082"></a><a name="gga221b779e6bb7b8d40677d7642bfefac5a6ab1f388a1a94d680bcbe808ec45a082"></a></strong>INVALID_LEVEL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477452862084825"><a name="p1477452862084825"></a><a name="p1477452862084825"></a>Invalid level</p>
<p id="p665310142153"><a name="p665310142153"></a><a name="p665310142153"></a></p>
</td>
</tr>
<tr id="row28328394084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1482208278084825p0"><a name="entry1482208278084825p0"></a><a name="entry1482208278084825p0"></a><strong id="gga221b779e6bb7b8d40677d7642bfefac5aee353b803bd93ba9e01e99e67b8afb49"><a name="gga221b779e6bb7b8d40677d7642bfefac5aee353b803bd93ba9e01e99e67b8afb49"></a><a name="gga221b779e6bb7b8d40677d7642bfefac5aee353b803bd93ba9e01e99e67b8afb49"></a></strong>AVC_LEVEL_1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086602524084825"><a name="p1086602524084825"></a><a name="p1086602524084825"></a>H.264 level 1</p>
<p id="p065371471514"><a name="p065371471514"></a><a name="p065371471514"></a></p>
</td>
</tr>
<tr id="row1148325668084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry633333355084825p0"><a name="entry633333355084825p0"></a><a name="entry633333355084825p0"></a><strong id="gga221b779e6bb7b8d40677d7642bfefac5a25819fec0bd7476c85122100b61536bb"><a name="gga221b779e6bb7b8d40677d7642bfefac5a25819fec0bd7476c85122100b61536bb"></a><a name="gga221b779e6bb7b8d40677d7642bfefac5a25819fec0bd7476c85122100b61536bb"></a></strong>HEVC_LEVEL_MAIN_1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p921390325084825"><a name="p921390325084825"></a><a name="p921390325084825"></a>H.265 Main level 1</p>
<p id="p8653514101514"><a name="p8653514101514"></a><a name="p8653514101514"></a></p>
</td>
</tr>
<tr id="row1004248135084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1471931181084825p0"><a name="entry1471931181084825p0"></a><a name="entry1471931181084825p0"></a><strong id="gga221b779e6bb7b8d40677d7642bfefac5ab21d7836b0849b87149b7cdd7924d862"><a name="gga221b779e6bb7b8d40677d7642bfefac5ab21d7836b0849b87149b7cdd7924d862"></a><a name="gga221b779e6bb7b8d40677d7642bfefac5ab21d7836b0849b87149b7cdd7924d862"></a></strong>HEVC_LEVEL_MAIN_2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2070423968084825"><a name="p2070423968084825"></a><a name="p2070423968084825"></a>H.265 Main level 2</p>
<p id="p66531148152"><a name="p66531148152"></a><a name="p66531148152"></a></p>
</td>
</tr>
</tbody>
</table>

## ParamKey<a name="ga575c56a2d6b42c48881cf47b0008d5a6"></a>

```
enum [ParamKey](codec.md#ga575c56a2d6b42c48881cf47b0008d5a6)
```

**Description:**

Enumerates indexes of parameter types.

<a name="table473127661084825"></a>
<table><thead align="left"><tr id="row702837612084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p908075634084825"><a name="p908075634084825"></a><a name="p908075634084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p313903828084825"><a name="p313903828084825"></a><a name="p313903828084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row77534017084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry952146540084825p0"><a name="entry952146540084825p0"></a><a name="entry952146540084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6aef2a08e0112230b41df402fd38efc1ed"><a name="gga575c56a2d6b42c48881cf47b0008d5a6aef2a08e0112230b41df402fd38efc1ed"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6aef2a08e0112230b41df402fd38efc1ed"></a></strong>KEY_MIMETYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929470092084825"><a name="p929470092084825"></a><a name="p929470092084825"></a>MIME type. For the value type, see <a href="codec.md#ga1bee586eafa91dfb60f94ba40fc95faa">AvCodecMime</a>.</p>
<p id="p136571214191511"><a name="p136571214191511"></a><a name="p136571214191511"></a></p>
</td>
</tr>
<tr id="row1416693388084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2096793018084825p0"><a name="entry2096793018084825p0"></a><a name="entry2096793018084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a2c86d69eb4995dbadfdb6d289834f7f2"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a2c86d69eb4995dbadfdb6d289834f7f2"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a2c86d69eb4995dbadfdb6d289834f7f2"></a></strong>KEY_BUFFERSIZE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094183091084825"><a name="p2094183091084825"></a><a name="p2094183091084825"></a>Buffer size. The value type is uint32_t.</p>
<p id="p15657614131517"><a name="p15657614131517"></a><a name="p15657614131517"></a></p>
</td>
</tr>
<tr id="row1912557773084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry416359275084825p0"><a name="entry416359275084825p0"></a><a name="entry416359275084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a4c97de4e44d3c9778530ddd2cffe1728"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a4c97de4e44d3c9778530ddd2cffe1728"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a4c97de4e44d3c9778530ddd2cffe1728"></a></strong>KEY_LEFT_STREAM_FRAMES</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143954037084825"><a name="p1143954037084825"></a><a name="p1143954037084825"></a>Number of frames in the remaining data streams. The value type is uint32_t.</p>
<p id="p16657314131510"><a name="p16657314131510"></a><a name="p16657314131510"></a></p>
</td>
</tr>
<tr id="row1997795411084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1230102582084825p0"><a name="entry1230102582084825p0"></a><a name="entry1230102582084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ac3e2aece8c07c078567996464d654e5a"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ac3e2aece8c07c078567996464d654e5a"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ac3e2aece8c07c078567996464d654e5a"></a></strong>KEY_CODEC_TYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403232358084825"><a name="p403232358084825"></a><a name="p403232358084825"></a>Codec type. For the value type, see <a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a>.</p>
<p id="p76571714111519"><a name="p76571714111519"></a><a name="p76571714111519"></a></p>
</td>
</tr>
<tr id="row730750455084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry339163655084825p0"><a name="entry339163655084825p0"></a><a name="entry339163655084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ac1ff343954a9a979fd49bf6ef80d2589"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ac1ff343954a9a979fd49bf6ef80d2589"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ac1ff343954a9a979fd49bf6ef80d2589"></a></strong>KEY_DIRECTION_TYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1241452043084825"><a name="p1241452043084825"></a><a name="p1241452043084825"></a>Input/Output type. For the value type, see <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a>.</p>
<p id="p165741481514"><a name="p165741481514"></a><a name="p165741481514"></a></p>
</td>
</tr>
<tr id="row776103087084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry364663858084825p0"><a name="entry364663858084825p0"></a><a name="entry364663858084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ad8c37ded7037d0e1eeb6e477ff72492f"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ad8c37ded7037d0e1eeb6e477ff72492f"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ad8c37ded7037d0e1eeb6e477ff72492f"></a></strong>KEY_BITRATE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1906475392084825"><a name="p1906475392084825"></a><a name="p1906475392084825"></a>Bit rate. The value type is uint32_t.</p>
<p id="p36572148150"><a name="p36572148150"></a><a name="p36572148150"></a></p>
</td>
</tr>
<tr id="row332410525084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1989874662084825p0"><a name="entry1989874662084825p0"></a><a name="entry1989874662084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6adab65ac6751535b13f6275dbfa1ba90e"><a name="gga575c56a2d6b42c48881cf47b0008d5a6adab65ac6751535b13f6275dbfa1ba90e"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6adab65ac6751535b13f6275dbfa1ba90e"></a></strong>KEY_WIDTH</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060714560084825"><a name="p1060714560084825"></a><a name="p1060714560084825"></a>Width. The value type is uint32_t.</p>
<p id="p46571414141511"><a name="p46571414141511"></a><a name="p46571414141511"></a></p>
</td>
</tr>
<tr id="row1207276542084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry838359160084825p0"><a name="entry838359160084825p0"></a><a name="entry838359160084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a78fd0c2ba5fb7894ec4a164ff2b119b8"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a78fd0c2ba5fb7894ec4a164ff2b119b8"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a78fd0c2ba5fb7894ec4a164ff2b119b8"></a></strong>KEY_HEIGHT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246706388084825"><a name="p246706388084825"></a><a name="p246706388084825"></a>Hight. The value type is uint32_t.</p>
<p id="p1365810145159"><a name="p1365810145159"></a><a name="p1365810145159"></a></p>
</td>
</tr>
<tr id="row1346325681084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2107679922084825p0"><a name="entry2107679922084825p0"></a><a name="entry2107679922084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ad25b08a51da92cb8928402bd2a99ec60"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ad25b08a51da92cb8928402bd2a99ec60"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ad25b08a51da92cb8928402bd2a99ec60"></a></strong>KEY_STRIDE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224463649084825"><a name="p224463649084825"></a><a name="p224463649084825"></a>Stride. The value type is uint32_t.</p>
<p id="p12658141411517"><a name="p12658141411517"></a><a name="p12658141411517"></a></p>
</td>
</tr>
<tr id="row1269600197084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1318170002084825p0"><a name="entry1318170002084825p0"></a><a name="entry1318170002084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ae45fd20d699c2a40110d510c26e2b0bb"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ae45fd20d699c2a40110d510c26e2b0bb"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ae45fd20d699c2a40110d510c26e2b0bb"></a></strong>KEY_VIDEO_FIELD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1839736691084825"><a name="p1839736691084825"></a><a name="p1839736691084825"></a>Video field. For the value type, see <a href="codec.md#ga1420ddfb066b941fb55a153b869d9ccf">VideoField</a>.</p>
<p id="p1165813145156"><a name="p1165813145156"></a><a name="p1165813145156"></a></p>
</td>
</tr>
<tr id="row1723100650084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1301578964084825p0"><a name="entry1301578964084825p0"></a><a name="entry1301578964084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a8b4fdf85f17f5bb549236a6280e36328"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a8b4fdf85f17f5bb549236a6280e36328"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a8b4fdf85f17f5bb549236a6280e36328"></a></strong>KEY_PIXEL_FORMAT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p556282266084825"><a name="p556282266084825"></a><a name="p556282266084825"></a>Pixel format. For the value type, see <a href="display.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a>.</p>
<p id="p3658201416152"><a name="p3658201416152"></a><a name="p3658201416152"></a></p>
</td>
</tr>
<tr id="row1555374851084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1441824276084825p0"><a name="entry1441824276084825p0"></a><a name="entry1441824276084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6abed5c9737ae85a1771f6d065692fdab1"><a name="gga575c56a2d6b42c48881cf47b0008d5a6abed5c9737ae85a1771f6d065692fdab1"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6abed5c9737ae85a1771f6d065692fdab1"></a></strong>KEY_VIDEO_RC_MODE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967027927084825"><a name="p967027927084825"></a><a name="p967027927084825"></a>Rate control mode. For the value type, see <a href="codec.md#ga94267d7ba495136561e1c65686b240f7">VenCodeRcMode</a>.</p>
<p id="p1465861481515"><a name="p1465861481515"></a><a name="p1465861481515"></a></p>
</td>
</tr>
<tr id="row985649317084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1007816148084825p0"><a name="entry1007816148084825p0"></a><a name="entry1007816148084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6aae6cd2e1f70f313300e8579d2c6befbc"><a name="gga575c56a2d6b42c48881cf47b0008d5a6aae6cd2e1f70f313300e8579d2c6befbc"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6aae6cd2e1f70f313300e8579d2c6befbc"></a></strong>KEY_VIDEO_GOP_MODE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p730341524084825"><a name="p730341524084825"></a><a name="p730341524084825"></a>GOP mode. For the value type, see <a href="codec.md#ga9532f651a003219a262c440f5621d129">VenCodeGopMode</a>.</p>
<p id="p10658131441510"><a name="p10658131441510"></a><a name="p10658131441510"></a></p>
</td>
</tr>
<tr id="row1755791142084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry212145098084825p0"><a name="entry212145098084825p0"></a><a name="entry212145098084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a19a23598acca8b0d1dfa8bb48f58a7ef"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a19a23598acca8b0d1dfa8bb48f58a7ef"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a19a23598acca8b0d1dfa8bb48f58a7ef"></a></strong>KEY_VIDEO_PIC_SIZE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p945758899084825"><a name="p945758899084825"></a><a name="p945758899084825"></a>Image resolution. For the value type, see <a href="codec.md#ga94981b885085085ed5f9dea406519b48">PicSize</a>.</p>
<p id="p665881471518"><a name="p665881471518"></a><a name="p665881471518"></a></p>
</td>
</tr>
<tr id="row2079755077084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2063050832084825p0"><a name="entry2063050832084825p0"></a><a name="entry2063050832084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ab05b2fdf7c66accbce8bd4c5689dbe31"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ab05b2fdf7c66accbce8bd4c5689dbe31"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ab05b2fdf7c66accbce8bd4c5689dbe31"></a></strong>KEY_VIDEO_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1986167883084825"><a name="p1986167883084825"></a><a name="p1986167883084825"></a>Codec profile. The value type is uint32_t.</p>
<p id="p116581914161518"><a name="p116581914161518"></a><a name="p116581914161518"></a></p>
</td>
</tr>
<tr id="row1879750511084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry313013753084825p0"><a name="entry313013753084825p0"></a><a name="entry313013753084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6acdfdfbe59769faa9eb22c7fabf99ab77"><a name="gga575c56a2d6b42c48881cf47b0008d5a6acdfdfbe59769faa9eb22c7fabf99ab77"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6acdfdfbe59769faa9eb22c7fabf99ab77"></a></strong>KEY_VIDEO_FRAME_RATE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1682444034084825"><a name="p1682444034084825"></a><a name="p1682444034084825"></a>Frame rate. The value type is uint32_t.</p>
<p id="p1965831491519"><a name="p1965831491519"></a><a name="p1965831491519"></a></p>
</td>
</tr>
<tr id="row1067419154084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry453754620084825p0"><a name="entry453754620084825p0"></a><a name="entry453754620084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a513f3e7cbf10667949bd2f276b43227e"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a513f3e7cbf10667949bd2f276b43227e"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a513f3e7cbf10667949bd2f276b43227e"></a></strong>KEY_SAMPLE_RATE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2052799074084825"><a name="p2052799074084825"></a><a name="p2052799074084825"></a>Sampling rate. The value type is uint32_t.</p>
<p id="p1665801416152"><a name="p1665801416152"></a><a name="p1665801416152"></a></p>
</td>
</tr>
<tr id="row1046750259084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry491749815084825p0"><a name="entry491749815084825p0"></a><a name="entry491749815084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a1a00600fff0e7a378bc0c690451f1040"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a1a00600fff0e7a378bc0c690451f1040"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a1a00600fff0e7a378bc0c690451f1040"></a></strong>KEY_AUDIO_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1079059590084825"><a name="p1079059590084825"></a><a name="p1079059590084825"></a>Audio encoding profile. The value type is uint32_t.</p>
<p id="p3658131441520"><a name="p3658131441520"></a><a name="p3658131441520"></a></p>
</td>
</tr>
<tr id="row690886644084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1611817795084825p0"><a name="entry1611817795084825p0"></a><a name="entry1611817795084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a8c791931da4303642db329af0bb383a8"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a8c791931da4303642db329af0bb383a8"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a8c791931da4303642db329af0bb383a8"></a></strong>KEY_CHANNEL_COUNT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932839278084825"><a name="p1932839278084825"></a><a name="p1932839278084825"></a>Number of channels. The value type is uint32_t.</p>
<p id="p1665831411518"><a name="p1665831411518"></a><a name="p1665831411518"></a></p>
</td>
</tr>
<tr id="row1798772045084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1042145020084825p0"><a name="entry1042145020084825p0"></a><a name="entry1042145020084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ae054dfca35dd75e795aa9af83390a4fd"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ae054dfca35dd75e795aa9af83390a4fd"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ae054dfca35dd75e795aa9af83390a4fd"></a></strong>KEY_BITWITH</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45389622084825"><a name="p45389622084825"></a><a name="p45389622084825"></a>Bit width. For the value type, see <a href="en-us_topic_0000001055678046.md#gae3e35ee2a2222a667fdebbc5b793ca7c">AudioBitWidth</a>.</p>
<p id="p7658914151515"><a name="p7658914151515"></a><a name="p7658914151515"></a></p>
</td>
</tr>
<tr id="row445647522084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry606660199084825p0"><a name="entry606660199084825p0"></a><a name="entry606660199084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ade681ad9e4e270d52ed2127dc86a90c7"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ade681ad9e4e270d52ed2127dc86a90c7"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ade681ad9e4e270d52ed2127dc86a90c7"></a></strong>KEY_SOUND_MODE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846204776084825"><a name="p846204776084825"></a><a name="p846204776084825"></a>Audio channel mode. For the value type, see <a href="codec.md#gacecb40e35c431a27385f7b439fc7a76c">AudioSoundMode</a>.</p>
<p id="p11658161481515"><a name="p11658161481515"></a><a name="p11658161481515"></a></p>
</td>
</tr>
<tr id="row1249527516084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry351174094084825p0"><a name="entry351174094084825p0"></a><a name="entry351174094084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6ab6ca06e65b7ee9808e07389507555b48"><a name="gga575c56a2d6b42c48881cf47b0008d5a6ab6ca06e65b7ee9808e07389507555b48"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6ab6ca06e65b7ee9808e07389507555b48"></a></strong>KEY_POINT_NUM_PER_FRAME</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106710096084825"><a name="p1106710096084825"></a><a name="p1106710096084825"></a>Number of sampling points per frame. The value type is uint32_t.</p>
<p id="p7658151418151"><a name="p7658151418151"></a><a name="p7658151418151"></a></p>
</td>
</tr>
<tr id="row436668101084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1677397595084825p0"><a name="entry1677397595084825p0"></a><a name="entry1677397595084825p0"></a><strong id="gga575c56a2d6b42c48881cf47b0008d5a6a15bf33195ec3c6067084aa3fa047cad2"><a name="gga575c56a2d6b42c48881cf47b0008d5a6a15bf33195ec3c6067084aa3fa047cad2"></a><a name="gga575c56a2d6b42c48881cf47b0008d5a6a15bf33195ec3c6067084aa3fa047cad2"></a></strong>KEY_DEVICE_ID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884445655084825"><a name="p884445655084825"></a><a name="p884445655084825"></a>Device ID. The value type is uint32_t.</p>
<p id="p156581414111517"><a name="p156581414111517"></a><a name="p156581414111517"></a></p>
</td>
</tr>
</tbody>
</table>

## PicSize<a name="ga94981b885085085ed5f9dea406519b48"></a>

```
enum [PicSize](codec.md#ga94981b885085085ed5f9dea406519b48)
```

**Description:**

Enumerates resolutions.

<a name="table1803223268084825"></a>
<table><thead align="left"><tr id="row789393717084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p180068791084825"><a name="p180068791084825"></a><a name="p180068791084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1348850702084825"><a name="p1348850702084825"></a><a name="p1348850702084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1363185441084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry796648611084825p0"><a name="entry796648611084825p0"></a><a name="entry796648611084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48a373065e30654b1d097cb9725bec88962"><a name="gga94981b885085085ed5f9dea406519b48a373065e30654b1d097cb9725bec88962"></a><a name="gga94981b885085085ed5f9dea406519b48a373065e30654b1d097cb9725bec88962"></a></strong>Resolution_CIF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207762699084825"><a name="p1207762699084825"></a><a name="p1207762699084825"></a>352x288</p>
<p id="p96761142156"><a name="p96761142156"></a><a name="p96761142156"></a></p>
</td>
</tr>
<tr id="row1335254019084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1873999453084825p0"><a name="entry1873999453084825p0"></a><a name="entry1873999453084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48af6b390500e92b07d1c8829c7ce13fc9b"><a name="gga94981b885085085ed5f9dea406519b48af6b390500e92b07d1c8829c7ce13fc9b"></a><a name="gga94981b885085085ed5f9dea406519b48af6b390500e92b07d1c8829c7ce13fc9b"></a></strong>Resolution_360P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1886331385084825"><a name="p1886331385084825"></a><a name="p1886331385084825"></a>640x360</p>
<p id="p1267691491516"><a name="p1267691491516"></a><a name="p1267691491516"></a></p>
</td>
</tr>
<tr id="row928000829084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1043965127084825p0"><a name="entry1043965127084825p0"></a><a name="entry1043965127084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48a7662d5257ffca575be7f343015f3e6ab"><a name="gga94981b885085085ed5f9dea406519b48a7662d5257ffca575be7f343015f3e6ab"></a><a name="gga94981b885085085ed5f9dea406519b48a7662d5257ffca575be7f343015f3e6ab"></a></strong>Resolution_D1_PAL</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p826875470084825"><a name="p826875470084825"></a><a name="p826875470084825"></a>720x576</p>
<p id="p9676914191513"><a name="p9676914191513"></a><a name="p9676914191513"></a></p>
</td>
</tr>
<tr id="row1322892814084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry924545781084825p0"><a name="entry924545781084825p0"></a><a name="entry924545781084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48ae2644966a8e6b6595f90bc950fa9673d"><a name="gga94981b885085085ed5f9dea406519b48ae2644966a8e6b6595f90bc950fa9673d"></a><a name="gga94981b885085085ed5f9dea406519b48ae2644966a8e6b6595f90bc950fa9673d"></a></strong>Resolution_D1_NTSC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400716199084825"><a name="p1400716199084825"></a><a name="p1400716199084825"></a>720x480</p>
<p id="p7676151411151"><a name="p7676151411151"></a><a name="p7676151411151"></a></p>
</td>
</tr>
<tr id="row971840648084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry58173457084825p0"><a name="entry58173457084825p0"></a><a name="entry58173457084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48ae6d83a5bdf1b754df6dc23b07d781a5e"><a name="gga94981b885085085ed5f9dea406519b48ae6d83a5bdf1b754df6dc23b07d781a5e"></a><a name="gga94981b885085085ed5f9dea406519b48ae6d83a5bdf1b754df6dc23b07d781a5e"></a></strong>Resolution_720P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555800201084825"><a name="p1555800201084825"></a><a name="p1555800201084825"></a>1280x720</p>
<p id="p17676171491515"><a name="p17676171491515"></a><a name="p17676171491515"></a></p>
</td>
</tr>
<tr id="row694366365084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry677212880084825p0"><a name="entry677212880084825p0"></a><a name="entry677212880084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48a460ffc02a1f90e6194fca5f1fcfb513b"><a name="gga94981b885085085ed5f9dea406519b48a460ffc02a1f90e6194fca5f1fcfb513b"></a><a name="gga94981b885085085ed5f9dea406519b48a460ffc02a1f90e6194fca5f1fcfb513b"></a></strong>Resolution_1080P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1480007997084825"><a name="p1480007997084825"></a><a name="p1480007997084825"></a>1920x1080</p>
<p id="p1867611431515"><a name="p1867611431515"></a><a name="p1867611431515"></a></p>
</td>
</tr>
<tr id="row748705646084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1308603662084825p0"><a name="entry1308603662084825p0"></a><a name="entry1308603662084825p0"></a><strong id="gga94981b885085085ed5f9dea406519b48ae26dfcd8b806ea2ec7236f5a43dba1a2"><a name="gga94981b885085085ed5f9dea406519b48ae26dfcd8b806ea2ec7236f5a43dba1a2"></a><a name="gga94981b885085085ed5f9dea406519b48ae26dfcd8b806ea2ec7236f5a43dba1a2"></a></strong>Resolution_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075639905084825"><a name="p2075639905084825"></a><a name="p2075639905084825"></a>Invalid resolution</p>
<p id="p867691416151"><a name="p867691416151"></a><a name="p867691416151"></a></p>
</td>
</tr>
</tbody>
</table>

## PixelFormat<a name="ga60883d4958a60b91661e97027a85072a"></a>

```
enum [PixelFormat](codec.md#ga60883d4958a60b91661e97027a85072a)
```

**Description:**

Enumerates pixel formats.

<a name="table1871265349084825"></a>
<table><thead align="left"><tr id="row1630301875084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1565976665084825"><a name="p1565976665084825"></a><a name="p1565976665084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1018632345084825"><a name="p1018632345084825"></a><a name="p1018632345084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row153720661084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry232666425084825p0"><a name="entry232666425084825p0"></a><a name="entry232666425084825p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa442172344e87ea7d96a7675112f2a544"><a name="gga60883d4958a60b91661e97027a85072aa442172344e87ea7d96a7675112f2a544"></a><a name="gga60883d4958a60b91661e97027a85072aa442172344e87ea7d96a7675112f2a544"></a></strong>YVU_SEMIPLANAR_420</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330047745084825"><a name="p330047745084825"></a><a name="p330047745084825"></a>YUV 420 SP</p>
<p id="p7682201481519"><a name="p7682201481519"></a><a name="p7682201481519"></a></p>
</td>
</tr>
<tr id="row1827953718084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry513985664084825p0"><a name="entry513985664084825p0"></a><a name="entry513985664084825p0"></a><strong id="gga60883d4958a60b91661e97027a85072aac31c324ea9de2f481f8836586ed270b4"><a name="gga60883d4958a60b91661e97027a85072aac31c324ea9de2f481f8836586ed270b4"></a><a name="gga60883d4958a60b91661e97027a85072aac31c324ea9de2f481f8836586ed270b4"></a></strong>YVU_SEMIPLANAR_420_TILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654985612084825"><a name="p654985612084825"></a><a name="p654985612084825"></a>YUV SP 420 TILE</p>
<p id="p8682714111519"><a name="p8682714111519"></a><a name="p8682714111519"></a></p>
</td>
</tr>
<tr id="row104060850084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1929427153084825p0"><a name="entry1929427153084825p0"></a><a name="entry1929427153084825p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa2518a2ff4cd9bda80aab9ddbc7477a32"><a name="gga60883d4958a60b91661e97027a85072aa2518a2ff4cd9bda80aab9ddbc7477a32"></a><a name="gga60883d4958a60b91661e97027a85072aa2518a2ff4cd9bda80aab9ddbc7477a32"></a></strong>PIX_FORMAT_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1745773964084825"><a name="p1745773964084825"></a><a name="p1745773964084825"></a>Invalid format</p>
<p id="p868221415158"><a name="p868221415158"></a><a name="p868221415158"></a></p>
</td>
</tr>
</tbody>
</table>

## Profile<a name="ga85b10143618f300ff4f5bc6d45c72c01"></a>

```
enum [Profile](codec.md#ga85b10143618f300ff4f5bc6d45c72c01)
```

**Description:**

Enumerates codec profiles.

<a name="table1506234432084825"></a>
<table><thead align="left"><tr id="row841115264084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1562719941084825"><a name="p1562719941084825"></a><a name="p1562719941084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p475885741084825"><a name="p475885741084825"></a><a name="p475885741084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1912633448084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry87013021084825p0"><a name="entry87013021084825p0"></a><a name="entry87013021084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01a6d67944b4958ad33b0eeb851bbcd169f"><a name="gga85b10143618f300ff4f5bc6d45c72c01a6d67944b4958ad33b0eeb851bbcd169f"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01a6d67944b4958ad33b0eeb851bbcd169f"></a></strong>INVALID_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1785621774084825"><a name="p1785621774084825"></a><a name="p1785621774084825"></a>Invalid profile</p>
<p id="p187135143156"><a name="p187135143156"></a><a name="p187135143156"></a></p>
</td>
</tr>
<tr id="row1566695844084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1149165851084825p0"><a name="entry1149165851084825p0"></a><a name="entry1149165851084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01ad91765d6dcad7253a924d3cb30501e44"><a name="gga85b10143618f300ff4f5bc6d45c72c01ad91765d6dcad7253a924d3cb30501e44"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01ad91765d6dcad7253a924d3cb30501e44"></a></strong>AAC_LC_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712060208084825"><a name="p1712060208084825"></a><a name="p1712060208084825"></a>AAC-Low Complex</p>
<p id="p15714714141518"><a name="p15714714141518"></a><a name="p15714714141518"></a></p>
</td>
</tr>
<tr id="row558249121084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry416150990084825p0"><a name="entry416150990084825p0"></a><a name="entry416150990084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01aada4d857818cd9aa1ad62cdf608dab6b"><a name="gga85b10143618f300ff4f5bc6d45c72c01aada4d857818cd9aa1ad62cdf608dab6b"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01aada4d857818cd9aa1ad62cdf608dab6b"></a></strong>AAC_MAIN_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216050423084825"><a name="p216050423084825"></a><a name="p216050423084825"></a>AAC-Main</p>
<p id="p127143146159"><a name="p127143146159"></a><a name="p127143146159"></a></p>
</td>
</tr>
<tr id="row1766072742084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1627036011084825p0"><a name="entry1627036011084825p0"></a><a name="entry1627036011084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01ab4255dc0e7450af4f526b85acbabfd3e"><a name="gga85b10143618f300ff4f5bc6d45c72c01ab4255dc0e7450af4f526b85acbabfd3e"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01ab4255dc0e7450af4f526b85acbabfd3e"></a></strong>AAC_HE_V1_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73555380084825"><a name="p73555380084825"></a><a name="p73555380084825"></a>HEAAC, AAC+, or AACPlusV1</p>
<p id="p17141414181517"><a name="p17141414181517"></a><a name="p17141414181517"></a></p>
</td>
</tr>
<tr id="row1408758612084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1173265251084825p0"><a name="entry1173265251084825p0"></a><a name="entry1173265251084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01a9b54f7a8c45ea6d4804133d8de4b8dd8"><a name="gga85b10143618f300ff4f5bc6d45c72c01a9b54f7a8c45ea6d4804133d8de4b8dd8"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01a9b54f7a8c45ea6d4804133d8de4b8dd8"></a></strong>AAC_HE_V2_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p841003294084825"><a name="p841003294084825"></a><a name="p841003294084825"></a>AAC++ or AACPlusV2</p>
<p id="p77145145156"><a name="p77145145156"></a><a name="p77145145156"></a></p>
</td>
</tr>
<tr id="row1328120831084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2025222981084825p0"><a name="entry2025222981084825p0"></a><a name="entry2025222981084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01afaaacd4f6bdadac28b5cf49ae8f8470a"><a name="gga85b10143618f300ff4f5bc6d45c72c01afaaacd4f6bdadac28b5cf49ae8f8470a"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01afaaacd4f6bdadac28b5cf49ae8f8470a"></a></strong>AAC_LD_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973385090084825"><a name="p1973385090084825"></a><a name="p1973385090084825"></a>AAC-Low Delay</p>
<p id="p107141014131513"><a name="p107141014131513"></a><a name="p107141014131513"></a></p>
</td>
</tr>
<tr id="row1602633189084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1361797872084825p0"><a name="entry1361797872084825p0"></a><a name="entry1361797872084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01a7c8028283d1ff60e486b3305bf8c1adc"><a name="gga85b10143618f300ff4f5bc6d45c72c01a7c8028283d1ff60e486b3305bf8c1adc"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01a7c8028283d1ff60e486b3305bf8c1adc"></a></strong>AAC_ELD_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847349408084825"><a name="p1847349408084825"></a><a name="p1847349408084825"></a>AAC-Enhanced Low Delay</p>
<p id="p2714101481510"><a name="p2714101481510"></a><a name="p2714101481510"></a></p>
</td>
</tr>
<tr id="row1751454031084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1693500851084825p0"><a name="entry1693500851084825p0"></a><a name="entry1693500851084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01a5bab002f00d3d7281aedc4807123a47a"><a name="gga85b10143618f300ff4f5bc6d45c72c01a5bab002f00d3d7281aedc4807123a47a"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01a5bab002f00d3d7281aedc4807123a47a"></a></strong>AVC_BASELINE_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106832309084825"><a name="p106832309084825"></a><a name="p106832309084825"></a>H.264 Baseline</p>
<p id="p167143148152"><a name="p167143148152"></a><a name="p167143148152"></a></p>
</td>
</tr>
<tr id="row25128528084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1985717315084825p0"><a name="entry1985717315084825p0"></a><a name="entry1985717315084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01a323c1d6e02363f1717f7e6b33fd9a646"><a name="gga85b10143618f300ff4f5bc6d45c72c01a323c1d6e02363f1717f7e6b33fd9a646"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01a323c1d6e02363f1717f7e6b33fd9a646"></a></strong>AVC_MAIN_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1948555260084825"><a name="p1948555260084825"></a><a name="p1948555260084825"></a>H.264 Main</p>
<p id="p6714171418151"><a name="p6714171418151"></a><a name="p6714171418151"></a></p>
</td>
</tr>
<tr id="row261437265084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1608436264084825p0"><a name="entry1608436264084825p0"></a><a name="entry1608436264084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01ab9406e6bf30a0c128c3639cce51fe246"><a name="gga85b10143618f300ff4f5bc6d45c72c01ab9406e6bf30a0c128c3639cce51fe246"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01ab9406e6bf30a0c128c3639cce51fe246"></a></strong>AVC_HIGH_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238892645084825"><a name="p238892645084825"></a><a name="p238892645084825"></a>H.264 High</p>
<p id="p27142014151517"><a name="p27142014151517"></a><a name="p27142014151517"></a></p>
</td>
</tr>
<tr id="row961606021084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1589208788084825p0"><a name="entry1589208788084825p0"></a><a name="entry1589208788084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01ae0d37dc2c7d39753a80f6e0ba64e5e22"><a name="gga85b10143618f300ff4f5bc6d45c72c01ae0d37dc2c7d39753a80f6e0ba64e5e22"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01ae0d37dc2c7d39753a80f6e0ba64e5e22"></a></strong>HEVC_MAIN_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790728914084825"><a name="p790728914084825"></a><a name="p790728914084825"></a>H.265 Main</p>
<p id="p20714214111520"><a name="p20714214111520"></a><a name="p20714214111520"></a></p>
</td>
</tr>
<tr id="row910695449084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry365735170084825p0"><a name="entry365735170084825p0"></a><a name="entry365735170084825p0"></a><strong id="gga85b10143618f300ff4f5bc6d45c72c01a811b9e02d8b0afa93e7ab8d2aa7e5de6"><a name="gga85b10143618f300ff4f5bc6d45c72c01a811b9e02d8b0afa93e7ab8d2aa7e5de6"></a><a name="gga85b10143618f300ff4f5bc6d45c72c01a811b9e02d8b0afa93e7ab8d2aa7e5de6"></a></strong>HEVC_MAIN_10_PROFILE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p332887398084825"><a name="p332887398084825"></a><a name="p332887398084825"></a>H.265 Main 10</p>
<p id="p177147143157"><a name="p177147143157"></a><a name="p177147143157"></a></p>
</td>
</tr>
</tbody>
</table>

## StreamFlagType<a name="ga8a15793172118d64d8adeba0c8544e84"></a>

```
enum [StreamFlagType](codec.md#ga8a15793172118d64d8adeba0c8544e84)
```

**Description:**

Enumerates stream flags.

<a name="table2056128170084825"></a>
<table><thead align="left"><tr id="row611205959084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p298469450084825"><a name="p298469450084825"></a><a name="p298469450084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1307682009084825"><a name="p1307682009084825"></a><a name="p1307682009084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1214075341084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry139125619084825p0"><a name="entry139125619084825p0"></a><a name="entry139125619084825p0"></a><strong id="gga8a15793172118d64d8adeba0c8544e84ae0da6ed262d36cb4de4b63cd25889ea2"><a name="gga8a15793172118d64d8adeba0c8544e84ae0da6ed262d36cb4de4b63cd25889ea2"></a><a name="gga8a15793172118d64d8adeba0c8544e84ae0da6ed262d36cb4de4b63cd25889ea2"></a></strong>STREAM_FLAG_KEYFRAME</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91099709084825"><a name="p91099709084825"></a><a name="p91099709084825"></a>Keyframe</p>
<p id="p187242014151510"><a name="p187242014151510"></a><a name="p187242014151510"></a></p>
</td>
</tr>
<tr id="row1310425943084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry999399251084825p0"><a name="entry999399251084825p0"></a><a name="entry999399251084825p0"></a><strong id="gga8a15793172118d64d8adeba0c8544e84a9a06fdc891d28272ba6651ca9791d166"><a name="gga8a15793172118d64d8adeba0c8544e84a9a06fdc891d28272ba6651ca9791d166"></a><a name="gga8a15793172118d64d8adeba0c8544e84a9a06fdc891d28272ba6651ca9791d166"></a></strong>STREAM_FLAG_CODEC_SPECIFIC_INF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1893290493084825"><a name="p1893290493084825"></a><a name="p1893290493084825"></a>Codec specifications</p>
<p id="p177241914101514"><a name="p177241914101514"></a><a name="p177241914101514"></a></p>
</td>
</tr>
<tr id="row441880001084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry540697039084825p0"><a name="entry540697039084825p0"></a><a name="entry540697039084825p0"></a><strong id="gga8a15793172118d64d8adeba0c8544e84abe40ab8f6da71b5a7d6a382954dc5d4f"><a name="gga8a15793172118d64d8adeba0c8544e84abe40ab8f6da71b5a7d6a382954dc5d4f"></a><a name="gga8a15793172118d64d8adeba0c8544e84abe40ab8f6da71b5a7d6a382954dc5d4f"></a></strong>STREAM_FLAG_EOS</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1686175974084825"><a name="p1686175974084825"></a><a name="p1686175974084825"></a>End of streams</p>
<p id="p167241314131511"><a name="p167241314131511"></a><a name="p167241314131511"></a></p>
</td>
</tr>
<tr id="row535789080084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1938148147084825p0"><a name="entry1938148147084825p0"></a><a name="entry1938148147084825p0"></a><strong id="gga8a15793172118d64d8adeba0c8544e84a7809fe65541dc27f50ba4952685c34bd"><a name="gga8a15793172118d64d8adeba0c8544e84a7809fe65541dc27f50ba4952685c34bd"></a><a name="gga8a15793172118d64d8adeba0c8544e84a7809fe65541dc27f50ba4952685c34bd"></a></strong>STREAM_FLAG_PART_OF_FRAME</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1967430782084825"><a name="p1967430782084825"></a><a name="p1967430782084825"></a>Partial frame</p>
<p id="p14724714191514"><a name="p14724714191514"></a><a name="p14724714191514"></a></p>
</td>
</tr>
<tr id="row1826372198084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1026223343084825p0"><a name="entry1026223343084825p0"></a><a name="entry1026223343084825p0"></a><strong id="gga8a15793172118d64d8adeba0c8544e84abb9a3fba052c516ac141e34ea9fa6dca"><a name="gga8a15793172118d64d8adeba0c8544e84abb9a3fba052c516ac141e34ea9fa6dca"></a><a name="gga8a15793172118d64d8adeba0c8544e84abb9a3fba052c516ac141e34ea9fa6dca"></a></strong>STREAM_FLAG_END_OF_FRAME</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441422808084825"><a name="p1441422808084825"></a><a name="p1441422808084825"></a>End of frames, used in pair with <strong id="b890118506084825"><a name="b890118506084825"></a><a name="b890118506084825"></a> STREAM_FLAG_PART_OF_FRAME</strong></p>
<p id="p172461419151"><a name="p172461419151"></a><a name="p172461419151"></a></p>
</td>
</tr>
</tbody>
</table>

## VenCodeGopMode<a name="ga9532f651a003219a262c440f5621d129"></a>

```
enum [VenCodeGopMode](codec.md#ga9532f651a003219a262c440f5621d129)
```

**Description:**

Enumerates types of group of pictures \(GOP\).

<a name="table1538395380084825"></a>
<table><thead align="left"><tr id="row249389098084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1144217571084825"><a name="p1144217571084825"></a><a name="p1144217571084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1045573042084825"><a name="p1045573042084825"></a><a name="p1045573042084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1247791979084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1708085295084825p0"><a name="entry1708085295084825p0"></a><a name="entry1708085295084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129a1f3b41538fdbdbb9f920f740f89c7c95"><a name="gga9532f651a003219a262c440f5621d129a1f3b41538fdbdbb9f920f740f89c7c95"></a><a name="gga9532f651a003219a262c440f5621d129a1f3b41538fdbdbb9f920f740f89c7c95"></a></strong>VENCOD_GOPMODE_NORMALP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19014177084825"><a name="p19014177084825"></a><a name="p19014177084825"></a>P-frames using only one reference frame during encoding</p>
<p id="p18729614171510"><a name="p18729614171510"></a><a name="p18729614171510"></a></p>
</td>
</tr>
<tr id="row325674044084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry55213914084825p0"><a name="entry55213914084825p0"></a><a name="entry55213914084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129a6b063f65ef8ec77e360bbbd56c7b233f"><a name="gga9532f651a003219a262c440f5621d129a6b063f65ef8ec77e360bbbd56c7b233f"></a><a name="gga9532f651a003219a262c440f5621d129a6b063f65ef8ec77e360bbbd56c7b233f"></a></strong>VENCOD_GOPMODE_DUALP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1358809981084825"><a name="p1358809981084825"></a><a name="p1358809981084825"></a>P-frames using two reference frames during encoding</p>
<p id="p117293146157"><a name="p117293146157"></a><a name="p117293146157"></a></p>
</td>
</tr>
<tr id="row310318597084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry753369364084825p0"><a name="entry753369364084825p0"></a><a name="entry753369364084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129a37226f50b4e07586d8bd8e22114e2324"><a name="gga9532f651a003219a262c440f5621d129a37226f50b4e07586d8bd8e22114e2324"></a><a name="gga9532f651a003219a262c440f5621d129a37226f50b4e07586d8bd8e22114e2324"></a></strong>VENCOD_GOPMODE_SMARTP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182334422084825"><a name="p1182334422084825"></a><a name="p1182334422084825"></a>Smart P-frames for encoding</p>
<p id="p16729111418159"><a name="p16729111418159"></a><a name="p16729111418159"></a></p>
</td>
</tr>
<tr id="row981384044084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1005156280084825p0"><a name="entry1005156280084825p0"></a><a name="entry1005156280084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129a8caa9e9fae7ca1d041ccb163bbcf92c6"><a name="gga9532f651a003219a262c440f5621d129a8caa9e9fae7ca1d041ccb163bbcf92c6"></a><a name="gga9532f651a003219a262c440f5621d129a8caa9e9fae7ca1d041ccb163bbcf92c6"></a></strong>VENCOD_GOPMODE_ADVSMARTP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229387188084825"><a name="p229387188084825"></a><a name="p229387188084825"></a>Advanced smart P-frames for encoding</p>
<p id="p11729314141510"><a name="p11729314141510"></a><a name="p11729314141510"></a></p>
</td>
</tr>
<tr id="row727207872084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1195712660084825p0"><a name="entry1195712660084825p0"></a><a name="entry1195712660084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129a7a120c500828b79e7a87e4f8a9d4378c"><a name="gga9532f651a003219a262c440f5621d129a7a120c500828b79e7a87e4f8a9d4378c"></a><a name="gga9532f651a003219a262c440f5621d129a7a120c500828b79e7a87e4f8a9d4378c"></a></strong>VENCOD_GOPMODE_BIPREDB</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p906503645084825"><a name="p906503645084825"></a><a name="p906503645084825"></a>B-frames for encoding</p>
<p id="p107291314121514"><a name="p107291314121514"></a><a name="p107291314121514"></a></p>
</td>
</tr>
<tr id="row742617908084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1536335276084825p0"><a name="entry1536335276084825p0"></a><a name="entry1536335276084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129ae02038b7e71cb65c991676da17a11a73"><a name="gga9532f651a003219a262c440f5621d129ae02038b7e71cb65c991676da17a11a73"></a><a name="gga9532f651a003219a262c440f5621d129ae02038b7e71cb65c991676da17a11a73"></a></strong>VENCOD_GOPMODE_LOWDELAYB</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577954824084825"><a name="p577954824084825"></a><a name="p577954824084825"></a>B-frames using only previous frames as references during encoding.</p>
<p id="p1272951420158"><a name="p1272951420158"></a><a name="p1272951420158"></a></p>
</td>
</tr>
<tr id="row96883341084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry815903897084825p0"><a name="entry815903897084825p0"></a><a name="entry815903897084825p0"></a><strong id="gga9532f651a003219a262c440f5621d129a6b54943891a852da1b3e37cac4893b55"><a name="gga9532f651a003219a262c440f5621d129a6b54943891a852da1b3e37cac4893b55"></a><a name="gga9532f651a003219a262c440f5621d129a6b54943891a852da1b3e37cac4893b55"></a></strong>VENCOD_GOPMODE_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061579100084825"><a name="p1061579100084825"></a><a name="p1061579100084825"></a>Invalid type</p>
<p id="p172914146152"><a name="p172914146152"></a><a name="p172914146152"></a></p>
</td>
</tr>
</tbody>
</table>

## VenCodeRcMode<a name="ga94267d7ba495136561e1c65686b240f7"></a>

```
enum [VenCodeRcMode](codec.md#ga94267d7ba495136561e1c65686b240f7)
```

**Description:**

Enumerates control modes of the channel encoding rate.

<a name="table519134631084825"></a>
<table><thead align="left"><tr id="row748703884084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p549683445084825"><a name="p549683445084825"></a><a name="p549683445084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p959268609084825"><a name="p959268609084825"></a><a name="p959268609084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2064326349084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry676158434084825p0"><a name="entry676158434084825p0"></a><a name="entry676158434084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7af65e058f6076a39b864a5e5351c508a8"><a name="gga94267d7ba495136561e1c65686b240f7af65e058f6076a39b864a5e5351c508a8"></a><a name="gga94267d7ba495136561e1c65686b240f7af65e058f6076a39b864a5e5351c508a8"></a></strong>VENCOD_RC_CBR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801463902084825"><a name="p801463902084825"></a><a name="p801463902084825"></a>Fixed bit rate</p>
<p id="p073418141153"><a name="p073418141153"></a><a name="p073418141153"></a></p>
</td>
</tr>
<tr id="row1148693195084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1103444917084825p0"><a name="entry1103444917084825p0"></a><a name="entry1103444917084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7ad40974ef1c63cc0fcef1106a69dc696a"><a name="gga94267d7ba495136561e1c65686b240f7ad40974ef1c63cc0fcef1106a69dc696a"></a><a name="gga94267d7ba495136561e1c65686b240f7ad40974ef1c63cc0fcef1106a69dc696a"></a></strong>VENCOD_RC_VBR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p658855062084825"><a name="p658855062084825"></a><a name="p658855062084825"></a>Variable bit rate</p>
<p id="p273431431513"><a name="p273431431513"></a><a name="p273431431513"></a></p>
</td>
</tr>
<tr id="row2142455358084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1927236794084825p0"><a name="entry1927236794084825p0"></a><a name="entry1927236794084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7ae4e2d1f85e783430a12ad412edf21ddc"><a name="gga94267d7ba495136561e1c65686b240f7ae4e2d1f85e783430a12ad412edf21ddc"></a><a name="gga94267d7ba495136561e1c65686b240f7ae4e2d1f85e783430a12ad412edf21ddc"></a></strong>VENCOD_RC_AVBR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844115422084825"><a name="p844115422084825"></a><a name="p844115422084825"></a>Adaptive variable bit rate</p>
<p id="p3734101418154"><a name="p3734101418154"></a><a name="p3734101418154"></a></p>
</td>
</tr>
<tr id="row207295159084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1062662207084825p0"><a name="entry1062662207084825p0"></a><a name="entry1062662207084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7aa3294f73cd0cd078618ef9db4d3cb6f5"><a name="gga94267d7ba495136561e1c65686b240f7aa3294f73cd0cd078618ef9db4d3cb6f5"></a><a name="gga94267d7ba495136561e1c65686b240f7aa3294f73cd0cd078618ef9db4d3cb6f5"></a></strong>VENCOD_RC_QVBR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2146570069084825"><a name="p2146570069084825"></a><a name="p2146570069084825"></a>Quality-defined variable bit rate</p>
<p id="p6735514101520"><a name="p6735514101520"></a><a name="p6735514101520"></a></p>
</td>
</tr>
<tr id="row76076640084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1810884867084825p0"><a name="entry1810884867084825p0"></a><a name="entry1810884867084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7ad43d98e7b3b42efa4cc6d4d1a2298024"><a name="gga94267d7ba495136561e1c65686b240f7ad43d98e7b3b42efa4cc6d4d1a2298024"></a><a name="gga94267d7ba495136561e1c65686b240f7ad43d98e7b3b42efa4cc6d4d1a2298024"></a></strong>VENCOD_RC_CVBR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466399446084825"><a name="p1466399446084825"></a><a name="p1466399446084825"></a>Constrained variable bit rate</p>
<p id="p373591415159"><a name="p373591415159"></a><a name="p373591415159"></a></p>
</td>
</tr>
<tr id="row1444154350084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry977889840084825p0"><a name="entry977889840084825p0"></a><a name="entry977889840084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7a3e89e3affbe63967e5cdfc3b162d8ac9"><a name="gga94267d7ba495136561e1c65686b240f7a3e89e3affbe63967e5cdfc3b162d8ac9"></a><a name="gga94267d7ba495136561e1c65686b240f7a3e89e3affbe63967e5cdfc3b162d8ac9"></a></strong>VENCOD_RC_QPMAP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p819221524084825"><a name="p819221524084825"></a><a name="p819221524084825"></a>Configuration-mapped quantization parameters</p>
<p id="p17351142157"><a name="p17351142157"></a><a name="p17351142157"></a></p>
</td>
</tr>
<tr id="row1589626685084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1280920586084825p0"><a name="entry1280920586084825p0"></a><a name="entry1280920586084825p0"></a><strong id="gga94267d7ba495136561e1c65686b240f7ae9a1e0b19d79f1c2bdada4c5830e2584"><a name="gga94267d7ba495136561e1c65686b240f7ae9a1e0b19d79f1c2bdada4c5830e2584"></a><a name="gga94267d7ba495136561e1c65686b240f7ae9a1e0b19d79f1c2bdada4c5830e2584"></a></strong>VENCOD_RC_FIXQP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1620786949084825"><a name="p1620786949084825"></a><a name="p1620786949084825"></a>Fixed quantization parameters</p>
<p id="p5735181441513"><a name="p5735181441513"></a><a name="p5735181441513"></a></p>
</td>
</tr>
</tbody>
</table>

## VideoField<a name="ga1420ddfb066b941fb55a153b869d9ccf"></a>

```
enum [VideoField](codec.md#ga1420ddfb066b941fb55a153b869d9ccf)
```

**Description:**

Enumerates video frame fields.

<a name="table1916598085084825"></a>
<table><thead align="left"><tr id="row1265981939084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1118104555084825"><a name="p1118104555084825"></a><a name="p1118104555084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p776502608084825"><a name="p776502608084825"></a><a name="p776502608084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1906729342084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry485044455084825p0"><a name="entry485044455084825p0"></a><a name="entry485044455084825p0"></a><strong id="gga1420ddfb066b941fb55a153b869d9ccfadf9934801550e7c45e395d8e4704aff9"><a name="gga1420ddfb066b941fb55a153b869d9ccfadf9934801550e7c45e395d8e4704aff9"></a><a name="gga1420ddfb066b941fb55a153b869d9ccfadf9934801550e7c45e395d8e4704aff9"></a></strong>VID_FIELD_TOP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672959982084825"><a name="p672959982084825"></a><a name="p672959982084825"></a>Top fields on even-number lines</p>
<p id="p17411814171514"><a name="p17411814171514"></a><a name="p17411814171514"></a></p>
</td>
</tr>
<tr id="row1878259593084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry600597604084825p0"><a name="entry600597604084825p0"></a><a name="entry600597604084825p0"></a><strong id="gga1420ddfb066b941fb55a153b869d9ccfa3de04ce552cc5a52d977256efed8611a"><a name="gga1420ddfb066b941fb55a153b869d9ccfa3de04ce552cc5a52d977256efed8611a"></a><a name="gga1420ddfb066b941fb55a153b869d9ccfa3de04ce552cc5a52d977256efed8611a"></a></strong>VID_FIELD_BOTTOM</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223153136084825"><a name="p223153136084825"></a><a name="p223153136084825"></a>Bottom fields on odd-number lines</p>
<p id="p474171431511"><a name="p474171431511"></a><a name="p474171431511"></a></p>
</td>
</tr>
<tr id="row1873076830084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry181626577084825p0"><a name="entry181626577084825p0"></a><a name="entry181626577084825p0"></a><strong id="gga1420ddfb066b941fb55a153b869d9ccfa9c3bffc837d46ece68154c98bfc4c303"><a name="gga1420ddfb066b941fb55a153b869d9ccfa9c3bffc837d46ece68154c98bfc4c303"></a><a name="gga1420ddfb066b941fb55a153b869d9ccfa9c3bffc837d46ece68154c98bfc4c303"></a></strong>VID_FIELD_INTERLACED</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1805241498084825"><a name="p1805241498084825"></a><a name="p1805241498084825"></a>Interlaced fields</p>
<p id="p07414140157"><a name="p07414140157"></a><a name="p07414140157"></a></p>
</td>
</tr>
<tr id="row325366270084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry918307348084825p0"><a name="entry918307348084825p0"></a><a name="entry918307348084825p0"></a><strong id="gga1420ddfb066b941fb55a153b869d9ccfaaf092a3bb1b706a47a425e7eff683526"><a name="gga1420ddfb066b941fb55a153b869d9ccfaaf092a3bb1b706a47a425e7eff683526"></a><a name="gga1420ddfb066b941fb55a153b869d9ccfaaf092a3bb1b706a47a425e7eff683526"></a></strong>VID_FIELD_FRAME</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p292212715084825"><a name="p292212715084825"></a><a name="p292212715084825"></a>Non-interlaced frames</p>
<p id="p147411414171520"><a name="p147411414171520"></a><a name="p147411414171520"></a></p>
</td>
</tr>
<tr id="row71618782084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1133920810084825p0"><a name="entry1133920810084825p0"></a><a name="entry1133920810084825p0"></a><strong id="gga1420ddfb066b941fb55a153b869d9ccfaedd6cdcd59983317521c2ac717884405"><a name="gga1420ddfb066b941fb55a153b869d9ccfaedd6cdcd59983317521c2ac717884405"></a><a name="gga1420ddfb066b941fb55a153b869d9ccfaedd6cdcd59983317521c2ac717884405"></a></strong>VID_FIELD_INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1753320791084825"><a name="p1753320791084825"></a><a name="p1753320791084825"></a>Invalid fields</p>
<p id="p167411714131510"><a name="p167411714131510"></a><a name="p167411714131510"></a></p>
</td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1090685024084825"></a>

## CodecCreate\(\)<a name="ga74aa0395a51f004390f7a92fb68faddd"></a>

```
int32_t CodecCreate (const char * name, const [Param](en-us_topic_0000001054718161.md) * attr, int len, [CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) * handle )
```

**Description:**

Creates a specific codec component and returns the component context through a handle.

You can adjust the parameters required for creating a component based on service requirements.

**Parameters:**

<a name="table735230942084825"></a>
<table><thead align="left"><tr id="row163964466084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1207721189084825"><a name="p1207721189084825"></a><a name="p1207721189084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2060014952084825"><a name="p2060014952084825"></a><a name="p2060014952084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1835588698084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1564128906084825p0"><a name="entry1564128906084825p0"></a><a name="entry1564128906084825p0"></a>name</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1421773323084825p0"><a name="entry1421773323084825p0"></a><a name="entry1421773323084825p0"></a>Indicates the pointer to the unique name of the component, for example, <strong id="b1998156117084825"><a name="b1998156117084825"></a><a name="b1998156117084825"></a>codec.avc.hardware.decoder</strong>.</p>
</td>
</tr>
<tr id="row1499675072084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1699510368084825p0"><a name="entry1699510368084825p0"></a><a name="entry1699510368084825p0"></a>attr</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry885741856084825p0"><a name="entry885741856084825p0"></a><a name="entry885741856084825p0"></a>Indicates the pointer to the parameters in the array required for creating the component.</p>
</td>
</tr>
<tr id="row1915695836084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry48975255084825p0"><a name="entry48975255084825p0"></a><a name="entry48975255084825p0"></a>len</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry775498920084825p0"><a name="entry775498920084825p0"></a><a name="entry775498920084825p0"></a>Indicates the number of elements in the parameter array.</p>
</td>
</tr>
<tr id="row2111059122084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry699569957084825p0"><a name="entry699569957084825p0"></a><a name="entry699569957084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry829352253084825p0"><a name="entry829352253084825p0"></a><a name="entry829352253084825p0"></a>Indicates the pointer to the codec handle returned.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the codec component is created and the handle is available; returns a non-zero value otherwise.

## CodecDeinit\(\)<a name="ga2d6eb231ca7766990cfa8c1841637245"></a>

```
int32_t CodecDeinit ()
```

**Description:**

Deinitializes the internal audio and video submodules of the codec.

This function needs to be called only once in a process.

**Returns:**

Returns  **0**  if the deinitialization is successful; returns a non-zero value otherwise.

**See also:**

[CodecInit](codec.md#gadb2714f1e7a69419cefd38a2ad1f9829)

## CodecDequeInput\(\)<a name="ga91d7e1566c90d7cb9ac846eecad0024f"></a>

```
int32_t CodecDequeInput ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, uint32_t timeoutMs, [InputInfo](en-us_topic_0000001054879536.md) * inputData )
```

**Description:**

Dequeues input data that has been used.

This function works with  [CodecQueueInput](codec.md#ga0daece8dbf22da84f926761c994819bc)  to implement input data transmission.

**Parameters:**

<a name="table666773633084825"></a>
<table><thead align="left"><tr id="row2115264907084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2104952643084825"><a name="p2104952643084825"></a><a name="p2104952643084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p12520873084825"><a name="p12520873084825"></a><a name="p12520873084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row826448690084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1239943926084825p0"><a name="entry1239943926084825p0"></a><a name="entry1239943926084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry359621515084825p0"><a name="entry359621515084825p0"></a><a name="entry359621515084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row963113545084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2010496439084825p0"><a name="entry2010496439084825p0"></a><a name="entry2010496439084825p0"></a>timeoutMs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry648947922084825p0"><a name="entry648947922084825p0"></a><a name="entry648947922084825p0"></a>Indicates the timeout duration. Generally, the value is less than or equal to <strong id="b2059356765084825"><a name="b2059356765084825"></a><a name="b2059356765084825"></a>3</strong> seconds.</p>
</td>
</tr>
<tr id="row952113758084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry942490297084825p0"><a name="entry942490297084825p0"></a><a name="entry942490297084825p0"></a>inputData</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry353909876084825p0"><a name="entry353909876084825p0"></a><a name="entry353909876084825p0"></a>Indicates the pointer to the input data that is used.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecDequeueOutput\(\)<a name="gab575752467517eb8e6766773c1e3fb23"></a>

```
int32_t CodecDequeueOutput ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, uint32_t timeoutMs, int * acquireFd, [OutputInfo](en-us_topic_0000001054918167.md) * outInfo )
```

**Description:**

Dequeues output data.

This function works with  [CodecQueueOutput](codec.md#gac98f3505082c3cb2413d9e95eef9c804)  to implement output data transmission.

**Parameters:**

<a name="table1039694293084825"></a>
<table><thead align="left"><tr id="row232082526084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1873829043084825"><a name="p1873829043084825"></a><a name="p1873829043084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1968915439084825"><a name="p1968915439084825"></a><a name="p1968915439084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1071188033084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry280129646084825p0"><a name="entry280129646084825p0"></a><a name="entry280129646084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry430722261084825p0"><a name="entry430722261084825p0"></a><a name="entry430722261084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row1836251159084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1245917050084825p0"><a name="entry1245917050084825p0"></a><a name="entry1245917050084825p0"></a>timeoutMs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1509898048084825p0"><a name="entry1509898048084825p0"></a><a name="entry1509898048084825p0"></a>Indicates the timeout duration.</p>
</td>
</tr>
<tr id="row1893469643084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1372561875084825p0"><a name="entry1372561875084825p0"></a><a name="entry1372561875084825p0"></a>acquireFd</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1827737374084825p0"><a name="entry1827737374084825p0"></a><a name="entry1827737374084825p0"></a>Indicates that this parameter is derived from the codec mode. The output data can be used only after waiting for <strong id="b1354633854084825"><a name="b1354633854084825"></a><a name="b1354633854084825"></a>acquireFd</strong> is successful. The value <strong id="b1879755682084825"><a name="b1879755682084825"></a><a name="b1879755682084825"></a>-1</strong> indicates that <strong id="b1596305032084825"><a name="b1596305032084825"></a><a name="b1596305032084825"></a>acquireFd</strong> is invalid.</p>
</td>
</tr>
<tr id="row863445468084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1104451796084825p0"><a name="entry1104451796084825p0"></a><a name="entry1104451796084825p0"></a>outInfo</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1554571688084825p0"><a name="entry1554571688084825p0"></a><a name="entry1554571688084825p0"></a>Indicates the pointer to the output data.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecDestroy\(\)<a name="ga1bc0592b05e4f687e2bef2ffb83102b8"></a>

```
int32_t CodecDestroy ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle)
```

**Description:**

Destroys a codec component.

**Parameters:**

<a name="table860862295084825"></a>
<table><thead align="left"><tr id="row691193737084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1105964499084825"><a name="p1105964499084825"></a><a name="p1105964499084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p830880735084825"><a name="p830880735084825"></a><a name="p830880735084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row517997588084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry507026644084825p0"><a name="entry507026644084825p0"></a><a name="entry507026644084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1941507553084825p0"><a name="entry1941507553084825p0"></a><a name="entry1941507553084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the codec component is destroyed; returns a non-zero value otherwise.

**See also:**

[CodecCreate](codec.md#ga74aa0395a51f004390f7a92fb68faddd)

## CodecEnumerateCapbility\(\)<a name="gaf0bb69d2f8c5ad0fec6959b353ee1acd"></a>

```
int32_t CodecEnumerateCapbility (uint32_t index, [CodecCapbility](codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3) * cap )
```

**Description:**

Obtains the capabilities of a specified media type based on an index.

You can call this function repeatedly to obtain the codec capabilities until  **CODEC\_END**  is returned. The corresponding capabilities are described in the  **Capability**  structure, including the maximum and minimum resolutions, maximum and minimum bit rates, and supported profiles and levels. After obtaining the capabilities, determine whether they can meet your requirements, for example, whether specific media files can be played and whether audio and video frames can be compressed.

**Parameters:**

<a name="table452904715084825"></a>
<table><thead align="left"><tr id="row1971046470084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1254476732084825"><a name="p1254476732084825"></a><a name="p1254476732084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1251046721084825"><a name="p1251046721084825"></a><a name="p1251046721084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row327404230084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1383698058084825p0"><a name="entry1383698058084825p0"></a><a name="entry1383698058084825p0"></a>index</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry358449600084825p0"><a name="entry358449600084825p0"></a><a name="entry358449600084825p0"></a>Indicates the index of the capabilities.</p>
</td>
</tr>
<tr id="row110525459084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1405000693084825p0"><a name="entry1405000693084825p0"></a><a name="entry1405000693084825p0"></a>cap</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry533112258084825p0"><a name="entry533112258084825p0"></a><a name="entry533112258084825p0"></a>Indicates the pointer to the capabilities.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **CODEC\_SUCCESS**  if the capabilities corresponding to the index are available; returns  **CODEC\_END**  otherwise.

## CodecFlush\(\)<a name="gaa6ed6c24e29f8fdfbbb0a3d562260a6a"></a>

```
int32_t CodecFlush ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, [DirectionType](codec.md#ga8ef30fa9c08e08c8706653571f9f5b81) directType )
```

**Description:**

Clears the cache when the codec component is the running state.

Generally, this function is called when the seek operation is performed during playback.

**Parameters:**

<a name="table1233000965084825"></a>
<table><thead align="left"><tr id="row1227382675084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p965214064084825"><a name="p965214064084825"></a><a name="p965214064084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1211217877084825"><a name="p1211217877084825"></a><a name="p1211217877084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1029654830084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2014699087084825p0"><a name="entry2014699087084825p0"></a><a name="entry2014699087084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry774842741084825p0"><a name="entry774842741084825p0"></a><a name="entry774842741084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecGetCapbility\(\)<a name="ga1a6fbf6e84e01fdc1af59caa4203ce8e"></a>

```
int32_t CodecGetCapbility ([AvCodecMime](codec.md#ga1bee586eafa91dfb60f94ba40fc95faa) mime, [CodecType](codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79) type, uint32_t flags, [CodecCapbility](codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3) * cap )
```

**Description:**

Obtains the capabilities of a specified media type.

You can call this function to obtain the codec capabilities. The corresponding capabilities are described in the  **Capability**  structure, including the maximum and minimum resolutions, maximum and minimum bit rates, and supported profiles and levels. After obtaining the capabilities, determine whether they can meet your requirements, for example, whether specific media files can be played and whether audio and video frames can be compressed.

**Parameters:**

<a name="table2138177685084825"></a>
<table><thead align="left"><tr id="row938928818084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1144624079084825"><a name="p1144624079084825"></a><a name="p1144624079084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p92743395084825"><a name="p92743395084825"></a><a name="p92743395084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row321490532084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry799343324084825p0"><a name="entry799343324084825p0"></a><a name="entry799343324084825p0"></a>mime</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1572955627084825p0"><a name="entry1572955627084825p0"></a><a name="entry1572955627084825p0"></a>Indicates the media type. For details, see <a href="codec.md#ga1bee586eafa91dfb60f94ba40fc95faa">AvCodecMime</a>.</p>
</td>
</tr>
<tr id="row301888208084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry307395619084825p0"><a name="entry307395619084825p0"></a><a name="entry307395619084825p0"></a>type</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry33929247084825p0"><a name="entry33929247084825p0"></a><a name="entry33929247084825p0"></a>Indicates the audio and video codec types. For details, see <a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a>.</p>
</td>
</tr>
<tr id="row1085536876084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1321805664084825p0"><a name="entry1321805664084825p0"></a><a name="entry1321805664084825p0"></a>flags</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry889497770084825p0"><a name="entry889497770084825p0"></a><a name="entry889497770084825p0"></a>Indicates the audio and video codec flags. <strong id="b1842257132084825"><a name="b1842257132084825"></a><a name="b1842257132084825"></a>0</strong> indicates hardware codec, and <strong id="b522784548084825"><a name="b522784548084825"></a><a name="b522784548084825"></a>1</strong> indicates software codec.</p>
</td>
</tr>
<tr id="row455086322084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1277656221084825p0"><a name="entry1277656221084825p0"></a><a name="entry1277656221084825p0"></a>cap</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry59266180084825p0"><a name="entry59266180084825p0"></a><a name="entry59266180084825p0"></a>Indicates the pointer to the capabilities.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the codec is supported and capabilities are available; returns a non-zero value if the codec is not supported or the capabilities are unavailable.

## CodecGetParameter\(\)<a name="ga1d812eac032e3e05cf5bf71b03e93f65"></a>

```
int32_t CodecGetParameter ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, [Param](en-us_topic_0000001054718161.md) * params, int paramCnt )
```

**Description:**

Obtains parameters from a codec component.

This function must be called after  [CodecCreate](codec.md#ga74aa0395a51f004390f7a92fb68faddd).

**Parameters:**

<a name="table898143746084825"></a>
<table><thead align="left"><tr id="row1288182335084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2107397988084825"><a name="p2107397988084825"></a><a name="p2107397988084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1512543297084825"><a name="p1512543297084825"></a><a name="p1512543297084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1719426667084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry10439545084825p0"><a name="entry10439545084825p0"></a><a name="entry10439545084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry554311197084825p0"><a name="entry554311197084825p0"></a><a name="entry554311197084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row1598013451084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2118470564084825p0"><a name="entry2118470564084825p0"></a><a name="entry2118470564084825p0"></a>params</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry645679412084825p0"><a name="entry645679412084825p0"></a><a name="entry645679412084825p0"></a>Indicates the pointer to the parameters in the array used when the component is created.</p>
</td>
</tr>
<tr id="row1395562827084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry786037209084825p0"><a name="entry786037209084825p0"></a><a name="entry786037209084825p0"></a>paramCnt</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry2055808600084825p0"><a name="entry2055808600084825p0"></a><a name="entry2055808600084825p0"></a>Indicates the number of elements in the parameter array.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if all parameters to obtain are supported; returns a non-zero value otherwise.

**See also:**

[CodecSetParameter](codec.md#gaa080cf23aa5f77b30f3b90a026d97cc0)

## CodecInit\(\)<a name="gadb2714f1e7a69419cefd38a2ad1f9829"></a>

```
int32_t CodecInit ()
```

**Description:**

Initializes the internal audio and video submodules of the codec.

This function needs to be called only once in a process.

**Returns:**

Returns  **0**  if the initialization is successful; returns a non-zero value otherwise.

**See also:**

[CodecDeinit](codec.md#ga2d6eb231ca7766990cfa8c1841637245)

## CodecQueueInput\(\)<a name="ga0daece8dbf22da84f926761c994819bc"></a>

```
int32_t CodecQueueInput ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, const [InputInfo](en-us_topic_0000001054879536.md) * inputData, uint32_t timeoutMs )
```

**Description:**

Queues input data.

This function works with  [CodecDequeInput](codec.md#ga91d7e1566c90d7cb9ac846eecad0024f)  to implement input data transmission.

**Parameters:**

<a name="table1253249514084825"></a>
<table><thead align="left"><tr id="row960265471084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1151492979084825"><a name="p1151492979084825"></a><a name="p1151492979084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p206668769084825"><a name="p206668769084825"></a><a name="p206668769084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row194856533084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry198410828084825p0"><a name="entry198410828084825p0"></a><a name="entry198410828084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1696470468084825p0"><a name="entry1696470468084825p0"></a><a name="entry1696470468084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row319187960084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1309520926084825p0"><a name="entry1309520926084825p0"></a><a name="entry1309520926084825p0"></a>inputData</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1563987247084825p0"><a name="entry1563987247084825p0"></a><a name="entry1563987247084825p0"></a>Indicates the pointer to the input data.</p>
</td>
</tr>
<tr id="row1590657593084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1153185942084825p0"><a name="entry1153185942084825p0"></a><a name="entry1153185942084825p0"></a>timeoutMs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry736445442084825p0"><a name="entry736445442084825p0"></a><a name="entry736445442084825p0"></a>Indicates the timeout duration.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecQueueOutput\(\)<a name="gac98f3505082c3cb2413d9e95eef9c804"></a>

```
int32_t CodecQueueOutput ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, [OutputInfo](en-us_topic_0000001054918167.md) * outInfo, uint32_t timeoutMs, int releaseFenceFd )
```

**Description:**

Queues output data.

This function works with  [CodecDequeueOutput](codec.md#gab575752467517eb8e6766773c1e3fb23)  to implement output data transmission.

**Parameters:**

<a name="table894638425084825"></a>
<table><thead align="left"><tr id="row1429791989084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p565653683084825"><a name="p565653683084825"></a><a name="p565653683084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p741196862084825"><a name="p741196862084825"></a><a name="p741196862084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1279013842084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry250741343084825p0"><a name="entry250741343084825p0"></a><a name="entry250741343084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1354439491084825p0"><a name="entry1354439491084825p0"></a><a name="entry1354439491084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row1665799478084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1397718631084825p0"><a name="entry1397718631084825p0"></a><a name="entry1397718631084825p0"></a>outInfo</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry105807911084825p0"><a name="entry105807911084825p0"></a><a name="entry105807911084825p0"></a>Indicates the pointer to the output data.</p>
</td>
</tr>
<tr id="row487209711084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1995823974084825p0"><a name="entry1995823974084825p0"></a><a name="entry1995823974084825p0"></a>timeoutMs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1193681389084825p0"><a name="entry1193681389084825p0"></a><a name="entry1193681389084825p0"></a>Indicates the timeout duration.</p>
</td>
</tr>
<tr id="row1396793935084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry383625994084825p0"><a name="entry383625994084825p0"></a><a name="entry383625994084825p0"></a>releaseFenceFd</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1446433111084825p0"><a name="entry1446433111084825p0"></a><a name="entry1446433111084825p0"></a>Indicates that the descriptor comes from a buffer consumer. The output data can be used only after waiting for <strong id="b1967390178084825"><a name="b1967390178084825"></a><a name="b1967390178084825"></a>releaseFenceFd</strong> is successful. The value <strong id="b23665421084825"><a name="b23665421084825"></a><a name="b23665421084825"></a>-1</strong> indicates that <strong id="b1843359003084825"><a name="b1843359003084825"></a><a name="b1843359003084825"></a>releaseFenceFd</strong> is invalid.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecSetCallback\(\)<a name="ga28ec6149d05765ee75f4836e0b092406"></a>

```
int32_t CodecSetCallback ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, const [CodecCallback](en-us_topic_0000001055358102.md) * cb, [UINTPTR](codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc) instance )
```

**Description:**

Sets the callback function.

The codec uses the callback function to notify the upper layer of events and asynchronously report available input/output information.

**Parameters:**

<a name="table1885415744084825"></a>
<table><thead align="left"><tr id="row147161429084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p764119065084825"><a name="p764119065084825"></a><a name="p764119065084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2035913532084825"><a name="p2035913532084825"></a><a name="p2035913532084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1934120489084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1186851599084825p0"><a name="entry1186851599084825p0"></a><a name="entry1186851599084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1798092188084825p0"><a name="entry1798092188084825p0"></a><a name="entry1798092188084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row1940398606084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry63140447084825p0"><a name="entry63140447084825p0"></a><a name="entry63140447084825p0"></a>cb</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1974408102084825p0"><a name="entry1974408102084825p0"></a><a name="entry1974408102084825p0"></a>Indicates the pointer to the callback function. For details, see <a href="en-us_topic_0000001055358102.md">CodecCallback</a>.</p>
</td>
</tr>
<tr id="row1521883720084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1682377396084825p0"><a name="entry1682377396084825p0"></a><a name="entry1682377396084825p0"></a>instance</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry289331572084825p0"><a name="entry289331572084825p0"></a><a name="entry289331572084825p0"></a>Indicates the upper-layer instance to be notified.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecSetParameter\(\)<a name="gaa080cf23aa5f77b30f3b90a026d97cc0"></a>

```
int32_t CodecSetParameter ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, const [Param](en-us_topic_0000001054718161.md) * params, int paramCnt )
```

**Description:**

Sets parameters required by a codec component.

You should call this function to set parameters after  [CodecCreate](codec.md#ga74aa0395a51f004390f7a92fb68faddd)  is called but before  [CodecStart](codec.md#ga38c1744b0b4be5817ef49556ae665d18)  is called.

**Parameters:**

<a name="table1128452163084825"></a>
<table><thead align="left"><tr id="row767299604084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2125122051084825"><a name="p2125122051084825"></a><a name="p2125122051084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p452846676084825"><a name="p452846676084825"></a><a name="p452846676084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1938429500084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry102798173084825p0"><a name="entry102798173084825p0"></a><a name="entry102798173084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1791285824084825p0"><a name="entry1791285824084825p0"></a><a name="entry1791285824084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row1264894687084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1796420034084825p0"><a name="entry1796420034084825p0"></a><a name="entry1796420034084825p0"></a>params</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry241857675084825p0"><a name="entry241857675084825p0"></a><a name="entry241857675084825p0"></a>Indicates the pointer to the parameters to set in the array.</p>
</td>
</tr>
<tr id="row295345470084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2033907479084825p0"><a name="entry2033907479084825p0"></a><a name="entry2033907479084825p0"></a>paramCnt</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1861952388084825p0"><a name="entry1861952388084825p0"></a><a name="entry1861952388084825p0"></a>Indicates the number of elements in the parameter array.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a non-zero value otherwise.

**See also:**

[CodecGetParameter](codec.md#ga1d812eac032e3e05cf5bf71b03e93f65)

## CodecSetPortMode\(\)<a name="ga36a994c5f9f4d104aad0c24b5e8cbd37"></a>

```
int32_t CodecSetPortMode ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle, [DirectionType](codec.md#ga8ef30fa9c08e08c8706653571f9f5b81) type, [BufferMode](codec.md#gacc0fd55192fd9f663121b037b06f41e8) mode )
```

**Description:**

Sets the input or output buffer mode.

You can learn about the support of the codec input/output buffer for internal and external buffer modes by calling  [CodecGetCapbility](codec.md#ga1a6fbf6e84e01fdc1af59caa4203ce8e). In this way, you can determine whether to use an internal or external buffer mode. If the current codec can use only the specific buffer mode, you do not need to set it.

**Parameters:**

<a name="table74866355084825"></a>
<table><thead align="left"><tr id="row1311828138084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1461374707084825"><a name="p1461374707084825"></a><a name="p1461374707084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p611373700084825"><a name="p611373700084825"></a><a name="p611373700084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row184307410084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry674908667084825p0"><a name="entry674908667084825p0"></a><a name="entry674908667084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1752409776084825p0"><a name="entry1752409776084825p0"></a><a name="entry1752409776084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
<tr id="row2057182154084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1568064343084825p0"><a name="entry1568064343084825p0"></a><a name="entry1568064343084825p0"></a>type</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry656850602084825p0"><a name="entry656850602084825p0"></a><a name="entry656850602084825p0"></a>Specifies whether the buffer type is an input type or an output type.</p>
</td>
</tr>
<tr id="row1181463390084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1130949932084825p0"><a name="entry1130949932084825p0"></a><a name="entry1130949932084825p0"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry419658038084825p0"><a name="entry419658038084825p0"></a><a name="entry419658038084825p0"></a>Specifies whether to use an internal or external buffer mode.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a non-zero value otherwise.

## CodecStart\(\)<a name="ga38c1744b0b4be5817ef49556ae665d18"></a>

```
int32_t CodecStart ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle)
```

**Description:**

Starts a codec component.

You can restart a component after it is stopped.

**Parameters:**

<a name="table1120774051084825"></a>
<table><thead align="left"><tr id="row421699376084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1549590785084825"><a name="p1549590785084825"></a><a name="p1549590785084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p893493606084825"><a name="p893493606084825"></a><a name="p893493606084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row891132680084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry233784924084825p0"><a name="entry233784924084825p0"></a><a name="entry233784924084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1920939340084825p0"><a name="entry1920939340084825p0"></a><a name="entry1920939340084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

## CodecStop\(\)<a name="ga8e7913c052c2e45e193fb0aab3f5c7fd"></a>

```
int32_t CodecStop ([CODEC_HANDLETYPE](codec.md#ga9381a619f36ac8d5d7f467d2f0404183) handle)
```

**Description:**

Stops a codec component.

**Parameters:**

<a name="table504612769084825"></a>
<table><thead align="left"><tr id="row401260075084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1667110244084825"><a name="p1667110244084825"></a><a name="p1667110244084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1528450723084825"><a name="p1528450723084825"></a><a name="p1528450723084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1172545609084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1275429120084825p0"><a name="entry1275429120084825p0"></a><a name="entry1275429120084825p0"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1895706928084825p0"><a name="entry1895706928084825p0"></a><a name="entry1895706928084825p0"></a>Indicates the handle of the codec component.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.

