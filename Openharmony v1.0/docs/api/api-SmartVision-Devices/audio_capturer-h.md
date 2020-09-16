# audio\_capturer.h<a name="ZH-CN_TOPIC_0000001054879490"></a>

## **Overview**<a name="section585267214093523"></a>

**Related Modules:**

[MultiMedia\_AudioCapturer](MultiMedia_AudioCapturer.md)

**Description:**

Provides the  **AudioCapturer**  class to implement operations related to audio capture. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1435349005093523"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table255356889093523"></a>
<table><thead align="left"><tr id="row1760682352093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1869747732093523"><a name="p1869747732093523"></a><a name="p1869747732093523"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1771112337093523"><a name="p1771112337093523"></a><a name="p1771112337093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row496992606093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p167417118093523"><a name="p167417118093523"></a><a name="p167417118093523"></a><a href="OHOS-Audio-AudioCapturerInfo.md">OHOS::Audio::AudioCapturerInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1852513880093523"><a name="p1852513880093523"></a><a name="p1852513880093523"></a>Defines information about audio capture parameters, including the input source, audio codec format,sampling rate (Hz), number of audio channels, bit rate, and bit width. </p>
</td>
</tr>
<tr id="row676053365093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p216583466093523"><a name="p216583466093523"></a><a name="p216583466093523"></a><a href="OHOS-Audio-Timestamp.md">OHOS::Audio::Timestamp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p97279505093523"><a name="p97279505093523"></a><a name="p97279505093523"></a>Represents timestamp information, including the frame position information and high-resolution time source. </p>
</td>
</tr>
<tr id="row1112199466093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1345917941093523"><a name="p1345917941093523"></a><a name="p1345917941093523"></a><a href="OHOS-Audio-AudioCapturer.md">OHOS::Audio::AudioCapturer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1936719024093523"><a name="p1936719024093523"></a><a name="p1936719024093523"></a>Provides functions for applications to implement audio capturing. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table35360353093523"></a>
<table><thead align="left"><tr id="row1613883737093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p72101178093523"><a name="p72101178093523"></a><a name="p72101178093523"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2073735579093523"><a name="p2073735579093523"></a><a name="p2073735579093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1401047342093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p807196218093523"><a name="p807196218093523"></a><a name="p807196218093523"></a><a href="MultiMedia_AudioCapturer.md#ga3d8d6798a2346e57e241d16da673d508">OHOS::Audio::State</a> : uint32_t { <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508a368f9c124fa478d643e6b3884bd4931c">OHOS::Audio::PREPPARED</a>, <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508a6d83cfbb144468bcd7f1d0609ba1a401">OHOS::Audio::RECORDING</a>, <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508abc10d40a09b83e61c72dd68daa457399">OHOS::Audio::STOPPED</a>, <a href="MultiMedia_AudioCapturer.md#gga3d8d6798a2346e57e241d16da673d508ab061f3539998a6bcec9b4c11357b5ff2">OHOS::Audio::RELEASED</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989031296093523"><a name="p1989031296093523"></a><a name="p1989031296093523"></a>Enumerates the recording states of the current device. </p>
</td>
</tr>
</tbody>
</table>

