# Touchscreen Development Example<a name="EN-US_TOPIC_0000001052576212"></a>

This example describes how to develop the Touchscreen driver.

## Loading the Driver<a name="section85281142102317"></a>

Load and start the Touchscreen driver based on the HDF driver model. For details, see  [Driver Development](driver-development.md). The example code is as follows:

```
/* Implement TouchDispatch as required. */
int32_t TouchDispatch(struct HdfDeviceObject *device, int cmd, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    (void)device;
    (void)cmd;
    if (data == NULL || reply == NULL) {
        HDF_LOGE("%s: param is null", __func__);
        return HDF_FAILURE;
    }
    return HDF_SUCCESS;
}

/* Implement TouchEntryOpen based on actual service requirements. */
int32_t Gt911TouchDriverOpen(struct HdfDeviceObject *object)
{
    if (object == NULL) {
        HDF_LOGE("%s: param is null", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    static struct IRemoteService service = {
        .object = {0},
        .Dispatch = TouchDispatch,
    };
    object->service = &service;
    return HDF_SUCCESS;
}

/* Implement the Init function for the Touchscreen driver. */
int Gt911TouchDriverInit(struct HdfDeviceObject *object)
{
    /* For details about the function implementation, see the sample code below of "Executing the Initialization". */
    return HDF_SUCCESS;
}
/* Define the entry to the HDF. */
struct HdfDriverEntry g_gt5p5TouchDevEntry = {
    .moduleVersion = 1,
    .moduleName = "HDF_TOUCHSCREEN",
    .Bind = Gt911TouchDriverOpen,
    .Init = Gt911TouchDriverInit,
};

HDF_INIT(g_gt5p5TouchDevEntry);
```

## Initializing the Driver<a name="section189081946192410"></a>

The following describes the common initialization steps. You can change them based on the service requirements.

```
int TouchEntryInit(struct HdfDeviceObject *object)
{
    (void)object;
    /* Create a global data structure for storing information about the touchscreen driver. */
    g_coreData = (TouchCoreData *)OsalMemAlloc(sizeof(TouchCoreData));
    if (g_coreData == NULL) {
        HDF_LOGE("%s: malloc failed", __func__);
        return HDF_ERR_MALLOC_FAIL;
    }

    if (memset_s(g_coreData, sizeof(TouchCoreData), 0, sizeof(TouchCoreData)) != EOK) {
        HDF_LOGE("%s: memset_s fail", __func__);
        return;
    }
    /* Initialize the global data structure, and parse and assign values to the touchscreen driver configuration items. */
    TouchConfigInit(g_coreData);
    /* Set the GPIO attributes and status. */
    if (TouchSetupGpio(g_coreData)) {
        goto ERR_EXIT;
    }
    /* Set and obtain the I2C bus handle. */
    if (TouchSetupI2c(g_coreData)) {
        goto ERR_EXIT;
    }
    /* Create a task to detect and process interrupts. */
    if (TouchIrqTaskInit(g_coreData)) {
        goto ERR_EXIT;
    }
    /* Initialize the power supply. */
    if (TouchPowerInit(g_coreData)) {
        goto ERR_EXIT;
    }
    /* Create an input device file. */
    (void)mkdir("/dev/input", DEFAULT_DIR_MODE);
    if (register_driver(TOUCH_DEVICE, &g_touchDevOps, TOUCH_DEVICE_MODE, NULL)) {
        HDF_LOGE("%s: register touch dev failed", __func__);
        goto ERR_EXIT;
    }
    HDF_LOGE("%s: exit succ", __func__);
    return HDF_SUCCESS;

ERR_EXIT:
    if (g_coreData->i2cClient.i2cHandle != NULL) {
        DeviceHandleDestroy(g_coreData->i2cClient.i2cHandle);
        g_coreData->i2cClient.i2cHandle = NULL;
    }
    OsalMemFree(g_coreData);
    g_coreData = NULL;
    return HDF_FAILURE;
}
```

## Configuring Basic Parameters<a name="section19856687253"></a>

Configure the address of the I2C device, bus number, touch reporting range on the touchscreen, input device type, and GPIO pin. The configuration depends on the board and touchscreen in use. The following provides a configuration example:

