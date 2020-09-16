# Hi3861 Board Environment Setup<a name="EN-US_TOPIC_0000001054781998"></a>

## Environment Requirements<a name="section466851916410"></a>

## Hardware<a name="section07318322310"></a>

-   Linux server
-   Windows workstation \(Host computer\)
-   Hi3861 WLAN module
-   USB Type-C cable \(This cable connects Windows workstation and Hi3861 Wi-Fi module.\)

[Figure 1](#fa54d47112b684c65b3dbf1779413545a)  shows the hardware connections.

**Figure  1**  Hardware connections<a name="fig1625971115114"></a>  
![](figures/hardware-connections.png "hardware-connections")

## Software<a name="section182305581332"></a>

**Table  1**  Requirements on the development platform

<a name="tc50585b2b3fe43f7835154789b0e25af"></a>
<table><thead align="left"><tr id="ra9df6acc53154b819d5f86d885d994de"><th class="cellrowborder" valign="top" width="12.41%" id="mcps1.2.5.1.1"><p id="a999bb40532eb4f74a7383e1e776bb94a"><a name="a999bb40532eb4f74a7383e1e776bb94a"></a><a name="a999bb40532eb4f74a7383e1e776bb94a"></a>Hardware</p>
</th>
<th class="cellrowborder" valign="top" width="12.389999999999999%" id="mcps1.2.5.1.2"><p id="ae63cf791fbe348d3b907d20fc4927df8"><a name="ae63cf791fbe348d3b907d20fc4927df8"></a><a name="ae63cf791fbe348d3b907d20fc4927df8"></a>Software</p>
</th>
<th class="cellrowborder" valign="top" width="61.39%" id="mcps1.2.5.1.3"><p id="a54c4c80c43c84cb187342865a1d2b51e"><a name="a54c4c80c43c84cb187342865a1d2b51e"></a><a name="a54c4c80c43c84cb187342865a1d2b51e"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="13.81%" id="mcps1.2.5.1.4"><p id="a11e8d096fb204378a63d8805cd6d1f88"><a name="a11e8d096fb204378a63d8805cd6d1f88"></a><a name="a11e8d096fb204378a63d8805cd6d1f88"></a>Remarks</p>
</th>
</tr>
</thead>
<tbody><tr id="row117591159175819"><td class="cellrowborder" valign="top" width="12.41%" headers="mcps1.2.5.1.1 "><p id="a0c1290183f2548898dbfc516a4db2c4b"><a name="a0c1290183f2548898dbfc516a4db2c4b"></a><a name="a0c1290183f2548898dbfc516a4db2c4b"></a>Linux compile server</p>
</td>
<td class="cellrowborder" valign="top" width="12.389999999999999%" headers="mcps1.2.5.1.2 "><p id="a687efa8001f140488dc1da9a2ee8f6d1"><a name="a687efa8001f140488dc1da9a2ee8f6d1"></a><a name="a687efa8001f140488dc1da9a2ee8f6d1"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" width="61.39%" headers="mcps1.2.5.1.3 "><p id="ace724e00c9094eccb8c600d6ad426ed8"><a name="ace724e00c9094eccb8c600d6ad426ed8"></a><a name="ace724e00c9094eccb8c600d6ad426ed8"></a>Ubuntu 16.04 64-bit server or later (Use bash as the shell.)</p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="13.81%" headers="mcps1.2.5.1.4 "><p id="a4d0e2c8444484554ab58949ce322be32"><a name="a4d0e2c8444484554ab58949ce322be32"></a><a name="a4d0e2c8444484554ab58949ce322be32"></a>You can develop programs on the Windows workstation or on the Linux server via remote login.</p>
</td>
</tr>
<tr id="r85c4bf56ff3244e48db9d2f5b622b340"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="a8e99fd0262cb4489b70cf86c2144c294"><a name="a8e99fd0262cb4489b70cf86c2144c294"></a><a name="a8e99fd0262cb4489b70cf86c2144c294"></a>Windows workstation</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="a44d6164ce2e9421f9ade362f600c2815"><a name="a44d6164ce2e9421f9ade362f600c2815"></a><a name="a44d6164ce2e9421f9ade362f600c2815"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="a1c17349e334a44ada5c5f150457fe17d"><a name="a1c17349e334a44ada5c5f150457fe17d"></a><a name="a1c17349e334a44ada5c5f150457fe17d"></a>Windows XP/Windows7/Windows10</p>
</td>
</tr>
</tbody>
</table>

## Build Tools for Linux<a name="section20374218687"></a>

[Table 2](en-us_topic_0000001053782584.md#table6299192712513)  lists the obtaining channels and common tools required for Linux.

**Table  2**  Development tools and obtaining channels

<a name="table6299192712513"></a>
<table><thead align="left"><tr id="row122993276512"><th class="cellrowborder" valign="top" width="25.562556255625562%" id="mcps1.2.4.1.1"><p id="p1829914271858"><a name="p1829914271858"></a><a name="p1829914271858"></a>Development Tool</p>
</th>
<th class="cellrowborder" valign="top" width="41.1041104110411%" id="mcps1.2.4.1.2"><p id="p429918274517"><a name="p429918274517"></a><a name="p429918274517"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p12997271757"><a name="p12997271757"></a><a name="p12997271757"></a>Obtaining Channel</p>
</th>
</tr>
</thead>
<tbody><tr id="row1829915274517"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p1629902717511"><a name="p1629902717511"></a><a name="p1629902717511"></a>gcc_riscv32</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p1219863434519"><a name="p1219863434519"></a><a name="p1219863434519"></a>Cross compilation tool</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p7934105401914"><a name="p7934105401914"></a><a name="p7934105401914"></a><a href="hi3861-board-environment-setup.md">http://tools.harmonyos.com/mirrors/gcc_riscv32/7.3.0/linux/gcc_riscv32-linux-7.3.0.tar.gz</a></p>
</td>
</tr>
<tr id="row430016273514"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p330015271158"><a name="p330015271158"></a><a name="p330015271158"></a>Python3.7+</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p43003270510"><a name="p43003270510"></a><a name="p43003270510"></a>Executes script compilation.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p722419345151"><a name="p722419345151"></a><a name="p722419345151"></a>Public internet</p>
</td>
</tr>
<tr id="row1397335913612"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p097355911620"><a name="p097355911620"></a><a name="p097355911620"></a>SCons3.0.4+</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p1973195917619"><a name="p1973195917619"></a><a name="p1973195917619"></a>Compilation and build tool</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1722663441514"><a name="p1722663441514"></a><a name="p1722663441514"></a>Internet</p>
</td>
</tr>
<tr id="row42668197206"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p426711912014"><a name="p426711912014"></a><a name="p426711912014"></a>bash</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p14267131962014"><a name="p14267131962014"></a><a name="p14267131962014"></a>Command processor</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p14267101962014"><a name="p14267101962014"></a><a name="p14267101962014"></a>Internet</p>
</td>
</tr>
<tr id="row1463517494402"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p258814561424"><a name="p258814561424"></a><a name="p258814561424"></a>build-essential</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p1749611716181"><a name="p1749611716181"></a><a name="p1749611716181"></a>Packages on which compilation depends</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p8635174916403"><a name="p8635174916403"></a><a name="p8635174916403"></a>Internet</p>
</td>
</tr>
<tr id="row1711946154018"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p15588165684216"><a name="p15588165684216"></a><a name="p15588165684216"></a>gn</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p4588135634213"><a name="p4588135634213"></a><a name="p4588135634213"></a>Generates ninja files.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p12371418204"><a name="p12371418204"></a><a name="p12371418204"></a><a href="hi3861-board-environment-setup.md">http://tools.harmonyos.com/mirrors/gn/1523/linux/gn-linux-1523.tar</a></p>
</td>
</tr>
<tr id="row16990164213404"><td class="cellrowborder" valign="top" width="25.562556255625562%" headers="mcps1.2.4.1.1 "><p id="p1858825613428"><a name="p1858825613428"></a><a name="p1858825613428"></a>ninja</p>
</td>
<td class="cellrowborder" valign="top" width="41.1041104110411%" headers="mcps1.2.4.1.2 "><p id="p15844174611816"><a name="p15844174611816"></a><a name="p15844174611816"></a>Runs ninja files.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p19354152452012"><a name="p19354152452012"></a><a name="p19354152452012"></a><a href="hi3861-board-environment-setup.md">http://tools.harmonyos.com/mirrors/ninja/1.9.0/linux/ninja-linux-1.9.0.tar</a></p>
</td>
</tr>
</tbody>
</table>

## Development Tools for Windows<a name="section11161833102716"></a>

**Table  3**  Development tools and obtaining channels

<a name="table1313323311274"></a>
<table><thead align="left"><tr id="row3133133312711"><th class="cellrowborder" valign="top" width="16.371637163716375%" id="mcps1.2.4.1.1"><p id="p16132203372716"><a name="p16132203372716"></a><a name="p16132203372716"></a>Development tool</p>
</th>
<th class="cellrowborder" valign="top" width="50.29502950295029%" id="mcps1.2.4.1.2"><p id="p1413219339278"><a name="p1413219339278"></a><a name="p1413219339278"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p17133183312711"><a name="p17133183312711"></a><a name="p17133183312711"></a>Obtaining Channel</p>
</th>
</tr>
</thead>
<tbody><tr id="row138432533451"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p163612016916"><a name="p163612016916"></a><a name="p163612016916"></a>Visual Studio Code</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p1563690791"><a name="p1563690791"></a><a name="p1563690791"></a>A code editor</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p146361701097"><a name="p146361701097"></a><a name="p146361701097"></a><a href="https://code.visualstudio.com/" target="_blank" rel="noopener noreferrer">https://code.visualstudio.com/</a></p>
</td>
</tr>
<tr id="row12133123315277"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p613393317271"><a name="p613393317271"></a><a name="p613393317271"></a>HUAWEI DevEco Device Tool</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p10133193310276"><a name="p10133193310276"></a><a name="p10133193310276"></a>The integrated development environment (IDE) development tool is used to compile and burn the code of the Wi-Fi module.</p>
<div class="note" id="note7133193392718"><a name="note7133193392718"></a><a name="note7133193392718"></a><span class="notetitle"> NOTE: </span><div class="notebody"><p id="p1133183310277"><a name="p1133183310277"></a><a name="p1133183310277"></a>HUAWEI DevEco Device Tool is a one-stop integrated development environment for smart device developers. It supports on-demand component customization, code editing and compilation, and C/C++ languages. It is deployed on Visual Studio Code as a plug-in.</p>
</div></div>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p8313122172512"><a name="p8313122172512"></a><a name="p8313122172512"></a><a href="https://partnerdevicetest.devccsrnd.hwcloudtest.cn:3092/cn/ide" target="_blank" rel="noopener noreferrer">https://partnerdevicetest.devccsrnd.hwcloudtest.cn:3092/cn/ide</a></p>
</td>
</tr>
<tr id="row18342145821513"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p123421958131517"><a name="p123421958131517"></a><a name="p123421958131517"></a>IPOP, PuTTY, or other HyperTerminal</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p18342658131511"><a name="p18342658131511"></a><a name="p18342658131511"></a>A tool that remotely connects to the Linux compilation server and cmodule serial port</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p17342125851518"><a name="p17342125851518"></a><a name="p17342125851518"></a>Internet (for example, <a href="https://www.putty.org/" target="_blank" rel="noopener noreferrer">https://www.putty.org/</a>)</p>
</td>
</tr>
<tr id="row244884215147"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p1044974291416"><a name="p1044974291416"></a><a name="p1044974291416"></a>CH341SER.EXE</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p94491342131413"><a name="p94491342131413"></a><a name="p94491342131413"></a>USB-serial adapter driver</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p6449184214148"><a name="p6449184214148"></a><a name="p6449184214148"></a><a href="http://www.wch.cn/search?q=ch340g&amp;t=downloads" target="_blank" rel="noopener noreferrer">http://www.wch.cn/search?q=ch340g&amp;t=downloads</a></p>
</td>
</tr>
</tbody>
</table>

## Installing the basic compilation environment<a name="section497484245614"></a>

## connecting to the Linux server<a name="section15541530155711"></a>

Using PuTTY on Windows to log into Linux server

1.  Open  [puTTY](https://www.putty.org/), enter the IP address of the Linux server, and click  **Open**.

    **Figure  2**  PuTTY configuration page<a name="f825e6d7569cc487db9b744e454c7157a"></a>  
    ![](figures/putty-configuration-page.png "putty-configuration-page")

2.  Select  **Yes**  in the dialog displaying a security alert.

    **Figure  3**  PuTTY Security Alert dialog<a name="fc3ef6d32e0ee41bbaaaee0d41446ef18"></a>  
    ![](figures/putty-security-alert-dialog.png "putty-security-alert-dialog")

3.  Enter the account and password.

    **Figure  4**  Login page<a name="fe1428afffbdd45f9b4a39497691ff5ff"></a>  
    ![](figures/login-page.png "login-page")

4.  The login is successful.

    **Figure  5**  Successful login page<a name="f11bea69483e14bd39fef4a10b1ed1a3a"></a>  
    ![](figures/successful-login-page.png "successful-login-page")


## h2 Change Linux shell to bash.<a name="section182814544221"></a>

Run the following command on the terminal to check whether the shell is bash:

```
ls -l /bin/sh
```

如果为显示为/bin/sh -\> bash则为正常，否则请按以下方式修改：

**方法一**

在终端运行如下命令，然后选择 no。

```
sudo dpkg-reconfigure dash
```

**方法二**

Delete sh and run sh again.

```
rm -rf /bin/sh
sudo ln -s /bin/bash /bin/sh
```

## Installing the Python environment<a name="section126831816258"></a>

1.  Open the terminal of the Linux compilation server.
2.  Run the  **python3 --version**  command to check the Python version. Python 3.7 or later is required. Otherwise, perform the following steps \(Python 3.8 is used as an example\):
    -   If the Ubuntu version is 18, run the sudo apt-get install python3.8 command.
    -   If the Ubuntu version is 16, download the installation package and install Python.

        1. Run the following command to install the python dependency:

        Run sudo apt-get install gcc to install gcc.

        Install g++ and run sudo apt-get install g++.

        Run the sudo apt-get install make command to install make.

        Run the sudo apt-get install zlib\* command to install zlib.

        Install libffi and run "sudo apt-get install libffi-dev".

        2. Obtaining the python3.8.5 Installation Package

        3. Run the  **tar -xvzf Python-3.8.5.tgz**  command.

        4. Run the  **cd Python-3.8.5**  command.

        5. Run the  **sudo ./configure**  command.

        6. Run the  **make**  command.

        7. Run the  **sudo make install**  command.


    -   Run the sudo apt-get install python3-setuptools python3-pip -y command to install the Python package management tool. \(The root/sudo permission is required for the installation.\) Upgrade pip3 and run "sudo pip3 install --upgrade pip".

        Alternatively, install the Python package management tool as instructed by the official website. Download "curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py" and run python get-pip.py.


3.  Install  **setuptools**  by running the  **pip3 install setuptools**  command.
4.  Install GUI menuconfig by running the  **sudo pip3 install kconfiglib**  command. The Kconfiglib 13.2.0+ version is recommended. \(The root/sudo permission is required.\)

    You can also perform the following steps to install Kconfiglib 13.2.0+:

    1.  Download the .whl file \(for example, kconfiglib-13.2.0-py2.py3-none-any.whl\).

        Download path: https://pypi.org/project/kconfiglib\#files


    1.  Install the .whl file by running the  **sudo pip3 install kconfiglib-xxx.whl**  command \(for example,  **sudo pip3 install kconfiglib-13.2.0-py2.py3-none-any.whl**\). \(The root/sudo permission is required.\)
    2.  If an error of  **subprocess.CalledProcessError: Command '\('lsb\_release', '-a'\)' returned non-zero exit status 1.**  occurs, run the  **find / -name lsb\_release**  command, for example,  **rm -rf /usr/bin/lsb\_release**  to locate  **sb\_release**  and release it.

5.  Install pycryptodome by running the  **sudo pip3 install pycryptodome**  command or performing the following operations:

    >![](public_sys-resources/icon-note.gif) **NOTE:** 
    >-   Install the Python component packages on which the signature of the upgrade file depends, including pycryptodome, six, and ecdsa.
    >-   The ecdsa installation depends on six. Please install six before installing ecdsa.

    1.  Download the .whl file \(for example, pycryptodome-3.7.3-cp37-cp37m-manylinux1\_x86\_64.whl\).

        Download path:  [https://pypi.org/project/pycryptodome/\#files](https://pypi.org/project/pycryptodome/#files)


    1.  Install the .whl file by running the  **sudo pip3 install pycryptodome-xxx.whl**  command \(for example, sudo pip3 install pycryptodome-3.7.3-cp37-cp37m-manylinux1\_x86\_64.whl\).

    The message  **Successfully installed pycryptodome-3.7.3**  is displayed after the installation.

6.  Install  **six**  by running the  **sudo pip3 install six --upgrade --ignore-installed six**  command or performing the following operations:

    1.  Download the .whl file, for example, six-1.12.0-py2.py3-none-any.whl.

        Download path:  [https://pypi.org/project/six/\#files](https://pypi.org/project/six/#files)


    1.  Install the .whl file by running the  **sudo pip3 install six-xxx.whl**  command, for example,  **sudo pip3 install six-1.12.0-py2.py3-none-any.whl**. \(The root/sudo permission is required.\)

    After the installation, the message  **Successfully installed six-1.12.0**  is displayed.

7.  Install ecdsa by running the  **sudo pip3 install ecdsa**  command, or by doing as follows:

    1.  Download the .whl file, for example, ecdsa-0.14.1-py2.py3-none-any.whl.

        Download path:  [https://pypi.org/project/ecdsa/\#files](https://pypi.org/project/ecdsa/#files)


    1.  Install the .whl file by running the  **sudo pip3 install ecdsa-xxx.whl**  command, for example,  **sudo pip3 install ecdsa-0.14.1-py2.py3-none-any.whl**. \(The root/sudo permission is required for the installation.\)

    After the installation, the message  **Successfully installed ecdsa-0.14.1**  is displayed.


## Installing Scons<a name="section2462246562"></a>

1.  Open the Linux terminal.
2.  Install the SCons package by running the  **sudo apt-get install scons -y**  command. \(The root/sudo permission is required for the installation.\)

    Run the  **sudo apt-get install scons -y**  command. If the installation package cannot be found in the software source, do as follows:

    1.  Download the source code package from  [https://scons.org/pages/download.html](https://scons.org/pages/download.html). The recommended SCons version is 3.0.4+.
    2.  Decompress the source code package to any directory.
    3.  Enter the source code directory and run the  **sudo python3 setup.py install**  command to install the source code package. \(The root/sudo permission is required for the installation.\)

3.  Run the  **scons -v**  command to check whether the installation is successful. 

    **Figure  6**  Successful installation<a name="fig235815252492"></a>  
    ![](figures/successful-installation.png "successful-installation")


##  Installing  **gn**<a name="section2024354014506"></a>

1.  Open a Linux terminal.
2.  Download  [gn](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest).
3.  Decompress the tool package to the  **\~/gn**  directory on the Linux server.
4.  Set environment variables by running the  **vim /etc/profile**  command and add new variables by running the  **export PATH=\~/gn:$PATH**  command.
5.  Validate environment variables by running the  **source /etc/profile**  command.

## Installing  **ninjah**<a name="section182441140185010"></a>

1.  Open a Linux terminal.
2.  Download  [ninja](https://github.com/ninja-build/ninja/releases/download/v1.10.0/ninja-linux.zip).
3.  Decompress the tool package to the  **\~/ninja**  directory on the Linux server.
4.  Set environment variables by running the  **vim /etc/profile**  command and add new variables by running the  **PATH=\~/ninja:$PATH**  command.
5.  Validate environment variables by running the  **source /etc/profile**  command.

## Obtaining the Compilation Tool Chain of the WLAN Module<a name="section2014123416523"></a>

## Installing  **riscv gcc**  tool chain<a name="section0411311145415"></a>

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>The Hi3861 platform supports only the static link of the library when libgcc is running. You are not advised to use the dynamic link of the library when libgcc is running. Otherwise, GPL V3 will be polluted during commercial distribution.

1.  Open a Linux terminal.
2.  Download the gcc\_riscv32 compilation tool chain.

    Use the Huawei image cloud to download the gcc\_riscv32 binary compilation tool chain and decompress it to the /opt/gcc\_riscv32 directory on Linux.

3.  Decompress the package to the /opt/gcc\_riscv32 directory.
4.  Set the environment variable $vim /etc/profile and add $ export PATH=/opt/gcc\_riscv32/bin:$PATH.
5.  Validate environment variables by running the  **$source /etc/profile**  command.
6.  Check whether the installation is successful by entering  **$ riscv32-unknown-elf-gcc -v**  in the shell command line.

    If the compiler version number can be correctly displayed, the compiler is successfully installed.


