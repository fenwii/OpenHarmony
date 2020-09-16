# Setting up a Hi3516 Board Environment<a name="EN-US_TOPIC_0000001054501981"></a>

## Environment Requirements<a name="section179175261196"></a>

## Hardware<a name="section185788208272"></a>

-   Linux server
-   Windows workstation \(host computer\)
-   Hi3516DV300 IoT camera development board
-   USB cable and network cable \(The Windows workstation is connected to Hi3516DV300 development board through the USB cable and network cable.\)

[Figure 1](#fa54d47112b684c65b3dbf1779413545a)  shows the hardware connections.

**Figure  1**  Hardware connections<a name="fig19527104710591"></a>  
![](figures/hardware-connections-0.png "hardware-connections-0")

## Software<a name="section3343841379"></a>

**Table  1**  Platforms required for the Hi3516DV300 development board

<a name="tc50585b2b3fe43f7835154789b0e25af"></a>
<table><thead align="left"><tr id="ra9df6acc53154b819d5f86d885d994de"><th class="cellrowborder" valign="top" width="8.53%" id="mcps1.2.5.1.1"><p id="a999bb40532eb4f74a7383e1e776bb94a"><a name="a999bb40532eb4f74a7383e1e776bb94a"></a><a name="a999bb40532eb4f74a7383e1e776bb94a"></a>Hardware</p>
</th>
<th class="cellrowborder" valign="top" width="11.66%" id="mcps1.2.5.1.2"><p id="ae63cf791fbe348d3b907d20fc4927df8"><a name="ae63cf791fbe348d3b907d20fc4927df8"></a><a name="ae63cf791fbe348d3b907d20fc4927df8"></a>Software</p>
</th>
<th class="cellrowborder" valign="top" width="66%" id="mcps1.2.5.1.3"><p id="a54c4c80c43c84cb187342865a1d2b51e"><a name="a54c4c80c43c84cb187342865a1d2b51e"></a><a name="a54c4c80c43c84cb187342865a1d2b51e"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="13.81%" id="mcps1.2.5.1.4"><p id="a11e8d096fb204378a63d8805cd6d1f88"><a name="a11e8d096fb204378a63d8805cd6d1f88"></a><a name="a11e8d096fb204378a63d8805cd6d1f88"></a>Remarks</p>
</th>
</tr>
</thead>
<tbody><tr id="row117591159175819"><td class="cellrowborder" valign="top" width="8.53%" headers="mcps1.2.5.1.1 "><p id="a0c1290183f2548898dbfc516a4db2c4b"><a name="a0c1290183f2548898dbfc516a4db2c4b"></a><a name="a0c1290183f2548898dbfc516a4db2c4b"></a>Linux compile server</p>
</td>
<td class="cellrowborder" valign="top" width="11.66%" headers="mcps1.2.5.1.2 "><p id="a687efa8001f140488dc1da9a2ee8f6d1"><a name="a687efa8001f140488dc1da9a2ee8f6d1"></a><a name="a687efa8001f140488dc1da9a2ee8f6d1"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.5.1.3 "><p id="ace724e00c9094eccb8c600d6ad426ed8"><a name="ace724e00c9094eccb8c600d6ad426ed8"></a><a name="ace724e00c9094eccb8c600d6ad426ed8"></a>Ubuntu 16.04 64-bit or later is used for the Linux OS, and Bash is used for the shell.</p>
<div class="note" id="note124531828194919"><a name="note124531828194919"></a><a name="note124531828194919"></a><span class="notetitle"> NOTE: </span><div class="notebody"><p id="p1244243142810"><a name="p1244243142810"></a><a name="p1244243142810"></a>Common software such as samba and vim is installed in the OS by default. Adaptation is required to support Linux file sharing.</p>
</div></div>
</td>
<td class="cellrowborder" rowspan="3" valign="top" width="13.81%" headers="mcps1.2.5.1.4 "><p id="a4d0e2c8444484554ab58949ce322be32"><a name="a4d0e2c8444484554ab58949ce322be32"></a><a name="a4d0e2c8444484554ab58949ce322be32"></a>You can develop programs on the Windows workstation or on the Linux server through remote login.</p>
</td>
</tr>
<tr id="r85c4bf56ff3244e48db9d2f5b622b340"><td class="cellrowborder" rowspan="2" valign="top" headers="mcps1.2.5.1.1 "><p id="a8e99fd0262cb4489b70cf86c2144c294"><a name="a8e99fd0262cb4489b70cf86c2144c294"></a><a name="a8e99fd0262cb4489b70cf86c2144c294"></a>Windows workstation</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="a44d6164ce2e9421f9ade362f600c2815"><a name="a44d6164ce2e9421f9ade362f600c2815"></a><a name="a44d6164ce2e9421f9ade362f600c2815"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="a1c17349e334a44ada5c5f150457fe17d"><a name="a1c17349e334a44ada5c5f150457fe17d"></a><a name="a1c17349e334a44ada5c5f150457fe17d"></a>Windows XP/Windows7/Windows10</p>
</td>
</tr>
<tr id="r2c85a3b244764425b0d08fa20503da12"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="a70beb9d769e340018c9c39c7d44cf424"><a name="a70beb9d769e340018c9c39c7d44cf424"></a><a name="a70beb9d769e340018c9c39c7d44cf424"></a>USB-serial adapter driver</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p89891726111611"><a name="p89891726111611"></a><a name="p89891726111611"></a><a href="http://www.hihope.org/download" target="_blank" rel="noopener noreferrer">http://www.hihope.org/download</a></p>
<p id="p15657734141613"><a name="p15657734141613"></a><a name="p15657734141613"></a>USB-to-Serial Comm Port.exe</p>
</td>
</tr>
</tbody>
</table>

## Build Tools for Linux<a name="section20374218687"></a>

The following table describes the common tools required for Linux and how to obtain them.

**Table  2**  Development tools and obtaining methods

<a name="table6299192712513"></a>
<table><thead align="left"><tr id="row122993276512"><th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.1"><p id="p1829914271858"><a name="p1829914271858"></a><a name="p1829914271858"></a>Development Tool</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.2"><p id="p429918274517"><a name="p429918274517"></a><a name="p429918274517"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p12997271757"><a name="p12997271757"></a><a name="p12997271757"></a>How to Obtain</p>
</th>
</tr>
</thead>
<tbody><tr id="row430016273514"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p330015271158"><a name="p330015271158"></a><a name="p330015271158"></a>Python3.7+</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p43003270510"><a name="p43003270510"></a><a name="p43003270510"></a>Runs the compilation scripts.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p18254155164617"><a name="p18254155164617"></a><a name="p18254155164617"></a><a href="https://www.python.org/ftp/python/3.8.5/Python-3.8.5.tgz" target="_blank" rel="noopener noreferrer">https://www.python.org/ftp/python/3.8.5/Python-3.8.5.tgz</a></p>
</td>
</tr>
<tr id="row42668197206"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p426711912014"><a name="p426711912014"></a><a name="p426711912014"></a>bash</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p14267131962014"><a name="p14267131962014"></a><a name="p14267131962014"></a>Executes commands.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p14267101962014"><a name="p14267101962014"></a><a name="p14267101962014"></a>Internet</p>
</td>
</tr>
<tr id="row1711946154018"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p15588165684216"><a name="p15588165684216"></a><a name="p15588165684216"></a>gn</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p4588135634213"><a name="p4588135634213"></a><a name="p4588135634213"></a>Generates ninja compilation scripts.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p10572194318318"><a name="p10572194318318"></a><a name="p10572194318318"></a><a href="http://tools.harmonyos.com/mirrors/gn/1523/linux/gn.1523.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/gn/1523/linux/gn.1523.tar</a></p>
</td>
</tr>
<tr id="row16990164213404"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p1858825613428"><a name="p1858825613428"></a><a name="p1858825613428"></a>ninja</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p15844174611816"><a name="p15844174611816"></a><a name="p15844174611816"></a>Executes ninja compilation scripts.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p377581023312"><a name="p377581023312"></a><a name="p377581023312"></a><a href="http://tools.harmonyos.com/mirrors/ninja/1.9.0/linux/ninja.1.9.0.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/ninja/1.9.0/linux/ninja.1.9.0.tar</a></p>
</td>
</tr>
<tr id="row192161027104010"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p15217227174016"><a name="p15217227174016"></a><a name="p15217227174016"></a>LLVM</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p122171727184019"><a name="p122171727184019"></a><a name="p122171727184019"></a>Functions as the compiler toolchain.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p12127241115612"><a name="p12127241115612"></a><a name="p12127241115612"></a><a href="http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar</a></p>
</td>
</tr>
<tr id="row18516509507"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p14521650135017"><a name="p14521650135017"></a><a name="p14521650135017"></a>hc-gen</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p125255010501"><a name="p125255010501"></a><a name="p125255010501"></a>Configures and compiles files.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p4381131720413"><a name="p4381131720413"></a><a name="p4381131720413"></a><a href="http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar</a></p>
</td>
</tr>
<tr id="row105773499422"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p15300102717517"><a name="p15300102717517"></a><a name="p15300102717517"></a>IPOP, PuTTY, or other HyperTerminal software</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p109418530386"><a name="p109418530386"></a><a name="p109418530386"></a>Connects to the Linux server (choose one of the terminals).</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p7312122523813"><a name="p7312122523813"></a><a name="p7312122523813"></a>Internet (for example, <a href="https://www.putty.org/" target="_blank" rel="noopener noreferrer">https://www.putty.org/</a>)</p>
</td>
</tr>
</tbody>
</table>

## Development Tools for Windows<a name="section11161833102716"></a>

**Table  3**  Development tools for the Windows workstation

<a name="table1313323311274"></a>
<table><thead align="left"><tr id="row3133133312711"><th class="cellrowborder" valign="top" width="16.371637163716375%" id="mcps1.2.4.1.1"><p id="p16132203372716"><a name="p16132203372716"></a><a name="p16132203372716"></a>Development Tool</p>
</th>
<th class="cellrowborder" valign="top" width="50.29502950295029%" id="mcps1.2.4.1.2"><p id="p1413219339278"><a name="p1413219339278"></a><a name="p1413219339278"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p17133183312711"><a name="p17133183312711"></a><a name="p17133183312711"></a>How to Obtain</p>
</th>
</tr>
</thead>
<tbody><tr id="row13697410143219"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p163612016916"><a name="p163612016916"></a><a name="p163612016916"></a>Visual Studio Code</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p1563690791"><a name="p1563690791"></a><a name="p1563690791"></a>Edits codes.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p146361701097"><a name="p146361701097"></a><a name="p146361701097"></a><a href="https://code.visualstudio.com/" target="_blank" rel="noopener noreferrer">https://code.visualstudio.com/</a></p>
</td>
</tr>
<tr id="row12133123315277"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p613393317271"><a name="p613393317271"></a><a name="p613393317271"></a>HUAWEI DevEco Device Tool</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p10133193310276"><a name="p10133193310276"></a><a name="p10133193310276"></a>Functions as the integrated development environment (IDE) to provide code compilation, burning, and debugging. C and C++ languages are supported.</p>
<div class="note" id="note7133193392718"><a name="note7133193392718"></a><a name="note7133193392718"></a><span class="notetitle"> NOTE: </span><div class="notebody"><p id="p1133183310277"><a name="p1133183310277"></a><a name="p1133183310277"></a>HUAWEI DevEco Device Tool is a one-stop IDE provided by <span id="text4133533192719"><a name="text4133533192719"></a><a name="text4133533192719"></a>OpenHarmony</span> for smart device developers. You can customize <span id="text14536110256"><a name="text14536110256"></a><a name="text14536110256"></a>OpenHarmony</span> components on it as required, HUAWEI DevEco Device Tool is deployed on Visual Studio Code as a plug-in.</p>
</div></div>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p16788135433519"><a name="p16788135433519"></a><a name="p16788135433519"></a><a href="https://device.harmonyos.com/cn/ide" target="_blank" rel="noopener noreferrer">https://device.harmonyos.com/cn/ide</a></p>
</td>
</tr>
</tbody>
</table>

## Installing the Basic Compilation Environment<a name="section497484245614"></a>

## Connecting to a Linux Server<a name="section73731485127"></a>

Using PuTTY to log in to a Linux server from a PC running Windows

1.  Open  [PuTTY](https://www.putty.org/), enter the IP address of the Linux server, and click  **Open**.

    **Figure  2**  PuTTY configuration<a name="en-us_topic_0000001054781998_f825e6d7569cc487db9b744e454c7157a"></a>  
    ![](figures/putty-configuration.png "putty-configuration")

2.  Click  **Yes**  in the PuTTY  **Security Alert**  dialog box.
3.  Enter the account and password.

    **Figure  3**  Login<a name="en-us_topic_0000001054781998_fe1428afffbdd45f9b4a39497691ff5ff"></a>  
    ![](figures/login.png "login")

4.  The login is successful.

    **Figure  4**  Successful login<a name="en-us_topic_0000001054781998_f11bea69483e14bd39fef4a10b1ed1a3a"></a>  
    ![](figures/successful-login.png "successful-login")


## Changing Linux Shell to Bash<a name="section11741048173311"></a>

Run the following command to check whether bash is used as the shell:

```
ls -l /bin/sh
```

If  **/bin/sh -\> bash**  is not displayed, do as follows to change the shell to bash.

**Method 1:**  Run the following command on the device and then click  **No**.

```
sudo dpkg-reconfigure dash
```

**Method 2:**  Run the  **rm -rf /bin/sh**  command to delete sh and then run the sudo  **ln -s /bin/bash /bin/sh**  command to create a new soft link.

```
rm -rf /bin/sh
sudo ln -s /bin/bash /bin/sh
```

## Installing a Python Environment<a name="section16270312203916"></a>

1.  Start a Linux server.
2.  Run the  **python3 --version**  command to check the Python version. If the Python version is not 3.7 or later, do as follows to install an appropriate Python version, for example, Python 3.8:
    -   If the Ubuntu version is 18, run the  **sudo apt-get install python3.8**  command.
    -   If the Ubuntu version is 16, download the installation package and install Python.

        1. Run the following command to install Python environment dependencies \(gcc, g++, make, zlib, libffi\):

        "sudo apt-get install gcc && sudo apt-get install g++ && sudo apt-get install make && sudo apt-get install zlib\* && sudo apt-get install libffi-dev "

        2. Obtain  [Python 3.8.5 installation package](https://www.python.org/ftp/python/3.8.5/Python-3.8.5.tgz), save it to the Linux server, and run the following command to install it:

        "tar -xvzf Python-3.8.5.tgz && cd Python-3.8.5 && sudo ./configure && make && sudo make install"

        3. After Python-3.8.5 is installed, run  **which python3.8**  to display a path and link it to  **/usr/bin/python**. For example:

        "cd /usr/bin && rm python && ln -s /usr/local/bin/python3.8 python && python --version"


    -   Run the  **sudo apt-get install python3-setuptools python3-pip -y**  command to install the Python package management tool. \(The root/sudo permission is required.\) Run the  **sudo pip3 install --upgrade pip**  command to upgrade  **pip3**.

        Alternatively, install the Python package management tool as instructed by the official website. Specifically, run the  **curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py**  command to download the script  **get-pip.py**  and run the  **python get-pip.py**  command to install this script.


3.  Run the  **pip3 install setuptools**  command to install setuptools module of Python.
4.  Run the  **sudo pip3 install kconfiglib**  command to install  **GUI menuconfig**. The Kconfiglib 13.2.0 or later is recommended. \(The root/sudo permission is required.\)

    Alternatively, you can do as follows to install Kconfiglib 13.2.0 or later:

    1.  Download the .whl file, for example,  **kconfiglib-13.2.0-py2.py3-none-any.whl**, from  [https://pypi.org/project/kconfiglib\#files](https://pypi.org/project/kconfiglib#files).

    1.  Run the  **sudo pip3 install kconfiglib-xxx.whl**  command to install the .whl file, for example,  **sudo pip3 install kconfiglib-13.2.0-py2.py3-none-any.whl**\). \(The root/sudo permission is required.\)
    2.  If you encounter the error  **subprocess.CalledProcessError: Command '\('lsb\_release', '-a'\)' returned non-zero exit status 1.**, run the  **find / -name lsb\_release**  command, for example,  **rm -rf /usr/bin/lsb\_release**  to locate and delete it  **sb\_release**.


## Installing a File Packing Tool<a name="section755831544314"></a>

1.  Start a Linux server.
2.  Run  **mkfs.vfat**. If the command is not found, run  **sudo apt-get install dosfstools**.
3.  Run  **mcopy**. If the command is not found, run  **sudo apt-get install mtools**.

## Installing Compilation Tools<a name="section7227629152013"></a>

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>-   If you obtain the source code using an HPM component or HPM CLI tool, compilation tools like  **gn**,  **ninja**,  **LLVM**, and  **hc-gen**  are not required.
>-   \(Recommended\) If you obtain the source code through an image site or a code repository, compilation tools like  **gn**,  **ninja**,  **LLVM**, and  **hc-gen**  need to be installed.
>    When installing  **gn**,  **ninja**,  **LLVM**, and  **hc-gen**, ensure that the environment variable paths of the compilation tools are unique.

## Installing gn<a name="section1737610811213"></a>

1.  Start a Linux server.
2.  Download  [gn](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest).
3.  Decompress the  **gn**  installation package to the  **tar -xvf gn.1523.tar -C \~/**  in  **\~/gn**  directory.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/gn:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

## Installing ninjah<a name="section103777819124"></a>

1.  Start a Linux server.
2.  Download  [ninja](https://github.com/ninja-build/ninja/releases/download/v1.10.0/ninja-linux.zip).
3.  Decompress the  **ninja**  installation package to  **tar -xvf ninja.1.9.0.tar -C \~/**  in  **\~/ninja**  directory.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/ninja:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

## Installing the LLVM Toolchain<a name="section11613193644213"></a>

1.  Start a Linux server.
2.  Download  [http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar](http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar).
3.  Decompress the LLVM installation package to the  **\~/llvm**  path by running  **"tar -xvf llvm-linux-9.0.0-34042.tar -C \~/"**.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/llvm/bin:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

##  Installing hc-gen<a name="section139624410163"></a>

1.  Start a Linux server.
2.  Download  [http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar](http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar).
3.  Decompress the hc-gen installation package to the  **\~/hc-gen**  directory on the Linux server.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/hc-gen:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

