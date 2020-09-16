# GPIO Usage Example<a name="EN-US_TOPIC_0000001052777597"></a>

In this example, we test the interrupt trigger of a GPIO pin as follows: Set the ISR function for the pin, set the trigger mode to rising edge and failing edge, write high and low levels to the pin alternately to generate level fluctuation, and observe the execution of the ISR function.

Select an idle GPIO pin. This example uses a Hi3516D V300 development board and GPIO pin GPIO10\_3, which is numbered GPIO83.

You can select an idle GPIO pin based on the development board and schematic diagram.

```
#include "gpio_if.h"
#include "hdf_log.h"
#include "osal_irq.h"
#include "osal_time.h"

static uint32_t g_irqCnt;

/* ISR function */
static int32_t TestCaseGpioIrqHandler(uint16_t gpio, void *data)
{
    HDF_LOGE("%s: irq triggered! on gpio:%u, data=%p", __func__, gpio, data);
    g_irqCnt++; /* If the ISR function is triggered, the number of global interrupts is incremented by 1. */
    return GpioDisableIrq(gpio);
}

/* Test case function */
static int32_t TestCaseGpioIrqEdge(void)
{
    int32_t ret;
    uint16_t valRead;
    uint16_t mode;
    uint16_t gpio = 83; /* Number of the GPIO pin to test */
    uint32_t timeout;

    /* Set the output direction for the pin. */
    ret = GpioSetDir(gpio, GPIO_DIR_OUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set dir fail! ret:%d\n", __func__, ret);
        return ret;
    }

    /* Disable the interrupt of the pin. */
    ret = GpioDisableIrq(gpio);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: disable irq fail! ret:%d\n", __func__, ret);
        return ret;
    }

    /* Set the ISR function for the pin. The trigger mode is both rising edge and falling edge. */
    mode = OSAL_IRQF_TRIGGER_RISING | OSAL_IRQF_TRIGGER_FALLING;
    HDF_LOGE("%s: mode:%0x\n", __func__, mode);
    ret = GpioSetIrq(gpio, mode, TestCaseGpioIrqHandler, NULL);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set irq fail! ret:%d\n", __func__, ret);
        return ret;
    }

    /* Enable the interrupt for this pin. */
    ret = GpioEnableIrq(gpio);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: enable irq fail! ret:%d\n", __func__, ret);
        (void)GpioUnSetIrq(gpio);
        return ret;
    }

    g_irqCnt = 0; /* Reset the global counter. */
    timeout = 0;  /* Reset the waiting time. */
    /* Wait for the ISR function of this pin to trigger. The timeout duration is 1000 ms. */
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

