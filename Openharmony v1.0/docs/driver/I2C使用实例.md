# I2C使用实例<a name="ZH-CN_TOPIC_0000001052218252"></a>

本例程以操作开发板上的I2C设备为例，详细展示I2C接口的完整使用流程。

本例拟对Hi3516DV300某开发板上TouchPad设备进行简单的寄存器读写访问，基本硬件信息如下：

-   SOC：hi3516dv300

-   Touch IC：I2C地址为0x38, IC内部寄存器位宽为1字节。

-   原理图信息：TouchPad设备挂接在3号I2C控制器下；IC的复位管脚为3号GPIO

本例程首先对Touch IC进行复位操作（开发板上电默认会给TouchIC供电，本例程不考虑供电），然后对其某某个内部寄存器进行随机读写，测试I2C通路是否正常。

>![](public_sys-resources/icon-note.gif) **说明：** 
>本例程重点在于展示I2C设备访问流程，并验证I2C通路，所以对于设备寄存器读写值不做关注，读写寄存器导致的行为由设备自身决定。

示例如下：

```
#include "i2c_if.h"          /* I2C标准接口头文件 */
#include "gpio_if.h"         /* GPIO标准接口头文件 */
#include "hdf_log.h"         /* 标准日志打印头文件 */
#include "osal_io.h"         /* 标准IO读写接口头文件 */
#include "osal_time.h"       /* 标准延迟&睡眠接口头文件 */

/* 定义一个表示TP设备的结构体，存储i2c及gpio相关硬件信息 */
struct TpI2cDevice {
    uint16_t rstGpio;             /* 复位管脚 */
    uint16_t busId;               /* I2C总线号 */ 
    uint16_t addr;                /* I2C设备地址 */ 
    uint16_t regLen;              /* 寄存器字节宽度 */ 
    struct DevHandle *i2cHandle;  /* I2C控制器句柄 */ 
};

/* I2C管脚io配置，需要查阅SOC寄存器手册  */
#define I2C3_DATA_REG_ADDR 0x112f008c /* 3号I2C控制器SDA管脚配置寄存器地址 */
#define I2C3_CLK_REG_ADDR 0x112f0090  /* 3号I2C控制器SCL管脚配置寄存器地址 */
#define I2C_REG_CFG 0x5f1             /* 3号I2C控制器SDA及SCL管脚配置值 */

static void TpSocIoCfg(void)
{
    /* 将3号I2C控制器对应两个管脚的IO功能设置为I2C */
    OSAL_WRITEL(I2C_REG_CFG, IO_DEVICE_ADDR(I2C3_DATA_REG_ADDR));
    OSAL_WRITEL(I2C_REG_CFG, IO_DEVICE_ADDR(I2C3_CLK_REG_ADDR));
}

/* 对TP的复位管脚进行初始化， 拉高维持20ms, 再拉底维持50ms，最后再拉高维持20s， 完成复位动作 */
static int32_t TestCaseGpioInit(struct TpI2cDevice *tpDevice)
{
    int32_t ret;

    /* 设置复位管脚方向为输出 */ 
    ret = GpioSetDir(tpDevice->rstGpio, GPIO_DIR_OUT);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set rst dir fail!:%d", __func__, ret);
        return ret;
    }

    ret = GpioWrite(tpDevice->rstGpio, GPIO_VAL_HIGH);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set rst hight fail!:%d", __func__, ret);
        return ret;
    }
    OsalMSleep(20);

    ret = GpioWrite(tpDevice->rstGpio, GPIO_VAL_LOW);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set rst low fail!:%d", __func__, ret);
        return ret;
    }
    OsalMSleep(50);

    ret = GpioWrite(tpDevice->rstGpio, GPIO_VAL_HIGH);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: set rst high fail!:%d", __func__, ret);
        return ret;
    }
    OsalMSleep(20);

    return HDF_SUCCESS;
}

/* 基于I2cTransfer方法封装一个寄存器读写的辅助函数， 通过flag表示读或写 */
static int TpI2cReadWrite(struct TpI2cDevice *tpDevice, unsigned int regAddr,
    unsigned char *regData, unsigned int dataLen, uint8_t flag)
{
    int index = 0;
    unsigned char regBuf[4] = {0};
    struct I2cMsg msgs[2] = {0};

    /* 单双字节寄存器长度适配 */
    if (tpDevice->regLen == 1) { 
        regBuf[index++] = regAddr & 0xFF;
    } else {
        regBuf[index++] = (regAddr >> 8) & 0xFF;
        regBuf[index++] = regAddr & 0xFF;
    }

    /* 填充I2cMsg消息结构 */ 
    msgs[0].addr = tpDevice->addr;
    msgs[0].flags = 0; /* 标记为0，表示写入 */ 
    msgs[0].len = tpDevice->regLen;
    msgs[0].buf = regBuf;

    msgs[1].addr = tpDevice->addr;
    msgs[1].flags = (flag == 1) ? I2C_FLAG_READ : 0; /* 添加读标记位，表示读取 */ 
    msgs[1].len = dataLen;
    msgs[1].buf = regData;

    if (I2cTransfer(tpDevice->i2cHandle, msgs, 2) != 2) {
        HDF_LOGE("%s: i2c read err", __func__);
        return HDF_FAILURE;
    }
    return HDF_SUCCESS;
}

/* TP寄存器读函数 */ 
static inline int TpI2cReadReg(struct TpI2cDevice *tpDevice, unsigned int regAddr,
    unsigned char *regData, unsigned int dataLen)
{
    return TpI2cReadWrite(tpDevice, regAddr, regData, dataLen, 1);
}

/* TP寄存器写函数 */ 
static inline int TpI2cWriteReg(struct TpI2cDevice *tpDevice, unsigned int regAddr,
    unsigned char *regData, unsigned int dataLen)
{
    return TpI2cReadWrite(tpDevice, regAddr, regData, dataLen, 0);
}

/* I2C例程总入口 */ 
static int32_t TestCaseI2c(void)
{
    int32_t i;
    int32_t ret;
    unsigned char bufWrite[7] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xA, 0xB, 0xC };
    unsigned char bufRead[7] = {0};
    static struct TpI2cDevice tpDevice;

    /* IO管脚功能配置 */
    TpSocIoCfg();

    /* TP设备信息初始化 */ 
    tpDevice.rstGpio = 3;
    tpDevice.busId = 3;
    tpDevice.addr = 0x38;
    tpDevice.regLen = 1;
    tpDevice.i2cHandle = NULL;

    /* GPIO管脚初始化 */ 
    ret = TestCaseGpioInit(&tpDevice);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: gpio init fail!:%d", __func__, ret);
        return ret;
    }

    /* 打开I2C控制器 */ 
    tpDevice.i2cHandle = I2cOpen(tpDevice.busId);
    if (tpDevice.i2cHandle == NULL) {
        HDF_LOGE("%s: Open I2c:%u fail!", __func__, tpDevice.busId);
        return -1;
    }

    /* 向TP-IC的0xD5寄存器连续写7字节数据 */ 
    ret = TpI2cWriteReg(&tpDevice, 0xD5, bufWrite, 7);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: tp i2c write reg fail!:%d", __func__, ret);
        I2cClose(tpDevice.i2cHandle);
        return -1;
    }
    OsalMSleep(10);

    /* 从TP-IC的0xDO寄存器连续读7字节数据 */ 
    ret = TpI2cReadReg(&tpDevice, 0xD5, bufRead, 7);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: tp i2c read reg fail!:%d", __func__, ret);
        I2cClose(tpDevice.i2cHandle);
        return -1;
    }

    HDF_LOGE("%s: tp i2c write&read reg success!", __func__);
    for (i = 0; i < 7; i++) {
        HDF_LOGE("%s: bufRead[%d] = 0x%x", __func__, i, bufRead[i]);
    }

    /* 访问完毕关闭I2C控制器 */ 
    I2cClose(tpDevice.i2cHandle);
    return ret;
}
```

