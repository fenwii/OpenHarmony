# option<a name="ZH-CN_TOPIC_0000001054718173"></a>

## **Overview**<a name="section1302395280084843"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Defines the command parsing option. 

## **Summary**<a name="section1669044165084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1591233149084843"></a>
<table><thead align="left"><tr id="row1743054722084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2104888712084843"><a name="p2104888712084843"></a><a name="p2104888712084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p130692078084843"><a name="p130692078084843"></a><a name="p130692078084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1272865366084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1019719965084843"><a name="p1019719965084843"></a><a name="p1019719965084843"></a><a href="option.md#adc503659d37af8017fb4b86d61c99086">name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561506508084843"><a name="p1561506508084843"></a><a name="p1561506508084843"></a>const char *&nbsp;</p>
</td>
</tr>
<tr id="row1167653243084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p877210594084843"><a name="p877210594084843"></a><a name="p877210594084843"></a><a href="option.md#a90d7ee9a51eea5c002682dbd0af149e4">has_arg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p916556202084843"><a name="p916556202084843"></a><a name="p916556202084843"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row1073067211084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463461784084843"><a name="p463461784084843"></a><a name="p463461784084843"></a><a href="option.md#ab366eea5fe7be25c1928328ba715e353">flag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003741039084843"><a name="p1003741039084843"></a><a name="p1003741039084843"></a>int *&nbsp;</p>
</td>
</tr>
<tr id="row618006478084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916582130084843"><a name="p1916582130084843"></a><a name="p1916582130084843"></a><a href="option.md#a13bd155ec3b405d29c41ab8d0793be11">val</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1475968066084843"><a name="p1475968066084843"></a><a name="p1475968066084843"></a>int&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section662880372084843"></a>

## **Field Documentation**<a name="section131126100084843"></a>

## flag<a name="ab366eea5fe7be25c1928328ba715e353"></a>

```
int* option::flag
```

 **Description:**

Determines the returned value of the  **[getopt\(\)](UTILS.md#ga5ffa4c677fc71cecd94f140ef9db624c)**  function. If  **flag**  is  **NULL**, the  **[getopt\(\)](UTILS.md#ga5ffa4c677fc71cecd94f140ef9db624c)**  function returns the  **val**  value that matches the option. If  **flag**  is not  **NULL**, assign the  **val**  value to the memory to which  **flag**  points, and set the returned value to  **0**. 

## has\_arg<a name="a90d7ee9a51eea5c002682dbd0af149e4"></a>

```
int option::has_arg
```

 **Description:**

**has\_arg**  has three values.  **0**  indicates that the argument is not followed by an argument value,  **1**  indicates that the argument must be followed by an argument value, and  **2**  indicates that the argument can be followed or not followed by an argument value. 

## name<a name="adc503659d37af8017fb4b86d61c99086"></a>

```
const char* option::name
```

 **Description:**

Long argument name 

## val<a name="a13bd155ec3b405d29c41ab8d0793be11"></a>

```
int option::val
```

 **Description:**

The returned value is determined by  **flag**. 

