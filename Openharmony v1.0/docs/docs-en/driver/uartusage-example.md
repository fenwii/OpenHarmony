# UART Usage Example<a name="EN-US_TOPIC_0000001051619004"></a>

The following is a usage example of a UART device, including how to obtain the UART device handle, set the baud rate, device attributes, and transmission mode, read data from or write data into the UART device, and then destroy the UART device handle.

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
    attribute.dataBits = UART_ATTR_DATABIT_7;   /* Set the number of data bits to 7. */
    attribute.parity = UART_ATTR_PARITY_NONE;   /* Set the parity bit to no parity. */
    attribute.stopBits = UART_ATTR_STOPBIT_1;   /* Set the stop bit to 1. */
    attribute.rts = UART_ATTR_RTS_DIS;          /* Disable the RTS signal. */
    attribute.cts = UART_ATTR_CTS_DIS;          /* Disable the CTS signal. */
    attribute.fifoRxEn = UART_ATTR_RX_FIFO_EN;  /* Enable RX FIFO. */
    attribute.fifoTxEn = UART_ATTR_TX_FIFO_EN;  /* Enable TX FIFO. */
    /* Set the UART port number actually used. */
    port = 1; 
    /* Obtain the UART device handle. */
    handle = UartOpen(port);
    if (handle == NULL) {
        HDF_LOGE("UartOpen: failed!\n");
        return;
    }
    /* Set the UART baud rate to 9600. */
    ret = UartSetBaud(handle, 9600);
    if (ret != 0) {
        HDF_LOGE("UartSetBaud: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* Set the UART device attributes. */
    ret = UartSetAttribute(handle, &attribute);
    if (ret != 0) {
        HDF_LOGE("UartSetAttribute: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* Set the UART transmission mode to non-blocking mode. */
    ret = UartSetTransMode(handle, UART_MODE_RD_NONBLOCK);
    if (ret != 0) {
        HDF_LOGE("UartSetTransMode: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* Write 5-byte data into the UART device. */
    ret = UartWrite(handle, wbuff, 5);
    if (ret != 0) {
        HDF_LOGE("UartWrite: failed, ret %d\n", ret);
        goto _ERR;
    }
    /* Read 5-byte data from the UART device. */
    ret = UartRead(handle, rbuff, 5);
    if (ret < 0) {
        HDF_LOGE("UartRead: failed, ret %d\n", ret);
        goto _ERR;
    }
_ERR:
    /* Destroy the UART device handle. */
    UartClose(handle); 
}
```

