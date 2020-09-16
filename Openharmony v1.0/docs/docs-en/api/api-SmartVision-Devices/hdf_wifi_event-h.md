# hdf\_wifi\_event.h<a name="EN-US_TOPIC_0000001054879502"></a>

## **Overview**<a name="section1067247191093525"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Declares WLAN driver events. 

The functions in this file are used to report events such as scanning results, scanning completion, and station disconnection to the WPA interface.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1261743388093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1350532147093525"></a>
<table><thead align="left"><tr id="row1901320813093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1023493061093525"><a name="p1023493061093525"></a><a name="p1023493061093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2064760943093525"><a name="p2064760943093525"></a><a name="p2064760943093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1511025064093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p781359811093525"><a name="p781359811093525"></a><a name="p781359811093525"></a><a href="rateinfo.md">RateInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p176863256093525"><a name="p176863256093525"></a><a name="p176863256093525"></a>Defines the rate information received or sent over WLAN. </p>
</td>
</tr>
<tr id="row1890114467093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1008242096093525"><a name="p1008242096093525"></a><a name="p1008242096093525"></a><a href="stabssparameters.md">StaBssParameters</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591546190093525"><a name="p591546190093525"></a><a name="p591546190093525"></a>Defines parameters related to the WLAN module that works in station mode. </p>
</td>
</tr>
<tr id="row150659253093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469378299093525"><a name="p469378299093525"></a><a name="p469378299093525"></a><a href="staflagupdate.md">StaFlagUpdate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813049190093525"><a name="p813049190093525"></a><a name="p813049190093525"></a>Defines the update of the <strong id="b1780995277093525"><a name="b1780995277093525"></a><a name="b1780995277093525"></a>Sta</strong> flag. </p>
</td>
</tr>
<tr id="row1839613562093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1232905468093525"><a name="p1232905468093525"></a><a name="p1232905468093525"></a><a href="stationinfo.md">StationInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p198057856093525"><a name="p198057856093525"></a><a name="p198057856093525"></a>Defines station information. </p>
</td>
</tr>
<tr id="row80671836093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p276277006093525"><a name="p276277006093525"></a><a name="p276277006093525"></a><a href="auth.md">Auth</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266985267093525"><a name="p1266985267093525"></a><a name="p1266985267093525"></a>Defines authentication information. </p>
</td>
</tr>
<tr id="row1138434377093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2057360651093525"><a name="p2057360651093525"></a><a name="p2057360651093525"></a><a href="deauth.md">Deauth</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p787409583093525"><a name="p787409583093525"></a><a name="p787409583093525"></a>Defines deauthentication information. </p>
</td>
</tr>
<tr id="row1768332998093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825500546093525"><a name="p825500546093525"></a><a name="p825500546093525"></a><a href="assocreq.md">AssocReq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1982433264093525"><a name="p1982433264093525"></a><a name="p1982433264093525"></a>Defines station association request. </p>
</td>
</tr>
<tr id="row1119896544093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p311644883093525"><a name="p311644883093525"></a><a name="p311644883093525"></a><a href="assocresp.md">AssocResp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1621848500093525"><a name="p1621848500093525"></a><a name="p1621848500093525"></a>Defines station association response. </p>
</td>
</tr>
<tr id="row1545015441093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980200602093525"><a name="p980200602093525"></a><a name="p980200602093525"></a><a href="reassocreq.md">ReassocReq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419055799093525"><a name="p419055799093525"></a><a name="p419055799093525"></a>Defines station reassociation request. </p>
</td>
</tr>
<tr id="row1151461956093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p552778871093525"><a name="p552778871093525"></a><a name="p552778871093525"></a><a href="reassocresp.md">ReassocResp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900813765093525"><a name="p1900813765093525"></a><a name="p1900813765093525"></a>Defines station reassociation response. </p>
</td>
</tr>
<tr id="row2078841689093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1849081287093525"><a name="p1849081287093525"></a><a name="p1849081287093525"></a><a href="disassoc.md">Disassoc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p961504507093525"><a name="p961504507093525"></a><a name="p961504507093525"></a>Defines station disconnection. </p>
</td>
</tr>
<tr id="row1838546705093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p744488447093525"><a name="p744488447093525"></a><a name="p744488447093525"></a><a href="beacon.md">Beacon</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120437188093525"><a name="p120437188093525"></a><a name="p120437188093525"></a>Defines the update of the <strong id="b1035623982093525"><a name="b1035623982093525"></a><a name="b1035623982093525"></a>Sta</strong> flag. </p>
</td>
</tr>
<tr id="row1863096253093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p823714501093525"><a name="p823714501093525"></a><a name="p823714501093525"></a><a href="proberesp.md">ProbeResp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463208767093525"><a name="p463208767093525"></a><a name="p463208767093525"></a>Defines scanning response. </p>
</td>
</tr>
<tr id="row1185706410093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982405813093525"><a name="p1982405813093525"></a><a name="p1982405813093525"></a><a href="ieee80211mgmt.md">Ieee80211Mgmt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1676020694093525"><a name="p1676020694093525"></a><a name="p1676020694093525"></a>Defines management frame information. </p>
</td>
</tr>
<tr id="row1722645118093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265590643093525"><a name="p1265590643093525"></a><a name="p1265590643093525"></a><a href="scannedbssinfo.md">ScannedBssInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261237877093525"><a name="p1261237877093525"></a><a name="p1261237877093525"></a>Represents the scanned BSS information. </p>
</td>
</tr>
<tr id="row1495736189093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307636142093525"><a name="p1307636142093525"></a><a name="p1307636142093525"></a><a href="connetresult.md">ConnetResult</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15335752093525"><a name="p15335752093525"></a><a name="p15335752093525"></a>Defines association results. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2138616532093525"></a>
<table><thead align="left"><tr id="row546790449093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p144380622093525"><a name="p144380622093525"></a><a name="p144380622093525"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1013206625093525"><a name="p1013206625093525"></a><a name="p1013206625093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row328893730093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683537067093525"><a name="p683537067093525"></a><a name="p683537067093525"></a><a href="wlan.md#gaf3e873b51f0cfa077aca9d33ed7a0960">WifiHmacMgmtStatus</a> {   <a href="wlan.md#ggaf3e873b51f0cfa077aca9d33ed7a0960ad9c7e2f362bd6fcadef189fa2a5d7c63">WIFI_HMAC_MGMT_SUCCESS</a> = 0, <a href="wlan.md#ggaf3e873b51f0cfa077aca9d33ed7a0960a539c65a358a20b9731fc66fc60ebcbc2">WIFI_HMAC_MGMT_INVALID</a> = 1, <a href="wlan.md#ggaf3e873b51f0cfa077aca9d33ed7a0960ad1731acef8ddb8c50bcc26ae80fa83a3">WIFI_HMAC_MGMT_TIMEOUT</a> = 2, <a href="wlan.md#ggaf3e873b51f0cfa077aca9d33ed7a0960a05f532edadae3b6afc80b7575dd46961">WIFI_HMAC_MGMT_REFUSED</a> = 3,   <a href="wlan.md#ggaf3e873b51f0cfa077aca9d33ed7a0960a9e241ef81e72de130e1fda573ce2a412">WIFI_HMAC_MGMT_TOMANY_REQ</a> = 4, <a href="wlan.md#ggaf3e873b51f0cfa077aca9d33ed7a0960aa3db4634dc2727e029aef13384bc3940">WIFI_HMAC_MGMT_ALREADY_BSS</a> = 5 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288294610093525"><a name="p288294610093525"></a><a name="p288294610093525"></a>Enumerates MLME management statuses, indicating whether a device is successfully associated or fails to be associated. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1366363023093525"></a>
<table><thead align="left"><tr id="row1846491782093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p481244060093525"><a name="p481244060093525"></a><a name="p481244060093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p234065950093525"><a name="p234065950093525"></a><a name="p234065950093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row426099244093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265524872093525"><a name="p1265524872093525"></a><a name="p1265524872093525"></a><a href="wlan.md#ga31edc1e9de8835e0e8a9c1e89fad3bd9">HdfWifiEventNewSta</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, const uint8_t *macAddr, uint8_t addrLen, const struct <a href="stationinfo.md">StationInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1374435681093525"><a name="p1374435681093525"></a><a name="p1374435681093525"></a>int32_t </p>
<p id="p1485347671093525"><a name="p1485347671093525"></a><a name="p1485347671093525"></a>Reports a new STA event. </p>
</td>
</tr>
<tr id="row1684541318093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1041964910093525"><a name="p1041964910093525"></a><a name="p1041964910093525"></a><a href="wlan.md#ga208ef54b2a601f416a472bb1e21fae7e">HdfWifiEventDelSta</a> (struct <a href="netdevice.md">NetDevice</a> *netdev, const uint8_t *macAddr, uint8_t addrLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782471294093525"><a name="p782471294093525"></a><a name="p782471294093525"></a>int32_t </p>
<p id="p1536144510093525"><a name="p1536144510093525"></a><a name="p1536144510093525"></a>Reports a station deletion event. </p>
</td>
</tr>
<tr id="row1127593857093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290676010093525"><a name="p1290676010093525"></a><a name="p1290676010093525"></a><a href="wlan.md#ga941675fb683212e6e0d8e1529b300482">HdfWifiEventInformBssFrame</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, struct <a href="wiphy.md">Wiphy</a> *wiphy, const struct <a href="ieee80211channel.md">Ieee80211Channel</a> *channel, const struct <a href="scannedbssinfo.md">ScannedBssInfo</a> *bssInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114371562093525"><a name="p2114371562093525"></a><a name="p2114371562093525"></a>int32_t </p>
<p id="p1672327585093525"><a name="p1672327585093525"></a><a name="p1672327585093525"></a>Reports a scanned BSS event. </p>
</td>
</tr>
<tr id="row841026949093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1756712881093525"><a name="p1756712881093525"></a><a name="p1756712881093525"></a><a href="wlan.md#ga41efbd6788a80604b81ae117a363b657">HdfWifiEventScanDone</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, WifiScanStatus status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513996846093525"><a name="p1513996846093525"></a><a name="p1513996846093525"></a>int32_t </p>
<p id="p1413836621093525"><a name="p1413836621093525"></a><a name="p1413836621093525"></a>Reports a scanning completion event. </p>
</td>
</tr>
<tr id="row1738283129093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637588876093525"><a name="p637588876093525"></a><a name="p637588876093525"></a><a href="wlan.md#gaf9e61f36e11d7d2e94e7969a8ecf22f1">HdfWifiEventConnectResult</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, const struct <a href="connetresult.md">ConnetResult</a> *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402419064093525"><a name="p402419064093525"></a><a name="p402419064093525"></a>int32_t </p>
<p id="p1307061498093525"><a name="p1307061498093525"></a><a name="p1307061498093525"></a>Reports a connection result event. </p>
</td>
</tr>
<tr id="row1257189405093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p307843565093525"><a name="p307843565093525"></a><a name="p307843565093525"></a><a href="wlan.md#ga58b1a613d784233a1e84027079e1ea57">HdfWifiEventDisconnected</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, uint16_t reason, const uint8_t *ie, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289027655093525"><a name="p289027655093525"></a><a name="p289027655093525"></a>int32_t </p>
<p id="p1817220487093525"><a name="p1817220487093525"></a><a name="p1817220487093525"></a>Reports a disconnection event. </p>
</td>
</tr>
<tr id="row918373039093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790775904093525"><a name="p790775904093525"></a><a name="p790775904093525"></a><a href="wlan.md#ga1721c7e1b5af0240a663ea9f0fe12854">HdfWifiEventMgmtTxStatus</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, const uint8_t *buf, size_t len, uint8_t ack)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1170259785093525"><a name="p1170259785093525"></a><a name="p1170259785093525"></a>int32_t </p>
<p id="p1515032466093525"><a name="p1515032466093525"></a><a name="p1515032466093525"></a>Reports a transmission management status event. </p>
</td>
</tr>
<tr id="row59439792093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1501782973093525"><a name="p1501782973093525"></a><a name="p1501782973093525"></a><a href="wlan.md#gad47d56e4332ccd14116368444a4b330f">HdfWifiEventRxMgmt</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, int32_t freq, int32_t sigMbm, const uint8_t *buf, size_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1865738747093525"><a name="p1865738747093525"></a><a name="p1865738747093525"></a>int32_t </p>
<p id="p951646575093525"><a name="p951646575093525"></a><a name="p951646575093525"></a>Reports a receive management status event. </p>
</td>
</tr>
<tr id="row1817915375093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1375876388093525"><a name="p1375876388093525"></a><a name="p1375876388093525"></a><a href="wlan.md#ga2aa62f7e8e72e8f9df0b2101c08a9d44">HdfWifiEventCsaChannelSwitch</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, int32_t freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p545031524093525"><a name="p545031524093525"></a><a name="p545031524093525"></a>int32_t </p>
<p id="p1524956634093525"><a name="p1524956634093525"></a><a name="p1524956634093525"></a>Reports a CSA channel switching event. </p>
</td>
</tr>
<tr id="row2077552082093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1252911173093525"><a name="p1252911173093525"></a><a name="p1252911173093525"></a><a href="wlan.md#gafda13471995c91e65326a9aa374ae1c9">HdfWifiEventTimeoutDisconnected</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1270424074093525"><a name="p1270424074093525"></a><a name="p1270424074093525"></a>int32_t </p>
<p id="p124591335093525"><a name="p124591335093525"></a><a name="p124591335093525"></a>Reports a timeout disconnection event. </p>
</td>
</tr>
<tr id="row1516647793093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2095200547093525"><a name="p2095200547093525"></a><a name="p2095200547093525"></a><a href="wlan.md#ga3e60f4568723471226107848ddbe582f">HdfWifiEventEapolRecv</a> (const char *name, void *context)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748458737093525"><a name="p748458737093525"></a><a name="p748458737093525"></a>int32_t </p>
<p id="p641910331093525"><a name="p641910331093525"></a><a name="p641910331093525"></a>Reports the event of receiving the EAPOL frame and notifies WPA to read the EAPOL frame. </p>
</td>
</tr>
</tbody>
</table>

