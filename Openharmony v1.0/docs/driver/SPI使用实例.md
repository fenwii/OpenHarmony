# SPI使用实例<a name="ZH-CN_TOPIC_0000001052459271"></a>

SPI设备完整的使用示例如下所示，首先获取SPI设备句柄，然后配置SPI设备属性，接着调用读写接口进行数据传输，最后销毁SPI设备句柄。

```
#include "hdf_log.h"
#include "spi_if.h"

void SpiTestSample(void)
{
    int32_t ret;
    struct SpiCfg cfg;                  /* SPI配置信息 */
    struct SpiDevInfo spiDevinfo;       /* SPI设备描述符 */
    struct DevHandle *spiHandle = NULL; /* SPI设备句柄 */
    struct SpiMsg msg;                  /* 自定义传输的消息 */
    uint8_t rbuff[4] = { 0 };
    uint8_t wbuff[4] = { 0x12, 0x34, 0x56, 0x78 };
    uint8_t wbuff2[4] = { 0xa1, 0xb2, 0xc3, 0xd4 };

    spiDevinfo.busNum = 0;              /* SPI设备总线号 */
    spiDevinfo.csNum = 0;               /* SPI设备片选号 */
    spiHandle = SpiOpen(&spiDevinfo);   /* 根据spiDevinfo获取SPI设备句柄 */
    if (spiHandle == NULL) {
        HDF_LOGE("SpiOpen: failed\n");
        return;
    }
    /* 获取SPI设备属性 */
    ret = SpiGetCfg(spiHandle, &cfg);
    if (ret != 0) {
        HDF_LOGE("SpiGetCfg: failed, ret %d\n", ret);
        goto err;
    }
    cfg.maxSpeedHz = 115200;                /* 将最大时钟频率改为115200 */
    cfg.bitsPerWord = 8;                    /* 传输位宽改为8比特 */
    /* 配置SPI设备属性 */
    ret = SpiSetCfg(spiHandle, &cfg);
    if (ret != 0) {
        HDF_LOGE("SpiSetCfg: failed, ret %d\n", ret);
        goto err;
    }
    /* 向SPI设备写入指定长度的数据 */
    ret = SpiWrite(spiHandle, wbuff, 4);
    if (ret != 0) {
        HDF_LOGE("SpiWrite: failed, ret %d\n", ret);
        goto err;
    }
    /* 从SPI设备读取指定长度的数据 */
    ret = SpiRead(spiHandle, rbuff, 4);
    if (ret != 0) {
        HDF_LOGE("SpiRead: failed, ret %d\n", ret);
        goto err;
    }
    msg.wbuf = wbuff2;  /* 写入的数据 */
    msg.rbuf = rbuff;   /* 读取的数据 */
    msg.len = 4;        /* 读取写入数据的长度为4 */
    msg.csChange = 1;   /* 进行下一次传输前关闭片选 */
    msg.delayUs = 0;    /* 进行下一次传输前不进行延时 */
    msg.speed = 115200; /* 本次传输的速度 */
    /* 进行一次自定义传输，传输的msg个数为1 */
    ret = SpiTransfer(spiHandle, &msg, 1);
    if (ret != 0) {
        HDF_LOGE("SpiTransfer: failed, ret %d\n", ret);
        goto err;
    }
err:
    /* 销毁SPI设备句柄 */
    SpiClose(spiHandle);
}
```

