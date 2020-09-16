# WifiIotI2cData<a name="ZH-CN_TOPIC_0000001055075081"></a>

## **Overview**<a name="section1157782469191903"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Defines I2C data transmission attributes. 

## **Summary**<a name="section1664079675191903"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1990019212191903"></a>
<table><thead align="left"><tr id="row248937326191903"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p844502911191903"><a name="p844502911191903"></a><a name="p844502911191903"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1438198270191903"><a name="p1438198270191903"></a><a name="p1438198270191903"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1782715688191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269916338191903"><a name="p269916338191903"></a><a name="p269916338191903"></a><a href="WifiIotI2cData.md#a14f3216d056d4af9ae1fc616086bc348">sendBuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1626381521191903"><a name="p1626381521191903"></a><a name="p1626381521191903"></a>unsigned char *&nbsp;</p>
</td>
</tr>
<tr id="row392987194191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228122691191903"><a name="p228122691191903"></a><a name="p228122691191903"></a><a href="WifiIotI2cData.md#a4b89d01c60fd122b59c68045d6fe21c2">sendLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366677715191903"><a name="p366677715191903"></a><a name="p366677715191903"></a>unsigned int&nbsp;</p>
</td>
</tr>
<tr id="row389948038191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1592623603191903"><a name="p1592623603191903"></a><a name="p1592623603191903"></a><a href="WifiIotI2cData.md#aa22d85c572f7fa7d032c038c8b7960b1">receiveBuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p605102066191903"><a name="p605102066191903"></a><a name="p605102066191903"></a>unsigned char *&nbsp;</p>
</td>
</tr>
<tr id="row596681031191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p373084833191903"><a name="p373084833191903"></a><a name="p373084833191903"></a><a href="WifiIotI2cData.md#ad4059d524c9deae8cd1e7ff0d429b5e4">receiveLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p742738787191903"><a name="p742738787191903"></a><a name="p742738787191903"></a>unsigned int&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1779698233191903"></a>

## **Field Documentation**<a name="section1520851422191903"></a>

## receiveBuf<a name="aa22d85c572f7fa7d032c038c8b7960b1"></a>

```
unsigned char* WifiIotI2cData::receiveBuf
```

 **Description:**

Pointer to the buffer for storing data to receive 

## receiveLen<a name="ad4059d524c9deae8cd1e7ff0d429b5e4"></a>

```
unsigned int WifiIotI2cData::receiveLen
```

 **Description:**

Length of data received 

## sendBuf<a name="a14f3216d056d4af9ae1fc616086bc348"></a>

```
unsigned char* WifiIotI2cData::sendBuf
```

 **Description:**

Pointer to the buffer storing data to send 

## sendLen<a name="a4b89d01c60fd122b59c68045d6fe21c2"></a>

```
unsigned int WifiIotI2cData::sendLen
```

 **Description:**

Length of data to send 

