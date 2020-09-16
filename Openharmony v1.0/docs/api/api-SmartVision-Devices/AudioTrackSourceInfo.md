# AudioTrackSourceInfo<a name="ZH-CN_TOPIC_0000001055518078"></a>

## **Overview**<a name="section1793423480093529"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines information about the muxer audio source. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1895861114093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table390775067093529"></a>
<table><thead align="left"><tr id="row925051241093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p322533423093529"><a name="p322533423093529"></a><a name="p322533423093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p777640612093529"><a name="p777640612093529"></a><a name="p777640612093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1746888656093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p932178404093529"><a name="p932178404093529"></a><a name="p932178404093529"></a><a href="AudioTrackSourceInfo.md#abb7f5e09a8cc552aa558d8da6d45a2b7">codecType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1957845399093529"><a name="p1957845399093529"></a><a name="p1957845399093529"></a><a href="Format.md#gaf7ed135f15d4b218d41705bac0122ba7">CodecFormat</a>&nbsp;</p>
</td>
</tr>
<tr id="row2046697984093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p146712789093529"><a name="p146712789093529"></a><a name="p146712789093529"></a><a href="AudioTrackSourceInfo.md#a1853d9a135862a487c7c612862871b33">sampleRate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987839260093529"><a name="p987839260093529"></a><a name="p987839260093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row83543201093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1454175371093529"><a name="p1454175371093529"></a><a name="p1454175371093529"></a><a href="AudioTrackSourceInfo.md#a9102735a0ca74b965f1946b5a282ce49">channelCount</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032551836093529"><a name="p1032551836093529"></a><a name="p1032551836093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row128718947093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076488370093529"><a name="p2076488370093529"></a><a name="p2076488370093529"></a><a href="AudioTrackSourceInfo.md#a4d17b98a1cb944d9e401fb5ea158c72e">sampleBitWidth</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p378014238093529"><a name="p378014238093529"></a><a name="p378014238093529"></a><a href="Format.md#gadf0700999998f587f0017c4d02977b22">AudioSampleFmt</a>&nbsp;</p>
</td>
</tr>
<tr id="row389651622093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p368290494093529"><a name="p368290494093529"></a><a name="p368290494093529"></a><a href="AudioTrackSourceInfo.md#ab1878c9d95c3f20395d219c662e2ae6f">samplesPerFrame</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915342283093529"><a name="p915342283093529"></a><a name="p915342283093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1442958936093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p688473273093529"><a name="p688473273093529"></a><a name="p688473273093529"></a><a href="AudioTrackSourceInfo.md#aca750f7a7165a35cfa92a6af0c23d771">avgBytesPerSec</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1545524476093529"><a name="p1545524476093529"></a><a name="p1545524476093529"></a>uint32_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1609043273093529"></a>

## **Field Documentation**<a name="section1519138013093529"></a>

## avgBytesPerSec<a name="aca750f7a7165a35cfa92a6af0c23d771"></a>

```
uint32_t AudioTrackSourceInfo::avgBytesPerSec
```

 **Description:**

Average bit rate, in byte/s 

## channelCount<a name="a9102735a0ca74b965f1946b5a282ce49"></a>

```
uint32_t AudioTrackSourceInfo::channelCount
```

 **Description:**

Number of audio channels 

## codecType<a name="abb7f5e09a8cc552aa558d8da6d45a2b7"></a>

```
[CodecFormat](Format.md#gaf7ed135f15d4b218d41705bac0122ba7) AudioTrackSourceInfo::codecType
```

 **Description:**

Audio encoding type, for details, see  [CodecFormat](Format.md#gaf7ed135f15d4b218d41705bac0122ba7). 

## sampleBitWidth<a name="a4d17b98a1cb944d9e401fb5ea158c72e"></a>

```
[AudioSampleFmt](Format.md#gadf0700999998f587f0017c4d02977b22) AudioTrackSourceInfo::sampleBitWidth
```

 **Description:**

Bit width 

## sampleRate<a name="a1853d9a135862a487c7c612862871b33"></a>

```
uint32_t AudioTrackSourceInfo::sampleRate
```

 **Description:**

Sampling rate 

## samplesPerFrame<a name="ab1878c9d95c3f20395d219c662e2ae6f"></a>

```
uint32_t AudioTrackSourceInfo::samplesPerFrame
```

 **Description:**

Number of samples per frame 

