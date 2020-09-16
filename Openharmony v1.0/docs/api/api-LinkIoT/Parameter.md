# Parameter<a name="ZH-CN_TOPIC_0000001055675014"></a>

## **Overview**<a name="section2040956696090252"></a>

Provides functions for obtaining system parameters. 

This module can obtain device information such as device type and manufacturer. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section262122634090252"></a>

## Files<a name="files"></a>

<a name="table1688690852090252"></a>
<table><thead align="left"><tr id="row437280217090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1627314734090252"><a name="p1627314734090252"></a><a name="p1627314734090252"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1632121223090252"><a name="p1632121223090252"></a><a name="p1632121223090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1553965245090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112308717090252"><a name="p112308717090252"></a><a name="p112308717090252"></a><a href="parameter-h.md">parameter.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1897536787090252"><a name="p1897536787090252"></a><a name="p1897536787090252"></a>Declares functions for obtaining system parameters. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table624166717090252"></a>
<table><thead align="left"><tr id="row1056578116090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2144263055090252"><a name="p2144263055090252"></a><a name="p2144263055090252"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1617293712090252"><a name="p1617293712090252"></a><a name="p1617293712090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row932810788090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1673483853090252"><a name="p1673483853090252"></a><a name="p1673483853090252"></a><a href="Parameter.md#gae6a476fa36d2b1876eee0e4f256db6a6">GetParameter</a> (const char *key, const char *def, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445408033090252"><a name="p1445408033090252"></a><a name="p1445408033090252"></a>int&nbsp;</p>
<p id="p563029969090252"><a name="p563029969090252"></a><a name="p563029969090252"></a>Obtains a system parameter matching the specified <strong id="b1032051281090252"><a name="b1032051281090252"></a><a name="b1032051281090252"></a>key</strong>. </p>
</td>
</tr>
<tr id="row1307691396090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275967121090252"><a name="p275967121090252"></a><a name="p275967121090252"></a><a href="Parameter.md#ga2779b5e59d43308c51f7be38b9c98ddb">SetParameter</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847965871090252"><a name="p1847965871090252"></a><a name="p1847965871090252"></a>int&nbsp;</p>
<p id="p1314636322090252"><a name="p1314636322090252"></a><a name="p1314636322090252"></a>Sets or updates a system parameter. </p>
</td>
</tr>
<tr id="row875057868090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980767321090252"><a name="p980767321090252"></a><a name="p980767321090252"></a><a href="Parameter.md#ga2d6e83004da9cfdef6f3162d484163f1">GetProductType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p816741169090252"><a name="p816741169090252"></a><a name="p816741169090252"></a>char *&nbsp;</p>
<p id="p1137141307090252"><a name="p1137141307090252"></a><a name="p1137141307090252"></a>Obtains the device type. </p>
</td>
</tr>
<tr id="row2125597950090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p297071298090252"><a name="p297071298090252"></a><a name="p297071298090252"></a><a href="Parameter.md#gad6d21dda3b027eb603dd24c7315ee6ea">GetManufacture</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1603900349090252"><a name="p1603900349090252"></a><a name="p1603900349090252"></a>char *&nbsp;</p>
<p id="p171278431090252"><a name="p171278431090252"></a><a name="p171278431090252"></a>Obtains the device manufacturer. </p>
</td>
</tr>
<tr id="row1213301020090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1812989726090252"><a name="p1812989726090252"></a><a name="p1812989726090252"></a><a href="Parameter.md#gaba787cc6f740d7d8f5e7ccd5a98fc7ed">GetBrand</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351424179090252"><a name="p1351424179090252"></a><a name="p1351424179090252"></a>char *&nbsp;</p>
<p id="p1150029038090252"><a name="p1150029038090252"></a><a name="p1150029038090252"></a>Obtains the device brand. </p>
</td>
</tr>
<tr id="row930271424090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773961769090252"><a name="p1773961769090252"></a><a name="p1773961769090252"></a><a href="Parameter.md#gaa3adb204e5affd0a9e18828c1fbf2b0b">GetMarketName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858479720090252"><a name="p858479720090252"></a><a name="p858479720090252"></a>char *&nbsp;</p>
<p id="p1407675180090252"><a name="p1407675180090252"></a><a name="p1407675180090252"></a>Obtains the device marketing name. </p>
</td>
</tr>
<tr id="row1617115083090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8249725090252"><a name="p8249725090252"></a><a name="p8249725090252"></a><a href="Parameter.md#ga8a0d394075a3cbafe7ef0f51d08319a8">GetProductSeries</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p263334908090252"><a name="p263334908090252"></a><a name="p263334908090252"></a>char *&nbsp;</p>
<p id="p598326783090252"><a name="p598326783090252"></a><a name="p598326783090252"></a>Obtains the device series name. </p>
</td>
</tr>
<tr id="row1548253674090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319180026090252"><a name="p319180026090252"></a><a name="p319180026090252"></a><a href="Parameter.md#gaa62644b77184644fac848f54837f4e5b">GetProductModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2068829317090252"><a name="p2068829317090252"></a><a name="p2068829317090252"></a>char *&nbsp;</p>
<p id="p1112331969090252"><a name="p1112331969090252"></a><a name="p1112331969090252"></a>Obtains the device authentication model. </p>
</td>
</tr>
<tr id="row1126189852090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140214174090252"><a name="p1140214174090252"></a><a name="p1140214174090252"></a><a href="Parameter.md#ga309a7fb6d9a60f6d6453e3faea030d7a">GetSoftwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555905253090252"><a name="p1555905253090252"></a><a name="p1555905253090252"></a>char *&nbsp;</p>
<p id="p1191363673090252"><a name="p1191363673090252"></a><a name="p1191363673090252"></a>Obtains the device software model. </p>
</td>
</tr>
<tr id="row1882596141090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288969206090252"><a name="p1288969206090252"></a><a name="p1288969206090252"></a><a href="Parameter.md#ga0ff61721ab17eb07fcece1ccaf40293a">GetHardwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432923802090252"><a name="p1432923802090252"></a><a name="p1432923802090252"></a>char *&nbsp;</p>
<p id="p1772836848090252"><a name="p1772836848090252"></a><a name="p1772836848090252"></a>Obtains the device hardware model. </p>
</td>
</tr>
<tr id="row690207607090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p464631606090252"><a name="p464631606090252"></a><a name="p464631606090252"></a><a href="Parameter.md#gaf98290ad8bd5328aff40293ff42d6a9b">GetHardwareProfile</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567615925090252"><a name="p1567615925090252"></a><a name="p1567615925090252"></a>char *&nbsp;</p>
<p id="p1770647288090252"><a name="p1770647288090252"></a><a name="p1770647288090252"></a>Obtains the device hardware profile. </p>
</td>
</tr>
<tr id="row1921065716090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146142586090252"><a name="p2146142586090252"></a><a name="p2146142586090252"></a><a href="Parameter.md#gacc29ceeab6d312f3becdf19b28b9185d">GetSerial</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541008822090252"><a name="p1541008822090252"></a><a name="p1541008822090252"></a>char *&nbsp;</p>
<p id="p967380808090252"><a name="p967380808090252"></a><a name="p967380808090252"></a>Obtains the device serial number (SN). </p>
</td>
</tr>
<tr id="row97632552090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p251166277090252"><a name="p251166277090252"></a><a name="p251166277090252"></a><a href="Parameter.md#ga1402657e793875973f8801f631c29781">GetOsName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1517299799090252"><a name="p1517299799090252"></a><a name="p1517299799090252"></a>char *&nbsp;</p>
<p id="p179755500090252"><a name="p179755500090252"></a><a name="p179755500090252"></a>Obtains the operating system (OS) name. </p>
</td>
</tr>
<tr id="row1163407656090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908273051090252"><a name="p908273051090252"></a><a name="p908273051090252"></a><a href="Parameter.md#gaacd61c8a367a307d5b5c3e907822f271">GetDisplayVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p410869132090252"><a name="p410869132090252"></a><a name="p410869132090252"></a>char *&nbsp;</p>
<p id="p1482028887090252"><a name="p1482028887090252"></a><a name="p1482028887090252"></a>Obtains the software version visible to users. </p>
</td>
</tr>
<tr id="row1102365474090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618281961090252"><a name="p618281961090252"></a><a name="p618281961090252"></a><a href="Parameter.md#gab033380f4acabc3304c401ea40034a3b">GetBootloaderVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p33171130090252"><a name="p33171130090252"></a><a name="p33171130090252"></a>char *&nbsp;</p>
<p id="p176769296090252"><a name="p176769296090252"></a><a name="p176769296090252"></a>Obtains the bootloader version of this device. </p>
</td>
</tr>
<tr id="row1803411652090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p125951321090252"><a name="p125951321090252"></a><a name="p125951321090252"></a><a href="Parameter.md#gaa2407d8ce39e4a151b7e9d45123794c2">GetSecurityPatchTag</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p98923128090252"><a name="p98923128090252"></a><a name="p98923128090252"></a>char *&nbsp;</p>
<p id="p356540229090252"><a name="p356540229090252"></a><a name="p356540229090252"></a>Obtains the security patch tag. </p>
</td>
</tr>
<tr id="row734473816090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881499344090252"><a name="p1881499344090252"></a><a name="p1881499344090252"></a><a href="Parameter.md#gaa5e3d6179f398e407b632cc53410cd1a">GetAbiList</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1708765549090252"><a name="p1708765549090252"></a><a name="p1708765549090252"></a>char *&nbsp;</p>
<p id="p1394346758090252"><a name="p1394346758090252"></a><a name="p1394346758090252"></a>Obtains the list of application binary interfaces (ABIs) supported on this device. </p>
</td>
</tr>
<tr id="row2097795580090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p544547905090252"><a name="p544547905090252"></a><a name="p544547905090252"></a><a href="Parameter.md#ga4720291ec5700581109e2f7943e2e371">GetSdkApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310202916090252"><a name="p1310202916090252"></a><a name="p1310202916090252"></a>char *&nbsp;</p>
<p id="p340307495090252"><a name="p340307495090252"></a><a name="p340307495090252"></a>Obtains the SDK API level that matches the current system software. </p>
</td>
</tr>
<tr id="row1052890058090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p101396792090252"><a name="p101396792090252"></a><a name="p101396792090252"></a><a href="Parameter.md#ga6f62d683d76a160775b3ac46e856955e">GetFirstApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2045412838090252"><a name="p2045412838090252"></a><a name="p2045412838090252"></a>char *&nbsp;</p>
<p id="p1772203570090252"><a name="p1772203570090252"></a><a name="p1772203570090252"></a>Obtains the first SDK API level of the system software. </p>
</td>
</tr>
<tr id="row1973808837090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1136483230090252"><a name="p1136483230090252"></a><a name="p1136483230090252"></a><a href="Parameter.md#ga3d52b0a354555dbb16c265d5d5923546">GetIncrementalVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533064707090252"><a name="p1533064707090252"></a><a name="p1533064707090252"></a>char *&nbsp;</p>
<p id="p1951676183090252"><a name="p1951676183090252"></a><a name="p1951676183090252"></a>Obtains the incremental version. </p>
</td>
</tr>
<tr id="row1304089105090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1213040213090252"><a name="p1213040213090252"></a><a name="p1213040213090252"></a><a href="Parameter.md#gaea3cb294680fcef18a0a52f35fdaa124">GetVersionId</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1211889955090252"><a name="p1211889955090252"></a><a name="p1211889955090252"></a>char *&nbsp;</p>
<p id="p532184115090252"><a name="p532184115090252"></a><a name="p532184115090252"></a>Obtains the version ID. </p>
</td>
</tr>
<tr id="row40338864090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p718831451090252"><a name="p718831451090252"></a><a name="p718831451090252"></a><a href="Parameter.md#gad1a95a2a073bf7f78c6a8513e29c3ddc">GetBuildType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630165623090252"><a name="p630165623090252"></a><a name="p630165623090252"></a>char *&nbsp;</p>
<p id="p63319430090252"><a name="p63319430090252"></a><a name="p63319430090252"></a>Obtains the build type. </p>
</td>
</tr>
<tr id="row349366819090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p23054045090252"><a name="p23054045090252"></a><a name="p23054045090252"></a><a href="Parameter.md#gaa49edb9e675d928790a8ca7332905659">GetBuildUser</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1517873593090252"><a name="p1517873593090252"></a><a name="p1517873593090252"></a>char *&nbsp;</p>
<p id="p1628275459090252"><a name="p1628275459090252"></a><a name="p1628275459090252"></a>Obtains the build account user name. </p>
</td>
</tr>
<tr id="row1455188442090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363217629090252"><a name="p363217629090252"></a><a name="p363217629090252"></a><a href="Parameter.md#ga54aad44d8a1c01ee1a3af82b5464e616">GetBuildHost</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p550687274090252"><a name="p550687274090252"></a><a name="p550687274090252"></a>char *&nbsp;</p>
<p id="p517353253090252"><a name="p517353253090252"></a><a name="p517353253090252"></a>Obtains the build host name. </p>
</td>
</tr>
<tr id="row669453698090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2050649103090252"><a name="p2050649103090252"></a><a name="p2050649103090252"></a><a href="Parameter.md#ga6707dd0565fd65ab18149aa70ec233ac">GetBuildTime</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305567139090252"><a name="p1305567139090252"></a><a name="p1305567139090252"></a>char *&nbsp;</p>
<p id="p605541122090252"><a name="p605541122090252"></a><a name="p605541122090252"></a>Obtains the version build time. </p>
</td>
</tr>
<tr id="row128576920090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1965170219090252"><a name="p1965170219090252"></a><a name="p1965170219090252"></a><a href="Parameter.md#ga26f28a1bf6f0f3c550c716223397673c">GetBuildRootHash</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078368763090252"><a name="p1078368763090252"></a><a name="p1078368763090252"></a>char *&nbsp;</p>
<p id="p1119240449090252"><a name="p1119240449090252"></a><a name="p1119240449090252"></a>Obtains the buildroot hash value of this version. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1529164679090252"></a>

