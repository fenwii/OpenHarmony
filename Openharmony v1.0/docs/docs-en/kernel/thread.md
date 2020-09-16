# Thread<a name="EN-US_TOPIC_0000001051452247"></a>

## Basic Concepts<a name="section1179311337405"></a>

Threads are the minimum running units that compete for system resources. They can use or wait to use CPUs and use system resources such as memory. They run independently from one another.

Threads in each process of the OpenHarmony kernel run and are scheduled independently. The scheduling of threads in a process is not affected by threads in other processes.

Threads in the OpenHarmony kernel use the preemptive scheduling mechanism, either round-robin \(RR\) scheduling or First In First Out \(FIFO\) scheduling.

Threads in the OpenHarmony kernel are assigned 32 priorities, ranging from  **0**  \(highest\) to  **31**  \(lowest\).

A high-priority thread in a process can preempt the resources of a low-priority thread in this process. The low-priority thread can be scheduled only after the high-priority thread is blocked or terminated.

**A thread may have the following states:**

-   **Init**: The thread is being created.

-   **Ready**: The thread is in the ready list and waits for being scheduled by the CPU.

-   **Running**: The thread is running.

-   **Blocked**: The thread is blocked and suspended. The  **Blocked**  states include  **pend**  \(blocked due to lock, event, or semaphore issues\),  **suspend**  \(active pending\),  **delay**  \(blocked due to delays\), and  **pendtime**  \(blocked by waiting timeout of locks, events, or semaphores\).

-   **Exit**: The thread stops running and waits for the parent thread to reclaim its control block resources.


**Figure  1**  State transition of a thread<a name="fig15746193414436"></a>  


![](figures/en-us_image_0000001054569218.png)

**Description of the thread state transition:**

-   Init→Ready:

    When a thread is created, the thread enters the  **Init**  state to start initialization after obtaining the control block. After the thread is initialized, the thread is inserted into the scheduling queue and therefore enters the  **Ready**  state.

-   Ready→Running:

    When a thread switchover is triggered, the thread with the highest priority in the ready list is executed and enters the  **Running**  state. This thread will be deleted from the ready list.

-   Running→Blocked:

    When a running thread is blocked \(for example, is pended, delayed, or reading semaphores\), the thread is deleted from the ready list, and its state changes from  **Running**  to  **Blocked**. Then, a thread switchover is triggered to run the thread with the highest priority in the ready list.

-   Blocked→Ready/Blocked→Running:

    After the blocked thread is restored \(for example, the thread is restored, the delay times out, the semaphore reading times out, or semaphores have been read\), the thread is added to the ready list and changes from the  **Blocked**  state to the  **Ready**  state. In this case, if the priority of the restored thread is higher than that of the running thread, a thread switchover occurs to run the restored thread, and therefore the restored thread changes from the  **Ready**  state to the  **Running**  state.

-   Ready→Blocked:

    A thread may also be blocked \(suspended\) in the  **Ready**  state. The blocked thread will change from the  **Ready**  state to the  **Blocked**  state and is deleted from the ready list. In this case, the thread will not be scheduled until it is restored.

-   Running→Ready:

    After a thread with a higher priority is created or restored, threads will be scheduled. The thread with the highest priority in the ready list will change to the  **Running**  state. The originally running thread will change from the  **Running**  state to the  **Ready**  state and be added to the ready list.

-   Running→Exit:

    When a running thread is terminated, its state changes from  **Running**  to  **Exit**. The thread without the  **PTHREAD\_CREATE\_DETACHED**  attribute will present the  **Exit**  state after being terminated.

-   Blocked→Exit:

    If an API is called to delete a blocked thread, the thread changes from the  **Blocked**  state to the  **Exit**  state.


## When to Use<a name="section44877547404"></a>

After a thread is created, it can be scheduled, suspended, restored, and delayed in user space. In addition, you can set and obtain the scheduling priority and scheduling policy of the thread.

## Available APIs<a name="section2069477134115"></a>

The following table describes the APIs provided by the thread management module of the OpenHarmony kernel.

**Table  1**  APIs provided by the thread management module

