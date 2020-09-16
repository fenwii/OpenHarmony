# Shell命令开发指导<a name="ZH-CN_TOPIC_0000001052370293"></a>

## 开发指导<a name="section22071515161018"></a>

新增Shell命令的典型开发流程如下：

1.  包含如下头文件：

    ```
    #include "shell.h"
    #include "shcmd.h"
    ```

2.  注册命令。用户可以选择静态注册命令方式和系统运行时动态注册命令方式，静态注册命令方式一般用在系统常用命令注册，动态注册命令方式一般用在用户命令注册。

    1.  静态注册命令方式：

        1.  通过宏的方式注册。

            这个宏的原型为：

            SHELLCMD\_ENTRY\(l, cmdType, cmdKey, paraNum, cmdHook\)

            **表 1**  SHELLCMD\_ENTRY参数详解

            <a name="table1198543584513"></a>
            <table><thead align="left"><tr id="row209856358456"><th class="cellrowborder" valign="top" width="20.91%" id="mcps1.2.3.1.1"><p id="p998583517456"><a name="p998583517456"></a><a name="p998583517456"></a>参数</p>
            </th>
            <th class="cellrowborder" valign="top" width="79.09%" id="mcps1.2.3.1.2"><p id="p169851735174511"><a name="p169851735174511"></a><a name="p169851735174511"></a>描述</p>
            </th>
            </tr>
            </thead>
            <tbody><tr id="row13985153574517"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p6985113513452"><a name="p6985113513452"></a><a name="p6985113513452"></a>l</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p998573514457"><a name="p998573514457"></a><a name="p998573514457"></a>静态注册全局变量名（注意：不与系统中其他symbol重名）。</p>
            </td>
            </tr>
            <tr id="row398513594518"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p59856356450"><a name="p59856356450"></a><a name="p59856356450"></a>cmdType</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p119859355458"><a name="p119859355458"></a><a name="p119859355458"></a>命令类型：</p>
            <a name="ul11135144114816"></a><a name="ul11135144114816"></a><ul id="ul11135144114816"><li><p id="p21351144488"><a name="p21351144488"></a><a name="p21351144488"></a>CMD_TYPE_EX：不支持标准命令参数输入，会把用户填写的命令关键字屏蔽掉，例如：输入ls  /ramfs，传入给注册函数的参数只有/ramfs，而ls命令关键字并不会被传入。</p>
            </li><li><p id="p21353410482"><a name="p21353410482"></a><a name="p21353410482"></a>CMD_TYPE_STD：支持的标准命令参数输入，所有输入的字符都会通过命令解析后被传入。</p>
            </li></ul>
            </td>
            </tr>
            <tr id="row20985153524519"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p1098693510451"><a name="p1098693510451"></a><a name="p1098693510451"></a>cmdKey</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p11986735144514"><a name="p11986735144514"></a><a name="p11986735144514"></a>命令关键字，函数在Shell中访问的名称。</p>
            </td>
            </tr>
            <tr id="row1398683511450"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p598613359451"><a name="p598613359451"></a><a name="p598613359451"></a>paraNum</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p11986535144516"><a name="p11986535144516"></a><a name="p11986535144516"></a>调用的执行函数的入参最大个数，暂不支持。</p>
            </td>
            </tr>
            <tr id="row39861935154516"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p5986735114518"><a name="p5986735114518"></a><a name="p5986735114518"></a>cmdHook</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p398683574515"><a name="p398683574515"></a><a name="p398683574515"></a>命令执行函数地址，即命令实际执行函数。</p>
            </td>
            </tr>
            </tbody>
            </table>

            如：SHELLCMD\_ENTRY\(ls\_shellcmd,  CMD\_TYPE\_EX, "ls", XARGS,  \(CMD\_CBK\_FUNC\)osShellCmdLs\)

        2.  在build/mk/liteos\_tables\_ldflags.mk中添加相应选项：

            如：上述“ls”命令注册时，需在build/mk/liteos\_tables\_ldflags.mk中添加“-uls\_shellcmd”。其中-u后面跟SHELLCMD\_ENTRY的第一个参数。


    2.  动态注册命令方式：

        注册函数原型：

        UINT32 osCmdReg\(CmdT ype cmdType, CHAR \*cmdKey, UINT32 paraNum, CmdCallBackFunc cmdProc\)

        **表 2**  UINT32 osCmdReg参数详解

        <a name="table194461933114919"></a>
        <table><thead align="left"><tr id="row1644693318490"><th class="cellrowborder" valign="top" width="20.91%" id="mcps1.2.3.1.1"><p id="p1644618337493"><a name="p1644618337493"></a><a name="p1644618337493"></a>参数</p>
        </th>
        <th class="cellrowborder" valign="top" width="79.09%" id="mcps1.2.3.1.2"><p id="p444603317491"><a name="p444603317491"></a><a name="p444603317491"></a>描述</p>
        </th>
        </tr>
        </thead>
        <tbody><tr id="row844643374912"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p14446133319498"><a name="p14446133319498"></a><a name="p14446133319498"></a>cmdType</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p174461339496"><a name="p174461339496"></a><a name="p174461339496"></a>命令类型：</p>
        <a name="ul1244773317496"></a><a name="ul1244773317496"></a><ul id="ul1244773317496"><li><p id="p1844719331495"><a name="p1844719331495"></a><a name="p1844719331495"></a>CMD_TYPE_EX：不支持标准命令参数输入，会把用户填写的命令关键字屏蔽掉，例如：输入ls  /ramfs，传入给注册函数的参数只有/ramfs，而ls命令关键字并不会被传入。</p>
        </li><li><p id="p20447143315498"><a name="p20447143315498"></a><a name="p20447143315498"></a>CMD_TYPE_STD：支持的标准命令参数输入，所有输入的字符都会通过命令解析后被传入。</p>
        </li></ul>
        </td>
        </tr>
        <tr id="row14471733184915"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p744783319494"><a name="p744783319494"></a><a name="p744783319494"></a>cmdKey</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p18447833124914"><a name="p18447833124914"></a><a name="p18447833124914"></a>命令关键字，函数在Shell中访问的名称。</p>
        </td>
        </tr>
        <tr id="row17447143317495"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p174477331495"><a name="p174477331495"></a><a name="p174477331495"></a>paraNum</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p8447233184914"><a name="p8447233184914"></a><a name="p8447233184914"></a>调用的执行函数的入参最大个数，暂不支持该参数；当前为默认值XARGS(0xFFFFFFFF)。</p>
        </td>
        </tr>
        <tr id="row10447233174913"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p18447183334920"><a name="p18447183334920"></a><a name="p18447183334920"></a>cmdHook</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p44471533184912"><a name="p44471533184912"></a><a name="p44471533184912"></a>命令执行函数地址，即命令实际执行函数。</p>
        </td>
        </tr>
        </tbody>
        </table>

        如：osCmdReg\(CMD\_TYPE\_EX, "ls", XARGS,  \(CMD\_CBK\_FUNC\)osShellCmdLs\)


    >![](public_sys-resources/icon-note.gif) **说明：** 
    >命令关键字必须是唯一的，也即两个不同的命令项不能拥有相同的命令关键字，否则只会执行其中一个。
    >Shell在执行用户命令时，如果存在多个命令关键字相同的命令，只会执行其中在"help"命令中排序在最前面的一个。

