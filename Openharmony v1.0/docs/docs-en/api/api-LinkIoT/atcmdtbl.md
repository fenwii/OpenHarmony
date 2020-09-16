# AtCmdTbl<a name="EN-US_TOPIC_0000001055036452"></a>

## **Overview**<a name="section2064737160191858"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Defines the AT command registration structure. 

## **Summary**<a name="section1571632696191858"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1652590832191858"></a>
<table><thead align="left"><tr id="row1772459793191858"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p773912997191858"><a name="p773912997191858"></a><a name="p773912997191858"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1426608632191858"><a name="p1426608632191858"></a><a name="p1426608632191858"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2032418511191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1902039158191858"><a name="p1902039158191858"></a><a name="p1902039158191858"></a><a href="atcmdtbl.md#af9e3433c293ffaa1e60ccb07e051ef29">atCmdName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541237630191858"><a name="p1541237630191858"></a><a name="p1541237630191858"></a>char * </p>
</td>
</tr>
<tr id="row1471418372191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p92861653191858"><a name="p92861653191858"></a><a name="p92861653191858"></a><a href="atcmdtbl.md#a01ef03a0c8669e107e2fd988514935ab">atCmdLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964772384191858"><a name="p964772384191858"></a><a name="p964772384191858"></a>char </p>
</td>
</tr>
<tr id="row1455582246191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2011214047191858"><a name="p2011214047191858"></a><a name="p2011214047191858"></a><a href="atcmdtbl.md#ac4640c36b35e6986e5a2a5b82f3a880e">atTestCmd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p162925060191858"><a name="p162925060191858"></a><a name="p162925060191858"></a>AtCallbackFunc </p>
</td>
</tr>
<tr id="row2067323084191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686880580191858"><a name="p686880580191858"></a><a name="p686880580191858"></a><a href="atcmdtbl.md#ae9395d9f2d87a304c6e068fadce74e99">atQueryCmd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1892663102191858"><a name="p1892663102191858"></a><a name="p1892663102191858"></a>AtCallbackFunc </p>
</td>
</tr>
<tr id="row1460815620191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413985929191858"><a name="p1413985929191858"></a><a name="p1413985929191858"></a><a href="atcmdtbl.md#ae210d9f8e403f52c5f17f7fb716d5e29">atSetupCmd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p104645735191858"><a name="p104645735191858"></a><a name="p104645735191858"></a>AtCallbackFunc </p>
</td>
</tr>
<tr id="row965911634191858"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p11872626191858"><a name="p11872626191858"></a><a name="p11872626191858"></a><a href="atcmdtbl.md#a6f6aa00ff3315b14afcba9d649f73543">atExeCmd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p33578643191858"><a name="p33578643191858"></a><a name="p33578643191858"></a>AtCallbackFunc </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1254548727191858"></a>

## **Field Documentation**<a name="section205322858191858"></a>

## atCmdLen<a name="a01ef03a0c8669e107e2fd988514935ab"></a>

```
char AtCmdTbl::atCmdLen
```

 **Description:**

AT command length 

## atCmdName<a name="af9e3433c293ffaa1e60ccb07e051ef29"></a>

```
char* AtCmdTbl::atCmdName
```

 **Description:**

AT command name 

## atExeCmd<a name="a6f6aa00ff3315b14afcba9d649f73543"></a>

```
AtCallbackFunc AtCmdTbl::atExeCmd
```

 **Description:**

AT command execution 

## atQueryCmd<a name="ae9395d9f2d87a304c6e068fadce74e99"></a>

```
AtCallbackFunc AtCmdTbl::atQueryCmd
```

 **Description:**

AT command query 

## atSetupCmd<a name="ae210d9f8e403f52c5f17f7fb716d5e29"></a>

```
AtCallbackFunc AtCmdTbl::atSetupCmd
```

 **Description:**

AT command setup 

## atTestCmd<a name="ac4640c36b35e6986e5a2a5b82f3a880e"></a>

```
AtCallbackFunc AtCmdTbl::atTestCmd
```

 **Description:**

AT test command 

