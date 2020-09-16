# SdioFuncInfo<a name="EN-US_TOPIC_0000001055518126"></a>

## **Overview**<a name="section1072546208093536"></a>

**Related Modules:**

[SDIO](sdio.md)

**Description:**

Defines the SDIO capabilities. 

You can obtain and set the SDIO capabilities by calling  [SdioGetCommonInfo](sdio.md#gac5c6bf733ea9e4408fd1109b18741ce8)  and  [SdioSetCommonInfo](sdio.md#ga563b67c90fbb88075bf5a05d9b5d5706)  with  [SdioCommonInfo](sdiocommoninfo.md)  and  [SdioCommonInfoType](sdio.md#ga4037437ac001a9848dd242e8aa632678)  passed. 

## **Summary**<a name="section229400949093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1195343884093536"></a>
<table><thead align="left"><tr id="row1547249317093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1320638981093536"><a name="p1320638981093536"></a><a name="p1320638981093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p972004915093536"><a name="p972004915093536"></a><a name="p972004915093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row276078657093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082073570093536"><a name="p2082073570093536"></a><a name="p2082073570093536"></a><a href="sdiofuncinfo.md#a04d38dfd2a8d39a35eafcfc29b673e26">maxBlockNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023474434093536"><a name="p1023474434093536"></a><a name="p1023474434093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row369928198093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p134294344093536"><a name="p134294344093536"></a><a name="p134294344093536"></a><a href="sdiofuncinfo.md#af5f3459fa5c7b774f59b0dcd70b9a0b6">maxBlockSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635360405093536"><a name="p635360405093536"></a><a name="p635360405093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row682955634093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015019149093536"><a name="p2015019149093536"></a><a name="p2015019149093536"></a><a href="sdiofuncinfo.md#a2b5bfbd05ef54dc65027068de0175d9e">maxRequestSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177409764093536"><a name="p1177409764093536"></a><a name="p1177409764093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row868500515093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p411449086093536"><a name="p411449086093536"></a><a name="p411449086093536"></a><a href="sdiofuncinfo.md#a85c9b17ab885cb72eab7ded6e49d8476">enTimeout</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2103821144093536"><a name="p2103821144093536"></a><a name="p2103821144093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row1236969985093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p656510405093536"><a name="p656510405093536"></a><a name="p656510405093536"></a><a href="sdiofuncinfo.md#a7d99a390cc82cdccda84122580f20e2b">funcNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1781285017093536"><a name="p1781285017093536"></a><a name="p1781285017093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row1157080353093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217231305093536"><a name="p1217231305093536"></a><a name="p1217231305093536"></a><a href="sdiofuncinfo.md#aff0bdebbfd7969076ab2f9ccd2b1867c">irqCap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453589978093536"><a name="p453589978093536"></a><a name="p453589978093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row1495252910093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037392219093536"><a name="p2037392219093536"></a><a name="p2037392219093536"></a><a href="sdiofuncinfo.md#a3867493e7beca9cafb6833523f29ccda">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386921025093536"><a name="p386921025093536"></a><a name="p386921025093536"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section41899832093536"></a>

## **Field Documentation**<a name="section380865490093536"></a>

## data<a name="a3867493e7beca9cafb6833523f29ccda"></a>

```
void* SdioFuncInfo::data
```

 **Description:**

Private data 

## enTimeout<a name="a85c9b17ab885cb72eab7ded6e49d8476"></a>

```
uint32_t SdioFuncInfo::enTimeout
```

 **Description:**

Maximum timeout duration, in milliseconds. The value cannot exceed  **1**  second. 

## funcNum<a name="a7d99a390cc82cdccda84122580f20e2b"></a>

```
uint32_t SdioFuncInfo::funcNum
```

 **Description:**

Functionality number, ranging from  **1**  to  **7**. 

## irqCap<a name="aff0bdebbfd7969076ab2f9ccd2b1867c"></a>

```
uint32_t SdioFuncInfo::irqCap
```

 **Description:**

IRQ capabilities 

## maxBlockNum<a name="a04d38dfd2a8d39a35eafcfc29b673e26"></a>

```
uint32_t SdioFuncInfo::maxBlockNum
```

 **Description:**

Maximum number of blocks in a request 

## maxBlockSize<a name="af5f3459fa5c7b774f59b0dcd70b9a0b6"></a>

```
uint32_t SdioFuncInfo::maxBlockSize
```

 **Description:**

Maximum number of bytes in a block. The value ranges from  **1**  to  **2048**. 

## maxRequestSize<a name="a2b5bfbd05ef54dc65027068de0175d9e"></a>

```
uint32_t SdioFuncInfo::maxRequestSize
```

 **Description:**

Maximum number of bytes in a request. The value ranges from  **1**  to  **2048**. 

