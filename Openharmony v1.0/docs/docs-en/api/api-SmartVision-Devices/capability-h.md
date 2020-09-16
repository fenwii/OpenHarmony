# capability.h<a name="EN-US_TOPIC_0000001055387980"></a>

## **Overview**<a name="section570030333084829"></a>

**Related Modules:**

[PROCESS](process.md)

**Description:**

Provides functions and related data structures for obtaining and setting process capabilities. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section743817236084829"></a>

## Functions<a name="func-members"></a>

<a name="table821794587084829"></a>
<table><thead align="left"><tr id="row702118191084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1107978012084829"><a name="p1107978012084829"></a><a name="p1107978012084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1438850312084829"><a name="p1438850312084829"></a><a name="p1438850312084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row915838169084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985686257084829"><a name="p985686257084829"></a><a name="p985686257084829"></a><a href="process.md#gaa284eba1654e9fc0672aca2a6d2cd0ce">capget</a> (cap_user_header_t hdr_ptr, cap_user_data_t data_ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p905455941084829"><a name="p905455941084829"></a><a name="p905455941084829"></a>int </p>
<p id="p995457228084829"><a name="p995457228084829"></a><a name="p995457228084829"></a>Obtains the capability information of a specified process based on the input parameters (compatible with the Linux API format). </p>
</td>
</tr>
<tr id="row1469934048084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425913678084829"><a name="p425913678084829"></a><a name="p425913678084829"></a><a href="process.md#gaaa15be01b20aff9efb09de5a8ead207e">capset</a> (cap_user_header_t hdr_ptr, const cap_user_data_t data_ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669905243084829"><a name="p669905243084829"></a><a name="p669905243084829"></a>int </p>
<p id="p1371697071084829"><a name="p1371697071084829"></a><a name="p1371697071084829"></a>Sets the capability information for a specified process based on the input parameters (compatible with the Linux API format). </p>
</td>
</tr>
<tr id="row1878850774084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1845969413084829"><a name="p1845969413084829"></a><a name="p1845969413084829"></a><a href="process.md#gadc569f762fec70a992db20cfec698e29">ohos_capget</a> (unsigned int *caps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088208562084829"><a name="p1088208562084829"></a><a name="p1088208562084829"></a>int </p>
<p id="p2091301513084829"><a name="p2091301513084829"></a><a name="p2091301513084829"></a>Obtains the capability information of a specified process based on the input parameters. </p>
</td>
</tr>
<tr id="row64042473084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1336377112084829"><a name="p1336377112084829"></a><a name="p1336377112084829"></a><a href="process.md#ga77ad7758babf522e7ffb28551332a659">ohos_capset</a> (unsigned int caps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p421073487084829"><a name="p421073487084829"></a><a name="p421073487084829"></a>int </p>
<p id="p2080406601084829"><a name="p2080406601084829"></a><a name="p2080406601084829"></a>Sets the capability information of a specified process based on the input parameters. </p>
</td>
</tr>
</tbody>
</table>

