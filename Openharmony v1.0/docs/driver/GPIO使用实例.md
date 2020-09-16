# GPIO使用实例<a name="ZH-CN_TOPIC_0000001052777597"></a>

本实例程序中，我们将测试一个GPIO管脚的中断触发：为管脚设置中断服务函数，触发方式为边沿触发，然后通过交替写高低电平到管脚，产生电平波动，制造触发条件，观察中断服务函数的执行。

首先需要选取一个空闲的GPIO管脚，本例程基于Hi3516DV300某开发板，GPIO管脚选择GPIO10\_3，换算成GPIO号为83。

读者可以根据自己使用的开发板，参考其原理图，选择一个空闲的GPIO管脚即可。

```
#include "gpio_if.h"
#include "hdf_log.h"
#include "osal_irq.h"
#include "osal_time.h"

static uint32_t g_irqCnt;

/* 中断服务函数*/
static int32_t TestCaseGpioIrqHandler(uint16_t gpio, void *data)
{
    HDF_LOGE("%s: irq triggered! on gpio:%u, data=%p", __func__, gpio, data);
    g_irqCnt++; /* 如果中断服务函数触发执行，则将全局中断计数加1 */
    return GpioDisableIrq(gpio);
}

/* 测试用例函数 */
static int32_t TestCaseGpioIrqEdge(void)
{
    int32_t ret;
    uint16_t valRead;
    uint16_t mode;
    uint16_t gpio = 83; /* 待测试的GPIO管脚号 */
    uint32_t timeout;

    /* 将管脚方向设置为输出 */
    ret = GpioSetDir(gpio, GPIO_DIR_OUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set dir fail! ret:%d\n", __func__, ret);
        return ret;
    }

    /* 先禁止该管脚中断 */
    ret = GpioDisableIrq(gpio);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: disable irq fail! ret:%d\n", __func__, ret);
        return ret;
    }

    /* 为管脚设置中断服务函数，触发模式为上升沿和下降沿共同触发 */
    mode = OSAL_IRQF_TRIGGER_RISING | OSAL_IRQF_TRIGGER_FALLING;
    HDF_LOGE("%s: mode:%0x\n", __func__, mode);
    ret = GpioSetIrq(gpio, mode, TestCaseGpioIrqHandler, NULL);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set irq fail! ret:%d\n", __func__, ret);
        return ret;
    }

    /* 使能此管脚中断 */
    ret = GpioEnableIrq(gpio);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: enable irq fail! ret:%d\n", __func__, ret);
        (void)GpioUnSetIrq(gpio);
        return ret;
    }

    g_irqCnt = 0; /* 清除全局计数器 */
    timeout = 0;  /* 等待时间清零 */
    /* 等待此管脚中断服务函数触发，等待超时时间为1000毫秒 */
    while (g_irqCnt <= 0 && timeout < 1000) {
        (void)GpioRead(gpio, &valRead);
        (void)GpioWrite(gpio, (valRead == GPIO_VAL_LOW) ? GPIO_VAL_HIGH : GPIO_VAL_LOW);
        HDF_LOGE("%s: wait irq timeout:%u\n", __func__, timeout);
        OsalMDelay(200); /* wait for irq trigger */
        timeout += 200;
    }
    (void)GpioUnSetIrq(gpio);
    return (g_irqCnt > 0) ? HDF_SUCCESS : HDF_FAILURE;
}
```

