# UART使用实例<a name="ZH-CN_TOPIC_0000001051619004"></a>

UART设备完整的使用示例如下所示，首先获取UART设备句柄，接着设置波特率、设备属性和传输模式，之后进行UART通信，最后销毁UART设备句柄。

```
#include "hdf_log.h"
#include "uart_if.h"

void UartTestSample(void)
{
    int32_t ret;
    uint32_t port;  
    struct DevHandle *handle = NULL;
    uint8_t wbuff[5] = { 1, 2, 3, 4, 5 };
    uint8_t rbuff[5] = { 0 };
    struct UartAttribute attribute;
    attribute.dataBits = UART_ATTR_DATABIT_7;   /* UART传输数据位宽，一次传输7个bit */
    attribute.parity = UART_ATTR_PARITY_NONE;   /* UART传输数据无校检 */
    attribute.stopBits = UART_ATTR_STOPBIT_1;   /* UART传输数据停止位为1位 */
    attribute.rts = UART_ATTR_RTS_DIS;          /* UART禁用RTS */
    attribute.cts = UART_ATTR_CTS_DIS;          /* UART禁用CTS */
    attribute.fifoRxEn = UART_ATTR_RX_FIFO_EN;  /* UART使能RX FIFO */
    attribute.fifoTxEn = UART_ATTR_TX_FIFO_EN;  /* UART使能TX FIFO */
    /* UART设备端口号，要填写实际平台上的端口号 */
    port = 1; 
    /* 获取UART设备句柄 */
    handle = UartOpen(port);
    if (handle == NULL) {
        HDF_LOGE("UartOpen: failed!\n");
        return;
    }
    /* 设置UART波特率为9600 */
    ret = UartSetBaud(handle, 9600);
    if (ret != 0) {
        HDF_LOGE("UartSetBaud: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* 设置UART设备属性 */
    ret = UartSetAttribute(handle, &attribute);
    if (ret != 0) {
        HDF_LOGE("UartSetAttribute: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* 设置UART传输模式为非阻塞模式 */
    ret = UartSetTransMode(handle, UART_MODE_RD_NONBLOCK);
    if (ret != 0) {
        HDF_LOGE("UartSetTransMode: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* 向UART设备写入5字节的数据 */
    ret = UartWrite(handle, wbuff, 5);
    if (ret != 0) {
        HDF_LOGE("UartWrite: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* 从UART设备读取5字节的数据 */
    ret = UartRead(handle, rbuff, 5);
    if (ret < 0) {
        HDF_LOGE("UartRead: failed, ret %d\n", ret);
        goto _ERR;
    }
_ERR:
    /* 销毁UART设备句柄 */
    UartClose(handle); 
}
```

