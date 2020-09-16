# glob.h<a name="ZH-CN_TOPIC_0000001055308033"></a>

## **Overview**<a name="section572754746084829"></a>

**Related Modules:**

[FS](FS.md)

**Description:**

Provides functions and structures used to find path names matching a pattern and release the memory that was applied for during the search. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1552077715084829"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table851029188084829"></a>
<table><thead align="left"><tr id="row1182889479084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p801071897084829"><a name="p801071897084829"></a><a name="p801071897084829"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1624095394084829"><a name="p1624095394084829"></a><a name="p1624095394084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row437299338084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1445595099084829"><a name="p1445595099084829"></a><a name="p1445595099084829"></a><a href="glob_t.md">glob_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074953724084829"><a name="p1074953724084829"></a><a name="p1074953724084829"></a>Defines the search information. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1269791357084829"></a>
<table><thead align="left"><tr id="row921111961084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1243014806084829"><a name="p1243014806084829"></a><a name="p1243014806084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p65923406084829"><a name="p65923406084829"></a><a name="p65923406084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1523967329084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1546194649084829"><a name="p1546194649084829"></a><a name="p1546194649084829"></a><a href="FS.md#ga9e77b0b20a1c1d66cdf924a07776f360">GLOB_ERR</a>&nbsp;&nbsp;&nbsp;0x01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1691670328084829"><a name="p1691670328084829"></a><a name="p1691670328084829"></a>Return upon a read error. </p>
</td>
</tr>
<tr id="row1829501756084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920297224084829"><a name="p920297224084829"></a><a name="p920297224084829"></a><a href="FS.md#gac6ec2b6ae844d895de9685a689dd27f0">GLOB_MARK</a>&nbsp;&nbsp;&nbsp;0x02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p391599919084829"><a name="p391599919084829"></a><a name="p391599919084829"></a>Append a slash (/) to each path, which corresponds to a directory. </p>
</td>
</tr>
<tr id="row1415074615084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p643612401084829"><a name="p643612401084829"></a><a name="p643612401084829"></a><a href="FS.md#ga4eba6cedebdfe13f924d9b4a489bfe83">GLOB_NOSORT</a>&nbsp;&nbsp;&nbsp;0x04</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p704089182084829"><a name="p704089182084829"></a><a name="p704089182084829"></a>Do not sort the returned path names. </p>
</td>
</tr>
<tr id="row89617264084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842829892084829"><a name="p842829892084829"></a><a name="p842829892084829"></a><a href="FS.md#ga8ae13e97ae5da0993fe526c406337c62">GLOB_DOOFFS</a>&nbsp;&nbsp;&nbsp;0x08</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1406679358084829"><a name="p1406679358084829"></a><a name="p1406679358084829"></a>In the <strong id="b841089712084829"><a name="b841089712084829"></a><a name="b841089712084829"></a>pglob</strong> parameter of the <a href="FS.md#gae98601409da7fd3c85a9c219e1a9020c">glob()</a> function, reserve a string that has a length of <strong id="b1578675804084829"><a name="b1578675804084829"></a><a name="b1578675804084829"></a>pglob-&gt;gl_offs</strong> and ends with <strong id="b89235847084829"><a name="b89235847084829"></a><a name="b89235847084829"></a>\0</strong> at the beginning of the string list in <strong id="b452447406084829"><a name="b452447406084829"></a><a name="b452447406084829"></a>pglob-&gt;pathv</strong>. That is, the newly matched string is appended to a position where the distance from the beginning of <strong id="b1122246771084829"><a name="b1122246771084829"></a><a name="b1122246771084829"></a>pglob-&gt;pathv</strong> is the length of <strong id="b1229170861084829"><a name="b1229170861084829"></a><a name="b1229170861084829"></a>pglob-&gt;gl_offs</strong>. </p>
</td>
</tr>
<tr id="row2030229998084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1518127165084829"><a name="p1518127165084829"></a><a name="p1518127165084829"></a><a href="FS.md#gaf183b2f40936442579be8d62b87e6fc6">GLOB_NOCHECK</a>&nbsp;&nbsp;&nbsp;0x10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2102044908084829"><a name="p2102044908084829"></a><a name="p2102044908084829"></a>If no pattern matches, return the original pattern. </p>
</td>
</tr>
<tr id="row1218378541084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272514364084829"><a name="p1272514364084829"></a><a name="p1272514364084829"></a><a href="FS.md#ga7e586df07bb159e904a61d8470f1fda2">GLOB_APPEND</a>&nbsp;&nbsp;&nbsp;0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226142420084829"><a name="p1226142420084829"></a><a name="p1226142420084829"></a>Append the results of this call to the results returned by a previous call to <strong id="b454526392084829"><a name="b454526392084829"></a><a name="b454526392084829"></a><a href="FS.md#gae98601409da7fd3c85a9c219e1a9020c">glob()</a></strong>. </p>
</td>
</tr>
<tr id="row1816525675084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p78832252084829"><a name="p78832252084829"></a><a name="p78832252084829"></a><a href="FS.md#gad21c37825788f86d5fefea803276f746">GLOB_NOESCAPE</a>&nbsp;&nbsp;&nbsp;0x40</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p651301932084829"><a name="p651301932084829"></a><a name="p651301932084829"></a>Do not use a backslash () as an escape character. </p>
</td>
</tr>
<tr id="row20199397084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712475689084829"><a name="p1712475689084829"></a><a name="p1712475689084829"></a><a href="FS.md#gab548aece9c1254c6c08475ce8c6274a2">GLOB_PERIOD</a>&nbsp;&nbsp;&nbsp;0x80</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630660745084829"><a name="p630660745084829"></a><a name="p630660745084829"></a>Allow a leading period to be matched by metacharacters. </p>
</td>
</tr>
<tr id="row2113776536084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p533481697084829"><a name="p533481697084829"></a><a name="p533481697084829"></a><a href="FS.md#ga4f1c6c0dae8dfefcf3032fed1b5cd0fe">GLOB_TILDE</a>&nbsp;&nbsp;&nbsp;0x1000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p407837023084829"><a name="p407837023084829"></a><a name="p407837023084829"></a>Carry out tilde expansion. If a tilde (~) is the only character in the pattern, or an initial tilde is followed immediately by a slash (/), then the home directory of the caller is substituted for the tilde. </p>
</td>
</tr>
<tr id="row1250078573084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p674181761084829"><a name="p674181761084829"></a><a name="p674181761084829"></a><a href="FS.md#gacf779f5283225f7a1507122f75418103">GLOB_TILDE_CHECK</a>&nbsp;&nbsp;&nbsp;0x4000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p690783592084829"><a name="p690783592084829"></a><a name="p690783592084829"></a>Similar to <a href="FS.md#ga4f1c6c0dae8dfefcf3032fed1b5cd0fe">GLOB_TILDE</a>. The difference is that if the username is invalid, or the home directory cannot be determined, <a href="FS.md#gae98601409da7fd3c85a9c219e1a9020c">glob()</a> returns <a href="FS.md#gaed760cf90fd4398067cdb679ebe60312">GLOB_NOMATCH</a> to indicate an error. </p>
</td>
</tr>
<tr id="row1761579581084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1973854846084829"><a name="p1973854846084829"></a><a name="p1973854846084829"></a><a href="FS.md#gab53de39e075e6fb9a11678341772930b">GLOB_NOSPACE</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893738568084829"><a name="p893738568084829"></a><a name="p893738568084829"></a>Memory insufficient. </p>
</td>
</tr>
<tr id="row277775868084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382589757084829"><a name="p382589757084829"></a><a name="p382589757084829"></a><a href="FS.md#gab5de50cedafa21283878657d05fb2ba8">GLOB_ABORTED</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1211067513084829"><a name="p1211067513084829"></a><a name="p1211067513084829"></a>Read error. </p>
</td>
</tr>
<tr id="row61784323084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p231068112084829"><a name="p231068112084829"></a><a name="p231068112084829"></a><a href="FS.md#gaed760cf90fd4398067cdb679ebe60312">GLOB_NOMATCH</a>&nbsp;&nbsp;&nbsp;3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p483883906084829"><a name="p483883906084829"></a><a name="p483883906084829"></a>No matching item is found. </p>
</td>
</tr>
<tr id="row1860085201084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727072868084829"><a name="p727072868084829"></a><a name="p727072868084829"></a><a href="FS.md#ga121ff4729e5e2d403808f90e6a47a113">GLOB_NOSYS</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p431372935084829"><a name="p431372935084829"></a><a name="p431372935084829"></a>The function is not supported. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1197976783084829"></a>
<table><thead align="left"><tr id="row482465376084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p23349820084829"><a name="p23349820084829"></a><a name="p23349820084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p250473037084829"><a name="p250473037084829"></a><a name="p250473037084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row976811098084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p759945964084829"><a name="p759945964084829"></a><a name="p759945964084829"></a><a href="FS.md#gae98601409da7fd3c85a9c219e1a9020c">glob</a> (const char *__restrict pattern, int flags, int(*errfunc)(const char *, int), <a href="glob_t.md">glob_t</a> *__restrict pglob)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2123944530084829"><a name="p2123944530084829"></a><a name="p2123944530084829"></a>int&nbsp;</p>
<p id="p1133187975084829"><a name="p1133187975084829"></a><a name="p1133187975084829"></a>Searches for path names that meet a specified pattern. </p>
</td>
</tr>
<tr id="row1954828514084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p749775914084829"><a name="p749775914084829"></a><a name="p749775914084829"></a><a href="FS.md#gaa43d417234c8572d6e98fb1dc12a4794">globfree</a> (<a href="glob_t.md">glob_t</a> *pglob)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1758449252084829"><a name="p1758449252084829"></a><a name="p1758449252084829"></a>void&nbsp;</p>
<p id="p1904510346084829"><a name="p1904510346084829"></a><a name="p1904510346084829"></a>Frees allocated memory from a call to <strong id="b2116342122084829"><a name="b2116342122084829"></a><a name="b2116342122084829"></a><a href="FS.md#gae98601409da7fd3c85a9c219e1a9020c">glob()</a></strong>. </p>
</td>
</tr>
</tbody>
</table>

