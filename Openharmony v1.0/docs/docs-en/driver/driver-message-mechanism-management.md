# Driver Message Mechanism Management<a name="EN-US_TOPIC_0000001052657065"></a>

## When to Use<a name="section33014541954"></a>

When user-level applications need to interact with kernel-level drivers, the driver message mechanism of the HDF can be used.

## Available APIs<a name="section538852311616"></a>

The message mechanism provides the following features:

1.  User-level applications send messages to drivers.
2.  User-level applications receive events sent by the drivers.

**Table  1**  APIs for the driver message mechanism

<a name="table208212674114"></a>
<table><thead align="left"><tr id="row08282618416"><th class="cellrowborder" valign="top" width="46.379999999999995%" id="mcps1.2.3.1.1"><p id="p382132664112"><a name="p382132664112"></a><a name="p382132664112"></a><strong id="b142817619332"><a name="b142817619332"></a><a name="b142817619332"></a>Function</strong></p>
</th>
<th class="cellrowborder" valign="top" width="53.620000000000005%" id="mcps1.2.3.1.2"><p id="p4826264419"><a name="p4826264419"></a><a name="p4826264419"></a><strong id="b201539486743916"><a name="b201539486743916"></a><a name="b201539486743916"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1582426174114"><td class="cellrowborder" valign="top" width="46.379999999999995%" headers="mcps1.2.3.1.1 "><p id="p182341916144420"><a name="p182341916144420"></a><a name="p182341916144420"></a>struct HdfIoService *HdfIoServiceBind(const char *serviceName, mode_t permission)</p>
</td>
<td class="cellrowborder" valign="top" width="53.620000000000005%" headers="mcps1.2.3.1.2 "><p id="p58272614113"><a name="p58272614113"></a><a name="p58272614113"></a>Obtains a specified driver service. After the service is obtained, the <strong id="b9799159433"><a name="b9799159433"></a><a name="b9799159433"></a>Dispatch</strong> function of the service is used to send messages to the driver.</p>
</td>
</tr>
<tr id="row578565084913"><td class="cellrowborder" valign="top" width="46.379999999999995%" headers="mcps1.2.3.1.1 "><p id="p15786185024918"><a name="p15786185024918"></a><a name="p15786185024918"></a>void HdfIoServiceRecycle(struct HdfIoService *service);</p>
</td>
<td class="cellrowborder" valign="top" width="53.620000000000005%" headers="mcps1.2.3.1.2 "><p id="p47861750154912"><a name="p47861750154912"></a><a name="p47861750154912"></a>Releases a specified driver service.</p>
</td>
</tr>
<tr id="row1382112617413"><td class="cellrowborder" valign="top" width="46.379999999999995%" headers="mcps1.2.3.1.1 "><p id="p482182611415"><a name="p482182611415"></a><a name="p482182611415"></a>int HdfDeviceRegisterEventListener(struct HdfIoService *target, struct HdfDevEventlistener *listener);</p>
</td>
<td class="cellrowborder" valign="top" width="53.620000000000005%" headers="mcps1.2.3.1.2 "><p id="p18825261412"><a name="p18825261412"></a><a name="p18825261412"></a>Receives events sent by the drivers.</p>
</td>
</tr>
<tr id="row498956124019"><td class="cellrowborder" valign="top" width="46.379999999999995%" headers="mcps1.2.3.1.1 "><p id="p6412911184019"><a name="p6412911184019"></a><a name="p6412911184019"></a>int HdfDeviceSendEvent(struct HdfDeviceObject *deviceObject, uint32_t id, struct HdfSBuf *data);</p>
</td>
<td class="cellrowborder" valign="top" width="53.620000000000005%" headers="mcps1.2.3.1.2 "><p id="p1698915634018"><a name="p1698915634018"></a><a name="p1698915634018"></a>Sends events.</p>
</td>
</tr>
</tbody>
</table>

## How to Develop<a name="section946912121153"></a>

1.  Set the value of the  **policy**  field in the driver configuration information to  **2**  \(SERVICE\_POLICY\_CAPACITY, see  [Driver Service Management](driver-service-management.md)\).

    ```
    device_sample :: Device {
        policy = 2;
        ...
    }
    ```

