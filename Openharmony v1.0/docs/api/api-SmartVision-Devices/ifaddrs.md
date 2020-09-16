# ifaddrs<a name="ZH-CN_TOPIC_0000001054479609"></a>

## **Overview**<a name="section1153691106084843"></a>

**Related Modules:**

[NET](NET.md)

**Description:**

Defines the network interface information. 

## **Summary**<a name="section45445202084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2048728160084843"></a>
<table><thead align="left"><tr id="row1803036534084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p942735620084843"><a name="p942735620084843"></a><a name="p942735620084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p8552576084843"><a name="p8552576084843"></a><a name="p8552576084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1410566812084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740552843084843"><a name="p740552843084843"></a><a name="p740552843084843"></a><a href="ifaddrs.md#a56ad9ba85e2c8f8634b8f15fc53b6447">ifa_next</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1872848464084843"><a name="p1872848464084843"></a><a name="p1872848464084843"></a>struct <a href="ifaddrs.md">ifaddrs</a> *&nbsp;</p>
</td>
</tr>
<tr id="row225951150084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1441122085084843"><a name="p1441122085084843"></a><a name="p1441122085084843"></a><a href="ifaddrs.md#a15b0944beb947aaef5e8532635889f6f">ifa_name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108567717084843"><a name="p108567717084843"></a><a name="p108567717084843"></a>char *&nbsp;</p>
</td>
</tr>
<tr id="row1682393175084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p650192905084843"><a name="p650192905084843"></a><a name="p650192905084843"></a><a href="ifaddrs.md#a7a68b76a064a1b2474f73aac492780da">ifa_flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p296074180084843"><a name="p296074180084843"></a><a name="p296074180084843"></a>unsigned&nbsp;</p>
</td>
</tr>
<tr id="row270979596084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1223025426084843"><a name="p1223025426084843"></a><a name="p1223025426084843"></a><a href="ifaddrs.md#a12d148f51adf48cee024fc6204f42c94">ifa_addr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839082363084843"><a name="p839082363084843"></a><a name="p839082363084843"></a>struct <a href="sockaddr.md">sockaddr</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1295565672084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589339604084843"><a name="p589339604084843"></a><a name="p589339604084843"></a><a href="ifaddrs.md#acac3a8d7d40841c497bb55b9e42c41d5">ifa_netmask</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p215420655084843"><a name="p215420655084843"></a><a name="p215420655084843"></a>struct <a href="sockaddr.md">sockaddr</a> *&nbsp;</p>
</td>
</tr>
<tr id="row2140793647084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662352065084843"><a name="p662352065084843"></a><a name="p662352065084843"></a><a href="ifaddrs.md#a7298836283614a0a469c8da1eabdabb9">ifa_data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p126649336084843"><a name="p126649336084843"></a><a name="p126649336084843"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row895855655084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901642777084843"><a name="p901642777084843"></a><a name="p901642777084843"></a><a href="ifaddrs.md#add59b160fa5ec481f1f650158cc746ab">ifu_broadaddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418648238084843"><a name="p418648238084843"></a><a name="p418648238084843"></a>struct <a href="sockaddr.md">sockaddr</a> *&nbsp;</p>
</td>
</tr>
<tr id="row2002156394084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91623292084843"><a name="p91623292084843"></a><a name="p91623292084843"></a><a href="ifaddrs.md#a67a6b7d90d3648e32752c8251cfce98a">ifu_dstaddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867267049084843"><a name="p867267049084843"></a><a name="p867267049084843"></a>struct <a href="sockaddr.md">sockaddr</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1142764682084843"></a>

## **Field Documentation**<a name="section1265003291084843"></a>

## ifa\_addr<a name="a12d148f51adf48cee024fc6204f42c94"></a>

```
struct [sockaddr](sockaddr.md)* ifaddrs::ifa_addr
```

 **Description:**

Interface address 

## ifa\_data<a name="a7298836283614a0a469c8da1eabdabb9"></a>

```
void* ifaddrs::ifa_data
```

 **Description:**

Address-specific data 

## ifa\_flags<a name="a7a68b76a064a1b2474f73aac492780da"></a>

```
unsigned ifaddrs::ifa_flags
```

 **Description:**

Interface flag 

## ifa\_name<a name="a15b0944beb947aaef5e8532635889f6f"></a>

```
char* ifaddrs::ifa_name
```

 **Description:**

Interface name 

## ifa\_netmask<a name="acac3a8d7d40841c497bb55b9e42c41d5"></a>

```
struct [sockaddr](sockaddr.md)* ifaddrs::ifa_netmask
```

 **Description:**

Interface netmask 

## ifa\_next<a name="a56ad9ba85e2c8f8634b8f15fc53b6447"></a>

```
struct [ifaddrs](ifaddrs.md)* ifaddrs::ifa_next
```

 **Description:**

Next item in the linked list 

## ifu\_broadaddr<a name="add59b160fa5ec481f1f650158cc746ab"></a>

```
struct [sockaddr](sockaddr.md)* ifaddrs::ifu_broadaddr
```

 **Description:**

Broadcast address associated with  **ifa\_addr** 

## ifu\_dstaddr<a name="a67a6b7d90d3648e32752c8251cfce98a"></a>

```
struct [sockaddr](sockaddr.md)* ifaddrs::ifu_dstaddr
```

 **Description:**

Destination address of the point-to-point interface 

