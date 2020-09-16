# exec<a name="EN-US_TOPIC_0000001053502450"></a>

## Command Function<a name="section4643204919313"></a>

This command is a built-in shell command used to execute user-space programs.

## Syntax<a name="section6553153635"></a>

exec <_executable-file_\>

## Parameter Description<a name="section208971157532"></a>

**Table  1**  Parameters

<a name="table3900mcpsimp"></a>
<table><thead align="left"><tr id="row3906mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p3908mcpsimp"><a name="p3908mcpsimp"></a><a name="p3908mcpsimp"></a><strong id="b15824121217379"><a name="b15824121217379"></a><a name="b15824121217379"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p3910mcpsimp"><a name="p3910mcpsimp"></a><a name="p3910mcpsimp"></a><strong id="b58922014133710"><a name="b58922014133710"></a><a name="b58922014133710"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p3912mcpsimp"><a name="p3912mcpsimp"></a><a name="p3912mcpsimp"></a><strong id="b9819413295"><a name="b9819413295"></a><a name="b9819413295"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row3913mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3915mcpsimp"><a name="p3915mcpsimp"></a><a name="p3915mcpsimp"></a>executable-file</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3917mcpsimp"><a name="p3917mcpsimp"></a><a name="p3917mcpsimp"></a>Indicates a valid executable file.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3919mcpsimp"><a name="p3919mcpsimp"></a><a name="p3919mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section213115219413"></a>

Currently, this command supports only valid binary programs. The programs are successfully executed and then run in the background by default. However, the programs share the same device with the shell. As a result, the output of the programs and the shell may be interlaced.

## Example<a name="section13736564418"></a>

Enter  **exec helloworld**.

## Output<a name="section194005101413"></a>

```
OHOS # exec helloworld
OHOS # hello world!
```

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>After the executable file is executed, prompt  **OHOS \#**  is printed first. The shell  **exec**  command is executed in the background, causing the prompt to be printed in advance.

