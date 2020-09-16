# Window<a name="ZH-CN_TOPIC_0000001055039468"></a>

## **Overview**<a name="section347175552093522"></a>

Provides window management capabilities, including creating, destroying, showing, hiding, moving, resizing a window, raising a window to the top, and lowering a window to the bottom. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section44833948093522"></a>

## Files<a name="files"></a>

<a name="table143703035093522"></a>
<table><thead align="left"><tr id="row1002178223093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1000075184093522"><a name="p1000075184093522"></a><a name="p1000075184093522"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p629661613093522"><a name="p629661613093522"></a><a name="p629661613093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row229642334093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099875752093522"><a name="p2099875752093522"></a><a name="p2099875752093522"></a><a href="window-h.md">window.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p737892012093522"><a name="p737892012093522"></a><a name="p737892012093522"></a>Declares the <strong id="b1479398992093522"><a name="b1479398992093522"></a><a name="b1479398992093522"></a>Window</strong> class that provides a drawing canvas for the <strong id="b1441679359093522"><a name="b1441679359093522"></a><a name="b1441679359093522"></a>RootView</strong>, which represents the root node of a view tree. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1900693761093522"></a>
<table><thead align="left"><tr id="row1881884897093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p549563914093522"><a name="p549563914093522"></a><a name="p549563914093522"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1458560763093522"><a name="p1458560763093522"></a><a name="p1458560763093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1624877854093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799249980093522"><a name="p799249980093522"></a><a name="p799249980093522"></a><a href="OHOS-WindowConfig.md">OHOS::WindowConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p925348020093522"><a name="p925348020093522"></a><a name="p925348020093522"></a>Sets the attributes for this window. </p>
</td>
</tr>
<tr id="row2092831046093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149314282093522"><a name="p1149314282093522"></a><a name="p1149314282093522"></a><a href="OHOS-Window.md">OHOS::Window</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p392310609093522"><a name="p392310609093522"></a><a name="p392310609093522"></a>Provides a drawing canvas for the <strong id="b1533617037093522"><a name="b1533617037093522"></a><a name="b1533617037093522"></a><a href="OHOS-RootView.md">RootView</a></strong>, which represents the root node of a view tree. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table501210235093522"></a>
<table><thead align="left"><tr id="row1312201832093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1469456556093522"><a name="p1469456556093522"></a><a name="p1469456556093522"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2047773330093522"><a name="p2047773330093522"></a><a name="p2047773330093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row511751926093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1457001253093522"><a name="p1457001253093522"></a><a name="p1457001253093522"></a><a href="Window.md#gade9f6a70c1e8547785d266aab3ca5725">OHOS::WindowPixelFormat</a> { <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a23fea82a04292ba974dad96468ae610c">OHOS::WINDOW_PIXEL_FORMAT_RGB565</a> = 101, <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a4f397aa8d8480b22b8a65594e09fbc9a">OHOS::WINDOW_PIXEL_FORMAT_ARGB1555</a>, <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a083e4a4abba5810d7bedb8a65bea23f1">OHOS::WINDOW_PIXEL_FORMAT_RGB888</a>, <a href="Window.md#ggade9f6a70c1e8547785d266aab3ca5725a94212b4cc96d2cb46cec7de114437d26">OHOS::WINDOW_PIXEL_FORMAT_ARGB8888</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375968203093522"><a name="p375968203093522"></a><a name="p375968203093522"></a>Enumerates the pixel formats of this window. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table440588903093522"></a>
<table><thead align="left"><tr id="row923062013093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1604827251093522"><a name="p1604827251093522"></a><a name="p1604827251093522"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1963434332093522"><a name="p1963434332093522"></a><a name="p1963434332093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row337757630093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1143000983093522"><a name="p1143000983093522"></a><a name="p1143000983093522"></a><a href="Window.md#ga13f51542db51b560e4bd8c52fe37a7d0">OHOS::Window::CreateWindow</a> (const <a href="OHOS-WindowConfig.md">WindowConfig</a> &amp;config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395382747093522"><a name="p395382747093522"></a><a name="p395382747093522"></a>static <a href="OHOS-Window.md">Window</a> *&nbsp;</p>
<p id="p1623068620093522"><a name="p1623068620093522"></a><a name="p1623068620093522"></a>Creates a <strong id="b262307778093522"><a name="b262307778093522"></a><a name="b262307778093522"></a><a href="OHOS-Window.md">Window</a></strong> instance. </p>
</td>
</tr>
<tr id="row808224078093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p628375143093522"><a name="p628375143093522"></a><a name="p628375143093522"></a><a href="Window.md#gaae86fd5bd45c654159939ac4ba877cc1">OHOS::Window::DestoryWindow</a> (<a href="OHOS-Window.md">Window</a> *window)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p26456372093522"><a name="p26456372093522"></a><a name="p26456372093522"></a>static void&nbsp;</p>
<p id="p1880427746093522"><a name="p1880427746093522"></a><a name="p1880427746093522"></a>Destroys a specified window. </p>
</td>
</tr>
<tr id="row814377084093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p762110330093522"><a name="p762110330093522"></a><a name="p762110330093522"></a><a href="Window.md#ga10d20114dbd02b0ea8306fd508108af9">OHOS::Window::BindRootView</a> (<a href="OHOS-RootView.md">RootView</a> *rootView)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p454661806093522"><a name="p454661806093522"></a><a name="p454661806093522"></a>virtual void&nbsp;</p>
<p id="p426575790093522"><a name="p426575790093522"></a><a name="p426575790093522"></a>Binds the <strong id="b1013682314093522"><a name="b1013682314093522"></a><a name="b1013682314093522"></a><a href="OHOS-RootView.md">RootView</a></strong> to this window. </p>
</td>
</tr>
<tr id="row2018517608093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p3371061093522"><a name="p3371061093522"></a><a name="p3371061093522"></a><a href="Window.md#ga7ad1bbc5a9a758e48a0fcecc10512bf2">OHOS::Window::UnbindRootView</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p158809682093522"><a name="p158809682093522"></a><a name="p158809682093522"></a>virtual void&nbsp;</p>
<p id="p1594262645093522"><a name="p1594262645093522"></a><a name="p1594262645093522"></a>Unbinds the <strong id="b1237257355093522"><a name="b1237257355093522"></a><a name="b1237257355093522"></a><a href="OHOS-RootView.md">RootView</a></strong> from this window. </p>
</td>
</tr>
<tr id="row1741152235093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2093845758093522"><a name="p2093845758093522"></a><a name="p2093845758093522"></a><a href="Window.md#ga0f81825ac2f7acd742d114627d007dc0">OHOS::Window::GetRootView</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p345147682093522"><a name="p345147682093522"></a><a name="p345147682093522"></a>virtual <a href="OHOS-RootView.md">RootView</a> *&nbsp;</p>
<p id="p1079204155093522"><a name="p1079204155093522"></a><a name="p1079204155093522"></a>Obtains the <strong id="b596834272093522"><a name="b596834272093522"></a><a name="b596834272093522"></a><a href="OHOS-RootView.md">RootView</a></strong> bound to this window. </p>
</td>
</tr>
<tr id="row1473315831093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p232472449093522"><a name="p232472449093522"></a><a name="p232472449093522"></a><a href="Window.md#ga2c14344eed608ec8cd345a6c1c835a53">OHOS::Window::GetRect</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638218988093522"><a name="p1638218988093522"></a><a name="p1638218988093522"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p2033285785093522"><a name="p2033285785093522"></a><a name="p2033285785093522"></a>Obtains the rectangle information (position, width, and height) of this window. </p>
</td>
</tr>
<tr id="row1365632378093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302821660093522"><a name="p1302821660093522"></a><a name="p1302821660093522"></a><a href="Window.md#ga920aaa7deb0054c1436b2aaba3a81e4f">OHOS::Window::Show</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1405955152093522"><a name="p1405955152093522"></a><a name="p1405955152093522"></a>virtual void&nbsp;</p>
<p id="p1868197400093522"><a name="p1868197400093522"></a><a name="p1868197400093522"></a>Shows this window. </p>
</td>
</tr>
<tr id="row573818364093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2081347178093522"><a name="p2081347178093522"></a><a name="p2081347178093522"></a><a href="Window.md#ga37272c50d164a77bf004c18174d94736">OHOS::Window::Hide</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105987176093522"><a name="p1105987176093522"></a><a name="p1105987176093522"></a>virtual void&nbsp;</p>
<p id="p541639046093522"><a name="p541639046093522"></a><a name="p541639046093522"></a>Hides this window. </p>
</td>
</tr>
<tr id="row1228743745093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434070053093522"><a name="p1434070053093522"></a><a name="p1434070053093522"></a><a href="Window.md#ga7454cb1c3c28e68f4e962fef108a0d2f">OHOS::Window::MoveTo</a> (int16_t x, int16_t y)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p685660912093522"><a name="p685660912093522"></a><a name="p685660912093522"></a>virtual void&nbsp;</p>
<p id="p1752947105093522"><a name="p1752947105093522"></a><a name="p1752947105093522"></a>Moves this window to a specified position. </p>
</td>
</tr>
<tr id="row207249391093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p889197233093522"><a name="p889197233093522"></a><a name="p889197233093522"></a><a href="Window.md#gac2c1bf9dc681741eb9c0490785bd73c2">OHOS::Window::Resize</a> (int16_t width, int16_t height)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930965719093522"><a name="p1930965719093522"></a><a name="p1930965719093522"></a>virtual void&nbsp;</p>
<p id="p422054007093522"><a name="p422054007093522"></a><a name="p422054007093522"></a>Resizes this window. </p>
</td>
</tr>
<tr id="row1093955752093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1971075479093522"><a name="p1971075479093522"></a><a name="p1971075479093522"></a><a href="Window.md#ga395aa07d4a622059c627d18ecd2ff115">OHOS::Window::RaiseToTop</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672651959093522"><a name="p672651959093522"></a><a name="p672651959093522"></a>virtual void&nbsp;</p>
<p id="p702644549093522"><a name="p702644549093522"></a><a name="p702644549093522"></a>Raises this window to the top. </p>
</td>
</tr>
<tr id="row890831769093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1117276179093522"><a name="p1117276179093522"></a><a name="p1117276179093522"></a><a href="Window.md#ga61c01a10b37843abf8cf348bd7d1d659">OHOS::Window::LowerToBottom</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p995306613093522"><a name="p995306613093522"></a><a name="p995306613093522"></a>virtual void&nbsp;</p>
<p id="p1712057192093522"><a name="p1712057192093522"></a><a name="p1712057192093522"></a>Lowers this window to the bottom. </p>
</td>
</tr>
<tr id="row2137301226093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p768148746093522"><a name="p768148746093522"></a><a name="p768148746093522"></a><a href="Window.md#ga7efafa2bc07e9a0b5fc5c4c8b1b17b89">OHOS::Window::GetWindowId</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1429255263093522"><a name="p1429255263093522"></a><a name="p1429255263093522"></a>virtual int32_t&nbsp;</p>
<p id="p1213482297093522"><a name="p1213482297093522"></a><a name="p1213482297093522"></a>Obtains the unique ID of this window. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1780068350093522"></a>

