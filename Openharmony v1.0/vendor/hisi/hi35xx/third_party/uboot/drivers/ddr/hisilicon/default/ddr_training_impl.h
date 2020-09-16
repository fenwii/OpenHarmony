/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *

 */

#ifndef DDR_TRAINING_IMPL_H
#define DDR_TRAINING_IMPL_H

#ifndef __ASSEMBLY__

#include "ddr_training_custom.h"
#include "ddr_training_internal_config.h"
#include "ddr_interface.h"

/****** special config define*******************************************/
#ifdef DDR_DATAEYE_NORMAL_NOT_ADJ_CONFIG
/* Adjust dataeye window consume a lot of time, disable it will make boot
 * faster.
 * NOTE: The WDQ Phase and RDQS MUST be config a good value in the init table
 * to avoid window trend to one side.
 */
#define DDR_DATAEYE_NORMAL_ADJUST   (DDR_FALSE)
#else
#define DDR_DATAEYE_NORMAL_ADJUST   (DDR_TRUE)
#endif
/* MUST adjust dataeye window after HW or MPR training */
#define DDR_DATAEYE_ABNORMAL_ADJUST       (DDR_TRUE)

/****** ddr training item bypass mask define ****************************/
#define DDR_BYPASS_PHY0_MASK        0x1 /* [0]PHY0 training */
#define DDR_BYPASS_PHY1_MASK        0x2 /* [1]PHY1 training */
#define DDR_BYPASS_WL_MASK          0x10 /* [4]Write leveling */
#define DDR_BYPASS_GATE_MASK        0x100 /* [8]Gate training */
#define DDR_BYPASS_DATAEYE_MASK     0x10000 /* [16]Dataeye training */
#define DDR_BYPASS_PCODE_MASK       0x40000 /* [18]Pcode training */
#define DDR_BYPASS_HW_MASK          0x100000 /* [20]Hardware read training */
#define DDR_BYPASS_MPR_MASK         0x200000 /* [21]MPR training */
#define DDR_BYPASS_AC_MASK          0x400000 /* [22]AC training */
#define DDR_BYPASS_LPCA_MASK        0x800000 /* [23]LPDDR CA training */
#define DDR_BYPASS_VREF_HOST_MASK   0x1000000 /* [24]Host Vref training */
#define DDR_BYPASS_VREF_DRAM_MASK   0x2000000 /* [25]DRAM Vref training */
#define DDR_BYPASS_DCC_MASK         0x08000000 /* [27]DCC training */
#define DDR_BYPASS_DATAEYE_ADJ_MASK 0x10000000 /* [28]Dataeye adjust */
#define DDR_BYPASS_WL_ADJ_MASK      0x20000000 /* [29]WL write adjust */
#define DDR_BYPASS_HW_ADJ_MASK      0x40000000 /* [30]HW read adjust */
#define DDR_BYPASS_ALL_MASK         0xffffffff /* all bypass */

/****** ddr read/write define **********************************************/
unsigned int ddr_read(unsigned addr);
void ddr_write(unsigned val, unsigned addr);

/****** common define **********************************************/
/* special ddrt need special read and write register */
#ifdef DDR_DDRT_SPECIAL_CONFIG
#define DDRT_REG_READ(addr)        ddr_ddrt_read(addr)
#define DDRT_REG_WRITE(val, addr)  ddr_ddrt_write(val, addr)
#else
#define DDRT_REG_READ(addr)        ddr_read(addr)
#define DDRT_REG_WRITE(val, addr)  ddr_write(val, addr)
#endif

#define DDR_MODE_READ                     (1 << 0)
#define DDR_MODE_WRITE                    (1 << 1)

#define DDR_ENTER_SREF                    (1 << 0)
#define DDR_EXIT_SREF                     (1 << 1)

/* DSB to make sure the operation is complete */
#ifndef DDR_ASM_DSB
#if (__LINUX_ARM_ARCH__ >= 8)
#define DDR_ASM_DSB()                     { __asm__ __volatile__("dsb sy"); }
#else
#define DDR_ASM_DSB()                     { __asm__ __volatile__("dsb"); }
#endif
#endif

#define DDR_HWR_WAIT_TIMEOUT	          0xffffffff
#define DDR_SFC_WAIT_TIMEOUT	          (1000)
#define DDR_LPCA_WAIT_TIMEOUT	          (1000)

