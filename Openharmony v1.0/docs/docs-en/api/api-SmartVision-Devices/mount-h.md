# mount.h<a name="EN-US_TOPIC_0000001054829487"></a>

## **Overview**<a name="section950397658084831"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Provides functions for mounting and unmounting a file system. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2087249887084831"></a>

## Functions<a name="func-members"></a>

<a name="table1880051874084831"></a>
<table><thead align="left"><tr id="row360039547084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2144973848084831"><a name="p2144973848084831"></a><a name="p2144973848084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1764744959084831"><a name="p1764744959084831"></a><a name="p1764744959084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row183516001084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616066713084831"><a name="p1616066713084831"></a><a name="p1616066713084831"></a><a href="fs.md#gadaaf1ec8aa37137233fa25d2b3af9fc8">mount</a> (const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1969982428084831"><a name="p1969982428084831"></a><a name="p1969982428084831"></a>int </p>
<p id="p1231014681084831"><a name="p1231014681084831"></a><a name="p1231014681084831"></a>Mounts a file system. </p>
</td>
</tr>
<tr id="row570129409084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395679296084831"><a name="p1395679296084831"></a><a name="p1395679296084831"></a><a href="fs.md#ga44634cfa8bcc732c29bcdf5822095422">umount</a> (const char *target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p377772780084831"><a name="p377772780084831"></a><a name="p377772780084831"></a>int </p>
<p id="p2049370354084831"><a name="p2049370354084831"></a><a name="p2049370354084831"></a>Unmounts a file system. </p>
</td>
</tr>
<tr id="row679078840084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1018837930084831"><a name="p1018837930084831"></a><a name="p1018837930084831"></a><a href="fs.md#ga2125a021d10f7a28a66cbc9335ad826f">umount2</a> (const char *target, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1418786361084831"><a name="p1418786361084831"></a><a name="p1418786361084831"></a>int </p>
<p id="p582388988084831"><a name="p582388988084831"></a><a name="p582388988084831"></a>Unmounts a file system. </p>
</td>
</tr>
</tbody>
</table>

