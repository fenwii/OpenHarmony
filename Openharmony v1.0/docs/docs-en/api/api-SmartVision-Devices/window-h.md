# window.h<a name="EN-US_TOPIC_0000001055039504"></a>

## **Overview**<a name="section1589497142093528"></a>

**Related Modules:**

[Window](window.md)

**Description:**

Declares the  **Window**  class that provides a drawing canvas for the  **RootView**, which represents the root node of a view tree. 

Each window is bound to a  **RootView**. For details, see  **RootView**. The  **Window**  class also provides window management capabilities, including creating, destroying, showing, hiding, moving, resizing a window, raising a window to the top, and lowering a window to the bottom.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1798001279093528"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table933090669093528"></a>
<table><thead align="left"><tr id="row822839275093528"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p740492849093528"><a name="p740492849093528"></a><a name="p740492849093528"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2105730530093528"><a name="p2105730530093528"></a><a name="p2105730530093528"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1803759112093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807578804093528"><a name="p1807578804093528"></a><a name="p1807578804093528"></a><a href="ohos-windowconfig.md">OHOS::WindowConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1110465539093528"><a name="p1110465539093528"></a><a name="p1110465539093528"></a>Sets the attributes for this window. </p>
</td>
</tr>
<tr id="row1018596681093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051660495093528"><a name="p2051660495093528"></a><a name="p2051660495093528"></a><a href="ohos-window.md">OHOS::Window</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246812686093528"><a name="p246812686093528"></a><a name="p246812686093528"></a>Provides a drawing canvas for the <strong id="b650417577093528"><a name="b650417577093528"></a><a name="b650417577093528"></a><a href="ohos-rootview.md">RootView</a></strong>, which represents the root node of a view tree. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table950178814093528"></a>
<table><thead align="left"><tr id="row1783762976093528"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1283999468093528"><a name="p1283999468093528"></a><a name="p1283999468093528"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1308278540093528"><a name="p1308278540093528"></a><a name="p1308278540093528"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2011239017093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1968278327093528"><a name="p1968278327093528"></a><a name="p1968278327093528"></a><a href="window.md#gade9f6a70c1e8547785d266aab3ca5725">OHOS::WindowPixelFormat</a> { <a href="window.md#ggade9f6a70c1e8547785d266aab3ca5725a23fea82a04292ba974dad96468ae610c">OHOS::WINDOW_PIXEL_FORMAT_RGB565</a> = 101, <a href="window.md#ggade9f6a70c1e8547785d266aab3ca5725a4f397aa8d8480b22b8a65594e09fbc9a">OHOS::WINDOW_PIXEL_FORMAT_ARGB1555</a>, <a href="window.md#ggade9f6a70c1e8547785d266aab3ca5725a083e4a4abba5810d7bedb8a65bea23f1">OHOS::WINDOW_PIXEL_FORMAT_RGB888</a>, <a href="window.md#ggade9f6a70c1e8547785d266aab3ca5725a94212b4cc96d2cb46cec7de114437d26">OHOS::WINDOW_PIXEL_FORMAT_ARGB8888</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459038084093528"><a name="p459038084093528"></a><a name="p459038084093528"></a>Enumerates the pixel formats of this window. </p>
</td>
</tr>
</tbody>
</table>

