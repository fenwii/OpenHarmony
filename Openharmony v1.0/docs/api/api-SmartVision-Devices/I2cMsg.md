# I2cMsg<a name="ZH-CN_TOPIC_0000001054918161"></a>

## **Overview**<a name="section1031387868093531"></a>

**Related Modules:**

[I2C](I2C.md)

**Description:**

Defines the I2C transfer message used during custom transfers. 

**Since:**

1.0

## **Summary**<a name="section864407268093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1074804782093531"></a>
<table><thead align="left"><tr id="row1999970168093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298445345093531"><a name="p1298445345093531"></a><a name="p1298445345093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2102822043093531"><a name="p2102822043093531"></a><a name="p2102822043093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1107694212093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1092213066093531"><a name="p1092213066093531"></a><a name="p1092213066093531"></a><a href="I2cMsg.md#a8f9fae2a615957552b2c409b868e91cd">addr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p696158384093531"><a name="p696158384093531"></a><a name="p696158384093531"></a>uint16_t&nbsp;</p>
</td>
</tr>
<tr id="row1591373434093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p857449103093531"><a name="p857449103093531"></a><a name="p857449103093531"></a><a href="I2cMsg.md#a7b32a5e6322edb302cea3faf698953a0">buf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p653523785093531"><a name="p653523785093531"></a><a name="p653523785093531"></a>uint8_t *&nbsp;</p>
</td>
</tr>
<tr id="row193181691093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1801505782093531"><a name="p1801505782093531"></a><a name="p1801505782093531"></a><a href="I2cMsg.md#aa3951709930c577af6f5ee4cf53b6dad">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1280970248093531"><a name="p1280970248093531"></a><a name="p1280970248093531"></a>uint16_t&nbsp;</p>
</td>
</tr>
<tr id="row147811393093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003244974093531"><a name="p2003244974093531"></a><a name="p2003244974093531"></a><a href="I2cMsg.md#adfecd4720506fef0a87d0abd45d1f201">flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850634333093531"><a name="p1850634333093531"></a><a name="p1850634333093531"></a>uint16_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1802433676093531"></a>

## **Field Documentation**<a name="section1580769389093531"></a>

## addr<a name="a8f9fae2a615957552b2c409b868e91cd"></a>

```
uint16_t I2cMsg::addr
```

 **Description:**

Address of the I2C device 

## buf<a name="a7b32a5e6322edb302cea3faf698953a0"></a>

```
uint8_t* I2cMsg::buf
```

 **Description:**

Address of the buffer for storing transferred data 

## flags<a name="adfecd4720506fef0a87d0abd45d1f201"></a>

```
uint16_t I2cMsg::flags
```

## len<a name="aa3951709930c577af6f5ee4cf53b6dad"></a>

```
uint16_t I2cMsg::len
```

 **Description:**

Length of the transferred data 

