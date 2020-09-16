# Watchdog Usage Example<a name="EN-US_TOPIC_0000001052657651"></a>

This example provides a complete process for using a watchdog.

In this example, open a watchdog, set the timeout duration, and start the watchdog.

1. Feed the watchdog periodically to ensure that the system is not reset due to timer expiry.

2. Stop feeding the watchdog and check whether the system is reset after the timer expires.

Example:

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

    /* Open watchdog 0. */
    handle = WatchdogOpen(0);
    if (handle == NULL) {
        HDF_LOGE("Open Watchdog fail!");
        return -1;
    }

    /* Set the timeout duration. */
    ret = WatchdogSetTimeout(handle, WATCHDOG_TEST_TIMEOUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set timeout fail! ret:%d\n", __func__, ret);
        WatchdogClose(handle);
        return ret;
    }

    /* Obtain the configured timeout duration. */
    ret = WatchdogGetTimeout(handle, &timeout);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: get timeout fail! ret:%d\n", __func__, ret);
        WatchdogClose(handle);
        return ret;
    }
    HDF_LOGI("%s: read timeout back:%u\n", __func__, timeout);

    /* Start the watchdog. The timer starts. */
    ret = WatchdogStart(handle);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: satrt fail! ret:%d\n", __func__, ret);
        WatchdogClose(handle);
        return ret;
    }

    /* Feed the watchdog every 1s. */
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
    /* Because the interval for feeding the watchdog is shorter than the timeout duration, the system does not reset, and logs can be printed normally. */
    HDF_LOGE("%s: no reset ... feeding test OK!!!\n", __func__);

    /* Enable the timer to expire by stopping feeding the watchdog. */
    for (i = 0; i < WATCHDOG_TEST_FEED_TIME; i++) {
        HDF_LOGE("%s: watiting dog buck %d times... \n", __func__, i);
        OsalSleep(1);
    }

    /* The system resets when the timer expires. If the code is correct, the log below is not displayed. */
    HDF_LOGE("%s: dog has't buck!!! \n", __func__, i);
    WatchdogClose(handle);
    return -1;
}
```

