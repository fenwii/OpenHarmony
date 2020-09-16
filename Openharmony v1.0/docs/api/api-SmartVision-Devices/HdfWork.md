# HdfWork<a name="ZH-CN_TOPIC_0000001055518088"></a>

## **Overview**<a name="section745676953093530"></a>

**Related Modules:**

[DriverUtils](DriverUtils.md)

**Description:**

Describes a work item and a delayed work item. This structure defines the work and delayed work items, and then calls the initialization function  [HdfWorkInit](DriverUtils.md#gad171adc8eda320fd01049a2b87ea62fb)  or  [HdfDelayedWorkInit](DriverUtils.md#ga55bf669dc6740c65e4d45a4f641db2f1)  to perform initialization. The  **[HdfAddWork\(\)](DriverUtils.md#ga82cc68d656aa17317634b07d49dae160)**  function is to add a work item to a work queue immediately, and the  **[HdfAddDelayedWork\(\)](DriverUtils.md#gaef781ccc1579db3070745088da47b2c5)**  function is to add a work item to a work queue after the configured delayed time. 

## **Summary**<a name="section1135713559093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1692733874093530"></a>
<table><thead align="left"><tr id="row540227682093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p601732280093530"><a name="p601732280093530"></a><a name="p601732280093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2113177913093530"><a name="p2113177913093530"></a><a name="p2113177913093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1156814672093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p983577245093530"><a name="p983577245093530"></a><a name="p983577245093530"></a><a href="HdfWork.md#a8830d89e775646b48db0beae2af4b561">realWork</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p834767806093530"><a name="p834767806093530"></a><a name="p834767806093530"></a>void *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1661245844093530"></a>

## **Field Documentation**<a name="section1350972881093530"></a>

## realWork<a name="a8830d89e775646b48db0beae2af4b561"></a>

```
void* HdfWork::realWork
```

 **Description:**

Pointer to a work item and a delayed work item 

