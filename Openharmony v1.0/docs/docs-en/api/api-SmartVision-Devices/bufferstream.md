# BufferStream<a name="EN-US_TOPIC_0000001055518082"></a>

## **Overview**<a name="section768519582093529"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines the function for reading stream data. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section931399633093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1452526778093529"></a>
<table><thead align="left"><tr id="row1323234146093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p441301631093529"><a name="p441301631093529"></a><a name="p441301631093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1552533267093529"><a name="p1552533267093529"></a><a name="p1552533267093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1997461826093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323546637093529"><a name="p1323546637093529"></a><a name="p1323546637093529"></a><a href="bufferstream.md#af0c4387f21bba2c1f02a5310daa95a00">ReadData</a> )(void *<a href="bufferstream.md#ae2019a77aba73fa96d5a716155c7fb7f">handle</a>, uint8_t *data, int32_t size, int32_t timeOutMs, <a href="format.md#gacff079fdf8427c743f9197ea5be33a7f">DataFlags</a> *flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p766582115093529"><a name="p766582115093529"></a><a name="p766582115093529"></a>int32_t(* </p>
<p id="p387230513093529"><a name="p387230513093529"></a><a name="p387230513093529"></a>Reads data from streams, save the data to the buffer pointed by <strong id="b1222491118093529"><a name="b1222491118093529"></a><a name="b1222491118093529"></a>data</strong> with the specified <strong id="b613371266093529"><a name="b613371266093529"></a><a name="b613371266093529"></a>size</strong>, and returns the size of the read data and type. </p>
</td>
</tr>
<tr id="row1216511084093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1406357602093529"><a name="p1406357602093529"></a><a name="p1406357602093529"></a><a href="bufferstream.md#a24e47ffeb7e9c2a8e01f83ffb3a16407">GetReadableSize</a> )(const void *<a href="bufferstream.md#ae2019a77aba73fa96d5a716155c7fb7f">handle</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1158899833093529"><a name="p1158899833093529"></a><a name="p1158899833093529"></a>int32_t(* </p>
<p id="p1204108019093529"><a name="p1204108019093529"></a><a name="p1204108019093529"></a>Obtains the size of data that can be read. </p>
</td>
</tr>
<tr id="row328899468093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p200010745093529"><a name="p200010745093529"></a><a name="p200010745093529"></a><a href="bufferstream.md#ae2019a77aba73fa96d5a716155c7fb7f">handle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p697775831093529"><a name="p697775831093529"></a><a name="p697775831093529"></a>void * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1674721808093529"></a>

## **Field Documentation**<a name="section1513064537093529"></a>

## GetReadableSize<a name="a24e47ffeb7e9c2a8e01f83ffb3a16407"></a>

```
int32_t(* BufferStream::GetReadableSize) (const void *[handle](bufferstream.md#ae2019a77aba73fa96d5a716155c7fb7f))
```

 **Description:**

Obtains the size of data that can be read. 

Before reading data, you should call this function to check whether there is data to read.

**Parameters:**

<a name="table707523236093529"></a>
<table><thead align="left"><tr id="row1227170241093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p612879636093529"><a name="p612879636093529"></a><a name="p612879636093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p809849653093529"><a name="p809849653093529"></a><a name="p809849653093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row302141161093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the context handle. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the size of the read data. 



## handle<a name="ae2019a77aba73fa96d5a716155c7fb7f"></a>

```
void* BufferStream::handle
```

 **Description:**

Context handle 

## ReadData<a name="af0c4387f21bba2c1f02a5310daa95a00"></a>

```
int32_t(* BufferStream::ReadData) (void *[handle](bufferstream.md#ae2019a77aba73fa96d5a716155c7fb7f), uint8_t *data, int32_t size, int32_t timeOutMs, [DataFlags](format.md#gacff079fdf8427c743f9197ea5be33a7f) *flags)
```

 **Description:**

Reads data from streams, save the data to the buffer pointed by  **data**  with the specified  **size**, and returns the size of the read data and type. 

**Parameters:**

<a name="table1931880739093529"></a>
<table><thead align="left"><tr id="row669909289093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p335502138093529"><a name="p335502138093529"></a><a name="p335502138093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1662677005093529"><a name="p1662677005093529"></a><a name="p1662677005093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1477108758093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the context handle. </td>
</tr>
<tr id="row1593245296093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer to store the read data. The memory is allocated by the caller. </td>
</tr>
<tr id="row1010827668093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the available buffer memory. </td>
</tr>
<tr id="row1225687994093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOutMs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates read operation wait time. The value <strong id="b99771570093529"><a name="b99771570093529"></a><a name="b99771570093529"></a>0</strong> means no wait time. </td>
</tr>
<tr id="row962851156093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the type of the read data, see <a href="format.md#gacff079fdf8427c743f9197ea5be33a7f">DataFlags</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the size of the read data. 



