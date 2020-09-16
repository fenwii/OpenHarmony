# parameter.h<a name="EN-US_TOPIC_0000001054476493"></a>

## **Overview**<a name="section2025203949090253"></a>

**Related Modules:**

[Parameter](parameter.md)

**Description:**

Declares functions for obtaining system parameters. 

You can use the provided functions to obtain device information such as device type and manufacturer. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1848137634090253"></a>

## Functions<a name="func-members"></a>

<a name="table1670405282090253"></a>
<table><thead align="left"><tr id="row1868692534090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1287535171090253"><a name="p1287535171090253"></a><a name="p1287535171090253"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2104374310090253"><a name="p2104374310090253"></a><a name="p2104374310090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row646993902090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301508763090253"><a name="p301508763090253"></a><a name="p301508763090253"></a><a href="parameter.md#gae6a476fa36d2b1876eee0e4f256db6a6">GetParameter</a> (const char *key, const char *def, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p292798839090253"><a name="p292798839090253"></a><a name="p292798839090253"></a>int </p>
<p id="p136878463090253"><a name="p136878463090253"></a><a name="p136878463090253"></a>Obtains a system parameter matching the specified <strong id="b1062592748090253"><a name="b1062592748090253"></a><a name="b1062592748090253"></a>key</strong>. </p>
</td>
</tr>
<tr id="row1592278771090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275992313090253"><a name="p275992313090253"></a><a name="p275992313090253"></a><a href="parameter.md#ga2779b5e59d43308c51f7be38b9c98ddb">SetParameter</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262877172090253"><a name="p262877172090253"></a><a name="p262877172090253"></a>int </p>
<p id="p1495840082090253"><a name="p1495840082090253"></a><a name="p1495840082090253"></a>Sets or updates a system parameter. </p>
</td>
</tr>
<tr id="row1084278906090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094535256090253"><a name="p2094535256090253"></a><a name="p2094535256090253"></a><a href="parameter.md#ga2d6e83004da9cfdef6f3162d484163f1">GetProductType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p520531316090253"><a name="p520531316090253"></a><a name="p520531316090253"></a>char * </p>
<p id="p504387539090253"><a name="p504387539090253"></a><a name="p504387539090253"></a>Obtains the device type. </p>
</td>
</tr>
<tr id="row444992820090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155612496090253"><a name="p155612496090253"></a><a name="p155612496090253"></a><a href="parameter.md#gad6d21dda3b027eb603dd24c7315ee6ea">GetManufacture</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268528022090253"><a name="p268528022090253"></a><a name="p268528022090253"></a>char * </p>
<p id="p398719692090253"><a name="p398719692090253"></a><a name="p398719692090253"></a>Obtains the device manufacturer. </p>
</td>
</tr>
<tr id="row109766806090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479049947090253"><a name="p479049947090253"></a><a name="p479049947090253"></a><a href="parameter.md#gaba787cc6f740d7d8f5e7ccd5a98fc7ed">GetBrand</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374849272090253"><a name="p374849272090253"></a><a name="p374849272090253"></a>char * </p>
<p id="p1746516213090253"><a name="p1746516213090253"></a><a name="p1746516213090253"></a>Obtains the device brand. </p>
</td>
</tr>
<tr id="row1901121001090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094628942090253"><a name="p2094628942090253"></a><a name="p2094628942090253"></a><a href="parameter.md#gaa3adb204e5affd0a9e18828c1fbf2b0b">GetMarketName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p24894833090253"><a name="p24894833090253"></a><a name="p24894833090253"></a>char * </p>
<p id="p1665968761090253"><a name="p1665968761090253"></a><a name="p1665968761090253"></a>Obtains the device marketing name. </p>
</td>
</tr>
<tr id="row1981996241090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p934714375090253"><a name="p934714375090253"></a><a name="p934714375090253"></a><a href="parameter.md#ga8a0d394075a3cbafe7ef0f51d08319a8">GetProductSeries</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331067051090253"><a name="p1331067051090253"></a><a name="p1331067051090253"></a>char * </p>
<p id="p1146824487090253"><a name="p1146824487090253"></a><a name="p1146824487090253"></a>Obtains the device series name. </p>
</td>
</tr>
<tr id="row1327287441090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901662120090253"><a name="p1901662120090253"></a><a name="p1901662120090253"></a><a href="parameter.md#gaa62644b77184644fac848f54837f4e5b">GetProductModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14351472090253"><a name="p14351472090253"></a><a name="p14351472090253"></a>char * </p>
<p id="p1400032949090253"><a name="p1400032949090253"></a><a name="p1400032949090253"></a>Obtains the device authentication model. </p>
</td>
</tr>
<tr id="row865860497090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p337267225090253"><a name="p337267225090253"></a><a name="p337267225090253"></a><a href="parameter.md#ga309a7fb6d9a60f6d6453e3faea030d7a">GetSoftwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p171184250090253"><a name="p171184250090253"></a><a name="p171184250090253"></a>char * </p>
<p id="p563818289090253"><a name="p563818289090253"></a><a name="p563818289090253"></a>Obtains the device software model. </p>
</td>
</tr>
<tr id="row1491508535090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626344428090253"><a name="p1626344428090253"></a><a name="p1626344428090253"></a><a href="parameter.md#ga0ff61721ab17eb07fcece1ccaf40293a">GetHardwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1130187148090253"><a name="p1130187148090253"></a><a name="p1130187148090253"></a>char * </p>
<p id="p1451622420090253"><a name="p1451622420090253"></a><a name="p1451622420090253"></a>Obtains the device hardware model. </p>
</td>
</tr>
<tr id="row1237981345090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920571927090253"><a name="p920571927090253"></a><a name="p920571927090253"></a><a href="parameter.md#gaf98290ad8bd5328aff40293ff42d6a9b">GetHardwareProfile</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p387915263090253"><a name="p387915263090253"></a><a name="p387915263090253"></a>char * </p>
<p id="p1346494556090253"><a name="p1346494556090253"></a><a name="p1346494556090253"></a>Obtains the device hardware profile. </p>
</td>
</tr>
<tr id="row1320573125090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1630999641090253"><a name="p1630999641090253"></a><a name="p1630999641090253"></a><a href="parameter.md#gacc29ceeab6d312f3becdf19b28b9185d">GetSerial</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308859535090253"><a name="p308859535090253"></a><a name="p308859535090253"></a>char * </p>
<p id="p966057522090253"><a name="p966057522090253"></a><a name="p966057522090253"></a>Obtains the device serial number (SN). </p>
</td>
</tr>
<tr id="row942512153090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p309568364090253"><a name="p309568364090253"></a><a name="p309568364090253"></a><a href="parameter.md#ga1402657e793875973f8801f631c29781">GetOsName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452428367090253"><a name="p1452428367090253"></a><a name="p1452428367090253"></a>char * </p>
<p id="p970011927090253"><a name="p970011927090253"></a><a name="p970011927090253"></a>Obtains the operating system (OS) name. </p>
</td>
</tr>
<tr id="row630287623090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p46256483090253"><a name="p46256483090253"></a><a name="p46256483090253"></a><a href="parameter.md#gaacd61c8a367a307d5b5c3e907822f271">GetDisplayVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1089774458090253"><a name="p1089774458090253"></a><a name="p1089774458090253"></a>char * </p>
<p id="p288964090253"><a name="p288964090253"></a><a name="p288964090253"></a>Obtains the software version visible to users. </p>
</td>
</tr>
<tr id="row1374094068090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402410441090253"><a name="p402410441090253"></a><a name="p402410441090253"></a><a href="parameter.md#gab033380f4acabc3304c401ea40034a3b">GetBootloaderVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p357676075090253"><a name="p357676075090253"></a><a name="p357676075090253"></a>char * </p>
<p id="p564105585090253"><a name="p564105585090253"></a><a name="p564105585090253"></a>Obtains the bootloader version of this device. </p>
</td>
</tr>
<tr id="row2128566460090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2053487280090253"><a name="p2053487280090253"></a><a name="p2053487280090253"></a><a href="parameter.md#gaa2407d8ce39e4a151b7e9d45123794c2">GetSecurityPatchTag</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313649896090253"><a name="p1313649896090253"></a><a name="p1313649896090253"></a>char * </p>
<p id="p865275348090253"><a name="p865275348090253"></a><a name="p865275348090253"></a>Obtains the security patch tag. </p>
</td>
</tr>
<tr id="row115664205090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220970175090253"><a name="p220970175090253"></a><a name="p220970175090253"></a><a href="parameter.md#gaa5e3d6179f398e407b632cc53410cd1a">GetAbiList</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1767828957090253"><a name="p1767828957090253"></a><a name="p1767828957090253"></a>char * </p>
<p id="p76023494090253"><a name="p76023494090253"></a><a name="p76023494090253"></a>Obtains the list of application binary interfaces (ABIs) supported on this device. </p>
</td>
</tr>
<tr id="row1585316826090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1878687053090253"><a name="p1878687053090253"></a><a name="p1878687053090253"></a><a href="parameter.md#ga4720291ec5700581109e2f7943e2e371">GetSdkApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1674179542090253"><a name="p1674179542090253"></a><a name="p1674179542090253"></a>char * </p>
<p id="p535416040090253"><a name="p535416040090253"></a><a name="p535416040090253"></a>Obtains the SDK API level that matches the current system software. </p>
</td>
</tr>
<tr id="row1006475472090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p556731218090253"><a name="p556731218090253"></a><a name="p556731218090253"></a><a href="parameter.md#ga6f62d683d76a160775b3ac46e856955e">GetFirstApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81189580090253"><a name="p81189580090253"></a><a name="p81189580090253"></a>char * </p>
<p id="p1022731455090253"><a name="p1022731455090253"></a><a name="p1022731455090253"></a>Obtains the first SDK API level of the system software. </p>
</td>
</tr>
<tr id="row1177758866090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451260612090253"><a name="p451260612090253"></a><a name="p451260612090253"></a><a href="parameter.md#ga3d52b0a354555dbb16c265d5d5923546">GetIncrementalVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946494334090253"><a name="p946494334090253"></a><a name="p946494334090253"></a>char * </p>
<p id="p895566138090253"><a name="p895566138090253"></a><a name="p895566138090253"></a>Obtains the incremental version. </p>
</td>
</tr>
<tr id="row1113488071090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670878506090253"><a name="p670878506090253"></a><a name="p670878506090253"></a><a href="parameter.md#gaea3cb294680fcef18a0a52f35fdaa124">GetVersionId</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p632726333090253"><a name="p632726333090253"></a><a name="p632726333090253"></a>char * </p>
<p id="p1367448860090253"><a name="p1367448860090253"></a><a name="p1367448860090253"></a>Obtains the version ID. </p>
</td>
</tr>
<tr id="row449160145090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413047878090253"><a name="p1413047878090253"></a><a name="p1413047878090253"></a><a href="parameter.md#gad1a95a2a073bf7f78c6a8513e29c3ddc">GetBuildType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727684991090253"><a name="p727684991090253"></a><a name="p727684991090253"></a>char * </p>
<p id="p1937327938090253"><a name="p1937327938090253"></a><a name="p1937327938090253"></a>Obtains the build type. </p>
</td>
</tr>
<tr id="row2092921742090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1928746957090253"><a name="p1928746957090253"></a><a name="p1928746957090253"></a><a href="parameter.md#gaa49edb9e675d928790a8ca7332905659">GetBuildUser</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600894166090253"><a name="p600894166090253"></a><a name="p600894166090253"></a>char * </p>
<p id="p149621907090253"><a name="p149621907090253"></a><a name="p149621907090253"></a>Obtains the build account user name. </p>
</td>
</tr>
<tr id="row1371218312090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p510729632090253"><a name="p510729632090253"></a><a name="p510729632090253"></a><a href="parameter.md#ga54aad44d8a1c01ee1a3af82b5464e616">GetBuildHost</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1577863598090253"><a name="p1577863598090253"></a><a name="p1577863598090253"></a>char * </p>
<p id="p989634434090253"><a name="p989634434090253"></a><a name="p989634434090253"></a>Obtains the build host name. </p>
</td>
</tr>
<tr id="row207694609090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106582078090253"><a name="p2106582078090253"></a><a name="p2106582078090253"></a><a href="parameter.md#ga6707dd0565fd65ab18149aa70ec233ac">GetBuildTime</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1181112842090253"><a name="p1181112842090253"></a><a name="p1181112842090253"></a>char * </p>
<p id="p1914448352090253"><a name="p1914448352090253"></a><a name="p1914448352090253"></a>Obtains the version build time. </p>
</td>
</tr>
<tr id="row1912850669090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1294657829090253"><a name="p1294657829090253"></a><a name="p1294657829090253"></a><a href="parameter.md#ga26f28a1bf6f0f3c550c716223397673c">GetBuildRootHash</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1181327302090253"><a name="p1181327302090253"></a><a name="p1181327302090253"></a>char * </p>
<p id="p1161435923090253"><a name="p1161435923090253"></a><a name="p1161435923090253"></a>Obtains the buildroot hash value of this version. </p>
</td>
</tr>
</tbody>
</table>

