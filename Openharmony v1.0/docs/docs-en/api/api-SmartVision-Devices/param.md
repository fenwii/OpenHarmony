# Param<a name="EN-US_TOPIC_0000001054718161"></a>

## **Overview**<a name="section1857314309093536"></a>

**Related Modules:**

[Codec](codec.md)

**Description:**

Describes the dynamic parameter structure, which is mainly used by  [CodecCreate](codec.md#ga74aa0395a51f004390f7a92fb68faddd)  and  [CodecSetParameter](codec.md#gaa080cf23aa5f77b30f3b90a026d97cc0). 

## **Summary**<a name="section482121123093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1393928297093536"></a>
<table><thead align="left"><tr id="row1644261262093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1036560192093536"><a name="p1036560192093536"></a><a name="p1036560192093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1872208987093536"><a name="p1872208987093536"></a><a name="p1872208987093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1568675547093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2002794098093536"><a name="p2002794098093536"></a><a name="p2002794098093536"></a><a href="param.md#ace6f19effda894bc68afd60d5425a4a8">key</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1641363514093536"><a name="p1641363514093536"></a><a name="p1641363514093536"></a><a href="codec.md#ga575c56a2d6b42c48881cf47b0008d5a6">ParamKey</a> </p>
</td>
</tr>
<tr id="row1044838011093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p681328815093536"><a name="p681328815093536"></a><a name="p681328815093536"></a><a href="param.md#a375689df3cbcede96a3fb20ab6e0a086">val</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114345035093536"><a name="p2114345035093536"></a><a name="p2114345035093536"></a>void * </p>
</td>
</tr>
<tr id="row289472582093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1191032802093536"><a name="p1191032802093536"></a><a name="p1191032802093536"></a><a href="param.md#a4f68079ff933352feeef5364436bc402">size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157713884093536"><a name="p157713884093536"></a><a name="p157713884093536"></a>int </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1131879235093536"></a>

## **Field Documentation**<a name="section707905573093536"></a>

## key<a name="ace6f19effda894bc68afd60d5425a4a8"></a>

```
[ParamKey](codec.md#ga575c56a2d6b42c48881cf47b0008d5a6) Param::key
```

 **Description:**

Parameter type index 

## size<a name="a4f68079ff933352feeef5364436bc402"></a>

```
int Param::size
```

 **Description:**

Parameter value size 

## val<a name="a375689df3cbcede96a3fb20ab6e0a086"></a>

```
void* Param::val
```

 **Description:**

Pointer to the parameter value 

