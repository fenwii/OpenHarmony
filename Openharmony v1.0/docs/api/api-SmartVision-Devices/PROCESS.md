# PROCESS<a name="ZH-CN_TOPIC_0000001055387978"></a>

## **Overview**<a name="section216682500084824"></a>

Provides process- and thread-related structures and functions. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section755710590084824"></a>

## Files<a name="files"></a>

<a name="table767216095084824"></a>
<table><thead align="left"><tr id="row1953516044084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p681796236084824"><a name="p681796236084824"></a><a name="p681796236084824"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p628290204084824"><a name="p628290204084824"></a><a name="p628290204084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1342524941084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1176397014084824"><a name="p1176397014084824"></a><a name="p1176397014084824"></a><a href="pthread-h.md">pthread.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p471781434084824"><a name="p471781434084824"></a><a name="p471781434084824"></a>Provides process- and thread-related structures (providing fields such as thread attributes) and functions (including the functions for creating and destroying threads, and setting the thread detach state and blocking conditions). </p>
</td>
</tr>
<tr id="row481580836084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1185606752084824"><a name="p1185606752084824"></a><a name="p1185606752084824"></a><a href="sched-h.md">sched.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959677003084824"><a name="p959677003084824"></a><a name="p959677003084824"></a>Provides process- and thread-related structures and functions (for example, obtaining scheduling policies and parameters). </p>
</td>
</tr>
<tr id="row481699412084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1287281756084824"><a name="p1287281756084824"></a><a name="p1287281756084824"></a><a href="capability-h.md">capability.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115754317084824"><a name="p115754317084824"></a><a name="p115754317084824"></a>Provides functions and related data structures for obtaining and setting process capabilities. </p>
</td>
</tr>
<tr id="row1670751711084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1246042313084824"><a name="p1246042313084824"></a><a name="p1246042313084824"></a><a href="resource-h.md">resource.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531248025084824"><a name="p531248025084824"></a><a name="p531248025084824"></a>Declares process-related structures and functions. </p>
</td>
</tr>
<tr id="row2124941268084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p306503530084824"><a name="p306503530084824"></a><a name="p306503530084824"></a><a href="wait-h.md">wait.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486154153084824"><a name="p486154153084824"></a><a name="p486154153084824"></a>Provides process- and thread-related structures and functions (for example, waiting for child processes to end and reclaiming resources). </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table682346335084824"></a>
<table><thead align="left"><tr id="row817121446084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p219265005084824"><a name="p219265005084824"></a><a name="p219265005084824"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p832414515084824"><a name="p832414515084824"></a><a name="p832414515084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1059264485084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1279681808084824"><a name="p1279681808084824"></a><a name="p1279681808084824"></a><a href="sched_param.md">sched_param</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40186533084824"><a name="p40186533084824"></a><a name="p40186533084824"></a>Defines process scheduling parameters. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table822152528084824"></a>
<table><thead align="left"><tr id="row521616366084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1495287544084824"><a name="p1495287544084824"></a><a name="p1495287544084824"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1076191136084824"><a name="p1076191136084824"></a><a name="p1076191136084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1230895783084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1986378178084824"><a name="p1986378178084824"></a><a name="p1986378178084824"></a><a href="PROCESS.md#gae5d18438d4d20c8a2e42cd2500578d79">pthread_create</a> (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p818783949084824"><a name="p818783949084824"></a><a name="p818783949084824"></a>int&nbsp;</p>
<p id="p1231807798084824"><a name="p1231807798084824"></a><a name="p1231807798084824"></a>Creates a thread. </p>
</td>
</tr>
<tr id="row510723797084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1445691358084824"><a name="p1445691358084824"></a><a name="p1445691358084824"></a><a href="PROCESS.md#ga7c275c509c26566b6dd95a2de1668a2f">pthread_detach</a> (pthread_t thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2040410717084824"><a name="p2040410717084824"></a><a name="p2040410717084824"></a>int&nbsp;</p>
<p id="p1249908559084824"><a name="p1249908559084824"></a><a name="p1249908559084824"></a>Detaches a thread. </p>
</td>
</tr>
<tr id="row1392282775084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872571028084824"><a name="p1872571028084824"></a><a name="p1872571028084824"></a><a href="PROCESS.md#gaadfb4e5de5a20880c6a40d4e73ce2597">pthread_exit</a> (void *retval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093857391084824"><a name="p1093857391084824"></a><a name="p1093857391084824"></a>_Noreturn void&nbsp;</p>
<p id="p1470851100084824"><a name="p1470851100084824"></a><a name="p1470851100084824"></a>Terminates the calling thread. </p>
</td>
</tr>
<tr id="row1615924053084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p823437819084824"><a name="p823437819084824"></a><a name="p823437819084824"></a><a href="PROCESS.md#ga28a15bba47cab57cbc9f5dac9af99c8b">pthread_join</a> (pthread_t thread, void **retval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1860239003084824"><a name="p1860239003084824"></a><a name="p1860239003084824"></a>int&nbsp;</p>
<p id="p1066784514084824"><a name="p1066784514084824"></a><a name="p1066784514084824"></a>Waits for a thread to terminate. </p>
</td>
</tr>
<tr id="row411404738084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p169656249084824"><a name="p169656249084824"></a><a name="p169656249084824"></a><a href="PROCESS.md#ga4c4f5f3b4f8f45d9d897847d53b11aaa">pthread_self</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p349733716084824"><a name="p349733716084824"></a><a name="p349733716084824"></a>pthread_t&nbsp;</p>
<p id="p1094342581084824"><a name="p1094342581084824"></a><a name="p1094342581084824"></a>Obtains the ID of the calling thread. </p>
</td>
</tr>
<tr id="row2042431845084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635007973084824"><a name="p635007973084824"></a><a name="p635007973084824"></a><a href="PROCESS.md#ga98ec817164a6641eda2341de473b659d">pthread_equal</a> (pthread_t t1, pthread_t t2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1856656988084824"><a name="p1856656988084824"></a><a name="p1856656988084824"></a>int&nbsp;</p>
<p id="p1962174415084824"><a name="p1962174415084824"></a><a name="p1962174415084824"></a>Compares whether two thread IDs are equal. </p>
</td>
</tr>
<tr id="row1863114397084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1017902519084824"><a name="p1017902519084824"></a><a name="p1017902519084824"></a><a href="PROCESS.md#ga37075410fbbaad7ee93c95375fc86e0e">pthread_setcancelstate</a> (int state, int *oldstate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791017095084824"><a name="p791017095084824"></a><a name="p791017095084824"></a>int&nbsp;</p>
<p id="p1453388641084824"><a name="p1453388641084824"></a><a name="p1453388641084824"></a>Sets the cancelability state for the calling thread. </p>
</td>
</tr>
<tr id="row1382105325084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2137046438084824"><a name="p2137046438084824"></a><a name="p2137046438084824"></a><a href="PROCESS.md#gaab579bcfcf0662a0c1e35fd82162e61d">pthread_setcanceltype</a> (int type, int *oldtype)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846893514084824"><a name="p846893514084824"></a><a name="p846893514084824"></a>int&nbsp;</p>
<p id="p1294978354084824"><a name="p1294978354084824"></a><a name="p1294978354084824"></a>Sets the cancelability type for the calling thread. </p>
</td>
</tr>
<tr id="row2088051828084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1306855307084824"><a name="p1306855307084824"></a><a name="p1306855307084824"></a><a href="PROCESS.md#gaf1c95282ab2bea25f0888a19652cd41f">pthread_testcancel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1102884148084824"><a name="p1102884148084824"></a><a name="p1102884148084824"></a>void&nbsp;</p>
<p id="p39981116084824"><a name="p39981116084824"></a><a name="p39981116084824"></a>Requests delivery of any pending cancellation request. </p>
</td>
</tr>
<tr id="row1333227032084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2136645967084824"><a name="p2136645967084824"></a><a name="p2136645967084824"></a><a href="PROCESS.md#ga9e77a80c073787bf9a593e9c619dce27">pthread_cancel</a> (pthread_t thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679871657084824"><a name="p679871657084824"></a><a name="p679871657084824"></a>int&nbsp;</p>
<p id="p251591882084824"><a name="p251591882084824"></a><a name="p251591882084824"></a>Sends a cancellation request to a thread. </p>
</td>
</tr>
<tr id="row1087584235084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p876370210084824"><a name="p876370210084824"></a><a name="p876370210084824"></a><a href="PROCESS.md#ga5aafacc071cdfafd0eb992004dee3e62">pthread_kill</a> (pthread_t thread, int sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1045741938084824"><a name="p1045741938084824"></a><a name="p1045741938084824"></a>int&nbsp;</p>
<p id="p1605226618084824"><a name="p1605226618084824"></a><a name="p1605226618084824"></a>Sends a signal to a thread. </p>
</td>
</tr>
<tr id="row636687686084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275899528084824"><a name="p275899528084824"></a><a name="p275899528084824"></a><a href="PROCESS.md#gaae9850b3759769c748727e171c4c6e61">pthread_getschedparam</a> (pthread_t thread, int *policy, struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782725349084824"><a name="p782725349084824"></a><a name="p782725349084824"></a>int&nbsp;</p>
<p id="p1781332802084824"><a name="p1781332802084824"></a><a name="p1781332802084824"></a>Obtains the scheduling policy and parameters of a thread. </p>
</td>
</tr>
<tr id="row471698343084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p316846844084824"><a name="p316846844084824"></a><a name="p316846844084824"></a><a href="PROCESS.md#ga14f50e1f5d815c90f1f4225eca5d3a8c">pthread_setschedparam</a> (pthread_t thread, int policy, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417161703084824"><a name="p417161703084824"></a><a name="p417161703084824"></a>int&nbsp;</p>
<p id="p1873739526084824"><a name="p1873739526084824"></a><a name="p1873739526084824"></a>Sets a scheduling policy and parameters for a thread. </p>
</td>
</tr>
<tr id="row544840724084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2021926316084824"><a name="p2021926316084824"></a><a name="p2021926316084824"></a><a href="PROCESS.md#ga7a23cbcfc21a4e3edf531ed65f022370">pthread_setschedprio</a> (pthread_t thread, int prio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206961812084824"><a name="p206961812084824"></a><a name="p206961812084824"></a>int&nbsp;</p>
<p id="p1563878324084824"><a name="p1563878324084824"></a><a name="p1563878324084824"></a>Sets a static scheduling priority for a thread. </p>
</td>
</tr>
<tr id="row1472684860084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652218614084824"><a name="p1652218614084824"></a><a name="p1652218614084824"></a><a href="PROCESS.md#ga196103ac97710dad7a93fd6c188cc999">pthread_once</a> (pthread_once_t *once_control, void(*init_routine)(void))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p784727275084824"><a name="p784727275084824"></a><a name="p784727275084824"></a>int&nbsp;</p>
<p id="p1308983946084824"><a name="p1308983946084824"></a><a name="p1308983946084824"></a>Enables the initialization function to be called only once. </p>
</td>
</tr>
<tr id="row852312790084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p239938724084824"><a name="p239938724084824"></a><a name="p239938724084824"></a><a href="PROCESS.md#gadd99221596e95a55f70c59c1c712bbde">pthread_mutex_init</a> (pthread_mutex_t *__restrict m, const pthread_mutexattr_t *__restrict a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764123098084824"><a name="p764123098084824"></a><a name="p764123098084824"></a>int&nbsp;</p>
<p id="p37708256084824"><a name="p37708256084824"></a><a name="p37708256084824"></a>Initializes a mutex. </p>
</td>
</tr>
<tr id="row1098115412084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1224703206084824"><a name="p1224703206084824"></a><a name="p1224703206084824"></a><a href="PROCESS.md#gafd70d6f2c50e22b996c926fb9d6ad291">pthread_mutex_lock</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1073520173084824"><a name="p1073520173084824"></a><a name="p1073520173084824"></a>int&nbsp;</p>
<p id="p1494686068084824"><a name="p1494686068084824"></a><a name="p1494686068084824"></a>Locks a mutex. </p>
</td>
</tr>
<tr id="row2120740207084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841280862084824"><a name="p841280862084824"></a><a name="p841280862084824"></a><a href="PROCESS.md#ga02a3c64dac70730e226c31c0e7dbb45c">pthread_mutex_unlock</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p161407185084824"><a name="p161407185084824"></a><a name="p161407185084824"></a>int&nbsp;</p>
<p id="p446801288084824"><a name="p446801288084824"></a><a name="p446801288084824"></a>Unlocks a mutex. </p>
</td>
</tr>
<tr id="row1211540295084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1499562748084824"><a name="p1499562748084824"></a><a name="p1499562748084824"></a><a href="PROCESS.md#gacc1ccbaf3d76572da85a8030bba1ede4">pthread_mutex_trylock</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1571014668084824"><a name="p1571014668084824"></a><a name="p1571014668084824"></a>int&nbsp;</p>
<p id="p1338230033084824"><a name="p1338230033084824"></a><a name="p1338230033084824"></a>Attempts to lock a mutex. </p>
</td>
</tr>
<tr id="row716639129084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977665537084824"><a name="p977665537084824"></a><a name="p977665537084824"></a><a href="PROCESS.md#gabc6a044b418e942b91121b1babb61708">pthread_mutex_timedlock</a> (pthread_mutex_t *__restrict m, const struct <a href="timespec.md">timespec</a> *__restrict at)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859596301084824"><a name="p859596301084824"></a><a name="p859596301084824"></a>int&nbsp;</p>
<p id="p875479066084824"><a name="p875479066084824"></a><a name="p875479066084824"></a>Blocks the calling thread to lock a mutex. </p>
</td>
</tr>
<tr id="row1845567629084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488331416084824"><a name="p488331416084824"></a><a name="p488331416084824"></a><a href="PROCESS.md#gaf89d9cfa300f33b46720a96eac83d175">pthread_mutex_destroy</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p496645906084824"><a name="p496645906084824"></a><a name="p496645906084824"></a>int&nbsp;</p>
<p id="p1030009182084824"><a name="p1030009182084824"></a><a name="p1030009182084824"></a>Destroys a mutex. </p>
</td>
</tr>
<tr id="row839400019084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p10986733084824"><a name="p10986733084824"></a><a name="p10986733084824"></a><a href="PROCESS.md#gabdf02ed57b055f1920991e96e7d67043">pthread_cond_init</a> (pthread_cond_t *__restrict c, const pthread_condattr_t *__restrict a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p52002185084824"><a name="p52002185084824"></a><a name="p52002185084824"></a>int&nbsp;</p>
<p id="p628117143084824"><a name="p628117143084824"></a><a name="p628117143084824"></a>Initializes a condition variable. </p>
</td>
</tr>
<tr id="row849010609084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479462506084824"><a name="p479462506084824"></a><a name="p479462506084824"></a><a href="PROCESS.md#ga7f2a7328ee3a7743686adcd2d51771c4">pthread_cond_destroy</a> (pthread_cond_t *c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1134691727084824"><a name="p1134691727084824"></a><a name="p1134691727084824"></a>int&nbsp;</p>
<p id="p105793999084824"><a name="p105793999084824"></a><a name="p105793999084824"></a>Destroys a condition variable. </p>
</td>
</tr>
<tr id="row1341534618084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1707813496084824"><a name="p1707813496084824"></a><a name="p1707813496084824"></a><a href="PROCESS.md#gaea601b8ce596a5c54fb12758c56b10a1">pthread_cond_wait</a> (pthread_cond_t *__restrict c, pthread_mutex_t *__restrict m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1118658318084824"><a name="p1118658318084824"></a><a name="p1118658318084824"></a>int&nbsp;</p>
<p id="p1950630600084824"><a name="p1950630600084824"></a><a name="p1950630600084824"></a>Blocks the calling thread to wait for the condition set by <strong id="b1641448758084824"><a name="b1641448758084824"></a><a name="b1641448758084824"></a>pthread_con_signal()</strong>. </p>
</td>
</tr>
<tr id="row1445521592084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331714822084824"><a name="p331714822084824"></a><a name="p331714822084824"></a><a href="PROCESS.md#ga506c0350d597721ab24bba7129e8e0df">pthread_cond_timedwait</a> (pthread_cond_t *__restrict c, pthread_mutex_t *__restrict m, const struct <a href="timespec.md">timespec</a> *__restrict ts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p270582322084824"><a name="p270582322084824"></a><a name="p270582322084824"></a>int&nbsp;</p>
<p id="p1050138378084824"><a name="p1050138378084824"></a><a name="p1050138378084824"></a>Blocks the calling thread to wait for the condition set by <strong id="b2136715367084824"><a name="b2136715367084824"></a><a name="b2136715367084824"></a>pthread_con_signal()</strong> for a period of time specified by <strong id="b1455607764084824"><a name="b1455607764084824"></a><a name="b1455607764084824"></a>ts</strong>. </p>
</td>
</tr>
<tr id="row158798013084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032947575084824"><a name="p2032947575084824"></a><a name="p2032947575084824"></a><a href="PROCESS.md#ga1c1ac7c8faaf8ad63e12bc3717f430f3">pthread_cond_broadcast</a> (pthread_cond_t *c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p208511296084824"><a name="p208511296084824"></a><a name="p208511296084824"></a>int&nbsp;</p>
<p id="p1945329112084824"><a name="p1945329112084824"></a><a name="p1945329112084824"></a>Unblocks all threads that are currently blocked on the condition variable <strong id="b341640724084824"><a name="b341640724084824"></a><a name="b341640724084824"></a>cond</strong>. </p>
</td>
</tr>
<tr id="row2087017518084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p619893845084824"><a name="p619893845084824"></a><a name="p619893845084824"></a><a href="PROCESS.md#ga9b0f2c7dead8c628e081d76c86a1addc">pthread_cond_signal</a> (pthread_cond_t *c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1337972878084824"><a name="p1337972878084824"></a><a name="p1337972878084824"></a>int&nbsp;</p>
<p id="p1794206867084824"><a name="p1794206867084824"></a><a name="p1794206867084824"></a>Unblocks a thread. </p>
</td>
</tr>
<tr id="row1553493264084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p499213701084824"><a name="p499213701084824"></a><a name="p499213701084824"></a><a href="PROCESS.md#ga1cf4bc49696c1a30db31219aef994401">pthread_rwlock_init</a> (pthread_rwlock_t *__restrict rw, const pthread_rwlockattr_t *__restrict a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1647297827084824"><a name="p1647297827084824"></a><a name="p1647297827084824"></a>int&nbsp;</p>
<p id="p1615038139084824"><a name="p1615038139084824"></a><a name="p1615038139084824"></a>Initializes a read-write lock. </p>
</td>
</tr>
<tr id="row140098169084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1880949370084824"><a name="p1880949370084824"></a><a name="p1880949370084824"></a><a href="PROCESS.md#gaa106bb55bdd0e120519d5412823f8b29">pthread_rwlock_destroy</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p578122098084824"><a name="p578122098084824"></a><a name="p578122098084824"></a>int&nbsp;</p>
<p id="p1127655805084824"><a name="p1127655805084824"></a><a name="p1127655805084824"></a>Destroys a read-write lock. </p>
</td>
</tr>
<tr id="row168159213084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382281616084824"><a name="p1382281616084824"></a><a name="p1382281616084824"></a><a href="PROCESS.md#ga6153aca32112735053e6cc4a2a290feb">pthread_rwlock_rdlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p664288869084824"><a name="p664288869084824"></a><a name="p664288869084824"></a>int&nbsp;</p>
<p id="p1522941739084824"><a name="p1522941739084824"></a><a name="p1522941739084824"></a>Applies a read lock to a read-write lock. </p>
</td>
</tr>
<tr id="row730975010084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1537751739084824"><a name="p1537751739084824"></a><a name="p1537751739084824"></a><a href="PROCESS.md#ga3ba2170f06184d12543c4a5b78715fa7">pthread_rwlock_tryrdlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1929536504084824"><a name="p1929536504084824"></a><a name="p1929536504084824"></a>int&nbsp;</p>
<p id="p1731386957084824"><a name="p1731386957084824"></a><a name="p1731386957084824"></a>Attempts to apply a read lock to a read-write lock. </p>
</td>
</tr>
<tr id="row342809242084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1523833757084824"><a name="p1523833757084824"></a><a name="p1523833757084824"></a><a href="PROCESS.md#ga8edbe14731fd79a80f72384334266715">pthread_rwlock_timedrdlock</a> (pthread_rwlock_t *__restrict rw, const struct <a href="timespec.md">timespec</a> *__restrict at)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400994854084824"><a name="p400994854084824"></a><a name="p400994854084824"></a>int&nbsp;</p>
<p id="p1589134742084824"><a name="p1589134742084824"></a><a name="p1589134742084824"></a>Blocks the calling thread to lock a read-write lock for reading. </p>
</td>
</tr>
<tr id="row67630817084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1163685423084824"><a name="p1163685423084824"></a><a name="p1163685423084824"></a><a href="PROCESS.md#gaf2ca5563676ae3ac35d3bc7b3547e7f7">pthread_rwlock_wrlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206200851084824"><a name="p1206200851084824"></a><a name="p1206200851084824"></a>int&nbsp;</p>
<p id="p1211511474084824"><a name="p1211511474084824"></a><a name="p1211511474084824"></a>Applies a write lock to a read-write lock. </p>
</td>
</tr>
<tr id="row1730444579084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998872737084824"><a name="p1998872737084824"></a><a name="p1998872737084824"></a><a href="PROCESS.md#ga2b5044e2da304ae9666fdd4e05479905">pthread_rwlock_trywrlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327783417084824"><a name="p1327783417084824"></a><a name="p1327783417084824"></a>int&nbsp;</p>
<p id="p905219992084824"><a name="p905219992084824"></a><a name="p905219992084824"></a>Attempts to apply a write lock to a read-write lock. </p>
</td>
</tr>
<tr id="row1922060356084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2041305664084824"><a name="p2041305664084824"></a><a name="p2041305664084824"></a><a href="PROCESS.md#ga3fb8fb33e16653c5ad7b7f092959738e">pthread_rwlock_timedwrlock</a> (pthread_rwlock_t *__restrict rw, const struct <a href="timespec.md">timespec</a> *__restrict at)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1210463946084824"><a name="p1210463946084824"></a><a name="p1210463946084824"></a>int&nbsp;</p>
<p id="p2005342750084824"><a name="p2005342750084824"></a><a name="p2005342750084824"></a>Blocks the calling thread to lock a read-write lock for writing. </p>
</td>
</tr>
<tr id="row1304647113084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379845857084824"><a name="p1379845857084824"></a><a name="p1379845857084824"></a><a href="PROCESS.md#gaffd8a19e83fc87d865d103d6fbce8c4f">pthread_rwlock_unlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p173869996084824"><a name="p173869996084824"></a><a name="p173869996084824"></a>int&nbsp;</p>
<p id="p1210636188084824"><a name="p1210636188084824"></a><a name="p1210636188084824"></a>Unlocks a read-write lock. </p>
</td>
</tr>
<tr id="row1123904821084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2020518800084824"><a name="p2020518800084824"></a><a name="p2020518800084824"></a><a href="PROCESS.md#ga665a56a7bed60c8eaa6c28af40d13cd4">pthread_spin_init</a> (pthread_spinlock_t *s, int shared)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124853382084824"><a name="p124853382084824"></a><a name="p124853382084824"></a>int&nbsp;</p>
<p id="p2063485080084824"><a name="p2063485080084824"></a><a name="p2063485080084824"></a>Initializes a spin lock. </p>
</td>
</tr>
<tr id="row1807394783084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895671272084824"><a name="p895671272084824"></a><a name="p895671272084824"></a><a href="PROCESS.md#ga822c2ff425ddad4c25b6a6092c6effff">pthread_spin_destroy</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p753139427084824"><a name="p753139427084824"></a><a name="p753139427084824"></a>int&nbsp;</p>
<p id="p1409930049084824"><a name="p1409930049084824"></a><a name="p1409930049084824"></a>Destroys a spin lock. </p>
</td>
</tr>
<tr id="row2145337131084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1795576077084824"><a name="p1795576077084824"></a><a name="p1795576077084824"></a><a href="PROCESS.md#ga62cfd14d1f937a6e8f966e3a331bcf94">pthread_spin_lock</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481359690084824"><a name="p1481359690084824"></a><a name="p1481359690084824"></a>int&nbsp;</p>
<p id="p225106359084824"><a name="p225106359084824"></a><a name="p225106359084824"></a>Locks a spin lock. </p>
</td>
</tr>
<tr id="row1374750544084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758675269084824"><a name="p758675269084824"></a><a name="p758675269084824"></a><a href="PROCESS.md#ga084834fa2d06f173f086ce23ec1ea5d9">pthread_spin_trylock</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085169604084824"><a name="p1085169604084824"></a><a name="p1085169604084824"></a>int&nbsp;</p>
<p id="p2099664152084824"><a name="p2099664152084824"></a><a name="p2099664152084824"></a>Attempts to lock a spin lock. </p>
</td>
</tr>
<tr id="row1506580405084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1440938255084824"><a name="p1440938255084824"></a><a name="p1440938255084824"></a><a href="PROCESS.md#ga3fe246007a85cee9d5f7af9b7d592b54">pthread_spin_unlock</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844533316084824"><a name="p844533316084824"></a><a name="p844533316084824"></a>int&nbsp;</p>
<p id="p1882084734084824"><a name="p1882084734084824"></a><a name="p1882084734084824"></a>Unlocks a spin lock. </p>
</td>
</tr>
<tr id="row1874532645084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1266667315084824"><a name="p1266667315084824"></a><a name="p1266667315084824"></a><a href="PROCESS.md#ga4a324cd758cae702213ea41882f4cf41">pthread_barrier_init</a> (pthread_barrier_t *__restrict b, const pthread_barrierattr_t *__restrict a, unsigned count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p718038033084824"><a name="p718038033084824"></a><a name="p718038033084824"></a>int&nbsp;</p>
<p id="p618647721084824"><a name="p618647721084824"></a><a name="p618647721084824"></a>Initializes a barrier. </p>
</td>
</tr>
<tr id="row424249851084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1562299760084824"><a name="p1562299760084824"></a><a name="p1562299760084824"></a><a href="PROCESS.md#gab05ae13769e61dea9c53ca7894743c8f">pthread_barrier_destroy</a> (pthread_barrier_t *b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2127495834084824"><a name="p2127495834084824"></a><a name="p2127495834084824"></a>int&nbsp;</p>
<p id="p710303237084824"><a name="p710303237084824"></a><a name="p710303237084824"></a>Destroys a barrier. </p>
</td>
</tr>
<tr id="row1943842238084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p968931412084824"><a name="p968931412084824"></a><a name="p968931412084824"></a><a href="PROCESS.md#gaf786372165ba080986ae4143928c5436">pthread_barrier_wait</a> (pthread_barrier_t *b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p662609854084824"><a name="p662609854084824"></a><a name="p662609854084824"></a>int&nbsp;</p>
<p id="p272847710084824"><a name="p272847710084824"></a><a name="p272847710084824"></a>Synchronizes participating threads at a barrier. </p>
</td>
</tr>
<tr id="row266551814084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607212120084824"><a name="p607212120084824"></a><a name="p607212120084824"></a><a href="PROCESS.md#gaf4b7ced8ecff505380fe8216244a3764">pthread_key_create</a> (pthread_key_t *key, void(*destructor)(void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1332131757084824"><a name="p1332131757084824"></a><a name="p1332131757084824"></a>int&nbsp;</p>
<p id="p1195936341084824"><a name="p1195936341084824"></a><a name="p1195936341084824"></a>Creates a key for thread data. </p>
</td>
</tr>
<tr id="row2109171082084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1374727198084824"><a name="p1374727198084824"></a><a name="p1374727198084824"></a><a href="PROCESS.md#gaee96306dc79294927ee840bb4de2244b">pthread_key_delete</a> (pthread_key_t key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550190821084824"><a name="p1550190821084824"></a><a name="p1550190821084824"></a>int&nbsp;</p>
<p id="p1935436837084824"><a name="p1935436837084824"></a><a name="p1935436837084824"></a>Deletes a key for thread data. </p>
</td>
</tr>
<tr id="row1552370303084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p311096652084824"><a name="p311096652084824"></a><a name="p311096652084824"></a><a href="PROCESS.md#ga31469375891078185bda93f0e4411a2c">pthread_getspecific</a> (pthread_key_t key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703836574084824"><a name="p1703836574084824"></a><a name="p1703836574084824"></a>void *&nbsp;</p>
<p id="p252287811084824"><a name="p252287811084824"></a><a name="p252287811084824"></a>Obtains specific thread data. </p>
</td>
</tr>
<tr id="row1722563793084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583811376084824"><a name="p583811376084824"></a><a name="p583811376084824"></a><a href="PROCESS.md#ga2187333dd46ce08d9d2e044f79fad705">pthread_setspecific</a> (pthread_key_t key, const void *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746901691084824"><a name="p746901691084824"></a><a name="p746901691084824"></a>int&nbsp;</p>
<p id="p839114254084824"><a name="p839114254084824"></a><a name="p839114254084824"></a>Sets specific thread data. </p>
</td>
</tr>
<tr id="row1495788129084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629490717084824"><a name="p1629490717084824"></a><a name="p1629490717084824"></a><a href="PROCESS.md#ga0b85ebb1e3aac081a4c0a5e85ae3cbe9">pthread_attr_init</a> (pthread_attr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p433408670084824"><a name="p433408670084824"></a><a name="p433408670084824"></a>int&nbsp;</p>
<p id="p1763973434084824"><a name="p1763973434084824"></a><a name="p1763973434084824"></a>Initializes a thread attribute object. </p>
</td>
</tr>
<tr id="row1209261207084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829471784084824"><a name="p1829471784084824"></a><a name="p1829471784084824"></a><a href="PROCESS.md#ga4bcdbf47c17c7dcc51e9f05f5cb56d81">pthread_attr_destroy</a> (pthread_attr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2136122412084824"><a name="p2136122412084824"></a><a name="p2136122412084824"></a>int&nbsp;</p>
<p id="p75389362084824"><a name="p75389362084824"></a><a name="p75389362084824"></a>Destroys a thread attribute object. </p>
</td>
</tr>
<tr id="row2030471846084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730763676084824"><a name="p730763676084824"></a><a name="p730763676084824"></a><a href="PROCESS.md#gaa8b692ecc3880fdd49a4d423ba1ce91e">pthread_attr_getguardsize</a> (const pthread_attr_t *attr, size_t *guardsize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91244538084824"><a name="p91244538084824"></a><a name="p91244538084824"></a>int&nbsp;</p>
<p id="p1495622493084824"><a name="p1495622493084824"></a><a name="p1495622493084824"></a>Obtains the guard size of a thread attribute object. </p>
</td>
</tr>
<tr id="row1477910872084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2126398859084824"><a name="p2126398859084824"></a><a name="p2126398859084824"></a><a href="PROCESS.md#ga532b31c11a9d87663053c5342400758c">pthread_attr_setguardsize</a> (pthread_attr_t *attr, size_t guardsize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122674873084824"><a name="p1122674873084824"></a><a name="p1122674873084824"></a>int&nbsp;</p>
<p id="p1644030466084824"><a name="p1644030466084824"></a><a name="p1644030466084824"></a>Sets the guard size for a thread attribute object. </p>
</td>
</tr>
<tr id="row1234973428084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997437033084824"><a name="p1997437033084824"></a><a name="p1997437033084824"></a><a href="PROCESS.md#gae23600d4670359ab12bfba20db2c9a37">pthread_attr_getstacksize</a> (const pthread_attr_t *attr, size_t *stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p438312741084824"><a name="p438312741084824"></a><a name="p438312741084824"></a>int&nbsp;</p>
<p id="p1328450445084824"><a name="p1328450445084824"></a><a name="p1328450445084824"></a>Obtains the stack size of a thread attribute object. </p>
</td>
</tr>
<tr id="row1475972926084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1258869279084824"><a name="p1258869279084824"></a><a name="p1258869279084824"></a><a href="PROCESS.md#ga812a9a455ae2ef2bb0dca4fff201a281">pthread_attr_setstacksize</a> (pthread_attr_t *attr, size_t stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p744594020084824"><a name="p744594020084824"></a><a name="p744594020084824"></a>int&nbsp;</p>
<p id="p1476085572084824"><a name="p1476085572084824"></a><a name="p1476085572084824"></a>Sets the stack size for a thread attribute object. </p>
</td>
</tr>
<tr id="row2101660487084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p998909172084824"><a name="p998909172084824"></a><a name="p998909172084824"></a><a href="PROCESS.md#ga391c34da42e68ddd24f5ee0c070d5c4f">pthread_attr_getdetachstate</a> (const pthread_attr_t *attr, int *detachstate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p10660291084824"><a name="p10660291084824"></a><a name="p10660291084824"></a>int&nbsp;</p>
<p id="p649634962084824"><a name="p649634962084824"></a><a name="p649634962084824"></a>Obtains the detach state of a thread attribute object. </p>
</td>
</tr>
<tr id="row1370742037084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119837030084824"><a name="p1119837030084824"></a><a name="p1119837030084824"></a><a href="PROCESS.md#gae6ee78c307d8467b34a9b0c330993a54">pthread_attr_setdetachstate</a> (pthread_attr_t *attr, int detachstate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080286277084824"><a name="p1080286277084824"></a><a name="p1080286277084824"></a>int&nbsp;</p>
<p id="p747228174084824"><a name="p747228174084824"></a><a name="p747228174084824"></a>Sets the detach state for a thread attribute object. </p>
</td>
</tr>
<tr id="row1810891776084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671061706084824"><a name="p671061706084824"></a><a name="p671061706084824"></a><a href="PROCESS.md#gaec19ad460995a9fe8aeb4eaf2bb1ed1d">pthread_attr_getstack</a> (const pthread_attr_t *attr, void **stackaddr, size_t *stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630013778084824"><a name="p1630013778084824"></a><a name="p1630013778084824"></a>int&nbsp;</p>
<p id="p1279517640084824"><a name="p1279517640084824"></a><a name="p1279517640084824"></a>Obtains stack attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row1627830948084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p918659317084824"><a name="p918659317084824"></a><a name="p918659317084824"></a><a href="PROCESS.md#ga94ede89b99a3a4fa17e516d30aaf3409">pthread_attr_setstack</a> (pthread_attr_t *attr, void *stackaddr, size_t stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1577356896084824"><a name="p1577356896084824"></a><a name="p1577356896084824"></a>int&nbsp;</p>
<p id="p1216159704084824"><a name="p1216159704084824"></a><a name="p1216159704084824"></a>Sets stack attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row1839681327084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p475194060084824"><a name="p475194060084824"></a><a name="p475194060084824"></a><a href="PROCESS.md#ga8a53d8e8b40b2332581ee219c5e4c468">pthread_attr_getscope</a> (const pthread_attr_t *arrt, int *scope)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p851334852084824"><a name="p851334852084824"></a><a name="p851334852084824"></a>int&nbsp;</p>
<p id="p1384876804084824"><a name="p1384876804084824"></a><a name="p1384876804084824"></a>Obtains contention scope attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row505992683084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1033303329084824"><a name="p1033303329084824"></a><a name="p1033303329084824"></a><a href="PROCESS.md#ga9f90a3707a1797591661272928c152f9">pthread_attr_setscope</a> (pthread_attr_t *arrt, int scope)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901058125084824"><a name="p1901058125084824"></a><a name="p1901058125084824"></a>int&nbsp;</p>
<p id="p1124516592084824"><a name="p1124516592084824"></a><a name="p1124516592084824"></a>Sets contention scope attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row1353118307084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1314033347084824"><a name="p1314033347084824"></a><a name="p1314033347084824"></a><a href="PROCESS.md#gaec4d8127833d1a573aa82539f898a8ed">pthread_attr_getschedpolicy</a> (const pthread_attr_t *attr, int *schedpolicy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354190128084824"><a name="p1354190128084824"></a><a name="p1354190128084824"></a>int&nbsp;</p>
<p id="p91885378084824"><a name="p91885378084824"></a><a name="p91885378084824"></a>Obtains scheduling policy attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row866776703084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236122631084824"><a name="p236122631084824"></a><a name="p236122631084824"></a><a href="PROCESS.md#gab6cb2eb73f04abf328b2f39777c35dca">pthread_attr_setschedpolicy</a> (pthread_attr_t *attr, int schedpolicy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1658647610084824"><a name="p1658647610084824"></a><a name="p1658647610084824"></a>int&nbsp;</p>
<p id="p377005714084824"><a name="p377005714084824"></a><a name="p377005714084824"></a>Sets scheduling policy attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row869576005084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21075794084824"><a name="p21075794084824"></a><a name="p21075794084824"></a><a href="PROCESS.md#gafd3d272d702481044f8a8cd253fd9b47">pthread_attr_getschedparam</a> (const pthread_attr_t *attr, struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59555893084824"><a name="p59555893084824"></a><a name="p59555893084824"></a>int&nbsp;</p>
<p id="p2124720870084824"><a name="p2124720870084824"></a><a name="p2124720870084824"></a>Obtains scheduling parameter attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row2089430174084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p154079084824"><a name="p154079084824"></a><a name="p154079084824"></a><a href="PROCESS.md#ga579e6529f0ce482312a5e77ac61cb4d5">pthread_attr_setschedparam</a> (pthread_attr_t *attr, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1867327269084824"><a name="p1867327269084824"></a><a name="p1867327269084824"></a>int&nbsp;</p>
<p id="p1751717309084824"><a name="p1751717309084824"></a><a name="p1751717309084824"></a>Sets scheduling parameter attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row1842433567084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870069745084824"><a name="p1870069745084824"></a><a name="p1870069745084824"></a><a href="PROCESS.md#ga79a77b688c30213e5e52e6be178cde4e">pthread_attr_getinheritsched</a> (const pthread_attr_t *attr, int *inheritsched)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1267293066084824"><a name="p1267293066084824"></a><a name="p1267293066084824"></a>int&nbsp;</p>
<p id="p459985925084824"><a name="p459985925084824"></a><a name="p459985925084824"></a>Obtains inherit scheduler attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row2063022663084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170962736084824"><a name="p170962736084824"></a><a name="p170962736084824"></a><a href="PROCESS.md#gad437fe8caa3ef9f0cb7d69f6f6479df9">pthread_attr_setinheritsched</a> (pthread_attr_t *attr, int inheritsched)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1176732875084824"><a name="p1176732875084824"></a><a name="p1176732875084824"></a>int&nbsp;</p>
<p id="p321151403084824"><a name="p321151403084824"></a><a name="p321151403084824"></a>Sets inherit scheduler attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row1237894379084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p730737539084824"><a name="p730737539084824"></a><a name="p730737539084824"></a><a href="PROCESS.md#ga2321aabf58224b06021185708d0f9658">pthread_mutexattr_destroy</a> (pthread_mutexattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p37452427084824"><a name="p37452427084824"></a><a name="p37452427084824"></a>int&nbsp;</p>
<p id="p393608011084824"><a name="p393608011084824"></a><a name="p393608011084824"></a>Destroys a mutex attribute object. </p>
</td>
</tr>
<tr id="row1067738838084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1168248642084824"><a name="p1168248642084824"></a><a name="p1168248642084824"></a><a href="PROCESS.md#ga4789e2d3ada7aab2af1458bfec53ee3c">pthread_mutexattr_gettype</a> (const pthread_mutexattr_t *__restrict attr, int *__restrict type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1811861962084824"><a name="p1811861962084824"></a><a name="p1811861962084824"></a>int&nbsp;</p>
<p id="p1061939526084824"><a name="p1061939526084824"></a><a name="p1061939526084824"></a>Obtains the mutex type attribute. </p>
</td>
</tr>
<tr id="row1645543980084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498888106084824"><a name="p498888106084824"></a><a name="p498888106084824"></a><a href="PROCESS.md#gaf98f6b6c483077a39d1400b1de1577b8">pthread_mutexattr_init</a> (pthread_mutexattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1659795991084824"><a name="p1659795991084824"></a><a name="p1659795991084824"></a>int&nbsp;</p>
<p id="p945596378084824"><a name="p945596378084824"></a><a name="p945596378084824"></a>Initializes a mutex attribute object. </p>
</td>
</tr>
<tr id="row672797319084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274001967084824"><a name="p1274001967084824"></a><a name="p1274001967084824"></a><a href="PROCESS.md#ga8387c80e660e9426f801ac0217ecfae5">pthread_mutexattr_settype</a> (pthread_mutexattr_t *attr, int type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628524102084824"><a name="p1628524102084824"></a><a name="p1628524102084824"></a>int&nbsp;</p>
<p id="p1023271238084824"><a name="p1023271238084824"></a><a name="p1023271238084824"></a>Sets the mutex type attribute. </p>
</td>
</tr>
<tr id="row1471369283084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1466629561084824"><a name="p1466629561084824"></a><a name="p1466629561084824"></a><a href="PROCESS.md#ga487a919ab54fd47c8464507031957df0">pthread_condattr_init</a> (pthread_condattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1042467549084824"><a name="p1042467549084824"></a><a name="p1042467549084824"></a>int&nbsp;</p>
<p id="p1136956675084824"><a name="p1136956675084824"></a><a name="p1136956675084824"></a>Initializes a condition variable attribute object. </p>
</td>
</tr>
<tr id="row892152193084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2028678170084824"><a name="p2028678170084824"></a><a name="p2028678170084824"></a><a href="PROCESS.md#ga8ab009937339c899a5197eea2e48e6a1">pthread_condattr_destroy</a> (pthread_condattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p920667794084824"><a name="p920667794084824"></a><a name="p920667794084824"></a>int&nbsp;</p>
<p id="p2138767259084824"><a name="p2138767259084824"></a><a name="p2138767259084824"></a>Destroys a condition variable attribute object. </p>
</td>
</tr>
<tr id="row2050731864084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1380396067084824"><a name="p1380396067084824"></a><a name="p1380396067084824"></a><a href="PROCESS.md#gaaf7ac0f85233c0effaf850a9c65b6d68">pthread_condattr_setclock</a> (pthread_condattr_t *a, clockid_t clk)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p877714594084824"><a name="p877714594084824"></a><a name="p877714594084824"></a>int&nbsp;</p>
<p id="p1307321257084824"><a name="p1307321257084824"></a><a name="p1307321257084824"></a>Sets a clock for a condition variable attribute object. </p>
</td>
</tr>
<tr id="row469939326084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1189954864084824"><a name="p1189954864084824"></a><a name="p1189954864084824"></a><a href="PROCESS.md#gadcf908971c2ea15ced780025772084e3">pthread_condattr_getclock</a> (const pthread_condattr_t *__restrict a, clockid_t *__restrict clk)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p998901471084824"><a name="p998901471084824"></a><a name="p998901471084824"></a>int&nbsp;</p>
<p id="p487903187084824"><a name="p487903187084824"></a><a name="p487903187084824"></a>Obtains the clock of a condition variable attribute object. </p>
</td>
</tr>
<tr id="row1188120880084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237104176084824"><a name="p1237104176084824"></a><a name="p1237104176084824"></a><a href="PROCESS.md#ga9d831af0179ed16d1b6cbeba0304810b">pthread_rwlockattr_init</a> (pthread_rwlockattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1757310623084824"><a name="p1757310623084824"></a><a name="p1757310623084824"></a>int&nbsp;</p>
<p id="p385743363084824"><a name="p385743363084824"></a><a name="p385743363084824"></a>Initializes a read-write lock attribute object. </p>
</td>
</tr>
<tr id="row2047972513084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p341751571084824"><a name="p341751571084824"></a><a name="p341751571084824"></a><a href="PROCESS.md#ga78a54e67f0afe2601dbda0a904fa0bdf">pthread_rwlockattr_destroy</a> (pthread_rwlockattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105865138084824"><a name="p1105865138084824"></a><a name="p1105865138084824"></a>int&nbsp;</p>
<p id="p223666453084824"><a name="p223666453084824"></a><a name="p223666453084824"></a>Destroys a read-write lock attribute object. </p>
</td>
</tr>
<tr id="row1913395792084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1869824638084824"><a name="p1869824638084824"></a><a name="p1869824638084824"></a><a href="PROCESS.md#ga3bd99d89e352ccc51d5b94d157f1218b">pthread_barrierattr_destroy</a> (pthread_barrierattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443504972084824"><a name="p443504972084824"></a><a name="p443504972084824"></a>int&nbsp;</p>
<p id="p1154881083084824"><a name="p1154881083084824"></a><a name="p1154881083084824"></a>Destroys a barrier attribute object. </p>
</td>
</tr>
<tr id="row369596868084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544468739084824"><a name="p1544468739084824"></a><a name="p1544468739084824"></a><a href="PROCESS.md#ga2ff720e06488668dc0ae6779755946e6">pthread_barrierattr_init</a> (pthread_barrierattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275783262084824"><a name="p1275783262084824"></a><a name="p1275783262084824"></a>int&nbsp;</p>
<p id="p407285060084824"><a name="p407285060084824"></a><a name="p407285060084824"></a>Initializes a barrier attribute object. </p>
</td>
</tr>
<tr id="row23530164084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116267239084824"><a name="p1116267239084824"></a><a name="p1116267239084824"></a><a href="PROCESS.md#ga80008474c3d68e9880da960a53d2f430">pthread_atfork</a> (void(*prepare)(void), void(*parent)(void), void(*child)(void))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445545322084824"><a name="p1445545322084824"></a><a name="p1445545322084824"></a>int&nbsp;</p>
<p id="p621559997084824"><a name="p621559997084824"></a><a name="p621559997084824"></a>Registers a fork handler to be called before and after <a href="UTILS.md#gaa4e4714e6e8927c80b2553a40094b6d9">fork()</a>. </p>
</td>
</tr>
<tr id="row1241769862084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p104165488084824"><a name="p104165488084824"></a><a name="p104165488084824"></a><a href="PROCESS.md#ga68bc26522daf418f3cc78360925374ef">pthread_cleanup_push</a> (void(*routine)(void *), void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1277465028084824"><a name="p1277465028084824"></a><a name="p1277465028084824"></a>void&nbsp;</p>
<p id="p906666158084824"><a name="p906666158084824"></a><a name="p906666158084824"></a>Pushes the routine to the top of the clean-up handler stack. </p>
</td>
</tr>
<tr id="row1294256342084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657071356084824"><a name="p1657071356084824"></a><a name="p1657071356084824"></a><a href="PROCESS.md#gafbe33fb00cd24693796a0870a3374631">pthread_cleanup_pop</a> (int execute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p645888782084824"><a name="p645888782084824"></a><a name="p645888782084824"></a>void&nbsp;</p>
<p id="p1301194099084824"><a name="p1301194099084824"></a><a name="p1301194099084824"></a>Removes the routine at the top of the clean-up handler stack. </p>
</td>
</tr>
<tr id="row324413135084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2030338429084824"><a name="p2030338429084824"></a><a name="p2030338429084824"></a><a href="PROCESS.md#ga6bdca4b2c8a436c4651fb5e8d462408b">pthread_getattr_np</a> (pthread_t thread, pthread_attr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p536905983084824"><a name="p536905983084824"></a><a name="p536905983084824"></a>int&nbsp;</p>
<p id="p1830862147084824"><a name="p1830862147084824"></a><a name="p1830862147084824"></a>Obtains the attributes of a created thread. </p>
</td>
</tr>
<tr id="row2087941101084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549047572084824"><a name="p549047572084824"></a><a name="p549047572084824"></a><a href="PROCESS.md#ga185584d77295432838d8b839d916f160">pthread_setname_np</a> (pthread_t pthread, const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538374774084824"><a name="p1538374774084824"></a><a name="p1538374774084824"></a>int&nbsp;</p>
<p id="p1105014341084824"><a name="p1105014341084824"></a><a name="p1105014341084824"></a>Sets the thread name. </p>
</td>
</tr>
<tr id="row467202089084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p929730015084824"><a name="p929730015084824"></a><a name="p929730015084824"></a><a href="PROCESS.md#gafaebd1698caeb9b9b9e614ad84edd609">sched_get_priority_max</a> (int policy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1160567422084824"><a name="p1160567422084824"></a><a name="p1160567422084824"></a>int&nbsp;</p>
<p id="p888430176084824"><a name="p888430176084824"></a><a name="p888430176084824"></a>Obtains the maximum static priority that can be used for a process. </p>
</td>
</tr>
<tr id="row1583158745084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492329499084824"><a name="p1492329499084824"></a><a name="p1492329499084824"></a><a href="PROCESS.md#gaf1f370fc36ea6b22ed42b5ee3cf82a81">sched_get_priority_min</a> (int policy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1772582612084824"><a name="p1772582612084824"></a><a name="p1772582612084824"></a>int&nbsp;</p>
<p id="p1937164718084824"><a name="p1937164718084824"></a><a name="p1937164718084824"></a>Obtains the minimum static priority that can be used for a process. </p>
</td>
</tr>
<tr id="row478689088084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1952100227084824"><a name="p1952100227084824"></a><a name="p1952100227084824"></a><a href="PROCESS.md#ga563c7ac53bac2c1b51379147e66c44ec">sched_getparam</a> (pid_t pid, struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837960267084824"><a name="p837960267084824"></a><a name="p837960267084824"></a>int&nbsp;</p>
<p id="p811296250084824"><a name="p811296250084824"></a><a name="p811296250084824"></a>Obtains scheduling parameters of a process. </p>
</td>
</tr>
<tr id="row1476232825084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p159873658084824"><a name="p159873658084824"></a><a name="p159873658084824"></a><a href="PROCESS.md#ga99fcb2532b1482d236dc04495a3f194d">sched_getscheduler</a> (pid_t pid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947229078084824"><a name="p1947229078084824"></a><a name="p1947229078084824"></a>int&nbsp;</p>
<p id="p1912877894084824"><a name="p1912877894084824"></a><a name="p1912877894084824"></a>Obtains the scheduling policy of a process. </p>
</td>
</tr>
<tr id="row1156344728084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p736735690084824"><a name="p736735690084824"></a><a name="p736735690084824"></a><a href="PROCESS.md#ga484f0eb93529d29a66e24485725c4c7b">sched_rr_get_interval</a> (pid_t pid, struct <a href="timespec.md">timespec</a> *interval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1181253244084824"><a name="p1181253244084824"></a><a name="p1181253244084824"></a>int&nbsp;</p>
<p id="p847007270084824"><a name="p847007270084824"></a><a name="p847007270084824"></a>Obtains the execution time limit of a process. </p>
</td>
</tr>
<tr id="row208921569084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652809253084824"><a name="p1652809253084824"></a><a name="p1652809253084824"></a><a href="PROCESS.md#ga06b497c4ea6bbabd2b62ba1a8a848a1b">sched_setparam</a> (pid_t pid, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1264337258084824"><a name="p1264337258084824"></a><a name="p1264337258084824"></a>int&nbsp;</p>
<p id="p1401516440084824"><a name="p1401516440084824"></a><a name="p1401516440084824"></a>Sets scheduling parameters related to a scheduling policy for a process. </p>
</td>
</tr>
<tr id="row722426355084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386377182084824"><a name="p386377182084824"></a><a name="p386377182084824"></a><a href="PROCESS.md#ga84ad29a6f2ad27370df09c664ac65eac">sched_setscheduler</a> (pid_t pid, int policy, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363990651084824"><a name="p1363990651084824"></a><a name="p1363990651084824"></a>int&nbsp;</p>
<p id="p1831511663084824"><a name="p1831511663084824"></a><a name="p1831511663084824"></a>Sets a scheduling policy for a process. </p>
</td>
</tr>
<tr id="row1277544311084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1454958263084824"><a name="p1454958263084824"></a><a name="p1454958263084824"></a><a href="PROCESS.md#ga357cd4b34c13011749dfffb42b489f09">sched_yield</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791274809084824"><a name="p791274809084824"></a><a name="p791274809084824"></a>int&nbsp;</p>
<p id="p1341014772084824"><a name="p1341014772084824"></a><a name="p1341014772084824"></a>Yields the running process. </p>
</td>
</tr>
<tr id="row93531609084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p130267073084824"><a name="p130267073084824"></a><a name="p130267073084824"></a><a href="PROCESS.md#gaa284eba1654e9fc0672aca2a6d2cd0ce">capget</a> (cap_user_header_t hdr_ptr, cap_user_data_t data_ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883981525084824"><a name="p1883981525084824"></a><a name="p1883981525084824"></a>int&nbsp;</p>
<p id="p357603146084824"><a name="p357603146084824"></a><a name="p357603146084824"></a>Obtains the capability information of a specified process based on the input parameters (compatible with the Linux API format). </p>
</td>
</tr>
<tr id="row1633453202084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1248874912084824"><a name="p1248874912084824"></a><a name="p1248874912084824"></a><a href="PROCESS.md#gaaa15be01b20aff9efb09de5a8ead207e">capset</a> (cap_user_header_t hdr_ptr, const cap_user_data_t data_ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p973631038084824"><a name="p973631038084824"></a><a name="p973631038084824"></a>int&nbsp;</p>
<p id="p937045220084824"><a name="p937045220084824"></a><a name="p937045220084824"></a>Sets the capability information for a specified process based on the input parameters (compatible with the Linux API format). </p>
</td>
</tr>
<tr id="row1713508516084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p845460725084824"><a name="p845460725084824"></a><a name="p845460725084824"></a><a href="PROCESS.md#gadc569f762fec70a992db20cfec698e29">ohos_capget</a> (unsigned int *caps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p117690403084824"><a name="p117690403084824"></a><a name="p117690403084824"></a>int&nbsp;</p>
<p id="p1469220257084824"><a name="p1469220257084824"></a><a name="p1469220257084824"></a>Obtains the capability information of a specified process based on the input parameters. </p>
</td>
</tr>
<tr id="row625951306084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p533088168084824"><a name="p533088168084824"></a><a name="p533088168084824"></a><a href="PROCESS.md#ga77ad7758babf522e7ffb28551332a659">ohos_capset</a> (unsigned int caps)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088086806084824"><a name="p1088086806084824"></a><a name="p1088086806084824"></a>int&nbsp;</p>
<p id="p1652750451084824"><a name="p1652750451084824"></a><a name="p1652750451084824"></a>Sets the capability information of a specified process based on the input parameters. </p>
</td>
</tr>
<tr id="row1056924427084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2041614050084824"><a name="p2041614050084824"></a><a name="p2041614050084824"></a><a href="PROCESS.md#gac2ee4921a8961060b4c7fcad8bf2b4e2">getpriority</a> (int which, id_t who)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824847031084824"><a name="p1824847031084824"></a><a name="p1824847031084824"></a>int&nbsp;</p>
<p id="p932014623084824"><a name="p932014623084824"></a><a name="p932014623084824"></a>Obtains the static priority of a specified ID. </p>
</td>
</tr>
<tr id="row554795327084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1293979954084824"><a name="p1293979954084824"></a><a name="p1293979954084824"></a><a href="PROCESS.md#ga0a8d4c8043a7748c25dd551dc69dcad2">setpriority</a> (int which, id_t who, int value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2143315206084824"><a name="p2143315206084824"></a><a name="p2143315206084824"></a>int&nbsp;</p>
<p id="p839437533084824"><a name="p839437533084824"></a><a name="p839437533084824"></a>Sets the static priority of a specified ID. </p>
</td>
</tr>
<tr id="row937266197084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p629137941084824"><a name="p629137941084824"></a><a name="p629137941084824"></a><a href="PROCESS.md#gabf2fbcf6df59fd5234e9eed4db1a1804">wait</a> (int *status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1344590512084824"><a name="p1344590512084824"></a><a name="p1344590512084824"></a>pid_t&nbsp;</p>
<p id="p1390046259084824"><a name="p1390046259084824"></a><a name="p1390046259084824"></a>Waits for any child process to end and reclaims its resources. </p>
</td>
</tr>
<tr id="row811927952084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970798163084824"><a name="p1970798163084824"></a><a name="p1970798163084824"></a><a href="PROCESS.md#ga77de8005691d1f125540d66032a3cc62">waitpid</a> (pid_t pid, int *status, int options)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1129467620084824"><a name="p1129467620084824"></a><a name="p1129467620084824"></a>pid_t&nbsp;</p>
<p id="p967495309084824"><a name="p967495309084824"></a><a name="p967495309084824"></a>Waits for a specified child process to end and reclaims its resources. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section510763513084824"></a>

## **Function Documentation**<a name="section1720628532084824"></a>

## capget\(\)<a name="gaa284eba1654e9fc0672aca2a6d2cd0ce"></a>

```
int capget (cap_user_header_t hdr_ptr, cap_user_data_t data_ptr )
```

 **Description:**

Obtains the capability information of a specified process based on the input parameters \(compatible with the Linux API format\). 

**Parameters:**

<a name="table2085781203084824"></a>
<table><thead align="left"><tr id="row951906347084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1698855269084824"><a name="p1698855269084824"></a><a name="p1698855269084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p152230177084824"><a name="p152230177084824"></a><a name="p152230177084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row880369737084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hdr_ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data structure required for this function call, including the API version and the target process identifier (PID). The PID can only be set to <strong id="b650764473084824"><a name="b650764473084824"></a><a name="b650764473084824"></a>0</strong>. </td>
</tr>
<tr id="row1983319476084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data_ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer space for storing the process capabilities. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1994104012084824"></a>
<table><thead align="left"><tr id="row1240162387084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p146240031084824"><a name="p146240031084824"></a><a name="p146240031084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1317755804084824"><a name="p1317755804084824"></a><a name="p1317755804084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row926727905084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p563875497084824"><a name="p563875497084824"></a><a name="p563875497084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p725927624084824"><a name="p725927624084824"></a><a name="p725927624084824"></a>Incorrect parameter. </p>
</td>
</tr>
<tr id="row458886552084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2119811734084824"><a name="p2119811734084824"></a><a name="p2119811734084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114100824084824"><a name="p2114100824084824"></a><a name="p2114100824084824"></a>No permission. </p>
</td>
</tr>
<tr id="row1260172994084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1132732084824"><a name="p1132732084824"></a><a name="p1132732084824"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676066416084824"><a name="p676066416084824"></a><a name="p676066416084824"></a>Invalid memory address. </p>
</td>
</tr>
</tbody>
</table>

## capset\(\)<a name="gaaa15be01b20aff9efb09de5a8ead207e"></a>

```
int capset (cap_user_header_t hdr_ptr, const cap_user_data_t data_ptr )
```

 **Description:**

Sets the capability information for a specified process based on the input parameters \(compatible with the Linux API format\). 

**Parameters:**

<a name="table129792095084824"></a>
<table><thead align="left"><tr id="row1255171170084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p166181063084824"><a name="p166181063084824"></a><a name="p166181063084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1889658101084824"><a name="p1889658101084824"></a><a name="p1889658101084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1505084379084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hdr_ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data structure required for this function call, including the API version and the target PID. The PID can only be set to <strong id="b1087971895084824"><a name="b1087971895084824"></a><a name="b1087971895084824"></a>0</strong>, representing the current process. </td>
</tr>
<tr id="row182043133084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data_ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer space for storing the customized process capabilities. Currently, the following capabilities are supported (other values do not take effect): CAP_CHOWN: changes the permissions of file ownership. CAP_DAC_OVERRIDE: ignores discretionary access control (DAC) restrictions. CAP_DAC_READ_SEARCH: ignores DAC restrictions on file read and search. CAP_FOWNER: allows other users (not the file owner) to modify file permission configurations. CAP_KILL: allows the current process to send signals to other processes with different UIDs. CAP_SETGID: allows changing the group ID of the process. CAP_SETUID: allows changing the user ID of the process. CAP_SETPCAP: allows changing the capabilities. CAP_NET_BIND_SERVICE: allows the process to be bound to a port whose number is smaller than 1024. CAP_NET_BROADCAST: allows network broadcast or multicast. CAP_NET_ADMIN: allows network-related management functions. CAP_NET_RAW: allows raw sockets to be used. CAP_SYS_PTRACE: allows system commissioning. CAP_SYS_ADMIN: allows system management operations. CAP_SYS_NICE: allows priority increase and priority setting for other processes. CAP_SYS_TIME: allows changing the system clock. The <strong id="b1060434819084824"><a name="b1060434819084824"></a><a name="b1060434819084824"></a>cap_user_data_t</strong> structure contains three members: <strong id="b501991736084824"><a name="b501991736084824"></a><a name="b501991736084824"></a>effective</strong>, <strong id="b720001143084824"><a name="b720001143084824"></a><a name="b720001143084824"></a>permitted</strong>, and <strong id="b943229069084824"><a name="b943229069084824"></a><a name="b943229069084824"></a>inheritable</strong>. <strong id="b1993559137084824"><a name="b1993559137084824"></a><a name="b1993559137084824"></a>inheritable</strong> is not implemented. <strong id="b1349383929084824"><a name="b1349383929084824"></a><a name="b1349383929084824"></a>effective</strong> is included in <strong id="b759484432084824"><a name="b759484432084824"></a><a name="b759484432084824"></a>permitted</strong>. <strong id="b141282293084824"><a name="b141282293084824"></a><a name="b141282293084824"></a>permitted</strong> and <strong id="b752941958084824"><a name="b752941958084824"></a><a name="b752941958084824"></a>inheritable</strong> can only be decreased. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the creation fails. 

<a name="table1565839667084824"></a>
<table><thead align="left"><tr id="row622383254084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1088703599084824"><a name="p1088703599084824"></a><a name="p1088703599084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1279050662084824"><a name="p1279050662084824"></a><a name="p1279050662084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row847262098084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2113719621084824"><a name="p2113719621084824"></a><a name="p2113719621084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1618566444084824"><a name="p1618566444084824"></a><a name="p1618566444084824"></a>Incorrect parameter. </p>
</td>
</tr>
<tr id="row1595138755084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524437505084824"><a name="p524437505084824"></a><a name="p524437505084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007636053084824"><a name="p2007636053084824"></a><a name="p2007636053084824"></a>No permission. </p>
</td>
</tr>
</tbody>
</table>

## getpriority\(\)<a name="gac2ee4921a8961060b4c7fcad8bf2b4e2"></a>

```
int getpriority (int which, id_t who )
```

 **Description:**

Obtains the static priority of a specified ID. 

**Parameters:**

<a name="table1434604177084824"></a>
<table><thead align="left"><tr id="row2144162423084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1700993000084824"><a name="p1700993000084824"></a><a name="p1700993000084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p301983493084824"><a name="p301983493084824"></a><a name="p301983493084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row610423028084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">which</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a specified value. The values are as follows: </td>
</tr>
<tr id="row530388221084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">who</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the specified ID. </td>
</tr>
</tbody>
</table>

<a name="table193361917084824"></a>
<table><thead align="left"><tr id="row348885867084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p284057970084824"><a name="p284057970084824"></a><a name="p284057970084824"></a>value </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1297402024084824"><a name="p1297402024084824"></a><a name="p1297402024084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row575034466084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1903883105084824"><a name="p1903883105084824"></a><a name="p1903883105084824"></a>RIO_PROCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925466972084824"><a name="p1925466972084824"></a><a name="p1925466972084824"></a><strong id="b1409507230084824"><a name="b1409507230084824"></a><a name="b1409507230084824"></a>who</strong> indicates the ID of a specified process. </p>
</td>
</tr>
<tr id="row968996248084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1198608550084824"><a name="p1198608550084824"></a><a name="p1198608550084824"></a>PRIO_PGRP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374128758084824"><a name="p374128758084824"></a><a name="p374128758084824"></a><strong id="b1534416505084824"><a name="b1534416505084824"></a><a name="b1534416505084824"></a>who</strong> indicates the ID of a specified process group. This value is not supported yet. </p>
</td>
</tr>
<tr id="row1476051019084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2066006285084824"><a name="p2066006285084824"></a><a name="p2066006285084824"></a>PRIO_USER </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p945299514084824"><a name="p945299514084824"></a><a name="p945299514084824"></a><strong id="b1705620117084824"><a name="b1705620117084824"></a><a name="b1705620117084824"></a>who</strong> indicates the ID of a specified valid user. This value is not supported yet. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the scheduling priority if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table otherwise. 

<a name="table330687263084824"></a>
<table><thead align="left"><tr id="row367091687084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1678805576084824"><a name="p1678805576084824"></a><a name="p1678805576084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p346283658084824"><a name="p346283658084824"></a><a name="p346283658084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1615120760084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348291103084824"><a name="p348291103084824"></a><a name="p348291103084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979800602084824"><a name="p979800602084824"></a><a name="p979800602084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1516275333084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980828218084824"><a name="p980828218084824"></a><a name="p980828218084824"></a>EOPNOTSUPP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012936593084824"><a name="p1012936593084824"></a><a name="p1012936593084824"></a>Unsupported value. </p>
</td>
</tr>
</tbody>
</table>

## ohos\_capget\(\)<a name="gadc569f762fec70a992db20cfec698e29"></a>

```
int ohos_capget (unsigned int * caps)
```

 **Description:**

Obtains the capability information of a specified process based on the input parameters. 

**Parameters:**

<a name="table1847576773084824"></a>
<table><thead align="left"><tr id="row1859326939084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1554040017084824"><a name="p1554040017084824"></a><a name="p1554040017084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p983590973084824"><a name="p983590973084824"></a><a name="p983590973084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1241867269084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">caps</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory address for storing the obtained capability information of a specified process. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1784706605084824"></a>
<table><thead align="left"><tr id="row1686076508084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p511850562084824"><a name="p511850562084824"></a><a name="p511850562084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1902857986084824"><a name="p1902857986084824"></a><a name="p1902857986084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1907643463084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p96334393084824"><a name="p96334393084824"></a><a name="p96334393084824"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1657586542084824"><a name="p1657586542084824"></a><a name="p1657586542084824"></a>Invalid memory address. </p>
</td>
</tr>
</tbody>
</table>

## ohos\_capset\(\)<a name="ga77ad7758babf522e7ffb28551332a659"></a>

```
int ohos_capset (unsigned int caps)
```

 **Description:**

Sets the capability information of a specified process based on the input parameters. 

**Parameters:**

<a name="table659099000084824"></a>
<table><thead align="left"><tr id="row364204258084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p858809444084824"><a name="p858809444084824"></a><a name="p858809444084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1387730436084824"><a name="p1387730436084824"></a><a name="p1387730436084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row920035194084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">caps</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the customized capability information of the process. Currently, the following capabilities are supported (other values do not take effect): OHOS_CAP_CHOWN: changes the permissions of file ownership. OHOS_CAP_DAC_EXECUTE: ignores discretionary access control (DAC) restrictions on file execution. OHOS_CAP_DAC_WRITE: ignores DAC restrictions on file write. OHOS_CAP_DAC_READ_SEARCH: ignores DAC restrictions on file read and search. OHOS_CAP_FOWNER: allows other users (not the file owner) to modify file permission configurations. OHOS_CAP_KILL: allows the current process to send signals to other processes with different UIDs. OHOS_CAP_SETGID: allows changing the group ID of the process. OHOS_CAP_SETUID: allows changing the user ID of the process. OHOS_CAP_NET_BIND_SERVICE: allows the process to be bound to a port whose number is smaller than 1024. OHOS_CAP_NET_BROADCAST: allows network broadcast and multicast. OHOS_CAP_NET_ADMIN: allows network-related management functions. OHOS_CAP_NET_RAW: allows raw sockets to be used. OHOS_CAP_FS_MOUNT: allows mounting operations. OHOS_CAP_FS_FORMAT: allows storage formatting operations. OHOS_CAP_SCHED_SETPRIORITY: allows priority increase and priority setting for other processes. OHOS_CAP_SET_TIMEOFDAY: allows calling of the timeofday API. OHOS_CAP_CLOCK_SETTIME: allows calling of the clock_settime API. OHOS_CAP_CAPSET: allows changing the capabilities. OHOS_CAP_SHELL_EXEC: allows calling of the shellexec API. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the creation fails. 

<a name="table1485709461084824"></a>
<table><thead align="left"><tr id="row596346739084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1475108987084824"><a name="p1475108987084824"></a><a name="p1475108987084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p905957220084824"><a name="p905957220084824"></a><a name="p905957220084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row57878428084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1842208568084824"><a name="p1842208568084824"></a><a name="p1842208568084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1727987132084824"><a name="p1727987132084824"></a><a name="p1727987132084824"></a>No permission. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_atfork\(\)<a name="ga80008474c3d68e9880da960a53d2f430"></a>

```
int pthread_atfork (void(*)(void) prepare, void(*)(void) parent, void(*)(void) child )
```

 **Description:**

Registers a fork handler to be called before and after  [fork\(\)](UTILS.md#gaa4e4714e6e8927c80b2553a40094b6d9). 

**Parameters:**

<a name="table1042783038084824"></a>
<table><thead align="left"><tr id="row610862155084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1435858554084824"><a name="p1435858554084824"></a><a name="p1435858554084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1174025822084824"><a name="p1174025822084824"></a><a name="p1174025822084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1870494721084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prepare</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the fork handler to be called before <a href="UTILS.md#gaa4e4714e6e8927c80b2553a40094b6d9">fork()</a>. </td>
</tr>
<tr id="row1206821395084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">parent</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the fork handler to be called after <a href="UTILS.md#gaa4e4714e6e8927c80b2553a40094b6d9">fork()</a> in the parent process. </td>
</tr>
<tr id="row1883281204084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">child</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the fork handler to be called after <a href="UTILS.md#gaa4e4714e6e8927c80b2553a40094b6d9">fork()</a> in the child process. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## pthread\_attr\_destroy\(\)<a name="ga4bcdbf47c17c7dcc51e9f05f5cb56d81"></a>

```
int pthread_attr_destroy (pthread_attr_t * attr)
```

 **Description:**

Destroys a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table954467176084824"></a>
<table><thead align="left"><tr id="row1151412069084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p155296264084824"><a name="p155296264084824"></a><a name="p155296264084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2030977312084824"><a name="p2030977312084824"></a><a name="p2030977312084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row209288691084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread attribute object to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_getdetachstate\(\)<a name="ga391c34da42e68ddd24f5ee0c070d5c4f"></a>

```
int pthread_attr_getdetachstate (const pthread_attr_t * attr, int * detachstate )
```

 **Description:**

Obtains the detach state of a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table2103974071084824"></a>
<table><thead align="left"><tr id="row500575555084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p690428831084824"><a name="p690428831084824"></a><a name="p690428831084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1164769673084824"><a name="p1164769673084824"></a><a name="p1164769673084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2087951893084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1833656736084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">detachstate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained detach state. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_getguardsize\(\)<a name="gaa8b692ecc3880fdd49a4d423ba1ce91e"></a>

```
int pthread_attr_getguardsize (const pthread_attr_t * attr, size_t * guardsize )
```

 **Description:**

Obtains the guard size of a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1867824798084824"></a>
<table><thead align="left"><tr id="row240287384084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p491177722084824"><a name="p491177722084824"></a><a name="p491177722084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p295216038084824"><a name="p295216038084824"></a><a name="p295216038084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2131236603084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row500045819084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">guardsize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained guard size. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_getinheritsched\(\)<a name="ga79a77b688c30213e5e52e6be178cde4e"></a>

```
int pthread_attr_getinheritsched (const pthread_attr_t * attr, int * inheritsched )
```

 **Description:**

Obtains inherit scheduler attributes of a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1261533828084824"></a>
<table><thead align="left"><tr id="row486205182084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1807347651084824"><a name="p1807347651084824"></a><a name="p1807347651084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1395478539084824"><a name="p1395478539084824"></a><a name="p1395478539084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row181189477084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row51108636084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">inheritsched</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained inherit scheduler attributes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_getschedparam\(\)<a name="gafd3d272d702481044f8a8cd253fd9b47"></a>

```
int pthread_attr_getschedparam (const pthread_attr_t * attr, struct [sched_param](sched_param.md) * param )
```

 **Description:**

Obtains scheduling parameter attributes of a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1690283726084824"></a>
<table><thead align="left"><tr id="row1270920186084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p508600256084824"><a name="p508600256084824"></a><a name="p508600256084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1091571827084824"><a name="p1091571827084824"></a><a name="p1091571827084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row484008880084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1894110832084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained scheduling parameter attributes. Only the thread priority is supported. The priority ranges from 0 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_getschedpolicy\(\)<a name="gaec4d8127833d1a573aa82539f898a8ed"></a>

```
int pthread_attr_getschedpolicy (const pthread_attr_t * attr, int * schedpolicy )
```

 **Description:**

Obtains scheduling policy attributes of a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1211462923084824"></a>
<table><thead align="left"><tr id="row302021596084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p412249960084824"><a name="p412249960084824"></a><a name="p412249960084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1873292139084824"><a name="p1873292139084824"></a><a name="p1873292139084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row252551319084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1281935835084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">schedpolicy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained scheduling policy attributes. Only <strong id="b3663884084824"><a name="b3663884084824"></a><a name="b3663884084824"></a>SCHED_FIFO</strong> and <strong id="b469928759084824"><a name="b469928759084824"></a><a name="b469928759084824"></a>SCHED_RR</strong> are supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_getscope\(\)<a name="ga8a53d8e8b40b2332581ee219c5e4c468"></a>

```
int pthread_attr_getscope (const pthread_attr_t * arrt, int * scope )
```

 **Description:**

Obtains contention scope attributes of a thread attribute object. 

**Parameters:**

<a name="table229376226084824"></a>
<table><thead align="left"><tr id="row5342589084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1066913128084824"><a name="p1066913128084824"></a><a name="p1066913128084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1038335974084824"><a name="p1038335974084824"></a><a name="p1038335974084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row14983062084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row69356976084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">scope</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start address of the buffer that stores the target thread attribute object. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1487405701084824"></a>
<table><thead align="left"><tr id="row394970216084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1714576264084824"><a name="p1714576264084824"></a><a name="p1714576264084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1841076617084824"><a name="p1841076617084824"></a><a name="p1841076617084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row423178277084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985735910084824"><a name="p985735910084824"></a><a name="p985735910084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078100848084824"><a name="p1078100848084824"></a><a name="p1078100848084824"></a>Invalid <strong id="b316677849084824"><a name="b316677849084824"></a><a name="b316677849084824"></a>scope</strong> value. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_getstack\(\)<a name="gaec19ad460995a9fe8aeb4eaf2bb1ed1d"></a>

```
int pthread_attr_getstack (const pthread_attr_t * attr, void ** stackaddr, size_t * stacksize )
```

 **Description:**

Obtains stack attributes of a thread attribute object. 

**Parameters:**

<a name="table1504556339084824"></a>
<table><thead align="left"><tr id="row1996813818084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1093226958084824"><a name="p1093226958084824"></a><a name="p1093226958084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1822266152084824"><a name="p1822266152084824"></a><a name="p1822266152084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1808831380084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1173572873084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">stackaddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the start address of the buffer that stores the obtained stack attributes. </td>
</tr>
<tr id="row883315901084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">stacksize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the size of the buffer that stores the obtained stack attributes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1051338136084824"></a>
<table><thead align="left"><tr id="row1829323631084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2030063384084824"><a name="p2030063384084824"></a><a name="p2030063384084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p124464237084824"><a name="p124464237084824"></a><a name="p124464237084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1919076203084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p373183484084824"><a name="p373183484084824"></a><a name="p373183484084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311983018084824"><a name="p311983018084824"></a><a name="p311983018084824"></a>Invalid start address. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_getstacksize\(\)<a name="gae23600d4670359ab12bfba20db2c9a37"></a>

```
int pthread_attr_getstacksize (const pthread_attr_t * attr, size_t * stacksize )
```

 **Description:**

Obtains the stack size of a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1837650204084824"></a>
<table><thead align="left"><tr id="row19033120084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p868314594084824"><a name="p868314594084824"></a><a name="p868314594084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1523947524084824"><a name="p1523947524084824"></a><a name="p1523947524084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2045709457084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1458203006084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">stacksize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained stack size. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_init\(\)<a name="ga0b85ebb1e3aac081a4c0a5e85ae3cbe9"></a>

```
int pthread_attr_init (pthread_attr_t * attr)
```

 **Description:**

Initializes a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table961476993084824"></a>
<table><thead align="left"><tr id="row980129005084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p416554786084824"><a name="p416554786084824"></a><a name="p416554786084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1887319701084824"><a name="p1887319701084824"></a><a name="p1887319701084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2139979894084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread attribute object that is successfully initialized. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_attr\_setdetachstate\(\)<a name="gae6ee78c307d8467b34a9b0c330993a54"></a>

```
int pthread_attr_setdetachstate (pthread_attr_t * attr, int detachstate )
```

 **Description:**

Sets the detach state for a thread attribute object. 

**Parameters:**

<a name="table211414323084824"></a>
<table><thead align="left"><tr id="row512550563084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1084529761084824"><a name="p1084529761084824"></a><a name="p1084529761084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p136185609084824"><a name="p136185609084824"></a><a name="p136185609084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row401770508084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row209809028084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">detachstate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the detach state to set. Available values are as follows: </td>
</tr>
</tbody>
</table>

<a name="table2128599435084824"></a>
<table><thead align="left"><tr id="row757850778084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1634605574084824"><a name="p1634605574084824"></a><a name="p1634605574084824"></a>detachstate </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p265848138084824"><a name="p265848138084824"></a><a name="p265848138084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row71435267084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773056414084824"><a name="p1773056414084824"></a><a name="p1773056414084824"></a>PTHREAD_CREATE_DETACHED </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563698106084824"><a name="p1563698106084824"></a><a name="p1563698106084824"></a>Threads using <strong id="b589448721084824"><a name="b589448721084824"></a><a name="b589448721084824"></a>attr</strong> are created in the detached state. </p>
</td>
</tr>
<tr id="row166125825084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2137847451084824"><a name="p2137847451084824"></a><a name="p2137847451084824"></a>PTHREAD_CREATE_JOINABLE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167402242084824"><a name="p1167402242084824"></a><a name="p1167402242084824"></a>Threads using <strong id="b44278282084824"><a name="b44278282084824"></a><a name="b44278282084824"></a>attr</strong> are created in the joinable state. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1939288265084824"></a>
<table><thead align="left"><tr id="row210283277084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p256096643084824"><a name="p256096643084824"></a><a name="p256096643084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1960757845084824"><a name="p1960757845084824"></a><a name="p1960757845084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1743174904084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470146280084824"><a name="p470146280084824"></a><a name="p470146280084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1818809574084824"><a name="p1818809574084824"></a><a name="p1818809574084824"></a>Invalid detach state. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setguardsize\(\)<a name="ga532b31c11a9d87663053c5342400758c"></a>

```
int pthread_attr_setguardsize (pthread_attr_t * attr, size_t guardsize )
```

 **Description:**

Sets the guard size for a thread attribute object. 

**Parameters:**

<a name="table949134438084824"></a>
<table><thead align="left"><tr id="row807937328084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1106637968084824"><a name="p1106637968084824"></a><a name="p1106637968084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p329530806084824"><a name="p329530806084824"></a><a name="p329530806084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row159628251084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row762349824084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">guardsize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the guard size to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table468205379084824"></a>
<table><thead align="left"><tr id="row1072140260084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1389259328084824"><a name="p1389259328084824"></a><a name="p1389259328084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1157103979084824"><a name="p1157103979084824"></a><a name="p1157103979084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1065316477084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1912176144084824"><a name="p1912176144084824"></a><a name="p1912176144084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1066960950084824"><a name="p1066960950084824"></a><a name="p1066960950084824"></a>Invalid guard size. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setinheritsched\(\)<a name="gad437fe8caa3ef9f0cb7d69f6f6479df9"></a>

```
int pthread_attr_setinheritsched (pthread_attr_t * attr, int inheritsched )
```

 **Description:**

Sets inherit scheduler attributes for a thread attribute object. 

**Parameters:**

<a name="table802482622084824"></a>
<table><thead align="left"><tr id="row746224253084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p385472005084824"><a name="p385472005084824"></a><a name="p385472005084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1868718166084824"><a name="p1868718166084824"></a><a name="p1868718166084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2040290015084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1822564983084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">inheritsched</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the inherit scheduler attributes to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1113800093084824"></a>
<table><thead align="left"><tr id="row759656687084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p103723519084824"><a name="p103723519084824"></a><a name="p103723519084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1138178453084824"><a name="p1138178453084824"></a><a name="p1138178453084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row272232930084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1946761970084824"><a name="p1946761970084824"></a><a name="p1946761970084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1282645969084824"><a name="p1282645969084824"></a><a name="p1282645969084824"></a>Invalid inherit scheduler attribute. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setschedparam\(\)<a name="ga579e6529f0ce482312a5e77ac61cb4d5"></a>

```
int pthread_attr_setschedparam (pthread_attr_t * attr, const struct [sched_param](sched_param.md) * param )
```

 **Description:**

Sets scheduling parameter attributes for a thread attribute object. 

**Parameters:**

<a name="table811129933084824"></a>
<table><thead align="left"><tr id="row157024206084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p979612593084824"><a name="p979612593084824"></a><a name="p979612593084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2047016287084824"><a name="p2047016287084824"></a><a name="p2047016287084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row306138970084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1711135244084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling parameter attributes to set. Only the thread priority is supported. The priority ranges from 0 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table554460060084824"></a>
<table><thead align="left"><tr id="row884385228084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1892048339084824"><a name="p1892048339084824"></a><a name="p1892048339084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p831921378084824"><a name="p831921378084824"></a><a name="p831921378084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row952255803084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p761572842084824"><a name="p761572842084824"></a><a name="p761572842084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225796755084824"><a name="p1225796755084824"></a><a name="p1225796755084824"></a>Invalid scheduling parameter attributes. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setschedpolicy\(\)<a name="gab6cb2eb73f04abf328b2f39777c35dca"></a>

```
int pthread_attr_setschedpolicy (pthread_attr_t * attr, int schedpolicy )
```

 **Description:**

Sets scheduling policy attributes for a thread attribute object. 

**Parameters:**

<a name="table1514856899084824"></a>
<table><thead align="left"><tr id="row968407234084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p523765994084824"><a name="p523765994084824"></a><a name="p523765994084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1208848535084824"><a name="p1208848535084824"></a><a name="p1208848535084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2099342419084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row23754997084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">schedpolicy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the scheduling policy attributes to set. Only <strong id="b1101405110084824"><a name="b1101405110084824"></a><a name="b1101405110084824"></a>SCHED_FIFO</strong> and <strong id="b1029936392084824"><a name="b1029936392084824"></a><a name="b1029936392084824"></a>SCHED_RR</strong> are supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table924644044084824"></a>
<table><thead align="left"><tr id="row2141266412084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2037497942084824"><a name="p2037497942084824"></a><a name="p2037497942084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p625132174084824"><a name="p625132174084824"></a><a name="p625132174084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1672619277084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p886926488084824"><a name="p886926488084824"></a><a name="p886926488084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1426346768084824"><a name="p1426346768084824"></a><a name="p1426346768084824"></a>Invalid scheduling policy attribute. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setscope\(\)<a name="ga9f90a3707a1797591661272928c152f9"></a>

```
int pthread_attr_setscope (pthread_attr_t * arrt, int scope )
```

 **Description:**

Sets contention scope attributes for a thread attribute object. 

The contention scope attribute defines a set of threads against which a thread competes for resources such as the CPU. POSIX.1-2001 specifies two values for  **scope**: 

POSIX.1-2001 does not specify how these threads contend with other threads in other process on the system or with other threads in the same process that were created with the  **PTHREAD\_SCOPE\_SYSTEM**  contention scope. 

**Parameters:**

<a name="table32917314084824"></a>
<table><thead align="left"><tr id="row960805865084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p821734053084824"><a name="p821734053084824"></a><a name="p821734053084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1368515527084824"><a name="p1368515527084824"></a><a name="p1368515527084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row330092309084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row1409456386084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">scope</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start address of the buffer that stores the target thread attribute object. By default, only <strong id="b964531206084824"><a name="b964531206084824"></a><a name="b964531206084824"></a>PTHREAD_SCOPE_PROCESS</strong> is supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1959666426084824"></a>
<table><thead align="left"><tr id="row84900723084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1087347019084824"><a name="p1087347019084824"></a><a name="p1087347019084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p55228587084824"><a name="p55228587084824"></a><a name="p55228587084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row281236816084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647287732084824"><a name="p1647287732084824"></a><a name="p1647287732084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445013255084824"><a name="p1445013255084824"></a><a name="p1445013255084824"></a>Invalid <strong id="b2093079344084824"><a name="b2093079344084824"></a><a name="b2093079344084824"></a>scope</strong> value. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setstack\(\)<a name="ga94ede89b99a3a4fa17e516d30aaf3409"></a>

```
int pthread_attr_setstack (pthread_attr_t * attr, void * stackaddr, size_t stacksize )
```

 **Description:**

Sets stack attributes for a thread attribute object. 

**Parameters:**

<a name="table998354282084824"></a>
<table><thead align="left"><tr id="row165598998084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p814796014084824"><a name="p814796014084824"></a><a name="p814796014084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p107085427084824"><a name="p107085427084824"></a><a name="p107085427084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row130872635084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread attribute object. </td>
</tr>
<tr id="row1922364655084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">stackaddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start address of the buffer that stores the stack attributes to set. </td>
</tr>
<tr id="row1388725867084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">stacksize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the buffer that stores the stack attributes to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1992212206084824"></a>
<table><thead align="left"><tr id="row507354055084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1857551476084824"><a name="p1857551476084824"></a><a name="p1857551476084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1367721446084824"><a name="p1367721446084824"></a><a name="p1367721446084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2029382585084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26850201084824"><a name="p26850201084824"></a><a name="p26850201084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143952413084824"><a name="p1143952413084824"></a><a name="p1143952413084824"></a>Invalid start address. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_attr\_setstacksize\(\)<a name="ga812a9a455ae2ef2bb0dca4fff201a281"></a>

```
int pthread_attr_setstacksize (pthread_attr_t * attr, size_t stacksize )
```

 **Description:**

Sets the stack size for a thread attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table121731112084824"></a>
<table><thead align="left"><tr id="row230968608084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p614271082084824"><a name="p614271082084824"></a><a name="p614271082084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1826891525084824"><a name="p1826891525084824"></a><a name="p1826891525084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row416558467084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target thread attribute object. </td>
</tr>
<tr id="row185536683084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">stacksize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the stack size. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table489416223084824"></a>
<table><thead align="left"><tr id="row933287660084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2040123603084824"><a name="p2040123603084824"></a><a name="p2040123603084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1601214885084824"><a name="p1601214885084824"></a><a name="p1601214885084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1826124070084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p426169803084824"><a name="p426169803084824"></a><a name="p426169803084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342692310084824"><a name="p1342692310084824"></a><a name="p1342692310084824"></a>Invalid stack size. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_barrier\_destroy\(\)<a name="gab05ae13769e61dea9c53ca7894743c8f"></a>

```
int pthread_barrier_destroy (pthread_barrier_t * b)
```

 **Description:**

Destroys a barrier. 

This function always succeeds. 

**Parameters:**

<a name="table1510665380084824"></a>
<table><thead align="left"><tr id="row658293147084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p424642910084824"><a name="p424642910084824"></a><a name="p424642910084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2139286324084824"><a name="p2139286324084824"></a><a name="p2139286324084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1389335642084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">b</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the barrier to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_barrier\_init\(\)<a name="ga4a324cd758cae702213ea41882f4cf41"></a>

```
int pthread_barrier_init (pthread_barrier_t *__restrict b, const pthread_barrierattr_t *__restrict a, unsigned count )
```

 **Description:**

Initializes a barrier. 

**Parameters:**

<a name="table1260882928084824"></a>
<table><thead align="left"><tr id="row1868110653084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1196555087084824"><a name="p1196555087084824"></a><a name="p1196555087084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1780855236084824"><a name="p1780855236084824"></a><a name="p1780855236084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1049001445084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">b</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the barrier to initialize. </td>
</tr>
<tr id="row911552712084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the barrier attribute object. If this parameter is set to <strong id="b132540700084824"><a name="b132540700084824"></a><a name="b132540700084824"></a>NULL</strong>, the default barrier attributes are used. </td>
</tr>
<tr id="row956156178084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of threads that must call <a href="PROCESS.md#gaf786372165ba080986ae4143928c5436">pthread_barrier_wait()</a> before any of them successfully returns from the call. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1241421084084824"></a>
<table><thead align="left"><tr id="row656201714084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1578403255084824"><a name="p1578403255084824"></a><a name="p1578403255084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p495662721084824"><a name="p495662721084824"></a><a name="p495662721084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row838312584084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1399820259084824"><a name="p1399820259084824"></a><a name="p1399820259084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1527008404084824"><a name="p1527008404084824"></a><a name="p1527008404084824"></a>The value of <strong id="b1332973757084824"><a name="b1332973757084824"></a><a name="b1332973757084824"></a>count </strong> is greater than the maximum number of threads to block. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_barrier\_wait\(\)<a name="gaf786372165ba080986ae4143928c5436"></a>

```
int pthread_barrier_wait (pthread_barrier_t * b)
```

 **Description:**

Synchronizes participating threads at a barrier. 

The call is blocked until the required number of threads have called this function with the specified barrier. 

**Parameters:**

<a name="table606745545084824"></a>
<table><thead align="left"><tr id="row7540794084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p241065082084824"><a name="p241065082084824"></a><a name="p241065082084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1846424745084824"><a name="p1846424745084824"></a><a name="p1846424745084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1543303839084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">b</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the barrier to be used for synchronization. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **PTHREAD\_BARRIER\_SERIAL\_THREAD**  for the first restored thread and  **0**  for other threads. 



## pthread\_barrierattr\_destroy\(\)<a name="ga3bd99d89e352ccc51d5b94d157f1218b"></a>

```
int pthread_barrierattr_destroy (pthread_barrierattr_t * a)
```

 **Description:**

Destroys a barrier attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table2114171255084824"></a>
<table><thead align="left"><tr id="row818657773084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p37622902084824"><a name="p37622902084824"></a><a name="p37622902084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p175855510084824"><a name="p175855510084824"></a><a name="p175855510084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1536301157084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the barrier attribute object to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_barrierattr\_init\(\)<a name="ga2ff720e06488668dc0ae6779755946e6"></a>

```
int pthread_barrierattr_init (pthread_barrierattr_t * a)
```

 **Description:**

Initializes a barrier attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table117118203084824"></a>
<table><thead align="left"><tr id="row1910461922084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1595509416084824"><a name="p1595509416084824"></a><a name="p1595509416084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1716434052084824"><a name="p1716434052084824"></a><a name="p1716434052084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row656614507084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the barrier attribute object to initialize. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_cancel\(\)<a name="ga9e77a80c073787bf9a593e9c619dce27"></a>

```
int pthread_cancel (pthread_t thread)
```

 **Description:**

Sends a cancellation request to a thread. 

**Parameters:**

<a name="table887536791084824"></a>
<table><thead align="left"><tr id="row1024516785084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p685336563084824"><a name="p685336563084824"></a><a name="p685336563084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1946265838084824"><a name="p1946265838084824"></a><a name="p1946265838084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1449441334084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread to receive the cancellation request. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table725837492084824"></a>
<table><thead align="left"><tr id="row503498325084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1115732919084824"><a name="p1115732919084824"></a><a name="p1115732919084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p224420531084824"><a name="p224420531084824"></a><a name="p224420531084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row10142264084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p359480944084824"><a name="p359480944084824"></a><a name="p359480944084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p533658244084824"><a name="p533658244084824"></a><a name="p533658244084824"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_cleanup\_pop\(\)<a name="gafbe33fb00cd24693796a0870a3374631"></a>

```
void pthread_cleanup_pop (int execute)
```

 **Description:**

Removes the routine at the top of the clean-up handler stack. 

**Parameters:**

<a name="table1884983918084824"></a>
<table><thead align="left"><tr id="row1800560397084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1725057723084824"><a name="p1725057723084824"></a><a name="p1725057723084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1068885248084824"><a name="p1068885248084824"></a><a name="p1068885248084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row779813009084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">execute</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether the routine at the top of the clean-up handler stack should be executed. If this parameter is set to a non-zero value, the routine at the top of the clean-up handler stack must be popped and executed. </td>
</tr>
</tbody>
</table>

## pthread\_cleanup\_push\(\)<a name="ga68bc26522daf418f3cc78360925374ef"></a>

```
void pthread_cleanup_push (void(*)(void *) routine, void * arg )
```

 **Description:**

Pushes the routine to the top of the clean-up handler stack. 

**Parameters:**

<a name="table297196247084824"></a>
<table><thead align="left"><tr id="row259805569084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p708364875084824"><a name="p708364875084824"></a><a name="p708364875084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1897423885084824"><a name="p1897423885084824"></a><a name="p1897423885084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row491147519084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">routine</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the routine used to complete the clean-up. </td>
</tr>
<tr id="row1199818968084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">arg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the parameter to be passed to the routine. </td>
</tr>
</tbody>
</table>

## pthread\_cond\_broadcast\(\)<a name="ga1c1ac7c8faaf8ad63e12bc3717f430f3"></a>

```
int pthread_cond_broadcast (pthread_cond_t * c)
```

 **Description:**

Unblocks all threads that are currently blocked on the condition variable  **cond**. 

This function always succeeds. 

**Parameters:**

<a name="table1854941569084824"></a>
<table><thead align="left"><tr id="row1170547301084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p413724946084824"><a name="p413724946084824"></a><a name="p413724946084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1616207003084824"><a name="p1616207003084824"></a><a name="p1616207003084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row98082103084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">c</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable to broadcast. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_cond\_destroy\(\)<a name="ga7f2a7328ee3a7743686adcd2d51771c4"></a>

```
int pthread_cond_destroy (pthread_cond_t * c)
```

 **Description:**

Destroys a condition variable. 

This function always succeeds. 

**Parameters:**

<a name="table1065020029084824"></a>
<table><thead align="left"><tr id="row1555345309084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p376997047084824"><a name="p376997047084824"></a><a name="p376997047084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p779958534084824"><a name="p779958534084824"></a><a name="p779958534084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row155325633084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">c</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_cond\_init\(\)<a name="gabdf02ed57b055f1920991e96e7d67043"></a>

```
int pthread_cond_init (pthread_cond_t *__restrict c, const pthread_condattr_t *__restrict a )
```

 **Description:**

Initializes a condition variable. 

This function always succeeds. 

**Parameters:**

<a name="table898911696084824"></a>
<table><thead align="left"><tr id="row1899830900084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p617520147084824"><a name="p617520147084824"></a><a name="p617520147084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p196136457084824"><a name="p196136457084824"></a><a name="p196136457084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2039754462084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">c</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable to initialize. </td>
</tr>
<tr id="row1731294419084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable attribute object. If this parameter is set to <strong id="b1287351228084824"><a name="b1287351228084824"></a><a name="b1287351228084824"></a>NULL</strong>, the default condition variable attributes are used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_cond\_signal\(\)<a name="ga9b0f2c7dead8c628e081d76c86a1addc"></a>

```
int pthread_cond_signal (pthread_cond_t * c)
```

 **Description:**

Unblocks a thread. 

If multiple threads are blocked on the condition variable  **cond**, this function unblocks at least one thread. This function always succeeds. 

**Parameters:**

<a name="table81491761084824"></a>
<table><thead align="left"><tr id="row1703103528084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p747532086084824"><a name="p747532086084824"></a><a name="p747532086084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1536362064084824"><a name="p1536362064084824"></a><a name="p1536362064084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row352065615084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">c</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable to signal. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_cond\_timedwait\(\)<a name="ga506c0350d597721ab24bba7129e8e0df"></a>

```
int pthread_cond_timedwait (pthread_cond_t *__restrict c, pthread_mutex_t *__restrict m, const struct [timespec](timespec.md) *__restrict ts )
```

 **Description:**

Blocks the calling thread to wait for the condition set by  **pthread\_con\_signal\(\)**  for a period of time specified by  **ts**. 

**Parameters:**

<a name="table1148295040084824"></a>
<table><thead align="left"><tr id="row1408349646084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p210787963084824"><a name="p210787963084824"></a><a name="p210787963084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p526287943084824"><a name="p526287943084824"></a><a name="p526287943084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1124439164084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">c</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable to wait for. </td>
</tr>
<tr id="row1092528814084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex associated with the condition variable. </td>
</tr>
<tr id="row1253720678084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ts</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the absolute system time when the calling thread stops blocking. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1257885903084824"></a>
<table><thead align="left"><tr id="row363861872084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1079763018084824"><a name="p1079763018084824"></a><a name="p1079763018084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1919538508084824"><a name="p1919538508084824"></a><a name="p1919538508084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row215387736084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612707631084824"><a name="p612707631084824"></a><a name="p612707631084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85166342084824"><a name="p85166342084824"></a><a name="p85166342084824"></a>Invalid <strong id="b1334699044084824"><a name="b1334699044084824"></a><a name="b1334699044084824"></a>ts</strong> value. </p>
</td>
</tr>
<tr id="row1468838206084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062111156084824"><a name="p1062111156084824"></a><a name="p1062111156084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p986811104084824"><a name="p986811104084824"></a><a name="p986811104084824"></a>The associated mutex is invalid. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_cond\_wait\(\)<a name="gaea601b8ce596a5c54fb12758c56b10a1"></a>

```
int pthread_cond_wait (pthread_cond_t *__restrict c, pthread_mutex_t *__restrict m )
```

 **Description:**

Blocks the calling thread to wait for the condition set by  **pthread\_con\_signal\(\)**. 

**Parameters:**

<a name="table392258440084824"></a>
<table><thead align="left"><tr id="row1033639350084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p842606709084824"><a name="p842606709084824"></a><a name="p842606709084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1790212099084824"><a name="p1790212099084824"></a><a name="p1790212099084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row674764786084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">c</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the condition variable to wait for. </td>
</tr>
<tr id="row482702583084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex associated with the condition variable. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1080548244084824"></a>
<table><thead align="left"><tr id="row977121179084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p28445548084824"><a name="p28445548084824"></a><a name="p28445548084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1568578621084824"><a name="p1568578621084824"></a><a name="p1568578621084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row719787280084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131229783084824"><a name="p2131229783084824"></a><a name="p2131229783084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1489847328084824"><a name="p1489847328084824"></a><a name="p1489847328084824"></a>The associated mutex is invalid. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_condattr\_destroy\(\)<a name="ga8ab009937339c899a5197eea2e48e6a1"></a>

```
int pthread_condattr_destroy (pthread_condattr_t * a)
```

 **Description:**

Destroys a condition variable attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table116347124084824"></a>
<table><thead align="left"><tr id="row188000355084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p277442479084824"><a name="p277442479084824"></a><a name="p277442479084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1384953790084824"><a name="p1384953790084824"></a><a name="p1384953790084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1765650258084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable that contains the condition variable attributes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_condattr\_getclock\(\)<a name="gadcf908971c2ea15ced780025772084e3"></a>

```
int pthread_condattr_getclock (const pthread_condattr_t *__restrict a, clockid_t *__restrict clk )
```

 **Description:**

Obtains the clock of a condition variable attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table812028473084824"></a>
<table><thead align="left"><tr id="row1745811910084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1247304737084824"><a name="p1247304737084824"></a><a name="p1247304737084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p536278397084824"><a name="p536278397084824"></a><a name="p536278397084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1895482576084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable that contains the condition variable attributes. </td>
</tr>
<tr id="row1477718354084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">clk</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained clock ID. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_condattr\_init\(\)<a name="ga487a919ab54fd47c8464507031957df0"></a>

```
int pthread_condattr_init (pthread_condattr_t * a)
```

 **Description:**

Initializes a condition variable attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table147978640084824"></a>
<table><thead align="left"><tr id="row244067104084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1559278616084824"><a name="p1559278616084824"></a><a name="p1559278616084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p238215409084824"><a name="p238215409084824"></a><a name="p238215409084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1869287225084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable that contains the condition variable attributes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_condattr\_setclock\(\)<a name="gaaf7ac0f85233c0effaf850a9c65b6d68"></a>

```
int pthread_condattr_setclock (pthread_condattr_t * a, clockid_t clk )
```

 **Description:**

Sets a clock for a condition variable attribute object. 

**Parameters:**

<a name="table456760175084824"></a>
<table><thead align="left"><tr id="row527416521084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1915876632084824"><a name="p1915876632084824"></a><a name="p1915876632084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p663226040084824"><a name="p663226040084824"></a><a name="p663226040084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1677163352084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable that contains the condition variable attributes. </td>
</tr>
<tr id="row1053907015084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">clk</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the clock to set. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1548255886084824"></a>
<table><thead align="left"><tr id="row960484982084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p580080636084824"><a name="p580080636084824"></a><a name="p580080636084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p154349035084824"><a name="p154349035084824"></a><a name="p154349035084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row693150617084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p881491999084824"><a name="p881491999084824"></a><a name="p881491999084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501631077084824"><a name="p1501631077084824"></a><a name="p1501631077084824"></a>Invalid <strong id="b1480956388084824"><a name="b1480956388084824"></a><a name="b1480956388084824"></a>clk&gt; value. </strong></p>
</td>
</tr>
</tbody>
</table>

## pthread\_create\(\)<a name="gae5d18438d4d20c8a2e42cd2500578d79"></a>

```
int pthread_create (pthread_t * thread, const pthread_attr_t * attr, void *(*)(void *) start_routine, void * arg )
```

 **Description:**

Creates a thread. 

This function creates a thread in the calling process. The new thread starts execution from the entry point  **star\_routine**.  **arg**  is passed as the unique argument of the entry point. 

**Parameters:**

<a name="table1094393601084824"></a>
<table><thead align="left"><tr id="row91300803084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p304228201084824"><a name="p304228201084824"></a><a name="p304228201084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1179749995084824"><a name="p1179749995084824"></a><a name="p1179749995084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1400604522084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the thread ID. </td>
</tr>
<tr id="row509033323084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread attribute object. If this parameter is set to <strong id="b178327149084824"><a name="b178327149084824"></a><a name="b178327149084824"></a>NULL</strong>, the default thread attributes are used. </td>
</tr>
<tr id="row518405403084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">start_routine</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the entry point of the thread. </td>
</tr>
<tr id="row378235462084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">arg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Functions as the unique argument of <strong id="b1952170176084824"><a name="b1952170176084824"></a><a name="b1952170176084824"></a>start_routine</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table632266589084824"></a>
<table><thead align="left"><tr id="row1671943990084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1675515335084824"><a name="p1675515335084824"></a><a name="p1675515335084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1335906377084824"><a name="p1335906377084824"></a><a name="p1335906377084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row410943385084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p19190158084824"><a name="p19190158084824"></a><a name="p19190158084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p546504751084824"><a name="p546504751084824"></a><a name="p546504751084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row68409469084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p499179616084824"><a name="p499179616084824"></a><a name="p499179616084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359840135084824"><a name="p359840135084824"></a><a name="p359840135084824"></a>Insufficient resource, or the maximum number of threads allowed by the system reached. </p>
</td>
</tr>
<tr id="row1841834681084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1122653817084824"><a name="p1122653817084824"></a><a name="p1122653817084824"></a>ENOSYS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1549410044084824"><a name="p1549410044084824"></a><a name="p1549410044084824"></a>Unsupported system call. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_detach\(\)<a name="ga7c275c509c26566b6dd95a2de1668a2f"></a>

```
int pthread_detach (pthread_t thread)
```

 **Description:**

Detaches a thread. 

 

**Parameters:**

<a name="table305962765084824"></a>
<table><thead align="left"><tr id="row1742618534084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1908620645084824"><a name="p1908620645084824"></a><a name="p1908620645084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2147471222084824"><a name="p2147471222084824"></a><a name="p2147471222084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row675413150084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the user-level thread to detach. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1360864000084824"></a>
<table><thead align="left"><tr id="row628111307084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1053218836084824"><a name="p1053218836084824"></a><a name="p1053218836084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1716542571084824"><a name="p1716542571084824"></a><a name="p1716542571084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row534694372084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1690176650084824"><a name="p1690176650084824"></a><a name="p1690176650084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p263780901084824"><a name="p263780901084824"></a><a name="p263780901084824"></a>The thread is not joinable. </p>
</td>
</tr>
<tr id="row1503836208084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2039692378084824"><a name="p2039692378084824"></a><a name="p2039692378084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p949048702084824"><a name="p949048702084824"></a><a name="p949048702084824"></a>Invalid thread ID. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_equal\(\)<a name="ga98ec817164a6641eda2341de473b659d"></a>

```
int pthread_equal (pthread_t t1, pthread_t t2 )
```

 **Description:**

Compares whether two thread IDs are equal. 

**Parameters:**

<a name="table104085586084824"></a>
<table><thead align="left"><tr id="row1020311807084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p40084871084824"><a name="p40084871084824"></a><a name="p40084871084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1125907949084824"><a name="p1125907949084824"></a><a name="p1125907949084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row388103056084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">t1</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the first thread. </td>
</tr>
<tr id="row1624192537084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">t2</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the second thread. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the two are not equal; returns a non-zero value otherwise. 



## pthread\_exit\(\)<a name="gaadfb4e5de5a20880c6a40d4e73ce2597"></a>

```
_Noreturn void pthread_exit (void * retval)
```

 **Description:**

Terminates the calling thread. 

**Parameters:**

<a name="table1440184684084824"></a>
<table><thead align="left"><tr id="row215921690084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1256170355084824"><a name="p1256170355084824"></a><a name="p1256170355084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p469896264084824"><a name="p469896264084824"></a><a name="p469896264084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1782474122084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">retval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the return value after the thread is terminated. </td>
</tr>
</tbody>
</table>

## pthread\_getattr\_np\(\)<a name="ga6bdca4b2c8a436c4651fb5e8d462408b"></a>

```
int pthread_getattr_np (pthread_t thread, pthread_attr_t * attr )
```

 **Description:**

Obtains the attributes of a created thread. 

This function always succeeds. 

**Parameters:**

<a name="table1356055696084824"></a>
<table><thead align="left"><tr id="row1234902547084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1350227582084824"><a name="p1350227582084824"></a><a name="p1350227582084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p728556454084824"><a name="p728556454084824"></a><a name="p728556454084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1808902719084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread that has been created. </td>
</tr>
<tr id="row500566356084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the attribute values that describe the running thread. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_getschedparam\(\)<a name="gaae9850b3759769c748727e171c4c6e61"></a>

```
int pthread_getschedparam (pthread_t thread, int * policy, struct [sched_param](sched_param.md) * param )
```

 **Description:**

Obtains the scheduling policy and parameters of a thread. 

**Parameters:**

<a name="table2130939130084824"></a>
<table><thead align="left"><tr id="row1663479498084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1940091847084824"><a name="p1940091847084824"></a><a name="p1940091847084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p957381297084824"><a name="p957381297084824"></a><a name="p957381297084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row854939192084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target thread. </td>
</tr>
<tr id="row631521136084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">policy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling policy. The value can only be <strong id="b817503777084824"><a name="b817503777084824"></a><a name="b817503777084824"></a>SCHED_FIFO</strong> or <strong id="b2082147799084824"><a name="b2082147799084824"></a><a name="b2082147799084824"></a>SCHED_RR</strong>. </td>
</tr>
<tr id="row327984054084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling parameters. Only the thread priority is supported. The priority ranges from 0 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table2039816900084824"></a>
<table><thead align="left"><tr id="row490225812084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1339978088084824"><a name="p1339978088084824"></a><a name="p1339978088084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p374009861084824"><a name="p374009861084824"></a><a name="p374009861084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1800373278084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476428121084824"><a name="p476428121084824"></a><a name="p476428121084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p259821171084824"><a name="p259821171084824"></a><a name="p259821171084824"></a>Invalid thread ID. </p>
</td>
</tr>
<tr id="row916843138084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34915974084824"><a name="p34915974084824"></a><a name="p34915974084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538622003084824"><a name="p1538622003084824"></a><a name="p1538622003084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1952120460084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1361405155084824"><a name="p1361405155084824"></a><a name="p1361405155084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p386076044084824"><a name="p386076044084824"></a><a name="p386076044084824"></a>No permission to obtain the specified scheduling policy and parameters. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_getspecific\(\)<a name="ga31469375891078185bda93f0e4411a2c"></a>

```
void* pthread_getspecific (pthread_key_t key)
```

 **Description:**

Obtains specific thread data. 

**Parameters:**

<a name="table304105357084824"></a>
<table><thead align="left"><tr id="row1614818830084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p234893945084824"><a name="p234893945084824"></a><a name="p234893945084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p65011683084824"><a name="p65011683084824"></a><a name="p65011683084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1712070019084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key bound to the thread data. </td>
</tr>
</tbody>
</table>

## pthread\_join\(\)<a name="ga28a15bba47cab57cbc9f5dac9af99c8b"></a>

```
int pthread_join (pthread_t thread, void ** retval )
```

 **Description:**

Waits for a thread to terminate. 

This function returns a value immediately if the thread has already terminated. 

**Parameters:**

<a name="table1710637811084824"></a>
<table><thead align="left"><tr id="row478603138084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1360049996084824"><a name="p1360049996084824"></a><a name="p1360049996084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1342833571084824"><a name="p1342833571084824"></a><a name="p1342833571084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row625875828084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target thread. </td>
</tr>
<tr id="row819988091084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">retval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the exit or cancellation status of the target thread. This parameter can be <strong id="b1203453011084824"><a name="b1203453011084824"></a><a name="b1203453011084824"></a>NULL</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1406676300084824"></a>
<table><thead align="left"><tr id="row1506449724084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p73530762084824"><a name="p73530762084824"></a><a name="p73530762084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p143171685084824"><a name="p143171685084824"></a><a name="p143171685084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2113596711084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204812344084824"><a name="p1204812344084824"></a><a name="p1204812344084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2106502850084824"><a name="p2106502850084824"></a><a name="p2106502850084824"></a>The thread is not joinable, or the target thread is the calling thread. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_key\_create\(\)<a name="gaf4b7ced8ecff505380fe8216244a3764"></a>

```
int pthread_key_create (pthread_key_t * key, void(*)(void *) destructor )
```

 **Description:**

Creates a key for thread data. 

**Parameters:**

<a name="table1890714156084824"></a>
<table><thead align="left"><tr id="row248401362084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p879322249084824"><a name="p879322249084824"></a><a name="p879322249084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p313985558084824"><a name="p313985558084824"></a><a name="p313985558084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1913750077084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the key to set for the thread data. </td>
</tr>
<tr id="row1528344694084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">destructor</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the function to be bound to the key. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1233387431084824"></a>
<table><thead align="left"><tr id="row114335994084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1402783789084824"><a name="p1402783789084824"></a><a name="p1402783789084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p938846421084824"><a name="p938846421084824"></a><a name="p938846421084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row608579025084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1384377860084824"><a name="p1384377860084824"></a><a name="p1384377860084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640079510084824"><a name="p1640079510084824"></a><a name="p1640079510084824"></a>The system lacks the necessary resources to create another thread-specific key, or the number of keys exceeds the limit specified by <strong id="b898762430084824"><a name="b898762430084824"></a><a name="b898762430084824"></a>PTHREAD_KEYS_MAX</strong> for each process. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_key\_delete\(\)<a name="gaee96306dc79294927ee840bb4de2244b"></a>

```
int pthread_key_delete (pthread_key_t key)
```

 **Description:**

Deletes a key for thread data. 

**Parameters:**

<a name="table1938829571084824"></a>
<table><thead align="left"><tr id="row1429357530084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p737437161084824"><a name="p737437161084824"></a><a name="p737437161084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1290547101084824"><a name="p1290547101084824"></a><a name="p1290547101084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1585397397084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the key to delete for the thread data. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1506613932084824"></a>
<table><thead align="left"><tr id="row92938400084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p241649362084824"><a name="p241649362084824"></a><a name="p241649362084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1494366203084824"><a name="p1494366203084824"></a><a name="p1494366203084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1687922410084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080868220084824"><a name="p2080868220084824"></a><a name="p2080868220084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p794709477084824"><a name="p794709477084824"></a><a name="p794709477084824"></a>Invalid key. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_kill\(\)<a name="ga5aafacc071cdfafd0eb992004dee3e62"></a>

```
int pthread_kill (pthread_t thread, int sig )
```

 **Description:**

Sends a signal to a thread. 

If  **sig**  is  **0**, no signal is sent, but error checking is still performed. Therefore, you can call this function with  **sig**  set to  **0**  to check whether a thread exists. 

**Parameters:**

<a name="table130256352084824"></a>
<table><thead align="left"><tr id="row2134377707084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p209262979084824"><a name="p209262979084824"></a><a name="p209262979084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1475089072084824"><a name="p1475089072084824"></a><a name="p1475089072084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row788097211084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread to receive the signal. </td>
</tr>
<tr id="row659010149084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sig</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal to send. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1311395870084824"></a>
<table><thead align="left"><tr id="row621828509084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1646731111084824"><a name="p1646731111084824"></a><a name="p1646731111084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1169269963084824"><a name="p1169269963084824"></a><a name="p1169269963084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1673354710084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p239672936084824"><a name="p239672936084824"></a><a name="p239672936084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1738215051084824"><a name="p1738215051084824"></a><a name="p1738215051084824"></a>Invalid signal. </p>
</td>
</tr>
<tr id="row427751104084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1108614206084824"><a name="p1108614206084824"></a><a name="p1108614206084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1781989631084824"><a name="p1781989631084824"></a><a name="p1781989631084824"></a>Invalid thread ID. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_mutex\_destroy\(\)<a name="gaf89d9cfa300f33b46720a96eac83d175"></a>

```
int pthread_mutex_destroy (pthread_mutex_t * m)
```

 **Description:**

Destroys a mutex. 

This function always succeeds. 

**Parameters:**

<a name="table1187297274084824"></a>
<table><thead align="left"><tr id="row555505678084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1978273195084824"><a name="p1978273195084824"></a><a name="p1978273195084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p251916987084824"><a name="p251916987084824"></a><a name="p251916987084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row381199550084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_mutex\_init\(\)<a name="gadd99221596e95a55f70c59c1c712bbde"></a>

```
int pthread_mutex_init (pthread_mutex_t *__restrict m, const pthread_mutexattr_t *__restrict a )
```

 **Description:**

Initializes a mutex. 

This function dynamically creates a mutex. The parameter  **a**  specifies the attributes of the mutex. This function always succeeds. 

**Parameters:**

<a name="table1249326199084824"></a>
<table><thead align="left"><tr id="row1783192724084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p274107627084824"><a name="p274107627084824"></a><a name="p274107627084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p998820158084824"><a name="p998820158084824"></a><a name="p998820158084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1430160295084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex to initialize. </td>
</tr>
<tr id="row31169427084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex attribute object. If this parameter is set to <strong id="b541175565084824"><a name="b541175565084824"></a><a name="b541175565084824"></a>NULL</strong>, the default mutex attributes are used. The default attributes indicate a fast mutex. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_mutex\_lock\(\)<a name="gafd70d6f2c50e22b996c926fb9d6ad291"></a>

```
int pthread_mutex_lock (pthread_mutex_t * m)
```

 **Description:**

Locks a mutex. 

If the mutex is already locked by a thread, the call is blocked until the holding thread unlocks the mutex by calling  [pthread\_mutex\_unlock\(\)](PROCESS.md#ga02a3c64dac70730e226c31c0e7dbb45c). 

**Parameters:**

<a name="table2144735325084824"></a>
<table><thead align="left"><tr id="row82374337084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1806301495084824"><a name="p1806301495084824"></a><a name="p1806301495084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p766791606084824"><a name="p766791606084824"></a><a name="p766791606084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row561377586084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex to lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table651312142084824"></a>
<table><thead align="left"><tr id="row1663914357084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1071631517084824"><a name="p1071631517084824"></a><a name="p1071631517084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1464647204084824"><a name="p1464647204084824"></a><a name="p1464647204084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1711094363084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1891170639084824"><a name="p1891170639084824"></a><a name="p1891170639084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p25992430084824"><a name="p25992430084824"></a><a name="p25992430084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row2069860237084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1095884281084824"><a name="p1095884281084824"></a><a name="p1095884281084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699456261084824"><a name="p1699456261084824"></a><a name="p1699456261084824"></a>The mutex has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row2062465161084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p863754052084824"><a name="p863754052084824"></a><a name="p863754052084824"></a>EDEADLK </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1289993524084824"><a name="p1289993524084824"></a><a name="p1289993524084824"></a>The thread attempts to relock the mutex that it has already locked, and the mutex is of the error check mutex type. </p>
</td>
</tr>
<tr id="row591386488084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1359616265084824"><a name="p1359616265084824"></a><a name="p1359616265084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1509552217084824"><a name="p1509552217084824"></a><a name="p1509552217084824"></a>The maximum number of recursive locks for the mutex has been exceeded. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_mutex\_timedlock\(\)<a name="gabc6a044b418e942b91121b1babb61708"></a>

```
int pthread_mutex_timedlock (pthread_mutex_t *__restrict m, const struct [timespec](timespec.md) *__restrict at )
```

 **Description:**

Blocks the calling thread to lock a mutex. 

If the mutex is already locked, the call is blocked until the specified timeout duration expires or the holding thread unlocks the mutex by calling  [pthread\_mutex\_unlock\(\)](PROCESS.md#ga02a3c64dac70730e226c31c0e7dbb45c). 

**Parameters:**

<a name="table1251379955084824"></a>
<table><thead align="left"><tr id="row1983658504084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1274928726084824"><a name="p1274928726084824"></a><a name="p1274928726084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1142925346084824"><a name="p1142925346084824"></a><a name="p1142925346084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row714830775084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex to lock. </td>
</tr>
<tr id="row1224462761084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">at</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the maximum duration that the calling thread waits for the mutex. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1939329476084824"></a>
<table><thead align="left"><tr id="row670380827084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p119650069084824"><a name="p119650069084824"></a><a name="p119650069084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2134573290084824"><a name="p2134573290084824"></a><a name="p2134573290084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1742824855084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898663016084824"><a name="p1898663016084824"></a><a name="p1898663016084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1548692395084824"><a name="p1548692395084824"></a><a name="p1548692395084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row560701084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p914122288084824"><a name="p914122288084824"></a><a name="p914122288084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p762824637084824"><a name="p762824637084824"></a><a name="p762824637084824"></a>The mutex has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row1875449319084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199555219084824"><a name="p1199555219084824"></a><a name="p1199555219084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45591242084824"><a name="p45591242084824"></a><a name="p45591242084824"></a>The mutex is already locked. </p>
</td>
</tr>
<tr id="row314997803084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701339545084824"><a name="p701339545084824"></a><a name="p701339545084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p361344852084824"><a name="p361344852084824"></a><a name="p361344852084824"></a>The maximum number of recursive locks for the mutex has been exceeded. </p>
</td>
</tr>
<tr id="row1186505820084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422042054084824"><a name="p422042054084824"></a><a name="p422042054084824"></a>ETIMEDOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107415360084824"><a name="p107415360084824"></a><a name="p107415360084824"></a>The mutex cannot be acquired within the specified period of time. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_mutex\_trylock\(\)<a name="gacc1ccbaf3d76572da85a8030bba1ede4"></a>

```
int pthread_mutex_trylock (pthread_mutex_t * m)
```

 **Description:**

Attempts to lock a mutex. 

This function attempts to acquire a mutex, without blocking the calling thread. If the mutex is already locked, the error code  **EBUSY**  is returned immediately. 

**Parameters:**

<a name="table1513301661084824"></a>
<table><thead align="left"><tr id="row2074096900084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p421382102084824"><a name="p421382102084824"></a><a name="p421382102084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1815714703084824"><a name="p1815714703084824"></a><a name="p1815714703084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1905899798084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex to lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table805271607084824"></a>
<table><thead align="left"><tr id="row873991344084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1827072626084824"><a name="p1827072626084824"></a><a name="p1827072626084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1448312541084824"><a name="p1448312541084824"></a><a name="p1448312541084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row917925866084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p467395408084824"><a name="p467395408084824"></a><a name="p467395408084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2046993795084824"><a name="p2046993795084824"></a><a name="p2046993795084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row420039206084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858259622084824"><a name="p858259622084824"></a><a name="p858259622084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994158003084824"><a name="p1994158003084824"></a><a name="p1994158003084824"></a>The mutex has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row1188753891084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p437269480084824"><a name="p437269480084824"></a><a name="p437269480084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p822990214084824"><a name="p822990214084824"></a><a name="p822990214084824"></a>The mutex is already locked. </p>
</td>
</tr>
<tr id="row950439614084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106993107084824"><a name="p1106993107084824"></a><a name="p1106993107084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p408390188084824"><a name="p408390188084824"></a><a name="p408390188084824"></a>The maximum number of recursive locks for the mutex has been exceeded. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_mutex\_unlock\(\)<a name="ga02a3c64dac70730e226c31c0e7dbb45c"></a>

```
int pthread_mutex_unlock (pthread_mutex_t * m)
```

 **Description:**

Unlocks a mutex. 

If the calling thread attempts to unlock a mutex that it has not locked \(by calling  [pthread\_mutex\_lock\(\)](PROCESS.md#gafd70d6f2c50e22b996c926fb9d6ad291),  [pthread\_mutex\_trylock\(\)](PROCESS.md#gacc1ccbaf3d76572da85a8030bba1ede4), or  **pthread\_mutex\_timedlock\_np\(\)**, the unlock request fails and the error code  **EPERM**  is returned. 

**Parameters:**

<a name="table640877058084824"></a>
<table><thead align="left"><tr id="row1942815835084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p452994897084824"><a name="p452994897084824"></a><a name="p452994897084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p697527190084824"><a name="p697527190084824"></a><a name="p697527190084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row156877855084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">m</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex to unlock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1349565043084824"></a>
<table><thead align="left"><tr id="row1800500978084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1301237297084824"><a name="p1301237297084824"></a><a name="p1301237297084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p816791443084824"><a name="p816791443084824"></a><a name="p816791443084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1460761018084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701589589084824"><a name="p701589589084824"></a><a name="p701589589084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737253986084824"><a name="p1737253986084824"></a><a name="p1737253986084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row1319365406084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479863123084824"><a name="p479863123084824"></a><a name="p479863123084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989520479084824"><a name="p1989520479084824"></a><a name="p1989520479084824"></a>The mutex has not been locked by the calling thread. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_mutexattr\_destroy\(\)<a name="ga2321aabf58224b06021185708d0f9658"></a>

```
int pthread_mutexattr_destroy (pthread_mutexattr_t * attr)
```

 **Description:**

Destroys a mutex attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table20592986084824"></a>
<table><thead align="left"><tr id="row1964216579084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1166031515084824"><a name="p1166031515084824"></a><a name="p1166031515084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p764984305084824"><a name="p764984305084824"></a><a name="p764984305084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row274411992084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target mutex attribute object. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_mutexattr\_gettype\(\)<a name="ga4789e2d3ada7aab2af1458bfec53ee3c"></a>

```
int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict attr, int *__restrict type )
```

 **Description:**

Obtains the mutex type attribute. 

This function always succeeds. 

**Parameters:**

<a name="table1673013906084824"></a>
<table><thead align="left"><tr id="row707462009084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2074974057084824"><a name="p2074974057084824"></a><a name="p2074974057084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2094820224084824"><a name="p2094820224084824"></a><a name="p2094820224084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row240825851084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex attribute object. </td>
</tr>
<tr id="row994707105084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained mutex type attribute. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_mutexattr\_init\(\)<a name="gaf98f6b6c483077a39d1400b1de1577b8"></a>

```
int pthread_mutexattr_init (pthread_mutexattr_t * attr)
```

 **Description:**

Initializes a mutex attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1201292800084824"></a>
<table><thead align="left"><tr id="row1812742208084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1604211454084824"><a name="p1604211454084824"></a><a name="p1604211454084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2015406547084824"><a name="p2015406547084824"></a><a name="p2015406547084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1495783690084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target mutex attribute object. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_mutexattr\_settype\(\)<a name="ga8387c80e660e9426f801ac0217ecfae5"></a>

```
int pthread_mutexattr_settype (pthread_mutexattr_t * attr, int type )
```

 **Description:**

Sets the mutex type attribute. 

**Parameters:**

<a name="table271285672084824"></a>
<table><thead align="left"><tr id="row405631784084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p32347186084824"><a name="p32347186084824"></a><a name="p32347186084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p707189770084824"><a name="p707189770084824"></a><a name="p707189770084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row148610137084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the mutex attribute object. </td>
</tr>
<tr id="row180901266084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the mutex. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1759374746084824"></a>
<table><thead align="left"><tr id="row1623464091084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1945863889084824"><a name="p1945863889084824"></a><a name="p1945863889084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p416064720084824"><a name="p416064720084824"></a><a name="p416064720084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1905212481084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1213343685084824"><a name="p1213343685084824"></a><a name="p1213343685084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443592451084824"><a name="p1443592451084824"></a><a name="p1443592451084824"></a>Invalid mutex type attribute. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_once\(\)<a name="ga196103ac97710dad7a93fd6c188cc999"></a>

```
int pthread_once (pthread_once_t * once_control, void(*)(void) init_routine )
```

 **Description:**

Enables the initialization function to be called only once. 

This function dynamically initializes the function specified by  **init\_routine**  and ensures that it will be called only once. 

**Parameters:**

<a name="table736091387084824"></a>
<table><thead align="left"><tr id="row169707694084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1562937241084824"><a name="p1562937241084824"></a><a name="p1562937241084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1905044798084824"><a name="p1905044798084824"></a><a name="p1905044798084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2078386644084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">once_control</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a variable specifying the execution status. The value <strong id="b823465863084824"><a name="b823465863084824"></a><a name="b823465863084824"></a>0</strong> means <strong id="b32813000084824"><a name="b32813000084824"></a><a name="b32813000084824"></a>NEVER</strong>, <strong id="b1377499028084824"><a name="b1377499028084824"></a><a name="b1377499028084824"></a>1</strong> means <strong id="b1619545548084824"><a name="b1619545548084824"></a><a name="b1619545548084824"></a>IN PROGRESS</strong>, and <strong id="b1649510106084824"><a name="b1649510106084824"></a><a name="b1649510106084824"></a>2</strong> means <strong id="b500417073084824"><a name="b500417073084824"></a><a name="b500417073084824"></a>DONE</strong>. </td>
</tr>
<tr id="row1357932294084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">init_routine</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the function that you want to call for any required initialization. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if  **once\_control**  is set to  **0**  or  **2**. If  **once\_control**  is  **1**, the calling thread waits until the other thread completes initialization. 



## pthread\_rwlock\_destroy\(\)<a name="gaa106bb55bdd0e120519d5412823f8b29"></a>

```
int pthread_rwlock_destroy (pthread_rwlock_t * rw)
```

 **Description:**

Destroys a read-write lock. 

This function always succeeds. 

**Parameters:**

<a name="table1060416494084824"></a>
<table><thead align="left"><tr id="row262756304084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1301005076084824"><a name="p1301005076084824"></a><a name="p1301005076084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p978925484084824"><a name="p978925484084824"></a><a name="p978925484084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2061396812084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_rwlock\_init\(\)<a name="ga1cf4bc49696c1a30db31219aef994401"></a>

```
int pthread_rwlock_init (pthread_rwlock_t *__restrict rw, const pthread_rwlockattr_t *__restrict a )
```

 **Description:**

Initializes a read-write lock. 

This function always succeeds. 

**Parameters:**

<a name="table1102181117084824"></a>
<table><thead align="left"><tr id="row1229434645084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p372973941084824"><a name="p372973941084824"></a><a name="p372973941084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1024222071084824"><a name="p1024222071084824"></a><a name="p1024222071084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1601848441084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to initialize. </td>
</tr>
<tr id="row603218247084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">a</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock attribute object. If this parameter is set to <strong id="b27000443084824"><a name="b27000443084824"></a><a name="b27000443084824"></a>NULL</strong>, the default read-write lock attributes are used. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_rwlock\_rdlock\(\)<a name="ga6153aca32112735053e6cc4a2a290feb"></a>

```
int pthread_rwlock_rdlock (pthread_rwlock_t * rw)
```

 **Description:**

Applies a read lock to a read-write lock. 

**Parameters:**

<a name="table1152787126084824"></a>
<table><thead align="left"><tr id="row2019134155084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p488254451084824"><a name="p488254451084824"></a><a name="p488254451084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1300504026084824"><a name="p1300504026084824"></a><a name="p1300504026084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1796424308084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target read-write lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1734185353084824"></a>
<table><thead align="left"><tr id="row940742185084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1947016812084824"><a name="p1947016812084824"></a><a name="p1947016812084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1344811373084824"><a name="p1344811373084824"></a><a name="p1344811373084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row458515721084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p326035226084824"><a name="p326035226084824"></a><a name="p326035226084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929609044084824"><a name="p929609044084824"></a><a name="p929609044084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row1414749679084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p990676834084824"><a name="p990676834084824"></a><a name="p990676834084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533681948084824"><a name="p1533681948084824"></a><a name="p1533681948084824"></a>The read-write lock has been damaged during the waiting. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlock\_timedrdlock\(\)<a name="ga8edbe14731fd79a80f72384334266715"></a>

```
int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict rw, const struct [timespec](timespec.md) *__restrict at )
```

 **Description:**

Blocks the calling thread to lock a read-write lock for reading. 

If the read-write lock is already locked, the calling thread is blocked until the specified timeout duration expires or the holding thread unlocks the read-write lock by calling  [pthread\_rwlock\_unlock\(\)](PROCESS.md#gaffd8a19e83fc87d865d103d6fbce8c4f). 

**Parameters:**

<a name="table1403535164084824"></a>
<table><thead align="left"><tr id="row1092982807084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p646060719084824"><a name="p646060719084824"></a><a name="p646060719084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p952329702084824"><a name="p952329702084824"></a><a name="p952329702084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row630607907084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to lock. </td>
</tr>
<tr id="row115810055084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">at</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum duration that the calling thread waits for the read-write lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table2131527126084824"></a>
<table><thead align="left"><tr id="row1641870098084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p41811619084824"><a name="p41811619084824"></a><a name="p41811619084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p107390483084824"><a name="p107390483084824"></a><a name="p107390483084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2090181174084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977441781084824"><a name="p977441781084824"></a><a name="p977441781084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1439178228084824"><a name="p1439178228084824"></a><a name="p1439178228084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row1950040490084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p333309125084824"><a name="p333309125084824"></a><a name="p333309125084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681318155084824"><a name="p1681318155084824"></a><a name="p1681318155084824"></a>The read-write lock has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row1518033230084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p614594805084824"><a name="p614594805084824"></a><a name="p614594805084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649477073084824"><a name="p649477073084824"></a><a name="p649477073084824"></a>The read-write lock is already locked. </p>
</td>
</tr>
<tr id="row739269017084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382263296084824"><a name="p382263296084824"></a><a name="p382263296084824"></a>ETIMEDOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435296619084824"><a name="p1435296619084824"></a><a name="p1435296619084824"></a>The read-write lock cannot be acquired within the specified period of time. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlock\_timedwrlock\(\)<a name="ga3fb8fb33e16653c5ad7b7f092959738e"></a>

```
int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict rw, const struct [timespec](timespec.md) *__restrict at )
```

 **Description:**

Blocks the calling thread to lock a read-write lock for writing. 

If the read-write lock is already locked, the calling thread is blocked until the specified timeout duration expires or the holding thread unlocks the read-write lock by calling  [pthread\_rwlock\_unlock\(\)](PROCESS.md#gaffd8a19e83fc87d865d103d6fbce8c4f). 

**Parameters:**

<a name="table926226752084824"></a>
<table><thead align="left"><tr id="row1791398607084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p549487376084824"><a name="p549487376084824"></a><a name="p549487376084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p570507622084824"><a name="p570507622084824"></a><a name="p570507622084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row755552872084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to lock. </td>
</tr>
<tr id="row641375915084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">at</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the maximum duration that the calling thread waits for the read-write lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table54870108084824"></a>
<table><thead align="left"><tr id="row474043251084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1420862672084824"><a name="p1420862672084824"></a><a name="p1420862672084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1980300892084824"><a name="p1980300892084824"></a><a name="p1980300892084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1369799458084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1030737722084824"><a name="p1030737722084824"></a><a name="p1030737722084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1051533949084824"><a name="p1051533949084824"></a><a name="p1051533949084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row1935012692084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1622642431084824"><a name="p1622642431084824"></a><a name="p1622642431084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090458210084824"><a name="p1090458210084824"></a><a name="p1090458210084824"></a>The read-write lock has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row2051257234084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1691895147084824"><a name="p1691895147084824"></a><a name="p1691895147084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1070618916084824"><a name="p1070618916084824"></a><a name="p1070618916084824"></a>The read-write lock is already locked. </p>
</td>
</tr>
<tr id="row383772433084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p79285911084824"><a name="p79285911084824"></a><a name="p79285911084824"></a>ETIMEDOUT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p226822175084824"><a name="p226822175084824"></a><a name="p226822175084824"></a>The read-write lock cannot be acquired within the specified period of time. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlock\_tryrdlock\(\)<a name="ga3ba2170f06184d12543c4a5b78715fa7"></a>

```
int pthread_rwlock_tryrdlock (pthread_rwlock_t * rw)
```

 **Description:**

Attempts to apply a read lock to a read-write lock. 

This function attempts to lock a read-write lock for reading, without blocking the calling thread. If the read-write lock is already locked, the error code  **EBUSY**  is returned immediately. 

**Parameters:**

<a name="table794769450084824"></a>
<table><thead align="left"><tr id="row1826774608084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p347265064084824"><a name="p347265064084824"></a><a name="p347265064084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p825671912084824"><a name="p825671912084824"></a><a name="p825671912084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row998936845084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target read-write lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table891370405084824"></a>
<table><thead align="left"><tr id="row2109678098084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p555086591084824"><a name="p555086591084824"></a><a name="p555086591084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p726419734084824"><a name="p726419734084824"></a><a name="p726419734084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2040240147084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319921355084824"><a name="p319921355084824"></a><a name="p319921355084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554930532084824"><a name="p1554930532084824"></a><a name="p1554930532084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row566703677084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982954861084824"><a name="p982954861084824"></a><a name="p982954861084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731545776084824"><a name="p731545776084824"></a><a name="p731545776084824"></a>The read-write lock has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row291529930084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p913711613084824"><a name="p913711613084824"></a><a name="p913711613084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041685801084824"><a name="p1041685801084824"></a><a name="p1041685801084824"></a>The read-write lock is already locked. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlock\_trywrlock\(\)<a name="ga2b5044e2da304ae9666fdd4e05479905"></a>

```
int pthread_rwlock_trywrlock (pthread_rwlock_t * rw)
```

 **Description:**

Attempts to apply a write lock to a read-write lock. 

This function attempts to lock a read-write lock for writing, without blocking the calling thread. If the read-write lock is already locked, the error code  **EBUSY**  is returned immediately. 

**Parameters:**

<a name="table734855661084824"></a>
<table><thead align="left"><tr id="row765145665084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1747492800084824"><a name="p1747492800084824"></a><a name="p1747492800084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1863685025084824"><a name="p1863685025084824"></a><a name="p1863685025084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1585635059084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1221061627084824"></a>
<table><thead align="left"><tr id="row1067057706084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1593022275084824"><a name="p1593022275084824"></a><a name="p1593022275084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2009302582084824"><a name="p2009302582084824"></a><a name="p2009302582084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2089294858084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1625174821084824"><a name="p1625174821084824"></a><a name="p1625174821084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699894861084824"><a name="p1699894861084824"></a><a name="p1699894861084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row643628467084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p507008296084824"><a name="p507008296084824"></a><a name="p507008296084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p505879560084824"><a name="p505879560084824"></a><a name="p505879560084824"></a>The read-write lock has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row2103205934084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p592461405084824"><a name="p592461405084824"></a><a name="p592461405084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p597984209084824"><a name="p597984209084824"></a><a name="p597984209084824"></a>The read-write lock is already locked. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlock\_unlock\(\)<a name="gaffd8a19e83fc87d865d103d6fbce8c4f"></a>

```
int pthread_rwlock_unlock (pthread_rwlock_t * rw)
```

 **Description:**

Unlocks a read-write lock. 

If the calling thread attempts to unlock a read-write lock that it has not locked, the unlock request fails and the error code  **EPERM**  is returned. 

**Parameters:**

<a name="table2081363242084824"></a>
<table><thead align="left"><tr id="row1948152353084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1638056715084824"><a name="p1638056715084824"></a><a name="p1638056715084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p249058036084824"><a name="p249058036084824"></a><a name="p249058036084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row958230642084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to unlock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1257362839084824"></a>
<table><thead align="left"><tr id="row1737896338084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p471106824084824"><a name="p471106824084824"></a><a name="p471106824084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1934141218084824"><a name="p1934141218084824"></a><a name="p1934141218084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2015599450084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1728443361084824"><a name="p1728443361084824"></a><a name="p1728443361084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1239648578084824"><a name="p1239648578084824"></a><a name="p1239648578084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row1122643476084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1560856101084824"><a name="p1560856101084824"></a><a name="p1560856101084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1875975389084824"><a name="p1875975389084824"></a><a name="p1875975389084824"></a>The read-write lock is not held by the calling thread. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlock\_wrlock\(\)<a name="gaf2ca5563676ae3ac35d3bc7b3547e7f7"></a>

```
int pthread_rwlock_wrlock (pthread_rwlock_t * rw)
```

 **Description:**

Applies a write lock to a read-write lock. 

**Parameters:**

<a name="table298893795084824"></a>
<table><thead align="left"><tr id="row447678531084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1148064083084824"><a name="p1148064083084824"></a><a name="p1148064083084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1532679810084824"><a name="p1532679810084824"></a><a name="p1532679810084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1920462979084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock to lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1867512507084824"></a>
<table><thead align="left"><tr id="row1904964581084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1662009620084824"><a name="p1662009620084824"></a><a name="p1662009620084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1660220290084824"><a name="p1660220290084824"></a><a name="p1660220290084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1531957369084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974841802084824"><a name="p1974841802084824"></a><a name="p1974841802084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403378141084824"><a name="p1403378141084824"></a><a name="p1403378141084824"></a>Incorrect parameter value. </p>
</td>
</tr>
<tr id="row2090163362084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p495682113084824"><a name="p495682113084824"></a><a name="p495682113084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125113419084824"><a name="p2125113419084824"></a><a name="p2125113419084824"></a>The read-write lock has been damaged during the waiting. </p>
</td>
</tr>
<tr id="row1302937754084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1941024498084824"><a name="p1941024498084824"></a><a name="p1941024498084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p322227440084824"><a name="p322227440084824"></a><a name="p322227440084824"></a>The read-write lock is already locked. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_rwlockattr\_destroy\(\)<a name="ga78a54e67f0afe2601dbda0a904fa0bdf"></a>

```
int pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr)
```

 **Description:**

Destroys a read-write lock attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1997590666084824"></a>
<table><thead align="left"><tr id="row679165810084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1422162705084824"><a name="p1422162705084824"></a><a name="p1422162705084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1277015423084824"><a name="p1277015423084824"></a><a name="p1277015423084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1130117069084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock attribute object to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_rwlockattr\_init\(\)<a name="ga9d831af0179ed16d1b6cbeba0304810b"></a>

```
int pthread_rwlockattr_init (pthread_rwlockattr_t * attr)
```

 **Description:**

Initializes a read-write lock attribute object. 

This function always succeeds. 

**Parameters:**

<a name="table1955882870084824"></a>
<table><thead align="left"><tr id="row312743665084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p255746921084824"><a name="p255746921084824"></a><a name="p255746921084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1149553061084824"><a name="p1149553061084824"></a><a name="p1149553061084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row114832721084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read-write lock attribute object to initialize. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_self\(\)<a name="ga4c4f5f3b4f8f45d9d897847d53b11aaa"></a>

```
pthread_t pthread_self (void )
```

 **Description:**

Obtains the ID of the calling thread. 

This function always succeeds. 

**Returns:**

Returns the thread ID. 



## pthread\_setcancelstate\(\)<a name="ga37075410fbbaad7ee93c95375fc86e0e"></a>

```
int pthread_setcancelstate (int state, int * oldstate )
```

 **Description:**

Sets the cancelability state for the calling thread. 

This function sets the cancelability state of the calling thread to the value specified by  **state**. The previous cancelability state is stored in the buffer pointed to by oldstate. 

**Parameters:**

<a name="table579395525084824"></a>
<table><thead align="left"><tr id="row659857631084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1579872921084824"><a name="p1579872921084824"></a><a name="p1579872921084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1727488584084824"><a name="p1727488584084824"></a><a name="p1727488584084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1843576115084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">state</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the cancelability state to set. Available values are as follows: </td>
</tr>
<tr id="row1539967861084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oldstate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the previous cancelability state before the setting. </td>
</tr>
</tbody>
</table>

<a name="table738976431084824"></a>
<table><thead align="left"><tr id="row264119582084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1681267146084824"><a name="p1681267146084824"></a><a name="p1681267146084824"></a>state </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p522223731084824"><a name="p522223731084824"></a><a name="p522223731084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2011886048084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1189365610084824"><a name="p1189365610084824"></a><a name="p1189365610084824"></a>PTHREAD_CANCEL_ENABLE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354539825084824"><a name="p1354539825084824"></a><a name="p1354539825084824"></a>The thread is cancelable. </p>
</td>
</tr>
<tr id="row803197575084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p234158356084824"><a name="p234158356084824"></a><a name="p234158356084824"></a>PTHREAD_CANCEL_DISABLE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209267044084824"><a name="p1209267044084824"></a><a name="p1209267044084824"></a>The thread is not cancelable. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table770947369084824"></a>
<table><thead align="left"><tr id="row347787083084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p518725892084824"><a name="p518725892084824"></a><a name="p518725892084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1877299662084824"><a name="p1877299662084824"></a><a name="p1877299662084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2015192552084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413536659084824"><a name="p413536659084824"></a><a name="p413536659084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p300615155084824"><a name="p300615155084824"></a><a name="p300615155084824"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_setcanceltype\(\)<a name="gaab579bcfcf0662a0c1e35fd82162e61d"></a>

```
int pthread_setcanceltype (int type, int * oldtype )
```

 **Description:**

Sets the cancelability type for the calling thread. 

This function sets the cancelability type of the calling thread to the value specified by  **type**. The previous cancelability type is stored in the buffer pointed to by oldtype. 

**Parameters:**

<a name="table272808638084824"></a>
<table><thead align="left"><tr id="row1536633195084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p573979549084824"><a name="p573979549084824"></a><a name="p573979549084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1492460785084824"><a name="p1492460785084824"></a><a name="p1492460785084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1551962264084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the cancelability type to set. Available values are as follows: </td>
</tr>
<tr id="row2038382155084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oldtype</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the previous cancelability type before the setting. </td>
</tr>
</tbody>
</table>

<a name="table1988819745084824"></a>
<table><thead align="left"><tr id="row531765661084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p161003141084824"><a name="p161003141084824"></a><a name="p161003141084824"></a>type </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1017942272084824"><a name="p1017942272084824"></a><a name="p1017942272084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1929516163084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973575879084824"><a name="p973575879084824"></a><a name="p973575879084824"></a>PTHREAD_CANCEL_DEFERRED </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2092293178084824"><a name="p2092293178084824"></a><a name="p2092293178084824"></a>The thread is canceled until the next cancellation point. </p>
</td>
</tr>
<tr id="row1706208453084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712993118084824"><a name="p1712993118084824"></a><a name="p1712993118084824"></a>PTHREAD_CANCEL_ASYNCHRONOUS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756197303084824"><a name="p756197303084824"></a><a name="p756197303084824"></a>The thread is canceled immediately upon receiving a cancellation request. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1173909345084824"></a>
<table><thead align="left"><tr id="row1706364173084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p809279189084824"><a name="p809279189084824"></a><a name="p809279189084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1214788993084824"><a name="p1214788993084824"></a><a name="p1214788993084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1416803994084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2011169736084824"><a name="p2011169736084824"></a><a name="p2011169736084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257704841084824"><a name="p257704841084824"></a><a name="p257704841084824"></a>Invalid parameter. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_setname\_np\(\)<a name="ga185584d77295432838d8b839d916f160"></a>

```
int pthread_setname_np (pthread_t pthread, const char * name )
```

 **Description:**

Sets the thread name. 

**Parameters:**

<a name="table570535415084824"></a>
<table><thead align="left"><tr id="row1450574535084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p47471452084824"><a name="p47471452084824"></a><a name="p47471452084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p38138259084824"><a name="p38138259084824"></a><a name="p38138259084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1992558899084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the thread whose name is to be changed. </td>
</tr>
<tr id="row35263507084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread name to set. The value contains a maximum of 16 characters, including the terminating null byte ('\0'). </td>
</tr>
</tbody>
</table>

**Attention:**

Currently, a thread can change its own thread name only. 

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1053133472084824"></a>
<table><thead align="left"><tr id="row882978370084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1933512733084824"><a name="p1933512733084824"></a><a name="p1933512733084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1893355519084824"><a name="p1893355519084824"></a><a name="p1893355519084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row830500490084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416430221084824"><a name="p416430221084824"></a><a name="p416430221084824"></a>ERANGE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600555888084824"><a name="p600555888084824"></a><a name="p600555888084824"></a>The name is too long. </p>
</td>
</tr>
<tr id="row1040799901084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1397170854084824"><a name="p1397170854084824"></a><a name="p1397170854084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1376361661084824"><a name="p1376361661084824"></a><a name="p1376361661084824"></a>Failed to copy data from the user-level thread. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_setschedparam\(\)<a name="ga14f50e1f5d815c90f1f4225eca5d3a8c"></a>

```
int pthread_setschedparam (pthread_t thread, int policy, const struct [sched_param](sched_param.md) * param )
```

 **Description:**

Sets a scheduling policy and parameters for a thread. 

**Parameters:**

<a name="table752075224084824"></a>
<table><thead align="left"><tr id="row470558511084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p648548959084824"><a name="p648548959084824"></a><a name="p648548959084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p169237322084824"><a name="p169237322084824"></a><a name="p169237322084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1387069224084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target thread. </td>
</tr>
<tr id="row1549662035084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">policy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the scheduling policy to set. The value can only be <strong id="b2033964480084824"><a name="b2033964480084824"></a><a name="b2033964480084824"></a>SCHED_FIFO</strong> or <strong id="b1471548297084824"><a name="b1471548297084824"></a><a name="b1471548297084824"></a>SCHED_RR</strong>. </td>
</tr>
<tr id="row628111831084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling parameters to set. Only the thread priority is supported. The priority ranges from 0 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. If the operation fails, the scheduling policy and parameters of the target thread remain unchanged. 

<a name="table1375660654084824"></a>
<table><thead align="left"><tr id="row1420648598084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1431250725084824"><a name="p1431250725084824"></a><a name="p1431250725084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p322071498084824"><a name="p322071498084824"></a><a name="p322071498084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row865226574084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290617860084824"><a name="p1290617860084824"></a><a name="p1290617860084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1089802246084824"><a name="p1089802246084824"></a><a name="p1089802246084824"></a>Invalid thread ID. </p>
</td>
</tr>
<tr id="row2099093595084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1631362318084824"><a name="p1631362318084824"></a><a name="p1631362318084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700483127084824"><a name="p1700483127084824"></a><a name="p1700483127084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1102618411084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p876629983084824"><a name="p876629983084824"></a><a name="p876629983084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577825097084824"><a name="p577825097084824"></a><a name="p577825097084824"></a>No permission to set the specified scheduling policy and parameters. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_setschedprio\(\)<a name="ga7a23cbcfc21a4e3edf531ed65f022370"></a>

```
int pthread_setschedprio (pthread_t thread, int prio )
```

 **Description:**

Sets a static scheduling priority for a thread. 

**Parameters:**

<a name="table1566386084084824"></a>
<table><thead align="left"><tr id="row806996318084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2067186531084824"><a name="p2067186531084824"></a><a name="p2067186531084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p395537276084824"><a name="p395537276084824"></a><a name="p395537276084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1327206764084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">thread</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target thread. </td>
</tr>
<tr id="row166775742084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">priority</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the static scheduling priority to set. The value ranges from 0 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. If the operation fails, the scheduling policy of the target thread remains unchanged. 

<a name="table268768710084824"></a>
<table><thead align="left"><tr id="row575224891084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p699524606084824"><a name="p699524606084824"></a><a name="p699524606084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p250641629084824"><a name="p250641629084824"></a><a name="p250641629084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1506148250084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1003398462084824"><a name="p1003398462084824"></a><a name="p1003398462084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177699959084824"><a name="p1177699959084824"></a><a name="p1177699959084824"></a>Invalid thread ID. </p>
</td>
</tr>
<tr id="row65890798084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1387099069084824"><a name="p1387099069084824"></a><a name="p1387099069084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p789632479084824"><a name="p789632479084824"></a><a name="p789632479084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row778499614084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35912148084824"><a name="p35912148084824"></a><a name="p35912148084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312225574084824"><a name="p1312225574084824"></a><a name="p1312225574084824"></a>No permission to set the specified scheduling policy and parameters. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_setspecific\(\)<a name="ga2187333dd46ce08d9d2e044f79fad705"></a>

```
int pthread_setspecific (pthread_key_t key, const void * value )
```

 **Description:**

Sets specific thread data. 

This function always succeeds. 

**Parameters:**

<a name="table1632732282084824"></a>
<table><thead align="left"><tr id="row551102116084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1977765812084824"><a name="p1977765812084824"></a><a name="p1977765812084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1405468893084824"><a name="p1405468893084824"></a><a name="p1405468893084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1922888349084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key bound to the thread data. </td>
</tr>
<tr id="row1492059447084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the thread data to be bound to the key. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_spin\_destroy\(\)<a name="ga822c2ff425ddad4c25b6a6092c6effff"></a>

```
int pthread_spin_destroy (pthread_spinlock_t * s)
```

 **Description:**

Destroys a spin lock. 

This function always succeeds. 

**Parameters:**

<a name="table67250421084824"></a>
<table><thead align="left"><tr id="row1304551471084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p837506629084824"><a name="p837506629084824"></a><a name="p837506629084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p986857206084824"><a name="p986857206084824"></a><a name="p986857206084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row30686407084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">s</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spin lock to destroy. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_spin\_init\(\)<a name="ga665a56a7bed60c8eaa6c28af40d13cd4"></a>

```
int pthread_spin_init (pthread_spinlock_t * s, int shared )
```

 **Description:**

Initializes a spin lock. 

This function always succeeds. 

**Parameters:**

<a name="table1808669780084824"></a>
<table><thead align="left"><tr id="row1057844792084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1860242448084824"><a name="p1860242448084824"></a><a name="p1860242448084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p148518918084824"><a name="p148518918084824"></a><a name="p148518918084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2092190883084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">s</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spin lock to initialize. </td>
</tr>
<tr id="row1479755581084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shared</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates thread process-shared synchronization, which is not supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_spin\_lock\(\)<a name="ga62cfd14d1f937a6e8f966e3a331bcf94"></a>

```
int pthread_spin_lock (pthread_spinlock_t * s)
```

 **Description:**

Locks a spin lock. 

This function always succeeds. 

**Parameters:**

<a name="table1162846298084824"></a>
<table><thead align="left"><tr id="row1953896846084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p304453300084824"><a name="p304453300084824"></a><a name="p304453300084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1379260656084824"><a name="p1379260656084824"></a><a name="p1379260656084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1580573846084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">s</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spin lock to lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_spin\_trylock\(\)<a name="ga084834fa2d06f173f086ce23ec1ea5d9"></a>

```
int pthread_spin_trylock (pthread_spinlock_t * s)
```

 **Description:**

Attempts to lock a spin lock. 

This function attempts to lock the spin lock, without blocking the calling thread. If the spin lock is already locked, the error code  **EBUSY**  is returned immediately. 

**Parameters:**

<a name="table1808647563084824"></a>
<table><thead align="left"><tr id="row1234761703084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p532717755084824"><a name="p532717755084824"></a><a name="p532717755084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1692441908084824"><a name="p1692441908084824"></a><a name="p1692441908084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1070204047084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">s</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spin lock to lock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a value listed in  **errno**  otherwise. 

<a name="table1633806825084824"></a>
<table><thead align="left"><tr id="row147172686084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1321844679084824"><a name="p1321844679084824"></a><a name="p1321844679084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p678163805084824"><a name="p678163805084824"></a><a name="p678163805084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1574935219084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2078791637084824"><a name="p2078791637084824"></a><a name="p2078791637084824"></a>EBUSY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601825216084824"><a name="p1601825216084824"></a><a name="p1601825216084824"></a>The spin lock has been held by another thread. </p>
</td>
</tr>
</tbody>
</table>

## pthread\_spin\_unlock\(\)<a name="ga3fe246007a85cee9d5f7af9b7d592b54"></a>

```
int pthread_spin_unlock (pthread_spinlock_t * s)
```

 **Description:**

Unlocks a spin lock. 

This function always succeeds. 

**Parameters:**

<a name="table1027778726084824"></a>
<table><thead align="left"><tr id="row463126330084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p931084045084824"><a name="p931084045084824"></a><a name="p931084045084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1370555443084824"><a name="p1370555443084824"></a><a name="p1370555443084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row964766544084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">s</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the spin lock to unlock. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**. 



## pthread\_testcancel\(\)<a name="gaf1c95282ab2bea25f0888a19652cd41f"></a>

```
void pthread_testcancel (void )
```

 **Description:**

Requests delivery of any pending cancellation request. 

This function creates a cancellation point in the calling thread. In this way, the thread executing code that contains no cancellation point responds to the cancellation request. This function always succeeds. 

**Returns:**

Returns the cancellation point. 



## sched\_get\_priority\_max\(\)<a name="gafaebd1698caeb9b9b9e614ad84edd609"></a>

```
int sched_get_priority_max (int policy)
```

 **Description:**

Obtains the maximum static priority that can be used for a process. 

This function returns the lowest priority of process scheduling in a scheduling policy specified by  **policy**. The value of  **policy**  must be a value defined in  [sched.h](sched-h.md). 

**Parameters:**

<a name="table1365829169084824"></a>
<table><thead align="left"><tr id="row2110535431084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p952898106084824"><a name="p952898106084824"></a><a name="p952898106084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p876140486084824"><a name="p876140486084824"></a><a name="p876140486084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row856982052084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">policy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the scheduling policy. The value can be <strong id="b1790289278084824"><a name="b1790289278084824"></a><a name="b1790289278084824"></a>SCHED_FIFO</strong> or <strong id="b1587625722084824"><a name="b1587625722084824"></a><a name="b1587625722084824"></a>SCHED_RR</strong>, but not <strong id="b1920073762084824"><a name="b1920073762084824"></a><a name="b1920073762084824"></a>SCHED_OTHER</strong>, <strong id="b679356465084824"><a name="b679356465084824"></a><a name="b679356465084824"></a>SCHED_BATCH</strong>, <strong id="b578977372084824"><a name="b578977372084824"></a><a name="b578977372084824"></a>SCHED_IDLE</strong>, or <strong id="b102483708084824"><a name="b102483708084824"></a><a name="b102483708084824"></a>SCHED_DEADLINE</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the lowest priority of the scheduling policy if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table775515552084824"></a>
<table><thead align="left"><tr id="row1009007999084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p717947669084824"><a name="p717947669084824"></a><a name="p717947669084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p98783648084824"><a name="p98783648084824"></a><a name="p98783648084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2052496558084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p63870506084824"><a name="p63870506084824"></a><a name="p63870506084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213191380084824"><a name="p213191380084824"></a><a name="p213191380084824"></a>Invalid parameter. The value of <strong id="b1496506334084824"><a name="b1496506334084824"></a><a name="b1496506334084824"></a>policy</strong> is not a defined scheduling policy. </p>
</td>
</tr>
<tr id="row1845301361084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488928356084824"><a name="p1488928356084824"></a><a name="p1488928356084824"></a>ENOSYS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1813151540084824"><a name="p1813151540084824"></a><a name="p1813151540084824"></a>Unsupported scheduling policy. </p>
</td>
</tr>
</tbody>
</table>

## sched\_get\_priority\_min\(\)<a name="gaf1f370fc36ea6b22ed42b5ee3cf82a81"></a>

```
int sched_get_priority_min (int policy)
```

 **Description:**

Obtains the minimum static priority that can be used for a process. 

This function returns the highest priority of process scheduling in a scheduling policy specified by  **policy**. The value of  **policy**  must be a value defined in  [sched.h](sched-h.md). 

**Parameters:**

<a name="table562654584084824"></a>
<table><thead align="left"><tr id="row610522661084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p304987963084824"><a name="p304987963084824"></a><a name="p304987963084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p142297991084824"><a name="p142297991084824"></a><a name="p142297991084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row207918455084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">policy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the scheduling policy. The value can be <strong id="b2054144560084824"><a name="b2054144560084824"></a><a name="b2054144560084824"></a>SCHED_FIFO</strong> or <strong id="b1061181588084824"><a name="b1061181588084824"></a><a name="b1061181588084824"></a>SCHED_RR</strong>, but not <strong id="b1548665652084824"><a name="b1548665652084824"></a><a name="b1548665652084824"></a>SCHED_OTHER</strong>, <strong id="b937350232084824"><a name="b937350232084824"></a><a name="b937350232084824"></a>SCHED_BATCH</strong>, <strong id="b607779683084824"><a name="b607779683084824"></a><a name="b607779683084824"></a>SCHED_IDLE</strong>, or <strong id="b1447612053084824"><a name="b1447612053084824"></a><a name="b1447612053084824"></a>SCHED_DEADLINE</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the highest priority of the scheduling policy if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1834928888084824"></a>
<table><thead align="left"><tr id="row891645712084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p501343707084824"><a name="p501343707084824"></a><a name="p501343707084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1325594630084824"><a name="p1325594630084824"></a><a name="p1325594630084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1591692126084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589794944084824"><a name="p589794944084824"></a><a name="p589794944084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596737288084824"><a name="p596737288084824"></a><a name="p596737288084824"></a>Invalid parameter. The value of <strong id="b1303804701084824"><a name="b1303804701084824"></a><a name="b1303804701084824"></a>policy</strong> is not a defined scheduling policy. </p>
</td>
</tr>
<tr id="row1752393481084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836553983084824"><a name="p1836553983084824"></a><a name="p1836553983084824"></a>ENOSYS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305310622084824"><a name="p1305310622084824"></a><a name="p1305310622084824"></a>Unsupported scheduling policy. </p>
</td>
</tr>
</tbody>
</table>

## sched\_getparam\(\)<a name="ga563c7ac53bac2c1b51379147e66c44ec"></a>

```
int sched_getparam (pid_t pid, struct [sched_param](sched_param.md) * param )
```

 **Description:**

Obtains scheduling parameters of a process. 

**Parameters:**

<a name="table1457768205084824"></a>
<table><thead align="left"><tr id="row181966639084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1207507040084824"><a name="p1207507040084824"></a><a name="p1207507040084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p653399163084824"><a name="p653399163084824"></a><a name="p653399163084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row463389139084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the process for which the scheduling parameters are to be obtained. If this parameter is set to <strong id="b795372350084824"><a name="b795372350084824"></a><a name="b795372350084824"></a>0</strong>, the scheduling parameters of the calling process are to be obtained. </td>
</tr>
<tr id="row1396022396084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling parameters. Only the static priority is supported. The priority ranges from 10 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table179764371084824"></a>
<table><thead align="left"><tr id="row1755369784084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p483033851084824"><a name="p483033851084824"></a><a name="p483033851084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1906536930084824"><a name="p1906536930084824"></a><a name="p1906536930084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1855480520084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170202932084824"><a name="p170202932084824"></a><a name="p170202932084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259731509084824"><a name="p1259731509084824"></a><a name="p1259731509084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row900101907084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1030516582084824"><a name="p1030516582084824"></a><a name="p1030516582084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852325314084824"><a name="p852325314084824"></a><a name="p852325314084824"></a>The process specified by <strong id="b1373939856084824"><a name="b1373939856084824"></a><a name="b1373939856084824"></a>pid</strong> cannot be found. </p>
</td>
</tr>
</tbody>
</table>

## sched\_getscheduler\(\)<a name="ga99fcb2532b1482d236dc04495a3f194d"></a>

```
int sched_getscheduler (pid_t pid)
```

 **Description:**

Obtains the scheduling policy of a process. 

**Parameters:**

<a name="table2027214958084824"></a>
<table><thead align="left"><tr id="row1538717472084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1246549962084824"><a name="p1246549962084824"></a><a name="p1246549962084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1622263272084824"><a name="p1622263272084824"></a><a name="p1622263272084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1064984055084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the process for which the scheduling policy is to be obtained. If this parameter is set to <strong id="b1047012060084824"><a name="b1047012060084824"></a><a name="b1047012060084824"></a>0</strong>, the scheduling policy of the calling process is to be obtained. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table826439427084824"></a>
<table><thead align="left"><tr id="row1980497263084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1042562028084824"><a name="p1042562028084824"></a><a name="p1042562028084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p736589049084824"><a name="p736589049084824"></a><a name="p736589049084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1457187046084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823137242084824"><a name="p1823137242084824"></a><a name="p1823137242084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772811511084824"><a name="p772811511084824"></a><a name="p772811511084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row929885451084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1483306951084824"><a name="p1483306951084824"></a><a name="p1483306951084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p354039684084824"><a name="p354039684084824"></a><a name="p354039684084824"></a>No permission. </p>
</td>
</tr>
<tr id="row118637321084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p934277694084824"><a name="p934277694084824"></a><a name="p934277694084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221251001084824"><a name="p1221251001084824"></a><a name="p1221251001084824"></a>The process specified by <strong id="b1023052320084824"><a name="b1023052320084824"></a><a name="b1023052320084824"></a>pid</strong> cannot be found. </p>
</td>
</tr>
</tbody>
</table>

## sched\_rr\_get\_interval\(\)<a name="ga484f0eb93529d29a66e24485725c4c7b"></a>

```
int sched_rr_get_interval (pid_t pid, struct [timespec](timespec.md) * interval )
```

 **Description:**

Obtains the execution time limit of a process. 

This function updates the  **timespec**  structure referenced by the parameter  **interval**  to record the execution time limit of a process. 

**Parameters:**

<a name="table20155582084824"></a>
<table><thead align="left"><tr id="row1805719614084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p266869152084824"><a name="p266869152084824"></a><a name="p266869152084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p228586528084824"><a name="p228586528084824"></a><a name="p228586528084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1024202323084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the process for which the execution time limit is to be obtained. If this parameter is &lt;0&gt;0, the time quantum of the calling process is obtained and written into the parameter <strong id="b1347544856084824"><a name="b1347544856084824"></a><a name="b1347544856084824"></a>interval</strong>. </td>
</tr>
<tr id="row591632764084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">interval</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time structure that records the time limit. The time structure supports only seconds and nanoseconds. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table979535308084824"></a>
<table><thead align="left"><tr id="row475328810084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1625189668084824"><a name="p1625189668084824"></a><a name="p1625189668084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2063970236084824"><a name="p2063970236084824"></a><a name="p2063970236084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1621611674084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1419767787084824"><a name="p1419767787084824"></a><a name="p1419767787084824"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2130921649084824"><a name="p2130921649084824"></a><a name="p2130921649084824"></a>An error occurred when copying information to the user space. </p>
</td>
</tr>
<tr id="row627053275084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p132415801084824"><a name="p132415801084824"></a><a name="p132415801084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823382928084824"><a name="p1823382928084824"></a><a name="p1823382928084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row495401368084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806062003084824"><a name="p1806062003084824"></a><a name="p1806062003084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304730891084824"><a name="p304730891084824"></a><a name="p304730891084824"></a>The process specified by <strong id="b915696514084824"><a name="b915696514084824"></a><a name="b915696514084824"></a>pid</strong> cannot be found. </p>
</td>
</tr>
</tbody>
</table>

## sched\_setparam\(\)<a name="ga06b497c4ea6bbabd2b62ba1a8a848a1b"></a>

```
int sched_setparam (pid_t pid, const struct [sched_param](sched_param.md) * param )
```

 **Description:**

Sets scheduling parameters related to a scheduling policy for a process. 

 

**Parameters:**

<a name="table2105979245084824"></a>
<table><thead align="left"><tr id="row1873217285084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1526728506084824"><a name="p1526728506084824"></a><a name="p1526728506084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p601052862084824"><a name="p601052862084824"></a><a name="p601052862084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1786349217084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the process for which the scheduling parameters are to be set. If this parameter is set to <strong id="b852008320084824"><a name="b852008320084824"></a><a name="b852008320084824"></a>0</strong>, the scheduling parameters of the calling process are to be set. </td>
</tr>
<tr id="row2132978165084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling parameters to set. Only the static priority can be set. The priority ranges from 10 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1074185100084824"></a>
<table><thead align="left"><tr id="row812159755084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1493425942084824"><a name="p1493425942084824"></a><a name="p1493425942084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1498297649084824"><a name="p1498297649084824"></a><a name="p1498297649084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1259085716084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1760150466084824"><a name="p1760150466084824"></a><a name="p1760150466084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069711761084824"><a name="p2069711761084824"></a><a name="p2069711761084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row162449459084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1038543993084824"><a name="p1038543993084824"></a><a name="p1038543993084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643499681084824"><a name="p1643499681084824"></a><a name="p1643499681084824"></a>No permission. </p>
</td>
</tr>
<tr id="row1928338387084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1591167817084824"><a name="p1591167817084824"></a><a name="p1591167817084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1116861347084824"><a name="p1116861347084824"></a><a name="p1116861347084824"></a>The process specified by <strong id="b435526145084824"><a name="b435526145084824"></a><a name="b435526145084824"></a>pid</strong> cannot be found. </p>
</td>
</tr>
</tbody>
</table>

## sched\_setscheduler\(\)<a name="ga84ad29a6f2ad27370df09c664ac65eac"></a>

```
int sched_setscheduler (pid_t pid, int policy, const struct [sched_param](sched_param.md) * param )
```

 **Description:**

Sets a scheduling policy for a process. 

**Parameters:**

<a name="table1269507852084824"></a>
<table><thead align="left"><tr id="row942861590084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2043590809084824"><a name="p2043590809084824"></a><a name="p2043590809084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1708038948084824"><a name="p1708038948084824"></a><a name="p1708038948084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1857129711084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the process for which the scheduling policy and parameters are to be set. If this parameter is set to <strong id="b348603408084824"><a name="b348603408084824"></a><a name="b348603408084824"></a>0</strong>, the scheduling policy and parameters of the calling process are to be set. </td>
</tr>
<tr id="row1422529118084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">policy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the scheduling policy to set. The value can be <strong id="b955751460084824"><a name="b955751460084824"></a><a name="b955751460084824"></a>SCHED_FIFO</strong> or <strong id="b774237033084824"><a name="b774237033084824"></a><a name="b774237033084824"></a>SCHED_RR</strong>, but not <strong id="b1912911166084824"><a name="b1912911166084824"></a><a name="b1912911166084824"></a>SCHED_OTHER</strong>, <strong id="b1772282513084824"><a name="b1772282513084824"></a><a name="b1772282513084824"></a>SCHED_BATCH</strong>, <strong id="b433911072084824"><a name="b433911072084824"></a><a name="b433911072084824"></a>SCHED_IDLE</strong>, or <strong id="b2064869853084824"><a name="b2064869853084824"></a><a name="b2064869853084824"></a>SCHED_DEADLINE</strong>. </td>
</tr>
<tr id="row1070910884084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">param</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the scheduling parameters to set. Only the static priority can be set. The priority ranges from 10 (highest priority) to 31 (lowest priority). </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1373640784084824"></a>
<table><thead align="left"><tr id="row936457881084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1015749365084824"><a name="p1015749365084824"></a><a name="p1015749365084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p603467523084824"><a name="p603467523084824"></a><a name="p603467523084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row630486967084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106866921084824"><a name="p106866921084824"></a><a name="p106866921084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402459474084824"><a name="p402459474084824"></a><a name="p402459474084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row664034002084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657434371084824"><a name="p1657434371084824"></a><a name="p1657434371084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858441832084824"><a name="p858441832084824"></a><a name="p858441832084824"></a>No permission. </p>
</td>
</tr>
<tr id="row570675277084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1582491280084824"><a name="p1582491280084824"></a><a name="p1582491280084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1690696273084824"><a name="p1690696273084824"></a><a name="p1690696273084824"></a>The process specified by <strong id="b1349344176084824"><a name="b1349344176084824"></a><a name="b1349344176084824"></a>pid</strong> cannot be found. </p>
</td>
</tr>
</tbody>
</table>

## sched\_yield\(\)<a name="ga357cd4b34c13011749dfffb42b489f09"></a>

```
int sched_yield (void )
```

 **Description:**

Yields the running process. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## setpriority\(\)<a name="ga0a8d4c8043a7748c25dd551dc69dcad2"></a>

```
int setpriority (int which, id_t who, int value )
```

 **Description:**

Sets the static priority of a specified ID. 

**Parameters:**

<a name="table95682041084824"></a>
<table><thead align="left"><tr id="row2908518084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1776405014084824"><a name="p1776405014084824"></a><a name="p1776405014084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1437068570084824"><a name="p1437068570084824"></a><a name="p1437068570084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1923261830084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">which</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a specified value. The values are as follows: </td>
</tr>
<tr id="row1641209746084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">who</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the specified ID. </td>
</tr>
<tr id="row920137103084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target priority to set. </td>
</tr>
</tbody>
</table>

<a name="table751840414084824"></a>
<table><thead align="left"><tr id="row1994441055084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1014474411084824"><a name="p1014474411084824"></a><a name="p1014474411084824"></a>value </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p753720752084824"><a name="p753720752084824"></a><a name="p753720752084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row187520453084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p389851325084824"><a name="p389851325084824"></a><a name="p389851325084824"></a>RIO_PROCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1731622282084824"><a name="p1731622282084824"></a><a name="p1731622282084824"></a><strong id="b356339857084824"><a name="b356339857084824"></a><a name="b356339857084824"></a>who</strong> indicates the ID of a specified process. </p>
</td>
</tr>
<tr id="row937770015084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081733521084824"><a name="p1081733521084824"></a><a name="p1081733521084824"></a>PRIO_PGRP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p866434261084824"><a name="p866434261084824"></a><a name="p866434261084824"></a><strong id="b1021195849084824"><a name="b1021195849084824"></a><a name="b1021195849084824"></a>who</strong> indicates the ID of a specified process group. This value is not supported yet. </p>
</td>
</tr>
<tr id="row1780490060084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1419069856084824"><a name="p1419069856084824"></a><a name="p1419069856084824"></a>PRIO_USER </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1334843853084824"><a name="p1334843853084824"></a><a name="p1334843853084824"></a><strong id="b825655766084824"><a name="b825655766084824"></a><a name="b825655766084824"></a>who</strong> indicates the ID of a specified valid user. This value is not supported yet. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the scheduling priority if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table otherwise. 

<a name="table1823402035084824"></a>
<table><thead align="left"><tr id="row1207892225084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p317895833084824"><a name="p317895833084824"></a><a name="p317895833084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1874062425084824"><a name="p1874062425084824"></a><a name="p1874062425084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1852815095084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1611169375084824"><a name="p1611169375084824"></a><a name="p1611169375084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1348442133084824"><a name="p1348442133084824"></a><a name="p1348442133084824"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row2029795253084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p313216788084824"><a name="p313216788084824"></a><a name="p313216788084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p916055636084824"><a name="p916055636084824"></a><a name="p916055636084824"></a>The operation is not allowed. </p>
</td>
</tr>
<tr id="row1399520519084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492145042084824"><a name="p1492145042084824"></a><a name="p1492145042084824"></a>EOPNOTSUPP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3981232084824"><a name="p3981232084824"></a><a name="p3981232084824"></a>Unsupported value. </p>
</td>
</tr>
</tbody>
</table>

## wait\(\)<a name="gabf2fbcf6df59fd5234e9eed4db1a1804"></a>

```
pid_t wait (int * status)
```

 **Description:**

Waits for any child process to end and reclaims its resources. 

**Parameters:**

<a name="table1672486167084824"></a>
<table><thead align="left"><tr id="row682490845084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p387103329084824"><a name="p387103329084824"></a><a name="p387103329084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1078023471084824"><a name="p1078023471084824"></a><a name="p1078023471084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row650476754084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained status information. If this parameter is not <strong id="b173608801084824"><a name="b173608801084824"></a><a name="b173608801084824"></a>NULL</strong>, the status information is stored in the int value that it points to. You can use the following macros defined in <strong id="b1149772924084824"><a name="b1149772924084824"></a><a name="b1149772924084824"></a>private.h</strong> to check the integer (the macro uses the integer as a parameter instead of the pointer that points to it): <a name="ul1248326348084824"></a><a name="ul1248326348084824"></a><ul id="ul1248326348084824"><li> <strong id="b722261736084824"><a name="b722261736084824"></a><a name="b722261736084824"></a>WIFEXITED(status)</strong>: If the child process ends normally, <strong id="b1631474552084824"><a name="b1631474552084824"></a><a name="b1631474552084824"></a>true</strong> is returned. Otherwise, <strong id="b806930945084824"><a name="b806930945084824"></a><a name="b806930945084824"></a>false</strong> is returned. </li><li> <strong id="b1188228814084824"><a name="b1188228814084824"></a><a name="b1188228814084824"></a>WEXITSTATUS(status)</strong>: If <strong id="b2078302814084824"><a name="b2078302814084824"></a><a name="b2078302814084824"></a>WIFEXITED(status)</strong> is <strong id="b829996654084824"><a name="b829996654084824"></a><a name="b829996654084824"></a>true</strong>, this macro can be used to obtain the exit code that the child process passed to <a href="UTILS.md#ga55e99c539cf7723ec15e856b7e0a8cee">exit()</a>. </li><li> <strong id="b195069785084824"><a name="b195069785084824"></a><a name="b195069785084824"></a>WTERMSIG(status)</strong>: After a child process ends abnormally, the parent process can obtain the child process exit code <a href="IPC.md#gabaaa61abe503c43481e35e21b0b5a031">SIGUSR2</a> through <strong id="b1786773448084824"><a name="b1786773448084824"></a><a name="b1786773448084824"></a>WTERMSIG</strong>, indicating that the child process ends abnormally. This is the only case supported.</li></ul>
 </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the child process ID if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table214487328084824"></a>
<table><thead align="left"><tr id="row690599331084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2047074100084824"><a name="p2047074100084824"></a><a name="p2047074100084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1901449640084824"><a name="p1901449640084824"></a><a name="p1901449640084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1889256722084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615763472084824"><a name="p1615763472084824"></a><a name="p1615763472084824"></a>ECHILD </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p164980120084824"><a name="p164980120084824"></a><a name="p164980120084824"></a>The child process does not exist, or the specified process group does not exist. </p>
</td>
</tr>
<tr id="row60083484084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2123775560084824"><a name="p2123775560084824"></a><a name="p2123775560084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p239241213084824"><a name="p239241213084824"></a><a name="p239241213084824"></a>The child process ends abnormally. </p>
</td>
</tr>
</tbody>
</table>

## waitpid\(\)<a name="ga77de8005691d1f125540d66032a3cc62"></a>

```
pid_t waitpid (pid_t pid, int * status, int options )
```

 **Description:**

Waits for a specified child process to end and reclaims its resources. 

**Parameters:**

<a name="table1888836989084824"></a>
<table><thead align="left"><tr id="row1509159145084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p104214296084824"><a name="p104214296084824"></a><a name="p104214296084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p828725368084824"><a name="p828725368084824"></a><a name="p828725368084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1451708955084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of the child process to wait for. <a name="ul586554969084824"></a><a name="ul586554969084824"></a><ul id="ul586554969084824"><li> If this parameter is less than <strong id="b2073578231084824"><a name="b2073578231084824"></a><a name="b2073578231084824"></a>-1</strong>, the system waits for any child process whose process group ID is the absolute value of <strong id="b1760180391084824"><a name="b1760180391084824"></a><a name="b1760180391084824"></a>pid</strong>. </li><li> If this parameter is <strong id="b1407370540084824"><a name="b1407370540084824"></a><a name="b1407370540084824"></a>-1</strong>, the system waits for any child process. In this case, this function is equivalent to <a href="PROCESS.md#gabf2fbcf6df59fd5234e9eed4db1a1804">wait()</a>. </li><li> If this parameter is <strong id="b398738566084824"><a name="b398738566084824"></a><a name="b398738566084824"></a>0</strong>, the system waits for a child process whose process group ID is the same as the calling process (any process that is in the same process group as the calling process). </li><li> If this parameter is greater than <strong id="b1258091492084824"><a name="b1258091492084824"></a><a name="b1258091492084824"></a>0</strong>, the system waits for the child process whose process ID is the value of <strong id="b2146760478084824"><a name="b2146760478084824"></a><a name="b2146760478084824"></a>pid</strong>.</li></ul>
 </td>
</tr>
<tr id="row1640598931084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained status information. If this parameter is not <strong id="b1983388979084824"><a name="b1983388979084824"></a><a name="b1983388979084824"></a>NULL</strong>, the status information is stored in the int value that it points to. You can use the following macros defined in <strong id="b2101688337084824"><a name="b2101688337084824"></a><a name="b2101688337084824"></a>private.h</strong> to check the integer (the macro uses the integer as a parameter instead of the pointer that points to it): <a name="ul951899725084824"></a><a name="ul951899725084824"></a><ul id="ul951899725084824"><li> <strong id="b234084565084824"><a name="b234084565084824"></a><a name="b234084565084824"></a>WIFEXITED(status)</strong>: If the child process ends normally, <strong id="b138502518084824"><a name="b138502518084824"></a><a name="b138502518084824"></a>true</strong> is returned. Otherwise, <strong id="b1099988664084824"><a name="b1099988664084824"></a><a name="b1099988664084824"></a>false</strong> is returned. </li><li> <strong id="b1148635040084824"><a name="b1148635040084824"></a><a name="b1148635040084824"></a>WEXITSTATUS(status)</strong>: If <strong id="b1258613854084824"><a name="b1258613854084824"></a><a name="b1258613854084824"></a>WIFEXITED(status)</strong> is <strong id="b330112755084824"><a name="b330112755084824"></a><a name="b330112755084824"></a>true</strong>, this macro can be used to obtain the exit code that the child process passed to <a href="UTILS.md#ga55e99c539cf7723ec15e856b7e0a8cee">exit()</a>. </li><li> <strong id="b1364828171084824"><a name="b1364828171084824"></a><a name="b1364828171084824"></a>WTERMSIG(status)</strong>: After a child process ends abnormally, the parent process can obtain the child process exit code <a href="IPC.md#gabaaa61abe503c43481e35e21b0b5a031">SIGUSR2</a> through <strong id="b1788644069084824"><a name="b1788644069084824"></a><a name="b1788644069084824"></a>WTERMSIG</strong>, indicating that the child process ends abnormally. This is the only case supported.</li></ul>
 <strong id="b1394740503084824"><a name="b1394740503084824"></a><a name="b1394740503084824"></a>WIFSIGNALED</strong>, <strong id="b1913915132084824"><a name="b1913915132084824"></a><a name="b1913915132084824"></a>WIFSTOPPED</strong>, <strong id="b194850714084824"><a name="b194850714084824"></a><a name="b194850714084824"></a>WSTOPSIG</strong>, <strong id="b1857764064084824"><a name="b1857764064084824"></a><a name="b1857764064084824"></a>WCOREDUMP</strong>, <strong id="b185439660084824"><a name="b185439660084824"></a><a name="b185439660084824"></a>WIFCONTINUED</strong>, and <strong id="b1820567518084824"><a name="b1820567518084824"></a><a name="b1820567518084824"></a>WUNTRACED</strong> are not supported. </td>
</tr>
<tr id="row942372475084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">options</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Provides some options to control the behavior of this function. If you do not want to use these options, set this parameter to <strong id="b874384907084824"><a name="b874384907084824"></a><a name="b874384907084824"></a>0</strong>. <strong id="b1412060134084824"><a name="b1412060134084824"></a><a name="b1412060134084824"></a>WNOHANG</strong>: If the child process specified by <strong id="b1430006637084824"><a name="b1430006637084824"></a><a name="b1430006637084824"></a>pid</strong> is not ended, this function returns <strong id="b47649522084824"><a name="b47649522084824"></a><a name="b47649522084824"></a>0</strong> immediately instead of blocking the calling process. If the child process is ended, the process ID of the child process is returned. <strong id="b1901026729084824"><a name="b1901026729084824"></a><a name="b1901026729084824"></a>WUNTRACED</strong>, <strong id="b707643048084824"><a name="b707643048084824"></a><a name="b707643048084824"></a>WEXITED</strong>, <strong id="b192298835084824"><a name="b192298835084824"></a><a name="b192298835084824"></a>WSTOPPED</strong>, <strong id="b1157833905084824"><a name="b1157833905084824"></a><a name="b1157833905084824"></a>WCONTINUED</strong>, and <strong id="b1596697080084824"><a name="b1596697080084824"></a><a name="b1596697080084824"></a>WNOWAIT</strong> are not supported. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the child process ID if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1146891697084824"></a>
<table><thead align="left"><tr id="row64917654084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1182157590084824"><a name="p1182157590084824"></a><a name="p1182157590084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1820147610084824"><a name="p1820147610084824"></a><a name="p1820147610084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row82974093084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642372743084824"><a name="p642372743084824"></a><a name="p642372743084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053587079084824"><a name="p2053587079084824"></a><a name="p2053587079084824"></a>Invalid options. </p>
</td>
</tr>
<tr id="row1587728176084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p395171788084824"><a name="p395171788084824"></a><a name="p395171788084824"></a>EOPNOTSUPP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125524894084824"><a name="p2125524894084824"></a><a name="p2125524894084824"></a>Unsupported options. </p>
</td>
</tr>
<tr id="row1078037643084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716993742084824"><a name="p716993742084824"></a><a name="p716993742084824"></a>ECHILD </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748946295084824"><a name="p748946295084824"></a><a name="p748946295084824"></a>The child process does not exist, or the specified process group does not exist. </p>
</td>
</tr>
<tr id="row93778743084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1784325915084824"><a name="p1784325915084824"></a><a name="p1784325915084824"></a>ESRCH </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783741175084824"><a name="p783741175084824"></a><a name="p783741175084824"></a>The child process ends abnormally. </p>
</td>
</tr>
</tbody>
</table>

