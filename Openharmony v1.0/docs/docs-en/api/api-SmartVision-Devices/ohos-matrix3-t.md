# OHOS::Matrix3< T \><a name="EN-US_TOPIC_0000001055039548"></a>

## **Overview**<a name="section1057195079093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a 3 x 3 matrix. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section418850123093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table212649853093535"></a>
<table><thead align="left"><tr id="row1465179318093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p383046308093535"><a name="p383046308093535"></a><a name="p383046308093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p809880963093535"><a name="p809880963093535"></a><a name="p809880963093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2003137152093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1241739101093535"><a name="p1241739101093535"></a><a name="p1241739101093535"></a><a href="graphic.md#ga8fedd026cac422882e9c0a0d5d1f3b50">Matrix3</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854547715093535"><a name="p854547715093535"></a><a name="p854547715093535"></a> </p>
<p id="p1065864924093535"><a name="p1065864924093535"></a><a name="p1065864924093535"></a>Defines a <strong id="b303532962093535"><a name="b303532962093535"></a><a name="b303532962093535"></a><a href="ohos-matrix3-t.md">Matrix3</a></strong> instance and initializes the 3 x 3 matrix data. </p>
</td>
</tr>
<tr id="row95102199093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p43332724093535"><a name="p43332724093535"></a><a name="p43332724093535"></a><a href="graphic.md#ga068d055d130c7c46269072bf65254082">Matrix3</a> (T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2062160409093535"><a name="p2062160409093535"></a><a name="p2062160409093535"></a> </p>
<p id="p1552186000093535"><a name="p1552186000093535"></a><a name="p1552186000093535"></a>Defines a <strong id="b1162026835093535"><a name="b1162026835093535"></a><a name="b1162026835093535"></a><a href="ohos-matrix3-t.md">Matrix3</a></strong> instance and initializes the 3 x 3 matrix data. </p>
</td>
</tr>
<tr id="row877831004093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p910697128093535"><a name="p910697128093535"></a><a name="p910697128093535"></a><a href="graphic.md#ga9cf7c2656623468c34003bb3c4056a72">~Matrix3</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448137344093535"><a name="p448137344093535"></a><a name="p448137344093535"></a> </p>
<p id="p1194970341093535"><a name="p1194970341093535"></a><a name="p1194970341093535"></a>A destructor used to delete the <strong id="b668805540093535"><a name="b668805540093535"></a><a name="b668805540093535"></a><a href="ohos-matrix3-t.md">Matrix3</a></strong> instance. </p>
</td>
</tr>
<tr id="row2086765940093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221257751093535"><a name="p1221257751093535"></a><a name="p1221257751093535"></a><a href="graphic.md#ga8fd60ee68cc3a51d8c7ea9d3d665323c">GetData</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415975102093535"><a name="p415975102093535"></a><a name="p415975102093535"></a>const T * </p>
<p id="p1658507425093535"><a name="p1658507425093535"></a><a name="p1658507425093535"></a>Obtains the 3 x 3 matrix data. </p>
</td>
</tr>
<tr id="row362782337093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963915830093535"><a name="p963915830093535"></a><a name="p963915830093535"></a><a href="graphic.md#ga5464ffd57d0abbd0381b2a6cf3a7d2fb">Determinant</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1807157117093535"><a name="p1807157117093535"></a><a name="p1807157117093535"></a>T </p>
<p id="p1479835198093535"><a name="p1479835198093535"></a><a name="p1479835198093535"></a>Obtains the determinant of the matrix. </p>
</td>
</tr>
<tr id="row799778879093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725184543093535"><a name="p725184543093535"></a><a name="p725184543093535"></a><a href="graphic.md#gabf1edc9a01bace13596de01615ae20a2">Inverse</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1208229890093535"><a name="p1208229890093535"></a><a name="p1208229890093535"></a><a href="ohos-matrix3-t.md">Matrix3</a> </p>
<p id="p2111978631093535"><a name="p2111978631093535"></a><a name="p2111978631093535"></a>Obtains the inverse matrix. </p>
</td>
</tr>
<tr id="row1424363713093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413409626093535"><a name="p1413409626093535"></a><a name="p1413409626093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870245778093535"><a name="p1870245778093535"></a><a name="p1870245778093535"></a>void * </p>
<p id="p515527655093535"><a name="p515527655093535"></a><a name="p515527655093535"></a>Overrides the <strong id="b1856300574093535"><a name="b1856300574093535"></a><a name="b1856300574093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row428473992093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p293268650093535"><a name="p293268650093535"></a><a name="p293268650093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635851355093535"><a name="p635851355093535"></a><a name="p635851355093535"></a>void </p>
<p id="p74413970093535"><a name="p74413970093535"></a><a name="p74413970093535"></a>Overrides the <strong id="b559304360093535"><a name="b559304360093535"></a><a name="b559304360093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table109650236093535"></a>
<table><thead align="left"><tr id="row1503677222093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1312366474093535"><a name="p1312366474093535"></a><a name="p1312366474093535"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1873257622093535"><a name="p1873257622093535"></a><a name="p1873257622093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row639289371093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1014642559093535"><a name="p1014642559093535"></a><a name="p1014642559093535"></a><a href="graphic.md#ga8bd72462c8fdba21d3a805a415a88d06">Rotate</a> (T angle, const <a href="ohos-vector2-t.md">Vector2</a>&lt; T &gt; &amp;pivot)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1896342474093535"><a name="p1896342474093535"></a><a name="p1896342474093535"></a>static <a href="ohos-matrix3-t.md">Matrix3</a> </p>
<p id="p2064047681093535"><a name="p2064047681093535"></a><a name="p2064047681093535"></a>Obtains a rotation matrix. After a matrix is rotated, its data is shifted leftwards by 15 bits. Therefore, the result data needs to be shifted rightwards by 15 bits. </p>
</td>
</tr>
<tr id="row1771942696093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1731086554093535"><a name="p1731086554093535"></a><a name="p1731086554093535"></a><a href="graphic.md#ga915aa59cac37c6584fafb06a06046087">Scale</a> (const <a href="ohos-vector2-t.md">Vector2</a>&lt; T &gt; &amp;scale, const <a href="ohos-vector2-t.md">Vector2</a>&lt; T &gt; &amp;fixed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1311410426093535"><a name="p1311410426093535"></a><a name="p1311410426093535"></a>static <a href="ohos-matrix3-t.md">Matrix3</a> </p>
<p id="p96768868093535"><a name="p96768868093535"></a><a name="p96768868093535"></a>Obtains the scaling matrix. After a matrix is scaled, its data is shifted leftwards by 8 bits. Therefore, the result data needs to be shifted rightwards by 8 bits. </p>
</td>
</tr>
<tr id="row1229897940093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1262398766093535"><a name="p1262398766093535"></a><a name="p1262398766093535"></a><a href="graphic.md#gab1cbae80ef16538294c97ba81626970e">Translate</a> (const <a href="ohos-vector2-t.md">Vector2</a>&lt; T &gt; &amp;trans)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1761980472093535"><a name="p1761980472093535"></a><a name="p1761980472093535"></a>static <a href="ohos-matrix3-t.md">Matrix3</a>&lt; T &gt; </p>
<p id="p1134111254093535"><a name="p1134111254093535"></a><a name="p1134111254093535"></a>Obtains a matrix translation. </p>
</td>
</tr>
</tbody>
</table>