## **Function Documentation**<a name="section207820489090252"></a>

## GetAbiList\(\)<a name="gaa5e3d6179f398e407b632cc53410cd1a"></a>

```
char* GetAbiList (void )
```

 **Description:**

Obtains the list of application binary interfaces \(ABIs\) supported on this device. 

The interfaces in the ABI list are separated by commas \(,\). This function is available only for an OS with an ecosystem accommodating native applications. 

**Returns:**

Returns the ABI list if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBootloaderVersion\(\)<a name="gab033380f4acabc3304c401ea40034a3b"></a>

```
char* GetBootloaderVersion (void )
```

 **Description:**

Obtains the bootloader version of this device. 

The bootloader version can have a maximum length of 64 characters. 

**Returns:**

Returns the bootloader version if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBrand\(\)<a name="gaba787cc6f740d7d8f5e7ccd5a98fc7ed"></a>

```
char* GetBrand (void )
```

 **Description:**

Obtains the device brand. 

The device brand can have a maximum length of 32 characters. 

**Returns:**

Returns the device brand if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBuildHost\(\)<a name="ga54aad44d8a1c01ee1a3af82b5464e616"></a>

```
char* GetBuildHost (void )
```

 **Description:**

Obtains the build host name. 

The build host name can have a maximum length of 32 characters. 

