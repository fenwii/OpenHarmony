# glob\_t<a name="EN-US_TOPIC_0000001054718171"></a>

## **Overview**<a name="section610754998084842"></a>

**Related Modules:**

[FS](fs.md)

**Description:**

Defines the search information. 

This structure is used to store information about matched files. 

## **Summary**<a name="section1833441792084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2100106751084842"></a>
<table><thead align="left"><tr id="row2107463414084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p448547359084842"><a name="p448547359084842"></a><a name="p448547359084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p504260849084842"><a name="p504260849084842"></a><a name="p504260849084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row536205749084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1171297856084842"><a name="p1171297856084842"></a><a name="p1171297856084842"></a><a href="glob_t.md#a69dc492f370a9793f06c11e3eb12f199">gl_pathc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1813797633084842"><a name="p1813797633084842"></a><a name="p1813797633084842"></a>size_t </p>
</td>
</tr>
<tr id="row398824629084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1228103466084842"><a name="p1228103466084842"></a><a name="p1228103466084842"></a><a href="glob_t.md#abd9ba3e5bd7a4767af2cd3dd98a2a64f">gl_pathv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p321657837084842"><a name="p321657837084842"></a><a name="p321657837084842"></a>char ** </p>
</td>
</tr>
<tr id="row1912619242084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1869477969084842"><a name="p1869477969084842"></a><a name="p1869477969084842"></a><a href="glob_t.md#ada6945e8f6ca53ecf82c9d736fb5307e">gl_offs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1873684322084842"><a name="p1873684322084842"></a><a name="p1873684322084842"></a>size_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section667313865084842"></a>

## **Field Documentation**<a name="section1300123413084842"></a>

## gl\_offs<a name="ada6945e8f6ca53ecf82c9d736fb5307e"></a>

```
size_t glob_t::gl_offs
```

 **Description:**

Slots to reserve in  **gl\_pathv** 

## gl\_pathc<a name="a69dc492f370a9793f06c11e3eb12f199"></a>

```
size_t glob_t::gl_pathc
```

 **Description:**

Number of matched paths so far 

## gl\_pathv<a name="abd9ba3e5bd7a4767af2cd3dd98a2a64f"></a>

```
char** glob_t::gl_pathv
```

 **Description:**

List of matched path names 

