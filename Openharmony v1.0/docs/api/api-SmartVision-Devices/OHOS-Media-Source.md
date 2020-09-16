# OHOS::Media::Source<a name="ZH-CN_TOPIC_0000001054799611"></a>

## **Overview**<a name="section1314153436093532"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Provides functions to implement source-related operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section970211093093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1251880469093532"></a>
<table><thead align="left"><tr id="row735436161093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2146126069093532"><a name="p2146126069093532"></a><a name="p2146126069093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1751473038093532"><a name="p1751473038093532"></a><a name="p1751473038093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row789550323093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1088525372093532"><a name="p1088525372093532"></a><a name="p1088525372093532"></a><a href="MultiMedia_MediaCommon.md#gab9bfa209ae382e3ba5d5242e8dfe5b20">Source</a> (const std::string &amp;uri)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705465698093532"><a name="p1705465698093532"></a><a name="p1705465698093532"></a>&nbsp;</p>
<p id="p716363395093532"><a name="p716363395093532"></a><a name="p716363395093532"></a>A constructor used to create a <a href="OHOS-Media-Source.md">Source</a> instance based on a specified URI. </p>
</td>
</tr>
<tr id="row61546176093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271962921093532"><a name="p1271962921093532"></a><a name="p1271962921093532"></a><a href="MultiMedia_MediaCommon.md#ga84e570aa39e0810815e3f90419b2a0f0">Source</a> (const std::string &amp;uri, const std::map&lt; std::string, std::string &gt; &amp;header)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073287196093532"><a name="p2073287196093532"></a><a name="p2073287196093532"></a>&nbsp;</p>
<p id="p591730466093532"><a name="p591730466093532"></a><a name="p591730466093532"></a>A constructor used to create a <a href="OHOS-Media-Source.md">Source</a> instance based on a specified URI and header. </p>
</td>
</tr>
<tr id="row536003201093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687497800093532"><a name="p687497800093532"></a><a name="p687497800093532"></a><a href="MultiMedia_MediaCommon.md#gae3640fec3bb0f33f4076dc30e88dac61">Source</a> (const std::shared_ptr&lt; <a href="OHOS-Media-StreamSource.md">StreamSource</a> &gt; &amp;stream, const <a href="OHOS-Media-Format.md">Format</a> &amp;formats)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823412818093532"><a name="p1823412818093532"></a><a name="p1823412818093532"></a>&nbsp;</p>
<p id="p1895359359093532"><a name="p1895359359093532"></a><a name="p1895359359093532"></a>A constructor used to create a <a href="OHOS-Media-Source.md">Source</a> instance based on the stream source and format information. </p>
</td>
</tr>
<tr id="row326412187093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p849810423093532"><a name="p849810423093532"></a><a name="p849810423093532"></a><a href="MultiMedia_MediaCommon.md#ga93a8f8b86a9385436f6bbce10a860770">GetSourceType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1082129085093532"><a name="p1082129085093532"></a><a name="p1082129085093532"></a><a href="MultiMedia_MediaCommon.md#ga4052b7b55dfd94f1d07678e79d80b507">SourceType</a>&nbsp;</p>
<p id="p47903434093532"><a name="p47903434093532"></a><a name="p47903434093532"></a>Obtains the source type. </p>
</td>
</tr>
<tr id="row498595090093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256385015093532"><a name="p256385015093532"></a><a name="p256385015093532"></a><a href="MultiMedia_MediaCommon.md#ga69ed2683ce3a632f6b2295fb398e4b7b">GetSourceUri</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1145464967093532"><a name="p1145464967093532"></a><a name="p1145464967093532"></a>const std::string &amp;&nbsp;</p>
<p id="p431532433093532"><a name="p431532433093532"></a><a name="p431532433093532"></a>Obtains the media source URI. </p>
</td>
</tr>
<tr id="row1751045385093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898561815093532"><a name="p898561815093532"></a><a name="p898561815093532"></a><a href="MultiMedia_MediaCommon.md#ga6bb820da4b770311efc550ad27d7ce4a">GetSourceHeader</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p662848448093532"><a name="p662848448093532"></a><a name="p662848448093532"></a>const std::map&lt; std::string, std::string &gt; &amp;&nbsp;</p>
<p id="p944758906093532"><a name="p944758906093532"></a><a name="p944758906093532"></a>Obtains the HTTP header for the media source. </p>
</td>
</tr>
<tr id="row1258905963093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440300180093532"><a name="p440300180093532"></a><a name="p440300180093532"></a><a href="MultiMedia_MediaCommon.md#ga395325402881ad38ef40c9ebd13f174d">GetSourceStream</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p208918276093532"><a name="p208918276093532"></a><a name="p208918276093532"></a>const std::shared_ptr&lt; <a href="OHOS-Media-StreamSource.md">StreamSource</a> &gt; &amp;&nbsp;</p>
<p id="p1169766788093532"><a name="p1169766788093532"></a><a name="p1169766788093532"></a>Obtains information about the media source stream. </p>
</td>
</tr>
<tr id="row2109386448093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1365326656093532"><a name="p1365326656093532"></a><a name="p1365326656093532"></a><a href="MultiMedia_MediaCommon.md#gafbd3c732660124a1dc1d9dd0dfb51393">GetSourceStreamFormat</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p234672362093532"><a name="p234672362093532"></a><a name="p234672362093532"></a>const <a href="OHOS-Media-Format.md">Format</a> &amp;&nbsp;</p>
<p id="p1832360950093532"><a name="p1832360950093532"></a><a name="p1832360950093532"></a>Obtains the media source stream format. </p>
</td>
</tr>
</tbody>
</table>