**Returns:**

Returns the build host name if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBuildRootHash\(\)<a name="ga26f28a1bf6f0f3c550c716223397673c"></a>

```
char* GetBuildRootHash (void )
```

 **Description:**

Obtains the buildroot hash value of this version. 

The buildroot hash value is represented by the root hash value in the software version hash tree. 

**Returns:**

Returns the buildroot hash value if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBuildTime\(\)<a name="ga6707dd0565fd65ab18149aa70ec233ac"></a>

```
char* GetBuildTime (void )
```

 **Description:**

Obtains the version build time. 

The version build time is represented by the number of milliseconds elapsed since 1970-01-01 00:00:00 GMT. 

**Returns:**

Returns the version build time if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBuildType\(\)<a name="gad1a95a2a073bf7f78c6a8513e29c3ddc"></a>

```
char* GetBuildType (void )
```

 **Description:**

Obtains the build type. 

Different build types with the same baseline codes will be returned, for example,  **debug/release**  and  **log/nolog**. Multiple build types can be separated by semicolons \(;\). 

**Returns:**

Returns the build type if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetBuildUser\(\)<a name="gaa49edb9e675d928790a8ca7332905659"></a>

```
char* GetBuildUser (void )
```

 **Description:**

Obtains the build account user name. 

The build account user name can have a maximum length of 32 characters. 

