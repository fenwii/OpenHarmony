# ThreadInfo<a name="EN-US_TOPIC_0000001055515030"></a>

## **Overview**<a name="section425086273191902"></a>

**Related Modules:**

[KAL](en-us_topic_0000001054595087.md)

**Description:**

Describes a thread. 

## **Summary**<a name="section1309594257191902"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table306006874191902"></a>
<table><thead align="left"><tr id="row507374646191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1046545888191902"><a name="p1046545888191902"></a><a name="p1046545888191902"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1289151577191902"><a name="p1289151577191902"></a><a name="p1289151577191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1675007072191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390716100191902"><a name="p390716100191902"></a><a name="p390716100191902"></a><a href="en-us_topic_0000001054595087.md#ga13a2aab39a8c95bf10c135207b15f851">name</a> [<a href="en-us_topic_0000001054595087.md#ga5c36b53bd6e8cbdbcd79f702eda94fdc">KAL_TASK_NAME_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1254538215191902"><a name="p1254538215191902"></a><a name="p1254538215191902"></a>char </p>
</td>
</tr>
<tr id="row1096724032191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1986266106191902"><a name="p1986266106191902"></a><a name="p1986266106191902"></a><a href="en-us_topic_0000001054595087.md#gac764c6a73d29bd0730350f81f4594a9f">id</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1771625424191902"><a name="p1771625424191902"></a><a name="p1771625424191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row435246948191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p572113388191902"><a name="p572113388191902"></a><a name="p572113388191902"></a><a href="en-us_topic_0000001054595087.md#ga0ab6ed527e0c49b254e7e6764fd99c09">status</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184372673191902"><a name="p1184372673191902"></a><a name="p1184372673191902"></a>unsigned short </p>
</td>
</tr>
<tr id="row482416464191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p630374533191902"><a name="p630374533191902"></a><a name="p630374533191902"></a><a href="en-us_topic_0000001054595087.md#ga5eb18799436289247d58027508924bf9">priority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1783272417191902"><a name="p1783272417191902"></a><a name="p1783272417191902"></a>unsigned short </p>
</td>
</tr>
<tr id="row22139075191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432451241191902"><a name="p432451241191902"></a><a name="p432451241191902"></a><a href="en-us_topic_0000001054595087.md#gabce57039bcba8c3c5941e11fc13908e1">taskSem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p995184689191902"><a name="p995184689191902"></a><a name="p995184689191902"></a>void * </p>
</td>
</tr>
<tr id="row1953408366191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p572189789191902"><a name="p572189789191902"></a><a name="p572189789191902"></a><a href="en-us_topic_0000001054595087.md#ga2001b2a08dea8277c36d7e8f6cfb09f5">taskMutex</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135064702191902"><a name="p135064702191902"></a><a name="p135064702191902"></a>void * </p>
</td>
</tr>
<tr id="row760746421191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p861189846191902"><a name="p861189846191902"></a><a name="p861189846191902"></a><a href="en-us_topic_0000001054595087.md#ga1424ad853216d3a422ad7ce7626225cd">eventStru</a> [3]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754884852191902"><a name="p754884852191902"></a><a name="p754884852191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row710928846191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242533684191902"><a name="p242533684191902"></a><a name="p242533684191902"></a><a href="en-us_topic_0000001054595087.md#gae92f3f338fe0daeee86bf24205d029f4">eventMask</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p745906987191902"><a name="p745906987191902"></a><a name="p745906987191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row1571157393191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1545041531191902"><a name="p1545041531191902"></a><a name="p1545041531191902"></a><a href="en-us_topic_0000001054595087.md#ga3948edc6f57a3afbdaf45347d29a85c8">stackSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262247266191902"><a name="p262247266191902"></a><a name="p262247266191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row650439333191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497814948191902"><a name="p1497814948191902"></a><a name="p1497814948191902"></a><a href="en-us_topic_0000001054595087.md#ga3a22f2522b3d5cdd6063f2f57d4206ea">topOfStack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985575141191902"><a name="p1985575141191902"></a><a name="p1985575141191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row1978171932191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977845497191902"><a name="p977845497191902"></a><a name="p977845497191902"></a><a href="en-us_topic_0000001054595087.md#ga9782002d7ff296063c57521353df67fe">bottomOfStack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p760572284191902"><a name="p760572284191902"></a><a name="p760572284191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row1351467070191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p690661565191902"><a name="p690661565191902"></a><a name="p690661565191902"></a><a href="en-us_topic_0000001054595087.md#gae7d1ec2921ba3fd0d2d4009f76f73f3f">mstatus</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p815457192191902"><a name="p815457192191902"></a><a name="p815457192191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row464507867191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2120922533191902"><a name="p2120922533191902"></a><a name="p2120922533191902"></a><a href="en-us_topic_0000001054595087.md#ga443d3e54ba44e2528c482c206997de94">mepc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137277445191902"><a name="p2137277445191902"></a><a name="p2137277445191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row996017982191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1920889864191902"><a name="p1920889864191902"></a><a name="p1920889864191902"></a><a href="en-us_topic_0000001054595087.md#ga782cce4041f34c75829b862b32e19ca1">tp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p822853370191902"><a name="p822853370191902"></a><a name="p822853370191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row509666540191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1612747980191902"><a name="p1612747980191902"></a><a name="p1612747980191902"></a><a href="en-us_topic_0000001054595087.md#gae011035df8be3da14189c65a0028a137">ra</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35371026191902"><a name="p35371026191902"></a><a name="p35371026191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row1833085091191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p446721566191902"><a name="p446721566191902"></a><a name="p446721566191902"></a><a href="en-us_topic_0000001054595087.md#gae2812d96da0c6a7580f5161663af418a">sp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333088230191902"><a name="p333088230191902"></a><a name="p333088230191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row369851168191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1164902711191902"><a name="p1164902711191902"></a><a name="p1164902711191902"></a><a href="en-us_topic_0000001054595087.md#ga0a57d18c5ea4b55301b070c14bcfec60">currUsed</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28320644191902"><a name="p28320644191902"></a><a name="p28320644191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row827088600191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379174881191902"><a name="p1379174881191902"></a><a name="p1379174881191902"></a><a href="en-us_topic_0000001054595087.md#ga2416d243f06063f759aea86e793417dc">peakUsed</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81312936191902"><a name="p81312936191902"></a><a name="p81312936191902"></a>unsigned int </p>
</td>
</tr>
<tr id="row507189175191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p118359088191902"><a name="p118359088191902"></a><a name="p118359088191902"></a><a href="en-us_topic_0000001054595087.md#gac28ecdda9bd5ba304bfcb4437c729e9f">overflowFlag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1204018332191902"><a name="p1204018332191902"></a><a name="p1204018332191902"></a>unsigned int </p>
</td>
</tr>
</tbody>
</table>

