# Developing the First Driver Program running on the Hi3516 Development Board<a name="EN-US_TOPIC_0000001054448621"></a>

This section describes how to develop a driver program on the board, including introduction, compilation, burning, and operation of the driver.

## Obtaining the Source Code<a name="section1486619351629"></a>

You need to download a set of source code from the Linux server. For details, see  [Source Code Acquisition](en-us_topic_0000001050769927.md).

## Introduction to Driver<a name="s8efc1952ebfe4d1ea717182e108c29bb"></a>

The following example shows how to add configuration files, implement the driver code, and compile the code for interaction between the user-space applications and the driver based on the UART driver. The driver source code is stored in the  **vendor/huawei/hdf/sample**  directory.

1.  Add Configurations.

    The following example shows how to add the driver configurations to the HDF configuration file \(for example,  **vendor/hisi/hi35xx/hi3516dv300/config/uart/uart\_config.hcs**\).

    ```
    root {
        platform {
            uart_sample {
    num = 5; // UART Device No.
                base = 0x120a0000;  // UART registers
                irqNum = 38;
                baudrate = 115200;
                uartClk = 24000000;
                wlen = 0x60;
                parity = 0;
                stopBit = 0;
                match_attr = "sample_uart_5";
            }
        }
    }
    ```

    This example shows how to add the driver nodes to the HDF configuration file \(for example,  **vendor/hisi/hi35xx/hi3516dv300/config/device\_info/device\_info.hcs**\).

    ```
    root {
        device_info {
            platform :: host {
                hostName = "platform_host";
                priority = 50;
                device_uart :: device {
                    device5 :: deviceNode {
                        policy = 1;
                        priority = 40;
                        permission = 0644;
                        moduleName = "UART_SAMPLE";
                        serviceName = "HDF_PLATFORM_UART_5";
                        deviceMatchAttr = "sample_uart_5";
                    }
                }
            }
        }
    }
    ```

    >![](public_sys-resources/icon-note.gif) **NOTE:** 
    >The configuration file and the source code of the UART driver sample are in the same path. You need to manually add them to the path of the Hi3516D V300 board.