**Returns:**

Returns the build account user name if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetDisplayVersion\(\)<a name="gaacd61c8a367a307d5b5c3e907822f271"></a>

```
char* GetDisplayVersion (void )
```

 **Description:**

Obtains the software version visible to users. 

The software version visible to users can have a maximum length of 64 characters. 

**Returns:**

Returns the software version visible to users if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetFirstApiLevel\(\)<a name="ga6f62d683d76a160775b3ac46e856955e"></a>

```
char* GetFirstApiLevel (void )
```

 **Description:**

Obtains the first SDK API level of the system software. 

In general, the first SDK API level is an integer. This function is only available for an OS with an ecosystem. 

**Returns:**

Returns the first SDK API level if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetHardwareModel\(\)<a name="ga0ff61721ab17eb07fcece1ccaf40293a"></a>

```
char* GetHardwareModel (void )
```

 **Description:**

Obtains the device hardware model. 

The device hardware model can have a maximum length of 32 characters. 

**Returns:**

Returns the device hardware model if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetHardwareProfile\(\)<a name="gaf98290ad8bd5328aff40293ff42d6a9b"></a>

```
char* GetHardwareProfile (void )
```

 **Description:**

Obtains the device hardware profile. 

The device hardware profile is a string in JSON format and has a maximum length of 1000 characters. 

