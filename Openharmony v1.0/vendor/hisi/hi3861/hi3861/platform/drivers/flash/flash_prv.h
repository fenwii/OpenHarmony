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

#ifndef __FLASH_PRV_H__
#define __FLASH_PRV_H__
#include <hi_flash_base.h>
#include <hi_types_base.h>
#include <hi3861_platform_base.h>
#define flash_info_print(fmt, ...)

#define HI_FLASH_OPTION_READ_WAIT_READY             0x1
#define HI_FLASH_OPTION_WRITE_WAIT_READY            0x2
#define HI_FLASH_OPTION_ERASE_WAIT_READY            0x4
#define HI_FLASH_OPTION_WRITE_ENABLE_WAIT_READY     0x8

/*****************************************************************************/
#define SPI_QE_EN                                   0x02   /* QE Bit Enable */
#define SPI_CMD_WREN                                0x06   /* Write Enable */
#define SPI_CMD_VSR_WREN                            0x50   /* write volatile SR reg enable */
/*****************************************************************************/
#define SPI_CMD_SE_4K                               0x20   /* 4KB sector Erase */
#define SPI_CMD_SE_32K                              0x52   /* 32KB sector Erase */
#define SPI_CMD_SE                                  0xD8   /* 64KB Sector Erase */
#define SPI_CMD_CE1                                 0xC7   /* chip erase */
#define SPI_CMD_CE2                                 0x60   /* chip erase */
/*****************************************************************************/
#define SPI_CMD_WRSR1                               0x01   /* Write Status Register */
#define SPI_CMD_WRSR2                               0x31   /* Write Status Register-2 */
#define SPI_CMD_RDSR2                               0x35   /* Read Status Register-2 */
#define SPI_CMD_WRSR3                               0x11   /* Write Status Register-3 */
#define SPI_CMD_RDSR3                               0x15   /* Read Status Register-3 */
#define SPI_CMD_RDID                                0x9F   /* Read Identification */

/* read status register. */
#define SPI_CMD_RDSR                                0x05

/* write status/configuration register. */
#define SPI_CMD_WRSRCR                              0x01

/* read configuration register. */
#define SPI_CMD_RDCR                                0x15

/*****************************************************************************/
#define SPI_CMD_PP                                  0x02   /* Page Programming */
#define SPI_CMD_WRITE_DUAL                          0xA2   /* fast program dual input */
#define SPI_CMD_WRITE_QUAD                          0x32   /* fast program quad input */
#define SPI_CMD_WRITE_DUAL_ADDR                     0xD2   /* Dual I/O High Performance Write */
#define SPI_CMD_WRITE_QUAD_ADDR                     0x12   /* Quad I/O High Performance Write */
/*****************************************************************************/
#define SPI_CMD_READ                                0x03   /* Read Data bytes */
#define SPI_CMD_FAST_READ                           0x0B   /* Read Data Bytes at Higher Speed */
#define SPI_CMD_READ_DUAL                           0x3B   /* fast read dual output */
#define SPI_CMD_READ_QUAD                           0x6B   /* fast read quad output */
#define SPI_CMD_QUAD_IO                             0xEB   /* fast quad-IO */

#define SPI_CMD_READ_DUAL_ADDR                      0xBB   /* Dual I/O High Performance Read */
#define SPI_CMD_READ_QUAD_ADDR                      0xEB   /* Quad I/O High Performance Read */
/*****************************************************************************/
#define SPI_CMD_SR_WIPN                             0      /* Write in Progress */
#define SPI_CMD_SR_WIP                              1      /* Write in Progress */
#define SPI_CMD_SR_WEL                              2      /* Write Enable Latch */
/*****************************************************************************/
#define SPI_CMD_EN4B                                0xB7  /* enter to 4 bytes mode and set 4 byte bit as '1' */
#define SPI_CMD_EX4B                                0xE9  /* exit 4 bytes mode and clear 4 byte bit as '0' */

#define SPI_CMD_RESET_ENABLE                        0x66   /* RESET Enable */
#define SPI_CMD_RESET                               0x99   /* RESET */

#define SPI_SR_BIT_WIP                              (1<<0)  /* Write in Progress */
#define SPI_SR_BIT_WEL                              (1<<1)  /* Write Enable Latch */

#define _1K             0x400
#define _2K             0x800
#define _4K             0x1000
#define _8K             0x2000
#define _16K            0x4000
#define _32K            0x8000
#define _64K            0x10000
#define _128K           0x20000
#define _256K           0x40000
#define _512K           0x80000
#define _1M             0x100000
#define _2M             0x200000
#define _4M             0x400000
#define _8M             0x800000
#define _16M            0x1000000
#define _32M            0x2000000

