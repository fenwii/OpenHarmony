# wctype.h<a name="EN-US_TOPIC_0000001055707986"></a>

## **Overview**<a name="section2099845366084834"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Provides functions to detect, translate, and map wide characters. 

Wide characters are classified into the following types:  **alnum**,  **alpha**,  **upper**,  **lower**,  **digit**,  **xdigit**,  **graph**,  **cntrl**,  **punct**, and  **space**. You can use these functions to detect the type of wide characters and translate the type for the current locale  [LC\_CTYPE](io.md#ga07c66689961056725d7f50231d740ba9)  or a specified locale. You can use these functions to convert the case of wide characters, map the wide characters, and obtain the mapping descriptor for conversion. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1539543054084834"></a>

## Functions<a name="func-members"></a>

<a name="table1514730186084834"></a>
<table><thead align="left"><tr id="row1748385002084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1516023713084834"><a name="p1516023713084834"></a><a name="p1516023713084834"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1722859213084834"><a name="p1722859213084834"></a><a name="p1722859213084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1165020260084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242422474084834"><a name="p242422474084834"></a><a name="p242422474084834"></a><a href="utils.md#gadafb512a79ac9274486d6ddbbbd9d9ba">iswalnum</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093515948084834"><a name="p1093515948084834"></a><a name="p1093515948084834"></a>int </p>
<p id="p815648615084834"><a name="p815648615084834"></a><a name="p815648615084834"></a>Checks whether a wide character is a letter or digit. </p>
</td>
</tr>
<tr id="row1071126679084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797116376084834"><a name="p1797116376084834"></a><a name="p1797116376084834"></a><a href="utils.md#ga72477b4f142de340164deb7bf5a7ae7b">iswalpha</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555581518084834"><a name="p1555581518084834"></a><a name="p1555581518084834"></a>int </p>
<p id="p170337063084834"><a name="p170337063084834"></a><a name="p170337063084834"></a>Checks whether a wide character is a letter. </p>
</td>
</tr>
<tr id="row890911150084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p139035485084834"><a name="p139035485084834"></a><a name="p139035485084834"></a><a href="utils.md#ga934cbdaad02f3df1b03e566103a5a118">iswblank</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1212008512084834"><a name="p1212008512084834"></a><a name="p1212008512084834"></a>int </p>
<p id="p1132429817084834"><a name="p1132429817084834"></a><a name="p1132429817084834"></a>Checks whether a wide character is a space or tab character (\t). </p>
</td>
</tr>
<tr id="row1239210638084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1664647313084834"><a name="p1664647313084834"></a><a name="p1664647313084834"></a><a href="utils.md#ga35f4bb15841d36c759ab271aa8033ba8">iswcntrl</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463255313084834"><a name="p463255313084834"></a><a name="p463255313084834"></a>int </p>
<p id="p1671969373084834"><a name="p1671969373084834"></a><a name="p1671969373084834"></a>Checks whether a wide character is a control character. </p>
</td>
</tr>
<tr id="row1546681052084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p906536531084834"><a name="p906536531084834"></a><a name="p906536531084834"></a><a href="utils.md#ga972fbaff0c1d4b4e612c789b8532e9af">iswdigit</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261636789084834"><a name="p1261636789084834"></a><a name="p1261636789084834"></a>int </p>
<p id="p1801361560084834"><a name="p1801361560084834"></a><a name="p1801361560084834"></a>Checks whether a wide character is a decimal digit. </p>
</td>
</tr>
<tr id="row62432113084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1882671652084834"><a name="p1882671652084834"></a><a name="p1882671652084834"></a><a href="utils.md#ga27b090b588b25bacca79bd11926ce308">iswgraph</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p758504571084834"><a name="p758504571084834"></a><a name="p758504571084834"></a>int </p>
<p id="p1582820365084834"><a name="p1582820365084834"></a><a name="p1582820365084834"></a>Checks whether a wide character is visible. </p>
</td>
</tr>
<tr id="row2114086266084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823892369084834"><a name="p1823892369084834"></a><a name="p1823892369084834"></a><a href="utils.md#ga92c2a9aad2bf7e6c56a7c01597f59649">iswlower</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415044682084834"><a name="p415044682084834"></a><a name="p415044682084834"></a>int </p>
<p id="p591615422084834"><a name="p591615422084834"></a><a name="p591615422084834"></a>Checks whether a wide character is a lowercase letter. </p>
</td>
</tr>
<tr id="row1507482287084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p457107942084834"><a name="p457107942084834"></a><a name="p457107942084834"></a><a href="utils.md#ga3eef94f4b2065e786f96e231e871d521">iswprint</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2122035392084834"><a name="p2122035392084834"></a><a name="p2122035392084834"></a>int </p>
<p id="p184363735084834"><a name="p184363735084834"></a><a name="p184363735084834"></a>Checks whether a wide character is printable. </p>
</td>
</tr>
<tr id="row446795300084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p542137301084834"><a name="p542137301084834"></a><a name="p542137301084834"></a><a href="utils.md#gacf0bab8aa20334835ea1b55f715ddd64">iswpunct</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1818446575084834"><a name="p1818446575084834"></a><a name="p1818446575084834"></a>int </p>
<p id="p290236467084834"><a name="p290236467084834"></a><a name="p290236467084834"></a>Checks whether a wide character is a punctuation mark. </p>
</td>
</tr>
<tr id="row1101639386084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p937711727084834"><a name="p937711727084834"></a><a name="p937711727084834"></a><a href="utils.md#gaf9d04695802b960ca3765c72d73ddb7c">iswupper</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p613456857084834"><a name="p613456857084834"></a><a name="p613456857084834"></a>int </p>
<p id="p1675621044084834"><a name="p1675621044084834"></a><a name="p1675621044084834"></a>Checks whether a wide character is an uppercase letter. </p>
</td>
</tr>
<tr id="row1478913183084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1517333929084834"><a name="p1517333929084834"></a><a name="p1517333929084834"></a><a href="utils.md#ga4f1c74cab8bd862ddac6ad81a4e23f72">iswxdigit</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1604865948084834"><a name="p1604865948084834"></a><a name="p1604865948084834"></a>int </p>
<p id="p1633291813084834"><a name="p1633291813084834"></a><a name="p1633291813084834"></a>Checks whether a wide character is a hexadecimal digit. </p>
</td>
</tr>
<tr id="row1443128938084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p79078001084834"><a name="p79078001084834"></a><a name="p79078001084834"></a><a href="utils.md#gae7bade1da794a7950ad25da75e43ad39">iswctype</a> (wint_t wc, wctype_t desc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1524351497084834"><a name="p1524351497084834"></a><a name="p1524351497084834"></a>int </p>
<p id="p426138864084834"><a name="p426138864084834"></a><a name="p426138864084834"></a>Checks whether the character specified by <strong id="b1201747368084834"><a name="b1201747368084834"></a><a name="b1201747368084834"></a>wc</strong> belongs to the <strong id="b880488284084834"><a name="b880488284084834"></a><a name="b880488284084834"></a>desc</strong> class. </p>
</td>
</tr>
<tr id="row53241037084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1590243021084834"><a name="p1590243021084834"></a><a name="p1590243021084834"></a><a href="utils.md#gac1d7671abe2a106b481d5bb24717fd11">towctrans</a> (wint_t wc, <a href="utils.md#ga10b40cc6ecda73a91162017d2df251a3">wctrans_t</a> desc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751823728084834"><a name="p1751823728084834"></a><a name="p1751823728084834"></a>wint_t </p>
<p id="p1620617510084834"><a name="p1620617510084834"></a><a name="p1620617510084834"></a>Translates the type of a wide character based on the conversion mapping relationship. </p>
</td>
</tr>
<tr id="row413383902084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453524845084834"><a name="p453524845084834"></a><a name="p453524845084834"></a><a href="utils.md#gab9cd9fba7f8437d2ad5242baa25fd176">towlower</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1285638174084834"><a name="p1285638174084834"></a><a name="p1285638174084834"></a>wint_t </p>
<p id="p506983339084834"><a name="p506983339084834"></a><a name="p506983339084834"></a>Converts an uppercase wide character to lowercase. </p>
</td>
</tr>
<tr id="row306743046084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p297500223084834"><a name="p297500223084834"></a><a name="p297500223084834"></a><a href="utils.md#gaaf8d2b2d230df873695d41757d5889f9">towupper</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1473983314084834"><a name="p1473983314084834"></a><a name="p1473983314084834"></a>wint_t </p>
<p id="p920501741084834"><a name="p920501741084834"></a><a name="p920501741084834"></a>Converts a lowercase wide character to uppercase. </p>
</td>
</tr>
<tr id="row910888408084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35598783084834"><a name="p35598783084834"></a><a name="p35598783084834"></a><a href="utils.md#ga98df6598dc60588b24067b97225070ed">wctrans</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1413902599084834"><a name="p1413902599084834"></a><a name="p1413902599084834"></a><a href="utils.md#ga10b40cc6ecda73a91162017d2df251a3">wctrans_t</a> </p>
<p id="p8570963084834"><a name="p8570963084834"></a><a name="p8570963084834"></a>Determines a mapping which can map a wide character to another wide character. </p>
</td>
</tr>
<tr id="row362990612084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048439885084834"><a name="p1048439885084834"></a><a name="p1048439885084834"></a><a href="utils.md#gae8a9ddd29c6a369345a12c6cb93aabe1">wctype</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003044524084834"><a name="p1003044524084834"></a><a name="p1003044524084834"></a>wctype_t </p>
<p id="p1589773043084834"><a name="p1589773043084834"></a><a name="p1589773043084834"></a>Checks whether a wide character type exists in the <a href="io.md#ga07c66689961056725d7f50231d740ba9">LC_CTYPE</a> locale. </p>
</td>
</tr>
<tr id="row596508074084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662304310084834"><a name="p662304310084834"></a><a name="p662304310084834"></a><a href="utils.md#ga8d6ca21d11b21620ff32e32ebc5b251a">iswalnum_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1950459052084834"><a name="p1950459052084834"></a><a name="p1950459052084834"></a>int </p>
<p id="p117591614084834"><a name="p117591614084834"></a><a name="p117591614084834"></a>Checks whether a wide character is a letter or digit for the specified locale. </p>
</td>
</tr>
<tr id="row1221851836084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1979912602084834"><a name="p1979912602084834"></a><a name="p1979912602084834"></a><a href="utils.md#gadfbb99771f4af02201ef68fc2377164b">iswalpha_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p955692743084834"><a name="p955692743084834"></a><a name="p955692743084834"></a>int </p>
<p id="p756730207084834"><a name="p756730207084834"></a><a name="p756730207084834"></a>Checks whether a wide character is alphabetic for the specified locale. </p>
</td>
</tr>
<tr id="row2000256450084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1927862967084834"><a name="p1927862967084834"></a><a name="p1927862967084834"></a><a href="utils.md#ga7d5300cc6bbc4ba910a3f9b4d9da2f4d">iswblank_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854634175084834"><a name="p854634175084834"></a><a name="p854634175084834"></a>int </p>
<p id="p591590761084834"><a name="p591590761084834"></a><a name="p591590761084834"></a>Checks whether a wide character is a blank or <strong id="b420181951084834"><a name="b420181951084834"></a><a name="b420181951084834"></a>\t</strong> character for the specified locale. </p>
</td>
</tr>
<tr id="row836704471084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p856591055084834"><a name="p856591055084834"></a><a name="p856591055084834"></a><a href="utils.md#ga51c189ba9f96d6ed8207da1da81100ca">iswcntrl_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1690996578084834"><a name="p1690996578084834"></a><a name="p1690996578084834"></a>int </p>
<p id="p819293941084834"><a name="p819293941084834"></a><a name="p819293941084834"></a>Checks whether a wide character is a control character for the specified locale. </p>
</td>
</tr>
<tr id="row1331263695084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p87410379084834"><a name="p87410379084834"></a><a name="p87410379084834"></a><a href="utils.md#gab84fd3a86d300fc49af9d708431566a9">iswdigit_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p646594757084834"><a name="p646594757084834"></a><a name="p646594757084834"></a>int </p>
<p id="p782667173084834"><a name="p782667173084834"></a><a name="p782667173084834"></a>Checks whether a wide character is a decimal digit for the specified locale. </p>
</td>
</tr>
<tr id="row801384327084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832356097084834"><a name="p832356097084834"></a><a name="p832356097084834"></a><a href="utils.md#gad7529291433b9e8f5e68caada7572244">iswgraph_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1612729493084834"><a name="p1612729493084834"></a><a name="p1612729493084834"></a>int </p>
<p id="p2126810579084834"><a name="p2126810579084834"></a><a name="p2126810579084834"></a>Checks whether a wide character is visible for the specified locale. </p>
</td>
</tr>
<tr id="row450044527084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35199908084834"><a name="p35199908084834"></a><a name="p35199908084834"></a><a href="utils.md#ga944498fac122e95a2da80137e7fffcb4">iswlower_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1489232608084834"><a name="p1489232608084834"></a><a name="p1489232608084834"></a>int </p>
<p id="p2006388677084834"><a name="p2006388677084834"></a><a name="p2006388677084834"></a>Checks whether a wide character is in lowercase for the specified locale. </p>
</td>
</tr>
<tr id="row1876756365084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024283754084834"><a name="p1024283754084834"></a><a name="p1024283754084834"></a><a href="utils.md#gacd7a8387b98672ae64f222072eefd38e">iswprint_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197612491084834"><a name="p197612491084834"></a><a name="p197612491084834"></a>int </p>
<p id="p1052747756084834"><a name="p1052747756084834"></a><a name="p1052747756084834"></a>Checks whether a wide character is printable for the specified locale. </p>
</td>
</tr>
<tr id="row38909682084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1303935536084834"><a name="p1303935536084834"></a><a name="p1303935536084834"></a><a href="utils.md#gad355af93606bf5c7688518d78a7c017c">iswpunct_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p714991925084834"><a name="p714991925084834"></a><a name="p714991925084834"></a>int </p>
<p id="p702858478084834"><a name="p702858478084834"></a><a name="p702858478084834"></a>Checks whether <strong id="b1359451554084834"><a name="b1359451554084834"></a><a name="b1359451554084834"></a>wc</strong> is a punctuation wide character for the specified locale. </p>
</td>
</tr>
<tr id="row2029226177084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1010998690084834"><a name="p1010998690084834"></a><a name="p1010998690084834"></a><a href="utils.md#gafb90e73f1be310ac1fe22f0d652838bc">iswspace</a> (wint_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367740425084834"><a name="p367740425084834"></a><a name="p367740425084834"></a>int </p>
<p id="p1027734305084834"><a name="p1027734305084834"></a><a name="p1027734305084834"></a>Checks whether a wide character belongs to the wide-character class <strong id="b909753992084834"><a name="b909753992084834"></a><a name="b909753992084834"></a>space</strong>. </p>
</td>
</tr>
<tr id="row1171039547084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p950379629084834"><a name="p950379629084834"></a><a name="p950379629084834"></a><a href="utils.md#gac9068379860381e27a47831612a85c25">iswspace_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p188519295084834"><a name="p188519295084834"></a><a name="p188519295084834"></a>int </p>
<p id="p1491706114084834"><a name="p1491706114084834"></a><a name="p1491706114084834"></a>Checks whether a wide character belongs to the wide-character class <strong id="b1828415679084834"><a name="b1828415679084834"></a><a name="b1828415679084834"></a>space</strong> for the specified locale. </p>
</td>
</tr>
<tr id="row330741008084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901592076084834"><a name="p1901592076084834"></a><a name="p1901592076084834"></a><a href="utils.md#ga4f73f2368e29bb2fc350479157987bc8">iswupper_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060006948084834"><a name="p1060006948084834"></a><a name="p1060006948084834"></a>int </p>
<p id="p245622217084834"><a name="p245622217084834"></a><a name="p245622217084834"></a>Checks whether a wide character is in uppercase for the specified locale. </p>
</td>
</tr>
<tr id="row264554648084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476527472084834"><a name="p476527472084834"></a><a name="p476527472084834"></a><a href="utils.md#ga2355dbfdaa44cb73ffd0216f97a7ad93">iswxdigit_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445369964084834"><a name="p1445369964084834"></a><a name="p1445369964084834"></a>int </p>
<p id="p1559762981084834"><a name="p1559762981084834"></a><a name="p1559762981084834"></a>Checks whether a wide character is a hexadecimal digit for the specified locale. </p>
</td>
</tr>
<tr id="row1387478527084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p162645229084834"><a name="p162645229084834"></a><a name="p162645229084834"></a><a href="utils.md#ga0f3b0048ef4d82840c1f7d1c78e25e6b">iswctype_l</a> (wint_t wc, wctype_t desc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201196898084834"><a name="p1201196898084834"></a><a name="p1201196898084834"></a>int </p>
<p id="p457220824084834"><a name="p457220824084834"></a><a name="p457220824084834"></a>Checks whether the character specified by <strong id="b528627835084834"><a name="b528627835084834"></a><a name="b528627835084834"></a>wc</strong> belongs to the <strong id="b1621174959084834"><a name="b1621174959084834"></a><a name="b1621174959084834"></a>desc</strong> class for the specified locale. </p>
</td>
</tr>
<tr id="row826034651084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1114387122084834"><a name="p1114387122084834"></a><a name="p1114387122084834"></a><a href="utils.md#ga6333139346611f59c603f70b61b521b5">towlower_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p260633494084834"><a name="p260633494084834"></a><a name="p260633494084834"></a>wint_t </p>
<p id="p687401029084834"><a name="p687401029084834"></a><a name="p687401029084834"></a>Converts an uppercase wide character to lowercase for the specified locale. </p>
</td>
</tr>
<tr id="row1064054032084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p124236512084834"><a name="p124236512084834"></a><a name="p124236512084834"></a><a href="utils.md#gac01816aef7bc2050e1b19db17a26bae8">towupper_l</a> (wint_t wc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149701396084834"><a name="p149701396084834"></a><a name="p149701396084834"></a>wint_t </p>
<p id="p1279478838084834"><a name="p1279478838084834"></a><a name="p1279478838084834"></a>Converts a lowercase wide character to uppercase for the specified locale. </p>
</td>
</tr>
<tr id="row1617378857084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p42559169084834"><a name="p42559169084834"></a><a name="p42559169084834"></a><a href="utils.md#gaa65f72b343b0d847933e6dbb7454a915">towctrans_l</a> (wint_t wc, wctype_t desc, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315521554084834"><a name="p315521554084834"></a><a name="p315521554084834"></a>wint_t </p>
<p id="p744493548084834"><a name="p744493548084834"></a><a name="p744493548084834"></a>Translates the type of a wide character based on the translation mapping relationship for the specified locale. </p>
</td>
</tr>
<tr id="row1357823071084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p270396993084834"><a name="p270396993084834"></a><a name="p270396993084834"></a><a href="utils.md#ga85e85bc84a644c3a0686fd6e4cfd96d7">wctrans_l</a> (const char *name, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p241125124084834"><a name="p241125124084834"></a><a name="p241125124084834"></a><a href="utils.md#ga10b40cc6ecda73a91162017d2df251a3">wctrans_t</a> </p>
<p id="p1577644352084834"><a name="p1577644352084834"></a><a name="p1577644352084834"></a>Determines a mapping which can map a wide character to another wide character. </p>
</td>
</tr>
<tr id="row1983158290084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451066142084834"><a name="p451066142084834"></a><a name="p451066142084834"></a><a href="utils.md#gae43cf599bd1eb5674ed9cc17870f7472">wctype_l</a> (const char *name, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p52199928084834"><a name="p52199928084834"></a><a name="p52199928084834"></a>wctype_t </p>
<p id="p1569384530084834"><a name="p1569384530084834"></a><a name="p1569384530084834"></a>Checks whether a wide character type exists for the specified locale. </p>
</td>
</tr>
</tbody>
</table>

