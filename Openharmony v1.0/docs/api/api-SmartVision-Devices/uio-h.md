# uio.h<a name="ZH-CN_TOPIC_0000001054909436"></a>

## **Overview**<a name="section1958413696084833"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Provides functions and structures related to input/output \(I/O\) to a file or buffer. 

You can use the functions provided in this file to read files to the buffer or read information from the buffer to files.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1568228698084833"></a>

## Functions<a name="func-members"></a>

<a name="table67292722084833"></a>
<table><thead align="left"><tr id="row1839212327084833"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p749819170084833"><a name="p749819170084833"></a><a name="p749819170084833"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1844508993084833"><a name="p1844508993084833"></a><a name="p1844508993084833"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row192483031084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1603613644084833"><a name="p1603613644084833"></a><a name="p1603613644084833"></a><a href="IO.md#gaa1952d693ed3c43292566e643ceb9858">readv</a> (int fd, const struct iovec *iov, int iovcnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922484154084833"><a name="p922484154084833"></a><a name="p922484154084833"></a>ssize_t&nbsp;</p>
<p id="p769354411084833"><a name="p769354411084833"></a><a name="p769354411084833"></a>Reads the data of <strong id="b2073426289084833"><a name="b2073426289084833"></a><a name="b2073426289084833"></a>fd</strong> to <strong id="b1288751199084833"><a name="b1288751199084833"></a><a name="b1288751199084833"></a>iov</strong>. </p>
</td>
</tr>
<tr id="row722201382084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p783301121084833"><a name="p783301121084833"></a><a name="p783301121084833"></a><a href="IO.md#gad57f362a0aef72b52ea59288f74dd1ea">writev</a> (int fd, const struct iovec *iov, int iovcnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481184841084833"><a name="p1481184841084833"></a><a name="p1481184841084833"></a>ssize_t&nbsp;</p>
<p id="p1792103177084833"><a name="p1792103177084833"></a><a name="p1792103177084833"></a>Writes a given length of data into a file. </p>
</td>
</tr>
<tr id="row1136210918084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p590329727084833"><a name="p590329727084833"></a><a name="p590329727084833"></a><a href="IO.md#ga94adc8dd94a6bdaaa9cf4d9f388418b3">preadv</a> (int fd, const struct iovec *iov, int iovcnt, off_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1382048568084833"><a name="p1382048568084833"></a><a name="p1382048568084833"></a>ssize_t&nbsp;</p>
<p id="p1978634881084833"><a name="p1978634881084833"></a><a name="p1978634881084833"></a>Reads the data in a file whose <strong id="b1988564612084833"><a name="b1988564612084833"></a><a name="b1988564612084833"></a>fd</strong> offset is <strong id="b2061854574084833"><a name="b2061854574084833"></a><a name="b2061854574084833"></a>offset</strong> to the multi-group buffer space pointed to by <strong id="b710320883084833"><a name="b710320883084833"></a><a name="b710320883084833"></a>iov</strong>. </p>
</td>
</tr>
<tr id="row1934060607084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1552336291084833"><a name="p1552336291084833"></a><a name="p1552336291084833"></a><a href="IO.md#ga3de6f9331d6bb930e748bb61860edbd6">pwritev</a> (int fd, const struct iovec *iov, int iovcnt, off_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p704913409084833"><a name="p704913409084833"></a><a name="p704913409084833"></a>ssize_t&nbsp;</p>
<p id="p57694973084833"><a name="p57694973084833"></a><a name="p57694973084833"></a>Writes the data of a multi-group buffer space pointed to by <strong id="b1454197725084833"><a name="b1454197725084833"></a><a name="b1454197725084833"></a>iov</strong> to the offset of <strong id="b1950188693084833"><a name="b1950188693084833"></a><a name="b1950188693084833"></a>fd</strong>. </p>
</td>
</tr>
</tbody>
</table>