#define _CHIP_SIZE      0x3ffff
#define HI_FLASH_DEFAULT_TYPE_NUM   8

#define HI_FLASH_SUPPORT_REF_VBAT   /* VBAT can be used as ref valtage */
/* if support flash_update:#define HI_FLASH_SUPPORT_UPDATE_SFC_FREQ */
#define HI_FLASH_VOLTAGE_TH0 280
#define HI_FLASH_VOLTAGE_TH1 310
#define PLL2DBB_192M_MASK    0x3
#define CMU_CLK_SEL_96M      96
#define CMU_CLK_SEL_80M      80
#define CMU_CLK_SEL_48M      48

typedef struct {
    hi_u32 cmd :     8;
    hi_u32 iftype :  3;
    hi_u32 dummy :   3;
    hi_u32 size :    18;
} spi_flash_operation;

typedef enum {
    HI_FLASH_SUPPORT_4K_ERASE = 0x1,
    HI_FLASH_SUPPORT_32K_ERASE = 0x2,
    HI_FLASH_SUPPORT_64K_ERASE = 0x4,
    HI_FLASH_SUPPORT_CHIP_ERASE = 0x8,
    HI_FLASH_SUPPORT_AREA_LOCK_NV = 0x10,
    HI_FLASH_SUPPORT_AREA_LOCK_VOLATILE = 0x20,
    HI_FLASH_SUPPORT_INDIVIDUAL_LOCK = 0x40,
    HI_FLASH_SUPPORT_SUSPEND_RESUME = 0x80,
    HI_FLASH_VLT_INFLUENCE_FREQ = 0x100,
    HI_FLASH_SUPPORT_MASK = 0xFFFF,
} hi_spi_flash_chip_attribute;

typedef struct {
    hi_char *chip_name;
    hi_u8  chip_id[HI_FLASH_CHIP_ID_NUM];
    hi_u8  freq_read;
    hi_u8  freq_lowpower;
    hi_u8  freq_hpm;
    hi_u16 chip_attribute;
    hi_u8  cmd_suspend;
    hi_u8  cmd_resume;
    hi_u8  cmd_readsr;
    hi_u8  sus_bits;
} hi_spi_flash_basic_info;

typedef struct {
    hi_u32 flash_offset;
    hi_u8 *ram_data;
    hi_u32 size;
} spi_flash_prv_addr_info;

typedef struct {
    hi_u8 chip_id[HI_FLASH_CHIP_ID_NUM];  /* flash chip ID */
    hi_u8 freq_high : 2;
    hi_u8 freq_midle : 2;
    hi_u8 freq_low : 2;
    hi_u8 voltage : 2;
} flash_vlt_sfc_info;

#define HI_FLASH_SUPPORT_CHIPS (HI_FLASH_SUPPORT_4K_ERASE | \
                                HI_FLASH_SUPPORT_64K_ERASE | \
                                HI_FLASH_SUPPORT_CHIP_ERASE | \
                                HI_FLASH_SUPPORT_AREA_LOCK_NV | \
                                HI_FLASH_SUPPORT_AREA_LOCK_VOLATILE)
#define HI_FLASH_SUPPORT_DEFAULT (HI_FLASH_SUPPORT_4K_ERASE | \
                                  HI_FLASH_SUPPORT_64K_ERASE | \
                                  HI_FLASH_SUPPORT_CHIP_ERASE)

#define PRODUCT_CFG_FLASH_BLOCK_SIZE        0x1000
/*****************************************************************************/
#define HISFC300_DMA_MAX_SIZE               2048
#define HISFC300_DMA_MAX_MASK               0x7FF

/*****************************************************************************/
#define HISFC300_REG_BUF_SIZE               64
#define HISFC300_REG_BUF_MASK               0x3F

#define HISFC300_BUS_CONFIG2                0x0204
#define HISFC300_BUS_BASE_ADDR_CS1          0x0218
#define HISFC300_BUS_ALIAS_ADDR             0x021C
#define HISFC300_BUS_ALIAS_CS               0x0220
#define HISFC300_CMD_DATABUF64              0x04FC

/***************SFC of Hi1131HV100********************************************/
#define SFC_REG_BASE_ADDRESS                HI_SFC_REG_BASE
#define SFC_BUFFER_BASE_ADDRESS             0x400000

