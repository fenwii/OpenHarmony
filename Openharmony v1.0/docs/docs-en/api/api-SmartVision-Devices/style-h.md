# style.h<a name="EN-US_TOPIC_0000001055358088"></a>

## **Overview**<a name="section1717532277084832"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the attributes and common functions of style. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1351518273084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1432527986084832"></a>
<table><thead align="left"><tr id="row593923219084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p688356694084832"><a name="p688356694084832"></a><a name="p688356694084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p448130666084832"><a name="p448130666084832"></a><a name="p448130666084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row930387789084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1560161125084832"><a name="p1560161125084832"></a><a name="p1560161125084832"></a><a href="ohos-style.md">OHOS::Style</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1180739751084832"><a name="p1180739751084832"></a><a name="p1180739751084832"></a>Defines the basic attributes and functions of a style. You can use this class to set different styles. </p>
</td>
</tr>
<tr id="row1016027357084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1421311582084832"><a name="p1421311582084832"></a><a name="p1421311582084832"></a><a href="ohos-styledefault.md">OHOS::StyleDefault</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867646635084832"><a name="p867646635084832"></a><a name="p867646635084832"></a>Define some default style for <a href="ohos-uiview.md">UIView</a>. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2060380913084832"></a>
<table><thead align="left"><tr id="row1562942271084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1325133938084832"><a name="p1325133938084832"></a><a name="p1325133938084832"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1621297290084832"><a name="p1621297290084832"></a><a name="p1621297290084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row754319223084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1977949510084832"><a name="p1977949510084832"></a><a name="p1977949510084832"></a>: uint8_t {   <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa81f161546d7e1853d1c273e3810fe08b">OHOS::STYLE_BACKGROUND_COLOR</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa639cb87312225b97bde6e4d2be950b7f">OHOS::STYLE_BACKGROUND_OPA</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa4e61810ea3d5f385908eb8a4139027a5">OHOS::STYLE_BORDER_RADIUS</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa8fc5a572665a64ad6d27f70480de3b9a">OHOS::STYLE_BORDER_COLOR</a>,   <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa13df567903c15b369bf612bd97a9b886">OHOS::STYLE_BORDER_OPA</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfae9bd454f8703c13e8385668b3ac19e41">OHOS::STYLE_BORDER_WIDTH</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa3231d33e8bb12cd0cf6911076c877892">OHOS::STYLE_PADDING_LEFT</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa8cc34b7c9774ce7dc940b7deeb64de1f">OHOS::STYLE_PADDING_RIGHT</a>,   <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa5225ed05b95d4a95a2c48250518c7c7f">OHOS::STYLE_PADDING_TOP</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa65e4dd92a76dc374b487cd24fa37199b">OHOS::STYLE_PADDING_BOTTOM</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa251e2a6ea777b9b6af8f6ccf79d060cc">OHOS::STYLE_MARGIN_LEFT</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa59ab9a49b6fe3f1fd42a79bf70398c70">OHOS::STYLE_MARGIN_RIGHT</a>,   <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfad5dbc07ebf86daf81e30fcbf9051c3b6">OHOS::STYLE_MARGIN_TOP</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa05fa788c60b80429efd0e42fc5d3d4af">OHOS::STYLE_MARGIN_BOTTOM</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfae63c7c001e11994f2ec952559c3a0d5f">OHOS::STYLE_IMAGE_OPA</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa21142f37831ece4dc6fe12a3474029a5">OHOS::STYLE_TEXT_COLOR</a>,   <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa7288938187d2b5c74d0d1789d73784a3">OHOS::STYLE_TEXT_FONT</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfaf705c0b077d93c8e5ee3cb4583c8ea87">OHOS::STYLE_LETTER_SPACE</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa06ab7c8b467da98902fe19f2b21595ba">OHOS::STYLE_LINE_SPACE</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa8889542f8ea0fc454895c6e245d9cfdf">OHOS::STYLE_TEXT_OPA</a>,   <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa59ce09cf70ef205a7ff081f10d6c1380">OHOS::STYLE_LINE_COLOR</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfadb7984bac1deeffafc3f04169480937e">OHOS::STYLE_LINE_WIDTH</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa7aa7e8dfa8b88cc3ef77c4c3b23a5ea2">OHOS::STYLE_LINE_OPA</a>, <a href="graphic.md#gga2933ed17ce67e3e9c997aa2cf6bd04bfa420aa5184ddfd2e95632095c92dfbee5">OHOS::STYLE_LINE_CAP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p335855108084832"><a name="p335855108084832"></a><a name="p335855108084832"></a>Enumerates keys of styles. </p>
</td>
</tr>
<tr id="row2068664695084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p576792033084832"><a name="p576792033084832"></a><a name="p576792033084832"></a><a href="graphic.md#ga2db3928cdf793f4950245a6841dd43d6">OHOS::CapType</a> : uint8_t { <a href="graphic.md#gga2db3928cdf793f4950245a6841dd43d6a7692381654eff26893e03ac1983c8f45">OHOS::CAP_NONE</a>, <a href="graphic.md#gga2db3928cdf793f4950245a6841dd43d6ada0a5a2f0100d929e9e1d1d31ef26cce">OHOS::CAP_ROUND</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486398123084832"><a name="p486398123084832"></a><a name="p486398123084832"></a>Enumerates cap styles. </p>
</td>
</tr>
</tbody>
</table>

