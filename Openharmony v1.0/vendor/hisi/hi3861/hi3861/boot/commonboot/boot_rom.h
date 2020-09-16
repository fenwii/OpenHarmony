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

#ifndef _BOOT_ROM_H_
#define _BOOT_ROM_H_
#include <hi_types.h>
#include <hi_cipher.h>

#define BOOTLOADER_FLASH_HEAD_ADDR      0x00400000

/* This register is used internally and cannot be used externally. */
#define GLB_CTL_GP_REG0_REG                 (GLB_CTL_BASE + 0x10)
#define GLB_CTL_GP_REG1_REG                 (GLB_CTL_BASE + 0x14)
#define GLB_CTL_GP_REG2_REG                 (GLB_CTL_BASE + 0x18)
#define GLB_CTL_GP_REG3_REG                 (GLB_CTL_BASE + 0x1C)
#define PMU_CMU_CTL_GP_REG0_REG             (PMU_CMU_CTL_BASE + 0x010)
#define PMU_CMU_CTL_GP_REG1_REG             (PMU_CMU_CTL_BASE + 0x014)
#define PMU_CMU_CTL_GP_REG2_REG             (PMU_CMU_CTL_BASE + 0x018)
#define PMU_CMU_CTL_GP_REG3_REG             (PMU_CMU_CTL_BASE + 0x01C)
#define CLDO_CTL_GEN_REG0                   (CLDO_CTL_RB_BASE + 0x10)
#define CLDO_CTL_GEN_REG1                   (CLDO_CTL_RB_BASE + 0x14)
#define CLDO_CTL_GEN_REG2                   (CLDO_CTL_RB_BASE + 0x18)
#define CLDO_CTL_GEN_REG3                   (CLDO_CTL_RB_BASE + 0x1C)

/* heap module */
hi_void rom_boot_malloc_init(hi_u32 heap_start_addr, hi_u32 heap_end_addr, hi_u32 check_sum);
hi_void *rom_boot_malloc(hi_u32 size);
hi_u32  rom_boot_free(hi_void *addr);

/* reset module */
#define RESET_DELAY_MS              3
hi_void reset(hi_void);
hi_void global_reset(hi_void);

/* secure module */
HI_EXTERN hi_cipher_ecc_param g_brain_pool_p256r1_verify;

/* flash driver module */
#define FEATURE_SUPPORT_FLASH_PROTECT

#define flash_info_print(fmt, ...)
#define SPI_QE_EN    0x02 /* QE Bit Enable */
#define SPI_QE_EN_MX 0x40 /* QE Bit Enable(temp for FPGA MX) */

#define SPI_CMD_WREN 0x06 /* Write Enable */
/* ----------------------------------------------------------------------------- */
#define SPI_CMD_SE_4K  0x20 /* 4KB sector Erase */
#define SPI_CMD_SE_32K 0x52 /* 32KB sector Erase */
#define SPI_CMD_SE     0xD8 /* 64KB Sector Erase */
#define SPI_CMD_CE1    0xC7 /* chip erase */
#define SPI_CMD_CE2    0x60 /* chip erase */

/* ----------------------------------------------------------------------------- */
#define SPI_CMD_WRSR1 0x01 /* Write Status Register */

#define SPI_CMD_WRSR2 0x31 /* Write Status Register-2 */
#define SPI_CMD_RDSR2 0x35 /* Read Status Register-2 */

#define SPI_CMD_WRSR3 0x11 /* Write Status Register-3 */
#define SPI_CMD_RDSR3 0x15 /* Read Status Register-3 */

#define SPI_CMD_RDID 0x9F /* Read Identification */

/* read status register. */
#define SPI_CMD_RDSR 0x05
#define SPI_CMD_VSR_WREN 0x50 /* write volatile SR reg enable */

/* write status/configuration register. */
#define SPI_CMD_WRSRCR 0x01

/* ----------------------------------------------------------------------------- */
#define SPI_CMD_SR_WIPN 0 /* Write in Progress */
#define SPI_CMD_SR_WIP  1 /* Write in Progress */
#define SPI_CMD_SR_WEL  2 /* Write Enable Latch */

