# fmtmsg.h<a name="ZH-CN_TOPIC_0000001055387982"></a>

## **Overview**<a name="section1421740106084829"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Provides a function for printing formatted messages. 

You can use the function in the file to write messages \(especially error messages\) into the output device specified by  **classification**.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section188608256084829"></a>

## Macros<a name="define-members"></a>

<a name="table1050600159084829"></a>
<table><thead align="left"><tr id="row1747719729084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p651338886084829"><a name="p651338886084829"></a><a name="p651338886084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p813353658084829"><a name="p813353658084829"></a><a name="p813353658084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row595402911084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p989910487084829"><a name="p989910487084829"></a><a name="p989910487084829"></a><a href="UTILS.md#ga7250644aab1a485bd6a24720d2867ad8">MM_HARD</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p99496457084829"><a name="p99496457084829"></a><a name="p99496457084829"></a>A hardware error occurred. </p>
</td>
</tr>
<tr id="row1039139343084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527759427084829"><a name="p1527759427084829"></a><a name="p1527759427084829"></a><a href="UTILS.md#ga95d4386c5cab57599cf9fdad75dbd9ef">MM_SOFT</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2022339565084829"><a name="p2022339565084829"></a><a name="p2022339565084829"></a>A software error occurred. </p>
</td>
</tr>
<tr id="row731862055084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p623502387084829"><a name="p623502387084829"></a><a name="p623502387084829"></a><a href="UTILS.md#gaad8873c0512aaad8e20a95d8d7867fa6">MM_FIRM</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p112584848084829"><a name="p112584848084829"></a><a name="p112584848084829"></a>A firmware error occurred. </p>
</td>
</tr>
<tr id="row1128258933084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006318538084829"><a name="p2006318538084829"></a><a name="p2006318538084829"></a><a href="UTILS.md#ga9c8b88fc46ddd4d418c05b4c5c685786">MM_APPL</a>&nbsp;&nbsp;&nbsp;8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416540288084829"><a name="p416540288084829"></a><a name="p416540288084829"></a>An error is detected by an application. </p>
</td>
</tr>
<tr id="row294236386084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645610336084829"><a name="p645610336084829"></a><a name="p645610336084829"></a><a href="UTILS.md#ga5b43fa612f8e72db32d32385192f5bd9">MM_UTIL</a>&nbsp;&nbsp;&nbsp;16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p696835301084829"><a name="p696835301084829"></a><a name="p696835301084829"></a>An error is detected by a utility. </p>
</td>
</tr>
<tr id="row1184547156084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748303635084829"><a name="p748303635084829"></a><a name="p748303635084829"></a><a href="UTILS.md#ga3257723578ef85fb0cef91ac18a6a8e9">MM_OPSYS</a>&nbsp;&nbsp;&nbsp;32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1102924964084829"><a name="p1102924964084829"></a><a name="p1102924964084829"></a>An error is detected by the operating system. </p>
</td>
</tr>
<tr id="row729742812084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2127505406084829"><a name="p2127505406084829"></a><a name="p2127505406084829"></a><a href="UTILS.md#ga655710ff6f4600613aba693f2c933844">MM_RECOVER</a>&nbsp;&nbsp;&nbsp;64</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1581228245084829"><a name="p1581228245084829"></a><a name="p1581228245084829"></a>The error is recoverable. </p>
</td>
</tr>
<tr id="row1681081749084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1745978810084829"><a name="p1745978810084829"></a><a name="p1745978810084829"></a><a href="UTILS.md#gaac7ced5531ea5e8af060a12930bd930b">MM_NRECOV</a>&nbsp;&nbsp;&nbsp;128</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979351813084829"><a name="p979351813084829"></a><a name="p979351813084829"></a>The error is non-recoverable. </p>
</td>
</tr>
<tr id="row118318873084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p154207748084829"><a name="p154207748084829"></a><a name="p154207748084829"></a><a href="UTILS.md#ga28f8601bbd8dfa8c1a1133892dbaaeaf">MM_PRINT</a>&nbsp;&nbsp;&nbsp;256</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p63758305084829"><a name="p63758305084829"></a><a name="p63758305084829"></a>Prints error messages on standard error (stderr). </p>
</td>
</tr>
<tr id="row796687722084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1716010845084829"><a name="p1716010845084829"></a><a name="p1716010845084829"></a><a href="UTILS.md#ga28df3705304c876e17ee22267eaa01af">MM_CONSOLE</a>&nbsp;&nbsp;&nbsp;512</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70600180084829"><a name="p70600180084829"></a><a name="p70600180084829"></a>Prints error messages on the system console. </p>
</td>
</tr>
<tr id="row1795315906084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1720610496084829"><a name="p1720610496084829"></a><a name="p1720610496084829"></a><a href="UTILS.md#ga0d1ed1880858b3eb76f4173619c58c40">MM_NULLMC</a>&nbsp;&nbsp;&nbsp;0L</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713812929084829"><a name="p1713812929084829"></a><a name="p1713812929084829"></a>Ignores the <strong id="b2093917200084829"><a name="b2093917200084829"></a><a name="b2093917200084829"></a>classification</strong> parameter. </p>
</td>
</tr>
<tr id="row1004149936084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p843142409084829"><a name="p843142409084829"></a><a name="p843142409084829"></a><a href="UTILS.md#ga3d5f92b4ab4f31431e764e04cd74de61">MM_HALT</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p811103720084829"><a name="p811103720084829"></a><a name="p811103720084829"></a>Fatal fault. </p>
</td>
</tr>
<tr id="row412352148084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1032508375084829"><a name="p1032508375084829"></a><a name="p1032508375084829"></a><a href="UTILS.md#ga691f4cd7904d1f6579e093fb40226b98">MM_ERROR</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209326365084829"><a name="p1209326365084829"></a><a name="p1209326365084829"></a>Error-level fault. </p>
</td>
</tr>
<tr id="row1180145008084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1450940611084829"><a name="p1450940611084829"></a><a name="p1450940611084829"></a><a href="UTILS.md#ga277b9951914986b139db5750177091f3">MM_WARNING</a>&nbsp;&nbsp;&nbsp;3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217182707084829"><a name="p217182707084829"></a><a name="p217182707084829"></a>Warning condition. </p>
</td>
</tr>
<tr id="row323138745084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892155226084829"><a name="p1892155226084829"></a><a name="p1892155226084829"></a><a href="UTILS.md#ga0c65f03a4d4009ddbc8b318c4cca2662">MM_INFO</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2023984823084829"><a name="p2023984823084829"></a><a name="p2023984823084829"></a>Informative message. </p>
</td>
</tr>
<tr id="row105933198084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2008098897084829"><a name="p2008098897084829"></a><a name="p2008098897084829"></a><a href="UTILS.md#gaf4e60c7def20483a91f2c85b9a98420c">MM_NOSEV</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p513506778084829"><a name="p513506778084829"></a><a name="p513506778084829"></a>No severity level is set, equivalent to <a href="UTILS.md#gad65c53433554559cdc93e413786cc981">MM_NULLSEV</a>. </p>
</td>
</tr>
<tr id="row1247527313084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1690190769084829"><a name="p1690190769084829"></a><a name="p1690190769084829"></a><a href="UTILS.md#ga2d55c51901766d6400ea645cfaa56ad7">MM_OK</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1192167180084829"><a name="p1192167180084829"></a><a name="p1192167180084829"></a>The function succeeded. </p>
</td>
</tr>
<tr id="row415118995084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1710324645084829"><a name="p1710324645084829"></a><a name="p1710324645084829"></a><a href="UTILS.md#ga6c6fa7e4345318cb7b7a12a6492f414b">MM_NOTOK</a>&nbsp;&nbsp;&nbsp;(-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566351378084829"><a name="p1566351378084829"></a><a name="p1566351378084829"></a>The function failed. </p>
</td>
</tr>
<tr id="row946486379084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1486767312084829"><a name="p1486767312084829"></a><a name="p1486767312084829"></a><a href="UTILS.md#ga16ba492651e5414d28fbca6da09999e2">MM_NOMSG</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891638478084829"><a name="p891638478084829"></a><a name="p891638478084829"></a>Error writing to stderr. </p>
</td>
</tr>
<tr id="row1616309604084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339707583084829"><a name="p339707583084829"></a><a name="p339707583084829"></a><a href="UTILS.md#ga47ee40d662d07179517362f5796fedc6">MM_NOCON</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p469511394084829"><a name="p469511394084829"></a><a name="p469511394084829"></a>Error writing to the console. </p>
</td>
</tr>
<tr id="row95603939084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051672983084829"><a name="p2051672983084829"></a><a name="p2051672983084829"></a><a href="UTILS.md#ga174d0d4b9bbda298cd1faec4d4f27202">MM_NULLLBL</a>&nbsp;&nbsp;&nbsp;((char*)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p62879517084829"><a name="p62879517084829"></a><a name="p62879517084829"></a>Ignores the <strong id="b2060853437084829"><a name="b2060853437084829"></a><a name="b2060853437084829"></a>label</strong> parameter. </p>
</td>
</tr>
<tr id="row464007440084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p854369195084829"><a name="p854369195084829"></a><a name="p854369195084829"></a><a href="UTILS.md#ga345476b2492fd41e52ec6cbb08265b07">MM_NULLTXT</a>&nbsp;&nbsp;&nbsp;((char*)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1033751080084829"><a name="p1033751080084829"></a><a name="p1033751080084829"></a>Ignores the <strong id="b640462846084829"><a name="b640462846084829"></a><a name="b640462846084829"></a>text</strong> parameter. </p>
</td>
</tr>
<tr id="row327781867084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1884824031084829"><a name="p1884824031084829"></a><a name="p1884824031084829"></a><a href="UTILS.md#ga715bfd49536d249ea7812a4114602db0">MM_NULLACT</a>&nbsp;&nbsp;&nbsp;((char*)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731137933084829"><a name="p731137933084829"></a><a name="p731137933084829"></a>Ignores the <strong id="b1368338422084829"><a name="b1368338422084829"></a><a name="b1368338422084829"></a>action</strong> parameter. </p>
</td>
</tr>
<tr id="row826624136084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2049280298084829"><a name="p2049280298084829"></a><a name="p2049280298084829"></a><a href="UTILS.md#ga64da80d889e56fc4dc22b0d8e07576cc">MM_NULLTAG</a>&nbsp;&nbsp;&nbsp;((char*)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p513441115084829"><a name="p513441115084829"></a><a name="p513441115084829"></a>Ignores the <strong id="b1967136865084829"><a name="b1967136865084829"></a><a name="b1967136865084829"></a>tag</strong> parameter. </p>
</td>
</tr>
<tr id="row2038831038084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1585960418084829"><a name="p1585960418084829"></a><a name="p1585960418084829"></a><a href="UTILS.md#gad65c53433554559cdc93e413786cc981">MM_NULLSEV</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1738733271084829"><a name="p1738733271084829"></a><a name="p1738733271084829"></a>Ignores the <strong id="b705006479084829"><a name="b705006479084829"></a><a name="b705006479084829"></a>severity</strong> parameter. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table607174892084829"></a>
<table><thead align="left"><tr id="row902436941084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p427285574084829"><a name="p427285574084829"></a><a name="p427285574084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1898596466084829"><a name="p1898596466084829"></a><a name="p1898596466084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1483351862084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817191135084829"><a name="p1817191135084829"></a><a name="p1817191135084829"></a><a href="UTILS.md#ga41115d5b017933dcee85d41ed7a743e7">fmtmsg</a> (long classification, const char *label, int severity, const char *text, const char *action, const char *tag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930101098084829"><a name="p1930101098084829"></a><a name="p1930101098084829"></a>int&nbsp;</p>
<p id="p370682208084829"><a name="p370682208084829"></a><a name="p370682208084829"></a>Prints formatted messages. </p>
</td>
</tr>
</tbody>
</table>

