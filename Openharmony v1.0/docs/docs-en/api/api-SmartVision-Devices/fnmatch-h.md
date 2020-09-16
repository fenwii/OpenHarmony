# fnmatch.h<a name="EN-US_TOPIC_0000001055108021"></a>

## **Overview**<a name="section150884713084829"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Provides a function for checking whether a specified string matches a string that contains wildcards. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1156606769084829"></a>

## Macros<a name="define-members"></a>

<a name="table235159658084829"></a>
<table><thead align="left"><tr id="row187155154084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1637536501084829"><a name="p1637536501084829"></a><a name="p1637536501084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1740979412084829"><a name="p1740979412084829"></a><a name="p1740979412084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1189712835084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577550522084829"><a name="p577550522084829"></a><a name="p577550522084829"></a><a href="utils.md#gaed9e649990b20ba86e1aa7cacdc1bafe">FNM_PATHNAME</a>   0x1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021930789084829"><a name="p1021930789084829"></a><a name="p1021930789084829"></a>If this flag is set, a slash (/) in <strong id="b1748742106084829"><a name="b1748742106084829"></a><a name="b1748742106084829"></a>string</strong> can be matched by a slash (/) in <strong id="b59771910084829"><a name="b59771910084829"></a><a name="b59771910084829"></a>pattern</strong>, but not by an asterisk (*), or a question mark (?), or a bracket expression ([]) containing a slash. </p>
</td>
</tr>
<tr id="row2144341311084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271019780084829"><a name="p1271019780084829"></a><a name="p1271019780084829"></a><a href="utils.md#ga0c050a8a7551c2ca86560396de3d20d0">FNM_NOESCAPE</a>   0x2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1276258791084829"><a name="p1276258791084829"></a><a name="p1276258791084829"></a>If this flag is set, the backslash () is treated as an ordinary character, instead of an escape character. </p>
</td>
</tr>
<tr id="row498862936084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p769877616084829"><a name="p769877616084829"></a><a name="p769877616084829"></a><a href="utils.md#gaab98fecc02c06d6379bfcf416d6d297e">FNM_PERIOD</a>   0x4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1776358903084829"><a name="p1776358903084829"></a><a name="p1776358903084829"></a>If this flag is set, a leading period (.) in <strong id="b1901157562084829"><a name="b1901157562084829"></a><a name="b1901157562084829"></a>string</strong> can be exactly matched by the period (.) in <strong id="b141464124084829"><a name="b141464124084829"></a><a name="b141464124084829"></a>pattern</strong>. A period is considered to be leading if it is the first character in <strong id="b1844390131084829"><a name="b1844390131084829"></a><a name="b1844390131084829"></a>string</strong>, or if both <strong id="b976431874084829"><a name="b976431874084829"></a><a name="b976431874084829"></a>FNM_PATHNAME</strong> is set and the period immediately follows a slash. </p>
</td>
</tr>
<tr id="row1871468549084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p456965966084829"><a name="p456965966084829"></a><a name="p456965966084829"></a><a href="utils.md#ga94f8f78b6d024e35c971dd3ec057140c">FNM_LEADING_DIR</a>   0x8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53981998084829"><a name="p53981998084829"></a><a name="p53981998084829"></a>If this flag is set, a trailing sequence of characters starting with a slash (/) is ignored in <strong id="b1604687949084829"><a name="b1604687949084829"></a><a name="b1604687949084829"></a>string</strong>. For example, if this flag is set, either <strong id="b309467140084829"><a name="b309467140084829"></a><a name="b309467140084829"></a>foo*</strong> or <strong id="b1551497998084829"><a name="b1551497998084829"></a><a name="b1551497998084829"></a>foobar</strong> as a pattern would match the string <strong id="b711181615084829"><a name="b711181615084829"></a><a name="b711181615084829"></a>foobar/frobozz</strong>. </p>
</td>
</tr>
<tr id="row226620211084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p265281042084829"><a name="p265281042084829"></a><a name="p265281042084829"></a><a href="utils.md#gad41e3158a654dd4dfdab19d97745698a">FNM_CASEFOLD</a>   0x10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159560345084829"><a name="p159560345084829"></a><a name="p159560345084829"></a>If this flag is set, the pattern is matched case-insensitively. </p>
</td>
</tr>
<tr id="row2052181462084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p503050771084829"><a name="p503050771084829"></a><a name="p503050771084829"></a><a href="utils.md#gad4df04c067e436af77a11440afbded0f">FNM_FILE_NAME</a>   <a href="utils.md#gaed9e649990b20ba86e1aa7cacdc1bafe">FNM_PATHNAME</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1318112668084829"><a name="p1318112668084829"></a><a name="p1318112668084829"></a>The definition is similar to that of <a href="utils.md#gaed9e649990b20ba86e1aa7cacdc1bafe">FNM_PATHNAME</a>. </p>
</td>
</tr>
<tr id="row866266836084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726654356084829"><a name="p726654356084829"></a><a name="p726654356084829"></a><a href="utils.md#gaf2661230e0cfc9970d6cdbe01571e753">FNM_NOMATCH</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1534490002084829"><a name="p1534490002084829"></a><a name="p1534490002084829"></a>The <strong id="b1215972103084829"><a name="b1215972103084829"></a><a name="b1215972103084829"></a>string</strong> parameter does not match the <strong id="b1856182398084829"><a name="b1856182398084829"></a><a name="b1856182398084829"></a>pattern</strong> parameter. </p>
</td>
</tr>
<tr id="row228479500084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1469699378084829"><a name="p1469699378084829"></a><a name="p1469699378084829"></a><a href="utils.md#gabf296e95251824c90803dd3aa374190d">FNM_NOSYS</a>   (-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p918648797084829"><a name="p918648797084829"></a><a name="p918648797084829"></a>The function does not support the operation. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table949833720084829"></a>
<table><thead align="left"><tr id="row1263551450084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1618728875084829"><a name="p1618728875084829"></a><a name="p1618728875084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p630564643084829"><a name="p630564643084829"></a><a name="p630564643084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1816298026084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271252037084829"><a name="p271252037084829"></a><a name="p271252037084829"></a><a href="utils.md#ga088b414f40eb0ce3dad9e5243816f68f">fnmatch</a> (const char *pattern, const char *string, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p236650904084829"><a name="p236650904084829"></a><a name="p236650904084829"></a>int </p>
<p id="p1627564960084829"><a name="p1627564960084829"></a><a name="p1627564960084829"></a>Matches a file name or a path name. </p>
</td>
</tr>
</tbody>
</table>

