# pthread.h<a name="EN-US_TOPIC_0000001055228018"></a>

## **Overview**<a name="section936784353084831"></a>

**Related Modules:**

[PROCESS](process.md)

**Description:**

Provides process- and thread-related structures \(providing fields such as thread attributes\) and functions \(including the functions for creating and destroying threads, and setting the thread detach state and blocking conditions\). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section587924770084831"></a>

## Functions<a name="func-members"></a>

<a name="table278933531084831"></a>
<table><thead align="left"><tr id="row629732592084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1674192319084831"><a name="p1674192319084831"></a><a name="p1674192319084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1966658112084831"><a name="p1966658112084831"></a><a name="p1966658112084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1338231546084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1420505920084831"><a name="p1420505920084831"></a><a name="p1420505920084831"></a><a href="process.md#gae5d18438d4d20c8a2e42cd2500578d79">pthread_create</a> (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p158737550084831"><a name="p158737550084831"></a><a name="p158737550084831"></a>int </p>
<p id="p1499526583084831"><a name="p1499526583084831"></a><a name="p1499526583084831"></a>Creates a thread. </p>
</td>
</tr>
<tr id="row141995018084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274339001084831"><a name="p274339001084831"></a><a name="p274339001084831"></a><a href="process.md#ga7c275c509c26566b6dd95a2de1668a2f">pthread_detach</a> (pthread_t thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427776902084831"><a name="p1427776902084831"></a><a name="p1427776902084831"></a>int </p>
<p id="p1748908653084831"><a name="p1748908653084831"></a><a name="p1748908653084831"></a>Detaches a thread. </p>
</td>
</tr>
<tr id="row1707637780084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1336791060084831"><a name="p1336791060084831"></a><a name="p1336791060084831"></a><a href="process.md#gaadfb4e5de5a20880c6a40d4e73ce2597">pthread_exit</a> (void *retval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1404496180084831"><a name="p1404496180084831"></a><a name="p1404496180084831"></a>_Noreturn void </p>
<p id="p316311595084831"><a name="p316311595084831"></a><a name="p316311595084831"></a>Terminates the calling thread. </p>
</td>
</tr>
<tr id="row275643329084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1240326946084831"><a name="p1240326946084831"></a><a name="p1240326946084831"></a><a href="process.md#ga28a15bba47cab57cbc9f5dac9af99c8b">pthread_join</a> (pthread_t thread, void **retval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911776136084831"><a name="p1911776136084831"></a><a name="p1911776136084831"></a>int </p>
<p id="p1654684601084831"><a name="p1654684601084831"></a><a name="p1654684601084831"></a>Waits for a thread to terminate. </p>
</td>
</tr>
<tr id="row500385784084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p246570847084831"><a name="p246570847084831"></a><a name="p246570847084831"></a><a href="process.md#ga4c4f5f3b4f8f45d9d897847d53b11aaa">pthread_self</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1471574492084831"><a name="p1471574492084831"></a><a name="p1471574492084831"></a>pthread_t </p>
<p id="p1250721980084831"><a name="p1250721980084831"></a><a name="p1250721980084831"></a>Obtains the ID of the calling thread. </p>
</td>
</tr>
<tr id="row1322849588084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1399150485084831"><a name="p1399150485084831"></a><a name="p1399150485084831"></a><a href="process.md#ga98ec817164a6641eda2341de473b659d">pthread_equal</a> (pthread_t t1, pthread_t t2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1624582945084831"><a name="p1624582945084831"></a><a name="p1624582945084831"></a>int </p>
<p id="p591628834084831"><a name="p591628834084831"></a><a name="p591628834084831"></a>Compares whether two thread IDs are equal. </p>
</td>
</tr>
<tr id="row1123516869084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p310019677084831"><a name="p310019677084831"></a><a name="p310019677084831"></a><a href="process.md#ga37075410fbbaad7ee93c95375fc86e0e">pthread_setcancelstate</a> (int state, int *oldstate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375925438084831"><a name="p1375925438084831"></a><a name="p1375925438084831"></a>int </p>
<p id="p13320449084831"><a name="p13320449084831"></a><a name="p13320449084831"></a>Sets the cancelability state for the calling thread. </p>
</td>
</tr>
<tr id="row327124959084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530598869084831"><a name="p530598869084831"></a><a name="p530598869084831"></a><a href="process.md#gaab579bcfcf0662a0c1e35fd82162e61d">pthread_setcanceltype</a> (int type, int *oldtype)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155242778084831"><a name="p1155242778084831"></a><a name="p1155242778084831"></a>int </p>
<p id="p343036429084831"><a name="p343036429084831"></a><a name="p343036429084831"></a>Sets the cancelability type for the calling thread. </p>
</td>
</tr>
<tr id="row1525994075084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p969747806084831"><a name="p969747806084831"></a><a name="p969747806084831"></a><a href="process.md#gaf1c95282ab2bea25f0888a19652cd41f">pthread_testcancel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800889596084831"><a name="p800889596084831"></a><a name="p800889596084831"></a>void </p>
<p id="p846143272084831"><a name="p846143272084831"></a><a name="p846143272084831"></a>Requests delivery of any pending cancellation request. </p>
</td>
</tr>
<tr id="row1419595392084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478578056084831"><a name="p478578056084831"></a><a name="p478578056084831"></a><a href="process.md#ga9e77a80c073787bf9a593e9c619dce27">pthread_cancel</a> (pthread_t thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1515902843084831"><a name="p1515902843084831"></a><a name="p1515902843084831"></a>int </p>
<p id="p653290080084831"><a name="p653290080084831"></a><a name="p653290080084831"></a>Sends a cancellation request to a thread. </p>
</td>
</tr>
<tr id="row1340992926084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322243165084831"><a name="p322243165084831"></a><a name="p322243165084831"></a><a href="process.md#ga5aafacc071cdfafd0eb992004dee3e62">pthread_kill</a> (pthread_t thread, int sig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1739966800084831"><a name="p1739966800084831"></a><a name="p1739966800084831"></a>int </p>
<p id="p1903311140084831"><a name="p1903311140084831"></a><a name="p1903311140084831"></a>Sends a signal to a thread. </p>
</td>
</tr>
<tr id="row1494854668084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p962490977084831"><a name="p962490977084831"></a><a name="p962490977084831"></a><a href="process.md#gaae9850b3759769c748727e171c4c6e61">pthread_getschedparam</a> (pthread_t thread, int *policy, struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1988845719084831"><a name="p1988845719084831"></a><a name="p1988845719084831"></a>int </p>
<p id="p1595724400084831"><a name="p1595724400084831"></a><a name="p1595724400084831"></a>Obtains the scheduling policy and parameters of a thread. </p>
</td>
</tr>
<tr id="row1065579712084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p491695424084831"><a name="p491695424084831"></a><a name="p491695424084831"></a><a href="process.md#ga14f50e1f5d815c90f1f4225eca5d3a8c">pthread_setschedparam</a> (pthread_t thread, int policy, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p258015925084831"><a name="p258015925084831"></a><a name="p258015925084831"></a>int </p>
<p id="p1017117311084831"><a name="p1017117311084831"></a><a name="p1017117311084831"></a>Sets a scheduling policy and parameters for a thread. </p>
</td>
</tr>
<tr id="row1950245672084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p909485016084831"><a name="p909485016084831"></a><a name="p909485016084831"></a><a href="process.md#ga7a23cbcfc21a4e3edf531ed65f022370">pthread_setschedprio</a> (pthread_t thread, int prio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1532326522084831"><a name="p1532326522084831"></a><a name="p1532326522084831"></a>int </p>
<p id="p2136329142084831"><a name="p2136329142084831"></a><a name="p2136329142084831"></a>Sets a static scheduling priority for a thread. </p>
</td>
</tr>
<tr id="row2022991064084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636419163084831"><a name="p636419163084831"></a><a name="p636419163084831"></a><a href="process.md#ga196103ac97710dad7a93fd6c188cc999">pthread_once</a> (pthread_once_t *once_control, void(*init_routine)(void))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p645947359084831"><a name="p645947359084831"></a><a name="p645947359084831"></a>int </p>
<p id="p1460939055084831"><a name="p1460939055084831"></a><a name="p1460939055084831"></a>Enables the initialization function to be called only once. </p>
</td>
</tr>
<tr id="row1755466003084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p814549636084831"><a name="p814549636084831"></a><a name="p814549636084831"></a><a href="process.md#gadd99221596e95a55f70c59c1c712bbde">pthread_mutex_init</a> (pthread_mutex_t *__restrict m, const pthread_mutexattr_t *__restrict a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141511484084831"><a name="p1141511484084831"></a><a name="p1141511484084831"></a>int </p>
<p id="p1004020697084831"><a name="p1004020697084831"></a><a name="p1004020697084831"></a>Initializes a mutex. </p>
</td>
</tr>
<tr id="row1422353289084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102319312084831"><a name="p1102319312084831"></a><a name="p1102319312084831"></a><a href="process.md#gafd70d6f2c50e22b996c926fb9d6ad291">pthread_mutex_lock</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p238347624084831"><a name="p238347624084831"></a><a name="p238347624084831"></a>int </p>
<p id="p1153626701084831"><a name="p1153626701084831"></a><a name="p1153626701084831"></a>Locks a mutex. </p>
</td>
</tr>
<tr id="row1859001340084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993807004084831"><a name="p993807004084831"></a><a name="p993807004084831"></a><a href="process.md#ga02a3c64dac70730e226c31c0e7dbb45c">pthread_mutex_unlock</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370172725084831"><a name="p370172725084831"></a><a name="p370172725084831"></a>int </p>
<p id="p187360236084831"><a name="p187360236084831"></a><a name="p187360236084831"></a>Unlocks a mutex. </p>
</td>
</tr>
<tr id="row1235779003084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p438775945084831"><a name="p438775945084831"></a><a name="p438775945084831"></a><a href="process.md#gacc1ccbaf3d76572da85a8030bba1ede4">pthread_mutex_trylock</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2133606930084831"><a name="p2133606930084831"></a><a name="p2133606930084831"></a>int </p>
<p id="p660242088084831"><a name="p660242088084831"></a><a name="p660242088084831"></a>Attempts to lock a mutex. </p>
</td>
</tr>
<tr id="row894940980084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1879399869084831"><a name="p1879399869084831"></a><a name="p1879399869084831"></a><a href="process.md#gabc6a044b418e942b91121b1babb61708">pthread_mutex_timedlock</a> (pthread_mutex_t *__restrict m, const struct <a href="timespec.md">timespec</a> *__restrict at)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030474491084831"><a name="p1030474491084831"></a><a name="p1030474491084831"></a>int </p>
<p id="p1812469817084831"><a name="p1812469817084831"></a><a name="p1812469817084831"></a>Blocks the calling thread to lock a mutex. </p>
</td>
</tr>
<tr id="row820503766084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649748259084831"><a name="p649748259084831"></a><a name="p649748259084831"></a><a href="process.md#gaf89d9cfa300f33b46720a96eac83d175">pthread_mutex_destroy</a> (pthread_mutex_t *m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p544988886084831"><a name="p544988886084831"></a><a name="p544988886084831"></a>int </p>
<p id="p1306499301084831"><a name="p1306499301084831"></a><a name="p1306499301084831"></a>Destroys a mutex. </p>
</td>
</tr>
<tr id="row1907510046084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722057731084831"><a name="p722057731084831"></a><a name="p722057731084831"></a><a href="process.md#gabdf02ed57b055f1920991e96e7d67043">pthread_cond_init</a> (pthread_cond_t *__restrict c, const pthread_condattr_t *__restrict a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415585396084831"><a name="p415585396084831"></a><a name="p415585396084831"></a>int </p>
<p id="p327079038084831"><a name="p327079038084831"></a><a name="p327079038084831"></a>Initializes a condition variable. </p>
</td>
</tr>
<tr id="row821779608084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1329383228084831"><a name="p1329383228084831"></a><a name="p1329383228084831"></a><a href="process.md#ga7f2a7328ee3a7743686adcd2d51771c4">pthread_cond_destroy</a> (pthread_cond_t *c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569925612084831"><a name="p569925612084831"></a><a name="p569925612084831"></a>int </p>
<p id="p411021103084831"><a name="p411021103084831"></a><a name="p411021103084831"></a>Destroys a condition variable. </p>
</td>
</tr>
<tr id="row382249280084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p522537576084831"><a name="p522537576084831"></a><a name="p522537576084831"></a><a href="process.md#gaea601b8ce596a5c54fb12758c56b10a1">pthread_cond_wait</a> (pthread_cond_t *__restrict c, pthread_mutex_t *__restrict m)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564636238084831"><a name="p564636238084831"></a><a name="p564636238084831"></a>int </p>
<p id="p441388351084831"><a name="p441388351084831"></a><a name="p441388351084831"></a>Blocks the calling thread to wait for the condition set by <strong id="b1316206122084831"><a name="b1316206122084831"></a><a name="b1316206122084831"></a>pthread_con_signal()</strong>. </p>
</td>
</tr>
<tr id="row1755515377084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p314053802084831"><a name="p314053802084831"></a><a name="p314053802084831"></a><a href="process.md#ga506c0350d597721ab24bba7129e8e0df">pthread_cond_timedwait</a> (pthread_cond_t *__restrict c, pthread_mutex_t *__restrict m, const struct <a href="timespec.md">timespec</a> *__restrict ts)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1291622451084831"><a name="p1291622451084831"></a><a name="p1291622451084831"></a>int </p>
<p id="p1208583012084831"><a name="p1208583012084831"></a><a name="p1208583012084831"></a>Blocks the calling thread to wait for the condition set by <strong id="b210362209084831"><a name="b210362209084831"></a><a name="b210362209084831"></a>pthread_con_signal()</strong> for a period of time specified by <strong id="b452665276084831"><a name="b452665276084831"></a><a name="b452665276084831"></a>ts</strong>. </p>
</td>
</tr>
<tr id="row1774150005084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788467754084831"><a name="p788467754084831"></a><a name="p788467754084831"></a><a href="process.md#ga1c1ac7c8faaf8ad63e12bc3717f430f3">pthread_cond_broadcast</a> (pthread_cond_t *c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1063472185084831"><a name="p1063472185084831"></a><a name="p1063472185084831"></a>int </p>
<p id="p1860563641084831"><a name="p1860563641084831"></a><a name="p1860563641084831"></a>Unblocks all threads that are currently blocked on the condition variable <strong id="b893356967084831"><a name="b893356967084831"></a><a name="b893356967084831"></a>cond</strong>. </p>
</td>
</tr>
<tr id="row108169007084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1194653832084831"><a name="p1194653832084831"></a><a name="p1194653832084831"></a><a href="process.md#ga9b0f2c7dead8c628e081d76c86a1addc">pthread_cond_signal</a> (pthread_cond_t *c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1938786207084831"><a name="p1938786207084831"></a><a name="p1938786207084831"></a>int </p>
<p id="p783221724084831"><a name="p783221724084831"></a><a name="p783221724084831"></a>Unblocks a thread. </p>
</td>
</tr>
<tr id="row1106926559084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p223804769084831"><a name="p223804769084831"></a><a name="p223804769084831"></a><a href="process.md#ga1cf4bc49696c1a30db31219aef994401">pthread_rwlock_init</a> (pthread_rwlock_t *__restrict rw, const pthread_rwlockattr_t *__restrict a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p338836281084831"><a name="p338836281084831"></a><a name="p338836281084831"></a>int </p>
<p id="p1909951793084831"><a name="p1909951793084831"></a><a name="p1909951793084831"></a>Initializes a read-write lock. </p>
</td>
</tr>
<tr id="row580922433084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844764665084831"><a name="p844764665084831"></a><a name="p844764665084831"></a><a href="process.md#gaa106bb55bdd0e120519d5412823f8b29">pthread_rwlock_destroy</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029789656084831"><a name="p2029789656084831"></a><a name="p2029789656084831"></a>int </p>
<p id="p1476903852084831"><a name="p1476903852084831"></a><a name="p1476903852084831"></a>Destroys a read-write lock. </p>
</td>
</tr>
<tr id="row2041332948084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1589325106084831"><a name="p1589325106084831"></a><a name="p1589325106084831"></a><a href="process.md#ga6153aca32112735053e6cc4a2a290feb">pthread_rwlock_rdlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1379663212084831"><a name="p1379663212084831"></a><a name="p1379663212084831"></a>int </p>
<p id="p83981748084831"><a name="p83981748084831"></a><a name="p83981748084831"></a>Applies a read lock to a read-write lock. </p>
</td>
</tr>
<tr id="row768609467084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904300510084831"><a name="p904300510084831"></a><a name="p904300510084831"></a><a href="process.md#ga3ba2170f06184d12543c4a5b78715fa7">pthread_rwlock_tryrdlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831401027084831"><a name="p1831401027084831"></a><a name="p1831401027084831"></a>int </p>
<p id="p1192924920084831"><a name="p1192924920084831"></a><a name="p1192924920084831"></a>Attempts to apply a read lock to a read-write lock. </p>
</td>
</tr>
<tr id="row1195914500084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123286682084831"><a name="p123286682084831"></a><a name="p123286682084831"></a><a href="process.md#ga8edbe14731fd79a80f72384334266715">pthread_rwlock_timedrdlock</a> (pthread_rwlock_t *__restrict rw, const struct <a href="timespec.md">timespec</a> *__restrict at)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p770106311084831"><a name="p770106311084831"></a><a name="p770106311084831"></a>int </p>
<p id="p2053532631084831"><a name="p2053532631084831"></a><a name="p2053532631084831"></a>Blocks the calling thread to lock a read-write lock for reading. </p>
</td>
</tr>
<tr id="row1753084030084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813612984084831"><a name="p1813612984084831"></a><a name="p1813612984084831"></a><a href="process.md#gaf2ca5563676ae3ac35d3bc7b3547e7f7">pthread_rwlock_wrlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492185166084831"><a name="p1492185166084831"></a><a name="p1492185166084831"></a>int </p>
<p id="p1267324456084831"><a name="p1267324456084831"></a><a name="p1267324456084831"></a>Applies a write lock to a read-write lock. </p>
</td>
</tr>
<tr id="row918921628084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230907731084831"><a name="p1230907731084831"></a><a name="p1230907731084831"></a><a href="process.md#ga2b5044e2da304ae9666fdd4e05479905">pthread_rwlock_trywrlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p121975858084831"><a name="p121975858084831"></a><a name="p121975858084831"></a>int </p>
<p id="p1470047318084831"><a name="p1470047318084831"></a><a name="p1470047318084831"></a>Attempts to apply a write lock to a read-write lock. </p>
</td>
</tr>
<tr id="row1830089508084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402225811084831"><a name="p402225811084831"></a><a name="p402225811084831"></a><a href="process.md#ga3fb8fb33e16653c5ad7b7f092959738e">pthread_rwlock_timedwrlock</a> (pthread_rwlock_t *__restrict rw, const struct <a href="timespec.md">timespec</a> *__restrict at)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2120360381084831"><a name="p2120360381084831"></a><a name="p2120360381084831"></a>int </p>
<p id="p1059318709084831"><a name="p1059318709084831"></a><a name="p1059318709084831"></a>Blocks the calling thread to lock a read-write lock for writing. </p>
</td>
</tr>
<tr id="row1333552980084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334579078084831"><a name="p334579078084831"></a><a name="p334579078084831"></a><a href="process.md#gaffd8a19e83fc87d865d103d6fbce8c4f">pthread_rwlock_unlock</a> (pthread_rwlock_t *rw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1745255417084831"><a name="p1745255417084831"></a><a name="p1745255417084831"></a>int </p>
<p id="p483843727084831"><a name="p483843727084831"></a><a name="p483843727084831"></a>Unlocks a read-write lock. </p>
</td>
</tr>
<tr id="row924591775084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274497422084831"><a name="p1274497422084831"></a><a name="p1274497422084831"></a><a href="process.md#ga665a56a7bed60c8eaa6c28af40d13cd4">pthread_spin_init</a> (pthread_spinlock_t *s, int shared)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1372482964084831"><a name="p1372482964084831"></a><a name="p1372482964084831"></a>int </p>
<p id="p692957053084831"><a name="p692957053084831"></a><a name="p692957053084831"></a>Initializes a spin lock. </p>
</td>
</tr>
<tr id="row1274795186084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p720730290084831"><a name="p720730290084831"></a><a name="p720730290084831"></a><a href="process.md#ga822c2ff425ddad4c25b6a6092c6effff">pthread_spin_destroy</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591624441084831"><a name="p591624441084831"></a><a name="p591624441084831"></a>int </p>
<p id="p1853804188084831"><a name="p1853804188084831"></a><a name="p1853804188084831"></a>Destroys a spin lock. </p>
</td>
</tr>
<tr id="row643274050084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2060205142084831"><a name="p2060205142084831"></a><a name="p2060205142084831"></a><a href="process.md#ga62cfd14d1f937a6e8f966e3a331bcf94">pthread_spin_lock</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p32638432084831"><a name="p32638432084831"></a><a name="p32638432084831"></a>int </p>
<p id="p1599634186084831"><a name="p1599634186084831"></a><a name="p1599634186084831"></a>Locks a spin lock. </p>
</td>
</tr>
<tr id="row748217708084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973610773084831"><a name="p973610773084831"></a><a name="p973610773084831"></a><a href="process.md#ga084834fa2d06f173f086ce23ec1ea5d9">pthread_spin_trylock</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p521643920084831"><a name="p521643920084831"></a><a name="p521643920084831"></a>int </p>
<p id="p416711561084831"><a name="p416711561084831"></a><a name="p416711561084831"></a>Attempts to lock a spin lock. </p>
</td>
</tr>
<tr id="row342366889084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p626798791084831"><a name="p626798791084831"></a><a name="p626798791084831"></a><a href="process.md#ga3fe246007a85cee9d5f7af9b7d592b54">pthread_spin_unlock</a> (pthread_spinlock_t *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1723386011084831"><a name="p1723386011084831"></a><a name="p1723386011084831"></a>int </p>
<p id="p42497869084831"><a name="p42497869084831"></a><a name="p42497869084831"></a>Unlocks a spin lock. </p>
</td>
</tr>
<tr id="row1517454319084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307025977084831"><a name="p1307025977084831"></a><a name="p1307025977084831"></a><a href="process.md#ga4a324cd758cae702213ea41882f4cf41">pthread_barrier_init</a> (pthread_barrier_t *__restrict b, const pthread_barrierattr_t *__restrict a, unsigned count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p432503584084831"><a name="p432503584084831"></a><a name="p432503584084831"></a>int </p>
<p id="p1750743122084831"><a name="p1750743122084831"></a><a name="p1750743122084831"></a>Initializes a barrier. </p>
</td>
</tr>
<tr id="row1721000148084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p213461963084831"><a name="p213461963084831"></a><a name="p213461963084831"></a><a href="process.md#gab05ae13769e61dea9c53ca7894743c8f">pthread_barrier_destroy</a> (pthread_barrier_t *b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405612242084831"><a name="p405612242084831"></a><a name="p405612242084831"></a>int </p>
<p id="p1649906970084831"><a name="p1649906970084831"></a><a name="p1649906970084831"></a>Destroys a barrier. </p>
</td>
</tr>
<tr id="row582820070084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p814744780084831"><a name="p814744780084831"></a><a name="p814744780084831"></a><a href="process.md#gaf786372165ba080986ae4143928c5436">pthread_barrier_wait</a> (pthread_barrier_t *b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p624337739084831"><a name="p624337739084831"></a><a name="p624337739084831"></a>int </p>
<p id="p55238447084831"><a name="p55238447084831"></a><a name="p55238447084831"></a>Synchronizes participating threads at a barrier. </p>
</td>
</tr>
<tr id="row399081808084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133870241084831"><a name="p2133870241084831"></a><a name="p2133870241084831"></a><a href="process.md#gaf4b7ced8ecff505380fe8216244a3764">pthread_key_create</a> (pthread_key_t *key, void(*destructor)(void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069186700084831"><a name="p2069186700084831"></a><a name="p2069186700084831"></a>int </p>
<p id="p1250767680084831"><a name="p1250767680084831"></a><a name="p1250767680084831"></a>Creates a key for thread data. </p>
</td>
</tr>
<tr id="row524405397084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261665856084831"><a name="p261665856084831"></a><a name="p261665856084831"></a><a href="process.md#gaee96306dc79294927ee840bb4de2244b">pthread_key_delete</a> (pthread_key_t key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803698431084831"><a name="p1803698431084831"></a><a name="p1803698431084831"></a>int </p>
<p id="p1781913900084831"><a name="p1781913900084831"></a><a name="p1781913900084831"></a>Deletes a key for thread data. </p>
</td>
</tr>
<tr id="row1490494588084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490043769084831"><a name="p1490043769084831"></a><a name="p1490043769084831"></a><a href="process.md#ga31469375891078185bda93f0e4411a2c">pthread_getspecific</a> (pthread_key_t key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p819819440084831"><a name="p819819440084831"></a><a name="p819819440084831"></a>void * </p>
<p id="p316080855084831"><a name="p316080855084831"></a><a name="p316080855084831"></a>Obtains specific thread data. </p>
</td>
</tr>
<tr id="row97121947084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657109082084831"><a name="p1657109082084831"></a><a name="p1657109082084831"></a><a href="process.md#ga2187333dd46ce08d9d2e044f79fad705">pthread_setspecific</a> (pthread_key_t key, const void *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1738412280084831"><a name="p1738412280084831"></a><a name="p1738412280084831"></a>int </p>
<p id="p1612135869084831"><a name="p1612135869084831"></a><a name="p1612135869084831"></a>Sets specific thread data. </p>
</td>
</tr>
<tr id="row1312726078084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088739510084831"><a name="p2088739510084831"></a><a name="p2088739510084831"></a><a href="process.md#ga0b85ebb1e3aac081a4c0a5e85ae3cbe9">pthread_attr_init</a> (pthread_attr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1405400537084831"><a name="p1405400537084831"></a><a name="p1405400537084831"></a>int </p>
<p id="p600399390084831"><a name="p600399390084831"></a><a name="p600399390084831"></a>Initializes a thread attribute object. </p>
</td>
</tr>
<tr id="row1715876912084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1406195704084831"><a name="p1406195704084831"></a><a name="p1406195704084831"></a><a href="process.md#ga4bcdbf47c17c7dcc51e9f05f5cb56d81">pthread_attr_destroy</a> (pthread_attr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70541783084831"><a name="p70541783084831"></a><a name="p70541783084831"></a>int </p>
<p id="p968125547084831"><a name="p968125547084831"></a><a name="p968125547084831"></a>Destroys a thread attribute object. </p>
</td>
</tr>
<tr id="row1547551324084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p231857140084831"><a name="p231857140084831"></a><a name="p231857140084831"></a><a href="process.md#gaa8b692ecc3880fdd49a4d423ba1ce91e">pthread_attr_getguardsize</a> (const pthread_attr_t *attr, size_t *guardsize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p329296708084831"><a name="p329296708084831"></a><a name="p329296708084831"></a>int </p>
<p id="p617325603084831"><a name="p617325603084831"></a><a name="p617325603084831"></a>Obtains the guard size of a thread attribute object. </p>
</td>
</tr>
<tr id="row345992839084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1235092972084831"><a name="p1235092972084831"></a><a name="p1235092972084831"></a><a href="process.md#ga532b31c11a9d87663053c5342400758c">pthread_attr_setguardsize</a> (pthread_attr_t *attr, size_t guardsize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973287078084831"><a name="p1973287078084831"></a><a name="p1973287078084831"></a>int </p>
<p id="p1291680086084831"><a name="p1291680086084831"></a><a name="p1291680086084831"></a>Sets the guard size for a thread attribute object. </p>
</td>
</tr>
<tr id="row1887143004084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p592771056084831"><a name="p592771056084831"></a><a name="p592771056084831"></a><a href="process.md#gae23600d4670359ab12bfba20db2c9a37">pthread_attr_getstacksize</a> (const pthread_attr_t *attr, size_t *stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756280506084831"><a name="p756280506084831"></a><a name="p756280506084831"></a>int </p>
<p id="p1956529050084831"><a name="p1956529050084831"></a><a name="p1956529050084831"></a>Obtains the stack size of a thread attribute object. </p>
</td>
</tr>
<tr id="row1108864808084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44554055084831"><a name="p44554055084831"></a><a name="p44554055084831"></a><a href="process.md#ga812a9a455ae2ef2bb0dca4fff201a281">pthread_attr_setstacksize</a> (pthread_attr_t *attr, size_t stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2103548279084831"><a name="p2103548279084831"></a><a name="p2103548279084831"></a>int </p>
<p id="p520366593084831"><a name="p520366593084831"></a><a name="p520366593084831"></a>Sets the stack size for a thread attribute object. </p>
</td>
</tr>
<tr id="row364800129084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p699710753084831"><a name="p699710753084831"></a><a name="p699710753084831"></a><a href="process.md#ga391c34da42e68ddd24f5ee0c070d5c4f">pthread_attr_getdetachstate</a> (const pthread_attr_t *attr, int *detachstate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p190337036084831"><a name="p190337036084831"></a><a name="p190337036084831"></a>int </p>
<p id="p1859032902084831"><a name="p1859032902084831"></a><a name="p1859032902084831"></a>Obtains the detach state of a thread attribute object. </p>
</td>
</tr>
<tr id="row555016421084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629362014084831"><a name="p1629362014084831"></a><a name="p1629362014084831"></a><a href="process.md#gae6ee78c307d8467b34a9b0c330993a54">pthread_attr_setdetachstate</a> (pthread_attr_t *attr, int detachstate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1167242567084831"><a name="p1167242567084831"></a><a name="p1167242567084831"></a>int </p>
<p id="p661431418084831"><a name="p661431418084831"></a><a name="p661431418084831"></a>Sets the detach state for a thread attribute object. </p>
</td>
</tr>
<tr id="row149048428084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p881965056084831"><a name="p881965056084831"></a><a name="p881965056084831"></a><a href="process.md#gaec19ad460995a9fe8aeb4eaf2bb1ed1d">pthread_attr_getstack</a> (const pthread_attr_t *attr, void **stackaddr, size_t *stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1048339901084831"><a name="p1048339901084831"></a><a name="p1048339901084831"></a>int </p>
<p id="p672582673084831"><a name="p672582673084831"></a><a name="p672582673084831"></a>Obtains stack attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row1861962987084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1130614847084831"><a name="p1130614847084831"></a><a name="p1130614847084831"></a><a href="process.md#ga94ede89b99a3a4fa17e516d30aaf3409">pthread_attr_setstack</a> (pthread_attr_t *attr, void *stackaddr, size_t stacksize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p441152324084831"><a name="p441152324084831"></a><a name="p441152324084831"></a>int </p>
<p id="p602856745084831"><a name="p602856745084831"></a><a name="p602856745084831"></a>Sets stack attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row889935092084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1480372976084831"><a name="p1480372976084831"></a><a name="p1480372976084831"></a><a href="process.md#ga8a53d8e8b40b2332581ee219c5e4c468">pthread_attr_getscope</a> (const pthread_attr_t *arrt, int *scope)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535245185084831"><a name="p1535245185084831"></a><a name="p1535245185084831"></a>int </p>
<p id="p1305851051084831"><a name="p1305851051084831"></a><a name="p1305851051084831"></a>Obtains contention scope attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row1958429859084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p736339643084831"><a name="p736339643084831"></a><a name="p736339643084831"></a><a href="process.md#ga9f90a3707a1797591661272928c152f9">pthread_attr_setscope</a> (pthread_attr_t *arrt, int scope)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274973072084831"><a name="p1274973072084831"></a><a name="p1274973072084831"></a>int </p>
<p id="p2007504309084831"><a name="p2007504309084831"></a><a name="p2007504309084831"></a>Sets contention scope attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row1913027630084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1269545958084831"><a name="p1269545958084831"></a><a name="p1269545958084831"></a><a href="process.md#gaec4d8127833d1a573aa82539f898a8ed">pthread_attr_getschedpolicy</a> (const pthread_attr_t *attr, int *schedpolicy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061771971084831"><a name="p2061771971084831"></a><a name="p2061771971084831"></a>int </p>
<p id="p1049047212084831"><a name="p1049047212084831"></a><a name="p1049047212084831"></a>Obtains scheduling policy attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row397695594084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p483253293084831"><a name="p483253293084831"></a><a name="p483253293084831"></a><a href="process.md#gab6cb2eb73f04abf328b2f39777c35dca">pthread_attr_setschedpolicy</a> (pthread_attr_t *attr, int schedpolicy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362811922084831"><a name="p1362811922084831"></a><a name="p1362811922084831"></a>int </p>
<p id="p1501814409084831"><a name="p1501814409084831"></a><a name="p1501814409084831"></a>Sets scheduling policy attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row48985152084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691822041084831"><a name="p691822041084831"></a><a name="p691822041084831"></a><a href="process.md#gafd3d272d702481044f8a8cd253fd9b47">pthread_attr_getschedparam</a> (const pthread_attr_t *attr, struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1534724584084831"><a name="p1534724584084831"></a><a name="p1534724584084831"></a>int </p>
<p id="p949790474084831"><a name="p949790474084831"></a><a name="p949790474084831"></a>Obtains scheduling parameter attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row1642692139084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106462006084831"><a name="p106462006084831"></a><a name="p106462006084831"></a><a href="process.md#ga579e6529f0ce482312a5e77ac61cb4d5">pthread_attr_setschedparam</a> (pthread_attr_t *attr, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p894355443084831"><a name="p894355443084831"></a><a name="p894355443084831"></a>int </p>
<p id="p263621543084831"><a name="p263621543084831"></a><a name="p263621543084831"></a>Sets scheduling parameter attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row1743889236084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479594472084831"><a name="p1479594472084831"></a><a name="p1479594472084831"></a><a href="process.md#ga79a77b688c30213e5e52e6be178cde4e">pthread_attr_getinheritsched</a> (const pthread_attr_t *attr, int *inheritsched)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1433533892084831"><a name="p1433533892084831"></a><a name="p1433533892084831"></a>int </p>
<p id="p1814160414084831"><a name="p1814160414084831"></a><a name="p1814160414084831"></a>Obtains inherit scheduler attributes of a thread attribute object. </p>
</td>
</tr>
<tr id="row1541463778084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50885123084831"><a name="p50885123084831"></a><a name="p50885123084831"></a><a href="process.md#gad437fe8caa3ef9f0cb7d69f6f6479df9">pthread_attr_setinheritsched</a> (pthread_attr_t *attr, int inheritsched)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405131685084831"><a name="p405131685084831"></a><a name="p405131685084831"></a>int </p>
<p id="p547736646084831"><a name="p547736646084831"></a><a name="p547736646084831"></a>Sets inherit scheduler attributes for a thread attribute object. </p>
</td>
</tr>
<tr id="row985735702084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620580933084831"><a name="p620580933084831"></a><a name="p620580933084831"></a><a href="process.md#ga2321aabf58224b06021185708d0f9658">pthread_mutexattr_destroy</a> (pthread_mutexattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877499107084831"><a name="p1877499107084831"></a><a name="p1877499107084831"></a>int </p>
<p id="p557249148084831"><a name="p557249148084831"></a><a name="p557249148084831"></a>Destroys a mutex attribute object. </p>
</td>
</tr>
<tr id="row1834053130084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1602544983084831"><a name="p1602544983084831"></a><a name="p1602544983084831"></a><a href="process.md#ga4789e2d3ada7aab2af1458bfec53ee3c">pthread_mutexattr_gettype</a> (const pthread_mutexattr_t *__restrict attr, int *__restrict type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1933104397084831"><a name="p1933104397084831"></a><a name="p1933104397084831"></a>int </p>
<p id="p1656021059084831"><a name="p1656021059084831"></a><a name="p1656021059084831"></a>Obtains the mutex type attribute. </p>
</td>
</tr>
<tr id="row1335849793084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051563756084831"><a name="p2051563756084831"></a><a name="p2051563756084831"></a><a href="process.md#gaf98f6b6c483077a39d1400b1de1577b8">pthread_mutexattr_init</a> (pthread_mutexattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383560030084831"><a name="p1383560030084831"></a><a name="p1383560030084831"></a>int </p>
<p id="p916298987084831"><a name="p916298987084831"></a><a name="p916298987084831"></a>Initializes a mutex attribute object. </p>
</td>
</tr>
<tr id="row1680577948084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1360726988084831"><a name="p1360726988084831"></a><a name="p1360726988084831"></a><a href="process.md#ga8387c80e660e9426f801ac0217ecfae5">pthread_mutexattr_settype</a> (pthread_mutexattr_t *attr, int type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787708123084831"><a name="p1787708123084831"></a><a name="p1787708123084831"></a>int </p>
<p id="p1889169699084831"><a name="p1889169699084831"></a><a name="p1889169699084831"></a>Sets the mutex type attribute. </p>
</td>
</tr>
<tr id="row1937461344084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1766030892084831"><a name="p1766030892084831"></a><a name="p1766030892084831"></a><a href="process.md#ga487a919ab54fd47c8464507031957df0">pthread_condattr_init</a> (pthread_condattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393537776084831"><a name="p393537776084831"></a><a name="p393537776084831"></a>int </p>
<p id="p124172070084831"><a name="p124172070084831"></a><a name="p124172070084831"></a>Initializes a condition variable attribute object. </p>
</td>
</tr>
<tr id="row842013558084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102933516084831"><a name="p1102933516084831"></a><a name="p1102933516084831"></a><a href="process.md#ga8ab009937339c899a5197eea2e48e6a1">pthread_condattr_destroy</a> (pthread_condattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1948093895084831"><a name="p1948093895084831"></a><a name="p1948093895084831"></a>int </p>
<p id="p645025015084831"><a name="p645025015084831"></a><a name="p645025015084831"></a>Destroys a condition variable attribute object. </p>
</td>
</tr>
<tr id="row1194238766084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61272094084831"><a name="p61272094084831"></a><a name="p61272094084831"></a><a href="process.md#gaaf7ac0f85233c0effaf850a9c65b6d68">pthread_condattr_setclock</a> (pthread_condattr_t *a, clockid_t clk)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498304829084831"><a name="p498304829084831"></a><a name="p498304829084831"></a>int </p>
<p id="p675838331084831"><a name="p675838331084831"></a><a name="p675838331084831"></a>Sets a clock for a condition variable attribute object. </p>
</td>
</tr>
<tr id="row1204595935084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451371700084831"><a name="p451371700084831"></a><a name="p451371700084831"></a><a href="process.md#gadcf908971c2ea15ced780025772084e3">pthread_condattr_getclock</a> (const pthread_condattr_t *__restrict a, clockid_t *__restrict clk)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p978804122084831"><a name="p978804122084831"></a><a name="p978804122084831"></a>int </p>
<p id="p117694865084831"><a name="p117694865084831"></a><a name="p117694865084831"></a>Obtains the clock of a condition variable attribute object. </p>
</td>
</tr>
<tr id="row865642635084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p94339740084831"><a name="p94339740084831"></a><a name="p94339740084831"></a><a href="process.md#ga9d831af0179ed16d1b6cbeba0304810b">pthread_rwlockattr_init</a> (pthread_rwlockattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884251426084831"><a name="p1884251426084831"></a><a name="p1884251426084831"></a>int </p>
<p id="p1300943600084831"><a name="p1300943600084831"></a><a name="p1300943600084831"></a>Initializes a read-write lock attribute object. </p>
</td>
</tr>
<tr id="row1025309419084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488661024084831"><a name="p1488661024084831"></a><a name="p1488661024084831"></a><a href="process.md#ga78a54e67f0afe2601dbda0a904fa0bdf">pthread_rwlockattr_destroy</a> (pthread_rwlockattr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p889346200084831"><a name="p889346200084831"></a><a name="p889346200084831"></a>int </p>
<p id="p1292284431084831"><a name="p1292284431084831"></a><a name="p1292284431084831"></a>Destroys a read-write lock attribute object. </p>
</td>
</tr>
<tr id="row1000717963084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p456292394084831"><a name="p456292394084831"></a><a name="p456292394084831"></a><a href="process.md#ga3bd99d89e352ccc51d5b94d157f1218b">pthread_barrierattr_destroy</a> (pthread_barrierattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p919171016084831"><a name="p919171016084831"></a><a name="p919171016084831"></a>int </p>
<p id="p1681371465084831"><a name="p1681371465084831"></a><a name="p1681371465084831"></a>Destroys a barrier attribute object. </p>
</td>
</tr>
<tr id="row1007660618084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1372238609084831"><a name="p1372238609084831"></a><a name="p1372238609084831"></a><a href="process.md#ga2ff720e06488668dc0ae6779755946e6">pthread_barrierattr_init</a> (pthread_barrierattr_t *a)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p643437975084831"><a name="p643437975084831"></a><a name="p643437975084831"></a>int </p>
<p id="p2079628309084831"><a name="p2079628309084831"></a><a name="p2079628309084831"></a>Initializes a barrier attribute object. </p>
</td>
</tr>
<tr id="row1737437712084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p512421754084831"><a name="p512421754084831"></a><a name="p512421754084831"></a><a href="process.md#ga80008474c3d68e9880da960a53d2f430">pthread_atfork</a> (void(*prepare)(void), void(*parent)(void), void(*child)(void))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p612378556084831"><a name="p612378556084831"></a><a name="p612378556084831"></a>int </p>
<p id="p1117042248084831"><a name="p1117042248084831"></a><a name="p1117042248084831"></a>Registers a fork handler to be called before and after <a href="utils.md#gaa4e4714e6e8927c80b2553a40094b6d9">fork()</a>. </p>
</td>
</tr>
<tr id="row1035158548084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1805223837084831"><a name="p1805223837084831"></a><a name="p1805223837084831"></a><a href="process.md#ga68bc26522daf418f3cc78360925374ef">pthread_cleanup_push</a> (void(*routine)(void *), void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p637442076084831"><a name="p637442076084831"></a><a name="p637442076084831"></a>void </p>
<p id="p881017134084831"><a name="p881017134084831"></a><a name="p881017134084831"></a>Pushes the routine to the top of the clean-up handler stack. </p>
</td>
</tr>
<tr id="row61896709084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p270282937084831"><a name="p270282937084831"></a><a name="p270282937084831"></a><a href="process.md#gafbe33fb00cd24693796a0870a3374631">pthread_cleanup_pop</a> (int execute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1174941274084831"><a name="p1174941274084831"></a><a name="p1174941274084831"></a>void </p>
<p id="p907610598084831"><a name="p907610598084831"></a><a name="p907610598084831"></a>Removes the routine at the top of the clean-up handler stack. </p>
</td>
</tr>
<tr id="row81027234084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p180392888084831"><a name="p180392888084831"></a><a name="p180392888084831"></a><a href="process.md#ga6bdca4b2c8a436c4651fb5e8d462408b">pthread_getattr_np</a> (pthread_t thread, pthread_attr_t *attr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p759119449084831"><a name="p759119449084831"></a><a name="p759119449084831"></a>int </p>
<p id="p2024641697084831"><a name="p2024641697084831"></a><a name="p2024641697084831"></a>Obtains the attributes of a created thread. </p>
</td>
</tr>
<tr id="row213558680084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245593825084831"><a name="p1245593825084831"></a><a name="p1245593825084831"></a><a href="process.md#ga185584d77295432838d8b839d916f160">pthread_setname_np</a> (pthread_t pthread, const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790630260084831"><a name="p790630260084831"></a><a name="p790630260084831"></a>int </p>
<p id="p1964451861084831"><a name="p1964451861084831"></a><a name="p1964451861084831"></a>Sets the thread name. </p>
</td>
</tr>
</tbody>
</table>

