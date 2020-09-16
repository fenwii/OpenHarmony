# BufferData<a name="ZH-CN_TOPIC_0000001054718119"></a>

## **Overview**<a name="section1025561045093529"></a>

**Related Modules:**

[Display](Display.md)

**Description:**

Defines buffer data of a layer, including the virtual and physical memory addresses. 

## **Summary**<a name="section252323968093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table319746025093529"></a>
<table><thead align="left"><tr id="row1260371318093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2132828713093529"><a name="p2132828713093529"></a><a name="p2132828713093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1374347013093529"><a name="p1374347013093529"></a><a name="p1374347013093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row202378074093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p406859367093529"><a name="p406859367093529"></a><a name="p406859367093529"></a><a href="BufferData.md#a6e2adcd036df26d903bb8d464ac8f79d">phyAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p170898936093529"><a name="p170898936093529"></a><a name="p170898936093529"></a>uint64_t&nbsp;</p>
</td>
</tr>
<tr id="row845602466093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2059199609093529"><a name="p2059199609093529"></a><a name="p2059199609093529"></a><a href="BufferData.md#a1deeebc7e7c016ff350f6fdf6e054901">virAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798707719093529"><a name="p798707719093529"></a><a name="p798707719093529"></a>void *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section297431245093529"></a>

## **Field Documentation**<a name="section554373364093529"></a>

## phyAddr<a name="a6e2adcd036df26d903bb8d464ac8f79d"></a>

```
uint64_t BufferData::phyAddr
```

 **Description:**

Physical memory address 

## virAddr<a name="a1deeebc7e7c016ff350f6fdf6e054901"></a>

```
void* BufferData::virAddr
```

 **Description:**

Virtual memory address 

