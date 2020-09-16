# sigaltstack<a name="EN-US_TOPIC_0000001055358156"></a>

## **Overview**<a name="section1460711223093538"></a>

**Related Modules:**

[IPC](en-us_topic_0000001054718071.md)

**Description:**

Describes a signal stack. 

## **Summary**<a name="section1896718488093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table519160551093538"></a>
<table><thead align="left"><tr id="row568900560093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p866810110093538"><a name="p866810110093538"></a><a name="p866810110093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p765800097093538"><a name="p765800097093538"></a><a name="p765800097093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row971803527093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p921202735093538"><a name="p921202735093538"></a><a name="p921202735093538"></a><a href="sigaltstack.md#a366cdbadb5cb79396f7832690c72ad85">ss_sp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p561577636093538"><a name="p561577636093538"></a><a name="p561577636093538"></a>void * </p>
</td>
</tr>
<tr id="row340678867093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p43590876093538"><a name="p43590876093538"></a><a name="p43590876093538"></a><a href="sigaltstack.md#a173db1abf4231d1850b2595a01ebc9e2">ss_flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1659772526093538"><a name="p1659772526093538"></a><a name="p1659772526093538"></a>int </p>
</td>
</tr>
<tr id="row1986820137093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p503399544093538"><a name="p503399544093538"></a><a name="p503399544093538"></a><a href="sigaltstack.md#a0a5016360b089485d55a5ad785f5bddc">ss_size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115761274093538"><a name="p115761274093538"></a><a name="p115761274093538"></a>size_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1469922206093538"></a>

## **Field Documentation**<a name="section1287421740093538"></a>

## ss\_flags<a name="a173db1abf4231d1850b2595a01ebc9e2"></a>

```
int sigaltstack::ss_flags
```

 **Description:**

Flag 

## ss\_size<a name="a0a5016360b089485d55a5ad785f5bddc"></a>

```
size_t sigaltstack::ss_size
```

 **Description:**

Number of bytes in the signal stack 

## ss\_sp<a name="a366cdbadb5cb79396f7832690c72ad85"></a>

```
void * sigaltstack::ss_sp
```

 **Description:**

Base address of the signal stack 

