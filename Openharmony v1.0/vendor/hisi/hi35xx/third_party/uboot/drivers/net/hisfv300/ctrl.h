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
 * Description: Control hieth regisiter header file
 */


#ifndef __HIETH_CTRL_H__
#define __HIETH_CTRL_H__

#include "hieth.h"

#ifdef HIETH_SFV300

/* ENDIAN */
#define GLB_ENDIAN_MOD		0x1318
#define BITS_ENDIAN			mk_bits(0, 2)
#define HIETH_BIG_ENDIAN	0
#define HIETH_LITTLE_ENDIAN	3

/* IRQs */
#define GLB_RO_IRQ_STAT		0x1330
#define GLB_RW_IRQ_ENA		0x1334
#define GLB_RW_IRQ_RAW		0x1338

/* IRQs mask bits */
#define BITS_IRQS_U				mk_bits(0, 8)
#define BITS_VLAN_IRQS			mk_bits(11, 1)
#define BITS_MDIO_IRQS			mk_bits(13, 2)
#define BITS_IRQS_ENA_D			mk_bits(17, 1)
#define BITS_IRQS_ENA_U			mk_bits(18, 1)
#define BITS_IRQS_ENA_ALLPORT	mk_bits(19, 1)
#define BITS_IRQS_D				mk_bits(20, 8)

#define BITS_IRQS_MASK_U		(0xFF)
#define BITS_IRQS_MASK_D		(0xFF << 20)

/* IRQs bit name */
#define HIETH_INT_RX_RDY_U      bit(0)
#define HIETH_INT_RX_RDY_D      bit(20)
#define HIETH_INT_TX_FIN_U		bit(1)
#define HIETH_INT_TX_FIN_D		bit(21)
#define HIETH_INT_LINK_CH_U		bit(2)
#define HIETH_INT_LINK_CH_D		bit(22)
#define HIETH_INT_SPEED_CH_U	bit(3)
#define HIETH_INT_SPEED_CH_D	bit(23)
#define HIETH_INT_DUPLEX_CH_U	bit(4)
#define HIETH_INT_DUPLEX_CH_D	bit(24)
#define HIETH_INT_STATE_CH_U	bit(5)
#define HIETH_INT_STATE_CH_D	bit(25)
#define HIETH_INT_TXQUE_RDY_U	bit(6)
#define HIETH_INT_TXQUE_RDY_D	bit(26)
#define HIETH_INT_MULTI_RXRDY_U	bit(7)
#define HIETH_INT_MULTI_RXRDY_D	bit(27)

#define HIETH_INT_MDIO_FINISH	bit(12)
#define HIETH_INT_UNKNOW_VLANID	bit(13)
#define HIETH_INT_UNKNOW_VLANM	bit(14)

/* Tx/Rx Queue depth */
#define U_GLB_QLEN_SET			0x0344
#define D_GLB_QLEN_SET			0x2344
#define BITS_TXQ_DEP			mk_bits(0, 6)
#define BITS_RXQ_DEP			mk_bits(8, 6)

/* Rx (read only) Queue-ID and LEN */
#define U_GLB_RO_IQFRM_DES		0x0354
#define D_GLB_RO_IQFRM_DES		0x2354
/* bits of UD_GLB_RO_IQFRM_DES */
#define BITS_RXPKG_LEN			mk_bits(0, 11)
#define BITS_RXPKG_ID			mk_bits(12, 6)
#define BITS_FRM_VLAN_VID		mk_bits(18, 1)
#define BITS_FD_VID_VID			mk_bits(19, 1)
#define BITS_FD_VLANID			mk_bits(20, 12)

/* Rx ADDR */
#define U_GLB_IQ_ADDR		0x0358
#define D_GLB_IQ_ADDR		0x2358

/* Tx ADDR and LEN */
#define U_GLB_EQ_ADDR		0x0360
#define D_GLB_EQ_ADDR		0x2360
#define U_GLB_EQFRM_LEN		0x0364
#define D_GLB_EQFRM_LEN		0x2364
/* bits of UD_GLB_EQFRM_LEN */
#define BITS_TXINQ_LEN		mk_bits(0, 11)

