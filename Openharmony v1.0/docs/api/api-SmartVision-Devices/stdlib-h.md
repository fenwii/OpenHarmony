# stdlib.h<a name="ZH-CN_TOPIC_0000001054948039"></a>

## **Overview**<a name="section854068182084832"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Declares common functions used for performing I/O operations. 

You can use the functions provided in this file to complete string conversion, random number generation, array sorting, and tree-related operations during development. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section58478781084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1665428802084832"></a>
<table><thead align="left"><tr id="row127512637084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1680630344084832"><a name="p1680630344084832"></a><a name="p1680630344084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p928033290084832"><a name="p928033290084832"></a><a name="p928033290084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1748123506084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655384254084832"><a name="p655384254084832"></a><a name="p655384254084832"></a><a href="div_t.md">div_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2093190203084832"><a name="p2093190203084832"></a><a name="p2093190203084832"></a>Defines the structures of the division operation result. </p>
</td>
</tr>
<tr id="row105110466084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p556094150084832"><a name="p556094150084832"></a><a name="p556094150084832"></a><a href="ldiv_t.md">ldiv_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307598728084832"><a name="p307598728084832"></a><a name="p307598728084832"></a>Defines the structures of the division operation result. </p>
</td>
</tr>
<tr id="row540001421084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1833860202084832"><a name="p1833860202084832"></a><a name="p1833860202084832"></a><a href="lldiv_t.md">lldiv_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p474333151084832"><a name="p474333151084832"></a><a name="p474333151084832"></a>Defines the structures of the division operation result. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table836229930084832"></a>
<table><thead align="left"><tr id="row714379489084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1505502967084832"><a name="p1505502967084832"></a><a name="p1505502967084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p306642401084832"><a name="p306642401084832"></a><a name="p306642401084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1209749793084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748058286084832"><a name="p1748058286084832"></a><a name="p1748058286084832"></a><a href="UTILS.md#gad228deceea1bac4d9f171f647c265059">atoi</a> (const char *nptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798207353084832"><a name="p798207353084832"></a><a name="p798207353084832"></a>int&nbsp;</p>
<p id="p1722566886084832"><a name="p1722566886084832"></a><a name="p1722566886084832"></a>Converts an input string to an integer. </p>
</td>
</tr>
<tr id="row1112957820084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p574025708084832"><a name="p574025708084832"></a><a name="p574025708084832"></a><a href="UTILS.md#ga185551efd32d058ef290ebe2d144219f">atol</a> (const char *nptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2100424477084832"><a name="p2100424477084832"></a><a name="p2100424477084832"></a>long&nbsp;</p>
<p id="p494946342084832"><a name="p494946342084832"></a><a name="p494946342084832"></a>Converts an input string to a long integer. </p>
</td>
</tr>
<tr id="row717775844084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740509951084832"><a name="p740509951084832"></a><a name="p740509951084832"></a><a href="UTILS.md#ga5d0555f6ac42472671281e5903244b7b">atoll</a> (const char *nptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911654043084832"><a name="p911654043084832"></a><a name="p911654043084832"></a>long long&nbsp;</p>
<p id="p348757352084832"><a name="p348757352084832"></a><a name="p348757352084832"></a>Converts a string to an 8-byte long integer. </p>
</td>
</tr>
<tr id="row1351061174084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p231722885084832"><a name="p231722885084832"></a><a name="p231722885084832"></a><a href="UTILS.md#gac03da055b7752247b034fb582cb4372f">atof</a> (const char *nptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p704423958084832"><a name="p704423958084832"></a><a name="p704423958084832"></a>double&nbsp;</p>
<p id="p976155908084832"><a name="p976155908084832"></a><a name="p976155908084832"></a>Converts an input string to a double-precision floating-point number. </p>
</td>
</tr>
<tr id="row676874445084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1161422051084832"><a name="p1161422051084832"></a><a name="p1161422051084832"></a><a href="UTILS.md#ga2370632318c3797a314f8eb62d37947c">strtof</a> (const char *nptr, char **endptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2045658898084832"><a name="p2045658898084832"></a><a name="p2045658898084832"></a>float&nbsp;</p>
<p id="p352201677084832"><a name="p352201677084832"></a><a name="p352201677084832"></a>Converts an input string to a floating-point number. </p>
</td>
</tr>
<tr id="row1992642683084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106188049084832"><a name="p1106188049084832"></a><a name="p1106188049084832"></a><a href="UTILS.md#ga0c17a0b44f572941d9f73518f99ea7ed">strtod</a> (const char *nptr, char **endptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1410959504084832"><a name="p1410959504084832"></a><a name="p1410959504084832"></a>double&nbsp;</p>
<p id="p1795710674084832"><a name="p1795710674084832"></a><a name="p1795710674084832"></a>Converts a string to <strong id="b897407324084832"><a name="b897407324084832"></a><a name="b897407324084832"></a>double</strong>. </p>
</td>
</tr>
<tr id="row1920348406084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683345467084832"><a name="p1683345467084832"></a><a name="p1683345467084832"></a><a href="UTILS.md#gad2ed05594fb04a126627c0fd5c7e2232">strtold</a> (const char *nptr, char **endptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p739945931084832"><a name="p739945931084832"></a><a name="p739945931084832"></a>long double&nbsp;</p>
<p id="p1918766759084832"><a name="p1918766759084832"></a><a name="p1918766759084832"></a>Converts a string to <strong id="b2109471875084832"><a name="b2109471875084832"></a><a name="b2109471875084832"></a>long double</strong>. </p>
</td>
</tr>
<tr id="row1336163533084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1026574721084832"><a name="p1026574721084832"></a><a name="p1026574721084832"></a><a href="UTILS.md#ga311071298c2fe3e5d7057f396a6acfdc">strtol</a> (const char *nptr, char **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380625717084832"><a name="p380625717084832"></a><a name="p380625717084832"></a>long&nbsp;</p>
<p id="p1698089987084832"><a name="p1698089987084832"></a><a name="p1698089987084832"></a>Converts a string to a long integer according to the given <strong id="b382005766084832"><a name="b382005766084832"></a><a name="b382005766084832"></a>base</strong>. </p>
</td>
</tr>
<tr id="row2085102307084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1846766153084832"><a name="p1846766153084832"></a><a name="p1846766153084832"></a><a href="UTILS.md#ga6d257fc3f00865d0556ed7327c312b55">strtoul</a> (const char *nptr, char **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p595943290084832"><a name="p595943290084832"></a><a name="p595943290084832"></a>unsigned long&nbsp;</p>
<p id="p44100387084832"><a name="p44100387084832"></a><a name="p44100387084832"></a>Converts a string to an unsigned long integer according to the given <strong id="b725544892084832"><a name="b725544892084832"></a><a name="b725544892084832"></a>base</strong>. </p>
</td>
</tr>
<tr id="row1253348033084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806731374084832"><a name="p1806731374084832"></a><a name="p1806731374084832"></a><a href="UTILS.md#gafb901aa665b7e2e3e27025ca77fecd1b">strtoll</a> (const char *nptr, char **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1123597797084832"><a name="p1123597797084832"></a><a name="p1123597797084832"></a>long long&nbsp;</p>
<p id="p1569635353084832"><a name="p1569635353084832"></a><a name="p1569635353084832"></a>Converts a string to a long long integer according to the given <strong id="b968294623084832"><a name="b968294623084832"></a><a name="b968294623084832"></a>base</strong>. </p>
</td>
</tr>
<tr id="row1300064742084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p42939229084832"><a name="p42939229084832"></a><a name="p42939229084832"></a><a href="UTILS.md#gae5835422eb2dfc17ea8deb3b15bcc541">strtoull</a> (const char *nptr, char **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087519029084832"><a name="p1087519029084832"></a><a name="p1087519029084832"></a>unsigned long long&nbsp;</p>
<p id="p2076296619084832"><a name="p2076296619084832"></a><a name="p2076296619084832"></a>Converts a string to an unsigned long long integer according to the given <strong id="b1978432686084832"><a name="b1978432686084832"></a><a name="b1978432686084832"></a>base</strong>. </p>
</td>
</tr>
<tr id="row136827969084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p208394531084832"><a name="p208394531084832"></a><a name="p208394531084832"></a><a href="UTILS.md#gae23144bcbb8e3742b00eb687c36654d1">rand</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064072032084832"><a name="p2064072032084832"></a><a name="p2064072032084832"></a>int&nbsp;</p>
<p id="p430704822084832"><a name="p430704822084832"></a><a name="p430704822084832"></a>Generates a pseudo-random number. </p>
</td>
</tr>
<tr id="row603041640084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p379859689084832"><a name="p379859689084832"></a><a name="p379859689084832"></a><a href="UTILS.md#ga83a727cc697aea22e24cad5f39198dd2">srand</a> (unsigned int seed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1590042034084832"><a name="p1590042034084832"></a><a name="p1590042034084832"></a>void&nbsp;</p>
<p id="p1400044291084832"><a name="p1400044291084832"></a><a name="p1400044291084832"></a>Initializes a random number generator. </p>
</td>
</tr>
<tr id="row791044016084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1028840323084832"><a name="p1028840323084832"></a><a name="p1028840323084832"></a><a href="UTILS.md#ga7ac38fce3243a7dcf448301ee9ffd392">malloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023808841084832"><a name="p1023808841084832"></a><a name="p1023808841084832"></a>void *&nbsp;</p>
<p id="p2141908212084832"><a name="p2141908212084832"></a><a name="p2141908212084832"></a>Dynamically allocates a memory block of <strong id="b1777177994084832"><a name="b1777177994084832"></a><a name="b1777177994084832"></a>size</strong>. </p>
</td>
</tr>
<tr id="row746486176084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790813357084832"><a name="p790813357084832"></a><a name="p790813357084832"></a><a href="UTILS.md#ga62b7798461bd461da64c5f9d35feddf7">calloc</a> (size_t nmemb, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909345304084832"><a name="p909345304084832"></a><a name="p909345304084832"></a>void *&nbsp;</p>
<p id="p1879870317084832"><a name="p1879870317084832"></a><a name="p1879870317084832"></a>Dynamically allocates <strong id="b1836457587084832"><a name="b1836457587084832"></a><a name="b1836457587084832"></a>nmemb</strong> memory blocks of <strong id="b1029201292084832"><a name="b1029201292084832"></a><a name="b1029201292084832"></a>size</strong>. </p>
</td>
</tr>
<tr id="row1769670915084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1947998272084832"><a name="p1947998272084832"></a><a name="p1947998272084832"></a><a href="UTILS.md#ga1a6b5e8d2f1c37e5b43e4345586075be">realloc</a> (void *ptr, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p567818960084832"><a name="p567818960084832"></a><a name="p567818960084832"></a>void *&nbsp;</p>
<p id="p1113211466084832"><a name="p1113211466084832"></a><a name="p1113211466084832"></a>Changes the size of the memory block pointed to by <strong id="b1688279842084832"><a name="b1688279842084832"></a><a name="b1688279842084832"></a>ptr</strong> to <strong id="b1935923273084832"><a name="b1935923273084832"></a><a name="b1935923273084832"></a>size</strong> bytes. </p>
</td>
</tr>
<tr id="row1303731371084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33880578084832"><a name="p33880578084832"></a><a name="p33880578084832"></a><a href="UTILS.md#gafbedc913aa4651b3c3b4b3aecd9b4711">free</a> (void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874506695084832"><a name="p874506695084832"></a><a name="p874506695084832"></a>void&nbsp;</p>
<p id="p2137545266084832"><a name="p2137545266084832"></a><a name="p2137545266084832"></a>Releases the memory space pointed to by <strong id="b539100703084832"><a name="b539100703084832"></a><a name="b539100703084832"></a>ptr</strong>. </p>
</td>
</tr>
<tr id="row445301393084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p864404086084832"><a name="p864404086084832"></a><a name="p864404086084832"></a><a href="UTILS.md#ga7d78319026a43c0a5f942436ad3f09a1">abort</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269857679084832"><a name="p269857679084832"></a><a name="p269857679084832"></a>_Noreturn void&nbsp;</p>
<p id="p685761061084832"><a name="p685761061084832"></a><a name="p685761061084832"></a>Terminates an abnormal process and sends the <strong id="b721588320084832"><a name="b721588320084832"></a><a name="b721588320084832"></a>SIGABRT</strong> signal to the caller. </p>
</td>
</tr>
<tr id="row1807323102084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1134742345084832"><a name="p1134742345084832"></a><a name="p1134742345084832"></a><a href="UTILS.md#ga7fd89c82095df80e5e12d6b2834a2acc">atexit</a> (void(*func)(void))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296076036084832"><a name="p1296076036084832"></a><a name="p1296076036084832"></a>int&nbsp;</p>
<p id="p196059231084832"><a name="p196059231084832"></a><a name="p196059231084832"></a>Registers a termination function. </p>
</td>
</tr>
<tr id="row82208269084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970958983084832"><a name="p1970958983084832"></a><a name="p1970958983084832"></a><a href="UTILS.md#ga55e99c539cf7723ec15e856b7e0a8cee">exit</a> (int status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1632314361084832"><a name="p1632314361084832"></a><a name="p1632314361084832"></a>void&nbsp;</p>
<p id="p1730600708084832"><a name="p1730600708084832"></a><a name="p1730600708084832"></a>Terminates the calling process, clears the used memory space and various data structures in the kernel, and sends the process end status to the parent process. All functions registered with atexit and on_exit are called in the reverse order. </p>
</td>
</tr>
<tr id="row2074483036084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1310015515084832"><a name="p1310015515084832"></a><a name="p1310015515084832"></a><a href="UTILS.md#gabc6595dbf6880c71628fecf0dbb23d66">getenv</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p547927553084832"><a name="p547927553084832"></a><a name="p547927553084832"></a>char *&nbsp;</p>
<p id="p1535463229084832"><a name="p1535463229084832"></a><a name="p1535463229084832"></a>Obtains the value of an environment variable. </p>
</td>
</tr>
<tr id="row1096475904084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p376654299084832"><a name="p376654299084832"></a><a name="p376654299084832"></a><a href="UTILS.md#ga7631d470a867ad04b3272667ea4b643e">_Exit</a> (int status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319452151084832"><a name="p319452151084832"></a><a name="p319452151084832"></a>void&nbsp;</p>
<p id="p1666365721084832"><a name="p1666365721084832"></a><a name="p1666365721084832"></a>Terminates the calling process, clears the used memory space and various data structures in the kernel, and sends the process end status to the parent process. </p>
</td>
</tr>
<tr id="row1985344947084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1808503405084832"><a name="p1808503405084832"></a><a name="p1808503405084832"></a><a href="UTILS.md#ga901e482eabd0dedb19224cf731e15403">assert</a> (scalar expression)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507055619084832"><a name="p1507055619084832"></a><a name="p1507055619084832"></a>void&nbsp;</p>
<p id="p1602364485084832"><a name="p1602364485084832"></a><a name="p1602364485084832"></a>Aborts the program if assertion is false. </p>
</td>
</tr>
<tr id="row1212697377084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385793318084832"><a name="p385793318084832"></a><a name="p385793318084832"></a><a href="UTILS.md#ga131d5a62230be50122c603018fdb3fc2">secure_getenv</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p978435785084832"><a name="p978435785084832"></a><a name="p978435785084832"></a>char *&nbsp;</p>
<p id="p1060394490084832"><a name="p1060394490084832"></a><a name="p1060394490084832"></a>Obtains the value of an environment variable. </p>
</td>
</tr>
<tr id="row1825121899084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850256098084832"><a name="p1850256098084832"></a><a name="p1850256098084832"></a><a href="UTILS.md#gac1ed47dda697f858893a9a68882a9fab">bsearch</a> (const void *key, const void *base, size_t nel, size_t width, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p215358437084832"><a name="p215358437084832"></a><a name="p215358437084832"></a>void *&nbsp;</p>
<p id="p1928528991084832"><a name="p1928528991084832"></a><a name="p1928528991084832"></a>Searches for <strong id="b489968413084832"><a name="b489968413084832"></a><a name="b489968413084832"></a>key</strong> using the binary search algorithm from the array element <strong id="b361800692084832"><a name="b361800692084832"></a><a name="b361800692084832"></a>base[0]</strong> to <strong id="b422836185084832"><a name="b422836185084832"></a><a name="b422836185084832"></a>base[num-1]</strong>. </p>
</td>
</tr>
<tr id="row313543150084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2117943289084832"><a name="p2117943289084832"></a><a name="p2117943289084832"></a><a href="UTILS.md#ga56ba7474387aae0977ce6dbe9bef805f">qsort</a> (const void *base, size_t nel, size_t width, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p256346286084832"><a name="p256346286084832"></a><a name="p256346286084832"></a>void&nbsp;</p>
<p id="p394815720084832"><a name="p394815720084832"></a><a name="p394815720084832"></a>Sorts array elements <strong id="b269913543084832"><a name="b269913543084832"></a><a name="b269913543084832"></a>base[0]</strong> to <strong id="b1122418290084832"><a name="b1122418290084832"></a><a name="b1122418290084832"></a>base[num-1]</strong> based on the comparison rules of <strong id="b1838871198084832"><a name="b1838871198084832"></a><a name="b1838871198084832"></a>compar</strong>. </p>
</td>
</tr>
<tr id="row765004102084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1261077937084832"><a name="p1261077937084832"></a><a name="p1261077937084832"></a><a href="UTILS.md#gaf15d7205d8d10c4820f997ce5c526279">abs</a> (int i)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p276165981084832"><a name="p276165981084832"></a><a name="p276165981084832"></a>int&nbsp;</p>
<p id="p1611203407084832"><a name="p1611203407084832"></a><a name="p1611203407084832"></a>Obtains the absolute value of an integer value. </p>
</td>
</tr>
<tr id="row1040373189084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1403733101084832"><a name="p1403733101084832"></a><a name="p1403733101084832"></a><a href="UTILS.md#gac39409d0077cf980e4e6419bc6014d10">labs</a> (long i)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911387447084832"><a name="p1911387447084832"></a><a name="p1911387447084832"></a>long&nbsp;</p>
<p id="p335769059084832"><a name="p335769059084832"></a><a name="p335769059084832"></a>Calculates the absolute value of a long integer. </p>
</td>
</tr>
<tr id="row230683590084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p578838337084832"><a name="p578838337084832"></a><a name="p578838337084832"></a><a href="UTILS.md#ga7251caa2dd32261e7768d824c0a532c6">llabs</a> (long long i)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023795310084832"><a name="p1023795310084832"></a><a name="p1023795310084832"></a>long long&nbsp;</p>
<p id="p1909582844084832"><a name="p1909582844084832"></a><a name="p1909582844084832"></a>Calculates the absolute value of a long long integer. </p>
</td>
</tr>
<tr id="row1430343727084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886094066084832"><a name="p1886094066084832"></a><a name="p1886094066084832"></a><a href="UTILS.md#ga98cbdcca43b259bf545f16c72f07825b">div</a> (int numerator, int denominator)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284054480084832"><a name="p284054480084832"></a><a name="p284054480084832"></a><a href="div_t.md">div_t</a>&nbsp;</p>
<p id="p1375642757084832"><a name="p1375642757084832"></a><a name="p1375642757084832"></a>Calculates the quotient and remainder of an integer after division. </p>
</td>
</tr>
<tr id="row1135811021084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p880639760084832"><a name="p880639760084832"></a><a name="p880639760084832"></a><a href="UTILS.md#ga9ce9bebe15110c3774f311cd587dc543">ldiv</a> (long numerator, long denominator)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904883471084832"><a name="p904883471084832"></a><a name="p904883471084832"></a><a href="ldiv_t.md">ldiv_t</a>&nbsp;</p>
<p id="p1369135024084832"><a name="p1369135024084832"></a><a name="p1369135024084832"></a>Calculates the quotient and remainder of a long integer after division. </p>
</td>
</tr>
<tr id="row736863588084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p699392952084832"><a name="p699392952084832"></a><a name="p699392952084832"></a><a href="UTILS.md#ga28b92959777798288e1ac1def1c16ddc">lldiv</a> (long long numerator, long long denominator)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1324436832084832"><a name="p1324436832084832"></a><a name="p1324436832084832"></a><a href="lldiv_t.md">lldiv_t</a>&nbsp;</p>
<p id="p355490799084832"><a name="p355490799084832"></a><a name="p355490799084832"></a>Calculates the quotient and remainder of a long long integer after division. </p>
</td>
</tr>
<tr id="row1247197290084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2027083544084832"><a name="p2027083544084832"></a><a name="p2027083544084832"></a><a href="UTILS.md#ga10b28b2a9d994195623066c344fcf1fd">mblen</a> (const char *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611765442084832"><a name="p611765442084832"></a><a name="p611765442084832"></a>int&nbsp;</p>
<p id="p1002690792084832"><a name="p1002690792084832"></a><a name="p1002690792084832"></a>Obtains the number of bytes in the next multi-byte string. </p>
</td>
</tr>
<tr id="row19013180084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339657616084832"><a name="p339657616084832"></a><a name="p339657616084832"></a><a href="UTILS.md#ga6d2e39eeb319f32608b467c0c0ca1393">mbtowc</a> (wchar_t *pwc, const char *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1892211320084832"><a name="p1892211320084832"></a><a name="p1892211320084832"></a>int&nbsp;</p>
<p id="p1801291671084832"><a name="p1801291671084832"></a><a name="p1801291671084832"></a>Converts a string constant to a wide character. </p>
</td>
</tr>
<tr id="row1852174497084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911773264084832"><a name="p911773264084832"></a><a name="p911773264084832"></a><a href="UTILS.md#gab576ad05484aba7fe43b3d047a3fabb5">wctomb</a> (char *s, wchar_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p968190701084832"><a name="p968190701084832"></a><a name="p968190701084832"></a>int&nbsp;</p>
<p id="p127608051084832"><a name="p127608051084832"></a><a name="p127608051084832"></a>Converts a wide character to its multi-byte sequence and stores it in a character array. </p>
</td>
</tr>
<tr id="row897229330084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478308781084832"><a name="p478308781084832"></a><a name="p478308781084832"></a><a href="UTILS.md#ga95b89e577f091ba05d6403ff542c2164">mbstowcs</a> (wchar_t *dest, const char *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1095807620084832"><a name="p1095807620084832"></a><a name="p1095807620084832"></a>size_t&nbsp;</p>
<p id="p1740022235084832"><a name="p1740022235084832"></a><a name="p1740022235084832"></a>Converts a multi-byte string to a wide-character string. </p>
</td>
</tr>
<tr id="row944754627084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183168808084832"><a name="p1183168808084832"></a><a name="p1183168808084832"></a><a href="UTILS.md#gae7586ae6f537a5fd64c8c2d7c850e3be">wcstombs</a> (char *dest, const wchar_t *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p64291216084832"><a name="p64291216084832"></a><a name="p64291216084832"></a>size_t&nbsp;</p>
<p id="p1795419459084832"><a name="p1795419459084832"></a><a name="p1795419459084832"></a>Converts a wide-character string to a multi-byte string. </p>
</td>
</tr>
<tr id="row4388762084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p210800020084832"><a name="p210800020084832"></a><a name="p210800020084832"></a><a href="UTILS.md#gaed1e9c27ea92f5ae3a480059bf45c311">posix_memalign</a> (void **memptr, size_t alignment, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179859363084832"><a name="p1179859363084832"></a><a name="p1179859363084832"></a>int&nbsp;</p>
<p id="p833373072084832"><a name="p833373072084832"></a><a name="p833373072084832"></a>Allocates memory with the specified size based on the given <strong id="b88382980084832"><a name="b88382980084832"></a><a name="b88382980084832"></a>alignment</strong>. </p>
</td>
</tr>
<tr id="row1759575950084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p461315676084832"><a name="p461315676084832"></a><a name="p461315676084832"></a><a href="UTILS.md#ga1c8b16a3abcb4dc450a0a62b42c554dd">setenv</a> (const char *name, const char *value, int overwrite)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p245698113084832"><a name="p245698113084832"></a><a name="p245698113084832"></a>int&nbsp;</p>
<p id="p2022391208084832"><a name="p2022391208084832"></a><a name="p2022391208084832"></a>Add or change an environment variable. </p>
</td>
</tr>
<tr id="row784361885084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1135888441084832"><a name="p1135888441084832"></a><a name="p1135888441084832"></a><a href="UTILS.md#ga17a3a11d20a551951a4acbc3872b280c">unsetenv</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1128303864084832"><a name="p1128303864084832"></a><a name="p1128303864084832"></a>int&nbsp;</p>
<p id="p228380712084832"><a name="p228380712084832"></a><a name="p228380712084832"></a>Deletes an environment variable. </p>
</td>
</tr>
<tr id="row1387201459084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1366428870084832"><a name="p1366428870084832"></a><a name="p1366428870084832"></a><a href="UTILS.md#ga6abe6c5eb77aeaf05ad81a7425547d9e">mkstemp</a> (char *template)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1172250389084832"><a name="p1172250389084832"></a><a name="p1172250389084832"></a>int&nbsp;</p>
<p id="p88058464084832"><a name="p88058464084832"></a><a name="p88058464084832"></a>Creates and opens a unique temporary file. </p>
</td>
</tr>
<tr id="row1955466476084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p58320569084832"><a name="p58320569084832"></a><a name="p58320569084832"></a><a href="UTILS.md#ga691bcfdddb46ab9b43a91217a0ff77c9">mkostemp</a> (char *template, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p54461711084832"><a name="p54461711084832"></a><a name="p54461711084832"></a>int&nbsp;</p>
<p id="p732703358084832"><a name="p732703358084832"></a><a name="p732703358084832"></a>Creates and opens a unique temporary file. </p>
</td>
</tr>
<tr id="row1758005359084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1311685104084832"><a name="p1311685104084832"></a><a name="p1311685104084832"></a><a href="UTILS.md#ga4c366b8d0ad8a393cf6224b5fc9ee045">mkdtemp</a> (char *template)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121000261084832"><a name="p1121000261084832"></a><a name="p1121000261084832"></a>char *&nbsp;</p>
<p id="p874504239084832"><a name="p874504239084832"></a><a name="p874504239084832"></a>Creates a unique temporary directory based on <strong id="b1705043709084832"><a name="b1705043709084832"></a><a name="b1705043709084832"></a>template</strong>. </p>
</td>
</tr>
<tr id="row1052096750084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1405216050084832"><a name="p1405216050084832"></a><a name="p1405216050084832"></a><a href="UTILS.md#ga2959446c8426187f340f8d5a625bf2e6">getsubopt</a> (char **optionp, char *const *tokens, char **valuep)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p203499417084832"><a name="p203499417084832"></a><a name="p203499417084832"></a>int&nbsp;</p>
<p id="p157463452084832"><a name="p157463452084832"></a><a name="p157463452084832"></a>Processes the parameters of an option in the command line. </p>
</td>
</tr>
<tr id="row1253296739084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p640449153084832"><a name="p640449153084832"></a><a name="p640449153084832"></a><a href="UTILS.md#ga4d592bbc52a36404b05aa9ff5b7503c1">rand_r</a> (unsigned *seedp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772858591084832"><a name="p772858591084832"></a><a name="p772858591084832"></a>int&nbsp;</p>
<p id="p2006507283084832"><a name="p2006507283084832"></a><a name="p2006507283084832"></a>Generates a pseudo-random number. </p>
</td>
</tr>
<tr id="row414559647084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993618162084832"><a name="p993618162084832"></a><a name="p993618162084832"></a><a href="UTILS.md#gaae6b0f26f4a57df79f7c497a65d174d9">realpath</a> (const char *__restrict path, char *__restrict resolved)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820812200084832"><a name="p1820812200084832"></a><a name="p1820812200084832"></a>char *&nbsp;</p>
<p id="p402743314084832"><a name="p402743314084832"></a><a name="p402743314084832"></a>Obtains a normalized absolute path. </p>
</td>
</tr>
<tr id="row1352169936084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776088862084832"><a name="p776088862084832"></a><a name="p776088862084832"></a><a href="UTILS.md#ga350b5b3334c99bb57d2b39da0b2dd694">random</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312451093084832"><a name="p1312451093084832"></a><a name="p1312451093084832"></a>long int&nbsp;</p>
<p id="p2116173272084832"><a name="p2116173272084832"></a><a name="p2116173272084832"></a>Generates a pseudo-random number. </p>
</td>
</tr>
<tr id="row599585453084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429411021084832"><a name="p429411021084832"></a><a name="p429411021084832"></a><a href="UTILS.md#gaf1e7e3d144face36372f9ae8b18aa009">srandom</a> (unsigned int seed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1664846319084832"><a name="p1664846319084832"></a><a name="p1664846319084832"></a>void&nbsp;</p>
<p id="p840261363084832"><a name="p840261363084832"></a><a name="p840261363084832"></a>Initializes a random number generator. </p>
</td>
</tr>
<tr id="row761545988084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984427661084832"><a name="p984427661084832"></a><a name="p984427661084832"></a><a href="UTILS.md#ga9250c684f653b1bd715bab29d35d2423">initstate</a> (unsigned int seed, char *state, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656799385084832"><a name="p656799385084832"></a><a name="p656799385084832"></a>char *&nbsp;</p>
<p id="p1761483155084832"><a name="p1761483155084832"></a><a name="p1761483155084832"></a>Initializes a random number generator. </p>
</td>
</tr>
<tr id="row158232145084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780915773084832"><a name="p780915773084832"></a><a name="p780915773084832"></a><a href="UTILS.md#gaa4970d8361258d9b821ad83036a2da3a">setstate</a> (char *state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1587167794084832"><a name="p1587167794084832"></a><a name="p1587167794084832"></a>char *&nbsp;</p>
<p id="p2080220309084832"><a name="p2080220309084832"></a><a name="p2080220309084832"></a>Sets the current state list for subsequent random use. </p>
</td>
</tr>
<tr id="row1192665125084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363284998084832"><a name="p1363284998084832"></a><a name="p1363284998084832"></a><a href="UTILS.md#ga8a382cc6123c7cf09a144e28fdfe5bc1">putenv</a> (char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213695610084832"><a name="p213695610084832"></a><a name="p213695610084832"></a>int&nbsp;</p>
<p id="p1511554770084832"><a name="p1511554770084832"></a><a name="p1511554770084832"></a>Configures an environment variable. </p>
</td>
</tr>
<tr id="row1734189983084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1804332640084832"><a name="p1804332640084832"></a><a name="p1804332640084832"></a><a href="UTILS.md#gaba5e81f4ce55d1e02fb94974c382b63d">unlockpt</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1779277042084832"><a name="p1779277042084832"></a><a name="p1779277042084832"></a>int&nbsp;</p>
<p id="p866994824084832"><a name="p866994824084832"></a><a name="p866994824084832"></a>Unlocks the secondary pseudo terminal corresponding to a primary pseudo terminal. </p>
</td>
</tr>
<tr id="row314986015084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p193167523084832"><a name="p193167523084832"></a><a name="p193167523084832"></a><a href="UTILS.md#ga4602f14b8c8f146f93d72986341a27b7">ptsname</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623044572084832"><a name="p623044572084832"></a><a name="p623044572084832"></a>char *&nbsp;</p>
<p id="p1642126783084832"><a name="p1642126783084832"></a><a name="p1642126783084832"></a>Obtains the name of a pseudo terminal. </p>
</td>
</tr>
<tr id="row161901268084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772424012084832"><a name="p1772424012084832"></a><a name="p1772424012084832"></a><a href="UTILS.md#ga4045440e70229bdb726924f628f66d92">l64a</a> (long value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025804985084832"><a name="p1025804985084832"></a><a name="p1025804985084832"></a>char *&nbsp;</p>
<p id="p238726774084832"><a name="p238726774084832"></a><a name="p238726774084832"></a>Converts a long integer to a 64-bit ASCII string. </p>
</td>
</tr>
<tr id="row1522826158084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586314821084832"><a name="p586314821084832"></a><a name="p586314821084832"></a><a href="UTILS.md#gaed396b4eb37b2a1f5414f9c21749dadb">a64l</a> (const char *str64)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080388300084832"><a name="p1080388300084832"></a><a name="p1080388300084832"></a>long&nbsp;</p>
<p id="p2046510972084832"><a name="p2046510972084832"></a><a name="p2046510972084832"></a>Converts between a 32-bit long integer and a little-endian 64-bit ASCII string. </p>
</td>
</tr>
<tr id="row409601225084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p890785684084832"><a name="p890785684084832"></a><a name="p890785684084832"></a><a href="UTILS.md#gaf9329f9acef07ca14ea2256191c3ce74">drand48</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751198613084832"><a name="p1751198613084832"></a><a name="p1751198613084832"></a>double&nbsp;</p>
<p id="p603783100084832"><a name="p603783100084832"></a><a name="p603783100084832"></a>Obtains a random number. </p>
</td>
</tr>
<tr id="row1169456257084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p388796737084832"><a name="p388796737084832"></a><a name="p388796737084832"></a><a href="UTILS.md#ga95f02f2831f093c6e151f0b782f20e48">erand48</a> (unsigned short xsubi[3])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007918718084832"><a name="p1007918718084832"></a><a name="p1007918718084832"></a>double&nbsp;</p>
<p id="p1993808099084832"><a name="p1993808099084832"></a><a name="p1993808099084832"></a>Obtains a random number. </p>
</td>
</tr>
<tr id="row1386297176084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413948237084832"><a name="p1413948237084832"></a><a name="p1413948237084832"></a><a href="UTILS.md#gad20ddf22bece340e3036c60cad913250">lrand48</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1780732293084832"><a name="p1780732293084832"></a><a name="p1780732293084832"></a>long int&nbsp;</p>
<p id="p1393951329084832"><a name="p1393951329084832"></a><a name="p1393951329084832"></a>Generates pseudo-random numbers evenly distributed between [0, 2^31). </p>
</td>
</tr>
<tr id="row186320884084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p191842976084832"><a name="p191842976084832"></a><a name="p191842976084832"></a><a href="UTILS.md#gaae8f9c9ee0a49b3bd8bea3331dab500f">nrand48</a> (unsigned short xsubi[3])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p220048914084832"><a name="p220048914084832"></a><a name="p220048914084832"></a>long int&nbsp;</p>
<p id="p1168333290084832"><a name="p1168333290084832"></a><a name="p1168333290084832"></a>Generates pseudo-random numbers evenly distributed between [0, 2^31). </p>
</td>
</tr>
<tr id="row1399366671084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816398821084832"><a name="p816398821084832"></a><a name="p816398821084832"></a><a href="UTILS.md#ga9c450a7a3d4437e3d5f8def180f68103">mrand48</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p127788458084832"><a name="p127788458084832"></a><a name="p127788458084832"></a>long&nbsp;</p>
<p id="p1737488286084832"><a name="p1737488286084832"></a><a name="p1737488286084832"></a>Generates pseudo-random numbers evenly distributed between [-2^31, 2^31). </p>
</td>
</tr>
<tr id="row1759858520084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1162728712084832"><a name="p1162728712084832"></a><a name="p1162728712084832"></a><a href="UTILS.md#ga79163d3776f4009f0e7f1830f4be4d02">jrand48</a> (unsigned short xsubi[3])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147607415084832"><a name="p1147607415084832"></a><a name="p1147607415084832"></a>long&nbsp;</p>
<p id="p1140414589084832"><a name="p1140414589084832"></a><a name="p1140414589084832"></a>Generates pseudo-random numbers evenly distributed between [-2^31, 2^31). </p>
</td>
</tr>
<tr id="row580729380084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1819826249084832"><a name="p1819826249084832"></a><a name="p1819826249084832"></a><a href="UTILS.md#ga91c6acf8516086891c689926e49f1ddf">srand48</a> (long int seedval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1186802459084832"><a name="p1186802459084832"></a><a name="p1186802459084832"></a>void&nbsp;</p>
<p id="p1912569456084832"><a name="p1912569456084832"></a><a name="p1912569456084832"></a>Sets the start seed value for the pseudo-random number generator. </p>
</td>
</tr>
<tr id="row1354869398084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081920353084832"><a name="p1081920353084832"></a><a name="p1081920353084832"></a><a href="UTILS.md#ga0b86f7fc9964c291844e8112a367721c">seed48</a> (unsigned short[3])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754900888084832"><a name="p754900888084832"></a><a name="p754900888084832"></a>unsigned short *&nbsp;</p>
<p id="p367305418084832"><a name="p367305418084832"></a><a name="p367305418084832"></a>Generates an evenly distributed pseudo-random seed. </p>
</td>
</tr>
<tr id="row1750746684084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429309189084832"><a name="p429309189084832"></a><a name="p429309189084832"></a><a href="UTILS.md#ga71e0019171f5584bb6957867691c3e10">lcong48</a> (unsigned short param[7])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078859219084832"><a name="p1078859219084832"></a><a name="p1078859219084832"></a>void&nbsp;</p>
<p id="p146636918084832"><a name="p146636918084832"></a><a name="p146636918084832"></a>Sets the seed and related algorithm parameters for the pseudo-random number generator. </p>
</td>
</tr>
<tr id="row471476312084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1852137452084832"><a name="p1852137452084832"></a><a name="p1852137452084832"></a><a href="UTILS.md#ga3db0418e1e0258f6a8809286c291cc5b">mktemp</a> (char *template)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1419663635084832"><a name="p1419663635084832"></a><a name="p1419663635084832"></a>char *&nbsp;</p>
<p id="p1151185464084832"><a name="p1151185464084832"></a><a name="p1151185464084832"></a>Creates a unique temporary file name. </p>
</td>
</tr>
<tr id="row447391869084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p744776137084832"><a name="p744776137084832"></a><a name="p744776137084832"></a><a href="UTILS.md#gab962063e3bb487de132da3016e2c813c">mkstemps</a> (char *template, int suffixlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511750678084832"><a name="p1511750678084832"></a><a name="p1511750678084832"></a>int&nbsp;</p>
<p id="p2088309639084832"><a name="p2088309639084832"></a><a name="p2088309639084832"></a>Creates and opens a unique temporary file. </p>
</td>
</tr>
<tr id="row1377173608084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339213537084832"><a name="p339213537084832"></a><a name="p339213537084832"></a><a href="UTILS.md#gafab16d88038590bdb4900150d2791081">mkostemps</a> (char *template, int suffixlen, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1704800802084832"><a name="p1704800802084832"></a><a name="p1704800802084832"></a>int&nbsp;</p>
<p id="p1609664087084832"><a name="p1609664087084832"></a><a name="p1609664087084832"></a>Creates and opens a unique temporary file. </p>
</td>
</tr>
<tr id="row1485983088084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1598740522084832"><a name="p1598740522084832"></a><a name="p1598740522084832"></a><a href="UTILS.md#ga3d09e44a916600a38b367c1b6ebdf118">valloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498403698084832"><a name="p498403698084832"></a><a name="p498403698084832"></a>void *&nbsp;</p>
<p id="p1213374597084832"><a name="p1213374597084832"></a><a name="p1213374597084832"></a>Allocates memory with the specified size and aligns the allocated memory by page size. </p>
</td>
</tr>
<tr id="row2036301131084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p535230313084832"><a name="p535230313084832"></a><a name="p535230313084832"></a><a href="UTILS.md#ga888afe4104cd3bdc07445d8ed27b96bd">ecvt</a> (double number, int ndigits, int *decpt, int *sign)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1049925866084832"><a name="p1049925866084832"></a><a name="p1049925866084832"></a>char *&nbsp;</p>
<p id="p1838671203084832"><a name="p1838671203084832"></a><a name="p1838671203084832"></a>Converts a double-precision floating-point number into a string. </p>
</td>
</tr>
<tr id="row1367613689084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1446864869084832"><a name="p1446864869084832"></a><a name="p1446864869084832"></a><a href="UTILS.md#gaf2658700b7da33eea87761f928b102de">fcvt</a> (double number, int ndigits, int *decpt, int *sign)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1289756506084832"><a name="p1289756506084832"></a><a name="p1289756506084832"></a>char *&nbsp;</p>
<p id="p530326133084832"><a name="p530326133084832"></a><a name="p530326133084832"></a>Converts a floating-point number to a string. </p>
</td>
</tr>
<tr id="row1075333765084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1161452898084832"><a name="p1161452898084832"></a><a name="p1161452898084832"></a><a href="UTILS.md#gafabf46107539bb1ec32994c214b5eeba">gcvt</a> (double x, int n, char *b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896080795084832"><a name="p896080795084832"></a><a name="p896080795084832"></a>char *&nbsp;</p>
<p id="p2114985013084832"><a name="p2114985013084832"></a><a name="p2114985013084832"></a>Converts a floating-point number to a string. </p>
</td>
</tr>
</tbody>
</table>

