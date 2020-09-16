# inet.h<a name="ZH-CN_TOPIC_0000001055069406"></a>

## **Overview**<a name="section499227211084830"></a>

**Related Modules:**

[NET](NET.md)

**Description:**

Provides functions and data structures related to network operations. 

For example, you can use the functions to send and receive network data, manage network addresses, and convert bytes.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1704814592084830"></a>

## Functions<a name="func-members"></a>

<a name="table824018120084830"></a>
<table><thead align="left"><tr id="row1215150845084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p486113305084830"><a name="p486113305084830"></a><a name="p486113305084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2046172098084830"><a name="p2046172098084830"></a><a name="p2046172098084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1939430463084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851677098084830"><a name="p1851677098084830"></a><a name="p1851677098084830"></a><a href="NET.md#gac7eed08cd3b67f42bf56063157c8fd55">htonl</a> (uint32_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p358234067084830"><a name="p358234067084830"></a><a name="p358234067084830"></a>uint32_t&nbsp;</p>
<p id="p20271588084830"><a name="p20271588084830"></a><a name="p20271588084830"></a>Converts an integer from the host byte order to the network byte order. </p>
</td>
</tr>
<tr id="row1855094244084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091665870084830"><a name="p1091665870084830"></a><a name="p1091665870084830"></a><a href="NET.md#gaabce0f8d453c3380e5b8a3d4947eb48c">htons</a> (uint16_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1754212086084830"><a name="p1754212086084830"></a><a name="p1754212086084830"></a>uint16_t&nbsp;</p>
<p id="p984757828084830"><a name="p984757828084830"></a><a name="p984757828084830"></a>Converts a 16-bit integer from the host byte order to the network byte order. </p>
</td>
</tr>
<tr id="row704694683084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616507597084830"><a name="p1616507597084830"></a><a name="p1616507597084830"></a><a href="NET.md#gae68530d41f32dfef707f20b2bbaa5a44">ntohl</a> (uint32_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1573502634084830"><a name="p1573502634084830"></a><a name="p1573502634084830"></a>uint32_t&nbsp;</p>
<p id="p245608330084830"><a name="p245608330084830"></a><a name="p245608330084830"></a>Converts an integer from the network byte order to the host byte order. </p>
</td>
</tr>
<tr id="row1482167919084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331446154084830"><a name="p331446154084830"></a><a name="p331446154084830"></a><a href="NET.md#gaf8c87af507c59bd8fef112e5e35fe537">ntohs</a> (uint16_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051670506084830"><a name="p2051670506084830"></a><a name="p2051670506084830"></a>uint16_t&nbsp;</p>
<p id="p1358367288084830"><a name="p1358367288084830"></a><a name="p1358367288084830"></a>Converts a 16-bit integer from the network byte order to the host byte order. </p>
</td>
</tr>
<tr id="row188502024084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112041676084830"><a name="p112041676084830"></a><a name="p112041676084830"></a><a href="NET.md#ga617651ec952a1f4c9cbddbf78f4b2e2e">inet_addr</a> (const char *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083944410084830"><a name="p2083944410084830"></a><a name="p2083944410084830"></a>in_addr_t&nbsp;</p>
<p id="p1653197234084830"><a name="p1653197234084830"></a><a name="p1653197234084830"></a>Converts a string from the IPv4 numbers-and-dots notation to the binary data in network byte order. </p>
</td>
</tr>
<tr id="row588864733084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618929517084830"><a name="p618929517084830"></a><a name="p618929517084830"></a><a href="NET.md#ga6f478437c4810fce89cf0e77d94181f8">inet_network</a> (const char *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p560801436084830"><a name="p560801436084830"></a><a name="p560801436084830"></a>in_addr_t&nbsp;</p>
<p id="p748145253084830"><a name="p748145253084830"></a><a name="p748145253084830"></a>Converts a string from the IPv4 numbers-and-dots notation to the binary data in host byte order. </p>
</td>
</tr>
<tr id="row1990410781084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1145214085084830"><a name="p1145214085084830"></a><a name="p1145214085084830"></a><a href="NET.md#ga08b9fff487151e004d9862cbf34a51ad">inet_ntoa</a> (struct in_addr in)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p771982371084830"><a name="p771982371084830"></a><a name="p771982371084830"></a>char *&nbsp;</p>
<p id="p1376324366084830"><a name="p1376324366084830"></a><a name="p1376324366084830"></a>Converts a network address to a string in dotted-decimal format. </p>
</td>
</tr>
<tr id="row1741167084084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1017359147084830"><a name="p1017359147084830"></a><a name="p1017359147084830"></a><a href="NET.md#ga3f6e2b2dae98a409d77c6e3b0cebc04b">inet_pton</a> (int af, const char *__restrict s, void *__restrict a0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206378410084830"><a name="p1206378410084830"></a><a name="p1206378410084830"></a>int&nbsp;</p>
<p id="p391296804084830"><a name="p391296804084830"></a><a name="p391296804084830"></a>Converts a string to a network address in the specified address family. </p>
</td>
</tr>
<tr id="row1826872287084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697630088084830"><a name="p697630088084830"></a><a name="p697630088084830"></a><a href="NET.md#gae9a2182ca3255f16723adeea14665b55">inet_ntop</a> (int af, const void *restrict a0, char *restrict s, socklen_t l)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924880344084830"><a name="p924880344084830"></a><a name="p924880344084830"></a>const char *&nbsp;</p>
<p id="p866869098084830"><a name="p866869098084830"></a><a name="p866869098084830"></a>Converts a network address in the specified address family to a string. </p>
</td>
</tr>
<tr id="row73247357084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p54687755084830"><a name="p54687755084830"></a><a name="p54687755084830"></a><a href="NET.md#ga26ee8e8e3949699a9c0e02ece272d370">inet_aton</a> (const char *s0, struct in_addr *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157531350084830"><a name="p157531350084830"></a><a name="p157531350084830"></a>int&nbsp;</p>
<p id="p1914301095084830"><a name="p1914301095084830"></a><a name="p1914301095084830"></a>Converts an IP address from the string format to the 32-bit binary format in network byte order. </p>
</td>
</tr>
<tr id="row970781287084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703695374084830"><a name="p703695374084830"></a><a name="p703695374084830"></a><a href="NET.md#gab28732d1d740597f53fb65a09d97800c">inet_makeaddr</a> (in_addr_t n, in_addr_t h)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021907234084830"><a name="p1021907234084830"></a><a name="p1021907234084830"></a>struct in_addr&nbsp;</p>
<p id="p859413553084830"><a name="p859413553084830"></a><a name="p859413553084830"></a>Converts the network number and host address to the network address. </p>
</td>
</tr>
<tr id="row558937714084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1672811058084830"><a name="p1672811058084830"></a><a name="p1672811058084830"></a><a href="NET.md#ga1facb1380b7657ca9c72fb2633b60e3b">inet_lnaof</a> (struct in_addr in)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p144989569084830"><a name="p144989569084830"></a><a name="p144989569084830"></a>in_addr_t&nbsp;</p>
<p id="p638709695084830"><a name="p638709695084830"></a><a name="p638709695084830"></a>Converts an IP address into a host ID in host byte order without network bits. </p>
</td>
</tr>
<tr id="row1936110789084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p10209375084830"><a name="p10209375084830"></a><a name="p10209375084830"></a><a href="NET.md#ga3a96aa4e6abe8e6959ea63fe338174dd">inet_netof</a> (struct in_addr in)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1407482099084830"><a name="p1407482099084830"></a><a name="p1407482099084830"></a>in_addr_t&nbsp;</p>
<p id="p778278999084830"><a name="p778278999084830"></a><a name="p778278999084830"></a>Extracts the network number from the <strong id="b1572027303084830"><a name="b1572027303084830"></a><a name="b1572027303084830"></a>in_addr</strong> structure and converts it to the host byte order. </p>
</td>
</tr>
</tbody>
</table>

