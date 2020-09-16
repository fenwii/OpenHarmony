# sdio\_if.h<a name="EN-US_TOPIC_0000001054918133"></a>

## **Overview**<a name="section620336583093527"></a>

**Related Modules:**

[SDIO](sdio.md)

**Description:**

Declares the standard SDIO APIs. 

**Since:**

1.0

## **Summary**<a name="section460166360093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table373500756093527"></a>
<table><thead align="left"><tr id="row2054765201093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p928426435093527"><a name="p928426435093527"></a><a name="p928426435093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1045776833093527"><a name="p1045776833093527"></a><a name="p1045776833093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2144733756093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686692731093527"><a name="p686692731093527"></a><a name="p686692731093527"></a><a href="sdiofuncinfo.md">SdioFuncInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101495468093527"><a name="p1101495468093527"></a><a name="p1101495468093527"></a>Defines the SDIO capabilities. </p>
</td>
</tr>
<tr id="row1299902468093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056013779093527"><a name="p2056013779093527"></a><a name="p2056013779093527"></a><a href="sdiocommoninfo.md">SdioCommonInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p186678445093527"><a name="p186678445093527"></a><a name="p186678445093527"></a>Defines SDIO common information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table318757584093527"></a>
<table><thead align="left"><tr id="row1031092721093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p878480039093527"><a name="p878480039093527"></a><a name="p878480039093527"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p495592868093527"><a name="p495592868093527"></a><a name="p495592868093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row688333406093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p872820735093527"><a name="p872820735093527"></a><a name="p872820735093527"></a><a href="sdio.md#ga858bec274683a4f50d53d1f9f43d204b">SdioIrqHandler</a>(void *)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p971496478093527"><a name="p971496478093527"></a><a name="p971496478093527"></a>typedef void </p>
<p id="p563912778093527"><a name="p563912778093527"></a><a name="p563912778093527"></a>Defines the function type of an SDIO IRQ. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table348805231093527"></a>
<table><thead align="left"><tr id="row1765663663093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p896565792093527"><a name="p896565792093527"></a><a name="p896565792093527"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1636314604093527"><a name="p1636314604093527"></a><a name="p1636314604093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1672872858093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1429003366093527"><a name="p1429003366093527"></a><a name="p1429003366093527"></a><a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a> { <a href="sdio.md#gga4037437ac001a9848dd242e8aa632678aa4e25cb3b51d47da78d6b58d11d946cd">SDIO_FUNC_INFO</a> = 0, <a href="sdio.md#gga4037437ac001a9848dd242e8aa632678a7aa994f868190924d0bf354c1bb0d67b">SDIO_OTHER_INFO</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p570634045093527"><a name="p570634045093527"></a><a name="p570634045093527"></a>Enumerates SDIO common information types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table95650607093527"></a>
<table><thead align="left"><tr id="row1736764406093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1323915635093527"><a name="p1323915635093527"></a><a name="p1323915635093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2087410301093527"><a name="p2087410301093527"></a><a name="p2087410301093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1685307285093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460103277093527"><a name="p1460103277093527"></a><a name="p1460103277093527"></a><a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a> (int16_t busNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061511309093527"><a name="p1061511309093527"></a><a name="p1061511309093527"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1692586144093527"><a name="p1692586144093527"></a><a name="p1692586144093527"></a>Opens an SDIO controller with a specified bus number. </p>
</td>
</tr>
<tr id="row1606912840093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p252187722093527"><a name="p252187722093527"></a><a name="p252187722093527"></a><a href="sdio.md#ga15427d4b231423c6de812fedffbd61e3">SdioClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779357974093527"><a name="p779357974093527"></a><a name="p779357974093527"></a>void </p>
<p id="p395510129093527"><a name="p395510129093527"></a><a name="p395510129093527"></a>Closes an SDIO controller. </p>
</td>
</tr>
<tr id="row1790990103093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p310831698093527"><a name="p310831698093527"></a><a name="p310831698093527"></a><a href="sdio.md#ga274a9b0ed15c1b4ab961344c74c34304">SdioReadBytes</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051363363093527"><a name="p2051363363093527"></a><a name="p2051363363093527"></a>int32_t </p>
<p id="p405305099093527"><a name="p405305099093527"></a><a name="p405305099093527"></a>Incrementally reads a given length of data from the specified SDIO address. </p>
</td>
</tr>
<tr id="row290900429093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953056535093527"><a name="p1953056535093527"></a><a name="p1953056535093527"></a><a href="sdio.md#ga4daf7bbcb80e38804225ccbaaa496d90">SdioWriteBytes</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p534397445093527"><a name="p534397445093527"></a><a name="p534397445093527"></a>int32_t </p>
<p id="p709757074093527"><a name="p709757074093527"></a><a name="p709757074093527"></a>Incrementally writes a given length of data into the specified SDIO address. </p>
</td>
</tr>
<tr id="row1487234683093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503102571093527"><a name="p1503102571093527"></a><a name="p1503102571093527"></a><a href="sdio.md#ga78ce6ad2dd6e0e8d74086702897a106f">SdioReadBytesFromFixedAddr</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1134602047093527"><a name="p1134602047093527"></a><a name="p1134602047093527"></a>int32_t </p>
<p id="p1419075222093527"><a name="p1419075222093527"></a><a name="p1419075222093527"></a>Reads a given length of data from the fixed SDIO address. </p>
</td>
</tr>
<tr id="row973211294093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p130779472093527"><a name="p130779472093527"></a><a name="p130779472093527"></a><a href="sdio.md#gae2bffd43990954fb1da9f9c6866c4018">SdioWriteBytesToFixedAddr</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2118875638093527"><a name="p2118875638093527"></a><a name="p2118875638093527"></a>int32_t </p>
<p id="p1734809374093527"><a name="p1734809374093527"></a><a name="p1734809374093527"></a>Writes a given length of data into the fixed SDIO address. </p>
</td>
</tr>
<tr id="row324313615093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p67036297093527"><a name="p67036297093527"></a><a name="p67036297093527"></a><a href="sdio.md#gaed3257012d57f3b12be6da1867a66c31">SdioReadBytesFromFunc0</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1464346952093527"><a name="p1464346952093527"></a><a name="p1464346952093527"></a>int32_t </p>
<p id="p1267871168093527"><a name="p1267871168093527"></a><a name="p1267871168093527"></a>Reads a given length of data from the address space of SDIO function 0. </p>
</td>
</tr>
<tr id="row1984529484093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p532480187093527"><a name="p532480187093527"></a><a name="p532480187093527"></a><a href="sdio.md#gace26ab5ab8cfe037b6d6e132a045a7e0">SdioWriteBytesToFunc0</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094935302093527"><a name="p2094935302093527"></a><a name="p2094935302093527"></a>int32_t </p>
<p id="p307915212093527"><a name="p307915212093527"></a><a name="p307915212093527"></a>Writes a given length of data into the address space of SDIO function 0. </p>
</td>
</tr>
<tr id="row1724765618093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1957520679093527"><a name="p1957520679093527"></a><a name="p1957520679093527"></a><a href="sdio.md#gad8e070346da466f5f2d68d1d7d18a738">SdioSetBlockSize</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t blockSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165187585093527"><a name="p1165187585093527"></a><a name="p1165187585093527"></a>int32_t </p>
<p id="p779107638093527"><a name="p779107638093527"></a><a name="p779107638093527"></a>Sets the block size. </p>
</td>
</tr>
<tr id="row1782260416093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1599248429093527"><a name="p1599248429093527"></a><a name="p1599248429093527"></a><a href="sdio.md#gac5c6bf733ea9e4408fd1109b18741ce8">SdioGetCommonInfo</a> (struct <a href="devhandle.md">DevHandle</a> *handle, <a href="sdiocommoninfo.md">SdioCommonInfo</a> *info, <a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a> infoType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084218452093527"><a name="p1084218452093527"></a><a name="p1084218452093527"></a>int32_t </p>
<p id="p1378709499093527"><a name="p1378709499093527"></a><a name="p1378709499093527"></a>Obtains common information. </p>
</td>
</tr>
<tr id="row680838212093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755596232093527"><a name="p1755596232093527"></a><a name="p1755596232093527"></a><a href="sdio.md#ga563b67c90fbb88075bf5a05d9b5d5706">SdioSetCommonInfo</a> (struct <a href="devhandle.md">DevHandle</a> *handle, <a href="sdiocommoninfo.md">SdioCommonInfo</a> *info, <a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a> infoType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1993211705093527"><a name="p1993211705093527"></a><a name="p1993211705093527"></a>int32_t </p>
<p id="p266812401093527"><a name="p266812401093527"></a><a name="p266812401093527"></a>Sets common information. </p>
</td>
</tr>
<tr id="row1185998328093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1052947801093527"><a name="p1052947801093527"></a><a name="p1052947801093527"></a><a href="sdio.md#gae5a7c821bfd483a676227c29895d08bc">SdioFlushData</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168461386093527"><a name="p168461386093527"></a><a name="p168461386093527"></a>int32_t </p>
<p id="p584641785093527"><a name="p584641785093527"></a><a name="p584641785093527"></a>Flushes data. </p>
</td>
</tr>
<tr id="row814051288093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1104487683093527"><a name="p1104487683093527"></a><a name="p1104487683093527"></a><a href="sdio.md#ga86e24b0480c860cfad8ff12fbc66bc9f">SdioClaimHost</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184583510093527"><a name="p1184583510093527"></a><a name="p1184583510093527"></a>void </p>
<p id="p513377809093527"><a name="p513377809093527"></a><a name="p513377809093527"></a>Claims a host exclusively. </p>
</td>
</tr>
<tr id="row175002314093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p337402827093527"><a name="p337402827093527"></a><a name="p337402827093527"></a><a href="sdio.md#gabd2fe2d978e7fde51eba584f30dc8e7c">SdioReleaseHost</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1077861665093527"><a name="p1077861665093527"></a><a name="p1077861665093527"></a>void </p>
<p id="p493818075093527"><a name="p493818075093527"></a><a name="p493818075093527"></a>Releases the exclusively claimed host. </p>
</td>
</tr>
<tr id="row1284330069093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1085108008093527"><a name="p1085108008093527"></a><a name="p1085108008093527"></a><a href="sdio.md#ga2f31cd318990db879e827e3b8f9f2393">SdioEnableFunc</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1203608503093527"><a name="p1203608503093527"></a><a name="p1203608503093527"></a>int32_t </p>
<p id="p1364140771093527"><a name="p1364140771093527"></a><a name="p1364140771093527"></a>Enables the SDIO device so that its register can be accessed. </p>
</td>
</tr>
<tr id="row1491790156093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2143959607093527"><a name="p2143959607093527"></a><a name="p2143959607093527"></a><a href="sdio.md#gaabe2a2c83401940ed163feb692f3efc3">SdioDisableFunc</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365427742093527"><a name="p1365427742093527"></a><a name="p1365427742093527"></a>int32_t </p>
<p id="p1840882325093527"><a name="p1840882325093527"></a><a name="p1840882325093527"></a>Disables the SDIO device. </p>
</td>
</tr>
<tr id="row1746054416093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1530334307093527"><a name="p1530334307093527"></a><a name="p1530334307093527"></a><a href="sdio.md#ga81f98e541845c15a632cf59cd9c263f8">SdioClaimIrq</a> (struct <a href="devhandle.md">DevHandle</a> *handle, <a href="sdio.md#ga858bec274683a4f50d53d1f9f43d204b">SdioIrqHandler</a> *irqHandler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016710629093527"><a name="p1016710629093527"></a><a name="p1016710629093527"></a>int32_t </p>
<p id="p1377642477093527"><a name="p1377642477093527"></a><a name="p1377642477093527"></a>Claims an SDIO IRQ. </p>
</td>
</tr>
<tr id="row694356972093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p304671525093527"><a name="p304671525093527"></a><a name="p304671525093527"></a><a href="sdio.md#ga309d2ff3b603994d6c031b726aa8a305">SdioReleaseIrq</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p430960217093527"><a name="p430960217093527"></a><a name="p430960217093527"></a>int32_t </p>
<p id="p1010237191093527"><a name="p1010237191093527"></a><a name="p1010237191093527"></a>Releases an SDIO IRQ. </p>
</td>
</tr>
</tbody>
</table>