#ifdef CFG_EDA_VERIFY
#define DDR_AUTO_TIMING_DELAY	          (1)
#else
#define DDR_AUTO_TIMING_DELAY	          (1000)
#endif

#define DDR_FIND_DQ_BOTH                  (1 << 0) /* find a valid value*/
/* x is valid, (x-1) is invalid*/
#define DDR_FIND_DQ_LEFT                  (1 << 1)
/* x is valid, (x+1) is invalid*/
#define DDR_FIND_DQ_RIGHT                 (1 << 2)

#define DDR_VREF_DRAM_VAL_MAX             (0x32)        /* 92.50%*VDDIO */
#define DDR_VREF_DRAM_VAL_MIN             (0x0)         /* 60.00%*VDDIO */

#define DDR_PHY_REG_DQ_NUM                4  /* one register has 4 DQ BDL */

#define DDR_PHY_CA_MAX                    10
#define DDR_PHY_CA_REG_MAX                (DDR_PHY_CA_MAX >> 1)

#define DDR_TRUE                          1
#define DDR_FALSE                         0

#define DDR_WIN_MIDDLE                    (1 << 0)
#define DDR_WIN_LEFT                      (1 << 1)
#define DDR_WIN_RIGHT                     (1 << 2)

#define DDR_DELAY_PHASE                   1
#define DDR_DELAY_BDL                     2

#ifndef DDR_DATAEYE_WIN_NUM
/* Dateeye window number. More bigger more slower when Vref training. */
#define DDR_DATAEYE_WIN_NUM               8
#endif
#ifndef DDR_LOOP_TIMES_LMT
/* Dataeye DQ deskew times for best result. More bigger more slower. */
#define DDR_LOOP_TIMES_LMT                1
#endif
#ifndef DDR_VREF_COMPARE_TIMES
/* Compare times when find best vref value. More bigger more slower. */
#define DDR_VREF_COMPARE_TIMES            3
#endif
#ifndef DDR_MPR_RDQS_FIND_TIMES
/* MPR Find first start rdqs times. More bigger, start rdqs more bigger. */
#define DDR_MPR_RDQS_FIND_TIMES           3
#endif
#ifndef DDR_VREF_COMPARE_STEP
/* Compare step when begin to find. More bigger, more mistake, more stable. */
#define DDR_VREF_COMPARE_STEP             3
#endif

#define DDR_DATAEYE_RESULT_MASK           0xffff
#define DDR_DATAEYE_RESULT_BIT            16

#define DDR_WL_BDL_STEP                   2 /* wl bdl step */
#define DDR_GATE_BDL_STEP                 2 /* gate bdl step */
#define DDR_DQS_ADJ_STEP                  1 /* WR/RD DQS adjust step */

#define DDR_DDRT_MODE_GATE                (1 << 0)
#define DDR_DDRT_MODE_DATAEYE             (1 << 1)

#define DDR_CHECK_TYPE_DDRT               (1 << 0)
#define DDR_CHECK_TYPE_MPR                (1 << 1)

#define DDR_MPR_BYTE_MASK                 0xff
#define DDR_MPR_BIT_MASK                  0x1
#define DDR_MPR_BYTE_BIT                  16          /* 16 bit (2 byte) */

#define DDR_PHY_AC_TEST_VAL0              0x0
#define DDR_PHY_AC_TEST_VAL1              0xffffffff
#define DDR_PHY_AC_TEST_VAL2              0x55555555
#define DDR_PHY_AC_TEST_VAL3              0xaaaaaaaa

/*******log define ***********************************************/
#if defined(DDR_TRAINING_CMD) && defined(DDR_TRAINING_LOG_CONFIG)
#define DDR_INFO(fmt...)     ddr_training_log(__func__, DDR_LOG_INFO, fmt)
#define DDR_DEBUG(fmt...)    ddr_training_log(__func__, DDR_LOG_DEBUG, fmt)
#define DDR_WARNING(fmt...)  ddr_training_log(__func__, DDR_LOG_WARNING, fmt)
#define DDR_ERROR(fmt...)    ddr_training_log(__func__, DDR_LOG_ERROR, fmt)
#define DDR_FATAL(fmt...)    ddr_training_log(__func__, DDR_LOG_FATAL, fmt)
#else
#define DDR_INFO(fmt...)
#define DDR_DEBUG(fmt...)
#define DDR_WARNING(fmt...)
#define DDR_ERROR(fmt...)
#define DDR_FATAL(fmt...)
#endif /* DDR_TRAINING_CMD && DDR_TRAINING_LOG_CONFIG */

