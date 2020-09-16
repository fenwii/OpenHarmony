# wifiiot\_sdio.h<a name="EN-US_TOPIC_0000001054595099"></a>

## **Overview**<a name="section570974626191856"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the SDIO interface functions. 

These functions are used for SDIO initialization and data transmission. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section753530560191856"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1298046344191856"></a>
<table><thead align="left"><tr id="row2025119091191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2006787447191856"><a name="p2006787447191856"></a><a name="p2006787447191856"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p778205323191856"><a name="p778205323191856"></a><a name="p778205323191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1724056676191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960840943191856"><a name="p960840943191856"></a><a name="p960840943191856"></a><a href="wifiiotsdioextendfunc.md">WifiIotSdioExtendFunc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p970883816191856"><a name="p970883816191856"></a><a name="p970883816191856"></a>Provides extended SDIO attributes. </p>
</td>
</tr>
<tr id="row832681846191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p672529293191856"><a name="p672529293191856"></a><a name="p672529293191856"></a><a href="wifiiotsdioadmatable.md">WifiIotSdioAdmatable</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327288398191856"><a name="p327288398191856"></a><a name="p327288398191856"></a>Defines attributes of an SDIO ADMA table. </p>
</td>
</tr>
<tr id="row528612650191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1786681748191856"><a name="p1786681748191856"></a><a name="p1786681748191856"></a><a href="wifiiotsdiointcallback.md">WifiIotSdioIntcallback</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313451112191856"><a name="p313451112191856"></a><a name="p313451112191856"></a>SDIO interrupt callback structure. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1903743632191856"></a>
<table><thead align="left"><tr id="row147245563191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2118691992191856"><a name="p2118691992191856"></a><a name="p2118691992191856"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p634520737191856"><a name="p634520737191856"></a><a name="p634520737191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row479764922191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p497858152191856"><a name="p497858152191856"></a><a name="p497858152191856"></a><a href="wifiiot.md#ga107279ca1341146ae076f8e08c10d1dc">WIFI_IOT_SDIO_EXTENDREG_COUNT</a>   64</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351457485191856"><a name="p351457485191856"></a><a name="p351457485191856"></a>Indicates the number of extended registers on an SDIO device. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1076197914191856"></a>
<table><thead align="left"><tr id="row1775478469191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p396002329191856"><a name="p396002329191856"></a><a name="p396002329191856"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1939039124191856"><a name="p1939039124191856"></a><a name="p1939039124191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1337505744191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133302331191856"><a name="p1133302331191856"></a><a name="p1133302331191856"></a><a href="wifiiot.md#ga133bb67c0fa6e9dcab35f00edff68e58">NotifyHostMessageEvent</a>) (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1186958895191856"><a name="p1186958895191856"></a><a name="p1186958895191856"></a> typedef void(* </p>
<p id="p1068228501191856"><a name="p1068228501191856"></a><a name="p1068228501191856"></a>Indicates the callback invoked upon a message event on the host. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table850745450191856"></a>
<table><thead align="left"><tr id="row1111734442191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p106035715191856"><a name="p106035715191856"></a><a name="p106035715191856"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p863697095191856"><a name="p863697095191856"></a><a name="p863697095191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row779767322191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1679090442191856"><a name="p1679090442191856"></a><a name="p1679090442191856"></a><a href="wifiiot.md#gaad3bec1e62fb695ed4b8f0627b3f4e84">SdioInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p958594571191856"><a name="p958594571191856"></a><a name="p958594571191856"></a>unsigned int </p>
<p id="p1526930300191856"><a name="p1526930300191856"></a><a name="p1526930300191856"></a>Initializes the SDIO device. </p>
</td>
</tr>
<tr id="row535330025191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p846167486191856"><a name="p846167486191856"></a><a name="p846167486191856"></a><a href="wifiiot.md#ga7093b6e5941cedd1d3fa706500fb3c66">SdioReinit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197196488191856"><a name="p197196488191856"></a><a name="p197196488191856"></a>unsigned int </p>
<p id="p1687484172191856"><a name="p1687484172191856"></a><a name="p1687484172191856"></a>Reinitializes the SDIO device. </p>
</td>
</tr>
<tr id="row1029225989191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838166926191856"><a name="p838166926191856"></a><a name="p838166926191856"></a><a href="wifiiot.md#ga180aae06228682aee1e7ac335498c94f">SdioSoftReset</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703191067191856"><a name="p1703191067191856"></a><a name="p1703191067191856"></a>void </p>
<p id="p567609182191856"><a name="p567609182191856"></a><a name="p567609182191856"></a>Resets the SDIO device. </p>
</td>
</tr>
<tr id="row1760485709191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2022255439191856"><a name="p2022255439191856"></a><a name="p2022255439191856"></a><a href="wifiiot.md#ga8d8b7169c2668a0be5f3870e12d41071">SdioRegisterCallback</a> (const <a href="wifiiotsdiointcallback.md">WifiIotSdioIntcallback</a> *callbackFunc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1200302670191856"><a name="p1200302670191856"></a><a name="p1200302670191856"></a>unsigned int </p>
<p id="p1192958254191856"><a name="p1192958254191856"></a><a name="p1192958254191856"></a>Registers an interrupt callback for the SDIO device. </p>
</td>
</tr>
<tr id="row72719481191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1450225611191856"><a name="p1450225611191856"></a><a name="p1450225611191856"></a><a href="wifiiot.md#ga2615d7d406366292f8b2fd445d841971">SdioCompleteSend</a> (unsigned char *admaTable, unsigned int admaIndex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p389381829191856"><a name="p389381829191856"></a><a name="p389381829191856"></a>unsigned int </p>
<p id="p1051861650191856"><a name="p1051861650191856"></a><a name="p1051861650191856"></a>Completes data sending on the SDIO device. </p>
</td>
</tr>
<tr id="row1505090611191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280036595191856"><a name="p280036595191856"></a><a name="p280036595191856"></a><a href="wifiiot.md#ga257b72a879ec478d9434d2a2a2a69281">SdioSetPadAdmatab</a> (unsigned int padlen, unsigned char *admatable, unsigned int admaIndex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924354191191856"><a name="p924354191191856"></a><a name="p924354191191856"></a>unsigned int </p>
<p id="p1023993112191856"><a name="p1023993112191856"></a><a name="p1023993112191856"></a>Sets the ADMA table that requires data padding. </p>
</td>
</tr>
<tr id="row1134223407191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488033918191856"><a name="p488033918191856"></a><a name="p488033918191856"></a><a href="wifiiot.md#ga79d11f1582ccd79d55e28c4a3c3896ad">SdioWriteExtinfo</a> (<a href="wifiiotsdioextendfunc.md">WifiIotSdioExtendFunc</a> *extFunc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p260015344191856"><a name="p260015344191856"></a><a name="p260015344191856"></a>unsigned int </p>
<p id="p504048199191856"><a name="p504048199191856"></a><a name="p504048199191856"></a>Sets the extended SDIO attributes. </p>
</td>
</tr>
<tr id="row727547964191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982763229191856"><a name="p1982763229191856"></a><a name="p1982763229191856"></a><a href="wifiiot.md#ga5a38e3c0f2848972cbe736980ea6e355">SdioSendData</a> (unsigned int xferBytes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856672693191856"><a name="p856672693191856"></a><a name="p856672693191856"></a>void </p>
<p id="p1474205635191856"><a name="p1474205635191856"></a><a name="p1474205635191856"></a>Starts to send data. </p>
</td>
</tr>
<tr id="row1840278548191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1591993505191856"><a name="p1591993505191856"></a><a name="p1591993505191856"></a><a href="wifiiot.md#gadbd7176d96c0a92bc8dd3186d5e56044">SdioSetAdmatable</a> (unsigned char *admatable, unsigned int admaIndex, const unsigned int *dataAddr, unsigned int dataLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368023490191856"><a name="p368023490191856"></a><a name="p368023490191856"></a>unsigned int </p>
<p id="p310998694191856"><a name="p310998694191856"></a><a name="p310998694191856"></a>Sets an SDIO ADMA. </p>
</td>
</tr>
<tr id="row1499368369191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773525563191856"><a name="p773525563191856"></a><a name="p773525563191856"></a><a href="wifiiot.md#ga6ce36235d20976c2f4668798de3fd0fb">SdioSchedMsg</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1577621158191856"><a name="p1577621158191856"></a><a name="p1577621158191856"></a>unsigned int </p>
<p id="p39164521191856"><a name="p39164521191856"></a><a name="p39164521191856"></a>Sends a suspended SDIO message. </p>
</td>
</tr>
<tr id="row539898116191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1052060773191856"><a name="p1052060773191856"></a><a name="p1052060773191856"></a><a href="wifiiot.md#ga475a381fc4b9357aee48386bd1825d28">SdioSendSyncMsg</a> (unsigned int msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386560680191856"><a name="p386560680191856"></a><a name="p386560680191856"></a>unsigned int </p>
<p id="p1779525623191856"><a name="p1779525623191856"></a><a name="p1779525623191856"></a>Adds a message to a message queue and sends the message. </p>
</td>
</tr>
<tr id="row1094352814191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1454484793191856"><a name="p1454484793191856"></a><a name="p1454484793191856"></a><a href="wifiiot.md#gae8c8a1b4725d9f291fbf17e2760e5bb9">SdioSendMsgAck</a> (unsigned int msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989812219191856"><a name="p1989812219191856"></a><a name="p1989812219191856"></a>unsigned int </p>
<p id="p1392673565191856"><a name="p1392673565191856"></a><a name="p1392673565191856"></a>Sends a specified message. </p>
</td>
</tr>
<tr id="row224530568191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76290585191856"><a name="p76290585191856"></a><a name="p76290585191856"></a><a href="wifiiot.md#ga1e8370bf332882774ca34d6a9b4164b8">SdioProcessMsg</a> (unsigned int sendMsg, unsigned int clearMsg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475982639191856"><a name="p475982639191856"></a><a name="p475982639191856"></a>unsigned int </p>
<p id="p1479731141191856"><a name="p1479731141191856"></a><a name="p1479731141191856"></a>Clears a specified suspended message in the message queue, adds a new message to it, and sends the new message. </p>
</td>
</tr>
<tr id="row413993814191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1097768192191856"><a name="p1097768192191856"></a><a name="p1097768192191856"></a><a href="wifiiot.md#gafc188bce50a808f7ebd6641d01725602">SdioIsPendingMsg</a> (unsigned int msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133927959191856"><a name="p1133927959191856"></a><a name="p1133927959191856"></a>unsigned int </p>
<p id="p412611338191856"><a name="p412611338191856"></a><a name="p412611338191856"></a>Checks whether a specified message is suspended. </p>
</td>
</tr>
<tr id="row162791983191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p631585513191856"><a name="p631585513191856"></a><a name="p631585513191856"></a><a href="wifiiot.md#ga5ee18bbecf0f451068e943f44ada8b9c">SdioIsSendingMsg</a> (unsigned int msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p787726993191856"><a name="p787726993191856"></a><a name="p787726993191856"></a>unsigned int </p>
<p id="p1570974268191856"><a name="p1570974268191856"></a><a name="p1570974268191856"></a>Checks whether a specified message is being sent. </p>
</td>
</tr>
<tr id="row151182942191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p605545143191856"><a name="p605545143191856"></a><a name="p605545143191856"></a><a href="wifiiot.md#gac4b082298d466441c68e0e916f92dc03">SdioGetExtendInfo</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1111850642191856"><a name="p1111850642191856"></a><a name="p1111850642191856"></a><a href="wifiiotsdioextendfunc.md">WifiIotSdioExtendFunc</a> * </p>
<p id="p94762755191856"><a name="p94762755191856"></a><a name="p94762755191856"></a>Obtains the extended configuration. </p>
</td>
</tr>
<tr id="row990780187191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275385992191856"><a name="p275385992191856"></a><a name="p275385992191856"></a><a href="wifiiot.md#gae8925d25b4fc160d0fa9760c28c87e84">SdioRegisterNotifyMessageCallback</a> (<a href="wifiiot.md#ga133bb67c0fa6e9dcab35f00edff68e58">NotifyHostMessageEvent</a> msgEventCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p61351880191856"><a name="p61351880191856"></a><a name="p61351880191856"></a>void </p>
<p id="p2124667716191856"><a name="p2124667716191856"></a><a name="p2124667716191856"></a>Registers the callback that will be invoked when the host sends a message or data. </p>
</td>
</tr>
<tr id="row495022824191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1443087532191856"><a name="p1443087532191856"></a><a name="p1443087532191856"></a><a href="wifiiot.md#gaa507e3ae762f43b644c716aa5385172a">SdioSetPowerdownWhenDeepSleep</a> (unsigned char powerDown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1070065849191856"><a name="p1070065849191856"></a><a name="p1070065849191856"></a>void </p>
<p id="p432990987191856"><a name="p432990987191856"></a><a name="p432990987191856"></a>Sets whether the SDIO device is powered off in deep sleep mode. </p>
</td>
</tr>
</tbody>
</table>

