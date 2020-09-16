# OHOS::UIDumpDomTree<a name="ZH-CN_TOPIC_0000001055518118"></a>

## **Overview**<a name="section1985786740093535"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Provides functions for exporting information about a specified DOM node or information about the DOM tree starting from a specified DOM node. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section775896990093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table608674004093535"></a>
<table><thead align="left"><tr id="row1682925049093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p894607072093535"><a name="p894607072093535"></a><a name="p894607072093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p245458329093535"><a name="p245458329093535"></a><a name="p245458329093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1309938068093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1321544421093535"><a name="p1321544421093535"></a><a name="p1321544421093535"></a><a href="Graphic.md#ga04fbff1f92851a2ac55c4575cbc132e9">DumpDomTree</a> (const char *id, const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1709950052093535"><a name="p1709950052093535"></a><a name="p1709950052093535"></a>bool&nbsp;</p>
<p id="p1626832109093535"><a name="p1626832109093535"></a><a name="p1626832109093535"></a>Exports information about a DOM tree starting from a specified DOM node and saves the information to a specified path. </p>
</td>
</tr>
<tr id="row888180448093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p415205668093535"><a name="p415205668093535"></a><a name="p415205668093535"></a><a href="Graphic.md#ga25384e441719c58d5cfdc3c67f1e8625">DumpDomTree</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p573610735093535"><a name="p573610735093535"></a><a name="p573610735093535"></a>bool&nbsp;</p>
<p id="p931139294093535"><a name="p931139294093535"></a><a name="p931139294093535"></a>Exports information about a DOM tree starting from a specified DOM node and saves the information to the default path. The default path is <strong id="b1632874084093535"><a name="b1632874084093535"></a><a name="b1632874084093535"></a>DEFAULT_DUMP_DOM_TREE_PATH</strong>. </p>
</td>
</tr>
<tr id="row154391909093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1815014047093535"><a name="p1815014047093535"></a><a name="p1815014047093535"></a><a href="Graphic.md#ga812e123f85aa3ff687908e19d23fc54f">DumpDomNode</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1739927651093535"><a name="p1739927651093535"></a><a name="p1739927651093535"></a>char *&nbsp;</p>
<p id="p1228304079093535"><a name="p1228304079093535"></a><a name="p1228304079093535"></a>Exports information about a specified DOM node. </p>
</td>
</tr>
<tr id="row2055025841093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p989011564093535"><a name="p989011564093535"></a><a name="p989011564093535"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144682381093535"><a name="p2144682381093535"></a><a name="p2144682381093535"></a>void *&nbsp;</p>
<p id="p1115299005093535"><a name="p1115299005093535"></a><a name="p1115299005093535"></a>Overrides the <strong id="b821222247093535"><a name="b821222247093535"></a><a name="b821222247093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row2067842326093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102771312093535"><a name="p1102771312093535"></a><a name="p1102771312093535"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p718947443093535"><a name="p718947443093535"></a><a name="p718947443093535"></a>void&nbsp;</p>
<p id="p1742895108093535"><a name="p1742895108093535"></a><a name="p1742895108093535"></a>Overrides the <strong id="b705934177093535"><a name="b705934177093535"></a><a name="b705934177093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table1012886607093535"></a>
<table><thead align="left"><tr id="row954727881093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1153572703093535"><a name="p1153572703093535"></a><a name="p1153572703093535"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2067918327093535"><a name="p2067918327093535"></a><a name="p2067918327093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1571969637093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1877667438093535"><a name="p1877667438093535"></a><a name="p1877667438093535"></a><a href="Graphic.md#ga9f1bc7dc04063baeb71a3d3106be2b51">GetInstance</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p253364080093535"><a name="p253364080093535"></a><a name="p253364080093535"></a>static <a href="OHOS-UIDumpDomTree.md">UIDumpDomTree</a> *&nbsp;</p>
<p id="p339758907093535"><a name="p339758907093535"></a><a name="p339758907093535"></a>Obtains an instance in singleton pattern. </p>
</td>
</tr>
</tbody>
</table>

