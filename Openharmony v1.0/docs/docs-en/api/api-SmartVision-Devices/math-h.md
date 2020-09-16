# math.h<a name="EN-US_TOPIC_0000001055547980"></a>

## **Overview**<a name="section249436590084831"></a>

**Related Modules:**

[MATH](math.md)

**Description:**

Provides common math functions. 

You can use the functions provided in this file to perform mathematical operations during development. The functions include trigonometric, inverse trigonometric, hyperbolic, inverse hyperbolic, rounding, exponential, logarithmic, and Bessel functions. When using these functions, pay attention to the value range of their input parameters. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1955606870084831"></a>

## Macros<a name="define-members"></a>

<a name="table1524184398084831"></a>
<table><thead align="left"><tr id="row266060427084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1008542788084831"><a name="p1008542788084831"></a><a name="p1008542788084831"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1753110660084831"><a name="p1753110660084831"></a><a name="p1753110660084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row509776808084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440276717084831"><a name="p440276717084831"></a><a name="p440276717084831"></a><a href="math.md#ga8abfcc76130f3f991d124dd22d7e69bc">NAN</a>   (0.0f/0.0f)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p685069145084831"><a name="p685069145084831"></a><a name="p685069145084831"></a>Indicates an undefined or unrepresentable value. </p>
</td>
</tr>
<tr id="row1010642342084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878964641084831"><a name="p878964641084831"></a><a name="p878964641084831"></a><a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a>   1e5000f</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333629775084831"><a name="p333629775084831"></a><a name="p333629775084831"></a>Indicates an infinity. </p>
</td>
</tr>
<tr id="row1923529264084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1110602888084831"><a name="p1110602888084831"></a><a name="p1110602888084831"></a><a href="math.md#gacd69981d54c27fe0ff514645dbfc6359">HUGE_VALF</a>   <a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057742474084831"><a name="p1057742474084831"></a><a name="p1057742474084831"></a>Indicates a float infinity. </p>
</td>
</tr>
<tr id="row425499674084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451053562084831"><a name="p451053562084831"></a><a name="p451053562084831"></a><a href="math.md#gaf2164b2db92d8a0ed3838ad5c28db971">HUGE_VAL</a>   ((double)<a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507065215084831"><a name="p1507065215084831"></a><a name="p1507065215084831"></a>Indicates a double infinity. </p>
</td>
</tr>
<tr id="row286777046084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p951566149084831"><a name="p951566149084831"></a><a name="p951566149084831"></a><a href="math.md#gab8b359c356d4311bf5d4ae6c03f43182">HUGE_VALL</a>   ((long double)<a href="math.md#ga956e2723d559858d08644ac99146e910">INFINITY</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11242831084831"><a name="p11242831084831"></a><a name="p11242831084831"></a>Indicates a long double infinity. </p>
</td>
</tr>
<tr id="row1953547936084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242454096084831"><a name="p1242454096084831"></a><a name="p1242454096084831"></a><a href="math.md#ga42b212d215eab7142f8272fefcd1c938">MATH_ERRNO</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1518194976084831"><a name="p1518194976084831"></a><a name="p1518194976084831"></a>Indicates an error that occurs in floating-point operations. </p>
</td>
</tr>
<tr id="row759110900084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1763342743084831"><a name="p1763342743084831"></a><a name="p1763342743084831"></a><a href="math.md#gae05ce3fe3745507c8e989f6e9efe0a83">MATH_ERREXCEPT</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382320162084831"><a name="p382320162084831"></a><a name="p382320162084831"></a>Indicates a floating-point exception. </p>
</td>
</tr>
<tr id="row1197331402084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2134911990084831"><a name="p2134911990084831"></a><a name="p2134911990084831"></a><a href="math.md#gaa8618aec27dedcd32f494ccf22f3ed42">math_errhandling</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660590674084831"><a name="p1660590674084831"></a><a name="p1660590674084831"></a>Indicates the error handling mechanism employed by math functions. </p>
</td>
</tr>
<tr id="row1981012382084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032284063084831"><a name="p2032284063084831"></a><a name="p2032284063084831"></a><a href="math.md#ga01e2e5be97c739a5bdcbc619b44f9742">FP_ILOGBNAN</a>   (-1-0x7fffffff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139971388084831"><a name="p1139971388084831"></a><a name="p1139971388084831"></a>Indicates the calculation result of <a href="math.md#ga600dd249210d15af31b9a29c2d09d255">ilogb</a>(<a href="math.md#ga8abfcc76130f3f991d124dd22d7e69bc">NAN</a>). </p>
</td>
</tr>
<tr id="row1879880657084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1980701909084831"><a name="p1980701909084831"></a><a name="p1980701909084831"></a><a href="math.md#ga9ec0e31304d15c42262b2c4a3b58443c">FP_ILOGB0</a>   <a href="math.md#ga01e2e5be97c739a5bdcbc619b44f9742">FP_ILOGBNAN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89638558084831"><a name="p89638558084831"></a><a name="p89638558084831"></a>Indicates the calculation result of <a href="math.md#ga600dd249210d15af31b9a29c2d09d255">ilogb</a>(0). </p>
</td>
</tr>
<tr id="row1110872765084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1234880803084831"><a name="p1234880803084831"></a><a name="p1234880803084831"></a><a href="math.md#ga1d481cc6e6a8ff729147ed46e61a4c9f">FP_NAN</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312464303084831"><a name="p1312464303084831"></a><a name="p1312464303084831"></a>Indicates a Not-a-Number (NaN) value. </p>
</td>
</tr>
<tr id="row536928976084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p489786504084831"><a name="p489786504084831"></a><a name="p489786504084831"></a><a href="math.md#ga4f64bcc64f8b84dd9daf5a4e56abf0ca">FP_INFINITE</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1562707142084831"><a name="p1562707142084831"></a><a name="p1562707142084831"></a>Indicates an infinity. </p>
</td>
</tr>
<tr id="row1098226604084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1666969082084831"><a name="p1666969082084831"></a><a name="p1666969082084831"></a><a href="math.md#ga32eba50da417c9f303ba49583d5b9f40">FP_ZERO</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427222823084831"><a name="p427222823084831"></a><a name="p427222823084831"></a>Indicates value <strong id="b2142707818084831"><a name="b2142707818084831"></a><a name="b2142707818084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1197164921084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1765922824084831"><a name="p1765922824084831"></a><a name="p1765922824084831"></a><a href="math.md#gadbc0a13ec75c05d238ca12ef1f8c6b2b">FP_SUBNORMAL</a>   3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1506597100084831"><a name="p1506597100084831"></a><a name="p1506597100084831"></a>Indicates a subnormal. </p>
</td>
</tr>
<tr id="row1446474936084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p229916938084831"><a name="p229916938084831"></a><a name="p229916938084831"></a><a href="math.md#gab9e29bb9e853934c4ba647c840b7e5de">FP_NORMAL</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615431595084831"><a name="p615431595084831"></a><a name="p615431595084831"></a>Indicates a normal value. </p>
</td>
</tr>
<tr id="row947288310084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472599455084831"><a name="p472599455084831"></a><a name="p472599455084831"></a><a href="math.md#ga2a266c767456556e5c0da234b602b18b">isinf</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094459767084831"><a name="p2094459767084831"></a><a name="p2094459767084831"></a>Checks whether the floating-point value <strong id="b1010143880084831"><a name="b1010143880084831"></a><a name="b1010143880084831"></a>x</strong> is an infinity. </p>
</td>
</tr>
<tr id="row2138732160084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p246780122084831"><a name="p246780122084831"></a><a name="p246780122084831"></a><a href="math.md#ga2e1baae9134e580910322362dc23290e">isnan</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1172455215084831"><a name="p1172455215084831"></a><a name="p1172455215084831"></a>Checks whether the floating-point value <strong id="b527408509084831"><a name="b527408509084831"></a><a name="b527408509084831"></a>x</strong> is a NaN value. </p>
</td>
</tr>
<tr id="row60895538084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1318996028084831"><a name="p1318996028084831"></a><a name="p1318996028084831"></a><a href="math.md#gad83f5949c4b5d810225b9a834840bac9">isnormal</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497776856084831"><a name="p497776856084831"></a><a name="p497776856084831"></a>Checks whether the floating-point value <strong id="b1478449374084831"><a name="b1478449374084831"></a><a name="b1478449374084831"></a>x</strong> is a normal value. </p>
</td>
</tr>
<tr id="row1993356306084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48091803084831"><a name="p48091803084831"></a><a name="p48091803084831"></a><a href="math.md#ga256d70a32c03904ce13c999c1e9dc35d">isfinite</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p914072511084831"><a name="p914072511084831"></a><a name="p914072511084831"></a>Checks whether the floating-point value <strong id="b2048708184084831"><a name="b2048708184084831"></a><a name="b2048708184084831"></a>x</strong> is finite. </p>
</td>
</tr>
<tr id="row1630953543084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924291927084831"><a name="p924291927084831"></a><a name="p924291927084831"></a><a href="math.md#gaa63ffa98f213f62e536b073c28cb3cd8">signbit</a>(x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289698970084831"><a name="p289698970084831"></a><a name="p289698970084831"></a>Checks whether the sign of the floating-point value <strong id="b201367633084831"><a name="b201367633084831"></a><a name="b201367633084831"></a>x</strong> is negative. </p>
</td>
</tr>
<tr id="row529659533084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121413649084831"><a name="p2121413649084831"></a><a name="p2121413649084831"></a><a href="math.md#ga33daf51eb7138d477e0b0985c51e4fad">isunordered</a>(x, y)   (<a href="math.md#ga2e1baae9134e580910322362dc23290e">isnan</a>((x)) ? ((void)(y),1) : <a href="math.md#ga2e1baae9134e580910322362dc23290e">isnan</a>((y)))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549576560084831"><a name="p549576560084831"></a><a name="p549576560084831"></a>Checks whether floating-point value <strong id="b275785126084831"><a name="b275785126084831"></a><a name="b275785126084831"></a>x</strong> or <strong id="b1257306548084831"><a name="b1257306548084831"></a><a name="b1257306548084831"></a>y</strong> is unordered. </p>
</td>
</tr>
<tr id="row1444095824084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p623072298084831"><a name="p623072298084831"></a><a name="p623072298084831"></a><a href="math.md#ga61079b32084130da4345c2eea93e0d61">isless</a>(x, y)   __tg_pred_2(x, y, __isless)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1249293862084831"><a name="p1249293862084831"></a><a name="p1249293862084831"></a>Checks whether floating-point value <strong id="b54419321084831"><a name="b54419321084831"></a><a name="b54419321084831"></a>x</strong> is less than <strong id="b418075076084831"><a name="b418075076084831"></a><a name="b418075076084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1411904018084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p122620012084831"><a name="p122620012084831"></a><a name="p122620012084831"></a><a href="math.md#gabf3cb1e5a0aaa1c42dffa9ebb1d78c30">islessequal</a>(x, y)   __tg_pred_2(x, y, __islessequal)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147005199084831"><a name="p1147005199084831"></a><a name="p1147005199084831"></a>Checks whether floating-point value <strong id="b1362176268084831"><a name="b1362176268084831"></a><a name="b1362176268084831"></a>x</strong> is less than or equal to <strong id="b1181969433084831"><a name="b1181969433084831"></a><a name="b1181969433084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1094167085084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p268645503084831"><a name="p268645503084831"></a><a name="p268645503084831"></a><a href="math.md#ga5e534756b747fd2e9ee19f8fdd93b30b">islessgreater</a>(x, y)   __tg_pred_2(x, y, __islessgreater)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1522083640084831"><a name="p1522083640084831"></a><a name="p1522083640084831"></a>Checks whether floating-point value <strong id="b157315373084831"><a name="b157315373084831"></a><a name="b157315373084831"></a>x</strong> is either less than or greater than <strong id="b1646443721084831"><a name="b1646443721084831"></a><a name="b1646443721084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1624269025084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1975849499084831"><a name="p1975849499084831"></a><a name="p1975849499084831"></a><a href="math.md#gada788e9d6ce0ca927874ec4e53af1f77">isgreater</a>(x, y)   __tg_pred_2(x, y, __isgreater)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1295970448084831"><a name="p1295970448084831"></a><a name="p1295970448084831"></a>Checks whether floating-point value <strong id="b131068385084831"><a name="b131068385084831"></a><a name="b131068385084831"></a>x</strong> is greater than <strong id="b1739208217084831"><a name="b1739208217084831"></a><a name="b1739208217084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row596175704084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p513943469084831"><a name="p513943469084831"></a><a name="p513943469084831"></a><a href="math.md#ga5a7f86a4d3e6139e4913e2e8eba52612">isgreaterequal</a>(x, y)   __tg_pred_2(x, y, __isgreaterequal)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619988950084831"><a name="p1619988950084831"></a><a name="p1619988950084831"></a>Checks whether floating-point value <strong id="b755991705084831"><a name="b755991705084831"></a><a name="b755991705084831"></a>x</strong> is greater than or equal to <strong id="b1261264887084831"><a name="b1261264887084831"></a><a name="b1261264887084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1341623281084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1308290705084831"><a name="p1308290705084831"></a><a name="p1308290705084831"></a><a href="math.md#ga5e9e29217f6ec61105a4520ec5942225">MAXFLOAT</a>   3.40282346638528859812e+38F</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1131233172084831"><a name="p1131233172084831"></a><a name="p1131233172084831"></a>Maximum value of type float. </p>
</td>
</tr>
<tr id="row926283581084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691216845084831"><a name="p691216845084831"></a><a name="p691216845084831"></a><a href="math.md#ga9bf5d952c5c93c70f9e66c9794d406c9">M_E</a>   2.7182818284590452354 /* e */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1924632531084831"><a name="p1924632531084831"></a><a name="p1924632531084831"></a>Base e of natural logarithms. </p>
</td>
</tr>
<tr id="row184616245084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p914576905084831"><a name="p914576905084831"></a><a name="p914576905084831"></a><a href="math.md#gac5c747ee5bcbe892875672a0b9d8171c">M_LOG2E</a>   1.4426950408889634074 /* log_2 e */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p271651608084831"><a name="p271651608084831"></a><a name="p271651608084831"></a>Logarithm to base 2 of <strong id="b2060248621084831"><a name="b2060248621084831"></a><a name="b2060248621084831"></a>M_E</strong> </p>
</td>
</tr>
<tr id="row89442066084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1741123364084831"><a name="p1741123364084831"></a><a name="p1741123364084831"></a><a href="math.md#ga9ed2b5582226f3896424ff6d2a3ebb14">M_LOG10E</a>   0.43429448190325182765 /* log_10 e */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1931150944084831"><a name="p1931150944084831"></a><a name="p1931150944084831"></a>Logarithm to base 10 of <strong id="b27993592084831"><a name="b27993592084831"></a><a name="b27993592084831"></a>M_E</strong> </p>
</td>
</tr>
<tr id="row1405995396084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1512123508084831"><a name="p1512123508084831"></a><a name="p1512123508084831"></a><a href="math.md#ga92428112a5d24721208748774a4f23e6">M_LN2</a>   0.69314718055994530942 /* log_e 2 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p811963695084831"><a name="p811963695084831"></a><a name="p811963695084831"></a>Natural logarithm of <strong id="b927244308084831"><a name="b927244308084831"></a><a name="b927244308084831"></a>2</strong> </p>
</td>
</tr>
<tr id="row859516482084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271335129084831"><a name="p1271335129084831"></a><a name="p1271335129084831"></a><a href="math.md#ga0a53871497a155afe91424c28a8ec3c4">M_LN10</a>   2.30258509299404568402 /* log_e 10 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p830472116084831"><a name="p830472116084831"></a><a name="p830472116084831"></a>Natural logarithm of <strong id="b1280618064084831"><a name="b1280618064084831"></a><a name="b1280618064084831"></a>10</strong> </p>
</td>
</tr>
<tr id="row1562940334084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p110218576084831"><a name="p110218576084831"></a><a name="p110218576084831"></a><a href="math.md#gae71449b1cc6e6250b91f539153a7a0d3">M_PI</a>   3.14159265358979323846 /* pi */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40948214084831"><a name="p40948214084831"></a><a name="p40948214084831"></a>Ratio of a circle's circumference to its diameter. </p>
</td>
</tr>
<tr id="row1746000149084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870248201084831"><a name="p1870248201084831"></a><a name="p1870248201084831"></a><a href="math.md#ga958e4508ed28ee5cc04249144312c15f">M_PI_2</a>   1.57079632679489661923 /* pi/2 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2008536521084831"><a name="p2008536521084831"></a><a name="p2008536521084831"></a>Pi divided by <strong id="b1977311795084831"><a name="b1977311795084831"></a><a name="b1977311795084831"></a>2</strong> </p>
</td>
</tr>
<tr id="row1824401356084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1747121051084831"><a name="p1747121051084831"></a><a name="p1747121051084831"></a><a href="math.md#gaeb24420b096a677f3a2dc5a72b36bf22">M_PI_4</a>   0.78539816339744830962 /* pi/4 */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152211602084831"><a name="p1152211602084831"></a><a name="p1152211602084831"></a>Pi divided by <strong id="b854922017084831"><a name="b854922017084831"></a><a name="b854922017084831"></a>4</strong> </p>
</td>
</tr>
<tr id="row123568146084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1113924376084831"><a name="p1113924376084831"></a><a name="p1113924376084831"></a><a href="math.md#ga08dfac3cca9601a02fc88356cc078e1d">M_1_PI</a>   0.31830988618379067154 /* 1/pi */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p373256579084831"><a name="p373256579084831"></a><a name="p373256579084831"></a>Reciprocal of pi. </p>
</td>
</tr>
<tr id="row1797336159084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p666045834084831"><a name="p666045834084831"></a><a name="p666045834084831"></a><a href="math.md#ga97f6d6514d3d3dd50c3a2a6d622673db">M_2_PI</a>   0.63661977236758134308 /* 2/pi */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915868441084831"><a name="p915868441084831"></a><a name="p915868441084831"></a>Two times the reciprocal of pi. </p>
</td>
</tr>
<tr id="row1408222243084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895028545084831"><a name="p895028545084831"></a><a name="p895028545084831"></a><a href="math.md#ga631ff334c4a1a6db2e8a7ff4acbe48a5">M_2_SQRTPI</a>   1.12837916709551257390 /* 2/<a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a>(pi) */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p121211750084831"><a name="p121211750084831"></a><a name="p121211750084831"></a>Two times the reciprocal of the square root of pi. </p>
</td>
</tr>
<tr id="row1949914791084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p89871589084831"><a name="p89871589084831"></a><a name="p89871589084831"></a><a href="math.md#ga66b3ab30f1332874326ed93969e496e0">M_SQRT2</a>   1.41421356237309504880 /* <a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a>(2) */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p875448808084831"><a name="p875448808084831"></a><a name="p875448808084831"></a>Square root of <strong id="b193850015084831"><a name="b193850015084831"></a><a name="b193850015084831"></a>2</strong> </p>
</td>
</tr>
<tr id="row816892461084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735457111084831"><a name="p735457111084831"></a><a name="p735457111084831"></a><a href="math.md#gacdbb2c2f9429f08916f03c8786d2d2d7">M_SQRT1_2</a>   0.70710678118654752440 /* 1/<a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a>(2) */</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p515232173084831"><a name="p515232173084831"></a><a name="p515232173084831"></a>Reciprocal of the square root of <strong id="b365831992084831"><a name="b365831992084831"></a><a name="b365831992084831"></a>2</strong> </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table949854444084831"></a>
<table><thead align="left"><tr id="row670318656084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1070030069084831"><a name="p1070030069084831"></a><a name="p1070030069084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p448329285084831"><a name="p448329285084831"></a><a name="p448329285084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row131245112084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p744933299084831"><a name="p744933299084831"></a><a name="p744933299084831"></a><a href="math.md#gae93afe22ff34c79ee97ea3eaf77557db">acos</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601811052084831"><a name="p601811052084831"></a><a name="p601811052084831"></a>double </p>
<p id="p1671027301084831"><a name="p1671027301084831"></a><a name="p1671027301084831"></a>Calculates the arc cosine of the double value <strong id="b1025948409084831"><a name="b1025948409084831"></a><a name="b1025948409084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1582084632084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1057011558084831"><a name="p1057011558084831"></a><a name="p1057011558084831"></a><a href="math.md#ga983a9e1aa7568df39153ea4d8e16653b">acosf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1942714576084831"><a name="p1942714576084831"></a><a name="p1942714576084831"></a>float </p>
<p id="p1283226466084831"><a name="p1283226466084831"></a><a name="p1283226466084831"></a>Calculates the arc cosine of the float value <strong id="b624543938084831"><a name="b624543938084831"></a><a name="b624543938084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row123593411084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p293307948084831"><a name="p293307948084831"></a><a name="p293307948084831"></a><a href="math.md#gae84dc6cff92b3417098f16a1811635e4">acosl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1716533842084831"><a name="p1716533842084831"></a><a name="p1716533842084831"></a>long double </p>
<p id="p1967625220084831"><a name="p1967625220084831"></a><a name="p1967625220084831"></a>Calculates the arc cosine of the long double value <strong id="b1686850347084831"><a name="b1686850347084831"></a><a name="b1686850347084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row140902220084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1167699752084831"><a name="p1167699752084831"></a><a name="p1167699752084831"></a><a href="math.md#gac862445bcb46911b1782c284829d5e46">acosh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1369520055084831"><a name="p1369520055084831"></a><a name="p1369520055084831"></a>double </p>
<p id="p1123670458084831"><a name="p1123670458084831"></a><a name="p1123670458084831"></a>Calculates the inverse hyperbolic cosine of the double value <strong id="b712431011084831"><a name="b712431011084831"></a><a name="b712431011084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row828147946084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2008289351084831"><a name="p2008289351084831"></a><a name="p2008289351084831"></a><a href="math.md#ga84cfd14c3432390f70b6233d24ad173b">acoshf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96427082084831"><a name="p96427082084831"></a><a name="p96427082084831"></a>float </p>
<p id="p165409369084831"><a name="p165409369084831"></a><a name="p165409369084831"></a>Calculates the inverse hyperbolic cosine of float value <strong id="b283205077084831"><a name="b283205077084831"></a><a name="b283205077084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1365042178084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1598135660084831"><a name="p1598135660084831"></a><a name="p1598135660084831"></a><a href="math.md#ga104456314ba05665d6cbb805e823dd10">acoshl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1632096675084831"><a name="p1632096675084831"></a><a name="p1632096675084831"></a>long double </p>
<p id="p855969490084831"><a name="p855969490084831"></a><a name="p855969490084831"></a>Calculates the inverse hyperbolic cosine of the long double value <strong id="b618311660084831"><a name="b618311660084831"></a><a name="b618311660084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1503014597084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p783480663084831"><a name="p783480663084831"></a><a name="p783480663084831"></a><a href="math.md#gaa9528d92a3ae44ad6484da0774604454">asin</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p774763267084831"><a name="p774763267084831"></a><a name="p774763267084831"></a>double </p>
<p id="p648428479084831"><a name="p648428479084831"></a><a name="p648428479084831"></a>Calculates the arc sine of the double value <strong id="b1114278866084831"><a name="b1114278866084831"></a><a name="b1114278866084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row96208141084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094157214084831"><a name="p2094157214084831"></a><a name="p2094157214084831"></a><a href="math.md#ga7447a7400ca474ba42d127b04d6ee2b7">asinf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1284828877084831"><a name="p1284828877084831"></a><a name="p1284828877084831"></a>float </p>
<p id="p1440221536084831"><a name="p1440221536084831"></a><a name="p1440221536084831"></a>Calculates the arc sine of the float value <strong id="b1733528462084831"><a name="b1733528462084831"></a><a name="b1733528462084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row373551944084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p59048391084831"><a name="p59048391084831"></a><a name="p59048391084831"></a><a href="math.md#ga3ace56b4f2a4a9364993a5af676793c5">asinl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751812551084831"><a name="p751812551084831"></a><a name="p751812551084831"></a>long double </p>
<p id="p341158838084831"><a name="p341158838084831"></a><a name="p341158838084831"></a>Calculates the arc sine of the long double value <strong id="b1317940817084831"><a name="b1317940817084831"></a><a name="b1317940817084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row307168560084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259543080084831"><a name="p1259543080084831"></a><a name="p1259543080084831"></a><a href="math.md#ga907297107e93ea9c8a0c8409a8e65079">asinh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2035596689084831"><a name="p2035596689084831"></a><a name="p2035596689084831"></a>double </p>
<p id="p1289066940084831"><a name="p1289066940084831"></a><a name="p1289066940084831"></a>Calculates the inverse hyperbolic sine of the double value <strong id="b1681116694084831"><a name="b1681116694084831"></a><a name="b1681116694084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2131410102084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p151486846084831"><a name="p151486846084831"></a><a name="p151486846084831"></a><a href="math.md#ga1131c65ac49f31ed6774d27106c6394d">asinhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1529386637084831"><a name="p1529386637084831"></a><a name="p1529386637084831"></a>float </p>
<p id="p521742807084831"><a name="p521742807084831"></a><a name="p521742807084831"></a>Calculates the inverse hyperbolic sine of the float value <strong id="b1142845641084831"><a name="b1142845641084831"></a><a name="b1142845641084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1026200307084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p145439806084831"><a name="p145439806084831"></a><a name="p145439806084831"></a><a href="math.md#ga98df355372e19c11634992e4b7e35784">asinhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754792723084831"><a name="p754792723084831"></a><a name="p754792723084831"></a>long double </p>
<p id="p1386099560084831"><a name="p1386099560084831"></a><a name="p1386099560084831"></a>Calculates the inverse hyperbolic sine of the long double value <strong id="b1297008385084831"><a name="b1297008385084831"></a><a name="b1297008385084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row697156973084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904636880084831"><a name="p904636880084831"></a><a name="p904636880084831"></a><a href="math.md#ga1e2f8f6d64eaa95131bc63fee34970ea">atan</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211584172084831"><a name="p211584172084831"></a><a name="p211584172084831"></a>double </p>
<p id="p1913757157084831"><a name="p1913757157084831"></a><a name="p1913757157084831"></a>Calculates the arc tangent of the double value <strong id="b534677713084831"><a name="b534677713084831"></a><a name="b534677713084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row909495240084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1579986884084831"><a name="p1579986884084831"></a><a name="p1579986884084831"></a><a href="math.md#gaa582bc257e477e805f4ec384a39a3a8e">atanf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1192772316084831"><a name="p1192772316084831"></a><a name="p1192772316084831"></a>float </p>
<p id="p375148600084831"><a name="p375148600084831"></a><a name="p375148600084831"></a>Calculates the arc tangent of the float value <strong id="b440449002084831"><a name="b440449002084831"></a><a name="b440449002084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row462825618084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p741596610084831"><a name="p741596610084831"></a><a name="p741596610084831"></a><a href="math.md#ga650d8dd23c16c6699d84651a18827d37">atanl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p205861611084831"><a name="p205861611084831"></a><a name="p205861611084831"></a>long double </p>
<p id="p1489513796084831"><a name="p1489513796084831"></a><a name="p1489513796084831"></a>Calculates the arc tangent of the long double value <strong id="b300055242084831"><a name="b300055242084831"></a><a name="b300055242084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1132897010084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p542100340084831"><a name="p542100340084831"></a><a name="p542100340084831"></a><a href="math.md#ga349377202ca14f79eb335b1a421fe4d8">atan2</a> (double y, double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1114010754084831"><a name="p1114010754084831"></a><a name="p1114010754084831"></a>double </p>
<p id="p998599588084831"><a name="p998599588084831"></a><a name="p998599588084831"></a>Calculates the arc tangent of two double values <strong id="b1585670917084831"><a name="b1585670917084831"></a><a name="b1585670917084831"></a>x</strong> and <strong id="b28346989084831"><a name="b28346989084831"></a><a name="b28346989084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row269821731084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p561607399084831"><a name="p561607399084831"></a><a name="p561607399084831"></a><a href="math.md#gaf9e5469acf7a7bf82f29d86a77f539d4">atan2f</a> (float y, float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2004607796084831"><a name="p2004607796084831"></a><a name="p2004607796084831"></a>float </p>
<p id="p723649708084831"><a name="p723649708084831"></a><a name="p723649708084831"></a>Calculates the arc tangent of two float values <strong id="b1483995499084831"><a name="b1483995499084831"></a><a name="b1483995499084831"></a>x</strong> and <strong id="b2124447689084831"><a name="b2124447689084831"></a><a name="b2124447689084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1633558675084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1580074703084831"><a name="p1580074703084831"></a><a name="p1580074703084831"></a><a href="math.md#gaa983bf34c931b97d66be8b7bfd03dc48">atan2l</a> (long double y, long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1116599145084831"><a name="p1116599145084831"></a><a name="p1116599145084831"></a>long double </p>
<p id="p968321850084831"><a name="p968321850084831"></a><a name="p968321850084831"></a>Calculates the arc tangent of two long double values <strong id="b1580419436084831"><a name="b1580419436084831"></a><a name="b1580419436084831"></a>x</strong> and <strong id="b206972422084831"><a name="b206972422084831"></a><a name="b206972422084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row686817786084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241992870084831"><a name="p241992870084831"></a><a name="p241992870084831"></a><a href="math.md#gac07fd7b77fa341563abccf9efcc1a711">atanh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1493604261084831"><a name="p1493604261084831"></a><a name="p1493604261084831"></a>double </p>
<p id="p21402138084831"><a name="p21402138084831"></a><a name="p21402138084831"></a>Calculates the inverse hyperbolic tangent of the double value <strong id="b914728143084831"><a name="b914728143084831"></a><a name="b914728143084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row688034342084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p644483025084831"><a name="p644483025084831"></a><a name="p644483025084831"></a><a href="math.md#ga626d9d6644848e74188f37f0f3ddd4f4">atanhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1853873872084831"><a name="p1853873872084831"></a><a name="p1853873872084831"></a>float </p>
<p id="p1913164053084831"><a name="p1913164053084831"></a><a name="p1913164053084831"></a>Calculates the inverse hyperbolic tangent of the float value <strong id="b153883853084831"><a name="b153883853084831"></a><a name="b153883853084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row116801165084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1655108837084831"><a name="p1655108837084831"></a><a name="p1655108837084831"></a><a href="math.md#gab25c31215118cd62672c38f80f010d66">atanhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445685748084831"><a name="p1445685748084831"></a><a name="p1445685748084831"></a>long double </p>
<p id="p258730294084831"><a name="p258730294084831"></a><a name="p258730294084831"></a>Calculates the inverse hyperbolic tangent of the long double value <strong id="b742645875084831"><a name="b742645875084831"></a><a name="b742645875084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row748766740084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p514502353084831"><a name="p514502353084831"></a><a name="p514502353084831"></a><a href="math.md#ga8af00e2203928978e0242b4afd1d899f">cbrt</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1564047774084831"><a name="p1564047774084831"></a><a name="p1564047774084831"></a>double </p>
<p id="p1076990376084831"><a name="p1076990376084831"></a><a name="p1076990376084831"></a>Calculates the cube root of the double value <strong id="b1115496725084831"><a name="b1115496725084831"></a><a name="b1115496725084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1839200797084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p518763165084831"><a name="p518763165084831"></a><a name="p518763165084831"></a><a href="math.md#ga396c6a553500a355627741e234045bf4">cbrtf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229087468084831"><a name="p229087468084831"></a><a name="p229087468084831"></a>float </p>
<p id="p2005779524084831"><a name="p2005779524084831"></a><a name="p2005779524084831"></a>Calculates the cube root of the float value <strong id="b2102784844084831"><a name="b2102784844084831"></a><a name="b2102784844084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1758490845084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085743712084831"><a name="p2085743712084831"></a><a name="p2085743712084831"></a><a href="math.md#ga521c2f4c10b7bb5363bad058ef56794c">cbrtl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459618803084831"><a name="p1459618803084831"></a><a name="p1459618803084831"></a>long double </p>
<p id="p900305408084831"><a name="p900305408084831"></a><a name="p900305408084831"></a>Calculates the cube root of the long double value <strong id="b1972079085084831"><a name="b1972079085084831"></a><a name="b1972079085084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2043419605084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878728572084831"><a name="p878728572084831"></a><a name="p878728572084831"></a><a href="math.md#ga1ea6d7b591132268abc2e843ababd084">ceil</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p713825095084831"><a name="p713825095084831"></a><a name="p713825095084831"></a>double </p>
<p id="p1339375690084831"><a name="p1339375690084831"></a><a name="p1339375690084831"></a>Calculates the minimum integer greater than or equal to the double value <strong id="b154444838084831"><a name="b154444838084831"></a><a name="b154444838084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1669719200084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1426924784084831"><a name="p1426924784084831"></a><a name="p1426924784084831"></a><a href="math.md#ga8c1a8db0710bb3f25f643a0fca68fc60">ceilf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2039390250084831"><a name="p2039390250084831"></a><a name="p2039390250084831"></a>float </p>
<p id="p228695346084831"><a name="p228695346084831"></a><a name="p228695346084831"></a>Calculates the minimum integer greater than or equal to the float value <strong id="b1242214654084831"><a name="b1242214654084831"></a><a name="b1242214654084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1146610368084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p358446302084831"><a name="p358446302084831"></a><a name="p358446302084831"></a><a href="math.md#gae11b7781f057eb7ba5d7ed95be7fdbee">ceill</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1862691819084831"><a name="p1862691819084831"></a><a name="p1862691819084831"></a>long double </p>
<p id="p1589581786084831"><a name="p1589581786084831"></a><a name="p1589581786084831"></a>Calculates the minimum integer greater than or equal to the long double value <strong id="b1077880878084831"><a name="b1077880878084831"></a><a name="b1077880878084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row757188746084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p436612373084831"><a name="p436612373084831"></a><a name="p436612373084831"></a><a href="math.md#gad8d1296592a3e783acdd0de21ff58e2e">copysign</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1220566871084831"><a name="p1220566871084831"></a><a name="p1220566871084831"></a>double </p>
<p id="p387230163084831"><a name="p387230163084831"></a><a name="p387230163084831"></a>Generates a value by combining the magnitude of the double value <strong id="b2103957766084831"><a name="b2103957766084831"></a><a name="b2103957766084831"></a>x</strong> and the sign of the double value <strong id="b1204705576084831"><a name="b1204705576084831"></a><a name="b1204705576084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1973294352084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1419997534084831"><a name="p1419997534084831"></a><a name="p1419997534084831"></a><a href="math.md#gaf7eb976cc28d0a9a6f0827d01611f979">copysignf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1111700234084831"><a name="p1111700234084831"></a><a name="p1111700234084831"></a>float </p>
<p id="p1658393126084831"><a name="p1658393126084831"></a><a name="p1658393126084831"></a>Generates a value by combining the magnitude of the float value <strong id="b1680397490084831"><a name="b1680397490084831"></a><a name="b1680397490084831"></a>x</strong> and the sign of the float value <strong id="b1931112033084831"><a name="b1931112033084831"></a><a name="b1931112033084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1746604452084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p886372679084831"><a name="p886372679084831"></a><a name="p886372679084831"></a><a href="math.md#gae60d4866e88abf023d92d33c6351ae6f">copysignl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703443975084831"><a name="p1703443975084831"></a><a name="p1703443975084831"></a>long double </p>
<p id="p131572407084831"><a name="p131572407084831"></a><a name="p131572407084831"></a>Generates a value by combining the magnitude of the long double value <strong id="b1520077077084831"><a name="b1520077077084831"></a><a name="b1520077077084831"></a>x</strong> and the sign of the long double value <strong id="b1149387395084831"><a name="b1149387395084831"></a><a name="b1149387395084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row918037196084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1607496299084831"><a name="p1607496299084831"></a><a name="p1607496299084831"></a><a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1982270791084831"><a name="p1982270791084831"></a><a name="p1982270791084831"></a>double </p>
<p id="p465818625084831"><a name="p465818625084831"></a><a name="p465818625084831"></a>Calculates the cosine of the double value <strong id="b199520991084831"><a name="b199520991084831"></a><a name="b199520991084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row182107494084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1670055211084831"><a name="p1670055211084831"></a><a name="p1670055211084831"></a><a href="math.md#ga7b126b2344591e649c21c9ab0b8adb40">cosf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315163624084831"><a name="p315163624084831"></a><a name="p315163624084831"></a>float </p>
<p id="p721782038084831"><a name="p721782038084831"></a><a name="p721782038084831"></a>Calculates the cosine of the float value <strong id="b1382572917084831"><a name="b1382572917084831"></a><a name="b1382572917084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2057882576084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44404999084831"><a name="p44404999084831"></a><a name="p44404999084831"></a><a href="math.md#ga659287f7399efa8d6bc66dc37c8e35f4">cosl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p198674633084831"><a name="p198674633084831"></a><a name="p198674633084831"></a>long double </p>
<p id="p731440847084831"><a name="p731440847084831"></a><a name="p731440847084831"></a>Calculates the cosine of the long double value <strong id="b2047285440084831"><a name="b2047285440084831"></a><a name="b2047285440084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1078076590084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1174047367084831"><a name="p1174047367084831"></a><a name="p1174047367084831"></a><a href="math.md#ga3795d3c1f1d30819be56da4e4d67f64b">cosh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974623406084831"><a name="p1974623406084831"></a><a name="p1974623406084831"></a>double </p>
<p id="p1194485996084831"><a name="p1194485996084831"></a><a name="p1194485996084831"></a>Calculates the hyperbolic cosine of the double value <strong id="b1558940909084831"><a name="b1558940909084831"></a><a name="b1558940909084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1173325581084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001480351084831"><a name="p1001480351084831"></a><a name="p1001480351084831"></a><a href="math.md#ga498b368486b7ce8677820beeb78d8f66">coshf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1758082686084831"><a name="p1758082686084831"></a><a name="p1758082686084831"></a>float </p>
<p id="p354200851084831"><a name="p354200851084831"></a><a name="p354200851084831"></a>Calculates the hyperbolic cosine of the float value <strong id="b559826982084831"><a name="b559826982084831"></a><a name="b559826982084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row587400398084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1541268773084831"><a name="p1541268773084831"></a><a name="p1541268773084831"></a><a href="math.md#ga57602cd20f8de2dceea4f05ffb516d82">coshl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665677851084831"><a name="p1665677851084831"></a><a name="p1665677851084831"></a>long double </p>
<p id="p809626913084831"><a name="p809626913084831"></a><a name="p809626913084831"></a>Calculates the hyperbolic cosine of the long double value <strong id="b2019774299084831"><a name="b2019774299084831"></a><a name="b2019774299084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row864230544084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49479932084831"><a name="p49479932084831"></a><a name="p49479932084831"></a><a href="math.md#gaa8b35382a71885eed509a5f87bf5e266">erf</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1505164802084831"><a name="p1505164802084831"></a><a name="p1505164802084831"></a>double </p>
<p id="p765139259084831"><a name="p765139259084831"></a><a name="p765139259084831"></a>Calculates the error function of the double value <strong id="b1008426462084831"><a name="b1008426462084831"></a><a name="b1008426462084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1968587458084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2023474084084831"><a name="p2023474084084831"></a><a name="p2023474084084831"></a><a href="math.md#gaabebdd2dd548c14805831297ac129862">erff</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274332418084831"><a name="p274332418084831"></a><a name="p274332418084831"></a>float </p>
<p id="p1587188221084831"><a name="p1587188221084831"></a><a name="p1587188221084831"></a>Calculates the error function of the float value <strong id="b98639486084831"><a name="b98639486084831"></a><a name="b98639486084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1687575027084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790173081084831"><a name="p1790173081084831"></a><a name="p1790173081084831"></a><a href="math.md#ga6ccdcbbc2f0b22de2add8955e415170e">erfl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1672345866084831"><a name="p1672345866084831"></a><a name="p1672345866084831"></a>long double </p>
<p id="p1418219461084831"><a name="p1418219461084831"></a><a name="p1418219461084831"></a>Calculates the error function of the long double value <strong id="b380946911084831"><a name="b380946911084831"></a><a name="b380946911084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1929054633084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051947432084831"><a name="p2051947432084831"></a><a name="p2051947432084831"></a><a href="math.md#ga0b6c4cfae41124da64c9a2dcc09e6045">erfc</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p747844892084831"><a name="p747844892084831"></a><a name="p747844892084831"></a>double </p>
<p id="p171578223084831"><a name="p171578223084831"></a><a name="p171578223084831"></a>Calculates the complementary error function of the double value <strong id="b156616385084831"><a name="b156616385084831"></a><a name="b156616385084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row967528679084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p149107401084831"><a name="p149107401084831"></a><a name="p149107401084831"></a><a href="math.md#gad948b9d3bfcb66c074ffe17326030d41">erfcf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p639747337084831"><a name="p639747337084831"></a><a name="p639747337084831"></a>float </p>
<p id="p41580796084831"><a name="p41580796084831"></a><a name="p41580796084831"></a>Calculates the complementary error function of the float value <strong id="b164400250084831"><a name="b164400250084831"></a><a name="b164400250084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1872408620084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1371437840084831"><a name="p1371437840084831"></a><a name="p1371437840084831"></a><a href="math.md#ga8ac2c9e0246c0c8106d04762a9623594">erfcl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444808539084831"><a name="p444808539084831"></a><a name="p444808539084831"></a>long double </p>
<p id="p655532294084831"><a name="p655532294084831"></a><a name="p655532294084831"></a>Calculates the complementary error function of the long double value <strong id="b1529163375084831"><a name="b1529163375084831"></a><a name="b1529163375084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1111747947084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432088134084831"><a name="p432088134084831"></a><a name="p432088134084831"></a><a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124213291084831"><a name="p1124213291084831"></a><a name="p1124213291084831"></a>double </p>
<p id="p1266741110084831"><a name="p1266741110084831"></a><a name="p1266741110084831"></a>Calculates the base-e exponential function of the double value <strong id="b684318755084831"><a name="b684318755084831"></a><a name="b684318755084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2060005030084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1484773928084831"><a name="p1484773928084831"></a><a name="p1484773928084831"></a><a href="math.md#ga0c2bc89b8355a89542ac98d9e2120363">expf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1962205853084831"><a name="p1962205853084831"></a><a name="p1962205853084831"></a>float </p>
<p id="p1269198805084831"><a name="p1269198805084831"></a><a name="p1269198805084831"></a>Calculates the base-e exponential function of the float value <strong id="b788467151084831"><a name="b788467151084831"></a><a name="b788467151084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1883025987084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522853516084831"><a name="p1522853516084831"></a><a name="p1522853516084831"></a><a href="math.md#gaed4eb11ef1397c751334311ce5b43920">expl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554095059084831"><a name="p1554095059084831"></a><a name="p1554095059084831"></a>long double </p>
<p id="p552891460084831"><a name="p552891460084831"></a><a name="p552891460084831"></a>Calculates the base-e exponential function of the long double value <strong id="b1090770262084831"><a name="b1090770262084831"></a><a name="b1090770262084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row885524774084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1852384654084831"><a name="p1852384654084831"></a><a name="p1852384654084831"></a><a href="math.md#ga86e37219434c0b7978453b6ca88fc5fb">exp2</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1346942582084831"><a name="p1346942582084831"></a><a name="p1346942582084831"></a>double </p>
<p id="p900709169084831"><a name="p900709169084831"></a><a name="p900709169084831"></a>Calculates the base-2 exponential function of the double value <strong id="b1963161293084831"><a name="b1963161293084831"></a><a name="b1963161293084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1484991390084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589900154084831"><a name="p589900154084831"></a><a name="p589900154084831"></a><a href="math.md#gaed26c6708ff2027f9a8214d206eef0e7">exp2f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403011063084831"><a name="p403011063084831"></a><a name="p403011063084831"></a>float </p>
<p id="p1774237326084831"><a name="p1774237326084831"></a><a name="p1774237326084831"></a>Calculates the base-2 exponential function of the float value <strong id="b2035493089084831"><a name="b2035493089084831"></a><a name="b2035493089084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row284766656084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p769783326084831"><a name="p769783326084831"></a><a name="p769783326084831"></a><a href="math.md#ga4618e032de8318b72df5cc71f15b5e45">exp2l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p932829903084831"><a name="p932829903084831"></a><a name="p932829903084831"></a>long double </p>
<p id="p1162944153084831"><a name="p1162944153084831"></a><a name="p1162944153084831"></a>Calculates the base-2 exponential function of the long double value <strong id="b1351415503084831"><a name="b1351415503084831"></a><a name="b1351415503084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2110106268084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376288817084831"><a name="p1376288817084831"></a><a name="p1376288817084831"></a><a href="math.md#gae4963ac40f96d4b1fe8af1b1e90a20bb">expm1</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623284499084831"><a name="p623284499084831"></a><a name="p623284499084831"></a>double </p>
<p id="p1692934273084831"><a name="p1692934273084831"></a><a name="p1692934273084831"></a>Calculates e raised to the power of the double value <strong id="b691424131084831"><a name="b691424131084831"></a><a name="b691424131084831"></a>x</strong> minus one, that is, (e^x)-1. </p>
</td>
</tr>
<tr id="row1398968564084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p77911835084831"><a name="p77911835084831"></a><a name="p77911835084831"></a><a href="math.md#ga5b8d8815f5c801fdbdb7f7767fbf9af4">expm1f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p441953163084831"><a name="p441953163084831"></a><a name="p441953163084831"></a>float </p>
<p id="p739037991084831"><a name="p739037991084831"></a><a name="p739037991084831"></a>Calculates e raised to the power of the float value <strong id="b927077186084831"><a name="b927077186084831"></a><a name="b927077186084831"></a>x</strong> minus one. </p>
</td>
</tr>
<tr id="row18696538084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479937999084831"><a name="p479937999084831"></a><a name="p479937999084831"></a><a href="math.md#ga702b0680671cf9ef94017ac04f77358b">expm1l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804579833084831"><a name="p804579833084831"></a><a name="p804579833084831"></a>long double </p>
<p id="p276651207084831"><a name="p276651207084831"></a><a name="p276651207084831"></a>Calculates e raised to the power of the long double value <strong id="b1461417372084831"><a name="b1461417372084831"></a><a name="b1461417372084831"></a>x</strong> minus one. </p>
</td>
</tr>
<tr id="row1896839025084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901080018084831"><a name="p901080018084831"></a><a name="p901080018084831"></a><a href="math.md#ga8fb5c0b9b43a108724b355136d29d2f9">fabs</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036052068084831"><a name="p1036052068084831"></a><a name="p1036052068084831"></a>double </p>
<p id="p1833789049084831"><a name="p1833789049084831"></a><a name="p1833789049084831"></a>Calculates the absolute value of the double value <strong id="b892514219084831"><a name="b892514219084831"></a><a name="b892514219084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1858904786084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1848139841084831"><a name="p1848139841084831"></a><a name="p1848139841084831"></a><a href="math.md#ga9b02e2f3ebf257ac4f4d3ca1da6147d7">fabsf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1131036706084831"><a name="p1131036706084831"></a><a name="p1131036706084831"></a>float </p>
<p id="p1815620827084831"><a name="p1815620827084831"></a><a name="p1815620827084831"></a>Calculates the absolute value of the float value <strong id="b2081157444084831"><a name="b2081157444084831"></a><a name="b2081157444084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1373059382084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995335907084831"><a name="p995335907084831"></a><a name="p995335907084831"></a><a href="math.md#ga404c051ab9afd74c7ceed207683a235f">fabsl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1379283912084831"><a name="p1379283912084831"></a><a name="p1379283912084831"></a>long double </p>
<p id="p224558255084831"><a name="p224558255084831"></a><a name="p224558255084831"></a>Calculates the absolute value of the long double value <strong id="b1442741863084831"><a name="b1442741863084831"></a><a name="b1442741863084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row529691272084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1318290561084831"><a name="p1318290561084831"></a><a name="p1318290561084831"></a><a href="math.md#ga800522810eaaed28bd53798bff4b0bfa">fdim</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14957849084831"><a name="p14957849084831"></a><a name="p14957849084831"></a>double </p>
<p id="p746138357084831"><a name="p746138357084831"></a><a name="p746138357084831"></a>Calculates the positive difference between the double value <strong id="b1122300649084831"><a name="b1122300649084831"></a><a name="b1122300649084831"></a>x</strong> and <strong id="b1416039498084831"><a name="b1416039498084831"></a><a name="b1416039498084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row159063098084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1512088147084831"><a name="p1512088147084831"></a><a name="p1512088147084831"></a><a href="math.md#gaeee3a0bf2804c53c65199590ac4804cf">fdimf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35578124084831"><a name="p35578124084831"></a><a name="p35578124084831"></a>float </p>
<p id="p1512174615084831"><a name="p1512174615084831"></a><a name="p1512174615084831"></a>Calculates the positive difference between the float value <strong id="b828872178084831"><a name="b828872178084831"></a><a name="b828872178084831"></a>x</strong> and <strong id="b604963021084831"><a name="b604963021084831"></a><a name="b604963021084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1519551479084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2042593138084831"><a name="p2042593138084831"></a><a name="p2042593138084831"></a><a href="math.md#gab88ba65d1861deddbbc5cb5384d6a02e">fdiml</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1945935544084831"><a name="p1945935544084831"></a><a name="p1945935544084831"></a>long double </p>
<p id="p2041889203084831"><a name="p2041889203084831"></a><a name="p2041889203084831"></a>Calculates the positive difference between the long double value <strong id="b195140002084831"><a name="b195140002084831"></a><a name="b195140002084831"></a>x</strong> and <strong id="b1588125932084831"><a name="b1588125932084831"></a><a name="b1588125932084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row824826290084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1768806500084831"><a name="p1768806500084831"></a><a name="p1768806500084831"></a><a href="math.md#ga6de60a3e907dcf0bfe3ea8d64f1e8873">floor</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813191644084831"><a name="p813191644084831"></a><a name="p813191644084831"></a>double </p>
<p id="p504152857084831"><a name="p504152857084831"></a><a name="p504152857084831"></a>Obtains the largest integer less than or equal to the double value <strong id="b1588901512084831"><a name="b1588901512084831"></a><a name="b1588901512084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1298442864084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p706484548084831"><a name="p706484548084831"></a><a name="p706484548084831"></a><a href="math.md#ga0bcc6aa4b3c37bfa73f06ebdecc0d247">floorf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91905720084831"><a name="p91905720084831"></a><a name="p91905720084831"></a>float </p>
<p id="p1053217850084831"><a name="p1053217850084831"></a><a name="p1053217850084831"></a>Obtains the largest integer less than or equal to the float value <strong id="b706968166084831"><a name="b706968166084831"></a><a name="b706968166084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row164964814084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p464249391084831"><a name="p464249391084831"></a><a name="p464249391084831"></a><a href="math.md#ga211df53cdf5208b9bbfa92e2d9aef97f">floorl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1277259072084831"><a name="p1277259072084831"></a><a name="p1277259072084831"></a>long double </p>
<p id="p649759124084831"><a name="p649759124084831"></a><a name="p649759124084831"></a>Obtains the largest integer less than or equal to the long double value <strong id="b1061306020084831"><a name="b1061306020084831"></a><a name="b1061306020084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row809450446084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1557697596084831"><a name="p1557697596084831"></a><a name="p1557697596084831"></a><a href="math.md#gac6df7bd41d198a70da3915a80de5452d">fma</a> (double x, double y, double z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974191202084831"><a name="p1974191202084831"></a><a name="p1974191202084831"></a>double </p>
<p id="p597337071084831"><a name="p597337071084831"></a><a name="p597337071084831"></a>Calculates the value of <strong id="b101512756084831"><a name="b101512756084831"></a><a name="b101512756084831"></a>x*y+z</strong> and rounds the result up. </p>
</td>
</tr>
<tr id="row1963270366084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1190603282084831"><a name="p1190603282084831"></a><a name="p1190603282084831"></a><a href="math.md#gaa6b32a0b7f88680bb59bcfb9c6168ed2">fmaf</a> (float x, float y, float z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1571034717084831"><a name="p1571034717084831"></a><a name="p1571034717084831"></a>float </p>
<p id="p1502512909084831"><a name="p1502512909084831"></a><a name="p1502512909084831"></a>Calculates the value of <strong id="b1632276822084831"><a name="b1632276822084831"></a><a name="b1632276822084831"></a>x*y+z</strong> and rounds the result up. </p>
</td>
</tr>
<tr id="row1460471891084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291041367084831"><a name="p291041367084831"></a><a name="p291041367084831"></a><a href="math.md#gaf30b6b26252979964796ffa55dd30120">fmal</a> (long double x, long double y, long double z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2074018117084831"><a name="p2074018117084831"></a><a name="p2074018117084831"></a>long double </p>
<p id="p1201806317084831"><a name="p1201806317084831"></a><a name="p1201806317084831"></a>Calculates the value of <strong id="b1369191951084831"><a name="b1369191951084831"></a><a name="b1369191951084831"></a>x*y+z</strong> and rounds the result up. </p>
</td>
</tr>
<tr id="row1070152294084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269078614084831"><a name="p269078614084831"></a><a name="p269078614084831"></a><a href="math.md#ga35e041615ac931b4d848a7b173049301">fmax</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437509043084831"><a name="p437509043084831"></a><a name="p437509043084831"></a>double </p>
<p id="p1259405870084831"><a name="p1259405870084831"></a><a name="p1259405870084831"></a>Obtains the larger value of two double values <strong id="b1724441938084831"><a name="b1724441938084831"></a><a name="b1724441938084831"></a>x</strong> and <strong id="b1678265651084831"><a name="b1678265651084831"></a><a name="b1678265651084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row487904442084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p548889983084831"><a name="p548889983084831"></a><a name="p548889983084831"></a><a href="math.md#ga8849bfdbec18ded429fad4772cf60f4b">fmaxf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577642013084831"><a name="p577642013084831"></a><a name="p577642013084831"></a>float </p>
<p id="p1610621841084831"><a name="p1610621841084831"></a><a name="p1610621841084831"></a>Obtains the larger value of two float values <strong id="b527490522084831"><a name="b527490522084831"></a><a name="b527490522084831"></a>x</strong> and <strong id="b1603815712084831"><a name="b1603815712084831"></a><a name="b1603815712084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1245798906084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864502479084831"><a name="p1864502479084831"></a><a name="p1864502479084831"></a><a href="math.md#ga0e31e170115494fdc03b6556844232f3">fmaxl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1072791722084831"><a name="p1072791722084831"></a><a name="p1072791722084831"></a>long double </p>
<p id="p512636404084831"><a name="p512636404084831"></a><a name="p512636404084831"></a>Obtains the larger value of two long double values <strong id="b514665215084831"><a name="b514665215084831"></a><a name="b514665215084831"></a>x</strong> and <strong id="b1148885982084831"><a name="b1148885982084831"></a><a name="b1148885982084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row693558937084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935359501084831"><a name="p935359501084831"></a><a name="p935359501084831"></a><a href="math.md#gaf0a18b3ac9e461ac48b4cfffb4945a84">fmin</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1882231409084831"><a name="p1882231409084831"></a><a name="p1882231409084831"></a>double </p>
<p id="p105153850084831"><a name="p105153850084831"></a><a name="p105153850084831"></a>Obtains the smaller value of two double values <strong id="b1424341848084831"><a name="b1424341848084831"></a><a name="b1424341848084831"></a>x</strong> and <strong id="b1894863111084831"><a name="b1894863111084831"></a><a name="b1894863111084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1375871056084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p433982111084831"><a name="p433982111084831"></a><a name="p433982111084831"></a><a href="math.md#ga9b4132c27f31d39c91c3c6063f378103">fminf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p571693424084831"><a name="p571693424084831"></a><a name="p571693424084831"></a>float </p>
<p id="p467636967084831"><a name="p467636967084831"></a><a name="p467636967084831"></a>Obtains the smaller value of two float values <strong id="b526183128084831"><a name="b526183128084831"></a><a name="b526183128084831"></a>x</strong> and <strong id="b185073665084831"><a name="b185073665084831"></a><a name="b185073665084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1802702099084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40158033084831"><a name="p40158033084831"></a><a name="p40158033084831"></a><a href="math.md#ga8a301190384886aa4e327db265fb5c9f">fminl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p974814245084831"><a name="p974814245084831"></a><a name="p974814245084831"></a>long double </p>
<p id="p112314867084831"><a name="p112314867084831"></a><a name="p112314867084831"></a>Obtains the smaller value of two long double values <strong id="b901067584084831"><a name="b901067584084831"></a><a name="b901067584084831"></a>x</strong> and <strong id="b555227968084831"><a name="b555227968084831"></a><a name="b555227968084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row5564953084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p77701109084831"><a name="p77701109084831"></a><a name="p77701109084831"></a><a href="math.md#ga537296d1a8f9fb621676038b99ba7edf">fmod</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1686067998084831"><a name="p1686067998084831"></a><a name="p1686067998084831"></a>double </p>
<p id="p269563537084831"><a name="p269563537084831"></a><a name="p269563537084831"></a>Calculates the remainder of the double value <strong id="b362501850084831"><a name="b362501850084831"></a><a name="b362501850084831"></a>x</strong> divided by the double value <strong id="b479059379084831"><a name="b479059379084831"></a><a name="b479059379084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row711962076084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1880213395084831"><a name="p1880213395084831"></a><a name="p1880213395084831"></a><a href="math.md#gaf17ec425baca2b5f3882a05b5e19dfb5">fmodf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p898368327084831"><a name="p898368327084831"></a><a name="p898368327084831"></a>float </p>
<p id="p339967449084831"><a name="p339967449084831"></a><a name="p339967449084831"></a>Calculates the remainder of the float value <strong id="b1292178310084831"><a name="b1292178310084831"></a><a name="b1292178310084831"></a>x</strong> divided by the float value <strong id="b372257012084831"><a name="b372257012084831"></a><a name="b372257012084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1812374328084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1824075295084831"><a name="p1824075295084831"></a><a name="p1824075295084831"></a><a href="math.md#gaa927d9996fb40db42bd3a6cbe57da9a7">fmodl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354057384084831"><a name="p1354057384084831"></a><a name="p1354057384084831"></a>long double </p>
<p id="p599376625084831"><a name="p599376625084831"></a><a name="p599376625084831"></a>Calculates the remainder of the long double value <strong id="b1794418423084831"><a name="b1794418423084831"></a><a name="b1794418423084831"></a>x</strong> divided by the long double value <strong id="b729926239084831"><a name="b729926239084831"></a><a name="b729926239084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row373180475084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1063228428084831"><a name="p1063228428084831"></a><a name="p1063228428084831"></a><a href="math.md#gae3fa88adf02f16a693f3dccea3c42ef0">frexp</a> (double x, int *<a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857498532084831"><a name="p1857498532084831"></a><a name="p1857498532084831"></a>double </p>
<p id="p2046160116084831"><a name="p2046160116084831"></a><a name="p2046160116084831"></a>Decomposes the double value <strong id="b2014056418084831"><a name="b2014056418084831"></a><a name="b2014056418084831"></a>x</strong> into a significand and an integral exponent for 2. </p>
</td>
</tr>
<tr id="row2030431378084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218375327084831"><a name="p218375327084831"></a><a name="p218375327084831"></a><a href="math.md#ga12c36e745d8a9eb4f01c7e0eeb426dd3">frexpf</a> (float x, int *<a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540088539084831"><a name="p1540088539084831"></a><a name="p1540088539084831"></a>float </p>
<p id="p1888377718084831"><a name="p1888377718084831"></a><a name="p1888377718084831"></a>Decomposes float value <strong id="b464735660084831"><a name="b464735660084831"></a><a name="b464735660084831"></a>x</strong> into a binary significand and an integral exponent for 2. </p>
</td>
</tr>
<tr id="row34154592084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1442207116084831"><a name="p1442207116084831"></a><a name="p1442207116084831"></a><a href="math.md#ga239d50c0595ff8538b9aa3186ac4fd29">frexpl</a> (long double x, int *<a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1768100885084831"><a name="p1768100885084831"></a><a name="p1768100885084831"></a>long double </p>
<p id="p1219054124084831"><a name="p1219054124084831"></a><a name="p1219054124084831"></a>Decomposes long double value <strong id="b471430090084831"><a name="b471430090084831"></a><a name="b471430090084831"></a>x</strong> into a binary significand and an integral exponent for 2. </p>
</td>
</tr>
<tr id="row846140437084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1308926135084831"><a name="p1308926135084831"></a><a name="p1308926135084831"></a><a href="math.md#ga6d6a905f61d535f8454190433b8c0ea5">hypot</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p412958346084831"><a name="p412958346084831"></a><a name="p412958346084831"></a>double </p>
<p id="p358461075084831"><a name="p358461075084831"></a><a name="p358461075084831"></a>Calculates the hypotenuse of a right triangle whose legs are <strong id="b592893953084831"><a name="b592893953084831"></a><a name="b592893953084831"></a>x</strong> and <strong id="b420207799084831"><a name="b420207799084831"></a><a name="b420207799084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row2089894490084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1932698522084831"><a name="p1932698522084831"></a><a name="p1932698522084831"></a><a href="math.md#ga9fa4a03d7c4abfda7d9ad7b6ff7f6456">hypotf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911472274084831"><a name="p1911472274084831"></a><a name="p1911472274084831"></a>float </p>
<p id="p1614604920084831"><a name="p1614604920084831"></a><a name="p1614604920084831"></a>Calculates the hypotenuse of a right triangle whose legs are <strong id="b539223814084831"><a name="b539223814084831"></a><a name="b539223814084831"></a>x</strong> and <strong id="b1120149024084831"><a name="b1120149024084831"></a><a name="b1120149024084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row955759413084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p569293690084831"><a name="p569293690084831"></a><a name="p569293690084831"></a><a href="math.md#ga92a0e76d17c34fc1b3b2e7c0868aea6e">hypotl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1467931075084831"><a name="p1467931075084831"></a><a name="p1467931075084831"></a>long double </p>
<p id="p947724886084831"><a name="p947724886084831"></a><a name="p947724886084831"></a>Calculates the hypotenuse of a right triangle whose legs are <strong id="b978095866084831"><a name="b978095866084831"></a><a name="b978095866084831"></a>x</strong> and <strong id="b610059120084831"><a name="b610059120084831"></a><a name="b610059120084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1557006744084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702014718084831"><a name="p702014718084831"></a><a name="p702014718084831"></a><a href="math.md#ga600dd249210d15af31b9a29c2d09d255">ilogb</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376552421084831"><a name="p376552421084831"></a><a name="p376552421084831"></a>int </p>
<p id="p932238584084831"><a name="p932238584084831"></a><a name="p932238584084831"></a>Obtains the integral part of the logarithm of double value <strong id="b757893093084831"><a name="b757893093084831"></a><a name="b757893093084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1185189505084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346167461084831"><a name="p346167461084831"></a><a name="p346167461084831"></a><a href="math.md#gaf53f0f07bb80b1a38fb47773a190e7a7">ilogbf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109858747084831"><a name="p1109858747084831"></a><a name="p1109858747084831"></a>int </p>
<p id="p1065420586084831"><a name="p1065420586084831"></a><a name="p1065420586084831"></a>Obtains the integral part of the logarithm of float value <strong id="b64334595084831"><a name="b64334595084831"></a><a name="b64334595084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row999766604084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1540387061084831"><a name="p1540387061084831"></a><a name="p1540387061084831"></a><a href="math.md#gafbd166ed232a372f090b8f9fa8441423">ilogbl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1633236652084831"><a name="p1633236652084831"></a><a name="p1633236652084831"></a>int </p>
<p id="p983535163084831"><a name="p983535163084831"></a><a name="p983535163084831"></a>Obtains the integral part of the logarithm of the long double value <strong id="b77612577084831"><a name="b77612577084831"></a><a name="b77612577084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row554779795084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793492848084831"><a name="p793492848084831"></a><a name="p793492848084831"></a><a href="math.md#gab3662815756f0bd419dc1b12f4ad905d">ldexp</a> (double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414261962084831"><a name="p1414261962084831"></a><a name="p1414261962084831"></a>double </p>
<p id="p1195349303084831"><a name="p1195349303084831"></a><a name="p1195349303084831"></a>Multiplies the double value <strong id="b2123561070084831"><a name="b2123561070084831"></a><a name="b2123561070084831"></a>x</strong> by 2 raised to the power of <strong id="b1950157730084831"><a name="b1950157730084831"></a><a name="b1950157730084831"></a>exp</strong>. </p>
</td>
</tr>
<tr id="row1262459980084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1679020909084831"><a name="p1679020909084831"></a><a name="p1679020909084831"></a><a href="math.md#gaacd370a7830c29f47239dea1ea2eb7f9">ldexpf</a> (float x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p999238559084831"><a name="p999238559084831"></a><a name="p999238559084831"></a>float </p>
<p id="p1073601203084831"><a name="p1073601203084831"></a><a name="p1073601203084831"></a>Multiplies the float value <strong id="b146310710084831"><a name="b146310710084831"></a><a name="b146310710084831"></a>x</strong> by 2 raised to the power of <strong id="b1556097838084831"><a name="b1556097838084831"></a><a name="b1556097838084831"></a>exp</strong>. </p>
</td>
</tr>
<tr id="row171585342084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807364458084831"><a name="p1807364458084831"></a><a name="p1807364458084831"></a><a href="math.md#ga454187039ef790629dab1e7724c3c3b2">ldexpl</a> (long double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1215881468084831"><a name="p1215881468084831"></a><a name="p1215881468084831"></a>long double </p>
<p id="p633420817084831"><a name="p633420817084831"></a><a name="p633420817084831"></a>Multiplies the long double value <strong id="b1897498710084831"><a name="b1897498710084831"></a><a name="b1897498710084831"></a>x</strong> by 2 raised to the power of <strong id="b1774057548084831"><a name="b1774057548084831"></a><a name="b1774057548084831"></a>exp</strong>. </p>
</td>
</tr>
<tr id="row349129772084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441806348084831"><a name="p441806348084831"></a><a name="p441806348084831"></a><a href="math.md#gacd3ebe923fa039624f0b7de3320816bf">lgamma</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p462601637084831"><a name="p462601637084831"></a><a name="p462601637084831"></a>double </p>
<p id="p1847961408084831"><a name="p1847961408084831"></a><a name="p1847961408084831"></a>Calculates the natural logarithm of the absolute value of the gamma function of the double value <strong id="b471636057084831"><a name="b471636057084831"></a><a name="b471636057084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1614290023084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245512733084831"><a name="p1245512733084831"></a><a name="p1245512733084831"></a><a href="math.md#ga5900f7bf0093757f1ba36b5940b1e10b">lgammaf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667015059084831"><a name="p667015059084831"></a><a name="p667015059084831"></a>float </p>
<p id="p1114031163084831"><a name="p1114031163084831"></a><a name="p1114031163084831"></a>Calculates the natural logarithm of the absolute value of the gamma function of the float value <strong id="b1530346531084831"><a name="b1530346531084831"></a><a name="b1530346531084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row259567249084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150187158084831"><a name="p1150187158084831"></a><a name="p1150187158084831"></a><a href="math.md#ga4dafd3eb6952c8daabe8a98f4a64a7df">lgammal</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052727640084831"><a name="p1052727640084831"></a><a name="p1052727640084831"></a>long double </p>
<p id="p1954773577084831"><a name="p1954773577084831"></a><a name="p1954773577084831"></a>Calculates the natural logarithm of the absolute value of the gamma function of the long double value <strong id="b370225153084831"><a name="b370225153084831"></a><a name="b370225153084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row706321397084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p409313785084831"><a name="p409313785084831"></a><a name="p409313785084831"></a><a href="math.md#ga64a4201c82f6ee7043a270bbbc6a5e19">llrint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p636891854084831"><a name="p636891854084831"></a><a name="p636891854084831"></a>long long int </p>
<p id="p303009618084831"><a name="p303009618084831"></a><a name="p303009618084831"></a>Rounds double value <strong id="b1310201537084831"><a name="b1310201537084831"></a><a name="b1310201537084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row7669190084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434508123084831"><a name="p1434508123084831"></a><a name="p1434508123084831"></a><a href="math.md#ga33d95711621def731d3f88c4e606323e">llrintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1068131876084831"><a name="p1068131876084831"></a><a name="p1068131876084831"></a>long long int </p>
<p id="p1798544410084831"><a name="p1798544410084831"></a><a name="p1798544410084831"></a>Rounds float value <strong id="b633957466084831"><a name="b633957466084831"></a><a name="b633957466084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row512813843084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p333911159084831"><a name="p333911159084831"></a><a name="p333911159084831"></a><a href="math.md#ga20e0da115f76608eff4695177f2f605a">llrintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p7089233084831"><a name="p7089233084831"></a><a name="p7089233084831"></a>long long int </p>
<p id="p1085965596084831"><a name="p1085965596084831"></a><a name="p1085965596084831"></a>Rounds long double value <strong id="b1862991312084831"><a name="b1862991312084831"></a><a name="b1862991312084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row1834945329084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905877474084831"><a name="p1905877474084831"></a><a name="p1905877474084831"></a><a href="math.md#ga3e4957daeecea4e616ed1f1870fe4f31">llround</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698849169084831"><a name="p1698849169084831"></a><a name="p1698849169084831"></a>long long int </p>
<p id="p850221043084831"><a name="p850221043084831"></a><a name="p850221043084831"></a>Rounds double value <strong id="b852678767084831"><a name="b852678767084831"></a><a name="b852678767084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b246841116084831"><a name="b246841116084831"></a><a name="b246841116084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row619656681084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p768864054084831"><a name="p768864054084831"></a><a name="p768864054084831"></a><a href="math.md#ga8259999687e8bd4b5509ca0d69b0ad9d">llroundf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p913107955084831"><a name="p913107955084831"></a><a name="p913107955084831"></a>long long int </p>
<p id="p1648301694084831"><a name="p1648301694084831"></a><a name="p1648301694084831"></a>Rounds float value <strong id="b594972392084831"><a name="b594972392084831"></a><a name="b594972392084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b1974755491084831"><a name="b1974755491084831"></a><a name="b1974755491084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1265766894084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791578355084831"><a name="p1791578355084831"></a><a name="p1791578355084831"></a><a href="math.md#ga82a6d70a29e839514b93bb0699f07bbe">llroundl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699321019084831"><a name="p699321019084831"></a><a name="p699321019084831"></a>long long int </p>
<p id="p2050413828084831"><a name="p2050413828084831"></a><a name="p2050413828084831"></a>Rounds long double value <strong id="b576885856084831"><a name="b576885856084831"></a><a name="b576885856084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b1449961296084831"><a name="b1449961296084831"></a><a name="b1449961296084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1067280292084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p857700454084831"><a name="p857700454084831"></a><a name="p857700454084831"></a><a href="math.md#gadb302c9aafbaa5e180d9f60ee954bb82">log</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1724559577084831"><a name="p1724559577084831"></a><a name="p1724559577084831"></a>double </p>
<p id="p1160686977084831"><a name="p1160686977084831"></a><a name="p1160686977084831"></a>Calculates the natural logarithm of the double value <strong id="b1394461307084831"><a name="b1394461307084831"></a><a name="b1394461307084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2022882906084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1710063648084831"><a name="p1710063648084831"></a><a name="p1710063648084831"></a><a href="math.md#ga8246b3e17a39b137d0c62670d0c6e336">logf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993234848084831"><a name="p993234848084831"></a><a name="p993234848084831"></a>float </p>
<p id="p1716340385084831"><a name="p1716340385084831"></a><a name="p1716340385084831"></a>Calculates the natural logarithm of the float value <strong id="b1275929914084831"><a name="b1275929914084831"></a><a name="b1275929914084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1482753836084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1414513344084831"><a name="p1414513344084831"></a><a name="p1414513344084831"></a><a href="math.md#gaf67da1c28ce33b403f955103f201dfb8">logl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807290818084831"><a name="p807290818084831"></a><a name="p807290818084831"></a>long double </p>
<p id="p1793203711084831"><a name="p1793203711084831"></a><a name="p1793203711084831"></a>Calculates the natural logarithm of the long double value <strong id="b875443835084831"><a name="b875443835084831"></a><a name="b875443835084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1308005001084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p714354421084831"><a name="p714354421084831"></a><a name="p714354421084831"></a><a href="math.md#ga6572e82a4891917a9ba7fb2a964f8182">log10</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995515768084831"><a name="p1995515768084831"></a><a name="p1995515768084831"></a>double </p>
<p id="p689191488084831"><a name="p689191488084831"></a><a name="p689191488084831"></a>Calculates the common logarithm (logarithm with base 10) of the double value <strong id="b1407046380084831"><a name="b1407046380084831"></a><a name="b1407046380084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row330447167084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424920790084831"><a name="p424920790084831"></a><a name="p424920790084831"></a><a href="math.md#gae207b1eb007a6c23394dcb6fc7f16adf">log10f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p968616083084831"><a name="p968616083084831"></a><a name="p968616083084831"></a>float </p>
<p id="p1357845789084831"><a name="p1357845789084831"></a><a name="p1357845789084831"></a>Calculates the common logarithm (logarithm with base 10) of the float value <strong id="b1790126028084831"><a name="b1790126028084831"></a><a name="b1790126028084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row172512533084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1228801398084831"><a name="p1228801398084831"></a><a name="p1228801398084831"></a><a href="math.md#gae824e49a04221dcf66b9791c5df8d6b6">log10l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058342476084831"><a name="p1058342476084831"></a><a name="p1058342476084831"></a>long double </p>
<p id="p426620589084831"><a name="p426620589084831"></a><a name="p426620589084831"></a>Calculates the common logarithm (logarithm with base 10) of the long double value <strong id="b1403375798084831"><a name="b1403375798084831"></a><a name="b1403375798084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row41975840084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p745931608084831"><a name="p745931608084831"></a><a name="p745931608084831"></a><a href="math.md#gac2aac20ab1347498e6e4f209148fea84">log1p</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1231298125084831"><a name="p1231298125084831"></a><a name="p1231298125084831"></a>double </p>
<p id="p366913286084831"><a name="p366913286084831"></a><a name="p366913286084831"></a>Calculates the natural logarithm of one plus the double value <strong id="b784273082084831"><a name="b784273082084831"></a><a name="b784273082084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row520744472084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344097887084831"><a name="p344097887084831"></a><a name="p344097887084831"></a><a href="math.md#gacbf820b74779ce35a3c726a3a62bc8ef">log1pf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p708632289084831"><a name="p708632289084831"></a><a name="p708632289084831"></a>float </p>
<p id="p848631106084831"><a name="p848631106084831"></a><a name="p848631106084831"></a>Calculates the natural logarithm of one plus the float value <strong id="b2092532762084831"><a name="b2092532762084831"></a><a name="b2092532762084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row986661364084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564397021084831"><a name="p564397021084831"></a><a name="p564397021084831"></a><a href="math.md#ga2a632effaace01f30cba42725ae48dfa">log1pl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1214997815084831"><a name="p1214997815084831"></a><a name="p1214997815084831"></a>long double </p>
<p id="p1338094694084831"><a name="p1338094694084831"></a><a name="p1338094694084831"></a>Calculates the natural logarithm of one plus the long double value <strong id="b1333104317084831"><a name="b1333104317084831"></a><a name="b1333104317084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row544824622084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1668804955084831"><a name="p1668804955084831"></a><a name="p1668804955084831"></a><a href="math.md#ga38bd88274dc5594b4826fd60c8054c8e">log2</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p346147064084831"><a name="p346147064084831"></a><a name="p346147064084831"></a>double </p>
<p id="p977540561084831"><a name="p977540561084831"></a><a name="p977540561084831"></a>Calculates the binary logarithm (logarithm with base 2) of the double value <strong id="b1426267562084831"><a name="b1426267562084831"></a><a name="b1426267562084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1789050091084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642256502084831"><a name="p642256502084831"></a><a name="p642256502084831"></a><a href="math.md#ga79fe62234001b88317245f7599158aaf">log2f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p613160870084831"><a name="p613160870084831"></a><a name="p613160870084831"></a>float </p>
<p id="p1764771828084831"><a name="p1764771828084831"></a><a name="p1764771828084831"></a>Calculates the binary logarithm (logarithm with base 2) of the float value <strong id="b1821192375084831"><a name="b1821192375084831"></a><a name="b1821192375084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row867151604084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p499444282084831"><a name="p499444282084831"></a><a name="p499444282084831"></a><a href="math.md#gaa383ae0cab6c24f1bcba661dee0fbd70">log2l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p195635565084831"><a name="p195635565084831"></a><a name="p195635565084831"></a>long double </p>
<p id="p763387046084831"><a name="p763387046084831"></a><a name="p763387046084831"></a>Calculates the binary logarithm (logarithm with base 2) of the long double value <strong id="b1417839337084831"><a name="b1417839337084831"></a><a name="b1417839337084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row652544720084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088938111084831"><a name="p2088938111084831"></a><a name="p2088938111084831"></a><a href="math.md#gaa34bf5be5c3dab058c532adc2792113c">logb</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728514249084831"><a name="p728514249084831"></a><a name="p728514249084831"></a>double </p>
<p id="p590230693084831"><a name="p590230693084831"></a><a name="p590230693084831"></a>Calculates the logarithm of the absolute value of the double value <strong id="b440114660084831"><a name="b440114660084831"></a><a name="b440114660084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row497999566084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1989483077084831"><a name="p1989483077084831"></a><a name="p1989483077084831"></a><a href="math.md#ga6939b8381c2f160d26913646ca7ab6c4">logbf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p464063466084831"><a name="p464063466084831"></a><a name="p464063466084831"></a>float </p>
<p id="p1011872308084831"><a name="p1011872308084831"></a><a name="p1011872308084831"></a>Calculates the logarithm of the absolute value of the float value <strong id="b2091405171084831"><a name="b2091405171084831"></a><a name="b2091405171084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row356762954084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762802338084831"><a name="p1762802338084831"></a><a name="p1762802338084831"></a><a href="math.md#ga2f9c0448126d1a838624e3460217bb84">logbl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733310620084831"><a name="p1733310620084831"></a><a name="p1733310620084831"></a>long double </p>
<p id="p1956159244084831"><a name="p1956159244084831"></a><a name="p1956159244084831"></a>Calculates the logarithm of the absolute value of the long double value <strong id="b1471519053084831"><a name="b1471519053084831"></a><a name="b1471519053084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1386247188084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327972495084831"><a name="p1327972495084831"></a><a name="p1327972495084831"></a><a href="math.md#ga3337db086394bad101bd8d42d891640a">lrint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1048904727084831"><a name="p1048904727084831"></a><a name="p1048904727084831"></a>long int </p>
<p id="p1503410920084831"><a name="p1503410920084831"></a><a name="p1503410920084831"></a>Rounds the double value <strong id="b1005766207084831"><a name="b1005766207084831"></a><a name="b1005766207084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row550013186084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1929183347084831"><a name="p1929183347084831"></a><a name="p1929183347084831"></a><a href="math.md#ga16173bca19eef93d0230bfb7c86b5740">lrintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543629951084831"><a name="p1543629951084831"></a><a name="p1543629951084831"></a>long int </p>
<p id="p639559741084831"><a name="p639559741084831"></a><a name="p639559741084831"></a>Rounds the float value <strong id="b1110876174084831"><a name="b1110876174084831"></a><a name="b1110876174084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row1335855660084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1427670861084831"><a name="p1427670861084831"></a><a name="p1427670861084831"></a><a href="math.md#gac6d217e9b96a145f5eeb2a490e6496e6">lrintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p831263030084831"><a name="p831263030084831"></a><a name="p831263030084831"></a>long int </p>
<p id="p316764887084831"><a name="p316764887084831"></a><a name="p316764887084831"></a>Rounds the long double value <strong id="b1983167401084831"><a name="b1983167401084831"></a><a name="b1983167401084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row1886303230084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p537852612084831"><a name="p537852612084831"></a><a name="p537852612084831"></a><a href="math.md#ga5936ef27aa03815e9c17d557e87a33d7">lround</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1359267393084831"><a name="p1359267393084831"></a><a name="p1359267393084831"></a>long int </p>
<p id="p736715557084831"><a name="p736715557084831"></a><a name="p736715557084831"></a>Rounds double value <strong id="b1675049007084831"><a name="b1675049007084831"></a><a name="b1675049007084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b1248209259084831"><a name="b1248209259084831"></a><a name="b1248209259084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1972157797084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1291960427084831"><a name="p1291960427084831"></a><a name="p1291960427084831"></a><a href="math.md#ga0136619b503ddb8ce1a226cd34c9538c">lroundf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1684843212084831"><a name="p1684843212084831"></a><a name="p1684843212084831"></a>long int </p>
<p id="p1411695527084831"><a name="p1411695527084831"></a><a name="p1411695527084831"></a>Rounds the float value <strong id="b610416726084831"><a name="b610416726084831"></a><a name="b610416726084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b1735306191084831"><a name="b1735306191084831"></a><a name="b1735306191084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row2129722047084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1649995892084831"><a name="p1649995892084831"></a><a name="p1649995892084831"></a><a href="math.md#gafa865c5b70c9311f0f8701a1af60c715">lroundl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p575095082084831"><a name="p575095082084831"></a><a name="p575095082084831"></a>long int </p>
<p id="p919658866084831"><a name="p919658866084831"></a><a name="p919658866084831"></a>Rounds the long double value <strong id="b1788068914084831"><a name="b1788068914084831"></a><a name="b1788068914084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b1327175696084831"><a name="b1327175696084831"></a><a name="b1327175696084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1596133282084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p475684873084831"><a name="p475684873084831"></a><a name="p475684873084831"></a><a href="math.md#gafcfe25b77e975450988866fea9d3c9f0">modf</a> (double x, double *iptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p563424584084831"><a name="p563424584084831"></a><a name="p563424584084831"></a>double </p>
<p id="p141312432084831"><a name="p141312432084831"></a><a name="p141312432084831"></a>Breaks the double value <strong id="b404224811084831"><a name="b404224811084831"></a><a name="b404224811084831"></a>x</strong> into a signed integral and a fractional part. </p>
</td>
</tr>
<tr id="row659615193084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1586462655084831"><a name="p1586462655084831"></a><a name="p1586462655084831"></a><a href="math.md#gad8314f66dfe8603f3a166eb466261ce1">modff</a> (float x, float *iptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p230342168084831"><a name="p230342168084831"></a><a name="p230342168084831"></a>float </p>
<p id="p1194381526084831"><a name="p1194381526084831"></a><a name="p1194381526084831"></a>Breaks the float value <strong id="b1825231405084831"><a name="b1825231405084831"></a><a name="b1825231405084831"></a>x</strong> into a signed integral and a fractional part. </p>
</td>
</tr>
<tr id="row1272118788084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1215798029084831"><a name="p1215798029084831"></a><a name="p1215798029084831"></a><a href="math.md#gabacf3b74f8d7e30a70da8ae47c8e4e3e">modfl</a> (long double x, long double *iptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141321588084831"><a name="p2141321588084831"></a><a name="p2141321588084831"></a>long double </p>
<p id="p2026659862084831"><a name="p2026659862084831"></a><a name="p2026659862084831"></a>Breaks the long double value <strong id="b976295221084831"><a name="b976295221084831"></a><a name="b976295221084831"></a>x</strong> into a signed integral and a fractional part. </p>
</td>
</tr>
<tr id="row1104478656084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984975811084831"><a name="p984975811084831"></a><a name="p984975811084831"></a><a href="math.md#gaa4ee2f416f261bbd71cda3193c4884c9">nan</a> (const char *tagp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350233502084831"><a name="p1350233502084831"></a><a name="p1350233502084831"></a>double </p>
<p id="p1801982590084831"><a name="p1801982590084831"></a><a name="p1801982590084831"></a>Obtains a quiet NaN value of the double type. </p>
</td>
</tr>
<tr id="row549849178084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725423995084831"><a name="p1725423995084831"></a><a name="p1725423995084831"></a><a href="math.md#ga7fe43d4c86419daea2c133e8c5c1a17d">nanf</a> (const char *tagp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p188960392084831"><a name="p188960392084831"></a><a name="p188960392084831"></a>float </p>
<p id="p66677327084831"><a name="p66677327084831"></a><a name="p66677327084831"></a>Obtains a quiet NaN value of the float type. </p>
</td>
</tr>
<tr id="row387395304084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p863306762084831"><a name="p863306762084831"></a><a name="p863306762084831"></a><a href="math.md#gac92b1a3a1073a630ae0b7084e596d40f">nanl</a> (const char *tagp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1157788630084831"><a name="p1157788630084831"></a><a name="p1157788630084831"></a>long double </p>
<p id="p1136104573084831"><a name="p1136104573084831"></a><a name="p1136104573084831"></a>Obtains a quiet NaN value of the long double type. </p>
</td>
</tr>
<tr id="row635425530084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2117071382084831"><a name="p2117071382084831"></a><a name="p2117071382084831"></a><a href="math.md#ga61ba6b3078ccbd5aac518e6ca2a757bd">nearbyint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856520579084831"><a name="p856520579084831"></a><a name="p856520579084831"></a>double </p>
<p id="p358575858084831"><a name="p358575858084831"></a><a name="p358575858084831"></a>Rounds the double value <strong id="b827627240084831"><a name="b827627240084831"></a><a name="b827627240084831"></a>x</strong> to an integer in floating-point format. </p>
</td>
</tr>
<tr id="row1095930224084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1686990073084831"><a name="p1686990073084831"></a><a name="p1686990073084831"></a><a href="math.md#gab3be3fdcb83a6d7cbd10aa5d891f88bf">nearbyintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427789866084831"><a name="p427789866084831"></a><a name="p427789866084831"></a>float </p>
<p id="p1510774769084831"><a name="p1510774769084831"></a><a name="p1510774769084831"></a>Rounds the float value <strong id="b1417178895084831"><a name="b1417178895084831"></a><a name="b1417178895084831"></a>x</strong> to an integer in floating-point format. </p>
</td>
</tr>
<tr id="row460789823084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1506226354084831"><a name="p1506226354084831"></a><a name="p1506226354084831"></a><a href="math.md#ga4b51faf338f7d4f31224d0c096a8859b">nearbyintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323598270084831"><a name="p1323598270084831"></a><a name="p1323598270084831"></a>long double </p>
<p id="p819509429084831"><a name="p819509429084831"></a><a name="p819509429084831"></a>Rounds the long double value <strong id="b69872704084831"><a name="b69872704084831"></a><a name="b69872704084831"></a>x</strong> to an integer in floating-point format. </p>
</td>
</tr>
<tr id="row766991617084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2031197552084831"><a name="p2031197552084831"></a><a name="p2031197552084831"></a><a href="math.md#gabed1b7ee913471448c2dbe58dff28db3">nextafter</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080354942084831"><a name="p1080354942084831"></a><a name="p1080354942084831"></a>double </p>
<p id="p1083893571084831"><a name="p1083893571084831"></a><a name="p1083893571084831"></a>Obtains the next representable value following the double value <strong id="b1020169472084831"><a name="b1020169472084831"></a><a name="b1020169472084831"></a>x</strong> in the direction of the double value <strong id="b1295107465084831"><a name="b1295107465084831"></a><a name="b1295107465084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row684462216084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p294292898084831"><a name="p294292898084831"></a><a name="p294292898084831"></a><a href="math.md#ga57d2446286a54227595950a2118b349b">nextafterf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p529217264084831"><a name="p529217264084831"></a><a name="p529217264084831"></a>float </p>
<p id="p1815218838084831"><a name="p1815218838084831"></a><a name="p1815218838084831"></a>Obtains the next representable value following the float value <strong id="b1948797812084831"><a name="b1948797812084831"></a><a name="b1948797812084831"></a>x</strong> in the direction of the float value <strong id="b1026343250084831"><a name="b1026343250084831"></a><a name="b1026343250084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row559779687084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997980029084831"><a name="p997980029084831"></a><a name="p997980029084831"></a><a href="math.md#ga38691f2f734e77206e4336cdcddd0e5b">nextafterl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432492291084831"><a name="p1432492291084831"></a><a name="p1432492291084831"></a>long double </p>
<p id="p1449840550084831"><a name="p1449840550084831"></a><a name="p1449840550084831"></a>Obtains the next representable value following the long double value <strong id="b224794578084831"><a name="b224794578084831"></a><a name="b224794578084831"></a>x</strong> in the direction of the long double value <strong id="b1528577778084831"><a name="b1528577778084831"></a><a name="b1528577778084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1498275920084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1310611400084831"><a name="p1310611400084831"></a><a name="p1310611400084831"></a><a href="math.md#gaeb7afe6d08d8daec35aa282c63d7647e">nexttoward</a> (double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p32044776084831"><a name="p32044776084831"></a><a name="p32044776084831"></a>double </p>
<p id="p1486867418084831"><a name="p1486867418084831"></a><a name="p1486867418084831"></a>Obtains the next representable value following the double value <strong id="b1118980095084831"><a name="b1118980095084831"></a><a name="b1118980095084831"></a>x</strong> in the direction of the long double value <strong id="b381771621084831"><a name="b381771621084831"></a><a name="b381771621084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1591496846084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1740438114084831"><a name="p1740438114084831"></a><a name="p1740438114084831"></a><a href="math.md#ga634a1dabb08aa5a4fa6897920eff3c1d">nexttowardf</a> (float x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p592262056084831"><a name="p592262056084831"></a><a name="p592262056084831"></a>float </p>
<p id="p1648253504084831"><a name="p1648253504084831"></a><a name="p1648253504084831"></a>Obtains the next representable value following the float value <strong id="b1617279741084831"><a name="b1617279741084831"></a><a name="b1617279741084831"></a>x</strong> in the direction of the long double value <strong id="b1072050857084831"><a name="b1072050857084831"></a><a name="b1072050857084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row123557404084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p900361727084831"><a name="p900361727084831"></a><a name="p900361727084831"></a><a href="math.md#ga3930cfe4df009d7221db329b910d6e30">nexttowardl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501176860084831"><a name="p1501176860084831"></a><a name="p1501176860084831"></a>long double </p>
<p id="p1130650955084831"><a name="p1130650955084831"></a><a name="p1130650955084831"></a>Obtains the next representable value following the long double value <strong id="b313542998084831"><a name="b313542998084831"></a><a name="b313542998084831"></a>x</strong> in the direction of the long double value <strong id="b327090845084831"><a name="b327090845084831"></a><a name="b327090845084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row507769789084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1592232716084831"><a name="p1592232716084831"></a><a name="p1592232716084831"></a><a href="math.md#gaa56c9494c95edf68386375e97d64159b">pow</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995795247084831"><a name="p1995795247084831"></a><a name="p1995795247084831"></a>double </p>
<p id="p893590638084831"><a name="p893590638084831"></a><a name="p893590638084831"></a>Obtains the double value <strong id="b623476650084831"><a name="b623476650084831"></a><a name="b623476650084831"></a>x</strong> raised to the power of the double value <strong id="b2142771046084831"><a name="b2142771046084831"></a><a name="b2142771046084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1379928480084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1801511745084831"><a name="p1801511745084831"></a><a name="p1801511745084831"></a><a href="math.md#gac6b287549be087f6f0bf03b6fe30499e">powf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p360893901084831"><a name="p360893901084831"></a><a name="p360893901084831"></a>float </p>
<p id="p1893864886084831"><a name="p1893864886084831"></a><a name="p1893864886084831"></a>Obtains the float value <strong id="b791847606084831"><a name="b791847606084831"></a><a name="b791847606084831"></a>x</strong> raised to the power of the float value <strong id="b407506860084831"><a name="b407506860084831"></a><a name="b407506860084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1024204529084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1861738765084831"><a name="p1861738765084831"></a><a name="p1861738765084831"></a><a href="math.md#gab6a77d7e1f713b898ceb3b945a2420b5">powf10</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657244188084831"><a name="p1657244188084831"></a><a name="p1657244188084831"></a>float </p>
<p id="p204397904084831"><a name="p204397904084831"></a><a name="p204397904084831"></a>Calculates the xth power of 10. </p>
</td>
</tr>
<tr id="row158903453084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p423076048084831"><a name="p423076048084831"></a><a name="p423076048084831"></a><a href="math.md#ga2f4830e468138e1513b55ca6a92a0f9a">powl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566488817084831"><a name="p1566488817084831"></a><a name="p1566488817084831"></a>long double </p>
<p id="p68078539084831"><a name="p68078539084831"></a><a name="p68078539084831"></a>Obtains the long double value <strong id="b1825656906084831"><a name="b1825656906084831"></a><a name="b1825656906084831"></a>x</strong> raised to the power of the long double value <strong id="b898585525084831"><a name="b898585525084831"></a><a name="b898585525084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row937606956084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2075435441084831"><a name="p2075435441084831"></a><a name="p2075435441084831"></a><a href="math.md#ga532525cfd5b2a8ce221f1b13a7009376">powl10</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902329998084831"><a name="p1902329998084831"></a><a name="p1902329998084831"></a>long double </p>
<p id="p1063609342084831"><a name="p1063609342084831"></a><a name="p1063609342084831"></a>Calculates the xth power of 10. </p>
</td>
</tr>
<tr id="row295253810084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872458409084831"><a name="p1872458409084831"></a><a name="p1872458409084831"></a><a href="math.md#gaf7df01c4a9038dbf3562b41bc8c3be03">remainder</a> (double x, double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867110819084831"><a name="p867110819084831"></a><a name="p867110819084831"></a>double </p>
<p id="p1552083059084831"><a name="p1552083059084831"></a><a name="p1552083059084831"></a>Calculates the remainder of the double value <strong id="b928107136084831"><a name="b928107136084831"></a><a name="b928107136084831"></a>x</strong> divided by the double value <strong id="b1334674679084831"><a name="b1334674679084831"></a><a name="b1334674679084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1746249609084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927183965084831"><a name="p927183965084831"></a><a name="p927183965084831"></a><a href="math.md#ga370ff5cfa842822bfd8ea0a93d441a33">remainderf</a> (float x, float y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p750552523084831"><a name="p750552523084831"></a><a name="p750552523084831"></a>float </p>
<p id="p552650438084831"><a name="p552650438084831"></a><a name="p552650438084831"></a>Calculates the remainder of the float value <strong id="b456371690084831"><a name="b456371690084831"></a><a name="b456371690084831"></a>x</strong> divided by the float value <strong id="b82100823084831"><a name="b82100823084831"></a><a name="b82100823084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row625391954084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1984107130084831"><a name="p1984107130084831"></a><a name="p1984107130084831"></a><a href="math.md#gabadbe61e166bbf3031b979661f0e8336">remainderl</a> (long double x, long double y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p506457717084831"><a name="p506457717084831"></a><a name="p506457717084831"></a>long double </p>
<p id="p1485663527084831"><a name="p1485663527084831"></a><a name="p1485663527084831"></a>Calculates the remainder of the long double value <strong id="b922377587084831"><a name="b922377587084831"></a><a name="b922377587084831"></a>x</strong> divided by the long double value <strong id="b573933811084831"><a name="b573933811084831"></a><a name="b573933811084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1215233261084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p39243666084831"><a name="p39243666084831"></a><a name="p39243666084831"></a><a href="math.md#gac836dc6a979229173eb3d6e2744d82de">remquo</a> (double x, double y, int *quo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1791831725084831"><a name="p1791831725084831"></a><a name="p1791831725084831"></a>double </p>
<p id="p2032106204084831"><a name="p2032106204084831"></a><a name="p2032106204084831"></a>Calculates the quotient and remainder of the double value <strong id="b953505064084831"><a name="b953505064084831"></a><a name="b953505064084831"></a>x</strong> divided by the double value <strong id="b2143176224084831"><a name="b2143176224084831"></a><a name="b2143176224084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row896143789084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1423175409084831"><a name="p1423175409084831"></a><a name="p1423175409084831"></a><a href="math.md#ga15ec704e1894cfa573ac37a65afe009a">remquof</a> (float x, float y, int *quo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289588877084831"><a name="p289588877084831"></a><a name="p289588877084831"></a>float </p>
<p id="p1143643213084831"><a name="p1143643213084831"></a><a name="p1143643213084831"></a>Calculates the quotient and remainder of the float value <strong id="b49412205084831"><a name="b49412205084831"></a><a name="b49412205084831"></a>x</strong> divided by the float value <strong id="b43892291084831"><a name="b43892291084831"></a><a name="b43892291084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1582826913084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780296237084831"><a name="p780296237084831"></a><a name="p780296237084831"></a><a href="math.md#gaacadcc57a95279058f29e657dce4d285">remquol</a> (long double x, long double y, int *quo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1204948649084831"><a name="p1204948649084831"></a><a name="p1204948649084831"></a>long double </p>
<p id="p708630347084831"><a name="p708630347084831"></a><a name="p708630347084831"></a>Calculates the quotient and remainder of the long double value <strong id="b1483263449084831"><a name="b1483263449084831"></a><a name="b1483263449084831"></a>x</strong> divided by the long double value <strong id="b1514015967084831"><a name="b1514015967084831"></a><a name="b1514015967084831"></a>y</strong>. </p>
</td>
</tr>
<tr id="row1483121938084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p107232263084831"><a name="p107232263084831"></a><a name="p107232263084831"></a><a href="math.md#gae1f9edd5049d3ff63b0373a3c15c38c1">rint</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366079014084831"><a name="p366079014084831"></a><a name="p366079014084831"></a>double </p>
<p id="p2052791398084831"><a name="p2052791398084831"></a><a name="p2052791398084831"></a>Rounds the double value <strong id="b1815565417084831"><a name="b1815565417084831"></a><a name="b1815565417084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row1419803702084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p947418111084831"><a name="p947418111084831"></a><a name="p947418111084831"></a><a href="math.md#ga48f9341b9310fefa5dd1b0c8c84c99df">rintf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p312073751084831"><a name="p312073751084831"></a><a name="p312073751084831"></a>float </p>
<p id="p221274597084831"><a name="p221274597084831"></a><a name="p221274597084831"></a>Rounds the float value <strong id="b1791266283084831"><a name="b1791266283084831"></a><a name="b1791266283084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row1921575912084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032401411084831"><a name="p2032401411084831"></a><a name="p2032401411084831"></a><a href="math.md#gaedc37bf10d69d2efa2a478f5f5d4b26b">rintl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1463005655084831"><a name="p1463005655084831"></a><a name="p1463005655084831"></a>long double </p>
<p id="p253210469084831"><a name="p253210469084831"></a><a name="p253210469084831"></a>Rounds the long double value <strong id="b426635814084831"><a name="b426635814084831"></a><a name="b426635814084831"></a>x</strong> to the nearest integer. </p>
</td>
</tr>
<tr id="row737893396084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p389849288084831"><a name="p389849288084831"></a><a name="p389849288084831"></a><a href="math.md#ga7df19cf730447c00150569250a4b5e1d">round</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1072923291084831"><a name="p1072923291084831"></a><a name="p1072923291084831"></a>double </p>
<p id="p857334061084831"><a name="p857334061084831"></a><a name="p857334061084831"></a>Rounds the double value <strong id="b2091491346084831"><a name="b2091491346084831"></a><a name="b2091491346084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b665899932084831"><a name="b665899932084831"></a><a name="b665899932084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row243076493084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2071908949084831"><a name="p2071908949084831"></a><a name="p2071908949084831"></a><a href="math.md#gade09185c0cf8101fa9e2f25c15041b81">roundf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056547789084831"><a name="p1056547789084831"></a><a name="p1056547789084831"></a>float </p>
<p id="p368232369084831"><a name="p368232369084831"></a><a name="p368232369084831"></a>Rounds the float value <strong id="b1230517767084831"><a name="b1230517767084831"></a><a name="b1230517767084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b475448853084831"><a name="b475448853084831"></a><a name="b475448853084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1944038227084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2090635124084831"><a name="p2090635124084831"></a><a name="p2090635124084831"></a><a href="math.md#ga6565127c023ae8f392ce69e3b3f30aa1">roundl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588252493084831"><a name="p1588252493084831"></a><a name="p1588252493084831"></a>long double </p>
<p id="p1955182702084831"><a name="p1955182702084831"></a><a name="p1955182702084831"></a>Rounds the long double value <strong id="b921340125084831"><a name="b921340125084831"></a><a name="b921340125084831"></a>x</strong> to the nearest integer, rounding away from <strong id="b758844040084831"><a name="b758844040084831"></a><a name="b758844040084831"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1787506200084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115579816084831"><a name="p2115579816084831"></a><a name="p2115579816084831"></a><a href="math.md#ga947d3d0739c0dc7c46d1eec778d4b6af">scalbln</a> (double x, long int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p125824835084831"><a name="p125824835084831"></a><a name="p125824835084831"></a>double </p>
<p id="p1873829980084831"><a name="p1873829980084831"></a><a name="p1873829980084831"></a>Multiplies the double value <strong id="b1170538674084831"><a name="b1170538674084831"></a><a name="b1170538674084831"></a>x</strong> by <strong id="b1157043766084831"><a name="b1157043766084831"></a><a name="b1157043766084831"></a>FLT_RADIX</strong> raised to the power of the long int value <strong id="b886915203084831"><a name="b886915203084831"></a><a name="b886915203084831"></a>exp</strong>, that is, <strong id="b1405752390084831"><a name="b1405752390084831"></a><a name="b1405752390084831"></a>x*(<strong id="b2020293427084831"><a name="b2020293427084831"></a><a name="b2020293427084831"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row413775426084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101216655084831"><a name="p1101216655084831"></a><a name="p1101216655084831"></a><a href="math.md#ga1aa3cc34e8f84a2a09400c25c578100d">scalblnf</a> (float x, long int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201475515084831"><a name="p1201475515084831"></a><a name="p1201475515084831"></a>float </p>
<p id="p1993361396084831"><a name="p1993361396084831"></a><a name="p1993361396084831"></a>Multiplies the float value <strong id="b2053220534084831"><a name="b2053220534084831"></a><a name="b2053220534084831"></a>x</strong> by <strong id="b234348090084831"><a name="b234348090084831"></a><a name="b234348090084831"></a>FLT_RADIX</strong> raised to the power of the long int value <strong id="b1443602521084831"><a name="b1443602521084831"></a><a name="b1443602521084831"></a>exp</strong>, that is, <strong id="b2036509534084831"><a name="b2036509534084831"></a><a name="b2036509534084831"></a>x*(<strong id="b1650172513084831"><a name="b1650172513084831"></a><a name="b1650172513084831"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row215337270084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140663660084831"><a name="p1140663660084831"></a><a name="p1140663660084831"></a><a href="math.md#gaeb098df94536b520ced9df59fd353848">scalblnl</a> (long double x, long int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p843736878084831"><a name="p843736878084831"></a><a name="p843736878084831"></a>long double </p>
<p id="p2002996954084831"><a name="p2002996954084831"></a><a name="p2002996954084831"></a>Multiplies the long double value <strong id="b1604695800084831"><a name="b1604695800084831"></a><a name="b1604695800084831"></a>x</strong> by <strong id="b1689844138084831"><a name="b1689844138084831"></a><a name="b1689844138084831"></a>FLT_RADIX</strong> raised to the power of the long int value <strong id="b1062884998084831"><a name="b1062884998084831"></a><a name="b1062884998084831"></a>exp</strong>, that is, <strong id="b1443628114084831"><a name="b1443628114084831"></a><a name="b1443628114084831"></a>x*(<strong id="b1125157761084831"><a name="b1125157761084831"></a><a name="b1125157761084831"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row1701918073084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p371139396084831"><a name="p371139396084831"></a><a name="p371139396084831"></a><a href="math.md#gaa2fbea1fca1faaebedf2deec71c47189">scalbn</a> (double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787234254084831"><a name="p1787234254084831"></a><a name="p1787234254084831"></a>double </p>
<p id="p761120758084831"><a name="p761120758084831"></a><a name="p761120758084831"></a>Multiplies the double value <strong id="b512045479084831"><a name="b512045479084831"></a><a name="b512045479084831"></a>x</strong> by <strong id="b1625040553084831"><a name="b1625040553084831"></a><a name="b1625040553084831"></a>FLT_RADIX</strong> raised to the power of the int value <strong id="b473773835084831"><a name="b473773835084831"></a><a name="b473773835084831"></a>exp</strong>, that is, <strong id="b781838835084831"><a name="b781838835084831"></a><a name="b781838835084831"></a>x*(<strong id="b1805007257084831"><a name="b1805007257084831"></a><a name="b1805007257084831"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row371036544084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1257533858084831"><a name="p1257533858084831"></a><a name="p1257533858084831"></a><a href="math.md#ga3849b86bb2f39ebccb79b91745f7883f">scalbnf</a> (float x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1448376770084831"><a name="p1448376770084831"></a><a name="p1448376770084831"></a>float </p>
<p id="p1776881064084831"><a name="p1776881064084831"></a><a name="p1776881064084831"></a>Multiplies the float value <strong id="b41374087084831"><a name="b41374087084831"></a><a name="b41374087084831"></a>x</strong> by <strong id="b678160207084831"><a name="b678160207084831"></a><a name="b678160207084831"></a>FLT_RADIX</strong> raised to the power of the int value <strong id="b527844026084831"><a name="b527844026084831"></a><a name="b527844026084831"></a>exp</strong>, that is, <strong id="b251307439084831"><a name="b251307439084831"></a><a name="b251307439084831"></a>x*(<strong id="b1333019157084831"><a name="b1333019157084831"></a><a name="b1333019157084831"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row913783976084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p227679622084831"><a name="p227679622084831"></a><a name="p227679622084831"></a><a href="math.md#ga284717e9eceed5bc33389ce33170f907">scalbnl</a> (long double x, int <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1119477800084831"><a name="p1119477800084831"></a><a name="p1119477800084831"></a>long double </p>
<p id="p882486064084831"><a name="p882486064084831"></a><a name="p882486064084831"></a>Multiplies the long double value <strong id="b1927678325084831"><a name="b1927678325084831"></a><a name="b1927678325084831"></a>x</strong> by <strong id="b1172831140084831"><a name="b1172831140084831"></a><a name="b1172831140084831"></a>FLT_RADIX</strong> raised to the power of the int value <strong id="b822375548084831"><a name="b822375548084831"></a><a name="b822375548084831"></a>exp</strong>, that is, <strong id="b1615067746084831"><a name="b1615067746084831"></a><a name="b1615067746084831"></a>x*(<strong id="b491036020084831"><a name="b491036020084831"></a><a name="b491036020084831"></a>FLT_RADIX</strong>)^exp</strong>. </p>
</td>
</tr>
<tr id="row122796228084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p57383447084831"><a name="p57383447084831"></a><a name="p57383447084831"></a><a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909466872084831"><a name="p909466872084831"></a><a name="p909466872084831"></a>double </p>
<p id="p2114048121084831"><a name="p2114048121084831"></a><a name="p2114048121084831"></a>Calculates the sine of the double value <strong id="b1049727694084831"><a name="b1049727694084831"></a><a name="b1049727694084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row587102359084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1609173320084831"><a name="p1609173320084831"></a><a name="p1609173320084831"></a><a href="math.md#ga8a7dc2a88e109f4e15b661247665709a">sinf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p358354479084831"><a name="p358354479084831"></a><a name="p358354479084831"></a>float </p>
<p id="p416722884084831"><a name="p416722884084831"></a><a name="p416722884084831"></a>Calculates the sine of the float value <strong id="b1844041253084831"><a name="b1844041253084831"></a><a name="b1844041253084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1114896389084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p417550077084831"><a name="p417550077084831"></a><a name="p417550077084831"></a><a href="math.md#gaeb537bfea71fa91192234a666f3a6a25">sinl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1051629178084831"><a name="p1051629178084831"></a><a name="p1051629178084831"></a>long double </p>
<p id="p1719865186084831"><a name="p1719865186084831"></a><a name="p1719865186084831"></a>Calculates the sine of the long double value <strong id="b1324351415084831"><a name="b1324351415084831"></a><a name="b1324351415084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1639065764084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713958965084831"><a name="p1713958965084831"></a><a name="p1713958965084831"></a><a href="math.md#ga862012e970c977c482507064e2793b45">sinh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1439652803084831"><a name="p1439652803084831"></a><a name="p1439652803084831"></a>double </p>
<p id="p91188371084831"><a name="p91188371084831"></a><a name="p91188371084831"></a>Calculates the hyperbolic sine of the double value <strong id="b363905598084831"><a name="b363905598084831"></a><a name="b363905598084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row866240775084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2086493524084831"><a name="p2086493524084831"></a><a name="p2086493524084831"></a><a href="math.md#ga1976c7577fb97800f4b926bd042b64ac">sinhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1755261975084831"><a name="p1755261975084831"></a><a name="p1755261975084831"></a>float </p>
<p id="p5702640084831"><a name="p5702640084831"></a><a name="p5702640084831"></a>Calculates the hyperbolic sine of the float value <strong id="b1887404390084831"><a name="b1887404390084831"></a><a name="b1887404390084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row586396769084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183311237084831"><a name="p183311237084831"></a><a name="p183311237084831"></a><a href="math.md#gad160d5d1bb3f113e96135a4bebe76abe">sinhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2045811442084831"><a name="p2045811442084831"></a><a name="p2045811442084831"></a>long double </p>
<p id="p16356998084831"><a name="p16356998084831"></a><a name="p16356998084831"></a>Calculates the hyperbolic sine of the long double value <strong id="b2137153588084831"><a name="b2137153588084831"></a><a name="b2137153588084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row2057099659084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737311129084831"><a name="p737311129084831"></a><a name="p737311129084831"></a><a href="math.md#gab87521a75ef827a85807f89a6c10629a">sqrt</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481996115084831"><a name="p1481996115084831"></a><a name="p1481996115084831"></a>double </p>
<p id="p1818637765084831"><a name="p1818637765084831"></a><a name="p1818637765084831"></a>Calculates the square root of double value <strong id="b2034453915084831"><a name="b2034453915084831"></a><a name="b2034453915084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row391848950084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1574363328084831"><a name="p1574363328084831"></a><a name="p1574363328084831"></a><a href="math.md#ga46c9a8d40cde7c4d5ab40a67e55316bb">sqrtf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1156919126084831"><a name="p1156919126084831"></a><a name="p1156919126084831"></a>float </p>
<p id="p850213415084831"><a name="p850213415084831"></a><a name="p850213415084831"></a>Calculates the square root of the float value <strong id="b631201859084831"><a name="b631201859084831"></a><a name="b631201859084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1314542044084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1478027882084831"><a name="p1478027882084831"></a><a name="p1478027882084831"></a><a href="math.md#ga9c028a87917b3bb9bba9e75f66cdbd43">sqrtl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p292104115084831"><a name="p292104115084831"></a><a name="p292104115084831"></a>long double </p>
<p id="p561507761084831"><a name="p561507761084831"></a><a name="p561507761084831"></a>Calculates the square root of the long double value <strong id="b297518035084831"><a name="b297518035084831"></a><a name="b297518035084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row742155116084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p596708847084831"><a name="p596708847084831"></a><a name="p596708847084831"></a><a href="math.md#gaa48fdfd5eea5f4f9c33496402b9e4039">tan</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801587134084831"><a name="p801587134084831"></a><a name="p801587134084831"></a>double </p>
<p id="p1828253123084831"><a name="p1828253123084831"></a><a name="p1828253123084831"></a>Calculates the tangent of the double value <strong id="b1918055140084831"><a name="b1918055140084831"></a><a name="b1918055140084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row424342309084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261962962084831"><a name="p261962962084831"></a><a name="p261962962084831"></a><a href="math.md#ga67d5bfe80effce6adebf5fcbc5a7dae0">tanf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p984430727084831"><a name="p984430727084831"></a><a name="p984430727084831"></a>float </p>
<p id="p745414110084831"><a name="p745414110084831"></a><a name="p745414110084831"></a>Calculates the tangent of the float value <strong id="b1021123417084831"><a name="b1021123417084831"></a><a name="b1021123417084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row550726539084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998658553084831"><a name="p1998658553084831"></a><a name="p1998658553084831"></a><a href="math.md#ga2151fba6c1e9b4fa5d2af2dcb5c68b17">tanl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p560989146084831"><a name="p560989146084831"></a><a name="p560989146084831"></a>long double </p>
<p id="p500067564084831"><a name="p500067564084831"></a><a name="p500067564084831"></a>Calculates the tangent of the long double value <strong id="b938140420084831"><a name="b938140420084831"></a><a name="b938140420084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1377978916084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1674705437084831"><a name="p1674705437084831"></a><a name="p1674705437084831"></a><a href="math.md#gaf85bcf153d7ae805733927f12329dac1">tanh</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1150855842084831"><a name="p1150855842084831"></a><a name="p1150855842084831"></a>double </p>
<p id="p306451523084831"><a name="p306451523084831"></a><a name="p306451523084831"></a>Calculates the hyperbolic tangent of the double value <strong id="b557117804084831"><a name="b557117804084831"></a><a name="b557117804084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row517786166084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1756256409084831"><a name="p1756256409084831"></a><a name="p1756256409084831"></a><a href="math.md#ga74e8f87bb37a338d2cebbb6b1d696593">tanhf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p619777830084831"><a name="p619777830084831"></a><a name="p619777830084831"></a>float </p>
<p id="p1121686090084831"><a name="p1121686090084831"></a><a name="p1121686090084831"></a>Calculates the hyperbolic tangent of the float value <strong id="b1050622814084831"><a name="b1050622814084831"></a><a name="b1050622814084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1180570986084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969563201084831"><a name="p1969563201084831"></a><a name="p1969563201084831"></a><a href="math.md#ga94ee8c57b6b2d0bc5466c75bea2bffcf">tanhl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p299406343084831"><a name="p299406343084831"></a><a name="p299406343084831"></a>long double </p>
<p id="p2000383771084831"><a name="p2000383771084831"></a><a name="p2000383771084831"></a>Calculates the hyperbolic tangent of the long double value <strong id="b1440438587084831"><a name="b1440438587084831"></a><a name="b1440438587084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1127662487084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p689168886084831"><a name="p689168886084831"></a><a name="p689168886084831"></a><a href="math.md#ga54afbf509eea5e9d6f9efdebc572339a">tgamma</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478829132084831"><a name="p478829132084831"></a><a name="p478829132084831"></a>double </p>
<p id="p1907888760084831"><a name="p1907888760084831"></a><a name="p1907888760084831"></a>Calculates the gamma function of the double value <strong id="b1877616803084831"><a name="b1877616803084831"></a><a name="b1877616803084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1187977791084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p664694236084831"><a name="p664694236084831"></a><a name="p664694236084831"></a><a href="math.md#ga2ab69de9110cc2c62ca78b5d20a3a3ae">tgammaf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021923158084831"><a name="p1021923158084831"></a><a name="p1021923158084831"></a>float </p>
<p id="p2025236296084831"><a name="p2025236296084831"></a><a name="p2025236296084831"></a>Calculates the gamma function of the float value <strong id="b1089987071084831"><a name="b1089987071084831"></a><a name="b1089987071084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1414798724084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544298820084831"><a name="p1544298820084831"></a><a name="p1544298820084831"></a><a href="math.md#ga8eff39a57115761c5025e08ff2e08c6a">tgammal</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1816271559084831"><a name="p1816271559084831"></a><a name="p1816271559084831"></a>long double </p>
<p id="p1513035238084831"><a name="p1513035238084831"></a><a name="p1513035238084831"></a>Calculates the gamma function of the long double value <strong id="b422089919084831"><a name="b422089919084831"></a><a name="b422089919084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row398608174084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p68204149084831"><a name="p68204149084831"></a><a name="p68204149084831"></a><a href="math.md#ga82a151adfde56b28fa8a50355c4f2ff6">trunc</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p473309871084831"><a name="p473309871084831"></a><a name="p473309871084831"></a>double </p>
<p id="p719430514084831"><a name="p719430514084831"></a><a name="p719430514084831"></a>Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the double value <strong id="b1823318573084831"><a name="b1823318573084831"></a><a name="b1823318573084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row210397138084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493106984084831"><a name="p1493106984084831"></a><a name="p1493106984084831"></a><a href="math.md#gaa8bb2049c170c9ac5b131fdba029991a">truncf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572746113084831"><a name="p572746113084831"></a><a name="p572746113084831"></a>float </p>
<p id="p799454476084831"><a name="p799454476084831"></a><a name="p799454476084831"></a>Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the float value <strong id="b655652496084831"><a name="b655652496084831"></a><a name="b655652496084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row438047943084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1144921834084831"><a name="p1144921834084831"></a><a name="p1144921834084831"></a><a href="math.md#ga8f9695496a9bb839eb5f728b6bf0c856">truncl</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p240260908084831"><a name="p240260908084831"></a><a name="p240260908084831"></a>long double </p>
<p id="p156466407084831"><a name="p156466407084831"></a><a name="p156466407084831"></a>Obtains the nearest integer whose absolute value is less than or equal to the absolute value of the long double value <strong id="b148355742084831"><a name="b148355742084831"></a><a name="b148355742084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row575510051084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1384641082084831"><a name="p1384641082084831"></a><a name="p1384641082084831"></a><a href="math.md#gaffb00730a1127dee798137075951ae21">j0</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p944560080084831"><a name="p944560080084831"></a><a name="p944560080084831"></a>double </p>
<p id="p226917797084831"><a name="p226917797084831"></a><a name="p226917797084831"></a>Calculates the Bessel function of the first kind of order <strong id="b1867675213084831"><a name="b1867675213084831"></a><a name="b1867675213084831"></a>0</strong> for the double value <strong id="b827789100084831"><a name="b827789100084831"></a><a name="b827789100084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1521891221084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106397672084831"><a name="p1106397672084831"></a><a name="p1106397672084831"></a><a href="math.md#ga8cac4aa70c418eba481417f1878b4cee">j1</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p900947521084831"><a name="p900947521084831"></a><a name="p900947521084831"></a>double </p>
<p id="p1097880123084831"><a name="p1097880123084831"></a><a name="p1097880123084831"></a>Calculates the Bessel function of the first kind of order <strong id="b1880883518084831"><a name="b1880883518084831"></a><a name="b1880883518084831"></a>1</strong> for the double value <strong id="b56383627084831"><a name="b56383627084831"></a><a name="b56383627084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1132042970084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2095473301084831"><a name="p2095473301084831"></a><a name="p2095473301084831"></a><a href="math.md#gadeff843dc8106ffda5caba6df44c591d">jn</a> (int n, double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2024942667084831"><a name="p2024942667084831"></a><a name="p2024942667084831"></a>double </p>
<p id="p1202760074084831"><a name="p1202760074084831"></a><a name="p1202760074084831"></a>Calculates the Bessel function of the first kind of order <strong id="b983837868084831"><a name="b983837868084831"></a><a name="b983837868084831"></a>n</strong> for the double value <strong id="b81999362084831"><a name="b81999362084831"></a><a name="b81999362084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row761739843084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1654220283084831"><a name="p1654220283084831"></a><a name="p1654220283084831"></a><a href="math.md#gafca57fd80386476e5cd1dd52173103c5">y0</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p759225804084831"><a name="p759225804084831"></a><a name="p759225804084831"></a>double </p>
<p id="p2014698577084831"><a name="p2014698577084831"></a><a name="p2014698577084831"></a>Calculates the Bessel function of the second kind of order <strong id="b1515913363084831"><a name="b1515913363084831"></a><a name="b1515913363084831"></a>0</strong> for the double value <strong id="b2004076262084831"><a name="b2004076262084831"></a><a name="b2004076262084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row787250932084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1108512965084831"><a name="p1108512965084831"></a><a name="p1108512965084831"></a><a href="math.md#ga369368526a105f3fba6776b11586070c">y1</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1127409470084831"><a name="p1127409470084831"></a><a name="p1127409470084831"></a>double </p>
<p id="p43927344084831"><a name="p43927344084831"></a><a name="p43927344084831"></a>Calculates the Bessel function of the second kind of order <strong id="b306073389084831"><a name="b306073389084831"></a><a name="b306073389084831"></a>1</strong> for the double value <strong id="b1901367561084831"><a name="b1901367561084831"></a><a name="b1901367561084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1512430125084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p19429570084831"><a name="p19429570084831"></a><a name="p19429570084831"></a><a href="math.md#gae31b4c8c6af724eaa73ad2ebce1aa3ce">yn</a> (int n, double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576546293084831"><a name="p1576546293084831"></a><a name="p1576546293084831"></a>double </p>
<p id="p811506109084831"><a name="p811506109084831"></a><a name="p811506109084831"></a>Calculates the Bessel function of the second kind of order <strong id="b1634183636084831"><a name="b1634183636084831"></a><a name="b1634183636084831"></a>n</strong> for the double value <strong id="b130302399084831"><a name="b130302399084831"></a><a name="b130302399084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row542158346084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431393946084831"><a name="p1431393946084831"></a><a name="p1431393946084831"></a><a href="math.md#ga08e754462e6ec13bc05fd41cff9cdd4a">finite</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501462302084831"><a name="p1501462302084831"></a><a name="p1501462302084831"></a>int </p>
<p id="p1180243182084831"><a name="p1180243182084831"></a><a name="p1180243182084831"></a>Checks whether the double value <strong id="b297091472084831"><a name="b297091472084831"></a><a name="b297091472084831"></a>x</strong> is an infinity or a NaN value. </p>
</td>
</tr>
<tr id="row2095862470084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1060932420084831"><a name="p1060932420084831"></a><a name="p1060932420084831"></a><a href="math.md#gaea39ac813876c506f8c351e6c14a5cb7">finitef</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1828920472084831"><a name="p1828920472084831"></a><a name="p1828920472084831"></a>int </p>
<p id="p1510754517084831"><a name="p1510754517084831"></a><a name="p1510754517084831"></a>Checks whether the float value <strong id="b1084774754084831"><a name="b1084774754084831"></a><a name="b1084774754084831"></a>x</strong> is an infinity or a NaN value. </p>
</td>
</tr>
<tr id="row1532249267084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p751159442084831"><a name="p751159442084831"></a><a name="p751159442084831"></a><a href="math.md#ga14db57dcd8982430d12219bbecd08a05">scalb</a> (double x, double <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566086580084831"><a name="p1566086580084831"></a><a name="p1566086580084831"></a>double </p>
<p id="p678922592084831"><a name="p678922592084831"></a><a name="p678922592084831"></a>Multiplies the double value <strong id="b1146088455084831"><a name="b1146088455084831"></a><a name="b1146088455084831"></a>x</strong> by <strong id="b1254899313084831"><a name="b1254899313084831"></a><a name="b1254899313084831"></a>FLT_RADIX</strong> raised to the power of the double value <strong id="b538189417084831"><a name="b538189417084831"></a><a name="b538189417084831"></a>exp</strong>, that is, x*<strong id="b1796681430084831"><a name="b1796681430084831"></a><a name="b1796681430084831"></a>FLT_RADIX</strong>^exp. </p>
</td>
</tr>
<tr id="row434019636084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p610686571084831"><a name="p610686571084831"></a><a name="p610686571084831"></a><a href="math.md#ga9c9db25d2ff9973e0d8638cf42df3999">scalbf</a> (float x, float <a href="math.md#gae09128febbbe6372cde4fa0c65608a42">exp</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p961451656084831"><a name="p961451656084831"></a><a name="p961451656084831"></a>float </p>
<p id="p1932737357084831"><a name="p1932737357084831"></a><a name="p1932737357084831"></a>Multiplies the float value <strong id="b2134869847084831"><a name="b2134869847084831"></a><a name="b2134869847084831"></a>x</strong> by <strong id="b77771919084831"><a name="b77771919084831"></a><a name="b77771919084831"></a>FLT_RADIX</strong> raised to the power of the float value <strong id="b1889090207084831"><a name="b1889090207084831"></a><a name="b1889090207084831"></a>exp</strong>, that is, x*<strong id="b200799874084831"><a name="b200799874084831"></a><a name="b200799874084831"></a>FLT_RADIX</strong>^exp. </p>
</td>
</tr>
<tr id="row865896901084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780438766084831"><a name="p780438766084831"></a><a name="p780438766084831"></a><a href="math.md#gafad3bf1f77c516fb8891c72beb51640f">significand</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p583167650084831"><a name="p583167650084831"></a><a name="p583167650084831"></a>double </p>
<p id="p1625911666084831"><a name="p1625911666084831"></a><a name="p1625911666084831"></a>Obtains the significand of the double value <strong id="b1779774412084831"><a name="b1779774412084831"></a><a name="b1779774412084831"></a>x</strong> scaled to the range [1,2). </p>
</td>
</tr>
<tr id="row1717551047084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2047055039084831"><a name="p2047055039084831"></a><a name="p2047055039084831"></a><a href="math.md#gac57d7d88e1a9b57c9a129ee4d4a68c42">significandf</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p75385722084831"><a name="p75385722084831"></a><a name="p75385722084831"></a>float </p>
<p id="p856046308084831"><a name="p856046308084831"></a><a name="p856046308084831"></a>Obtains the significand of the float value <strong id="b2111936255084831"><a name="b2111936255084831"></a><a name="b2111936255084831"></a>x</strong> scaled to the range [1,2). </p>
</td>
</tr>
<tr id="row359185054084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785708201084831"><a name="p785708201084831"></a><a name="p785708201084831"></a><a href="math.md#gafa59b98550749c27995dfb7c70e6783a">j0f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383816731084831"><a name="p1383816731084831"></a><a name="p1383816731084831"></a>float </p>
<p id="p1482328390084831"><a name="p1482328390084831"></a><a name="p1482328390084831"></a>Calculates the Bessel function of the first kind of order <strong id="b1240307175084831"><a name="b1240307175084831"></a><a name="b1240307175084831"></a>0</strong> for the float value <strong id="b1931649055084831"><a name="b1931649055084831"></a><a name="b1931649055084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1068854820084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p633412947084831"><a name="p633412947084831"></a><a name="p633412947084831"></a><a href="math.md#ga4b50bbed127a1c57940d600498a3c5c7">j1f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825753581084831"><a name="p1825753581084831"></a><a name="p1825753581084831"></a>float </p>
<p id="p1533863544084831"><a name="p1533863544084831"></a><a name="p1533863544084831"></a>Calculates the Bessel function of the first kind of order <strong id="b183753643084831"><a name="b183753643084831"></a><a name="b183753643084831"></a>1</strong> for the float value <strong id="b1184944935084831"><a name="b1184944935084831"></a><a name="b1184944935084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1966714092084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879621210084831"><a name="p879621210084831"></a><a name="p879621210084831"></a><a href="math.md#gac3fcdfd92a775eed4ebd673d7da02525">jnf</a> (int n, float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p133709499084831"><a name="p133709499084831"></a><a name="p133709499084831"></a>float </p>
<p id="p632913155084831"><a name="p632913155084831"></a><a name="p632913155084831"></a>Calculates the Bessel function of the first kind of order <strong id="b741862227084831"><a name="b741862227084831"></a><a name="b741862227084831"></a>n</strong> for the float value <strong id="b730541809084831"><a name="b730541809084831"></a><a name="b730541809084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row791790182084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282866165084831"><a name="p1282866165084831"></a><a name="p1282866165084831"></a><a href="math.md#gaba3cd2d73c1ae75ec2d01ebb2dfc108c">y0f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1719864924084831"><a name="p1719864924084831"></a><a name="p1719864924084831"></a>float </p>
<p id="p1083966317084831"><a name="p1083966317084831"></a><a name="p1083966317084831"></a>Calculates the Bessel function of the second kind of order <strong id="b422455062084831"><a name="b422455062084831"></a><a name="b422455062084831"></a>0</strong> for the float value <strong id="b1886836945084831"><a name="b1886836945084831"></a><a name="b1886836945084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row124700215084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p460336001084831"><a name="p460336001084831"></a><a name="p460336001084831"></a><a href="math.md#ga5f37c38e8985dafae6abca2d1782c160">y1f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155828246084831"><a name="p155828246084831"></a><a name="p155828246084831"></a>float </p>
<p id="p1529291423084831"><a name="p1529291423084831"></a><a name="p1529291423084831"></a>Calculates the Bessel function of the second kind of order <strong id="b1149529233084831"><a name="b1149529233084831"></a><a name="b1149529233084831"></a>1</strong> for the float value <strong id="b528642060084831"><a name="b528642060084831"></a><a name="b528642060084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row358589935084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1253781700084831"><a name="p1253781700084831"></a><a name="p1253781700084831"></a><a href="math.md#ga47f8750942b731456dd7f2cbf5f55806">ynf</a> (int n, float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p119758716084831"><a name="p119758716084831"></a><a name="p119758716084831"></a>float </p>
<p id="p1868878797084831"><a name="p1868878797084831"></a><a name="p1868878797084831"></a>Calculates the Bessel function of the second kind of order <strong id="b1682144360084831"><a name="b1682144360084831"></a><a name="b1682144360084831"></a>n</strong> for the float value <strong id="b1912427334084831"><a name="b1912427334084831"></a><a name="b1912427334084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1572363498084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1584908596084831"><a name="p1584908596084831"></a><a name="p1584908596084831"></a><a href="math.md#ga278e86e217081a0268107f0d6876cb9b">lgammal_r</a> (long double x, int *signp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109814578084831"><a name="p1109814578084831"></a><a name="p1109814578084831"></a>long double </p>
<p id="p2085136950084831"><a name="p2085136950084831"></a><a name="p2085136950084831"></a>Calculates the natural logarithm of the absolute value of the gamma function of the double value <strong id="b1989091880084831"><a name="b1989091880084831"></a><a name="b1989091880084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row759731773084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p743980914084831"><a name="p743980914084831"></a><a name="p743980914084831"></a><a href="math.md#gaf4509ae544cecab0e9a61efdfccb7530">sincos</a> (double x, double *<a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a>, double *<a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084516596084831"><a name="p1084516596084831"></a><a name="p1084516596084831"></a>void </p>
<p id="p804777694084831"><a name="p804777694084831"></a><a name="p804777694084831"></a>Calculates the sine and cosine of the double value <strong id="b791204355084831"><a name="b791204355084831"></a><a name="b791204355084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1194615318084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773375145084831"><a name="p1773375145084831"></a><a name="p1773375145084831"></a><a href="math.md#gac59adab35511be68e92ad9013d63e866">sincosf</a> (float x, float *<a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a>, float *<a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p144516014084831"><a name="p144516014084831"></a><a name="p144516014084831"></a>void </p>
<p id="p1365187170084831"><a name="p1365187170084831"></a><a name="p1365187170084831"></a>Calculates the sine and cosine of the float value <strong id="b1817960202084831"><a name="b1817960202084831"></a><a name="b1817960202084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row826569534084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p594577683084831"><a name="p594577683084831"></a><a name="p594577683084831"></a><a href="math.md#gaf877b78dbe8e265bdf4b975dbc713482">sincosl</a> (long double x, long double *<a href="math.md#gaad4af25633b071b0e2cdb8ebd87eca77">sin</a>, long double *<a href="math.md#ga5e7b53a694b3cf0f2d7debd444140fbd">cos</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115121238084831"><a name="p115121238084831"></a><a name="p115121238084831"></a>void </p>
<p id="p1779862064084831"><a name="p1779862064084831"></a><a name="p1779862064084831"></a>Calculates the sine and cosine of the long double value <strong id="b597196081084831"><a name="b597196081084831"></a><a name="b597196081084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1364130064084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164811572084831"><a name="p164811572084831"></a><a name="p164811572084831"></a><a href="math.md#gaea673cadd2aef111e2ee7a813776b768">exp10</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1189342447084831"><a name="p1189342447084831"></a><a name="p1189342447084831"></a>double </p>
<p id="p1596504026084831"><a name="p1596504026084831"></a><a name="p1596504026084831"></a>Calculates the base-10 exponential function of the double value <strong id="b275488214084831"><a name="b275488214084831"></a><a name="b275488214084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1013538446084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084027923084831"><a name="p2084027923084831"></a><a name="p2084027923084831"></a><a href="math.md#gad27f10a0e30a7fe130c18786bf097e4b">exp10f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097166449084831"><a name="p2097166449084831"></a><a name="p2097166449084831"></a>float </p>
<p id="p1247993736084831"><a name="p1247993736084831"></a><a name="p1247993736084831"></a>Calculates the base-10 exponential function of the float value <strong id="b1822991127084831"><a name="b1822991127084831"></a><a name="b1822991127084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1840252272084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878851106084831"><a name="p878851106084831"></a><a name="p878851106084831"></a><a href="math.md#ga28c11df4d7b29c9f59ac733fba51bece">exp10l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106525754084831"><a name="p1106525754084831"></a><a name="p1106525754084831"></a>long double </p>
<p id="p1056022092084831"><a name="p1056022092084831"></a><a name="p1056022092084831"></a>Calculates the base-10 exponential function of the long double value <strong id="b1712281146084831"><a name="b1712281146084831"></a><a name="b1712281146084831"></a>x</strong>. </p>
</td>
</tr>
<tr id="row1176718214084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841801084084831"><a name="p1841801084084831"></a><a name="p1841801084084831"></a><a href="math.md#gafbbc60a3627a8de4845c7e99e6134ec8">pow10</a> (double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1612836773084831"><a name="p1612836773084831"></a><a name="p1612836773084831"></a>double </p>
<p id="p1259698558084831"><a name="p1259698558084831"></a><a name="p1259698558084831"></a>Calculates the value of 10 raised to the power <strong id="b620332707084831"><a name="b620332707084831"></a><a name="b620332707084831"></a>x</strong>, which is a double value. </p>
</td>
</tr>
<tr id="row636646013084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1407421503084831"><a name="p1407421503084831"></a><a name="p1407421503084831"></a><a href="math.md#ga2cb598503b85d66abf59e9da06478f1a">pow10f</a> (float x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1547119153084831"><a name="p1547119153084831"></a><a name="p1547119153084831"></a>float </p>
<p id="p1240422014084831"><a name="p1240422014084831"></a><a name="p1240422014084831"></a>Calculates the value of 10 raised to the power <strong id="b379277467084831"><a name="b379277467084831"></a><a name="b379277467084831"></a>x</strong>, which is a float value. </p>
</td>
</tr>
<tr id="row1373674464084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408831243084831"><a name="p1408831243084831"></a><a name="p1408831243084831"></a><a href="math.md#ga9baf71e9033dd73a9c225a2fc9cca61d">pow10l</a> (long double x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1386552955084831"><a name="p1386552955084831"></a><a name="p1386552955084831"></a>long double </p>
<p id="p1425720773084831"><a name="p1425720773084831"></a><a name="p1425720773084831"></a>Calculates the value of 10 raised to the power <strong id="b758358960084831"><a name="b758358960084831"></a><a name="b758358960084831"></a>x</strong>, which is a long double value. </p>
</td>
</tr>
</tbody>
</table>

