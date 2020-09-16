# osThreadAttr\_t<a name="ZH-CN_TOPIC_0000001054595107"></a>

## **Overview**<a name="section1746575538191908"></a>

**Related Modules:**

[CMSIS](zh-cn_topic_0000001055075063.md)

**Description:**

Describes thread attributes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section567445026191908"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1864377955191908"></a>
<table><thead align="left"><tr id="row1682226581191908"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1767875778191908"><a name="p1767875778191908"></a><a name="p1767875778191908"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p848412214191908"><a name="p848412214191908"></a><a name="p848412214191908"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row706014101191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1348084641191908"><a name="p1348084641191908"></a><a name="p1348084641191908"></a><a href="zh-cn_topic_0000001055075063.md#gaed20d9f112c97dcb4fc6374290ab7446">name</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679600132191908"><a name="p679600132191908"></a><a name="p679600132191908"></a>const char *&nbsp;</p>
</td>
</tr>
<tr id="row231910089191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1072388657191908"><a name="p1072388657191908"></a><a name="p1072388657191908"></a><a href="zh-cn_topic_0000001055075063.md#ga5f48a821ddc41410fe625860b6380d3a">attr_bits</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775878856191908"><a name="p775878856191908"></a><a name="p775878856191908"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1430998868191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325534511191908"><a name="p1325534511191908"></a><a name="p1325534511191908"></a><a href="zh-cn_topic_0000001055075063.md#ga378962e098d6fc89cd0bdecaf03b59de">cb_mem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751596759191908"><a name="p751596759191908"></a><a name="p751596759191908"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row1435421852191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709154716191908"><a name="p709154716191908"></a><a name="p709154716191908"></a><a href="zh-cn_topic_0000001055075063.md#ga8992f7ce1ac52bb8682ccd4f42751de5">cb_size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146877508191908"><a name="p1146877508191908"></a><a name="p1146877508191908"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row693094909191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61126726191908"><a name="p61126726191908"></a><a name="p61126726191908"></a><a href="zh-cn_topic_0000001055075063.md#ga8ce05e5336d40cba01b6e1d1e36afe77">stack_mem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p872871025191908"><a name="p872871025191908"></a><a name="p872871025191908"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row1515765918191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2078129152191908"><a name="p2078129152191908"></a><a name="p2078129152191908"></a><a href="zh-cn_topic_0000001055075063.md#gacb537dae7fecd9c744852ff6d6ea2c04">stack_size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1166441162191908"><a name="p1166441162191908"></a><a name="p1166441162191908"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1523632706191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275774299191908"><a name="p275774299191908"></a><a name="p275774299191908"></a><a href="zh-cn_topic_0000001055075063.md#ga90ae74b20698ee175b68f7f53a0b9091">priority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354056165191908"><a name="p1354056165191908"></a><a name="p1354056165191908"></a><a href="zh-cn_topic_0000001055075063.md#gad4e3e0971b41f2d17584a8c6837342ec">osPriority_t</a>&nbsp;</p>
</td>
</tr>
<tr id="row1168493665191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1285975490191908"><a name="p1285975490191908"></a><a name="p1285975490191908"></a><a href="zh-cn_topic_0000001055075063.md#ga5cefc38447dae2c9f3fb81c193c49536">tz_module</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1214128494191908"><a name="p1214128494191908"></a><a name="p1214128494191908"></a><a href="zh-cn_topic_0000001055075063.md#gad5ef21485fe5f60263bc0b48006202cb">TZ_ModuleId_t</a>&nbsp;</p>
</td>
</tr>
<tr id="row156364085191908"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242445286191908"><a name="p1242445286191908"></a><a name="p1242445286191908"></a><a href="zh-cn_topic_0000001055075063.md#ga553fd9961d8f9e4562f84cd68709ae2d">reserved</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327191837191908"><a name="p327191837191908"></a><a name="p327191837191908"></a>uint32_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