## **Enumeration Type Documentation**<a name="section448278391093522"></a>

## WindowPixelFormat<a name="gade9f6a70c1e8547785d266aab3ca5725"></a>

```
enum [OHOS::WindowPixelFormat](Window.md#gade9f6a70c1e8547785d266aab3ca5725)
```

 **Description:**

Enumerates the pixel formats of this window. 

<a name="table431736759093522"></a>
<table><thead align="left"><tr id="row400260670093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1729410217093522"><a name="p1729410217093522"></a><a name="p1729410217093522"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p864349340093522"><a name="p864349340093522"></a><a name="p864349340093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row140297532093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggade9f6a70c1e8547785d266aab3ca5725a23fea82a04292ba974dad96468ae610c"><a name="ggade9f6a70c1e8547785d266aab3ca5725a23fea82a04292ba974dad96468ae610c"></a><a name="ggade9f6a70c1e8547785d266aab3ca5725a23fea82a04292ba974dad96468ae610c"></a></strong>WINDOW_PIXEL_FORMAT_RGB565&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131224570093522"><a name="p2131224570093522"></a><a name="p2131224570093522"></a>RGB565 format </p>
 </td>
</tr>
<tr id="row1797088418093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggade9f6a70c1e8547785d266aab3ca5725a4f397aa8d8480b22b8a65594e09fbc9a"><a name="ggade9f6a70c1e8547785d266aab3ca5725a4f397aa8d8480b22b8a65594e09fbc9a"></a><a name="ggade9f6a70c1e8547785d266aab3ca5725a4f397aa8d8480b22b8a65594e09fbc9a"></a></strong>WINDOW_PIXEL_FORMAT_ARGB1555&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391443577093522"><a name="p1391443577093522"></a><a name="p1391443577093522"></a>ARGB1555 format </p>
 </td>
