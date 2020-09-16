/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "sys_config.h"
#include "board.h"
#include "los_typedef.h"

#include "stdlib.h"
#include "stdio.h"
#include "los_process_pri.h"
#include "disk.h"
#include "los_rootfs.h"
#ifdef LOSCFG_DRIVERS_VIDEO
#include "fb.h"
#endif
#ifdef LOSCFG_SHELL
#include "shell.h"
#include "shcmd.h"
#endif

#ifdef LOSCFG_DRIVERS_HDF_PLATFORM_UART
#include "console.h"
#include "hisoc/uart.h"
#endif

#ifdef LOSCFG_DRIVERS_HDF
#include "devmgr_service_start.h"
#endif

#ifdef LOSCFG_DRIVERS_USB
#include "implementation/usb_init.h"
#endif

#ifdef LOSCFG_DRIVERS_NETDEV
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"

#define SLEEP_TIME_MS 60
#define NETIF_SETUP_OVERTIME 100

void net_init(void)
{
    struct netif *pnetif;

extern void tcpip_init(tcpip_init_done_fn initfunc, void *arg);
    dprintf("\ntcpip_init start\n");
    tcpip_init(NULL, NULL);
    dprintf("\ntcpip_init end\n");

    static unsigned int overtime = 0;
    PRINTK("Ethernet start.");

#ifdef LOSCFG_DRIVERS_HIGMAC
    extern int ethnet_higmac_init(void);
    (void)ethnet_higmac_init();
#endif

#ifdef LOSCFG_DRIVERS_HIETH_SF
    extern int ethnet_hieth_init(void);
    (void)ethnet_hieth_init();
#endif

    extern void get_defaultNetif(struct netif **pnetif);
    get_defaultNetif(&pnetif);

    (void)netifapi_netif_set_up(pnetif);
    do {
        LOS_Msleep(SLEEP_TIME_MS);
        overtime++;
        if (overtime > NETIF_SETUP_OVERTIME) {
            PRINTK("netif_is_link_up overtime!\n");
            break;
        }
    } while (netif_is_link_up(pnetif) == 0);
}
#endif

extern void SDK_init(void);
extern void CatLogShell(void);

void SystemInit(void)
{
#ifdef LOSCFG_PLATFORM_HISI_AMP
    extern int _ipcm_vdd_init(void);
    dprintf("ipcm init ...\n");
    _ipcm_vdd_init();

#ifndef LOSCFG_ARCH_CORTEX_M7
    extern int sharefs_client_init(const char *path);
    dprintf("sharefs init ...\n");
    sharefs_client_init("/sharefs");
#endif

    extern int virt_tty_dev_init(void);
    dprintf("virt tty init ...\n");
    virt_tty_dev_init();
#endif

#ifdef LOSCFG_DRIVERS_RANDOM
    dprintf("random dev init ...\n");
    extern int ran_dev_register(void);
    ran_dev_register();
#endif

#ifdef LOSCFG_FS_PROC
    dprintf("proc fs init ...\n");
    extern void ProcFsInit(void);
    ProcFsInit();
#endif

#ifdef LOSCFG_DRIVERS_MMC
    dprintf("MMC dev init ...");
    extern int SD_MMC_Host_init(void);
    SD_MMC_Host_init();
#endif

#ifdef LOSCFG_DRIVERS_MEM
    dprintf("mem dev init ...\n");
    extern int mem_dev_register(void);
    mem_dev_register();
#endif

#ifndef LOSCFG_DRIVERS_HDF
#ifdef LOSCFG_DRIVERS_GPIO
    dprintf("gpio init ...\n");
    extern int gpio_dev_init(void);
    gpio_dev_init();
#endif
#endif

#ifdef LOSCFG_DRIVERS_HIEDMAC
    extern int hiedmac_init(void);
    hiedmac_init();
#endif
#ifdef LOSCFG_DRIVERS_HIDMAC
    dprintf("dmac init ...\n");
#endif

#ifdef LOSCFG_DRIVERS_MTD_NAND
    dprintf("nand init ...\n");
    extern int nand_init(void);

    if (!nand_init()) {
        extern int add_mtd_partition(char *type, UINT32 start_addr, UINT32 length, UINT32 partition_num);

        extern int mount(const char *source, const char *target,
                         const char *filesystemtype, unsigned long mountflags,
                         const void *data);
    }

#endif

#ifdef LOSCFG_DRIVERS_MTD_SPI_NOR
    dprintf("spi nor flash init ...\n");
    extern int spinor_init(void);

    if (!spinor_init()) {
        dprintf("spinor_init ...\n");
    }
#endif

#ifdef LOSCFG_DRIVERS_NETDEV
    dprintf("net init ...\n");
    net_init();
    dprintf("\n************************************************************\n");
#endif

#ifdef LOSCFG_DRIVERS_USB
    dprintf("usb init ...\n");
    usb_init(DEVICE, DEV_ETHERNET);
#endif

    dprintf("Date:%s.\n", __DATE__);
    dprintf("Time:%s.\n", __TIME__);

#ifndef LOSCFG_DRIVERS_HDF_PLATFORM_HISI_SDK
    dprintf("calling SDK_init form HISI_SDK");
    SDK_init();
    dprintf("calling SDK_init form HISI_SDK done!");
#endif

#ifdef LOSCFG_PLATFORM_ROOTFS
    dprintf("OsMountRootfs start ...\n");
    OsMountRootfs();
    dprintf("OsMountRootfs end ...\n");
#endif

#ifdef LOSCFG_DRIVERS_HDF
    dprintf("DeviceManagerStart start ...\n");
    if (DeviceManagerStart()) {
        PRINT_ERR("No drivers need load by hdf manager!");
    }
    dprintf("DeviceManagerStart end ...\n");
#endif
#ifdef LOSCFG_DRIVERS_HDF_PLATFORM_UART
    dprintf("virtual_serial_init start ...\n");
    if (virtual_serial_init(TTY_DEVICE) != 0) {
        PRINT_ERR("virtual_serial_init failed");
    }
    dprintf("virtual_serial_init end ...\n");
    if (system_console_init(SERIAL) != 0) {
        PRINT_ERR("system_console_init failed\n");
    }
    dprintf("system_console_init end ...\n");
#endif
#ifdef LOSCFG_SHELL
    dprintf("CatLogShell start ...\n");
    CatLogShell();
    dprintf("CatLogShell start ...\n");
#endif
    dprintf("OsUserInitProcess start ...\n");
    if (OsUserInitProcess()) {
        PRINT_ERR("Create user init process faialed!\n");
        return;
    }
    dprintf("OsUserInitProcess end ...\n");
    return;
}
