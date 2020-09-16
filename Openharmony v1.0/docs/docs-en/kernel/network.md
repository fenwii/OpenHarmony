# Network<a name="EN-US_TOPIC_0000001051770946"></a>

## Basic Concepts <a name="section9840143083510"></a>

The network module implements basic functions of the TCP/IP protocol stack and provides the standard POSIX socket interfaces.

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>Currently, the OS uses  **lwIP**  to provide network capabilities.

## When to Use<a name="section1575885183516"></a>

For user-space development, the OpenHarmony kernel provides a set of APIs for you to implement network functionalities, including creating and disabling sockets, transmitting and receiving data, and setting network attributes, in addition to standard POSIX socket functions provided by the C library.

## Description<a name="section16351198193614"></a>

**Table  1**  Standard APIs in the C library

<a name="table89488035718"></a>
<table><thead align="left"><tr id="row1494810045717"><th class="cellrowborder" valign="top" width="15.17%" id="mcps1.2.4.1.1"><p id="p294915015578"><a name="p294915015578"></a><a name="p294915015578"></a>Header File</p>
</th>
<th class="cellrowborder" valign="top" width="50.9%" id="mcps1.2.4.1.2"><p id="p17949190205711"><a name="p17949190205711"></a><a name="p17949190205711"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="33.93%" id="mcps1.2.4.1.3"><p id="p894950175712"><a name="p894950175712"></a><a name="p894950175712"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row19501105571"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p109504011576"><a name="p109504011576"></a><a name="p109504011576"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p99508013571"><a name="p99508013571"></a><a name="p99508013571"></a>int accept(int socket, struct sockaddr *address, socklen_t *address_len)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p2095015035719"><a name="p2095015035719"></a><a name="p2095015035719"></a>Accepts incoming connection requests.</p>
</td>
</tr>
<tr id="row209508065717"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p136322417199"><a name="p136322417199"></a><a name="p136322417199"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p89509014573"><a name="p89509014573"></a><a name="p89509014573"></a>int bind(int s, const struct sockaddr *name, socklen_t namelen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p6950903575"><a name="p6950903575"></a><a name="p6950903575"></a>Binds an IP address to a socket.</p>
</td>
</tr>
<tr id="row99511100571"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p23757247194"><a name="p23757247194"></a><a name="p23757247194"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p59529055717"><a name="p59529055717"></a><a name="p59529055717"></a>int shutdown(int socket, int how)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p129527012573"><a name="p129527012573"></a><a name="p129527012573"></a>Shuts down a socket.</p>
</td>
</tr>
<tr id="row49527011574"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p0392172441910"><a name="p0392172441910"></a><a name="p0392172441910"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p29531909577"><a name="p29531909577"></a><a name="p29531909577"></a>int getpeername(int s, struct sockaddr *name, socklen_t *namelen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p119534011576"><a name="p119534011576"></a><a name="p119534011576"></a>Retrieves the peer address of the specified socket.</p>
</td>
</tr>
<tr id="row139532014576"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p34091724181911"><a name="p34091724181911"></a><a name="p34091724181911"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p616711716015"><a name="p616711716015"></a><a name="p616711716015"></a>int getsockname(int s, struct sockaddr *name, socklen_t *namelen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p181651471103"><a name="p181651471103"></a><a name="p181651471103"></a>Retrieves the local address of the specified socket.</p>
</td>
</tr>
<tr id="row695520019572"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p1842812441920"><a name="p1842812441920"></a><a name="p1842812441920"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p2016357007"><a name="p2016357007"></a><a name="p2016357007"></a>int getsockopt(int s, struct sockaddr *name, socklen_t *namelen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p1716037404"><a name="p1716037404"></a><a name="p1716037404"></a>Retrieves the socket options.</p>
</td>
</tr>
<tr id="row79551708579"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p2442224121911"><a name="p2442224121911"></a><a name="p2442224121911"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p6158671601"><a name="p6158671601"></a><a name="p6158671601"></a>int setsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p415510716015"><a name="p415510716015"></a><a name="p415510716015"></a>Sets the socket options.</p>
</td>
</tr>
<tr id="row595550165713"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p1345422415197"><a name="p1345422415197"></a><a name="p1345422415197"></a>unistd.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p19153371020"><a name="p19153371020"></a><a name="p19153371020"></a>int close(int s)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p815119715017"><a name="p815119715017"></a><a name="p815119715017"></a>Closes a socket.</p>
</td>
</tr>
<tr id="row139566085714"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p114692024121917"><a name="p114692024121917"></a><a name="p114692024121917"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p181481371010"><a name="p181481371010"></a><a name="p181481371010"></a>int connect(int s, const struct sockaddr *name, socklen_t namelen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p41455713010"><a name="p41455713010"></a><a name="p41455713010"></a>Initiates a connection to a socket.</p>
</td>
</tr>
<tr id="row89575035714"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p184811924191919"><a name="p184811924191919"></a><a name="p184811924191919"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p21421376013"><a name="p21421376013"></a><a name="p21421376013"></a>int listen(int sockfd, int backlog)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p9139271308"><a name="p9139271308"></a><a name="p9139271308"></a>Listens for network connections.</p>
</td>
</tr>
<tr id="row69581108574"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p349182412196"><a name="p349182412196"></a><a name="p349182412196"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p1813627005"><a name="p1813627005"></a><a name="p1813627005"></a>ssize_t recv(int socket, void *buffer, size_t length, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p1113318713018"><a name="p1113318713018"></a><a name="p1113318713018"></a>Receives data from another socket.</p>
</td>
</tr>
<tr id="row89591609574"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p55011249191"><a name="p55011249191"></a><a name="p55011249191"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p10131976020"><a name="p10131976020"></a><a name="p10131976020"></a>ssize_t recvmsg(int s, struct msghdr *message, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p2010837004"><a name="p2010837004"></a><a name="p2010837004"></a>Receives data from a specified socket based on the input parameters.</p>
</td>
</tr>
<tr id="row8960903574"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p1351310242192"><a name="p1351310242192"></a><a name="p1351310242192"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p310519717015"><a name="p310519717015"></a><a name="p310519717015"></a>ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p11102471608"><a name="p11102471608"></a><a name="p11102471608"></a>Receives data from a specified socket and obtains the IP address of the data source.</p>
</td>
</tr>
<tr id="row16961120195719"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p3525112420198"><a name="p3525112420198"></a><a name="p3525112420198"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p101001872009"><a name="p101001872009"></a><a name="p101001872009"></a>ssize_t send(int s, const void *dataptr, size_t size, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p197171402"><a name="p197171402"></a><a name="p197171402"></a>Sends data to another socket.</p>
</td>
</tr>
<tr id="row59620075717"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p165381324121910"><a name="p165381324121910"></a><a name="p165381324121910"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p6941671602"><a name="p6941671602"></a><a name="p6941671602"></a>ssize_t sendmsg(int s, const struct msghdr *message, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p13912710013"><a name="p13912710013"></a><a name="p13912710013"></a>Sends data to another socket based on the input parameters.</p>
</td>
</tr>
<tr id="row296213055716"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p1055242414196"><a name="p1055242414196"></a><a name="p1055242414196"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p588573013"><a name="p588573013"></a><a name="p588573013"></a>ssize_t sendto(int s, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p108612713014"><a name="p108612713014"></a><a name="p108612713014"></a>Sends data to another socket at the specified destination IP address.</p>
</td>
</tr>
<tr id="row1896320155718"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p165642024191919"><a name="p165642024191919"></a><a name="p165642024191919"></a>sys/socket.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p168413711019"><a name="p168413711019"></a><a name="p168413711019"></a>int socket(int domain, int type, int protocol)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p1278772017"><a name="p1278772017"></a><a name="p1278772017"></a>Creates a socket.</p>
</td>
</tr>
<tr id="row49644012571"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p3574152491918"><a name="p3574152491918"></a><a name="p3574152491918"></a>sys/select.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p575471204"><a name="p575471204"></a><a name="p575471204"></a>int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p6721171012"><a name="p6721171012"></a><a name="p6721171012"></a>Monitors the I/O events of multiple file descriptors.</p>
</td>
</tr>
<tr id="row1965904571"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p1958512413195"><a name="p1958512413195"></a><a name="p1958512413195"></a>sys/ioctl.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p27013715013"><a name="p27013715013"></a><a name="p27013715013"></a>int ioctl(int s, int request, ...)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p867471405"><a name="p867471405"></a><a name="p867471405"></a>Obtains and sets socket options.</p>
</td>
</tr>
<tr id="row179471552191312"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p4595192471910"><a name="p4595192471910"></a><a name="p4595192471910"></a>arpa/inet.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p189481522130"><a name="p189481522130"></a><a name="p189481522130"></a>const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p494814527138"><a name="p494814527138"></a><a name="p494814527138"></a>Converts an IP address in binary format to a string.</p>
</td>
</tr>
<tr id="row189663017574"><td class="cellrowborder" valign="top" width="15.17%" headers="mcps1.2.4.1.1 "><p id="p335556182016"><a name="p335556182016"></a><a name="p335556182016"></a>arpa/inet.h</p>
</td>
<td class="cellrowborder" valign="top" width="50.9%" headers="mcps1.2.4.1.2 "><p id="p46417716014"><a name="p46417716014"></a><a name="p46417716014"></a>int inet_pton(int af, const char *src, void *dst)</p>
</td>
<td class="cellrowborder" valign="top" width="33.93%" headers="mcps1.2.4.1.3 "><p id="p176112713010"><a name="p176112713010"></a><a name="p176112713010"></a>Converts a string to an IP address in binary format.</p>
</td>
</tr>
</tbody>
</table>

Details on API differences:

-   **sendmsg**

    **Function prototype:**

    ssize\_t sendmsg\(int s, const struct msghdr \*message, int flags\)

    **Function description:**  sends a message on a socket.

    **Parameter description:**

    <a name="table193101953145116"></a>
    <table><thead align="left"><tr id="row13311125313516"><th class="cellrowborder" valign="top" width="19.439999999999998%" id="mcps1.1.3.1.1"><p id="p19311195312510"><a name="p19311195312510"></a><a name="p19311195312510"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="80.56%" id="mcps1.1.3.1.2"><p id="p19311205313512"><a name="p19311205313512"></a><a name="p19311205313512"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row1731175316511"><td class="cellrowborder" valign="top" width="19.439999999999998%" headers="mcps1.1.3.1.1 "><p id="p153111753125118"><a name="p153111753125118"></a><a name="p153111753125118"></a>s</p>
    </td>
    <td class="cellrowborder" valign="top" width="80.56%" headers="mcps1.1.3.1.2 "><p id="p031165311519"><a name="p031165311519"></a><a name="p031165311519"></a>Indicates the socket.</p>
    </td>
    </tr>
    <tr id="row15311185317518"><td class="cellrowborder" valign="top" width="19.439999999999998%" headers="mcps1.1.3.1.1 "><p id="p7311115319516"><a name="p7311115319516"></a><a name="p7311115319516"></a>message</p>
    </td>
    <td class="cellrowborder" valign="top" width="80.56%" headers="mcps1.1.3.1.2 "><p id="p331125385118"><a name="p331125385118"></a><a name="p331125385118"></a>Indicates the pointer to the message to be sent. The ancillary message is not supported.</p>
    </td>
    </tr>
    <tr id="row63111753195116"><td class="cellrowborder" valign="top" width="19.439999999999998%" headers="mcps1.1.3.1.1 "><p id="p131175318519"><a name="p131175318519"></a><a name="p131175318519"></a>flags</p>
    </td>
    <td class="cellrowborder" valign="top" width="80.56%" headers="mcps1.1.3.1.2 "><p id="p11799112211525"><a name="p11799112211525"></a><a name="p11799112211525"></a>Indicates the socket flags for sending the message. The options are as follows:</p>
    <a name="ul1179912222521"></a><a name="ul1179912222521"></a><ul id="ul1179912222521"><li><strong id="b318752774612"><a name="b318752774612"></a><a name="b318752774612"></a>MSG_MORE</strong>: allows messages that have been sent for multiple times to be packaged and sent at a time.</li><li><strong id="b17461161555117"><a name="b17461161555117"></a><a name="b17461161555117"></a>MSG_DONTWAIT</strong>: enables a non-blocking operation.</li></ul>
    </td>
    </tr>
    </tbody>
    </table>

    **Return values:**

    -   Returns the number of bytes that have been sent if the operation is successful.
    -   Returns  **-1**  and sets  **errno**  if the operation fails.


-   **recvmsg**

    **Function prototype:**

    ssize\_t recvmsg\(int s, struct msghdr \*message, int flags\)

    **Function description:**  receives a message from a socket.

    **Parameter description:**

    <a name="table1847716407526"></a>
    <table><thead align="left"><tr id="row15477840185218"><th class="cellrowborder" valign="top" width="21.42%" id="mcps1.1.3.1.1"><p id="p8477104015217"><a name="p8477104015217"></a><a name="p8477104015217"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="78.58000000000001%" id="mcps1.1.3.1.2"><p id="p1447717402527"><a name="p1447717402527"></a><a name="p1447717402527"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row3477340125210"><td class="cellrowborder" valign="top" width="21.42%" headers="mcps1.1.3.1.1 "><p id="p154771740155218"><a name="p154771740155218"></a><a name="p154771740155218"></a>s</p>
    </td>
    <td class="cellrowborder" valign="top" width="78.58000000000001%" headers="mcps1.1.3.1.2 "><p id="p1347718402522"><a name="p1347718402522"></a><a name="p1347718402522"></a>Indicates the socket.</p>
    </td>
    </tr>
    <tr id="row174771405527"><td class="cellrowborder" valign="top" width="21.42%" headers="mcps1.1.3.1.1 "><p id="p54771440185218"><a name="p54771440185218"></a><a name="p54771440185218"></a>message</p>
    </td>
    <td class="cellrowborder" valign="top" width="78.58000000000001%" headers="mcps1.1.3.1.2 "><p id="p5477164075215"><a name="p5477164075215"></a><a name="p5477164075215"></a>Indicates the pointer to the address to receive the message. The ancillary message is not supported.</p>
    </td>
    </tr>
    <tr id="row9477174020529"><td class="cellrowborder" valign="top" width="21.42%" headers="mcps1.1.3.1.1 "><p id="p747715404521"><a name="p747715404521"></a><a name="p747715404521"></a>flags</p>
    </td>
    <td class="cellrowborder" valign="top" width="78.58000000000001%" headers="mcps1.1.3.1.2 "><p id="p99911829531"><a name="p99911829531"></a><a name="p99911829531"></a>Indicates the socket flags for receiving the message. The options are as follows:</p>
    <a name="ul1099113216538"></a><a name="ul1099113216538"></a><ul id="ul1099113216538"><li><strong id="b12913203135518"><a name="b12913203135518"></a><a name="b12913203135518"></a>MSG_PEEK</strong>: allows the message to be read without being removed.</li><li><strong id="b127217398013"><a name="b127217398013"></a><a name="b127217398013"></a>MSG_DONTWAIT</strong>: enables a non-blocking operation.</li></ul>
    </td>
    </tr>
    </tbody>
    </table>

    **Return values:**

    -   Returns the number of bytes that have been received if the operation is successful.
    -   Returns  **-1**  and sets  **errno**  if the operation fails.


-   **ioctl**

    **Function prototype:**

    int ioctl\(int s, int request, ...\)

    **Function description:**  obtains or sets socket options.

    **Parameter description:**

    <a name="table1011381714533"></a>
    <table><thead align="left"><tr id="row16113161795318"><th class="cellrowborder" valign="top" width="15.25%" id="mcps1.1.3.1.1"><p id="p1811381712530"><a name="p1811381712530"></a><a name="p1811381712530"></a>Parameter</p>
    </th>
    <th class="cellrowborder" valign="top" width="84.75%" id="mcps1.1.3.1.2"><p id="p20113161712534"><a name="p20113161712534"></a><a name="p20113161712534"></a>Description</p>
    </th>
    </tr>
    </thead>
    <tbody><tr id="row18113191735318"><td class="cellrowborder" valign="top" width="15.25%" headers="mcps1.1.3.1.1 "><p id="p9113617165312"><a name="p9113617165312"></a><a name="p9113617165312"></a>s</p>
    </td>
    <td class="cellrowborder" valign="top" width="84.75%" headers="mcps1.1.3.1.2 "><p id="p16114317145314"><a name="p16114317145314"></a><a name="p16114317145314"></a>Indicates the socket.</p>
    </td>
    </tr>
    <tr id="row5114121719536"><td class="cellrowborder" valign="top" width="15.25%" headers="mcps1.1.3.1.1 "><p id="p17114117185312"><a name="p17114117185312"></a><a name="p17114117185312"></a>request</p>
    </td>
    <td class="cellrowborder" valign="top" width="84.75%" headers="mcps1.1.3.1.2 "><p id="p137162040165319"><a name="p137162040165319"></a><a name="p137162040165319"></a>Indicates the operation to perform on the socket options. The options are as follows:</p>
    <a name="ul1671694075316"></a><a name="ul1671694075316"></a><ul id="ul1671694075316"><li><strong id="b24181736341"><a name="b24181736341"></a><a name="b24181736341"></a>FIONREAD</strong>: obtains the number of bytes of the data that can be read from the socket.</li><li><strong id="b173691420511"><a name="b173691420511"></a><a name="b173691420511"></a>FIONBIO</strong>: sets whether the socket is non-blocked.</li></ul>
    </td>
    </tr>
    </tbody>
    </table>

    **Return values:**

    -   Returns  **0**  if the operation is successful.
    -   Returns  **-1**  and sets  **errno**  if the operation fails.


