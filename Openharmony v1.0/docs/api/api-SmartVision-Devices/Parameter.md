# Parameter<a name="ZH-CN_TOPIC_0000001054718083"></a>

## **Overview**<a name="section916691467093523"></a>

Provides functions for obtaining system parameters. 

This module can obtain device information such as device type and manufacturer. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1334321569093523"></a>

## Files<a name="files"></a>

<a name="table1091010746093523"></a>
<table><thead align="left"><tr id="row1248861041093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1728401573093523"><a name="p1728401573093523"></a><a name="p1728401573093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1877853050093523"><a name="p1877853050093523"></a><a name="p1877853050093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1639769413093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140487342093523"><a name="p1140487342093523"></a><a name="p1140487342093523"></a><a href="parameter-h.md">parameter.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221033526093523"><a name="p221033526093523"></a><a name="p221033526093523"></a>Declares functions for obtaining system parameters. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table152934388093523"></a>
<table><thead align="left"><tr id="row1931302609093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1116466615093523"><a name="p1116466615093523"></a><a name="p1116466615093523"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p733739402093523"><a name="p733739402093523"></a><a name="p733739402093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1020220054093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092998029093523"><a name="p2092998029093523"></a><a name="p2092998029093523"></a><a href="Parameter.md#gae6a476fa36d2b1876eee0e4f256db6a6">GetParameter</a> (const char *key, const char *def, char *value, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1882815170093523"><a name="p1882815170093523"></a><a name="p1882815170093523"></a>int&nbsp;</p>
<p id="p398194718093523"><a name="p398194718093523"></a><a name="p398194718093523"></a>Obtains a system parameter matching the specified <strong id="b811523460093523"><a name="b811523460093523"></a><a name="b811523460093523"></a>key</strong>. </p>
</td>
</tr>
<tr id="row516669785093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561252009093523"><a name="p1561252009093523"></a><a name="p1561252009093523"></a><a href="Parameter.md#ga2779b5e59d43308c51f7be38b9c98ddb">SetParameter</a> (const char *key, const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264661786093523"><a name="p264661786093523"></a><a name="p264661786093523"></a>int&nbsp;</p>
<p id="p198237632093523"><a name="p198237632093523"></a><a name="p198237632093523"></a>Sets or updates a system parameter. </p>
</td>
</tr>
<tr id="row499435826093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119444072093523"><a name="p1119444072093523"></a><a name="p1119444072093523"></a><a href="Parameter.md#ga2d6e83004da9cfdef6f3162d484163f1">GetProductType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313840134093523"><a name="p1313840134093523"></a><a name="p1313840134093523"></a>char *&nbsp;</p>
<p id="p1979423143093523"><a name="p1979423143093523"></a><a name="p1979423143093523"></a>Obtains the device type. </p>
</td>
</tr>
<tr id="row1486087999093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p18278811093523"><a name="p18278811093523"></a><a name="p18278811093523"></a><a href="Parameter.md#gad6d21dda3b027eb603dd24c7315ee6ea">GetManufacture</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1299279981093523"><a name="p1299279981093523"></a><a name="p1299279981093523"></a>char *&nbsp;</p>
<p id="p415050108093523"><a name="p415050108093523"></a><a name="p415050108093523"></a>Obtains the device manufacturer. </p>
</td>
</tr>
<tr id="row929437629093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p338850531093523"><a name="p338850531093523"></a><a name="p338850531093523"></a><a href="Parameter.md#gaba787cc6f740d7d8f5e7ccd5a98fc7ed">GetBrand</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p21256843093523"><a name="p21256843093523"></a><a name="p21256843093523"></a>char *&nbsp;</p>
<p id="p1643984360093523"><a name="p1643984360093523"></a><a name="p1643984360093523"></a>Obtains the device brand. </p>
</td>
</tr>
<tr id="row1765685357093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2097463510093523"><a name="p2097463510093523"></a><a name="p2097463510093523"></a><a href="Parameter.md#gaa3adb204e5affd0a9e18828c1fbf2b0b">GetMarketName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1607330401093523"><a name="p1607330401093523"></a><a name="p1607330401093523"></a>char *&nbsp;</p>
<p id="p1187060220093523"><a name="p1187060220093523"></a><a name="p1187060220093523"></a>Obtains the device marketing name. </p>
</td>
</tr>
<tr id="row248358973093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275004468093523"><a name="p275004468093523"></a><a name="p275004468093523"></a><a href="Parameter.md#ga8a0d394075a3cbafe7ef0f51d08319a8">GetProductSeries</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1324899406093523"><a name="p1324899406093523"></a><a name="p1324899406093523"></a>char *&nbsp;</p>
<p id="p1745516668093523"><a name="p1745516668093523"></a><a name="p1745516668093523"></a>Obtains the device series name. </p>
</td>
</tr>
<tr id="row449315299093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1329084388093523"><a name="p1329084388093523"></a><a name="p1329084388093523"></a><a href="Parameter.md#gaa62644b77184644fac848f54837f4e5b">GetProductModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p716523645093523"><a name="p716523645093523"></a><a name="p716523645093523"></a>char *&nbsp;</p>
<p id="p1148297952093523"><a name="p1148297952093523"></a><a name="p1148297952093523"></a>Obtains the device authentication model. </p>
</td>
</tr>
<tr id="row756000334093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170301001093523"><a name="p170301001093523"></a><a name="p170301001093523"></a><a href="Parameter.md#ga309a7fb6d9a60f6d6453e3faea030d7a">GetSoftwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1104137557093523"><a name="p1104137557093523"></a><a name="p1104137557093523"></a>char *&nbsp;</p>
<p id="p1379173536093523"><a name="p1379173536093523"></a><a name="p1379173536093523"></a>Obtains the device software model. </p>
</td>
</tr>
<tr id="row1675599114093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328224660093523"><a name="p328224660093523"></a><a name="p328224660093523"></a><a href="Parameter.md#ga0ff61721ab17eb07fcece1ccaf40293a">GetHardwareModel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1724109733093523"><a name="p1724109733093523"></a><a name="p1724109733093523"></a>char *&nbsp;</p>
<p id="p1578380183093523"><a name="p1578380183093523"></a><a name="p1578380183093523"></a>Obtains the device hardware model. </p>
</td>
</tr>
<tr id="row1761878580093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p536570485093523"><a name="p536570485093523"></a><a name="p536570485093523"></a><a href="Parameter.md#gaf98290ad8bd5328aff40293ff42d6a9b">GetHardwareProfile</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p958168334093523"><a name="p958168334093523"></a><a name="p958168334093523"></a>char *&nbsp;</p>
<p id="p707759194093523"><a name="p707759194093523"></a><a name="p707759194093523"></a>Obtains the device hardware profile. </p>
</td>
</tr>
<tr id="row1247599877093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2009746469093523"><a name="p2009746469093523"></a><a name="p2009746469093523"></a><a href="Parameter.md#gacc29ceeab6d312f3becdf19b28b9185d">GetSerial</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1840005117093523"><a name="p1840005117093523"></a><a name="p1840005117093523"></a>char *&nbsp;</p>
<p id="p1455410709093523"><a name="p1455410709093523"></a><a name="p1455410709093523"></a>Obtains the device serial number (SN). </p>
</td>
</tr>
<tr id="row1697329777093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636918761093523"><a name="p1636918761093523"></a><a name="p1636918761093523"></a><a href="Parameter.md#ga1402657e793875973f8801f631c29781">GetOsName</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996545081093523"><a name="p996545081093523"></a><a name="p996545081093523"></a>char *&nbsp;</p>
<p id="p1702593018093523"><a name="p1702593018093523"></a><a name="p1702593018093523"></a>Obtains the operating system (OS) name. </p>
</td>
</tr>
<tr id="row1572013438093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1473262768093523"><a name="p1473262768093523"></a><a name="p1473262768093523"></a><a href="Parameter.md#gaacd61c8a367a307d5b5c3e907822f271">GetDisplayVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p39896933093523"><a name="p39896933093523"></a><a name="p39896933093523"></a>char *&nbsp;</p>
<p id="p1836309266093523"><a name="p1836309266093523"></a><a name="p1836309266093523"></a>Obtains the software version visible to users. </p>
</td>
</tr>
<tr id="row255946012093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183773978093523"><a name="p183773978093523"></a><a name="p183773978093523"></a><a href="Parameter.md#gab033380f4acabc3304c401ea40034a3b">GetBootloaderVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p886296348093523"><a name="p886296348093523"></a><a name="p886296348093523"></a>char *&nbsp;</p>
<p id="p754253369093523"><a name="p754253369093523"></a><a name="p754253369093523"></a>Obtains the bootloader version of this device. </p>
</td>
</tr>
<tr id="row364476806093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1554949555093523"><a name="p1554949555093523"></a><a name="p1554949555093523"></a><a href="Parameter.md#gaa2407d8ce39e4a151b7e9d45123794c2">GetSecurityPatchTag</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101119099093523"><a name="p1101119099093523"></a><a name="p1101119099093523"></a>char *&nbsp;</p>
<p id="p518331584093523"><a name="p518331584093523"></a><a name="p518331584093523"></a>Obtains the security patch tag. </p>
</td>
</tr>
<tr id="row936882442093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p387947115093523"><a name="p387947115093523"></a><a name="p387947115093523"></a><a href="Parameter.md#gaa5e3d6179f398e407b632cc53410cd1a">GetAbiList</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p131242343093523"><a name="p131242343093523"></a><a name="p131242343093523"></a>char *&nbsp;</p>
<p id="p1878753534093523"><a name="p1878753534093523"></a><a name="p1878753534093523"></a>Obtains the list of application binary interfaces (ABIs) supported on this device. </p>
</td>
</tr>
<tr id="row1398996054093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1109412012093523"><a name="p1109412012093523"></a><a name="p1109412012093523"></a><a href="Parameter.md#ga4720291ec5700581109e2f7943e2e371">GetSdkApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2024078415093523"><a name="p2024078415093523"></a><a name="p2024078415093523"></a>char *&nbsp;</p>
<p id="p1945282121093523"><a name="p1945282121093523"></a><a name="p1945282121093523"></a>Obtains the SDK API level that matches the current system software. </p>
</td>
</tr>
<tr id="row474514530093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p510507751093523"><a name="p510507751093523"></a><a name="p510507751093523"></a><a href="Parameter.md#ga6f62d683d76a160775b3ac46e856955e">GetFirstApiLevel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356723414093523"><a name="p356723414093523"></a><a name="p356723414093523"></a>char *&nbsp;</p>
<p id="p467908179093523"><a name="p467908179093523"></a><a name="p467908179093523"></a>Obtains the first SDK API level of the system software. </p>
</td>
</tr>
<tr id="row689093441093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879486719093523"><a name="p879486719093523"></a><a name="p879486719093523"></a><a href="Parameter.md#ga3d52b0a354555dbb16c265d5d5923546">GetIncrementalVersion</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1210474311093523"><a name="p1210474311093523"></a><a name="p1210474311093523"></a>char *&nbsp;</p>
<p id="p958170233093523"><a name="p958170233093523"></a><a name="p958170233093523"></a>Obtains the incremental version. </p>
</td>
</tr>
<tr id="row2110253737093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1637011210093523"><a name="p1637011210093523"></a><a name="p1637011210093523"></a><a href="Parameter.md#gaea3cb294680fcef18a0a52f35fdaa124">GetVersionId</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572131669093523"><a name="p572131669093523"></a><a name="p572131669093523"></a>char *&nbsp;</p>
<p id="p1003059329093523"><a name="p1003059329093523"></a><a name="p1003059329093523"></a>Obtains the version ID. </p>
</td>
</tr>
<tr id="row1296764116093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123310986093523"><a name="p123310986093523"></a><a name="p123310986093523"></a><a href="Parameter.md#gad1a95a2a073bf7f78c6a8513e29c3ddc">GetBuildType</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p997308206093523"><a name="p997308206093523"></a><a name="p997308206093523"></a>char *&nbsp;</p>
<p id="p1853281070093523"><a name="p1853281070093523"></a><a name="p1853281070093523"></a>Obtains the build type. </p>
</td>
</tr>
<tr id="row621677990093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102103534093523"><a name="p2102103534093523"></a><a name="p2102103534093523"></a><a href="Parameter.md#gaa49edb9e675d928790a8ca7332905659">GetBuildUser</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2027486460093523"><a name="p2027486460093523"></a><a name="p2027486460093523"></a>char *&nbsp;</p>
<p id="p872797589093523"><a name="p872797589093523"></a><a name="p872797589093523"></a>Obtains the build account user name. </p>
</td>
</tr>
<tr id="row251286060093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773359516093523"><a name="p773359516093523"></a><a name="p773359516093523"></a><a href="Parameter.md#ga54aad44d8a1c01ee1a3af82b5464e616">GetBuildHost</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p568602662093523"><a name="p568602662093523"></a><a name="p568602662093523"></a>char *&nbsp;</p>
<p id="p435137115093523"><a name="p435137115093523"></a><a name="p435137115093523"></a>Obtains the build host name. </p>
</td>
</tr>
<tr id="row1781230758093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908351599093523"><a name="p908351599093523"></a><a name="p908351599093523"></a><a href="Parameter.md#ga6707dd0565fd65ab18149aa70ec233ac">GetBuildTime</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p753788626093523"><a name="p753788626093523"></a><a name="p753788626093523"></a>char *&nbsp;</p>
<p id="p1220106210093523"><a name="p1220106210093523"></a><a name="p1220106210093523"></a>Obtains the version build time. </p>
</td>
</tr>
<tr id="row923031911093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p772494946093523"><a name="p772494946093523"></a><a name="p772494946093523"></a><a href="Parameter.md#ga26f28a1bf6f0f3c550c716223397673c">GetBuildRootHash</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48845147093523"><a name="p48845147093523"></a><a name="p48845147093523"></a>char *&nbsp;</p>
<p id="p535740538093523"><a name="p535740538093523"></a><a name="p535740538093523"></a>Obtains the buildroot hash value of this version. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section321351981093523"></a>

## **Function Documentation**<a name="section1462025626093523"></a>

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

<a name="table1580441615093523"></a>
<table><thead align="left"><tr id="row1291834144093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1198703222093523"><a name="p1198703222093523"></a><a name="p1198703222093523"></a>Description </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1598493399093523"><a name="p1598493399093523"></a><a name="p1598493399093523"></a>key  </p>
</th>
</tr>
</thead>
<tbody><tr id="row425125485093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1223746831093523"><a name="p1223746831093523"></a><a name="p1223746831093523"></a>Audio playback </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53020346093523"><a name="p53020346093523"></a><a name="p53020346093523"></a>aout </p>
</td>
</tr>
<tr id="row1385593769093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994108726093523"><a name="p1994108726093523"></a><a name="p1994108726093523"></a>Display </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999530869093523"><a name="p1999530869093523"></a><a name="p1999530869093523"></a>display </p>
</td>
</tr>
<tr id="row433524928093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791147140093523"><a name="p1791147140093523"></a><a name="p1791147140093523"></a>Camera </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1606987096093523"><a name="p1606987096093523"></a><a name="p1606987096093523"></a>camera </p>
</td>
</tr>
<tr id="row1054223029093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p427566820093523"><a name="p427566820093523"></a><a name="p427566820093523"></a>2D acceleration capability </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436284920093523"><a name="p436284920093523"></a><a name="p436284920093523"></a>DMA_2D </p>
</td>
</tr>
<tr id="row1460295583093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p513072201093523"><a name="p513072201093523"></a><a name="p513072201093523"></a>Random-access memory </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765924691093523"><a name="p765924691093523"></a><a name="p765924691093523"></a>RAM </p>
</td>
</tr>
<tr id="row344349361093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p502868672093523"><a name="p502868672093523"></a><a name="p502868672093523"></a>Read-only memory </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687315571093523"><a name="p1687315571093523"></a><a name="p1687315571093523"></a>ROM </p>
</td>
</tr>
<tr id="row750088250093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302119573093523"><a name="p1302119573093523"></a><a name="p1302119573093523"></a>Graphics processing unit </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1528288179093523"><a name="p1528288179093523"></a><a name="p1528288179093523"></a>GPU </p>
</td>
</tr>
<tr id="row1435473161093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p248894306093523"><a name="p248894306093523"></a><a name="p248894306093523"></a>Neural-network processing unit </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1284515491093523"><a name="p1284515491093523"></a><a name="p1284515491093523"></a>NPU </p>
</td>
</tr>
<tr id="row832412248093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144244684093523"><a name="p2144244684093523"></a><a name="p2144244684093523"></a>Radio </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964405780093523"><a name="p964405780093523"></a><a name="p964405780093523"></a>radio </p>
</td>
</tr>
<tr id="row984743211093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p461261962093523"><a name="p461261962093523"></a><a name="p461261962093523"></a>Bluetooth </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1747425900093523"><a name="p1747425900093523"></a><a name="p1747425900093523"></a>bluetooth </p>
</td>
</tr>
<tr id="row1300941378093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260486586093523"><a name="p260486586093523"></a><a name="p260486586093523"></a>Wi-Fi </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601297181093523"><a name="p1601297181093523"></a><a name="p1601297181093523"></a>WIFI </p>
</td>
</tr>
<tr id="row251964019093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p929453925093523"><a name="p929453925093523"></a><a name="p929453925093523"></a>USB </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1818877276093523"><a name="p1818877276093523"></a><a name="p1818877276093523"></a>usbhost </p>
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

<a name="table1504013536093523"></a>
<table><thead align="left"><tr id="row2144234814093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1189881401093523"><a name="p1189881401093523"></a><a name="p1189881401093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1722945605093523"><a name="p1722945605093523"></a><a name="p1722945605093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row336398849093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key for the system parameter to query. The value can contain lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row578196924093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the default value to return when no query result is found. This parameter is specified by the caller. </td>
</tr>
<tr id="row419733018093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data buffer that stores the query result. This parameter is applied for and released by the caller and can be used as an output parameter. </td>
</tr>
<tr id="row665063266093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
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

<a name="table1768670811093523"></a>
<table><thead align="left"><tr id="row864910666093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p664293457093523"><a name="p664293457093523"></a><a name="p664293457093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p480218148093523"><a name="p480218148093523"></a><a name="p480218148093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1532336283093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key for the parameter to set or update. The value can contain lowercase letters, digits, underscores (_), and dots (.). Its length cannot exceed 32 bytes (including the end-of-text character in the string). </td>
</tr>
<tr id="row1056192134093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the system parameter value. Its length cannot exceed 128 bytes (including the end-of-text character in the string). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-9**  if a parameter is incorrect; returns  **-1**  in other scenarios. 