**Returns:**

Returns the device hardware profile if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. The JSON field in the device hardware profile is defined as follows: 

<a name="table1062691174090252"></a>
<table><thead align="left"><tr id="row251905452090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1356788590090252"><a name="p1356788590090252"></a><a name="p1356788590090252"></a>Description </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p302066452090252"><a name="p302066452090252"></a><a name="p302066452090252"></a>key  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1486181137090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1776532344090252"><a name="p1776532344090252"></a><a name="p1776532344090252"></a>Audio playback </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1968408227090252"><a name="p1968408227090252"></a><a name="p1968408227090252"></a>aout </p>
</td>
</tr>
<tr id="row2081194574090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1689077176090252"><a name="p1689077176090252"></a><a name="p1689077176090252"></a>Display </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457706885090252"><a name="p457706885090252"></a><a name="p457706885090252"></a>display </p>
</td>
</tr>
<tr id="row583615648090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643052035090252"><a name="p1643052035090252"></a><a name="p1643052035090252"></a>Camera </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p421849755090252"><a name="p421849755090252"></a><a name="p421849755090252"></a>camera </p>
</td>
</tr>
<tr id="row1416597976090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084083067090252"><a name="p2084083067090252"></a><a name="p2084083067090252"></a>2D acceleration capability </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338441684090252"><a name="p1338441684090252"></a><a name="p1338441684090252"></a>DMA_2D </p>
</td>
</tr>
<tr id="row1803250631090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1788250788090252"><a name="p1788250788090252"></a><a name="p1788250788090252"></a>Random-access memory </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1631115424090252"><a name="p1631115424090252"></a><a name="p1631115424090252"></a>RAM </p>
</td>
</tr>
<tr id="row1632529803090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p53586633090252"><a name="p53586633090252"></a><a name="p53586633090252"></a>Read-only memory </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073057916090252"><a name="p2073057916090252"></a><a name="p2073057916090252"></a>ROM </p>
</td>
</tr>
<tr id="row811605079090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p516762800090252"><a name="p516762800090252"></a><a name="p516762800090252"></a>Graphics processing unit </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1289628992090252"><a name="p1289628992090252"></a><a name="p1289628992090252"></a>GPU </p>
</td>
</tr>
<tr id="row1797409692090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p654942734090252"><a name="p654942734090252"></a><a name="p654942734090252"></a>Neural-network processing unit </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2002883252090252"><a name="p2002883252090252"></a><a name="p2002883252090252"></a>NPU </p>
</td>
</tr>
<tr id="row1771276335090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p560035848090252"><a name="p560035848090252"></a><a name="p560035848090252"></a>Radio </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946739906090252"><a name="p1946739906090252"></a><a name="p1946739906090252"></a>radio </p>
</td>
</tr>
<tr id="row1967561705090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p567131903090252"><a name="p567131903090252"></a><a name="p567131903090252"></a>Bluetooth </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884801842090252"><a name="p884801842090252"></a><a name="p884801842090252"></a>bluetooth </p>
</td>
</tr>
<tr id="row452138850090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p667760162090252"><a name="p667760162090252"></a><a name="p667760162090252"></a>Wi-Fi </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1428558769090252"><a name="p1428558769090252"></a><a name="p1428558769090252"></a>WIFI </p>
</td>
</tr>
<tr id="row1917986293090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p783277336090252"><a name="p783277336090252"></a><a name="p783277336090252"></a>USB </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p806560836090252"><a name="p806560836090252"></a><a name="p806560836090252"></a>usbhost </p>
</td>
</tr>
</tbody>
</table>

