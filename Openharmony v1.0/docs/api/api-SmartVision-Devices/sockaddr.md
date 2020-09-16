# sockaddr<a name="ZH-CN_TOPIC_0000001055518138"></a>

## **Overview**<a name="section1458141129084843"></a>

**Related Modules:**

[NET](NET.md)

**Description:**

Describes the socket address information. 

## **Summary**<a name="section1705386702084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table786858458084843"></a>
<table><thead align="left"><tr id="row730251168084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1247862304084843"><a name="p1247862304084843"></a><a name="p1247862304084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1548832792084843"><a name="p1548832792084843"></a><a name="p1548832792084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row551115408084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p100784832084843"><a name="p100784832084843"></a><a name="p100784832084843"></a><a href="sockaddr.md#ac6ef02e9a2e90a30218132ffd7b5a5c5">sa_family</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391401489084843"><a name="p1391401489084843"></a><a name="p1391401489084843"></a>sa_family_t&nbsp;</p>
</td>
</tr>
<tr id="row105910604084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1984758199084843"><a name="p1984758199084843"></a><a name="p1984758199084843"></a><a href="sockaddr.md#afd5d95d56d0f8959f5b56458b3b3c714">sa_data</a> [14]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422001221084843"><a name="p422001221084843"></a><a name="p422001221084843"></a>char&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1703274891084843"></a>

## **Field Documentation**<a name="section1111441486084843"></a>

## sa\_data<a name="afd5d95d56d0f8959f5b56458b3b3c714"></a>

```
char sockaddr::sa_data[14]
```

 **Description:**

Protocol address 

## sa\_family<a name="ac6ef02e9a2e90a30218132ffd7b5a5c5"></a>

```
sa_family_t sockaddr::sa_family
```

 **Description:**

Address family 

