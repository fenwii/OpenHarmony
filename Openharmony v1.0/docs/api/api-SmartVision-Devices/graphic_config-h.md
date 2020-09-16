# graphic\_config.h<a name="ZH-CN_TOPIC_0000001054479531"></a>

## **Overview**<a name="section1707835830093525"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Provides configuration items required for graphics. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2098924841093525"></a>

## Macros<a name="define-members"></a>

<a name="table303527132093525"></a>
<table><thead align="left"><tr id="row47410996093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p36583760093525"><a name="p36583760093525"></a><a name="p36583760093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p135981805093525"><a name="p135981805093525"></a><a name="p135981805093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2037522554093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p810272622093525"><a name="p810272622093525"></a><a name="p810272622093525"></a><a href="Graphic.md#ga2017774de578acba5afd77793c00205b">VERSION_STANDARD</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row547311273093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p69848423093525"><a name="p69848423093525"></a><a name="p69848423093525"></a><a href="Graphic.md#ga3d83acf19f4d5c59f7a29b6b29440dd2">ENABLE_DMA2D</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445836144093525"><a name="p1445836144093525"></a><a name="p1445836144093525"></a>DMA2D hardware acceleration, which does not take effect on other platforms. </p>
</td>
</tr>
<tr id="row1891407048093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p56399639093525"><a name="p56399639093525"></a><a name="p56399639093525"></a><a href="Graphic.md#gaef5d32e398c657450011db566a5fad04">ENABLE_DMA2D_TEXT</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1332352992093525"><a name="p1332352992093525"></a><a name="p1332352992093525"></a>DMA2D hardware acceleration for font rendering, which does not take effect on other platforms. </p>
</td>
</tr>
<tr id="row795958064093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603368029093525"><a name="p603368029093525"></a><a name="p603368029093525"></a><a href="Graphic.md#ga1a28113245f31cacd0afacc80c7d12c1">ENABLE_ICU</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p574553560093525"><a name="p574553560093525"></a><a name="p574553560093525"></a>Advanced algorithm for line breaks, which is disabled by default on other platforms. </p>
</td>
</tr>
<tr id="row796989853093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850516604093525"><a name="p1850516604093525"></a><a name="p1850516604093525"></a><a href="Graphic.md#ga8fffdbb807e226013ce790500b5c88e2">ENABLE_WINDOW</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96768882093525"><a name="p96768882093525"></a><a name="p96768882093525"></a>Multi-window, which is enabled by default on other platforms. </p>
</td>
</tr>
<tr id="row187968698093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p867060931093525"><a name="p867060931093525"></a><a name="p867060931093525"></a><a href="Graphic.md#gaf319cb3be43a211a63f2ea97a1c3ae6d">ENABLE_FRAME_BUFFER</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551612281093525"><a name="p551612281093525"></a><a name="p551612281093525"></a>Display buffer for rendering data refresh, which is disabled by default on other platforms. </p>
</td>
</tr>
<tr id="row439814104093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p522089926093525"><a name="p522089926093525"></a><a name="p522089926093525"></a><a href="Graphic.md#ga2c3acabc94a483bd191a250f67c1f43b">ENABLE_VECTOR_FONT</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030276411093525"><a name="p1030276411093525"></a><a name="p1030276411093525"></a>Vector type font，which is enabled by default on other platforms. </p>
</td>
</tr>
<tr id="row1346163800093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242432533093525"><a name="p1242432533093525"></a><a name="p1242432533093525"></a><a href="Graphic.md#ga8f198e8500b353e58b618b331f768f27">ENABLE_BUFFER_RGBA</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p918843010093525"><a name="p918843010093525"></a><a name="p918843010093525"></a>Graphics bottom-layer RGBA, which is enabled by default. </p>
</td>
</tr>
<tr id="row415398244093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952719968093525"><a name="p952719968093525"></a><a name="p952719968093525"></a><a href="Graphic.md#ga8508eb8cc5346dbdc552a9fbc11dbb06">ENABLE_HARDWARE_ACCELERATION</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088196012093525"><a name="p2088196012093525"></a><a name="p2088196012093525"></a>Graphics rendering hardware acceleration, which is enabled by default. </p>
</td>
</tr>
<tr id="row1389840068093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p392313786093525"><a name="p392313786093525"></a><a name="p392313786093525"></a><a href="Graphic.md#ga432138093c53d7580af9ec5c5dca387f">ENABLE_DEBUG</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1960487433093525"><a name="p1960487433093525"></a><a name="p1960487433093525"></a>Debug mode, which is disabled by default. </p>
</td>
</tr>
<tr id="row520044965093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p523054699093525"><a name="p523054699093525"></a><a name="p523054699093525"></a><a href="Graphic.md#gaa492b15de59b36af68c10a65952dc870">ENABLE_MEMORY_HOOKS</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1797167417093525"><a name="p1797167417093525"></a><a name="p1797167417093525"></a>Memory hook, which is enabled by default. The system memory allocation is taken over after it is enabled. </p>
</td>
</tr>
<tr id="row1702785548093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8893901093525"><a name="p8893901093525"></a><a name="p8893901093525"></a><a href="Graphic.md#ga4c1dffa1615941394d376b12a8fbdf24">ENABLE_FPS_SUPPORT</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2081076283093525"><a name="p2081076283093525"></a><a name="p2081076283093525"></a>Function for monitoring the image refresh frame rate, which is disabled by default. </p>
</td>
</tr>
<tr id="row1186710559093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906613586093525"><a name="p1906613586093525"></a><a name="p1906613586093525"></a><a href="Graphic.md#ga2e63917ecfb73182bcea30104c497bc9">ENABLE_ANTIALIAS</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p627280984093525"><a name="p627280984093525"></a><a name="p627280984093525"></a>Anti-aliasing, which is enabled by default. </p>
</td>
</tr>
<tr id="row1825270260093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386337764093525"><a name="p386337764093525"></a><a name="p386337764093525"></a><a href="Graphic.md#gaade33b264d4ea661ff8f36976908b4ba">ENABLE_RECT_ANTIALIAS</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782191153093525"><a name="p782191153093525"></a><a name="p782191153093525"></a><a href="Rectangle.md">Rectangle</a> anti-aliasing, which is disabled by default. </p>
</td>
</tr>
<tr id="row341416888093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1368420821093525"><a name="p1368420821093525"></a><a name="p1368420821093525"></a><a href="Graphic.md#ga733acdcb7c5872a7b864ae108cd86413">ENABLE_SPEC_FONT</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375542845093525"><a name="p375542845093525"></a><a name="p375542845093525"></a>Font color mode, which is disabled by default. After it is enabled, the font color mode is set to <strong id="b1081561919093525"><a name="b1081561919093525"></a><a name="b1081561919093525"></a>4</strong> to accelerate font rendering. </p>
</td>
</tr>
<tr id="row2055141376093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323225802093525"><a name="p1323225802093525"></a><a name="p1323225802093525"></a><a href="Graphic.md#ga703e1a14b7cccc8074986836c5c1de02">ENABLE_GRAPHIC_LOG</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868819654093525"><a name="p1868819654093525"></a><a name="p1868819654093525"></a>Log function of a graphics subsystem, which is disabled by default. </p>
</td>
</tr>
<tr id="row1985232573093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p102324167093525"><a name="p102324167093525"></a><a name="p102324167093525"></a><a href="Graphic.md#ga31b6586b78d550c8b08abb87c8ae8d0b">ENABLE_AOD</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902243721093525"><a name="p1902243721093525"></a><a name="p1902243721093525"></a>Function for receiving input events in screen-off mode, which is disabled by default. </p>
</td>
</tr>
<tr id="row272621036093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934619702093525"><a name="p1934619702093525"></a><a name="p1934619702093525"></a><a href="Graphic.md#gaca8a42c138892758d4d3252dddbd1373">GRAPHIC_LOG_LEVEL</a>&nbsp;&nbsp;&nbsp;5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100572682093525"><a name="p100572682093525"></a><a name="p100572682093525"></a>Defines the log level. A smaller value indicates a higher priority. Logs whose priorities are higher than a specified level can be recorded. Log levels: NONE: disabling logs FATAL: fatal level ERROR: error level WARN: warning level INFO: info level DEBUG: debugging level. </p>
</td>
</tr>
<tr id="row500214254093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p779931276093525"><a name="p779931276093525"></a><a name="p779931276093525"></a><a href="Graphic.md#ga70d330906276a996f7dab090a03ce2a5">COLOR_DEPTH</a>&nbsp;&nbsp;&nbsp;32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p230556240093525"><a name="p230556240093525"></a><a name="p230556240093525"></a>Defines the color depth of graphics rendering. The default value is <strong id="b85349709093525"><a name="b85349709093525"></a><a name="b85349709093525"></a>32</strong> bits. The value can be <strong id="b721785868093525"><a name="b721785868093525"></a><a name="b721785868093525"></a>16</strong> or <strong id="b1747962150093525"><a name="b1747962150093525"></a><a name="b1747962150093525"></a>32</strong>. </p>
</td>
</tr>
<tr id="row620989349093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p819165218093525"><a name="p819165218093525"></a><a name="p819165218093525"></a><a href="Graphic.md#ga78a7a5cd4bd7deb45047b3ca9f088fb6">DEFAULT_VECTOR_FONT_FILENAME</a>&nbsp;&nbsp;&nbsp;"SourceHanSansSC-Regular.otf"</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p250748860093525"><a name="p250748860093525"></a><a name="p250748860093525"></a>Defines the file name of default vector font. </p>
</td>
</tr>
</tbody>
</table>

