# chown<a name="ZH-CN_TOPIC_0000001052810292"></a>

## 命令功能<a name="section247414691513"></a>

chmod用于将指定文件的拥有者改为指定的用户或组。

## 命令格式<a name="section14773151018159"></a>

chown \[_owner_\] \[_group_\] \[_pathname_\]

## 参数说明<a name="section598731391517"></a>

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
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>owner</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p13519122819294"><a name="p13519122819294"></a><a name="p13519122819294"></a>文件拥有者。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p182181026104214"><a name="p182181026104214"></a><a name="p182181026104214"></a>[0,0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p68901524203516"><a name="p68901524203516"></a><a name="p68901524203516"></a>group</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1066mcpsimp"><a name="p1066mcpsimp"></a><a name="p1066mcpsimp"></a>文件群组。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p81831811183618"><a name="p81831811183618"></a><a name="p81831811183618"></a>1、为空。</p>
<p id="p1068mcpsimp"><a name="p1068mcpsimp"></a><a name="p1068mcpsimp"></a>2、[0,0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row10616101153510"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>pathname</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4218826194210"><a name="p4218826194210"></a><a name="p4218826194210"></a>文件路径。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p13872195215290"><a name="p13872195215290"></a><a name="p13872195215290"></a>已存在的文件。</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section16524152071510"></a>

-   在需要修改的文件名前加上文件拥有者和文件群组就可以分别修改该文件的拥有者和群组。
-   当owner或group值为-1时则表示对应的owner或group不修改。
-   group参数可以为空。

## 使用实例<a name="section17901152561510"></a>

举例：chown 100 200 hello-harmony.txt

## 输出说明<a name="section15513163115816"></a>

**图 1**  修改 hello-harmony.txt 文件的uid为100，gid为200<a name="fig518593394920"></a>  
![](figures/修改-hello-harmony-txt-文件的uid为100-gid为200.png "修改-hello-harmony-txt-文件的uid为100-gid为200")

