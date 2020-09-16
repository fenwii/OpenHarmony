# OsalFirmware<a name="EN-US_TOPIC_0000001054718141"></a>

## **Overview**<a name="section2063649547093532"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Defines the data structure for operating a firmware file. 

## **Summary**<a name="section125727665093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1673806137093532"></a>
<table><thead align="left"><tr id="row1127994137093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1961319043093532"><a name="p1961319043093532"></a><a name="p1961319043093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1124380161093532"><a name="p1124380161093532"></a><a name="p1124380161093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1697535573093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1086036807093532"><a name="p1086036807093532"></a><a name="p1086036807093532"></a><a href="osalfirmware.md#abc1fab9dde51713c504936594369d067">fwSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147324799093532"><a name="p1147324799093532"></a><a name="p1147324799093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row144228549093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2052593476093532"><a name="p2052593476093532"></a><a name="p2052593476093532"></a><a href="osalfirmware.md#a11f428199ca9e9e4f94c1ef7c2bdea11">para</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179532946093532"><a name="p1179532946093532"></a><a name="p1179532946093532"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section190858918093532"></a>

## **Field Documentation**<a name="section661988190093532"></a>

## fwSize<a name="abc1fab9dde51713c504936594369d067"></a>

```
uint32_t OsalFirmware::fwSize
```

 **Description:**

Firmware file size, which is returned by calling  [OsalRequestFirmware](osal.md#ga428b9de7fb95a20ab9e25b47a7d4272c). 

## para<a name="a11f428199ca9e9e4f94c1ef7c2bdea11"></a>

```
void* OsalFirmware::para
```

 **Description:**

Pointer to a firmware file, which is returned by calling  [OsalRequestFirmware](osal.md#ga428b9de7fb95a20ab9e25b47a7d4272c). You do not need to allocate space. 

