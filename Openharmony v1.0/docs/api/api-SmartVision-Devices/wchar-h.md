# wchar.h<a name="ZH-CN_TOPIC_0000001054748015"></a>

## **Overview**<a name="section1297391930084834"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Declares commonly used functions related to wide characters. 

You can use functions provided in this file to perform operations such as reading, writing, comparing, concatenating, copying, and searching wide characters. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section680326190084834"></a>

## Functions<a name="func-members"></a>

<a name="table615871167084834"></a>
<table><thead align="left"><tr id="row1970225323084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p617083537084834"><a name="p617083537084834"></a><a name="p617083537084834"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p922726369084834"><a name="p922726369084834"></a><a name="p922726369084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row167638882084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393971376084834"><a name="p1393971376084834"></a><a name="p1393971376084834"></a><a href="UTILS.md#gae6b223ed61020ed2abf0279af175b203">wcscpy</a> (wchar_t *dest, const wchar_t *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935171726084834"><a name="p1935171726084834"></a><a name="p1935171726084834"></a>wchar_t *&nbsp;</p>
<p id="p1391496898084834"><a name="p1391496898084834"></a><a name="p1391496898084834"></a>Copies the wide characters pointed to by <strong id="b1313042429084834"><a name="b1313042429084834"></a><a name="b1313042429084834"></a>src</strong> to the wide character array pointed to by <strong id="b1113713588084834"><a name="b1113713588084834"></a><a name="b1113713588084834"></a>dest</strong>, including the terminating null character <strong id="b1105155581084834"><a name="b1105155581084834"></a><a name="b1105155581084834"></a>'\0'</strong>. . </p>
</td>
</tr>
<tr id="row1299309393084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196617395084834"><a name="p196617395084834"></a><a name="p196617395084834"></a><a href="UTILS.md#gab1f03e735cf92afa01bef89682008c9b">wcsncpy</a> (wchar_t *dest, const wchar_t *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p136819028084834"><a name="p136819028084834"></a><a name="p136819028084834"></a>wchar_t *&nbsp;</p>
<p id="p692848306084834"><a name="p692848306084834"></a><a name="p692848306084834"></a>Copies the first <strong id="b146388962084834"><a name="b146388962084834"></a><a name="b146388962084834"></a>n</strong> wide characters pointed to by <strong id="b572730535084834"><a name="b572730535084834"></a><a name="b572730535084834"></a>src</strong> to the wide character array pointed to by <strong id="b691611173084834"><a name="b691611173084834"></a><a name="b691611173084834"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row818989592084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639997542084834"><a name="p1639997542084834"></a><a name="p1639997542084834"></a><a href="UTILS.md#ga1fa2f722dd578b02ed196a74488f75f0">wcscat</a> (wchar_t *dest, const wchar_t *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1522806891084834"><a name="p1522806891084834"></a><a name="p1522806891084834"></a>wchar_t *&nbsp;</p>
<p id="p863909130084834"><a name="p863909130084834"></a><a name="p863909130084834"></a>Appends a copy of the wide characters pointed to by <strong id="b311771848084834"><a name="b311771848084834"></a><a name="b311771848084834"></a>src</strong> to the end of the wide character array pointed to by <strong id="b824619975084834"><a name="b824619975084834"></a><a name="b824619975084834"></a>dest</strong> and adds a terminating null character <strong id="b1847859101084834"><a name="b1847859101084834"></a><a name="b1847859101084834"></a>'\0'</strong>. </p>
</td>
</tr>
<tr id="row439055162084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131119126084834"><a name="p2131119126084834"></a><a name="p2131119126084834"></a><a href="UTILS.md#ga8af5b08f466d2d6843f7ec250eddb41c">wcsncat</a> (wchar_t *dest, const wchar_t *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1786112921084834"><a name="p1786112921084834"></a><a name="p1786112921084834"></a>wchar_t *&nbsp;</p>
<p id="p523884705084834"><a name="p523884705084834"></a><a name="p523884705084834"></a>Appends a copy of the first <strong id="b1806702574084834"><a name="b1806702574084834"></a><a name="b1806702574084834"></a>n</strong> wide characters pointed to by <strong id="b496803537084834"><a name="b496803537084834"></a><a name="b496803537084834"></a>src</strong> to the end of the wide characters pointed to by <strong id="b1309469337084834"><a name="b1309469337084834"></a><a name="b1309469337084834"></a>dest</strong> and adds a terminating null character <strong id="b1827497664084834"><a name="b1827497664084834"></a><a name="b1827497664084834"></a>'\0'</strong>. </p>
</td>
</tr>
<tr id="row1193136098084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1702346872084834"><a name="p1702346872084834"></a><a name="p1702346872084834"></a><a href="UTILS.md#gab361438866831d03563fbb430c1514c5">wcscmp</a> (const wchar_t *s1, const wchar_t *s2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980644348084834"><a name="p980644348084834"></a><a name="p980644348084834"></a>int&nbsp;</p>
<p id="p265049712084834"><a name="p265049712084834"></a><a name="p265049712084834"></a>Compares each character in the string pointed to by <strong id="b134102994084834"><a name="b134102994084834"></a><a name="b134102994084834"></a>s1</strong> with that in the string pointed to by <strong id="b1716453850084834"><a name="b1716453850084834"></a><a name="b1716453850084834"></a>s2</strong> in ASCII-code order. </p>
</td>
</tr>
<tr id="row1747559067084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p721537511084834"><a name="p721537511084834"></a><a name="p721537511084834"></a><a href="UTILS.md#ga422e6bb262f249f2d71b6a2d77408038">wcsncmp</a> (const wchar_t *s1, const wchar_t *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1899537806084834"><a name="p1899537806084834"></a><a name="p1899537806084834"></a>int&nbsp;</p>
<p id="p1515057158084834"><a name="p1515057158084834"></a><a name="p1515057158084834"></a>Compares the first <strong id="b844216752084834"><a name="b844216752084834"></a><a name="b844216752084834"></a>n</strong> characters in the string pointed to by <strong id="b1076348529084834"><a name="b1076348529084834"></a><a name="b1076348529084834"></a>s1</strong> with those in the string pointed to by <strong id="b169826888084834"><a name="b169826888084834"></a><a name="b169826888084834"></a>s2</strong> in ASCII-code order. </p>
</td>
</tr>
<tr id="row1063273339084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p327014331084834"><a name="p327014331084834"></a><a name="p327014331084834"></a><a href="UTILS.md#ga99ef4b8381c22d8db3b2b13d8c3a3c29">wcscoll</a> (const wchar_t *ws1, const wchar_t *ws2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016890811084834"><a name="p1016890811084834"></a><a name="p1016890811084834"></a>int&nbsp;</p>
<p id="p403685315084834"><a name="p403685315084834"></a><a name="p403685315084834"></a>Compares the wide characters in the string pointed to by <strong id="b188709055084834"><a name="b188709055084834"></a><a name="b188709055084834"></a>ws1</strong> with those in the string pointed to by <strong id="b1578183892084834"><a name="b1578183892084834"></a><a name="b1578183892084834"></a>ws2</strong> based on the specified locale <a href="IO.md#gaab9cf7b1a206fb75e5884934c8d676db">LC_COLLATE</a>. </p>
</td>
</tr>
<tr id="row952081792084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1752994385084834"><a name="p1752994385084834"></a><a name="p1752994385084834"></a><a href="UTILS.md#ga3a0974b661a750f99ec204adf0921baf">wcsxfrm</a> (wchar_t *s1, const wchar_t *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367545042084834"><a name="p367545042084834"></a><a name="p367545042084834"></a>size_t&nbsp;</p>
<p id="p1482320556084834"><a name="p1482320556084834"></a><a name="p1482320556084834"></a>Compares the first <strong id="b993246416084834"><a name="b993246416084834"></a><a name="b993246416084834"></a>n</strong> wide characters in the string pointed to by <strong id="b2061548062084834"><a name="b2061548062084834"></a><a name="b2061548062084834"></a>s1</strong> with those in the string pointed to by <strong id="b2002431256084834"><a name="b2002431256084834"></a><a name="b2002431256084834"></a>s2</strong>. </p>
</td>
</tr>
<tr id="row1337887026084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271954259084834"><a name="p1271954259084834"></a><a name="p1271954259084834"></a><a href="UTILS.md#ga3fe8f361d1cff837a204ef0f4fac68eb">wcschr</a> (const wchar_t *wcs, wchar_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1606239833084834"><a name="p1606239833084834"></a><a name="p1606239833084834"></a>wchar_t *&nbsp;</p>
<p id="p81481095084834"><a name="p81481095084834"></a><a name="p81481095084834"></a>Locates the first occurrence of the wide character pointed to by <strong id="b2011902385084834"><a name="b2011902385084834"></a><a name="b2011902385084834"></a>wc</strong> in the wide character string pointed to by <strong id="b967159004084834"><a name="b967159004084834"></a><a name="b967159004084834"></a>wcs</strong>. </p>
</td>
</tr>
<tr id="row120546154084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1867403508084834"><a name="p1867403508084834"></a><a name="p1867403508084834"></a><a href="UTILS.md#ga1e2b53d4a4eb975edfd1ec59099a43bd">wcsrchr</a> (const wchar_t *wcs, wchar_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734546575084834"><a name="p734546575084834"></a><a name="p734546575084834"></a>wchar_t *&nbsp;</p>
<p id="p536730820084834"><a name="p536730820084834"></a><a name="p536730820084834"></a>Locates the last occurrence of the wide character pointed to by <strong id="b233885357084834"><a name="b233885357084834"></a><a name="b233885357084834"></a>wc</strong> in the wide character string pointed to by <strong id="b267058841084834"><a name="b267058841084834"></a><a name="b267058841084834"></a>wcs</strong>. </p>
</td>
</tr>
<tr id="row572538716084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489223472084834"><a name="p1489223472084834"></a><a name="p1489223472084834"></a><a href="UTILS.md#ga188fb5a6a8c210ee46b885a671f55c61">wcscspn</a> (const wchar_t *wcs, const wchar_t *<a href="NET.md#ga0807af5ac9dfc2a63624e8c3e0ae95ef">accept</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650989281084834"><a name="p650989281084834"></a><a name="p650989281084834"></a>size_t&nbsp;</p>
<p id="p1615744462084834"><a name="p1615744462084834"></a><a name="p1615744462084834"></a>Scans the wide character string pointed to by <strong id="b1976487130084834"><a name="b1976487130084834"></a><a name="b1976487130084834"></a>wcs</strong> for any wide characters specified in <strong id="b2141349977084834"><a name="b2141349977084834"></a><a name="b2141349977084834"></a>reject</strong> and obtains the number of unmatched characters in <strong id="b2118348013084834"><a name="b2118348013084834"></a><a name="b2118348013084834"></a>wcs</strong>. </p>
</td>
</tr>
<tr id="row942821231084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p919204145084834"><a name="p919204145084834"></a><a name="p919204145084834"></a><a href="UTILS.md#ga2a5d42d9b374cbffb3037d0e7efb97a9">wcsspn</a> (const wchar_t *wcs, const wchar_t *<a href="NET.md#ga0807af5ac9dfc2a63624e8c3e0ae95ef">accept</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140966317084834"><a name="p2140966317084834"></a><a name="p2140966317084834"></a>size_t&nbsp;</p>
<p id="p1993665549084834"><a name="p1993665549084834"></a><a name="p1993665549084834"></a>Scans the wide character string pointed to by <strong id="b989667320084834"><a name="b989667320084834"></a><a name="b989667320084834"></a>wcs</strong> for any wide characters specified in <strong id="b708406872084834"><a name="b708406872084834"></a><a name="b708406872084834"></a>reject</strong> and obtains the number matched characters in <strong id="b1243983084834"><a name="b1243983084834"></a><a name="b1243983084834"></a>wcs</strong>. </p>
</td>
</tr>
<tr id="row653523509084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p281061487084834"><a name="p281061487084834"></a><a name="p281061487084834"></a><a href="UTILS.md#ga65c3cbada5beb856956f682e7ab2d812">wcspbrk</a> (const wchar_t *wcs, const wchar_t *<a href="NET.md#ga0807af5ac9dfc2a63624e8c3e0ae95ef">accept</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1349076550084834"><a name="p1349076550084834"></a><a name="p1349076550084834"></a>wchar_t *&nbsp;</p>
<p id="p1640216198084834"><a name="p1640216198084834"></a><a name="p1640216198084834"></a>Scans the wide character string pointed to by <strong id="b678198571084834"><a name="b678198571084834"></a><a name="b678198571084834"></a>wcs</strong> for any wide characters specified in <strong id="b1185111702084834"><a name="b1185111702084834"></a><a name="b1185111702084834"></a>accept</strong> and obtains the first occurrence of the matched character. </p>
</td>
</tr>
<tr id="row783253843084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p270137968084834"><a name="p270137968084834"></a><a name="p270137968084834"></a><a href="UTILS.md#ga01f67f93543c36fdae41b410a7f3d963">wcstok</a> (wchar_t *wcs, const wchar_t *delim, wchar_t **ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1707703817084834"><a name="p1707703817084834"></a><a name="p1707703817084834"></a>wchar_t *&nbsp;</p>
<p id="p1914675577084834"><a name="p1914675577084834"></a><a name="p1914675577084834"></a>Splits a wide character string pointed to by <strong id="b1468402574084834"><a name="b1468402574084834"></a><a name="b1468402574084834"></a>wcs</strong> into tokens using the given delimiter. </p>
</td>
</tr>
<tr id="row1218477583084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662015837084834"><a name="p662015837084834"></a><a name="p662015837084834"></a><a href="UTILS.md#ga7859e4ba07f77515772c4632d4caa4e0">wcslen</a> (const wchar_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1721908433084834"><a name="p1721908433084834"></a><a name="p1721908433084834"></a>size_t&nbsp;</p>
<p id="p2064043634084834"><a name="p2064043634084834"></a><a name="p2064043634084834"></a>Calculates the length of a wide character string pointed to by <strong id="b882284120084834"><a name="b882284120084834"></a><a name="b882284120084834"></a>s</strong>. </p>
</td>
</tr>
<tr id="row918512661084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1623899841084834"><a name="p1623899841084834"></a><a name="p1623899841084834"></a><a href="UTILS.md#ga844ce8231d55e4cc8010130477dd0d5a">wcswcs</a> (const wchar_t *haystack, const wchar_t *needle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980936544084834"><a name="p980936544084834"></a><a name="p980936544084834"></a>wchar_t *&nbsp;</p>
<p id="p1340847275084834"><a name="p1340847275084834"></a><a name="p1340847275084834"></a>Searches the wide character string pointed to by <strong id="b253210721084834"><a name="b253210721084834"></a><a name="b253210721084834"></a>dest</strong> for the first occurrence of the wide character string pointed to by <strong id="b905202669084834"><a name="b905202669084834"></a><a name="b905202669084834"></a>src</strong>. </p>
</td>
</tr>
<tr id="row1890990468084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1941982230084834"><a name="p1941982230084834"></a><a name="p1941982230084834"></a><a href="UTILS.md#gacb1e61bbd4b15305803c0e558c00bcdd">wmemchr</a> (const wchar_t *s, wchar_t c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402560394084834"><a name="p1402560394084834"></a><a name="p1402560394084834"></a>wchar_t *&nbsp;</p>
<p id="p1895487872084834"><a name="p1895487872084834"></a><a name="p1895487872084834"></a>Searches for the first position of the matched wide character within the specified number of characters in a wide character string. </p>
</td>
</tr>
<tr id="row1099780064084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662242062084834"><a name="p1662242062084834"></a><a name="p1662242062084834"></a><a href="UTILS.md#gaec76ca0ca875ef6cfcc1d7415052eb26">wmemcmp</a> (const wchar_t *lhs, const wchar_t *rhs, size_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265277583084834"><a name="p265277583084834"></a><a name="p265277583084834"></a>int&nbsp;</p>
<p id="p301435275084834"><a name="p301435275084834"></a><a name="p301435275084834"></a>Compares the first <strong id="b1693503095084834"><a name="b1693503095084834"></a><a name="b1693503095084834"></a>count</strong> characters in the string pointed to by <strong id="b1865473191084834"><a name="b1865473191084834"></a><a name="b1865473191084834"></a>lhs</strong> with the first <strong id="b328010518084834"><a name="b328010518084834"></a><a name="b328010518084834"></a>count</strong> characters in the string pointed to by <strong id="b1181086105084834"><a name="b1181086105084834"></a><a name="b1181086105084834"></a>rhs</strong>. </p>
</td>
</tr>
<tr id="row54753138084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p190187853084834"><a name="p190187853084834"></a><a name="p190187853084834"></a><a href="UTILS.md#gac20ec2fc709b45b0b89dbdc3ae6a537e">wmemcpy</a> (wchar_t *dest, const wchar_t *src, size_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1355997663084834"><a name="p1355997663084834"></a><a name="p1355997663084834"></a>wchar_t *&nbsp;</p>
<p id="p1874131295084834"><a name="p1874131295084834"></a><a name="p1874131295084834"></a>Copies <strong id="b220220531084834"><a name="b220220531084834"></a><a name="b220220531084834"></a>count</strong> successive characters from the wide character array pointed to by <strong id="b2043800354084834"><a name="b2043800354084834"></a><a name="b2043800354084834"></a>src</strong> to the wide character array pointed to by <strong id="b219005466084834"><a name="b219005466084834"></a><a name="b219005466084834"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row1757320961084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1834370212084834"><a name="p1834370212084834"></a><a name="p1834370212084834"></a><a href="UTILS.md#ga7eeab622d3eacdfd8ff0c4226cf85209">wmemmove</a> (wchar_t *dest, const wchar_t *src, size_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994710321084834"><a name="p994710321084834"></a><a name="p994710321084834"></a>wchar_t *&nbsp;</p>
<p id="p211233023084834"><a name="p211233023084834"></a><a name="p211233023084834"></a>Copies <strong id="b709354381084834"><a name="b709354381084834"></a><a name="b709354381084834"></a>count</strong> successive characters from the wide character array pointed to by <strong id="b8904080084834"><a name="b8904080084834"></a><a name="b8904080084834"></a>src</strong> to the wide character array pointed to by <strong id="b137968063084834"><a name="b137968063084834"></a><a name="b137968063084834"></a>dest</strong> (with possible array overlapping). </p>
</td>
</tr>
<tr id="row2147411263084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1753379252084834"><a name="p1753379252084834"></a><a name="p1753379252084834"></a><a href="UTILS.md#ga830c36f7d0d13b4dcb5059e7b1d9ab83">wmemset</a> (wchar_t *dest, wchar_t ch, size_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1544860459084834"><a name="p1544860459084834"></a><a name="p1544860459084834"></a>wchar_t *&nbsp;</p>
<p id="p150307219084834"><a name="p150307219084834"></a><a name="p150307219084834"></a>Fills <strong id="b1721392157084834"><a name="b1721392157084834"></a><a name="b1721392157084834"></a>count</strong> characters specified by <strong id="b819176648084834"><a name="b819176648084834"></a><a name="b819176648084834"></a>ch</strong> to the wide character array pointed to by <strong id="b1341503704084834"><a name="b1341503704084834"></a><a name="b1341503704084834"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row701174646084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1144527222084834"><a name="p1144527222084834"></a><a name="p1144527222084834"></a><a href="UTILS.md#ga263759bc74f8621e89e6077095caa942">btowc</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1069514173084834"><a name="p1069514173084834"></a><a name="p1069514173084834"></a>wint_t&nbsp;</p>
<p id="p1081453469084834"><a name="p1081453469084834"></a><a name="p1081453469084834"></a>Converts a single-byte character <strong id="b1187024200084834"><a name="b1187024200084834"></a><a name="b1187024200084834"></a>c</strong> into its wide-character representation. </p>
</td>
</tr>
<tr id="row1539090636084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643585164084834"><a name="p1643585164084834"></a><a name="p1643585164084834"></a><a href="UTILS.md#gafea1d08554775797ac259bf0aea62938">wctob</a> (wint_t c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740036474084834"><a name="p740036474084834"></a><a name="p740036474084834"></a>int&nbsp;</p>
<p id="p1096476566084834"><a name="p1096476566084834"></a><a name="p1096476566084834"></a>Converts a wide character <strong id="b1451539472084834"><a name="b1451539472084834"></a><a name="b1451539472084834"></a>c</strong> into its single-byte representation. </p>
</td>
</tr>
<tr id="row44606727084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396227919084834"><a name="p1396227919084834"></a><a name="p1396227919084834"></a><a href="UTILS.md#gac87bb41cb64e86b29faf5b569c2533b4">mbsinit</a> (const mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1490892437084834"><a name="p1490892437084834"></a><a name="p1490892437084834"></a>int&nbsp;</p>
<p id="p78753967084834"><a name="p78753967084834"></a><a name="p78753967084834"></a>Checks whether the <strong id="b1096965268084834"><a name="b1096965268084834"></a><a name="b1096965268084834"></a>mbstate_t</strong> object pointed to by <strong id="b1941902805084834"><a name="b1941902805084834"></a><a name="b1941902805084834"></a>ps</strong> is in the initial state. </p>
</td>
</tr>
<tr id="row1175262659084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1040252195084834"><a name="p1040252195084834"></a><a name="p1040252195084834"></a><a href="UTILS.md#ga67e98eb761f2880dc93ceb3833bbf9bd">wcrtomb</a> (char *s, wchar_t wc, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p167750538084834"><a name="p167750538084834"></a><a name="p167750538084834"></a>size_t&nbsp;</p>
<p id="p439472974084834"><a name="p439472974084834"></a><a name="p439472974084834"></a>Converts the wide character specified by <strong id="b445829358084834"><a name="b445829358084834"></a><a name="b445829358084834"></a>wc</strong> into a character string and stores the string to the beginning of the character array pointed to by <strong id="b566014983084834"><a name="b566014983084834"></a><a name="b566014983084834"></a>s</strong>. </p>
</td>
</tr>
<tr id="row1095130153084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9809842084834"><a name="p9809842084834"></a><a name="p9809842084834"></a><a href="UTILS.md#gab7c8a08e5174c1235b0e925dfc77b938">mbrlen</a> (const char *s, size_t n, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1390768482084834"><a name="p1390768482084834"></a><a name="p1390768482084834"></a>size_t&nbsp;</p>
<p id="p1759519578084834"><a name="p1759519578084834"></a><a name="p1759519578084834"></a>Determines the number of bytes in a character string pointed to by <strong id="b1951524734084834"><a name="b1951524734084834"></a><a name="b1951524734084834"></a>s</strong>. </p>
</td>
</tr>
<tr id="row1681495587084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1847070383084834"><a name="p1847070383084834"></a><a name="p1847070383084834"></a><a href="UTILS.md#gac3ebddff1a73c20b17986a6b7b68fe56">mbsrtowcs</a> (wchar_t *dest, const char **src, size_t len, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1480474581084834"><a name="p1480474581084834"></a><a name="p1480474581084834"></a>size_t&nbsp;</p>
<p id="p1893004506084834"><a name="p1893004506084834"></a><a name="p1893004506084834"></a>Converts a multi-byte character string with a length of <strong id="b118635711084834"><a name="b118635711084834"></a><a name="b118635711084834"></a>len</strong> into a wide character string. </p>
</td>
</tr>
<tr id="row1311521552084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p75055554084834"><a name="p75055554084834"></a><a name="p75055554084834"></a><a href="UTILS.md#ga0a628490d6458cfc836ebf3721e68a98">wcsrtombs</a> (char *dest, const wchar_t **src, size_t len, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p616229612084834"><a name="p616229612084834"></a><a name="p616229612084834"></a>size_t&nbsp;</p>
<p id="p360698395084834"><a name="p360698395084834"></a><a name="p360698395084834"></a>Converts a wide character string into a multi-byte string. </p>
</td>
</tr>
<tr id="row1963244607084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313260087084834"><a name="p1313260087084834"></a><a name="p1313260087084834"></a><a href="UTILS.md#gadf99123a55665bf0669487a12aee795f">wcstof</a> (const wchar_t *str, wchar_t **endptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475862926084834"><a name="p475862926084834"></a><a name="p475862926084834"></a>float&nbsp;</p>
<p id="p2088193383084834"><a name="p2088193383084834"></a><a name="p2088193383084834"></a>Converts a wide character string pointed to by <strong id="b181858200084834"><a name="b181858200084834"></a><a name="b181858200084834"></a>str</strong> into a floating-point value and assigns the next character in <strong id="b984440225084834"><a name="b984440225084834"></a><a name="b984440225084834"></a>str</strong> after the floating-point value to <strong id="b304372136084834"><a name="b304372136084834"></a><a name="b304372136084834"></a>endptr</strong>. </p>
</td>
</tr>
<tr id="row306519621084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119363705084834"><a name="p1119363705084834"></a><a name="p1119363705084834"></a><a href="UTILS.md#ga2030f1f318ded574650a1957574711a0">wcstod</a> (const wchar_t *str, wchar_t **endptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135603164084834"><a name="p135603164084834"></a><a name="p135603164084834"></a>double&nbsp;</p>
<p id="p778543396084834"><a name="p778543396084834"></a><a name="p778543396084834"></a>Converts a wide character string pointed to by <strong id="b903304197084834"><a name="b903304197084834"></a><a name="b903304197084834"></a>str</strong> into a double value and assigns the next character in <strong id="b1282442705084834"><a name="b1282442705084834"></a><a name="b1282442705084834"></a>str</strong> after the double value to <strong id="b1062441847084834"><a name="b1062441847084834"></a><a name="b1062441847084834"></a>endptr</strong>. </p>
</td>
</tr>
<tr id="row284176323084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782442108084834"><a name="p1782442108084834"></a><a name="p1782442108084834"></a><a href="UTILS.md#gaf1879aa0145431434cbac389629bee6a">wcstold</a> (const wchar_t *str, wchar_t **endptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311281995084834"><a name="p311281995084834"></a><a name="p311281995084834"></a>long double&nbsp;</p>
<p id="p1789674390084834"><a name="p1789674390084834"></a><a name="p1789674390084834"></a>Converts a wide character string pointed to by <strong id="b936802831084834"><a name="b936802831084834"></a><a name="b936802831084834"></a>str</strong> into a long double value and assigns the next character in <strong id="b874214053084834"><a name="b874214053084834"></a><a name="b874214053084834"></a>str</strong> after the long double value to <strong id="b2054088689084834"><a name="b2054088689084834"></a><a name="b2054088689084834"></a>endptr</strong>. </p>
</td>
</tr>
<tr id="row1516884025084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001694827084834"><a name="p1001694827084834"></a><a name="p1001694827084834"></a><a href="UTILS.md#ga623c775bac158351e308fd3811daeb9f">wcstol</a> (const wchar_t *str, wchar_t **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601741131084834"><a name="p1601741131084834"></a><a name="p1601741131084834"></a>long&nbsp;</p>
<p id="p849910344084834"><a name="p849910344084834"></a><a name="p849910344084834"></a>Converts a wide character string pointed to by <strong id="b2133393381084834"><a name="b2133393381084834"></a><a name="b2133393381084834"></a>str</strong> into a long value. </p>
</td>
</tr>
<tr id="row857185679084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044061999084834"><a name="p2044061999084834"></a><a name="p2044061999084834"></a><a href="UTILS.md#ga71d821611320a733b3f51ff8077ce92c">wcstoul</a> (const wchar_t *str, wchar_t **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p299712757084834"><a name="p299712757084834"></a><a name="p299712757084834"></a>unsigned long&nbsp;</p>
<p id="p269451959084834"><a name="p269451959084834"></a><a name="p269451959084834"></a>Converts a wide character string pointed to by <strong id="b1560235624084834"><a name="b1560235624084834"></a><a name="b1560235624084834"></a>str</strong> into an unsigned long value of a specified base. </p>
</td>
</tr>
<tr id="row2013335549084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1469596614084834"><a name="p1469596614084834"></a><a name="p1469596614084834"></a><a href="UTILS.md#ga1f43fe48b9afd42fb80b0560c1358ad3">wcstoll</a> (const wchar_t *str, wchar_t **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103882092084834"><a name="p1103882092084834"></a><a name="p1103882092084834"></a>long long&nbsp;</p>
<p id="p742828242084834"><a name="p742828242084834"></a><a name="p742828242084834"></a>Converts a wide character string pointed to by <strong id="b1947109187084834"><a name="b1947109187084834"></a><a name="b1947109187084834"></a>str</strong> into a long long value of a specified base. </p>
</td>
</tr>
<tr id="row1289362298084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2137536280084834"><a name="p2137536280084834"></a><a name="p2137536280084834"></a><a href="UTILS.md#gad28d6c39911a0d99ebaf2ee4e3b9f621">wcstoull</a> (const wchar_t *str, wchar_t **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1593970826084834"><a name="p1593970826084834"></a><a name="p1593970826084834"></a>unsigned long long&nbsp;</p>
<p id="p359005930084834"><a name="p359005930084834"></a><a name="p359005930084834"></a>Converts a wide character string pointed to by <strong id="b1971190277084834"><a name="b1971190277084834"></a><a name="b1971190277084834"></a>str</strong> into an unsigned long long value of a specified base. </p>
</td>
</tr>
<tr id="row992280149084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1098752580084834"><a name="p1098752580084834"></a><a name="p1098752580084834"></a><a href="UTILS.md#ga5438ce60b99b0455f356cd27726161ab">fwide</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, int mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748002868084834"><a name="p748002868084834"></a><a name="p748002868084834"></a>int&nbsp;</p>
<p id="p1079101225084834"><a name="p1079101225084834"></a><a name="p1079101225084834"></a>Sets and determines the orientation of the file stream. </p>
</td>
</tr>
<tr id="row552513067084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101038167084834"><a name="p1101038167084834"></a><a name="p1101038167084834"></a><a href="UTILS.md#gaf30b50dd88f13675d890857755670a2d">wprintf</a> (const wchar_t *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274798115084834"><a name="p1274798115084834"></a><a name="p1274798115084834"></a>int&nbsp;</p>
<p id="p633076324084834"><a name="p633076324084834"></a><a name="p633076324084834"></a>Prints formatted data to the standard output (stdout). </p>
</td>
</tr>
<tr id="row1907600750084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785592434084834"><a name="p1785592434084834"></a><a name="p1785592434084834"></a><a href="UTILS.md#ga2b7ff2e4c9e4d1c0d6dc35bf93542d53">fwprintf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *__restrict fp, const wchar_t *__restrict fmt,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1988075618084834"><a name="p1988075618084834"></a><a name="p1988075618084834"></a>int&nbsp;</p>
<p id="p400937249084834"><a name="p400937249084834"></a><a name="p400937249084834"></a>Prints wide character strings to a specified file stream. </p>
</td>
</tr>
<tr id="row1522653703084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1958031611084834"><a name="p1958031611084834"></a><a name="p1958031611084834"></a><a href="UTILS.md#ga7c963d10722b32fbcf5508057ccf76ec">swprintf</a> (wchar_t *wcs, size_t maxlen, const wchar_t *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870943283084834"><a name="p1870943283084834"></a><a name="p1870943283084834"></a>int&nbsp;</p>
<p id="p1101904523084834"><a name="p1101904523084834"></a><a name="p1101904523084834"></a>Prints formatted data to a specified string. </p>
</td>
</tr>
<tr id="row1084960799084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079718576084834"><a name="p2079718576084834"></a><a name="p2079718576084834"></a><a href="UTILS.md#gadff14929a4410b3ac0ce28b55357e280">vwprintf</a> (const wchar_t *format, va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577538311084834"><a name="p577538311084834"></a><a name="p577538311084834"></a>int&nbsp;</p>
<p id="p484433250084834"><a name="p484433250084834"></a><a name="p484433250084834"></a>Prints formatted data from a variable argument list to the standard output (stdout). </p>
</td>
</tr>
<tr id="row1314163013084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1698480288084834"><a name="p1698480288084834"></a><a name="p1698480288084834"></a><a href="UTILS.md#ga52697c5b86b8a3fa892b69f70fac8843">vfwprintf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const wchar_t *format, __isoc_va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034097334084834"><a name="p2034097334084834"></a><a name="p2034097334084834"></a>int&nbsp;</p>
<p id="p809154784084834"><a name="p809154784084834"></a><a name="p809154784084834"></a>Prints formatted data from a variable argument list specified by <strong id="b604742354084834"><a name="b604742354084834"></a><a name="b604742354084834"></a>args</strong> to a specified file stream. </p>
</td>
</tr>
<tr id="row1420179472084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1584347177084834"><a name="p1584347177084834"></a><a name="p1584347177084834"></a><a href="UTILS.md#gad79402226fa58569bee4601eb029b717">vswprintf</a> (wchar_t *wcs, size_t maxlen, const wchar_t *format, __isoc_va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424545387084834"><a name="p1424545387084834"></a><a name="p1424545387084834"></a>int&nbsp;</p>
<p id="p1302898109084834"><a name="p1302898109084834"></a><a name="p1302898109084834"></a>Prints formatted data from a variable argument list specified by <strong id="b1969584897084834"><a name="b1969584897084834"></a><a name="b1969584897084834"></a>args</strong> to a specified string. </p>
</td>
</tr>
<tr id="row372196632084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888848622084834"><a name="p888848622084834"></a><a name="p888848622084834"></a><a href="UTILS.md#ga24e265f34e058454b9a9b6247b1694b0">wscanf</a> (const wchar_t *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175393816084834"><a name="p1175393816084834"></a><a name="p1175393816084834"></a>int&nbsp;</p>
<p id="p94469205084834"><a name="p94469205084834"></a><a name="p94469205084834"></a>Reads formatted data from the standard input (stdin) and stores it based on the wide string format into the locations pointed to by the variable arguments. </p>
</td>
</tr>
<tr id="row440830629084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256787217084834"><a name="p256787217084834"></a><a name="p256787217084834"></a><a href="UTILS.md#ga1e39ec126230aed6ffa3e922be38a014">fwscanf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const wchar_t *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983669620084834"><a name="p983669620084834"></a><a name="p983669620084834"></a>int&nbsp;</p>
<p id="p1893379505084834"><a name="p1893379505084834"></a><a name="p1893379505084834"></a>Reads formatted data from a specified stream and stores it based on the wide string format into the locations pointed to by the variable arguments. </p>
</td>
</tr>
<tr id="row1695322403084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1880990654084834"><a name="p1880990654084834"></a><a name="p1880990654084834"></a><a href="UTILS.md#gaac90953229a0d08ce45ba328430d6637">swscanf</a> (const wchar_t *ws, const wchar_t *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1983878883084834"><a name="p1983878883084834"></a><a name="p1983878883084834"></a>int&nbsp;</p>
<p id="p599191152084834"><a name="p599191152084834"></a><a name="p599191152084834"></a>Reads data from a wide character string pointed to by <strong id="b1235545534084834"><a name="b1235545534084834"></a><a name="b1235545534084834"></a>ws</strong> and stores it based on the wide string format into the locations pointed to by the variable arguments. </p>
</td>
</tr>
<tr id="row1115932274084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712039360084834"><a name="p1712039360084834"></a><a name="p1712039360084834"></a><a href="UTILS.md#ga4406b91b463b1fc3d4d43b44ccb46d1c">vwscanf</a> (const wchar_t *format, va_list arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1484128307084834"><a name="p1484128307084834"></a><a name="p1484128307084834"></a>int&nbsp;</p>
<p id="p932710823084834"><a name="p932710823084834"></a><a name="p932710823084834"></a>Reads data from the stdin and stores it based on the wide string format into the locations pointed to by the elements in the variable argument list identified by <strong id="b1113843957084834"><a name="b1113843957084834"></a><a name="b1113843957084834"></a>arg</strong>. </p>
</td>
</tr>
<tr id="row1085440638084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413750229084834"><a name="p1413750229084834"></a><a name="p1413750229084834"></a><a href="UTILS.md#ga0d7996cc31075571432fcc7a21c402fa">vfwscanf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const wchar_t *format, va_list arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638168517084834"><a name="p1638168517084834"></a><a name="p1638168517084834"></a>int&nbsp;</p>
<p id="p732422936084834"><a name="p732422936084834"></a><a name="p732422936084834"></a>Reads data from a specified file stream and stores it based on the wide string format into the locations pointed to by the elements in the variable argument list identified by <strong id="b887414606084834"><a name="b887414606084834"></a><a name="b887414606084834"></a>arg</strong>. </p>
</td>
</tr>
<tr id="row1248559136084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1684115351084834"><a name="p1684115351084834"></a><a name="p1684115351084834"></a><a href="UTILS.md#ga0b70af0bd7f82c6f81886d79ad41b2c1">vswscanf</a> (const wchar_t *ws, const wchar_t *format, va_list arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391669361084834"><a name="p1391669361084834"></a><a name="p1391669361084834"></a>int&nbsp;</p>
<p id="p538682495084834"><a name="p538682495084834"></a><a name="p538682495084834"></a>Reads data from a string pointed to by <strong id="b1956077067084834"><a name="b1956077067084834"></a><a name="b1956077067084834"></a>ws</strong> and stores it based on the wide string format into the locations pointed to by the elements in the variable argument list identified by <strong id="b2146931402084834"><a name="b2146931402084834"></a><a name="b2146931402084834"></a>arg</strong>. </p>
</td>
</tr>
<tr id="row1739946327084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1659816230084834"><a name="p1659816230084834"></a><a name="p1659816230084834"></a><a href="UTILS.md#ga2b545d8d6d3209a2eb6129d8ba646fe3">fgetwc</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1624176469084834"><a name="p1624176469084834"></a><a name="p1624176469084834"></a>wint_t&nbsp;</p>
<p id="p30966041084834"><a name="p30966041084834"></a><a name="p30966041084834"></a>Reads a wide character from a specified file stream. </p>
</td>
</tr>
<tr id="row156634705084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1715658925084834"><a name="p1715658925084834"></a><a name="p1715658925084834"></a><a href="UTILS.md#gaadd2028a176fe13a0d6090cec651a369">getwc</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311035726084834"><a name="p311035726084834"></a><a name="p311035726084834"></a>wint_t&nbsp;</p>
<p id="p148312436084834"><a name="p148312436084834"></a><a name="p148312436084834"></a>Reads the first wide character from a specified file stream. </p>
</td>
</tr>
<tr id="row1668862563084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2012167869084834"><a name="p2012167869084834"></a><a name="p2012167869084834"></a><a href="UTILS.md#gaa1379ae6936df3415301dc580aa8756e">getwchar</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p166130898084834"><a name="p166130898084834"></a><a name="p166130898084834"></a>wint_t&nbsp;</p>
<p id="p1720248341084834"><a name="p1720248341084834"></a><a name="p1720248341084834"></a>Reads a wide character from the stdin. </p>
</td>
</tr>
<tr id="row914983542084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p613302456084834"><a name="p613302456084834"></a><a name="p613302456084834"></a><a href="UTILS.md#gab405f6ad88ebd1c6150206d19d3c7f12">fputwc</a> (wchar_t wc, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165329179084834"><a name="p1165329179084834"></a><a name="p1165329179084834"></a>wint_t&nbsp;</p>
<p id="p1520720578084834"><a name="p1520720578084834"></a><a name="p1520720578084834"></a>Writes a wide character <strong id="b1783511779084834"><a name="b1783511779084834"></a><a name="b1783511779084834"></a>wc</strong> to a specified file stream. </p>
</td>
</tr>
<tr id="row1162461101084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472139846084834"><a name="p1472139846084834"></a><a name="p1472139846084834"></a><a href="UTILS.md#ga578ce42fa0cf04469cff45134114b701">putwc</a> (wchar_t wc, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p47399125084834"><a name="p47399125084834"></a><a name="p47399125084834"></a>wint_t&nbsp;</p>
<p id="p1529326529084834"><a name="p1529326529084834"></a><a name="p1529326529084834"></a>Writes a wide character <strong id="b319321747084834"><a name="b319321747084834"></a><a name="b319321747084834"></a>wc</strong> to a specified file stream. </p>
</td>
</tr>
<tr id="row2117355403084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492359717084834"><a name="p1492359717084834"></a><a name="p1492359717084834"></a><a href="UTILS.md#ga34ef116bac70390d5a2ff8c5fdb45777">putwchar</a> (wchar_t wc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542261011084834"><a name="p1542261011084834"></a><a name="p1542261011084834"></a>wint_t&nbsp;</p>
<p id="p154119086084834"><a name="p154119086084834"></a><a name="p154119086084834"></a>Writes a wide character <strong id="b2143457898084834"><a name="b2143457898084834"></a><a name="b2143457898084834"></a>wc</strong> to the stdout. </p>
</td>
</tr>
<tr id="row1230254125084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379318232084834"><a name="p1379318232084834"></a><a name="p1379318232084834"></a><a href="UTILS.md#ga6f98d7f5d5d1e6ad282ee1a348eab753">fgetws</a> (wchar_t *ws, int n, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p605864746084834"><a name="p605864746084834"></a><a name="p605864746084834"></a>wchar_t *&nbsp;</p>
<p id="p1815045362084834"><a name="p1815045362084834"></a><a name="p1815045362084834"></a>Reads wide characters from a specified file stream. </p>
</td>
</tr>
<tr id="row1203808267084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p876053562084834"><a name="p876053562084834"></a><a name="p876053562084834"></a><a href="UTILS.md#gad3afb048298b1f152181fcac8e20d6e3">fputws</a> (const wchar_t *ws, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p164334091084834"><a name="p164334091084834"></a><a name="p164334091084834"></a>int&nbsp;</p>
<p id="p96917575084834"><a name="p96917575084834"></a><a name="p96917575084834"></a>Writes a wide string pointed to by <strong id="b153206942084834"><a name="b153206942084834"></a><a name="b153206942084834"></a>ws</strong> to a specified file stream. </p>
</td>
</tr>
<tr id="row118682033084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1912223739084834"><a name="p1912223739084834"></a><a name="p1912223739084834"></a><a href="UTILS.md#ga35264055ce08ba6d23ba03075897a0fb">ungetwc</a> (wint_t ch, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1505340426084834"><a name="p1505340426084834"></a><a name="p1505340426084834"></a>wint_t&nbsp;</p>
<p id="p772000585084834"><a name="p772000585084834"></a><a name="p772000585084834"></a>Pushes a character back into a specified file stream. </p>
</td>
</tr>
<tr id="row1291593909084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994841038084834"><a name="p1994841038084834"></a><a name="p1994841038084834"></a><a href="UTILS.md#ga6fd639ff3ac22621951452b380468327">mbrtowc</a> (wchar_t *pwc, const char *s, size_t n, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094627129084834"><a name="p2094627129084834"></a><a name="p2094627129084834"></a>size_t&nbsp;</p>
<p id="p1030486889084834"><a name="p1030486889084834"></a><a name="p1030486889084834"></a>Converts a multi-byte character string with a length of <strong id="b1252289321084834"><a name="b1252289321084834"></a><a name="b1252289321084834"></a>n</strong> into a wide character string. </p>
</td>
</tr>
<tr id="row963164442084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2057465348084834"><a name="p2057465348084834"></a><a name="p2057465348084834"></a><a href="UTILS.md#ga08f9c737e4060d9e123e0fc28a1eb2f3">mbsnrtowcs</a> (wchar_t *dest, const char **src, size_t nwc, size_t len, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2004239525084834"><a name="p2004239525084834"></a><a name="p2004239525084834"></a>size_t&nbsp;</p>
<p id="p856625795084834"><a name="p856625795084834"></a><a name="p856625795084834"></a>Converts a multi-byte character string with a length of <strong id="b1860936463084834"><a name="b1860936463084834"></a><a name="b1860936463084834"></a>n</strong> into a wide character string that can hold a total of <strong id="b415525977084834"><a name="b415525977084834"></a><a name="b415525977084834"></a>nwc</strong> wide characters. </p>
</td>
</tr>
<tr id="row1677927843084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1445951319084834"><a name="p1445951319084834"></a><a name="p1445951319084834"></a><a href="UTILS.md#gaf189ea21a3aa444f88607ad23f448f37">wcsnrtombs</a> (char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566712237084834"><a name="p1566712237084834"></a><a name="p1566712237084834"></a>size_t&nbsp;</p>
<p id="p128608007084834"><a name="p128608007084834"></a><a name="p128608007084834"></a>Converts <strong id="b1642606786084834"><a name="b1642606786084834"></a><a name="b1642606786084834"></a>nwc</strong> wide characters in the string pointed to by <strong id="b359159821084834"><a name="b359159821084834"></a><a name="b359159821084834"></a>src</strong> into a character string. </p>
</td>
</tr>
<tr id="row1465685408084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p94537508084834"><a name="p94537508084834"></a><a name="p94537508084834"></a><a href="UTILS.md#ga21234261a334fd22ff3d6ba8883eca3a">wcsdup</a> (const wchar_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p678376994084834"><a name="p678376994084834"></a><a name="p678376994084834"></a>wchar_t *&nbsp;</p>
<p id="p828980934084834"><a name="p828980934084834"></a><a name="p828980934084834"></a>Copies a specified wide character string to a newly allocated buffer. </p>
</td>
</tr>
<tr id="row1500764059084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p818317922084834"><a name="p818317922084834"></a><a name="p818317922084834"></a><a href="UTILS.md#ga5ef7fc85c7678f86f1530fd52dbf2486">wcsnlen</a> (const wchar_t *s, size_t maxlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987747401084834"><a name="p987747401084834"></a><a name="p987747401084834"></a>size_t&nbsp;</p>
<p id="p1483050357084834"><a name="p1483050357084834"></a><a name="p1483050357084834"></a>Calculates the length of a wide character string pointed to by <strong id="b320599510084834"><a name="b320599510084834"></a><a name="b320599510084834"></a>s</strong>. </p>
</td>
</tr>
<tr id="row240529430084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p208658740084834"><a name="p208658740084834"></a><a name="p208658740084834"></a><a href="UTILS.md#gaa4f33e46d5c0263f0b3e9a1e8eb0a7a9">wcpcpy</a> (wchar_t *dest, const wchar_t *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1311988987084834"><a name="p1311988987084834"></a><a name="p1311988987084834"></a>wchar_t *&nbsp;</p>
<p id="p979447884084834"><a name="p979447884084834"></a><a name="p979447884084834"></a>Copies the wide characters (including the terminating null character <strong id="b1823312349084834"><a name="b1823312349084834"></a><a name="b1823312349084834"></a>'\0'</strong>) pointed to by <strong id="b77762325084834"><a name="b77762325084834"></a><a name="b77762325084834"></a>src</strong> to the wide character array pointed to by <strong id="b853414658084834"><a name="b853414658084834"></a><a name="b853414658084834"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row1640419816084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p646998882084834"><a name="p646998882084834"></a><a name="p646998882084834"></a><a href="UTILS.md#ga2b77c48e45c06857bae5c4720fd977b9">wcpncpy</a> (wchar_t *dest, const wchar_t *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722219990084834"><a name="p1722219990084834"></a><a name="p1722219990084834"></a>wchar_t *&nbsp;</p>
<p id="p1229339689084834"><a name="p1229339689084834"></a><a name="p1229339689084834"></a>Copies <strong id="b1761349203084834"><a name="b1761349203084834"></a><a name="b1761349203084834"></a>n</strong> wide characters (including the terminating null character <strong id="b1517119943084834"><a name="b1517119943084834"></a><a name="b1517119943084834"></a>'\0'</strong>) pointed to by <strong id="b1411094035084834"><a name="b1411094035084834"></a><a name="b1411094035084834"></a>src</strong> to the wide character array pointed to by <strong id="b2134980477084834"><a name="b2134980477084834"></a><a name="b2134980477084834"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row2137378921084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778690127084834"><a name="p1778690127084834"></a><a name="p1778690127084834"></a><a href="UTILS.md#ga1cfd283a315ce1081565d9370dadbd1e">wcscasecmp</a> (const wchar_t *s1, const wchar_t *s2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540802193084834"><a name="p1540802193084834"></a><a name="p1540802193084834"></a>int&nbsp;</p>
<p id="p1856057821084834"><a name="p1856057821084834"></a><a name="p1856057821084834"></a>Compares the wide characters in the string pointed to by <strong id="b1720477309084834"><a name="b1720477309084834"></a><a name="b1720477309084834"></a>s1</strong> with those in the string pointed to by <strong id="b431479933084834"><a name="b431479933084834"></a><a name="b431479933084834"></a>s2</strong>, with their case differences ignored. </p>
</td>
</tr>
<tr id="row1019124845084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757855308084834"><a name="p1757855308084834"></a><a name="p1757855308084834"></a><a href="UTILS.md#gad5fd70aa458e05eaec03bb88d5eefdef">wcscasecmp_l</a> (const wchar_t *s1, const wchar_t *s2, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1562160699084834"><a name="p1562160699084834"></a><a name="p1562160699084834"></a>int&nbsp;</p>
<p id="p238984724084834"><a name="p238984724084834"></a><a name="p238984724084834"></a>Compares the wide characters in the string pointed to by <strong id="b1842682516084834"><a name="b1842682516084834"></a><a name="b1842682516084834"></a>s1</strong> with those in the string pointed to by <strong id="b39265630084834"><a name="b39265630084834"></a><a name="b39265630084834"></a>s2</strong> based on the specified <strong id="b450249623084834"><a name="b450249623084834"></a><a name="b450249623084834"></a>locale</strong> environment, with their case differences ignored. </p>
</td>
</tr>
<tr id="row296075646084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p531853184084834"><a name="p531853184084834"></a><a name="p531853184084834"></a><a href="UTILS.md#ga5c9957285778ae41af839bb22cc4a9d0">wcsncasecmp</a> (const wchar_t *s1, const wchar_t *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1834490778084834"><a name="p1834490778084834"></a><a name="p1834490778084834"></a>int&nbsp;</p>
<p id="p1874717670084834"><a name="p1874717670084834"></a><a name="p1874717670084834"></a>Compares a maximum of <strong id="b1442683716084834"><a name="b1442683716084834"></a><a name="b1442683716084834"></a>n</strong> wide characters in the string pointed to by <strong id="b399816718084834"><a name="b399816718084834"></a><a name="b399816718084834"></a>s1</strong> with those in the string pointed to by <strong id="b1060725053084834"><a name="b1060725053084834"></a><a name="b1060725053084834"></a>s2</strong>, with their case differences ignored. </p>
</td>
</tr>
<tr id="row544289111084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p604668733084834"><a name="p604668733084834"></a><a name="p604668733084834"></a><a href="UTILS.md#ga157e21d5005c4af440f8fe0407dab8ec">wcsncasecmp_l</a> (const wchar_t *s1, const wchar_t *s2, size_t n, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773196915084834"><a name="p1773196915084834"></a><a name="p1773196915084834"></a>int&nbsp;</p>
<p id="p1076431737084834"><a name="p1076431737084834"></a><a name="p1076431737084834"></a>Compares a maximum of <strong id="b484139596084834"><a name="b484139596084834"></a><a name="b484139596084834"></a>n</strong> wide characters in the string pointed to by <strong id="b994120730084834"><a name="b994120730084834"></a><a name="b994120730084834"></a>s1</strong> with those in the string pointed to by <strong id="b555544995084834"><a name="b555544995084834"></a><a name="b555544995084834"></a>s2</strong> based on the specified <strong id="b693287411084834"><a name="b693287411084834"></a><a name="b693287411084834"></a>locale</strong> environment, with their case differences ignored. </p>
</td>
</tr>
<tr id="row214481559084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896442894084834"><a name="p1896442894084834"></a><a name="p1896442894084834"></a><a href="UTILS.md#ga8bdd5a976685e97d9ac7f45f7951a52c">wcscoll_l</a> (const wchar_t *s1, const wchar_t *s2, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513619486084834"><a name="p1513619486084834"></a><a name="p1513619486084834"></a>int&nbsp;</p>
<p id="p1607315292084834"><a name="p1607315292084834"></a><a name="p1607315292084834"></a>Compares wide characters in the string pointed to by <strong id="b1179284825084834"><a name="b1179284825084834"></a><a name="b1179284825084834"></a>s1</strong> with those in the string pointed to by <strong id="b808501313084834"><a name="b808501313084834"></a><a name="b808501313084834"></a>s2</strong> based on the specified <strong id="b939933876084834"><a name="b939933876084834"></a><a name="b939933876084834"></a>locale</strong> environment. </p>
</td>
</tr>
<tr id="row1508745774084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217723987084834"><a name="p1217723987084834"></a><a name="p1217723987084834"></a><a href="UTILS.md#ga215d4539e43613e57c992b87158084b4">wcsftime</a> (wchar_t *__restrict wcs, size_t n, const wchar_t *__restrict f, const struct <a href="tm.md">tm</a> *__restrict <a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2063873487084834"><a name="p2063873487084834"></a><a name="p2063873487084834"></a>size_t&nbsp;</p>
<p id="p1612925509084834"><a name="p1612925509084834"></a><a name="p1612925509084834"></a>Converts the date and time in the <strong id="b1811259919084834"><a name="b1811259919084834"></a><a name="b1811259919084834"></a>tm</strong> structure to a wide character string. </p>
</td>
</tr>
<tr id="row1899844758084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206263866084834"><a name="p206263866084834"></a><a name="p206263866084834"></a><a href="UTILS.md#gadd93407a6dc241056ae5198b356f07d4">wcsxfrm_l</a> (wchar_t *s1, const wchar_t *s2, size_t n, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2129932035084834"><a name="p2129932035084834"></a><a name="p2129932035084834"></a>size_t&nbsp;</p>
<p id="p834997624084834"><a name="p834997624084834"></a><a name="p834997624084834"></a>Compares the first <strong id="b2129674274084834"><a name="b2129674274084834"></a><a name="b2129674274084834"></a>n</strong> wide characters in the string pointed to by <strong id="b1621496759084834"><a name="b1621496759084834"></a><a name="b1621496759084834"></a>s1</strong> with those in the string pointed to by <strong id="b1055194380084834"><a name="b1055194380084834"></a><a name="b1055194380084834"></a>s2</strong> based on the specified <strong id="b2043215186084834"><a name="b2043215186084834"></a><a name="b2043215186084834"></a>locale</strong> environment. </p>
</td>
</tr>
</tbody>
</table>

