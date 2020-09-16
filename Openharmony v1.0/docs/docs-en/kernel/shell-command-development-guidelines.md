# Shell Command Development Guidelines<a name="EN-US_TOPIC_0000001052370293"></a>

## Development Guidelines<a name="section22071515161018"></a>

You can perform the following operations to add shell commands:

1.  Include the following header files:

    ```
    #include "shell.h"
    #include "shcmd.h"
    ```

2.  Register commands. You can register commands either statically or dynamically when the system is running. In most cases, static registration is widely used by common system commands, and dynamic registration is widely used by user commands.

    1.  Static registration:

        1.  Register a command using a macro.

            The prototype of the macro is as follows:

            SHELLCMD\_ENTRY\(l, cmdType, cmdKey, paraNum, cmdHook\)

            **Table  1**  Parameters of the SHELLCMD\_ENTRY macro

            <a name="table1198543584513"></a>
            <table><thead align="left"><tr id="row209856358456"><th class="cellrowborder" valign="top" width="20.91%" id="mcps1.2.3.1.1"><p id="p998583517456"><a name="p998583517456"></a><a name="p998583517456"></a><strong id="b1195317394217"><a name="b1195317394217"></a><a name="b1195317394217"></a>Parameter</strong></p>
            </th>
            <th class="cellrowborder" valign="top" width="79.09%" id="mcps1.2.3.1.2"><p id="p169851735174511"><a name="p169851735174511"></a><a name="p169851735174511"></a><strong id="b1958216251314"><a name="b1958216251314"></a><a name="b1958216251314"></a>Description</strong></p>
            </th>
            </tr>
            </thead>
            <tbody><tr id="row13985153574517"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p6985113513452"><a name="p6985113513452"></a><a name="p6985113513452"></a>l</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p998573514457"><a name="p998573514457"></a><a name="p998573514457"></a>Indicates the global variable name to be passed during the static registration. Note that the name cannot be the same as other symbol names in the system.</p>
            </td>
            </tr>
            <tr id="row398513594518"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p59856356450"><a name="p59856356450"></a><a name="p59856356450"></a>cmdType</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p119859355458"><a name="p119859355458"></a><a name="p119859355458"></a>Indicates the command type.</p>
            <a name="ul11135144114816"></a><a name="ul11135144114816"></a><ul id="ul11135144114816"><li><p id="p21351144488"><a name="p21351144488"></a><a name="p21351144488"></a><strong id="b189416548121"><a name="b189416548121"></a><a name="b189416548121"></a>CMD_TYPE_EX</strong>: does not support standard command parameters and will mask the command keywords you entered. For example, if you enter <strong id="b1940315357339"><a name="b1940315357339"></a><a name="b1940315357339"></a>ls /ramfs</strong>, only <strong id="b67371541123316"><a name="b67371541123316"></a><a name="b67371541123316"></a>/ramfs</strong> will be passed to the registration function, and the <strong id="b1145320313411"><a name="b1145320313411"></a><a name="b1145320313411"></a>ls</strong> command keyword will be masked.</p>
            </li><li><p id="p21353410482"><a name="p21353410482"></a><a name="p21353410482"></a><strong id="b15922145203418"><a name="b15922145203418"></a><a name="b15922145203418"></a>CMD_TYPE_STD</strong>: supports standard command parameters. All the characters you entered will be passed to the registration function after being parsed.</p>
            </li></ul>
            </td>
            </tr>
            <tr id="row20985153524519"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p1098693510451"><a name="p1098693510451"></a><a name="p1098693510451"></a>cmdKey</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p11986735144514"><a name="p11986735144514"></a><a name="p11986735144514"></a>Indicates the command keyword, which is the name used to access a shell function.</p>
            </td>
            </tr>
            <tr id="row1398683511450"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p598613359451"><a name="p598613359451"></a><a name="p598613359451"></a>paraNum</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p11986535144516"><a name="p11986535144516"></a><a name="p11986535144516"></a>Indicates the maximum number of input parameters in the execution function to be invoked. This parameter is not supported currently.</p>
            </td>
            </tr>
            <tr id="row39861935154516"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p5986735114518"><a name="p5986735114518"></a><a name="p5986735114518"></a>cmdHook</p>
            </td>
            <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p398683574515"><a name="p398683574515"></a><a name="p398683574515"></a>Indicates the address of the execution function, that is, the function that is actually executed by the command.</p>
            </td>
            </tr>
            </tbody>
            </table>

            Example: SHELLCMD\_ENTRY\(ls\_shellcmd, CMD\_TYPE\_EX, "ls", XARGS, \(CMD\_CBK\_FUNC\)osShellCmdLs\)

        2.  Add the required options to the  **build/mk/liteos\_tables\_ldflags.mk**  file.

            For example, when registering the  **ls**  command, add  **-uls\_shellcmd**  to the  **build/mk/liteos\_tables\_ldflags.mk**  file.  **-u**  is followed by the first parameter of  **SHELLCMD\_ENTRY**.


    2.  Dynamic registration:

        The prototype of the function to register is as follows:

        UINT32 osCmdReg\(CmdT ype cmdType, CHAR \*cmdKey, UINT32 paraNum, CmdCallBackFunc cmdProc\)

        **Table  2**  Parameters of UINT32 osCmdReg

        <a name="table194461933114919"></a>
        <table><thead align="left"><tr id="row1644693318490"><th class="cellrowborder" valign="top" width="20.91%" id="mcps1.2.3.1.1"><p id="p1644618337493"><a name="p1644618337493"></a><a name="p1644618337493"></a><strong id="b414914114815"><a name="b414914114815"></a><a name="b414914114815"></a>Parameter</strong></p>
        </th>
        <th class="cellrowborder" valign="top" width="79.09%" id="mcps1.2.3.1.2"><p id="p444603317491"><a name="p444603317491"></a><a name="p444603317491"></a><strong id="b19862274819"><a name="b19862274819"></a><a name="b19862274819"></a>Description</strong></p>
        </th>
        </tr>
        </thead>
        <tbody><tr id="row844643374912"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p14446133319498"><a name="p14446133319498"></a><a name="p14446133319498"></a>cmdType</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p174461339496"><a name="p174461339496"></a><a name="p174461339496"></a>Indicates the command type.</p>
        <a name="ul1244773317496"></a><a name="ul1244773317496"></a><ul id="ul1244773317496"><li><p id="p1844719331495"><a name="p1844719331495"></a><a name="p1844719331495"></a><strong id="b611520734815"><a name="b611520734815"></a><a name="b611520734815"></a>CMD_TYPE_EX</strong>: does not support standard command parameters and will mask the command keywords you entered. For example, if you enter <strong id="b1812019754812"><a name="b1812019754812"></a><a name="b1812019754812"></a>ls /ramfs</strong>, only <strong id="b11200734815"><a name="b11200734815"></a><a name="b11200734815"></a>/ramfs</strong> will be passed to the registration function, and the <strong id="b11121177144815"><a name="b11121177144815"></a><a name="b11121177144815"></a>ls</strong> command keyword will be masked.</p>
        </li><li><p id="p20447143315498"><a name="p20447143315498"></a><a name="p20447143315498"></a><strong id="b1672116964815"><a name="b1672116964815"></a><a name="b1672116964815"></a>CMD_TYPE_STD</strong>: supports standard command parameters. All the characters you entered will be passed to the registration function after being parsed.</p>
        </li></ul>
        </td>
        </tr>
        <tr id="row14471733184915"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p744783319494"><a name="p744783319494"></a><a name="p744783319494"></a>cmdKey</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p18447833124914"><a name="p18447833124914"></a><a name="p18447833124914"></a>Indicates the command keyword, which is the name used to access a shell function.</p>
        </td>
        </tr>
        <tr id="row17447143317495"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p174477331495"><a name="p174477331495"></a><a name="p174477331495"></a>paraNum</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p8447233184914"><a name="p8447233184914"></a><a name="p8447233184914"></a>Indicates the maximum number of input parameters in the execution function to be invoked. This parameter is not supported currently. The default value is <strong id="b1425195414484"><a name="b1425195414484"></a><a name="b1425195414484"></a>XARGS(0xFFFFFFFF)</strong>.</p>
        </td>
        </tr>
        <tr id="row10447233174913"><td class="cellrowborder" valign="top" width="20.91%" headers="mcps1.2.3.1.1 "><p id="p18447183334920"><a name="p18447183334920"></a><a name="p18447183334920"></a>cmdHook</p>
        </td>
        <td class="cellrowborder" valign="top" width="79.09%" headers="mcps1.2.3.1.2 "><p id="p44471533184912"><a name="p44471533184912"></a><a name="p44471533184912"></a>Indicates the address of the execution function, that is, the function that is actually executed by the command.</p>
        </td>
        </tr>
        </tbody>
        </table>

        Example: osCmdReg\(CMD\_TYPE\_EX, "ls", XARGS,  \(CMD\_CBK\_FUNC\)osShellCmdLs\)


    >![](public_sys-resources/icon-note.gif) **NOTE:** 
    >The command keyword must be unique. Specifically, two different commands cannot share the same command keyword. Otherwise, only one command is executed.
    >When executing user commands sharing the same keyword, the shell executes only the first command in the  **help**  commands.

