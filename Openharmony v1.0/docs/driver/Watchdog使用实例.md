# Watchdog使用实例<a name="ZH-CN_TOPIC_0000001052657651"></a>

本例程提供Watchdog的完整使用流程。

在本例程中，我们打开一个看门狗设备，设置超时时间并启动计时：

1）首先定期喂狗，即按时清除看门狗定时器，确保系统不会因定时器超时而复位；

2）接着再停止喂狗，观察定时器到期后系统是否发生复位行为

示例如下：

```
#include "watchdog_if.h"
#include "hdf_log.h"
#include "osal_irq.h"
#include "osal_time.h"

#define WATCHDOG_TEST_TIMEOUT     2
#define WATCHDOG_TEST_FEED_TIME   6

static int32_t TestCaseWatchdog(void)
{
    int32_t i;
    int32_t ret;
    uint32_t timeout;
    struct DevHandle *handle = NULL;

    /* 打开0号Watchdog设备 */
    handle = WatchdogOpen(0);
    if (handle == NULL) {
        HDF_LOGE("Open Watchdog fail!");
        return -1;
    }

    /* 设置超时时间 */
    ret = WatchdogSetTimeout(handle, WATCHDOG_TEST_TIMEOUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set timeout fail! ret:%d\n", __func__, ret);
        WatchdogClose(handle);
        return ret;
    }

    /* 回读设置的timeout值 */
    ret = WatchdogGetTimeout(handle, &timeout);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: get timeout fail! ret:%d\n", __func__, ret);
        WatchdogClose(handle);
        return ret;
    }
    HDF_LOGI("%s: read timeout back:%u\n", __func__, timeout);

    /* 启动看门狗，开始计时 */
    ret = WatchdogStart(handle);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: satrt fail! ret:%d\n", __func__, ret);
        WatchdogClose(handle);
        return ret;
    }

    /* 每隔1S喂狗一次 */
    for (i = 0; i < WATCHDOG_TEST_FEED_TIME; i++) {
        HDF_LOGE("%s: feeding watchdog %d times... \n", __func__, i);
        ret = WatchdogFeed(handle);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("%s: feed dog fail! ret:%d\n", __func__, ret);
            WatchdogClose(handle);
            return ret;
        }
        OsalSleep(1);
    }
    /* 由于喂狗间隔小于超时时间，系统不会发生复位，此日志可以正常打印 */
    HDF_LOGE("%s: no reset ... feeding test OK!!!\n", __func__);

    /* 接下来持续不喂狗，使得看门狗计时器超时 */
    for (i = 0; i < WATCHDOG_TEST_FEED_TIME; i++) {
        HDF_LOGE("%s: watiting dog buck %d times... \n", __func__, i);
        OsalSleep(1);
    }

    /* 当不喂狗时间到达之前设定的超时时间的时候，系统会发生复位，理论上观察不到此日志的打印 */
    HDF_LOGE("%s: dog has't buck!!! \n", __func__, i);
    WatchdogClose(handle);
    return -1;
}
```