2.  Register a UART driver entry.

    The following example shows how to register the  **HdfDriverEntry**  entry of the UART driver based on the HDF.

    ```
    // Bind the UART driver interface to the HDF.
    static int32_t HdfUartSampleBind(struct HdfDeviceObject *device)
    {
        if (device == NULL) {
            return HDF_ERR_INVALID_OBJECT;
        }
        HDF_LOGI("Enter %s:", __func__);
        return (UartHostCreate(device) == NULL) ? HDF_FAILURE : HDF_SUCCESS;
    }
     
    // Obtain configuration information from the HCS of the UART driver.
    static uint32_t UartDeviceGetResource(
        struct UartDevice *device, const struct DeviceResourceNode *resourceNode)
    {
        struct UartResource *resource = &device->resource;
        struct DeviceResourceIface *dri = NULL;
        dri = DeviceResourceGetIfaceInstance(HDF_CONFIG_SOURCE);
        if (dri == NULL || dri->GetUint32 == NULL) {
            HDF_LOGE("DeviceResourceIface is invalid");
            return HDF_FAILURE;
        }
     
        if (dri->GetUint32(resourceNode, "num", &resource->num, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read num fail");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "base", &resource->base, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read base fail");
            return HDF_FAILURE;
        }
        resource->physBase = (unsigned long) OsalIoRemap(resource->base, 0x48);
        if (resource->physBase == 0) {
            HDF_LOGE("uart config fail to remap physBase");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "irqNum", &resource->irqNum, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config read irqNum fail");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "baudrate", &resource->baudrate, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read baudrate fail");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "wlen", &resource->wlen, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read wlen fail");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "parity", &resource->parity, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read parity fail");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "stopBit", &resource->stopBit, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read stopBit fail");
            return HDF_FAILURE;
        }
        if (dri->GetUint32(resourceNode, "uartClk", &resource->uartClk, 0) != HDF_SUCCESS) {
            HDF_LOGE("uart config  read uartClk fail");
            return HDF_FAILURE;
        }
        return HDF_SUCCESS;
    }
     
    // Attach the configuration and interfaces of the UART driver to the HDF.
    static int32_t SampleAttach(struct UartHost *host, struct HdfDeviceObject *device)
    {
        int32_t ret;
        struct UartDevice *uartDevice = NULL;
        if (device->property == NULL) {
            HDF_LOGE("%s: property is NULL", __func__);
            return HDF_FAILURE;
        }
        uartDevice = (struct UartDevice *) OsalMemCalloc(sizeof(struct UartDevice));
        if (uartDevice == NULL) {
            HDF_LOGE("%s: OsalMemCalloc uartDevice error", __func__);
            return HDF_ERR_MALLOC_FAIL;
        }
        ret = UartDeviceGetResource(uartDevice, device->property);
        if (ret != HDF_SUCCESS) {
            (void) OsalMemFree(uartDevice);
            return HDF_FAILURE;
        }
        host->num = uartDevice->resource.num;
        host->priv = uartDevice;
        UartSampleAddDev(host); // Add a user-space UART node. For details, see the source code uart_dev_sample.
        return UartDeviceInit(uartDevice); // Initialize UART PL011. For details, see the source code uart_pl011_sample.
    }
     
    // Initialize the UART driver.
    static int32_t HdfUartSampleInit(struct HdfDeviceObject *device)
    {
        int32_t ret;
        struct UartHost *host = NULL;
     
        if (device == NULL) {
            HDF_LOGE("%s: device is NULL", __func__);
            return HDF_ERR_INVALID_OBJECT;
        }
        HDF_LOGI("Enter %s:", __func__);
        host = UartHostFromDevice(device);
        if (host == NULL) {
            HDF_LOGE("%s: host is NULL", __func__);
            return HDF_FAILURE;
        }
        ret = SampleAttach(host, device);
        if (ret != HDF_SUCCESS) {
            HDF_LOGE("%s: attach error", __func__);
            return HDF_FAILURE;
        }
        host->method = &g_uartSampleHostMethod;
        return ret;
    }
     
    static void UartDeviceDeinit(struct UartDevice *device)
    {
        struct UartRegisterMap *regMap = (struct UartRegisterMap *) device->resource.physBase;
        /* wait for uart enter idle. */
        while (UartPl011IsBusy(regMap));
        UartPl011ResetRegisters(regMap);
        uart_clk_cfg(0, false);
        OsalIoUnmap((void *) device->resource.physBase);
        device->state = UART_DEVICE_UNINITIALIZED;
    }
     
    // Unbind and detach the UART driver.
    static void SampleDetach(struct UartHost *host)
    {
        struct UartDevice *uartDevice = NULL;
     
        if (host->priv == NULL) {
            HDF_LOGE("%s: invalid parameter", __func__);
            return;
        }
        uartDevice = host->priv;
        UartDeviceDeinit(uartDevice);
        (void) OsalMemFree(uartDevice);
        host->priv = NULL;
    }
     
    // Release the UART driver.
    static void HdfUartSampleRelease(struct HdfDeviceObject *device)
    {
        struct UartHost *host = NULL;
        HDF_LOGI("Enter %s:", __func__);
     
        if (device == NULL) {
            HDF_LOGE("%s: device is null", __func__);
            return;
        }
        host = UartHostFromDevice(device);
        if (host == NULL) {
            HDF_LOGE("%s: host is null", __func__);
            return;
        }
        if (host->priv != NULL) {
            SampleDetach(host);
        }
        UartHostDestroy(host);
    }
     
    struct HdfDriverEntry g_hdfUartSample = {
        .moduleVersion = 1,
        .moduleName = "UART_SAMPLE",
        .Bind = HdfUartSampleBind,
        .Init = HdfUartSampleInit,
        .Release = HdfUartSampleRelease,
    };
     
    HDF_INIT(g_hdfUartSample);
    ```

