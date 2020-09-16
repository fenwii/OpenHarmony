# OHOS::Window<a name="ZH-CN_TOPIC_0000001055678106"></a>

## **Overview**<a name="section966679488093532"></a>

**Related Modules:**

[Window](Window.md)

**Description:**

Provides a drawing canvas for the  **[RootView](OHOS-RootView.md)**, which represents the root node of a view tree. 

Each window is bound to a  **[RootView](OHOS-RootView.md)**. For details, see  [RootView](OHOS-RootView.md). This class also provides window management capabilities, including creating, destroying, showing, hiding, moving, resizing a window, raising a window to the top, and lowering a window to the bottom.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1082264336093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table362303986093532"></a>
<table><thead align="left"><tr id="row1923925105093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p718194250093532"><a name="p718194250093532"></a><a name="p718194250093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1073158127093532"><a name="p1073158127093532"></a><a name="p1073158127093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row696356688093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981262838093532"><a name="p1981262838093532"></a><a name="p1981262838093532"></a><a href="Window.md#ga10d20114dbd02b0ea8306fd508108af9">BindRootView</a> (<a href="OHOS-RootView.md">RootView</a> *rootView)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288457243093532"><a name="p288457243093532"></a><a name="p288457243093532"></a>virtual void&nbsp;</p>
<p id="p361259415093532"><a name="p361259415093532"></a><a name="p361259415093532"></a>Binds the <strong id="b1624369593093532"><a name="b1624369593093532"></a><a name="b1624369593093532"></a><a href="OHOS-RootView.md">RootView</a></strong> to this window. </p>
</td>
</tr>
<tr id="row1660513521093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651130225093532"><a name="p651130225093532"></a><a name="p651130225093532"></a><a href="Window.md#ga7ad1bbc5a9a758e48a0fcecc10512bf2">UnbindRootView</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1077671900093532"><a name="p1077671900093532"></a><a name="p1077671900093532"></a>virtual void&nbsp;</p>
<p id="p806762751093532"><a name="p806762751093532"></a><a name="p806762751093532"></a>Unbinds the <strong id="b1713884052093532"><a name="b1713884052093532"></a><a name="b1713884052093532"></a><a href="OHOS-RootView.md">RootView</a></strong> from this window. </p>
</td>
</tr>
<tr id="row838855240093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p811376753093532"><a name="p811376753093532"></a><a name="p811376753093532"></a><a href="Window.md#ga0f81825ac2f7acd742d114627d007dc0">GetRootView</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107647409093532"><a name="p107647409093532"></a><a name="p107647409093532"></a>virtual <a href="OHOS-RootView.md">RootView</a> *&nbsp;</p>
<p id="p692551750093532"><a name="p692551750093532"></a><a name="p692551750093532"></a>Obtains the <strong id="b960032965093532"><a name="b960032965093532"></a><a name="b960032965093532"></a><a href="OHOS-RootView.md">RootView</a></strong> bound to this window. </p>
</td>
</tr>
<tr id="row716807692093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953920425093532"><a name="p953920425093532"></a><a name="p953920425093532"></a><a href="Window.md#ga2c14344eed608ec8cd345a6c1c835a53">GetRect</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399096325093532"><a name="p1399096325093532"></a><a name="p1399096325093532"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p72899929093532"><a name="p72899929093532"></a><a name="p72899929093532"></a>Obtains the rectangle information (position, width, and height) of this window. </p>
</td>
</tr>
<tr id="row1027198499093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105176396093532"><a name="p105176396093532"></a><a name="p105176396093532"></a><a href="Window.md#ga920aaa7deb0054c1436b2aaba3a81e4f">Show</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491163301093532"><a name="p491163301093532"></a><a name="p491163301093532"></a>virtual void&nbsp;</p>
<p id="p1161535336093532"><a name="p1161535336093532"></a><a name="p1161535336093532"></a>Shows this window. </p>
</td>
</tr>
<tr id="row1167842460093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079797656093532"><a name="p2079797656093532"></a><a name="p2079797656093532"></a><a href="Window.md#ga37272c50d164a77bf004c18174d94736">Hide</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1333107569093532"><a name="p1333107569093532"></a><a name="p1333107569093532"></a>virtual void&nbsp;</p>
<p id="p709137617093532"><a name="p709137617093532"></a><a name="p709137617093532"></a>Hides this window. </p>
</td>
</tr>
<tr id="row52612541093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p307641407093532"><a name="p307641407093532"></a><a name="p307641407093532"></a><a href="Window.md#ga7454cb1c3c28e68f4e962fef108a0d2f">MoveTo</a> (int16_t x, int16_t y)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1581552037093532"><a name="p1581552037093532"></a><a name="p1581552037093532"></a>virtual void&nbsp;</p>
<p id="p1316161591093532"><a name="p1316161591093532"></a><a name="p1316161591093532"></a>Moves this window to a specified position. </p>
</td>
</tr>
<tr id="row1239322177093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795180600093532"><a name="p795180600093532"></a><a name="p795180600093532"></a><a href="Window.md#gac2c1bf9dc681741eb9c0490785bd73c2">Resize</a> (int16_t width, int16_t height)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657280570093532"><a name="p1657280570093532"></a><a name="p1657280570093532"></a>virtual void&nbsp;</p>
<p id="p1215807367093532"><a name="p1215807367093532"></a><a name="p1215807367093532"></a>Resizes this window. </p>
</td>
</tr>
<tr id="row799886260093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p713601140093532"><a name="p713601140093532"></a><a name="p713601140093532"></a><a href="Window.md#ga395aa07d4a622059c627d18ecd2ff115">RaiseToTop</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p102710043093532"><a name="p102710043093532"></a><a name="p102710043093532"></a>virtual void&nbsp;</p>
<p id="p1768530472093532"><a name="p1768530472093532"></a><a name="p1768530472093532"></a>Raises this window to the top. </p>
</td>
</tr>
<tr id="row243039631093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1342364407093532"><a name="p1342364407093532"></a><a name="p1342364407093532"></a><a href="Window.md#ga61c01a10b37843abf8cf348bd7d1d659">LowerToBottom</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1437886739093532"><a name="p1437886739093532"></a><a name="p1437886739093532"></a>virtual void&nbsp;</p>
<p id="p1035327384093532"><a name="p1035327384093532"></a><a name="p1035327384093532"></a>Lowers this window to the bottom. </p>
</td>
</tr>
<tr id="row44690126093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1080946541093532"><a name="p1080946541093532"></a><a name="p1080946541093532"></a><a href="Window.md#ga7efafa2bc07e9a0b5fc5c4c8b1b17b89">GetWindowId</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1336228672093532"><a name="p1336228672093532"></a><a name="p1336228672093532"></a>virtual int32_t&nbsp;</p>
<p id="p450188365093532"><a name="p450188365093532"></a><a name="p450188365093532"></a>Obtains the unique ID of this window. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table855511761093532"></a>
<table><thead align="left"><tr id="row1215126099093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p215978964093532"><a name="p215978964093532"></a><a name="p215978964093532"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1500824884093532"><a name="p1500824884093532"></a><a name="p1500824884093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1626691303093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468813803093532"><a name="p468813803093532"></a><a name="p468813803093532"></a><a href="Window.md#ga13f51542db51b560e4bd8c52fe37a7d0">CreateWindow</a> (const <a href="OHOS-WindowConfig.md">WindowConfig</a> &amp;config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74721279093532"><a name="p74721279093532"></a><a name="p74721279093532"></a>static <a href="OHOS-Window.md">Window</a> *&nbsp;</p>
<p id="p1770984460093532"><a name="p1770984460093532"></a><a name="p1770984460093532"></a>Creates a <strong id="b361065470093532"><a name="b361065470093532"></a><a name="b361065470093532"></a><a href="OHOS-Window.md">Window</a></strong> instance. </p>
</td>
</tr>
<tr id="row1965543349093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374951789093532"><a name="p374951789093532"></a><a name="p374951789093532"></a><a href="Window.md#gaae86fd5bd45c654159939ac4ba877cc1">DestoryWindow</a> (<a href="OHOS-Window.md">Window</a> *window)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p335242482093532"><a name="p335242482093532"></a><a name="p335242482093532"></a>static void&nbsp;</p>
<p id="p1463959295093532"><a name="p1463959295093532"></a><a name="p1463959295093532"></a>Destroys a specified window. </p>
</td>
</tr>
</tbody>
</table>

