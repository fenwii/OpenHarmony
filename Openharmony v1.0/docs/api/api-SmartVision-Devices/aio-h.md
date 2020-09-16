# aio.h<a name="ZH-CN_TOPIC_0000001054909426"></a>

## **Overview**<a name="section150181007084828"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Declares functions related to asynchronous I/O \(AIO\) operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1017143857084828"></a>

## Macros<a name="define-members"></a>

<a name="table1676876048084828"></a>
<table><thead align="left"><tr id="row964714561084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1219254963084828"><a name="p1219254963084828"></a><a name="p1219254963084828"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1157828587084828"><a name="p1157828587084828"></a><a name="p1157828587084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row316375022084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p622953120084828"><a name="p622953120084828"></a><a name="p622953120084828"></a><a href="IO.md#ga6643367cfb016dbacaef01c4ef3706b0">LIO_WAIT</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2101977395084828"><a name="p2101977395084828"></a><a name="p2101977395084828"></a>Waiting to be notified of the completion of all asynchronous I/O operations. </p>
</td>
</tr>
<tr id="row1521640475084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265192024084828"><a name="p1265192024084828"></a><a name="p1265192024084828"></a><a href="IO.md#gaed8f2a06da21fad02bfc0e5749a8ecca">LIO_NOWAIT</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45180535084828"><a name="p45180535084828"></a><a name="p45180535084828"></a>Not waiting to be notified of the completion of all asynchronous I/O operations. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table45129762084828"></a>
<table><thead align="left"><tr id="row804990874084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p434568179084828"><a name="p434568179084828"></a><a name="p434568179084828"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1857415988084828"><a name="p1857415988084828"></a><a name="p1857415988084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1033583675084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p690155071084828"><a name="p690155071084828"></a><a name="p690155071084828"></a><a href="IO.md#gae15ea0aaa18c5f007c3933085749ecaf">lio_listio</a> (int mode, struct aiocb *restrict const *restrict cbs, int cnt, struct <a href="sigevent.md">sigevent</a> *restrict sev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592923034084828"><a name="p1592923034084828"></a><a name="p1592923034084828"></a>int&nbsp;</p>
<p id="p1119296659084828"><a name="p1119296659084828"></a><a name="p1119296659084828"></a>Initiates AIO requests. </p>
</td>
</tr>
</tbody>
</table>