3.  Register a UART driver interface.

    The following example shows how to implement the UART driver interface using the template  **UartHostMethod**  provided by the HDF.

    ```
    static int32_t SampleInit(struct UartHost *host)
    {
        HDF_LOGI("%s: Enter", __func__);
        if (host == NULL) {
            HDF_LOGE("%s: invalid parameter", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        return HDF_SUCCESS;
    }
    
    static int32_t SampleDeinit(struct UartHost *host)
    {
        HDF_LOGI("%s: Enter", __func__);
        if (host == NULL) {
            HDF_LOGE("%s: invalid parameter", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        return HDF_SUCCESS;
    }
    
    // Write data into the UART.
    static int32_t SampleWrite(struct UartHost *host, uint8_t *data, uint32_t size)
    {
        HDF_LOGI("%s: Enter", __func__);
        uint32_t idx;
        struct UartRegisterMap *regMap = NULL;
        struct UartDevice *device = NULL;
     
        if (host == NULL || data == NULL || size == 0) {
            HDF_LOGE("%s: invalid parameter", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        device = (struct UartDevice *) host->priv;
        if (device == NULL) {
            HDF_LOGE("%s: device is NULL", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        regMap = (struct UartRegisterMap *) device->resource.physBase;
        for (idx = 0; idx < size; idx++) {
            while (UartPl011IsBusy(regMap));
            UartPl011Write(regMap, data[idx]);
        }
        return HDF_SUCCESS;
    }
     
    // Set the baud rate of the UART.
    static int32_t SampleSetBaud(struct UartHost *host, uint32_t baudRate)
    {
        HDF_LOGI("%s: Enter", __func__);
        struct UartDevice *device = NULL;
        struct UartRegisterMap *regMap = NULL;
        UartPl011Error err;
     
        if (host == NULL) {
            HDF_LOGE("%s: invalid parameter", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        device = (struct UartDevice *) host->priv;
        if (device == NULL) {
            HDF_LOGE("%s: device is NULL", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        regMap = (struct UartRegisterMap *) device->resource.physBase;
        if (device->state != UART_DEVICE_INITIALIZED) {
            return UART_PL011_ERR_NOT_INIT;
        }
        if (baudRate == 0) {
            return UART_PL011_ERR_INVALID_BAUD;
        }
        err = UartPl011SetBaudrate(regMap, device->uartClk, baudRate);
        if (err == UART_PL011_ERR_NONE) {
            device->baudrate = baudRate;
        }
        return err;
    }
     
    // Obtain the baud rate of the UART.
    static int32_t SampleGetBaud(struct UartHost *host, uint32_t *baudRate)
    {
        HDF_LOGI("%s: Enter", __func__);
        struct UartDevice *device = NULL;
     
        if (host == NULL) {
            HDF_LOGE("%s: invalid parameter", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        device = (struct UartDevice *) host->priv;
        if (device == NULL) {
            HDF_LOGE("%s: device is NULL", __func__);
            return HDF_ERR_INVALID_PARAM;
        }
        *baudRate = device->baudrate;
        return HDF_SUCCESS;
    }
     
    // Bind the UART using HdfUartSampleInit.
    struct UartHostMethod g_uartSampleHostMethod = {
        .Init = SampleInit,
        .Deinit = SampleDeinit,
        .Read = NULL,
        .Write = SampleWrite,
        .SetBaud = SampleSetBaud,
        .GetBaud = SampleGetBaud,
        .SetAttribute = NULL,
        .GetAttribute = NULL,
        .SetTransMode = NULL,
    };
    ```

    The following sample code shows how to add the module of the UART driver to the compilation script  **vendor/huawei/hdf/hdf\_vendor.mk**.

    ```
    LITEOS_BASELIB += -lhdf_uart_sample
    LIB_SUBDIRS    += $(VENDOR_HDF_DRIVERS_ROOT)/sample/platform/uart
    ```

4.  Compile the code for interaction between the user-space applications and driver.

    Create the  **/dev/uartdev-5**  node after the UART driver is initialized successfully. The following example shows how to interact with the UART driver through the node.

    ```
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include "hdf_log.h"
    
    #define HDF_LOG_TAG "hello_uart"
    #define INFO_SIZE 16
    
    int main(void)
    {
        int ret;
        int fd;
        const char info[INFO_SIZE] = {" HELLO UART! "};
    
        fd = open("/dev/uartdev-5", O_RDWR);
        if (fd < 0) {
            HDF_LOGE("hello_uart uartdev-5 open failed %d", fd);
            return -1;
        }
        ret = write(fd, info, INFO_SIZE);
        if (ret != 0) {
            HDF_LOGE("hello_uart write uartdev-5 ret is %d", ret);
        }
        ret = close(fd);
        if (ret != 0) {
            HDF_LOGE("hello_uart uartdev-5 close failed %d", fd);
            return -1;
        }
        return ret;
    }
    ```

    The following example shows how to add the  **hello\_uart\_sample**  component to the  **hdf**  subsystem in the  **build/lite/product/ipcamera\_hi3516dv300.json**  file.

    ```
    {
      "subsystem": [
        {
          "name": "hdf",
          "component": [
            { "name": "hdf_sample", "dir": "//vendor/huawei/hdf/sample/platform/uart:hello_uart_sample", "feature":[] }
          ]
        }
      ]
    }
    ```

    >![](public_sys-resources/icon-note.gif) **NOTE:** 
    >The preceding code is only a sample code. You can view the complete code in  **vendor/huawei/hdf/sample**.
    >The sample code is not automatically compiled by default. You need to manually add it to the compilation script.