#define SPI_SR_BIT_WIP (1 << 0) /* Write in Progress */
#define SPI_SR_BIT_WEL (1 << 1) /* Write Enable Latch */

#define FLASH_DMA_BUF_LEN  256
#define FLASH_DMA_RAM_SIZE 1024
#define HI_FLASH_DEFAULT_TYPE_NUM   8
#define HI_FLASH_CHIP_ID_NUM        3
#define HI_FLASH_CAPACITY_ID        2
typedef struct {
    hi_u32 cmd : 8;
    hi_u32 iftype : 3;
    hi_u32 dummy : 3;
    hi_u32 size : 18;
} spi_flash_operation;

typedef enum {
    HI_FLASH_SUPPORT_4K_ERASE = 0x1,              /* Flash 4K erasing */
    HI_FLASH_SUPPORT_32K_ERASE = 0x2,             /* Flash 32K erasing  */
    HI_FLASH_SUPPORT_64K_ERASE = 0x4,             /* Flash 64K erasing */
    HI_FLASH_SUPPORT_CHIP_ERASE = 0x8,            /* Flash full-chip erasing */
    HI_FLASH_SUPPORT_AREA_LOCK_NV = 0x10,         /* Non-volatile flash area protection */
    HI_FLASH_SUPPORT_AREA_LOCK_VOLATILE = 0x20,   /* Flash volatile area protection */
    HI_FLASH_SUPPORT_INDIVIDUAL_LOCK = 0x40,      /* Independent flash block protection */
    HI_FLASH_VLT_INFLUENCE_FREQ = 0x100,
    HI_FLASH_SUPPORT_MASK = 0xFFFF,               /* Mask */
} hi_spi_flash_chip_attribute;

typedef struct {
    hi_char *chip_name;
    hi_u8  chip_id[HI_FLASH_CHIP_ID_NUM];
    hi_u8  freq_read;
    hi_u8  freq_lowpower;
    hi_u8  freq_hpm;
    hi_u16 chip_attribute;
} hi_spi_flash_basic_info;

#define HI_FLASH_SUPPORT_CHIPS (HI_FLASH_SUPPORT_4K_ERASE | \
                               HI_FLASH_SUPPORT_64K_ERASE | \
                               HI_FLASH_SUPPORT_CHIP_ERASE | \
                               HI_FLASH_SUPPORT_AREA_LOCK_NV | \
                               HI_FLASH_SUPPORT_AREA_LOCK_VOLATILE)
#define HI_FLASH_SUPPORT_DEFAULT    (HI_FLASH_SUPPORT_4K_ERASE | \
                                   HI_FLASH_SUPPORT_64K_ERASE | \
                                   HI_FLASH_SUPPORT_CHIP_ERASE)

#define PRODUCT_CFG_FLASH_BLOCK_SIZE 0x1000
/*****************************************************************************/
#define HISFC300_DMA_MAX_SIZE 2048
#define HISFC300_DMA_MAX_MASK 0x7FF

/*****************************************************************************/
#define HISFC300_REG_BUF_SIZE 64
#define HISFC300_REG_BUF_MASK 0x3F

#define HISFC300_BUS_CONFIG2       0x0204
#define HISFC300_BUS_BASE_ADDR_CS1 0x0218
#define HISFC300_BUS_ALIAS_ADDR    0x021C
#define HISFC300_BUS_ALIAS_CS      0x0220
#define HISFC300_CMD_DATABUF64     0x04FC

#define SFC_REG_BASE_ADDRESS    HI_SFC_REG_BASE
#define SFC_BUFFER_BASE_ADDRESS 0x400000

#define SFC_REG_GLOBAL_CONFIG               0x0100
#define SFC_REG_GLOBAL_CONFIG_ADDR_MODE_4B  (1 << 2)
#define SFC_REG_TIMING                      0x0110
#define SFC_REG_GLOBAL_CONFIG_WP_ENABLE     (1 << 1)
#define sfc_timing_tshsl(_n)                ((_n) & 0xF)
#define sfc_timing_tshwl(_n)                (((_n) & 0xF) << 4)
#define sfc_timing_tcss(_n)                 (((_n) & 0x7) << 8)
#define sfc_timing_tcsh(_n)                 (((_n) & 0x7) << 12)
#define sfc_timing_trpd(_n)                 (((_n) & 0xFFF) << 16)
#define SFC_REG_INT_RAW_STATUS              0x0120 /* Raw interrupt status register */
#define SFC_REG_INT_RAW_STATUS_DMA_DONE     (1 << 1)
#define SFC_REG_INT_STATUS                  0x0124
#define SFC_REG_INT_MASK                    0x0128
#define SFC_REG_INT_CLEAR                   0x012C
#define SFC_REG_INT_CLEAR_DMA_DONE          (1 << 1)
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

