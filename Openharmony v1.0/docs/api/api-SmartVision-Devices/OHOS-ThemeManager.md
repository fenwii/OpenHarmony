# OHOS::ThemeManager<a name="ZH-CN_TOPIC_0000001055358142"></a>

## **Overview**<a name="section1211049927093536"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Declares the singleton class used to manage the current screen theme of an application. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section483548575093536"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table668183813093536"></a>
<table><thead align="left"><tr id="row1128172977093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p358639187093536"><a name="p358639187093536"></a><a name="p358639187093536"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p877292995093536"><a name="p877292995093536"></a><a name="p877292995093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row926532263093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p77582817093536"><a name="p77582817093536"></a><a name="p77582817093536"></a><a href="Graphic.md#ga6c4963d3186afc52db0d0a18bd52820f">SetCurrent</a> (<a href="OHOS-Theme.md">Theme</a> *theme)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074467864093536"><a name="p1074467864093536"></a><a name="p1074467864093536"></a>void&nbsp;</p>
<p id="p1650936969093536"><a name="p1650936969093536"></a><a name="p1650936969093536"></a>Sets the current screen theme for this application. </p>
</td>
</tr>
<tr id="row1564739216093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838108131093536"><a name="p838108131093536"></a><a name="p838108131093536"></a><a href="Graphic.md#ga6aeed87ecd925de4262763f20cd940d5">GetCurrent</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1840925574093536"><a name="p1840925574093536"></a><a name="p1840925574093536"></a><a href="OHOS-Theme.md">Theme</a> *&nbsp;</p>
<p id="p2037648242093536"><a name="p2037648242093536"></a><a name="p2037648242093536"></a>Obtains the current screen theme of this application. </p>
</td>
</tr>
<tr id="row1246958519093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p961557396093536"><a name="p961557396093536"></a><a name="p961557396093536"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783000690093536"><a name="p783000690093536"></a><a name="p783000690093536"></a>void *&nbsp;</p>
<p id="p863342410093536"><a name="p863342410093536"></a><a name="p863342410093536"></a>Overrides the <strong id="b725471156093536"><a name="b725471156093536"></a><a name="b725471156093536"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1111391155093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291841407093536"><a name="p291841407093536"></a><a name="p291841407093536"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1378571431093536"><a name="p1378571431093536"></a><a name="p1378571431093536"></a>void&nbsp;</p>
<p id="p873818121093536"><a name="p873818121093536"></a><a name="p873818121093536"></a>Overrides the <strong id="b1876940898093536"><a name="b1876940898093536"></a><a name="b1876940898093536"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table1880653263093536"></a>
<table><thead align="left"><tr id="row637058615093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p133216911093536"><a name="p133216911093536"></a><a name="p133216911093536"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p230347195093536"><a name="p230347195093536"></a><a name="p230347195093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row668568874093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p309704858093536"><a name="p309704858093536"></a><a name="p309704858093536"></a><a href="Graphic.md#gaf98c321c61e63bdfdc1a0eed3735084b">GetInstance</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1923455591093536"><a name="p1923455591093536"></a><a name="p1923455591093536"></a>static <a href="OHOS-ThemeManager.md">ThemeManager</a> &amp;&nbsp;</p>
<p id="p573944714093536"><a name="p573944714093536"></a><a name="p573944714093536"></a>Obtains the singleton instance of the <strong id="b1068867578093536"><a name="b1068867578093536"></a><a name="b1068867578093536"></a><a href="OHOS-ThemeManager.md">ThemeManager</a></strong> class. </p>
</td>
</tr>
</tbody>
</table>

