# stdio.h<a name="ZH-CN_TOPIC_0000001054829489"></a>

## **Overview**<a name="section514986757084832"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Declares common functions used for performing input and output \(I/O\) operations. 

You can use the functions provided in this file to perform the I/O operations required during development. Distinguished by I/O targets, there are standard I/O, file stream I/O, and string I/O. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section551752401084832"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table251774991084832"></a>
<table><thead align="left"><tr id="row1529138586084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p379158778084832"><a name="p379158778084832"></a><a name="p379158778084832"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1051953816084832"><a name="p1051953816084832"></a><a name="p1051953816084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row865689722084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340789351084832"><a name="p1340789351084832"></a><a name="p1340789351084832"></a><a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p770639519084832"><a name="p770639519084832"></a><a name="p770639519084832"></a> typedef struct _IO_FILE&nbsp;</p>
<p id="p1141502744084832"><a name="p1141502744084832"></a><a name="p1141502744084832"></a>Struct of file stream. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table498490666084832"></a>
<table><thead align="left"><tr id="row2126250749084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1655294344084832"><a name="p1655294344084832"></a><a name="p1655294344084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p248861961084832"><a name="p248861961084832"></a><a name="p248861961084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row384426946084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898538295084832"><a name="p1898538295084832"></a><a name="p1898538295084832"></a><a href="IO.md#ga58386e895d3c07b008c8865b2a9716fb">fopen</a> (const char *__restrict path, const char *__restrict mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1497865213084832"><a name="p1497865213084832"></a><a name="p1497865213084832"></a><a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *&nbsp;</p>
<p id="p1388731660084832"><a name="p1388731660084832"></a><a name="p1388731660084832"></a>Opens the file stored in the specified path based on the given mode. </p>
</td>
</tr>
<tr id="row79128963084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p246105861084832"><a name="p246105861084832"></a><a name="p246105861084832"></a><a href="IO.md#gac41a0ad4b31be2ad59d8222a0de30bda">fclose</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141014990084832"><a name="p1141014990084832"></a><a name="p1141014990084832"></a>int&nbsp;</p>
<p id="p501576849084832"><a name="p501576849084832"></a><a name="p501576849084832"></a>Closes a file based on the specified file descriptor. </p>
</td>
</tr>
<tr id="row1709852360084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101450494084832"><a name="p1101450494084832"></a><a name="p1101450494084832"></a><a href="IO.md#ga02b13b56a188401119ea4da43c184913">remove</a> (const char *pathname)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844629892084832"><a name="p1844629892084832"></a><a name="p1844629892084832"></a>int&nbsp;</p>
<p id="p561280857084832"><a name="p561280857084832"></a><a name="p561280857084832"></a>Deletes a specified file or directory from the file system. </p>
</td>
</tr>
<tr id="row796084637084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p407488915084832"><a name="p407488915084832"></a><a name="p407488915084832"></a><a href="IO.md#ga4d4709508ed7604103d77c3fdc5ea4a2">rename</a> (const char *oldpath, const char *newpath)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564210448084832"><a name="p564210448084832"></a><a name="p564210448084832"></a>int&nbsp;</p>
<p id="p1209380175084832"><a name="p1209380175084832"></a><a name="p1209380175084832"></a>Renames a specified file. </p>
</td>
</tr>
<tr id="row737950414084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1645676193084832"><a name="p1645676193084832"></a><a name="p1645676193084832"></a><a href="IO.md#gafb95de1535a5a185954819539f3c6ca5">feof</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p578876596084832"><a name="p578876596084832"></a><a name="p578876596084832"></a>int&nbsp;</p>
<p id="p1239466669084832"><a name="p1239466669084832"></a><a name="p1239466669084832"></a>Tests the end-of-file indicator for a specified stream. </p>
</td>
</tr>
<tr id="row1790018101084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p807062940084832"><a name="p807062940084832"></a><a name="p807062940084832"></a><a href="IO.md#ga4a98383bb54291c2abede7aa28acf597">ferror</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1034692170084832"><a name="p1034692170084832"></a><a name="p1034692170084832"></a>int&nbsp;</p>
<p id="p2119807291084832"><a name="p2119807291084832"></a><a name="p2119807291084832"></a>Tests for the error identifier of a specified file stream. </p>
</td>
</tr>
<tr id="row1145146101084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p837142200084832"><a name="p837142200084832"></a><a name="p837142200084832"></a><a href="IO.md#gae4459e830d3e2abcf428337a661d9456">fflush</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p210995026084832"><a name="p210995026084832"></a><a name="p210995026084832"></a>int&nbsp;</p>
<p id="p1234939691084832"><a name="p1234939691084832"></a><a name="p1234939691084832"></a>Flushes the output buffer of a specified stream. </p>
</td>
</tr>
<tr id="row859867631084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p632013375084832"><a name="p632013375084832"></a><a name="p632013375084832"></a><a href="IO.md#ga81202d6a15259fbceb71a961a878b01a">clearerr</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538615200084832"><a name="p1538615200084832"></a><a name="p1538615200084832"></a>void&nbsp;</p>
<p id="p469658577084832"><a name="p469658577084832"></a><a name="p469658577084832"></a>Resets the error indicators. </p>
</td>
</tr>
<tr id="row1087737428084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1691122450084832"><a name="p1691122450084832"></a><a name="p1691122450084832"></a><a href="IO.md#gaece5d6e00c239ffd0847d8d2ef65bd57">fseek</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp, long offset, int whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363104050084832"><a name="p1363104050084832"></a><a name="p1363104050084832"></a>int&nbsp;</p>
<p id="p55622734084832"><a name="p55622734084832"></a><a name="p55622734084832"></a>Changes the position of a specified stream to a new position. </p>
</td>
</tr>
<tr id="row1500991376084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1254019955084832"><a name="p1254019955084832"></a><a name="p1254019955084832"></a><a href="IO.md#gaae4231ac8066eb54ea1d9d12d551605c">ftell</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2098062337084832"><a name="p2098062337084832"></a><a name="p2098062337084832"></a>long&nbsp;</p>
<p id="p199605005084832"><a name="p199605005084832"></a><a name="p199605005084832"></a>Obtains the current value of the file position indicator for a specified file stream. </p>
</td>
</tr>
<tr id="row1070098730084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220337423084832"><a name="p1220337423084832"></a><a name="p1220337423084832"></a><a href="IO.md#gaa0cd401f198d33d9d01a9e8aa4026819">rewind</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p901689715084832"><a name="p901689715084832"></a><a name="p901689715084832"></a>void&nbsp;</p>
<p id="p1356242731084832"><a name="p1356242731084832"></a><a name="p1356242731084832"></a>Sets the position indicator of a specified stream to the beginning of the file. </p>
</td>
</tr>
<tr id="row990967451084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1021563245084832"><a name="p1021563245084832"></a><a name="p1021563245084832"></a><a href="IO.md#gaf2e2b1a01359f5f7068b61d1dffcdcdd">fgetpos</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, fpos_t *pos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1663611449084832"><a name="p1663611449084832"></a><a name="p1663611449084832"></a>int&nbsp;</p>
<p id="p1261588948084832"><a name="p1261588948084832"></a><a name="p1261588948084832"></a>Obtains the current file position of a specified stream and writes it to the <strong id="b1641544266084832"><a name="b1641544266084832"></a><a name="b1641544266084832"></a>pos</strong> parameter. </p>
</td>
</tr>
<tr id="row938176080084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073685885084832"><a name="p2073685885084832"></a><a name="p2073685885084832"></a><a href="IO.md#gae47e3f92dd8fc42ce0b6384c03ce6a9b">fsetpos</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp, const fpos_t *pos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1771289651084832"><a name="p1771289651084832"></a><a name="p1771289651084832"></a>int&nbsp;</p>
<p id="p1340193839084832"><a name="p1340193839084832"></a><a name="p1340193839084832"></a>Sets the file position indicator for a specified file stream. </p>
</td>
</tr>
<tr id="row1709982970084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807377288084832"><a name="p1807377288084832"></a><a name="p1807377288084832"></a><a href="IO.md#ga091b3f41bdd6984d63ea48d87a62bfd2">fread</a> (void *__restrict ptr, size_t size, size_t nmemb, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *__restrict stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342514980084832"><a name="p1342514980084832"></a><a name="p1342514980084832"></a>size_t&nbsp;</p>
<p id="p1709796988084832"><a name="p1709796988084832"></a><a name="p1709796988084832"></a>Reads data from a specified stream. </p>
</td>
</tr>
<tr id="row621318322084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1937922812084832"><a name="p1937922812084832"></a><a name="p1937922812084832"></a><a href="IO.md#gaf86a4505e5de39a100f7ea828377b585">fwrite</a> (const void *__restrict ptr, size_t size, size_t nmemb, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *__restrict stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1859162933084832"><a name="p1859162933084832"></a><a name="p1859162933084832"></a>size_t&nbsp;</p>
<p id="p1278850077084832"><a name="p1278850077084832"></a><a name="p1278850077084832"></a>Writes data to a specified stream. </p>
</td>
</tr>
<tr id="row678591163084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1170862118084832"><a name="p1170862118084832"></a><a name="p1170862118084832"></a><a href="IO.md#gad5a0ea2c21a23a380b7c30fe35fa9456">getc</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p914025871084832"><a name="p914025871084832"></a><a name="p914025871084832"></a>int&nbsp;</p>
<p id="p1257764039084832"><a name="p1257764039084832"></a><a name="p1257764039084832"></a>Reads a character from a specified file stream. </p>
</td>
</tr>
<tr id="row173964797084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p856050775084832"><a name="p856050775084832"></a><a name="p856050775084832"></a><a href="IO.md#ga3e29caa20f7cffe18f410f01278905a8">getchar</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p350133619084832"><a name="p350133619084832"></a><a name="p350133619084832"></a>int&nbsp;</p>
<p id="p857033200084832"><a name="p857033200084832"></a><a name="p857033200084832"></a>Obtains the next character from the standard input (stdin). </p>
</td>
</tr>
<tr id="row1256643156084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453843995084832"><a name="p1453843995084832"></a><a name="p1453843995084832"></a><a href="IO.md#ga54efa95b6d5b41adec98e5b8a1a9f27b">ungetc</a> (int c, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p951981078084832"><a name="p951981078084832"></a><a name="p951981078084832"></a>int&nbsp;</p>
<p id="p1024784017084832"><a name="p1024784017084832"></a><a name="p1024784017084832"></a>Pushes a character back into a specified file stream. </p>
</td>
</tr>
<tr id="row95428019084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945123695084832"><a name="p1945123695084832"></a><a name="p1945123695084832"></a><a href="IO.md#gabe6299d5823dd023e610aaa619735a3f">fputc</a> (int c, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946586144084832"><a name="p946586144084832"></a><a name="p946586144084832"></a>int&nbsp;</p>
<p id="p1640393423084832"><a name="p1640393423084832"></a><a name="p1640393423084832"></a>Writes a character into the position pointed to by a specified stream. </p>
</td>
</tr>
<tr id="row461832947084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p151145176084832"><a name="p151145176084832"></a><a name="p151145176084832"></a><a href="IO.md#ga38f980218f04ebdddcdcd1b77e1cf6b1">putc</a> (int c, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311650540084832"><a name="p311650540084832"></a><a name="p311650540084832"></a>int&nbsp;</p>
<p id="p1909917924084832"><a name="p1909917924084832"></a><a name="p1909917924084832"></a>Writes a character to a specified file stream. </p>
</td>
</tr>
<tr id="row1716505917084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1802856511084832"><a name="p1802856511084832"></a><a name="p1802856511084832"></a><a href="IO.md#gaf4de2514b7778805db3815e8dd6cf09a">putchar</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1447582174084832"><a name="p1447582174084832"></a><a name="p1447582174084832"></a>int&nbsp;</p>
<p id="p2110541045084832"><a name="p2110541045084832"></a><a name="p2110541045084832"></a>Writes a character into the standard output (stdout). </p>
</td>
</tr>
<tr id="row290126375084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1317773879084832"><a name="p1317773879084832"></a><a name="p1317773879084832"></a><a href="IO.md#ga2b3df0e66b41edab3c039191fe6cc4f9">fgets</a> (char *s, int size, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96693064084832"><a name="p96693064084832"></a><a name="p96693064084832"></a>char *&nbsp;</p>
<p id="p1199139060084832"><a name="p1199139060084832"></a><a name="p1199139060084832"></a>Reads a line of characters from a specified file stream and stores it into the string pointed to by <strong id="b729082833084832"><a name="b729082833084832"></a><a name="b729082833084832"></a>s</strong>. </p>
</td>
</tr>
<tr id="row799930076084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1917563554084832"><a name="p1917563554084832"></a><a name="p1917563554084832"></a><a href="IO.md#gaab85b30d68ce9d9e0475e0f51bf610b1">gets</a> (char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775166446084832"><a name="p1775166446084832"></a><a name="p1775166446084832"></a>char *&nbsp;</p>
<p id="p436958380084832"><a name="p436958380084832"></a><a name="p436958380084832"></a>Reads a line of characters from the stdin and stores it in the buffer. </p>
</td>
</tr>
<tr id="row201186601084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1940971645084832"><a name="p1940971645084832"></a><a name="p1940971645084832"></a><a href="IO.md#ga68236e664c1f0da049b25fba1c1695f6">fputs</a> (const char *s, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p189049327084832"><a name="p189049327084832"></a><a name="p189049327084832"></a>int&nbsp;</p>
<p id="p703718318084832"><a name="p703718318084832"></a><a name="p703718318084832"></a>Writes a character string (excluding the terminating null character) to a specified file stream. </p>
</td>
</tr>
<tr id="row763920722084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p134795309084832"><a name="p134795309084832"></a><a name="p134795309084832"></a><a href="IO.md#gad41876f99f190c7488e64ef39c50a23f">puts</a> (const char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p972965254084832"><a name="p972965254084832"></a><a name="p972965254084832"></a>int&nbsp;</p>
<p id="p2036898437084832"><a name="p2036898437084832"></a><a name="p2036898437084832"></a>Writes a character string and appends a new-line character to the stdout. </p>
</td>
</tr>
<tr id="row1956966113084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380874053084832"><a name="p380874053084832"></a><a name="p380874053084832"></a><a href="IO.md#ga98631211a4a8aee62f572375d5b637be">printf</a> (const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p47564364084832"><a name="p47564364084832"></a><a name="p47564364084832"></a>int&nbsp;</p>
<p id="p1476914768084832"><a name="p1476914768084832"></a><a name="p1476914768084832"></a>Formats arguments based on <strong id="b1110686027084832"><a name="b1110686027084832"></a><a name="b1110686027084832"></a>format</strong> and prints formatted data to the stdout. </p>
</td>
</tr>
<tr id="row647259795084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1954456574084832"><a name="p1954456574084832"></a><a name="p1954456574084832"></a><a href="IO.md#gad9291335f34e874c8431285d705bc3aa">fprintf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330635774084832"><a name="p1330635774084832"></a><a name="p1330635774084832"></a>int&nbsp;</p>
<p id="p728251860084832"><a name="p728251860084832"></a><a name="p728251860084832"></a>Formats arguments based on <strong id="b206655117084832"><a name="b206655117084832"></a><a name="b206655117084832"></a>format</strong> and prints formatted data to a specified file stream. </p>
</td>
</tr>
<tr id="row929250525084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858458217084832"><a name="p858458217084832"></a><a name="p858458217084832"></a><a href="IO.md#ga3082155ec11e7229f7a20439b31a169e">sprintf</a> (char *str, const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1577424910084832"><a name="p1577424910084832"></a><a name="p1577424910084832"></a>int&nbsp;</p>
<p id="p223658368084832"><a name="p223658368084832"></a><a name="p223658368084832"></a>Prints formatted data from a variable argument list to a specified string. </p>
</td>
</tr>
<tr id="row986663059084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1154191461084832"><a name="p1154191461084832"></a><a name="p1154191461084832"></a><a href="IO.md#gad76145a6edfc98981ded8815a760e0cd">snprintf</a> (char *str, size_t size, const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776033341084832"><a name="p776033341084832"></a><a name="p776033341084832"></a>int&nbsp;</p>
<p id="p231347941084832"><a name="p231347941084832"></a><a name="p231347941084832"></a>Prints formatted data of a maximum of <strong id="b421023802084832"><a name="b421023802084832"></a><a name="b421023802084832"></a>size</strong> bytes from a variable argument list to a specified string. </p>
</td>
</tr>
<tr id="row360220131084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1362163932084832"><a name="p1362163932084832"></a><a name="p1362163932084832"></a><a href="IO.md#gaa715ef816dc040c8b367fde4ba84d6f3">vprintf</a> (const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827326593084832"><a name="p1827326593084832"></a><a name="p1827326593084832"></a>int&nbsp;</p>
<p id="p1229332573084832"><a name="p1229332573084832"></a><a name="p1229332573084832"></a>Prints formatted data from a variable argument list to the stdout. </p>
</td>
</tr>
<tr id="row12971859084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1902574901084832"><a name="p1902574901084832"></a><a name="p1902574901084832"></a><a href="IO.md#gad80f05917df38df3a5e1817498d67c26">vfprintf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441905565084832"><a name="p1441905565084832"></a><a name="p1441905565084832"></a>int&nbsp;</p>
<p id="p203114977084832"><a name="p203114977084832"></a><a name="p203114977084832"></a>Prints formatted data from a variable argument list to a specified file stream. </p>
</td>
</tr>
<tr id="row44739903084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1909767099084832"><a name="p1909767099084832"></a><a name="p1909767099084832"></a><a href="IO.md#gaab3db67c98c32122fcb3d076d4207bbc">vsprintf</a> (char *str, const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080493223084832"><a name="p1080493223084832"></a><a name="p1080493223084832"></a>int&nbsp;</p>
<p id="p1264801410084832"><a name="p1264801410084832"></a><a name="p1264801410084832"></a>Prints formatted data from a variable argument list to a specified string. </p>
</td>
</tr>
<tr id="row1882168786084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529570323084832"><a name="p529570323084832"></a><a name="p529570323084832"></a><a href="IO.md#ga2cadafbeb2d6e0d5781f6e5106d41fc2">vsnprintf</a> (char *str, size_t size, const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1819521079084832"><a name="p1819521079084832"></a><a name="p1819521079084832"></a>int&nbsp;</p>
<p id="p1466017990084832"><a name="p1466017990084832"></a><a name="p1466017990084832"></a>Prints formatted data of a maximum of <strong id="b57455422084832"><a name="b57455422084832"></a><a name="b57455422084832"></a>size</strong> bytes from a variable argument list to a specified string. </p>
</td>
</tr>
<tr id="row518174159084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p661756702084832"><a name="p661756702084832"></a><a name="p661756702084832"></a><a href="IO.md#ga5c48433db9c04031772d5b36e6c4411d">scanf</a> (const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1053855447084832"><a name="p1053855447084832"></a><a name="p1053855447084832"></a>int&nbsp;</p>
<p id="p1583773751084832"><a name="p1583773751084832"></a><a name="p1583773751084832"></a>Reads formatted data from the stdin and stores the data to the additional arguments based on <strong id="b796494144084832"><a name="b796494144084832"></a><a name="b796494144084832"></a>format</strong>. </p>
</td>
</tr>
<tr id="row1068421549084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284828302084832"><a name="p284828302084832"></a><a name="p284828302084832"></a><a href="IO.md#gae902a7b8796799a6e076f07e9d7de045">fscanf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679698108084832"><a name="p1679698108084832"></a><a name="p1679698108084832"></a>int&nbsp;</p>
<p id="p2035312283084832"><a name="p2035312283084832"></a><a name="p2035312283084832"></a>Reads formatted data from a specified file stream and stores it based on <strong id="b1009066413084832"><a name="b1009066413084832"></a><a name="b1009066413084832"></a>format</strong> into the locations pointed to by the variable arguments. </p>
</td>
</tr>
<tr id="row452601739084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1052691735084832"><a name="p1052691735084832"></a><a name="p1052691735084832"></a><a href="IO.md#gaec1e54556dca3bd701d44395d34818dd">sscanf</a> (const char *str, const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931852713084832"><a name="p931852713084832"></a><a name="p931852713084832"></a>int&nbsp;</p>
<p id="p1596861387084832"><a name="p1596861387084832"></a><a name="p1596861387084832"></a>Reads data from a character string pointed to by <strong id="b1310548230084832"><a name="b1310548230084832"></a><a name="b1310548230084832"></a>str</strong> and stores it based on <strong id="b1912273839084832"><a name="b1912273839084832"></a><a name="b1912273839084832"></a>format</strong> into the locations pointed to by the variable arguments. </p>
</td>
</tr>
<tr id="row183527071084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p766778157084832"><a name="p766778157084832"></a><a name="p766778157084832"></a><a href="IO.md#ga40250d63904acd3e898061c9eab6ead3">vscanf</a> (const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1886787440084832"><a name="p1886787440084832"></a><a name="p1886787440084832"></a>int&nbsp;</p>
<p id="p817671958084832"><a name="p817671958084832"></a><a name="p817671958084832"></a>Reads data from the stdin and stores it based on <strong id="b1841077211084832"><a name="b1841077211084832"></a><a name="b1841077211084832"></a>format</strong> into the locations pointed to by the elements in the variable argument list identified by <strong id="b955478215084832"><a name="b955478215084832"></a><a name="b955478215084832"></a>ap</strong>. </p>
</td>
</tr>
<tr id="row1782879807084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p986401749084832"><a name="p986401749084832"></a><a name="p986401749084832"></a><a href="IO.md#gabdd32e401e37c9d954f3f0a6907500d9">vfscanf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1853161337084832"><a name="p1853161337084832"></a><a name="p1853161337084832"></a>int&nbsp;</p>
<p id="p1583038964084832"><a name="p1583038964084832"></a><a name="p1583038964084832"></a>Reads data from a specified file stream and stores it based on <strong id="b876943104084832"><a name="b876943104084832"></a><a name="b876943104084832"></a>format</strong> into the locations pointed to by the elements in the variable argument list identified by <strong id="b1019883159084832"><a name="b1019883159084832"></a><a name="b1019883159084832"></a>ap</strong>. </p>
</td>
</tr>
<tr id="row562731176084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p840205569084832"><a name="p840205569084832"></a><a name="p840205569084832"></a><a href="IO.md#gab1c4552aba80fe03c9b45fe27f4331ad">vsscanf</a> (const char *str, const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555762322084832"><a name="p1555762322084832"></a><a name="p1555762322084832"></a>int&nbsp;</p>
<p id="p967962552084832"><a name="p967962552084832"></a><a name="p967962552084832"></a>Reads data from a specified string and stores it based on <strong id="b760346435084832"><a name="b760346435084832"></a><a name="b760346435084832"></a>format</strong> into the locations pointed to by the elements in the variable argument list identified by <strong id="b432928958084832"><a name="b432928958084832"></a><a name="b432928958084832"></a>ap</strong>. </p>
</td>
</tr>
<tr id="row1523602408084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p810518301084832"><a name="p810518301084832"></a><a name="p810518301084832"></a><a href="IO.md#ga80b37b56a5a42139dccaef56da4bf82a">perror</a> (const char *msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061699577084832"><a name="p2061699577084832"></a><a name="p2061699577084832"></a>void&nbsp;</p>
<p id="p610706727084832"><a name="p610706727084832"></a><a name="p610706727084832"></a>Prints the last error occurred during a call to a system or library function to the standard error output stream (stderr). </p>
</td>
</tr>
<tr id="row1580998420084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637694857084832"><a name="p637694857084832"></a><a name="p637694857084832"></a><a href="IO.md#gaf691eb990d669a9edec8a9ec721ce3bc">setvbuf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, char *buf, int mode, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432028260084832"><a name="p1432028260084832"></a><a name="p1432028260084832"></a>int&nbsp;</p>
<p id="p902372169084832"><a name="p902372169084832"></a><a name="p902372169084832"></a>Sets the mode and size of the buffer for a specified stream. </p>
</td>
</tr>
<tr id="row1912930057084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p13205862084832"><a name="p13205862084832"></a><a name="p13205862084832"></a><a href="IO.md#ga36d24924e1acc69f9c3ce49a832615fe">setbuf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, char *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p138957296084832"><a name="p138957296084832"></a><a name="p138957296084832"></a>void&nbsp;</p>
<p id="p730172728084832"><a name="p730172728084832"></a><a name="p730172728084832"></a>Sets a buffer to be used by a specified stream. </p>
</td>
</tr>
<tr id="row1846810228084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34747281084832"><a name="p34747281084832"></a><a name="p34747281084832"></a><a href="IO.md#ga6b2efc6515c53ab5f0c9800c35f65789">fmemopen</a> (void *buf, size_t size, const char *mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p426807927084832"><a name="p426807927084832"></a><a name="p426807927084832"></a><a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *&nbsp;</p>
<p id="p465638360084832"><a name="p465638360084832"></a><a name="p465638360084832"></a>Opens a memory stream that allows the access mode specified by <strong id="b1906011424084832"><a name="b1906011424084832"></a><a name="b1906011424084832"></a>mode</strong>. </p>
</td>
</tr>
<tr id="row777065919084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069413294084832"><a name="p2069413294084832"></a><a name="p2069413294084832"></a><a href="IO.md#gac7250554d80d31f4d8ad316c4c3c3c85">open_memstream</a> (char **ptr, size_t *size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p251946892084832"><a name="p251946892084832"></a><a name="p251946892084832"></a><a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *&nbsp;</p>
<p id="p482571526084832"><a name="p482571526084832"></a><a name="p482571526084832"></a>Opens a stream for writing to a specified buffer. </p>
</td>
</tr>
<tr id="row787627205084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589808690084832"><a name="p589808690084832"></a><a name="p589808690084832"></a><a href="IO.md#ga30839d83d780a6a3d13bf40c2d666827">pclose</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *f)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1285493797084832"><a name="p1285493797084832"></a><a name="p1285493797084832"></a>int&nbsp;</p>
<p id="p733260398084832"><a name="p733260398084832"></a><a name="p733260398084832"></a>Closes a specified pipe. </p>
</td>
</tr>
<tr id="row2107739804084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1239487976084832"><a name="p1239487976084832"></a><a name="p1239487976084832"></a><a href="IO.md#ga03681b8592bba6fe02941b9abc182808">fileno</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p123850964084832"><a name="p123850964084832"></a><a name="p123850964084832"></a>int&nbsp;</p>
<p id="p145765462084832"><a name="p145765462084832"></a><a name="p145765462084832"></a>Obtains the file descriptor of a specified file stream. </p>
</td>
</tr>
<tr id="row1834111670084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224118416084832"><a name="p224118416084832"></a><a name="p224118416084832"></a><a href="IO.md#ga6926f47b76b028f112045fbe7ced4115">fseeko</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp, off_t offset, int whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p695789608084832"><a name="p695789608084832"></a><a name="p695789608084832"></a>int&nbsp;</p>
<p id="p978649391084832"><a name="p978649391084832"></a><a name="p978649391084832"></a>Sets the position of the next input or output operation on a specified file stream. </p>
</td>
</tr>
<tr id="row496280481084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451048563084832"><a name="p1451048563084832"></a><a name="p1451048563084832"></a><a href="IO.md#ga5f52ea043b9a2aa4d8cc92d674a2117b">ftello</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *fp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1626427776084832"><a name="p1626427776084832"></a><a name="p1626427776084832"></a>off_t&nbsp;</p>
<p id="p839589834084832"><a name="p839589834084832"></a><a name="p839589834084832"></a>Obtains the current value of the file position indicator for a specified file stream. </p>
</td>
</tr>
<tr id="row1623520464084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2002610234084832"><a name="p2002610234084832"></a><a name="p2002610234084832"></a><a href="IO.md#ga5fe0fc8fe920b640d488856c5ca43cb5">dprintf</a> (int fd, const char *format,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1408524810084832"><a name="p1408524810084832"></a><a name="p1408524810084832"></a>int&nbsp;</p>
<p id="p1434988198084832"><a name="p1434988198084832"></a><a name="p1434988198084832"></a>Prints formatted data to a specified file. </p>
</td>
</tr>
<tr id="row900637347084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p978308616084832"><a name="p978308616084832"></a><a name="p978308616084832"></a><a href="IO.md#ga0d0a950c2b4e6fba795cb7d8f2e8b8b8">vdprintf</a> (int fd, const char *format, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p196190309084832"><a name="p196190309084832"></a><a name="p196190309084832"></a>int&nbsp;</p>
<p id="p1199875567084832"><a name="p1199875567084832"></a><a name="p1199875567084832"></a>Prints formatted data from a variable argument list to a specified file. </p>
</td>
</tr>
<tr id="row806779766084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p129824912084832"><a name="p129824912084832"></a><a name="p129824912084832"></a><a href="IO.md#gab486b89691678e4873ec8b1b15c2678a">ftrylockfile</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *filehandle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1518805345084832"><a name="p1518805345084832"></a><a name="p1518805345084832"></a>int&nbsp;</p>
<p id="p500467533084832"><a name="p500467533084832"></a><a name="p500467533084832"></a>Locks a specified file. </p>
</td>
</tr>
<tr id="row831534143084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1036177054084832"><a name="p1036177054084832"></a><a name="p1036177054084832"></a><a href="IO.md#ga4f016c54ff86ca62454417bb7b32ab11">funlockfile</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *filehandle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1514148839084832"><a name="p1514148839084832"></a><a name="p1514148839084832"></a>void&nbsp;</p>
<p id="p1726479386084832"><a name="p1726479386084832"></a><a name="p1726479386084832"></a>Unlocks a specified file. </p>
</td>
</tr>
<tr id="row490708202084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226234378084832"><a name="p226234378084832"></a><a name="p226234378084832"></a><a href="IO.md#ga169f9b7e933ba56156885e30f7263b28">getc_unlocked</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420506783084832"><a name="p420506783084832"></a><a name="p420506783084832"></a>int&nbsp;</p>
<p id="p1982160072084832"><a name="p1982160072084832"></a><a name="p1982160072084832"></a>Obtains a character from a specified file stream without locking the file stream or checking whether it is locked. </p>
</td>
</tr>
<tr id="row599913563084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1855787697084832"><a name="p1855787697084832"></a><a name="p1855787697084832"></a><a href="IO.md#gafef7e39f2376c63728163cd5ccfbe99e">getchar_unlocked</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314188722084832"><a name="p1314188722084832"></a><a name="p1314188722084832"></a>int&nbsp;</p>
<p id="p322168833084832"><a name="p322168833084832"></a><a name="p322168833084832"></a>Obtains the next character from stdin. </p>
</td>
</tr>
<tr id="row1820397202084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1275858433084832"><a name="p1275858433084832"></a><a name="p1275858433084832"></a><a href="IO.md#ga340b21ecb337abb08905095e673672f6">putc_unlocked</a> (int c, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p401957240084832"><a name="p401957240084832"></a><a name="p401957240084832"></a>int&nbsp;</p>
<p id="p310830379084832"><a name="p310830379084832"></a><a name="p310830379084832"></a>Writes a character to a specified file stream with the thread remains unlocked. </p>
</td>
</tr>
<tr id="row1894560236084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139075924084832"><a name="p2139075924084832"></a><a name="p2139075924084832"></a><a href="IO.md#ga07ff061a8fed45cdedbecdd899b5fdb1">putchar_unlocked</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1590622694084832"><a name="p1590622694084832"></a><a name="p1590622694084832"></a>int&nbsp;</p>
<p id="p534142014084832"><a name="p534142014084832"></a><a name="p534142014084832"></a>Writes a character to the stdout with the thread remains unlocked. </p>
</td>
</tr>
<tr id="row292842001084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p648880650084832"><a name="p648880650084832"></a><a name="p648880650084832"></a><a href="IO.md#gab87a24b4c09e8fc3712a6d6090bfd371">getdelim</a> (char **lineptr, size_t *n, int delim, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1842764688084832"><a name="p1842764688084832"></a><a name="p1842764688084832"></a>ssize_t&nbsp;</p>
<p id="p1420397108084832"><a name="p1420397108084832"></a><a name="p1420397108084832"></a>Reads an entire line from a specified file stream. </p>
</td>
</tr>
<tr id="row70303890084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p792492741084832"><a name="p792492741084832"></a><a name="p792492741084832"></a><a href="IO.md#gaaf07c1bbc2aa081a54bdd66f0e152312">getline</a> (char **lineptr, size_t *n, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142222377084832"><a name="p142222377084832"></a><a name="p142222377084832"></a>ssize_t&nbsp;</p>
<p id="p1583485702084832"><a name="p1583485702084832"></a><a name="p1583485702084832"></a>Reads an entire line from a specified file stream. </p>
</td>
</tr>
<tr id="row2033411480084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087377276084832"><a name="p2087377276084832"></a><a name="p2087377276084832"></a><a href="IO.md#ga44dcf948b2c1dc3356d2937635a27839">tempnam</a> (const char *dir, const char *prefix)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p877387149084832"><a name="p877387149084832"></a><a name="p877387149084832"></a>char *&nbsp;</p>
<p id="p355920652084832"><a name="p355920652084832"></a><a name="p355920652084832"></a>Creates a temporary file with a unique file name. </p>
</td>
</tr>
<tr id="row1332508508084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2107228550084832"><a name="p2107228550084832"></a><a name="p2107228550084832"></a><a href="IO.md#ga53a57437279b4ed57b7f116dfc9cbbcc">setbuffer</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *f, char *buf, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1154327770084832"><a name="p1154327770084832"></a><a name="p1154327770084832"></a>void&nbsp;</p>
<p id="p491738165084832"><a name="p491738165084832"></a><a name="p491738165084832"></a>Sets the buffer for a specified file stream. </p>
</td>
</tr>
<tr id="row1862360130084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1254223426084832"><a name="p1254223426084832"></a><a name="p1254223426084832"></a><a href="IO.md#ga2e13e101d5a57cfccf1bab51f8768a5d">setlinebuf</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *f)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144726623084832"><a name="p2144726623084832"></a><a name="p2144726623084832"></a>void&nbsp;</p>
<p id="p405845501084832"><a name="p405845501084832"></a><a name="p405845501084832"></a>Sets the linear buffer for a specified file stream. </p>
</td>
</tr>
<tr id="row1751880757084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1893160494084832"><a name="p1893160494084832"></a><a name="p1893160494084832"></a><a href="IO.md#gab11a990e4f8863a1e7736e3c1d430092">fgetc</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2113018191084832"><a name="p2113018191084832"></a><a name="p2113018191084832"></a>int&nbsp;</p>
<p id="p1578013942084832"><a name="p1578013942084832"></a><a name="p1578013942084832"></a>Reads a character from the file pointed to by <strong id="b967526899084832"><a name="b967526899084832"></a><a name="b967526899084832"></a>stream</strong>. </p>
</td>
</tr>
<tr id="row405481400084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1766975489084832"><a name="p1766975489084832"></a><a name="p1766975489084832"></a><a href="IO.md#ga9b8e6d63482eb1fe38f3eb9d7fc9bd8e">fgetc_unlocked</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445097312084832"><a name="p1445097312084832"></a><a name="p1445097312084832"></a>int&nbsp;</p>
<p id="p1917345568084832"><a name="p1917345568084832"></a><a name="p1917345568084832"></a>Reads a character from the file pointed to by <strong id="b860562009084832"><a name="b860562009084832"></a><a name="b860562009084832"></a>stream</strong> with the thread remains unlocked. </p>
</td>
</tr>
<tr id="row923790161084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p259750598084832"><a name="p259750598084832"></a><a name="p259750598084832"></a><a href="IO.md#gab8680ff3f49f3fe7ce0fb78b4cb8394c">fputc_unlocked</a> (int c, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072721757084832"><a name="p2072721757084832"></a><a name="p2072721757084832"></a>int&nbsp;</p>
<p id="p1341878563084832"><a name="p1341878563084832"></a><a name="p1341878563084832"></a>Writes a character to the file stream pointed to by <strong id="b2139108257084832"><a name="b2139108257084832"></a><a name="b2139108257084832"></a>stream</strong> at the current position. </p>
</td>
</tr>
<tr id="row1992680347084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160201788084832"><a name="p160201788084832"></a><a name="p160201788084832"></a><a href="IO.md#ga089fd72e6218cf6805c8fc21123d3d5f">ferror_unlocked</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p707697959084832"><a name="p707697959084832"></a><a name="p707697959084832"></a>int&nbsp;</p>
<p id="p142247958084832"><a name="p142247958084832"></a><a name="p142247958084832"></a>Tests for the error identifier of a specified file stream. </p>
</td>
</tr>
<tr id="row1462190195084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291187459084832"><a name="p291187459084832"></a><a name="p291187459084832"></a><a href="IO.md#ga6d475ead5d1f35e3f14423a99ef3a992">getw</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535142236084832"><a name="p1535142236084832"></a><a name="p1535142236084832"></a>int&nbsp;</p>
<p id="p1055617115084832"><a name="p1055617115084832"></a><a name="p1055617115084832"></a>Reads a word (an int value) from a specified file stream. </p>
</td>
</tr>
<tr id="row939652816084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916758200084832"><a name="p1916758200084832"></a><a name="p1916758200084832"></a><a href="IO.md#gae3a2f96dac9fa87b964b69ff6d5cce46">putw</a> (int w, <a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p494605829084832"><a name="p494605829084832"></a><a name="p494605829084832"></a>int&nbsp;</p>
<p id="p285489016084832"><a name="p285489016084832"></a><a name="p285489016084832"></a>Writes a word (an int value) to a specified file stream. </p>
</td>
</tr>
<tr id="row1434508618084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1866476064084832"><a name="p1866476064084832"></a><a name="p1866476064084832"></a><a href="IO.md#ga8e6fe2fcd5eaa8e2d146a50eeaae5b40">fgetln</a> (<a href="IO.md#ga912af5ab9f8a52ddd387b7defc0b49f1">FILE</a> *stream, size_t *len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p482817747084832"><a name="p482817747084832"></a><a name="p482817747084832"></a>char *&nbsp;</p>
<p id="p1627031328084832"><a name="p1627031328084832"></a><a name="p1627031328084832"></a>Reads a line of data from the current position of a specified file stream. </p>
</td>
</tr>
<tr id="row1555649291084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1605257874084832"><a name="p1605257874084832"></a><a name="p1605257874084832"></a><a href="IO.md#ga1af9acc6b6efdca3576cb8223d95f401">asprintf</a> (char **strp, const char *fmt,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2067968604084832"><a name="p2067968604084832"></a><a name="p2067968604084832"></a>int&nbsp;</p>
<p id="p1574515860084832"><a name="p1574515860084832"></a><a name="p1574515860084832"></a>Prints formatted data to a specified character string. </p>
</td>
</tr>
<tr id="row122605514084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p447581542084832"><a name="p447581542084832"></a><a name="p447581542084832"></a><a href="IO.md#ga5ec7fd90ebe6015636bce974c192c86a">vasprintf</a> (char **strp, const char *fmt, va_list ap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620862330084832"><a name="p620862330084832"></a><a name="p620862330084832"></a>int&nbsp;</p>
<p id="p732625613084832"><a name="p732625613084832"></a><a name="p732625613084832"></a>Prints formatted data from a variable argument list to a specified character string. </p>
</td>
</tr>
</tbody>
</table>

