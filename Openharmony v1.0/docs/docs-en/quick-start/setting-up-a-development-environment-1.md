# Setting Up a Development Environment<a name="EN-US_TOPIC_0000001054022306"></a>

## Environment Requirements<a name="section1724111409282"></a>

## Hardware<a name="section185788208272"></a>

-   Linux server
-   Windows workstation \(host computer\)
-   Hi3518EV300 IoT camera development board
-   USB cable and network cable \(The Windows workstation is connected to Hi3518EV300 development board through the USB cable and network cable.\)

    [Figure 1](#fig8211468392)  shows the hardware connections.


**Figure  1**  Hardware connections<a name="fig8211468392"></a>  
![](figures/hardware-connections-1.png "hardware-connections-1")

## Software<a name="section383442213405"></a>

**Table  1**  Platforms required for the Hi3518EV300 development board

<a name="table16641975408"></a>
<table><thead align="left"><tr id="row196634713405"><th class="cellrowborder" valign="top" width="8.53%" id="mcps1.2.5.1.1"><p id="p116632718408"><a name="p116632718408"></a><a name="p116632718408"></a>Hardware</p>
</th>
<th class="cellrowborder" valign="top" width="11.66%" id="mcps1.2.5.1.2"><p id="p1766312724017"><a name="p1766312724017"></a><a name="p1766312724017"></a>Software</p>
</th>
<th class="cellrowborder" valign="top" width="66%" id="mcps1.2.5.1.3"><p id="p666327144010"><a name="p666327144010"></a><a name="p666327144010"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="13.81%" id="mcps1.2.5.1.4"><p id="p106631273406"><a name="p106631273406"></a><a name="p106631273406"></a>Remarks</p>
</th>
</tr>
</thead>
<tbody><tr id="row066315717402"><td class="cellrowborder" valign="top" width="8.53%" headers="mcps1.2.5.1.1 "><p id="p666318712403"><a name="p666318712403"></a><a name="p666318712403"></a>Linux compile server</p>
</td>
<td class="cellrowborder" valign="top" width="11.66%" headers="mcps1.2.5.1.2 "><p id="p76632712403"><a name="p76632712403"></a><a name="p76632712403"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.5.1.3 "><p id="p15663127204015"><a name="p15663127204015"></a><a name="p15663127204015"></a>Ubuntu 16.04 64-bit or later is used for the Linux OS, and bash is used as the shell.</p>
<div class="note" id="note196631578401"><a name="note196631578401"></a><a name="note196631578401"></a><span class="notetitle"> NOTE: </span><div class="notebody"><p id="p1466311720406"><a name="p1466311720406"></a><a name="p1466311720406"></a>Common software such as samba and vim is installed in the OS by default. Adaptation is required to support Linux file sharing.</p>
</div></div>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="13.81%" headers="mcps1.2.5.1.4 "><p id="p96631975404"><a name="p96631975404"></a><a name="p96631975404"></a>You can develop programs on the Windows workstation or on the Linux server through remote login.</p>
</td>
</tr>
<tr id="row19664272408"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1366314764011"><a name="p1366314764011"></a><a name="p1366314764011"></a>Windows workstation</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p15663177204019"><a name="p15663177204019"></a><a name="p15663177204019"></a>Operating system</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p1766411719408"><a name="p1766411719408"></a><a name="p1766411719408"></a>Windows XP/Windows7/Windows10</p>
</td>
</tr>
</tbody>
</table>

## Build Tools for Linux<a name="section11111412465"></a>

The following table describes the common tools required for Linux and how to obtain them.

**Table  2**  Development tools and obtaining methods

<a name="en-us_topic_0000001054501981_table6299192712513"></a>
<table><thead align="left"><tr id="en-us_topic_0000001054501981_row122993276512"><th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.1"><p id="en-us_topic_0000001054501981_p1829914271858"><a name="en-us_topic_0000001054501981_p1829914271858"></a><a name="en-us_topic_0000001054501981_p1829914271858"></a>Development Tool</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.2"><p id="en-us_topic_0000001054501981_p429918274517"><a name="en-us_topic_0000001054501981_p429918274517"></a><a name="en-us_topic_0000001054501981_p429918274517"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="en-us_topic_0000001054501981_p12997271757"><a name="en-us_topic_0000001054501981_p12997271757"></a><a name="en-us_topic_0000001054501981_p12997271757"></a>How to Obtain</p>
</th>
</tr>
</thead>
<tbody><tr id="en-us_topic_0000001054501981_row430016273514"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p330015271158"><a name="en-us_topic_0000001054501981_p330015271158"></a><a name="en-us_topic_0000001054501981_p330015271158"></a>Python3.7+</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p43003270510"><a name="en-us_topic_0000001054501981_p43003270510"></a><a name="en-us_topic_0000001054501981_p43003270510"></a>Runs the compilation scripts.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p18254155164617"><a name="en-us_topic_0000001054501981_p18254155164617"></a><a name="en-us_topic_0000001054501981_p18254155164617"></a><a href="https://www.python.org/ftp/python/3.8.5/Python-3.8.5.tgz" target="_blank" rel="noopener noreferrer">https://www.python.org/ftp/python/3.8.5/Python-3.8.5.tgz</a></p>
</td>
</tr>
<tr id="en-us_topic_0000001054501981_row42668197206"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p426711912014"><a name="en-us_topic_0000001054501981_p426711912014"></a><a name="en-us_topic_0000001054501981_p426711912014"></a>bash</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p14267131962014"><a name="en-us_topic_0000001054501981_p14267131962014"></a><a name="en-us_topic_0000001054501981_p14267131962014"></a>Executes commands.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p14267101962014"><a name="en-us_topic_0000001054501981_p14267101962014"></a><a name="en-us_topic_0000001054501981_p14267101962014"></a>Internet</p>
</td>
</tr>
<tr id="en-us_topic_0000001054501981_row1711946154018"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p15588165684216"><a name="en-us_topic_0000001054501981_p15588165684216"></a><a name="en-us_topic_0000001054501981_p15588165684216"></a>gn</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p4588135634213"><a name="en-us_topic_0000001054501981_p4588135634213"></a><a name="en-us_topic_0000001054501981_p4588135634213"></a>Generates ninja compilation scripts.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p10572194318318"><a name="en-us_topic_0000001054501981_p10572194318318"></a><a name="en-us_topic_0000001054501981_p10572194318318"></a><a href="http://tools.harmonyos.com/mirrors/gn/1523/linux/gn.1523.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/gn/1523/linux/gn.1523.tar</a></p>
</td>
</tr>
<tr id="en-us_topic_0000001054501981_row16990164213404"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p1858825613428"><a name="en-us_topic_0000001054501981_p1858825613428"></a><a name="en-us_topic_0000001054501981_p1858825613428"></a>ninja</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p15844174611816"><a name="en-us_topic_0000001054501981_p15844174611816"></a><a name="en-us_topic_0000001054501981_p15844174611816"></a>Executes ninja compilation scripts.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p377581023312"><a name="en-us_topic_0000001054501981_p377581023312"></a><a name="en-us_topic_0000001054501981_p377581023312"></a><a href="http://tools.harmonyos.com/mirrors/ninja/1.9.0/linux/ninja.1.9.0.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/ninja/1.9.0/linux/ninja.1.9.0.tar</a></p>
</td>
</tr>
<tr id="en-us_topic_0000001054501981_row192161027104010"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p15217227174016"><a name="en-us_topic_0000001054501981_p15217227174016"></a><a name="en-us_topic_0000001054501981_p15217227174016"></a>LLVM</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p122171727184019"><a name="en-us_topic_0000001054501981_p122171727184019"></a><a name="en-us_topic_0000001054501981_p122171727184019"></a>Functions as the compiler toolchain.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p12127241115612"><a name="en-us_topic_0000001054501981_p12127241115612"></a><a name="en-us_topic_0000001054501981_p12127241115612"></a><a href="http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar</a></p>
</td>
</tr>
<tr id="en-us_topic_0000001054501981_row18516509507"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p14521650135017"><a name="en-us_topic_0000001054501981_p14521650135017"></a><a name="en-us_topic_0000001054501981_p14521650135017"></a>hc-gen</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p125255010501"><a name="en-us_topic_0000001054501981_p125255010501"></a><a name="en-us_topic_0000001054501981_p125255010501"></a>Configures and compiles files.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p4381131720413"><a name="en-us_topic_0000001054501981_p4381131720413"></a><a name="en-us_topic_0000001054501981_p4381131720413"></a><a href="http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar" target="_blank" rel="noopener noreferrer">http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar</a></p>
</td>
</tr>
<tr id="en-us_topic_0000001054501981_row105773499422"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="en-us_topic_0000001054501981_p15300102717517"><a name="en-us_topic_0000001054501981_p15300102717517"></a><a name="en-us_topic_0000001054501981_p15300102717517"></a>IPOP, PuTTY, or other HyperTerminal software</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="en-us_topic_0000001054501981_p109418530386"><a name="en-us_topic_0000001054501981_p109418530386"></a><a name="en-us_topic_0000001054501981_p109418530386"></a>Connects to the Linux server (choose one of the terminals).</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="en-us_topic_0000001054501981_p7312122523813"><a name="en-us_topic_0000001054501981_p7312122523813"></a><a name="en-us_topic_0000001054501981_p7312122523813"></a>Internet (for example, <a href="https://www.putty.org/" target="_blank" rel="noopener noreferrer">https://www.putty.org/</a>)</p>
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
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p1563690791"><a name="p1563690791"></a><a name="p1563690791"></a>Edits code.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p146361701097"><a name="p146361701097"></a><a name="p146361701097"></a><a href="https://code.visualstudio.com/" target="_blank" rel="noopener noreferrer">https://code.visualstudio.com/</a></p>
</td>
</tr>
<tr id="row12133123315277"><td class="cellrowborder" valign="top" width="16.371637163716375%" headers="mcps1.2.4.1.1 "><p id="p613393317271"><a name="p613393317271"></a><a name="p613393317271"></a>HiTool</p>
</td>
<td class="cellrowborder" valign="top" width="50.29502950295029%" headers="mcps1.2.4.1.2 "><p id="p201334121092"><a name="p201334121092"></a><a name="p201334121092"></a>Burns the images and the U-Boot.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p108615410278"><a name="p108615410278"></a><a name="p108615410278"></a><a href="http://www.hihope.org/download" target="_blank" rel="noopener noreferrer">http://www.hihope.org/download</a></p>
</td>
</tr>
</tbody>
</table>

## Installing the Basic Compilation Environment<a name="section7813043104310"></a>

## Connecting to a Linux Server<a name="section111021456154718"></a>

Using PuTTY to log in to a Linux server from a PC running Windows

1.  Open  [PuTTY](https://www.putty.org/), enter the IP address of the Linux server, and click  **Open**.

    **Figure  2**  PuTTY configuration<a name="en-us_topic_0000001054501981_en-us_topic_0000001054781998_f825e6d7569cc487db9b744e454c7157a"></a>  
    ![](figures/putty-configuration.png "putty-configuration")

2.  Click  **Yes**  in the PuTTY  **Security Alert**  dialog box.
3.  Enter the account and password.

    **Figure  3**  Login<a name="en-us_topic_0000001054501981_en-us_topic_0000001054781998_fe1428afffbdd45f9b4a39497691ff5ff"></a>  
    ![](figures/login.png "login")

4.  The login is successful.

    **Figure  4**  Successful login<a name="en-us_topic_0000001054501981_en-us_topic_0000001054781998_f11bea69483e14bd39fef4a10b1ed1a3a"></a>  
    ![](figures/successful-login.png "successful-login")


## Changing Linux Shell to Bash<a name="section980212574810"></a>

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

## Installing a Python Environment<a name="section918195118487"></a>

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


## Installing a File Packing Tool<a name="section145881557185214"></a>

1.  Start a Linux server.
2.  Run  **mkfs.vfat**. If the command is not found, run  **sudo apt-get install dosfstools**.
3.  Run  **mcopy**. If the command is not found, run  **sudo apt-get install mtools**.

## Installing Compilation Tools<a name="section7227629152013"></a>

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>-   If you obtain the source code using an HPM component or HPM CLI tool, compilation tools like  **gn**,  **ninja**,  **LLVM**, and  **hc-gen**  are not required.
>-   \(Recommended\) If you obtain the source code through an image site or a code repository, compilation tools like  **gn**,  **ninja**,  **LLVM**, and  **hc-gen**  need to be installed.
>    When installing  **gn**,  **ninja**,  **LLVM**, and  **hc-gen**, ensure that the environment variable paths of the compilation tools are unique.

## Installing gn<a name="section119641436125219"></a>

1.  Start a Linux server.
2.  Download  [gn](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest).
3.  Decompress the  **gn**  installation package to the  **tar -xvf gn.1523.tar -C \~/**  in  **\~/gn**  directory.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/gn:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

## Installing ninjah<a name="section96781928145213"></a>

1.  Start a Linux server.
2.  Download  [ninja](https://github.com/ninja-build/ninja/releases/download/v1.10.0/ninja-linux.zip).
3.  Decompress the  **ninja**  installation package to  **tar -xvf ninja.1.9.0.tar -C \~/**  in  **\~/ninja**  directory.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/ninja:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

## Installing the LLVM Toolchain<a name="section667822819521"></a>

1.  Start a Linux server.
2.  Download  [http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar](http://tools.harmonyos.com/mirrors/clang/9.0.0-34042/linux/llvm-linux-9.0.0-34042.tar).
3.  Decompress the LLVM installation package to the  **\~/llvm**  path by running  **"tar -xvf llvm-linux-9.0.0-34042.tar -C \~/"**.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/llvm/bin:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

##  Installing hc-gen<a name="section201517625210"></a>

1.  Start a Linux server.
2.  Download  [http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar](http://tools.harmonyos.com/mirrors/hc-gen/0.65/linux/hc-gen-0.65-linux.tar).
3.  Decompress the hc-gen installation package to the  **\~/hc-gen**  directory on the Linux server.
4.  Open the  **\~/.bashrc**  file in Vim and add a line of  **export PATH=\~/hc-gen:$PATH**  to set an environment variable.
5.  Run  **source \~/.bashrc**  to validate the environment variable.

