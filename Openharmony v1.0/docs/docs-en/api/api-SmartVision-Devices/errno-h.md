# errno.h<a name="EN-US_TOPIC_0000001055069404"></a>

## **Overview**<a name="section637297759084829"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Defines error codes. 

You can view the value of  **errno**  to check the error code definition in this file to preliminarily locate the fault. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section354120149084829"></a>

## Macros<a name="define-members"></a>

<a name="table2014736502084829"></a>
<table><thead align="left"><tr id="row1671428491084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1620671699084829"><a name="p1620671699084829"></a><a name="p1620671699084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p825446283084829"><a name="p825446283084829"></a><a name="p825446283084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2038657420084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1991265780084829"><a name="p1991265780084829"></a><a name="p1991265780084829"></a><a href="utils.md#gadd669d31505a077f769cff8e66c780b3">EPERM</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p834412211084829"><a name="p834412211084829"></a><a name="p834412211084829"></a>Operation not permitted. </p>
</td>
</tr>
<tr id="row832686078084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1226206104084829"><a name="p1226206104084829"></a><a name="p1226206104084829"></a><a href="utils.md#ga03e689f378f643d16ea7537918528a48">ENOENT</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338043402084829"><a name="p1338043402084829"></a><a name="p1338043402084829"></a>No such file or path. </p>
</td>
</tr>
<tr id="row1366840124084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1264593720084829"><a name="p1264593720084829"></a><a name="p1264593720084829"></a><a href="utils.md#ga462e47a8af6288232a5df548221ada4c">ESRCH</a>   3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p185553493084829"><a name="p185553493084829"></a><a name="p185553493084829"></a>No such process. </p>
</td>
</tr>
<tr id="row1722100994084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1597876899084829"><a name="p1597876899084829"></a><a name="p1597876899084829"></a><a href="utils.md#ga46b83d9f6c23b1b65a8cecfd775ddaed">EINTR</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700136670084829"><a name="p1700136670084829"></a><a name="p1700136670084829"></a>Interrupted function call. </p>
</td>
</tr>
<tr id="row2053289866084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p512182067084829"><a name="p512182067084829"></a><a name="p512182067084829"></a><a href="utils.md#ga70979f50f9c83e5aebab3d6a1bd4cf35">EIO</a>   5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p87657803084829"><a name="p87657803084829"></a><a name="p87657803084829"></a>I/O error. </p>
</td>
</tr>
<tr id="row984703120084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p873690716084829"><a name="p873690716084829"></a><a name="p873690716084829"></a><a href="utils.md#ga2b3884b11e4932bd372bb6d899d6fbfe">ENXIO</a>   6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368848298084829"><a name="p368848298084829"></a><a name="p368848298084829"></a>No such device or address. </p>
</td>
</tr>
<tr id="row657875836084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888753876084829"><a name="p888753876084829"></a><a name="p888753876084829"></a><a href="utils.md#gaba8481985c201ff726f349d7f2d09895">E2BIG</a>   7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1936863934084829"><a name="p1936863934084829"></a><a name="p1936863934084829"></a>Parameter list too long. </p>
</td>
</tr>
<tr id="row502961271084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p802733269084829"><a name="p802733269084829"></a><a name="p802733269084829"></a><a href="utils.md#ga4d0b1b435ec441e7d50a430b83df5832">ENOEXEC</a>   8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1489346337084829"><a name="p1489346337084829"></a><a name="p1489346337084829"></a>Exec format error. </p>
</td>
</tr>
<tr id="row532067612084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452616047084829"><a name="p452616047084829"></a><a name="p452616047084829"></a><a href="utils.md#gac54507d66b43ad12f9356257323c0018">EBADF</a>   9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133110988084829"><a name="p1133110988084829"></a><a name="p1133110988084829"></a>Bad file descriptor. </p>
</td>
</tr>
<tr id="row567436064084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451829797084829"><a name="p1451829797084829"></a><a name="p1451829797084829"></a><a href="utils.md#ga47b42c351e0e011a048058d224205c0f">ECHILD</a>   10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p97895558084829"><a name="p97895558084829"></a><a name="p97895558084829"></a>No child processes. </p>
</td>
</tr>
<tr id="row39718495084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p114999486084829"><a name="p114999486084829"></a><a name="p114999486084829"></a><a href="utils.md#gaf0fac1cea1165b4debec7f686edf3313">EAGAIN</a>   11</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267032329084829"><a name="p267032329084829"></a><a name="p267032329084829"></a>Retry. </p>
</td>
</tr>
<tr id="row1637098232084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701143057084829"><a name="p701143057084829"></a><a name="p701143057084829"></a><a href="utils.md#ga6a05c923dad0c1208043e9c20a58c8e5">ENOMEM</a>   12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844993521084829"><a name="p1844993521084829"></a><a name="p1844993521084829"></a>Not enough memory space. </p>
</td>
</tr>
<tr id="row749625988084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p668355322084829"><a name="p668355322084829"></a><a name="p668355322084829"></a><a href="utils.md#gac2a2e9fa555401f94478f74e01868032">EACCES</a>   13</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623227011084829"><a name="p623227011084829"></a><a name="p623227011084829"></a>Incorrect permission. </p>
</td>
</tr>
<tr id="row1021532668084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p696000028084829"><a name="p696000028084829"></a><a name="p696000028084829"></a><a href="utils.md#ga3f317946e043623f9d6b93dbf60e6316">EFAULT</a>   14</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p760160400084829"><a name="p760160400084829"></a><a name="p760160400084829"></a>Invalid address. </p>
</td>
</tr>
<tr id="row33344247084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748015520084829"><a name="p1748015520084829"></a><a name="p1748015520084829"></a><a href="utils.md#gaa0a4b0e307e83f52be51099f01156936">ENOTBLK</a>   15</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366201857084829"><a name="p366201857084829"></a><a name="p366201857084829"></a>Block device request. </p>
</td>
</tr>
<tr id="row1342301855084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1193835226084829"><a name="p1193835226084829"></a><a name="p1193835226084829"></a><a href="utils.md#ga8368025077a0385849d6817b2007c095">EBUSY</a>   16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p939759686084829"><a name="p939759686084829"></a><a name="p939759686084829"></a>Device or resource busy. </p>
</td>
</tr>
<tr id="row906558083084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250360668084829"><a name="p250360668084829"></a><a name="p250360668084829"></a><a href="utils.md#ga0a3bef9e5c47e42917692b5dae3b5498">EEXIST</a>   17</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551672497084829"><a name="p551672497084829"></a><a name="p551672497084829"></a>File exists. </p>
</td>
</tr>
<tr id="row1966048943084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p528721806084829"><a name="p528721806084829"></a><a name="p528721806084829"></a><a href="utils.md#ga3396cf9fb0ff5af3a18dd2a2bbdb21e1">EXDEV</a>   18</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1618054181084829"><a name="p1618054181084829"></a><a name="p1618054181084829"></a>Incorrect link. </p>
</td>
</tr>
<tr id="row2143293319084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1060837626084829"><a name="p1060837626084829"></a><a name="p1060837626084829"></a><a href="utils.md#gab9b8cc17d1947160d13faaba7a18d6d1">ENODEV</a>   19</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2009172619084829"><a name="p2009172619084829"></a><a name="p2009172619084829"></a>No such device. </p>
</td>
</tr>
<tr id="row1395703295084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785866242084829"><a name="p785866242084829"></a><a name="p785866242084829"></a><a href="utils.md#ga9262fb92f7ef662d0bdd577912a5b101">ENOTDIR</a>   20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p350300369084829"><a name="p350300369084829"></a><a name="p350300369084829"></a>Not a directory. </p>
</td>
</tr>
<tr id="row1462985852084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p62512080084829"><a name="p62512080084829"></a><a name="p62512080084829"></a><a href="utils.md#gae22c3a1e0a38f3896de238cc30d0e19b">EISDIR</a>   21</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083592003084829"><a name="p2083592003084829"></a><a name="p2083592003084829"></a>Is a directory. </p>
</td>
</tr>
<tr id="row964449029084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p78891162084829"><a name="p78891162084829"></a><a name="p78891162084829"></a><a href="utils.md#ga2d1678d5a7cc8ce499643f3b8957def4">EINVAL</a>   22</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1677121690084829"><a name="p1677121690084829"></a><a name="p1677121690084829"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row920752994084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p114676288084829"><a name="p114676288084829"></a><a name="p114676288084829"></a><a href="utils.md#ga5554094b3fb4bb6ebeb0157cb3f82a55">ENFILE</a>   23</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1285038792084829"><a name="p1285038792084829"></a><a name="p1285038792084829"></a>Too many opened files in system (the maximum number exceeded) </p>
</td>
</tr>
<tr id="row394132072084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121748391084829"><a name="p2121748391084829"></a><a name="p2121748391084829"></a><a href="utils.md#ga64a75c174882ddbfa726c7fd040f87a1">EMFILE</a>   24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540248896084829"><a name="p1540248896084829"></a><a name="p1540248896084829"></a>Too many opened files in a process (the maximum number exceeded) </p>
</td>
</tr>
<tr id="row1155755309084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1843086616084829"><a name="p1843086616084829"></a><a name="p1843086616084829"></a><a href="utils.md#gac3daf409082bb528032f4452a81e1034">ENOTTY</a>   25</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1992708686084829"><a name="p1992708686084829"></a><a name="p1992708686084829"></a>Inappropriate I/O control operation. </p>
</td>
</tr>
<tr id="row781875283084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1380628301084829"><a name="p1380628301084829"></a><a name="p1380628301084829"></a><a href="utils.md#gaaed12e82224923d599b6f1939c8e0971">ETXTBSY</a>   26</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765479692084829"><a name="p765479692084829"></a><a name="p765479692084829"></a>Text file busy. </p>
</td>
</tr>
<tr id="row1200798232084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1824167779084829"><a name="p1824167779084829"></a><a name="p1824167779084829"></a><a href="utils.md#gaf5401a500939ed1812c04ca200b95eef">EFBIG</a>   27</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034218911084829"><a name="p2034218911084829"></a><a name="p2034218911084829"></a>File too large. </p>
</td>
</tr>
<tr id="row2014232588084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1659748348084829"><a name="p1659748348084829"></a><a name="p1659748348084829"></a><a href="utils.md#ga088abe8bad2df798edad3053d719b937">ENOSPC</a>   28</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1778942104084829"><a name="p1778942104084829"></a><a name="p1778942104084829"></a>No space left on device. </p>
</td>
</tr>
<tr id="row1547265692084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307844366084829"><a name="p1307844366084829"></a><a name="p1307844366084829"></a><a href="utils.md#ga0e42d4f9fecdcf5fcca2b333252173c3">ESPIPE</a>   29</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p534952477084829"><a name="p534952477084829"></a><a name="p534952477084829"></a>Invalid query. </p>
</td>
</tr>
<tr id="row510319479084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1141156736084829"><a name="p1141156736084829"></a><a name="p1141156736084829"></a><a href="utils.md#gacb02bb67dddd7ca8cf82634a0781d58d">EROFS</a>   30</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p93240863084829"><a name="p93240863084829"></a><a name="p93240863084829"></a>Read-only file system. </p>
</td>
</tr>
<tr id="row207975409084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p65740834084829"><a name="p65740834084829"></a><a name="p65740834084829"></a><a href="utils.md#ga97f59fa1a5a2f61b792c1b9dfc218072">EMLINK</a>   31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1862935346084829"><a name="p1862935346084829"></a><a name="p1862935346084829"></a>Too many links. </p>
</td>
</tr>
<tr id="row1132922281084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1592603240084829"><a name="p1592603240084829"></a><a name="p1592603240084829"></a><a href="utils.md#ga5f8d33deb08fa27c04897b278ac7f965">EPIPE</a>   32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924271651084829"><a name="p924271651084829"></a><a name="p924271651084829"></a>The pipe file is incorrect or the read end of the pipe is closed during the write operation. </p>
</td>
</tr>
<tr id="row1317151696084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643153448084829"><a name="p1643153448084829"></a><a name="p1643153448084829"></a><a href="utils.md#ga5fe247e079b591a68e0fdbf7caec5b70">EDOM</a>   33</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1171021233084829"><a name="p1171021233084829"></a><a name="p1171021233084829"></a>Domain error. The value of at least one input parameter is out of the parameter range. </p>
</td>
</tr>
<tr id="row1130052797084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p818006687084829"><a name="p818006687084829"></a><a name="p818006687084829"></a><a href="utils.md#gaa1591a4f3a86360108de5b9ba34980ca">ERANGE</a>   34</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1123882576084829"><a name="p1123882576084829"></a><a name="p1123882576084829"></a>The actual return value exceeds the return value range. </p>
</td>
</tr>
<tr id="row540528757084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544882085084829"><a name="p1544882085084829"></a><a name="p1544882085084829"></a><a href="utils.md#ga55cc70ce0ba661298f3c412095dfeeb6">EDEADLK</a>   35</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p799889911084829"><a name="p799889911084829"></a><a name="p799889911084829"></a>Resource deadlock. </p>
</td>
</tr>
<tr id="row1970527250084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1956290571084829"><a name="p1956290571084829"></a><a name="p1956290571084829"></a><a href="utils.md#ga41d5ab3a8a05f9c5eab536c9cfba305b">ENAMETOOLONG</a>   36</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1574526907084829"><a name="p1574526907084829"></a><a name="p1574526907084829"></a>File name too long. </p>
</td>
</tr>
<tr id="row1721591936084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p5208429084829"><a name="p5208429084829"></a><a name="p5208429084829"></a><a href="utils.md#ga65e1a7bda392be276a701988d0604e63">ENOLCK</a>   37</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755143480084829"><a name="p755143480084829"></a><a name="p755143480084829"></a>No locks available. </p>
</td>
</tr>
<tr id="row483196102084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670587604084829"><a name="p670587604084829"></a><a name="p670587604084829"></a><a href="utils.md#ga43785b9969e0bd1af532dbde06c5540b">ENOSYS</a>   38</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1589861999084829"><a name="p1589861999084829"></a><a name="p1589861999084829"></a>Function not implemented. </p>
</td>
</tr>
<tr id="row1326605949084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044819882084829"><a name="p2044819882084829"></a><a name="p2044819882084829"></a><a href="utils.md#gaa0f602f3fd369a6fede82190710b9c5c">ENOTEMPTY</a>   39</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1993995143084829"><a name="p1993995143084829"></a><a name="p1993995143084829"></a>Directory not empty. </p>
</td>
</tr>
<tr id="row1770114988084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1429104285084829"><a name="p1429104285084829"></a><a name="p1429104285084829"></a><a href="utils.md#ga2f78c246352d2bf2f19dc5d43da2f0c9">ELOOP</a>   40</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672685191084829"><a name="p672685191084829"></a><a name="p672685191084829"></a>Too many levels of symbolic links. </p>
</td>
</tr>
<tr id="row1299485107084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1844184208084829"><a name="p1844184208084829"></a><a name="p1844184208084829"></a><a href="utils.md#ga4a3a0b3605fd3b2336455062ee8e25f0">EWOULDBLOCK</a>   <a href="utils.md#gaf0fac1cea1165b4debec7f686edf3313">EAGAIN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p841884902084829"><a name="p841884902084829"></a><a name="p841884902084829"></a>Operation would block (the same value as <a href="utils.md#gaf0fac1cea1165b4debec7f686edf3313">EAGAIN</a>) </p>
</td>
</tr>
<tr id="row569470340084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1645000850084829"><a name="p1645000850084829"></a><a name="p1645000850084829"></a><a href="utils.md#gae40596feaa3f66f5440b485bf7c1c2d1">ENOMSG</a>   42</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303013732084829"><a name="p1303013732084829"></a><a name="p1303013732084829"></a>No message of the desired type. </p>
</td>
</tr>
<tr id="row819319612084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2113605671084829"><a name="p2113605671084829"></a><a name="p2113605671084829"></a><a href="utils.md#gad9913290fef890d46a6b7e8b4bfb1c29">EIDRM</a>   43</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497405000084829"><a name="p497405000084829"></a><a name="p497405000084829"></a>Identifier removed. </p>
</td>
</tr>
<tr id="row1436188265084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214670435084829"><a name="p214670435084829"></a><a name="p214670435084829"></a><a href="utils.md#ga15d68f826dc2f784d7d3627311e916c1">ECHRNG</a>   44</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522253624084829"><a name="p522253624084829"></a><a name="p522253624084829"></a>Channel number out of range. </p>
</td>
</tr>
<tr id="row969347012084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p905923187084829"><a name="p905923187084829"></a><a name="p905923187084829"></a><a href="utils.md#gacdf97ac22e88c3988c28c9c8f7d14c5e">EL2NSYNC</a>   45</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p818128682084829"><a name="p818128682084829"></a><a name="p818128682084829"></a>Level 2 not synchronized. </p>
</td>
</tr>
<tr id="row1051747769084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665951763084829"><a name="p665951763084829"></a><a name="p665951763084829"></a><a href="utils.md#ga2e4efb348b873846645cd56144b0ea1e">EL3HLT</a>   46</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1863068350084829"><a name="p1863068350084829"></a><a name="p1863068350084829"></a>Level 3 halted. </p>
</td>
</tr>
<tr id="row844820903084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p436011575084829"><a name="p436011575084829"></a><a name="p436011575084829"></a><a href="utils.md#ga5117695086a9942c77befdbd650910cf">EL3RST</a>   47</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124784941084829"><a name="p1124784941084829"></a><a name="p1124784941084829"></a>Level 3 reset. </p>
</td>
</tr>
<tr id="row610983954084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p512751024084829"><a name="p512751024084829"></a><a name="p512751024084829"></a><a href="utils.md#ga059ed0ab5dab96dfe00ffca40b35155f">ELNRNG</a>   48</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1745648993084829"><a name="p1745648993084829"></a><a name="p1745648993084829"></a>Link ID out of range. </p>
</td>
</tr>
<tr id="row1295545761084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1800304629084829"><a name="p1800304629084829"></a><a name="p1800304629084829"></a><a href="utils.md#gac71878d33a396ae1a4e3fe16489f00a9">EUNATCH</a>   49</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p558529131084829"><a name="p558529131084829"></a><a name="p558529131084829"></a>Protocol driver not attached. </p>
</td>
</tr>
<tr id="row63248612084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1273466714084829"><a name="p1273466714084829"></a><a name="p1273466714084829"></a><a href="utils.md#ga2f1893e03a904a500dcb95ff8e35889b">ENOCSI</a>   50</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168085088084829"><a name="p168085088084829"></a><a name="p168085088084829"></a>No available CSI structure. </p>
</td>
</tr>
<tr id="row1063615605084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841389130084829"><a name="p1841389130084829"></a><a name="p1841389130084829"></a><a href="utils.md#ga81a4a94e4d7d996ad5d2a9137539e392">EL2HLT</a>   51</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p604050870084829"><a name="p604050870084829"></a><a name="p604050870084829"></a>Level 2 halted. </p>
</td>
</tr>
<tr id="row931658171084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p545745987084829"><a name="p545745987084829"></a><a name="p545745987084829"></a><a href="utils.md#ga0c17130b2933edfec68b2c70a2cd0a7f">EBADE</a>   52</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657400387084829"><a name="p1657400387084829"></a><a name="p1657400387084829"></a>Invalid exchange. </p>
</td>
</tr>
<tr id="row1672704191084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835068215084829"><a name="p835068215084829"></a><a name="p835068215084829"></a><a href="utils.md#gaca1e9da0ef95864e910f550467d475fa">EBADR</a>   53</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087490591084829"><a name="p2087490591084829"></a><a name="p2087490591084829"></a>Invalid request descriptor. </p>
</td>
</tr>
<tr id="row1597372004084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p349488370084829"><a name="p349488370084829"></a><a name="p349488370084829"></a><a href="utils.md#ga69aa360ec60f24c128556361f7729e48">EXFULL</a>   54</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1132205461084829"><a name="p1132205461084829"></a><a name="p1132205461084829"></a>Exchange full. </p>
</td>
</tr>
<tr id="row1921845031084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804218226084829"><a name="p804218226084829"></a><a name="p804218226084829"></a><a href="utils.md#ga7eb46ddb59ec78bac0de2d45ce2a5053">ENOANO</a>   55</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141877410084829"><a name="p1141877410084829"></a><a name="p1141877410084829"></a>No anode. </p>
</td>
</tr>
<tr id="row1490069677084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600703404084829"><a name="p1600703404084829"></a><a name="p1600703404084829"></a><a href="utils.md#gabe200466dc512a9e314b9cc7d081c1ac">EBADRQC</a>   56</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1562307472084829"><a name="p1562307472084829"></a><a name="p1562307472084829"></a>Invalid request code. </p>
</td>
</tr>
<tr id="row524646910084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50893983084829"><a name="p50893983084829"></a><a name="p50893983084829"></a><a href="utils.md#ga45d8c9818d0bf75ad33ebab50631276a">EBADSLT</a>   57</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p360018571084829"><a name="p360018571084829"></a><a name="p360018571084829"></a>Invalid slot. </p>
</td>
</tr>
<tr id="row1334376665084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1958842580084829"><a name="p1958842580084829"></a><a name="p1958842580084829"></a><a href="utils.md#gacfea92d35e42dd807a7e9beb1e394e4c">EDEADLOCK</a>   <a href="utils.md#ga55cc70ce0ba661298f3c412095dfeeb6">EDEADLK</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213239760084829"><a name="p213239760084829"></a><a name="p213239760084829"></a>Resource deadlock (the same value as <a href="utils.md#ga55cc70ce0ba661298f3c412095dfeeb6">EDEADLK</a>) </p>
</td>
</tr>
<tr id="row121086315084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1196257833084829"><a name="p1196257833084829"></a><a name="p1196257833084829"></a><a href="utils.md#gae4d80808cd12a64d14a3da0d39cad443">EBFONT</a>   59</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p590317647084829"><a name="p590317647084829"></a><a name="p590317647084829"></a>Incorrect font format. </p>
</td>
</tr>
<tr id="row1507391601084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1456658804084829"><a name="p1456658804084829"></a><a name="p1456658804084829"></a><a href="utils.md#ga7cea86ddbdacae0b391674e680f17bdb">ENOSTR</a>   60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308264941084829"><a name="p1308264941084829"></a><a name="p1308264941084829"></a>Not a stream device. </p>
</td>
</tr>
<tr id="row1738595767084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1213747965084829"><a name="p1213747965084829"></a><a name="p1213747965084829"></a><a href="utils.md#ga0030614bc864d1b24eaedd71585acc27">ENODATA</a>   61</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p432406593084829"><a name="p432406593084829"></a><a name="p432406593084829"></a>No message is available on the stream head read queue. </p>
</td>
</tr>
<tr id="row1942103281084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259584261084829"><a name="p1259584261084829"></a><a name="p1259584261084829"></a><a href="utils.md#gab59cf3c65eaf836d5c647fa2a24ca649">ETIME</a>   62</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1092929357084829"><a name="p1092929357084829"></a><a name="p1092929357084829"></a>Timer expired. </p>
</td>
</tr>
<tr id="row1857125359084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1653339222084829"><a name="p1653339222084829"></a><a name="p1653339222084829"></a><a href="utils.md#gad88bc6ea94ec1a5e91d3651677d85c00">ENOSR</a>   63</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p816794481084829"><a name="p816794481084829"></a><a name="p816794481084829"></a>No stream resources. </p>
</td>
</tr>
<tr id="row1238947440084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131312802084829"><a name="p2131312802084829"></a><a name="p2131312802084829"></a><a href="utils.md#ga4a49ca5a72811f9950d2773806eaa641">ENONET</a>   64</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2111495976084829"><a name="p2111495976084829"></a><a name="p2111495976084829"></a>Machine is disconnected from the network. </p>
</td>
</tr>
<tr id="row1344979979084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006663186084829"><a name="p2006663186084829"></a><a name="p2006663186084829"></a><a href="utils.md#ga63fb0df2a890ace70f5093b26cbf7065">ENOPKG</a>   65</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1409039784084829"><a name="p1409039784084829"></a><a name="p1409039784084829"></a>Package not installed. </p>
</td>
</tr>
<tr id="row1597196290084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p606054758084829"><a name="p606054758084829"></a><a name="p606054758084829"></a><a href="utils.md#ga5e1edba49c18fc631dbf54ff53702d4a">EREMOTE</a>   66</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1677835897084829"><a name="p1677835897084829"></a><a name="p1677835897084829"></a>Object is remote. </p>
</td>
</tr>
<tr id="row733734006084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31374691084829"><a name="p31374691084829"></a><a name="p31374691084829"></a><a href="utils.md#gadd4408349a756880be9d91efadb8aed0">ENOLINK</a>   67</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p23577853084829"><a name="p23577853084829"></a><a name="p23577853084829"></a>Link has been severed. </p>
</td>
</tr>
<tr id="row2073471394084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1528300453084829"><a name="p1528300453084829"></a><a name="p1528300453084829"></a><a href="utils.md#ga7ef87d37bfaf88d1ad1de1b531330a42">EADV</a>   68</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1853970924084829"><a name="p1853970924084829"></a><a name="p1853970924084829"></a>Broadcast error. </p>
</td>
</tr>
<tr id="row260241822084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816529445084829"><a name="p816529445084829"></a><a name="p816529445084829"></a><a href="utils.md#gae7df13cc989ed4b6921455a6eff3c249">ESRMNT</a>   69</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1022047294084829"><a name="p1022047294084829"></a><a name="p1022047294084829"></a>srmount error </p>
</td>
</tr>
<tr id="row1604249988084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261580999084829"><a name="p261580999084829"></a><a name="p261580999084829"></a><a href="utils.md#gad9e159536fe852a5679a99a0b8191d69">ECOMM</a>   70</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269253790084829"><a name="p269253790084829"></a><a name="p269253790084829"></a>Communication error on send. </p>
</td>
</tr>
<tr id="row1333659565084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788669784084829"><a name="p788669784084829"></a><a name="p788669784084829"></a><a href="utils.md#ga5a92de56e8ebe19cbd8a2ce8c80ad03e">EPROTO</a>   71</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9122841084829"><a name="p9122841084829"></a><a name="p9122841084829"></a>Protocol error. </p>
</td>
</tr>
<tr id="row1488327368084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978498375084829"><a name="p1978498375084829"></a><a name="p1978498375084829"></a><a href="utils.md#ga4d7b69d7ce0dfa0a9b998403b4ffe226">EMULTIHOP</a>   72</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213805432084829"><a name="p213805432084829"></a><a name="p213805432084829"></a>Multi-hop attempt. </p>
</td>
</tr>
<tr id="row1662433894084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p936000446084829"><a name="p936000446084829"></a><a name="p936000446084829"></a><a href="utils.md#ga66443788a7b1b20f15ac1a67b106f20d">EDOTDOT</a>   73</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1408213406084829"><a name="p1408213406084829"></a><a name="p1408213406084829"></a>RFS-specific error. </p>
</td>
</tr>
<tr id="row1609166880084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024114036084829"><a name="p2024114036084829"></a><a name="p2024114036084829"></a><a href="utils.md#ga251e9b536ed96ccb16aa28ca2d5bd656">EBADMSG</a>   74</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541482921084829"><a name="p1541482921084829"></a><a name="p1541482921084829"></a>Non-data message. </p>
</td>
</tr>
<tr id="row1825831318084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p643109753084829"><a name="p643109753084829"></a><a name="p643109753084829"></a><a href="utils.md#ga888552a5e3c78b5883904cf5d55244ab">EOVERFLOW</a>   75</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1039275215084829"><a name="p1039275215084829"></a><a name="p1039275215084829"></a>Value too large to be represented by the defined data type. </p>
</td>
</tr>
<tr id="row357569920084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1319751427084829"><a name="p1319751427084829"></a><a name="p1319751427084829"></a><a href="utils.md#gafb498fa12135b33c784f3dc4445ce30f">ENOTUNIQ</a>   76</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p241803506084829"><a name="p241803506084829"></a><a name="p241803506084829"></a>Name not unique on the network. </p>
</td>
</tr>
<tr id="row1000543305084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267803649084829"><a name="p1267803649084829"></a><a name="p1267803649084829"></a><a href="utils.md#gae9284c9860c0064da7dd8cba12c1f90f">EBADFD</a>   77</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833040919084829"><a name="p833040919084829"></a><a name="p833040919084829"></a>File descriptor in the bad state. </p>
</td>
</tr>
<tr id="row401068729084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1769440393084829"><a name="p1769440393084829"></a><a name="p1769440393084829"></a><a href="utils.md#gaa8fa21a58da5282010753ae1bed331af">EREMCHG</a>   78</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580279161084829"><a name="p580279161084829"></a><a name="p580279161084829"></a>Remote address changed. </p>
</td>
</tr>
<tr id="row266661063084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188146414084829"><a name="p188146414084829"></a><a name="p188146414084829"></a><a href="utils.md#ga438fa452772ae90a9ccef5d3711bd752">ELIBACC</a>   79</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p542676243084829"><a name="p542676243084829"></a><a name="p542676243084829"></a>Cannot access a needed shared library. </p>
</td>
</tr>
<tr id="row1978076257084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p837992387084829"><a name="p837992387084829"></a><a name="p837992387084829"></a><a href="utils.md#ga6c0c4ad172a62cde82900773c875e259">ELIBBAD</a>   80</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424049095084829"><a name="p424049095084829"></a><a name="p424049095084829"></a>Accessing a corrupted shared library. </p>
</td>
</tr>
<tr id="row1765415910084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856036445084829"><a name="p1856036445084829"></a><a name="p1856036445084829"></a><a href="utils.md#gaf208def3c8b59e39e6fe3d3d97d71a86">ELIBSCN</a>   81</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057814200084829"><a name="p1057814200084829"></a><a name="p1057814200084829"></a>lib section in a.out corrupted </p>
</td>
</tr>
<tr id="row169535881084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1932984056084829"><a name="p1932984056084829"></a><a name="p1932984056084829"></a><a href="utils.md#gad2084b03b9e1c7467ab1b8bdbdfc2fe6">ELIBMAX</a>   82</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1252748193084829"><a name="p1252748193084829"></a><a name="p1252748193084829"></a>Attempting to link in too many shared libraries. </p>
</td>
</tr>
<tr id="row1708158958084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p59446822084829"><a name="p59446822084829"></a><a name="p59446822084829"></a><a href="utils.md#ga95774ff58533d1e67961890ed30f87b2">ELIBEXEC</a>   83</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856474897084829"><a name="p856474897084829"></a><a name="p856474897084829"></a>Cannot execute a shared library directly. </p>
</td>
</tr>
<tr id="row2081894374084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p70704607084829"><a name="p70704607084829"></a><a name="p70704607084829"></a><a href="utils.md#gac6c071293826a4e66a717bb38db7794d">EILSEQ</a>   84</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036273365084829"><a name="p2036273365084829"></a><a name="p2036273365084829"></a>Invalid byte sequence. </p>
</td>
</tr>
<tr id="row1665432774084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1775809658084829"><a name="p1775809658084829"></a><a name="p1775809658084829"></a><a href="utils.md#ga0e5993319c80d5a93ed10b6253878ae5">ERESTART</a>   85</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430051094084829"><a name="p1430051094084829"></a><a name="p1430051094084829"></a>Interrupted system call should be restarted. </p>
</td>
</tr>
<tr id="row1243985689084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p487733447084829"><a name="p487733447084829"></a><a name="p487733447084829"></a><a href="utils.md#ga07773d22c3eb7a4d4ea0696ee5f49841">ESTRPIPE</a>   86</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391656411084829"><a name="p1391656411084829"></a><a name="p1391656411084829"></a>Stream pipe error. </p>
</td>
</tr>
<tr id="row2055664383084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p257969658084829"><a name="p257969658084829"></a><a name="p257969658084829"></a><a href="utils.md#ga9b153104ed38c8579f009f81bc7b2dc9">EUSERS</a>   87</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354697043084829"><a name="p1354697043084829"></a><a name="p1354697043084829"></a>Too many users. </p>
</td>
</tr>
<tr id="row1082340698084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1543057616084829"><a name="p1543057616084829"></a><a name="p1543057616084829"></a><a href="utils.md#gae34fa7a550ac1c415daa2e114a1c0f38">ENOTSOCK</a>   88</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1398712381084829"><a name="p1398712381084829"></a><a name="p1398712381084829"></a>Not a socket. </p>
</td>
</tr>
<tr id="row917410292084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496230343084829"><a name="p496230343084829"></a><a name="p496230343084829"></a><a href="utils.md#ga0e416d3478cf030e37e90c55d68ad97a">EDESTADDRREQ</a>   89</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229490410084829"><a name="p229490410084829"></a><a name="p229490410084829"></a>Destination address required. </p>
</td>
</tr>
<tr id="row1039273465084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757574033084829"><a name="p1757574033084829"></a><a name="p1757574033084829"></a><a href="utils.md#gae37becfaa095a9df5c5c788bce5aa06f">EMSGSIZE</a>   90</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p434156666084829"><a name="p434156666084829"></a><a name="p434156666084829"></a>Message too long. </p>
</td>
</tr>
<tr id="row1096836634084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522388029084829"><a name="p1522388029084829"></a><a name="p1522388029084829"></a><a href="utils.md#gae6014faa948366b8321d755204acf755">EPROTOTYPE</a>   91</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422694218084829"><a name="p422694218084829"></a><a name="p422694218084829"></a>Socket protocol error. </p>
</td>
</tr>
<tr id="row727924240084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p729244848084829"><a name="p729244848084829"></a><a name="p729244848084829"></a><a href="utils.md#gacd570f8ab92198653b4459773dc3bca3">ENOPROTOOPT</a>   92</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994784089084829"><a name="p1994784089084829"></a><a name="p1994784089084829"></a>Protocol not available. </p>
</td>
</tr>
<tr id="row1056377127084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p931649930084829"><a name="p931649930084829"></a><a name="p931649930084829"></a><a href="utils.md#gad581c46fdd4dee9419f60eaff40415e7">EPROTONOSUPPORT</a>   93</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168809021084829"><a name="p168809021084829"></a><a name="p168809021084829"></a>Protocol not supported. </p>
</td>
</tr>
<tr id="row1722639984084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p998586710084829"><a name="p998586710084829"></a><a name="p998586710084829"></a><a href="utils.md#ga891103a0628442461b41d4d85fb6d945">ESOCKTNOSUPPORT</a>   94</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p496967519084829"><a name="p496967519084829"></a><a name="p496967519084829"></a>Socket type not supported. </p>
</td>
</tr>
<tr id="row1673586055084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p6925639084829"><a name="p6925639084829"></a><a name="p6925639084829"></a><a href="utils.md#ga4b807895c74cea4d0302bf27725d4b9d">EOPNOTSUPP</a>   95</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807815840084829"><a name="p807815840084829"></a><a name="p807815840084829"></a>Operation not supported on socket. </p>
</td>
</tr>
<tr id="row1657297023084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p531692337084829"><a name="p531692337084829"></a><a name="p531692337084829"></a><a href="utils.md#ga91457bbf35f0f1085619a99423bb1f33">ENOTSUP</a>   <a href="utils.md#ga4b807895c74cea4d0302bf27725d4b9d">EOPNOTSUPP</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p301804554084829"><a name="p301804554084829"></a><a name="p301804554084829"></a>Operation not supported on socket. The value is the same as that of <a href="utils.md#ga4b807895c74cea4d0302bf27725d4b9d">EOPNOTSUPP</a>. </p>
</td>
</tr>
<tr id="row198130688084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970357879084829"><a name="p1970357879084829"></a><a name="p1970357879084829"></a><a href="utils.md#ga871b9fabb281dbc2d3b81cb79c163c20">EPFNOSUPPORT</a>   96</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1784189876084829"><a name="p1784189876084829"></a><a name="p1784189876084829"></a>Protocol family not supported. </p>
</td>
</tr>
<tr id="row1289358621084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1122492964084829"><a name="p1122492964084829"></a><a name="p1122492964084829"></a><a href="utils.md#ga4c3a793b4d51cb7dd020af92e536fe21">EAFNOSUPPORT</a>   97</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1346550792084829"><a name="p1346550792084829"></a><a name="p1346550792084829"></a>Address family not supported. </p>
</td>
</tr>
<tr id="row309035523084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p966460495084829"><a name="p966460495084829"></a><a name="p966460495084829"></a><a href="utils.md#ga61676e39b42371c65c3b960a91887b03">EADDRINUSE</a>   98</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27436843084829"><a name="p27436843084829"></a><a name="p27436843084829"></a>Address already in use. </p>
</td>
</tr>
<tr id="row1123682102084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2143412988084829"><a name="p2143412988084829"></a><a name="p2143412988084829"></a><a href="utils.md#ga556612e55358838192165684c971a44f">EADDRNOTAVAIL</a>   99</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1404836564084829"><a name="p1404836564084829"></a><a name="p1404836564084829"></a>Address not available. </p>
</td>
</tr>
<tr id="row348837980084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p52841568084829"><a name="p52841568084829"></a><a name="p52841568084829"></a><a href="utils.md#gaac51995026fa19cdd0ad84a272304af0">ENETDOWN</a>   100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p398226740084829"><a name="p398226740084829"></a><a name="p398226740084829"></a>Network is down. </p>
</td>
</tr>
<tr id="row1123021212084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p45217862084829"><a name="p45217862084829"></a><a name="p45217862084829"></a><a href="utils.md#ga3f91f1ad503432783c7a5d1481b45419">ENETUNREACH</a>   101</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418080593084829"><a name="p418080593084829"></a><a name="p418080593084829"></a>Network unreachable. </p>
</td>
</tr>
<tr id="row1247267232084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470359618084829"><a name="p470359618084829"></a><a name="p470359618084829"></a><a href="utils.md#ga92750db73ff8e83591c977bbb3a5bea1">ENETRESET</a>   102</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296242198084829"><a name="p1296242198084829"></a><a name="p1296242198084829"></a>Network disconnection caused by restart. </p>
</td>
</tr>
<tr id="row1741400063084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1335143043084829"><a name="p1335143043084829"></a><a name="p1335143043084829"></a><a href="utils.md#ga45342991e001e28bbf87916d92b7e09a">ECONNABORTED</a>   103</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229162944084829"><a name="p229162944084829"></a><a name="p229162944084829"></a>Network disconnection caused by software problems. </p>
</td>
</tr>
<tr id="row1621978859084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1084580233084829"><a name="p1084580233084829"></a><a name="p1084580233084829"></a><a href="utils.md#gadd4258b08af02fbe4590fbaae7260037">ECONNRESET</a>   104</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p260905948084829"><a name="p260905948084829"></a><a name="p260905948084829"></a>Connection reset. </p>
</td>
</tr>
<tr id="row1548124323084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p887393140084829"><a name="p887393140084829"></a><a name="p887393140084829"></a><a href="utils.md#ga9e655f47bfd914a1174f281fc31cf63d">ENOBUFS</a>   105</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656786864084829"><a name="p656786864084829"></a><a name="p656786864084829"></a>No buffer space available. </p>
</td>
</tr>
<tr id="row780831221084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p976224328084829"><a name="p976224328084829"></a><a name="p976224328084829"></a><a href="utils.md#ga164ca8549da7a385e2fe1cba823b9eaf">EISCONN</a>   106</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p579651673084829"><a name="p579651673084829"></a><a name="p579651673084829"></a>Socket is connected. </p>
</td>
</tr>
<tr id="row677618955084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859032487084829"><a name="p1859032487084829"></a><a name="p1859032487084829"></a><a href="utils.md#gaf23e48762a0676f49d480db91cfd5e4b">ENOTCONN</a>   107</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1584125711084829"><a name="p1584125711084829"></a><a name="p1584125711084829"></a>Socket disconnected. </p>
</td>
</tr>
<tr id="row472772090084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1170982251084829"><a name="p1170982251084829"></a><a name="p1170982251084829"></a><a href="utils.md#ga2a55c5dd8b54ff5aace6c274c6726d68">ESHUTDOWN</a>   108</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p951062810084829"><a name="p951062810084829"></a><a name="p951062810084829"></a>Cannot send after transport endpoint shutdown. </p>
</td>
</tr>
<tr id="row603754402084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1333985317084829"><a name="p1333985317084829"></a><a name="p1333985317084829"></a><a href="utils.md#ga10426080250efba47f4aaf254036ff00">ETOOMANYREFS</a>   109</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926560961084829"><a name="p926560961084829"></a><a name="p926560961084829"></a>Cannot splice due to too many references. </p>
</td>
</tr>
<tr id="row1121972723084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003032955084829"><a name="p2003032955084829"></a><a name="p2003032955084829"></a><a href="utils.md#ga597718e59a8fc9c4d4ab63f5a34e28b1">ETIMEDOUT</a>   110</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p511653346084829"><a name="p511653346084829"></a><a name="p511653346084829"></a>Connection timed out. </p>
</td>
</tr>
<tr id="row1006921910084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p700137598084829"><a name="p700137598084829"></a><a name="p700137598084829"></a><a href="utils.md#gaad88020b394ef1aa4af2f4ef9b4c8b39">ECONNREFUSED</a>   111</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p62380535084829"><a name="p62380535084829"></a><a name="p62380535084829"></a>Connection refused. </p>
</td>
</tr>
<tr id="row207078171084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p383823951084829"><a name="p383823951084829"></a><a name="p383823951084829"></a><a href="utils.md#gaa92bcaf70544db6998f4c503026359c5">EHOSTDOWN</a>   112</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278990845084829"><a name="p1278990845084829"></a><a name="p1278990845084829"></a>Host is down. </p>
</td>
</tr>
<tr id="row2123815615084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000042671084829"><a name="p1000042671084829"></a><a name="p1000042671084829"></a><a href="utils.md#ga53e186028fc992c3341ccb0d4d239b24">EHOSTUNREACH</a>   113</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p978926907084829"><a name="p978926907084829"></a><a name="p978926907084829"></a>Host is unreachable. </p>
</td>
</tr>
<tr id="row588519408084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197771966084829"><a name="p1197771966084829"></a><a name="p1197771966084829"></a><a href="utils.md#gaa4ccb54aa806de3e41a8515f06db85d4">EALREADY</a>   114</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904125748084829"><a name="p904125748084829"></a><a name="p904125748084829"></a>Operation already in process. </p>
</td>
</tr>
<tr id="row774739051084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267612954084829"><a name="p1267612954084829"></a><a name="p1267612954084829"></a><a href="utils.md#ga6c045d5be06e715cc335784a7320714e">EINPROGRESS</a>   115</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687998170084829"><a name="p1687998170084829"></a><a name="p1687998170084829"></a>Operation in progress. </p>
</td>
</tr>
<tr id="row1164666630084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356011134084829"><a name="p1356011134084829"></a><a name="p1356011134084829"></a><a href="utils.md#ga09e189d2214d9fe2847d27bf270ca1d7">ESTALE</a>   116</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1708067887084829"><a name="p1708067887084829"></a><a name="p1708067887084829"></a>Stale file handle. </p>
</td>
</tr>
<tr id="row1729846412084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727723742084829"><a name="p1727723742084829"></a><a name="p1727723742084829"></a><a href="utils.md#ga909dbec1577dd4de42e3de940449d991">EUCLEAN</a>   117</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1067180860084829"><a name="p1067180860084829"></a><a name="p1067180860084829"></a>Structure needs cleaning. </p>
</td>
</tr>
<tr id="row711840167084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977355409084829"><a name="p977355409084829"></a><a name="p977355409084829"></a><a href="utils.md#ga604c754d9cff19a3f842f263939744ed">ENOTNAM</a>   118</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445861667084829"><a name="p445861667084829"></a><a name="p445861667084829"></a>Not a XENIX named type file. </p>
</td>
</tr>
<tr id="row1571679070084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p906451355084829"><a name="p906451355084829"></a><a name="p906451355084829"></a><a href="utils.md#ga4df8882de9228023855dc31287c1728c">ENAVAIL</a>   119</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1527836045084829"><a name="p1527836045084829"></a><a name="p1527836045084829"></a>No XENIX semaphores available. </p>
</td>
</tr>
<tr id="row773741164084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241181700084829"><a name="p241181700084829"></a><a name="p241181700084829"></a><a href="utils.md#gab43dd11ce0541c2bc2bdbd36cbcbd6b7">EISNAM</a>   120</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p50534241084829"><a name="p50534241084829"></a><a name="p50534241084829"></a>Duplicate file name. </p>
</td>
</tr>
<tr id="row594550879084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1984522323084829"><a name="p1984522323084829"></a><a name="p1984522323084829"></a><a href="utils.md#gaa206a5818e8b3666cd46274d71ab7c45">EREMOTEIO</a>   121</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175975093084829"><a name="p175975093084829"></a><a name="p175975093084829"></a>Remote I/O error. </p>
</td>
</tr>
<tr id="row413343738084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589726841084829"><a name="p589726841084829"></a><a name="p589726841084829"></a><a href="utils.md#gaa5a48566b00cf9062d9deeeb0682cdaf">EDQUOT</a>   122</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288952536084829"><a name="p288952536084829"></a><a name="p288952536084829"></a>Quota exceeded. </p>
</td>
</tr>
<tr id="row198479675084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p212693305084829"><a name="p212693305084829"></a><a name="p212693305084829"></a><a href="utils.md#ga434a80cd2a94a829078d50b61ebd277d">ENOMEDIUM</a>   123</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p714391750084829"><a name="p714391750084829"></a><a name="p714391750084829"></a>No medium found. </p>
</td>
</tr>
<tr id="row921913319084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1653564081084829"><a name="p1653564081084829"></a><a name="p1653564081084829"></a><a href="utils.md#ga3431fd1c9d585b39b0089ebc0b97450f">EMEDIUMTYPE</a>   124</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1054707359084829"><a name="p1054707359084829"></a><a name="p1054707359084829"></a>Wrong medium type. </p>
</td>
</tr>
<tr id="row907643310084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p611610759084829"><a name="p611610759084829"></a><a name="p611610759084829"></a><a href="utils.md#ga9532d840ef91fd8e1ecc5d7ca7cbf212">ECANCELED</a>   125</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28337789084829"><a name="p28337789084829"></a><a name="p28337789084829"></a>Operation canceled. </p>
</td>
</tr>
<tr id="row1087072127084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1468976186084829"><a name="p1468976186084829"></a><a name="p1468976186084829"></a><a href="utils.md#ga21e1aad43086cf76131101b31ca391cc">ENOKEY</a>   126</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1814241093084829"><a name="p1814241093084829"></a><a name="p1814241093084829"></a>Required key not available. </p>
</td>
</tr>
<tr id="row1028486058084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408096002084829"><a name="p1408096002084829"></a><a name="p1408096002084829"></a><a href="utils.md#gac1eb981061f0b7e10a3460b48490e1e2">EKEYEXPIRED</a>   127</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1996880186084829"><a name="p1996880186084829"></a><a name="p1996880186084829"></a>Key has expired. </p>
</td>
</tr>
<tr id="row118418079084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636159187084829"><a name="p636159187084829"></a><a name="p636159187084829"></a><a href="utils.md#ga4dc832fdf410d2f441ce364a7f6d768a">EKEYREVOKED</a>   128</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p339465210084829"><a name="p339465210084829"></a><a name="p339465210084829"></a>Key has been revoked. </p>
</td>
</tr>
<tr id="row1724054302084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044563903084829"><a name="p1044563903084829"></a><a name="p1044563903084829"></a><a href="utils.md#gaddb68626b2a7ebc047c14180b51a5d95">EKEYREJECTED</a>   129</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669123211084829"><a name="p669123211084829"></a><a name="p669123211084829"></a>Key was rejected by service. </p>
</td>
</tr>
<tr id="row1495138946084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430993639084829"><a name="p430993639084829"></a><a name="p430993639084829"></a><a href="utils.md#gaf3f021d87caf24b44761036578c7beae">EOWNERDEAD</a>   130</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877969662084829"><a name="p1877969662084829"></a><a name="p1877969662084829"></a>Resource owner died. </p>
</td>
</tr>
<tr id="row989726172084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143266146084829"><a name="p143266146084829"></a><a name="p143266146084829"></a><a href="utils.md#gac69acb8e9e296867cc3f9fdf4223d05d">ENOTRECOVERABLE</a>   131</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1530109694084829"><a name="p1530109694084829"></a><a name="p1530109694084829"></a>State not recoverable. </p>
</td>
</tr>
<tr id="row1293604206084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541496967084829"><a name="p541496967084829"></a><a name="p541496967084829"></a><a href="utils.md#ga1ef2e2afa19fd790ef00003c23fc90dd">ERFKILL</a>   132</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313999625084829"><a name="p313999625084829"></a><a name="p313999625084829"></a>Operation not possible due to RF-kill. </p>
</td>
</tr>
<tr id="row953413052084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143535361084829"><a name="p143535361084829"></a><a name="p143535361084829"></a><a href="utils.md#ga7ac6735b364cb147c6ce8b887506a281">EHWPOISON</a>   133</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2080898256084829"><a name="p2080898256084829"></a><a name="p2080898256084829"></a>Hardware errors on the memory page. </p>
</td>
</tr>
</tbody>
</table>

