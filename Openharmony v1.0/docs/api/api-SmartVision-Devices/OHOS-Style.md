# OHOS::Style<a name="ZH-CN_TOPIC_0000001055518122"></a>

## **Overview**<a name="section2108654161093535"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the basic attributes and functions of a style. You can use this class to set different styles. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section549467273093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table620474465093535"></a>
<table><thead align="left"><tr id="row1392097237093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p844187577093535"><a name="p844187577093535"></a><a name="p844187577093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1390423510093535"><a name="p1390423510093535"></a><a name="p1390423510093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row923617430093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680387646093535"><a name="p680387646093535"></a><a name="p680387646093535"></a><a href="Graphic.md#ga592b31b43819c40563c52fe7b45d9358">Style</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p123921535093535"><a name="p123921535093535"></a><a name="p123921535093535"></a>&nbsp;</p>
<p id="p428771639093535"><a name="p428771639093535"></a><a name="p428771639093535"></a>A constructor used to create a <strong id="b1519572613093535"><a name="b1519572613093535"></a><a name="b1519572613093535"></a><a href="OHOS-Style.md">Style</a></strong> instance. </p>
</td>
</tr>
<tr id="row513978450093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p619407309093535"><a name="p619407309093535"></a><a name="p619407309093535"></a><a href="Graphic.md#ga6356d56766de8fe37d4888ef70f521ec">~Style</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060878766093535"><a name="p1060878766093535"></a><a name="p1060878766093535"></a>virtual&nbsp;</p>
<p id="p1650272926093535"><a name="p1650272926093535"></a><a name="p1650272926093535"></a>A destructor used to delete the <strong id="b411275292093535"><a name="b411275292093535"></a><a name="b411275292093535"></a><a href="OHOS-Style.md">Style</a></strong> instance. </p>
</td>
</tr>
<tr id="row1855002966093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1941049711093535"><a name="p1941049711093535"></a><a name="p1941049711093535"></a><a href="Graphic.md#ga31941bb1abbb6744ee832d4b0fe6e080">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449218336093535"><a name="p1449218336093535"></a><a name="p1449218336093535"></a>void&nbsp;</p>
<p id="p615725530093535"><a name="p615725530093535"></a><a name="p615725530093535"></a>Sets a style. </p>
</td>
</tr>
<tr id="row678079210093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p115903671093535"><a name="p115903671093535"></a><a name="p115903671093535"></a><a href="Graphic.md#ga2b4b818f26822ad6a020473e6a5e5214">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p365913227093535"><a name="p365913227093535"></a><a name="p365913227093535"></a>int64_t&nbsp;</p>
<p id="p142755439093535"><a name="p142755439093535"></a><a name="p142755439093535"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1816506074093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p136577877093535"><a name="p136577877093535"></a><a name="p136577877093535"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640618871093535"><a name="p1640618871093535"></a><a name="p1640618871093535"></a>void *&nbsp;</p>
<p id="p297654919093535"><a name="p297654919093535"></a><a name="p297654919093535"></a>Overrides the <strong id="b1856003185093535"><a name="b1856003185093535"></a><a name="b1856003185093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row340579671093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p340982175093535"><a name="p340982175093535"></a><a name="p340982175093535"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p583621766093535"><a name="p583621766093535"></a><a name="p583621766093535"></a>void&nbsp;</p>
<p id="p1471711746093535"><a name="p1471711746093535"></a><a name="p1471711746093535"></a>Overrides the <strong id="b1911358044093535"><a name="b1911358044093535"></a><a name="b1911358044093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

