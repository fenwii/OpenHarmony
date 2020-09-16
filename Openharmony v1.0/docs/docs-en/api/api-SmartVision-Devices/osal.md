# OSAL<a name="EN-US_TOPIC_0000001054799547"></a>

## **Overview**<a name="section1167366392093521"></a>

Defines the structures and interfaces for the Operating System Abstraction Layer \(OSAL\) module. 

The OSAL module harmonizes OS interface differences and provides unified OS interfaces externally, including the memory management, thread, mutex, spinlock, semaphore, timer, file, interrupt, time, atomic, firmware, and I/O operation modules.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1525733174093521"></a>

## Files<a name="files"></a>

<a name="table1519828879093521"></a>
<table><thead align="left"><tr id="row1957561272093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1027321041093521"><a name="p1027321041093521"></a><a name="p1027321041093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p160064208093521"><a name="p160064208093521"></a><a name="p160064208093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1448127181093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1562378761093521"><a name="p1562378761093521"></a><a name="p1562378761093521"></a><a href="osal_atomic-h.md">osal_atomic.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397062109093521"><a name="p397062109093521"></a><a name="p397062109093521"></a>Declares atomic and bit operation interfaces. </p>
</td>
</tr>
<tr id="row1778451130093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1556238976093521"><a name="p1556238976093521"></a><a name="p1556238976093521"></a><a href="osal_file-h.md">osal_file.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728133180093521"><a name="p728133180093521"></a><a name="p728133180093521"></a>Declares the file structures and interfaces. </p>
</td>
</tr>
<tr id="row2135453724093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906170330093521"><a name="p1906170330093521"></a><a name="p1906170330093521"></a><a href="osal_firmware-h.md">osal_firmware.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1136936493093521"><a name="p1136936493093521"></a><a name="p1136936493093521"></a>Declares firmware structures and interfaces. </p>
</td>
</tr>
<tr id="row1576088275093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550123077093521"><a name="p550123077093521"></a><a name="p550123077093521"></a><a href="osal_io-h.md">osal_io.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386617071093521"><a name="p386617071093521"></a><a name="p386617071093521"></a>Declares I/O interfaces. </p>
</td>
</tr>
<tr id="row1562211690093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1736086569093521"><a name="p1736086569093521"></a><a name="p1736086569093521"></a><a href="osal_irq-h.md">osal_irq.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71642327093521"><a name="p71642327093521"></a><a name="p71642327093521"></a>Declares interrupt request (IRQ) interfaces and common IRQ trigger modes. </p>
</td>
</tr>
<tr id="row915959705093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1158382923093521"><a name="p1158382923093521"></a><a name="p1158382923093521"></a><a href="osal_mem-h.md">osal_mem.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p230579362093521"><a name="p230579362093521"></a><a name="p230579362093521"></a>Declares the driver memory request and release interfaces. </p>
</td>
</tr>
<tr id="row1927898337093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p746579599093521"><a name="p746579599093521"></a><a name="p746579599093521"></a><a href="osal_mutex-h.md">osal_mutex.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p942120266093521"><a name="p942120266093521"></a><a name="p942120266093521"></a>Declares mutex types and interfaces. </p>
</td>
</tr>
<tr id="row1016999170093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p693111868093521"><a name="p693111868093521"></a><a name="p693111868093521"></a><a href="osal_sem-h.md">osal_sem.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567991610093521"><a name="p1567991610093521"></a><a name="p1567991610093521"></a>Declares semaphore structures and interfaces. </p>
</td>
</tr>
<tr id="row1314441322093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557150838093521"><a name="p557150838093521"></a><a name="p557150838093521"></a><a href="osal_spinlock-h.md">osal_spinlock.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1397483652093521"><a name="p1397483652093521"></a><a name="p1397483652093521"></a>Declares spinlock types and interfaces. </p>
</td>
</tr>
<tr id="row1192844052093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p782280836093521"><a name="p782280836093521"></a><a name="p782280836093521"></a><a href="osal_thread-h.md">osal_thread.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492764140093521"><a name="p1492764140093521"></a><a name="p1492764140093521"></a>Declares thread types and interfaces. </p>
</td>
</tr>
<tr id="row885620621093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1690634524093521"><a name="p1690634524093521"></a><a name="p1690634524093521"></a><a href="osal_time-h.md">osal_time.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1777452489093521"><a name="p1777452489093521"></a><a name="p1777452489093521"></a>Declares the time, sleep, and delay interfaces. </p>
</td>
</tr>
<tr id="row1191373894093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410474093521"><a name="p410474093521"></a><a name="p410474093521"></a><a href="osal_timer-h.md">osal_timer.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1502452439093521"><a name="p1502452439093521"></a><a name="p1502452439093521"></a>Declares timer types and interfaces. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table658648026093521"></a>
<table><thead align="left"><tr id="row636171014093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1349539313093521"><a name="p1349539313093521"></a><a name="p1349539313093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2035613669093521"><a name="p2035613669093521"></a><a name="p2035613669093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row753446695093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381119698093521"><a name="p381119698093521"></a><a name="p381119698093521"></a><a href="osalatomic.md">OsalAtomic</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315294670093521"><a name="p315294670093521"></a><a name="p315294670093521"></a>Describes an atomic. </p>
</td>
</tr>
<tr id="row1004888215093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1996697722093521"><a name="p1996697722093521"></a><a name="p1996697722093521"></a><a href="osalfile.md">OsalFile</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167170260093521"><a name="p1167170260093521"></a><a name="p1167170260093521"></a>Declares a file type. </p>
</td>
</tr>
<tr id="row1557217912093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091392714093521"><a name="p1091392714093521"></a><a name="p1091392714093521"></a><a href="osalfirmware.md">OsalFirmware</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564907708093521"><a name="p564907708093521"></a><a name="p564907708093521"></a>Defines the data structure for operating a firmware file. </p>
</td>
</tr>
<tr id="row1434543186093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069589120093521"><a name="p2069589120093521"></a><a name="p2069589120093521"></a><a href="osalfwblock.md">OsalFwBlock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1009544200093521"><a name="p1009544200093521"></a><a name="p1009544200093521"></a>Defines the data structure for reading a firmware file. </p>
</td>
</tr>
<tr id="row147511763093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376572675093521"><a name="p1376572675093521"></a><a name="p1376572675093521"></a><a href="osalmutex.md">OsalMutex</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p185598030093521"><a name="p185598030093521"></a><a name="p185598030093521"></a>Describes a mutex. </p>
</td>
</tr>
<tr id="row133903255093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p808307518093521"><a name="p808307518093521"></a><a name="p808307518093521"></a><a href="osalsem.md">OsalSem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p292497565093521"><a name="p292497565093521"></a><a name="p292497565093521"></a>Describes a semaphore. </p>
</td>
</tr>
<tr id="row11065192093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205088945093521"><a name="p205088945093521"></a><a name="p205088945093521"></a><a href="osalspinlock.md">OsalSpinlock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1140593164093521"><a name="p1140593164093521"></a><a name="p1140593164093521"></a>Describes a spinlock. </p>
</td>
</tr>
<tr id="row689360168093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844153764093521"><a name="p844153764093521"></a><a name="p844153764093521"></a><a href="osalthreadparam.md">OsalThreadParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452882852093521"><a name="p1452882852093521"></a><a name="p1452882852093521"></a>Describes thread parameters. </p>
</td>
</tr>
<tr id="row1323696451093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p938909435093521"><a name="p938909435093521"></a><a name="p938909435093521"></a><a href="osalthread.md">OsalThread</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p285122683093521"><a name="p285122683093521"></a><a name="p285122683093521"></a>Describes a thread. </p>
</td>
</tr>
<tr id="row2030350719093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1756976892093521"><a name="p1756976892093521"></a><a name="p1756976892093521"></a><a href="osaltimespec.md">OsalTimespec</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2054360779093521"><a name="p2054360779093521"></a><a name="p2054360779093521"></a>Defines time. </p>
</td>
</tr>
<tr id="row953465334093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2141528254093521"><a name="p2141528254093521"></a><a name="p2141528254093521"></a><a href="osaltimer.md">OsalTimer</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p762796336093521"><a name="p762796336093521"></a><a name="p762796336093521"></a>Describes a timer. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table463975062093521"></a>
<table><thead align="left"><tr id="row1633621838093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1998814527093521"><a name="p1998814527093521"></a><a name="p1998814527093521"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1177597075093521"><a name="p1177597075093521"></a><a name="p1177597075093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1467886239093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p163416110093521"><a name="p163416110093521"></a><a name="p163416110093521"></a><em id="gab208afeed35dd98f6a0ccf807e9c722d"><a name="gab208afeed35dd98f6a0ccf807e9c722d"></a><a name="gab208afeed35dd98f6a0ccf807e9c722d"></a></em>OSAL_O_RD_ONLY    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1553655489093521"><a name="p1553655489093521"></a><a name="p1553655489093521"></a>Opens a file in read-only mode. </p>
</td>
</tr>
<tr id="row491937594093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813264446093521"><a name="p813264446093521"></a><a name="p813264446093521"></a><em id="ga1e37c3fb82a2bcff729f97478bc28f81"><a name="ga1e37c3fb82a2bcff729f97478bc28f81"></a><a name="ga1e37c3fb82a2bcff729f97478bc28f81"></a></em>OSAL_O_WR_ONLY    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2067716207093521"><a name="p2067716207093521"></a><a name="p2067716207093521"></a>Opens a file in write-only mode. </p>
</td>
</tr>
<tr id="row1439971061093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p854926280093521"><a name="p854926280093521"></a><a name="p854926280093521"></a><em id="gabac6ceec2cb877ae0c4c0c89f2e13451"><a name="gabac6ceec2cb877ae0c4c0c89f2e13451"></a><a name="gabac6ceec2cb877ae0c4c0c89f2e13451"></a></em>OSAL_O_RDWR    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1280174862093521"><a name="p1280174862093521"></a><a name="p1280174862093521"></a>Opens a file in read and write mode. </p>
</td>
</tr>
<tr id="row130933157093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414217746093521"><a name="p414217746093521"></a><a name="p414217746093521"></a><em id="ga9cb465f6d142e859258e14199702906e"><a name="ga9cb465f6d142e859258e14199702906e"></a><a name="ga9cb465f6d142e859258e14199702906e"></a></em>OSAL_S_IREAD    00400</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p797145506093521"><a name="p797145506093521"></a><a name="p797145506093521"></a>Defines the read permission for the owner. </p>
</td>
</tr>
<tr id="row127428305093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1128577146093521"><a name="p1128577146093521"></a><a name="p1128577146093521"></a><em id="gaf93f6ab3441029a84b5f04904daf68be"><a name="gaf93f6ab3441029a84b5f04904daf68be"></a><a name="gaf93f6ab3441029a84b5f04904daf68be"></a></em>OSAL_S_IWRITE    00200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262579946093521"><a name="p262579946093521"></a><a name="p262579946093521"></a>Defines the write permission for the owner. </p>
</td>
</tr>
<tr id="row427153894093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886163224093521"><a name="p1886163224093521"></a><a name="p1886163224093521"></a><em id="gaa168a8495f19631b9d4de6e5da688e26"><a name="gaa168a8495f19631b9d4de6e5da688e26"></a><a name="gaa168a8495f19631b9d4de6e5da688e26"></a></em>OSAL_S_IEXEC    00100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p30532715093521"><a name="p30532715093521"></a><a name="p30532715093521"></a>Defines the execution permission for the owner. </p>
</td>
</tr>
<tr id="row1548675487093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292958281093521"><a name="p1292958281093521"></a><a name="p1292958281093521"></a><em id="ga008dcb6a04b63ef620c25aa5b41f211a"><a name="ga008dcb6a04b63ef620c25aa5b41f211a"></a><a name="ga008dcb6a04b63ef620c25aa5b41f211a"></a></em>OSAL_S_IRGRP    00040</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870126568093521"><a name="p1870126568093521"></a><a name="p1870126568093521"></a>Defines the read permission for the group. </p>
</td>
</tr>
<tr id="row210321654093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p86680955093521"><a name="p86680955093521"></a><a name="p86680955093521"></a><em id="ga982f1e009c6caeb8060e6442a866803f"><a name="ga982f1e009c6caeb8060e6442a866803f"></a><a name="ga982f1e009c6caeb8060e6442a866803f"></a></em>OSAL_S_IWGRP    00020</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p538149674093521"><a name="p538149674093521"></a><a name="p538149674093521"></a>Defines the write permission for the group. </p>
</td>
</tr>
<tr id="row626093708093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118885749093521"><a name="p2118885749093521"></a><a name="p2118885749093521"></a><em id="gaa1e6fa403fcd99229902e9a8cd98a74c"><a name="gaa1e6fa403fcd99229902e9a8cd98a74c"></a><a name="gaa1e6fa403fcd99229902e9a8cd98a74c"></a></em>OSAL_S_IXGRP    00010</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1879735875093521"><a name="p1879735875093521"></a><a name="p1879735875093521"></a>Defines the execution permission for the group. </p>
</td>
</tr>
<tr id="row134112858093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044141507093521"><a name="p1044141507093521"></a><a name="p1044141507093521"></a><em id="ga01e4a94482a048060c250d3d5d899cd6"><a name="ga01e4a94482a048060c250d3d5d899cd6"></a><a name="ga01e4a94482a048060c250d3d5d899cd6"></a></em>OSAL_S_IROTH    00004</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1769140605093521"><a name="p1769140605093521"></a><a name="p1769140605093521"></a>Defines the read permission for others. </p>
</td>
</tr>
<tr id="row1590223976093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1961224389093521"><a name="p1961224389093521"></a><a name="p1961224389093521"></a><em id="gaea63281bfbac42036bb549c2bda2d192"><a name="gaea63281bfbac42036bb549c2bda2d192"></a><a name="gaea63281bfbac42036bb549c2bda2d192"></a></em>OSAL_S_IWOTH    00002</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1675397441093521"><a name="p1675397441093521"></a><a name="p1675397441093521"></a>Defines the write permission for others. </p>
</td>
</tr>
<tr id="row1751150654093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881196345093521"><a name="p1881196345093521"></a><a name="p1881196345093521"></a><em id="ga9e308388be9855050060a87a93191d5e"><a name="ga9e308388be9855050060a87a93191d5e"></a><a name="ga9e308388be9855050060a87a93191d5e"></a></em>OSAL_S_IXOTH    00001</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1732959772093521"><a name="p1732959772093521"></a><a name="p1732959772093521"></a>Defines the execution permission for others. </p>
</td>
</tr>
<tr id="row1601621237093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370980362093521"><a name="p1370980362093521"></a><a name="p1370980362093521"></a><em id="ga110fc469c88e83828679a3dedb4b5f3d"><a name="ga110fc469c88e83828679a3dedb4b5f3d"></a><a name="ga110fc469c88e83828679a3dedb4b5f3d"></a></em>OSAL_SEEK_SET    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375450928093521"><a name="p1375450928093521"></a><a name="p1375450928093521"></a>Defines the offset from the file header. </p>
</td>
</tr>
<tr id="row2077290314093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1169596881093521"><a name="p1169596881093521"></a><a name="p1169596881093521"></a><em id="ga2ae6c04da45367479db0f914b250a0a7"><a name="ga2ae6c04da45367479db0f914b250a0a7"></a><a name="ga2ae6c04da45367479db0f914b250a0a7"></a></em>OSAL_SEEK_CUR    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491396965093521"><a name="p491396965093521"></a><a name="p491396965093521"></a>Defines the offset from the current position. </p>
</td>
</tr>
<tr id="row1373733346093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1711241290093521"><a name="p1711241290093521"></a><a name="p1711241290093521"></a><em id="gaf282e1e5207b934c0c71ce9558ac1940"><a name="gaf282e1e5207b934c0c71ce9558ac1940"></a><a name="gaf282e1e5207b934c0c71ce9558ac1940"></a></em>OSAL_SEEK_END    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1499124281093521"><a name="p1499124281093521"></a><a name="p1499124281093521"></a>Defines the offset from the end of the file. </p>
</td>
</tr>
<tr id="row536475216093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422599961093521"><a name="p422599961093521"></a><a name="p422599961093521"></a><a href="osal.md#ga48e1f404639550c229aee3ec35a06d79">OSAL_WRITEB</a>(value, address)   writeb(value, address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087992362093521"><a name="p2087992362093521"></a><a name="p2087992362093521"></a>Writes one byte of data into an I/O address space. </p>
</td>
</tr>
<tr id="row1129359856093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1021718635093521"><a name="p1021718635093521"></a><a name="p1021718635093521"></a><a href="osal.md#ga3358a86c6bbb6f02ab108964962f441f">OSAL_WRITEW</a>(value, address)   writew(value, address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p272734765093521"><a name="p272734765093521"></a><a name="p272734765093521"></a>Writes a short integer into an I/O address space. </p>
</td>
</tr>
<tr id="row190509432093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292452397093521"><a name="p1292452397093521"></a><a name="p1292452397093521"></a><a href="osal.md#gaba47d67efad3ad9d1a33a35d2982bd49">OSAL_WRITEL</a>(value, address)   writel(value, address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p730256030093521"><a name="p730256030093521"></a><a name="p730256030093521"></a>Writes an integer into an I/O address space. </p>
</td>
</tr>
<tr id="row142201821093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p397292517093521"><a name="p397292517093521"></a><a name="p397292517093521"></a><a href="osal.md#ga3de1529efbdabd4fb2f144c6f48df70b">OSAL_READB</a>(address)   readb(address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622737922093521"><a name="p1622737922093521"></a><a name="p1622737922093521"></a>Reads one byte of data from an I/O address space. </p>
</td>
</tr>
<tr id="row2087505900093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116635521093521"><a name="p2116635521093521"></a><a name="p2116635521093521"></a><a href="osal.md#ga8bd523f234f24415fe733addd113e60b">OSAL_READW</a>(address)   readw(address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2035681808093521"><a name="p2035681808093521"></a><a name="p2035681808093521"></a>Reads a short integer from an I/O address space. </p>
</td>
</tr>
<tr id="row1034108149093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841928077093521"><a name="p1841928077093521"></a><a name="p1841928077093521"></a><a href="osal.md#ga14ce14451b2484b2e268a38757237f41">OSAL_READL</a>(address)   readl(address)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698133086093521"><a name="p1698133086093521"></a><a name="p1698133086093521"></a>Reads an integer from an I/O address space. </p>
</td>
</tr>
<tr id="row120740086093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p747379029093521"><a name="p747379029093521"></a><a name="p747379029093521"></a><em id="ga63b1e9f0b9eacddc211f9a481c2597b3"><a name="ga63b1e9f0b9eacddc211f9a481c2597b3"></a><a name="ga63b1e9f0b9eacddc211f9a481c2597b3"></a></em>OSAL_DECLARE_MUTEX (mutex)   struct <a href="osalmutex.md">OsalMutex</a> mutex</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1649545459093521"><a name="p1649545459093521"></a><a name="p1649545459093521"></a>Defines a mutex. </p>
</td>
</tr>
<tr id="row977160869093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91638957093521"><a name="p91638957093521"></a><a name="p91638957093521"></a><em id="ga5e37d1f50835b70611517ad96146fc93"><a name="ga5e37d1f50835b70611517ad96146fc93"></a><a name="ga5e37d1f50835b70611517ad96146fc93"></a></em>OSAL_DECLARE_SEMAPHORE (sem)   struct <a href="osalsem.md">OsalSem</a> sem</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773330694093521"><a name="p773330694093521"></a><a name="p773330694093521"></a>Defines a semaphore. </p>
</td>
</tr>
<tr id="row895996063093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393964522093521"><a name="p1393964522093521"></a><a name="p1393964522093521"></a><em id="gad624af1547135d60073f38b7f31ad826"><a name="gad624af1547135d60073f38b7f31ad826"></a><a name="gad624af1547135d60073f38b7f31ad826"></a></em>OSAL_DECLARE_SPINLOCK (spinlock)   <a href="osalspinlock.md">OsalSpinlock</a> spinlock</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679827395093521"><a name="p679827395093521"></a><a name="p679827395093521"></a>Defines a spinlock. </p>
</td>
</tr>
<tr id="row351994179093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p11737002093521"><a name="p11737002093521"></a><a name="p11737002093521"></a><em id="ga6178591bdeb64df97a5232350cc9bc26"><a name="ga6178591bdeb64df97a5232350cc9bc26"></a><a name="ga6178591bdeb64df97a5232350cc9bc26"></a></em>OSAL_DECLARE_THREAD (thread)   struct <a href="osalthread.md">OsalThread</a> thread</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646282999093521"><a name="p1646282999093521"></a><a name="p1646282999093521"></a>Defines a thread macro. </p>
</td>
</tr>
<tr id="row988047457093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112951409093521"><a name="p112951409093521"></a><a name="p112951409093521"></a><em id="ga556360caa9ece72fcbbc6aef5fc648f1"><a name="ga556360caa9ece72fcbbc6aef5fc648f1"></a><a name="ga556360caa9ece72fcbbc6aef5fc648f1"></a></em>OSAL_DECLARE_TIMER (timer)   <a href="osaltimer.md">OsalTimer</a> timer</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1764512560093521"><a name="p1764512560093521"></a><a name="p1764512560093521"></a>Defines a timer macro. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1351677664093521"></a>
<table><thead align="left"><tr id="row1942236383093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2140281115093521"><a name="p2140281115093521"></a><a name="p2140281115093521"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p317355815093521"><a name="p317355815093521"></a><a name="p317355815093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row739594180093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873747904093521"><a name="p1873747904093521"></a><a name="p1873747904093521"></a><em id="gab671a9e177f622a98af9ca1bd93198eb"><a name="gab671a9e177f622a98af9ca1bd93198eb"></a><a name="gab671a9e177f622a98af9ca1bd93198eb"></a></em>OsalIRQHandle ) (uint32_t irqId, void *dev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1783715504093521"><a name="p1783715504093521"></a><a name="p1783715504093521"></a><strong id="b716826374"><a name="b716826374"></a><a name="b716826374"></a></strong> typedef uint32_t(* </p>
<p id="p1102523262093521"><a name="p1102523262093521"></a><a name="p1102523262093521"></a>Defines an IRQ type. </p>
</td>
</tr>
<tr id="row556189340093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106696390093521"><a name="p106696390093521"></a><a name="p106696390093521"></a><em id="ga21ea0f87d53e65ec86a424c532d688d8"><a name="ga21ea0f87d53e65ec86a424c532d688d8"></a><a name="ga21ea0f87d53e65ec86a424c532d688d8"></a></em>OsalThreadEntry ) (void *)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901362911093521"><a name="p1901362911093521"></a><a name="p1901362911093521"></a><strong id="b310830771"><a name="b310830771"></a><a name="b310830771"></a></strong> typedef int(* </p>
<p id="p461327713093521"><a name="p461327713093521"></a><a name="p461327713093521"></a>Defines a thread callback function type. </p>
</td>
</tr>
<tr id="row2136625364093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2141921801093521"><a name="p2141921801093521"></a><a name="p2141921801093521"></a><em id="gaf3e7a12075b25df5971049d8cd77c25c"><a name="gaf3e7a12075b25df5971049d8cd77c25c"></a><a name="gaf3e7a12075b25df5971049d8cd77c25c"></a></em>OsalTimerFunc ) (uintptr_t arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731697798093521"><a name="p731697798093521"></a><a name="p731697798093521"></a><strong id="b777349828"><a name="b777349828"></a><a name="b777349828"></a></strong> typedef void(* </p>
<p id="p183729995093521"><a name="p183729995093521"></a><a name="p183729995093521"></a>Describes a timer execution function type. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table191561054093521"></a>
<table><thead align="left"><tr id="row1265704839093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p911530553093521"><a name="p911530553093521"></a><a name="p911530553093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p132692918093521"><a name="p132692918093521"></a><a name="p132692918093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row563116796093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p487063107093521"><a name="p487063107093521"></a><a name="p487063107093521"></a><a href="osal.md#ga78cd126b10424753db6f39f9b72ea124">OSAL_IRQ_TRIGGER_MODE</a> {   <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124aa0252cbf1f560b1d9951da4dfe896a1d">OSAL_IRQF_TRIGGER_NONE</a> = 0, <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124ab98297946a624d99a3fad6adac899f2c">OSAL_IRQF_TRIGGER_RISING</a> = 1, <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124a3088c6875fb44d05fd3a64a3d158295b">OSAL_IRQF_TRIGGER_FALLING</a> = 2, <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124a9a997189554c568f66dd994a9f9e203d">OSAL_IRQF_TRIGGER_HIGH</a> = 4,   <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124a7768ec0b5be5e88cfeb07dea96cd5865">OSAL_IRQF_TRIGGER_LOW</a> = 8 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1334153131093521"><a name="p1334153131093521"></a><a name="p1334153131093521"></a>Enumerates interrupt trigger modes. </p>
</td>
</tr>
<tr id="row2123971910093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p590998807093521"><a name="p590998807093521"></a><a name="p590998807093521"></a><a href="osal.md#gab8c099a9c39fdde73c74b3f7367be5d0">OSAL_THREAD_PRIORITY</a> { <a href="osal.md#ggab8c099a9c39fdde73c74b3f7367be5d0a077e53412997ddef962069a7cea4def6">OSAL_THREAD_PRI_LOW</a>, <a href="osal.md#ggab8c099a9c39fdde73c74b3f7367be5d0abc9ef48a9fc95f359a5c4d52041111e5">OSAL_THREAD_PRI_DEFAULT</a>, <a href="osal.md#ggab8c099a9c39fdde73c74b3f7367be5d0a61697eda5c5265d6d62271d00c098121">OSAL_THREAD_PRI_HIGH</a>, <a href="osal.md#ggab8c099a9c39fdde73c74b3f7367be5d0a9e66435e6d967adc68606b359a8753bd">OSAL_THREAD_PRI_HIGHEST</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58717288093521"><a name="p58717288093521"></a><a name="p58717288093521"></a>Enumerates thread priorities. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table471981625093521"></a>
<table><thead align="left"><tr id="row1648845833093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1161090949093521"><a name="p1161090949093521"></a><a name="p1161090949093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1127140004093521"><a name="p1127140004093521"></a><a name="p1127140004093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row187947931093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p865618346093521"><a name="p865618346093521"></a><a name="p865618346093521"></a><a href="osal.md#gaf7b7a860f5cf11bda3008ce16a5d79d5">OsalAtomicRead</a> (const <a href="osalatomic.md">OsalAtomic</a> *v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021098092093521"><a name="p2021098092093521"></a><a name="p2021098092093521"></a>int32_t </p>
<p id="p443417909093521"><a name="p443417909093521"></a><a name="p443417909093521"></a>Reads the counter of an atomic. </p>
</td>
</tr>
<tr id="row160953579093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1922839697093521"><a name="p1922839697093521"></a><a name="p1922839697093521"></a><a href="osal.md#ga0b82ac10305c7ec5ae46707034b866c3">OsalAtomicSet</a> (<a href="osalatomic.md">OsalAtomic</a> *v, int32_t counter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053247470093521"><a name="p2053247470093521"></a><a name="p2053247470093521"></a>void </p>
<p id="p1047715123093521"><a name="p1047715123093521"></a><a name="p1047715123093521"></a>Sets the counter for an atomic. </p>
</td>
</tr>
<tr id="row2105206754093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1793260186093521"><a name="p1793260186093521"></a><a name="p1793260186093521"></a><a href="osal.md#ga11214c11a9b875cb8ba0a67aeccc6ac9">OsalAtomicInc</a> (<a href="osalatomic.md">OsalAtomic</a> *v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025227316093521"><a name="p2025227316093521"></a><a name="p2025227316093521"></a>void </p>
<p id="p2058509249093521"><a name="p2058509249093521"></a><a name="p2058509249093521"></a>Increments the counter of an atomic by 1. </p>
</td>
</tr>
<tr id="row770634500093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p71785886093521"><a name="p71785886093521"></a><a name="p71785886093521"></a><a href="osal.md#gaa411f380e6b21c8467260030ceee38ff">OsalAtomicDec</a> (<a href="osalatomic.md">OsalAtomic</a> *v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1963687192093521"><a name="p1963687192093521"></a><a name="p1963687192093521"></a>void </p>
<p id="p547315889093521"><a name="p547315889093521"></a><a name="p547315889093521"></a>Decrements the counter of an atomic by 1. </p>
</td>
</tr>
<tr id="row682761196093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395442555093521"><a name="p1395442555093521"></a><a name="p1395442555093521"></a><a href="osal.md#gaf02c15a3593cac4add3f661b63aebf81">OsalTestBit</a> (unsigned long nr, const volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005994301093521"><a name="p2005994301093521"></a><a name="p2005994301093521"></a>int32_t </p>
<p id="p1593866348093521"><a name="p1593866348093521"></a><a name="p1593866348093521"></a>Tests the value of a specified bit of a variable. </p>
</td>
</tr>
<tr id="row209962624093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453712700093521"><a name="p453712700093521"></a><a name="p453712700093521"></a><a href="osal.md#gac0ff99812a327a4a595802a23b41b46f">OsalTestSetBit</a> (unsigned long nr, volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p610893619093521"><a name="p610893619093521"></a><a name="p610893619093521"></a>int32_t </p>
<p id="p1202640225093521"><a name="p1202640225093521"></a><a name="p1202640225093521"></a>Sets the value of a specified bit of the variable and returns the bit value before the setting. </p>
</td>
</tr>
<tr id="row1677275655093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1783658951093521"><a name="p1783658951093521"></a><a name="p1783658951093521"></a><a href="osal.md#ga8665e70c704921f443fd2db8193ff7cc">OsalTestClearBit</a> (unsigned long nr, volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1839115508093521"><a name="p1839115508093521"></a><a name="p1839115508093521"></a>int32_t </p>
<p id="p1119201179093521"><a name="p1119201179093521"></a><a name="p1119201179093521"></a>Clears the value of a specified bit of the variable and returns the bit value before clearing. </p>
</td>
</tr>
<tr id="row389514992093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1920803488093521"><a name="p1920803488093521"></a><a name="p1920803488093521"></a><a href="osal.md#gae3e5b84f326aa1a2c4b8427509f80cd9">OsalClearBit</a> (unsigned long nr, volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997439616093521"><a name="p1997439616093521"></a><a name="p1997439616093521"></a>void </p>
<p id="p170516528093521"><a name="p170516528093521"></a><a name="p170516528093521"></a>Clears the value of a specified bit of the variable. </p>
</td>
</tr>
<tr id="row1283973962093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883074222093521"><a name="p883074222093521"></a><a name="p883074222093521"></a><a href="osal.md#ga6707125b6ac5e13912a181877f18f292">OsalFileOpen</a> (<a href="osalfile.md">OsalFile</a> *file, const char *path, int flags, uint32_t rights)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1170370713093521"><a name="p1170370713093521"></a><a name="p1170370713093521"></a>int32_t </p>
<p id="p987592502093521"><a name="p987592502093521"></a><a name="p987592502093521"></a>Opens a file. </p>
</td>
</tr>
<tr id="row174747714093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377879559093521"><a name="p1377879559093521"></a><a name="p1377879559093521"></a><a href="osal.md#ga305f575f875ff26bb907c67c23dfb16a">OsalFileWrite</a> (<a href="osalfile.md">OsalFile</a> *file, const void *string, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1494041655093521"><a name="p1494041655093521"></a><a name="p1494041655093521"></a>ssize_t </p>
<p id="p382634434093521"><a name="p382634434093521"></a><a name="p382634434093521"></a>Writes a file. </p>
</td>
</tr>
<tr id="row1826141322093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1374626857093521"><a name="p1374626857093521"></a><a name="p1374626857093521"></a><a href="osal.md#ga8786ab2baa8669e79173ab7ab47d67bb">OsalFileClose</a> (<a href="osalfile.md">OsalFile</a> *file)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1988412310093521"><a name="p1988412310093521"></a><a name="p1988412310093521"></a>void </p>
<p id="p1985925639093521"><a name="p1985925639093521"></a><a name="p1985925639093521"></a>Closes a file. </p>
</td>
</tr>
<tr id="row688431177093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1174244412093521"><a name="p1174244412093521"></a><a name="p1174244412093521"></a><a href="osal.md#gac8ebc8dc4b9ce9725875868f69fd17a8">OsalFileRead</a> (<a href="osalfile.md">OsalFile</a> *file, void *buf, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2129972886093521"><a name="p2129972886093521"></a><a name="p2129972886093521"></a>ssize_t </p>
<p id="p1139880225093521"><a name="p1139880225093521"></a><a name="p1139880225093521"></a>Reads a file. </p>
</td>
</tr>
<tr id="row969821237093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p446583319093521"><a name="p446583319093521"></a><a name="p446583319093521"></a><a href="osal.md#gaada4d66f4bb789bb4113e4084da6dea2">OsalFileLseek</a> (<a href="osalfile.md">OsalFile</a> *file, off_t offset, int32_t whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1808499809093521"><a name="p1808499809093521"></a><a name="p1808499809093521"></a>off_t </p>
<p id="p325784778093521"><a name="p325784778093521"></a><a name="p325784778093521"></a>Sets the file read/write offset. </p>
</td>
</tr>
<tr id="row211445821093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1181123956093521"><a name="p1181123956093521"></a><a name="p1181123956093521"></a><a href="osal.md#ga428b9de7fb95a20ab9e25b47a7d4272c">OsalRequestFirmware</a> (struct <a href="osalfirmware.md">OsalFirmware</a> *fw, const char *fwName, void *device)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p30635914093521"><a name="p30635914093521"></a><a name="p30635914093521"></a>int32_t </p>
<p id="p1839246609093521"><a name="p1839246609093521"></a><a name="p1839246609093521"></a>Requests a firmware file based on its name and device information. </p>
</td>
</tr>
<tr id="row303153858093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p540490131093521"><a name="p540490131093521"></a><a name="p540490131093521"></a><a href="osal.md#ga41ae4dade9246f3b30efd276cbd43474">OsalSeekFirmware</a> (struct <a href="osalfirmware.md">OsalFirmware</a> *fw, uint32_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p913505441093521"><a name="p913505441093521"></a><a name="p913505441093521"></a>int32_t </p>
<p id="p783206261093521"><a name="p783206261093521"></a><a name="p783206261093521"></a>Reads a firmware file. </p>
</td>
</tr>
<tr id="row2080851867093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816251492093521"><a name="p816251492093521"></a><a name="p816251492093521"></a><a href="osal.md#ga2b721d36c177786841cd05cecdb01034">OsalReadFirmware</a> (struct <a href="osalfirmware.md">OsalFirmware</a> *fw, struct <a href="osalfwblock.md">OsalFwBlock</a> *block)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369846832093521"><a name="p369846832093521"></a><a name="p369846832093521"></a>int32_t </p>
<p id="p1780686164093521"><a name="p1780686164093521"></a><a name="p1780686164093521"></a>Releases a firmware file. </p>
</td>
</tr>
<tr id="row615360713093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038747529093521"><a name="p2038747529093521"></a><a name="p2038747529093521"></a><a href="osal.md#gadfccddc78411a76ae8f4af4282da12f0">OsalReleaseFirmware</a> (struct <a href="osalfirmware.md">OsalFirmware</a> *fw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445869547093521"><a name="p445869547093521"></a><a name="p445869547093521"></a>int32_t </p>
</td>
</tr>
<tr id="row620673813093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761150932093521"><a name="p1761150932093521"></a><a name="p1761150932093521"></a><a href="osal.md#ga281757438906600ef89a13362151d955">OsalIoRemap</a> (unsigned long phys_addr, unsigned long size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p687808964093521"><a name="p687808964093521"></a><a name="p687808964093521"></a>static void * </p>
<p id="p1932217710093521"><a name="p1932217710093521"></a><a name="p1932217710093521"></a>Remaps an I/O physical address to its virtual address. </p>
</td>
</tr>
<tr id="row1635159169093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p884967589093521"><a name="p884967589093521"></a><a name="p884967589093521"></a><a href="osal.md#ga0a845edb56df0a35beeea338dc5121aa">OsalIoUnmap</a> (void *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2001712708093521"><a name="p2001712708093521"></a><a name="p2001712708093521"></a>static void </p>
<p id="p782785995093521"><a name="p782785995093521"></a><a name="p782785995093521"></a>Unmaps an I/O virtual address associated with the physical address. </p>
</td>
</tr>
<tr id="row959280904093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1804545589093521"><a name="p1804545589093521"></a><a name="p1804545589093521"></a><a href="osal.md#gade084a1942c1672f2148ccf8f6c06331">OsalRegisterIrq</a> (uint32_t irqId, uint32_t config, <a href="osal.md#gab671a9e177f622a98af9ca1bd93198eb">OsalIRQHandle</a> handle, const char *name, void *dev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2050373009093521"><a name="p2050373009093521"></a><a name="p2050373009093521"></a>int32_t </p>
<p id="p655475797093521"><a name="p655475797093521"></a><a name="p655475797093521"></a>Registers an IRQ. </p>
</td>
</tr>
<tr id="row281018838093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649689367093521"><a name="p649689367093521"></a><a name="p649689367093521"></a><a href="osal.md#gade4ec4496eb07f1ff0610b53ba419dba">OsalUnregisterIrq</a> (uint32_t irqId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1558669681093521"><a name="p1558669681093521"></a><a name="p1558669681093521"></a>int32_t </p>
<p id="p294950162093521"><a name="p294950162093521"></a><a name="p294950162093521"></a>Unregisters an IRQ. </p>
</td>
</tr>
<tr id="row331758799093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p873829230093521"><a name="p873829230093521"></a><a name="p873829230093521"></a><a href="osal.md#ga7f27c6171678ab8cf925660068ac38ff">OsalEnableIrq</a> (uint32_t irqId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p362018549093521"><a name="p362018549093521"></a><a name="p362018549093521"></a>int32_t </p>
<p id="p538978202093521"><a name="p538978202093521"></a><a name="p538978202093521"></a>Enables an IRQ. </p>
</td>
</tr>
<tr id="row1709816169093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490921910093521"><a name="p1490921910093521"></a><a name="p1490921910093521"></a><a href="osal.md#gaf6ae039d209e46d45c683aeda3e7cd28">OsalDisableIrq</a> (uint32_t irqId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911643970093521"><a name="p911643970093521"></a><a name="p911643970093521"></a>int32_t </p>
<p id="p1787551298093521"><a name="p1787551298093521"></a><a name="p1787551298093521"></a>Disables an IRQ. </p>
</td>
</tr>
<tr id="row181761464093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p803159136093521"><a name="p803159136093521"></a><a name="p803159136093521"></a><a href="osal.md#ga0a1c85eaad6c1588ed091e0e89b74ed2">OsalMemAlloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p97380117093521"><a name="p97380117093521"></a><a name="p97380117093521"></a>void * </p>
<p id="p1207667485093521"><a name="p1207667485093521"></a><a name="p1207667485093521"></a>Allocates memory of a specified size. </p>
</td>
</tr>
<tr id="row77876455093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1358518850093521"><a name="p1358518850093521"></a><a name="p1358518850093521"></a><a href="osal.md#ga7a6d0f6400e835bcbe9ec655bc9f43ee">OsalMemCalloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993344781093521"><a name="p993344781093521"></a><a name="p993344781093521"></a>void * </p>
<p id="p529113295093521"><a name="p529113295093521"></a><a name="p529113295093521"></a>Allocates memory of a specified size, and clears the allocated memory. </p>
</td>
</tr>
<tr id="row313837534093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1233317211093521"><a name="p1233317211093521"></a><a name="p1233317211093521"></a><a href="osal.md#gaf6d1b6e5583d9e1ca5abf5048bb3bad9">OsalMemAllocAlign</a> (size_t alignment, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000140844093521"><a name="p2000140844093521"></a><a name="p2000140844093521"></a>void * </p>
<p id="p297734807093521"><a name="p297734807093521"></a><a name="p297734807093521"></a>Allocates memory of a specified size, and aligns the memory address on a given boundary. </p>
</td>
</tr>
<tr id="row2088527848093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1745469088093521"><a name="p1745469088093521"></a><a name="p1745469088093521"></a><a href="osal.md#ga20dc9c415433effea4d481180a50cfa1">OsalMemFree</a> (void *mem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2108218250093521"><a name="p2108218250093521"></a><a name="p2108218250093521"></a>void </p>
<p id="p1415907608093521"><a name="p1415907608093521"></a><a name="p1415907608093521"></a>Releases memory. </p>
</td>
</tr>
<tr id="row381713868093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977611254093521"><a name="p977611254093521"></a><a name="p977611254093521"></a><a href="osal.md#ga9bbc55785f8a533b0b099956bcbe258e">OsalMutexInit</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504952965093521"><a name="p504952965093521"></a><a name="p504952965093521"></a>int32_t </p>
<p id="p608575725093521"><a name="p608575725093521"></a><a name="p608575725093521"></a>Initializes a mutex. </p>
</td>
</tr>
<tr id="row986494971093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1882535444093521"><a name="p1882535444093521"></a><a name="p1882535444093521"></a><a href="osal.md#gaa37328265ee97277516f6905f90a41b3">OsalMutexDestroy</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842288760093521"><a name="p842288760093521"></a><a name="p842288760093521"></a>int32_t </p>
<p id="p1275532071093521"><a name="p1275532071093521"></a><a name="p1275532071093521"></a>Destroys a mutex. </p>
</td>
</tr>
<tr id="row1935267522093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1586228574093521"><a name="p1586228574093521"></a><a name="p1586228574093521"></a><a href="osal.md#ga45d893bf49a8fb8caf76fa5d31822e0e">OsalMutexLock</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075672306093521"><a name="p2075672306093521"></a><a name="p2075672306093521"></a>int32_t </p>
<p id="p1118095764093521"><a name="p1118095764093521"></a><a name="p1118095764093521"></a>Locks a mutex. </p>
</td>
</tr>
<tr id="row512079154093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797587303093521"><a name="p1797587303093521"></a><a name="p1797587303093521"></a><a href="osal.md#ga57162c8f2e812ef3e5ace498bb85a3b6">OsalMutexTimedLock</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex, uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519520131093521"><a name="p519520131093521"></a><a name="p519520131093521"></a>int32_t </p>
<p id="p991103214093521"><a name="p991103214093521"></a><a name="p991103214093521"></a>Locks a mutex with a specified timeout duration. </p>
</td>
</tr>
<tr id="row103266387093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p594260556093521"><a name="p594260556093521"></a><a name="p594260556093521"></a><a href="osal.md#gae76ffb4db66c988be5209e0dfdc7a35f">OsalMutexUnlock</a> (struct <a href="osalmutex.md">OsalMutex</a> *mutex)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974987058093521"><a name="p1974987058093521"></a><a name="p1974987058093521"></a>int32_t </p>
<p id="p303331803093521"><a name="p303331803093521"></a><a name="p303331803093521"></a>Unlocks a mutex. </p>
</td>
</tr>
<tr id="row1025085351093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1151186485093521"><a name="p1151186485093521"></a><a name="p1151186485093521"></a><a href="osal.md#ga7e4325c951479e93abe072290162da0b">OsalSemInit</a> (struct <a href="osalsem.md">OsalSem</a> *sem, uint32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p533825708093521"><a name="p533825708093521"></a><a name="p533825708093521"></a>int32_t </p>
<p id="p208074337093521"><a name="p208074337093521"></a><a name="p208074337093521"></a>Initializes a semaphore. </p>
</td>
</tr>
<tr id="row1543225650093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1637057604093521"><a name="p1637057604093521"></a><a name="p1637057604093521"></a><a href="osal.md#ga0000b9ee1421950d5b3a04cbc839c6af">OsalSemWait</a> (struct <a href="osalsem.md">OsalSem</a> *sem, uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p640474435093521"><a name="p640474435093521"></a><a name="p640474435093521"></a>int32_t </p>
<p id="p1152672700093521"><a name="p1152672700093521"></a><a name="p1152672700093521"></a>Waits for a semaphore. </p>
</td>
</tr>
<tr id="row770288082093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40877854093521"><a name="p40877854093521"></a><a name="p40877854093521"></a><a href="osal.md#gadc3205b416d3fc8e1fa9c332b82e634a">OsalSemPost</a> (struct <a href="osalsem.md">OsalSem</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p24302495093521"><a name="p24302495093521"></a><a name="p24302495093521"></a>int32_t </p>
<p id="p2034298188093521"><a name="p2034298188093521"></a><a name="p2034298188093521"></a>Releases a semaphore. </p>
</td>
</tr>
<tr id="row1459623043093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p882876495093521"><a name="p882876495093521"></a><a name="p882876495093521"></a><a href="osal.md#ga0b6642005b8a128ac01f69385bd6969f">OsalSemDestroy</a> (struct <a href="osalsem.md">OsalSem</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386047965093521"><a name="p386047965093521"></a><a name="p386047965093521"></a>int32_t </p>
<p id="p834023310093521"><a name="p834023310093521"></a><a name="p834023310093521"></a>Destroys a semaphore. </p>
</td>
</tr>
<tr id="row1753155811093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850709224093521"><a name="p1850709224093521"></a><a name="p1850709224093521"></a><a href="osal.md#gae36a2d6e4e0191273c9f86a918befb5c">OsalSpinInit</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1469538041093521"><a name="p1469538041093521"></a><a name="p1469538041093521"></a>int32_t </p>
<p id="p153715082093521"><a name="p153715082093521"></a><a name="p153715082093521"></a>Initializes a spinlock. </p>
</td>
</tr>
<tr id="row351046468093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106307525093521"><a name="p2106307525093521"></a><a name="p2106307525093521"></a><a href="osal.md#gacd3824f292ddef395bd1a4a7b5546470">OsalSpinDestroy</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900448430093521"><a name="p1900448430093521"></a><a name="p1900448430093521"></a>int32_t </p>
<p id="p524710125093521"><a name="p524710125093521"></a><a name="p524710125093521"></a>Destroys a spinlock. </p>
</td>
</tr>
<tr id="row1590290114093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793487506093521"><a name="p793487506093521"></a><a name="p793487506093521"></a><a href="osal.md#gae1c4b9ac8ea2a4820d73c20ae017dbd7">OsalSpinLock</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700921259093521"><a name="p1700921259093521"></a><a name="p1700921259093521"></a>int32_t </p>
<p id="p752488858093521"><a name="p752488858093521"></a><a name="p752488858093521"></a>Obtains a spinlock. </p>
</td>
</tr>
<tr id="row2112526634093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1319141716093521"><a name="p1319141716093521"></a><a name="p1319141716093521"></a><a href="osal.md#gada1f1826b19dc900af370a2bcd9681b9">OsalSpinUnlock</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223712385093521"><a name="p223712385093521"></a><a name="p223712385093521"></a>int32_t </p>
<p id="p1109749084093521"><a name="p1109749084093521"></a><a name="p1109749084093521"></a>Releases a spinlock. </p>
</td>
</tr>
<tr id="row1001727194093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1320491677093521"><a name="p1320491677093521"></a><a name="p1320491677093521"></a><a href="osal.md#ga7d409ec573a06078112a8ffae14afce5">OsalSpinLockIrq</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890694074093521"><a name="p1890694074093521"></a><a name="p1890694074093521"></a>int32_t </p>
<p id="p635134198093521"><a name="p635134198093521"></a><a name="p635134198093521"></a>Obtains a spinlock and disables the IRQ. </p>
</td>
</tr>
<tr id="row1408721580093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1690613733093521"><a name="p1690613733093521"></a><a name="p1690613733093521"></a><a href="osal.md#ga7d7848d572fbda413b3b5770e95a234e">OsalSpinUnlockIrq</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417537049093521"><a name="p1417537049093521"></a><a name="p1417537049093521"></a>int32_t </p>
<p id="p383135053093521"><a name="p383135053093521"></a><a name="p383135053093521"></a>Releases a spinlock and enables the IRQ. </p>
</td>
</tr>
<tr id="row2115721404093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1058401714093521"><a name="p1058401714093521"></a><a name="p1058401714093521"></a><a href="osal.md#gab711d8d56055e78dd85f84bc530a4d3f">OsalSpinLockIrqSave</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock, uint32_t *flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1759762295093521"><a name="p1759762295093521"></a><a name="p1759762295093521"></a>int32_t </p>
<p id="p2122526286093521"><a name="p2122526286093521"></a><a name="p2122526286093521"></a>Obtains a spinlock, disables the IRQ, and saves its status. </p>
</td>
</tr>
<tr id="row14378293093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p548746550093521"><a name="p548746550093521"></a><a name="p548746550093521"></a><a href="osal.md#ga3be4dbde6c9ae740b012e49ab90e7a8a">OsalSpinUnlockIrqRestore</a> (<a href="osalspinlock.md">OsalSpinlock</a> *spinlock, uint32_t *flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1116787983093521"><a name="p1116787983093521"></a><a name="p1116787983093521"></a>int32_t </p>
<p id="p908032271093521"><a name="p908032271093521"></a><a name="p908032271093521"></a>Releases a spinlock, enables the IRQ, and restores the saved IRQ status. </p>
</td>
</tr>
<tr id="row152799945093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1023155750093521"><a name="p1023155750093521"></a><a name="p1023155750093521"></a><a href="osal.md#gad598b3f4b91f5e6aeeaf7b8a6e507f1e">OsalThreadCreate</a> (struct <a href="osalthread.md">OsalThread</a> *thread, <a href="osal.md#ga21ea0f87d53e65ec86a424c532d688d8">OsalThreadEntry</a> threadEntry, void *entryPara)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1516620739093521"><a name="p1516620739093521"></a><a name="p1516620739093521"></a>int32_t </p>
<p id="p1846864746093521"><a name="p1846864746093521"></a><a name="p1846864746093521"></a>Creates a thread. </p>
</td>
</tr>
<tr id="row1142394363093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49900139093521"><a name="p49900139093521"></a><a name="p49900139093521"></a><a href="osal.md#ga74c93bd48d27cde830451f63b224307a">OsalThreadStart</a> (struct <a href="osalthread.md">OsalThread</a> *thread, const struct <a href="osalthreadparam.md">OsalThreadParam</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521517278093521"><a name="p1521517278093521"></a><a name="p1521517278093521"></a>int32_t </p>
<p id="p1933888666093521"><a name="p1933888666093521"></a><a name="p1933888666093521"></a>Starts a thread. </p>
</td>
</tr>
<tr id="row416410959093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p632532461093521"><a name="p632532461093521"></a><a name="p632532461093521"></a><a href="osal.md#ga223ce6b94770348a93168525c536e6f9">OsalThreadDestroy</a> (struct <a href="osalthread.md">OsalThread</a> *thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p803687984093521"><a name="p803687984093521"></a><a name="p803687984093521"></a>int32_t </p>
<p id="p712877449093521"><a name="p712877449093521"></a><a name="p712877449093521"></a>Destroys a thread. </p>
</td>
</tr>
<tr id="row220062863093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1621799451093521"><a name="p1621799451093521"></a><a name="p1621799451093521"></a><a href="osal.md#gad556075f625d01557c0075a2c092a1da">OsalThreadSuspend</a> (struct <a href="osalthread.md">OsalThread</a> *thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844670938093521"><a name="p1844670938093521"></a><a name="p1844670938093521"></a>int32_t </p>
<p id="p816219378093521"><a name="p816219378093521"></a><a name="p816219378093521"></a>Suspends a thread. </p>
</td>
</tr>
<tr id="row21102843093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1929932216093521"><a name="p1929932216093521"></a><a name="p1929932216093521"></a><a href="osal.md#ga32f0b5c622518b7453f758d95b137a94">OsalThreadResume</a> (struct <a href="osalthread.md">OsalThread</a> *thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1480649338093521"><a name="p1480649338093521"></a><a name="p1480649338093521"></a>int32_t </p>
<p id="p1183782609093521"><a name="p1183782609093521"></a><a name="p1183782609093521"></a>Resumes a thread. </p>
</td>
</tr>
<tr id="row540289066093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p75027702093521"><a name="p75027702093521"></a><a name="p75027702093521"></a><a href="osal.md#ga8b9ca3498c54b11dcbe88a2a456f23ab">OsalSleep</a> (uint32_t sec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566989105093521"><a name="p1566989105093521"></a><a name="p1566989105093521"></a>void </p>
<p id="p1412280908093521"><a name="p1412280908093521"></a><a name="p1412280908093521"></a>Describes thread sleep, in seconds. </p>
</td>
</tr>
<tr id="row1484455399093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2529250093521"><a name="p2529250093521"></a><a name="p2529250093521"></a><a href="osal.md#ga2361dc099952df28aaef8968f9f4b9a7">OsalMSleep</a> (uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p17587785093521"><a name="p17587785093521"></a><a name="p17587785093521"></a>void </p>
<p id="p473330792093521"><a name="p473330792093521"></a><a name="p473330792093521"></a>Describes thread sleep, in milliseconds. </p>
</td>
</tr>
<tr id="row75184085093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p638030686093521"><a name="p638030686093521"></a><a name="p638030686093521"></a><a href="osal.md#ga649d3090dcf9ba0e22649e11ac40831f">OsalGetTime</a> (<a href="osaltimespec.md">OsalTimespec</a> *<a href="en-us_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673273015093521"><a name="p1673273015093521"></a><a name="p1673273015093521"></a>int32_t </p>
<p id="p1417440741093521"><a name="p1417440741093521"></a><a name="p1417440741093521"></a>Obtains the second and microsecond time. </p>
</td>
</tr>
<tr id="row1904206964093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1343842056093521"><a name="p1343842056093521"></a><a name="p1343842056093521"></a><a href="osal.md#ga36b0af6646f887175993e78391a5cabc">OsalDiffTime</a> (const <a href="osaltimespec.md">OsalTimespec</a> *start, const <a href="osaltimespec.md">OsalTimespec</a> *end, <a href="osaltimespec.md">OsalTimespec</a> *diff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1442815403093521"><a name="p1442815403093521"></a><a name="p1442815403093521"></a>int32_t </p>
<p id="p65425161093521"><a name="p65425161093521"></a><a name="p65425161093521"></a>Obtains time difference. </p>
</td>
</tr>
<tr id="row2033434467093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p450021020093521"><a name="p450021020093521"></a><a name="p450021020093521"></a><a href="osal.md#gaf91cb1945b66e324fbb0761aa2f98ea3">OsalGetSysTimeMs</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670662582093521"><a name="p1670662582093521"></a><a name="p1670662582093521"></a>uint64_t </p>
<p id="p2118720733093521"><a name="p2118720733093521"></a><a name="p2118720733093521"></a>Obtains the system time. </p>
</td>
</tr>
<tr id="row1017728539093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1750689521093521"><a name="p1750689521093521"></a><a name="p1750689521093521"></a><a href="osal.md#ga82ddd682a2441a22dd6148f634a6cea4">OsalMDelay</a> (uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58551780093521"><a name="p58551780093521"></a><a name="p58551780093521"></a>void </p>
<p id="p573464554093521"><a name="p573464554093521"></a><a name="p573464554093521"></a>Describes thread delay, in milliseconds. </p>
</td>
</tr>
<tr id="row1070733420093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p433013961093521"><a name="p433013961093521"></a><a name="p433013961093521"></a><a href="osal.md#ga7ae78fa3318a82dbd769827d4f373958">OsalUDelay</a> (uint32_t us)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p802244570093521"><a name="p802244570093521"></a><a name="p802244570093521"></a>void </p>
<p id="p1301466735093521"><a name="p1301466735093521"></a><a name="p1301466735093521"></a>Describes thread delay, in microseconds. </p>
</td>
</tr>
<tr id="row807814973093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1588418271093521"><a name="p1588418271093521"></a><a name="p1588418271093521"></a><a href="osal.md#ga879d9a437e1423021f95cb9341f0d6af">OsalTimerCreate</a> (<a href="osaltimer.md">OsalTimer</a> *timer, uint32_t interval, <a href="osal.md#gaf3e7a12075b25df5971049d8cd77c25c">OsalTimerFunc</a> func, uintptr_t arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122654473093521"><a name="p1122654473093521"></a><a name="p1122654473093521"></a>int32_t </p>
<p id="p730727352093521"><a name="p730727352093521"></a><a name="p730727352093521"></a>Creates a timer. </p>
</td>
</tr>
<tr id="row1065899177093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p340686338093521"><a name="p340686338093521"></a><a name="p340686338093521"></a><a href="osal.md#gab754f3522245e6b2f9ee1cdecae62b52">OsalTimerDelete</a> (<a href="osaltimer.md">OsalTimer</a> *timer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535396324093521"><a name="p1535396324093521"></a><a name="p1535396324093521"></a>int32_t </p>
<p id="p1721550014093521"><a name="p1721550014093521"></a><a name="p1721550014093521"></a>Deletes a timer. </p>
</td>
</tr>
<tr id="row1592333316093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p525375197093521"><a name="p525375197093521"></a><a name="p525375197093521"></a><a href="osal.md#gaf2e49d5b01b49e5f64a7701da8667141">OsalTimerStartOnce</a> (<a href="osaltimer.md">OsalTimer</a> *timer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p627998212093521"><a name="p627998212093521"></a><a name="p627998212093521"></a>int32_t </p>
<p id="p838870824093521"><a name="p838870824093521"></a><a name="p838870824093521"></a>Starts a timer. </p>
</td>
</tr>
<tr id="row1067008384093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p902348217093521"><a name="p902348217093521"></a><a name="p902348217093521"></a><a href="osal.md#ga575e4f41359c737ab9690ab28838b99f">OsalTimerStartLoop</a> (<a href="osaltimer.md">OsalTimer</a> *timer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1832708663093521"><a name="p1832708663093521"></a><a name="p1832708663093521"></a>int32_t </p>
<p id="p1607952091093521"><a name="p1607952091093521"></a><a name="p1607952091093521"></a>Starts a periodic timer. </p>
</td>
</tr>
<tr id="row1948910510093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651491219093521"><a name="p651491219093521"></a><a name="p651491219093521"></a><a href="osal.md#ga49c2fe3f54d548fe5ec0d03a79691376">OsalTimerSetTimeout</a> (<a href="osaltimer.md">OsalTimer</a> *timer, uint32_t interval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p747114186093521"><a name="p747114186093521"></a><a name="p747114186093521"></a>int32_t </p>
<p id="p99484877093521"><a name="p99484877093521"></a><a name="p99484877093521"></a>Sets the interval of a timer. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section802963690093521"></a>

## **Macro Definition Documentation**<a name="section551861785093521"></a>

## OSAL\_READB<a name="ga3de1529efbdabd4fb2f144c6f48df70b"></a>

```
#define OSAL_READB( address)   readb(address)
```

 **Description:**

Reads one byte of data from an I/O address space. 

**Parameters:**

<a name="table537206422093521"></a>
<table><thead align="left"><tr id="row2064645202093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p690608749093521"><a name="p690608749093521"></a><a name="p690608749093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1154153315093521"><a name="p1154153315093521"></a><a name="p1154153315093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1810072150093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the address to read. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the byte.



## OSAL\_READL<a name="ga14ce14451b2484b2e268a38757237f41"></a>

```
#define OSAL_READL( address)   readl(address)
```

 **Description:**

Reads an integer from an I/O address space. 

**Parameters:**

<a name="table47798010093521"></a>
<table><thead align="left"><tr id="row945489242093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1270530630093521"><a name="p1270530630093521"></a><a name="p1270530630093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1994658828093521"><a name="p1994658828093521"></a><a name="p1994658828093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row104590892093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the address to read. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the integer.



## OSAL\_READW<a name="ga8bd523f234f24415fe733addd113e60b"></a>

```
#define OSAL_READW( address)   readw(address)
```

 **Description:**

Reads a short integer from an I/O address space. 

**Parameters:**

<a name="table1709345388093521"></a>
<table><thead align="left"><tr id="row849839387093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p768271443093521"><a name="p768271443093521"></a><a name="p768271443093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p334201534093521"><a name="p334201534093521"></a><a name="p334201534093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1766263901093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the address to read. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the short integer.



## OSAL\_WRITEB<a name="ga48e1f404639550c229aee3ec35a06d79"></a>

```
#define OSAL_WRITEB( value,  address )   writeb(value, address)
```

 **Description:**

Writes one byte of data into an I/O address space. 

**Parameters:**

<a name="table1432389980093521"></a>
<table><thead align="left"><tr id="row1651244742093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1163754350093521"><a name="p1163754350093521"></a><a name="p1163754350093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p329501390093521"><a name="p329501390093521"></a><a name="p329501390093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row41836369093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data to write. </td>
</tr>
<tr id="row1565068134093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the address to write.</td>
</tr>
</tbody>
</table>

## OSAL\_WRITEL<a name="gaba47d67efad3ad9d1a33a35d2982bd49"></a>

```
#define OSAL_WRITEL( value,  address )   writel(value, address)
```

 **Description:**

Writes an integer into an I/O address space. 

**Parameters:**

<a name="table1176711798093521"></a>
<table><thead align="left"><tr id="row829853727093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1765694579093521"><a name="p1765694579093521"></a><a name="p1765694579093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p899676395093521"><a name="p899676395093521"></a><a name="p899676395093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row937216713093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data to write. </td>
</tr>
<tr id="row378376418093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the address to write.</td>
</tr>
</tbody>
</table>

## OSAL\_WRITEW<a name="ga3358a86c6bbb6f02ab108964962f441f"></a>

```
#define OSAL_WRITEW( value,  address )   writew(value, address)
```

 **Description:**

Writes a short integer into an I/O address space. 

**Parameters:**

<a name="table180885622093521"></a>
<table><thead align="left"><tr id="row1362277472093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1389860411093521"><a name="p1389860411093521"></a><a name="p1389860411093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1213371869093521"><a name="p1213371869093521"></a><a name="p1213371869093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1273104262093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data to write. </td>
</tr>
<tr id="row2003030600093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the address to write.</td>
</tr>
</tbody>
</table>

## **Enumeration Type Documentation**<a name="section1001556911093521"></a>

## OSAL\_IRQ\_TRIGGER\_MODE<a name="ga78cd126b10424753db6f39f9b72ea124"></a>

```
enum [OSAL_IRQ_TRIGGER_MODE](osal.md#ga78cd126b10424753db6f39f9b72ea124)
```

 **Description:**

Enumerates interrupt trigger modes. 

<a name="table727053384093521"></a>
<table><thead align="left"><tr id="row1709223302093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p627995344093521"><a name="p627995344093521"></a><a name="p627995344093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p475446660093521"><a name="p475446660093521"></a><a name="p475446660093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1246264110093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga78cd126b10424753db6f39f9b72ea124aa0252cbf1f560b1d9951da4dfe896a1d"><a name="gga78cd126b10424753db6f39f9b72ea124aa0252cbf1f560b1d9951da4dfe896a1d"></a><a name="gga78cd126b10424753db6f39f9b72ea124aa0252cbf1f560b1d9951da4dfe896a1d"></a></strong>OSAL_IRQF_TRIGGER_NONE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p83005396093521"><a name="p83005396093521"></a><a name="p83005396093521"></a>Edge-triggered is not set </p>
 </td>
</tr>
<tr id="row1332671870093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga78cd126b10424753db6f39f9b72ea124ab98297946a624d99a3fad6adac899f2c"><a name="gga78cd126b10424753db6f39f9b72ea124ab98297946a624d99a3fad6adac899f2c"></a><a name="gga78cd126b10424753db6f39f9b72ea124ab98297946a624d99a3fad6adac899f2c"></a></strong>OSAL_IRQF_TRIGGER_RISING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p234846486093521"><a name="p234846486093521"></a><a name="p234846486093521"></a>Rising edge triggered </p>
 </td>
</tr>
<tr id="row1184562975093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga78cd126b10424753db6f39f9b72ea124a3088c6875fb44d05fd3a64a3d158295b"><a name="gga78cd126b10424753db6f39f9b72ea124a3088c6875fb44d05fd3a64a3d158295b"></a><a name="gga78cd126b10424753db6f39f9b72ea124a3088c6875fb44d05fd3a64a3d158295b"></a></strong>OSAL_IRQF_TRIGGER_FALLING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1546252153093521"><a name="p1546252153093521"></a><a name="p1546252153093521"></a>Failing edge triggered </p>
 </td>
</tr>
<tr id="row1173557749093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga78cd126b10424753db6f39f9b72ea124a9a997189554c568f66dd994a9f9e203d"><a name="gga78cd126b10424753db6f39f9b72ea124a9a997189554c568f66dd994a9f9e203d"></a><a name="gga78cd126b10424753db6f39f9b72ea124a9a997189554c568f66dd994a9f9e203d"></a></strong>OSAL_IRQF_TRIGGER_HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p860189314093521"><a name="p860189314093521"></a><a name="p860189314093521"></a>High-level triggered </p>
 </td>
</tr>
<tr id="row278270792093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga78cd126b10424753db6f39f9b72ea124a7768ec0b5be5e88cfeb07dea96cd5865"><a name="gga78cd126b10424753db6f39f9b72ea124a7768ec0b5be5e88cfeb07dea96cd5865"></a><a name="gga78cd126b10424753db6f39f9b72ea124a7768ec0b5be5e88cfeb07dea96cd5865"></a></strong>OSAL_IRQF_TRIGGER_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770637609093521"><a name="p1770637609093521"></a><a name="p1770637609093521"></a>Low-level triggered </p>
 </td>
</tr>
</tbody>
</table>

## OSAL\_THREAD\_PRIORITY<a name="gab8c099a9c39fdde73c74b3f7367be5d0"></a>

```
enum [OSAL_THREAD_PRIORITY](osal.md#gab8c099a9c39fdde73c74b3f7367be5d0)
```

 **Description:**

Enumerates thread priorities. 

<a name="table1891707231093521"></a>
<table><thead align="left"><tr id="row1137273790093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1650147748093521"><a name="p1650147748093521"></a><a name="p1650147748093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1947947533093521"><a name="p1947947533093521"></a><a name="p1947947533093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row612507933093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab8c099a9c39fdde73c74b3f7367be5d0a077e53412997ddef962069a7cea4def6"><a name="ggab8c099a9c39fdde73c74b3f7367be5d0a077e53412997ddef962069a7cea4def6"></a><a name="ggab8c099a9c39fdde73c74b3f7367be5d0a077e53412997ddef962069a7cea4def6"></a></strong>OSAL_THREAD_PRI_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p747926316093521"><a name="p747926316093521"></a><a name="p747926316093521"></a>Low priority </p>
 </td>
</tr>
<tr id="row1927743041093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab8c099a9c39fdde73c74b3f7367be5d0abc9ef48a9fc95f359a5c4d52041111e5"><a name="ggab8c099a9c39fdde73c74b3f7367be5d0abc9ef48a9fc95f359a5c4d52041111e5"></a><a name="ggab8c099a9c39fdde73c74b3f7367be5d0abc9ef48a9fc95f359a5c4d52041111e5"></a></strong>OSAL_THREAD_PRI_DEFAULT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1637444531093521"><a name="p1637444531093521"></a><a name="p1637444531093521"></a>Default priority </p>
 </td>
</tr>
<tr id="row1333721496093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab8c099a9c39fdde73c74b3f7367be5d0a61697eda5c5265d6d62271d00c098121"><a name="ggab8c099a9c39fdde73c74b3f7367be5d0a61697eda5c5265d6d62271d00c098121"></a><a name="ggab8c099a9c39fdde73c74b3f7367be5d0a61697eda5c5265d6d62271d00c098121"></a></strong>OSAL_THREAD_PRI_HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p214099144093521"><a name="p214099144093521"></a><a name="p214099144093521"></a>High priority </p>
 </td>
</tr>
<tr id="row2094199829093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab8c099a9c39fdde73c74b3f7367be5d0a9e66435e6d967adc68606b359a8753bd"><a name="ggab8c099a9c39fdde73c74b3f7367be5d0a9e66435e6d967adc68606b359a8753bd"></a><a name="ggab8c099a9c39fdde73c74b3f7367be5d0a9e66435e6d967adc68606b359a8753bd"></a></strong>OSAL_THREAD_PRI_HIGHEST </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313415145093521"><a name="p1313415145093521"></a><a name="p1313415145093521"></a>Highest priority </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section180540894093521"></a>

## OsalAtomicDec\(\)<a name="gaa411f380e6b21c8467260030ceee38ff"></a>

```
void OsalAtomicDec ([OsalAtomic](osalatomic.md) * v)
```

 **Description:**

Decrements the counter of an atomic by 1. 

**Parameters:**

<a name="table843659020093521"></a>
<table><thead align="left"><tr id="row1333723671093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p65362834093521"><a name="p65362834093521"></a><a name="p65362834093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p23858584093521"><a name="p23858584093521"></a><a name="p23858584093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1500514704093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">v</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the atomic <a href="osalatomic.md">OsalAtomic</a>.</td>
</tr>
</tbody>
</table>

## OsalAtomicInc\(\)<a name="ga11214c11a9b875cb8ba0a67aeccc6ac9"></a>

```
void OsalAtomicInc ([OsalAtomic](osalatomic.md) * v)
```

 **Description:**

Increments the counter of an atomic by 1. 

**Parameters:**

<a name="table281068630093521"></a>
<table><thead align="left"><tr id="row841350728093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1523506881093521"><a name="p1523506881093521"></a><a name="p1523506881093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1516912269093521"><a name="p1516912269093521"></a><a name="p1516912269093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row948747005093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">v</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the atomic <a href="osalatomic.md">OsalAtomic</a>.</td>
</tr>
</tbody>
</table>

## OsalAtomicRead\(\)<a name="gaf7b7a860f5cf11bda3008ce16a5d79d5"></a>

```
int32_t OsalAtomicRead (const [OsalAtomic](osalatomic.md) * v)
```

 **Description:**

Reads the counter of an atomic. 

**Parameters:**

<a name="table469320983093521"></a>
<table><thead align="left"><tr id="row912050930093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1827674813093521"><a name="p1827674813093521"></a><a name="p1827674813093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1312742825093521"><a name="p1312742825093521"></a><a name="p1312742825093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row673443315093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">v</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the atomic <a href="osalatomic.md">OsalAtomic</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the counter. 



## OsalAtomicSet\(\)<a name="ga0b82ac10305c7ec5ae46707034b866c3"></a>

```
void OsalAtomicSet ([OsalAtomic](osalatomic.md) * v, int32_t counter )
```

 **Description:**

Sets the counter for an atomic. 

**Parameters:**

<a name="table1034952362093521"></a>
<table><thead align="left"><tr id="row982643435093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1684495298093521"><a name="p1684495298093521"></a><a name="p1684495298093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1655358453093521"><a name="p1655358453093521"></a><a name="p1655358453093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row335665342093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">v</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the atomic <a href="osalatomic.md">OsalAtomic</a>. </td>
</tr>
<tr id="row577402600093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">counter</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the counter to set.</td>
</tr>
</tbody>
</table>

## OsalClearBit\(\)<a name="gae3e5b84f326aa1a2c4b8427509f80cd9"></a>

```
void OsalClearBit (unsigned long nr, volatile unsigned long * addr )
```

 **Description:**

Clears the value of a specified bit of the variable. 

**Parameters:**

<a name="table459505512093521"></a>
<table><thead align="left"><tr id="row1329988717093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2076685009093521"><a name="p2076685009093521"></a><a name="p2076685009093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p155186520093521"><a name="p155186520093521"></a><a name="p155186520093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1611472961093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the bit of the variable. The value ranges from <strong id="b930602416093521"><a name="b930602416093521"></a><a name="b930602416093521"></a>0</strong> to <strong id="b430171946093521"><a name="b430171946093521"></a><a name="b430171946093521"></a>31</strong>. </td>
</tr>
<tr id="row610906577093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable.</td>
</tr>
</tbody>
</table>

## OsalDiffTime\(\)<a name="ga36b0af6646f887175993e78391a5cabc"></a>

```
int32_t OsalDiffTime (const [OsalTimespec](osaltimespec.md) * start, const [OsalTimespec](osaltimespec.md) * end, [OsalTimespec](osaltimespec.md) * diff )
```

 **Description:**

Obtains time difference. 

**Parameters:**

<a name="table284790328093521"></a>
<table><thead align="left"><tr id="row867851824093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p216363439093521"><a name="p216363439093521"></a><a name="p216363439093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1545901623093521"><a name="p1545901623093521"></a><a name="p1545901623093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1318495561093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">start</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start time <a href="osaltimespec.md">OsalTimespec</a>. </td>
</tr>
<tr id="row1008622668093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">end</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the end time <a href="osaltimespec.md">OsalTimespec</a>. </td>
</tr>
<tr id="row1447667003093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">diff</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time difference <a href="osaltimespec.md">OsalTimespec</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1300724719093521"></a>
<table><thead align="left"><tr id="row839128924093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p920122837093521"><a name="p920122837093521"></a><a name="p920122837093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1126677705093521"><a name="p1126677705093521"></a><a name="p1126677705093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row986788537093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844031694093521"><a name="p844031694093521"></a><a name="p844031694093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1302869332093521"><a name="p1302869332093521"></a><a name="p1302869332093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1517209553093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p173682513093521"><a name="p173682513093521"></a><a name="p173682513093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p590725258093521"><a name="p590725258093521"></a><a name="p590725258093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalDisableIrq\(\)<a name="gaf6ae039d209e46d45c683aeda3e7cd28"></a>

```
int32_t OsalDisableIrq (uint32_t irqId)
```

 **Description:**

Disables an IRQ. 

**Parameters:**

<a name="table36793536093521"></a>
<table><thead align="left"><tr id="row544566549093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p386424207093521"><a name="p386424207093521"></a><a name="p386424207093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1421698698093521"><a name="p1421698698093521"></a><a name="p1421698698093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1009967188093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">irqId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the IRQ ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table543969056093521"></a>
<table><thead align="left"><tr id="row368838130093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p650655424093521"><a name="p650655424093521"></a><a name="p650655424093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1271295682093521"><a name="p1271295682093521"></a><a name="p1271295682093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1795509392093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1186817846093521"><a name="p1186817846093521"></a><a name="p1186817846093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785156436093521"><a name="p785156436093521"></a><a name="p785156436093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row819352451093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230116287093521"><a name="p230116287093521"></a><a name="p230116287093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p978248930093521"><a name="p978248930093521"></a><a name="p978248930093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalEnableIrq\(\)<a name="ga7f27c6171678ab8cf925660068ac38ff"></a>

```
int32_t OsalEnableIrq (uint32_t irqId)
```

 **Description:**

Enables an IRQ. 

**Parameters:**

<a name="table49488121093521"></a>
<table><thead align="left"><tr id="row734052237093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1392518234093521"><a name="p1392518234093521"></a><a name="p1392518234093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1153797743093521"><a name="p1153797743093521"></a><a name="p1153797743093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row797221298093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">irqId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the IRQ ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1802225386093521"></a>
<table><thead align="left"><tr id="row1046200771093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p652630812093521"><a name="p652630812093521"></a><a name="p652630812093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1049452420093521"><a name="p1049452420093521"></a><a name="p1049452420093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1714850230093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651135094093521"><a name="p651135094093521"></a><a name="p651135094093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p133684725093521"><a name="p133684725093521"></a><a name="p133684725093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1523722151093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094979041093521"><a name="p2094979041093521"></a><a name="p2094979041093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1494659262093521"><a name="p1494659262093521"></a><a name="p1494659262093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalFileClose\(\)<a name="ga8786ab2baa8669e79173ab7ab47d67bb"></a>

```
void OsalFileClose ([OsalFile](osalfile.md) * file)
```

 **Description:**

Closes a file. 

**Parameters:**

<a name="table633509116093521"></a>
<table><thead align="left"><tr id="row1326388261093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1391401482093521"><a name="p1391401482093521"></a><a name="p1391401482093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1828818245093521"><a name="p1828818245093521"></a><a name="p1828818245093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1021996750093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">file</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the file type <a href="osalfile.md">OsalFile</a>.</td>
</tr>
</tbody>
</table>

## OsalFileLseek\(\)<a name="gaada4d66f4bb789bb4113e4084da6dea2"></a>

```
off_t OsalFileLseek ([OsalFile](osalfile.md) * file, off_t offset, int32_t whence )
```

 **Description:**

Sets the file read/write offset. 

**Parameters:**

<a name="table1346710569093521"></a>
<table><thead align="left"><tr id="row1340708170093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p129362619093521"><a name="p129362619093521"></a><a name="p129362619093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1488994606093521"><a name="p1488994606093521"></a><a name="p1488994606093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1999299580093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">file</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the file type <a href="osalfile.md">OsalFile</a>. </td>
</tr>
<tr id="row285272392093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">offset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the offset to set. </td>
</tr>
<tr id="row1168122497093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">whence</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the position from which the offset is to set. For details, see <a href="osal.md#ga110fc469c88e83828679a3dedb4b5f3d">OSAL_SEEK_SET</a>.</td>
</tr>
</tbody>
</table>

## OsalFileOpen\(\)<a name="ga6707125b6ac5e13912a181877f18f292"></a>

```
int32_t OsalFileOpen ([OsalFile](osalfile.md) * file, const char * path, int flags, uint32_t rights )
```

 **Description:**

Opens a file. 

**Parameters:**

<a name="table1192672109093521"></a>
<table><thead align="left"><tr id="row532711652093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p752836954093521"><a name="p752836954093521"></a><a name="p752836954093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1716270411093521"><a name="p1716270411093521"></a><a name="p1716270411093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1262455681093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">file</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the file type <a href="osalfile.md">OsalFile</a>. </td>
</tr>
<tr id="row1407865804093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the file to open. </td>
</tr>
<tr id="row641702676093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mode of opening the file. For details, see <a href="osal.md#gab208afeed35dd98f6a0ccf807e9c722d">OSAL_O_RD_ONLY</a>. </td>
</tr>
<tr id="row1297050558093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rights</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the permissions required for opening the file. For details, see <a href="osal.md#ga9cb465f6d142e859258e14199702906e">OSAL_S_IREAD</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table121989971093521"></a>
<table><thead align="left"><tr id="row1439345784093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p894623847093521"><a name="p894623847093521"></a><a name="p894623847093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1409784487093521"><a name="p1409784487093521"></a><a name="p1409784487093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row954812433093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p104682562093521"><a name="p104682562093521"></a><a name="p104682562093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p518204046093521"><a name="p518204046093521"></a><a name="p518204046093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row61893677093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1547278098093521"><a name="p1547278098093521"></a><a name="p1547278098093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p957072606093521"><a name="p957072606093521"></a><a name="p957072606093521"></a>Failed to invoke the system function to open the file. </p>
</td>
</tr>
<tr id="row1919626894093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1074745926093521"><a name="p1074745926093521"></a><a name="p1074745926093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491253285093521"><a name="p491253285093521"></a><a name="p491253285093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalFileRead\(\)<a name="gac8ebc8dc4b9ce9725875868f69fd17a8"></a>

```
ssize_t OsalFileRead ([OsalFile](osalfile.md) * file, void * buf, uint32_t length )
```

 **Description:**

Reads a file. 

**Parameters:**

<a name="table1312198087093521"></a>
<table><thead align="left"><tr id="row1245348130093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p512936848093521"><a name="p512936848093521"></a><a name="p512936848093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1826660800093521"><a name="p1826660800093521"></a><a name="p1826660800093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row401072992093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">file</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the file type <a href="osalfile.md">OsalFile</a>. </td>
</tr>
<tr id="row455190284093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the content to read. </td>
</tr>
<tr id="row891219123093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the content to read.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table320812815093521"></a>
<table><thead align="left"><tr id="row2105082990093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2143346993093521"><a name="p2143346993093521"></a><a name="p2143346993093521"></a>ssize_t </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1568067199093521"><a name="p1568067199093521"></a><a name="p1568067199093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1776241749093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p482616517093521"><a name="p482616517093521"></a><a name="p482616517093521"></a>Greater than <strong id="b568031029093521"><a name="b568031029093521"></a><a name="b568031029093521"></a>0</strong> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1956484873093521"><a name="p1956484873093521"></a><a name="p1956484873093521"></a>The length of the file content is successfully read. </p>
</td>
</tr>
<tr id="row912151181093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152617764093521"><a name="p152617764093521"></a><a name="p152617764093521"></a>HDF_FAILURE <a href="driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67">HDF_STATUS</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3740790093521"><a name="p3740790093521"></a><a name="p3740790093521"></a>Failed to invoke the system function to read the file. </p>
</td>
</tr>
<tr id="row941960596093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652499131093521"><a name="p1652499131093521"></a><a name="p1652499131093521"></a>HDF_ERR_INVALID_PARAM <a href="driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67">HDF_STATUS</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087566849093521"><a name="p2087566849093521"></a><a name="p2087566849093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalFileWrite\(\)<a name="ga305f575f875ff26bb907c67c23dfb16a"></a>

```
ssize_t OsalFileWrite ([OsalFile](osalfile.md) * file, const void * string, uint32_t length )
```

 **Description:**

Writes a file. 

**Parameters:**

<a name="table2013448615093521"></a>
<table><thead align="left"><tr id="row1270450498093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2089345510093521"><a name="p2089345510093521"></a><a name="p2089345510093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2105685179093521"><a name="p2105685179093521"></a><a name="p2105685179093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1655146447093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">file</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the file type <a href="osalfile.md">OsalFile</a>. </td>
</tr>
<tr id="row1378066882093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">string</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the content to write. </td>
</tr>
<tr id="row371931932093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the content to write.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table710880512093521"></a>
<table><thead align="left"><tr id="row1753688428093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1326676111093521"><a name="p1326676111093521"></a><a name="p1326676111093521"></a>ssize_t </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p253106495093521"><a name="p253106495093521"></a><a name="p253106495093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1723263339093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p743206996093521"><a name="p743206996093521"></a><a name="p743206996093521"></a>Greater than <strong id="b511823677093521"><a name="b511823677093521"></a><a name="b511823677093521"></a>0</strong> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p232013452093521"><a name="p232013452093521"></a><a name="p232013452093521"></a>The length of the file content is successfully written. </p>
</td>
</tr>
<tr id="row1243080535093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p483148180093521"><a name="p483148180093521"></a><a name="p483148180093521"></a>HDF_FAILURE <a href="driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67">HDF_STATUS</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832554356093521"><a name="p832554356093521"></a><a name="p832554356093521"></a>Failed to invoke the system function to write the file. </p>
</td>
</tr>
<tr id="row1046242007093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730397862093521"><a name="p730397862093521"></a><a name="p730397862093521"></a>HDF_ERR_INVALID_PARAM <a href="driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67">HDF_STATUS</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891006885093521"><a name="p891006885093521"></a><a name="p891006885093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalGetSysTimeMs\(\)<a name="gaf91cb1945b66e324fbb0761aa2f98ea3"></a>

```
uint64_t OsalGetSysTimeMs (void )
```

 **Description:**

Obtains the system time. 

**Returns:**

Returns the system time, in milliseconds. 



## OsalGetTime\(\)<a name="ga649d3090dcf9ba0e22649e11ac40831f"></a>

```
int32_t OsalGetTime ([OsalTimespec](osaltimespec.md) * time)
```

 **Description:**

Obtains the second and microsecond time. 

**Parameters:**

<a name="table153302385093521"></a>
<table><thead align="left"><tr id="row56697352093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1191607783093521"><a name="p1191607783093521"></a><a name="p1191607783093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p508339955093521"><a name="p508339955093521"></a><a name="p508339955093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row956162807093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time structure <a href="osaltimespec.md">OsalTimespec</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table2006834621093521"></a>
<table><thead align="left"><tr id="row1517623201093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1546732442093521"><a name="p1546732442093521"></a><a name="p1546732442093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p297449936093521"><a name="p297449936093521"></a><a name="p297449936093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1670399416093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1744898908093521"><a name="p1744898908093521"></a><a name="p1744898908093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2028756278093521"><a name="p2028756278093521"></a><a name="p2028756278093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row367840005093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48983110093521"><a name="p48983110093521"></a><a name="p48983110093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1790714759093521"><a name="p1790714759093521"></a><a name="p1790714759093521"></a>Failed to invoke the system function to obtain time. </p>
</td>
</tr>
<tr id="row1876134823093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901290034093521"><a name="p1901290034093521"></a><a name="p1901290034093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1790662445093521"><a name="p1790662445093521"></a><a name="p1790662445093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalIoRemap\(\)<a name="ga281757438906600ef89a13362151d955"></a>

```
static void* OsalIoRemap (unsigned long phys_addr, unsigned long size )
```

 **Description:**

Remaps an I/O physical address to its virtual address. 

**Parameters:**

<a name="table1880853856093521"></a>
<table><thead align="left"><tr id="row1599256159093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p177309953093521"><a name="p177309953093521"></a><a name="p177309953093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1403307104093521"><a name="p1403307104093521"></a><a name="p1403307104093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1254682562093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">phys_addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the I/O physical address. </td>
</tr>
<tr id="row1300099912093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the physical address to remap. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the virtual address.



## OsalIoUnmap\(\)<a name="ga0a845edb56df0a35beeea338dc5121aa"></a>

```
static void OsalIoUnmap (void * addr)
```

 **Description:**

Unmaps an I/O virtual address associated with the physical address. 

The virtual address is the one returned by calling  [OsalIoRemap](osal.md#ga281757438906600ef89a13362151d955).

**Parameters:**

<a name="table44469287093521"></a>
<table><thead align="left"><tr id="row1235282846093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p901012602093521"><a name="p901012602093521"></a><a name="p901012602093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1044043720093521"><a name="p1044043720093521"></a><a name="p1044043720093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1882505928093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the virtual address to unmap.</td>
</tr>
</tbody>
</table>

## OsalMDelay\(\)<a name="ga82ddd682a2441a22dd6148f634a6cea4"></a>

```
void OsalMDelay (uint32_t ms)
```

 **Description:**

Describes thread delay, in milliseconds. 

When a thread invokes this function, the CPU is not released. This function returns after waiting for milliseconds.

**Parameters:**

<a name="table1022774385093521"></a>
<table><thead align="left"><tr id="row561442191093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p361770186093521"><a name="p361770186093521"></a><a name="p361770186093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p691906060093521"><a name="p691906060093521"></a><a name="p691906060093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1337475497093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ms</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the delay time, in milliseconds. </td>
</tr>
</tbody>
</table>

## OsalMemAlloc\(\)<a name="ga0a1c85eaad6c1588ed091e0e89b74ed2"></a>

```
void* OsalMemAlloc (size_t size)
```

 **Description:**

Allocates memory of a specified size. 

**Parameters:**

<a name="table2077594270093521"></a>
<table><thead align="left"><tr id="row1045498226093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p825530460093521"><a name="p825530460093521"></a><a name="p825530460093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1168664886093521"><a name="p1168664886093521"></a><a name="p1168664886093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row43983337093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to allocate.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the allocated memory if the operation is successful; returns  **NULL**  otherwise. 



## OsalMemAllocAlign\(\)<a name="gaf6d1b6e5583d9e1ca5abf5048bb3bad9"></a>

```
void* OsalMemAllocAlign (size_t alignment, size_t size )
```

 **Description:**

Allocates memory of a specified size, and aligns the memory address on a given boundary. 

**Parameters:**

<a name="table1022356192093521"></a>
<table><thead align="left"><tr id="row191307803093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1544465458093521"><a name="p1544465458093521"></a><a name="p1544465458093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1847356578093521"><a name="p1847356578093521"></a><a name="p1847356578093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1493977188093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alignment</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the memory boundary alignment. The value must be a power of 2. </td>
</tr>
<tr id="row2003252194093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to allocate.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the allocated memory if the operation is successful; returns  **NULL**  otherwise. 



## OsalMemCalloc\(\)<a name="ga7a6d0f6400e835bcbe9ec655bc9f43ee"></a>

```
void* OsalMemCalloc (size_t size)
```

 **Description:**

Allocates memory of a specified size, and clears the allocated memory. 

**Parameters:**

<a name="table1185139834093521"></a>
<table><thead align="left"><tr id="row260348582093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1184250860093521"><a name="p1184250860093521"></a><a name="p1184250860093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p26966916093521"><a name="p26966916093521"></a><a name="p26966916093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row168262917093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to allocate.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the allocated memory if the operation is successful; returns  **NULL**  otherwise. 



## OsalMemFree\(\)<a name="ga20dc9c415433effea4d481180a50cfa1"></a>

```
void OsalMemFree (void * mem)
```

 **Description:**

Releases memory. 

**Parameters:**

<a name="table564722854093521"></a>
<table><thead align="left"><tr id="row1873332405093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p764962205093521"><a name="p764962205093521"></a><a name="p764962205093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1003734710093521"><a name="p1003734710093521"></a><a name="p1003734710093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1484955123093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory to release. </td>
</tr>
</tbody>
</table>

## OsalMSleep\(\)<a name="ga2361dc099952df28aaef8968f9f4b9a7"></a>

```
void OsalMSleep (uint32_t ms)
```

 **Description:**

Describes thread sleep, in milliseconds. 

When a thread invokes this function, the CPU is released and the thread enters the sleep state.

**Parameters:**

<a name="table1408675208093521"></a>
<table><thead align="left"><tr id="row1131218006093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1585806326093521"><a name="p1585806326093521"></a><a name="p1585806326093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1202621617093521"><a name="p1202621617093521"></a><a name="p1202621617093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1049022840093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ms</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the sleep time, in milliseconds. </td>
</tr>
</tbody>
</table>

## OsalMutexDestroy\(\)<a name="gaa37328265ee97277516f6905f90a41b3"></a>

```
int32_t OsalMutexDestroy (struct [OsalMutex](osalmutex.md) * mutex)
```

 **Description:**

Destroys a mutex. 

**Parameters:**

<a name="table406089045093521"></a>
<table><thead align="left"><tr id="row1346714357093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1357276669093521"><a name="p1357276669093521"></a><a name="p1357276669093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1230321556093521"><a name="p1230321556093521"></a><a name="p1230321556093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row201000781093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex <a href="osalmutex.md">OsalMutex</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table239224020093521"></a>
<table><thead align="left"><tr id="row1547820049093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p487524911093521"><a name="p487524911093521"></a><a name="p487524911093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p755511605093521"><a name="p755511605093521"></a><a name="p755511605093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row94151105093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p961810793093521"><a name="p961810793093521"></a><a name="p961810793093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p283095581093521"><a name="p283095581093521"></a><a name="p283095581093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row785899002093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p360156397093521"><a name="p360156397093521"></a><a name="p360156397093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p285471031093521"><a name="p285471031093521"></a><a name="p285471031093521"></a>Failed to invoke the system function to destroy the mutex. </p>
</td>
</tr>
<tr id="row336470210093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1732055322093521"><a name="p1732055322093521"></a><a name="p1732055322093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1298057439093521"><a name="p1298057439093521"></a><a name="p1298057439093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalMutexInit\(\)<a name="ga9bbc55785f8a533b0b099956bcbe258e"></a>

```
int32_t OsalMutexInit (struct [OsalMutex](osalmutex.md) * mutex)
```

 **Description:**

Initializes a mutex. 

**Parameters:**

<a name="table1199500124093521"></a>
<table><thead align="left"><tr id="row826258337093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p411794405093521"><a name="p411794405093521"></a><a name="p411794405093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p919850580093521"><a name="p919850580093521"></a><a name="p919850580093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1231257494093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex <a href="osalmutex.md">OsalMutex</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1895197038093521"></a>
<table><thead align="left"><tr id="row189932265093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p454953786093521"><a name="p454953786093521"></a><a name="p454953786093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p737020481093521"><a name="p737020481093521"></a><a name="p737020481093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row599954635093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p749536850093521"><a name="p749536850093521"></a><a name="p749536850093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1244173498093521"><a name="p1244173498093521"></a><a name="p1244173498093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1624622066093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719689448093521"><a name="p719689448093521"></a><a name="p719689448093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619897395093521"><a name="p1619897395093521"></a><a name="p1619897395093521"></a>Failed to invoke the system function to initialize the mutex. </p>
</td>
</tr>
<tr id="row1921443345093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p27506715093521"><a name="p27506715093521"></a><a name="p27506715093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1960299123093521"><a name="p1960299123093521"></a><a name="p1960299123093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalMutexLock\(\)<a name="ga45d893bf49a8fb8caf76fa5d31822e0e"></a>

```
int32_t OsalMutexLock (struct [OsalMutex](osalmutex.md) * mutex)
```

 **Description:**

Locks a mutex. 

**Parameters:**

<a name="table1551553464093521"></a>
<table><thead align="left"><tr id="row49178612093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p181318133093521"><a name="p181318133093521"></a><a name="p181318133093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p384846091093521"><a name="p384846091093521"></a><a name="p384846091093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row405461891093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex <a href="osalmutex.md">OsalMutex</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table2065488573093521"></a>
<table><thead align="left"><tr id="row1916532427093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1360531126093521"><a name="p1360531126093521"></a><a name="p1360531126093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p813898030093521"><a name="p813898030093521"></a><a name="p813898030093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row220636761093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2055561816093521"><a name="p2055561816093521"></a><a name="p2055561816093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1243393411093521"><a name="p1243393411093521"></a><a name="p1243393411093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1800435075093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1867534557093521"><a name="p1867534557093521"></a><a name="p1867534557093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946484359093521"><a name="p1946484359093521"></a><a name="p1946484359093521"></a>Failed to invoke the system function to lock the mutex. </p>
</td>
</tr>
<tr id="row1607402534093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p116112542093521"><a name="p116112542093521"></a><a name="p116112542093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1431427986093521"><a name="p1431427986093521"></a><a name="p1431427986093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalMutexTimedLock\(\)<a name="ga57162c8f2e812ef3e5ace498bb85a3b6"></a>

```
int32_t OsalMutexTimedLock (struct [OsalMutex](osalmutex.md) * mutex, uint32_t ms )
```

 **Description:**

Locks a mutex with a specified timeout duration. 

**Parameters:**

<a name="table817975290093521"></a>
<table><thead align="left"><tr id="row553351672093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1999679968093521"><a name="p1999679968093521"></a><a name="p1999679968093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1450898909093521"><a name="p1450898909093521"></a><a name="p1450898909093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row599798071093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex <a href="osalmutex.md">OsalMutex</a>. </td>
</tr>
<tr id="row592572739093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ms</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration, in milliseconds.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table147289613093521"></a>
<table><thead align="left"><tr id="row1050033477093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1899168479093521"><a name="p1899168479093521"></a><a name="p1899168479093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1601897925093521"><a name="p1601897925093521"></a><a name="p1601897925093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row581409427093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p759325735093521"><a name="p759325735093521"></a><a name="p759325735093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p163514551093521"><a name="p163514551093521"></a><a name="p163514551093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1334103613093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870344189093521"><a name="p870344189093521"></a><a name="p870344189093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1732435844093521"><a name="p1732435844093521"></a><a name="p1732435844093521"></a>Failed to invoke the system function to lock the mutex. </p>
</td>
</tr>
<tr id="row1558291591093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703353400093521"><a name="p703353400093521"></a><a name="p703353400093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p64426278093521"><a name="p64426278093521"></a><a name="p64426278093521"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1243274705093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p3783537093521"><a name="p3783537093521"></a><a name="p3783537093521"></a>HDF_ERR_TIMEOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p110706273093521"><a name="p110706273093521"></a><a name="p110706273093521"></a>Timeout occurs. </p>
</td>
</tr>
</tbody>
</table>

## OsalMutexUnlock\(\)<a name="gae76ffb4db66c988be5209e0dfdc7a35f"></a>

```
int32_t OsalMutexUnlock (struct [OsalMutex](osalmutex.md) * mutex)
```

 **Description:**

Unlocks a mutex. 

**Parameters:**

<a name="table1329475183093521"></a>
<table><thead align="left"><tr id="row1563548485093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p577176219093521"><a name="p577176219093521"></a><a name="p577176219093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p574067733093521"><a name="p574067733093521"></a><a name="p574067733093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row730090141093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mutex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex <a href="osalmutex.md">OsalMutex</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table2144607315093521"></a>
<table><thead align="left"><tr id="row1660079910093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p648366641093521"><a name="p648366641093521"></a><a name="p648366641093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2118426647093521"><a name="p2118426647093521"></a><a name="p2118426647093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2103061039093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816247190093521"><a name="p816247190093521"></a><a name="p816247190093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p677233774093521"><a name="p677233774093521"></a><a name="p677233774093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1467451433093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2134627778093521"><a name="p2134627778093521"></a><a name="p2134627778093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p520795343093521"><a name="p520795343093521"></a><a name="p520795343093521"></a>Failed to invoke the system function to unlock the mutex. </p>
</td>
</tr>
<tr id="row1305760878093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1893938508093521"><a name="p1893938508093521"></a><a name="p1893938508093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177576138093521"><a name="p1177576138093521"></a><a name="p1177576138093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalReadFirmware\(\)<a name="ga2b721d36c177786841cd05cecdb01034"></a>

```
int32_t OsalReadFirmware (struct [OsalFirmware](osalfirmware.md) * fw, struct [OsalFwBlock](osalfwblock.md) * block )
```

 **Description:**

Releases a firmware file. 

After the firmware file is read, this function is called to release the firmware file.

**Parameters:**

<a name="table244635164093521"></a>
<table><thead align="left"><tr id="row1709208285093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1523757635093521"><a name="p1523757635093521"></a><a name="p1523757635093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p192909227093521"><a name="p192909227093521"></a><a name="p192909227093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row636559392093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the firmware file <a href="osalfirmware.md">OsalFirmware</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table577370191093521"></a>
<table><thead align="left"><tr id="row941132320093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p382873248093521"><a name="p382873248093521"></a><a name="p382873248093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p458322835093521"><a name="p458322835093521"></a><a name="p458322835093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1311054791093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1297208450093521"><a name="p1297208450093521"></a><a name="p1297208450093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53893299093521"><a name="p53893299093521"></a><a name="p53893299093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1194358195093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2045406389093521"><a name="p2045406389093521"></a><a name="p2045406389093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1957226034093521"><a name="p1957226034093521"></a><a name="p1957226034093521"></a>Failed to invoke the system function. </p>
</td>
</tr>
<tr id="row1309652211093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657356891093521"><a name="p1657356891093521"></a><a name="p1657356891093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p778320359093521"><a name="p778320359093521"></a><a name="p778320359093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalRegisterIrq\(\)<a name="gade084a1942c1672f2148ccf8f6c06331"></a>

```
int32_t OsalRegisterIrq (uint32_t irqId, uint32_t config, [OsalIRQHandle](osal.md#gab671a9e177f622a98af9ca1bd93198eb) handle, const char * name, void * dev )
```

 **Description:**

Registers an IRQ. 

**Parameters:**

<a name="table1184519802093521"></a>
<table><thead align="left"><tr id="row1853609979093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1402732521093521"><a name="p1402732521093521"></a><a name="p1402732521093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p388686200093521"><a name="p388686200093521"></a><a name="p388686200093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row224644732093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">irqId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the IRQ ID. </td>
</tr>
<tr id="row1126982053093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">config</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the interrupt trigger mode. For details, see <a href="osal.md#ga78cd126b10424753db6f39f9b72ea124">OSAL_IRQ_TRIGGER_MODE</a>. </td>
</tr>
<tr id="row471454655093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the interrupt processing function. </td>
</tr>
<tr id="row1336425043093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the device name for registering an IRQ. </td>
</tr>
<tr id="row26870052093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the parameter passed to the interrupt processing function.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1876895828093521"></a>
<table><thead align="left"><tr id="row1864926967093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p332922166093521"><a name="p332922166093521"></a><a name="p332922166093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2023278628093521"><a name="p2023278628093521"></a><a name="p2023278628093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1578963405093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1641237333093521"><a name="p1641237333093521"></a><a name="p1641237333093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p820894079093521"><a name="p820894079093521"></a><a name="p820894079093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row357280987093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205119571093521"><a name="p205119571093521"></a><a name="p205119571093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p799931318093521"><a name="p799931318093521"></a><a name="p799931318093521"></a>Failed to invoke the system function to register the IRQ. </p>
</td>
</tr>
<tr id="row604752794093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1310003900093521"><a name="p1310003900093521"></a><a name="p1310003900093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375857338093521"><a name="p1375857338093521"></a><a name="p1375857338093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalReleaseFirmware\(\)<a name="gadfccddc78411a76ae8f4af4282da12f0"></a>

```
int32_t OsalReleaseFirmware (struct [OsalFirmware](osalfirmware.md) * fw)
```

 **Description:**

Release firmware resource

**Parameters:**

<a name="table1651900777093521"></a>
<table><thead align="left"><tr id="row1371542770093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1751911928093521"><a name="p1751911928093521"></a><a name="p1751911928093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p381874885093521"><a name="p381874885093521"></a><a name="p381874885093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2022407405093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">fw Firmware parameter, see detail in <a href="osalfirmware.md">OsalFirmware</a> block Firmware data block, see detail in hdf_FWBlock </td>
</tr>
</tbody>
</table>

**Returns:**

: true or false 



## OsalRequestFirmware\(\)<a name="ga428b9de7fb95a20ab9e25b47a7d4272c"></a>

```
int32_t OsalRequestFirmware (struct [OsalFirmware](osalfirmware.md) * fw, const char * fwName, void * device )
```

 **Description:**

Requests a firmware file based on its name and device information. 

**Parameters:**

<a name="table28904295093521"></a>
<table><thead align="left"><tr id="row2027642991093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p936592057093521"><a name="p936592057093521"></a><a name="p936592057093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p108724128093521"><a name="p108724128093521"></a><a name="p108724128093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1454153701093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the firmware file <a href="osalfirmware.md">OsalFirmware</a>, which cannot be empty. </td>
</tr>
<tr id="row202346089093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fwName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the firmware file name, which cannot be empty. </td>
</tr>
<tr id="row530795578093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">device</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the information about the device that requests the firmware file.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table334145677093521"></a>
<table><thead align="left"><tr id="row1534669908093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p675280156093521"><a name="p675280156093521"></a><a name="p675280156093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p477129691093521"><a name="p477129691093521"></a><a name="p477129691093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row326668569093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1088944081093521"><a name="p1088944081093521"></a><a name="p1088944081093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p435089246093521"><a name="p435089246093521"></a><a name="p435089246093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1217032533093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648343634093521"><a name="p1648343634093521"></a><a name="p1648343634093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088663542093521"><a name="p2088663542093521"></a><a name="p2088663542093521"></a>Failed to invoke the system function. </p>
</td>
</tr>
<tr id="row764458432093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702738635093521"><a name="p702738635093521"></a><a name="p702738635093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1166610291093521"><a name="p1166610291093521"></a><a name="p1166610291093521"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1381549732093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1792148446093521"><a name="p1792148446093521"></a><a name="p1792148446093521"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397882342093521"><a name="p397882342093521"></a><a name="p397882342093521"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

## OsalSeekFirmware\(\)<a name="ga41ae4dade9246f3b30efd276cbd43474"></a>

```
int32_t OsalSeekFirmware (struct [OsalFirmware](osalfirmware.md) * fw, uint32_t offset )
```

 **Description:**

Reads a firmware file. 

**Parameters:**

<a name="table2071591376093521"></a>
<table><thead align="left"><tr id="row808439140093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1141989733093521"><a name="p1141989733093521"></a><a name="p1141989733093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p119092718093521"><a name="p119092718093521"></a><a name="p119092718093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1402723604093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the firmware file <a href="osalfirmware.md">OsalFirmware</a>. </td>
</tr>
<tr id="row1680364883093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">block</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the firmware block to read. For details, see <a href="osalfwblock.md">OsalFwBlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table80447749093521"></a>
<table><thead align="left"><tr id="row585611795093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p881624816093521"><a name="p881624816093521"></a><a name="p881624816093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1686035068093521"><a name="p1686035068093521"></a><a name="p1686035068093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1796456439093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727935664093521"><a name="p1727935664093521"></a><a name="p1727935664093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1042250357093521"><a name="p1042250357093521"></a><a name="p1042250357093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row73427280093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1299080357093521"><a name="p1299080357093521"></a><a name="p1299080357093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1287446129093521"><a name="p1287446129093521"></a><a name="p1287446129093521"></a>Failed to invoke the system function. </p>
</td>
</tr>
<tr id="row1728902919093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p831364171093521"><a name="p831364171093521"></a><a name="p831364171093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1380664988093521"><a name="p1380664988093521"></a><a name="p1380664988093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSemDestroy\(\)<a name="ga0b6642005b8a128ac01f69385bd6969f"></a>

```
int32_t OsalSemDestroy (struct [OsalSem](osalsem.md) * sem)
```

 **Description:**

Destroys a semaphore. 

**Parameters:**

<a name="table904967034093521"></a>
<table><thead align="left"><tr id="row1304167280093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p455682466093521"><a name="p455682466093521"></a><a name="p455682466093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1861678041093521"><a name="p1861678041093521"></a><a name="p1861678041093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1088133433093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore <a href="osalsem.md">OsalSem</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table2153197093521"></a>
<table><thead align="left"><tr id="row43876968093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p861499893093521"><a name="p861499893093521"></a><a name="p861499893093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p912340282093521"><a name="p912340282093521"></a><a name="p912340282093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row570937361093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p711868166093521"><a name="p711868166093521"></a><a name="p711868166093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152343046093521"><a name="p1152343046093521"></a><a name="p1152343046093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1208586192093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1668469689093521"><a name="p1668469689093521"></a><a name="p1668469689093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748457745093521"><a name="p748457745093521"></a><a name="p748457745093521"></a>Failed to invoke the system function to destroy the semaphore. </p>
</td>
</tr>
<tr id="row433176204093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250228616093521"><a name="p250228616093521"></a><a name="p250228616093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p13815533093521"><a name="p13815533093521"></a><a name="p13815533093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSemInit\(\)<a name="ga7e4325c951479e93abe072290162da0b"></a>

```
int32_t OsalSemInit (struct [OsalSem](osalsem.md) * sem, uint32_t value )
```

 **Description:**

Initializes a semaphore. 

**Parameters:**

<a name="table238272019093521"></a>
<table><thead align="left"><tr id="row1166632163093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p840122707093521"><a name="p840122707093521"></a><a name="p840122707093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1610505218093521"><a name="p1610505218093521"></a><a name="p1610505218093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2134997091093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore <a href="osalsem.md">OsalSem</a>. </td>
</tr>
<tr id="row1776196128093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the initial value of the semaphore.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1734002360093521"></a>
<table><thead align="left"><tr id="row519245600093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1460744338093521"><a name="p1460744338093521"></a><a name="p1460744338093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p255165560093521"><a name="p255165560093521"></a><a name="p255165560093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row868360538093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875056236093521"><a name="p875056236093521"></a><a name="p875056236093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79053285093521"><a name="p79053285093521"></a><a name="p79053285093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row979325452093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p928849225093521"><a name="p928849225093521"></a><a name="p928849225093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1265201866093521"><a name="p1265201866093521"></a><a name="p1265201866093521"></a>Failed to invoke the system function to initialize the semaphore. </p>
</td>
</tr>
<tr id="row1825360243093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725348931093521"><a name="p725348931093521"></a><a name="p725348931093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p863636940093521"><a name="p863636940093521"></a><a name="p863636940093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSemPost\(\)<a name="gadc3205b416d3fc8e1fa9c332b82e634a"></a>

```
int32_t OsalSemPost (struct [OsalSem](osalsem.md) * sem)
```

 **Description:**

Releases a semaphore. 

**Parameters:**

<a name="table1557365650093521"></a>
<table><thead align="left"><tr id="row129766120093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2050017414093521"><a name="p2050017414093521"></a><a name="p2050017414093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1527748340093521"><a name="p1527748340093521"></a><a name="p1527748340093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row603791743093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore <a href="osalsem.md">OsalSem</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table373590074093521"></a>
<table><thead align="left"><tr id="row2055075430093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1477193849093521"><a name="p1477193849093521"></a><a name="p1477193849093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p518830810093521"><a name="p518830810093521"></a><a name="p518830810093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1788418260093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619466100093521"><a name="p1619466100093521"></a><a name="p1619466100093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1944125253093521"><a name="p1944125253093521"></a><a name="p1944125253093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1438659910093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308531189093521"><a name="p308531189093521"></a><a name="p308531189093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1081083685093521"><a name="p1081083685093521"></a><a name="p1081083685093521"></a>Failed to invoke the system function to release the semaphore. </p>
</td>
</tr>
<tr id="row388238880093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722470624093521"><a name="p722470624093521"></a><a name="p722470624093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932359545093521"><a name="p1932359545093521"></a><a name="p1932359545093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSemWait\(\)<a name="ga0000b9ee1421950d5b3a04cbc839c6af"></a>

```
int32_t OsalSemWait (struct [OsalSem](osalsem.md) * sem, uint32_t ms )
```

 **Description:**

Waits for a semaphore. 

**Parameters:**

<a name="table465001977093521"></a>
<table><thead align="left"><tr id="row2080217055093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1322293818093521"><a name="p1322293818093521"></a><a name="p1322293818093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p461920542093521"><a name="p461920542093521"></a><a name="p461920542093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1735557068093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore <a href="osalsem.md">OsalSem</a>. </td>
</tr>
<tr id="row1565466725093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ms</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout interval.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table106006279093521"></a>
<table><thead align="left"><tr id="row361232480093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1248554513093521"><a name="p1248554513093521"></a><a name="p1248554513093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1689752082093521"><a name="p1689752082093521"></a><a name="p1689752082093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row706527519093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826300568093521"><a name="p1826300568093521"></a><a name="p1826300568093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800666357093521"><a name="p800666357093521"></a><a name="p800666357093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1073172211093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1899621321093521"><a name="p1899621321093521"></a><a name="p1899621321093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1806204828093521"><a name="p1806204828093521"></a><a name="p1806204828093521"></a>Failed to invoke the system function to wait for the semaphore. </p>
</td>
</tr>
<tr id="row2131403438093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382381572093521"><a name="p1382381572093521"></a><a name="p1382381572093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p394372631093521"><a name="p394372631093521"></a><a name="p394372631093521"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row614778532093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1889956427093521"><a name="p1889956427093521"></a><a name="p1889956427093521"></a>HDF_ERR_TIMEOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1915248446093521"><a name="p1915248446093521"></a><a name="p1915248446093521"></a>Timeout occurs. </p>
</td>
</tr>
</tbody>
</table>

## OsalSleep\(\)<a name="ga8b9ca3498c54b11dcbe88a2a456f23ab"></a>

```
void OsalSleep (uint32_t sec)
```

 **Description:**

Describes thread sleep, in seconds. 

When a thread invokes this function, the CPU is released and the thread enters the sleep state.

**Parameters:**

<a name="table745940451093521"></a>
<table><thead align="left"><tr id="row925402565093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p704064993093521"><a name="p704064993093521"></a><a name="p704064993093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p371834854093521"><a name="p371834854093521"></a><a name="p371834854093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1490877755093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sec</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the sleep time, in seconds. </td>
</tr>
</tbody>
</table>

## OsalSpinDestroy\(\)<a name="gacd3824f292ddef395bd1a4a7b5546470"></a>

```
int32_t OsalSpinDestroy ([OsalSpinlock](osalspinlock.md) * spinlock)
```

 **Description:**

Destroys a spinlock. 

**Parameters:**

<a name="table822961561093521"></a>
<table><thead align="left"><tr id="row1752816857093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1294473357093521"><a name="p1294473357093521"></a><a name="p1294473357093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1043808490093521"><a name="p1043808490093521"></a><a name="p1043808490093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1503386942093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1619375814093521"></a>
<table><thead align="left"><tr id="row899249698093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1909567176093521"><a name="p1909567176093521"></a><a name="p1909567176093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p83198129093521"><a name="p83198129093521"></a><a name="p83198129093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row880189681093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315009739093521"><a name="p315009739093521"></a><a name="p315009739093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1405345397093521"><a name="p1405345397093521"></a><a name="p1405345397093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1701430769093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982018101093521"><a name="p982018101093521"></a><a name="p982018101093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517747135093521"><a name="p517747135093521"></a><a name="p517747135093521"></a>Failed to invoke the system function to destroy the spinlock. </p>
</td>
</tr>
<tr id="row1830311350093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1532625814093521"><a name="p1532625814093521"></a><a name="p1532625814093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1928969982093521"><a name="p1928969982093521"></a><a name="p1928969982093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinInit\(\)<a name="gae36a2d6e4e0191273c9f86a918befb5c"></a>

```
int32_t OsalSpinInit ([OsalSpinlock](osalspinlock.md) * spinlock)
```

 **Description:**

Initializes a spinlock. 

**Parameters:**

<a name="table1443716175093521"></a>
<table><thead align="left"><tr id="row1264999719093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1717060825093521"><a name="p1717060825093521"></a><a name="p1717060825093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1515485298093521"><a name="p1515485298093521"></a><a name="p1515485298093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row811480313093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table363566823093521"></a>
<table><thead align="left"><tr id="row1864188590093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p379310259093521"><a name="p379310259093521"></a><a name="p379310259093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p318093630093521"><a name="p318093630093521"></a><a name="p318093630093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row921244162093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1289751083093521"><a name="p1289751083093521"></a><a name="p1289751083093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701447198093521"><a name="p1701447198093521"></a><a name="p1701447198093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1830879923093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1495493940093521"><a name="p1495493940093521"></a><a name="p1495493940093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p538541649093521"><a name="p538541649093521"></a><a name="p538541649093521"></a>Failed to invoke the system function to initialize the spinlock. </p>
</td>
</tr>
<tr id="row1298243604093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1637223667093521"><a name="p1637223667093521"></a><a name="p1637223667093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1988761193093521"><a name="p1988761193093521"></a><a name="p1988761193093521"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row366023108093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247540475093521"><a name="p1247540475093521"></a><a name="p1247540475093521"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800915405093521"><a name="p1800915405093521"></a><a name="p1800915405093521"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinLock\(\)<a name="gae1c4b9ac8ea2a4820d73c20ae017dbd7"></a>

```
int32_t OsalSpinLock ([OsalSpinlock](osalspinlock.md) * spinlock)
```

 **Description:**

Obtains a spinlock. 

**Parameters:**

<a name="table668244874093521"></a>
<table><thead align="left"><tr id="row1635603429093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p844567040093521"><a name="p844567040093521"></a><a name="p844567040093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p832640795093521"><a name="p832640795093521"></a><a name="p832640795093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2089291082093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table922470450093521"></a>
<table><thead align="left"><tr id="row473339860093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1104946409093521"><a name="p1104946409093521"></a><a name="p1104946409093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p106352127093521"><a name="p106352127093521"></a><a name="p106352127093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row191105912093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2004423625093521"><a name="p2004423625093521"></a><a name="p2004423625093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941575384093521"><a name="p941575384093521"></a><a name="p941575384093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1536785688093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1233194406093521"><a name="p1233194406093521"></a><a name="p1233194406093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1024442253093521"><a name="p1024442253093521"></a><a name="p1024442253093521"></a>Failed to invoke the system function to obtain the spinlock. </p>
</td>
</tr>
<tr id="row729958149093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586814695093521"><a name="p586814695093521"></a><a name="p586814695093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1602018924093521"><a name="p1602018924093521"></a><a name="p1602018924093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinLockIrq\(\)<a name="ga7d409ec573a06078112a8ffae14afce5"></a>

```
int32_t OsalSpinLockIrq ([OsalSpinlock](osalspinlock.md) * spinlock)
```

 **Description:**

Obtains a spinlock and disables the IRQ. 

**Parameters:**

<a name="table40722695093521"></a>
<table><thead align="left"><tr id="row2030753186093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p763285886093521"><a name="p763285886093521"></a><a name="p763285886093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1178624958093521"><a name="p1178624958093521"></a><a name="p1178624958093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1897400904093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1876687399093521"></a>
<table><thead align="left"><tr id="row1806680781093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p449415356093521"><a name="p449415356093521"></a><a name="p449415356093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p429135025093521"><a name="p429135025093521"></a><a name="p429135025093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row973949314093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996797570093521"><a name="p996797570093521"></a><a name="p996797570093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p299427330093521"><a name="p299427330093521"></a><a name="p299427330093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1998702232093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1803387146093521"><a name="p1803387146093521"></a><a name="p1803387146093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1582796610093521"><a name="p1582796610093521"></a><a name="p1582796610093521"></a>Failed to invoke the system function to obtain the spinlock. </p>
</td>
</tr>
<tr id="row103887546093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p579149011093521"><a name="p579149011093521"></a><a name="p579149011093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209410764093521"><a name="p1209410764093521"></a><a name="p1209410764093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinLockIrqSave\(\)<a name="gab711d8d56055e78dd85f84bc530a4d3f"></a>

```
int32_t OsalSpinLockIrqSave ([OsalSpinlock](osalspinlock.md) * spinlock, uint32_t * flags )
```

 **Description:**

Obtains a spinlock, disables the IRQ, and saves its status. 

**Parameters:**

<a name="table1690076891093521"></a>
<table><thead align="left"><tr id="row500355588093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p342507143093521"><a name="p342507143093521"></a><a name="p342507143093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1828545511093521"><a name="p1828545511093521"></a><a name="p1828545511093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1864330750093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>. </td>
</tr>
<tr id="row1488943443093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the status of the IRQ register.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table931771289093521"></a>
<table><thead align="left"><tr id="row954612244093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1501968326093521"><a name="p1501968326093521"></a><a name="p1501968326093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p985996030093521"><a name="p985996030093521"></a><a name="p985996030093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row644348053093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327111868093521"><a name="p1327111868093521"></a><a name="p1327111868093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p501936734093521"><a name="p501936734093521"></a><a name="p501936734093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1126102588093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105538886093521"><a name="p105538886093521"></a><a name="p105538886093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809567556093521"><a name="p1809567556093521"></a><a name="p1809567556093521"></a>Failed to invoke the system function to obtain the spinlock. </p>
</td>
</tr>
<tr id="row1839973397093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1645370166093521"><a name="p1645370166093521"></a><a name="p1645370166093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2133748811093521"><a name="p2133748811093521"></a><a name="p2133748811093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinUnlock\(\)<a name="gada1f1826b19dc900af370a2bcd9681b9"></a>

```
int32_t OsalSpinUnlock ([OsalSpinlock](osalspinlock.md) * spinlock)
```

 **Description:**

Releases a spinlock. 

**Parameters:**

<a name="table268834174093521"></a>
<table><thead align="left"><tr id="row98462943093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p619376178093521"><a name="p619376178093521"></a><a name="p619376178093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p860590225093521"><a name="p860590225093521"></a><a name="p860590225093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1205092893093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table551558764093521"></a>
<table><thead align="left"><tr id="row488313693093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1331950316093521"><a name="p1331950316093521"></a><a name="p1331950316093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2071741838093521"><a name="p2071741838093521"></a><a name="p2071741838093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1295652799093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1042647414093521"><a name="p1042647414093521"></a><a name="p1042647414093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p513267514093521"><a name="p513267514093521"></a><a name="p513267514093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row589319962093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648343793093521"><a name="p1648343793093521"></a><a name="p1648343793093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1564675793093521"><a name="p1564675793093521"></a><a name="p1564675793093521"></a>Failed to invoke the system function to release the spinlock. </p>
</td>
</tr>
<tr id="row1057859837093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1759305816093521"><a name="p1759305816093521"></a><a name="p1759305816093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289387556093521"><a name="p289387556093521"></a><a name="p289387556093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinUnlockIrq\(\)<a name="ga7d7848d572fbda413b3b5770e95a234e"></a>

```
int32_t OsalSpinUnlockIrq ([OsalSpinlock](osalspinlock.md) * spinlock)
```

 **Description:**

Releases a spinlock and enables the IRQ. 

**Parameters:**

<a name="table550353972093521"></a>
<table><thead align="left"><tr id="row1476733259093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p693035425093521"><a name="p693035425093521"></a><a name="p693035425093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2141596563093521"><a name="p2141596563093521"></a><a name="p2141596563093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row559780597093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table837406315093521"></a>
<table><thead align="left"><tr id="row1557043701093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p496370346093521"><a name="p496370346093521"></a><a name="p496370346093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p651265557093521"><a name="p651265557093521"></a><a name="p651265557093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1787819998093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835952752093521"><a name="p835952752093521"></a><a name="p835952752093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174130771093521"><a name="p174130771093521"></a><a name="p174130771093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row917567525093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278163446093521"><a name="p278163446093521"></a><a name="p278163446093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472404514093521"><a name="p1472404514093521"></a><a name="p1472404514093521"></a>Failed to invoke the system function to release the spinlock. </p>
</td>
</tr>
<tr id="row1808238753093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p534047617093521"><a name="p534047617093521"></a><a name="p534047617093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802149342093521"><a name="p1802149342093521"></a><a name="p1802149342093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalSpinUnlockIrqRestore\(\)<a name="ga3be4dbde6c9ae740b012e49ab90e7a8a"></a>

```
int32_t OsalSpinUnlockIrqRestore ([OsalSpinlock](osalspinlock.md) * spinlock, uint32_t * flags )
```

 **Description:**

Releases a spinlock, enables the IRQ, and restores the saved IRQ status. 

**Parameters:**

<a name="table1790659883093521"></a>
<table><thead align="left"><tr id="row305844036093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p636408764093521"><a name="p636408764093521"></a><a name="p636408764093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p878726028093521"><a name="p878726028093521"></a><a name="p878726028093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row108144773093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">spinlock</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spinlock <a href="osalspinlock.md">OsalSpinlock</a>. </td>
</tr>
<tr id="row1768264409093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the value used to restore the IRQ register.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1486503507093521"></a>
<table><thead align="left"><tr id="row1457398876093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1716726527093521"><a name="p1716726527093521"></a><a name="p1716726527093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p917301754093521"><a name="p917301754093521"></a><a name="p917301754093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row938883699093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380329133093521"><a name="p380329133093521"></a><a name="p380329133093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p912368141093521"><a name="p912368141093521"></a><a name="p912368141093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row560189185093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1533017971093521"><a name="p1533017971093521"></a><a name="p1533017971093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1251219506093521"><a name="p1251219506093521"></a><a name="p1251219506093521"></a>Failed to invoke the system function to release the spinlock. </p>
</td>
</tr>
<tr id="row109851891093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500114003093521"><a name="p500114003093521"></a><a name="p500114003093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120202244093521"><a name="p1120202244093521"></a><a name="p1120202244093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalTestBit\(\)<a name="gaf02c15a3593cac4add3f661b63aebf81"></a>

```
int32_t OsalTestBit (unsigned long nr, const volatile unsigned long * addr )
```

 **Description:**

Tests the value of a specified bit of a variable. 

**Parameters:**

<a name="table916058936093521"></a>
<table><thead align="left"><tr id="row1991243892093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1309112267093521"><a name="p1309112267093521"></a><a name="p1309112267093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1528044443093521"><a name="p1528044443093521"></a><a name="p1528044443093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row235964707093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the bit of the variable. The value ranges from <strong id="b2049885999093521"><a name="b2049885999093521"></a><a name="b2049885999093521"></a>0</strong> to <strong id="b2103229644093521"><a name="b2103229644093521"></a><a name="b2103229644093521"></a>31</strong>. </td>
</tr>
<tr id="row1913854735093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the bit value. 



## OsalTestClearBit\(\)<a name="ga8665e70c704921f443fd2db8193ff7cc"></a>

```
int32_t OsalTestClearBit (unsigned long nr, volatile unsigned long * addr )
```

 **Description:**

Clears the value of a specified bit of the variable and returns the bit value before clearing. 

**Parameters:**

<a name="table682553742093521"></a>
<table><thead align="left"><tr id="row719302163093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2076750012093521"><a name="p2076750012093521"></a><a name="p2076750012093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2036318834093521"><a name="p2036318834093521"></a><a name="p2036318834093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1423828217093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the bit of the variable. The value ranges from <strong id="b1672676262093521"><a name="b1672676262093521"></a><a name="b1672676262093521"></a>0</strong> to <strong id="b1435482737093521"><a name="b1435482737093521"></a><a name="b1435482737093521"></a>31</strong>. </td>
</tr>
<tr id="row1907690895093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the bit value before the bit is cleared. 



## OsalTestSetBit\(\)<a name="gac0ff99812a327a4a595802a23b41b46f"></a>

```
int32_t OsalTestSetBit (unsigned long nr, volatile unsigned long * addr )
```

 **Description:**

Sets the value of a specified bit of the variable and returns the bit value before the setting. 

**Parameters:**

<a name="table356546523093521"></a>
<table><thead align="left"><tr id="row1083776219093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p190335564093521"><a name="p190335564093521"></a><a name="p190335564093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p104729399093521"><a name="p104729399093521"></a><a name="p104729399093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2057268345093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the bit of the variable. The value ranges from <strong id="b762807666093521"><a name="b762807666093521"></a><a name="b762807666093521"></a>0</strong> to <strong id="b553445990093521"><a name="b553445990093521"></a><a name="b553445990093521"></a>31</strong>. </td>
</tr>
<tr id="row519703725093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the bit value before the setting. 



## OsalThreadCreate\(\)<a name="gad598b3f4b91f5e6aeeaf7b8a6e507f1e"></a>

```
int32_t OsalThreadCreate (struct [OsalThread](osalthread.md) * thread, [OsalThreadEntry](osal.md#ga21ea0f87d53e65ec86a424c532d688d8) threadEntry, void * entryPara )
```

 **Description:**

Creates a thread. 

**Parameters:**

<a name="table266948896093521"></a>
<table><thead align="left"><tr id="row1242632803093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2049287982093521"><a name="p2049287982093521"></a><a name="p2049287982093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1835497305093521"><a name="p1835497305093521"></a><a name="p1835497305093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2092301883093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread <a href="osalthread.md">OsalThread</a>. </td>
</tr>
<tr id="row188125892093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">threadEntry</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread callback function <a href="osal.md#ga21ea0f87d53e65ec86a424c532d688d8">OsalThreadEntry</a>. </td>
</tr>
<tr id="row1423691662093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">entryPara</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the parameter passed to the thread callback function.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1629468608093521"></a>
<table><thead align="left"><tr id="row102429885093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1992531116093521"><a name="p1992531116093521"></a><a name="p1992531116093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1229875234093521"><a name="p1229875234093521"></a><a name="p1229875234093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row133097942093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196453106093521"><a name="p196453106093521"></a><a name="p196453106093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51702608093521"><a name="p51702608093521"></a><a name="p51702608093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1526187328093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1979932205093521"><a name="p1979932205093521"></a><a name="p1979932205093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p766065172093521"><a name="p766065172093521"></a><a name="p766065172093521"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1191017148093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p162261553093521"><a name="p162261553093521"></a><a name="p162261553093521"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p133289942093521"><a name="p133289942093521"></a><a name="p133289942093521"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

## OsalThreadDestroy\(\)<a name="ga223ce6b94770348a93168525c536e6f9"></a>

```
int32_t OsalThreadDestroy (struct [OsalThread](osalthread.md) * thread)
```

 **Description:**

Destroys a thread. 

**Parameters:**

<a name="table1328315295093521"></a>
<table><thead align="left"><tr id="row1859114074093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1210268245093521"><a name="p1210268245093521"></a><a name="p1210268245093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1272340418093521"><a name="p1272340418093521"></a><a name="p1272340418093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1638380865093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread <a href="osalthread.md">OsalThread</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1045772147093521"></a>
<table><thead align="left"><tr id="row1348383959093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p360271169093521"><a name="p360271169093521"></a><a name="p360271169093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p40545609093521"><a name="p40545609093521"></a><a name="p40545609093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row390523122093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704971343093521"><a name="p704971343093521"></a><a name="p704971343093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124787626093521"><a name="p124787626093521"></a><a name="p124787626093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1132423101093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p694602538093521"><a name="p694602538093521"></a><a name="p694602538093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881610382093521"><a name="p1881610382093521"></a><a name="p1881610382093521"></a>Failed to invoke the system function to destroy the thread. </p>
</td>
</tr>
<tr id="row467221372093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230435965093521"><a name="p1230435965093521"></a><a name="p1230435965093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p599301506093521"><a name="p599301506093521"></a><a name="p599301506093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalThreadResume\(\)<a name="ga32f0b5c622518b7453f758d95b137a94"></a>

```
int32_t OsalThreadResume (struct [OsalThread](osalthread.md) * thread)
```

 **Description:**

Resumes a thread. 

**Parameters:**

<a name="table1795105956093521"></a>
<table><thead align="left"><tr id="row1322052170093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p655041879093521"><a name="p655041879093521"></a><a name="p655041879093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1362048498093521"><a name="p1362048498093521"></a><a name="p1362048498093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1063617249093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread <a href="osalthread.md">OsalThread</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table542823119093521"></a>
<table><thead align="left"><tr id="row607711121093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1857897072093521"><a name="p1857897072093521"></a><a name="p1857897072093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p621170363093521"><a name="p621170363093521"></a><a name="p621170363093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2067085067093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p747153165093521"><a name="p747153165093521"></a><a name="p747153165093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p840732892093521"><a name="p840732892093521"></a><a name="p840732892093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row167699749093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p543855519093521"><a name="p543855519093521"></a><a name="p543855519093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868847819093521"><a name="p1868847819093521"></a><a name="p1868847819093521"></a>Failed to invoke the system function to resume the thread. </p>
</td>
</tr>
<tr id="row1138851720093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1610980895093521"><a name="p1610980895093521"></a><a name="p1610980895093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2039482809093521"><a name="p2039482809093521"></a><a name="p2039482809093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalThreadStart\(\)<a name="ga74c93bd48d27cde830451f63b224307a"></a>

```
int32_t OsalThreadStart (struct [OsalThread](osalthread.md) * thread, const struct [OsalThreadParam](osalthreadparam.md) * param )
```

 **Description:**

Starts a thread. 

**Parameters:**

<a name="table370110981093521"></a>
<table><thead align="left"><tr id="row360391006093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p154814050093521"><a name="p154814050093521"></a><a name="p154814050093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1717821813093521"><a name="p1717821813093521"></a><a name="p1717821813093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row479048002093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread <a href="osalthread.md">OsalThread</a>. </td>
</tr>
<tr id="row1654689272093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the parameter used to start a thread. For details, see <a href="osalthreadparam.md">OsalThreadParam</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1995890697093521"></a>
<table><thead align="left"><tr id="row1757837470093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1901575386093521"><a name="p1901575386093521"></a><a name="p1901575386093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p162363259093521"><a name="p162363259093521"></a><a name="p162363259093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1381601222093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1893883599093521"><a name="p1893883599093521"></a><a name="p1893883599093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775734623093521"><a name="p1775734623093521"></a><a name="p1775734623093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1623747835093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p207590758093521"><a name="p207590758093521"></a><a name="p207590758093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1243086449093521"><a name="p1243086449093521"></a><a name="p1243086449093521"></a>Failed to invoke the system function to start the thread. </p>
</td>
</tr>
<tr id="row1469037034093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p203288703093521"><a name="p203288703093521"></a><a name="p203288703093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p461900824093521"><a name="p461900824093521"></a><a name="p461900824093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalThreadSuspend\(\)<a name="gad556075f625d01557c0075a2c092a1da"></a>

```
int32_t OsalThreadSuspend (struct [OsalThread](osalthread.md) * thread)
```

 **Description:**

Suspends a thread. 

**Parameters:**

<a name="table80918178093521"></a>
<table><thead align="left"><tr id="row1391917534093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p663484946093521"><a name="p663484946093521"></a><a name="p663484946093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p496841612093521"><a name="p496841612093521"></a><a name="p496841612093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1763986992093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread <a href="osalthread.md">OsalThread</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1021970579093521"></a>
<table><thead align="left"><tr id="row89363451093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1230506840093521"><a name="p1230506840093521"></a><a name="p1230506840093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1274171763093521"><a name="p1274171763093521"></a><a name="p1274171763093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2006451566093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549665311093521"><a name="p549665311093521"></a><a name="p549665311093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1494332719093521"><a name="p1494332719093521"></a><a name="p1494332719093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row426131616093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p628571284093521"><a name="p628571284093521"></a><a name="p628571284093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508258870093521"><a name="p508258870093521"></a><a name="p508258870093521"></a>Failed to invoke the system function to suspend the thread. </p>
</td>
</tr>
<tr id="row1343182080093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758661319093521"><a name="p758661319093521"></a><a name="p758661319093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1916613727093521"><a name="p1916613727093521"></a><a name="p1916613727093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalTimerCreate\(\)<a name="ga879d9a437e1423021f95cb9341f0d6af"></a>

```
int32_t OsalTimerCreate ([OsalTimer](osaltimer.md) * timer, uint32_t interval, [OsalTimerFunc](osal.md#gaf3e7a12075b25df5971049d8cd77c25c) func, uintptr_t arg )
```

 **Description:**

Creates a timer. 

**Parameters:**

<a name="table597498967093521"></a>
<table><thead align="left"><tr id="row933133291093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1815752280093521"><a name="p1815752280093521"></a><a name="p1815752280093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p909930597093521"><a name="p909930597093521"></a><a name="p909930597093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1680188594093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer <a href="osaltimer.md">OsalTimer</a>. </td>
</tr>
<tr id="row1262554515093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">interval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer interval. </td>
</tr>
<tr id="row1903308266093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer execution function <a href="osal.md#gaf3e7a12075b25df5971049d8cd77c25c">OsalTimerFunc</a>. </td>
</tr>
<tr id="row1508920379093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">arg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the argument passed to the timer execution function.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1652182947093521"></a>
<table><thead align="left"><tr id="row28797147093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1167767391093521"><a name="p1167767391093521"></a><a name="p1167767391093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p667087915093521"><a name="p667087915093521"></a><a name="p667087915093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1460101813093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1148919932093521"><a name="p1148919932093521"></a><a name="p1148919932093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p592094731093521"><a name="p592094731093521"></a><a name="p592094731093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1445707595093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1384713950093521"><a name="p1384713950093521"></a><a name="p1384713950093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395576849093521"><a name="p395576849093521"></a><a name="p395576849093521"></a>Failed to invoke the system function. </p>
</td>
</tr>
<tr id="row702435481093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615019645093521"><a name="p1615019645093521"></a><a name="p1615019645093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1777321740093521"><a name="p1777321740093521"></a><a name="p1777321740093521"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row974129693093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1388804923093521"><a name="p1388804923093521"></a><a name="p1388804923093521"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p817493910093521"><a name="p817493910093521"></a><a name="p817493910093521"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

## OsalTimerDelete\(\)<a name="gab754f3522245e6b2f9ee1cdecae62b52"></a>

```
int32_t OsalTimerDelete ([OsalTimer](osaltimer.md) * timer)
```

 **Description:**

Deletes a timer. 

**Parameters:**

<a name="table845210274093521"></a>
<table><thead align="left"><tr id="row808895961093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p402052785093521"><a name="p402052785093521"></a><a name="p402052785093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1191729859093521"><a name="p1191729859093521"></a><a name="p1191729859093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row268804499093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer <a href="osaltimer.md">OsalTimer</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table297043252093521"></a>
<table><thead align="left"><tr id="row1907340811093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p691024953093521"><a name="p691024953093521"></a><a name="p691024953093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p282800971093521"><a name="p282800971093521"></a><a name="p282800971093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row736589542093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220786070093521"><a name="p1220786070093521"></a><a name="p1220786070093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1355919483093521"><a name="p1355919483093521"></a><a name="p1355919483093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row19634464093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1212801745093521"><a name="p1212801745093521"></a><a name="p1212801745093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844914836093521"><a name="p1844914836093521"></a><a name="p1844914836093521"></a>Failed to invoke the system function to delete the timer. </p>
</td>
</tr>
<tr id="row253710267093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p412059305093521"><a name="p412059305093521"></a><a name="p412059305093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995567203093521"><a name="p1995567203093521"></a><a name="p1995567203093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalTimerSetTimeout\(\)<a name="ga49c2fe3f54d548fe5ec0d03a79691376"></a>

```
int32_t OsalTimerSetTimeout ([OsalTimer](osaltimer.md) * timer, uint32_t interval )
```

 **Description:**

Sets the interval of a timer. 

**Parameters:**

<a name="table143227111093521"></a>
<table><thead align="left"><tr id="row1233755670093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2144676755093521"><a name="p2144676755093521"></a><a name="p2144676755093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p477788787093521"><a name="p477788787093521"></a><a name="p477788787093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row761920435093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer <a href="osaltimer.md">OsalTimer</a>. </td>
</tr>
<tr id="row1197560279093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">interval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer interval, in milliseconds.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1441937415093521"></a>
<table><thead align="left"><tr id="row180548374093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p128965805093521"><a name="p128965805093521"></a><a name="p128965805093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p316725123093521"><a name="p316725123093521"></a><a name="p316725123093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1313477411093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687707195093521"><a name="p687707195093521"></a><a name="p687707195093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259913104093521"><a name="p1259913104093521"></a><a name="p1259913104093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row813175400093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896724897093521"><a name="p1896724897093521"></a><a name="p1896724897093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1340364596093521"><a name="p1340364596093521"></a><a name="p1340364596093521"></a>Failed to invoke the system function. </p>
</td>
</tr>
<tr id="row885010344093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319613241093521"><a name="p319613241093521"></a><a name="p319613241093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p680652672093521"><a name="p680652672093521"></a><a name="p680652672093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalTimerStartLoop\(\)<a name="ga575e4f41359c737ab9690ab28838b99f"></a>

```
int32_t OsalTimerStartLoop ([OsalTimer](osaltimer.md) * timer)
```

 **Description:**

Starts a periodic timer. 

**Parameters:**

<a name="table1750694035093521"></a>
<table><thead align="left"><tr id="row1882812020093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p276337267093521"><a name="p276337267093521"></a><a name="p276337267093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2141489802093521"><a name="p2141489802093521"></a><a name="p2141489802093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row479235860093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer <a href="osaltimer.md">OsalTimer</a>. </td>
</tr>
<tr id="row704037154093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">interval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer interval, in milliseconds.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1216422645093521"></a>
<table><thead align="left"><tr id="row686864089093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p492454424093521"><a name="p492454424093521"></a><a name="p492454424093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1245262797093521"><a name="p1245262797093521"></a><a name="p1245262797093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1898705906093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p272744802093521"><a name="p272744802093521"></a><a name="p272744802093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p192663614093521"><a name="p192663614093521"></a><a name="p192663614093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1324083533093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955334113093521"><a name="p955334113093521"></a><a name="p955334113093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1547725859093521"><a name="p1547725859093521"></a><a name="p1547725859093521"></a>Failed to invoke the system function to start the timer. </p>
</td>
</tr>
<tr id="row237557029093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p585159033093521"><a name="p585159033093521"></a><a name="p585159033093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1954097489093521"><a name="p1954097489093521"></a><a name="p1954097489093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalTimerStartOnce\(\)<a name="gaf2e49d5b01b49e5f64a7701da8667141"></a>

```
int32_t OsalTimerStartOnce ([OsalTimer](osaltimer.md) * timer)
```

 **Description:**

Starts a timer. 

**Parameters:**

<a name="table1219469306093521"></a>
<table><thead align="left"><tr id="row1834405980093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p423268908093521"><a name="p423268908093521"></a><a name="p423268908093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1994599653093521"><a name="p1994599653093521"></a><a name="p1994599653093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row535319627093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer <a href="osaltimer.md">OsalTimer</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table817804590093521"></a>
<table><thead align="left"><tr id="row1571780411093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1161264902093521"><a name="p1161264902093521"></a><a name="p1161264902093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1489154184093521"><a name="p1489154184093521"></a><a name="p1489154184093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row85443369093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997447898093521"><a name="p1997447898093521"></a><a name="p1997447898093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849052764093521"><a name="p1849052764093521"></a><a name="p1849052764093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1250265475093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p667270285093521"><a name="p667270285093521"></a><a name="p667270285093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1569115204093521"><a name="p1569115204093521"></a><a name="p1569115204093521"></a>Failed to invoke the system function to start the timer. </p>
</td>
</tr>
<tr id="row375830194093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p553356128093521"><a name="p553356128093521"></a><a name="p553356128093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388550126093521"><a name="p1388550126093521"></a><a name="p1388550126093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## OsalUDelay\(\)<a name="ga7ae78fa3318a82dbd769827d4f373958"></a>

```
void OsalUDelay (uint32_t us)
```

 **Description:**

Describes thread delay, in microseconds. 

When a thread invokes this function, the CPU is not released. This function returns after waiting for microseconds.

**Parameters:**

<a name="table796671186093521"></a>
<table><thead align="left"><tr id="row1608779812093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1419457142093521"><a name="p1419457142093521"></a><a name="p1419457142093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1054199827093521"><a name="p1054199827093521"></a><a name="p1054199827093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row414900799093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">us</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the delay time, in microseconds. </td>
</tr>
</tbody>
</table>

## OsalUnregisterIrq\(\)<a name="gade4ec4496eb07f1ff0610b53ba419dba"></a>

```
int32_t OsalUnregisterIrq (uint32_t irqId)
```

 **Description:**

Unregisters an IRQ. 

**Parameters:**

<a name="table1040162668093521"></a>
<table><thead align="left"><tr id="row2005161540093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p995772206093521"><a name="p995772206093521"></a><a name="p995772206093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1964174767093521"><a name="p1964174767093521"></a><a name="p1964174767093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1393211684093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">irqId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the IRQ ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1953494989093521"></a>
<table><thead align="left"><tr id="row2138689228093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2055748315093521"><a name="p2055748315093521"></a><a name="p2055748315093521"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1829204122093521"><a name="p1829204122093521"></a><a name="p1829204122093521"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row309732241093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76102059093521"><a name="p76102059093521"></a><a name="p76102059093521"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p770691149093521"><a name="p770691149093521"></a><a name="p770691149093521"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1179676516093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1588027674093521"><a name="p1588027674093521"></a><a name="p1588027674093521"></a>HDF_FAILURE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p202029019093521"><a name="p202029019093521"></a><a name="p202029019093521"></a>Failed to invoke the system function to unregister the IRQ. </p>
</td>
</tr>
<tr id="row1493811472093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p115152158093521"><a name="p115152158093521"></a><a name="p115152158093521"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p610521038093521"><a name="p610521038093521"></a><a name="p610521038093521"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

