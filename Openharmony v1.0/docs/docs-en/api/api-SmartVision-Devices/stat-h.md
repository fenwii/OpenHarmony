# stat.h<a name="EN-US_TOPIC_0000001055189449"></a>

## **Overview**<a name="section492059681084832"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Provides functions for file and directory operations. 

These functions can be used for file system operations, such as file read/write, directory traversal, and file system mounting.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section417781680084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table180771926084832"></a>
<table><thead align="left"><tr id="row1537775208084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p58499656084832"><a name="p58499656084832"></a><a name="p58499656084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p824013685084832"><a name="p824013685084832"></a><a name="p824013685084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1848320786084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1280681490084832"><a name="p1280681490084832"></a><a name="p1280681490084832"></a><a href="stat.md">stat</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554371096084832"><a name="p554371096084832"></a><a name="p554371096084832"></a>Defines the file information structure. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1206836946084832"></a>
<table><thead align="left"><tr id="row2116836133084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p182436732084832"><a name="p182436732084832"></a><a name="p182436732084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1685321034084832"><a name="p1685321034084832"></a><a name="p1685321034084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1081627936084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870664182084832"><a name="p870664182084832"></a><a name="p870664182084832"></a><a href="fs.md#gad2e0bcbe40344116102877f6268ee6ea">stat</a> (const char *__restrict path, struct <a href="stat.md">stat</a> *__restrict buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p184841862084832"><a name="p184841862084832"></a><a name="p184841862084832"></a>int </p>
<p id="p1980981785084832"><a name="p1980981785084832"></a><a name="p1980981785084832"></a>Obtains file information. </p>
</td>
</tr>
<tr id="row1533990793084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1500789189084832"><a name="p1500789189084832"></a><a name="p1500789189084832"></a><a href="fs.md#ga198a57e185e8a036ad06345623b84521">fstat</a> (int fd, struct <a href="stat.md">stat</a> *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p347456097084832"><a name="p347456097084832"></a><a name="p347456097084832"></a>int </p>
<p id="p654612340084832"><a name="p654612340084832"></a><a name="p654612340084832"></a>Obtains file status information. </p>
</td>
</tr>
<tr id="row547295941084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34296290084832"><a name="p34296290084832"></a><a name="p34296290084832"></a><a href="fs.md#ga879b7c433a19b6b07b42edcf3871c40f">lstat</a> (const char *__restrict path, struct <a href="stat.md">stat</a> *__restrict buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402865219084832"><a name="p1402865219084832"></a><a name="p1402865219084832"></a>int </p>
<p id="p1884120562084832"><a name="p1884120562084832"></a><a name="p1884120562084832"></a>Obtains file information. </p>
</td>
</tr>
<tr id="row357785439084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p685054705084832"><a name="p685054705084832"></a><a name="p685054705084832"></a><a href="fs.md#gaee98bbe743c2d14dbaa67f01c3fb9ed5">mkdir</a> (const char *pathname, mode_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841006153084832"><a name="p1841006153084832"></a><a name="p1841006153084832"></a>int </p>
<p id="p26871973084832"><a name="p26871973084832"></a><a name="p26871973084832"></a>Creates a directory. </p>
</td>
</tr>
<tr id="row1000267709084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1706795819084832"><a name="p1706795819084832"></a><a name="p1706795819084832"></a><a href="fs.md#ga6b0f61de936f648da290c92ed36192c4">mkfifo</a> (const char *name, mode_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705435053084832"><a name="p705435053084832"></a><a name="p705435053084832"></a>int </p>
<p id="p1675404371084832"><a name="p1675404371084832"></a><a name="p1675404371084832"></a>Creates a named pipe to implement inter-process communication. </p>
</td>
</tr>
<tr id="row789910750084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1707174645084832"><a name="p1707174645084832"></a><a name="p1707174645084832"></a><a href="fs.md#gae0b68526355956a8e3298fcb6a72e3bc">mkdirat</a> (int fd, const char *pathname, mode_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206097508084832"><a name="p206097508084832"></a><a name="p206097508084832"></a>int </p>
<p id="p548464402084832"><a name="p548464402084832"></a><a name="p548464402084832"></a>Creates a directory. </p>
</td>
</tr>
<tr id="row1918953956084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p454582379084832"><a name="p454582379084832"></a><a name="p454582379084832"></a><a href="fs.md#ga1b893413bc424887bbe61f8d0952a0ee">chmod</a> (const char *pathname, mode_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p845050245084832"><a name="p845050245084832"></a><a name="p845050245084832"></a>int </p>
<p id="p792042972084832"><a name="p792042972084832"></a><a name="p792042972084832"></a>Modifies permissions for a file. </p>
</td>
</tr>
<tr id="row624840625084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1388550490084832"><a name="p1388550490084832"></a><a name="p1388550490084832"></a><a href="fs.md#ga556063623e479c26c64544024a046024">umask</a> (mode_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p178700035084832"><a name="p178700035084832"></a><a name="p178700035084832"></a>mode_t </p>
<p id="p1761018719084832"><a name="p1761018719084832"></a><a name="p1761018719084832"></a>Sets umask for a process. </p>
</td>
</tr>
</tbody>
</table>

