# qelem<a name="EN-US_TOPIC_0000001055518136"></a>

## **Overview**<a name="section160326111093538"></a>

**Related Modules:**

[UTILS](en-us_topic_0000001055198076.md)

**Description:**

Creates a queue from the doubly linked list for  [insque](en-us_topic_0000001055198076.md#ga7dc680d5d6d07984f96737c220058d64)  and  [remque](en-us_topic_0000001055198076.md#ga1d2e353620a8dc3bb2702831607a3fc1). 

## **Summary**<a name="section515312520093538"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table770580698093538"></a>
<table><thead align="left"><tr id="row797207261093538"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1452479511093538"><a name="p1452479511093538"></a><a name="p1452479511093538"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p437840800093538"><a name="p437840800093538"></a><a name="p437840800093538"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row714343024093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p137158503093538"><a name="p137158503093538"></a><a name="p137158503093538"></a><a href="qelem.md#acde6ec14ed8d080765c2f58dc1343c6b">q_forw</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142252862093538"><a name="p142252862093538"></a><a name="p142252862093538"></a>struct <a href="qelem.md">qelem</a> * </p>
</td>
</tr>
<tr id="row763492195093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1308050144093538"><a name="p1308050144093538"></a><a name="p1308050144093538"></a><a href="qelem.md#a4a64afa420bf271831f625e269d8f904">q_back</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1272044957093538"><a name="p1272044957093538"></a><a name="p1272044957093538"></a>struct <a href="qelem.md">qelem</a> * </p>
</td>
</tr>
<tr id="row619886054093538"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1235464230093538"><a name="p1235464230093538"></a><a name="p1235464230093538"></a><a href="qelem.md#a6c6345d36147063410f8a50d01dc6d63">q_data</a> [1]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1044280628093538"><a name="p1044280628093538"></a><a name="p1044280628093538"></a>char </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1867352728093538"></a>

## **Field Documentation**<a name="section1110793081093538"></a>

## q\_back<a name="a4a64afa420bf271831f625e269d8f904"></a>

```
struct [qelem](qelem.md)* qelem::q_back
```

 **Description:**

Pointer to the next  **qelem**  type 

## q\_data<a name="a6c6345d36147063410f8a50d01dc6d63"></a>

```
char qelem::q_data[1]
```

 **Description:**

Data saved in the queue 

## q\_forw<a name="acde6ec14ed8d080765c2f58dc1343c6b"></a>

```
struct [qelem](qelem.md)* qelem::q_forw
```

 **Description:**

Pointer to the previous  **qelem**  type 

