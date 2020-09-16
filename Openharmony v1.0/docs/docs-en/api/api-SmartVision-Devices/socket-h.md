# socket.h<a name="EN-US_TOPIC_0000001055387988"></a>

## **Overview**<a name="section2068004053084832"></a>

**Related Modules:**

[NET](net.md)

**Description:**

Provides functions and data structures related to network operations. 

For example, you can use the functions to send and receive network data, manage network addresses, and convert bytes.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section735216199084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1597840261084832"></a>
<table><thead align="left"><tr id="row1407315965084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1781259210084832"><a name="p1781259210084832"></a><a name="p1781259210084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p63615027084832"><a name="p63615027084832"></a><a name="p63615027084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2139998295084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1082313746084832"><a name="p1082313746084832"></a><a name="p1082313746084832"></a><a href="sockaddr.md">sockaddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895224281084832"><a name="p1895224281084832"></a><a name="p1895224281084832"></a>Describes the socket address information. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1013651425084832"></a>
<table><thead align="left"><tr id="row689646696084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p423650521084832"><a name="p423650521084832"></a><a name="p423650521084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p288438517084832"><a name="p288438517084832"></a><a name="p288438517084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row998051946084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1195339108084832"><a name="p1195339108084832"></a><a name="p1195339108084832"></a><a href="net.md#ga92d045f6ee2f343d6b28830a9fec082e">SOL_SOCKET</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458778662084832"><a name="p1458778662084832"></a><a name="p1458778662084832"></a>Defines options for socket level. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table395948954084832"></a>
<table><thead align="left"><tr id="row2016863056084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p298285043084832"><a name="p298285043084832"></a><a name="p298285043084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1619085897084832"><a name="p1619085897084832"></a><a name="p1619085897084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row532891113084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p569882953084832"><a name="p569882953084832"></a><a name="p569882953084832"></a><a href="net.md#gaf4e0711877c45a41168ac677b0670ccd">socket</a> (int domain, int type, int protocol)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1948100992084832"><a name="p1948100992084832"></a><a name="p1948100992084832"></a>int </p>
<p id="p1569846028084832"><a name="p1569846028084832"></a><a name="p1569846028084832"></a>Creates a socket and returns its descriptor. </p>
</td>
</tr>
<tr id="row4587778084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900719512084832"><a name="p1900719512084832"></a><a name="p1900719512084832"></a><a href="net.md#ga402425b8e1ceab40ac38a949babcf1aa">shutdown</a> (int sockfd, int how)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823332696084832"><a name="p1823332696084832"></a><a name="p1823332696084832"></a>int </p>
<p id="p1183263832084832"><a name="p1183263832084832"></a><a name="p1183263832084832"></a>Shuts down a socket. </p>
</td>
</tr>
<tr id="row1467356061084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609964172084832"><a name="p609964172084832"></a><a name="p609964172084832"></a><a href="net.md#ga82199bcd81894331533a25f08e172480">bind</a> (int sockfd, const struct <a href="sockaddr.md">sockaddr</a> *addr, socklen_t addrlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543620286084832"><a name="p1543620286084832"></a><a name="p1543620286084832"></a>int </p>
<p id="p1384300129084832"><a name="p1384300129084832"></a><a name="p1384300129084832"></a>Binds a local protocol address to a socket. </p>
</td>
</tr>
<tr id="row1885572499084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1520091483084832"><a name="p1520091483084832"></a><a name="p1520091483084832"></a><a href="net.md#gacdfd99b6c59c833776412fbb0c539efb">connect</a> (int sockfd, const struct <a href="sockaddr.md">sockaddr</a> *addr, socklen_t addrlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1436571837084832"><a name="p1436571837084832"></a><a name="p1436571837084832"></a>int </p>
<p id="p979096383084832"><a name="p979096383084832"></a><a name="p979096383084832"></a>Initiates a connection to a socket. </p>
</td>
</tr>
<tr id="row438787767084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p575496306084832"><a name="p575496306084832"></a><a name="p575496306084832"></a><a href="net.md#ga5989c21d05cb17caba26cef496a7beea">listen</a> (int sockfd, int backlog)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983340708084832"><a name="p983340708084832"></a><a name="p983340708084832"></a>int </p>
<p id="p1099369125084832"><a name="p1099369125084832"></a><a name="p1099369125084832"></a>Listens for network connections. </p>
</td>
</tr>
<tr id="row722145567084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1194279431084832"><a name="p1194279431084832"></a><a name="p1194279431084832"></a><a href="net.md#ga0807af5ac9dfc2a63624e8c3e0ae95ef">accept</a> (int sockfd, struct <a href="sockaddr.md">sockaddr</a> *__restrict addr, socklen_t *__restrict addrlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1547262534084832"><a name="p1547262534084832"></a><a name="p1547262534084832"></a>int </p>
<p id="p1539022510084832"><a name="p1539022510084832"></a><a name="p1539022510084832"></a>Accepts incoming connection requests. </p>
</td>
</tr>
<tr id="row1140525635084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1721363619084832"><a name="p1721363619084832"></a><a name="p1721363619084832"></a><a href="net.md#ga62577da7dba23abb9c99cf5c2800ab24">getsockname</a> (int fd, struct <a href="sockaddr.md">sockaddr</a> *restrict addr, socklen_t *restrict len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1495950333084832"><a name="p1495950333084832"></a><a name="p1495950333084832"></a>int </p>
<p id="p320174763084832"><a name="p320174763084832"></a><a name="p320174763084832"></a>Retrieves the local address of the specified socket. </p>
</td>
</tr>
<tr id="row1247975347084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558179477084832"><a name="p558179477084832"></a><a name="p558179477084832"></a><a href="net.md#ga13d77555ad4ed62dfef0ce32dd16755c">getpeername</a> (int fd, struct <a href="sockaddr.md">sockaddr</a> *restrict addr, socklen_t *restrict len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041220186084832"><a name="p1041220186084832"></a><a name="p1041220186084832"></a>int </p>
<p id="p597691030084832"><a name="p597691030084832"></a><a name="p597691030084832"></a>Retrieves the peer address of the specified socket. </p>
</td>
</tr>
<tr id="row392969641084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p286330310084832"><a name="p286330310084832"></a><a name="p286330310084832"></a><a href="net.md#ga4053f5c8e26fd490ef54e2a0abf5c89f">send</a> (int fd, const void *buf, size_t len, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p414569668084832"><a name="p414569668084832"></a><a name="p414569668084832"></a>ssize_t </p>
<p id="p1171072615084832"><a name="p1171072615084832"></a><a name="p1171072615084832"></a>Sends data to another socket. </p>
</td>
</tr>
<tr id="row1951747278084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p729363610084832"><a name="p729363610084832"></a><a name="p729363610084832"></a><a href="net.md#ga5d049263cd0e3206b93530e68dfd7403">recv</a> (int fd, void *buf, size_t len, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2055755307084832"><a name="p2055755307084832"></a><a name="p2055755307084832"></a>ssize_t </p>
<p id="p811144429084832"><a name="p811144429084832"></a><a name="p811144429084832"></a>Receives data from another socket. </p>
</td>
</tr>
<tr id="row471728904084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p133423063084832"><a name="p133423063084832"></a><a name="p133423063084832"></a><a href="net.md#ga2587b27d2c6014c6b568a974655f41c5">sendto</a> (int fd, const void *buf, size_t len, int flags, const struct <a href="sockaddr.md">sockaddr</a> *addr, socklen_t alen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2118340887084832"><a name="p2118340887084832"></a><a name="p2118340887084832"></a>ssize_t </p>
<p id="p983125943084832"><a name="p983125943084832"></a><a name="p983125943084832"></a>Sends data to another socket. </p>
</td>
</tr>
<tr id="row1019030381084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609989964084832"><a name="p609989964084832"></a><a name="p609989964084832"></a><a href="net.md#ga3089d3ee59e26bd4def3ef870175540e">recvfrom</a> (int fd, void *__restrict buf, size_t len, int flags, struct <a href="sockaddr.md">sockaddr</a> *__restrict addr, socklen_t *__restrict alen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420927847084832"><a name="p420927847084832"></a><a name="p420927847084832"></a>ssize_t </p>
<p id="p886051972084832"><a name="p886051972084832"></a><a name="p886051972084832"></a>Receives data from a specified socket. </p>
</td>
</tr>
<tr id="row1621619633084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550910765084832"><a name="p550910765084832"></a><a name="p550910765084832"></a><a href="net.md#ga70c97d3a1eab72cba4461d66a1778570">sendmsg</a> (int fd, const struct msghdr *msg, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1249000759084832"><a name="p1249000759084832"></a><a name="p1249000759084832"></a>ssize_t </p>
<p id="p654616588084832"><a name="p654616588084832"></a><a name="p654616588084832"></a>Sends data to another socket. </p>
</td>
</tr>
<tr id="row1710125652084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1890060357084832"><a name="p1890060357084832"></a><a name="p1890060357084832"></a><a href="net.md#gaaba92f19a31c01b93e3391671a8b3dd5">recvmsg</a> (int fd, struct msghdr *msg, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p808689665084832"><a name="p808689665084832"></a><a name="p808689665084832"></a>ssize_t </p>
<p id="p1145288334084832"><a name="p1145288334084832"></a><a name="p1145288334084832"></a>Receives data from a specified socket. </p>
</td>
</tr>
<tr id="row354455595084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1923970899084832"><a name="p1923970899084832"></a><a name="p1923970899084832"></a><a href="net.md#gacfcf672e255123afb75ed4d326257073">getsockopt</a> (int fd, int level, int optname, void *__restrict optval, socklen_t *__restrict optlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106001175084832"><a name="p1106001175084832"></a><a name="p1106001175084832"></a>int </p>
<p id="p940061834084832"><a name="p940061834084832"></a><a name="p940061834084832"></a>Retrieves the socket options. </p>
</td>
</tr>
<tr id="row1608808159084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327048091084832"><a name="p1327048091084832"></a><a name="p1327048091084832"></a><a href="net.md#ga81983de50d79d797b2ac0f0d0f28953f">setsockopt</a> (int fd, int level, int optname, const void *optval, socklen_t optlen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142983490084832"><a name="p142983490084832"></a><a name="p142983490084832"></a>int </p>
<p id="p1502248886084832"><a name="p1502248886084832"></a><a name="p1502248886084832"></a>Sets the socket options. </p>
</td>
</tr>
</tbody>
</table>