/* [11:0] Error type */
/* 0x00000001 Write Leveling error */
#define DDR_ERR_WL                        (1 << 0)
/* 0x00000002 Hardware Gatining error */
#define DDR_ERR_HW_GATING                 (1 << 1)
/* 0x00000004 Sofeware Gatining error */
#define DDR_ERR_GATING                    (1 << 2)
/* 0x00000008 DDRT test time out */
#define DDR_ERR_DDRT_TIME_OUT             (1 << 3)
/* 0x00000010 Hardware read dataeye error */
#define DDR_ERR_HW_RD_DATAEYE			  (1 << 4)
/* 0x00000020 MPR error */
#define DDR_ERR_MPR                       (1 << 5)
/* 0x00000040 Dataeye error */
#define DDR_ERR_DATAEYE                   (1 << 6)
/* 0x00000080 LPDDR CA error */
#define DDR_ERR_LPCA                      (1 << 7)

/* [13:12] Error phy */
/* 0x00001000 PHY0 training error */
#define DDR_ERR_PHY0                      (1 << 12)
/* 0x00002000 PHY1 training error */
#define DDR_ERR_PHY1                      (1 << 13)

#define DDR_ERR_BYTE_BIT                  24 /* [28:24] Error DQ0-31 */
#define DDR_ERR_DQ_BIT                    20 /* [22:20] Error Byte0-3 */

/*******data define*********************************************/
#define GET_BYTE_NUM(cfg)  (cfg->phy[cfg->phy_idx].dmc[cfg->dmc_idx].byte_num)


#ifndef DDR_RELATE_REG_DECLARE
struct tr_custom_reg {
};
#endif

struct dmc_cfg_sref_st {
	unsigned int val[DDR_DMC_PER_PHY_MAX];
};

struct ddr_bdl_st {
	unsigned int bdl[DDR_PHY_BYTE_MAX];
};

struct ddr_timing_st {
	unsigned int val[DDR_DMC_PER_PHY_MAX];
};

struct rdqs_data_st {
	struct ddr_bdl_st origin;
	struct ddr_bdl_st rank[DDR_RANK_NUM];
};

struct ddr_delay_st {
	unsigned int phase[DDR_PHY_BYTE_MAX];
	unsigned int bdl[DDR_PHY_BYTE_MAX];
};

struct tr_relate_reg {
	unsigned int auto_ref_timing;
	unsigned int power_down;
	unsigned int dmc_scramb;
	unsigned int dmc_scramb_cfg;
	unsigned int misc_scramb;
	unsigned int ac_phy_ctl;
	unsigned int swapdfibyte_en;
	struct tr_custom_reg custom;
	struct ddr_ddrc_data ddrc;
};

struct tr_dq_data {
	unsigned int dq03[DDR_PHY_BYTE_MAX]; /* DQ0-DQ3 BDL */
	unsigned int dq47[DDR_PHY_BYTE_MAX]; /* DQ4-DQ7 BDL */
	unsigned int rdqs[DDR_PHY_BYTE_MAX];  /* RDQS */
	unsigned int rdm[DDR_PHY_BYTE_MAX];  /* RDM */
	unsigned int wdm[DDR_PHY_BYTE_MAX];  /* WDM */
};

struct ca_bit_st {
	unsigned int bit_p;
	unsigned int bit_n;
};

struct ca_data_st {
	unsigned int base_dmc;
	unsigned int base_phy;
	unsigned int done; /* whether all ca found bdl range */
	unsigned int min; /* min left bound */
	unsigned int max; /* max right bound */
	unsigned def[DDR_PHY_CA_REG_MAX];
	int left[DDR_PHY_CA_MAX];
	int right[DDR_PHY_CA_MAX];
	struct ca_bit_st bits[DDR_PHY_CA_MAX];
};

struct ddr_dmc_st {
	unsigned int addr;
	unsigned int byte_num;
	unsigned int ddrt_pattern; /* ddrt reversed data */
};

struct ddr_rank_st {
	unsigned int item;    /* software training item */
	unsigned int item_hw; /* hardware training item */
};

struct ddr_phy_st {
	unsigned int addr;
	unsigned int dram_type;
	unsigned int dmc_num;
	unsigned int rank_num;
	unsigned int total_byte_num;
	struct ddr_dmc_st dmc[DDR_DMC_PER_PHY_MAX];
	struct ddr_rank_st rank[DDR_RANK_NUM];
};

