# fenv.h<a name="ZH-CN_TOPIC_0000001055189443"></a>

## **Overview**<a name="section1076127382084829"></a>

**Related Modules:**

[MATH](MATH.md)

**Description:**

Declares specific functions for performing operations for floating-point exceptions and rounding modes. 

You can use the functions provided in this file to set, clear, and store the current floating-point exception and to obtain and set the current rounding mode. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section339020810084829"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table173249635084829"></a>
<table><thead align="left"><tr id="row566904649084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p885295812084829"><a name="p885295812084829"></a><a name="p885295812084829"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2114894054084829"><a name="p2114894054084829"></a><a name="p2114894054084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row47905178084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p65275906084829"><a name="p65275906084829"></a><a name="p65275906084829"></a><a href="fenv_t.md">fenv_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883146524084829"><a name="p1883146524084829"></a><a name="p1883146524084829"></a>Defines the floating-point environment. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1118051375084829"></a>
<table><thead align="left"><tr id="row231737488084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2086010779084829"><a name="p2086010779084829"></a><a name="p2086010779084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2135453510084829"><a name="p2135453510084829"></a><a name="p2135453510084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1767583278084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856827603084829"><a name="p1856827603084829"></a><a name="p1856827603084829"></a><a href="MATH.md#ga638c8489adb1fac7204b07ece42998ae">FE_INVALID</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p927801473084829"><a name="p927801473084829"></a><a name="p927801473084829"></a>Indicates an invalid floating-point exception. At least one parameter value is not defined in the function. </p>
</td>
</tr>
<tr id="row406235955084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p185244898084829"><a name="p185244898084829"></a><a name="p185244898084829"></a><a href="MATH.md#gab1317930189d1a14841893fb4bd9b5a0">FE_DIVBYZERO</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010802891084829"><a name="p2010802891084829"></a><a name="p2010802891084829"></a>Indicates a pole error exception. The return value is asymptotically infinite when the divisor is zero or the input is asymptotic to zero. </p>
</td>
</tr>
<tr id="row223729649084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900570943084829"><a name="p1900570943084829"></a><a name="p1900570943084829"></a><a href="MATH.md#gad373306add36e7227d9c9620b6962323">FE_OVERFLOW</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1641618522084829"><a name="p1641618522084829"></a><a name="p1641618522084829"></a>Indicates an overflow floating-point exception. The result is too large to be represented in the normal return value. </p>
</td>
</tr>
<tr id="row1922015768084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583414382084829"><a name="p583414382084829"></a><a name="p583414382084829"></a><a href="MATH.md#ga57b80dfe7d5ce60c3c76e517fce89ffe">FE_UNDERFLOW</a>&nbsp;&nbsp;&nbsp;8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1552019267084829"><a name="p1552019267084829"></a><a name="p1552019267084829"></a>Indicates an underflow floating-point exception. The result is too small to be represented in the normal return value. </p>
</td>
</tr>
<tr id="row404596437084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638126754084829"><a name="p1638126754084829"></a><a name="p1638126754084829"></a><a href="MATH.md#ga6e24165ff28571734b3e14530219faab">FE_INEXACT</a>&nbsp;&nbsp;&nbsp;16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1444443440084829"><a name="p1444443440084829"></a><a name="p1444443440084829"></a>Indicates an inexact floating-point exception. </p>
</td>
</tr>
<tr id="row307844992084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1590060193084829"><a name="p1590060193084829"></a><a name="p1590060193084829"></a><a href="MATH.md#ga09e405b3782b934813075e48366dda9a">FE_ALL_EXCEPT</a>&nbsp;&nbsp;&nbsp;31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804505751084829"><a name="p804505751084829"></a><a name="p804505751084829"></a>Indicates bitwise OR of all the preceding supported floating-point exceptions. </p>
</td>
</tr>
<tr id="row1937540548084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p307808757084829"><a name="p307808757084829"></a><a name="p307808757084829"></a><a href="MATH.md#ga5b5383719a63f98b7c95cc2feccaa1a7">FE_TONEAREST</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2067090206084829"><a name="p2067090206084829"></a><a name="p2067090206084829"></a>Indicates rounding towards the nearest integer. </p>
</td>
</tr>
<tr id="row1587736101084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806553987084829"><a name="p806553987084829"></a><a name="p806553987084829"></a><a href="MATH.md#ga5e011a345a41ad4622da05932e83536f">FE_DOWNWARD</a>&nbsp;&nbsp;&nbsp;0x800000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902992486084829"><a name="p1902992486084829"></a><a name="p1902992486084829"></a>Indicates rounding towards negative infinity. </p>
</td>
</tr>
<tr id="row763572496084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1598700481084829"><a name="p1598700481084829"></a><a name="p1598700481084829"></a><a href="MATH.md#ga5aa71a164a4b4d7780570d97058890f1">FE_UPWARD</a>&nbsp;&nbsp;&nbsp;0x400000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1411608881084829"><a name="p1411608881084829"></a><a name="p1411608881084829"></a>Indicates rounding towards positive infinity. </p>
</td>
</tr>
<tr id="row375310228084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p491176975084829"><a name="p491176975084829"></a><a name="p491176975084829"></a><a href="MATH.md#gac171099e006285a9e8be5683be71591c">FE_TOWARDZERO</a>&nbsp;&nbsp;&nbsp;0xc00000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309942068084829"><a name="p1309942068084829"></a><a name="p1309942068084829"></a>Indicates rounding towards zero. </p>
</td>
</tr>
<tr id="row250392700084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1389077119084829"><a name="p1389077119084829"></a><a name="p1389077119084829"></a><a href="MATH.md#ga5777a3689f7f4c555df1c643d28b5bc0">FE_DFL_ENV</a>&nbsp;&nbsp;&nbsp;((const <a href="fenv_t.md">fenv_t</a> *) -1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069319595084829"><a name="p2069319595084829"></a><a name="p2069319595084829"></a>Defines the default floating-point environment. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table98819501084829"></a>
<table><thead align="left"><tr id="row330317891084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1531267185084829"><a name="p1531267185084829"></a><a name="p1531267185084829"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p634235732084829"><a name="p634235732084829"></a><a name="p634235732084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1519868433084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p356464256084829"><a name="p356464256084829"></a><a name="p356464256084829"></a><a href="MATH.md#ga3eec78fdb9921de3f7254105f546c624">fexcept_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p943622710084829"><a name="p943622710084829"></a><a name="p943622710084829"></a> typedef unsigned long&nbsp;</p>
<p id="p1686858963084829"><a name="p1686858963084829"></a><a name="p1686858963084829"></a>Floating-point exception type. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table891068792084829"></a>
<table><thead align="left"><tr id="row2092356443084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2014202682084829"><a name="p2014202682084829"></a><a name="p2014202682084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1808194150084829"><a name="p1808194150084829"></a><a name="p1808194150084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row445158621084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118075812084829"><a name="p2118075812084829"></a><a name="p2118075812084829"></a><a href="MATH.md#gac85b548794b2e0c90e147ab5e0f285e5">feclearexcept</a> (int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323773955084829"><a name="p1323773955084829"></a><a name="p1323773955084829"></a>int&nbsp;</p>
<p id="p695245553084829"><a name="p695245553084829"></a><a name="p695245553084829"></a>Clears floating-point exceptions specified by <strong id="b722785746084829"><a name="b722785746084829"></a><a name="b722785746084829"></a>excepts</strong>. </p>
</td>
</tr>
<tr id="row1467150334084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612118314084829"><a name="p612118314084829"></a><a name="p612118314084829"></a><a href="MATH.md#gadc77aa0943782d65cd89a7ad931efccd">fegetexceptflag</a> (<a href="MATH.md#ga3eec78fdb9921de3f7254105f546c624">fexcept_t</a> *flagp, int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996197034084829"><a name="p996197034084829"></a><a name="p996197034084829"></a>int&nbsp;</p>
<p id="p1912753794084829"><a name="p1912753794084829"></a><a name="p1912753794084829"></a>Stores the floating-point exceptions specified by <strong id="b803491955084829"><a name="b803491955084829"></a><a name="b803491955084829"></a>excepts</strong> into the <strong id="b1822242872084829"><a name="b1822242872084829"></a><a name="b1822242872084829"></a>flagp</strong> variable address. </p>
</td>
</tr>
<tr id="row814553401084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1756237896084829"><a name="p1756237896084829"></a><a name="p1756237896084829"></a><a href="MATH.md#gaeecf59ba4dd156c6a9954bd0c1a9f6eb">feraiseexcept</a> (int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526399983084829"><a name="p1526399983084829"></a><a name="p1526399983084829"></a>int&nbsp;</p>
<p id="p289055900084829"><a name="p289055900084829"></a><a name="p289055900084829"></a>Obtains the floating-point exceptions specified by <strong id="b482090526084829"><a name="b482090526084829"></a><a name="b482090526084829"></a>excepts</strong>. </p>
</td>
</tr>
<tr id="row305957072084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377229606084829"><a name="p1377229606084829"></a><a name="p1377229606084829"></a><a href="MATH.md#gafb3852ee8f5a841548c91bac153ee3d1">fesetexceptflag</a> (const <a href="MATH.md#ga3eec78fdb9921de3f7254105f546c624">fexcept_t</a> *flagp, int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303090510084829"><a name="p1303090510084829"></a><a name="p1303090510084829"></a>int&nbsp;</p>
<p id="p1561884880084829"><a name="p1561884880084829"></a><a name="p1561884880084829"></a>Sets the exception status flag by copying the floating-point exceptions stored in the <strong id="b860367633084829"><a name="b860367633084829"></a><a name="b860367633084829"></a>flagp</strong> address to the <strong id="b1481129747084829"><a name="b1481129747084829"></a><a name="b1481129747084829"></a>excepts</strong> parameter. </p>
</td>
</tr>
<tr id="row904286539084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1378260389084829"><a name="p1378260389084829"></a><a name="p1378260389084829"></a><a href="MATH.md#ga1fd22f10456d303ba12c28e394b1da90">fetestexcept</a> (int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646448887084829"><a name="p1646448887084829"></a><a name="p1646448887084829"></a>int&nbsp;</p>
<p id="p1749451288084829"><a name="p1749451288084829"></a><a name="p1749451288084829"></a>Checks whether the floating-point exceptions specified by <strong id="b1255707986084829"><a name="b1255707986084829"></a><a name="b1255707986084829"></a>excepts</strong> have been raised. </p>
</td>
</tr>
<tr id="row1406982666084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1045114875084829"><a name="p1045114875084829"></a><a name="p1045114875084829"></a><a href="MATH.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8">fegetround</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973039507084829"><a name="p1973039507084829"></a><a name="p1973039507084829"></a>int&nbsp;</p>
<p id="p622469517084829"><a name="p622469517084829"></a><a name="p622469517084829"></a>Obtains the macro corresponding to the current rounding mode. </p>
</td>
</tr>
<tr id="row2144166904084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p634891231084829"><a name="p634891231084829"></a><a name="p634891231084829"></a><a href="MATH.md#ga5729c4728ebe75d4975bb7250a2d8f4a">fesetround</a> (int rounding_mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1887200012084829"><a name="p1887200012084829"></a><a name="p1887200012084829"></a>int&nbsp;</p>
<p id="p1559208184084829"><a name="p1559208184084829"></a><a name="p1559208184084829"></a>Sets the rounding mode. </p>
</td>
</tr>
<tr id="row1350094645084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p326092317084829"><a name="p326092317084829"></a><a name="p326092317084829"></a><a href="MATH.md#ga9a971efefb28e62b22de4e5f2567da81">fegetenv</a> (<a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96662345084829"><a name="p96662345084829"></a><a name="p96662345084829"></a>int&nbsp;</p>
<p id="p1050478748084829"><a name="p1050478748084829"></a><a name="p1050478748084829"></a>Stores the current floating-point environment into the object specified by <strong id="b2104222242084829"><a name="b2104222242084829"></a><a name="b2104222242084829"></a>envp</strong>. </p>
</td>
</tr>
<tr id="row1667755563084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1779661999084829"><a name="p1779661999084829"></a><a name="p1779661999084829"></a><a href="MATH.md#ga7bf2aed63eeaa74f4295a996b3ba4616">feholdexcept</a> (<a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1042796712084829"><a name="p1042796712084829"></a><a name="p1042796712084829"></a>int&nbsp;</p>
<p id="p2146353278084829"><a name="p2146353278084829"></a><a name="p2146353278084829"></a>Stores the current floating-point environment into the object specified by <strong id="b825187025084829"><a name="b825187025084829"></a><a name="b825187025084829"></a>envp</strong>, with all status flags cleared. </p>
</td>
</tr>
<tr id="row872531176084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1054470348084829"><a name="p1054470348084829"></a><a name="p1054470348084829"></a><a href="MATH.md#ga65184dc5ad4e001083a6fd59d0cd7a2d">fesetenv</a> (const <a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p595993555084829"><a name="p595993555084829"></a><a name="p595993555084829"></a>int&nbsp;</p>
<p id="p311227039084829"><a name="p311227039084829"></a><a name="p311227039084829"></a>Sets the current floating-point environment. </p>
</td>
</tr>
<tr id="row408795594084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665294542084829"><a name="p665294542084829"></a><a name="p665294542084829"></a><a href="MATH.md#gaa8c45da6bfe39178d4d199d3f0f6bbaf">feupdateenv</a> (const <a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932794422084829"><a name="p1932794422084829"></a><a name="p1932794422084829"></a>int&nbsp;</p>
<p id="p952382646084829"><a name="p952382646084829"></a><a name="p952382646084829"></a>Updates the current floating-point environment from the object specified by <strong id="b1341967328084829"><a name="b1341967328084829"></a><a name="b1341967328084829"></a>envp</strong>. </p>
</td>
</tr>
</tbody>
</table>

