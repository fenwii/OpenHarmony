# complex.h<a name="ZH-CN_TOPIC_0000001055108019"></a>

## **Overview**<a name="section88508162084829"></a>

**Related Modules:**

[MATH](MATH.md)

**Description:**

Declares functions to perform operations on complex numbers. 

You can use the functions provided in this file to perform operations on complex numbers during development. The functions include complex trigonometric, inverse trigonometric, hyperbolic, inverse hyperbolic, exponential, and logarithmic functions, and the functions to obtain the real and imaginary parts of a complex number. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2008290128084829"></a>

## Macros<a name="define-members"></a>

<a name="table467945365084829"></a>
<table><thead align="left"><tr id="row415088873084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p602904731084829"><a name="p602904731084829"></a><a name="p602904731084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p710081797084829"><a name="p710081797084829"></a><a name="p710081797084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1658660842084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p505534013084829"><a name="p505534013084829"></a><a name="p505534013084829"></a><a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;&nbsp;&nbsp;_Complex</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p778783812084829"><a name="p778783812084829"></a><a name="p778783812084829"></a>Indicates the type of a complex number. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table215913053084829"></a>
<table><thead align="left"><tr id="row818977951084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p797173634084829"><a name="p797173634084829"></a><a name="p797173634084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1075227862084829"><a name="p1075227862084829"></a><a name="p1075227862084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1186807969084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p217787038084829"><a name="p217787038084829"></a><a name="p217787038084829"></a><a href="MATH.md#ga51a9bcdc7791e50f879c79d64362d7c3">cacos</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1321442786084829"><a name="p1321442786084829"></a><a name="p1321442786084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p622109066084829"><a name="p622109066084829"></a><a name="p622109066084829"></a>Calculates the arc cosine of the complex number <strong id="b1477654832084829"><a name="b1477654832084829"></a><a name="b1477654832084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row514432194084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1185405076084829"><a name="p1185405076084829"></a><a name="p1185405076084829"></a><a href="MATH.md#ga238bc3dbd59adeb477af18c9a501e04e">cacosf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1718672657084829"><a name="p1718672657084829"></a><a name="p1718672657084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p411804850084829"><a name="p411804850084829"></a><a name="p411804850084829"></a>Calculates the arc cosine of the complex number <strong id="b290390116084829"><a name="b290390116084829"></a><a name="b290390116084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row2135156239084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278715723084829"><a name="p278715723084829"></a><a name="p278715723084829"></a><a href="MATH.md#ga789143f2859142f58590b2726328025f">cacosl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896588105084829"><a name="p896588105084829"></a><a name="p896588105084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1234806673084829"><a name="p1234806673084829"></a><a name="p1234806673084829"></a>Calculates the arc cosine of the complex number <strong id="b1294270044084829"><a name="b1294270044084829"></a><a name="b1294270044084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row319559913084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908728861084829"><a name="p908728861084829"></a><a name="p908728861084829"></a><a href="MATH.md#gac43774f89411806a3e0695012cdb7f38">casin</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p719967220084829"><a name="p719967220084829"></a><a name="p719967220084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1765996729084829"><a name="p1765996729084829"></a><a name="p1765996729084829"></a>Calculates the arc sine of the complex number <strong id="b1244260079084829"><a name="b1244260079084829"></a><a name="b1244260079084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row489363048084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p90118614084829"><a name="p90118614084829"></a><a name="p90118614084829"></a><a href="MATH.md#ga04d2cd1f0b47d3f1b782aeb517151033">casinf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p955645761084829"><a name="p955645761084829"></a><a name="p955645761084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p979508799084829"><a name="p979508799084829"></a><a name="p979508799084829"></a>Calculates the arc sine of the complex number <strong id="b1496771884084829"><a name="b1496771884084829"></a><a name="b1496771884084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row260035095084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727764006084829"><a name="p727764006084829"></a><a name="p727764006084829"></a><a href="MATH.md#ga8770350a79904ac151ebb3eebd736188">casinl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p36726841084829"><a name="p36726841084829"></a><a name="p36726841084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p590673169084829"><a name="p590673169084829"></a><a name="p590673169084829"></a>Calculates the arc sine of the complex number <strong id="b1072983532084829"><a name="b1072983532084829"></a><a name="b1072983532084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row847487681084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087056529084829"><a name="p2087056529084829"></a><a name="p2087056529084829"></a><a href="MATH.md#ga1a77a3240b834af81a23b38f2af6c93d">catan</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649698075084829"><a name="p649698075084829"></a><a name="p649698075084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p711782797084829"><a name="p711782797084829"></a><a name="p711782797084829"></a>Calculates the arc tangent of the complex number <strong id="b350749031084829"><a name="b350749031084829"></a><a name="b350749031084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1161096849084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892897470084829"><a name="p1892897470084829"></a><a name="p1892897470084829"></a><a href="MATH.md#ga4d0beef9b3994887e356c6b5c98388d9">catanf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1233820659084829"><a name="p1233820659084829"></a><a name="p1233820659084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p620710720084829"><a name="p620710720084829"></a><a name="p620710720084829"></a>Calculates the arc tangent of the complex number <strong id="b27827070084829"><a name="b27827070084829"></a><a name="b27827070084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1889265999084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496387585084829"><a name="p496387585084829"></a><a name="p496387585084829"></a><a href="MATH.md#gaf28ad2f006e49eaa6bbdb97dd143d6cb">catanl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403204152084829"><a name="p1403204152084829"></a><a name="p1403204152084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1105549973084829"><a name="p1105549973084829"></a><a name="p1105549973084829"></a>Calculates the arc tangent of the complex number <strong id="b1916353290084829"><a name="b1916353290084829"></a><a name="b1916353290084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row456525481084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564849010084829"><a name="p1564849010084829"></a><a name="p1564849010084829"></a><a href="MATH.md#ga6a25bcd38751910533efde6dad1499c3">ccos</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1821429107084829"><a name="p1821429107084829"></a><a name="p1821429107084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p519000021084829"><a name="p519000021084829"></a><a name="p519000021084829"></a>Calculates the cosine of the complex number <strong id="b578939194084829"><a name="b578939194084829"></a><a name="b578939194084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1143723206084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1314188780084829"><a name="p1314188780084829"></a><a name="p1314188780084829"></a><a href="MATH.md#ga88df5eebfb10b88ed37e444f5b13fd6a">ccosf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277688325084829"><a name="p277688325084829"></a><a name="p277688325084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p958560879084829"><a name="p958560879084829"></a><a name="p958560879084829"></a>Calculates the cosine of the complex number <strong id="b1003236385084829"><a name="b1003236385084829"></a><a name="b1003236385084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1483569472084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1350233766084829"><a name="p1350233766084829"></a><a name="p1350233766084829"></a><a href="MATH.md#ga785d8c7b2ac4283d4759dfa6a86779ab">ccosl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1123243354084829"><a name="p1123243354084829"></a><a name="p1123243354084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p2073654893084829"><a name="p2073654893084829"></a><a name="p2073654893084829"></a>Calculates the cosine of the complex number <strong id="b1958855053084829"><a name="b1958855053084829"></a><a name="b1958855053084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row2037880280084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p831743210084829"><a name="p831743210084829"></a><a name="p831743210084829"></a><a href="MATH.md#ga1b9030685d326e66a93a35ca8c4bb0f6">csin</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990563655084829"><a name="p1990563655084829"></a><a name="p1990563655084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1849836073084829"><a name="p1849836073084829"></a><a name="p1849836073084829"></a>Calculates the sine of the complex number <strong id="b812625987084829"><a name="b812625987084829"></a><a name="b812625987084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row489957103084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1519202031084829"><a name="p1519202031084829"></a><a name="p1519202031084829"></a><a href="MATH.md#ga76dc89521e12096bc2104c9c0dcc20ea">csinf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305883089084829"><a name="p305883089084829"></a><a name="p305883089084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p675129833084829"><a name="p675129833084829"></a><a name="p675129833084829"></a>Calculates the sine of the complex number <strong id="b1169387111084829"><a name="b1169387111084829"></a><a name="b1169387111084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row103543422084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056623371084829"><a name="p2056623371084829"></a><a name="p2056623371084829"></a><a href="MATH.md#gad594fa6071ea5d383a0c7abaa0c32d80">csinl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867894084829"><a name="p867894084829"></a><a name="p867894084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p943300912084829"><a name="p943300912084829"></a><a name="p943300912084829"></a>Calculates the sine of the complex number <strong id="b1128374737084829"><a name="b1128374737084829"></a><a name="b1128374737084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row252395887084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1261000955084829"><a name="p1261000955084829"></a><a name="p1261000955084829"></a><a href="MATH.md#ga665b5dfc1b1f51d3b444f049c6bd95dd">ctan</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1584774297084829"><a name="p1584774297084829"></a><a name="p1584774297084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1094231799084829"><a name="p1094231799084829"></a><a name="p1094231799084829"></a>Calculates the tangent of the complex number <strong id="b300614610084829"><a name="b300614610084829"></a><a name="b300614610084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1661815988084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1249522177084829"><a name="p1249522177084829"></a><a name="p1249522177084829"></a><a href="MATH.md#ga4301d608cc419f1ba3177fae4f258f30">ctanf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1464960852084829"><a name="p1464960852084829"></a><a name="p1464960852084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1767148233084829"><a name="p1767148233084829"></a><a name="p1767148233084829"></a>Calculates the tangent of the complex number <strong id="b432402879084829"><a name="b432402879084829"></a><a name="b432402879084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row625607827084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1939187181084829"><a name="p1939187181084829"></a><a name="p1939187181084829"></a><a href="MATH.md#ga7aa0362acd67521c9aac791aa617f953">ctanl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1843012819084829"><a name="p1843012819084829"></a><a name="p1843012819084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1489418754084829"><a name="p1489418754084829"></a><a name="p1489418754084829"></a>Calculates the tangent of the complex number <strong id="b32292851084829"><a name="b32292851084829"></a><a name="b32292851084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row638213401084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226693316084829"><a name="p226693316084829"></a><a name="p226693316084829"></a><a href="MATH.md#gaf7286142554fde4ba6316a2b64b96c5c">cacosh</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1763947632084829"><a name="p1763947632084829"></a><a name="p1763947632084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p2111994724084829"><a name="p2111994724084829"></a><a name="p2111994724084829"></a>Calculates the inverse hyperbolic cosine of the complex number <strong id="b422930396084829"><a name="b422930396084829"></a><a name="b422930396084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row723913209084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509465913084829"><a name="p509465913084829"></a><a name="p509465913084829"></a><a href="MATH.md#gabe9dbe34293eef409598b0559435c5ff">cacoshf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p461621629084829"><a name="p461621629084829"></a><a name="p461621629084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p461440728084829"><a name="p461440728084829"></a><a name="p461440728084829"></a>Calculates the inverse hyperbolic cosine of the complex number <strong id="b1712533102084829"><a name="b1712533102084829"></a><a name="b1712533102084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1954613275084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1499370926084829"><a name="p1499370926084829"></a><a name="p1499370926084829"></a><a href="MATH.md#gad8e03bbb434b8a9af73e0e3daec045ac">cacoshl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501941369084829"><a name="p1501941369084829"></a><a name="p1501941369084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1448681723084829"><a name="p1448681723084829"></a><a name="p1448681723084829"></a>Calculates the inverse hyperbolic cosine of the complex number <strong id="b1653771352084829"><a name="b1653771352084829"></a><a name="b1653771352084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1242218412084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081257366084829"><a name="p1081257366084829"></a><a name="p1081257366084829"></a><a href="MATH.md#ga6fc1a0c1cbac62ba63e799d7e8f488e0">casinh</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809429697084829"><a name="p1809429697084829"></a><a name="p1809429697084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1977162007084829"><a name="p1977162007084829"></a><a name="p1977162007084829"></a>Calculates the inverse hyperbolic sine of the complex number <strong id="b842541000084829"><a name="b842541000084829"></a><a name="b842541000084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1454448280084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859667283084829"><a name="p1859667283084829"></a><a name="p1859667283084829"></a><a href="MATH.md#ga8b682e1c311efa5594ec0d0b39c9efe0">casinhf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459078686084829"><a name="p1459078686084829"></a><a name="p1459078686084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p829964705084829"><a name="p829964705084829"></a><a name="p829964705084829"></a>Calculates the inverse hyperbolic sine of the complex number <strong id="b1253681941084829"><a name="b1253681941084829"></a><a name="b1253681941084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row643035800084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522100640084829"><a name="p1522100640084829"></a><a name="p1522100640084829"></a><a href="MATH.md#ga174b8f2a00e771dbbad06fdf0e0ee449">casinhl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p827912785084829"><a name="p827912785084829"></a><a name="p827912785084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p379214010084829"><a name="p379214010084829"></a><a name="p379214010084829"></a>Calculates the inverse hyperbolic sine of the complex number <strong id="b1845670601084829"><a name="b1845670601084829"></a><a name="b1845670601084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1120805892084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658049776084829"><a name="p1658049776084829"></a><a name="p1658049776084829"></a><a href="MATH.md#ga376fef7890def8c0e7b2b5a5292be074">catanh</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052423757084829"><a name="p1052423757084829"></a><a name="p1052423757084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1477198842084829"><a name="p1477198842084829"></a><a name="p1477198842084829"></a>Calculates the inverse hyperbolic tangent of the complex number <strong id="b395737596084829"><a name="b395737596084829"></a><a name="b395737596084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row661718036084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735217235084829"><a name="p735217235084829"></a><a name="p735217235084829"></a><a href="MATH.md#ga480c29e0eeace893be77a2c61995d2ec">catanhf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405467987084829"><a name="p405467987084829"></a><a name="p405467987084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1151434477084829"><a name="p1151434477084829"></a><a name="p1151434477084829"></a>Calculates the inverse hyperbolic tangent of the complex number <strong id="b206986522084829"><a name="b206986522084829"></a><a name="b206986522084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1336972013084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p610837380084829"><a name="p610837380084829"></a><a name="p610837380084829"></a><a href="MATH.md#gab2422355124f175a41ec092c3b8adf2b">catanhl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225986290084829"><a name="p1225986290084829"></a><a name="p1225986290084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1316777080084829"><a name="p1316777080084829"></a><a name="p1316777080084829"></a>Calculates the inverse hyperbolic tangent of the complex number <strong id="b1566637427084829"><a name="b1566637427084829"></a><a name="b1566637427084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row373610129084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p717264077084829"><a name="p717264077084829"></a><a name="p717264077084829"></a><a href="MATH.md#ga62c8f7e0cce95bbf670af16376909324">ccosh</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1347757698084829"><a name="p1347757698084829"></a><a name="p1347757698084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p250355243084829"><a name="p250355243084829"></a><a name="p250355243084829"></a>Calculates the hyperbolic cosine of the complex number <strong id="b699818023084829"><a name="b699818023084829"></a><a name="b699818023084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row785252460084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1714514828084829"><a name="p1714514828084829"></a><a name="p1714514828084829"></a><a href="MATH.md#gabe11c35bd81b278ab0e47196c5952662">ccoshf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1965060898084829"><a name="p1965060898084829"></a><a name="p1965060898084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p916029083084829"><a name="p916029083084829"></a><a name="p916029083084829"></a>Calculates the hyperbolic cosine of the complex number <strong id="b667857278084829"><a name="b667857278084829"></a><a name="b667857278084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row295675599084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p492343552084829"><a name="p492343552084829"></a><a name="p492343552084829"></a><a href="MATH.md#gad2b7878b871c0266ecb1f58e5bf141a7">ccoshl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1609961515084829"><a name="p1609961515084829"></a><a name="p1609961515084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1869527423084829"><a name="p1869527423084829"></a><a name="p1869527423084829"></a>Calculates the hyperbolic cosine of the complex number <strong id="b2054160354084829"><a name="b2054160354084829"></a><a name="b2054160354084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row383846607084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626691790084829"><a name="p1626691790084829"></a><a name="p1626691790084829"></a><a href="MATH.md#ga0c782aa9258a4e11cc3ea57b2dcccfef">csinh</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086374700084829"><a name="p1086374700084829"></a><a name="p1086374700084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1277276345084829"><a name="p1277276345084829"></a><a name="p1277276345084829"></a>Calculates the hyperbolic sine of the complex number <strong id="b562926525084829"><a name="b562926525084829"></a><a name="b562926525084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row694035483084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p526983325084829"><a name="p526983325084829"></a><a name="p526983325084829"></a><a href="MATH.md#ga268ba13d67a10e6667bd6b64a1a96351">csinhf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p481168755084829"><a name="p481168755084829"></a><a name="p481168755084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p810442156084829"><a name="p810442156084829"></a><a name="p810442156084829"></a>Calculates the hyperbolic sine of the complex number <strong id="b1116981160084829"><a name="b1116981160084829"></a><a name="b1116981160084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row2062587487084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1882259774084829"><a name="p1882259774084829"></a><a name="p1882259774084829"></a><a href="MATH.md#ga0d14ae39cd9a811e42e36512fe6c7e53">csinhl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016241249084829"><a name="p1016241249084829"></a><a name="p1016241249084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1754655646084829"><a name="p1754655646084829"></a><a name="p1754655646084829"></a>Calculates the hyperbolic sine of the complex number <strong id="b2036260492084829"><a name="b2036260492084829"></a><a name="b2036260492084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1416469573084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179800412084829"><a name="p179800412084829"></a><a name="p179800412084829"></a><a href="MATH.md#ga9c5cf378e654f3aaed9fb0f5c8223585">ctanh</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279555700084829"><a name="p279555700084829"></a><a name="p279555700084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1552063511084829"><a name="p1552063511084829"></a><a name="p1552063511084829"></a>Calculates the hyperbolic tangent of the complex number <strong id="b407301208084829"><a name="b407301208084829"></a><a name="b407301208084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row531279087084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p749244975084829"><a name="p749244975084829"></a><a name="p749244975084829"></a><a href="MATH.md#gad68db7f429f2104acf52b096c5efb69a">ctanhf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p566162640084829"><a name="p566162640084829"></a><a name="p566162640084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1686169653084829"><a name="p1686169653084829"></a><a name="p1686169653084829"></a>Calculates the hyperbolic tangent of the complex number <strong id="b1201040693084829"><a name="b1201040693084829"></a><a name="b1201040693084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row451510915084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1955178154084829"><a name="p1955178154084829"></a><a name="p1955178154084829"></a><a href="MATH.md#ga2fbb0a9d578343f924c96faed3189805">ctanhl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327065249084829"><a name="p327065249084829"></a><a name="p327065249084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1212235739084829"><a name="p1212235739084829"></a><a name="p1212235739084829"></a>Calculates the hyperbolic tangent of the complex number <strong id="b273275454084829"><a name="b273275454084829"></a><a name="b273275454084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row569927314084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856387570084829"><a name="p1856387570084829"></a><a name="p1856387570084829"></a><a href="MATH.md#gab9c654c52efefb54d06d52aa1a1c1827">cexp</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48938986084829"><a name="p48938986084829"></a><a name="p48938986084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1709269702084829"><a name="p1709269702084829"></a><a name="p1709269702084829"></a>Calculates the base-e exponential of the complex number <strong id="b843144570084829"><a name="b843144570084829"></a><a name="b843144570084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row584493118084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1275916939084829"><a name="p1275916939084829"></a><a name="p1275916939084829"></a><a href="MATH.md#ga8628a449a00228f124c9e53d2236611f">cexpf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p412672431084829"><a name="p412672431084829"></a><a name="p412672431084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1049785240084829"><a name="p1049785240084829"></a><a name="p1049785240084829"></a>Calculates the base-e exponential of the complex number <strong id="b375517914084829"><a name="b375517914084829"></a><a name="b375517914084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1275059144084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479451691084829"><a name="p479451691084829"></a><a name="p479451691084829"></a><a href="MATH.md#ga31a965fe1790cace431516e53f7d0cb5">cexpl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467076671084829"><a name="p467076671084829"></a><a name="p467076671084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p445469697084829"><a name="p445469697084829"></a><a name="p445469697084829"></a>Calculates the base-e exponential of the complex number <strong id="b1725780880084829"><a name="b1725780880084829"></a><a name="b1725780880084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row790290631084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564643277084829"><a name="p1564643277084829"></a><a name="p1564643277084829"></a><a href="MATH.md#gaa39c3557d8db10c19571bc0b63fd5529">clog</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683165929084829"><a name="p683165929084829"></a><a name="p683165929084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1084449800084829"><a name="p1084449800084829"></a><a name="p1084449800084829"></a>Calculates the natural (base-e) logarithm of the complex number <strong id="b1971868417084829"><a name="b1971868417084829"></a><a name="b1971868417084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1939764064084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1818085369084829"><a name="p1818085369084829"></a><a name="p1818085369084829"></a><a href="MATH.md#ga0c9f343c7d1dabc91f6e4cb868b81152">clogf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2142575118084829"><a name="p2142575118084829"></a><a name="p2142575118084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p814564757084829"><a name="p814564757084829"></a><a name="p814564757084829"></a>Calculates the natural (base-e) logarithm of the complex number <strong id="b531098704084829"><a name="b531098704084829"></a><a name="b531098704084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row2094715311084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315661156084829"><a name="p315661156084829"></a><a name="p315661156084829"></a><a href="MATH.md#ga48efe0bf63314044fafaeb32623fff17">clogl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2030649692084829"><a name="p2030649692084829"></a><a name="p2030649692084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p532481015084829"><a name="p532481015084829"></a><a name="p532481015084829"></a>Calculates the natural (base-e) logarithm of the complex number <strong id="b1517072911084829"><a name="b1517072911084829"></a><a name="b1517072911084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1149303088084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772355187084829"><a name="p1772355187084829"></a><a name="p1772355187084829"></a><a href="MATH.md#ga82c65f6b05062b620716623ba49ff07f">cabs</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p567393505084829"><a name="p567393505084829"></a><a name="p567393505084829"></a>double&nbsp;</p>
<p id="p1061628743084829"><a name="p1061628743084829"></a><a name="p1061628743084829"></a>Calculates the absolute value of the complex number <strong id="b792007234084829"><a name="b792007234084829"></a><a name="b792007234084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row626333610084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402118812084829"><a name="p402118812084829"></a><a name="p402118812084829"></a><a href="MATH.md#ga59a1f4977dfdf85b51a84bfd56737277">cabsf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246408576084829"><a name="p246408576084829"></a><a name="p246408576084829"></a>float&nbsp;</p>
<p id="p725822101084829"><a name="p725822101084829"></a><a name="p725822101084829"></a>Calculates the absolute value of the complex number <strong id="b1859743122084829"><a name="b1859743122084829"></a><a name="b1859743122084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row647135485084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p194282052084829"><a name="p194282052084829"></a><a name="p194282052084829"></a><a href="MATH.md#ga7e37259e24f3384f376e4d3eb45a9ea8">cabsl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125478359084829"><a name="p2125478359084829"></a><a name="p2125478359084829"></a>long double&nbsp;</p>
<p id="p1934090792084829"><a name="p1934090792084829"></a><a name="p1934090792084829"></a>Calculates the absolute value of the complex number <strong id="b553914492084829"><a name="b553914492084829"></a><a name="b553914492084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row2047569864084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683184775084829"><a name="p683184775084829"></a><a name="p683184775084829"></a><a href="MATH.md#ga6fd1bd16c6de991f95a4e19e0f2f2a12">cpow</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> x, double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p686811971084829"><a name="p686811971084829"></a><a name="p686811971084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p342086902084829"><a name="p342086902084829"></a><a name="p342086902084829"></a>Calculates the value of <strong id="b188634054084829"><a name="b188634054084829"></a><a name="b188634054084829"></a>x</strong> raised to the <strong id="b1394882657084829"><a name="b1394882657084829"></a><a name="b1394882657084829"></a>z</strong> power. </p>
</td>
</tr>
<tr id="row1430195479084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1654641989084829"><a name="p1654641989084829"></a><a name="p1654641989084829"></a><a href="MATH.md#ga58beb4a3ea7b6ab6bb942900f94179fa">cpowf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> x, float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1608050237084829"><a name="p1608050237084829"></a><a name="p1608050237084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1491666318084829"><a name="p1491666318084829"></a><a name="p1491666318084829"></a>Calculates the value of <strong id="b1764546661084829"><a name="b1764546661084829"></a><a name="b1764546661084829"></a>x</strong> raised to the <strong id="b380789743084829"><a name="b380789743084829"></a><a name="b380789743084829"></a>z</strong> power. </p>
</td>
</tr>
<tr id="row615215917084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p732851406084829"><a name="p732851406084829"></a><a name="p732851406084829"></a><a href="MATH.md#gae3ae7292dac86eeec3bb9a06b66f61cb">cpowl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> x, long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p231904872084829"><a name="p231904872084829"></a><a name="p231904872084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p311235887084829"><a name="p311235887084829"></a><a name="p311235887084829"></a>Calculates the value of <strong id="b670425114084829"><a name="b670425114084829"></a><a name="b670425114084829"></a>x</strong> raised to the <strong id="b1863342430084829"><a name="b1863342430084829"></a><a name="b1863342430084829"></a>z</strong> power. </p>
</td>
</tr>
<tr id="row1867869208084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p159924990084829"><a name="p159924990084829"></a><a name="p159924990084829"></a><a href="MATH.md#ga7ff172d72bc0474b93e27470ce94494b">csqrt</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167760912084829"><a name="p1167760912084829"></a><a name="p1167760912084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p791962903084829"><a name="p791962903084829"></a><a name="p791962903084829"></a>Calculates the square root of the complex number <strong id="b404841156084829"><a name="b404841156084829"></a><a name="b404841156084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1929889024084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554858101084829"><a name="p554858101084829"></a><a name="p554858101084829"></a><a href="MATH.md#gab8e425ba3e5d52d410afc3041bdeadce">csqrtf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p456846621084829"><a name="p456846621084829"></a><a name="p456846621084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1355961447084829"><a name="p1355961447084829"></a><a name="p1355961447084829"></a>Calculates the square root of the complex number <strong id="b1434577780084829"><a name="b1434577780084829"></a><a name="b1434577780084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row839767111084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p461277853084829"><a name="p461277853084829"></a><a name="p461277853084829"></a><a href="MATH.md#ga94a429c220e400a1a6781d6e11cbfafd">csqrtl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p16038253084829"><a name="p16038253084829"></a><a name="p16038253084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p273157664084829"><a name="p273157664084829"></a><a name="p273157664084829"></a>Calculates the square root of the complex number <strong id="b1583626365084829"><a name="b1583626365084829"></a><a name="b1583626365084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1254272180084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p166235045084829"><a name="p166235045084829"></a><a name="p166235045084829"></a><a href="MATH.md#ga4a1e5d839db7a1dc6013b2846b2432d9">carg</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245958558084829"><a name="p1245958558084829"></a><a name="p1245958558084829"></a>double&nbsp;</p>
<p id="p994860142084829"><a name="p994860142084829"></a><a name="p994860142084829"></a>Calculates the phase angle of the complex number <strong id="b2118849631084829"><a name="b2118849631084829"></a><a name="b2118849631084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row450442444084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727447941084829"><a name="p727447941084829"></a><a name="p727447941084829"></a><a href="MATH.md#ga66334f398567baa3648cd3111ed68d3b">cargf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656389067084829"><a name="p656389067084829"></a><a name="p656389067084829"></a>float&nbsp;</p>
<p id="p137617898084829"><a name="p137617898084829"></a><a name="p137617898084829"></a>Calculates the phase angle of the complex number <strong id="b1978958746084829"><a name="b1978958746084829"></a><a name="b1978958746084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1969726717084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p421717689084829"><a name="p421717689084829"></a><a name="p421717689084829"></a><a href="MATH.md#ga74f3429f1b860581f4d15bea90533fd5">cargl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p840622213084829"><a name="p840622213084829"></a><a name="p840622213084829"></a>long double&nbsp;</p>
<p id="p1232312951084829"><a name="p1232312951084829"></a><a name="p1232312951084829"></a>Calculates the phase angle of the complex number <strong id="b1130178803084829"><a name="b1130178803084829"></a><a name="b1130178803084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row84215393084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221112511084829"><a name="p1221112511084829"></a><a name="p1221112511084829"></a><a href="MATH.md#ga6c3d7c875ae93700b0a2a32db24b37d3">cimag</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p227793902084829"><a name="p227793902084829"></a><a name="p227793902084829"></a>double&nbsp;</p>
<p id="p1787782590084829"><a name="p1787782590084829"></a><a name="p1787782590084829"></a>Calculates the imaginary part of the complex number <strong id="b609175497084829"><a name="b609175497084829"></a><a name="b609175497084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1047143166084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1052845836084829"><a name="p1052845836084829"></a><a name="p1052845836084829"></a><a href="MATH.md#gaac22dc2fffc4326595ff807d441f0675">cimagf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1117521652084829"><a name="p1117521652084829"></a><a name="p1117521652084829"></a>float&nbsp;</p>
<p id="p641466035084829"><a name="p641466035084829"></a><a name="p641466035084829"></a>Calculates the imaginary part of the complex number <strong id="b1098137537084829"><a name="b1098137537084829"></a><a name="b1098137537084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1444984669084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p770053406084829"><a name="p770053406084829"></a><a name="p770053406084829"></a><a href="MATH.md#ga4237f0401b8123eaec284c995ced4b04">cimagl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193973454084829"><a name="p1193973454084829"></a><a name="p1193973454084829"></a>long double&nbsp;</p>
<p id="p76413477084829"><a name="p76413477084829"></a><a name="p76413477084829"></a>Calculates the imaginary part of the complex number <strong id="b1291054607084829"><a name="b1291054607084829"></a><a name="b1291054607084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1591299555084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1006051806084829"><a name="p1006051806084829"></a><a name="p1006051806084829"></a><a href="MATH.md#ga6fb30f37aa43eb2e0199ffdc38cac18a">conj</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1393905210084829"><a name="p1393905210084829"></a><a name="p1393905210084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p435037235084829"><a name="p435037235084829"></a><a name="p435037235084829"></a>Calculates the conjugate of the complex number <strong id="b700738066084829"><a name="b700738066084829"></a><a name="b700738066084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row908683319084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p217677688084829"><a name="p217677688084829"></a><a name="p217677688084829"></a><a href="MATH.md#ga471ecd8d25e722ecae510a635c1a2c53">conjf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809740162084829"><a name="p1809740162084829"></a><a name="p1809740162084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1669497150084829"><a name="p1669497150084829"></a><a name="p1669497150084829"></a>Calculates the conjugate of the complex number <strong id="b1261718301084829"><a name="b1261718301084829"></a><a name="b1261718301084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row678062067084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1940925185084829"><a name="p1940925185084829"></a><a name="p1940925185084829"></a><a href="MATH.md#ga5156353f4650ed7ee06b152790c1558b">conjl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1320330987084829"><a name="p1320330987084829"></a><a name="p1320330987084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p226256585084829"><a name="p226256585084829"></a><a name="p226256585084829"></a>Calculates the conjugate of the complex number <strong id="b1014594156084829"><a name="b1014594156084829"></a><a name="b1014594156084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row1584159718084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148761746084829"><a name="p148761746084829"></a><a name="p148761746084829"></a><a href="MATH.md#gac10f86edf0994d0ee834768633be644e">cproj</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242088077084829"><a name="p1242088077084829"></a><a name="p1242088077084829"></a>double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1689582149084829"><a name="p1689582149084829"></a><a name="p1689582149084829"></a>Calculates the projection of the complex number <strong id="b229040318084829"><a name="b229040318084829"></a><a name="b229040318084829"></a>z</strong> onto the Riemann sphere. </p>
</td>
</tr>
<tr id="row1175280658084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1919499576084829"><a name="p1919499576084829"></a><a name="p1919499576084829"></a><a href="MATH.md#ga9f435a71e44dd1e13eca358e2ca530e6">cprojf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p458411055084829"><a name="p458411055084829"></a><a name="p458411055084829"></a>float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p1956670939084829"><a name="p1956670939084829"></a><a name="p1956670939084829"></a>Calculates the projection of the complex number <strong id="b1194574613084829"><a name="b1194574613084829"></a><a name="b1194574613084829"></a>z</strong> onto the Riemann sphere. </p>
</td>
</tr>
<tr id="row1951954311084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1251503385084829"><a name="p1251503385084829"></a><a name="p1251503385084829"></a><a href="MATH.md#ga2cc437f3ab8e77dbd8fb024c66474915">cprojl</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p986021684084829"><a name="p986021684084829"></a><a name="p986021684084829"></a>long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a>&nbsp;</p>
<p id="p436554116084829"><a name="p436554116084829"></a><a name="p436554116084829"></a>Calculates the projection of the complex number <strong id="b1497961181084829"><a name="b1497961181084829"></a><a name="b1497961181084829"></a>z</strong> onto the Riemann sphere. </p>
</td>
</tr>
<tr id="row1752515630084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p974692738084829"><a name="p974692738084829"></a><a name="p974692738084829"></a><a href="MATH.md#ga24b1a511efdb973354d81646c5c3bb81">creal</a> (double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278859374084829"><a name="p1278859374084829"></a><a name="p1278859374084829"></a>double&nbsp;</p>
<p id="p256135245084829"><a name="p256135245084829"></a><a name="p256135245084829"></a>Calculates the real part of the complex number <strong id="b1497824347084829"><a name="b1497824347084829"></a><a name="b1497824347084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row182707269084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1458892058084829"><a name="p1458892058084829"></a><a name="p1458892058084829"></a><a href="MATH.md#gad052a3eb4d9f32153173e6bcea9e42ce">crealf</a> (float <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947316963084829"><a name="p1947316963084829"></a><a name="p1947316963084829"></a>float&nbsp;</p>
<p id="p2144227985084829"><a name="p2144227985084829"></a><a name="p2144227985084829"></a>Calculates the real part of the complex number <strong id="b413038337084829"><a name="b413038337084829"></a><a name="b413038337084829"></a>z</strong>. </p>
</td>
</tr>
<tr id="row16846834084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879330262084829"><a name="p879330262084829"></a><a name="p879330262084829"></a><a href="MATH.md#ga4ee2baa54a4e51877c59527d2be1a0da">creall</a> (long double <a href="MATH.md#ga0fa4878c968311979d497ccc322e0b9b">complex</a> z)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380083658084829"><a name="p380083658084829"></a><a name="p380083658084829"></a>long double&nbsp;</p>
<p id="p38131433084829"><a name="p38131433084829"></a><a name="p38131433084829"></a>Calculates the real part of the complex number <strong id="b1538964287084829"><a name="b1538964287084829"></a><a name="b1538964287084829"></a>z</strong>. </p>
</td>
</tr>
</tbody>
</table>