```
static void TouchConfigInit(TouchCoreData *cd)
{
    /* init waitqueue for poll */
    __init_waitqueue_head(&cd->pollWait);

    /* Configure the address of the I2C device, bus number, and touch reporting range. */
    cd->i2cClient.i2cCfg.addr = DRIVER_CHIP_I2C_ADDR;
    cd->i2cClient.i2cCfg.busNum = I2C_BUS_NUM;
    cd->inputCfg.solutionX = TOUCH_SOLUTION_X;
    cd->inputCfg.solutionY = TOUCH_SOLUTION_Y;

    /* Configure the input device type. In this example, the Touch driver is used. */
    cd->inputDevType = INDEV_TYPE_TOUCH;

    /* Configure the GPIO numbers of the reset and interrupt pins, and IRQ trigger mode. */
    cd->rstGpioNum = RST_GPIO_OFFSET;
    cd->intGpioNum = INT_GPIO_OFFSET;
    cd->irqFlag = OSAL_IRQF_TRIGGER_FALLING;
}
```

## Configuring and Using I/O Pins<a name="section636814296252"></a>

The following describes the initialization configuration of the reset and IRQ pins. The PAL interface is used for GPIO-related operations. For details, see  [GPIO Usage Guidelines](gpiousage-guidelines.md).

```
static int TouchSetupGpio(TouchCoreData *cd)
{
    /* Configure the I/O direction of the interrupt pin to the input and pull-up direction. */
    writel(INT_REG_CFG, IO_DEVICE_ADDR(INR_REG_ADDR));
    /* Set the I/O direction of the interrupt pin to the input direction. */
    int ret = GpioSetDir(cd->intGpioNum, GPIO_DIR_IN);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("set int to input dir failed, ret %d", ret);
        return HDF_FAILURE;
    }
    /* Set the I/O direction of the reset pin to the output direction. */
    ret = GpioSetDir(cd->rstGpioNum, GPIO_DIR_OUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("set reset to output dir failed, ret %d", ret);
        return HDF_FAILURE;
    }
    /* Pull up the reset pin. */
    ret = GpioWrite(cd->rstGpioNum, GPIO_VAL_HIGH);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("pull up reset gpio failed, ret %d", ret);
        return HDF_FAILURE;
    }
    OsalMSleep(RESET_HIGH_DELAY);
    /* Pull down the reset pin. */
    ret = GpioWrite(cd->rstGpioNum, GPIO_VAL_LOW);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("pull down reset gpio failed, ret %d", ret);
        return HDF_FAILURE;
    }
    OsalMSleep(RESET_LOW_DELAY);
    /* Pull up the reset pin again. */
    ret = GpioWrite(cd->rstGpioNum, GPIO_VAL_HIGH);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("pull up reset gpio again failed, ret %d", ret);
        return HDF_FAILURE;
    }
    OsalMSleep(RESET_HIGH_DELAY);
    HDF_LOGI("%s: succ\n", __func__);
    return HDF_SUCCESS;
}
```

Reuse the I2C I/O pins and obtain the operation handle. For details, see  [I2C Usage Guidelines](i2c-usage-guidelines.md).

```
static int TouchSetupI2c(TouchCoreData *cd)
{
    /* config I2C reuse I2C7 */
    writel(I2C_REG_CFG, IO_DEVICE_ADDR(I2C7_DATA_REG_ADDR));
    writel(I2C_REG_CFG, IO_DEVICE_ADDR(I2C7_CLK_REG_ADDR));
    /* get i2c handle */
    cd->i2cClient.i2cHandle = I2cOpen(cd->i2cClient.i2cCfg.busNum);
    if (cd->i2cClient.i2cHandle == NULL) {
        HDF_LOGE("open i2c failed");
        return HDF_FAILURE;
    }
    HDF_LOGI("%s: exit succ", __func__);
    return HDF_SUCCESS;
}
```

## Creating a Task for IRQ<a name="section1621716152616"></a>

Create a task for obtaining and processing touch reporting data.

```
static int TouchIrqTaskInit(TouchCoreData *cd)
{
    /* Initialize the message event. */
    int ret = LOS_EventInit(&g_touchEventIrq);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("LOS_EventInit failed, ret = %d", ret);
        return HDF_FAILURE;
    }

    /* Register an interrupt. */
    ret = GpioSetIrq(cd->intGpioNum, cd->irqFlag, IrqHandle, cd);
    if (ret != 0) {
        HDF_LOGE("register irq failed, ret %d", ret);
        return ret;
    }
    /* Enable the IRQ. */
    ret = GpioEnableIrq(cd->intGpioNum);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("enable irq failed, ret %d", ret);
        return HDF_FAILURE;
    }
    /* Create an IRQ task for reading and parsing the data of the input event. */
    TSK_INIT_PARAM_S handleEventTask = {0};
    UINT32 handleEventTaskID;
    handleEventTask.pfnTaskEntry = (TSK_ENTRY_FUNC)TouchHandleEvent;
    handleEventTask.uwStackSize  = TASK_SIZE;
    handleEventTask.pcName       = "HdfTouchEventHandler";
    handleEventTask.usTaskPrio   = TASK_PRIO_LEVEL_TWO;
    handleEventTask.uwResved     = LOS_TASK_STATUS_DETACHED;
    if (LOS_TaskCreate(&handleEventTaskID, &handleEventTask) != HDF_SUCCESS) {
        HDF_LOGE("%s: LOS_TaskCreate fail, HdfTouchEventHandler", __func__);
        return HDF_FAILURE;
    }
    HDF_LOGI("%s: exit succ", __func__);
    return HDF_SUCCESS;
}
```