#define SFC_REG_GLOBAL_CONFIG               0x0100
#define SFC_REG_GLOBAL_CONFIG_ADDR_MODE_4B  (1 << 2)
#define SFC_REG_TIMING                      0x0110
#define SFC_REG_GLOBAL_CONFIG_WP_ENABLE     (1<<1)
#define sfc_timing_tshsl(_n)                ((_n) & 0xF)
#define sfc_timing_tshwl(_n)                (((_n) & 0xF) << 4)
#define sfc_timing_tcss(_n)                 (((_n) & 0x7) << 8)
#define sfc_timing_tcsh(_n)                 (((_n) & 0x7) << 12)
#define sfc_timing_trpd(_n)                 (((_n) & 0xFFF) << 16)
#define SFC_REG_INT_RAW_STATUS              0x0120
#define SFC_REG_INT_RAW_STATUS_DMA_DONE     (1<<1)
#define SFC_REG_INT_STATUS                  0x0124
#define SFC_REG_INT_MASK                    0x0128
#define SFC_REG_INT_CLEAR                   0x012C
#define SFC_REG_INT_CLEAR_DMA_DONE          (1<<1)
#define SFC_REG_VERSION                     0x01F8
#define SFC_REG_VERSION_SEL                 0x01FC

#define SFC_REG_BUS_CONFIG1                 0x0200
#define SFC_REG_BUS_CONFIG1_MASK_RD         0x8000ffff
#define SFC_REG_BUS_CONFIG1_MASK_WT         0x7fff0000

#define sfc_bus_config1_wr_ins(_n)          (((_n) & 0xFF) << 22)
#define sfc_bus_config1_rd_ins(_n)          (((_n) & 0xFF) << 8)
#define sfc_bus_config1_rd_prefetch_cnt(_n) (((_n) & 0x3) << 6)
#define sfc_bus_config1_rd_dummy_bytes(_n)  (((_n) & 0x7) << 3)
#define sfc_bus_config1_rd_mem_if_type(_n)  ((_n) & 0x7)
#define SFC_BUS_CONFIG1_RD_ENABLE           ((hi_u32)1 << 31)

#define SFC_REG_BUS_FLASH_SIZE              0x0210
#define SFC_REG_BUS_BASE_ADDR_CS0           0x0214
#define SFC_REG_BUS_BASE_ADDR_CS1           0x0218

#define SFC_REG_BUS_DMA_CTRL                0X0240
#define SFC_BUS_DMA_CTRL_START              (1<<0)
#define sfc_bus_dma_ctrl_read(_dir)         ((_dir) << 1)
#define sfc_bus_dma_ctrl_cs(_cs)            (((_cs) & 0x01) << 4)
#define SFC_REG_BUS_DMA_MEM_SADDR           0X0244 /* DMA DDR start address R */
#define SFC_REG_BUS_DMA_FLASH_SADDR         0X0248
#define SFC_REG_BUS_DMA_LEN                 0x024C
#define SFC_REG_BUS_DMA_AHB_CTRL            0X0250
#define SFC_BUS_DMA_AHB_CTRL_INCR4_EN       (1<<0)
#define SFC_BUS_DMA_AHB_CTRL_INCR8_EN       (1<<1)
#define SFC_BUS_DMA_AHB_CTRL_INCR16_EN      (1<<2)

#define SFC_REG_CMD_CONFIG                  0x0300
#define sfc_cmd_config_mem_if_type(_n)      (((_n) & 0x07) << 17)
#define sfc_cmd_config_data_cnt(_n)         ((((_n) - 1) & HISFC300_REG_BUF_MASK) << 9)
#define SFC_CMD_CONFIG_RW                   (1<<8)
#define SFC_CMD_CONFIG_DATA_EN              (1<<7)
#define sfc_cmd_config_dummy_byte_cnt(_n)   (((_n) & 0x07) << 4)
#define SFC_CMD_CONFIG_ADDR_EN              (1<<3)
#define SFC_CMD_CONFIG_SEL_CS               (0x01 << 1)
#define SFC_CMD_CONFIG_START                (1 << 0)
#define SFC_REG_CMD_INS                     0x0308

#define SFC_REG_CMD_ADDR                    0x030C
#define SFC_CMD_ADDR_MASK                   0x3FFFFFFF
#define    SFC_REG_CMD_DATABUF1             0x0400

#define SPI_SR3_DRV_MASK        0x3

#define SFC_ERASE_OPT_MAX_NUM   4

typedef enum {
    SPI_SR3_DRV_100PCT = 0,
    SPI_SR3_DRV_75PCT,
    SPI_SR3_DRV_50PCT,
    SPI_SR3_DRV_25PCT,
    SPI_SR3_DRV_MAX,
} hi_flash_drv_strength;

#define SFC_CMD_WRITE (0<<8)
#define SFC_CMD_READ  (1<<8)

