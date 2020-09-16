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

#ifndef DDR_INTERFACE_H
#define DDR_INTERFACE_H

#define DDR_PHY_BYTE_MAX                  4
#define DDR_PHY_BIT_NUM                   8
/* support max bit 32*/
#define DDR_PHY_BIT_MAX                   (DDR_PHY_BYTE_MAX * DDR_PHY_BIT_NUM)

#define DDR_REG_NAME_MAX              32       /* register name */
#define DDR_CA_ADDR_MAX               10

#define DDR_SUPPORT_PHY_MAX           2        /* support max phy number */
#define DDR_SUPPORT_RANK_MAX          2       /* support max rank number */
#define DDR_SUPPORT_DMC_MAX           4        /* support max dmc number */
#define DDR_CK_RESULT_MAX             2        /* DCC CK result number */


/**
 * DDR training register number:
 * WDQS              4
 * WDQ Phase         4
 * WDQ BDL           8
 * WDM               4
 * Write DQ/DQS OE   4
 * RDQS              4
 * RDQ BDL           8
 * Gate              4
 * CS                1
 * CLK               1
 * Host Vref         4
 * DRAM Vref         4
 * CA Phase          1
 * CA BDL            5
 * -------------------
 *                  60
 */
#define DDR_TRAINING_REG_NUM          60
/* register max. */
#define DDR_TRAINING_REG_MAX        (DDR_TRAINING_REG_NUM * DDR_SUPPORT_PHY_MAX)

#define DDR_TRAINING_CMD_SW         (1 << 0)
#define DDR_TRAINING_CMD_HW         (1 << 1)
#define DDR_TRAINING_CMD_MPR        (1 << 2)
#define DDR_TRAINING_CMD_WL         (1 << 3)
#define DDR_TRAINING_CMD_GATE       (1 << 4)
#define DDR_TRAINING_CMD_DATAEYE    (1 << 5)
#define DDR_TRAINING_CMD_VREF       (1 << 6)
#define DDR_TRAINING_CMD_AC         (1 << 7)
#define DDR_TRAINING_CMD_LPCA       (1 << 8)
#define DDR_TRAINING_CMD_SW_NO_WL   (1 << 9)
#define DDR_TRAINING_CMD_CONSOLE    (1 << 10)
#define DDR_TRAINING_CMD_DCC        (1 << 11)
#define DDR_TRAINING_CMD_PCODE      (1 << 12)

/*******log level ********************/
#define DDR_LOG_INFO_STR              "info"
#define DDR_LOG_DEBUG_STR             "debug"
#define DDR_LOG_WARNING_STR           "warning"
#define DDR_LOG_ERROR_STR             "error"
#define DDR_LOG_FATAL_STR             "fatal"

#define DDR_LOG_INFO                  (1 << 0)
#define DDR_LOG_DEBUG                 (1 << 1)
#define DDR_LOG_WARNING               (1 << 2)
#define DDR_LOG_ERROR                 (1 << 3)
#define DDR_LOG_FATAL                 (1 << 4)

#define DDR_TRAINING_BOOT_RESULT_ADDR (TEXT_BASE + 0x1000000)  /* boot + 16M */

#define DDR_TRAINING_VER "V2.1.6 20181228"
#define DDR_VERSION    0x216
struct training_data {
	unsigned int ddr_bit_result[DDR_PHY_BIT_MAX];
	unsigned int ddr_bit_best[DDR_PHY_BIT_MAX];
	unsigned int ddr_win_sum;
};

struct ddr_training_data_st {
	unsigned int base_phy;
	unsigned int byte_num;
	unsigned int rank_idx;
	struct training_data read;
	struct training_data write;
	unsigned int ca_addr[DDR_CA_ADDR_MAX];
};

struct rank_data_st {
	unsigned int item;
	struct ddr_training_data_st ddrtr_data;
};

struct phy_data_st {
	unsigned int rank_num;
	struct rank_data_st rank_st[DDR_SUPPORT_RANK_MAX];
};

struct ddr_training_result_st {
	unsigned int phy_num;
	struct phy_data_st phy_st[DDR_SUPPORT_PHY_MAX];
};

struct ddr_reg_val_st {
	unsigned int rank_index;
	unsigned int byte_index;
	unsigned int offset;
	unsigned int val;
	char name[DDR_REG_NAME_MAX];
};

struct ddr_cmd_st {
	unsigned int cmd;
	unsigned int level;
	unsigned int start;
	unsigned int length;
};

typedef struct ddr_training_result_st * (*ddr_cmd_entry_func)
				(struct ddr_cmd_st *cmd_st);

/* DDR training interface before boot */
int ddr_pcode_training_if(void);
int ddr_sw_training_if(void);
int ddr_hw_training_if(void);
int ddr_training_console_if(void *args);

/* DDR training check interface when boot */
struct ddr_training_result_st *ddr_cmd_training_if(struct ddr_cmd_st *cmd_st);
int check_ddr_training(void);

/* DDR training command interface after boot */
void ddr_reg_result_display(struct ddr_training_result_st *ddrtr_result);
void ddr_cmd_result_display(struct ddr_training_result_st *ddrtr_result,
	unsigned int cmd);
void *ddr_cmd_get_entry(void);
void ddr_cmd_prepare_copy(void);
void ddr_cmd_site_save(void);
void ddr_cmd_site_restore(void);

#endif /* DDR_INTERFACE_H */

