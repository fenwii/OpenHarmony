# RTC Usage Guidelines<a name="EN-US_TOPIC_0000001052578218"></a>

## How to Use<a name="section620515765714"></a>

During the OS startup, the HDF loads the RTC driver based on the configuration file. The RTC driver detects the RTC component and initializes the driver.

[Figure 1](#fig166181128151112)  illustrates the process of an RTC device.

**Figure  1**  Process of using an RTC device<a name="fig166181128151112"></a>  


![](figures/en-us_image_0000001054728498.png)

## Creating an RTC Device Handle<a name="section0702183665711"></a>

After the RTC driver is loaded successfully, you can use the API provided by the HDF and call APIs of the RTC driver.

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>Currently, only one RTC device is supported in the OS.

struct DevHandle \*RtcOpen\(void\);

**Table  1**  Description of  **RtcOpen**

<a name="table1380712985611"></a>
<table><tbody><tr id="row580722985616"><td class="cellrowborder" valign="top" width="21.45%"><p id="p1280722911565"><a name="p1280722911565"></a><a name="p1280722911565"></a><strong id="b4807829175617"><a name="b4807829175617"></a><a name="b4807829175617"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p5807112965618"><a name="p5807112965618"></a><a name="p5807112965618"></a><strong id="b47232063818"><a name="b47232063818"></a><a name="b47232063818"></a>Description</strong></p>
</td>
</tr>
<tr id="row17807112935611"><td class="cellrowborder" valign="top" width="21.45%"><p id="p13807132915565"><a name="p13807132915565"></a><a name="p13807132915565"></a>void</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p15807429185612"><a name="p15807429185612"></a><a name="p15807429185612"></a>NA</p>
</td>
</tr>
<tr id="row1980782911567"><td class="cellrowborder" valign="top" width="21.45%"><p id="p0807529165613"><a name="p0807529165613"></a><a name="p0807529165613"></a><strong id="b2807132925619"><a name="b2807132925619"></a><a name="b2807132925619"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p9808162935612"><a name="p9808162935612"></a><a name="p9808162935612"></a><strong id="b1808152910566"><a name="b1808152910566"></a><a name="b1808152910566"></a>Description</strong></p>
</td>
</tr>
<tr id="row2808192935615"><td class="cellrowborder" valign="top" width="21.45%"><p id="p380852915567"><a name="p380852915567"></a><a name="p380852915567"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p26881319114110"><a name="p26881319114110"></a><a name="p26881319114110"></a>Returns the pointer to  if the operation is successful.</p>
</td>
</tr>
<tr id="row4808142945615"><td class="cellrowborder" valign="top" width="21.45%"><p id="p188084291561"><a name="p188084291561"></a><a name="p188084291561"></a>NULL</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p780852912566"><a name="p780852912566"></a><a name="p780852912566"></a>The operation fails.</p>
</td>
</tr>
</tbody>
</table>

```
struct DevHandle * handle = NULL;

/* Obtain the RTC device handle. */
handle = RtcOpen();
if (handle  == NULL) {
    /* Process the error. */
}
```

## Releasing the RTC Device Handle<a name="section639962619542"></a>

You can call the following function to release the RTC device handle, thereby releasing resources of the device:

void RtcClose\(struct DevHandle \*handle\);

**Table  2**  Description of  **RtcClose**

<a name="table37525421510"></a>
<table><tbody><tr id="row10752134216114"><td class="cellrowborder" valign="top" width="21.45%"><p id="p1075217421019"><a name="p1075217421019"></a><a name="p1075217421019"></a><strong id="b1575214428111"><a name="b1575214428111"></a><a name="b1575214428111"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p117531421411"><a name="p117531421411"></a><a name="p117531421411"></a><strong id="b192917915411"><a name="b192917915411"></a><a name="b192917915411"></a>Description</strong></p>
</td>
</tr>
<tr id="row57531442914"><td class="cellrowborder" valign="top" width="21.45%"><p id="p8753164210119"><a name="p8753164210119"></a><a name="p8753164210119"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p17533425113"><a name="p17533425113"></a><a name="p17533425113"></a>Pointer to the RTC device handle</p>
</td>
</tr>
</tbody>
</table>

```
/* Release the RTC device handle. */
RtcClose(handle);
```

## Registering RtcAlarmCallback<a name="section123631358135713"></a>

After the OS is started, call the following function to register  **RtcAlarmCallback**, which will be invoked when an alarm is generated at the specified time:

int32\_t RtcRegisterAlarmCallback\(struct DevHandle \*handle, enum RtcAlarmIndex alarmIndex, RtcAlarmCallback cb\);

**Table  3**  Description of  **RtcRegisterAlarmCallback**

<a name="table7603619123820"></a>
<table><thead align="left"><tr id="row1060351914386"><th class="cellrowborder" valign="top" width="21.36%" id="mcps1.2.3.1.1"><p id="p14603181917382"><a name="p14603181917382"></a><a name="p14603181917382"></a><strong id="b16510829133012"><a name="b16510829133012"></a><a name="b16510829133012"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="78.64%" id="mcps1.2.3.1.2"><p id="p36031519183819"><a name="p36031519183819"></a><a name="p36031519183819"></a><strong id="b4471749184119"><a name="b4471749184119"></a><a name="b4471749184119"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1181618191115"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p131811218131116"><a name="p131811218131116"></a><a name="p131811218131116"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p6181191851111"><a name="p6181191851111"></a><a name="p6181191851111"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row960361918383"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p1775535165418"><a name="p1775535165418"></a><a name="p1775535165418"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p137551851185412"><a name="p137551851185412"></a><a name="p137551851185412"></a>Alarm index</p>
</td>
</tr>
<tr id="row1960431983813"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p3604719123817"><a name="p3604719123817"></a><a name="p3604719123817"></a>cb</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p1560441923818"><a name="p1560441923818"></a><a name="p1560441923818"></a>Callback that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
<tr id="row11410612183019"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p460381915385"><a name="p460381915385"></a><a name="p460381915385"></a><strong id="b4349113243013"><a name="b4349113243013"></a><a name="b4349113243013"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p96031619153812"><a name="p96031619153812"></a><a name="p96031619153812"></a><strong id="b63502322308"><a name="b63502322308"></a><a name="b63502322308"></a>Description</strong></p>
</td>
</tr>
<tr id="row15410111273017"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p133081510112813"><a name="p133081510112813"></a><a name="p133081510112813"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p530813107289"><a name="p530813107289"></a><a name="p530813107289"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row1241081213303"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p1123362173010"><a name="p1123362173010"></a><a name="p1123362173010"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p1723362153010"><a name="p1723362153010"></a><a name="p1723362153010"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

The following is an example of registering  **RtcAlarmCallback**  for processing alarm  **RTC\_ALARM\_INDEX\_A**:

```
/* Register an RTC alarm callback. */
int32_t RtcAlarmACallback(enum RtcAlarmIndex alarmIndex)
{
    if (alarmIndex == RTC_ALARM_INDEX_A) {
        /* Process alarm A. */
    } else if (alarmIndex == RTC_ALARM_INDEX_B) {
        /* Process alarm B. */
    } else {
    /* Process the error. */
    }
    return 0;
}
int32_t ret;
/* Register RtcAlarmCallback for alarm A. */
ret = RtcRegisterAlarmCallback(handle, RTC_ALARM_INDEX_A, RtcAlarmACallback);
if (ret != 0) {
    /* Process the error. */
}
```

## Performing RTC-related Operations<a name="section11091522125812"></a>

-   Reading RTC time

Call the following function to read time information from the RTC driver, including the year, month, the day fo the week, day, hour, minute, second, and millisecond:

int32\_t RtcReadTime\(struct DevHandle \*handle, struct RtcTime \*time\);

**Table  4**  Description of  **RtcReadTime**

<a name="table1018490043"></a>
<table><tbody><tr id="row31848013417"><td class="cellrowborder" valign="top" width="21.45%"><p id="p1415816132411"><a name="p1415816132411"></a><a name="p1415816132411"></a><strong id="b129796117337"><a name="b129796117337"></a><a name="b129796117337"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p11158111316410"><a name="p11158111316410"></a><a name="p11158111316410"></a><strong id="b16343164694820"><a name="b16343164694820"></a><a name="b16343164694820"></a>Description</strong></p>
</td>
</tr>
<tr id="row1246615200297"><td class="cellrowborder" valign="top" width="21.45%"><p id="p188871821142917"><a name="p188871821142917"></a><a name="p188871821142917"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p1788742182910"><a name="p1788742182910"></a><a name="p1788742182910"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row10184701945"><td class="cellrowborder" valign="top" width="21.45%"><p id="p104891871157"><a name="p104891871157"></a><a name="p104891871157"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p204891671156"><a name="p204891671156"></a><a name="p204891671156"></a>Pointer to the time information read from the RTC driver. The time information includes the year, month, the day of the week, day, hour, minute, second, and millisecond. </p>
</td>
</tr>
<tr id="row17393154515328"><td class="cellrowborder" valign="top" width="21.45%"><p id="p8158313248"><a name="p8158313248"></a><a name="p8158313248"></a><strong id="b18542051332"><a name="b18542051332"></a><a name="b18542051332"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p161591413741"><a name="p161591413741"></a><a name="p161591413741"></a><strong id="b45520523313"><a name="b45520523313"></a><a name="b45520523313"></a>Description</strong></p>
</td>
</tr>
<tr id="row339324593215"><td class="cellrowborder" valign="top" width="21.45%"><p id="p139599615287"><a name="p139599615287"></a><a name="p139599615287"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p1895911611284"><a name="p1895911611284"></a><a name="p1895911611284"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row15393184519323"><td class="cellrowborder" valign="top" width="21.45%"><p id="p13521182309"><a name="p13521182309"></a><a name="p13521182309"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p1035216186309"><a name="p1035216186309"></a><a name="p1035216186309"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
struct RtcTime tm;

/* Read time information from the RTC driver. */
ret = RtcReadTime(handle, &tm);
if (ret != 0) {
    /* Process the error. */
}
```

-   Setting RTC time

Call the following function to set the RTC time:

int32\_t RtcWriteTime\(struct DevHandle \*handle, struct RtcTime \*time\);

**Table  5**  Description of  **RtcWriteTime**

<a name="table223910318361"></a>
<table><tbody><tr id="row924033173613"><td class="cellrowborder" valign="top" width="21.54%"><p id="p16240143143611"><a name="p16240143143611"></a><a name="p16240143143611"></a><strong id="b1724033112363"><a name="b1724033112363"></a><a name="b1724033112363"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p32401031113610"><a name="p32401031113610"></a><a name="p32401031113610"></a><strong id="b1676117393490"><a name="b1676117393490"></a><a name="b1676117393490"></a>Description</strong></p>
</td>
</tr>
<tr id="row148011248153018"><td class="cellrowborder" valign="top" width="21.54%"><p id="p189641849113018"><a name="p189641849113018"></a><a name="p189641849113018"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p20964249123013"><a name="p20964249123013"></a><a name="p20964249123013"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row024043193619"><td class="cellrowborder" valign="top" width="21.54%"><p id="p157679281384"><a name="p157679281384"></a><a name="p157679281384"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p167675286381"><a name="p167675286381"></a><a name="p167675286381"></a>Pointer to the time information written into the RTC driver. The time information includes the year, month, the day of the week, day, hour, minute, second, and millisecond. </p>
</td>
</tr>
<tr id="row424093120369"><td class="cellrowborder" valign="top" width="21.54%"><p id="p1240143114366"><a name="p1240143114366"></a><a name="p1240143114366"></a><strong id="b0240173133615"><a name="b0240173133615"></a><a name="b0240173133615"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p18241173133619"><a name="p18241173133619"></a><a name="p18241173133619"></a><strong id="b7241153112361"><a name="b7241153112361"></a><a name="b7241153112361"></a>Description</strong></p>
</td>
</tr>
<tr id="row18241531153610"><td class="cellrowborder" valign="top" width="21.54%"><p id="p8550174182810"><a name="p8550174182810"></a><a name="p8550174182810"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p145503417284"><a name="p145503417284"></a><a name="p145503417284"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row024153123616"><td class="cellrowborder" valign="top" width="21.54%"><p id="p5602191619300"><a name="p5602191619300"></a><a name="p5602191619300"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p12602131643015"><a name="p12602131643015"></a><a name="p12602131643015"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>The RTC start time is 1970/01/01 Thursday 00:00:00 \(UTC\). The maximum value of  **year**  must be set based on the requirements specified in the product manual of the in-use component. You do not need to configure the day of the week.

```
int32_t ret;
struct RtcTime tm;

/* Set the RTC time to UTC 2020/01/01 00:59:00 .000. */
tm.year = 2020;
tm.month = 01;
tm.day = 01;
tm.hour= 00;
tm.minute = 59;
tm.second = 00;
tm.millisecond = 0;
/* Write the RTC time information. */
ret = RtcWriteTime(handle, &tm);
if (ret != 0) {
    /* Process the error. */
}
```

-   Reading the RTC alarm time

Call the following function to read the alarm time:

int32\_t RtcReadAlarm\(struct DevHandle \*handle, enum RtcAlarmIndex alarmIndex, struct RtcTime \*time\);

**Table  6**  Description of  **RtcReadAlarm**

<a name="table11342203111420"></a>
<table><tbody><tr id="row133429310140"><td class="cellrowborder" valign="top" width="21.54%"><p id="p9886411201416"><a name="p9886411201416"></a><a name="p9886411201416"></a><strong id="b38861211101412"><a name="b38861211101412"></a><a name="b38861211101412"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p2886411171417"><a name="p2886411171417"></a><a name="p2886411171417"></a><strong id="b215455625020"><a name="b215455625020"></a><a name="b215455625020"></a>Description</strong></p>
</td>
</tr>
<tr id="row13835647114113"><td class="cellrowborder" valign="top" width="21.54%"><p id="p1183011486412"><a name="p1183011486412"></a><a name="p1183011486412"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p1583074815413"><a name="p1583074815413"></a><a name="p1583074815413"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row113439391410"><td class="cellrowborder" valign="top" width="21.54%"><p id="p132281120194318"><a name="p132281120194318"></a><a name="p132281120194318"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p1022852034315"><a name="p1022852034315"></a><a name="p1022852034315"></a>Alarm index</p>
</td>
</tr>
<tr id="row193431836147"><td class="cellrowborder" valign="top" width="21.54%"><p id="p1926195164011"><a name="p1926195164011"></a><a name="p1926195164011"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p112695144013"><a name="p112695144013"></a><a name="p112695144013"></a>Pointer to the RTC alarm time information. The time information includes the year, month, the day of the week, day, hour, minute, second, and millisecond. </p>
</td>
</tr>
<tr id="row43438361419"><td class="cellrowborder" valign="top" width="21.54%"><p id="p388715117143"><a name="p388715117143"></a><a name="p388715117143"></a><strong id="b9887011121415"><a name="b9887011121415"></a><a name="b9887011121415"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p088719117143"><a name="p088719117143"></a><a name="p088719117143"></a><strong id="b1788714110146"><a name="b1788714110146"></a><a name="b1788714110146"></a>Description</strong></p>
</td>
</tr>
<tr id="row17169595467"><td class="cellrowborder" valign="top" width="21.54%"><p id="p107751111283"><a name="p107751111283"></a><a name="p107751111283"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p87751917289"><a name="p87751917289"></a><a name="p87751917289"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row016911915461"><td class="cellrowborder" valign="top" width="21.54%"><p id="p6833213133013"><a name="p6833213133013"></a><a name="p6833213133013"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p168341213143015"><a name="p168341213143015"></a><a name="p168341213143015"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
struct RtcTime alarmTime;

/* Read the RTC alarm time information of alarm RTC_ALARM_INDEX_A. */
ret = RtcReadAlarm(handle, RTC_ALARM_INDEX_A, &alarmTime);
if (ret != 0) {
    /* Process the error. */
}
```

-   Setting RTC alarm time

Call the following function to set the RTC alarm time based on the alarm index:

int32\_t RtcWriteAlarm\(struct DevHandle \*handle, enum RtcAlarmIndex  alarmIndex, struct RtcTime \*time\);

**Table  7**  Description of  **RtcWriteAlarm**

<a name="table107922162179"></a>
<table><tbody><tr id="row14793316131710"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1891718412183"><a name="p1891718412183"></a><a name="p1891718412183"></a><strong id="b11841849174820"><a name="b11841849174820"></a><a name="b11841849174820"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p891712461814"><a name="p891712461814"></a><a name="p891712461814"></a><strong id="b19311844125113"><a name="b19311844125113"></a><a name="b19311844125113"></a>Description</strong></p>
</td>
</tr>
<tr id="row18419611133117"><td class="cellrowborder" valign="top" width="21.62%"><p id="p075881210314"><a name="p075881210314"></a><a name="p075881210314"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p975811215317"><a name="p975811215317"></a><a name="p975811215317"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row11793151613176"><td class="cellrowborder" valign="top" width="21.62%"><p id="p562522145215"><a name="p562522145215"></a><a name="p562522145215"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p126257215217"><a name="p126257215217"></a><a name="p126257215217"></a>Alarm index</p>
</td>
</tr>
<tr id="row37932016201720"><td class="cellrowborder" valign="top" width="21.62%"><p id="p26269212527"><a name="p26269212527"></a><a name="p26269212527"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p462602125211"><a name="p462602125211"></a><a name="p462602125211"></a>Pointer to the RTC alarm time information. The time information includes the year, month, the day of the week, day, hour, minute, second, and millisecond. </p>
</td>
</tr>
<tr id="row586915225485"><td class="cellrowborder" valign="top" width="21.62%"><p id="p591712441810"><a name="p591712441810"></a><a name="p591712441810"></a><strong id="b1992335254811"><a name="b1992335254811"></a><a name="b1992335254811"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1591720461810"><a name="p1591720461810"></a><a name="p1591720461810"></a><strong id="b792425244814"><a name="b792425244814"></a><a name="b792425244814"></a>Description</strong></p>
</td>
</tr>
<tr id="row19869122210483"><td class="cellrowborder" valign="top" width="21.62%"><p id="p10798105812717"><a name="p10798105812717"></a><a name="p10798105812717"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1179817586276"><a name="p1179817586276"></a><a name="p1179817586276"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row1686918225483"><td class="cellrowborder" valign="top" width="21.62%"><p id="p16246181033012"><a name="p16246181033012"></a><a name="p16246181033012"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p3246111019309"><a name="p3246111019309"></a><a name="p3246111019309"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>The RTC start time is 1970/01/01 Thursday 00:00:00 \(UTC\). The maximum value of  **year**  must be set based on the requirements specified in the product manual of the in-use component. You do not need to configure the day of the week.

```
int32_t ret;
struct RtcTime alarmTime;

/* Set the RTC alarm time to 2020/01/01 00:59:59 .000. */
alarmTime.year = 2020;
alarmTime.month = 01;
alarmTime.day = 01;
alarmTime.hour = 00;
alarmTime.minute = 59;
alarmTime.second = 59;
alarmTime.millisecond = 0;
/* Set the alarm time of alarm RTC_ALARM_INDEX_A. */
ret = RtcWriteAlarm(handle, RTC_ALARM_INDEX_A, &alarmTime);
if (ret != 0) {
    /* Process the error. */
}
```

-   Enabling or disabling alarm interrupts

Before performing alarm operations, use this function to enable alarm interrupts, so that  **RtcAlarmCallback**  will be called when the alarm is not generated upon a timeout.

int32\_t RtcAlarmInterruptEnable\(struct DevHandle \*handle, enum RtcAlarmIndex alarmIndex, uint8\_t enable\);

**Table  8**  Description of  **RtcAlarmInterruptEnable**

<a name="table1934615314159"></a>
<table><tbody><tr id="row5346853171519"><td class="cellrowborder" valign="top" width="21.36%"><p id="p143464533153"><a name="p143464533153"></a><a name="p143464533153"></a><strong id="b63463534157"><a name="b63463534157"></a><a name="b63463534157"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p113461853171514"><a name="p113461853171514"></a><a name="p113461853171514"></a><strong id="b47410218565"><a name="b47410218565"></a><a name="b47410218565"></a>Description</strong></p>
</td>
</tr>
<tr id="row2125652144213"><td class="cellrowborder" valign="top" width="21.36%"><p id="p3150105313422"><a name="p3150105313422"></a><a name="p3150105313422"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p9151653144212"><a name="p9151653144212"></a><a name="p9151653144212"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row153794518293"><td class="cellrowborder" valign="top" width="21.36%"><p id="p4259165518294"><a name="p4259165518294"></a><a name="p4259165518294"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p725985522917"><a name="p725985522917"></a><a name="p725985522917"></a>Alarm index</p>
</td>
</tr>
<tr id="row19346653141518"><td class="cellrowborder" valign="top" width="21.36%"><p id="p6346253101516"><a name="p6346253101516"></a><a name="p6346253101516"></a>enable</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p234655341511"><a name="p234655341511"></a><a name="p234655341511"></a>Whether to enable RTC alarm interrupts. Value <strong id="b214115020922037"><a name="b214115020922037"></a><a name="b214115020922037"></a>1</strong> means to enable alarm interrupts and value <strong id="b116937965922037"><a name="b116937965922037"></a><a name="b116937965922037"></a>0</strong> means to disable alarm interrupts.</p>
</td>
</tr>
<tr id="row18346953111513"><td class="cellrowborder" valign="top" width="21.36%"><p id="p53460537156"><a name="p53460537156"></a><a name="p53460537156"></a><strong id="b23461553171512"><a name="b23461553171512"></a><a name="b23461553171512"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p4346153171510"><a name="p4346153171510"></a><a name="p4346153171510"></a><strong id="b1834675316154"><a name="b1834675316154"></a><a name="b1834675316154"></a>Description</strong></p>
</td>
</tr>
<tr id="row1234685314151"><td class="cellrowborder" valign="top" width="21.36%"><p id="p8947195310279"><a name="p8947195310279"></a><a name="p8947195310279"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p99471953152712"><a name="p99471953152712"></a><a name="p99471953152712"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row2347115321514"><td class="cellrowborder" valign="top" width="21.36%"><p id="p324855163018"><a name="p324855163018"></a><a name="p324855163018"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p7248857302"><a name="p7248857302"></a><a name="p7248857302"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;

/* Enable the RTC alarm interrupts. */
ret = RtcAlarmInterruptEnable(handle, RTC_ALARM_INDEX_A, 1);
if (ret != 0) {
    /* Process the error. */
}
```

-   Reading RTC external frequency

Call the following function to read the frequency of the external crystal oscillator connected to the RTC driver:

int32\_t RtcGetFreq\(struct DevHandle \*handle, uint32\_t \*freq\);

**Table  9**  Description of  **RtcGetFreq**

<a name="table125881625185"></a>
<table><tbody><tr id="row1458811241816"><td class="cellrowborder" valign="top" width="21.36%"><p id="p658820241813"><a name="p658820241813"></a><a name="p658820241813"></a><strong id="b1358817216185"><a name="b1358817216185"></a><a name="b1358817216185"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p758812261820"><a name="p758812261820"></a><a name="p758812261820"></a><strong id="b1838823105710"><a name="b1838823105710"></a><a name="b1838823105710"></a>Description</strong></p>
</td>
</tr>
<tr id="row831259124219"><td class="cellrowborder" valign="top" width="21.36%"><p id="p171541407431"><a name="p171541407431"></a><a name="p171541407431"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p715413094314"><a name="p715413094314"></a><a name="p715413094314"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row1358842171820"><td class="cellrowborder" valign="top" width="21.36%"><p id="p258814210188"><a name="p258814210188"></a><a name="p258814210188"></a>freq</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p165888211810"><a name="p165888211810"></a><a name="p165888211810"></a>Frequency to set for the external crystal oscillator, in Hz</p>
</td>
</tr>
<tr id="row2058818281817"><td class="cellrowborder" valign="top" width="21.36%"><p id="p458872151810"><a name="p458872151810"></a><a name="p458872151810"></a><strong id="b658814210189"><a name="b658814210189"></a><a name="b658814210189"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p155880251819"><a name="p155880251819"></a><a name="p155880251819"></a><strong id="b558816211182"><a name="b558816211182"></a><a name="b558816211182"></a>Description</strong></p>
</td>
</tr>
<tr id="row35883213183"><td class="cellrowborder" valign="top" width="21.36%"><p id="p8133145211272"><a name="p8133145211272"></a><a name="p8133145211272"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p13133352202719"><a name="p13133352202719"></a><a name="p13133352202719"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row135892261811"><td class="cellrowborder" valign="top" width="21.36%"><p id="p152692538292"><a name="p152692538292"></a><a name="p152692538292"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p327015313294"><a name="p327015313294"></a><a name="p327015313294"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint32_t freq = 0;

/* Read frequency of the external crystal oscillator connected to the RTC driver */
ret = RtcGetFreq(handle, &freq);
if (ret != 0) {
    /* Process the error. */
}
```

-   Setting the frequency of the external crystal oscillator connected to the RTC driver

Call the following function to set the frequency of the external crystal oscillator connected to the RTC driver:

int32\_t RtcSetFreq\(struct DevHandle \*handle, uint32\_t freq\);

**Table  10**  Description of  **RtcSetFreq**

<a name="table1170124316209"></a>
<table><tbody><tr id="row270119432202"><td class="cellrowborder" valign="top" width="21.36%"><p id="p127011343132010"><a name="p127011343132010"></a><a name="p127011343132010"></a><strong id="b970114382014"><a name="b970114382014"></a><a name="b970114382014"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p7701184372013"><a name="p7701184372013"></a><a name="p7701184372013"></a><strong id="b1785917225582"><a name="b1785917225582"></a><a name="b1785917225582"></a>Description</strong></p>
</td>
</tr>
<tr id="row36067554319"><td class="cellrowborder" valign="top" width="21.36%"><p id="p881511716433"><a name="p881511716433"></a><a name="p881511716433"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p188157714432"><a name="p188157714432"></a><a name="p188157714432"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row127019437204"><td class="cellrowborder" valign="top" width="21.36%"><p id="p27019438207"><a name="p27019438207"></a><a name="p27019438207"></a>freq</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p167021043182011"><a name="p167021043182011"></a><a name="p167021043182011"></a>Frequency to set for the external crystal oscillator, in Hz</p>
</td>
</tr>
<tr id="row97022434205"><td class="cellrowborder" valign="top" width="21.36%"><p id="p1770218431208"><a name="p1770218431208"></a><a name="p1770218431208"></a><strong id="b107021743132010"><a name="b107021743132010"></a><a name="b107021743132010"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p1170217432201"><a name="p1170217432201"></a><a name="p1170217432201"></a><strong id="b3702243202015"><a name="b3702243202015"></a><a name="b3702243202015"></a>Description</strong></p>
</td>
</tr>
<tr id="row1670212432206"><td class="cellrowborder" valign="top" width="21.36%"><p id="p77021543152017"><a name="p77021543152017"></a><a name="p77021543152017"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p770214310209"><a name="p770214310209"></a><a name="p770214310209"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row10702194313201"><td class="cellrowborder" valign="top" width="21.36%"><p id="p165182216306"><a name="p165182216306"></a><a name="p165182216306"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p651815219302"><a name="p651815219302"></a><a name="p651815219302"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint32_t freq = 32768; /* 32768 Hz */

/* Set the frequency of the external crystal oscillator. Note that the frequency must be configured in accordance with the requirements specified in the product manual of the in-use component. */
ret = RtcSetFreq(handle, freq);
if (ret != 0) {
    /* Process the error. */
}
```

-   Resetting the RTC driver

Call the following function to perform a reset on the RTC driver. After the reset, the registers are restored to the default values:

int32\_t RtcReset\(struct DevHandle \*handle\);

**Table  11**  Description of  **RtcReset**

<a name="table398973152517"></a>
<table><tbody><tr id="row179899311254"><td class="cellrowborder" valign="top" width="21.36%"><p id="p199899314257"><a name="p199899314257"></a><a name="p199899314257"></a><strong id="b3989163192516"><a name="b3989163192516"></a><a name="b3989163192516"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p179897315257"><a name="p179897315257"></a><a name="p179897315257"></a><strong id="b868445912581"><a name="b868445912581"></a><a name="b868445912581"></a>Description</strong></p>
</td>
</tr>
<tr id="row14989113118257"><td class="cellrowborder" valign="top" width="21.36%"><p id="p129018136436"><a name="p129018136436"></a><a name="p129018136436"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p290111304310"><a name="p290111304310"></a><a name="p290111304310"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row7989123111254"><td class="cellrowborder" valign="top" width="21.36%"><p id="p129894313251"><a name="p129894313251"></a><a name="p129894313251"></a><strong id="b7989931162516"><a name="b7989931162516"></a><a name="b7989931162516"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p799013112256"><a name="p799013112256"></a><a name="p799013112256"></a><strong id="b499053112519"><a name="b499053112519"></a><a name="b499053112519"></a>Description</strong></p>
</td>
</tr>
<tr id="row9990193142513"><td class="cellrowborder" valign="top" width="21.36%"><p id="p1999043111257"><a name="p1999043111257"></a><a name="p1999043111257"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p1799093182516"><a name="p1799093182516"></a><a name="p1799093182516"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row16990133152516"><td class="cellrowborder" valign="top" width="21.36%"><p id="p17536173573015"><a name="p17536173573015"></a><a name="p17536173573015"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p1153623503014"><a name="p1153623503014"></a><a name="p1153623503014"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;

/* Reset the RTC driver. After the reset, the configuration registers are restored to the default values. */
ret = RtcReset(handle);
if (ret != 0) {
    /* Process the error. */
}
```

-   Reading the configuration of a custom RTC register

Call the following function to read the configuration of a custom RTC register based on the register index \(one index corresponds to one byte of the configuration value\):

int32\_t RtcReadReg\(struct DevHandle \*handle, uint8\_t usrDefIndex, uint8\_t \*value\);

**Table  12**  Description of  **RtcReadReg**

<a name="table1624674153319"></a>
<table><tbody><tr id="row92469423320"><td class="cellrowborder" valign="top" width="21.62%"><p id="p102461548331"><a name="p102461548331"></a><a name="p102461548331"></a><strong id="b224610493313"><a name="b224610493313"></a><a name="b224610493313"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p15246847331"><a name="p15246847331"></a><a name="p15246847331"></a><strong id="b9971203213597"><a name="b9971203213597"></a><a name="b9971203213597"></a>Description</strong></p>
</td>
</tr>
<tr id="row171318200434"><td class="cellrowborder" valign="top" width="21.62%"><p id="p9895321184320"><a name="p9895321184320"></a><a name="p9895321184320"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p68951214436"><a name="p68951214436"></a><a name="p68951214436"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row324614143314"><td class="cellrowborder" valign="top" width="21.62%"><p id="p82466433320"><a name="p82466433320"></a><a name="p82466433320"></a>usrDefIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p181671825470"><a name="p181671825470"></a><a name="p181671825470"></a>Index of the custom register</p>
</td>
</tr>
<tr id="row524716420334"><td class="cellrowborder" valign="top" width="21.62%"><p id="p8247844333"><a name="p8247844333"></a><a name="p8247844333"></a>value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p524711413319"><a name="p524711413319"></a><a name="p524711413319"></a>Register value</p>
</td>
</tr>
<tr id="row112471143334"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1124716483312"><a name="p1124716483312"></a><a name="p1124716483312"></a><strong id="b192476416337"><a name="b192476416337"></a><a name="b192476416337"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1524716443313"><a name="p1524716443313"></a><a name="p1524716443313"></a><strong id="b72472473313"><a name="b72472473313"></a><a name="b72472473313"></a>Description</strong></p>
</td>
</tr>
<tr id="row9247194183314"><td class="cellrowborder" valign="top" width="21.62%"><p id="p62476410334"><a name="p62476410334"></a><a name="p62476410334"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p152471433317"><a name="p152471433317"></a><a name="p152471433317"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row1424719410333"><td class="cellrowborder" valign="top" width="21.62%"><p id="p112477417335"><a name="p112477417335"></a><a name="p112477417335"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p7247547338"><a name="p7247547338"></a><a name="p7247547338"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t usrDefIndex = 0; /* Define index 0 for the first custom register. */
uint8_t value = 0;

/* Read the configuration of a custom RTC register based on the register index. One index corresponds to one byte of the configuration value. */
ret = RtcReadReg(handle, usrDefIndex, &value);
if (ret != 0) {
    /* Process the error. */
}
```

-   Setting the configuration of a custom RTC register

Call the following function to configure a register based on the specified register index \(one index corresponds to one byte of the configuration value\):

int32\_t RtcWriteReg\(struct DevHandle \*handle, uint8\_t usrDefIndex, uint8\_t value\);

**Table  13**  Description of  **RtcWriteReg**

<a name="table1072216482360"></a>
<table><tbody><tr id="row187221648133611"><td class="cellrowborder" valign="top" width="21.62%"><p id="p2722184823617"><a name="p2722184823617"></a><a name="p2722184823617"></a><strong id="b18723134883614"><a name="b18723134883614"></a><a name="b18723134883614"></a>Parameter</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1372374810367"><a name="p1372374810367"></a><a name="p1372374810367"></a><strong id="b4284919601"><a name="b4284919601"></a><a name="b4284919601"></a>Description</strong></p>
</td>
</tr>
<tr id="row1675092612435"><td class="cellrowborder" valign="top" width="21.62%"><p id="p7783927144312"><a name="p7783927144312"></a><a name="p7783927144312"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p197831427134310"><a name="p197831427134310"></a><a name="p197831427134310"></a>Pointer to the RTC device handle</p>
</td>
</tr>
<tr id="row1723174815367"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1972364814366"><a name="p1972364814366"></a><a name="p1972364814366"></a>usrDefIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p18723184819365"><a name="p18723184819365"></a><a name="p18723184819365"></a>Index of the custom register</p>
</td>
</tr>
<tr id="row2723548163611"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1772364893610"><a name="p1772364893610"></a><a name="p1772364893610"></a>value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1772324803619"><a name="p1772324803619"></a><a name="p1772324803619"></a>Register value</p>
</td>
</tr>
<tr id="row1072314482361"><td class="cellrowborder" valign="top" width="21.62%"><p id="p6723194853618"><a name="p6723194853618"></a><a name="p6723194853618"></a><strong id="b14723194863611"><a name="b14723194863611"></a><a name="b14723194863611"></a>Return Value</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1872314893614"><a name="p1872314893614"></a><a name="p1872314893614"></a><strong id="b8723154812365"><a name="b8723154812365"></a><a name="b8723154812365"></a>Description</strong></p>
</td>
</tr>
<tr id="row20723148173617"><td class="cellrowborder" valign="top" width="21.62%"><p id="p12723348133615"><a name="p12723348133615"></a><a name="p12723348133615"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p472324873620"><a name="p472324873620"></a><a name="p472324873620"></a>The operation is successful.</p>
</td>
</tr>
<tr id="row127231848123615"><td class="cellrowborder" valign="top" width="21.62%"><p id="p197231148173613"><a name="p197231148173613"></a><a name="p197231148173613"></a>Negative value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p16723134823618"><a name="p16723134823618"></a><a name="p16723134823618"></a>The operation fails. </p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t usrDefIndex = 0; /* Define index 0 for the first custom register. */
uint8_t value = 0x10;

/* Configure a register based on the specified register index. One index corresponds to one byte of the configuration value. */
ret = RtcWriteReg(handle, usrDefIndex, value);
if (ret != 0) {
    /* Process the error. */
}
```

