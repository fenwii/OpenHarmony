# osal\_mutex.h<a name="EN-US_TOPIC_0000001055039492"></a>

## **Overview**<a name="section1675701804093526"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Declares mutex types and interfaces. 

This file provides interfaces for initializing and destroying a mutex, locking a mutex, locking a mutex upon timeout, and unlocking a mutex. The mutex must be destroyed after being used.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1154907409093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table253295313093526"></a>
<table><thead align="left"><tr id="row1327382104093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1120770094093526"><a name="p1120770094093526"></a><a name="p1120770094093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1047298068093526"><a name="p1047298068093526"></a><a name="p1047298068093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1046987574093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p124045760093526"><a name="p124045760093526"></a><a name="p124045760093526"></a><a href="osalmutex.md">OsalMutex</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p802204458093526"><a name="p802204458093526"></a><a name="p802204458093526"></a>Describes a mutex. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1088375841093526"></a>
<table><thead align="left"><tr id="row1965308587093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1218003377093526"><a name="p1218003377093526"></a><a name="p1218003377093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1882091861093526"><a name="p1882091861093526"></a><a name="p1882091861093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row171375580093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973819246093526"><a name="p973819246093526"></a><a name="p973819246093526"></a><a href="osal.md#ga63b1e9f0b9eacddc211f9a481c2597b3">OSAL_DECLARE_MUTEX</a>(mutex)   struct <a href="osalmutex.md">OsalMutex</a> mutex</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284707408093526"><a name="p284707408093526"></a><a name="p284707408093526"></a>Defines a mutex. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table646751663093526"></a>
<table><thead align="left"><tr id="row924545571093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p128272633093526"><a name="p128272633093526"></a><a name="p128272633093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1010816043093526"><a name="p1010816043093526"></a><a name="p1010816043093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1256918081093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484303201093526"><a name="p484303201093526"></a><a name="p484303201093526"></a><a href="osal.md#ga9bbc55785f8a533b0b099956bcbe258e">OsalMutexInit</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59244094093526"><a name="p59244094093526"></a><a name="p59244094093526"></a>int32_t </p>
<p id="p21208119093526"><a name="p21208119093526"></a><a name="p21208119093526"></a>Initializes a mutex. </p>
</td>
</tr>
<tr id="row500771136093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424157742093526"><a name="p424157742093526"></a><a name="p424157742093526"></a><a href="osal.md#gaa37328265ee97277516f6905f90a41b3">OsalMutexDestroy</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779952008093526"><a name="p779952008093526"></a><a name="p779952008093526"></a>int32_t </p>
<p id="p1551839741093526"><a name="p1551839741093526"></a><a name="p1551839741093526"></a>Destroys a mutex. </p>
</td>
</tr>
<tr id="row1271061671093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p994630793093526"><a name="p994630793093526"></a><a name="p994630793093526"></a><a href="osal.md#ga45d893bf49a8fb8caf76fa5d31822e0e">OsalMutexLock</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807436000093526"><a name="p807436000093526"></a><a name="p807436000093526"></a>int32_t </p>
<p id="p72872658093526"><a name="p72872658093526"></a><a name="p72872658093526"></a>Locks a mutex. </p>
</td>
</tr>
<tr id="row1212491446093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1331193672093526"><a name="p1331193672093526"></a><a name="p1331193672093526"></a><a href="osal.md#ga57162c8f2e812ef3e5ace498bb85a3b6">OsalMutexTimedLock</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex, uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p655778290093526"><a name="p655778290093526"></a><a name="p655778290093526"></a>int32_t </p>
<p id="p1792962840093526"><a name="p1792962840093526"></a><a name="p1792962840093526"></a>Locks a mutex with a specified timeout duration. </p>
</td>
</tr>
<tr id="row1078205557093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1989495231093526"><a name="p1989495231093526"></a><a name="p1989495231093526"></a><a href="osal.md#gae76ffb4db66c988be5209e0dfdc7a35f">OsalMutexUnlock</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1290042472093526"><a name="p1290042472093526"></a><a name="p1290042472093526"></a>int32_t </p>
<p id="p709216398093526"><a name="p709216398093526"></a><a name="p709216398093526"></a>Unlocks a mutex. </p>
</td>
</tr>
</tbody>
</table>