## Compiling<a name="section164159213275"></a>

On the Linux server, go to the root directory of the source code package. The build.py compilation script is stored in the directory. Run the following script to compile the source code package:

Run the following script in the root directory of the source code package to compile the source code package. The result file is generated in the out/ipcamera\_hi3516dv300 directory.

```
python build.py ipcamera_hi3516dv300 -b debug
```

## Burning<a name="section0716824162715"></a>

Network Burning Mode

This method applies only to the board \(such as Hi3516D V300\) that supports the network port. In addition, the PC and the board must be connected by using a network cable and configured on the same network.

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>The Visual Studio Code software connects the board to the network. If the board cannot connect to the computer network, check the firewall settings. For details, see FAQ 2.

1.  Install the USB-to-serial adapter driver and obtain the serial port number.

    **Figure  1**  Successful driver installation<a name="en-us_topic_0000001052906247_fig87951742181717"></a>  
    ![](figures/successful-driver-installation.png "successful-driver-installation")

    1.  Power on the board and connect the serial port cable of the board to the Windows console.
    2.  Install the driver and obtain the driver link.
    3.  Open Device Manager, then check and record the value of  **Prolific USB-to-Serial Comm Port**.

        After the driver is successfully installed, if a warning icon is displayed on the device icon, right-click the device, uninstall the driver, reinstall the driver, and restart the computer as prompted.


2.  On the Windows console, add the IP address 192.168.1.3 for the interconnection network port of the board. The method is as follows:

    **Figure  2**  Adding a Windows host IP address<a name="en-us_topic_0000001052906247_fig1438112431779"></a>  
    ![](figures/adding-a-windows-host-ip-address.png "adding-a-windows-host-ip-address")

    1.  Choose Control Panel \> Network and Internet-\> Network Connections, right-click the network adapter connected to the board, and choose Properties from the shortcut menu.
    2.  Double-click Internet 协议版本4（TCP/IPv4）. 
    3.  Configure the IP address and gateway according to the preceding figure.
    4.  Click OK to save the configuration.

3.  hi3516dv300 is added to the board list. After you choose Board Configure and enable a board, the board configuration table is automatically added.

    **Figure  3**  Add a board.<a name="en-us_topic_0000001052906247_fig152451448203711"></a>  
    ![](figures/add-a-board.png "add-a-board")

4.  Start the IDE and click the icons in sequence to configure the contents to be burnt over the network.

    **Figure  4**  Network configuration diagram of the IDE tool<a name="en-us_topic_0000001052906247_fig79672366813"></a>  
    

    ![](figures/ide.png)

    1.  Select Hi3516 as the board type.
    2.  Click Burn.
    3.  Set Burning Mode to "network".
    4.  Host IP Address: Click to refresh the page and select 192.168.1.3 from the drop-down list box.

5.  Select the chip to be burnt to the flash memory and the burning address.

    **Figure  5**  Setting the parameters for burning files<a name="en-us_topic_0000001052906247_fig11902195416418"></a>  
    

    ![](figures/ide2.png)

    1.  Select emmc from the Memory Type drop-down list box as the flash memory type.
    2.  Click New to add three files. Enter the OHOS\_Image.bin, rootfs.img, and userfs.img files in the file path in sequence. Set the start address and file length as shown in the following figure, obtain the file from the out/ipcamera\_hi3516dv300 directory.
    3.  Click <cf id="Bold"\>Save</cf\> to save the changes.
    4.  Click Burn on the left to start burning.

6.  Select a serial port number from the drop-down list box displayed in the upper part, for example, COM11.

    **Figure  6**  Selecting the serial port to be connected to the board<a name="en-us_topic_0000001052906247_fig73452316549"></a>  
    ![](figures/selecting-the-serial-port-to-be-connected-to-the-board.png "selecting-the-serial-port-to-be-connected-to-the-board")

7.  The burning starts. If a message is displayed, you need to manually restart the board \(by powering off and then powering on the board\).

    **Figure  7**  The system prompts you to power off the board and power on the board again.<a name="en-us_topic_0000001052906247_fig3421920185520"></a>  
    

    ![](figures/reset2.png)

