# FormatCallback<a name="EN-US_TOPIC_0000001055358106"></a>

## **Overview**<a name="section1756292648093530"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines listener callbacks for the format. 

## **Summary**<a name="section487629430093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1429770207093530"></a>
<table><thead align="left"><tr id="row311806369093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p992922799093530"><a name="p992922799093530"></a><a name="p992922799093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1736997678093530"><a name="p1736997678093530"></a><a name="p1736997678093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row920607240093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1279026383093530"><a name="p1279026383093530"></a><a name="p1279026383093530"></a><a href="formatcallback.md#a4e4c7c6789cbf8bfc1aa0444dcd106b5">privateDataHandle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p937898137093530"><a name="p937898137093530"></a><a name="p937898137093530"></a><a href="format.md#gab928f39c359734527bda3fd160f89331">CALLBACK_HANDLE</a> </p>
</td>
</tr>
<tr id="row1683114336093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069840523093530"><a name="p2069840523093530"></a><a name="p2069840523093530"></a><a href="formatcallback.md#a47f30ebe4db3087e01c4259c0a983588">OnError</a> )(<a href="format.md#gab928f39c359734527bda3fd160f89331">CALLBACK_HANDLE</a> <a href="formatcallback.md#a4e4c7c6789cbf8bfc1aa0444dcd106b5">privateDataHandle</a>, int32_t errorType, int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669298759093530"><a name="p669298759093530"></a><a name="p669298759093530"></a>int32_t(* </p>
<p id="p100764849093530"><a name="p100764849093530"></a><a name="p100764849093530"></a>Called when a format error occurs during capturing. This callback is used to report the errors. </p>
</td>
</tr>
<tr id="row1338837790093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527556392093530"><a name="p1527556392093530"></a><a name="p1527556392093530"></a><a href="formatcallback.md#a24b3d9a290f39522c4a733d141772cb1">OnInfo</a> )(<a href="format.md#gab928f39c359734527bda3fd160f89331">CALLBACK_HANDLE</a> <a href="formatcallback.md#a4e4c7c6789cbf8bfc1aa0444dcd106b5">privateDataHandle</a>, int32_t type, int32_t extra)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807725600093530"><a name="p807725600093530"></a><a name="p807725600093530"></a>int32_t(* </p>
<p id="p650230144093530"><a name="p650230144093530"></a><a name="p650230144093530"></a>Called when an information event occurs during capturing. This callback is used to report capturing information. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section396259517093530"></a>

## **Field Documentation**<a name="section45078836093530"></a>

## OnError<a name="a47f30ebe4db3087e01c4259c0a983588"></a>

```
int32_t(* FormatCallback::OnError) ([CALLBACK_HANDLE](format.md#gab928f39c359734527bda3fd160f89331) [privateDataHandle](formatcallback.md#a4e4c7c6789cbf8bfc1aa0444dcd106b5), int32_t errorType, int32_t errorCode)
```

 **Description:**

Called when a format error occurs during capturing. This callback is used to report the errors. 

**Parameters:**

<a name="table345588598093530"></a>
<table><thead align="left"><tr id="row912952937093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1079188798093530"><a name="p1079188798093530"></a><a name="p1079188798093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1891363060093530"><a name="p1891363060093530"></a><a name="p1891363060093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row342436121093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">privateDataHandle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the private data handle. </td>
</tr>
<tr id="row351846281093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error type. For details, see <a href="format.md#ga31e7fcf42722fa15e4e5489c2fef9092">FormatErrorType</a>. </td>
</tr>
<tr id="row644332350093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorCode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the error code. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## OnInfo<a name="a24b3d9a290f39522c4a733d141772cb1"></a>

```
int32_t(* FormatCallback::OnInfo) ([CALLBACK_HANDLE](format.md#gab928f39c359734527bda3fd160f89331) [privateDataHandle](formatcallback.md#a4e4c7c6789cbf8bfc1aa0444dcd106b5), int32_t type, int32_t extra)
```

 **Description:**

Called when an information event occurs during capturing. This callback is used to report capturing information. 

**Parameters:**

<a name="table908062449093530"></a>
<table><thead align="left"><tr id="row207160540093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p385647452093530"><a name="p385647452093530"></a><a name="p385647452093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1395909945093530"><a name="p1395909945093530"></a><a name="p1395909945093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row957586861093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">privateDataHandle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the private data handle. </td>
</tr>
<tr id="row546648600093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the information type. For details, see <a href="format.md#ga6f00342925d3d5e586c76f8695985cad">FormatInfoType</a>. </td>
</tr>
<tr id="row25357983093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">extra</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates other information, for example, the start time position of the captured file. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise. 



## privateDataHandle<a name="a4e4c7c6789cbf8bfc1aa0444dcd106b5"></a>

```
[CALLBACK_HANDLE](format.md#gab928f39c359734527bda3fd160f89331) FormatCallback::privateDataHandle
```

 **Description:**

Private data handle 