</tr>
<tr id="row1205692694093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggade9f6a70c1e8547785d266aab3ca5725a083e4a4abba5810d7bedb8a65bea23f1"><a name="ggade9f6a70c1e8547785d266aab3ca5725a083e4a4abba5810d7bedb8a65bea23f1"></a><a name="ggade9f6a70c1e8547785d266aab3ca5725a083e4a4abba5810d7bedb8a65bea23f1"></a></strong>WINDOW_PIXEL_FORMAT_RGB888&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1522656366093522"><a name="p1522656366093522"></a><a name="p1522656366093522"></a>RGB888 format </p>
 </td>
</tr>
<tr id="row208326974093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggade9f6a70c1e8547785d266aab3ca5725a94212b4cc96d2cb46cec7de114437d26"><a name="ggade9f6a70c1e8547785d266aab3ca5725a94212b4cc96d2cb46cec7de114437d26"></a><a name="ggade9f6a70c1e8547785d266aab3ca5725a94212b4cc96d2cb46cec7de114437d26"></a></strong>WINDOW_PIXEL_FORMAT_ARGB8888&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037543718093522"><a name="p1037543718093522"></a><a name="p1037543718093522"></a>ARGB8888 format </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section55068677093522"></a>

## BindRootView\(\)<a name="ga10d20114dbd02b0ea8306fd508108af9"></a>