2.  The  **permission**  field in the driver configuration information indicates the permission provided for the driver to create device nodes. The default value is  **0666**. You can configure the value of this field based on the actual application scenario of the driver.
3.  Implement the  **Dispatch**  function of the service base member  **IDeviceIoService**  during service implementation.

    ```
    // Process messages delivered by user-level applications.
    int32_t SampleDriverDispatch(struct HdfDeviceObject *device, int cmdCode, struct HdfSBuf *data, struct HdfSBuf *reply)
    {
        HDF_LOGE("sample driver lite A dispatch");
        return 0;
    }
    int32_t SampleDriverBind(struct HdfDeviceObject *device)
    {
        HDF_LOGE("test for lite os sample driver A Open!");
        if (device == NULL) {
            HDF_LOGE("test for lite os sample driver A Open failed!");
            return -1;
        }
        static struct ISampleDriverService sampleDriverA = {
            .ioService.Dispatch = SampleDriverDispatch,
            .ServiceA = SampleDriverServiceA,
            .ServiceB = SampleDriverServiceB,
        };
        device->service = (struct IDeviceIoService *)(&sampleDriverA);
        return 0;
    }
    ```

4.  Define the CMD type in the message processing function.

    ```
    #define SAMPLE_WRITE_READ 1    // Read and write operation 1
    ```

5.  Enable the user-level application to obtain the service interface and send messages to the driver.

    ```
    int SendMsg(const char *testMsg)
    {
        if (testMsg == NULL) {
            HDF_LOGE("test msg is null");
            return -1;
        }
        struct HdfIoService *serv = HdfIoServiceBind("sample_driver", 0);
        if (serv == NULL) {
            HDF_LOGE("fail to get service");
            return -1;
        }
        struct HdfSBuf *data = HdfSBufObtainDefaultSize();
        if (data == NULL) {
            HDF_LOGE("fail to obtain sbuf data");
            return -1;
        }
        struct HdfSBuf *reply = HdfSBufObtainDefaultSize();
        if (reply == NULL) {
            HDF_LOGE("fail to obtain sbuf reply");
            ret = HDF_DEV_ERR_NO_MEMORY;
            goto out;
        }
        if (!HdfSbufWriteString(data, testMsg)) {
            HDF_LOGE("fail to write sbuf");
            ret = HDF_FAILURE;
            goto out;
        }
        int ret = serv->dispatcher->Dispatch(&serv->object, SAMPLE_WRITE_READ, data, reply);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("fail to send service call");
            goto out;
        }
    out:
        HdfSBufRecycle(data);
        HdfSBufRecycle(reply);
        HdfIoServiceRecycle(serv);
        return ret;
    }
    ```

6.  Enable the user-level application to receive messages reported by the driver.
    1.  Enable the user-level application to compile the function for processing messages reported by the driver.

        ```
        static int OnDevEventReceived(void *priv,  uint32_t id, struct HdfSBuf *data)
        {
            OsalTimespec time;
            OsalGetTime(&time);
            HDF_LOGE("%s received event at %llu.%llu", (char *)priv, time.sec, time.usec);
        
            const char *string = HdfSbufReadString(data);
            if (string == NULL) {
                HDF_LOGE("fail to read string in event data");
                return -1;
            }
            HDF_LOGE("%s: dev event received: %d %s",  (char *)priv, id, string);
            return 0;
        }
        ```

    2.  Enable the user-level application to register the function for receiving messages reported by the driver.

        ```
        int RegisterListen()
        {
            struct HdfIoService *serv = HdfIoServiceBind("sample_driver", 0);
            if (serv == NULL) {
                HDF_LOGE("fail to get service");
                return -1;
            }
            static struct HdfDevEventlistener listener = {
                .callBack = OnDevEventReceived,
                .priv ="Service0"
            };
            if (HdfDeviceRegisterEventListener(serv, &listener) != 0) {
                HDF_LOGE("fail to register event listener");
                return -1;
            }
            ......
            HdfDeviceUnregisterEventListener(serv, &listener);
            HdfIoServiceRecycle(serv);
            return 0;
        }
        ```

    3.  Enable the driver to report events.

        ```
        int32_t SampleDriverDispatch(struct HdfDeviceObject *device, int cmdCode, struct HdfSBuf *data, struct HdfSBuf *reply)
        {
            ... // process api call here
            return HdfDeviceSendEvent(deviceObject, cmdCode, data);
        }
        ```



