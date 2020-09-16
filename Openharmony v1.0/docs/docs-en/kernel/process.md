# Process<a name="EN-US_TOPIC_0000001051612194"></a>

## Basic Concepts<a name="section29197338383"></a>

Processes are resource management units in the OS. They can use or wait to use CPUs and use system resources such as memory. They run independently from one another.

The OpenHarmony kernel allows multiple processes to run simultaneously, switch, and communicate, facilitating your management over service programs. In this regard, you will have more time to devote to the implementation of service functionalities.

Processes in the OpenHarmony kernel use the preemptive scheduling mechanism, either round-robin \(RR\) scheduling or First In First Out \(FIFO\) scheduling.

These processes are assigned 32 priorities \(**0**  to  **31**\). Among them, user processes can be configured with 22 priorities from  **10**  \(highest\) to  **31**  \(lowest\).

A high-priority process can preempt the resources of a low-priority process. The low-priority process can be scheduled only after the high-priority process is blocked or terminated.

Each user-space process has its own memory space, which is invisible to other processes. In this way, processes are isolated from each other.

The user-space root process init is started by the kernel. Then other user-space processes are created by the init process via the  **fork**  call.

**A process may have the following states:**

-   **Init**: The process is being created.

-   **Ready**: The process is in the ready list and waits for being scheduled by the CPU.

-   **Running**: The process is running.

-   **Pend**: The process is blocked and suspended. When all threads in a process are blocked, the process is blocked and suspended.

-   **Zombies**: The process stops running and waits for the parent process to reclaim its control block resources.


**Figure  1**  State transition of a process<a name="fig1877059202911"></a>  


![](figures/en-us_image_0000001053930456.png)

**Description of the process state transition:**

-   Init→Ready:

    When a process is created, the process enters the  **Init**  state to start initialization after obtaining the process control block. After the process is initialized, the process is inserted into the scheduling queue and therefore enters the  **Ready**  state.

-   Ready→Running:

    When a process switchover is triggered, the process with the highest priority in the ready list is executed and enters the  **Running**  state. If this process has no thread in the  **Ready**  state, the process is deleted from the ready list and resides only in the  **Running**  state. However, if it has threads in the  **Ready**  state, the process still stays in the ready list. In this case, the process is in both the  **Ready**  and  **Running**  states.

-   Running→Pend:

    If all threads in a process are entering the  **Pend**  state, the process will enter the  **Pend**  state together with its last thread. Then, a process switchover is triggered.

-   Pend→Ready/Pend→Running:

    When any thread in a  **Pend**  process restores to the  **Ready**  state, the process is added to the ready list and changes to the  **Ready**  state. If a process switchover occurs at this time, the process state changes from the  **Ready**  state to the  **Running**  state.

-   Ready→Pend:

    When the last ready thread in a process enters the  **Pend**  state, the process is deleted from the ready list, and the process changes from the  **Ready**  state to the  **Pend**  state.

-   Running→Ready:

    A process may change from the  **Running**  state to the  **Ready**  state in either of the following scenarios:

    1.  After a process with a higher priority is created or restored, processes will be scheduled. The process with the highest priority in the ready list will change to the  **Running**  state, and the originally running process will change from the  **Running**  state to the  **Ready**  state.
    2.  If a process has the  **SCHED\_RR**  scheduling policy and shares the same priority with another process in the  **Ready**  state, this process will change from the  **Running**  state to the  **Ready**  state after its time slices are used up, and the other process with the same priority will change from the  **Ready**  state to the  **Running**  state.

-   Running→Zombies:

    After the main thread or all threads of a process are stopped, the process changes from the  **Running**  state to the  **Zombies**  state and waits for the parent process to reclaim resources.


## When to Use<a name="section85513272398"></a>

