# chmod<a name="ZH-CN_TOPIC_0000001052170278"></a>

## 命令功能<a name="section13992936121418"></a>

chmod用于修改文件操作权限。

## 命令格式<a name="section63342439147"></a>

chmod \[_mode_\] \[_pathname_\]

## 参数说明<a name="section894414671411"></a>

**表 1**  参数说明

<a name="table1049mcpsimp"></a>
<table><thead align="left"><tr id="row1055mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1057mcpsimp"><a name="p1057mcpsimp"></a><a name="p1057mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1059mcpsimp"><a name="p1059mcpsimp"></a><a name="p1059mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1061mcpsimp"><a name="p1061mcpsimp"></a><a name="p1061mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p13519122819294"><a name="p13519122819294"></a><a name="p13519122819294"></a>文件或文件夹权限，用8进制表示对应User、Group、及Other（拥有者、群组、其他组）的权限。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p182181026104214"><a name="p182181026104214"></a><a name="p182181026104214"></a>[0,777]</p>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>pathname</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4218826194210"><a name="p4218826194210"></a><a name="p4218826194210"></a>文件路径。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p13872195215290"><a name="p13872195215290"></a><a name="p13872195215290"></a>已存在的文件。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section182415221419"></a>

在需要修改的文件名前加上文件权限值就可以修改该文件的权限值。

## 使用实例<a name="section8518195718147"></a>

举例：chmod 666 hello-harmony.txt

## 输出说明<a name="section127391818158"></a>

**图 1**  修改 hello-harmony.txt 文件的权限为666<a name="fig501223144912"></a>  
![](figures/修改-hello-harmony-txt-文件的权限为666.png "修改-hello-harmony-txt-文件的权限为666")

