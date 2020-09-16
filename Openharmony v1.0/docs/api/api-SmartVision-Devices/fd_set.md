# fd\_set<a name="ZH-CN_TOPIC_0000001054598205"></a>

## **Overview**<a name="section285387112084842"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Defines a file descriptor set. 

This structure is used to specify whether the file descriptor set exists. 

## **Summary**<a name="section292186290084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table746499477084842"></a>
<table><thead align="left"><tr id="row108201520084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p778114934084842"><a name="p778114934084842"></a><a name="p778114934084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2113486390084842"><a name="p2113486390084842"></a><a name="p2113486390084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row602092891084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1724468896084842"><a name="p1724468896084842"></a><a name="p1724468896084842"></a><a href="fd_set.md#af3253fd40c49cf37181639e903f16aba">fds_bits</a> [<a href="IO.md#ga86c5dbf5a99358e288f573d6a1e0873f">FD_SETSIZE</a>/8/sizeof(long)]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312313278084842"><a name="p1312313278084842"></a><a name="p1312313278084842"></a>unsigned long&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section757959966084842"></a>

## **Field Documentation**<a name="section359367446084842"></a>

## fds\_bits<a name="af3253fd40c49cf37181639e903f16aba"></a>

```
unsigned long fd_set::fds_bits[[FD_SETSIZE](IO.md#ga86c5dbf5a99358e288f573d6a1e0873f)/8/sizeof(long)]
```

 **Description:**

Whether the descriptor exists is indicated by each bit. 

