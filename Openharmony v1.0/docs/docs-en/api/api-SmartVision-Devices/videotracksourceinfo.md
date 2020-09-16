# VideoTrackSourceInfo<a name="EN-US_TOPIC_0000001055518130"></a>

## **Overview**<a name="section655139360093537"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines information about the muxer video source. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1677668574093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table997332110093537"></a>
<table><thead align="left"><tr id="row115978624093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1108549647093537"><a name="p1108549647093537"></a><a name="p1108549647093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1739890424093537"><a name="p1739890424093537"></a><a name="p1739890424093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row27159422093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410175968093537"><a name="p410175968093537"></a><a name="p410175968093537"></a><a href="videotracksourceinfo.md#af5da9e75ec58525d973015237eda6dfc">codecType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1171586800093537"><a name="p1171586800093537"></a><a name="p1171586800093537"></a><a href="format.md#gaf7ed135f15d4b218d41705bac0122ba7">CodecFormat</a> </p>
</td>
</tr>
<tr id="row471597590093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1019037259093537"><a name="p1019037259093537"></a><a name="p1019037259093537"></a><a href="videotracksourceinfo.md#ac05a648fdbc7902c8845b9784398ec70">width</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p183343325093537"><a name="p183343325093537"></a><a name="p183343325093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row1933167959093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772936989093537"><a name="p1772936989093537"></a><a name="p1772936989093537"></a><a href="videotracksourceinfo.md#a97aff725ec37d360cd3dee5a0050d597">height</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1364612259093537"><a name="p1364612259093537"></a><a name="p1364612259093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row488996519093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1240290311093537"><a name="p1240290311093537"></a><a name="p1240290311093537"></a><a href="videotracksourceinfo.md#a61809ef1608eedcd1cb62b53a835acb2">bitRate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p741017820093537"><a name="p741017820093537"></a><a name="p741017820093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row772070835093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092698588093537"><a name="p2092698588093537"></a><a name="p2092698588093537"></a><a href="videotracksourceinfo.md#ad73d656b0f478e287b305609bc831f52">frameRate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052281700093537"><a name="p1052281700093537"></a><a name="p1052281700093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row1001741889093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1473002503093537"><a name="p1473002503093537"></a><a name="p1473002503093537"></a><a href="videotracksourceinfo.md#a2485907934d8d174860dcb915c8cbef7">speed</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733431677093537"><a name="p733431677093537"></a><a name="p733431677093537"></a>float </p>
</td>
</tr>
<tr id="row172136864093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1835191114093537"><a name="p1835191114093537"></a><a name="p1835191114093537"></a><a href="videotracksourceinfo.md#a645143b2ac9d6de335300c62aec4c73e">keyFrameInterval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211816260093537"><a name="p211816260093537"></a><a name="p211816260093537"></a>uint32_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section452771114093537"></a>

## **Field Documentation**<a name="section1835561952093537"></a>

## bitRate<a name="a61809ef1608eedcd1cb62b53a835acb2"></a>

```
uint32_t VideoTrackSourceInfo::bitRate
```

 **Description:**

Encoding bit rate, in bit/s 

## codecType<a name="af5da9e75ec58525d973015237eda6dfc"></a>

```
[CodecFormat](format.md#gaf7ed135f15d4b218d41705bac0122ba7) VideoTrackSourceInfo::codecType
```

 **Description:**

Video encoding type, for details, see  [CodecFormat](format.md#gaf7ed135f15d4b218d41705bac0122ba7). 

## frameRate<a name="ad73d656b0f478e287b305609bc831f52"></a>

```
uint32_t VideoTrackSourceInfo::frameRate
```

 **Description:**

Encoding frame rate 

## height<a name="a97aff725ec37d360cd3dee5a0050d597"></a>

```
uint32_t VideoTrackSourceInfo::height
```

 **Description:**

Video height 

## keyFrameInterval<a name="a645143b2ac9d6de335300c62aec4c73e"></a>

```
uint32_t VideoTrackSourceInfo::keyFrameInterval
```

 **Description:**

Keyframe interval 

## speed<a name="a2485907934d8d174860dcb915c8cbef7"></a>

```
float VideoTrackSourceInfo::speed
```

 **Description:**

Video speed 

## width<a name="ac05a648fdbc7902c8845b9784398ec70"></a>

```
uint32_t VideoTrackSourceInfo::width
```

 **Description:**

Video width 

