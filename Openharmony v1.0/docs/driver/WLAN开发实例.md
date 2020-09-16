# WLAN开发实例<a name="ZH-CN_TOPIC_0000001052682331"></a>

本例程提供WLAN模块初始化过程的完整使用流程。示例如下：

1、根据硬件，修改配置参数

```
/* 根据硬件参数，通过wifi_config.hcs配置相关参数，以下是配置chip的示例 */
hisi :& deviceList {
    C1 :: Chip {
        chipName = "hisi";   /* WLAN芯片的名称 */
        chipId = 0;          /* WLAN芯片的id */
        featureMap = 0xFFFF; /* WLAN模块特性map */
        powerType = 0;       /* 电源类型 */
        irqNo = 0;           /* 中断号 */
        bus {
            busType = 0;       /* 总线类型：0-sdio 1-usb 2-spi etc. */
            funcNum = [1];     /* 功能号 */
            vendorId = 0x0296; /* 厂商id */
            deviceId = 0x5347; /* 设备id */
            timeout = 1000;    /* 读/写数据的超时时间 */
            blockSize = 512;   /* 读/写数据的块大小 */
        }
    }
}
board {
	boardName = "3518EV300";  /* 单板名称 */
	busType = 0;              /* 总线类型 */
	busIdx = 1;               /* 总线索引 */
	reset   = [5,0];          /* GPIO组号和偏移 */
	gpioArgs = [10,10,10];    /* GPIO组数, GPIO每组个数, GPIO中断数 */
	busRegs {
		cclk_out = [0x112C0048, 0x1A04];  /* 时钟线寄存器配置 */
		ccmd     = [0x112C004C, 0x1004];  /* 命令传输线寄存器配 */
		cdata0    = [0x112C0064, 0x1004]; /* 数据0线线寄存器配 */
		cdata1    = [0x112C0058, 0x1004]; /* 数据1线寄存器配 */
		cdata2    = [0x112C005C, 0x1004]; /* 数据2线寄存器配 */
		cdata3    = [0x112C0060, 0x1004]; /* 数据3线寄存器配 */
	}
}
```

2、适配挂接

