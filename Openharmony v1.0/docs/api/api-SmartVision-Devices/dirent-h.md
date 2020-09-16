# dirent.h<a name="ZH-CN_TOPIC_0000001055707976"></a>

## **Overview**<a name="section1017345307084829"></a>

**Related Modules:**

[FS](FS.md)

**Description:**

Provides functions and structures used for performing file system operations, including file read/write, directory traversal, and file system mounting. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2116194256084829"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table941289598084829"></a>
<table><thead align="left"><tr id="row1118935664084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p387123418084829"><a name="p387123418084829"></a><a name="p387123418084829"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1388716986084829"><a name="p1388716986084829"></a><a name="p1388716986084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1893238379084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727923985084829"><a name="p727923985084829"></a><a name="p727923985084829"></a><a href="dirent.md">dirent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071092157084829"><a name="p2071092157084829"></a><a name="p2071092157084829"></a>Defines the content of the directory. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table579102071084829"></a>
<table><thead align="left"><tr id="row468739605084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2034427834084829"><a name="p2034427834084829"></a><a name="p2034427834084829"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1931574595084829"><a name="p1931574595084829"></a><a name="p1931574595084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1158307286084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558397991084829"><a name="p558397991084829"></a><a name="p558397991084829"></a><a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357190821084829"><a name="p1357190821084829"></a><a name="p1357190821084829"></a> typedef struct __dirstream&nbsp;</p>
<p id="p1594314475084829"><a name="p1594314475084829"></a><a name="p1594314475084829"></a>Opens the handle of the folder directory. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1774249912084829"></a>
<table><thead align="left"><tr id="row1601164708084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1947372552084829"><a name="p1947372552084829"></a><a name="p1947372552084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p759831775084829"><a name="p759831775084829"></a><a name="p759831775084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1977850163084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14617655084829"><a name="p14617655084829"></a><a name="p14617655084829"></a><a href="FS.md#gaaeac2b41e8c2c3a5f91c9bd511a8c0a6">closedir</a> (<a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *dirp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2116904978084829"><a name="p2116904978084829"></a><a name="p2116904978084829"></a>int&nbsp;</p>
<p id="p2144084126084829"><a name="p2144084126084829"></a><a name="p2144084126084829"></a>Closes a specified directory. </p>
</td>
</tr>
<tr id="row577975437084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079503289084829"><a name="p2079503289084829"></a><a name="p2079503289084829"></a><a href="FS.md#gad09dd96447776d2bc5d8321e4b499591">opendir</a> (const char *<a href="FS.md#gab1b6028f4625caec30c1020e737216e2">dirname</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1028350732084829"><a name="p1028350732084829"></a><a name="p1028350732084829"></a><a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *&nbsp;</p>
<p id="p1140641568084829"><a name="p1140641568084829"></a><a name="p1140641568084829"></a>Opens a specified directory. </p>
</td>
</tr>
<tr id="row872339008084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132946733084829"><a name="p2132946733084829"></a><a name="p2132946733084829"></a><a href="FS.md#ga58257faf8b13b3f14558613c632b2373">readdir</a> (<a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *dirp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p652651275084829"><a name="p652651275084829"></a><a name="p652651275084829"></a>struct <a href="dirent.md">dirent</a> *&nbsp;</p>
<p id="p1597190442084829"><a name="p1597190442084829"></a><a name="p1597190442084829"></a>Reads a specified directory. </p>
</td>
</tr>
<tr id="row872150628084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p338726387084829"><a name="p338726387084829"></a><a name="p338726387084829"></a><a href="FS.md#ga9f1bc61c37394eda9e74e0c79afec872">readdir_r</a> (<a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *__restrict dirp, struct <a href="dirent.md">dirent</a> *__restrict <a href="entry.md">entry</a>, struct <a href="dirent.md">dirent</a> **__restrict result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68291362084829"><a name="p68291362084829"></a><a name="p68291362084829"></a>int&nbsp;</p>
<p id="p936357930084829"><a name="p936357930084829"></a><a name="p936357930084829"></a>Reads a specified directory (thread-safe version). </p>
</td>
</tr>
<tr id="row754763681084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p202714724084829"><a name="p202714724084829"></a><a name="p202714724084829"></a><a href="FS.md#gad4fcb58b9194b1a3c1699654de963719">rewinddir</a> (<a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *dirp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554861879084829"><a name="p554861879084829"></a><a name="p554861879084829"></a>void&nbsp;</p>
<p id="p1928454079084829"><a name="p1928454079084829"></a><a name="p1928454079084829"></a>Resets a directory stream read position. </p>
</td>
</tr>
<tr id="row160318952084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197459484084829"><a name="p1197459484084829"></a><a name="p1197459484084829"></a><a href="FS.md#ga8a52fd9a3ded793b8200ac0a5a1f10d2">alphasort</a> (const struct <a href="dirent.md">dirent</a> **a, const struct <a href="dirent.md">dirent</a> **b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p110678932084829"><a name="p110678932084829"></a><a name="p110678932084829"></a>int&nbsp;</p>
<p id="p1631218465084829"><a name="p1631218465084829"></a><a name="p1631218465084829"></a>Sorts the directory entries in alphabetical order. </p>
</td>
</tr>
<tr id="row1162229010084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p673261011084829"><a name="p673261011084829"></a><a name="p673261011084829"></a><a href="FS.md#gaca6df630e382cf13bac90ed6e5c4141c">scandir</a> (const char *dir, struct <a href="dirent.md">dirent</a> ***namelist, int(*sel)(const struct <a href="dirent.md">dirent</a> *), int(*compar)(const struct <a href="dirent.md">dirent</a> **, const struct <a href="dirent.md">dirent</a> **))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121529313084829"><a name="p1121529313084829"></a><a name="p1121529313084829"></a>int&nbsp;</p>
<p id="p1657080235084829"><a name="p1657080235084829"></a><a name="p1657080235084829"></a>Scans directory to find the target entries. </p>
</td>
</tr>
<tr id="row1165479813084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844296141084829"><a name="p844296141084829"></a><a name="p844296141084829"></a><a href="FS.md#gacf0a74ce364760e330619edb38eadfff">seekdir</a> (<a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *dirp, long offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497519139084829"><a name="p497519139084829"></a><a name="p497519139084829"></a>void&nbsp;</p>
<p id="p292210228084829"><a name="p292210228084829"></a><a name="p292210228084829"></a>Sets the position of the next <a href="FS.md#ga58257faf8b13b3f14558613c632b2373">readdir</a> call in the directory stream. </p>
</td>
</tr>
<tr id="row881285609084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773433691084829"><a name="p1773433691084829"></a><a name="p1773433691084829"></a><a href="FS.md#ga4c2cd02bd612ae655782632c9f5227ec">telldir</a> (<a href="FS.md#ga0ebe68390948c14bb9d82987adbfc849">DIR</a> *dirp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121372254084829"><a name="p1121372254084829"></a><a name="p1121372254084829"></a>long&nbsp;</p>
<p id="p93120418084829"><a name="p93120418084829"></a><a name="p93120418084829"></a>Obtains the current position in the specified directory stream. </p>
</td>
</tr>
</tbody>
</table>

