# RTC Usage Example<a name="EN-US_TOPIC_0000001052778235"></a>

This section describes the process of using RTC APIs:

1.  During the OS startup, the HDF identifies the RTC component in the system.
2.  The HDF initializes and creates the RTC device.
3.  You can perform operations on the RTC device by calling different APIs.
4.  Call the  **RtcClose**  function to release the device handle and device resources.

Example:

```
#include "rtc_if.h"
int32_t RtcAlarmACallback(enum RtcAlarmIndex alarmIndex)
{
    if (alarmIndex == RTC_ALARM_INDEX_A) {
        /* Process alarm A. */
        printf("RTC Alarm A callback function\n\r");
    } else if (alarmIndex == RTC_ALARM_INDEX_B) {
        /* Process alarm B. */
        printf("RTC Alarm B callback function\n\r");
    } else {
    /* Process the error. */
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

    /* Obtain the RTC device handle. */
    handle = RtcOpen();
    if (handle == NULL) {
        /* Process the error. */
    }
    /* Register RtcAlarmCallback for alarm A. */
    ret = RtcRegisterAlarmCallback(handle, RTC_ALARM_INDEX_A, RtcAlarmACallback);
    if (ret != 0) {
        /* Process the error. */
    }
    /* Set the RTC external crystal frequency. Note that the frequency must be configured in accordance with the requirements specified in the product manual of the in-use component. */
    freq = 32768; /* 32768 Hz */
    ret = RtcSetFreq(handle, freq);
    if (ret != 0) {
        /* Process the error. */
    }
    /* Enable the RTC alarm interrupts. */
    ret = RtcAlarmInterruptEnable(handle, RTC_ALARM_INDEX_A, 1);
    if (ret != 0) {
        /* Process the error. */
    }
    /* Set the RTC time to 2020/01/01 00:00:10 .990. */
    tm.year = 2020;
    tm.month = 01;
    tm.day = 01;
    tm.hour= 0;
    tm.minute = 0;
    tm.second = 10;
    tm.millisecond = 990;
    /* Write the RTC time information. */
    ret = RtcWriteTime(handle, &tm);
    if (ret != 0) {
        /* Process the error. */
    }
    /* Set the RTC alarm time to 2020/01/01 00:00:30 .100. */
    alarmTime.year = 2020;
    alarmTime.month = 01;
    alarmTime.day = 01;
    alarmTime.hour = 0;
    alarmTime.minute = 0;
    alarmTime.second = 30;
    alarmTime.millisecond = 100;
    /* Set the alarm time information for RTC_ALARM_INDEX_A. When the specified time is reached, "RTC Alarm A callback function" is printed. */
    ret = RtcWriteAlarm(handle, RTC_ALARM_INDEX_A, &alarmTime);
    if (ret != 0) {
        /* Process the error. */
    }

    /* Read the RTC real time. */
    ret = RtcReadTime(handle, &tm);
    if (ret != 0) {
        /* Process the error. */
    }
    sleep(5)
    printf("RTC read time:\n\r");
    printf("year-month-date-weekday hour:minute:second .millisecond %04u-%02u-%02u-%u %02u:%02u:%02u .%03u",
        tm.year, tm.month, tm.day, tm.weekday, tm.hour, tm.minute, tm.second, tm.millisecond);
    /* Release the RTC device handle. */
    RtcClose(handle);
}
```

