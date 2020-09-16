# LayerInfo<a name="EN-US_TOPIC_0000001055518096"></a>

## **Overview**<a name="section1264606618093531"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Defines layer information. 

**[LayerInfo](layerinfo.md)**  must be passed to the  **OpenLayer**  function, which creates a layer based on the layer information. 

## **Summary**<a name="section1870171467093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table904868816093531"></a>
<table><thead align="left"><tr id="row185746262093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p244968993093531"><a name="p244968993093531"></a><a name="p244968993093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1668134281093531"><a name="p1668134281093531"></a><a name="p1668134281093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row881025986093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1035373795093531"><a name="p1035373795093531"></a><a name="p1035373795093531"></a><a href="layerinfo.md#a31b0ef7b0a83950c56dd1cafd20c9509">width</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1623027565093531"><a name="p1623027565093531"></a><a name="p1623027565093531"></a>int32_t </p>
</td>
</tr>
<tr id="row1490866696093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319639760093531"><a name="p319639760093531"></a><a name="p319639760093531"></a><a href="layerinfo.md#aab83825af07139338b4536e45fe6d8fc">height</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p239054000093531"><a name="p239054000093531"></a><a name="p239054000093531"></a>int32_t </p>
</td>
</tr>
<tr id="row650418085093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307759698093531"><a name="p1307759698093531"></a><a name="p1307759698093531"></a><a href="layerinfo.md#ade3a008d2aeccc966c226a60eb59e7ae">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p750077504093531"><a name="p750077504093531"></a><a name="p750077504093531"></a><a href="display.md#ga56943a0946e5f15e5e58054b8e7a04a4">LayerType</a> </p>
</td>
</tr>
<tr id="row1944786613093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1635381137093531"><a name="p1635381137093531"></a><a name="p1635381137093531"></a><a href="layerinfo.md#abf13f41732fac1713e51ab377c27922a">bpp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366860117093531"><a name="p366860117093531"></a><a name="p366860117093531"></a>int32_t </p>
</td>
</tr>
<tr id="row292436078093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1679559454093531"><a name="p1679559454093531"></a><a name="p1679559454093531"></a><a href="layerinfo.md#a3a05038829a72f6afa87d504712f9117">pixFormat</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p227543467093531"><a name="p227543467093531"></a><a name="p227543467093531"></a><a href="codec.md#ga60883d4958a60b91661e97027a85072a">PixelFormat</a> </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section54143905093531"></a>

## **Field Documentation**<a name="section479015316093531"></a>

## bpp<a name="abf13f41732fac1713e51ab377c27922a"></a>

```
int32_t LayerInfo::bpp
```

 **Description:**

Number of bits occupied by each pixel 

## height<a name="aab83825af07139338b4536e45fe6d8fc"></a>

```
int32_t LayerInfo::height
```

 **Description:**

Layer height 

## pixFormat<a name="a3a05038829a72f6afa87d504712f9117"></a>

```
[PixelFormat](codec.md#ga60883d4958a60b91661e97027a85072a) LayerInfo::pixFormat
```

 **Description:**

Pixel format of the layer 

## type<a name="ade3a008d2aeccc966c226a60eb59e7ae"></a>

```
[LayerType](display.md#ga56943a0946e5f15e5e58054b8e7a04a4) LayerInfo::type
```

 **Description:**

Layer type, which can be a graphics layer, overlay layer, and sideband layer 

## width<a name="a31b0ef7b0a83950c56dd1cafd20c9509"></a>

```
int32_t LayerInfo::width
```

 **Description:**

Layer width 

