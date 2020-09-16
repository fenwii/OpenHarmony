# Source<a name="ZH-CN_TOPIC_0000001054532911"></a>

## **Overview**<a name="section2103749429113040"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Provides functions to implement source-related operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section405075257113040"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#gab9bfa209ae382e3ba5d5242e8dfe5b20">Source</a> (const std::string &amp;uri)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>&nbsp;</p>
<p>A constructor used to create a <a href="Source.md">Source</a> instance based on a specified URI. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#ga84e570aa39e0810815e3f90419b2a0f0">Source</a> (const std::string &amp;uri, const std::map&lt; std::string, std::string &gt; &amp;header)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>&nbsp;</p>
<p>A constructor used to create a <a href="Source.md">Source</a> instance based on a specified URI and header. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#gae3640fec3bb0f33f4076dc30e88dac61">Source</a> (const std::shared_ptr&lt; <a href="OHOS-Media-StreamSource.md">StreamSource</a> &gt; &amp;stream, const <a href="OHOS-Media-Format.md">Format</a> &amp;formats)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>&nbsp;</p>
<p>A constructor used to create a <a href="Source.md">Source</a> instance based on the stream source and format information. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#ga93a8f8b86a9385436f6bbce10a860770">GetSourceType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p><a href="MultiMedia_MediaCommon.md#ga4052b7b55dfd94f1d07678e79d80b507">SourceType</a>&nbsp;</p>
<p>Obtains the source type. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#ga69ed2683ce3a632f6b2295fb398e4b7b">GetSourceUri</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>const std::string &amp;&nbsp;</p>
<p>Obtains the media source URI. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#ga6bb820da4b770311efc550ad27d7ce4a">GetSourceHeader</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>const std::map&lt; std::string, std::string &gt; &amp;&nbsp;</p>
<p>Obtains the HTTP header for the media source. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#ga395325402881ad38ef40c9ebd13f174d">GetSourceStream</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>const std::shared_ptr&lt; <a href="OHOS-Media-StreamSource.md">StreamSource</a> &gt; &amp;&nbsp;</p>
<p>Obtains information about the media source stream. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_MediaCommon.md#gafbd3c732660124a1dc1d9dd0dfb51393">GetSourceStreamFormat</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>const <a href="OHOS-Media-Format.md">Format</a> &amp;&nbsp;</p>
<p>Obtains the media source stream format. </p>
</td>
</tr>
</tbody>
</table>

