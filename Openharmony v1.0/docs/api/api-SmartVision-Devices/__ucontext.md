# \_\_ucontext<a name="ZH-CN_TOPIC_0000001055039560"></a>

## **Overview**<a name="section1498156335093537"></a>

**Related Modules:**

[IPC](zh-cn_topic_0000001054718071.md)

**Description:**

Describes the user execution context. 

## **Summary**<a name="section644896465093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1781620728093537"></a>
<table><thead align="left"><tr id="row1311912665093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1091073248093537"><a name="p1091073248093537"></a><a name="p1091073248093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1459174334093537"><a name="p1459174334093537"></a><a name="p1459174334093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1365442229093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1026147200093537"><a name="p1026147200093537"></a><a name="p1026147200093537"></a><a href="__ucontext.md#a37d6c2fd659ca179dac3b3e201caf721">uc_flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2123182388093537"><a name="p2123182388093537"></a><a name="p2123182388093537"></a>unsigned long&nbsp;</p>
</td>
</tr>
<tr id="row911669614093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1919659478093537"><a name="p1919659478093537"></a><a name="p1919659478093537"></a><a href="__ucontext.md#ac959c5e5cf5dc08fe790c048f7c7f802">uc_link</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1854207267093537"><a name="p1854207267093537"></a><a name="p1854207267093537"></a>struct <a href="__ucontext.md">__ucontext</a> *&nbsp;</p>
</td>
</tr>
<tr id="row561404688093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p598157113093537"><a name="p598157113093537"></a><a name="p598157113093537"></a><a href="__ucontext.md#ad53e410e77eb4014fffad71484aee872">uc_stack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124677967093537"><a name="p2124677967093537"></a><a name="p2124677967093537"></a><a href="zh-cn_topic_0000001054718071.md#ga395f9ff4025fe05bb535322593abde72">stack_t</a>&nbsp;</p>
</td>
</tr>
<tr id="row1057695361093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1347816882093537"><a name="p1347816882093537"></a><a name="p1347816882093537"></a><a href="__ucontext.md#a7b1df7352cb1f09948bcfa9af895eac1">uc_mcontext</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146211582093537"><a name="p1146211582093537"></a><a name="p1146211582093537"></a>mcontext_t&nbsp;</p>
</td>
</tr>
<tr id="row1791359216093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1471605501093537"><a name="p1471605501093537"></a><a name="p1471605501093537"></a><a href="__ucontext.md#a2edf70532d013389f4362252f749f14c">uc_sigmask</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1131667511093537"><a name="p1131667511093537"></a><a name="p1131667511093537"></a>sigset_t&nbsp;</p>
</td>
</tr>
<tr id="row1026704580093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390411973093537"><a name="p1390411973093537"></a><a name="p1390411973093537"></a><a href="__ucontext.md#a93ddd393e196ec5f6c436e3179c5d19c">uc_regspace</a> [64]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823109353093537"><a name="p1823109353093537"></a><a name="p1823109353093537"></a>unsigned long long&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1115212877093537"></a>

## **Field Documentation**<a name="section30097202093537"></a>

## uc\_flags<a name="a37d6c2fd659ca179dac3b3e201caf721"></a>

```
unsigned long __ucontext::uc_flags
```

 **Description:**

Flag 

## uc\_link<a name="ac959c5e5cf5dc08fe790c048f7c7f802"></a>

```
struct [__ucontext](__ucontext.md)* __ucontext::uc_link
```

 **Description:**

Context linked-list 

## uc\_mcontext<a name="a7b1df7352cb1f09948bcfa9af895eac1"></a>

```
mcontext_t __ucontext::uc_mcontext
```

 **Description:**

Related signal context 

## uc\_regspace<a name="a93ddd393e196ec5f6c436e3179c5d19c"></a>

```
unsigned long long __ucontext::uc_regspace[64]
```

 **Description:**

User register space 

## uc\_sigmask<a name="a2edf70532d013389f4362252f749f14c"></a>

```
sigset_t __ucontext::uc_sigmask
```

 **Description:**

User signal mask 

## uc\_stack<a name="ad53e410e77eb4014fffad71484aee872"></a>

```
[stack_t](zh-cn_topic_0000001054718071.md#ga395f9ff4025fe05bb535322593abde72) __ucontext::uc_stack
```

 **Description:**

User stack 