#define SFC_REG_BUS_FLASH_SIZE    0x0210
#define SFC_REG_BUS_BASE_ADDR_CS0 0x0214
#define SFC_REG_BUS_BASE_ADDR_CS1 0x0218

#define SFC_REG_BUS_DMA_CTRL           0X0240
#define SFC_BUS_DMA_CTRL_START         (1 << 0)
#define sfc_bus_dma_ctrl_read(_dir)    ((_dir) << 1)
#define sfc_bus_dma_ctrl_cs(_cs)       (((_cs) & 0x01) << 4)
#define SFC_REG_BUS_DMA_MEM_SADDR      0X0244 /* DMA DDR start address R */
#define SFC_REG_BUS_DMA_FLASH_SADDR    0X0248
#define SFC_REG_BUS_DMA_LEN            0x024C
#define SFC_REG_BUS_DMA_AHB_CTRL       0X0250
#define SFC_BUS_DMA_AHB_CTRL_INCR4_EN  (1 << 0)
#define SFC_BUS_DMA_AHB_CTRL_INCR8_EN  (1 << 1)
#define SFC_BUS_DMA_AHB_CTRL_INCR16_EN (1 << 2)

#define SFC_REG_CMD_CONFIG                0x0300
#define sfc_cmd_config_mem_if_type(_n)    (((_n) & 0x07) << 17)
#define sfc_cmd_config_data_cnt(_n)       ((((_n) - 1) & HISFC300_REG_BUF_MASK) << 9)
#define SFC_CMD_CONFIG_RW                 (1 << 8)
#define SFC_CMD_CONFIG_DATA_EN            (1 << 7)
#define sfc_cmd_config_dummy_byte_cnt(_n) (((_n) & 0x07) << 4)
#define SFC_CMD_CONFIG_ADDR_EN            (1 << 3)
#define SFC_CMD_CONFIG_SEL_CS             (0x01 << 1)
#define SFC_CMD_CONFIG_START              (1 << 0)
#define SFC_REG_CMD_INS                   0x0308

#define SFC_REG_CMD_ADDR     0x030C
#define SFC_CMD_ADDR_MASK    0x3FFFFFFF
#define SFC_REG_CMD_DATABUF1 0x0400

#define SPI_SR3_DRV_MASK 0x3

#define SFC_ERASE_OPT_MAX_NUM 4

typedef enum {
    SPI_SR3_DRV_100PCT = 0,
    SPI_SR3_DRV_75PCT,
    SPI_SR3_DRV_50PCT,
    SPI_SR3_DRV_25PCT,
    SPI_SR3_DRV_MAX,
} hi_flash_drv_strength;

#define SFC_CMD_WRITE (0 << 8)
#define SFC_CMD_READ  (1 << 8)

typedef enum {
    HI_FLASH_CHECK_PARAM_OPT_READ,
    HI_FLASH_CHECK_PARAM_OPT_WRITE,
    HI_FLASH_CHECK_PARAM_OPT_ERASE,
} hi_flash_check_param_opt;

typedef struct spi_flash_ctrl {
    hi_u32 is_inited;
    hi_spi_flash_basic_info basic_info;
    spi_flash_operation opt_read;
    spi_flash_operation opt_write;
    spi_flash_operation array_opt_erase[SFC_ERASE_OPT_MAX_NUM];
    hi_u32 chip_size;
    hi_u32 erase_size;
    hi_u32 dma_ram_size;
    hi_u8 *dma_ram_buffer;
    hi_u8 *back_up_buf;
    hi_u32(*read)(struct spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr,
        hi_u32 read_size, hi_void *ram_addr, hi_bool is_crash);
    hi_u32(*write)(struct spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr,
        hi_u32 write_size, hi_void *ram_addr, hi_bool is_crash);
    hi_u32(*erase)(struct spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr,
        hi_u32 erase_size, hi_bool is_crash);
    hi_u32 mutex_handle;
    hi_pvoid usr_data;
} hi_spi_flash_ctrl;

