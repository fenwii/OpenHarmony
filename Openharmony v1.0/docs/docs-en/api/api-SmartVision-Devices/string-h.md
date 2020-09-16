# string.h<a name="EN-US_TOPIC_0000001054748013"></a>

## **Overview**<a name="section954002691084832"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Declares commonly used functions for string operations. 

You can use the functions provided in this file to perform the mathematical operations required during development. The operations include copying, searching for, locating, and appending a string, as well as comparing two strings. You must pay attention to memory management during function calls. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1744115961084832"></a>

## Macros<a name="define-members"></a>

<a name="table435406862084832"></a>
<table><thead align="left"><tr id="row2064291249084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p43772431084832"><a name="p43772431084832"></a><a name="p43772431084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p817427477084832"><a name="p817427477084832"></a><a name="p817427477084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row125001866084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1760992242084832"><a name="p1760992242084832"></a><a name="p1760992242084832"></a><a href="utils.md#ga6dfceaa174558eaee80a23cb09139dfd">strdupa</a>(x)   <a href="utils.md#ga7a82515b5d377be04817715c5465b647">strcpy</a>(alloca(<a href="utils.md#gaa383452fe445bfae989358c9d7d96f4f">strlen</a>(x)+1),x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p13297625084832"><a name="p13297625084832"></a><a name="p13297625084832"></a>Copies a string to a new position. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table900534181084832"></a>
<table><thead align="left"><tr id="row266851306084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p431922747084832"><a name="p431922747084832"></a><a name="p431922747084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1405887708084832"><a name="p1405887708084832"></a><a name="p1405887708084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1086094900084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039884616084832"><a name="p1039884616084832"></a><a name="p1039884616084832"></a><a href="utils.md#ga0ee37e291991bef6e3f4b49a970171e7">memcpy</a> (void *__restrict dest, const void *__restrict src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577959938084832"><a name="p577959938084832"></a><a name="p577959938084832"></a>void * </p>
<p id="p1532084046084832"><a name="p1532084046084832"></a><a name="p1532084046084832"></a>Copies a string (overlapping not allowed). </p>
</td>
</tr>
<tr id="row243566314084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408087178084832"><a name="p1408087178084832"></a><a name="p1408087178084832"></a><a href="utils.md#ga802c986820d3866639922b6bc9484f90">memmove</a> (void *dest, const void *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308399523084832"><a name="p308399523084832"></a><a name="p308399523084832"></a>void * </p>
<p id="p636583504084832"><a name="p636583504084832"></a><a name="p636583504084832"></a>Copies a string (overlapping allowed). </p>
</td>
</tr>
<tr id="row522184168084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1277697427084832"><a name="p1277697427084832"></a><a name="p1277697427084832"></a><a href="utils.md#gace6ee45c30e71865e6eb635200379db9">memset</a> (void *s, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1888566513084832"><a name="p1888566513084832"></a><a name="p1888566513084832"></a>void * </p>
<p id="p1726815995084832"><a name="p1726815995084832"></a><a name="p1726815995084832"></a>Copies a character to the specified memory area. </p>
</td>
</tr>
<tr id="row1153121489084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p836985448084832"><a name="p836985448084832"></a><a name="p836985448084832"></a><a href="utils.md#ga9e6df54ee04e18a3772335580e2ed872">memcmp</a> (const void *s1, const void *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305043998084832"><a name="p305043998084832"></a><a name="p305043998084832"></a>int </p>
<p id="p1455292695084832"><a name="p1455292695084832"></a><a name="p1455292695084832"></a>Compares two memory areas. </p>
</td>
</tr>
<tr id="row512024983084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1534030547084832"><a name="p1534030547084832"></a><a name="p1534030547084832"></a><a href="utils.md#ga16d6b0bd660cc3f9910924c6b6f4af8e">memchr</a> (const void *s, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1702400018084832"><a name="p1702400018084832"></a><a name="p1702400018084832"></a>void * </p>
<p id="p533284414084832"><a name="p533284414084832"></a><a name="p533284414084832"></a>Searches for a character in the specified memory area. </p>
</td>
</tr>
<tr id="row570301865084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p457806803084832"><a name="p457806803084832"></a><a name="p457806803084832"></a><a href="utils.md#ga7a82515b5d377be04817715c5465b647">strcpy</a> (char *dest, const char *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p244491856084832"><a name="p244491856084832"></a><a name="p244491856084832"></a>char * </p>
<p id="p595675820084832"><a name="p595675820084832"></a><a name="p595675820084832"></a>Copies a string. </p>
</td>
</tr>
<tr id="row1125504946084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1109093573084832"><a name="p1109093573084832"></a><a name="p1109093573084832"></a><a href="utils.md#ga47d54f24198df56da51078a6c540b9ed">strncpy</a> (char *dest, const char *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630777822084832"><a name="p1630777822084832"></a><a name="p1630777822084832"></a>char * </p>
<p id="p963385878084832"><a name="p963385878084832"></a><a name="p963385878084832"></a>Copies <strong id="b1169383028084832"><a name="b1169383028084832"></a><a name="b1169383028084832"></a>n</strong> characters of a string. </p>
</td>
</tr>
<tr id="row1951248245084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1834336426084832"><a name="p1834336426084832"></a><a name="p1834336426084832"></a><a href="utils.md#gadb8723e585ed29f2370cddf90f6891bc">strcat</a> (char *dest, const char *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1923330630084832"><a name="p1923330630084832"></a><a name="p1923330630084832"></a>char * </p>
<p id="p1500466902084832"><a name="p1500466902084832"></a><a name="p1500466902084832"></a>Appends a string to another one. </p>
</td>
</tr>
<tr id="row1772822592084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p15374762084832"><a name="p15374762084832"></a><a name="p15374762084832"></a><a href="utils.md#ga0aee928c2844a269966e4832fd2255c5">strncat</a> (char *dest, const char *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027059737084832"><a name="p1027059737084832"></a><a name="p1027059737084832"></a>char * </p>
<p id="p553248873084832"><a name="p553248873084832"></a><a name="p553248873084832"></a>Appends the first <strong id="b1503670549084832"><a name="b1503670549084832"></a><a name="b1503670549084832"></a>n</strong> bytes of a string to another one. </p>
</td>
</tr>
<tr id="row1999205716084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1844155800084832"><a name="p1844155800084832"></a><a name="p1844155800084832"></a><a href="utils.md#ga11bd144d7d44914099a3aeddf1c8567d">strcmp</a> (const char *s1, const char *s2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1984087152084832"><a name="p1984087152084832"></a><a name="p1984087152084832"></a>int </p>
<p id="p1518550880084832"><a name="p1518550880084832"></a><a name="p1518550880084832"></a>Compares two strings by characters. </p>
</td>
</tr>
<tr id="row590566638084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p285685836084832"><a name="p285685836084832"></a><a name="p285685836084832"></a><a href="utils.md#ga07f4a84c11c106e95c32b6ab509346ef">strncmp</a> (const char *s1, const char *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1644625507084832"><a name="p1644625507084832"></a><a name="p1644625507084832"></a>int </p>
<p id="p1833624408084832"><a name="p1833624408084832"></a><a name="p1833624408084832"></a>Compares the first n characters of two strings. </p>
</td>
</tr>
<tr id="row609867976084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p667545939084832"><a name="p667545939084832"></a><a name="p667545939084832"></a><a href="utils.md#gaa4718e50ed45c2275c5d85a121d68097">strcoll</a> (const char *s1, const char *s2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551529414084832"><a name="p551529414084832"></a><a name="p551529414084832"></a>int </p>
<p id="p1459873722084832"><a name="p1459873722084832"></a><a name="p1459873722084832"></a>Compares two strings by character for the program's current locale. </p>
</td>
</tr>
<tr id="row891680121084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804331564084832"><a name="p804331564084832"></a><a name="p804331564084832"></a><a href="utils.md#ga2294f2f1c4eaef870ef3d5d90e5cb36f">strcoll_l</a> (const char *s1, const char *s2, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368057523084832"><a name="p368057523084832"></a><a name="p368057523084832"></a>int </p>
<p id="p1398029512084832"><a name="p1398029512084832"></a><a name="p1398029512084832"></a>Compares two strings by character for the specified locale. </p>
</td>
</tr>
<tr id="row1404882066084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1112001428084832"><a name="p1112001428084832"></a><a name="p1112001428084832"></a><a href="utils.md#gadd1f1078b3303920c19fd68fcba3f908">strxfrm</a> (char *dest, const char *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1632716666084832"><a name="p1632716666084832"></a><a name="p1632716666084832"></a>size_t </p>
<p id="p1506144084084832"><a name="p1506144084084832"></a><a name="p1506144084084832"></a>Converts the first n characters of the source string pointed to by <strong id="b1390515925084832"><a name="b1390515925084832"></a><a name="b1390515925084832"></a>src</strong> based on the program's current locale specified by <a href="io.md#gaab9cf7b1a206fb75e5884934c8d676db">LC_COLLATE</a>, and places them in the destination string pointed to by <strong id="b1642470686084832"><a name="b1642470686084832"></a><a name="b1642470686084832"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row461937204084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p154451360084832"><a name="p154451360084832"></a><a name="p154451360084832"></a><a href="utils.md#ga12871ed234858ef0e363d2b8aa572fc1">strchr</a> (const char *s, int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p186716304084832"><a name="p186716304084832"></a><a name="p186716304084832"></a>char * </p>
<p id="p1615134773084832"><a name="p1615134773084832"></a><a name="p1615134773084832"></a>Locates the first occurrence of a character in a string. </p>
</td>
</tr>
<tr id="row168386494084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1365721096084832"><a name="p1365721096084832"></a><a name="p1365721096084832"></a><a href="utils.md#ga0c05a458deff028ef4d4e64059098db4">strrchr</a> (const char *s, int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1596528211084832"><a name="p1596528211084832"></a><a name="p1596528211084832"></a>char * </p>
<p id="p201685714084832"><a name="p201685714084832"></a><a name="p201685714084832"></a>Locates the last occurrence of a character in a string. </p>
</td>
</tr>
<tr id="row834051215084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p831042989084832"><a name="p831042989084832"></a><a name="p831042989084832"></a><a href="utils.md#gaeb6c449e5d77477c057abf00eaaf88fe">strcspn</a> (const char *s, const char *reject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700679071084832"><a name="p1700679071084832"></a><a name="p1700679071084832"></a>size_t </p>
<p id="p1911616614084832"><a name="p1911616614084832"></a><a name="p1911616614084832"></a>Obtains the length of the initial segment of a string that contains characters not in reject. </p>
</td>
</tr>
<tr id="row347204505084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472457996084832"><a name="p1472457996084832"></a><a name="p1472457996084832"></a><a href="utils.md#ga900a0edfa51f601d479244f7451cedd1">strspn</a> (const char *s, const char *<a href="net.md#ga0807af5ac9dfc2a63624e8c3e0ae95ef">accept</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1252356728084832"><a name="p1252356728084832"></a><a name="p1252356728084832"></a>size_t </p>
<p id="p1330081892084832"><a name="p1330081892084832"></a><a name="p1330081892084832"></a>Obtains the length of the initial segment of a string that contains characters in accept. </p>
</td>
</tr>
<tr id="row1041385977084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p65642890084832"><a name="p65642890084832"></a><a name="p65642890084832"></a><a href="utils.md#ga119f23a5dcb4eb5f1c1eed3cbf5cb0ed">strpbrk</a> (const char *s, const char *<a href="net.md#ga0807af5ac9dfc2a63624e8c3e0ae95ef">accept</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447746467084832"><a name="p447746467084832"></a><a name="p447746467084832"></a>char * </p>
<p id="p916419770084832"><a name="p916419770084832"></a><a name="p916419770084832"></a>Searches for any of a set of characters in a string. </p>
</td>
</tr>
<tr id="row351337084084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1402087061084832"><a name="p1402087061084832"></a><a name="p1402087061084832"></a><a href="utils.md#ga4a710d86541afc6b7dafddcdb4b1c94f">strstr</a> (const char *haystack, const char *needle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p196114591084832"><a name="p196114591084832"></a><a name="p196114591084832"></a>char * </p>
<p id="p1576848235084832"><a name="p1576848235084832"></a><a name="p1576848235084832"></a>Searches for a needle string in its haystack string. </p>
</td>
</tr>
<tr id="row2015876062084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p754060067084832"><a name="p754060067084832"></a><a name="p754060067084832"></a><a href="utils.md#ga8cb460f64c449f2a9b9b7a40569ce0fe">strtok</a> (char *str, const char *delim)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802213801084832"><a name="p1802213801084832"></a><a name="p1802213801084832"></a>char * </p>
<p id="p91658649084832"><a name="p91658649084832"></a><a name="p91658649084832"></a>Separates a string into a series of tokens separated by a delimiter. </p>
</td>
</tr>
<tr id="row355706792084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28346888084832"><a name="p28346888084832"></a><a name="p28346888084832"></a><a href="utils.md#gaa383452fe445bfae989358c9d7d96f4f">strlen</a> (const char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902750753084832"><a name="p1902750753084832"></a><a name="p1902750753084832"></a>size_t </p>
<p id="p1819518384084832"><a name="p1819518384084832"></a><a name="p1819518384084832"></a>Calculates the length of a string. </p>
</td>
</tr>
<tr id="row2083785207084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p762527325084832"><a name="p762527325084832"></a><a name="p762527325084832"></a><a href="utils.md#gadd46ab98f32b76457852dbb872842bf2">strerror</a> (int errnum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038625991084832"><a name="p1038625991084832"></a><a name="p1038625991084832"></a>char * </p>
<p id="p70609482084832"><a name="p70609482084832"></a><a name="p70609482084832"></a>Obtains an error description string of the specified error code. </p>
</td>
</tr>
<tr id="row1045416975084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1224725377084832"><a name="p1224725377084832"></a><a name="p1224725377084832"></a><a href="utils.md#gab11d86a2a3af0a355cad2337c6f4e9f7">strtok_r</a> (char *str, const char *delim, char **saveptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1509853830084832"><a name="p1509853830084832"></a><a name="p1509853830084832"></a>char * </p>
<p id="p1651518381084832"><a name="p1651518381084832"></a><a name="p1651518381084832"></a>Separates a string into a series of tokens separated by a delimiter, with the <strong id="b1204168448084832"><a name="b1204168448084832"></a><a name="b1204168448084832"></a>saveptr</strong> parameter specified. </p>
</td>
</tr>
<tr id="row131159730084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p128445819084832"><a name="p128445819084832"></a><a name="p128445819084832"></a><a href="utils.md#ga8f7507e357cbd24048ae77e27e5d41d7">strerror_l</a> (int errnum, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p907250144084832"><a name="p907250144084832"></a><a name="p907250144084832"></a>char * </p>
<p id="p1972356492084832"><a name="p1972356492084832"></a><a name="p1972356492084832"></a>Obtains an error description string of the specified error code for the specified locale. </p>
</td>
</tr>
<tr id="row472422121084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1264813788084832"><a name="p1264813788084832"></a><a name="p1264813788084832"></a><a href="utils.md#ga7253ba059153058c57952194237c6b55">strerror_r</a> (int errnum, char *buf, size_t buflen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217207591084832"><a name="p217207591084832"></a><a name="p217207591084832"></a>char * </p>
<p id="p394977477084832"><a name="p394977477084832"></a><a name="p394977477084832"></a>Obtains an error description string of the specified error code. </p>
</td>
</tr>
<tr id="row641871139084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p808875132084832"><a name="p808875132084832"></a><a name="p808875132084832"></a><a href="utils.md#ga890dbcd7c456828c1b6ff714e405fcc1">stpcpy</a> (char *dest, const char *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238002723084832"><a name="p238002723084832"></a><a name="p238002723084832"></a>char * </p>
<p id="p1776264703084832"><a name="p1776264703084832"></a><a name="p1776264703084832"></a>Copies a string. </p>
</td>
</tr>
<tr id="row859540045084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p209340994084832"><a name="p209340994084832"></a><a name="p209340994084832"></a><a href="utils.md#ga217a70a69e2fc7727278516b7ad2fc26">stpncpy</a> (char *dest, const char *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140674643084832"><a name="p140674643084832"></a><a name="p140674643084832"></a>char * </p>
<p id="p1364628092084832"><a name="p1364628092084832"></a><a name="p1364628092084832"></a>Copies n characters of a string. </p>
</td>
</tr>
<tr id="row145462078084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p399223964084832"><a name="p399223964084832"></a><a name="p399223964084832"></a><a href="utils.md#gafc92d2231e45d19988c7894aa2a07f0c">strnlen</a> (const char *s, size_t maxlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2081427846084832"><a name="p2081427846084832"></a><a name="p2081427846084832"></a>size_t </p>
<p id="p796945884084832"><a name="p796945884084832"></a><a name="p796945884084832"></a>Calculates the length of a string. </p>
</td>
</tr>
<tr id="row1990137645084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p562298579084832"><a name="p562298579084832"></a><a name="p562298579084832"></a><a href="utils.md#gab1cc1a3ff560049e22576031c7c2345b">strdup</a> (const char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p536579325084832"><a name="p536579325084832"></a><a name="p536579325084832"></a>char * </p>
<p id="p368028601084832"><a name="p368028601084832"></a><a name="p368028601084832"></a>Copies a string to a new position. </p>
</td>
</tr>
<tr id="row240737603084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p861615938084832"><a name="p861615938084832"></a><a name="p861615938084832"></a><a href="utils.md#ga8b860ba32fef12da8acd4507c059e509">strndup</a> (const char *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274878393084832"><a name="p1274878393084832"></a><a name="p1274878393084832"></a>char * </p>
<p id="p1230007521084832"><a name="p1230007521084832"></a><a name="p1230007521084832"></a>Copies n characters of a string to a new position. </p>
</td>
</tr>
<tr id="row1563632745084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1668233252084832"><a name="p1668233252084832"></a><a name="p1668233252084832"></a><a href="utils.md#ga8f7c22bf1131bd6ffe6635e386fb4ebd">strsignal</a> (int sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1840104384084832"><a name="p1840104384084832"></a><a name="p1840104384084832"></a>char * </p>
<p id="p871877367084832"><a name="p871877367084832"></a><a name="p871877367084832"></a>Returns a string describing the signal number. </p>
</td>
</tr>
<tr id="row612030256084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p517078556084832"><a name="p517078556084832"></a><a name="p517078556084832"></a><a href="utils.md#ga2ffbfe50042aaf5b987782dcd16ea1f0">memccpy</a> (void *__restrict dest, const void *__restrict src, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804908639084832"><a name="p804908639084832"></a><a name="p804908639084832"></a>void * </p>
<p id="p294630903084832"><a name="p294630903084832"></a><a name="p294630903084832"></a>Copies a memory area to another one. </p>
</td>
</tr>
<tr id="row1934651684084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727803469084832"><a name="p1727803469084832"></a><a name="p1727803469084832"></a><a href="utils.md#ga93c766c6e86f4f79e7507c21f1794e15">strsep</a> (char **stringp, const char *delim)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p598798726084832"><a name="p598798726084832"></a><a name="p598798726084832"></a>char * </p>
<p id="p1137229838084832"><a name="p1137229838084832"></a><a name="p1137229838084832"></a>Separates a string into a series of tokens separated by a delimiter. </p>
</td>
</tr>
<tr id="row21355044084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1042466404084832"><a name="p1042466404084832"></a><a name="p1042466404084832"></a><a href="utils.md#ga0266462615f2f112003cdb591710d299">strlcat</a> (char *d, const char *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720848803084832"><a name="p720848803084832"></a><a name="p720848803084832"></a>size_t </p>
<p id="p1227912849084832"><a name="p1227912849084832"></a><a name="p1227912849084832"></a>Appends the first <strong id="b807654321084832"><a name="b807654321084832"></a><a name="b807654321084832"></a>n</strong> bytes of a string to another one. </p>
</td>
</tr>
<tr id="row1365408070084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1666718893084832"><a name="p1666718893084832"></a><a name="p1666718893084832"></a><a href="utils.md#ga50bd3317d65f3da7d180b8981e58c5a4">strlcpy</a> (char *d, const char *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p818603115084832"><a name="p818603115084832"></a><a name="p818603115084832"></a>size_t </p>
<p id="p904325244084832"><a name="p904325244084832"></a><a name="p904325244084832"></a>Copies a string. </p>
</td>
</tr>
<tr id="row1806409977084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227890662084832"><a name="p1227890662084832"></a><a name="p1227890662084832"></a><a href="utils.md#ga1563a7059aabf95c0b588278e8bed575">strverscmp</a> (const char *s1, const char *s2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340244770084832"><a name="p340244770084832"></a><a name="p340244770084832"></a>int </p>
<p id="p364833704084832"><a name="p364833704084832"></a><a name="p364833704084832"></a>Compares strings of two versions (string 1 and string 2) and returns the comparison result. </p>
</td>
</tr>
<tr id="row1417080912084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p506927266084832"><a name="p506927266084832"></a><a name="p506927266084832"></a><a href="utils.md#gae9229017a4501f8d6a637b4498cfed2e">strcasestr</a> (const char *haystack, const char *needle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p962030099084832"><a name="p962030099084832"></a><a name="p962030099084832"></a>char * </p>
<p id="p2061322858084832"><a name="p2061322858084832"></a><a name="p2061322858084832"></a>Searches for a needle string in its haystack string and returns a pointer. </p>
</td>
</tr>
<tr id="row987061132084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p326380775084832"><a name="p326380775084832"></a><a name="p326380775084832"></a><a href="utils.md#ga5f6423417e952f934be0a582d87b663a">memmem</a> (const void *haystack, size_t haystacklen, const void *needle, size_t needlelen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700789581084832"><a name="p1700789581084832"></a><a name="p1700789581084832"></a>void * </p>
<p id="p1832552154084832"><a name="p1832552154084832"></a><a name="p1832552154084832"></a>Searches for a needle string in its haystack string. </p>
</td>
</tr>
<tr id="row596205462084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1284502306084832"><a name="p1284502306084832"></a><a name="p1284502306084832"></a><a href="utils.md#ga45623070e5e0b7008d44600a283ea2ee">memrchr</a> (const void *s, int c, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2145869494084832"><a name="p2145869494084832"></a><a name="p2145869494084832"></a>void * </p>
<p id="p1287001420084832"><a name="p1287001420084832"></a><a name="p1287001420084832"></a>Searches for a character in the specified memory area. </p>
</td>
</tr>
<tr id="row1756419144084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567753492084832"><a name="p1567753492084832"></a><a name="p1567753492084832"></a><a href="utils.md#ga7ac7c0f43132e3acf013e0c71a58cdc9">mempcpy</a> (void *dest, const void *src, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003457438084832"><a name="p2003457438084832"></a><a name="p2003457438084832"></a>void * </p>
<p id="p1192048765084832"><a name="p1192048765084832"></a><a name="p1192048765084832"></a>Copies a string (overlapping not allowed). </p>
</td>
</tr>
</tbody>
</table>

