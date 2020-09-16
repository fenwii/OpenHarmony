# parameter.h<a name="ZH-CN_TOPIC_0000001054598137"></a>

## **Overview**<a name="section127048515093526"></a>

**Related Modules:**

[Parameter](Parameter.md)

**Description:**

Declares functions for obtaining system parameters. 

You can use the provided functions to obtain device information such as device type and manufacturer. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1618514149093526"></a>

## Functions<a name="func-members"></a>

<a name="table733111625093526"></a>
<table><thead align="left"><tr id="row575813877093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p696697431093526"><a name="p696697431093526"></a><a name="p696697431093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1356045183093526"><a name="p1356045183093526"></a><a name="p1356045183093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1285720453093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206104182093526"><a name="p206104182093526"></a><a name="p206104182093526"></a><a href="Parameter.md#gae6a476fa36d2b1876eee0e4f256db6a6">GetParameter</a> (const char *key, const char *def, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444500031093526"><a name="p444500031093526"></a><a name="p444500031093526"></a>int&nbsp;</p>
<p id="p1679314155093526"><a name="p1679314155093526"></a><a name="p1679314155093526"></a>Obtains a system parameter matching the specified <strong id="b1335936869093526"><a name="b1335936869093526"></a><a name="b1335936869093526"></a>key</strong>. </p>
</td>
</tr>
<tr id="row1783791610093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139375521093526"><a name="p2139375521093526"></a><a name="p2139375521093526"></a><a href="Parameter.md#ga2779b5e59d43308c51f7be38b9c98ddb">SetParameter</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427129204093526"><a name="p1427129204093526"></a><a name="p1427129204093526"></a>int&nbsp;</p>
<p id="p1698306071093526"><a name="p1698306071093526"></a><a name="p1698306071093526"></a>Sets or updates a system parameter. </p>
</td>
</tr>
<tr id="row1024990172093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395490943093526"><a name="p1395490943093526"></a><a name="p1395490943093526"></a><a href="Parameter.md#ga2d6e83004da9cfdef6f3162d484163f1">GetProductType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351743143093526"><a name="p351743143093526"></a><a name="p351743143093526"></a>char *&nbsp;</p>
<p id="p1911851488093526"><a name="p1911851488093526"></a><a name="p1911851488093526"></a>Obtains the device type. </p>
</td>
</tr>
<tr id="row269229994093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841319269093526"><a name="p1841319269093526"></a><a name="p1841319269093526"></a><a href="Parameter.md#gad6d21dda3b027eb603dd24c7315ee6ea">GetManufacture</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871949540093526"><a name="p1871949540093526"></a><a name="p1871949540093526"></a>char *&nbsp;</p>
<p id="p169538106093526"><a name="p169538106093526"></a><a name="p169538106093526"></a>Obtains the device manufacturer. </p>
</td>
</tr>
<tr id="row1578935332093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1678089340093526"><a name="p1678089340093526"></a><a name="p1678089340093526"></a><a href="Parameter.md#gaba787cc6f740d7d8f5e7ccd5a98fc7ed">GetBrand</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p204781998093526"><a name="p204781998093526"></a><a name="p204781998093526"></a>char *&nbsp;</p>
<p id="p541336489093526"><a name="p541336489093526"></a><a name="p541336489093526"></a>Obtains the device brand. </p>
</td>
</tr>
<tr id="row1454245172093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1480141176093526"><a name="p1480141176093526"></a><a name="p1480141176093526"></a><a href="Parameter.md#gaa3adb204e5affd0a9e18828c1fbf2b0b">GetMarketName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14595653093526"><a name="p14595653093526"></a><a name="p14595653093526"></a>char *&nbsp;</p>
<p id="p1933577032093526"><a name="p1933577032093526"></a><a name="p1933577032093526"></a>Obtains the device marketing name. </p>
</td>
</tr>
<tr id="row1739329032093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1012547436093526"><a name="p1012547436093526"></a><a name="p1012547436093526"></a><a href="Parameter.md#ga8a0d394075a3cbafe7ef0f51d08319a8">GetProductSeries</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p184887966093526"><a name="p184887966093526"></a><a name="p184887966093526"></a>char *&nbsp;</p>
<p id="p47454048093526"><a name="p47454048093526"></a><a name="p47454048093526"></a>Obtains the device series name. </p>
</td>
</tr>
<tr id="row1290738908093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1130347580093526"><a name="p1130347580093526"></a><a name="p1130347580093526"></a><a href="Parameter.md#gaa62644b77184644fac848f54837f4e5b">GetProductModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p541682230093526"><a name="p541682230093526"></a><a name="p541682230093526"></a>char *&nbsp;</p>
<p id="p1708658996093526"><a name="p1708658996093526"></a><a name="p1708658996093526"></a>Obtains the device authentication model. </p>
</td>
</tr>
<tr id="row1029005678093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1172847806093526"><a name="p1172847806093526"></a><a name="p1172847806093526"></a><a href="Parameter.md#ga309a7fb6d9a60f6d6453e3faea030d7a">GetSoftwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p709658716093526"><a name="p709658716093526"></a><a name="p709658716093526"></a>char *&nbsp;</p>
<p id="p1884561428093526"><a name="p1884561428093526"></a><a name="p1884561428093526"></a>Obtains the device software model. </p>
</td>
</tr>
<tr id="row1648538042093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832688697093526"><a name="p832688697093526"></a><a name="p832688697093526"></a><a href="Parameter.md#ga0ff61721ab17eb07fcece1ccaf40293a">GetHardwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197707001093526"><a name="p1197707001093526"></a><a name="p1197707001093526"></a>char *&nbsp;</p>
<p id="p184025731093526"><a name="p184025731093526"></a><a name="p184025731093526"></a>Obtains the device hardware model. </p>
</td>
</tr>
<tr id="row739505327093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p276505842093526"><a name="p276505842093526"></a><a name="p276505842093526"></a><a href="Parameter.md#gaf98290ad8bd5328aff40293ff42d6a9b">GetHardwareProfile</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1489747235093526"><a name="p1489747235093526"></a><a name="p1489747235093526"></a>char *&nbsp;</p>
<p id="p1787016655093526"><a name="p1787016655093526"></a><a name="p1787016655093526"></a>Obtains the device hardware profile. </p>
</td>
</tr>
<tr id="row899485290093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652413139093526"><a name="p1652413139093526"></a><a name="p1652413139093526"></a><a href="Parameter.md#gacc29ceeab6d312f3becdf19b28b9185d">GetSerial</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p525966006093526"><a name="p525966006093526"></a><a name="p525966006093526"></a>char *&nbsp;</p>
<p id="p1988398468093526"><a name="p1988398468093526"></a><a name="p1988398468093526"></a>Obtains the device serial number (SN). </p>
</td>
</tr>
<tr id="row1501995421093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284395503093526"><a name="p284395503093526"></a><a name="p284395503093526"></a><a href="Parameter.md#ga1402657e793875973f8801f631c29781">GetOsName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p972535341093526"><a name="p972535341093526"></a><a name="p972535341093526"></a>char *&nbsp;</p>
<p id="p1009030034093526"><a name="p1009030034093526"></a><a name="p1009030034093526"></a>Obtains the operating system (OS) name. </p>
</td>
</tr>
<tr id="row1840811539093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2117231104093526"><a name="p2117231104093526"></a><a name="p2117231104093526"></a><a href="Parameter.md#gaacd61c8a367a307d5b5c3e907822f271">GetDisplayVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300975510093526"><a name="p1300975510093526"></a><a name="p1300975510093526"></a>char *&nbsp;</p>
<p id="p2058749495093526"><a name="p2058749495093526"></a><a name="p2058749495093526"></a>Obtains the software version visible to users. </p>
</td>
</tr>
<tr id="row1411208247093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p150604706093526"><a name="p150604706093526"></a><a name="p150604706093526"></a><a href="Parameter.md#gab033380f4acabc3304c401ea40034a3b">GetBootloaderVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1634573192093526"><a name="p1634573192093526"></a><a name="p1634573192093526"></a>char *&nbsp;</p>
<p id="p1675294114093526"><a name="p1675294114093526"></a><a name="p1675294114093526"></a>Obtains the bootloader version of this device. </p>
</td>
</tr>
<tr id="row948143441093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000312853093526"><a name="p1000312853093526"></a><a name="p1000312853093526"></a><a href="Parameter.md#gaa2407d8ce39e4a151b7e9d45123794c2">GetSecurityPatchTag</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823595725093526"><a name="p823595725093526"></a><a name="p823595725093526"></a>char *&nbsp;</p>
<p id="p706741897093526"><a name="p706741897093526"></a><a name="p706741897093526"></a>Obtains the security patch tag. </p>
</td>
</tr>
<tr id="row991887046093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040379158093526"><a name="p2040379158093526"></a><a name="p2040379158093526"></a><a href="Parameter.md#gaa5e3d6179f398e407b632cc53410cd1a">GetAbiList</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p358434469093526"><a name="p358434469093526"></a><a name="p358434469093526"></a>char *&nbsp;</p>
<p id="p1273859455093526"><a name="p1273859455093526"></a><a name="p1273859455093526"></a>Obtains the list of application binary interfaces (ABIs) supported on this device. </p>
</td>
</tr>
<tr id="row1610970610093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860842195093526"><a name="p1860842195093526"></a><a name="p1860842195093526"></a><a href="Parameter.md#ga4720291ec5700581109e2f7943e2e371">GetSdkApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1934676665093526"><a name="p1934676665093526"></a><a name="p1934676665093526"></a>char *&nbsp;</p>
<p id="p982438614093526"><a name="p982438614093526"></a><a name="p982438614093526"></a>Obtains the SDK API level that matches the current system software. </p>
</td>
</tr>
<tr id="row346996081093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p364300669093526"><a name="p364300669093526"></a><a name="p364300669093526"></a><a href="Parameter.md#ga6f62d683d76a160775b3ac46e856955e">GetFirstApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616677510093526"><a name="p1616677510093526"></a><a name="p1616677510093526"></a>char *&nbsp;</p>
<p id="p1702744619093526"><a name="p1702744619093526"></a><a name="p1702744619093526"></a>Obtains the first SDK API level of the system software. </p>
</td>
</tr>
<tr id="row443706190093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898549468093526"><a name="p898549468093526"></a><a name="p898549468093526"></a><a href="Parameter.md#ga3d52b0a354555dbb16c265d5d5923546">GetIncrementalVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1392891194093526"><a name="p1392891194093526"></a><a name="p1392891194093526"></a>char *&nbsp;</p>
<p id="p463639923093526"><a name="p463639923093526"></a><a name="p463639923093526"></a>Obtains the incremental version. </p>
</td>
</tr>
<tr id="row104049401093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550099178093526"><a name="p1550099178093526"></a><a name="p1550099178093526"></a><a href="Parameter.md#gaea3cb294680fcef18a0a52f35fdaa124">GetVersionId</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666346667093526"><a name="p1666346667093526"></a><a name="p1666346667093526"></a>char *&nbsp;</p>
<p id="p984381299093526"><a name="p984381299093526"></a><a name="p984381299093526"></a>Obtains the version ID. </p>
</td>
</tr>
<tr id="row766715739093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220269837093526"><a name="p220269837093526"></a><a name="p220269837093526"></a><a href="Parameter.md#gad1a95a2a073bf7f78c6a8513e29c3ddc">GetBuildType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224008191093526"><a name="p224008191093526"></a><a name="p224008191093526"></a>char *&nbsp;</p>
<p id="p1118624157093526"><a name="p1118624157093526"></a><a name="p1118624157093526"></a>Obtains the build type. </p>
</td>
</tr>
<tr id="row228893744093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408523894093526"><a name="p1408523894093526"></a><a name="p1408523894093526"></a><a href="Parameter.md#gaa49edb9e675d928790a8ca7332905659">GetBuildUser</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1287223175093526"><a name="p1287223175093526"></a><a name="p1287223175093526"></a>char *&nbsp;</p>
<p id="p1308541123093526"><a name="p1308541123093526"></a><a name="p1308541123093526"></a>Obtains the build account user name. </p>
</td>
</tr>
<tr id="row1286119286093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33296698093526"><a name="p33296698093526"></a><a name="p33296698093526"></a><a href="Parameter.md#ga54aad44d8a1c01ee1a3af82b5464e616">GetBuildHost</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1077439714093526"><a name="p1077439714093526"></a><a name="p1077439714093526"></a>char *&nbsp;</p>
<p id="p2131691592093526"><a name="p2131691592093526"></a><a name="p2131691592093526"></a>Obtains the build host name. </p>
</td>
</tr>
<tr id="row581417692093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p489540653093526"><a name="p489540653093526"></a><a name="p489540653093526"></a><a href="Parameter.md#ga6707dd0565fd65ab18149aa70ec233ac">GetBuildTime</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1299458188093526"><a name="p1299458188093526"></a><a name="p1299458188093526"></a>char *&nbsp;</p>
<p id="p1846099690093526"><a name="p1846099690093526"></a><a name="p1846099690093526"></a>Obtains the version build time. </p>
</td>
</tr>
<tr id="row642631996093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804327731093526"><a name="p804327731093526"></a><a name="p804327731093526"></a><a href="Parameter.md#ga26f28a1bf6f0f3c550c716223397673c">GetBuildRootHash</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844051119093526"><a name="p844051119093526"></a><a name="p844051119093526"></a>char *&nbsp;</p>
<p id="p2007109902093526"><a name="p2007109902093526"></a><a name="p2007109902093526"></a>Obtains the buildroot hash value of this version. </p>
</td>
</tr>
</tbody>
</table>

