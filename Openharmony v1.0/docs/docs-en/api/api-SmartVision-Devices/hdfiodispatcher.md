# HdfIoDispatcher<a name="EN-US_TOPIC_0000001055078139"></a>

## **Overview**<a name="section154265925093530"></a>

**Related Modules:**

[Core](core.md)

**Description:**

Defines a driver service call dispatcher. 

**Since:**

1.0

## **Summary**<a name="section84469407093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table855787415093530"></a>
<table><thead align="left"><tr id="row544230642093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1850233226093530"><a name="p1850233226093530"></a><a name="p1850233226093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1192978743093530"><a name="p1192978743093530"></a><a name="p1192978743093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1738720333093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p223041841093530"><a name="p223041841093530"></a><a name="p223041841093530"></a><a href="hdfiodispatcher.md#ab87eb61c3bea95bc41c9e8dcc6e2f865">Dispatch</a> )(struct <a href="hdfobject.md">HdfObject</a> *service, int cmdId, struct <a href="hdfsbuf.md">HdfSBuf</a> *data, struct <a href="hdfsbuf.md">HdfSBuf</a> *reply)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827517979093530"><a name="p1827517979093530"></a><a name="p1827517979093530"></a>int(* </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section741057410093530"></a>

## **Field Documentation**<a name="section949528996093530"></a>

## Dispatch<a name="ab87eb61c3bea95bc41c9e8dcc6e2f865"></a>

```
int(* HdfIoDispatcher::Dispatch) (struct [HdfObject](hdfobject.md) *service, int cmdId, struct [HdfSBuf](hdfsbuf.md) *data, struct [HdfSBuf](hdfsbuf.md) *reply)
```

 **Description:**

Dispatches a driver service call.  **service**  indicates the pointer to the driver service object,  **id**  indicates the command word of the function,  **data**  indicates the pointer to the data you want to pass to the driver, and  **reply**  indicates the pointer to the data returned by the driver. 

