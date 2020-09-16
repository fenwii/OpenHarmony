# hostent<a name="EN-US_TOPIC_0000001055678138"></a>

## **Overview**<a name="section297468305084843"></a>

**Related Modules:**

[NET](net.md)

**Description:**

Describes the host name and address information. 

## **Summary**<a name="section951533296084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table53880578084843"></a>
<table><thead align="left"><tr id="row1744409788084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p70075613084843"><a name="p70075613084843"></a><a name="p70075613084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p573011380084843"><a name="p573011380084843"></a><a name="p573011380084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1580142621084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496002065084843"><a name="p496002065084843"></a><a name="p496002065084843"></a><a href="hostent.md#a439d6e5efa18bc14aab63b14a12ae371">h_name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1222848230084843"><a name="p1222848230084843"></a><a name="p1222848230084843"></a>char * </p>
</td>
</tr>
<tr id="row619467426084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1218427990084843"><a name="p1218427990084843"></a><a name="p1218427990084843"></a><a href="hostent.md#ac266a0b528443e9479f2d8e1680b5e78">h_aliases</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1732472969084843"><a name="p1732472969084843"></a><a name="p1732472969084843"></a>char ** </p>
</td>
</tr>
<tr id="row1480619283084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p774293488084843"><a name="p774293488084843"></a><a name="p774293488084843"></a><a href="hostent.md#a405ebb31a6922898809635b03f0faf06">h_addrtype</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1306564120084843"><a name="p1306564120084843"></a><a name="p1306564120084843"></a>int </p>
</td>
</tr>
<tr id="row243969668084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p473499894084843"><a name="p473499894084843"></a><a name="p473499894084843"></a><a href="hostent.md#ab9db18bfcc6adfc9c944b0c06ec2dccc">h_length</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1191467925084843"><a name="p1191467925084843"></a><a name="p1191467925084843"></a>int </p>
</td>
</tr>
<tr id="row936117609084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p893722168084843"><a name="p893722168084843"></a><a name="p893722168084843"></a><a href="hostent.md#a4ff8499f29c5111435d6ed4adccfb621">h_addr_list</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453688842084843"><a name="p1453688842084843"></a><a name="p1453688842084843"></a>char ** </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section77285869084843"></a>

## **Field Documentation**<a name="section1195561891084843"></a>

## h\_addr\_list<a name="a4ff8499f29c5111435d6ed4adccfb621"></a>

```
char** hostent::h_addr_list
```

 **Description:**

A pointer to an array of pointers to host addresses 

## h\_addrtype<a name="a405ebb31a6922898809635b03f0faf06"></a>

```
int hostent::h_addrtype
```

 **Description:**

IP address type 

## h\_aliases<a name="ac266a0b528443e9479f2d8e1680b5e78"></a>

```
char** hostent::h_aliases
```

 **Description:**

A pointer to an array of pointers to alternative host names 

## h\_length<a name="ab9db18bfcc6adfc9c944b0c06ec2dccc"></a>

```
int hostent::h_length
```

 **Description:**

Address length 

## h\_name<a name="a439d6e5efa18bc14aab63b14a12ae371"></a>

```
char* hostent::h_name
```

 **Description:**

A pointer to the host name 

