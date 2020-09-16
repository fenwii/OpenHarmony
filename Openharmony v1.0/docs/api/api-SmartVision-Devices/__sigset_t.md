# \_\_sigset\_t<a name="ZH-CN_TOPIC_0000001054479607"></a>

## **Overview**<a name="section1104558195093537"></a>

**Related Modules:**

[IPC](zh-cn_topic_0000001054718071.md)

**Description:**

Defines a signal set. 

## **Summary**<a name="section683411226093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table819217554093537"></a>
<table><thead align="left"><tr id="row20271024093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1218916989093537"><a name="p1218916989093537"></a><a name="p1218916989093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2029807298093537"><a name="p2029807298093537"></a><a name="p2029807298093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1048737231093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620315964093537"><a name="p1620315964093537"></a><a name="p1620315964093537"></a><a href="__sigset_t.md#a2a5e8eb9ceb28a1898295eaa235bd28b">__bits</a> [128/sizeof(long)]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580814190093537"><a name="p580814190093537"></a><a name="p580814190093537"></a>unsigned long&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1952406966093537"></a>

## **Field Documentation**<a name="section1622338388093537"></a>

## \_\_bits<a name="a2a5e8eb9ceb28a1898295eaa235bd28b"></a>

```
unsigned long __sigset_t::__bits[128/sizeof(long)]
```

 **Description:**

Saves signals in the signal set. 

