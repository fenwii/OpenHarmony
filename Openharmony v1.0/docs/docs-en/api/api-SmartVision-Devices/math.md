# MATH<a name="EN-US_TOPIC_0000001055228010"></a>

## **Overview**<a name="section652651780084824"></a>

Provides math functions, such as trigonometric, exponential, logarithmic functions,and perform operations on complex numbers. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1703895429084824"></a>

## Files<a name="files"></a>

<a name="table2008929174084824"></a>
<table><thead align="left"><tr id="row1157876129084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1066428612084824"><a name="p1066428612084824"></a><a name="p1066428612084824"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1980383298084824"><a name="p1980383298084824"></a><a name="p1980383298084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1023761931084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434831419084824"><a name="p1434831419084824"></a><a name="p1434831419084824"></a><a href="complex-h.md">complex.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1426744713084824"><a name="p1426744713084824"></a><a name="p1426744713084824"></a>Declares functions to perform operations on complex numbers. </p>
</td>
</tr>
<tr id="row1427656343084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1345148323084824"><a name="p1345148323084824"></a><a name="p1345148323084824"></a><a href="fenv-h.md">fenv.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1496574266084824"><a name="p1496574266084824"></a><a name="p1496574266084824"></a>Declares specific functions for performing operations for floating-point exceptions and rounding modes. </p>
</td>
</tr>
<tr id="row312016451084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118317097084824"><a name="p2118317097084824"></a><a name="p2118317097084824"></a><a href="math-h.md">math.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597843427084824"><a name="p1597843427084824"></a><a name="p1597843427084824"></a>Provides common math functions. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table819181793084824"></a>
<table><thead align="left"><tr id="row757115127084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1015609073084824"><a name="p1015609073084824"></a><a name="p1015609073084824"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1696896542084824"><a name="p1696896542084824"></a><a name="p1696896542084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1294613292084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p350128936084824"><a name="p350128936084824"></a><a name="p350128936084824"></a><a href="fenv_t.md">fenv_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2056605391084824"><a name="p2056605391084824"></a><a name="p2056605391084824"></a>Defines the floating-point environment. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table506337585084824"></a>
<table><thead align="left"><tr id="row142695003084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p998293255084824"><a name="p998293255084824"></a><a name="p998293255084824"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p164929377084824"><a name="p164929377084824"></a><a name="p164929377084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1003501476084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p845823872084824"><a name="p845823872084824"></a><a name="p845823872084824"></a><em id="ga0fa4878c968311979d497ccc322e0b9b"><a name="ga0fa4878c968311979d497ccc322e0b9b"></a><a name="ga0fa4878c968311979d497ccc322e0b9b"></a></em>complex    _Complex</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p589860382084824"><a name="p589860382084824"></a><a name="p589860382084824"></a>Indicates the type of a complex number. </p>
</td>
</tr>
<tr id="row575903045084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826978257084824"><a name="p1826978257084824"></a><a name="p1826978257084824"></a><em id="ga638c8489adb1fac7204b07ece42998ae"><a name="ga638c8489adb1fac7204b07ece42998ae"></a><a name="ga638c8489adb1fac7204b07ece42998ae"></a></em>FE_INVALID    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492462355084824"><a name="p492462355084824"></a><a name="p492462355084824"></a>Indicates an invalid floating-point exception. At least one parameter value is not defined in the function. </p>
</td>
</tr>
<tr id="row428031018084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p944056134084824"><a name="p944056134084824"></a><a name="p944056134084824"></a><em id="gab1317930189d1a14841893fb4bd9b5a0"><a name="gab1317930189d1a14841893fb4bd9b5a0"></a><a name="gab1317930189d1a14841893fb4bd9b5a0"></a></em>FE_DIVBYZERO    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554045682084824"><a name="p1554045682084824"></a><a name="p1554045682084824"></a>Indicates a pole error exception. The return value is asymptotically infinite when the divisor is zero or the input is asymptotic to zero. </p>
</td>
</tr>
<tr id="row1280788235084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785678423084824"><a name="p785678423084824"></a><a name="p785678423084824"></a><em id="gad373306add36e7227d9c9620b6962323"><a name="gad373306add36e7227d9c9620b6962323"></a><a name="gad373306add36e7227d9c9620b6962323"></a></em>FE_OVERFLOW    4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772304658084824"><a name="p772304658084824"></a><a name="p772304658084824"></a>Indicates an overflow floating-point exception. The result is too large to be represented in the normal return value. </p>
</td>
</tr>
<tr id="row323472362084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2124518082084824"><a name="p2124518082084824"></a><a name="p2124518082084824"></a><em id="ga57b80dfe7d5ce60c3c76e517fce89ffe"><a name="ga57b80dfe7d5ce60c3c76e517fce89ffe"></a><a name="ga57b80dfe7d5ce60c3c76e517fce89ffe"></a></em>FE_UNDERFLOW    8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056131215084824"><a name="p1056131215084824"></a><a name="p1056131215084824"></a>Indicates an underflow floating-point exception. The result is too small to be represented in the normal return value. </p>
</td>
</tr>
<tr id="row1070487992084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1613949343084824"><a name="p1613949343084824"></a><a name="p1613949343084824"></a><em id="ga6e24165ff28571734b3e14530219faab"><a name="ga6e24165ff28571734b3e14530219faab"></a><a name="ga6e24165ff28571734b3e14530219faab"></a></em>FE_INEXACT    16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1862183410084824"><a name="p1862183410084824"></a><a name="p1862183410084824"></a>Indicates an inexact floating-point exception. </p>
</td>
</tr>
<tr id="row1464032551084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1804814596084824"><a name="p1804814596084824"></a><a name="p1804814596084824"></a><em id="ga09e405b3782b934813075e48366dda9a"><a name="ga09e405b3782b934813075e48366dda9a"></a><a name="ga09e405b3782b934813075e48366dda9a"></a></em>FE_ALL_EXCEPT    31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p500912722084824"><a name="p500912722084824"></a><a name="p500912722084824"></a>Indicates bitwise OR of all the preceding supported floating-point exceptions. </p>
</td>
</tr>
<tr id="row1856694347084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1255868144084824"><a name="p1255868144084824"></a><a name="p1255868144084824"></a><em id="ga5b5383719a63f98b7c95cc2feccaa1a7"><a name="ga5b5383719a63f98b7c95cc2feccaa1a7"></a><a name="ga5b5383719a63f98b7c95cc2feccaa1a7"></a></em>FE_TONEAREST    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1572703137084824"><a name="p1572703137084824"></a><a name="p1572703137084824"></a>Indicates rounding towards the nearest integer. </p>
</td>
</tr>
<tr id="row1859078786084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256684437084824"><a name="p256684437084824"></a><a name="p256684437084824"></a><em id="ga5e011a345a41ad4622da05932e83536f"><a name="ga5e011a345a41ad4622da05932e83536f"></a><a name="ga5e011a345a41ad4622da05932e83536f"></a></em>FE_DOWNWARD    0x800000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460270337084824"><a name="p1460270337084824"></a><a name="p1460270337084824"></a>Indicates rounding towards negative infinity. </p>
</td>
</tr>
<tr id="row1025232433084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33296156084824"><a name="p33296156084824"></a><a name="p33296156084824"></a><em id="ga5aa71a164a4b4d7780570d97058890f1"><a name="ga5aa71a164a4b4d7780570d97058890f1"></a><a name="ga5aa71a164a4b4d7780570d97058890f1"></a></em>FE_UPWARD    0x400000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1239725797084824"><a name="p1239725797084824"></a><a name="p1239725797084824"></a>Indicates rounding towards positive infinity. </p>
</td>
</tr>
<tr id="row1666994397084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p688173076084824"><a name="p688173076084824"></a><a name="p688173076084824"></a><em id="gac171099e006285a9e8be5683be71591c"><a name="gac171099e006285a9e8be5683be71591c"></a><a name="gac171099e006285a9e8be5683be71591c"></a></em>FE_TOWARDZERO    0xc00000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p901724925084824"><a name="p901724925084824"></a><a name="p901724925084824"></a>Indicates rounding towards zero. </p>
</td>
</tr>
<tr id="row1871444430084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659749856084824"><a name="p659749856084824"></a><a name="p659749856084824"></a><em id="ga5777a3689f7f4c555df1c643d28b5bc0"><a name="ga5777a3689f7f4c555df1c643d28b5bc0"></a><a name="ga5777a3689f7f4c555df1c643d28b5bc0"></a></em>FE_DFL_ENV    ((const <a href="fenv_t.md">fenv_t</a> *) -1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037676393084824"><a name="p1037676393084824"></a><a name="p1037676393084824"></a>Defines the default floating-point environment. </p>
</td>
</tr>
<tr id="row850831415084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p829836672084824"><a name="p829836672084824"></a><a name="p829836672084824"></a><em id="ga8abfcc76130f3f991d124dd22d7e69bc"><a name="ga8abfcc76130f3f991d124dd22d7e69bc"></a><a name="ga8abfcc76130f3f991d124dd22d7e69bc"></a></em>NAN    (0.0f/0.0f)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137626847084824"><a name="p2137626847084824"></a><a name="p2137626847084824"></a>Indicates an undefined or unrepresentable value. </p>
</td>
</tr>
<tr id="row2142916641084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908612707084824"><a name="p908612707084824"></a><a name="p908612707084824"></a><em id="ga956e2723d559858d08644ac99146e910"><a name="ga956e2723d559858d08644ac99146e910"></a><a name="ga956e2723d559858d08644ac99146e910"></a></em>INFINITY    1e5000f</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p713981262084824"><a name="p713981262084824"></a><a name="p713981262084824"></a>Indicates an infinity. </p>
</td>
</tr>
<tr id="row877635678084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1046343198084824"><a name="p1046343198084824"></a><a name="p1046343198084824"></a><em id="gacd69981d54c27fe0ff514645dbfc6359"><a name="gacd69981d54c27fe0ff514645dbfc6359"></a><a name="gacd69981d54c27fe0ff514645dbfc6359"></a></em>HUGE_VALF    <a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p421713626084824"><a name="p421713626084824"></a><a name="p421713626084824"></a>Indicates a float infinity. </p>
</td>
</tr>
<tr id="row701850266084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p347587316084824"><a name="p347587316084824"></a><a name="p347587316084824"></a><em id="gaf2164b2db92d8a0ed3838ad5c28db971"><a name="gaf2164b2db92d8a0ed3838ad5c28db971"></a><a name="gaf2164b2db92d8a0ed3838ad5c28db971"></a></em>HUGE_VAL    ((double)<a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238181518084824"><a name="p1238181518084824"></a><a name="p1238181518084824"></a>Indicates a double infinity. </p>
</td>
</tr>
<tr id="row23934904084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1950038769084824"><a name="p1950038769084824"></a><a name="p1950038769084824"></a><em id="gab8b359c356d4311bf5d4ae6c03f43182"><a name="gab8b359c356d4311bf5d4ae6c03f43182"></a><a name="gab8b359c356d4311bf5d4ae6c03f43182"></a></em>HUGE_VALL    ((long double)<a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832124765084824"><a name="p832124765084824"></a><a name="p832124765084824"></a>Indicates a long double infinity. </p>
</td>
</tr>
<tr id="row1362902894084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p139772605084824"><a name="p139772605084824"></a><a name="p139772605084824"></a><em id="ga42b212d215eab7142f8272fefcd1c938"><a name="ga42b212d215eab7142f8272fefcd1c938"></a><a name="ga42b212d215eab7142f8272fefcd1c938"></a></em>MATH_ERRNO    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1369412664084824"><a name="p1369412664084824"></a><a name="p1369412664084824"></a>Indicates an error that occurs in floating-point operations. </p>
</td>
</tr>
<tr id="row1575183529084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p142253037084824"><a name="p142253037084824"></a><a name="p142253037084824"></a><em id="gae05ce3fe3745507c8e989f6e9efe0a83"><a name="gae05ce3fe3745507c8e989f6e9efe0a83"></a><a name="gae05ce3fe3745507c8e989f6e9efe0a83"></a></em>MATH_ERREXCEPT    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728997416084824"><a name="p728997416084824"></a><a name="p728997416084824"></a>Indicates a floating-point exception. </p>
</td>
</tr>
<tr id="row1790833470084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2081810754084824"><a name="p2081810754084824"></a><a name="p2081810754084824"></a><em id="gaa8618aec27dedcd32f494ccf22f3ed42"><a name="gaa8618aec27dedcd32f494ccf22f3ed42"></a><a name="gaa8618aec27dedcd32f494ccf22f3ed42"></a></em>math_errhandling    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51114097084824"><a name="p51114097084824"></a><a name="p51114097084824"></a>Indicates the error handling mechanism employed by math functions. </p>
</td>
</tr>
<tr id="row251927204084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p970689066084824"><a name="p970689066084824"></a><a name="p970689066084824"></a><em id="ga01e2e5be97c739a5bdcbc619b44f9742"><a name="ga01e2e5be97c739a5bdcbc619b44f9742"></a><a name="ga01e2e5be97c739a5bdcbc619b44f9742"></a></em>FP_ILOGBNAN    (-1-0x7fffffff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007667840084824"><a name="p1007667840084824"></a><a name="p1007667840084824"></a>Indicates the calculation result of <a href="math.md#ga600dd249210d15af31b9a29c2d09d255">ilogb</a>(<a href="math.md#ga8abfcc76130f3f991d124dd22d7e69bc">NAN</a>). </p>
</td>
</tr>
<tr id="row1832177501084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1714011242084824"><a name="p1714011242084824"></a><a name="p1714011242084824"></a><em id="ga9ec0e31304d15c42262b2c4a3b58443c"><a name="ga9ec0e31304d15c42262b2c4a3b58443c"></a><a name="ga9ec0e31304d15c42262b2c4a3b58443c"></a></em>FP_ILOGB0    <a href="math.md#ga01e2e5be97c739a5bdcbc619b44f9742">FP_ILOGBNAN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1404311000084824"><a name="p1404311000084824"></a><a name="p1404311000084824"></a>Indicates the calculation result of <a href="math.md#ga600dd249210d15af31b9a29c2d09d255">ilogb</a>(0). </p>
</td>
</tr>
<tr id="row1653411609084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p656329684084824"><a name="p656329684084824"></a><a name="p656329684084824"></a><em id="ga1d481cc6e6a8ff729147ed46e61a4c9f"><a name="ga1d481cc6e6a8ff729147ed46e61a4c9f"></a><a name="ga1d481cc6e6a8ff729147ed46e61a4c9f"></a></em>FP_NAN    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2019564031084824"><a name="p2019564031084824"></a><a name="p2019564031084824"></a>Indicates a Not-a-Number (NaN) value. </p>
</td>
</tr>
<tr id="row185369705084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1404130131084824"><a name="p1404130131084824"></a><a name="p1404130131084824"></a><em id="ga4f64bcc64f8b84dd9daf5a4e56abf0ca"><a name="ga4f64bcc64f8b84dd9daf5a4e56abf0ca"></a><a name="ga4f64bcc64f8b84dd9daf5a4e56abf0ca"></a></em>FP_INFINITE    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1525979893084824"><a name="p1525979893084824"></a><a name="p1525979893084824"></a>Indicates an infinity. </p>
</td>
</tr>
<tr id="row842406346084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2089667086084824"><a name="p2089667086084824"></a><a name="p2089667086084824"></a><em id="ga32eba50da417c9f303ba49583d5b9f40"><a name="ga32eba50da417c9f303ba49583d5b9f40"></a><a name="ga32eba50da417c9f303ba49583d5b9f40"></a></em>FP_ZERO    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238710923084824"><a name="p238710923084824"></a><a name="p238710923084824"></a>Indicates value <strong id="b1501639260084824"><a name="b1501639260084824"></a><a name="b1501639260084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1979847572084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615654462084824"><a name="p1615654462084824"></a><a name="p1615654462084824"></a><em id="gadbc0a13ec75c05d238ca12ef1f8c6b2b"><a name="gadbc0a13ec75c05d238ca12ef1f8c6b2b"></a><a name="gadbc0a13ec75c05d238ca12ef1f8c6b2b"></a></em>FP_SUBNORMAL    3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779530448084824"><a name="p779530448084824"></a><a name="p779530448084824"></a>Indicates a subnormal. </p>
</td>
</tr>
<tr id="row161968205084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1610325260084824"><a name="p1610325260084824"></a><a name="p1610325260084824"></a><em id="gab9e29bb9e853934c4ba647c840b7e5de"><a name="gab9e29bb9e853934c4ba647c840b7e5de"></a><a name="gab9e29bb9e853934c4ba647c840b7e5de"></a></em>FP_NORMAL    4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323064108084824"><a name="p323064108084824"></a><a name="p323064108084824"></a>Indicates a normal value. </p>
</td>
</tr>
<tr id="row408108551084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p480276140084824"><a name="p480276140084824"></a><a name="p480276140084824"></a><a href="math.md#ga2a266c767456556e5c0da234b602b18b">isinf</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1117135437084824"><a name="p1117135437084824"></a><a name="p1117135437084824"></a>Checks whether the floating-point value <strong id="b1281159267084824"><a name="b1281159267084824"></a><a name="b1281159267084824"></a>x</strong> is an infinity. </p>
</td>
</tr>
<tr id="row1845196447084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1537408806084824"><a name="p1537408806084824"></a><a name="p1537408806084824"></a><a href="math.md#ga2e1baae9134e580910322362dc23290e">isnan</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p141029265084824"><a name="p141029265084824"></a><a name="p141029265084824"></a>Checks whether the floating-point value <strong id="b66226139084824"><a name="b66226139084824"></a><a name="b66226139084824"></a>x</strong> is a NaN value. </p>
</td>
</tr>
<tr id="row1503988046084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468050194084824"><a name="p468050194084824"></a><a name="p468050194084824"></a><a href="math.md#gad83f5949c4b5d810225b9a834840bac9">isnormal</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1581164378084824"><a name="p1581164378084824"></a><a name="p1581164378084824"></a>Checks whether the floating-point value <strong id="b947706299084824"><a name="b947706299084824"></a><a name="b947706299084824"></a>x</strong> is a normal value. </p>
</td>
</tr>
<tr id="row328974271084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p223167394084824"><a name="p223167394084824"></a><a name="p223167394084824"></a><a href="math.md#ga256d70a32c03904ce13c999c1e9dc35d">isfinite</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p360398242084824"><a name="p360398242084824"></a><a name="p360398242084824"></a>Checks whether the floating-point value <strong id="b1832174264084824"><a name="b1832174264084824"></a><a name="b1832174264084824"></a>x</strong> is finite. </p>
</td>
</tr>
<tr id="row70470771084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530553190084824"><a name="p530553190084824"></a><a name="p530553190084824"></a><a href="math.md#gaa63ffa98f213f62e536b073c28cb3cd8">signbit</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74481719084824"><a name="p74481719084824"></a><a name="p74481719084824"></a>Checks whether the sign of the floating-point value <strong id="b1023686820084824"><a name="b1023686820084824"></a><a name="b1023686820084824"></a>x</strong> is negative. </p>
</td>
</tr>
<tr id="row1765908687084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348959944084824"><a name="p348959944084824"></a><a name="p348959944084824"></a><a href="math.md#ga33daf51eb7138d477e0b0985c51e4fad">isunordered</a>(x, y)   (<a href="math.md#ga2e1baae9134e580910322362dc23290e">isnan</a>((x)) ? ((void)(y),1) : <a href="math.md#ga2e1baae9134e580910322362dc23290e">isnan</a>((y)))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p960102966084824"><a name="p960102966084824"></a><a name="p960102966084824"></a>Checks whether floating-point value <strong id="b1616485076084824"><a name="b1616485076084824"></a><a name="b1616485076084824"></a>x</strong> or <strong id="b1591514044084824"><a name="b1591514044084824"></a><a name="b1591514044084824"></a>y</strong> is unordered. </p>
</td>
</tr>
<tr id="row267477692084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049768384084824"><a name="p1049768384084824"></a><a name="p1049768384084824"></a><a href="math.md#ga61079b32084130da4345c2eea93e0d61">isless</a>(x, y)   __tg_pred_2(x, y, __isless)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521459724084824"><a name="p1521459724084824"></a><a name="p1521459724084824"></a>Checks whether floating-point value <strong id="b880530898084824"><a name="b880530898084824"></a><a name="b880530898084824"></a>x</strong> is less than <strong id="b848059264084824"><a name="b848059264084824"></a><a name="b848059264084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1023327911084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719428551084824"><a name="p719428551084824"></a><a name="p719428551084824"></a><a href="math.md#gabf3cb1e5a0aaa1c42dffa9ebb1d78c30">islessequal</a>(x, y)   __tg_pred_2(x, y, __islessequal)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45045425084824"><a name="p45045425084824"></a><a name="p45045425084824"></a>Checks whether floating-point value <strong id="b500469060084824"><a name="b500469060084824"></a><a name="b500469060084824"></a>x</strong> is less than or equal to <strong id="b808232422084824"><a name="b808232422084824"></a><a name="b808232422084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1728231663084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1722544092084824"><a name="p1722544092084824"></a><a name="p1722544092084824"></a><a href="math.md#ga5e534756b747fd2e9ee19f8fdd93b30b">islessgreater</a>(x, y)   __tg_pred_2(x, y, __islessgreater)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029516724084824"><a name="p1029516724084824"></a><a name="p1029516724084824"></a>Checks whether floating-point value <strong id="b242781583084824"><a name="b242781583084824"></a><a name="b242781583084824"></a>x</strong> is either less than or greater than <strong id="b1552360676084824"><a name="b1552360676084824"></a><a name="b1552360676084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1744131350084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522625278084824"><a name="p1522625278084824"></a><a name="p1522625278084824"></a><a href="math.md#gada788e9d6ce0ca927874ec4e53af1f77">isgreater</a>(x, y)   __tg_pred_2(x, y, __isgreater)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461504673084824"><a name="p1461504673084824"></a><a name="p1461504673084824"></a>Checks whether floating-point value <strong id="b1033546347084824"><a name="b1033546347084824"></a><a name="b1033546347084824"></a>x</strong> is greater than <strong id="b925478696084824"><a name="b925478696084824"></a><a name="b925478696084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row716638733084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1268519657084824"><a name="p1268519657084824"></a><a name="p1268519657084824"></a><a href="math.md#ga5a7f86a4d3e6139e4913e2e8eba52612">isgreaterequal</a>(x, y)   __tg_pred_2(x, y, __isgreaterequal)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1517441316084824"><a name="p1517441316084824"></a><a name="p1517441316084824"></a>Checks whether floating-point value <strong id="b1169697673084824"><a name="b1169697673084824"></a><a name="b1169697673084824"></a>x</strong> is greater than or equal to <strong id="b1551798615084824"><a name="b1551798615084824"></a><a name="b1551798615084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row202744172084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p211162022084824"><a name="p211162022084824"></a><a name="p211162022084824"></a><em id="ga5e9e29217f6ec61105a4520ec5942225"><a name="ga5e9e29217f6ec61105a4520ec5942225"></a><a name="ga5e9e29217f6ec61105a4520ec5942225"></a></em>MAXFLOAT    3.40282346638528859812e+38F</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033875016084824"><a name="p2033875016084824"></a><a name="p2033875016084824"></a>Maximum value of type float. </p>
</td>
</tr>
<tr id="row640444025084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597644705084824"><a name="p597644705084824"></a><a name="p597644705084824"></a><em id="ga9bf5d952c5c93c70f9e66c9794d406c9"><a name="ga9bf5d952c5c93c70f9e66c9794d406c9"></a><a name="ga9bf5d952c5c93c70f9e66c9794d406c9"></a></em>M_E    2.7182818284590452354 /* e */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1893699655084824"><a name="p1893699655084824"></a><a name="p1893699655084824"></a>Base e of natural logarithms. </p>
</td>
</tr>
<tr id="row1611802005084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1655550888084824"><a name="p1655550888084824"></a><a name="p1655550888084824"></a><em id="gac5c747ee5bcbe892875672a0b9d8171c"><a name="gac5c747ee5bcbe892875672a0b9d8171c"></a><a name="gac5c747ee5bcbe892875672a0b9d8171c"></a></em>M_LOG2E    1.4426950408889634074 /* log_2 e */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1380266763084824"><a name="p1380266763084824"></a><a name="p1380266763084824"></a>Logarithm to base 2 of <strong id="b1581135500084824"><a name="b1581135500084824"></a><a name="b1581135500084824"></a>M_E</strong> </p>
</td>
</tr>
<tr id="row1480926379084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737186305084824"><a name="p737186305084824"></a><a name="p737186305084824"></a><em id="ga9ed2b5582226f3896424ff6d2a3ebb14"><a name="ga9ed2b5582226f3896424ff6d2a3ebb14"></a><a name="ga9ed2b5582226f3896424ff6d2a3ebb14"></a></em>M_LOG10E    0.43429448190325182765 /* log_10 e */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p398080663084824"><a name="p398080663084824"></a><a name="p398080663084824"></a>Logarithm to base 10 of <strong id="b1846359830084824"><a name="b1846359830084824"></a><a name="b1846359830084824"></a>M_E</strong> </p>
</td>
</tr>
<tr id="row104879533084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290601832084824"><a name="p1290601832084824"></a><a name="p1290601832084824"></a><em id="ga92428112a5d24721208748774a4f23e6"><a name="ga92428112a5d24721208748774a4f23e6"></a><a name="ga92428112a5d24721208748774a4f23e6"></a></em>M_LN2    0.69314718055994530942 /* log_e 2 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p840371854084824"><a name="p840371854084824"></a><a name="p840371854084824"></a>Natural logarithm of <strong id="b2024861784084824"><a name="b2024861784084824"></a><a name="b2024861784084824"></a>2</strong> </p>
</td>
</tr>
<tr id="row1172481159084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492859380084824"><a name="p1492859380084824"></a><a name="p1492859380084824"></a><em id="ga0a53871497a155afe91424c28a8ec3c4"><a name="ga0a53871497a155afe91424c28a8ec3c4"></a><a name="ga0a53871497a155afe91424c28a8ec3c4"></a></em>M_LN10    2.30258509299404568402 /* log_e 10 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1854961753084824"><a name="p1854961753084824"></a><a name="p1854961753084824"></a>Natural logarithm of <strong id="b214754690084824"><a name="b214754690084824"></a><a name="b214754690084824"></a>10</strong> </p>
</td>
</tr>
<tr id="row1194378267084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328371545084824"><a name="p328371545084824"></a><a name="p328371545084824"></a><em id="gae71449b1cc6e6250b91f539153a7a0d3"><a name="gae71449b1cc6e6250b91f539153a7a0d3"></a><a name="gae71449b1cc6e6250b91f539153a7a0d3"></a></em>M_PI    3.14159265358979323846 /* pi */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174565089084824"><a name="p174565089084824"></a><a name="p174565089084824"></a>Ratio of a circle's circumference to its diameter. </p>
</td>
</tr>
<tr id="row1126259190084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960568893084824"><a name="p960568893084824"></a><a name="p960568893084824"></a><em id="ga958e4508ed28ee5cc04249144312c15f"><a name="ga958e4508ed28ee5cc04249144312c15f"></a><a name="ga958e4508ed28ee5cc04249144312c15f"></a></em>M_PI_2    1.57079632679489661923 /* pi/2 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129956248084824"><a name="p129956248084824"></a><a name="p129956248084824"></a>Pi divided by <strong id="b1981177143084824"><a name="b1981177143084824"></a><a name="b1981177143084824"></a>2</strong> </p>
</td>
</tr>
<tr id="row170160931084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p104229223084824"><a name="p104229223084824"></a><a name="p104229223084824"></a><em id="gaeb24420b096a677f3a2dc5a72b36bf22"><a name="gaeb24420b096a677f3a2dc5a72b36bf22"></a><a name="gaeb24420b096a677f3a2dc5a72b36bf22"></a></em>M_PI_4    0.78539816339744830962 /* pi/4 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p95198333084824"><a name="p95198333084824"></a><a name="p95198333084824"></a>Pi divided by <strong id="b178882523084824"><a name="b178882523084824"></a><a name="b178882523084824"></a>4</strong> </p>
</td>
</tr>
<tr id="row2129393898084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1903116805084824"><a name="p1903116805084824"></a><a name="p1903116805084824"></a><em id="ga08dfac3cca9601a02fc88356cc078e1d"><a name="ga08dfac3cca9601a02fc88356cc078e1d"></a><a name="ga08dfac3cca9601a02fc88356cc078e1d"></a></em>M_1_PI    0.31830988618379067154 /* 1/pi */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1804873441084824"><a name="p1804873441084824"></a><a name="p1804873441084824"></a>Reciprocal of pi. </p>
</td>
</tr>
<tr id="row643727011084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222973174084824"><a name="p222973174084824"></a><a name="p222973174084824"></a><em id="ga97f6d6514d3d3dd50c3a2a6d622673db"><a name="ga97f6d6514d3d3dd50c3a2a6d622673db"></a><a name="ga97f6d6514d3d3dd50c3a2a6d622673db"></a></em>M_2_PI    0.63661977236758134308 /* 2/pi */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1352853504084824"><a name="p1352853504084824"></a><a name="p1352853504084824"></a>Two times the reciprocal of pi. </p>
</td>
</tr>
<tr id="row1930468555084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p975972536084824"><a name="p975972536084824"></a><a name="p975972536084824"></a><em id="ga631ff334c4a1a6db2e8a7ff4acbe48a5"><a name="ga631ff334c4a1a6db2e8a7ff4acbe48a5"></a><a name="ga631ff334c4a1a6db2e8a7ff4acbe48a5"></a></em>M_2_SQRTPI    1.12837916709551257390 /* 2/<a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a>(pi) */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p605923006084824"><a name="p605923006084824"></a><a name="p605923006084824"></a>Two times the reciprocal of the square root of pi. </p>
</td>
</tr>
<tr id="row59748057084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748069776084824"><a name="p1748069776084824"></a><a name="p1748069776084824"></a><em id="ga66b3ab30f1332874326ed93969e496e0"><a name="ga66b3ab30f1332874326ed93969e496e0"></a><a name="ga66b3ab30f1332874326ed93969e496e0"></a></em>M_SQRT2    1.41421356237309504880 /* <a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a>(2) */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844874392084824"><a name="p1844874392084824"></a><a name="p1844874392084824"></a>Square root of <strong id="b1049569124084824"><a name="b1049569124084824"></a><a name="b1049569124084824"></a>2</strong> </p>
</td>
</tr>
<tr id="row99709729084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p354123094084824"><a name="p354123094084824"></a><a name="p354123094084824"></a><em id="gacdbb2c2f9429f08916f03c8786d2d2d7"><a name="gacdbb2c2f9429f08916f03c8786d2d2d7"></a><a name="gacdbb2c2f9429f08916f03c8786d2d2d7"></a></em>M_SQRT1_2    0.70710678118654752440 /* 1/<a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a>(2) */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p158281258084824"><a name="p158281258084824"></a><a name="p158281258084824"></a>Reciprocal of the square root of <strong id="b1051301159084824"><a name="b1051301159084824"></a><a name="b1051301159084824"></a>2</strong> </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1892381128084824"></a>
<table><thead align="left"><tr id="row791765944084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p525897532084824"><a name="p525897532084824"></a><a name="p525897532084824"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p214218930084824"><a name="p214218930084824"></a><a name="p214218930084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row931335993084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049500096084824"><a name="p1049500096084824"></a><a name="p1049500096084824"></a><em id="ga3eec78fdb9921de3f7254105f546c624"><a name="ga3eec78fdb9921de3f7254105f546c624"></a><a name="ga3eec78fdb9921de3f7254105f546c624"></a></em>fexcept_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576005467084824"><a name="p1576005467084824"></a><a name="p1576005467084824"></a><strong id="b1334977434"><a name="b1334977434"></a><a name="b1334977434"></a></strong> typedef unsigned long </p>
<p id="p1165015144084824"><a name="p1165015144084824"></a><a name="p1165015144084824"></a>Floating-point exception type. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1695885382084824"></a>
<table><thead align="left"><tr id="row542721201084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1639779523084824"><a name="p1639779523084824"></a><a name="p1639779523084824"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p744742895084824"><a name="p744742895084824"></a><a name="p744742895084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2048057964084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1703802480084824"><a name="p1703802480084824"></a><a name="p1703802480084824"></a><a href="math.md#ga51a9bcdc7791e50f879c79d64362d7c3">cacos</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1969992095084824"><a name="p1969992095084824"></a><a name="p1969992095084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p328725567084824"><a name="p328725567084824"></a><a name="p328725567084824"></a>Calculates the arc cosine of the complex number <strong id="b1759605000084824"><a name="b1759605000084824"></a><a name="b1759605000084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1794538691084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p757202388084824"><a name="p757202388084824"></a><a name="p757202388084824"></a><a href="math.md#ga238bc3dbd59adeb477af18c9a501e04e">cacosf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993659043084824"><a name="p993659043084824"></a><a name="p993659043084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p329539371084824"><a name="p329539371084824"></a><a name="p329539371084824"></a>Calculates the arc cosine of the complex number <strong id="b1688415334084824"><a name="b1688415334084824"></a><a name="b1688415334084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1791675655084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076885549084824"><a name="p2076885549084824"></a><a name="p2076885549084824"></a><a href="math.md#ga789143f2859142f58590b2726328025f">cacosl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p709805029084824"><a name="p709805029084824"></a><a name="p709805029084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1761433462084824"><a name="p1761433462084824"></a><a name="p1761433462084824"></a>Calculates the arc cosine of the complex number <strong id="b664289240084824"><a name="b664289240084824"></a><a name="b664289240084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row17599623084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697350646084824"><a name="p697350646084824"></a><a name="p697350646084824"></a><a href="math.md#gac43774f89411806a3e0695012cdb7f38">casin</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856508515084824"><a name="p856508515084824"></a><a name="p856508515084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1922672218084824"><a name="p1922672218084824"></a><a name="p1922672218084824"></a>Calculates the arc sine of the complex number <strong id="b1479805095084824"><a name="b1479805095084824"></a><a name="b1479805095084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row834508373084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615607323084824"><a name="p1615607323084824"></a><a name="p1615607323084824"></a><a href="math.md#ga04d2cd1f0b47d3f1b782aeb517151033">casinf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1188437087084824"><a name="p1188437087084824"></a><a name="p1188437087084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1557984301084824"><a name="p1557984301084824"></a><a name="p1557984301084824"></a>Calculates the arc sine of the complex number <strong id="b682133081084824"><a name="b682133081084824"></a><a name="b682133081084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row326629005084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p733549206084824"><a name="p733549206084824"></a><a name="p733549206084824"></a><a href="math.md#ga8770350a79904ac151ebb3eebd736188">casinl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p190748078084824"><a name="p190748078084824"></a><a name="p190748078084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p100798335084824"><a name="p100798335084824"></a><a name="p100798335084824"></a>Calculates the arc sine of the complex number <strong id="b349751274084824"><a name="b349751274084824"></a><a name="b349751274084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1802451981084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p909201982084824"><a name="p909201982084824"></a><a name="p909201982084824"></a><a href="math.md#ga1a77a3240b834af81a23b38f2af6c93d">catan</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909317083084824"><a name="p909317083084824"></a><a name="p909317083084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p302659791084824"><a name="p302659791084824"></a><a name="p302659791084824"></a>Calculates the arc tangent of the complex number <strong id="b2102326610084824"><a name="b2102326610084824"></a><a name="b2102326610084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1794853815084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1350921445084824"><a name="p1350921445084824"></a><a name="p1350921445084824"></a><a href="math.md#ga4d0beef9b3994887e356c6b5c98388d9">catanf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1848309182084824"><a name="p1848309182084824"></a><a name="p1848309182084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p285222507084824"><a name="p285222507084824"></a><a name="p285222507084824"></a>Calculates the arc tangent of the complex number <strong id="b1164075878084824"><a name="b1164075878084824"></a><a name="b1164075878084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row337391697084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330204672084824"><a name="p1330204672084824"></a><a name="p1330204672084824"></a><a href="math.md#gaf28ad2f006e49eaa6bbdb97dd143d6cb">catanl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798100123084824"><a name="p798100123084824"></a><a name="p798100123084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p933165891084824"><a name="p933165891084824"></a><a name="p933165891084824"></a>Calculates the arc tangent of the complex number <strong id="b1665821989084824"><a name="b1665821989084824"></a><a name="b1665821989084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1635635367084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p337599218084824"><a name="p337599218084824"></a><a name="p337599218084824"></a><a href="math.md#ga6a25bcd38751910533efde6dad1499c3">ccos</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405245164084824"><a name="p405245164084824"></a><a name="p405245164084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p738760245084824"><a name="p738760245084824"></a><a name="p738760245084824"></a>Calculates the cosine of the complex number <strong id="b1960609782084824"><a name="b1960609782084824"></a><a name="b1960609782084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row992233454084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1832105350084824"><a name="p1832105350084824"></a><a name="p1832105350084824"></a><a href="math.md#ga88df5eebfb10b88ed37e444f5b13fd6a">ccosf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p836659289084824"><a name="p836659289084824"></a><a name="p836659289084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1352129812084824"><a name="p1352129812084824"></a><a name="p1352129812084824"></a>Calculates the cosine of the complex number <strong id="b1926716126084824"><a name="b1926716126084824"></a><a name="b1926716126084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row305386028084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p398816209084824"><a name="p398816209084824"></a><a name="p398816209084824"></a><a href="math.md#ga785d8c7b2ac4283d4759dfa6a86779ab">ccosl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2020271979084824"><a name="p2020271979084824"></a><a name="p2020271979084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1462145987084824"><a name="p1462145987084824"></a><a name="p1462145987084824"></a>Calculates the cosine of the complex number <strong id="b1691383029084824"><a name="b1691383029084824"></a><a name="b1691383029084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1928555323084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1786600730084824"><a name="p1786600730084824"></a><a name="p1786600730084824"></a><a href="math.md#ga1b9030685d326e66a93a35ca8c4bb0f6">csin</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p350451017084824"><a name="p350451017084824"></a><a name="p350451017084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p412504822084824"><a name="p412504822084824"></a><a name="p412504822084824"></a>Calculates the sine of the complex number <strong id="b674980009084824"><a name="b674980009084824"></a><a name="b674980009084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row978941962084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871872914084824"><a name="p871872914084824"></a><a name="p871872914084824"></a><a href="math.md#ga76dc89521e12096bc2104c9c0dcc20ea">csinf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003179650084824"><a name="p1003179650084824"></a><a name="p1003179650084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1754794070084824"><a name="p1754794070084824"></a><a name="p1754794070084824"></a>Calculates the sine of the complex number <strong id="b1100733664084824"><a name="b1100733664084824"></a><a name="b1100733664084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1301099368084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651420089084824"><a name="p651420089084824"></a><a name="p651420089084824"></a><a href="math.md#gad594fa6071ea5d383a0c7abaa0c32d80">csinl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1664856712084824"><a name="p1664856712084824"></a><a name="p1664856712084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p536248129084824"><a name="p536248129084824"></a><a name="p536248129084824"></a>Calculates the sine of the complex number <strong id="b552736603084824"><a name="b552736603084824"></a><a name="b552736603084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row2027502902084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871730263084824"><a name="p871730263084824"></a><a name="p871730263084824"></a><a href="math.md#ga665b5dfc1b1f51d3b444f049c6bd95dd">ctan</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787077547084824"><a name="p1787077547084824"></a><a name="p1787077547084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1591227496084824"><a name="p1591227496084824"></a><a name="p1591227496084824"></a>Calculates the tangent of the complex number <strong id="b1815886633084824"><a name="b1815886633084824"></a><a name="b1815886633084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1435098115084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1243567195084824"><a name="p1243567195084824"></a><a name="p1243567195084824"></a><a href="math.md#ga4301d608cc419f1ba3177fae4f258f30">ctanf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1233822526084824"><a name="p1233822526084824"></a><a name="p1233822526084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1368626876084824"><a name="p1368626876084824"></a><a name="p1368626876084824"></a>Calculates the tangent of the complex number <strong id="b266600159084824"><a name="b266600159084824"></a><a name="b266600159084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row182294739084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p673211074084824"><a name="p673211074084824"></a><a name="p673211074084824"></a><a href="math.md#ga7aa0362acd67521c9aac791aa617f953">ctanl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1372017456084824"><a name="p1372017456084824"></a><a name="p1372017456084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1228553472084824"><a name="p1228553472084824"></a><a name="p1228553472084824"></a>Calculates the tangent of the complex number <strong id="b1871617806084824"><a name="b1871617806084824"></a><a name="b1871617806084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1083016330084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1519582691084824"><a name="p1519582691084824"></a><a name="p1519582691084824"></a><a href="math.md#gaf7286142554fde4ba6316a2b64b96c5c">cacosh</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622875088084824"><a name="p1622875088084824"></a><a name="p1622875088084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1107464057084824"><a name="p1107464057084824"></a><a name="p1107464057084824"></a>Calculates the inverse hyperbolic cosine of the complex number <strong id="b582563316084824"><a name="b582563316084824"></a><a name="b582563316084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1053668964084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1485009266084824"><a name="p1485009266084824"></a><a name="p1485009266084824"></a><a href="math.md#gabe9dbe34293eef409598b0559435c5ff">cacoshf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p513717858084824"><a name="p513717858084824"></a><a name="p513717858084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p772401834084824"><a name="p772401834084824"></a><a name="p772401834084824"></a>Calculates the inverse hyperbolic cosine of the complex number <strong id="b418128081084824"><a name="b418128081084824"></a><a name="b418128081084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row838855371084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1706425528084824"><a name="p1706425528084824"></a><a name="p1706425528084824"></a><a href="math.md#gad8e03bbb434b8a9af73e0e3daec045ac">cacoshl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p270480084824"><a name="p270480084824"></a><a name="p270480084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p729042562084824"><a name="p729042562084824"></a><a name="p729042562084824"></a>Calculates the inverse hyperbolic cosine of the complex number <strong id="b1322294457084824"><a name="b1322294457084824"></a><a name="b1322294457084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row998362072084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222391908084824"><a name="p222391908084824"></a><a name="p222391908084824"></a><a href="math.md#ga6fc1a0c1cbac62ba63e799d7e8f488e0">casinh</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124248157084824"><a name="p1124248157084824"></a><a name="p1124248157084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1927581660084824"><a name="p1927581660084824"></a><a name="p1927581660084824"></a>Calculates the inverse hyperbolic sine of the complex number <strong id="b780141950084824"><a name="b780141950084824"></a><a name="b780141950084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row540185618084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2113631516084824"><a name="p2113631516084824"></a><a name="p2113631516084824"></a><a href="math.md#ga8b682e1c311efa5594ec0d0b39c9efe0">casinhf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356713113084824"><a name="p356713113084824"></a><a name="p356713113084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p6598093084824"><a name="p6598093084824"></a><a name="p6598093084824"></a>Calculates the inverse hyperbolic sine of the complex number <strong id="b357202125084824"><a name="b357202125084824"></a><a name="b357202125084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1227333943084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1233257972084824"><a name="p1233257972084824"></a><a name="p1233257972084824"></a><a href="math.md#ga174b8f2a00e771dbbad06fdf0e0ee449">casinhl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1126437789084824"><a name="p1126437789084824"></a><a name="p1126437789084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p660097343084824"><a name="p660097343084824"></a><a name="p660097343084824"></a>Calculates the inverse hyperbolic sine of the complex number <strong id="b1485602939084824"><a name="b1485602939084824"></a><a name="b1485602939084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row860401269084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702782931084824"><a name="p702782931084824"></a><a name="p702782931084824"></a><a href="math.md#ga376fef7890def8c0e7b2b5a5292be074">catanh</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p855624555084824"><a name="p855624555084824"></a><a name="p855624555084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p520537950084824"><a name="p520537950084824"></a><a name="p520537950084824"></a>Calculates the inverse hyperbolic tangent of the complex number <strong id="b489562414084824"><a name="b489562414084824"></a><a name="b489562414084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row539806376084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529345425084824"><a name="p529345425084824"></a><a name="p529345425084824"></a><a href="math.md#ga480c29e0eeace893be77a2c61995d2ec">catanhf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018651376084824"><a name="p2018651376084824"></a><a name="p2018651376084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p643091941084824"><a name="p643091941084824"></a><a name="p643091941084824"></a>Calculates the inverse hyperbolic tangent of the complex number <strong id="b1868423204084824"><a name="b1868423204084824"></a><a name="b1868423204084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row8457371084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175704385084824"><a name="p175704385084824"></a><a name="p175704385084824"></a><a href="math.md#gab2422355124f175a41ec092c3b8adf2b">catanhl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1387493237084824"><a name="p1387493237084824"></a><a name="p1387493237084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1156693149084824"><a name="p1156693149084824"></a><a name="p1156693149084824"></a>Calculates the inverse hyperbolic tangent of the complex number <strong id="b413936222084824"><a name="b413936222084824"></a><a name="b413936222084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1549244995084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1233313511084824"><a name="p1233313511084824"></a><a name="p1233313511084824"></a><a href="math.md#ga62c8f7e0cce95bbf670af16376909324">ccosh</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1377331448084824"><a name="p1377331448084824"></a><a name="p1377331448084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1124520660084824"><a name="p1124520660084824"></a><a name="p1124520660084824"></a>Calculates the hyperbolic cosine of the complex number <strong id="b568097595084824"><a name="b568097595084824"></a><a name="b568097595084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1604974440084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637906387084824"><a name="p637906387084824"></a><a name="p637906387084824"></a><a href="math.md#gabe11c35bd81b278ab0e47196c5952662">ccoshf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058432500084824"><a name="p1058432500084824"></a><a name="p1058432500084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p750748620084824"><a name="p750748620084824"></a><a name="p750748620084824"></a>Calculates the hyperbolic cosine of the complex number <strong id="b903126936084824"><a name="b903126936084824"></a><a name="b903126936084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row880940781084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1359033563084824"><a name="p1359033563084824"></a><a name="p1359033563084824"></a><a href="math.md#gad2b7878b871c0266ecb1f58e5bf141a7">ccoshl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910332317084824"><a name="p1910332317084824"></a><a name="p1910332317084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p390077338084824"><a name="p390077338084824"></a><a name="p390077338084824"></a>Calculates the hyperbolic cosine of the complex number <strong id="b1169484031084824"><a name="b1169484031084824"></a><a name="b1169484031084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row525078576084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p296229869084824"><a name="p296229869084824"></a><a name="p296229869084824"></a><a href="math.md#ga0c782aa9258a4e11cc3ea57b2dcccfef">csinh</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p10970024084824"><a name="p10970024084824"></a><a name="p10970024084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p631149984084824"><a name="p631149984084824"></a><a name="p631149984084824"></a>Calculates the hyperbolic sine of the complex number <strong id="b1534515970084824"><a name="b1534515970084824"></a><a name="b1534515970084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row631344834084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952431058084824"><a name="p952431058084824"></a><a name="p952431058084824"></a><a href="math.md#ga268ba13d67a10e6667bd6b64a1a96351">csinhf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135748021084824"><a name="p135748021084824"></a><a name="p135748021084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p89330488084824"><a name="p89330488084824"></a><a name="p89330488084824"></a>Calculates the hyperbolic sine of the complex number <strong id="b192271322084824"><a name="b192271322084824"></a><a name="b192271322084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row573195781084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726473079084824"><a name="p726473079084824"></a><a name="p726473079084824"></a><a href="math.md#ga0d14ae39cd9a811e42e36512fe6c7e53">csinhl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061877521084824"><a name="p2061877521084824"></a><a name="p2061877521084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p860643005084824"><a name="p860643005084824"></a><a name="p860643005084824"></a>Calculates the hyperbolic sine of the complex number <strong id="b943098526084824"><a name="b943098526084824"></a><a name="b943098526084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1379260511084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761256513084824"><a name="p1761256513084824"></a><a name="p1761256513084824"></a><a href="math.md#ga9c5cf378e654f3aaed9fb0f5c8223585">ctanh</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p984238170084824"><a name="p984238170084824"></a><a name="p984238170084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1839088395084824"><a name="p1839088395084824"></a><a name="p1839088395084824"></a>Calculates the hyperbolic tangent of the complex number <strong id="b959012791084824"><a name="b959012791084824"></a><a name="b959012791084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1374225449084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755654371084824"><a name="p1755654371084824"></a><a name="p1755654371084824"></a><a href="math.md#gad68db7f429f2104acf52b096c5efb69a">ctanhf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p819602516084824"><a name="p819602516084824"></a><a name="p819602516084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p18672339084824"><a name="p18672339084824"></a><a name="p18672339084824"></a>Calculates the hyperbolic tangent of the complex number <strong id="b248954607084824"><a name="b248954607084824"></a><a name="b248954607084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row333032960084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363896047084824"><a name="p1363896047084824"></a><a name="p1363896047084824"></a><a href="math.md#ga2fbb0a9d578343f924c96faed3189805">ctanhl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p381104883084824"><a name="p381104883084824"></a><a name="p381104883084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1367769183084824"><a name="p1367769183084824"></a><a name="p1367769183084824"></a>Calculates the hyperbolic tangent of the complex number <strong id="b532008411084824"><a name="b532008411084824"></a><a name="b532008411084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row709852946084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p596654152084824"><a name="p596654152084824"></a><a name="p596654152084824"></a><a href="math.md#gab9c654c52efefb54d06d52aa1a1c1827">cexp</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947705729084824"><a name="p1947705729084824"></a><a name="p1947705729084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p2016611152084824"><a name="p2016611152084824"></a><a name="p2016611152084824"></a>Calculates the base-e exponential of the complex number <strong id="b1448296647084824"><a name="b1448296647084824"></a><a name="b1448296647084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1472667803084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315417143084824"><a name="p1315417143084824"></a><a name="p1315417143084824"></a><a href="math.md#ga8628a449a00228f124c9e53d2236611f">cexpf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519327586084824"><a name="p519327586084824"></a><a name="p519327586084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p76248529084824"><a name="p76248529084824"></a><a name="p76248529084824"></a>Calculates the base-e exponential of the complex number <strong id="b724932090084824"><a name="b724932090084824"></a><a name="b724932090084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1758308155084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1660646006084824"><a name="p1660646006084824"></a><a name="p1660646006084824"></a><a href="math.md#ga31a965fe1790cace431516e53f7d0cb5">cexpl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194937272084824"><a name="p194937272084824"></a><a name="p194937272084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1586345461084824"><a name="p1586345461084824"></a><a name="p1586345461084824"></a>Calculates the base-e exponential of the complex number <strong id="b1325336035084824"><a name="b1325336035084824"></a><a name="b1325336035084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1865034702084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160730273084824"><a name="p160730273084824"></a><a name="p160730273084824"></a><a href="math.md#gaa39c3557d8db10c19571bc0b63fd5529">clog</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870487017084824"><a name="p1870487017084824"></a><a name="p1870487017084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p667233031084824"><a name="p667233031084824"></a><a name="p667233031084824"></a>Calculates the natural (base-e) logarithm of the complex number <strong id="b335757565084824"><a name="b335757565084824"></a><a name="b335757565084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row180166084084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1022313059084824"><a name="p1022313059084824"></a><a name="p1022313059084824"></a><a href="math.md#ga0c9f343c7d1dabc91f6e4cb868b81152">clogf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1897492292084824"><a name="p1897492292084824"></a><a name="p1897492292084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1673892234084824"><a name="p1673892234084824"></a><a name="p1673892234084824"></a>Calculates the natural (base-e) logarithm of the complex number <strong id="b1251674513084824"><a name="b1251674513084824"></a><a name="b1251674513084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1879201533084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1417174374084824"><a name="p1417174374084824"></a><a name="p1417174374084824"></a><a href="math.md#ga48efe0bf63314044fafaeb32623fff17">clogl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1419405662084824"><a name="p1419405662084824"></a><a name="p1419405662084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p694671551084824"><a name="p694671551084824"></a><a name="p694671551084824"></a>Calculates the natural (base-e) logarithm of the complex number <strong id="b121061180084824"><a name="b121061180084824"></a><a name="b121061180084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row251064840084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1515519868084824"><a name="p1515519868084824"></a><a name="p1515519868084824"></a><a href="math.md#ga82c65f6b05062b620716623ba49ff07f">cabs</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1741339909084824"><a name="p1741339909084824"></a><a name="p1741339909084824"></a>double </p>
<p id="p2122981179084824"><a name="p2122981179084824"></a><a name="p2122981179084824"></a>Calculates the absolute value of the complex number <strong id="b199496516084824"><a name="b199496516084824"></a><a name="b199496516084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row809023024084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p227897292084824"><a name="p227897292084824"></a><a name="p227897292084824"></a><a href="math.md#ga59a1f4977dfdf85b51a84bfd56737277">cabsf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648281571084824"><a name="p648281571084824"></a><a name="p648281571084824"></a>float </p>
<p id="p554233026084824"><a name="p554233026084824"></a><a name="p554233026084824"></a>Calculates the absolute value of the complex number <strong id="b1575194465084824"><a name="b1575194465084824"></a><a name="b1575194465084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row614737674084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835008175084824"><a name="p835008175084824"></a><a name="p835008175084824"></a><a href="math.md#ga7e37259e24f3384f376e4d3eb45a9ea8">cabsl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165343933084824"><a name="p1165343933084824"></a><a name="p1165343933084824"></a>long double </p>
<p id="p1867618869084824"><a name="p1867618869084824"></a><a name="p1867618869084824"></a>Calculates the absolute value of the complex number <strong id="b1010882398084824"><a name="b1010882398084824"></a><a name="b1010882398084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1697045248084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237209838084824"><a name="p1237209838084824"></a><a name="p1237209838084824"></a><a href="math.md#ga6fd1bd16c6de991f95a4e19e0f2f2a12">cpow</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> x, double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1559869110084824"><a name="p1559869110084824"></a><a name="p1559869110084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p240828527084824"><a name="p240828527084824"></a><a name="p240828527084824"></a>Calculates the value of <strong id="b493045823084824"><a name="b493045823084824"></a><a name="b493045823084824"></a>x</strong> raised to the <strong id="b1010484910084824"><a name="b1010484910084824"></a><a name="b1010484910084824"></a>z</strong> power. </p>
</td>
</tr>
<tr id="row1817763635084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207835314084824"><a name="p1207835314084824"></a><a name="p1207835314084824"></a><a href="math.md#ga58beb4a3ea7b6ab6bb942900f94179fa">cpowf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> x, float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059847500084824"><a name="p1059847500084824"></a><a name="p1059847500084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1107500063084824"><a name="p1107500063084824"></a><a name="p1107500063084824"></a>Calculates the value of <strong id="b2093255137084824"><a name="b2093255137084824"></a><a name="b2093255137084824"></a>x</strong> raised to the <strong id="b664287189084824"><a name="b664287189084824"></a><a name="b664287189084824"></a>z</strong> power. </p>
</td>
</tr>
<tr id="row1837209842084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p770094383084824"><a name="p770094383084824"></a><a name="p770094383084824"></a><a href="math.md#gae3ae7292dac86eeec3bb9a06b66f61cb">cpowl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> x, long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931300569084824"><a name="p931300569084824"></a><a name="p931300569084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p145930391084824"><a name="p145930391084824"></a><a name="p145930391084824"></a>Calculates the value of <strong id="b522383288084824"><a name="b522383288084824"></a><a name="b522383288084824"></a>x</strong> raised to the <strong id="b144497948084824"><a name="b144497948084824"></a><a name="b144497948084824"></a>z</strong> power. </p>
</td>
</tr>
<tr id="row1175657075084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1971031413084824"><a name="p1971031413084824"></a><a name="p1971031413084824"></a><a href="math.md#ga7ff172d72bc0474b93e27470ce94494b">csqrt</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p802626495084824"><a name="p802626495084824"></a><a name="p802626495084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1643752144084824"><a name="p1643752144084824"></a><a name="p1643752144084824"></a>Calculates the square root of the complex number <strong id="b33918908084824"><a name="b33918908084824"></a><a name="b33918908084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1670103325084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044240871084824"><a name="p2044240871084824"></a><a name="p2044240871084824"></a><a href="math.md#gab8e425ba3e5d52d410afc3041bdeadce">csqrtf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1908329627084824"><a name="p1908329627084824"></a><a name="p1908329627084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1294137028084824"><a name="p1294137028084824"></a><a name="p1294137028084824"></a>Calculates the square root of the complex number <strong id="b1473209779084824"><a name="b1473209779084824"></a><a name="b1473209779084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row352242838084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p12296371084824"><a name="p12296371084824"></a><a name="p12296371084824"></a><a href="math.md#ga94a429c220e400a1a6781d6e11cbfafd">csqrtl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974872694084824"><a name="p1974872694084824"></a><a name="p1974872694084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p682841857084824"><a name="p682841857084824"></a><a name="p682841857084824"></a>Calculates the square root of the complex number <strong id="b1109751863084824"><a name="b1109751863084824"></a><a name="b1109751863084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1824819220084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p135549840084824"><a name="p135549840084824"></a><a name="p135549840084824"></a><a href="math.md#ga4a1e5d839db7a1dc6013b2846b2432d9">carg</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1111404419084824"><a name="p1111404419084824"></a><a name="p1111404419084824"></a>double </p>
<p id="p1969848581084824"><a name="p1969848581084824"></a><a name="p1969848581084824"></a>Calculates the phase angle of the complex number <strong id="b1529089281084824"><a name="b1529089281084824"></a><a name="b1529089281084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row823201392084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271062223084824"><a name="p271062223084824"></a><a name="p271062223084824"></a><a href="math.md#ga66334f398567baa3648cd3111ed68d3b">cargf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695110379084824"><a name="p1695110379084824"></a><a name="p1695110379084824"></a>float </p>
<p id="p2042444548084824"><a name="p2042444548084824"></a><a name="p2042444548084824"></a>Calculates the phase angle of the complex number <strong id="b43119176084824"><a name="b43119176084824"></a><a name="b43119176084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1824359120084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1226522905084824"><a name="p1226522905084824"></a><a name="p1226522905084824"></a><a href="math.md#ga74f3429f1b860581f4d15bea90533fd5">cargl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2076766512084824"><a name="p2076766512084824"></a><a name="p2076766512084824"></a>long double </p>
<p id="p1959962777084824"><a name="p1959962777084824"></a><a name="p1959962777084824"></a>Calculates the phase angle of the complex number <strong id="b924977196084824"><a name="b924977196084824"></a><a name="b924977196084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row569000917084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906137019084824"><a name="p1906137019084824"></a><a name="p1906137019084824"></a><a href="math.md#ga6c3d7c875ae93700b0a2a32db24b37d3">cimag</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1236752669084824"><a name="p1236752669084824"></a><a name="p1236752669084824"></a>double </p>
<p id="p1673059554084824"><a name="p1673059554084824"></a><a name="p1673059554084824"></a>Calculates the imaginary part of the complex number <strong id="b1739675022084824"><a name="b1739675022084824"></a><a name="b1739675022084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row825971890084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025259834084824"><a name="p2025259834084824"></a><a name="p2025259834084824"></a><a href="math.md#gaac22dc2fffc4326595ff807d441f0675">cimagf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1938424233084824"><a name="p1938424233084824"></a><a name="p1938424233084824"></a>float </p>
<p id="p970482176084824"><a name="p970482176084824"></a><a name="p970482176084824"></a>Calculates the imaginary part of the complex number <strong id="b534155162084824"><a name="b534155162084824"></a><a name="b534155162084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1446718042084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789691743084824"><a name="p1789691743084824"></a><a name="p1789691743084824"></a><a href="math.md#ga4237f0401b8123eaec284c995ced4b04">cimagl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1250895754084824"><a name="p1250895754084824"></a><a name="p1250895754084824"></a>long double </p>
<p id="p1754767738084824"><a name="p1754767738084824"></a><a name="p1754767738084824"></a>Calculates the imaginary part of the complex number <strong id="b1512844705084824"><a name="b1512844705084824"></a><a name="b1512844705084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row239499063084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p285779775084824"><a name="p285779775084824"></a><a name="p285779775084824"></a><a href="math.md#ga6fb30f37aa43eb2e0199ffdc38cac18a">conj</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088910584084824"><a name="p1088910584084824"></a><a name="p1088910584084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1350770366084824"><a name="p1350770366084824"></a><a name="p1350770366084824"></a>Calculates the conjugate of the complex number <strong id="b2092185668084824"><a name="b2092185668084824"></a><a name="b2092185668084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row354539671084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p755329908084824"><a name="p755329908084824"></a><a name="p755329908084824"></a><a href="math.md#ga471ecd8d25e722ecae510a635c1a2c53">conjf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1506678466084824"><a name="p1506678466084824"></a><a name="p1506678466084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1562837837084824"><a name="p1562837837084824"></a><a name="p1562837837084824"></a>Calculates the conjugate of the complex number <strong id="b772334381084824"><a name="b772334381084824"></a><a name="b772334381084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row750777834084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p699113840084824"><a name="p699113840084824"></a><a name="p699113840084824"></a><a href="math.md#ga5156353f4650ed7ee06b152790c1558b">conjl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p636162884084824"><a name="p636162884084824"></a><a name="p636162884084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p624646009084824"><a name="p624646009084824"></a><a name="p624646009084824"></a>Calculates the conjugate of the complex number <strong id="b922315213084824"><a name="b922315213084824"></a><a name="b922315213084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row409564200084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p565187962084824"><a name="p565187962084824"></a><a name="p565187962084824"></a><a href="math.md#gac10f86edf0994d0ee834768633be644e">cproj</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268634156084824"><a name="p268634156084824"></a><a name="p268634156084824"></a>double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p697801748084824"><a name="p697801748084824"></a><a name="p697801748084824"></a>Calculates the projection of the complex number <strong id="b454188532084824"><a name="b454188532084824"></a><a name="b454188532084824"></a>z</strong> onto the Riemann sphere. </p>
</td>
</tr>
<tr id="row1858370540084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597989997084824"><a name="p597989997084824"></a><a name="p597989997084824"></a><a href="math.md#ga9f435a71e44dd1e13eca358e2ca530e6">cprojf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p812756504084824"><a name="p812756504084824"></a><a name="p812756504084824"></a>float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p1434868079084824"><a name="p1434868079084824"></a><a name="p1434868079084824"></a>Calculates the projection of the complex number <strong id="b1273267409084824"><a name="b1273267409084824"></a><a name="b1273267409084824"></a>z</strong> onto the Riemann sphere. </p>
</td>
</tr>
<tr id="row318901991084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p60635441084824"><a name="p60635441084824"></a><a name="p60635441084824"></a><a href="math.md#ga2cc437f3ab8e77dbd8fb024c66474915">cprojl</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p263198400084824"><a name="p263198400084824"></a><a name="p263198400084824"></a>long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> </p>
<p id="p590788143084824"><a name="p590788143084824"></a><a name="p590788143084824"></a>Calculates the projection of the complex number <strong id="b1587494234084824"><a name="b1587494234084824"></a><a name="b1587494234084824"></a>z</strong> onto the Riemann sphere. </p>
</td>
</tr>
<tr id="row346827458084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838356292084824"><a name="p838356292084824"></a><a name="p838356292084824"></a><a href="math.md#ga24b1a511efdb973354d81646c5c3bb81">creal</a> (double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416643463084824"><a name="p416643463084824"></a><a name="p416643463084824"></a>double </p>
<p id="p843163874084824"><a name="p843163874084824"></a><a name="p843163874084824"></a>Calculates the real part of the complex number <strong id="b655812516084824"><a name="b655812516084824"></a><a name="b655812516084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1338598567084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323976930084824"><a name="p1323976930084824"></a><a name="p1323976930084824"></a><a href="math.md#gad052a3eb4d9f32153173e6bcea9e42ce">crealf</a> (float <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743284068084824"><a name="p743284068084824"></a><a name="p743284068084824"></a>float </p>
<p id="p1479690177084824"><a name="p1479690177084824"></a><a name="p1479690177084824"></a>Calculates the real part of the complex number <strong id="b516201970084824"><a name="b516201970084824"></a><a name="b516201970084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row208289584084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1693280076084824"><a name="p1693280076084824"></a><a name="p1693280076084824"></a><a href="math.md#ga4ee2baa54a4e51877c59527d2be1a0da">creall</a> (long double <a href="math.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397543696084824"><a name="p397543696084824"></a><a name="p397543696084824"></a>long double </p>
<p id="p324621634084824"><a name="p324621634084824"></a><a name="p324621634084824"></a>Calculates the real part of the complex number <strong id="b335116003084824"><a name="b335116003084824"></a><a name="b335116003084824"></a>z</strong>. </p>
</td>
</tr>
<tr id="row606997953084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1866921772084824"><a name="p1866921772084824"></a><a name="p1866921772084824"></a><a href="math.md#gac85b548794b2e0c90e147ab5e0f285e5">feclearexcept</a> (int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p235636814084824"><a name="p235636814084824"></a><a name="p235636814084824"></a>int </p>
<p id="p1807548030084824"><a name="p1807548030084824"></a><a name="p1807548030084824"></a>Clears floating-point exceptions specified by <strong id="b111168617084824"><a name="b111168617084824"></a><a name="b111168617084824"></a>excepts</strong>. </p>
</td>
</tr>
<tr id="row780370826084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356610415084824"><a name="p1356610415084824"></a><a name="p1356610415084824"></a><a href="math.md#gadc77aa0943782d65cd89a7ad931efccd">fegetexceptflag</a> (<a href="math.md#ga3eec78fdb9921de3f7254105f546c624">fexcept_t</a> *flagp, int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825844175084824"><a name="p1825844175084824"></a><a name="p1825844175084824"></a>int </p>
<p id="p330441136084824"><a name="p330441136084824"></a><a name="p330441136084824"></a>Stores the floating-point exceptions specified by <strong id="b1016425322084824"><a name="b1016425322084824"></a><a name="b1016425322084824"></a>excepts</strong> into the <strong id="b138466607084824"><a name="b138466607084824"></a><a name="b138466607084824"></a>flagp</strong> variable address. </p>
</td>
</tr>
<tr id="row1976578551084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p762541902084824"><a name="p762541902084824"></a><a name="p762541902084824"></a><a href="math.md#gaeecf59ba4dd156c6a9954bd0c1a9f6eb">feraiseexcept</a> (int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699064772084824"><a name="p1699064772084824"></a><a name="p1699064772084824"></a>int </p>
<p id="p1849102312084824"><a name="p1849102312084824"></a><a name="p1849102312084824"></a>Obtains the floating-point exceptions specified by <strong id="b1519452209084824"><a name="b1519452209084824"></a><a name="b1519452209084824"></a>excepts</strong>. </p>
</td>
</tr>
<tr id="row1568838050084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227218412084824"><a name="p1227218412084824"></a><a name="p1227218412084824"></a><a href="math.md#gafb3852ee8f5a841548c91bac153ee3d1">fesetexceptflag</a> (const <a href="math.md#ga3eec78fdb9921de3f7254105f546c624">fexcept_t</a> *flagp, int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2112793549084824"><a name="p2112793549084824"></a><a name="p2112793549084824"></a>int </p>
<p id="p1785815611084824"><a name="p1785815611084824"></a><a name="p1785815611084824"></a>Sets the exception status flag by copying the floating-point exceptions stored in the <strong id="b1522476937084824"><a name="b1522476937084824"></a><a name="b1522476937084824"></a>flagp</strong> address to the <strong id="b1803705863084824"><a name="b1803705863084824"></a><a name="b1803705863084824"></a>excepts</strong> parameter. </p>
</td>
</tr>
<tr id="row670750943084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p57813561084824"><a name="p57813561084824"></a><a name="p57813561084824"></a><a href="math.md#ga1fd22f10456d303ba12c28e394b1da90">fetestexcept</a> (int excepts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924901276084824"><a name="p924901276084824"></a><a name="p924901276084824"></a>int </p>
<p id="p2024763880084824"><a name="p2024763880084824"></a><a name="p2024763880084824"></a>Checks whether the floating-point exceptions specified by <strong id="b1225990248084824"><a name="b1225990248084824"></a><a name="b1225990248084824"></a>excepts</strong> have been raised. </p>
</td>
</tr>
<tr id="row863731019084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704247677084824"><a name="p704247677084824"></a><a name="p704247677084824"></a><a href="math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8">fegetround</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p769392023084824"><a name="p769392023084824"></a><a name="p769392023084824"></a>int </p>
<p id="p1513037199084824"><a name="p1513037199084824"></a><a name="p1513037199084824"></a>Obtains the macro corresponding to the current rounding mode. </p>
</td>
</tr>
<tr id="row1582688001084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p297485434084824"><a name="p297485434084824"></a><a name="p297485434084824"></a><a href="math.md#ga5729c4728ebe75d4975bb7250a2d8f4a">fesetround</a> (int rounding_mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1409391970084824"><a name="p1409391970084824"></a><a name="p1409391970084824"></a>int </p>
<p id="p2129701520084824"><a name="p2129701520084824"></a><a name="p2129701520084824"></a>Sets the rounding mode. </p>
</td>
</tr>
<tr id="row2030652158084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1914675773084824"><a name="p1914675773084824"></a><a name="p1914675773084824"></a><a href="math.md#ga9a971efefb28e62b22de4e5f2567da81">fegetenv</a> (<a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733501343084824"><a name="p1733501343084824"></a><a name="p1733501343084824"></a>int </p>
<p id="p672326769084824"><a name="p672326769084824"></a><a name="p672326769084824"></a>Stores the current floating-point environment into the object specified by <strong id="b872585805084824"><a name="b872585805084824"></a><a name="b872585805084824"></a>envp</strong>. </p>
</td>
</tr>
<tr id="row319740839084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380346578084824"><a name="p380346578084824"></a><a name="p380346578084824"></a><a href="math.md#ga7bf2aed63eeaa74f4295a996b3ba4616">feholdexcept</a> (<a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059946388084824"><a name="p1059946388084824"></a><a name="p1059946388084824"></a>int </p>
<p id="p261382906084824"><a name="p261382906084824"></a><a name="p261382906084824"></a>Stores the current floating-point environment into the object specified by <strong id="b1711171465084824"><a name="b1711171465084824"></a><a name="b1711171465084824"></a>envp</strong>, with all status flags cleared. </p>
</td>
</tr>
<tr id="row1397314731084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p325037144084824"><a name="p325037144084824"></a><a name="p325037144084824"></a><a href="math.md#ga65184dc5ad4e001083a6fd59d0cd7a2d">fesetenv</a> (const <a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p220799199084824"><a name="p220799199084824"></a><a name="p220799199084824"></a>int </p>
<p id="p229958289084824"><a name="p229958289084824"></a><a name="p229958289084824"></a>Sets the current floating-point environment. </p>
</td>
</tr>
<tr id="row1500204194084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612512870084824"><a name="p612512870084824"></a><a name="p612512870084824"></a><a href="math.md#gaa8c45da6bfe39178d4d199d3f0f6bbaf">feupdateenv</a> (const <a href="fenv_t.md">fenv_t</a> *envp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1055533586084824"><a name="p1055533586084824"></a><a name="p1055533586084824"></a>int </p>
<p id="p1931906920084824"><a name="p1931906920084824"></a><a name="p1931906920084824"></a>Updates the current floating-point environment from the object specified by <strong id="b843482275084824"><a name="b843482275084824"></a><a name="b843482275084824"></a>envp</strong>. </p>
</td>
</tr>
<tr id="row2074602454084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p310177121084824"><a name="p310177121084824"></a><a name="p310177121084824"></a><a href="math.md#gae93afe22ff34c79ee97ea3eaf77557db">acos</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121076957084824"><a name="p1121076957084824"></a><a name="p1121076957084824"></a>double </p>
<p id="p806518742084824"><a name="p806518742084824"></a><a name="p806518742084824"></a>Calculates the arc cosine of the double value <strong id="b696648082084824"><a name="b696648082084824"></a><a name="b696648082084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1951525849084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488328398084824"><a name="p1488328398084824"></a><a name="p1488328398084824"></a><a href="math.md#ga983a9e1aa7568df39153ea4d8e16653b">acosf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971762856084824"><a name="p1971762856084824"></a><a name="p1971762856084824"></a>float </p>
<p id="p1574561802084824"><a name="p1574561802084824"></a><a name="p1574561802084824"></a>Calculates the arc cosine of the float value <strong id="b1877504450084824"><a name="b1877504450084824"></a><a name="b1877504450084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1388939829084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1334954783084824"><a name="p1334954783084824"></a><a name="p1334954783084824"></a><a href="math.md#gae84dc6cff92b3417098f16a1811635e4">acosl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1544622520084824"><a name="p1544622520084824"></a><a name="p1544622520084824"></a>long double </p>
<p id="p1156338726084824"><a name="p1156338726084824"></a><a name="p1156338726084824"></a>Calculates the arc cosine of the long double value <strong id="b1899710893084824"><a name="b1899710893084824"></a><a name="b1899710893084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1678731680084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146135566084824"><a name="p2146135566084824"></a><a name="p2146135566084824"></a><a href="math.md#gac862445bcb46911b1782c284829d5e46">acosh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2054455086084824"><a name="p2054455086084824"></a><a name="p2054455086084824"></a>double </p>
<p id="p1749005699084824"><a name="p1749005699084824"></a><a name="p1749005699084824"></a>Calculates the inverse hyperbolic cosine of the double value <strong id="b581415025084824"><a name="b581415025084824"></a><a name="b581415025084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row496388484084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p695813033084824"><a name="p695813033084824"></a><a name="p695813033084824"></a><a href="math.md#ga84cfd14c3432390f70b6233d24ad173b">acoshf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p61842205084824"><a name="p61842205084824"></a><a name="p61842205084824"></a>float </p>
<p id="p1577812935084824"><a name="p1577812935084824"></a><a name="p1577812935084824"></a>Calculates the inverse hyperbolic cosine of float value <strong id="b651466660084824"><a name="b651466660084824"></a><a name="b651466660084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1675513042084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p923061569084824"><a name="p923061569084824"></a><a name="p923061569084824"></a><a href="math.md#ga104456314ba05665d6cbb805e823dd10">acoshl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768772770084824"><a name="p768772770084824"></a><a name="p768772770084824"></a>long double </p>
<p id="p138581012084824"><a name="p138581012084824"></a><a name="p138581012084824"></a>Calculates the inverse hyperbolic cosine of the long double value <strong id="b479789477084824"><a name="b479789477084824"></a><a name="b479789477084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row92072778084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p491591994084824"><a name="p491591994084824"></a><a name="p491591994084824"></a><a href="math.md#gaa9528d92a3ae44ad6484da0774604454">asin</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225271561084824"><a name="p1225271561084824"></a><a name="p1225271561084824"></a>double </p>
<p id="p448081830084824"><a name="p448081830084824"></a><a name="p448081830084824"></a>Calculates the arc sine of the double value <strong id="b771824404084824"><a name="b771824404084824"></a><a name="b771824404084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1014497255084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40625793084824"><a name="p40625793084824"></a><a name="p40625793084824"></a><a href="math.md#ga7447a7400ca474ba42d127b04d6ee2b7">asinf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457207710084824"><a name="p457207710084824"></a><a name="p457207710084824"></a>float </p>
<p id="p1187703811084824"><a name="p1187703811084824"></a><a name="p1187703811084824"></a>Calculates the arc sine of the float value <strong id="b2128177031084824"><a name="b2128177031084824"></a><a name="b2128177031084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2051894343084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p608768004084824"><a name="p608768004084824"></a><a name="p608768004084824"></a><a href="math.md#ga3ace56b4f2a4a9364993a5af676793c5">asinl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380344866084824"><a name="p380344866084824"></a><a name="p380344866084824"></a>long double </p>
<p id="p648654258084824"><a name="p648654258084824"></a><a name="p648654258084824"></a>Calculates the arc sine of the long double value <strong id="b859555379084824"><a name="b859555379084824"></a><a name="b859555379084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1119320336084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1405302162084824"><a name="p1405302162084824"></a><a name="p1405302162084824"></a><a href="math.md#ga907297107e93ea9c8a0c8409a8e65079">asinh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820146524084824"><a name="p1820146524084824"></a><a name="p1820146524084824"></a>double </p>
<p id="p2119735335084824"><a name="p2119735335084824"></a><a name="p2119735335084824"></a>Calculates the inverse hyperbolic sine of the double value <strong id="b180580499084824"><a name="b180580499084824"></a><a name="b180580499084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row888433194084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488671936084824"><a name="p1488671936084824"></a><a name="p1488671936084824"></a><a href="math.md#ga1131c65ac49f31ed6774d27106c6394d">asinhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p487288935084824"><a name="p487288935084824"></a><a name="p487288935084824"></a>float </p>
<p id="p1457858316084824"><a name="p1457858316084824"></a><a name="p1457858316084824"></a>Calculates the inverse hyperbolic sine of the float value <strong id="b500011079084824"><a name="b500011079084824"></a><a name="b500011079084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1342352356084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p482981066084824"><a name="p482981066084824"></a><a name="p482981066084824"></a><a href="math.md#ga98df355372e19c11634992e4b7e35784">asinhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p506208904084824"><a name="p506208904084824"></a><a name="p506208904084824"></a>long double </p>
<p id="p566462737084824"><a name="p566462737084824"></a><a name="p566462737084824"></a>Calculates the inverse hyperbolic sine of the long double value <strong id="b1141601190084824"><a name="b1141601190084824"></a><a name="b1141601190084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row785725400084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488945768084824"><a name="p1488945768084824"></a><a name="p1488945768084824"></a><a href="math.md#ga1e2f8f6d64eaa95131bc63fee34970ea">atan</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p655116119084824"><a name="p655116119084824"></a><a name="p655116119084824"></a>double </p>
<p id="p1486407240084824"><a name="p1486407240084824"></a><a name="p1486407240084824"></a>Calculates the arc tangent of the double value <strong id="b209583931084824"><a name="b209583931084824"></a><a name="b209583931084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1770781180084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1704994599084824"><a name="p1704994599084824"></a><a name="p1704994599084824"></a><a href="math.md#gaa582bc257e477e805f4ec384a39a3a8e">atanf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1239871240084824"><a name="p1239871240084824"></a><a name="p1239871240084824"></a>float </p>
<p id="p1963718630084824"><a name="p1963718630084824"></a><a name="p1963718630084824"></a>Calculates the arc tangent of the float value <strong id="b1564010084084824"><a name="b1564010084084824"></a><a name="b1564010084084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row4201978084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p553447708084824"><a name="p553447708084824"></a><a name="p553447708084824"></a><a href="math.md#ga650d8dd23c16c6699d84651a18827d37">atanl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462921796084824"><a name="p1462921796084824"></a><a name="p1462921796084824"></a>long double </p>
<p id="p2131104351084824"><a name="p2131104351084824"></a><a name="p2131104351084824"></a>Calculates the arc tangent of the long double value <strong id="b1940467992084824"><a name="b1940467992084824"></a><a name="b1940467992084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1672971046084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597359573084824"><a name="p597359573084824"></a><a name="p597359573084824"></a><a href="math.md#ga349377202ca14f79eb335b1a421fe4d8">atan2</a> (double y, double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1013436688084824"><a name="p1013436688084824"></a><a name="p1013436688084824"></a>double </p>
<p id="p1363393165084824"><a name="p1363393165084824"></a><a name="p1363393165084824"></a>Calculates the arc tangent of two double values <strong id="b2088043028084824"><a name="b2088043028084824"></a><a name="b2088043028084824"></a>x</strong> and <strong id="b1327812776084824"><a name="b1327812776084824"></a><a name="b1327812776084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row231389907084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1473456870084824"><a name="p1473456870084824"></a><a name="p1473456870084824"></a><a href="math.md#gaf9e5469acf7a7bf82f29d86a77f539d4">atan2f</a> (float y, float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p701767222084824"><a name="p701767222084824"></a><a name="p701767222084824"></a>float </p>
<p id="p1600813465084824"><a name="p1600813465084824"></a><a name="p1600813465084824"></a>Calculates the arc tangent of two float values <strong id="b1857986513084824"><a name="b1857986513084824"></a><a name="b1857986513084824"></a>x</strong> and <strong id="b275449269084824"><a name="b275449269084824"></a><a name="b275449269084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1452641892084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p506035875084824"><a name="p506035875084824"></a><a name="p506035875084824"></a><a href="math.md#gaa983bf34c931b97d66be8b7bfd03dc48">atan2l</a> (long double y, long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1049957448084824"><a name="p1049957448084824"></a><a name="p1049957448084824"></a>long double </p>
<p id="p1678545128084824"><a name="p1678545128084824"></a><a name="p1678545128084824"></a>Calculates the arc tangent of two long double values <strong id="b721911497084824"><a name="b721911497084824"></a><a name="b721911497084824"></a>x</strong> and <strong id="b1313205384084824"><a name="b1313205384084824"></a><a name="b1313205384084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row74391290084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442627219084824"><a name="p442627219084824"></a><a name="p442627219084824"></a><a href="math.md#gac07fd7b77fa341563abccf9efcc1a711">atanh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45415361084824"><a name="p45415361084824"></a><a name="p45415361084824"></a>double </p>
<p id="p2119502568084824"><a name="p2119502568084824"></a><a name="p2119502568084824"></a>Calculates the inverse hyperbolic tangent of the double value <strong id="b609769527084824"><a name="b609769527084824"></a><a name="b609769527084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1341485149084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p159725347084824"><a name="p159725347084824"></a><a name="p159725347084824"></a><a href="math.md#ga626d9d6644848e74188f37f0f3ddd4f4">atanhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1922541243084824"><a name="p1922541243084824"></a><a name="p1922541243084824"></a>float </p>
<p id="p174647983084824"><a name="p174647983084824"></a><a name="p174647983084824"></a>Calculates the inverse hyperbolic tangent of the float value <strong id="b345295407084824"><a name="b345295407084824"></a><a name="b345295407084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1034884243084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549404530084824"><a name="p549404530084824"></a><a name="p549404530084824"></a><a href="math.md#gab25c31215118cd62672c38f80f010d66">atanhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70358231084824"><a name="p70358231084824"></a><a name="p70358231084824"></a>long double </p>
<p id="p1179181706084824"><a name="p1179181706084824"></a><a name="p1179181706084824"></a>Calculates the inverse hyperbolic tangent of the long double value <strong id="b415017670084824"><a name="b415017670084824"></a><a name="b415017670084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1936507820084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794801083084824"><a name="p1794801083084824"></a><a name="p1794801083084824"></a><a href="math.md#ga8af00e2203928978e0242b4afd1d899f">cbrt</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640162870084824"><a name="p1640162870084824"></a><a name="p1640162870084824"></a>double </p>
<p id="p269775939084824"><a name="p269775939084824"></a><a name="p269775939084824"></a>Calculates the cube root of the double value <strong id="b373002193084824"><a name="b373002193084824"></a><a name="b373002193084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1221077827084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1402010850084824"><a name="p1402010850084824"></a><a name="p1402010850084824"></a><a href="math.md#ga396c6a553500a355627741e234045bf4">cbrtf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1160064926084824"><a name="p1160064926084824"></a><a name="p1160064926084824"></a>float </p>
<p id="p716872543084824"><a name="p716872543084824"></a><a name="p716872543084824"></a>Calculates the cube root of the float value <strong id="b190098454084824"><a name="b190098454084824"></a><a name="b190098454084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1546556993084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873071755084824"><a name="p1873071755084824"></a><a name="p1873071755084824"></a><a href="math.md#ga521c2f4c10b7bb5363bad058ef56794c">cbrtl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979998571084824"><a name="p979998571084824"></a><a name="p979998571084824"></a>long double </p>
<p id="p129344688084824"><a name="p129344688084824"></a><a name="p129344688084824"></a>Calculates the cube root of the long double value <strong id="b927651259084824"><a name="b927651259084824"></a><a name="b927651259084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1378961617084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1644301425084824"><a name="p1644301425084824"></a><a name="p1644301425084824"></a><a href="math.md#ga1ea6d7b591132268abc2e843ababd084">ceil</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1765034412084824"><a name="p1765034412084824"></a><a name="p1765034412084824"></a>double </p>
<p id="p631269845084824"><a name="p631269845084824"></a><a name="p631269845084824"></a>Calculates the minimum integer greater than or equal to the double value <strong id="b1809493550084824"><a name="b1809493550084824"></a><a name="b1809493550084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2097174351084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1810928616084824"><a name="p1810928616084824"></a><a name="p1810928616084824"></a><a href="math.md#ga8c1a8db0710bb3f25f643a0fca68fc60">ceilf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p266565069084824"><a name="p266565069084824"></a><a name="p266565069084824"></a>float </p>
<p id="p1488888945084824"><a name="p1488888945084824"></a><a name="p1488888945084824"></a>Calculates the minimum integer greater than or equal to the float value <strong id="b1943458090084824"><a name="b1943458090084824"></a><a name="b1943458090084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1625389686084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p403510105084824"><a name="p403510105084824"></a><a name="p403510105084824"></a><a href="math.md#gae11b7781f057eb7ba5d7ed95be7fdbee">ceill</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p516662624084824"><a name="p516662624084824"></a><a name="p516662624084824"></a>long double </p>
<p id="p1255644707084824"><a name="p1255644707084824"></a><a name="p1255644707084824"></a>Calculates the minimum integer greater than or equal to the long double value <strong id="b1132791339084824"><a name="b1132791339084824"></a><a name="b1132791339084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1147598979084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150256844084824"><a name="p1150256844084824"></a><a name="p1150256844084824"></a><a href="math.md#gad8d1296592a3e783acdd0de21ff58e2e">copysign</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1407864721084824"><a name="p1407864721084824"></a><a name="p1407864721084824"></a>double </p>
<p id="p1573068524084824"><a name="p1573068524084824"></a><a name="p1573068524084824"></a>Generates a value by combining the magnitude of the double value <strong id="b976265619084824"><a name="b976265619084824"></a><a name="b976265619084824"></a>x</strong> and the sign of the double value <strong id="b1518680493084824"><a name="b1518680493084824"></a><a name="b1518680493084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row720843235084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228857248084824"><a name="p228857248084824"></a><a name="p228857248084824"></a><a href="math.md#gaf7eb976cc28d0a9a6f0827d01611f979">copysignf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550949748084824"><a name="p1550949748084824"></a><a name="p1550949748084824"></a>float </p>
<p id="p270927117084824"><a name="p270927117084824"></a><a name="p270927117084824"></a>Generates a value by combining the magnitude of the float value <strong id="b529229714084824"><a name="b529229714084824"></a><a name="b529229714084824"></a>x</strong> and the sign of the float value <strong id="b1698195842084824"><a name="b1698195842084824"></a><a name="b1698195842084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1923723459084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753069447084824"><a name="p753069447084824"></a><a name="p753069447084824"></a><a href="math.md#gae60d4866e88abf023d92d33c6351ae6f">copysignl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p973344896084824"><a name="p973344896084824"></a><a name="p973344896084824"></a>long double </p>
<p id="p2116935747084824"><a name="p2116935747084824"></a><a name="p2116935747084824"></a>Generates a value by combining the magnitude of the long double value <strong id="b1536689802084824"><a name="b1536689802084824"></a><a name="b1536689802084824"></a>x</strong> and the sign of the long double value <strong id="b804576496084824"><a name="b804576496084824"></a><a name="b804576496084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1405923366084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007367896084824"><a name="p2007367896084824"></a><a name="p2007367896084824"></a><a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526106852084824"><a name="p1526106852084824"></a><a name="p1526106852084824"></a>double </p>
<p id="p402140823084824"><a name="p402140823084824"></a><a name="p402140823084824"></a>Calculates the cosine of the double value <strong id="b595718582084824"><a name="b595718582084824"></a><a name="b595718582084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row595146501084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p754241827084824"><a name="p754241827084824"></a><a name="p754241827084824"></a><a href="math.md#ga7b126b2344591e649c21c9ab0b8adb40">cosf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005777684084824"><a name="p2005777684084824"></a><a name="p2005777684084824"></a>float </p>
<p id="p2119577086084824"><a name="p2119577086084824"></a><a name="p2119577086084824"></a>Calculates the cosine of the float value <strong id="b880170222084824"><a name="b880170222084824"></a><a name="b880170222084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1324086004084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080833412084824"><a name="p2080833412084824"></a><a name="p2080833412084824"></a><a href="math.md#ga659287f7399efa8d6bc66dc37c8e35f4">cosl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1496249074084824"><a name="p1496249074084824"></a><a name="p1496249074084824"></a>long double </p>
<p id="p1865792043084824"><a name="p1865792043084824"></a><a name="p1865792043084824"></a>Calculates the cosine of the long double value <strong id="b1457368882084824"><a name="b1457368882084824"></a><a name="b1457368882084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1443577109084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1519291372084824"><a name="p1519291372084824"></a><a name="p1519291372084824"></a><a href="math.md#ga3795d3c1f1d30819be56da4e4d67f64b">cosh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p664707476084824"><a name="p664707476084824"></a><a name="p664707476084824"></a>double </p>
<p id="p991786459084824"><a name="p991786459084824"></a><a name="p991786459084824"></a>Calculates the hyperbolic cosine of the double value <strong id="b531338352084824"><a name="b531338352084824"></a><a name="b531338352084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row455687386084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892656814084824"><a name="p892656814084824"></a><a name="p892656814084824"></a><a href="math.md#ga498b368486b7ce8677820beeb78d8f66">coshf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p687298810084824"><a name="p687298810084824"></a><a name="p687298810084824"></a>float </p>
<p id="p1297903768084824"><a name="p1297903768084824"></a><a name="p1297903768084824"></a>Calculates the hyperbolic cosine of the float value <strong id="b832704578084824"><a name="b832704578084824"></a><a name="b832704578084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row389878424084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1415414985084824"><a name="p1415414985084824"></a><a name="p1415414985084824"></a><a href="math.md#ga57602cd20f8de2dceea4f05ffb516d82">coshl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1504041015084824"><a name="p1504041015084824"></a><a name="p1504041015084824"></a>long double </p>
<p id="p1571836801084824"><a name="p1571836801084824"></a><a name="p1571836801084824"></a>Calculates the hyperbolic cosine of the long double value <strong id="b634634364084824"><a name="b634634364084824"></a><a name="b634634364084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row899841905084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p121765702084824"><a name="p121765702084824"></a><a name="p121765702084824"></a><a href="math.md#gaa8b35382a71885eed509a5f87bf5e266">erf</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527146181084824"><a name="p527146181084824"></a><a name="p527146181084824"></a>double </p>
<p id="p1662649540084824"><a name="p1662649540084824"></a><a name="p1662649540084824"></a>Calculates the error function of the double value <strong id="b755739182084824"><a name="b755739182084824"></a><a name="b755739182084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1601467291084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1189774067084824"><a name="p1189774067084824"></a><a name="p1189774067084824"></a><a href="math.md#gaabebdd2dd548c14805831297ac129862">erff</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720735353084824"><a name="p720735353084824"></a><a name="p720735353084824"></a>float </p>
<p id="p1630998596084824"><a name="p1630998596084824"></a><a name="p1630998596084824"></a>Calculates the error function of the float value <strong id="b1729155829084824"><a name="b1729155829084824"></a><a name="b1729155829084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1062403487084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521027462084824"><a name="p521027462084824"></a><a name="p521027462084824"></a><a href="math.md#ga6ccdcbbc2f0b22de2add8955e415170e">erfl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1916818869084824"><a name="p1916818869084824"></a><a name="p1916818869084824"></a>long double </p>
<p id="p642509198084824"><a name="p642509198084824"></a><a name="p642509198084824"></a>Calculates the error function of the long double value <strong id="b1062409015084824"><a name="b1062409015084824"></a><a name="b1062409015084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row698052217084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1730188114084824"><a name="p1730188114084824"></a><a name="p1730188114084824"></a><a href="math.md#ga0b6c4cfae41124da64c9a2dcc09e6045">erfc</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069978647084824"><a name="p2069978647084824"></a><a name="p2069978647084824"></a>double </p>
<p id="p890472658084824"><a name="p890472658084824"></a><a name="p890472658084824"></a>Calculates the complementary error function of the double value <strong id="b1394255043084824"><a name="b1394255043084824"></a><a name="b1394255043084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1131424407084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390363651084824"><a name="p390363651084824"></a><a name="p390363651084824"></a><a href="math.md#gad948b9d3bfcb66c074ffe17326030d41">erfcf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p251526346084824"><a name="p251526346084824"></a><a name="p251526346084824"></a>float </p>
<p id="p1761149428084824"><a name="p1761149428084824"></a><a name="p1761149428084824"></a>Calculates the complementary error function of the float value <strong id="b1303148670084824"><a name="b1303148670084824"></a><a name="b1303148670084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row980888602084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509589110084824"><a name="p1509589110084824"></a><a name="p1509589110084824"></a><a href="math.md#ga8ac2c9e0246c0c8106d04762a9623594">erfcl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864688796084824"><a name="p1864688796084824"></a><a name="p1864688796084824"></a>long double </p>
<p id="p1099251788084824"><a name="p1099251788084824"></a><a name="p1099251788084824"></a>Calculates the complementary error function of the long double value <strong id="b1833616508084824"><a name="b1833616508084824"></a><a name="b1833616508084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row990230657084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p891940821084824"><a name="p891940821084824"></a><a name="p891940821084824"></a><a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023393900084824"><a name="p1023393900084824"></a><a name="p1023393900084824"></a>double </p>
<p id="p1745499070084824"><a name="p1745499070084824"></a><a name="p1745499070084824"></a>Calculates the base-e exponential function of the double value <strong id="b540391754084824"><a name="b540391754084824"></a><a name="b540391754084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1841208856084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1262867114084824"><a name="p1262867114084824"></a><a name="p1262867114084824"></a><a href="math.md#ga0c2bc89b8355a89542ac98d9e2120363">expf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1709171846084824"><a name="p1709171846084824"></a><a name="p1709171846084824"></a>float </p>
<p id="p1703040058084824"><a name="p1703040058084824"></a><a name="p1703040058084824"></a>Calculates the base-e exponential function of the float value <strong id="b654486164084824"><a name="b654486164084824"></a><a name="b654486164084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1896363181084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p156319241084824"><a name="p156319241084824"></a><a name="p156319241084824"></a><a href="math.md#gaed4eb11ef1397c751334311ce5b43920">expl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p318775439084824"><a name="p318775439084824"></a><a name="p318775439084824"></a>long double </p>
<p id="p1380668829084824"><a name="p1380668829084824"></a><a name="p1380668829084824"></a>Calculates the base-e exponential function of the long double value <strong id="b1114610102084824"><a name="b1114610102084824"></a><a name="b1114610102084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1763569973084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490745087084824"><a name="p1490745087084824"></a><a name="p1490745087084824"></a><a href="math.md#ga86e37219434c0b7978453b6ca88fc5fb">exp2</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164987279084824"><a name="p1164987279084824"></a><a name="p1164987279084824"></a>double </p>
<p id="p292757224084824"><a name="p292757224084824"></a><a name="p292757224084824"></a>Calculates the base-2 exponential function of the double value <strong id="b991613510084824"><a name="b991613510084824"></a><a name="b991613510084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1604324580084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2013856486084824"><a name="p2013856486084824"></a><a name="p2013856486084824"></a><a href="math.md#gaed26c6708ff2027f9a8214d206eef0e7">exp2f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p5521821084824"><a name="p5521821084824"></a><a name="p5521821084824"></a>float </p>
<p id="p382872224084824"><a name="p382872224084824"></a><a name="p382872224084824"></a>Calculates the base-2 exponential function of the float value <strong id="b1488082304084824"><a name="b1488082304084824"></a><a name="b1488082304084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1337686552084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778995880084824"><a name="p1778995880084824"></a><a name="p1778995880084824"></a><a href="math.md#ga4618e032de8318b72df5cc71f15b5e45">exp2l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2118806503084824"><a name="p2118806503084824"></a><a name="p2118806503084824"></a>long double </p>
<p id="p349686782084824"><a name="p349686782084824"></a><a name="p349686782084824"></a>Calculates the base-2 exponential function of the long double value <strong id="b1285744723084824"><a name="b1285744723084824"></a><a name="b1285744723084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row929872378084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974580458084824"><a name="p1974580458084824"></a><a name="p1974580458084824"></a><a href="math.md#gae4963ac40f96d4b1fe8af1b1e90a20bb">expm1</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p300262874084824"><a name="p300262874084824"></a><a name="p300262874084824"></a>double </p>
<p id="p421183243084824"><a name="p421183243084824"></a><a name="p421183243084824"></a>Calculates e raised to the power of the double value <strong id="b1130492168084824"><a name="b1130492168084824"></a><a name="b1130492168084824"></a>x</strong> minus one, that is, (e^x)-1. </p>
</td>
</tr>
<tr id="row783653367084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587787272084824"><a name="p1587787272084824"></a><a name="p1587787272084824"></a><a href="math.md#ga5b8d8815f5c801fdbdb7f7767fbf9af4">expm1f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p928857356084824"><a name="p928857356084824"></a><a name="p928857356084824"></a>float </p>
<p id="p1378879407084824"><a name="p1378879407084824"></a><a name="p1378879407084824"></a>Calculates e raised to the power of the float value <strong id="b564806368084824"><a name="b564806368084824"></a><a name="b564806368084824"></a>x</strong> minus one. </p>
</td>
</tr>
<tr id="row741225017084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295842696084824"><a name="p295842696084824"></a><a name="p295842696084824"></a><a href="math.md#ga702b0680671cf9ef94017ac04f77358b">expm1l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615818682084824"><a name="p1615818682084824"></a><a name="p1615818682084824"></a>long double </p>
<p id="p1967731350084824"><a name="p1967731350084824"></a><a name="p1967731350084824"></a>Calculates e raised to the power of the long double value <strong id="b1420086321084824"><a name="b1420086321084824"></a><a name="b1420086321084824"></a>x</strong> minus one. </p>
</td>
</tr>
<tr id="row392618796084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p595463574084824"><a name="p595463574084824"></a><a name="p595463574084824"></a><a href="math.md#ga8fb5c0b9b43a108724b355136d29d2f9">fabs</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448595099084824"><a name="p448595099084824"></a><a name="p448595099084824"></a>double </p>
<p id="p548236602084824"><a name="p548236602084824"></a><a name="p548236602084824"></a>Calculates the absolute value of the double value <strong id="b1039279917084824"><a name="b1039279917084824"></a><a name="b1039279917084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1916302918084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1411851666084824"><a name="p1411851666084824"></a><a name="p1411851666084824"></a><a href="math.md#ga9b02e2f3ebf257ac4f4d3ca1da6147d7">fabsf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1888125318084824"><a name="p1888125318084824"></a><a name="p1888125318084824"></a>float </p>
<p id="p1002948007084824"><a name="p1002948007084824"></a><a name="p1002948007084824"></a>Calculates the absolute value of the float value <strong id="b9999755084824"><a name="b9999755084824"></a><a name="b9999755084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1464972958084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p306254430084824"><a name="p306254430084824"></a><a name="p306254430084824"></a><a href="math.md#ga404c051ab9afd74c7ceed207683a235f">fabsl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140088517084824"><a name="p140088517084824"></a><a name="p140088517084824"></a>long double </p>
<p id="p461422156084824"><a name="p461422156084824"></a><a name="p461422156084824"></a>Calculates the absolute value of the long double value <strong id="b119838788084824"><a name="b119838788084824"></a><a name="b119838788084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row462532623084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p692921335084824"><a name="p692921335084824"></a><a name="p692921335084824"></a><a href="math.md#ga800522810eaaed28bd53798bff4b0bfa">fdim</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p816772769084824"><a name="p816772769084824"></a><a name="p816772769084824"></a>double </p>
<p id="p353538765084824"><a name="p353538765084824"></a><a name="p353538765084824"></a>Calculates the positive difference between the double value <strong id="b865495064084824"><a name="b865495064084824"></a><a name="b865495064084824"></a>x</strong> and <strong id="b1287791280084824"><a name="b1287791280084824"></a><a name="b1287791280084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1722267953084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1442540191084824"><a name="p1442540191084824"></a><a name="p1442540191084824"></a><a href="math.md#gaeee3a0bf2804c53c65199590ac4804cf">fdimf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p706765072084824"><a name="p706765072084824"></a><a name="p706765072084824"></a>float </p>
<p id="p27008118084824"><a name="p27008118084824"></a><a name="p27008118084824"></a>Calculates the positive difference between the float value <strong id="b2029221650084824"><a name="b2029221650084824"></a><a name="b2029221650084824"></a>x</strong> and <strong id="b581197774084824"><a name="b581197774084824"></a><a name="b581197774084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1453113756084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1884785814084824"><a name="p1884785814084824"></a><a name="p1884785814084824"></a><a href="math.md#gab88ba65d1861deddbbc5cb5384d6a02e">fdiml</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213686544084824"><a name="p213686544084824"></a><a name="p213686544084824"></a>long double </p>
<p id="p1821420234084824"><a name="p1821420234084824"></a><a name="p1821420234084824"></a>Calculates the positive difference between the long double value <strong id="b836556673084824"><a name="b836556673084824"></a><a name="b836556673084824"></a>x</strong> and <strong id="b2015959485084824"><a name="b2015959485084824"></a><a name="b2015959485084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1066242473084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1439844992084824"><a name="p1439844992084824"></a><a name="p1439844992084824"></a><a href="math.md#ga6de60a3e907dcf0bfe3ea8d64f1e8873">floor</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p937556439084824"><a name="p937556439084824"></a><a name="p937556439084824"></a>double </p>
<p id="p1671750950084824"><a name="p1671750950084824"></a><a name="p1671750950084824"></a>Obtains the largest integer less than or equal to the double value <strong id="b984655883084824"><a name="b984655883084824"></a><a name="b984655883084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1243334258084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001066958084824"><a name="p1001066958084824"></a><a name="p1001066958084824"></a><a href="math.md#ga0bcc6aa4b3c37bfa73f06ebdecc0d247">floorf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309227485084824"><a name="p309227485084824"></a><a name="p309227485084824"></a>float </p>
<p id="p214703202084824"><a name="p214703202084824"></a><a name="p214703202084824"></a>Obtains the largest integer less than or equal to the float value <strong id="b417011904084824"><a name="b417011904084824"></a><a name="b417011904084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1395692200084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p182261185084824"><a name="p182261185084824"></a><a name="p182261185084824"></a><a href="math.md#ga211df53cdf5208b9bbfa92e2d9aef97f">floorl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1506137180084824"><a name="p1506137180084824"></a><a name="p1506137180084824"></a>long double </p>
<p id="p1944391225084824"><a name="p1944391225084824"></a><a name="p1944391225084824"></a>Obtains the largest integer less than or equal to the long double value <strong id="b1987062535084824"><a name="b1987062535084824"></a><a name="b1987062535084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1195143306084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904715337084824"><a name="p904715337084824"></a><a name="p904715337084824"></a><a href="math.md#gac6df7bd41d198a70da3915a80de5452d">fma</a> (double x, double y, double z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126855969084824"><a name="p2126855969084824"></a><a name="p2126855969084824"></a>double </p>
<p id="p1199846486084824"><a name="p1199846486084824"></a><a name="p1199846486084824"></a>Calculates the value of <strong id="b1692383231084824"><a name="b1692383231084824"></a><a name="b1692383231084824"></a>x*y+z</strong> and rounds the result up. </p>
</td>
</tr>
<tr id="row1618303428084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1936540565084824"><a name="p1936540565084824"></a><a name="p1936540565084824"></a><a href="math.md#gaa6b32a0b7f88680bb59bcfb9c6168ed2">fmaf</a> (float x, float y, float z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p56891085084824"><a name="p56891085084824"></a><a name="p56891085084824"></a>float </p>
<p id="p921339940084824"><a name="p921339940084824"></a><a name="p921339940084824"></a>Calculates the value of <strong id="b1771224692084824"><a name="b1771224692084824"></a><a name="b1771224692084824"></a>x*y+z</strong> and rounds the result up. </p>
</td>
</tr>
<tr id="row910027135084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2416126084824"><a name="p2416126084824"></a><a name="p2416126084824"></a><a href="math.md#gaf30b6b26252979964796ffa55dd30120">fmal</a> (long double x, long double y, long double z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2013972486084824"><a name="p2013972486084824"></a><a name="p2013972486084824"></a>long double </p>
<p id="p2002976606084824"><a name="p2002976606084824"></a><a name="p2002976606084824"></a>Calculates the value of <strong id="b337952992084824"><a name="b337952992084824"></a><a name="b337952992084824"></a>x*y+z</strong> and rounds the result up. </p>
</td>
</tr>
<tr id="row393763518084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1947793865084824"><a name="p1947793865084824"></a><a name="p1947793865084824"></a><a href="math.md#ga35e041615ac931b4d848a7b173049301">fmax</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p93709462084824"><a name="p93709462084824"></a><a name="p93709462084824"></a>double </p>
<p id="p959270920084824"><a name="p959270920084824"></a><a name="p959270920084824"></a>Obtains the larger value of two double values <strong id="b682849242084824"><a name="b682849242084824"></a><a name="b682849242084824"></a>x</strong> and <strong id="b919364494084824"><a name="b919364494084824"></a><a name="b919364494084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row591484189084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683852421084824"><a name="p1683852421084824"></a><a name="p1683852421084824"></a><a href="math.md#ga8849bfdbec18ded429fad4772cf60f4b">fmaxf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368274943084824"><a name="p368274943084824"></a><a name="p368274943084824"></a>float </p>
<p id="p1341663688084824"><a name="p1341663688084824"></a><a name="p1341663688084824"></a>Obtains the larger value of two float values <strong id="b580371556084824"><a name="b580371556084824"></a><a name="b580371556084824"></a>x</strong> and <strong id="b341526840084824"><a name="b341526840084824"></a><a name="b341526840084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1088856459084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p503319121084824"><a name="p503319121084824"></a><a name="p503319121084824"></a><a href="math.md#ga0e31e170115494fdc03b6556844232f3">fmaxl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895966181084824"><a name="p1895966181084824"></a><a name="p1895966181084824"></a>long double </p>
<p id="p188899728084824"><a name="p188899728084824"></a><a name="p188899728084824"></a>Obtains the larger value of two long double values <strong id="b1393797085084824"><a name="b1393797085084824"></a><a name="b1393797085084824"></a>x</strong> and <strong id="b1707937523084824"><a name="b1707937523084824"></a><a name="b1707937523084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row101990409084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1406395810084824"><a name="p1406395810084824"></a><a name="p1406395810084824"></a><a href="math.md#gaf0a18b3ac9e461ac48b4cfffb4945a84">fmin</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441894420084824"><a name="p1441894420084824"></a><a name="p1441894420084824"></a>double </p>
<p id="p1946011124084824"><a name="p1946011124084824"></a><a name="p1946011124084824"></a>Obtains the smaller value of two double values <strong id="b1411216289084824"><a name="b1411216289084824"></a><a name="b1411216289084824"></a>x</strong> and <strong id="b2045047366084824"><a name="b2045047366084824"></a><a name="b2045047366084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row646457724084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1716551323084824"><a name="p1716551323084824"></a><a name="p1716551323084824"></a><a href="math.md#ga9b4132c27f31d39c91c3c6063f378103">fminf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1549720623084824"><a name="p1549720623084824"></a><a name="p1549720623084824"></a>float </p>
<p id="p229541348084824"><a name="p229541348084824"></a><a name="p229541348084824"></a>Obtains the smaller value of two float values <strong id="b1782689328084824"><a name="b1782689328084824"></a><a name="b1782689328084824"></a>x</strong> and <strong id="b1878451169084824"><a name="b1878451169084824"></a><a name="b1878451169084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row816850794084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864853407084824"><a name="p1864853407084824"></a><a name="p1864853407084824"></a><a href="math.md#ga8a301190384886aa4e327db265fb5c9f">fminl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p566671053084824"><a name="p566671053084824"></a><a name="p566671053084824"></a>long double </p>
<p id="p415774414084824"><a name="p415774414084824"></a><a name="p415774414084824"></a>Obtains the smaller value of two long double values <strong id="b1819657673084824"><a name="b1819657673084824"></a><a name="b1819657673084824"></a>x</strong> and <strong id="b840241126084824"><a name="b840241126084824"></a><a name="b840241126084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row269953737084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478330993084824"><a name="p478330993084824"></a><a name="p478330993084824"></a><a href="math.md#ga537296d1a8f9fb621676038b99ba7edf">fmod</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563738167084824"><a name="p1563738167084824"></a><a name="p1563738167084824"></a>double </p>
<p id="p467736660084824"><a name="p467736660084824"></a><a name="p467736660084824"></a>Calculates the remainder of the double value <strong id="b1185493902084824"><a name="b1185493902084824"></a><a name="b1185493902084824"></a>x</strong> divided by the double value <strong id="b1816531963084824"><a name="b1816531963084824"></a><a name="b1816531963084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1962787146084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683768268084824"><a name="p683768268084824"></a><a name="p683768268084824"></a><a href="math.md#gaf17ec425baca2b5f3882a05b5e19dfb5">fmodf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1347873125084824"><a name="p1347873125084824"></a><a name="p1347873125084824"></a>float </p>
<p id="p1970612265084824"><a name="p1970612265084824"></a><a name="p1970612265084824"></a>Calculates the remainder of the float value <strong id="b2005212491084824"><a name="b2005212491084824"></a><a name="b2005212491084824"></a>x</strong> divided by the float value <strong id="b733717277084824"><a name="b733717277084824"></a><a name="b733717277084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1791362731084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p877901055084824"><a name="p877901055084824"></a><a name="p877901055084824"></a><a href="math.md#gaa927d9996fb40db42bd3a6cbe57da9a7">fmodl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1761170237084824"><a name="p1761170237084824"></a><a name="p1761170237084824"></a>long double </p>
<p id="p19553866084824"><a name="p19553866084824"></a><a name="p19553866084824"></a>Calculates the remainder of the long double value <strong id="b1196167872084824"><a name="b1196167872084824"></a><a name="b1196167872084824"></a>x</strong> divided by the long double value <strong id="b1239074464084824"><a name="b1239074464084824"></a><a name="b1239074464084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1662661198084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p715250368084824"><a name="p715250368084824"></a><a name="p715250368084824"></a><a href="math.md#gae3fa88adf02f16a693f3dccea3c42ef0">frexp</a> (double x, int *<a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p188394609084824"><a name="p188394609084824"></a><a name="p188394609084824"></a>double </p>
<p id="p963546585084824"><a name="p963546585084824"></a><a name="p963546585084824"></a>Decomposes the double value <strong id="b1871789539084824"><a name="b1871789539084824"></a><a name="b1871789539084824"></a>x</strong> into a significand and an integral exponent for 2. </p>
</td>
</tr>
<tr id="row1066316565084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p961439593084824"><a name="p961439593084824"></a><a name="p961439593084824"></a><a href="math.md#ga12c36e745d8a9eb4f01c7e0eeb426dd3">frexpf</a> (float x, int *<a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p178541149084824"><a name="p178541149084824"></a><a name="p178541149084824"></a>float </p>
<p id="p1364453915084824"><a name="p1364453915084824"></a><a name="p1364453915084824"></a>Decomposes float value <strong id="b1275614921084824"><a name="b1275614921084824"></a><a name="b1275614921084824"></a>x</strong> into a binary significand and an integral exponent for 2. </p>
</td>
</tr>
<tr id="row1172672283084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535887937084824"><a name="p1535887937084824"></a><a name="p1535887937084824"></a><a href="math.md#ga239d50c0595ff8538b9aa3186ac4fd29">frexpl</a> (long double x, int *<a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1213001631084824"><a name="p1213001631084824"></a><a name="p1213001631084824"></a>long double </p>
<p id="p1960619968084824"><a name="p1960619968084824"></a><a name="p1960619968084824"></a>Decomposes long double value <strong id="b668308692084824"><a name="b668308692084824"></a><a name="b668308692084824"></a>x</strong> into a binary significand and an integral exponent for 2. </p>
</td>
</tr>
<tr id="row1006523553084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61879992084824"><a name="p61879992084824"></a><a name="p61879992084824"></a><a href="math.md#ga6d6a905f61d535f8454190433b8c0ea5">hypot</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274545645084824"><a name="p1274545645084824"></a><a name="p1274545645084824"></a>double </p>
<p id="p1972337944084824"><a name="p1972337944084824"></a><a name="p1972337944084824"></a>Calculates the hypotenuse of a right triangle whose legs are <strong id="b491988674084824"><a name="b491988674084824"></a><a name="b491988674084824"></a>x</strong> and <strong id="b696800552084824"><a name="b696800552084824"></a><a name="b696800552084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1842933801084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1669453051084824"><a name="p1669453051084824"></a><a name="p1669453051084824"></a><a href="math.md#ga9fa4a03d7c4abfda7d9ad7b6ff7f6456">hypotf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p347710967084824"><a name="p347710967084824"></a><a name="p347710967084824"></a>float </p>
<p id="p2139803844084824"><a name="p2139803844084824"></a><a name="p2139803844084824"></a>Calculates the hypotenuse of a right triangle whose legs are <strong id="b1119410303084824"><a name="b1119410303084824"></a><a name="b1119410303084824"></a>x</strong> and <strong id="b669325406084824"><a name="b669325406084824"></a><a name="b669325406084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row628617613084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527494028084824"><a name="p1527494028084824"></a><a name="p1527494028084824"></a><a href="math.md#ga92a0e76d17c34fc1b3b2e7c0868aea6e">hypotl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1894353817084824"><a name="p1894353817084824"></a><a name="p1894353817084824"></a>long double </p>
<p id="p1730422498084824"><a name="p1730422498084824"></a><a name="p1730422498084824"></a>Calculates the hypotenuse of a right triangle whose legs are <strong id="b1068584483084824"><a name="b1068584483084824"></a><a name="b1068584483084824"></a>x</strong> and <strong id="b1212253891084824"><a name="b1212253891084824"></a><a name="b1212253891084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row317229382084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p192903370084824"><a name="p192903370084824"></a><a name="p192903370084824"></a><a href="math.md#ga600dd249210d15af31b9a29c2d09d255">ilogb</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1514208596084824"><a name="p1514208596084824"></a><a name="p1514208596084824"></a>int </p>
<p id="p2000249019084824"><a name="p2000249019084824"></a><a name="p2000249019084824"></a>Obtains the integral part of the logarithm of double value <strong id="b578565387084824"><a name="b578565387084824"></a><a name="b578565387084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1537324590084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056559613084824"><a name="p2056559613084824"></a><a name="p2056559613084824"></a><a href="math.md#gaf53f0f07bb80b1a38fb47773a190e7a7">ilogbf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1624943270084824"><a name="p1624943270084824"></a><a name="p1624943270084824"></a>int </p>
<p id="p937093283084824"><a name="p937093283084824"></a><a name="p937093283084824"></a>Obtains the integral part of the logarithm of float value <strong id="b578248900084824"><a name="b578248900084824"></a><a name="b578248900084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2004228722084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p115922296084824"><a name="p115922296084824"></a><a name="p115922296084824"></a><a href="math.md#gafbd166ed232a372f090b8f9fa8441423">ilogbl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090968384084824"><a name="p1090968384084824"></a><a name="p1090968384084824"></a>int </p>
<p id="p341275930084824"><a name="p341275930084824"></a><a name="p341275930084824"></a>Obtains the integral part of the logarithm of the long double value <strong id="b384923580084824"><a name="b384923580084824"></a><a name="b384923580084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1603874631084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175490194084824"><a name="p175490194084824"></a><a name="p175490194084824"></a><a href="math.md#gab3662815756f0bd419dc1b12f4ad905d">ldexp</a> (double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1840848543084824"><a name="p1840848543084824"></a><a name="p1840848543084824"></a>double </p>
<p id="p506318262084824"><a name="p506318262084824"></a><a name="p506318262084824"></a>Multiplies the double value <strong id="b1970432068084824"><a name="b1970432068084824"></a><a name="b1970432068084824"></a>x</strong> by 2 raised to the power of <strong id="b30401867084824"><a name="b30401867084824"></a><a name="b30401867084824"></a>exp</strong>. </p>
</td>
</tr>
<tr id="row381805534084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1124314088084824"><a name="p1124314088084824"></a><a name="p1124314088084824"></a><a href="math.md#gaacd370a7830c29f47239dea1ea2eb7f9">ldexpf</a> (float x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p871834177084824"><a name="p871834177084824"></a><a name="p871834177084824"></a>float </p>
<p id="p66621533084824"><a name="p66621533084824"></a><a name="p66621533084824"></a>Multiplies the float value <strong id="b1977597728084824"><a name="b1977597728084824"></a><a name="b1977597728084824"></a>x</strong> by 2 raised to the power of <strong id="b335609523084824"><a name="b335609523084824"></a><a name="b335609523084824"></a>exp</strong>. </p>
</td>
</tr>
<tr id="row864209049084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325948825084824"><a name="p1325948825084824"></a><a name="p1325948825084824"></a><a href="math.md#ga454187039ef790629dab1e7724c3c3b2">ldexpl</a> (long double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1035601569084824"><a name="p1035601569084824"></a><a name="p1035601569084824"></a>long double </p>
<p id="p1545199370084824"><a name="p1545199370084824"></a><a name="p1545199370084824"></a>Multiplies the long double value <strong id="b718829316084824"><a name="b718829316084824"></a><a name="b718829316084824"></a>x</strong> by 2 raised to the power of <strong id="b1070475032084824"><a name="b1070475032084824"></a><a name="b1070475032084824"></a>exp</strong>. </p>
</td>
</tr>
<tr id="row1609866777084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144893700084824"><a name="p2144893700084824"></a><a name="p2144893700084824"></a><a href="math.md#gacd3ebe923fa039624f0b7de3320816bf">lgamma</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749679985084824"><a name="p749679985084824"></a><a name="p749679985084824"></a>double </p>
<p id="p284642606084824"><a name="p284642606084824"></a><a name="p284642606084824"></a>Calculates the natural logarithm of the absolute value of the gamma function of the double value <strong id="b2086810873084824"><a name="b2086810873084824"></a><a name="b2086810873084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row440187323084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21737570084824"><a name="p21737570084824"></a><a name="p21737570084824"></a><a href="math.md#ga5900f7bf0093757f1ba36b5940b1e10b">lgammaf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1645701590084824"><a name="p1645701590084824"></a><a name="p1645701590084824"></a>float </p>
<p id="p1935464392084824"><a name="p1935464392084824"></a><a name="p1935464392084824"></a>Calculates the natural logarithm of the absolute value of the gamma function of the float value <strong id="b636681604084824"><a name="b636681604084824"></a><a name="b636681604084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row119115559084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1446094138084824"><a name="p1446094138084824"></a><a name="p1446094138084824"></a><a href="math.md#ga4dafd3eb6952c8daabe8a98f4a64a7df">lgammal</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400018313084824"><a name="p1400018313084824"></a><a name="p1400018313084824"></a>long double </p>
<p id="p1001230299084824"><a name="p1001230299084824"></a><a name="p1001230299084824"></a>Calculates the natural logarithm of the absolute value of the gamma function of the long double value <strong id="b104532791084824"><a name="b104532791084824"></a><a name="b104532791084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row549819316084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489140093084824"><a name="p1489140093084824"></a><a name="p1489140093084824"></a><a href="math.md#ga64a4201c82f6ee7043a270bbbc6a5e19">llrint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p396637835084824"><a name="p396637835084824"></a><a name="p396637835084824"></a>long long int </p>
<p id="p1165673509084824"><a name="p1165673509084824"></a><a name="p1165673509084824"></a>Rounds double value <strong id="b948269035084824"><a name="b948269035084824"></a><a name="b948269035084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row191249063084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2041032329084824"><a name="p2041032329084824"></a><a name="p2041032329084824"></a><a href="math.md#ga33d95711621def731d3f88c4e606323e">llrintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p379914580084824"><a name="p379914580084824"></a><a name="p379914580084824"></a>long long int </p>
<p id="p849819352084824"><a name="p849819352084824"></a><a name="p849819352084824"></a>Rounds float value <strong id="b1675176374084824"><a name="b1675176374084824"></a><a name="b1675176374084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row99584107084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p411918046084824"><a name="p411918046084824"></a><a name="p411918046084824"></a><a href="math.md#ga20e0da115f76608eff4695177f2f605a">llrintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1605010025084824"><a name="p1605010025084824"></a><a name="p1605010025084824"></a>long long int </p>
<p id="p363477178084824"><a name="p363477178084824"></a><a name="p363477178084824"></a>Rounds long double value <strong id="b1051437560084824"><a name="b1051437560084824"></a><a name="b1051437560084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row2046107412084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p128294552084824"><a name="p128294552084824"></a><a name="p128294552084824"></a><a href="math.md#ga3e4957daeecea4e616ed1f1870fe4f31">llround</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p472895409084824"><a name="p472895409084824"></a><a name="p472895409084824"></a>long long int </p>
<p id="p406716840084824"><a name="p406716840084824"></a><a name="p406716840084824"></a>Rounds double value <strong id="b1533536394084824"><a name="b1533536394084824"></a><a name="b1533536394084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1547842527084824"><a name="b1547842527084824"></a><a name="b1547842527084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row197682615084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1397944063084824"><a name="p1397944063084824"></a><a name="p1397944063084824"></a><a href="math.md#ga8259999687e8bd4b5509ca0d69b0ad9d">llroundf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1508259253084824"><a name="p1508259253084824"></a><a name="p1508259253084824"></a>long long int </p>
<p id="p118568649084824"><a name="p118568649084824"></a><a name="p118568649084824"></a>Rounds float value <strong id="b221741796084824"><a name="b221741796084824"></a><a name="b221741796084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1052635537084824"><a name="b1052635537084824"></a><a name="b1052635537084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1333760660084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1920940084084824"><a name="p1920940084084824"></a><a name="p1920940084084824"></a><a href="math.md#ga82a6d70a29e839514b93bb0699f07bbe">llroundl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p933534162084824"><a name="p933534162084824"></a><a name="p933534162084824"></a>long long int </p>
<p id="p1294064518084824"><a name="p1294064518084824"></a><a name="p1294064518084824"></a>Rounds long double value <strong id="b1964734184084824"><a name="b1964734184084824"></a><a name="b1964734184084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1367926341084824"><a name="b1367926341084824"></a><a name="b1367926341084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1288705256084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1987050298084824"><a name="p1987050298084824"></a><a name="p1987050298084824"></a><a href="math.md#gadb302c9aafbaa5e180d9f60ee954bb82">log</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526447947084824"><a name="p1526447947084824"></a><a name="p1526447947084824"></a>double </p>
<p id="p925239935084824"><a name="p925239935084824"></a><a name="p925239935084824"></a>Calculates the natural logarithm of the double value <strong id="b2139679596084824"><a name="b2139679596084824"></a><a name="b2139679596084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row295013311084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p257651172084824"><a name="p257651172084824"></a><a name="p257651172084824"></a><a href="math.md#ga8246b3e17a39b137d0c62670d0c6e336">logf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1590044973084824"><a name="p1590044973084824"></a><a name="p1590044973084824"></a>float </p>
<p id="p1388334991084824"><a name="p1388334991084824"></a><a name="p1388334991084824"></a>Calculates the natural logarithm of the float value <strong id="b589712805084824"><a name="b589712805084824"></a><a name="b589712805084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row239589933084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61627928084824"><a name="p61627928084824"></a><a name="p61627928084824"></a><a href="math.md#gaf67da1c28ce33b403f955103f201dfb8">logl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391835596084824"><a name="p1391835596084824"></a><a name="p1391835596084824"></a>long double </p>
<p id="p20349010084824"><a name="p20349010084824"></a><a name="p20349010084824"></a>Calculates the natural logarithm of the long double value <strong id="b2076196825084824"><a name="b2076196825084824"></a><a name="b2076196825084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row718026522084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1728731883084824"><a name="p1728731883084824"></a><a name="p1728731883084824"></a><a href="math.md#ga6572e82a4891917a9ba7fb2a964f8182">log10</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1001380608084824"><a name="p1001380608084824"></a><a name="p1001380608084824"></a>double </p>
<p id="p243178005084824"><a name="p243178005084824"></a><a name="p243178005084824"></a>Calculates the common logarithm (logarithm with base 10) of the double value <strong id="b77857779084824"><a name="b77857779084824"></a><a name="b77857779084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row779686134084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274266625084824"><a name="p274266625084824"></a><a name="p274266625084824"></a><a href="math.md#gae207b1eb007a6c23394dcb6fc7f16adf">log10f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703943546084824"><a name="p1703943546084824"></a><a name="p1703943546084824"></a>float </p>
<p id="p1700422533084824"><a name="p1700422533084824"></a><a name="p1700422533084824"></a>Calculates the common logarithm (logarithm with base 10) of the float value <strong id="b867455826084824"><a name="b867455826084824"></a><a name="b867455826084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1084506654084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301460484084824"><a name="p301460484084824"></a><a name="p301460484084824"></a><a href="math.md#gae824e49a04221dcf66b9791c5df8d6b6">log10l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705557600084824"><a name="p1705557600084824"></a><a name="p1705557600084824"></a>long double </p>
<p id="p857156929084824"><a name="p857156929084824"></a><a name="p857156929084824"></a>Calculates the common logarithm (logarithm with base 10) of the long double value <strong id="b824649853084824"><a name="b824649853084824"></a><a name="b824649853084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row223129994084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p400763490084824"><a name="p400763490084824"></a><a name="p400763490084824"></a><a href="math.md#gac2aac20ab1347498e6e4f209148fea84">log1p</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1097170511084824"><a name="p1097170511084824"></a><a name="p1097170511084824"></a>double </p>
<p id="p1337259274084824"><a name="p1337259274084824"></a><a name="p1337259274084824"></a>Calculates the natural logarithm of one plus the double value <strong id="b1867460704084824"><a name="b1867460704084824"></a><a name="b1867460704084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row153108348084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p969079624084824"><a name="p969079624084824"></a><a name="p969079624084824"></a><a href="math.md#gacbf820b74779ce35a3c726a3a62bc8ef">log1pf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p312618863084824"><a name="p312618863084824"></a><a name="p312618863084824"></a>float </p>
<p id="p1154031182084824"><a name="p1154031182084824"></a><a name="p1154031182084824"></a>Calculates the natural logarithm of one plus the float value <strong id="b905327822084824"><a name="b905327822084824"></a><a name="b905327822084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row709340547084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p729662113084824"><a name="p729662113084824"></a><a name="p729662113084824"></a><a href="math.md#ga2a632effaace01f30cba42725ae48dfa">log1pl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370805662084824"><a name="p370805662084824"></a><a name="p370805662084824"></a>long double </p>
<p id="p936994333084824"><a name="p936994333084824"></a><a name="p936994333084824"></a>Calculates the natural logarithm of one plus the long double value <strong id="b1678890010084824"><a name="b1678890010084824"></a><a name="b1678890010084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1712353853084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p406316459084824"><a name="p406316459084824"></a><a name="p406316459084824"></a><a href="math.md#ga38bd88274dc5594b4826fd60c8054c8e">log2</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p589447234084824"><a name="p589447234084824"></a><a name="p589447234084824"></a>double </p>
<p id="p1132672175084824"><a name="p1132672175084824"></a><a name="p1132672175084824"></a>Calculates the binary logarithm (logarithm with base 2) of the double value <strong id="b1963750755084824"><a name="b1963750755084824"></a><a name="b1963750755084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2144821203084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245462490084824"><a name="p1245462490084824"></a><a name="p1245462490084824"></a><a href="math.md#ga79fe62234001b88317245f7599158aaf">log2f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512720987084824"><a name="p1512720987084824"></a><a name="p1512720987084824"></a>float </p>
<p id="p1408284073084824"><a name="p1408284073084824"></a><a name="p1408284073084824"></a>Calculates the binary logarithm (logarithm with base 2) of the float value <strong id="b732323640084824"><a name="b732323640084824"></a><a name="b732323640084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1246034064084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1176235553084824"><a name="p1176235553084824"></a><a name="p1176235553084824"></a><a href="math.md#gaa383ae0cab6c24f1bcba661dee0fbd70">log2l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666380387084824"><a name="p1666380387084824"></a><a name="p1666380387084824"></a>long double </p>
<p id="p2066845312084824"><a name="p2066845312084824"></a><a name="p2066845312084824"></a>Calculates the binary logarithm (logarithm with base 2) of the long double value <strong id="b494733832084824"><a name="b494733832084824"></a><a name="b494733832084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1417730022084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p281313478084824"><a name="p281313478084824"></a><a name="p281313478084824"></a><a href="math.md#gaa34bf5be5c3dab058c532adc2792113c">logb</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146092277084824"><a name="p1146092277084824"></a><a name="p1146092277084824"></a>double </p>
<p id="p1210403466084824"><a name="p1210403466084824"></a><a name="p1210403466084824"></a>Calculates the logarithm of the absolute value of the double value <strong id="b1120453396084824"><a name="b1120453396084824"></a><a name="b1120453396084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row124204668084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351016335084824"><a name="p351016335084824"></a><a name="p351016335084824"></a><a href="math.md#ga6939b8381c2f160d26913646ca7ab6c4">logbf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586978190084824"><a name="p1586978190084824"></a><a name="p1586978190084824"></a>float </p>
<p id="p1490829948084824"><a name="p1490829948084824"></a><a name="p1490829948084824"></a>Calculates the logarithm of the absolute value of the float value <strong id="b1891445273084824"><a name="b1891445273084824"></a><a name="b1891445273084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row864619343084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1635584033084824"><a name="p1635584033084824"></a><a name="p1635584033084824"></a><a href="math.md#ga2f9c0448126d1a838624e3460217bb84">logbl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2107031131084824"><a name="p2107031131084824"></a><a name="p2107031131084824"></a>long double </p>
<p id="p1970843841084824"><a name="p1970843841084824"></a><a name="p1970843841084824"></a>Calculates the logarithm of the absolute value of the long double value <strong id="b1572592091084824"><a name="b1572592091084824"></a><a name="b1572592091084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2030501799084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1745298738084824"><a name="p1745298738084824"></a><a name="p1745298738084824"></a><a href="math.md#ga3337db086394bad101bd8d42d891640a">lrint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p212539316084824"><a name="p212539316084824"></a><a name="p212539316084824"></a>long int </p>
<p id="p320838315084824"><a name="p320838315084824"></a><a name="p320838315084824"></a>Rounds the double value <strong id="b1200020104084824"><a name="b1200020104084824"></a><a name="b1200020104084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row886884385084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p998156030084824"><a name="p998156030084824"></a><a name="p998156030084824"></a><a href="math.md#ga16173bca19eef93d0230bfb7c86b5740">lrintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p165581719084824"><a name="p165581719084824"></a><a name="p165581719084824"></a>long int </p>
<p id="p203148579084824"><a name="p203148579084824"></a><a name="p203148579084824"></a>Rounds the float value <strong id="b14563603084824"><a name="b14563603084824"></a><a name="b14563603084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row772724183084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1427519318084824"><a name="p1427519318084824"></a><a name="p1427519318084824"></a><a href="math.md#gac6d217e9b96a145f5eeb2a490e6496e6">lrintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2106095026084824"><a name="p2106095026084824"></a><a name="p2106095026084824"></a>long int </p>
<p id="p1838621664084824"><a name="p1838621664084824"></a><a name="p1838621664084824"></a>Rounds the long double value <strong id="b632672308084824"><a name="b632672308084824"></a><a name="b632672308084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row1872290080084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2055879395084824"><a name="p2055879395084824"></a><a name="p2055879395084824"></a><a href="math.md#ga5936ef27aa03815e9c17d557e87a33d7">lround</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2093478206084824"><a name="p2093478206084824"></a><a name="p2093478206084824"></a>long int </p>
<p id="p1922204837084824"><a name="p1922204837084824"></a><a name="p1922204837084824"></a>Rounds double value <strong id="b922828431084824"><a name="b922828431084824"></a><a name="b922828431084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1832492647084824"><a name="b1832492647084824"></a><a name="b1832492647084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1024025802084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1582433863084824"><a name="p1582433863084824"></a><a name="p1582433863084824"></a><a href="math.md#ga0136619b503ddb8ce1a226cd34c9538c">lroundf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1587824390084824"><a name="p1587824390084824"></a><a name="p1587824390084824"></a>long int </p>
<p id="p1290716145084824"><a name="p1290716145084824"></a><a name="p1290716145084824"></a>Rounds the float value <strong id="b1893377331084824"><a name="b1893377331084824"></a><a name="b1893377331084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b2145845712084824"><a name="b2145845712084824"></a><a name="b2145845712084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1028856283084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p781818253084824"><a name="p781818253084824"></a><a name="p781818253084824"></a><a href="math.md#gafa865c5b70c9311f0f8701a1af60c715">lroundl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p136207596084824"><a name="p136207596084824"></a><a name="p136207596084824"></a>long int </p>
<p id="p1958158349084824"><a name="p1958158349084824"></a><a name="p1958158349084824"></a>Rounds the long double value <strong id="b1805287438084824"><a name="b1805287438084824"></a><a name="b1805287438084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b2052317571084824"><a name="b2052317571084824"></a><a name="b2052317571084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1602288495084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1260137129084824"><a name="p1260137129084824"></a><a name="p1260137129084824"></a><a href="math.md#gafcfe25b77e975450988866fea9d3c9f0">modf</a> (double x, double *iptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1797943264084824"><a name="p1797943264084824"></a><a name="p1797943264084824"></a>double </p>
<p id="p743831862084824"><a name="p743831862084824"></a><a name="p743831862084824"></a>Breaks the double value <strong id="b1322968583084824"><a name="b1322968583084824"></a><a name="b1322968583084824"></a>x</strong> into a signed integral and a fractional part. </p>
</td>
</tr>
<tr id="row1188508679084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106608473084824"><a name="p2106608473084824"></a><a name="p2106608473084824"></a><a href="math.md#gad8314f66dfe8603f3a166eb466261ce1">modff</a> (float x, float *iptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2127162107084824"><a name="p2127162107084824"></a><a name="p2127162107084824"></a>float </p>
<p id="p1540035021084824"><a name="p1540035021084824"></a><a name="p1540035021084824"></a>Breaks the float value <strong id="b86729934084824"><a name="b86729934084824"></a><a name="b86729934084824"></a>x</strong> into a signed integral and a fractional part. </p>
</td>
</tr>
<tr id="row911008429084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164762725084824"><a name="p164762725084824"></a><a name="p164762725084824"></a><a href="math.md#gabacf3b74f8d7e30a70da8ae47c8e4e3e">modfl</a> (long double x, long double *iptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330962980084824"><a name="p330962980084824"></a><a name="p330962980084824"></a>long double </p>
<p id="p722590988084824"><a name="p722590988084824"></a><a name="p722590988084824"></a>Breaks the long double value <strong id="b168655283084824"><a name="b168655283084824"></a><a name="b168655283084824"></a>x</strong> into a signed integral and a fractional part. </p>
</td>
</tr>
<tr id="row1587286996084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1752091519084824"><a name="p1752091519084824"></a><a name="p1752091519084824"></a><a href="math.md#gaa4ee2f416f261bbd71cda3193c4884c9">nan</a> (const char *tagp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842738747084824"><a name="p842738747084824"></a><a name="p842738747084824"></a>double </p>
<p id="p1874268085084824"><a name="p1874268085084824"></a><a name="p1874268085084824"></a>Obtains a quiet NaN value of the double type. </p>
</td>
</tr>
<tr id="row2026132128084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p708929213084824"><a name="p708929213084824"></a><a name="p708929213084824"></a><a href="math.md#ga7fe43d4c86419daea2c133e8c5c1a17d">nanf</a> (const char *tagp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p585975306084824"><a name="p585975306084824"></a><a name="p585975306084824"></a>float </p>
<p id="p898766208084824"><a name="p898766208084824"></a><a name="p898766208084824"></a>Obtains a quiet NaN value of the float type. </p>
</td>
</tr>
<tr id="row873017485084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1570078912084824"><a name="p1570078912084824"></a><a name="p1570078912084824"></a><a href="math.md#gac92b1a3a1073a630ae0b7084e596d40f">nanl</a> (const char *tagp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p326889764084824"><a name="p326889764084824"></a><a name="p326889764084824"></a>long double </p>
<p id="p329734032084824"><a name="p329734032084824"></a><a name="p329734032084824"></a>Obtains a quiet NaN value of the long double type. </p>
</td>
</tr>
<tr id="row301200695084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p387413699084824"><a name="p387413699084824"></a><a name="p387413699084824"></a><a href="math.md#ga61ba6b3078ccbd5aac518e6ca2a757bd">nearbyint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596209230084824"><a name="p596209230084824"></a><a name="p596209230084824"></a>double </p>
<p id="p1469597499084824"><a name="p1469597499084824"></a><a name="p1469597499084824"></a>Rounds the double value <strong id="b301658912084824"><a name="b301658912084824"></a><a name="b301658912084824"></a>x</strong> to an integer in floating-point format. </p>
</td>
</tr>
<tr id="row490309506084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p495763504084824"><a name="p495763504084824"></a><a name="p495763504084824"></a><a href="math.md#gab3be3fdcb83a6d7cbd10aa5d891f88bf">nearbyintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375598086084824"><a name="p375598086084824"></a><a name="p375598086084824"></a>float </p>
<p id="p697885477084824"><a name="p697885477084824"></a><a name="p697885477084824"></a>Rounds the float value <strong id="b1232414875084824"><a name="b1232414875084824"></a><a name="b1232414875084824"></a>x</strong> to an integer in floating-point format. </p>
</td>
</tr>
<tr id="row1084634324084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p675367132084824"><a name="p675367132084824"></a><a name="p675367132084824"></a><a href="math.md#ga4b51faf338f7d4f31224d0c096a8859b">nearbyintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p476647651084824"><a name="p476647651084824"></a><a name="p476647651084824"></a>long double </p>
<p id="p786691256084824"><a name="p786691256084824"></a><a name="p786691256084824"></a>Rounds the long double value <strong id="b1577087378084824"><a name="b1577087378084824"></a><a name="b1577087378084824"></a>x</strong> to an integer in floating-point format. </p>
</td>
</tr>
<tr id="row1011182246084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226588336084824"><a name="p226588336084824"></a><a name="p226588336084824"></a><a href="math.md#gabed1b7ee913471448c2dbe58dff28db3">nextafter</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p575752276084824"><a name="p575752276084824"></a><a name="p575752276084824"></a>double </p>
<p id="p1492509076084824"><a name="p1492509076084824"></a><a name="p1492509076084824"></a>Obtains the next representable value following the double value <strong id="b787276773084824"><a name="b787276773084824"></a><a name="b787276773084824"></a>x</strong> in the direction of the double value <strong id="b635082172084824"><a name="b635082172084824"></a><a name="b635082172084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1850108989084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1979725836084824"><a name="p1979725836084824"></a><a name="p1979725836084824"></a><a href="math.md#ga57d2446286a54227595950a2118b349b">nextafterf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124797014084824"><a name="p1124797014084824"></a><a name="p1124797014084824"></a>float </p>
<p id="p1974366098084824"><a name="p1974366098084824"></a><a name="p1974366098084824"></a>Obtains the next representable value following the float value <strong id="b811867505084824"><a name="b811867505084824"></a><a name="b811867505084824"></a>x</strong> in the direction of the float value <strong id="b1942855155084824"><a name="b1942855155084824"></a><a name="b1942855155084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1151565400084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p745552606084824"><a name="p745552606084824"></a><a name="p745552606084824"></a><a href="math.md#ga38691f2f734e77206e4336cdcddd0e5b">nextafterl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2095047925084824"><a name="p2095047925084824"></a><a name="p2095047925084824"></a>long double </p>
<p id="p557243605084824"><a name="p557243605084824"></a><a name="p557243605084824"></a>Obtains the next representable value following the long double value <strong id="b1722162982084824"><a name="b1722162982084824"></a><a name="b1722162982084824"></a>x</strong> in the direction of the long double value <strong id="b1508577796084824"><a name="b1508577796084824"></a><a name="b1508577796084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row627880234084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p941701866084824"><a name="p941701866084824"></a><a name="p941701866084824"></a><a href="math.md#gaeb7afe6d08d8daec35aa282c63d7647e">nexttoward</a> (double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p875405506084824"><a name="p875405506084824"></a><a name="p875405506084824"></a>double </p>
<p id="p589192340084824"><a name="p589192340084824"></a><a name="p589192340084824"></a>Obtains the next representable value following the double value <strong id="b1690052672084824"><a name="b1690052672084824"></a><a name="b1690052672084824"></a>x</strong> in the direction of the long double value <strong id="b115963075084824"><a name="b115963075084824"></a><a name="b115963075084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row178033606084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367976621084824"><a name="p1367976621084824"></a><a name="p1367976621084824"></a><a href="math.md#ga634a1dabb08aa5a4fa6897920eff3c1d">nexttowardf</a> (float x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p254021148084824"><a name="p254021148084824"></a><a name="p254021148084824"></a>float </p>
<p id="p316866081084824"><a name="p316866081084824"></a><a name="p316866081084824"></a>Obtains the next representable value following the float value <strong id="b1519694311084824"><a name="b1519694311084824"></a><a name="b1519694311084824"></a>x</strong> in the direction of the long double value <strong id="b1268745624084824"><a name="b1268745624084824"></a><a name="b1268745624084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row104001198084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1565865760084824"><a name="p1565865760084824"></a><a name="p1565865760084824"></a><a href="math.md#ga3930cfe4df009d7221db329b910d6e30">nexttowardl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1498154704084824"><a name="p1498154704084824"></a><a name="p1498154704084824"></a>long double </p>
<p id="p1253422719084824"><a name="p1253422719084824"></a><a name="p1253422719084824"></a>Obtains the next representable value following the long double value <strong id="b1505937881084824"><a name="b1505937881084824"></a><a name="b1505937881084824"></a>x</strong> in the direction of the long double value <strong id="b393558249084824"><a name="b393558249084824"></a><a name="b393558249084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row895680238084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712024614084824"><a name="p1712024614084824"></a><a name="p1712024614084824"></a><a href="math.md#gaa56c9494c95edf68386375e97d64159b">pow</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1497741815084824"><a name="p1497741815084824"></a><a name="p1497741815084824"></a>double </p>
<p id="p826643356084824"><a name="p826643356084824"></a><a name="p826643356084824"></a>Obtains the double value <strong id="b1449505888084824"><a name="b1449505888084824"></a><a name="b1449505888084824"></a>x</strong> raised to the power of the double value <strong id="b1128702441084824"><a name="b1128702441084824"></a><a name="b1128702441084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row16091906084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p277739491084824"><a name="p277739491084824"></a><a name="p277739491084824"></a><a href="math.md#gac6b287549be087f6f0bf03b6fe30499e">powf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1899655589084824"><a name="p1899655589084824"></a><a name="p1899655589084824"></a>float </p>
<p id="p2081907036084824"><a name="p2081907036084824"></a><a name="p2081907036084824"></a>Obtains the float value <strong id="b353569517084824"><a name="b353569517084824"></a><a name="b353569517084824"></a>x</strong> raised to the power of the float value <strong id="b55610552084824"><a name="b55610552084824"></a><a name="b55610552084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row502445444084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497945497084824"><a name="p1497945497084824"></a><a name="p1497945497084824"></a><a href="math.md#gab6a77d7e1f713b898ceb3b945a2420b5">powf10</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202738239084824"><a name="p1202738239084824"></a><a name="p1202738239084824"></a>float </p>
<p id="p1272585269084824"><a name="p1272585269084824"></a><a name="p1272585269084824"></a>Calculates the xth power of 10. </p>
</td>
</tr>
<tr id="row2002863743084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344282980084824"><a name="p344282980084824"></a><a name="p344282980084824"></a><a href="math.md#ga2f4830e468138e1513b55ca6a92a0f9a">powl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1667779151084824"><a name="p1667779151084824"></a><a name="p1667779151084824"></a>long double </p>
<p id="p603377433084824"><a name="p603377433084824"></a><a name="p603377433084824"></a>Obtains the long double value <strong id="b1952130542084824"><a name="b1952130542084824"></a><a name="b1952130542084824"></a>x</strong> raised to the power of the long double value <strong id="b1378514649084824"><a name="b1378514649084824"></a><a name="b1378514649084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row914022447084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1385741625084824"><a name="p1385741625084824"></a><a name="p1385741625084824"></a><a href="math.md#ga532525cfd5b2a8ce221f1b13a7009376">powl10</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226976386084824"><a name="p1226976386084824"></a><a name="p1226976386084824"></a>long double </p>
<p id="p358662573084824"><a name="p358662573084824"></a><a name="p358662573084824"></a>Calculates the xth power of 10. </p>
</td>
</tr>
<tr id="row2023008002084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344981710084824"><a name="p344981710084824"></a><a name="p344981710084824"></a><a href="math.md#gaf7df01c4a9038dbf3562b41bc8c3be03">remainder</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923160602084824"><a name="p923160602084824"></a><a name="p923160602084824"></a>double </p>
<p id="p924676249084824"><a name="p924676249084824"></a><a name="p924676249084824"></a>Calculates the remainder of the double value <strong id="b151976498084824"><a name="b151976498084824"></a><a name="b151976498084824"></a>x</strong> divided by the double value <strong id="b44966642084824"><a name="b44966642084824"></a><a name="b44966642084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row160152538084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2054283635084824"><a name="p2054283635084824"></a><a name="p2054283635084824"></a><a href="math.md#ga370ff5cfa842822bfd8ea0a93d441a33">remainderf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813166577084824"><a name="p813166577084824"></a><a name="p813166577084824"></a>float </p>
<p id="p519512505084824"><a name="p519512505084824"></a><a name="p519512505084824"></a>Calculates the remainder of the float value <strong id="b1659811807084824"><a name="b1659811807084824"></a><a name="b1659811807084824"></a>x</strong> divided by the float value <strong id="b1596522268084824"><a name="b1596522268084824"></a><a name="b1596522268084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row129791217084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687288097084824"><a name="p687288097084824"></a><a name="p687288097084824"></a><a href="math.md#gabadbe61e166bbf3031b979661f0e8336">remainderl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575206169084824"><a name="p1575206169084824"></a><a name="p1575206169084824"></a>long double </p>
<p id="p1378221618084824"><a name="p1378221618084824"></a><a name="p1378221618084824"></a>Calculates the remainder of the long double value <strong id="b1063710220084824"><a name="b1063710220084824"></a><a name="b1063710220084824"></a>x</strong> divided by the long double value <strong id="b942906973084824"><a name="b942906973084824"></a><a name="b942906973084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row11581010084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091810789084824"><a name="p2091810789084824"></a><a name="p2091810789084824"></a><a href="math.md#gac836dc6a979229173eb3d6e2744d82de">remquo</a> (double x, double y, int *quo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1149953385084824"><a name="p1149953385084824"></a><a name="p1149953385084824"></a>double </p>
<p id="p1500158083084824"><a name="p1500158083084824"></a><a name="p1500158083084824"></a>Calculates the quotient and remainder of the double value <strong id="b1151650568084824"><a name="b1151650568084824"></a><a name="b1151650568084824"></a>x</strong> divided by the double value <strong id="b1326909808084824"><a name="b1326909808084824"></a><a name="b1326909808084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row963445602084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p672237184084824"><a name="p672237184084824"></a><a name="p672237184084824"></a><a href="math.md#ga15ec704e1894cfa573ac37a65afe009a">remquof</a> (float x, float y, int *quo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19500873084824"><a name="p19500873084824"></a><a name="p19500873084824"></a>float </p>
<p id="p1688507161084824"><a name="p1688507161084824"></a><a name="p1688507161084824"></a>Calculates the quotient and remainder of the float value <strong id="b1605743925084824"><a name="b1605743925084824"></a><a name="b1605743925084824"></a>x</strong> divided by the float value <strong id="b458800892084824"><a name="b458800892084824"></a><a name="b458800892084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1254317695084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220355048084824"><a name="p1220355048084824"></a><a name="p1220355048084824"></a><a href="math.md#gaacadcc57a95279058f29e657dce4d285">remquol</a> (long double x, long double y, int *quo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p244551673084824"><a name="p244551673084824"></a><a name="p244551673084824"></a>long double </p>
<p id="p928360306084824"><a name="p928360306084824"></a><a name="p928360306084824"></a>Calculates the quotient and remainder of the long double value <strong id="b1637258089084824"><a name="b1637258089084824"></a><a name="b1637258089084824"></a>x</strong> divided by the long double value <strong id="b165923301084824"><a name="b165923301084824"></a><a name="b165923301084824"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1687945367084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003517769084824"><a name="p2003517769084824"></a><a name="p2003517769084824"></a><a href="math.md#gae1f9edd5049d3ff63b0373a3c15c38c1">rint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1888413322084824"><a name="p1888413322084824"></a><a name="p1888413322084824"></a>double </p>
<p id="p180091326084824"><a name="p180091326084824"></a><a name="p180091326084824"></a>Rounds the double value <strong id="b324839511084824"><a name="b324839511084824"></a><a name="b324839511084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row492031203084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101154009084824"><a name="p1101154009084824"></a><a name="p1101154009084824"></a><a href="math.md#ga48f9341b9310fefa5dd1b0c8c84c99df">rintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p879966655084824"><a name="p879966655084824"></a><a name="p879966655084824"></a>float </p>
<p id="p834905077084824"><a name="p834905077084824"></a><a name="p834905077084824"></a>Rounds the float value <strong id="b979204006084824"><a name="b979204006084824"></a><a name="b979204006084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row385865664084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p639159556084824"><a name="p639159556084824"></a><a name="p639159556084824"></a><a href="math.md#gaedc37bf10d69d2efa2a478f5f5d4b26b">rintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p219050357084824"><a name="p219050357084824"></a><a name="p219050357084824"></a>long double </p>
<p id="p1399045726084824"><a name="p1399045726084824"></a><a name="p1399045726084824"></a>Rounds the long double value <strong id="b1864609919084824"><a name="b1864609919084824"></a><a name="b1864609919084824"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row279725047084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049315492084824"><a name="p1049315492084824"></a><a name="p1049315492084824"></a><a href="math.md#ga7df19cf730447c00150569250a4b5e1d">round</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264803426084824"><a name="p264803426084824"></a><a name="p264803426084824"></a>double </p>
<p id="p636206094084824"><a name="p636206094084824"></a><a name="p636206094084824"></a>Rounds the double value <strong id="b1371312170084824"><a name="b1371312170084824"></a><a name="b1371312170084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1273428738084824"><a name="b1273428738084824"></a><a name="b1273428738084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row403659594084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1792097296084824"><a name="p1792097296084824"></a><a name="p1792097296084824"></a><a href="math.md#gade09185c0cf8101fa9e2f25c15041b81">roundf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785208621084824"><a name="p785208621084824"></a><a name="p785208621084824"></a>float </p>
<p id="p1662756942084824"><a name="p1662756942084824"></a><a name="p1662756942084824"></a>Rounds the float value <strong id="b1582497091084824"><a name="b1582497091084824"></a><a name="b1582497091084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1125259262084824"><a name="b1125259262084824"></a><a name="b1125259262084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row150493753084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1273260775084824"><a name="p1273260775084824"></a><a name="p1273260775084824"></a><a href="math.md#ga6565127c023ae8f392ce69e3b3f30aa1">roundl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673107911084824"><a name="p673107911084824"></a><a name="p673107911084824"></a>long double </p>
<p id="p1684723247084824"><a name="p1684723247084824"></a><a name="p1684723247084824"></a>Rounds the long double value <strong id="b1464297394084824"><a name="b1464297394084824"></a><a name="b1464297394084824"></a>x</strong> to the nearest integer, rounding away from <strong id="b1452655560084824"><a name="b1452655560084824"></a><a name="b1452655560084824"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1134397624084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468648478084824"><a name="p468648478084824"></a><a name="p468648478084824"></a><a href="math.md#ga947d3d0739c0dc7c46d1eec778d4b6af">scalbln</a> (double x, long int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1667404691084824"><a name="p1667404691084824"></a><a name="p1667404691084824"></a>double </p>
<p id="p986007624084824"><a name="p986007624084824"></a><a name="p986007624084824"></a>Multiplies the double value <strong id="b1198733642084824"><a name="b1198733642084824"></a><a name="b1198733642084824"></a>x</strong> by <strong id="b1108562839084824"><a name="b1108562839084824"></a><a name="b1108562839084824"></a>FLT_RADIX</strong> raised to the power of the long int value <strong id="b805378991084824"><a name="b805378991084824"></a><a name="b805378991084824"></a>exp</strong>, that is, <strong id="b1150483097084824"><a name="b1150483097084824"></a><a name="b1150483097084824"></a>x*(<strong id="b657832827084824"><a name="b657832827084824"></a><a name="b657832827084824"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row1325959187084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924347309084824"><a name="p924347309084824"></a><a name="p924347309084824"></a><a href="math.md#ga1aa3cc34e8f84a2a09400c25c578100d">scalblnf</a> (float x, long int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1613368841084824"><a name="p1613368841084824"></a><a name="p1613368841084824"></a>float </p>
<p id="p281527840084824"><a name="p281527840084824"></a><a name="p281527840084824"></a>Multiplies the float value <strong id="b491756421084824"><a name="b491756421084824"></a><a name="b491756421084824"></a>x</strong> by <strong id="b1552384355084824"><a name="b1552384355084824"></a><a name="b1552384355084824"></a>FLT_RADIX</strong> raised to the power of the long int value <strong id="b1379329587084824"><a name="b1379329587084824"></a><a name="b1379329587084824"></a>exp</strong>, that is, <strong id="b1387005052084824"><a name="b1387005052084824"></a><a name="b1387005052084824"></a>x*(<strong id="b1379759747084824"><a name="b1379759747084824"></a><a name="b1379759747084824"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row1911559704084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678864584084824"><a name="p678864584084824"></a><a name="p678864584084824"></a><a href="math.md#gaeb098df94536b520ced9df59fd353848">scalblnl</a> (long double x, long int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1451366927084824"><a name="p1451366927084824"></a><a name="p1451366927084824"></a>long double </p>
<p id="p532384632084824"><a name="p532384632084824"></a><a name="p532384632084824"></a>Multiplies the long double value <strong id="b1175894770084824"><a name="b1175894770084824"></a><a name="b1175894770084824"></a>x</strong> by <strong id="b1480435899084824"><a name="b1480435899084824"></a><a name="b1480435899084824"></a>FLT_RADIX</strong> raised to the power of the long int value <strong id="b1965312655084824"><a name="b1965312655084824"></a><a name="b1965312655084824"></a>exp</strong>, that is, <strong id="b1519359146084824"><a name="b1519359146084824"></a><a name="b1519359146084824"></a>x*(<strong id="b120364639084824"><a name="b120364639084824"></a><a name="b120364639084824"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row1062331283084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2128499223084824"><a name="p2128499223084824"></a><a name="p2128499223084824"></a><a href="math.md#gaa2fbea1fca1faaebedf2deec71c47189">scalbn</a> (double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1070302157084824"><a name="p1070302157084824"></a><a name="p1070302157084824"></a>double </p>
<p id="p1339038979084824"><a name="p1339038979084824"></a><a name="p1339038979084824"></a>Multiplies the double value <strong id="b2029883650084824"><a name="b2029883650084824"></a><a name="b2029883650084824"></a>x</strong> by <strong id="b881744552084824"><a name="b881744552084824"></a><a name="b881744552084824"></a>FLT_RADIX</strong> raised to the power of the int value <strong id="b1455128996084824"><a name="b1455128996084824"></a><a name="b1455128996084824"></a>exp</strong>, that is, <strong id="b322728795084824"><a name="b322728795084824"></a><a name="b322728795084824"></a>x*(<strong id="b1071007514084824"><a name="b1071007514084824"></a><a name="b1071007514084824"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row419959976084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1502566432084824"><a name="p1502566432084824"></a><a name="p1502566432084824"></a><a href="math.md#ga3849b86bb2f39ebccb79b91745f7883f">scalbnf</a> (float x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194295234084824"><a name="p1194295234084824"></a><a name="p1194295234084824"></a>float </p>
<p id="p1034108053084824"><a name="p1034108053084824"></a><a name="p1034108053084824"></a>Multiplies the float value <strong id="b555734130084824"><a name="b555734130084824"></a><a name="b555734130084824"></a>x</strong> by <strong id="b1435917566084824"><a name="b1435917566084824"></a><a name="b1435917566084824"></a>FLT_RADIX</strong> raised to the power of the int value <strong id="b818656049084824"><a name="b818656049084824"></a><a name="b818656049084824"></a>exp</strong>, that is, <strong id="b515859675084824"><a name="b515859675084824"></a><a name="b515859675084824"></a>x*(<strong id="b1327638196084824"><a name="b1327638196084824"></a><a name="b1327638196084824"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row329800345084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p388025664084824"><a name="p388025664084824"></a><a name="p388025664084824"></a><a href="math.md#ga284717e9eceed5bc33389ce33170f907">scalbnl</a> (long double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701835925084824"><a name="p1701835925084824"></a><a name="p1701835925084824"></a>long double </p>
<p id="p291869745084824"><a name="p291869745084824"></a><a name="p291869745084824"></a>Multiplies the long double value <strong id="b2078476822084824"><a name="b2078476822084824"></a><a name="b2078476822084824"></a>x</strong> by <strong id="b976430383084824"><a name="b976430383084824"></a><a name="b976430383084824"></a>FLT_RADIX</strong> raised to the power of the int value <strong id="b718951236084824"><a name="b718951236084824"></a><a name="b718951236084824"></a>exp</strong>, that is, <strong id="b1808490630084824"><a name="b1808490630084824"></a><a name="b1808490630084824"></a>x*(<strong id="b34266546084824"><a name="b34266546084824"></a><a name="b34266546084824"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row1402739175084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p535776635084824"><a name="p535776635084824"></a><a name="p535776635084824"></a><a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1962223171084824"><a name="p1962223171084824"></a><a name="p1962223171084824"></a>double </p>
<p id="p1437317988084824"><a name="p1437317988084824"></a><a name="p1437317988084824"></a>Calculates the sine of the double value <strong id="b953589577084824"><a name="b953589577084824"></a><a name="b953589577084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row763327664084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242254617084824"><a name="p1242254617084824"></a><a name="p1242254617084824"></a><a href="math.md#ga8a7dc2a88e109f4e15b661247665709a">sinf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p998275672084824"><a name="p998275672084824"></a><a name="p998275672084824"></a>float </p>
<p id="p1380961637084824"><a name="p1380961637084824"></a><a name="p1380961637084824"></a>Calculates the sine of the float value <strong id="b1977471648084824"><a name="b1977471648084824"></a><a name="b1977471648084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1032830189084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p421816805084824"><a name="p421816805084824"></a><a name="p421816805084824"></a><a href="math.md#gaeb537bfea71fa91192234a666f3a6a25">sinl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p126791959084824"><a name="p126791959084824"></a><a name="p126791959084824"></a>long double </p>
<p id="p1357154052084824"><a name="p1357154052084824"></a><a name="p1357154052084824"></a>Calculates the sine of the long double value <strong id="b892621042084824"><a name="b892621042084824"></a><a name="b892621042084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row330801827084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p885185275084824"><a name="p885185275084824"></a><a name="p885185275084824"></a><a href="math.md#ga862012e970c977c482507064e2793b45">sinh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p145410118084824"><a name="p145410118084824"></a><a name="p145410118084824"></a>double </p>
<p id="p556801009084824"><a name="p556801009084824"></a><a name="p556801009084824"></a>Calculates the hyperbolic sine of the double value <strong id="b793566091084824"><a name="b793566091084824"></a><a name="b793566091084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1026252192084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288540853084824"><a name="p1288540853084824"></a><a name="p1288540853084824"></a><a href="math.md#ga1976c7577fb97800f4b926bd042b64ac">sinhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269049758084824"><a name="p269049758084824"></a><a name="p269049758084824"></a>float </p>
<p id="p315619186084824"><a name="p315619186084824"></a><a name="p315619186084824"></a>Calculates the hyperbolic sine of the float value <strong id="b1434914180084824"><a name="b1434914180084824"></a><a name="b1434914180084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row528907297084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205924751084824"><a name="p205924751084824"></a><a name="p205924751084824"></a><a href="math.md#gad160d5d1bb3f113e96135a4bebe76abe">sinhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959301273084824"><a name="p959301273084824"></a><a name="p959301273084824"></a>long double </p>
<p id="p728296343084824"><a name="p728296343084824"></a><a name="p728296343084824"></a>Calculates the hyperbolic sine of the long double value <strong id="b361077024084824"><a name="b361077024084824"></a><a name="b361077024084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1878996852084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1631928975084824"><a name="p1631928975084824"></a><a name="p1631928975084824"></a><a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746768572084824"><a name="p746768572084824"></a><a name="p746768572084824"></a>double </p>
<p id="p1038931803084824"><a name="p1038931803084824"></a><a name="p1038931803084824"></a>Calculates the square root of double value <strong id="b119337126084824"><a name="b119337126084824"></a><a name="b119337126084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1213642223084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472864480084824"><a name="p1472864480084824"></a><a name="p1472864480084824"></a><a href="math.md#ga46c9a8d40cde7c4d5ab40a67e55316bb">sqrtf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435049331084824"><a name="p1435049331084824"></a><a name="p1435049331084824"></a>float </p>
<p id="p566145897084824"><a name="p566145897084824"></a><a name="p566145897084824"></a>Calculates the square root of the float value <strong id="b766792271084824"><a name="b766792271084824"></a><a name="b766792271084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1514830784084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p886081069084824"><a name="p886081069084824"></a><a name="p886081069084824"></a><a href="math.md#ga9c028a87917b3bb9bba9e75f66cdbd43">sqrtl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223400885084824"><a name="p223400885084824"></a><a name="p223400885084824"></a>long double </p>
<p id="p323293861084824"><a name="p323293861084824"></a><a name="p323293861084824"></a>Calculates the square root of the long double value <strong id="b768178598084824"><a name="b768178598084824"></a><a name="b768178598084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1362954715084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1694011718084824"><a name="p1694011718084824"></a><a name="p1694011718084824"></a><a href="math.md#gaa48fdfd5eea5f4f9c33496402b9e4039">tan</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681063542084824"><a name="p1681063542084824"></a><a name="p1681063542084824"></a>double </p>
<p id="p1043238331084824"><a name="p1043238331084824"></a><a name="p1043238331084824"></a>Calculates the tangent of the double value <strong id="b776425619084824"><a name="b776425619084824"></a><a name="b776425619084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row914241336084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p628101622084824"><a name="p628101622084824"></a><a name="p628101622084824"></a><a href="math.md#ga67d5bfe80effce6adebf5fcbc5a7dae0">tanf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1558157737084824"><a name="p1558157737084824"></a><a name="p1558157737084824"></a>float </p>
<p id="p248138451084824"><a name="p248138451084824"></a><a name="p248138451084824"></a>Calculates the tangent of the float value <strong id="b953554592084824"><a name="b953554592084824"></a><a name="b953554592084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row160750658084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p797350501084824"><a name="p797350501084824"></a><a name="p797350501084824"></a><a href="math.md#ga2151fba6c1e9b4fa5d2af2dcb5c68b17">tanl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p485578848084824"><a name="p485578848084824"></a><a name="p485578848084824"></a>long double </p>
<p id="p1234900456084824"><a name="p1234900456084824"></a><a name="p1234900456084824"></a>Calculates the tangent of the long double value <strong id="b254585763084824"><a name="b254585763084824"></a><a name="b254585763084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1884818391084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1594229685084824"><a name="p1594229685084824"></a><a name="p1594229685084824"></a><a href="math.md#gaf85bcf153d7ae805733927f12329dac1">tanh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p614306390084824"><a name="p614306390084824"></a><a name="p614306390084824"></a>double </p>
<p id="p1861086112084824"><a name="p1861086112084824"></a><a name="p1861086112084824"></a>Calculates the hyperbolic tangent of the double value <strong id="b2088845398084824"><a name="b2088845398084824"></a><a name="b2088845398084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1669556483084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p81413118084824"><a name="p81413118084824"></a><a name="p81413118084824"></a><a href="math.md#ga74e8f87bb37a338d2cebbb6b1d696593">tanhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313520501084824"><a name="p313520501084824"></a><a name="p313520501084824"></a>float </p>
<p id="p408283004084824"><a name="p408283004084824"></a><a name="p408283004084824"></a>Calculates the hyperbolic tangent of the float value <strong id="b1347099797084824"><a name="b1347099797084824"></a><a name="b1347099797084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1422317509084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143773094084824"><a name="p143773094084824"></a><a name="p143773094084824"></a><a href="math.md#ga94ee8c57b6b2d0bc5466c75bea2bffcf">tanhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p587819028084824"><a name="p587819028084824"></a><a name="p587819028084824"></a>long double </p>
<p id="p1992096898084824"><a name="p1992096898084824"></a><a name="p1992096898084824"></a>Calculates the hyperbolic tangent of the long double value <strong id="b503330808084824"><a name="b503330808084824"></a><a name="b503330808084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1851143600084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1670100033084824"><a name="p1670100033084824"></a><a name="p1670100033084824"></a><a href="math.md#ga54afbf509eea5e9d6f9efdebc572339a">tgamma</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p88861355084824"><a name="p88861355084824"></a><a name="p88861355084824"></a>double </p>
<p id="p2048681776084824"><a name="p2048681776084824"></a><a name="p2048681776084824"></a>Calculates the gamma function of the double value <strong id="b722106499084824"><a name="b722106499084824"></a><a name="b722106499084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1643921263084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p120798755084824"><a name="p120798755084824"></a><a name="p120798755084824"></a><a href="math.md#ga2ab69de9110cc2c62ca78b5d20a3a3ae">tgammaf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357101662084824"><a name="p1357101662084824"></a><a name="p1357101662084824"></a>float </p>
<p id="p1222792743084824"><a name="p1222792743084824"></a><a name="p1222792743084824"></a>Calculates the gamma function of the float value <strong id="b1004113585084824"><a name="b1004113585084824"></a><a name="b1004113585084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1753591252084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753984032084824"><a name="p753984032084824"></a><a name="p753984032084824"></a><a href="math.md#ga8eff39a57115761c5025e08ff2e08c6a">tgammal</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p730285346084824"><a name="p730285346084824"></a><a name="p730285346084824"></a>long double </p>
<p id="p1412232452084824"><a name="p1412232452084824"></a><a name="p1412232452084824"></a>Calculates the gamma function of the long double value <strong id="b1431555725084824"><a name="b1431555725084824"></a><a name="b1431555725084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1390068029084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p627499351084824"><a name="p627499351084824"></a><a name="p627499351084824"></a><a href="math.md#ga82a151adfde56b28fa8a50355c4f2ff6">trunc</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p682308009084824"><a name="p682308009084824"></a><a name="p682308009084824"></a>double </p>
<p id="p2107011644084824"><a name="p2107011644084824"></a><a name="p2107011644084824"></a>Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the double value <strong id="b72718283084824"><a name="b72718283084824"></a><a name="b72718283084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2060873652084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1602268340084824"><a name="p1602268340084824"></a><a name="p1602268340084824"></a><a href="math.md#gaa8bb2049c170c9ac5b131fdba029991a">truncf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1307100375084824"><a name="p1307100375084824"></a><a name="p1307100375084824"></a>float </p>
<p id="p1612816390084824"><a name="p1612816390084824"></a><a name="p1612816390084824"></a>Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the float value <strong id="b1326146183084824"><a name="b1326146183084824"></a><a name="b1326146183084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row907400960084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1268003814084824"><a name="p1268003814084824"></a><a name="p1268003814084824"></a><a href="math.md#ga8f9695496a9bb839eb5f728b6bf0c856">truncl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510979223084824"><a name="p1510979223084824"></a><a name="p1510979223084824"></a>long double </p>
<p id="p1247160079084824"><a name="p1247160079084824"></a><a name="p1247160079084824"></a>Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the long double value <strong id="b2017849839084824"><a name="b2017849839084824"></a><a name="b2017849839084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1628467733084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334354491084824"><a name="p334354491084824"></a><a name="p334354491084824"></a><a href="math.md#gaffb00730a1127dee798137075951ae21">j0</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p970518039084824"><a name="p970518039084824"></a><a name="p970518039084824"></a>double </p>
<p id="p543690827084824"><a name="p543690827084824"></a><a name="p543690827084824"></a>Calculates the Bessel function of the first kind of order <strong id="b1588583711084824"><a name="b1588583711084824"></a><a name="b1588583711084824"></a>0</strong> for the double value <strong id="b585602719084824"><a name="b585602719084824"></a><a name="b585602719084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row923053251084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p751545658084824"><a name="p751545658084824"></a><a name="p751545658084824"></a><a href="math.md#ga8cac4aa70c418eba481417f1878b4cee">j1</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p490030216084824"><a name="p490030216084824"></a><a name="p490030216084824"></a>double </p>
<p id="p1808804867084824"><a name="p1808804867084824"></a><a name="p1808804867084824"></a>Calculates the Bessel function of the first kind of order <strong id="b1597176019084824"><a name="b1597176019084824"></a><a name="b1597176019084824"></a>1</strong> for the double value <strong id="b2129206560084824"><a name="b2129206560084824"></a><a name="b2129206560084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row139163709084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612430462084824"><a name="p612430462084824"></a><a name="p612430462084824"></a><a href="math.md#gadeff843dc8106ffda5caba6df44c591d">jn</a> (int n, double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715074341084824"><a name="p1715074341084824"></a><a name="p1715074341084824"></a>double </p>
<p id="p1883702625084824"><a name="p1883702625084824"></a><a name="p1883702625084824"></a>Calculates the Bessel function of the first kind of order <strong id="b248068423084824"><a name="b248068423084824"></a><a name="b248068423084824"></a>n</strong> for the double value <strong id="b1148268880084824"><a name="b1148268880084824"></a><a name="b1148268880084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1759100581084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p262995841084824"><a name="p262995841084824"></a><a name="p262995841084824"></a><a href="math.md#gafca57fd80386476e5cd1dd52173103c5">y0</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238221713084824"><a name="p1238221713084824"></a><a name="p1238221713084824"></a>double </p>
<p id="p1793831112084824"><a name="p1793831112084824"></a><a name="p1793831112084824"></a>Calculates the Bessel function of the second kind of order <strong id="b140640600084824"><a name="b140640600084824"></a><a name="b140640600084824"></a>0</strong> for the double value <strong id="b1883287550084824"><a name="b1883287550084824"></a><a name="b1883287550084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row187456689084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p377303462084824"><a name="p377303462084824"></a><a name="p377303462084824"></a><a href="math.md#ga369368526a105f3fba6776b11586070c">y1</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420384725084824"><a name="p420384725084824"></a><a name="p420384725084824"></a>double </p>
<p id="p1108027732084824"><a name="p1108027732084824"></a><a name="p1108027732084824"></a>Calculates the Bessel function of the second kind of order <strong id="b1874776007084824"><a name="b1874776007084824"></a><a name="b1874776007084824"></a>1</strong> for the double value <strong id="b1202662541084824"><a name="b1202662541084824"></a><a name="b1202662541084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row325451441084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1125304765084824"><a name="p1125304765084824"></a><a name="p1125304765084824"></a><a href="math.md#gae31b4c8c6af724eaa73ad2ebce1aa3ce">yn</a> (int n, double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679329654084824"><a name="p1679329654084824"></a><a name="p1679329654084824"></a>double </p>
<p id="p2022229747084824"><a name="p2022229747084824"></a><a name="p2022229747084824"></a>Calculates the Bessel function of the second kind of order <strong id="b1917609351084824"><a name="b1917609351084824"></a><a name="b1917609351084824"></a>n</strong> for the double value <strong id="b1537111375084824"><a name="b1537111375084824"></a><a name="b1537111375084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2073935753084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1665241165084824"><a name="p1665241165084824"></a><a name="p1665241165084824"></a><a href="math.md#ga08e754462e6ec13bc05fd41cff9cdd4a">finite</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1556044565084824"><a name="p1556044565084824"></a><a name="p1556044565084824"></a>int </p>
<p id="p461120206084824"><a name="p461120206084824"></a><a name="p461120206084824"></a>Checks whether the double value <strong id="b173940319084824"><a name="b173940319084824"></a><a name="b173940319084824"></a>x</strong> is an infinity or a NaN value. </p>
</td>
</tr>
<tr id="row967570092084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996707868084824"><a name="p996707868084824"></a><a name="p996707868084824"></a><a href="math.md#gaea39ac813876c506f8c351e6c14a5cb7">finitef</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p982049593084824"><a name="p982049593084824"></a><a name="p982049593084824"></a>int </p>
<p id="p1163856250084824"><a name="p1163856250084824"></a><a name="p1163856250084824"></a>Checks whether the float value <strong id="b368712732084824"><a name="b368712732084824"></a><a name="b368712732084824"></a>x</strong> is an infinity or a NaN value. </p>
</td>
</tr>
<tr id="row1878524181084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p856564196084824"><a name="p856564196084824"></a><a name="p856564196084824"></a><a href="math.md#ga14db57dcd8982430d12219bbecd08a05">scalb</a> (double x, double <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780297082084824"><a name="p780297082084824"></a><a name="p780297082084824"></a>double </p>
<p id="p1284016554084824"><a name="p1284016554084824"></a><a name="p1284016554084824"></a>Multiplies the double value <strong id="b1838052143084824"><a name="b1838052143084824"></a><a name="b1838052143084824"></a>x</strong> by <strong id="b1196449954084824"><a name="b1196449954084824"></a><a name="b1196449954084824"></a>FLT_RADIX</strong> raised to the power of the double value <strong id="b970596666084824"><a name="b970596666084824"></a><a name="b970596666084824"></a>exp</strong>, that is, x*<strong id="b569450175084824"><a name="b569450175084824"></a><a name="b569450175084824"></a>FLT_RADIX</strong>^exp. </p>
</td>
</tr>
<tr id="row410887116084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p692106370084824"><a name="p692106370084824"></a><a name="p692106370084824"></a><a href="math.md#ga9c9db25d2ff9973e0d8638cf42df3999">scalbf</a> (float x, float <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445341094084824"><a name="p1445341094084824"></a><a name="p1445341094084824"></a>float </p>
<p id="p1319121757084824"><a name="p1319121757084824"></a><a name="p1319121757084824"></a>Multiplies the float value <strong id="b1680447098084824"><a name="b1680447098084824"></a><a name="b1680447098084824"></a>x</strong> by <strong id="b875412603084824"><a name="b875412603084824"></a><a name="b875412603084824"></a>FLT_RADIX</strong> raised to the power of the float value <strong id="b2094202148084824"><a name="b2094202148084824"></a><a name="b2094202148084824"></a>exp</strong>, that is, x*<strong id="b737725446084824"><a name="b737725446084824"></a><a name="b737725446084824"></a>FLT_RADIX</strong>^exp. </p>
</td>
</tr>
<tr id="row1437275094084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p965447981084824"><a name="p965447981084824"></a><a name="p965447981084824"></a><a href="math.md#gafad3bf1f77c516fb8891c72beb51640f">significand</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423367091084824"><a name="p423367091084824"></a><a name="p423367091084824"></a>double </p>
<p id="p440087917084824"><a name="p440087917084824"></a><a name="p440087917084824"></a>Obtains the significand of the double value <strong id="b15651050084824"><a name="b15651050084824"></a><a name="b15651050084824"></a>x</strong> scaled to the range [1,2). </p>
</td>
</tr>
<tr id="row2066925858084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237943514084824"><a name="p1237943514084824"></a><a name="p1237943514084824"></a><a href="math.md#gac57d7d88e1a9b57c9a129ee4d4a68c42">significandf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824087595084824"><a name="p1824087595084824"></a><a name="p1824087595084824"></a>float </p>
<p id="p134949323084824"><a name="p134949323084824"></a><a name="p134949323084824"></a>Obtains the significand of the float value <strong id="b1923670337084824"><a name="b1923670337084824"></a><a name="b1923670337084824"></a>x</strong> scaled to the range [1,2). </p>
</td>
</tr>
<tr id="row245212041084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p246485250084824"><a name="p246485250084824"></a><a name="p246485250084824"></a><a href="math.md#gafa59b98550749c27995dfb7c70e6783a">j0f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630057266084824"><a name="p630057266084824"></a><a name="p630057266084824"></a>float </p>
<p id="p5074730084824"><a name="p5074730084824"></a><a name="p5074730084824"></a>Calculates the Bessel function of the first kind of order <strong id="b130127133084824"><a name="b130127133084824"></a><a name="b130127133084824"></a>0</strong> for the float value <strong id="b854221850084824"><a name="b854221850084824"></a><a name="b854221850084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row712081083084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832174921084824"><a name="p832174921084824"></a><a name="p832174921084824"></a><a href="math.md#ga4b50bbed127a1c57940d600498a3c5c7">j1f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994811150084824"><a name="p1994811150084824"></a><a name="p1994811150084824"></a>float </p>
<p id="p818187632084824"><a name="p818187632084824"></a><a name="p818187632084824"></a>Calculates the Bessel function of the first kind of order <strong id="b1517452118084824"><a name="b1517452118084824"></a><a name="b1517452118084824"></a>1</strong> for the float value <strong id="b1199898341084824"><a name="b1199898341084824"></a><a name="b1199898341084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1191569317084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p92099273084824"><a name="p92099273084824"></a><a name="p92099273084824"></a><a href="math.md#gac3fcdfd92a775eed4ebd673d7da02525">jnf</a> (int n, float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823870255084824"><a name="p1823870255084824"></a><a name="p1823870255084824"></a>float </p>
<p id="p2095910597084824"><a name="p2095910597084824"></a><a name="p2095910597084824"></a>Calculates the Bessel function of the first kind of order <strong id="b1726188855084824"><a name="b1726188855084824"></a><a name="b1726188855084824"></a>n</strong> for the float value <strong id="b950108095084824"><a name="b950108095084824"></a><a name="b950108095084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row726622594084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1409310705084824"><a name="p1409310705084824"></a><a name="p1409310705084824"></a><a href="math.md#gaba3cd2d73c1ae75ec2d01ebb2dfc108c">y0f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078689467084824"><a name="p1078689467084824"></a><a name="p1078689467084824"></a>float </p>
<p id="p1180089417084824"><a name="p1180089417084824"></a><a name="p1180089417084824"></a>Calculates the Bessel function of the second kind of order <strong id="b295749380084824"><a name="b295749380084824"></a><a name="b295749380084824"></a>0</strong> for the float value <strong id="b270687581084824"><a name="b270687581084824"></a><a name="b270687581084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1315023867084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577605120084824"><a name="p577605120084824"></a><a name="p577605120084824"></a><a href="math.md#ga5f37c38e8985dafae6abca2d1782c160">y1f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635128328084824"><a name="p1635128328084824"></a><a name="p1635128328084824"></a>float </p>
<p id="p1291294929084824"><a name="p1291294929084824"></a><a name="p1291294929084824"></a>Calculates the Bessel function of the second kind of order <strong id="b174438469084824"><a name="b174438469084824"></a><a name="b174438469084824"></a>1</strong> for the float value <strong id="b807921715084824"><a name="b807921715084824"></a><a name="b807921715084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1847292024084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1211320061084824"><a name="p1211320061084824"></a><a name="p1211320061084824"></a><a href="math.md#ga47f8750942b731456dd7f2cbf5f55806">ynf</a> (int n, float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223926956084824"><a name="p1223926956084824"></a><a name="p1223926956084824"></a>float </p>
<p id="p1110753630084824"><a name="p1110753630084824"></a><a name="p1110753630084824"></a>Calculates the Bessel function of the second kind of order <strong id="b1848589891084824"><a name="b1848589891084824"></a><a name="b1848589891084824"></a>n</strong> for the float value <strong id="b1694757940084824"><a name="b1694757940084824"></a><a name="b1694757940084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1174895558084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112418695084824"><a name="p112418695084824"></a><a name="p112418695084824"></a><a href="math.md#ga278e86e217081a0268107f0d6876cb9b">lgammal_r</a> (long double x, int *signp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699859284084824"><a name="p699859284084824"></a><a name="p699859284084824"></a>long double </p>
<p id="p1338860006084824"><a name="p1338860006084824"></a><a name="p1338860006084824"></a>Calculates the natural logarithm of the absolute value of the gamma function of the double value <strong id="b935047012084824"><a name="b935047012084824"></a><a name="b935047012084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row684278394084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521800518084824"><a name="p521800518084824"></a><a name="p521800518084824"></a><a href="math.md#gaf4509ae544cecab0e9a61efdfccb7530">sincos</a> (double x, double *<a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a>, double *<a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1998300575084824"><a name="p1998300575084824"></a><a name="p1998300575084824"></a>void </p>
<p id="p270234887084824"><a name="p270234887084824"></a><a name="p270234887084824"></a>Calculates the sine and cosine of the double value <strong id="b365385233084824"><a name="b365385233084824"></a><a name="b365385233084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row672338654084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1041864863084824"><a name="p1041864863084824"></a><a name="p1041864863084824"></a><a href="math.md#gac59adab35511be68e92ad9013d63e866">sincosf</a> (float x, float *<a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a>, float *<a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851525473084824"><a name="p1851525473084824"></a><a name="p1851525473084824"></a>void </p>
<p id="p2015313941084824"><a name="p2015313941084824"></a><a name="p2015313941084824"></a>Calculates the sine and cosine of the float value <strong id="b321215645084824"><a name="b321215645084824"></a><a name="b321215645084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row91001228084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823210084824"><a name="p1823210084824"></a><a name="p1823210084824"></a><a href="math.md#gaf877b78dbe8e265bdf4b975dbc713482">sincosl</a> (long double x, long double *<a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a>, long double *<a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p151760669084824"><a name="p151760669084824"></a><a name="p151760669084824"></a>void </p>
<p id="p159813774084824"><a name="p159813774084824"></a><a name="p159813774084824"></a>Calculates the sine and cosine of the long double value <strong id="b170790529084824"><a name="b170790529084824"></a><a name="b170790529084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1478364315084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1745777824084824"><a name="p1745777824084824"></a><a name="p1745777824084824"></a><a href="math.md#gaea673cadd2aef111e2ee7a813776b768">exp10</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914924563084824"><a name="p1914924563084824"></a><a name="p1914924563084824"></a>double </p>
<p id="p345438440084824"><a name="p345438440084824"></a><a name="p345438440084824"></a>Calculates the base-10 exponential function of the double value <strong id="b1249540317084824"><a name="b1249540317084824"></a><a name="b1249540317084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row737724776084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p876634817084824"><a name="p876634817084824"></a><a name="p876634817084824"></a><a href="math.md#gad27f10a0e30a7fe130c18786bf097e4b">exp10f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720967110084824"><a name="p1720967110084824"></a><a name="p1720967110084824"></a>float </p>
<p id="p743165986084824"><a name="p743165986084824"></a><a name="p743165986084824"></a>Calculates the base-10 exponential function of the float value <strong id="b1540088364084824"><a name="b1540088364084824"></a><a name="b1540088364084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1880277864084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p458615804084824"><a name="p458615804084824"></a><a name="p458615804084824"></a><a href="math.md#ga28c11df4d7b29c9f59ac733fba51bece">exp10l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1607733690084824"><a name="p1607733690084824"></a><a name="p1607733690084824"></a>long double </p>
<p id="p1497039751084824"><a name="p1497039751084824"></a><a name="p1497039751084824"></a>Calculates the base-10 exponential function of the long double value <strong id="b627536302084824"><a name="b627536302084824"></a><a name="b627536302084824"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1335412088084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982387280084824"><a name="p982387280084824"></a><a name="p982387280084824"></a><a href="math.md#gafbbc60a3627a8de4845c7e99e6134ec8">pow10</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588471284084824"><a name="p1588471284084824"></a><a name="p1588471284084824"></a>double </p>
<p id="p1151948197084824"><a name="p1151948197084824"></a><a name="p1151948197084824"></a>Calculates the value of 10 raised to the power <strong id="b408326287084824"><a name="b408326287084824"></a><a name="b408326287084824"></a>x</strong>, which is a double value. </p>
</td>
</tr>
<tr id="row1741049231084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1878468165084824"><a name="p1878468165084824"></a><a name="p1878468165084824"></a><a href="math.md#ga2cb598503b85d66abf59e9da06478f1a">pow10f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1360503604084824"><a name="p1360503604084824"></a><a name="p1360503604084824"></a>float </p>
<p id="p498024462084824"><a name="p498024462084824"></a><a name="p498024462084824"></a>Calculates the value of 10 raised to the power <strong id="b271243435084824"><a name="b271243435084824"></a><a name="b271243435084824"></a>x</strong>, which is a float value. </p>
</td>
</tr>
<tr id="row1779975085084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179421196084824"><a name="p179421196084824"></a><a name="p179421196084824"></a><a href="math.md#ga9baf71e9033dd73a9c225a2fc9cca61d">pow10l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754592447084824"><a name="p754592447084824"></a><a name="p754592447084824"></a>long double </p>
<p id="p1485133329084824"><a name="p1485133329084824"></a><a name="p1485133329084824"></a>Calculates the value of 10 raised to the power <strong id="b373678619084824"><a name="b373678619084824"></a><a name="b373678619084824"></a>x</strong>, which is a long double value. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2068673837084824"></a>

## **Macro Definition Documentation**<a name="section526383883084824"></a>

## isfinite<a name="ga256d70a32c03904ce13c999c1e9dc35d"></a>

```
#define isfinite( x)
```

```
Values:( \

sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) < 0x7f800000 : \

sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL>>1) < 0x7ffULL<<52 : \

__fpclassifyl(x) > [FP_INFINITE](math.md#ga4f64bcc64f8b84dd9daf5a4e56abf0ca))


```

 **Description:**

Checks whether the floating-point value  **x**  is finite. 

A finite value is any value that is neither an infinity nor a NaN value. 

**Parameters:**

<a name="table212576941084824"></a>
<table><thead align="left"><tr id="row1815444040084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1410521821084824"><a name="p1410521821084824"></a><a name="p1410521821084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p42216642084824"><a name="p42216642084824"></a><a name="p42216642084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row18373668084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b687256725084824"><a name="b687256725084824"></a><a name="b687256725084824"></a>x</strong> to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **1**  if  **x**  is finite; returns  **0**  otherwise. 



## isgreater<a name="gada788e9d6ce0ca927874ec4e53af1f77"></a>

```
#define isgreater( x,  y )   __tg_pred_2(x, y, __isgreater)
```

 **Description:**

Checks whether floating-point value  **x**  is greater than  **y**. 

**Parameters:**

<a name="table1687647538084824"></a>
<table><thead align="left"><tr id="row589008141084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1896892808084824"><a name="p1896892808084824"></a><a name="p1896892808084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p248076846084824"><a name="p248076846084824"></a><a name="p248076846084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1713970777084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b2006784492084824"><a name="b2006784492084824"></a><a name="b2006784492084824"></a>x</strong> to check. </td>
</tr>
<tr id="row1913032966084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1819050117084824"><a name="b1819050117084824"></a><a name="b1819050117084824"></a>y</strong> to check. </td>
</tr>
</tbody>
</table>

**Attention:**

If either or both of  **x**  and  **y**  are a NaN value, an exception occurs. This function requires hardware support. 

**Returns:**

Returns  **1**  if  **x**  is greater than  **y**; returns  **0**  otherwise. 



## isgreaterequal<a name="ga5a7f86a4d3e6139e4913e2e8eba52612"></a>

```
#define isgreaterequal( x,  y )   __tg_pred_2(x, y, __isgreaterequal)
```

 **Description:**

Checks whether floating-point value  **x**  is greater than or equal to  **y**. 

**Parameters:**

<a name="table431906598084824"></a>
<table><thead align="left"><tr id="row1224101127084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1078531023084824"><a name="p1078531023084824"></a><a name="p1078531023084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1586501640084824"><a name="p1586501640084824"></a><a name="p1586501640084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row195579359084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1612534695084824"><a name="b1612534695084824"></a><a name="b1612534695084824"></a>x</strong> to check. </td>
</tr>
<tr id="row1632902407084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b610907561084824"><a name="b610907561084824"></a><a name="b610907561084824"></a>y</strong> to check. </td>
</tr>
</tbody>
</table>

**Attention:**

If either or both of  **x**  and  **y**  are a NaN value, an exception occurs. This function requires hardware support. 

**Returns:**

Returns  **1**  if  **x**  is greater than or equal to  **y**; returns  **0**  otherwise. 



## isinf<a name="ga2a266c767456556e5c0da234b602b18b"></a>

```
#define isinf( x)
```

```
Values:( \

sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) == 0x7f800000 : \

sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL>>1) == 0x7ffULL<<52 : \

__fpclassifyl(x) == [FP_INFINITE](math.md#ga4f64bcc64f8b84dd9daf5a4e56abf0ca))


```

 **Description:**

Checks whether the floating-point value  **x**  is an infinity. 

**Parameters:**

<a name="table669819912084824"></a>
<table><thead align="left"><tr id="row2143073249084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1523647317084824"><a name="p1523647317084824"></a><a name="p1523647317084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1190541340084824"><a name="p1190541340084824"></a><a name="p1190541340084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1113517560084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1052864606084824"><a name="b1052864606084824"></a><a name="b1052864606084824"></a>x</strong> to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **1**  if  **x**  is an infinity; returns  **0**  otherwise. 



## isless<a name="ga61079b32084130da4345c2eea93e0d61"></a>

```
#define isless( x,  y )   __tg_pred_2(x, y, __isless)
```

 **Description:**

Checks whether floating-point value  **x**  is less than  **y**. 

**Parameters:**

<a name="table1041714321084824"></a>
<table><thead align="left"><tr id="row524332973084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p655304141084824"><a name="p655304141084824"></a><a name="p655304141084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1436110221084824"><a name="p1436110221084824"></a><a name="p1436110221084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row788270221084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b517102429084824"><a name="b517102429084824"></a><a name="b517102429084824"></a>x</strong> to check. </td>
</tr>
<tr id="row1368487196084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b631354505084824"><a name="b631354505084824"></a><a name="b631354505084824"></a>y</strong> to check. </td>
</tr>
</tbody>
</table>

**Attention:**

If either or both of  **x**  and  **y**  are a NaN value, an exception occurs. This function requires hardware support. 

**Returns:**

Returns  **1**  if  **x**  is less than  **y**; returns  **0**  otherwise. 



## islessequal<a name="gabf3cb1e5a0aaa1c42dffa9ebb1d78c30"></a>

```
#define islessequal( x,  y )   __tg_pred_2(x, y, __islessequal)
```

 **Description:**

Checks whether floating-point value  **x**  is less than or equal to  **y**. 

**Parameters:**

<a name="table292435009084824"></a>
<table><thead align="left"><tr id="row1152805298084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1756913830084824"><a name="p1756913830084824"></a><a name="p1756913830084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1437593433084824"><a name="p1437593433084824"></a><a name="p1437593433084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1762965600084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1128398341084824"><a name="b1128398341084824"></a><a name="b1128398341084824"></a>x</strong> to check. </td>
</tr>
<tr id="row111615379084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1169668411084824"><a name="b1169668411084824"></a><a name="b1169668411084824"></a>y</strong> to check. </td>
</tr>
</tbody>
</table>

**Attention:**

If either or both of  **x**  and  **y**  are a NaN value, an exception occurs. This function requires hardware support. 

**Returns:**

Returns  **1**  if  **x**  is less than or equal to  **y**; returns  **0**  otherwise. 



## islessgreater<a name="ga5e534756b747fd2e9ee19f8fdd93b30b"></a>

```
#define islessgreater( x,  y )   __tg_pred_2(x, y, __islessgreater)
```

 **Description:**

Checks whether floating-point value  **x**  is either less than or greater than  **y**. 

**Parameters:**

<a name="table1358069765084824"></a>
<table><thead align="left"><tr id="row447990764084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1512368662084824"><a name="p1512368662084824"></a><a name="p1512368662084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1597262116084824"><a name="p1597262116084824"></a><a name="p1597262116084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1693110456084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1061989193084824"><a name="b1061989193084824"></a><a name="b1061989193084824"></a>x</strong> to check. </td>
</tr>
<tr id="row1727736914084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b2058263134084824"><a name="b2058263134084824"></a><a name="b2058263134084824"></a>y</strong> to check. </td>
</tr>
</tbody>
</table>

**Attention:**

If either or both of  **x**  and  **y**  are a NaN value, an exception occurs. This function requires hardware support. 

**Returns:**

Returns  **1**  if  **x**  is either less than or greater than  **y**; returns  **0**  otherwise. 



## isnan<a name="ga2e1baae9134e580910322362dc23290e"></a>

```
#define isnan( x)
```

```
Values:( \

sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) > 0x7f800000 : \

sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL>>1) > 0x7ffULL<<52 : \

__fpclassifyl(x) == [FP_NAN](math.md#ga1d481cc6e6a8ff729147ed46e61a4c9f))


```

 **Description:**

Checks whether the floating-point value  **x**  is a NaN value. 

**Parameters:**

<a name="table933525670084824"></a>
<table><thead align="left"><tr id="row246470603084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1659875705084824"><a name="p1659875705084824"></a><a name="p1659875705084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1645540471084824"><a name="p1645540471084824"></a><a name="p1645540471084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1099603962084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b521501008084824"><a name="b521501008084824"></a><a name="b521501008084824"></a>x</strong> to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a non-zero value if  **x**  is a NaN value; returns  **0**  otherwise. 



## isnormal<a name="gad83f5949c4b5d810225b9a834840bac9"></a>

```
#define isnormal( x)
```

```
Values:( \

sizeof(x) == sizeof(float) ? ((__FLOAT_BITS(x)+0x00800000) & 0x7fffffff) >= 0x01000000 : \

sizeof(x) == sizeof(double) ? ((__DOUBLE_BITS(x)+(1ULL<<52)) & -1ULL>>1) >= 1ULL<<53 : \

__fpclassifyl(x) == [FP_NORMAL](math.md#gab9e29bb9e853934c4ba647c840b7e5de))


```

 **Description:**

Checks whether the floating-point value  **x**  is a normal value. 

A normal value refers to any value that is not an infinity, a NaN value, or  **0**. 

**Parameters:**

<a name="table716474074084824"></a>
<table><thead align="left"><tr id="row32076750084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1028939611084824"><a name="p1028939611084824"></a><a name="p1028939611084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1931046168084824"><a name="p1931046168084824"></a><a name="p1931046168084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1305829321084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b896436298084824"><a name="b896436298084824"></a><a name="b896436298084824"></a>x</strong> to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a non-zero value if  **x**  is a normal value; returns  **0**  otherwise. 



## isunordered<a name="ga33daf51eb7138d477e0b0985c51e4fad"></a>

```
#define isunordered( x,  y )   ([isnan](math.md#ga2e1baae9134e580910322362dc23290e)((x)) ? ((void)(y),1) : [isnan](math.md#ga2e1baae9134e580910322362dc23290e)((y)))
```

 **Description:**

Checks whether floating-point value  **x**  or  **y**  is unordered. 

An unordered value refers to a NaN value. 

**Parameters:**

<a name="table970630895084824"></a>
<table><thead align="left"><tr id="row1549410334084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1676281495084824"><a name="p1676281495084824"></a><a name="p1676281495084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p292254033084824"><a name="p292254033084824"></a><a name="p292254033084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row333370355084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1958343406084824"><a name="b1958343406084824"></a><a name="b1958343406084824"></a>x</strong> to check. </td>
</tr>
<tr id="row556779225084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b983295660084824"><a name="b983295660084824"></a><a name="b983295660084824"></a>y</strong> to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **1**  if either  **x**  or  **y**  is unordered; returns  **0**  otherwise. 



## signbit<a name="gaa63ffa98f213f62e536b073c28cb3cd8"></a>

```
#define signbit( x)
```

```
Values:( \

sizeof(x) == sizeof(float) ? (int)(__FLOAT_BITS(x)>>31) : \

sizeof(x) == sizeof(double) ? (int)(__DOUBLE_BITS(x)>>63) : \

__signbitl(x) )


```

 **Description:**

Checks whether the sign of the floating-point value  **x**  is negative. 

**Parameters:**

<a name="table1107599889084824"></a>
<table><thead align="left"><tr id="row698726389084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1418071487084824"><a name="p1418071487084824"></a><a name="p1418071487084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p708581048084824"><a name="p708581048084824"></a><a name="p708581048084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row983380851084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point value <strong id="b1937521694084824"><a name="b1937521694084824"></a><a name="b1937521694084824"></a>x</strong> to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a non-zero value if the sign of  **x**  is negative; returns  **0**  otherwise. 



## **Function Documentation**<a name="section536345563084824"></a>

## acos\(\)<a name="gae93afe22ff34c79ee97ea3eaf77557db"></a>

```
double acos (double x)
```

 **Description:**

Calculates the arc cosine of the double value  **x**. 

**Parameters:**

<a name="table443819889084824"></a>
<table><thead align="left"><tr id="row972630180084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1144150819084824"><a name="p1144150819084824"></a><a name="p1144150819084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p915872528084824"><a name="p915872528084824"></a><a name="p915872528084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1964630528084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose arc cosine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc cosine of  **x**  in radians, ranging from 0 to  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+1**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a NaN value and reports a domain error. If  **x**  is out of the range \[-1, 1\], this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## acosf\(\)<a name="ga983a9e1aa7568df39153ea4d8e16653b"></a>

```
float acosf (float x)
```

 **Description:**

Calculates the arc cosine of the float value  **x**. 

**Parameters:**

<a name="table516997590084824"></a>
<table><thead align="left"><tr id="row210810779084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1496752484084824"><a name="p1496752484084824"></a><a name="p1496752484084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1155534117084824"><a name="p1155534117084824"></a><a name="p1155534117084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row194896400084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose arc cosine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc cosine of  **x**  in radians, ranging from 0 to  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+1**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a NaN value and reports a domain error. If  **x**  is out of the range \[-1, 1\], this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## acosh\(\)<a name="gac862445bcb46911b1782c284829d5e46"></a>

```
double acosh (double x)
```

 **Description:**

Calculates the inverse hyperbolic cosine of the double value  **x**. 

**Parameters:**

<a name="table1108631984084824"></a>
<table><thead align="left"><tr id="row268762059084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1258704317084824"><a name="p1258704317084824"></a><a name="p1258704317084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p791625953084824"><a name="p791625953084824"></a><a name="p791625953084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row169940241084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose inverse hyperbolic cosine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic cosine of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+1**, this function returns  **+0**. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is less than  **1**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## acoshf\(\)<a name="ga84cfd14c3432390f70b6233d24ad173b"></a>

```
float acoshf (float x)
```

 **Description:**

Calculates the inverse hyperbolic cosine of float value  **x**. 

**Parameters:**

<a name="table855360208084824"></a>
<table><thead align="left"><tr id="row1636600115084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p130071474084824"><a name="p130071474084824"></a><a name="p130071474084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p84416361084824"><a name="p84416361084824"></a><a name="p84416361084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row69263995084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose inverse hyperbolic cosine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic cosine of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+1**, this function returns  **+0**. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is less than  **1**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## acoshl\(\)<a name="ga104456314ba05665d6cbb805e823dd10"></a>

```
long double acoshl (long double x)
```

 **Description:**

Calculates the inverse hyperbolic cosine of the long double value  **x**. 

**Parameters:**

<a name="table857472496084824"></a>
<table><thead align="left"><tr id="row1270575034084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1786439994084824"><a name="p1786439994084824"></a><a name="p1786439994084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2089740279084824"><a name="p2089740279084824"></a><a name="p2089740279084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1647719801084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose inverse hyperbolic cosine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic cosine of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+1**, this function returns  **+0**. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is less than  **1**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## acosl\(\)<a name="gae84dc6cff92b3417098f16a1811635e4"></a>

```
long double acosl (long double x)
```

 **Description:**

Calculates the arc cosine of the long double value  **x**. 

**Parameters:**

<a name="table1388937007084824"></a>
<table><thead align="left"><tr id="row2091530505084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1389580318084824"><a name="p1389580318084824"></a><a name="p1389580318084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1254736443084824"><a name="p1254736443084824"></a><a name="p1254736443084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1467379346084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose arc cosine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc cosine of  **x**  in radians, ranging from 0 to  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+1**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a NaN value and reports a domain error. If  **x**  is out of the range \[-1, 1\], this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## asin\(\)<a name="gaa9528d92a3ae44ad6484da0774604454"></a>

```
double asin (double x)
```

 **Description:**

Calculates the arc sine of the double value  **x**. 

**Parameters:**

<a name="table1477048897084824"></a>
<table><thead align="left"><tr id="row451769897084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p931473731084824"><a name="p931473731084824"></a><a name="p931473731084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2073839737084824"><a name="p2073839737084824"></a><a name="p2073839737084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2146987060084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose arc sine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc sine of  **x**  in radians, ranging from -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  to  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**. If  **x**  is out of the range \[-1, 1\], this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## asinf\(\)<a name="ga7447a7400ca474ba42d127b04d6ee2b7"></a>

```
float asinf (float x)
```

 **Description:**

Calculates the arc sine of the float value  **x**. 

**Parameters:**

<a name="table712098817084824"></a>
<table><thead align="left"><tr id="row538856632084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p249769716084824"><a name="p249769716084824"></a><a name="p249769716084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2108898196084824"><a name="p2108898196084824"></a><a name="p2108898196084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2008110494084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose arc sine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc sine of  **x**  in radians, ranging from -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  to  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**. If  **x**  is out of the range \[-1, 1\], this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## asinh\(\)<a name="ga907297107e93ea9c8a0c8409a8e65079"></a>

```
double asinh (double x)
```

 **Description:**

Calculates the inverse hyperbolic sine of the double value  **x**. 

**Parameters:**

<a name="table470768107084824"></a>
<table><thead align="left"><tr id="row89630542084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p714986413084824"><a name="p714986413084824"></a><a name="p714986413084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p726584737084824"><a name="p726584737084824"></a><a name="p726584737084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2053673861084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose inverse hyperbolic sine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic sine of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. 



## asinhf\(\)<a name="ga1131c65ac49f31ed6774d27106c6394d"></a>

```
float asinhf (float x)
```

 **Description:**

Calculates the inverse hyperbolic sine of the float value  **x**. 

**Parameters:**

<a name="table173934397084824"></a>
<table><thead align="left"><tr id="row1014204654084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1542930630084824"><a name="p1542930630084824"></a><a name="p1542930630084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1547190406084824"><a name="p1547190406084824"></a><a name="p1547190406084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row996762060084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose inverse hyperbolic sine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic sine of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. 



## asinhl\(\)<a name="ga98df355372e19c11634992e4b7e35784"></a>

```
long double asinhl (long double x)
```

 **Description:**

Calculates the inverse hyperbolic sine of the long double value  **x**. 

**Parameters:**

<a name="table537934904084824"></a>
<table><thead align="left"><tr id="row203837050084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p917439981084824"><a name="p917439981084824"></a><a name="p917439981084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1373913876084824"><a name="p1373913876084824"></a><a name="p1373913876084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2131475455084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose inverse hyperbolic sine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic sine of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. 



## asinl\(\)<a name="ga3ace56b4f2a4a9364993a5af676793c5"></a>

```
long double asinl (long double x)
```

 **Description:**

Calculates the arc sine of the long double value  **x**. 

**Parameters:**

<a name="table283841473084824"></a>
<table><thead align="left"><tr id="row252428903084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1261078264084824"><a name="p1261078264084824"></a><a name="p1261078264084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p218763389084824"><a name="p218763389084824"></a><a name="p218763389084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row208953668084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose arc sine is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc sine of  **x**  in radians, ranging from -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  to  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**. If  **x**  is out of the range \[-1, 1\], this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## atan\(\)<a name="ga1e2f8f6d64eaa95131bc63fee34970ea"></a>

```
double atan (double x)
```

 **Description:**

Calculates the arc tangent of the double value  **x**. 

**Parameters:**

<a name="table1452693885084824"></a>
<table><thead align="left"><tr id="row154365267084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2128840082084824"><a name="p2128840082084824"></a><a name="p2128840082084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p876570556084824"><a name="p876570556084824"></a><a name="p876570556084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row427382734084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose arc tangent is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the principal value of the arc tangent of  **x**  in radians, ranging from -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  to  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). 



## atan2\(\)<a name="ga349377202ca14f79eb335b1a421fe4d8"></a>

```
double atan2 (double y, double x )
```

 **Description:**

Calculates the arc tangent of two double values  **x**  and  **y**. 

**Parameters:**

<a name="table1629150320084824"></a>
<table><thead align="left"><tr id="row1053113403084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p464953103084824"><a name="p464953103084824"></a><a name="p464953103084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1295896673084824"><a name="p1295896673084824"></a><a name="p1295896673084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1809894872084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1927402729084824"><a name="b1927402729084824"></a><a name="b1927402729084824"></a>y</strong> for calculating the arc tangent. </td>
</tr>
<tr id="row1093007070084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1021508039084824"><a name="b1021508039084824"></a><a name="b1021508039084824"></a>x</strong> for calculating the arc tangent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the principal value of the arc tangent of y/x in radians, ranging from  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  to  **[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**. If  **y**  is  **+0**  or  **-0**, and  **x**  is less than  **0**, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is  **+0**  or  **-0**, and  **x**  is greater than  **0**, this function returns  **+0**  or  **-0**, respectively. If  **y**  is less than  **0**  and  **x**  is either  **+0**  or  **-0**, this function returns  **-[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**. If  **y**  is greater than  **0**  and  **x**  is either  **+0**  or  **-0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **y**  is  **+0**  or  **-0**, and  **x**  is  **-0**, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is  **+0**  or  **-0**, and  **x**  is  **+0**, this function returns  **+0**  or  **-0**, respectively. If  **y**  is a finite value greater than or less than  **0**, and  **x**  is a negative infinity, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is a finite value greater than or less than  **0**, and  **x**  is a positive infinity, this function returns  **+0**  or  **-0**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**  or  **-[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a negative infinity, this function returns  **+3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**  or  **-3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a positive infinity, this function returns  **+[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**  or  **-[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**, respectively. 



## atan2f\(\)<a name="gaf9e5469acf7a7bf82f29d86a77f539d4"></a>

```
float atan2f (float y, float x )
```

 **Description:**

Calculates the arc tangent of two float values  **x**  and  **y**. 

**Parameters:**

<a name="table613930025084824"></a>
<table><thead align="left"><tr id="row752138558084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p315417015084824"><a name="p315417015084824"></a><a name="p315417015084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1897849308084824"><a name="p1897849308084824"></a><a name="p1897849308084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row799391044084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1044849026084824"><a name="b1044849026084824"></a><a name="b1044849026084824"></a>y</strong> for calculating the arc tangent. </td>
</tr>
<tr id="row449555417084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b234920647084824"><a name="b234920647084824"></a><a name="b234920647084824"></a>x</strong> for calculating the arc tangent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the principal value of the arc tangent of y/x in radians, ranging from  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  to  **[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**. If  **y**  is  **+0**  or  **-0**, and  **x**  is less than  **0**, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is  **+0**  or  **-0**, and  **x**  is greater than  **0**, this function returns  **+0**  or  **-0**, respectively. If  **y**  is less than  **0**  and  **x**  is either  **+0**  or  **-0**, this function returns  **-[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**. If  **y**  is greater than  **0**  and  **x**  is either  **+0**  or  **-0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **y**  is  **+0**  or  **-0**, and  **x**  is  **-0**, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is  **+0**  or  **-0**, and  **x**  is  **+0**, this function returns  **+0**  or  **-0**, respectively. If  **y**  is a finite value greater than or less than  **0**, and  **x**  is a negative infinity, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is a finite value greater than or less than  **0**, and  **x**  is a positive infinity, this function returns  **+0**  or  **-0**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**  or  **-[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a negative infinity, this function returns  **+3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**  or  **-3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a positive infinity, this function returns  **+[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**  or  **-[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**, respectively. 



## atan2l\(\)<a name="gaa983bf34c931b97d66be8b7bfd03dc48"></a>

```
long double atan2l (long double y, long double x )
```

 **Description:**

Calculates the arc tangent of two long double values  **x**  and  **y**. 

**Parameters:**

<a name="table1361946176084824"></a>
<table><thead align="left"><tr id="row1949427316084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p107001154084824"><a name="p107001154084824"></a><a name="p107001154084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1882484516084824"><a name="p1882484516084824"></a><a name="p1882484516084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1111720523084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1739343181084824"><a name="b1739343181084824"></a><a name="b1739343181084824"></a>y</strong> for calculating the arc tangent. </td>
</tr>
<tr id="row579754750084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b852048933084824"><a name="b852048933084824"></a><a name="b852048933084824"></a>x</strong> for calculating the arc tangent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the principal value of the arc tangent of y/x in radians, ranging from  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  to  **[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**. If  **y**  is  **+0**  or  **-0**, and  **x**  is less than  **0**, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is  **+0**  or  **-0**, and  **x**  is greater than  **0**, this function returns  **+0**  or  **-0**, respectively. If  **y**  is less than  **0**  and  **x**  is either  **+0**  or  **-0**, this function returns  **-[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**. If  **y**  is greater than  **0**  and  **x**  is either  **+0**  or  **-0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **y**  is  **+0**  or  **-0**, and  **x**  is  **-0**, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is  **+0**  or  **-0**, and  **x**  is  **+0**, this function returns  **+0**  or  **-0**, respectively. If  **y**  is a finite value greater than or less than  **0**, and  **x**  is a negative infinity, this function returns  **+[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**  or  **-[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)**, respectively. If  **y**  is a finite value greater than or less than  **0**, and  **x**  is a positive infinity, this function returns  **+0**  or  **-0**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**  or  **-[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a negative infinity, this function returns  **+3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**  or  **-3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**, respectively. If  **y**  is a positive or negative infinity, and  **x**  is a positive infinity, this function returns  **+[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**  or  **-[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)**, respectively. 



## atanf\(\)<a name="gaa582bc257e477e805f4ec384a39a3a8e"></a>

```
float atanf (float x)
```

 **Description:**

Calculates the arc tangent of the float value  **x**. 

**Parameters:**

<a name="table501436267084824"></a>
<table><thead align="left"><tr id="row2141955595084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2073247747084824"><a name="p2073247747084824"></a><a name="p2073247747084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p698315893084824"><a name="p698315893084824"></a><a name="p698315893084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row556869321084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose arc tangent is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the principal value of the arc tangent of  **x**  in radians, ranging from -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  to  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  or -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f), respectively. 



## atanh\(\)<a name="gac07fd7b77fa341563abccf9efcc1a711"></a>

```
double atanh (double x)
```

 **Description:**

Calculates the inverse hyperbolic tangent of the double value  **x**. 

**Parameters:**

<a name="table205500613084824"></a>
<table><thead align="left"><tr id="row1734197692084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1029417145084824"><a name="p1029417145084824"></a><a name="p1029417145084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p665231642084824"><a name="p665231642084824"></a><a name="p665231642084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row84328420084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose inverse hyperbolic tangent is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic tangent of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is  **+1**  or  **-1**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), reports a pole error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If the absolute value of  **x**  is greater than  **1**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## atanhf\(\)<a name="ga626d9d6644848e74188f37f0f3ddd4f4"></a>

```
float atanhf (float x)
```

 **Description:**

Calculates the inverse hyperbolic tangent of the float value  **x**. 

**Parameters:**

<a name="table319944594084824"></a>
<table><thead align="left"><tr id="row2088655684084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p639748208084824"><a name="p639748208084824"></a><a name="p639748208084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1277246110084824"><a name="p1277246110084824"></a><a name="p1277246110084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1013658385084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose inverse hyperbolic tangent is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic tangent of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is  **+1**  or  **-1**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), reports a pole error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If the absolute value of  **x**  is greater than  **1**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## atanhl\(\)<a name="gab25c31215118cd62672c38f80f010d66"></a>

```
long double atanhl (long double x)
```

 **Description:**

Calculates the inverse hyperbolic tangent of the long double value  **x**. 

**Parameters:**

<a name="table1792579441084824"></a>
<table><thead align="left"><tr id="row1841934882084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p340079526084824"><a name="p340079526084824"></a><a name="p340079526084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1108921821084824"><a name="p1108921821084824"></a><a name="p1108921821084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row416101299084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose inverse hyperbolic tangent is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic tangent of  **x**. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is  **+1**  or  **-1**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), reports a pole error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If the absolute value of  **x**  is greater than  **1**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## atanl\(\)<a name="ga650d8dd23c16c6699d84651a18827d37"></a>

```
long double atanl (long double x)
```

 **Description:**

Calculates the arc tangent of the long double value  **x**. 

**Parameters:**

<a name="table169556117084824"></a>
<table><thead align="left"><tr id="row1540744846084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p975217878084824"><a name="p975217878084824"></a><a name="p975217878084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p748135531084824"><a name="p748135531084824"></a><a name="p748135531084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1275581341084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose arc tangent is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the principal value of the arc tangent of  **x**  in radians, ranging from -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  to  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f). If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  or -[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f), respectively. 



## cabs\(\)<a name="ga82c65f6b05062b620716623ba49ff07f"></a>

```
double cabs (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the absolute value of the complex number  **z**. 

**Parameters:**

<a name="table1642917785084824"></a>
<table><thead align="left"><tr id="row455394241084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1364366016084824"><a name="p1364366016084824"></a><a name="p1364366016084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1099102040084824"><a name="p1099102040084824"></a><a name="p1099102040084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row106257196084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose absolute value is to be obtained. </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [hypot](math.md#ga6d6a905f61d535f8454190433b8c0ea5)\([cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\) +  [creal](math.md#ga24b1a511efdb973354d81646c5c3bb81)\(z\)\). 

**Returns:**

Returns the absolute value of  **z**  if the operation is successful. 



## cabsf\(\)<a name="ga59a1f4977dfdf85b51a84bfd56737277"></a>

```
float cabsf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the absolute value of the complex number  **z**. 

**Parameters:**

<a name="table776473023084824"></a>
<table><thead align="left"><tr id="row1126301525084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p629559286084824"><a name="p629559286084824"></a><a name="p629559286084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p558624164084824"><a name="p558624164084824"></a><a name="p558624164084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1185774991084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose absolute value is to be obtained. </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [hypot](math.md#ga6d6a905f61d535f8454190433b8c0ea5)\([cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\) +  [creal](math.md#ga24b1a511efdb973354d81646c5c3bb81)\(z\)\). 

**Returns:**

Returns the absolute value of  **z**  if the operation is successful. 



## cabsl\(\)<a name="ga7e37259e24f3384f376e4d3eb45a9ea8"></a>

```
long double cabsl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the absolute value of the complex number  **z**. 

**Parameters:**

<a name="table383003384084824"></a>
<table><thead align="left"><tr id="row1982442239084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1290247971084824"><a name="p1290247971084824"></a><a name="p1290247971084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1975874866084824"><a name="p1975874866084824"></a><a name="p1975874866084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row386280582084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose absolute value is to be obtained. </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [hypot](math.md#ga6d6a905f61d535f8454190433b8c0ea5)\([cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\) +  [creal](math.md#ga24b1a511efdb973354d81646c5c3bb81)\(z\)\). 

**Returns:**

Returns the absolute value of  **z**  if the operation is successful. 



## cacos\(\)<a name="ga51a9bcdc7791e50f879c79d64362d7c3"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cacos (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table242645101084824"></a>
<table><thead align="left"><tr id="row1999460164084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p795924350084824"><a name="p795924350084824"></a><a name="p795924350084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p892714623084824"><a name="p892714623084824"></a><a name="p892714623084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1450997911084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose arc cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc cosine of  **z**  if the operation is successful. If  **x**  is  **+0**  or  **-0**  and  **y**  is  **0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  - 0i**. If  **x**  is  **+0**  or  **-0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is not an infinity and  **y**  is an infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  -  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)  -  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)  -  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)  -  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  is a positive or negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  -  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cacosf\(\)<a name="ga238bc3dbd59adeb477af18c9a501e04e"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cacosf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1965365636084824"></a>
<table><thead align="left"><tr id="row921847550084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1657980959084824"><a name="p1657980959084824"></a><a name="p1657980959084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p316472981084824"><a name="p316472981084824"></a><a name="p316472981084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1231243331084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose arc cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc cosine of  **z**  if the operation is successful. If  **x**  is  **+0**  or  **-0**  and  **y**  is  **0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  - 0i**. If  **x**  is  **+0**  or  **-0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is not an infinity and  **y**  is an infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)  -  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)  -  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)  -  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  is a positive or negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  -  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cacosh\(\)<a name="gaf7286142554fde4ba6316a2b64b96c5c"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cacosh (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table406588291084824"></a>
<table><thead align="left"><tr id="row908240707084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p840865301084824"><a name="p840865301084824"></a><a name="p840865301084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p800955323084824"><a name="p800955323084824"></a><a name="p800955323084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row386930621084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose inverse hyperbolic cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic cosine of  **z**  if the operation is successful. If  **x**  is  **0**  and  **y**  is  **0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  + 3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cacoshf\(\)<a name="gabe9dbe34293eef409598b0559435c5ff"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cacoshf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table280764596084824"></a>
<table><thead align="left"><tr id="row1075388350084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1538036265084824"><a name="p1538036265084824"></a><a name="p1538036265084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2140004967084824"><a name="p2140004967084824"></a><a name="p2140004967084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row675289743084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose inverse hyperbolic cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic cosine of  **z**  if the operation is successful. If  **x**  is  **0**  and  **y**  is  **0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  + 3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cacoshl\(\)<a name="gad8e03bbb434b8a9af73e0e3daec045ac"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cacoshl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table131206889084824"></a>
<table><thead align="left"><tr id="row665444942084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1567953474084824"><a name="p1567953474084824"></a><a name="p1567953474084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2146796626084824"><a name="p2146796626084824"></a><a name="p2146796626084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2076989864084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose inverse hyperbolic cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic cosine of  **z**  if the operation is successful. If  **x**  is  **0**  and  **y**  is  **0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  + 3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cacosl\(\)<a name="ga789143f2859142f58590b2726328025f"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cacosl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table309766151084824"></a>
<table><thead align="left"><tr id="row1999276765084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1672398480084824"><a name="p1672398480084824"></a><a name="p1672398480084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p235074422084824"><a name="p235074422084824"></a><a name="p235074422084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1089418355084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose arc cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc cosine of  **z**  if the operation is successful. If  **x**  is  **+0**  or  **-0**  and  **y**  is  **0**, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  - 0i**. If  **x**  is  **+0**  or  **-0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is not an infinity and  **y**  is an infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)  -  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)  -  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)  -  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  is a positive or negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  -  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## carg\(\)<a name="ga4a1e5d839db7a1dc6013b2846b2432d9"></a>

```
double carg (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the phase angle of the complex number  **z**. 

**Parameters:**

<a name="table215744745084824"></a>
<table><thead align="left"><tr id="row2073640484084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p400713625084824"><a name="p400713625084824"></a><a name="p400713625084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p134832784084824"><a name="p134832784084824"></a><a name="p134832784084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1837469983084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose phase angle is to be obtained. </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [atan2](math.md#ga349377202ca14f79eb335b1a421fe4d8)\([cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\) +  [creal](math.md#ga24b1a511efdb973354d81646c5c3bb81)\(z\)\). 

**Returns:**

Returns the phase angle of  **z**  if the operation is successful. 



## cargf\(\)<a name="ga66334f398567baa3648cd3111ed68d3b"></a>

```
float cargf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the phase angle of the complex number  **z**. 

**Parameters:**

<a name="table446849438084824"></a>
<table><thead align="left"><tr id="row1577894974084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1389539594084824"><a name="p1389539594084824"></a><a name="p1389539594084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1820919174084824"><a name="p1820919174084824"></a><a name="p1820919174084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row993222132084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose phase angle is to be obtained. </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [atan2](math.md#ga349377202ca14f79eb335b1a421fe4d8)\([cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\) +  [creal](math.md#ga24b1a511efdb973354d81646c5c3bb81)\(z\)\). 

**Returns:**

Returns the phase angle of  **z**  if the operation is successful. 



## cargl\(\)<a name="ga74f3429f1b860581f4d15bea90533fd5"></a>

```
long double cargl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the phase angle of the complex number  **z**. 

**Parameters:**

<a name="table1424498539084824"></a>
<table><thead align="left"><tr id="row595966753084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p233111378084824"><a name="p233111378084824"></a><a name="p233111378084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1283588980084824"><a name="p1283588980084824"></a><a name="p1283588980084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2141293316084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [atan2](math.md#ga349377202ca14f79eb335b1a421fe4d8)\([cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\) +  [creal](math.md#ga24b1a511efdb973354d81646c5c3bb81)\(z\)\). 

**Returns:**

Returns the phase angle of  **z**  if the operation is successful. 



## casin\(\)<a name="gac43774f89411806a3e0695012cdb7f38"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) casin (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table910450338084824"></a>
<table><thead align="left"><tr id="row1256440545084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p894140860084824"><a name="p894140860084824"></a><a name="p894140860084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1022237714084824"><a name="p1022237714084824"></a><a name="p1022237714084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row3949248084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose arc sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## casinf\(\)<a name="ga04d2cd1f0b47d3f1b782aeb517151033"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) casinf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1460898766084824"></a>
<table><thead align="left"><tr id="row549986201084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2006581306084824"><a name="p2006581306084824"></a><a name="p2006581306084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p852467485084824"><a name="p852467485084824"></a><a name="p852467485084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1375963111084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose arc sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## casinh\(\)<a name="ga6fc1a0c1cbac62ba63e799d7e8f488e0"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) casinh (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1916953402084824"></a>
<table><thead align="left"><tr id="row1223707808084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p625169884084824"><a name="p625169884084824"></a><a name="p625169884084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1954221308084824"><a name="p1954221308084824"></a><a name="p1954221308084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2134990352084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose inverse hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## casinhf\(\)<a name="ga8b682e1c311efa5594ec0d0b39c9efe0"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) casinhf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1154270388084824"></a>
<table><thead align="left"><tr id="row1596739705084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p857311563084824"><a name="p857311563084824"></a><a name="p857311563084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1054691619084824"><a name="p1054691619084824"></a><a name="p1054691619084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1832480411084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose inverse hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## casinhl\(\)<a name="ga174b8f2a00e771dbbad06fdf0e0ee449"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) casinhl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1863464497084824"></a>
<table><thead align="left"><tr id="row546174392084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1551747031084824"><a name="p1551747031084824"></a><a name="p1551747031084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1439377539084824"><a name="p1439377539084824"></a><a name="p1439377539084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1344217330084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose inverse hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## casinl\(\)<a name="ga8770350a79904ac151ebb3eebd736188"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) casinl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table2122355278084824"></a>
<table><thead align="left"><tr id="row120200592084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1348050821084824"><a name="p1348050821084824"></a><a name="p1348050821084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p703518974084824"><a name="p703518974084824"></a><a name="p703518974084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1747068565084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose arc sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## catan\(\)<a name="ga1a77a3240b834af81a23b38f2af6c93d"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) catan (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1777834165084824"></a>
<table><thead align="left"><tr id="row1572362567084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1324457923084824"><a name="p1324457923084824"></a><a name="p1324457923084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1308579108084824"><a name="p1308579108084824"></a><a name="p1308579108084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2023817373084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose arc tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  **1**  and  **y**  is  **0**, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## catanf\(\)<a name="ga4d0beef9b3994887e356c6b5c98388d9"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) catanf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table268228166084824"></a>
<table><thead align="left"><tr id="row1884147749084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p495823236084824"><a name="p495823236084824"></a><a name="p495823236084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p657896763084824"><a name="p657896763084824"></a><a name="p657896763084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1484714956084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose arc tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  **1**  and  **y**  is  **0**, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## catanh\(\)<a name="ga376fef7890def8c0e7b2b5a5292be074"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) catanh (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1968913813084824"></a>
<table><thead align="left"><tr id="row36940656084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1796240883084824"><a name="p1796240883084824"></a><a name="p1796240883084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1938176786084824"><a name="p1938176786084824"></a><a name="p1938176786084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1049827679084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose inverse hyperbolic tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  **1**  and  **y**  is  **0**, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## catanhf\(\)<a name="ga480c29e0eeace893be77a2c61995d2ec"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) catanhf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1144428823084824"></a>
<table><thead align="left"><tr id="row192689730084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p351391679084824"><a name="p351391679084824"></a><a name="p351391679084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1032528732084824"><a name="p1032528732084824"></a><a name="p1032528732084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1787130081084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose inverse hyperbolic tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  **1**  and  **y**  is  **0**, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## catanhl\(\)<a name="gab2422355124f175a41ec092c3b8adf2b"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) catanhl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the inverse hyperbolic tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table521145531084824"></a>
<table><thead align="left"><tr id="row697036960084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p89723876084824"><a name="p89723876084824"></a><a name="p89723876084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p738409964084824"><a name="p738409964084824"></a><a name="p738409964084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1350813788084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose inverse hyperbolic tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the inverse hyperbolic tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  **1**  and  **y**  is  **0**, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## catanl\(\)<a name="gaf28ad2f006e49eaa6bbdb97dd143d6cb"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) catanl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the arc tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1565086021084824"></a>
<table><thead align="left"><tr id="row1425411026084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1003390309084824"><a name="p1003390309084824"></a><a name="p1003390309084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p697261028084824"><a name="p697261028084824"></a><a name="p697261028084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1670826286084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose arc tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the arc tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  **1**  and  **y**  is  **0**, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cbrt\(\)<a name="ga8af00e2203928978e0242b4afd1d899f"></a>

```
double cbrt (double x)
```

 **Description:**

Calculates the cube root of the double value  **x**. 

**Parameters:**

<a name="table709233906084824"></a>
<table><thead align="left"><tr id="row160733963084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p549142947084824"><a name="p549142947084824"></a><a name="p549142947084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p921809289084824"><a name="p921809289084824"></a><a name="p921809289084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1838108844084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose cube root is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cube root if the operation is successful; returns the passed  **x**  if  **x**  is  **+0**,  **-0**, a positive or negative infinity, or a NaN value. 



## cbrtf\(\)<a name="ga396c6a553500a355627741e234045bf4"></a>

```
float cbrtf (float x)
```

 **Description:**

Calculates the cube root of the float value  **x**. 

**Parameters:**

<a name="table786004779084824"></a>
<table><thead align="left"><tr id="row2103556433084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1816295201084824"><a name="p1816295201084824"></a><a name="p1816295201084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1368884079084824"><a name="p1368884079084824"></a><a name="p1368884079084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row38013564084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value whose cube root is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cube root if the operation is successful; returns the passed  **x**  if  **x**  is  **+0**,  **-0**, a positive or negative infinity, or a NaN value. 



## cbrtl\(\)<a name="ga521c2f4c10b7bb5363bad058ef56794c"></a>

```
long double cbrtl (long double x)
```

 **Description:**

Calculates the cube root of the long double value  **x**. 

**Parameters:**

<a name="table1781649075084824"></a>
<table><thead align="left"><tr id="row260908275084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p510809503084824"><a name="p510809503084824"></a><a name="p510809503084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1385441628084824"><a name="p1385441628084824"></a><a name="p1385441628084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1481936721084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value whose cube root is to be calculated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cube root if the operation is successful; returns the passed  **x**  if  **x**  is  **+0**,  **-0**, a positive or negative infinity, or a NaN value. 



## ccos\(\)<a name="ga6a25bcd38751910533efde6dad1499c3"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ccos (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1796974491084824"></a>
<table><thead align="left"><tr id="row895291822084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p321301612084824"><a name="p321301612084824"></a><a name="p321301612084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p80123325084824"><a name="p80123325084824"></a><a name="p80123325084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row305559225084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cosine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971). If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is a negative infinity and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is neither an infinity nor  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive or negative infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ccosf\(\)<a name="ga88df5eebfb10b88ed37e444f5b13fd6a"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ccosf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1155208746084824"></a>
<table><thead align="left"><tr id="row621394820084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p259161175084824"><a name="p259161175084824"></a><a name="p259161175084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2009380278084824"><a name="p2009380278084824"></a><a name="p2009380278084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1773377252084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cosine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359). If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is a negative infinity and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is neither an infinity nor  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive or negative infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ccosh\(\)<a name="ga62c8f7e0cce95bbf670af16376909324"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ccosh (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table2038713966084824"></a>
<table><thead align="left"><tr id="row1656642960084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p763591424084824"><a name="p763591424084824"></a><a name="p763591424084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p783149959084824"><a name="p783149959084824"></a><a name="p783149959084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row470051236084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose hyperbolic cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic cosine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is neither an infinity nor  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971). If  **x**  is a positive infinity and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive or negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is neither an infinity nor  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ccoshf\(\)<a name="gabe11c35bd81b278ab0e47196c5952662"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ccoshf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1082129075084824"></a>
<table><thead align="left"><tr id="row1957547757084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1310356840084824"><a name="p1310356840084824"></a><a name="p1310356840084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1051108926084824"><a name="p1051108926084824"></a><a name="p1051108926084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row974512996084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose hyperbolic cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic cosine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is neither an infinity nor  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359). If  **x**  is a positive infinity and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive or negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is neither an infinity nor  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ccoshl\(\)<a name="gad2b7878b871c0266ecb1f58e5bf141a7"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ccoshl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1334953184084824"></a>
<table><thead align="left"><tr id="row956414824084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2094885891084824"><a name="p2094885891084824"></a><a name="p2094885891084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p961171928084824"><a name="p961171928084824"></a><a name="p961171928084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1798961204084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose hyperbolic cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic cosine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is neither an infinity nor  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182). If  **x**  is a positive infinity and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive or negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is neither an infinity nor  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ccosl\(\)<a name="ga785d8c7b2ac4283d4759dfa6a86779ab"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ccosl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the cosine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table239611144084824"></a>
<table><thead align="left"><tr id="row199778907084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1399845037084824"><a name="p1399845037084824"></a><a name="p1399845037084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1326745937084824"><a name="p1326745937084824"></a><a name="p1326745937084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row960031663084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose cosine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cosine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182). If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is a negative infinity and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is neither an infinity nor  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive or negative infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is neither an infinity nor  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ceil\(\)<a name="ga1ea6d7b591132268abc2e843ababd084"></a>

```
double ceil (double x)
```

 **Description:**

Calculates the minimum integer greater than or equal to the double value  **x**. 

**Parameters:**

<a name="table1066969003084824"></a>
<table><thead align="left"><tr id="row2021591542084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1749789722084824"><a name="p1749789722084824"></a><a name="p1749789722084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p934296477084824"><a name="p934296477084824"></a><a name="p934296477084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row105313229084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b2077038969084824"><a name="b2077038969084824"></a><a name="b2077038969084824"></a>x</strong> to compare with. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the minimum integer greater than or equal to  **x**  if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## ceilf\(\)<a name="ga8c1a8db0710bb3f25f643a0fca68fc60"></a>

```
float ceilf (float x)
```

 **Description:**

Calculates the minimum integer greater than or equal to the float value  **x**. 

**Parameters:**

<a name="table1320003116084824"></a>
<table><thead align="left"><tr id="row945511798084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1692639497084824"><a name="p1692639497084824"></a><a name="p1692639497084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1613921720084824"><a name="p1613921720084824"></a><a name="p1613921720084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1768499981084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1914753577084824"><a name="b1914753577084824"></a><a name="b1914753577084824"></a>x</strong> to compare with. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the minimum integer greater than or equal to  **x**  if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## ceill\(\)<a name="gae11b7781f057eb7ba5d7ed95be7fdbee"></a>

```
long double ceill (long double x)
```

 **Description:**

Calculates the minimum integer greater than or equal to the long double value  **x**. 

**Parameters:**

<a name="table1981850556084824"></a>
<table><thead align="left"><tr id="row1937577064084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1054683211084824"><a name="p1054683211084824"></a><a name="p1054683211084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p257829796084824"><a name="p257829796084824"></a><a name="p257829796084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1874376863084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1937118409084824"><a name="b1937118409084824"></a><a name="b1937118409084824"></a>x</strong> to compare with. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the minimum integer greater than or equal to  **x**  if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## cexp\(\)<a name="gab9c654c52efefb54d06d52aa1a1c1827"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cexp (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the base-e exponential of the complex number  **z**. 

The mathematical formula is e^z. z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1077398376084824"></a>
<table><thead align="left"><tr id="row321736695084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1188902041084824"><a name="p1188902041084824"></a><a name="p1188902041084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1791602898084824"><a name="p1791602898084824"></a><a name="p1791602898084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1637255113084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose base-e exponential is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-e exponential of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971). If  **x**  is a negative infinity and  **y**  is an infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **0**. If  **x**  is a positive infinity and  **y**  is neither an infinity nor  **0**, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cexpf\(\)<a name="ga8628a449a00228f124c9e53d2236611f"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cexpf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the base-e exponential of the complex number  **z**. 

The mathematical formula is e^z. z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1309641601084824"></a>
<table><thead align="left"><tr id="row1807563213084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p981792216084824"><a name="p981792216084824"></a><a name="p981792216084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1906119817084824"><a name="p1906119817084824"></a><a name="p1906119817084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1734378356084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose base-e exponential is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-e exponential of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359). If  **x**  is a negative infinity and  **y**  is an infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **0**. If  **x**  is a positive infinity and  **y**  is neither an infinity nor  **0**, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cexpl\(\)<a name="ga31a965fe1790cace431516e53f7d0cb5"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cexpl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the base-e exponential of the complex number  **z**. 

The mathematical formula is e^z. z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1670747479084824"></a>
<table><thead align="left"><tr id="row319890021084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p848172180084824"><a name="p848172180084824"></a><a name="p848172180084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p989092591084824"><a name="p989092591084824"></a><a name="p989092591084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row586450733084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose base-e exponential is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-e exponential of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **1**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182). If  **x**  is a negative infinity and  **y**  is an infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **0**. If  **x**  is a positive infinity and  **y**  is neither an infinity nor  **0**, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## cimag\(\)<a name="ga6c3d7c875ae93700b0a2a32db24b37d3"></a>

```
double cimag (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the imaginary part of the complex number  **z**. 

 

**Parameters:**

<a name="table2132566694084824"></a>
<table><thead align="left"><tr id="row915012429084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2055327030084824"><a name="p2055327030084824"></a><a name="p2055327030084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1718958156084824"><a name="p1718958156084824"></a><a name="p1718958156084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1023965377084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose imaginary part is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the imaginary part of  **z**  if the operation is successful. 



## cimagf\(\)<a name="gaac22dc2fffc4326595ff807d441f0675"></a>

```
float cimagf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the imaginary part of the complex number  **z**. 

 

**Parameters:**

<a name="table1308201126084824"></a>
<table><thead align="left"><tr id="row183834168084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p715957603084824"><a name="p715957603084824"></a><a name="p715957603084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p661495362084824"><a name="p661495362084824"></a><a name="p661495362084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2117452124084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose imaginary part is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the imaginary part of  **z**  if the operation is successful. 



## cimagl\(\)<a name="ga4237f0401b8123eaec284c995ced4b04"></a>

```
long double cimagl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the imaginary part of the complex number  **z**. 

 

**Parameters:**

<a name="table1366846743084824"></a>
<table><thead align="left"><tr id="row1962071657084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2116107560084824"><a name="p2116107560084824"></a><a name="p2116107560084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p947761001084824"><a name="p947761001084824"></a><a name="p947761001084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row871602075084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose imaginary part is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the imaginary part of  **z**  if the operation is successful. 



## clog\(\)<a name="gaa39c3557d8db10c19571bc0b63fd5529"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) clog (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the natural \(base-e\) logarithm of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1981615270084824"></a>
<table><thead align="left"><tr id="row832363178084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p848039804084824"><a name="p848039804084824"></a><a name="p848039804084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1831699605084824"><a name="p1831699605084824"></a><a name="p1831699605084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row508281445084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose natural (base-e) logarithm is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural \(base-e\) logarithm of  **z**  if the operation is successful. If  **x**  is  **-0**  and  **y**  is  **+0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  and  **y**  are both  **+0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  + 0i**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  + 3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  + 0i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## clogf\(\)<a name="ga0c9f343c7d1dabc91f6e4cb868b81152"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) clogf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the natural \(base-e\) logarithm of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table600105531084824"></a>
<table><thead align="left"><tr id="row968715509084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1264224539084824"><a name="p1264224539084824"></a><a name="p1264224539084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p133817202084824"><a name="p133817202084824"></a><a name="p133817202084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row177582375084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose natural (base-e) logarithm is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural \(base-e\) logarithm of  **z**  if the operation is successful. If  **x**  is  **-0**  and  **y**  is  **+0**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  and  **y**  are both  **+0**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  + 0i**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  + 3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  + 0i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## clogl\(\)<a name="ga48efe0bf63314044fafaeb32623fff17"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) clogl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the natural \(base-e\) logarithm of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1656757141084824"></a>
<table><thead align="left"><tr id="row204136111084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1776464602084824"><a name="p1776464602084824"></a><a name="p1776464602084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2016553367084824"><a name="p2016553367084824"></a><a name="p2016553367084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1974126336084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose natural (base-e) logarithm is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural \(base-e\) logarithm of  **z**  if the operation is successful. If  **x**  is  **-0**  and  **y**  is  **+0**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  and  **y**  are both  **+0**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  + 0i**  and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_2](math.md#ga958e4508ed28ee5cc04249144312c15f)i**. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI](math.md#gae71449b1cc6e6250b91f539153a7a0d3)i**. If  **x**  is a negative infinity and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  + 3\*[M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  + 0i**. If  **x**  and  **y**  are both positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [M\_PI\_4](math.md#gaeb24420b096a677f3a2dc5a72b36bf22)i**. If  **x**  is an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not an infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## conj\(\)<a name="ga6fb30f37aa43eb2e0199ffdc38cac18a"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) conj (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the conjugate of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1636752809084824"></a>
<table><thead align="left"><tr id="row1613853969084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p667828200084824"><a name="p667828200084824"></a><a name="p667828200084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1663091702084824"><a name="p1663091702084824"></a><a name="p1663091702084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1298747995084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose conjugate is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the conjugate of  **z**, which is equal to x - yi. 



## conjf\(\)<a name="ga471ecd8d25e722ecae510a635c1a2c53"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) conjf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the conjugate of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1912342220084824"></a>
<table><thead align="left"><tr id="row1881044754084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1797919294084824"><a name="p1797919294084824"></a><a name="p1797919294084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p595317178084824"><a name="p595317178084824"></a><a name="p595317178084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row836007757084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose conjugate is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the conjugate of  **z**, which is equal to x - yi. 



## conjl\(\)<a name="ga5156353f4650ed7ee06b152790c1558b"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) conjl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the conjugate of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1042314652084824"></a>
<table><thead align="left"><tr id="row739376730084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p643853384084824"><a name="p643853384084824"></a><a name="p643853384084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1940686282084824"><a name="p1940686282084824"></a><a name="p1940686282084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1943727286084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose conjugate is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the conjugate of  **z**, which is equal to x - yi. 



## copysign\(\)<a name="gad8d1296592a3e783acdd0de21ff58e2e"></a>

```
double copysign (double x, double y )
```

 **Description:**

Generates a value by combining the magnitude of the double value  **x**  and the sign of the double value  **y**. 

For example, if  **x**  is  **42.0**  and  **y**  is  **-1.0**, value  **-42.0**  will be generated. 

**Parameters:**

<a name="table98980241084824"></a>
<table><thead align="left"><tr id="row1044270259084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p334873952084824"><a name="p334873952084824"></a><a name="p334873952084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1761467295084824"><a name="p1761467295084824"></a><a name="p1761467295084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row634358520084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1878817454084824"><a name="b1878817454084824"></a><a name="b1878817454084824"></a>x</strong> whose magnitude will be used. </td>
</tr>
<tr id="row1478496758084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b2007147636084824"><a name="b2007147636084824"></a><a name="b2007147636084824"></a>y</strong> whose sign will be used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the generated value if the operation is successful; returns a NaN value with the sign of  **y**  if  **x**  is a NaN value. 



## copysignf\(\)<a name="gaf7eb976cc28d0a9a6f0827d01611f979"></a>

```
float copysignf (float x, float y )
```

 **Description:**

Generates a value by combining the magnitude of the float value  **x**  and the sign of the float value  **y**. 

For example, if  **x**  is  **42.0**  and  **y**  is  **-1.0**, value  **-42.0**  will be generated. 

**Parameters:**

<a name="table1832529412084824"></a>
<table><thead align="left"><tr id="row1318779752084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p7958882084824"><a name="p7958882084824"></a><a name="p7958882084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p150873499084824"><a name="p150873499084824"></a><a name="p150873499084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row499753915084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b859376061084824"><a name="b859376061084824"></a><a name="b859376061084824"></a>x</strong> whose magnitude will be used. </td>
</tr>
<tr id="row1675141756084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b969424691084824"><a name="b969424691084824"></a><a name="b969424691084824"></a>y</strong> whose sign will be used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the generated value if the operation is successful; returns a NaN value with the sign of  **y**  if  **x**  is a NaN value. 



## copysignl\(\)<a name="gae60d4866e88abf023d92d33c6351ae6f"></a>

```
long double copysignl (long double x, long double y )
```

 **Description:**

Generates a value by combining the magnitude of the long double value  **x**  and the sign of the long double value  **y**. 

For example, if  **x**  is  **42.0**  and  **y**  is  **-1.0**, value  **-42.0**  will be generated. 

**Parameters:**

<a name="table729359438084824"></a>
<table><thead align="left"><tr id="row2035722878084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p313158823084824"><a name="p313158823084824"></a><a name="p313158823084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p645899665084824"><a name="p645899665084824"></a><a name="p645899665084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1636159690084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1922367330084824"><a name="b1922367330084824"></a><a name="b1922367330084824"></a>x</strong> whose magnitude will be used. </td>
</tr>
<tr id="row858867114084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1107635873084824"><a name="b1107635873084824"></a><a name="b1107635873084824"></a>y</strong> whose magnitude will be used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the generated value if the operation is successful; returns a NaN value with the sign of  **y**  if  **x**  is a NaN value. 



## cos\(\)<a name="ga5e7b53a694b3cf0f2d7debd444140fbd"></a>

```
double cos (double x)
```

 **Description:**

Calculates the cosine of the double value  **x**. 

**Parameters:**

<a name="table266938071084824"></a>
<table><thead align="left"><tr id="row1531833223084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p292917581084824"><a name="p292917581084824"></a><a name="p292917581084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p457438969084824"><a name="p457438969084824"></a><a name="p457438969084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1007970339084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cosine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## cosf\(\)<a name="ga7b126b2344591e649c21c9ab0b8adb40"></a>

```
float cosf (float x)
```

 **Description:**

Calculates the cosine of the float value  **x**. 

**Parameters:**

<a name="table1468375103084824"></a>
<table><thead align="left"><tr id="row530365419084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p578241321084824"><a name="p578241321084824"></a><a name="p578241321084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p781665538084824"><a name="p781665538084824"></a><a name="p781665538084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row21468217084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cosine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## cosh\(\)<a name="ga3795d3c1f1d30819be56da4e4d67f64b"></a>

```
double cosh (double x)
```

 **Description:**

Calculates the hyperbolic cosine of the double value  **x**. 

**Parameters:**

<a name="table952536886084824"></a>
<table><thead align="left"><tr id="row1679350882084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p703939747084824"><a name="p703939747084824"></a><a name="p703939747084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2113150778084824"><a name="p2113150778084824"></a><a name="p2113150778084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row364616166084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic cosine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **1**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If an overflow range error occurs, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## coshf\(\)<a name="ga498b368486b7ce8677820beeb78d8f66"></a>

```
float coshf (float x)
```

 **Description:**

Calculates the hyperbolic cosine of the float value  **x**. 

**Parameters:**

<a name="table262660583084824"></a>
<table><thead align="left"><tr id="row512703196084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1163444794084824"><a name="p1163444794084824"></a><a name="p1163444794084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p202910956084824"><a name="p202910956084824"></a><a name="p202910956084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row469895104084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic cosine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **1**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359), sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## coshl\(\)<a name="ga57602cd20f8de2dceea4f05ffb516d82"></a>

```
long double coshl (long double x)
```

 **Description:**

Calculates the hyperbolic cosine of the long double value  **x**. 

**Parameters:**

<a name="table1434938827084824"></a>
<table><thead align="left"><tr id="row2065795568084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1532696708084824"><a name="p1532696708084824"></a><a name="p1532696708084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p129218583084824"><a name="p129218583084824"></a><a name="p129218583084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row941932927084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic cosine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **1**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182), sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## cosl\(\)<a name="ga659287f7399efa8d6bc66dc37c8e35f4"></a>

```
long double cosl (long double x)
```

 **Description:**

Calculates the cosine of the long double value  **x**. 

**Parameters:**

<a name="table1449152634084824"></a>
<table><thead align="left"><tr id="row849164688084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p638685100084824"><a name="p638685100084824"></a><a name="p638685100084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2050428882084824"><a name="p2050428882084824"></a><a name="p2050428882084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1549469345084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the cosine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## cpow\(\)<a name="ga6fd1bd16c6de991f95a4e19e0f2f2a12"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cpow (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) x, double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z )
```

 **Description:**

Calculates the value of  **x**  raised to the  **z**  power. 

The mathematical formula is x^z. 

**Parameters:**

<a name="table777571829084824"></a>
<table><thead align="left"><tr id="row379504901084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1745814111084824"><a name="p1745814111084824"></a><a name="p1745814111084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1911896359084824"><a name="p1911896359084824"></a><a name="p1911896359084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row808941825084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the base (a double complex number). </td>
</tr>
<tr id="row517480567084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the exponent (a double complex number). </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **x**  or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [cexp](math.md#gab9c654c52efefb54d06d52aa1a1c1827)\(z\*[clog](math.md#gaa39c3557d8db10c19571bc0b63fd5529)\(x\)\). 

**Returns:**

Returns the value of  **x**  raised to the  **z**  power if the operation is successful. 



## cpowf\(\)<a name="ga58beb4a3ea7b6ab6bb942900f94179fa"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cpowf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) x, float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z )
```

 **Description:**

Calculates the value of  **x**  raised to the  **z**  power. 

The mathematical formula is x^z. 

**Parameters:**

<a name="table997373767084824"></a>
<table><thead align="left"><tr id="row1933525125084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1835905471084824"><a name="p1835905471084824"></a><a name="p1835905471084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1073867746084824"><a name="p1073867746084824"></a><a name="p1073867746084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1536510474084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the base (a float complex number). </td>
</tr>
<tr id="row739875258084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the exponent (a float complex number). </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **x**  or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [cexp](math.md#gab9c654c52efefb54d06d52aa1a1c1827)\(z\*[clog](math.md#gaa39c3557d8db10c19571bc0b63fd5529)\(x\)\). 

**Returns:**

Returns the value of  **x**  raised to the  **z**  power if the operation is successful. 



## cpowl\(\)<a name="gae3ae7292dac86eeec3bb9a06b66f61cb"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cpowl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) x, long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z )
```

 **Description:**

Calculates the value of  **x**  raised to the  **z**  power. 

The mathematical formula is x^z. 

**Parameters:**

<a name="table1167663899084824"></a>
<table><thead align="left"><tr id="row502891146084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1678471982084824"><a name="p1678471982084824"></a><a name="p1678471982084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1665435126084824"><a name="p1665435126084824"></a><a name="p1665435126084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1812111189084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the base (a long double complex number). </td>
</tr>
<tr id="row454025938084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the exponent (a long double complex number). </td>
</tr>
</tbody>
</table>

**Attention:**

If an error occurs or  **x**  or  **z**  is a positive or negative infinity or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), the returned value is calculated based on the formula  [cexp](math.md#gab9c654c52efefb54d06d52aa1a1c1827)\(z\*[clog](math.md#gaa39c3557d8db10c19571bc0b63fd5529)\(x\)\). 

**Returns:**

Returns the value of  **x**  raised to the  **z**  power if the operation is successful. 



## cproj\(\)<a name="gac10f86edf0994d0ee834768633be644e"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cproj (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the projection of the complex number  **z**  onto the Riemann sphere. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table786922324084824"></a>
<table><thead align="left"><tr id="row1413494127084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p936847445084824"><a name="p936847445084824"></a><a name="p936847445084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p397075435084824"><a name="p397075435084824"></a><a name="p397075435084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row965568694084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose projection onto the Riemann sphere is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the projection of  **z**  onto the Riemann sphere if the operation is successful. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is an infinity, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971). If  **x**  is an infinity, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  + i\*[copysign](math.md#gad8d1296592a3e783acdd0de21ff58e2e)\(0.0,  [cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\)\). 



## cprojf\(\)<a name="ga9f435a71e44dd1e13eca358e2ca530e6"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cprojf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the projection of the complex number  **z**  onto the Riemann sphere. 

**Parameters:**

<a name="table1845933083084824"></a>
<table><thead align="left"><tr id="row1225797370084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1921490051084824"><a name="p1921490051084824"></a><a name="p1921490051084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1254558560084824"><a name="p1254558560084824"></a><a name="p1254558560084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row817417717084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose projection onto the Riemann sphere is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the projection of  **z**  onto the Riemann sphere if the operation is successful. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is an infinity, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359). If  **x**  is an infinity, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  + i\*[copysign](math.md#gad8d1296592a3e783acdd0de21ff58e2e)\(0.0,  [cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\)\). 



## cprojl\(\)<a name="ga2cc437f3ab8e77dbd8fb024c66474915"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) cprojl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the projection of the complex number  **z**  onto the Riemann sphere. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table981134966084824"></a>
<table><thead align="left"><tr id="row1486668533084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p439356170084824"><a name="p439356170084824"></a><a name="p439356170084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1057570030084824"><a name="p1057570030084824"></a><a name="p1057570030084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row877792150084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose projection onto the Riemann sphere is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the projection of  **z**  onto the Riemann sphere if the operation is successful. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is an infinity, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182). If  **x**  is an infinity, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  + i\*[copysign](math.md#gad8d1296592a3e783acdd0de21ff58e2e)\(0.0,  [cimag](math.md#ga6c3d7c875ae93700b0a2a32db24b37d3)\(z\)\). 



## creal\(\)<a name="ga24b1a511efdb973354d81646c5c3bb81"></a>

```
double creal (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the real part of the complex number  **z**. 

**Parameters:**

<a name="table324136867084824"></a>
<table><thead align="left"><tr id="row1995555614084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1874842780084824"><a name="p1874842780084824"></a><a name="p1874842780084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p511544245084824"><a name="p511544245084824"></a><a name="p511544245084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2045770794084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose real part is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the real part of  **z**  if the operation is successful. 



## crealf\(\)<a name="gad052a3eb4d9f32153173e6bcea9e42ce"></a>

```
float crealf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the real part of the complex number  **z**. 

**Parameters:**

<a name="table231080289084824"></a>
<table><thead align="left"><tr id="row1187157016084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1545539386084824"><a name="p1545539386084824"></a><a name="p1545539386084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p960308679084824"><a name="p960308679084824"></a><a name="p960308679084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1315284671084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose real part is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the real part of  **z**  if the operation is successful. 



## creall\(\)<a name="ga4ee2baa54a4e51877c59527d2be1a0da"></a>

```
long double creall (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the real part of the complex number  **z**. 

**Parameters:**

<a name="table1482752228084824"></a>
<table><thead align="left"><tr id="row2055516216084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p277668486084824"><a name="p277668486084824"></a><a name="p277668486084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p417390413084824"><a name="p417390413084824"></a><a name="p417390413084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1675019213084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose real part is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the real part of  **z**  if the operation is successful. 



## csin\(\)<a name="ga1b9030685d326e66a93a35ca8c4bb0f6"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csin (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table206180897084824"></a>
<table><thead align="left"><tr id="row1952160865084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1599397424084824"><a name="p1599397424084824"></a><a name="p1599397424084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p185155659084824"><a name="p185155659084824"></a><a name="p185155659084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1529263475084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive finite value and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csinf\(\)<a name="ga76dc89521e12096bc2104c9c0dcc20ea"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csinf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1123045482084824"></a>
<table><thead align="left"><tr id="row1695613333084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p938728735084824"><a name="p938728735084824"></a><a name="p938728735084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1148784510084824"><a name="p1148784510084824"></a><a name="p1148784510084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row99059994084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive finite value and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csinh\(\)<a name="ga0c782aa9258a4e11cc3ea57b2dcccfef"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csinh (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1536126643084824"></a>
<table><thead align="left"><tr id="row920608342084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p985251430084824"><a name="p985251430084824"></a><a name="p985251430084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p459828524084824"><a name="p459828524084824"></a><a name="p459828524084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row777411641084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive finite value and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csinhf\(\)<a name="ga268ba13d67a10e6667bd6b64a1a96351"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csinhf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table533749397084824"></a>
<table><thead align="left"><tr id="row60896904084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1127790498084824"><a name="p1127790498084824"></a><a name="p1127790498084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1011751039084824"><a name="p1011751039084824"></a><a name="p1011751039084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1265605058084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive finite value and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csinhl\(\)<a name="ga0d14ae39cd9a811e42e36512fe6c7e53"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csinhl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table732315711084824"></a>
<table><thead align="left"><tr id="row566892037084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1467330331084824"><a name="p1467330331084824"></a><a name="p1467330331084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1752898694084824"><a name="p1752898694084824"></a><a name="p1752898694084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row959171445084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose hyperbolic sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive finite value and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csinl\(\)<a name="gad594fa6071ea5d383a0c7abaa0c32d80"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csinl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the sine of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1154592872084824"></a>
<table><thead align="left"><tr id="row1560206604084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1235616367084824"><a name="p1235616367084824"></a><a name="p1235616367084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p584578567084824"><a name="p584578567084824"></a><a name="p584578567084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row341311507084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose sine is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the sine of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is  **0**  and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **0**  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is a positive finite value and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive finite value and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  **0**, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)\*\([cos](math.md#ga5e7b53a694b3cf0f2d7debd444140fbd)\(y\) + i[sin](math.md#gaad4af25633b071b0e2cdb8ebd87eca77)\(y\)\)**. If  **x**  and  **y**  are both positive infinity, this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\) and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **+\(-\)[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  \(the sign bit of the real part of the returned value is uncertain\). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csqrt\(\)<a name="ga7ff172d72bc0474b93e27470ce94494b"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csqrt (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the square root of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table942041342084824"></a>
<table><thead align="left"><tr id="row567933906084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1173938341084824"><a name="p1173938341084824"></a><a name="p1173938341084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2138477986084824"><a name="p2138477986084824"></a><a name="p2138477986084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1480667509084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose square root is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the square root of  **z**  if the operation is successful. If  **x**  is  **+0**  or  **-0**  and  **y**  is  **+0**, this function returns  **+0 + 0i**. If  **x**  is neither an infinity nor  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  is a finite value or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**. If  **x**  is a negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  + 0i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is any value, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csqrtf\(\)<a name="gab8e425ba3e5d52d410afc3041bdeadce"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csqrtf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the square root of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table651330324084824"></a>
<table><thead align="left"><tr id="row391278453084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p24790255084824"><a name="p24790255084824"></a><a name="p24790255084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1058698675084824"><a name="p1058698675084824"></a><a name="p1058698675084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row130563053084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose square root is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the square root of  **z**  if the operation is successful. If  **x**  is  **+0**  or  **-0**  and  **y**  is  **+0**, this function returns  **+0 + 0i**. If  **x**  is neither an infinity nor  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  is a finite value or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**. If  **x**  is a negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  + 0i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is any value, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## csqrtl\(\)<a name="ga94a429c220e400a1a6781d6e11cbfafd"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) csqrtl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the square root of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table282842024084824"></a>
<table><thead align="left"><tr id="row627168114084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1181736717084824"><a name="p1181736717084824"></a><a name="p1181736717084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p120083443084824"><a name="p120083443084824"></a><a name="p120083443084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row433012339084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose square root is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the square root of  **z**  if the operation is successful. If  **x**  is  **+0**  or  **-0**  and  **y**  is  **+0**, this function returns  **+0 + 0i**. If  **x**  is neither an infinity nor  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is a positive infinity, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  +  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  is a finite value or  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**. If  **x**  is a negative infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +\(-\)  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)i**  \(the sign bit of the imaginary part of the returned value is uncertain\). If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  + 0i**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)+[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is any value, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ctan\(\)<a name="ga665b5dfc1b1f51d3b444f049c6bd95dd"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ctan (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1096497476084824"></a>
<table><thead align="left"><tr id="row2142275197084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p863351751084824"><a name="p863351751084824"></a><a name="p863351751084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1607037455084824"><a name="p1607037455084824"></a><a name="p1607037455084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2108848643084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **1**. If  **x**  and  **y**  are both positive infinity, this function returns  **1**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **1**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ctanf\(\)<a name="ga4301d608cc419f1ba3177fae4f258f30"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ctanf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1735795011084824"></a>
<table><thead align="left"><tr id="row2015619647084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1624143598084824"><a name="p1624143598084824"></a><a name="p1624143598084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p822412972084824"><a name="p822412972084824"></a><a name="p822412972084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1851780110084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **1**. If  **x**  and  **y**  are both positive infinity, this function returns  **1**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **1**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ctanh\(\)<a name="ga9c5cf378e654f3aaed9fb0f5c8223585"></a>

```
double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ctanh (double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1824264316084824"></a>
<table><thead align="left"><tr id="row1476337502084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p940637065084824"><a name="p940637065084824"></a><a name="p940637065084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p876352214084824"><a name="p876352214084824"></a><a name="p876352214084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1945303507084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a double value) whose hyperbolic tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **1**. If  **x**  and  **y**  are both positive infinity, this function returns  **1**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **1**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ctanhf\(\)<a name="gad68db7f429f2104acf52b096c5efb69a"></a>

```
float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ctanhf (float [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1990165377084824"></a>
<table><thead align="left"><tr id="row1011363451084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p121537324084824"><a name="p121537324084824"></a><a name="p121537324084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p517736380084824"><a name="p517736380084824"></a><a name="p517736380084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row646205896084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a float value) whose hyperbolic tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **1**. If  **x**  and  **y**  are both positive infinity, this function returns  **1**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **1**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ctanhl\(\)<a name="ga2fbb0a9d578343f924c96faed3189805"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ctanhl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the hyperbolic tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table2138126947084824"></a>
<table><thead align="left"><tr id="row2131133502084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1879003677084824"><a name="p1879003677084824"></a><a name="p1879003677084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p342224702084824"><a name="p342224702084824"></a><a name="p342224702084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row676925586084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose hyperbolic tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **1**. If  **x**  and  **y**  are both positive infinity, this function returns  **1**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **1**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## ctanl\(\)<a name="ga7aa0362acd67521c9aac791aa617f953"></a>

```
long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) ctanl (long double [complex](math.md#ga0fa4878c968311979d497ccc322e0b9b) z)
```

 **Description:**

Calculates the tangent of the complex number  **z**. 

z = x + yi, where i =  [sqrt](math.md#gab87521a75ef827a85807f89a6c10629a)\(-1\) 

**Parameters:**

<a name="table1802135926084824"></a>
<table><thead align="left"><tr id="row2113746059084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1303958172084824"><a name="p1303958172084824"></a><a name="p1303958172084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p305899757084824"><a name="p305899757084824"></a><a name="p305899757084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1679085299084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the complex number (a long double value) whose tangent is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the tangent of  **z**  if the operation is successful. If  **x**  and  **y**  are both  **0**, this function returns  **0**. If  **x**  is not an infinity and  **y**  is a positive infinity, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is not an infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and may throw the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a positive infinity and  **y**  is a positive finite value, this function returns  **1**. If  **x**  and  **y**  are both positive infinity, this function returns  **1**. If  **x**  is a positive infinity and  **y**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **1**. If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is  **0**, this function returns  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc). If  **x**  is  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  and  **y**  is not  **0**, this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**  and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  and  **y**  are both  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc), this function returns  **[NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)  +  [NAN](math.md#ga8abfcc76130f3f991d124dd22d7e69bc)i**. 



## erf\(\)<a name="gaa8b35382a71885eed509a5f87bf5e266"></a>

```
double erf (double x)
```

 **Description:**

Calculates the error function of the double value  **x**. 

**Parameters:**

<a name="table659208727084824"></a>
<table><thead align="left"><tr id="row2092203345084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p928355518084824"><a name="p928355518084824"></a><a name="p928355518084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p703584141084824"><a name="p703584141084824"></a><a name="p703584141084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1620426275084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the error function if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns  **+1**  or  **-1**, respectively. If an underflow range error occurs, this function returns  **2\*x/sqrt\(pi\)**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## erfc\(\)<a name="ga0b6c4cfae41124da64c9a2dcc09e6045"></a>

```
double erfc (double x)
```

 **Description:**

Calculates the complementary error function of the double value  **x**. 

**Parameters:**

<a name="table2031366274084824"></a>
<table><thead align="left"><tr id="row1983464562084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p913303016084824"><a name="p913303016084824"></a><a name="p913303016084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p134744496084824"><a name="p134744496084824"></a><a name="p134744496084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1269959784084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the complementary error function if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **1**. If  **x**  is a positive infinity, this function returns  **+0**. If  **x**  is a negative infinity, this function returns  **+2**. If an underflow range error occurs and an unrepresentable value is generated, this function returns  **0.0**. If an underflow range error occurs and a representable value is generated, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## erfcf\(\)<a name="gad948b9d3bfcb66c074ffe17326030d41"></a>

```
float erfcf (float x)
```

 **Description:**

Calculates the complementary error function of the float value  **x**. 

**Parameters:**

<a name="table372671896084824"></a>
<table><thead align="left"><tr id="row641506901084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1790863044084824"><a name="p1790863044084824"></a><a name="p1790863044084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1035375280084824"><a name="p1035375280084824"></a><a name="p1035375280084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row20739214084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the complementary error function if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **1**. If  **x**  is a positive infinity, this function returns  **+0**. If  **x**  is a negative infinity, this function returns  **+2**. If an underflow range error occurs and an unrepresentable value is generated, this function returns  **0.0**. If an underflow range error occurs and a representable value is generated, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## erfcl\(\)<a name="ga8ac2c9e0246c0c8106d04762a9623594"></a>

```
long double erfcl (long double x)
```

 **Description:**

Calculates the complementary error function of the long double value  **x**. 

**Parameters:**

<a name="table1248526778084824"></a>
<table><thead align="left"><tr id="row1866488376084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1450962222084824"><a name="p1450962222084824"></a><a name="p1450962222084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1583907407084824"><a name="p1583907407084824"></a><a name="p1583907407084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1522027007084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the complementary error function if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **1**. If  **x**  is a positive infinity, this function returns  **+0**. If  **x**  is a negative infinity, this function returns  **+2**. If an underflow range error occurs and an unrepresentable value is generated, this function returns  **0.0**. If an underflow range error occurs and a representable value is generated, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## erff\(\)<a name="gaabebdd2dd548c14805831297ac129862"></a>

```
float erff (float x)
```

 **Description:**

Calculates the error function of the float value  **x**. 

**Parameters:**

<a name="table988954146084824"></a>
<table><thead align="left"><tr id="row1396678509084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p995032946084824"><a name="p995032946084824"></a><a name="p995032946084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1499592818084824"><a name="p1499592818084824"></a><a name="p1499592818084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1669118342084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the error function if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns  **+1**  or  **-1**, respectively. If an underflow range error occurs, this function returns  **2\*x/sqrt\(pi\)**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## erfl\(\)<a name="ga6ccdcbbc2f0b22de2add8955e415170e"></a>

```
long double erfl (long double x)
```

 **Description:**

Calculates the error function of the long double value  **x**. 

**Parameters:**

<a name="table410004551084824"></a>
<table><thead align="left"><tr id="row1059406050084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p257968755084824"><a name="p257968755084824"></a><a name="p257968755084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1607304722084824"><a name="p1607304722084824"></a><a name="p1607304722084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2085223860084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the error function if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns  **+1**  or  **-1**, respectively. If an underflow range error occurs, this function returns  **2\*x/sqrt\(pi\)**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## exp\(\)<a name="gae09128febbbe6372cde4fa0c65608a42"></a>

```
double exp (double x)
```

 **Description:**

Calculates the base-e exponential function of the double value  **x**. 

**Parameters:**

<a name="table1998019671084824"></a>
<table><thead align="left"><tr id="row654207590084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1699093556084824"><a name="p1699093556084824"></a><a name="p1699093556084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p122960429084824"><a name="p122960429084824"></a><a name="p122960429084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1075859894084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-e exponential function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **+0**. If an underflow range error occurs, this function returns  **0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. If an overflow range error occurs, this function returns  **+[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## exp10\(\)<a name="gaea673cadd2aef111e2ee7a813776b768"></a>

```
double exp10 (double x)
```

 **Description:**

Calculates the base-10 exponential function of the double value  **x**. 

**Parameters:**

<a name="table1574558149084824"></a>
<table><thead align="left"><tr id="row1207872362084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p967880650084824"><a name="p967880650084824"></a><a name="p967880650084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p565435972084824"><a name="p565435972084824"></a><a name="p565435972084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row356034665084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b941835783084824"><a name="b941835783084824"></a><a name="b941835783084824"></a>x</strong> used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-10 exponential function of  **x**  if the operation is successful. 



## exp10f\(\)<a name="gad27f10a0e30a7fe130c18786bf097e4b"></a>

```
float exp10f (float x)
```

 **Description:**

Calculates the base-10 exponential function of the float value  **x**. 

**Parameters:**

<a name="table857215930084824"></a>
<table><thead align="left"><tr id="row1970628204084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p133524357084824"><a name="p133524357084824"></a><a name="p133524357084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p489112887084824"><a name="p489112887084824"></a><a name="p489112887084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row763417879084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1543282575084824"><a name="b1543282575084824"></a><a name="b1543282575084824"></a>x</strong> used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-10 exponential function of  **x**  if the operation is successful. 



## exp10l\(\)<a name="ga28c11df4d7b29c9f59ac733fba51bece"></a>

```
long double exp10l (long double x)
```

 **Description:**

Calculates the base-10 exponential function of the long double value  **x**. 

**Parameters:**

<a name="table1205683718084824"></a>
<table><thead align="left"><tr id="row908752960084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p498378055084824"><a name="p498378055084824"></a><a name="p498378055084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p341273452084824"><a name="p341273452084824"></a><a name="p341273452084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row624317672084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1296155877084824"><a name="b1296155877084824"></a><a name="b1296155877084824"></a>x</strong> used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-10 exponential function of  **x**  if the operation is successful. 



## exp2\(\)<a name="ga86e37219434c0b7978453b6ca88fc5fb"></a>

```
double exp2 (double x)
```

 **Description:**

Calculates the base-2 exponential function of the double value  **x**. 

**Parameters:**

<a name="table606629547084824"></a>
<table><thead align="left"><tr id="row1192649140084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p540176162084824"><a name="p540176162084824"></a><a name="p540176162084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p592784934084824"><a name="p592784934084824"></a><a name="p592784934084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row442951912084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-2 exponential function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **+0**. If an underflow range error occurs, this function returns  **0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. If an overflow range error occurs, this function returns  **+[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## exp2f\(\)<a name="gaed26c6708ff2027f9a8214d206eef0e7"></a>

```
float exp2f (float x)
```

 **Description:**

Calculates the base-2 exponential function of the float value  **x**. 

**Parameters:**

<a name="table356514662084824"></a>
<table><thead align="left"><tr id="row1087300010084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1512912281084824"><a name="p1512912281084824"></a><a name="p1512912281084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p122038228084824"><a name="p122038228084824"></a><a name="p122038228084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row551675437084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-2 exponential function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **+0**. If an underflow range error occurs, this function returns  **0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. If an overflow range error occurs, this function returns  **+[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## exp2l\(\)<a name="ga4618e032de8318b72df5cc71f15b5e45"></a>

```
long double exp2l (long double x)
```

 **Description:**

Calculates the base-2 exponential function of the long double value  **x**. 

**Parameters:**

<a name="table1521030811084824"></a>
<table><thead align="left"><tr id="row99419814084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1336243363084824"><a name="p1336243363084824"></a><a name="p1336243363084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1036995955084824"><a name="p1036995955084824"></a><a name="p1036995955084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row458273397084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-2 exponential function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **+0**. If an underflow range error occurs, this function returns  **0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. If an overflow range error occurs, this function returns  **+[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## expf\(\)<a name="ga0c2bc89b8355a89542ac98d9e2120363"></a>

```
float expf (float x)
```

 **Description:**

Calculates the base-e exponential function of the float value  **x**. 

**Parameters:**

<a name="table102632339084824"></a>
<table><thead align="left"><tr id="row1363303924084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1816989852084824"><a name="p1816989852084824"></a><a name="p1816989852084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1867725005084824"><a name="p1867725005084824"></a><a name="p1867725005084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1520367100084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-e exponential function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **+0**. If an underflow range error occurs, this function returns  **0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. If an overflow range error occurs, this function returns  **+[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## expl\(\)<a name="gaed4eb11ef1397c751334311ce5b43920"></a>

```
long double expl (long double x)
```

 **Description:**

Calculates the base-e exponential function of the long double value  **x**. 

**Parameters:**

<a name="table1515120451084824"></a>
<table><thead align="left"><tr id="row1070039310084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1621717848084824"><a name="p1621717848084824"></a><a name="p1621717848084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1028716057084824"><a name="p1028716057084824"></a><a name="p1028716057084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1957401928084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the base-e exponential function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **+0**. If an underflow range error occurs, this function returns  **0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. If an overflow range error occurs, this function returns  **+[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## expm1\(\)<a name="gae4963ac40f96d4b1fe8af1b1e90a20bb"></a>

```
double expm1 (double x)
```

 **Description:**

Calculates e raised to the power of the double value  **x**  minus one, that is, \(e^x\)-1. 

**Parameters:**

<a name="table1284620379084824"></a>
<table><thead align="left"><tr id="row1483192319084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p113700450084824"><a name="p113700450084824"></a><a name="p113700450084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1386246550084824"><a name="p1386246550084824"></a><a name="p1386246550084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1791315463084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns e raised to the power of  **x**  minus one if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **-1**. If an overflow range error occurs, this function returns  **+[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## expm1f\(\)<a name="ga5b8d8815f5c801fdbdb7f7767fbf9af4"></a>

```
float expm1f (float x)
```

 **Description:**

Calculates e raised to the power of the float value  **x**  minus one. 

**Parameters:**

<a name="table1080378960084824"></a>
<table><thead align="left"><tr id="row1005345376084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1499919982084824"><a name="p1499919982084824"></a><a name="p1499919982084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p376863826084824"><a name="p376863826084824"></a><a name="p376863826084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row308228491084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns e raised to the power of  **x**  minus one if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **-1**. If an overflow range error occurs, this function returns  **+[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## expm1l\(\)<a name="ga702b0680671cf9ef94017ac04f77358b"></a>

```
long double expm1l (long double x)
```

 **Description:**

Calculates e raised to the power of the long double value  **x**  minus one. 

**Parameters:**

<a name="table351204709084824"></a>
<table><thead align="left"><tr id="row170142005084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p975894583084824"><a name="p975894583084824"></a><a name="p975894583084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2018770099084824"><a name="p2018770099084824"></a><a name="p2018770099084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row156959610084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns e raised to the power of  **x**  minus one if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity, this function returns  **-1**. If an overflow range error occurs, this function returns  **+[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## fabs\(\)<a name="ga8fb5c0b9b43a108724b355136d29d2f9"></a>

```
double fabs (double x)
```

 **Description:**

Calculates the absolute value of the double value  **x**. 

**Parameters:**

<a name="table782240360084824"></a>
<table><thead align="left"><tr id="row1521663950084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1349197344084824"><a name="p1349197344084824"></a><a name="p1349197344084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p82153389084824"><a name="p82153389084824"></a><a name="p82153389084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1604667011084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the absolute value of  **x**  if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **+0**  if  **x**  is  **-0**; returns a positive infinity if  **x**  is a positive or negative infinity. 



## fabsf\(\)<a name="ga9b02e2f3ebf257ac4f4d3ca1da6147d7"></a>

```
float fabsf (float x)
```

 **Description:**

Calculates the absolute value of the float value  **x**. 

**Parameters:**

<a name="table1088246242084824"></a>
<table><thead align="left"><tr id="row948346073084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1842501905084824"><a name="p1842501905084824"></a><a name="p1842501905084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p719323064084824"><a name="p719323064084824"></a><a name="p719323064084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row946248745084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the absolute value of  **x**  if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **+0**  if  **x**  is  **-0**; returns a positive infinity if  **x**  is a positive or negative infinity. 



## fabsl\(\)<a name="ga404c051ab9afd74c7ceed207683a235f"></a>

```
long double fabsl (long double x)
```

 **Description:**

Calculates the absolute value of the long double value  **x**. 

**Parameters:**

<a name="table238128214084824"></a>
<table><thead align="left"><tr id="row490003373084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p425609034084824"><a name="p425609034084824"></a><a name="p425609034084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1330714155084824"><a name="p1330714155084824"></a><a name="p1330714155084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row234227569084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the absolute value of  **x**  if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **+0**  if  **x**  is  **-0**; returns a positive infinity if  **x**  is a positive or negative infinity. 



## fdim\(\)<a name="ga800522810eaaed28bd53798bff4b0bfa"></a>

```
double fdim (double x, double y )
```

 **Description:**

Calculates the positive difference between the double value  **x**  and  **y**. 

**Parameters:**

<a name="table1003608130084824"></a>
<table><thead align="left"><tr id="row933199370084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1666344077084824"><a name="p1666344077084824"></a><a name="p1666344077084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1790360722084824"><a name="p1790360722084824"></a><a name="p1790360722084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1285128241084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b464837280084824"><a name="b464837280084824"></a><a name="b464837280084824"></a>x</strong>. </td>
</tr>
<tr id="row1130249094084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b682126407084824"><a name="b682126407084824"></a><a name="b682126407084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the positive difference between  **x**  and  **y**. 



## fdimf\(\)<a name="gaeee3a0bf2804c53c65199590ac4804cf"></a>

```
float fdimf (float x, float y )
```

 **Description:**

Calculates the positive difference between the float value  **x**  and  **y**. 

**Parameters:**

<a name="table1598113552084824"></a>
<table><thead align="left"><tr id="row1455482873084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1826318527084824"><a name="p1826318527084824"></a><a name="p1826318527084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p698239425084824"><a name="p698239425084824"></a><a name="p698239425084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row969028491084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1602700760084824"><a name="b1602700760084824"></a><a name="b1602700760084824"></a>x</strong>. </td>
</tr>
<tr id="row1642351156084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b493807129084824"><a name="b493807129084824"></a><a name="b493807129084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the positive difference between  **x**  and  **y**. 



## fdiml\(\)<a name="gab88ba65d1861deddbbc5cb5384d6a02e"></a>

```
long double fdiml (long double x, long double y )
```

 **Description:**

Calculates the positive difference between the long double value  **x**  and  **y**. 

**Parameters:**

<a name="table1137415673084824"></a>
<table><thead align="left"><tr id="row1166354058084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2112170767084824"><a name="p2112170767084824"></a><a name="p2112170767084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2000188639084824"><a name="p2000188639084824"></a><a name="p2000188639084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row562843501084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b611990204084824"><a name="b611990204084824"></a><a name="b611990204084824"></a>x</strong>. </td>
</tr>
<tr id="row664767213084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b882616949084824"><a name="b882616949084824"></a><a name="b882616949084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the positive difference between  **x**  and  **y**. 



## feclearexcept\(\)<a name="gac85b548794b2e0c90e147ab5e0f285e5"></a>

```
int feclearexcept (int excepts)
```

 **Description:**

Clears floating-point exceptions specified by  **excepts**. 

**Parameters:**

<a name="table2142607794084824"></a>
<table><thead align="left"><tr id="row1287598067084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1913079454084824"><a name="p1913079454084824"></a><a name="p1913079454084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1093787528084824"><a name="p1093787528084824"></a><a name="p1093787528084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row389156887084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">excepts</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point exceptions to clear. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fegetenv\(\)<a name="ga9a971efefb28e62b22de4e5f2567da81"></a>

```
int fegetenv ([fenv_t](fenv_t.md) * envp)
```

 **Description:**

Stores the current floating-point environment into the object specified by  **envp**. 

The floating-point environment contains the current control modes and status flags of floating-point operations. 

**Parameters:**

<a name="table522343616084824"></a>
<table><thead align="left"><tr id="row1042728584084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p192011307084824"><a name="p192011307084824"></a><a name="p192011307084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2026064459084824"><a name="p2026064459084824"></a><a name="p2026064459084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row560306198084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">envp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the floating-point environment. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fegetexceptflag\(\)<a name="gadc77aa0943782d65cd89a7ad931efccd"></a>

```
int fegetexceptflag ([fexcept_t](math.md#ga3eec78fdb9921de3f7254105f546c624) * flagp, int excepts )
```

 **Description:**

Stores the floating-point exceptions specified by  **excepts**  into the  **flagp**  variable address. 

**Parameters:**

<a name="table936607585084824"></a>
<table><thead align="left"><tr id="row41065970084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1105492509084824"><a name="p1105492509084824"></a><a name="p1105492509084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1414829310084824"><a name="p1414829310084824"></a><a name="p1414829310084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2094757784084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flagp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the floating-point exceptions. </td>
</tr>
<tr id="row54842569084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">excepts</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the current floating-point exceptions to store. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fegetround\(\)<a name="gaf43d2de25e6d5e3b65b1d1f32c01b3c8"></a>

```
int fegetround (void )
```

 **Description:**

Obtains the macro corresponding to the current rounding mode. 

The rounding mode can be  [FE\_TONEAREST](math.md#ga5b5383719a63f98b7c95cc2feccaa1a7),  [FE\_UPWARD](math.md#ga5aa71a164a4b4d7780570d97058890f1),  [FE\_DOWNWARD](math.md#ga5e011a345a41ad4622da05932e83536f), or  [FE\_TOWARDZERO](math.md#gac171099e006285a9e8be5683be71591c). 

**Returns:**

Returns the macro corresponding to the current rounding mode. 



## feholdexcept\(\)<a name="ga7bf2aed63eeaa74f4295a996b3ba4616"></a>

```
int feholdexcept ([fenv_t](fenv_t.md) * envp)
```

 **Description:**

Stores the current floating-point environment into the object specified by  **envp**, with all status flags cleared. 

**Parameters:**

<a name="table63460677084824"></a>
<table><thead align="left"><tr id="row39588264084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p687220582084824"><a name="p687220582084824"></a><a name="p687220582084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1790405948084824"><a name="p1790405948084824"></a><a name="p1790405948084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row218920289084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">envp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the floating-point environment. </td>
</tr>
</tbody>
</table>

**Attention:**

This function clears all exception status flags and sets the environment to the non-stop mode \(to continue the execution of the exceptions\), if any. 

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## feraiseexcept\(\)<a name="gaeecf59ba4dd156c6a9954bd0c1a9f6eb"></a>

```
int feraiseexcept (int excepts)
```

 **Description:**

Obtains the floating-point exceptions specified by  **excepts**. 

**Parameters:**

<a name="table1107646651084824"></a>
<table><thead align="left"><tr id="row113458511084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p295212062084824"><a name="p295212062084824"></a><a name="p295212062084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p623723185084824"><a name="p623723185084824"></a><a name="p623723185084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1554756643084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">excepts</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point exceptions to obtain. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fesetenv\(\)<a name="ga65184dc5ad4e001083a6fd59d0cd7a2d"></a>

```
int fesetenv (const [fenv_t](fenv_t.md) * envp)
```

 **Description:**

Sets the current floating-point environment. 

This function restores the floating-point environment from the object specified by  **envp**. The floating-point environment contains the current control modes and status flags of floating-point operations. 

**Parameters:**

<a name="table1132728831084824"></a>
<table><thead align="left"><tr id="row1205304476084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p188158082084824"><a name="p188158082084824"></a><a name="p188158082084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1436841315084824"><a name="p1436841315084824"></a><a name="p1436841315084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1741454435084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">envp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the floating-point environment. </td>
</tr>
</tbody>
</table>

**Attention:**

The object specified by  **envp**  must be valid. 

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fesetexceptflag\(\)<a name="gafb3852ee8f5a841548c91bac153ee3d1"></a>

```
int fesetexceptflag (const [fexcept_t](math.md#ga3eec78fdb9921de3f7254105f546c624) * flagp, int excepts )
```

 **Description:**

Sets the exception status flag by copying the floating-point exceptions stored in the  **flagp**  address to the  **excepts**  parameter. 

**Parameters:**

<a name="table523523796084824"></a>
<table><thead align="left"><tr id="row670810836084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1058678669084824"><a name="p1058678669084824"></a><a name="p1058678669084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2048485243084824"><a name="p2048485243084824"></a><a name="p2048485243084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1234268356084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flagp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the floating-point exceptions. </td>
</tr>
<tr id="row1743197091084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">excepts</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the current floating-point exceptions to store. </td>
</tr>
</tbody>
</table>

**Attention:**

Before using this function, ensure that you have successfully called  [fegetexceptflag](math.md#gadc77aa0943782d65cd89a7ad931efccd). 

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fesetround\(\)<a name="ga5729c4728ebe75d4975bb7250a2d8f4a"></a>

```
int fesetround (int rounding_mode)
```

 **Description:**

Sets the rounding mode. 

The rounding mode can be  [FE\_TONEAREST](math.md#ga5b5383719a63f98b7c95cc2feccaa1a7),  [FE\_UPWARD](math.md#ga5aa71a164a4b4d7780570d97058890f1),  [FE\_DOWNWARD](math.md#ga5e011a345a41ad4622da05932e83536f), or  [FE\_TOWARDZERO](math.md#gac171099e006285a9e8be5683be71591c). 

**Parameters:**

<a name="table221420349084824"></a>
<table><thead align="left"><tr id="row1941723907084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1036958813084824"><a name="p1036958813084824"></a><a name="p1036958813084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p890172988084824"><a name="p890172988084824"></a><a name="p890172988084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1173168985084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rounding_mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the rounding mode to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## fetestexcept\(\)<a name="ga1fd22f10456d303ba12c28e394b1da90"></a>

```
int fetestexcept (int excepts)
```

 **Description:**

Checks whether the floating-point exceptions specified by  **excepts**  have been raised. 

For example, if the value of  **excepts**  is  **[FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  |  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)**, this function checks whether the current floating-point operation has thrown an overflow exception or is invalid. 

**Parameters:**

<a name="table2112597198084824"></a>
<table><thead align="left"><tr id="row1419343334084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1234360625084824"><a name="p1234360625084824"></a><a name="p1234360625084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p390492341084824"><a name="p390492341084824"></a><a name="p390492341084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row483356623084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">excepts</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the floating-point exceptions. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the macros describing the specified exceptions if they have been raised; returns  **0**  if the specified exceptions do not exist. 



## feupdateenv\(\)<a name="gaa8c45da6bfe39178d4d199d3f0f6bbaf"></a>

```
int feupdateenv (const [fenv_t](fenv_t.md) * envp)
```

 **Description:**

Updates the current floating-point environment from the object specified by  **envp**. 

**Parameters:**

<a name="table854385633084824"></a>
<table><thead align="left"><tr id="row1392935328084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p225783205084824"><a name="p225783205084824"></a><a name="p225783205084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p293001909084824"><a name="p293001909084824"></a><a name="p293001909084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row921131727084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">envp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the floating-point environment. </td>
</tr>
</tbody>
</table>

**Attention:**

The object specified by  **envp**  must be valid. 

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## finite\(\)<a name="ga08e754462e6ec13bc05fd41cff9cdd4a"></a>

```
int finite (double x)
```

 **Description:**

Checks whether the double value  **x**  is an infinity or a NaN value. 

**Parameters:**

<a name="table1745275014084824"></a>
<table><thead align="left"><tr id="row376999561084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1179107244084824"><a name="p1179107244084824"></a><a name="p1179107244084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p336436539084824"><a name="p336436539084824"></a><a name="p336436539084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1260438729084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if  **x**  is an infinity or a NaN value; returns  **1**  otherwise. 



## finitef\(\)<a name="gaea39ac813876c506f8c351e6c14a5cb7"></a>

```
int finitef (float x)
```

 **Description:**

Checks whether the float value  **x**  is an infinity or a NaN value. 

**Parameters:**

<a name="table1336864027084824"></a>
<table><thead align="left"><tr id="row996098164084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1579557881084824"><a name="p1579557881084824"></a><a name="p1579557881084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p845110692084824"><a name="p845110692084824"></a><a name="p845110692084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1906467031084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value to check. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if  **x**  is an infinity or a NaN value; returns  **1**  otherwise. 



## floor\(\)<a name="ga6de60a3e907dcf0bfe3ea8d64f1e8873"></a>

```
double floor (double x)
```

 **Description:**

Obtains the largest integer less than or equal to the double value  **x**. 

**Parameters:**

<a name="table1536166238084824"></a>
<table><thead align="left"><tr id="row884400058084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1338562702084824"><a name="p1338562702084824"></a><a name="p1338562702084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1661507342084824"><a name="p1661507342084824"></a><a name="p1661507342084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row573629753084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1014859538084824"><a name="b1014859538084824"></a><a name="b1014859538084824"></a>x</strong> to compare with. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the largest integer less than or equal to  **x**. 



## floorf\(\)<a name="ga0bcc6aa4b3c37bfa73f06ebdecc0d247"></a>

```
float floorf (float x)
```

 **Description:**

Obtains the largest integer less than or equal to the float value  **x**. 

**Parameters:**

<a name="table593356137084824"></a>
<table><thead align="left"><tr id="row198607761084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p358176340084824"><a name="p358176340084824"></a><a name="p358176340084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p390950283084824"><a name="p390950283084824"></a><a name="p390950283084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1507595464084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1628510589084824"><a name="b1628510589084824"></a><a name="b1628510589084824"></a>x</strong> to compare with. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the largest integer less than or equal to  **x**. 



## floorl\(\)<a name="ga211df53cdf5208b9bbfa92e2d9aef97f"></a>

```
long double floorl (long double x)
```

 **Description:**

Obtains the largest integer less than or equal to the long double value  **x**. 

**Parameters:**

<a name="table1245910959084824"></a>
<table><thead align="left"><tr id="row2041274460084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1221368506084824"><a name="p1221368506084824"></a><a name="p1221368506084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2041387897084824"><a name="p2041387897084824"></a><a name="p2041387897084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row786134481084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b286153873084824"><a name="b286153873084824"></a><a name="b286153873084824"></a>x</strong> to compare with. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the largest integer less than or equal to  **x**. 



## fma\(\)<a name="gac6df7bd41d198a70da3915a80de5452d"></a>

```
double fma (double x, double y, double z )
```

 **Description:**

Calculates the value of  **x\*y+z**  and rounds the result up. 

**Parameters:**

<a name="table1121027115084824"></a>
<table><thead align="left"><tr id="row1077653930084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2080894939084824"><a name="p2080894939084824"></a><a name="p2080894939084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p536041508084824"><a name="p536041508084824"></a><a name="p536041508084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row459226129084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b451195229084824"><a name="b451195229084824"></a><a name="b451195229084824"></a>x</strong>. </td>
</tr>
<tr id="row2141414667084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b575126303084824"><a name="b575126303084824"></a><a name="b575126303084824"></a>y</strong>. </td>
</tr>
<tr id="row61485523084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b113934473084824"><a name="b113934473084824"></a><a name="b113934473084824"></a>z</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The rounding mode is the same as that set in the system. 

**Returns:**

Returns the calculation result. 



## fmaf\(\)<a name="gaa6b32a0b7f88680bb59bcfb9c6168ed2"></a>

```
float fmaf (float x, float y, float z )
```

 **Description:**

Calculates the value of  **x\*y+z**  and rounds the result up. 

**Parameters:**

<a name="table1881711435084824"></a>
<table><thead align="left"><tr id="row394424778084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p349670203084824"><a name="p349670203084824"></a><a name="p349670203084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p237654832084824"><a name="p237654832084824"></a><a name="p237654832084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1665250623084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b670797773084824"><a name="b670797773084824"></a><a name="b670797773084824"></a>x</strong>. </td>
</tr>
<tr id="row1732711589084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b824166950084824"><a name="b824166950084824"></a><a name="b824166950084824"></a>y</strong>. </td>
</tr>
<tr id="row450471774084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1349932456084824"><a name="b1349932456084824"></a><a name="b1349932456084824"></a>z</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The rounding mode is the same as that set in the system. 

**Returns:**

Returns the calculation result. 



## fmal\(\)<a name="gaf30b6b26252979964796ffa55dd30120"></a>

```
long double fmal (long double x, long double y, long double z )
```

 **Description:**

Calculates the value of  **x\*y+z**  and rounds the result up. 

**Parameters:**

<a name="table6867598084824"></a>
<table><thead align="left"><tr id="row130228169084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2010919698084824"><a name="p2010919698084824"></a><a name="p2010919698084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1607981648084824"><a name="p1607981648084824"></a><a name="p1607981648084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1160502984084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1162576924084824"><a name="b1162576924084824"></a><a name="b1162576924084824"></a>x</strong>. </td>
</tr>
<tr id="row2113945653084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b2078332195084824"><a name="b2078332195084824"></a><a name="b2078332195084824"></a>y</strong>. </td>
</tr>
<tr id="row861155213084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">z</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b531130235084824"><a name="b531130235084824"></a><a name="b531130235084824"></a>z</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The rounding mode is the same as that set in the system. 

**Returns:**

Returns the calculation result. 



## fmax\(\)<a name="ga35e041615ac931b4d848a7b173049301"></a>

```
double fmax (double x, double y )
```

 **Description:**

Obtains the larger value of two double values  **x**  and  **y**. 

**Parameters:**

<a name="table626776458084824"></a>
<table><thead align="left"><tr id="row1764532903084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1531830952084824"><a name="p1531830952084824"></a><a name="p1531830952084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p693036357084824"><a name="p693036357084824"></a><a name="p693036357084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1014314521084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b483399950084824"><a name="b483399950084824"></a><a name="b483399950084824"></a>x</strong>. </td>
</tr>
<tr id="row2036782123084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1235020316084824"><a name="b1235020316084824"></a><a name="b1235020316084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the larger value. 



## fmaxf\(\)<a name="ga8849bfdbec18ded429fad4772cf60f4b"></a>

```
float fmaxf (float x, float y )
```

 **Description:**

Obtains the larger value of two float values  **x**  and  **y**. 

**Parameters:**

<a name="table1393623289084824"></a>
<table><thead align="left"><tr id="row1849816566084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1925453826084824"><a name="p1925453826084824"></a><a name="p1925453826084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1499626483084824"><a name="p1499626483084824"></a><a name="p1499626483084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row397579372084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1463521477084824"><a name="b1463521477084824"></a><a name="b1463521477084824"></a>x</strong>. </td>
</tr>
<tr id="row1219182174084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b292886035084824"><a name="b292886035084824"></a><a name="b292886035084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the larger value. 



## fmaxl\(\)<a name="ga0e31e170115494fdc03b6556844232f3"></a>

```
long double fmaxl (long double x, long double y )
```

 **Description:**

Obtains the larger value of two long double values  **x**  and  **y**. 

**Parameters:**

<a name="table1848057502084824"></a>
<table><thead align="left"><tr id="row941266836084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p756382565084824"><a name="p756382565084824"></a><a name="p756382565084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p833939629084824"><a name="p833939629084824"></a><a name="p833939629084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row262540621084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b438622224084824"><a name="b438622224084824"></a><a name="b438622224084824"></a>x</strong>. </td>
</tr>
<tr id="row1362513837084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b515456143084824"><a name="b515456143084824"></a><a name="b515456143084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the larger value. 



## fmin\(\)<a name="gaf0a18b3ac9e461ac48b4cfffb4945a84"></a>

```
double fmin (double x, double y )
```

 **Description:**

Obtains the smaller value of two double values  **x**  and  **y**. 

**Parameters:**

<a name="table521601801084824"></a>
<table><thead align="left"><tr id="row1980156561084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1398040771084824"><a name="p1398040771084824"></a><a name="p1398040771084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p861500186084824"><a name="p861500186084824"></a><a name="p861500186084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row326377550084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1244297166084824"><a name="b1244297166084824"></a><a name="b1244297166084824"></a>x</strong>. </td>
</tr>
<tr id="row930143905084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1812351964084824"><a name="b1812351964084824"></a><a name="b1812351964084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the smaller value. 



## fminf\(\)<a name="ga9b4132c27f31d39c91c3c6063f378103"></a>

```
float fminf (float x, float y )
```

 **Description:**

Obtains the smaller value of two float values  **x**  and  **y**. 

**Parameters:**

<a name="table1007011914084824"></a>
<table><thead align="left"><tr id="row508947056084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1490319268084824"><a name="p1490319268084824"></a><a name="p1490319268084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p26192958084824"><a name="p26192958084824"></a><a name="p26192958084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1880143879084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1343369233084824"><a name="b1343369233084824"></a><a name="b1343369233084824"></a>x</strong>. </td>
</tr>
<tr id="row1716066513084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1216729511084824"><a name="b1216729511084824"></a><a name="b1216729511084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the smaller value. 



## fminl\(\)<a name="ga8a301190384886aa4e327db265fb5c9f"></a>

```
long double fminl (long double x, long double y )
```

 **Description:**

Obtains the smaller value of two long double values  **x**  and  **y**. 

**Parameters:**

<a name="table245607080084824"></a>
<table><thead align="left"><tr id="row1170721858084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1759764241084824"><a name="p1759764241084824"></a><a name="p1759764241084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p778867507084824"><a name="p778867507084824"></a><a name="p778867507084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1358163732084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b2046322590084824"><a name="b2046322590084824"></a><a name="b2046322590084824"></a>x</strong>. </td>
</tr>
<tr id="row720989126084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b515679191084824"><a name="b515679191084824"></a><a name="b515679191084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the smaller value. 



## fmod\(\)<a name="ga537296d1a8f9fb621676038b99ba7edf"></a>

```
double fmod (double x, double y )
```

 **Description:**

Calculates the remainder of the double value  **x**  divided by the double value  **y**. 

 

**Parameters:**

<a name="table1101897123084824"></a>
<table><thead align="left"><tr id="row1912153518084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p338652699084824"><a name="p338652699084824"></a><a name="p338652699084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p229488971084824"><a name="p229488971084824"></a><a name="p229488971084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1040770589084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1609690526084824"><a name="b1609690526084824"></a><a name="b1609690526084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row2015744060084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b110889306084824"><a name="b110889306084824"></a><a name="b110889306084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the remainder. 



## fmodf\(\)<a name="gaf17ec425baca2b5f3882a05b5e19dfb5"></a>

```
float fmodf (float x, float y )
```

 **Description:**

Calculates the remainder of the float value  **x**  divided by the float value  **y**. 

**Parameters:**

<a name="table630153133084824"></a>
<table><thead align="left"><tr id="row889200303084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1576646313084824"><a name="p1576646313084824"></a><a name="p1576646313084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1308482509084824"><a name="p1308482509084824"></a><a name="p1308482509084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1824562677084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b658874868084824"><a name="b658874868084824"></a><a name="b658874868084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row1502630010084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b161819427084824"><a name="b161819427084824"></a><a name="b161819427084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the remainder. 



## fmodl\(\)<a name="gaa927d9996fb40db42bd3a6cbe57da9a7"></a>

```
long double fmodl (long double x, long double y )
```

 **Description:**

Calculates the remainder of the long double value  **x**  divided by the long double value  **y**. 

**Parameters:**

<a name="table1362301327084824"></a>
<table><thead align="left"><tr id="row681261971084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1433517498084824"><a name="p1433517498084824"></a><a name="p1433517498084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2067183688084824"><a name="p2067183688084824"></a><a name="p2067183688084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1708270281084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1388235398084824"><a name="b1388235398084824"></a><a name="b1388235398084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row1522905861084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b521597666084824"><a name="b521597666084824"></a><a name="b521597666084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the remainder. 



## frexp\(\)<a name="gae3fa88adf02f16a693f3dccea3c42ef0"></a>

```
double frexp (double x, int * exp )
```

 **Description:**

Decomposes the double value  **x**  into a significand and an integral exponent for 2. 

The absolute value of the significand ranges from 0.5 \(included\) to 1 \(excluded\). x = significand \* 2^exponent 

**Parameters:**

<a name="table1738125814084824"></a>
<table><thead align="left"><tr id="row1986626321084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1779771936084824"><a name="p1779771936084824"></a><a name="p1779771936084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1047351866084824"><a name="p1047351866084824"></a><a name="p1047351866084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row477057456084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b384521182084824"><a name="b384521182084824"></a><a name="b384521182084824"></a>x</strong> to decompose. </td>
</tr>
<tr id="row1197951327084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the binary significand of  **x**  if the operation is successful; returns  **0**  if  **x**  is  **0**  \(**exp**  is also  **0**\); returns a NaN value if  **x**  is a NaN value \(**exp**  is not specified\); returns a positive or negative infinity if  **x**  is a positive or negative infinity, respectively \(**exp**  is not specified\). 



## frexpf\(\)<a name="ga12c36e745d8a9eb4f01c7e0eeb426dd3"></a>

```
float frexpf (float x, int * exp )
```

 **Description:**

Decomposes float value  **x**  into a binary significand and an integral exponent for 2. 

The absolute value of the significand ranges from 0.5 \(included\) to 1 \(excluded\). x = significand \* 2^exponent 

**Parameters:**

<a name="table968832689084824"></a>
<table><thead align="left"><tr id="row449653038084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2080560613084824"><a name="p2080560613084824"></a><a name="p2080560613084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p240050113084824"><a name="p240050113084824"></a><a name="p240050113084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row703324676084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value to decompose. </td>
</tr>
<tr id="row1711452203084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to an integer where the exponent is stored. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the binary significand of  **x**  if the operation is successful; returns  **0**  if  **x**  is  **0**  \(**exp**  is also  **0**\); returns a NaN value if  **x**  is a NaN value \(**exp**  is not specified\); returns a positive or negative infinity if  **x**  is a positive or negative infinity \(**exp**  is not specified\). 



## frexpl\(\)<a name="ga239d50c0595ff8538b9aa3186ac4fd29"></a>

```
long double frexpl (long double x, int * exp )
```

 **Description:**

Decomposes long double value  **x**  into a binary significand and an integral exponent for 2. 

The absolute value of the significand ranges from 0.5 \(included\) to 1 \(excluded\). x = significand \* 2^exponent 

**Parameters:**

<a name="table742188307084824"></a>
<table><thead align="left"><tr id="row1836227725084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1572656943084824"><a name="p1572656943084824"></a><a name="p1572656943084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1124923115084824"><a name="p1124923115084824"></a><a name="p1124923115084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2056662587084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value to decompose. </td>
</tr>
<tr id="row973239905084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to an integer where the exponent is stored. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the binary significand of  **x**  if the operation is successful; returns  **0**  if  **x**  is  **0**  \(**exp**  is also  **0**\); returns a NaN value if  **x**  is a NaN value \(**exp**  is not specified\); returns a positive or negative infinity if  **x**  is a positive or negative infinity \(**exp**  is not specified\). 



## hypot\(\)<a name="ga6d6a905f61d535f8454190433b8c0ea5"></a>

```
double hypot (double x, double y )
```

 **Description:**

Calculates the hypotenuse of a right triangle whose legs are  **x**  and  **y**. 

**Parameters:**

<a name="table733868043084824"></a>
<table><thead align="left"><tr id="row1581332642084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1399795624084824"><a name="p1399795624084824"></a><a name="p1399795624084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1074084795084824"><a name="p1074084795084824"></a><a name="p1074084795084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row552846996084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of one side of the right triangle, represented using a double value. </td>
</tr>
<tr id="row440088734084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the other side of the right triangle, represented using a double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hypotenuse of the right triangle. 



## hypotf\(\)<a name="ga9fa4a03d7c4abfda7d9ad7b6ff7f6456"></a>

```
float hypotf (float x, float y )
```

 **Description:**

Calculates the hypotenuse of a right triangle whose legs are  **x**  and  **y**. 

**Parameters:**

<a name="table614545262084824"></a>
<table><thead align="left"><tr id="row632549574084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2006859176084824"><a name="p2006859176084824"></a><a name="p2006859176084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1769886537084824"><a name="p1769886537084824"></a><a name="p1769886537084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row717022291084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of one side of the right triangle, represented using a float value. </td>
</tr>
<tr id="row1561610680084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the other side of the right triangle, represented using a float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hypotenuse of the right triangle. 



## hypotl\(\)<a name="ga92a0e76d17c34fc1b3b2e7c0868aea6e"></a>

```
long double hypotl (long double x, long double y )
```

 **Description:**

Calculates the hypotenuse of a right triangle whose legs are  **x**  and  **y**. 

**Parameters:**

<a name="table734066626084824"></a>
<table><thead align="left"><tr id="row432488239084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1589051625084824"><a name="p1589051625084824"></a><a name="p1589051625084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1058255282084824"><a name="p1058255282084824"></a><a name="p1058255282084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row178754439084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of one side of the right triangle, represented using a long double value. </td>
</tr>
<tr id="row1575539891084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the other side of the right triangle, represented using a long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hypotenuse of the right triangle. 



## ilogb\(\)<a name="ga600dd249210d15af31b9a29c2d09d255"></a>

```
int ilogb (double x)
```

 **Description:**

Obtains the integral part of the logarithm of double value  **x**. 

**FLT\_RADIX**  is used as the base for the logarithm. 

**Parameters:**

<a name="table2067145705084824"></a>
<table><thead align="left"><tr id="row629150520084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p838836515084824"><a name="p838836515084824"></a><a name="p838836515084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2010568919084824"><a name="p2010568919084824"></a><a name="p2010568919084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2018709667084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the integral part of the logarithm of  **x**  if the operation is successful. If  **x**  is  **0**, this function returns  [FP\_ILOGB0](math.md#ga9ec0e31304d15c42262b2c4a3b58443c)  and reports a domain error. If  **x**  is a NaN value, this function returns  [FP\_ILOGBNAN](math.md#ga01e2e5be97c739a5bdcbc619b44f9742)  and reports a domain error. If  **x**  is positive or negative infinity, this function returns  [INT\_MAX](utils.md#ga9ec306f36d50c7375e74f0d1c55a3a67)  and reports a domain error. 



## ilogbf\(\)<a name="gaf53f0f07bb80b1a38fb47773a190e7a7"></a>

```
int ilogbf (float x)
```

 **Description:**

Obtains the integral part of the logarithm of float value  **x**. 

**FLT\_RADIX**  is used as the base for the logarithm. 

**Parameters:**

<a name="table981619101084824"></a>
<table><thead align="left"><tr id="row1197790095084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p775409553084824"><a name="p775409553084824"></a><a name="p775409553084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p818142147084824"><a name="p818142147084824"></a><a name="p818142147084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row186917590084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the integral part of the logarithm of  **x**  if the operation is successful. If  **x**  is  **0**, this function returns  [FP\_ILOGB0](math.md#ga9ec0e31304d15c42262b2c4a3b58443c)  and reports a domain error. If  **x**  is a NaN value, this function returns  [FP\_ILOGBNAN](math.md#ga01e2e5be97c739a5bdcbc619b44f9742)  and reports a domain error. If  **x**  is positive or negative infinity, this function returns  [INT\_MAX](utils.md#ga9ec306f36d50c7375e74f0d1c55a3a67)  and reports a domain error. 



## ilogbl\(\)<a name="gafbd166ed232a372f090b8f9fa8441423"></a>

```
int ilogbl (long double x)
```

 **Description:**

Obtains the integral part of the logarithm of the long double value  **x**. 

**FLT\_RADIX**  is used as the base for the logarithm. 

**Parameters:**

<a name="table178213972084824"></a>
<table><thead align="left"><tr id="row1917424497084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2065439474084824"><a name="p2065439474084824"></a><a name="p2065439474084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p187306473084824"><a name="p187306473084824"></a><a name="p187306473084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1210302164084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the integral part of the logarithm of  **x**  if the operation is successful. If  **x**  is  **0**, this function returns  [FP\_ILOGB0](math.md#ga9ec0e31304d15c42262b2c4a3b58443c)  and reports a domain error. If  **x**  is a NaN value, this function returns  [FP\_ILOGBNAN](math.md#ga01e2e5be97c739a5bdcbc619b44f9742)  and reports a domain error. If  **x**  is positive or negative infinity, this function returns  [INT\_MAX](utils.md#ga9ec306f36d50c7375e74f0d1c55a3a67)  and reports a domain error. 



## j0\(\)<a name="gaffb00730a1127dee798137075951ae21"></a>

```
double j0 (double x)
```

 **Description:**

Calculates the Bessel function of the first kind of order  **0**  for the double value  **x**. 

**Parameters:**

<a name="table410470838084824"></a>
<table><thead align="left"><tr id="row1549754881084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p395173706084824"><a name="p395173706084824"></a><a name="p395173706084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p523384497084824"><a name="p523384497084824"></a><a name="p523384497084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row3830078084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the Bessel function of the first kind of order  **0**  for  **x**  if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **0**  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)  if  **x**  is too large or an overflow range error occurs. 



## j0f\(\)<a name="gafa59b98550749c27995dfb7c70e6783a"></a>

```
float j0f (float x)
```

 **Description:**

Calculates the Bessel function of the first kind of order  **0**  for the float value  **x**. 

**Parameters:**

<a name="table184473551084824"></a>
<table><thead align="left"><tr id="row119961870084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p389888264084824"><a name="p389888264084824"></a><a name="p389888264084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1802843327084824"><a name="p1802843327084824"></a><a name="p1802843327084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1984691272084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **0**  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)  if  **x**  is too large or an overflow range error occurs. 



## j1\(\)<a name="ga8cac4aa70c418eba481417f1878b4cee"></a>

```
double j1 (double x)
```

 **Description:**

Calculates the Bessel function of the first kind of order  **1**  for the double value  **x**. 

**Parameters:**

<a name="table484806914084824"></a>
<table><thead align="left"><tr id="row1785543538084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p841227199084824"><a name="p841227199084824"></a><a name="p841227199084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p938781670084824"><a name="p938781670084824"></a><a name="p938781670084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row244728809084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the Bessel function of the first kind of order  **1**  for  **x**  if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **0**  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)  if  **x**  is too large or an overflow range error occurs. 



## j1f\(\)<a name="ga4b50bbed127a1c57940d600498a3c5c7"></a>

```
float j1f (float x)
```

 **Description:**

Calculates the Bessel function of the first kind of order  **1**  for the float value  **x**. 

**Parameters:**

<a name="table908303014084824"></a>
<table><thead align="left"><tr id="row218194757084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p562782605084824"><a name="p562782605084824"></a><a name="p562782605084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p902751942084824"><a name="p902751942084824"></a><a name="p902751942084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row601611033084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **0**  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)  if  **x**  is too large or an overflow range error occurs. 



## jn\(\)<a name="gadeff843dc8106ffda5caba6df44c591d"></a>

```
double jn (int n, double x )
```

 **Description:**

Calculates the Bessel function of the first kind of order  **n**  for the double value  **x**. 

**Parameters:**

<a name="table878618580084824"></a>
<table><thead align="left"><tr id="row33319373084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p863729467084824"><a name="p863729467084824"></a><a name="p863729467084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p740680081084824"><a name="p740680081084824"></a><a name="p740680081084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row593259097084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">n</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the order of the Bessel function of the first kind. </td>
</tr>
<tr id="row370799829084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the Bessel function of the first kind of order  **n**  for  **x**  if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **0**  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)  if  **x**  is too large or an overflow range error occurs. 



## jnf\(\)<a name="gac3fcdfd92a775eed4ebd673d7da02525"></a>

```
float jnf (int n, float x )
```

 **Description:**

Calculates the Bessel function of the first kind of order  **n**  for the float value  **x**. 

**Parameters:**

<a name="table1834252892084824"></a>
<table><thead align="left"><tr id="row1865805385084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1624509995084824"><a name="p1624509995084824"></a><a name="p1624509995084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p382955527084824"><a name="p382955527084824"></a><a name="p382955527084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row703967726084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">n</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the order of the Bessel function of the first kind. </td>
</tr>
<tr id="row2106004885084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **0**  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)  if  **x**  is too large or an overflow range error occurs. 



## ldexp\(\)<a name="gab3662815756f0bd419dc1b12f4ad905d"></a>

```
double ldexp (double x, int exp )
```

 **Description:**

Multiplies the double value  **x**  by 2 raised to the power of  **exp**. 

The calculation formula is x\*2^exp. 

**Parameters:**

<a name="table2115139154084824"></a>
<table><thead align="left"><tr id="row1797582415084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p404573077084824"><a name="p404573077084824"></a><a name="p404573077084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p807704945084824"><a name="p807704945084824"></a><a name="p807704945084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1490010400084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
<tr id="row318454863084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result. 



## ldexpf\(\)<a name="gaacd370a7830c29f47239dea1ea2eb7f9"></a>

```
float ldexpf (float x, int exp )
```

 **Description:**

Multiplies the float value  **x**  by 2 raised to the power of  **exp**. 

The calculation formula is x\*2^exp. 

**Parameters:**

<a name="table1057308569084824"></a>
<table><thead align="left"><tr id="row793856452084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1136235702084824"><a name="p1136235702084824"></a><a name="p1136235702084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1075535241084824"><a name="p1075535241084824"></a><a name="p1075535241084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row970846753084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
<tr id="row991420447084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result. 



## ldexpl\(\)<a name="ga454187039ef790629dab1e7724c3c3b2"></a>

```
long double ldexpl (long double x, int exp )
```

 **Description:**

Multiplies the long double value  **x**  by 2 raised to the power of  **exp**. 

The calculation formula is x\*2^exp. 

**Parameters:**

<a name="table108227241084824"></a>
<table><thead align="left"><tr id="row981111349084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1380298001084824"><a name="p1380298001084824"></a><a name="p1380298001084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p31867736084824"><a name="p31867736084824"></a><a name="p31867736084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1054098378084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
<tr id="row609510364084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result. 



## lgamma\(\)<a name="gacd3ebe923fa039624f0b7de3320816bf"></a>

```
double lgamma (double x)
```

 **Description:**

Calculates the natural logarithm of the absolute value of the gamma function of the double value  **x**. 

**Parameters:**

<a name="table37785917084824"></a>
<table><thead align="left"><tr id="row609689256084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p341035514084824"><a name="p341035514084824"></a><a name="p341035514084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p186639407084824"><a name="p186639407084824"></a><a name="p186639407084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1791952398084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **1**  or  **2**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If  **x**  is  **0**  or a negative value, this function returns one of +[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)\). If an overflow range error occurs, this function returns one of  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  \* and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## lgammaf\(\)<a name="ga5900f7bf0093757f1ba36b5940b1e10b"></a>

```
float lgammaf (float x)
```

 **Description:**

Calculates the natural logarithm of the absolute value of the gamma function of the float value  **x**. 

**Parameters:**

<a name="table2003270396084824"></a>
<table><thead align="left"><tr id="row900049866084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1900104659084824"><a name="p1900104659084824"></a><a name="p1900104659084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1723320502084824"><a name="p1723320502084824"></a><a name="p1723320502084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row489084250084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **1**  or  **2**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If  **x**  is  **0**  or a negative value, this function returns one of +[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359), reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). If an overflow range error occurs, this function returns one of  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## lgammal\(\)<a name="ga4dafd3eb6952c8daabe8a98f4a64a7df"></a>

```
long double lgammal (long double x)
```

 **Description:**

Calculates the natural logarithm of the absolute value of the gamma function of the long double value  **x**. 

**Parameters:**

<a name="table1727093797084824"></a>
<table><thead align="left"><tr id="row1997026863084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p317979950084824"><a name="p317979950084824"></a><a name="p317979950084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p714574298084824"><a name="p714574298084824"></a><a name="p714574298084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1860985789084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **1**  or  **2**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If  **x**  is  **0**  or a negative value, this function returns one of +[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182), reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). If an overflow range error occurs, this function returns one of  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## lgammal\_r\(\)<a name="ga278e86e217081a0268107f0d6876cb9b"></a>

```
long double lgammal_r (long double x, int * signp )
```

 **Description:**

Calculates the natural logarithm of the absolute value of the gamma function of the double value  **x**. 

**Parameters:**

<a name="table1478453608084824"></a>
<table><thead align="left"><tr id="row73834905084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p151779892084824"><a name="p151779892084824"></a><a name="p151779892084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p960393221084824"><a name="p960393221084824"></a><a name="p960393221084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row104820823084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
<tr id="row533997309084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">return value of sign. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **1**  or  **2**, this function returns  **+0**. If  **x**  is a positive or negative infinity, this function returns a positive infinity. If  **x**  is  **0**  or a negative value, this function returns one of +[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca)\). If an overflow range error occurs, this function returns one of  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  \* and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## llrint\(\)<a name="ga64a4201c82f6ee7043a270bbbc6a5e19"></a>

```
long long int llrint (double x)
```

 **Description:**

Rounds double value  **x**  to the nearest integer. 

**Parameters:**

<a name="table1204052157084824"></a>
<table><thead align="left"><tr id="row713654019084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1901007326084824"><a name="p1901007326084824"></a><a name="p1901007326084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1918326060084824"><a name="p1918326060084824"></a><a name="p1918326060084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row437215198084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value to round. </td>
</tr>
</tbody>
</table>

**Attention:**

The type of  **x**, rounding mode, and rounding direction are specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## llrintf\(\)<a name="ga33d95711621def731d3f88c4e606323e"></a>

```
long long int llrintf (float x)
```

 **Description:**

Rounds float value  **x**  to the nearest integer. 

**Parameters:**

<a name="table1761178164084824"></a>
<table><thead align="left"><tr id="row1750072065084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2055940018084824"><a name="p2055940018084824"></a><a name="p2055940018084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1088332072084824"><a name="p1088332072084824"></a><a name="p1088332072084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2011420540084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Attention:**

The type of  **x**, rounding mode, and rounding direction are specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## llrintl\(\)<a name="ga20e0da115f76608eff4695177f2f605a"></a>

```
long long int llrintl (long double x)
```

 **Description:**

Rounds long double value  **x**  to the nearest integer. 

**Parameters:**

<a name="table1580005594084824"></a>
<table><thead align="left"><tr id="row506192375084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p545528153084824"><a name="p545528153084824"></a><a name="p545528153084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p673551323084824"><a name="p673551323084824"></a><a name="p673551323084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1109833633084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Attention:**

The type of  **x**, rounding mode, and rounding direction are specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## llround\(\)<a name="ga3e4957daeecea4e616ed1f1870fe4f31"></a>

```
long long int llround (double x)
```

 **Description:**

Rounds double value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table2117240911084824"></a>
<table><thead align="left"><tr id="row273832266084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1216576904084824"><a name="p1216576904084824"></a><a name="p1216576904084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p575100945084824"><a name="p575100945084824"></a><a name="p575100945084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row669460950084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## llroundf\(\)<a name="ga8259999687e8bd4b5509ca0d69b0ad9d"></a>

```
long long int llroundf (float x)
```

 **Description:**

Rounds float value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table478697924084824"></a>
<table><thead align="left"><tr id="row1316183303084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p77210359084824"><a name="p77210359084824"></a><a name="p77210359084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1437190193084824"><a name="p1437190193084824"></a><a name="p1437190193084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row737853310084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## llroundl\(\)<a name="ga82a6d70a29e839514b93bb0699f07bbe"></a>

```
long long int llroundl (long double x)
```

 **Description:**

Rounds long double value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table316717308084824"></a>
<table><thead align="left"><tr id="row1233928523084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2097073537084824"><a name="p2097073537084824"></a><a name="p2097073537084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1083425901084824"><a name="p1083425901084824"></a><a name="p1083425901084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row232271926084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## log\(\)<a name="gadb302c9aafbaa5e180d9f60ee954bb82"></a>

```
double log (double x)
```

 **Description:**

Calculates the natural logarithm of the double value  **x**. 

**Parameters:**

<a name="table538032498084824"></a>
<table><thead align="left"><tr id="row969499424084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1197843568084824"><a name="p1197843568084824"></a><a name="p1197843568084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1305020736084824"><a name="p1305020736084824"></a><a name="p1305020736084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1077622390084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log10\(\)<a name="ga6572e82a4891917a9ba7fb2a964f8182"></a>

```
double log10 (double x)
```

 **Description:**

Calculates the common logarithm \(logarithm with base 10\) of the double value  **x**. 

**Parameters:**

<a name="table520027566084824"></a>
<table><thead align="left"><tr id="row1418300029084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2034036474084824"><a name="p2034036474084824"></a><a name="p2034036474084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p648811510084824"><a name="p648811510084824"></a><a name="p648811510084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row902132719084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log10f\(\)<a name="gae207b1eb007a6c23394dcb6fc7f16adf"></a>

```
float log10f (float x)
```

 **Description:**

Calculates the common logarithm \(logarithm with base 10\) of the float value  **x**. 

**Parameters:**

<a name="table512168885084824"></a>
<table><thead align="left"><tr id="row1889170240084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p724110068084824"><a name="p724110068084824"></a><a name="p724110068084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2070123021084824"><a name="p2070123021084824"></a><a name="p2070123021084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row552661878084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log10l\(\)<a name="gae824e49a04221dcf66b9791c5df8d6b6"></a>

```
long double log10l (long double x)
```

 **Description:**

Calculates the common logarithm \(logarithm with base 10\) of the long double value  **x**. 

**Parameters:**

<a name="table1306547919084824"></a>
<table><thead align="left"><tr id="row522754049084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p230621312084824"><a name="p230621312084824"></a><a name="p230621312084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1965634730084824"><a name="p1965634730084824"></a><a name="p1965634730084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1081707851084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log1p\(\)<a name="gac2aac20ab1347498e6e4f209148fea84"></a>

```
double log1p (double x)
```

 **Description:**

Calculates the natural logarithm of one plus the double value  **x**. 

**Parameters:**

<a name="table691882678084824"></a>
<table><thead align="left"><tr id="row2087810006084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p836259298084824"><a name="p836259298084824"></a><a name="p836259298084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1720600576084824"><a name="p1720600576084824"></a><a name="p1720600576084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row599978874084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of one plus  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **-1**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is less than  **-1**  \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log1pf\(\)<a name="gacbf820b74779ce35a3c726a3a62bc8ef"></a>

```
float log1pf (float x)
```

 **Description:**

Calculates the natural logarithm of one plus the float value  **x**. 

**Parameters:**

<a name="table1603526447084824"></a>
<table><thead align="left"><tr id="row532496347084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2072005358084824"><a name="p2072005358084824"></a><a name="p2072005358084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p78557753084824"><a name="p78557753084824"></a><a name="p78557753084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row646823933084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of one plus  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **-1**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is less than  **-1**  \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log1pl\(\)<a name="ga2a632effaace01f30cba42725ae48dfa"></a>

```
long double log1pl (long double x)
```

 **Description:**

Calculates the natural logarithm of one plus the long double value  **x**. 

**Parameters:**

<a name="table1850654248084824"></a>
<table><thead align="left"><tr id="row1286009795084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1173663378084824"><a name="p1173663378084824"></a><a name="p1173663378084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2075484023084824"><a name="p2075484023084824"></a><a name="p2075484023084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2123355482084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of one plus  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **-1**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is less than  **-1**  \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log2\(\)<a name="ga38bd88274dc5594b4826fd60c8054c8e"></a>

```
double log2 (double x)
```

 **Description:**

Calculates the binary logarithm \(logarithm with base 2\) of the double value  **x**. 

**Parameters:**

<a name="table2083142897084824"></a>
<table><thead align="left"><tr id="row2090429859084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p173626359084824"><a name="p173626359084824"></a><a name="p173626359084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p868757427084824"><a name="p868757427084824"></a><a name="p868757427084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1492666462084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the binary logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log2f\(\)<a name="ga79fe62234001b88317245f7599158aaf"></a>

```
float log2f (float x)
```

 **Description:**

Calculates the binary logarithm \(logarithm with base 2\) of the float value  **x**. 

**Parameters:**

<a name="table1785461780084824"></a>
<table><thead align="left"><tr id="row876177166084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p373889706084824"><a name="p373889706084824"></a><a name="p373889706084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1056074901084824"><a name="p1056074901084824"></a><a name="p1056074901084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1862433643084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the binary logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## log2l\(\)<a name="gaa383ae0cab6c24f1bcba661dee0fbd70"></a>

```
long double log2l (long double x)
```

 **Description:**

Calculates the binary logarithm \(logarithm with base 2\) of the long double value  **x**. 

**Parameters:**

<a name="table1798057801084824"></a>
<table><thead align="left"><tr id="row1785633219084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1883323533084824"><a name="p1883323533084824"></a><a name="p1883323533084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1171118489084824"><a name="p1171118489084824"></a><a name="p1171118489084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1392532263084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the binary \(base-2\) logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## logb\(\)<a name="gaa34bf5be5c3dab058c532adc2792113c"></a>

```
double logb (double x)
```

 **Description:**

Calculates the logarithm of the absolute value of the double value  **x**. 

**FLT\_RADIX**  is used as the base for the logarithm. 

**Parameters:**

<a name="table1139294074084824"></a>
<table><thead align="left"><tr id="row1304047676084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p459757179084824"><a name="p459757179084824"></a><a name="p459757179084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p491700862084824"><a name="p491700862084824"></a><a name="p491700862084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row527523285084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Attention:**

Set  **FLT\_RADIX**  to  **2**  in the  **float.h**  file. 

**Returns:**

Returns the logarithm of the absolute value of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, reports a pole error, and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## logbf\(\)<a name="ga6939b8381c2f160d26913646ca7ab6c4"></a>

```
float logbf (float x)
```

 **Description:**

Calculates the logarithm of the absolute value of the float value  **x**. 

**FLT\_RADIX**  is used as the base for the logarithm. 

**Parameters:**

<a name="table1038063341084824"></a>
<table><thead align="left"><tr id="row2079730877084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1996517796084824"><a name="p1996517796084824"></a><a name="p1996517796084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p418342557084824"><a name="p418342557084824"></a><a name="p418342557084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1820888994084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Attention:**

Set  **FLT\_RADIX**  to  **2**  in the  **float.h**  file. 

**Returns:**

Returns the logarithm of the absolute value of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, reports a pole error, and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## logbl\(\)<a name="ga2f9c0448126d1a838624e3460217bb84"></a>

```
long double logbl (long double x)
```

 **Description:**

Calculates the logarithm of the absolute value of the long double value  **x**. 

**FLT\_RADIX**  is used as the base for the logarithm. 

**Parameters:**

<a name="table1503147774084824"></a>
<table><thead align="left"><tr id="row622510617084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p359182412084824"><a name="p359182412084824"></a><a name="p359182412084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p461226234084824"><a name="p461226234084824"></a><a name="p461226234084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1886086965084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Attention:**

Set  **FLT\_RADIX**  to  **2**  in the  **float.h**  file. 

**Returns:**

Returns the logarithm of the absolute value of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, reports a pole error, and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## logf\(\)<a name="ga8246b3e17a39b137d0c62670d0c6e336"></a>

```
float logf (float x)
```

 **Description:**

Calculates the natural logarithm of the float value  **x**. 

**Parameters:**

<a name="table2054957624084824"></a>
<table><thead align="left"><tr id="row759799266084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p320712755084824"><a name="p320712755084824"></a><a name="p320712755084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p134196110084824"><a name="p134196110084824"></a><a name="p134196110084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row566781333084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## logl\(\)<a name="gaf67da1c28ce33b403f955103f201dfb8"></a>

```
long double logl (long double x)
```

 **Description:**

Calculates the natural logarithm of the long double value  **x**. 

**Parameters:**

<a name="table1718668843084824"></a>
<table><thead align="left"><tr id="row223369911084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p157843232084824"><a name="p157843232084824"></a><a name="p157843232084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p5768328084824"><a name="p5768328084824"></a><a name="p5768328084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row373435056084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the natural logarithm of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is  **0**, this function returns  **-[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is a negative value \(including a negative infinity\), this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. 



## lrint\(\)<a name="ga3337db086394bad101bd8d42d891640a"></a>

```
long int lrint (double x)
```

 **Description:**

Rounds the double value  **x**  to the nearest integer. 

**Parameters:**

<a name="table976061175084824"></a>
<table><thead align="left"><tr id="row153834683084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p568349666084824"><a name="p568349666084824"></a><a name="p568349666084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2117973454084824"><a name="p2117973454084824"></a><a name="p2117973454084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1720560344084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value to round. </td>
</tr>
</tbody>
</table>

**Attention:**

The type of  **x**, rounding mode, and rounding direction are specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## lrintf\(\)<a name="ga16173bca19eef93d0230bfb7c86b5740"></a>

```
long int lrintf (float x)
```

 **Description:**

Rounds the float value  **x**  to the nearest integer. 

**Parameters:**

<a name="table3639609084824"></a>
<table><thead align="left"><tr id="row1973030181084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p877346499084824"><a name="p877346499084824"></a><a name="p877346499084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1302396672084824"><a name="p1302396672084824"></a><a name="p1302396672084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row871318119084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value to round. </td>
</tr>
</tbody>
</table>

**Attention:**

The type of  **x**, rounding mode, and rounding direction are specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## lrintl\(\)<a name="gac6d217e9b96a145f5eeb2a490e6496e6"></a>

```
long int lrintl (long double x)
```

 **Description:**

Rounds the long double value  **x**  to the nearest integer. 

**Parameters:**

<a name="table1976928364084824"></a>
<table><thead align="left"><tr id="row1436530136084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1252186063084824"><a name="p1252186063084824"></a><a name="p1252186063084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1020895736084824"><a name="p1020895736084824"></a><a name="p1020895736084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row48896012084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Attention:**

The type of  **x**, rounding mode, and rounding direction are specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## lround\(\)<a name="ga5936ef27aa03815e9c17d557e87a33d7"></a>

```
long int lround (double x)
```

 **Description:**

Rounds double value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table1944070203084824"></a>
<table><thead align="left"><tr id="row680788606084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1363500668084824"><a name="p1363500668084824"></a><a name="p1363500668084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p143965226084824"><a name="p143965226084824"></a><a name="p143965226084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row802901084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value to round. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## lroundf\(\)<a name="ga0136619b503ddb8ce1a226cd34c9538c"></a>

```
long int lroundf (float x)
```

 **Description:**

Rounds the float value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table1594813977084824"></a>
<table><thead align="left"><tr id="row30074991084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1087480853084824"><a name="p1087480853084824"></a><a name="p1087480853084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1286987184084824"><a name="p1286987184084824"></a><a name="p1286987184084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row804005687084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value to round. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## lroundl\(\)<a name="gafa865c5b70c9311f0f8701a1af60c715"></a>

```
long int lroundl (long double x)
```

 **Description:**

Rounds the long double value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table1763272675084824"></a>
<table><thead align="left"><tr id="row1112309088084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p133547346084824"><a name="p133547346084824"></a><a name="p133547346084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1331347135084824"><a name="p1331347135084824"></a><a name="p1331347135084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1899287207084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value to round. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns an unspecified value if  **x**  is a NaN value or an infinity, or the rounded value is outside the specified range, in which case a domain error or overflow range error occurs. 



## modf\(\)<a name="gafcfe25b77e975450988866fea9d3c9f0"></a>

```
double modf (double x, double * iptr )
```

 **Description:**

Breaks the double value  **x**  into a signed integral and a fractional part. 

**Parameters:**

<a name="table1298273117084824"></a>
<table><thead align="left"><tr id="row1909570385084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p768900600084824"><a name="p768900600084824"></a><a name="p768900600084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1009887218084824"><a name="p1009887218084824"></a><a name="p1009887218084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1997930153084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b2028663902084824"><a name="b2028663902084824"></a><a name="b2028663902084824"></a>x</strong>. </td>
</tr>
<tr id="row1361176990084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the object where the signed integral part is stored. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the fractional part of  **x**. 



## modff\(\)<a name="gad8314f66dfe8603f3a166eb466261ce1"></a>

```
float modff (float x, float * iptr )
```

 **Description:**

Breaks the float value  **x**  into a signed integral and a fractional part. 

**Parameters:**

<a name="table1046956016084824"></a>
<table><thead align="left"><tr id="row1413268582084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p915131591084824"><a name="p915131591084824"></a><a name="p915131591084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1234294560084824"><a name="p1234294560084824"></a><a name="p1234294560084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2088442070084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1709826603084824"><a name="b1709826603084824"></a><a name="b1709826603084824"></a>x</strong>. </td>
</tr>
<tr id="row1098189629084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the object where the signed integral part is stored. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the fractional part of  **x**. 



## modfl\(\)<a name="gabacf3b74f8d7e30a70da8ae47c8e4e3e"></a>

```
long double modfl (long double x, long double * iptr )
```

 **Description:**

Breaks the long double value  **x**  into a signed integral and a fractional part. 

**Parameters:**

<a name="table2044883356084824"></a>
<table><thead align="left"><tr id="row1734832049084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1618868264084824"><a name="p1618868264084824"></a><a name="p1618868264084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1298881796084824"><a name="p1298881796084824"></a><a name="p1298881796084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row692057711084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1824083989084824"><a name="b1824083989084824"></a><a name="b1824083989084824"></a>x</strong>. </td>
</tr>
<tr id="row1118755463084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">iptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the object where the signed integral part is stored. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the fractional part of  **x**. 



## nan\(\)<a name="gaa4ee2f416f261bbd71cda3193c4884c9"></a>

```
double nan (const char * tagp)
```

 **Description:**

Obtains a quiet NaN value of the double type. 

This function checks whether the input parameter is a NaN value and converts it to the double type. 

**Parameters:**

<a name="table1718514937084824"></a>
<table><thead align="left"><tr id="row1560040033084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p907811694084824"><a name="p907811694084824"></a><a name="p907811694084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1126783723084824"><a name="p1126783723084824"></a><a name="p1126783723084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row584950655084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tagp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a character constant. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a quiet NaN value if the operation is successful; returns a NaN value otherwise. 



## nanf\(\)<a name="ga7fe43d4c86419daea2c133e8c5c1a17d"></a>

```
float nanf (const char * tagp)
```

 **Description:**

Obtains a quiet NaN value of the float type. 

This function checks whether the input parameter is a NaN value and converts it to the float type. 

**Parameters:**

<a name="table1142641085084824"></a>
<table><thead align="left"><tr id="row1327499782084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p156806985084824"><a name="p156806985084824"></a><a name="p156806985084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p119957163084824"><a name="p119957163084824"></a><a name="p119957163084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2126453840084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tagp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a character constant. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a quiet NaN value if the operation is successful; returns a NaN value otherwise. 



## nanl\(\)<a name="gac92b1a3a1073a630ae0b7084e596d40f"></a>

```
long double nanl (const char * tagp)
```

 **Description:**

Obtains a quiet NaN value of the long double type. 

This function checks whether the input parameter is a NaN value and converts it to the long double type. 

**Parameters:**

<a name="table112391315084824"></a>
<table><thead align="left"><tr id="row291886869084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1834258449084824"><a name="p1834258449084824"></a><a name="p1834258449084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1354063219084824"><a name="p1354063219084824"></a><a name="p1354063219084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row859863620084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tagp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a character constant. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a quiet NaN value if the operation is successful; returns a NaN value otherwise. 



## nearbyint\(\)<a name="ga61ba6b3078ccbd5aac518e6ca2a757bd"></a>

```
double nearbyint (double x)
```

 **Description:**

Rounds the double value  **x**  to an integer in floating-point format. 

**Parameters:**

<a name="table177884779084824"></a>
<table><thead align="left"><tr id="row1855058804084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p260456786084824"><a name="p260456786084824"></a><a name="p260456786084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p177257222084824"><a name="p177257222084824"></a><a name="p177257222084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row206990860084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1878732297084824"><a name="b1878732297084824"></a><a name="b1878732297084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The rounding mode is specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the rounded value. 



## nearbyintf\(\)<a name="gab3be3fdcb83a6d7cbd10aa5d891f88bf"></a>

```
float nearbyintf (float x)
```

 **Description:**

Rounds the float value  **x**  to an integer in floating-point format. 

**Parameters:**

<a name="table83826007084824"></a>
<table><thead align="left"><tr id="row946228169084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2096329559084824"><a name="p2096329559084824"></a><a name="p2096329559084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1521475131084824"><a name="p1521475131084824"></a><a name="p1521475131084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row643958151084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1537529005084824"><a name="b1537529005084824"></a><a name="b1537529005084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The rounding mode is specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the rounded value. 



## nearbyintl\(\)<a name="ga4b51faf338f7d4f31224d0c096a8859b"></a>

```
long double nearbyintl (long double x)
```

 **Description:**

Rounds the long double value  **x**  to an integer in floating-point format. 

**Parameters:**

<a name="table1181731269084824"></a>
<table><thead align="left"><tr id="row1884296504084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p495585590084824"><a name="p495585590084824"></a><a name="p495585590084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1232971360084824"><a name="p1232971360084824"></a><a name="p1232971360084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1030661047084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Attention:**

The rounding mode is specified by  [fegetround](math.md#gaf43d2de25e6d5e3b65b1d1f32c01b3c8). 

**Returns:**

Returns the rounded value. 



## nextafter\(\)<a name="gabed1b7ee913471448c2dbe58dff28db3"></a>

```
double nextafter (double x, double y )
```

 **Description:**

Obtains the next representable value following the double value  **x**  in the direction of the double value  **y**. 

**Parameters:**

<a name="table1498727111084824"></a>
<table><thead align="left"><tr id="row1363144085084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1681614893084824"><a name="p1681614893084824"></a><a name="p1681614893084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p522257622084824"><a name="p522257622084824"></a><a name="p522257622084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1727232225084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b953345540084824"><a name="b953345540084824"></a><a name="b953345540084824"></a>x</strong>. </td>
</tr>
<tr id="row467479630084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b136361806084824"><a name="b136361806084824"></a><a name="b136361806084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

If  **y**  is less than  **x**, this function returns the maximum representable value less than  **x**. 

**Returns:**

Returns the next representable value after  **x**  in the direction of  **y**  if the operation is successful; returns the passed  **y**  if  **x**  is equal to  **y**; returns a NaN value if  **x**  is a NaN value; returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  and reports an overflow range error if  **x**  is a finite value. 



## nextafterf\(\)<a name="ga57d2446286a54227595950a2118b349b"></a>

```
float nextafterf (float x, float y )
```

 **Description:**

Obtains the next representable value following the float value  **x**  in the direction of the float value  **y**. 

**Parameters:**

<a name="table1605864098084824"></a>
<table><thead align="left"><tr id="row794832760084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1135740416084824"><a name="p1135740416084824"></a><a name="p1135740416084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p975700645084824"><a name="p975700645084824"></a><a name="p975700645084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1754196595084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b128254592084824"><a name="b128254592084824"></a><a name="b128254592084824"></a>x</strong>. </td>
</tr>
<tr id="row1803794048084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1294887058084824"><a name="b1294887058084824"></a><a name="b1294887058084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

If  **y**  is less than  **x**, this function returns the maximum representable value less than  **x**. 

**Returns:**

Returns the next representable value following  **x**  in the direction of  **y**  if the operation is successful; returns the passed  **y**  if  **x**  is equal to  **y**; returns a NaN value if  **x**  is a NaN value; returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  and reports an overflow range error if  **x**  is a finite value. 



## nextafterl\(\)<a name="ga38691f2f734e77206e4336cdcddd0e5b"></a>

```
long double nextafterl (long double x, long double y )
```

 **Description:**

Obtains the next representable value following the long double value  **x**  in the direction of the long double value  **y**. 

**Parameters:**

<a name="table11667185084824"></a>
<table><thead align="left"><tr id="row1121326666084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1578132049084824"><a name="p1578132049084824"></a><a name="p1578132049084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p199232192084824"><a name="p199232192084824"></a><a name="p199232192084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row362859073084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1471821846084824"><a name="b1471821846084824"></a><a name="b1471821846084824"></a>x</strong>. </td>
</tr>
<tr id="row1721081177084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b5167787084824"><a name="b5167787084824"></a><a name="b5167787084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

If  **y**  is less than  **x**, this function returns the maximum representable value less than  **x**. 

**Returns:**

Returns the next representable value after  **x**  in the direction of  **y**  if the operation is successful; returns the passed  **y**  if  **x**  is equal to  **y**; returns a NaN value if  **x**  is a NaN value; returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  and reports an overflow range error if  **x**  is a finite value. 



## nexttoward\(\)<a name="gaeb7afe6d08d8daec35aa282c63d7647e"></a>

```
double nexttoward (double x, long double y )
```

 **Description:**

Obtains the next representable value following the double value  **x**  in the direction of the long double value  **y**. 

**Parameters:**

<a name="table1857197627084824"></a>
<table><thead align="left"><tr id="row1291399961084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p497830763084824"><a name="p497830763084824"></a><a name="p497830763084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p803257618084824"><a name="p803257618084824"></a><a name="p803257618084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1897869828084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b944313052084824"><a name="b944313052084824"></a><a name="b944313052084824"></a>x</strong>. </td>
</tr>
<tr id="row1584409987084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b855131914084824"><a name="b855131914084824"></a><a name="b855131914084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

If  **y**  is less than  **x**, this function returns the maximum representable value less than  **x**. 

**Returns:**

Returns the next representable value following  **x**  in the direction of  **y**  if the operation is successful; returns the passed  **y**  if  **x**  is equal to  **y**; returns a NaN value if  **x**  is a NaN value; returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  and reports an overflow range error if  **x**  is a finite value. 



## nexttowardf\(\)<a name="ga634a1dabb08aa5a4fa6897920eff3c1d"></a>

```
float nexttowardf (float x, long double y )
```

 **Description:**

Obtains the next representable value following the float value  **x**  in the direction of the long double value  **y**. 

**Parameters:**

<a name="table1343600344084824"></a>
<table><thead align="left"><tr id="row591652182084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p349467536084824"><a name="p349467536084824"></a><a name="p349467536084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p526786840084824"><a name="p526786840084824"></a><a name="p526786840084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1036145101084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1775403701084824"><a name="b1775403701084824"></a><a name="b1775403701084824"></a>x</strong>. </td>
</tr>
<tr id="row935985660084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b2146961965084824"><a name="b2146961965084824"></a><a name="b2146961965084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

If  **y**  is less than  **x**, this function returns the maximum representable value less than  **x**. 

**Returns:**

Returns the next representable value after  **x**  in the direction of  **y**  if the operation is successful; returns the passed  **y**  if  **x**  is equal to  **y**; returns a NaN value if  **x**  is a NaN value; returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  and reports an overflow range error if  **x**  is a finite value. 



## nexttowardl\(\)<a name="ga3930cfe4df009d7221db329b910d6e30"></a>

```
long double nexttowardl (long double x, long double y )
```

 **Description:**

Obtains the next representable value following the long double value  **x**  in the direction of the long double value  **y**. 

**Parameters:**

<a name="table1801800262084824"></a>
<table><thead align="left"><tr id="row147303855084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p848632439084824"><a name="p848632439084824"></a><a name="p848632439084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1225896293084824"><a name="p1225896293084824"></a><a name="p1225896293084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row497609819084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1083082122084824"><a name="b1083082122084824"></a><a name="b1083082122084824"></a>x</strong>. </td>
</tr>
<tr id="row1306598782084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b486969673084824"><a name="b486969673084824"></a><a name="b486969673084824"></a>y</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

If  **y**  is less than  **x**, this function returns the maximum representable value less than  **x**. 

**Returns:**

Returns the next representable value following  **x**  in the direction of  **y**  if the operation is successful; returns the passed  **y**  if  **x**  is equal to  **y**; returns a NaN value if  **x**  is a NaN value; returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  and reports an overflow range error if  **x**  is a finite value. 



## pow\(\)<a name="gaa56c9494c95edf68386375e97d64159b"></a>

```
double pow (double x, double y )
```

 **Description:**

Obtains the double value  **x**  raised to the power of the double value  **y**. 

**Parameters:**

<a name="table116703153084824"></a>
<table><thead align="left"><tr id="row769150633084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p914093926084824"><a name="p914093926084824"></a><a name="p914093926084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1806805804084824"><a name="p1806805804084824"></a><a name="p1806805804084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2023954182084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1168459993084824"><a name="b1168459993084824"></a><a name="b1168459993084824"></a>x</strong>, which is used as the base. </td>
</tr>
<tr id="row1261138390084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1313854784084824"><a name="b1313854784084824"></a><a name="b1313854784084824"></a>y</strong>, which is used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **y**  is a NaN value, this returns a NaN value, except as specified below. If  **x**  is  **+1**  \(even if  **y**  is a NaN value\), this function returns  **1.0**. If  **y**  is  **0**  \(even if  **x**  is a NaN value\), this function returns  **1.0**. If  **x**  is  **+0**  or  **-0**, and  **y**  is an odd integer greater than  **0**, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **y**  is greater than  **0**  and not an odd integer, this function returns  **+0**. If  **x**  is  **-1**  and  **y**  is a positive or negative infinity, this function returns  **1.0**. If the absolute value of  **x**  is less than  **1**  and  **y**  is a negative infinity, this function returns a positive infinity. If the absolute value of  **x**  is greater than  **1**  and  **y**  is a negative infinity, this function returns  **+0**. If the absolute value of  **x**  is less than  **1**  and  **y**  is a positive infinity, this function returns  **+0**. If the absolute value of  **x**  is greater than  **1**  and  **y**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity and  **y**  is an odd integer less than  **0**, this function returns  **-0**. If  **x**  is a negative infinity and  **y**  is less than  **0**  and not an odd integer, this function returns  **+0**. If  **x**  is a negative infinity and  **y**  is an odd integer greater than  **0**, this function returns a negative infinity. If  **x**  is a negative infinity and  **y**  is greater than  **0**  and not an odd integer, this function returns a positive infinity. If  **x**  is a positive infinity and  **y**  is less than  **0**, this function returns  **+0**. If  **x**  is a positive infinity and  **y**  is greater than  **0**, this function returns a positive infinity. If  **x**  is a negative value and  **y**  is a finite non-integer, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **+0**  or  **-0**  and  **y**  is a negative odd integer, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is  **+0**  or  **-0**  and  **y**  is a negative non-odd integer, this function returns  **+[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If an overflow range error occurs, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971), sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0.0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## pow10\(\)<a name="gafbbc60a3627a8de4845c7e99e6134ec8"></a>

```
double pow10 (double x)
```

 **Description:**

Calculates the value of 10 raised to the power  **x**, which is a double value. 

**Parameters:**

<a name="table1762278960084824"></a>
<table><thead align="left"><tr id="row91733237084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2036289298084824"><a name="p2036289298084824"></a><a name="p2036289298084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p348133128084824"><a name="p348133128084824"></a><a name="p348133128084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1810813996084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b124232683084824"><a name="b124232683084824"></a><a name="b124232683084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the value of 10 raised to the power  **x**  if the operation is successful. 



## pow10f\(\)<a name="ga2cb598503b85d66abf59e9da06478f1a"></a>

```
float pow10f (float x)
```

 **Description:**

Calculates the value of 10 raised to the power  **x**, which is a float value. 

**Parameters:**

<a name="table1704262413084824"></a>
<table><thead align="left"><tr id="row1786148619084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1766807977084824"><a name="p1766807977084824"></a><a name="p1766807977084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p9054717084824"><a name="p9054717084824"></a><a name="p9054717084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1975507140084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1054775878084824"><a name="b1054775878084824"></a><a name="b1054775878084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the value of 10 raised to the power  **x**  if the operation is successful. 



## pow10l\(\)<a name="ga9baf71e9033dd73a9c225a2fc9cca61d"></a>

```
long double pow10l (long double x)
```

 **Description:**

Calculates the value of 10 raised to the power  **x**, which is a long double value. 

**Parameters:**

<a name="table991645316084824"></a>
<table><thead align="left"><tr id="row1378198800084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2038039618084824"><a name="p2038039618084824"></a><a name="p2038039618084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1185848165084824"><a name="p1185848165084824"></a><a name="p1185848165084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row17034101084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b890350403084824"><a name="b890350403084824"></a><a name="b890350403084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the value of 10 raised to the power  **x**  if the operation is successful. 



## powf\(\)<a name="gac6b287549be087f6f0bf03b6fe30499e"></a>

```
float powf (float x, float y )
```

 **Description:**

Obtains the float value  **x**  raised to the power of the float value  **y**. 

**Parameters:**

<a name="table1585327621084824"></a>
<table><thead align="left"><tr id="row1339673891084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p594638074084824"><a name="p594638074084824"></a><a name="p594638074084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1820886777084824"><a name="p1820886777084824"></a><a name="p1820886777084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1314405873084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b165676624084824"><a name="b165676624084824"></a><a name="b165676624084824"></a>x</strong>, which is used as the base. </td>
</tr>
<tr id="row1257062334084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b2108911871084824"><a name="b2108911871084824"></a><a name="b2108911871084824"></a>y</strong>, which is used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **y**  is a NaN value, this returns a NaN value, except as specified below. If  **x**  is  **+1**  \(even if  **y**  is a NaN value\), this function returns  **1.0**. If  **y**  is  **0**  \(even if  **x**  is a NaN value\), this function returns  **1.0**. If  **x**  is  **+0**  or  **-0**, and  **y**  is an odd integer greater than  **0**, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **y**  is greater than  **0**  and not an odd integer, this function returns  **+0**. If  **x**  is  **-1**  and  **y**  is a positive or negative infinity, this function returns  **1.0**. If the absolute value of  **x**  is less than  **1**  and  **y**  is a negative infinity, this function returns a positive infinity. If the absolute value of  **x**  is greater than  **1**  and  **y**  is a negative infinity, this function returns  **+0**. If the absolute value of  **x**  is less than  **1**  and  **y**  is a positive infinity, this function returns  **+0**. If the absolute value of  **x**  is greater than  **1**  and  **y**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity and  **y**  is an odd integer less than  **0**, this function returns  **-0**. If  **x**  is a negative infinity and  **y**  is less than  **0**  and not an odd integer, this function returns  **+0**. If  **x**  is a negative infinity and  **y**  is an odd integer greater than  **0**, this function returns a negative infinity. If  **x**  is a negative infinity and  **y**  is greater than  **0**  and not an odd integer, this function returns a positive infinity. If  **x**  is a positive infinity and  **y**  is less than  **0**, this function returns  **+0**. If  **x**  is a positive infinity and  **y**  is greater than  **0**, this function returns a positive infinity. If  **x**  is a negative value and  **y**  is a finite non-integer, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **+0**  or  **-0**  and  **y**  is a negative odd integer, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359), reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is  **+0**  or  **-0**  and  **y**  is a negative non-odd integer, this function returns  **+[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359), sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0.0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## powf10\(\)<a name="gab6a77d7e1f713b898ceb3b945a2420b5"></a>

```
float powf10 (float x)
```

 **Description:**

Calculates the xth power of 10. 

**Parameters:**

<a name="table1437309195084824"></a>
<table><thead align="left"><tr id="row1669625679084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p749506293084824"><a name="p749506293084824"></a><a name="p749506293084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2007454638084824"><a name="p2007454638084824"></a><a name="p2007454638084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row237487580084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value x, which is used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If y is 0 \(even if x is a NaN value\), this function returns 1.0. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359), sets errno to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns 0.0, sets errno to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## powl\(\)<a name="ga2f4830e468138e1513b55ca6a92a0f9a"></a>

```
long double powl (long double x, long double y )
```

 **Description:**

Obtains the long double value  **x**  raised to the power of the long double value  **y**. 

 

**Parameters:**

<a name="table1102491543084824"></a>
<table><thead align="left"><tr id="row2104686065084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p914259155084824"><a name="p914259155084824"></a><a name="p914259155084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1570850168084824"><a name="p1570850168084824"></a><a name="p1570850168084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1336093214084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b553936197084824"><a name="b553936197084824"></a><a name="b553936197084824"></a>x</strong>, which is used as the base. </td>
</tr>
<tr id="row1511432525084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1468224034084824"><a name="b1468224034084824"></a><a name="b1468224034084824"></a>y</strong>, which is used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **y**  is a NaN value, this returns a NaN value, except as specified below. If  **x**  is  **+1**  \(even if  **y**  is a NaN value\), this function returns  **1.0**. If  **y**  is  **0**  \(even if  **x**  is a NaN value\), this function returns  **1.0**. If  **x**  is  **+0**  or  **-0**, and  **y**  is an odd integer greater than  **0**, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **y**  is greater than  **0**  and not an odd integer, this function returns  **+0**. If  **x**  is  **-1**  and  **y**  is a positive or negative infinity, this function returns  **1.0**. If the absolute value of  **x**  is less than  **1**  and  **y**  is a negative infinity, this function returns a positive infinity. If the absolute value of  **x**  is greater than  **1**  and  **y**  is a negative infinity, this function returns  **+0**. If the absolute value of  **x**  is less than  **1**  and  **y**  is a positive infinity, this function returns  **+0**. If the absolute value of  **x**  is greater than  **1**  and  **y**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative infinity and  **y**  is an odd integer less than  **0**, this function returns  **-0**. If  **x**  is a negative infinity and  **y**  is less than  **0**  and not an odd integer, this function returns  **+0**. If  **x**  is a negative infinity and  **y**  is an odd integer greater than  **0**, this function returns a negative infinity. If  **x**  is a negative infinity and  **y**  is greater than  **0**  and not an odd integer, this function returns a positive infinity. If  **x**  is a positive infinity and  **y**  is less than  **0**, this function returns  **+0**. If  **x**  is a positive infinity and  **y**  is greater than  **0**, this function returns a positive infinity. If  **x**  is a negative value and  **y**  is a finite non-integer, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is  **+0**  or  **-0**  and  **y**  is a negative odd integer, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182), reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If  **x**  is  **+0**  or  **-0**  and  **y**  is a negative non-odd integer, this function returns  **+[HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)**, reports a pole error, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_DIVBYZERO](math.md#gab1317930189d1a14841893fb4bd9b5a0)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182), sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0.0**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## powl10\(\)<a name="ga532525cfd5b2a8ce221f1b13a7009376"></a>

```
long double powl10 (long double x)
```

 **Description:**

Calculates the xth power of 10. 

**Parameters:**

<a name="table1929130494084824"></a>
<table><thead align="left"><tr id="row1678129651084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p388005367084824"><a name="p388005367084824"></a><a name="p388005367084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p324545843084824"><a name="p324545843084824"></a><a name="p324545843084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row833161082084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value x, which is used as the exponent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful. If x is 0, this function returns 1.0. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182), sets errno to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns 0.0, sets errno to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## remainder\(\)<a name="gaf7df01c4a9038dbf3562b41bc8c3be03"></a>

```
double remainder (double x, double y )
```

 **Description:**

Calculates the remainder of the double value  **x**  divided by the double value  **y**. 

**Parameters:**

<a name="table877449230084824"></a>
<table><thead align="left"><tr id="row1224698052084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1312766435084824"><a name="p1312766435084824"></a><a name="p1312766435084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1327459004084824"><a name="p1327459004084824"></a><a name="p1327459004084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row482544821084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b543124408084824"><a name="b543124408084824"></a><a name="b543124408084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row1195572666084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b495958045084824"><a name="b495958045084824"></a><a name="b495958045084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
</tbody>
</table>

**Attention:**

The return value is  **x-n\*y**, where  **n**  is the value of  **x**/**y**, rounded toward the nearest integer \(with halfway values rounded toward the even number\). For example, if the decimal part of  **x**/**y**  is  **0.5**, the value is rounded to an even number and  **0**  is returned. 

**Returns:**

Returns the remainder if the operation is successful. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **x**  is an infinity and  **y**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. If  **y**  is  **0**  and  **x**  is not a NaN value, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  **FE\_INVAID**  exception. 



## remainderf\(\)<a name="ga370ff5cfa842822bfd8ea0a93d441a33"></a>

```
float remainderf (float x, float y )
```

 **Description:**

Calculates the remainder of the float value  **x**  divided by the float value  **y**. 

**Parameters:**

<a name="table2078105012084824"></a>
<table><thead align="left"><tr id="row1322071852084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p364433136084824"><a name="p364433136084824"></a><a name="p364433136084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2034937794084824"><a name="p2034937794084824"></a><a name="p2034937794084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row340487372084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b367042055084824"><a name="b367042055084824"></a><a name="b367042055084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row1225136093084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1151234859084824"><a name="b1151234859084824"></a><a name="b1151234859084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
</tbody>
</table>

**Attention:**

The return value is  **x-n\*y**, where  **n**  is the value of  **x**/**y**, rounded toward the nearest integer \(with halfway values rounded toward the even number\). For example, if the decimal part of  **x**/**y**  is  **0.5**, the value is rounded to an even number and  **0**  is returned. 

**Returns:**

Returns the remainder if the operation is successful. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **x**  is an infinity and  **y**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. If  **y**  is  **0**  and  **x**  is not a NaN value, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  **FE\_INVAID**  exception. 



## remainderl\(\)<a name="gabadbe61e166bbf3031b979661f0e8336"></a>

```
long double remainderl (long double x, long double y )
```

 **Description:**

Calculates the remainder of the long double value  **x**  divided by the long double value  **y**. 

**Parameters:**

<a name="table1526590917084824"></a>
<table><thead align="left"><tr id="row338371779084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2010259701084824"><a name="p2010259701084824"></a><a name="p2010259701084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2026790936084824"><a name="p2026790936084824"></a><a name="p2026790936084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1378946750084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1425467420084824"><a name="b1425467420084824"></a><a name="b1425467420084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row1067846228084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b726108647084824"><a name="b726108647084824"></a><a name="b726108647084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
</tbody>
</table>

**Attention:**

The return value is  **x-n\*y**, where  **n**  is the value of  **x**/**y**, rounded toward the nearest integer \(with halfway values rounded toward the even number\). For example, if the decimal part of  **x**/**y**  is  **0.5**, the value is rounded to an even number and  **0**  is returned. 

**Returns:**

Returns the remainder if the operation is successful. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **x**  is an infinity and  **y**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. If  **y**  is  **0**  and  **x**  is not a NaN value, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  **FE\_INVAID**  exception. 



## remquo\(\)<a name="gac836dc6a979229173eb3d6e2744d82de"></a>

```
double remquo (double x, double y, int * quo )
```

 **Description:**

Calculates the quotient and remainder of the double value  **x**  divided by the double value  **y**. 

The return value is  **x-n\*y**, where  **n**  is the value of  **x**/**y**, rounded toward the nearest integer \(with halfway values rounded toward the even number\). For example, if the decimal part of  **x**/**y**  is  **0.5**, the value is rounded to an even number and  **0**  is returned.  **n**  is converted into a signed binary number, and the sign and the least significant three bits of the binary number are combined and stored to the pointer specified by  **quo**. For example, if  **x**  is  **29.0**  and  **y**  is  **3.0**, the return value is  **-1.0**  and  **n**  is  **10**.  **n**  is converted into a signed binary number  **00001010**. Therefore,  **2**  is stored to the pointer specified by  **quo**. 

**Parameters:**

<a name="table661312858084824"></a>
<table><thead align="left"><tr id="row2021537505084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2007635636084824"><a name="p2007635636084824"></a><a name="p2007635636084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1008134676084824"><a name="p1008134676084824"></a><a name="p1008134676084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row358641430084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b17431037084824"><a name="b17431037084824"></a><a name="b17431037084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row1645530320084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b319962776084824"><a name="b319962776084824"></a><a name="b319962776084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
<tr id="row1872403607084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">quo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer that stores the quotient. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the remainder if the operation is successful. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **x**  is an infinity and  **y**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. If  **y**  is  **0**  and  **x**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. 



## remquof\(\)<a name="ga15ec704e1894cfa573ac37a65afe009a"></a>

```
float remquof (float x, float y, int * quo )
```

 **Description:**

Calculates the quotient and remainder of the float value  **x**  divided by the float value  **y**. 

The return value is  **x-n\*y**, where  **n**  is the value of  **x**/**y**, rounded toward the nearest integer \(with halfway values rounded toward the even number\). For example, if the decimal part of  **x**/**y**  is  **0.5**, the value is rounded to an even number and  **0**  is returned.  **n**  is converted into a signed binary number, and the sign and the least significant three bits of the binary number are combined and stored to the pointer specified by  **quo**. For example, if  **x**  is  **29.0**  and  **y**  is  **3.0**, the return value is  **-1.0**  and  **n**  is  **10**.  **n**  is converted into a signed binary number  **00001010**. Therefore,  **2**  is stored to the pointer specified by  **quo**. 

**Parameters:**

<a name="table1283215406084824"></a>
<table><thead align="left"><tr id="row92224747084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1747370117084824"><a name="p1747370117084824"></a><a name="p1747370117084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1803218934084824"><a name="p1803218934084824"></a><a name="p1803218934084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1848286885084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1633050356084824"><a name="b1633050356084824"></a><a name="b1633050356084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row370809015084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b693514943084824"><a name="b693514943084824"></a><a name="b693514943084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
<tr id="row54761921084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">quo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer that stores the quotient. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the remainder if the operation is successful. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **x**  is an infinity and  **y**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. If  **y**  is  **0**  and  **x**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. 



## remquol\(\)<a name="gaacadcc57a95279058f29e657dce4d285"></a>

```
long double remquol (long double x, long double y, int * quo )
```

 **Description:**

Calculates the quotient and remainder of the long double value  **x**  divided by the long double value  **y**. 

The return value is  **x-n\*y**, where  **n**  is the value of  **x**/**y**, rounded toward the nearest integer \(with halfway values rounded toward the even number\). For example, if the decimal part of  **x**/**y**  is  **0.5**, the value is rounded to an even number and  **0**  is returned.  **n**  is converted into a signed binary number, and the sign and the least significant three bits of the binary number are combined and stored to the pointer specified by  **quo**. For example, if  **x**  is  **29.0**  and  **y**  is  **3.0**, the return value is  **-1.0**  and  **n**  is  **10**.  **n**  is converted into a signed binary number  **00001010**. Therefore,  **2**  is stored to the pointer specified by  **quo**. 

**Parameters:**

<a name="table837121724084824"></a>
<table><thead align="left"><tr id="row1020217458084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1483857812084824"><a name="p1483857812084824"></a><a name="p1483857812084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p657683512084824"><a name="p657683512084824"></a><a name="p657683512084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1705384291084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b596369980084824"><a name="b596369980084824"></a><a name="b596369980084824"></a>x</strong>, which is used as the numerator. </td>
</tr>
<tr id="row2054738601084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b2023029951084824"><a name="b2023029951084824"></a><a name="b2023029951084824"></a>y</strong>, which is used as the denominator. </td>
</tr>
<tr id="row1705678304084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">quo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer that stores the quotient. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the remainder if the operation is successful. If  **x**  or  **y**  is a NaN value, this function returns a NaN value. If  **x**  is an infinity and  **y**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. If  **y**  is  **0**  and  **x**  is not a NaN value, this function returns a NaN value, reports a domain error, and throws the  **FE\_INVAID**  exception. 



## rint\(\)<a name="gae1f9edd5049d3ff63b0373a3c15c38c1"></a>

```
double rint (double x)
```

 **Description:**

Rounds the double value  **x**  to the nearest integer. 

**Parameters:**

<a name="table445806089084824"></a>
<table><thead align="left"><tr id="row1263338759084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2103760739084824"><a name="p2103760739084824"></a><a name="p2103760739084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1896213087084824"><a name="p1896213087084824"></a><a name="p1896213087084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1004508648084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Attention:**

POSIX.1-2001 records overflow range errors. If there are two nearest integers, the even integer is returned. For example, if  **x**  is  **0.5**,  **0**  is returned. 

**Returns:**

Returns the nearest integer if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## rintf\(\)<a name="ga48f9341b9310fefa5dd1b0c8c84c99df"></a>

```
float rintf (float x)
```

 **Description:**

Rounds the float value  **x**  to the nearest integer. 

**Parameters:**

<a name="table1683095179084824"></a>
<table><thead align="left"><tr id="row2131401929084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1303192777084824"><a name="p1303192777084824"></a><a name="p1303192777084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p589307182084824"><a name="p589307182084824"></a><a name="p589307182084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row363700150084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Attention:**

POSIX.1-2001 records overflow range errors. If there are two nearest integers, the even integer is returned. For example, if  **x**  is  **0.5**,  **0**  is returned. 

**Returns:**

Returns the nearest integer if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## rintl\(\)<a name="gaedc37bf10d69d2efa2a478f5f5d4b26b"></a>

```
long double rintl (long double x)
```

 **Description:**

Rounds the long double value  **x**  to the nearest integer. 

**Parameters:**

<a name="table1656302712084824"></a>
<table><thead align="left"><tr id="row1838141456084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1377803836084824"><a name="p1377803836084824"></a><a name="p1377803836084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p464098601084824"><a name="p464098601084824"></a><a name="p464098601084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1155046853084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Attention:**

POSIX.1-2001 records overflow range errors. If there are two nearest integers, the even integer is returned. For example, if  **x**  is  **0.5**,  **0**  is returned. 

**Returns:**

Returns the nearest integer if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## round\(\)<a name="ga7df19cf730447c00150569250a4b5e1d"></a>

```
double round (double x)
```

 **Description:**

Rounds the double value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table467776402084824"></a>
<table><thead align="left"><tr id="row1153174700084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1915187370084824"><a name="p1915187370084824"></a><a name="p1915187370084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p607820665084824"><a name="p607820665084824"></a><a name="p607820665084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row612202823084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b409051047084824"><a name="b409051047084824"></a><a name="b409051047084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. For example, if  **x**  is  **0.5**, the rounded value is  **1**; if  **x**  is  **-0.5**, the rounded value is  **-1**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## roundf\(\)<a name="gade09185c0cf8101fa9e2f25c15041b81"></a>

```
float roundf (float x)
```

 **Description:**

Rounds the float value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table328660099084824"></a>
<table><thead align="left"><tr id="row1040681761084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1337130163084824"><a name="p1337130163084824"></a><a name="p1337130163084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p894404517084824"><a name="p894404517084824"></a><a name="p894404517084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row166199045084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1573464735084824"><a name="b1573464735084824"></a><a name="b1573464735084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. For example, if  **x**  is  **0.5**, the rounded value is  **1**; if  **x**  is  **-0.5**, the rounded value is  **-1**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## roundl\(\)<a name="ga6565127c023ae8f392ce69e3b3f30aa1"></a>

```
long double roundl (long double x)
```

 **Description:**

Rounds the long double value  **x**  to the nearest integer, rounding away from  **0**. 

**Parameters:**

<a name="table1514308900084824"></a>
<table><thead align="left"><tr id="row745291873084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p396774137084824"><a name="p396774137084824"></a><a name="p396774137084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2003621183084824"><a name="p2003621183084824"></a><a name="p2003621183084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row356470892084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1604201484084824"><a name="b1604201484084824"></a><a name="b1604201484084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

Halfway values are rounded away from  **0**. For example, if  **x**  is  **0.5**, the rounded value is  **1**; if  **x**  is  **-0.5**, the rounded value is  **-1**. 

**Returns:**

Returns the nearest integer if the operation is successful; returns the passed  **x**  if  **x**  is an integer,  **+0**,  **-0**, a NaN value, or an infinity. 



## scalb\(\)<a name="ga14db57dcd8982430d12219bbecd08a05"></a>

```
double scalb (double x, double exp )
```

 **Description:**

Multiplies the double value  **x**  by  **FLT\_RADIX**  raised to the power of the double value  **exp**, that is, x\***FLT\_RADIX**^exp. 

**Parameters:**

<a name="table1271374359084824"></a>
<table><thead align="left"><tr id="row434443468084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p334466350084824"><a name="p334466350084824"></a><a name="p334466350084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1238765689084824"><a name="p1238765689084824"></a><a name="p1238765689084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row115086962084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1560646164084824"><a name="b1560646164084824"></a><a name="b1560646164084824"></a>x</strong>. </td>
</tr>
<tr id="row1624512163084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## scalbf\(\)<a name="ga9c9db25d2ff9973e0d8638cf42df3999"></a>

```
float scalbf (float x, float exp )
```

 **Description:**

Multiplies the float value  **x**  by  **FLT\_RADIX**  raised to the power of the float value  **exp**, that is, x\***FLT\_RADIX**^exp. 

**Parameters:**

<a name="table1294116641084824"></a>
<table><thead align="left"><tr id="row1040654584084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2143858373084824"><a name="p2143858373084824"></a><a name="p2143858373084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1885929488084824"><a name="p1885929488084824"></a><a name="p1885929488084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1915106809084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b2127306957084824"><a name="b2127306957084824"></a><a name="b2127306957084824"></a>x</strong>. </td>
</tr>
<tr id="row1565547169084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## scalbln\(\)<a name="ga947d3d0739c0dc7c46d1eec778d4b6af"></a>

```
double scalbln (double x, long int exp )
```

 **Description:**

Multiplies the double value  **x**  by  **FLT\_RADIX**  raised to the power of the long int value  **exp**, that is,  **x\*\(**FLT\_RADIX**\)^exp**. 

**Parameters:**

<a name="table1466685107084824"></a>
<table><thead align="left"><tr id="row1672595607084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1760971444084824"><a name="p1760971444084824"></a><a name="p1760971444084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p945421016084824"><a name="p945421016084824"></a><a name="p945421016084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1259352571084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1936171219084824"><a name="b1936171219084824"></a><a name="b1936171219084824"></a>x</strong>. </td>
</tr>
<tr id="row389663054084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## scalblnf\(\)<a name="ga1aa3cc34e8f84a2a09400c25c578100d"></a>

```
float scalblnf (float x, long int exp )
```

 **Description:**

Multiplies the float value  **x**  by  **FLT\_RADIX**  raised to the power of the long int value  **exp**, that is,  **x\*\(**FLT\_RADIX**\)^exp**. 

**Parameters:**

<a name="table1407208936084824"></a>
<table><thead align="left"><tr id="row1410365914084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1774651414084824"><a name="p1774651414084824"></a><a name="p1774651414084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1309508798084824"><a name="p1309508798084824"></a><a name="p1309508798084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row59584794084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b229941396084824"><a name="b229941396084824"></a><a name="b229941396084824"></a>x</strong>. </td>
</tr>
<tr id="row1003273908084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## scalblnl\(\)<a name="gaeb098df94536b520ced9df59fd353848"></a>

```
long double scalblnl (long double x, long int exp )
```

 **Description:**

Multiplies the long double value  **x**  by  **FLT\_RADIX**  raised to the power of the long int value  **exp**, that is,  **x\*\(**FLT\_RADIX**\)^exp**. 

**Parameters:**

<a name="table1632148395084824"></a>
<table><thead align="left"><tr id="row2055388091084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2095369267084824"><a name="p2095369267084824"></a><a name="p2095369267084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p314049410084824"><a name="p314049410084824"></a><a name="p314049410084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row637550981084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1808521115084824"><a name="b1808521115084824"></a><a name="b1808521115084824"></a>x</strong>. </td>
</tr>
<tr id="row471862761084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## scalbn\(\)<a name="gaa2fbea1fca1faaebedf2deec71c47189"></a>

```
double scalbn (double x, int exp )
```

 **Description:**

Multiplies the double value  **x**  by  **FLT\_RADIX**  raised to the power of the int value  **exp**, that is,  **x\*\(**FLT\_RADIX**\)^exp**. 

**Parameters:**

<a name="table1383018961084824"></a>
<table><thead align="left"><tr id="row1628758886084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1662387271084824"><a name="p1662387271084824"></a><a name="p1662387271084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1086063707084824"><a name="p1086063707084824"></a><a name="p1086063707084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row456108499084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1804408198084824"><a name="b1804408198084824"></a><a name="b1804408198084824"></a>x</strong>. </td>
</tr>
<tr id="row1123258475084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## scalbnf\(\)<a name="ga3849b86bb2f39ebccb79b91745f7883f"></a>

```
float scalbnf (float x, int exp )
```

 **Description:**

Multiplies the float value  **x**  by  **FLT\_RADIX**  raised to the power of the int value  **exp**, that is,  **x\*\(**FLT\_RADIX**\)^exp**. 

**Parameters:**

<a name="table621572316084824"></a>
<table><thead align="left"><tr id="row1743663976084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p603899435084824"><a name="p603899435084824"></a><a name="p603899435084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p368757264084824"><a name="p368757264084824"></a><a name="p368757264084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1325146339084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b1991270080084824"><a name="b1991270080084824"></a><a name="b1991270080084824"></a>x</strong>. </td>
</tr>
<tr id="row2134695550084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. If an underflow range error occurs, this function returns  **0**  and throws the  [FE\_UNDERFLOW](math.md#ga57b80dfe7d5ce60c3c76e517fce89ffe)  exception. 



## scalbnl\(\)<a name="ga284717e9eceed5bc33389ce33170f907"></a>

```
long double scalbnl (long double x, int exp )
```

 **Description:**

Multiplies the long double value  **x**  by  **FLT\_RADIX**  raised to the power of the int value  **exp**, that is,  **x\*\(**FLT\_RADIX**\)^exp**. 

**Parameters:**

<a name="table2115773662084824"></a>
<table><thead align="left"><tr id="row258747553084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1600810034084824"><a name="p1600810034084824"></a><a name="p1600810034084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1309836018084824"><a name="p1309836018084824"></a><a name="p1309836018084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row360929353084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b665264309084824"><a name="b665264309084824"></a><a name="b665264309084824"></a>x</strong>. </td>
</tr>
<tr id="row1167566090084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">exp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value used as the exponent. </td>
</tr>
</tbody>
</table>

**Attention:**

**FLT\_RADIX**  is defined in  **float.h**  and is generally  **2**. 

**Returns:**

Returns the calculation result if the operation is successful. If  **x**  or  **exp**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, and  **exp**  is not a negative infinity, this function returns a positive or negative infinity. If  **x**  is  **+0**  or  **-0**, and  **exp**  is not a positive infinity, this function returns  **+0**  or  **-0**. If  **x**  is  **0**  and  **exp**  is a positive infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If  **x**  is an infinity and  **exp**  is a negative infinity, this function returns a NaN value, reports a domain error, and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  with the sign of  **x**  and throws the  [FE\_OVERFLOW](math.md#gad373306add36e7227d9c9620b6962323)  exception. 



## significand\(\)<a name="gafad3bf1f77c516fb8891c72beb51640f"></a>

```
double significand (double x)
```

 **Description:**

Obtains the significand of the double value  **x**  scaled to the range \[1,2\). 

The calculation formula is x\*2^-[ilogb](math.md#ga600dd249210d15af31b9a29c2d09d255)\(x\). This function is mainly used in certain standardized tests for IEEE 754 conformance. 

**Parameters:**

<a name="table1984298229084824"></a>
<table><thead align="left"><tr id="row1459303874084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1514329108084824"><a name="p1514329108084824"></a><a name="p1514329108084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1671536766084824"><a name="p1671536766084824"></a><a name="p1671536766084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1938108480084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b97096125084824"><a name="b97096125084824"></a><a name="b97096125084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the significand of  **x**  if the operation is successful. 



## significandf\(\)<a name="gac57d7d88e1a9b57c9a129ee4d4a68c42"></a>

```
float significandf (float x)
```

 **Description:**

Obtains the significand of the float value  **x**  scaled to the range \[1,2\). 

The calculation formula is x\*2^-[ilogb](math.md#ga600dd249210d15af31b9a29c2d09d255)\(x\). This function is mainly used in certain standardized tests for IEEE 754 conformance. 

**Parameters:**

<a name="table331404123084824"></a>
<table><thead align="left"><tr id="row1610603530084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p229259313084824"><a name="p229259313084824"></a><a name="p229259313084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1713189046084824"><a name="p1713189046084824"></a><a name="p1713189046084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1865306255084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b419719062084824"><a name="b419719062084824"></a><a name="b419719062084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the significand of  **x**  if the operation is successful. 



## sin\(\)<a name="gaad4af25633b071b0e2cdb8ebd87eca77"></a>

```
double sin (double x)
```

 **Description:**

Calculates the sine of the double value  **x**. 

**Parameters:**

<a name="table1118462927084824"></a>
<table><thead align="left"><tr id="row1539691264084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p863332431084824"><a name="p863332431084824"></a><a name="p863332431084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1803075557084824"><a name="p1803075557084824"></a><a name="p1803075557084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1111782083084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the sine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sincos\(\)<a name="gaf4509ae544cecab0e9a61efdfccb7530"></a>

```
void sincos (double x, double * sin, double * cos )
```

 **Description:**

Calculates the sine and cosine of the double value  **x**. 

**Parameters:**

<a name="table993266936084824"></a>
<table><thead align="left"><tr id="row1974656299084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1125384525084824"><a name="p1125384525084824"></a><a name="p1125384525084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1376768115084824"><a name="p1376768115084824"></a><a name="p1376768115084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row341914149084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose sine and cosine are to be calculated. </td>
</tr>
<tr id="row2036970764084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sin</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained sine. </td>
</tr>
<tr id="row1848701452084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained cosine. </td>
</tr>
</tbody>
</table>

**Attention:**

A domain error occurs if  **x**  is an infinity. In this case, the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception is thrown, and  **sin**  and  **cos**  are both NaN values. If  **x**  is a NaN value,  **sin**  and  **cos**  are both NaN values. 



## sincosf\(\)<a name="gac59adab35511be68e92ad9013d63e866"></a>

```
void sincosf (float x, float * sin, float * cos )
```

 **Description:**

Calculates the sine and cosine of the float value  **x**. 

**Parameters:**

<a name="table8232960084824"></a>
<table><thead align="left"><tr id="row189287199084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p645525364084824"><a name="p645525364084824"></a><a name="p645525364084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p655752375084824"><a name="p655752375084824"></a><a name="p655752375084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1253296808084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose sine and cosine are to be calculated. </td>
</tr>
<tr id="row928779355084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sin</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained sine. </td>
</tr>
<tr id="row375036841084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained cosine. </td>
</tr>
</tbody>
</table>

**Attention:**

A domain error occurs if  **x**  is an infinity. In this case, the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception is thrown, and  **sin**  and  **cos**  are both NaN values. If  **x**  is a NaN value,  **sin**  and  **cos**  are both NaN values. 



## sincosl\(\)<a name="gaf877b78dbe8e265bdf4b975dbc713482"></a>

```
void sincosl (long double x, long double * sin, long double * cos )
```

 **Description:**

Calculates the sine and cosine of the long double value  **x**. 

**Parameters:**

<a name="table1816109151084824"></a>
<table><thead align="left"><tr id="row1289798055084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1902560624084824"><a name="p1902560624084824"></a><a name="p1902560624084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1890760016084824"><a name="p1890760016084824"></a><a name="p1890760016084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1165574260084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value whose sine and cosine are to be calculated. </td>
</tr>
<tr id="row2029763004084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sin</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained sine. </td>
</tr>
<tr id="row1099920598084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained cosine. </td>
</tr>
</tbody>
</table>

**Attention:**

A domain error occurs if  **x**  is an infinity. In this case, the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception is thrown, and  **sin**  and  **cos**  are both NaN values. If  **x**  is a NaN value,  **sin**  and  **cos**  are both NaN values. 



## sinf\(\)<a name="ga8a7dc2a88e109f4e15b661247665709a"></a>

```
float sinf (float x)
```

 **Description:**

Calculates the sine of the float value  **x**. 

**Parameters:**

<a name="table1234648542084824"></a>
<table><thead align="left"><tr id="row2096933033084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p228886652084824"><a name="p228886652084824"></a><a name="p228886652084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1722296357084824"><a name="p1722296357084824"></a><a name="p1722296357084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1419051847084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the sine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sinh\(\)<a name="ga862012e970c977c482507064e2793b45"></a>

```
double sinh (double x)
```

 **Description:**

Calculates the hyperbolic sine of the double value  **x**. 

**Parameters:**

<a name="table1396557886084824"></a>
<table><thead align="left"><tr id="row1195649083084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1137232325084824"><a name="p1137232325084824"></a><a name="p1137232325084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1893551789084824"><a name="p1893551789084824"></a><a name="p1893551789084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row206706706084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic sine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  with the sign of  **x**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sinhf\(\)<a name="ga1976c7577fb97800f4b926bd042b64ac"></a>

```
float sinhf (float x)
```

 **Description:**

Calculates the hyperbolic sine of the float value  **x**. 

**Parameters:**

<a name="table1034619814084824"></a>
<table><thead align="left"><tr id="row2123502084084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p86899543084824"><a name="p86899543084824"></a><a name="p86899543084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p403770853084824"><a name="p403770853084824"></a><a name="p403770853084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2097910084084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic sine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  with the sign of  **x**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sinhl\(\)<a name="gad160d5d1bb3f113e96135a4bebe76abe"></a>

```
long double sinhl (long double x)
```

 **Description:**

Calculates the hyperbolic sine of the long double value  **x**. 

**Parameters:**

<a name="table1426552052084824"></a>
<table><thead align="left"><tr id="row1491457733084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1630531161084824"><a name="p1630531161084824"></a><a name="p1630531161084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1401601393084824"><a name="p1401601393084824"></a><a name="p1401601393084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row374840463084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic sine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **+0**  or  **-0**, this function returns  **+0**  or  **-0**, respectively. If  **x**  is a positive or negative infinity, this function returns a positive or negative infinity. If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  with the sign of  **x**, sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sinl\(\)<a name="gaeb537bfea71fa91192234a666f3a6a25"></a>

```
long double sinl (long double x)
```

 **Description:**

Calculates the sine of the long double value  **x**. 

**Parameters:**

<a name="table1663613467084824"></a>
<table><thead align="left"><tr id="row763433322084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1972255294084824"><a name="p1972255294084824"></a><a name="p1972255294084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1587089542084824"><a name="p1587089542084824"></a><a name="p1587089542084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row99561258084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the sine of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive or negative infinity, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sqrt\(\)<a name="gab87521a75ef827a85807f89a6c10629a"></a>

```
double sqrt (double x)
```

 **Description:**

Calculates the square root of double value  **x**. 

**Parameters:**

<a name="table1842365816084824"></a>
<table><thead align="left"><tr id="row58383831084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p671645342084824"><a name="p671645342084824"></a><a name="p671645342084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1883834922084824"><a name="p1883834922084824"></a><a name="p1883834922084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1102997947084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the square root of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sqrtf\(\)<a name="ga46c9a8d40cde7c4d5ab40a67e55316bb"></a>

```
float sqrtf (float x)
```

 **Description:**

Calculates the square root of the float value  **x**. 

**Parameters:**

<a name="table1766797044084824"></a>
<table><thead align="left"><tr id="row486753566084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p116948794084824"><a name="p116948794084824"></a><a name="p116948794084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1851210085084824"><a name="p1851210085084824"></a><a name="p1851210085084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1209063682084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the square root of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## sqrtl\(\)<a name="ga9c028a87917b3bb9bba9e75f66cdbd43"></a>

```
long double sqrtl (long double x)
```

 **Description:**

Calculates the square root of the long double value  **x**. 

**Parameters:**

<a name="table1819940816084824"></a>
<table><thead align="left"><tr id="row1374994818084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p189236092084824"><a name="p189236092084824"></a><a name="p189236092084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p572489562084824"><a name="p572489562084824"></a><a name="p572489562084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row464453689084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the square root of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tan\(\)<a name="gaa48fdfd5eea5f4f9c33496402b9e4039"></a>

```
double tan (double x)
```

 **Description:**

Calculates the tangent of the double value  **x**. 

**Parameters:**

<a name="table202039541084824"></a>
<table><thead align="left"><tr id="row1068122394084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p159688255084824"><a name="p159688255084824"></a><a name="p159688255084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p106685189084824"><a name="p106685189084824"></a><a name="p106685189084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1043523122084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value, which represents an angle in radians. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the tangent of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tanf\(\)<a name="ga67d5bfe80effce6adebf5fcbc5a7dae0"></a>

```
float tanf (float x)
```

 **Description:**

Calculates the tangent of the float value  **x**. 

**Parameters:**

<a name="table1315203208084824"></a>
<table><thead align="left"><tr id="row1860041495084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p916627514084824"><a name="p916627514084824"></a><a name="p916627514084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1834481128084824"><a name="p1834481128084824"></a><a name="p1834481128084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1835491210084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value, which represents an angle in radians. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the tangent of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tanh\(\)<a name="gaf85bcf153d7ae805733927f12329dac1"></a>

```
double tanh (double x)
```

 **Description:**

Calculates the hyperbolic tangent of the double value  **x**. 

**Parameters:**

<a name="table1052938335084824"></a>
<table><thead align="left"><tr id="row589071965084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1475947773084824"><a name="p1475947773084824"></a><a name="p1475947773084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1425728682084824"><a name="p1425728682084824"></a><a name="p1425728682084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1204475374084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic tangent of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tanhf\(\)<a name="ga74e8f87bb37a338d2cebbb6b1d696593"></a>

```
float tanhf (float x)
```

 **Description:**

Calculates the hyperbolic tangent of the float value  **x**. 

**Parameters:**

<a name="table1454444187084824"></a>
<table><thead align="left"><tr id="row2050890462084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1938246489084824"><a name="p1938246489084824"></a><a name="p1938246489084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p348122220084824"><a name="p348122220084824"></a><a name="p348122220084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1205256223084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic tangent of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tanhl\(\)<a name="ga94ee8c57b6b2d0bc5466c75bea2bffcf"></a>

```
long double tanhl (long double x)
```

 **Description:**

Calculates the hyperbolic tangent of the long double value  **x**. 

**Parameters:**

<a name="table703472729084824"></a>
<table><thead align="left"><tr id="row2104310191084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1116513540084824"><a name="p1116513540084824"></a><a name="p1116513540084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p742239443084824"><a name="p742239443084824"></a><a name="p742239443084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row944894271084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the hyperbolic tangent of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tanl\(\)<a name="ga2151fba6c1e9b4fa5d2af2dcb5c68b17"></a>

```
long double tanl (long double x)
```

 **Description:**

Calculates the tangent of the long double value  **x**. 

**Parameters:**

<a name="table423349447084824"></a>
<table><thead align="left"><tr id="row108924498084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p325973422084824"><a name="p325973422084824"></a><a name="p325973422084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p559528488084824"><a name="p559528488084824"></a><a name="p559528488084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2134322067084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value, which represents an angle in radians. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the tangent of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0**, this function returns  **0**. If  **x**  is less than  **-0**, this function returns a NaN value, reports a domain error, sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70), and throws the  [FE\_INVALID](math.md#ga638c8489adb1fac7204b07ece42998ae)  exception. 



## tgamma\(\)<a name="ga54afbf509eea5e9d6f9efdebc572339a"></a>

```
double tgamma (double x)
```

 **Description:**

Calculates the gamma function of the double value  **x**. 

**Parameters:**

<a name="table1659338212084824"></a>
<table><thead align="left"><tr id="row140456190084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1076793683084824"><a name="p1076793683084824"></a><a name="p1076793683084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p712187282084824"><a name="p712187282084824"></a><a name="p712187282084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row659102024084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the gamma function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative integer or negative infinity, this function returns a NaN value, reports a domain error, and sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70). If an underflow range error occurs, this function returns  **+0**. If  **x**  is  **+0**  or  **-0**, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  with the sign of  **x**, reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). If an overflow range error occurs, this function returns  [HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## tgammaf\(\)<a name="ga2ab69de9110cc2c62ca78b5d20a3a3ae"></a>

```
float tgammaf (float x)
```

 **Description:**

Calculates the gamma function of the float value  **x**. 

**Parameters:**

<a name="table531866270084824"></a>
<table><thead align="left"><tr id="row1023729715084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p787158544084824"><a name="p787158544084824"></a><a name="p787158544084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1103511168084824"><a name="p1103511168084824"></a><a name="p1103511168084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1451080114084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the gamma function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative integer or negative infinity, this function returns a NaN value, reports a domain error, and sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70). If an underflow range error occurs, this function returns  **+0**. If  **x**  is  **+0**  or  **-0**, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  with the sign of  **x**, reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). If an overflow range error occurs, this function returns  [HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## tgammal\(\)<a name="ga8eff39a57115761c5025e08ff2e08c6a"></a>

```
long double tgammal (long double x)
```

 **Description:**

Calculates the gamma function of the long double value  **x**. 

**Parameters:**

<a name="table286550834084824"></a>
<table><thead align="left"><tr id="row354237666084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p261064957084824"><a name="p261064957084824"></a><a name="p261064957084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1645470097084824"><a name="p1645470097084824"></a><a name="p1645470097084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1534316764084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the gamma function of  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is a positive infinity, this function returns a positive infinity. If  **x**  is a negative integer or negative infinity, this function returns a NaN value, reports a domain error, and sets  **errno**  to  [EDOM](utils.md#ga5fe247e079b591a68e0fdbf7caec5b70). If an underflow range error occurs, this function returns  **+0**. If  **x**  is  **+0**  or  **-0**, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  with the sign of  **x**, reports a pole error, and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). If an overflow range error occurs, this function returns  [HUGE\_VALL](math.md#gab8b359c356d4311bf5d4ae6c03f43182)  and sets  **errno**  to  [ERANGE](utils.md#gaa1591a4f3a86360108de5b9ba34980ca). 



## trunc\(\)<a name="ga82a151adfde56b28fa8a50355c4f2ff6"></a>

```
double trunc (double x)
```

 **Description:**

Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the double value  **x**. 

**Parameters:**

<a name="table1054033447084824"></a>
<table><thead align="left"><tr id="row1389801243084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p253566119084824"><a name="p253566119084824"></a><a name="p253566119084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p640933492084824"><a name="p640933492084824"></a><a name="p640933492084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1751448088084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value <strong id="b1085798407084824"><a name="b1085798407084824"></a><a name="b1085798407084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the nearest integer whose absolute value is less than or equal to the absolute value of  **x**. 



## truncf\(\)<a name="gaa8bb2049c170c9ac5b131fdba029991a"></a>

```
float truncf (float x)
```

 **Description:**

Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the float value  **x**. 

**Parameters:**

<a name="table1534373530084824"></a>
<table><thead align="left"><tr id="row773390549084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1425762188084824"><a name="p1425762188084824"></a><a name="p1425762188084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1726851511084824"><a name="p1726851511084824"></a><a name="p1726851511084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1111136320084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value <strong id="b164998802084824"><a name="b164998802084824"></a><a name="b164998802084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the nearest integer whose absolute value is less than or equal to the absolute value of  **x**. 



## truncl\(\)<a name="ga8f9695496a9bb839eb5f728b6bf0c856"></a>

```
long double truncl (long double x)
```

 **Description:**

Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the long double value  **x**. 

**Parameters:**

<a name="table1614568330084824"></a>
<table><thead align="left"><tr id="row339417746084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1203272781084824"><a name="p1203272781084824"></a><a name="p1203272781084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1132675157084824"><a name="p1132675157084824"></a><a name="p1132675157084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row274066902084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the long double value <strong id="b1792884307084824"><a name="b1792884307084824"></a><a name="b1792884307084824"></a>x</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the nearest integer whose absolute value is less than or equal to the absolute value of  **x**. 



## y0\(\)<a name="gafca57fd80386476e5cd1dd52173103c5"></a>

```
double y0 (double x)
```

 **Description:**

Calculates the Bessel function of the second kind of order  **0**  for the double value  **x**. 

**Parameters:**

<a name="table607153032084824"></a>
<table><thead align="left"><tr id="row1476923255084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1865237213084824"><a name="p1865237213084824"></a><a name="p1865237213084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p516366699084824"><a name="p516366699084824"></a><a name="p516366699084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1573223675084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the Bessel function of the second kind of order  **0**  for  **x**  if the operation is successful . If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0.0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and reports a pole error. If  **x**  is a negative value, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and reports a range error. If an overflow range error occurs, this function returns  **0.0**. 



## y0f\(\)<a name="gaba3cd2d73c1ae75ec2d01ebb2dfc108c"></a>

```
float y0f (float x)
```

 **Description:**

Calculates the Bessel function of the second kind of order  **0**  for the float value  **x**. 

**Parameters:**

<a name="table1822433378084824"></a>
<table><thead align="left"><tr id="row574997225084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1417356124084824"><a name="p1417356124084824"></a><a name="p1417356124084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p585386111084824"><a name="p585386111084824"></a><a name="p585386111084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1435717465084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and reports a pole error if  **x**  is  **0.0**; returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and reports a domain error if  **x**  is a negative value; returns  **0.0**  if an overflow range error occurs. 



## y1\(\)<a name="ga369368526a105f3fba6776b11586070c"></a>

```
double y1 (double x)
```

 **Description:**

Calculates the Bessel function of the second kind of order  **1**  for the double value  **x**. 

**Parameters:**

<a name="table562822725084824"></a>
<table><thead align="left"><tr id="row1781366809084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p510499003084824"><a name="p510499003084824"></a><a name="p510499003084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p901274715084824"><a name="p901274715084824"></a><a name="p901274715084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row441272577084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the Bessel function of the second kind of order  **1**  for  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0.0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and reports a pole error. If  **x**  is a negative value, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and reports a range error. If an overflow range error occurs, this function returns  **0.0**. 



## y1f\(\)<a name="ga5f37c38e8985dafae6abca2d1782c160"></a>

```
float y1f (float x)
```

 **Description:**

Calculates the Bessel function of the second kind of order  **1**  for the float value  **x**. 

**Parameters:**

<a name="table882237174084824"></a>
<table><thead align="left"><tr id="row1413588954084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1172945773084824"><a name="p1172945773084824"></a><a name="p1172945773084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p147511717084824"><a name="p147511717084824"></a><a name="p147511717084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1761739676084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and reports a pole error if  **x**  is  **0.0**; returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and reports a domain error if  **x**  is a negative value; returns  **0.0**  if an overflow range error occurs. 



## yn\(\)<a name="gae31b4c8c6af724eaa73ad2ebce1aa3ce"></a>

```
double yn (int n, double x )
```

 **Description:**

Calculates the Bessel function of the second kind of order  **n**  for the double value  **x**. 

**Parameters:**

<a name="table2066749750084824"></a>
<table><thead align="left"><tr id="row1510572343084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1088144464084824"><a name="p1088144464084824"></a><a name="p1088144464084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1720964234084824"><a name="p1720964234084824"></a><a name="p1720964234084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1598094975084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">n</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the order of the Bessel function of the first kind. </td>
</tr>
<tr id="row33079648084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the Bessel function of the second kind of order  **n**  for  **x**  if the operation is successful. If  **x**  is a NaN value, this function returns a NaN value. If  **x**  is  **0.0**, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and reports a pole error. If  **x**  is a negative value, this function returns  **-[HUGE\_VAL](math.md#gaf2164b2db92d8a0ed3838ad5c28db971)**  and reports a range error. If an overflow range error occurs, this function returns  **0.0**. 



## ynf\(\)<a name="ga47f8750942b731456dd7f2cbf5f55806"></a>

```
float ynf (int n, float x )
```

 **Description:**

Calculates the Bessel function of the second kind of order  **n**  for the float value  **x**. 

**Parameters:**

<a name="table1341026168084824"></a>
<table><thead align="left"><tr id="row829427318084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1963422108084824"><a name="p1963422108084824"></a><a name="p1963422108084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p147240682084824"><a name="p147240682084824"></a><a name="p147240682084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1657605516084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">n</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the order of the Bessel function of the second kind. </td>
</tr>
<tr id="row1024868396084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the float value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the calculation result if the operation is successful; returns a NaN value if  **x**  is a NaN value; returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and reports a pole error if  **x**  is  **0.0**; returns  **-[HUGE\_VALF](math.md#gacd69981d54c27fe0ff514645dbfc6359)**  and reports a domain error if  **x**  is a negative value; returns  **0.0**  if an overflow range error occurs. 



