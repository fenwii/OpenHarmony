# ftw.h<a name="EN-US_TOPIC_0000001055228014"></a>

## **Overview**<a name="section1633037390084829"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Provides functions and structures related to file tree traversal. 

You can use the functions and structures to traverse files in a specified directory to obtain or process related information.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1140102331084829"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table205915463084829"></a>
<table><thead align="left"><tr id="row859320286084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2065168756084829"><a name="p2065168756084829"></a><a name="p2065168756084829"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2005097249084829"><a name="p2005097249084829"></a><a name="p2005097249084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1702033798084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1697960350084829"><a name="p1697960350084829"></a><a name="p1697960350084829"></a><a href="ftw.md">FTW</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507412410084829"><a name="p1507412410084829"></a><a name="p1507412410084829"></a>Defines the file tree walker (<a href="ftw.md">FTW</a>). </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1503176479084829"></a>
<table><thead align="left"><tr id="row957841966084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1826171208084829"><a name="p1826171208084829"></a><a name="p1826171208084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2007480888084829"><a name="p2007480888084829"></a><a name="p2007480888084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1221710111084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1523782865084829"><a name="p1523782865084829"></a><a name="p1523782865084829"></a><a href="fs.md#ga2feb73df4762e428e3967f8dfbbc8696">FTW_F</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437350438084829"><a name="p437350438084829"></a><a name="p437350438084829"></a>Regular file. </p>
</td>
</tr>
<tr id="row1873307386084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p229475682084829"><a name="p229475682084829"></a><a name="p229475682084829"></a><a href="fs.md#gabb7c3d2c39c0f3c8c5f0f1b9caa3499a">FTW_D</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1509411380084829"><a name="p1509411380084829"></a><a name="p1509411380084829"></a>Directory. </p>
</td>
</tr>
<tr id="row297441103084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1167166007084829"><a name="p1167166007084829"></a><a name="p1167166007084829"></a><a href="fs.md#gaf38dcdf86d19736b0aa55ac4defa666e">FTW_DNR</a>   3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926515421084829"><a name="p926515421084829"></a><a name="p926515421084829"></a>Unreadable directory. Its subdirectories will not be traversed. </p>
</td>
</tr>
<tr id="row530907551084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886576673084829"><a name="p1886576673084829"></a><a name="p1886576673084829"></a><a href="fs.md#ga17ff288701c7c6baf075795c9a1beb86">FTW_NS</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466832950084829"><a name="p1466832950084829"></a><a name="p1466832950084829"></a>The data of the <strong id="b282876840084829"><a name="b282876840084829"></a><a name="b282876840084829"></a>stat</strong> structure cannot be obtained. The possible cause is that the permission is incorrect. </p>
</td>
</tr>
<tr id="row715041896084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p595945727084829"><a name="p595945727084829"></a><a name="p595945727084829"></a><a href="fs.md#gaeee6cd556fb6bfaf7237772e698fa48d">FTW_SL</a>   5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1316407204084829"><a name="p1316407204084829"></a><a name="p1316407204084829"></a>Symbolic link. </p>
</td>
</tr>
<tr id="row1540660525084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813833385084829"><a name="p813833385084829"></a><a name="p813833385084829"></a><a href="fs.md#ga8b34563aa640cd03e2ddf054b0b99e49">FTW_DP</a>   6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row1260914555084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1473513553084829"><a name="p1473513553084829"></a><a name="p1473513553084829"></a><a href="fs.md#gaf0e95fe567ba665873d18284d67e0f80">FTW_SLN</a>   7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630071792084829"><a name="p630071792084829"></a><a name="p630071792084829"></a>Symbolic link that names a non-existent file. </p>
</td>
</tr>
<tr id="row1287036237084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564473688084829"><a name="p564473688084829"></a><a name="p564473688084829"></a><a href="fs.md#ga8c98a3c79a82339a189b11094032a09a">FTW_PHYS</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216855169084829"><a name="p216855169084829"></a><a name="p216855169084829"></a>Symbolic links that are not traversed. If not set, symbolic links are traversed by default. </p>
</td>
</tr>
<tr id="row1004616180084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1824723265084829"><a name="p1824723265084829"></a><a name="p1824723265084829"></a><a href="fs.md#ga7bbaf43efae1f2d3c8092d99a340729d">FTW_MOUNT</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p179944666084829"><a name="p179944666084829"></a><a name="p179944666084829"></a>Stay within the same file system. </p>
</td>
</tr>
<tr id="row1662804045084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382551967084829"><a name="p382551967084829"></a><a name="p382551967084829"></a><a href="fs.md#gad8a9cc4cf048af5fab2c5f65ed9cb0db">FTW_CHDIR</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p164483984084829"><a name="p164483984084829"></a><a name="p164483984084829"></a><a href="utils.md#ga03af571dfb595681bfa203c83385c07b">chdir</a> is called to go to the directory before reading the directory. </p>
</td>
</tr>
<tr id="row520614725084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476262814084829"><a name="p476262814084829"></a><a name="p476262814084829"></a><a href="fs.md#gaf9008c0040247fbea883ec24b10cf884">FTW_DEPTH</a>   8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803704290084829"><a name="p1803704290084829"></a><a name="p1803704290084829"></a>All subdirectories will be traversed before the directory itself. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1214780631084829"></a>
<table><thead align="left"><tr id="row1253682778084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1462592559084829"><a name="p1462592559084829"></a><a name="p1462592559084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1832690537084829"><a name="p1832690537084829"></a><a name="p1832690537084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row861657500084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255535520084829"><a name="p255535520084829"></a><a name="p255535520084829"></a><a href="fs.md#ga8dda75835c2b90f305d96e908dc0f84d">ftw</a> (const char *path, int(*fn)(const char *file, const struct <a href="stat.md">stat</a> *sb, int flag), int depth)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938670848084829"><a name="p938670848084829"></a><a name="p938670848084829"></a>int </p>
<p id="p1060486832084829"><a name="p1060486832084829"></a><a name="p1060486832084829"></a>Traverses a file tree. </p>
</td>
</tr>
<tr id="row481783190084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703968128084829"><a name="p703968128084829"></a><a name="p703968128084829"></a><a href="fs.md#ga3fb6324259c86bfee53d3354798cfd43">nftw</a> (const char *path, int(*fn)(const char *file, const struct <a href="stat.md">stat</a> *sb, int flag, struct <a href="ftw.md">FTW</a> *s), int fd_limit, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703321351084829"><a name="p1703321351084829"></a><a name="p1703321351084829"></a>int </p>
<p id="p451060571084829"><a name="p451060571084829"></a><a name="p451060571084829"></a>Traverses a file tree. </p>
</td>
</tr>
</tbody>
</table>

