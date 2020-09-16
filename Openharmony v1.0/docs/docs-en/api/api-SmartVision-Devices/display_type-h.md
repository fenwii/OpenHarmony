# display\_type.h<a name="EN-US_TOPIC_0000001055678058"></a>

## **Overview**<a name="section158218905093524"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Declares the types used by the display driver functions.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1086743985093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table132642847093524"></a>
<table><thead align="left"><tr id="row1345403566093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p280173333093524"><a name="p280173333093524"></a><a name="p280173333093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1893371893093524"><a name="p1893371893093524"></a><a name="p1893371893093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1277698662093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516789349093524"><a name="p1516789349093524"></a><a name="p1516789349093524"></a><a href="en-us_topic_0000001054479559.md">DisplayInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354676520093524"><a name="p1354676520093524"></a><a name="p1354676520093524"></a>Defines display information.</p>
</td>
</tr>
<tr id="row1822387127093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807423673093524"><a name="p1807423673093524"></a><a name="p1807423673093524"></a><a href="en-us_topic_0000001055518096.md">LayerInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p408293115093524"><a name="p408293115093524"></a><a name="p408293115093524"></a>Defines layer information.</p>
</td>
</tr>
<tr id="row663298043093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2034396994093524"><a name="p2034396994093524"></a><a name="p2034396994093524"></a><a href="en-us_topic_0000001054799607.md">LayerAlpha</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325895464093524"><a name="p1325895464093524"></a><a name="p1325895464093524"></a>Defines alpha operations on a layer.</p>
</td>
</tr>
<tr id="row1844578782093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365178197093524"><a name="p365178197093524"></a><a name="p365178197093524"></a><a href="en-us_topic_0000001054918147.md">BufferHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p966764307093524"><a name="p966764307093524"></a><a name="p966764307093524"></a>Defines the buffer handle type. The virtual address of a handle maps to its physical address.</p>
</td>
</tr>
<tr id="row1322962104093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737586123093524"><a name="p737586123093524"></a><a name="p737586123093524"></a><a href="en-us_topic_0000001054718125.md">GrallocBuffer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184815610093524"><a name="p1184815610093524"></a><a name="p1184815610093524"></a>Defines the memory buffer, including the buffer handle, memory type, memory size, and virtual memory address.</p>
</td>
</tr>
<tr id="row1661457075093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327292073093524"><a name="p1327292073093524"></a><a name="p1327292073093524"></a><a href="en-us_topic_0000001054718119.md">BufferData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p547107777093524"><a name="p547107777093524"></a><a name="p547107777093524"></a>Defines buffer data of a layer, including the virtual and physical memory addresses.</p>
</td>
</tr>
<tr id="row66112663093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703217574093524"><a name="p703217574093524"></a><a name="p703217574093524"></a><a href="en-us_topic_0000001055039524.md">LayerBuffer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743106017093524"><a name="p743106017093524"></a><a name="p743106017093524"></a>Defines the buffer, which is used to store layer data.</p>
</td>
</tr>
<tr id="row640097722093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651793937093524"><a name="p651793937093524"></a><a name="p651793937093524"></a><a href="en-us_topic_0000001055678096.md">IRect</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p509014590093524"><a name="p509014590093524"></a><a name="p509014590093524"></a>Defines the coordinates of the upper left corner of a rectangle as well as its width and height to describe a rectangular area for an image.</p>
</td>
</tr>
<tr id="row537406376093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370926822093524"><a name="p1370926822093524"></a><a name="p1370926822093524"></a><a href="en-us_topic_0000001055518092.md">ISurface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p619847487093524"><a name="p619847487093524"></a><a name="p619847487093524"></a>Stores surface information for hardware acceleration, such as draw image, and bit blit.</p>
</td>
</tr>
<tr id="row1684686740093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716833260093524"><a name="p716833260093524"></a><a name="p716833260093524"></a><a href="en-us_topic_0000001054799603.md">ILine</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p860110191093524"><a name="p860110191093524"></a><a name="p860110191093524"></a>Describes a line to help draw lines in hardware acceleration.</p>
</td>
</tr>
<tr id="row5411310093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p83102892093524"><a name="p83102892093524"></a><a name="p83102892093524"></a><a href="en-us_topic_0000001055039520.md">ICircle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804741139093524"><a name="p804741139093524"></a><a name="p804741139093524"></a>Describes a circle to help draw circles in hardware acceleration.</p>
</td>
</tr>
<tr id="row1925540396093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032043471093524"><a name="p2032043471093524"></a><a name="p2032043471093524"></a><a href="en-us_topic_0000001054479599.md">Rectangle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103092545093524"><a name="p1103092545093524"></a><a name="p1103092545093524"></a>Describes a rectangle to help draw rectangles in hardware acceleration.</p>
</td>
</tr>
<tr id="row1956829770093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p400137640093524"><a name="p400137640093524"></a><a name="p400137640093524"></a><a href="en-us_topic_0000001055678092.md">GfxOpt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2065096856093524"><a name="p2065096856093524"></a><a name="p2065096856093524"></a>Defines hardware acceleration options.</p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1145974478093524"></a>
<table><thead align="left"><tr id="row1439482302093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1304496496093524"><a name="p1304496496093524"></a><a name="p1304496496093524"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1640976958093524"><a name="p1640976958093524"></a><a name="p1640976958093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row8483595093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024282284093524"><a name="p1024282284093524"></a><a name="p1024282284093524"></a><a href="display.md#ga12a925dadef7573cd74d63d06824f9b0">DispErrCode</a> {   <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0a188daac95e787159d50ff9546536035b">DISPLAY_SUCCESS</a> = 0, <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0afdffc20c71fb142c3e7f01323a31d742">DISPLAY_FAILURE</a> = -1, <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0a5bdb0a826a652f51e6c82685ae08ede8">DISPLAY_FD_ERR</a> = -2, <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0a330e09be303bc7056f6115830bbd2370">DISPLAY_PARAM_ERR</a> = -3,   <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0a82fbcdba6c699059bc04b491c92424ac">DISPLAY_NULL_PTR</a> = -4, <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0a950a7bc41e893450315da9e73208f8c2">DISPLAY_NOT_SUPPORT</a> = -5, <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0af186ab511133fa3280c54d2c44358882">DISPLAY_NOMEM</a> = -6, <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0ac11b678fc04745ff4d91f4398b83c427">DISPLAY_SYS_BUSY</a> = -7,   <a href="display.md#gga12a925dadef7573cd74d63d06824f9b0ad133674b9f3b857a12791479aaf58cf8">DISPLAY_NOT_PERM</a> = -8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1608231238093524"><a name="p1608231238093524"></a><a name="p1608231238093524"></a>Enumerates return values of the functions.</p>
</td>
</tr>
<tr id="row618434687093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p81835710093524"><a name="p81835710093524"></a><a name="p81835710093524"></a><a href="display.md#ga56943a0946e5f15e5e58054b8e7a04a4">LayerType</a> { <a href="display.md#gga56943a0946e5f15e5e58054b8e7a04a4a6ef157ea82a5d4c1715b3cddcca38d6f">LAYER_TYPE_GRAPHIC</a>, <a href="display.md#gga56943a0946e5f15e5e58054b8e7a04a4ac33e449941bc0e4d039b4b5bed853a78">LAYER_TYPE_OVERLAY</a>, <a href="display.md#gga56943a0946e5f15e5e58054b8e7a04a4a0aef2c460a206fa00c742219d65be477">LAYER_TYPE_SDIEBAND</a>, <a href="display.md#gga56943a0946e5f15e5e58054b8e7a04a4acd813c5ad9a2be97c85a97d4bdf1cb57">LAYER_TYPE_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p935199480093524"><a name="p935199480093524"></a><a name="p935199480093524"></a>Enumerates layer types.</p>
</td>
</tr>
<tr id="row422700252093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p604669806093524"><a name="p604669806093524"></a><a name="p604669806093524"></a><a href="display.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> {  <a href="display.md#gga60883d4958a60b91661e97027a85072aa5fae320872be3ffdda0d371cec048ec6">PIXEL_FMT_RGB_565</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa4c16147153b63d7ba71b257111afdd62">PIXEL_FMT_RGBA_5658</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aaa479ac0d983fde9b4f7f0e1a3b3e230f">PIXEL_FMT_RGBX_4444</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aacbb91256e8c45a51410a9f6caae2d04c">PIXEL_FMT_RGBA_4444</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa7d18a83da06902c104208031ed487942">PIXEL_FMT_RGB_444</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa85e5dd1a0e547c0031baffd02abb31a0">PIXEL_FMT_RGBX_5551</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aadc1387526a271d8c6db7729de06474b1">PIXEL_FMT_RGBA_5551</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa720a429fa57133f6e27ef8c8fa1c404a">PIXEL_FMT_RGB_555</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa24a7181b7fb4019e7c19739bd9b65ff0">PIXEL_FMT_RGBX_8888</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa90b462672221691ed66cacb07dd2e05f">PIXEL_FMT_RGBA_8888</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aa7ff77397bf2cf52b4614a46264f8ce01">PIXEL_FMT_RGB_888</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aaec581b908c291e2bd0155e25169f9629">PIXEL_FMT_BGR_565</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa6b5a7b35e00fc25146de0c9bf88b0230">PIXEL_FMT_BGRX_4444</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa2f3d4ada099b2e8d84ec4501fbc8bed9">PIXEL_FMT_BGRA_4444</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aaaf1a20dc0a597258cfe6aca806a8e0de">PIXEL_FMT_BGRX_5551</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa2319d4a75dae0b56776fa63d525e308b">PIXEL_FMT_BGRA_5551</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa1b19279f89c8cfb60e7d77ce23cd5f43">PIXEL_FMT_BGRX_8888</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aaeb31c670120a1fbc96a0e0887997fe16">PIXEL_FMT_BGRA_8888</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aac73c2a84907a53ed95a329007b5c8992">PIXEL_FMT_YUV_422_I</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aabdf1224848278508479ce97f637dd711">PIXEL_FMT_YCBCR_422_SP</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa8bf97d66e26b3aad7c83dfa70e2bc451">PIXEL_FMT_YCRCB_422_SP</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa0d1db50eb492f9073abdd2d662c56396">PIXEL_FMT_YCBCR_420_SP</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aa1fa43c8a197d5c974a35b8bf02ab386e">PIXEL_FMT_YCRCB_420_SP</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aaa2fe085e63428ea76e1d975175001dc6">PIXEL_FMT_YCBCR_422_P</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aab04eb6e1d940e42f3b4cc20c0a44c4ee">PIXEL_FMT_YCRCB_422_P</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa3d80e785bed28e2b3f5c7df563500962">PIXEL_FMT_YCBCR_420_P</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aa3dc5a0a5ad2f21218b446c477277210a">PIXEL_FMT_YCRCB_420_P</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa3980def5b133584bdb2982a71f07798e">PIXEL_FMT_YUYV_422_PKG</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aadfd69bd5b421aad5bdd39d5f33317197">PIXEL_FMT_UYVY_422_PKG</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aaf851031c336e8d9f57c940c5f52381f4">PIXEL_FMT_YVYU_422_PKG</a>,   <a href="display.md#gga60883d4958a60b91661e97027a85072aa317a761939335025379d382074a1541c">PIXEL_FMT_VYUY_422_PKG</a>, <a href="display.md#gga60883d4958a60b91661e97027a85072aa07086bb3356c9c88959eee00c0982684">PIXEL_FMT_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p357846450093524"><a name="p357846450093524"></a><a name="p357846450093524"></a>Enumerates pixel formats.</p>
</td>
</tr>
<tr id="row501737170093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p690212569093524"><a name="p690212569093524"></a><a name="p690212569093524"></a><a href="display.md#gaa65f3b21a9a92ff022e435a7304126d2">TransformType</a> {   <a href="display.md#ggaa65f3b21a9a92ff022e435a7304126d2a68e349e9d45a8eba440e2a7a3ba31ec9">ROTATE_NONE</a> = 0, <a href="display.md#ggaa65f3b21a9a92ff022e435a7304126d2a685062467b0c1a3164556335b467c886">ROTATE_90</a>, <a href="display.md#ggaa65f3b21a9a92ff022e435a7304126d2a186263164422bb8f0eb5f7b7d195a3d1">ROTATE_180</a>, <a href="display.md#ggaa65f3b21a9a92ff022e435a7304126d2a554e734d2a23790b248c5ce39816c18f">ROTATE_270</a>,   <a href="display.md#ggaa65f3b21a9a92ff022e435a7304126d2a9b6ff871536aeef2a8e3ce4a753988ed">ROTATE_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061736382093524"><a name="p1061736382093524"></a><a name="p1061736382093524"></a>Enumerates transform types of images.</p>
</td>
</tr>
<tr id="row556432532093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290868231093524"><a name="p1290868231093524"></a><a name="p1290868231093524"></a><a href="display.md#gabd31f838aefffa46191d0d7dc36a96b2">MemType</a> { <a href="display.md#ggabd31f838aefffa46191d0d7dc36a96b2ad3379d0af95e2e9dcbcfdb016d1cf9b3">NORMAL_MEM</a> = 0, <a href="display.md#ggabd31f838aefffa46191d0d7dc36a96b2a2ad949ccc994ad1718cb54929d762700">CACHE_MEM</a>, <a href="display.md#ggabd31f838aefffa46191d0d7dc36a96b2a79f98876507c94448fed5f6f33683fb7">SHM_MEM</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309469932093524"><a name="p1309469932093524"></a><a name="p1309469932093524"></a>Enumerates memory types.</p>
</td>
</tr>
<tr id="row750069588093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p233405333093524"><a name="p233405333093524"></a><a name="p233405333093524"></a><a href="display.md#gaab1839ed4aab1030dfda801a51e68817">BlendType</a> {   <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817ae410edb34509ca21425fe5872bbc7e2f">BLEND_NONE</a> = 0, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a6330cee419fbdafc0b25f0aa068814e5">BLEND_CLEAR</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817af01da0c255cdbf67d0774a67c2d221b5">BLEND_SRC</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817ad4c0cd02aa4b5f4849e2b29a26481dde">BLEND_SRCOVER</a>,   <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a21f03e8d04a58ed0684b39eb84bdb89f">BLEND_DSTOVER</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a74e681f6c9027bb2cf0bda3b72d2dd9e">BLEND_SRCIN</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a19f528828d75c34e18375219f113d9bb">BLEND_DSTIN</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a404e05a118462520e878c23f89808199">BLEND_SRCOUT</a>,   <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817ac0dc902b4928413d367376e4c842d909">BLEND_DSTOUT</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817ada473c7e3bf2b1102349489416aefefc">BLEND_SRCATOP</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a0129b4506a06b1a6df297bcf685f5f89">BLEND_DSTATOP</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817adbdb329830e5b4d9fa2b17d5d6d7894f">BLEND_ADD</a>,   <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a167c3b256e051244066d8e53cdd5529d">BLEND_XOR</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a4686a5f30c73982d625a05db021e9b15">BLEND_DST</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817ae549aa3794365df8965a2c3853c8da99">BLEND_AKS</a>, <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817a3cc39f12fa8bceba626a33c2d82a8bf7">BLEND_AKD</a>,   <a href="display.md#ggaab1839ed4aab1030dfda801a51e68817ad0650812ac2aa9eee228f48ac514b44a">BLEND_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p57286950093524"><a name="p57286950093524"></a><a name="p57286950093524"></a>Enumerates image blending types.</p>
</td>
</tr>
<tr id="row2077618398093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p573446427093524"><a name="p573446427093524"></a><a name="p573446427093524"></a><a href="display.md#ga24265f7618fbdba53d3da4806d3097c4">RopType</a> {   <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a6358a786ec3b81000a07b343424cee0d">ROP_BLACK</a> = 0, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a96c89f7b89a9048d355b4dc467224f4c">ROP_NOTMERGEPEN</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a54d054ea6920cb88f374f70e8d41f934">ROP_MASKNOTPEN</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4af4a5d5dc0f15249001cff7ef32fadef1">ROP_NOTCOPYPEN</a>,   <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4ad777eea18ba9f4e071b00aa060db00e3">ROP_MASKPENNOT</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4afa63c8e2a6a39d50954cb6316576b4e9">ROP_NOT</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a79433776e85bb80ad0306ced0b82947c">ROP_XORPEN</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4ad6c4d2458a9caaa079a3e5907d636e8a">ROP_NOTMASKPEN</a>,   <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a2a069e2105c5b8d4dac5d174c76eb9d4">ROP_MASKPEN</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a33c37c5ce718e876f43141dc5a028375">ROP_NOTXORPEN</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a2acacab882af44bba09878bd58e18695">ROP_NOP</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4afaea3c47612082914332b78ca8c331b3">ROP_MERGENOTPEN</a>,   <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a91bae697f9dea25ac4d7be011958a45d">ROP_COPYPE</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a3580b77320e4829da046b8739c61d6b8">ROP_MERGEPENNOT</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a8195ac0d37e0d69b2cd71dd7362d3fd3">ROP_MERGEPEN</a>, <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4a533a614b27da8a81b67ada085b018618">ROP_WHITE</a>,   <a href="display.md#gga24265f7618fbdba53d3da4806d3097c4aa858b07e214a7f62625e24776806c74b">ROP_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2067377724093524"><a name="p2067377724093524"></a><a name="p2067377724093524"></a>Enumerates ROP types supported by hardware acceleration.</p>
</td>
</tr>
<tr id="row255719961093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451856855093524"><a name="p451856855093524"></a><a name="p451856855093524"></a><a href="display.md#ga4fe6fb05c7ba0048b1739d88f4d4878e">ColorKey</a> { <a href="display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea629b31de258db2ce01cb757b85bd5273">CKEY_NONE</a> = 0, <a href="display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea5e3271e73dce39d0806ff8e9cba011bc">CKEY_SRC</a>, <a href="display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea6921c2c202aa69293467baa6c33fae05">CKEY_DST</a>, <a href="display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea32cedc8986de2c290bf2ec193d88cabf">CKEY_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p421124903093524"><a name="p421124903093524"></a><a name="p421124903093524"></a>Enumerates color key types supported by hardware acceleration.</p>
</td>
</tr>
<tr id="row2094367560093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p782224341093524"><a name="p782224341093524"></a><a name="p782224341093524"></a><a href="display.md#ga08d32376574b541d162d8534adb78fd0">MirrorType</a> { <a href="display.md#gga08d32376574b541d162d8534adb78fd0a5ad82fcc8af04f92571e185b61eeb309">MIRROR_NONE</a> = 0, <a href="display.md#gga08d32376574b541d162d8534adb78fd0ae35099d9fd28c2974661bcce36a9ea5c">MIRROR_LR</a>, <a href="display.md#gga08d32376574b541d162d8534adb78fd0afd82e59546a645fd29bc779c50bfa733">MIRROR_TB</a>, <a href="display.md#gga08d32376574b541d162d8534adb78fd0ad9e357a2c2f7dc0e3ca5a351ec457410">MIRROR_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457254462093524"><a name="p457254462093524"></a><a name="p457254462093524"></a>Enumerates mirror types supported by hardware acceleration.</p>
</td>
</tr>
<tr id="row963611682093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1593368467093524"><a name="p1593368467093524"></a><a name="p1593368467093524"></a><a href="display.md#gab0845c0c8d309ee865c78b095b00e671">Connection</a> { <a href="display.md#ggab0845c0c8d309ee865c78b095b00e671aef2863a469df3ea6871d640e3669a2f2">INVALID</a> = 0, <a href="display.md#ggab0845c0c8d309ee865c78b095b00e671a7a691a2430ec26878897b5fbc9c22a4c">CONNECTED</a>, <a href="display.md#ggab0845c0c8d309ee865c78b095b00e671acdaad1112073e3e2ea032424c38c34e1">DISCONNECTED</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1570805610093524"><a name="p1570805610093524"></a><a name="p1570805610093524"></a>Enumerates connection types of hot plugging.</p>
</td>
</tr>
</tbody>
</table>

