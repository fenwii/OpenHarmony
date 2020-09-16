# TextAdapter<a name="ZH-CN_TOPIC_0000001054212923"></a>

## **Overview**<a name="section208340203113041"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a text adapter, which implements  [UILabel](UILabel.md)  instance construction and supports text data and continuous integer data. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section320696424113041"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga38bde4aa4a0952341ad74284ff686832">TextAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>&nbsp;</p>
<p>A constructor used to create a <strong><a href="UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga1e868c845df224beff2f3c6f49593d3b">~TextAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual&nbsp;</p>
<p>A destructor used to delete the <strong><a href="UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga733211ca13eccff628bb2712c27b885e">GetView</a> (<a href="OHOS-UIView.md">UIView</a> *inView, int16_t index) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p>Obtains a <strong><a href="UILabel.md">UILabel</a></strong> instance to convert adapter data into another <strong><a href="UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga7147c1cc7f5f5ccd6bdd939082a1d88b">SetData</a> (<a href="OHOS-List-T.md">List</a>&lt; const char *&gt; *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the <a href="UILabel.md">UILabel</a> adapter data, which is a string linked list. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga9521d17dfaf251b42deafc182aea8a1e">SetData</a> (int16_t start, int16_t end)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets continuously increasing data. For example, if you need to set data <strong>0</strong>, <strong>1</strong>, <strong>2</strong>, <strong>3</strong>, <strong>4</strong>, use this function to set <strong>start</strong> to 0 and <strong>end</strong> to 4. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gaf0ec9f4036ed071ab95081bb3237f89a">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets font ID. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga077ac9bece7019abc2a755031ddc5575">GetFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>uint8_t&nbsp;</p>
<p>Obtains font ID. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga28d957b0aa0324e876a871eae1b80d3f">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the font. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gacba8806f0f63a2b0436dbe4ec1b4d01c">GetStyle</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Style &amp;&nbsp;</p>
<p>Obtains the <a href="UILabel.md">UILabel</a> adapter style. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gaa8d1098628c391a687b08f4ccdba0a4d">GetCount</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual uint16_t&nbsp;</p>
<p>Obtains the <strong>data</strong> size of the <a href="UILabel.md">UILabel</a> adapter. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gaed7f27b1dbf4f50ae8eda00cc6cb6a27">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the width of <a href="UILabel.md">UILabel</a> constructed by the adapter. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga618021df16f2156ddeeb12d5a8fa14f9">SetDirect</a> (<a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> direct)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the direction of the <a href="UILabel.md">UILabel</a> constructed by the adapter. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga2c83259c064091d74deac1e4a69f834c">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the height of the <a href="UILabel.md">UILabel</a> constructed by the adapter. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gafc5f3b2c909753f4a7ef53daa80b530b">SetLineBreakMode</a> (const uint8_t lineBreakMode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the <strong>LineBreakMode</strong> attribute of <a href="UILabel.md">UILabel</a> constructed by the adapter. For details about the values of <strong>LineBreakMode</strong>, see <strong>LINE_BREAK_ADAPT</strong>, <strong>LINE_BREAK_WRAP</strong>, <strong>LINE_BREAK_ELLIPSIS</strong>, and <strong>LINE_BREAK_MARQUEE</strong>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga9aa8cecae666906c7fa3d292d6c1c842">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">UIView::OnClickListener</a> *clickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the callback function to be invoked upon a click event. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gadad75361a42fd390b5f9c5edad2f2f0b">SetTextFormatter</a> (<a href="OHOS-TextFormatter.md">TextFormatter</a> *formatter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the text formatter. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#gab60e1c77fb98352bd62e56b550d75d88">AbstractAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>&nbsp;</p>
<p>A constructor used to create an <strong><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> instance. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Graphic.md#ga86fbbc62904d459ec4fa39bab7703af7">~AbstractAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual&nbsp;</p>
<p>A destructor used to delete the <strong><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> instance. </p>
</td>
</tr>
</tbody>
</table>

