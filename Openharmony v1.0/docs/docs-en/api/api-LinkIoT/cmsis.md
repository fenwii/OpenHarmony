# CMSIS<a name="EN-US_TOPIC_0000001055308173"></a>

## **Overview**<a name="section1420242807090250"></a>

Provides standard, universal real-time operating system \(RTOS\) APIs. 

These APIs comply with ARM CMSIS and are used for thread management, timer management, inter-process communications, and semaphores.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1256921422090250"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1858235711090250"></a>
<table><thead align="left"><tr id="row781992054090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p973472812090250"><a name="p973472812090250"></a><a name="p973472812090250"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p719806344090250"><a name="p719806344090250"></a><a name="p719806344090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1997716395090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p401588824090250"><a name="p401588824090250"></a><a name="p401588824090250"></a><a href="osversion_t.md">osVersion_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1676133979090250"><a name="p1676133979090250"></a><a name="p1676133979090250"></a>Describes the system version. </p>
</td>
</tr>
<tr id="row1751205074090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642509932090250"><a name="p642509932090250"></a><a name="p642509932090250"></a><a href="osthreadattr_t.md">osThreadAttr_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334791415090250"><a name="p334791415090250"></a><a name="p334791415090250"></a>Describes thread attributes. </p>
</td>
</tr>
<tr id="row1567462820090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p696617070090250"><a name="p696617070090250"></a><a name="p696617070090250"></a><a href="ostimerattr_t.md">osTimerAttr_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510900023090250"><a name="p510900023090250"></a><a name="p510900023090250"></a>Describes timer attributes. </p>
</td>
</tr>
<tr id="row607038205090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p941533263090250"><a name="p941533263090250"></a><a name="p941533263090250"></a><a href="oseventflagsattr_t.md">osEventFlagsAttr_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670969238090250"><a name="p1670969238090250"></a><a name="p1670969238090250"></a>Describes event attributes. </p>
</td>
</tr>
<tr id="row1929517078090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p848868866090250"><a name="p848868866090250"></a><a name="p848868866090250"></a><a href="osmutexattr_t.md">osMutexAttr_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1366859739090250"><a name="p1366859739090250"></a><a name="p1366859739090250"></a>Describes mutex attributes. </p>
</td>
</tr>
<tr id="row963740317090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p854984613090250"><a name="p854984613090250"></a><a name="p854984613090250"></a><a href="ossemaphoreattr_t.md">osSemaphoreAttr_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p254741407090250"><a name="p254741407090250"></a><a name="p254741407090250"></a>Describes semaphore attributes. </p>
</td>
</tr>
<tr id="row973367029090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007618755090250"><a name="p2007618755090250"></a><a name="p2007618755090250"></a><a href="osmessagequeueattr_t.md">osMessageQueueAttr_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087009930090250"><a name="p2087009930090250"></a><a name="p2087009930090250"></a>Describes message queue attributes. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table368998880090250"></a>
<table><thead align="left"><tr id="row1327278265090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1016154769090250"><a name="p1016154769090250"></a><a name="p1016154769090250"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p373811542090250"><a name="p373811542090250"></a><a name="p373811542090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row326286177090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1032043523090250"><a name="p1032043523090250"></a><a name="p1032043523090250"></a><a href="cmsis.md#ga9eb9a7a797a42e4b55eb171ecc609ddb">osWaitForever</a>   0xFFFFFFFFU</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1002414506090250"><a name="p1002414506090250"></a><a name="p1002414506090250"></a>Indicates that the RTOS waits forever unless an event flag is received. </p>
</td>
</tr>
<tr id="row738934013090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617952244090250"><a name="p617952244090250"></a><a name="p617952244090250"></a><a href="cmsis.md#gaf235b13764754739d13c3cb709dc24e6">osNoWait</a>   0x0U</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201543601090250"><a name="p1201543601090250"></a><a name="p1201543601090250"></a>Indicates that the RTOS does not wait. </p>
</td>
</tr>
<tr id="row1436688056090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340668819090250"><a name="p1340668819090250"></a><a name="p1340668819090250"></a><a href="cmsis.md#ga18e63587b8450d5b8798b6f6ec04e012">osFlagsWaitAny</a>   0x00000000U</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p583916184090250"><a name="p583916184090250"></a><a name="p583916184090250"></a>Indicates that the RTOS waits until any event flag is triggered. </p>
</td>
</tr>
<tr id="row1057269224090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1793640858090250"><a name="p1793640858090250"></a><a name="p1793640858090250"></a><a href="cmsis.md#ga8b6f562736fbfb5428940e0c017dec24">osFlagsWaitAll</a>   0x00000001U</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2120290534090250"><a name="p2120290534090250"></a><a name="p2120290534090250"></a>Indicates that the system waits until all event flags are triggered. </p>
</td>
</tr>
<tr id="row695201262090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1578109265090250"><a name="p1578109265090250"></a><a name="p1578109265090250"></a><a href="cmsis.md#gaade844a42237d8c37569d4d9b16b9f1c">osFlagsNoClear</a>   0x00000002U</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p301438742090250"><a name="p301438742090250"></a><a name="p301438742090250"></a>Indicates that defined flags are not cleared. </p>
</td>
</tr>
<tr id="row1848376013090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p692651459090250"><a name="p692651459090250"></a><a name="p692651459090250"></a><a href="cmsis.md#ga01c1359c3a5640bff6e08f09bf94ce3a">osFlagsError</a>   0x80000000U</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791861353090250"><a name="p791861353090250"></a><a name="p791861353090250"></a>Indicates a flag error. </p>
</td>
</tr>
<tr id="row202098489090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793847464090250"><a name="p793847464090250"></a><a name="p793847464090250"></a><a href="cmsis.md#ga3b1d9fbb83d64eedb62f831c9be647c3">osFlagsErrorUnknown</a>   0xFFFFFFFFU</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924136202090250"><a name="p924136202090250"></a><a name="p924136202090250"></a>Indicates an unknown error. </p>
</td>
</tr>
<tr id="row607607107090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527605006090250"><a name="p1527605006090250"></a><a name="p1527605006090250"></a><a href="cmsis.md#ga2e951c3f1c3b7bff4eca3d7836cd19ca">osFlagsErrorTimeout</a>   0xFFFFFFFEU</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1677980810090250"><a name="p1677980810090250"></a><a name="p1677980810090250"></a>Indicates a timeout. </p>
</td>
</tr>
<tr id="row1492484889090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p16216049090250"><a name="p16216049090250"></a><a name="p16216049090250"></a><a href="cmsis.md#ga4db38b50da1889bcaaa7f747e844f904">osFlagsErrorResource</a>   0xFFFFFFFDU</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305227024090250"><a name="p1305227024090250"></a><a name="p1305227024090250"></a>Indicates a resource error. </p>
</td>
</tr>
<tr id="row1564666301090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236803960090250"><a name="p236803960090250"></a><a name="p236803960090250"></a><a href="cmsis.md#gaa8a95ef938f8f5a9fcb815ec53184f77">osFlagsErrorParameter</a>   0xFFFFFFFCU</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989588810090250"><a name="p1989588810090250"></a><a name="p1989588810090250"></a>Indicates an incorrect parameter. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1133673949090250"></a>
<table><thead align="left"><tr id="row2011302125090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p181907308090250"><a name="p181907308090250"></a><a name="p181907308090250"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1578884326090250"><a name="p1578884326090250"></a><a name="p1578884326090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row415762328090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1962715039090250"><a name="p1962715039090250"></a><a name="p1962715039090250"></a><a href="cmsis.md#ga8ef2773ed8ef63ab8727e0d06ebec4d2">osThreadFunc_t</a>) (void *argument)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2136897648090250"><a name="p2136897648090250"></a><a name="p2136897648090250"></a>typedef void(* </p>
<p id="p30139061090250"><a name="p30139061090250"></a><a name="p30139061090250"></a>Callback for thread scheduling. </p>
</td>
</tr>
<tr id="row606666308090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2064587475090250"><a name="p2064587475090250"></a><a name="p2064587475090250"></a><a href="cmsis.md#ga77a298218f3c8382b39a09a6d134d040">osTimerFunc_t</a>) (void *argument)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499073884090250"><a name="p499073884090250"></a><a name="p499073884090250"></a>typedef void(* </p>
<p id="p1371943676090250"><a name="p1371943676090250"></a><a name="p1371943676090250"></a>Callback for timer triggering. </p>
</td>
</tr>
<tr id="row1004207213090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p846190338090250"><a name="p846190338090250"></a><a name="p846190338090250"></a><a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p698863527090250"><a name="p698863527090250"></a><a name="p698863527090250"></a>typedef void * </p>
<p id="p1760910823090250"><a name="p1760910823090250"></a><a name="p1760910823090250"></a>Identifies a thread. </p>
</td>
</tr>
<tr id="row2082027885090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1759797456090250"><a name="p1759797456090250"></a><a name="p1759797456090250"></a><a href="cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44">osTimerId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400097459090250"><a name="p400097459090250"></a><a name="p400097459090250"></a>typedef void * </p>
<p id="p512565151090250"><a name="p512565151090250"></a><a name="p512565151090250"></a>Identifies a timer. </p>
</td>
</tr>
<tr id="row501914068090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1948348165090250"><a name="p1948348165090250"></a><a name="p1948348165090250"></a><a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071475319090250"><a name="p2071475319090250"></a><a name="p2071475319090250"></a>typedef void * </p>
<p id="p1512266494090250"><a name="p1512266494090250"></a><a name="p1512266494090250"></a>Identifies an event flag. </p>
</td>
</tr>
<tr id="row364692190090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895773132090250"><a name="p895773132090250"></a><a name="p895773132090250"></a><a href="cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7">osMutexId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1744101310090250"><a name="p1744101310090250"></a><a name="p1744101310090250"></a>typedef void * </p>
<p id="p1487121306090250"><a name="p1487121306090250"></a><a name="p1487121306090250"></a>Identifies a mutex. </p>
</td>
</tr>
<tr id="row789001190090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1819053450090250"><a name="p1819053450090250"></a><a name="p1819053450090250"></a><a href="cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1">osSemaphoreId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2103150797090250"><a name="p2103150797090250"></a><a name="p2103150797090250"></a>typedef void * </p>
<p id="p529723401090250"><a name="p529723401090250"></a><a name="p529723401090250"></a>Identifies a semaphore object. </p>
</td>
</tr>
<tr id="row1363886371090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1508583087090250"><a name="p1508583087090250"></a><a name="p1508583087090250"></a><a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120611494090250"><a name="p1120611494090250"></a><a name="p1120611494090250"></a>typedef void * </p>
<p id="p17735742090250"><a name="p17735742090250"></a><a name="p17735742090250"></a>Identifies a message queue. </p>
</td>
</tr>
<tr id="row1977726710090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1515493286090250"><a name="p1515493286090250"></a><a name="p1515493286090250"></a><a href="cmsis.md#gad5ef21485fe5f60263bc0b48006202cb">TZ_ModuleId_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1110235400090250"><a name="p1110235400090250"></a><a name="p1110235400090250"></a>typedef uint32_t </p>
<p id="p1209742999090250"><a name="p1209742999090250"></a><a name="p1209742999090250"></a>Identifies a TrustZone module call process. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1229582743090250"></a>
<table><thead align="left"><tr id="row1279749660090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1613215157090250"><a name="p1613215157090250"></a><a name="p1613215157090250"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1164299655090250"><a name="p1164299655090250"></a><a name="p1164299655090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1790098433090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p201073110090250"><a name="p201073110090250"></a><a name="p201073110090250"></a><a href="cmsis.md#ga08326469274b668140ca934b168a5ad4">osKernelState_t</a> {   <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4ae9a7d578873c28590009479283922db9">osKernelInactive</a> = 0, <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4a87ef9718301b92bfa9c97d61d660a8aa">osKernelReady</a> = 1, <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4a98d8ad539d2cc6c3dbb7138356049db2">osKernelRunning</a> = 2, <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4a033026d41a9309bd9551df1ae8153553">osKernelLocked</a> = 3,   <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4a3240807627595e80f59a46434639b765">osKernelSuspended</a> = 4, <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4a1b942a8c76daeba2925a763d4d7567a2">osKernelError</a> = -1, <a href="cmsis.md#gga08326469274b668140ca934b168a5ad4a9cc4cc562a20a28c0f6f4b878ecf2df5">osKernelReserved</a> = 0x7FFFFFFFU }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p542198670090250"><a name="p542198670090250"></a><a name="p542198670090250"></a>Enumerates kernel states. </p>
</td>
</tr>
<tr id="row2018673431090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p417756364090250"><a name="p417756364090250"></a><a name="p417756364090250"></a><a href="cmsis.md#gad3dc89e942e38d9f3af858a0269a820d">osThreadState_t</a> {   <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820da7d7d4f719a1be6daa63a251563585fdd">osThreadInactive</a> = 0, <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820dad9a040e03d7e7943c0217a3359fc1e8b">osThreadReady</a> = 1, <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820da71dae1f35a4b4d9d2ab24e186461a17f">osThreadRunning</a> = 2, <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820da476cd2370e6938974fb2a79811408819">osThreadBlocked</a> = 3,   <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820dac2a35280d5475f56352c539c9c9b42f9">osThreadTerminated</a> = 4, <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820dac841e73a7198a42364c9450f1f54a0ef">osThreadError</a> = -1, <a href="cmsis.md#ggad3dc89e942e38d9f3af858a0269a820da8872f7e352370eb11ee772c7dcca6e6c">osThreadReserved</a> = 0x7FFFFFFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1398145183090250"><a name="p1398145183090250"></a><a name="p1398145183090250"></a>Enumerates thread states. </p>
</td>
</tr>
<tr id="row438005401090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385525573090250"><a name="p385525573090250"></a><a name="p385525573090250"></a><a href="cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec">osPriority_t</a> {   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca6c437c7185161a3bd1e7e4669dfa17a3">osPriorityNone</a> = 0, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca549e79a43ff4f8b2b31afb613f5caa81">osPriorityIdle</a> = 1, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca61cb822239ac8f66dfbdc7291598a3d4">osPriorityLow</a> = 8, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecaba2b6919f0b630c8c1b2c940e3bfadbe">osPriorityLow1</a> = 8+1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca78ad5d00aa07a2b4bf30a639544f5507">osPriorityLow2</a> = 8+2, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca28ccb07942c16f5f5efefb6cf68a7f50">osPriorityLow3</a> = 8+3, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca5a4a4f26d5b220a968e221e854f69a81">osPriorityLow4</a> = 8+4, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecad69b8c14809bc5bdce4887f5a57d9353">osPriorityLow5</a> = 8+5,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecac0f188468664d06d4cd9e6e1ed351393">osPriorityLow6</a> = 8+6, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca5b151ebba7fdeb1baaa9b7b420890b7a">osPriorityLow7</a> = 8+7, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca193b650117c209b4a203954542bcc3e6">osPriorityBelowNormal</a> = 16, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca9138da7187690b15f52d8e5729c18da5">osPriorityBelowNormal1</a> = 16+1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca4f081d6735bf2f513338b07eddf13ae3">osPriorityBelowNormal2</a> = 16+2, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca19c013690d0d6bf3ac90707942be3fdf">osPriorityBelowNormal3</a> = 16+3, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca36931ad6cee5e4700e2c8622bdd2cd24">osPriorityBelowNormal4</a> = 16+4, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca0bcd9ad1e7a02e3bf03be7dcc8ece38e">osPriorityBelowNormal5</a> = 16+5,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecabd3cc7df5b92b752ddf1e7843a786c05">osPriorityBelowNormal6</a> = 16+6, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecab18e3bda7b5e418e309a62d6267ea14b">osPriorityBelowNormal7</a> = 16+7, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca45a2895ad30c79fb97de18cac7cc19f1">osPriorityNormal</a> = 24, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca3e70c19e03d5a54e66bd071f0776782c">osPriorityNormal1</a> = 24+1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca19e96f2b025b6462a43b1965043c8205">osPriorityNormal2</a> = 24+2, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca402bd7ab26fb57c8cee8cf94168f4c91">osPriorityNormal3</a> = 24+3, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca93ef07d3a107aeee6508bfd29ba3485d">osPriorityNormal4</a> = 24+4, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca68f3f6fdaa639de300277802aa13a0ab">osPriorityNormal5</a> = 24+5,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca8221eb0d059726a6309f1f2d0cdb6204">osPriorityNormal6</a> = 24+6, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca049abd04f8951415407ec9d92bd9b80b">osPriorityNormal7</a> = 24+7, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca17b36cd9cd38652c2bc6d4803990674b">osPriorityAboveNormal</a> = 32, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecabfeafc713edfc7b9130aa5c762d68998">osPriorityAboveNormal1</a> = 32+1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca901acf86070e06f5990b611734ee2562">osPriorityAboveNormal2</a> = 32+2, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecad566b876b64e6efdc3eba0fc04e54013">osPriorityAboveNormal3</a> = 32+3, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca6ccac37d7dae4586a2031966d36a63ec">osPriorityAboveNormal4</a> = 32+4, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecae36e8b38ee046a3104bcccabb10cf78c">osPriorityAboveNormal5</a> = 32+5,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca61e6ce27e1e0f34f2540b413b8a8b207">osPriorityAboveNormal6</a> = 32+6, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecadbbb0fed3ada6b9b50d4a628abc2a67d">osPriorityAboveNormal7</a> = 32+7, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca914433934143a9ba767e59577c56e6c2">osPriorityHigh</a> = 40, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca17b7a7e6febf12444a84e90edfce36cb">osPriorityHigh1</a> = 40+1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca40a120cf8bbc42e575455c027f3d9b03">osPriorityHigh2</a> = 40+2, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca0b15518b0b5321a29efa0b42b2f8c759">osPriorityHigh3</a> = 40+3, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecafe5a4f393fab04551ac7d93e80cdf0fb">osPriorityHigh4</a> = 40+4, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca5960841bfbdd959b163429e8502ea4e9">osPriorityHigh5</a> = 40+5,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca5714dda6effc1a3f8ec155d97e3e69bc">osPriorityHigh6</a> = 40+6, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca63ad0cc52a701ef3d9df52b59b995652">osPriorityHigh7</a> = 40+7, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca1485dec3702434a1ec3cb74c7a17a4af">osPriorityRealtime</a> = 48, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecaf685a06b30f0635476e21347a986305b">osPriorityRealtime1</a> = 48+1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecab832bd9de84e5eec2ecad69d085dadff">osPriorityRealtime2</a> = 48+2, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca3f2261e5e733e92844ae8c630f2f9eaa">osPriorityRealtime3</a> = 48+3, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecaf614e3dc966d559cd9d9d2a0f78ebe70">osPriorityRealtime4</a> = 48+4, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecaff84f31ceff203c711fb9476443507df">osPriorityRealtime5</a> = 48+5,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca80ae9d0dd256312c0c8f44af48316194">osPriorityRealtime6</a> = 48+6, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecaa76da6825c4bd31c4958200bc289103b">osPriorityRealtime7</a> = 48+7, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342eca3943224956e1ea667c6a931c74137b79">osPriorityISR</a> = 56, <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecae35f5e2f9c64ad346822521b643bdea4">osPriorityError</a> = -1,   <a href="cmsis.md#ggad4e3e0971b41f2d17584a8c6837342ecac86c171f8d466cced0cb1b03bb03343b">osPriorityReserved</a> = 0x7FFFFFFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p919035106090250"><a name="p919035106090250"></a><a name="p919035106090250"></a>Enumerates thread priorities. </p>
</td>
</tr>
<tr id="row1904010106090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p849005940090250"><a name="p849005940090250"></a><a name="p849005940090250"></a><a href="cmsis.md#ga7dc24a4c2b90334427081c3da7a71915">osTimerType_t</a> { <a href="cmsis.md#gga7dc24a4c2b90334427081c3da7a71915ad21712f8df5f97069c82dc9eec37b951">osTimerOnce</a> = 0, <a href="cmsis.md#gga7dc24a4c2b90334427081c3da7a71915ab9c91f9699162edb09bb7c90c11c8788">osTimerPeriodic</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399702235090250"><a name="p1399702235090250"></a><a name="p1399702235090250"></a>Enumerates timer types. </p>
</td>
</tr>
<tr id="row1908003856090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1331313840090250"><a name="p1331313840090250"></a><a name="p1331313840090250"></a><a href="cmsis.md#ga6274cbe33c6db824bbc40dc6eaa8e578">os_timer_rouses_type</a> { <a href="cmsis.md#gga6274cbe33c6db824bbc40dc6eaa8e578a9bc896516fd34ea78d2c3106f421bc1e">osTimerRousesIgnore</a> = 0, <a href="cmsis.md#gga6274cbe33c6db824bbc40dc6eaa8e578ae45ed4bdfd52ff62958e347eab459edb">osTimerRousesAllow</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1922821728090250"><a name="p1922821728090250"></a><a name="p1922821728090250"></a>Enumerates timer permissions. </p>
</td>
</tr>
<tr id="row1446897077090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007538885090250"><a name="p2007538885090250"></a><a name="p2007538885090250"></a><a href="cmsis.md#ga3d617b70715d7fb2c7c6f06809ee3913">os_timer_align_type</a> { <a href="cmsis.md#gga3d617b70715d7fb2c7c6f06809ee3913a30e89a6569f3f32e6d4f2c77ceba3bd9">osTimerAlignIgnore</a> = 0, <a href="cmsis.md#gga3d617b70715d7fb2c7c6f06809ee3913a8fd513208cb4a465b439fb04d9223f43">osTimerAlignAllow</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1292951348090250"><a name="p1292951348090250"></a><a name="p1292951348090250"></a>Enumerates timer alignment modes. </p>
</td>
</tr>
<tr id="row1467648243090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1926209431090250"><a name="p1926209431090250"></a><a name="p1926209431090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> {   <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813ea9e1c9e2550bb4de8969a935acffc968f">osOK</a> = 0, <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813eabb7b2d2c4efa66df42f1c10635467b09">osError</a> = -1, <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813ea913eb5df15ad85f8557eb3a456b56879">osErrorTimeout</a> = -2, <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813ea8fc5801e8b0482bdf22ad63a77f0155d">osErrorResource</a> = -3,   <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813eac24adca6a5d072c9f01c32178ba0d109">osErrorParameter</a> = -4, <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813eaf1fac0240218e51eb30a13da2f8aae81">osErrorNoMemory</a> = -5, <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813ea21635bdc492d3094fe83027fa4a30e2f">osErrorISR</a> = -6, <a href="cmsis.md#gga6c0dbe6069e4e7f47bb4cd32ae2b813ea66cc9ce9106b508df0e4a733a55a439d">osStatusReserved</a> = 0x7FFFFFFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330193221090250"><a name="p1330193221090250"></a><a name="p1330193221090250"></a>Enumerates return values of CMSIS-RTOS. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1899154273090250"></a>
<table><thead align="left"><tr id="row1951089809090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1846631333090250"><a name="p1846631333090250"></a><a name="p1846631333090250"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1760357149090250"><a name="p1760357149090250"></a><a name="p1760357149090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row799742865090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p246697543090250"><a name="p246697543090250"></a><a name="p246697543090250"></a><a href="cmsis.md#gae818f6611d25ba3140bede410a52d659">osKernelInitialize</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1834148634090250"><a name="p1834148634090250"></a><a name="p1834148634090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1688654081090250"><a name="p1688654081090250"></a><a name="p1688654081090250"></a>Initializes the RTOS kernel. </p>
</td>
</tr>
<tr id="row1990057841090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260280260090250"><a name="p260280260090250"></a><a name="p260280260090250"></a><a href="cmsis.md#ga6f7764e7250c5c5364c00c45a5d1d199">osKernelGetInfo</a> (<a href="osversion_t.md">osVersion_t</a> *version, char *id_buf, uint32_t id_size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p94166302090250"><a name="p94166302090250"></a><a name="p94166302090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1959426189090250"><a name="p1959426189090250"></a><a name="p1959426189090250"></a>Obtains the system version and name. </p>
</td>
</tr>
<tr id="row46868238090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1541139098090250"><a name="p1541139098090250"></a><a name="p1541139098090250"></a><a href="cmsis.md#ga48b69b81012fce051f639be288b243ba">osKernelGetState</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012425202090250"><a name="p1012425202090250"></a><a name="p1012425202090250"></a><a href="cmsis.md#ga08326469274b668140ca934b168a5ad4">osKernelState_t</a> </p>
<p id="p1438913731090250"><a name="p1438913731090250"></a><a name="p1438913731090250"></a>Obtains the kernel state. </p>
</td>
</tr>
<tr id="row93141798090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065702216090250"><a name="p1065702216090250"></a><a name="p1065702216090250"></a><a href="cmsis.md#ga9ae2cc00f0d89d7b6a307bba942b5221">osKernelStart</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1159684418090250"><a name="p1159684418090250"></a><a name="p1159684418090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p192892120090250"><a name="p192892120090250"></a><a name="p192892120090250"></a>Starts the kernel. </p>
</td>
</tr>
<tr id="row209519510090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772553251090250"><a name="p1772553251090250"></a><a name="p1772553251090250"></a><a href="cmsis.md#ga948609ee930d9b38336b9e1c2a4dfe12">osKernelLock</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057729028090250"><a name="p1057729028090250"></a><a name="p1057729028090250"></a>int32_t </p>
<p id="p508196005090250"><a name="p508196005090250"></a><a name="p508196005090250"></a>Locks the kernel. </p>
</td>
</tr>
<tr id="row1544241903090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227114477090250"><a name="p1227114477090250"></a><a name="p1227114477090250"></a><a href="cmsis.md#gaf401728b4657456198c33fe75f8d6720">osKernelUnlock</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368663055090250"><a name="p368663055090250"></a><a name="p368663055090250"></a>int32_t </p>
<p id="p755497317090250"><a name="p755497317090250"></a><a name="p755497317090250"></a>Unlocks the kernel. </p>
</td>
</tr>
<tr id="row1608971861090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898141786090250"><a name="p1898141786090250"></a><a name="p1898141786090250"></a><a href="cmsis.md#gae7d0a71b9586cbbb49fcbdf6a04f0289">osKernelRestoreLock</a> (int32_t lock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1921058087090250"><a name="p1921058087090250"></a><a name="p1921058087090250"></a>int32_t </p>
<p id="p946811632090250"><a name="p946811632090250"></a><a name="p946811632090250"></a>Restores the previous lock state of the kernel. </p>
</td>
</tr>
<tr id="row922379970090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469138375090250"><a name="p469138375090250"></a><a name="p469138375090250"></a><a href="cmsis.md#ga7a8d7bd927eaaa58999f91d7d6310cee">osKernelGetTickFreq</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1387801395090250"><a name="p1387801395090250"></a><a name="p1387801395090250"></a>uint32_t </p>
<p id="p656289240090250"><a name="p656289240090250"></a><a name="p656289240090250"></a>Obtains the number of kernel ticks per second. </p>
</td>
</tr>
<tr id="row1854139806090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829242757090250"><a name="p1829242757090250"></a><a name="p1829242757090250"></a><a href="cmsis.md#gae0fcaff6cecfb4013bb556c87afcd7d2">osKernelGetSysTimerCount</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971477047090250"><a name="p1971477047090250"></a><a name="p1971477047090250"></a>uint32_t </p>
<p id="p1098543503090250"><a name="p1098543503090250"></a><a name="p1098543503090250"></a>Obtains the kernel system timer. </p>
</td>
</tr>
<tr id="row178467930090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031477172090250"><a name="p1031477172090250"></a><a name="p1031477172090250"></a><a href="cmsis.md#ga4d69215a93220f72be3684cad582f16a">osKernelGetSysTimerFreq</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194030281090250"><a name="p1194030281090250"></a><a name="p1194030281090250"></a>uint32_t </p>
<p id="p520674801090250"><a name="p520674801090250"></a><a name="p520674801090250"></a>Obtains the frequency of the system timer. </p>
</td>
</tr>
<tr id="row743444024090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1742665484090250"><a name="p1742665484090250"></a><a name="p1742665484090250"></a><a href="cmsis.md#ga48d68b8666d99d28fa646ee1d2182b8f">osThreadNew</a> (<a href="cmsis.md#ga8ef2773ed8ef63ab8727e0d06ebec4d2">osThreadFunc_t</a> func, void *argument, const <a href="osthreadattr_t.md">osThreadAttr_t</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1393299522090250"><a name="p1393299522090250"></a><a name="p1393299522090250"></a><a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> </p>
<p id="p405070985090250"><a name="p405070985090250"></a><a name="p405070985090250"></a>Creates an active thread. </p>
</td>
</tr>
<tr id="row1888412109090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p792042095090250"><a name="p792042095090250"></a><a name="p792042095090250"></a><a href="cmsis.md#ga2fea4fad136f73ad973126789c4b99ee">osThreadGetName</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1819099495090250"><a name="p1819099495090250"></a><a name="p1819099495090250"></a>const char * </p>
<p id="p1847175877090250"><a name="p1847175877090250"></a><a name="p1847175877090250"></a>Obtains the name of a thread. </p>
</td>
</tr>
<tr id="row755531852090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424953302090250"><a name="p424953302090250"></a><a name="p424953302090250"></a><a href="cmsis.md#ga8df03548e89fbc56402a5cd584a505da">osThreadGetId</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016193319090250"><a name="p1016193319090250"></a><a name="p1016193319090250"></a><a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> </p>
<p id="p678135193090250"><a name="p678135193090250"></a><a name="p678135193090250"></a>Obtains the ID of the currently running thread. </p>
</td>
</tr>
<tr id="row1431317812090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1007051756090250"><a name="p1007051756090250"></a><a name="p1007051756090250"></a><a href="cmsis.md#gacc0a98b42f0a5928e12dc91dc76866b9">osThreadGetState</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p925951830090250"><a name="p925951830090250"></a><a name="p925951830090250"></a><a href="cmsis.md#gad3dc89e942e38d9f3af858a0269a820d">osThreadState_t</a> </p>
<p id="p1533090286090250"><a name="p1533090286090250"></a><a name="p1533090286090250"></a>Obtains the state of a thread. </p>
</td>
</tr>
<tr id="row112484224090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685024974090250"><a name="p1685024974090250"></a><a name="p1685024974090250"></a><a href="cmsis.md#gab9f8bd715d671c6ee27644867bc1bf65">osThreadGetStackSize</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p894782615090250"><a name="p894782615090250"></a><a name="p894782615090250"></a>uint32_t </p>
<p id="p1369832264090250"><a name="p1369832264090250"></a><a name="p1369832264090250"></a>Obtains the stack size of a thread. </p>
</td>
</tr>
<tr id="row1388306724090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619150379090250"><a name="p1619150379090250"></a><a name="p1619150379090250"></a><a href="cmsis.md#ga9c83bd5dd8de329701775d6ef7012720">osThreadGetStackSpace</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883360948090250"><a name="p1883360948090250"></a><a name="p1883360948090250"></a>uint32_t </p>
<p id="p1848091362090250"><a name="p1848091362090250"></a><a name="p1848091362090250"></a>Obtains the size of the available stack space for a thread based on the stack watermark. </p>
</td>
</tr>
<tr id="row1354398093090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1581391705090250"><a name="p1581391705090250"></a><a name="p1581391705090250"></a><a href="cmsis.md#ga861a420fb2d643115b06622903fb3bfb">osThreadSetPriority</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id, <a href="cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec">osPriority_t</a> priority)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1634517199090250"><a name="p1634517199090250"></a><a name="p1634517199090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p133274627090250"><a name="p133274627090250"></a><a name="p133274627090250"></a>Changes the priority of a thread. </p>
</td>
</tr>
<tr id="row1558991233090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p905691590090250"><a name="p905691590090250"></a><a name="p905691590090250"></a><a href="cmsis.md#ga0aeaf349604f456e68e78f9d3b42e44b">osThreadGetPriority</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1814851170090250"><a name="p1814851170090250"></a><a name="p1814851170090250"></a><a href="cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec">osPriority_t</a> </p>
<p id="p506129639090250"><a name="p506129639090250"></a><a name="p506129639090250"></a>Gets the prority of an active thread. </p>
</td>
</tr>
<tr id="row1201106667090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230013467090250"><a name="p1230013467090250"></a><a name="p1230013467090250"></a><a href="cmsis.md#gad01c7ec26535b1de6b018bb9466720e2">osThreadYield</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p134561144090250"><a name="p134561144090250"></a><a name="p134561144090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p609741765090250"><a name="p609741765090250"></a><a name="p609741765090250"></a>Sets the currently running thread to the ready state. </p>
</td>
</tr>
<tr id="row2135382762090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p650655676090250"><a name="p650655676090250"></a><a name="p650655676090250"></a><a href="cmsis.md#gaa9de419d0152bf77e9bbcd1f369fb990">osThreadSuspend</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219144903090250"><a name="p1219144903090250"></a><a name="p1219144903090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1783355561090250"><a name="p1783355561090250"></a><a name="p1783355561090250"></a>Suspends a thread. </p>
</td>
</tr>
<tr id="row1993700752090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629901711090250"><a name="p1629901711090250"></a><a name="p1629901711090250"></a><a href="cmsis.md#ga3dbad90eff394b02de76a452c84c5d80">osThreadResume</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261263218090250"><a name="p1261263218090250"></a><a name="p1261263218090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p810209819090250"><a name="p810209819090250"></a><a name="p810209819090250"></a>Resumes a thread from the suspended state. </p>
</td>
</tr>
<tr id="row790437917090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p925792699090250"><a name="p925792699090250"></a><a name="p925792699090250"></a><a href="cmsis.md#ga2f8ba6dba6e9c065a6e236ffd410d74a">osThreadTerminate</a> (<a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> thread_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964252843090250"><a name="p964252843090250"></a><a name="p964252843090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p158189665090250"><a name="p158189665090250"></a><a name="p158189665090250"></a>Terminates a thread. </p>
</td>
</tr>
<tr id="row268344103090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35873069090250"><a name="p35873069090250"></a><a name="p35873069090250"></a><a href="cmsis.md#ga495b3f812224e7301f23a691793765db">osThreadGetCount</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846660123090250"><a name="p846660123090250"></a><a name="p846660123090250"></a>uint32_t </p>
<p id="p272078954090250"><a name="p272078954090250"></a><a name="p272078954090250"></a>Obtains the number of active threads. </p>
</td>
</tr>
<tr id="row1490776235090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662913660090250"><a name="p1662913660090250"></a><a name="p1662913660090250"></a><a href="cmsis.md#gaf6055a51390ef65b6b6edc28bf47322e">osDelay</a> (uint32_t ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202254386090250"><a name="p1202254386090250"></a><a name="p1202254386090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1719090217090250"><a name="p1719090217090250"></a><a name="p1719090217090250"></a>Waits for a period of time. </p>
</td>
</tr>
<tr id="row684403835090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1644475469090250"><a name="p1644475469090250"></a><a name="p1644475469090250"></a><a href="cmsis.md#gaf0763875335699a9baa704ee36990d3c">osDelayUntil</a> (uint64_t ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959286144090250"><a name="p959286144090250"></a><a name="p959286144090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1342777906090250"><a name="p1342777906090250"></a><a name="p1342777906090250"></a>Waits until a specified time arrives. </p>
</td>
</tr>
<tr id="row52009486090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897557058090250"><a name="p1897557058090250"></a><a name="p1897557058090250"></a><a href="cmsis.md#gad4e7f785c5f700a509f55a3bf6a62bec">osTimerNew</a> (<a href="cmsis.md#ga77a298218f3c8382b39a09a6d134d040">osTimerFunc_t</a> func, <a href="cmsis.md#ga7dc24a4c2b90334427081c3da7a71915">osTimerType_t</a> type, void *argument, const <a href="ostimerattr_t.md">osTimerAttr_t</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p921037310090250"><a name="p921037310090250"></a><a name="p921037310090250"></a><a href="cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44">osTimerId_t</a> </p>
<p id="p451893916090250"><a name="p451893916090250"></a><a name="p451893916090250"></a>Creates and initializes a timer. </p>
</td>
</tr>
<tr id="row216911607090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p147238566090250"><a name="p147238566090250"></a><a name="p147238566090250"></a><a href="cmsis.md#gab6ee2859ea657641b7adfac599b8121d">osTimerStart</a> (<a href="cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44">osTimerId_t</a> timer_id, uint32_t ticks)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757566805090250"><a name="p757566805090250"></a><a name="p757566805090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1512494869090250"><a name="p1512494869090250"></a><a name="p1512494869090250"></a>Starts or restarts a timer. </p>
</td>
</tr>
<tr id="row2087532522090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p248244518090250"><a name="p248244518090250"></a><a name="p248244518090250"></a><a href="cmsis.md#gabd7a89356da7717293eb0bc5d87b8ac9">osTimerStop</a> (<a href="cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44">osTimerId_t</a> timer_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197205666090250"><a name="p1197205666090250"></a><a name="p1197205666090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p443716118090250"><a name="p443716118090250"></a><a name="p443716118090250"></a>Stops a timer. </p>
</td>
</tr>
<tr id="row2101698165090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390197401090250"><a name="p1390197401090250"></a><a name="p1390197401090250"></a><a href="cmsis.md#ga69d3589f54194022c30dd01e45ec6741">osTimerIsRunning</a> (<a href="cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44">osTimerId_t</a> timer_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159860846090250"><a name="p159860846090250"></a><a name="p159860846090250"></a>uint32_t </p>
<p id="p574371699090250"><a name="p574371699090250"></a><a name="p574371699090250"></a>Checks whether a timer is running. </p>
</td>
</tr>
<tr id="row451885803090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p38455186090250"><a name="p38455186090250"></a><a name="p38455186090250"></a><a href="cmsis.md#gad0001dd74721ab461789324806db2453">osTimerDelete</a> (<a href="cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44">osTimerId_t</a> timer_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p273749973090250"><a name="p273749973090250"></a><a name="p273749973090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p2045593629090250"><a name="p2045593629090250"></a><a name="p2045593629090250"></a>Deletes a timer. </p>
</td>
</tr>
<tr id="row1201401379090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1697446367090250"><a name="p1697446367090250"></a><a name="p1697446367090250"></a><a href="cmsis.md#gab14b1caeb12ffa42cce1bfe889cd07df">osEventFlagsNew</a> (const <a href="oseventflagsattr_t.md">osEventFlagsAttr_t</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1000909405090250"><a name="p1000909405090250"></a><a name="p1000909405090250"></a><a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a> </p>
<p id="p2058662895090250"><a name="p2058662895090250"></a><a name="p2058662895090250"></a>Creates and initializes an event flags object. </p>
</td>
</tr>
<tr id="row543164864090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2071669044090250"><a name="p2071669044090250"></a><a name="p2071669044090250"></a><a href="cmsis.md#ga33b71d14cecf90b4e72639dd19f23a5e">osEventFlagsSet</a> (<a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a> ef_id, uint32_t flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400041583090250"><a name="p400041583090250"></a><a name="p400041583090250"></a>uint32_t </p>
<p id="p1735626755090250"><a name="p1735626755090250"></a><a name="p1735626755090250"></a>Sets event flags. </p>
</td>
</tr>
<tr id="row1692586120090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p266045713090250"><a name="p266045713090250"></a><a name="p266045713090250"></a><a href="cmsis.md#ga93bf258ca0007c6641fbe8e4f2b8a1e5">osEventFlagsClear</a> (<a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a> ef_id, uint32_t flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238131297090250"><a name="p238131297090250"></a><a name="p238131297090250"></a>uint32_t </p>
<p id="p1132153197090250"><a name="p1132153197090250"></a><a name="p1132153197090250"></a>Clears event flags. </p>
</td>
</tr>
<tr id="row1662315210090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271185343090250"><a name="p1271185343090250"></a><a name="p1271185343090250"></a><a href="cmsis.md#ga8bda3185f46bfd278cea8a6cf357677d">osEventFlagsGet</a> (<a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a> ef_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029434219090250"><a name="p1029434219090250"></a><a name="p1029434219090250"></a>uint32_t </p>
<p id="p498614134090250"><a name="p498614134090250"></a><a name="p498614134090250"></a>Obtains event flags. </p>
</td>
</tr>
<tr id="row669533636090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1322273266090250"><a name="p1322273266090250"></a><a name="p1322273266090250"></a><a href="cmsis.md#ga52acb34a8322e58020227344fe662b4e">osEventFlagsWait</a> (<a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a> ef_id, uint32_t flags, uint32_t options, uint32_t timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892332746090250"><a name="p892332746090250"></a><a name="p892332746090250"></a>uint32_t </p>
<p id="p227750645090250"><a name="p227750645090250"></a><a name="p227750645090250"></a>Waits for event flags to trigger. </p>
</td>
</tr>
<tr id="row1680513899090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725702096090250"><a name="p725702096090250"></a><a name="p725702096090250"></a><a href="cmsis.md#ga7c4acf2fb0d506ec82905dee53fb5435">osEventFlagsDelete</a> (<a href="cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd">osEventFlagsId_t</a> ef_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108856022090250"><a name="p108856022090250"></a><a name="p108856022090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1798203589090250"><a name="p1798203589090250"></a><a name="p1798203589090250"></a>Deletes an event flags object. </p>
</td>
</tr>
<tr id="row952520070090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2018335753090250"><a name="p2018335753090250"></a><a name="p2018335753090250"></a><a href="cmsis.md#gab90920022ab944296821368ef6bb52f8">osMutexNew</a> (const <a href="osmutexattr_t.md">osMutexAttr_t</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1843122197090250"><a name="p1843122197090250"></a><a name="p1843122197090250"></a><a href="cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7">osMutexId_t</a> </p>
<p id="p280613966090250"><a name="p280613966090250"></a><a name="p280613966090250"></a>Creates and initializes a mutex. </p>
</td>
</tr>
<tr id="row1269870911090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p965897131090250"><a name="p965897131090250"></a><a name="p965897131090250"></a><a href="cmsis.md#gabc54686ea0fc281823b1763422d2a924">osMutexAcquire</a> (<a href="cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7">osMutexId_t</a> mutex_id, uint32_t timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1867552994090250"><a name="p1867552994090250"></a><a name="p1867552994090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p2061466169090250"><a name="p2061466169090250"></a><a name="p2061466169090250"></a>Obtains a mutex. </p>
</td>
</tr>
<tr id="row1075540636090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1258719341090250"><a name="p1258719341090250"></a><a name="p1258719341090250"></a><a href="cmsis.md#gaea629705703580ff58776bf73c8db915">osMutexRelease</a> (<a href="cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7">osMutexId_t</a> mutex_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p777149553090250"><a name="p777149553090250"></a><a name="p777149553090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1910796188090250"><a name="p1910796188090250"></a><a name="p1910796188090250"></a>Releases a mutex. </p>
</td>
</tr>
<tr id="row1561583574090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170499660090250"><a name="p170499660090250"></a><a name="p170499660090250"></a><a href="cmsis.md#ga7f9a7666df0978738cd570cb700b83fb">osMutexGetOwner</a> (<a href="cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7">osMutexId_t</a> mutex_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1329530093090250"><a name="p1329530093090250"></a><a name="p1329530093090250"></a><a href="cmsis.md#ga6333e016ba9b008e6dd76851c38b9217">osThreadId_t</a> </p>
<p id="p1922593352090250"><a name="p1922593352090250"></a><a name="p1922593352090250"></a>Obtains the thread ID of the currently acquired mutex. </p>
</td>
</tr>
<tr id="row1496814875090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p355795039090250"><a name="p355795039090250"></a><a name="p355795039090250"></a><a href="cmsis.md#gabee73ad227ba4587d3db12ef9bd582bc">osMutexDelete</a> (<a href="cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7">osMutexId_t</a> mutex_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p166748014090250"><a name="p166748014090250"></a><a name="p166748014090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p103516313090250"><a name="p103516313090250"></a><a name="p103516313090250"></a>Deletes a mutex. </p>
</td>
</tr>
<tr id="row1270826241090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1092281842090250"><a name="p1092281842090250"></a><a name="p1092281842090250"></a><a href="cmsis.md#ga2a39806ace781a0008a4374ca701b14a">osSemaphoreNew</a> (uint32_t max_count, uint32_t initial_count, const <a href="ossemaphoreattr_t.md">osSemaphoreAttr_t</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675111583090250"><a name="p675111583090250"></a><a name="p675111583090250"></a><a href="cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1">osSemaphoreId_t</a> </p>
<p id="p379891967090250"><a name="p379891967090250"></a><a name="p379891967090250"></a>Creates and initializes a semaphore object. </p>
</td>
</tr>
<tr id="row1480101660090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1309275613090250"><a name="p1309275613090250"></a><a name="p1309275613090250"></a><a href="cmsis.md#ga7e94c8b242a0c81f2cc79ec22895c87b">osSemaphoreAcquire</a> (<a href="cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1">osSemaphoreId_t</a> semaphore_id, uint32_t timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713871573090250"><a name="p1713871573090250"></a><a name="p1713871573090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1469592519090250"><a name="p1469592519090250"></a><a name="p1469592519090250"></a>Acquires a token of a semaphore object. </p>
</td>
</tr>
<tr id="row1865790632090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1795708278090250"><a name="p1795708278090250"></a><a name="p1795708278090250"></a><a href="cmsis.md#ga0abcee1b5449d7a6928fb9248c690bb6">osSemaphoreRelease</a> (<a href="cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1">osSemaphoreId_t</a> semaphore_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871461511090250"><a name="p1871461511090250"></a><a name="p1871461511090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p724590090090250"><a name="p724590090090250"></a><a name="p724590090090250"></a>Releases a token of a semaphore object. </p>
</td>
</tr>
<tr id="row382191023090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727535672090250"><a name="p727535672090250"></a><a name="p727535672090250"></a><a href="cmsis.md#ga7559d4dff3cda9992fc5ab5de3e74c70">osSemaphoreGetCount</a> (<a href="cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1">osSemaphoreId_t</a> semaphore_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257455345090250"><a name="p257455345090250"></a><a name="p257455345090250"></a>uint32_t </p>
<p id="p625963994090250"><a name="p625963994090250"></a><a name="p625963994090250"></a>Obtains the number of available tokens of a semaphore object. </p>
</td>
</tr>
<tr id="row925235557090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1181872198090250"><a name="p1181872198090250"></a><a name="p1181872198090250"></a><a href="cmsis.md#ga81258ce9c67fa89f07cc49d2e136cd88">osSemaphoreDelete</a> (<a href="cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1">osSemaphoreId_t</a> semaphore_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p112997878090250"><a name="p112997878090250"></a><a name="p112997878090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1979020402090250"><a name="p1979020402090250"></a><a name="p1979020402090250"></a>Deletes a semaphore object. </p>
</td>
</tr>
<tr id="row889362032090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981074668090250"><a name="p1981074668090250"></a><a name="p1981074668090250"></a><a href="cmsis.md#ga24e895a00f9d484db33aaf784c57bfed">osMessageQueueNew</a> (uint32_t msg_count, uint32_t msg_size, const <a href="osmessagequeueattr_t.md">osMessageQueueAttr_t</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p889035916090250"><a name="p889035916090250"></a><a name="p889035916090250"></a><a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> </p>
<p id="p604760059090250"><a name="p604760059090250"></a><a name="p604760059090250"></a>Creates and initializes a message queue. </p>
</td>
</tr>
<tr id="row693857076090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115656302090250"><a name="p2115656302090250"></a><a name="p2115656302090250"></a><a href="cmsis.md#gaa515fc8b956f721a8f72b2c505813bfc">osMessageQueuePut</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p137329068090250"><a name="p137329068090250"></a><a name="p137329068090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1394950454090250"><a name="p1394950454090250"></a><a name="p1394950454090250"></a>Places a message in a message queue. </p>
</td>
</tr>
<tr id="row350638474090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1752615542090250"><a name="p1752615542090250"></a><a name="p1752615542090250"></a><a href="cmsis.md#gad90d4959466a7a65105061da8256ab9e">osMessageQueueGet</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803734014090250"><a name="p1803734014090250"></a><a name="p1803734014090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1495732079090250"><a name="p1495732079090250"></a><a name="p1495732079090250"></a>Obtains a message in a message queue. </p>
</td>
</tr>
<tr id="row1616846801090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p446162096090250"><a name="p446162096090250"></a><a name="p446162096090250"></a><a href="cmsis.md#gac24f87d4f395e9e9c900c320e45ade8a">osMessageQueueGetCapacity</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531692571090250"><a name="p531692571090250"></a><a name="p531692571090250"></a>uint32_t </p>
<p id="p1314389543090250"><a name="p1314389543090250"></a><a name="p1314389543090250"></a>Obtains the maximum number of messages that can be placed in a message queue. </p>
</td>
</tr>
<tr id="row45491234090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1742359215090250"><a name="p1742359215090250"></a><a name="p1742359215090250"></a><a href="cmsis.md#ga96d3d84069b20359de48109e28a1a89e">osMessageQueueGetMsgSize</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11442926090250"><a name="p11442926090250"></a><a name="p11442926090250"></a>uint32_t </p>
<p id="p16864845090250"><a name="p16864845090250"></a><a name="p16864845090250"></a>Obtains the maximum size of messages that can be placed in a message queue. </p>
</td>
</tr>
<tr id="row2033672099090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2004095476090250"><a name="p2004095476090250"></a><a name="p2004095476090250"></a><a href="cmsis.md#ga6a32ac394fcff568b251c160cc3014b2">osMessageQueueGetCount</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443395988090250"><a name="p443395988090250"></a><a name="p443395988090250"></a>uint32_t </p>
<p id="p654324159090250"><a name="p654324159090250"></a><a name="p654324159090250"></a>Obtains the number of queued messages in a message queue. </p>
</td>
</tr>
<tr id="row493916106090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p434187786090250"><a name="p434187786090250"></a><a name="p434187786090250"></a><a href="cmsis.md#gaddf0904427436dd3880d46263c2dc9fa">osMessageQueueGetSpace</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440235203090250"><a name="p440235203090250"></a><a name="p440235203090250"></a>uint32_t </p>
<p id="p545236666090250"><a name="p545236666090250"></a><a name="p545236666090250"></a>Obtains the number of available slots for messages in a message queue. </p>
</td>
</tr>
<tr id="row732690822090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1552013968090250"><a name="p1552013968090250"></a><a name="p1552013968090250"></a><a href="cmsis.md#gaba987f665444e0d83fa6a3a68bc72abe">osMessageQueueDelete</a> (<a href="cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317">osMessageQueueId_t</a> mq_id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493314187090250"><a name="p493314187090250"></a><a name="p493314187090250"></a><a href="cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e">osStatus_t</a> </p>
<p id="p1867931534090250"><a name="p1867931534090250"></a><a name="p1867931534090250"></a>Deletes a message queue. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1235631918090250"></a>

## **Macro Definition Documentation**<a name="section1087727278090250"></a>

## osFlagsError<a name="ga01c1359c3a5640bff6e08f09bf94ce3a"></a>

```
#define osFlagsError   0x80000000U
```

 **Description:**

Indicates a flag error. 

## osFlagsErrorParameter<a name="gaa8a95ef938f8f5a9fcb815ec53184f77"></a>

```
#define osFlagsErrorParameter   0xFFFFFFFCU
```

 **Description:**

Indicates an incorrect parameter. 

## osFlagsErrorResource<a name="ga4db38b50da1889bcaaa7f747e844f904"></a>

```
#define osFlagsErrorResource   0xFFFFFFFDU
```

 **Description:**

Indicates a resource error. 

## osFlagsErrorTimeout<a name="ga2e951c3f1c3b7bff4eca3d7836cd19ca"></a>

```
#define osFlagsErrorTimeout   0xFFFFFFFEU
```

 **Description:**

Indicates a timeout. 

## osFlagsErrorUnknown<a name="ga3b1d9fbb83d64eedb62f831c9be647c3"></a>

```
#define osFlagsErrorUnknown   0xFFFFFFFFU
```

 **Description:**

Indicates an unknown error. 

## osFlagsNoClear<a name="gaade844a42237d8c37569d4d9b16b9f1c"></a>

```
#define osFlagsNoClear   0x00000002U
```

 **Description:**

Indicates that defined flags are not cleared. 

## osFlagsWaitAll<a name="ga8b6f562736fbfb5428940e0c017dec24"></a>

```
#define osFlagsWaitAll   0x00000001U
```

 **Description:**

Indicates that the system waits until all event flags are triggered. 

## osFlagsWaitAny<a name="ga18e63587b8450d5b8798b6f6ec04e012"></a>

```
#define osFlagsWaitAny   0x00000000U
```

 **Description:**

Indicates that the RTOS waits until any event flag is triggered. 

## osNoWait<a name="gaf235b13764754739d13c3cb709dc24e6"></a>

```
#define osNoWait   0x0U
```

 **Description:**

Indicates that the RTOS does not wait. 

## osWaitForever<a name="ga9eb9a7a797a42e4b55eb171ecc609ddb"></a>

```
#define osWaitForever   0xFFFFFFFFU
```

 **Description:**

Indicates that the RTOS waits forever unless an event flag is received. 

## **Typedef Documentation**<a name="section1489634255090250"></a>

## osEventFlagsId\_t<a name="gaf0a3ba8f502ca6581ed1009005c0dadd"></a>

```
typedef void* [osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd)
```

 **Description:**

Identifies an event flag. 

## osMessageQueueId\_t<a name="ga206dbc05367e03c39fc6d4d1ebcff317"></a>

```
typedef void* [osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317)
```

 **Description:**

Identifies a message queue. 

## osMutexId\_t<a name="ga29b7ba721f4fe0b11c84c55d079cc3e7"></a>

```
typedef void* [osMutexId_t](cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7)
```

 **Description:**

Identifies a mutex. 

## osSemaphoreId\_t<a name="ga5abc2c02a86678b63a711e13894ac5b1"></a>

```
typedef void* [osSemaphoreId_t](cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1)
```

 **Description:**

Identifies a semaphore object. 

## osThreadFunc\_t<a name="ga8ef2773ed8ef63ab8727e0d06ebec4d2"></a>

```
typedef void(* osThreadFunc_t) (void *argument)
```

 **Description:**

Callback for thread scheduling. 

## osThreadId\_t<a name="ga6333e016ba9b008e6dd76851c38b9217"></a>

```
typedef void* [osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217)
```

 **Description:**

Identifies a thread. 

## osTimerFunc\_t<a name="ga77a298218f3c8382b39a09a6d134d040"></a>

```
typedef void(* osTimerFunc_t) (void *argument)
```

 **Description:**

Callback for timer triggering. 

## osTimerId\_t<a name="gac2000ac2a8c6740700fd8e6c938cff44"></a>

```
typedef void* [osTimerId_t](cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44)
```

 **Description:**

Identifies a timer. 

## TZ\_ModuleId\_t<a name="gad5ef21485fe5f60263bc0b48006202cb"></a>

```
typedef uint32_t [TZ_ModuleId_t](cmsis.md#gad5ef21485fe5f60263bc0b48006202cb)
```

 **Description:**

Identifies a TrustZone module call process. 

## **Enumeration Type Documentation**<a name="section284564826090250"></a>

## os\_timer\_align\_type<a name="ga3d617b70715d7fb2c7c6f06809ee3913"></a>

```
enum [os_timer_align_type](cmsis.md#ga3d617b70715d7fb2c7c6f06809ee3913)
```

 **Description:**

Enumerates timer alignment modes. 

<a name="table1836217971090250"></a>
<table><thead align="left"><tr id="row325369088090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p498431558090250"><a name="p498431558090250"></a><a name="p498431558090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p269937183090250"><a name="p269937183090250"></a><a name="p269937183090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1098759703090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3d617b70715d7fb2c7c6f06809ee3913a30e89a6569f3f32e6d4f2c77ceba3bd9"><a name="gga3d617b70715d7fb2c7c6f06809ee3913a30e89a6569f3f32e6d4f2c77ceba3bd9"></a><a name="gga3d617b70715d7fb2c7c6f06809ee3913a30e89a6569f3f32e6d4f2c77ceba3bd9"></a></strong>osTimerAlignIgnore </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437798712090250"><a name="p437798712090250"></a><a name="p437798712090250"></a>The timer ignores alignment. </p>
 </td>
</tr>
<tr id="row94654824090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga3d617b70715d7fb2c7c6f06809ee3913a8fd513208cb4a465b439fb04d9223f43"><a name="gga3d617b70715d7fb2c7c6f06809ee3913a8fd513208cb4a465b439fb04d9223f43"></a><a name="gga3d617b70715d7fb2c7c6f06809ee3913a8fd513208cb4a465b439fb04d9223f43"></a></strong>osTimerAlignAllow </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896510077090250"><a name="p896510077090250"></a><a name="p896510077090250"></a>The timer allows alignment. </p>
 </td>
</tr>
</tbody>
</table>

## os\_timer\_rouses\_type<a name="ga6274cbe33c6db824bbc40dc6eaa8e578"></a>

```
enum [os_timer_rouses_type](cmsis.md#ga6274cbe33c6db824bbc40dc6eaa8e578)
```

 **Description:**

Enumerates timer permissions. 

<a name="table227731790090250"></a>
<table><thead align="left"><tr id="row1403198625090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1689747389090250"><a name="p1689747389090250"></a><a name="p1689747389090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1284263830090250"><a name="p1284263830090250"></a><a name="p1284263830090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row846629439090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6274cbe33c6db824bbc40dc6eaa8e578a9bc896516fd34ea78d2c3106f421bc1e"><a name="gga6274cbe33c6db824bbc40dc6eaa8e578a9bc896516fd34ea78d2c3106f421bc1e"></a><a name="gga6274cbe33c6db824bbc40dc6eaa8e578a9bc896516fd34ea78d2c3106f421bc1e"></a></strong>osTimerRousesIgnore </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281374364090250"><a name="p1281374364090250"></a><a name="p1281374364090250"></a>The timer is not allowed to wake up the RTOS. </p>
 </td>
</tr>
<tr id="row1051108023090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6274cbe33c6db824bbc40dc6eaa8e578ae45ed4bdfd52ff62958e347eab459edb"><a name="gga6274cbe33c6db824bbc40dc6eaa8e578ae45ed4bdfd52ff62958e347eab459edb"></a><a name="gga6274cbe33c6db824bbc40dc6eaa8e578ae45ed4bdfd52ff62958e347eab459edb"></a></strong>osTimerRousesAllow </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p34938554090250"><a name="p34938554090250"></a><a name="p34938554090250"></a>The timer is allowed to wake up the RTOS. </p>
 </td>
</tr>
</tbody>
</table>

## osKernelState\_t<a name="ga08326469274b668140ca934b168a5ad4"></a>

```
enum [osKernelState_t](cmsis.md#ga08326469274b668140ca934b168a5ad4)
```

 **Description:**

Enumerates kernel states. 

<a name="table287195635090250"></a>
<table><thead align="left"><tr id="row1980226811090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1014037713090250"><a name="p1014037713090250"></a><a name="p1014037713090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1441547524090250"><a name="p1441547524090250"></a><a name="p1441547524090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1633530269090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4ae9a7d578873c28590009479283922db9"><a name="gga08326469274b668140ca934b168a5ad4ae9a7d578873c28590009479283922db9"></a><a name="gga08326469274b668140ca934b168a5ad4ae9a7d578873c28590009479283922db9"></a></strong>osKernelInactive </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p482897686090250"><a name="p482897686090250"></a><a name="p482897686090250"></a>The kernel is inactive. </p>
 </td>
</tr>
<tr id="row1851852451090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4a87ef9718301b92bfa9c97d61d660a8aa"><a name="gga08326469274b668140ca934b168a5ad4a87ef9718301b92bfa9c97d61d660a8aa"></a><a name="gga08326469274b668140ca934b168a5ad4a87ef9718301b92bfa9c97d61d660a8aa"></a></strong>osKernelReady </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557479659090250"><a name="p1557479659090250"></a><a name="p1557479659090250"></a>The kernel is ready. </p>
 </td>
</tr>
<tr id="row76019443090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4a98d8ad539d2cc6c3dbb7138356049db2"><a name="gga08326469274b668140ca934b168a5ad4a98d8ad539d2cc6c3dbb7138356049db2"></a><a name="gga08326469274b668140ca934b168a5ad4a98d8ad539d2cc6c3dbb7138356049db2"></a></strong>osKernelRunning </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021703702090250"><a name="p2021703702090250"></a><a name="p2021703702090250"></a>The kernel is running. </p>
 </td>
</tr>
<tr id="row1993663245090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4a033026d41a9309bd9551df1ae8153553"><a name="gga08326469274b668140ca934b168a5ad4a033026d41a9309bd9551df1ae8153553"></a><a name="gga08326469274b668140ca934b168a5ad4a033026d41a9309bd9551df1ae8153553"></a></strong>osKernelLocked </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84249120090250"><a name="p84249120090250"></a><a name="p84249120090250"></a>The kernel is locked. </p>
 </td>
</tr>
<tr id="row1058040229090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4a3240807627595e80f59a46434639b765"><a name="gga08326469274b668140ca934b168a5ad4a3240807627595e80f59a46434639b765"></a><a name="gga08326469274b668140ca934b168a5ad4a3240807627595e80f59a46434639b765"></a></strong>osKernelSuspended </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p887058425090250"><a name="p887058425090250"></a><a name="p887058425090250"></a>The kernel is suspended. </p>
 </td>
</tr>
<tr id="row1664502463090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4a1b942a8c76daeba2925a763d4d7567a2"><a name="gga08326469274b668140ca934b168a5ad4a1b942a8c76daeba2925a763d4d7567a2"></a><a name="gga08326469274b668140ca934b168a5ad4a1b942a8c76daeba2925a763d4d7567a2"></a></strong>osKernelError </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p759696319090250"><a name="p759696319090250"></a><a name="p759696319090250"></a>The kernel is abnormal. </p>
 </td>
</tr>
<tr id="row750120422090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga08326469274b668140ca934b168a5ad4a9cc4cc562a20a28c0f6f4b878ecf2df5"><a name="gga08326469274b668140ca934b168a5ad4a9cc4cc562a20a28c0f6f4b878ecf2df5"></a><a name="gga08326469274b668140ca934b168a5ad4a9cc4cc562a20a28c0f6f4b878ecf2df5"></a></strong>osKernelReserved </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175062953090250"><a name="p1175062953090250"></a><a name="p1175062953090250"></a>Reserved </p>
 </td>
</tr>
</tbody>
</table>

## osPriority\_t<a name="gad4e3e0971b41f2d17584a8c6837342ec"></a>

```
enum [osPriority_t](cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec)
```

 **Description:**

Enumerates thread priorities. 

<a name="table1689724863090250"></a>
<table><thead align="left"><tr id="row518225001090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1430080520090250"><a name="p1430080520090250"></a><a name="p1430080520090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1377410769090250"><a name="p1377410769090250"></a><a name="p1377410769090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1104803511090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca6c437c7185161a3bd1e7e4669dfa17a3"><a name="ggad4e3e0971b41f2d17584a8c6837342eca6c437c7185161a3bd1e7e4669dfa17a3"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca6c437c7185161a3bd1e7e4669dfa17a3"></a></strong>osPriorityNone </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p109344457090250"><a name="p109344457090250"></a><a name="p109344457090250"></a>Undefined </p>
 </td>
</tr>
<tr id="row348812650090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca549e79a43ff4f8b2b31afb613f5caa81"><a name="ggad4e3e0971b41f2d17584a8c6837342eca549e79a43ff4f8b2b31afb613f5caa81"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca549e79a43ff4f8b2b31afb613f5caa81"></a></strong>osPriorityIdle </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025452445090250"><a name="p2025452445090250"></a><a name="p2025452445090250"></a>Reserved for idle threads </p>
 </td>
</tr>
<tr id="row1659823571090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca61cb822239ac8f66dfbdc7291598a3d4"><a name="ggad4e3e0971b41f2d17584a8c6837342eca61cb822239ac8f66dfbdc7291598a3d4"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca61cb822239ac8f66dfbdc7291598a3d4"></a></strong>osPriorityLow </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2055148347090250"><a name="p2055148347090250"></a><a name="p2055148347090250"></a>Low (unsupported) </p>
 </td>
</tr>
<tr id="row1134492620090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecaba2b6919f0b630c8c1b2c940e3bfadbe"><a name="ggad4e3e0971b41f2d17584a8c6837342ecaba2b6919f0b630c8c1b2c940e3bfadbe"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecaba2b6919f0b630c8c1b2c940e3bfadbe"></a></strong>osPriorityLow1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1328172626090250"><a name="p1328172626090250"></a><a name="p1328172626090250"></a>Low + 1 </p>
 </td>
</tr>
<tr id="row729383398090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca78ad5d00aa07a2b4bf30a639544f5507"><a name="ggad4e3e0971b41f2d17584a8c6837342eca78ad5d00aa07a2b4bf30a639544f5507"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca78ad5d00aa07a2b4bf30a639544f5507"></a></strong>osPriorityLow2 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436394351090250"><a name="p436394351090250"></a><a name="p436394351090250"></a>Low + 2 </p>
 </td>
</tr>
<tr id="row1715162194090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca28ccb07942c16f5f5efefb6cf68a7f50"><a name="ggad4e3e0971b41f2d17584a8c6837342eca28ccb07942c16f5f5efefb6cf68a7f50"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca28ccb07942c16f5f5efefb6cf68a7f50"></a></strong>osPriorityLow3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1166064145090250"><a name="p1166064145090250"></a><a name="p1166064145090250"></a>Low + 3 </p>
 </td>
</tr>
<tr id="row671758216090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca5a4a4f26d5b220a968e221e854f69a81"><a name="ggad4e3e0971b41f2d17584a8c6837342eca5a4a4f26d5b220a968e221e854f69a81"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca5a4a4f26d5b220a968e221e854f69a81"></a></strong>osPriorityLow4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820668387090250"><a name="p1820668387090250"></a><a name="p1820668387090250"></a>Low + 4 </p>
 </td>
</tr>
<tr id="row327039744090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecad69b8c14809bc5bdce4887f5a57d9353"><a name="ggad4e3e0971b41f2d17584a8c6837342ecad69b8c14809bc5bdce4887f5a57d9353"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecad69b8c14809bc5bdce4887f5a57d9353"></a></strong>osPriorityLow5 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1171732241090250"><a name="p1171732241090250"></a><a name="p1171732241090250"></a>Low + 5 </p>
 </td>
</tr>
<tr id="row2147032422090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecac0f188468664d06d4cd9e6e1ed351393"><a name="ggad4e3e0971b41f2d17584a8c6837342ecac0f188468664d06d4cd9e6e1ed351393"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecac0f188468664d06d4cd9e6e1ed351393"></a></strong>osPriorityLow6 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268731320090250"><a name="p268731320090250"></a><a name="p268731320090250"></a>Low + 6 </p>
 </td>
</tr>
<tr id="row808842840090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca5b151ebba7fdeb1baaa9b7b420890b7a"><a name="ggad4e3e0971b41f2d17584a8c6837342eca5b151ebba7fdeb1baaa9b7b420890b7a"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca5b151ebba7fdeb1baaa9b7b420890b7a"></a></strong>osPriorityLow7 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p72607269090250"><a name="p72607269090250"></a><a name="p72607269090250"></a>Low + 7 </p>
 </td>
</tr>
<tr id="row1033124844090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca193b650117c209b4a203954542bcc3e6"><a name="ggad4e3e0971b41f2d17584a8c6837342eca193b650117c209b4a203954542bcc3e6"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca193b650117c209b4a203954542bcc3e6"></a></strong>osPriorityBelowNormal </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567360274090250"><a name="p1567360274090250"></a><a name="p1567360274090250"></a>Below normal </p>
 </td>
</tr>
<tr id="row848806143090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca9138da7187690b15f52d8e5729c18da5"><a name="ggad4e3e0971b41f2d17584a8c6837342eca9138da7187690b15f52d8e5729c18da5"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca9138da7187690b15f52d8e5729c18da5"></a></strong>osPriorityBelowNormal1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1987587823090250"><a name="p1987587823090250"></a><a name="p1987587823090250"></a>Below normal + 1 </p>
 </td>
</tr>
<tr id="row1624831849090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca4f081d6735bf2f513338b07eddf13ae3"><a name="ggad4e3e0971b41f2d17584a8c6837342eca4f081d6735bf2f513338b07eddf13ae3"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca4f081d6735bf2f513338b07eddf13ae3"></a></strong>osPriorityBelowNormal2 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1498053874090250"><a name="p1498053874090250"></a><a name="p1498053874090250"></a>Below normal + 2 </p>
 </td>
</tr>
<tr id="row1760362340090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca19c013690d0d6bf3ac90707942be3fdf"><a name="ggad4e3e0971b41f2d17584a8c6837342eca19c013690d0d6bf3ac90707942be3fdf"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca19c013690d0d6bf3ac90707942be3fdf"></a></strong>osPriorityBelowNormal3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175145959090250"><a name="p175145959090250"></a><a name="p175145959090250"></a>Below normal + 3 </p>
 </td>
</tr>
<tr id="row1611926128090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca36931ad6cee5e4700e2c8622bdd2cd24"><a name="ggad4e3e0971b41f2d17584a8c6837342eca36931ad6cee5e4700e2c8622bdd2cd24"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca36931ad6cee5e4700e2c8622bdd2cd24"></a></strong>osPriorityBelowNormal4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805877662090250"><a name="p805877662090250"></a><a name="p805877662090250"></a>Below normal + 4 </p>
 </td>
</tr>
<tr id="row1735222425090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca0bcd9ad1e7a02e3bf03be7dcc8ece38e"><a name="ggad4e3e0971b41f2d17584a8c6837342eca0bcd9ad1e7a02e3bf03be7dcc8ece38e"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca0bcd9ad1e7a02e3bf03be7dcc8ece38e"></a></strong>osPriorityBelowNormal5 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p714087067090250"><a name="p714087067090250"></a><a name="p714087067090250"></a>Below normal + 5 </p>
 </td>
</tr>
<tr id="row1385931923090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecabd3cc7df5b92b752ddf1e7843a786c05"><a name="ggad4e3e0971b41f2d17584a8c6837342ecabd3cc7df5b92b752ddf1e7843a786c05"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecabd3cc7df5b92b752ddf1e7843a786c05"></a></strong>osPriorityBelowNormal6 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1429942227090250"><a name="p1429942227090250"></a><a name="p1429942227090250"></a>Below normal + 6 </p>
 </td>
</tr>
<tr id="row107441292090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecab18e3bda7b5e418e309a62d6267ea14b"><a name="ggad4e3e0971b41f2d17584a8c6837342ecab18e3bda7b5e418e309a62d6267ea14b"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecab18e3bda7b5e418e309a62d6267ea14b"></a></strong>osPriorityBelowNormal7 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521971294090250"><a name="p1521971294090250"></a><a name="p1521971294090250"></a>Below normal + 7 (unsupported) </p>
 </td>
</tr>
<tr id="row192583087090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca45a2895ad30c79fb97de18cac7cc19f1"><a name="ggad4e3e0971b41f2d17584a8c6837342eca45a2895ad30c79fb97de18cac7cc19f1"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca45a2895ad30c79fb97de18cac7cc19f1"></a></strong>osPriorityNormal </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p618576611090250"><a name="p618576611090250"></a><a name="p618576611090250"></a>Normal (unsupported) </p>
 </td>
</tr>
<tr id="row178918605090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca3e70c19e03d5a54e66bd071f0776782c"><a name="ggad4e3e0971b41f2d17584a8c6837342eca3e70c19e03d5a54e66bd071f0776782c"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca3e70c19e03d5a54e66bd071f0776782c"></a></strong>osPriorityNormal1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1957236276090250"><a name="p1957236276090250"></a><a name="p1957236276090250"></a>Normal + 1 (unsupported) </p>
 </td>
</tr>
<tr id="row351634453090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca19e96f2b025b6462a43b1965043c8205"><a name="ggad4e3e0971b41f2d17584a8c6837342eca19e96f2b025b6462a43b1965043c8205"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca19e96f2b025b6462a43b1965043c8205"></a></strong>osPriorityNormal2 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868693847090250"><a name="p1868693847090250"></a><a name="p1868693847090250"></a>Normal + 2 (unsupported) </p>
 </td>
</tr>
<tr id="row1860383564090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca402bd7ab26fb57c8cee8cf94168f4c91"><a name="ggad4e3e0971b41f2d17584a8c6837342eca402bd7ab26fb57c8cee8cf94168f4c91"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca402bd7ab26fb57c8cee8cf94168f4c91"></a></strong>osPriorityNormal3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720182421090250"><a name="p1720182421090250"></a><a name="p1720182421090250"></a>Normal + 3 (unsupported) </p>
 </td>
</tr>
<tr id="row1694675723090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca93ef07d3a107aeee6508bfd29ba3485d"><a name="ggad4e3e0971b41f2d17584a8c6837342eca93ef07d3a107aeee6508bfd29ba3485d"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca93ef07d3a107aeee6508bfd29ba3485d"></a></strong>osPriorityNormal4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989422856090250"><a name="p989422856090250"></a><a name="p989422856090250"></a>Normal + 4 (unsupported) </p>
 </td>
</tr>
<tr id="row1555750351090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca68f3f6fdaa639de300277802aa13a0ab"><a name="ggad4e3e0971b41f2d17584a8c6837342eca68f3f6fdaa639de300277802aa13a0ab"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca68f3f6fdaa639de300277802aa13a0ab"></a></strong>osPriorityNormal5 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915454635090250"><a name="p915454635090250"></a><a name="p915454635090250"></a>Normal + 5 (unsupported) </p>
 </td>
</tr>
<tr id="row1447617957090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca8221eb0d059726a6309f1f2d0cdb6204"><a name="ggad4e3e0971b41f2d17584a8c6837342eca8221eb0d059726a6309f1f2d0cdb6204"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca8221eb0d059726a6309f1f2d0cdb6204"></a></strong>osPriorityNormal6 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p698463553090250"><a name="p698463553090250"></a><a name="p698463553090250"></a>Normal + 6 (unsupported) </p>
 </td>
</tr>
<tr id="row1631965974090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca049abd04f8951415407ec9d92bd9b80b"><a name="ggad4e3e0971b41f2d17584a8c6837342eca049abd04f8951415407ec9d92bd9b80b"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca049abd04f8951415407ec9d92bd9b80b"></a></strong>osPriorityNormal7 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p446405364090250"><a name="p446405364090250"></a><a name="p446405364090250"></a>Normal + 7 (unsupported) </p>
 </td>
</tr>
<tr id="row1710722150090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca17b36cd9cd38652c2bc6d4803990674b"><a name="ggad4e3e0971b41f2d17584a8c6837342eca17b36cd9cd38652c2bc6d4803990674b"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca17b36cd9cd38652c2bc6d4803990674b"></a></strong>osPriorityAboveNormal </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p651485468090250"><a name="p651485468090250"></a><a name="p651485468090250"></a>Above normal (unsupported) </p>
 </td>
</tr>
<tr id="row787419781090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecabfeafc713edfc7b9130aa5c762d68998"><a name="ggad4e3e0971b41f2d17584a8c6837342ecabfeafc713edfc7b9130aa5c762d68998"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecabfeafc713edfc7b9130aa5c762d68998"></a></strong>osPriorityAboveNormal1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917137975090250"><a name="p917137975090250"></a><a name="p917137975090250"></a>Above normal + 1 (unsupported) </p>
 </td>
</tr>
<tr id="row828216859090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca901acf86070e06f5990b611734ee2562"><a name="ggad4e3e0971b41f2d17584a8c6837342eca901acf86070e06f5990b611734ee2562"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca901acf86070e06f5990b611734ee2562"></a></strong>osPriorityAboveNormal2 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84055825090250"><a name="p84055825090250"></a><a name="p84055825090250"></a>Above normal + 2 (unsupported) </p>
 </td>
</tr>
<tr id="row1803895695090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecad566b876b64e6efdc3eba0fc04e54013"><a name="ggad4e3e0971b41f2d17584a8c6837342ecad566b876b64e6efdc3eba0fc04e54013"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecad566b876b64e6efdc3eba0fc04e54013"></a></strong>osPriorityAboveNormal3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1766358270090250"><a name="p1766358270090250"></a><a name="p1766358270090250"></a>Above normal + 3 (unsupported) </p>
 </td>
</tr>
<tr id="row209380215090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca6ccac37d7dae4586a2031966d36a63ec"><a name="ggad4e3e0971b41f2d17584a8c6837342eca6ccac37d7dae4586a2031966d36a63ec"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca6ccac37d7dae4586a2031966d36a63ec"></a></strong>osPriorityAboveNormal4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40911473090250"><a name="p40911473090250"></a><a name="p40911473090250"></a>Above normal + 4 (unsupported) </p>
 </td>
</tr>
<tr id="row2140447145090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecae36e8b38ee046a3104bcccabb10cf78c"><a name="ggad4e3e0971b41f2d17584a8c6837342ecae36e8b38ee046a3104bcccabb10cf78c"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecae36e8b38ee046a3104bcccabb10cf78c"></a></strong>osPriorityAboveNormal5 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688502018090250"><a name="p1688502018090250"></a><a name="p1688502018090250"></a>Above normal + 5 (unsupported) </p>
 </td>
</tr>
<tr id="row789494669090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca61e6ce27e1e0f34f2540b413b8a8b207"><a name="ggad4e3e0971b41f2d17584a8c6837342eca61e6ce27e1e0f34f2540b413b8a8b207"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca61e6ce27e1e0f34f2540b413b8a8b207"></a></strong>osPriorityAboveNormal6 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p758884436090250"><a name="p758884436090250"></a><a name="p758884436090250"></a>Above normal + 6 (unsupported) </p>
 </td>
</tr>
<tr id="row1260510814090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecadbbb0fed3ada6b9b50d4a628abc2a67d"><a name="ggad4e3e0971b41f2d17584a8c6837342ecadbbb0fed3ada6b9b50d4a628abc2a67d"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecadbbb0fed3ada6b9b50d4a628abc2a67d"></a></strong>osPriorityAboveNormal7 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711873953090250"><a name="p711873953090250"></a><a name="p711873953090250"></a>Above normal + 7 (unsupported) </p>
 </td>
</tr>
<tr id="row1928010713090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca914433934143a9ba767e59577c56e6c2"><a name="ggad4e3e0971b41f2d17584a8c6837342eca914433934143a9ba767e59577c56e6c2"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca914433934143a9ba767e59577c56e6c2"></a></strong>osPriorityHigh </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p485532090090250"><a name="p485532090090250"></a><a name="p485532090090250"></a>High (unsupported) </p>
 </td>
</tr>
<tr id="row1479032122090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca17b7a7e6febf12444a84e90edfce36cb"><a name="ggad4e3e0971b41f2d17584a8c6837342eca17b7a7e6febf12444a84e90edfce36cb"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca17b7a7e6febf12444a84e90edfce36cb"></a></strong>osPriorityHigh1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1000560582090250"><a name="p1000560582090250"></a><a name="p1000560582090250"></a>High + 1 (unsupported) </p>
 </td>
</tr>
<tr id="row581848161090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca40a120cf8bbc42e575455c027f3d9b03"><a name="ggad4e3e0971b41f2d17584a8c6837342eca40a120cf8bbc42e575455c027f3d9b03"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca40a120cf8bbc42e575455c027f3d9b03"></a></strong>osPriorityHigh2 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445225448090250"><a name="p445225448090250"></a><a name="p445225448090250"></a>High + 2 (unsupported) </p>
 </td>
</tr>
<tr id="row844886463090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca0b15518b0b5321a29efa0b42b2f8c759"><a name="ggad4e3e0971b41f2d17584a8c6837342eca0b15518b0b5321a29efa0b42b2f8c759"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca0b15518b0b5321a29efa0b42b2f8c759"></a></strong>osPriorityHigh3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p533325553090250"><a name="p533325553090250"></a><a name="p533325553090250"></a>High + 3 (unsupported) </p>
 </td>
</tr>
<tr id="row380126283090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecafe5a4f393fab04551ac7d93e80cdf0fb"><a name="ggad4e3e0971b41f2d17584a8c6837342ecafe5a4f393fab04551ac7d93e80cdf0fb"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecafe5a4f393fab04551ac7d93e80cdf0fb"></a></strong>osPriorityHigh4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p38791612090250"><a name="p38791612090250"></a><a name="p38791612090250"></a>High + 4 (unsupported) </p>
 </td>
</tr>
<tr id="row1237690099090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca5960841bfbdd959b163429e8502ea4e9"><a name="ggad4e3e0971b41f2d17584a8c6837342eca5960841bfbdd959b163429e8502ea4e9"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca5960841bfbdd959b163429e8502ea4e9"></a></strong>osPriorityHigh5 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224080492090250"><a name="p224080492090250"></a><a name="p224080492090250"></a>High + 5 (unsupported) </p>
 </td>
</tr>
<tr id="row725264330090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca5714dda6effc1a3f8ec155d97e3e69bc"><a name="ggad4e3e0971b41f2d17584a8c6837342eca5714dda6effc1a3f8ec155d97e3e69bc"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca5714dda6effc1a3f8ec155d97e3e69bc"></a></strong>osPriorityHigh6 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735452728090250"><a name="p735452728090250"></a><a name="p735452728090250"></a>High + 6 (unsupported) </p>
 </td>
</tr>
<tr id="row1155266072090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca63ad0cc52a701ef3d9df52b59b995652"><a name="ggad4e3e0971b41f2d17584a8c6837342eca63ad0cc52a701ef3d9df52b59b995652"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca63ad0cc52a701ef3d9df52b59b995652"></a></strong>osPriorityHigh7 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995785102090250"><a name="p1995785102090250"></a><a name="p1995785102090250"></a>High + 7 (unsupported) </p>
 </td>
</tr>
<tr id="row1331207590090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca1485dec3702434a1ec3cb74c7a17a4af"><a name="ggad4e3e0971b41f2d17584a8c6837342eca1485dec3702434a1ec3cb74c7a17a4af"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca1485dec3702434a1ec3cb74c7a17a4af"></a></strong>osPriorityRealtime </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p76698219090250"><a name="p76698219090250"></a><a name="p76698219090250"></a>Real-time (unsupported) </p>
 </td>
</tr>
<tr id="row1018200023090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecaf685a06b30f0635476e21347a986305b"><a name="ggad4e3e0971b41f2d17584a8c6837342ecaf685a06b30f0635476e21347a986305b"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecaf685a06b30f0635476e21347a986305b"></a></strong>osPriorityRealtime1 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1835045585090250"><a name="p1835045585090250"></a><a name="p1835045585090250"></a>Real-time + 1 (unsupported) </p>
 </td>
</tr>
<tr id="row2139961364090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecab832bd9de84e5eec2ecad69d085dadff"><a name="ggad4e3e0971b41f2d17584a8c6837342ecab832bd9de84e5eec2ecad69d085dadff"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecab832bd9de84e5eec2ecad69d085dadff"></a></strong>osPriorityRealtime2 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368950900090250"><a name="p368950900090250"></a><a name="p368950900090250"></a>Real-time + 2 (unsupported) </p>
 </td>
</tr>
<tr id="row312586290090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca3f2261e5e733e92844ae8c630f2f9eaa"><a name="ggad4e3e0971b41f2d17584a8c6837342eca3f2261e5e733e92844ae8c630f2f9eaa"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca3f2261e5e733e92844ae8c630f2f9eaa"></a></strong>osPriorityRealtime3 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833784264090250"><a name="p833784264090250"></a><a name="p833784264090250"></a>Real-time + 3 (unsupported) </p>
 </td>
</tr>
<tr id="row1403365950090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecaf614e3dc966d559cd9d9d2a0f78ebe70"><a name="ggad4e3e0971b41f2d17584a8c6837342ecaf614e3dc966d559cd9d9d2a0f78ebe70"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecaf614e3dc966d559cd9d9d2a0f78ebe70"></a></strong>osPriorityRealtime4 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p879792692090250"><a name="p879792692090250"></a><a name="p879792692090250"></a>Real-time + 4 (unsupported) </p>
 </td>
</tr>
<tr id="row1792182242090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecaff84f31ceff203c711fb9476443507df"><a name="ggad4e3e0971b41f2d17584a8c6837342ecaff84f31ceff203c711fb9476443507df"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecaff84f31ceff203c711fb9476443507df"></a></strong>osPriorityRealtime5 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389275921090250"><a name="p1389275921090250"></a><a name="p1389275921090250"></a>Real-time + 5 (unsupported) </p>
 </td>
</tr>
<tr id="row438723639090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca80ae9d0dd256312c0c8f44af48316194"><a name="ggad4e3e0971b41f2d17584a8c6837342eca80ae9d0dd256312c0c8f44af48316194"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca80ae9d0dd256312c0c8f44af48316194"></a></strong>osPriorityRealtime6 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p534509445090250"><a name="p534509445090250"></a><a name="p534509445090250"></a>Real-time + 6 (unsupported) </p>
 </td>
</tr>
<tr id="row1863933563090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecaa76da6825c4bd31c4958200bc289103b"><a name="ggad4e3e0971b41f2d17584a8c6837342ecaa76da6825c4bd31c4958200bc289103b"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecaa76da6825c4bd31c4958200bc289103b"></a></strong>osPriorityRealtime7 </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p561531890090250"><a name="p561531890090250"></a><a name="p561531890090250"></a>Real-time + 7 (unsupported) </p>
 </td>
</tr>
<tr id="row150556248090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342eca3943224956e1ea667c6a931c74137b79"><a name="ggad4e3e0971b41f2d17584a8c6837342eca3943224956e1ea667c6a931c74137b79"></a><a name="ggad4e3e0971b41f2d17584a8c6837342eca3943224956e1ea667c6a931c74137b79"></a></strong>osPriorityISR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053314826090250"><a name="p2053314826090250"></a><a name="p2053314826090250"></a>Reserved for ISR deferred threads (unsupported) </p>
 </td>
</tr>
<tr id="row468769664090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecae35f5e2f9c64ad346822521b643bdea4"><a name="ggad4e3e0971b41f2d17584a8c6837342ecae35f5e2f9c64ad346822521b643bdea4"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecae35f5e2f9c64ad346822521b643bdea4"></a></strong>osPriorityError </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820807770090250"><a name="p1820807770090250"></a><a name="p1820807770090250"></a>Invalid </p>
 </td>
</tr>
<tr id="row1603914888090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad4e3e0971b41f2d17584a8c6837342ecac86c171f8d466cced0cb1b03bb03343b"><a name="ggad4e3e0971b41f2d17584a8c6837342ecac86c171f8d466cced0cb1b03bb03343b"></a><a name="ggad4e3e0971b41f2d17584a8c6837342ecac86c171f8d466cced0cb1b03bb03343b"></a></strong>osPriorityReserved </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p966283679090250"><a name="p966283679090250"></a><a name="p966283679090250"></a>Reserved. It enables the compiler to identify enumeration variables as 32-bit numbers and prevents the enumeration variables from being optimized. </p>
 </td>
</tr>
</tbody>
</table>

## osStatus\_t<a name="ga6c0dbe6069e4e7f47bb4cd32ae2b813e"></a>

```
enum [osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e)
```

 **Description:**

Enumerates return values of CMSIS-RTOS. 

<a name="table992958103090250"></a>
<table><thead align="left"><tr id="row715318202090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1291924456090250"><a name="p1291924456090250"></a><a name="p1291924456090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p610280516090250"><a name="p610280516090250"></a><a name="p610280516090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1239385712090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea9e1c9e2550bb4de8969a935acffc968f"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea9e1c9e2550bb4de8969a935acffc968f"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea9e1c9e2550bb4de8969a935acffc968f"></a></strong>osOK </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p619008443090250"><a name="p619008443090250"></a><a name="p619008443090250"></a>Operation completed successfully </p>
 </td>
</tr>
<tr id="row1917881258090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813eabb7b2d2c4efa66df42f1c10635467b09"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813eabb7b2d2c4efa66df42f1c10635467b09"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813eabb7b2d2c4efa66df42f1c10635467b09"></a></strong>osError </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756026530090250"><a name="p756026530090250"></a><a name="p756026530090250"></a>Unspecified error </p>
 </td>
</tr>
<tr id="row1283008742090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea913eb5df15ad85f8557eb3a456b56879"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea913eb5df15ad85f8557eb3a456b56879"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea913eb5df15ad85f8557eb3a456b56879"></a></strong>osErrorTimeout </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416229245090250"><a name="p416229245090250"></a><a name="p416229245090250"></a>Timeout </p>
 </td>
</tr>
<tr id="row1001052655090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea8fc5801e8b0482bdf22ad63a77f0155d"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea8fc5801e8b0482bdf22ad63a77f0155d"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea8fc5801e8b0482bdf22ad63a77f0155d"></a></strong>osErrorResource </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449990248090250"><a name="p1449990248090250"></a><a name="p1449990248090250"></a>Resource error </p>
 </td>
</tr>
<tr id="row1791665510090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813eac24adca6a5d072c9f01c32178ba0d109"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813eac24adca6a5d072c9f01c32178ba0d109"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813eac24adca6a5d072c9f01c32178ba0d109"></a></strong>osErrorParameter </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p466967428090250"><a name="p466967428090250"></a><a name="p466967428090250"></a>Incorrect parameter </p>
 </td>
</tr>
<tr id="row135859002090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813eaf1fac0240218e51eb30a13da2f8aae81"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813eaf1fac0240218e51eb30a13da2f8aae81"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813eaf1fac0240218e51eb30a13da2f8aae81"></a></strong>osErrorNoMemory </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p951008331090250"><a name="p951008331090250"></a><a name="p951008331090250"></a>Insufficient memory </p>
 </td>
</tr>
<tr id="row1169874254090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea21635bdc492d3094fe83027fa4a30e2f"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea21635bdc492d3094fe83027fa4a30e2f"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea21635bdc492d3094fe83027fa4a30e2f"></a></strong>osErrorISR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278838114090250"><a name="p278838114090250"></a><a name="p278838114090250"></a><a href="service.md">Service</a> interruption </p>
 </td>
</tr>
<tr id="row1918627501090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea66cc9ce9106b508df0e4a733a55a439d"><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea66cc9ce9106b508df0e4a733a55a439d"></a><a name="gga6c0dbe6069e4e7f47bb4cd32ae2b813ea66cc9ce9106b508df0e4a733a55a439d"></a></strong>osStatusReserved </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493861054090250"><a name="p493861054090250"></a><a name="p493861054090250"></a>Reserved. It is used to prevent the compiler from optimizing enumerations. </p>
 </td>
</tr>
</tbody>
</table>

## osThreadState\_t<a name="gad3dc89e942e38d9f3af858a0269a820d"></a>

```
enum [osThreadState_t](cmsis.md#gad3dc89e942e38d9f3af858a0269a820d)
```

 **Description:**

Enumerates thread states. 

<a name="table241524802090250"></a>
<table><thead align="left"><tr id="row1352872149090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1333654054090250"><a name="p1333654054090250"></a><a name="p1333654054090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1931472376090250"><a name="p1931472376090250"></a><a name="p1931472376090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2132733003090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820da7d7d4f719a1be6daa63a251563585fdd"><a name="ggad3dc89e942e38d9f3af858a0269a820da7d7d4f719a1be6daa63a251563585fdd"></a><a name="ggad3dc89e942e38d9f3af858a0269a820da7d7d4f719a1be6daa63a251563585fdd"></a></strong>osThreadInactive </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1829870549090250"><a name="p1829870549090250"></a><a name="p1829870549090250"></a>The thread is inactive. </p>
 </td>
</tr>
<tr id="row1081183361090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820dad9a040e03d7e7943c0217a3359fc1e8b"><a name="ggad3dc89e942e38d9f3af858a0269a820dad9a040e03d7e7943c0217a3359fc1e8b"></a><a name="ggad3dc89e942e38d9f3af858a0269a820dad9a040e03d7e7943c0217a3359fc1e8b"></a></strong>osThreadReady </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1254462578090250"><a name="p1254462578090250"></a><a name="p1254462578090250"></a>The thread is ready. </p>
 </td>
</tr>
<tr id="row2025094898090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820da71dae1f35a4b4d9d2ab24e186461a17f"><a name="ggad3dc89e942e38d9f3af858a0269a820da71dae1f35a4b4d9d2ab24e186461a17f"></a><a name="ggad3dc89e942e38d9f3af858a0269a820da71dae1f35a4b4d9d2ab24e186461a17f"></a></strong>osThreadRunning </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622283207090250"><a name="p1622283207090250"></a><a name="p1622283207090250"></a>The thread is running. </p>
 </td>
</tr>
<tr id="row885743422090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820da476cd2370e6938974fb2a79811408819"><a name="ggad3dc89e942e38d9f3af858a0269a820da476cd2370e6938974fb2a79811408819"></a><a name="ggad3dc89e942e38d9f3af858a0269a820da476cd2370e6938974fb2a79811408819"></a></strong>osThreadBlocked </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1904773047090250"><a name="p1904773047090250"></a><a name="p1904773047090250"></a>The thread is blocked. </p>
 </td>
</tr>
<tr id="row1068339065090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820dac2a35280d5475f56352c539c9c9b42f9"><a name="ggad3dc89e942e38d9f3af858a0269a820dac2a35280d5475f56352c539c9c9b42f9"></a><a name="ggad3dc89e942e38d9f3af858a0269a820dac2a35280d5475f56352c539c9c9b42f9"></a></strong>osThreadTerminated </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635108716090250"><a name="p635108716090250"></a><a name="p635108716090250"></a>The thread is terminated. </p>
 </td>
</tr>
<tr id="row907452661090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820dac841e73a7198a42364c9450f1f54a0ef"><a name="ggad3dc89e942e38d9f3af858a0269a820dac841e73a7198a42364c9450f1f54a0ef"></a><a name="ggad3dc89e942e38d9f3af858a0269a820dac841e73a7198a42364c9450f1f54a0ef"></a></strong>osThreadError </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694183081090250"><a name="p1694183081090250"></a><a name="p1694183081090250"></a>The thread is abnormal. </p>
 </td>
</tr>
<tr id="row1061016816090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3dc89e942e38d9f3af858a0269a820da8872f7e352370eb11ee772c7dcca6e6c"><a name="ggad3dc89e942e38d9f3af858a0269a820da8872f7e352370eb11ee772c7dcca6e6c"></a><a name="ggad3dc89e942e38d9f3af858a0269a820da8872f7e352370eb11ee772c7dcca6e6c"></a></strong>osThreadReserved </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1647553897090250"><a name="p1647553897090250"></a><a name="p1647553897090250"></a>Reserved </p>
 </td>
</tr>
</tbody>
</table>

## osTimerType\_t<a name="ga7dc24a4c2b90334427081c3da7a71915"></a>

```
enum [osTimerType_t](cmsis.md#ga7dc24a4c2b90334427081c3da7a71915)
```

 **Description:**

Enumerates timer types. 

<a name="table1505838234090250"></a>
<table><thead align="left"><tr id="row1729447361090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1558235782090250"><a name="p1558235782090250"></a><a name="p1558235782090250"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p175042271090250"><a name="p175042271090250"></a><a name="p175042271090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row784347070090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7dc24a4c2b90334427081c3da7a71915ad21712f8df5f97069c82dc9eec37b951"><a name="gga7dc24a4c2b90334427081c3da7a71915ad21712f8df5f97069c82dc9eec37b951"></a><a name="gga7dc24a4c2b90334427081c3da7a71915ad21712f8df5f97069c82dc9eec37b951"></a></strong>osTimerOnce </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p160813828090250"><a name="p160813828090250"></a><a name="p160813828090250"></a>One-shot timer </p>
 </td>
</tr>
<tr id="row1291139204090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7dc24a4c2b90334427081c3da7a71915ab9c91f9699162edb09bb7c90c11c8788"><a name="gga7dc24a4c2b90334427081c3da7a71915ab9c91f9699162edb09bb7c90c11c8788"></a><a name="gga7dc24a4c2b90334427081c3da7a71915ab9c91f9699162edb09bb7c90c11c8788"></a></strong>osTimerPeriodic </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670293461090250"><a name="p1670293461090250"></a><a name="p1670293461090250"></a>Repeating timer </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1855397309090250"></a>

## osDelay\(\)<a name="gaf6055a51390ef65b6b6edc28bf47322e"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osDelay (uint32_t ticks)
```

 **Description:**

Waits for a period of time. 

**Parameters:**

<a name="table848902177090250"></a>
<table><thead align="left"><tr id="row1723687961090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1679409375090250"><a name="p1679409375090250"></a><a name="p1679409375090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1650349438090250"><a name="p1650349438090250"></a><a name="p1650349438090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1150796627090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ticks</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of ticks to wait for. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osDelayUntil\(\)<a name="gaf0763875335699a9baa704ee36990d3c"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osDelayUntil (uint64_t ticks)
```

 **Description:**

Waits until a specified time arrives. 

**Parameters:**

<a name="table443348182090250"></a>
<table><thead align="left"><tr id="row689766761090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p137279800090250"><a name="p137279800090250"></a><a name="p137279800090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p277291111090250"><a name="p277291111090250"></a><a name="p277291111090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row385646029090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ticks</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of ticks converted from the absolute time. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osEventFlagsClear\(\)<a name="ga93bf258ca0007c6641fbe8e4f2b8a1e5"></a>

```
uint32_t osEventFlagsClear ([osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd) ef_id, uint32_t flags )
```

 **Description:**

Clears event flags. 

**Parameters:**

<a name="table325533048090250"></a>
<table><thead align="left"><tr id="row370250432090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p708220755090250"><a name="p708220755090250"></a><a name="p708220755090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1542322767090250"><a name="p1542322767090250"></a><a name="p1542322767090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row927731956090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ef_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags ID, which is obtained using osEventFlagsNew. </td>
</tr>
<tr id="row1753787196090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags to clear. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the event flags; returns osFlagsErrorParameter in the case of an error. 



## osEventFlagsDelete\(\)<a name="ga7c4acf2fb0d506ec82905dee53fb5435"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osEventFlagsDelete ([osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd) ef_id)
```

 **Description:**

Deletes an event flags object. 

**Parameters:**

<a name="table1765923834090250"></a>
<table><thead align="left"><tr id="row550359566090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2139523843090250"><a name="p2139523843090250"></a><a name="p2139523843090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p511325479090250"><a name="p511325479090250"></a><a name="p511325479090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row83411032090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ef_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags ID, which is obtained using osEventFlagsNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osEventFlagsGet\(\)<a name="ga8bda3185f46bfd278cea8a6cf357677d"></a>

```
uint32_t osEventFlagsGet ([osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd) ef_id)
```

 **Description:**

Obtains event flags. 

**Parameters:**

<a name="table1141585917090250"></a>
<table><thead align="left"><tr id="row1578550193090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1327289553090250"><a name="p1327289553090250"></a><a name="p1327289553090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1002963399090250"><a name="p1002963399090250"></a><a name="p1002963399090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1612429020090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ef_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags ID, which is obtained using osEventFlagsNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the event flags triggered. 



## osEventFlagsNew\(\)<a name="gab14b1caeb12ffa42cce1bfe889cd07df"></a>

```
[osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd) osEventFlagsNew (const [osEventFlagsAttr_t](oseventflagsattr_t.md) * attr)
```

 **Description:**

Creates and initializes an event flags object. 

**Parameters:**

<a name="table378849457090250"></a>
<table><thead align="left"><tr id="row240639983090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1726514187090250"><a name="p1726514187090250"></a><a name="p1726514187090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1171372825090250"><a name="p1171372825090250"></a><a name="p1171372825090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row388828657090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the event flags attributes. This parameter is not used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the event flags ID; returns NULL in the case of an error. 



## osEventFlagsSet\(\)<a name="ga33b71d14cecf90b4e72639dd19f23a5e"></a>

```
uint32_t osEventFlagsSet ([osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd) ef_id, uint32_t flags )
```

 **Description:**

Sets event flags. 

**Parameters:**

<a name="table2066470592090250"></a>
<table><thead align="left"><tr id="row558788763090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2113271372090250"><a name="p2113271372090250"></a><a name="p2113271372090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p742742685090250"><a name="p742742685090250"></a><a name="p742742685090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1871300734090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ef_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags ID, which is obtained using osEventFlagsNew. </td>
</tr>
<tr id="row650548324090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the event flags; returns osFlagsErrorParameter in the case of an error. 



## osEventFlagsWait\(\)<a name="ga52acb34a8322e58020227344fe662b4e"></a>

```
uint32_t osEventFlagsWait ([osEventFlagsId_t](cmsis.md#gaf0a3ba8f502ca6581ed1009005c0dadd) ef_id, uint32_t flags, uint32_t options, uint32_t timeout )
```

 **Description:**

Waits for event flags to trigger. 

**Parameters:**

<a name="table1550015587090250"></a>
<table><thead align="left"><tr id="row275152460090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p950407712090250"><a name="p950407712090250"></a><a name="p950407712090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1191525067090250"><a name="p1191525067090250"></a><a name="p1191525067090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1350678542090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ef_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags ID, which is obtained using osEventFlagsNew. </td>
</tr>
<tr id="row543836688090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the event flags to trigger. </td>
</tr>
<tr id="row633327716090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">options</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the configuration of the event flags to trigger. </td>
</tr>
<tr id="row1462870699090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the triggered event flags; returns an error value in the case of an error. 



## osKernelGetInfo\(\)<a name="ga6f7764e7250c5c5364c00c45a5d1d199"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osKernelGetInfo ([osVersion_t](osversion_t.md) * version, char * id_buf, uint32_t id_size )
```

 **Description:**

Obtains the system version and name. 

**Parameters:**

<a name="table194211431090250"></a>
<table><thead align="left"><tr id="row1603807651090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1337112182090250"><a name="p1337112182090250"></a><a name="p1337112182090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p505558291090250"><a name="p505558291090250"></a><a name="p505558291090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row84579636090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">version</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the version. </td>
</tr>
<tr id="row1785751195090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id_buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the kernel ID. </td>
</tr>
<tr id="row71173663090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id_size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the buffer for storing the kernel ID. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osKernelGetState\(\)<a name="ga48b69b81012fce051f639be288b243ba"></a>

```
[osKernelState_t](cmsis.md#ga08326469274b668140ca934b168a5ad4) osKernelGetState (void )
```

 **Description:**

Obtains the kernel state. 

**Returns:**

Returns the kernel state. 



## osKernelGetSysTimerCount\(\)<a name="gae0fcaff6cecfb4013bb556c87afcd7d2"></a>

```
uint32_t osKernelGetSysTimerCount (void )
```

 **Description:**

Obtains the kernel system timer. 

**Returns:**

Returns the kernel system timer. 



## osKernelGetSysTimerFreq\(\)<a name="ga4d69215a93220f72be3684cad582f16a"></a>

```
uint32_t osKernelGetSysTimerFreq (void )
```

 **Description:**

Obtains the frequency of the system timer. 

**Returns:**

Returns the system timer frequency. 



## osKernelGetTickFreq\(\)<a name="ga7a8d7bd927eaaa58999f91d7d6310cee"></a>

```
uint32_t osKernelGetTickFreq (void )
```

 **Description:**

Obtains the number of kernel ticks per second. 

**Returns:**

Returns the number of kernel ticks. 



## osKernelInitialize\(\)<a name="gae818f6611d25ba3140bede410a52d659"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osKernelInitialize (void )
```

 **Description:**

Initializes the RTOS kernel. 

**Returns:**

Returns the CMSIS-RTOS running result. 



## osKernelLock\(\)<a name="ga948609ee930d9b38336b9e1c2a4dfe12"></a>

```
int32_t osKernelLock (void )
```

 **Description:**

Locks the kernel. 

**Returns:**

Returns 1 if the kernel is locked successfully; returns 0 if the lock starts; returns a negative value in the case of an error. 



## osKernelRestoreLock\(\)<a name="gae7d0a71b9586cbbb49fcbdf6a04f0289"></a>

```
int32_t osKernelRestoreLock (int32_t lock)
```

 **Description:**

Restores the previous lock state of the kernel. 

**Parameters:**

<a name="table1813663426090250"></a>
<table><thead align="left"><tr id="row1694281803090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1413932663090250"><a name="p1413932663090250"></a><a name="p1413932663090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p38355276090250"><a name="p38355276090250"></a><a name="p38355276090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row475496493090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">locks</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the lock state to restore to. The value 1 indicates the locked state, and 0 indicates the unlocked state. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns 1 if the kernel is locked; returns 0 if the kernel is not locked; returns a negative value in the case of an error. 



## osKernelStart\(\)<a name="ga9ae2cc00f0d89d7b6a307bba942b5221"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osKernelStart (void )
```

 **Description:**

Starts the kernel. 

**Returns:**

Returns the CMSIS-RTOS running result. 



## osKernelUnlock\(\)<a name="gaf401728b4657456198c33fe75f8d6720"></a>

```
int32_t osKernelUnlock (void )
```

 **Description:**

Unlocks the kernel. 

**Returns:**

Returns 1 if the kernel is unlocked successfully; returns 0 if the kernel is not locked; returns a negative value in the case of an error. 



## osMessageQueueDelete\(\)<a name="gaba987f665444e0d83fa6a3a68bc72abe"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osMessageQueueDelete ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id)
```

 **Description:**

Deletes a message queue. 

**Parameters:**

<a name="table1798673762090250"></a>
<table><thead align="left"><tr id="row1076258451090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1864440229090250"><a name="p1864440229090250"></a><a name="p1864440229090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1638614021090250"><a name="p1638614021090250"></a><a name="p1638614021090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2055272948090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osMessageQueueGet\(\)<a name="gad90d4959466a7a65105061da8256ab9e"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osMessageQueueGet ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id, void * msg_ptr, uint8_t * msg_prio, uint32_t timeout )
```

 **Description:**

Obtains a message in a message queue. 

**Parameters:**

<a name="table2011900349090250"></a>
<table><thead align="left"><tr id="row1852226093090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p926073059090250"><a name="p926073059090250"></a><a name="p926073059090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1678998021090250"><a name="p1678998021090250"></a><a name="p1678998021090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2106018630090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
<tr id="row263699644090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msg_ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the message to be retrieved from the message queue. </td>
</tr>
<tr id="row386487457090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msg_prio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the priority of the message to be retrieved from the message queue. This parameter can be left empty. </td>
</tr>
<tr id="row409579739090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osMessageQueueGetCapacity\(\)<a name="gac24f87d4f395e9e9c900c320e45ade8a"></a>

```
uint32_t osMessageQueueGetCapacity ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id)
```

 **Description:**

Obtains the maximum number of messages that can be placed in a message queue. 

**Parameters:**

<a name="table1173290137090250"></a>
<table><thead align="left"><tr id="row369170253090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p615023892090250"><a name="p615023892090250"></a><a name="p615023892090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1365996789090250"><a name="p1365996789090250"></a><a name="p1365996789090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row23389728090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the maximum number. 



## osMessageQueueGetCount\(\)<a name="ga6a32ac394fcff568b251c160cc3014b2"></a>

```
uint32_t osMessageQueueGetCount ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id)
```

 **Description:**

Obtains the number of queued messages in a message queue. 

**Parameters:**

<a name="table1909308856090250"></a>
<table><thead align="left"><tr id="row1396755194090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1271894121090250"><a name="p1271894121090250"></a><a name="p1271894121090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1092613085090250"><a name="p1092613085090250"></a><a name="p1092613085090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row867879758090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of queued messages. 



## osMessageQueueGetMsgSize\(\)<a name="ga96d3d84069b20359de48109e28a1a89e"></a>

```
uint32_t osMessageQueueGetMsgSize ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id)
```

 **Description:**

Obtains the maximum size of messages that can be placed in a message queue. 

**Parameters:**

<a name="table2124067138090250"></a>
<table><thead align="left"><tr id="row419958260090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1278577043090250"><a name="p1278577043090250"></a><a name="p1278577043090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p661360274090250"><a name="p661360274090250"></a><a name="p661360274090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1759020522090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the maximum message size. 



## osMessageQueueGetSpace\(\)<a name="gaddf0904427436dd3880d46263c2dc9fa"></a>

```
uint32_t osMessageQueueGetSpace ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id)
```

 **Description:**

Obtains the number of available slots for messages in a message queue. 

**Parameters:**

<a name="table359554621090250"></a>
<table><thead align="left"><tr id="row597095658090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1960588237090250"><a name="p1960588237090250"></a><a name="p1960588237090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1977129767090250"><a name="p1977129767090250"></a><a name="p1977129767090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1492294645090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of available slots for messages. 



## osMessageQueueNew\(\)<a name="ga24e895a00f9d484db33aaf784c57bfed"></a>

```
[osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const [osMessageQueueAttr_t](osmessagequeueattr_t.md) * attr )
```

 **Description:**

Creates and initializes a message queue. 

**Parameters:**

<a name="table1941885872090250"></a>
<table><thead align="left"><tr id="row1846653214090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p772171677090250"><a name="p772171677090250"></a><a name="p772171677090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1782746591090250"><a name="p1782746591090250"></a><a name="p1782746591090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1120235772090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msg_count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of messages in the message queue. </td>
</tr>
<tr id="row430427519090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msg_size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of messages in the message queue. </td>
</tr>
<tr id="row608029399090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the message queue attributes. This parameter is not used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the message queue ID; returns NULL in the case of an error. 



## osMessageQueuePut\(\)<a name="gaa515fc8b956f721a8f72b2c505813bfc"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osMessageQueuePut ([osMessageQueueId_t](cmsis.md#ga206dbc05367e03c39fc6d4d1ebcff317) mq_id, const void * msg_ptr, uint8_t msg_prio, uint32_t timeout )
```

 **Description:**

Places a message in a message queue. 

**Parameters:**

<a name="table1715675988090250"></a>
<table><thead align="left"><tr id="row255825692090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2005782684090250"><a name="p2005782684090250"></a><a name="p2005782684090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1824220565090250"><a name="p1824220565090250"></a><a name="p1824220565090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row569393262090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">osMessageQueueId_t</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue ID, which is obtained using osMessageQueueNew. </td>
</tr>
<tr id="row2025706103090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msg_ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the message to be placed in the message queue. </td>
</tr>
<tr id="row1847615698090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msg_prio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the priority of the message to be placed in the message queue. </td>
</tr>
<tr id="row154415090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osMutexAcquire\(\)<a name="gabc54686ea0fc281823b1763422d2a924"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osMutexAcquire ([osMutexId_t](cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7) mutex_id, uint32_t timeout )
```

 **Description:**

Obtains a mutex. 

**Parameters:**

<a name="table2059609382090250"></a>
<table><thead align="left"><tr id="row68237904090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p851911542090250"><a name="p851911542090250"></a><a name="p851911542090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p840817647090250"><a name="p840817647090250"></a><a name="p840817647090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1193918870090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mutex ID, which is obtained using osMutexNew. </td>
</tr>
<tr id="row1115992711090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osMutexDelete\(\)<a name="gabee73ad227ba4587d3db12ef9bd582bc"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osMutexDelete ([osMutexId_t](cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7) mutex_id)
```

 **Description:**

Deletes a mutex. 

**Parameters:**

<a name="table2121567312090250"></a>
<table><thead align="left"><tr id="row1861288593090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1379706677090250"><a name="p1379706677090250"></a><a name="p1379706677090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1388929521090250"><a name="p1388929521090250"></a><a name="p1388929521090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row408866369090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mutex ID, which is obtained using osMutexNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osMutexGetOwner\(\)<a name="ga7f9a7666df0978738cd570cb700b83fb"></a>

```
[osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) osMutexGetOwner ([osMutexId_t](cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7) mutex_id)
```

 **Description:**

Obtains the thread ID of the currently acquired mutex. 

**Parameters:**

<a name="table580980851090250"></a>
<table><thead align="left"><tr id="row1865133722090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p643135276090250"><a name="p643135276090250"></a><a name="p643135276090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p513332980090250"><a name="p513332980090250"></a><a name="p513332980090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1220264760090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mutex ID, which is obtained using osMutexNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the thread ID. 



## osMutexNew\(\)<a name="gab90920022ab944296821368ef6bb52f8"></a>

```
[osMutexId_t](cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7) osMutexNew (const [osMutexAttr_t](osmutexattr_t.md) * attr)
```

 **Description:**

Creates and initializes a mutex. 

**Parameters:**

<a name="table57095177090250"></a>
<table><thead align="left"><tr id="row1416271458090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p452913578090250"><a name="p452913578090250"></a><a name="p452913578090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1329040929090250"><a name="p1329040929090250"></a><a name="p1329040929090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1747403795090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex attributes. This parameter is not used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the mutex ID; returns NULL in the case of an error. 



## osMutexRelease\(\)<a name="gaea629705703580ff58776bf73c8db915"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osMutexRelease ([osMutexId_t](cmsis.md#ga29b7ba721f4fe0b11c84c55d079cc3e7) mutex_id)
```

 **Description:**

Releases a mutex. 

**Parameters:**

<a name="table1221075283090250"></a>
<table><thead align="left"><tr id="row1945454503090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2008218735090250"><a name="p2008218735090250"></a><a name="p2008218735090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1601917846090250"><a name="p1601917846090250"></a><a name="p1601917846090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1804068431090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mutex ID, which is obtained using osMutexNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osSemaphoreAcquire\(\)<a name="ga7e94c8b242a0c81f2cc79ec22895c87b"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osSemaphoreAcquire ([osSemaphoreId_t](cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1) semaphore_id, uint32_t timeout )
```

 **Description:**

Acquires a token of a semaphore object. 

**Parameters:**

<a name="table743416150090250"></a>
<table><thead align="left"><tr id="row255489513090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2035142835090250"><a name="p2035142835090250"></a><a name="p2035142835090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1806278292090250"><a name="p1806278292090250"></a><a name="p1806278292090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1830609322090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">semaphore_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the semaphore ID, which is obtained using osSemaphoreNew. </td>
</tr>
<tr id="row1779890494090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osSemaphoreDelete\(\)<a name="ga81258ce9c67fa89f07cc49d2e136cd88"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osSemaphoreDelete ([osSemaphoreId_t](cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1) semaphore_id)
```

 **Description:**

Deletes a semaphore object. 

**Parameters:**

<a name="table78144019090250"></a>
<table><thead align="left"><tr id="row1407704546090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1620113590090250"><a name="p1620113590090250"></a><a name="p1620113590090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p588953136090250"><a name="p588953136090250"></a><a name="p588953136090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row125253785090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">semaphore_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the semaphore ID, which is obtained using osSemaphoreNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osSemaphoreGetCount\(\)<a name="ga7559d4dff3cda9992fc5ab5de3e74c70"></a>

```
uint32_t osSemaphoreGetCount ([osSemaphoreId_t](cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1) semaphore_id)
```

 **Description:**

Obtains the number of available tokens of a semaphore object. 

**Parameters:**

<a name="table685301603090250"></a>
<table><thead align="left"><tr id="row834941044090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1159774707090250"><a name="p1159774707090250"></a><a name="p1159774707090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p934159945090250"><a name="p934159945090250"></a><a name="p934159945090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1519734178090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">semaphore_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the semaphore ID, which is obtained using osSemaphoreNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of available tokens. 



## osSemaphoreNew\(\)<a name="ga2a39806ace781a0008a4374ca701b14a"></a>

```
[osSemaphoreId_t](cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1) osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const [osSemaphoreAttr_t](ossemaphoreattr_t.md) * attr )
```

 **Description:**

Creates and initializes a semaphore object. 

**Parameters:**

<a name="table9153161090250"></a>
<table><thead align="left"><tr id="row916707657090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p710177164090250"><a name="p710177164090250"></a><a name="p710177164090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2133460281090250"><a name="p2133460281090250"></a><a name="p2133460281090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1360604292090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">max_count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum number of available tokens that can be applied for. </td>
</tr>
<tr id="row541794366090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">initial_count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the initial number of available tokens. </td>
</tr>
<tr id="row316709721090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore attributes. This parameter is not used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the semaphore ID; returns NULL in the case of an error. 



## osSemaphoreRelease\(\)<a name="ga0abcee1b5449d7a6928fb9248c690bb6"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osSemaphoreRelease ([osSemaphoreId_t](cmsis.md#ga5abc2c02a86678b63a711e13894ac5b1) semaphore_id)
```

 **Description:**

Releases a token of a semaphore object. 

**Parameters:**

<a name="table1167115334090250"></a>
<table><thead align="left"><tr id="row748774274090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p945233376090250"><a name="p945233376090250"></a><a name="p945233376090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p132589404090250"><a name="p132589404090250"></a><a name="p132589404090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1987891692090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">semaphore_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the semaphore ID, which is obtained using osSemaphoreNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osThreadGetCount\(\)<a name="ga495b3f812224e7301f23a691793765db"></a>

```
uint32_t osThreadGetCount (void )
```

 **Description:**

Obtains the number of active threads. 

**Returns:**

Returns the number; returns 0 in the case of an error. 



## osThreadGetId\(\)<a name="ga8df03548e89fbc56402a5cd584a505da"></a>

```
[osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) osThreadGetId (void )
```

 **Description:**

Obtains the ID of the currently running thread. 

**Returns:**

Returns the thread ID; returns NULL in the case of an error. 



## osThreadGetName\(\)<a name="ga2fea4fad136f73ad973126789c4b99ee"></a>

```
const char* osThreadGetName ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Obtains the name of a thread. 

**Parameters:**

<a name="table1148204373090250"></a>
<table><thead align="left"><tr id="row20299880090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1997905909090250"><a name="p1997905909090250"></a><a name="p1997905909090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1380388578090250"><a name="p1380388578090250"></a><a name="p1380388578090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1796352112090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the thread name; returns NULL in the case of an error. 



## osThreadGetPriority\(\)<a name="ga0aeaf349604f456e68e78f9d3b42e44b"></a>

```
[osPriority_t](cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec) osThreadGetPriority ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Gets the prority of an active thread. 

**Parameters:**

<a name="table1796944233090250"></a>
<table><thead align="left"><tr id="row586034801090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p46914137090250"><a name="p46914137090250"></a><a name="p46914137090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1807238685090250"><a name="p1807238685090250"></a><a name="p1807238685090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row354642238090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the prority of the thread. 



## osThreadGetStackSize\(\)<a name="gab9f8bd715d671c6ee27644867bc1bf65"></a>

```
uint32_t osThreadGetStackSize ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Obtains the stack size of a thread. 

**Parameters:**

<a name="table1024311213090250"></a>
<table><thead align="left"><tr id="row1865138433090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2082386064090250"><a name="p2082386064090250"></a><a name="p2082386064090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p856770238090250"><a name="p856770238090250"></a><a name="p856770238090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row483331174090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the stack size, in bytes; returns 0 in the case of an error. 



## osThreadGetStackSpace\(\)<a name="ga9c83bd5dd8de329701775d6ef7012720"></a>

```
uint32_t osThreadGetStackSpace ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Obtains the size of the available stack space for a thread based on the stack watermark. 

**Parameters:**

<a name="table2067294041090250"></a>
<table><thead align="left"><tr id="row1582402804090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p937742614090250"><a name="p937742614090250"></a><a name="p937742614090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p748184145090250"><a name="p748184145090250"></a><a name="p748184145090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1329918249090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the available stack size, in bytes; returns 0 in the case of an error. 



## osThreadGetState\(\)<a name="gacc0a98b42f0a5928e12dc91dc76866b9"></a>

```
[osThreadState_t](cmsis.md#gad3dc89e942e38d9f3af858a0269a820d) osThreadGetState ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Obtains the state of a thread. 

**Parameters:**

<a name="table918110875090250"></a>
<table><thead align="left"><tr id="row248386032090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298912320090250"><a name="p1298912320090250"></a><a name="p1298912320090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p179294442090250"><a name="p179294442090250"></a><a name="p179294442090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row429567008090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the thread state. 



## osThreadNew\(\)<a name="ga48d68b8666d99d28fa646ee1d2182b8f"></a>

```
[osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) osThreadNew ([osThreadFunc_t](cmsis.md#ga8ef2773ed8ef63ab8727e0d06ebec4d2) func, void * argument, const [osThreadAttr_t](osthreadattr_t.md) * attr )
```

 **Description:**

Creates an active thread. 

**Parameters:**

<a name="table1104619028090250"></a>
<table><thead align="left"><tr id="row67672876090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p135191572090250"><a name="p135191572090250"></a><a name="p135191572090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1838413252090250"><a name="p1838413252090250"></a><a name="p1838413252090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1510010898090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry of the thread callback function. </td>
</tr>
<tr id="row8286384090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">argument</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the argument passed to the thread. </td>
</tr>
<tr id="row1414551701090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread attributes. If this parameter is left unspecified, the default value 0 is used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the thread ID; returns NULL in the case of an error. 



## osThreadResume\(\)<a name="ga3dbad90eff394b02de76a452c84c5d80"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osThreadResume ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Resumes a thread from the suspended state. 

**Parameters:**

<a name="table126728395090250"></a>
<table><thead align="left"><tr id="row93628991090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p987958195090250"><a name="p987958195090250"></a><a name="p987958195090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p746440014090250"><a name="p746440014090250"></a><a name="p746440014090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row49523736090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osThreadSetPriority\(\)<a name="ga861a420fb2d643115b06622903fb3bfb"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osThreadSetPriority ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id, [osPriority_t](cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec) priority )
```

 **Description:**

Changes the priority of a thread. 

**Parameters:**

<a name="table907907725090250"></a>
<table><thead align="left"><tr id="row1788192042090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p850949359090250"><a name="p850949359090250"></a><a name="p850949359090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p116247759090250"><a name="p116247759090250"></a><a name="p116247759090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1783266888090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
<tr id="row1330858165090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the new priority. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osThreadSuspend\(\)<a name="gaa9de419d0152bf77e9bbcd1f369fb990"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osThreadSuspend ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Suspends a thread. 

**Parameters:**

<a name="table1024430904090250"></a>
<table><thead align="left"><tr id="row941335982090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1697028751090250"><a name="p1697028751090250"></a><a name="p1697028751090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1786898581090250"><a name="p1786898581090250"></a><a name="p1786898581090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1104043820090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osThreadTerminate\(\)<a name="ga2f8ba6dba6e9c065a6e236ffd410d74a"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osThreadTerminate ([osThreadId_t](cmsis.md#ga6333e016ba9b008e6dd76851c38b9217) thread_id)
```

 **Description:**

Terminates a thread. 

**Parameters:**

<a name="table33429937090250"></a>
<table><thead align="left"><tr id="row206416627090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1825242644090250"><a name="p1825242644090250"></a><a name="p1825242644090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1663905466090250"><a name="p1663905466090250"></a><a name="p1663905466090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1625255683090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osThreadYield\(\)<a name="gad01c7ec26535b1de6b018bb9466720e2"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osThreadYield (void )
```

 **Description:**

Sets the currently running thread to the ready state. 

**Returns:**

Returns the CMSIS-RTOS running result. 



## osTimerDelete\(\)<a name="gad0001dd74721ab461789324806db2453"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osTimerDelete ([osTimerId_t](cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44) timer_id)
```

 **Description:**

Deletes a timer. 

**Parameters:**

<a name="table1855307599090250"></a>
<table><thead align="left"><tr id="row2012919331090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1874403191090250"><a name="p1874403191090250"></a><a name="p1874403191090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p900202213090250"><a name="p900202213090250"></a><a name="p900202213090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2145132946090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer ID, which is obtained using osTimerNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osTimerIsRunning\(\)<a name="ga69d3589f54194022c30dd01e45ec6741"></a>

```
uint32_t osTimerIsRunning ([osTimerId_t](cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44) timer_id)
```

 **Description:**

Checks whether a timer is running. 

**Parameters:**

<a name="table1249657744090250"></a>
<table><thead align="left"><tr id="row1759762738090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p93950339090250"><a name="p93950339090250"></a><a name="p93950339090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1216989625090250"><a name="p1216989625090250"></a><a name="p1216989625090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row342776617090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer ID, which is obtained using osTimerNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns 1 if the timer is running; returns 0 otherwise. 



## osTimerNew\(\)<a name="gad4e7f785c5f700a509f55a3bf6a62bec"></a>

```
[osTimerId_t](cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44) osTimerNew ([osTimerFunc_t](cmsis.md#ga77a298218f3c8382b39a09a6d134d040) func, [osTimerType_t](cmsis.md#ga7dc24a4c2b90334427081c3da7a71915) type, void * argument, const [osTimerAttr_t](ostimerattr_t.md) * attr )
```

 **Description:**

Creates and initializes a timer. 

**Parameters:**

<a name="table834700017090250"></a>
<table><thead align="left"><tr id="row1391056361090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1865770903090250"><a name="p1865770903090250"></a><a name="p1865770903090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1008329186090250"><a name="p1008329186090250"></a><a name="p1008329186090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row842028008090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the entry of the timer callback function. </td>
</tr>
<tr id="row1255106031090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer type. </td>
</tr>
<tr id="row502244194090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">argument</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the argument used in timer callback. </td>
</tr>
<tr id="row690185014090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer attributes. This parameter is not used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the timer ID; returns NULL in the case of an error. 



## osTimerStart\(\)<a name="gab6ee2859ea657641b7adfac599b8121d"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osTimerStart ([osTimerId_t](cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44) timer_id, uint32_t ticks )
```

 **Description:**

Starts or restarts a timer. 

**Parameters:**

<a name="table1989770748090250"></a>
<table><thead align="left"><tr id="row1549368165090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1137767950090250"><a name="p1137767950090250"></a><a name="p1137767950090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1800929222090250"><a name="p1800929222090250"></a><a name="p1800929222090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row382963052090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer ID, which is obtained using osTimerNew. </td>
</tr>
<tr id="row653838117090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ticks</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of ticks since the timer starts running. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## osTimerStop\(\)<a name="gabd7a89356da7717293eb0bc5d87b8ac9"></a>

```
[osStatus_t](cmsis.md#ga6c0dbe6069e4e7f47bb4cd32ae2b813e) osTimerStop ([osTimerId_t](cmsis.md#gac2000ac2a8c6740700fd8e6c938cff44) timer_id)
```

 **Description:**

Stops a timer. 

**Parameters:**

<a name="table877670763090250"></a>
<table><thead align="left"><tr id="row1015014242090250"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1124648543090250"><a name="p1124648543090250"></a><a name="p1124648543090250"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p229636292090250"><a name="p229636292090250"></a><a name="p229636292090250"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2009679290090250"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer_id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer ID, which is obtained using osTimerNew. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the CMSIS-RTOS running result. 



## **Variable Documentation**<a name="section1557605127090250"></a>

## api<a name="ga399e0292985f12145a0e61c0b50a50ec"></a>

```
uint32_t osVersion_t::api
```

 **Description:**

API version 

## attr\_bits \[1/6\]<a name="ga5f48a821ddc41410fe625860b6380d3a"></a>

```
uint32_t osThreadAttr_t::attr_bits
```

 **Description:**

Thread attribute bits 

## attr\_bits \[2/6\]<a name="ga7701a75e9afe37e9bd46bb5626e17759"></a>

```
uint32_t osTimerAttr_t::attr_bits
```

 **Description:**

Reserved attribute bits 

## attr\_bits \[3/6\]<a name="ga7aabb3ae376079d34ddd78787733ca5c"></a>

```
uint32_t osEventFlagsAttr_t::attr_bits
```

 **Description:**

Reserved attribute bits 

## attr\_bits \[4/6\]<a name="ga9dbf080ff04a6e5fde40b8e962868fd5"></a>

```
uint32_t osMutexAttr_t::attr_bits
```

 **Description:**

Reserved attribute bits 

## attr\_bits \[5/6\]<a name="ga718a87b56a768a4f358a90f8c09b1aab"></a>

```
uint32_t osSemaphoreAttr_t::attr_bits
```

 **Description:**

Reserved attribute bits 

## attr\_bits \[6/6\]<a name="ga89d1d6bc8c5926f764c0c915f7fc04e5"></a>

```
uint32_t osMessageQueueAttr_t::attr_bits
```

 **Description:**

Reserved attribute bits 

## cb\_mem \[1/6\]<a name="ga378962e098d6fc89cd0bdecaf03b59de"></a>

```
void* osThreadAttr_t::cb_mem
```

 **Description:**

Memory for the thread control block 

## cb\_mem \[2/6\]<a name="ga2a7f8245862c91afe08d0c671ded2fd3"></a>

```
void* osTimerAttr_t::cb_mem
```

 **Description:**

Memory for the timer control block 

## cb\_mem \[3/6\]<a name="gadbcc8550d7f5129aacb083ac773874e4"></a>

```
void* osEventFlagsAttr_t::cb_mem
```

 **Description:**

Memory for the event control block 

## cb\_mem \[4/6\]<a name="gafb6e0bd20375f3ebc1cca487b9c01799"></a>

```
void* osMutexAttr_t::cb_mem
```

 **Description:**

Memory for the mutex control block 

## cb\_mem \[5/6\]<a name="gadcabe022804af99fc5a4477dd95c8003"></a>

```
void* osSemaphoreAttr_t::cb_mem
```

 **Description:**

Memory for the semaphore control block 

## cb\_mem \[6/6\]<a name="gad3452e2c35fbdccbedfc88781ad16059"></a>

```
void* osMessageQueueAttr_t::cb_mem
```

 **Description:**

Memory for the message queue control block 

## cb\_size \[1/6\]<a name="ga8992f7ce1ac52bb8682ccd4f42751de5"></a>

```
uint32_t osThreadAttr_t::cb_size
```

 **Description:**

Size of the memory for the thread control block 

## cb\_size \[2/6\]<a name="gaa5c0dc5e54b430c01ca3d212a44e31fb"></a>

```
uint32_t osTimerAttr_t::cb_size
```

 **Description:**

Size of the memory for the timer control block 

## cb\_size \[3/6\]<a name="ga93ff7c1bc7cb7508e817b83169dc5840"></a>

```
uint32_t osEventFlagsAttr_t::cb_size
```

 **Description:**

Size of the memory for the event control block 

## cb\_size \[4/6\]<a name="ga444c834a2336196cc87b200cbd33106c"></a>

```
uint32_t osMutexAttr_t::cb_size
```

 **Description:**

Size of the memory for the mutex control block 

## cb\_size \[5/6\]<a name="gaa674886431b3111d252bb90b6f911d32"></a>

```
uint32_t osSemaphoreAttr_t::cb_size
```

 **Description:**

Size of the memory for the semaphore control block 

## cb\_size \[6/6\]<a name="gaf027a158b586c5064006bba6f965b8fa"></a>

```
uint32_t osMessageQueueAttr_t::cb_size
```

 **Description:**

Size of the memory for the message queue control block 

## kernel<a name="ga3a589e0cc665071abb720afda12e9a15"></a>

```
uint32_t osVersion_t::kernel
```

 **Description:**

Kernel version 

## mq\_mem<a name="gaf1492738958bf4a44c90d96a08d34a57"></a>

```
void* osMessageQueueAttr_t::mq_mem
```

 **Description:**

Memory for storing data in the message queue 

## mq\_size<a name="gadec49e7e57147aed14e83bd99cf2c6d7"></a>

```
uint32_t osMessageQueueAttr_t::mq_size
```

 **Description:**

Size of the memory for storing data in the message queue 

## name \[1/6\]<a name="gaed20d9f112c97dcb4fc6374290ab7446"></a>

```
const char* osThreadAttr_t::name
```

 **Description:**

Thread name 

## name \[2/6\]<a name="ga2b432a32e222f51f5c3ed37db14a2db5"></a>

```
const char* osTimerAttr_t::name
```

 **Description:**

Timer name 

## name \[3/6\]<a name="gac3d95d16f3eed79d9e068567acb2b0d4"></a>

```
const char* osEventFlagsAttr_t::name
```

 **Description:**

Event name 

## name \[4/6\]<a name="gaf3997dba664ce0e0f788a35e8f473a4d"></a>

```
const char* osMutexAttr_t::name
```

 **Description:**

Mutex name 

## name \[5/6\]<a name="ga0151928f02ecbbc0a22793a63892af66"></a>

```
const char* osSemaphoreAttr_t::name
```

 **Description:**

Semaphore name 

## name \[6/6\]<a name="ga7a0ddc31f97f8d8e5d9f880f5d03768b"></a>

```
const char* osMessageQueueAttr_t::name
```

 **Description:**

Message queue name 

## priority<a name="ga90ae74b20698ee175b68f7f53a0b9091"></a>

```
[osPriority_t](cmsis.md#gad4e3e0971b41f2d17584a8c6837342ec) osThreadAttr_t::priority
```

 **Description:**

Thread priority 

## reserved<a name="ga553fd9961d8f9e4562f84cd68709ae2d"></a>

```
uint32_t osThreadAttr_t::reserved
```

 **Description:**

Reserved 

## stack\_mem<a name="ga8ce05e5336d40cba01b6e1d1e36afe77"></a>

```
void* osThreadAttr_t::stack_mem
```

 **Description:**

Memory for the thread stack 

## stack\_size<a name="gacb537dae7fecd9c744852ff6d6ea2c04"></a>

```
uint32_t osThreadAttr_t::stack_size
```

 **Description:**

Size of the thread stack 

## tz\_module<a name="ga5cefc38447dae2c9f3fb81c193c49536"></a>

```
[TZ_ModuleId_t](cmsis.md#gad5ef21485fe5f60263bc0b48006202cb) osThreadAttr_t::tz_module
```

 **Description:**

TrustZone module of the thread 