```
virtual void OHOS::Window::BindRootView ([RootView](OHOS-RootView.md) * rootView)
```

 **Description:**

Binds the  **[RootView](OHOS-RootView.md)**  to this window. 

**Parameters:**

<a name="table1451575427093522"></a>
<table><thead align="left"><tr id="row1725648960093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p801511851093522"><a name="p801511851093522"></a><a name="p801511851093522"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1911780876093522"><a name="p1911780876093522"></a><a name="p1911780876093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2052002571093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rootView</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b776741010093522"><a name="b776741010093522"></a><a name="b776741010093522"></a><a href="OHOS-RootView.md">RootView</a></strong> to bind. </td>
</tr>
</tbody>
</table>

## CreateWindow\(\)<a name="ga13f51542db51b560e4bd8c52fe37a7d0"></a>

```
static [Window](OHOS-Window.md)* OHOS::Window::CreateWindow (const [WindowConfig](OHOS-WindowConfig.md) & config)
```

 **Description:**

Creates a  **[Window](OHOS-Window.md)**  instance. 

**Parameters:**

<a name="table112422287093522"></a>
<table><thead align="left"><tr id="row45740337093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p480069026093522"><a name="p480069026093522"></a><a name="p480069026093522"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1306718185093522"><a name="p1306718185093522"></a><a name="p1306718185093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row478099065093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">config</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the window configuration. For details, see <a href="OHOS-WindowConfig.md">WindowConfig</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the  **[Window](OHOS-Window.md)**  instance if the operation is successful; returns  **nullptr**  otherwise. 



## DestoryWindow\(\)<a name="gaae86fd5bd45c654159939ac4ba877cc1"></a>

```
static void OHOS::Window::DestoryWindow ([Window](OHOS-Window.md) * window)
```

 **Description:**

Destroys a specified window. 

**Parameters:**

<a name="table365971020093522"></a>
<table><thead align="left"><tr id="row263024794093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1093330173093522"><a name="p1093330173093522"></a><a name="p1093330173093522"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p992541186093522"><a name="p992541186093522"></a><a name="p992541186093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row621426409093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">window</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b749329953093522"><a name="b749329953093522"></a><a name="b749329953093522"></a><a href="OHOS-Window.md">Window</a></strong> instance to destroy. </td>
</tr>
</tbody>
</table>

## GetRect\(\)<a name="ga2c14344eed608ec8cd345a6c1c835a53"></a>

```
virtual [Rect](OHOS-Rect.md) OHOS::Window::GetRect ()
```

 **Description:**

Obtains the rectangle information \(position, width, and height\) of this window. 

**Returns:**

Returns the rectangle information of this window. 



## GetRootView\(\)<a name="ga0f81825ac2f7acd742d114627d007dc0"></a>

