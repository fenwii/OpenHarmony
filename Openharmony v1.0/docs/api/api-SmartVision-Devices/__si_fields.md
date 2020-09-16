# \_\_si\_fields<a name="ZH-CN_TOPIC_0000001054879576"></a>

## **Overview**<a name="section2010064035084842"></a>

**Related Modules:**

[IPC](IPC.md)

**Description:**

Describes signal information. 

## **Summary**<a name="section946716420084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1129414724084842"></a>
<table><thead align="left"><tr id="row829732284084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2142746410084842"><a name="p2142746410084842"></a><a name="p2142746410084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1197918998084842"><a name="p1197918998084842"></a><a name="p1197918998084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2102516878084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488060015084842"><a name="p1488060015084842"></a><a name="p1488060015084842"></a><a href="__si_fields.md#a1640d7d62d6bf4e0c6f859348ee15fbf">si_signo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p431350046084842"><a name="p431350046084842"></a><a name="p431350046084842"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row1522270430084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p599380135084842"><a name="p599380135084842"></a><a name="p599380135084842"></a><a href="__si_fields.md#ad8322ef52a0a0ec711ccd4e99ed4e8bd">si_errno</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1637312072084842"><a name="p1637312072084842"></a><a name="p1637312072084842"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row1506721772084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p986851962084842"><a name="p986851962084842"></a><a name="p986851962084842"></a><a href="__si_fields.md#aea37db23af7a01123e78567c63fea57f">si_code</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312418550084842"><a name="p1312418550084842"></a><a name="p1312418550084842"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row231912171084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1975081230084842"><a name="p1975081230084842"></a><a name="p1975081230084842"></a><a href="__si_fields.md#af2be33102b7e76235a62db547c89e642">char__pad</a> [128 - 2 *sizeof(int) - sizeof(long)]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768661937084842"><a name="p768661937084842"></a><a name="p768661937084842"></a>&nbsp;</p>
</td>
</tr>
<tr id="row697682021084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021376778084842"><a name="p2021376778084842"></a><a name="p2021376778084842"></a>struct {</p>
</td>
</tr>
<tr id="row1641697301084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875801670084842"><a name="p1875801670084842"></a><a name="p1875801670084842"></a><a href="__si_fields.md#a216f748c88cd41a069f632f6d9402a40">__piduid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1031672402084842"><a name="p1031672402084842"></a><a name="p1031672402084842"></a>}&nbsp;</p>
</td>
</tr>
<tr id="row1140434784084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521159568084842"><a name="p1521159568084842"></a><a name="p1521159568084842"></a>struct {</p>
</td>
</tr>
<tr id="row472474508084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1903325059084842"><a name="p1903325059084842"></a><a name="p1903325059084842"></a><a href="__si_fields.md#a8e8e826b7efadbbfb2957100ec98db2a">__timer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p707946517084842"><a name="p707946517084842"></a><a name="p707946517084842"></a>}&nbsp;</p>
</td>
</tr>
<tr id="row1828135781084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830639510084842"><a name="p1830639510084842"></a><a name="p1830639510084842"></a><a href="__si_fields.md#abedf932f1bdc181052be44232803d6e1">si_value</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999891859084842"><a name="p1999891859084842"></a><a name="p1999891859084842"></a>union <a href="sigval.md">sigval</a>&nbsp;</p>
</td>
</tr>
<tr id="row1102863654084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p887851471084842"><a name="p887851471084842"></a><a name="p887851471084842"></a>struct {</p>
</td>
</tr>
<tr id="row1513454857084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1216658180084842"><a name="p1216658180084842"></a><a name="p1216658180084842"></a><a href="__si_fields.md#a99fb68087a4859ae9856b048dfa89894">__sigchld</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261285652084842"><a name="p1261285652084842"></a><a name="p1261285652084842"></a>}&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1575889680084842"></a>

## **Field Documentation**<a name="section1935953797084842"></a>

## \_\_piduid<a name="a216f748c88cd41a069f632f6d9402a40"></a>

```
struct { ... } __si_fields::__piduid
```

 **Description:**

This structure is not supported. 

## \_\_sigchld<a name="a99fb68087a4859ae9856b048dfa89894"></a>

```
struct { ... } __si_fields::__sigchld
```

 **Description:**

This structure is not supported. 

## \_\_timer<a name="a8e8e826b7efadbbfb2957100ec98db2a"></a>

```
struct { ... } __si_fields::__timer
```

 **Description:**

This structure is not supported. 

## char\_\_pad<a name="af2be33102b7e76235a62db547c89e642"></a>

```
__si_fields::char__pad[128 - 2 *sizeof(int) - sizeof(long)]
```

 **Description:**

Alignment fields 

## si\_code<a name="aea37db23af7a01123e78567c63fea57f"></a>

```
int __si_fields::si_code
```

 **Description:**

Cause of signal generation, which is not supported currently 

## si\_errno<a name="ad8322ef52a0a0ec711ccd4e99ed4e8bd"></a>

```
int __si_fields::si_errno
```

 **Description:**

Error code, which is not supported currently 

## si\_signo<a name="a1640d7d62d6bf4e0c6f859348ee15fbf"></a>

```
int __si_fields::si_signo
```

 **Description:**

Signal number 

## si\_value<a name="abedf932f1bdc181052be44232803d6e1"></a>

```
union [sigval](sigval.md) __si_fields::si_value
```

 **Description:**

**sival\_int**  in the union is supported. 