IRQ function

```
int32_t IrqHandle(uint16_t irqGpio, void *data)
{
    HDF_LOGD("%s: irq is triggered, irqGpio = %d", __func__, irqGpio);
    (void)data;
    /* Disable the IRQ. */
    int ret = GpioDisableIrq(irqGpio);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("disable irq failed, ret %d", ret);
    }
    (void)LOS_EventWrite(&g_touchEventIrq, EVENT_SYNC);
    return HDF_SUCCESS;
}
```

Task processing functions

```
static void TouchHandleEvent(void)
{
    InputEventData event;
    TouchCoreData *cd = GetCoreData();
    (void)memset_s(&event, sizeof(InputEventData), 0, sizeof(InputEventData));

    while (true) {
        /* Read the synchronization event. */
        int ret = LOS_EventRead(&g_touchEventIrq, EVENT_SYNC, LOS_WAITMODE_AND | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
        if (ret != EVENT_SYNC) {
            OsalMSleep(TASK_SLEEP_MS);
        } else {
            /* Read and parse the touch reporting event. */
            if (EventHandler(cd, &event) == HDF_SUCCESS) {
                TouchWakeupPoll();
            }
        }
        /* Enable the IRQ. */
        ret = GpioEnableIrq(cd->intGpioNum);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("enable irq failed, ret %d", ret);
        }

        if (cd->shouldStop) {
            HDF_LOGE("%s: the event task should be stoped", __func__);
            break;
        }
    }
}
```

## Creating a Device File and Performing Operations on It<a name="section2097184020265"></a>

The following describes the functions for creating and operating a device file.  **Iocatl**  is used as an example.

```
/* Create a device file. */
register_driver(TOUCH_DEVICE, &g_touchDevOps, TOUCH_DEVICE_MODE, NULL);

/* File operations */
static const struct file_operations_vfs g_touchDevOps = {
    .open = TouchOpen,
    .close = TouchClose,
    .read = NULL,
    .write = NULL,
    .seek = NULL,
    .ioctl = TouchIoctl,
    .mmap = NULL,
#ifndef CONFIG_DISABLE_POLL
    .poll = TouchPoll,
#endif
    .unlink = NULL,
};

/* Ioctl operation mode */
static int TouchIoctl(FAR struct file *filep, int cmd, unsigned long arg)
{
    int ret;
    if (filep == NULL) {
        HDF_LOGE("%s: param is null", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    switch (cmd) {
        case INPUT_IOCTL_GET_EVENT_DATA:
            ret = IoctlReadInputEvent(arg);
            break;
        case INPUT_IOCTL_GET_DEVICE_TYPE:
            ret = IoctlGetDeviceType(arg);
            break;
        case INPUT_IOCTL_GET_CHIP_INFO:
            ret = IoctlGetChipInfo(arg);
            break;
        default:
            ret = 0;
            HDF_LOGE("%s: cmd unknown, cmd = 0x%x", __func__, cmd);
            break;
    }
    return ret;
}
```

## Main Data Structures<a name="section2088122714426"></a>

```
/* Touch event */
typedef enum {
    EVENT_DOWN,
    EVENT_UP,
    EVENT_CONTACT,
} EventType;

/* I2C configuration information */
typedef struct {
    unsigned short busNum;
    unsigned short addr;
} I2cConfig;

/* I2C client information */
typedef struct {
    struct DevHandle *i2cHandle;
    I2cConfig i2cCfg;
} InputI2cClient;

/* Data structure of an input event */
typedef struct {
    int x;
    int y;
    int z;
    int definedEvent;
    int fingerID;
    int pointNum;
    struct timeval timeStamp;
    bool moreDataFlag;
} InputEventData;

/* Core data structure of the touchscreen driver */
typedef struct {
    unsigned int inputDevType;
    wait_queue_head_t pollWait;
    bool readFinishFlag;
    bool shouldStop;
    struct InputConfig inputCfg;
    InputI2cClient i2cClient;
    int intGpioNum;
    int rstGpioNum;
    unsigned int irqFlag;
    unsigned int powerStatus;
    char chipInfo[CHIP_INFO_LEN];
    char vendorName[VENDOR_NAME_LEN];
    char chipName[CHIP_NAME_LEN];
} TouchCoreData;
```