3.  Use the following function prototype to add built-in commands:

    UINT32 osShellCmdLs\(UINT32 argc,  CHAR \*\*argv\)

    **Table  3**  Parameters of osShellCmdLs

    <a name="table174451958105116"></a>
    <table><thead align="left"><tr id="row84451058105117"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1644515855111"><a name="p1644515855111"></a><a name="p1644515855111"></a><strong id="b710871813012"><a name="b710871813012"></a><a name="b710871813012"></a>Parameter</strong></p>
    </th>
    <th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p18445145805113"><a name="p18445145805113"></a><a name="p18445145805113"></a><strong id="b12608195015"><a name="b12608195015"></a><a name="b12608195015"></a>Description</strong></p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row194461458185112"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p64461158145120"><a name="p64461158145120"></a><a name="p64461158145120"></a>argc</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1844625885112"><a name="p1844625885112"></a><a name="p1844625885112"></a>Indicates the number of parameters in the shell command.</p>
    </td>
    </tr>
    <tr id="row144620587511"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p244625811517"><a name="p244625811517"></a><a name="p244625811517"></a>argv</p>
    </td>
    <td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p11446958105119"><a name="p11446958105119"></a><a name="p11446958105119"></a>Indicates a pointer array, where each element points to a string. You can determine whether to pass the command keyword to the registration function by specifying the command type.</p>
    </td>
    </tr>
    </tbody>
    </table>

4.  Enter the shell command in either of the following methods:
    -   Enter the shell command in the serial port tool.

    -   Enter the shell command in the Telnet tool. For details, see  [telnet](telnet.md).