8.  Burning is complete.

    **Figure  8**  Successful burning<a name="en-us_topic_0000001052906247_fig88368374585"></a>  
    ![](figures/successful-burning.png "successful-burning")


## Running an Image<a name="section197971119142915"></a>

1.  Connect a serial port cable.

    **Figure  9**  Connect the serial port cables.<a name="en-us_topic_0000001052906247_fig056645018495"></a>  
    

    ![](figures/chuankou1.png)

    1.  Click Serial port to enable the serial port.
    2.  Enter the serial port number of the "com11" and press Enter until hisillicon is displayed.
    3.  If the board is started for the first time or the startup parameters are modified, go to step 2. Otherwise, go to step 3.

2.  \(Mandatory when the board is started for the first time\) Modify the bootcmd and bootargs of the U-boot. This step is a fixed operation. If the parameters are not modified, you need to perform this step only once. The system automatically enters the system each time the board is reset.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >By default, the U-boot boot program waits for two seconds. You can press Enter to interrupt the waiting and the message "hisillicon" is displayed. You can run the reset command to restart the system.

    **Table  1**  U-boot startup parameters

    <a name="en-us_topic_0000001052906247_table432481061214"></a>
    <table><tbody><tr id="en-us_topic_0000001052906247_row532461021219"><th class="firstcol" valign="top" width="8.39%" id="mcps1.2.3.1.1"><p id="en-us_topic_0000001052906247_p1238114718129"><a name="en-us_topic_0000001052906247_p1238114718129"></a><a name="en-us_topic_0000001052906247_p1238114718129"></a>Command</p>
    </th>
    <td class="cellrowborder" valign="top" width="91.61%" headers="mcps1.2.3.1.1 "><p id="en-us_topic_0000001052906247_p93816470127"><a name="en-us_topic_0000001052906247_p93816470127"></a><a name="en-us_topic_0000001052906247_p93816470127"></a><strong id="en-us_topic_0000001052906247_b143728351609"><a name="en-us_topic_0000001052906247_b143728351609"></a><a name="en-us_topic_0000001052906247_b143728351609"></a>setenv bootcmd "sf probe 0;mmc read 0x0 0x80000000 0x800 0x4800; go 0x80000000";</strong></p>
    <p id="en-us_topic_0000001052906247_p83904761218"><a name="en-us_topic_0000001052906247_p83904761218"></a><a name="en-us_topic_0000001052906247_p83904761218"></a><strong id="en-us_topic_0000001052906247_b14389193520014"><a name="en-us_topic_0000001052906247_b14389193520014"></a><a name="en-us_topic_0000001052906247_b14389193520014"></a>setenv bootargs "console=ttyAMA0,115200n8 root=emmc fstype=vfat rootaddr=10M rootsize=15M rw";</strong></p>
    <p id="en-us_topic_0000001052906247_p7399470123"><a name="en-us_topic_0000001052906247_p7399470123"></a><a name="en-us_topic_0000001052906247_p7399470123"></a><strong id="en-us_topic_0000001052906247_b1041015359012"><a name="en-us_topic_0000001052906247_b1041015359012"></a><a name="en-us_topic_0000001052906247_b1041015359012"></a>saveenv</strong></p>
    <p id="en-us_topic_0000001052906247_p14391747131219"><a name="en-us_topic_0000001052906247_p14391747131219"></a><a name="en-us_topic_0000001052906247_p14391747131219"></a><strong id="en-us_topic_0000001052906247_b84127351701"><a name="en-us_topic_0000001052906247_b84127351701"></a><a name="en-us_topic_0000001052906247_b84127351701"></a>reset</strong></p>
    </td>
    </tr>
    <tr id="en-us_topic_0000001052906247_row6324410171216"><th class="firstcol" valign="top" width="8.39%" id="mcps1.2.3.2.1"><p id="en-us_topic_0000001052906247_p203915473129"><a name="en-us_topic_0000001052906247_p203915473129"></a><a name="en-us_topic_0000001052906247_p203915473129"></a>Description</p>
    </th>
    <td class="cellrowborder" valign="top" width="91.61%" headers="mcps1.2.3.2.1 "><p id="en-us_topic_0000001052906247_p439134715129"><a name="en-us_topic_0000001052906247_p439134715129"></a><a name="en-us_topic_0000001052906247_p439134715129"></a><strong id="en-us_topic_0000001052906247_b14391847171211"><a name="en-us_topic_0000001052906247_b14391847171211"></a><a name="en-us_topic_0000001052906247_b14391847171211"></a>setenv bootcmd "mmc read 0x0 0x80000000 0x800 0x4800;go 0x80000000";</strong></p>
    <p id="en-us_topic_0000001052906247_p1439184741218"><a name="en-us_topic_0000001052906247_p1439184741218"></a><a name="en-us_topic_0000001052906247_p1439184741218"></a>This command indicates that flash 0 is selected, and the contents with the start address of 0x800 (unit: 512 bytes, that is, 1 MB) and the size of 0x4800 (unit: 512 bytes, that is, 9 MB) are read to the memory address 0x80000000.</p>
    <p id="en-us_topic_0000001052906247_p7391347101215"><a name="en-us_topic_0000001052906247_p7391347101215"></a><a name="en-us_topic_0000001052906247_p7391347101215"></a><strong id="en-us_topic_0000001052906247_b0397473129"><a name="en-us_topic_0000001052906247_b0397473129"></a><a name="en-us_topic_0000001052906247_b0397473129"></a>setenv bootargs "console=ttyAMA0,115200n8 root=emmc fstype=vfat rootaddr=10M rootsize=15M rw";</strong></p>
    <p id="en-us_topic_0000001052906247_p939547151215"><a name="en-us_topic_0000001052906247_p939547151215"></a><a name="en-us_topic_0000001052906247_p939547151215"></a>This command sets the boot parameters to serial port output, baud rate to 115200, data bit to 8, rootfs to be mounted to the eMMC, and file system type to vfat,</p>
    <p id="en-us_topic_0000001052906247_p8402475121"><a name="en-us_topic_0000001052906247_p8402475121"></a><a name="en-us_topic_0000001052906247_p8402475121"></a>Enter the start burning position and length of rootfs.img in rootaddr=10M rootsize=15M rw. The size must be the same as that of the rootfs.img file added in the IDE.</p>
    <p id="en-us_topic_0000001052906247_p54034712120"><a name="en-us_topic_0000001052906247_p54034712120"></a><a name="en-us_topic_0000001052906247_p54034712120"></a><strong id="en-us_topic_0000001052906247_b2600155013264"><a name="en-us_topic_0000001052906247_b2600155013264"></a><a name="en-us_topic_0000001052906247_b2600155013264"></a>saveenv</strong> indicates that the current configuration is saved.</p>
    <p id="en-us_topic_0000001052906247_p2401247131212"><a name="en-us_topic_0000001052906247_p2401247131212"></a><a name="en-us_topic_0000001052906247_p2401247131212"></a><strong id="en-us_topic_0000001052906247_b1427444612265"><a name="en-us_topic_0000001052906247_b1427444612265"></a><a name="en-us_topic_0000001052906247_b1427444612265"></a>reset</strong> indicates that the board is reset.</p>
    <p id="en-us_topic_0000001052906247_p1440164791213"><a name="en-us_topic_0000001052906247_p1440164791213"></a><a name="en-us_topic_0000001052906247_p1440164791213"></a><strong id="en-us_topic_0000001052906247_b725515390267"><a name="en-us_topic_0000001052906247_b725515390267"></a><a name="en-us_topic_0000001052906247_b725515390267"></a>(Optional) go 0x40000000</strong> indicates that the command is fixed in the startup parameters by default and the board automatically starts after it is reset. If you want to manually start the board, you can press <strong id="en-us_topic_0000001052906247_b1420714384268"><a name="en-us_topic_0000001052906247_b1420714384268"></a><a name="en-us_topic_0000001052906247_b1420714384268"></a>Enter</strong> in the countdown phase of the U-Boot startup to interrupt the automatic startup.</p>
    </td>
    </tr>
    </tbody>
    </table>

3.  Enter reset and press Enter to restart the board. After the board is restarted successfully, press Enter. OHOS is displayed.

    **Figure  10**  Start the system<a name="en-us_topic_0000001052906247_fig10181006376"></a>  
    

    ![](figures/qi1.png)

4.  In the root directory, run the  **./bin/hello\_uart**  command line to operate the demo program. The following figure shows the compilation result.

    ```
    OHOS # ./bin/hello_uart
    OHOS #  HELLO UART!
    ```


