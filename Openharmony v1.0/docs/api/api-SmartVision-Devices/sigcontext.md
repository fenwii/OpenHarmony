# sigcontext<a name="ZH-CN_TOPIC_0000001054414213"></a>

## **Overview**<a name="section2127314767113042"></a>

**Related Modules:**

[IPC](IPC.md)

**Description:**

Describes the signal context. 

## **Summary**<a name="section2106455985113042"></a>

## Data Fields<a name="pub-attribs"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#aa164913813a1b485fce098107b309f02">trap_no</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a6eaff68f4ddfd515bd1cc5175a8f54fc">error_code</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#adfe9d1041a802bd6627f2664c9d0a221">oldmask</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a97eaf05f2862af06ccd89b4921db3c49">arm_r0</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#ab33e8f9761c53bcdabee934ef9d30c16">arm_r1</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a534266af5196a1567067fae2b6c3b41f">arm_r2</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#abe0fd93d30db9bbdc3173eb7313f508c">arm_r3</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a66b9c30adfadd843742d948db9f01548">arm_r4</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a63a587efce0e216b5e044fae5efb4001">arm_r5</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a518fd405d89f82e5d04b9ff3149cfc9d">arm_r6</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a9b7fbf6a4bafb1777574f57e58618bf2">arm_r7</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#ac0b7fd82cd289a426a99f039186081bd">arm_r8</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#acb4bb9d051a0e9c9809996fbeaef6aae">arm_r9</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#ac3a4c09edf65920b94ab738b0249e699">arm_r10</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a311f35f38ad24c1d8d323ce84112e053">arm_fp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a989591cba7c919f8bb8a0f6c4f6229ba">arm_ip</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#ad64f1d83f0d367371e5ff33518090ae4">arm_sp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a40fc9551a8a8238e279fbe2d28044095">arm_lr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a858e6ba025e0ec1226a68d61eb8e79a7">arm_pc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#a1e71cab409638ba8663f81499c3eec47">arm_cpsr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="sigcontext.md#aa8c284cb09714d4e07e0c5e1be0c0845">fault_address</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>unsigned long&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2055495532113042"></a>

## **Field Documentation**<a name="section1214377083113042"></a>

## arm\_cpsr<a name="a1e71cab409638ba8663f81499c3eec47"></a>

```
unsigned long sigcontext::arm_cpsr
```

 **Description:**

cpsr register backup 

## arm\_fp<a name="a311f35f38ad24c1d8d323ce84112e053"></a>

```
unsigned long sigcontext::arm_fp
```

 **Description:**

fp register backup 

## arm\_ip<a name="a989591cba7c919f8bb8a0f6c4f6229ba"></a>

```
unsigned long sigcontext::arm_ip
```

 **Description:**

ip register backup 

## arm\_lr<a name="a40fc9551a8a8238e279fbe2d28044095"></a>

```
unsigned long sigcontext::arm_lr
```

 **Description:**

lr register backup 

## arm\_pc<a name="a858e6ba025e0ec1226a68d61eb8e79a7"></a>

```
unsigned long sigcontext::arm_pc
```

 **Description:**

pc register backup 

## arm\_r0<a name="a97eaf05f2862af06ccd89b4921db3c49"></a>

```
unsigned long sigcontext::arm_r0
```

 **Description:**

r0 register backup 

## arm\_r1<a name="ab33e8f9761c53bcdabee934ef9d30c16"></a>

```
unsigned long sigcontext::arm_r1
```

 **Description:**

r1 register backup 

## arm\_r10<a name="ac3a4c09edf65920b94ab738b0249e699"></a>

```
unsigned long sigcontext::arm_r10
```

 **Description:**

r10 register backup 

## arm\_r2<a name="a534266af5196a1567067fae2b6c3b41f"></a>

```
unsigned long sigcontext::arm_r2
```

 **Description:**

r2 register backup 

## arm\_r3<a name="abe0fd93d30db9bbdc3173eb7313f508c"></a>

```
unsigned long sigcontext::arm_r3
```

 **Description:**

r3 register backup 

## arm\_r4<a name="a66b9c30adfadd843742d948db9f01548"></a>

```
unsigned long sigcontext::arm_r4
```

 **Description:**

r4 register backup 

## arm\_r5<a name="a63a587efce0e216b5e044fae5efb4001"></a>

```
unsigned long sigcontext::arm_r5
```

 **Description:**

r5 register backup 

## arm\_r6<a name="a518fd405d89f82e5d04b9ff3149cfc9d"></a>

```
unsigned long sigcontext::arm_r6
```

 **Description:**

r6 register backup 

## arm\_r7<a name="a9b7fbf6a4bafb1777574f57e58618bf2"></a>

```
unsigned long sigcontext::arm_r7
```

 **Description:**

r7 register backup 

## arm\_r8<a name="ac0b7fd82cd289a426a99f039186081bd"></a>

```
unsigned long sigcontext::arm_r8
```

 **Description:**

r8 register backup 

## arm\_r9<a name="acb4bb9d051a0e9c9809996fbeaef6aae"></a>

```
unsigned long sigcontext::arm_r9
```

 **Description:**

r9 register backup 

## arm\_sp<a name="ad64f1d83f0d367371e5ff33518090ae4"></a>

```
unsigned long sigcontext::arm_sp
```

 **Description:**

sp register backup 

## error\_code<a name="a6eaff68f4ddfd515bd1cc5175a8f54fc"></a>

```
unsigned long sigcontext::error_code
```

 **Description:**

Error code 

## fault\_address<a name="aa8c284cb09714d4e07e0c5e1be0c0845"></a>

```
unsigned long sigcontext::fault_address
```

 **Description:**

Fault address 

## oldmask<a name="adfe9d1041a802bd6627f2664c9d0a221"></a>

```
unsigned long sigcontext::oldmask
```

 **Description:**

Original signal mask 

## trap\_no<a name="aa164913813a1b485fce098107b309f02"></a>

```
unsigned long sigcontext::trap_no
```

 **Description:**

Trap number 