3.  添加内置命令函数原型。

    UINT32 osShellCmdLs\(UINT32 argc,  CHAR \*\*argv\)

    **表 3**  osShellCmdLs参数说明

    <a name="table174451958105116"></a>
    <table><thead align="left"><tr id="row84451058105117"><th class="cellrowborder" valign="top" width="24.42%" id="mcps1.2.3.1.1"><p id="p1644515855111"><a name="p1644515855111"></a><a name="p1644515855111"></a>参数</p>
    </th>
    <th class="cellrowborder" valign="top" width="75.58%" id="mcps1.2.3.1.2"><p id="p18445145805113"><a name="p18445145805113"></a><a name="p18445145805113"></a>参数描述</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row194461458185112"><td class="cellrowborder" valign="top" width="24.42%" headers="mcps1.2.3.1.1 "><p id="p64461158145120"><a name="p64461158145120"></a><a name="p64461158145120"></a>argc</p>
    </td>
    <td class="cellrowborder" valign="top" width="75.58%" headers="mcps1.2.3.1.2 "><p id="p1844625885112"><a name="p1844625885112"></a><a name="p1844625885112"></a>Shell命令中，参数个数。</p>
    </td>
    </tr>
    <tr id="row144620587511"><td class="cellrowborder" valign="top" width="24.42%" headers="mcps1.2.3.1.1 "><p id="p244625811517"><a name="p244625811517"></a><a name="p244625811517"></a>argv</p>
    </td>
    <td class="cellrowborder" valign="top" width="75.58%" headers="mcps1.2.3.1.2 "><p id="p11446958105119"><a name="p11446958105119"></a><a name="p11446958105119"></a>为指针数组，每个元素指向一个字符串，可以根据选择命令类型，决定是否要把命令关键字传入给注册函数。</p>
    </td>
    </tr>
    </tbody>
    </table>

4.  输入Shell命令，有两种输入方式：
    -   在串口工具中直接输入Shell命令。

    -   在telnet工具中输入Shell命令（telnet使用方式详见[telnet](telnet.md)）。



