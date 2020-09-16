# I2C Usage Example<a name="EN-US_TOPIC_0000001052218252"></a>

This example describes how to use I2C APIs by using an I2C device on a development board.

This example shows a simple register read/write operation on TouchPad on a Hi3516D V300 development board. The basic hardware information is as follows:

-   SoC: hi3516dv300

-   Touch IC: The I2C address is 0x38, and the bit width of Touch IC's internal register is 1 byte.

-   Schematic diagram: TouchPad is mounted to I2C controller 3. The reset pin of Touch IC is GPIO3.

In this example, first we reset Touch IC. \(The development board supplies power to Touch IC by default after being powered on, and this use case does not consider the power supply\). Then, we perform a read/wirte operation on an internal register to test whether the I2C channel is normal.

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>The example focuses on I2C device access and verifies the I2C channel. The read and write values of the device register are not concerned. The behavior caused by the read and write operations on the register is determined by the device itself.

Example:

```
#include "i2c_if.h"          /* Header file of I2C APIs */
#include "gpio_if.h"         /* Header file of GPIO APIs */
#include "hdf_log.h"         /* Header file for log APIs */
#include "osal_io.h"         /* Header file of I/O read and write APIs */
#include "osal_time.h"       /* Header file of delay and sleep APIs */

/* Define a TP device structure to store I2C and GPIO hardware information. */
struct TpI2cDevice {
    uint16_t rstGpio;             /* Reset pin */
    uint16_t busId;               /* I2C bus ID */
    uint16_t addr;                /* I2C device address */
    uint16_t regLen;              /* Register bit width */
    struct DevHandle *i2cHandle;  /* I2C controller handle */
};

/* I2C pin I/O configuration. For details, see the SoC register manual. */
#define I2C3_DATA_REG_ADDR 0x112f008c /* Address of the SDA pin configuration register of I2C controller 3
#define I2C3_CLK_REG_ADDR 0x112f0090 /* Address of the SCL pin configuration register of I2C controller 3
#define I2C_REG_CFG 0x5f1             /* Configuration values of SDA and SCL pins of I2C controller 3

static void TpSocIoCfg(void)
{
    /* Set the I/O function of the two pins corresponding to I2C controller 3 to I2C. */
    OSAL_WRITEL(I2C_REG_CFG, IO_DEVICE_ADDR(I2C3_DATA_REG_ADDR));
    OSAL_WRITEL(I2C_REG_CFG, IO_DEVICE_ADDR(I2C3_CLK_REG_ADDR));
}

/* Initialize the reset pin of the TP. Pull up the pin for 20 ms, pull down the pin for 50 ms, and then pull up the pin for 20s to complete the resetting. */
static int32_t TestCaseGpioInit(struct TpI2cDevice *tpDevice)
{
    int32_t ret;

    /* Set the output direction for the reset pin. */
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

/* Use I2cTransfer to encapsulate a register read/write auxiliary function. Use flag to indicate the read or write operation. */
static int TpI2cReadWrite(struct TpI2cDevice *tpDevice, unsigned int regAddr,
    unsigned char *regData, unsigned int dataLen, uint8_t flag)
{
    int index = 0;
    unsigned char regBuf[4] = {0};
    struct I2cMsg msgs[2] = {0};

    /* Perform length adaptation for the single- or dual-byte register. */
    if (tpDevice->regLen == 1) { 
        regBuf[index++] = regAddr & 0xFF;
    } else {
        regBuf[index++] = (regAddr >> 8) & 0xFF;
        regBuf[index++] = regAddr & 0xFF;
    }

    /* Fill in the I2cMsg message structure. */
    msgs[0].addr = tpDevice->addr;
    msgs[0].flags = 0; /* The flag is 0, indicating the write operation. */
    msgs[0].len = tpDevice->regLen;
    msgs[0].buf = regBuf;

    msgs[1].addr = tpDevice->addr;
    msgs[1].flags = (flag == 1)? I2C_FLAG_READ: 0; /* Add the read flag. */
    msgs[1].len = dataLen;
    msgs[1].buf = regData;

    if (I2cTransfer(tpDevice->i2cHandle, msgs, 2) != 2) {
        HDF_LOGE("%s: i2c read err", __func__);
        return HDF_FAILURE;
    }
    return HDF_SUCCESS;
}

/* TP register read function */
static inline int TpI2cReadReg(struct TpI2cDevice *tpDevice, unsigned int regAddr,
    unsigned char *regData, unsigned int dataLen)
{
    return TpI2cReadWrite(tpDevice, regAddr, regData, dataLen, 1);
}

/* TP register write function */
static inline int TpI2cWriteReg(struct TpI2cDevice *tpDevice, unsigned int regAddr,
    unsigned char *regData, unsigned int dataLen)
{
    return TpI2cReadWrite(tpDevice, regAddr, regData, dataLen, 0);
}

/* Main entry of I2C */
static int32_t TestCaseI2c(void)
{
    int32_t i;
    int32_t ret;
    unsigned char bufWrite[7] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xA, 0xB, 0xC };
    unsigned char bufRead[7] = {0};
    static struct TpI2cDevice tpDevice;

    /* I/O pin function configuration */
    TpSocIoCfg();

    /* Initialize TP device information. */
    tpDevice.rstGpio = 3;
    tpDevice.busId = 3;
    tpDevice.addr = 0x38;
    tpDevice.regLen = 1;
    tpDevice.i2cHandle = NULL;

    /* Initialize the GPIO pin. */
    ret = TestCaseGpioInit(&tpDevice);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: gpio init fail!:%d", __func__, ret);
        return ret;
    }

    /* Open an I2C controller. */
    tpDevice.i2cHandle = I2cOpen(tpDevice.busId);
    if (tpDevice.i2cHandle == NULL) {
        HDF_LOGE("%s: Open I2c:%u fail!", __func__, tpDevice.busId);
        return -1;
    }

    /* Continuously write 7-byte data to register 0xD5 of TP-IC. */
    ret = TpI2cWriteReg(&tpDevice, 0xD5, bufWrite, 7);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s: tp i2c write reg fail!:%d", __func__, ret);
        I2cClose(tpDevice.i2cHandle);
        return -1;
    }
    OsalMSleep(10);

    /* Continuously read 7-byte data from register 0xDO of TP-IC. */
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

    /* Close the I2C controller. */
    I2cClose(tpDevice.i2cHandle);
    return ret;
}
```

