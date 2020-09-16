# pollfd<a name="ZH-CN_TOPIC_0000001055678140"></a>

## **Overview**<a name="section1068338001093538"></a>

**Related Modules:**

[IO](zh-cn_topic_0000001054799545.md)

**Description:**

Defines I/O multiplexing. 

This structure is used to describe the content during I/O multiplexing, including the file descriptor, event mask, and returned event mask. 

## **Summary**<a name="section370009542093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1071595730093538"></a>
<table><thead align="left"><tr id="row1215897561093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p873790722093538"><a name="p873790722093538"></a><a name="p873790722093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p314903502093538"><a name="p314903502093538"></a><a name="p314903502093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1003810035093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1347236539093538"><a name="p1347236539093538"></a><a name="p1347236539093538"></a><a href="pollfd.md#a57e1c316fb063e468d680b6246147861">fd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487561159093538"><a name="p1487561159093538"></a><a name="p1487561159093538"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row982464530093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179164005093538"><a name="p179164005093538"></a><a name="p179164005093538"></a><a href="pollfd.md#ac9b2f2c5b1f9a7487eb57e67cd4960ef">events</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743569576093538"><a name="p743569576093538"></a><a name="p743569576093538"></a>short&nbsp;</p>
</td>
</tr>
<tr id="row140477975093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2061225483093538"><a name="p2061225483093538"></a><a name="p2061225483093538"></a><a href="pollfd.md#aafb457d11cac415faf0e1e2b825118c2">revents</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932232730093538"><a name="p1932232730093538"></a><a name="p1932232730093538"></a>short&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1569340034093538"></a>

## **Field Documentation**<a name="section2043469424093538"></a>

## events<a name="ac9b2f2c5b1f9a7487eb57e67cd4960ef"></a>

```
short pollfd::events
```

 **Description:**

Event mask to be queried 

## fd<a name="a57e1c316fb063e468d680b6246147861"></a>

```
int pollfd::fd
```

 **Description:**

File descriptor 

## revents<a name="aafb457d11cac415faf0e1e2b825118c2"></a>

```
short pollfd::revents
```

 **Description:**

Returned event mask 

