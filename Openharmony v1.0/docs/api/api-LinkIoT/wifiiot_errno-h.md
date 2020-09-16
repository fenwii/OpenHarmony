# wifiiot\_errno.h<a name="ZH-CN_TOPIC_0000001054915089"></a>

## **Overview**<a name="section1184877017191855"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Defines error codes used by the Wi-Fi module. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section526659062191855"></a>

## Macros<a name="define-members"></a>

<a name="table773893923191855"></a>
<table><thead align="left"><tr id="row416555009191855"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p126891521191855"><a name="p126891521191855"></a><a name="p126891521191855"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p120931411191855"><a name="p120931411191855"></a><a name="p120931411191855"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1475289713191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1627992521191855"><a name="p1627992521191855"></a><a name="p1627992521191855"></a><a href="Wifiiot.md#gae70eaf627c0370cc271dcb8060aee861">WIFI_IOT_SUCCESS</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423840660191855"><a name="p423840660191855"></a><a name="p423840660191855"></a>Defines a module-level return value to indicate a successful operation. </p>
</td>
</tr>
<tr id="row163206930191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401864315191855"><a name="p1401864315191855"></a><a name="p1401864315191855"></a><a href="Wifiiot.md#gae2bfd5a14f6126c51fa6206a7f1008be">WIFI_IOT_FAILURE</a>&nbsp;&nbsp;&nbsp;(-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671714671191855"><a name="p671714671191855"></a><a name="p671714671191855"></a>Defines a module-level return value to indicate an operation failure. </p>
</td>
</tr>
<tr id="row1996483076191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p528263537191855"><a name="p528263537191855"></a><a name="p528263537191855"></a><a href="Wifiiot.md#gaf5cf7e2b308037a65be66bb755dc5880">WIFI_IOT_ERR_UART_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80001000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859747096191855"><a name="p859747096191855"></a><a name="p859747096191855"></a>Defines a UART error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row2047463736191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549892458191855"><a name="p549892458191855"></a><a name="p549892458191855"></a><a href="Wifiiot.md#ga5877267c67a4620a43d714d3d853d2e3">WIFI_IOT_ERR_UART_INVALID_SUSPEND</a>&nbsp;&nbsp;&nbsp;0x80001001</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1173848372191855"><a name="p1173848372191855"></a><a name="p1173848372191855"></a>Defines a UART error code to indicate an invalid pause operation. </p>
</td>
</tr>
<tr id="row958636937191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683535091191855"><a name="p1683535091191855"></a><a name="p1683535091191855"></a><a href="Wifiiot.md#ga2ba1db97d77cf3d74466a7951861538a">WIFI_IOT_ERR_UART_INVALID_PARITY</a>&nbsp;&nbsp;&nbsp;0x80001002</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28008064191855"><a name="p28008064191855"></a><a name="p28008064191855"></a>Defines a UART error code to indicate an invalid parity check. </p>
</td>
</tr>
<tr id="row1062710885191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658973128191855"><a name="p1658973128191855"></a><a name="p1658973128191855"></a><a href="Wifiiot.md#ga20dfd6fedd138cdd065e70e267c90340">WIFI_IOT_ERR_UART_INVALID_DATA_BITS</a>&nbsp;&nbsp;&nbsp;0x80001003</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69547817191855"><a name="p69547817191855"></a><a name="p69547817191855"></a>Defines a UART error code to indicate an invalid data bit. </p>
</td>
</tr>
<tr id="row1204186962191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p705599153191855"><a name="p705599153191855"></a><a name="p705599153191855"></a><a href="Wifiiot.md#ga936de56f79c06da2e782b00b66e47e8c">WIFI_IOT_ERR_UART_INVALID_STOP_BITS</a>&nbsp;&nbsp;&nbsp;0x80001004</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1364988456191855"><a name="p1364988456191855"></a><a name="p1364988456191855"></a>Defines a UART error code to indicate an invalid stop bit. </p>
</td>
</tr>
<tr id="row1983507015191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1816804470191855"><a name="p1816804470191855"></a><a name="p1816804470191855"></a><a href="Wifiiot.md#gacb947326cf340c964edb6ccdbb5273f1">WIFI_IOT_ERR_UART_INVALID_BAUD</a>&nbsp;&nbsp;&nbsp;0x80001005</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305663563191855"><a name="p1305663563191855"></a><a name="p1305663563191855"></a>Defines a UART error code to indicate an invalid baud rate. </p>
</td>
</tr>
<tr id="row2038908152191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451339888191855"><a name="p451339888191855"></a><a name="p451339888191855"></a><a href="Wifiiot.md#ga4c677c899cabd847fe4627400e27f4b0">WIFI_IOT_ERR_UART_INVALID_COM_PORT</a>&nbsp;&nbsp;&nbsp;0x80001006</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1984357540191855"><a name="p1984357540191855"></a><a name="p1984357540191855"></a>Defines a UART error code to indicate an invalid port number. </p>
</td>
</tr>
<tr id="row1116290545191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152859962191855"><a name="p1152859962191855"></a><a name="p1152859962191855"></a><a href="Wifiiot.md#ga08fefa68d06c7559dc59e69a4a5ff58d">WIFI_IOT_ERR_UART_NOT_SUPPORT_DMA</a>&nbsp;&nbsp;&nbsp;0x80001007</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1006166415191855"><a name="p1006166415191855"></a><a name="p1006166415191855"></a>Defines a UART error code to indicate a non-support for DMA. </p>
</td>
</tr>
<tr id="row1312456000191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p874252938191855"><a name="p874252938191855"></a><a name="p874252938191855"></a><a href="Wifiiot.md#ga2261c686d955fb1caca8a2b123330341">WIFI_IOT_ERR_UART_NOT_BLOCK_MODE</a>&nbsp;&nbsp;&nbsp;0x80001008</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899712640191855"><a name="p899712640191855"></a><a name="p899712640191855"></a>Defines a UART error code to indicate the non-block mode. </p>
</td>
</tr>
<tr id="row27774137191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111279354191855"><a name="p111279354191855"></a><a name="p111279354191855"></a><a href="Wifiiot.md#gae1dde2925aab87cc79a5cf3b55f69d7b">WIFI_IOT_ERR_GPIO_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80001040</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1425340344191855"><a name="p1425340344191855"></a><a name="p1425340344191855"></a>Defines a GPIO error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row1713528057191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p433055366191855"><a name="p433055366191855"></a><a name="p433055366191855"></a><a href="Wifiiot.md#ga86c5c689c1ba112ef2875bf01418281f">WIFI_IOT_ERR_GPIO_REPEAT_INIT</a>&nbsp;&nbsp;&nbsp;0x80001041</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2059411639191855"><a name="p2059411639191855"></a><a name="p2059411639191855"></a>Defines a GPIO error code to indicate repeated initialization. </p>
</td>
</tr>
<tr id="row2000800289191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p745558406191855"><a name="p745558406191855"></a><a name="p745558406191855"></a><a href="Wifiiot.md#ga4607e3646ccfe40732d4c068c071f53a">WIFI_IOT_ERR_GPIO_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x80001042</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1360861582191855"><a name="p1360861582191855"></a><a name="p1360861582191855"></a>Defines a GPIO error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row768844862191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p37516623191855"><a name="p37516623191855"></a><a name="p37516623191855"></a><a href="Wifiiot.md#ga0080f4d4a86cbce7e86d319386fd9cd2">WIFI_IOT_ERR_GPIO_NOT_SUPPORT</a>&nbsp;&nbsp;&nbsp;0x80001043</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142680368191855"><a name="p142680368191855"></a><a name="p142680368191855"></a>Defines a GPIO error code to indicate a non-support. </p>
</td>
</tr>
<tr id="row1876171017191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1818363432191855"><a name="p1818363432191855"></a><a name="p1818363432191855"></a><a href="Wifiiot.md#gaebd30986c46f1c6a01931f04776531a0">WIFI_IOT_ERR_FLASH_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x800010C0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1596855915191855"><a name="p1596855915191855"></a><a name="p1596855915191855"></a>Defines a flash error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row269091905191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1585301752191855"><a name="p1585301752191855"></a><a name="p1585301752191855"></a><a href="Wifiiot.md#ga2cd1281dc392b88851c7da895d121696">WIFI_IOT_ERR_FLASH_INVALID_PARAM</a>&nbsp;&nbsp;&nbsp;0x800010C1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007619334191855"><a name="p1007619334191855"></a><a name="p1007619334191855"></a>Defines a flash error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row2147116694191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1815008486191855"><a name="p1815008486191855"></a><a name="p1815008486191855"></a><a href="Wifiiot.md#ga0b58bc9856c6879faf0c6a65510fe341">WIFI_IOT_ERR_FLASH_INVALID_PARAM_BEYOND_ADDR</a>&nbsp;&nbsp;&nbsp;0x800010C2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73204831191855"><a name="p73204831191855"></a><a name="p73204831191855"></a>Defines a flash error code to indicate that the address is out of range. </p>
</td>
</tr>
<tr id="row2108827165191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1328916600191855"><a name="p1328916600191855"></a><a name="p1328916600191855"></a><a href="Wifiiot.md#gaefb0daa74035564d57262ae477bc7fa2">WIFI_IOT_ERR_FLASH_INVALID_PARAM_SIZE_ZERO</a>&nbsp;&nbsp;&nbsp;0x800010C3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147059303191855"><a name="p1147059303191855"></a><a name="p1147059303191855"></a>Defines a flash error code to indicate that the parameter size is <strong id="b443227804191855"><a name="b443227804191855"></a><a name="b443227804191855"></a>0</strong> </p>
</td>
</tr>
<tr id="row1770599630191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931977502191855"><a name="p1931977502191855"></a><a name="p1931977502191855"></a><a href="Wifiiot.md#gaadfebe4ca2dfbfbd5e6121216bb2b4cf">WIFI_IOT_ERR_FLASH_INVALID_PARAM_ERASE_NOT_ALIGN</a>&nbsp;&nbsp;&nbsp;0x800010C4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p901873412191855"><a name="p901873412191855"></a><a name="p901873412191855"></a>Defines a flash error code to indicate that the erase size is not aligned. </p>
</td>
</tr>
<tr id="row1967280609191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1010654973191855"><a name="p1010654973191855"></a><a name="p1010654973191855"></a><a href="Wifiiot.md#gae9ae811688863c24f7be8c89583ef5cb">WIFI_IOT_ERR_FLASH_INVALID_PARAM_IOCTRL_DATA_NULL</a>&nbsp;&nbsp;&nbsp;0x800010C5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p290975994191855"><a name="p290975994191855"></a><a name="p290975994191855"></a>Defines a flash error code to indicate that the data of the I/O controller is empty. </p>
</td>
</tr>
<tr id="row811126729191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1138459749191855"><a name="p1138459749191855"></a><a name="p1138459749191855"></a><a href="Wifiiot.md#ga41abe9a86b37f2c88714111895c5a7fd">WIFI_IOT_ERR_FLASH_INVALID_PARAM_DATA_NULL</a>&nbsp;&nbsp;&nbsp;0x800010C6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2092695949191855"><a name="p2092695949191855"></a><a name="p2092695949191855"></a>Defines a flash error code to indicate empty data. </p>
</td>
</tr>
<tr id="row1612464902191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1642568853191855"><a name="p1642568853191855"></a><a name="p1642568853191855"></a><a href="Wifiiot.md#ga9f31319390fdaa4051abaa5cf9c1e6bd">WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD1</a>&nbsp;&nbsp;&nbsp;0x800010C7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p326614414191855"><a name="p326614414191855"></a><a name="p326614414191855"></a>Defines a flash error code to indicate that pad1 is incorrect. </p>
</td>
</tr>
<tr id="row1684023600191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p693945712191855"><a name="p693945712191855"></a><a name="p693945712191855"></a><a href="Wifiiot.md#ga3aeceb16cc526bc3977e363533c4caf2">WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD2</a>&nbsp;&nbsp;&nbsp;0x800010C8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1153554427191855"><a name="p1153554427191855"></a><a name="p1153554427191855"></a>Defines a flash error code to indicate that pad2 is incorrect. </p>
</td>
</tr>
<tr id="row1805573007191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686299845191855"><a name="p686299845191855"></a><a name="p686299845191855"></a><a href="Wifiiot.md#gacb66dcc29fa65a9fa64a43a20acc3e6d">WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD3</a>&nbsp;&nbsp;&nbsp;0x800010C9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073770801191855"><a name="p2073770801191855"></a><a name="p2073770801191855"></a>Defines a flash error code to indicate that pad3 is incorrect. </p>
</td>
</tr>
<tr id="row1281077772191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1716475071191855"><a name="p1716475071191855"></a><a name="p1716475071191855"></a><a href="Wifiiot.md#ga3d5fe958b7383f49040abc6f1f1c9976">WIFI_IOT_ERR_FLASH_INVALID_PARAM_PAD4</a>&nbsp;&nbsp;&nbsp;0x800010CA</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p778139727191855"><a name="p778139727191855"></a><a name="p778139727191855"></a>Defines a flash error code to indicate that pad4 is incorrect. </p>
</td>
</tr>
<tr id="row1324069984191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p3631528191855"><a name="p3631528191855"></a><a name="p3631528191855"></a><a href="Wifiiot.md#gaf067c19a95c6c8c38a46956ec0aea959">WIFI_IOT_ERR_FLASH_TIME_OUT_WAIT_READY</a>&nbsp;&nbsp;&nbsp;0x800010CB</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179425040191855"><a name="p1179425040191855"></a><a name="p1179425040191855"></a>Defines a flash error code to indicate a timeout on waiting for ready. </p>
</td>
</tr>
<tr id="row763466218191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p690581562191855"><a name="p690581562191855"></a><a name="p690581562191855"></a><a href="Wifiiot.md#gad25105354cedaa65cadfd01e011d58aa">WIFI_IOT_ERR_FLASH_QUAD_MODE_READ_REG1</a>&nbsp;&nbsp;&nbsp;0x800010CC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1727731541191855"><a name="p1727731541191855"></a><a name="p1727731541191855"></a>Defines a flash error code to indicate that an error occurs when reading register 1. </p>
</td>
</tr>
<tr id="row1511515066191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p17399749191855"><a name="p17399749191855"></a><a name="p17399749191855"></a><a href="Wifiiot.md#gaf86f02647b83f2b4ad942748de6c3877">WIFI_IOT_ERR_FLASH_QUAD_MODE_READ_REG2</a>&nbsp;&nbsp;&nbsp;0x800010CD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1920447994191855"><a name="p1920447994191855"></a><a name="p1920447994191855"></a>Defines a flash error code to indicate that an error occurs when reading register 2. </p>
</td>
</tr>
<tr id="row665281288191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p231417342191855"><a name="p231417342191855"></a><a name="p231417342191855"></a><a href="Wifiiot.md#ga436294992f32cc090be1f296ef7edb1a">WIFI_IOT_ERR_FLASH_QUAD_MODE_COMPARE_REG</a>&nbsp;&nbsp;&nbsp;0x800010CE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1897912009191855"><a name="p1897912009191855"></a><a name="p1897912009191855"></a>Defines a flash error code to indicate that an error occurs when comparing registers. </p>
</td>
</tr>
<tr id="row260698895191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1349081576191855"><a name="p1349081576191855"></a><a name="p1349081576191855"></a><a href="Wifiiot.md#ga749a534281fe75e79788ac6bbd2ab6ab">WIFI_IOT_ERR_FLASH_NO_MATCH_FLASH</a>&nbsp;&nbsp;&nbsp;0x800010CF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1746560545191855"><a name="p1746560545191855"></a><a name="p1746560545191855"></a>Defines a flash error code to indicate a flash mismatch. </p>
</td>
</tr>
<tr id="row1099176487191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1142923285191855"><a name="p1142923285191855"></a><a name="p1142923285191855"></a><a href="Wifiiot.md#ga8e7bba169009c4a64d9d5d1c566d2d21">WIFI_IOT_ERR_FLASH_WRITE_ENABLE</a>&nbsp;&nbsp;&nbsp;0x800010D0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2027031233191855"><a name="p2027031233191855"></a><a name="p2027031233191855"></a>Defines a flash error code to indicate a failure in enabling write. </p>
</td>
</tr>
<tr id="row722837032191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p337163073191855"><a name="p337163073191855"></a><a name="p337163073191855"></a><a href="Wifiiot.md#ga0abb8298403aeb5a5362663affc67bf8">WIFI_IOT_ERR_FLASH_NO_MATCH_ERASE_SIZE</a>&nbsp;&nbsp;&nbsp;0x800010D1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357879191855"><a name="p1357879191855"></a><a name="p1357879191855"></a>Defines a flash error code to indicate a mismatch in the size of data to erase. </p>
</td>
</tr>
<tr id="row302174285191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892434078191855"><a name="p1892434078191855"></a><a name="p1892434078191855"></a><a href="Wifiiot.md#gaca07e3664b7ca260316507fe5bc0ece1">WIFI_IOT_ERR_FLASH_MAX_SPI_OP</a>&nbsp;&nbsp;&nbsp;0x800010D2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493876753191855"><a name="p493876753191855"></a><a name="p493876753191855"></a>Defines a flash error code to indicate the maximum value of the SPI operation. </p>
</td>
</tr>
<tr id="row23540295191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p536385579191855"><a name="p536385579191855"></a><a name="p536385579191855"></a><a href="Wifiiot.md#gad836fbc11d75d82a80f01c1517742e5a">WIFI_IOT_ERR_FLASH_NOT_SUPPORT_IOCTRL_ID</a>&nbsp;&nbsp;&nbsp;0x800010D3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492828974191855"><a name="p492828974191855"></a><a name="p492828974191855"></a>Defines a flash error code to indicate an unsupported IO controller ID.. </p>
</td>
</tr>
<tr id="row2080592032191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1210404575191855"><a name="p1210404575191855"></a><a name="p1210404575191855"></a><a href="Wifiiot.md#gad8b63e06e4ab22df1965868a5b8e9c34">WIFI_IOT_ERR_FLASH_INVALID_CHIP_ID</a>&nbsp;&nbsp;&nbsp;0x800010D4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2040704773191855"><a name="p2040704773191855"></a><a name="p2040704773191855"></a>Defines a flash error code to indicate an invalid chip ID. </p>
</td>
</tr>
<tr id="row1483423773191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953826049191855"><a name="p953826049191855"></a><a name="p953826049191855"></a><a href="Wifiiot.md#ga0658f79d7edb143919457775b77cc0ac">WIFI_IOT_ERR_FLASH_RE_INIT</a>&nbsp;&nbsp;&nbsp;0x800010D5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p471300424191855"><a name="p471300424191855"></a><a name="p471300424191855"></a>Defines a flash error code to indicate repeated initialization. </p>
</td>
</tr>
<tr id="row1942053301191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p130331141191855"><a name="p130331141191855"></a><a name="p130331141191855"></a><a href="Wifiiot.md#ga4b2d2f87ed5fbd5dae380b1faf41b4b8">WIFI_IOT_ERR_FLASH_WRITE_NOT_SUPPORT_ERASE</a>&nbsp;&nbsp;&nbsp;0x800010D6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p613132962191855"><a name="p613132962191855"></a><a name="p613132962191855"></a>Defines a flash error code to indicate a non-support for data erasure. </p>
</td>
</tr>
<tr id="row155365491191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1729393932191855"><a name="p1729393932191855"></a><a name="p1729393932191855"></a><a href="Wifiiot.md#ga93d94962d03d6551b528e1a65760a43c">WIFI_IOT_ERR_FLASH_WRITE_COMPARE_WRONG</a>&nbsp;&nbsp;&nbsp;0x800010D7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1384641071191855"><a name="p1384641071191855"></a><a name="p1384641071191855"></a>Defines a flash error code to indicate that an error occurs when comparing the data written. </p>
</td>
</tr>
<tr id="row1231004180191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p64191525191855"><a name="p64191525191855"></a><a name="p64191525191855"></a><a href="Wifiiot.md#gaff332b79601f3f3ed37fe184fe797fba">WIFI_IOT_ERR_FLASH_WAIT_CFG_START_TIME_OUT</a>&nbsp;&nbsp;&nbsp;0x800010D8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1815698780191855"><a name="p1815698780191855"></a><a name="p1815698780191855"></a>Defines a flash error code to indicate a timeout on waiting for a configuration to start. </p>
</td>
</tr>
<tr id="row424434877191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1695610528191855"><a name="p1695610528191855"></a><a name="p1695610528191855"></a><a href="Wifiiot.md#ga5ee3d72623a4d33d3d0373578a3a2361">WIFI_IOT_ERR_FLASH_PATITION_INIT_FAIL</a>&nbsp;&nbsp;&nbsp;0x800010D9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p691494498191855"><a name="p691494498191855"></a><a name="p691494498191855"></a>Defines a flash error code to indicate a partition initialization failure. </p>
</td>
</tr>
<tr id="row447803329191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953641310191855"><a name="p1953641310191855"></a><a name="p1953641310191855"></a><a href="Wifiiot.md#gac104ab385c136cf5eaf40f7dc51f81cd">WIFI_IOT_ERR_FLASH_INITILIZATION</a>&nbsp;&nbsp;&nbsp;0x800010DA</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p358194624191855"><a name="p358194624191855"></a><a name="p358194624191855"></a>Defines a flash error code to indicate initialization. </p>
</td>
</tr>
<tr id="row1204689877191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p418615209191855"><a name="p418615209191855"></a><a name="p418615209191855"></a><a href="Wifiiot.md#gaa7e9a59dbe5dea2a9bf0c31da1c3cc10">WIFI_IOT_ERR_FLASH_ERASE_NOT_4K_ALIGN</a>&nbsp;&nbsp;&nbsp;0x800010DB</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2143961058191855"><a name="p2143961058191855"></a><a name="p2143961058191855"></a>Defines a flash error code to indicate that the size of data to erase is not a multiple of 4K bytes. </p>
</td>
</tr>
<tr id="row678561117191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1549744716191855"><a name="p1549744716191855"></a><a name="p1549744716191855"></a><a href="Wifiiot.md#ga608fd06772893b809c7f0f158e85d09d">WIFI_IOT_ERR_FLASH_PROTECT_NOT_SUPPORT</a>&nbsp;&nbsp;&nbsp;0x800010DC</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938110041191855"><a name="p938110041191855"></a><a name="p938110041191855"></a>Defines a flash error code to indicate a non-support. </p>
</td>
</tr>
<tr id="row1795161919191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1084380760191855"><a name="p1084380760191855"></a><a name="p1084380760191855"></a><a href="Wifiiot.md#gaccc1cff2256173d6504b236d36733c6d">WIFI_IOT_ERR_FLASH_PROTECT_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x800010DD</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954718242191855"><a name="p954718242191855"></a><a name="p954718242191855"></a>Defines a flash error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row772841000191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1223409112191855"><a name="p1223409112191855"></a><a name="p1223409112191855"></a><a href="Wifiiot.md#ga76a2feb8426c43b143cb4f3ba9cfa0e2">WIFI_IOT_ERR_FLASH_PROTECT_RE_INIT</a>&nbsp;&nbsp;&nbsp;0x800010DE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p474762074191855"><a name="p474762074191855"></a><a name="p474762074191855"></a>Defines a flash error code to indicate repeated initialization. </p>
</td>
</tr>
<tr id="row1224399514191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p66551731191855"><a name="p66551731191855"></a><a name="p66551731191855"></a><a href="Wifiiot.md#ga148b4bd927a934584b15362b7a56ed9b">WIFI_IOT_ERR_FLASH_PROTECT_NOT_FIND_CHIP</a>&nbsp;&nbsp;&nbsp;0x800010DF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p710841248191855"><a name="p710841248191855"></a><a name="p710841248191855"></a>Defines a flash error code to indicate that no chip is found. </p>
</td>
</tr>
<tr id="row812575793191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676146617191855"><a name="p676146617191855"></a><a name="p676146617191855"></a><a href="Wifiiot.md#ga422a081f8d37f63e0fcaeec383d8e478">WIFI_IOT_ERR_FLASH_CRYPTO_INVALID_PARAM</a>&nbsp;&nbsp;&nbsp;0x800010F0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1384048385191855"><a name="p1384048385191855"></a><a name="p1384048385191855"></a>Defines a flash error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row1526647365191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p545350573191855"><a name="p545350573191855"></a><a name="p545350573191855"></a><a href="Wifiiot.md#ga271adaa6c3c576b4c871b0c28722e6c2">WIFI_IOT_ERR_FLASH_CRYPTO_BEYOND_ADDR_SIZE</a>&nbsp;&nbsp;&nbsp;0x800010F1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913804034191855"><a name="p1913804034191855"></a><a name="p1913804034191855"></a>Defines a flash error code to indicate that the address is out of range. </p>
</td>
</tr>
<tr id="row1428655126191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864292612191855"><a name="p1864292612191855"></a><a name="p1864292612191855"></a><a href="Wifiiot.md#ga5b9858094e8f0cd73050f0079f41a18d">WIFI_IOT_ERR_FLASH_CRYPTO_MALLOC_FAIL</a>&nbsp;&nbsp;&nbsp;0x800001F2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620626611191855"><a name="p620626611191855"></a><a name="p620626611191855"></a>Defines a flash error code to indicate a failure in applying for memory. </p>
</td>
</tr>
<tr id="row850599581191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p599585645191855"><a name="p599585645191855"></a><a name="p599585645191855"></a><a href="Wifiiot.md#ga20381f13537e23d77a33a43917f8b7bc">WIFI_IOT_ERR_FLASH_CRYPTO_DATA_ENCRYPT_ERR</a>&nbsp;&nbsp;&nbsp;0x800001F3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1366706041191855"><a name="p1366706041191855"></a><a name="p1366706041191855"></a>Defines a flash error code to indicate an encryption error. </p>
</td>
</tr>
<tr id="row1342883753191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988769908191855"><a name="p1988769908191855"></a><a name="p1988769908191855"></a><a href="Wifiiot.md#ga3727ba9b17d5b3ce5f53c4bb41b03ea6">WIFI_IOT_ERR_FLASH_CRYPTO_DATA_DECRYPT_ERR</a>&nbsp;&nbsp;&nbsp;0x800001F4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1471691944191855"><a name="p1471691944191855"></a><a name="p1471691944191855"></a>Defines a flash error code to indicate a decryption error. </p>
</td>
</tr>
<tr id="row1543623212191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460969345191855"><a name="p1460969345191855"></a><a name="p1460969345191855"></a><a href="Wifiiot.md#gaeddc722740b9d1405b6d4338e8f22abe">WIFI_IOT_ERR_FLASH_CRYPTO_KEY_EMPTY_ERR</a>&nbsp;&nbsp;&nbsp;0x800001F5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1528791178191855"><a name="p1528791178191855"></a><a name="p1528791178191855"></a>Defines a flash error code to indicate an empty key value. </p>
</td>
</tr>
<tr id="row1714328658191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179150922191855"><a name="p179150922191855"></a><a name="p179150922191855"></a><a href="Wifiiot.md#ga95cbe0f9ca1f79c65a8eab2338b25dc3">WIFI_IOT_ERR_FLASH_CRYPTO_MEMCPY_FAIL</a>&nbsp;&nbsp;&nbsp;0x800001F6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2027342585191855"><a name="p2027342585191855"></a><a name="p2027342585191855"></a>Defines a flash error code to indicate a copy failure. </p>
</td>
</tr>
<tr id="row1310184617191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735089949191855"><a name="p735089949191855"></a><a name="p735089949191855"></a><a href="Wifiiot.md#gaff6ccf87c21ba2f1786b0823d492b814">WIFI_IOT_ERR_FLASH_CRYPTO_NOT_SUPPORT</a>&nbsp;&nbsp;&nbsp;0x800001F7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p701803140191855"><a name="p701803140191855"></a><a name="p701803140191855"></a>Defines a flash error code to indicate a non-support for encryption. </p>
</td>
</tr>
<tr id="row864767874191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p581997594191855"><a name="p581997594191855"></a><a name="p581997594191855"></a><a href="Wifiiot.md#gac6e8d4d70fe1ca039b5e853f261c8fd8">WIFI_IOT_ERR_FLASH_CRYPTO_PREPARE_ERR</a>&nbsp;&nbsp;&nbsp;0x800001F8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1307079489191855"><a name="p1307079489191855"></a><a name="p1307079489191855"></a>Defines a flash error code to indicate an incorrect parameter during encryption. </p>
</td>
</tr>
<tr id="row1152676091191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p497202777191855"><a name="p497202777191855"></a><a name="p497202777191855"></a><a href="Wifiiot.md#ga8d1bfe4560224e99df17820ca283baa5">WIFI_IOT_ERR_FLASH_CRYPTO_KEY_INVALID_ERR</a>&nbsp;&nbsp;&nbsp;0x800001F9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1047421792191855"><a name="p1047421792191855"></a><a name="p1047421792191855"></a>Defines a flash error code to indicate an invalid key. </p>
</td>
</tr>
<tr id="row1516588343191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1328315347191855"><a name="p1328315347191855"></a><a name="p1328315347191855"></a><a href="Wifiiot.md#ga4ddacb6881da562bd8906a2374a21d15">WIFI_IOT_ERR_FLASH_CRYPTO_KEY_SAVE_ERR</a>&nbsp;&nbsp;&nbsp;0x800001FA</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1469982604191855"><a name="p1469982604191855"></a><a name="p1469982604191855"></a>Defines a flash error code to indicate a failure in saving the key. </p>
</td>
</tr>
<tr id="row1045883567191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870694633191855"><a name="p870694633191855"></a><a name="p870694633191855"></a><a href="Wifiiot.md#gab414fb9ce381560a725fe725511812b1">WIFI_IOT_ERR_FLASH_CRYPTO_KERNEL_ADDR_ERR</a>&nbsp;&nbsp;&nbsp;0x800001FB</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466925906191855"><a name="p1466925906191855"></a><a name="p1466925906191855"></a>Defines a flash error code to indicate an incorrect kernel address.. </p>
</td>
</tr>
<tr id="row1548066601191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955026092191855"><a name="p955026092191855"></a><a name="p955026092191855"></a><a href="Wifiiot.md#ga86974c4b426016d366b978096938101f">WIFI_IOT_ERR_I2C_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x80001180</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327703577191855"><a name="p1327703577191855"></a><a name="p1327703577191855"></a>Defines an I2C error code to indicate a non-support. </p>
</td>
</tr>
<tr id="row1487141234191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995081062191855"><a name="p995081062191855"></a><a name="p995081062191855"></a><a href="Wifiiot.md#gab663a535e93102e3c3ea1512f63664f8">WIFI_IOT_ERR_I2C_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80001181</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492918115191855"><a name="p492918115191855"></a><a name="p492918115191855"></a>Defines an I2C error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row1179542064191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550019264191855"><a name="p1550019264191855"></a><a name="p1550019264191855"></a><a href="Wifiiot.md#ga355774fcb1d6cc687d41e6ac93988e37">WIFI_IOT_ERR_I2C_TIMEOUT_START</a>&nbsp;&nbsp;&nbsp;0x80001182</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p430506135191855"><a name="p430506135191855"></a><a name="p430506135191855"></a>Defines an I2C error code to indicate a start timeout. </p>
</td>
</tr>
<tr id="row273298601191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657789577191855"><a name="p1657789577191855"></a><a name="p1657789577191855"></a><a href="Wifiiot.md#ga5504ab71071109a4adcc5ab594636bd0">WIFI_IOT_ERR_I2C_TIMEOUT_WAIT</a>&nbsp;&nbsp;&nbsp;0x80001183</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1500132659191855"><a name="p1500132659191855"></a><a name="p1500132659191855"></a>Defines an I2C error code to indicate a wait timeout. </p>
</td>
</tr>
<tr id="row1957759569191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p724623166191855"><a name="p724623166191855"></a><a name="p724623166191855"></a><a href="Wifiiot.md#ga70fe483466bb0a1908838d09af9e08ee">WIFI_IOT_ERR_I2C_TIMEOUT_STOP</a>&nbsp;&nbsp;&nbsp;0x80001184</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p55630745191855"><a name="p55630745191855"></a><a name="p55630745191855"></a>Defines an I2C error code to indicate a stop timeout. </p>
</td>
</tr>
<tr id="row566119861191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2026271030191855"><a name="p2026271030191855"></a><a name="p2026271030191855"></a><a href="Wifiiot.md#ga07d88ba023c14c7051330bb505fcf2a2">WIFI_IOT_ERR_I2C_TIMEOUT_RCV_BYTE</a>&nbsp;&nbsp;&nbsp;0x80001185</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p834122125191855"><a name="p834122125191855"></a><a name="p834122125191855"></a>Defines an I2C error code to indicate a receive timeout. </p>
</td>
</tr>
<tr id="row454162119191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207886696191855"><a name="p1207886696191855"></a><a name="p1207886696191855"></a><a href="Wifiiot.md#gadc61cee9de2201533a19247b2d8e991d">WIFI_IOT_ERR_I2C_TIMEOUT_RCV_BYTE_PROC</a>&nbsp;&nbsp;&nbsp;0x80001186</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1004857877191855"><a name="p1004857877191855"></a><a name="p1004857877191855"></a>Defines an I2C error code to indicate a processing timeout. </p>
</td>
</tr>
<tr id="row2034392520191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p154104294191855"><a name="p154104294191855"></a><a name="p154104294191855"></a><a href="Wifiiot.md#ga0535100d16963cfd5b83da321871c2e3">WIFI_IOT_ERR_I2C_WAIT_SEM_FAIL</a>&nbsp;&nbsp;&nbsp;0x80001187</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999042020191855"><a name="p1999042020191855"></a><a name="p1999042020191855"></a>Defines an I2C error code to indicate a waiting failure. </p>
</td>
</tr>
<tr id="row1798680562191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904240741191855"><a name="p904240741191855"></a><a name="p904240741191855"></a><a href="Wifiiot.md#ga1f827afc8a122131000e3c3a415482cb">WIFI_IOT_ERR_I2C_START_ACK_ERR</a>&nbsp;&nbsp;&nbsp;0x80001188</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p828550213191855"><a name="p828550213191855"></a><a name="p828550213191855"></a>Defines an I2C error code to indicate a responding failure. </p>
</td>
</tr>
<tr id="row1659141561191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p528448742191855"><a name="p528448742191855"></a><a name="p528448742191855"></a><a href="Wifiiot.md#ga8244270946d616498697e8f3f14ec777">WIFI_IOT_ERR_I2C_WAIT_ACK_ERR</a>&nbsp;&nbsp;&nbsp;0x80001189</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p526492015191855"><a name="p526492015191855"></a><a name="p526492015191855"></a>Defines an I2C error code to indicate a failure in waiting for a response. </p>
</td>
</tr>
<tr id="row1387592732191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997244113191855"><a name="p997244113191855"></a><a name="p997244113191855"></a><a href="Wifiiot.md#gad4e8ba59aa79284855f8097e2a10f2df">WIFI_IOT_ERR_SPI_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x800011C0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873562397191855"><a name="p873562397191855"></a><a name="p873562397191855"></a>Defines an SPI error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row1182267037191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259285650191855"><a name="p1259285650191855"></a><a name="p1259285650191855"></a><a href="Wifiiot.md#ga503c84a7a64db295583a4c32c799002f">WIFI_IOT_ERR_SPI_REINIT</a>&nbsp;&nbsp;&nbsp;0x800011C1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p603631034191855"><a name="p603631034191855"></a><a name="p603631034191855"></a>Defines an SPI error code to indicate repeated initialization. </p>
</td>
</tr>
<tr id="row2033777352191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p929635490191855"><a name="p929635490191855"></a><a name="p929635490191855"></a><a href="Wifiiot.md#gafacaaace84501679b61488c53d5e76c3">WIFI_IOT_ERR_SPI_PARAMETER_WRONG</a>&nbsp;&nbsp;&nbsp;0x800011C2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p834368573191855"><a name="p834368573191855"></a><a name="p834368573191855"></a>Defines an SPI error code to indicate a parameter error. </p>
</td>
</tr>
<tr id="row1444326435191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516474327191855"><a name="p1516474327191855"></a><a name="p1516474327191855"></a><a href="Wifiiot.md#gaa419999b00bbb93a9bf7ec6e5729d3c3">WIFI_IOT_ERR_SPI_BUSY</a>&nbsp;&nbsp;&nbsp;0x800011C3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1500036804191855"><a name="p1500036804191855"></a><a name="p1500036804191855"></a>Defines an SPI error code to indicate the busy state. </p>
</td>
</tr>
<tr id="row2002961155191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1993538111191855"><a name="p1993538111191855"></a><a name="p1993538111191855"></a><a href="Wifiiot.md#ga9063703b367dc0e392759c6e9f2f84ec">WIFI_IOT_ERR_SPI_WRITE_TIMEOUT</a>&nbsp;&nbsp;&nbsp;0x800011C4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820940673191855"><a name="p1820940673191855"></a><a name="p1820940673191855"></a>Defines an SPI error code to indicate a write timeout. </p>
</td>
</tr>
<tr id="row574449387191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p739347938191855"><a name="p739347938191855"></a><a name="p739347938191855"></a><a href="Wifiiot.md#ga10a6043e83efd5639859fce4dc3ffa6c">WIFI_IOT_ERR_SPI_READ_TIMEOUT</a>&nbsp;&nbsp;&nbsp;0x800011C5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p203235075191855"><a name="p203235075191855"></a><a name="p203235075191855"></a>Defines an SPI error code to indicate a read timeout. </p>
</td>
</tr>
<tr id="row1752181620191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p869014310191855"><a name="p869014310191855"></a><a name="p869014310191855"></a><a href="Wifiiot.md#gade8e979043f1d0641ac08adb73197730">WIFI_IOT_ERR_SPI_NOT_SUPPORT_DMA</a>&nbsp;&nbsp;&nbsp;0x800011C6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1689501988191855"><a name="p1689501988191855"></a><a name="p1689501988191855"></a>Defines an SPI error code to indicate a non-support for DMA. </p>
</td>
</tr>
<tr id="row131831037191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p679471695191855"><a name="p679471695191855"></a><a name="p679471695191855"></a><a href="Wifiiot.md#gac059172aa16736913b47cd9fff537afc">WIFI_IOT_ERR_SDIO_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80001280</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159631313191855"><a name="p159631313191855"></a><a name="p159631313191855"></a>Defines an SDIO error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row1474567928191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772015459191855"><a name="p1772015459191855"></a><a name="p1772015459191855"></a><a href="Wifiiot.md#ga26eb2003b98a03a78822e072ea9d6f1a">WIFI_IOT_ERR_ADC_PARAMETER_WRONG</a>&nbsp;&nbsp;&nbsp;0x80001300</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142537764191855"><a name="p142537764191855"></a><a name="p142537764191855"></a>Defines an ADC error code to indicate a parameter error. </p>
</td>
</tr>
<tr id="row21222616191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339147372191855"><a name="p339147372191855"></a><a name="p339147372191855"></a><a href="Wifiiot.md#ga51d02496da9b876fb3953fde207ab83e">WIFI_IOT_ERR_ADC_INVALID_CHANNEL_ID</a>&nbsp;&nbsp;&nbsp;0x80001301</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1335257776191855"><a name="p1335257776191855"></a><a name="p1335257776191855"></a>Defines an ADC error code to indicate an invalid channel. </p>
</td>
</tr>
<tr id="row2091879084191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p395161283191855"><a name="p395161283191855"></a><a name="p395161283191855"></a><a href="Wifiiot.md#gad43d862b02b1e8d7e11562bb8192e18d">WIFI_IOT_ERR_ADC_TIMEOUT</a>&nbsp;&nbsp;&nbsp;0x80001302</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478190600191855"><a name="p478190600191855"></a><a name="p478190600191855"></a>Defines an ADC error code to indicate a timeout. </p>
</td>
</tr>
<tr id="row926893668191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p252152949191855"><a name="p252152949191855"></a><a name="p252152949191855"></a><a href="Wifiiot.md#gad299ef5c0943421884e6941827679935">WIFI_IOT_ERR_ADC_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x80001303</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395858433191855"><a name="p395858433191855"></a><a name="p395858433191855"></a>Defines an ADC error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row1693925384191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p552608321191855"><a name="p552608321191855"></a><a name="p552608321191855"></a><a href="Wifiiot.md#ga59e7a7be362105ba9f68558a305df640">WIFI_IOT_ERR_PWM_NO_INIT</a>&nbsp;&nbsp;&nbsp;0x80001340</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064475947191855"><a name="p2064475947191855"></a><a name="p2064475947191855"></a>Defines a PWM error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row1406489574191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183065382191855"><a name="p1183065382191855"></a><a name="p1183065382191855"></a><a href="Wifiiot.md#gacfc74f2eb47edfc1c5fc6f0a8eb06853">WIFI_IOT_ERR_PWM_INITILIZATION_ALREADY</a>&nbsp;&nbsp;&nbsp;0x80001341</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946163818191855"><a name="p1946163818191855"></a><a name="p1946163818191855"></a>Defines a PWM error code to indicate an initialization error. </p>
</td>
</tr>
<tr id="row670685028191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2001812259191855"><a name="p2001812259191855"></a><a name="p2001812259191855"></a><a href="Wifiiot.md#ga63e9f9737a00e8fc7147ba18d21682a5">WIFI_IOT_ERR_PWM_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80001342</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586766674191855"><a name="p1586766674191855"></a><a name="p1586766674191855"></a>Defines a PWM error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row1903578511191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p729414865191855"><a name="p729414865191855"></a><a name="p729414865191855"></a><a href="Wifiiot.md#gaa0095a6a3cce0f1b5ac6d76167ac5db9">WIFI_IOT_ERR_DMA_INVALID_PARA</a>&nbsp;&nbsp;&nbsp;0x80001380</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1591143556191855"><a name="p1591143556191855"></a><a name="p1591143556191855"></a>Defines a DMA error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row1949862528191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p446771844191855"><a name="p446771844191855"></a><a name="p446771844191855"></a><a href="Wifiiot.md#gabb302953a44571fa73d9142037e8369c">WIFI_IOT_ERR_DMA_NOT_INIT</a>&nbsp;&nbsp;&nbsp;0x80001381</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577203743191855"><a name="p577203743191855"></a><a name="p577203743191855"></a>Defines a DMA error code to indicate non-initialization. </p>
</td>
</tr>
<tr id="row1916763027191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p932986507191855"><a name="p932986507191855"></a><a name="p932986507191855"></a><a href="Wifiiot.md#ga8e39d0a271b7dc5226f73a1e8e4bf540">WIFI_IOT_ERR_DMA_BUSY</a>&nbsp;&nbsp;&nbsp;0x80001382</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p737937307191855"><a name="p737937307191855"></a><a name="p737937307191855"></a>Defines a DMA error code to indicate the busy state. </p>
</td>
</tr>
<tr id="row1872025327191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2112121883191855"><a name="p2112121883191855"></a><a name="p2112121883191855"></a><a href="Wifiiot.md#gaac0d381fd56d357ca04f5ba662630ad4">WIFI_IOT_ERR_DMA_TRANSFER_FAIL</a>&nbsp;&nbsp;&nbsp;0x80001383</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400786015191855"><a name="p400786015191855"></a><a name="p400786015191855"></a>Defines a DMA error code to indicate a transmission failure. </p>
</td>
</tr>
<tr id="row792268154191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1368670900191855"><a name="p1368670900191855"></a><a name="p1368670900191855"></a><a href="Wifiiot.md#ga2d964ec500835559f09356795773081c">WIFI_IOT_ERR_DMA_TRANSFER_TIMEOUT</a>&nbsp;&nbsp;&nbsp;0x80001384</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1747122803191855"><a name="p1747122803191855"></a><a name="p1747122803191855"></a>Defines a DMA error code to indicate a transmission timeout. </p>
</td>
</tr>
<tr id="row1653163523191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p700958943191855"><a name="p700958943191855"></a><a name="p700958943191855"></a><a href="Wifiiot.md#ga126bae9f91f5c1cc91bdcc1f8d10acd3">WIFI_IOT_ERR_DMA_GET_NOTE_FAIL</a>&nbsp;&nbsp;&nbsp;0x80001385</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097317632191855"><a name="p2097317632191855"></a><a name="p2097317632191855"></a>Defines a DMA error code to indicate a retrieval failure. </p>
</td>
</tr>
<tr id="row212265075191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p754031821191855"><a name="p754031821191855"></a><a name="p754031821191855"></a><a href="Wifiiot.md#ga0676eed6e7e5e5771fce800a131dde53">WIFI_IOT_ERR_DMA_LLI_NOT_CREATE</a>&nbsp;&nbsp;&nbsp;0x80001386</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1360664037191855"><a name="p1360664037191855"></a><a name="p1360664037191855"></a>Defines a DMA error code to indicate that the LLI is not created. </p>
</td>
</tr>
<tr id="row1210003492191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635496578191855"><a name="p635496578191855"></a><a name="p635496578191855"></a><a href="Wifiiot.md#gaf8502b3f56b5750a131d36bf91d8fea0">WIFI_IOT_ERR_DMA_CH_IRQ_ENABLE_FAIL</a>&nbsp;&nbsp;&nbsp;0x80001387</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1079097030191855"><a name="p1079097030191855"></a><a name="p1079097030191855"></a>Defines a DMA error code to indicate a failure in enabling channel interrupt. </p>
</td>
</tr>
<tr id="row1864152964191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390875151191855"><a name="p390875151191855"></a><a name="p390875151191855"></a><a href="Wifiiot.md#ga24837886814d447997ba4e147d7b88b7">WIFI_IOT_ERR_I2S_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80001400</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908124139191855"><a name="p908124139191855"></a><a name="p908124139191855"></a>Defines an I2S error code to indicate an invalid parameter. </p>
</td>
</tr>
<tr id="row926712062191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p744062722191855"><a name="p744062722191855"></a><a name="p744062722191855"></a><a href="Wifiiot.md#ga624feb752f94207583f7529eea816197">WIFI_IOT_ERR_I2S_WRITE_TIMEOUT</a>&nbsp;&nbsp;&nbsp;0x80001401</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698830434191855"><a name="p1698830434191855"></a><a name="p1698830434191855"></a>Defines an I2S error code to indicate a write timeout. </p>
</td>
</tr>
<tr id="row732323938191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106696491191855"><a name="p1106696491191855"></a><a name="p1106696491191855"></a><a href="Wifiiot.md#ga227218024cb39b3c9569b5ca1512cdd7">WIFI_IOT_ERR_AT_NAME_OR_FUNC_REPEAT_REGISTERED</a>&nbsp;&nbsp;&nbsp;0x80003280</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1104719798191855"><a name="p1104719798191855"></a><a name="p1104719798191855"></a>Defines an AT error code to indicate repeated function registration. </p>
</td>
</tr>
<tr id="row1958623804191855"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p74789679191855"><a name="p74789679191855"></a><a name="p74789679191855"></a><a href="Wifiiot.md#gafeeea5f2038721f00f3233c32b81d176">WIFI_IOT_ERR_AT_INVALID_PARAMETER</a>&nbsp;&nbsp;&nbsp;0x80003281</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837899727191855"><a name="p837899727191855"></a><a name="p837899727191855"></a>Defines an AT error code to indicate an invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