typedef enum {
    HI_FLASH_CHECK_PARAM_OPT_READ,
    HI_FLASH_CHECK_PARAM_OPT_WRITE,
    HI_FLASH_CHECK_PARAM_OPT_ERASE,
} hi_flash_check_param_opt;

typedef struct spi_flash_ctrl {
    hi_bool init;
    hi_bool sus_enable;
    hi_bool limit_0_to_1;
    hi_u8 reserve;
    hi_spi_flash_basic_info basic_info;
    spi_flash_operation opt_read;
    spi_flash_operation opt_write;
    spi_flash_operation array_opt_erase[SFC_ERASE_OPT_MAX_NUM];
    hi_u32 chip_size;
    hi_u32 erase_size;
    hi_u32 dma_ram_size;
    hi_u8 *dma_ram_buffer;
    hi_u8 *back_up_buf;
    hi_u32 (*read)(struct spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 read_size,
                   hi_void* ram_addr, hi_bool b_is_crash);
    hi_u32 (*write)(struct spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 write_size,
                    hi_void* ram_addr, hi_bool b_is_crash);
    hi_u32 (*erase)(struct spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 erase_size, hi_bool is_crash);
    hi_bool (*is_busy)(hi_void);
    hi_u32 mutex_handle;
    hi_pvoid usr_data;
} hi_spi_flash_ctrl;

/*****************************************************************************/
#define hisfc_read(_reg) \
    reg_read_val(SFC_REG_BASE_ADDRESS +(_reg))

#define hisfc_write(_reg, _value) \
    reg_write32(SFC_REG_BASE_ADDRESS + (_reg), (_value))

HI_EXTERN hi_u32 spi_flash_read_chip_id(hi_u8 *chip_id, hi_u8 id_len);
HI_EXTERN hi_u32 spi_flash_configure_driver_strength(hi_flash_drv_strength drv_strength);

HI_EXTERN hi_u32 spif_map_chipsize(hi_u32 chip_size);
HI_EXTERN hi_u32 spif_dma_read(hi_spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 read_size,
                               hi_void* ram_addr, hi_bool is_crash);
HI_EXTERN hi_u32 spif_reg_erase(hi_spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 erase_size, hi_bool is_crash);
HI_EXTERN hi_u32 spif_dma_write(hi_spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 write_size,
                                hi_void* ram_addr, hi_bool is_crash);
HI_EXTERN hi_bool spif_is_busy(hi_void);
HI_EXTERN hi_u32 spi_flash_basic_info_probe(HI_INOUT hi_spi_flash_ctrl* spif_ctrl, hi_u8 *chip_id,
                                            hi_u8 id_len, hi_spi_flash_basic_info *spi_info_tbl, hi_u32 tbl_size);
HI_EXTERN hi_u32 flash_write_prv(hi_spi_flash_ctrl* spif_ctrl, const spi_flash_prv_addr_info *info, hi_bool do_erase,
                                 hi_bool is_crash);
HI_EXTERN hi_u32 flash_erase_prv(hi_spi_flash_ctrl* spif_ctrl, hi_u32 flash_addr, hi_u32 size, hi_bool is_crash);
HI_EXTERN hi_u32 flash_read_prv(hi_spi_flash_ctrl* spif_ctrl, const spi_flash_prv_addr_info *info, hi_bool is_crash);
HI_EXTERN hi_u32 flash_suspend_prv_default(const hi_spi_flash_ctrl *spif_ctrl, hi_u32 timeout);
HI_EXTERN hi_void flash_resume_prv_default(const hi_spi_flash_ctrl *spif_ctrl, hi_u32 timeout);
HI_EXTERN hi_void spif_send_cmd(hi_u8 cmd);
HI_EXTERN hi_u32 spi_flash_read_reg(hi_u8 cmd, hi_u8 *data, hi_u8 data_len);
HI_EXTERN hi_u32 spi_flash_write_reg(hi_u8 cmd, const hi_u8 *data, hi_u8 data_len);
HI_EXTERN hi_u32 sfc_check_para(const hi_spi_flash_ctrl* spif_ctrl, hi_u32 addr, hi_u32 size,
                                hi_flash_check_param_opt opt);
