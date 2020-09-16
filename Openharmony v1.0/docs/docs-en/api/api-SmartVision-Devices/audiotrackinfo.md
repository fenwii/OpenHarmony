# AudioTrackInfo<a name="EN-US_TOPIC_0000001055678082"></a>

## **Overview**<a name="section804907645093529"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines audio track information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section907642918093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table863041384093529"></a>
<table><thead align="left"><tr id="row1903670244093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1384275741093529"><a name="p1384275741093529"></a><a name="p1384275741093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1797541461093529"><a name="p1797541461093529"></a><a name="p1797541461093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1156399812093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1388791705093529"><a name="p1388791705093529"></a><a name="p1388791705093529"></a><a href="audiotrackinfo.md#ae7b9c8bf17575184f4027cbe55b7c0a9">format</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232442678093529"><a name="p1232442678093529"></a><a name="p1232442678093529"></a><a href="format.md#gaf7ed135f15d4b218d41705bac0122ba7">CodecFormat</a> </p>
</td>
</tr>
<tr id="row941327642093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1261994728093529"><a name="p1261994728093529"></a><a name="p1261994728093529"></a><a href="audiotrackinfo.md#a87acdd081cb338b01364e1ced4c132aa">profile</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p706957491093529"><a name="p706957491093529"></a><a name="p706957491093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row1964789528093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2105056565093529"><a name="p2105056565093529"></a><a name="p2105056565093529"></a><a href="audiotrackinfo.md#a7504ddf6a446c7e157eeb015194e2db8">sampleRate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061253995093529"><a name="p2061253995093529"></a><a name="p2061253995093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row1922411288093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237150281093529"><a name="p237150281093529"></a><a name="p237150281093529"></a><a href="audiotrackinfo.md#a5a4778ebb70d50bc91f250ae6254ab26">sampleFmt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125384557093529"><a name="p2125384557093529"></a><a name="p2125384557093529"></a>uint16_t </p>
</td>
</tr>
<tr id="row882763823093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900262980093529"><a name="p1900262980093529"></a><a name="p1900262980093529"></a><a href="audiotrackinfo.md#a4468c447f3ad0673c6d06590ff764099">channels</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p868658979093529"><a name="p868658979093529"></a><a name="p868658979093529"></a>uint16_t </p>
</td>
</tr>
<tr id="row1389326953093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437874892093529"><a name="p1437874892093529"></a><a name="p1437874892093529"></a><a href="audiotrackinfo.md#a682193c30bd99445980e3a8d591bb0ae">subStreamID</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635355674093529"><a name="p635355674093529"></a><a name="p635355674093529"></a>int32_t </p>
</td>
</tr>
<tr id="row668564043093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1654632933093529"><a name="p1654632933093529"></a><a name="p1654632933093529"></a><a href="audiotrackinfo.md#a5e5683087b9272d3ee346180ca199afa">bitrate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p524801925093529"><a name="p524801925093529"></a><a name="p524801925093529"></a>uint32_t </p>
</td>
</tr>
<tr id="row1248892265093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701986930093529"><a name="p701986930093529"></a><a name="p701986930093529"></a><a href="audiotrackinfo.md#ac7d6fb077c4ef6f2c14737fef8f92ba7">language</a> [<a href="format.md#gaa70508bb1089c99f9aa3d59fcbdfa8eb">FORMAT_LANGUAGE_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403092836093529"><a name="p1403092836093529"></a><a name="p1403092836093529"></a>char </p>
</td>
</tr>
<tr id="row110365399093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p938789872093529"><a name="p938789872093529"></a><a name="p938789872093529"></a><a href="audiotrackinfo.md#a67862089989d0fae5fd35312ed5287fe">durationMs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467044613093529"><a name="p467044613093529"></a><a name="p467044613093529"></a>int64_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section515990934093529"></a>

## **Field Documentation**<a name="section426869070093529"></a>

## bitrate<a name="a5e5683087b9272d3ee346180ca199afa"></a>

```
uint32_t AudioTrackInfo::bitrate
```

 **Description:**

Audio and video bit rate 

## channels<a name="a4468c447f3ad0673c6d06590ff764099"></a>

```
uint16_t AudioTrackInfo::channels
```

 **Description:**

Number of audio channels 

## durationMs<a name="a67862089989d0fae5fd35312ed5287fe"></a>

```
int64_t AudioTrackInfo::durationMs
```

 **Description:**

Stream duration, in milliseconds 

## format<a name="ae7b9c8bf17575184f4027cbe55b7c0a9"></a>

```
[CodecFormat](format.md#gaf7ed135f15d4b218d41705bac0122ba7) AudioTrackInfo::format
```

 **Description:**

Audio encoding format. For details, see  [CodecFormat](format.md#gaf7ed135f15d4b218d41705bac0122ba7). 

## language<a name="ac7d6fb077c4ef6f2c14737fef8f92ba7"></a>

```
char AudioTrackInfo::language[[FORMAT_LANGUAGE_LEN](format.md#gaa70508bb1089c99f9aa3d59fcbdfa8eb)]
```

 **Description:**

Audio track language 

## profile<a name="a87acdd081cb338b01364e1ced4c132aa"></a>

```
uint32_t AudioTrackInfo::profile
```

 **Description:**

Audio encoding profile, for example,  **0x160\(WMAV1\)**  and  **0x161 \(WMAV2\)**. 

## sampleFmt<a name="a5a4778ebb70d50bc91f250ae6254ab26"></a>

```
uint16_t AudioTrackInfo::sampleFmt
```

 **Description:**

Data storage format of one sample in an audio channel. For details, see  [AudioSampleFmt](format.md#gadf0700999998f587f0017c4d02977b22). 

## sampleRate<a name="a7504ddf6a446c7e157eeb015194e2db8"></a>

```
uint32_t AudioTrackInfo::sampleRate
```

 **Description:**

Audio sampling rate, for example,  **8000**,  **16000**,  **24000**,  **32000**,  **11025**,  **22050**,  **441000**, and  **48000** 

## subStreamID<a name="a682193c30bd99445980e3a8d591bb0ae"></a>

```
int32_t AudioTrackInfo::subStreamID
```

 **Description:**

ID of the subsidiary audio stream, which is used when the encoding or decoding format of the primary stream is not supported for audio rendering. 

