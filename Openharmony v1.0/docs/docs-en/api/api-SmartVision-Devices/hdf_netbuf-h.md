# hdf\_netbuf.h<a name="EN-US_TOPIC_0000001054479533"></a>

## **Overview**<a name="section2031683887084830"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Declares network data buffers and provides APIs for operating buffer queues. 

This file describes the following network data operations for network device driver development: Applying for, releasing, and moving a network data buffer Initializing a network data buffer queue, placing a network data buffer to a queue, and removing a network data buffer from a queue

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1761091779084830"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table804216100084830"></a>
<table><thead align="left"><tr id="row1809402544084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p704493289084830"><a name="p704493289084830"></a><a name="p704493289084830"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p305797461084830"><a name="p305797461084830"></a><a name="p305797461084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row492756947084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752045555084830"><a name="p752045555084830"></a><a name="p752045555084830"></a><a href="netbuf.md">NetBuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167495105084830"><a name="p1167495105084830"></a><a name="p1167495105084830"></a>Records and saves a network data buffer. </p>
</td>
</tr>
<tr id="row1903589401084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346264842084830"><a name="p346264842084830"></a><a name="p346264842084830"></a><a href="netbufqueue.md">NetBufQueue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2030039728084830"><a name="p2030039728084830"></a><a name="p2030039728084830"></a>Indicates the queues for storing network data. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table2120376721084830"></a>
<table><thead align="left"><tr id="row306372467084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1363899640084830"><a name="p1363899640084830"></a><a name="p1363899640084830"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1383530526084830"><a name="p1383530526084830"></a><a name="p1383530526084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row860669978084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p193126665084830"><a name="p193126665084830"></a><a name="p193126665084830"></a><a href="wlan.md#ga794c035a19a38acc000146a8f9a4ec80">MAX_NETBUF_RESEVER_SIZE</a>   68</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086000371084830"><a name="p1086000371084830"></a><a name="p1086000371084830"></a>Defines the reserved field of a network data buffer used to store private information. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table641699460084830"></a>
<table><thead align="left"><tr id="row1391135278084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p360696949084830"><a name="p360696949084830"></a><a name="p360696949084830"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1863730264084830"><a name="p1863730264084830"></a><a name="p1863730264084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row139117772084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489136239084830"><a name="p1489136239084830"></a><a name="p1489136239084830"></a>{ <a href="wlan.md#ggae4d5251432e1a9e6803c0240cc492e18a0e4808dd476b314c0fdbf417307f8b92">E_HEAD_BUF</a>, <a href="wlan.md#ggae4d5251432e1a9e6803c0240cc492e18a4b374b76d2b9bb60c31a1a540369b6d4">E_DATA_BUF</a>, <a href="wlan.md#ggae4d5251432e1a9e6803c0240cc492e18a316baeacb77ecf28631a76f1dbea872d">E_TAIL_BUF</a>, <a href="wlan.md#ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19">MAX_BUF_NUM</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291686347084830"><a name="p291686347084830"></a><a name="p291686347084830"></a>Enumerates the segments of a network data buffer. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1090204589084830"></a>
<table><thead align="left"><tr id="row1874055758084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1658913838084830"><a name="p1658913838084830"></a><a name="p1658913838084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1261207828084830"><a name="p1261207828084830"></a><a name="p1261207828084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1410530556084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1802436455084830"><a name="p1802436455084830"></a><a name="p1802436455084830"></a><a href="wlan.md#ga6e754d5529b23b413d1fe00102a95db9">NetBufQueueInit</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1553357123084830"><a name="p1553357123084830"></a><a name="p1553357123084830"></a>static void </p>
<p id="p1954915200084830"><a name="p1954915200084830"></a><a name="p1954915200084830"></a>Initializes a network data buffer queue. </p>
</td>
</tr>
<tr id="row995819684084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1590205803084830"><a name="p1590205803084830"></a><a name="p1590205803084830"></a><a href="wlan.md#gaaa5c00efd1dedecf846af4dd108b6701">NetBufQueueSize</a> (const struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p625910844084830"><a name="p625910844084830"></a><a name="p625910844084830"></a>static uint32_t </p>
<p id="p1528203006084830"><a name="p1528203006084830"></a><a name="p1528203006084830"></a>Obtains the size of a network data buffer queue. </p>
</td>
</tr>
<tr id="row991165898084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302042900084830"><a name="p302042900084830"></a><a name="p302042900084830"></a><a href="wlan.md#ga36297284c60746f2b6895d94ea5e2dc3">NetBufQueueIsEmpty</a> (const struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007612342084830"><a name="p1007612342084830"></a><a name="p1007612342084830"></a>static bool </p>
<p id="p657832703084830"><a name="p657832703084830"></a><a name="p657832703084830"></a>Checks whether the network data buffer queue is empty. </p>
</td>
</tr>
<tr id="row1773682241084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662441722084830"><a name="p1662441722084830"></a><a name="p1662441722084830"></a><a href="wlan.md#ga25bf5d56e8afec1bc80080b20c3b7daa">NetBufQueueEnqueue</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q, struct <a href="netbuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749774250084830"><a name="p749774250084830"></a><a name="p749774250084830"></a>void </p>
<p id="p251023529084830"><a name="p251023529084830"></a><a name="p251023529084830"></a>Adds a network data buffer to the tail of a queue. </p>
</td>
</tr>
<tr id="row396764396084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1033202403084830"><a name="p1033202403084830"></a><a name="p1033202403084830"></a><a href="wlan.md#ga5ebe7aff6d5187645869f067b0a8f659">NetBufQueueEnqueueHead</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q, struct <a href="netbuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477273027084830"><a name="p1477273027084830"></a><a name="p1477273027084830"></a>void </p>
<p id="p481618962084830"><a name="p481618962084830"></a><a name="p481618962084830"></a>Adds a network data buffer to the header of a queue. </p>
</td>
</tr>
<tr id="row435495855084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484873437084830"><a name="p484873437084830"></a><a name="p484873437084830"></a><a href="wlan.md#ga4ad66d7ca7aabda3aef08fa541dc9ee4">NetBufQueueDequeue</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2002588702084830"><a name="p2002588702084830"></a><a name="p2002588702084830"></a>struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p140863412084830"><a name="p140863412084830"></a><a name="p140863412084830"></a>Obtains a network data buffer from the header of a queue and deletes it from the queue. </p>
</td>
</tr>
<tr id="row536183793084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1360315015084830"><a name="p1360315015084830"></a><a name="p1360315015084830"></a><a href="wlan.md#ga390319a0419c26c73552bcee6b8d5c32">NetBufQueueDequeueTail</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1178377946084830"><a name="p1178377946084830"></a><a name="p1178377946084830"></a>struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p1615225889084830"><a name="p1615225889084830"></a><a name="p1615225889084830"></a>Obtains a network data buffer from the tail of a queue and deletes it from the queue. </p>
</td>
</tr>
<tr id="row97932756084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900553448084830"><a name="p1900553448084830"></a><a name="p1900553448084830"></a><a href="wlan.md#ga082b7a173ca09288c3b418ce4e4faa7d">NetBufQueueAtHead</a> (const struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018834823084830"><a name="p2018834823084830"></a><a name="p2018834823084830"></a>static struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p217931197084830"><a name="p217931197084830"></a><a name="p217931197084830"></a>Obtains the network data buffer from the header of a queue, without deleting it from the queue. </p>
</td>
</tr>
<tr id="row694494053084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146667009084830"><a name="p2146667009084830"></a><a name="p2146667009084830"></a><a href="wlan.md#ga9de36bf1db57bd4eb042e87cb63dae69">NetBufQueueAtTail</a> (const struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p927542750084830"><a name="p927542750084830"></a><a name="p927542750084830"></a>static struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p93424888084830"><a name="p93424888084830"></a><a name="p93424888084830"></a>Obtains the network data buffer from the tail of a queue, without deleting it from the queue. </p>
</td>
</tr>
<tr id="row1072343122084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1380231756084830"><a name="p1380231756084830"></a><a name="p1380231756084830"></a><a href="wlan.md#ga79045ebd1636c27bee454e9541498f33">NetBufQueueClear</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1292845723084830"><a name="p1292845723084830"></a><a name="p1292845723084830"></a>void </p>
<p id="p1373545309084830"><a name="p1373545309084830"></a><a name="p1373545309084830"></a>Clears a network data buffer queue and releases the network data buffer in the queue. </p>
</td>
</tr>
<tr id="row1249885891084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859137337084830"><a name="p1859137337084830"></a><a name="p1859137337084830"></a><a href="wlan.md#ga2331e6b8c8f1ac4f00f8a1206fb1a3d8">NetBufQueueConcat</a> (struct <a href="netbufqueue.md">NetBufQueue</a> *q, struct <a href="netbufqueue.md">NetBufQueue</a> *add)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p717734055084830"><a name="p717734055084830"></a><a name="p717734055084830"></a>void </p>
<p id="p167330546084830"><a name="p167330546084830"></a><a name="p167330546084830"></a>Moves all network data buffers from one queue to another and clears the source queue. </p>
</td>
</tr>
<tr id="row1179769917084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140469434084830"><a name="p1140469434084830"></a><a name="p1140469434084830"></a><a href="wlan.md#ga5ced2af63a9064b0e33d0aa4e86b3fc1">NetBufAlloc</a> (uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868165751084830"><a name="p1868165751084830"></a><a name="p1868165751084830"></a>struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p1933348750084830"><a name="p1933348750084830"></a><a name="p1933348750084830"></a>Applies for a network data buffer. </p>
</td>
</tr>
<tr id="row1061110537084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1285811158084830"><a name="p1285811158084830"></a><a name="p1285811158084830"></a><a href="wlan.md#ga9320642699593dfecd79dc30132dd4eb">NetBufFree</a> (struct <a href="netbuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1822794131084830"><a name="p1822794131084830"></a><a name="p1822794131084830"></a>void </p>
<p id="p1140213095084830"><a name="p1140213095084830"></a><a name="p1140213095084830"></a>Releases a network data buffer. </p>
</td>
</tr>
<tr id="row1659246138084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p919993090084830"><a name="p919993090084830"></a><a name="p919993090084830"></a><a href="wlan.md#ga74198f03268aadc025f6b76056b09604">NetBufDevAlloc</a> (const struct <a href="netdevice.md">NetDevice</a> *dev, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1742194318084830"><a name="p1742194318084830"></a><a name="p1742194318084830"></a>struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p841030219084830"><a name="p841030219084830"></a><a name="p841030219084830"></a>Applies for a network data buffer based on the reserved space and requested size set by a network device. </p>
</td>
</tr>
<tr id="row139089176084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719132011084830"><a name="p719132011084830"></a><a name="p719132011084830"></a><a href="wlan.md#gac4ec1cedef616e61038dcb6dbf67d204">NetBufPush</a> (struct <a href="netbuf.md">NetBuf</a> *nb, uint32_t id, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748401245084830"><a name="p748401245084830"></a><a name="p748401245084830"></a>void * </p>
<p id="p1933370676084830"><a name="p1933370676084830"></a><a name="p1933370676084830"></a>Performs operations based on the segment ID of a network data buffer. The function is opposite to that of <a href="wlan.md#ga81f298aebc5b7772f173e2f6fadc004f">NetBufPop</a>. </p>
</td>
</tr>
<tr id="row1879985743084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p358409181084830"><a name="p358409181084830"></a><a name="p358409181084830"></a><a href="wlan.md#ga81f298aebc5b7772f173e2f6fadc004f">NetBufPop</a> (struct <a href="netbuf.md">NetBuf</a> *nb, uint32_t id, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p744511676084830"><a name="p744511676084830"></a><a name="p744511676084830"></a>void * </p>
<p id="p706397001084830"><a name="p706397001084830"></a><a name="p706397001084830"></a>Performs operations based on the segment ID of a network data buffer. The function is opposite to that of <a href="wlan.md#gac4ec1cedef616e61038dcb6dbf67d204">NetBufPush</a>. </p>
</td>
</tr>
<tr id="row2065723674084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p6122860084830"><a name="p6122860084830"></a><a name="p6122860084830"></a><a href="wlan.md#gacd40d5004291b4aaa5c27703d9379c9c">NetBufGetAddress</a> (const struct <a href="netbuf.md">NetBuf</a> *nb, uint32_t id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701370972084830"><a name="p1701370972084830"></a><a name="p1701370972084830"></a>static uint8_t * </p>
<p id="p1343041350084830"><a name="p1343041350084830"></a><a name="p1343041350084830"></a>Obtains the address of a specified buffer segment in a network data buffer. </p>
</td>
</tr>
<tr id="row400592832084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p370716705084830"><a name="p370716705084830"></a><a name="p370716705084830"></a><a href="wlan.md#ga09245834fe9f55fe475a0dc226a6a709">NetBufGetRoom</a> (const struct <a href="netbuf.md">NetBuf</a> *nb, uint32_t id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266893295084830"><a name="p1266893295084830"></a><a name="p1266893295084830"></a>static uint32_t </p>
<p id="p152134116084830"><a name="p152134116084830"></a><a name="p152134116084830"></a>Obtains the size of a specified buffer segment space in a network data buffer. </p>
</td>
</tr>
<tr id="row1542354106084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1603090642084830"><a name="p1603090642084830"></a><a name="p1603090642084830"></a><a href="wlan.md#ga67eeb57ebe467b9caa4f31734955727b">NetBufGetDataLen</a> (const struct <a href="netbuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1836662798084830"><a name="p1836662798084830"></a><a name="p1836662798084830"></a>static uint32_t </p>
<p id="p1965460292084830"><a name="p1965460292084830"></a><a name="p1965460292084830"></a>Obtains the actual data length of the data segment of a network data buffer. </p>
</td>
</tr>
<tr id="row839827184084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175450291084830"><a name="p175450291084830"></a><a name="p175450291084830"></a><a href="wlan.md#ga623e0b15e65f317f746b53b9a4530bdd">NetBufResizeRoom</a> (struct <a href="netbuf.md">NetBuf</a> *nb, uint32_t head, uint32_t tail)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2115158334084830"><a name="p2115158334084830"></a><a name="p2115158334084830"></a>int32_t </p>
<p id="p680601581084830"><a name="p680601581084830"></a><a name="p680601581084830"></a>Adjusts the size of a network data buffer space. </p>
</td>
</tr>
<tr id="row514323445084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p15854358084830"><a name="p15854358084830"></a><a name="p15854358084830"></a><a href="wlan.md#ga89ee14a3da1b7b83325045af9c488ef8">NetBufConcat</a> (struct <a href="netbuf.md">NetBuf</a> *nb, struct <a href="netbuf.md">NetBuf</a> *cnb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985308129084830"><a name="p985308129084830"></a><a name="p985308129084830"></a>uint32_t </p>
<p id="p1150143583084830"><a name="p1150143583084830"></a><a name="p1150143583084830"></a>Copies data in a network data buffer to another network data buffer. </p>
</td>
</tr>
<tr id="row1164926903084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1758323319084830"><a name="p1758323319084830"></a><a name="p1758323319084830"></a><a href="wlan.md#ga8d44f8dbfa75583d0056702b5a2d32a1">Pbuf2NetBuf</a> (const struct <a href="netdevice.md">NetDevice</a> *netdev, struct pbuf *lwipBuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1114329755084830"><a name="p1114329755084830"></a><a name="p1114329755084830"></a>struct <a href="netbuf.md">NetBuf</a> * </p>
<p id="p2081363268084830"><a name="p2081363268084830"></a><a name="p2081363268084830"></a>Converts the <strong id="b634038491084830"><a name="b634038491084830"></a><a name="b634038491084830"></a>pbuf</strong> structure of Lightweight TCP/IP Stack (lwIP) to a network data buffer. </p>
</td>
</tr>
<tr id="row408820923084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9103515084830"><a name="p9103515084830"></a><a name="p9103515084830"></a><a href="wlan.md#ga88e4943fc1b1f4e31f388bf8eec57476">NetBuf2Pbuf</a> (const struct <a href="netbuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273042628084830"><a name="p1273042628084830"></a><a name="p1273042628084830"></a>struct pbuf * </p>
<p id="p1853076870084830"><a name="p1853076870084830"></a><a name="p1853076870084830"></a>Converts a network data buffer to the <strong id="b22020467084830"><a name="b22020467084830"></a><a name="b22020467084830"></a>pbuf</strong> structure of Lightweight TCP/IP Stack (lwIP). </p>
</td>
</tr>
</tbody>
</table>

