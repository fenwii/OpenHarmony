# wifiiot\_pwm.h<a name="ZH-CN_TOPIC_0000001055075075"></a>

## **Overview**<a name="section979751764191856"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the PWM interface functions. 

These functions are used for PWM initialization, deinitialization, and signal output. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1964347332191856"></a>

## Enumerations<a name="enum-members"></a>

<a name="table1096365732191856"></a>
<table><thead align="left"><tr id="row57998761191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1752471129191856"><a name="p1752471129191856"></a><a name="p1752471129191856"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p393234153191856"><a name="p393234153191856"></a><a name="p393234153191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row370422970191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p240232763191856"><a name="p240232763191856"></a><a name="p240232763191856"></a><a href="Wifiiot.md#ga2ecbd0ab9636fedd354de7447056df29">WifiIotPwmClkSource</a> { <a href="Wifiiot.md#gga2ecbd0ab9636fedd354de7447056df29adaadc6f6a5e89f7d1a8fa55d8cc89d0f">WIFI_IOT_PWM_CLK_160M</a>, <a href="Wifiiot.md#gga2ecbd0ab9636fedd354de7447056df29a610c246fc1c129b3c223884b5f644888">WIFI_IOT_PWM_CLK_XTAL</a>, <a href="Wifiiot.md#gga2ecbd0ab9636fedd354de7447056df29a09394bc5af28cf9e01eb6cca9bf8e633">WIFI_IOT_PWM_CLK_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219299254191856"><a name="p1219299254191856"></a><a name="p1219299254191856"></a>Enumerates PWM clock sources. </p>
</td>
</tr>
<tr id="row831047131191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p181037701191856"><a name="p181037701191856"></a><a name="p181037701191856"></a><a href="Wifiiot.md#gab3518ce878df4a40d614e88a6f81dea7">WifiIotPwmPort</a> { &nbsp;&nbsp;<a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7a99047f09c031299d4c68c0eb2dc523e9">WIFI_IOT_PWM_PORT_PWM0</a> = 0, <a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7afe267b92864e4b1bb171724d8f555922">WIFI_IOT_PWM_PORT_PWM1</a> = 1, <a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7ac6530394f6bab8fecc8cf7417646c66b">WIFI_IOT_PWM_PORT_PWM2</a> = 2, <a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7a0b16863a2291abfac01581c15e184126">WIFI_IOT_PWM_PORT_PWM3</a> = 3, &nbsp;&nbsp;<a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7aa6d4371910a891288c6181ffd358b7fb">WIFI_IOT_PWM_PORT_PWM4</a> = 4, <a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7a3f7666b782bb361e556e8062b4ff80aa">WIFI_IOT_PWM_PORT_PWM5</a> = 5, <a href="Wifiiot.md#ggab3518ce878df4a40d614e88a6f81dea7a24bfb3984d6e6e91f897e20e267ada3b">WIFI_IOT_PWM_PORT_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p361725082191856"><a name="p361725082191856"></a><a name="p361725082191856"></a>Enumerates PWM ports. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table952742221191856"></a>
<table><thead align="left"><tr id="row1645917653191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1909192175191856"><a name="p1909192175191856"></a><a name="p1909192175191856"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p790177599191856"><a name="p790177599191856"></a><a name="p790177599191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row734243333191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377107128191856"><a name="p1377107128191856"></a><a name="p1377107128191856"></a><a href="Wifiiot.md#ga27d50a2258388ba88ed35581096fb5eb">PwmInit</a> (<a href="Wifiiot.md#gab3518ce878df4a40d614e88a6f81dea7">WifiIotPwmPort</a> port)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2120948831191856"><a name="p2120948831191856"></a><a name="p2120948831191856"></a>unsigned int&nbsp;</p>
<p id="p596003761191856"><a name="p596003761191856"></a><a name="p596003761191856"></a>Initializes a PWM device. </p>
</td>
</tr>
<tr id="row1379300673191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051943474191856"><a name="p2051943474191856"></a><a name="p2051943474191856"></a><a href="Wifiiot.md#gac63da03016596aed4234e9c4053c15b9">PwmDeinit</a> (<a href="Wifiiot.md#gab3518ce878df4a40d614e88a6f81dea7">WifiIotPwmPort</a> port)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1203808215191856"><a name="p1203808215191856"></a><a name="p1203808215191856"></a>unsigned int&nbsp;</p>
<p id="p1009878953191856"><a name="p1009878953191856"></a><a name="p1009878953191856"></a>Deinitializes a PWM device. </p>
</td>
</tr>
<tr id="row1168419637191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292946667191856"><a name="p292946667191856"></a><a name="p292946667191856"></a><a href="Wifiiot.md#gae853022c27750fcdb9a2c60653761afe">PwmStart</a> (<a href="Wifiiot.md#gab3518ce878df4a40d614e88a6f81dea7">WifiIotPwmPort</a> port, unsigned short duty, unsigned short freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308573525191856"><a name="p1308573525191856"></a><a name="p1308573525191856"></a>unsigned int&nbsp;</p>
<p id="p1307967811191856"><a name="p1307967811191856"></a><a name="p1307967811191856"></a>Outputs PWM signals based on the input parameters. </p>
</td>
</tr>
<tr id="row1692903580191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607057869191856"><a name="p607057869191856"></a><a name="p607057869191856"></a><a href="Wifiiot.md#ga158474c4e73c1e557352c12cc31a154f">PwmStop</a> (<a href="Wifiiot.md#gab3518ce878df4a40d614e88a6f81dea7">WifiIotPwmPort</a> port)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p725693650191856"><a name="p725693650191856"></a><a name="p725693650191856"></a>unsigned int&nbsp;</p>
<p id="p455394764191856"><a name="p455394764191856"></a><a name="p455394764191856"></a>Stops the PWM signal output. </p>
</td>
</tr>
</tbody>
</table>

