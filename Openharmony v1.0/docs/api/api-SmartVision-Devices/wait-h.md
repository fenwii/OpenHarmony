# wait.h<a name="ZH-CN_TOPIC_0000001055308041"></a>

## **Overview**<a name="section163267972084834"></a>

**Related Modules:**

[PROCESS](PROCESS.md)

**Description:**

Provides process- and thread-related structures and functions \(for example, waiting for child processes to end and reclaiming resources\). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section501337559084834"></a>

## Functions<a name="func-members"></a>

<a name="table351200089084834"></a>
<table><thead align="left"><tr id="row1980755993084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p794794045084834"><a name="p794794045084834"></a><a name="p794794045084834"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p131188127084834"><a name="p131188127084834"></a><a name="p131188127084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1760929413084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1416747338084834"><a name="p1416747338084834"></a><a name="p1416747338084834"></a><a href="PROCESS.md#gabf2fbcf6df59fd5234e9eed4db1a1804">wait</a> (int *status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1898461253084834"><a name="p1898461253084834"></a><a name="p1898461253084834"></a>pid_t&nbsp;</p>
<p id="p140286640084834"><a name="p140286640084834"></a><a name="p140286640084834"></a>Waits for any child process to end and reclaims its resources. </p>
</td>
</tr>
<tr id="row1460489530084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497355926084834"><a name="p1497355926084834"></a><a name="p1497355926084834"></a><a href="PROCESS.md#ga77de8005691d1f125540d66032a3cc62">waitpid</a> (pid_t pid, int *status, int options)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p260620552084834"><a name="p260620552084834"></a><a name="p260620552084834"></a>pid_t&nbsp;</p>
<p id="p1704086306084834"><a name="p1704086306084834"></a><a name="p1704086306084834"></a>Waits for a specified child process to end and reclaims its resources. </p>
</td>
</tr>
</tbody>
</table>

