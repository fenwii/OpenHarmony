# audio\_types.h<a name="ZH-CN_TOPIC_0000001054479525"></a>

## **Overview**<a name="section605400256093524"></a>

**Related Modules:**

[Audio](Audio.md)

**Description:**

Defines custom data types used in API declarations for the audio module, including audio ports, adapter descriptors, device descriptors, scene descriptors, sampling attributes, and timestamp. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section916116982093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table245242866093524"></a>
<table><thead align="left"><tr id="row884252219093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p534156986093524"><a name="p534156986093524"></a><a name="p534156986093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p884842408093524"><a name="p884842408093524"></a><a name="p884842408093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row668849220093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1298425671093524"><a name="p1298425671093524"></a><a name="p1298425671093524"></a><a href="AudioPort.md">AudioPort</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1509511624093524"><a name="p1509511624093524"></a><a name="p1509511624093524"></a>Defines the audio port. </p>
</td>
</tr>
<tr id="row616831746093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1243944140093524"><a name="p1243944140093524"></a><a name="p1243944140093524"></a><a href="AudioAdapterDescriptor.md">AudioAdapterDescriptor</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2013982052093524"><a name="p2013982052093524"></a><a name="p2013982052093524"></a>Defines the audio adapter descriptor. </p>
</td>
</tr>
<tr id="row1017315092093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1359605105093524"><a name="p1359605105093524"></a><a name="p1359605105093524"></a><a href="AudioDeviceDescriptor.md">AudioDeviceDescriptor</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168357757093524"><a name="p168357757093524"></a><a name="p168357757093524"></a>Defines the audio device descriptor. </p>
</td>
</tr>
<tr id="row688649230093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1470457651093524"><a name="p1470457651093524"></a><a name="p1470457651093524"></a><a href="AudioSceneDescriptor.md">AudioSceneDescriptor</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p830210463093524"><a name="p830210463093524"></a><a name="p830210463093524"></a>Defines the audio scene descriptor. </p>
</td>
</tr>
<tr id="row775628523093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1375146699093524"><a name="p1375146699093524"></a><a name="p1375146699093524"></a><a href="AudioSceneDescriptor-SceneDesc.md">AudioSceneDescriptor::SceneDesc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1696306647093524"><a name="p1696306647093524"></a><a name="p1696306647093524"></a>Describes the audio scene. </p>
</td>
</tr>
<tr id="row1226254500093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1642582058093524"><a name="p1642582058093524"></a><a name="p1642582058093524"></a><a href="AudioSampleAttributes.md">AudioSampleAttributes</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880200162093524"><a name="p1880200162093524"></a><a name="p1880200162093524"></a>Defines audio sampling attributes. </p>
</td>
</tr>
<tr id="row316237419093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48911287093524"><a name="p48911287093524"></a><a name="p48911287093524"></a><a href="AudioTimeStamp.md">AudioTimeStamp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1073483774093524"><a name="p1073483774093524"></a><a name="p1073483774093524"></a>Defines the audio timestamp, which is a substitute for POSIX <strong id="b2015374507093524"><a name="b2015374507093524"></a><a name="b2015374507093524"></a>timespec</strong>. </p>
</td>
</tr>
<tr id="row144515819093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1827081215093524"><a name="p1827081215093524"></a><a name="p1827081215093524"></a><a href="AudioSubPortCapability.md">AudioSubPortCapability</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19174568093524"><a name="p19174568093524"></a><a name="p19174568093524"></a>Defines the sub-port capability. </p>
</td>
</tr>
<tr id="row1060678656093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p166700594093524"><a name="p166700594093524"></a><a name="p166700594093524"></a><a href="AudioPortCapability.md">AudioPortCapability</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340098876093524"><a name="p340098876093524"></a><a name="p340098876093524"></a>Defines the audio port capability. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table789731458093524"></a>
<table><thead align="left"><tr id="row359722020093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1201203063093524"><a name="p1201203063093524"></a><a name="p1201203063093524"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1821269277093524"><a name="p1821269277093524"></a><a name="p1821269277093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1621040464093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133756191093524"><a name="p2133756191093524"></a><a name="p2133756191093524"></a><a href="Audio.md#ga18675ddb073465fdeac33a897f675d79">AudioHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p738803497093524"><a name="p738803497093524"></a><a name="p738803497093524"></a> typedef void *&nbsp;</p>
<p id="p1529498232093524"><a name="p1529498232093524"></a><a name="p1529498232093524"></a>Defines the audio handle. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table807757090093524"></a>
<table><thead align="left"><tr id="row1384618484093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p58311905093524"><a name="p58311905093524"></a><a name="p58311905093524"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p377300129093524"><a name="p377300129093524"></a><a name="p377300129093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row111687130093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1475198540093524"><a name="p1475198540093524"></a><a name="p1475198540093524"></a><a href="Audio.md#ga68ff7140b15790debbac4bbc62f8e9f8">AudioPortDirection</a> { <a href="Audio.md#gga68ff7140b15790debbac4bbc62f8e9f8af54f110a0f64337d474989fbac06bc22">PORT_OUT</a> = 0x1u, <a href="Audio.md#gga68ff7140b15790debbac4bbc62f8e9f8a154a6db110515b7afde52d3a36d57846">PORT_IN</a> = 0x2u, <a href="Audio.md#gga68ff7140b15790debbac4bbc62f8e9f8a87e14fe9da9c332ba29185b9213d7bbf">PORT_OUT_IN</a> = 0x3u }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1320570935093524"><a name="p1320570935093524"></a><a name="p1320570935093524"></a>Enumerates the audio port type. </p>
</td>
</tr>
<tr id="row1450577459093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1921015196093524"><a name="p1921015196093524"></a><a name="p1921015196093524"></a><a href="Audio.md#gaa7114aeeccf3ac4f5f7e1d880bcfa835">AudioPortPin</a> { &nbsp;&nbsp;<a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835ad2f867652c04c17517db7731af03bf20">PIN_NONE</a> = 0x0u, <a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835ab1070439bab93e06446c21157771dd6f">PIN_OUT_SPEAKER</a> = 0x1u, <a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835a271013721c8840cc2700c19b3ff8d0a6">PIN_OUT_HEADSET</a> = 0x2u, <a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835a411e9037214c75d22c9080505cf9cae6">PIN_OUT_LINEOUT</a> = 0x4u, &nbsp;&nbsp;<a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835ab4aaa2ec71ec77480f60743cd79340b9">PIN_OUT_HDMI</a> = 0x8u, <a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835a336001f5685d9c206b1251714553b485">PIN_IN_MIC</a> = 0x8000001u, <a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835aaeca21ac0a7b249905d1cea5b683f574">PIN_IN_HS_MIC</a> = 0x8000002u, <a href="Audio.md#ggaa7114aeeccf3ac4f5f7e1d880bcfa835a5146add03ff98f06648567bb0e02a477">PIN_IN_LINEIN</a> = 0x8000004u }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773227294093524"><a name="p773227294093524"></a><a name="p773227294093524"></a>Enumerates the pin of an audio adapter. </p>
</td>
</tr>
<tr id="row2020132381093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1056989366093524"><a name="p1056989366093524"></a><a name="p1056989366093524"></a><a href="Audio.md#gaf210d41d152890f3aaf2aaac99bd28d5">AudioCategory</a> { <a href="Audio.md#ggaf210d41d152890f3aaf2aaac99bd28d5a6ac6cfd90dcc34de100c1cecb3df44c3">AUDIO_IN_MEDIA</a> = 0, <a href="Audio.md#ggaf210d41d152890f3aaf2aaac99bd28d5a474576c773934a0df994bad4cf781b41">AUDIO_IN_COMMUNICATION</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021363684093524"><a name="p2021363684093524"></a><a name="p2021363684093524"></a>Enumerates the audio category. </p>
</td>
</tr>
<tr id="row1148790385093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1231297798093524"><a name="p1231297798093524"></a><a name="p1231297798093524"></a><a href="Audio.md#ga98d5d077cca088ddf77314871474fe59">AudioFormat</a> { &nbsp;&nbsp;<a href="Audio.md#gga98d5d077cca088ddf77314871474fe59a321cc2160af35aa86b8ee55f231ef1e6">AUDIO_FORMAT_PCM_8_BIT</a> = 0x1u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59ae188cf87c8f2e6218c74b3b2385068e6">AUDIO_FORMAT_PCM_16_BIT</a> = 0x2u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59a21eb864e2117df577dcd90ad81da3b14">AUDIO_FORMAT_PCM_24_BIT</a> = 0x3u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59adf7a0bf1f3dd15c9c43fac07c0c6ea26">AUDIO_FORMAT_PCM_32_BIT</a> = 0x4u, &nbsp;&nbsp;<a href="Audio.md#gga98d5d077cca088ddf77314871474fe59a5a781e6f8b145066ae7fb2c310804bab">AUDIO_FORMAT_AAC_MAIN</a> = 0x1000001u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59a3d4bc5d534d0452635455ed8d2cade57">AUDIO_FORMAT_AAC_LC</a> = 0x1000002u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59ad4baf87ff9f4684c03483c572052b700">AUDIO_FORMAT_AAC_LD</a> = 0x1000003u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59a4b8d42988fecf03e2bf73c4395501852">AUDIO_FORMAT_AAC_ELD</a> = 0x1000004u, &nbsp;&nbsp;<a href="Audio.md#gga98d5d077cca088ddf77314871474fe59abaddb86f122d3185de9407dbc673bf0e">AUDIO_FORMAT_AAC_HE_V1</a> = 0x1000005u, <a href="Audio.md#gga98d5d077cca088ddf77314871474fe59ab610e0121e0b5076b3f78831e3c237fd">AUDIO_FORMAT_AAC_HE_V2</a> = 0x1000006u }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p622735356093524"><a name="p622735356093524"></a><a name="p622735356093524"></a>Enumerates the audio format. </p>
</td>
</tr>
<tr id="row1728955489093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1184532925093524"><a name="p1184532925093524"></a><a name="p1184532925093524"></a><a href="Audio.md#ga137eb03027d5947ea294b32f5095b83c">AudioChannelMask</a> { <a href="Audio.md#gga137eb03027d5947ea294b32f5095b83ca0419483310bfc5abe46a0c586070ed18">AUDIO_CHANNEL_FRONT_LEFT</a> = 0x1, <a href="Audio.md#gga137eb03027d5947ea294b32f5095b83ca05525a25c5912eda05e9a8786a743a75">AUDIO_CHANNEL_FRONT_RIGHT</a> = 0x2, <a href="Audio.md#gga137eb03027d5947ea294b32f5095b83ca0479e1cd2137cbbad68efae1d2b2c9a9">AUDIO_CHANNEL_MONO</a> = 0x1u, <a href="Audio.md#gga137eb03027d5947ea294b32f5095b83ca70f2212ea5439c13f7fcba3e30b15c1a">AUDIO_CHANNEL_STEREO</a> = 0x3u }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1151122010093524"><a name="p1151122010093524"></a><a name="p1151122010093524"></a>Enumerates the audio channel mask. </p>
</td>
</tr>
<tr id="row222511785093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1026738021093524"><a name="p1026738021093524"></a><a name="p1026738021093524"></a><a href="Audio.md#ga7053fcaa56d1dc47d2fcd83ee131fe4c">AudioSampleRatesMask</a> { &nbsp;&nbsp;<a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4ca046a26906a4df81bfc38c583ba3606e9">AUDIO_SAMPLE_RATE_MASK_8000</a> = 0x1u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4caf1f34aa763f2bf6d5f43178f2d335d10">AUDIO_SAMPLE_RATE_MASK_12000</a> = 0x2u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4ca5f13b000ef455b858506fc90d17e2dd7">AUDIO_SAMPLE_RATE_MASK_11025</a> = 0x4u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4ca3102248493467e00d16c2cf1971635a7">AUDIO_SAMPLE_RATE_MASK_16000</a> = 0x8u, &nbsp;&nbsp;<a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4cae7cfb2244a15cd133373cfa5e96ec82e">AUDIO_SAMPLE_RATE_MASK_22050</a> = 0x10u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4cacce4defc0cf23abfe52d399b4aa68fdf">AUDIO_SAMPLE_RATE_MASK_24000</a> = 0x20u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4ca5594285d8ef3897e9f29a15e0795b814">AUDIO_SAMPLE_RATE_MASK_32000</a> = 0x40u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4ca52345265822f55a62b2e038438daf37e">AUDIO_SAMPLE_RATE_MASK_44100</a> = 0x80u, &nbsp;&nbsp;<a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4caa52c49624fecf6d9f1d075d0d3ad0bbf">AUDIO_SAMPLE_RATE_MASK_48000</a> = 0x100u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4caf111a8b9762ec169361a106ba7efdb0f">AUDIO_SAMPLE_RATE_MASK_64000</a> = 0x200u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4caa9e4deb07b2a7c32e5a19b8c81d9fd0d">AUDIO_SAMPLE_RATE_MASK_96000</a> = 0x400u, <a href="Audio.md#gga7053fcaa56d1dc47d2fcd83ee131fe4ca41f8d22ab95c84d0acb3d0c78679274c">AUDIO_SAMPLE_RATE_MASK_INVALID</a> = 0xFFFFFFFFu }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1253951404093524"><a name="p1253951404093524"></a><a name="p1253951404093524"></a>Enumerates masks of audio sampling rates. </p>
</td>
</tr>
<tr id="row1736883818093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1578455188093524"><a name="p1578455188093524"></a><a name="p1578455188093524"></a><a href="Audio.md#ga186d2d4f9a2ecacb80cd2cce2bd26f0e">AudioPortPassthroughMode</a> { <a href="Audio.md#gga186d2d4f9a2ecacb80cd2cce2bd26f0ea48da60ec7958d35e8884e67cc32cb465">PORT_PASSTHROUGH_LPCM</a> = 0x1, <a href="Audio.md#gga186d2d4f9a2ecacb80cd2cce2bd26f0eaf44936c424fbadafda9e1a12829b291f">PORT_PASSTHROUGH_RAW</a> = 0x2, <a href="Audio.md#gga186d2d4f9a2ecacb80cd2cce2bd26f0eada09d902428d269446b94c2b7e9eb95e">PORT_PASSTHROUGH_HBR2LBR</a> = 0x4, <a href="Audio.md#gga186d2d4f9a2ecacb80cd2cce2bd26f0ea6fd7a77031d807247e159c3deec07e11">PORT_PASSTHROUGH_AUTO</a> = 0x8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727545908093524"><a name="p727545908093524"></a><a name="p727545908093524"></a>Enumerates the passthrough data transmission mode of an audio port. </p>
</td>
</tr>
<tr id="row1048303202093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p767162504093524"><a name="p767162504093524"></a><a name="p767162504093524"></a><a href="Audio.md#ga78aab1fafb9657451804e42b42897123">AudioChannelMode</a> { &nbsp;&nbsp;<a href="Audio.md#gga78aab1fafb9657451804e42b42897123aa97ec21f6627e1dfd4854b5b470cdfba">AUDIO_CHANNEL_NORMAL</a> = 0, <a href="Audio.md#gga78aab1fafb9657451804e42b42897123a47fd61e4531acb6b5cc058ac26af5d51">AUDIO_CHANNEL_BOTH_LEFT</a>, <a href="Audio.md#gga78aab1fafb9657451804e42b42897123a3341b11cad1d47bda2b4a2be60dda023">AUDIO_CHANNEL_BOTH_RIGHT</a>, <a href="Audio.md#gga78aab1fafb9657451804e42b42897123a3f2e41939cc24c51213d8730c32e74e9">AUDIO_CHANNEL_EXCHANGE</a>, &nbsp;&nbsp;<a href="Audio.md#gga78aab1fafb9657451804e42b42897123a2c1537bccd5c2a05d1c515e58ec4481e">AUDIO_CHANNEL_MIX</a>, <a href="Audio.md#gga78aab1fafb9657451804e42b42897123a485c0423ce07fbb7f844a387ed9bb546">AUDIO_CHANNEL_LEFT_MUTE</a>, <a href="Audio.md#gga78aab1fafb9657451804e42b42897123a0878cdf6f3e0d9ae9ae1f61b7f74257e">AUDIO_CHANNEL_RIGHT_MUTE</a>, <a href="Audio.md#gga78aab1fafb9657451804e42b42897123a22540143eb96abf8176e73c19fc0d8e5">AUDIO_CHANNEL_BOTH_MUTE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1721583568093524"><a name="p1721583568093524"></a><a name="p1721583568093524"></a>Enumerates channel modes for audio rendering. </p>
</td>
</tr>
</tbody>
</table>

