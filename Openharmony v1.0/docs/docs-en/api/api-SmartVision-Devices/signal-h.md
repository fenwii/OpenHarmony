# signal.h<a name="EN-US_TOPIC_0000001055707982"></a>

## **Overview**<a name="section1821586111084832"></a>

**Related Modules:**

[IPC](ipc.md)

**Description:**

Provides signal operation functions and structures, including changing the signal processing mode and the process signal mask set. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section701060476084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1603751687084832"></a>
<table><thead align="left"><tr id="row1667027957084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p613360328084832"><a name="p613360328084832"></a><a name="p613360328084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p337784964084832"><a name="p337784964084832"></a><a name="p337784964084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2039526234084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p57128777084832"><a name="p57128777084832"></a><a name="p57128777084832"></a><a href="sigaltstack.md">sigaltstack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675569175084832"><a name="p675569175084832"></a><a name="p675569175084832"></a>Describes a signal stack. </p>
</td>
</tr>
<tr id="row1740279640084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090378421084832"><a name="p1090378421084832"></a><a name="p1090378421084832"></a><a href="__ucontext.md">__ucontext</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p232894362084832"><a name="p232894362084832"></a><a name="p232894362084832"></a>Describes the user execution context. </p>
</td>
</tr>
<tr id="row570643705084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047306842084832"><a name="p1047306842084832"></a><a name="p1047306842084832"></a><a href="__sigset_t.md">__sigset_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1714848312084832"><a name="p1714848312084832"></a><a name="p1714848312084832"></a>Defines a signal set. </p>
</td>
</tr>
<tr id="row1057037727084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1284221793084832"><a name="p1284221793084832"></a><a name="p1284221793084832"></a><a href="sigaction.md">sigaction</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550704503084832"><a name="p1550704503084832"></a><a name="p1550704503084832"></a>Defines the signal processing actions and related attributes. You can use the structures to change the processing actions or attributes. </p>
</td>
</tr>
<tr id="row998312453084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p562683813084832"><a name="p562683813084832"></a><a name="p562683813084832"></a><a href="sigaltstack.md">sigaltstack</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p680716061084832"><a name="p680716061084832"></a><a name="p680716061084832"></a>Describes a signal stack. </p>
</td>
</tr>
<tr id="row205724509084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1060523873084832"><a name="p1060523873084832"></a><a name="p1060523873084832"></a><a href="sigval.md">sigval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1677384502084832"><a name="p1677384502084832"></a><a name="p1677384502084832"></a>Describes signal values in different cases. </p>
</td>
</tr>
<tr id="row481868996084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298474406084832"><a name="p298474406084832"></a><a name="p298474406084832"></a><a href="__si_fields.md">__si_fields</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p593008945084832"><a name="p593008945084832"></a><a name="p593008945084832"></a>Describes signal information. </p>
</td>
</tr>
<tr id="row1146573707084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618991919084832"><a name="p618991919084832"></a><a name="p618991919084832"></a><a href="sigaction.md">sigaction</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1924641963084832"><a name="p1924641963084832"></a><a name="p1924641963084832"></a>Defines the signal processing actions and related attributes. You can use the structures to change the processing actions or attributes. </p>
</td>
</tr>
<tr id="row579436358084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p774977884084832"><a name="p774977884084832"></a><a name="p774977884084832"></a><a href="sigevent.md">sigevent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699140791084832"><a name="p1699140791084832"></a><a name="p1699140791084832"></a>Describes asynchronous notifications. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table902714761084832"></a>
<table><thead align="left"><tr id="row1080601522084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1757172685084832"><a name="p1757172685084832"></a><a name="p1757172685084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p174915179084832"><a name="p174915179084832"></a><a name="p174915179084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row93195636084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1328098737084832"><a name="p1328098737084832"></a><a name="p1328098737084832"></a><a href="ipc.md#gaf6a71c97263725437f59ceb16241fd32">SA_NOCLDSTOP</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58858609084832"><a name="p58858609084832"></a><a name="p58858609084832"></a>Stops a child process without sending the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> signal. </p>
</td>
</tr>
<tr id="row182973566084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1166216600084832"><a name="p1166216600084832"></a><a name="p1166216600084832"></a><a href="ipc.md#gae4c1aad864ef72e4a2cce74b1b8a5a0b">SA_NOCLDWAIT</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090094218084832"><a name="p1090094218084832"></a><a name="p1090094218084832"></a>Sets the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> flag to prevent zombie processes. </p>
</td>
</tr>
<tr id="row992996320084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p139699270084832"><a name="p139699270084832"></a><a name="p139699270084832"></a><a href="ipc.md#ga59b4c0774aace526b10b6d737075a790">SA_SIGINFO</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109603312084832"><a name="p1109603312084832"></a><a name="p1109603312084832"></a>Transfers the <strong id="b2049464963084832"><a name="b2049464963084832"></a><a name="b2049464963084832"></a>siginfo_t</strong> structure with the signal. </p>
</td>
</tr>
<tr id="row1286083149084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p153417508084832"><a name="p153417508084832"></a><a name="p153417508084832"></a><a href="ipc.md#ga322c220e296393958ab4238145a0d273">SA_ONSTACK</a>   0x08000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p60136228084832"><a name="p60136228084832"></a><a name="p60136228084832"></a>Uses the signal stack specified by <a href="sigaltstack.md">sigaltstack</a> for signal processing. </p>
</td>
</tr>
<tr id="row1559218178084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1038058813084832"><a name="p1038058813084832"></a><a name="p1038058813084832"></a><a href="ipc.md#ga74ef0a27afcf55b6cd6d35cf0fa5d427">SA_RESTART</a>   0x10000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849970166084832"><a name="p1849970166084832"></a><a name="p1849970166084832"></a>Obtains the restart signal. </p>
</td>
</tr>
<tr id="row121018920084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691611917084832"><a name="p691611917084832"></a><a name="p691611917084832"></a><a href="ipc.md#gabec4abd80d73397fc2f78f57f178565f">SA_NODEFER</a>   0x40000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p970118823084832"><a name="p970118823084832"></a><a name="p970118823084832"></a>The signals being processed are not masked during signal processing. </p>
</td>
</tr>
<tr id="row623454896084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1426171705084832"><a name="p1426171705084832"></a><a name="p1426171705084832"></a><a href="ipc.md#ga8d5fb4f35858d31035e7354c1d4048ea">SA_RESETHAND</a>   0x80000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1473011907084832"><a name="p1473011907084832"></a><a name="p1473011907084832"></a>The default processing mode is restored after the signal processing is complete. </p>
</td>
</tr>
<tr id="row2112100797084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1353888796084832"><a name="p1353888796084832"></a><a name="p1353888796084832"></a><a href="ipc.md#ga4af58063b5774f0422ddf346ff64846e">SA_RESTORER</a>   0x04000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1282928562084832"><a name="p1282928562084832"></a><a name="p1282928562084832"></a>Not intended for application use. This flag is used by C libraries to indicate that the <strong id="b128732812084832"><a name="b128732812084832"></a><a name="b128732812084832"></a>sa_restorer</strong> field contains the address of a <strong id="b872519445084832"><a name="b872519445084832"></a><a name="b872519445084832"></a>trampoline</strong>. </p>
</td>
</tr>
<tr id="row1763797354084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662464696084832"><a name="p1662464696084832"></a><a name="p1662464696084832"></a><a href="ipc.md#gaae6a742a8c5acf12caba1d148dd03f10">MINSIGSTKSZ</a>   2048</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787929814084832"><a name="p1787929814084832"></a><a name="p1787929814084832"></a>Defines the minimum size of the replaceable signal stack. </p>
</td>
</tr>
<tr id="row396314166084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1231067337084832"><a name="p1231067337084832"></a><a name="p1231067337084832"></a><a href="ipc.md#ga8a433a10420a0c51355da26cfcab2131">SIGSTKSZ</a>   8192</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165099449084832"><a name="p1165099449084832"></a><a name="p1165099449084832"></a>Defines the size of a signal stack. </p>
</td>
</tr>
<tr id="row580808927084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p812582406084832"><a name="p812582406084832"></a><a name="p812582406084832"></a><a href="ipc.md#ga275020780cb70a8b0cba8db5accc5d19">_NSIG</a>   65</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85452881084832"><a name="p85452881084832"></a><a name="p85452881084832"></a>Number of supported signals. </p>
</td>
</tr>
<tr id="row302718897084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290978611084832"><a name="p1290978611084832"></a><a name="p1290978611084832"></a><a href="ipc.md#ga15d5d2dce732343eece4e11ac487e003">_NSIG_BPW</a>   <a href="utils.md#ga0bf2a26a1f15f79f80319edbaa5cc9a5">__BITS_PER_LONG</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1656308354084832"><a name="p1656308354084832"></a><a name="p1656308354084832"></a>Number of bits occupied by a word. </p>
</td>
</tr>
<tr id="row801273358084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1667095700084832"><a name="p1667095700084832"></a><a name="p1667095700084832"></a><a href="ipc.md#gacd9297a3ab78048b3f46055fc7739c17">_NSIG_WORDS</a>   (<a href="ipc.md#ga275020780cb70a8b0cba8db5accc5d19">_NSIG</a> / <a href="ipc.md#ga15d5d2dce732343eece4e11ac487e003">_NSIG_BPW</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p540727840084832"><a name="p540727840084832"></a><a name="p540727840084832"></a>Number of words required by all signals. </p>
</td>
</tr>
<tr id="row1031969918084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1058825813084832"><a name="p1058825813084832"></a><a name="p1058825813084832"></a><a href="ipc.md#ga136c64ec2d1306de745e39d6aee362ca">SIGHUP</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157158668084832"><a name="p157158668084832"></a><a name="p157158668084832"></a>Hangs up a process. </p>
</td>
</tr>
<tr id="row2082103305084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1524267880084832"><a name="p1524267880084832"></a><a name="p1524267880084832"></a><a href="ipc.md#ga487309e3e9e0527535644115204a639a">SIGINT</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101620921084832"><a name="p1101620921084832"></a><a name="p1101620921084832"></a>Interrupts a process from keyboard. </p>
</td>
</tr>
<tr id="row689582006084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1885279445084832"><a name="p1885279445084832"></a><a name="p1885279445084832"></a><a href="ipc.md#ga62045b465be11891160d53c10861b16c">SIGQUIT</a>   3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224096272084832"><a name="p224096272084832"></a><a name="p224096272084832"></a>Exits a process from keyboard. A core file is generated. </p>
</td>
</tr>
<tr id="row222669849084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1676044543084832"><a name="p1676044543084832"></a><a name="p1676044543084832"></a><a href="ipc.md#ga4c9c5284f8c8d146bd7a93d25017fc62">SIGILL</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91348852084832"><a name="p91348852084832"></a><a name="p91348852084832"></a>Illegal instruction. </p>
</td>
</tr>
<tr id="row651145209084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1223146038084832"><a name="p1223146038084832"></a><a name="p1223146038084832"></a><a href="ipc.md#gaa2beb906ab1b46676e63823f4e773c38">SIGTRAP</a>   5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746663048084832"><a name="p746663048084832"></a><a name="p746663048084832"></a>Breakpoint, used for debugging. </p>
</td>
</tr>
<tr id="row889874665084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1799191067084832"><a name="p1799191067084832"></a><a name="p1799191067084832"></a><a href="ipc.md#gaa86c630133e5b5174ac970227b273446">SIGABRT</a>   6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1594459729084832"><a name="p1594459729084832"></a><a name="p1594459729084832"></a>Abnormal termination. </p>
</td>
</tr>
<tr id="row274267787084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1147486882084832"><a name="p1147486882084832"></a><a name="p1147486882084832"></a><a href="ipc.md#gab12271d5e5911f8a85dc7c3f0e2364c7">SIGIOT</a>   6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1735870317084832"><a name="p1735870317084832"></a><a name="p1735870317084832"></a>Equivalent to <a href="ipc.md#gaa86c630133e5b5174ac970227b273446">SIGABRT</a>. </p>
</td>
</tr>
<tr id="row1199268762084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723247431084832"><a name="p723247431084832"></a><a name="p723247431084832"></a><a href="ipc.md#gaead3d488474201acf18c4b63d91edc3c">SIGBUS</a>   7</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030156732084832"><a name="p1030156732084832"></a><a name="p1030156732084832"></a>Invalid address access. </p>
</td>
</tr>
<tr id="row1136197749084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26228975084832"><a name="p26228975084832"></a><a name="p26228975084832"></a><a href="ipc.md#ga7fbba29aec3e4a8daae12935299df92d">SIGFPE</a>   8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849003957084832"><a name="p1849003957084832"></a><a name="p1849003957084832"></a>Floating-point exceptions. </p>
</td>
</tr>
<tr id="row31099301084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1298475282084832"><a name="p1298475282084832"></a><a name="p1298475282084832"></a><a href="ipc.md#gaddd8dcd406ce514ab3b4f576a5343d42">SIGKILL</a>   9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140472178084832"><a name="p2140472178084832"></a><a name="p2140472178084832"></a>Forcibly stops a process. </p>
</td>
</tr>
<tr id="row100041848084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1216790159084832"><a name="p1216790159084832"></a><a name="p1216790159084832"></a><a href="ipc.md#ga944a8250e34bfd7991123abd3436d8c0">SIGUSR1</a>   10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p347240357084832"><a name="p347240357084832"></a><a name="p347240357084832"></a>User-defined signal 1. </p>
</td>
</tr>
<tr id="row941090538084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p555429557084832"><a name="p555429557084832"></a><a name="p555429557084832"></a><a href="ipc.md#gae20b4f7171a09516ea73c9d2745bd596">SIGSEGV</a>   11</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144458762084832"><a name="p2144458762084832"></a><a name="p2144458762084832"></a>Illegal memory access. </p>
</td>
</tr>
<tr id="row284161226084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1137716237084832"><a name="p1137716237084832"></a><a name="p1137716237084832"></a><a href="ipc.md#gabaaa61abe503c43481e35e21b0b5a031">SIGUSR2</a>   12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1915606767084832"><a name="p1915606767084832"></a><a name="p1915606767084832"></a>User-defined signal 2. </p>
</td>
</tr>
<tr id="row260120983084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21933963084832"><a name="p21933963084832"></a><a name="p21933963084832"></a><a href="ipc.md#ga57e9c8c5fa13bf86bc779a9f6f408b7c">SIGPIPE</a>   13</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89603322084832"><a name="p89603322084832"></a><a name="p89603322084832"></a>The pipe is broken. </p>
</td>
</tr>
<tr id="row1210500484084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p944986124084832"><a name="p944986124084832"></a><a name="p944986124084832"></a><a href="ipc.md#gaa6946723c6b7a86ec3c33caaf832840b">SIGALRM</a>   14</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615247187084832"><a name="p1615247187084832"></a><a name="p1615247187084832"></a>Timer signal. </p>
</td>
</tr>
<tr id="row593450642084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p405804240084832"><a name="p405804240084832"></a><a name="p405804240084832"></a><a href="ipc.md#ga682182a5e5f38fd61f4311501e9dac5d">SIGTERM</a>   15</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847940157084832"><a name="p1847940157084832"></a><a name="p1847940157084832"></a>Termination signal. </p>
</td>
</tr>
<tr id="row997780482084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1623045816084832"><a name="p1623045816084832"></a><a name="p1623045816084832"></a><a href="ipc.md#ga03612fcda4ab9671dfa7051e7b666fb6">SIGSTKFLT</a>   16</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1066045689084832"><a name="p1066045689084832"></a><a name="p1066045689084832"></a>Coprocessor stack error. </p>
</td>
</tr>
<tr id="row2001578486084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p742295436084832"><a name="p742295436084832"></a><a name="p742295436084832"></a><a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a>   17</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1680993712084832"><a name="p1680993712084832"></a><a name="p1680993712084832"></a>Child process terminated or stopped. </p>
</td>
</tr>
<tr id="row451105132084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1704342982084832"><a name="p1704342982084832"></a><a name="p1704342982084832"></a><a href="ipc.md#ga024f43063003e753afc6cca1acd6e104">SIGCONT</a>   18</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114307872084832"><a name="p2114307872084832"></a><a name="p2114307872084832"></a>Resumes a suspended process. </p>
</td>
</tr>
<tr id="row861055528084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2002103970084832"><a name="p2002103970084832"></a><a name="p2002103970084832"></a><a href="ipc.md#ga069e358bc9a864b7dc4fed2440eda14c">SIGSTOP</a>   19</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507943805084832"><a name="p1507943805084832"></a><a name="p1507943805084832"></a>Suspends a process. </p>
</td>
</tr>
<tr id="row2074438171084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1914339519084832"><a name="p1914339519084832"></a><a name="p1914339519084832"></a><a href="ipc.md#gabe65c086e01f0d286b7a785a7e3cdd1a">SIGTSTP</a>   20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1759636084832"><a name="p1759636084832"></a><a name="p1759636084832"></a>Stops a process by entering the command on the terminal. </p>
</td>
</tr>
<tr id="row1195142908084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p87332626084832"><a name="p87332626084832"></a><a name="p87332626084832"></a><a href="ipc.md#ga2c146e34a6b5a78dfba41cded3331181">SIGTTIN</a>   21</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p455518988084832"><a name="p455518988084832"></a><a name="p455518988084832"></a>Input required by the background process. </p>
</td>
</tr>
<tr id="row2143019649084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p373102460084832"><a name="p373102460084832"></a><a name="p373102460084832"></a><a href="ipc.md#ga782864287613e2c5c030411fa9c5e9b1">SIGTTOU</a>   22</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720003607084832"><a name="p720003607084832"></a><a name="p720003607084832"></a>Output required by the background process. </p>
</td>
</tr>
<tr id="row1437904186084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671578095084832"><a name="p671578095084832"></a><a name="p671578095084832"></a><a href="ipc.md#gad9ff13149e36144a4ea28788948c34dd">SIGURG</a>   23</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926181244084832"><a name="p926181244084832"></a><a name="p926181244084832"></a>Urgent socket condition. </p>
</td>
</tr>
<tr id="row1034985786084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1012785546084832"><a name="p1012785546084832"></a><a name="p1012785546084832"></a><a href="ipc.md#ga7265cbba4972503c1c30a2e52a929874">SIGXCPU</a>   24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1934116148084832"><a name="p1934116148084832"></a><a name="p1934116148084832"></a>CPU time limit exceeded. </p>
</td>
</tr>
<tr id="row408169047084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1285338060084832"><a name="p1285338060084832"></a><a name="p1285338060084832"></a><a href="ipc.md#ga75440a7aa885a1052dfd3b4393fd9baa">SIGXFSZ</a>   25</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1316332843084832"><a name="p1316332843084832"></a><a name="p1316332843084832"></a>File size limit exceeded. </p>
</td>
</tr>
<tr id="row2057902867084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p270243432084832"><a name="p270243432084832"></a><a name="p270243432084832"></a><a href="ipc.md#ga71403d2f5240e409e213060ea3301851">SIGVTALRM</a>   26</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830911156084832"><a name="p1830911156084832"></a><a name="p1830911156084832"></a>Virtual timer, used to calculate the CPU occupation time of a process. </p>
</td>
</tr>
<tr id="row2071195650084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1532071074084832"><a name="p1532071074084832"></a><a name="p1532071074084832"></a><a href="ipc.md#gab6bd2a2ff7e58d45965ef257f96dfe65">SIGPROF</a>   27</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1397870727084832"><a name="p1397870727084832"></a><a name="p1397870727084832"></a>Calculates the CPU time occupied by a process and the system calling time. </p>
</td>
</tr>
<tr id="row1018596514084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p585372041084832"><a name="p585372041084832"></a><a name="p585372041084832"></a><a href="ipc.md#ga13ba0e7c4365813312eb4566907bce4f">SIGWINCH</a>   28</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p812696713084832"><a name="p812696713084832"></a><a name="p812696713084832"></a>Window size change. </p>
</td>
</tr>
<tr id="row2120282719084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683803886084832"><a name="p1683803886084832"></a><a name="p1683803886084832"></a><a href="ipc.md#ga929c5eace94ce2e099c6fa732450ce86">SIGIO</a>   29</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p919532298084832"><a name="p919532298084832"></a><a name="p919532298084832"></a>Input/Output. </p>
</td>
</tr>
<tr id="row1572535644084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1360588957084832"><a name="p1360588957084832"></a><a name="p1360588957084832"></a><a href="ipc.md#ga1614264a836d6a5642554775ef0134d0">SIGPOLL</a>   <a href="ipc.md#ga929c5eace94ce2e099c6fa732450ce86">SIGIO</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p855815474084832"><a name="p855815474084832"></a><a name="p855815474084832"></a>Equivalent to <a href="ipc.md#ga929c5eace94ce2e099c6fa732450ce86">SIGIO</a>. </p>
</td>
</tr>
<tr id="row766357024084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1041400453084832"><a name="p1041400453084832"></a><a name="p1041400453084832"></a><a href="ipc.md#ga633dbd7dca7d839e6af0299bd4713f0a">SIGPWR</a>   30</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2060406480084832"><a name="p2060406480084832"></a><a name="p2060406480084832"></a>Power failure. </p>
</td>
</tr>
<tr id="row843808252084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2142357933084832"><a name="p2142357933084832"></a><a name="p2142357933084832"></a><a href="ipc.md#ga8bacf9eb18fd539099c1bb4666c45d60">SIGSYS</a>   31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1142256189084832"><a name="p1142256189084832"></a><a name="p1142256189084832"></a>Non-existent system call. </p>
</td>
</tr>
<tr id="row1072760780084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p119855883084832"><a name="p119855883084832"></a><a name="p119855883084832"></a><a href="ipc.md#ga11e925ada5a97c7bbb6b88de8ed543b4">SIGUNUSED</a>   31</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303261200084832"><a name="p303261200084832"></a><a name="p303261200084832"></a>Equivalent to <a href="ipc.md#ga8bacf9eb18fd539099c1bb4666c45d60">SIGSYS</a>. </p>
</td>
</tr>
<tr id="row982362104084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024873958084832"><a name="p2024873958084832"></a><a name="p2024873958084832"></a><a href="ipc.md#gae89f9a1282bd2d1b2a2b310c12ea16a5">SIGRTMIN</a>   32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p811519799084832"><a name="p811519799084832"></a><a name="p811519799084832"></a>Start of a reliable signal. </p>
</td>
</tr>
<tr id="row1093860534084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14316919084832"><a name="p14316919084832"></a><a name="p14316919084832"></a><a href="ipc.md#ga5336d2c76af22b10373e3dd28fb3b0f0">SIGRTMAX</a>   <a href="ipc.md#ga275020780cb70a8b0cba8db5accc5d19">_NSIG</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2043502815084832"><a name="p2043502815084832"></a><a name="p2043502815084832"></a>End of a reliable signal. </p>
</td>
</tr>
<tr id="row142534002084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2104350120084832"><a name="p2104350120084832"></a><a name="p2104350120084832"></a><a href="ipc.md#gaf6a71c97263725437f59ceb16241fd32">SA_NOCLDSTOP</a>   0x00000001</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077934351084832"><a name="p2077934351084832"></a><a name="p2077934351084832"></a>Stops a child process without sending the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> signal. </p>
</td>
</tr>
<tr id="row1457929505084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2016142891084832"><a name="p2016142891084832"></a><a name="p2016142891084832"></a><a href="ipc.md#gae4c1aad864ef72e4a2cce74b1b8a5a0b">SA_NOCLDWAIT</a>   0x00000002</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226654104084832"><a name="p1226654104084832"></a><a name="p1226654104084832"></a>Sets the <a href="ipc.md#ga0e63521a64cc8bc2b91d36a87d32c9f8">SIGCHLD</a> flag to prevent zombie processes. </p>
</td>
</tr>
<tr id="row1175640883084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984292804084832"><a name="p984292804084832"></a><a name="p984292804084832"></a><a href="ipc.md#ga59b4c0774aace526b10b6d737075a790">SA_SIGINFO</a>   0x00000004</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p653722877084832"><a name="p653722877084832"></a><a name="p653722877084832"></a>Transfers the <strong id="b712912293084832"><a name="b712912293084832"></a><a name="b712912293084832"></a>siginfo_t</strong> structure with the signal. </p>
</td>
</tr>
<tr id="row1318573268084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p373698184084832"><a name="p373698184084832"></a><a name="p373698184084832"></a><a href="ipc.md#ga93598c2382d6b05a1ff33edd21a1dcd0">SA_THIRTYTWO</a>   0x02000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p479289511084832"><a name="p479289511084832"></a><a name="p479289511084832"></a>Transfers signals in a 32-bit mode even if the task runs in a 26-bit mode. </p>
</td>
</tr>
<tr id="row949796186084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645409350084832"><a name="p645409350084832"></a><a name="p645409350084832"></a><a href="ipc.md#ga4af58063b5774f0422ddf346ff64846e">SA_RESTORER</a>   0x04000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1368178552084832"><a name="p1368178552084832"></a><a name="p1368178552084832"></a>Not intended for application use. This flag is used by C libraries to indicate that the <strong id="b854545254084832"><a name="b854545254084832"></a><a name="b854545254084832"></a>sa_restorer</strong> field contains the address of a <strong id="b710597122084832"><a name="b710597122084832"></a><a name="b710597122084832"></a>trampoline</strong>. </p>
</td>
</tr>
<tr id="row1311028256084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713530754084832"><a name="p1713530754084832"></a><a name="p1713530754084832"></a><a href="ipc.md#ga322c220e296393958ab4238145a0d273">SA_ONSTACK</a>   0x08000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p853183753084832"><a name="p853183753084832"></a><a name="p853183753084832"></a>Uses the signal stack specified by <a href="sigaltstack.md">sigaltstack</a> for signal processing. </p>
</td>
</tr>
<tr id="row1437077456084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p318119827084832"><a name="p318119827084832"></a><a name="p318119827084832"></a><a href="ipc.md#ga74ef0a27afcf55b6cd6d35cf0fa5d427">SA_RESTART</a>   0x10000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1379588050084832"><a name="p1379588050084832"></a><a name="p1379588050084832"></a>Obtains the restart signal. </p>
</td>
</tr>
<tr id="row1536651214084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p407886581084832"><a name="p407886581084832"></a><a name="p407886581084832"></a><a href="ipc.md#gabec4abd80d73397fc2f78f57f178565f">SA_NODEFER</a>   0x40000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p879618743084832"><a name="p879618743084832"></a><a name="p879618743084832"></a>The signals being processed are not masked during signal processing. </p>
</td>
</tr>
<tr id="row850719981084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p294496102084832"><a name="p294496102084832"></a><a name="p294496102084832"></a><a href="ipc.md#ga8d5fb4f35858d31035e7354c1d4048ea">SA_RESETHAND</a>   0x80000000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1316729366084832"><a name="p1316729366084832"></a><a name="p1316729366084832"></a>The default processing mode is restored after the signal processing is complete. </p>
</td>
</tr>
<tr id="row1435503553084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1019121471084832"><a name="p1019121471084832"></a><a name="p1019121471084832"></a><a href="ipc.md#ga43c1d5510c7bedd95c0e4deac99e1729">SA_NOMASK</a>   <a href="ipc.md#gabec4abd80d73397fc2f78f57f178565f">SA_NODEFER</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1656431976084832"><a name="p1656431976084832"></a><a name="p1656431976084832"></a>Signals being processed are not masked during signal processing. </p>
</td>
</tr>
<tr id="row634901056084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p171766125084832"><a name="p171766125084832"></a><a name="p171766125084832"></a><a href="ipc.md#ga40c57ae45831edc27ae9ff933b11aa50">SA_ONESHOT</a>   <a href="ipc.md#ga8d5fb4f35858d31035e7354c1d4048ea">SA_RESETHAND</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p862396704084832"><a name="p862396704084832"></a><a name="p862396704084832"></a>The default processing mode is restored after the signal processing is complete. </p>
</td>
</tr>
<tr id="row1988832034084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1504191030084832"><a name="p1504191030084832"></a><a name="p1504191030084832"></a><a href="ipc.md#gaae6a742a8c5acf12caba1d148dd03f10">MINSIGSTKSZ</a>   2048</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764291296084832"><a name="p764291296084832"></a><a name="p764291296084832"></a>Defines the minimum size of the replaceable signal stack. </p>
</td>
</tr>
<tr id="row774411422084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1281187546084832"><a name="p1281187546084832"></a><a name="p1281187546084832"></a><a href="ipc.md#ga8a433a10420a0c51355da26cfcab2131">SIGSTKSZ</a>   8192</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1180629915084832"><a name="p1180629915084832"></a><a name="p1180629915084832"></a>Defines the size of a signal stack. </p>
</td>
</tr>
<tr id="row1035981262084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p342737844084832"><a name="p342737844084832"></a><a name="p342737844084832"></a><a href="ipc.md#ga927f6ae16379576d638006c7498ac5d7">SIG_BLOCK</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1960295543084832"><a name="p1960295543084832"></a><a name="p1960295543084832"></a>Defines the function behaviors such as <a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask()</a> and <a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask()</a>, which are used to add signals to the mask set. </p>
</td>
</tr>
<tr id="row1627915582084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1622294565084832"><a name="p1622294565084832"></a><a name="p1622294565084832"></a><a href="ipc.md#ga5fcd73313a63dac2cc7eb3b654215250">SIG_UNBLOCK</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p329418397084832"><a name="p329418397084832"></a><a name="p329418397084832"></a>Defines the function behaviors such as <a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask()</a> and <a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask()</a>, which are used to remove signals from the mask set. </p>
</td>
</tr>
<tr id="row1400063432084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1478100008084832"><a name="p1478100008084832"></a><a name="p1478100008084832"></a><a href="ipc.md#ga37750b78b7ae75fe02ad26e70f6cc845">SIG_SETMASK</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p584720352084832"><a name="p584720352084832"></a><a name="p584720352084832"></a>Defines the function behaviors such as <a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask()</a> and <a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask()</a>, which are used to set the mask set. </p>
</td>
</tr>
<tr id="row282486765084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1211037273084832"><a name="p1211037273084832"></a><a name="p1211037273084832"></a><a href="ipc.md#ga51d2f3aecb6f42d152e5f319e6b178b9">sa_handler</a>   _u._sa_handler</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1473630337084832"><a name="p1473630337084832"></a><a name="p1473630337084832"></a>Defines the simplified writing used to indicate the <strong id="b1787490870084832"><a name="b1787490870084832"></a><a name="b1787490870084832"></a>__sa_handler.sa_handler</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row867684844084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1013331779084832"><a name="p1013331779084832"></a><a name="p1013331779084832"></a><a href="ipc.md#ga14be6197399829e41a778070ecebd9a3">sa_sigaction</a>   _u._sa_sigaction</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1613584506084832"><a name="p1613584506084832"></a><a name="p1613584506084832"></a>Defines the simplified writing used to indicate the <strong id="b1341930075084832"><a name="b1341930075084832"></a><a name="b1341930075084832"></a>__sa_handler.sa_sigaction</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row1562211671084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1972005366084832"><a name="p1972005366084832"></a><a name="p1972005366084832"></a><a href="ipc.md#ga0fa971487344a463a7f0545c9c9ef2bf">SIG_HOLD</a>   ((void (*)(int)) 2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p407513104084832"><a name="p407513104084832"></a><a name="p407513104084832"></a>Defines the function behaviors such as <strong id="b1695853517084832"><a name="b1695853517084832"></a><a name="b1695853517084832"></a>sigset()</strong> and adds a specified signal to the process signal mask without changing the current processing mode of the signal. </p>
</td>
</tr>
<tr id="row2088671643084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1415239190084832"><a name="p1415239190084832"></a><a name="p1415239190084832"></a><a href="ipc.md#ga51d2f3aecb6f42d152e5f319e6b178b9">sa_handler</a>   __sa_handler.sa_handler</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1366654390084832"><a name="p1366654390084832"></a><a name="p1366654390084832"></a>Defines the simplified writing used to indicate the <strong id="b1266776599084832"><a name="b1266776599084832"></a><a name="b1266776599084832"></a>__sa_handler.sa_handler</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row1553674856084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271365790084832"><a name="p271365790084832"></a><a name="p271365790084832"></a><a href="ipc.md#ga14be6197399829e41a778070ecebd9a3">sa_sigaction</a>   __sa_handler.sa_sigaction</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1677105778084832"><a name="p1677105778084832"></a><a name="p1677105778084832"></a>Defines the simplified writing used to indicate the <strong id="b2062428213084832"><a name="b2062428213084832"></a><a name="b2062428213084832"></a>__sa_handler.sa_sigaction</strong> field in <a href="sigaction.md">sigaction</a>. </p>
</td>
</tr>
<tr id="row551323517084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p180491697084832"><a name="p180491697084832"></a><a name="p180491697084832"></a><a href="ipc.md#ga06d5881eeb84e6ac35f5b801c380dbb6">SIGEV_SIGNAL</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2017360136084832"><a name="p2017360136084832"></a><a name="p2017360136084832"></a>Sets the notification method in <a href="sigevent.md">sigevent</a>: signal notification. </p>
</td>
</tr>
<tr id="row1047819531084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26435545084832"><a name="p26435545084832"></a><a name="p26435545084832"></a><a href="ipc.md#gaced9a66610d9d61756999ce4f103740e">SIGEV_NONE</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1804929955084832"><a name="p1804929955084832"></a><a name="p1804929955084832"></a>Sets the notification method in <a href="sigevent.md">sigevent</a>: no notification. </p>
</td>
</tr>
<tr id="row2055250713084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1596290788084832"><a name="p1596290788084832"></a><a name="p1596290788084832"></a><a href="ipc.md#ga29ccb6a17fa90a1357b478f62af7fca0">SIGEV_THREAD</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365414823084832"><a name="p1365414823084832"></a><a name="p1365414823084832"></a>Sets the notification method in <a href="sigevent.md">sigevent</a>: thread notification. </p>
</td>
</tr>
<tr id="row1335274338084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196806196084832"><a name="p196806196084832"></a><a name="p196806196084832"></a><a href="ipc.md#gae89f9a1282bd2d1b2a2b310c12ea16a5">SIGRTMIN</a>   (__libc_current_sigrtmin())</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p826004815084832"><a name="p826004815084832"></a><a name="p826004815084832"></a>Start of a reliable signal. </p>
</td>
</tr>
<tr id="row139297259084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2097769323084832"><a name="p2097769323084832"></a><a name="p2097769323084832"></a><a href="ipc.md#ga5336d2c76af22b10373e3dd28fb3b0f0">SIGRTMAX</a>   (__libc_current_sigrtmax())</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2020703740084832"><a name="p2020703740084832"></a><a name="p2020703740084832"></a>End of a reliable signal. </p>
</td>
</tr>
<tr id="row1505877559084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1832301401084832"><a name="p1832301401084832"></a><a name="p1832301401084832"></a><a href="ipc.md#ga3c330fbddd84bf34e65af370b11998d6">SIG_ERR</a>   ((__sighandler_t)-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p939267298084832"><a name="p939267298084832"></a><a name="p939267298084832"></a>Defines the value returned when a function such as <a href="ipc.md#gaf0f8ed40d30773bdb68e858ef0139b58">signal()</a> fails. </p>
</td>
</tr>
<tr id="row1213517986084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522327982084832"><a name="p1522327982084832"></a><a name="p1522327982084832"></a><a href="ipc.md#ga27d5dc561093d6243542e6a2465bc0f8">SIG_DFL</a>   ((__sighandler_t)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225839148084832"><a name="p1225839148084832"></a><a name="p1225839148084832"></a>Defines the default signal processing mode. </p>
</td>
</tr>
<tr id="row1046266265084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2034118696084832"><a name="p2034118696084832"></a><a name="p2034118696084832"></a><a href="ipc.md#gacf0e499b0ac946b366b4f47a3b3e8b9e">SIG_IGN</a>   ((__sighandler_t)1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211165317084832"><a name="p211165317084832"></a><a name="p211165317084832"></a>Defines the signal processing mode in which the signal is ignored. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1222111342084832"></a>
<table><thead align="left"><tr id="row2035206935084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p211961589084832"><a name="p211961589084832"></a><a name="p211961589084832"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p897208551084832"><a name="p897208551084832"></a><a name="p897208551084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1870109815084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p718552061084832"><a name="p718552061084832"></a><a name="p718552061084832"></a><a href="ipc.md#ga1a2cdfb5c67c69b7aaab293b0946593b">ucontext_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p477623196084832"><a name="p477623196084832"></a><a name="p477623196084832"></a> typedef struct <a href="__ucontext.md">__ucontext</a> </p>
<p id="p401889248084832"><a name="p401889248084832"></a><a name="p401889248084832"></a>Describes the user execution context. </p>
</td>
</tr>
<tr id="row579124982084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905072505084832"><a name="p1905072505084832"></a><a name="p1905072505084832"></a><a href="ipc.md#ga395f9ff4025fe05bb535322593abde72">stack_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p718191942084832"><a name="p718191942084832"></a><a name="p718191942084832"></a>typedef struct <a href="sigaltstack.md">sigaltstack</a> </p>
<p id="p1498217875084832"><a name="p1498217875084832"></a><a name="p1498217875084832"></a>Describes a signal stack. </p>
</td>
</tr>
<tr id="row503373480084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p563311551084832"><a name="p563311551084832"></a><a name="p563311551084832"></a><a href="ipc.md#ga754cdc0bcfffe07baa426dc252c9101a">sighandler_t</a>) (int)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p953544771084832"><a name="p953544771084832"></a><a name="p953544771084832"></a> typedef void(* </p>
<p id="p1545433438084832"><a name="p1545433438084832"></a><a name="p1545433438084832"></a>Function pointer of signal handler. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2037857643084832"></a>
<table><thead align="left"><tr id="row678897599084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1583580993084832"><a name="p1583580993084832"></a><a name="p1583580993084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p480968413084832"><a name="p480968413084832"></a><a name="p480968413084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row320066158084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255747930084832"><a name="p255747930084832"></a><a name="p255747930084832"></a><a href="ipc.md#ga4539db972bcf3dd8c8b429af0dc3789d">kill</a> (pid_t pid, int sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521838327084832"><a name="p1521838327084832"></a><a name="p1521838327084832"></a>int </p>
<p id="p1431192456084832"><a name="p1431192456084832"></a><a name="p1431192456084832"></a>Sends a signal to a specified process. </p>
</td>
</tr>
<tr id="row1971457041084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995390543084832"><a name="p995390543084832"></a><a name="p995390543084832"></a><a href="ipc.md#ga5925352f90eb589393274fa0376d7def">sigemptyset</a> (sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p16366444084832"><a name="p16366444084832"></a><a name="p16366444084832"></a>int </p>
<p id="p606594628084832"><a name="p606594628084832"></a><a name="p606594628084832"></a>Clears all signals in a specified signal set. </p>
</td>
</tr>
<tr id="row576918058084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1936700149084832"><a name="p1936700149084832"></a><a name="p1936700149084832"></a><a href="ipc.md#ga88d7bbc77ea1569ee21c90db549ea023">sigfillset</a> (sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323950042084832"><a name="p323950042084832"></a><a name="p323950042084832"></a>int </p>
<p id="p2033670513084832"><a name="p2033670513084832"></a><a name="p2033670513084832"></a>Adds all signals to a specified signal set. </p>
</td>
</tr>
<tr id="row28898105084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1380742546084832"><a name="p1380742546084832"></a><a name="p1380742546084832"></a><a href="ipc.md#gae412e6a5436a6c28424b0173251d349c">sigaddset</a> (sigset_t *set, int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1981375225084832"><a name="p1981375225084832"></a><a name="p1981375225084832"></a>int </p>
<p id="p962557067084832"><a name="p962557067084832"></a><a name="p962557067084832"></a>Adds a signal to a specified signal set. </p>
</td>
</tr>
<tr id="row674955377084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40292942084832"><a name="p40292942084832"></a><a name="p40292942084832"></a><a href="ipc.md#gab0025e4f32ce2737c40cc0074cc6d7d2">sigdelset</a> (sigset_t *set, int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705015891084832"><a name="p705015891084832"></a><a name="p705015891084832"></a>int </p>
<p id="p1396532801084832"><a name="p1396532801084832"></a><a name="p1396532801084832"></a>Delete a signal from a specified signal set. </p>
</td>
</tr>
<tr id="row721015385084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451857381084832"><a name="p451857381084832"></a><a name="p451857381084832"></a><a href="ipc.md#ga63693cc65f43d772729b588b453fe1ef">sigismember</a> (const sigset_t *set, int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1282050469084832"><a name="p1282050469084832"></a><a name="p1282050469084832"></a>int </p>
<p id="p865504024084832"><a name="p865504024084832"></a><a name="p865504024084832"></a>Checks whether a signal is in the signal set. </p>
</td>
</tr>
<tr id="row448840735084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33760668084832"><a name="p33760668084832"></a><a name="p33760668084832"></a><a href="ipc.md#gae11d1cbeb529d0050ab5600fe4b5fef9">sigprocmask</a> (int how, const sigset_t *__restrict set, sigset_t *__restrict oldset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657629199084832"><a name="p1657629199084832"></a><a name="p1657629199084832"></a>int </p>
<p id="p2087146763084832"><a name="p2087146763084832"></a><a name="p2087146763084832"></a>Changes the signal mask of the calling thread. </p>
</td>
</tr>
<tr id="row1646458419084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p542786770084832"><a name="p542786770084832"></a><a name="p542786770084832"></a><a href="ipc.md#gae5f92586ad50092a7813465eeef792c0">sigsuspend</a> (const sigset_t *mask)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323008922084832"><a name="p1323008922084832"></a><a name="p1323008922084832"></a>int </p>
<p id="p2144667077084832"><a name="p2144667077084832"></a><a name="p2144667077084832"></a>Sets <strong id="b1390024532084832"><a name="b1390024532084832"></a><a name="b1390024532084832"></a>mask</strong> as the signal mask set of the current process and suspends the process until a signal processing action is triggered. </p>
</td>
</tr>
<tr id="row1933407359084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p499773805084832"><a name="p499773805084832"></a><a name="p499773805084832"></a><a href="ipc.md#ga5263ce0feb3eb0934bc56ab81cae8ddb">sigaction</a> (int signum, const struct <a href="sigaction.md">sigaction</a> *__restrict act, struct <a href="sigaction.md">sigaction</a> *__restrict oldact)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033425570084832"><a name="p2033425570084832"></a><a name="p2033425570084832"></a>int </p>
<p id="p886602707084832"><a name="p886602707084832"></a><a name="p886602707084832"></a>Checks or changes the processing action associated with a specified signal. Do not use the process creation function or thread creation function in the registered callback processing function. Otherwise, the process is abnormal. For example, do not use the <strong id="b1185814445084832"><a name="b1185814445084832"></a><a name="b1185814445084832"></a>fork</strong> or <strong id="b2096943146084832"><a name="b2096943146084832"></a><a name="b2096943146084832"></a>pthread_create</strong> function. </p>
</td>
</tr>
<tr id="row851171844084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790199582084832"><a name="p790199582084832"></a><a name="p790199582084832"></a><a href="ipc.md#ga7b91eecad5998acd6162fde3ab530d7a">sigpending</a> (sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40179190084832"><a name="p40179190084832"></a><a name="p40179190084832"></a>int </p>
<p id="p440273743084832"><a name="p440273743084832"></a><a name="p440273743084832"></a>Obtains the signal suspended by the current thread. </p>
</td>
</tr>
<tr id="row290660209084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639084310084832"><a name="p1639084310084832"></a><a name="p1639084310084832"></a><a href="ipc.md#ga900d91a9635b965dbbae6b3cee2d2a2b">sigwait</a> (const sigset_t *__restrict set, int *__restrict sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1317424309084832"><a name="p1317424309084832"></a><a name="p1317424309084832"></a>int </p>
<p id="p1450318664084832"><a name="p1450318664084832"></a><a name="p1450318664084832"></a>Suspends the calling thread and waits for the signal. </p>
</td>
</tr>
<tr id="row455070402084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284835479084832"><a name="p284835479084832"></a><a name="p284835479084832"></a><a href="ipc.md#ga786f18a8e5b7eceed0ddcdc722f3340b">sigwaitinfo</a> (const sigset_t *__restrict set, siginfo_t *__restrict info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1438170050084832"><a name="p1438170050084832"></a><a name="p1438170050084832"></a>int </p>
<p id="p1463377253084832"><a name="p1463377253084832"></a><a name="p1463377253084832"></a>Suspends the calling thread and waits for the signal, with a timeout period specified. </p>
</td>
</tr>
<tr id="row265233747084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1268953251084832"><a name="p1268953251084832"></a><a name="p1268953251084832"></a><a href="ipc.md#ga155a526c3da5ffd1a79ba2925bdd278a">sigtimedwait</a> (const sigset_t *__restrict set, siginfo_t *__restrict info, const struct <a href="timespec.md">timespec</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1940141134084832"><a name="p1940141134084832"></a><a name="p1940141134084832"></a>int </p>
<p id="p1916236090084832"><a name="p1916236090084832"></a><a name="p1916236090084832"></a>Suspends the calling thread and waits for the signal, with a timeout period specified. </p>
</td>
</tr>
<tr id="row1040604002084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p543116762084832"><a name="p543116762084832"></a><a name="p543116762084832"></a><a href="ipc.md#ga8ca5be75c386a4aacd17be00721bf0f8">pthread_sigmask</a> (int how, const sigset_t *__restrict set, sigset_t *__restrict oldset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223567154084832"><a name="p1223567154084832"></a><a name="p1223567154084832"></a>int </p>
<p id="p583830767084832"><a name="p583830767084832"></a><a name="p583830767084832"></a>Checks or changes the signal mask of the calling thread. </p>
</td>
</tr>
<tr id="row531849559084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1010228139084832"><a name="p1010228139084832"></a><a name="p1010228139084832"></a><a href="ipc.md#gada1fed9730b224a68e768e5f2eac53ff">psignal</a> (int signum, const char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1204038889084832"><a name="p1204038889084832"></a><a name="p1204038889084832"></a>void </p>
<p id="p1998153468084832"><a name="p1998153468084832"></a><a name="p1998153468084832"></a>Prints signal information. </p>
</td>
</tr>
<tr id="row1390638149084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1691641313084832"><a name="p1691641313084832"></a><a name="p1691641313084832"></a><a href="ipc.md#ga95a78da8c44db11c7031b678504d0b34">sigpause</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p688122030084832"><a name="p688122030084832"></a><a name="p688122030084832"></a>int </p>
<p id="p584985415084832"><a name="p584985415084832"></a><a name="p584985415084832"></a>Deletes the signal specified by <strong id="b425993500084832"><a name="b425993500084832"></a><a name="b425993500084832"></a>signum</strong> from the signal mask of the calling process and suspends the process until the signal is received. </p>
</td>
</tr>
<tr id="row645647992084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408885888084832"><a name="p1408885888084832"></a><a name="p1408885888084832"></a><a href="ipc.md#ga4378a40ea3370c436d4e46c7a2a58172">sighold</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27514571084832"><a name="p27514571084832"></a><a name="p27514571084832"></a>int </p>
<p id="p1678101235084832"><a name="p1678101235084832"></a><a name="p1678101235084832"></a>Adds the signal specified by <strong id="b58968812084832"><a name="b58968812084832"></a><a name="b58968812084832"></a>signum</strong> to the signal mask of the calling process. </p>
</td>
</tr>
<tr id="row1276921833084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1471941115084832"><a name="p1471941115084832"></a><a name="p1471941115084832"></a><a href="ipc.md#ga96c4aed60b8b727709887e1fae0f5bea">sigrelse</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880305446084832"><a name="p1880305446084832"></a><a name="p1880305446084832"></a>int </p>
<p id="p1828005545084832"><a name="p1828005545084832"></a><a name="p1828005545084832"></a>Deletes the signal specified by <strong id="b46983098084832"><a name="b46983098084832"></a><a name="b46983098084832"></a>signum</strong> from the signal mask of the calling process. </p>
</td>
</tr>
<tr id="row623826292084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396755025084832"><a name="p1396755025084832"></a><a name="p1396755025084832"></a><a href="ipc.md#gac41035aa05cb4523ae93e8a6d55f9453">sigisemptyset</a> (const sigset_t *set)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580231506084832"><a name="p580231506084832"></a><a name="p580231506084832"></a>int </p>
<p id="p903104562084832"><a name="p903104562084832"></a><a name="p903104562084832"></a>Checks whether the signal set is empty. </p>
</td>
</tr>
<tr id="row983485855084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p535532256084832"><a name="p535532256084832"></a><a name="p535532256084832"></a><a href="ipc.md#ga1a0d037b7fd84fb392a4c2ffc6c3525c">sigorset</a> (sigset_t *dest, const sigset_t *left, const sigset_t *right)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549001084832"><a name="p549001084832"></a><a name="p549001084832"></a>int </p>
<p id="p1023411532084832"><a name="p1023411532084832"></a><a name="p1023411532084832"></a>Adds the union set of <strong id="b1440450060084832"><a name="b1440450060084832"></a><a name="b1440450060084832"></a>left</strong> and <strong id="b1212207584084832"><a name="b1212207584084832"></a><a name="b1212207584084832"></a>right</strong> to <strong id="b1183685017084832"><a name="b1183685017084832"></a><a name="b1183685017084832"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row459038151084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571616892084832"><a name="p1571616892084832"></a><a name="p1571616892084832"></a><a href="ipc.md#ga2a0910ff9d18931a05b995143dc4576e">sigandset</a> (sigset_t *dest, const sigset_t *left, const sigset_t *right)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615296961084832"><a name="p1615296961084832"></a><a name="p1615296961084832"></a>int </p>
<p id="p375327511084832"><a name="p375327511084832"></a><a name="p375327511084832"></a>Adds the intersection of <strong id="b771359931084832"><a name="b771359931084832"></a><a name="b771359931084832"></a>left</strong> and <strong id="b2042592345084832"><a name="b2042592345084832"></a><a name="b2042592345084832"></a>right</strong> to <strong id="b659873681084832"><a name="b659873681084832"></a><a name="b659873681084832"></a>dest</strong>. </p>
</td>
</tr>
<tr id="row280659121084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836086854084832"><a name="p1836086854084832"></a><a name="p1836086854084832"></a><a href="ipc.md#gaf0f8ed40d30773bdb68e858ef0139b58">signal</a> (int signum, <a href="ipc.md#ga754cdc0bcfffe07baa426dc252c9101a">sighandler_t</a> handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1495558568084832"><a name="p1495558568084832"></a><a name="p1495558568084832"></a><a href="ipc.md#ga754cdc0bcfffe07baa426dc252c9101a">sighandler_t</a> </p>
<p id="p655344225084832"><a name="p655344225084832"></a><a name="p655344225084832"></a>Changes the processing action of a specified signal. Do not use the process creation function or thread creation function in the registered callback processing function. Otherwise, the process is abnormal. For example, do not use the <strong id="b369668499084832"><a name="b369668499084832"></a><a name="b369668499084832"></a>fork</strong> or <strong id="b998174922084832"><a name="b998174922084832"></a><a name="b998174922084832"></a>pthread_create</strong> function. </p>
</td>
</tr>
<tr id="row520191033084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911449192084832"><a name="p1911449192084832"></a><a name="p1911449192084832"></a><a href="ipc.md#ga350675984ca13ce9b056e69098bda5c6">raise</a> (int signum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p147768263084832"><a name="p147768263084832"></a><a name="p147768263084832"></a>int </p>
<p id="p1671779478084832"><a name="p1671779478084832"></a><a name="p1671779478084832"></a>Sends a signal to the calling process. </p>
</td>
</tr>
</tbody>
</table>

