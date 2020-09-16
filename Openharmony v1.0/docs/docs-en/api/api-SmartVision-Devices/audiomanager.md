# AudioManager<a name="EN-US_TOPIC_0000001054598151"></a>

## **Overview**<a name="section2067960358093529"></a>

**Related Modules:**

[Audio](audio.md)

**Description:**

Manages audio adapters through a specific adapter driver program loaded based on the given audio adapter descriptor. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1894073402093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2082499934093529"></a>
<table><thead align="left"><tr id="row713939675093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p273140907093529"><a name="p273140907093529"></a><a name="p273140907093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1021554312093529"><a name="p1021554312093529"></a><a name="p1021554312093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row748406243093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733388767093529"><a name="p1733388767093529"></a><a name="p1733388767093529"></a><a href="audiomanager.md#a93a0ffb0df907fabcfca827d31dadf39">GetAllAdapters</a> )(struct <a href="audiomanager.md">AudioManager</a> *manager, struct <a href="audioadapterdescriptor.md">AudioAdapterDescriptor</a> **descs, int32_t *size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083020219093529"><a name="p2083020219093529"></a><a name="p2083020219093529"></a>int32_t(* </p>
<p id="p1351898503093529"><a name="p1351898503093529"></a><a name="p1351898503093529"></a>Obtains the list of all adapters supported by an audio driver. </p>
</td>
</tr>
<tr id="row668891931093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813377886093529"><a name="p813377886093529"></a><a name="p813377886093529"></a><a href="audiomanager.md#ab090e9c760a2888b55acc7baa4222ccb">LoadAdapter</a> )(struct <a href="audiomanager.md">AudioManager</a> *manager, const struct <a href="audioadapterdescriptor.md">AudioAdapterDescriptor</a> *desc, struct <a href="audioadapter.md">AudioAdapter</a> **adapter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1268650350093529"><a name="p1268650350093529"></a><a name="p1268650350093529"></a>int32_t(* </p>
<p id="p104197628093529"><a name="p104197628093529"></a><a name="p104197628093529"></a>Loads the driver for an audio adapter. </p>
</td>
</tr>
<tr id="row698057735093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p317899072093529"><a name="p317899072093529"></a><a name="p317899072093529"></a><a href="audiomanager.md#a556137764c5bf784972ba79303720fc3">UnloadAdapter</a> )(struct <a href="audiomanager.md">AudioManager</a> *manager, struct <a href="audioadapter.md">AudioAdapter</a> *adapter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1982866854093529"><a name="p1982866854093529"></a><a name="p1982866854093529"></a>void(* </p>
<p id="p1868168070093529"><a name="p1868168070093529"></a><a name="p1868168070093529"></a>Unloads the driver of an audio adapter. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1659934598093529"></a>

## **Field Documentation**<a name="section654983564093529"></a>

## GetAllAdapters<a name="a93a0ffb0df907fabcfca827d31dadf39"></a>

```
int32_t(* AudioManager::GetAllAdapters) (struct [AudioManager](audiomanager.md) *manager, struct [AudioAdapterDescriptor](audioadapterdescriptor.md) **descs, int32_t *size)
```

 **Description:**

Obtains the list of all adapters supported by an audio driver. 

**Parameters:**

<a name="table1056219980093529"></a>
<table><thead align="left"><tr id="row729588104093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p551971613093529"><a name="p551971613093529"></a><a name="p551971613093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p546930465093529"><a name="p546930465093529"></a><a name="p546930465093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row160433142093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">manager</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter manager to operate. </td>
</tr>
<tr id="row523725233093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">descs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the audio adapter list. </td>
</tr>
<tr id="row1066925309093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the length of the list. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the list is obtained successfully; returns a negative value otherwise. 

**See also:**

[LoadAdapter](audiomanager.md#ab090e9c760a2888b55acc7baa4222ccb) 

## LoadAdapter<a name="ab090e9c760a2888b55acc7baa4222ccb"></a>

```
int32_t(* AudioManager::LoadAdapter) (struct [AudioManager](audiomanager.md) *manager, const struct [AudioAdapterDescriptor](audioadapterdescriptor.md) *desc, struct [AudioAdapter](audioadapter.md) **adapter)
```

 **Description:**

Loads the driver for an audio adapter. 

For example, to load a USB driver, you may need to load a dynamic-link library \(\*.so\) in specific implementation.

**Parameters:**

<a name="table965009965093529"></a>
<table><thead align="left"><tr id="row1525628476093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2042036607093529"><a name="p2042036607093529"></a><a name="p2042036607093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p548932665093529"><a name="p548932665093529"></a><a name="p548932665093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row753263546093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">manager</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter manager to operate. </td>
</tr>
<tr id="row382506739093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">desc</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the descriptor of the audio adapter. </td>
</tr>
<tr id="row552897463093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the audio adapter. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the driver is loaded successfully; returns a negative value otherwise. 

**See also:**

[GetAllAdapters](audiomanager.md#a93a0ffb0df907fabcfca827d31dadf39) 

## UnloadAdapter<a name="a556137764c5bf784972ba79303720fc3"></a>

```
void(* AudioManager::UnloadAdapter) (struct [AudioManager](audiomanager.md) *manager, struct [AudioAdapter](audioadapter.md) *adapter)
```

 **Description:**

Unloads the driver of an audio adapter. 

**Parameters:**

<a name="table868679443093529"></a>
<table><thead align="left"><tr id="row1008245406093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1894088234093529"><a name="p1894088234093529"></a><a name="p1894088234093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p502549433093529"><a name="p502549433093529"></a><a name="p502549433093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row455725036093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">manager</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter manager to operate. </td>
</tr>
<tr id="row1902824982093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">adapter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the audio adapter whose driver will be unloaded. </td>
</tr>
</tbody>
</table>

**See also:**

[LoadAdapter](audiomanager.md#ab090e9c760a2888b55acc7baa4222ccb) 

