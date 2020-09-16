# HDF开发实例<a name="ZH-CN_TOPIC_0000001052451677"></a>

下面基于HDF框架，提供一个完整的样例，包含配置文件的添加，驱动代码的实现以及用户态程序和驱动交互的流程。

## 添加配置<a name="section27261067111"></a>

在HDF框架的配置文件（例如vendor/hisi/hi35xx/hi3516dv300/config/device\_info/device\_info.hcs）中添加该驱动的配置信息，如下所示：

```
root {
    device_info {
        match_attr = "hdf_manager";
        template host {
            hostName = "";
            priority = 100;
            template device {
                template deviceNode {
                    policy = 0;
                    priority = 100;
                    preload = 0;
                    permission = 0664;
                    moduleName = "";
                    serviceName = "";
                    deviceMatchAttr = "";
                }
            }
        }
        sample_host :: host {
            hostName = "sample_host";
            sample_device :: device {
                device0 :: deviceNode {
                    policy = 2;
                    priority = 100;
                    preload = 1;
                    permission = 0664;
                    moduleName = "sample_driver";
                    serviceName = "sample_service";
                }
            }
        }
    }
}
```

## 编写驱动代码<a name="section177988005"></a>

基于HDF框架编写的sample驱动代码如下：

```
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "hdf_log.h"
#include "hdf_base.h"
#include "hdf_device_desc.h"

#define HDF_LOG_TAG sample_driver

#define SAMPLE_WRITE_READ 123

int32_t HdfSampleDriverDispatch(
    struct HdfDeviceObject *deviceObject, int id, struct HdfSBuf *data, struct HdfSBuf *reply)
{
    HDF_LOGE("%s: received cmd %d", __func__, id);
    if (id == SAMPLE_WRITE_READ) {
        const char *readData = HdfSbufReadString(data);
        if (readData != NULL) {
            HDF_LOGE("%s: read data is: %s", __func__, readData);
        }
        if (!HdfSbufWriteInt32(reply, INT32_MAX)) {
            HDF_LOGE("%s: reply int32 fail", __func__);
        }
        return HdfDeviceSendEvent(deviceObject, id, data);
    }
    return HDF_FAILURE;
}

void HdfSampleDriverRelease(struct HdfDeviceObject *deviceObject)
{
    // release resources here
    return;
}

int HdfSampleDriverBind(struct HdfDeviceObject *deviceObject)
{
    if (deviceObject == NULL) {
        return HDF_FAILURE;
    }
    static struct IDeviceIoService testService = {
        .Dispatch = HdfSampleDriverDispatch,
    };
    deviceObject->service = &testService;
    return HDF_SUCCESS;
}

int HdfSampleDriverInit(struct HdfDeviceObject *deviceObject)
{
    if (deviceObject == NULL) {
        HDF_LOGE("%s::ptr is null!", __func__);
        return HDF_FAILURE;
    }
    HDF_LOGE("Sample driver Init success");
    return HDF_SUCCESS;
}

struct HdfDriverEntry g_sampleDriverEntry = {
    .moduleVersion = 1,
    .moduleName = "sample_driver",
    .Bind = HdfSampleDriverBind,
    .Init = HdfSampleDriverInit,
    .Release = HdfSampleDriverRelease,
};

HDF_INIT(g_sampleDriverEntry);
```

## 编写用户程序和驱动交互代码<a name="section6205173816412"></a>

基于HDF框架编写的用户态程序和驱动交互的代码如下：

```
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "hdf_log.h"
#include "hdf_sbuf.h"
#include "hdf_io_service_if.h"

#define HDF_LOG_TAG "sample_test"
#define SAMPLE_SERVICE_NAME "sample_service"

#define SAMPLE_WRITE_READ 123

int g_replyFlag = 0;

static int OnDevEventReceived(void *priv,  uint32_t id, struct HdfSBuf *data)
{
    const char *string = HdfSbufReadString(data);
    if (string == NULL) {
        HDF_LOGE("fail to read string in event data");
        g_replyFlag = 1;
        return HDF_FAILURE;
    }
    HDF_LOGE("%s: dev event received: %u %s",  (char *)priv, id, string);
    g_replyFlag = 1;
    return HDF_SUCCESS;
}

static int SendEvent(struct HdfIoService *serv, char *eventData)
{
    int ret = 0;
    struct HdfSBuf *data = HdfSBufObtainDefaultSize();
    if (data == NULL) {
        HDF_LOGE("fail to obtain sbuf data");
        return 1;
    }

    struct HdfSBuf *reply = HdfSBufObtainDefaultSize();
    if (reply == NULL) {
        HDF_LOGE("fail to obtain sbuf reply");
        ret = HDF_DEV_ERR_NO_MEMORY;
        goto out;
    }

    if (!HdfSbufWriteString(data, eventData)) {
        HDF_LOGE("fail to write sbuf");
        ret = HDF_FAILURE;
        goto out;
    }

    ret = serv->dispatcher->Dispatch(&serv->object, SAMPLE_WRITE_READ, data, reply);
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("fail to send service call");
        goto out;
    }

    int replyData = 0;
    if (!HdfSbufReadInt32(reply, &replyData)) {
        HDF_LOGE("fail to get service call reply");
        ret = HDF_ERR_INVALID_OBJECT;
        goto out;
    }
    HDF_LOGE("Get reply is: %d", replyData);
out:
    HdfSBufRecycle(data);
    HdfSBufRecycle(reply);
    return ret;
}

int main()
{
    char *sendData = "default event info";
    struct HdfIoService *serv = HdfIoServiceBind(SAMPLE_SERVICE_NAME, 0);
    if (serv == NULL) {
        HDF_LOGE("fail to get service %s", SAMPLE_SERVICE_NAME);
        return HDF_FAILURE;
    }

    static struct HdfDevEventlistener listener = {
        .callBack = OnDevEventReceived,
        .priv ="Service0"
    };

    if (HdfDeviceRegisterEventListener(serv, &listener) != HDF_SUCCESS) {
        HDF_LOGE("fail to register event listener");
        return HDF_FAILURE;
    }
    if (SendEvent(serv, sendData)) {
        HDF_LOGE("fail to send event");
        return HDF_FAILURE;
    }

    /* wait for event receive event finishing */
    while (g_replyFlag == 0) {
        sleep(1);
    }

    if (HdfDeviceUnregisterEventListener(serv, &listener)) {
        HDF_LOGE("fail to  unregister listener");
        return HDF_FAILURE;
    }

    HdfIoServiceRecycle(serv);
    return HDF_SUCCESS;
}
```

>![](public_sys-resources/icon-note.gif) **说明：** 
>用户态应用程序使用了HDF框架中的消息发送接口，因此在编译用户态程序的过程中需要依赖HDF框架对外提供的hdf\_core和osal的动态库，在gn编译文件中添加如下依赖项：
>deps = \[
>"//drivers/hdf/lite/manager:hdf\_core",
>"//drivers/hdf/lite/adapter/osal/posix:hdf\_posix\_osal",
>\]