## GetIncrementalVersion\(\)<a name="ga3d52b0a354555dbb16c265d5d5923546"></a>

```
char* GetIncrementalVersion (void )
```

 **Description:**

Obtains the incremental version. 

The incremental version can be used as the unique software version when the device model is the same. 

**Returns:**

Returns the incremental version if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetManufacture\(\)<a name="gad6d21dda3b027eb603dd24c7315ee6ea"></a>

```
char* GetManufacture (void )
```

 **Description:**

Obtains the device manufacturer. 

The device manufacturer can have a maximum length of 32 characters. 

**Returns:**

Returns the device manufacturer if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetMarketName\(\)<a name="gaa3adb204e5affd0a9e18828c1fbf2b0b"></a>

```
char* GetMarketName (void )
```

 **Description:**

Obtains the device marketing name. 

The device marketing name can have a maximum length of 32 characters. 

**Returns:**

Returns the device marketing name if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetOsName\(\)<a name="ga1402657e793875973f8801f631c29781"></a>

```
char* GetOsName (void )
```

 **Description:**

Obtains the operating system \(OS\) name. 

The device OS name can have a maximum length of 32 characters. 

**Returns:**

Returns the device OS name if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetParameter\(\)<a name="gae6a476fa36d2b1876eee0e4f256db6a6"></a>

```
int GetParameter (const char * key, const char * def, char * value, unsigned int len )
```

 **Description:**

Obtains a system parameter matching the specified  **key**. 

If no system parameter is found, the  **def**  parameter will be returned. 

**Parameters:**