HI_EXTERN hi_u32 flash_ioctl(const hi_spi_flash_ctrl* spif_ctrl, hi_u16 cmd, hi_void* data);
HI_EXTERN hi_u32 spi_flash_enable_quad_mode(hi_void);
HI_EXTERN hi_void spif_bus_config(const spi_flash_operation* spi_operation, hi_u8 cmd, hi_bool blto_read);
HI_EXTERN hi_void spif_register_irq_soft_patch(hi_void_callback prepare, hi_void_callback resume);
HI_EXTERN hi_void spif_wait_config_start(hi_void);
HI_EXTERN hi_u32 spif_write_enable(hi_bool is_crash);
HI_EXTERN hi_u32 spif_wait_ready(hi_bool is_crash, hi_u8 val, hi_u8 bit_mask);


HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_standard_read;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_fast_read;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_fast_dual_out_read;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_fast_quad_out_read;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_fast_quad_eb_out_read;

HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_page_program_write;

HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_sector_erase;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_32k_erase;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_64k_erase;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_chip_erase1;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_chip_erase2;
HI_EXTERN HI_CONST hi_spi_flash_basic_info g_flash_default_info_tbl[HI_FLASH_DEFAULT_TYPE_NUM];

#ifdef HI_FLASH_SUPPORT_REF_VBAT
#ifdef HI_FLASH_SUPPORT_UPDATE_SFC_FREQ
hi_u32 sfc_config_get_update_time(hi_u32 *time_ms);
hi_u32 sfc_config_set_update_time(hi_u32 time_ms);
hi_void sfc_config_set_voltage_threshold_increment(hi_u8 voltage_increment);
hi_u32 sfc_config_get_voltage_threshold_increment(hi_u8 *voltage_increment);

#endif
#endif

/* flash protect */
#define PROTECT_TIMEOUT_1    6000
#define PROTECT_TIMEOUT_2    3600000
#define PROTECT_TIMEOUT_AUTO 0xFFFFFFFF
#define PROTECT_FLASH_ALL    0x6  /* 0x6: 000110 */

#ifdef HI_BOARD_ASIC
/* if support flash protect:#define HI_FLASH_SUPPORT_FLASH_PROTECT */
#define HI_FLASH_SUPPORT_FLASH_PROTECT
#endif

typedef enum {
    HI_FLASH_PROTECT_TYPE_1 = 0x0,
    HI_FLASH_PROTECT_TYPE_2,
    HI_FLASH_PROTECT_NONE,
    HI_FLASH_PROTECT_TYPE_MAX,
}hi_flash_protect_type;

typedef struct {
    hi_u32 default_type : 6;
    hi_u32 enable : 1;
    hi_u32 is_volatile : 1;
    hi_u32 init : 1;
    hi_u32 current_block : 13;
    hi_u32 reserve : 10;
    hi_u32 timer_timeout;
    hi_u32 timer_handle;
} hi_flash_protect_ctrl;

typedef struct {
    hi_u32 cmp_bp : 6;
    hi_u32 block : 13;
    hi_u32 reseve : 13;
} hi_flash_protect_size;

typedef struct {
    hi_u32 support_flash_protect : 1;
    hi_u32 protect_all : 1;
    hi_u32 reserve : 30;
    hi_u32 (*protect_all_area)(hi_void);
} support_flash_protect;
support_flash_protect *flash_get_support_flash_protect_info(hi_void);
hi_spi_flash_ctrl *flash_get_spi_flash_ctrl_info(hi_void);

#ifdef HI_FLASH_SUPPORT_FLASH_PROTECT
hi_u32 flash_protect(hi_u32 flash_offset, hi_u32 size, hi_u32 timeout, hi_bool is_volatile);
hi_u32 flash_protect_set_protect(hi_u8 cmp_bp, hi_bool is_volatile, hi_bool forced_write);
#endif
hi_u32 hi_flash_protect_init(hi_flash_protect_type type);
hi_u32 hi_flash_protect_deinit(hi_void);
hi_u32 hi_flash_protect_enable(hi_bool enable);

hi_u32 flash_lock(hi_void);
hi_u32 flash_unlock(hi_void);
hi_u8 get_flash_op_during_flash(void); /* flash option is during crash */

hi_u32 hi_flash_write_fs(const hi_u32 flash_offset, hi_u32 size, const hi_u8 *ram_data, hi_bool do_erase);

#ifdef HI_FLASH_SUPPORT_COUNT_DEBUG

#define SECTOR_SIZE 4096
#define SECTOR_NUM  512
#define FLASH_OPT_RECORD_SIZE 2048
typedef struct {
    hi_u16 write_times[SECTOR_NUM];
    hi_u16 erase_times[SECTOR_NUM];
} hi_flash_opt_record; /* 2KB */

hi_void hi_flash_record_opt_init(hi_void);
hi_flash_opt_record* hi_flash_get_opt_record(hi_void);
#endif

hi_void hi_flash_record_flash_opt(hi_void);

#endif
