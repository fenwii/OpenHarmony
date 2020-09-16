# unistd.h<a name="EN-US_TOPIC_0000001055387990"></a>

## **Overview**<a name="section562192921084834"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Provides functions and data structures related to process operations. 

For example, you can use the functions to create and copy a process, and obtain a process ID.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1905590375084834"></a>

## Macros<a name="define-members"></a>

<a name="table1909329087084834"></a>
<table><thead align="left"><tr id="row851946096084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p225818659084834"><a name="p225818659084834"></a><a name="p225818659084834"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2024632426084834"><a name="p2024632426084834"></a><a name="p2024632426084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row174287283084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p178981097084834"><a name="p178981097084834"></a><a name="p178981097084834"></a><a href="utils.md#gafcf80a6d91178952d107ad00b165752b">STDIN_FILENO</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550053182084834"><a name="p1550053182084834"></a><a name="p1550053182084834"></a>Descriptor ID of the standard input file. </p>
</td>
</tr>
<tr id="row1000229252084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p60427303084834"><a name="p60427303084834"></a><a name="p60427303084834"></a><a href="utils.md#gabd165ee6474b5b75bf075842fff13a04">STDOUT_FILENO</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2060156012084834"><a name="p2060156012084834"></a><a name="p2060156012084834"></a>Descriptor ID of the standard output file. </p>
</td>
</tr>
<tr id="row995032692084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p792361888084834"><a name="p792361888084834"></a><a name="p792361888084834"></a><a href="utils.md#gae2fe1725bb5e9823d089c46b9ed5266e">STDERR_FILENO</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1228395244084834"><a name="p1228395244084834"></a><a name="p1228395244084834"></a>Descriptor ID of the standard error file. </p>
</td>
</tr>
<tr id="row1686801170084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1409906227084834"><a name="p1409906227084834"></a><a name="p1409906227084834"></a><a href="utils.md#ga0d112bae8fd35be772185b6ec6bcbe64">SEEK_SET</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323398507084834"><a name="p323398507084834"></a><a name="p323398507084834"></a>Relocation starts from the file header. </p>
</td>
</tr>
<tr id="row864416193084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1909810054084834"><a name="p1909810054084834"></a><a name="p1909810054084834"></a><a href="utils.md#ga4c8d0b76b470ba65a43ca46a88320f39">SEEK_CUR</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453409657084834"><a name="p453409657084834"></a><a name="p453409657084834"></a>Relocation starts from the position of the currently accessed file. </p>
</td>
</tr>
<tr id="row774009896084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p615843280084834"><a name="p615843280084834"></a><a name="p615843280084834"></a><a href="utils.md#gad2a2e6c114780c3071efd24f16c7f7d8">SEEK_END</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266120383084834"><a name="p1266120383084834"></a><a name="p1266120383084834"></a>Relocation starts from the end of the file. </p>
</td>
</tr>
<tr id="row463184952084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1539517649084834"><a name="p1539517649084834"></a><a name="p1539517649084834"></a><a href="utils.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4">NULL</a>   ((void*)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650282333084834"><a name="p1650282333084834"></a><a name="p1650282333084834"></a>NULL. </p>
</td>
</tr>
<tr id="row687200675084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797243445084834"><a name="p1797243445084834"></a><a name="p1797243445084834"></a><a href="utils.md#gaf837744613408b57dc3654fbc3bcf900">F_OK</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p413608116084834"><a name="p413608116084834"></a><a name="p413608116084834"></a>Existing file. </p>
</td>
</tr>
<tr id="row1606854275084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911273321084834"><a name="p1911273321084834"></a><a name="p1911273321084834"></a><a href="utils.md#ga24a7a0ceb1e8f5f44cb1038bb829030d">R_OK</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1878112613084834"><a name="p1878112613084834"></a><a name="p1878112613084834"></a>Readable file. </p>
</td>
</tr>
<tr id="row1606797089084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p358338231084834"><a name="p358338231084834"></a><a name="p358338231084834"></a><a href="utils.md#gae5acf4043c0903cda7436b108e29e8e6">W_OK</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510126257084834"><a name="p510126257084834"></a><a name="p510126257084834"></a>Writable file. </p>
</td>
</tr>
<tr id="row1729803653084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603262787084834"><a name="p603262787084834"></a><a name="p603262787084834"></a><a href="utils.md#ga5e995ef7690698b62bf016b14fbc45ca">X_OK</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225796770084834"><a name="p225796770084834"></a><a name="p225796770084834"></a>Executable file. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1473445525084834"></a>
<table><thead align="left"><tr id="row2147379310084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p522824874084834"><a name="p522824874084834"></a><a name="p522824874084834"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1155659952084834"><a name="p1155659952084834"></a><a name="p1155659952084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row389629249084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p818347022084834"><a name="p818347022084834"></a><a name="p818347022084834"></a><a href="utils.md#ga3d8839f39526d15b100953d64cc08f10">pipe</a> (int pipefd[2])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p13335460084834"><a name="p13335460084834"></a><a name="p13335460084834"></a>int </p>
<p id="p1673776751084834"><a name="p1673776751084834"></a><a name="p1673776751084834"></a>Creates an anonymous pipe. </p>
</td>
</tr>
<tr id="row802835352084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1604516914084834"><a name="p1604516914084834"></a><a name="p1604516914084834"></a><a href="utils.md#gaafbcde67669a1b96577e735ddebd8634">close</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418151940084834"><a name="p418151940084834"></a><a name="p418151940084834"></a>int </p>
<p id="p2130814245084834"><a name="p2130814245084834"></a><a name="p2130814245084834"></a>Closes a file with a specified file descriptor. </p>
</td>
</tr>
<tr id="row873996217084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2123165821084834"><a name="p2123165821084834"></a><a name="p2123165821084834"></a><a href="utils.md#ga2599c985f9cce0d9d7b11732941bd9dc">dup</a> (int oldfd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1729532540084834"><a name="p1729532540084834"></a><a name="p1729532540084834"></a>int </p>
<p id="p197952391084834"><a name="p197952391084834"></a><a name="p197952391084834"></a>Copies a specified file descriptor. </p>
</td>
</tr>
<tr id="row525095557084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830901558084834"><a name="p1830901558084834"></a><a name="p1830901558084834"></a><a href="utils.md#ga0bbddf8ae4f3dea6e57532be36c04268">dup2</a> (int oldfd, int newfd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077512500084834"><a name="p2077512500084834"></a><a name="p2077512500084834"></a>int </p>
<p id="p1947768814084834"><a name="p1947768814084834"></a><a name="p1947768814084834"></a>Copies the descriptor of the target file to a specified descriptor. </p>
</td>
</tr>
<tr id="row150118259084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132443229084834"><a name="p2132443229084834"></a><a name="p2132443229084834"></a><a href="utils.md#ga8bd74caed008a66808d92d57fa74d9f6">lseek</a> (int fd, off_t offset, int whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p346855367084834"><a name="p346855367084834"></a><a name="p346855367084834"></a>off_t </p>
<p id="p1013726100084834"><a name="p1013726100084834"></a><a name="p1013726100084834"></a>Sets the offset of the pointer to the file. </p>
</td>
</tr>
<tr id="row2097692982084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1229484693084834"><a name="p1229484693084834"></a><a name="p1229484693084834"></a><a href="utils.md#ga9ba34c4ff72e21db486eedf77c2a18d0">fsync</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p936983755084834"><a name="p936983755084834"></a><a name="p936983755084834"></a>int </p>
<p id="p388180296084834"><a name="p388180296084834"></a><a name="p388180296084834"></a>Synchronizes a file associated with a specified file descriptor to the storage device. </p>
</td>
</tr>
<tr id="row349370026084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806699979084834"><a name="p806699979084834"></a><a name="p806699979084834"></a><a href="utils.md#ga5975018bea8d2811c4b3abe10d493bb6">read</a> (int fd, void *buf, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791925326084834"><a name="p791925326084834"></a><a name="p791925326084834"></a>ssize_t </p>
<p id="p2053628843084834"><a name="p2053628843084834"></a><a name="p2053628843084834"></a>Reads the file contents and saves them in a specified buffer location. </p>
</td>
</tr>
<tr id="row1946864316084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1549275390084834"><a name="p1549275390084834"></a><a name="p1549275390084834"></a><a href="utils.md#gac06af22e9ce132f563db5c918ceb1eb1">write</a> (int fd, const void *buf, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1810850528084834"><a name="p1810850528084834"></a><a name="p1810850528084834"></a>ssize_t </p>
<p id="p2035959259084834"><a name="p2035959259084834"></a><a name="p2035959259084834"></a>Writes the specified content to the file. </p>
</td>
</tr>
<tr id="row184417509084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p925206649084834"><a name="p925206649084834"></a><a name="p925206649084834"></a><a href="utils.md#ga67ceebb141dbf6be0be4484804601e5b">pread</a> (int fd, void *buf, size_t count, off_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914470733084834"><a name="p1914470733084834"></a><a name="p1914470733084834"></a>ssize_t </p>
<p id="p972976740084834"><a name="p972976740084834"></a><a name="p972976740084834"></a>Reads data whose offset is <strong id="b1217130691084834"><a name="b1217130691084834"></a><a name="b1217130691084834"></a>offset</strong> and length is <strong id="b1729624265084834"><a name="b1729624265084834"></a><a name="b1729624265084834"></a>count</strong> from <strong id="b51112957084834"><a name="b51112957084834"></a><a name="b51112957084834"></a>fd</strong> to the buffer. </p>
</td>
</tr>
<tr id="row929242969084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p619820129084834"><a name="p619820129084834"></a><a name="p619820129084834"></a><a href="utils.md#ga6583cb37d551c2553bbb5e7df6c145be">pwrite</a> (int fd, const void *buf, size_t count, off_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2046890001084834"><a name="p2046890001084834"></a><a name="p2046890001084834"></a>ssize_t </p>
<p id="p194171527084834"><a name="p194171527084834"></a><a name="p194171527084834"></a>Writes data from the buffer to <strong id="b827679310084834"><a name="b827679310084834"></a><a name="b827679310084834"></a>fd</strong> whose offset is <strong id="b159351417084834"><a name="b159351417084834"></a><a name="b159351417084834"></a>offset</strong> and length is <strong id="b1375496553084834"><a name="b1375496553084834"></a><a name="b1375496553084834"></a>count</strong>. </p>
</td>
</tr>
<tr id="row1970791786084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1236420202084834"><a name="p1236420202084834"></a><a name="p1236420202084834"></a><a href="utils.md#ga28af9471bbdf262321af663e02899a47">unlink</a> (const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650464720084834"><a name="p650464720084834"></a><a name="p650464720084834"></a>int </p>
<p id="p572782085084834"><a name="p572782085084834"></a><a name="p572782085084834"></a>Deletes a specified file. </p>
</td>
</tr>
<tr id="row1168664954084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835215893084834"><a name="p835215893084834"></a><a name="p835215893084834"></a><a href="utils.md#gaa06a637e291f5d288cae85ce32a2fe49">unlinkat</a> (int fd, const char *path, int flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849406182084834"><a name="p1849406182084834"></a><a name="p1849406182084834"></a>int </p>
<p id="p515060052084834"><a name="p515060052084834"></a><a name="p515060052084834"></a>Deletes a specified file. </p>
</td>
</tr>
<tr id="row1955066902084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079451654084834"><a name="p2079451654084834"></a><a name="p2079451654084834"></a><a href="utils.md#gab2df76f2c62ae012c2e417813b5fe8ce">rmdir</a> (const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1486412437084834"><a name="p1486412437084834"></a><a name="p1486412437084834"></a>int </p>
<p id="p1205014173084834"><a name="p1205014173084834"></a><a name="p1205014173084834"></a>Deletes a directory. </p>
</td>
</tr>
<tr id="row712223601084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p177090626084834"><a name="p177090626084834"></a><a name="p177090626084834"></a><a href="utils.md#ga87674838dd2bcf61e1a1fb5c9892ab6c">truncate</a> (const char *path, off_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1454510178084834"><a name="p1454510178084834"></a><a name="p1454510178084834"></a>int </p>
<p id="p1404361465084834"><a name="p1404361465084834"></a><a name="p1404361465084834"></a>Truncates a file to a specified size based on the file path. </p>
</td>
</tr>
<tr id="row1397823512084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1815816955084834"><a name="p1815816955084834"></a><a name="p1815816955084834"></a><a href="utils.md#ga0fb7c60877eacbfbd66eff04533ab0fe">ftruncate</a> (int fd, off_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635129362084834"><a name="p635129362084834"></a><a name="p635129362084834"></a>int </p>
<p id="p717137154084834"><a name="p717137154084834"></a><a name="p717137154084834"></a>Truncates a file to a specified length. </p>
</td>
</tr>
<tr id="row1523246776084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752059247084834"><a name="p752059247084834"></a><a name="p752059247084834"></a><a href="utils.md#gaeff22ad09b35eda92f6c5632300b05da">access</a> (const char *path, int mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p191029783084834"><a name="p191029783084834"></a><a name="p191029783084834"></a>int </p>
<p id="p1711218740084834"><a name="p1711218740084834"></a><a name="p1711218740084834"></a>Checks whether a file has the corresponding permission. </p>
</td>
</tr>
<tr id="row278175799084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p942823745084834"><a name="p942823745084834"></a><a name="p942823745084834"></a><a href="utils.md#ga03af571dfb595681bfa203c83385c07b">chdir</a> (const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1154658487084834"><a name="p1154658487084834"></a><a name="p1154658487084834"></a>int </p>
<p id="p364502287084834"><a name="p364502287084834"></a><a name="p364502287084834"></a>Switches the current working directory to a specified directory. </p>
</td>
</tr>
<tr id="row92830382084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854277960084834"><a name="p1854277960084834"></a><a name="p1854277960084834"></a><a href="utils.md#ga3284211bd28346254245c9d4fd071d7f">getcwd</a> (char *buf, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1140937829084834"><a name="p1140937829084834"></a><a name="p1140937829084834"></a>char * </p>
<p id="p861050677084834"><a name="p861050677084834"></a><a name="p861050677084834"></a>Obtains the current working directory. </p>
</td>
</tr>
<tr id="row426675411084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221310393084834"><a name="p1221310393084834"></a><a name="p1221310393084834"></a><a href="utils.md#ga8c476685d78ea93ee343f8a0580c79fe">alarm</a> (unsigned int seconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139637329084834"><a name="p1139637329084834"></a><a name="p1139637329084834"></a>unsigned int </p>
<p id="p527285143084834"><a name="p527285143084834"></a><a name="p527285143084834"></a>Arranges a signal to be sent to the current process after the number of seconds specified by <strong id="b1100103874084834"><a name="b1100103874084834"></a><a name="b1100103874084834"></a>seconds</strong>. </p>
</td>
</tr>
<tr id="row459637068084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1231418677084834"><a name="p1231418677084834"></a><a name="p1231418677084834"></a><a href="utils.md#gad4669b3813c3b4a616a738317fdc974f">sleep</a> (unsigned seconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p905740652084834"><a name="p905740652084834"></a><a name="p905740652084834"></a>unsigned </p>
<p id="p18764255084834"><a name="p18764255084834"></a><a name="p18764255084834"></a>Sleeps for a period of time. </p>
</td>
</tr>
<tr id="row1007600221084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p449195731084834"><a name="p449195731084834"></a><a name="p449195731084834"></a><a href="utils.md#ga47a6ff5872f457ee230458137f2b2409">pause</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363530095084834"><a name="p1363530095084834"></a><a name="p1363530095084834"></a>int </p>
<p id="p391166424084834"><a name="p391166424084834"></a><a name="p391166424084834"></a>Waits for signal. </p>
</td>
</tr>
<tr id="row1712064096084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2074192026084834"><a name="p2074192026084834"></a><a name="p2074192026084834"></a><a href="utils.md#gaa4e4714e6e8927c80b2553a40094b6d9">fork</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611210081084834"><a name="p611210081084834"></a><a name="p611210081084834"></a>pid_t </p>
<p id="p1473356589084834"><a name="p1473356589084834"></a><a name="p1473356589084834"></a>Creates a new process that inherits from the user-mode data of its parent process. </p>
</td>
</tr>
<tr id="row165929750084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p884501675084834"><a name="p884501675084834"></a><a name="p884501675084834"></a><a href="utils.md#ga99ca2b673a47850c541b215ddfd6b23e">execve</a> (const char *path, char *const arg[], char *const envp[])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323985088084834"><a name="p1323985088084834"></a><a name="p1323985088084834"></a>int </p>
<p id="p1861105911084834"><a name="p1861105911084834"></a><a name="p1861105911084834"></a>Executes a specified user program file in ELF format. </p>
</td>
</tr>
<tr id="row662430955084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p747610160084834"><a name="p747610160084834"></a><a name="p747610160084834"></a><a href="utils.md#gadb609bbc5b9255bf715138cda88857b0">execv</a> (const char *path, char *const arg[])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1664409735084834"><a name="p1664409735084834"></a><a name="p1664409735084834"></a>int </p>
<p id="p1122502773084834"><a name="p1122502773084834"></a><a name="p1122502773084834"></a>Executes a specified user program file in ELF format. </p>
</td>
</tr>
<tr id="row576432429084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719081068084834"><a name="p719081068084834"></a><a name="p719081068084834"></a><a href="utils.md#ga2c2701379e4144b3105aa83c82363aa3">execle</a> (const char *path, const char *arg,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p582649300084834"><a name="p582649300084834"></a><a name="p582649300084834"></a>int </p>
<p id="p886173493084834"><a name="p886173493084834"></a><a name="p886173493084834"></a>Executes a specified user program file in ELF format. </p>
</td>
</tr>
<tr id="row278907643084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197618978084834"><a name="p1197618978084834"></a><a name="p1197618978084834"></a><a href="utils.md#ga1ade18bb3b763fbcefc507c770dc7e7e">execl</a> (const char *path, const char *arg,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p799525763084834"><a name="p799525763084834"></a><a name="p799525763084834"></a>int </p>
<p id="p912303928084834"><a name="p912303928084834"></a><a name="p912303928084834"></a>Executes a specified user program file in ELF format. </p>
</td>
</tr>
<tr id="row1882266430084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1353473215084834"><a name="p1353473215084834"></a><a name="p1353473215084834"></a><a href="utils.md#ga1bbb0ecd56c097ca82587115b4dfd540">execvp</a> (const char *path, char *const arg[])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p835263893084834"><a name="p835263893084834"></a><a name="p835263893084834"></a>int </p>
<p id="p1964676036084834"><a name="p1964676036084834"></a><a name="p1964676036084834"></a>Executes a specified user program file in ELF format. </p>
</td>
</tr>
<tr id="row515948779084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649550562084834"><a name="p649550562084834"></a><a name="p649550562084834"></a><a href="utils.md#ga4dd268acb7fc54f403ab6cb56b7ffd3f">execlp</a> (const char *path, const char *arg,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1776872146084834"><a name="p1776872146084834"></a><a name="p1776872146084834"></a>int </p>
<p id="p346453432084834"><a name="p346453432084834"></a><a name="p346453432084834"></a>Executes a specified user program file in ELF format. </p>
</td>
</tr>
<tr id="row34586514084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393539828084834"><a name="p1393539828084834"></a><a name="p1393539828084834"></a><a href="utils.md#gaee2ffcdf92b92a337c592a7ef9174769">_exit</a> (int status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773165151084834"><a name="p773165151084834"></a><a name="p773165151084834"></a>_Noreturn void </p>
<p id="p644492220084834"><a name="p644492220084834"></a><a name="p644492220084834"></a>Exits the process immediately and closes all opened file descriptors in the process. </p>
</td>
</tr>
<tr id="row979081321084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1831589418084834"><a name="p1831589418084834"></a><a name="p1831589418084834"></a><a href="utils.md#ga27ee6e902becdb181addb45b69a50b8c">swab</a> (const void *from, void *to, ssize_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1955270857084834"><a name="p1955270857084834"></a><a name="p1955270857084834"></a>void </p>
<p id="p926511587084834"><a name="p926511587084834"></a><a name="p926511587084834"></a>Swaps bytes. </p>
</td>
</tr>
<tr id="row1938287441084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p986483360084834"><a name="p986483360084834"></a><a name="p986483360084834"></a><a href="utils.md#gac61b207337ca21b3b309593fd1a0cb82">getpid</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720181474084834"><a name="p720181474084834"></a><a name="p720181474084834"></a>pid_t </p>
<p id="p827606730084834"><a name="p827606730084834"></a><a name="p827606730084834"></a>Obtains the process ID. </p>
</td>
</tr>
<tr id="row1395332433084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671705761084834"><a name="p671705761084834"></a><a name="p671705761084834"></a><a href="utils.md#gac6d7f7ade00dcdc302b0da5664eee812">getppid</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1656972383084834"><a name="p1656972383084834"></a><a name="p1656972383084834"></a>pid_t </p>
<p id="p1087196532084834"><a name="p1087196532084834"></a><a name="p1087196532084834"></a>Obtains the parent process ID. </p>
</td>
</tr>
<tr id="row194809949084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981337075084834"><a name="p1981337075084834"></a><a name="p1981337075084834"></a><a href="utils.md#ga06f4ba65249f92cacdba5782a8d70eba">getpgrp</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427492706084834"><a name="p427492706084834"></a><a name="p427492706084834"></a>pid_t </p>
<p id="p2086946759084834"><a name="p2086946759084834"></a><a name="p2086946759084834"></a>Obtains the ID of the process group of the calling process. </p>
</td>
</tr>
<tr id="row672878615084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p947794645084834"><a name="p947794645084834"></a><a name="p947794645084834"></a><a href="utils.md#ga48f523c98970793dfc2c5a05f6832006">getpgid</a> (pid_t pid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925910997084834"><a name="p1925910997084834"></a><a name="p1925910997084834"></a>pid_t </p>
<p id="p1307804896084834"><a name="p1307804896084834"></a><a name="p1307804896084834"></a>Obtains the ID of the process group whose process ID is specified by <strong id="b1564726504084834"><a name="b1564726504084834"></a><a name="b1564726504084834"></a>pid</strong>. </p>
</td>
</tr>
<tr id="row1783403233084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p130992298084834"><a name="p130992298084834"></a><a name="p130992298084834"></a><a href="utils.md#gae5aae5b0275eefe79314a4673195e475">setpgid</a> (pid_t pid, pid_t pgid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449285387084834"><a name="p1449285387084834"></a><a name="p1449285387084834"></a>int </p>
<p id="p1054988379084834"><a name="p1054988379084834"></a><a name="p1054988379084834"></a>Sets the ID of the process group whose process ID is specified by <strong id="b447307549084834"><a name="b447307549084834"></a><a name="b447307549084834"></a>pid</strong>. </p>
</td>
</tr>
<tr id="row1305437252084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1046699804084834"><a name="p1046699804084834"></a><a name="p1046699804084834"></a><a href="utils.md#ga5ffa4c677fc71cecd94f140ef9db624c">getopt</a> (int argc, char *const argv[], const char *optstring)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890404978084834"><a name="p1890404978084834"></a><a name="p1890404978084834"></a>int </p>
<p id="p1961700221084834"><a name="p1961700221084834"></a><a name="p1961700221084834"></a>Parses command-line arguments based on the specified option. </p>
</td>
</tr>
<tr id="row1668026006084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2140928370084834"><a name="p2140928370084834"></a><a name="p2140928370084834"></a><a href="utils.md#ga2f517436c22ef73337d3de4920908c6c">getuid</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563965975084834"><a name="p1563965975084834"></a><a name="p1563965975084834"></a>uid_t </p>
<p id="p754532044084834"><a name="p754532044084834"></a><a name="p754532044084834"></a>Obtains the real user ID (UID) of the calling process. </p>
</td>
</tr>
<tr id="row1640378372084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p324321379084834"><a name="p324321379084834"></a><a name="p324321379084834"></a><a href="utils.md#ga8b9a6dcf4e1d237f5607256dad93e26a">geteuid</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1651389236084834"><a name="p1651389236084834"></a><a name="p1651389236084834"></a>uid_t </p>
<p id="p1273924822084834"><a name="p1273924822084834"></a><a name="p1273924822084834"></a>Obtains the effective user ID (UID) of the calling process. </p>
</td>
</tr>
<tr id="row1272806512084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1170489230084834"><a name="p1170489230084834"></a><a name="p1170489230084834"></a><a href="utils.md#ga58ca281cc6931c62e6a85e2edb5b4b49">getgid</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1050966912084834"><a name="p1050966912084834"></a><a name="p1050966912084834"></a>gid_t </p>
<p id="p2081431222084834"><a name="p2081431222084834"></a><a name="p2081431222084834"></a>Obtains the real group ID (GID) of the calling process. </p>
</td>
</tr>
<tr id="row991949048084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p59363385084834"><a name="p59363385084834"></a><a name="p59363385084834"></a><a href="utils.md#ga3e7c694d68b4e62c1f275612d30b6d9d">getegid</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308162334084834"><a name="p308162334084834"></a><a name="p308162334084834"></a>gid_t </p>
<p id="p82129110084834"><a name="p82129110084834"></a><a name="p82129110084834"></a>Obtains the effective group ID (GID) of the calling process. </p>
</td>
</tr>
<tr id="row654864721084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p653215322084834"><a name="p653215322084834"></a><a name="p653215322084834"></a><a href="utils.md#gaacfa67f2aef6be4baceace6a00856d21">getgroups</a> (int size, gid_t list[])</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1745179923084834"><a name="p1745179923084834"></a><a name="p1745179923084834"></a>int </p>
<p id="p1241443648084834"><a name="p1241443648084834"></a><a name="p1241443648084834"></a>Obtains a list of supplementary user group IDs specific to the calling process. </p>
</td>
</tr>
<tr id="row1929445963084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1928877217084834"><a name="p1928877217084834"></a><a name="p1928877217084834"></a><a href="utils.md#gaa426fc963bb0a4f469eef61d9f0c4a26">setuid</a> (uid_t uid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p465103275084834"><a name="p465103275084834"></a><a name="p465103275084834"></a>int </p>
<p id="p424311328084834"><a name="p424311328084834"></a><a name="p424311328084834"></a>Sets the real user ID for the calling process. </p>
</td>
</tr>
<tr id="row468959733084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2070931567084834"><a name="p2070931567084834"></a><a name="p2070931567084834"></a><a href="utils.md#ga1f3f88da554f543f01a02a06c79c7bdd">seteuid</a> (uid_t euid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856467444084834"><a name="p856467444084834"></a><a name="p856467444084834"></a>int </p>
<p id="p1213531023084834"><a name="p1213531023084834"></a><a name="p1213531023084834"></a>Sets the effective user ID of the calling process. </p>
</td>
</tr>
<tr id="row1990960366084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p393395268084834"><a name="p393395268084834"></a><a name="p393395268084834"></a><a href="utils.md#ga3116233500c2c34795d437eaf34b69b5">setgid</a> (gid_t gid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164442867084834"><a name="p1164442867084834"></a><a name="p1164442867084834"></a>int </p>
<p id="p2119077946084834"><a name="p2119077946084834"></a><a name="p2119077946084834"></a>Sets the user group ID of the calling process. </p>
</td>
</tr>
<tr id="row954516247084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p941615169084834"><a name="p941615169084834"></a><a name="p941615169084834"></a><a href="utils.md#ga201d5dad2108506c5db5ba8d126ffbb2">setegid</a> (gid_t egid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1499937019084834"><a name="p1499937019084834"></a><a name="p1499937019084834"></a>int </p>
<p id="p966923082084834"><a name="p966923082084834"></a><a name="p966923082084834"></a>Sets the effective user group ID of the calling process. </p>
</td>
</tr>
<tr id="row1267546926084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1030601685084834"><a name="p1030601685084834"></a><a name="p1030601685084834"></a><a href="utils.md#gaa4ea4bbebf4841965159e66b5d1a49e8">pathconf</a> (const char *path, int name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p336150069084834"><a name="p336150069084834"></a><a name="p336150069084834"></a>long </p>
<p id="p58545449084834"><a name="p58545449084834"></a><a name="p58545449084834"></a>Obtains the configuration value of a file. </p>
</td>
</tr>
<tr id="row2136576068084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p866980823084834"><a name="p866980823084834"></a><a name="p866980823084834"></a><a href="utils.md#ga0c1be1c8a11bac9cdf41613e996c841b">setreuid</a> (uid_t ruid, uid_t euid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1015701222084834"><a name="p1015701222084834"></a><a name="p1015701222084834"></a>int </p>
<p id="p1853605976084834"><a name="p1853605976084834"></a><a name="p1853605976084834"></a>Sets the real and effective user IDs of the calling process. </p>
</td>
</tr>
<tr id="row1133499160084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1249185953084834"><a name="p1249185953084834"></a><a name="p1249185953084834"></a><a href="utils.md#ga869d651a498782b6f3625e2bdbc439d6">setregid</a> (gid_t rgid, gid_t egid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p469543756084834"><a name="p469543756084834"></a><a name="p469543756084834"></a>int </p>
<p id="p316988591084834"><a name="p316988591084834"></a><a name="p316988591084834"></a>Sets the real and effective user group IDs of the calling process. </p>
</td>
</tr>
<tr id="row588945413084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51490953084834"><a name="p51490953084834"></a><a name="p51490953084834"></a><a href="utils.md#gada2b1e6782cd8fc506fde243f7d313ec">setpgrp</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p796786658084834"><a name="p796786658084834"></a><a name="p796786658084834"></a>pid_t </p>
<p id="p2027581064084834"><a name="p2027581064084834"></a><a name="p2027581064084834"></a>Sets the process group ID of the calling process. </p>
</td>
</tr>
<tr id="row781518847084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1667100226084834"><a name="p1667100226084834"></a><a name="p1667100226084834"></a><a href="utils.md#ga608e849b00b0ac57524b26f45d408a55">usleep</a> (unsigned useconds)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876443286084834"><a name="p876443286084834"></a><a name="p876443286084834"></a>int </p>
<p id="p1489651508084834"><a name="p1489651508084834"></a><a name="p1489651508084834"></a>Sleeps for several microseconds. </p>
</td>
</tr>
<tr id="row503485460084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1575721327084834"><a name="p1575721327084834"></a><a name="p1575721327084834"></a><a href="utils.md#ga9d35348d3389a721ab5aef5f4f036c61">ualarm</a> (unsigned value, unsigned interval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462982368084834"><a name="p1462982368084834"></a><a name="p1462982368084834"></a>unsigned </p>
<p id="p1309443154084834"><a name="p1309443154084834"></a><a name="p1309443154084834"></a>Sets a microsecond-level timer. </p>
</td>
</tr>
<tr id="row2127865082084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p138255272084834"><a name="p138255272084834"></a><a name="p138255272084834"></a><a href="utils.md#gaf7df624933ff8690b60c537a29659718">setgroups</a> (size_t size, const gid_t *list)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p482056978084834"><a name="p482056978084834"></a><a name="p482056978084834"></a>int </p>
<p id="p741719373084834"><a name="p741719373084834"></a><a name="p741719373084834"></a>Sets the supplementary user group list of the calling process. </p>
</td>
</tr>
<tr id="row447268630084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p742555273084834"><a name="p742555273084834"></a><a name="p742555273084834"></a><a href="utils.md#gac3827ffb6833b1e282fc2ea856d534a1">setresuid</a> (uid_t ruid, uid_t euid, uid_t suid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1231396795084834"><a name="p1231396795084834"></a><a name="p1231396795084834"></a>int </p>
<p id="p2029709652084834"><a name="p2029709652084834"></a><a name="p2029709652084834"></a>Sets the real, effective, and saved user IDs of the calling process. </p>
</td>
</tr>
<tr id="row732608192084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p859939013084834"><a name="p859939013084834"></a><a name="p859939013084834"></a><a href="utils.md#gabb0ec1f467235bee75ee359400d817e4">setresgid</a> (gid_t rgid, gid_t egid, gid_t sgid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p195706711084834"><a name="p195706711084834"></a><a name="p195706711084834"></a>int </p>
<p id="p1937522962084834"><a name="p1937522962084834"></a><a name="p1937522962084834"></a>Sets the real, effective, and saved group IDs of the calling process. </p>
</td>
</tr>
<tr id="row699293416084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p860457533084834"><a name="p860457533084834"></a><a name="p860457533084834"></a><a href="utils.md#ga4e92f1f4fb48c6fa8cd15d328950bc68">getresuid</a> (uid_t *ruid, uid_t *euid, uid_t *suid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688202464084834"><a name="p1688202464084834"></a><a name="p1688202464084834"></a>int </p>
<p id="p936879942084834"><a name="p936879942084834"></a><a name="p936879942084834"></a>Obtains the real, effective, and saved user IDs of the calling process. </p>
</td>
</tr>
<tr id="row355016223084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1853630820084834"><a name="p1853630820084834"></a><a name="p1853630820084834"></a><a href="utils.md#gaf74b37e12b6a9418c094479721e8cbf0">getresgid</a> (gid_t *rgid, gid_t *egid, gid_t *sgid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1530572209084834"><a name="p1530572209084834"></a><a name="p1530572209084834"></a>int </p>
<p id="p29295965084834"><a name="p29295965084834"></a><a name="p29295965084834"></a>Obtains the real, effective, and saved user group IDs of the calling process. </p>
</td>
</tr>
<tr id="row1617865636084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841999404084834"><a name="p841999404084834"></a><a name="p841999404084834"></a><a href="utils.md#gaa0cf2e9b2a054c6ea46db972840fbc51">get_current_dir_name</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1945591940084834"><a name="p1945591940084834"></a><a name="p1945591940084834"></a>char * </p>
<p id="p2054976103084834"><a name="p2054976103084834"></a><a name="p2054976103084834"></a>Obtains the name of the current working directory. </p>
</td>
</tr>
<tr id="row1422456758084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p571314805084834"><a name="p571314805084834"></a><a name="p571314805084834"></a><a href="utils.md#ga3b818446c640442e94e746319f5f2858">sbrk</a> (intptr_t increment)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14335906084834"><a name="p14335906084834"></a><a name="p14335906084834"></a>void * </p>
<p id="p625064573084834"><a name="p625064573084834"></a><a name="p625064573084834"></a>Adjusts the heap size of a process. </p>
</td>
</tr>
<tr id="row654337306084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1193734523084834"><a name="p1193734523084834"></a><a name="p1193734523084834"></a><a href="utils.md#ga638757347bd9bf886b3d442b98033cf1">getpagesize</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p126777862084834"><a name="p126777862084834"></a><a name="p126777862084834"></a>int </p>
<p id="p916665428084834"><a name="p916665428084834"></a><a name="p916665428084834"></a>Obtains the memory page size. </p>
</td>
</tr>
<tr id="row1347419491084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835881624084834"><a name="p835881624084834"></a><a name="p835881624084834"></a><a href="utils.md#ga7c080ffcae5180218dda2df501e0cb15">chown</a> (const char *pathname, uid_t owner, gid_t group)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2079349491084834"><a name="p2079349491084834"></a><a name="p2079349491084834"></a>int </p>
<p id="p808270337084834"><a name="p808270337084834"></a><a name="p808270337084834"></a>Changes the user and group ownership of a file. </p>
</td>
</tr>
</tbody>
</table>