<a name="table134475244618"></a>
<table><thead align="left"><tr id="row16880122144619"><th class="cellrowborder" valign="top" width="14.29%" id="mcps1.2.5.1.1"><p id="p88808214619"><a name="p88808214619"></a><a name="p88808214619"></a>Header File</p>
</th>
<th class="cellrowborder" valign="top" width="28.57%" id="mcps1.2.5.1.2"><p id="p16880182174611"><a name="p16880182174611"></a><a name="p16880182174611"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="22.45%" id="mcps1.2.5.1.3"><p id="p198806214469"><a name="p198806214469"></a><a name="p198806214469"></a>Description</p>
</th>
<th class="cellrowborder" valign="top" width="34.69%" id="mcps1.2.5.1.4"><p id="p1188013294618"><a name="p1188013294618"></a><a name="p1188013294618"></a>Remarks</p>
</th>
</tr>
</thead>
<tbody><tr id="row1188092104619"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p488052134616"><a name="p488052134616"></a><a name="p488052134616"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p108808218461"><a name="p108808218461"></a><a name="p108808218461"></a>pthread_attr_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p18809234612"><a name="p18809234612"></a><a name="p18809234612"></a>Destroys a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1988012213468"><a name="p1988012213468"></a><a name="p1988012213468"></a>N/A</p>
</td>
</tr>
<tr id="row28802274616"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p148806212469"><a name="p148806212469"></a><a name="p148806212469"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p7880720461"><a name="p7880720461"></a><a name="p7880720461"></a>pthread_attr_getinheritsched</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p588012104619"><a name="p588012104619"></a><a name="p588012104619"></a>Obtains inherit scheduler attributes of a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p11880524466"><a name="p11880524466"></a><a name="p11880524466"></a>N/A</p>
</td>
</tr>
<tr id="row1888132164611"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p8881202114618"><a name="p8881202114618"></a><a name="p8881202114618"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p13881142154614"><a name="p13881142154614"></a><a name="p13881142154614"></a>pthread_attr_getschedparam</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p12881142144612"><a name="p12881142144612"></a><a name="p12881142144612"></a>Obtains scheduling parameter attributes of a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p988112204611"><a name="p988112204611"></a><a name="p988112204611"></a>N/A</p>
</td>
</tr>
<tr id="row788102134613"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p16881122114611"><a name="p16881122114611"></a><a name="p16881122114611"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p388111215466"><a name="p388111215466"></a><a name="p388111215466"></a>pthread_attr_getschedpolicy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p19881152174612"><a name="p19881152174612"></a><a name="p19881152174612"></a>Obtains scheduling policy attributes of a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p988112294619"><a name="p988112294619"></a><a name="p988112294619"></a><span id="text174691111144919"><a name="text174691111144919"></a><a name="text174691111144919"></a>OpenHarmony</span> supports the <strong id="b129611652193717"><a name="b129611652193717"></a><a name="b129611652193717"></a>SCHED_FIFO</strong> and <strong id="b45681956123715"><a name="b45681956123715"></a><a name="b45681956123715"></a>SCHED_RR</strong> scheduling policies.</p>
</td>
</tr>
<tr id="row14881423468"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p588152114611"><a name="p588152114611"></a><a name="p588152114611"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p188811626465"><a name="p188811626465"></a><a name="p188811626465"></a>pthread_attr_getstacksize</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p08825214467"><a name="p08825214467"></a><a name="p08825214467"></a>Obtains the stack size of a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p8882827467"><a name="p8882827467"></a><a name="p8882827467"></a>N/A</p>
</td>
</tr>
<tr id="row088212144619"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p688215274612"><a name="p688215274612"></a><a name="p688215274612"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p88827218466"><a name="p88827218466"></a><a name="p88827218466"></a>pthread_attr_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p14447368158"><a name="p14447368158"></a><a name="p14447368158"></a>Initializes a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p12882202134618"><a name="p12882202134618"></a><a name="p12882202134618"></a>N/A</p>
</td>
</tr>
<tr id="row1788214210462"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p3882525463"><a name="p3882525463"></a><a name="p3882525463"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1882528461"><a name="p1882528461"></a><a name="p1882528461"></a>pthread_attr_setdetachstate</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p11455363157"><a name="p11455363157"></a><a name="p11455363157"></a>Sets the detach state for a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1788202174613"><a name="p1788202174613"></a><a name="p1788202174613"></a>N/A</p>
</td>
</tr>
<tr id="row188829211469"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1088222134619"><a name="p1088222134619"></a><a name="p1088222134619"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p588272204612"><a name="p588272204612"></a><a name="p588272204612"></a>pthread_attr_setinheritsched</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p14611364154"><a name="p14611364154"></a><a name="p14611364154"></a>Sets inherit scheduler attributes for a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p3883102174611"><a name="p3883102174611"></a><a name="p3883102174611"></a>N/A</p>
</td>
</tr>
<tr id="row1588310244610"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p118831210461"><a name="p118831210461"></a><a name="p118831210461"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p188318214611"><a name="p188318214611"></a><a name="p188318214611"></a>pthread_attr_setschedparam</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1746636141515"><a name="p1746636141515"></a><a name="p1746636141515"></a>Sets scheduling parameter attributes for a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p44251243115214"><a name="p44251243115214"></a><a name="p44251243115214"></a>A larger value represents a higher priority of the thread in the system.</p>
<p id="p142941635183917"><a name="p142941635183917"></a><a name="p142941635183917"></a>Note: The <strong id="b48010297529"><a name="b48010297529"></a><a name="b48010297529"></a>inheritsched</strong> field of the <strong id="b34123735210"><a name="b34123735210"></a><a name="b34123735210"></a>pthread_attr_t</strong> attribute must be set to <strong id="b15898192195319"><a name="b15898192195319"></a><a name="b15898192195319"></a>PTHREAD_EXPLICIT_SCHED</strong>. Otherwise, the configured thread scheduling priority does not take effect. The default value is <strong id="b4779174311537"><a name="b4779174311537"></a><a name="b4779174311537"></a>PTHREAD_INHERIT_SCHED</strong>.</p>
</td>
</tr>
<tr id="row118831264610"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1688315220469"><a name="p1688315220469"></a><a name="p1688315220469"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1488320217468"><a name="p1488320217468"></a><a name="p1488320217468"></a>pthread_attr_setschedpolicy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p154615365156"><a name="p154615365156"></a><a name="p154615365156"></a>Sets scheduling policy attributes for a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p28831823468"><a name="p28831823468"></a><a name="p28831823468"></a><span id="text43341845185418"><a name="text43341845185418"></a><a name="text43341845185418"></a>OpenHarmony</span> supports the <strong id="b12334144516544"><a name="b12334144516544"></a><a name="b12334144516544"></a>SCHED_FIFO</strong> and <strong id="b13335144525411"><a name="b13335144525411"></a><a name="b13335144525411"></a>SCHED_RR</strong> scheduling policies.</p>
</td>
</tr>
<tr id="row888320244618"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p88840216460"><a name="p88840216460"></a><a name="p88840216460"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p3884328461"><a name="p3884328461"></a><a name="p3884328461"></a>pthread_attr_setstacksize</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p158841329461"><a name="p158841329461"></a><a name="p158841329461"></a>Sets the stack size for a thread attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1488412244619"><a name="p1488412244619"></a><a name="p1488412244619"></a>N/A</p>
</td>
</tr>
<tr id="row168841629468"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p988452104612"><a name="p988452104612"></a><a name="p988452104612"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p19884162194610"><a name="p19884162194610"></a><a name="p19884162194610"></a>pthread_getattr_np</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p64812367153"><a name="p64812367153"></a><a name="p64812367153"></a>Obtains the attributes of a created thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p108847254615"><a name="p108847254615"></a><a name="p108847254615"></a>N/A</p>
</td>
</tr>
<tr id="row28842029469"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1788412214613"><a name="p1788412214613"></a><a name="p1788412214613"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p188411220465"><a name="p188411220465"></a><a name="p188411220465"></a>pthread_cancel</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p08001317121519"><a name="p08001317121519"></a><a name="p08001317121519"></a>Sends a cancellation request to a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1288416254611"><a name="p1288416254611"></a><a name="p1288416254611"></a>N/A</p>
</td>
</tr>
<tr id="row788418214464"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p128844204618"><a name="p128844204618"></a><a name="p128844204618"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p17885182194616"><a name="p17885182194616"></a><a name="p17885182194616"></a>pthread_testcancel</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1279931731513"><a name="p1279931731513"></a><a name="p1279931731513"></a>Requests delivery of any pending cancellation request.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1588552204613"><a name="p1588552204613"></a><a name="p1588552204613"></a>N/A</p>
</td>
</tr>
<tr id="row98857211461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p5885102174614"><a name="p5885102174614"></a><a name="p5885102174614"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1388582144612"><a name="p1388582144612"></a><a name="p1388582144612"></a>pthread_setcanceltype</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p2079991771517"><a name="p2079991771517"></a><a name="p2079991771517"></a>Sets the cancelability type for the calling thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p138854224619"><a name="p138854224619"></a><a name="p138854224619"></a>N/A</p>
</td>
</tr>
<tr id="row1988516211466"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p68851929468"><a name="p68851929468"></a><a name="p68851929468"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p288515234613"><a name="p288515234613"></a><a name="p288515234613"></a>pthread_setcancelstate</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p8799217101512"><a name="p8799217101512"></a><a name="p8799217101512"></a>Sets the cancelability state for the calling thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p488518224620"><a name="p488518224620"></a><a name="p488518224620"></a>N/A</p>
</td>
</tr>
<tr id="row1288520284619"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p158851125462"><a name="p158851125462"></a><a name="p158851125462"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p188511211463"><a name="p188511211463"></a><a name="p188511211463"></a>pthread_create</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p18798171712153"><a name="p18798171712153"></a><a name="p18798171712153"></a>Creates a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p14886192124615"><a name="p14886192124615"></a><a name="p14886192124615"></a>N/A</p>
</td>
</tr>
<tr id="row1288614204611"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p388610218462"><a name="p388610218462"></a><a name="p388610218462"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p108861274620"><a name="p108861274620"></a><a name="p108861274620"></a>pthread_detach</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p379831718156"><a name="p379831718156"></a><a name="p379831718156"></a>Detaches a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p38861126461"><a name="p38861126461"></a><a name="p38861126461"></a>N/A</p>
</td>
</tr>
<tr id="row188614213467"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p14886826461"><a name="p14886826461"></a><a name="p14886826461"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p108861527469"><a name="p108861527469"></a><a name="p108861527469"></a>pthread_equal</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p18799817181516"><a name="p18799817181516"></a><a name="p18799817181516"></a>Compares whether two thread IDs are equal.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p588612219467"><a name="p588612219467"></a><a name="p588612219467"></a>N/A</p>
</td>
</tr>
<tr id="row1488619294613"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p108867214619"><a name="p108867214619"></a><a name="p108867214619"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p988752164613"><a name="p988752164613"></a><a name="p988752164613"></a>pthread_exit</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p979871741512"><a name="p979871741512"></a><a name="p979871741512"></a>Terminates the calling thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p28871522460"><a name="p28871522460"></a><a name="p28871522460"></a>N/A</p>
</td>
</tr>
<tr id="row88871220467"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p188877244617"><a name="p188877244617"></a><a name="p188877244617"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p188879212461"><a name="p188879212461"></a><a name="p188879212461"></a>pthread_getschedparam</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p158001717101517"><a name="p158001717101517"></a><a name="p158001717101517"></a>Obtains the scheduling policy and parameters of a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p198871128465"><a name="p198871128465"></a><a name="p198871128465"></a><span id="text98991723195910"><a name="text98991723195910"></a><a name="text98991723195910"></a>OpenHarmony</span> supports the <strong id="b5899132311593"><a name="b5899132311593"></a><a name="b5899132311593"></a>SCHED_FIFO</strong> and <strong id="b390011234594"><a name="b390011234594"></a><a name="b390011234594"></a>SCHED_RR</strong> scheduling policies.</p>
</td>
</tr>
<tr id="row198871527462"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1188715284613"><a name="p1188715284613"></a><a name="p1188715284613"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p088715274620"><a name="p088715274620"></a><a name="p088715274620"></a>pthread_join</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p2079921719159"><a name="p2079921719159"></a><a name="p2079921719159"></a>Waits for a thread to terminate.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p2088815214462"><a name="p2088815214462"></a><a name="p2088815214462"></a>N/A</p>
</td>
</tr>
<tr id="row13888142184617"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p688802124614"><a name="p688802124614"></a><a name="p688802124614"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1088820215469"><a name="p1088820215469"></a><a name="p1088820215469"></a>pthread_self</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1179931761515"><a name="p1179931761515"></a><a name="p1179931761515"></a>Obtains the ID of the calling thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p588802164611"><a name="p588802164611"></a><a name="p588802164611"></a>N/A</p>
</td>
</tr>
<tr id="row15888132124614"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p8888627462"><a name="p8888627462"></a><a name="p8888627462"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1888811214620"><a name="p1888811214620"></a><a name="p1888811214620"></a>pthread_setschedprio</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1888816219469"><a name="p1888816219469"></a><a name="p1888816219469"></a>Sets a static scheduling priority for a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p48881822463"><a name="p48881822463"></a><a name="p48881822463"></a>N/A</p>
</td>
</tr>
<tr id="row12889142194616"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1988915284613"><a name="p1988915284613"></a><a name="p1988915284613"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p148891026466"><a name="p148891026466"></a><a name="p148891026466"></a>pthread_kill</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p128001017121510"><a name="p128001017121510"></a><a name="p128001017121510"></a>Sends a signal to a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p9889522466"><a name="p9889522466"></a><a name="p9889522466"></a>N/A</p>
</td>
</tr>
<tr id="row19889624465"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p0889620469"><a name="p0889620469"></a><a name="p0889620469"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p58894244612"><a name="p58894244612"></a><a name="p58894244612"></a>pthread_once</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p4801617171515"><a name="p4801617171515"></a><a name="p4801617171515"></a>Enables the initialization function to be called only once.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p16889122204617"><a name="p16889122204617"></a><a name="p16889122204617"></a>N/A</p>
</td>
</tr>
<tr id="row288917219462"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1688913294617"><a name="p1688913294617"></a><a name="p1688913294617"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p2889152174613"><a name="p2889152174613"></a><a name="p2889152174613"></a>pthread_atfork</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p198899219461"><a name="p198899219461"></a><a name="p198899219461"></a>Registers a fork handler to be called before and after <strong id="b721019481629"><a name="b721019481629"></a><a name="b721019481629"></a>fork()</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p2889520467"><a name="p2889520467"></a><a name="p2889520467"></a>N/A</p>
</td>
</tr>
<tr id="row988922114611"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p88897234618"><a name="p88897234618"></a><a name="p88897234618"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1588952114611"><a name="p1588952114611"></a><a name="p1588952114611"></a>pthread_cleanup_pop</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p2048113619157"><a name="p2048113619157"></a><a name="p2048113619157"></a>Removes the routine at the top of the clean-up handler stack.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p178901424460"><a name="p178901424460"></a><a name="p178901424460"></a>N/A</p>
</td>
</tr>
<tr id="row188906284610"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p8890152134616"><a name="p8890152134616"></a><a name="p8890152134616"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p589017244615"><a name="p589017244615"></a><a name="p589017244615"></a>pthread_cleanup_push</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p114823610159"><a name="p114823610159"></a><a name="p114823610159"></a>Pushes the routine to the top of the clean-up handler stack.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1890828463"><a name="p1890828463"></a><a name="p1890828463"></a>N/A</p>
</td>
</tr>
<tr id="row189012284618"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p68908224615"><a name="p68908224615"></a><a name="p68908224615"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1589011234615"><a name="p1589011234615"></a><a name="p1589011234615"></a>pthread_barrier_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p188901723467"><a name="p188901723467"></a><a name="p188901723467"></a>Destroys a barrier (an advanced real-time thread).</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p88902244620"><a name="p88902244620"></a><a name="p88902244620"></a>N/A</p>
</td>
</tr>
<tr id="row089015218467"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1689011254619"><a name="p1689011254619"></a><a name="p1689011254619"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p48908214468"><a name="p48908214468"></a><a name="p48908214468"></a>pthread_barrier_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p7890172124617"><a name="p7890172124617"></a><a name="p7890172124617"></a>Initializes a barrier (an advanced real-time thread).</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1689015217461"><a name="p1689015217461"></a><a name="p1689015217461"></a>N/A</p>
</td>
</tr>
<tr id="row8890182114615"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p118907215468"><a name="p118907215468"></a><a name="p118907215468"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p128902215466"><a name="p128902215466"></a><a name="p128902215466"></a>pthread_barrier_wait</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1189112204618"><a name="p1189112204618"></a><a name="p1189112204618"></a>Synchronizes participating threads at a barrier.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p208911722464"><a name="p208911722464"></a><a name="p208911722464"></a>N/A</p>
</td>
</tr>
<tr id="row589110216461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p08911826466"><a name="p08911826466"></a><a name="p08911826466"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p18891321469"><a name="p18891321469"></a><a name="p18891321469"></a>pthread_barrierattr_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1048203611514"><a name="p1048203611514"></a><a name="p1048203611514"></a>Destroys a barrier attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1989112124612"><a name="p1989112124612"></a><a name="p1989112124612"></a>N/A</p>
</td>
</tr>
<tr id="row9891624468"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p108914214465"><a name="p108914214465"></a><a name="p108914214465"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1289182104618"><a name="p1289182104618"></a><a name="p1289182104618"></a>pthread_barrierattr_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1848113618159"><a name="p1848113618159"></a><a name="p1848113618159"></a>Initializes a barrier attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p12891202104615"><a name="p12891202104615"></a><a name="p12891202104615"></a>N/A</p>
</td>
</tr>
<tr id="row118914214464"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1289116214465"><a name="p1289116214465"></a><a name="p1289116214465"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1989116254616"><a name="p1989116254616"></a><a name="p1989116254616"></a>pthread_mutex_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p3891927469"><a name="p3891927469"></a><a name="p3891927469"></a>Destroys a mutex.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1189111220464"><a name="p1189111220464"></a><a name="p1189111220464"></a>N/A</p>
</td>
</tr>
<tr id="row18891326468"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p68915219469"><a name="p68915219469"></a><a name="p68915219469"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p689212124610"><a name="p689212124610"></a><a name="p689212124610"></a>pthread_mutex_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p189262174615"><a name="p189262174615"></a><a name="p189262174615"></a>Initializes a mutex.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p089216210461"><a name="p089216210461"></a><a name="p089216210461"></a>N/A</p>
</td>
</tr>
<tr id="row1689213216461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p38923244615"><a name="p38923244615"></a><a name="p38923244615"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p989216213462"><a name="p989216213462"></a><a name="p989216213462"></a>pthread_mutex_lock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1089216218469"><a name="p1089216218469"></a><a name="p1089216218469"></a>Locks a mutex.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p58921028469"><a name="p58921028469"></a><a name="p58921028469"></a>N/A</p>
</td>
</tr>
<tr id="row989214284614"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p168927213469"><a name="p168927213469"></a><a name="p168927213469"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1389262154612"><a name="p1389262154612"></a><a name="p1389262154612"></a>pthread_mutex_trylock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p9892182114619"><a name="p9892182114619"></a><a name="p9892182114619"></a>Attempts to lock a mutex.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p28926213469"><a name="p28926213469"></a><a name="p28926213469"></a>N/A</p>
</td>
</tr>
<tr id="row1989218264610"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1892122164617"><a name="p1892122164617"></a><a name="p1892122164617"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p8893132114614"><a name="p8893132114614"></a><a name="p8893132114614"></a>pthread_mutex_unlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p7893182154611"><a name="p7893182154611"></a><a name="p7893182154611"></a>Unlocks a mutex.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1689318210466"><a name="p1689318210466"></a><a name="p1689318210466"></a>N/A</p>
</td>
</tr>
<tr id="row10893192194614"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1789317254618"><a name="p1789317254618"></a><a name="p1789317254618"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1089320217465"><a name="p1089320217465"></a><a name="p1089320217465"></a>pthread_mutexattr_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p168933274614"><a name="p168933274614"></a><a name="p168933274614"></a>Destroys a mutex attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p11893326462"><a name="p11893326462"></a><a name="p11893326462"></a>N/A</p>
</td>
</tr>
<tr id="row7893523465"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p128937234619"><a name="p128937234619"></a><a name="p128937234619"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p38931922469"><a name="p38931922469"></a><a name="p38931922469"></a>pthread_mutexattr_gettype</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p547173614155"><a name="p547173614155"></a><a name="p547173614155"></a>Obtains the mutex type attribute.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p118932211469"><a name="p118932211469"></a><a name="p118932211469"></a>N/A</p>
</td>
</tr>
<tr id="row15893526464"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1989416284611"><a name="p1989416284611"></a><a name="p1989416284611"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1389413212461"><a name="p1389413212461"></a><a name="p1389413212461"></a>pthread_mutexattr_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p447133671516"><a name="p447133671516"></a><a name="p447133671516"></a>Initializes a mutex attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1189415254616"><a name="p1189415254616"></a><a name="p1189415254616"></a>N/A</p>
</td>
</tr>
<tr id="row1894102194616"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1289432134614"><a name="p1289432134614"></a><a name="p1289432134614"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p18941928465"><a name="p18941928465"></a><a name="p18941928465"></a>pthread_mutexattr_settype</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1247203611159"><a name="p1247203611159"></a><a name="p1247203611159"></a>Sets the mutex type attribute.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p168941328465"><a name="p168941328465"></a><a name="p168941328465"></a>N/A</p>
</td>
</tr>
<tr id="row48942215466"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p108942217463"><a name="p108942217463"></a><a name="p108942217463"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1189418216468"><a name="p1189418216468"></a><a name="p1189418216468"></a>pthread_mutex_timedlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p580191751513"><a name="p580191751513"></a><a name="p580191751513"></a>Blocks the calling thread to lock a mutex.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p0894122134613"><a name="p0894122134613"></a><a name="p0894122134613"></a>N/A</p>
</td>
</tr>
<tr id="row1894122134612"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p689414212466"><a name="p689414212466"></a><a name="p689414212466"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1189517234613"><a name="p1189517234613"></a><a name="p1189517234613"></a>pthread_rwlock_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p7895429466"><a name="p7895429466"></a><a name="p7895429466"></a>Destroys a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p10895122174617"><a name="p10895122174617"></a><a name="p10895122174617"></a>N/A</p>
</td>
</tr>
<tr id="row989562144613"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p389542184611"><a name="p389542184611"></a><a name="p389542184611"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p13895142104612"><a name="p13895142104612"></a><a name="p13895142104612"></a>pthread_rwlock_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p0895172114615"><a name="p0895172114615"></a><a name="p0895172114615"></a>Initializes a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p78951827462"><a name="p78951827462"></a><a name="p78951827462"></a>N/A</p>
</td>
</tr>
<tr id="row118953217461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p689516216461"><a name="p689516216461"></a><a name="p689516216461"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p58955244611"><a name="p58955244611"></a><a name="p58955244611"></a>pthread_rwlock_rdlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p15803181719154"><a name="p15803181719154"></a><a name="p15803181719154"></a>Applies a read lock to a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p889502164620"><a name="p889502164620"></a><a name="p889502164620"></a>N/A</p>
</td>
</tr>
<tr id="row689515218467"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p178956218463"><a name="p178956218463"></a><a name="p178956218463"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p17895152134618"><a name="p17895152134618"></a><a name="p17895152134618"></a>pthread_rwlock_timedrdlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p5803181721513"><a name="p5803181721513"></a><a name="p5803181721513"></a>Blocks the calling thread to lock a read-write lock for reading.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1589622114618"><a name="p1589622114618"></a><a name="p1589622114618"></a>N/A</p>
</td>
</tr>
<tr id="row789615254618"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p168961622467"><a name="p168961622467"></a><a name="p168961622467"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1889612124610"><a name="p1889612124610"></a><a name="p1889612124610"></a>pthread_rwlock_timedwrlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p11431336191520"><a name="p11431336191520"></a><a name="p11431336191520"></a>Blocks the calling thread to lock a read-write lock for writing.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p188966244617"><a name="p188966244617"></a><a name="p188966244617"></a>N/A</p>
</td>
</tr>
<tr id="row38966284617"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1389620264616"><a name="p1389620264616"></a><a name="p1389620264616"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p138961222469"><a name="p138961222469"></a><a name="p138961222469"></a>pthread_rwlock_tryrdlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1780314172156"><a name="p1780314172156"></a><a name="p1780314172156"></a>Attempts to apply a read lock to a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p989642174614"><a name="p989642174614"></a><a name="p989642174614"></a>N/A</p>
</td>
</tr>
<tr id="row20896142154616"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1689622204620"><a name="p1689622204620"></a><a name="p1689622204620"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p38981620462"><a name="p38981620462"></a><a name="p38981620462"></a>pthread_rwlock_trywrlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1443936191520"><a name="p1443936191520"></a><a name="p1443936191520"></a>Attempts to apply a write lock to a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p128981725468"><a name="p128981725468"></a><a name="p128981725468"></a>N/A</p>
</td>
</tr>
<tr id="row489815210461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p18899821465"><a name="p18899821465"></a><a name="p18899821465"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1789913217469"><a name="p1789913217469"></a><a name="p1789913217469"></a>pthread_rwlock_unlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p143193651512"><a name="p143193651512"></a><a name="p143193651512"></a>Unlocks a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p390010211465"><a name="p390010211465"></a><a name="p390010211465"></a>N/A</p>
</td>
</tr>
<tr id="row1890032124612"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p159009219466"><a name="p159009219466"></a><a name="p159009219466"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1190010214469"><a name="p1190010214469"></a><a name="p1190010214469"></a>pthread_rwlock_wrlock</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p14803517111519"><a name="p14803517111519"></a><a name="p14803517111519"></a>Applies a write lock to a read-write lock.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1390011294618"><a name="p1390011294618"></a><a name="p1390011294618"></a>N/A</p>
</td>
</tr>
<tr id="row590032124613"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p890022144619"><a name="p890022144619"></a><a name="p890022144619"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1290010244614"><a name="p1290010244614"></a><a name="p1290010244614"></a>pthread_rwlockattr_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p154719365157"><a name="p154719365157"></a><a name="p154719365157"></a>Destroys a read-write lock attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p19900428461"><a name="p19900428461"></a><a name="p19900428461"></a>N/A</p>
</td>
</tr>
<tr id="row190042174617"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1190010284610"><a name="p1190010284610"></a><a name="p1190010284610"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1890017217462"><a name="p1890017217462"></a><a name="p1890017217462"></a>pthread_rwlockattr_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p247133661511"><a name="p247133661511"></a><a name="p247133661511"></a>Initializes a read-write lock attribute object.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p17900192154611"><a name="p17900192154611"></a><a name="p17900192154611"></a>N/A</p>
</td>
</tr>
<tr id="row10900320461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p5901229462"><a name="p5901229462"></a><a name="p5901229462"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p149018294618"><a name="p149018294618"></a><a name="p149018294618"></a>pthread_cond_broadcast</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p16802181771514"><a name="p16802181771514"></a><a name="p16802181771514"></a>Unblocks all threads that are currently blocked on the condition variable <strong id="b3838632172213"><a name="b3838632172213"></a><a name="b3838632172213"></a>cond</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1290118264619"><a name="p1290118264619"></a><a name="p1290118264619"></a>N/A</p>
</td>
</tr>
<tr id="row590115234620"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p15901202194613"><a name="p15901202194613"></a><a name="p15901202194613"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1190119212466"><a name="p1190119212466"></a><a name="p1190119212466"></a>pthread_cond_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p19802017191512"><a name="p19802017191512"></a><a name="p19802017191512"></a>Destroys a condition variable.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p1390122114610"><a name="p1390122114610"></a><a name="p1390122114610"></a>N/A</p>
</td>
</tr>
<tr id="row1890192164611"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p3901112204616"><a name="p3901112204616"></a><a name="p3901112204616"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1890102184618"><a name="p1890102184618"></a><a name="p1890102184618"></a>pthread_cond_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p48025173153"><a name="p48025173153"></a><a name="p48025173153"></a>Initializes a condition variable.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p119011210466"><a name="p119011210466"></a><a name="p119011210466"></a>N/A</p>
</td>
</tr>
<tr id="row129011214615"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p9902523468"><a name="p9902523468"></a><a name="p9902523468"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p59021722460"><a name="p59021722460"></a><a name="p59021722460"></a>pthread_cond_signal</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p58024177158"><a name="p58024177158"></a><a name="p58024177158"></a>Unblocks a thread.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p179022244615"><a name="p179022244615"></a><a name="p179022244615"></a>N/A</p>
</td>
</tr>
<tr id="row13902423461"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p69022025464"><a name="p69022025464"></a><a name="p69022025464"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1190252134620"><a name="p1190252134620"></a><a name="p1190252134620"></a>pthread_cond_timedwait</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p158024175151"><a name="p158024175151"></a><a name="p158024175151"></a>Blocks the calling thread to wait for the condition set by <strong id="b258919128234"><a name="b258919128234"></a><a name="b258919128234"></a>pthread_con_signal()</strong> for a period of time specified by <strong id="b7341315122310"><a name="b7341315122310"></a><a name="b7341315122310"></a>ts</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p109020264613"><a name="p109020264613"></a><a name="p109020264613"></a>N/A</p>
</td>
</tr>
<tr id="row189022218464"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p09021228463"><a name="p09021228463"></a><a name="p09021228463"></a>pthread.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p3902324460"><a name="p3902324460"></a><a name="p3902324460"></a>pthread_cond_wait</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p1690262154612"><a name="p1690262154612"></a><a name="p1690262154612"></a>Blocks the calling thread to wait for the condition set by <strong id="b1273262914233"><a name="b1273262914233"></a><a name="b1273262914233"></a>pthread_con_signal()</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p19902122104611"><a name="p19902122104611"></a><a name="p19902122104611"></a>N/A</p>
</td>
</tr>
<tr id="row159027218467"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p990318212464"><a name="p990318212464"></a><a name="p990318212464"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p109039234617"><a name="p109039234617"></a><a name="p109039234617"></a>sem_destroy</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p195081328171710"><a name="p195081328171710"></a><a name="p195081328171710"></a>Destroys a specified anonymous semaphore that is no longer used.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p190318214460"><a name="p190318214460"></a><a name="p190318214460"></a>N/A</p>
</td>
</tr>
<tr id="row1690342194611"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1490318217469"><a name="p1490318217469"></a><a name="p1490318217469"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p0903162124610"><a name="p0903162124610"></a><a name="p0903162124610"></a>sem_getvalue</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p650892891712"><a name="p650892891712"></a><a name="p650892891712"></a>Obtains the count value of a specified semaphore.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p69036234614"><a name="p69036234614"></a><a name="p69036234614"></a>N/A</p>
</td>
</tr>
<tr id="row1490312214464"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p159031284618"><a name="p159031284618"></a><a name="p159031284618"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1790315254617"><a name="p1790315254617"></a><a name="p1790315254617"></a>sem_init</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p2508328121711"><a name="p2508328121711"></a><a name="p2508328121711"></a>Creates and initializes an anonymous semaphore.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p129038211463"><a name="p129038211463"></a><a name="p129038211463"></a>N/A</p>
</td>
</tr>
<tr id="row1490416211462"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p3904126469"><a name="p3904126469"></a><a name="p3904126469"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p090416220464"><a name="p090416220464"></a><a name="p090416220464"></a>sem_post</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p6508162813176"><a name="p6508162813176"></a><a name="p6508162813176"></a>Increments the semaphore count by 1.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p090414218463"><a name="p090414218463"></a><a name="p090414218463"></a>N/A</p>
</td>
</tr>
<tr id="row14904162164618"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p1590432194620"><a name="p1590432194620"></a><a name="p1590432194620"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p29041822467"><a name="p29041822467"></a><a name="p29041822467"></a>sem_timedwait</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p139049213468"><a name="p139049213468"></a><a name="p139049213468"></a>Obtains the semaphore, with a timeout period specified.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p690452114613"><a name="p690452114613"></a><a name="p690452114613"></a>N/A</p>
</td>
</tr>
<tr id="row390411211468"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p199049214612"><a name="p199049214612"></a><a name="p199049214612"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p1190413217467"><a name="p1190413217467"></a><a name="p1190413217467"></a>sem_trywait</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p18509102891714"><a name="p18509102891714"></a><a name="p18509102891714"></a>Attempts to obtain the semaphore.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p39048213469"><a name="p39048213469"></a><a name="p39048213469"></a>N/A</p>
</td>
</tr>
<tr id="row3905152174616"><td class="cellrowborder" valign="top" width="14.29%" headers="mcps1.2.5.1.1 "><p id="p690513215466"><a name="p690513215466"></a><a name="p690513215466"></a>semaphore.h</p>
</td>
<td class="cellrowborder" valign="top" width="28.57%" headers="mcps1.2.5.1.2 "><p id="p15905926462"><a name="p15905926462"></a><a name="p15905926462"></a>sem_wait</p>
</td>
<td class="cellrowborder" valign="top" width="22.45%" headers="mcps1.2.5.1.3 "><p id="p950912813172"><a name="p950912813172"></a><a name="p950912813172"></a>Obtains the semaphore.</p>
</td>
<td class="cellrowborder" valign="top" width="34.69%" headers="mcps1.2.5.1.4 "><p id="p109051725466"><a name="p109051725466"></a><a name="p109051725466"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

