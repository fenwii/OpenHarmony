# SDIO Usage Example<a name="EN-US_TOPIC_0000001052858034"></a>

The following example shows how to use an SDIO device. First, open an SDIO controller whose bus number is 1, exclusively claim a host, enable the SDIO device, claim an SDIO IRQ, and then perform SDIO communication \(such as reading and writing\). After the SDIO communication, release the SDIO IRQ, disable the SDIO device, release the host, and close the SDIO controller.

```
#include "hdf_log.h"
#include "sdio_if.h"

#define TEST_FUNC_NUM 1 /* The I/O function whose ID is 1 is used. */
#define TEST_FBR_BASE_ADDR 0x100 /* FBR base address of the I/O function whose ID is 1 */
#define TEST_ADDR_OFFSET 9 /* Address offset of the register to read or write */
#define TEST_DATA_LEN 3 /* Length of the data to read or write */
#define TEST_BLOCKSIZE 2 /* Size of a data block, in bytes */

/* Implement the SDIO IRQ function based on the application. */
static void SdioIrqFunc(void *data)
{
    if (data == NULL) {
        HDF_LOGE("SdioIrqFunc: data is NULL.\n");
        return;
    }
    /* You need to add specific implementations. */
}

void SdioTestSample(void)
{
    int32_t ret;  
    struct DevHandle *handle = NULL;
    uint8_t data[TEST_DATA_LEN] = {0};
    int16_t busNum = 1;
    uint8_t val;
    uint32_t addr;
    
    /* Open an SDIO controller whose bus number is 1. */
    handle = SdioOpen(busNum);
    if (handle == NULL) {
        HDF_LOGE("SdioOpen: failed!\n");
        return;
    }
   /* Claim a host exclusively. */
    SdioClaimHost(handle);
   /* Enable the SDIO device. */
    ret = SdioEnableFunc(handle);
    if (ret != 0) {
        HDF_LOGE("SdioEnableFunc: failed, ret %d\n", ret);
        goto ENABLE_ERR;
    }
   /* Claim an SDIO IRQ. */
    ret = SdioClaimIrq(handle, SdioIrqFunc);
    if (ret != 0) {
        HDF_LOGE("SdioClaimIrq: failed, ret %d\n", ret);
        goto CLAIM_IRQ_ERR;
    }
    /* Set the block size to 2 bytes. */
    ret = SdioSetBlockSize(handle, TEST_BLOCKSIZE);
    if (ret != 0) {
        HDF_LOGE("SdioSetBlockSize: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Read 3-byte data from the incremental address of an SDIO device. */
    addr = TEST_FBR_BASE_ADDR * TEST_FUNC_NUM + TEST_ADDR_OFFSET;
    ret = SdioReadBytes(handle, data, addr, TEST_DATA_LEN, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Write 3-byte data into the incremental address of an SDIO device. */
    ret = SdioWriteBytes(handle, data, addr, TEST_DATA_LEN, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Read 1-byte data from the SDIO device. */
    ret = SdioReadBytes(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Write 1-byte data into the SDIO device. */
    ret = SdioWriteBytes(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytes: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Read 3-byte data from the fixed address of an SDIO device. */
    ret = SdioReadBytesFromFixedAddr(handle, data, addr, TEST_DATA_LEN, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytesFromFixedAddr: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Write 1-byte data to the fixed address of an SDIO device. */
    ret = SdioWriteBytesToFixedAddr(handle, data, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytesToFixedAddr: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Read 1-byte data from SDIO function 0. */
    addr = 0x02;
    ret = SdioReadBytesFromFunc0(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioReadBytesFromFunc0: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
    /* Write 1-byte data into SDIO function 0. */
    ret = SdioWriteBytesToFunc0(handle, &val, addr, 1, 0);
    if (ret != 0) {
        HDF_LOGE("SdioWriteBytesToFunc0: failed, ret %d\n", ret);
        goto COMM_ERR;
    }
COMM_ERR:
    /* Release the SDIO IRQ. */
    ret = SdioReleaseIrq(handle);
    if (ret != 0) {
        HDF_LOGE("SdioReleaseIrq: failed, ret %d\n", ret);
    }
CLAIM_IRQ_ERR:
    /* Disable the SDIO device. */
    ret = SdioDisableFunc(handle);
    if (ret != 0) {
        HDF_LOGE("SdioDisableFunc: failed, ret %d\n", ret);
    }
ENABLE_ERR:
    /* Release the exclusively claimed host. */
    SdioReleaseHost(handle);
    /* Close an SDIO controller. */
    SdioClose(handle); 
}
```

