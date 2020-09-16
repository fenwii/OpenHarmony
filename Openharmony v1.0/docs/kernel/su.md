# su<a name="ZH-CN_TOPIC_0000001052451605"></a>

## 命令功能<a name="section297810431676"></a>

su用于变更为其他使用者的身份。

## 命令格式<a name="section157131147876"></a>

su \[_uid_\] \[_gid_\]

## 参数说明<a name="section04145521671"></a>

**表 1**  参数说明

<a name="table1049mcpsimp"></a>
<table><thead align="left"><tr id="row1055mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1057mcpsimp"><a name="p1057mcpsimp"></a><a name="p1057mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="51.93%" id="mcps1.2.4.1.2"><p id="p1059mcpsimp"><a name="p1059mcpsimp"></a><a name="p1059mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27.07%" id="mcps1.2.4.1.3"><p id="p1061mcpsimp"><a name="p1061mcpsimp"></a><a name="p1061mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>uid</p>
</td>
<td class="cellrowborder" valign="top" width="51.93%" headers="mcps1.2.4.1.2 "><p id="p14138191243"><a name="p14138191243"></a><a name="p14138191243"></a>目标用户的用户id值。</p>
</td>
<td class="cellrowborder" valign="top" width="27.07%" headers="mcps1.2.4.1.3 "><a name="ul14151675449"></a><a name="ul14151675449"></a><ul id="ul14151675449"><li>为空。</li><li>[0,60000]</li></ul>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>gid</p>
</td>
<td class="cellrowborder" valign="top" width="51.93%" headers="mcps1.2.4.1.2 "><p id="p48748461789"><a name="p48748461789"></a><a name="p48748461789"></a>目标用户的群组id值。</p>
</td>
<td class="cellrowborder" valign="top" width="27.07%" headers="mcps1.2.4.1.3 "><a name="ul10433713134417"></a><a name="ul10433713134417"></a><ul id="ul10433713134417"><li>为空。</li><li>[0,60000]</li></ul>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section14615155610719"></a>

-   su命令缺省切换到root用户，uid默认为0，gid为0。
-   在su命令后的输入参数uid和gid就可以切换到该uid和gid的用户。
-   输入参数超出范围时，会打印提醒输入正确范围参数。

## 使用实例<a name="section13338150985"></a>

举例：su 1000 1000

## 输出说明<a name="section125021924194613"></a>

**图 1** **切换到**为uid为1000，gid为1000的用户<a name="fig666918538448"></a>  
![](figures/切换到为uid为1000-gid为1000的用户.png "切换到为uid为1000-gid为1000的用户")

