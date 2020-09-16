# semaphore.h<a name="EN-US_TOPIC_0000001054748011"></a>

## **Overview**<a name="section766043969084832"></a>

**Related Modules:**

[IPC](ipc.md)

**Description:**

Provides functions and structures related to semaphore operations. 

For example, you can use the functions to create, open, close, and delete semaphores, and perform P and V operations on semaphores.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1409724101084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table96434775084832"></a>
<table><thead align="left"><tr id="row614773592084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1577395823084832"><a name="p1577395823084832"></a><a name="p1577395823084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2008474737084832"><a name="p2008474737084832"></a><a name="p2008474737084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2065719279084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p120286844084832"><a name="p120286844084832"></a><a name="p120286844084832"></a><a href="sem_t.md">sem_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362358577084832"><a name="p1362358577084832"></a><a name="p1362358577084832"></a>Defines semaphores. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table895814011084832"></a>
<table><thead align="left"><tr id="row1528959567084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p529667124084832"><a name="p529667124084832"></a><a name="p529667124084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1589974448084832"><a name="p1589974448084832"></a><a name="p1589974448084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1147250591084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p802437960084832"><a name="p802437960084832"></a><a name="p802437960084832"></a><a href="ipc.md#ga2ef55dcb46a51cb0f879f4c1724bdded">SEM_FAILED</a>   ((<a href="sem_t.md">sem_t</a> *)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1726826754084832"><a name="p1726826754084832"></a><a name="p1726826754084832"></a>Defines the semaphore failure flag. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1705430334084832"></a>
<table><thead align="left"><tr id="row1843819363084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p553566938084832"><a name="p553566938084832"></a><a name="p553566938084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p302440967084832"><a name="p302440967084832"></a><a name="p302440967084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row34250696084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p600955230084832"><a name="p600955230084832"></a><a name="p600955230084832"></a><a href="ipc.md#ga4e398fea1080fd7919e5c72ee94e2fc5">sem_close</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086172710084832"><a name="p1086172710084832"></a><a name="p1086172710084832"></a>int </p>
<p id="p2124398928084832"><a name="p2124398928084832"></a><a name="p2124398928084832"></a>Closes a specified semaphore. </p>
</td>
</tr>
<tr id="row1721913525084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p73611111084832"><a name="p73611111084832"></a><a name="p73611111084832"></a><a href="ipc.md#ga6bc9a7dd941a9b5e319715b767af5682">sem_destroy</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412260818084832"><a name="p1412260818084832"></a><a name="p1412260818084832"></a>int </p>
<p id="p1541530776084832"><a name="p1541530776084832"></a><a name="p1541530776084832"></a>Destroys a specified anonymous semaphore that is no longer used. </p>
</td>
</tr>
<tr id="row507843931084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p786010547084832"><a name="p786010547084832"></a><a name="p786010547084832"></a><a href="ipc.md#ga934bcc3cbc0c67a9e3a8e7a43c023460">sem_getvalue</a> (<a href="sem_t.md">sem_t</a> *__restrict sem, int *__restrict sval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p52909936084832"><a name="p52909936084832"></a><a name="p52909936084832"></a>int </p>
<p id="p1459495852084832"><a name="p1459495852084832"></a><a name="p1459495852084832"></a>Obtains the count value of a specified semaphore. </p>
</td>
</tr>
<tr id="row141324220084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1943662547084832"><a name="p1943662547084832"></a><a name="p1943662547084832"></a><a href="ipc.md#ga532509bd8a6499f8193253192fb83a3d">sem_init</a> (<a href="sem_t.md">sem_t</a> *sem, int pshared, unsigned int value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057721368084832"><a name="p1057721368084832"></a><a name="p1057721368084832"></a>int </p>
<p id="p600581776084832"><a name="p600581776084832"></a><a name="p600581776084832"></a>Creates and initializes an anonymous semaphore. </p>
</td>
</tr>
<tr id="row1725060317084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1810879975084832"><a name="p1810879975084832"></a><a name="p1810879975084832"></a><a href="ipc.md#ga015dce85cab8477c679cc47968958247">sem_post</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323877717084832"><a name="p323877717084832"></a><a name="p323877717084832"></a>int </p>
<p id="p1569105389084832"><a name="p1569105389084832"></a><a name="p1569105389084832"></a>Increments the semaphore count by 1. </p>
</td>
</tr>
<tr id="row1926502844084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p582441033084832"><a name="p582441033084832"></a><a name="p582441033084832"></a><a href="ipc.md#ga9d832817226c594e7628e2cc7ed7d723">sem_timedwait</a> (<a href="sem_t.md">sem_t</a> *__restrict sem, const struct <a href="timespec.md">timespec</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p346302062084832"><a name="p346302062084832"></a><a name="p346302062084832"></a>int </p>
<p id="p277064343084832"><a name="p277064343084832"></a><a name="p277064343084832"></a>Obtains the semaphore, with a timeout period specified. </p>
</td>
</tr>
<tr id="row1916757127084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896477375084832"><a name="p1896477375084832"></a><a name="p1896477375084832"></a><a href="ipc.md#ga4de7a9a334b01b6373b017aaefa07cf0">sem_trywait</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946973163084832"><a name="p946973163084832"></a><a name="p946973163084832"></a>int </p>
<p id="p1364408593084832"><a name="p1364408593084832"></a><a name="p1364408593084832"></a>Attempts to obtain the semaphore. </p>
</td>
</tr>
<tr id="row1947143977084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735857883084832"><a name="p735857883084832"></a><a name="p735857883084832"></a><a href="ipc.md#ga776256d1a473906f8b7490689bfcb75c">sem_unlink</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p664238821084832"><a name="p664238821084832"></a><a name="p664238821084832"></a>int </p>
<p id="p68854864084832"><a name="p68854864084832"></a><a name="p68854864084832"></a>Deletes a specified semaphore. </p>
</td>
</tr>
<tr id="row8714911084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p349093401084832"><a name="p349093401084832"></a><a name="p349093401084832"></a><a href="ipc.md#gaad70020dca2241a2b78e272ca033271b">sem_wait</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2006423985084832"><a name="p2006423985084832"></a><a name="p2006423985084832"></a>int </p>
<p id="p1932240049084832"><a name="p1932240049084832"></a><a name="p1932240049084832"></a>Obtains the semaphore. </p>
</td>
</tr>
</tbody>
</table>