struct ddr_cfg_st {
	struct ddr_phy_st phy[DDR_PHY_NUM];
	unsigned int phy_num;
	unsigned int cur_phy; /* current training phy addr */
	unsigned int cur_dmc; /* current training dmc addr */
	unsigned int cur_item;  /* current SW or HW training item */
	unsigned int cur_pattern;  /* current ddrt pattern */
	unsigned int cur_mode;  /* read or write */
	unsigned int cur_byte; /* current training byte index */
	unsigned int cur_dq; /* current training dq index */
	unsigned int phy_idx; /* current training phy index */
	unsigned int rank_idx; /* current training rank index */
	unsigned int dmc_idx; /* current training dmc index */
	unsigned int adjust; /* whether need to adjust dataeye window */
	unsigned int dq_check_type; /* ddrt or mpr */
	void *cmd_st; /* struct ddr_cmd_st */
	void *res_st; /* SW: struct ddr_training_result_st, HW: struct rdqs_data_st */
};

struct dcc_ck_st {
	unsigned int val[DDR_CK_RESULT_MAX];
	unsigned int win;
	unsigned int win_min_ctl;
	unsigned int win_max_ctl;
	unsigned int win_min_duty;
	unsigned int win_max_duty;
	unsigned int def_bp;
	unsigned int def_ctl;
	unsigned int def_duty;
	unsigned int idx_duty;
	unsigned int idx_duty_ctl;
	unsigned int idx_ctl;
	unsigned int BYPASS_CK_BIT;
	unsigned int ACIOCTL21_CTL_BIT;
	unsigned int ACIOCTL21_CK_BIT;
};

#ifdef DDR_DCC_TRAINING_CONFIG
struct dcc_data_st {
	struct tr_dq_data rank[DDR_RANK_NUM];
	struct dcc_ck_st ck[DDR_CK_NUM];
	unsigned int item[DDR_CK_NUM];
	unsigned int ioctl21_tmp;
};
#endif
/*******Uart early function ***********************************************/
#ifndef DDR_PUTS
#define DDR_PUTS        uart_early_puts
#endif
#ifndef DDR_PUT_HEX
#define DDR_PUT_HEX     uart_early_put_hex
#endif
#ifndef DDR_PUTC
#define DDR_PUTC        uart_early_putc
#endif

#if defined(DDR_TRAINING_UART_CONFIG) || defined(DDR_TRAINING_LOG_CONFIG)
extern void uart_early_puts(const char *s);
extern void uart_early_put_hex(int hex);
extern void uart_early_putc(int chr);
#else
#undef DDR_PUTS
#undef DDR_PUT_HEX
#undef DDR_PUTC
#endif
/*******function interface define*********************************************/
#ifndef DDR_SW_TRAINING_FUNC
#define DDR_SW_TRAINING_FUNC_PUBLIC
#define DDR_SW_TRAINING_FUNC        ddr_sw_training_func
#endif

#ifndef DDR_HW_TRAINING_FUNC
#define DDR_HW_TRAINING_FUNC_PUBLIC
#define DDR_HW_TRAINING_FUNC        ddr_hw_training_func
#endif

#ifndef DDR_PCODE_TRAINING_FUNC
#define DDR_PCODE_TRAINING_FUNC     ddr_pcode_training_func
#endif

#ifndef DDR_TRAINING_CONSOLE
#define DDR_TRAINING_CONSOLE_PUBLIC
#define DDR_TRAINING_CONSOLE        ddr_training_console
#endif
/*******Custom function ***********************************************/
#ifndef DDR_TRAINING_DDRT_PREPARE_FUNC
#define DDR_TRAINING_DDRT_PREPARE_FUNC()
#endif
#ifndef DDR_TRAINING_SAVE_REG_FUNC
#define DDR_TRAINING_SAVE_REG_FUNC(relate_reg, mask)
#endif
#ifndef DDR_TRAINING_RESTORE_REG_FUNC
#define DDR_TRAINING_RESTORE_REG_FUNC(relate_reg)
#endif
#ifndef ddr_boot_cmd_save_func
#define ddr_boot_cmd_save_func(relate_reg) ((void)(relate_reg))
#endif
#ifndef ddr_boot_cmd_restore_func
#define ddr_boot_cmd_restore_func(relate_reg) ((void)(relate_reg))
#endif
/*******function define*********************************************/
int ddr_sw_training_func(void);
int ddr_training_boot_func(struct ddr_cfg_st *cfg);
int ddr_training_cmd_func(struct ddr_cfg_st *cfg);

