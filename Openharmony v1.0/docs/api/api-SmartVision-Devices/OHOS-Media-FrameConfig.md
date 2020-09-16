# OHOS::Media::FrameConfig<a name="ZH-CN_TOPIC_0000001055358122"></a>

## **Overview**<a name="section1104856058084838"></a>

**Related Modules:**

[MultiMedia\_FrameConfig](MultiMedia_FrameConfig.md)

**Description:**

Provides functions to configure frames. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1890010794084838"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table6105295084838"></a>
<table><thead align="left"><tr id="row86453227084838"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p614410224084838"><a name="p614410224084838"></a><a name="p614410224084838"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1860890178084838"><a name="p1860890178084838"></a><a name="p1860890178084838"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row798058168084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p437097052084838"><a name="p437097052084838"></a><a name="p437097052084838"></a><a href="MultiMedia_FrameConfig.md#ga043537d52f5db46d981f9e89848b0fba">FrameConfig</a> ()=delete</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319716853084838"><a name="p319716853084838"></a><a name="p319716853084838"></a>&nbsp;</p>
<p id="p1280283555084838"><a name="p1280283555084838"></a><a name="p1280283555084838"></a>A constructor used to create a <strong id="b1477762909084838"><a name="b1477762909084838"></a><a name="b1477762909084838"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> instance. </p>
</td>
</tr>
<tr id="row2072568864084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503917954084838"><a name="p1503917954084838"></a><a name="p1503917954084838"></a><a href="MultiMedia_FrameConfig.md#gac8f74ff3689605a59a17997bdeaec1fc">FrameConfig</a> (int32_t type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p512144492084838"><a name="p512144492084838"></a><a name="p512144492084838"></a>&nbsp;</p>
<p id="p1412806540084838"><a name="p1412806540084838"></a><a name="p1412806540084838"></a>A constructor used to create a <strong id="b886222445084838"><a name="b886222445084838"></a><a name="b886222445084838"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> instance based on the configuration mode. </p>
</td>
</tr>
<tr id="row1287121501084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p933724231084838"><a name="p933724231084838"></a><a name="p933724231084838"></a><a href="MultiMedia_FrameConfig.md#gaa2e58c2ce602d9263b76596374823616">~FrameConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314498209084838"><a name="p1314498209084838"></a><a name="p1314498209084838"></a>&nbsp;</p>
<p id="p1844905450084838"><a name="p1844905450084838"></a><a name="p1844905450084838"></a>A destructor used to delete the <strong id="b161433776084838"><a name="b161433776084838"></a><a name="b161433776084838"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> instance. </p>
</td>
</tr>
<tr id="row1922456099084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259673113084838"><a name="p1259673113084838"></a><a name="p1259673113084838"></a><a href="MultiMedia_FrameConfig.md#ga382977445a583ed0424c5ccf581e824c">GetFrameConfigType</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1741999443084838"><a name="p1741999443084838"></a><a name="p1741999443084838"></a>int32_t&nbsp;</p>
<p id="p1172907840084838"><a name="p1172907840084838"></a><a name="p1172907840084838"></a>Obtains the frame configuration type. </p>
</td>
</tr>
<tr id="row676091468084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1424549163084838"><a name="p1424549163084838"></a><a name="p1424549163084838"></a><a href="MultiMedia_FrameConfig.md#ga955d04df96c009e4699ea6ed46d9e758">GetSurfaces</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1499402255084838"><a name="p1499402255084838"></a><a name="p1499402255084838"></a>std::list&lt; <a href="OHOS-Surface.md">Surface</a> * &gt;&nbsp;</p>
<p id="p663351193084838"><a name="p663351193084838"></a><a name="p663351193084838"></a>Obtains a list of shared memories (surface objects). </p>
</td>
</tr>
<tr id="row1507115178084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762698968084838"><a name="p1762698968084838"></a><a name="p1762698968084838"></a><a href="MultiMedia_FrameConfig.md#ga16760311713db03bf06ea0a6d6622013">AddSurface</a> (<a href="OHOS-Surface.md">Surface</a> &amp;surface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p803619183084838"><a name="p803619183084838"></a><a name="p803619183084838"></a>void&nbsp;</p>
<p id="p979268855084838"><a name="p979268855084838"></a><a name="p979268855084838"></a>Adds a surface (an object of shared memory). </p>
</td>
</tr>
<tr id="row1214227764084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p100452182084838"><a name="p100452182084838"></a><a name="p100452182084838"></a><a href="MultiMedia_FrameConfig.md#ga9ac4bc5e52840ee579482a3836774762">RemoveSurface</a> (<a href="OHOS-Surface.md">Surface</a> &amp;surface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352339825084838"><a name="p352339825084838"></a><a name="p352339825084838"></a>void&nbsp;</p>
<p id="p1601893395084838"><a name="p1601893395084838"></a><a name="p1601893395084838"></a>Removes a surface (an object of shared memory). You can call this function to release the surface when your application does not need to obtain data. </p>
</td>
</tr>
</tbody>
</table>

