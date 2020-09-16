# SDIO使用实例<a name="ZH-CN_TOPIC_0000001052858034"></a>

SDIO设备完整的使用示例如下所示，首先打开总线号为1的SDIO控制器，然后独占HOST、使能设备、注册中断，接着进行SDIO通信（读写等），通信完成之后，释放中断、去使能设备、释放HOST，最后关闭SDIO控制器。

```
#include "hdf_log.h"
#include "sdio_if.h"

#define TEST_FUNC_NUM 1              /* 本测试用例中，使用编号为1的I/O function */
#define TEST_FBR_BASE_ADDR 0x100     /* 编号为1的I/O function的FBR基地址 */
#define TEST_ADDR_OFFSET 9           /* 本测试用例中，需要读写的寄存器的地址偏移 */
#define TEST_DATA_LEN 3              /* 本测试用例中，读写数据的长度 */
#define TEST_BLOCKSIZE 2             /* 本测试用例中，数据块的大小，单位字节 */

/* 中断服务函数，需要根据各自平台的情况去实现 */
static void SdioIrqFunc(void *data)
{
    if (data == NULL) {
        HDF_LOGE("SdioIrqFunc: data is NULL.\n");
        return;
    }
    /* 需要开发者自行添加具体的实现 */
}

void SdioTestSample(void)
{
    int32_t ret;  
    struct DevHandle *handle = NULL;
    uint8_t data[TEST_DATA_LEN] = {0};
    int16_t busNum = 1;
    uint8_t val;
    uint32_t addr;
    
    /* 打开总线号为1的SDIO设备 */
    handle = SdioOpen(busNum);
    if (handle == NULL) {
        HDF_LOGE("SdioOpen: failed!\n");
        return;
    }
    /* 独占HOST */
    SdioClaimHost(handle);
    /* 使能SDIO设备 */
    ret = SdioEnableFunc(handle);
    if (ret != 0) {
        HDF_LOGE("SdioEnableFunc: failed, ret %d\n", ret);
        goto ENABLE_ERR;
    }
    /* 注册中断 */
    ret = SdioClaimIrq(handle, SdioIrqFunc);
    if (ret != 0) {
        HDF_LOGE("SdioClaimIrq: failed, ret %d\n", ret);
        goto CLAIM_IRQ_ERR;
    }
    /* 设置块大小为2字节 */
    ret = SdioSetBlockSize(handle, TEST_BLOCKSIZE);
    if (ret != 0) {
        HDF_LOGE("SdioSetBlockSize: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 从SDIO设备增量地址读取3字节的数据 */
    addr = TEST_FBR_BASE_ADDR * TEST_FUNC_NUM + TEST_ADDR_OFFSET;
    ret = SdioReadBytes(handle, data, addr, TEST_DATA_LEN, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 向SDIO设备增量地址写入3字节的数据 */
    ret = SdioWriteBytes(handle, data, addr, TEST_DATA_LEN, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 从SDIO设备读取1字节的数据 */
    ret = SdioReadBytes(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 向SDIO设备写入1字节的数据 */
    ret = SdioWriteBytes(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 从SDIO设备固定地址读取3字节的数据 */
    ret = SdioReadBytesFromFixedAddr(handle, data, addr, TEST_DATA_LEN, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytesFromFixedAddr: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 向SDIO设备固定地址写入1字节的数据 */
    ret = SdioWriteBytesToFixedAddr(handle, data, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytesToFixedAddr: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 从SDIO function 0读取1字节的数据 */
    addr = 0x02;
    ret = SdioReadBytesFromFunc0(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytesFromFunc0: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* 向SDIO function 0写入1字节的数据 */
    ret = SdioWriteBytesToFunc0(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytesToFunc0: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
COMM_ERR:
    /* 释放中断 */
    ret = SdioReleaseIrq(handle);
    if (ret != 0) {
        HDF_LOGE("SdioReleaseIrq: failed, ret %d\n", ret);
    }
CLAIM_IRQ_ERR:
    /* 去使能SDIO设备 */
    ret = SdioDisableFunc(handle);
    if (ret != 0) {
        HDF_LOGE("SdioDisableFunc: failed, ret %d\n", ret);
    }
ENABLE_ERR:
    /* 释放HOST */
    SdioReleaseHost(handle);
    /* 关闭SDIO设备 */
    SdioClose(handle); 
}
```

