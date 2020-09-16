# WLAN Development Example<a name="EN-US_TOPIC_0000001052682331"></a>

This example describes how to initialize a WLAN module. Example:

1. Modify configuration parameters based on hardware parameters.

```
/* Configure parameters in wifi_config.hcs based on hardware parameters. The following is an example of WLAN chip configuration. */
hisi :& deviceList {
    C1 :: Chip {
        chipName = "hisi";   /* Chip name */
        chipId = 0;          /* Chip ID */
        featureMap = 0xFFFF; /* Feature map of a WLAN module */
        powerType = 0;       /* Power type */
        irqNo = 0;           /* Interrupt request number */
        bus {
            busType = 0;       /* Bus type: 0-sdio 1-usb 2-spi etc. */
            funcNum = [1];     /* Function ID */
            vendorId = 0x0296; /* Vendor ID */
            deviceId = 0x5347; /* Device ID */
            timeout = 1000;    /* Timeout duration for reading/writing data */
            blockSize = 512;   /* Block size of the data to be read or written */
        }
    }
}
board {
	boardName = "3518EV300";  /* Board name */
	busType = 0;              /* Bus type */
	busIdx = 1;               /* Bus index */
	reset   = [5,0];          /* GPIO group index and offset in the group */
	gpioArgs = [10,10,10];    /* Number of GPIO groups, GPIO pins in each group, and GPIO interrupts */
	busRegs {
		cclk_out = [0x112C0048, 0x1A04];  /* Configure the clock cable register. */
		ccmd     = [0x112C004C, 0x1004];  /* Configure the command transmission cable register. */
		cdata0    = [0x112C0064, 0x1004]; /* Configure data 0 cable register. */
		cdata1    = [0x112C0058, 0x1004]; /* Configure data 1 cable register. */
		cdata2    = [0x112C005C, 0x1004]; /* Configure data 2 cable register. */
		cdata3    = [0x112C0060, 0x1004]; /* Configure data 3 cable register. */
	}
}
```

2. Adapt and mount a WLAN module.

```
/* WLAN initialization process */
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

/* Declare a chip driver. */
HDF_WIFI_CHIP_DECLARE(hisi);

int32_t Hi3881Deinit(struct HdfWifiChipData *chipData);
int32_t Hi3881Init(struct HdfWifiChipData *chipData, const struct HdfConfigWifiChip *chipConfig);
HDF_WIFI_CHIP_DRIVER(hisi, Hi3881Init, Hi3881Deinit);

struct HdfWifiChipData *g_wifiChips[] = {
    HDF_WIFI_CHIP(hisi),
};

/* Declare a chip driver. */
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

/* Initialize a WifiModule. */
static int16_t HdfWifiModuleInit(const struct HdfConfigWifiModuleConfig *config)
{
    if (config == NULL) {
        return HDF_FAILURE;
    }
    /* Create a WifiModule. */
    struct WifiModule *module = WifiModuleCreate(config);
    if (module == NULL) {
        return HDF_FAILURE;
    }
    g_hdfWifiProductData.module = module;
    HDF_LOGD("%s:hdf wifi module init succ", __func__);

    return HDF_SUCCESS;
}

/* Obtain the chip driver based on the chip name. */
static struct HdfWifiChipData *HdfWifiFindChipDriverByName(const char *chipName)
{
    if (chipName == NULL) {
        return NULL;
    }

    bool found = FALSE;
    struct HdfWifiChipData *chipDriver = NULL;
    int32_t chipNum = sizeof(g_wifiChips) / sizeof(g_wifiChips[0]);

    /* Traverse the configured chips cyclically and return the matched chip driver. */
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

/* Initialize the chip. */
static int16_t HdfWifiChipInit(struct WifiModule *module, const struct HdfConfigWifiChip *chipConfig)
{
    int32_t ret;

    if (module == NULL) {
        HDF_LOGE("%s: module is NULL", __func__);
        return HDF_FAILURE;
    }

    /* Obtain the chip driver based on the chip name. */
    struct HdfWifiChipData *chipDriver = HdfWifiFindChipDriverByName(chipConfig->chipName);
    if (chipDriver == NULL) {
        HDF_LOGI("%s: chip driver %s not supported", __func__, chipConfig->chipName);
        return HDF_DEV_ERR_OP;
    }

    if (chipDriver->init == NULL) {
        HDF_LOGI("%s: chip driver %s not 'init' api", __func__, chipConfig->chipName);
        return HDF_DEV_ERR_OP;
    }

    /* Initialize the chip driver. */
    ret = chipDriver->init(chipDriver, chipConfig);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s:init chip %s error ret=%d", __func__, chipConfig->chipName, ret);
        return HDF_DEV_ERR_OP;
    }

    /* Bind the chip to a feature of the module. */
    for (uint32_t i = 0; i < HDF_WIFI_FEATURE_NUM; i++) {
        if ((module->feList->fe[i] != NULL) && (chipConfig->featureMap & (1 << i))) {
            HDF_LOGI("%s:reg chip to feature %d", __func__, i);
            module->feList->fe[i]->chip = chipDriver;
        }
    }
    HDF_LOGI("%s:init chip %s success!", __func__, chipConfig->chipName);
    return HDF_SUCCESS;
}

/* Initialize the WLAN platform.*/
static int16_t HdfWifiPlatformInit(const struct HdfConfigWifiModuleConfig *config)
{
    /* Initialize the module based on the configuration. */
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
    /* Analyze configuration (initialize WLAN configuration). */
    ret = HdfWifiProductInit(device);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s:init produt cfg error ret=%d", __func__, ret);
        return ret;
    }
    /* Obtain the structure with the configured parameters. */
    struct HdfConfigWifiRoot *rootConfig = HdfWifiGetModuleConfigRoot();
    struct HdfWifiProductData *wifiData = HdfWifiGetProduct();
    const struct HdfConfigWifiModuleConfig *moduleConfig = &rootConfig->wifiConfig.moduleConfig;
    /* Initialize the WLAN platform (WLAN module initialization). */
    ret = HdfWifiPlatformInit(moduleConfig);
    if (ret) {
        HDF_LOGE("%s:init platform error ret=%d", __func__, ret);
        return ret;
    }

    /* Traverse the configured chips cyclically and initialize the matched chip on the hardware. */
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

