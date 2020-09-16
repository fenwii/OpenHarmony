# sem\_t<a name="ZH-CN_TOPIC_0000001055198178"></a>

## **Overview**<a name="section271629910084843"></a>

**Related Modules:**

[IPC](IPC.md)

**Description:**

Defines semaphores. 

This structure is used to store semaphores. 

## **Summary**<a name="section1860562269084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1220643812084843"></a>
<table><thead align="left"><tr id="row1528768792084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1471586996084843"><a name="p1471586996084843"></a><a name="p1471586996084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1307195632084843"><a name="p1307195632084843"></a><a name="p1307195632084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row553581489084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1326451148084843"><a name="p1326451148084843"></a><a name="p1326451148084843"></a><a href="sem_t.md#a79fdf291ed1877958bc756d78fc16cf3">__val</a> [4 *sizeof(long)/sizeof(int)]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p936090395084843"><a name="p936090395084843"></a><a name="p936090395084843"></a>volatile int&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section177351719084843"></a>

## **Field Documentation**<a name="section2106262304084843"></a>

## \_\_val<a name="a79fdf291ed1877958bc756d78fc16cf3"></a>

```
volatile int sem_t::__val[4 *sizeof(long)/sizeof(int)]
```

 **Description:**

Number of semaphores 

