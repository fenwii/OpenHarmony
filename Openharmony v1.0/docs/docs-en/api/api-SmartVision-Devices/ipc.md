# IPC<a name="EN-US_TOPIC_0000001054829479"></a>

## **Overview**<a name="section1716504298084823"></a>

Provides functions and structures related to inter-process communication \(IPC\), including signals, semaphores, and message queues. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section642869449084823"></a>

## Files<a name="files"></a>

<a name="table525847284084823"></a>
<table><thead align="left"><tr id="row1669639464084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1193167520084823"><a name="p1193167520084823"></a><a name="p1193167520084823"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1154679741084823"><a name="p1154679741084823"></a><a name="p1154679741084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1874689348084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p718133823084823"><a name="p718133823084823"></a><a name="p718133823084823"></a><a href="ipcstat-h.md">ipcstat.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p123873832084823"><a name="p123873832084823"></a><a name="p123873832084823"></a>Defines the macros related to the IPC functions. </p>
</td>
</tr>
<tr id="row468927800084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p505273053084823"><a name="p505273053084823"></a><a name="p505273053084823"></a><a href="mqueue-h.md">mqueue.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580128965084823"><a name="p580128965084823"></a><a name="p580128965084823"></a>Provides message queue operation functions and related structures. </p>
</td>
</tr>
<tr id="row2037815945084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1459559075084823"><a name="p1459559075084823"></a><a name="p1459559075084823"></a><a href="semaphore-h.md">semaphore.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1166978026084823"><a name="p1166978026084823"></a><a name="p1166978026084823"></a>Provides functions and structures related to semaphore operations. </p>
</td>
</tr>
<tr id="row1943962772084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088471689084823"><a name="p2088471689084823"></a><a name="p2088471689084823"></a><a href="signal-h.md">signal.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459063796084823"><a name="p1459063796084823"></a><a name="p1459063796084823"></a>Provides signal operation functions and structures, including changing the signal processing mode and the process signal mask set. </p>
</td>
</tr>
<tr id="row1065251673084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639125929084823"><a name="p1639125929084823"></a><a name="p1639125929084823"></a><a href="ipc-h.md">ipc.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179596552084823"><a name="p1179596552084823"></a><a name="p1179596552084823"></a>Defines IPC-related macros. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table806492626084823"></a>
<table><thead align="left"><tr id="row167241735084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1814424419084823"><a name="p1814424419084823"></a><a name="p1814424419084823"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p301125785084823"><a name="p301125785084823"></a><a name="p301125785084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1876633769084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1077151494084823"><a name="p1077151494084823"></a><a name="p1077151494084823"></a><a href="mq_attr.md">mq_attr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124155743084823"><a name="p124155743084823"></a><a name="p124155743084823"></a>Describes message queue attributes. </p>
</td>
</tr>
<tr id="row1981976779084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2012345099084823"><a name="p2012345099084823"></a><a name="p2012345099084823"></a><a href="sem_t.md">sem_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p609178666084823"><a name="p609178666084823"></a><a name="p609178666084823"></a>Defines semaphores. </p>
</td>
</tr>
<tr id="row1963521110084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61220975084823"><a name="p61220975084823"></a><a name="p61220975084823"></a><a href="sigaltstack.md">sigaltstack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412557028084823"><a name="p1412557028084823"></a><a name="p1412557028084823"></a>Describes a signal stack. </p>
</td>
</tr>
<tr id="row563283453084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780416680084823"><a name="p780416680084823"></a><a name="p780416680084823"></a><a href="__ucontext.md">__ucontext</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1256000650084823"><a name="p1256000650084823"></a><a name="p1256000650084823"></a>Describes the user execution context. </p>
</td>
</tr>
<tr id="row1493586591084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p608092998084823"><a name="p608092998084823"></a><a name="p608092998084823"></a><a href="__sigset_t.md">__sigset_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1723187427084823"><a name="p1723187427084823"></a><a name="p1723187427084823"></a>Defines a signal set. </p>
</td>
</tr>
<tr id="row1147116273084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549739001084823"><a name="p549739001084823"></a><a name="p549739001084823"></a><a href="sigaction.md">sigaction</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1195051578084823"><a name="p1195051578084823"></a><a name="p1195051578084823"></a>Defines the signal processing actions and related attributes. You can use the structures to change the processing actions or attributes. </p>
</td>
</tr>
<tr id="row2063878339084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903163723084823"><a name="p903163723084823"></a><a name="p903163723084823"></a><a href="sigval.md">sigval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p624292976084823"><a name="p624292976084823"></a><a name="p624292976084823"></a>Describes signal values in different cases. </p>
</td>
</tr>
<tr id="row620067738084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p641502899084823"><a name="p641502899084823"></a><a name="p641502899084823"></a><a href="__si_fields.md">__si_fields</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p789647164084823"><a name="p789647164084823"></a><a name="p789647164084823"></a>Describes signal information. </p>
</td>
</tr>
<tr id="row349183283084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206828478084823"><a name="p206828478084823"></a><a name="p206828478084823"></a><a href="sigevent.md">sigevent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1493140751084823"><a name="p1493140751084823"></a><a name="p1493140751084823"></a>Describes asynchronous notifications. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1185778318084823"></a>
<table><thead align="left"><tr id="row1968995028084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1562954459084823"><a name="p1562954459084823"></a><a name="p1562954459084823"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p840607678084823"><a name="p840607678084823"></a><a name="p840607678084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1566218327084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1834716959084823"><a name="p1834716959084823"></a><a name="p1834716959084823"></a><em id="ga16a91ee69c3cb6bfec425e1bfd5edd18"><a name="ga16a91ee69c3cb6bfec425e1bfd5edd18"></a><a name="ga16a91ee69c3cb6bfec425e1bfd5edd18"></a></em>IPC_STAT    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343690284084823"><a name="p343690284084823"></a><a name="p343690284084823"></a>Defines the input parameter used to obtain information from the kernel. </p>
</td>
</tr>
<tr id="row275505063084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p861682081084823"><a name="p861682081084823"></a><a name="p861682081084823"></a><em id="ga2ef55dcb46a51cb0f879f4c1724bdded"><a name="ga2ef55dcb46a51cb0f879f4c1724bdded"></a><a name="ga2ef55dcb46a51cb0f879f4c1724bdded"></a></em>SEM_FAILED    ((<a href="sem_t.md">sem_t</a> *)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798363856084823"><a name="p1798363856084823"></a><a name="p1798363856084823"></a>Defines the semaphore failure flag. </p>
</td>
</tr>
<tr id="row916326587084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806001471084823"><a name="p806001471084823"></a><a name="p806001471084823"></a><a href="ipc.md#gaf6a71c97263725437f59ceb16241fd32">SA_NOCLDSTOP</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511840380084823"><a name="p1511840380084823"></a><a name="p1511840380084823"></a>Stops a child process without sending the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> signal. </p>
</td>
</tr>
<tr id="row1648898091084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1176696134084823"><a name="p1176696134084823"></a><a name="p1176696134084823"></a><a href="ipc.md#gaf6a71c97263725437f59ceb16241fd32">SA_NOCLDSTOP</a>   0x00000001</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182460283084823"><a name="p182460283084823"></a><a name="p182460283084823"></a>Stops a child process without sending the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> signal. </p>
</td>
</tr>
<tr id="row674594813084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p994744454084823"><a name="p994744454084823"></a><a name="p994744454084823"></a><em id="gae4c1aad864ef72e4a2cce74b1b8a5a0b"><a name="gae4c1aad864ef72e4a2cce74b1b8a5a0b"></a><a name="gae4c1aad864ef72e4a2cce74b1b8a5a0b"></a></em>SA_NOCLDWAIT    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565986688084823"><a name="p1565986688084823"></a><a name="p1565986688084823"></a>Sets the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> flag to prevent zombie processes. </p>
</td>
</tr>
<tr id="row2101330915084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730022831084823"><a name="p730022831084823"></a><a name="p730022831084823"></a><em id="i1041694584"><a name="i1041694584"></a><a name="i1041694584"></a></em>SA_NOCLDWAIT    0x00000002</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152709756084823"><a name="p1152709756084823"></a><a name="p1152709756084823"></a>Sets the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> flag to prevent zombie processes. </p>
</td>
</tr>
<tr id="row2016643226084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609189098084823"><a name="p609189098084823"></a><a name="p609189098084823"></a><a href="ipc.md#ga59b4c0774aace526b10b6d737075a790">SA_SIGINFO</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380762169084823"><a name="p380762169084823"></a><a name="p380762169084823"></a>Transfers the <strong id="b44342533084823"><a name="b44342533084823"></a><a name="b44342533084823"></a>siginfo_t</strong> structure with the signal. </p>
</td>
</tr>
<tr id="row1653823907084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974123286084823"><a name="p1974123286084823"></a><a name="p1974123286084823"></a><a href="ipc.md#ga59b4c0774aace526b10b6d737075a790">SA_SIGINFO</a>   0x00000004</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p379383873084823"><a name="p379383873084823"></a><a name="p379383873084823"></a>Transfers the <strong id="b167965533084823"><a name="b167965533084823"></a><a name="b167965533084823"></a>siginfo_t</strong> structure with the signal. </p>
</td>
</tr>
<tr id="row69055616084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430221240084823"><a name="p430221240084823"></a><a name="p430221240084823"></a><a href="ipc.md#ga322c220e296393958ab4238145a0d273">SA_ONSTACK</a>   0x08000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p39353062084823"><a name="p39353062084823"></a><a name="p39353062084823"></a>Uses the signal stack specified by <a href="sigaltstack.md">sigaltstack</a> for signal processing. </p>
</td>
</tr>
<tr id="row477408527084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392348205084823"><a name="p1392348205084823"></a><a name="p1392348205084823"></a><a href="ipc.md#ga322c220e296393958ab4238145a0d273">SA_ONSTACK</a>   0x08000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1833215485084823"><a name="p1833215485084823"></a><a name="p1833215485084823"></a>Uses the signal stack specified by <a href="sigaltstack.md">sigaltstack</a> for signal processing. </p>
</td>
</tr>
<tr id="row1997496894084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2077427659084823"><a name="p2077427659084823"></a><a name="p2077427659084823"></a><em id="ga74ef0a27afcf55b6cd6d35cf0fa5d427"><a name="ga74ef0a27afcf55b6cd6d35cf0fa5d427"></a><a name="ga74ef0a27afcf55b6cd6d35cf0fa5d427"></a></em>SA_RESTART    0x10000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2079139715084823"><a name="p2079139715084823"></a><a name="p2079139715084823"></a>Obtains the restart signal. </p>
</td>
</tr>
<tr id="row1668779405084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1977843310084823"><a name="p1977843310084823"></a><a name="p1977843310084823"></a><em id="i1780388619"><a name="i1780388619"></a><a name="i1780388619"></a></em>SA_RESTART    0x10000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1463796841084823"><a name="p1463796841084823"></a><a name="p1463796841084823"></a>Obtains the restart signal. </p>
</td>
</tr>
<tr id="row804614109084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p836731967084823"><a name="p836731967084823"></a><a name="p836731967084823"></a><a href="ipc.md#gabec4abd80d73397fc2f78f57f178565f">SA_NODEFER</a>   0x40000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p936944434084823"><a name="p936944434084823"></a><a name="p936944434084823"></a>The signals being processed are not masked during signal processing. </p>
</td>
</tr>
<tr id="row471856549084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1899500156084823"><a name="p1899500156084823"></a><a name="p1899500156084823"></a><a href="ipc.md#gabec4abd80d73397fc2f78f57f178565f">SA_NODEFER</a>   0x40000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850216721084823"><a name="p1850216721084823"></a><a name="p1850216721084823"></a>The signals being processed are not masked during signal processing. </p>
</td>
</tr>
<tr id="row178418074084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1306928665084823"><a name="p1306928665084823"></a><a name="p1306928665084823"></a><em id="ga8d5fb4f35858d31035e7354c1d4048ea"><a name="ga8d5fb4f35858d31035e7354c1d4048ea"></a><a name="ga8d5fb4f35858d31035e7354c1d4048ea"></a></em>SA_RESETHAND    0x80000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749961495084823"><a name="p749961495084823"></a><a name="p749961495084823"></a>The default processing mode is restored after the signal processing is complete. </p>
</td>
</tr>
<tr id="row162656433084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p606194916084823"><a name="p606194916084823"></a><a name="p606194916084823"></a><em id="i979261069"><a name="i979261069"></a><a name="i979261069"></a></em>SA_RESETHAND    0x80000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452386513084823"><a name="p1452386513084823"></a><a name="p1452386513084823"></a>The default processing mode is restored after the signal processing is complete. </p>
</td>
</tr>
<tr id="row1122862448084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p232966778084823"><a name="p232966778084823"></a><a name="p232966778084823"></a><em id="ga4af58063b5774f0422ddf346ff64846e"><a name="ga4af58063b5774f0422ddf346ff64846e"></a><a name="ga4af58063b5774f0422ddf346ff64846e"></a></em>SA_RESTORER    0x04000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027932873084823"><a name="p1027932873084823"></a><a name="p1027932873084823"></a>Not intended for application use. This flag is used by C libraries to indicate that the <strong id="b1441878283084823"><a name="b1441878283084823"></a><a name="b1441878283084823"></a>sa_restorer</strong> field contains the address of a <strong id="b2012397146084823"><a name="b2012397146084823"></a><a name="b2012397146084823"></a>trampoline</strong>. </p>
</td>
</tr>
<tr id="row225829840084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640542446084823"><a name="p1640542446084823"></a><a name="p1640542446084823"></a><em id="i389166099"><a name="i389166099"></a><a name="i389166099"></a></em>SA_RESTORER    0x04000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1190403023084823"><a name="p1190403023084823"></a><a name="p1190403023084823"></a>Not intended for application use. This flag is used by C libraries to indicate that the <strong id="b738292897084823"><a name="b738292897084823"></a><a name="b738292897084823"></a>sa_restorer</strong> field contains the address of a <strong id="b1715985068084823"><a name="b1715985068084823"></a><a name="b1715985068084823"></a>trampoline</strong>. </p>
</td>
</tr>
<tr id="row1165185482084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087290298084823"><a name="p2087290298084823"></a><a name="p2087290298084823"></a><a href="ipc.md#gaae6a742a8c5acf12caba1d148dd03f10">MINSIGSTKSZ</a>   2048</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27459466084823"><a name="p27459466084823"></a><a name="p27459466084823"></a>Defines the minimum size of the replaceable signal stack. </p>
</td>
</tr>
<tr id="row1910932798084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1681093380084823"><a name="p1681093380084823"></a><a name="p1681093380084823"></a><a href="ipc.md#gaae6a742a8c5acf12caba1d148dd03f10">MINSIGSTKSZ</a>   2048</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459178176084823"><a name="p459178176084823"></a><a name="p459178176084823"></a>Defines the minimum size of the replaceable signal stack. </p>
</td>
</tr>
<tr id="row46519624084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1653816921084823"><a name="p1653816921084823"></a><a name="p1653816921084823"></a><a href="ipc.md#ga8a433a10420a0c51355da26cfcab2131">SIGSTKSZ</a>   8192</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1756232207084823"><a name="p1756232207084823"></a><a name="p1756232207084823"></a>Defines the size of a signal stack. </p>
</td>
</tr>
<tr id="row1585893450084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1432000516084823"><a name="p1432000516084823"></a><a name="p1432000516084823"></a><a href="ipc.md#ga8a433a10420a0c51355da26cfcab2131">SIGSTKSZ</a>   8192</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989286771084823"><a name="p989286771084823"></a><a name="p989286771084823"></a>Defines the size of a signal stack. </p>
</td>
</tr>
<tr id="row288461763084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687676505084823"><a name="p687676505084823"></a><a name="p687676505084823"></a><em id="ga275020780cb70a8b0cba8db5accc5d19"><a name="ga275020780cb70a8b0cba8db5accc5d19"></a><a name="ga275020780cb70a8b0cba8db5accc5d19"></a></em>_NSIG    65</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1965652221084823"><a name="p1965652221084823"></a><a name="p1965652221084823"></a>Number of supported signals. </p>
</td>
</tr>
<tr id="row2033747606084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1202746731084823"><a name="p1202746731084823"></a><a name="p1202746731084823"></a><em id="ga15d5d2dce732343eece4e11ac487e003"><a name="ga15d5d2dce732343eece4e11ac487e003"></a><a name="ga15d5d2dce732343eece4e11ac487e003"></a></em>_NSIG_BPW    <a href="utils.md#ga0bf2a26a1f15f79f80319edbaa5cc9a5">__BITS_PER_LONG</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1696196245084823"><a name="p1696196245084823"></a><a name="p1696196245084823"></a>Number of bits occupied by a word. </p>
</td>
</tr>
<tr id="row1482448777084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1788214954084823"><a name="p1788214954084823"></a><a name="p1788214954084823"></a><em id="gacd9297a3ab78048b3f46055fc7739c17"><a name="gacd9297a3ab78048b3f46055fc7739c17"></a><a name="gacd9297a3ab78048b3f46055fc7739c17"></a></em>_NSIG_WORDS    (<a href="ipc.md#ga275020780cb70a8b0cba8db5accc5d19">_NSIG</a> / <a href="ipc.md#ga15d5d2dce732343eece4e11ac487e003">_NSIG_BPW</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p838870438084823"><a name="p838870438084823"></a><a name="p838870438084823"></a>Number of words required by all signals. </p>
</td>
</tr>
<tr id="row1830090302084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p460477538084823"><a name="p460477538084823"></a><a name="p460477538084823"></a><em id="ga136c64ec2d1306de745e39d6aee362ca"><a name="ga136c64ec2d1306de745e39d6aee362ca"></a><a name="ga136c64ec2d1306de745e39d6aee362ca"></a></em>SIGHUP    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46834512084823"><a name="p46834512084823"></a><a name="p46834512084823"></a>Hangs up a process. </p>
</td>
</tr>
<tr id="row897660969084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2016863519084823"><a name="p2016863519084823"></a><a name="p2016863519084823"></a><em id="ga487309e3e9e0527535644115204a639a"><a name="ga487309e3e9e0527535644115204a639a"></a><a name="ga487309e3e9e0527535644115204a639a"></a></em>SIGINT    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p570233014084823"><a name="p570233014084823"></a><a name="p570233014084823"></a>Interrupts a process from keyboard. </p>
</td>
</tr>
<tr id="row2091622786084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p994783529084823"><a name="p994783529084823"></a><a name="p994783529084823"></a><em id="ga62045b465be11891160d53c10861b16c"><a name="ga62045b465be11891160d53c10861b16c"></a><a name="ga62045b465be11891160d53c10861b16c"></a></em>SIGQUIT    3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635231865084823"><a name="p635231865084823"></a><a name="p635231865084823"></a>Exits a process from keyboard. A core file is generated. </p>
</td>
</tr>
<tr id="row876192411084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1399046265084823"><a name="p1399046265084823"></a><a name="p1399046265084823"></a><em id="ga4c9c5284f8c8d146bd7a93d25017fc62"><a name="ga4c9c5284f8c8d146bd7a93d25017fc62"></a><a name="ga4c9c5284f8c8d146bd7a93d25017fc62"></a></em>SIGILL    4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383854423084823"><a name="p1383854423084823"></a><a name="p1383854423084823"></a>Illegal instruction. </p>
</td>
</tr>
<tr id="row155381277084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p789920080084823"><a name="p789920080084823"></a><a name="p789920080084823"></a><em id="gaa2beb906ab1b46676e63823f4e773c38"><a name="gaa2beb906ab1b46676e63823f4e773c38"></a><a name="gaa2beb906ab1b46676e63823f4e773c38"></a></em>SIGTRAP    5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298054264084823"><a name="p298054264084823"></a><a name="p298054264084823"></a>Breakpoint, used for debugging. </p>
</td>
</tr>
<tr id="row1851257971084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p602120496084823"><a name="p602120496084823"></a><a name="p602120496084823"></a><em id="gaa86c630133e5b5174ac970227b273446"><a name="gaa86c630133e5b5174ac970227b273446"></a><a name="gaa86c630133e5b5174ac970227b273446"></a></em>SIGABRT    6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1299162488084823"><a name="p1299162488084823"></a><a name="p1299162488084823"></a>Abnormal termination. </p>
</td>
</tr>
<tr id="row806782726084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678533143084823"><a name="p678533143084823"></a><a name="p678533143084823"></a><em id="gab12271d5e5911f8a85dc7c3f0e2364c7"><a name="gab12271d5e5911f8a85dc7c3f0e2364c7"></a><a name="gab12271d5e5911f8a85dc7c3f0e2364c7"></a></em>SIGIOT    6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p578746048084823"><a name="p578746048084823"></a><a name="p578746048084823"></a>Equivalent to <a href="ipc.md#gaa86c630133e5b5174ac970227b273446">SIGABRT</a>. </p>
</td>
</tr>
<tr id="row781910910084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p141339022084823"><a name="p141339022084823"></a><a name="p141339022084823"></a><em id="gaead3d488474201acf18c4b63d91edc3c"><a name="gaead3d488474201acf18c4b63d91edc3c"></a><a name="gaead3d488474201acf18c4b63d91edc3c"></a></em>SIGBUS    7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419653675084823"><a name="p419653675084823"></a><a name="p419653675084823"></a>Invalid address access. </p>
</td>
</tr>
<tr id="row1555574251084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1581898148084823"><a name="p1581898148084823"></a><a name="p1581898148084823"></a><em id="ga7fbba29aec3e4a8daae12935299df92d"><a name="ga7fbba29aec3e4a8daae12935299df92d"></a><a name="ga7fbba29aec3e4a8daae12935299df92d"></a></em>SIGFPE    8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327977528084823"><a name="p1327977528084823"></a><a name="p1327977528084823"></a>Floating-point exceptions. </p>
</td>
</tr>
<tr id="row123923295084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888208406084823"><a name="p888208406084823"></a><a name="p888208406084823"></a><em id="gaddd8dcd406ce514ab3b4f576a5343d42"><a name="gaddd8dcd406ce514ab3b4f576a5343d42"></a><a name="gaddd8dcd406ce514ab3b4f576a5343d42"></a></em>SIGKILL    9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p885204562084823"><a name="p885204562084823"></a><a name="p885204562084823"></a>Forcibly stops a process. </p>
</td>
</tr>
<tr id="row1705637670084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288101242084823"><a name="p1288101242084823"></a><a name="p1288101242084823"></a><em id="ga944a8250e34bfd7991123abd3436d8c0"><a name="ga944a8250e34bfd7991123abd3436d8c0"></a><a name="ga944a8250e34bfd7991123abd3436d8c0"></a></em>SIGUSR1    10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946278120084823"><a name="p1946278120084823"></a><a name="p1946278120084823"></a>User-defined signal 1. </p>
</td>
</tr>
<tr id="row149517770084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274048778084823"><a name="p1274048778084823"></a><a name="p1274048778084823"></a><em id="gae20b4f7171a09516ea73c9d2745bd596"><a name="gae20b4f7171a09516ea73c9d2745bd596"></a><a name="gae20b4f7171a09516ea73c9d2745bd596"></a></em>SIGSEGV    11</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646074826084823"><a name="p1646074826084823"></a><a name="p1646074826084823"></a>Illegal memory access. </p>
</td>
</tr>
<tr id="row39308354084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1213086602084823"><a name="p1213086602084823"></a><a name="p1213086602084823"></a><em id="gabaaa61abe503c43481e35e21b0b5a031"><a name="gabaaa61abe503c43481e35e21b0b5a031"></a><a name="gabaaa61abe503c43481e35e21b0b5a031"></a></em>SIGUSR2    12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519303872084823"><a name="p519303872084823"></a><a name="p519303872084823"></a>User-defined signal 2. </p>
</td>
</tr>
<tr id="row1839278587084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p184834868084823"><a name="p184834868084823"></a><a name="p184834868084823"></a><em id="ga57e9c8c5fa13bf86bc779a9f6f408b7c"><a name="ga57e9c8c5fa13bf86bc779a9f6f408b7c"></a><a name="ga57e9c8c5fa13bf86bc779a9f6f408b7c"></a></em>SIGPIPE    13</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p616912095084823"><a name="p616912095084823"></a><a name="p616912095084823"></a>The pipe is broken. </p>
</td>
</tr>
<tr id="row283552200084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413211019084823"><a name="p413211019084823"></a><a name="p413211019084823"></a><em id="gaa6946723c6b7a86ec3c33caaf832840b"><a name="gaa6946723c6b7a86ec3c33caaf832840b"></a><a name="gaa6946723c6b7a86ec3c33caaf832840b"></a></em>SIGALRM    14</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954742545084823"><a name="p954742545084823"></a><a name="p954742545084823"></a>Timer signal. </p>
</td>
</tr>
<tr id="row2011038214084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236243115084823"><a name="p236243115084823"></a><a name="p236243115084823"></a><em id="ga682182a5e5f38fd61f4311501e9dac5d"><a name="ga682182a5e5f38fd61f4311501e9dac5d"></a><a name="ga682182a5e5f38fd61f4311501e9dac5d"></a></em>SIGTERM    15</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p617483534084823"><a name="p617483534084823"></a><a name="p617483534084823"></a>Termination signal. </p>
</td>
</tr>
<tr id="row1824255630084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p178367574084823"><a name="p178367574084823"></a><a name="p178367574084823"></a><em id="ga03612fcda4ab9671dfa7051e7b666fb6"><a name="ga03612fcda4ab9671dfa7051e7b666fb6"></a><a name="ga03612fcda4ab9671dfa7051e7b666fb6"></a></em>SIGSTKFLT    16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p637423971084823"><a name="p637423971084823"></a><a name="p637423971084823"></a>Coprocessor stack error. </p>
</td>
</tr>
<tr id="row1947174776084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1429354133084823"><a name="p1429354133084823"></a><a name="p1429354133084823"></a><em id="ga0e63521a64cc8bc2b91d36a87d32c9f8"><a name="ga0e63521a64cc8bc2b91d36a87d32c9f8"></a><a name="ga0e63521a64cc8bc2b91d36a87d32c9f8"></a></em>SIGCHLD    17</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1013435752084823"><a name="p1013435752084823"></a><a name="p1013435752084823"></a>Child process terminated or stopped. </p>
</td>
</tr>
<tr id="row1473991957084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p58018353084823"><a name="p58018353084823"></a><a name="p58018353084823"></a><em id="ga024f43063003e753afc6cca1acd6e104"><a name="ga024f43063003e753afc6cca1acd6e104"></a><a name="ga024f43063003e753afc6cca1acd6e104"></a></em>SIGCONT    18</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1772288918084823"><a name="p1772288918084823"></a><a name="p1772288918084823"></a>Resumes a suspended process. </p>
</td>
</tr>
<tr id="row281054271084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1459367808084823"><a name="p1459367808084823"></a><a name="p1459367808084823"></a><em id="ga069e358bc9a864b7dc4fed2440eda14c"><a name="ga069e358bc9a864b7dc4fed2440eda14c"></a><a name="ga069e358bc9a864b7dc4fed2440eda14c"></a></em>SIGSTOP    19</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p414010008084823"><a name="p414010008084823"></a><a name="p414010008084823"></a>Suspends a process. </p>
</td>
</tr>
<tr id="row578538001084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680819227084823"><a name="p680819227084823"></a><a name="p680819227084823"></a><em id="gabe65c086e01f0d286b7a785a7e3cdd1a"><a name="gabe65c086e01f0d286b7a785a7e3cdd1a"></a><a name="gabe65c086e01f0d286b7a785a7e3cdd1a"></a></em>SIGTSTP    20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967122051084823"><a name="p967122051084823"></a><a name="p967122051084823"></a>Stops a process by entering the command on the terminal. </p>
</td>
</tr>
<tr id="row2115182326084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170892031084823"><a name="p170892031084823"></a><a name="p170892031084823"></a><em id="ga2c146e34a6b5a78dfba41cded3331181"><a name="ga2c146e34a6b5a78dfba41cded3331181"></a><a name="ga2c146e34a6b5a78dfba41cded3331181"></a></em>SIGTTIN    21</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056422742084823"><a name="p1056422742084823"></a><a name="p1056422742084823"></a>Input required by the background process. </p>
</td>
</tr>
<tr id="row1243130752084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1208527398084823"><a name="p1208527398084823"></a><a name="p1208527398084823"></a><em id="ga782864287613e2c5c030411fa9c5e9b1"><a name="ga782864287613e2c5c030411fa9c5e9b1"></a><a name="ga782864287613e2c5c030411fa9c5e9b1"></a></em>SIGTTOU    22</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p187606675084823"><a name="p187606675084823"></a><a name="p187606675084823"></a>Output required by the background process. </p>
</td>
</tr>
<tr id="row1538921767084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1893637039084823"><a name="p1893637039084823"></a><a name="p1893637039084823"></a><em id="gad9ff13149e36144a4ea28788948c34dd"><a name="gad9ff13149e36144a4ea28788948c34dd"></a><a name="gad9ff13149e36144a4ea28788948c34dd"></a></em>SIGURG    23</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p819014831084823"><a name="p819014831084823"></a><a name="p819014831084823"></a>Urgent socket condition. </p>
</td>
</tr>
<tr id="row2056720181084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1100839157084823"><a name="p1100839157084823"></a><a name="p1100839157084823"></a><em id="ga7265cbba4972503c1c30a2e52a929874"><a name="ga7265cbba4972503c1c30a2e52a929874"></a><a name="ga7265cbba4972503c1c30a2e52a929874"></a></em>SIGXCPU    24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293369945084823"><a name="p293369945084823"></a><a name="p293369945084823"></a>CPU time limit exceeded. </p>
</td>
</tr>
<tr id="row834248717084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529374443084823"><a name="p529374443084823"></a><a name="p529374443084823"></a><em id="ga75440a7aa885a1052dfd3b4393fd9baa"><a name="ga75440a7aa885a1052dfd3b4393fd9baa"></a><a name="ga75440a7aa885a1052dfd3b4393fd9baa"></a></em>SIGXFSZ    25</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540411312084823"><a name="p1540411312084823"></a><a name="p1540411312084823"></a>File size limit exceeded. </p>
</td>
</tr>
<tr id="row209299860084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p839351896084823"><a name="p839351896084823"></a><a name="p839351896084823"></a><em id="ga71403d2f5240e409e213060ea3301851"><a name="ga71403d2f5240e409e213060ea3301851"></a><a name="ga71403d2f5240e409e213060ea3301851"></a></em>SIGVTALRM    26</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125155831084823"><a name="p2125155831084823"></a><a name="p2125155831084823"></a>Virtual timer, used to calculate the CPU occupation time of a process. </p>
</td>
</tr>
<tr id="row507439523084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1963000177084823"><a name="p1963000177084823"></a><a name="p1963000177084823"></a><em id="gab6bd2a2ff7e58d45965ef257f96dfe65"><a name="gab6bd2a2ff7e58d45965ef257f96dfe65"></a><a name="gab6bd2a2ff7e58d45965ef257f96dfe65"></a></em>SIGPROF    27</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73287811084823"><a name="p73287811084823"></a><a name="p73287811084823"></a>Calculates the CPU time occupied by a process and the system calling time. </p>
</td>
</tr>
<tr id="row967039545084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2020846055084823"><a name="p2020846055084823"></a><a name="p2020846055084823"></a><em id="ga13ba0e7c4365813312eb4566907bce4f"><a name="ga13ba0e7c4365813312eb4566907bce4f"></a><a name="ga13ba0e7c4365813312eb4566907bce4f"></a></em>SIGWINCH    28</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p358238872084823"><a name="p358238872084823"></a><a name="p358238872084823"></a>Window size change. </p>
</td>
</tr>
<tr id="row430221283084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835615602084823"><a name="p835615602084823"></a><a name="p835615602084823"></a><em id="ga929c5eace94ce2e099c6fa732450ce86"><a name="ga929c5eace94ce2e099c6fa732450ce86"></a><a name="ga929c5eace94ce2e099c6fa732450ce86"></a></em>SIGIO    29</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1701579238084823"><a name="p1701579238084823"></a><a name="p1701579238084823"></a>Input/Output. </p>
</td>
</tr>
<tr id="row1623121298084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p491244797084823"><a name="p491244797084823"></a><a name="p491244797084823"></a><em id="ga1614264a836d6a5642554775ef0134d0"><a name="ga1614264a836d6a5642554775ef0134d0"></a><a name="ga1614264a836d6a5642554775ef0134d0"></a></em>SIGPOLL    <a href="ipc.md#ga929c5eace94ce2e099c6fa732450ce86">SIGIO</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193560905084823"><a name="p1193560905084823"></a><a name="p1193560905084823"></a>Equivalent to <a href="ipc.md#ga929c5eace94ce2e099c6fa732450ce86">SIGIO</a>. </p>
</td>
</tr>
<tr id="row1203249917084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p448964800084823"><a name="p448964800084823"></a><a name="p448964800084823"></a><em id="ga633dbd7dca7d839e6af0299bd4713f0a"><a name="ga633dbd7dca7d839e6af0299bd4713f0a"></a><a name="ga633dbd7dca7d839e6af0299bd4713f0a"></a></em>SIGPWR    30</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284678989084823"><a name="p284678989084823"></a><a name="p284678989084823"></a>Power failure. </p>
</td>
</tr>
<tr id="row1576780716084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p198884520084823"><a name="p198884520084823"></a><a name="p198884520084823"></a><em id="ga8bacf9eb18fd539099c1bb4666c45d60"><a name="ga8bacf9eb18fd539099c1bb4666c45d60"></a><a name="ga8bacf9eb18fd539099c1bb4666c45d60"></a></em>SIGSYS    31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980706771084823"><a name="p980706771084823"></a><a name="p980706771084823"></a>Non-existent system call. </p>
</td>
</tr>
<tr id="row328989788084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1138001348084823"><a name="p1138001348084823"></a><a name="p1138001348084823"></a><em id="ga11e925ada5a97c7bbb6b88de8ed543b4"><a name="ga11e925ada5a97c7bbb6b88de8ed543b4"></a><a name="ga11e925ada5a97c7bbb6b88de8ed543b4"></a></em>SIGUNUSED    31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71756025084823"><a name="p71756025084823"></a><a name="p71756025084823"></a>Equivalent to <a href="ipc.md#ga8bacf9eb18fd539099c1bb4666c45d60">SIGSYS</a>. </p>
</td>
</tr>
<tr id="row923068027084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1485361383084823"><a name="p1485361383084823"></a><a name="p1485361383084823"></a><a href="ipc.md#gae89f9a1282bd2d1b2a2b310c12ea16a5">SIGRTMIN</a>   32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1409466961084823"><a name="p1409466961084823"></a><a name="p1409466961084823"></a>Start of a reliable signal. </p>
</td>
</tr>
<tr id="row502725541084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p109713211084823"><a name="p109713211084823"></a><a name="p109713211084823"></a><a href="ipc.md#gae89f9a1282bd2d1b2a2b310c12ea16a5">SIGRTMIN</a>   (__libc_current_sigrtmin())</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p154721050084823"><a name="p154721050084823"></a><a name="p154721050084823"></a>Start of a reliable signal. </p>
</td>
</tr>
<tr id="row276275840084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p602303238084823"><a name="p602303238084823"></a><a name="p602303238084823"></a><a href="ipc.md#ga5336d2c76af22b10373e3dd28fb3b0f0">SIGRTMAX</a>   <a href="ipc.md#ga275020780cb70a8b0cba8db5accc5d19">_NSIG</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1377847350084823"><a name="p1377847350084823"></a><a name="p1377847350084823"></a>End of a reliable signal. </p>
</td>
</tr>
<tr id="row2075504782084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1287457988084823"><a name="p1287457988084823"></a><a name="p1287457988084823"></a><a href="ipc.md#ga5336d2c76af22b10373e3dd28fb3b0f0">SIGRTMAX</a>   (__libc_current_sigrtmax())</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p579899764084823"><a name="p579899764084823"></a><a name="p579899764084823"></a>End of a reliable signal. </p>
</td>
</tr>
<tr id="row1498270512084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478235730084823"><a name="p478235730084823"></a><a name="p478235730084823"></a><em id="ga93598c2382d6b05a1ff33edd21a1dcd0"><a name="ga93598c2382d6b05a1ff33edd21a1dcd0"></a><a name="ga93598c2382d6b05a1ff33edd21a1dcd0"></a></em>SA_THIRTYTWO    0x02000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1599046401084823"><a name="p1599046401084823"></a><a name="p1599046401084823"></a>Transfers signals in a 32-bit mode even if the task runs in a 26-bit mode. </p>
</td>
</tr>
<tr id="row1914543520084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1298313318084823"><a name="p1298313318084823"></a><a name="p1298313318084823"></a><em id="ga43c1d5510c7bedd95c0e4deac99e1729"><a name="ga43c1d5510c7bedd95c0e4deac99e1729"></a><a name="ga43c1d5510c7bedd95c0e4deac99e1729"></a></em>SA_NOMASK    <a href="ipc.md#gabec4abd80d73397fc2f78f57f178565f">SA_NODEFER</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330419533084823"><a name="p1330419533084823"></a><a name="p1330419533084823"></a>Signals being processed are not masked during signal processing. </p>
</td>
</tr>
<tr id="row1553148940084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1538544474084823"><a name="p1538544474084823"></a><a name="p1538544474084823"></a><em id="ga40c57ae45831edc27ae9ff933b11aa50"><a name="ga40c57ae45831edc27ae9ff933b11aa50"></a><a name="ga40c57ae45831edc27ae9ff933b11aa50"></a></em>SA_ONESHOT    <a href="ipc.md#ga8d5fb4f35858d31035e7354c1d4048ea">SA_RESETHAND</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p618559125084823"><a name="p618559125084823"></a><a name="p618559125084823"></a>The default processing mode is restored after the signal processing is complete. </p>
</td>
</tr>
<tr id="row1619976324084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382972882084823"><a name="p382972882084823"></a><a name="p382972882084823"></a><em id="ga927f6ae16379576d638006c7498ac5d7"><a name="ga927f6ae16379576d638006c7498ac5d7"></a><a name="ga927f6ae16379576d638006c7498ac5d7"></a></em>SIG_BLOCK    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093251945084823"><a name="p1093251945084823"></a><a name="p1093251945084823"></a>Defines the function behaviors such as <a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask()</a> and <a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask()</a>, which are used to add signals to the mask set. </p>
</td>
</tr>
<tr id="row1267898966084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1404863827084823"><a name="p1404863827084823"></a><a name="p1404863827084823"></a><em id="ga5fcd73313a63dac2cc7eb3b654215250"><a name="ga5fcd73313a63dac2cc7eb3b654215250"></a><a name="ga5fcd73313a63dac2cc7eb3b654215250"></a></em>SIG_UNBLOCK    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p336844318084823"><a name="p336844318084823"></a><a name="p336844318084823"></a>Defines the function behaviors such as <a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask()</a> and <a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask()</a>, which are used to remove signals from the mask set. </p>
</td>
</tr>
<tr id="row551421839084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1071046290084823"><a name="p1071046290084823"></a><a name="p1071046290084823"></a><em id="ga37750b78b7ae75fe02ad26e70f6cc845"><a name="ga37750b78b7ae75fe02ad26e70f6cc845"></a><a name="ga37750b78b7ae75fe02ad26e70f6cc845"></a></em>SIG_SETMASK    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648316443084823"><a name="p648316443084823"></a><a name="p648316443084823"></a>Defines the function behaviors such as <a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask()</a> and <a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask()</a>, which are used to set the mask set. </p>
</td>
</tr>
<tr id="row783795442084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1546971856084823"><a name="p1546971856084823"></a><a name="p1546971856084823"></a><a href="ipc.md#ga51d2f3aecb6f42d152e5f319e6b178b9">sa_handler</a>   _u._sa_handler</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533845922084823"><a name="p1533845922084823"></a><a name="p1533845922084823"></a>Defines the simplified writing used to indicate the <strong id="b317763642084823"><a name="b317763642084823"></a><a name="b317763642084823"></a>__sa_handler.sa_handler</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row1012425370084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p460882981084823"><a name="p460882981084823"></a><a name="p460882981084823"></a><a href="ipc.md#ga51d2f3aecb6f42d152e5f319e6b178b9">sa_handler</a>   __sa_handler.sa_handler</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71966487084823"><a name="p71966487084823"></a><a name="p71966487084823"></a>Defines the simplified writing used to indicate the <strong id="b614082601084823"><a name="b614082601084823"></a><a name="b614082601084823"></a>__sa_handler.sa_handler</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row1804021776084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1795771179084823"><a name="p1795771179084823"></a><a name="p1795771179084823"></a><a href="ipc.md#ga14be6197399829e41a778070ecebd9a3">sa_sigaction</a>   _u._sa_sigaction</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1348435354084823"><a name="p1348435354084823"></a><a name="p1348435354084823"></a>Defines the simplified writing used to indicate the <strong id="b1552797691084823"><a name="b1552797691084823"></a><a name="b1552797691084823"></a>__sa_handler.sa_sigaction</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row1828491548084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1502825626084823"><a name="p1502825626084823"></a><a name="p1502825626084823"></a><a href="ipc.md#ga14be6197399829e41a778070ecebd9a3">sa_sigaction</a>   __sa_handler.sa_sigaction</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012669840084823"><a name="p1012669840084823"></a><a name="p1012669840084823"></a>Defines the simplified writing used to indicate the <strong id="b410565842084823"><a name="b410565842084823"></a><a name="b410565842084823"></a>__sa_handler.sa_sigaction</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row530781710084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1598577764084823"><a name="p1598577764084823"></a><a name="p1598577764084823"></a><em id="ga0fa971487344a463a7f0545c9c9ef2bf"><a name="ga0fa971487344a463a7f0545c9c9ef2bf"></a><a name="ga0fa971487344a463a7f0545c9c9ef2bf"></a></em>SIG_HOLD    ((void (*)(int)) 2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354775191084823"><a name="p1354775191084823"></a><a name="p1354775191084823"></a>Defines the function behaviors such as <strong id="b1947385638084823"><a name="b1947385638084823"></a><a name="b1947385638084823"></a>sigset()</strong> and adds a specified signal to the process signal mask without changing the current processing mode of the signal. </p>
</td>
</tr>
<tr id="row687167252084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1071744423084823"><a name="p1071744423084823"></a><a name="p1071744423084823"></a><em id="ga06d5881eeb84e6ac35f5b801c380dbb6"><a name="ga06d5881eeb84e6ac35f5b801c380dbb6"></a><a name="ga06d5881eeb84e6ac35f5b801c380dbb6"></a></em>SIGEV_SIGNAL    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892566337084823"><a name="p892566337084823"></a><a name="p892566337084823"></a>Sets the notification method in <a href="sigevent.md">sigevent</a>: signal notification. </p>
</td>
</tr>
<tr id="row1673577752084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978848038084823"><a name="p1978848038084823"></a><a name="p1978848038084823"></a><em id="gaced9a66610d9d61756999ce4f103740e"><a name="gaced9a66610d9d61756999ce4f103740e"></a><a name="gaced9a66610d9d61756999ce4f103740e"></a></em>SIGEV_NONE    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1299869306084823"><a name="p1299869306084823"></a><a name="p1299869306084823"></a>Sets the notification method in <a href="sigevent.md">sigevent</a>: no notification. </p>
</td>
</tr>
<tr id="row1221581449084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911630257084823"><a name="p1911630257084823"></a><a name="p1911630257084823"></a><em id="ga29ccb6a17fa90a1357b478f62af7fca0"><a name="ga29ccb6a17fa90a1357b478f62af7fca0"></a><a name="ga29ccb6a17fa90a1357b478f62af7fca0"></a></em>SIGEV_THREAD    2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1845108843084823"><a name="p1845108843084823"></a><a name="p1845108843084823"></a>Sets the notification method in <a href="sigevent.md">sigevent</a>: thread notification. </p>
</td>
</tr>
<tr id="row958389175084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100606190084823"><a name="p2100606190084823"></a><a name="p2100606190084823"></a><em id="ga3c330fbddd84bf34e65af370b11998d6"><a name="ga3c330fbddd84bf34e65af370b11998d6"></a><a name="ga3c330fbddd84bf34e65af370b11998d6"></a></em>SIG_ERR    ((__sighandler_t)-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091619554084823"><a name="p1091619554084823"></a><a name="p1091619554084823"></a>Defines the value returned when a function such as <a href="ipc.md#gaf0f8ed40d30773bdb68e858ef0139b58">signal()</a> fails. </p>
</td>
</tr>
<tr id="row1030793346084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p837401171084823"><a name="p837401171084823"></a><a name="p837401171084823"></a><em id="ga27d5dc561093d6243542e6a2465bc0f8"><a name="ga27d5dc561093d6243542e6a2465bc0f8"></a><a name="ga27d5dc561093d6243542e6a2465bc0f8"></a></em>SIG_DFL    ((__sighandler_t)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1828911956084823"><a name="p1828911956084823"></a><a name="p1828911956084823"></a>Defines the default signal processing mode. </p>
</td>
</tr>
<tr id="row827299702084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1972821555084823"><a name="p1972821555084823"></a><a name="p1972821555084823"></a><em id="gacf0e499b0ac946b366b4f47a3b3e8b9e"><a name="gacf0e499b0ac946b366b4f47a3b3e8b9e"></a><a name="gacf0e499b0ac946b366b4f47a3b3e8b9e"></a></em>SIG_IGN    ((__sighandler_t)1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746243695084823"><a name="p746243695084823"></a><a name="p746243695084823"></a>Defines the signal processing mode in which the signal is ignored. </p>
</td>
</tr>
<tr id="row794112267084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1299693275084823"><a name="p1299693275084823"></a><a name="p1299693275084823"></a><em id="gace43f23fcb66ddaad964bb8ea8de6e9c"><a name="gace43f23fcb66ddaad964bb8ea8de6e9c"></a><a name="gace43f23fcb66ddaad964bb8ea8de6e9c"></a></em>IPC_CREAT    01000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743918312084823"><a name="p743918312084823"></a><a name="p743918312084823"></a>Defines the input parameter used to create an IPC object. </p>
</td>
</tr>
<tr id="row2000361995084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148153257084823"><a name="p148153257084823"></a><a name="p148153257084823"></a><em id="gacd312ab97691605718a3ee9a1c7c63e9"><a name="gacd312ab97691605718a3ee9a1c7c63e9"></a><a name="gacd312ab97691605718a3ee9a1c7c63e9"></a></em>IPC_EXCL    02000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850207696084823"><a name="p1850207696084823"></a><a name="p1850207696084823"></a>Defines the input parameter used together with <a href="ipc.md#gace43f23fcb66ddaad964bb8ea8de6e9c">IPC_CREAT</a> to prevent duplicate key values during IPC creation. </p>
</td>
</tr>
<tr id="row729620305084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035724688084823"><a name="p2035724688084823"></a><a name="p2035724688084823"></a><em id="ga5afdf5fc48bb22fa27fbd85627b189b9"><a name="ga5afdf5fc48bb22fa27fbd85627b189b9"></a><a name="ga5afdf5fc48bb22fa27fbd85627b189b9"></a></em>IPC_NOWAIT    04000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p95238691084823"><a name="p95238691084823"></a><a name="p95238691084823"></a>Defines the input parameter that specifies whether the communication is in non-blocking mode. </p>
</td>
</tr>
<tr id="row1718640771084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p487137850084823"><a name="p487137850084823"></a><a name="p487137850084823"></a><em id="ga752c83032a7bec60c904d97508ea4599"><a name="ga752c83032a7bec60c904d97508ea4599"></a><a name="ga752c83032a7bec60c904d97508ea4599"></a></em>IPC_RMID    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1891921835084823"><a name="p1891921835084823"></a><a name="p1891921835084823"></a>Defines the input parameter used to delete an IPC object. </p>
</td>
</tr>
<tr id="row497325212084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p782860543084823"><a name="p782860543084823"></a><a name="p782860543084823"></a><em id="ga1f1cdce55426e50878b1c71a4fc67a41"><a name="ga1f1cdce55426e50878b1c71a4fc67a41"></a><a name="ga1f1cdce55426e50878b1c71a4fc67a41"></a></em>IPC_SET    1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266106494084823"><a name="p1266106494084823"></a><a name="p1266106494084823"></a>Defines the input parameter used to set information to the kernel. </p>
</td>
</tr>
<tr id="row971914596084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027318189084823"><a name="p1027318189084823"></a><a name="p1027318189084823"></a><em id="ga17d3735e2d47ffa00a2cdf3a066f40d0"><a name="ga17d3735e2d47ffa00a2cdf3a066f40d0"></a><a name="ga17d3735e2d47ffa00a2cdf3a066f40d0"></a></em>IPC_INFO    3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987104602084823"><a name="p987104602084823"></a><a name="p987104602084823"></a>Defines the input parameter used to obtain the system-level restriction information of a specified communication type, for example, <a href="shminfo.md">shminfo</a>. </p>
</td>
</tr>
<tr id="row855781615084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1525685346084823"><a name="p1525685346084823"></a><a name="p1525685346084823"></a><em id="gae2b9b856a4a657c250b0b2e1cc0835d9"><a name="gae2b9b856a4a657c250b0b2e1cc0835d9"></a><a name="gae2b9b856a4a657c250b0b2e1cc0835d9"></a></em>IPC_PRIVATE    ((key_t) 0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p316708994084823"><a name="p316708994084823"></a><a name="p316708994084823"></a>Defines the IPC object as a private object. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table879235184084823"></a>
<table><thead align="left"><tr id="row511360389084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p560176644084823"><a name="p560176644084823"></a><a name="p560176644084823"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2079920474084823"><a name="p2079920474084823"></a><a name="p2079920474084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1705871993084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p693710542084823"><a name="p693710542084823"></a><a name="p693710542084823"></a><em id="ga1a2cdfb5c67c69b7aaab293b0946593b"><a name="ga1a2cdfb5c67c69b7aaab293b0946593b"></a><a name="ga1a2cdfb5c67c69b7aaab293b0946593b"></a></em>ucontext_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155855059084823"><a name="p155855059084823"></a><a name="p155855059084823"></a><strong id="b886797265"><a name="b886797265"></a><a name="b886797265"></a></strong> typedef struct <a href="__ucontext.md">__ucontext</a> </p>
<p id="p1497684047084823"><a name="p1497684047084823"></a><a name="p1497684047084823"></a>Describes the user execution context. </p>
</td>
</tr>
<tr id="row611350432084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1477942827084823"><a name="p1477942827084823"></a><a name="p1477942827084823"></a><a href="ipc.md#ga395f9ff4025fe05bb535322593abde72">stack_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804833030084823"><a name="p804833030084823"></a><a name="p804833030084823"></a>typedef struct <a href="sigaltstack.md">sigaltstack</a> </p>
<p id="p1059380228084823"><a name="p1059380228084823"></a><a name="p1059380228084823"></a>Describes a signal stack. </p>
</td>
</tr>
<tr id="row828609868084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453930624084823"><a name="p453930624084823"></a><a name="p453930624084823"></a><em id="ga754cdc0bcfffe07baa426dc252c9101a"><a name="ga754cdc0bcfffe07baa426dc252c9101a"></a><a name="ga754cdc0bcfffe07baa426dc252c9101a"></a></em>sighandler_t ) (int)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103373543084823"><a name="p1103373543084823"></a><a name="p1103373543084823"></a><strong id="b823442100"><a name="b823442100"></a><a name="b823442100"></a></strong> typedef void(* </p>
<p id="p1429395046084823"><a name="p1429395046084823"></a><a name="p1429395046084823"></a>Function pointer of signal handler. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table454437204084823"></a>
<table><thead align="left"><tr id="row226466382084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p537923775084823"><a name="p537923775084823"></a><a name="p537923775084823"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2058245278084823"><a name="p2058245278084823"></a><a name="p2058245278084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1240497844084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1113471188084823"><a name="p1113471188084823"></a><a name="p1113471188084823"></a><a href="ipc.md#ga3fbd3906296be63451c64d69be2bc371">mq_close</a> (mqd_t mqdes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2119878037084823"><a name="p2119878037084823"></a><a name="p2119878037084823"></a>int </p>
<p id="p1781016748084823"><a name="p1781016748084823"></a><a name="p1781016748084823"></a>Closes a message queue that is no longer used. </p>
</td>
</tr>
<tr id="row710397975084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1094407882084823"><a name="p1094407882084823"></a><a name="p1094407882084823"></a><a href="ipc.md#ga8fafe8b1183830322f8ff875f4e6cb4c">mq_getattr</a> (mqd_t mqdes, struct <a href="mq_attr.md">mq_attr</a> *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p624583127084823"><a name="p624583127084823"></a><a name="p624583127084823"></a>int </p>
<p id="p1019308073084823"><a name="p1019308073084823"></a><a name="p1019308073084823"></a>Obtains the attributes of the message queue specified by the descriptor. The values of <strong id="b1238745013084823"><a name="b1238745013084823"></a><a name="b1238745013084823"></a>mq_maxmsg</strong>, <strong id="b667826402084823"><a name="b667826402084823"></a><a name="b667826402084823"></a>mq_msgsize</strong>, and <strong id="b1235912871084823"><a name="b1235912871084823"></a><a name="b1235912871084823"></a>mq_curmsgs</strong> are fixed. </p>
</td>
</tr>
<tr id="row1565944527084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1918968158084823"><a name="p1918968158084823"></a><a name="p1918968158084823"></a><a href="ipc.md#gaf5d8bf423701bd1783849119511381a5">mq_open</a> (const char *name, int oflag,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135835334084823"><a name="p2135835334084823"></a><a name="p2135835334084823"></a>mqd_t </p>
<p id="p763314039084823"><a name="p763314039084823"></a><a name="p763314039084823"></a>Creates a message queue or opens an existing message queue. </p>
</td>
</tr>
<tr id="row1815036226084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985669760084823"><a name="p1985669760084823"></a><a name="p1985669760084823"></a><a href="ipc.md#gafcd715bf914289ca502136ef7022eab7">mq_receive</a> (mqd_t mqdes, char *buffer, size_t size, unsigned *prioptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p575908153084823"><a name="p575908153084823"></a><a name="p575908153084823"></a>ssize_t </p>
<p id="p1734670911084823"><a name="p1734670911084823"></a><a name="p1734670911084823"></a>Receives a message from a specified message queue. </p>
</td>
</tr>
<tr id="row1789722554084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1162720910084823"><a name="p1162720910084823"></a><a name="p1162720910084823"></a><a href="ipc.md#ga2d07e256d809a61bdc82178cb0dd1ba1">mq_send</a> (mqd_t mqdes, const char *buffer, size_t size, unsigned prio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440497178084823"><a name="p440497178084823"></a><a name="p440497178084823"></a>int </p>
<p id="p2005243731084823"><a name="p2005243731084823"></a><a name="p2005243731084823"></a>Sends a message to a specified message queue. </p>
</td>
</tr>
<tr id="row1654855758084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p119077866084823"><a name="p119077866084823"></a><a name="p119077866084823"></a><a href="ipc.md#gaf5cc07adf7823fac8611200b55fc3a27">mq_setattr</a> (mqd_t mqdes, const struct <a href="mq_attr.md">mq_attr</a> *__restrict newattr, struct <a href="mq_attr.md">mq_attr</a> *__restrict oldattr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137219943084823"><a name="p2137219943084823"></a><a name="p2137219943084823"></a>int </p>
<p id="p1275207356084823"><a name="p1275207356084823"></a><a name="p1275207356084823"></a>Sets the attributes of the message queue specified by the descriptor. The <strong id="b201199676084823"><a name="b201199676084823"></a><a name="b201199676084823"></a>mq_maxmsg</strong>, <strong id="b1165515940084823"><a name="b1165515940084823"></a><a name="b1165515940084823"></a>mq_msgsize</strong>, and <strong id="b981365929084823"><a name="b981365929084823"></a><a name="b981365929084823"></a>mq_curmsgs</strong> attributes cannot be modified. <strong id="b840887346084823"><a name="b840887346084823"></a><a name="b840887346084823"></a>mq_flags</strong> supports the <strong id="b1967933143084823"><a name="b1967933143084823"></a><a name="b1967933143084823"></a>O_NONBLOCK</strong> attribute only. </p>
</td>
</tr>
<tr id="row1235355010084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1558374333084823"><a name="p1558374333084823"></a><a name="p1558374333084823"></a><a href="ipc.md#gaa291cc1bc8bb02fd24bd0d4c563350f4">mq_timedreceive</a> (mqd_t mqdes, char *__restrict buffer, size_t size, unsigned *__restrict prioptr, const struct <a href="timespec.md">timespec</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1001326156084823"><a name="p1001326156084823"></a><a name="p1001326156084823"></a>ssize_t </p>
<p id="p585240817084823"><a name="p585240817084823"></a><a name="p585240817084823"></a>Receives a message from the message queue, with a timeout period specified. </p>
</td>
</tr>
<tr id="row318323380084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1584650903084823"><a name="p1584650903084823"></a><a name="p1584650903084823"></a><a href="ipc.md#gae59709d01cc34d009edfeae9900568cb">mq_timedsend</a> (mqd_t mqdes, const char *buffer, size_t size, unsigned prio, const struct <a href="timespec.md">timespec</a> *timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135734189084823"><a name="p2135734189084823"></a><a name="p2135734189084823"></a>int </p>
<p id="p1057620716084823"><a name="p1057620716084823"></a><a name="p1057620716084823"></a>Sends a message to a specified message queue, with a timeout period specified. </p>
</td>
</tr>
<tr id="row1007817121084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408390923084823"><a name="p1408390923084823"></a><a name="p1408390923084823"></a><a href="ipc.md#gaccd8c5ee36e60d990963e1d544ef4140">mq_unlink</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823992510084823"><a name="p823992510084823"></a><a name="p823992510084823"></a>int </p>
<p id="p589493602084823"><a name="p589493602084823"></a><a name="p589493602084823"></a>Decreases the reference count of the message queue by 1, or deletes the message queue if the reference count is <strong id="b522103475084823"><a name="b522103475084823"></a><a name="b522103475084823"></a>0</strong>. </p>
</td>
</tr>
<tr id="row499868865084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9021194084823"><a name="p9021194084823"></a><a name="p9021194084823"></a><a href="ipc.md#ga4e398fea1080fd7919e5c72ee94e2fc5">sem_close</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p824548598084823"><a name="p824548598084823"></a><a name="p824548598084823"></a>int </p>
<p id="p2079901908084823"><a name="p2079901908084823"></a><a name="p2079901908084823"></a>Closes a specified semaphore. </p>
</td>
</tr>
<tr id="row1174545136084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737007638084823"><a name="p737007638084823"></a><a name="p737007638084823"></a><a href="ipc.md#ga6bc9a7dd941a9b5e319715b767af5682">sem_destroy</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791779339084823"><a name="p791779339084823"></a><a name="p791779339084823"></a>int </p>
<p id="p561574771084823"><a name="p561574771084823"></a><a name="p561574771084823"></a>Destroys a specified anonymous semaphore that is no longer used. </p>
</td>
</tr>
<tr id="row1892256900084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650406801084823"><a name="p1650406801084823"></a><a name="p1650406801084823"></a><a href="ipc.md#ga934bcc3cbc0c67a9e3a8e7a43c023460">sem_getvalue</a> (<a href="sem_t.md">sem_t</a> *__restrict sem, int *__restrict sval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003335864084823"><a name="p2003335864084823"></a><a name="p2003335864084823"></a>int </p>
<p id="p355809002084823"><a name="p355809002084823"></a><a name="p355809002084823"></a>Obtains the count value of a specified semaphore. </p>
</td>
</tr>
<tr id="row1349311341084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p598873609084823"><a name="p598873609084823"></a><a name="p598873609084823"></a><a href="ipc.md#ga532509bd8a6499f8193253192fb83a3d">sem_init</a> (<a href="sem_t.md">sem_t</a> *sem, int pshared, unsigned int value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334035199084823"><a name="p334035199084823"></a><a name="p334035199084823"></a>int </p>
<p id="p302765075084823"><a name="p302765075084823"></a><a name="p302765075084823"></a>Creates and initializes an anonymous semaphore. </p>
</td>
</tr>
<tr id="row1556081416084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1371278372084823"><a name="p1371278372084823"></a><a name="p1371278372084823"></a><a href="ipc.md#ga015dce85cab8477c679cc47968958247">sem_post</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029899158084823"><a name="p2029899158084823"></a><a name="p2029899158084823"></a>int </p>
<p id="p1117732839084823"><a name="p1117732839084823"></a><a name="p1117732839084823"></a>Increments the semaphore count by 1. </p>
</td>
</tr>
<tr id="row1271734632084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1724934009084823"><a name="p1724934009084823"></a><a name="p1724934009084823"></a><a href="ipc.md#ga9d832817226c594e7628e2cc7ed7d723">sem_timedwait</a> (<a href="sem_t.md">sem_t</a> *__restrict sem, const struct <a href="timespec.md">timespec</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114138333084823"><a name="p114138333084823"></a><a name="p114138333084823"></a>int </p>
<p id="p2137175907084823"><a name="p2137175907084823"></a><a name="p2137175907084823"></a>Obtains the semaphore, with a timeout period specified. </p>
</td>
</tr>
<tr id="row1450885366084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p227322627084823"><a name="p227322627084823"></a><a name="p227322627084823"></a><a href="ipc.md#ga4de7a9a334b01b6373b017aaefa07cf0">sem_trywait</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140495278084823"><a name="p2140495278084823"></a><a name="p2140495278084823"></a>int </p>
<p id="p527226282084823"><a name="p527226282084823"></a><a name="p527226282084823"></a>Attempts to obtain the semaphore. </p>
</td>
</tr>
<tr id="row1033787015084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p172415408084823"><a name="p172415408084823"></a><a name="p172415408084823"></a><a href="ipc.md#ga776256d1a473906f8b7490689bfcb75c">sem_unlink</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1548292140084823"><a name="p1548292140084823"></a><a name="p1548292140084823"></a>int </p>
<p id="p1756966523084823"><a name="p1756966523084823"></a><a name="p1756966523084823"></a>Deletes a specified semaphore. </p>
</td>
</tr>
<tr id="row2102424818084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1389660093084823"><a name="p1389660093084823"></a><a name="p1389660093084823"></a><a href="ipc.md#gaad70020dca2241a2b78e272ca033271b">sem_wait</a> (<a href="sem_t.md">sem_t</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730305232084823"><a name="p1730305232084823"></a><a name="p1730305232084823"></a>int </p>
<p id="p1243485011084823"><a name="p1243485011084823"></a><a name="p1243485011084823"></a>Obtains the semaphore. </p>
</td>
</tr>
<tr id="row779561425084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1957827292084823"><a name="p1957827292084823"></a><a name="p1957827292084823"></a><a href="ipc.md#ga4539db972bcf3dd8c8b429af0dc3789d">kill</a> (pid_t pid, int sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p21432879084823"><a name="p21432879084823"></a><a name="p21432879084823"></a>int </p>
<p id="p259201899084823"><a name="p259201899084823"></a><a name="p259201899084823"></a>Sends a signal to a specified process. </p>
</td>
</tr>
<tr id="row2066351744084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1137754614084823"><a name="p1137754614084823"></a><a name="p1137754614084823"></a><a href="ipc.md#ga5925352f90eb589393274fa0376d7def">sigemptyset</a> (sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p131157677084823"><a name="p131157677084823"></a><a name="p131157677084823"></a>int </p>
<p id="p747662361084823"><a name="p747662361084823"></a><a name="p747662361084823"></a>Clears all signals in a specified signal set. </p>
</td>
</tr>
<tr id="row1998862020084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1231242168084823"><a name="p1231242168084823"></a><a name="p1231242168084823"></a><a href="ipc.md#ga88d7bbc77ea1569ee21c90db549ea023">sigfillset</a> (sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p167484225084823"><a name="p167484225084823"></a><a name="p167484225084823"></a>int </p>
<p id="p754773271084823"><a name="p754773271084823"></a><a name="p754773271084823"></a>Adds all signals to a specified signal set. </p>
</td>
</tr>
<tr id="row1180731606084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878057573084823"><a name="p878057573084823"></a><a name="p878057573084823"></a><a href="ipc.md#gae412e6a5436a6c28424b0173251d349c">sigaddset</a> (sigset_t *set, int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1768934668084823"><a name="p1768934668084823"></a><a name="p1768934668084823"></a>int </p>
<p id="p707482861084823"><a name="p707482861084823"></a><a name="p707482861084823"></a>Adds a signal to a specified signal set. </p>
</td>
</tr>
<tr id="row233326182084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363571642084823"><a name="p363571642084823"></a><a name="p363571642084823"></a><a href="ipc.md#gab0025e4f32ce2737c40cc0074cc6d7d2">sigdelset</a> (sigset_t *set, int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1254351160084823"><a name="p1254351160084823"></a><a name="p1254351160084823"></a>int </p>
<p id="p876090930084823"><a name="p876090930084823"></a><a name="p876090930084823"></a>Delete a signal from a specified signal set. </p>
</td>
</tr>
<tr id="row295408525084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205746784084823"><a name="p205746784084823"></a><a name="p205746784084823"></a><a href="ipc.md#ga63693cc65f43d772729b588b453fe1ef">sigismember</a> (const sigset_t *set, int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417248347084823"><a name="p1417248347084823"></a><a name="p1417248347084823"></a>int </p>
<p id="p1174143580084823"><a name="p1174143580084823"></a><a name="p1174143580084823"></a>Checks whether a signal is in the signal set. </p>
</td>
</tr>
<tr id="row353549312084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609310602084823"><a name="p609310602084823"></a><a name="p609310602084823"></a><a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask</a> (int how, const sigset_t *__restrict set, sigset_t *__restrict oldset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p471663123084823"><a name="p471663123084823"></a><a name="p471663123084823"></a>int </p>
<p id="p1111692693084823"><a name="p1111692693084823"></a><a name="p1111692693084823"></a>Changes the signal mask of the calling thread. </p>
</td>
</tr>
<tr id="row819279794084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p72797014084823"><a name="p72797014084823"></a><a name="p72797014084823"></a><a href="ipc.md#gae5f92586ad50092a7813465eeef792c0">sigsuspend</a> (const sigset_t *mask)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452477659084823"><a name="p452477659084823"></a><a name="p452477659084823"></a>int </p>
<p id="p2134145113084823"><a name="p2134145113084823"></a><a name="p2134145113084823"></a>Sets <strong id="b1120941431084823"><a name="b1120941431084823"></a><a name="b1120941431084823"></a>mask</strong> as the signal mask set of the current process and suspends the process until a signal processing action is triggered. </p>
</td>
</tr>
<tr id="row510646479084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886651043084823"><a name="p1886651043084823"></a><a name="p1886651043084823"></a><a href="ipc.md#ga5263ce0feb3eb0934bc56ab81cae8ddb">sigaction</a> (int signum, const struct <a href="sigaction.md">sigaction</a> *__restrict act, struct <a href="sigaction.md">sigaction</a> *__restrict oldact)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1817054066084823"><a name="p1817054066084823"></a><a name="p1817054066084823"></a>int </p>
<p id="p1998136680084823"><a name="p1998136680084823"></a><a name="p1998136680084823"></a>Checks or changes the processing action associated with a specified signal. Do not use the process creation function or thread creation function in the registered callback processing function. Otherwise, the process is abnormal. For example, do not use the <strong id="b1565415376084823"><a name="b1565415376084823"></a><a name="b1565415376084823"></a>fork</strong> or <strong id="b43426198084823"><a name="b43426198084823"></a><a name="b43426198084823"></a>pthread_create</strong> function. </p>
</td>
</tr>
<tr id="row1910664372084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p668012683084823"><a name="p668012683084823"></a><a name="p668012683084823"></a><a href="ipc.md#ga7b91eecad5998acd6162fde3ab530d7a">sigpending</a> (sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923578099084823"><a name="p923578099084823"></a><a name="p923578099084823"></a>int </p>
<p id="p2121024664084823"><a name="p2121024664084823"></a><a name="p2121024664084823"></a>Obtains the signal suspended by the current thread. </p>
</td>
</tr>
<tr id="row1351011324084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1098238655084823"><a name="p1098238655084823"></a><a name="p1098238655084823"></a><a href="ipc.md#ga900d91a9635b965dbbae6b3cee2d2a2b">sigwait</a> (const sigset_t *__restrict set, int *__restrict sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705940534084823"><a name="p1705940534084823"></a><a name="p1705940534084823"></a>int </p>
<p id="p1471965845084823"><a name="p1471965845084823"></a><a name="p1471965845084823"></a>Suspends the calling thread and waits for the signal. </p>
</td>
</tr>
<tr id="row2092621775084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p366738637084823"><a name="p366738637084823"></a><a name="p366738637084823"></a><a href="ipc.md#ga786f18a8e5b7eceed0ddcdc722f3340b">sigwaitinfo</a> (const sigset_t *__restrict set, siginfo_t *__restrict info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246110552084823"><a name="p246110552084823"></a><a name="p246110552084823"></a>int </p>
<p id="p2040620282084823"><a name="p2040620282084823"></a><a name="p2040620282084823"></a>Suspends the calling thread and waits for the signal, with a timeout period specified. </p>
</td>
</tr>
<tr id="row1577633099084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024016032084823"><a name="p1024016032084823"></a><a name="p1024016032084823"></a><a href="ipc.md#ga155a526c3da5ffd1a79ba2925bdd278a">sigtimedwait</a> (const sigset_t *__restrict set, siginfo_t *__restrict info, const struct <a href="timespec.md">timespec</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1785267877084823"><a name="p1785267877084823"></a><a name="p1785267877084823"></a>int </p>
<p id="p2054172984084823"><a name="p2054172984084823"></a><a name="p2054172984084823"></a>Suspends the calling thread and waits for the signal, with a timeout period specified. </p>
</td>
</tr>
<tr id="row515543902084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658816461084823"><a name="p658816461084823"></a><a name="p658816461084823"></a><a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask</a> (int how, const sigset_t *__restrict set, sigset_t *__restrict oldset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877270286084823"><a name="p1877270286084823"></a><a name="p1877270286084823"></a>int </p>
<p id="p1494825846084823"><a name="p1494825846084823"></a><a name="p1494825846084823"></a>Checks or changes the signal mask of the calling thread. </p>
</td>
</tr>
<tr id="row230430133084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583289058084823"><a name="p583289058084823"></a><a name="p583289058084823"></a><a href="ipc.md#gada1fed9730b224a68e768e5f2eac53ff">psignal</a> (int signum, const char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849818016084823"><a name="p1849818016084823"></a><a name="p1849818016084823"></a>void </p>
<p id="p440465787084823"><a name="p440465787084823"></a><a name="p440465787084823"></a>Prints signal information. </p>
</td>
</tr>
<tr id="row860320659084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381476584084823"><a name="p381476584084823"></a><a name="p381476584084823"></a><a href="ipc.md#ga95a78da8c44db11c7031b678504d0b34">sigpause</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p595706333084823"><a name="p595706333084823"></a><a name="p595706333084823"></a>int </p>
<p id="p498296763084823"><a name="p498296763084823"></a><a name="p498296763084823"></a>Deletes the signal specified by <strong id="b642343994084823"><a name="b642343994084823"></a><a name="b642343994084823"></a>signum</strong> from the signal mask of the calling process and suspends the process until the signal is received. </p>
</td>
</tr>
<tr id="row1492131544084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1659551161084823"><a name="p1659551161084823"></a><a name="p1659551161084823"></a><a href="ipc.md#ga4378a40ea3370c436d4e46c7a2a58172">sighold</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946887814084823"><a name="p946887814084823"></a><a name="p946887814084823"></a>int </p>
<p id="p116833608084823"><a name="p116833608084823"></a><a name="p116833608084823"></a>Adds the signal specified by <strong id="b641472891084823"><a name="b641472891084823"></a><a name="b641472891084823"></a>signum</strong> to the signal mask of the calling process. </p>
</td>
</tr>
<tr id="row992573442084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p97704826084823"><a name="p97704826084823"></a><a name="p97704826084823"></a><a href="ipc.md#ga96c4aed60b8b727709887e1fae0f5bea">sigrelse</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1975559977084823"><a name="p1975559977084823"></a><a name="p1975559977084823"></a>int </p>
<p id="p86198151084823"><a name="p86198151084823"></a><a name="p86198151084823"></a>Deletes the signal specified by <strong id="b1656596653084823"><a name="b1656596653084823"></a><a name="b1656596653084823"></a>signum</strong> from the signal mask of the calling process. </p>
</td>
</tr>
<tr id="row489475642084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379121942084823"><a name="p1379121942084823"></a><a name="p1379121942084823"></a><a href="ipc.md#gac41035aa05cb4523ae93e8a6d55f9453">sigisemptyset</a> (const sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1343642399084823"><a name="p1343642399084823"></a><a name="p1343642399084823"></a>int </p>
<p id="p1431560465084823"><a name="p1431560465084823"></a><a name="p1431560465084823"></a>Checks whether the signal set is empty. </p>
</td>
</tr>
<tr id="row888028651084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898074224084823"><a name="p1898074224084823"></a><a name="p1898074224084823"></a><a href="ipc.md#ga1a0d037b7fd84fb392a4c2ffc6c3525c">sigorset</a> (sigset_t *dest, const sigset_t *left, const sigset_t *right)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p22766519084823"><a name="p22766519084823"></a><a name="p22766519084823"></a>int </p>
<p id="p1704469925084823"><a name="p1704469925084823"></a><a name="p1704469925084823"></a>Adds the union set of <strong id="b2140054165084823"><a name="b2140054165084823"></a><a name="b2140054165084823"></a>left</strong> and <strong id="b1412018826084823"><a name="b1412018826084823"></a><a name="b1412018826084823"></a>right</strong> to <strong id="b1996489889084823"><a name="b1996489889084823"></a><a name="b1996489889084823"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row1135720888084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015497931084823"><a name="p2015497931084823"></a><a name="p2015497931084823"></a><a href="ipc.md#ga2a0910ff9d18931a05b995143dc4576e">sigandset</a> (sigset_t *dest, const sigset_t *left, const sigset_t *right)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1982750994084823"><a name="p1982750994084823"></a><a name="p1982750994084823"></a>int </p>
<p id="p536070259084823"><a name="p536070259084823"></a><a name="p536070259084823"></a>Adds the intersection of <strong id="b682520007084823"><a name="b682520007084823"></a><a name="b682520007084823"></a>left</strong> and <strong id="b1050458249084823"><a name="b1050458249084823"></a><a name="b1050458249084823"></a>right</strong> to <strong id="b1799756073084823"><a name="b1799756073084823"></a><a name="b1799756073084823"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row1070270567084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032534817084823"><a name="p2032534817084823"></a><a name="p2032534817084823"></a><a href="ipc.md#gaf0f8ed40d30773bdb68e858ef0139b58">signal</a> (int signum, <a href="ipc.md#ga754cdc0bcfffe07baa426dc252c9101a">sighandler_t</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101551531084823"><a name="p101551531084823"></a><a name="p101551531084823"></a><a href="ipc.md#ga754cdc0bcfffe07baa426dc252c9101a">sighandler_t</a> </p>
<p id="p1840159719084823"><a name="p1840159719084823"></a><a name="p1840159719084823"></a>Changes the processing action of a specified signal. Do not use the process creation function or thread creation function in the registered callback processing function. Otherwise, the process is abnormal. For example, do not use the <strong id="b1418920606084823"><a name="b1418920606084823"></a><a name="b1418920606084823"></a>fork</strong> or <strong id="b1652476399084823"><a name="b1652476399084823"></a><a name="b1652476399084823"></a>pthread_create</strong> function. </p>
</td>
</tr>
<tr id="row1910683649084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1719126487084823"><a name="p1719126487084823"></a><a name="p1719126487084823"></a><a href="ipc.md#ga350675984ca13ce9b056e69098bda5c6">raise</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896002832084823"><a name="p896002832084823"></a><a name="p896002832084823"></a>int </p>
<p id="p799586414084823"><a name="p799586414084823"></a><a name="p799586414084823"></a>Sends a signal to the calling process. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section588097269084823"></a>

## **Macro Definition Documentation**<a name="section2095012183084823"></a>

## MINSIGSTKSZ \[1/2\]<a name="gaae6a742a8c5acf12caba1d148dd03f10"></a>

```
#define MINSIGSTKSZ   2048
```

 **Description:**

Defines the minimum size of the replaceable signal stack. 

Minimum size of the replaceable signal stack. 

## MINSIGSTKSZ \[2/2\]<a name="section1677364088"></a>

```
#define MINSIGSTKSZ   2048
```

 **Description:**

Defines the minimum size of the replaceable signal stack. 

Minimum size of the replaceable signal stack. 

## sa\_handler \[1/2\]<a name="ga51d2f3aecb6f42d152e5f319e6b178b9"></a>

```
#define sa_handler   _u._sa_handler
```

 **Description:**

Defines the simplified writing used to indicate the  **\_\_sa\_handler.sa\_handler**  field in  [sigaction](sigaction.md). 

Indicates the  **\_u.\_sa\_handler**  field in  [sigaction](sigaction.md). 

## sa\_handler \[2/2\]<a name="section471272338"></a>

```
#define sa_handler   __sa_handler.sa_handler
```

 **Description:**

Defines the simplified writing used to indicate the  **\_\_sa\_handler.sa\_handler**  field in  [sigaction](sigaction.md). 

Indicates the  **\_u.\_sa\_handler**  field in  [sigaction](sigaction.md). 

## SA\_NOCLDSTOP \[1/2\]<a name="gaf6a71c97263725437f59ceb16241fd32"></a>

```
#define SA_NOCLDSTOP   1
```

 **Description:**

Stops a child process without sending the  [SIGCHLD](ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8)  signal. 

[SIGCHLD](ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8)  is not generated when the child process is stopped. 

## SA\_NOCLDSTOP \[2/2\]<a name="section1538081962"></a>

```
#define SA_NOCLDSTOP   0x00000001
```

 **Description:**

Stops a child process without sending the  [SIGCHLD](ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8)  signal. 

[SIGCHLD](ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8)  is not generated when the child process is stopped. 

## SA\_NODEFER \[1/2\]<a name="gabec4abd80d73397fc2f78f57f178565f"></a>

```
#define SA_NODEFER   0x40000000
```

 **Description:**

The signals being processed are not masked during signal processing. 

Signals being processed are not masked during signal processing. 

## SA\_NODEFER \[2/2\]<a name="section817152028"></a>

```
#define SA_NODEFER   0x40000000
```

 **Description:**

The signals being processed are not masked during signal processing. 

Signals being processed are not masked during signal processing. 

## SA\_ONSTACK \[1/2\]<a name="ga322c220e296393958ab4238145a0d273"></a>

```
#define SA_ONSTACK   0x08000000
```

 **Description:**

Uses the signal stack specified by  [sigaltstack](sigaltstack.md)  for signal processing. 

The signal stack specified by  [sigaltstack](sigaltstack.md)  is used for signal processing. 

## SA\_ONSTACK \[2/2\]<a name="section1474084447"></a>

```
#define SA_ONSTACK   0x08000000
```

 **Description:**

Uses the signal stack specified by  [sigaltstack](sigaltstack.md)  for signal processing. 

The signal stack specified by  [sigaltstack](sigaltstack.md)  is used for signal processing. 

## sa\_sigaction \[1/2\]<a name="ga14be6197399829e41a778070ecebd9a3"></a>

```
#define sa_sigaction   _u._sa_sigaction
```

 **Description:**

Defines the simplified writing used to indicate the  **\_\_sa\_handler.sa\_sigaction**  field in  [sigaction](sigaction.md). 

Indicates the  **\_\_sa\_handler.sa\_sigaction**  field in  [sigaction](sigaction.md). 

## sa\_sigaction \[2/2\]<a name="section2086931049"></a>

```
#define sa_sigaction   __sa_handler.sa_sigaction
```

 **Description:**

Defines the simplified writing used to indicate the  **\_\_sa\_handler.sa\_sigaction**  field in  [sigaction](sigaction.md). 

Indicates the  **\_\_sa\_handler.sa\_sigaction**  field in  [sigaction](sigaction.md). 

## SA\_SIGINFO \[1/2\]<a name="ga59b4c0774aace526b10b6d737075a790"></a>

```
#define SA_SIGINFO   4
```

 **Description:**

Transfers the  **siginfo\_t**  structure with the signal. 

Transfers the  **siginfo\_t**  with the signal. 

## SA\_SIGINFO \[2/2\]<a name="section1277311723"></a>

```
#define SA_SIGINFO   0x00000004
```

 **Description:**

Transfers the  **siginfo\_t**  structure with the signal. 

Transfers the  **siginfo\_t**  with the signal. 

## SIGRTMAX \[1/2\]<a name="ga5336d2c76af22b10373e3dd28fb3b0f0"></a>

```
#define SIGRTMAX   [_NSIG](ipc.md#ga275020780cb70a8b0cba8db5accc5d19)
```

 **Description:**

End of a reliable signal. 

Defines the highest available signal number. 

## SIGRTMAX \[2/2\]<a name="section2142597593"></a>

```
#define SIGRTMAX   (__libc_current_sigrtmax())
```

 **Description:**

End of a reliable signal. 

Defines the highest available signal number. 

## SIGRTMIN \[1/2\]<a name="gae89f9a1282bd2d1b2a2b310c12ea16a5"></a>

```
#define SIGRTMIN   32
```

 **Description:**

Start of a reliable signal. 

Defines the lowest available signal number. 

## SIGRTMIN \[2/2\]<a name="section186821911"></a>

```
#define SIGRTMIN   (__libc_current_sigrtmin())
```

 **Description:**

Start of a reliable signal. 

Defines the lowest available signal number. 

## SIGSTKSZ \[1/2\]<a name="ga8a433a10420a0c51355da26cfcab2131"></a>

```
#define SIGSTKSZ   8192
```

 **Description:**

Defines the size of a signal stack. 

Size of a signal stack. 

## SIGSTKSZ \[2/2\]<a name="section513684812"></a>

```
#define SIGSTKSZ   8192
```

 **Description:**

Defines the size of a signal stack. 

Size of a signal stack. 

## **Typedef Documentation**<a name="section1817647957084823"></a>

## stack\_t<a name="ga395f9ff4025fe05bb535322593abde72"></a>

```
typedef struct [sigaltstack](sigaltstack.md) [stack_t](ipc.md#ga395f9ff4025fe05bb535322593abde72)
```

 **Description:**

Describes a signal stack. 

Describes stack information for signal processing. 

## **Function Documentation**<a name="section107274842084823"></a>

## kill\(\)<a name="ga4539db972bcf3dd8c8b429af0dc3789d"></a>

```
int kill (pid_t pid, int sig )
```

 **Description:**

Sends a signal to a specified process. 

**Parameters:**

<a name="table238110802084823"></a>
<table><thead align="left"><tr id="row581149692084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p896954348084823"><a name="p896954348084823"></a><a name="p896954348084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p837790373084823"><a name="p837790373084823"></a><a name="p837790373084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row388176368084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target process ID. Parameters <strong id="b69416775084823"><a name="b69416775084823"></a><a name="b69416775084823"></a>0</strong> and <strong id="b1582709356084823"><a name="b1582709356084823"></a><a name="b1582709356084823"></a>-1</strong> are not supported. </td>
</tr>
<tr id="row1317324715084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sig</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be sent. </td>
</tr>
</tbody>
</table>

**Attention:**

The default signal behavior does not support  **STOP**  and  **CONTINUE**, and  **COREDUMP**  is not involved.  [SIGSTOP](ipc.md#ga069e358bc9a864b7dc4fed2440eda14c),  [SIGKILL](ipc.md#gaddd8dcd406ce514ab3b4f576a5343d42), and  [SIGCONT](ipc.md#ga024f43063003e753afc6cca1acd6e104)  cannot be masked. If a process is killed but its parent process is not recycled, a zombie process will be generated. After an asynchronous signal is sent to a process, the signal callback is executed only after the process is scheduled. The kernel cannot forcibly kill the process by using the signal. After the process is killed,  [SIGCHLD](ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8)  is sent to its parent process. The sending action cannot be canceled. A sleeping process cannot be woken up by a signal. For example, a process invokes the  **sleep**  function to enter the sleeping state. Currently, suspended and zombie processes cannot be forcibly killed. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table950811965084823"></a>
<table><thead align="left"><tr id="row218372331084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p382437678084823"><a name="p382437678084823"></a><a name="p382437678084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1780400220084823"><a name="p1780400220084823"></a><a name="p1780400220084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2038050133084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888425095084823"><a name="p1888425095084823"></a><a name="p1888425095084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p295942931084823"><a name="p295942931084823"></a><a name="p295942931084823"></a><strong id="b427867788084823"><a name="b427867788084823"></a><a name="b427867788084823"></a>sig</strong> is invalid. </p>
</td>
</tr>
<tr id="row2038547324084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1291465085084823"><a name="p1291465085084823"></a><a name="p1291465085084823"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417186367084823"><a name="p1417186367084823"></a><a name="p1417186367084823"></a>The current process does not have permission to send the signal to the target process. </p>
</td>
</tr>
</tbody>
</table>

## mq\_close\(\)<a name="ga3fbd3906296be63451c64d69be2bc371"></a>

```
int mq_close (mqd_t mqdes)
```

 **Description:**

Closes a message queue that is no longer used. 

**Parameters:**

<a name="table163195603084823"></a>
<table><thead align="left"><tr id="row1555340551084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p770471546084823"><a name="p770471546084823"></a><a name="p770471546084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p493232490084823"><a name="p493232490084823"></a><a name="p493232490084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row208500623084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the descriptor of the message queue to be closed. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the message queue is closed; returns  **-1**  and sets  **errno**  to a value in the following table if the message queue fails to be closed. 

<a name="table573980843084823"></a>
<table><thead align="left"><tr id="row200597144084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p266999171084823"><a name="p266999171084823"></a><a name="p266999171084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p232847444084823"><a name="p232847444084823"></a><a name="p232847444084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row398315282084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48258239084823"><a name="p48258239084823"></a><a name="p48258239084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666615661084823"><a name="p1666615661084823"></a><a name="p1666615661084823"></a><strong id="b1674781724084823"><a name="b1674781724084823"></a><a name="b1674781724084823"></a>mqdes</strong> is invalid. </p>
</td>
</tr>
<tr id="row692093255084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586585609084823"><a name="p586585609084823"></a><a name="p586585609084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1013711617084823"><a name="p1013711617084823"></a><a name="p1013711617084823"></a>Failed to delete the message queue in the function. </p>
</td>
</tr>
<tr id="row741100977084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1685147980084823"><a name="p1685147980084823"></a><a name="p1685147980084823"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p353142900084823"><a name="p353142900084823"></a><a name="p353142900084823"></a>Failed to release the space allocated with the message queue. </p>
</td>
</tr>
<tr id="row1533456313084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p940830119084823"><a name="p940830119084823"></a><a name="p940830119084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121834912084823"><a name="p1121834912084823"></a><a name="p1121834912084823"></a><strong id="b1694786697084823"><a name="b1694786697084823"></a><a name="b1694786697084823"></a>mqdes</strong> is invalid when the message queue is deleted in the function. </p>
</td>
</tr>
</tbody>
</table>

## mq\_getattr\(\)<a name="ga8fafe8b1183830322f8ff875f4e6cb4c"></a>

```
int mq_getattr (mqd_t mqdes, struct [mq_attr](mq_attr.md) * attr )
```

 **Description:**

Obtains the attributes of the message queue specified by the descriptor. The values of  **mq\_maxmsg**,  **mq\_msgsize**, and  **mq\_curmsgs**  are fixed. 

**Parameters:**

<a name="table1336748242084823"></a>
<table><thead align="left"><tr id="row212099513084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p329533760084823"><a name="p329533760084823"></a><a name="p329533760084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1317633594084823"><a name="p1317633594084823"></a><a name="p1317633594084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1620666141084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue descriptor. </td>
</tr>
<tr id="row582168181084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained message queue attributes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table559641874084823"></a>
<table><thead align="left"><tr id="row486023050084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1197368558084823"><a name="p1197368558084823"></a><a name="p1197368558084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2122119590084823"><a name="p2122119590084823"></a><a name="p2122119590084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1421197996084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196527990084823"><a name="p196527990084823"></a><a name="p196527990084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p933310906084823"><a name="p933310906084823"></a><a name="p933310906084823"></a><strong id="b168938831084823"><a name="b168938831084823"></a><a name="b168938831084823"></a>mqdes</strong> is invalid. </p>
</td>
</tr>
<tr id="row512628116084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2074358075084823"><a name="p2074358075084823"></a><a name="p2074358075084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207203544084823"><a name="p1207203544084823"></a><a name="p1207203544084823"></a><strong id="b495168244084823"><a name="b495168244084823"></a><a name="b495168244084823"></a>attr</strong> is <strong id="b1944558500084823"><a name="b1944558500084823"></a><a name="b1944558500084823"></a>NULL</strong>. </p>
</td>
</tr>
</tbody>
</table>

## mq\_open\(\)<a name="gaf5d8bf423701bd1783849119511381a5"></a>

```
mqd_t mq_open (const char * name, int oflag,  ... )
```

 **Description:**

Creates a message queue or opens an existing message queue. 

**Parameters:**

<a name="table1629680178084823"></a>
<table><thead align="left"><tr id="row1288088554084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2114782011084823"><a name="p2114782011084823"></a><a name="p2114782011084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p227144536084823"><a name="p227144536084823"></a><a name="p227144536084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1634459363084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the message queue to be created or opened. The maximum value is 259 bytes. </td>
</tr>
<tr id="row507118424084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oflag</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the open flag, including <a href="fs.md#ga7a68c9ffaac7dbcd652225dd7c06a54b">O_RDONLY</a>, <a href="fs.md#ga11b644a8526139c4cc1850dac1271ced">O_WRONLY</a>, <a href="fs.md#gabb0586253488ee61072b73557eeb873b">O_RDWR</a>, <strong id="b685877141084823"><a name="b685877141084823"></a><a name="b685877141084823"></a>O_CREAT</strong>, <strong id="b870750687084823"><a name="b870750687084823"></a><a name="b870750687084823"></a>O_EXCL</strong>, and <strong id="b1086762361084823"><a name="b1086762361084823"></a><a name="b1086762361084823"></a>O_NONBLOCK</strong>. </td>
</tr>
<tr id="row711422623084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used for permission control (not supported currently). Its type is <strong id="b327213261084823"><a name="b327213261084823"></a><a name="b327213261084823"></a>mode_t</strong>. This is parameter is required only during the creation of a message queue. </td>
</tr>
<tr id="row131684513084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the queue attributes to be set. Its type is <strong id="b726356908084823"><a name="b726356908084823"></a><a name="b726356908084823"></a>struct <a href="mq_attr.md">mq_attr</a></strong>. This parameter is optional and is used only during the creation of a message queue. </td>
</tr>
</tbody>
</table>

**Attention:**

The message consists of 64 bytes by default, and the maximum length of the message is 64 KB. A maximum of 1024 message queues can be created. The mq\_curmsgs field in  [mq\_attr](mq_attr.md)  is not supported. 

**Returns:**

Returns a message queue descriptor if the creation or opening is successful; returns  **\(mqd\_t\)-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1099679014084823"></a>
<table><thead align="left"><tr id="row1236915869084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1488864180084823"><a name="p1488864180084823"></a><a name="p1488864180084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p443122403084823"><a name="p443122403084823"></a><a name="p443122403084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1725341370084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111646454084823"><a name="p111646454084823"></a><a name="p111646454084823"></a>EEXIST </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140893702084823"><a name="p140893702084823"></a><a name="p140893702084823"></a>Both <strong id="b1640873881084823"><a name="b1640873881084823"></a><a name="b1640873881084823"></a>O_CREAT</strong> and <strong id="b15627750084823"><a name="b15627750084823"></a><a name="b15627750084823"></a>O_EXCL</strong> are specified in <strong id="b828968693084823"><a name="b828968693084823"></a><a name="b828968693084823"></a>oflag</strong>, and a queue with this name already exists. </p>
</td>
</tr>
<tr id="row389453112084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1962135272084823"><a name="p1962135272084823"></a><a name="p1962135272084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1230827564084823"><a name="p1230827564084823"></a><a name="p1230827564084823"></a><strong id="b590537569084823"><a name="b590537569084823"></a><a name="b590537569084823"></a>O_CREAT</strong> is specified in <strong id="b1214664742084823"><a name="b1214664742084823"></a><a name="b1214664742084823"></a>oflag</strong>, and <strong id="b1751576217084823"><a name="b1751576217084823"></a><a name="b1751576217084823"></a>attr</strong> is invalid. To be specific, the attribute value of the <strong id="b771214506084823"><a name="b771214506084823"></a><a name="b771214506084823"></a>mq_maxmsg</strong> field is less than 0 or greater than <a href="utils.md#ga689b119da994dece91d44b5aeac643ed">USHRT_MAX</a>, or the attribute value of <strong id="b416321687084823"><a name="b416321687084823"></a><a name="b416321687084823"></a>mq_msgsize</strong> is less than 0 or greater than <a href="utils.md#ga689b119da994dece91d44b5aeac643ed">USHRT_MAX</a>-4. <strong id="b1567699887084823"><a name="b1567699887084823"></a><a name="b1567699887084823"></a>name</strong> is <strong id="b577208674084823"><a name="b577208674084823"></a><a name="b577208674084823"></a>NULL</strong>, or the length of the string specified by <strong id="b658046270084823"><a name="b658046270084823"></a><a name="b658046270084823"></a>name</strong> is <strong id="b938010808084823"><a name="b938010808084823"></a><a name="b938010808084823"></a>0</strong>. </p>
</td>
</tr>
<tr id="row1841412595084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p55114380084823"><a name="p55114380084823"></a><a name="p55114380084823"></a>ENAMETOOLONG </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2110704116084823"><a name="p2110704116084823"></a><a name="p2110704116084823"></a><strong id="b957792347084823"><a name="b957792347084823"></a><a name="b957792347084823"></a>name</strong> is too long. </p>
</td>
</tr>
<tr id="row595371490084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778153083084823"><a name="p778153083084823"></a><a name="p778153083084823"></a>ENOENT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673786880084823"><a name="p1673786880084823"></a><a name="p1673786880084823"></a><strong id="b1088593015084823"><a name="b1088593015084823"></a><a name="b1088593015084823"></a>O_CREAT</strong> is not specified in <strong id="b1427572641084823"><a name="b1427572641084823"></a><a name="b1427572641084823"></a>oflag</strong>, and no queue with this name exists. </p>
</td>
</tr>
<tr id="row476210885084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639282219084823"><a name="p1639282219084823"></a><a name="p1639282219084823"></a>ENOSPC </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600576677084823"><a name="p600576677084823"></a><a name="p600576677084823"></a>Insufficient memory. </p>
</td>
</tr>
<tr id="row1819493936084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100757615084823"><a name="p2100757615084823"></a><a name="p2100757615084823"></a>ENFILE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p652670393084823"><a name="p652670393084823"></a><a name="p652670393084823"></a>The number of opened message queues exceeds the maximum. </p>
</td>
</tr>
</tbody>
</table>

## mq\_receive\(\)<a name="gafcd715bf914289ca502136ef7022eab7"></a>

```
ssize_t mq_receive (mqd_t mqdes, char * buffer, size_t size, unsigned * prioptr )
```

 **Description:**

Receives a message from a specified message queue. 

The message queue must have been open by  [mq\_open\(\)](ipc.md#gaf5d8bf423701bd1783849119511381a5). 

**Parameters:**

<a name="table1690265987084823"></a>
<table><thead align="left"><tr id="row353417274084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p510604511084823"><a name="p510604511084823"></a><a name="p510604511084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1461589620084823"><a name="p1461589620084823"></a><a name="p1461589620084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row767111646084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue descriptor. </td>
</tr>
<tr id="row1416708209084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for receiving the message. </td>
</tr>
<tr id="row698882877084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the buffer for receiving the message. </td>
</tr>
<tr id="row1302566312084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prioptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the priority of the received message if the value is not <strong id="b1973931499084823"><a name="b1973931499084823"></a><a name="b1973931499084823"></a>NULL</strong>. This parameter is not used because priority-based message processing is not supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of bytes in the received message if the message is received; returns  **\(mqd\_t\)-1**  and sets  **errno**  to a value in the following table if the message fails to be received. 

<a name="table145473445084823"></a>
<table><thead align="left"><tr id="row1338015523084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1546526467084823"><a name="p1546526467084823"></a><a name="p1546526467084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1435465157084823"><a name="p1435465157084823"></a><a name="p1435465157084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row525660476084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1703518267084823"><a name="p1703518267084823"></a><a name="p1703518267084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14080396084823"><a name="p14080396084823"></a><a name="p14080396084823"></a>Message receiving is interrupted. </p>
</td>
</tr>
<tr id="row1204211323084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p136126221084823"><a name="p136126221084823"></a><a name="p136126221084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1394978618084823"><a name="p1394978618084823"></a><a name="p1394978618084823"></a>The message queue is empty, and <strong id="b1196576877084823"><a name="b1196576877084823"></a><a name="b1196576877084823"></a>O_NONBLOCK</strong> is set for the message queue associated with <strong id="b724775971084823"><a name="b724775971084823"></a><a name="b724775971084823"></a>mqdes</strong>. </p>
</td>
</tr>
<tr id="row285687402084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662007657084823"><a name="p1662007657084823"></a><a name="p1662007657084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802083005084823"><a name="p1802083005084823"></a><a name="p1802083005084823"></a><strong id="b164642248084823"><a name="b164642248084823"></a><a name="b164642248084823"></a>mqdes</strong> is invalid or you do not have the read permission. </p>
</td>
</tr>
<tr id="row1658263053084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788760584084823"><a name="p788760584084823"></a><a name="p788760584084823"></a>EMSGSIZE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p907820932084823"><a name="p907820932084823"></a><a name="p907820932084823"></a>The size of the buffer for receiving the message is less than the message size attribute of the message queue. </p>
</td>
</tr>
<tr id="row1998659507084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620297527084823"><a name="p1620297527084823"></a><a name="p1620297527084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1776829918084823"><a name="p1776829918084823"></a><a name="p1776829918084823"></a><strong id="b398233003084823"><a name="b398233003084823"></a><a name="b398233003084823"></a>mqdes</strong> is <strong id="b1506730737084823"><a name="b1506730737084823"></a><a name="b1506730737084823"></a>NULL</strong> or the value of <strong id="b319523516084823"><a name="b319523516084823"></a><a name="b319523516084823"></a>size</strong> is <strong id="b1208588489084823"><a name="b1208588489084823"></a><a name="b1208588489084823"></a>0</strong>. </p>
</td>
</tr>
</tbody>
</table>

## mq\_send\(\)<a name="ga2d07e256d809a61bdc82178cb0dd1ba1"></a>

```
int mq_send (mqd_t mqdes, const char * buffer, size_t size, unsigned prio )
```

 **Description:**

Sends a message to a specified message queue. 

The message queue must have been opened using  [mq\_open\(\)](ipc.md#gaf5d8bf423701bd1783849119511381a5). 

**Parameters:**

<a name="table2003467764084823"></a>
<table><thead align="left"><tr id="row1292947969084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1077129759084823"><a name="p1077129759084823"></a><a name="p1077129759084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1347843165084823"><a name="p1347843165084823"></a><a name="p1347843165084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row478111071084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue descriptor. </td>
</tr>
<tr id="row90901969084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for receiving the message. </td>
</tr>
<tr id="row850103773084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the buffer for receiving the message. </td>
</tr>
<tr id="row270176634084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the priority of the message to be sent. This parameter must be <strong id="b286659477084823"><a name="b286659477084823"></a><a name="b286659477084823"></a>0</strong> because priority-based message processing is not supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the message is sent; returns  **-1**  and sets  **errno**  to a value in the following table if the message fails to be sent. 

<a name="table291362718084823"></a>
<table><thead align="left"><tr id="row1822986842084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1202831330084823"><a name="p1202831330084823"></a><a name="p1202831330084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p266355461084823"><a name="p266355461084823"></a><a name="p266355461084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2128949601084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319379718084823"><a name="p319379718084823"></a><a name="p319379718084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519137759084823"><a name="p519137759084823"></a><a name="p519137759084823"></a>Message sending is interrupted. </p>
</td>
</tr>
<tr id="row2078914890084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1331825673084823"><a name="p1331825673084823"></a><a name="p1331825673084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1805600927084823"><a name="p1805600927084823"></a><a name="p1805600927084823"></a>The message queue is full, and <strong id="b2029414405084823"><a name="b2029414405084823"></a><a name="b2029414405084823"></a>O_NONBLOCK</strong> is set for the message queue associated with <strong id="b434989872084823"><a name="b434989872084823"></a><a name="b434989872084823"></a>mqdes</strong>. </p>
</td>
</tr>
<tr id="row275605110084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p874482531084823"><a name="p874482531084823"></a><a name="p874482531084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124085973084823"><a name="p2124085973084823"></a><a name="p2124085973084823"></a><strong id="b907424502084823"><a name="b907424502084823"></a><a name="b907424502084823"></a>mqdes</strong> is invalid or you do not have the write permission. </p>
</td>
</tr>
<tr id="row1215956008084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p734075952084823"><a name="p734075952084823"></a><a name="p734075952084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p93409299084823"><a name="p93409299084823"></a><a name="p93409299084823"></a><strong id="b638774285084823"><a name="b638774285084823"></a><a name="b638774285084823"></a>mqdes</strong> is <strong id="b696694689084823"><a name="b696694689084823"></a><a name="b696694689084823"></a>NULL</strong> or the value of <strong id="b280865058084823"><a name="b280865058084823"></a><a name="b280865058084823"></a>size</strong> is <strong id="b1699191286084823"><a name="b1699191286084823"></a><a name="b1699191286084823"></a>0</strong>. </p>
</td>
</tr>
<tr id="row286301285084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p640110261084823"><a name="p640110261084823"></a><a name="p640110261084823"></a>EMSGSIZE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829558436084823"><a name="p829558436084823"></a><a name="p829558436084823"></a>The size of the message to be sent is greater than the message size attribute of the message queue. </p>
</td>
</tr>
<tr id="row146601257084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p721426016084823"><a name="p721426016084823"></a><a name="p721426016084823"></a>EOPNOTSUPP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931136934084823"><a name="p931136934084823"></a><a name="p931136934084823"></a>The operation is not supported. </p>
</td>
</tr>
<tr id="row1787924443084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291859807084823"><a name="p291859807084823"></a><a name="p291859807084823"></a>ENOSPC </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999784514084823"><a name="p1999784514084823"></a><a name="p1999784514084823"></a>Insufficient space. </p>
</td>
</tr>
</tbody>
</table>

## mq\_setattr\(\)<a name="gaf5cc07adf7823fac8611200b55fc3a27"></a>

```
int mq_setattr (mqd_t mqdes, const struct [mq_attr](mq_attr.md) *__restrict newattr, struct [mq_attr](mq_attr.md) *__restrict oldattr )
```

 **Description:**

Sets the attributes of the message queue specified by the descriptor. The  **mq\_maxmsg**,  **mq\_msgsize**, and  **mq\_curmsgs**  attributes cannot be modified.  **mq\_flags**  supports the  **O\_NONBLOCK**  attribute only. 

The message queue must have been opened using  [mq\_open\(\)](ipc.md#gaf5d8bf423701bd1783849119511381a5). 

**Parameters:**

<a name="table1811462195084823"></a>
<table><thead align="left"><tr id="row839081157084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1768295646084823"><a name="p1768295646084823"></a><a name="p1768295646084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1997441416084823"><a name="p1997441416084823"></a><a name="p1997441416084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1791970272084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue descriptor. </td>
</tr>
<tr id="row1814950486084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">newattr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the message queue attribute to be set. </td>
</tr>
<tr id="row1045197461084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oldattr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original attribute. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the setting fails. 

<a name="table678585484084823"></a>
<table><thead align="left"><tr id="row298899090084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2033530983084823"><a name="p2033530983084823"></a><a name="p2033530983084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p138279724084823"><a name="p138279724084823"></a><a name="p138279724084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1453608162084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p828258965084823"><a name="p828258965084823"></a><a name="p828258965084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p153190685084823"><a name="p153190685084823"></a><a name="p153190685084823"></a><strong id="b1240172606084823"><a name="b1240172606084823"></a><a name="b1240172606084823"></a>mqdes</strong> is invalid. </p>
</td>
</tr>
<tr id="row70282503084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p766598512084823"><a name="p766598512084823"></a><a name="p766598512084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644180050084823"><a name="p644180050084823"></a><a name="p644180050084823"></a><strong id="b18414387084823"><a name="b18414387084823"></a><a name="b18414387084823"></a>newattr</strong> is <strong id="b1941272881084823"><a name="b1941272881084823"></a><a name="b1941272881084823"></a>NULL</strong>. </p>
</td>
</tr>
</tbody>
</table>

## mq\_timedreceive\(\)<a name="gaa291cc1bc8bb02fd24bd0d4c563350f4"></a>

```
ssize_t mq_timedreceive (mqd_t mqdes, char *__restrict buffer, size_t size, unsigned *__restrict prioptr, const struct [timespec](timespec.md) *__restrict timeout )
```

 **Description:**

Receives a message from the message queue, with a timeout period specified. 

The message queue must have been open by  [mq\_open\(\)](ipc.md#gaf5d8bf423701bd1783849119511381a5). 

**Parameters:**

<a name="table1797135368084823"></a>
<table><thead align="left"><tr id="row656660191084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p197744226084823"><a name="p197744226084823"></a><a name="p197744226084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1374564960084823"><a name="p1374564960084823"></a><a name="p1374564960084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1280275030084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue descriptor. </td>
</tr>
<tr id="row1261687777084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for receiving the message. </td>
</tr>
<tr id="row614966948084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the buffer for receiving the message. </td>
</tr>
<tr id="row326323396084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prioptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the priority of the received message if the value is not <strong id="b427797665084823"><a name="b427797665084823"></a><a name="b427797665084823"></a>NULL</strong>. This parameter is not used because priority-based message processing is not supported. </td>
</tr>
<tr id="row73646305084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for returning a request. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of bytes in the message if the message is received; returns  **\(mqd\_t\)-1**  and sets  **errno**  to a value in the following table if the message fails to be received. 

<a name="table2081817400084823"></a>
<table><thead align="left"><tr id="row2071092394084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2069542378084823"><a name="p2069542378084823"></a><a name="p2069542378084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1868466029084823"><a name="p1868466029084823"></a><a name="p1868466029084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1544307391084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p718198809084823"><a name="p718198809084823"></a><a name="p718198809084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099239570084823"><a name="p1099239570084823"></a><a name="p1099239570084823"></a>Message receiving is interrupted. </p>
</td>
</tr>
<tr id="row1354811333084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007833235084823"><a name="p2007833235084823"></a><a name="p2007833235084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922219637084823"><a name="p922219637084823"></a><a name="p922219637084823"></a>The message queue is empty, and <strong id="b783847979084823"><a name="b783847979084823"></a><a name="b783847979084823"></a>O_NONBLOCK</strong> is set for the message queue associated with <strong id="b399820266084823"><a name="b399820266084823"></a><a name="b399820266084823"></a>mqdes</strong>. </p>
</td>
</tr>
<tr id="row483734309084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1768675118084823"><a name="p1768675118084823"></a><a name="p1768675118084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541162655084823"><a name="p1541162655084823"></a><a name="p1541162655084823"></a><strong id="b1824073837084823"><a name="b1824073837084823"></a><a name="b1824073837084823"></a>mqdes</strong> is invalid or you do not have the read permission. </p>
</td>
</tr>
<tr id="row720253185084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p857297303084823"><a name="p857297303084823"></a><a name="p857297303084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p60334038084823"><a name="p60334038084823"></a><a name="p60334038084823"></a><strong id="b2062869467084823"><a name="b2062869467084823"></a><a name="b2062869467084823"></a>mqdes</strong> is <strong id="b209442709084823"><a name="b209442709084823"></a><a name="b209442709084823"></a>NULL</strong> or the value of <strong id="b1273246292084823"><a name="b1273246292084823"></a><a name="b1273246292084823"></a>size</strong> is <strong id="b866028085084823"><a name="b866028085084823"></a><a name="b866028085084823"></a>0</strong>. <strong id="b2044247939084823"><a name="b2044247939084823"></a><a name="b2044247939084823"></a>timeout</strong> is invalid. Specifically, the value of <strong id="b2018994912084823"><a name="b2018994912084823"></a><a name="b2018994912084823"></a>tv_sec</strong> is less than 0, and the value of <strong id="b1806011733084823"><a name="b1806011733084823"></a><a name="b1806011733084823"></a>tv_nsec</strong> is less than 0 or greater than the ninth power of 10. </p>
</td>
</tr>
<tr id="row475231304084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157076944084823"><a name="p1157076944084823"></a><a name="p1157076944084823"></a>EMSGSIZE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1931750132084823"><a name="p1931750132084823"></a><a name="p1931750132084823"></a>The size of the buffer for receiving the message is less than the message size attribute of the message queue. </p>
</td>
</tr>
<tr id="row1656304224084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1756064918084823"><a name="p1756064918084823"></a><a name="p1756064918084823"></a>ETIMEDOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p222051415084823"><a name="p222051415084823"></a><a name="p222051415084823"></a>No message is received from the queue before the specified timeout period expires. </p>
</td>
</tr>
</tbody>
</table>

## mq\_timedsend\(\)<a name="gae59709d01cc34d009edfeae9900568cb"></a>

```
int mq_timedsend (mqd_t mqdes, const char * buffer, size_t size, unsigned prio, const struct [timespec](timespec.md) * timeout )
```

 **Description:**

Sends a message to a specified message queue, with a timeout period specified. 

The message queue must have been open by  [mq\_open\(\)](ipc.md#gaf5d8bf423701bd1783849119511381a5). 

**Parameters:**

<a name="table347683417084823"></a>
<table><thead align="left"><tr id="row1621602501084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p391937546084823"><a name="p391937546084823"></a><a name="p391937546084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p486951042084823"><a name="p486951042084823"></a><a name="p486951042084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1372099821084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mqdes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue descriptor. </td>
</tr>
<tr id="row753626359084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for sending the message. </td>
</tr>
<tr id="row928792108084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the message to be sent. </td>
</tr>
<tr id="row1258229015084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the priority of the message to be sent. This parameter must be <strong id="b1966567870084823"><a name="b1966567870084823"></a><a name="b1966567870084823"></a>0</strong> because priority-based message processing is not supported. </td>
</tr>
<tr id="row560919747084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration for returning a request. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the message is sent; returns  **-1**  and sets  **errno**  to a value in the following table if the message fails to be sent. 

<a name="table1674547017084823"></a>
<table><thead align="left"><tr id="row1466692071084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2003750643084823"><a name="p2003750643084823"></a><a name="p2003750643084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p974834907084823"><a name="p974834907084823"></a><a name="p974834907084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1389096590084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p299357314084823"><a name="p299357314084823"></a><a name="p299357314084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261523688084823"><a name="p1261523688084823"></a><a name="p1261523688084823"></a>Message sending is interrupted. </p>
</td>
</tr>
<tr id="row283854730084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p965257929084823"><a name="p965257929084823"></a><a name="p965257929084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029245581084823"><a name="p2029245581084823"></a><a name="p2029245581084823"></a>The message queue is full, and <strong id="b1920713028084823"><a name="b1920713028084823"></a><a name="b1920713028084823"></a>O_NONBLOCK</strong> is set for the message queue associated with <strong id="b1292388479084823"><a name="b1292388479084823"></a><a name="b1292388479084823"></a>mqdes</strong>. </p>
</td>
</tr>
<tr id="row150256667084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1218515278084823"><a name="p1218515278084823"></a><a name="p1218515278084823"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p894354155084823"><a name="p894354155084823"></a><a name="p894354155084823"></a><strong id="b1965395565084823"><a name="b1965395565084823"></a><a name="b1965395565084823"></a>mqdes</strong> is invalid or you do not have the write permission. </p>
</td>
</tr>
<tr id="row1350435924084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356695243084823"><a name="p1356695243084823"></a><a name="p1356695243084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1096358421084823"><a name="p1096358421084823"></a><a name="p1096358421084823"></a><strong id="b2098079531084823"><a name="b2098079531084823"></a><a name="b2098079531084823"></a>mqdes</strong> is <strong id="b857181103084823"><a name="b857181103084823"></a><a name="b857181103084823"></a>NULL</strong> or the value of <strong id="b718815391084823"><a name="b718815391084823"></a><a name="b718815391084823"></a>size</strong> is <strong id="b1173560260084823"><a name="b1173560260084823"></a><a name="b1173560260084823"></a>0</strong>. <strong id="b943906589084823"><a name="b943906589084823"></a><a name="b943906589084823"></a>timeout</strong> is invalid. Specifically, the value of <strong id="b827678475084823"><a name="b827678475084823"></a><a name="b827678475084823"></a>tv_sec</strong> is less than 0, and the value of <strong id="b1385438423084823"><a name="b1385438423084823"></a><a name="b1385438423084823"></a>tv_nsec</strong> is less than 0 or greater than the ninth power of 10. </p>
</td>
</tr>
<tr id="row211149955084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p571449053084823"><a name="p571449053084823"></a><a name="p571449053084823"></a>EMSGSIZE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p412706274084823"><a name="p412706274084823"></a><a name="p412706274084823"></a>The size of the message to be sent is greater than the message size attribute of the message queue. </p>
</td>
</tr>
<tr id="row1041882946084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612325031084823"><a name="p612325031084823"></a><a name="p612325031084823"></a>EOPNOTSUPP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1187932804084823"><a name="p1187932804084823"></a><a name="p1187932804084823"></a>The operation is not supported. </p>
</td>
</tr>
<tr id="row1507541635084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157504132084823"><a name="p1157504132084823"></a><a name="p1157504132084823"></a>ETIMEDOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1991215483084823"><a name="p1991215483084823"></a><a name="p1991215483084823"></a>No message is sent to the queue before the specified timeout period expires. </p>
</td>
</tr>
</tbody>
</table>

## mq\_unlink\(\)<a name="gaccd8c5ee36e60d990963e1d544ef4140"></a>

```
int mq_unlink (const char * name)
```

 **Description:**

Decreases the reference count of the message queue by 1, or deletes the message queue if the reference count is  **0**. 

**Parameters:**

<a name="table1162506889084823"></a>
<table><thead align="left"><tr id="row1529458357084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1703620401084823"><a name="p1703620401084823"></a><a name="p1703620401084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p43457990084823"><a name="p43457990084823"></a><a name="p43457990084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2051248854084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the message queue name. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table328295454084823"></a>
<table><thead align="left"><tr id="row1848728934084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1496901146084823"><a name="p1496901146084823"></a><a name="p1496901146084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1109111322084823"><a name="p1109111322084823"></a><a name="p1109111322084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1296488168084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1649159723084823"><a name="p1649159723084823"></a><a name="p1649159723084823"></a>ENAMETOOLONG </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684444972084823"><a name="p684444972084823"></a><a name="p684444972084823"></a><strong id="b729125736084823"><a name="b729125736084823"></a><a name="b729125736084823"></a>name</strong> is too long. </p>
</td>
</tr>
<tr id="row1965607742084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894015979084823"><a name="p894015979084823"></a><a name="p894015979084823"></a>ENOENT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508110179084823"><a name="p508110179084823"></a><a name="p508110179084823"></a>There is no message queue with the given name. </p>
</td>
</tr>
<tr id="row61482129084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p299921412084823"><a name="p299921412084823"></a><a name="p299921412084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018828184084823"><a name="p2018828184084823"></a><a name="p2018828184084823"></a>Failed to delete the message queue. </p>
</td>
</tr>
<tr id="row1523997882084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p132880570084823"><a name="p132880570084823"></a><a name="p132880570084823"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46146358084823"><a name="p46146358084823"></a><a name="p46146358084823"></a>The message queue to be deleted is being used. </p>
</td>
</tr>
<tr id="row805894683084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864561505084823"><a name="p1864561505084823"></a><a name="p1864561505084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1117032535084823"><a name="p1117032535084823"></a><a name="p1117032535084823"></a><strong id="b978705055084823"><a name="b978705055084823"></a><a name="b978705055084823"></a>name</strong> is <strong id="b1422877358084823"><a name="b1422877358084823"></a><a name="b1422877358084823"></a>NULL</strong>, or the length of the string specified by <strong id="b1567390437084823"><a name="b1567390437084823"></a><a name="b1567390437084823"></a>name</strong> is <strong id="b241519102084823"><a name="b241519102084823"></a><a name="b241519102084823"></a>0</strong>. </p>
</td>
</tr>
</tbody>
</table>

## psignal\(\)<a name="gada1fed9730b224a68e768e5f2eac53ff"></a>

```
void psignal (int signum, const char * s )
```

 **Description:**

Prints signal information. 

This function is used to print a message on the standard error output. The message consists of the character string  **s**, a colon, a space, a string describing the signal information  **signum**, and a newline character. If the string  **s**  is  **NULL**  or empty, the colon and space are omitted. If  **signum**  is invalid, the message displayed will indicate an unknown signal. 

**Parameters:**

<a name="table2052123885084823"></a>
<table><thead align="left"><tr id="row1736664161084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1124138814084823"><a name="p1124138814084823"></a><a name="p1124138814084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1362711719084823"><a name="p1362711719084823"></a><a name="p1362711719084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row253199584084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be operated. </td>
</tr>
<tr id="row484460499084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">s</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the customized string <strong id="b1781986781084823"><a name="b1781986781084823"></a><a name="b1781986781084823"></a>s</strong> to be printed. </td>
</tr>
</tbody>
</table>

## pthread\_sigmask\(\)<a name="ga8ca5be75c386a4aacd17be00721bf0f8"></a>

```
int pthread_sigmask (int how, const sigset_t *__restrict set, sigset_t *__restrict oldset )
```

 **Description:**

Checks or changes the signal mask of the calling thread. 

**Parameters:**

<a name="table1574889352084823"></a>
<table><thead align="left"><tr id="row987891003084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1285394146084823"><a name="p1285394146084823"></a><a name="p1285394146084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1126757007084823"><a name="p1126757007084823"></a><a name="p1126757007084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1100559610084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">how</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function behavior. </td>
</tr>
<tr id="row1318316791084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal set to be changed. </td>
</tr>
<tr id="row1576529071084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oldset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used for returning the original mask set of the calling thread. </td>
</tr>
</tbody>
</table>

<a name="table269806221084823"></a>
<table><thead align="left"><tr id="row611299338084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p446212971084823"><a name="p446212971084823"></a><a name="p446212971084823"></a>flags </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1853256313084823"><a name="p1853256313084823"></a><a name="p1853256313084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1477665575084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725629275084823"><a name="p1725629275084823"></a><a name="p1725629275084823"></a>SIG_BLOCK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586793653084823"><a name="p1586793653084823"></a><a name="p1586793653084823"></a>Adds the signals in <strong id="b254011621084823"><a name="b254011621084823"></a><a name="b254011621084823"></a>set</strong> to the mask set of the thread. </p>
</td>
</tr>
<tr id="row793956843084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542498267084823"><a name="p1542498267084823"></a><a name="p1542498267084823"></a>SIG_UNBLOCK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780383753084823"><a name="p780383753084823"></a><a name="p780383753084823"></a>Removes the signals in <strong id="b254892870084823"><a name="b254892870084823"></a><a name="b254892870084823"></a>set</strong> from the mask set of the thread. </p>
</td>
</tr>
<tr id="row809267101084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2092656950084823"><a name="p2092656950084823"></a><a name="p2092656950084823"></a>SIG_SETMASK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900896177084823"><a name="p1900896177084823"></a><a name="p1900896177084823"></a>Sets <strong id="b1216628399084823"><a name="b1216628399084823"></a><a name="b1216628399084823"></a>set</strong> of blocked signals as the mask set of the thread. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the change is successful; returns  **errno**  as described below if the change fails. 

<a name="table1018610861084823"></a>
<table><thead align="left"><tr id="row1794666992084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p205765833084823"><a name="p205765833084823"></a><a name="p205765833084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1338310306084823"><a name="p1338310306084823"></a><a name="p1338310306084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row64618002084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806941100084823"><a name="p806941100084823"></a><a name="p806941100084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p176504506084823"><a name="p176504506084823"></a><a name="p176504506084823"></a><strong id="b2103913431084823"><a name="b2103913431084823"></a><a name="b2103913431084823"></a>how</strong> is invalid. </p>
</td>
</tr>
<tr id="row950034517084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365045983084823"><a name="p365045983084823"></a><a name="p365045983084823"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954206851084823"><a name="p954206851084823"></a><a name="p954206851084823"></a>The <strong id="b1549951950084823"><a name="b1549951950084823"></a><a name="b1549951950084823"></a>set</strong> or <strong id="b1246922167084823"><a name="b1246922167084823"></a><a name="b1246922167084823"></a>oldset</strong> points outside the process's allocated address space. </p>
</td>
</tr>
</tbody>
</table>

## raise\(\)<a name="ga350675984ca13ce9b056e69098bda5c6"></a>

```
int raise (int signum)
```

 **Description:**

Sends a signal to the calling process. 

**Parameters:**

<a name="table651228964084823"></a>
<table><thead align="left"><tr id="row64463956084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1589666936084823"><a name="p1589666936084823"></a><a name="p1589666936084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p703806728084823"><a name="p703806728084823"></a><a name="p703806728084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row355172286084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be sent. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns 0 if the operation is successful; returns nonzero if the operation fails. 



## sem\_close\(\)<a name="ga4e398fea1080fd7919e5c72ee94e2fc5"></a>

```
int sem_close ([sem_t](sem_t.md) * sem)
```

 **Description:**

Closes a specified semaphore. 

**Parameters:**

<a name="table2131995771084823"></a>
<table><thead align="left"><tr id="row1060405972084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1035594696084823"><a name="p1035594696084823"></a><a name="p1035594696084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p321787895084823"><a name="p321787895084823"></a><a name="p321787895084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row852035692084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to close. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the semaphore is closed. errno | Description 



## sem\_destroy\(\)<a name="ga6bc9a7dd941a9b5e319715b767af5682"></a>

```
int sem_destroy ([sem_t](sem_t.md) * sem)
```

 **Description:**

Destroys a specified anonymous semaphore that is no longer used. 

**Parameters:**

<a name="table1475204873084823"></a>
<table><thead align="left"><tr id="row275519198084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1459811610084823"><a name="p1459811610084823"></a><a name="p1459811610084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p880744617084823"><a name="p880744617084823"></a><a name="p880744617084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1433010412084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the destruction is successful. 



## sem\_getvalue\(\)<a name="ga934bcc3cbc0c67a9e3a8e7a43c023460"></a>

```
int sem_getvalue ([sem_t](sem_t.md) *__restrict sem, int *__restrict sval )
```

 **Description:**

Obtains the count value of a specified semaphore. 

**Parameters:**

<a name="table233186632084823"></a>
<table><thead align="left"><tr id="row2053425527084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1648213618084823"><a name="p1648213618084823"></a><a name="p1648213618084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1557251315084823"><a name="p1557251315084823"></a><a name="p1557251315084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row365688949084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore. </td>
</tr>
<tr id="row1593435750084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained count value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. 



## sem\_init\(\)<a name="ga532509bd8a6499f8193253192fb83a3d"></a>

```
int sem_init ([sem_t](sem_t.md) * sem, int pshared, unsigned int value )
```

 **Description:**

Creates and initializes an anonymous semaphore. 

**Parameters:**

<a name="table1129657680084823"></a>
<table><thead align="left"><tr id="row1738650411084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p307908042084823"><a name="p307908042084823"></a><a name="p307908042084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1493355465084823"><a name="p1493355465084823"></a><a name="p1493355465084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1710090887084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to be created or initialized. </td>
</tr>
<tr id="row758108534084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pshared</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether the semaphore can be shared between the threads of a process. <strong id="b667648915084823"><a name="b667648915084823"></a><a name="b667648915084823"></a>0</strong> indicates that the semaphore is shared between the threads of a process. A non-zero value indicates that the semaphore can be shared between processes. </td>
</tr>
<tr id="row128208425084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the initial count value of the new semaphore. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the initialization is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the initialization fails. 

<a name="table1680455043084823"></a>
<table><thead align="left"><tr id="row783483560084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p808193168084823"><a name="p808193168084823"></a><a name="p808193168084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1318050680084823"><a name="p1318050680084823"></a><a name="p1318050680084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row798792226084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p964448070084823"><a name="p964448070084823"></a><a name="p964448070084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983611537084823"><a name="p983611537084823"></a><a name="p983611537084823"></a>The input parameters are invalid and the initial count value exceeds the limit. </p>
</td>
</tr>
</tbody>
</table>

## sem\_post\(\)<a name="ga015dce85cab8477c679cc47968958247"></a>

```
int sem_post ([sem_t](sem_t.md) * sem)
```

 **Description:**

Increments the semaphore count by 1. 

Generally, this function is used to increment the count of available shared resources when the process is to leave its critical section. This function is used together with  [sem\_wait\(\)](ipc.md#gaad70020dca2241a2b78e272ca033271b)  to protect shared resources. 

**Parameters:**

<a name="table1509379164084823"></a>
<table><thead align="left"><tr id="row1729264242084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p478196657084823"><a name="p478196657084823"></a><a name="p478196657084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p886114504084823"><a name="p886114504084823"></a><a name="p886114504084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1891044194084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to be operated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1857123225084823"></a>
<table><thead align="left"><tr id="row159095396084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1679361593084823"><a name="p1679361593084823"></a><a name="p1679361593084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1488774933084823"><a name="p1488774933084823"></a><a name="p1488774933084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1232844721084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1109108315084823"><a name="p1109108315084823"></a><a name="p1109108315084823"></a>EOVERFLOW </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p524012316084823"><a name="p524012316084823"></a><a name="p524012316084823"></a>The number of semaphores exceeds the maximum number. </p>
</td>
</tr>
</tbody>
</table>

## sem\_timedwait\(\)<a name="ga9d832817226c594e7628e2cc7ed7d723"></a>

```
int sem_timedwait ([sem_t](sem_t.md) *__restrict sem, const struct [timespec](timespec.md) *__restrict timeout )
```

 **Description:**

Obtains the semaphore, with a timeout period specified. 

If the semaphore count is greater than  **0**, the shared resources can be obtained and the semaphore count decreases by 1. After the function returns  **0**, the code execution enters the resource critical area. Otherwise, the shared resource is unavailable, the function keeps waiting, and code execution cannot enter the resource critical area. If no semaphore is obtained within the specified timeout period,  **-1**  is returned. This function is used together with  [sem\_post\(\)](ipc.md#ga015dce85cab8477c679cc47968958247)  to protect shared resources. 

**Parameters:**

<a name="table1280558188084823"></a>
<table><thead align="left"><tr id="row1948346316084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1638750975084823"><a name="p1638750975084823"></a><a name="p1638750975084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p669418418084823"><a name="p669418418084823"></a><a name="p669418418084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1405145148084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to be operated. </td>
</tr>
<tr id="row1201293289084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout period to be set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the semaphore is obtained; returns  **-1**  and sets  **errno**  to a value in the following table if the semaphore fails to be obtained. 

<a name="table189548832084823"></a>
<table><thead align="left"><tr id="row1095137471084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p214517367084823"><a name="p214517367084823"></a><a name="p214517367084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p912318103084823"><a name="p912318103084823"></a><a name="p912318103084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row169055154084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740004297084823"><a name="p740004297084823"></a><a name="p740004297084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p836840587084823"><a name="p836840587084823"></a><a name="p836840587084823"></a><strong id="b1099200167084823"><a name="b1099200167084823"></a><a name="b1099200167084823"></a>sem</strong> or <strong id="b725128231084823"><a name="b725128231084823"></a><a name="b725128231084823"></a>timeout</strong> is invalid. </p>
</td>
</tr>
<tr id="row2086354074084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p94711024084823"><a name="p94711024084823"></a><a name="p94711024084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1112009752084823"><a name="p1112009752084823"></a><a name="p1112009752084823"></a>The waiting for the semaphore is interrupted. </p>
</td>
</tr>
<tr id="row156626996084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1687768006084823"><a name="p1687768006084823"></a><a name="p1687768006084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1668188736084823"><a name="p1668188736084823"></a><a name="p1668188736084823"></a>The semaphore is set to non-blocking mode, and the semaphore count is <strong id="b489691215084823"><a name="b489691215084823"></a><a name="b489691215084823"></a>0</strong>. </p>
</td>
</tr>
<tr id="row472778435084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1750335612084823"><a name="p1750335612084823"></a><a name="p1750335612084823"></a>ETIMEDOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711593945084823"><a name="p711593945084823"></a><a name="p711593945084823"></a>Waiting for the semaphore timed out. </p>
</td>
</tr>
</tbody>
</table>

## sem\_trywait\(\)<a name="ga4de7a9a334b01b6373b017aaefa07cf0"></a>

```
int sem_trywait ([sem_t](sem_t.md) * sem)
```

 **Description:**

Attempts to obtain the semaphore. 

If the semaphore count is greater than  **0**, the shared resources can be obtained and the semaphore count decreases by 1. After the function returns  **0**, the code execution enters the resource critical area. Otherwise, the shared resource is unavailable, and the function returns  **-1**. This function is used together with  [sem\_post\(\)](ipc.md#ga015dce85cab8477c679cc47968958247)  to protect shared resources. 

**Parameters:**

<a name="table1580458503084823"></a>
<table><thead align="left"><tr id="row657616484084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1651746259084823"><a name="p1651746259084823"></a><a name="p1651746259084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p523175589084823"><a name="p523175589084823"></a><a name="p523175589084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2096677124084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to be operated. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the semaphore is obtained; returns  **-1**  and sets  **errno**  to a value in the following table if the semaphore fails to be obtained. 

<a name="table1954958399084823"></a>
<table><thead align="left"><tr id="row1608121249084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1384314594084823"><a name="p1384314594084823"></a><a name="p1384314594084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1699610300084823"><a name="p1699610300084823"></a><a name="p1699610300084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row396088972084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1423306176084823"><a name="p1423306176084823"></a><a name="p1423306176084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884657885084823"><a name="p1884657885084823"></a><a name="p1884657885084823"></a><strong id="b194367738084823"><a name="b194367738084823"></a><a name="b194367738084823"></a>sem</strong> is invalid. </p>
</td>
</tr>
<tr id="row719812254084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472416233084823"><a name="p1472416233084823"></a><a name="p1472416233084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2014388325084823"><a name="p2014388325084823"></a><a name="p2014388325084823"></a>The semaphore is set to non-blocking mode, and the semaphore count is <strong id="b1694049030084823"><a name="b1694049030084823"></a><a name="b1694049030084823"></a>0</strong>. </p>
</td>
</tr>
</tbody>
</table>

## sem\_unlink\(\)<a name="ga776256d1a473906f8b7490689bfcb75c"></a>

```
int sem_unlink (const char * name)
```

 **Description:**

Deletes a specified semaphore. 

This function is used to subtract 1 from the open count of the semaphore. If the open count is  **0**, this function deletes the semaphore. 

**Parameters:**

<a name="table338321505084823"></a>
<table><thead align="left"><tr id="row299381538084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1931881655084823"><a name="p1931881655084823"></a><a name="p1931881655084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p582210055084823"><a name="p582210055084823"></a><a name="p582210055084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row997189837084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the name of the semaphore to be deleted. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table867584772084823"></a>
<table><thead align="left"><tr id="row2098277766084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p560978662084823"><a name="p560978662084823"></a><a name="p560978662084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1657838919084823"><a name="p1657838919084823"></a><a name="p1657838919084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row44699226084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733978425084823"><a name="p1733978425084823"></a><a name="p1733978425084823"></a>ENAMETOOLONG </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p625924483084823"><a name="p625924483084823"></a><a name="p625924483084823"></a><strong id="b300511154084823"><a name="b300511154084823"></a><a name="b300511154084823"></a>name</strong> is too long. </p>
</td>
</tr>
<tr id="row1076061212084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496429615084823"><a name="p1496429615084823"></a><a name="p1496429615084823"></a>ENOENT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913988373084823"><a name="p1913988373084823"></a><a name="p1913988373084823"></a>There is no semaphore with the given name. </p>
</td>
</tr>
</tbody>
</table>

## sem\_wait\(\)<a name="gaad70020dca2241a2b78e272ca033271b"></a>

```
int sem_wait ([sem_t](sem_t.md) * sem)
```

 **Description:**

Obtains the semaphore. 

If the semaphore count is greater than  **0**, the shared resources can be obtained and the semaphore count decreases by 1. After the function returns  **0**, the code execution enters the resource critical area. Otherwise, the shared resource is unavailable, the function keeps waiting, and code execution cannot enter the resource critical area. This function is used together with  [sem\_post\(\)](ipc.md#ga015dce85cab8477c679cc47968958247)  to protect shared resources. 

**Parameters:**

<a name="table663157525084823"></a>
<table><thead align="left"><tr id="row499630479084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p949454724084823"><a name="p949454724084823"></a><a name="p949454724084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p90858537084823"><a name="p90858537084823"></a><a name="p90858537084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1630348929084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sem</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the semaphore to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the semaphore is obtained; returns  **-1**  and sets  **errno**  to a value in the following table if the semaphore fails to be obtained. 

<a name="table701592565084823"></a>
<table><thead align="left"><tr id="row363104135084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2145001361084823"><a name="p2145001361084823"></a><a name="p2145001361084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p862574995084823"><a name="p862574995084823"></a><a name="p862574995084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1682771243084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p102588180084823"><a name="p102588180084823"></a><a name="p102588180084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1942049727084823"><a name="p1942049727084823"></a><a name="p1942049727084823"></a><strong id="b524834604084823"><a name="b524834604084823"></a><a name="b524834604084823"></a>sem</strong> is invalid. </p>
</td>
</tr>
<tr id="row701018195084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1709688894084823"><a name="p1709688894084823"></a><a name="p1709688894084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1683273136084823"><a name="p1683273136084823"></a><a name="p1683273136084823"></a>The waiting for the semaphore is interrupted. </p>
</td>
</tr>
<tr id="row847800938084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564454887084823"><a name="p564454887084823"></a><a name="p564454887084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p668877569084823"><a name="p668877569084823"></a><a name="p668877569084823"></a>The semaphore is set to non-blocking mode, and the semaphore count is <strong id="b1667367092084823"><a name="b1667367092084823"></a><a name="b1667367092084823"></a>0</strong>. </p>
</td>
</tr>
</tbody>
</table>

## sigaction\(\)<a name="ga5263ce0feb3eb0934bc56ab81cae8ddb"></a>

```
int [sigaction](sigaction.md) (int signum, const struct [sigaction](sigaction.md) *__restrict act, struct [sigaction](sigaction.md) *__restrict oldact )
```

 **Description:**

Checks or changes the processing action associated with a specified signal. Do not use the process creation function or thread creation function in the registered callback processing function. Otherwise, the process is abnormal. For example, do not use the  **fork**  or  **pthread\_create**  function. 

**Parameters:**

<a name="table1545544589084823"></a>
<table><thead align="left"><tr id="row2028180258084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1022835439084823"><a name="p1022835439084823"></a><a name="p1022835439084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p923836579084823"><a name="p923836579084823"></a><a name="p923836579084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row563491843084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be operated. </td>
</tr>
<tr id="row713684203084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">act</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the new signal processing action. </td>
</tr>
<tr id="row98046733084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oldact</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the original signal processing action if the value is not <strong id="b1479404168084823"><a name="b1479404168084823"></a><a name="b1479404168084823"></a>NULL</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The  **sa\_flag**  field in  **act**  supports the  [SA\_SIGINFO](ipc.md#ga59b4c0774aace526b10b6d737075a790)  flag only. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1331308046084823"></a>
<table><thead align="left"><tr id="row821708417084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p731173791084823"><a name="p731173791084823"></a><a name="p731173791084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1815834630084823"><a name="p1815834630084823"></a><a name="p1815834630084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1736538115084823"><td class="cellrowborder" rowspan="2" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1137814631084823"><a name="p1137814631084823"></a><a name="p1137814631084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1979246227084823"><a name="p1979246227084823"></a><a name="p1979246227084823"></a><strong id="b998563551084823"><a name="b998563551084823"></a><a name="b998563551084823"></a>signum</strong> is invalid or cannot be captured. </p>
</td>
</tr>
<tr id="row209506340084823"><td class="cellrowborder" valign="top" headers="mcps1.1.3.1.1 "><p id="p997534207084823"><a name="p997534207084823"></a><a name="p997534207084823"></a><strong id="b384968997084823"><a name="b384968997084823"></a><a name="b384968997084823"></a>act</strong> is <strong id="b1677324528084823"><a name="b1677324528084823"></a><a name="b1677324528084823"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row1220775227084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716175508084823"><a name="p716175508084823"></a><a name="p716175508084823"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28104835084823"><a name="p28104835084823"></a><a name="p28104835084823"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## sigaddset\(\)<a name="gae412e6a5436a6c28424b0173251d349c"></a>

```
int sigaddset (sigset_t * set, int signum )
```

 **Description:**

Adds a signal to a specified signal set. 

**Parameters:**

<a name="table273576821084823"></a>
<table><thead align="left"><tr id="row1693785146084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p301932544084823"><a name="p301932544084823"></a><a name="p301932544084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1958741911084823"><a name="p1958741911084823"></a><a name="p1958741911084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row380765959084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to hold signals. </td>
</tr>
<tr id="row876851281084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be added. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. If  **set**  or  **signum**  is invalid, the process is abnormal. 



## sigandset\(\)<a name="ga2a0910ff9d18931a05b995143dc4576e"></a>

```
int sigandset (sigset_t * dest, const sigset_t * left, const sigset_t * right )
```

 **Description:**

Adds the intersection of  **left**  and  **right**  to  **dest**. 

**Parameters:**

<a name="table850413278084823"></a>
<table><thead align="left"><tr id="row9105596084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1766199325084823"><a name="p1766199325084823"></a><a name="p1766199325084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p825621193084823"><a name="p825621193084823"></a><a name="p825621193084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2146718630084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dest</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target signal set. </td>
</tr>
<tr id="row1960622661084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">left</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b888888712084823"><a name="b888888712084823"></a><a name="b888888712084823"></a>left</strong> set to be added. </td>
</tr>
<tr id="row823201696084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">right</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b1301834809084823"><a name="b1301834809084823"></a><a name="b1301834809084823"></a>right</strong> set to be added. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. 



## sigdelset\(\)<a name="gab0025e4f32ce2737c40cc0074cc6d7d2"></a>

```
int sigdelset (sigset_t * set, int signum )
```

 **Description:**

Delete a signal from a specified signal set. 

**Parameters:**

<a name="table1396303106084823"></a>
<table><thead align="left"><tr id="row741907083084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1167787310084823"><a name="p1167787310084823"></a><a name="p1167787310084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p291684268084823"><a name="p291684268084823"></a><a name="p291684268084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1159178708084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to hold signals. </td>
</tr>
<tr id="row1947560911084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be deleted. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. If  **set**  or  **signum**  is invalid, the process is abnormal. 



## sigemptyset\(\)<a name="ga5925352f90eb589393274fa0376d7def"></a>

```
int sigemptyset (sigset_t * set)
```

 **Description:**

Clears all signals in a specified signal set. 

**Parameters:**

<a name="table1087519818084823"></a>
<table><thead align="left"><tr id="row2092003078084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1972192692084823"><a name="p1972192692084823"></a><a name="p1972192692084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p574663967084823"><a name="p574663967084823"></a><a name="p574663967084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1049567732084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be cleared. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. If  **set**  is invalid, the process is abnormal. 



## sigfillset\(\)<a name="ga88d7bbc77ea1569ee21c90db549ea023"></a>

```
int sigfillset (sigset_t * set)
```

 **Description:**

Adds all signals to a specified signal set. 

**Parameters:**

<a name="table2108363916084823"></a>
<table><thead align="left"><tr id="row1032543420084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p468927990084823"><a name="p468927990084823"></a><a name="p468927990084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1047991394084823"><a name="p1047991394084823"></a><a name="p1047991394084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row380988068084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to hold signals. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. If  **set**  is invalid, the process is abnormal. 



## sighold\(\)<a name="ga4378a40ea3370c436d4e46c7a2a58172"></a>

```
int sighold (int signum)
```

 **Description:**

Adds the signal specified by  **signum**  to the signal mask of the calling process. 

**Parameters:**

<a name="table279382784084823"></a>
<table><thead align="left"><tr id="row524775053084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1817533075084823"><a name="p1817533075084823"></a><a name="p1817533075084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p383059153084823"><a name="p383059153084823"></a><a name="p383059153084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1305206262084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be added. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  if the operation fails. 



## sigisemptyset\(\)<a name="gac41035aa05cb4523ae93e8a6d55f9453"></a>

```
int sigisemptyset (const sigset_t * set)
```

 **Description:**

Checks whether the signal set is empty. 

**Parameters:**

<a name="table779210243084823"></a>
<table><thead align="left"><tr id="row1263815577084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1064037538084823"><a name="p1064037538084823"></a><a name="p1064037538084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1956121455084823"><a name="p1956121455084823"></a><a name="p1956121455084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1911132276084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be checked. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the set is not empty; returns  **1**  if the set is empty; returns  **-1**  if the operation fails. 



## sigismember\(\)<a name="ga63693cc65f43d772729b588b453fe1ef"></a>

```
int sigismember (const sigset_t * set, int signum )
```

 **Description:**

Checks whether a signal is in the signal set. 

**Parameters:**

<a name="table314493007084823"></a>
<table><thead align="left"><tr id="row1908303086084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1379893169084823"><a name="p1379893169084823"></a><a name="p1379893169084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p757579162084823"><a name="p757579162084823"></a><a name="p757579162084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1525333443084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be checked. </td>
</tr>
<tr id="row1974289577084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be checked. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the signal is not in the set; returns  **1**  if the signal is in the set. If  **set**  or  **signum**  is invalid, the process is abnormal. 



## signal\(\)<a name="gaf0f8ed40d30773bdb68e858ef0139b58"></a>

```
[sighandler_t](ipc.md#ga754cdc0bcfffe07baa426dc252c9101a) signal (int signum, [sighandler_t](ipc.md#ga754cdc0bcfffe07baa426dc252c9101a) handler )
```

 **Description:**

Changes the processing action of a specified signal. Do not use the process creation function or thread creation function in the registered callback processing function. Otherwise, the process is abnormal. For example, do not use the  **fork**  or  **pthread\_create**  function. 

**Parameters:**

<a name="table1779717774084823"></a>
<table><thead align="left"><tr id="row1679085084084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1642566793084823"><a name="p1642566793084823"></a><a name="p1642566793084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p48811813084823"><a name="p48811813084823"></a><a name="p48811813084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row791357000084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be operated. </td>
</tr>
<tr id="row1275864789084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handler</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the specified processing action (<a href="ipc.md#gacf0e499b0ac946b366b4f47a3b3e8b9e">SIG_IGN</a> or <a href="ipc.md#ga27d5dc561093d6243542e6a2465bc0f8">SIG_DFL</a>, or to a custom processing action. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the original processing action if the operation is successful; returns  [SIG\_ERR](ipc.md#ga3c330fbddd84bf34e65af370b11998d6)  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1512459316084823"></a>
<table><thead align="left"><tr id="row504619273084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p572895769084823"><a name="p572895769084823"></a><a name="p572895769084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p684219102084823"><a name="p684219102084823"></a><a name="p684219102084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1931920778084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p706132900084823"><a name="p706132900084823"></a><a name="p706132900084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772026860084823"><a name="p772026860084823"></a><a name="p772026860084823"></a><strong id="b835744787084823"><a name="b835744787084823"></a><a name="b835744787084823"></a>signum</strong> is invalid. </p>
</td>
</tr>
<tr id="row121338129084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2070124190084823"><a name="p2070124190084823"></a><a name="p2070124190084823"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683162722084823"><a name="p683162722084823"></a><a name="p683162722084823"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## sigorset\(\)<a name="ga1a0d037b7fd84fb392a4c2ffc6c3525c"></a>

```
int sigorset (sigset_t * dest, const sigset_t * left, const sigset_t * right )
```

 **Description:**

Adds the union set of  **left**  and  **right**  to  **dest**. 

**Parameters:**

<a name="table2069116702084823"></a>
<table><thead align="left"><tr id="row357639913084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2122702077084823"><a name="p2122702077084823"></a><a name="p2122702077084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1065136406084823"><a name="p1065136406084823"></a><a name="p1065136406084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row594279640084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dest</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target signal set. </td>
</tr>
<tr id="row1304389260084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">left</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b2015396076084823"><a name="b2015396076084823"></a><a name="b2015396076084823"></a>left</strong> set to be added. </td>
</tr>
<tr id="row1286772174084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">right</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the <strong id="b18723086084823"><a name="b18723086084823"></a><a name="b18723086084823"></a>right</strong> set to be added. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful. 



## sigpause\(\)<a name="ga95a78da8c44db11c7031b678504d0b34"></a>

```
int sigpause (int signum)
```

 **Description:**

Deletes the signal specified by  **signum**  from the signal mask of the calling process and suspends the process until the signal is received. 

**Parameters:**

<a name="table268316985084823"></a>
<table><thead align="left"><tr id="row1526872097084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p992943364084823"><a name="p992943364084823"></a><a name="p992943364084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p954608752084823"><a name="p954608752084823"></a><a name="p954608752084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2115074088084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be operated. </td>
</tr>
</tbody>
</table>

**Attention:**

After the signal is received, the original signal mask of the process is restored. 

**Returns:**

Returns  **-1**  and sets  **errno**  to a value in the following table. 

<a name="table1520419997084823"></a>
<table><thead align="left"><tr id="row1183920727084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1031103148084823"><a name="p1031103148084823"></a><a name="p1031103148084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p351210609084823"><a name="p351210609084823"></a><a name="p351210609084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row691820205084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p208557306084823"><a name="p208557306084823"></a><a name="p208557306084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892520719084823"><a name="p892520719084823"></a><a name="p892520719084823"></a>The suspension wait is interrupted by the signal. </p>
</td>
</tr>
</tbody>
</table>

## sigpending\(\)<a name="ga7b91eecad5998acd6162fde3ab530d7a"></a>

```
int sigpending (sigset_t * set)
```

 **Description:**

Obtains the signal suspended by the current thread. 

**Parameters:**

<a name="table1510527476084823"></a>
<table><thead align="left"><tr id="row1584019377084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1108390693084823"><a name="p1108390693084823"></a><a name="p1108390693084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1332926316084823"><a name="p1332926316084823"></a><a name="p1332926316084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1143264471084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set used to store the signal suspended by the current thread. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table910441096084823"></a>
<table><thead align="left"><tr id="row1875153175084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1015712635084823"><a name="p1015712635084823"></a><a name="p1015712635084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1662311919084823"><a name="p1662311919084823"></a><a name="p1662311919084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2079990806084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1603643685084823"><a name="p1603643685084823"></a><a name="p1603643685084823"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1234145994084823"><a name="p1234145994084823"></a><a name="p1234145994084823"></a><strong id="b992073311084823"><a name="b992073311084823"></a><a name="b992073311084823"></a>set</strong> points to an invalid space. </p>
</td>
</tr>
<tr id="row643804219084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p743297353084823"><a name="p743297353084823"></a><a name="p743297353084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611813695084823"><a name="p611813695084823"></a><a name="p611813695084823"></a><strong id="b1727189857084823"><a name="b1727189857084823"></a><a name="b1727189857084823"></a>set</strong> is <strong id="b263633828084823"><a name="b263633828084823"></a><a name="b263633828084823"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row528235594084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583170959084823"><a name="p583170959084823"></a><a name="p583170959084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2034408294084823"><a name="p2034408294084823"></a><a name="p2034408294084823"></a>The suspension wait is interrupted by the signal. </p>
</td>
</tr>
</tbody>
</table>

## sigprocmask\(\)<a name="gae11d1cbeb529d0050ab5600fe4b5fef9"></a>

```
int sigprocmask (int how, const sigset_t *__restrict set, sigset_t *__restrict oldset )
```

 **Description:**

Changes the signal mask of the calling thread. 

**Parameters:**

<a name="table427236820084823"></a>
<table><thead align="left"><tr id="row2046109502084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1815897923084823"><a name="p1815897923084823"></a><a name="p1815897923084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p152265058084823"><a name="p152265058084823"></a><a name="p152265058084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row910929321084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">how</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the function behavior. </td>
</tr>
<tr id="row490879276084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be changed. </td>
</tr>
<tr id="row963253555084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oldset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original mask set of the calling thread. </td>
</tr>
</tbody>
</table>

<a name="table458604909084823"></a>
<table><thead align="left"><tr id="row446389295084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p993434335084823"><a name="p993434335084823"></a><a name="p993434335084823"></a>flags </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2112930708084823"><a name="p2112930708084823"></a><a name="p2112930708084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1617154334084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p320330986084823"><a name="p320330986084823"></a><a name="p320330986084823"></a>SIG_BLOCK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1191042435084823"><a name="p1191042435084823"></a><a name="p1191042435084823"></a>Adds the signals in <strong id="b2056032294084823"><a name="b2056032294084823"></a><a name="b2056032294084823"></a>set</strong> to the mask set of the thread. </p>
</td>
</tr>
<tr id="row2097917318084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935249034084823"><a name="p1935249034084823"></a><a name="p1935249034084823"></a>SIG_UNBLOCK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106918511084823"><a name="p106918511084823"></a><a name="p106918511084823"></a>Removes the signals in <strong id="b1268187181084823"><a name="b1268187181084823"></a><a name="b1268187181084823"></a>set</strong> from the mask set of the thread. </p>
</td>
</tr>
<tr id="row249986515084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1549606372084823"><a name="p1549606372084823"></a><a name="p1549606372084823"></a>SIG_SETMASK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1376887150084823"><a name="p1376887150084823"></a><a name="p1376887150084823"></a>Sets <strong id="b1277859817084823"><a name="b1277859817084823"></a><a name="b1277859817084823"></a>set</strong> of blocked signals as the mask set of the thread. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the change is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the change fails. 

<a name="table2120699753084823"></a>
<table><thead align="left"><tr id="row1675420279084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1332958015084823"><a name="p1332958015084823"></a><a name="p1332958015084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p523539056084823"><a name="p523539056084823"></a><a name="p523539056084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row302328691084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1032209072084823"><a name="p1032209072084823"></a><a name="p1032209072084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763807648084823"><a name="p763807648084823"></a><a name="p763807648084823"></a><strong id="b580551522084823"><a name="b580551522084823"></a><a name="b580551522084823"></a>how</strong> is invalid. </p>
</td>
</tr>
<tr id="row769006033084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p598120558084823"><a name="p598120558084823"></a><a name="p598120558084823"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749898229084823"><a name="p1749898229084823"></a><a name="p1749898229084823"></a>The <strong id="b800311830084823"><a name="b800311830084823"></a><a name="b800311830084823"></a>set</strong> or <strong id="b1301478298084823"><a name="b1301478298084823"></a><a name="b1301478298084823"></a>oldset</strong> points outside the process's allocated address space. </p>
</td>
</tr>
</tbody>
</table>

## sigrelse\(\)<a name="ga96c4aed60b8b727709887e1fae0f5bea"></a>

```
int sigrelse (int signum)
```

 **Description:**

Deletes the signal specified by  **signum**  from the signal mask of the calling process. 

**Parameters:**

<a name="table1402852927084823"></a>
<table><thead align="left"><tr id="row1474138117084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1472970662084823"><a name="p1472970662084823"></a><a name="p1472970662084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1608114381084823"><a name="p1608114381084823"></a><a name="p1608114381084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1508604475084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">signum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to be deleted. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the deletion is successful; returns  **-1**  if the deletion fails. 



## sigsuspend\(\)<a name="gae5f92586ad50092a7813465eeef792c0"></a>

```
int sigsuspend (const sigset_t * mask)
```

 **Description:**

Sets  **mask**  as the signal mask set of the current process and suspends the process until a signal processing action is triggered. 

**Parameters:**

<a name="table699030743084823"></a>
<table><thead align="left"><tr id="row357294894084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p781947395084823"><a name="p781947395084823"></a><a name="p781947395084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p584097324084823"><a name="p584097324084823"></a><a name="p584097324084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1555358279084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mask</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **-1**  and sets  **errno**  to a value in the following table. 

<a name="table372205384084823"></a>
<table><thead align="left"><tr id="row790936423084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1490182757084823"><a name="p1490182757084823"></a><a name="p1490182757084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1624779058084823"><a name="p1624779058084823"></a><a name="p1624779058084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row174656238084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365234907084823"><a name="p365234907084823"></a><a name="p365234907084823"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388909132084823"><a name="p1388909132084823"></a><a name="p1388909132084823"></a><strong id="b1869043996084823"><a name="b1869043996084823"></a><a name="b1869043996084823"></a>mask</strong> points to an invalid space. </p>
</td>
</tr>
<tr id="row1437347925084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069270598084823"><a name="p1069270598084823"></a><a name="p1069270598084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493521032084823"><a name="p493521032084823"></a><a name="p493521032084823"></a>The suspension wait is interrupted by the signal. </p>
</td>
</tr>
<tr id="row1275292322084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1420861057084823"><a name="p1420861057084823"></a><a name="p1420861057084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314322366084823"><a name="p1314322366084823"></a><a name="p1314322366084823"></a><strong id="b516045923084823"><a name="b516045923084823"></a><a name="b516045923084823"></a>mask</strong> is <strong id="b961944045084823"><a name="b961944045084823"></a><a name="b961944045084823"></a>NULL</strong>. </p>
</td>
</tr>
</tbody>
</table>

## sigtimedwait\(\)<a name="ga155a526c3da5ffd1a79ba2925bdd278a"></a>

```
int sigtimedwait (const sigset_t *__restrict set, siginfo_t *__restrict info, const struct [timespec](timespec.md) *__restrict timeout )
```

 **Description:**

Suspends the calling thread and waits for the signal, with a timeout period specified. 

This function is used to suspend execution of the calling thread until one of the signals specified in the signal set becomes pending. This function specifies the timeout behavior. 

**Parameters:**

<a name="table31985725084823"></a>
<table><thead align="left"><tr id="row1478830545084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1814905362084823"><a name="p1814905362084823"></a><a name="p1814905362084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p539334628084823"><a name="p539334628084823"></a><a name="p539334628084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row30568048084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be waited. </td>
</tr>
<tr id="row138340362084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used to save the information about the waited signal if the value is not <strong id="b1584847246084823"><a name="b1584847246084823"></a><a name="b1584847246084823"></a>NULL</strong>. </td>
</tr>
<tr id="row906140679084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeout</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timeout duration. </td>
</tr>
</tbody>
</table>

**Attention:**

The signal to be waited must be in the mask set of the current thread. Once the signal is received, it is deleted from the pending list. The waiting for the signal cannot be interrupted by other signals, that is,  **EINTR**  is not supported. 

**Returns:**

Returns the value of the waited signal if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1910649432084823"></a>
<table><thead align="left"><tr id="row1843524752084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p119938371084823"><a name="p119938371084823"></a><a name="p119938371084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p529652071084823"><a name="p529652071084823"></a><a name="p529652071084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1938665098084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441120877084823"><a name="p441120877084823"></a><a name="p441120877084823"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2692247084823"><a name="p2692247084823"></a><a name="p2692247084823"></a>No signal specified by <strong id="b249173509084823"><a name="b249173509084823"></a><a name="b249173509084823"></a>set</strong> is generated within the specified timeout period. </p>
</td>
</tr>
<tr id="row113111290084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782487543084823"><a name="p1782487543084823"></a><a name="p1782487543084823"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168118622084823"><a name="p1168118622084823"></a><a name="p1168118622084823"></a><strong id="b1540348732084823"><a name="b1540348732084823"></a><a name="b1540348732084823"></a>timeout</strong> is invalid. </p>
</td>
</tr>
</tbody>
</table>

## sigwait\(\)<a name="ga900d91a9635b965dbbae6b3cee2d2a2b"></a>

```
int sigwait (const sigset_t *__restrict set, int *__restrict sig )
```

 **Description:**

Suspends the calling thread and waits for the signal. 

This function is used to suspend execution of the calling thread until one of the signals specified in the signal set becomes pending. 

**Parameters:**

<a name="table506687933084823"></a>
<table><thead align="left"><tr id="row289222069084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1546229708084823"><a name="p1546229708084823"></a><a name="p1546229708084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1992718189084823"><a name="p1992718189084823"></a><a name="p1992718189084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1480302245084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be waited. </td>
</tr>
<tr id="row1298420593084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sig</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used for saving the waited signal. </td>
</tr>
</tbody>
</table>

**Attention:**

The signal to be waited must be in the mask set of the current thread. Once the signal is received, it is deleted from the pending list. 

**Returns:**

Returns  **0**  if the signal is received; returns  **-1**  and sets  **errno**  to a value in the following table if the signal fails to be received. 

<a name="table1135390985084823"></a>
<table><thead align="left"><tr id="row1572036964084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p864406851084823"><a name="p864406851084823"></a><a name="p864406851084823"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1054897170084823"><a name="p1054897170084823"></a><a name="p1054897170084823"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row304516927084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p506625463084823"><a name="p506625463084823"></a><a name="p506625463084823"></a>EINTR </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p199918863084823"><a name="p199918863084823"></a><a name="p199918863084823"></a>The suspension wait is interrupted by the signal. </p>
</td>
</tr>
</tbody>
</table>

## sigwaitinfo\(\)<a name="ga786f18a8e5b7eceed0ddcdc722f3340b"></a>

```
int sigwaitinfo (const sigset_t *__restrict set, siginfo_t *__restrict info )
```

 **Description:**

Suspends the calling thread and waits for the signal, with a timeout period specified. 

This function is used to suspend execution of the calling thread until one of the signals specified in the signal set becomes pending. This function does not specify the timeout behavior. 

**Parameters:**

<a name="table454515972084823"></a>
<table><thead align="left"><tr id="row1609864499084823"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p692676568084823"><a name="p692676568084823"></a><a name="p692676568084823"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1208781596084823"><a name="p1208781596084823"></a><a name="p1208781596084823"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1674165232084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">set</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the signal set to be waited. </td>
</tr>
<tr id="row1323811332084823"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used to save the information about the waited signal if the value is not <strong id="b422028886084823"><a name="b422028886084823"></a><a name="b422028886084823"></a>NULL</strong>. </td>
</tr>
</tbody>
</table>

**Attention:**

The signal to be waited must be in the mask set of the current thread. Once the signal is received, it is deleted from the pending list. The waiting for the signal cannot be interrupted by other signals, that is,  **EINTR**  is not supported. 

**Returns:**

Returns the value of the waited signal if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. errno | Description ----—|-----------------------------— 