/*****************************************************************************/
#define hisfc_read(_reg) \
    hi_reg_read_val32(SFC_REG_BASE_ADDRESS + (_reg))

#define hisfc_write(_reg, _value) \
    hi_reg_write(SFC_REG_BASE_ADDRESS + (_reg), (_value))


HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_fast_quad_out_read;
HI_EXTERN HI_CONST spi_flash_operation g_spi_opt_fast_quad_eb_out_read;

HI_EXTERN HI_CONST hi_spi_flash_basic_info g_flash_default_info_tbl[];

hi_u32 spi_flash_read_chip_id(hi_u8 *chip_id, hi_u8 chip_id_len);
hi_u32 spi_flash_configure_driver_strength(hi_flash_drv_strength drv_strength);

hi_u32 spif_map_chipsize(hi_u32 chip_size);
hi_u32 spif_dma_read(hi_spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr, hi_u32 read_size, hi_void *ram_addr,
                     hi_bool is_crash);
hi_u32 spif_reg_erase(hi_spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr, hi_u32 erase_size, hi_bool is_crash);
hi_u32 spif_dma_write(hi_spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr, hi_u32 write_size, hi_void *ram_addr,
                      hi_bool is_crash);
hi_u32 spi_flash_read_reg(hi_u8 cmd, hi_u8 *data, hi_u8 data_len);
hi_u32 spi_flash_write_reg(hi_u8 cmd, const hi_u8 *data, hi_u8 data_len);
hi_void spif_config(const spi_flash_operation *spi_operation, hi_u8 cmd, hi_bool read);
hi_u32 spi_flash_enable_quad_mode_mx(hi_void);
hi_u32 spi_flash_enable_quad_mode(hi_void);
hi_void spif_wait_config_start(hi_void);
hi_u32 spif_write_enable(hi_bool is_crash);
hi_u32 spif_wait_ready(hi_bool is_crash, hi_u8 val, hi_u8 bit_mask);

hi_u32 spi_flash_basic_info_probe(hi_spi_flash_ctrl *spif_ctrl, hi_u8 *chip_id,
                                  hi_u8 id_len, hi_spi_flash_basic_info *spi_info_tbl, hi_u32 tbl_size);
hi_u32 flash_write_prv(hi_spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr, const hi_u8 *ram_addr, hi_u32 size,
                       hi_bool do_erase);
hi_u32 flash_erase_prv(hi_spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr, hi_u32 size);
hi_u32 flash_read_prv(hi_spi_flash_ctrl *spif_ctrl, hi_u32 flash_addr, hi_u8 *data, hi_u32 size);
hi_u32 spi_flash_get_size(const hi_u8 *chip_id);
hi_u32 sfc_check_para(const hi_spi_flash_ctrl *spif_ctrl, hi_u32 addr, hi_u32 size, hi_flash_check_param_opt opt);
hi_u32 flash_protect_set_protect(hi_u8 cmp_bp, hi_bool is_volatile);

typedef hi_u32 (*flash_init_func)(hi_void);
typedef hi_u32 (*flash_read_func)(hi_u32 flash_addr, hi_u32 flash_read_size, hi_u8 *p_flash_read_data);
typedef hi_u32 (*flash_write_func)(hi_u32 flash_addr, hi_u32 flash_write_size,
                                   const hi_u8 *p_flash_write_data, hi_bool do_erase);
typedef hi_u32 (*flash_erase_func)(hi_u32 flash_addr, hi_u32 flash_erase_size);

typedef struct {
    flash_init_func init;
    flash_read_func read;
    flash_write_func write;
    flash_erase_func erase;
} hi_flash_cmd_func;
HI_EXTERN hi_flash_cmd_func g_flash_cmd_funcs;

hi_u32 hi_cmd_regist_flash_cmd(const hi_flash_cmd_func *funcs);

#endif
