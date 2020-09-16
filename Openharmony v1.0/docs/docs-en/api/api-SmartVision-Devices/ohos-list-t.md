# OHOS::List< T \><a name="EN-US_TOPIC_0000001055678126"></a>

## **Overview**<a name="section965963051093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a linked list template class, which implements the data structure of bidirectional linked list and provides basic functions such as adding, deleting, inserting, clearing, popping up, and obtaining the size of the linked list. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2018194964093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table237376472093535"></a>
<table><thead align="left"><tr id="row1214409965093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p814485051093535"><a name="p814485051093535"></a><a name="p814485051093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1209819071093535"><a name="p1209819071093535"></a><a name="p1209819071093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row864247227093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176169038093535"><a name="p176169038093535"></a><a name="p176169038093535"></a><a href="graphic.md#ga92532583f91e7cb84255ddbacc34b3e6">List</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1440841676093535"><a name="p1440841676093535"></a><a name="p1440841676093535"></a> </p>
<p id="p1974452479093535"><a name="p1974452479093535"></a><a name="p1974452479093535"></a>A default constructor used to create a <strong id="b1422991723093535"><a name="b1422991723093535"></a><a name="b1422991723093535"></a><a href="ohos-list-t.md">List</a></strong> instance. The initial size is <strong id="b900484718093535"><a name="b900484718093535"></a><a name="b900484718093535"></a>0</strong>. </p>
</td>
</tr>
<tr id="row367635340093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p136958496093535"><a name="p136958496093535"></a><a name="p136958496093535"></a><a href="graphic.md#gae36a1bb98e3352c2b97423ca340a51a9">~List</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1972706612093535"><a name="p1972706612093535"></a><a name="p1972706612093535"></a>virtual </p>
<p id="p1857457833093535"><a name="p1857457833093535"></a><a name="p1857457833093535"></a>A destructor used to delete the <strong id="b374100739093535"><a name="b374100739093535"></a><a name="b374100739093535"></a><a href="ohos-list-t.md">List</a></strong> instance. </p>
</td>
</tr>
<tr id="row842418913093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p539868339093535"><a name="p539868339093535"></a><a name="p539868339093535"></a><a href="graphic.md#ga5e52d77c60c7710ca70ba3720b260c6a">Front</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1014332058093535"><a name="p1014332058093535"></a><a name="p1014332058093535"></a>const T </p>
<p id="p1105794174093535"><a name="p1105794174093535"></a><a name="p1105794174093535"></a>Obtains the head node data of a linked list. </p>
</td>
</tr>
<tr id="row313982868093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133215436093535"><a name="p2133215436093535"></a><a name="p2133215436093535"></a><a href="graphic.md#gae5c3f6272b58c45f458c475a79ebfe3d">Back</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343508726093535"><a name="p343508726093535"></a><a name="p343508726093535"></a>const T </p>
<p id="p218988823093535"><a name="p218988823093535"></a><a name="p218988823093535"></a>Obtains the tail node data of a linked list. </p>
</td>
</tr>
<tr id="row1854269693093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1717955174093535"><a name="p1717955174093535"></a><a name="p1717955174093535"></a><a href="graphic.md#gad26996a2802e32e89ecefa8311fe5d27">PushBack</a> (T data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555417860093535"><a name="p1555417860093535"></a><a name="p1555417860093535"></a>void </p>
<p id="p955304063093535"><a name="p955304063093535"></a><a name="p955304063093535"></a>Inserts data at the end of a linked list. </p>
</td>
</tr>
<tr id="row1444572328093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328076155093535"><a name="p328076155093535"></a><a name="p328076155093535"></a><a href="graphic.md#ga5084ab98dce9aab41b216f73a04ed8b6">PushFront</a> (T data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1115377960093535"><a name="p1115377960093535"></a><a name="p1115377960093535"></a>void </p>
<p id="p23726567093535"><a name="p23726567093535"></a><a name="p23726567093535"></a>Inserts data at the start of a linked list. </p>
</td>
</tr>
<tr id="row1465844936093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1958493835093535"><a name="p1958493835093535"></a><a name="p1958493835093535"></a><a href="graphic.md#ga667b81954fd60474b575b4aa9c6bc193">PopBack</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p328686225093535"><a name="p328686225093535"></a><a name="p328686225093535"></a>void </p>
<p id="p784663505093535"><a name="p784663505093535"></a><a name="p784663505093535"></a>Pops up a data record at the end of a linked list. </p>
</td>
</tr>
<tr id="row26922725093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416058486093535"><a name="p416058486093535"></a><a name="p416058486093535"></a><a href="graphic.md#ga0fa953b7476412923f25d079431f7189">PopFront</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p582644141093535"><a name="p582644141093535"></a><a name="p582644141093535"></a>void </p>
<p id="p1154341097093535"><a name="p1154341097093535"></a><a name="p1154341097093535"></a>Pops up a data record at the start of a linked list. </p>
</td>
</tr>
<tr id="row530134640093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549757858093535"><a name="p549757858093535"></a><a name="p549757858093535"></a><a href="graphic.md#ga3bdd5d105c9e7d7e18456dfb55ba8b45">Insert</a> (<a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; *node, T data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2130753822093535"><a name="p2130753822093535"></a><a name="p2130753822093535"></a>void </p>
<p id="p1721680024093535"><a name="p1721680024093535"></a><a name="p1721680024093535"></a>Inserts data before a specified node, which follows the inserted data node. </p>
</td>
</tr>
<tr id="row1249507990093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p945043277093535"><a name="p945043277093535"></a><a name="p945043277093535"></a><a href="graphic.md#gaf3806e9581846930ad5bf063ced38367">Remove</a> (<a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; *node)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851549972093535"><a name="p1851549972093535"></a><a name="p1851549972093535"></a>void </p>
<p id="p348495271093535"><a name="p348495271093535"></a><a name="p348495271093535"></a>Deletes a data node. </p>
</td>
</tr>
<tr id="row1382209790093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p82011437093535"><a name="p82011437093535"></a><a name="p82011437093535"></a><a href="graphic.md#ga2292866786c9f888bc722ffcebc7c831">Clear</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p820144600093535"><a name="p820144600093535"></a><a name="p820144600093535"></a>void </p>
<p id="p2089423948093535"><a name="p2089423948093535"></a><a name="p2089423948093535"></a>Deletes all nodes from a linked list. </p>
</td>
</tr>
<tr id="row553782959093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422293740093535"><a name="p422293740093535"></a><a name="p422293740093535"></a><a href="graphic.md#ga74dcfe1a4b37d6fabbcdb5f8049fb578">Head</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996333690093535"><a name="p996333690093535"></a><a name="p996333690093535"></a><a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; * </p>
<p id="p1377590836093535"><a name="p1377590836093535"></a><a name="p1377590836093535"></a>Obtains the head node address of a linked list. </p>
</td>
</tr>
<tr id="row704752045093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549791968093535"><a name="p549791968093535"></a><a name="p549791968093535"></a><a href="graphic.md#gab60fda7a08504db2cf992de435ad1848">Tail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p301262696093535"><a name="p301262696093535"></a><a name="p301262696093535"></a><a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; * </p>
<p id="p2120630251093535"><a name="p2120630251093535"></a><a name="p2120630251093535"></a>Obtains the tail node address of a linked list. </p>
</td>
</tr>
<tr id="row1897529712093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315393380093535"><a name="p315393380093535"></a><a name="p315393380093535"></a><a href="graphic.md#ga8fe8647f764773c29d3fa70c9b70eb2a">Begin</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79316061093535"><a name="p79316061093535"></a><a name="p79316061093535"></a><a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; * </p>
<p id="p994769156093535"><a name="p994769156093535"></a><a name="p994769156093535"></a>Obtains the head node address of a linked list. </p>
</td>
</tr>
<tr id="row1930309012093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2107612287093535"><a name="p2107612287093535"></a><a name="p2107612287093535"></a><a href="graphic.md#ga839de65540644c9725b31959367355c5">End</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45766537093535"><a name="p45766537093535"></a><a name="p45766537093535"></a>const <a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; * </p>
<p id="p1685504002093535"><a name="p1685504002093535"></a><a name="p1685504002093535"></a>Obtains the end node address of a linked list. </p>
</td>
</tr>
<tr id="row819522621093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p808343164093535"><a name="p808343164093535"></a><a name="p808343164093535"></a><a href="graphic.md#ga93ec1e9e9b778751aa53b7afb0b67258">Next</a> (const <a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; *node) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307825907093535"><a name="p307825907093535"></a><a name="p307825907093535"></a><a href="ohos-listnode-t.md">ListNode</a>&lt; T &gt; * </p>
<p id="p1437513343093535"><a name="p1437513343093535"></a><a name="p1437513343093535"></a>Obtains the address of the node following the specified <strong id="b484640267093535"><a name="b484640267093535"></a><a name="b484640267093535"></a>node</strong>. </p>
</td>
</tr>
<tr id="row825032147093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1294317588093535"><a name="p1294317588093535"></a><a name="p1294317588093535"></a><a href="graphic.md#ga48f81f9faa9f4057ae8f84e437d90442">IsEmpty</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1610897723093535"><a name="p1610897723093535"></a><a name="p1610897723093535"></a>bool </p>
<p id="p258235851093535"><a name="p258235851093535"></a><a name="p258235851093535"></a>Checks whether a linked list is empty. </p>
</td>
</tr>
<tr id="row1496968028093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1057083896093535"><a name="p1057083896093535"></a><a name="p1057083896093535"></a><a href="graphic.md#gae209f40639cdee7a5b07dc6587dac170">Size</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825875689093535"><a name="p1825875689093535"></a><a name="p1825875689093535"></a>uint16_t </p>
<p id="p1685566564093535"><a name="p1685566564093535"></a><a name="p1685566564093535"></a>Obtains the size of a linked list. </p>
</td>
</tr>
<tr id="row797564814093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p397588334093535"><a name="p397588334093535"></a><a name="p397588334093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p147157838093535"><a name="p147157838093535"></a><a name="p147157838093535"></a>void * </p>
<p id="p1522454176093535"><a name="p1522454176093535"></a><a name="p1522454176093535"></a>Overrides the <strong id="b91500885093535"><a name="b91500885093535"></a><a name="b91500885093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row413049094093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001200379093535"><a name="p1001200379093535"></a><a name="p1001200379093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1260341487093535"><a name="p1260341487093535"></a><a name="p1260341487093535"></a>void </p>
<p id="p1376592439093535"><a name="p1376592439093535"></a><a name="p1376592439093535"></a>Overrides the <strong id="b376822088093535"><a name="b376822088093535"></a><a name="b376822088093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

