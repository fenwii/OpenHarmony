# Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
# Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other materials
#    provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be used
#    to endorse or promote products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

####Kernel command####
#task_shellcmd.c -utask_shellcmd
#cpup_shellcmd.c -ucpup_shellcmd
#shell_shellcmd.c -uhelp_shellcmd
#mempt_shellcmd.c -ufree_shellcmd -umemcheck_shellcmd -uuname_shellcmd -ureadreg_shellcmd -uwritereg_shellcmd
#sem_shellcmd.c -usem_shellcmd
#sysinfo_shellcmd.c -usysteminfo_shellcmd
#swtmr_shellcmd.c -uswtmr_shellcmd
#hwi_shell.c -uhwi_shellcmd
#dynload_shellcmd.c -uldinit_shellcmd -ucall_shellcmd -ufindsym_shellcmd -ulddrop_shellcmd -umclose_shellcmd -umopen_shellcmd
LITEOS_TABLES_KERNEL_LDFLAGS := \
    -utask_shellcmd \
    -ug_usrVdsoDataPage\
    -uvm_shellcmd \
    -ucpup_shellcmd \
    -uhelp_shellcmd \
    -ufree_shellcmd \
    -usem_shellcmd \
    -umutex_shellcmd \
    -uqueue_shellcmd \
    -usysteminfo_shellcmd \
    -uswtmr_shellcmd \
    -uhwi_shellcmd \
    -ufindsym_shellcmd \
    -uzbar_scan_shellcmd \
    -udmesg_shellcmd \
    -udate_shellcmd \
    -ureadExcInfo_shellcmd \
    -uwatch_shellcmd \
    -udeadlock_shellcmd \
    -ukill_shellcmd \
    -upmm_shellcmd


####Net command####
#api_shell.c -uarp_shellcmd -uifconfig_shellcmd -uping_shellcmd -utftp_shellcmd -unetstat_shellcmd -udns_shellcmd -untpdate_shellcmd
#telnet_loop.c -utelnet_shellcmd
LITEOS_TABLES_NET_LDFLAGS := \
    -uarp_shellcmd \
    -utelnet_shellcmd \
    -uping_shellcmd \
    -unetstat_shellcmd \
    -uifconfig_shellcmd

####FS command####
#vfs_shellcmd.c -ucd_shellcmd -ucat_shellcmd -uls_shellcmd -upwd_shellcmd -urm_shellcmd -urmdir_shellcmd -umkdir_shellcmd -utouch_shellcmd -uumount_shellcmd -umount_shellcmd -usync_shellcmd -ustatfs_shellcmd -ucp_shellcmd
#fat_shellcmd.c -uformat_shellcmd
#mtd_shellcmd.c -upartition_shellcmd
#proc_shellcmd.c -uwriteproc_shellcmd
#disk_shellcmd.c -upartinfo_shellcmd
LITEOS_TABLES_FS_LDFLAGS := \
    -ucd_shellcmd \
    -uformat_shellcmd \
    -upartition_shellcmd \
    -uwriteproc_shellcmd \
    -upartinfo_shellcmd \
    -uumount_shellcmd -umount_shellcmd \
    -uvirstatfs_shellcmd \
    -ulsfd_shellcmd \
    -usu_shellcmd \
    -uchmod_shellcmd \
    -uchown_shellcmd \
    -uchgrp_shellcmd

####Tools command####
#iperf_shell.c -uiperf_shellcmd
LITEOS_TABLES_TOOLS_LDFLAGS := \
    -uiperf_shellcmd \
    -ulwip_dump_shellcmd

####Extend command####
#reset_shell.c -ureset_shellcmd
#bcm_wifi.c -ustartap_shellcmd -ustopap_shellcmd -ubcmwifi_shellcmd
#ddrs_shell.c -uhiddrs_shellcmd
#nand_shell.c -unand_bad_shellcmd
#i2c_shell.c -ui2c_read_shellcmd -ui2c_write_shellcmd
#spi_shell.c -ussp_read_shellcmd -ussp_write_shellcmd
#uart_shell.c -uuart_config_shellcmd -uuart_write_shellcmd -uuart_read_shellcmd -uuart_close_shellcmd
LITEOS_TABLES_EXTEND_LDFLAGS := \
    -ureset_shellcmd \
    -ustartap_shellcmd \
    -uhiddrs_shellcmd \
    -unand_bad_shellcmd \
    -ui2c_read_shellcmd \
    -ussp_read_shellcmd \
    -uuart_config_shellcmd\
    -uusb_debug_shellcmd

LITEOS_TABLES_DRIVER_LDFLAGS := \
    -ui2c_init \
    -ugpio_init \
    -uregulator_init \
    -uMtdInitList \
    -uhispi_init \
    -uhifmc100_init \
    -uhisfc350_init \
    -unand_hifmc100_init \
    -uhifmc100_parallel_init \
    -usd_mci_init \
    -uhi_mci_init \
    -upl011_init \
    -uhinfc620_init \
    -uhisnfc100_init \
    -uregulator_machine_init \
    -uhisimeidia_regulator_init \
    -ucpufreq_init  \
    -uhisilicon_cpufreq_init \
    -ucpufreq_machine_init  \
    -udevfreq_init \
    -umedia_devfreq_init \
    -udevfreq_machine_init\
    -uhieth_machine_init\
    -uhigmac_machine_init \
    -umachine_init

####FS MAP####
LITEOS_TABLES_FSMAP_LDFLAGS := \
    -uramfs_fsmap \
    -unfs_fsmap \
    -ufat_fsmap \
    -ujffs_fsmap \
    -uprocfs_fsmap \
    -ug_fsmap

LITEOS_TABLES_LDFLAGS := \
    $(LITEOS_TABLES_KERNEL_LDFLAGS)\
    $(LITEOS_TABLES_NET_LDFLAGS) \
    $(LITEOS_TABLES_FS_LDFLAGS) \
    $(LITEOS_TABLES_TOOLS_LDFLAGS) \
    $(LITEOS_TABLES_EXTEND_LDFLAGS) \
    $(LITEOS_TABLES_FSMAP_LDFLAGS) \
    $(LITEOS_TABLES_DRIVER_LDFLAGS)

