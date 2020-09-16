# mem\_api.h<a name="EN-US_TOPIC_0000001055198104"></a>

## **Overview**<a name="section451764427093526"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the functions for memory application and release. You can implement the  **malloc**  and  **free**  functions to manage the memory. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1007106306093526"></a>

## Functions<a name="func-members"></a>

<a name="table1539408624093526"></a>
<table><thead align="left"><tr id="row661290526093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p598015841093526"><a name="p598015841093526"></a><a name="p598015841093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1484983473093526"><a name="p1484983473093526"></a><a name="p1484983473093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1480823944093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p22923401093526"><a name="p22923401093526"></a><a name="p22923401093526"></a><a href="graphic.md#gaabb0ea584d8faebbdcb45fcc11447b8b">OHOS::ImageCacheMalloc</a> (ImageInfo &amp;info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657205150093526"><a name="p1657205150093526"></a><a name="p1657205150093526"></a>void * </p>
<p id="p1685033550093526"><a name="p1685033550093526"></a><a name="p1685033550093526"></a>Applies for the image cache memory. You can customize the memory area when loading image resources. </p>
</td>
</tr>
<tr id="row445042995093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014145699093526"><a name="p2014145699093526"></a><a name="p2014145699093526"></a><a href="graphic.md#ga71fe0f3eb82083006b51fec59ad11088">OHOS::ImageCacheFree</a> (ImageInfo &amp;info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1216839070093526"><a name="p1216839070093526"></a><a name="p1216839070093526"></a>void </p>
<p id="p1280821734093526"><a name="p1280821734093526"></a><a name="p1280821734093526"></a>Releases the image cache memory. </p>
</td>
</tr>
<tr id="row806496632093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p270328284093526"><a name="p270328284093526"></a><a name="p270328284093526"></a><a href="graphic.md#gafc7b2c7d0b427079d8b04b11cc4db009">OHOS::UIMalloc</a> (uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513412128093526"><a name="p1513412128093526"></a><a name="p1513412128093526"></a>void * </p>
<p id="p263350466093526"><a name="p263350466093526"></a><a name="p263350466093526"></a>Applies for memory for the graphics module. You can implement this function to override the <strong id="b1188092630093526"><a name="b1188092630093526"></a><a name="b1188092630093526"></a>malloc</strong> and <strong id="b311118695093526"><a name="b311118695093526"></a><a name="b311118695093526"></a>new</strong> functions. </p>
</td>
</tr>
<tr id="row182471555093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040690043093526"><a name="p2040690043093526"></a><a name="p2040690043093526"></a><a href="graphic.md#ga77914ea7bc96f6cb30f65ae2014746e8">OHOS::UIFree</a> (void *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265248880093526"><a name="p265248880093526"></a><a name="p265248880093526"></a>void </p>
<p id="p383787147093526"><a name="p383787147093526"></a><a name="p383787147093526"></a>Releases memory for the graphics module. You can implement this function to override the <strong id="b2097907477093526"><a name="b2097907477093526"></a><a name="b2097907477093526"></a>free</strong> and <strong id="b1376296542093526"><a name="b1376296542093526"></a><a name="b1376296542093526"></a>delete</strong> functions. </p>
</td>
</tr>
</tbody>
</table>

