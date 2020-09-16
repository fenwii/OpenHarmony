# OHOS::Surface<a name="ZH-CN_TOPIC_0000001055039528"></a>

## **Overview**<a name="section2080997428093532"></a>

**Related Modules:**

[Surface](Surface.md)

**Description:**

Defines the consumer listener used to notify consumers when the surface status is updated. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1810000922093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table74059788093532"></a>
<table><thead align="left"><tr id="row1280600468093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1748432273093532"><a name="p1748432273093532"></a><a name="p1748432273093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1064125150093532"><a name="p1064125150093532"></a><a name="p1064125150093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row827614414093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096926082093532"><a name="p1096926082093532"></a><a name="p1096926082093532"></a><a href="Surface.md#ga1d35e9b436057032ec4598f24e31dbfb">~Surface</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p907310922093532"><a name="p907310922093532"></a><a name="p907310922093532"></a>virtual&nbsp;</p>
<p id="p1027081944093532"><a name="p1027081944093532"></a><a name="p1027081944093532"></a>A destructor used to delete the <strong id="b2079032413093532"><a name="b2079032413093532"></a><a name="b2079032413093532"></a><a href="OHOS-Surface.md">Surface</a></strong> instance. </p>
</td>
</tr>
<tr id="row2065484453093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402861575093532"><a name="p402861575093532"></a><a name="p402861575093532"></a><a href="Surface.md#ga44138c9aa20a108358da26893b92150c">SetQueueSize</a> (uint8_t queueSize)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1756973790093532"><a name="p1756973790093532"></a><a name="p1756973790093532"></a>virtual void&nbsp;</p>
<p id="p1917452569093532"><a name="p1917452569093532"></a><a name="p1917452569093532"></a>Sets the number of buffers that can be allocated to the surface. The default value is <strong id="b1173575923093532"><a name="b1173575923093532"></a><a name="b1173575923093532"></a>1</strong>. The value range is [1, 10]. </p>
</td>
</tr>
<tr id="row1475535901093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823907836093532"><a name="p1823907836093532"></a><a name="p1823907836093532"></a><a href="Surface.md#gaff365f4d3178798ff28f0aaab9f467de">GetQueueSize</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196589717093532"><a name="p1196589717093532"></a><a name="p1196589717093532"></a>virtual uint8_t&nbsp;</p>
<p id="p2099457309093532"><a name="p2099457309093532"></a><a name="p2099457309093532"></a>Obtains the number of surface buffers that can be allocated to the surface. The default value is <strong id="b574227847093532"><a name="b574227847093532"></a><a name="b574227847093532"></a>1</strong>. The value range is [1, 10]. </p>
</td>
</tr>
<tr id="row1104523091093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p627873004093532"><a name="p627873004093532"></a><a name="p627873004093532"></a><a href="Surface.md#ga260c12281c283e5a0b63a49f24bd0cc0">SetWidthAndHeight</a> (uint32_t width, uint32_t height)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751682793093532"><a name="p1751682793093532"></a><a name="p1751682793093532"></a>virtual void&nbsp;</p>
<p id="p295747727093532"><a name="p295747727093532"></a><a name="p295747727093532"></a>Sets the width and height of the surface for calculating its stride and size. The default value range of width and height is (0,7680]. </p>
</td>
</tr>
<tr id="row1972118124093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p15953281093532"><a name="p15953281093532"></a><a name="p15953281093532"></a><a href="Surface.md#ga1220bd15e73d891105d310cf37422b56">GetWidth</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403439039093532"><a name="p1403439039093532"></a><a name="p1403439039093532"></a>virtual uint32_t&nbsp;</p>
<p id="p829863673093532"><a name="p829863673093532"></a><a name="p829863673093532"></a>Obtains the width of the surface. </p>
</td>
</tr>
<tr id="row772888555093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1858004803093532"><a name="p1858004803093532"></a><a name="p1858004803093532"></a><a href="Surface.md#ga0e6be0887bd69cf749c0d994bd826699">GetHeight</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p637279395093532"><a name="p637279395093532"></a><a name="p637279395093532"></a>virtual uint32_t&nbsp;</p>
<p id="p725589085093532"><a name="p725589085093532"></a><a name="p725589085093532"></a>Obtains the height of the surface. </p>
</td>
</tr>
<tr id="row298527665093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000069953093532"><a name="p1000069953093532"></a><a name="p1000069953093532"></a><a href="Surface.md#ga8e44c9100296571a9294dc9851ef48dc">SetFormat</a> (uint32_t format)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670462361093532"><a name="p1670462361093532"></a><a name="p1670462361093532"></a>virtual void&nbsp;</p>
<p id="p1252363514093532"><a name="p1252363514093532"></a><a name="p1252363514093532"></a>Sets the pixel format of the surface. For details, see <strong id="b239138981093532"><a name="b239138981093532"></a><a name="b239138981093532"></a>ImageFormat</strong>. The default pixel format is <strong id="b1831196266093532"><a name="b1831196266093532"></a><a name="b1831196266093532"></a>IMAGE_PIXEL_FORMAT_RGB565</strong>. </p>
</td>
</tr>
<tr id="row644863730093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1305396361093532"><a name="p1305396361093532"></a><a name="p1305396361093532"></a><a href="Surface.md#ga461caa118503a471c78ea09a8403a6ec">GetFormat</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1218441689093532"><a name="p1218441689093532"></a><a name="p1218441689093532"></a>virtual uint32_t&nbsp;</p>
<p id="p7671322093532"><a name="p7671322093532"></a><a name="p7671322093532"></a>Obtains the pixel format of the surface. For details, see <strong id="b1510517894093532"><a name="b1510517894093532"></a><a name="b1510517894093532"></a>ImageFormat</strong>. The default pixel format is <strong id="b489357632093532"><a name="b489357632093532"></a><a name="b489357632093532"></a>IMAGE_PIXEL_FORMAT_RGB565</strong>. </p>
</td>
</tr>
<tr id="row1145123097093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1143987201093532"><a name="p1143987201093532"></a><a name="p1143987201093532"></a><a href="Surface.md#ga5b27f54101d9d3371038b73373c36530">SetStrideAlignment</a> (uint32_t strideAlignment)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576606717093532"><a name="p1576606717093532"></a><a name="p1576606717093532"></a>virtual void&nbsp;</p>
<p id="p1668267379093532"><a name="p1668267379093532"></a><a name="p1668267379093532"></a>Sets the number of bytes for stride alignment. </p>
</td>
</tr>
<tr id="row191345093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1435597376093532"><a name="p1435597376093532"></a><a name="p1435597376093532"></a><a href="Surface.md#ga0d5317e6a008b8fd0ee98ebd516a0e7c">GetStrideAlignment</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249255076093532"><a name="p249255076093532"></a><a name="p249255076093532"></a>virtual uint32_t&nbsp;</p>
<p id="p1952581975093532"><a name="p1952581975093532"></a><a name="p1952581975093532"></a>Obtains the number of bytes for stride alignment. By default, 4-byte aligned is used. </p>
</td>
</tr>
<tr id="row280490833093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p732117211093532"><a name="p732117211093532"></a><a name="p732117211093532"></a><a href="Surface.md#ga5aabbb48f86992494c88ee2a7d00aa09">GetStride</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1173251834093532"><a name="p1173251834093532"></a><a name="p1173251834093532"></a>virtual uint32_t&nbsp;</p>
<p id="p792436571093532"><a name="p792436571093532"></a><a name="p792436571093532"></a>Obtains the stride of the surface. </p>
</td>
</tr>
<tr id="row710929190093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p581387843093532"><a name="p581387843093532"></a><a name="p581387843093532"></a><a href="Surface.md#ga3b2391ee37e762fa0fb093585c084714">SetSize</a> (uint32_t size)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931687374093532"><a name="p931687374093532"></a><a name="p931687374093532"></a>virtual void&nbsp;</p>
<p id="p122188830093532"><a name="p122188830093532"></a><a name="p122188830093532"></a>Sets the size of the shared memory to allocate. </p>
</td>
</tr>
<tr id="row1091284037093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p338859374093532"><a name="p338859374093532"></a><a name="p338859374093532"></a><a href="Surface.md#ga88e74ff7dc0ae3beb23df3ed00a81fc9">GetSize</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501746211093532"><a name="p1501746211093532"></a><a name="p1501746211093532"></a>virtual uint32_t&nbsp;</p>
<p id="p1209196204093532"><a name="p1209196204093532"></a><a name="p1209196204093532"></a>Obtains the size of the shared memory to allocate. </p>
</td>
</tr>
<tr id="row1717514238093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024095557093532"><a name="p2024095557093532"></a><a name="p2024095557093532"></a><a href="Surface.md#ga01df6145a5fda3ba72c50258634720b8">SetUsage</a> (uint32_t usage)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296899180093532"><a name="p1296899180093532"></a><a name="p1296899180093532"></a>virtual void&nbsp;</p>
<p id="p1655545430093532"><a name="p1655545430093532"></a><a name="p1655545430093532"></a>Sets the usage scenario of the buffer. Physically contiguous memory and virtual memory (by default) are supported. By default, virtual memory is allocated. </p>
</td>
</tr>
<tr id="row577528962093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1723975487093532"><a name="p1723975487093532"></a><a name="p1723975487093532"></a><a href="Surface.md#ga6a043b41406f282339bb68c1fc4793f9">GetUsage</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1054228146093532"><a name="p1054228146093532"></a><a name="p1054228146093532"></a>virtual uint32_t&nbsp;</p>
<p id="p1836160325093532"><a name="p1836160325093532"></a><a name="p1836160325093532"></a>Obtains the usage scenario of the buffer. Physically contiguous memory and virtual memory are supported. </p>
</td>
</tr>
<tr id="row1899067623093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1607057049093532"><a name="p1607057049093532"></a><a name="p1607057049093532"></a><a href="Surface.md#gae264fef4c98719a7c34bc85442cd1a5b">SetUserData</a> (const std::string &amp;key, const std::string &amp;value)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831811300093532"><a name="p1831811300093532"></a><a name="p1831811300093532"></a>virtual void&nbsp;</p>
<p id="p252834988093532"><a name="p252834988093532"></a><a name="p252834988093532"></a>Sets surface user data, which is stored in the format of &lt;key, value&gt;. </p>
</td>
</tr>
<tr id="row144998221093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701224958093532"><a name="p701224958093532"></a><a name="p701224958093532"></a><a href="Surface.md#gadd1c8826fd3191cd5f6a52594c5ef3ba">GetUserData</a> (const std::string &amp;key)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p913573820093532"><a name="p913573820093532"></a><a name="p913573820093532"></a>virtual std::string&nbsp;</p>
<p id="p807141981093532"><a name="p807141981093532"></a><a name="p807141981093532"></a>Obtains surface user data. </p>
</td>
</tr>
<tr id="row2001355186093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1555750471093532"><a name="p1555750471093532"></a><a name="p1555750471093532"></a><a href="Surface.md#gacc46ffcd4258b2660dc6cde05854c4ac">RequestBuffer</a> (uint8_t <a href="zh-cn_topic_0000001054479509.md#gabf2fbcf6df59fd5234e9eed4db1a1804">wait</a>=0)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041074372093532"><a name="p1041074372093532"></a><a name="p1041074372093532"></a>virtual <a href="OHOS-SurfaceBuffer.md">SurfaceBuffer</a> *&nbsp;</p>
<p id="p1188218196093532"><a name="p1188218196093532"></a><a name="p1188218196093532"></a>Obtains a buffer to write data. </p>
</td>
</tr>
<tr id="row836657755093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1278375752093532"><a name="p1278375752093532"></a><a name="p1278375752093532"></a><a href="Surface.md#ga8af29f3c031c1b3effe8de7366579329">FlushBuffer</a> (<a href="OHOS-SurfaceBuffer.md">SurfaceBuffer</a> *buffer)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038438264093532"><a name="p1038438264093532"></a><a name="p1038438264093532"></a>virtual int32_t&nbsp;</p>
<p id="p1476463423093532"><a name="p1476463423093532"></a><a name="p1476463423093532"></a>Flushes a buffer to the dirty queue for consumers to use. </p>
</td>
</tr>
<tr id="row1789180531093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1284136928093532"><a name="p1284136928093532"></a><a name="p1284136928093532"></a><a href="Surface.md#ga7acd9899b1ca4eb02ed13d54c2aca0af">AcquireBuffer</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774132457093532"><a name="p1774132457093532"></a><a name="p1774132457093532"></a>virtual <a href="OHOS-SurfaceBuffer.md">SurfaceBuffer</a> *&nbsp;</p>
<p id="p1204270943093532"><a name="p1204270943093532"></a><a name="p1204270943093532"></a>Obtains a buffer. </p>
</td>
</tr>
<tr id="row1338788754093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984976531093532"><a name="p984976531093532"></a><a name="p984976531093532"></a><a href="Surface.md#ga4150c81248f516882ef120731d9abb66">ReleaseBuffer</a> (<a href="OHOS-SurfaceBuffer.md">SurfaceBuffer</a> *buffer)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034543674093532"><a name="p2034543674093532"></a><a name="p2034543674093532"></a>virtual bool&nbsp;</p>
<p id="p1877065093532"><a name="p1877065093532"></a><a name="p1877065093532"></a>Releases the consumed buffer. </p>
</td>
</tr>
<tr id="row1511001839093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1482529688093532"><a name="p1482529688093532"></a><a name="p1482529688093532"></a><a href="Surface.md#ga6bae4ebcdc4e300eb5a076054f3379e4">CancelBuffer</a> (<a href="OHOS-SurfaceBuffer.md">SurfaceBuffer</a> *buffer)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1570338137093532"><a name="p1570338137093532"></a><a name="p1570338137093532"></a>virtual void&nbsp;</p>
<p id="p1233461571093532"><a name="p1233461571093532"></a><a name="p1233461571093532"></a>Releases a buffer to the free queue. </p>
</td>
</tr>
<tr id="row2049541733093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230420480093532"><a name="p1230420480093532"></a><a name="p1230420480093532"></a><a href="Surface.md#ga4b997a5b9493ad6d2015f86766f12b02">RegisterConsumerListener</a> (<a href="OHOS-IBufferConsumerListener.md">IBufferConsumerListener</a> &amp;listener)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616547435093532"><a name="p1616547435093532"></a><a name="p1616547435093532"></a>virtual void&nbsp;</p>
<p id="p1736190772093532"><a name="p1736190772093532"></a><a name="p1736190772093532"></a>Registers a consumer listener. </p>
</td>
</tr>
<tr id="row1254780076093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1656111914093532"><a name="p1656111914093532"></a><a name="p1656111914093532"></a><a href="Surface.md#ga0f303409d32d8d2b467888bf8fdc3223">UnregisterConsumerListener</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801491020093532"><a name="p801491020093532"></a><a name="p801491020093532"></a>virtual void&nbsp;</p>
<p id="p1383416536093532"><a name="p1383416536093532"></a><a name="p1383416536093532"></a>Unregisters the consumer listener. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table761633929093532"></a>
<table><thead align="left"><tr id="row725066963093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p152890737093532"><a name="p152890737093532"></a><a name="p152890737093532"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1774298687093532"><a name="p1774298687093532"></a><a name="p1774298687093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row674356907093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p251121002093532"><a name="p251121002093532"></a><a name="p251121002093532"></a><a href="Surface.md#ga49d6a759bec670ea5a47bee4eb252ae3">CreateSurface</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2012271121093532"><a name="p2012271121093532"></a><a name="p2012271121093532"></a>static <a href="OHOS-Surface.md">Surface</a> *&nbsp;</p>
<p id="p1171887929093532"><a name="p1171887929093532"></a><a name="p1171887929093532"></a>A constructor used to create a <a href="Surface.md">Surface</a> object for consumers to use. </p>
</td>
</tr>
</tbody>
</table>