After processes are created, you can operate the resources only in your own process space, except shared resources. In user space, processes can be suspended, restored, and delayed. In addition, you can set and obtain the scheduling priority and scheduling policy of processes. When a process is terminated, it proactively releases its resources. However, the PID resources of the process are reclaimed by the parent process via  **wait**/**waitpid**  or when the parent process exits.

## Available APIs<a name="section4517119124015"></a>

The following table describes the APIs provided by the process management module of the OpenHarmony kernel.

**Table  1**  APIs provided by the process management module

<a name="table12130144215441"></a>
<table><thead align="left"><tr id="row630210427446"><th class="cellrowborder" valign="top" width="13.020000000000001%" id="mcps1.2.5.1.1"><p id="p1430244284410"><a name="p1430244284410"></a><a name="p1430244284410"></a><strong id="b39614238211"><a name="b39614238211"></a><a name="b39614238211"></a>Category</strong></p>
</th>
<th class="cellrowborder" valign="top" width="23.150000000000002%" id="mcps1.2.5.1.2"><p id="p9302164284416"><a name="p9302164284416"></a><a name="p9302164284416"></a><strong id="b852810441211"><a name="b852810441211"></a><a name="b852810441211"></a>Function</strong></p>
</th>
<th class="cellrowborder" valign="top" width="28.93%" id="mcps1.2.5.1.3"><p id="p730211427445"><a name="p730211427445"></a><a name="p730211427445"></a><strong id="b1858304911219"><a name="b1858304911219"></a><a name="b1858304911219"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="34.9%" id="mcps1.2.5.1.4"><p id="p1430214294419"><a name="p1430214294419"></a><a name="p1430214294419"></a><strong id="b1898815613215"><a name="b1898815613215"></a><a name="b1898815613215"></a>Remarks</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row12302642134414"><td class="cellrowborder" rowspan="13" valign="top" width="13.020000000000001%" headers="mcps1.2.5.1.1 "><p id="p430213427443"><a name="p430213427443"></a><a name="p430213427443"></a>Process</p>
</td>
<td class="cellrowborder" valign="top" width="23.150000000000002%" headers="mcps1.2.5.1.2 "><p id="p10302154219449"><a name="p10302154219449"></a><a name="p10302154219449"></a>fork</p>
</td>
<td class="cellrowborder" valign="top" width="28.93%" headers="mcps1.2.5.1.3 "><p id="p930218420449"><a name="p930218420449"></a><a name="p930218420449"></a>Creates a new process.</p>
</td>
<td class="cellrowborder" valign="top" width="34.9%" headers="mcps1.2.5.1.4 "><p id="p230224211440"><a name="p230224211440"></a><a name="p230224211440"></a>N/A</p>
</td>
</tr>
<tr id="row20302154218442"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p130314204419"><a name="p130314204419"></a><a name="p130314204419"></a>exit</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p53031426443"><a name="p53031426443"></a><a name="p53031426443"></a>Exits the process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p113034423445"><a name="p113034423445"></a><a name="p113034423445"></a>N/A</p>
</td>
</tr>
<tr id="row930314421443"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p13303124213442"><a name="p13303124213442"></a><a name="p13303124213442"></a>atexit</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p1330324210442"><a name="p1330324210442"></a><a name="p1330324210442"></a>Registers the callback that will be called when the process is terminated normally.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p3303144264414"><a name="p3303144264414"></a><a name="p3303144264414"></a>N/A</p>
</td>
</tr>
<tr id="row113039426449"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1630394220444"><a name="p1630394220444"></a><a name="p1630394220444"></a>abort</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p133037421441"><a name="p133037421441"></a><a name="p133037421441"></a>Terminates the process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p1330334216449"><a name="p1330334216449"></a><a name="p1330334216449"></a>N/A</p>
</td>
</tr>
<tr id="row1330317422445"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p113036427441"><a name="p113036427441"></a><a name="p113036427441"></a>getpid</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p17303642194412"><a name="p17303642194412"></a><a name="p17303642194412"></a>Obtains the process ID.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p14304942104420"><a name="p14304942104420"></a><a name="p14304942104420"></a>N/A</p>
</td>
</tr>
<tr id="row3304204254412"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1430404218442"><a name="p1430404218442"></a><a name="p1430404218442"></a>getppid</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p9304134217443"><a name="p9304134217443"></a><a name="p9304134217443"></a>Obtains the parent process ID.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p1530418423449"><a name="p1530418423449"></a><a name="p1530418423449"></a>N/A</p>
</td>
</tr>
<tr id="row610863618327"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p110811368324"><a name="p110811368324"></a><a name="p110811368324"></a>getpgrp</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p51091436133217"><a name="p51091436133217"></a><a name="p51091436133217"></a>Obtains the ID of the process group of the calling process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p31094364326"><a name="p31094364326"></a><a name="p31094364326"></a>N/A</p>
</td>
</tr>
<tr id="row2379940183217"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1380184016329"><a name="p1380184016329"></a><a name="p1380184016329"></a>getpgid</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p8121101872215"><a name="p8121101872215"></a><a name="p8121101872215"></a>Obtains the process group ID of the process identified by <strong id="b301564102"><a name="b301564102"></a><a name="b301564102"></a>pid</strong>.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p63802401326"><a name="p63802401326"></a><a name="p63802401326"></a>N/A</p>
</td>
</tr>
<tr id="row1981395963412"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p4814559123412"><a name="p4814559123412"></a><a name="p4814559123412"></a>setpgrp</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p171226183225"><a name="p171226183225"></a><a name="p171226183225"></a>Sets the process group ID of the calling process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p8814959123416"><a name="p8814959123416"></a><a name="p8814959123416"></a>N/A</p>
</td>
</tr>
<tr id="row194862793516"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p5948162703511"><a name="p5948162703511"></a><a name="p5948162703511"></a>setpgid</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p7122131852218"><a name="p7122131852218"></a><a name="p7122131852218"></a>Sets the process group ID of the process identified by <strong id="b473312191110"><a name="b473312191110"></a><a name="b473312191110"></a>pid</strong>.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p1994915279352"><a name="p1994915279352"></a><a name="p1994915279352"></a>N/A</p>
</td>
</tr>
<tr id="row10304742114410"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p530474264418"><a name="p530474264418"></a><a name="p530474264418"></a>kill</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p2304174213441"><a name="p2304174213441"></a><a name="p2304174213441"></a>Sends a signal to a specified process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><a name="ul949915272011"></a><a name="ul949915272011"></a><ul id="ul949915272011"><li>Only signals 1 to 30 can be sent.</li><li>The default behavior for signals does not include <strong id="b8467181916425"><a name="b8467181916425"></a><a name="b8467181916425"></a>STOP</strong> and <strong id="b1056102115423"><a name="b1056102115423"></a><a name="b1056102115423"></a>CONTINUE</strong> and terminates the process without a core dump.</li><li><strong id="b1937515321030"><a name="b1937515321030"></a><a name="b1937515321030"></a>SIGSTOP</strong>, <strong id="b27003330317"><a name="b27003330317"></a><a name="b27003330317"></a>SIGKILL</strong>, and <strong id="b1319037838"><a name="b1319037838"></a><a name="b1319037838"></a>SIGCONT</strong> cannot be masked.</li><li>After an asynchronous signal is sent to a process, the signal callback is invoked only after the process is scheduled. For the sake of security, the process can be killed only by itself, and the kernel cannot forcibly kill the process by sending signals.</li><li>After the process is killed, <strong id="b74161730162317"><a name="b74161730162317"></a><a name="b74161730162317"></a>SIGCHLD</strong> is sent to its parent process. The sending action cannot be canceled.</li><li>A sleeping process cannot be woken up by a signal.</li></ul>
</td>
</tr>
<tr id="row1430454210446"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p830494212443"><a name="p830494212443"></a><a name="p830494212443"></a>wait</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p230464294410"><a name="p230464294410"></a><a name="p230464294410"></a>Waits for any child process to terminate and reclaims its resources.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p12512337347"><a name="p12512337347"></a><a name="p12512337347"></a>The <strong id="b156410326361"><a name="b156410326361"></a><a name="b156410326361"></a>status</strong> value is defined by the following macros:</p>
<a name="ul13349201524417"></a><a name="ul13349201524417"></a><ul id="ul13349201524417"><li><strong id="b06018713811"><a name="b06018713811"></a><a name="b06018713811"></a>WIFEXITED(status)</strong>: If the child process terminates normally, <strong id="b63031448163819"><a name="b63031448163819"></a><a name="b63031448163819"></a>true</strong> is returned. Otherwise, <strong id="b8505135423817"><a name="b8505135423817"></a><a name="b8505135423817"></a>false</strong> is returned.</li><li><strong id="b10515451113916"><a name="b10515451113916"></a><a name="b10515451113916"></a>WEXITSTATUS(status)</strong>: If <strong id="b194101084011"><a name="b194101084011"></a><a name="b194101084011"></a>WIFEXITED(status)</strong> is <strong id="b125682020164013"><a name="b125682020164013"></a><a name="b125682020164013"></a>true</strong>, this macro can be used to obtain the exit code that the child process passed to <strong id="b311317497406"><a name="b311317497406"></a><a name="b311317497406"></a>exit()</strong>.</li><li><strong id="b14193114020473"><a name="b14193114020473"></a><a name="b14193114020473"></a>WTERMSIG(status)</strong>: If a child process terminates abnormally, the child process exit code obtained by the parent process through <strong id="b1162241115210"><a name="b1162241115210"></a><a name="b1162241115210"></a>WTERMSIG</strong> is always <strong id="b1836285675110"><a name="b1836285675110"></a><a name="b1836285675110"></a>SIGUSR2</strong>. This is the only case supported.</li><li>The following operations are not supported: <strong id="b42912379517"><a name="b42912379517"></a><a name="b42912379517"></a>WIFSTOPPED</strong>, <strong id="b0024214511"><a name="b0024214511"></a><a name="b0024214511"></a>WSTOPSIG</strong>, <strong id="b1989011441751"><a name="b1989011441751"></a><a name="b1989011441751"></a>WCOREDUMP</strong>, and <strong id="b1421913541511"><a name="b1421913541511"></a><a name="b1421913541511"></a>WIFCONTINUED</strong>.</li></ul>
</td>
</tr>
<tr id="row13041742134416"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1530434217444"><a name="p1530434217444"></a><a name="p1530434217444"></a>waitpid</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p130564294420"><a name="p130564294420"></a><a name="p130564294420"></a>Waits for a specified child process to terminate and reclaims its resources.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p969785263816"><a name="p969785263816"></a><a name="p969785263816"></a>The options to control the function behavior do not support <strong id="b427712262449"><a name="b427712262449"></a><a name="b427712262449"></a>WUNTRACED</strong> and <strong id="b0180329164412"><a name="b0180329164412"></a><a name="b0180329164412"></a>WCONTINUED</strong>.</p>
<p id="p8497151543715"><a name="p8497151543715"></a><a name="p8497151543715"></a>The <strong id="b158163312443"><a name="b158163312443"></a><a name="b158163312443"></a>status</strong> value is defined by the following macros:</p>
<a name="ul7243133164416"></a><a name="ul7243133164416"></a><ul id="ul7243133164416"><li><strong id="b162659344488"><a name="b162659344488"></a><a name="b162659344488"></a>WIFEXITED(status)</strong>: If the child process terminates normally, <strong id="b127015347483"><a name="b127015347483"></a><a name="b127015347483"></a>true</strong> is returned. Otherwise, <strong id="b827110347483"><a name="b827110347483"></a><a name="b827110347483"></a>false</strong> is returned.</li><li><strong id="b101506426486"><a name="b101506426486"></a><a name="b101506426486"></a>WEXITSTATUS(status)</strong>: If <strong id="b1115194211488"><a name="b1115194211488"></a><a name="b1115194211488"></a>WIFEXITED(status)</strong> is <strong id="b115154214817"><a name="b115154214817"></a><a name="b115154214817"></a>true</strong>, this macro can be used to obtain the exit code that the child process passed to <strong id="b4152184212486"><a name="b4152184212486"></a><a name="b4152184212486"></a>exit()</strong>.</li><li><strong id="b1327754824815"><a name="b1327754824815"></a><a name="b1327754824815"></a>WTERMSIG(status)</strong>: If a child process terminates abnormally, the child process exit code obtained by the parent process through <strong id="b528264811483"><a name="b528264811483"></a><a name="b528264811483"></a>WTERMSIG</strong> is always <strong id="b3282104864815"><a name="b3282104864815"></a><a name="b3282104864815"></a>SIGUSR2</strong>. This is the only case supported.</li><li>The following operations are not supported: <strong id="b1033852104912"><a name="b1033852104912"></a><a name="b1033852104912"></a>WIFSTOPPED</strong>, <strong id="b3550195444911"><a name="b3550195444911"></a><a name="b3550195444911"></a>WSTOPSIG</strong>, <strong id="b563517586492"><a name="b563517586492"></a><a name="b563517586492"></a>WCOREDUMP</strong>, and <strong id="b316516775011"><a name="b316516775011"></a><a name="b316516775011"></a>WIFCONTINUED</strong>.</li></ul>
</td>
</tr>
<tr id="row4305194294417"><td class="cellrowborder" rowspan="10" valign="top" width="13.020000000000001%" headers="mcps1.2.5.1.1 "><p id="p5305194264419"><a name="p5305194264419"></a><a name="p5305194264419"></a>Scheduling</p>
</td>
<td class="cellrowborder" valign="top" width="23.150000000000002%" headers="mcps1.2.5.1.2 "><p id="p630544224416"><a name="p630544224416"></a><a name="p630544224416"></a>getpriority</p>
</td>
<td class="cellrowborder" valign="top" width="28.93%" headers="mcps1.2.5.1.3 "><p id="p174915589591"><a name="p174915589591"></a><a name="p174915589591"></a>Obtains the static priority of a specified ID.</p>
</td>
<td class="cellrowborder" rowspan="2" valign="top" width="34.9%" headers="mcps1.2.5.1.4 "><a name="ul185518513478"></a><a name="ul185518513478"></a><ul id="ul185518513478"><li><strong id="b4971715165515"><a name="b4971715165515"></a><a name="b4971715165515"></a>PRIO_PGRP</strong> and <strong id="b8758417185515"><a name="b8758417185515"></a><a name="b8758417185515"></a>PRIO_USER</strong> are not supported.</li></ul>
<a name="ul85091358174711"></a><a name="ul85091358174711"></a><ul id="ul85091358174711"><li>The priority to obtain and set refers to the static priority. The dynamic priority is not involved.</li></ul>
</td>
</tr>
<tr id="row930511425448"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1730524217448"><a name="p1730524217448"></a><a name="p1730524217448"></a>setpriority</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p17750205817594"><a name="p17750205817594"></a><a name="p17750205817594"></a>Sets the static priority of a specified ID.</p>
</td>
</tr>
<tr id="row2305174216445"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p7305942104417"><a name="p7305942104417"></a><a name="p7305942104417"></a>sched_rr_get_interval</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p1362018100165"><a name="p1362018100165"></a><a name="p1362018100165"></a>Obtains the execution time limit of a process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p5306134212447"><a name="p5306134212447"></a><a name="p5306134212447"></a>N/A</p>
</td>
</tr>
<tr id="row33061042104416"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p143061642164412"><a name="p143061642164412"></a><a name="p143061642164412"></a>sched_yield</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p1262017102164"><a name="p1262017102164"></a><a name="p1262017102164"></a>Yields the running process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p14306134220441"><a name="p14306134220441"></a><a name="p14306134220441"></a>N/A</p>
</td>
</tr>
<tr id="row11306134234417"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p11306184264417"><a name="p11306184264417"></a><a name="p11306184264417"></a>sched_get_priority_max</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p123062423446"><a name="p123062423446"></a><a name="p123062423446"></a>Obtains the maximum static priority that can be used for a process.</p>
</td>
<td class="cellrowborder" rowspan="4" valign="top" headers="mcps1.2.5.1.3 "><p id="p11306154210440"><a name="p11306154210440"></a><a name="p11306154210440"></a>The scheduling policy can only be <strong id="b1085116295185"><a name="b1085116295185"></a><a name="b1085116295185"></a>SCHED_FIFO</strong> or <strong id="b953693512189"><a name="b953693512189"></a><a name="b953693512189"></a>SCHED_RR</strong>.</p>
</td>
</tr>
<tr id="row15306242124413"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p430612427448"><a name="p430612427448"></a><a name="p430612427448"></a>sched_get_priority_min</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p430618428442"><a name="p430618428442"></a><a name="p430618428442"></a>Obtains the minimum static priority that can be used for a process.</p>
</td>
</tr>
<tr id="row730610428448"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p230684284419"><a name="p230684284419"></a><a name="p230684284419"></a>sched_getscheduler</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p20306184224417"><a name="p20306184224417"></a><a name="p20306184224417"></a>Obtains the scheduling policy of a process.</p>
</td>
</tr>
<tr id="row630764215441"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1530719424444"><a name="p1530719424444"></a><a name="p1530719424444"></a>sched_setscheduler</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p13072042104416"><a name="p13072042104416"></a><a name="p13072042104416"></a>Sets a scheduling policy for a process.</p>
</td>
</tr>
<tr id="row3307184274411"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p12307114274419"><a name="p12307114274419"></a><a name="p12307114274419"></a>sched_getparam</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p9307104210441"><a name="p9307104210441"></a><a name="p9307104210441"></a>Obtains scheduling parameters of a process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p163071842194417"><a name="p163071842194417"></a><a name="p163071842194417"></a>N/A</p>
</td>
</tr>
<tr id="row18307104210449"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1230784264419"><a name="p1230784264419"></a><a name="p1230784264419"></a>sched_setparam</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p1530784215445"><a name="p1530784215445"></a><a name="p1530784215445"></a>Sets scheduling parameters related to a scheduling policy for a process.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p730714264415"><a name="p730714264415"></a><a name="p730714264415"></a>N/A</p>
</td>
</tr>
<tr id="row17412918306"><td class="cellrowborder" rowspan="6" valign="top" width="13.020000000000001%" headers="mcps1.2.5.1.1 "><p id="p8528162314312"><a name="p8528162314312"></a><a name="p8528162314312"></a>exec</p>
</td>
<td class="cellrowborder" valign="top" width="23.150000000000002%" headers="mcps1.2.5.1.2 "><p id="p1951498305"><a name="p1951498305"></a><a name="p1951498305"></a>execl</p>
</td>
<td class="cellrowborder" valign="top" width="28.93%" headers="mcps1.2.5.1.3 "><p id="p1612191842215"><a name="p1612191842215"></a><a name="p1612191842215"></a>Executes a specified user program file in ELF format.</p>
</td>
<td class="cellrowborder" valign="top" width="34.9%" headers="mcps1.2.5.1.4 "><p id="p11679610113215"><a name="p11679610113215"></a><a name="p11679610113215"></a>N/A</p>
</td>
</tr>
<tr id="row16964151163015"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p1996413117300"><a name="p1996413117300"></a><a name="p1996413117300"></a>execle</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p104059331261"><a name="p104059331261"></a><a name="p104059331261"></a>Executes a specified user program file in ELF format.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p3209101117329"><a name="p3209101117329"></a><a name="p3209101117329"></a>N/A</p>
</td>
</tr>
<tr id="row9418101418309"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p741881443010"><a name="p741881443010"></a><a name="p741881443010"></a>execlp</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p493315383264"><a name="p493315383264"></a><a name="p493315383264"></a>Executes a specified user program file in ELF format.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p8741121112325"><a name="p8741121112325"></a><a name="p8741121112325"></a>N/A</p>
</td>
</tr>
<tr id="row2058611176305"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p155869170309"><a name="p155869170309"></a><a name="p155869170309"></a>execv</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p1644334112613"><a name="p1644334112613"></a><a name="p1644334112613"></a>Executes a specified user program file in ELF format.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p423311211323"><a name="p423311211323"></a><a name="p423311211323"></a>N/A</p>
</td>
</tr>
<tr id="row182359476306"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p202351547163016"><a name="p202351547163016"></a><a name="p202351547163016"></a>execve</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p13152444192616"><a name="p13152444192616"></a><a name="p13152444192616"></a>Executes a specified user program file in ELF format.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p148072123324"><a name="p148072123324"></a><a name="p148072123324"></a>N/A</p>
</td>
</tr>
<tr id="row14242145013304"><td class="cellrowborder" valign="top" headers="mcps1.2.5.1.1 "><p id="p02437507305"><a name="p02437507305"></a><a name="p02437507305"></a>execvp</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.2 "><p id="p06334469262"><a name="p06334469262"></a><a name="p06334469262"></a>Executes a specified user program file in ELF format.</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.5.1.3 "><p id="p333161353217"><a name="p333161353217"></a><a name="p333161353217"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

