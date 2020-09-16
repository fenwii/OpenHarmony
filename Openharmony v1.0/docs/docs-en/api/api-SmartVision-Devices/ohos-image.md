# OHOS::Image<a name="EN-US_TOPIC_0000001054598179"></a>

## **Overview**<a name="section2088772421093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents basic image attributes, including the image type and path. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1443742626093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table2010003841093533"></a>
<table><thead align="left"><tr id="row1689585865093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1496558457093533"><a name="p1496558457093533"></a><a name="p1496558457093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p281623539093533"><a name="p281623539093533"></a><a name="p281623539093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1701479676093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101691591093533"><a name="p1101691591093533"></a><a name="p1101691591093533"></a><a href="graphic.md#ga17210a2d5bb0be6d4b58efe249563d1b">Image</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p558052523093533"><a name="p558052523093533"></a><a name="p558052523093533"></a> </p>
<p id="p1944250859093533"><a name="p1944250859093533"></a><a name="p1944250859093533"></a>A constructor used to create an <strong id="b1723554393093533"><a name="b1723554393093533"></a><a name="b1723554393093533"></a><a href="ohos-image.md">Image</a></strong> instance. You can use this constructor when a component requires a map. </p>
</td>
</tr>
<tr id="row1876430056093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1134047076093533"><a name="p1134047076093533"></a><a name="p1134047076093533"></a><a href="graphic.md#gaf3794ceb5acb543f8c526b5d9f6a1e4e">~Image</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146103109093533"><a name="p1146103109093533"></a><a name="p1146103109093533"></a>virtual </p>
<p id="p1185058711093533"><a name="p1185058711093533"></a><a name="p1185058711093533"></a>A destructor used to delete the <strong id="b1179779167093533"><a name="b1179779167093533"></a><a name="b1179779167093533"></a><a href="ohos-image.md">Image</a></strong> instance. </p>
</td>
</tr>
<tr id="row270024263093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p630247078093533"><a name="p630247078093533"></a><a name="p630247078093533"></a><a href="graphic.md#ga592cbeb359a9d13274a6f4972aad3d79">GetImageInfo</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1933251626093533"><a name="p1933251626093533"></a><a name="p1933251626093533"></a>const <a href="ohos-imageinfo.md">ImageInfo</a> * </p>
<p id="p814822069093533"><a name="p814822069093533"></a><a name="p814822069093533"></a>Obtains the image information in an array. </p>
</td>
</tr>
<tr id="row707129495093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p57756415093533"><a name="p57756415093533"></a><a name="p57756415093533"></a><a href="graphic.md#gaa1552ae9813d324260a580c4ef5b0c9c">GetPath</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877807927093533"><a name="p1877807927093533"></a><a name="p1877807927093533"></a>const char * </p>
<p id="p1432623118093533"><a name="p1432623118093533"></a><a name="p1432623118093533"></a>Obtains the image path in binary. </p>
</td>
</tr>
<tr id="row1716152165093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945095724093533"><a name="p1945095724093533"></a><a name="p1945095724093533"></a><a href="graphic.md#gadf426b0d958898df8ef2f9b7b1d278f1">GetHeader</a> (<a href="ohos-imageheader.md">ImageHeader</a> &amp;header) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654001417093533"><a name="p654001417093533"></a><a name="p654001417093533"></a>void </p>
<p id="p1145853378093533"><a name="p1145853378093533"></a><a name="p1145853378093533"></a>Obtains the basic image information, including the image format, width, and height. </p>
</td>
</tr>
<tr id="row126330743093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323394338093533"><a name="p1323394338093533"></a><a name="p1323394338093533"></a><a href="graphic.md#ga7dc8490594e2bc7c9cf50c1237507239">GetSrcType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p888875626093533"><a name="p888875626093533"></a><a name="p888875626093533"></a>uint8_t </p>
<p id="p107015163093533"><a name="p107015163093533"></a><a name="p107015163093533"></a>Obtains the image type. </p>
</td>
</tr>
<tr id="row87038608093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1201476194093533"><a name="p1201476194093533"></a><a name="p1201476194093533"></a><a href="graphic.md#ga4fe78bf99b160fc55770ba1979412c8e">SetSrc</a> (const char *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1739191948093533"><a name="p1739191948093533"></a><a name="p1739191948093533"></a>bool </p>
<p id="p1325029705093533"><a name="p1325029705093533"></a><a name="p1325029705093533"></a>Sets the image path. </p>
</td>
</tr>
<tr id="row1956181193093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p90192903093533"><a name="p90192903093533"></a><a name="p90192903093533"></a><a href="graphic.md#ga9471d489ab4d5b6848c1e50b4b7aac23">SetSrc</a> (const <a href="ohos-imageinfo.md">ImageInfo</a> *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51965154093533"><a name="p51965154093533"></a><a name="p51965154093533"></a>bool </p>
<p id="p366138723093533"><a name="p366138723093533"></a><a name="p366138723093533"></a>Sets the image information. </p>
</td>
</tr>
<tr id="row178257217093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1526252941093533"><a name="p1526252941093533"></a><a name="p1526252941093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1287856789093533"><a name="p1287856789093533"></a><a name="p1287856789093533"></a>void * </p>
<p id="p1200739894093533"><a name="p1200739894093533"></a><a name="p1200739894093533"></a>Overrides the <strong id="b1875515140093533"><a name="b1875515140093533"></a><a name="b1875515140093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1244988086093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1059246762093533"><a name="p1059246762093533"></a><a name="p1059246762093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p565826276093533"><a name="p565826276093533"></a><a name="p565826276093533"></a>void </p>
<p id="p1546504882093533"><a name="p1546504882093533"></a><a name="p1546504882093533"></a>Overrides the <strong id="b1264682424093533"><a name="b1264682424093533"></a><a name="b1264682424093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

