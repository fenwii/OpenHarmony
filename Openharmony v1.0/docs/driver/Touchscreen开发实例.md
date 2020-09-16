# Touchscreen开发实例<a name="ZH-CN_TOPIC_0000001052576212"></a>

本实例提供Touchscreen驱动开发示例，并简要对具体关键点进行开发说明。

## 加载驱动<a name="section85281142102317"></a>

基于HDF驱动模型，加载启动Touchscreen驱动，代码形式如下，具体原理可参考[HDF驱动开发指南](驱动开发.md)。

```
/* 根据实际需求，实现TouchDispatch */
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

/* 根据业务实际需求，实现TouchEntryOpen */
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

/* Touch驱动的总入口Init函数 */
int Gt911TouchDriverInit(struct HdfDeviceObject *object)
{
    /* 具体实现参考下面“执行初始化”示例代码 */
    return HDF_SUCCESS;
}
/* HDF驱动入口数据结构 */
struct HdfDriverEntry g_gt5p5TouchDevEntry = {
    .moduleVersion = 1,
    .moduleName = "HDF_TOUCHSCREEN",
    .Bind = Gt911TouchDriverOpen,
    .Init = Gt911TouchDriverInit,
};

HDF_INIT(g_gt5p5TouchDevEntry);
```

## 执行初始化<a name="section189081946192410"></a>

如下初始化流程包含常用的步骤，实际业务开发时，可根据具体需求增删及修改如下初始化中的相关步骤，具体示例如下。

```
int TouchEntryInit(struct HdfDeviceObject *object)
{
    (void)object;
    /* 创建全局数据结构体，用于存储器件驱动相关信息 */
    g_coreData = (TouchCoreData *)OsalMemAlloc(sizeof(TouchCoreData));
    if (g_coreData == NULL) {
        HDF_LOGE("%s: malloc failed", __func__);
        return HDF_ERR_MALLOC_FAIL;
    }

    if (memset_s(g_coreData, sizeof(TouchCoreData), 0, sizeof(TouchCoreData)) != EOK) {
        HDF_LOGE("%s: memset_s fail", __func__);
        return;
    }
    /* 初始化全局数据结构体，将器件驱动相关的配置信息，进行解析赋值 */
    TouchConfigInit(g_coreData);
    /* 设置GPIO相关的属性及状态 */
    if (TouchSetupGpio(g_coreData)) {
        goto ERR_EXIT;
    }
    /* 设置并获取I2C BUS操作句柄 */
    if (TouchSetupI2c(g_coreData)) {
        goto ERR_EXIT;
    }
    /* 创建Task用于监听处理中断业务 */
    if (TouchIrqTaskInit(g_coreData)) {
        goto ERR_EXIT;
    }
    /* 进行电源初始化配置及操作 */
    if (TouchPowerInit(g_coreData)) {
        goto ERR_EXIT;
    }
    /* 创建input设备文件 */
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

## 配置基础参数<a name="section19856687253"></a>

如下示例中，主要配置了i2c的从地址及总线号、屏幕的报点范围、input设备类型、GPIO管脚号等。具体开发过程，需要根据实际使用的单板及器件进行配置，以下为示例。

```
static void TouchConfigInit(TouchCoreData *cd)
{
    /* init waitqueue for poll */
    __init_waitqueue_head(&cd->pollWait);

    /* 配置i2c从地址、总线号、报点范围 */
    cd->i2cClient.i2cCfg.addr = DRIVER_CHIP_I2C_ADDR;
    cd->i2cClient.i2cCfg.busNum = I2C_BUS_NUM;
    cd->inputCfg.solutionX = TOUCH_SOLUTION_X;
    cd->inputCfg.solutionY = TOUCH_SOLUTION_Y;

    /* 配置input设备类型，本例为Touch驱动 */
    cd->inputDevType = INDEV_TYPE_TOUCH;

    /* 配置reset、irq的gpio号，以及irq的中断触发方式 */
    cd->rstGpioNum = RST_GPIO_OFFSET;
    cd->intGpioNum = INT_GPIO_OFFSET;
    cd->irqFlag = OSAL_IRQF_TRIGGER_FALLING;
}
```

## 配置及使用IO管脚<a name="section636814296252"></a>

如下为reset和irq管脚的初始化配置，统一使用PAL接口实现对GPIO的操作，具体可参考PLATFORM提供的[GPIO接口使用指导](GPIO使用指导.md)

```
static int TouchSetupGpio(TouchCoreData *cd)
{
    /* 配置int为输入上拉 */
    writel(INT_REG_CFG, IO_DEVICE_ADDR(INR_REG_ADDR));
    /* 设置int为输入方向 */
    int ret = GpioSetDir(cd->intGpioNum, GPIO_DIR_IN);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("set int to input dir failed, ret %d", ret);
        return HDF_FAILURE;
    }
    /* 设置reset为输出方向 */
    ret = GpioSetDir(cd->rstGpioNum, GPIO_DIR_OUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("set reset to output dir failed, ret %d", ret);
        return HDF_FAILURE;
    }
    /* 拉高reset */
    ret = GpioWrite(cd->rstGpioNum, GPIO_VAL_HIGH);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("pull up reset gpio failed, ret %d", ret);
        return HDF_FAILURE;
    }
    OsalMSleep(RESET_HIGH_DELAY);
    /* 拉低reset */
    ret = GpioWrite(cd->rstGpioNum, GPIO_VAL_LOW);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("pull down reset gpio failed, ret %d", ret);
        return HDF_FAILURE;
    }
    OsalMSleep(RESET_LOW_DELAY);
    /* 再次拉高reset */
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