<a name="table584728230090252"></a>
<table><thead align="left"><tr id="row1520922523090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p278326812090252"><a name="p278326812090252"></a><a name="p278326812090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1592749319090252"><a name="p1592749319090252"></a><a name="p1592749319090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1271625395090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key for the system parameter to query. The value can contain lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row1636069936090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the default value to return when no query result is found. This parameter is specified by the caller. </td>
</tr>
<tr id="row1082125015090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data buffer that stores the query result. This parameter is applied for and released by the caller and can be used as an output parameter. </td>
</tr>
<tr id="row871169891090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data in the buffer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of bytes of the system parameter if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



## GetProductModel\(\)<a name="gaa62644b77184644fac848f54837f4e5b"></a>

```
char* GetProductModel (void )
```

 **Description:**

Obtains the device authentication model. 

The device authentication model can have a maximum length of 32 characters. 

**Returns:**

Returns the device authentication model if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetProductSeries\(\)<a name="ga8a0d394075a3cbafe7ef0f51d08319a8"></a>

```
char* GetProductSeries (void )
```

 **Description:**

Obtains the device series name. 

The device series name can have a maximum length of 32 characters. 

**Returns:**

Returns the device series name if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetProductType\(\)<a name="ga2d6e83004da9cfdef6f3162d484163f1"></a>

```
char* GetProductType (void )
```

 **Description:**

Obtains the device type. 

The device type can have a maximum length of 32 characters. 

**Returns:**

Returns the device type if a result is found, for example, returns  **wifiiot**  if the application is running on a Wi-Fi connected IoT device; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetSdkApiLevel\(\)<a name="ga4720291ec5700581109e2f7943e2e371"></a>

```
char* GetSdkApiLevel (void )
```

 **Description:**

Obtains the SDK API level that matches the current system software. 

In general, the SDK API level is an integer. This function is only available for an OS with an ecosystem. 

**Returns:**

Returns the SDK API level if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetSecurityPatchTag\(\)<a name="gaa2407d8ce39e4a151b7e9d45123794c2"></a>

```
char* GetSecurityPatchTag (void )
```

 **Description:**

Obtains the security patch tag. 

**Returns:**

Returns the security patch tag if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetSerial\(\)<a name="gacc29ceeab6d312f3becdf19b28b9185d"></a>

```
char* GetSerial (void )
```

 **Description:**

Obtains the device serial number \(SN\). 

The device SN can have a maximum length of 64 characters. 

**Returns:**

Returns the device SN if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetSoftwareModel\(\)<a name="ga309a7fb6d9a60f6d6453e3faea030d7a"></a>

```
char* GetSoftwareModel (void )
```

 **Description:**

Obtains the device software model. 

The device software model can have a maximum length of 32 characters. 

**Returns:**

Returns the device software model if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## GetVersionId\(\)<a name="gaea3cb294680fcef18a0a52f35fdaa124"></a>

```
char* GetVersionId (void )
```

 **Description:**

Obtains the version ID. 

The version ID can have a maximum length of 127 characters. It is the unique identifier of a device. 

**Returns:**

Returns the version ID if a result is found; returns  **NULL**  otherwise. The return result is released by the caller. 



## SetParameter\(\)<a name="ga2779b5e59d43308c51f7be38b9c98ddb"></a>

```
int SetParameter (const char * key, const char * value )
```

 **Description:**

Sets or updates a system parameter. 

You can use this function to set a system parameter that matches  **key**  as  **value**. 

**Parameters:**

<a name="table1031241137090252"></a>
<table><thead align="left"><tr id="row1802993833090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p337024397090252"><a name="p337024397090252"></a><a name="p337024397090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1108121953090252"><a name="p1108121953090252"></a><a name="p1108121953090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row417866710090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key for the parameter to set or update. The value can contain lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row522818540090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the system parameter value. Its length cannot exceed 128 bytes (including the end-of-text character in the string). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



