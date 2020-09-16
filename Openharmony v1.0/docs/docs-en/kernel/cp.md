# cp<a name="EN-US_TOPIC_0000001052451607"></a>

## Command Function<a name="section6841203041513"></a>

This command is used to create a copy for a file.

## Syntax<a name="section24286359150"></a>

cp \[_SOURCEFILE_\] \[_DESTFILE_\]

## Parameter Description<a name="section558617385152"></a>

**Table  1**  Parameters

<a name="table1130mcpsimp"></a>
<table><thead align="left"><tr id="row1136mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1138mcpsimp"><a name="p1138mcpsimp"></a><a name="p1138mcpsimp"></a><strong id="b203611832412"><a name="b203611832412"></a><a name="b203611832412"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1140mcpsimp"><a name="p1140mcpsimp"></a><a name="p1140mcpsimp"></a><strong id="b1170512342014"><a name="b1170512342014"></a><a name="b1170512342014"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1142mcpsimp"><a name="p1142mcpsimp"></a><a name="p1142mcpsimp"></a><strong id="b173835351418"><a name="b173835351418"></a><a name="b173835351418"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1143mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1145mcpsimp"><a name="p1145mcpsimp"></a><a name="p1145mcpsimp"></a>SOURCEFILE</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1147mcpsimp"><a name="p1147mcpsimp"></a><a name="p1147mcpsimp"></a>Indicates the path to the source file.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1149mcpsimp"><a name="p1149mcpsimp"></a><a name="p1149mcpsimp"></a>Currently, only files are supported. Directories are not supported.</p>
</td>
</tr>
<tr id="row1150mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1152mcpsimp"><a name="p1152mcpsimp"></a><a name="p1152mcpsimp"></a>DESTFILE</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1154mcpsimp"><a name="p1154mcpsimp"></a><a name="p1154mcpsimp"></a>Indicates the path to the destination file.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1156mcpsimp"><a name="p1156mcpsimp"></a><a name="p1156mcpsimp"></a>Both directories and files are supported.</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section16128156162"></a>

-   The name of the source file cannot be the same as that of the destination file in the same path.
-   The source file must exist and cannot be a directory.
-   The source file path supports wildcards: asterisks \(\*\) and question marks \(?\). The asterisk \(\*\) indicates any number of characters, and the question mark \(?\) represents a single character. The destination file path does not support wildcards. If the specified source file path matches multiple files, the destination file path must be a directory.
-   If the destination file path is a directory, this directory must exist. In this case, the destination file is named after the source file.
-   If the destination file path is a file, the directory for this file must exist. In this case, the file copy is renamed.
-   Currently, this command can be used to copy only one file. If more than two parameters are specified, only the first two parameters take effect.
-   If the destination file does not exist, a new file is created. If the destination file already exists, the existing file is overwritten.

When important system resources are copied, unexpected results such as a system breakdown may occur. For example, when the  **/dev/uartdev-0**  file is copied, the system may stop responding.

## Example<a name="section19354171211618"></a>

Enter  **cp hello-harmony.txt ./tmp/**.

## Output<a name="section16754183195914"></a>

**Figure  1**  File copying result<a name="fig184025115493"></a>  
![](figures/file-copying-result.png "file-copying-result")