配置I2C的IO管脚复用，以及其操作句柄的获取，可参考PLATFORM提供的[I2C接口使用指导](I2C使用指导.md)

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

## 创建中断处理TASK<a name="section1621716152616"></a>

创建用于获取及处理报点数据的Task

```
static int TouchIrqTaskInit(TouchCoreData *cd)
{
    /* 初始化消息事件 */
    int ret = LOS_EventInit(&g_touchEventIrq)；
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("LOS_EventInit failed, ret = %d", ret);
        return HDF_FAILURE;
    }

    /* 注册中断 */
    ret = GpioSetIrq(cd->intGpioNum, cd->irqFlag, IrqHandle, cd);
    if (ret != 0) {
        HDF_LOGE("register irq failed, ret %d", ret);
        return ret;
    }
    /* 使能中断 */
    ret = GpioEnableIrq(cd->intGpioNum);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("enable irq failed, ret %d", ret);
        return HDF_FAILURE;
    }
    /* 创建中断处理Task，其负责input event数据的读取和解析 */
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

中断响应函数

```
int32_t IrqHandle(uint16_t irqGpio, void *data)
{
    HDF_LOGD("%s: irq is triggered, irqGpio = %d", __func__, irqGpio);
    (void)data;
    /* 关闭中断响应 */
    int ret = GpioDisableIrq(irqGpio);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("disable irq failed, ret %d", ret);
    }
    (void)LOS_EventWrite(&g_touchEventIrq, EVENT_SYNC);
    return HDF_SUCCESS;
}
```

Task处理函数

```
static void TouchHandleEvent(void)
{
    InputEventData event;
    TouchCoreData *cd = GetCoreData();
    (void)memset_s(&event, sizeof(InputEventData), 0, sizeof(InputEventData));

    while (true) {
        /* 读取同步事件 */
        int ret = LOS_EventRead(&g_touchEventIrq, EVENT_SYNC, LOS_WAITMODE_AND | LOS_WAITMODE_CLR, LOS_WAIT_FOREVER);
        if (ret != EVENT_SYNC) {
            OsalMSleep(TASK_SLEEP_MS);
        } else {
            /* 报点事件的读取及解析 */
            if (EventHandler(cd, &event) == HDF_SUCCESS) {
                TouchWakeupPoll();
            }
        }
        /* 使能中断 */
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

## 创建及操作设备文件<a name="section2097184020265"></a>

设备文件的创建及其操作接口，本处仅举例Ioctl的使用

```
/* 创建设备文件 */
register_driver(TOUCH_DEVICE, &g_touchDevOps, TOUCH_DEVICE_MODE, NULL);

/* 文件操作ops */
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

/* Ioctl的操作方式 */
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

## 主要数据结构<a name="section2088122714426"></a>

```
/* 触摸事件 */
typedef enum {
    EVENT_DOWN,
    EVENT_UP,
    EVENT_CONTACT,
} EventType;

/* I2C配置信息 */
typedef struct {
    unsigned short busNum;
    unsigned short addr;
} I2cConfig;

/* I2C客户端信息 */
typedef struct {
    struct DevHandle *i2cHandle;
    I2cConfig i2cCfg;
} InputI2cClient;

/* 输入事件数据结构体 */
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

/* 器件驱动核心数据结构体 */
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

