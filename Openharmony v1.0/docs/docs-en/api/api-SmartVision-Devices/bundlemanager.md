# BundleManager<a name="EN-US_TOPIC_0000001054918105"></a>

## **Overview**<a name="section1167531519093521"></a>

Provides structures and functions for managing application bundles and obtaining application information. 

You can use functions provided by this module to install, update, or uninstall an application, obtain  [AbilityInfo](abilityinfo.md)  and  [BundleInfo](bundleinfo.md)  about an application, and obtain the bundle name of an application based on the application's user ID \(UID\).

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1700513019093521"></a>

## Files<a name="files"></a>

<a name="table306398054093521"></a>
<table><thead align="left"><tr id="row1793113913093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p919981763093521"><a name="p919981763093521"></a><a name="p919981763093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p732970626093521"><a name="p732970626093521"></a><a name="p732970626093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1869706205093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p747288203093521"><a name="p747288203093521"></a><a name="p747288203093521"></a><a href="ability_info-h.md">ability_info.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1620921144093521"><a name="p1620921144093521"></a><a name="p1620921144093521"></a>Declares structures and functions for managing ability information. </p>
</td>
</tr>
<tr id="row1607180618093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416400925093521"><a name="p416400925093521"></a><a name="p416400925093521"></a><a href="appexecfwk_errors-h.md">appexecfwk_errors.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861480779093521"><a name="p861480779093521"></a><a name="p861480779093521"></a>Declares error codes returned by bundle management functions. </p>
</td>
</tr>
<tr id="row676168500093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p13523210093521"><a name="p13523210093521"></a><a name="p13523210093521"></a><a href="bundle_info-h.md">bundle_info.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941027504093521"><a name="p941027504093521"></a><a name="p941027504093521"></a>Declares structures and functions for managing application bundle information. </p>
</td>
</tr>
<tr id="row2134376377093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p765709369093521"><a name="p765709369093521"></a><a name="p765709369093521"></a><a href="bundle_manager-h.md">bundle_manager.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1906008099093521"><a name="p1906008099093521"></a><a name="p1906008099093521"></a>Declares functions used for managing application bundles and obtaining bundle information. </p>
</td>
</tr>
<tr id="row1723044627093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535925580093521"><a name="p1535925580093521"></a><a name="p1535925580093521"></a><a href="element_name-h.md">element_name.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1128859850093521"><a name="p1128859850093521"></a><a name="p1128859850093521"></a>Declares the structure that defines the required information for querying <a href="abilityinfo.md">AbilityInfo</a>, including the device ID, bundle name, and class name, and functions for setting such information. </p>
</td>
</tr>
<tr id="row486388225093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p534542925093521"><a name="p534542925093521"></a><a name="p534542925093521"></a><a href="module_info-h.md">module_info.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p240703501093521"><a name="p240703501093521"></a><a name="p240703501093521"></a>Declares structures and functions for managing HAP package information. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1030983785093521"></a>
<table><thead align="left"><tr id="row660381627093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p285032353093521"><a name="p285032353093521"></a><a name="p285032353093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1128761498093521"><a name="p1128761498093521"></a><a name="p1128761498093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1850014023093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1584578457093521"><a name="p1584578457093521"></a><a name="p1584578457093521"></a><a href="abilityinfo.md">AbilityInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p500432909093521"><a name="p500432909093521"></a><a name="p500432909093521"></a>Defines the ability information. </p>
</td>
</tr>
<tr id="row1851248532093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183474961093521"><a name="p183474961093521"></a><a name="p183474961093521"></a><a href="bundleinfo.md">BundleInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p192903337093521"><a name="p192903337093521"></a><a name="p192903337093521"></a>Defines the bundle information. </p>
</td>
</tr>
<tr id="row16962057093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2120342730093521"><a name="p2120342730093521"></a><a name="p2120342730093521"></a><a href="elementname.md">ElementName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839340808093521"><a name="p839340808093521"></a><a name="p839340808093521"></a>Defines the ability information. </p>
</td>
</tr>
<tr id="row225977623093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1163858266093521"><a name="p1163858266093521"></a><a name="p1163858266093521"></a><a href="metadata.md">MetaData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p863846640093521"><a name="p863846640093521"></a><a name="p863846640093521"></a>Defines the metadata information in a <a href="moduleinfo.md">ModuleInfo</a> object. </p>
</td>
</tr>
<tr id="row1620653953093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p628156997093521"><a name="p628156997093521"></a><a name="p628156997093521"></a><a href="moduleinfo.md">ModuleInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665750187093521"><a name="p1665750187093521"></a><a name="p1665750187093521"></a>Defines the HAP information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1036294948093521"></a>
<table><thead align="left"><tr id="row542578146093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1954455529093521"><a name="p1954455529093521"></a><a name="p1954455529093521"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1754604855093521"><a name="p1754604855093521"></a><a name="p1754604855093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2004666810093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100179586093521"><a name="p2100179586093521"></a><a name="p2100179586093521"></a><a href="bundlemanager.md#ga00f021e76d728d2d44e1a28887ccc3af">InstallerCallback</a>) (const uint8_t resultCode, const void *resultMessage)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265532883093521"><a name="p265532883093521"></a><a name="p265532883093521"></a>typedef void(* </p>
<p id="p1328599859093521"><a name="p1328599859093521"></a><a name="p1328599859093521"></a>Called when an application is installed, updated, or uninstalled. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1901382664093521"></a>
<table><thead align="left"><tr id="row2051079811093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1329321181093521"><a name="p1329321181093521"></a><a name="p1329321181093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p602219339093521"><a name="p602219339093521"></a><a name="p602219339093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row95913554093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1910762204093521"><a name="p1910762204093521"></a><a name="p1910762204093521"></a><a href="bundlemanager.md#ga44b675d687acff3d739404c1227b4259">AbilityType</a> { <a href="bundlemanager.md#gga44b675d687acff3d739404c1227b4259a6ce26a62afab55d7606ad4e92428b30c">UNKNOWN</a> = 0, <a href="bundlemanager.md#gga44b675d687acff3d739404c1227b4259ab788d9e2cde88d51a5cda409f75db490">PAGE</a>, <a href="bundlemanager.md#gga44b675d687acff3d739404c1227b4259a5f6d448017ecd0a56245e38b76596e07">SERVICE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p465484643093521"><a name="p465484643093521"></a><a name="p465484643093521"></a>Enumerates types of templates used by an ability. </p>
</td>
</tr>
<tr id="row859041213093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1923390096093521"><a name="p1923390096093521"></a><a name="p1923390096093521"></a><a href="bundlemanager.md#ga605d46d860e356a74db6842e66522854">LaunchMode</a> { <a href="bundlemanager.md#gga605d46d860e356a74db6842e66522854a57da18394d2f90538c40b0b8d4a3a3c7">SINGLETON</a> = 0, <a href="bundlemanager.md#gga605d46d860e356a74db6842e66522854a9de934790934fe831fe946c851e8338e">STANDARD</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p136414741093521"><a name="p136414741093521"></a><a name="p136414741093521"></a>Enumerates startup modes of an ability. </p>
</td>
</tr>
<tr id="row1966402120093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381974435093521"><a name="p381974435093521"></a><a name="p381974435093521"></a><a href="bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1">AppexecfwkErrors</a> {   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb">ERR_OK</a> = 0, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ac56903bcb53061d4ccd81f356e2e6dff">ERR_APPEXECFWK_QUERY_PARAMETER_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a6609bd5ca64e005d23794eb0a9e65058">ERR_APPEXECFWK_QUERY_NO_INFOS</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a862f4edaae059afe7505f3a2355ace7a">ERR_APPEXECFWK_QUERY_INFOS_INIT_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a5d6b76480d9c381a4ea582e42ae13723">ERR_APPEXECFWK_OBJECT_NULL</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ab6bf660df1f71efbbc1dc171026e8b19">ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR</a> = 10, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a0d0ff29443bea7409cb49aa65276a734">ERR_APPEXECFWK_INSTALL_FAILED_PARAM_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ab5e45300939da4427f50b6a765701e34">ERR_APPEXECFWK_INSTALL_FAILED_FILE_PATH_INVALID</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a6242775e55f8eb650cc92fd8a3388e32">ERR_APPEXECFWK_INSTALL_FAILED_FILE_NOT_EXISTS</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a3f98ba8a2755dbb204d87abc64744d62">ERR_APPEXECFWK_INSTALL_FAILED_INVALID_FILE_NAME</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a74a6ca143ea4633376530ee2e9ce6eb1">ERR_APPEXECFWK_INSTALL_FAILED_BAD_FILE</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a02521dcb943509971fe14bfb8468a98d">ERR_APPEXECFWK_INSTALL_FAILED_CREATE_FILE_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a7786ae72ec65692f14a5f2049dc5a2a7">ERR_APPEXECFWK_INSTALL_FAILED_CREATE_CODE_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a2f5e672b7bf5e4149cdae0770ad200dc">ERR_APPEXECFWK_INSTALL_FAILED_REMOVE_CODE_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a72f16cafaafe6ff6e7069a2ef28507a7">ERR_APPEXECFWK_INSTALL_FAILED_CREATE_PERMISSIONS_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ab0d26918c1d8d1481601567cf87f2621">ERR_APPEXECFWK_INSTALL_FAILED_RENAME_DIR_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aaafdb262ffe01eed1722350d270cf09d">ERR_APPEXECFWK_INSTALL_FAILED_RENAME_FILE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1abe5bafc9885f41ff2d7fa348be381d66">ERR_APPEXECFWK_INSTALL_FAILED_REMOVE_DATA_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a9e457f181dce9e221dfa01c257d7fe12">ERR_APPEXECFWK_INSTALL_FAILED_CREATE_DATA_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ac62be957615c89ae23b780d8d288419e">ERR_APPEXECFWK_INSTALL_FAILED_RECORD_INFO_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a438581dc1abee81ed846d9dafee34e83">ERR_APPEXECFWK_INSTALL_FAILED_UID_AND_GID_BACKUP_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ad8e03ac63b84d45685f3b655717d3c92">ERR_APPEXECFWK_INSTALL_FAILED_CHOWN_DATA_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a0d874b79e811844325c76f65630db989">ERR_APPEXECFWK_INSTALL_FAILED_VERSION_DOWNGRADE</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a6ef4ca2fed2c05c5ec553f4e12844bac">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_BUNDLE_NUMBER</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a8599367df053820365395e64ae536e81">ERR_APPEXECFWK_INSTALL_FAILED_STORE_PERMISSIONS_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1adb1e3b901e0a5b88460f661a533b08f8">ERR_APPEXECFWK_INSTALL_FAILED_FILE_DATA_INVALID</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a2b9a032c6b9c843e1101cf753b2fa6fa">ERR_APPEXECFWK_INSTALL_FAILED_INCOMPATIBLE_SIGNATURE</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ab1dc9dd09156cc2b06643624d8465ea9">ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a06b51bb80923d2d9271f902f75842063">ERR_APPEXECFWK_INSTALL_FAILED_OPERATE_SIGNED_FILE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a34439d18e6612f31ba634766c3da6457">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_APP_SIGNATURE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a553374f3e17c7a39f6fbf9ecd932b618">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_SIGNATURE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a2c992cbdee385fbc00fecd0e313b33fc">ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_SIGNATURE_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a17e1305d5eeee7867a98c295c488e236">ERR_APPEXECFWK_SET_DEBUG_MODE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aef3bf9de62376b9d91070956c1a0b6a0">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR</a> = 40, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a014b98d9df51b98ff37f95aaba97c63f">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_BUNDLENAME_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a1ab7654bdb5ca8fcba99e6acb9ad4163">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a7f159724dde9d3ec69a22fd97c7c4275">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VENDOR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ad569e1e0e50704d8d94394b39df13599">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONCODE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a26e4922b83c0a42f8576cb81cd0760e2">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONNAME_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a022e0b7e7b978eda5e43db46efe9c916">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PERMISSIONS_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ac449d6df4540c1794f1b76599435c4df">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a05262a83fbc2d5817772db9a20d6c503">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICE_CONFIG_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1abcb1a3e0509445e2bff7dad43c379971">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_KEEPALIVE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a27d9af1e04f75bc389f35b3318ad1590">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULENAME_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a38afd7346c84b9d618aa1a477316c3ca">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_MODULENAME</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1af244274d1cf39090d9818aac15882e4c">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULE_DESCRIPTION_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ac36ac4af8d61e10431c39fe545f8f623">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a04f7cee0fe708631364d56e53fc7a2d8">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aba3187880d4a57348ac2cd3943546dd1">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULENAME_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a1c88e191b397644827022b0a238007da">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a9ec099feb69dc64a4f3bd48475723bba">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_DELIVERY_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a98508d3e35c99d09320ffd498469b984">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a1649053e390e2b20ac96674aa7d7ca88">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1adbf64bab15b50b69286efa90f7f1dec1">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_NAME_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aeefcd3f1a247768fc5fb2f59c0f1b966">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_TYPE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a8a282ca74395e3007dd75c90d671fe23">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a3c6dcb2ca14788595975cea51bf1cfed">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a164231485c5ea694f9a0b4d8307d5901">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_DESCRIPTION_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a6a592b570f8c29dc1c4161faedcf2acd">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LAUNCHTYPE_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a7d51c40e62b04e8bc2991db294fd10f3">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_VISIBLE_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa83132144c11442291f4a971e51dcbb1">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME_LENGTH</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a1e7f0159d459e0f416c05bcd106d8782">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_LABEL_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1af6fb04f5b2b34761822d84670f19e7ce">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VERSIONNAME_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a4d20732be30f3bc677ed0fff3b79aa93">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_NAME_LENGTH_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a4ddea99589bb62ae0297742763a12c1a">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_VALUE_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aabd55ad27e4671083b36aa1a9bce53b2">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VENDOR_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a85ed32b668e813a868dff8f11d1a0259">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_MODULENAME_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a2fd9e57b401b4c4ecb7f737d9cfb7f1a">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITYNAME_LENGTH_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1acb65a2d440e7aee4541ea265317582e0">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_DESCRIPTION_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a7d764e29e35ead6dbbca9302c284ee00">ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_LABEL_LENGTH_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aebc061682db1151f24248f0ca34eca98">ERR_APPEXECFWK_INSTALL_FAILED_EXTRACTOR_NOT_INIT</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a797b7558d35fdb43a923aaac8c464187">ERR_APPEXECFWK_INSTALL_FAILED_EXTRACT_HAP_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aeacdda0db2432c52b0795208bf69408e">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_JS_DIR_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a3a521918e6b836de9b70325a0a643362">ERR_APPEXECFWK_INSTALL_FAILED_RESOURCE_INDEX_NOT_EXISTS</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1acc1f483da695764aa8f3f22d697c8969">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_LABEL_RES_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a572a4b52c204c83b1742eb1fc8364a1a">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ICON_RES_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a128bf2cca7073ed0a6299c7d8529e33d">ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DESCRIPTION_RES_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ac31bcc78028487c5be87399325332380">ERR_APPEXECFWK_INSTALL_FAILED_SEND_REQUEST_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a26ff3a2760ff20c60aba2ab125ecdd17">ERR_APPEXECFWK_UNINSTALL_FAILED_INTERNAL_ERROR</a> = 90, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ae0670ff00ddfc9f4642815d13e50e732">ERR_APPEXECFWK_UNINSTALL_FAILED_PARAM_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a8d6b6bf5861d928ca86ddaeeb15c062a">ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_EXISTS</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a4949cab6b3e4f97fd44151eba0d488bb">ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_DIRS_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a9e5f0727ceed161044cf4bfdacec12e2">ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_RECORD_INFO_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a0050a0cd61152432d89221b3ed178724">ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_PERMISSIONS_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a58c70df1bf55bc3c2b61e2c0f0571a2f">ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_UNINSTALLABLE</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a11b7780ad61c6085f475c5415de34191">ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_UID_INFO_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a1e2b896e9cc48287bed17cd2835f44cb">ERR_APPEXECFWK_UNINSTALL_FAILED_SEND_REQUEST_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a3fbc51865d3bf19ead1c7e42c6058a42">ERR_APPEXECFWK_DUMP_ERROR</a> = 100,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a35c07d2afc0f8b17822a9f64b19a8993">ERR_APPEXECFWK_COMMAND_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a4d22c64508c3f6c3a9c3e8972e54696c">ERR_APPEXECFWK_CALLBACK_REGISTER_FAILED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ae0dd6d1b6cc227e1a67c910182dee9f9">ERR_APPEXECFWK_CALLBACK_UNREGISTER_FAILED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a3fc6a7d606bdfc9a569c732f7fc0dc85">ERR_APPEXECFWK_CALLBACK_GENERATE_LOCAL_SERVICEID_FAILED</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a030663d47f1763759349ab34509a2c1c">ERR_APPEXECFWK_CALLBACK_SERVICEID_TRANSMITTED_FAILED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aeb276d0adcc605cee18e3e06f641626e">ERR_APPEXECFWK_CALLBACK_NEVER_REGISTERED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ab853bfd0b4558a663bd683ab6a365c8b">ERR_APPEXECFWK_CALLBACK_OBTAIN_ALL_BUNDLE_FAILED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a8e8a7a1f2d610d5f078dc79959776930">ERR_APPEXECFWK_CALLBACK_NULL_CORRESPONDING_CALLBACK</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1acb14a1daa5fe17eb25798bbcd98bcd57">ERR_APPEXECFWK_CALLBACK_GET_INSTALLTYPE_FAILED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a8898f52b989730709638b26bcb555f54">ERR_APPEXECFWK_CALLBACK_GET_ERROR_INSTALLTYPE</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1ae31533f402b130eb4cc8fed07706c5b6">ERR_APPEXECFWK_SERIALIZATION_FAILED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a66b8941c7c418eedc7df7f758cbacc42">ERR_APPEXECFWK_DESERIALIZATION_FAILED</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a19aa79fde7b3e4da78567e4fcbe306a7">ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a0ad2ce2d577f995c2ba3ea946ce366e6">ERR_APPEXECFWK_NO_BUNDLENAME_FOR_UID</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a9161dd6c967af438a56b01cd916e01c2">ERR_APPEXECFWK_IPCIO_UNAVAILABLED</a>, <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a6cff9490f5817281ac9c2bcdafcf477f">ERR_APPEXECFWK_INVOKE_ERROR</a>,   <a href="bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1a2c357a03505c34ef9a843876af91739e">ERR_APPEXECFWK_PERMISSION_DENIED</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369097805093521"><a name="p369097805093521"></a><a name="p369097805093521"></a>Enumerates error codes provided by the Bundle Manager <a href="service.md">Service</a>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2061391555093521"></a>
<table><thead align="left"><tr id="row121296279093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1289575734093521"><a name="p1289575734093521"></a><a name="p1289575734093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p728571820093521"><a name="p728571820093521"></a><a name="p728571820093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1674376475093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401644731093521"><a name="p1401644731093521"></a><a name="p1401644731093521"></a><a href="bundlemanager.md#ga7377545918725f75645b59b1b7a319fa">ClearAbilityInfo</a> (<a href="abilityinfo.md">AbilityInfo</a> *abilityInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786550091093521"><a name="p786550091093521"></a><a name="p786550091093521"></a>void </p>
<p id="p1821831815093521"><a name="p1821831815093521"></a><a name="p1821831815093521"></a>Clears an <a href="abilityinfo.md">AbilityInfo</a> object. </p>
</td>
</tr>
<tr id="row1859906909093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p945012461093521"><a name="p945012461093521"></a><a name="p945012461093521"></a><a href="bundlemanager.md#ga78829b21273aefd65844eba4549162ca">ClearBundleInfo</a> (<a href="bundleinfo.md">BundleInfo</a> *bundleInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369027243093521"><a name="p369027243093521"></a><a name="p369027243093521"></a>void </p>
<p id="p368788772093521"><a name="p368788772093521"></a><a name="p368788772093521"></a>Clears a <a href="bundleinfo.md">BundleInfo</a> object. </p>
</td>
</tr>
<tr id="row859193333093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577911181093521"><a name="p577911181093521"></a><a name="p577911181093521"></a><a href="bundlemanager.md#ga5c49620ca8b752cd6f43fabc5d5c7416">RegisterCallback</a> (BundleStatusCallback *BundleStatusCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681533592093521"><a name="p1681533592093521"></a><a name="p1681533592093521"></a>int32_t </p>
<p id="p689589102093521"><a name="p689589102093521"></a><a name="p689589102093521"></a>Registers a callback to monitor the installation, update, and uninstallation state changes of an application. </p>
</td>
</tr>
<tr id="row916699480093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261374341093521"><a name="p261374341093521"></a><a name="p261374341093521"></a><a href="bundlemanager.md#ga095eee592eff6ce71a2a67a1a0e3e344">UnregisterCallback</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623132084093521"><a name="p623132084093521"></a><a name="p623132084093521"></a>int32_t </p>
<p id="p679759869093521"><a name="p679759869093521"></a><a name="p679759869093521"></a>Unregisters a callback previously registered for monitoring the installation, update, and uninstallation state changes of an application. </p>
</td>
</tr>
<tr id="row1930519011093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p923624192093521"><a name="p923624192093521"></a><a name="p923624192093521"></a><a href="bundlemanager.md#gaf1f1521a64cc98f076b0082df6c0abdd">Install</a> (const char *hapPath, const InstallParam *installParam, <a href="bundlemanager.md#ga00f021e76d728d2d44e1a28887ccc3af">InstallerCallback</a> installerCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84818610093521"><a name="p84818610093521"></a><a name="p84818610093521"></a>bool </p>
<p id="p228326753093521"><a name="p228326753093521"></a><a name="p228326753093521"></a>Installs or updates an application. </p>
</td>
</tr>
<tr id="row324116416093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p396691451093521"><a name="p396691451093521"></a><a name="p396691451093521"></a><a href="bundlemanager.md#gaa117e44378315a61b4e71fd252b2e496">Uninstall</a> (const char *bundleName, const InstallParam *installParam, <a href="bundlemanager.md#ga00f021e76d728d2d44e1a28887ccc3af">InstallerCallback</a> installerCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1429507132093521"><a name="p1429507132093521"></a><a name="p1429507132093521"></a>bool </p>
<p id="p993393501093521"><a name="p993393501093521"></a><a name="p993393501093521"></a>Uninstalls an application. </p>
</td>
</tr>
<tr id="row376402025093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1114443723093521"><a name="p1114443723093521"></a><a name="p1114443723093521"></a><a href="bundlemanager.md#ga4360375d15224d89632f59ee110b74c9">QueryAbilityInfo</a> (const <a href="want.md">Want</a> *want, <a href="abilityinfo.md">AbilityInfo</a> *abilityInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733187778093521"><a name="p1733187778093521"></a><a name="p1733187778093521"></a>uint8_t </p>
<p id="p1453439028093521"><a name="p1453439028093521"></a><a name="p1453439028093521"></a>Queries the <a href="abilityinfo.md">AbilityInfo</a> of an ability based on the information carried in the <a href="want.md">Want</a> structure. </p>
</td>
</tr>
<tr id="row400056372093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175657797093521"><a name="p175657797093521"></a><a name="p175657797093521"></a><a href="bundlemanager.md#ga5e81134e037911654e34cc8a7ba01a2f">GetBundleInfo</a> (const char *bundleName, int32_t flags, <a href="bundleinfo.md">BundleInfo</a> *bundleInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367884189093521"><a name="p1367884189093521"></a><a name="p1367884189093521"></a>uint8_t </p>
<p id="p94462384093521"><a name="p94462384093521"></a><a name="p94462384093521"></a>Obtains the <a href="bundleinfo.md">BundleInfo</a> of an application based on the specified bundle name. </p>
</td>
</tr>
<tr id="row1878123309093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p157003656093521"><a name="p157003656093521"></a><a name="p157003656093521"></a><a href="bundlemanager.md#ga2469dafbc61ba8e98b69041c13044cad">GetBundleInfos</a> (const int flags, <a href="bundleinfo.md">BundleInfo</a> **bundleInfos, int32_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453320315093521"><a name="p1453320315093521"></a><a name="p1453320315093521"></a>uint8_t </p>
<p id="p1614233916093521"><a name="p1614233916093521"></a><a name="p1614233916093521"></a>Obtains the <a href="bundleinfo.md">BundleInfo</a> of all bundles in the system. </p>
</td>
</tr>
<tr id="row1382835757093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615448619093521"><a name="p1615448619093521"></a><a name="p1615448619093521"></a><a href="bundlemanager.md#ga0c1cb00194993ecba7337fdf0a203314">QueryKeepAliveBundleInfos</a> (<a href="bundleinfo.md">BundleInfo</a> **bundleInfos, int32_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p92606509093521"><a name="p92606509093521"></a><a name="p92606509093521"></a>uint8_t </p>
<p id="p778632645093521"><a name="p778632645093521"></a><a name="p778632645093521"></a>Obtains the <a href="bundleinfo.md">BundleInfo</a> of all keep-alive applications in the system. </p>
</td>
</tr>
<tr id="row38693616093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p948981354093521"><a name="p948981354093521"></a><a name="p948981354093521"></a><a href="bundlemanager.md#ga711965038390aef4fa0a6b6a98f6998b">GetBundleInfosByMetaData</a> (const char *metaDataKey, <a href="bundleinfo.md">BundleInfo</a> **bundleInfos, int32_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2118879914093521"><a name="p2118879914093521"></a><a name="p2118879914093521"></a>uint8_t </p>
<p id="p1264075806093521"><a name="p1264075806093521"></a><a name="p1264075806093521"></a>Obtains the <a href="bundleinfo.md">BundleInfo</a> of application bundles based on the specified <a href="metadata.md">MetaData</a>. </p>
</td>
</tr>
<tr id="row102360059093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898881225093521"><a name="p898881225093521"></a><a name="p898881225093521"></a><a href="bundlemanager.md#ga4afdc08ba78506fce95a066e137ac46d">GetBundleNameForUid</a> (int32_t uid, char **bundleName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557690892093521"><a name="p1557690892093521"></a><a name="p1557690892093521"></a>uint8_t </p>
<p id="p7034499093521"><a name="p7034499093521"></a><a name="p7034499093521"></a>Obtains the bundle name of an application based on the specified UID. </p>
</td>
</tr>
<tr id="row1963553440093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1089049175093521"><a name="p1089049175093521"></a><a name="p1089049175093521"></a><a href="bundlemanager.md#ga3abe15ac14571de84ca72c98f4009724">ClearElement</a> (<a href="elementname.md">ElementName</a> *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246898233093521"><a name="p246898233093521"></a><a name="p246898233093521"></a>void </p>
<p id="p1077839849093521"><a name="p1077839849093521"></a><a name="p1077839849093521"></a>Clears the internal data of a specified <strong id="b475843173093521"><a name="b475843173093521"></a><a name="b475843173093521"></a><a href="elementname.md">ElementName</a></strong>. </p>
</td>
</tr>
<tr id="row512937472093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p71581386093521"><a name="p71581386093521"></a><a name="p71581386093521"></a><a href="bundlemanager.md#ga90e16f159ee8e7f1a9385feebb3dbc0c">SetElementDeviceID</a> (<a href="elementname.md">ElementName</a> *element, const char *deviceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1076172885093521"><a name="p1076172885093521"></a><a name="p1076172885093521"></a>bool </p>
<p id="p1454612503093521"><a name="p1454612503093521"></a><a name="p1454612503093521"></a>Sets the device ID used to query <a href="abilityinfo.md">AbilityInfo</a>. </p>
</td>
</tr>
<tr id="row1555762653093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1176334384093521"><a name="p1176334384093521"></a><a name="p1176334384093521"></a><a href="bundlemanager.md#ga60692e66a3a204a2f16f70c5cd452c1d">SetElementBundleName</a> (<a href="elementname.md">ElementName</a> *element, const char *bundleName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1377375157093521"><a name="p1377375157093521"></a><a name="p1377375157093521"></a>bool </p>
<p id="p1091204771093521"><a name="p1091204771093521"></a><a name="p1091204771093521"></a>Sets the bundle name used to query <a href="abilityinfo.md">AbilityInfo</a>. </p>
</td>
</tr>
<tr id="row1774171577093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658551431093521"><a name="p658551431093521"></a><a name="p658551431093521"></a><a href="bundlemanager.md#ga93a575cc428cb96526ae02b3997f1f3b">SetElementAbilityName</a> (<a href="elementname.md">ElementName</a> *element, const char *abilityName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1552623744093521"><a name="p1552623744093521"></a><a name="p1552623744093521"></a>bool </p>
<p id="p426377150093521"><a name="p426377150093521"></a><a name="p426377150093521"></a>Sets the class name of the ability used to query <a href="abilityinfo.md">AbilityInfo</a>. </p>
</td>
</tr>
<tr id="row438703208093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132084322093521"><a name="p2132084322093521"></a><a name="p2132084322093521"></a><a href="bundlemanager.md#ga6c2242cc10f135d129b95444faacb345">ClearModuleInfo</a> (<a href="moduleinfo.md">ModuleInfo</a> *moduleInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p595365136093521"><a name="p595365136093521"></a><a name="p595365136093521"></a>void </p>
<p id="p1234973230093521"><a name="p1234973230093521"></a><a name="p1234973230093521"></a>Clears a <a href="moduleinfo.md">ModuleInfo</a> object. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2113244738093521"></a>

## **Typedef Documentation**<a name="section2042361554093521"></a>

## InstallerCallback<a name="ga00f021e76d728d2d44e1a28887ccc3af"></a>

```
typedef void(* InstallerCallback) (const uint8_t resultCode, const void *resultMessage)
```

 **Description:**

Called when an application is installed, updated, or uninstalled. 

This function can be registered through  [Install](bundlemanager.md#gaf1f1521a64cc98f076b0082df6c0abdd)  and  [Uninstall](bundlemanager.md#gaa117e44378315a61b4e71fd252b2e496)  to receive the installation, update, and uninstallation result.

**Parameters:**

<a name="table462878328093521"></a>
<table><thead align="left"><tr id="row58893898093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p53721517093521"><a name="p53721517093521"></a><a name="p53721517093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1962111118093521"><a name="p1962111118093521"></a><a name="p1962111118093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1314325301093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">resultCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the status code returned for the application installation, update, or uninstallation result. For details, see <a href="bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1">AppexecfwkErrors</a>. </td>
</tr>
<tr id="row1497689551093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">resultMessage</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the result message returned with the status code.</td>
</tr>
</tbody>
</table>

## **Enumeration Type Documentation**<a name="section609164103093521"></a>

## AbilityType<a name="ga44b675d687acff3d739404c1227b4259"></a>

```
enum [AbilityType](bundlemanager.md#ga44b675d687acff3d739404c1227b4259)
```

 **Description:**

Enumerates types of templates used by an ability. 

<a name="table1434828994093521"></a>
<table><thead align="left"><tr id="row2112762075093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1119009550093521"><a name="p1119009550093521"></a><a name="p1119009550093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p214173517093521"><a name="p214173517093521"></a><a name="p214173517093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1944238126093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga44b675d687acff3d739404c1227b4259a6ce26a62afab55d7606ad4e92428b30c"><a name="gga44b675d687acff3d739404c1227b4259a6ce26a62afab55d7606ad4e92428b30c"></a><a name="gga44b675d687acff3d739404c1227b4259a6ce26a62afab55d7606ad4e92428b30c"></a></strong>UNKNOWN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165683046093521"><a name="p1165683046093521"></a><a name="p1165683046093521"></a>Unknown </p>
 </td>
</tr>
<tr id="row2064764759093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga44b675d687acff3d739404c1227b4259ab788d9e2cde88d51a5cda409f75db490"><a name="gga44b675d687acff3d739404c1227b4259ab788d9e2cde88d51a5cda409f75db490"></a><a name="gga44b675d687acff3d739404c1227b4259ab788d9e2cde88d51a5cda409f75db490"></a></strong>PAGE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2113490324093521"><a name="p2113490324093521"></a><a name="p2113490324093521"></a>Page </p>
 </td>
</tr>
<tr id="row761144862093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga44b675d687acff3d739404c1227b4259a5f6d448017ecd0a56245e38b76596e07"><a name="gga44b675d687acff3d739404c1227b4259a5f6d448017ecd0a56245e38b76596e07"></a><a name="gga44b675d687acff3d739404c1227b4259a5f6d448017ecd0a56245e38b76596e07"></a></strong>SERVICE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155679750093521"><a name="p1155679750093521"></a><a name="p1155679750093521"></a><a href="service.md">Service</a> </p>
 </td>
</tr>
</tbody>
</table>

## AppexecfwkErrors<a name="gac318d4f4dc0125e2367ea8c539770ed1"></a>

```
enum [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)
```

 **Description:**

Enumerates error codes provided by the Bundle Manager  [Service](service.md). 

<a name="table1262168975093521"></a>
<table><thead align="left"><tr id="row21673050093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p181326643093521"><a name="p181326643093521"></a><a name="p181326643093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p259661758093521"><a name="p259661758093521"></a><a name="p259661758093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1128564832093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb"></a></strong>ERR_OK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1671245110093521"><a name="p1671245110093521"></a><a name="p1671245110093521"></a>The function is successfully called. </p>
 </td>
</tr>
<tr id="row1550376434093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ac56903bcb53061d4ccd81f356e2e6dff"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac56903bcb53061d4ccd81f356e2e6dff"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac56903bcb53061d4ccd81f356e2e6dff"></a></strong>ERR_APPEXECFWK_QUERY_PARAMETER_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216654507093521"><a name="p216654507093521"></a><a name="p216654507093521"></a>Incorrect parameter for querying <a href="abilityinfo.md">AbilityInfo</a> or <a href="bundleinfo.md">BundleInfo</a>. </p>
 </td>
</tr>
<tr id="row171880679093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a6609bd5ca64e005d23794eb0a9e65058"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6609bd5ca64e005d23794eb0a9e65058"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6609bd5ca64e005d23794eb0a9e65058"></a></strong>ERR_APPEXECFWK_QUERY_NO_INFOS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p201025105093521"><a name="p201025105093521"></a><a name="p201025105093521"></a>No <a href="abilityinfo.md">AbilityInfo</a> or <a href="bundleinfo.md">BundleInfo</a> is found. </p>
 </td>
</tr>
<tr id="row1352840430093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a862f4edaae059afe7505f3a2355ace7a"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a862f4edaae059afe7505f3a2355ace7a"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a862f4edaae059afe7505f3a2355ace7a"></a></strong>ERR_APPEXECFWK_QUERY_INFOS_INIT_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1486331419093521"><a name="p1486331419093521"></a><a name="p1486331419093521"></a>An error occurred when initializing <a href="bundleinfo.md">BundleInfo</a> or <a href="abilityinfo.md">AbilityInfo</a> during information query. </p>
 </td>
</tr>
<tr id="row318877754093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a5d6b76480d9c381a4ea582e42ae13723"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a5d6b76480d9c381a4ea582e42ae13723"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a5d6b76480d9c381a4ea582e42ae13723"></a></strong>ERR_APPEXECFWK_OBJECT_NULL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003600519093521"><a name="p2003600519093521"></a><a name="p2003600519093521"></a>The object or pointer is null. </p>
 </td>
</tr>
<tr id="row1550723600093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ab6bf660df1f71efbbc1dc171026e8b19"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab6bf660df1f71efbbc1dc171026e8b19"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab6bf660df1f71efbbc1dc171026e8b19"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342828483093521"><a name="p1342828483093521"></a><a name="p1342828483093521"></a>Failed to install the application due to an internal logic error. </p>
 </td>
</tr>
<tr id="row2106395871093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a0d0ff29443bea7409cb49aa65276a734"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0d0ff29443bea7409cb49aa65276a734"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0d0ff29443bea7409cb49aa65276a734"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARAM_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141020031093521"><a name="p1141020031093521"></a><a name="p1141020031093521"></a>Failed to install the application due to incorrect parameters. </p>
 </td>
</tr>
<tr id="row328903254093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ab5e45300939da4427f50b6a765701e34"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab5e45300939da4427f50b6a765701e34"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab5e45300939da4427f50b6a765701e34"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_FILE_PATH_INVALID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830511926093521"><a name="p1830511926093521"></a><a name="p1830511926093521"></a>Failed to install the application because the installation file path is invalid. </p>
 </td>
</tr>
<tr id="row503438612093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a6242775e55f8eb650cc92fd8a3388e32"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6242775e55f8eb650cc92fd8a3388e32"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6242775e55f8eb650cc92fd8a3388e32"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_FILE_NOT_EXISTS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025112739093521"><a name="p2025112739093521"></a><a name="p2025112739093521"></a>Failed to install the application because the installation file does not exist. </p>
 </td>
</tr>
<tr id="row956791300093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a3f98ba8a2755dbb204d87abc64744d62"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3f98ba8a2755dbb204d87abc64744d62"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3f98ba8a2755dbb204d87abc64744d62"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_INVALID_FILE_NAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p490416033093521"><a name="p490416033093521"></a><a name="p490416033093521"></a>Failed to install the application because the installation file name is invalid. </p>
 </td>
</tr>
<tr id="row299562518093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a74a6ca143ea4633376530ee2e9ce6eb1"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a74a6ca143ea4633376530ee2e9ce6eb1"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a74a6ca143ea4633376530ee2e9ce6eb1"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_BAD_FILE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990533129093521"><a name="p1990533129093521"></a><a name="p1990533129093521"></a>Failed to install the application due to incorrect file content. </p>
 </td>
</tr>
<tr id="row1242992977093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a02521dcb943509971fe14bfb8468a98d"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a02521dcb943509971fe14bfb8468a98d"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a02521dcb943509971fe14bfb8468a98d"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_CREATE_FILE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010041952093521"><a name="p2010041952093521"></a><a name="p2010041952093521"></a>Failed to install the application due to a file creation error. </p>
 </td>
</tr>
<tr id="row522766567093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a7786ae72ec65692f14a5f2049dc5a2a7"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7786ae72ec65692f14a5f2049dc5a2a7"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7786ae72ec65692f14a5f2049dc5a2a7"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_CREATE_CODE_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1929681575093521"><a name="p1929681575093521"></a><a name="p1929681575093521"></a>Failed to install the application due to a file path creation error. </p>
 </td>
</tr>
<tr id="row982695176093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a2f5e672b7bf5e4149cdae0770ad200dc"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2f5e672b7bf5e4149cdae0770ad200dc"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2f5e672b7bf5e4149cdae0770ad200dc"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_REMOVE_CODE_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1808837174093521"><a name="p1808837174093521"></a><a name="p1808837174093521"></a>Failed to install the application due to a file path deletion error. </p>
 </td>
</tr>
<tr id="row926051444093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a72f16cafaafe6ff6e7069a2ef28507a7"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a72f16cafaafe6ff6e7069a2ef28507a7"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a72f16cafaafe6ff6e7069a2ef28507a7"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_CREATE_PERMISSIONS_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1482901112093521"><a name="p1482901112093521"></a><a name="p1482901112093521"></a>Failed to install the application because an error occurred when creating the permission file directory. </p>
 </td>
</tr>
<tr id="row1729745434093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ab0d26918c1d8d1481601567cf87f2621"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab0d26918c1d8d1481601567cf87f2621"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab0d26918c1d8d1481601567cf87f2621"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_RENAME_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941088940093521"><a name="p1941088940093521"></a><a name="p1941088940093521"></a>Failed to install the application due to a path renaming error. </p>
 </td>
</tr>
<tr id="row960880758093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aaafdb262ffe01eed1722350d270cf09d"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aaafdb262ffe01eed1722350d270cf09d"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aaafdb262ffe01eed1722350d270cf09d"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_RENAME_FILE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1879504623093521"><a name="p1879504623093521"></a><a name="p1879504623093521"></a>Failed to install the application due to a file renaming error. </p>
 </td>
</tr>
<tr id="row1763433530093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1abe5bafc9885f41ff2d7fa348be381d66"><a name="ggac318d4f4dc0125e2367ea8c539770ed1abe5bafc9885f41ff2d7fa348be381d66"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1abe5bafc9885f41ff2d7fa348be381d66"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_REMOVE_DATA_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1236798838093521"><a name="p1236798838093521"></a><a name="p1236798838093521"></a>Failed to install the application due to an error occurred when removing the data path. </p>
 </td>
</tr>
<tr id="row611521365093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a9e457f181dce9e221dfa01c257d7fe12"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9e457f181dce9e221dfa01c257d7fe12"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9e457f181dce9e221dfa01c257d7fe12"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_CREATE_DATA_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2040771235093521"><a name="p2040771235093521"></a><a name="p2040771235093521"></a>Failed to install the application due to an error occurred when creating the data path. </p>
 </td>
</tr>
<tr id="row696053568093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ac62be957615c89ae23b780d8d288419e"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac62be957615c89ae23b780d8d288419e"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac62be957615c89ae23b780d8d288419e"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_RECORD_INFO_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904652752093521"><a name="p904652752093521"></a><a name="p904652752093521"></a>Failed to install the application due to an error occurred when recording installation information. </p>
 </td>
</tr>
<tr id="row1925719458093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a438581dc1abee81ed846d9dafee34e83"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a438581dc1abee81ed846d9dafee34e83"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a438581dc1abee81ed846d9dafee34e83"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_UID_AND_GID_BACKUP_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417432531093521"><a name="p1417432531093521"></a><a name="p1417432531093521"></a>Failed to install the application due to an error occurred when backing up the UID and GID. </p>
 </td>
</tr>
<tr id="row1003072324093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ad8e03ac63b84d45685f3b655717d3c92"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ad8e03ac63b84d45685f3b655717d3c92"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ad8e03ac63b84d45685f3b655717d3c92"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_CHOWN_DATA_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918462896093521"><a name="p1918462896093521"></a><a name="p1918462896093521"></a>Failed to install the application due to an error occurred when changing ownership of the data directory. </p>
 </td>
</tr>
<tr id="row261024112093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a0d874b79e811844325c76f65630db989"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0d874b79e811844325c76f65630db989"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0d874b79e811844325c76f65630db989"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_VERSION_DOWNGRADE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p31174058093521"><a name="p31174058093521"></a><a name="p31174058093521"></a>Failed to install the application because an application of a later version has been installed. </p>
 </td>
</tr>
<tr id="row943927576093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a6ef4ca2fed2c05c5ec553f4e12844bac"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6ef4ca2fed2c05c5ec553f4e12844bac"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6ef4ca2fed2c05c5ec553f4e12844bac"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_BUNDLE_NUMBER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087452718093521"><a name="p2087452718093521"></a><a name="p2087452718093521"></a>Failed to install the application because the number of installed applications exceeds the maximum (30). This error code is available only to basic watches. </p>
 </td>
</tr>
<tr id="row1542429534093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a8599367df053820365395e64ae536e81"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8599367df053820365395e64ae536e81"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8599367df053820365395e64ae536e81"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_STORE_PERMISSIONS_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101896163093521"><a name="p101896163093521"></a><a name="p101896163093521"></a>Failed to install the application due to an error occurred when storing permission information. </p>
 </td>
</tr>
<tr id="row1661509933093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1adb1e3b901e0a5b88460f661a533b08f8"><a name="ggac318d4f4dc0125e2367ea8c539770ed1adb1e3b901e0a5b88460f661a533b08f8"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1adb1e3b901e0a5b88460f661a533b08f8"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_FILE_DATA_INVALID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616944600093521"><a name="p1616944600093521"></a><a name="p1616944600093521"></a>Failed to install the application due to invalid file data. This error code is available only to basic watches. </p>
 </td>
</tr>
<tr id="row1891748385093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a2b9a032c6b9c843e1101cf753b2fa6fa"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2b9a032c6b9c843e1101cf753b2fa6fa"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2b9a032c6b9c843e1101cf753b2fa6fa"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_INCOMPATIBLE_SIGNATURE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1377416591093521"><a name="p1377416591093521"></a><a name="p1377416591093521"></a>Failed to install the application due to unmatched signature used for version update. </p>
 </td>
</tr>
<tr id="row1975525203093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ab1dc9dd09156cc2b06643624d8465ea9"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab1dc9dd09156cc2b06643624d8465ea9"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab1dc9dd09156cc2b06643624d8465ea9"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_INVALID_PROVISIONINFO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1594417392093521"><a name="p1594417392093521"></a><a name="p1594417392093521"></a>Failed to install the application due to unmatched provisioning information during signature verification. </p>
 </td>
</tr>
<tr id="row1378090969093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a06b51bb80923d2d9271f902f75842063"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a06b51bb80923d2d9271f902f75842063"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a06b51bb80923d2d9271f902f75842063"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_OPERATE_SIGNED_FILE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881551754093521"><a name="p1881551754093521"></a><a name="p1881551754093521"></a>Failed to install the application due to an error occurred when processing the signature file. </p>
 </td>
</tr>
<tr id="row1536543905093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a34439d18e6612f31ba634766c3da6457"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a34439d18e6612f31ba634766c3da6457"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a34439d18e6612f31ba634766c3da6457"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_APP_SIGNATURE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1893710130093521"><a name="p1893710130093521"></a><a name="p1893710130093521"></a>Failed to install the application due to an error occurred when parsing the application signature. </p>
 </td>
</tr>
<tr id="row762915430093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a553374f3e17c7a39f6fbf9ecd932b618"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a553374f3e17c7a39f6fbf9ecd932b618"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a553374f3e17c7a39f6fbf9ecd932b618"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_SIGNATURE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376172717093521"><a name="p376172717093521"></a><a name="p376172717093521"></a>Failed to install the application due to an error occurred when parsing the file signature. </p>
 </td>
</tr>
<tr id="row1632946282093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a2c992cbdee385fbc00fecd0e313b33fc"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2c992cbdee385fbc00fecd0e313b33fc"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2c992cbdee385fbc00fecd0e313b33fc"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_INTERNAL_SIGNATURE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737101593093521"><a name="p1737101593093521"></a><a name="p1737101593093521"></a>Failed to install the application due to an internal error during signature verification. </p>
 </td>
</tr>
<tr id="row2042313111093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a17e1305d5eeee7867a98c295c488e236"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a17e1305d5eeee7867a98c295c488e236"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a17e1305d5eeee7867a98c295c488e236"></a></strong>ERR_APPEXECFWK_SET_DEBUG_MODE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249793082093521"><a name="p249793082093521"></a><a name="p249793082093521"></a>Failed to install the application due to an error occurred when setting the signature verification mode. </p>
 </td>
</tr>
<tr id="row105409504093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aef3bf9de62376b9d91070956c1a0b6a0"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aef3bf9de62376b9d91070956c1a0b6a0"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aef3bf9de62376b9d91070956c1a0b6a0"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PROFILE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p521022526093521"><a name="p521022526093521"></a><a name="p521022526093521"></a>Failed to parse the file. </p>
 </td>
</tr>
<tr id="row1783889812093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a014b98d9df51b98ff37f95aaba97c63f"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a014b98d9df51b98ff37f95aaba97c63f"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a014b98d9df51b98ff37f95aaba97c63f"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_BUNDLENAME_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705562286093521"><a name="p1705562286093521"></a><a name="p1705562286093521"></a>Failed to parse the bundle name. </p>
 </td>
</tr>
<tr id="row597804088093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a1ab7654bdb5ca8fcba99e6acb9ad4163"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1ab7654bdb5ca8fcba99e6acb9ad4163"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1ab7654bdb5ca8fcba99e6acb9ad4163"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p25645234093521"><a name="p25645234093521"></a><a name="p25645234093521"></a>Invalid bundle name. </p>
 </td>
</tr>
<tr id="row1060148372093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a7f159724dde9d3ec69a22fd97c7c4275"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7f159724dde9d3ec69a22fd97c7c4275"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7f159724dde9d3ec69a22fd97c7c4275"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VENDOR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p742403208093521"><a name="p742403208093521"></a><a name="p742403208093521"></a>Failed to parse the vendor information. </p>
 </td>
</tr>
<tr id="row539985688093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ad569e1e0e50704d8d94394b39df13599"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ad569e1e0e50704d8d94394b39df13599"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ad569e1e0e50704d8d94394b39df13599"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONCODE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800246655093521"><a name="p800246655093521"></a><a name="p800246655093521"></a>Failed to parse the version code. </p>
 </td>
</tr>
<tr id="row1638502394093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a26e4922b83c0a42f8576cb81cd0760e2"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a26e4922b83c0a42f8576cb81cd0760e2"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a26e4922b83c0a42f8576cb81cd0760e2"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_VERSIONNAME_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p539116618093521"><a name="p539116618093521"></a><a name="p539116618093521"></a>Failed to parse the version name. </p>
 </td>
</tr>
<tr id="row1773654246093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a022e0b7e7b978eda5e43db46efe9c916"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a022e0b7e7b978eda5e43db46efe9c916"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a022e0b7e7b978eda5e43db46efe9c916"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_PERMISSIONS_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p384601954093521"><a name="p384601954093521"></a><a name="p384601954093521"></a>Failed to parse the installation permission information. </p>
 </td>
</tr>
<tr id="row341217297093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ac449d6df4540c1794f1b76599435c4df"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac449d6df4540c1794f1b76599435c4df"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac449d6df4540c1794f1b76599435c4df"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_API_VERSION_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723385448093521"><a name="p723385448093521"></a><a name="p723385448093521"></a>Failed to parse the API version. </p>
 </td>
</tr>
<tr id="row1774632649093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a05262a83fbc2d5817772db9a20d6c503"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a05262a83fbc2d5817772db9a20d6c503"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a05262a83fbc2d5817772db9a20d6c503"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICE_CONFIG_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917891309093521"><a name="p917891309093521"></a><a name="p917891309093521"></a>Failed to parse the device configuration. </p>
 </td>
</tr>
<tr id="row487703049093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1abcb1a3e0509445e2bff7dad43c379971"><a name="ggac318d4f4dc0125e2367ea8c539770ed1abcb1a3e0509445e2bff7dad43c379971"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1abcb1a3e0509445e2bff7dad43c379971"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_KEEPALIVE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p796780619093521"><a name="p796780619093521"></a><a name="p796780619093521"></a>Failed to parse the <strong id="b976046886093521"><a name="b976046886093521"></a><a name="b976046886093521"></a>isKeepAlive</strong> field of the application. </p>
 </td>
</tr>
<tr id="row1500779727093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a27d9af1e04f75bc389f35b3318ad1590"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a27d9af1e04f75bc389f35b3318ad1590"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a27d9af1e04f75bc389f35b3318ad1590"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULENAME_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120111366093521"><a name="p120111366093521"></a><a name="p120111366093521"></a>Failed to parse the <strong id="b1750158461093521"><a name="b1750158461093521"></a><a name="b1750158461093521"></a>name</strong> field of the application's HAP package. The HAP information is encapsulated in a <a href="moduleinfo.md">ModuleInfo</a> object. </p>
 </td>
</tr>
<tr id="row1062068617093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a38afd7346c84b9d618aa1a477316c3ca"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a38afd7346c84b9d618aa1a477316c3ca"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a38afd7346c84b9d618aa1a477316c3ca"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_MODULENAME </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1651701370093521"><a name="p1651701370093521"></a><a name="p1651701370093521"></a>Invalid HAP name. </p>
 </td>
</tr>
<tr id="row1817786258093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1af244274d1cf39090d9818aac15882e4c"><a name="ggac318d4f4dc0125e2367ea8c539770ed1af244274d1cf39090d9818aac15882e4c"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1af244274d1cf39090d9818aac15882e4c"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_MODULE_DESCRIPTION_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330092271093521"><a name="p1330092271093521"></a><a name="p1330092271093521"></a>Failed to parse the HAP description information. </p>
 </td>
</tr>
<tr id="row1927174386093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ac36ac4af8d61e10431c39fe545f8f623"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac36ac4af8d61e10431c39fe545f8f623"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac36ac4af8d61e10431c39fe545f8f623"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DEVICETYPE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1690738224093521"><a name="p1690738224093521"></a><a name="p1690738224093521"></a>Failed to parse the <strong id="b1027154364093521"><a name="b1027154364093521"></a><a name="b1027154364093521"></a>deviceType</strong> field of the application's HAP package. </p>
 </td>
</tr>
<tr id="row585959628093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a04f7cee0fe708631364d56e53fc7a2d8"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a04f7cee0fe708631364d56e53fc7a2d8"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a04f7cee0fe708631364d56e53fc7a2d8"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069770364093521"><a name="p2069770364093521"></a><a name="p2069770364093521"></a>Failed to parse the HAP information. </p>
 </td>
</tr>
<tr id="row717739429093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aba3187880d4a57348ac2cd3943546dd1"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aba3187880d4a57348ac2cd3943546dd1"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aba3187880d4a57348ac2cd3943546dd1"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULENAME_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p210572711093521"><a name="p210572711093521"></a><a name="p210572711093521"></a>Failed to parse the <strong id="b1062302093521"><a name="b1062302093521"></a><a name="b1062302093521"></a>moduleName</strong> field of the application's HAP package. </p>
 </td>
</tr>
<tr id="row504102502093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a1c88e191b397644827022b0a238007da"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1c88e191b397644827022b0a238007da"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1c88e191b397644827022b0a238007da"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_MODULETYPE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289127541093521"><a name="p289127541093521"></a><a name="p289127541093521"></a>Invalid HAP type. </p>
 </td>
</tr>
<tr id="row1178580372093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a9ec099feb69dc64a4f3bd48475723bba"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9ec099feb69dc64a4f3bd48475723bba"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9ec099feb69dc64a4f3bd48475723bba"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DISTRO_DELIVERY_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1682997438093521"><a name="p1682997438093521"></a><a name="p1682997438093521"></a>Failed to parse the <strong id="b1040781591093521"><a name="b1040781591093521"></a><a name="b1040781591093521"></a>isDeliveryInstall</strong> field of the application's HAP package. </p>
 </td>
</tr>
<tr id="row1564177336093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a98508d3e35c99d09320ffd498469b984"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a98508d3e35c99d09320ffd498469b984"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a98508d3e35c99d09320ffd498469b984"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_METADATA_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p607411629093521"><a name="p607411629093521"></a><a name="p607411629093521"></a>Failed to parse the <a href="metadata.md">MetaData</a> information. </p>
 </td>
</tr>
<tr id="row1887433158093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a1649053e390e2b20ac96674aa7d7ca88"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1649053e390e2b20ac96674aa7d7ca88"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1649053e390e2b20ac96674aa7d7ca88"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITIES_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533102746093521"><a name="p1533102746093521"></a><a name="p1533102746093521"></a>Failed to parse the <a href="abilityinfo.md">AbilityInfo</a>. </p>
 </td>
</tr>
<tr id="row1718699579093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1adbf64bab15b50b69286efa90f7f1dec1"><a name="ggac318d4f4dc0125e2367ea8c539770ed1adbf64bab15b50b69286efa90f7f1dec1"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1adbf64bab15b50b69286efa90f7f1dec1"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_NAME_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p759603252093521"><a name="p759603252093521"></a><a name="p759603252093521"></a>Failed to parse the class name of the ability. </p>
 </td>
</tr>
<tr id="row1368888684093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aeefcd3f1a247768fc5fb2f59c0f1b966"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aeefcd3f1a247768fc5fb2f59c0f1b966"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aeefcd3f1a247768fc5fb2f59c0f1b966"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_TYPE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650829632093521"><a name="p1650829632093521"></a><a name="p1650829632093521"></a>Failed to parse the template used by the ability. </p>
 </td>
</tr>
<tr id="row507482523093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a8a282ca74395e3007dd75c90d671fe23"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8a282ca74395e3007dd75c90d671fe23"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8a282ca74395e3007dd75c90d671fe23"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_ICONPATH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15356469093521"><a name="p15356469093521"></a><a name="p15356469093521"></a>Failed to parse the icon path of the ability. </p>
 </td>
</tr>
<tr id="row1340691524093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a3c6dcb2ca14788595975cea51bf1cfed"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3c6dcb2ca14788595975cea51bf1cfed"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3c6dcb2ca14788595975cea51bf1cfed"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LABEL_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35642318093521"><a name="p35642318093521"></a><a name="p35642318093521"></a>Failed to parse the label of the ability. </p>
 </td>
</tr>
<tr id="row1656431608093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a164231485c5ea694f9a0b4d8307d5901"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a164231485c5ea694f9a0b4d8307d5901"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a164231485c5ea694f9a0b4d8307d5901"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_DESCRIPTION_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1336622161093521"><a name="p1336622161093521"></a><a name="p1336622161093521"></a>Failed to parse the description of the ability. </p>
 </td>
</tr>
<tr id="row422166329093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a6a592b570f8c29dc1c4161faedcf2acd"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6a592b570f8c29dc1c4161faedcf2acd"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6a592b570f8c29dc1c4161faedcf2acd"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_LAUNCHTYPE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311374046093521"><a name="p311374046093521"></a><a name="p311374046093521"></a>Failed to parse the startup mode of the ability. </p>
 </td>
</tr>
<tr id="row1316786154093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a7d51c40e62b04e8bc2991db294fd10f3"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7d51c40e62b04e8bc2991db294fd10f3"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7d51c40e62b04e8bc2991db294fd10f3"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ABILITY_VISIBLE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2054312017093521"><a name="p2054312017093521"></a><a name="p2054312017093521"></a>Failed to parse the <strong id="b276593823093521"><a name="b276593823093521"></a><a name="b276593823093521"></a>isVisible</strong> field of the ability. </p>
 </td>
</tr>
<tr id="row1161191498093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aa83132144c11442291f4a971e51dcbb1"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aa83132144c11442291f4a971e51dcbb1"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aa83132144c11442291f4a971e51dcbb1"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_INVALID_BUNDLENAME_LENGTH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672222933093521"><a name="p672222933093521"></a><a name="p672222933093521"></a>Invalid length of the bundle name. </p>
 </td>
</tr>
<tr id="row2029958940093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a1e7f0159d459e0f416c05bcd106d8782"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1e7f0159d459e0f416c05bcd106d8782"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1e7f0159d459e0f416c05bcd106d8782"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_LABEL_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531816140093521"><a name="p531816140093521"></a><a name="p531816140093521"></a>The parsed application label exceeds the maximum length (255 bytes). </p>
 </td>
</tr>
<tr id="row986174956093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1af6fb04f5b2b34761822d84670f19e7ce"><a name="ggac318d4f4dc0125e2367ea8c539770ed1af6fb04f5b2b34761822d84670f19e7ce"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1af6fb04f5b2b34761822d84670f19e7ce"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VERSIONNAME_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p4612224093521"><a name="p4612224093521"></a><a name="p4612224093521"></a>The parsed application version name exceeds the maximum length (127 bytes). </p>
 </td>
</tr>
<tr id="row951218862093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a4d20732be30f3bc677ed0fff3b79aa93"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4d20732be30f3bc677ed0fff3b79aa93"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4d20732be30f3bc677ed0fff3b79aa93"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_NAME_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467077811093521"><a name="p467077811093521"></a><a name="p467077811093521"></a>The parsed application metadata name exceeds the maximum length (255 bytes). </p>
 </td>
</tr>
<tr id="row754667942093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a4ddea99589bb62ae0297742763a12c1a"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4ddea99589bb62ae0297742763a12c1a"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4ddea99589bb62ae0297742763a12c1a"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_METADATA_VALUE_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427156186093521"><a name="p1427156186093521"></a><a name="p1427156186093521"></a>The parsed application metadata value exceeds the maximum length (255 bytes). </p>
 </td>
</tr>
<tr id="row709089290093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aabd55ad27e4671083b36aa1a9bce53b2"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aabd55ad27e4671083b36aa1a9bce53b2"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aabd55ad27e4671083b36aa1a9bce53b2"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_VENDOR_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p391163194093521"><a name="p391163194093521"></a><a name="p391163194093521"></a>The parsed application vendor name exceeds the maximum length (255 bytes). </p>
 </td>
</tr>
<tr id="row935497354093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a85ed32b668e813a868dff8f11d1a0259"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a85ed32b668e813a868dff8f11d1a0259"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a85ed32b668e813a868dff8f11d1a0259"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_MODULENAME_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p156340629093521"><a name="p156340629093521"></a><a name="p156340629093521"></a>The parsed HAP name exceeds the maximum length (31 bytes). </p>
 </td>
</tr>
<tr id="row779813635093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a2fd9e57b401b4c4ecb7f737d9cfb7f1a"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2fd9e57b401b4c4ecb7f737d9cfb7f1a"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2fd9e57b401b4c4ecb7f737d9cfb7f1a"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITYNAME_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427473637093521"><a name="p427473637093521"></a><a name="p427473637093521"></a>The parsed ability class name exceeds the maximum length (127 bytes). </p>
 </td>
</tr>
<tr id="row827254673093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1acb65a2d440e7aee4541ea265317582e0"><a name="ggac318d4f4dc0125e2367ea8c539770ed1acb65a2d440e7aee4541ea265317582e0"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1acb65a2d440e7aee4541ea265317582e0"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_DESCRIPTION_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883158082093521"><a name="p1883158082093521"></a><a name="p1883158082093521"></a>The parsed ability description exceeds the maximum length (255 bytes). </p>
 </td>
</tr>
<tr id="row1183101334093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a7d764e29e35ead6dbbca9302c284ee00"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7d764e29e35ead6dbbca9302c284ee00"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a7d764e29e35ead6dbbca9302c284ee00"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXCEED_MAX_ABILITY_LABEL_LENGTH_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122707092093521"><a name="p122707092093521"></a><a name="p122707092093521"></a>The parsed ability label exceeds the maximum length (255 bytes). </p>
 </td>
</tr>
<tr id="row227508683093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aebc061682db1151f24248f0ca34eca98"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aebc061682db1151f24248f0ca34eca98"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aebc061682db1151f24248f0ca34eca98"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXTRACTOR_NOT_INIT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p903241373093521"><a name="p903241373093521"></a><a name="p903241373093521"></a>Failed to initialize the extractor. </p>
 </td>
</tr>
<tr id="row113237027093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a797b7558d35fdb43a923aaac8c464187"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a797b7558d35fdb43a923aaac8c464187"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a797b7558d35fdb43a923aaac8c464187"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_EXTRACT_HAP_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1348382719093521"><a name="p1348382719093521"></a><a name="p1348382719093521"></a>Failed to extract hap. </p>
 </td>
</tr>
<tr id="row34929068093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aeacdda0db2432c52b0795208bf69408e"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aeacdda0db2432c52b0795208bf69408e"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aeacdda0db2432c52b0795208bf69408e"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_JS_DIR_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1222030494093521"><a name="p1222030494093521"></a><a name="p1222030494093521"></a>Failed to parse the JavaScript path. This error code is available only to basic watches. </p>
 </td>
</tr>
<tr id="row803287004093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a3a521918e6b836de9b70325a0a643362"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3a521918e6b836de9b70325a0a643362"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3a521918e6b836de9b70325a0a643362"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_RESOURCE_INDEX_NOT_EXISTS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1569579947093521"><a name="p1569579947093521"></a><a name="p1569579947093521"></a>The resource index does not exist. </p>
 </td>
</tr>
<tr id="row797715969093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1acc1f483da695764aa8f3f22d697c8969"><a name="ggac318d4f4dc0125e2367ea8c539770ed1acc1f483da695764aa8f3f22d697c8969"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1acc1f483da695764aa8f3f22d697c8969"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_LABEL_RES_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1708132028093521"><a name="p1708132028093521"></a><a name="p1708132028093521"></a>Failed to parse the label resource. </p>
 </td>
</tr>
<tr id="row1680361701093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a572a4b52c204c83b1742eb1fc8364a1a"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a572a4b52c204c83b1742eb1fc8364a1a"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a572a4b52c204c83b1742eb1fc8364a1a"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_ICON_RES_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667399953093521"><a name="p667399953093521"></a><a name="p667399953093521"></a>Failed to parse the icon resource. </p>
 </td>
</tr>
<tr id="row1081131257093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a128bf2cca7073ed0a6299c7d8529e33d"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a128bf2cca7073ed0a6299c7d8529e33d"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a128bf2cca7073ed0a6299c7d8529e33d"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_PARSE_DESCRIPTION_RES_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751558777093521"><a name="p751558777093521"></a><a name="p751558777093521"></a>Failed to parse the description resource. </p>
 </td>
</tr>
<tr id="row914634576093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ac31bcc78028487c5be87399325332380"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac31bcc78028487c5be87399325332380"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ac31bcc78028487c5be87399325332380"></a></strong>ERR_APPEXECFWK_INSTALL_FAILED_SEND_REQUEST_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1132426731093521"><a name="p1132426731093521"></a><a name="p1132426731093521"></a>Failed to install the application due to a request sending error. </p>
 </td>
</tr>
<tr id="row345298797093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a26ff3a2760ff20c60aba2ab125ecdd17"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a26ff3a2760ff20c60aba2ab125ecdd17"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a26ff3a2760ff20c60aba2ab125ecdd17"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_INTERNAL_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1539152122093521"><a name="p1539152122093521"></a><a name="p1539152122093521"></a>Failed to uninstall the application due to an internal error. </p>
 </td>
</tr>
<tr id="row232181075093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ae0670ff00ddfc9f4642815d13e50e732"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ae0670ff00ddfc9f4642815d13e50e732"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ae0670ff00ddfc9f4642815d13e50e732"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_PARAM_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514175282093521"><a name="p514175282093521"></a><a name="p514175282093521"></a>Failed to uninstall the application due to incorrect input parameters. </p>
 </td>
</tr>
<tr id="row1499126027093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a8d6b6bf5861d928ca86ddaeeb15c062a"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8d6b6bf5861d928ca86ddaeeb15c062a"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8d6b6bf5861d928ca86ddaeeb15c062a"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_EXISTS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1253241288093521"><a name="p1253241288093521"></a><a name="p1253241288093521"></a>Failed to uninstall the application because it does not exist. </p>
 </td>
</tr>
<tr id="row1754700633093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a4949cab6b3e4f97fd44151eba0d488bb"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4949cab6b3e4f97fd44151eba0d488bb"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4949cab6b3e4f97fd44151eba0d488bb"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_DIRS_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404028929093521"><a name="p404028929093521"></a><a name="p404028929093521"></a>Failed to uninstall the application due to an error occurred when deleting the path. </p>
 </td>
</tr>
<tr id="row234009439093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a9e5f0727ceed161044cf4bfdacec12e2"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9e5f0727ceed161044cf4bfdacec12e2"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9e5f0727ceed161044cf4bfdacec12e2"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_RECORD_INFO_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1858285793093521"><a name="p1858285793093521"></a><a name="p1858285793093521"></a>Failed to uninstall the application due to an error occurred when deleting the installation record. </p>
 </td>
</tr>
<tr id="row857915361093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a0050a0cd61152432d89221b3ed178724"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0050a0cd61152432d89221b3ed178724"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0050a0cd61152432d89221b3ed178724"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_PERMISSIONS_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1528140273093521"><a name="p1528140273093521"></a><a name="p1528140273093521"></a>Failed to uninstall the application due to an error occurred when deleting the permission information. </p>
 </td>
</tr>
<tr id="row341948095093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a58c70df1bf55bc3c2b61e2c0f0571a2f"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a58c70df1bf55bc3c2b61e2c0f0571a2f"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a58c70df1bf55bc3c2b61e2c0f0571a2f"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_BUNDLE_NOT_UNINSTALLABLE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1334255238093521"><a name="p1334255238093521"></a><a name="p1334255238093521"></a>Failed to uninstall the application because the application cannot be uninstalled. </p>
 </td>
</tr>
<tr id="row1364749397093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a11b7780ad61c6085f475c5415de34191"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a11b7780ad61c6085f475c5415de34191"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a11b7780ad61c6085f475c5415de34191"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_DELETE_UID_INFO_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p687770285093521"><a name="p687770285093521"></a><a name="p687770285093521"></a>Failed to uninstall the application due to an error occurred when deleting the UID information. </p>
 </td>
</tr>
<tr id="row1859742058093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a1e2b896e9cc48287bed17cd2835f44cb"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1e2b896e9cc48287bed17cd2835f44cb"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a1e2b896e9cc48287bed17cd2835f44cb"></a></strong>ERR_APPEXECFWK_UNINSTALL_FAILED_SEND_REQUEST_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1998606006093521"><a name="p1998606006093521"></a><a name="p1998606006093521"></a>Failed to uninstall the application due to a request sending error. </p>
 </td>
</tr>
<tr id="row2100025237093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a3fbc51865d3bf19ead1c7e42c6058a42"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3fbc51865d3bf19ead1c7e42c6058a42"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3fbc51865d3bf19ead1c7e42c6058a42"></a></strong>ERR_APPEXECFWK_DUMP_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1115666819093521"><a name="p1115666819093521"></a><a name="p1115666819093521"></a>Incorrect dump information. </p>
 </td>
</tr>
<tr id="row1587004753093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a35c07d2afc0f8b17822a9f64b19a8993"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a35c07d2afc0f8b17822a9f64b19a8993"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a35c07d2afc0f8b17822a9f64b19a8993"></a></strong>ERR_APPEXECFWK_COMMAND_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351856071093521"><a name="p351856071093521"></a><a name="p351856071093521"></a>Incorrect command. </p>
 </td>
</tr>
<tr id="row512661145093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a4d22c64508c3f6c3a9c3e8972e54696c"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4d22c64508c3f6c3a9c3e8972e54696c"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a4d22c64508c3f6c3a9c3e8972e54696c"></a></strong>ERR_APPEXECFWK_CALLBACK_REGISTER_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1205179100093521"><a name="p1205179100093521"></a><a name="p1205179100093521"></a>Failed to register the callback. </p>
 </td>
</tr>
<tr id="row1268094331093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ae0dd6d1b6cc227e1a67c910182dee9f9"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ae0dd6d1b6cc227e1a67c910182dee9f9"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ae0dd6d1b6cc227e1a67c910182dee9f9"></a></strong>ERR_APPEXECFWK_CALLBACK_UNREGISTER_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p905322704093521"><a name="p905322704093521"></a><a name="p905322704093521"></a>Failed to unregister the callback. </p>
 </td>
</tr>
<tr id="row2025981853093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a3fc6a7d606bdfc9a569c732f7fc0dc85"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3fc6a7d606bdfc9a569c732f7fc0dc85"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a3fc6a7d606bdfc9a569c732f7fc0dc85"></a></strong>ERR_APPEXECFWK_CALLBACK_GENERATE_LOCAL_SERVICEID_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p826720172093521"><a name="p826720172093521"></a><a name="p826720172093521"></a>Failed to generate a service ID for the current process. </p>
 </td>
</tr>
<tr id="row1210916089093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a030663d47f1763759349ab34509a2c1c"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a030663d47f1763759349ab34509a2c1c"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a030663d47f1763759349ab34509a2c1c"></a></strong>ERR_APPEXECFWK_CALLBACK_SERVICEID_TRANSMITTED_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1702201862093521"><a name="p1702201862093521"></a><a name="p1702201862093521"></a>Failed to transmit the service ID of the current process. </p>
 </td>
</tr>
<tr id="row309171381093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1aeb276d0adcc605cee18e3e06f641626e"><a name="ggac318d4f4dc0125e2367ea8c539770ed1aeb276d0adcc605cee18e3e06f641626e"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1aeb276d0adcc605cee18e3e06f641626e"></a></strong>ERR_APPEXECFWK_CALLBACK_NEVER_REGISTERED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1396736700093521"><a name="p1396736700093521"></a><a name="p1396736700093521"></a>The callback is never registered. </p>
 </td>
</tr>
<tr id="row2042864916093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ab853bfd0b4558a663bd683ab6a365c8b"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab853bfd0b4558a663bd683ab6a365c8b"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ab853bfd0b4558a663bd683ab6a365c8b"></a></strong>ERR_APPEXECFWK_CALLBACK_OBTAIN_ALL_BUNDLE_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p609032428093521"><a name="p609032428093521"></a><a name="p609032428093521"></a>Failed to obtain the bundle names of all applications in the system. </p>
 </td>
</tr>
<tr id="row1562939191093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a8e8a7a1f2d610d5f078dc79959776930"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8e8a7a1f2d610d5f078dc79959776930"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8e8a7a1f2d610d5f078dc79959776930"></a></strong>ERR_APPEXECFWK_CALLBACK_NULL_CORRESPONDING_CALLBACK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1215738106093521"><a name="p1215738106093521"></a><a name="p1215738106093521"></a>The required callback is unavailable. </p>
 </td>
</tr>
<tr id="row1008283653093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1acb14a1daa5fe17eb25798bbcd98bcd57"><a name="ggac318d4f4dc0125e2367ea8c539770ed1acb14a1daa5fe17eb25798bbcd98bcd57"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1acb14a1daa5fe17eb25798bbcd98bcd57"></a></strong>ERR_APPEXECFWK_CALLBACK_GET_INSTALLTYPE_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p616542756093521"><a name="p616542756093521"></a><a name="p616542756093521"></a>Failed to obtain the installation type (installation or uninstallation). </p>
 </td>
</tr>
<tr id="row1665182138093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a8898f52b989730709638b26bcb555f54"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8898f52b989730709638b26bcb555f54"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a8898f52b989730709638b26bcb555f54"></a></strong>ERR_APPEXECFWK_CALLBACK_GET_ERROR_INSTALLTYPE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194056334093521"><a name="p194056334093521"></a><a name="p194056334093521"></a>Incorrect installation type. </p>
 </td>
</tr>
<tr id="row340834892093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1ae31533f402b130eb4cc8fed07706c5b6"><a name="ggac318d4f4dc0125e2367ea8c539770ed1ae31533f402b130eb4cc8fed07706c5b6"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1ae31533f402b130eb4cc8fed07706c5b6"></a></strong>ERR_APPEXECFWK_SERIALIZATION_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751247097093521"><a name="p1751247097093521"></a><a name="p1751247097093521"></a>Serialization failed. </p>
 </td>
</tr>
<tr id="row1327889587093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a66b8941c7c418eedc7df7f758cbacc42"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a66b8941c7c418eedc7df7f758cbacc42"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a66b8941c7c418eedc7df7f758cbacc42"></a></strong>ERR_APPEXECFWK_DESERIALIZATION_FAILED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1649188941093521"><a name="p1649188941093521"></a><a name="p1649188941093521"></a>Deserialization failed. </p>
 </td>
</tr>
<tr id="row2019716826093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a19aa79fde7b3e4da78567e4fcbe306a7"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a19aa79fde7b3e4da78567e4fcbe306a7"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a19aa79fde7b3e4da78567e4fcbe306a7"></a></strong>ERR_APPEXECFWK_SYSTEM_INTERNAL_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1295498574093521"><a name="p1295498574093521"></a><a name="p1295498574093521"></a>Internal system error. </p>
 </td>
</tr>
<tr id="row687807327093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a0ad2ce2d577f995c2ba3ea946ce366e6"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0ad2ce2d577f995c2ba3ea946ce366e6"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a0ad2ce2d577f995c2ba3ea946ce366e6"></a></strong>ERR_APPEXECFWK_NO_BUNDLENAME_FOR_UID </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369555126093521"><a name="p369555126093521"></a><a name="p369555126093521"></a>No bundle name associated with the UID is found. </p>
 </td>
</tr>
<tr id="row860189365093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a9161dd6c967af438a56b01cd916e01c2"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9161dd6c967af438a56b01cd916e01c2"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a9161dd6c967af438a56b01cd916e01c2"></a></strong>ERR_APPEXECFWK_IPCIO_UNAVAILABLED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216770423093521"><a name="p216770423093521"></a><a name="p216770423093521"></a>The <strong id="b225432056093521"><a name="b225432056093521"></a><a name="b225432056093521"></a>IpcIo</strong> structure is unavailable. </p>
 </td>
</tr>
<tr id="row2105803388093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a6cff9490f5817281ac9c2bcdafcf477f"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6cff9490f5817281ac9c2bcdafcf477f"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a6cff9490f5817281ac9c2bcdafcf477f"></a></strong>ERR_APPEXECFWK_INVOKE_ERROR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733021506093521"><a name="p733021506093521"></a><a name="p733021506093521"></a>An error occurred when calling the <strong id="b1020038671093521"><a name="b1020038671093521"></a><a name="b1020038671093521"></a>invoke</strong> function of the Bundle Manager <a href="service.md">Service</a>. </p>
 </td>
</tr>
<tr id="row781447961093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac318d4f4dc0125e2367ea8c539770ed1a2c357a03505c34ef9a843876af91739e"><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2c357a03505c34ef9a843876af91739e"></a><a name="ggac318d4f4dc0125e2367ea8c539770ed1a2c357a03505c34ef9a843876af91739e"></a></strong>ERR_APPEXECFWK_PERMISSION_DENIED </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901937823093521"><a name="p1901937823093521"></a><a name="p1901937823093521"></a>The server that invokes the Bundle Manager <a href="service.md">Service</a> does not have required permission. </p>
 </td>
</tr>
</tbody>
</table>

## LaunchMode<a name="ga605d46d860e356a74db6842e66522854"></a>

```
enum [LaunchMode](bundlemanager.md#ga605d46d860e356a74db6842e66522854)
```

 **Description:**

Enumerates startup modes of an ability. 

<a name="table1696462237093521"></a>
<table><thead align="left"><tr id="row1498491874093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p882332387093521"><a name="p882332387093521"></a><a name="p882332387093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p350408673093521"><a name="p350408673093521"></a><a name="p350408673093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1002401075093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga605d46d860e356a74db6842e66522854a57da18394d2f90538c40b0b8d4a3a3c7"><a name="gga605d46d860e356a74db6842e66522854a57da18394d2f90538c40b0b8d4a3a3c7"></a><a name="gga605d46d860e356a74db6842e66522854a57da18394d2f90538c40b0b8d4a3a3c7"></a></strong>SINGLETON </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775440350093521"><a name="p775440350093521"></a><a name="p775440350093521"></a>Singleton mode, allowing only one instance </p>
 </td>
</tr>
<tr id="row2117065033093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga605d46d860e356a74db6842e66522854a9de934790934fe831fe946c851e8338e"><a name="gga605d46d860e356a74db6842e66522854a9de934790934fe831fe946c851e8338e"></a><a name="gga605d46d860e356a74db6842e66522854a9de934790934fe831fe946c851e8338e"></a></strong>STANDARD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628689557093521"><a name="p1628689557093521"></a><a name="p1628689557093521"></a>Standard mode, allowing multiple instances </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section577388262093521"></a>

## ClearAbilityInfo\(\)<a name="ga7377545918725f75645b59b1b7a319fa"></a>

```
void ClearAbilityInfo ([AbilityInfo](abilityinfo.md) * abilityInfo)
```

 **Description:**

Clears an  [AbilityInfo](abilityinfo.md)  object. 

This function clears and releases the memory occupied by the fields of the pointer type included in the specified  [AbilityInfo](abilityinfo.md)  object. 

**Parameters:**

<a name="table1588577250093521"></a>
<table><thead align="left"><tr id="row1807315770093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2141302947093521"><a name="p2141302947093521"></a><a name="p2141302947093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1278144769093521"><a name="p1278144769093521"></a><a name="p1278144769093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row448576586093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">abilityInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="abilityinfo.md">AbilityInfo</a> object to clear.</td>
</tr>
</tbody>
</table>

## ClearBundleInfo\(\)<a name="ga78829b21273aefd65844eba4549162ca"></a>

```
void ClearBundleInfo ([BundleInfo](bundleinfo.md) * bundleInfo)
```

 **Description:**

Clears a  [BundleInfo](bundleinfo.md)  object. 

This function clears and releases the memory occupied by the fields of the pointer type included in the specified  [BundleInfo](bundleinfo.md)  object. 

**Parameters:**

<a name="table371830412093521"></a>
<table><thead align="left"><tr id="row1249252398093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1425632885093521"><a name="p1425632885093521"></a><a name="p1425632885093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1155237175093521"><a name="p1155237175093521"></a><a name="p1155237175093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1288116560093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="bundleinfo.md">BundleInfo</a> object to clear.</td>
</tr>
</tbody>
</table>

## ClearElement\(\)<a name="ga3abe15ac14571de84ca72c98f4009724"></a>

```
void ClearElement ([ElementName](elementname.md) * element)
```

 **Description:**

Clears the internal data of a specified  **[ElementName](elementname.md)**. 

After  [AbilityInfo](abilityinfo.md)  is queried, clear the internal data of an  **[ElementName](elementname.md)**  if it is no longer required. 

**Parameters:**

<a name="table2020327885093521"></a>
<table><thead align="left"><tr id="row13496989093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p669799926093521"><a name="p669799926093521"></a><a name="p669799926093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p685684708093521"><a name="p685684708093521"></a><a name="p685684708093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row819524350093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b948273131093521"><a name="b948273131093521"></a><a name="b948273131093521"></a><a href="elementname.md">ElementName</a></strong> to clear. </td>
</tr>
</tbody>
</table>

## ClearModuleInfo\(\)<a name="ga6c2242cc10f135d129b95444faacb345"></a>

```
void ClearModuleInfo ([ModuleInfo](moduleinfo.md) * moduleInfo)
```

 **Description:**

Clears a  [ModuleInfo](moduleinfo.md)  object. 

This function clears and releases the memory occupied by the fields of the pointer type included in the specified  [ModuleInfo](moduleinfo.md)  object. 

**Parameters:**

<a name="table244186537093521"></a>
<table><thead align="left"><tr id="row1059407364093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p983109235093521"><a name="p983109235093521"></a><a name="p983109235093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1139124292093521"><a name="p1139124292093521"></a><a name="p1139124292093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row670212141093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">moduleInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="moduleinfo.md">ModuleInfo</a> object to clear.</td>
</tr>
</tbody>
</table>

## GetBundleInfo\(\)<a name="ga5e81134e037911654e34cc8a7ba01a2f"></a>

```
uint8_t GetBundleInfo (const char * bundleName, int32_t flags, [BundleInfo](bundleinfo.md) * bundleInfo )
```

 **Description:**

Obtains the  [BundleInfo](bundleinfo.md)  of an application based on the specified bundle name. 

**Parameters:**

<a name="table203624645093521"></a>
<table><thead align="left"><tr id="row1677855892093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p775331552093521"><a name="p775331552093521"></a><a name="p775331552093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p196593553093521"><a name="p196593553093521"></a><a name="p196593553093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1939625031093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the application bundle to query. </td>
</tr>
<tr id="row1999543172093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether the obtained <a href="bundleinfo.md">BundleInfo</a> object can contain <a href="abilityinfo.md">AbilityInfo</a>. The value <strong id="b939880518093521"><a name="b939880518093521"></a><a name="b939880518093521"></a>1</strong> indicates that it can contain <a href="abilityinfo.md">AbilityInfo</a>, and <strong id="b1424779880093521"><a name="b1424779880093521"></a><a name="b1424779880093521"></a>0</strong> indicates that it cannot. </td>
</tr>
<tr id="row1735973783093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained <a href="bundleinfo.md">BundleInfo</a> object.</td>
</tr>
</tbody>
</table>

**Attention:**

Before querying a  [BundleInfo](bundleinfo.md)  object, you should first call  **memset**  on the constructed  [BundleInfo](bundleinfo.md)  object so that each field in it can be properly initialized for carrying the obtained information. 

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## GetBundleInfos\(\)<a name="ga2469dafbc61ba8e98b69041c13044cad"></a>

```
uint8_t GetBundleInfos (const int flags, [BundleInfo](bundleinfo.md) ** bundleInfos, int32_t * len )
```

 **Description:**

Obtains the  [BundleInfo](bundleinfo.md)  of all bundles in the system. 

**Parameters:**

<a name="table842636700093521"></a>
<table><thead align="left"><tr id="row240826745093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p362296363093521"><a name="p362296363093521"></a><a name="p362296363093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p149499964093521"><a name="p149499964093521"></a><a name="p149499964093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1356204490093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether each of the obtained <a href="bundleinfo.md">BundleInfo</a> objects can contain <a href="abilityinfo.md">AbilityInfo</a>. The value <strong id="b918621714093521"><a name="b918621714093521"></a><a name="b918621714093521"></a>1</strong> indicates that it can contain <a href="abilityinfo.md">AbilityInfo</a>, and <strong id="b538407491093521"><a name="b538407491093521"></a><a name="b538407491093521"></a>0</strong> indicates that it cannot. </td>
</tr>
<tr id="row213984482093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleInfos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the obtained <a href="bundleinfo.md">BundleInfo</a> objects. </td>
</tr>
<tr id="row368587871093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the number of <a href="bundleinfo.md">BundleInfo</a> objects obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## GetBundleInfosByMetaData\(\)<a name="ga711965038390aef4fa0a6b6a98f6998b"></a>

```
uint8_t GetBundleInfosByMetaData (const char * metaDataKey, [BundleInfo](bundleinfo.md) ** bundleInfos, int32_t * len )
```

 **Description:**

Obtains the  [BundleInfo](bundleinfo.md)  of application bundles based on the specified  [MetaData](metadata.md). 

**Parameters:**

<a name="table582679273093521"></a>
<table><thead align="left"><tr id="row591299082093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p725593963093521"><a name="p725593963093521"></a><a name="p725593963093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p558861968093521"><a name="p558861968093521"></a><a name="p558861968093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1867752428093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">metaDataKey</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the metadata name in the <a href="metadata.md">MetaData</a>. </td>
</tr>
<tr id="row683561039093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleInfos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the obtained <a href="bundleinfo.md">BundleInfo</a> objects. </td>
</tr>
<tr id="row1622344350093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the number of <a href="bundleinfo.md">BundleInfo</a> objects obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## GetBundleNameForUid\(\)<a name="ga4afdc08ba78506fce95a066e137ac46d"></a>

```
uint8_t GetBundleNameForUid (int32_t uid, char ** bundleName )
```

 **Description:**

Obtains the bundle name of an application based on the specified UID. 

**Parameters:**

<a name="table743498660093521"></a>
<table><thead align="left"><tr id="row1333750311093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p162150895093521"><a name="p162150895093521"></a><a name="p162150895093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p102988444093521"><a name="p102988444093521"></a><a name="p102988444093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row968437521093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">uid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the UID of the application to query. </td>
</tr>
<tr id="row22975477093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the bundle name of the application. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## Install\(\)<a name="gaf1f1521a64cc98f076b0082df6c0abdd"></a>

```
bool Install (const char * hapPath, const InstallParam * installParam, [InstallerCallback](bundlemanager.md#ga00f021e76d728d2d44e1a28887ccc3af) installerCallback )
```

 **Description:**

Installs or updates an application. 

**Parameters:**

<a name="table11291529093521"></a>
<table><thead align="left"><tr id="row2055587081093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1098930137093521"><a name="p1098930137093521"></a><a name="p1098930137093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2132054705093521"><a name="p2132054705093521"></a><a name="p2132054705093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row557708253093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hapPath</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the path for storing the OpenHarmony Ability Package (HAP) of the application to install or update. </td>
</tr>
<tr id="row1147055748093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleCallback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to be invoked for notifying the installation or update result. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if this function is successfully called; returns  **false**  otherwise.



## QueryAbilityInfo\(\)<a name="ga4360375d15224d89632f59ee110b74c9"></a>

```
uint8_t QueryAbilityInfo (const [Want](want.md) * want, [AbilityInfo](abilityinfo.md) * abilityInfo )
```

 **Description:**

Queries the  [AbilityInfo](abilityinfo.md)  of an ability based on the information carried in the  [Want](want.md)  structure. 

**Parameters:**

<a name="table128359618093521"></a>
<table><thead align="left"><tr id="row797767663093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2112047274093521"><a name="p2112047274093521"></a><a name="p2112047274093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2070079002093521"><a name="p2070079002093521"></a><a name="p2070079002093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row157797826093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">want</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="want.md">Want</a> structure used for querying the specified ability. </td>
</tr>
<tr id="row1572326069093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">abilityInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained <a href="abilityinfo.md">AbilityInfo</a> object.</td>
</tr>
</tbody>
</table>

**Attention:**

Before querying an  [AbilityInfo](abilityinfo.md)  object, you should first call  **memset**  on the constructed  [AbilityInfo](abilityinfo.md)  object so that each field in it can be properly initialized for carrying the obtained information. 

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## QueryKeepAliveBundleInfos\(\)<a name="ga0c1cb00194993ecba7337fdf0a203314"></a>

```
uint8_t QueryKeepAliveBundleInfos ([BundleInfo](bundleinfo.md) ** bundleInfos, int32_t * len )
```

 **Description:**

Obtains the  [BundleInfo](bundleinfo.md)  of all keep-alive applications in the system. 

**Parameters:**

<a name="table1930218273093521"></a>
<table><thead align="left"><tr id="row1516522526093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2045632891093521"><a name="p2045632891093521"></a><a name="p2045632891093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1578613858093521"><a name="p1578613858093521"></a><a name="p1578613858093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1428294321093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleInfos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the obtained <a href="bundleinfo.md">BundleInfo</a> objects. </td>
</tr>
<tr id="row1496165144093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the number of <a href="bundleinfo.md">BundleInfo</a> objects obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## RegisterCallback\(\)<a name="ga5c49620ca8b752cd6f43fabc5d5c7416"></a>

```
int32_t RegisterCallback (BundleStatusCallback * BundleStatusCallback)
```

 **Description:**

Registers a callback to monitor the installation, update, and uninstallation state changes of an application. 

**Parameters:**

<a name="table1919977552093521"></a>
<table><thead align="left"><tr id="row783442767093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1682115450093521"><a name="p1682115450093521"></a><a name="p1682115450093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p870409052093521"><a name="p870409052093521"></a><a name="p870409052093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1599161081093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleCallback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to be invoked when the installation, update, or uninstallation state of the monitored application changes. </td>
</tr>
<tr id="row40732401093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the bundle name of the application to monitor. If this parameter is set to <strong id="b107686082093521"><a name="b107686082093521"></a><a name="b107686082093521"></a>nullptr</strong>, the installation, update, or uninstallation state of all applications will be monitored. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



## SetElementAbilityName\(\)<a name="ga93a575cc428cb96526ae02b3997f1f3b"></a>

```
bool SetElementAbilityName ([ElementName](elementname.md) * element, const char * abilityName )
```

 **Description:**

Sets the class name of the ability used to query  [AbilityInfo](abilityinfo.md). 

**Parameters:**

<a name="table2123984551093521"></a>
<table><thead align="left"><tr id="row773168224093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p829630877093521"><a name="p829630877093521"></a><a name="p829630877093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1831655249093521"><a name="p1831655249093521"></a><a name="p1831655249093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1692171303093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b33810138093521"><a name="b33810138093521"></a><a name="b33810138093521"></a><a href="elementname.md">ElementName</a></strong> to set. </td>
</tr>
<tr id="row574065410093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">abilityName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the class name to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the setting is successful; returns  **false**  otherwise. 



## SetElementBundleName\(\)<a name="ga60692e66a3a204a2f16f70c5cd452c1d"></a>

```
bool SetElementBundleName ([ElementName](elementname.md) * element, const char * bundleName )
```

 **Description:**

Sets the bundle name used to query  [AbilityInfo](abilityinfo.md). 

**Parameters:**

<a name="table1954886005093521"></a>
<table><thead align="left"><tr id="row1045511573093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2053415525093521"><a name="p2053415525093521"></a><a name="p2053415525093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1638136950093521"><a name="p1638136950093521"></a><a name="p1638136950093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1492592660093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b897897789093521"><a name="b897897789093521"></a><a name="b897897789093521"></a><a href="elementname.md">ElementName</a></strong> to set. </td>
</tr>
<tr id="row2138713387093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the bundle name to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the setting is successful; returns  **false**  otherwise. 



## SetElementDeviceID\(\)<a name="ga90e16f159ee8e7f1a9385feebb3dbc0c"></a>

```
bool SetElementDeviceID ([ElementName](elementname.md) * element, const char * deviceId )
```

 **Description:**

Sets the device ID used to query  [AbilityInfo](abilityinfo.md). 

**Parameters:**

<a name="table2077357099093521"></a>
<table><thead align="left"><tr id="row651048947093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1700894872093521"><a name="p1700894872093521"></a><a name="p1700894872093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1325436702093521"><a name="p1325436702093521"></a><a name="p1325436702093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1206601700093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">element</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1412949267093521"><a name="b1412949267093521"></a><a name="b1412949267093521"></a><a href="elementname.md">ElementName</a></strong> to set. </td>
</tr>
<tr id="row1685590886093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device ID to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the setting is successful; returns  **false**  otherwise. 



## Uninstall\(\)<a name="gaa117e44378315a61b4e71fd252b2e496"></a>

```
bool Uninstall (const char * bundleName, const InstallParam * installParam, [InstallerCallback](bundlemanager.md#ga00f021e76d728d2d44e1a28887ccc3af) installerCallback )
```

 **Description:**

Uninstalls an application. 

**Parameters:**

<a name="table325461398093521"></a>
<table><thead align="left"><tr id="row2141114823093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p263524617093521"><a name="p263524617093521"></a><a name="p263524617093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1156255887093521"><a name="p1156255887093521"></a><a name="p1156255887093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row636366823093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the bundle name of the application to uninstall. </td>
</tr>
<tr id="row1222177983093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleCallback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to be invoked for notifying the uninstallation result. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if this function is successfully called; returns  **false**  otherwise.



## UnregisterCallback\(\)<a name="ga095eee592eff6ce71a2a67a1a0e3e344"></a>

```
int32_t UnregisterCallback ()
```

 **Description:**

Unregisters a callback previously registered for monitoring the installation, update, and uninstallation state changes of an application. 

**Parameters:**

<a name="table1309672869093521"></a>
<table><thead align="left"><tr id="row1603631108093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p884465190093521"><a name="p884465190093521"></a><a name="p884465190093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p218522356093521"><a name="p218522356093521"></a><a name="p218522356093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2073656645093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bundleName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the bundle name of the application being monitored. If this parameter is set to <strong id="b2096667015093521"><a name="b2096667015093521"></a><a name="b2096667015093521"></a>nullptr</strong>, monitoring on the installation, update, or uninstallation state of all applications will be canceled. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  [ERR\_OK](bundlemanager.md#ggac318d4f4dc0125e2367ea8c539770ed1aa26c163b80b1f6786ca81dadc14b00fb)  if this function is successfully called; returns another error code defined in  [AppexecfwkErrors](bundlemanager.md#gac318d4f4dc0125e2367ea8c539770ed1)  otherwise.



