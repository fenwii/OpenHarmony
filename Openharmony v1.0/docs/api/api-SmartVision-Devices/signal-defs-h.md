# signal-defs.h<a name="ZH-CN_TOPIC_0000001054652829"></a>

## **Overview**<a name="section1988048498113029"></a>

**Related Modules:**

[IPC](IPC.md)

**Description:**

Defines the structures and macros for signal operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1170114853113029"></a>

## Macros<a name="define-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="IPC.md#ga927f6ae16379576d638006c7498ac5d7">SIG_BLOCK</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="IPC.md#ga5fcd73313a63dac2cc7eb3b654215250">SIG_UNBLOCK</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="IPC.md#ga37750b78b7ae75fe02ad26e70f6cc845">SIG_SETMASK</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="IPC.md#ga27d5dc561093d6243542e6a2465bc0f8">SIG_DFL</a>&nbsp;&nbsp;&nbsp;((__sighandler_t)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="IPC.md#gacf0e499b0ac946b366b4f47a3b3e8b9e">SIG_IGN</a>&nbsp;&nbsp;&nbsp;((__sighandler_t)1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="IPC.md#ga3c330fbddd84bf34e65af370b11998d6">SIG_ERR</a>&nbsp;&nbsp;&nbsp;((__sighandler_t)-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
</tbody>
</table>

