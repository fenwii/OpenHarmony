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
 * Description: Higmac driver main process header file
 */

#ifndef __HIGMAC_H__
#define __HIGMAC_H__

#include <common.h>
#include <command.h>
#include <linux/list.h>
#include <asm/io.h>
#include <malloc.h>         /* malloc, free, realloc */
#include <net.h>
#include <miiphy.h>

#define bit(nr)		(1UL << (nr))

#define GMAC_AT_LEAST_2PORT	(CONFIG_GMAC_NUMS >= 2)
#define GMAC_AT_LEAST_3PORT	(CONFIG_GMAC_NUMS >= 3)
#define ENV_BUF_LEN			32

/* board parameters */
#define DEFAULT_PHY_LINK_TIMES	20000

enum if_mode {
	INTERFACE_MODE_MII,
	INTERFACE_MODE_RMII,
	INTERFACE_MODE_RGMII,
	INTERFACE_MODE_BUTT
};

enum speed_mode {
	SPEED_MODE_10M,
	SPEED_MODE_100M,
	SPEED_MODE_1000M,
	SPEED_MODE_BUTT
};

enum { /* DEFAULT: DUPLEX_FULL */
	PORT_MODE_10_MII = 0x1D,
	PORT_MODE_100_MII = 0x1F,
	PORT_MODE_10_RGMII = 0x3D,
	PORT_MODE_100_RGMII = 0x3F,
	PORT_MODE_1000_RGMII = 0x3C,
	PORT_MODE_10_RMII = 0x9D,
	PORT_MODE_100_RMII = 0x9F,
	PORT_MODE_BUTT
};

#define INVALID_PHY_ADDR 0xFF
#define INVALID_LINK_STATUS 0

#define MAC_LEN 6
#define MAX_PHY_NAME_LEN 15
#define MAX_ETH_ADDR 20

#define MIN_PKG_LEN		42
#define MAX_PKG_LEN		1600
#define higmac_invalid_rxpkg_len(len) \
	(!(((len) >= MIN_PKG_LEN) && ((len) <= MAX_PKG_LEN)))

#define PORT_MOD_10M_MII		0
#define PORT_MOD_100M_MII		1
#define PORT_MOD_1000M_GMII		2
#define PORT_MOD_10M_RGMII		3
#define PORT_MOD_100M_RGMII		4
#define PORT_MOD_1000M_RGMII		5

#define HIGMAC_LINKED       bit(0)
#define HIGMAC_DUP_FULL     bit(1)
#define HIGMAC_SPD_10M      bit(2)
#define HIGMAC_SPD_100M     bit(3)
#define HIGMAC_SPD_1000M    bit(4)

#define RX_OUTCFF_WR_DESC_ENA	bit(3)
#define RX_CFF_RD_DESC_ENA	bit(2)
#define TX_OUTCFF_WR_DESC_ENA	bit(1)
#define TX_CFF_RD_DESC_ENA	bit(0)

#define HIGMAC_MAX_QUEUE_DEPTH	(SZ_1K*2)

#define HIGMAC_HWQ_RX_FQ_DEPTH	64
#define HIGMAC_HWQ_RX_BQ_DEPTH	64
#define HIGMAC_HWQ_TX_BQ_DEPTH	2
#define HIGMAC_HWQ_TX_RQ_DEPTH	2

#define HIGMAC_MONITOR_TIMER	(msecs_to_jiffies(10))

#define MAX_RX_POOLS		(SZ_1K)
#define HIETH_MAX_FRAME_SIZE	(SZ_1K*2)
/* mac rx buffer size should be no less than 1600,
 * reserve more 64 bytes for the max frame length 1518.
 */
#define HIETH_BUFFER_SIZE	1600
#define SKB_SIZE		(HIETH_MAX_FRAME_SIZE)

#if defined(CONFIG_64BIT)
#define REG_BIT_WIDTH			32
#define Q_ADDR_HI8_OFFSET		24
#define Q_ADDR_HI8_MASK			(bit(Q_ADDR_HI8_OFFSET) - 1)
#define TX_DESC_HI8_MASK		0xff
#define SG_DESC_HI8_OFFSET		8
#endif

#define DESC_VLD_FREE		0
#define DESC_VLD_BUSY		1
#define DESC_FL_FIRST		2
#define DESC_FL_MID		0
#define DESC_FL_LAST		1
#define DESC_FL_FULL		3

#ifdef CONFIG_HIGMAC_DESC_4_WORD
#define DESC_WORD_SHIFT		2
#else
#define DESC_WORD_SHIFT		3
#endif
#define DESC_BYTE_SHIFT		(DESC_WORD_SHIFT + 2)
#define DESC_WORD_CNT		(1 << DESC_WORD_SHIFT)
#define DESC_SIZE		(1 << DESC_BYTE_SHIFT)

typedef struct higmac_descriptor {
	unsigned int data_buff_addr;

	unsigned int buffer_len:11;
	unsigned int reserve2:5;
	unsigned int data_len:11;
	unsigned int reserve1:2;
	unsigned int fl:2;
	unsigned int descvid:1;

	unsigned int reserve3;
	unsigned int reserve4;
#ifndef CONFIG_HIGMAC_DESC_4_WORD
	unsigned int reserve5;
	unsigned int reserve6;
	unsigned int reserve7;
	unsigned int reserve8;
#endif
} higmac_desc;

struct higmac_netdev_local {
	unsigned long iobase; /* virtual io addr */
	unsigned long iobase_phys; /* physical io addr */

	higmac_desc *rx_fq_addr;
	higmac_desc *rx_bq_addr;
	higmac_desc *tx_bq_addr;
	higmac_desc *tx_rq_addr;

	int link_stat;
	int index;
	int initalized;
};

struct higmac_board_info {
	struct higmac_netdev_local higmac_ld;
	enum if_mode phy_intf;
	char *mii_name;
	int phy_addr;
};

extern struct higmac_board_info g_higmac_board_info[];
#endif