/* Rx/Tx Queue ID */
#define U_GLB_RO_QUEUE_ID	0x0368
#define D_GLB_RO_QUEUE_ID	0x2368
/* bits of UD_GLB_RO_QUEUE_ID */
#define BITS_TXOUTQ_ID		mk_bits(0, 6)
#define BITS_TXINQ_ID		mk_bits(8, 6)
#define BITS_RXINQ_ID		mk_bits(16, 6)

/* Rx/Tx Queue staus  */
#define U_GLB_RO_QUEUE_STAT	0x036C
#define D_GLB_RO_QUEUE_STAT	0x236C
/* bits of UD_GLB_RO_QUEUE_STAT */
/* check this bit to see if we can add a Tx package */
#define BITS_XMITQ_RDY		mk_bits(24, 1)
/* check this bit to see if we can add a Rx addr */
#define BITS_RECVQ_RDY		mk_bits(25, 1)
/* counts in queue, include currently sending */
#define BITS_XMITQ_CNT_INUSE	mk_bits(0, 6)
/* counts in queue, include currently receving */
#define BITS_RECVQ_CNT_RXOK		mk_bits(8, 6)

#define is_recv_packet(ld)		(hieth_readl(ld, GLB_RW_IRQ_RAW) & (ud_bit_name(HIETH_INT_RX_RDY)))
#define is_recv_packet_rx(ld)	((hieth_readl(ld, ud_reg_name(GLB_RO_QUEUE_STAT)) >> 8) & 0x3F)
#define hw_set_rxpkg_finish(ld)	hieth_writel(ld, ud_bit_name(HIETH_INT_RX_RDY), GLB_RW_IRQ_RAW)

// //////////////////////////////////////////////////////////////////////////////////////////

#define hw_get_rxpkg_id(ld)		hieth_readl_bits(ld, ud_reg_name(GLB_RO_IQFRM_DES), BITS_RXPKG_ID)
#define hw_get_rxpkg_len(ld)	hieth_readl_bits(ld, ud_reg_name(GLB_RO_IQFRM_DES), BITS_RXPKG_LEN)

#define hw_get_txqid(ld)	hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_ID), BITS_TXINQ_ID)
#define hw_get_rxqid(ld)	hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_ID), BITS_RXINQ_ID)

#define hw_xmitq_cnt_inuse(ld)	hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT), BITS_XMITQ_CNT_INUSE)
#define hw_recvq_cnt_rxok(ld)	hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT), BITS_RECVQ_CNT_RXOK)

#define hw_recvq_setfd(ld, fd) hieth_writel(ld, (fd).frm_addr, ud_reg_name(GLB_IQ_ADDR))

#endif

/* for each bits, set '1' enable the intterrupt, and '0' takes no effects */
/* return last irq_enable status */
u32 hieth_irq_enable(struct hieth_netdev_local *ld, u32 irqs);
u32 hieth_irq_disable(struct hieth_netdev_local *ld, u32 irqs);
/* return irqstatus */
u32 hieth_read_irqstatus(struct hieth_netdev_local *ld);
u32 hieth_read_raw_irqstatus(struct hieth_netdev_local *ld);
/* return irqstatus after clean */
u32 hieth_clear_irqstatus(struct hieth_netdev_local *ld, u32 irqs);

u32 hieth_set_endian_mode(struct hieth_netdev_local *ld, u32 mode);
void hw_xmitq_setfd(struct hieth_netdev_local *ld, struct hieth_frame_desc fd);

/* Tx/Rx queue operation */
int hieth_set_hwq_depth(struct hieth_netdev_local *ld);
int hieth_get_hwq_xmit_depth(struct hieth_netdev_local *ld);
int hieth_get_hwq_recv_depth(struct hieth_netdev_local *ld);

#define hieth_invalid_txqfd_addr(addr)	((addr) & 0x3)
#define hieth_invalid_rxqfd_addr(addr)	((addr) & 0x3)
#define hieth_invalid_rxpkg_len(len)	(!((len) >= 42 && (len) <= HIETH_MAX_FRAME_SIZE))

#endif
