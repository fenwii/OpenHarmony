# WifiIotSdioIntcallback<a name="ZH-CN_TOPIC_0000001055036458"></a>

## **Overview**<a name="section503191905191905"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

SDIO interrupt callback structure. 

## **Summary**<a name="section2105721617191905"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table330753881191905"></a>
<table><thead align="left"><tr id="row1831554242191905"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1095179541191905"><a name="p1095179541191905"></a><a name="p1095179541191905"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p476159290191905"><a name="p476159290191905"></a><a name="p476159290191905"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row36091202191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274073348191905"><a name="p1274073348191905"></a><a name="p1274073348191905"></a><a href="WifiIotSdioIntcallback.md#acc9dad5477a57e9a99c396f17c3a2972">RdstartCallback</a> )(unsigned int len, unsigned char *admaTable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164058388191905"><a name="p1164058388191905"></a><a name="p1164058388191905"></a>int(*&nbsp;</p>
</td>
</tr>
<tr id="row1191083268191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p428972021191905"><a name="p428972021191905"></a><a name="p428972021191905"></a><a href="WifiIotSdioIntcallback.md#a49f5c77ee508f9c6cab65b9c8a84bf3e">RdoverCallback</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1431112239191905"><a name="p1431112239191905"></a><a name="p1431112239191905"></a>int(*&nbsp;</p>
</td>
</tr>
<tr id="row608469975191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p677066270191905"><a name="p677066270191905"></a><a name="p677066270191905"></a><a href="WifiIotSdioIntcallback.md#ae0a737c353e28b85d99ed35bdfff8619">RderrCallback</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1380495948191905"><a name="p1380495948191905"></a><a name="p1380495948191905"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row1098806938191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p661550921191905"><a name="p661550921191905"></a><a name="p661550921191905"></a><a href="WifiIotSdioIntcallback.md#af58926c3ded02e3f80aa0b993d06e3b9">WrstartCallback</a> )(unsigned int len, unsigned char *admaTable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688357698191905"><a name="p1688357698191905"></a><a name="p1688357698191905"></a>int(*&nbsp;</p>
</td>
</tr>
<tr id="row2134155235191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p99368724191905"><a name="p99368724191905"></a><a name="p99368724191905"></a><a href="WifiIotSdioIntcallback.md#a2cca616f1cb07e606d250dc995f4f6a9">WroverCallback</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p544566900191905"><a name="p544566900191905"></a><a name="p544566900191905"></a>int(*&nbsp;</p>
</td>
</tr>
<tr id="row1961554200191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p861846226191905"><a name="p861846226191905"></a><a name="p861846226191905"></a><a href="WifiIotSdioIntcallback.md#a117b68e1bf52bb3d3df73cea45292ac9">ProcessmsgCallback</a> )(unsigned int msg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059648816191905"><a name="p1059648816191905"></a><a name="p1059648816191905"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row1081933303191905"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p459889357191905"><a name="p459889357191905"></a><a name="p459889357191905"></a><a href="WifiIotSdioIntcallback.md#aeb173521602d5cb1dc1c4e06f6cdb6a4">SoftRstCallback</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2099023843191905"><a name="p2099023843191905"></a><a name="p2099023843191905"></a>void(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section343659856191905"></a>

## **Field Documentation**<a name="section1105987385191905"></a>

## ProcessmsgCallback<a name="a117b68e1bf52bb3d3df73cea45292ac9"></a>

```
void(* WifiIotSdioIntcallback::ProcessmsgCallback) (unsigned int msg)
```

 **Description:**

Callback invoked when a message is received from the host 

## RderrCallback<a name="ae0a737c353e28b85d99ed35bdfff8619"></a>

```
void(* WifiIotSdioIntcallback::RderrCallback) (void)
```

 **Description:**

Callback invoked when a data read failure occurs on the host 

## RdoverCallback<a name="a49f5c77ee508f9c6cab65b9c8a84bf3e"></a>

```
int(* WifiIotSdioIntcallback::RdoverCallback) (void)
```

 **Description:**

Callback invoked when the host finishes a read operation 

## RdstartCallback<a name="acc9dad5477a57e9a99c396f17c3a2972"></a>

```
int(* WifiIotSdioIntcallback::RdstartCallback) (unsigned int len, unsigned char *admaTable)
```

 **Description:**

Callback invoked when the host starts a read operation 

## SoftRstCallback<a name="aeb173521602d5cb1dc1c4e06f6cdb6a4"></a>

```
void(* WifiIotSdioIntcallback::SoftRstCallback) (void)
```

 **Description:**

Callback invoked when a soft reset interrupt message is received from the host 

## WroverCallback<a name="a2cca616f1cb07e606d250dc995f4f6a9"></a>

```
int(* WifiIotSdioIntcallback::WroverCallback) (void)
```

 **Description:**

Callback invoked when the host finishes a write operation 

## WrstartCallback<a name="af58926c3ded02e3f80aa0b993d06e3b9"></a>

```
int(* WifiIotSdioIntcallback::WrstartCallback) (unsigned int len, unsigned char *admaTable)
```

 **Description:**

Callback invoked when the host starts a write operation 

