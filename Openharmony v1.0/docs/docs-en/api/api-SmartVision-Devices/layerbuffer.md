# LayerBuffer<a name="EN-US_TOPIC_0000001055039524"></a>

## **Overview**<a name="section1059549139093531"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Defines the buffer, which is used to store layer data. 

## **Summary**<a name="section1364805924093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table277587961093531"></a>
<table><thead align="left"><tr id="row1397173520093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1919188151093531"><a name="p1919188151093531"></a><a name="p1919188151093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1780899104093531"><a name="p1780899104093531"></a><a name="p1780899104093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2099654054093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778356595093531"><a name="p778356595093531"></a><a name="p778356595093531"></a><a href="layerbuffer.md#a46aa174ae3d0eb28fa7f3e53749fd5d1">fenceId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p695613308093531"><a name="p695613308093531"></a><a name="p695613308093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1610050155093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873861797093531"><a name="p1873861797093531"></a><a name="p1873861797093531"></a><a href="layerbuffer.md#a71196d704bd8a6a69b9bccf497b8224b">width</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1887112998093531"><a name="p1887112998093531"></a><a name="p1887112998093531"></a>int32_t </p>
</td>
</tr>
<tr id="row281928600093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p485368346093531"><a name="p485368346093531"></a><a name="p485368346093531"></a><a href="layerbuffer.md#aec2e142ea67776ec4e91fc3d8d3389ae">height</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342018495093531"><a name="p1342018495093531"></a><a name="p1342018495093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1191677909093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841249676093531"><a name="p841249676093531"></a><a name="p841249676093531"></a><a href="layerbuffer.md#a62a06a9381ac2d6fa48115ce7d01920d">pitch</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p975466594093531"><a name="p975466594093531"></a><a name="p975466594093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1396846638093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255899817093531"><a name="p255899817093531"></a><a name="p255899817093531"></a><a href="layerbuffer.md#a1ac426fb1997d872b347cae9cce94eb6">pixFormat</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p86476475093531"><a name="p86476475093531"></a><a name="p86476475093531"></a><a href="codec.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> </p>
</td>
</tr>
<tr id="row981512688093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988314583093531"><a name="p1988314583093531"></a><a name="p1988314583093531"></a><a href="layerbuffer.md#a9a1831091916905de22145585cf8b682">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342870480093531"><a name="p1342870480093531"></a><a name="p1342870480093531"></a><a href="bufferdata.md">BufferData</a> </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section146993515093531"></a>

## **Field Documentation**<a name="section554980737093531"></a>

## data<a name="a9a1831091916905de22145585cf8b682"></a>

```
[BufferData](bufferdata.md) LayerBuffer::data
```

 **Description:**

Layer buffer data 

## fenceId<a name="a46aa174ae3d0eb28fa7f3e53749fd5d1"></a>

```
int32_t LayerBuffer::fenceId
```

 **Description:**

Fence ID of the buffer 

## height<a name="aec2e142ea67776ec4e91fc3d8d3389ae"></a>

```
int32_t LayerBuffer::height
```

 **Description:**

Buffer height 

## pitch<a name="a62a06a9381ac2d6fa48115ce7d01920d"></a>

```
int32_t LayerBuffer::pitch
```

 **Description:**

Number of bytes from one row of pixels in memory to the next 

## pixFormat<a name="a1ac426fb1997d872b347cae9cce94eb6"></a>

```
[PixelFormat](codec.md#ga60883d4958a60b91661e97027a85072a) LayerBuffer::pixFormat
```

 **Description:**

Pixel format of the buffer 

## width<a name="a71196d704bd8a6a69b9bccf497b8224b"></a>

```
int32_t LayerBuffer::width
```

 **Description:**

Buffer width 

