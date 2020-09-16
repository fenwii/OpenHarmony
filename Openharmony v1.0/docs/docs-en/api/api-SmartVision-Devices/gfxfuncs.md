# GfxFuncs<a name="EN-US_TOPIC_0000001054598159"></a>

## **Overview**<a name="section1692081820084835"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Defines pointers to the hardware acceleration driver functions. 

## **Summary**<a name="section1979735469084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table315619937084835"></a>
<table><thead align="left"><tr id="row164160593084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1260655168084835"><a name="p1260655168084835"></a><a name="p1260655168084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p563441671084835"><a name="p563441671084835"></a><a name="p563441671084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row551454499084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p646342832084835"><a name="p646342832084835"></a><a name="p646342832084835"></a><a href="gfxfuncs.md#a3ec8ed6a467ed0c88e4dd723723c0f41">InitGfx</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p589022657084835"><a name="p589022657084835"></a><a name="p589022657084835"></a>int32_t(* </p>
<p id="p897803474084835"><a name="p897803474084835"></a><a name="p897803474084835"></a>Initializes hardware acceleration. </p>
</td>
</tr>
<tr id="row528678647084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p132228034084835"><a name="p132228034084835"></a><a name="p132228034084835"></a><a href="gfxfuncs.md#ad86b127aad2a6e7f01e07b77054d42b3">DeinitGfx</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499570929084835"><a name="p499570929084835"></a><a name="p499570929084835"></a>int32_t(* </p>
<p id="p816048766084835"><a name="p816048766084835"></a><a name="p816048766084835"></a>Deinitializes hardware acceleration. </p>
</td>
</tr>
<tr id="row595936201084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886503085084835"><a name="p1886503085084835"></a><a name="p1886503085084835"></a><a href="gfxfuncs.md#a12cf050a4c0d76f9816008fb102c7330">FillRect</a> )(<a href="isurface.md">ISurface</a> *surface, <a href="irect.md">IRect</a> *rect, uint32_t color, <a href="gfxopt.md">GfxOpt</a> *opt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1347586351084835"><a name="p1347586351084835"></a><a name="p1347586351084835"></a>int32_t(* </p>
<p id="p1494029984084835"><a name="p1494029984084835"></a><a name="p1494029984084835"></a>Fills a rectangle with a given color on the canvas. </p>
</td>
</tr>
<tr id="row661245350084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873560516084835"><a name="p1873560516084835"></a><a name="p1873560516084835"></a><a href="gfxfuncs.md#a96785cdbc636179fc51026fc589cac17">DrawRectangle</a> )(<a href="isurface.md">ISurface</a> *surface, <a href="rectangle.md">Rectangle</a> *rect, uint32_t color, <a href="gfxopt.md">GfxOpt</a> *opt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1961276135084835"><a name="p1961276135084835"></a><a name="p1961276135084835"></a>int32_t(* </p>
<p id="p1295787407084835"><a name="p1295787407084835"></a><a name="p1295787407084835"></a>Draws a rectangle with a given color on the canvas. </p>
</td>
</tr>
<tr id="row1581253459084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247269388084835"><a name="p1247269388084835"></a><a name="p1247269388084835"></a><a href="gfxfuncs.md#a5715347b14918e0dca51a9fd7b3d1a47">DrawLine</a> )(<a href="isurface.md">ISurface</a> *surface, <a href="iline.md">ILine</a> *line, <a href="gfxopt.md">GfxOpt</a> *opt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262267717084835"><a name="p262267717084835"></a><a name="p262267717084835"></a>int32_t(* </p>
<p id="p1858797511084835"><a name="p1858797511084835"></a><a name="p1858797511084835"></a>Draws a straight line with a given color on the canvas. </p>
</td>
</tr>
<tr id="row1148831372084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1591361529084835"><a name="p1591361529084835"></a><a name="p1591361529084835"></a><a href="gfxfuncs.md#acac8893b6bf7ab9abdad1b563c4ab6f2">DrawCircle</a> )(<a href="isurface.md">ISurface</a> *surface, <a href="icircle.md">ICircle</a> *circle, <a href="gfxopt.md">GfxOpt</a> *opt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2070982312084835"><a name="p2070982312084835"></a><a name="p2070982312084835"></a>int32_t(* </p>
<p id="p944801451084835"><a name="p944801451084835"></a><a name="p944801451084835"></a>Draws a circle with a specified center and radius on the canvas using a given color. </p>
</td>
</tr>
<tr id="row926652612084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1134528666084835"><a name="p1134528666084835"></a><a name="p1134528666084835"></a><a href="gfxfuncs.md#ab5bf93f23b73413e7aa7618a202364d7">Blit</a> )(<a href="isurface.md">ISurface</a> *srcSurface, <a href="irect.md">IRect</a> *srcRect, <a href="isurface.md">ISurface</a> *dstSurface, <a href="irect.md">IRect</a> *dstRect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383115218084835"><a name="p1383115218084835"></a><a name="p1383115218084835"></a>int32_t(* </p>
<p id="p695435953084835"><a name="p695435953084835"></a><a name="p695435953084835"></a>Blits bitmaps. </p>
</td>
</tr>
<tr id="row668643925084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047155763084835"><a name="p1047155763084835"></a><a name="p1047155763084835"></a><a href="gfxfuncs.md#aa1d93d9b5bc48cf48acb358ef531998a">Sync</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p310727155084835"><a name="p310727155084835"></a><a name="p310727155084835"></a>int32_t(* </p>
<p id="p1900997975084835"><a name="p1900997975084835"></a><a name="p1900997975084835"></a>Synchronizes hardware acceleration. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1124477260084835"></a>

## **Field Documentation**<a name="section469781073084835"></a>

## Blit<a name="ab5bf93f23b73413e7aa7618a202364d7"></a>

```
int32_t(* GfxFuncs::Blit) ([ISurface](isurface.md) *srcSurface, [IRect](irect.md) *srcRect, [ISurface](isurface.md) *dstSurface, [IRect](irect.md) *dstRect)
```

 **Description:**

Blits bitmaps. 

During bit blit, color space conversion \(CSC\), scaling, and rotation can be implemented.

**Parameters:**

<a name="table35743969084835"></a>
<table><thead align="left"><tr id="row9751102084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p736868013084835"><a name="p736868013084835"></a><a name="p736868013084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2070167761084835"><a name="p2070167761084835"></a><a name="p2070167761084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row878903506084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">srcSurface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the source bitmap. </td>
</tr>
<tr id="row1942501765084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">srcRect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the rectangle of the source bitmap. </td>
</tr>
<tr id="row1167908527084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dstSurface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the destination bitmap. </td>
</tr>
<tr id="row1325894623084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dstRect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the rectangle of the destination bitmap.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

Blit3 



## DeinitGfx<a name="ad86b127aad2a6e7f01e07b77054d42b3"></a>

```
int32_t(* GfxFuncs::DeinitGfx) (void)
```

 **Description:**

Deinitializes hardware acceleration. 

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[InitGfx](gfxfuncs.md#a3ec8ed6a467ed0c88e4dd723723c0f41) 

## DrawCircle<a name="acac8893b6bf7ab9abdad1b563c4ab6f2"></a>

```
int32_t(* GfxFuncs::DrawCircle) ([ISurface](isurface.md) *surface, [ICircle](icircle.md) *circle, [GfxOpt](gfxopt.md) *opt)
```

 **Description:**

Draws a circle with a specified center and radius on the canvas using a given color. 

**Parameters:**

<a name="table1650913588084835"></a>
<table><thead align="left"><tr id="row1975650700084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p471024255084835"><a name="p471024255084835"></a><a name="p471024255084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1229423242084835"><a name="p1229423242084835"></a><a name="p1229423242084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1966178516084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">surface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the canvas. </td>
</tr>
<tr id="row1929826260084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">circle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the circle to draw. </td>
</tr>
<tr id="row1386404507084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">opt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the hardware acceleration option.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## DrawLine<a name="a5715347b14918e0dca51a9fd7b3d1a47"></a>

```
int32_t(* GfxFuncs::DrawLine) ([ISurface](isurface.md) *surface, [ILine](iline.md) *line, [GfxOpt](gfxopt.md) *opt)
```

 **Description:**

Draws a straight line with a given color on the canvas. 

**Parameters:**

<a name="table1099685095084835"></a>
<table><thead align="left"><tr id="row1835557669084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1039175337084835"><a name="p1039175337084835"></a><a name="p1039175337084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p102611519084835"><a name="p102611519084835"></a><a name="p102611519084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1758959445084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">surface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the canvas. </td>
</tr>
<tr id="row1018170212084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">line</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the line to draw. </td>
</tr>
<tr id="row982680004084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">opt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the hardware acceleration option.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## DrawRectangle<a name="a96785cdbc636179fc51026fc589cac17"></a>

```
int32_t(* GfxFuncs::DrawRectangle) ([ISurface](isurface.md) *surface, [Rectangle](rectangle.md) *rect, uint32_t color, [GfxOpt](gfxopt.md) *opt)
```

 **Description:**

Draws a rectangle with a given color on the canvas. 

**Parameters:**

<a name="table794762730084835"></a>
<table><thead align="left"><tr id="row901255751084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2017189491084835"><a name="p2017189491084835"></a><a name="p2017189491084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1733050524084835"><a name="p1733050524084835"></a><a name="p1733050524084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1285787689084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">surface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the canvas. </td>
</tr>
<tr id="row1872821647084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the rectangle to draw. </td>
</tr>
<tr id="row2109589299084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">color</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the color to draw. </td>
</tr>
<tr id="row1111424588084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">opt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the hardware acceleration option.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[FillRect](gfxfuncs.md#a12cf050a4c0d76f9816008fb102c7330) 

## FillRect<a name="a12cf050a4c0d76f9816008fb102c7330"></a>

```
int32_t(* GfxFuncs::FillRect) ([ISurface](isurface.md) *surface, [IRect](irect.md) *rect, uint32_t color, [GfxOpt](gfxopt.md) *opt)
```

 **Description:**

Fills a rectangle with a given color on the canvas. 

**Parameters:**

<a name="table741426697084835"></a>
<table><thead align="left"><tr id="row1361261945084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1492856638084835"><a name="p1492856638084835"></a><a name="p1492856638084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1578509480084835"><a name="p1578509480084835"></a><a name="p1578509480084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row336842570084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">surface</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the canvas. </td>
</tr>
<tr id="row2077424405084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the rectangle to fill. </td>
</tr>
<tr id="row1583448919084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">color</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the color to fill. </td>
</tr>
<tr id="row878370344084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">opt</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the hardware acceleration option.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## InitGfx<a name="a3ec8ed6a467ed0c88e4dd723723c0f41"></a>

```
int32_t(* GfxFuncs::InitGfx) (void)
```

 **Description:**

Initializes hardware acceleration. 

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[DeinitGfx](gfxfuncs.md#ad86b127aad2a6e7f01e07b77054d42b3) 

## Sync<a name="aa1d93d9b5bc48cf48acb358ef531998a"></a>

```
int32_t(* GfxFuncs::Sync) (void)
```

 **Description:**

Synchronizes hardware acceleration. 

Use this function for hardware acceleration synchronization when hardware acceleration is used to draw and blit bitmaps. This function blocks the process until hardware acceleration is complete.

**Parameters:**

<a name="table2035912666084835"></a>
<table><thead align="left"><tr id="row1207331674084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1110852902084835"><a name="p1110852902084835"></a><a name="p1110852902084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1645616939084835"><a name="p1645616939084835"></a><a name="p1645616939084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row639020581084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for hardware acceleration synchronization. The value <strong id="b1365082297084835"><a name="b1365082297084835"></a><a name="b1365082297084835"></a>0</strong> indicates no timeout, so the process waits until hardware acceleration is complete.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



