# Display<a name="ZH-CN_TOPIC_0000001055198078"></a>

## **Overview**<a name="section1431919732093521"></a>

Defines driver functions of the display module.

The driver functions provided for the GUI include the layer, hardware acceleration, memory, and callback functions.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1025913459093521"></a>

## Files<a name="files"></a>

<a name="table2023431350093521"></a>
<table><thead align="left"><tr id="row955844466093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2089955670093521"><a name="p2089955670093521"></a><a name="p2089955670093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p570444029093521"><a name="p570444029093521"></a><a name="p570444029093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row756707900093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1824672386093521"><a name="p1824672386093521"></a><a name="p1824672386093521"></a><a href="zh-cn_topic_0000001054598125.md">display_gfx.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809478016093521"><a name="p1809478016093521"></a><a name="p1809478016093521"></a>Declares the driver functions for implementing hardware acceleration.</p>
</td>
</tr>
<tr id="row1027502032093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p85809673093521"><a name="p85809673093521"></a><a name="p85809673093521"></a><a href="zh-cn_topic_0000001054918119.md">display_gralloc.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p32252338093521"><a name="p32252338093521"></a><a name="p32252338093521"></a>Declares the driver functions for memory.</p>
</td>
</tr>
<tr id="row975585443093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1139520794093521"><a name="p1139520794093521"></a><a name="p1139520794093521"></a><a href="zh-cn_topic_0000001054718091.md">display_layer.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447902809093521"><a name="p447902809093521"></a><a name="p447902809093521"></a>Declares the driver functions for implementing layer operations.</p>
</td>
</tr>
<tr id="row1231887048093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047579084093521"><a name="p1047579084093521"></a><a name="p1047579084093521"></a><a href="display_type-h.md">display_type.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915785637093521"><a name="p915785637093521"></a><a name="p915785637093521"></a>Declares the types used by the display driver functions.</p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1549153936093521"></a>
<table><thead align="left"><tr id="row929931317093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1354221206093521"><a name="p1354221206093521"></a><a name="p1354221206093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1833114955093521"><a name="p1833114955093521"></a><a name="p1833114955093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1786511466093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1808931105093521"><a name="p1808931105093521"></a><a name="p1808931105093521"></a><a href="zh-cn_topic_0000001054598159.md">GfxFuncs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p63526767093521"><a name="p63526767093521"></a><a name="p63526767093521"></a>Defines pointers to the hardware acceleration driver functions.</p>
</td>
</tr>
<tr id="row546089763093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1530808826093521"><a name="p1530808826093521"></a><a name="p1530808826093521"></a><a href="zh-cn_topic_0000001054918153.md">GrallocFuncs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755211822093521"><a name="p755211822093521"></a><a name="p755211822093521"></a>Defines pointers to the memory driver functions.</p>
</td>
</tr>
<tr id="row1796924663093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p90949697093521"><a name="p90949697093521"></a><a name="p90949697093521"></a><a href="zh-cn_topic_0000001055678100.md">LayerFuncs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1230903373093521"><a name="p1230903373093521"></a><a name="p1230903373093521"></a>Defines pointers to the layer driver functions.</p>
</td>
</tr>
<tr id="row2117670631093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844726208093521"><a name="p844726208093521"></a><a name="p844726208093521"></a><a href="zh-cn_topic_0000001054479559.md">DisplayInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p849564803093521"><a name="p849564803093521"></a><a name="p849564803093521"></a>Defines display information.</p>
</td>
</tr>
<tr id="row1098666665093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1319323606093521"><a name="p1319323606093521"></a><a name="p1319323606093521"></a><a href="zh-cn_topic_0000001055518096.md">LayerInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452801190093521"><a name="p1452801190093521"></a><a name="p1452801190093521"></a>Defines layer information.</p>
</td>
</tr>
<tr id="row571697093093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024874822093521"><a name="p1024874822093521"></a><a name="p1024874822093521"></a><a href="zh-cn_topic_0000001054799607.md">LayerAlpha</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197784200093521"><a name="p197784200093521"></a><a name="p197784200093521"></a>Defines alpha operations on a layer.</p>
</td>
</tr>
<tr id="row299172642093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p54112901093521"><a name="p54112901093521"></a><a name="p54112901093521"></a><a href="zh-cn_topic_0000001054918147.md">BufferHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034255886093521"><a name="p2034255886093521"></a><a name="p2034255886093521"></a>Defines the buffer handle type. The virtual address of a handle maps to its physical address.</p>
</td>
</tr>
<tr id="row1854953935093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p967530821093521"><a name="p967530821093521"></a><a name="p967530821093521"></a><a href="zh-cn_topic_0000001054718125.md">GrallocBuffer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2104061548093521"><a name="p2104061548093521"></a><a name="p2104061548093521"></a>Defines the memory buffer, including the buffer handle, memory type, memory size, and virtual memory address.</p>
</td>
</tr>
<tr id="row48766651093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1904660657093521"><a name="p1904660657093521"></a><a name="p1904660657093521"></a><a href="zh-cn_topic_0000001054718119.md">BufferData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1218846815093521"><a name="p1218846815093521"></a><a name="p1218846815093521"></a>Defines buffer data of a layer, including the virtual and physical memory addresses.</p>
</td>
</tr>
<tr id="row1958882536093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p296995098093521"><a name="p296995098093521"></a><a name="p296995098093521"></a><a href="zh-cn_topic_0000001055039524.md">LayerBuffer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1256330711093521"><a name="p1256330711093521"></a><a name="p1256330711093521"></a>Defines the buffer, which is used to store layer data.</p>
</td>
</tr>
<tr id="row699411555093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28930531093521"><a name="p28930531093521"></a><a name="p28930531093521"></a><a href="zh-cn_topic_0000001055678096.md">IRect</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517027295093521"><a name="p517027295093521"></a><a name="p517027295093521"></a>Defines the coordinates of the upper left corner of a rectangle as well as its width and height to describe a rectangular area for an image.</p>
</td>
</tr>
<tr id="row1765568975093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1103138591093521"><a name="p1103138591093521"></a><a name="p1103138591093521"></a><a href="zh-cn_topic_0000001055518092.md">ISurface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p680129650093521"><a name="p680129650093521"></a><a name="p680129650093521"></a>Stores surface information for hardware acceleration, such as draw image, and bit blit.</p>
</td>
</tr>
<tr id="row1741728775093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1276128418093521"><a name="p1276128418093521"></a><a name="p1276128418093521"></a><a href="zh-cn_topic_0000001054799603.md">ILine</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p730341608093521"><a name="p730341608093521"></a><a name="p730341608093521"></a>Describes a line to help draw lines in hardware acceleration.</p>
</td>
</tr>
<tr id="row1481207607093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1465181253093521"><a name="p1465181253093521"></a><a name="p1465181253093521"></a><a href="zh-cn_topic_0000001055039520.md">ICircle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733211642093521"><a name="p733211642093521"></a><a name="p733211642093521"></a>Describes a circle to help draw circles in hardware acceleration.</p>
</td>
</tr>
<tr id="row668896437093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1653789217093521"><a name="p1653789217093521"></a><a name="p1653789217093521"></a><a href="zh-cn_topic_0000001054479599.md">Rectangle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1612395323093521"><a name="p1612395323093521"></a><a name="p1612395323093521"></a>Describes a rectangle to help draw rectangles in hardware acceleration.</p>
</td>
</tr>
<tr id="row2010763269093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1035934195093521"><a name="p1035934195093521"></a><a name="p1035934195093521"></a><a href="zh-cn_topic_0000001055678092.md">GfxOpt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p640523352093521"><a name="p640523352093521"></a><a name="p640523352093521"></a>Defines hardware acceleration options.</p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table61743123093521"></a>
<table><thead align="left"><tr id="row1041824982093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p891893378093521"><a name="p891893378093521"></a><a name="p891893378093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p373000548093521"><a name="p373000548093521"></a><a name="p373000548093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row782037317093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1606902736093521"><a name="p1606902736093521"></a><a name="p1606902736093521"></a><a href="Display.md#ga12a925dadef7573cd74d63d06824f9b0">DispErrCode</a> {   <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0a188daac95e787159d50ff9546536035b">DISPLAY_SUCCESS</a> = 0, <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0afdffc20c71fb142c3e7f01323a31d742">DISPLAY_FAILURE</a> = -1, <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0a5bdb0a826a652f51e6c82685ae08ede8">DISPLAY_FD_ERR</a> = -2, <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0a330e09be303bc7056f6115830bbd2370">DISPLAY_PARAM_ERR</a> = -3,   <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0a82fbcdba6c699059bc04b491c92424ac">DISPLAY_NULL_PTR</a> = -4, <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0a950a7bc41e893450315da9e73208f8c2">DISPLAY_NOT_SUPPORT</a> = -5, <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0af186ab511133fa3280c54d2c44358882">DISPLAY_NOMEM</a> = -6, <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0ac11b678fc04745ff4d91f4398b83c427">DISPLAY_SYS_BUSY</a> = -7,   <a href="Display.md#gga12a925dadef7573cd74d63d06824f9b0ad133674b9f3b857a12791479aaf58cf8">DISPLAY_NOT_PERM</a> = -8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p969777344093521"><a name="p969777344093521"></a><a name="p969777344093521"></a>Enumerates return values of the functions.</p>
</td>
</tr>
<tr id="row1445288755093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794552528093521"><a name="p1794552528093521"></a><a name="p1794552528093521"></a><a href="Display.md#ga56943a0946e5f15e5e58054b8e7a04a4">LayerType</a> { <a href="Display.md#gga56943a0946e5f15e5e58054b8e7a04a4a6ef157ea82a5d4c1715b3cddcca38d6f">LAYER_TYPE_GRAPHIC</a>, <a href="Display.md#gga56943a0946e5f15e5e58054b8e7a04a4ac33e449941bc0e4d039b4b5bed853a78">LAYER_TYPE_OVERLAY</a>, <a href="Display.md#gga56943a0946e5f15e5e58054b8e7a04a4a0aef2c460a206fa00c742219d65be477">LAYER_TYPE_SDIEBAND</a>, <a href="Display.md#gga56943a0946e5f15e5e58054b8e7a04a4acd813c5ad9a2be97c85a97d4bdf1cb57">LAYER_TYPE_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p250675587093521"><a name="p250675587093521"></a><a name="p250675587093521"></a>Enumerates layer types.</p>
</td>
</tr>
<tr id="row302050092093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1634814454093521"><a name="p1634814454093521"></a><a name="p1634814454093521"></a><a href="Display.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> { <a href="Display.md#gga60883d4958a60b91661e97027a85072aa5fae320872be3ffdda0d371cec048ec6">PIXEL_FMT_RGB_565</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa4c16147153b63d7ba71b257111afdd62">PIXEL_FMT_RGBA_5658</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aaa479ac0d983fde9b4f7f0e1a3b3e230f">PIXEL_FMT_RGBX_4444</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aacbb91256e8c45a51410a9f6caae2d04c">PIXEL_FMT_RGBA_4444</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa7d18a83da06902c104208031ed487942">PIXEL_FMT_RGB_444</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa85e5dd1a0e547c0031baffd02abb31a0">PIXEL_FMT_RGBX_5551</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aadc1387526a271d8c6db7729de06474b1">PIXEL_FMT_RGBA_5551</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa720a429fa57133f6e27ef8c8fa1c404a">PIXEL_FMT_RGB_555</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa24a7181b7fb4019e7c19739bd9b65ff0">PIXEL_FMT_RGBX_8888</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa90b462672221691ed66cacb07dd2e05f">PIXEL_FMT_RGBA_8888</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aa7ff77397bf2cf52b4614a46264f8ce01">PIXEL_FMT_RGB_888</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aaec581b908c291e2bd0155e25169f9629">PIXEL_FMT_BGR_565</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa6b5a7b35e00fc25146de0c9bf88b0230">PIXEL_FMT_BGRX_4444</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa2f3d4ada099b2e8d84ec4501fbc8bed9">PIXEL_FMT_BGRA_4444</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aaaf1a20dc0a597258cfe6aca806a8e0de">PIXEL_FMT_BGRX_5551</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa2319d4a75dae0b56776fa63d525e308b">PIXEL_FMT_BGRA_5551</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa1b19279f89c8cfb60e7d77ce23cd5f43">PIXEL_FMT_BGRX_8888</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aaeb31c670120a1fbc96a0e0887997fe16">PIXEL_FMT_BGRA_8888</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aac73c2a84907a53ed95a329007b5c8992">PIXEL_FMT_YUV_422_I</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aabdf1224848278508479ce97f637dd711">PIXEL_FMT_YCBCR_422_SP</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa8bf97d66e26b3aad7c83dfa70e2bc451">PIXEL_FMT_YCRCB_422_SP</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa0d1db50eb492f9073abdd2d662c56396">PIXEL_FMT_YCBCR_420_SP</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aa1fa43c8a197d5c974a35b8bf02ab386e">PIXEL_FMT_YCRCB_420_SP</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aaa2fe085e63428ea76e1d975175001dc6">PIXEL_FMT_YCBCR_422_P</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aab04eb6e1d940e42f3b4cc20c0a44c4ee">PIXEL_FMT_YCRCB_422_P</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa3d80e785bed28e2b3f5c7df563500962">PIXEL_FMT_YCBCR_420_P</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aa3dc5a0a5ad2f21218b446c477277210a">PIXEL_FMT_YCRCB_420_P</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa3980def5b133584bdb2982a71f07798e">PIXEL_FMT_YUYV_422_PKG</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aadfd69bd5b421aad5bdd39d5f33317197">PIXEL_FMT_UYVY_422_PKG</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aaf851031c336e8d9f57c940c5f52381f4">PIXEL_FMT_YVYU_422_PKG</a>,   <a href="Display.md#gga60883d4958a60b91661e97027a85072aa317a761939335025379d382074a1541c">PIXEL_FMT_VYUY_422_PKG</a>, <a href="Display.md#gga60883d4958a60b91661e97027a85072aa07086bb3356c9c88959eee00c0982684">PIXEL_FMT_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1387620422093521"><a name="p1387620422093521"></a><a name="p1387620422093521"></a>Enumerates pixel formats.</p>
</td>
</tr>
<tr id="row1666639226093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463626027093521"><a name="p463626027093521"></a><a name="p463626027093521"></a><a href="Display.md#gaa65f3b21a9a92ff022e435a7304126d2">TransformType</a> {   <a href="Display.md#ggaa65f3b21a9a92ff022e435a7304126d2a68e349e9d45a8eba440e2a7a3ba31ec9">ROTATE_NONE</a> = 0, <a href="Display.md#ggaa65f3b21a9a92ff022e435a7304126d2a685062467b0c1a3164556335b467c886">ROTATE_90</a>, <a href="Display.md#ggaa65f3b21a9a92ff022e435a7304126d2a186263164422bb8f0eb5f7b7d195a3d1">ROTATE_180</a>, <a href="Display.md#ggaa65f3b21a9a92ff022e435a7304126d2a554e734d2a23790b248c5ce39816c18f">ROTATE_270</a>,   <a href="Display.md#ggaa65f3b21a9a92ff022e435a7304126d2a9b6ff871536aeef2a8e3ce4a753988ed">ROTATE_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376951954093521"><a name="p376951954093521"></a><a name="p376951954093521"></a>Enumerates transform types of images.</p>
</td>
</tr>
<tr id="row320682056093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p162112040093521"><a name="p162112040093521"></a><a name="p162112040093521"></a><a href="Display.md#gabd31f838aefffa46191d0d7dc36a96b2">MemType</a> { <a href="Display.md#ggabd31f838aefffa46191d0d7dc36a96b2ad3379d0af95e2e9dcbcfdb016d1cf9b3">NORMAL_MEM</a> = 0, <a href="Display.md#ggabd31f838aefffa46191d0d7dc36a96b2a2ad949ccc994ad1718cb54929d762700">CACHE_MEM</a>, <a href="Display.md#ggabd31f838aefffa46191d0d7dc36a96b2a79f98876507c94448fed5f6f33683fb7">SHM_MEM</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115368490093521"><a name="p115368490093521"></a><a name="p115368490093521"></a>Enumerates memory types.</p>
</td>
</tr>
<tr id="row1539228976093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1045964137093521"><a name="p1045964137093521"></a><a name="p1045964137093521"></a><a href="Display.md#gaab1839ed4aab1030dfda801a51e68817">BlendType</a> {   <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817ae410edb34509ca21425fe5872bbc7e2f">BLEND_NONE</a> = 0, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a6330cee419fbdafc0b25f0aa068814e5">BLEND_CLEAR</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817af01da0c255cdbf67d0774a67c2d221b5">BLEND_SRC</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817ad4c0cd02aa4b5f4849e2b29a26481dde">BLEND_SRCOVER</a>,   <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a21f03e8d04a58ed0684b39eb84bdb89f">BLEND_DSTOVER</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a74e681f6c9027bb2cf0bda3b72d2dd9e">BLEND_SRCIN</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a19f528828d75c34e18375219f113d9bb">BLEND_DSTIN</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a404e05a118462520e878c23f89808199">BLEND_SRCOUT</a>,   <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817ac0dc902b4928413d367376e4c842d909">BLEND_DSTOUT</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817ada473c7e3bf2b1102349489416aefefc">BLEND_SRCATOP</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a0129b4506a06b1a6df297bcf685f5f89">BLEND_DSTATOP</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817adbdb329830e5b4d9fa2b17d5d6d7894f">BLEND_ADD</a>,   <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a167c3b256e051244066d8e53cdd5529d">BLEND_XOR</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a4686a5f30c73982d625a05db021e9b15">BLEND_DST</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817ae549aa3794365df8965a2c3853c8da99">BLEND_AKS</a>, <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817a3cc39f12fa8bceba626a33c2d82a8bf7">BLEND_AKD</a>,   <a href="Display.md#ggaab1839ed4aab1030dfda801a51e68817ad0650812ac2aa9eee228f48ac514b44a">BLEND_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650411839093521"><a name="p1650411839093521"></a><a name="p1650411839093521"></a>Enumerates image blending types.</p>
</td>
</tr>
<tr id="row1375220379093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p68015518093521"><a name="p68015518093521"></a><a name="p68015518093521"></a><a href="Display.md#ga24265f7618fbdba53d3da4806d3097c4">RopType</a> {   <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a6358a786ec3b81000a07b343424cee0d">ROP_BLACK</a> = 0, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a96c89f7b89a9048d355b4dc467224f4c">ROP_NOTMERGEPEN</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a54d054ea6920cb88f374f70e8d41f934">ROP_MASKNOTPEN</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4af4a5d5dc0f15249001cff7ef32fadef1">ROP_NOTCOPYPEN</a>,   <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4ad777eea18ba9f4e071b00aa060db00e3">ROP_MASKPENNOT</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4afa63c8e2a6a39d50954cb6316576b4e9">ROP_NOT</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a79433776e85bb80ad0306ced0b82947c">ROP_XORPEN</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4ad6c4d2458a9caaa079a3e5907d636e8a">ROP_NOTMASKPEN</a>,   <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a2a069e2105c5b8d4dac5d174c76eb9d4">ROP_MASKPEN</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a33c37c5ce718e876f43141dc5a028375">ROP_NOTXORPEN</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a2acacab882af44bba09878bd58e18695">ROP_NOP</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4afaea3c47612082914332b78ca8c331b3">ROP_MERGENOTPEN</a>,   <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a91bae697f9dea25ac4d7be011958a45d">ROP_COPYPE</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a3580b77320e4829da046b8739c61d6b8">ROP_MERGEPENNOT</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a8195ac0d37e0d69b2cd71dd7362d3fd3">ROP_MERGEPEN</a>, <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4a533a614b27da8a81b67ada085b018618">ROP_WHITE</a>,   <a href="Display.md#gga24265f7618fbdba53d3da4806d3097c4aa858b07e214a7f62625e24776806c74b">ROP_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1151898539093521"><a name="p1151898539093521"></a><a name="p1151898539093521"></a>Enumerates ROP types supported by hardware acceleration.</p>
</td>
</tr>
<tr id="row2120465487093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1624263386093521"><a name="p1624263386093521"></a><a name="p1624263386093521"></a><a href="Display.md#ga4fe6fb05c7ba0048b1739d88f4d4878e">ColorKey</a> { <a href="Display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea629b31de258db2ce01cb757b85bd5273">CKEY_NONE</a> = 0, <a href="Display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea5e3271e73dce39d0806ff8e9cba011bc">CKEY_SRC</a>, <a href="Display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea6921c2c202aa69293467baa6c33fae05">CKEY_DST</a>, <a href="Display.md#gga4fe6fb05c7ba0048b1739d88f4d4878ea32cedc8986de2c290bf2ec193d88cabf">CKEY_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p473177749093521"><a name="p473177749093521"></a><a name="p473177749093521"></a>Enumerates color key types supported by hardware acceleration.</p>
</td>
</tr>
<tr id="row1102466253093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p117863341093521"><a name="p117863341093521"></a><a name="p117863341093521"></a><a href="Display.md#ga08d32376574b541d162d8534adb78fd0">MirrorType</a> { <a href="Display.md#gga08d32376574b541d162d8534adb78fd0a5ad82fcc8af04f92571e185b61eeb309">MIRROR_NONE</a> = 0, <a href="Display.md#gga08d32376574b541d162d8534adb78fd0ae35099d9fd28c2974661bcce36a9ea5c">MIRROR_LR</a>, <a href="Display.md#gga08d32376574b541d162d8534adb78fd0afd82e59546a645fd29bc779c50bfa733">MIRROR_TB</a>, <a href="Display.md#gga08d32376574b541d162d8534adb78fd0ad9e357a2c2f7dc0e3ca5a351ec457410">MIRROR_BUTT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238859876093521"><a name="p1238859876093521"></a><a name="p1238859876093521"></a>Enumerates mirror types supported by hardware acceleration.</p>
</td>
</tr>
<tr id="row1589569661093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1192957968093521"><a name="p1192957968093521"></a><a name="p1192957968093521"></a><a href="Display.md#gab0845c0c8d309ee865c78b095b00e671">Connection</a> { <a href="Display.md#ggab0845c0c8d309ee865c78b095b00e671aef2863a469df3ea6871d640e3669a2f2">INVALID</a> = 0, <a href="Display.md#ggab0845c0c8d309ee865c78b095b00e671a7a691a2430ec26878897b5fbc9c22a4c">CONNECTED</a>, <a href="Display.md#ggab0845c0c8d309ee865c78b095b00e671acdaad1112073e3e2ea032424c38c34e1">DISCONNECTED</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163936672093521"><a name="p1163936672093521"></a><a name="p1163936672093521"></a>Enumerates connection types of hot plugging.</p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1681842927093521"></a>
<table><thead align="left"><tr id="row1721505925093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1938187314093521"><a name="p1938187314093521"></a><a name="p1938187314093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1483881552093521"><a name="p1483881552093521"></a><a name="p1483881552093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1838911367093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390115196093521"><a name="p390115196093521"></a><a name="p390115196093521"></a><a href="Display.md#ga251580eb0614b601ef2c901c722a59d3">GfxInitialize</a> (<a href="zh-cn_topic_0000001054598159.md">GfxFuncs</a> **funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699209212093521"><a name="p699209212093521"></a><a name="p699209212093521"></a>int32_t</p>
<p id="p879629297093521"><a name="p879629297093521"></a><a name="p879629297093521"></a>Initializes the hardware acceleration module to obtain the pointer to functions for hardware acceleration operations.</p>
</td>
</tr>
<tr id="row342699761093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079883041093521"><a name="p2079883041093521"></a><a name="p2079883041093521"></a><a href="Display.md#ga32595139adb26cfaacf709661b29b347">GfxUninitialize</a> (<a href="zh-cn_topic_0000001054598159.md">GfxFuncs</a> *funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2041178159093521"><a name="p2041178159093521"></a><a name="p2041178159093521"></a>int32_t</p>
<p id="p1582723227093521"><a name="p1582723227093521"></a><a name="p1582723227093521"></a>Deinitializes the hardware acceleration module to release the memory allocated to the pointer to functions for hardware acceleration operations.</p>
</td>
</tr>
<tr id="row1199991557093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1743697394093521"><a name="p1743697394093521"></a><a name="p1743697394093521"></a><a href="Display.md#ga304347c32a67bf7b20ef5d2b5714e5fa">GrallocInitialize</a> (<a href="zh-cn_topic_0000001054918153.md">GrallocFuncs</a> **funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492793757093521"><a name="p492793757093521"></a><a name="p492793757093521"></a>int32_t</p>
<p id="p779431531093521"><a name="p779431531093521"></a><a name="p779431531093521"></a>Initializes the memory module to obtain the pointer to functions for memory operations.</p>
</td>
</tr>
<tr id="row2055365700093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p435499376093521"><a name="p435499376093521"></a><a name="p435499376093521"></a><a href="Display.md#ga8842b25f91c247606048ab2d5cdb338f">GrallocUninitialize</a> (<a href="zh-cn_topic_0000001054918153.md">GrallocFuncs</a> *funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1043903373093521"><a name="p1043903373093521"></a><a name="p1043903373093521"></a>int32_t</p>
<p id="p1646432216093521"><a name="p1646432216093521"></a><a name="p1646432216093521"></a>Deinitializes the memory module to release the memory allocated to the pointer to functions for memory operations.</p>
</td>
</tr>
<tr id="row1182975233093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091747139093521"><a name="p1091747139093521"></a><a name="p1091747139093521"></a><a href="Display.md#ga061e587306a5d0367ff228d64434c05d">LayerInitialize</a> (<a href="zh-cn_topic_0000001055678100.md">LayerFuncs</a> **funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1379765123093521"><a name="p1379765123093521"></a><a name="p1379765123093521"></a>int32_t</p>
<p id="p1558510831093521"><a name="p1558510831093521"></a><a name="p1558510831093521"></a>Initializes the layer to apply for resources used by the layer and obtain the pointer to functions for layer operations.</p>
</td>
</tr>
<tr id="row249889090093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1366845626093521"><a name="p1366845626093521"></a><a name="p1366845626093521"></a><a href="Display.md#ga4e32b1a65cf243a9ac015b632a4eea0b">LayerUninitialize</a> (<a href="zh-cn_topic_0000001055678100.md">LayerFuncs</a> *funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673191183093521"><a name="p673191183093521"></a><a name="p673191183093521"></a>int32_t</p>
<p id="p1215381914093521"><a name="p1215381914093521"></a><a name="p1215381914093521"></a>Deinitializes the layer module to release the memory allocated to the pointer to functions for layer operations.</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1407282145093521"></a>

## **Enumeration Type Documentation**<a name="section1576021594093521"></a>

## BlendType<a name="gaab1839ed4aab1030dfda801a51e68817"></a>

```
enum [BlendType](Display.md#gaab1839ed4aab1030dfda801a51e68817)
```

**Description:**

Enumerates image blending types.

The system combines images based on a specified blending type during hardware acceleration.

<a name="table1031327576093521"></a>
<table><thead align="left"><tr id="row500510730093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p905471112093521"><a name="p905471112093521"></a><a name="p905471112093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p785126248093521"><a name="p785126248093521"></a><a name="p785126248093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1700481723093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry725762603093521p0"><a name="entry725762603093521p0"></a><a name="entry725762603093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817ae410edb34509ca21425fe5872bbc7e2f"><a name="ggaab1839ed4aab1030dfda801a51e68817ae410edb34509ca21425fe5872bbc7e2f"></a><a name="ggaab1839ed4aab1030dfda801a51e68817ae410edb34509ca21425fe5872bbc7e2f"></a></strong>BLEND_NONE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2042891349093521"><a name="p2042891349093521"></a><a name="p2042891349093521"></a>No blending</p>
<p id="p9372617103417"><a name="p9372617103417"></a><a name="p9372617103417"></a></p>
</td>
</tr>
<tr id="row1413966230093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry230191599093521p0"><a name="entry230191599093521p0"></a><a name="entry230191599093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a6330cee419fbdafc0b25f0aa068814e5"><a name="ggaab1839ed4aab1030dfda801a51e68817a6330cee419fbdafc0b25f0aa068814e5"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a6330cee419fbdafc0b25f0aa068814e5"></a></strong>BLEND_CLEAR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1981169365093521"><a name="p1981169365093521"></a><a name="p1981169365093521"></a>CLEAR blending</p>
<p id="p937212179343"><a name="p937212179343"></a><a name="p937212179343"></a></p>
</td>
</tr>
<tr id="row86654378093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1108171596093521p0"><a name="entry1108171596093521p0"></a><a name="entry1108171596093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817af01da0c255cdbf67d0774a67c2d221b5"><a name="ggaab1839ed4aab1030dfda801a51e68817af01da0c255cdbf67d0774a67c2d221b5"></a><a name="ggaab1839ed4aab1030dfda801a51e68817af01da0c255cdbf67d0774a67c2d221b5"></a></strong>BLEND_SRC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1181349254093521"><a name="p1181349254093521"></a><a name="p1181349254093521"></a>SRC blending</p>
<p id="p13372141711344"><a name="p13372141711344"></a><a name="p13372141711344"></a></p>
</td>
</tr>
<tr id="row1689227933093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1843633739093521p0"><a name="entry1843633739093521p0"></a><a name="entry1843633739093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817ad4c0cd02aa4b5f4849e2b29a26481dde"><a name="ggaab1839ed4aab1030dfda801a51e68817ad4c0cd02aa4b5f4849e2b29a26481dde"></a><a name="ggaab1839ed4aab1030dfda801a51e68817ad4c0cd02aa4b5f4849e2b29a26481dde"></a></strong>BLEND_SRCOVER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1832279242093521"><a name="p1832279242093521"></a><a name="p1832279242093521"></a>SRC_OVER blending</p>
<p id="p153721317193418"><a name="p153721317193418"></a><a name="p153721317193418"></a></p>
</td>
</tr>
<tr id="row412769096093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1192596637093521p0"><a name="entry1192596637093521p0"></a><a name="entry1192596637093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a21f03e8d04a58ed0684b39eb84bdb89f"><a name="ggaab1839ed4aab1030dfda801a51e68817a21f03e8d04a58ed0684b39eb84bdb89f"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a21f03e8d04a58ed0684b39eb84bdb89f"></a></strong>BLEND_DSTOVER</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1593806933093521"><a name="p1593806933093521"></a><a name="p1593806933093521"></a>DST_OVER blending</p>
<p id="p8372161720349"><a name="p8372161720349"></a><a name="p8372161720349"></a></p>
</td>
</tr>
<tr id="row655085092093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry89427880093521p0"><a name="entry89427880093521p0"></a><a name="entry89427880093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a74e681f6c9027bb2cf0bda3b72d2dd9e"><a name="ggaab1839ed4aab1030dfda801a51e68817a74e681f6c9027bb2cf0bda3b72d2dd9e"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a74e681f6c9027bb2cf0bda3b72d2dd9e"></a></strong>BLEND_SRCIN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1903555896093521"><a name="p1903555896093521"></a><a name="p1903555896093521"></a>SRC_IN blending</p>
<p id="p0372417163416"><a name="p0372417163416"></a><a name="p0372417163416"></a></p>
</td>
</tr>
<tr id="row366325679093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1264014360093521p0"><a name="entry1264014360093521p0"></a><a name="entry1264014360093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a19f528828d75c34e18375219f113d9bb"><a name="ggaab1839ed4aab1030dfda801a51e68817a19f528828d75c34e18375219f113d9bb"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a19f528828d75c34e18375219f113d9bb"></a></strong>BLEND_DSTIN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809977981093521"><a name="p1809977981093521"></a><a name="p1809977981093521"></a>DST_IN blending</p>
<p id="p83721717173417"><a name="p83721717173417"></a><a name="p83721717173417"></a></p>
</td>
</tr>
<tr id="row589326537093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1479210794093521p0"><a name="entry1479210794093521p0"></a><a name="entry1479210794093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a404e05a118462520e878c23f89808199"><a name="ggaab1839ed4aab1030dfda801a51e68817a404e05a118462520e878c23f89808199"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a404e05a118462520e878c23f89808199"></a></strong>BLEND_SRCOUT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650707613093521"><a name="p650707613093521"></a><a name="p650707613093521"></a>SRC_OUT blending</p>
<p id="p1373201753410"><a name="p1373201753410"></a><a name="p1373201753410"></a></p>
</td>
</tr>
<tr id="row1135436177093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry765353619093521p0"><a name="entry765353619093521p0"></a><a name="entry765353619093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817ac0dc902b4928413d367376e4c842d909"><a name="ggaab1839ed4aab1030dfda801a51e68817ac0dc902b4928413d367376e4c842d909"></a><a name="ggaab1839ed4aab1030dfda801a51e68817ac0dc902b4928413d367376e4c842d909"></a></strong>BLEND_DSTOUT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2050095937093521"><a name="p2050095937093521"></a><a name="p2050095937093521"></a>DST_OUT blending</p>
<p id="p93739178343"><a name="p93739178343"></a><a name="p93739178343"></a></p>
</td>
</tr>
<tr id="row1573184413093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry677048471093521p0"><a name="entry677048471093521p0"></a><a name="entry677048471093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817ada473c7e3bf2b1102349489416aefefc"><a name="ggaab1839ed4aab1030dfda801a51e68817ada473c7e3bf2b1102349489416aefefc"></a><a name="ggaab1839ed4aab1030dfda801a51e68817ada473c7e3bf2b1102349489416aefefc"></a></strong>BLEND_SRCATOP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352415641093521"><a name="p352415641093521"></a><a name="p352415641093521"></a>SRC_ATOP blending</p>
<p id="p1137317178343"><a name="p1137317178343"></a><a name="p1137317178343"></a></p>
</td>
</tr>
<tr id="row1354677478093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1314749647093521p0"><a name="entry1314749647093521p0"></a><a name="entry1314749647093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a0129b4506a06b1a6df297bcf685f5f89"><a name="ggaab1839ed4aab1030dfda801a51e68817a0129b4506a06b1a6df297bcf685f5f89"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a0129b4506a06b1a6df297bcf685f5f89"></a></strong>BLEND_DSTATOP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839654004093521"><a name="p839654004093521"></a><a name="p839654004093521"></a>DST_ATOP blending</p>
<p id="p43731317113416"><a name="p43731317113416"></a><a name="p43731317113416"></a></p>
</td>
</tr>
<tr id="row2122157428093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry745596789093521p0"><a name="entry745596789093521p0"></a><a name="entry745596789093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817adbdb329830e5b4d9fa2b17d5d6d7894f"><a name="ggaab1839ed4aab1030dfda801a51e68817adbdb329830e5b4d9fa2b17d5d6d7894f"></a><a name="ggaab1839ed4aab1030dfda801a51e68817adbdb329830e5b4d9fa2b17d5d6d7894f"></a></strong>BLEND_ADD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p935948233093521"><a name="p935948233093521"></a><a name="p935948233093521"></a>ADD blending</p>
<p id="p1837361720340"><a name="p1837361720340"></a><a name="p1837361720340"></a></p>
</td>
</tr>
<tr id="row2020963058093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry79625490093521p0"><a name="entry79625490093521p0"></a><a name="entry79625490093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a167c3b256e051244066d8e53cdd5529d"><a name="ggaab1839ed4aab1030dfda801a51e68817a167c3b256e051244066d8e53cdd5529d"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a167c3b256e051244066d8e53cdd5529d"></a></strong>BLEND_XOR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904787193093521"><a name="p904787193093521"></a><a name="p904787193093521"></a>XOR blending</p>
<p id="p14373121714346"><a name="p14373121714346"></a><a name="p14373121714346"></a></p>
</td>
</tr>
<tr id="row480248096093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1177576561093521p0"><a name="entry1177576561093521p0"></a><a name="entry1177576561093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a4686a5f30c73982d625a05db021e9b15"><a name="ggaab1839ed4aab1030dfda801a51e68817a4686a5f30c73982d625a05db021e9b15"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a4686a5f30c73982d625a05db021e9b15"></a></strong>BLEND_DST</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p674697046093521"><a name="p674697046093521"></a><a name="p674697046093521"></a>DST blending</p>
<p id="p6373101733410"><a name="p6373101733410"></a><a name="p6373101733410"></a></p>
</td>
</tr>
<tr id="row1426549974093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1171952799093521p0"><a name="entry1171952799093521p0"></a><a name="entry1171952799093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817ae549aa3794365df8965a2c3853c8da99"><a name="ggaab1839ed4aab1030dfda801a51e68817ae549aa3794365df8965a2c3853c8da99"></a><a name="ggaab1839ed4aab1030dfda801a51e68817ae549aa3794365df8965a2c3853c8da99"></a></strong>BLEND_AKS</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211194706093521"><a name="p211194706093521"></a><a name="p211194706093521"></a>AKS blending</p>
<p id="p1437381718345"><a name="p1437381718345"></a><a name="p1437381718345"></a></p>
</td>
</tr>
<tr id="row2129302357093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1188991961093521p0"><a name="entry1188991961093521p0"></a><a name="entry1188991961093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817a3cc39f12fa8bceba626a33c2d82a8bf7"><a name="ggaab1839ed4aab1030dfda801a51e68817a3cc39f12fa8bceba626a33c2d82a8bf7"></a><a name="ggaab1839ed4aab1030dfda801a51e68817a3cc39f12fa8bceba626a33c2d82a8bf7"></a></strong>BLEND_AKD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1686033752093521"><a name="p1686033752093521"></a><a name="p1686033752093521"></a>AKD blending</p>
<p id="p6373121783415"><a name="p6373121783415"></a><a name="p6373121783415"></a></p>
</td>
</tr>
<tr id="row1450094510093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1143497774093521p0"><a name="entry1143497774093521p0"></a><a name="entry1143497774093521p0"></a><strong id="ggaab1839ed4aab1030dfda801a51e68817ad0650812ac2aa9eee228f48ac514b44a"><a name="ggaab1839ed4aab1030dfda801a51e68817ad0650812ac2aa9eee228f48ac514b44a"></a><a name="ggaab1839ed4aab1030dfda801a51e68817ad0650812ac2aa9eee228f48ac514b44a"></a></strong>BLEND_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701329113093521"><a name="p1701329113093521"></a><a name="p1701329113093521"></a>Null operation</p>
<p id="p6373917153417"><a name="p6373917153417"></a><a name="p6373917153417"></a></p>
</td>
</tr>
</tbody>
</table>

## ColorKey<a name="ga4fe6fb05c7ba0048b1739d88f4d4878e"></a>

```
enum [ColorKey](Display.md#ga4fe6fb05c7ba0048b1739d88f4d4878e)
```

**Description:**

Enumerates color key types supported by hardware acceleration.

<a name="table198053741093521"></a>
<table><thead align="left"><tr id="row379504462093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p216756145093521"><a name="p216756145093521"></a><a name="p216756145093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1676702708093521"><a name="p1676702708093521"></a><a name="p1676702708093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1946386940093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry344728411093521p0"><a name="entry344728411093521p0"></a><a name="entry344728411093521p0"></a><strong id="gga4fe6fb05c7ba0048b1739d88f4d4878ea629b31de258db2ce01cb757b85bd5273"><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea629b31de258db2ce01cb757b85bd5273"></a><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea629b31de258db2ce01cb757b85bd5273"></a></strong>CKEY_NONE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1927616231093521"><a name="p1927616231093521"></a><a name="p1927616231093521"></a>No color key</p>
<p id="p5397171743413"><a name="p5397171743413"></a><a name="p5397171743413"></a></p>
</td>
</tr>
<tr id="row694775930093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1944131998093521p0"><a name="entry1944131998093521p0"></a><a name="entry1944131998093521p0"></a><strong id="gga4fe6fb05c7ba0048b1739d88f4d4878ea5e3271e73dce39d0806ff8e9cba011bc"><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea5e3271e73dce39d0806ff8e9cba011bc"></a><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea5e3271e73dce39d0806ff8e9cba011bc"></a></strong>CKEY_SRC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155336533093521"><a name="p155336533093521"></a><a name="p155336533093521"></a>Source color key</p>
<p id="p16398121713417"><a name="p16398121713417"></a><a name="p16398121713417"></a></p>
</td>
</tr>
<tr id="row2086802211093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1682060141093521p0"><a name="entry1682060141093521p0"></a><a name="entry1682060141093521p0"></a><strong id="gga4fe6fb05c7ba0048b1739d88f4d4878ea6921c2c202aa69293467baa6c33fae05"><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea6921c2c202aa69293467baa6c33fae05"></a><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea6921c2c202aa69293467baa6c33fae05"></a></strong>CKEY_DST</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684901006093521"><a name="p684901006093521"></a><a name="p684901006093521"></a>Destination color key</p>
<p id="p139819175341"><a name="p139819175341"></a><a name="p139819175341"></a></p>
</td>
</tr>
<tr id="row1949757602093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1255049752093521p0"><a name="entry1255049752093521p0"></a><a name="entry1255049752093521p0"></a><strong id="gga4fe6fb05c7ba0048b1739d88f4d4878ea32cedc8986de2c290bf2ec193d88cabf"><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea32cedc8986de2c290bf2ec193d88cabf"></a><a name="gga4fe6fb05c7ba0048b1739d88f4d4878ea32cedc8986de2c290bf2ec193d88cabf"></a></strong>CKEY_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p582270041093521"><a name="p582270041093521"></a><a name="p582270041093521"></a>Null operation</p>
<p id="p1539861714346"><a name="p1539861714346"></a><a name="p1539861714346"></a></p>
</td>
</tr>
</tbody>
</table>

## Connection<a name="gab0845c0c8d309ee865c78b095b00e671"></a>

```
enum [Connection](Display.md#gab0845c0c8d309ee865c78b095b00e671)
```

**Description:**

Enumerates connection types of hot plugging.

<a name="table1169936450093521"></a>
<table><thead align="left"><tr id="row312782078093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1274454614093521"><a name="p1274454614093521"></a><a name="p1274454614093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1099273429093521"><a name="p1099273429093521"></a><a name="p1099273429093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row746258562093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1102383844093521p0"><a name="entry1102383844093521p0"></a><a name="entry1102383844093521p0"></a><strong id="ggab0845c0c8d309ee865c78b095b00e671aef2863a469df3ea6871d640e3669a2f2"><a name="ggab0845c0c8d309ee865c78b095b00e671aef2863a469df3ea6871d640e3669a2f2"></a><a name="ggab0845c0c8d309ee865c78b095b00e671aef2863a469df3ea6871d640e3669a2f2"></a></strong>INVALID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221579671093521"><a name="p1221579671093521"></a><a name="p1221579671093521"></a>Invalid connection</p>
<p id="p740512173349"><a name="p740512173349"></a><a name="p740512173349"></a></p>
</td>
</tr>
<tr id="row997525869093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry227550975093521p0"><a name="entry227550975093521p0"></a><a name="entry227550975093521p0"></a><strong id="ggab0845c0c8d309ee865c78b095b00e671a7a691a2430ec26878897b5fbc9c22a4c"><a name="ggab0845c0c8d309ee865c78b095b00e671a7a691a2430ec26878897b5fbc9c22a4c"></a><a name="ggab0845c0c8d309ee865c78b095b00e671a7a691a2430ec26878897b5fbc9c22a4c"></a></strong>CONNECTED</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p624773523093521"><a name="p624773523093521"></a><a name="p624773523093521"></a>Connected</p>
<p id="p17405121717343"><a name="p17405121717343"></a><a name="p17405121717343"></a></p>
</td>
</tr>
<tr id="row210941475093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1126963187093521p0"><a name="entry1126963187093521p0"></a><a name="entry1126963187093521p0"></a><strong id="ggab0845c0c8d309ee865c78b095b00e671acdaad1112073e3e2ea032424c38c34e1"><a name="ggab0845c0c8d309ee865c78b095b00e671acdaad1112073e3e2ea032424c38c34e1"></a><a name="ggab0845c0c8d309ee865c78b095b00e671acdaad1112073e3e2ea032424c38c34e1"></a></strong>DISCONNECTED</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059242890093521"><a name="p1059242890093521"></a><a name="p1059242890093521"></a>Disconnected</p>
<p id="p94054175345"><a name="p94054175345"></a><a name="p94054175345"></a></p>
</td>
</tr>
</tbody>
</table>

## DispErrCode<a name="ga12a925dadef7573cd74d63d06824f9b0"></a>

```
enum [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)
```

**Description:**

Enumerates return values of the functions.

<a name="table315364107093521"></a>
<table><thead align="left"><tr id="row1194845383093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p834800169093521"><a name="p834800169093521"></a><a name="p834800169093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p30276771093521"><a name="p30276771093521"></a><a name="p30276771093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row372500155093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2020948026093521p0"><a name="entry2020948026093521p0"></a><a name="entry2020948026093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0a188daac95e787159d50ff9546536035b"><a name="gga12a925dadef7573cd74d63d06824f9b0a188daac95e787159d50ff9546536035b"></a><a name="gga12a925dadef7573cd74d63d06824f9b0a188daac95e787159d50ff9546536035b"></a></strong>DISPLAY_SUCCESS</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765079747093521"><a name="p765079747093521"></a><a name="p765079747093521"></a>Success</p>
<p id="p6411121718344"><a name="p6411121718344"></a><a name="p6411121718344"></a></p>
</td>
</tr>
<tr id="row415122978093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1683907038093521p0"><a name="entry1683907038093521p0"></a><a name="entry1683907038093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0afdffc20c71fb142c3e7f01323a31d742"><a name="gga12a925dadef7573cd74d63d06824f9b0afdffc20c71fb142c3e7f01323a31d742"></a><a name="gga12a925dadef7573cd74d63d06824f9b0afdffc20c71fb142c3e7f01323a31d742"></a></strong>DISPLAY_FAILURE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058714745093521"><a name="p1058714745093521"></a><a name="p1058714745093521"></a>Failure</p>
<p id="p174110171349"><a name="p174110171349"></a><a name="p174110171349"></a></p>
</td>
</tr>
<tr id="row1166062560093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry802389589093521p0"><a name="entry802389589093521p0"></a><a name="entry802389589093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0a5bdb0a826a652f51e6c82685ae08ede8"><a name="gga12a925dadef7573cd74d63d06824f9b0a5bdb0a826a652f51e6c82685ae08ede8"></a><a name="gga12a925dadef7573cd74d63d06824f9b0a5bdb0a826a652f51e6c82685ae08ede8"></a></strong>DISPLAY_FD_ERR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1729702142093521"><a name="p1729702142093521"></a><a name="p1729702142093521"></a>File handle (FD) error</p>
<p id="p15411141723418"><a name="p15411141723418"></a><a name="p15411141723418"></a></p>
</td>
</tr>
<tr id="row2081456089093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1390474877093521p0"><a name="entry1390474877093521p0"></a><a name="entry1390474877093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0a330e09be303bc7056f6115830bbd2370"><a name="gga12a925dadef7573cd74d63d06824f9b0a330e09be303bc7056f6115830bbd2370"></a><a name="gga12a925dadef7573cd74d63d06824f9b0a330e09be303bc7056f6115830bbd2370"></a></strong>DISPLAY_PARAM_ERR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1726029608093521"><a name="p1726029608093521"></a><a name="p1726029608093521"></a>Parameter error</p>
<p id="p13411617183417"><a name="p13411617183417"></a><a name="p13411617183417"></a></p>
</td>
</tr>
<tr id="row1670442421093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry233219760093521p0"><a name="entry233219760093521p0"></a><a name="entry233219760093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0a82fbcdba6c699059bc04b491c92424ac"><a name="gga12a925dadef7573cd74d63d06824f9b0a82fbcdba6c699059bc04b491c92424ac"></a><a name="gga12a925dadef7573cd74d63d06824f9b0a82fbcdba6c699059bc04b491c92424ac"></a></strong>DISPLAY_NULL_PTR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1246948685093521"><a name="p1246948685093521"></a><a name="p1246948685093521"></a>Null pointer</p>
<p id="p12411917163419"><a name="p12411917163419"></a><a name="p12411917163419"></a></p>
</td>
</tr>
<tr id="row332934127093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1312658524093521p0"><a name="entry1312658524093521p0"></a><a name="entry1312658524093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0a950a7bc41e893450315da9e73208f8c2"><a name="gga12a925dadef7573cd74d63d06824f9b0a950a7bc41e893450315da9e73208f8c2"></a><a name="gga12a925dadef7573cd74d63d06824f9b0a950a7bc41e893450315da9e73208f8c2"></a></strong>DISPLAY_NOT_SUPPORT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416624533093521"><a name="p416624533093521"></a><a name="p416624533093521"></a>Unsupported feature</p>
<p id="p941141719348"><a name="p941141719348"></a><a name="p941141719348"></a></p>
</td>
</tr>
<tr id="row420491133093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry671613517093521p0"><a name="entry671613517093521p0"></a><a name="entry671613517093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0af186ab511133fa3280c54d2c44358882"><a name="gga12a925dadef7573cd74d63d06824f9b0af186ab511133fa3280c54d2c44358882"></a><a name="gga12a925dadef7573cd74d63d06824f9b0af186ab511133fa3280c54d2c44358882"></a></strong>DISPLAY_NOMEM</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p563265120093521"><a name="p563265120093521"></a><a name="p563265120093521"></a>Insufficient memory</p>
<p id="p74113176341"><a name="p74113176341"></a><a name="p74113176341"></a></p>
</td>
</tr>
<tr id="row1029448869093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry151645392093521p0"><a name="entry151645392093521p0"></a><a name="entry151645392093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0ac11b678fc04745ff4d91f4398b83c427"><a name="gga12a925dadef7573cd74d63d06824f9b0ac11b678fc04745ff4d91f4398b83c427"></a><a name="gga12a925dadef7573cd74d63d06824f9b0ac11b678fc04745ff4d91f4398b83c427"></a></strong>DISPLAY_SYS_BUSY</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1782509684093521"><a name="p1782509684093521"></a><a name="p1782509684093521"></a>System busy</p>
<p id="p841121711342"><a name="p841121711342"></a><a name="p841121711342"></a></p>
</td>
</tr>
<tr id="row547888463093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1023992958093521p0"><a name="entry1023992958093521p0"></a><a name="entry1023992958093521p0"></a><strong id="gga12a925dadef7573cd74d63d06824f9b0ad133674b9f3b857a12791479aaf58cf8"><a name="gga12a925dadef7573cd74d63d06824f9b0ad133674b9f3b857a12791479aaf58cf8"></a><a name="gga12a925dadef7573cd74d63d06824f9b0ad133674b9f3b857a12791479aaf58cf8"></a></strong>DISPLAY_NOT_PERM</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142119759093521"><a name="p142119759093521"></a><a name="p142119759093521"></a>Forbidden operation</p>
<p id="p10411717153417"><a name="p10411717153417"></a><a name="p10411717153417"></a></p>
</td>
</tr>
</tbody>
</table>

## LayerType<a name="ga56943a0946e5f15e5e58054b8e7a04a4"></a>

```
enum [LayerType](Display.md#ga56943a0946e5f15e5e58054b8e7a04a4)
```

**Description:**

Enumerates layer types.

<a name="table434289348093521"></a>
<table><thead align="left"><tr id="row544310511093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p406602654093521"><a name="p406602654093521"></a><a name="p406602654093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2088332300093521"><a name="p2088332300093521"></a><a name="p2088332300093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2146946443093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1213847413093521p0"><a name="entry1213847413093521p0"></a><a name="entry1213847413093521p0"></a><strong id="gga56943a0946e5f15e5e58054b8e7a04a4a6ef157ea82a5d4c1715b3cddcca38d6f"><a name="gga56943a0946e5f15e5e58054b8e7a04a4a6ef157ea82a5d4c1715b3cddcca38d6f"></a><a name="gga56943a0946e5f15e5e58054b8e7a04a4a6ef157ea82a5d4c1715b3cddcca38d6f"></a></strong>LAYER_TYPE_GRAPHIC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319804983093521"><a name="p319804983093521"></a><a name="p319804983093521"></a>Graphic layer</p>
<p id="p134201117123415"><a name="p134201117123415"></a><a name="p134201117123415"></a></p>
</td>
</tr>
<tr id="row1621535218093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry234186175093521p0"><a name="entry234186175093521p0"></a><a name="entry234186175093521p0"></a><strong id="gga56943a0946e5f15e5e58054b8e7a04a4ac33e449941bc0e4d039b4b5bed853a78"><a name="gga56943a0946e5f15e5e58054b8e7a04a4ac33e449941bc0e4d039b4b5bed853a78"></a><a name="gga56943a0946e5f15e5e58054b8e7a04a4ac33e449941bc0e4d039b4b5bed853a78"></a></strong>LAYER_TYPE_OVERLAY</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436572481093521"><a name="p436572481093521"></a><a name="p436572481093521"></a>Overlay layer</p>
<p id="p142021743420"><a name="p142021743420"></a><a name="p142021743420"></a></p>
</td>
</tr>
<tr id="row699654822093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry529199432093521p0"><a name="entry529199432093521p0"></a><a name="entry529199432093521p0"></a><strong id="gga56943a0946e5f15e5e58054b8e7a04a4a0aef2c460a206fa00c742219d65be477"><a name="gga56943a0946e5f15e5e58054b8e7a04a4a0aef2c460a206fa00c742219d65be477"></a><a name="gga56943a0946e5f15e5e58054b8e7a04a4a0aef2c460a206fa00c742219d65be477"></a></strong>LAYER_TYPE_SDIEBAND</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105025354093521"><a name="p105025354093521"></a><a name="p105025354093521"></a>Sideband layer</p>
<p id="p15420517133410"><a name="p15420517133410"></a><a name="p15420517133410"></a></p>
</td>
</tr>
<tr id="row1194420709093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1427867286093521p0"><a name="entry1427867286093521p0"></a><a name="entry1427867286093521p0"></a><strong id="gga56943a0946e5f15e5e58054b8e7a04a4acd813c5ad9a2be97c85a97d4bdf1cb57"><a name="gga56943a0946e5f15e5e58054b8e7a04a4acd813c5ad9a2be97c85a97d4bdf1cb57"></a><a name="gga56943a0946e5f15e5e58054b8e7a04a4acd813c5ad9a2be97c85a97d4bdf1cb57"></a></strong>LAYER_TYPE_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989080000093521"><a name="p989080000093521"></a><a name="p989080000093521"></a>Empty layer</p>
<p id="p9420111720348"><a name="p9420111720348"></a><a name="p9420111720348"></a></p>
</td>
</tr>
</tbody>
</table>

## MemType<a name="gabd31f838aefffa46191d0d7dc36a96b2"></a>

```
enum [MemType](Display.md#gabd31f838aefffa46191d0d7dc36a96b2)
```

**Description:**

Enumerates memory types.

Memory is allocated based on the type specified by the GUI.

<a name="table1879212416093521"></a>
<table><thead align="left"><tr id="row1114729801093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p32450555093521"><a name="p32450555093521"></a><a name="p32450555093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1017709120093521"><a name="p1017709120093521"></a><a name="p1017709120093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row476527719093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1747486377093521p0"><a name="entry1747486377093521p0"></a><a name="entry1747486377093521p0"></a><strong id="ggabd31f838aefffa46191d0d7dc36a96b2ad3379d0af95e2e9dcbcfdb016d1cf9b3"><a name="ggabd31f838aefffa46191d0d7dc36a96b2ad3379d0af95e2e9dcbcfdb016d1cf9b3"></a><a name="ggabd31f838aefffa46191d0d7dc36a96b2ad3379d0af95e2e9dcbcfdb016d1cf9b3"></a></strong>NORMAL_MEM</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p179697721093521"><a name="p179697721093521"></a><a name="p179697721093521"></a>Memory without cache</p>
<p id="p12426417133416"><a name="p12426417133416"></a><a name="p12426417133416"></a></p>
</td>
</tr>
<tr id="row290142167093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry874148343093521p0"><a name="entry874148343093521p0"></a><a name="entry874148343093521p0"></a><strong id="ggabd31f838aefffa46191d0d7dc36a96b2a2ad949ccc994ad1718cb54929d762700"><a name="ggabd31f838aefffa46191d0d7dc36a96b2a2ad949ccc994ad1718cb54929d762700"></a><a name="ggabd31f838aefffa46191d0d7dc36a96b2a2ad949ccc994ad1718cb54929d762700"></a></strong>CACHE_MEM</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209645518093521"><a name="p209645518093521"></a><a name="p209645518093521"></a>Memory with cache</p>
<p id="p1142601733415"><a name="p1142601733415"></a><a name="p1142601733415"></a></p>
</td>
</tr>
<tr id="row355996725093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1858312643093521p0"><a name="entry1858312643093521p0"></a><a name="entry1858312643093521p0"></a><strong id="ggabd31f838aefffa46191d0d7dc36a96b2a79f98876507c94448fed5f6f33683fb7"><a name="ggabd31f838aefffa46191d0d7dc36a96b2a79f98876507c94448fed5f6f33683fb7"></a><a name="ggabd31f838aefffa46191d0d7dc36a96b2a79f98876507c94448fed5f6f33683fb7"></a></strong>SHM_MEM</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676987398093521"><a name="p676987398093521"></a><a name="p676987398093521"></a>Shared memory</p>
<p id="p7426317113413"><a name="p7426317113413"></a><a name="p7426317113413"></a></p>
</td>
</tr>
</tbody>
</table>

## MirrorType<a name="ga08d32376574b541d162d8534adb78fd0"></a>

```
enum [MirrorType](Display.md#ga08d32376574b541d162d8534adb78fd0)
```

**Description:**

Enumerates mirror types supported by hardware acceleration.

<a name="table806477430093521"></a>
<table><thead align="left"><tr id="row1975265834093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1101017927093521"><a name="p1101017927093521"></a><a name="p1101017927093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p886281777093521"><a name="p886281777093521"></a><a name="p886281777093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row738497623093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry72285688093521p0"><a name="entry72285688093521p0"></a><a name="entry72285688093521p0"></a><strong id="gga08d32376574b541d162d8534adb78fd0a5ad82fcc8af04f92571e185b61eeb309"><a name="gga08d32376574b541d162d8534adb78fd0a5ad82fcc8af04f92571e185b61eeb309"></a><a name="gga08d32376574b541d162d8534adb78fd0a5ad82fcc8af04f92571e185b61eeb309"></a></strong>MIRROR_NONE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056679315093521"><a name="p1056679315093521"></a><a name="p1056679315093521"></a>No mirror</p>
<p id="p184301517163412"><a name="p184301517163412"></a><a name="p184301517163412"></a></p>
</td>
</tr>
<tr id="row1976149221093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry377311474093521p0"><a name="entry377311474093521p0"></a><a name="entry377311474093521p0"></a><strong id="gga08d32376574b541d162d8534adb78fd0ae35099d9fd28c2974661bcce36a9ea5c"><a name="gga08d32376574b541d162d8534adb78fd0ae35099d9fd28c2974661bcce36a9ea5c"></a><a name="gga08d32376574b541d162d8534adb78fd0ae35099d9fd28c2974661bcce36a9ea5c"></a></strong>MIRROR_LR</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1508343553093521"><a name="p1508343553093521"></a><a name="p1508343553093521"></a>Left and right mirrors</p>
<p id="p10430317153416"><a name="p10430317153416"></a><a name="p10430317153416"></a></p>
</td>
</tr>
<tr id="row1666665109093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry27934345093521p0"><a name="entry27934345093521p0"></a><a name="entry27934345093521p0"></a><strong id="gga08d32376574b541d162d8534adb78fd0afd82e59546a645fd29bc779c50bfa733"><a name="gga08d32376574b541d162d8534adb78fd0afd82e59546a645fd29bc779c50bfa733"></a><a name="gga08d32376574b541d162d8534adb78fd0afd82e59546a645fd29bc779c50bfa733"></a></strong>MIRROR_TB</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p604253140093521"><a name="p604253140093521"></a><a name="p604253140093521"></a>Top and bottom mirrors</p>
<p id="p19430317123415"><a name="p19430317123415"></a><a name="p19430317123415"></a></p>
</td>
</tr>
<tr id="row637192762093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry547688410093521p0"><a name="entry547688410093521p0"></a><a name="entry547688410093521p0"></a><strong id="gga08d32376574b541d162d8534adb78fd0ad9e357a2c2f7dc0e3ca5a351ec457410"><a name="gga08d32376574b541d162d8534adb78fd0ad9e357a2c2f7dc0e3ca5a351ec457410"></a><a name="gga08d32376574b541d162d8534adb78fd0ad9e357a2c2f7dc0e3ca5a351ec457410"></a></strong>MIRROR_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2076509559093521"><a name="p2076509559093521"></a><a name="p2076509559093521"></a>Null operation</p>
<p id="p10430161793415"><a name="p10430161793415"></a><a name="p10430161793415"></a></p>
</td>
</tr>
</tbody>
</table>

## PixelFormat<a name="ga60883d4958a60b91661e97027a85072a"></a>

```
enum [PixelFormat](Codec.md#ga60883d4958a60b91661e97027a85072a)
```

**Description:**

Enumerates pixel formats.

<a name="table188317093521"></a>
<table><thead align="left"><tr id="row1440959410093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1232724880093521"><a name="p1232724880093521"></a><a name="p1232724880093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p801448640093521"><a name="p801448640093521"></a><a name="p801448640093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row661890889093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry864935634093521p0"><a name="entry864935634093521p0"></a><a name="entry864935634093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa5fae320872be3ffdda0d371cec048ec6"><a name="gga60883d4958a60b91661e97027a85072aa5fae320872be3ffdda0d371cec048ec6"></a><a name="gga60883d4958a60b91661e97027a85072aa5fae320872be3ffdda0d371cec048ec6"></a></strong>PIXEL_FMT_RGB_565</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p466057929093521"><a name="p466057929093521"></a><a name="p466057929093521"></a>RGB565 format</p>
<p id="p843621763412"><a name="p843621763412"></a><a name="p843621763412"></a></p>
</td>
</tr>
<tr id="row1855064056093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1319315921093521p0"><a name="entry1319315921093521p0"></a><a name="entry1319315921093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa4c16147153b63d7ba71b257111afdd62"><a name="gga60883d4958a60b91661e97027a85072aa4c16147153b63d7ba71b257111afdd62"></a><a name="gga60883d4958a60b91661e97027a85072aa4c16147153b63d7ba71b257111afdd62"></a></strong>PIXEL_FMT_RGBA_5658</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1796138744093521"><a name="p1796138744093521"></a><a name="p1796138744093521"></a>RGBA5658 format</p>
<p id="p194361017113416"><a name="p194361017113416"></a><a name="p194361017113416"></a></p>
</td>
</tr>
<tr id="row2077391247093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1744267563093521p0"><a name="entry1744267563093521p0"></a><a name="entry1744267563093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aaa479ac0d983fde9b4f7f0e1a3b3e230f"><a name="gga60883d4958a60b91661e97027a85072aaa479ac0d983fde9b4f7f0e1a3b3e230f"></a><a name="gga60883d4958a60b91661e97027a85072aaa479ac0d983fde9b4f7f0e1a3b3e230f"></a></strong>PIXEL_FMT_RGBX_4444</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775576635093521"><a name="p775576635093521"></a><a name="p775576635093521"></a>RGBX4444 format</p>
<p id="p6436141710344"><a name="p6436141710344"></a><a name="p6436141710344"></a></p>
</td>
</tr>
<tr id="row838914127093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1319602608093521p0"><a name="entry1319602608093521p0"></a><a name="entry1319602608093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aacbb91256e8c45a51410a9f6caae2d04c"><a name="gga60883d4958a60b91661e97027a85072aacbb91256e8c45a51410a9f6caae2d04c"></a><a name="gga60883d4958a60b91661e97027a85072aacbb91256e8c45a51410a9f6caae2d04c"></a></strong>PIXEL_FMT_RGBA_4444</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527224547093521"><a name="p527224547093521"></a><a name="p527224547093521"></a>RGBA4444 format</p>
<p id="p1543641723419"><a name="p1543641723419"></a><a name="p1543641723419"></a></p>
</td>
</tr>
<tr id="row16458467093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2031742921093521p0"><a name="entry2031742921093521p0"></a><a name="entry2031742921093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa7d18a83da06902c104208031ed487942"><a name="gga60883d4958a60b91661e97027a85072aa7d18a83da06902c104208031ed487942"></a><a name="gga60883d4958a60b91661e97027a85072aa7d18a83da06902c104208031ed487942"></a></strong>PIXEL_FMT_RGB_444</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1328591524093521"><a name="p1328591524093521"></a><a name="p1328591524093521"></a>RGB444 format</p>
<p id="p1843611719349"><a name="p1843611719349"></a><a name="p1843611719349"></a></p>
</td>
</tr>
<tr id="row653407437093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1813841701093521p0"><a name="entry1813841701093521p0"></a><a name="entry1813841701093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa85e5dd1a0e547c0031baffd02abb31a0"><a name="gga60883d4958a60b91661e97027a85072aa85e5dd1a0e547c0031baffd02abb31a0"></a><a name="gga60883d4958a60b91661e97027a85072aa85e5dd1a0e547c0031baffd02abb31a0"></a></strong>PIXEL_FMT_RGBX_5551</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p523646497093521"><a name="p523646497093521"></a><a name="p523646497093521"></a>RGBX5551 format</p>
<p id="p843671733415"><a name="p843671733415"></a><a name="p843671733415"></a></p>
</td>
</tr>
<tr id="row587357716093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry229372779093521p0"><a name="entry229372779093521p0"></a><a name="entry229372779093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aadc1387526a271d8c6db7729de06474b1"><a name="gga60883d4958a60b91661e97027a85072aadc1387526a271d8c6db7729de06474b1"></a><a name="gga60883d4958a60b91661e97027a85072aadc1387526a271d8c6db7729de06474b1"></a></strong>PIXEL_FMT_RGBA_5551</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p953713918093521"><a name="p953713918093521"></a><a name="p953713918093521"></a>RGBA5551 format</p>
<p id="p74361817143415"><a name="p74361817143415"></a><a name="p74361817143415"></a></p>
</td>
</tr>
<tr id="row374231236093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1791875463093521p0"><a name="entry1791875463093521p0"></a><a name="entry1791875463093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa720a429fa57133f6e27ef8c8fa1c404a"><a name="gga60883d4958a60b91661e97027a85072aa720a429fa57133f6e27ef8c8fa1c404a"></a><a name="gga60883d4958a60b91661e97027a85072aa720a429fa57133f6e27ef8c8fa1c404a"></a></strong>PIXEL_FMT_RGB_555</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876123184093521"><a name="p876123184093521"></a><a name="p876123184093521"></a>RGB555 format</p>
<p id="p443651718341"><a name="p443651718341"></a><a name="p443651718341"></a></p>
</td>
</tr>
<tr id="row1462751646093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry658916959093521p0"><a name="entry658916959093521p0"></a><a name="entry658916959093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa24a7181b7fb4019e7c19739bd9b65ff0"><a name="gga60883d4958a60b91661e97027a85072aa24a7181b7fb4019e7c19739bd9b65ff0"></a><a name="gga60883d4958a60b91661e97027a85072aa24a7181b7fb4019e7c19739bd9b65ff0"></a></strong>PIXEL_FMT_RGBX_8888</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108938443093521"><a name="p108938443093521"></a><a name="p108938443093521"></a>RGBX8888 format</p>
<p id="p15436121733413"><a name="p15436121733413"></a><a name="p15436121733413"></a></p>
</td>
</tr>
<tr id="row165596075093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2104659527093521p0"><a name="entry2104659527093521p0"></a><a name="entry2104659527093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa90b462672221691ed66cacb07dd2e05f"><a name="gga60883d4958a60b91661e97027a85072aa90b462672221691ed66cacb07dd2e05f"></a><a name="gga60883d4958a60b91661e97027a85072aa90b462672221691ed66cacb07dd2e05f"></a></strong>PIXEL_FMT_RGBA_8888</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705728242093521"><a name="p705728242093521"></a><a name="p705728242093521"></a>RGBA8888 format</p>
<p id="p16436817153411"><a name="p16436817153411"></a><a name="p16436817153411"></a></p>
</td>
</tr>
<tr id="row1425834429093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2050351822093521p0"><a name="entry2050351822093521p0"></a><a name="entry2050351822093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa7ff77397bf2cf52b4614a46264f8ce01"><a name="gga60883d4958a60b91661e97027a85072aa7ff77397bf2cf52b4614a46264f8ce01"></a><a name="gga60883d4958a60b91661e97027a85072aa7ff77397bf2cf52b4614a46264f8ce01"></a></strong>PIXEL_FMT_RGB_888</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2070011038093521"><a name="p2070011038093521"></a><a name="p2070011038093521"></a>RGB888 format</p>
<p id="p184361817103414"><a name="p184361817103414"></a><a name="p184361817103414"></a></p>
</td>
</tr>
<tr id="row1492272304093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry755168796093521p0"><a name="entry755168796093521p0"></a><a name="entry755168796093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aaec581b908c291e2bd0155e25169f9629"><a name="gga60883d4958a60b91661e97027a85072aaec581b908c291e2bd0155e25169f9629"></a><a name="gga60883d4958a60b91661e97027a85072aaec581b908c291e2bd0155e25169f9629"></a></strong>PIXEL_FMT_BGR_565</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1324041597093521"><a name="p1324041597093521"></a><a name="p1324041597093521"></a>BGR565 format</p>
<p id="p943611773414"><a name="p943611773414"></a><a name="p943611773414"></a></p>
</td>
</tr>
<tr id="row42567668093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry375257717093521p0"><a name="entry375257717093521p0"></a><a name="entry375257717093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa6b5a7b35e00fc25146de0c9bf88b0230"><a name="gga60883d4958a60b91661e97027a85072aa6b5a7b35e00fc25146de0c9bf88b0230"></a><a name="gga60883d4958a60b91661e97027a85072aa6b5a7b35e00fc25146de0c9bf88b0230"></a></strong>PIXEL_FMT_BGRX_4444</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113352331093521"><a name="p113352331093521"></a><a name="p113352331093521"></a>BGRX4444 format</p>
<p id="p3436111743414"><a name="p3436111743414"></a><a name="p3436111743414"></a></p>
</td>
</tr>
<tr id="row62059093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry171901222093521p0"><a name="entry171901222093521p0"></a><a name="entry171901222093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa2f3d4ada099b2e8d84ec4501fbc8bed9"><a name="gga60883d4958a60b91661e97027a85072aa2f3d4ada099b2e8d84ec4501fbc8bed9"></a><a name="gga60883d4958a60b91661e97027a85072aa2f3d4ada099b2e8d84ec4501fbc8bed9"></a></strong>PIXEL_FMT_BGRA_4444</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511236294093521"><a name="p1511236294093521"></a><a name="p1511236294093521"></a>BGRA4444 format</p>
<p id="p2436191718347"><a name="p2436191718347"></a><a name="p2436191718347"></a></p>
</td>
</tr>
<tr id="row657454107093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1617782698093521p0"><a name="entry1617782698093521p0"></a><a name="entry1617782698093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aaaf1a20dc0a597258cfe6aca806a8e0de"><a name="gga60883d4958a60b91661e97027a85072aaaf1a20dc0a597258cfe6aca806a8e0de"></a><a name="gga60883d4958a60b91661e97027a85072aaaf1a20dc0a597258cfe6aca806a8e0de"></a></strong>PIXEL_FMT_BGRX_5551</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p960381243093521"><a name="p960381243093521"></a><a name="p960381243093521"></a>BGRX5551 format</p>
<p id="p343719177344"><a name="p343719177344"></a><a name="p343719177344"></a></p>
</td>
</tr>
<tr id="row671815297093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1668791586093521p0"><a name="entry1668791586093521p0"></a><a name="entry1668791586093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa2319d4a75dae0b56776fa63d525e308b"><a name="gga60883d4958a60b91661e97027a85072aa2319d4a75dae0b56776fa63d525e308b"></a><a name="gga60883d4958a60b91661e97027a85072aa2319d4a75dae0b56776fa63d525e308b"></a></strong>PIXEL_FMT_BGRA_5551</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941040327093521"><a name="p1941040327093521"></a><a name="p1941040327093521"></a>BGRA5551 format</p>
<p id="p5437161710341"><a name="p5437161710341"></a><a name="p5437161710341"></a></p>
</td>
</tr>
<tr id="row1103564219093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1038878352093521p0"><a name="entry1038878352093521p0"></a><a name="entry1038878352093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa1b19279f89c8cfb60e7d77ce23cd5f43"><a name="gga60883d4958a60b91661e97027a85072aa1b19279f89c8cfb60e7d77ce23cd5f43"></a><a name="gga60883d4958a60b91661e97027a85072aa1b19279f89c8cfb60e7d77ce23cd5f43"></a></strong>PIXEL_FMT_BGRX_8888</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45955196093521"><a name="p45955196093521"></a><a name="p45955196093521"></a>BGRX8888 format</p>
<p id="p443712174342"><a name="p443712174342"></a><a name="p443712174342"></a></p>
</td>
</tr>
<tr id="row109083917093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1838533497093521p0"><a name="entry1838533497093521p0"></a><a name="entry1838533497093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aaeb31c670120a1fbc96a0e0887997fe16"><a name="gga60883d4958a60b91661e97027a85072aaeb31c670120a1fbc96a0e0887997fe16"></a><a name="gga60883d4958a60b91661e97027a85072aaeb31c670120a1fbc96a0e0887997fe16"></a></strong>PIXEL_FMT_BGRA_8888</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1955386873093521"><a name="p1955386873093521"></a><a name="p1955386873093521"></a>BGRA8888 format</p>
<p id="p843781713344"><a name="p843781713344"></a><a name="p843781713344"></a></p>
</td>
</tr>
<tr id="row1606231524093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1301025015093521p0"><a name="entry1301025015093521p0"></a><a name="entry1301025015093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aac73c2a84907a53ed95a329007b5c8992"><a name="gga60883d4958a60b91661e97027a85072aac73c2a84907a53ed95a329007b5c8992"></a><a name="gga60883d4958a60b91661e97027a85072aac73c2a84907a53ed95a329007b5c8992"></a></strong>PIXEL_FMT_YUV_422_I</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p668592345093521"><a name="p668592345093521"></a><a name="p668592345093521"></a>YUV422 interleaved format</p>
<p id="p3437917183420"><a name="p3437917183420"></a><a name="p3437917183420"></a></p>
</td>
</tr>
<tr id="row1625219208093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry136921962093521p0"><a name="entry136921962093521p0"></a><a name="entry136921962093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aabdf1224848278508479ce97f637dd711"><a name="gga60883d4958a60b91661e97027a85072aabdf1224848278508479ce97f637dd711"></a><a name="gga60883d4958a60b91661e97027a85072aabdf1224848278508479ce97f637dd711"></a></strong>PIXEL_FMT_YCBCR_422_SP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567215775093521"><a name="p1567215775093521"></a><a name="p1567215775093521"></a>YCBCR422 semi-planar format</p>
<p id="p154375171346"><a name="p154375171346"></a><a name="p154375171346"></a></p>
</td>
</tr>
<tr id="row1057202307093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry746418900093521p0"><a name="entry746418900093521p0"></a><a name="entry746418900093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa8bf97d66e26b3aad7c83dfa70e2bc451"><a name="gga60883d4958a60b91661e97027a85072aa8bf97d66e26b3aad7c83dfa70e2bc451"></a><a name="gga60883d4958a60b91661e97027a85072aa8bf97d66e26b3aad7c83dfa70e2bc451"></a></strong>PIXEL_FMT_YCRCB_422_SP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824754958093521"><a name="p1824754958093521"></a><a name="p1824754958093521"></a>YCRCB422 semi-planar format</p>
<p id="p17437161783412"><a name="p17437161783412"></a><a name="p17437161783412"></a></p>
</td>
</tr>
<tr id="row429589686093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1765818742093521p0"><a name="entry1765818742093521p0"></a><a name="entry1765818742093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa0d1db50eb492f9073abdd2d662c56396"><a name="gga60883d4958a60b91661e97027a85072aa0d1db50eb492f9073abdd2d662c56396"></a><a name="gga60883d4958a60b91661e97027a85072aa0d1db50eb492f9073abdd2d662c56396"></a></strong>PIXEL_FMT_YCBCR_420_SP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1582195247093521"><a name="p1582195247093521"></a><a name="p1582195247093521"></a>YCBCR420 semi-planar format</p>
<p id="p44379179347"><a name="p44379179347"></a><a name="p44379179347"></a></p>
</td>
</tr>
<tr id="row1485532508093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1979265912093521p0"><a name="entry1979265912093521p0"></a><a name="entry1979265912093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa1fa43c8a197d5c974a35b8bf02ab386e"><a name="gga60883d4958a60b91661e97027a85072aa1fa43c8a197d5c974a35b8bf02ab386e"></a><a name="gga60883d4958a60b91661e97027a85072aa1fa43c8a197d5c974a35b8bf02ab386e"></a></strong>PIXEL_FMT_YCRCB_420_SP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1294160234093521"><a name="p1294160234093521"></a><a name="p1294160234093521"></a>YCRCB420 semi-planar format</p>
<p id="p12437131773416"><a name="p12437131773416"></a><a name="p12437131773416"></a></p>
</td>
</tr>
<tr id="row663187544093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1895357891093521p0"><a name="entry1895357891093521p0"></a><a name="entry1895357891093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aaa2fe085e63428ea76e1d975175001dc6"><a name="gga60883d4958a60b91661e97027a85072aaa2fe085e63428ea76e1d975175001dc6"></a><a name="gga60883d4958a60b91661e97027a85072aaa2fe085e63428ea76e1d975175001dc6"></a></strong>PIXEL_FMT_YCBCR_422_P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075230091093521"><a name="p1075230091093521"></a><a name="p1075230091093521"></a>YCBCR422 planar format</p>
<p id="p11437317103415"><a name="p11437317103415"></a><a name="p11437317103415"></a></p>
</td>
</tr>
<tr id="row661178141093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1386714262093521p0"><a name="entry1386714262093521p0"></a><a name="entry1386714262093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aab04eb6e1d940e42f3b4cc20c0a44c4ee"><a name="gga60883d4958a60b91661e97027a85072aab04eb6e1d940e42f3b4cc20c0a44c4ee"></a><a name="gga60883d4958a60b91661e97027a85072aab04eb6e1d940e42f3b4cc20c0a44c4ee"></a></strong>PIXEL_FMT_YCRCB_422_P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p721934306093521"><a name="p721934306093521"></a><a name="p721934306093521"></a>YCRCB422 planar format</p>
<p id="p6437917203413"><a name="p6437917203413"></a><a name="p6437917203413"></a></p>
</td>
</tr>
<tr id="row1107200190093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1414786980093521p0"><a name="entry1414786980093521p0"></a><a name="entry1414786980093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa3d80e785bed28e2b3f5c7df563500962"><a name="gga60883d4958a60b91661e97027a85072aa3d80e785bed28e2b3f5c7df563500962"></a><a name="gga60883d4958a60b91661e97027a85072aa3d80e785bed28e2b3f5c7df563500962"></a></strong>PIXEL_FMT_YCBCR_420_P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p487224493093521"><a name="p487224493093521"></a><a name="p487224493093521"></a>YCBCR420 planar format</p>
<p id="p104371017173418"><a name="p104371017173418"></a><a name="p104371017173418"></a></p>
</td>
</tr>
<tr id="row2078193573093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry901716847093521p0"><a name="entry901716847093521p0"></a><a name="entry901716847093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa3dc5a0a5ad2f21218b446c477277210a"><a name="gga60883d4958a60b91661e97027a85072aa3dc5a0a5ad2f21218b446c477277210a"></a><a name="gga60883d4958a60b91661e97027a85072aa3dc5a0a5ad2f21218b446c477277210a"></a></strong>PIXEL_FMT_YCRCB_420_P</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1915299129093521"><a name="p1915299129093521"></a><a name="p1915299129093521"></a>YCRCB420 planar format</p>
<p id="p18437417103413"><a name="p18437417103413"></a><a name="p18437417103413"></a></p>
</td>
</tr>
<tr id="row473281747093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry655248001093521p0"><a name="entry655248001093521p0"></a><a name="entry655248001093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa3980def5b133584bdb2982a71f07798e"><a name="gga60883d4958a60b91661e97027a85072aa3980def5b133584bdb2982a71f07798e"></a><a name="gga60883d4958a60b91661e97027a85072aa3980def5b133584bdb2982a71f07798e"></a></strong>PIXEL_FMT_YUYV_422_PKG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051796753093521"><a name="p2051796753093521"></a><a name="p2051796753093521"></a>YUYV422 packed format</p>
<p id="p1943718179349"><a name="p1943718179349"></a><a name="p1943718179349"></a></p>
</td>
</tr>
<tr id="row1914090591093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1468067435093521p0"><a name="entry1468067435093521p0"></a><a name="entry1468067435093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aadfd69bd5b421aad5bdd39d5f33317197"><a name="gga60883d4958a60b91661e97027a85072aadfd69bd5b421aad5bdd39d5f33317197"></a><a name="gga60883d4958a60b91661e97027a85072aadfd69bd5b421aad5bdd39d5f33317197"></a></strong>PIXEL_FMT_UYVY_422_PKG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p952150539093521"><a name="p952150539093521"></a><a name="p952150539093521"></a>UYVY422 packed format</p>
<p id="p194376175347"><a name="p194376175347"></a><a name="p194376175347"></a></p>
</td>
</tr>
<tr id="row327674968093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry774544593093521p0"><a name="entry774544593093521p0"></a><a name="entry774544593093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aaf851031c336e8d9f57c940c5f52381f4"><a name="gga60883d4958a60b91661e97027a85072aaf851031c336e8d9f57c940c5f52381f4"></a><a name="gga60883d4958a60b91661e97027a85072aaf851031c336e8d9f57c940c5f52381f4"></a></strong>PIXEL_FMT_YVYU_422_PKG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1655831320093521"><a name="p1655831320093521"></a><a name="p1655831320093521"></a>YVYU422 packed format</p>
<p id="p11437517183414"><a name="p11437517183414"></a><a name="p11437517183414"></a></p>
</td>
</tr>
<tr id="row637555349093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1266943094093521p0"><a name="entry1266943094093521p0"></a><a name="entry1266943094093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa317a761939335025379d382074a1541c"><a name="gga60883d4958a60b91661e97027a85072aa317a761939335025379d382074a1541c"></a><a name="gga60883d4958a60b91661e97027a85072aa317a761939335025379d382074a1541c"></a></strong>PIXEL_FMT_VYUY_422_PKG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1634434989093521"><a name="p1634434989093521"></a><a name="p1634434989093521"></a>VYUY422 packed format</p>
<p id="p943741714349"><a name="p943741714349"></a><a name="p943741714349"></a></p>
</td>
</tr>
<tr id="row287750395093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry722086757093521p0"><a name="entry722086757093521p0"></a><a name="entry722086757093521p0"></a><strong id="gga60883d4958a60b91661e97027a85072aa07086bb3356c9c88959eee00c0982684"><a name="gga60883d4958a60b91661e97027a85072aa07086bb3356c9c88959eee00c0982684"></a><a name="gga60883d4958a60b91661e97027a85072aa07086bb3356c9c88959eee00c0982684"></a></strong>PIXEL_FMT_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274034053093521"><a name="p1274034053093521"></a><a name="p1274034053093521"></a>Invalid pixel format</p>
<p id="p2437111717346"><a name="p2437111717346"></a><a name="p2437111717346"></a></p>
</td>
</tr>
</tbody>
</table>

## RopType<a name="ga24265f7618fbdba53d3da4806d3097c4"></a>

```
enum [RopType](Display.md#ga24265f7618fbdba53d3da4806d3097c4)
```

**Description:**

Enumerates ROP types supported by hardware acceleration.

ROP performs bitwise Boolean operations \(including bitwise AND and bitwise OR\) on the RGB color and alpha values of the foreground bitmap with those of the background bitmap, and then outputs the result.

<a name="table1312755151093521"></a>
<table><thead align="left"><tr id="row834429767093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1330790320093521"><a name="p1330790320093521"></a><a name="p1330790320093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p651744481093521"><a name="p651744481093521"></a><a name="p651744481093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row231439706093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1842667486093521p0"><a name="entry1842667486093521p0"></a><a name="entry1842667486093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a6358a786ec3b81000a07b343424cee0d"><a name="gga24265f7618fbdba53d3da4806d3097c4a6358a786ec3b81000a07b343424cee0d"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a6358a786ec3b81000a07b343424cee0d"></a></strong>ROP_BLACK</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644526879093521"><a name="p644526879093521"></a><a name="p644526879093521"></a>Blackness</p>
<p id="p1847071733420"><a name="p1847071733420"></a><a name="p1847071733420"></a></p>
</td>
</tr>
<tr id="row1132416294093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry813628445093521p0"><a name="entry813628445093521p0"></a><a name="entry813628445093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a96c89f7b89a9048d355b4dc467224f4c"><a name="gga24265f7618fbdba53d3da4806d3097c4a96c89f7b89a9048d355b4dc467224f4c"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a96c89f7b89a9048d355b4dc467224f4c"></a></strong>ROP_NOTMERGEPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323894591093521"><a name="p323894591093521"></a><a name="p323894591093521"></a>~(S2+S1)</p>
<p id="p11470141718348"><a name="p11470141718348"></a><a name="p11470141718348"></a></p>
</td>
</tr>
<tr id="row1399054971093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry824613613093521p0"><a name="entry824613613093521p0"></a><a name="entry824613613093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a54d054ea6920cb88f374f70e8d41f934"><a name="gga24265f7618fbdba53d3da4806d3097c4a54d054ea6920cb88f374f70e8d41f934"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a54d054ea6920cb88f374f70e8d41f934"></a></strong>ROP_MASKNOTPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404523086093521"><a name="p404523086093521"></a><a name="p404523086093521"></a>~S2&amp;S1</p>
<p id="p114701317133414"><a name="p114701317133414"></a><a name="p114701317133414"></a></p>
</td>
</tr>
<tr id="row1264440599093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1059666445093521p0"><a name="entry1059666445093521p0"></a><a name="entry1059666445093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4af4a5d5dc0f15249001cff7ef32fadef1"><a name="gga24265f7618fbdba53d3da4806d3097c4af4a5d5dc0f15249001cff7ef32fadef1"></a><a name="gga24265f7618fbdba53d3da4806d3097c4af4a5d5dc0f15249001cff7ef32fadef1"></a></strong>ROP_NOTCOPYPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84349219093521"><a name="p84349219093521"></a><a name="p84349219093521"></a>~S2</p>
<p id="p12470161717346"><a name="p12470161717346"></a><a name="p12470161717346"></a></p>
</td>
</tr>
<tr id="row1986607799093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1272619856093521p0"><a name="entry1272619856093521p0"></a><a name="entry1272619856093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4ad777eea18ba9f4e071b00aa060db00e3"><a name="gga24265f7618fbdba53d3da4806d3097c4ad777eea18ba9f4e071b00aa060db00e3"></a><a name="gga24265f7618fbdba53d3da4806d3097c4ad777eea18ba9f4e071b00aa060db00e3"></a></strong>ROP_MASKPENNOT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749991189093521"><a name="p749991189093521"></a><a name="p749991189093521"></a>S2&amp;~S1</p>
<p id="p11470617103414"><a name="p11470617103414"></a><a name="p11470617103414"></a></p>
</td>
</tr>
<tr id="row1657350745093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1827251539093521p0"><a name="entry1827251539093521p0"></a><a name="entry1827251539093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4afa63c8e2a6a39d50954cb6316576b4e9"><a name="gga24265f7618fbdba53d3da4806d3097c4afa63c8e2a6a39d50954cb6316576b4e9"></a><a name="gga24265f7618fbdba53d3da4806d3097c4afa63c8e2a6a39d50954cb6316576b4e9"></a></strong>ROP_NOT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386537136093521"><a name="p386537136093521"></a><a name="p386537136093521"></a>~S1</p>
<p id="p4470151716346"><a name="p4470151716346"></a><a name="p4470151716346"></a></p>
</td>
</tr>
<tr id="row139599879093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1328158763093521p0"><a name="entry1328158763093521p0"></a><a name="entry1328158763093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a79433776e85bb80ad0306ced0b82947c"><a name="gga24265f7618fbdba53d3da4806d3097c4a79433776e85bb80ad0306ced0b82947c"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a79433776e85bb80ad0306ced0b82947c"></a></strong>ROP_XORPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p526795094093521"><a name="p526795094093521"></a><a name="p526795094093521"></a>S2^S1</p>
<p id="p114701817193413"><a name="p114701817193413"></a><a name="p114701817193413"></a></p>
</td>
</tr>
<tr id="row1030653847093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry271523229093521p0"><a name="entry271523229093521p0"></a><a name="entry271523229093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4ad6c4d2458a9caaa079a3e5907d636e8a"><a name="gga24265f7618fbdba53d3da4806d3097c4ad6c4d2458a9caaa079a3e5907d636e8a"></a><a name="gga24265f7618fbdba53d3da4806d3097c4ad6c4d2458a9caaa079a3e5907d636e8a"></a></strong>ROP_NOTMASKPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281257189093521"><a name="p1281257189093521"></a><a name="p1281257189093521"></a>~(S2&amp;S1)</p>
<p id="p104719179341"><a name="p104719179341"></a><a name="p104719179341"></a></p>
</td>
</tr>
<tr id="row508572313093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1637323968093521p0"><a name="entry1637323968093521p0"></a><a name="entry1637323968093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a2a069e2105c5b8d4dac5d174c76eb9d4"><a name="gga24265f7618fbdba53d3da4806d3097c4a2a069e2105c5b8d4dac5d174c76eb9d4"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a2a069e2105c5b8d4dac5d174c76eb9d4"></a></strong>ROP_MASKPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798332200093521"><a name="p798332200093521"></a><a name="p798332200093521"></a>S2&amp;S1</p>
<p id="p5471201713343"><a name="p5471201713343"></a><a name="p5471201713343"></a></p>
</td>
</tr>
<tr id="row589963179093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry272050950093521p0"><a name="entry272050950093521p0"></a><a name="entry272050950093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a33c37c5ce718e876f43141dc5a028375"><a name="gga24265f7618fbdba53d3da4806d3097c4a33c37c5ce718e876f43141dc5a028375"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a33c37c5ce718e876f43141dc5a028375"></a></strong>ROP_NOTXORPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909388290093521"><a name="p909388290093521"></a><a name="p909388290093521"></a>~(S2^S1)</p>
<p id="p204710172346"><a name="p204710172346"></a><a name="p204710172346"></a></p>
</td>
</tr>
<tr id="row238839488093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry433011007093521p0"><a name="entry433011007093521p0"></a><a name="entry433011007093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a2acacab882af44bba09878bd58e18695"><a name="gga24265f7618fbdba53d3da4806d3097c4a2acacab882af44bba09878bd58e18695"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a2acacab882af44bba09878bd58e18695"></a></strong>ROP_NOP</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265547613093521"><a name="p265547613093521"></a><a name="p265547613093521"></a>S1</p>
<p id="p9471161753420"><a name="p9471161753420"></a><a name="p9471161753420"></a></p>
</td>
</tr>
<tr id="row2091960290093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1820948014093521p0"><a name="entry1820948014093521p0"></a><a name="entry1820948014093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4afaea3c47612082914332b78ca8c331b3"><a name="gga24265f7618fbdba53d3da4806d3097c4afaea3c47612082914332b78ca8c331b3"></a><a name="gga24265f7618fbdba53d3da4806d3097c4afaea3c47612082914332b78ca8c331b3"></a></strong>ROP_MERGENOTPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566303156093521"><a name="p1566303156093521"></a><a name="p1566303156093521"></a>~S2+S1</p>
<p id="p1447119179348"><a name="p1447119179348"></a><a name="p1447119179348"></a></p>
</td>
</tr>
<tr id="row25910644093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry63916210093521p0"><a name="entry63916210093521p0"></a><a name="entry63916210093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a91bae697f9dea25ac4d7be011958a45d"><a name="gga24265f7618fbdba53d3da4806d3097c4a91bae697f9dea25ac4d7be011958a45d"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a91bae697f9dea25ac4d7be011958a45d"></a></strong>ROP_COPYPE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2067831360093521"><a name="p2067831360093521"></a><a name="p2067831360093521"></a>S2</p>
<p id="p1547131718343"><a name="p1547131718343"></a><a name="p1547131718343"></a></p>
</td>
</tr>
<tr id="row322411600093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1817876204093521p0"><a name="entry1817876204093521p0"></a><a name="entry1817876204093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a3580b77320e4829da046b8739c61d6b8"><a name="gga24265f7618fbdba53d3da4806d3097c4a3580b77320e4829da046b8739c61d6b8"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a3580b77320e4829da046b8739c61d6b8"></a></strong>ROP_MERGEPENNOT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219938126093521"><a name="p1219938126093521"></a><a name="p1219938126093521"></a>S2+~S1</p>
<p id="p947115171344"><a name="p947115171344"></a><a name="p947115171344"></a></p>
</td>
</tr>
<tr id="row1502809730093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry660684361093521p0"><a name="entry660684361093521p0"></a><a name="entry660684361093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a8195ac0d37e0d69b2cd71dd7362d3fd3"><a name="gga24265f7618fbdba53d3da4806d3097c4a8195ac0d37e0d69b2cd71dd7362d3fd3"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a8195ac0d37e0d69b2cd71dd7362d3fd3"></a></strong>ROP_MERGEPEN</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p314309139093521"><a name="p314309139093521"></a><a name="p314309139093521"></a>S2+S1</p>
<p id="p16471131713341"><a name="p16471131713341"></a><a name="p16471131713341"></a></p>
</td>
</tr>
<tr id="row1169409016093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry135647807093521p0"><a name="entry135647807093521p0"></a><a name="entry135647807093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4a533a614b27da8a81b67ada085b018618"><a name="gga24265f7618fbdba53d3da4806d3097c4a533a614b27da8a81b67ada085b018618"></a><a name="gga24265f7618fbdba53d3da4806d3097c4a533a614b27da8a81b67ada085b018618"></a></strong>ROP_WHITE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2063928080093521"><a name="p2063928080093521"></a><a name="p2063928080093521"></a>Whiteness</p>
<p id="p16471181783411"><a name="p16471181783411"></a><a name="p16471181783411"></a></p>
</td>
</tr>
<tr id="row1098168599093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry310011810093521p0"><a name="entry310011810093521p0"></a><a name="entry310011810093521p0"></a><strong id="gga24265f7618fbdba53d3da4806d3097c4aa858b07e214a7f62625e24776806c74b"><a name="gga24265f7618fbdba53d3da4806d3097c4aa858b07e214a7f62625e24776806c74b"></a><a name="gga24265f7618fbdba53d3da4806d3097c4aa858b07e214a7f62625e24776806c74b"></a></strong>ROP_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743074874093521"><a name="p1743074874093521"></a><a name="p1743074874093521"></a>Invalid ROP type</p>
<p id="p2047151773412"><a name="p2047151773412"></a><a name="p2047151773412"></a></p>
</td>
</tr>
</tbody>
</table>

## TransformType<a name="gaa65f3b21a9a92ff022e435a7304126d2"></a>

```
enum [TransformType](Display.md#gaa65f3b21a9a92ff022e435a7304126d2)
```

**Description:**

Enumerates transform types of images.

<a name="table913652312093521"></a>
<table><thead align="left"><tr id="row1779882515093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1368517598093521"><a name="p1368517598093521"></a><a name="p1368517598093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p245269968093521"><a name="p245269968093521"></a><a name="p245269968093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1482262504093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry571685174093521p0"><a name="entry571685174093521p0"></a><a name="entry571685174093521p0"></a><strong id="ggaa65f3b21a9a92ff022e435a7304126d2a68e349e9d45a8eba440e2a7a3ba31ec9"><a name="ggaa65f3b21a9a92ff022e435a7304126d2a68e349e9d45a8eba440e2a7a3ba31ec9"></a><a name="ggaa65f3b21a9a92ff022e435a7304126d2a68e349e9d45a8eba440e2a7a3ba31ec9"></a></strong>ROTATE_NONE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924060052093521"><a name="p924060052093521"></a><a name="p924060052093521"></a>No rotation</p>
<p id="p24861217153417"><a name="p24861217153417"></a><a name="p24861217153417"></a></p>
</td>
</tr>
<tr id="row1013641320093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry732239576093521p0"><a name="entry732239576093521p0"></a><a name="entry732239576093521p0"></a><strong id="ggaa65f3b21a9a92ff022e435a7304126d2a685062467b0c1a3164556335b467c886"><a name="ggaa65f3b21a9a92ff022e435a7304126d2a685062467b0c1a3164556335b467c886"></a><a name="ggaa65f3b21a9a92ff022e435a7304126d2a685062467b0c1a3164556335b467c886"></a></strong>ROTATE_90</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129448426093521"><a name="p129448426093521"></a><a name="p129448426093521"></a>Rotation by 90 degrees</p>
<p id="p104863179345"><a name="p104863179345"></a><a name="p104863179345"></a></p>
</td>
</tr>
<tr id="row1738916452093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1499713299093521p0"><a name="entry1499713299093521p0"></a><a name="entry1499713299093521p0"></a><strong id="ggaa65f3b21a9a92ff022e435a7304126d2a186263164422bb8f0eb5f7b7d195a3d1"><a name="ggaa65f3b21a9a92ff022e435a7304126d2a186263164422bb8f0eb5f7b7d195a3d1"></a><a name="ggaa65f3b21a9a92ff022e435a7304126d2a186263164422bb8f0eb5f7b7d195a3d1"></a></strong>ROTATE_180</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021900127093521"><a name="p1021900127093521"></a><a name="p1021900127093521"></a>Rotation by 180 degrees</p>
<p id="p12486141711341"><a name="p12486141711341"></a><a name="p12486141711341"></a></p>
</td>
</tr>
<tr id="row483184274093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1744142937093521p0"><a name="entry1744142937093521p0"></a><a name="entry1744142937093521p0"></a><strong id="ggaa65f3b21a9a92ff022e435a7304126d2a554e734d2a23790b248c5ce39816c18f"><a name="ggaa65f3b21a9a92ff022e435a7304126d2a554e734d2a23790b248c5ce39816c18f"></a><a name="ggaa65f3b21a9a92ff022e435a7304126d2a554e734d2a23790b248c5ce39816c18f"></a></strong>ROTATE_270</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p588513332093521"><a name="p588513332093521"></a><a name="p588513332093521"></a>Rotation by 270 degrees</p>
<p id="p10486191763416"><a name="p10486191763416"></a><a name="p10486191763416"></a></p>
</td>
</tr>
<tr id="row1207831680093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1147711979093521p0"><a name="entry1147711979093521p0"></a><a name="entry1147711979093521p0"></a><strong id="ggaa65f3b21a9a92ff022e435a7304126d2a9b6ff871536aeef2a8e3ce4a753988ed"><a name="ggaa65f3b21a9a92ff022e435a7304126d2a9b6ff871536aeef2a8e3ce4a753988ed"></a><a name="ggaa65f3b21a9a92ff022e435a7304126d2a9b6ff871536aeef2a8e3ce4a753988ed"></a></strong>ROTATE_BUTT</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1244991359093521"><a name="p1244991359093521"></a><a name="p1244991359093521"></a>Invalid operation</p>
<p id="p11486151753419"><a name="p11486151753419"></a><a name="p11486151753419"></a></p>
</td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1474615936093521"></a>

## GfxInitialize\(\)<a name="ga251580eb0614b601ef2c901c722a59d3"></a>

```
int32_t GfxInitialize ([GfxFuncs](zh-cn_topic_0000001054598159.md) ** funcs)
```

**Description:**

Initializes the hardware acceleration module to obtain the pointer to functions for hardware acceleration operations.

**Parameters:**

<a name="table559949481093521"></a>
<table><thead align="left"><tr id="row385341608093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p285022676093521"><a name="p285022676093521"></a><a name="p285022676093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1646898006093521"><a name="p1646898006093521"></a><a name="p1646898006093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1732458734093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1210010699093521p0"><a name="entry1210010699093521p0"></a><a name="entry1210010699093521p0"></a>funcs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry2005075552093521p0"><a name="entry2005075552093521p0"></a><a name="entry2005075552093521p0"></a>Indicates the double pointer to functions for hardware acceleration operations. Memory is allocated automatically when you initiate the hardware acceleration module, so you can simply use the pointer to gain access to the functions.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise.

**See also:**

[GfxUninitialize](Display.md#ga32595139adb26cfaacf709661b29b347)

## GfxUninitialize\(\)<a name="ga32595139adb26cfaacf709661b29b347"></a>

```
int32_t GfxUninitialize ([GfxFuncs](zh-cn_topic_0000001054598159.md) * funcs)
```

**Description:**

Deinitializes the hardware acceleration module to release the memory allocated to the pointer to functions for hardware acceleration operations.

**Parameters:**

<a name="table153496597093521"></a>
<table><thead align="left"><tr id="row576648322093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1974721832093521"><a name="p1974721832093521"></a><a name="p1974721832093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p77631074093521"><a name="p77631074093521"></a><a name="p77631074093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1121270676093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1116106290093521p0"><a name="entry1116106290093521p0"></a><a name="entry1116106290093521p0"></a>funcs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry692294985093521p0"><a name="entry692294985093521p0"></a><a name="entry692294985093521p0"></a>Indicates the pointer to functions for hardware acceleration operations.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise.

**See also:**

[GfxInitialize](Display.md#ga251580eb0614b601ef2c901c722a59d3)

## GrallocInitialize\(\)<a name="ga304347c32a67bf7b20ef5d2b5714e5fa"></a>

```
int32_t GrallocInitialize ([GrallocFuncs](zh-cn_topic_0000001054918153.md) ** funcs)
```

**Description:**

Initializes the memory module to obtain the pointer to functions for memory operations.

**Parameters:**

<a name="table1274752893093521"></a>
<table><thead align="left"><tr id="row1552112612093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1621929317093521"><a name="p1621929317093521"></a><a name="p1621929317093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p427682954093521"><a name="p427682954093521"></a><a name="p427682954093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row201147711093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry2098393462093521p0"><a name="entry2098393462093521p0"></a><a name="entry2098393462093521p0"></a>funcs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry147147719093521p0"><a name="entry147147719093521p0"></a><a name="entry147147719093521p0"></a>Indicates the double pointer to functions for memory operations. Memory is allocated automatically when you initiate the memory module initialization, so you can simply use the pointer to gain access to the functions.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise.

## GrallocUninitialize\(\)<a name="ga8842b25f91c247606048ab2d5cdb338f"></a>

```
int32_t GrallocUninitialize ([GrallocFuncs](zh-cn_topic_0000001054918153.md) * funcs)
```

**Description:**

Deinitializes the memory module to release the memory allocated to the pointer to functions for memory operations.

**Parameters:**

<a name="table1693994852093521"></a>
<table><thead align="left"><tr id="row150262125093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p152120728093521"><a name="p152120728093521"></a><a name="p152120728093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2109314397093521"><a name="p2109314397093521"></a><a name="p2109314397093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1573660557093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1819169300093521p0"><a name="entry1819169300093521p0"></a><a name="entry1819169300093521p0"></a>funcs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry2013730092093521p0"><a name="entry2013730092093521p0"></a><a name="entry2013730092093521p0"></a>Indicates the pointer to functions for memory operations.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise.

## LayerInitialize\(\)<a name="ga061e587306a5d0367ff228d64434c05d"></a>

```
int32_t LayerInitialize ([LayerFuncs](zh-cn_topic_0000001055678100.md) ** funcs)
```

**Description:**

Initializes the layer to apply for resources used by the layer and obtain the pointer to functions for layer operations.

**Parameters:**

<a name="table159240589093521"></a>
<table><thead align="left"><tr id="row138235506093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p292412721093521"><a name="p292412721093521"></a><a name="p292412721093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p992061626093521"><a name="p992061626093521"></a><a name="p992061626093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1112695776093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry1946187624093521p0"><a name="entry1946187624093521p0"></a><a name="entry1946187624093521p0"></a>funcs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry2030959173093521p0"><a name="entry2030959173093521p0"></a><a name="entry2030959173093521p0"></a>Indicates the double pointer to functions for layer operations. Memory is allocated automatically when you initiate the layer module, so you can simply use the pointer to gain access to the functions.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise.

**See also:**

[LayerUninitialize](Display.md#ga4e32b1a65cf243a9ac015b632a4eea0b)

## LayerUninitialize\(\)<a name="ga4e32b1a65cf243a9ac015b632a4eea0b"></a>

```
int32_t LayerUninitialize ([LayerFuncs](zh-cn_topic_0000001055678100.md) * funcs)
```

**Description:**

Deinitializes the layer module to release the memory allocated to the pointer to functions for layer operations.

**Parameters:**

<a name="table556962458093521"></a>
<table><thead align="left"><tr id="row1430373232093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p20619292093521"><a name="p20619292093521"></a><a name="p20619292093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p869608903093521"><a name="p869608903093521"></a><a name="p869608903093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row879531140093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="entry776809691093521p0"><a name="entry776809691093521p0"></a><a name="entry776809691093521p0"></a>funcs</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="entry1727361236093521p0"><a name="entry1727361236093521p0"></a><a name="entry1727361236093521p0"></a>Indicates the pointer to functions for layer operations.</p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise.

**See also:**

[LayerInitialize](Display.md#ga061e587306a5d0367ff228d64434c05d)

