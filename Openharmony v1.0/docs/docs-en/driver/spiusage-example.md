# SPI Usage Example<a name="EN-US_TOPIC_0000001052459271"></a>

The following is a usage example of an SPI device, including how to obtain an SPI device handle, set the configuration parameters, and then read or write data from or into the SPI device, and finally destroy the SPI device handle.

```
#include "hdf_log.h"
#include "spi_if.h"

void SpiTestSample(void)
{
    int32_t ret;
    struct SpiCfg cfg;                  /* SPI device configuration information */
    struct SpiDevInfo spiDevinfo;       /* SPI device descriptor */
    struct DevHandle *spiHandle = NULL; /* SPI device handle */
    struct SpiMsg msg;                  /* Custom message to be transferred */
    uint8_t rbuff[4] = { 0 };
    uint8_t wbuff[4] = { 0x12, 0x34, 0x56, 0x78 };
    uint8_t wbuff2[4] = { 0xa1, 0xb2, 0xc3, 0xd4 };

    spiDevinfo.busNum = 0;              /* SPI device bus number */
    spiDevinfo.csNum = 0;               /* SPI device CS number */
    spiHandle = SpiOpen(&spiDevinfo);   /* Obtain an SPI device handle based on spiDevinfo. */
    if (spiHandle == NULL) {
        HDF_LOGE("SpiOpen: failed\n");
        return;
    }
    /* Obtain configuration parameters of an SPI device. */
    ret = SpiGetCfg(spiHandle, &cfg);
    if (ret != 0) {
        HDF_LOGE("SpiGetCfg: failed, ret %d\n", ret);
        goto err;
    }
    cfg.maxSpeedHz = 115200;                /* Change the maximum clock frequency to 115200. */
    cfg.bitsPerWord = 8;                    /* Change the word width to 8 bits. */
    /* Set configuration parameters for an SPI device. */
    ret = SpiSetCfg(spiHandle, &cfg);
    if (ret != 0) {
        HDF_LOGE("SpiSetCfg: failed, ret %d\n", ret);
        goto err;
    }
    /* Write specified length of data into an SPI device. */
    ret = SpiWrite(spiHandle, wbuff, 4);
    if (ret != 0) {
        HDF_LOGE("SpiWrite: failed, ret %d\n", ret);
        goto err;
    }
    /* Read data of a specified length from an SPI device. */
    ret = SpiRead(spiHandle, rbuff, 4);
    if (ret != 0) {
        HDF_LOGE("SpiRead: failed, ret %d\n", ret);
        goto err;
    }
    msg.wbuf = wbuff2;  /* Pointer to the data to write */
    msg.rbuf = rbuff;   /* Pointer to the data to read */
    msg.len = 4;        /* The length of the data to be read or written is 4 bits. */
    msg.csChange = 1;   /* Disable the CS before the next transfer. */
    msg.delayUs = 0;    /* No delay before the next transfer */
    msg.speed = 115200; /* Speed of this transfer */
    /* Launch a custom transfer. The number of messages to be transferred is 1. */
    ret = SpiTransfer(spiHandle, &msg, 1);
    if (ret != 0) {
        HDF_LOGE("SpiTransfer: failed, ret %d\n", ret);
        goto err;
    }
err:
    /* Destroy the SPI device handle. */
    SpiClose(spiHandle);
}
```

