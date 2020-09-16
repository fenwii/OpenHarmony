# StationInfo<a name="EN-US_TOPIC_0000001054595103"></a>

## **Overview**<a name="section1712307282191902"></a>

**Related Modules:**

[Wifiservice](wifiservice.md)

**Description:**

Represents the station information. 

The station information is returned when  **OnHotspotStaJoin**  or  **OnHotspotStaLeave**  is called. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1595651537191902"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table23505855191902"></a>
<table><thead align="left"><tr id="row361059977191902"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p899118172191902"><a name="p899118172191902"></a><a name="p899118172191902"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p175351191191902"><a name="p175351191191902"></a><a name="p175351191191902"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1254853063191902"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430421032191902"><a name="p430421032191902"></a><a name="p430421032191902"></a><a href="stationinfo.md#aa6bd1670a7473f7a9b53aea6de2cd796">macAddress</a> [<a href="wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815">WIFI_MAC_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935378264191902"><a name="p1935378264191902"></a><a name="p1935378264191902"></a>unsigned char </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section387432517191902"></a>

## **Field Documentation**<a name="section1425540241191902"></a>

## macAddress<a name="aa6bd1670a7473f7a9b53aea6de2cd796"></a>

```
unsigned char StationInfo::macAddress[[WIFI_MAC_LEN](wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815)]
```

 **Description:**

MAC address. For its length, see  [WIFI\_MAC\_LEN](wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815). 

