# shminfo<a name="EN-US_TOPIC_0000001055039564"></a>

## **Overview**<a name="section679255156084843"></a>

**Related Modules:**

[MEM](mem.md)

**Description:**

Describes limitations and attributes of system-level shared memory. 

## **Summary**<a name="section1095350905084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table765226721084843"></a>
<table><thead align="left"><tr id="row1071570771084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1279545924084843"><a name="p1279545924084843"></a><a name="p1279545924084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p146894964084843"><a name="p146894964084843"></a><a name="p146894964084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1152593283084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1862920464084843"><a name="p1862920464084843"></a><a name="p1862920464084843"></a><a href="shminfo.md#a2d7778854ce2e55499a2036da769905a">shmmax</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983861991084843"><a name="p983861991084843"></a><a name="p983861991084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row1890341097084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505578260084843"><a name="p1505578260084843"></a><a name="p1505578260084843"></a><a href="shminfo.md#a9940d32ac5484be0f5df79296d9bc97a">shmmin</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100342808084843"><a name="p100342808084843"></a><a name="p100342808084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row1583735918084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550845632084843"><a name="p1550845632084843"></a><a name="p1550845632084843"></a><a href="shminfo.md#a084bc8449e6683ede60a6445255d14bd">shmmni</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918244563084843"><a name="p1918244563084843"></a><a name="p1918244563084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row1028734777084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871184792084843"><a name="p871184792084843"></a><a name="p871184792084843"></a><a href="shminfo.md#a11ee1150ca8aaad294c17fe939f35688">shmseg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1071198142084843"><a name="p1071198142084843"></a><a name="p1071198142084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row1765219809084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1844326937084843"><a name="p1844326937084843"></a><a name="p1844326937084843"></a><a href="shminfo.md#a4b74fbc85e2805f7b99f6aecde00c570">shmall</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448734012084843"><a name="p448734012084843"></a><a name="p448734012084843"></a>unsigned long </p>
</td>
</tr>
<tr id="row99108698084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228810183084843"><a name="p228810183084843"></a><a name="p228810183084843"></a><a href="shminfo.md#a68b65a802c7b3bc6d911ed41808203ef">__unused</a> [4]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801009267084843"><a name="p801009267084843"></a><a name="p801009267084843"></a>unsigned long </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1183055754084843"></a>

## **Field Documentation**<a name="section768473825084843"></a>

## \_\_unused<a name="a68b65a802c7b3bc6d911ed41808203ef"></a>

```
unsigned long shminfo::__unused[4]
```

 **Description:**

Reserved 

## shmall<a name="a4b74fbc85e2805f7b99f6aecde00c570"></a>

```
unsigned long shminfo::shmall
```

 **Description:**

Maximum size of all shared memory segments allowed by the system 

## shmmax<a name="a2d7778854ce2e55499a2036da769905a"></a>

```
unsigned long shminfo::shmmax
```

 **Description:**

Maximum size of a shared memory segment allowed by the system 

## shmmin<a name="a9940d32ac5484be0f5df79296d9bc97a"></a>

```
unsigned long shminfo::shmmin
```

 **Description:**

Minimum size of a shared memory segment allowed by the system 

## shmmni<a name="a084bc8449e6683ede60a6445255d14bd"></a>

```
unsigned long shminfo::shmmni
```

 **Description:**

Maximum number of shared memory segments allowed by the system 

## shmseg<a name="a11ee1150ca8aaad294c17fe939f35688"></a>

```
unsigned long shminfo::shmseg
```

 **Description:**

Maximum number of shared memory segments that can be attached by a process 

