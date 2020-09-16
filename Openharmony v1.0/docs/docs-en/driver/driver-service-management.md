# Driver Service Management<a name="EN-US_TOPIC_0000001052777057"></a>

Driver services are objects of open capabilities provided by the HDF and are managed by the HDF in a unified manner. Using driver service management, you can release and obtain driver services.

The HDF uses the  **policy**  field in the configuration file to define policies for drivers to release services externally. The values and meanings of this field are as follows:

```
typedef enum {
    /* The driver does not provide services. */
    SERVICE_POLICY_NONE = 0,
    /* The driver provides services for kernel-level applications. */
    SERVICE_POLICY_PUBLIC = 1,
    /* The driver provides services for both kernel- and user-level applications. */
    SERVICE_POLICY_CAPACITY = 2,
    /* The driver services are not released externally but can be subscribed to. */
    SERVICE_POLICY_FRIENDLY = 3,
    /* The driver services are private. They are neither released nor subscribed to. */
    SERVICE_POLICY_PRIVATE = 4,
    /* The service policy is incorrect. */
    SERVICE_POLICY_INVALID
} ServicePolicy;
```

## When to Use<a name="section14244270117"></a>

The driver service management capability can be used if the driver provides capabilities using APIs.

## Available APIs<a name="section1432412561722"></a>

The table below describes the APIs used for driver service management.

**Table  1**  APIs for driver service management

<a name="table82191668111"></a>
<table><thead align="left"><tr id="row132193618114"><th class="cellrowborder" valign="top" width="53.269999999999996%" id="mcps1.2.3.1.1"><p id="p18219061815"><a name="p18219061815"></a><a name="p18219061815"></a><strong id="b12478202911367"><a name="b12478202911367"></a><a name="b12478202911367"></a>Function</strong></p>
</th>
<th class="cellrowborder" valign="top" width="46.73%" id="mcps1.2.3.1.2"><p id="p22191466118"><a name="p22191466118"></a><a name="p22191466118"></a><strong id="b134538148443950"><a name="b134538148443950"></a><a name="b134538148443950"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row72198616119"><td class="cellrowborder" valign="top" width="53.269999999999996%" headers="mcps1.2.3.1.1 "><p id="p1894101717213"><a name="p1894101717213"></a><a name="p1894101717213"></a>int32_t (*Bind)(struct HdfDeviceObject *deviceObject);</p>
</td>
<td class="cellrowborder" valign="top" width="46.73%" headers="mcps1.2.3.1.2 "><p id="p15219864113"><a name="p15219864113"></a><a name="p15219864113"></a>Binds a service interface to the HDF. You need to implement the <strong id="b876584084419"><a name="b876584084419"></a><a name="b876584084419"></a>Bind</strong> function.</p>
</td>
</tr>
<tr id="row1821946716"><td class="cellrowborder" valign="top" width="53.269999999999996%" headers="mcps1.2.3.1.1 "><p id="p122191462017"><a name="p122191462017"></a><a name="p122191462017"></a>const struct HdfObject *DevSvcManagerClntGetService(const char *svcName);</p>
</td>
<td class="cellrowborder" valign="top" width="46.73%" headers="mcps1.2.3.1.2 "><p id="p92191766118"><a name="p92191766118"></a><a name="p92191766118"></a>Obtains a specified driver service.</p>
</td>
</tr>
<tr id="row630114414319"><td class="cellrowborder" valign="top" width="53.269999999999996%" headers="mcps1.2.3.1.1 "><p id="p340513438313"><a name="p340513438313"></a><a name="p340513438313"></a>int HdfDeviceSubscribeService(</p>
<p id="p1940512431634"><a name="p1940512431634"></a><a name="p1940512431634"></a>struct HdfDeviceObject *deviceObject, const char *serviceName, struct SubscriberCallback callback);</p>
</td>
<td class="cellrowborder" valign="top" width="46.73%" headers="mcps1.2.3.1.2 "><p id="p230154120317"><a name="p230154120317"></a><a name="p230154120317"></a>Subscribes to a specified driver service.</p>
</td>
</tr>
</tbody>
</table>

## How to Develop<a name="section393515164416"></a>

The development of driver service management includes compiling, binding, obtaining, and subscribing to driver services. The details are as follows:

1.  Release a driver service.

    ```
    Define the driver service structure.
    struct ISampleDriverService {
        struct IDeviceIoService ioService;   // The first member of the service structure must be a member of the IDeviceIoService type.
        int32_t (*ServiceA)(void);               // The first service interface of the driver.
        int32_t (*ServiceB)(uint32_t inputCode); // The second service interface of the driver. The rest can be deduced by analogy.
    };
    
    Implementation of the driver service interface
    int32_t SampleDriverServiceA(void)
    {
        // You need to implement the service logic.
        return 0;
    }
    
    int32_t SampleDriverServiceB(uint32_t inputCode)
    {
        // You need to implement the service logic.
        return 0;
    }
    ```

2.  Bind the driver service to the HDF and implement the  **Bind**  function in the  **HdfDriverEntry**  structure.

    ```
    int32_t SampleDriverBind(struct HdfDeviceObject *deviceObject)
    {
        // deviceObject indicates the pointer to the device object created by the HDF for each driver. It is used to store device-related private data and service interfaces.
        if (deviceObject== NULL) {
            HDF_LOGE("Sample device object is null!");
            return -1;
        }
        static struct ISampleDriverService sampleDriverA = {
            .ServiceA = SampleDriverServiceA,
            .ServiceB = SampleDriverServiceB,
        };
        deviceObject->service = &sampleDriverA.ioService;
        return 0;
    }
    ```

3.  Obtain the driver service.

    You can either use the API or subscription mechanism provided by the HDF to obtain the driver service.

    -   Using the API

        After the driver is loaded, you can obtain the driver service using the API provided by the HDF, as shown in the following:

        ```
        const struct ISampleDriverService *sampleService =
                (const struct ISampleDriverService *)DevSvcManagerClntGetService("sample_driver");
        if (sampleService == NULL) {
            return -1;
        }
        sampleService->ServiceA();
        sampleService->ServiceB(5);
        ```

    -   Using the subscription mechanism

        If you are unaware of the time for loading drivers \(on the same host\), use the subscription mechanism provided by the HDF to subscribe to the drivers. After the drivers are loaded, the HDF releases the driver services to you. The implementation is as follows:

        ```
        // Subscription callback function. After the subscribed drivers are loaded, the HDF releases the driver services to you using this function.
        // object indicates the pointer to the private data of the subscriber, and service indicates the pointer to the subscribed service.
        int32_t TestDriverSubCallBack(struct HdfDeviceObject *deviceObject, const struct HdfObject *service)
        {
            const struct ISampleDriverService *sampleService =
                (const struct ISampleDriverService *)service;
            if (sampleService == NULL) {
                return -1;
            }
            sampleService->ServiceA();
            sampleService->ServiceB(5);
        }
        // Implements the subscription process.
        int32_t TestDriverInit(struct HdfDeviceObject *deviceObject)
        {
            if (deviceObject== NULL) {
                HDF_LOGE("Test driver init failed, deviceObject is null!");
                return -1;
            }
            struct SubscriberCallback callBack;
            callBack.deviceObject = deviceObject;
            callBack.OnServiceConnected = TestDriverSubCallBack;
            int32_t ret = HdfDeviceSubscribeService(deviceObject, "sample_driver", callBack);
            if (ret != 0) {
                HDF_LOGE("Test driver subscribe sample driver failed!");
            }
            return ret;
        }
        ```



