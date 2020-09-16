# poll.h<a name="ZH-CN_TOPIC_0000001055387986"></a>

## **Overview**<a name="section23611824084831"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Declares I/O multiplexing functions. 

You can use the functions provided in this file to perform I/O multiplexing.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section270526204084831"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1723262006084831"></a>
<table><thead align="left"><tr id="row1379732849084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p723064932084831"><a name="p723064932084831"></a><a name="p723064932084831"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p933996839084831"><a name="p933996839084831"></a><a name="p933996839084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row135582303084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p614788875084831"><a name="p614788875084831"></a><a name="p614788875084831"></a><a href="pollfd.md">pollfd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594296747084831"><a name="p594296747084831"></a><a name="p594296747084831"></a>Defines I/O multiplexing. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table136845372084831"></a>
<table><thead align="left"><tr id="row1242806501084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1409192004084831"><a name="p1409192004084831"></a><a name="p1409192004084831"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1782074499084831"><a name="p1782074499084831"></a><a name="p1782074499084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row13990384084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038096644084831"><a name="p2038096644084831"></a><a name="p2038096644084831"></a><a href="IO.md#ga52ac479a805051f59643588b096024ff">POLLIN</a>&nbsp;&nbsp;&nbsp;0x001</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010727647084831"><a name="p2010727647084831"></a><a name="p2010727647084831"></a>POLLIN event. </p>
</td>
</tr>
<tr id="row165781509084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530771067084831"><a name="p530771067084831"></a><a name="p530771067084831"></a><a href="IO.md#gab6f53b89c7a4cc5e8349f7c778d85168">POLLPRI</a>&nbsp;&nbsp;&nbsp;0x002</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2059889376084831"><a name="p2059889376084831"></a><a name="p2059889376084831"></a>POLLPRI event. </p>
</td>
</tr>
<tr id="row809329740084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p569114367084831"><a name="p569114367084831"></a><a name="p569114367084831"></a><a href="IO.md#ga91b3c67129ac7675062f316b840a0d58">POLLOUT</a>&nbsp;&nbsp;&nbsp;0x004</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159914654084831"><a name="p159914654084831"></a><a name="p159914654084831"></a>POLLOUT event. </p>
</td>
</tr>
<tr id="row1922831126084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1059884369084831"><a name="p1059884369084831"></a><a name="p1059884369084831"></a><a href="IO.md#gab1c532446408c98559d4aaaeeeb99820">POLLERR</a>&nbsp;&nbsp;&nbsp;0x008</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309758794084831"><a name="p309758794084831"></a><a name="p309758794084831"></a>POLLERR event. </p>
</td>
</tr>
<tr id="row1685851733084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524516434084831"><a name="p524516434084831"></a><a name="p524516434084831"></a><a href="IO.md#ga262754fe6bdf27c2cd3da43284ec8536">POLLHUP</a>&nbsp;&nbsp;&nbsp;0x010</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1188359125084831"><a name="p1188359125084831"></a><a name="p1188359125084831"></a>POLLHUP event. </p>
</td>
</tr>
<tr id="row1761466911084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577896970084831"><a name="p577896970084831"></a><a name="p577896970084831"></a><a href="IO.md#gae8bffe35c61e12fb7b408b89721896df">POLLNVAL</a>&nbsp;&nbsp;&nbsp;0x020</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1257184357084831"><a name="p1257184357084831"></a><a name="p1257184357084831"></a>POLLNVAL event. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table200212197084831"></a>
<table><thead align="left"><tr id="row638960660084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2126020600084831"><a name="p2126020600084831"></a><a name="p2126020600084831"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p783246120084831"><a name="p783246120084831"></a><a name="p783246120084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1904372426084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p461282185084831"><a name="p461282185084831"></a><a name="p461282185084831"></a><a href="IO.md#ga0af7a8bdafcd5532e620a11f0d373d52">nfds_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1637920123084831"><a name="p1637920123084831"></a><a name="p1637920123084831"></a> typedef unsigned long&nbsp;</p>
<p id="p880001995084831"><a name="p880001995084831"></a><a name="p880001995084831"></a>Number of poll types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1882542699084831"></a>
<table><thead align="left"><tr id="row516352891084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2106622109084831"><a name="p2106622109084831"></a><a name="p2106622109084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2061409297084831"><a name="p2061409297084831"></a><a name="p2061409297084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row262795612084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p433001383084831"><a name="p433001383084831"></a><a name="p433001383084831"></a><a href="IO.md#gab7fc0f6be5f13c81de180c1288ba3b6f">poll</a> (struct <a href="pollfd.md">pollfd</a> fds[], <a href="IO.md#ga0af7a8bdafcd5532e620a11f0d373d52">nfds_t</a> nfds, int timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388145736084831"><a name="p388145736084831"></a><a name="p388145736084831"></a>int&nbsp;</p>
<p id="p1199668049084831"><a name="p1199668049084831"></a><a name="p1199668049084831"></a>Defines the I/O multiplexing system. </p>
</td>
</tr>
</tbody>
</table>

