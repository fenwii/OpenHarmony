# SDIO<a name="EN-US_TOPIC_0000001055678042"></a>

## **Overview**<a name="section1502965549093521"></a>

Declares standard APIs of basic secure digital input and output \(SDIO\) capabilities. 

You can use this module to access the SDIO and enable the driver to operate an SDIO-compliant device. These capabilities include reading and writing data based on SDIO, setting the block size, applying for and releasing interrupts, enabling and disabling devices, and occupying and releasing the bus.

**Since:**

1.0

## **Summary**<a name="section1082613086093521"></a>

## Files<a name="files"></a>

<a name="table358384044093521"></a>
<table><thead align="left"><tr id="row1530939187093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1173097328093521"><a name="p1173097328093521"></a><a name="p1173097328093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1026921565093521"><a name="p1026921565093521"></a><a name="p1026921565093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1141730278093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886511688093521"><a name="p1886511688093521"></a><a name="p1886511688093521"></a><a href="sdio_if-h.md">sdio_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700515241093521"><a name="p1700515241093521"></a><a name="p1700515241093521"></a>Declares the standard SDIO APIs. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table54075203093521"></a>
<table><thead align="left"><tr id="row917125872093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p227473209093521"><a name="p227473209093521"></a><a name="p227473209093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1637626164093521"><a name="p1637626164093521"></a><a name="p1637626164093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row712284064093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p940230443093521"><a name="p940230443093521"></a><a name="p940230443093521"></a><a href="sdiofuncinfo.md">SdioFuncInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199973939093521"><a name="p1199973939093521"></a><a name="p1199973939093521"></a>Defines the SDIO capabilities. </p>
</td>
</tr>
<tr id="row1937839706093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1880344750093521"><a name="p1880344750093521"></a><a name="p1880344750093521"></a><a href="sdiocommoninfo.md">SdioCommonInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800936819093521"><a name="p800936819093521"></a><a name="p800936819093521"></a>Defines SDIO common information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table650262017093521"></a>
<table><thead align="left"><tr id="row204816141093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1057566833093521"><a name="p1057566833093521"></a><a name="p1057566833093521"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1004585508093521"><a name="p1004585508093521"></a><a name="p1004585508093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row739855849093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996116088093521"><a name="p996116088093521"></a><a name="p996116088093521"></a><a href="sdio.md#ga858bec274683a4f50d53d1f9f43d204b">SdioIrqHandler</a>(void *)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673184254093521"><a name="p1673184254093521"></a><a name="p1673184254093521"></a>typedef void </p>
<p id="p1165807439093521"><a name="p1165807439093521"></a><a name="p1165807439093521"></a>Defines the function type of an SDIO IRQ. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table499135497093521"></a>
<table><thead align="left"><tr id="row1956670252093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p781209473093521"><a name="p781209473093521"></a><a name="p781209473093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p199347866093521"><a name="p199347866093521"></a><a name="p199347866093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row659342449093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250620675093521"><a name="p250620675093521"></a><a name="p250620675093521"></a><a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a> { <a href="sdio.md#gga4037437ac001a9848dd242e8aa632678aa4e25cb3b51d47da78d6b58d11d946cd">SDIO_FUNC_INFO</a> = 0, <a href="sdio.md#gga4037437ac001a9848dd242e8aa632678a7aa994f868190924d0bf354c1bb0d67b">SDIO_OTHER_INFO</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491162443093521"><a name="p491162443093521"></a><a name="p491162443093521"></a>Enumerates SDIO common information types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2041822298093521"></a>
<table><thead align="left"><tr id="row1042110697093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1261466832093521"><a name="p1261466832093521"></a><a name="p1261466832093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1780200296093521"><a name="p1780200296093521"></a><a name="p1780200296093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row12113101093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p992391195093521"><a name="p992391195093521"></a><a name="p992391195093521"></a><a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a> (int16_t busNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1335213774093521"><a name="p1335213774093521"></a><a name="p1335213774093521"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1665156749093521"><a name="p1665156749093521"></a><a name="p1665156749093521"></a>Opens an SDIO controller with a specified bus number. </p>
</td>
</tr>
<tr id="row2074470592093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1193210526093521"><a name="p1193210526093521"></a><a name="p1193210526093521"></a><a href="sdio.md#ga15427d4b231423c6de812fedffbd61e3">SdioClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115934128093521"><a name="p115934128093521"></a><a name="p115934128093521"></a>void </p>
<p id="p820541544093521"><a name="p820541544093521"></a><a name="p820541544093521"></a>Closes an SDIO controller. </p>
</td>
</tr>
<tr id="row246831540093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292036525093521"><a name="p1292036525093521"></a><a name="p1292036525093521"></a><a href="sdio.md#ga274a9b0ed15c1b4ab961344c74c34304">SdioReadBytes</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p394512756093521"><a name="p394512756093521"></a><a name="p394512756093521"></a>int32_t </p>
<p id="p100187598093521"><a name="p100187598093521"></a><a name="p100187598093521"></a>Incrementally reads a given length of data from the specified SDIO address. </p>
</td>
</tr>
<tr id="row178475772093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785212812093521"><a name="p1785212812093521"></a><a name="p1785212812093521"></a><a href="sdio.md#ga4daf7bbcb80e38804225ccbaaa496d90">SdioWriteBytes</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2099986850093521"><a name="p2099986850093521"></a><a name="p2099986850093521"></a>int32_t </p>
<p id="p1199546668093521"><a name="p1199546668093521"></a><a name="p1199546668093521"></a>Incrementally writes a given length of data into the specified SDIO address. </p>
</td>
</tr>
<tr id="row1278083929093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762187315093521"><a name="p1762187315093521"></a><a name="p1762187315093521"></a><a href="sdio.md#ga78ce6ad2dd6e0e8d74086702897a106f">SdioReadBytesFromFixedAddr</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2063275176093521"><a name="p2063275176093521"></a><a name="p2063275176093521"></a>int32_t </p>
<p id="p498999545093521"><a name="p498999545093521"></a><a name="p498999545093521"></a>Reads a given length of data from the fixed SDIO address. </p>
</td>
</tr>
<tr id="row1883778016093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1943796427093521"><a name="p1943796427093521"></a><a name="p1943796427093521"></a><a href="sdio.md#gae2bffd43990954fb1da9f9c6866c4018">SdioWriteBytesToFixedAddr</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443139987093521"><a name="p1443139987093521"></a><a name="p1443139987093521"></a>int32_t </p>
<p id="p731405899093521"><a name="p731405899093521"></a><a name="p731405899093521"></a>Writes a given length of data into the fixed SDIO address. </p>
</td>
</tr>
<tr id="row2054189706093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328763186093521"><a name="p328763186093521"></a><a name="p328763186093521"></a><a href="sdio.md#gaed3257012d57f3b12be6da1867a66c31">SdioReadBytesFromFunc0</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846143447093521"><a name="p846143447093521"></a><a name="p846143447093521"></a>int32_t </p>
<p id="p19637275093521"><a name="p19637275093521"></a><a name="p19637275093521"></a>Reads a given length of data from the address space of SDIO function 0. </p>
</td>
</tr>
<tr id="row521019527093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p129199027093521"><a name="p129199027093521"></a><a name="p129199027093521"></a><a href="sdio.md#gace26ab5ab8cfe037b6d6e132a045a7e0">SdioWriteBytesToFunc0</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t addr, uint32_t size, uint32_t timeOut)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829617544093521"><a name="p829617544093521"></a><a name="p829617544093521"></a>int32_t </p>
<p id="p132557401093521"><a name="p132557401093521"></a><a name="p132557401093521"></a>Writes a given length of data into the address space of SDIO function 0. </p>
</td>
</tr>
<tr id="row1572140813093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1957228703093521"><a name="p1957228703093521"></a><a name="p1957228703093521"></a><a href="sdio.md#gad8e070346da466f5f2d68d1d7d18a738">SdioSetBlockSize</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t blockSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p301642658093521"><a name="p301642658093521"></a><a name="p301642658093521"></a>int32_t </p>
<p id="p183444459093521"><a name="p183444459093521"></a><a name="p183444459093521"></a>Sets the block size. </p>
</td>
</tr>
<tr id="row805217635093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241444661093521"><a name="p241444661093521"></a><a name="p241444661093521"></a><a href="sdio.md#gac5c6bf733ea9e4408fd1109b18741ce8">SdioGetCommonInfo</a> (struct <a href="devhandle.md">DevHandle</a> *handle, <a href="sdiocommoninfo.md">SdioCommonInfo</a> *info, <a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a> infoType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1936100396093521"><a name="p1936100396093521"></a><a name="p1936100396093521"></a>int32_t </p>
<p id="p25185804093521"><a name="p25185804093521"></a><a name="p25185804093521"></a>Obtains common information. </p>
</td>
</tr>
<tr id="row991461248093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p314052752093521"><a name="p314052752093521"></a><a name="p314052752093521"></a><a href="sdio.md#ga563b67c90fbb88075bf5a05d9b5d5706">SdioSetCommonInfo</a> (struct <a href="devhandle.md">DevHandle</a> *handle, <a href="sdiocommoninfo.md">SdioCommonInfo</a> *info, <a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a> infoType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941162057093521"><a name="p1941162057093521"></a><a name="p1941162057093521"></a>int32_t </p>
<p id="p2061717887093521"><a name="p2061717887093521"></a><a name="p2061717887093521"></a>Sets common information. </p>
</td>
</tr>
<tr id="row282048750093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1466582138093521"><a name="p1466582138093521"></a><a name="p1466582138093521"></a><a href="sdio.md#gae5a7c821bfd483a676227c29895d08bc">SdioFlushData</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1605730652093521"><a name="p1605730652093521"></a><a name="p1605730652093521"></a>int32_t </p>
<p id="p2111394427093521"><a name="p2111394427093521"></a><a name="p2111394427093521"></a>Flushes data. </p>
</td>
</tr>
<tr id="row268889763093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1578641189093521"><a name="p1578641189093521"></a><a name="p1578641189093521"></a><a href="sdio.md#ga86e24b0480c860cfad8ff12fbc66bc9f">SdioClaimHost</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2133102691093521"><a name="p2133102691093521"></a><a name="p2133102691093521"></a>void </p>
<p id="p1493737635093521"><a name="p1493737635093521"></a><a name="p1493737635093521"></a>Claims a host exclusively. </p>
</td>
</tr>
<tr id="row1254701727093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382167776093521"><a name="p382167776093521"></a><a name="p382167776093521"></a><a href="sdio.md#gabd2fe2d978e7fde51eba584f30dc8e7c">SdioReleaseHost</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p172498001093521"><a name="p172498001093521"></a><a name="p172498001093521"></a>void </p>
<p id="p940814814093521"><a name="p940814814093521"></a><a name="p940814814093521"></a>Releases the exclusively claimed host. </p>
</td>
</tr>
<tr id="row262573471093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1037045944093521"><a name="p1037045944093521"></a><a name="p1037045944093521"></a><a href="sdio.md#ga2f31cd318990db879e827e3b8f9f2393">SdioEnableFunc</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510520618093521"><a name="p1510520618093521"></a><a name="p1510520618093521"></a>int32_t </p>
<p id="p2068308571093521"><a name="p2068308571093521"></a><a name="p2068308571093521"></a>Enables the SDIO device so that its register can be accessed. </p>
</td>
</tr>
<tr id="row1632671093093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2031699561093521"><a name="p2031699561093521"></a><a name="p2031699561093521"></a><a href="sdio.md#gaabe2a2c83401940ed163feb692f3efc3">SdioDisableFunc</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854350571093521"><a name="p854350571093521"></a><a name="p854350571093521"></a>int32_t </p>
<p id="p338416749093521"><a name="p338416749093521"></a><a name="p338416749093521"></a>Disables the SDIO device. </p>
</td>
</tr>
<tr id="row661708051093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1410015653093521"><a name="p1410015653093521"></a><a name="p1410015653093521"></a><a href="sdio.md#ga81f98e541845c15a632cf59cd9c263f8">SdioClaimIrq</a> (struct <a href="devhandle.md">DevHandle</a> *handle, <a href="sdio.md#ga858bec274683a4f50d53d1f9f43d204b">SdioIrqHandler</a> *irqHandler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1875325263093521"><a name="p1875325263093521"></a><a name="p1875325263093521"></a>int32_t </p>
<p id="p1717109204093521"><a name="p1717109204093521"></a><a name="p1717109204093521"></a>Claims an SDIO IRQ. </p>
</td>
</tr>
<tr id="row389683943093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p358520322093521"><a name="p358520322093521"></a><a name="p358520322093521"></a><a href="sdio.md#ga309d2ff3b603994d6c031b726aa8a305">SdioReleaseIrq</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902748560093521"><a name="p1902748560093521"></a><a name="p1902748560093521"></a>int32_t </p>
<p id="p1760011885093521"><a name="p1760011885093521"></a><a name="p1760011885093521"></a>Releases an SDIO IRQ. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section541879477093521"></a>

## **Typedef Documentation**<a name="section523785948093521"></a>

## SdioIrqHandler<a name="ga858bec274683a4f50d53d1f9f43d204b"></a>

```
typedef void SdioIrqHandler(void *)
```

 **Description:**

Defines the function type of an SDIO IRQ. 

This function is registered when you call  [SdioClaimIrq](sdio.md#ga81f98e541845c15a632cf59cd9c263f8)  to request the SDIO IRQ.

**Parameters:**

<a name="table663722514093521"></a>
<table><thead align="left"><tr id="row655106360093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1615362312093521"><a name="p1615362312093521"></a><a name="p1615362312093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1604471786093521"><a name="p1604471786093521"></a><a name="p1604471786093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row623759612093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the private data passed to this IRQ (The data is specified when the IRQ is registered).</td>
</tr>
</tbody>
</table>

## **Enumeration Type Documentation**<a name="section219003218093521"></a>

## SdioCommonInfoType<a name="ga4037437ac001a9848dd242e8aa632678"></a>

```
enum [SdioCommonInfoType](sdio.md#ga4037437ac001a9848dd242e8aa632678)
```

 **Description:**

Enumerates SDIO common information types. 

When obtaining SDIO common information by calling  [SdioGetCommonInfo](sdio.md#gac5c6bf733ea9e4408fd1109b18741ce8)  or setting the information by calling  [SdioSetCommonInfo](sdio.md#ga563b67c90fbb88075bf5a05d9b5d5706), you need to pass the information type. 

<a name="table1855813203093521"></a>
<table><thead align="left"><tr id="row105099053093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p453280380093521"><a name="p453280380093521"></a><a name="p453280380093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p472039072093521"><a name="p472039072093521"></a><a name="p472039072093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row936422258093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga4037437ac001a9848dd242e8aa632678aa4e25cb3b51d47da78d6b58d11d946cd"><a name="gga4037437ac001a9848dd242e8aa632678aa4e25cb3b51d47da78d6b58d11d946cd"></a><a name="gga4037437ac001a9848dd242e8aa632678aa4e25cb3b51d47da78d6b58d11d946cd"></a></strong>SDIO_FUNC_INFO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p674625696093521"><a name="p674625696093521"></a><a name="p674625696093521"></a>Functionality information </p>
 </td>
</tr>
<tr id="row408912188093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga4037437ac001a9848dd242e8aa632678a7aa994f868190924d0bf354c1bb0d67b"><a name="gga4037437ac001a9848dd242e8aa632678a7aa994f868190924d0bf354c1bb0d67b"></a><a name="gga4037437ac001a9848dd242e8aa632678a7aa994f868190924d0bf354c1bb0d67b"></a></strong>SDIO_OTHER_INFO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914756430093521"><a name="p1914756430093521"></a><a name="p1914756430093521"></a>Other information </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section318738832093521"></a>

## SdioClaimHost\(\)<a name="ga86e24b0480c860cfad8ff12fbc66bc9f"></a>

```
void SdioClaimHost (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Claims a host exclusively. 

You can call this function to enable the SDIO module to exclusively claim a host and then perform operations on the devices connected to the host. After performing required operations, release the host by calling  [SdioReleaseHost](sdio.md#gabd2fe2d978e7fde51eba584f30dc8e7c).

**Parameters:**

<a name="table1032488634093521"></a>
<table><thead align="left"><tr id="row2147008853093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2086040061093521"><a name="p2086040061093521"></a><a name="p2086040061093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p900061921093521"><a name="p900061921093521"></a><a name="p900061921093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row522622123093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>.</td>
</tr>
</tbody>
</table>

## SdioClaimIrq\(\)<a name="ga81f98e541845c15a632cf59cd9c263f8"></a>

```
int32_t SdioClaimIrq (struct [DevHandle](devhandle.md) * handle, [SdioIrqHandler](sdio.md#ga858bec274683a4f50d53d1f9f43d204b) * irqHandler )
```

 **Description:**

Claims an SDIO IRQ. 

When there is data, commands, or events, the IRQ function is executed.

**Parameters:**

<a name="table1877535021093521"></a>
<table><thead align="left"><tr id="row465971894093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1905903471093521"><a name="p1905903471093521"></a><a name="p1905903471093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1617545554093521"><a name="p1617545554093521"></a><a name="p1617545554093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1034886858093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row1787715877093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">irqHandler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SDIO IRQ function. For details, see <a href="sdio.md#ga858bec274683a4f50d53d1f9f43d204b">SdioIrqHandler</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioClose\(\)<a name="ga15427d4b231423c6de812fedffbd61e3"></a>

```
void SdioClose (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Closes an SDIO controller. 

After the SDIO interface is used, you can close the SDIO controller by calling  [SdioClose](sdio.md#ga15427d4b231423c6de812fedffbd61e3). This function is used in pair with  [SdioOpen](sdio.md#gadca7b0edcae3df85b3ade33704a306f8).

**Parameters:**

<a name="table1275793212093521"></a>
<table><thead align="left"><tr id="row1658150651093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p355271575093521"><a name="p355271575093521"></a><a name="p355271575093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p618707820093521"><a name="p618707820093521"></a><a name="p618707820093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1148892134093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller.</td>
</tr>
</tbody>
</table>

## SdioDisableFunc\(\)<a name="gaabe2a2c83401940ed163feb692f3efc3"></a>

```
int32_t SdioDisableFunc (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Disables the SDIO device. 

This function is used in pair with  [SdioEnableFunc](sdio.md#ga2f31cd318990db879e827e3b8f9f2393).

**Parameters:**

<a name="table829682249093521"></a>
<table><thead align="left"><tr id="row12515769093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1808583773093521"><a name="p1808583773093521"></a><a name="p1808583773093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p742498146093521"><a name="p742498146093521"></a><a name="p742498146093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1951394195093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioEnableFunc\(\)<a name="ga2f31cd318990db879e827e3b8f9f2393"></a>

```
int32_t SdioEnableFunc (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Enables the SDIO device so that its register can be accessed. 

**Parameters:**

<a name="table1546260656093521"></a>
<table><thead align="left"><tr id="row1785098719093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1605563093093521"><a name="p1605563093093521"></a><a name="p1605563093093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2034352675093521"><a name="p2034352675093521"></a><a name="p2034352675093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1672534765093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioFlushData\(\)<a name="gae5a7c821bfd483a676227c29895d08bc"></a>

```
int32_t SdioFlushData (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Flushes data. 

You can call this function when an SDIO needs to be reinitialized or an unexpected error occurs.

**Parameters:**

<a name="table1844324148093521"></a>
<table><thead align="left"><tr id="row1007800963093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1163141837093521"><a name="p1163141837093521"></a><a name="p1163141837093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p422772888093521"><a name="p422772888093521"></a><a name="p422772888093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1977125136093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioGetCommonInfo\(\)<a name="gac5c6bf733ea9e4408fd1109b18741ce8"></a>

```
int32_t SdioGetCommonInfo (struct [DevHandle](devhandle.md) * handle, [SdioCommonInfo](sdiocommoninfo.md) * info, [SdioCommonInfoType](sdio.md#ga4037437ac001a9848dd242e8aa632678) infoType )
```

 **Description:**

Obtains common information. 

You can call this function to obtain the capabilities and private data of the I/O function.

**Parameters:**

<a name="table344395804093521"></a>
<table><thead align="left"><tr id="row854623900093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p121177042093521"><a name="p121177042093521"></a><a name="p121177042093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1168811481093521"><a name="p1168811481093521"></a><a name="p1168811481093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row692197638093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row869981547093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the common information to be obtained. For details, see <a href="sdiocommoninfo.md">SdioCommonInfo</a>. </td>
</tr>
<tr id="row2105866485093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">infoType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the common information to be obtained. For details, see <a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioOpen\(\)<a name="gadca7b0edcae3df85b3ade33704a306f8"></a>

```
struct [DevHandle](devhandle.md)* SdioOpen (int16_t busNum)
```

 **Description:**

Opens an SDIO controller with a specified bus number. 

Before using the SDIO interface, you can obtain the device handle of the SDIO controller by calling  [SdioOpen](sdio.md#gadca7b0edcae3df85b3ade33704a306f8). This function is used in pair with  [SdioClose](sdio.md#ga15427d4b231423c6de812fedffbd61e3).

**Parameters:**

<a name="table1111294146093521"></a>
<table><thead align="left"><tr id="row1022156567093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p195375023093521"><a name="p195375023093521"></a><a name="p195375023093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1036600373093521"><a name="p1036600373093521"></a><a name="p1036600373093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row909166475093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">busNum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the bus number.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the device handle  [DevHandle](devhandle.md)  of the SDIO controller if the operation is successful; returns  **NULL**  otherwise. 



## SdioReadBytes\(\)<a name="ga274a9b0ed15c1b4ab961344c74c34304"></a>

```
int32_t SdioReadBytes (struct [DevHandle](devhandle.md) * handle, uint8_t * data, uint32_t addr, uint32_t size, uint32_t timeOut )
```

 **Description:**

Incrementally reads a given length of data from the specified SDIO address. 

If the length of the data to read is greater than the size of a block, the data is read by block, and the remaining data that is smaller than one block is read by byte. Otherwise, data is read by byte.

**Parameters:**

<a name="table1025575442093521"></a>
<table><thead align="left"><tr id="row539957154093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1406588321093521"><a name="p1406588321093521"></a><a name="p1406588321093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p546280427093521"><a name="p546280427093521"></a><a name="p546280427093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1238652636093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row2113087413093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to read. </td>
</tr>
<tr id="row391375230093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start address of the data to read. </td>
</tr>
<tr id="row1007713577093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to read. </td>
</tr>
<tr id="row50851260093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for reading data, in milliseconds. If the value is <strong id="b283299423093521"><a name="b283299423093521"></a><a name="b283299423093521"></a>0</strong>,the default value is used. The default value varies according to the application. Generally, the default value is <strong id="b1356888222093521"><a name="b1356888222093521"></a><a name="b1356888222093521"></a>1</strong> second.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioReadBytesFromFixedAddr\(\)<a name="ga78ce6ad2dd6e0e8d74086702897a106f"></a>

```
int32_t SdioReadBytesFromFixedAddr (struct [DevHandle](devhandle.md) * handle, uint8_t * data, uint32_t addr, uint32_t size, uint32_t timeOut )
```

 **Description:**

Reads a given length of data from the fixed SDIO address. 

If the length of the data to read is greater than the size of a block, the data is read by block, and the remaining data that is smaller than one block is read by byte. Otherwise, data is read by byte.

**Parameters:**

<a name="table1825077675093521"></a>
<table><thead align="left"><tr id="row1186293101093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p506955628093521"><a name="p506955628093521"></a><a name="p506955628093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1575226023093521"><a name="p1575226023093521"></a><a name="p1575226023093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row236485686093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row730848319093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to read. </td>
</tr>
<tr id="row1667016473093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the fixed address of the data to read. </td>
</tr>
<tr id="row876924867093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to read. </td>
</tr>
<tr id="row874519102093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for reading data, in milliseconds. If the value is <strong id="b981580292093521"><a name="b981580292093521"></a><a name="b981580292093521"></a>0</strong>, the default value is used. The default value varies according to the application. Generally, the default value is <strong id="b782583931093521"><a name="b782583931093521"></a><a name="b782583931093521"></a>1</strong> second.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioReadBytesFromFunc0\(\)<a name="gaed3257012d57f3b12be6da1867a66c31"></a>

```
int32_t SdioReadBytesFromFunc0 (struct [DevHandle](devhandle.md) * handle, uint8_t * data, uint32_t addr, uint32_t size, uint32_t timeOut )
```

 **Description:**

Reads a given length of data from the address space of SDIO function 0. 

Currently, only one byte of data can be read.

**Parameters:**

<a name="table1545927539093521"></a>
<table><thead align="left"><tr id="row506852630093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p596417145093521"><a name="p596417145093521"></a><a name="p596417145093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p771038819093521"><a name="p771038819093521"></a><a name="p771038819093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1025870798093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row198642918093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to read. </td>
</tr>
<tr id="row533646319093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start address of the data to read. </td>
</tr>
<tr id="row1979725897093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to read. </td>
</tr>
<tr id="row1890045957093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for reading data, in milliseconds. If the value is <strong id="b518479572093521"><a name="b518479572093521"></a><a name="b518479572093521"></a>0</strong>, the default value is used. The default value varies according to the application. Generally, the default value is <strong id="b92717147093521"><a name="b92717147093521"></a><a name="b92717147093521"></a>1</strong> second.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioReleaseHost\(\)<a name="gabd2fe2d978e7fde51eba584f30dc8e7c"></a>

```
void SdioReleaseHost (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Releases the exclusively claimed host. 

This function is used in pair with  [SdioClaimHost](sdio.md#ga86e24b0480c860cfad8ff12fbc66bc9f).

**Parameters:**

<a name="table802329491093521"></a>
<table><thead align="left"><tr id="row1797607361093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1720927117093521"><a name="p1720927117093521"></a><a name="p1720927117093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p406098729093521"><a name="p406098729093521"></a><a name="p406098729093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1978656463093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>.</td>
</tr>
</tbody>
</table>

## SdioReleaseIrq\(\)<a name="ga309d2ff3b603994d6c031b726aa8a305"></a>

```
int32_t SdioReleaseIrq (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Releases an SDIO IRQ. 

This function is used in pair with  [SdioClaimIrq](sdio.md#ga81f98e541845c15a632cf59cd9c263f8).

**Parameters:**

<a name="table172878985093521"></a>
<table><thead align="left"><tr id="row1648083606093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p675509644093521"><a name="p675509644093521"></a><a name="p675509644093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1307012968093521"><a name="p1307012968093521"></a><a name="p1307012968093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1485488927093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioSetBlockSize\(\)<a name="gad8e070346da466f5f2d68d1d7d18a738"></a>

```
int32_t SdioSetBlockSize (struct [DevHandle](devhandle.md) * handle, uint32_t blockSize )
```

 **Description:**

Sets the block size. 

If data to read or write is performed, use this function to set the block size.

**Parameters:**

<a name="table2014416312093521"></a>
<table><thead align="left"><tr id="row649779753093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1153712898093521"><a name="p1153712898093521"></a><a name="p1153712898093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2064222067093521"><a name="p2064222067093521"></a><a name="p2064222067093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row844748385093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row1492693180093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">blockSize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the block size to be set. If the value is <strong id="b474870478093521"><a name="b474870478093521"></a><a name="b474870478093521"></a>0</strong>, the default value is used. The value ranges from <strong id="b1030484109093521"><a name="b1030484109093521"></a><a name="b1030484109093521"></a>1</strong> to <strong id="b1596377359093521"><a name="b1596377359093521"></a><a name="b1596377359093521"></a>2048</strong> bytes.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioSetCommonInfo\(\)<a name="ga563b67c90fbb88075bf5a05d9b5d5706"></a>

```
int32_t SdioSetCommonInfo (struct [DevHandle](devhandle.md) * handle, [SdioCommonInfo](sdiocommoninfo.md) * info, [SdioCommonInfoType](sdio.md#ga4037437ac001a9848dd242e8aa632678) infoType )
```

 **Description:**

Sets common information. 

You can call this function to set the maximum timeout duration and private data.

**Parameters:**

<a name="table376815906093521"></a>
<table><thead align="left"><tr id="row1431464069093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p313469683093521"><a name="p313469683093521"></a><a name="p313469683093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1401177295093521"><a name="p1401177295093521"></a><a name="p1401177295093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2094230835093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row88000112093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the common information to be set. For details, see <a href="sdiocommoninfo.md">SdioCommonInfo</a>. </td>
</tr>
<tr id="row505721311093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">infoType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the common information to be set. For details, see <a href="sdio.md#ga4037437ac001a9848dd242e8aa632678">SdioCommonInfoType</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioWriteBytes\(\)<a name="ga4daf7bbcb80e38804225ccbaaa496d90"></a>

```
int32_t SdioWriteBytes (struct [DevHandle](devhandle.md) * handle, uint8_t * data, uint32_t addr, uint32_t size, uint32_t timeOut )
```

 **Description:**

Incrementally writes a given length of data into the specified SDIO address. 

If the length of the data to write is greater than the size of a block, the data is written by block first, and the remaining data that is smaller than one block is written by byte. Otherwise, data is written by byte.

**Parameters:**

<a name="table643226370093521"></a>
<table><thead align="left"><tr id="row1465973726093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1572153271093521"><a name="p1572153271093521"></a><a name="p1572153271093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1788496130093521"><a name="p1788496130093521"></a><a name="p1788496130093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row998619201093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row938450147093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to write. </td>
</tr>
<tr id="row1871125226093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start address of the data to write. </td>
</tr>
<tr id="row722659316093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to write. </td>
</tr>
<tr id="row1594324977093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for writing data, in milliseconds. If the value is <strong id="b670208236093521"><a name="b670208236093521"></a><a name="b670208236093521"></a>0</strong>, the default value is used. The default value varies according to the application. Generally, the default value is <strong id="b397385697093521"><a name="b397385697093521"></a><a name="b397385697093521"></a>1</strong> second.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioWriteBytesToFixedAddr\(\)<a name="gae2bffd43990954fb1da9f9c6866c4018"></a>

```
int32_t SdioWriteBytesToFixedAddr (struct [DevHandle](devhandle.md) * handle, uint8_t * data, uint32_t addr, uint32_t size, uint32_t timeOut )
```

 **Description:**

Writes a given length of data into the fixed SDIO address. 

If the length of the data to write is greater than the size of a block, the data is written by block first, and the remaining data that is smaller than one block is written by byte. Otherwise, data is written by byte.

**Parameters:**

<a name="table202943145093521"></a>
<table><thead align="left"><tr id="row1550226375093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1950831094093521"><a name="p1950831094093521"></a><a name="p1950831094093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1130821132093521"><a name="p1130821132093521"></a><a name="p1130821132093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1738347185093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row38615993093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to write. </td>
</tr>
<tr id="row2109653110093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the fixed address of the data to write. </td>
</tr>
<tr id="row460442548093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to write. </td>
</tr>
<tr id="row1362746796093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for writing data, in milliseconds. If the value is <strong id="b1445594892093521"><a name="b1445594892093521"></a><a name="b1445594892093521"></a>0</strong>, the default value is used. The default value varies according to the application. Generally, the default value is <strong id="b1557675659093521"><a name="b1557675659093521"></a><a name="b1557675659093521"></a>1</strong> second.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



## SdioWriteBytesToFunc0\(\)<a name="gace26ab5ab8cfe037b6d6e132a045a7e0"></a>

```
int32_t SdioWriteBytesToFunc0 (struct [DevHandle](devhandle.md) * handle, uint8_t * data, uint32_t addr, uint32_t size, uint32_t timeOut )
```

 **Description:**

Writes a given length of data into the address space of SDIO function 0. 

Currently, only one byte of data can be written.

**Parameters:**

<a name="table407469975093521"></a>
<table><thead align="left"><tr id="row1595079176093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p520761058093521"><a name="p520761058093521"></a><a name="p520761058093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1279188228093521"><a name="p1279188228093521"></a><a name="p1279188228093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row435996144093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device handle of the SDIO controller obtained by <a href="sdio.md#gadca7b0edcae3df85b3ade33704a306f8">SdioOpen</a>. </td>
</tr>
<tr id="row327099608093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to write. </td>
</tr>
<tr id="row2122130151093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start address of the data to write. </td>
</tr>
<tr id="row1956609249093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to write. </td>
</tr>
<tr id="row557957107093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for writing data, in milliseconds. If the value is <strong id="b1052303708093521"><a name="b1052303708093521"></a><a name="b1052303708093521"></a>0</strong>, the default value is used. The default value varies according to the application. Generally, the default value is <strong id="b666633816093521"><a name="b666633816093521"></a><a name="b666633816093521"></a>1</strong> second.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. 