```
/* WLAN初始化流程 */
#include "gpio_if.h"
#include "hdf_wifi_core.h"
#include "hdf_device_desc.h"
#include "hdf_wifi_product.h"
#include "hdf_log.h"
#include "hdf_wifi_cmd.h"
#include "osal_mem.h"
#include "osal_time.h"
#include "hdf_wifi_config.h"

struct HdfWifiProductData g_hdfWifiProductData;

/* 声明芯片驱动 */
HDF_WIFI_CHIP_DECLARE(hisi);

int32_t Hi3881Deinit(struct HdfWifiChipData *chipData);
int32_t Hi3881Init(struct HdfWifiChipData *chipData, const struct HdfConfigWifiChip *chipConfig);
HDF_WIFI_CHIP_DRIVER(hisi, Hi3881Init, Hi3881Deinit);

struct HdfWifiChipData *g_wifiChips[] = {
    HDF_WIFI_CHIP(hisi),
};

/* 声明芯片驱动 */
static const struct HdfConfigWifiBoard *HdfWifiGetBoardConfig(void)
{
    struct HdfConfigWifiRoot *rootConfig = HdfWifiGetModuleConfigRoot();

    return &rootConfig->wifiConfig.board;
}

int32_t HdfWifiGetBusIdx(void)
{
    const struct HdfConfigWifiBoard *board = HdfWifiGetBoardConfig();
    if (board != NULL) {
        return board->busIdx;
    }

    return -1;
}

static void HdfWifiChipReset(void)
{
    const struct HdfConfigWifiBoard *board = HdfWifiGetBoardConfig();
    uint16_t gpio;
    int32_t ret;

    if (board != NULL && board->busType == BUS_SDIO) {
        /* set dir input */
        gpio = board->reset[0] *  board->gpioArgs[1] + board->reset[1];
        ret = GpioSetDir(gpio, 1);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("%s: set dir fail! ret:%d\n", __func__, ret);
            return;
        }
        /* power off */
        ret = GpioWrite(gpio, 0);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("%s: val:0 write fail! ret:%d\n", __func__, ret);
            return;
        }
        OsalMSleep(0x10);
        /* power on */
        ret = GpioWrite(gpio, 1);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("%s: val:1 write fail! ret:%d\n", __func__, ret);
            return;
        }
        OsalMSleep(0x20);
    }

    return;
}

static int32_t HdfWifiProductInit(struct HdfDeviceObject *device)
{
    int32_t ret;

    ret = HdfParseWifiConfig(device->property);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s:ParseWifiConfig error ret=%d", __func__, ret);
        return ret;
    }
    /* reset chip firstly */
    HdfWifiChipReset();
    return HDF_SUCCESS;
}

/* WifiModule初始化 */
static int16_t HdfWifiModuleInit(const struct HdfConfigWifiModuleConfig *config)
{
    if (config == NULL) {
        return HDF_FAILURE;
    }
    /* 创建Module */
    struct WifiModule *module = WifiModuleCreate(config);
    if (module == NULL) {
        return HDF_FAILURE;
    }
    g_hdfWifiProductData.module = module;
    HDF_LOGD("%s:hdf wifi module init succ", __func__);

    return HDF_SUCCESS;
}

/* 通过芯片的名称获取相应的芯片驱动 */
static struct HdfWifiChipData *HdfWifiFindChipDriverByName(const char *chipName)
{
    if (chipName == NULL) {
        return NULL;
    }

    bool found = FALSE;
    struct HdfWifiChipData *chipDriver = NULL;
    int32_t chipNum = sizeof(g_wifiChips) / sizeof(g_wifiChips[0]);

    /* 循环遍历所配置的芯片，返回匹配的芯片驱动 */
    for (int32_t i = 0; i < chipNum; i++) {
        chipDriver = g_wifiChips[i];
        if (chipDriver != NULL && !strcmp(chipDriver->name, chipName)) {
            found = TRUE;
            HDF_LOGI("%s: find chip %s", __func__, chipName);
            break;
        }
    }

    return found ? chipDriver : NULL;
}

/* 芯片初始化 */
static int16_t HdfWifiChipInit(struct WifiModule *module, const struct HdfConfigWifiChip *chipConfig)
{
    int32_t ret;

    if (module == NULL) {
        HDF_LOGE("%s: module is NULL", __func__);
        return HDF_FAILURE;
    }

    /* 通过芯片的名称获取相应的芯片驱动 */
    struct HdfWifiChipData *chipDriver = HdfWifiFindChipDriverByName(chipConfig->chipName);
    if (chipDriver == NULL) {
        HDF_LOGI("%s: chip driver %s not supported", __func__, chipConfig->chipName);
        return HDF_DEV_ERR_OP;
    }

    if (chipDriver->init == NULL) {
        HDF_LOGI("%s: chip driver %s not 'init' api", __func__, chipConfig->chipName);
        return HDF_DEV_ERR_OP;
    }

    /* 初始化芯片 */
    ret = chipDriver->init(chipDriver, chipConfig);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s:init chip %s error ret=%d", __func__, chipConfig->chipName, ret);
        return HDF_DEV_ERR_OP;
    }

    /* 将芯片和feature进行绑定 */
    for (uint32_t i = 0; i < HDF_WIFI_FEATURE_NUM; i++) {
        if ((module->feList->fe[i] != NULL) && (chipConfig->featureMap & (1 << i))) {
            HDF_LOGI("%s:reg chip to feature %d", __func__, i);
            module->feList->fe[i]->chip = chipDriver;
        }
    }
    HDF_LOGI("%s:init chip %s success!", __func__, chipConfig->chipName);
    return HDF_SUCCESS;
}

/* WLAN平台初始化 */
static int16_t HdfWifiPlatformInit(const struct HdfConfigWifiModuleConfig *config)
{
    /* 根据配置进行module初始化 */
    int32_t ret = HdfWifiModuleInit(config);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s:HdfWifiModuleInit error ret=%d", __func__, ret);
        return ret;
    }

    return ret;
}

struct HdfWifiProductData *HdfWifiGetProduct(void)
{
    return &g_hdfWifiProductData;
}

static int32_t HdfWifiDriverInit(struct HdfDeviceObject *device)
{
    int32_t ret;
    HDF_LOGD("%s:start..", __func__);
    if (device == NULL) {
        return HDF_FAILURE;
    }
    /* 配置分析（初始化WLAN配置） */
    ret = HdfWifiProductInit(device);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s:init produt cfg error ret=%d", __func__, ret);
        return ret;
    }
    /* 获取全量配置的结构体对象 */
    struct HdfConfigWifiRoot *rootConfig = HdfWifiGetModuleConfigRoot();
    struct HdfWifiProductData *wifiData = HdfWifiGetProduct();
    const struct HdfConfigWifiModuleConfig *moduleConfig = &rootConfig->wifiConfig.moduleConfig;
    /* WIFI平台的初始化（Module初始化） */
    ret = HdfWifiPlatformInit(moduleConfig);
    if (ret) {
        HDF_LOGE("%s:init platform error ret=%d", __func__, ret);
        return ret;
    }

    /* 循环遍历所配置的芯片，并初始化有相应硬件的芯片 */
    for (int16_t i = 0; i < rootConfig->wifiConfig.deviceList.chipSize; i++) {
        const struct HdfConfigWifiChip *chipConfig = &rootConfig->wifiConfig.deviceList.chip[i];
        ret = HdfWifiChipInit(wifiData->module, chipConfig);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("%s:init chip %d error ret=%d, feature %d is unavailable!", __func__, i, ret,
                chipConfig->featureMap);
        } else {
            wifiData->device = device;
            HDF_LOGE("%s:init chip %d success!", __func__, i);
            break;
        }
    }

    HDF_LOGD("%s:success..", __func__);
    return ret;
}

int32_t HdfWifiDriverDispatch(struct HdfDeviceIoClient *client, int id, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    if (client == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    return WifiCmdProcess(client->device, id, data, reply);
}

static int HdfWifiDriverBind(struct HdfDeviceObject *dev)
{
    if (dev == NULL) {
        return HDF_FAILURE;
    }
    static struct IDeviceIoService wifiService = {
        .object.objectId = 1,
        .Dispatch = HdfWifiDriverDispatch,
    };
    dev->service = &wifiService;
    return HDF_SUCCESS;
}

static void HdfWifiDriverRelease(struct HdfDeviceObject *object)
{
    (void)object;
}

struct HdfDriverEntry g_hdfWifiEntry = {
    .moduleVersion = 1,
    .Bind = HdfWifiDriverBind,
    .Init = HdfWifiDriverInit,
    .Release = HdfWifiDriverRelease,
    .moduleName = "HDF_WIFI"
};

HDF_INIT(g_hdfWifiEntry);
```