void* ddrtr_memset(void *b, int c, unsigned int len);
void* ddrtr_memcpy(void *dst, const void *src, unsigned int len);
void ddr_training_cfg_init(struct ddr_cfg_st *cfg);
int ddr_training_by_dmc(struct ddr_cfg_st *cfg);
int ddr_training_by_rank(struct ddr_cfg_st *cfg);
int ddr_training_by_phy(struct ddr_cfg_st *cfg);
int ddr_training_all(struct ddr_cfg_st *cfg);
int ddr_dataeye_training_func(struct ddr_cfg_st *cfg);
int ddr_vref_training_func(struct ddr_cfg_st *cfg);
int ddr_wl_func(struct ddr_cfg_st *cfg);
int ddr_gating_func(struct ddr_cfg_st *cfg);
int ddr_ac_training_func(struct ddr_cfg_st *cfg);
int ddr_lpca_training_func(struct ddr_cfg_st *cfg);
int ddr_dcc_training_func(struct ddr_cfg_st *cfg);

void ddr_phy_cfg_update(unsigned int base_phy);
void ddr_phy_set_dq_bdl(struct ddr_cfg_st *cfg, unsigned int value);
int ddr_hw_training(struct ddr_cfg_st *cfg);
int ddr_pcode_training(struct ddr_cfg_st *cfg);

int ddr_mpr_training(struct ddr_cfg_st *cfg);
int ddr_write_leveling(struct ddr_cfg_st *cfg);
int ddr_gate_training(struct ddr_cfg_st *cfg);
int ddr_dataeye_training(struct ddr_cfg_st *cfg);
int ddr_vref_training(struct ddr_cfg_st *cfg);
int ddr_ac_training(struct ddr_cfg_st *cfg);
int ddr_lpca_training(struct ddr_cfg_st *cfg);
int ddr_dataeye_deskew(struct ddr_cfg_st *cfg, struct training_data *training);
void ddr_adjust_dataeye(struct ddr_cfg_st *cfg, struct training_data *training);
void ddr_result_data_save(struct ddr_cfg_st *cfg, struct training_data *training);
void ddr_lpca_data_save(struct ca_data_st *data);
unsigned int ddr_ddrt_get_test_addr(void);
int ddr_ddrt_test(unsigned int mask, int byte, int dq);
int ddr_dataeye_check_dq(struct ddr_cfg_st *cfg);
void ddr_ddrt_init(struct ddr_cfg_st *cfg, unsigned int mode);
int ddr_training_check_bypass(struct ddr_cfg_st *cfg, unsigned int mask);
int ddr_training_phy_disable(int index);
void ddr_training_save_reg(struct ddr_cfg_st *cfg, struct tr_relate_reg *relate_reg,
			   unsigned int mask);
void ddr_training_restore_reg(struct ddr_cfg_st *cfg, struct tr_relate_reg *relate_reg);
void ddr_training_get_base(int index, unsigned int *base_dmc,
			   unsigned int *base_phy);
void ddr_training_switch_axi(struct ddr_cfg_st *cfg);
void ddr_training_log(const char *func, int level, const char *fmt, ...);
void ddr_training_stat(unsigned int mask, unsigned int phy, int byte, int dq);
void ddr_training_error(unsigned int mask, unsigned int phy, int byte, int dq);
void ddr_training_start(void);
void ddr_training_suc(void);
unsigned int ddr_phy_get_byte_num(unsigned int base_dmc);
void ddr_training_set_timing(unsigned int base_dmc, unsigned int timing);
int ddr_hw_dataeye_read(struct ddr_cfg_st *cfg);

#ifdef DDR_MPR_TRAINING_CONFIG
int ddr_mpr_training_func(struct ddr_cfg_st *cfg);
int ddr_mpr_check(struct ddr_cfg_st *cfg);
#else
static inline int ddr_mpr_training_func(struct ddr_cfg_st *cfg)
{
	DDR_WARNING("Not support DDR MPR training.");
	return 0;
}
static inline int ddr_mpr_check(struct ddr_cfg_st *cfg) { return 0;}
#endif

#endif /* __ASSEMBLY__ */
#endif /* DDR_TRAINING_IMPL_H */
