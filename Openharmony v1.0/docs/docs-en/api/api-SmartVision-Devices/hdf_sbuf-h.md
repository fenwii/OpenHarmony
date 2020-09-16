# hdf\_sbuf.h<a name="EN-US_TOPIC_0000001055039486"></a>

## **Overview**<a name="section2077778926093525"></a>

**Related Modules:**

[Core](core.md)

**Description:**

Defines functions related to a  **[HdfSBuf](hdfsbuf.md)**. The HDF provides data serialization and deserialization capabilities for data transmission between user-mode applications and kernel-mode drivers. 

**Since:**

1.0

## **Summary**<a name="section3873971093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1632891105093525"></a>
<table><thead align="left"><tr id="row1963680918093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p610745227093525"><a name="p610745227093525"></a><a name="p610745227093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p350282944093525"><a name="p350282944093525"></a><a name="p350282944093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row679723314093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p56478790093525"><a name="p56478790093525"></a><a name="p56478790093525"></a><a href="hdfsbuf.md">HdfSBuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847271566093525"><a name="p1847271566093525"></a><a name="p1847271566093525"></a>Defines a <strong id="b1049999911093525"><a name="b1049999911093525"></a><a name="b1049999911093525"></a><a href="hdfsbuf.md">HdfSBuf</a></strong>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1417075399093525"></a>
<table><thead align="left"><tr id="row333962916093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2117354541093525"><a name="p2117354541093525"></a><a name="p2117354541093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1553731279093525"><a name="p1553731279093525"></a><a name="p1553731279093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1380744630093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1191449868093525"><a name="p1191449868093525"></a><a name="p1191449868093525"></a><a href="core.md#ga567eb533aa53051d0beec43f08e72dd8">HdfSbufWriteBuffer</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, const void *data, uint32_t writeSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1889887859093525"><a name="p1889887859093525"></a><a name="p1889887859093525"></a>bool </p>
<p id="p507427361093525"><a name="p507427361093525"></a><a name="p507427361093525"></a>Writes a data segment to a <strong id="b409078241093525"><a name="b409078241093525"></a><a name="b409078241093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row2033869018093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1349248705093525"><a name="p1349248705093525"></a><a name="p1349248705093525"></a><a href="core.md#ga164de95ad00302b599290bdb476a032f">HdfSbufWriteUint64</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315042489093525"><a name="p315042489093525"></a><a name="p315042489093525"></a>bool </p>
<p id="p922055300093525"><a name="p922055300093525"></a><a name="p922055300093525"></a>Writes a 64-bit unsigned integer to a <strong id="b771158700093525"><a name="b771158700093525"></a><a name="b771158700093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row83099383093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p579815334093525"><a name="p579815334093525"></a><a name="p579815334093525"></a><a href="core.md#ga23f2331cdfb0bf91a29f47f20ffd50df">HdfSbufWriteUint32</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p13157914093525"><a name="p13157914093525"></a><a name="p13157914093525"></a>bool </p>
<p id="p625153944093525"><a name="p625153944093525"></a><a name="p625153944093525"></a>Writes a 32-bit unsigned integer to a <strong id="b2133876100093525"><a name="b2133876100093525"></a><a name="b2133876100093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1031412069093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2000239414093525"><a name="p2000239414093525"></a><a name="p2000239414093525"></a><a href="core.md#ga31c9edfd9b20d6e44d34839efa0e08f7">HdfSbufWriteUint16</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1726966118093525"><a name="p1726966118093525"></a><a name="p1726966118093525"></a>bool </p>
<p id="p1074316879093525"><a name="p1074316879093525"></a><a name="p1074316879093525"></a>Writes a 16-bit unsigned integer to a <strong id="b1177248478093525"><a name="b1177248478093525"></a><a name="b1177248478093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1868163630093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p847352381093525"><a name="p847352381093525"></a><a name="p847352381093525"></a><a href="core.md#gafb4fe74246f85a158c140bf4c4951256">HdfSbufWriteUint8</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p525672919093525"><a name="p525672919093525"></a><a name="p525672919093525"></a>bool </p>
<p id="p1364577541093525"><a name="p1364577541093525"></a><a name="p1364577541093525"></a>Writes an 8-bit unsigned integer to a <strong id="b1873418170093525"><a name="b1873418170093525"></a><a name="b1873418170093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1828785687093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p223630812093525"><a name="p223630812093525"></a><a name="p223630812093525"></a><a href="core.md#ga7c63eb006b19e2aac43c23318c4ebe3b">HdfSbufWriteInt64</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p736286603093525"><a name="p736286603093525"></a><a name="p736286603093525"></a>bool </p>
<p id="p373944113093525"><a name="p373944113093525"></a><a name="p373944113093525"></a>Writes a 64-bit signed integer to a <strong id="b280552228093525"><a name="b280552228093525"></a><a name="b280552228093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row674965776093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978592643093525"><a name="p1978592643093525"></a><a name="p1978592643093525"></a><a href="core.md#ga3913510d670da2f8ffa3103b5ff293f1">HdfSbufWriteInt32</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1816887351093525"><a name="p1816887351093525"></a><a name="p1816887351093525"></a>bool </p>
<p id="p1458849697093525"><a name="p1458849697093525"></a><a name="p1458849697093525"></a>Writes a 32-bit signed integer to a <strong id="b2041803066093525"><a name="b2041803066093525"></a><a name="b2041803066093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1643912734093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1485439266093525"><a name="p1485439266093525"></a><a name="p1485439266093525"></a><a href="core.md#gaaa278bf9aa182a4c65c390c6c9ff06d2">HdfSbufWriteInt16</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267807249093525"><a name="p267807249093525"></a><a name="p267807249093525"></a>bool </p>
<p id="p1959204909093525"><a name="p1959204909093525"></a><a name="p1959204909093525"></a>Writes a 16-bit signed integer to a <strong id="b429272873093525"><a name="b429272873093525"></a><a name="b429272873093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row535888297093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997390184093525"><a name="p1997390184093525"></a><a name="p1997390184093525"></a><a href="core.md#gac514c3debd605043ad1bfa9c05a115a0">HdfSbufWriteInt8</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p176878630093525"><a name="p176878630093525"></a><a name="p176878630093525"></a>bool </p>
<p id="p1501857946093525"><a name="p1501857946093525"></a><a name="p1501857946093525"></a>Writes an 8-bit signed integer to a <strong id="b1015399425093525"><a name="b1015399425093525"></a><a name="b1015399425093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1735133988093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p923758698093525"><a name="p923758698093525"></a><a name="p923758698093525"></a><a href="core.md#gaf782f8a08dcd81f4038ab9d9bbc1cf9b">HdfSbufWriteString</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597223282093525"><a name="p1597223282093525"></a><a name="p1597223282093525"></a>bool </p>
<p id="p160868697093525"><a name="p160868697093525"></a><a name="p160868697093525"></a>Writes a string to a <strong id="b1219914028093525"><a name="b1219914028093525"></a><a name="b1219914028093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1189060265093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p325129206093525"><a name="p325129206093525"></a><a name="p325129206093525"></a><a href="core.md#ga345e8524a6cea44a0424e23b8f659792">HdfSbufReadBuffer</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, const void **data, uint32_t *readSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327156958093525"><a name="p1327156958093525"></a><a name="p1327156958093525"></a>bool </p>
<p id="p761020251093525"><a name="p761020251093525"></a><a name="p761020251093525"></a>Reads a data segment from a <strong id="b1799417142093525"><a name="b1799417142093525"></a><a name="b1799417142093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1718886941093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946551273093525"><a name="p946551273093525"></a><a name="p946551273093525"></a><a href="core.md#gabb10a71c031d3633c5745ba6fd62b0a4">HdfSbufReadUint64</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint64_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p668021138093525"><a name="p668021138093525"></a><a name="p668021138093525"></a>bool </p>
<p id="p955569390093525"><a name="p955569390093525"></a><a name="p955569390093525"></a>Reads a 64-bit unsigned integer from a <strong id="b1821431295093525"><a name="b1821431295093525"></a><a name="b1821431295093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row774712945093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p197249974093525"><a name="p197249974093525"></a><a name="p197249974093525"></a><a href="core.md#gac953788575b0c22947f18fa9f19a5bf5">HdfSbufReadUint32</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint32_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p811280258093525"><a name="p811280258093525"></a><a name="p811280258093525"></a>bool </p>
<p id="p1394903444093525"><a name="p1394903444093525"></a><a name="p1394903444093525"></a>Reads a 32-bit unsigned integer from a <strong id="b120731899093525"><a name="b120731899093525"></a><a name="b120731899093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1799962682093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825993231093525"><a name="p825993231093525"></a><a name="p825993231093525"></a><a href="core.md#gabc151ad38bdecd5589623a6298c31930">HdfSbufReadUint16</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint16_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751353808093525"><a name="p751353808093525"></a><a name="p751353808093525"></a>bool </p>
<p id="p1852922860093525"><a name="p1852922860093525"></a><a name="p1852922860093525"></a>Reads a 16-bit unsigned integer from a <strong id="b1608854589093525"><a name="b1608854589093525"></a><a name="b1608854589093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1852879170093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p165976566093525"><a name="p165976566093525"></a><a name="p165976566093525"></a><a href="core.md#ga07d93e6bcd8a6a8646067783d6f46e74">HdfSbufReadUint8</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, uint8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486814607093525"><a name="p486814607093525"></a><a name="p486814607093525"></a>bool </p>
<p id="p419373455093525"><a name="p419373455093525"></a><a name="p419373455093525"></a>Reads an 8-bit unsigned integer from a <strong id="b23608273093525"><a name="b23608273093525"></a><a name="b23608273093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1636216150093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p42228230093525"><a name="p42228230093525"></a><a name="p42228230093525"></a><a href="core.md#ga7fb121b4351f85e1735c6e63a5c951cc">HdfSbufReadInt64</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int64_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393585707093525"><a name="p393585707093525"></a><a name="p393585707093525"></a>bool </p>
<p id="p687014808093525"><a name="p687014808093525"></a><a name="p687014808093525"></a>Reads a 64-bit signed integer from a <strong id="b818679850093525"><a name="b818679850093525"></a><a name="b818679850093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row557183447093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p767847244093525"><a name="p767847244093525"></a><a name="p767847244093525"></a><a href="core.md#ga22e7b97735f54e57c0d3bed2fa3a47c4">HdfSbufReadInt32</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int32_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p631598318093525"><a name="p631598318093525"></a><a name="p631598318093525"></a>bool </p>
<p id="p1868574382093525"><a name="p1868574382093525"></a><a name="p1868574382093525"></a>Reads a 32-bit signed integer from a <strong id="b27154017093525"><a name="b27154017093525"></a><a name="b27154017093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row369630343093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p173539921093525"><a name="p173539921093525"></a><a name="p173539921093525"></a><a href="core.md#ga3fce62cbc34a70259d21399d5ff91b32">HdfSbufReadInt16</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int16_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472291015093525"><a name="p1472291015093525"></a><a name="p1472291015093525"></a>bool </p>
<p id="p368110273093525"><a name="p368110273093525"></a><a name="p368110273093525"></a>Reads a 16-bit signed integer from a <strong id="b1318531157093525"><a name="b1318531157093525"></a><a name="b1318531157093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row550423098093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116417723093525"><a name="p2116417723093525"></a><a name="p2116417723093525"></a><a href="core.md#gafff778f76f9142602ef25e8afff47c83">HdfSbufReadInt8</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf, int8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p272734524093525"><a name="p272734524093525"></a><a name="p272734524093525"></a>bool </p>
<p id="p676542377093525"><a name="p676542377093525"></a><a name="p676542377093525"></a>Reads an 8-bit signed integer from a <strong id="b497529010093525"><a name="b497529010093525"></a><a name="b497529010093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1052882434093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1216535194093525"><a name="p1216535194093525"></a><a name="p1216535194093525"></a><a href="core.md#gab03aa25c90fda50138496b0f874a664e">HdfSbufReadString</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71390371093525"><a name="p71390371093525"></a><a name="p71390371093525"></a>const char * </p>
<p id="p737647854093525"><a name="p737647854093525"></a><a name="p737647854093525"></a>Reads a string from a <strong id="b1052117642093525"><a name="b1052117642093525"></a><a name="b1052117642093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row748448988093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1097740748093525"><a name="p1097740748093525"></a><a name="p1097740748093525"></a><a href="core.md#ga3f4f5fdb03f64c23f318ecf7c602ac59">HdfSbufGetData</a> (const struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9271406093525"><a name="p9271406093525"></a><a name="p9271406093525"></a>uint8_t * </p>
<p id="p1858930585093525"><a name="p1858930585093525"></a><a name="p1858930585093525"></a>Obtains the pointer to the data stored in a<strong id="b81727792093525"><a name="b81727792093525"></a><a name="b81727792093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1178357999093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224816180093525"><a name="p224816180093525"></a><a name="p224816180093525"></a><a href="core.md#ga2b7a5750bf42151edd7bd686fb11a39d">HdfSbufFlush</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p972444178093525"><a name="p972444178093525"></a><a name="p972444178093525"></a>void </p>
<p id="p1939942266093525"><a name="p1939942266093525"></a><a name="p1939942266093525"></a>Clears the data stored in a <strong id="b679208914093525"><a name="b679208914093525"></a><a name="b679208914093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1647168979093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298035364093525"><a name="p298035364093525"></a><a name="p298035364093525"></a><a href="core.md#ga74941de5883ae39cb6103591f67dbea0">HdfSbufGetCapacity</a> (const struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763823723093525"><a name="p763823723093525"></a><a name="p763823723093525"></a>size_t </p>
<p id="p1348809198093525"><a name="p1348809198093525"></a><a name="p1348809198093525"></a>Obtains the capacity of a <strong id="b1293969586093525"><a name="b1293969586093525"></a><a name="b1293969586093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1822472292093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816942140093525"><a name="p816942140093525"></a><a name="p816942140093525"></a><a href="core.md#gaf983c174acfb5b1f8f9dc5b6c2f52e0d">HdfSbufGetDataSize</a> (const struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p253618620093525"><a name="p253618620093525"></a><a name="p253618620093525"></a>size_t </p>
<p id="p520982651093525"><a name="p520982651093525"></a><a name="p520982651093525"></a>Obtains the size of the data stored in a <strong id="b1254708524093525"><a name="b1254708524093525"></a><a name="b1254708524093525"></a>SBuf</strong>. </p>
</td>
</tr>
<tr id="row1551575615093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242897082093525"><a name="p242897082093525"></a><a name="p242897082093525"></a><a href="core.md#ga5e3dee8b1a2128da70cc5718b631c8ba">HdfSBufObtain</a> (size_t capacity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1636336211093525"><a name="p1636336211093525"></a><a name="p1636336211093525"></a>struct <a href="hdfsbuf.md">HdfSBuf</a> * </p>
<p id="p1825696211093525"><a name="p1825696211093525"></a><a name="p1825696211093525"></a>Obtains a <strong id="b1275683755093525"><a name="b1275683755093525"></a><a name="b1275683755093525"></a>SBuf</strong> instance. </p>
</td>
</tr>
<tr id="row2051358946093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183538243093525"><a name="p1183538243093525"></a><a name="p1183538243093525"></a><a href="core.md#ga479315c09d0d927aa211de829388122d">HdfSBufObtainDefaultSize</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p978386950093525"><a name="p978386950093525"></a><a name="p978386950093525"></a>struct <a href="hdfsbuf.md">HdfSBuf</a> * </p>
<p id="p988517038093525"><a name="p988517038093525"></a><a name="p988517038093525"></a>Obtains a <strong id="b209060794093525"><a name="b209060794093525"></a><a name="b209060794093525"></a>SBuf</strong> instance of the default capacity (256 bytes). </p>
</td>
</tr>
<tr id="row140948933093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006883690093525"><a name="p2006883690093525"></a><a name="p2006883690093525"></a><a href="core.md#gabcc9a442a3b2615828d60a1d4664b4a9">HdfSBufBind</a> (uintptr_t base, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p575444769093525"><a name="p575444769093525"></a><a name="p575444769093525"></a>struct <a href="hdfsbuf.md">HdfSBuf</a> * </p>
<p id="p2147364148093525"><a name="p2147364148093525"></a><a name="p2147364148093525"></a>Creates a <strong id="b170327258093525"><a name="b170327258093525"></a><a name="b170327258093525"></a>SBuf</strong> instance with the specified data and size. The pointer to the data stored in the <strong id="b1929536864093525"><a name="b1929536864093525"></a><a name="b1929536864093525"></a>SBuf</strong> is released by the caller, and the written data size should not exceed the specified value of <strong id="b135115559093525"><a name="b135115559093525"></a><a name="b135115559093525"></a>size</strong>. </p>
</td>
</tr>
<tr id="row2083312985093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453823374093525"><a name="p1453823374093525"></a><a name="p1453823374093525"></a><a href="core.md#gaa0041d238cfc7cf00779191aa58e7ee0">HdfSBufRecycle</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p545399945093525"><a name="p545399945093525"></a><a name="p545399945093525"></a>void </p>
<p id="p266620797093525"><a name="p266620797093525"></a><a name="p266620797093525"></a>Releases a <strong id="b694663811093525"><a name="b694663811093525"></a><a name="b694663811093525"></a>SBuf </strong>. </p>
</td>
</tr>
<tr id="row1733619288093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p383764465093525"><a name="p383764465093525"></a><a name="p383764465093525"></a><a href="core.md#ga22d4a953c89a941337e593647ebe2f5b">HdfSBufMove</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453777343093525"><a name="p1453777343093525"></a><a name="p1453777343093525"></a>struct <a href="hdfsbuf.md">HdfSBuf</a> * </p>
<p id="p359410378093525"><a name="p359410378093525"></a><a name="p359410378093525"></a>Creates a <strong id="b665649229093525"><a name="b665649229093525"></a><a name="b665649229093525"></a>SBuf</strong> instance with an original <strong id="b929046163093525"><a name="b929046163093525"></a><a name="b929046163093525"></a>SBuf</strong>. This function moves the data stored in the original <strong id="b2120646016093525"><a name="b2120646016093525"></a><a name="b2120646016093525"></a>SBuf</strong> to the new one without memory copy. </p>
</td>
</tr>
<tr id="row86060213093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709082369093525"><a name="p709082369093525"></a><a name="p709082369093525"></a><a href="core.md#ga406275df686ff556fd5bdb20349e4972">HdfSBufCopy</a> (const struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1291900487093525"><a name="p1291900487093525"></a><a name="p1291900487093525"></a>struct <a href="hdfsbuf.md">HdfSBuf</a> * </p>
<p id="p40828725093525"><a name="p40828725093525"></a><a name="p40828725093525"></a>Creates a <strong id="b1119269424093525"><a name="b1119269424093525"></a><a name="b1119269424093525"></a>SBuf</strong> instance with an original <strong id="b1567494750093525"><a name="b1567494750093525"></a><a name="b1567494750093525"></a>SBuf</strong>. This function copies the data stored in the original <strong id="b1225171044093525"><a name="b1225171044093525"></a><a name="b1225171044093525"></a>SBuf</strong> to the new one. </p>
</td>
</tr>
<tr id="row1418434977093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900219461093525"><a name="p1900219461093525"></a><a name="p1900219461093525"></a><a href="core.md#gaf391e9f47cc668daf3150c00f369bf1f">HdfSbufTransDataOwnership</a> (struct <a href="hdfsbuf.md">HdfSBuf</a> *sbuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1723289234093525"><a name="p1723289234093525"></a><a name="p1723289234093525"></a>void </p>
<p id="p1024743160093525"><a name="p1024743160093525"></a><a name="p1024743160093525"></a>Transfers the data ownership to a <strong id="b23979799093525"><a name="b23979799093525"></a><a name="b23979799093525"></a>SBuf</strong>. Once the <strong id="b520141704093525"><a name="b520141704093525"></a><a name="b520141704093525"></a>SBuf</strong> is released, the bound data memory is also released. This function is used together with <a href="core.md#gabcc9a442a3b2615828d60a1d4664b4a9">HdfSBufBind</a>. </p>
</td>
</tr>
</tbody>
</table>

