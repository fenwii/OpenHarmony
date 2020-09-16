# RTC使用指导<a name="ZH-CN_TOPIC_0000001052578218"></a>

## 使用流程<a name="section620515765714"></a>

在操作系统启动过程中，驱动管理模块根据配置文件加载RTC驱动，RTC驱动会检测RTC器件并初始化驱动。

使用RTC设备的一般流程如[图1](#fig166181128151112)所示。

**图 1**  RTC设备使用流程图<a name="fig166181128151112"></a>  


![](figures/zh-cn_image_0000001054728498.png)

## 创建RTC设备句柄<a name="section0702183665711"></a>

RTC驱动加载成功后，驱动开发者使用驱动框架提供的查询接口并调用RTC设备驱动接口。

>![](public_sys-resources/icon-note.gif) **说明：** 
>当前操作系统支持一个RTC设备。

struct DevHandle \*RtcOpen\(void\);

**表 1**  RtcOpen参数和返回值描述

<a name="table1380712985611"></a>
<table><tbody><tr id="row580722985616"><td class="cellrowborder" valign="top" width="21.45%"><p id="p1280722911565"><a name="p1280722911565"></a><a name="p1280722911565"></a><strong id="b4807829175617"><a name="b4807829175617"></a><a name="b4807829175617"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p5807112965618"><a name="p5807112965618"></a><a name="p5807112965618"></a><strong id="b11807172912564"><a name="b11807172912564"></a><a name="b11807172912564"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row17807112935611"><td class="cellrowborder" valign="top" width="21.45%"><p id="p13807132915565"><a name="p13807132915565"></a><a name="p13807132915565"></a>void</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p15807429185612"><a name="p15807429185612"></a><a name="p15807429185612"></a>NA</p>
</td>
</tr>
<tr id="row1980782911567"><td class="cellrowborder" valign="top" width="21.45%"><p id="p0807529165613"><a name="p0807529165613"></a><a name="p0807529165613"></a><strong id="b2807132925619"><a name="b2807132925619"></a><a name="b2807132925619"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p9808162935612"><a name="p9808162935612"></a><a name="p9808162935612"></a><strong id="b1808152910566"><a name="b1808152910566"></a><a name="b1808152910566"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row2808192935615"><td class="cellrowborder" valign="top" width="21.45%"><p id="p380852915567"><a name="p380852915567"></a><a name="p380852915567"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p26881319114110"><a name="p26881319114110"></a><a name="p26881319114110"></a>操作成功返回  指针类型</p>
</td>
</tr>
<tr id="row4808142945615"><td class="cellrowborder" valign="top" width="21.45%"><p id="p188084291561"><a name="p188084291561"></a><a name="p188084291561"></a>NULL</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p780852912566"><a name="p780852912566"></a><a name="p780852912566"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
struct DevHandle * handle = NULL;

/* 获取RTC句柄 */
handle = RtcOpen();
if (handle  == NULL) {
    /* 错误处理 */
}
```

## 销毁RTC设备句柄<a name="section639962619542"></a>

销毁RTC设备句柄，系统释放对应的资源。

void RtcClose\(struct DevHandle \*handle\);

**表 2**  RtcClose参数描述

<a name="table37525421510"></a>
<table><tbody><tr id="row10752134216114"><td class="cellrowborder" valign="top" width="21.45%"><p id="p1075217421019"><a name="p1075217421019"></a><a name="p1075217421019"></a><strong id="b1575214428111"><a name="b1575214428111"></a><a name="b1575214428111"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p117531421411"><a name="p117531421411"></a><a name="p117531421411"></a><strong id="b37535425119"><a name="b37535425119"></a><a name="b37535425119"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row57531442914"><td class="cellrowborder" valign="top" width="21.45%"><p id="p8753164210119"><a name="p8753164210119"></a><a name="p8753164210119"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p17533425113"><a name="p17533425113"></a><a name="p17533425113"></a>RTC设备句柄</p>
</td>
</tr>
</tbody>
</table>

```
/* 销毁RTC句柄 */
RtcClose(handle);
```

## 注册RTC定时报警回调函数<a name="section123631358135713"></a>

系统启动后需要注册RTC定时报警回调函数，报警超时后触发回调函数。

int32\_t RtcRegisterAlarmCallback\(struct DevHandle \*handle, enum RtcAlarmIndex alarmIndex, RtcAlarmCallback cb\);

**表 3**  RtcRegisterAlarmCallback参数和返回值描述

<a name="table7603619123820"></a>
<table><thead align="left"><tr id="row1060351914386"><th class="cellrowborder" valign="top" width="21.36%" id="mcps1.2.3.1.1"><p id="p14603181917382"><a name="p14603181917382"></a><a name="p14603181917382"></a><strong id="b16510829133012"><a name="b16510829133012"></a><a name="b16510829133012"></a>参数</strong></p>
</th>
<th class="cellrowborder" valign="top" width="78.64%" id="mcps1.2.3.1.2"><p id="p36031519183819"><a name="p36031519183819"></a><a name="p36031519183819"></a><strong id="b65222293309"><a name="b65222293309"></a><a name="b65222293309"></a>参数描述</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1181618191115"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p131811218131116"><a name="p131811218131116"></a><a name="p131811218131116"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p6181191851111"><a name="p6181191851111"></a><a name="p6181191851111"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row960361918383"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p1775535165418"><a name="p1775535165418"></a><a name="p1775535165418"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p137551851185412"><a name="p137551851185412"></a><a name="p137551851185412"></a>报警索引</p>
</td>
</tr>
<tr id="row1960431983813"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p3604719123817"><a name="p3604719123817"></a><a name="p3604719123817"></a>cb</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p1560441923818"><a name="p1560441923818"></a><a name="p1560441923818"></a>定时报警回调函数</p>
</td>
</tr>
<tr id="row11410612183019"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p460381915385"><a name="p460381915385"></a><a name="p460381915385"></a><strong id="b4349113243013"><a name="b4349113243013"></a><a name="b4349113243013"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p96031619153812"><a name="p96031619153812"></a><a name="p96031619153812"></a><strong id="b63502322308"><a name="b63502322308"></a><a name="b63502322308"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row15410111273017"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p133081510112813"><a name="p133081510112813"></a><a name="p133081510112813"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p530813107289"><a name="p530813107289"></a><a name="p530813107289"></a>操作成功</p>
</td>
</tr>
<tr id="row1241081213303"><td class="cellrowborder" valign="top" width="21.36%" headers="mcps1.2.3.1.1 "><p id="p1123362173010"><a name="p1123362173010"></a><a name="p1123362173010"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%" headers="mcps1.2.3.1.2 "><p id="p1723362153010"><a name="p1723362153010"></a><a name="p1723362153010"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

注册RTC\_ALARM\_INDEX\_A的定时报警处理函数， 示例如下：

```
/* 用户注册RTC定时报警回调函数的方法 */
int32_t RtcAlarmACallback(enum RtcAlarmIndex alarmIndex)
{
    if (alarmIndex == RTC_ALARM_INDEX_A) {
        /* 报警A的处理 */
    } else if (alarmIndex == RTC_ALARM_INDEX_B) {
        /* 报警B的处理 */
    } else {
        /* 错误处理 */
    }
    return 0;
}
int32_t ret;
/* 注册报警A的定时回调函数 */
ret = RtcRegisterAlarmCallback(handle, RTC_ALARM_INDEX_A, RtcAlarmACallback);
if (ret != 0) {
    /* 错误处理 */
}
```

## 操作RTC<a name="section11091522125812"></a>

-   读取RTC时间。

系统从RTC读取时间信息，包括年、月、星期、日、时、分、秒、毫秒，则可以通过以下函数完成：

int32\_t RtcReadTime\(struct DevHandle \*handle, struct RtcTime \*time\);

**表 4**  RtcReadTime参数和返回值描述

<a name="table1018490043"></a>
<table><tbody><tr id="row31848013417"><td class="cellrowborder" valign="top" width="21.45%"><p id="p1415816132411"><a name="p1415816132411"></a><a name="p1415816132411"></a><strong id="b129796117337"><a name="b129796117337"></a><a name="b129796117337"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p11158111316410"><a name="p11158111316410"></a><a name="p11158111316410"></a><strong id="b1699118123314"><a name="b1699118123314"></a><a name="b1699118123314"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row1246615200297"><td class="cellrowborder" valign="top" width="21.45%"><p id="p188871821142917"><a name="p188871821142917"></a><a name="p188871821142917"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p1788742182910"><a name="p1788742182910"></a><a name="p1788742182910"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row10184701945"><td class="cellrowborder" valign="top" width="21.45%"><p id="p104891871157"><a name="p104891871157"></a><a name="p104891871157"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p204891671156"><a name="p204891671156"></a><a name="p204891671156"></a>RTC读取时间信息，包括年、月、星期、日、时、分、秒、毫秒</p>
</td>
</tr>
<tr id="row17393154515328"><td class="cellrowborder" valign="top" width="21.45%"><p id="p8158313248"><a name="p8158313248"></a><a name="p8158313248"></a><strong id="b18542051332"><a name="b18542051332"></a><a name="b18542051332"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p161591413741"><a name="p161591413741"></a><a name="p161591413741"></a><strong id="b45520523313"><a name="b45520523313"></a><a name="b45520523313"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row339324593215"><td class="cellrowborder" valign="top" width="21.45%"><p id="p139599615287"><a name="p139599615287"></a><a name="p139599615287"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p1895911611284"><a name="p1895911611284"></a><a name="p1895911611284"></a>操作成功</p>
</td>
</tr>
<tr id="row15393184519323"><td class="cellrowborder" valign="top" width="21.45%"><p id="p13521182309"><a name="p13521182309"></a><a name="p13521182309"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.55%"><p id="p1035216186309"><a name="p1035216186309"></a><a name="p1035216186309"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
struct RtcTime tm;

/* 系统从RTC读取时间信息 */
ret = RtcReadTime(handle, &tm);
if (ret != 0) {
    /* 错误处理 */
}
```

-   设置RTC时间

设置RTC时间，则可以通过以下函数完成:

int32\_t RtcWriteTime\(struct DevHandle \*handle, struct RtcTime \*time\);

**表 5**  RtcWriteTime参数和返回值描述

<a name="table223910318361"></a>
<table><tbody><tr id="row924033173613"><td class="cellrowborder" valign="top" width="21.54%"><p id="p16240143143611"><a name="p16240143143611"></a><a name="p16240143143611"></a><strong id="b1724033112363"><a name="b1724033112363"></a><a name="b1724033112363"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p32401031113610"><a name="p32401031113610"></a><a name="p32401031113610"></a><strong id="b1324013111363"><a name="b1324013111363"></a><a name="b1324013111363"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row148011248153018"><td class="cellrowborder" valign="top" width="21.54%"><p id="p189641849113018"><a name="p189641849113018"></a><a name="p189641849113018"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p20964249123013"><a name="p20964249123013"></a><a name="p20964249123013"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row024043193619"><td class="cellrowborder" valign="top" width="21.54%"><p id="p157679281384"><a name="p157679281384"></a><a name="p157679281384"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p167675286381"><a name="p167675286381"></a><a name="p167675286381"></a>写RTC时间信息，包括年、月、星期、日、时、分、秒、毫秒</p>
</td>
</tr>
<tr id="row424093120369"><td class="cellrowborder" valign="top" width="21.54%"><p id="p1240143114366"><a name="p1240143114366"></a><a name="p1240143114366"></a><strong id="b0240173133615"><a name="b0240173133615"></a><a name="b0240173133615"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p18241173133619"><a name="p18241173133619"></a><a name="p18241173133619"></a><strong id="b7241153112361"><a name="b7241153112361"></a><a name="b7241153112361"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row18241531153610"><td class="cellrowborder" valign="top" width="21.54%"><p id="p8550174182810"><a name="p8550174182810"></a><a name="p8550174182810"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p145503417284"><a name="p145503417284"></a><a name="p145503417284"></a>操作成功</p>
</td>
</tr>
<tr id="row024153123616"><td class="cellrowborder" valign="top" width="21.54%"><p id="p5602191619300"><a name="p5602191619300"></a><a name="p5602191619300"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p12602131643015"><a name="p12602131643015"></a><a name="p12602131643015"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>RTC起始时间为UTC 1970/01/01 Thursday 00:00:00，年的最大取值按照用户器件手册要求计算配置，星期不用配置。

```
int32_t ret;
struct RtcTime tm;

/* 设置RTC时间为 UTC 2020/01/01 00:59:00 .000 */
tm.year = 2020;
tm.month = 01;
tm.day = 01;
tm.hour= 00;
tm.minute = 59;
tm.second = 00;
tm.millisecond = 0;
/* 写RTC时间信息 */
ret = RtcWriteTime(handle, &tm);
if (ret != 0) {
    /* 错误处理 */
}
```

-   读取RTC报警时间

如果需要读取定时报警时间，则可以通过以下函数完成：

int32\_t RtcReadAlarm\(struct DevHandle \*handle, enum RtcAlarmIndex alarmIndex, struct RtcTime \*time\);

**表 6**  RtcReadAlarm参数和返回值描述

<a name="table11342203111420"></a>
<table><tbody><tr id="row133429310140"><td class="cellrowborder" valign="top" width="21.54%"><p id="p9886411201416"><a name="p9886411201416"></a><a name="p9886411201416"></a><strong id="b38861211101412"><a name="b38861211101412"></a><a name="b38861211101412"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p2886411171417"><a name="p2886411171417"></a><a name="p2886411171417"></a><strong id="b158861411141411"><a name="b158861411141411"></a><a name="b158861411141411"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row13835647114113"><td class="cellrowborder" valign="top" width="21.54%"><p id="p1183011486412"><a name="p1183011486412"></a><a name="p1183011486412"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p1583074815413"><a name="p1583074815413"></a><a name="p1583074815413"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row113439391410"><td class="cellrowborder" valign="top" width="21.54%"><p id="p132281120194318"><a name="p132281120194318"></a><a name="p132281120194318"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p1022852034315"><a name="p1022852034315"></a><a name="p1022852034315"></a>报警索引</p>
</td>
</tr>
<tr id="row193431836147"><td class="cellrowborder" valign="top" width="21.54%"><p id="p1926195164011"><a name="p1926195164011"></a><a name="p1926195164011"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p112695144013"><a name="p112695144013"></a><a name="p112695144013"></a>RTC报警时间信息，包括年、月、星期、日、时、分、秒、毫秒</p>
</td>
</tr>
<tr id="row43438361419"><td class="cellrowborder" valign="top" width="21.54%"><p id="p388715117143"><a name="p388715117143"></a><a name="p388715117143"></a><strong id="b9887011121415"><a name="b9887011121415"></a><a name="b9887011121415"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p088719117143"><a name="p088719117143"></a><a name="p088719117143"></a><strong id="b1788714110146"><a name="b1788714110146"></a><a name="b1788714110146"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row17169595467"><td class="cellrowborder" valign="top" width="21.54%"><p id="p107751111283"><a name="p107751111283"></a><a name="p107751111283"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p87751917289"><a name="p87751917289"></a><a name="p87751917289"></a>操作成功</p>
</td>
</tr>
<tr id="row016911915461"><td class="cellrowborder" valign="top" width="21.54%"><p id="p6833213133013"><a name="p6833213133013"></a><a name="p6833213133013"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.46%"><p id="p168341213143015"><a name="p168341213143015"></a><a name="p168341213143015"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
struct RtcTime alarmTime;

/* 读RTC_ALARM_INDEX_A索引的RTC定时报警时间信息 */
ret = RtcReadAlarm(handle, RTC_ALARM_INDEX_A, &alarmTime);
if (ret != 0) {
    /* 错误处理 */
}
```

-   设置RTC报警时间

根据报警索引设置RTC报警时间，通过以下函数完成：

int32\_t RtcWriteAlarm\(struct DevHandle \*handle, enum RtcAlarmIndex  alarmIndex, struct RtcTime \*time\);

**表 7**  RtcWriteAlarm参数和返回值描述

<a name="table107922162179"></a>
<table><tbody><tr id="row14793316131710"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1891718412183"><a name="p1891718412183"></a><a name="p1891718412183"></a><strong id="b11841849174820"><a name="b11841849174820"></a><a name="b11841849174820"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p891712461814"><a name="p891712461814"></a><a name="p891712461814"></a><strong id="b985314916480"><a name="b985314916480"></a><a name="b985314916480"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row18419611133117"><td class="cellrowborder" valign="top" width="21.62%"><p id="p075881210314"><a name="p075881210314"></a><a name="p075881210314"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p975811215317"><a name="p975811215317"></a><a name="p975811215317"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row11793151613176"><td class="cellrowborder" valign="top" width="21.62%"><p id="p562522145215"><a name="p562522145215"></a><a name="p562522145215"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p126257215217"><a name="p126257215217"></a><a name="p126257215217"></a>报警索引</p>
</td>
</tr>
<tr id="row37932016201720"><td class="cellrowborder" valign="top" width="21.62%"><p id="p26269212527"><a name="p26269212527"></a><a name="p26269212527"></a>time</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p462602125211"><a name="p462602125211"></a><a name="p462602125211"></a>RTC报警时间信息，包括年、月、星期、日、时、分、秒、毫秒</p>
</td>
</tr>
<tr id="row586915225485"><td class="cellrowborder" valign="top" width="21.62%"><p id="p591712441810"><a name="p591712441810"></a><a name="p591712441810"></a><strong id="b1992335254811"><a name="b1992335254811"></a><a name="b1992335254811"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1591720461810"><a name="p1591720461810"></a><a name="p1591720461810"></a><strong id="b792425244814"><a name="b792425244814"></a><a name="b792425244814"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row19869122210483"><td class="cellrowborder" valign="top" width="21.62%"><p id="p10798105812717"><a name="p10798105812717"></a><a name="p10798105812717"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1179817586276"><a name="p1179817586276"></a><a name="p1179817586276"></a>操作成功</p>
</td>
</tr>
<tr id="row1686918225483"><td class="cellrowborder" valign="top" width="21.62%"><p id="p16246181033012"><a name="p16246181033012"></a><a name="p16246181033012"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p3246111019309"><a name="p3246111019309"></a><a name="p3246111019309"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **说明：** 
>RTC起始时间为UTC 1970/01/01 Thursday 00:00:00，年的最大取值按照用户器件手册要求计算配置，星期不用配置。

```
int32_t ret;
struct RtcTime alarmTime;

/* 设置RTC报警时间为2020/01/01 00:59:59 .000 */
alarmTime.year = 2020;
alarmTime.month = 01;
alarmTime.day = 01;
alarmTime.hour = 00;
alarmTime.minute = 59;
alarmTime.second = 59;
alarmTime.millisecond = 0;
/* 设置RTC_ALARM_INDEX_A索引的定时报警时间 */
ret = RtcWriteAlarm(handle, RTC_ALARM_INDEX_A, &alarmTime);
if (ret != 0) {
    /* 错误处理 */
}
```

-   设置定时报警中断使能或去使能

在启动报警操作前，需要先设置报警中断使能，报警超时后会触发告警回调函数，可以通过以下函数完成：

int32\_t RtcAlarmInterruptEnable\(struct DevHandle \*handle, enum RtcAlarmIndex alarmIndex, uint8\_t enable\);

**表 8**  RtcAlarmInterruptEnable参数和返回值描述

<a name="table1934615314159"></a>
<table><tbody><tr id="row5346853171519"><td class="cellrowborder" valign="top" width="21.36%"><p id="p143464533153"><a name="p143464533153"></a><a name="p143464533153"></a><strong id="b63463534157"><a name="b63463534157"></a><a name="b63463534157"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p113461853171514"><a name="p113461853171514"></a><a name="p113461853171514"></a><strong id="b153461253191513"><a name="b153461253191513"></a><a name="b153461253191513"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row2125652144213"><td class="cellrowborder" valign="top" width="21.36%"><p id="p3150105313422"><a name="p3150105313422"></a><a name="p3150105313422"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p9151653144212"><a name="p9151653144212"></a><a name="p9151653144212"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row153794518293"><td class="cellrowborder" valign="top" width="21.36%"><p id="p4259165518294"><a name="p4259165518294"></a><a name="p4259165518294"></a>alarmIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p725985522917"><a name="p725985522917"></a><a name="p725985522917"></a>报警索引</p>
</td>
</tr>
<tr id="row19346653141518"><td class="cellrowborder" valign="top" width="21.36%"><p id="p6346253101516"><a name="p6346253101516"></a><a name="p6346253101516"></a>enable</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p234655341511"><a name="p234655341511"></a><a name="p234655341511"></a>RTC报警中断配置，1：使能，0：去使能</p>
</td>
</tr>
<tr id="row18346953111513"><td class="cellrowborder" valign="top" width="21.36%"><p id="p53460537156"><a name="p53460537156"></a><a name="p53460537156"></a><strong id="b23461553171512"><a name="b23461553171512"></a><a name="b23461553171512"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p4346153171510"><a name="p4346153171510"></a><a name="p4346153171510"></a><strong id="b1834675316154"><a name="b1834675316154"></a><a name="b1834675316154"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row1234685314151"><td class="cellrowborder" valign="top" width="21.36%"><p id="p8947195310279"><a name="p8947195310279"></a><a name="p8947195310279"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p99471953152712"><a name="p99471953152712"></a><a name="p99471953152712"></a>操作成功</p>
</td>
</tr>
<tr id="row2347115321514"><td class="cellrowborder" valign="top" width="21.36%"><p id="p324855163018"><a name="p324855163018"></a><a name="p324855163018"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p7248857302"><a name="p7248857302"></a><a name="p7248857302"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;

/* 设置RTC报警中断使能 */
ret = RtcAlarmInterruptEnable(handle, RTC_ALARM_INDEX_A, 1);
if (ret != 0) {
    /* 错误处理 */
}
```

-   读取RTC外频

读取RTC外接晶体振荡频率，可以通过以下函数完成：

int32\_t RtcGetFreq\(struct DevHandle \*handle, uint32\_t \*freq\);

**表 9**  RtcGetFreq参数和返回值描述

<a name="table125881625185"></a>
<table><tbody><tr id="row1458811241816"><td class="cellrowborder" valign="top" width="21.36%"><p id="p658820241813"><a name="p658820241813"></a><a name="p658820241813"></a><strong id="b1358817216185"><a name="b1358817216185"></a><a name="b1358817216185"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p758812261820"><a name="p758812261820"></a><a name="p758812261820"></a><strong id="b2588922188"><a name="b2588922188"></a><a name="b2588922188"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row831259124219"><td class="cellrowborder" valign="top" width="21.36%"><p id="p171541407431"><a name="p171541407431"></a><a name="p171541407431"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p715413094314"><a name="p715413094314"></a><a name="p715413094314"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row1358842171820"><td class="cellrowborder" valign="top" width="21.36%"><p id="p258814210188"><a name="p258814210188"></a><a name="p258814210188"></a>freq</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p165888211810"><a name="p165888211810"></a><a name="p165888211810"></a>RTC的外接晶体振荡频率，单位（HZ）</p>
</td>
</tr>
<tr id="row2058818281817"><td class="cellrowborder" valign="top" width="21.36%"><p id="p458872151810"><a name="p458872151810"></a><a name="p458872151810"></a><strong id="b658814210189"><a name="b658814210189"></a><a name="b658814210189"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p155880251819"><a name="p155880251819"></a><a name="p155880251819"></a><strong id="b558816211182"><a name="b558816211182"></a><a name="b558816211182"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row35883213183"><td class="cellrowborder" valign="top" width="21.36%"><p id="p8133145211272"><a name="p8133145211272"></a><a name="p8133145211272"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p13133352202719"><a name="p13133352202719"></a><a name="p13133352202719"></a>操作成功</p>
</td>
</tr>
<tr id="row135892261811"><td class="cellrowborder" valign="top" width="21.36%"><p id="p152692538292"><a name="p152692538292"></a><a name="p152692538292"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p327015313294"><a name="p327015313294"></a><a name="p327015313294"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint32_t freq = 0;

/* 读取RTC外接晶体振荡频率 */
ret = RtcGetFreq(handle, &freq);
if (ret != 0) {
    /* 错误处理 */
}
```

-   配置RTC外频

配置RTC外接晶体振荡频率，可以通过以下函数完成：

int32\_t RtcSetFreq\(struct DevHandle \*handle, uint32\_t freq\);

**表 10**  RtcSetFreq参数和返回值描述

<a name="table1170124316209"></a>
<table><tbody><tr id="row270119432202"><td class="cellrowborder" valign="top" width="21.36%"><p id="p127011343132010"><a name="p127011343132010"></a><a name="p127011343132010"></a><strong id="b970114382014"><a name="b970114382014"></a><a name="b970114382014"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p7701184372013"><a name="p7701184372013"></a><a name="p7701184372013"></a><strong id="b11701743182010"><a name="b11701743182010"></a><a name="b11701743182010"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row36067554319"><td class="cellrowborder" valign="top" width="21.36%"><p id="p881511716433"><a name="p881511716433"></a><a name="p881511716433"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p188157714432"><a name="p188157714432"></a><a name="p188157714432"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row127019437204"><td class="cellrowborder" valign="top" width="21.36%"><p id="p27019438207"><a name="p27019438207"></a><a name="p27019438207"></a>freq</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p167021043182011"><a name="p167021043182011"></a><a name="p167021043182011"></a>RTC的外接晶体振荡频率，单位（HZ）</p>
</td>
</tr>
<tr id="row97022434205"><td class="cellrowborder" valign="top" width="21.36%"><p id="p1770218431208"><a name="p1770218431208"></a><a name="p1770218431208"></a><strong id="b107021743132010"><a name="b107021743132010"></a><a name="b107021743132010"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p1170217432201"><a name="p1170217432201"></a><a name="p1170217432201"></a><strong id="b3702243202015"><a name="b3702243202015"></a><a name="b3702243202015"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row1670212432206"><td class="cellrowborder" valign="top" width="21.36%"><p id="p77021543152017"><a name="p77021543152017"></a><a name="p77021543152017"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p770214310209"><a name="p770214310209"></a><a name="p770214310209"></a>操作成功</p>
</td>
</tr>
<tr id="row10702194313201"><td class="cellrowborder" valign="top" width="21.36%"><p id="p165182216306"><a name="p165182216306"></a><a name="p165182216306"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p651815219302"><a name="p651815219302"></a><a name="p651815219302"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint32_t freq = 32768; /* 32768 Hz */

/* 设置RTC外接晶体振荡频率，注意按照器件手册要求配置RTC外频 */
ret = RtcSetFreq(handle, freq);
if (ret != 0) {
    /* 错误处理 */
}
```

-   复位RTC

复位RTC，复位RTC后各配置寄存器恢复默认值，可以通过以下函数完成：

int32\_t RtcReset\(struct DevHandle \*handle\);

**表 11**  RtcReset参数和返回值描述

<a name="table398973152517"></a>
<table><tbody><tr id="row179899311254"><td class="cellrowborder" valign="top" width="21.36%"><p id="p199899314257"><a name="p199899314257"></a><a name="p199899314257"></a><strong id="b3989163192516"><a name="b3989163192516"></a><a name="b3989163192516"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p179897315257"><a name="p179897315257"></a><a name="p179897315257"></a><strong id="b16989193110252"><a name="b16989193110252"></a><a name="b16989193110252"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row14989113118257"><td class="cellrowborder" valign="top" width="21.36%"><p id="p129018136436"><a name="p129018136436"></a><a name="p129018136436"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p290111304310"><a name="p290111304310"></a><a name="p290111304310"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row7989123111254"><td class="cellrowborder" valign="top" width="21.36%"><p id="p129894313251"><a name="p129894313251"></a><a name="p129894313251"></a><strong id="b7989931162516"><a name="b7989931162516"></a><a name="b7989931162516"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p799013112256"><a name="p799013112256"></a><a name="p799013112256"></a><strong id="b499053112519"><a name="b499053112519"></a><a name="b499053112519"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row9990193142513"><td class="cellrowborder" valign="top" width="21.36%"><p id="p1999043111257"><a name="p1999043111257"></a><a name="p1999043111257"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p1799093182516"><a name="p1799093182516"></a><a name="p1799093182516"></a>操作成功</p>
</td>
</tr>
<tr id="row16990133152516"><td class="cellrowborder" valign="top" width="21.36%"><p id="p17536173573015"><a name="p17536173573015"></a><a name="p17536173573015"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.64%"><p id="p1153623503014"><a name="p1153623503014"></a><a name="p1153623503014"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;

/* 复位RTC，复位RTC后各配置寄存器恢复默认值 */
ret = RtcReset(handle);
if (ret != 0) {
    /* 错误处理 */
}
```

-   读取RTC自定义寄存器配置

按照用户定义的寄存器索引，读取对应的寄存器配置，一个索引对应一字节的配置值，通过以下函数完成：

int32\_t RtcReadReg\(struct DevHandle \*handle, uint8\_t usrDefIndex, uint8\_t \*value\);

**表 12**  RtcReadReg参数和返回值描述

<a name="table1624674153319"></a>
<table><tbody><tr id="row92469423320"><td class="cellrowborder" valign="top" width="21.62%"><p id="p102461548331"><a name="p102461548331"></a><a name="p102461548331"></a><strong id="b224610493313"><a name="b224610493313"></a><a name="b224610493313"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p15246847331"><a name="p15246847331"></a><a name="p15246847331"></a><strong id="b724612453315"><a name="b724612453315"></a><a name="b724612453315"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row171318200434"><td class="cellrowborder" valign="top" width="21.62%"><p id="p9895321184320"><a name="p9895321184320"></a><a name="p9895321184320"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p68951214436"><a name="p68951214436"></a><a name="p68951214436"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row324614143314"><td class="cellrowborder" valign="top" width="21.62%"><p id="p82466433320"><a name="p82466433320"></a><a name="p82466433320"></a>usrDefIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p181671825470"><a name="p181671825470"></a><a name="p181671825470"></a>用户定义的寄存器对应索引</p>
</td>
</tr>
<tr id="row524716420334"><td class="cellrowborder" valign="top" width="21.62%"><p id="p8247844333"><a name="p8247844333"></a><a name="p8247844333"></a>value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p524711413319"><a name="p524711413319"></a><a name="p524711413319"></a>寄存器值</p>
</td>
</tr>
<tr id="row112471143334"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1124716483312"><a name="p1124716483312"></a><a name="p1124716483312"></a><strong id="b192476416337"><a name="b192476416337"></a><a name="b192476416337"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1524716443313"><a name="p1524716443313"></a><a name="p1524716443313"></a><strong id="b72472473313"><a name="b72472473313"></a><a name="b72472473313"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row9247194183314"><td class="cellrowborder" valign="top" width="21.62%"><p id="p62476410334"><a name="p62476410334"></a><a name="p62476410334"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p152471433317"><a name="p152471433317"></a><a name="p152471433317"></a>操作成功</p>
</td>
</tr>
<tr id="row1424719410333"><td class="cellrowborder" valign="top" width="21.62%"><p id="p112477417335"><a name="p112477417335"></a><a name="p112477417335"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p7247547338"><a name="p7247547338"></a><a name="p7247547338"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t usrDefIndex = 0; /* 定义0索引对应用户定义的第一个寄存器*/
uint8_t value = 0;

/* 按照用户定义的寄存器索引，读取对应的寄存器配置，一个索引对应一字节的配置值 */
ret = RtcReadReg(handle, usrDefIndex, &value);
if (ret != 0) {
    /* 错误处理 */
}
```

-   设置RTC自定义寄存器配置

按照用户定义的寄存器索引，设置对应的寄存器配置，一个索引对应一字节的配置值，通过以下函数完成：

int32\_t RtcWriteReg\(struct DevHandle \*handle, uint8\_t usrDefIndex, uint8\_t value\);

**表 13**  RtcWriteReg参数和返回值描述

<a name="table1072216482360"></a>
<table><tbody><tr id="row187221648133611"><td class="cellrowborder" valign="top" width="21.62%"><p id="p2722184823617"><a name="p2722184823617"></a><a name="p2722184823617"></a><strong id="b18723134883614"><a name="b18723134883614"></a><a name="b18723134883614"></a>参数</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1372374810367"><a name="p1372374810367"></a><a name="p1372374810367"></a><strong id="b147230481369"><a name="b147230481369"></a><a name="b147230481369"></a>参数描述</strong></p>
</td>
</tr>
<tr id="row1675092612435"><td class="cellrowborder" valign="top" width="21.62%"><p id="p7783927144312"><a name="p7783927144312"></a><a name="p7783927144312"></a>handle</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p197831427134310"><a name="p197831427134310"></a><a name="p197831427134310"></a>RTC设备句柄</p>
</td>
</tr>
<tr id="row1723174815367"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1972364814366"><a name="p1972364814366"></a><a name="p1972364814366"></a>usrDefIndex</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p18723184819365"><a name="p18723184819365"></a><a name="p18723184819365"></a>用户定义的寄存器对应索引</p>
</td>
</tr>
<tr id="row2723548163611"><td class="cellrowborder" valign="top" width="21.62%"><p id="p1772364893610"><a name="p1772364893610"></a><a name="p1772364893610"></a>value</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1772324803619"><a name="p1772324803619"></a><a name="p1772324803619"></a>寄存器值</p>
</td>
</tr>
<tr id="row1072314482361"><td class="cellrowborder" valign="top" width="21.62%"><p id="p6723194853618"><a name="p6723194853618"></a><a name="p6723194853618"></a><strong id="b14723194863611"><a name="b14723194863611"></a><a name="b14723194863611"></a>返回值</strong></p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p1872314893614"><a name="p1872314893614"></a><a name="p1872314893614"></a><strong id="b8723154812365"><a name="b8723154812365"></a><a name="b8723154812365"></a>返回值描述</strong></p>
</td>
</tr>
<tr id="row20723148173617"><td class="cellrowborder" valign="top" width="21.62%"><p id="p12723348133615"><a name="p12723348133615"></a><a name="p12723348133615"></a>0</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p472324873620"><a name="p472324873620"></a><a name="p472324873620"></a>操作成功</p>
</td>
</tr>
<tr id="row127231848123615"><td class="cellrowborder" valign="top" width="21.62%"><p id="p197231148173613"><a name="p197231148173613"></a><a name="p197231148173613"></a>负数</p>
</td>
<td class="cellrowborder" valign="top" width="78.38000000000001%"><p id="p16723134823618"><a name="p16723134823618"></a><a name="p16723134823618"></a>操作失败</p>
</td>
</tr>
</tbody>
</table>

```
int32_t ret;
uint8_t usrDefIndex = 0; /* 定义0索引对应用户定义第一个寄存器*/
uint8_t value = 0x10;

/* 按照用户的定义的寄存器索引，设置对应的寄存器配置，一个索引对应一字节的配置值 */
ret = RtcWriteReg(handle, usrDefIndex, value);
if (ret != 0) {
    /* 错误处理 */
}
```

