# mqueue.h<a name="ZH-CN_TOPIC_0000001055707980"></a>

## **Overview**<a name="section1290059545084831"></a>

**Related Modules:**

[IPC](IPC.md)

**Description:**

Provides message queue operation functions and related structures. 

For example, you can use the functions to create, open, close, delete, read, and write a message queue, and to obtain and set its attributes.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section158166769084831"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table177271205084831"></a>
<table><thead align="left"><tr id="row1357532096084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1126610916084831"><a name="p1126610916084831"></a><a name="p1126610916084831"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p598848476084831"><a name="p598848476084831"></a><a name="p598848476084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1623340061084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1853045994084831"><a name="p1853045994084831"></a><a name="p1853045994084831"></a><a href="mq_attr.md">mq_attr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1589392064084831"><a name="p1589392064084831"></a><a name="p1589392064084831"></a>Describes message queue attributes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table645909514084831"></a>
<table><thead align="left"><tr id="row1586553151084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p557343322084831"><a name="p557343322084831"></a><a name="p557343322084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p542346034084831"><a name="p542346034084831"></a><a name="p542346034084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row528002848084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963714008084831"><a name="p963714008084831"></a><a name="p963714008084831"></a><a href="IPC.md#ga3fbd3906296be63451c64d69be2bc371">mq_close</a> (mqd_t mqdes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1652431109084831"><a name="p1652431109084831"></a><a name="p1652431109084831"></a>int&nbsp;</p>
<p id="p156856598084831"><a name="p156856598084831"></a><a name="p156856598084831"></a>Closes a message queue that is no longer used. </p>
</td>
</tr>
<tr id="row1749386662084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164735842084831"><a name="p164735842084831"></a><a name="p164735842084831"></a><a href="IPC.md#ga8fafe8b1183830322f8ff875f4e6cb4c">mq_getattr</a> (mqd_t mqdes, struct <a href="mq_attr.md">mq_attr</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839744025084831"><a name="p839744025084831"></a><a name="p839744025084831"></a>int&nbsp;</p>
<p id="p1347121667084831"><a name="p1347121667084831"></a><a name="p1347121667084831"></a>Obtains the attributes of the message queue specified by the descriptor. The values of <strong id="b851114650084831"><a name="b851114650084831"></a><a name="b851114650084831"></a>mq_maxmsg</strong>, <strong id="b612149861084831"><a name="b612149861084831"></a><a name="b612149861084831"></a>mq_msgsize</strong>, and <strong id="b1334984659084831"><a name="b1334984659084831"></a><a name="b1334984659084831"></a>mq_curmsgs</strong> are fixed. </p>
</td>
</tr>
<tr id="row1837364552084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509502087084831"><a name="p1509502087084831"></a><a name="p1509502087084831"></a><a href="IPC.md#gaf5d8bf423701bd1783849119511381a5">mq_open</a> (const char *name, int oflag,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388697709084831"><a name="p388697709084831"></a><a name="p388697709084831"></a>mqd_t&nbsp;</p>
<p id="p304639038084831"><a name="p304639038084831"></a><a name="p304639038084831"></a>Creates a message queue or opens an existing message queue. </p>
</td>
</tr>
<tr id="row1351135507084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p492271851084831"><a name="p492271851084831"></a><a name="p492271851084831"></a><a href="IPC.md#gafcd715bf914289ca502136ef7022eab7">mq_receive</a> (mqd_t mqdes, char *buffer, size_t size, unsigned *prioptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1624789446084831"><a name="p1624789446084831"></a><a name="p1624789446084831"></a>ssize_t&nbsp;</p>
<p id="p393717103084831"><a name="p393717103084831"></a><a name="p393717103084831"></a>Receives a message from a specified message queue. </p>
</td>
</tr>
<tr id="row1898195847084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1407021360084831"><a name="p1407021360084831"></a><a name="p1407021360084831"></a><a href="IPC.md#ga2d07e256d809a61bdc82178cb0dd1ba1">mq_send</a> (mqd_t mqdes, const char *buffer, size_t size, unsigned prio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740878554084831"><a name="p740878554084831"></a><a name="p740878554084831"></a>int&nbsp;</p>
<p id="p245727963084831"><a name="p245727963084831"></a><a name="p245727963084831"></a>Sends a message to a specified message queue. </p>
</td>
</tr>
<tr id="row1800643802084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1847885701084831"><a name="p1847885701084831"></a><a name="p1847885701084831"></a><a href="IPC.md#gaf5cc07adf7823fac8611200b55fc3a27">mq_setattr</a> (mqd_t mqdes, const struct <a href="mq_attr.md">mq_attr</a> *__restrict newattr, struct <a href="mq_attr.md">mq_attr</a> *__restrict oldattr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p986131364084831"><a name="p986131364084831"></a><a name="p986131364084831"></a>int&nbsp;</p>
<p id="p1356206786084831"><a name="p1356206786084831"></a><a name="p1356206786084831"></a>Sets the attributes of the message queue specified by the descriptor. The <strong id="b966759745084831"><a name="b966759745084831"></a><a name="b966759745084831"></a>mq_maxmsg</strong>, <strong id="b823855711084831"><a name="b823855711084831"></a><a name="b823855711084831"></a>mq_msgsize</strong>, and <strong id="b375667004084831"><a name="b375667004084831"></a><a name="b375667004084831"></a>mq_curmsgs</strong> attributes cannot be modified. <strong id="b1129072592084831"><a name="b1129072592084831"></a><a name="b1129072592084831"></a>mq_flags</strong> supports the <strong id="b1720479062084831"><a name="b1720479062084831"></a><a name="b1720479062084831"></a>O_NONBLOCK</strong> attribute only. </p>
</td>
</tr>
<tr id="row1970642142084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1238632493084831"><a name="p1238632493084831"></a><a name="p1238632493084831"></a><a href="IPC.md#gaa291cc1bc8bb02fd24bd0d4c563350f4">mq_timedreceive</a> (mqd_t mqdes, char *__restrict buffer, size_t size, unsigned *__restrict prioptr, const struct <a href="timespec.md">timespec</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p251191204084831"><a name="p251191204084831"></a><a name="p251191204084831"></a>ssize_t&nbsp;</p>
<p id="p515032415084831"><a name="p515032415084831"></a><a name="p515032415084831"></a>Receives a message from the message queue, with a timeout period specified. </p>
</td>
</tr>
<tr id="row703504034084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911150045084831"><a name="p1911150045084831"></a><a name="p1911150045084831"></a><a href="IPC.md#gae59709d01cc34d009edfeae9900568cb">mq_timedsend</a> (mqd_t mqdes, const char *buffer, size_t size, unsigned prio, const struct <a href="timespec.md">timespec</a> *timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313176928084831"><a name="p1313176928084831"></a><a name="p1313176928084831"></a>int&nbsp;</p>
<p id="p946847412084831"><a name="p946847412084831"></a><a name="p946847412084831"></a>Sends a message to a specified message queue, with a timeout period specified. </p>
</td>
</tr>
<tr id="row2127330527084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p551784950084831"><a name="p551784950084831"></a><a name="p551784950084831"></a><a href="IPC.md#gaccd8c5ee36e60d990963e1d544ef4140">mq_unlink</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443714017084831"><a name="p443714017084831"></a><a name="p443714017084831"></a>int&nbsp;</p>
<p id="p775559004084831"><a name="p775559004084831"></a><a name="p775559004084831"></a>Decreases the reference count of the message queue by 1, or deletes the message queue if the reference count is <strong id="b855150720084831"><a name="b855150720084831"></a><a name="b855150720084831"></a>0</strong>. </p>
</td>
</tr>
</tbody>
</table>

