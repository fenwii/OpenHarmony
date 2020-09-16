# HdfIoService<a name="ZH-CN_TOPIC_0000001054598161"></a>

## **Overview**<a name="section1231012473093530"></a>

**Related Modules:**

[Core](Core.md)

**Description:**

Defines a driver service object. 

**Since:**

1.0

## **Summary**<a name="section2006077718093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table742148269093530"></a>
<table><thead align="left"><tr id="row424487222093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1639564560093530"><a name="p1639564560093530"></a><a name="p1639564560093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1365378017093530"><a name="p1365378017093530"></a><a name="p1365378017093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row710479616093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1942838344093530"><a name="p1942838344093530"></a><a name="p1942838344093530"></a><a href="HdfIoService.md#a6ad278c554dab0fa5b2269e3cae22cab">object</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935341494093530"><a name="p1935341494093530"></a><a name="p1935341494093530"></a>struct <a href="HdfObject.md">HdfObject</a>&nbsp;</p>
</td>
</tr>
<tr id="row61539404093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1735301085093530"><a name="p1735301085093530"></a><a name="p1735301085093530"></a><a href="HdfIoService.md#a4b30a5c89ee7213eb1f74898e2ad605c">target</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1418353520093530"><a name="p1418353520093530"></a><a name="p1418353520093530"></a>struct <a href="HdfObject.md">HdfObject</a> *&nbsp;</p>
</td>
</tr>
<tr id="row736175776093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p590716118093530"><a name="p590716118093530"></a><a name="p590716118093530"></a><a href="HdfIoService.md#a3da28f5ff9b7805e136081bb65952761">dispatcher</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456352926093530"><a name="p1456352926093530"></a><a name="p1456352926093530"></a>struct <a href="HdfIoDispatcher.md">HdfIoDispatcher</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1218803229093530"></a>

## **Field Documentation**<a name="section632658158093530"></a>

## dispatcher<a name="a3da28f5ff9b7805e136081bb65952761"></a>

```
struct [HdfIoDispatcher](HdfIoDispatcher.md)* HdfIoService::dispatcher
```

 **Description:**

[Service](Service.md)  call dispatcher 

## object<a name="a6ad278c554dab0fa5b2269e3cae22cab"></a>

```
struct [HdfObject](HdfObject.md) HdfIoService::object
```

 **Description:**

Base class object 

## target<a name="a4b30a5c89ee7213eb1f74898e2ad605c"></a>

```
struct [HdfObject](HdfObject.md)* HdfIoService::target
```

 **Description:**

Pointer to the bound service entity, which is used for framework management. You can ignore it. 