```
virtual [RootView](OHOS-RootView.md)* OHOS::Window::GetRootView ()
```

 **Description:**

Obtains the  **[RootView](OHOS-RootView.md)**  bound to this window. 

**Returns:**

Returns the  **[RootView](OHOS-RootView.md)**  if available; returns  **nullptr**  otherwise. 



## GetWindowId\(\)<a name="ga7efafa2bc07e9a0b5fc5c4c8b1b17b89"></a>

```
virtual int32_t OHOS::Window::GetWindowId ()
```

 **Description:**

Obtains the unique ID of this window. 

The window ID is within \[0, 31\]. An ID will be reused after the current window is destroyed. A maximum of 32 windows can be displayed at the same time.

**Returns:**

Returns the unique ID of this window if the operation is successful; returns  **-1**  otherwise. 



## Hide\(\)<a name="ga37272c50d164a77bf004c18174d94736"></a>

```
virtual void OHOS::Window::Hide ()
```

 **Description:**

Hides this window. 

## LowerToBottom\(\)<a name="ga61c01a10b37843abf8cf348bd7d1d659"></a>

```
virtual void OHOS::Window::LowerToBottom ()
```

 **Description:**

Lowers this window to the bottom. 

## MoveTo\(\)<a name="ga7454cb1c3c28e68f4e962fef108a0d2f"></a>

```
virtual void OHOS::Window::MoveTo (int16_t x, int16_t y )
```

 **Description:**

Moves this window to a specified position. 

**Parameters:**

<a name="table641177919093522"></a>
<table><thead align="left"><tr id="row1434276207093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1755852698093522"><a name="p1755852698093522"></a><a name="p1755852698093522"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1827512244093522"><a name="p1827512244093522"></a><a name="p1827512244093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row888830017093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">x</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the x-coordinate of the target position. </td>
</tr>
<tr id="row1763055494093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">y</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the y-coordinate of the target position. </td>
</tr>
</tbody>
</table>

## RaiseToTop\(\)<a name="ga395aa07d4a622059c627d18ecd2ff115"></a>

```
virtual void OHOS::Window::RaiseToTop ()
```

 **Description:**

Raises this window to the top. 

## Resize\(\)<a name="gac2c1bf9dc681741eb9c0490785bd73c2"></a>

```
virtual void OHOS::Window::Resize (int16_t width, int16_t height )
```

 **Description:**

Resizes this window. 

**Parameters:**

<a name="table1492760117093522"></a>
<table><thead align="left"><tr id="row312033665093522"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p834581489093522"><a name="p834581489093522"></a><a name="p834581489093522"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1419849522093522"><a name="p1419849522093522"></a><a name="p1419849522093522"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row641914432093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">width</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the new window width. </td>
</tr>
<tr id="row1730602488093522"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">height</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the new window height. </td>
</tr>
</tbody>
</table>

## Show\(\)<a name="ga920aaa7deb0054c1436b2aaba3a81e4f"></a>

```
virtual void OHOS::Window::Show ()
```

 **Description:**

Shows this window. 

## UnbindRootView\(\)<a name="ga7ad1bbc5a9a758e48a0fcecc10512bf2"></a>

```
virtual void OHOS::Window::UnbindRootView ()
```

 **Description:**

Unbinds the  **[RootView](OHOS-RootView.md)**  from this window. 

## **Variable Documentation**<a name="section2060045332093522"></a>

## opacity<a name="ga848d59949e340c4c2572c49212eb6f5a"></a>

```
uint8_t OHOS::WindowConfig::opacity
```

 **Description:**

Opacity, within \[0, 255\] 

## option<a name="gae5bf33ab2eecd5dcafe2eb3da43d6f27"></a>

```
uint32_t OHOS::WindowConfig::option
```

 **Description:**

Other options 

## pixelFormat<a name="ga213fd5a52a7232dd4fbaef7108e2a36a"></a>

```
[WindowPixelFormat](Window.md#gade9f6a70c1e8547785d266aab3ca5725) OHOS::WindowConfig::pixelFormat
```

 **Description:**

Pixel format 

## rect<a name="gabb7c9c7f86fb9f1d29728ca0afa10668"></a>

```
[Rect](OHOS-Rect.md) OHOS::WindowConfig::rect
```

 **Description:**

[Rectangle](Rectangle.md) 

