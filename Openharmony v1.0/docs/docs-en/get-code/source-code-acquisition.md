# Source Code Acquisition<a name="EN-US_TOPIC_0000001050769927"></a>

## About OpenHarmony<a name="section6370143622110"></a>

OpenHarmony is an open-source version of HarmonyOS. It is donated by Huawei to OpenAtom Foundation. The first open-source version can run on 128 KB to 128 MB devices. You are welcomed to join the open-source community for continuous improvement.

Access code repositories at  [https://openharmony.gitee.com](https://openharmony.gitee.com).

## Overview of Source Code Acquisition<a name="section12763342204"></a>

This document describes how to acquire OpenHarmony source code and provides its directory structure. The OpenHarmony code is open to you as  [bundles](../bundles/overview-0.md), which can be obtained in any of the following ways:

-   **Method 1 \(recommended\)**: Download compressed files from an image site.
-   **Method 2**: Visit the HarmonyOS Package Manager \([HPM](https://hpm.harmonyos.com/#/en/home)\) platform, search for your desired solution, select or exclude bundles from the solution, and download it.
-   **Method 3**: Use an hpm-cli tool available on the  [HPM](https://hpm.harmonyos.com/#/en/home)  platform, and run related HPM commands to download your desired code.
-   **Method 4**: Use the  **repo**  or  **git**  tool to download your desired code from the code repository.

## Method 1: Acquiring Source Code from Image Sites<a name="section61172538310"></a>

You can download the source code or the corresponding solutions from the image library at the sites listed below.

**Table  1**  Acquiring source code from image sites

<a name="table9930153132517"></a>
<table><thead align="left"><tr id="row5928133152512"><th class="cellrowborder" valign="top" width="25%" id="mcps1.2.5.1.1"><p id="p1792803142518"><a name="p1792803142518"></a><a name="p1792803142518"></a>Content</p>
</th>
<th class="cellrowborder" valign="top" width="16.14%" id="mcps1.2.5.1.2"><p id="p0928738254"><a name="p0928738254"></a><a name="p0928738254"></a>Version Information</p>
</th>
<th class="cellrowborder" valign="top" width="24.759999999999998%" id="mcps1.2.5.1.3"><p id="p39281035251"><a name="p39281035251"></a><a name="p39281035251"></a>Site</p>
</th>
<th class="cellrowborder" valign="top" width="34.1%" id="mcps1.2.5.1.4"><p id="p292819322511"><a name="p292819322511"></a><a name="p292819322511"></a>SHA-256 Verification Code</p>
</th>
</tr>
</thead>
<tbody><tr id="row492963182513"><td class="cellrowborder" valign="top" width="25%" headers="mcps1.2.5.1.1 "><p id="p69292322516"><a name="p69292322516"></a><a name="p69292322516"></a><span id="text958012347463"><a name="text958012347463"></a><a name="text958012347463"></a>OpenHarmony</span> full code base</p>
</td>
<td class="cellrowborder" valign="top" width="16.14%" headers="mcps1.2.5.1.2 "><p id="p79291938252"><a name="p79291938252"></a><a name="p79291938252"></a>1.0</p>
</td>
<td class="cellrowborder" valign="top" width="24.759999999999998%" headers="mcps1.2.5.1.3 "><p id="p10929236258"><a name="p10929236258"></a><a name="p10929236258"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/code-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 1</a>, <a href="https://mirrors.huaweicloud.com/harmonyos/os/1.0/code-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 2</a></p>
</td>
<td class="cellrowborder" valign="top" width="34.1%" headers="mcps1.2.5.1.4 "><p id="p992993202517"><a name="p992993202517"></a><a name="p992993202517"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/code-1.0.tar.gz.sha256" target="_blank" rel="noopener noreferrer">SHA-256 Verification Code</a></p>
</td>
</tr>
<tr id="row6929934252"><td class="cellrowborder" valign="top" width="25%" headers="mcps1.2.5.1.1 "><p id="p0929163132512"><a name="p0929163132512"></a><a name="p0929163132512"></a>Hi3861 solutions</p>
</td>
<td class="cellrowborder" valign="top" width="16.14%" headers="mcps1.2.5.1.2 "><p id="p392913162517"><a name="p392913162517"></a><a name="p392913162517"></a>1.0</p>
</td>
<td class="cellrowborder" valign="top" width="24.759999999999998%" headers="mcps1.2.5.1.3 "><p id="p592912312511"><a name="p592912312511"></a><a name="p592912312511"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/wifiiot-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 1</a>, <a href="https://mirrors.huaweicloud.com/harmonyos/os/1.0/wifiiot-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 2</a></p>
</td>
<td class="cellrowborder" valign="top" width="34.1%" headers="mcps1.2.5.1.4 "><p id="p199296318252"><a name="p199296318252"></a><a name="p199296318252"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/wifiiot-1.0.tar.gz.sha256" target="_blank" rel="noopener noreferrer">SHA-256 Verification Code</a></p>
</td>
</tr>
<tr id="row1293014352510"><td class="cellrowborder" valign="top" width="25%" headers="mcps1.2.5.1.1 "><p id="p692917311258"><a name="p692917311258"></a><a name="p692917311258"></a>Hi3518 solutions</p>
</td>
<td class="cellrowborder" valign="top" width="16.14%" headers="mcps1.2.5.1.2 "><p id="p49291935254"><a name="p49291935254"></a><a name="p49291935254"></a>1.0</p>
</td>
<td class="cellrowborder" valign="top" width="24.759999999999998%" headers="mcps1.2.5.1.3 "><p id="p1792943152517"><a name="p1792943152517"></a><a name="p1792943152517"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/ipcamera_hi3518ev300-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 1</a>, <a href="https://mirrors.huaweicloud.com/harmonyos/os/1.0/ipcamera_hi3518ev300-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 2</a></p>
</td>
<td class="cellrowborder" valign="top" width="34.1%" headers="mcps1.2.5.1.4 "><p id="p1392983162514"><a name="p1392983162514"></a><a name="p1392983162514"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/ipcamera_hi3518ev300-1.0.tar.gz.sha256" target="_blank" rel="noopener noreferrer">SHA-256 Verification Code</a></p>
</td>
</tr>
<tr id="row199306317255"><td class="cellrowborder" valign="top" width="25%" headers="mcps1.2.5.1.1 "><p id="p1693063122511"><a name="p1693063122511"></a><a name="p1693063122511"></a>Hi3516 solutions</p>
</td>
<td class="cellrowborder" valign="top" width="16.14%" headers="mcps1.2.5.1.2 "><p id="p169301335252"><a name="p169301335252"></a><a name="p169301335252"></a>1.0</p>
</td>
<td class="cellrowborder" valign="top" width="24.759999999999998%" headers="mcps1.2.5.1.3 "><p id="p1393012302510"><a name="p1393012302510"></a><a name="p1393012302510"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/ipcamera_hi3516dv300-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 1</a>, <a href="https://mirrors.huaweicloud.com/harmonyos/os/1.0/ipcamera_hi3516dv300-1.0.tar.gz" target="_blank" rel="noopener noreferrer">Site 2</a></p>
</td>
<td class="cellrowborder" valign="top" width="34.1%" headers="mcps1.2.5.1.4 "><p id="p1393083102517"><a name="p1393083102517"></a><a name="p1393083102517"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/ipcamera_hi3516dv300-1.0.tar.gz.sha256" target="_blank" rel="noopener noreferrer">SHA-256 Verification Code</a></p>
</td>
</tr>
<tr id="row13795111119551"><td class="cellrowborder" valign="top" width="25%" headers="mcps1.2.5.1.1 "><p id="p679516111552"><a name="p679516111552"></a><a name="p679516111552"></a>RELEASE-NOTES</p>
</td>
<td class="cellrowborder" valign="top" width="16.14%" headers="mcps1.2.5.1.2 "><p id="p13796201120553"><a name="p13796201120553"></a><a name="p13796201120553"></a>1.0</p>
</td>
<td class="cellrowborder" valign="top" width="24.759999999999998%" headers="mcps1.2.5.1.3 "><p id="p8796911155518"><a name="p8796911155518"></a><a name="p8796911155518"></a><a href="http://tools.harmonyos.com/mirrors/os/1.0/RELEASE-NOTES.txt" target="_blank" rel="noopener noreferrer">Site 1</a></p>
</td>
<td class="cellrowborder" valign="top" width="34.1%" headers="mcps1.2.5.1.4 "><p id="p16796011205518"><a name="p16796011205518"></a><a name="p16796011205518"></a>-</p>
</td>
</tr>
</tbody>
</table>

## Method 2: Acquiring Source Code from the Bundle-specific HPM<a name="section463013147412"></a>

## When to Use<a name="section123926431441"></a>

If OpenHarmony is new to you, sample solutions are helpful to your development. The  [HPM](https://hpm.harmonyos.com/#/en/home)  platform provides a recommended solution. You can add or exclude bundles to quickly customize your system.

## How to Use<a name="section1781916234118"></a>

1.  Search for a proper solution.
    1.  Access the  [HPM](https://hpm.harmonyos.com/#/en/home)  page, and click the  **Solution**  tab, as shown in the following figure.
    2.  Enter a keyword \("camera" as an example\) in the search box. All matched solutions are found.
    3.  Specify filter criteria, such as the bundle type \(example:  **Board support**  and  **Kernel support**\), to further filter the solutions.
    4.  Click the solution you need to view its details.

        **Figure  1**  HPM page<a name="fig838103114320"></a>  
        

        ![](figures/en-us_image_0000001054919529.png)


2.  Customize the solution.

    1.  Read the information under  **Readme**  to learn about the solution \(application scenarios, features, usage, and customization\), as shown in the following figure.
    2.  Click  **Download**  to download the solution to your local PC.
    3.  Click  **Log in to custom**  to customize the bundles for the solution.

    **Figure  2**  Solution example<a name="fig1329851510414"></a>  
    

    ![](figures/en-us_image_0000001054719501.png)

3.  Customize bundles.
    1.  Access the  **Custom solution**  page, as shown in the following figure.
    2.  Set the toggle switch next to a specific optional bundle to exclude it from the solution, or click  **Add bundle**  to add new bundles.
    3.  Enter the basic information about your project, including the bundle name, version, and description, on the right pane.
    4.  Click  **Download**. The system then generates the OpenHarmony code structure file \(for example,  **name.zip**\) and saves it to your local PC.
        -   The downloaded compressed package does not contain the original file of source code. You can import the package to the IDE, decompress it, and run the  **hpm install**  command to download all required bundles.
        -   The downloaded bundles are stored in the  **ohos\_bundles**  folder in the project directory.

            **Figure  3**  Customizing bundles<a name="fig2448349749"></a>  
            

            ![](figures/en-us_image_0000001055679464.png)




## Method 3: Acquiring Source Code with a hpm-cli Tool<a name="section9459261856"></a>

## When to Use<a name="section1854923620139"></a>

-   You have obtained bundle-specific source code from the HPM website, and want to independently upgrade one or more bundles in the source code.
-   You are familiar with OpenHarmony development and  **hpm-cli**  tools.

## Preparations<a name="section4451113551114"></a>

You need to install the  **Node.js**  and hpm-cli tool as follows:

1.  Install  **Node.js**.

    Download  **Node.js**  from its official website and install it on your local PC.

    You are advised to install  [Node.js](https://nodejs.org/)  12.x \(including npm 6.14.4\) or a later version \(12.13.0 or later is recommended\).

2.  Install the hpm-cli tool using  **npm**  delivered with  **Node.js**.

    Open the CMD window and run the following command:

    ```
    npm install -g @ohos/hpm-cli
    ```

3.  Run the following command to check whether the installation is successful. If the HPM version is displayed, the installation is successful.

    ```
    hpm -V or hpm --version
    ```

4.  Run the following command to upgrade the HPM version:

    ```
    npm update -g @ohos/hpm-cli
    ```


## Operations<a name="section1445143510117"></a>

Add the bundle \(**@ohos/demo**  as an example\) to your project as follows:

1.  Go to the development directory and run the following command to create a development project using the default template:

    ```
    hpm init -t default
    ```

2.  Run the following command to install the bundle \(**@ohos/demo**  as an example\):

    ```
    hpm install @ohos/demo
    ```

3.  Verify that the  **hpm-cli**  tool automatically downloads all dependent bundles from the server. If the download is successful, the message "Install successfully!" is displayed.

    ```
    $ hpm install @ohos/demo
    Requesting: https://url.foo.bar/hpm/registry/api/bundles/@ohos/demo
    downloading @ohos/demo
    Requesting: https://lfcontentcenterdev....../bMAlLrYISLqdUTFFFCdgzA.tgz
    extract D:\demo\ohos_bundles\@ohos\demo\@ohos-demo-1.0.7.tgz
    Install successfully!
    ```


## Method 4: Acquiring Source Code from a Code Repository<a name="section537312010229"></a>

## When to Use<a name="section1492115412228"></a>

-   You want to establish a baseline based on stable OpenHarmony releases and distribute the baseline to your customers.

-   You have interconnected your software with OpenHarmony and need official certification from OpenHarmony.

-   You want to contribute code to the OpenHarmony ecosystem after chips, modules, and applications are certified by OpenHarmony.

-   You need to address OpenHarmony issues.

-   You want to learn OpenHarmony source code.


## Preparations<a name="section1076962313239"></a>

1.  Register your account with gitee.
2.  Register an SSH public key.
3.  Install the git client and configure basic information.

    ```
    git config --global user.name "yourname"
    git config --global user.email "your-email-address"
    git config --global credential.helper store
    ```

4.  Run the following commands to install the  **repo**  tool:

    ```
    curl https://gitee.com/oschina/repo/raw/fork_flow/repo-py3 > /usr/local/bin/repo
    chmod a+x /usr/local/bin/repo
    pip install -i https://pypi.tuna.tsinghua.edu.cn/simple requests
    ```


## Operations<a name="section17162735266"></a>

Method 1 \(recommended\): Use the  **repo**  tool to download source code.

```
repo init -u https://gitee.com/openharmony/manifest.git -b master --no-repo-verify
repo sync -c
```

Method 2: Run the  **git clone**  command to clone a single code repository.

Go to https://gitee.com/openharmony, select the code repository to be cloned, and run the following command:

```
git clone https://gitee.com/openharmony/manifest.git -b master
```

## Source Code Directories<a name="section1072115612811"></a>

The following table describes the OpenHarmony source code directories.

**Table  2**  Directory description

<a name="table3815144702820"></a>
<table><thead align="left"><tr id="row198162047192810"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p690319291299"><a name="p690319291299"></a><a name="p690319291299"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p5903122962918"><a name="p5903122962918"></a><a name="p5903122962918"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1981674719280"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p69031429162912"><a name="p69031429162912"></a><a name="p69031429162912"></a>applications</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p090352912914"><a name="p090352912914"></a><a name="p090352912914"></a>Application samples, including <strong id="b18983231356"><a name="b18983231356"></a><a name="b18983231356"></a>wifi-iot</strong> and <strong id="b689814231158"><a name="b689814231158"></a><a name="b689814231158"></a>ip-camera</strong></p>
</td>
</tr>
<tr id="row5816747132817"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p99031129112918"><a name="p99031129112918"></a><a name="p99031129112918"></a>base</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p790472962914"><a name="p790472962914"></a><a name="p790472962914"></a>Basic software service subsystem set and hardware service subsystem set</p>
</td>
</tr>
<tr id="row1134218692910"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p4904112910295"><a name="p4904112910295"></a><a name="p4904112910295"></a>build</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1090482942911"><a name="p1090482942911"></a><a name="p1090482942911"></a>Bundle-based compilation, building, and configuration scripts</p>
</td>
</tr>
<tr id="row1841618902919"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1390462902910"><a name="p1390462902910"></a><a name="p1390462902910"></a>domains</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1390432914296"><a name="p1390432914296"></a><a name="p1390432914296"></a>Enhanced software service subsystem set</p>
</td>
</tr>
<tr id="row841620912298"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p119041629182919"><a name="p119041629182919"></a><a name="p119041629182919"></a>drivers</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p9904629132911"><a name="p9904629132911"></a><a name="p9904629132911"></a>Driver subsystem</p>
</td>
</tr>
<tr id="row164164992915"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p79042298298"><a name="p79042298298"></a><a name="p79042298298"></a>foundation</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p18904132922915"><a name="p18904132922915"></a><a name="p18904132922915"></a>Basic system capability subsystem set</p>
</td>
</tr>
<tr id="row1441610922915"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p490402916299"><a name="p490402916299"></a><a name="p490402916299"></a>kernel</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1904112932912"><a name="p1904112932912"></a><a name="p1904112932912"></a>Kernel subsystem</p>
</td>
</tr>
<tr id="row194175972917"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1904132912910"><a name="p1904132912910"></a><a name="p1904132912910"></a>prebuilts</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p390492919296"><a name="p390492919296"></a><a name="p390492919296"></a>Compiler and tool chain subsystem</p>
</td>
</tr>
<tr id="row841718942913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p12904929202919"><a name="p12904929202919"></a><a name="p12904929202919"></a>test</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p4904152912297"><a name="p4904152912297"></a><a name="p4904152912297"></a>Testing subsystem</p>
</td>
</tr>
<tr id="row24175915294"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p13904162992916"><a name="p13904162992916"></a><a name="p13904162992916"></a>third_party</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p6904829112917"><a name="p6904829112917"></a><a name="p6904829112917"></a>Open-source third-party software</p>
</td>
</tr>
<tr id="row334210652914"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1390442918299"><a name="p1390442918299"></a><a name="p1390442918299"></a>utils</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p690412296297"><a name="p690412296297"></a><a name="p690412296297"></a>Commonly used development tools</p>
</td>
</tr>
<tr id="row73421664298"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7905172920292"><a name="p7905172920292"></a><a name="p7905172920292"></a>vendor</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p290510290293"><a name="p290510290293"></a><a name="p290510290293"></a>Vendor-provided software</p>
</td>
</tr>
<tr id="row734319617292"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p09056291290"><a name="p09056291290"></a><a name="p09056291290"></a>build.py</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1790542912290"><a name="p1790542912290"></a><a name="p1790542912290"></a>Compilation script file</p>
</td>
</tr>
</tbody>
</table>

