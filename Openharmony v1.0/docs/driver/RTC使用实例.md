# RTC使用实例<a name="ZH-CN_TOPIC_0000001052778235"></a>

本实例提供RTC接口的完整使用流程：

1.  系统启动，驱动管理模块会识别系统当前的RTC器件;
2.  驱动管理模块完成RTC设备的初始化和设备创建；
3.  用户通过不同API，对该RTC设备进行对应的操作；
4.  关闭RTC设备，释放设备资源。

示例如下：

```
#include "rtc_if.h"
int32_t RtcAlarmACallback(enum RtcAlarmIndex alarmIndex)
{
    if (alarmIndex == RTC_ALARM_INDEX_A) {
        /* 报警A的处理 */
        printf("RTC Alarm A callback function\n\r");
    } else if (alarmIndex == RTC_ALARM_INDEX_B) {
        /* 报警B的处理 */
        printf("RTC Alarm B callback function\n\r");
    } else {
        /* 错误处理 */
    }
    return 0;
}

void RtcTestSample(void)
{
    int32_t ret;
    struct RtcTime tm;
    struct RtcTime alarmTime;
    uint32_t freq;
    struct DevHandle *handle = NULL;

    /* 获取RTC设备句柄 */
    handle = RtcOpen();
    if (handle == NULL) {
        /* 错误处理 */
    }
    /* 注册报警A的定时回调函数 */
    ret = RtcRegisterAlarmCallback(handle, RTC_ALARM_INDEX_A, RtcAlarmACallback);
    if (ret != 0) {
        /* 错误处理 */
    }
    /* 设置RTC外接晶体振荡频率，注意按照器件手册要求配置RTC外频 */
    freq = 32768; /* 32768 Hz */
    ret = RtcSetFreq(handle, freq);
    if (ret != 0) {
        /* 错误处理 */
    }
    /* 设置RTC报警中断使能 */
    ret = RtcAlarmInterruptEnable(handle, RTC_ALARM_INDEX_A, 1);
    if (ret != 0) {
        /* 错误处理 */
    }
    /* 设置RTC时间为2020/01/01 00:00:10 .990 */
    tm.year = 2020;
    tm.month = 01;
    tm.day = 01;
    tm.hour= 0;
    tm.minute = 0;
    tm.second = 10;
    tm.millisecond = 990;
    /* 写RTC时间信息 */
    ret = RtcWriteTime(handle, &tm);
    if (ret != 0) {
        /* 错误处理 */
    }
    /* 设置RTC报警时间为2020/01/01 00:00:30 .100 */
    alarmTime.year = 2020;
    alarmTime.month = 01;
    alarmTime.day = 01;
    alarmTime.hour = 0;
    alarmTime.minute = 0;
    alarmTime.second = 30;
    alarmTime.millisecond = 100;
    /* 设置RTC_ALARM_INDEX_A索引定时报警时间信息, 定时时间到后会打印"RTC Alarm A callback function" */
    ret = RtcWriteAlarm(handle, RTC_ALARM_INDEX_A, &alarmTime);
    if (ret != 0) {
        /* 错误处理 */
    }

    /* 读取RTC实时时间 */
    ret = RtcReadTime(handle, &tm);
    if (ret != 0) {
        /* 错误处理 */
    }
    sleep(5)
    printf("RTC read time:\n\r");
    printf("year-month-date-weekday hour:minute:second .millisecond %04u-%02u-%02u-%u %02u:%02u:%02u .%03u",
        tm.year, tm.month, tm.day, tm.weekday, tm.hour, tm.minute, tm.second, tm.millisecond);
    /* 销毁RTC设备句柄 */
    RtcClose(handle);
}
```

