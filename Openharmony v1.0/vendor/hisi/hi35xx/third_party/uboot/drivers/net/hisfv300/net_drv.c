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
 * Description: Hieth driver main process
 */


#define HIETH_SFV300
#include "hieth.h"
#include "mac.h"
#include "ctrl.h"
#include "glb.h"
#include "sys.h"
#include "mii_drv.h"
#include <config.h>
#include <miiphy.h>
#include <net.h>
#include <cpu_func.h>

/*************************************************************************/
int hieth_mdiobus_driver_init(struct hieth_netdev_local *ld);
void hieth_mdiobus_driver_exit(struct hieth_netdev_local *ld);

/* Used when trying to connect to a specific phy (mii bus id:phy device id) */
/* refer linux-2.6.23 ./include/linux/phy.h line 76 */
char mdio_bus_name[MAX_PHY_NAME_LEN];

#define MAC_LEN 6

struct hieth_netdev_local hieth_devs_priv[MAX_PORT] = {
	{
		.port = UP_PORT,
		.mii_name = mdio_bus_name,
		.phy_addr = HISFV_PHY_U,
		.phy_intf = HIETH_MII_RMII_MODE_U,
	},
	{
		.port = DOWN_PORT,
		.mii_name = mdio_bus_name,
		.phy_addr = HISFV_PHY_D,
		.phy_intf = HIETH_MII_RMII_MODE_D,
	},
};

static int set_mac_address(const char *mac)
{
	u32 val;

	val = ((u32)mac[0] << 8) | (u32)mac[1]; /* mac 0 [8:15], mac 1 [0:7] */
	writel(val, REG_BASE_SF + GLB_HOSTMAC_H16);
	/* mac 2 [24:31], mac 3 [16:23], mac 4 [8:15], mac 5 [0:7] */
	val = ((u32)mac[2] << 24) | ((u32)mac[3] << 16) | ((u32)mac[4] << 8) | (u32)mac[5];
	writel(val, REG_BASE_SF + GLB_HOSTMAC_L32);

	return 0;
}

#ifdef HIETH_RX_QUEUE_MULTI_DESC
static int hieth_init_hw_desc_queue(struct hieth_netdev_local *ld)
{
	struct hieth_frame_desc *queue_phy_addr = NULL;
	int i;

	const int size = HIETH_HW_DESC_DEPTH * sizeof(struct hieth_frame_desc);
	/* init rx fq */
	queue_phy_addr = (struct hieth_frame_desc *)malloc(size);
	if (queue_phy_addr == NULL) {
		printf("alloc rx fq error!\n");
		return 1;
	}

	memset((void *)queue_phy_addr, 0, size);
	ld->hieth_desc_head = queue_phy_addr;
	ld->desc_hw_offset = 0;
	ld->desc_rec_offset = 0;

	for (i = 0; i < HIETH_HW_DESC_DEPTH; i++) {
		queue_phy_addr[i].frm_addr = (unsigned long)memalign(PKTALIGN, PKTSIZE_ALIGN);
		queue_phy_addr[i].frm_len = 0;
	}
	return 0;
}
#endif

#ifdef HIETH_RX_QUEUE_MULTI_DESC
static int hieth_destroy_hw_desc_queue(struct hieth_netdev_local *ld)
{
	struct hieth_frame_desc *queue_phy_addr = ld->hieth_desc_head;
	int i;

	if (queue_phy_addr != NULL) {
		for (i = 0; i < HIETH_HW_DESC_DEPTH; i++)
			free((void *)queue_phy_addr[i].frm_addr);

		free(ld->hieth_desc_head);
		ld->hieth_desc_head = NULL;
	}
	ld->desc_hw_offset = 0;
	ld->desc_rec_offset = 0;

	return 0;
}
#endif

int eth_set_host_mac_address(struct eth_device *dev)
{
	unsigned char mac[MAC_LEN];

	memset(mac, 0, sizeof(mac));

	if (!eth_env_get_enetaddr("ethaddr", mac)) {
		printf("MAC address invalid!\n");
#ifdef CONFIG_NET_RANDOM_ETHADDR
		net_random_ethaddr(mac);
		printf("Set Random MAC address!\n");
		eth_setenv_enetaddr("ethaddr", mac);
#endif
	}

	set_mac_address((char *)mac);
	memcpy(dev->enetaddr, mac, MAC_LEN);

	return 0;
}

static void phy_print_status(struct hieth_netdev_local *ld, unsigned int stat)
{
	printf("%s : phy status change : LINK=%s : DUPLEX=%s : SPEED=%s\n",
		   (ld->port == UP_PORT) ? "eth0" : "eth1",
		   (stat & HIETH_LINKED) ? "UP" : "DOWN",
		   (stat & HIETH_DUP_FULL) ? "FULL" : "HALF",
		   (stat & HIETH_SPD_100M) ? "100M" : "10M");
}

static void hieth_adjust_link(struct hieth_netdev_local *ld)
{
	u32 stat = 0;
	int timeout_us = 1000;
	/* this env phy_link_time used to solve the difference phy auto-negotiation time of  various phys */
	char *timeout = env_get("phy_link_time");
	if (timeout != NULL) {
		timeout_us = simple_strtol(timeout, 0, 10); /* Base10 */
		if (timeout_us < 0)
			timeout_us = 1000; /* delay 1000us */
	}
retry:
	udelay(1);

	stat |= miiphy_link(ld->mii_name, ld->phy_addr) ? HIETH_LINKED : 0;
	stat |= miiphy_duplex(ld->mii_name, ld->phy_addr) == FULL ? HIETH_DUP_FULL : 0;
	stat |= miiphy_speed(ld->mii_name, ld->phy_addr) == _100BASET ? HIETH_SPD_100M : 0;
	if (--timeout_us && !(stat & HIETH_LINKED))
		goto retry;

	if (stat != ld->link_stat) {
		hieth_set_linkstat(ld, stat);
		phy_print_status(ld, stat);
		ld->link_stat = stat;
		hieth_set_mii_mode(ld, ld->phy_intf);
	}

	set_phy_valtage();
}

static int hieth_net_open(struct hieth_netdev_local *ld)
{
	/* enable sys-ctrl-en and clk-en  */
	hieth_sys_startup();

	/* setup hardware tx dep */
	hieth_writel_bits(ld, HIETH_HW_TXQ_DEPTH, ud_reg_name(GLB_QLEN_SET), BITS_TXQ_DEP);

	/* setup hardware rx dep */
	hieth_writel_bits(ld, HIETH_HW_RXQ_DEPTH, ud_reg_name(GLB_QLEN_SET), BITS_RXQ_DEP);

	ld->link_stat = 0;
	hieth_adjust_link(ld);

	hieth_irq_enable(ld, ud_bit_name(HIETH_INT_RX_RDY));

	return 0;
}

static int hieth_net_close(struct hieth_netdev_local *ld)
{
	hieth_glb_preinit_dummy(ld);

	hieth_sys_allstop();

	return 0;
}

static int hieth_dev_probe_init(struct hieth_netdev_local *ld)
{
	ld->iobase_phys = REG_BASE_SF;

	hieth_glb_preinit_dummy(ld);

#ifdef HIETH_RX_QUEUE_MULTI_DESC
	hieth_init_hw_desc_queue(ld);
#endif

	hieth_sys_allstop();

	return 0;
}

static int hieth_dev_remove(struct hieth_netdev_local *ld)
{
#ifdef HIETH_RX_QUEUE_MULTI_DESC
	hieth_destroy_hw_desc_queue(ld);
#endif

	return 0;
}

static void hieth_get_phy_intf(struct hieth_netdev_local *ld)
{
	char *mdio_intf = NULL;

	/* get mdio interface from env.FORMAT: mdio_intf=mii or mdio_intf=rmii */
	mdio_intf = env_get("mdio_intf");
	if (mdio_intf != NULL) {
		if (!strncmp(mdio_intf, "mii", strlen("mii"))) {
			ld->phy_intf = INTERFACE_MODE_MII;
		} else if (!strncmp(mdio_intf, "rmii", strlen("rmii"))) {
			ld->phy_intf = INTERFACE_MODE_RMII;
		} else {
			printf("Invalid mdio_intf, should be mii or rmii.\n");
			ld->phy_intf = INTERFACE_MODE_RMII;
		}
	}
}

static void hieth_get_phy_addr(struct hieth_netdev_local *ld)
{
	char *phyaddr = NULL;
	char addr_name[MAX_PORT][10] = { "phyaddru", "phyaddrd" }; /* max name size is 10 */

	if (ld->port >= MAX_PORT)
		return;

	/* get phy addr of up port */
	phyaddr = env_get(addr_name[ld->port]);
	if (phyaddr != NULL) {
		unsigned long tmp = simple_strtoul(phyaddr, 0, 10); /* use Base10 */
		/* check phyaddr > 0x1f */
		if (tmp >= 0x1f) {
			printf("Detected env '%s' had been set greater"
				   "than 0x1f,this may not correct.\n",
				   addr_name[ld->port]);
			return;
		}
		ld->phy_addr = (unsigned char)tmp;
	} else {
#if defined(INNER_PHY)
		if (ld->port == UP_PORT) {
#if defined(INNER_PHY_ADDR_U)
			ld->phy_addr = INNER_PHY_ADDR_U;
#endif
		} else {
#if defined(INNER_PHY_ADDR_D)
			ld->phy_addr = INNER_PHY_ADDR_D;
#endif
		}
#endif
	}
}

static void hieth_exit(struct hieth_netdev_local *ld)
{
	hieth_mdiobus_driver_exit(ld);

	hieth_sys_exit();
}

int hieth_init(struct eth_device *dev, bd_t *bd)
{
	struct hieth_netdev_local *ld = (struct hieth_netdev_local *)dev->priv;
	int ret;
	int count = 30;

	hieth_get_phy_intf(ld);
#if defined(CONFIG_HI3536DV100)
	hieth_set_crg_phy_mode(ld->phy_intf);
#endif

	hieth_get_phy_addr(ld);
#ifdef INNER_PHY
	if (ld->port == UP_PORT)
		set_inner_phy_addr(ld->phy_addr);
#endif

	printf(OSDRV_MODULE_VERSION_STRING "\n");

	set_efuse_unread();

	/* sys-func-sel */
	hieth_sys_init();

	/* register MDIO bus to uboot */
	if (hieth_mdiobus_driver_init(ld) != 0) {
		goto _error_hieth_init;
	}

	if (phy_detected(ld->mii_name, ld->phy_addr) == false) {
		goto _error_hieth_init;
	}

	miiphy_reset(ld->mii_name, ld->phy_addr);

	ret = hieth_dev_probe_init(ld);
	if (ret) {
		hieth_error("register Ether netdevice"
					" driver failed!");
		goto _error_hieth_init;
	}

	eth_set_host_mac_address(dev);

	while (--count >= 0) {
		/* open UpEther net dev */
		hieth_net_open(ld);
		if (ld->link_stat & HIETH_LINKED) {
			return 0;
		}
	}

	printf("PHY not link.\n");

_error_hieth_init:
	hieth_mdiobus_driver_exit(ld);
	hieth_net_close(ld);

	return -1;
}

#ifdef HIETH_RX_QUEUE_MULTI_DESC
static int hieth_recv(struct eth_device *dev)
{
	struct hieth_netdev_local *ld = (struct hieth_netdev_local *)dev->priv;
	int recvq_ready, hw_offset, rec_offset;
	int timeout_us = 10000;
	struct hieth_frame_desc *fd;
	struct hieth_frame_desc receive_fd;

	fd = ld->hieth_desc_head;
	hw_offset = ld->desc_hw_offset;
	rec_offset = ld->desc_rec_offset;

	/* check this we can add a Rx addr */
	recvq_ready = hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT), BITS_RECVQ_RDY);
	if (!recvq_ready)
		hieth_trace(HIETH_TRACE_DRV, "hw can't add a rx addr.");

	while (recvq_ready &&
		   ((hw_offset + 1) % HIETH_HW_DESC_DEPTH != rec_offset)) {
		receive_fd = fd[hw_offset];
		invalidate_dcache_range(receive_fd.frm_addr,
								ALIGN(receive_fd.frm_addr + PKTSIZE_ALIGN, ARCH_DMA_MINALIGN));
		hw_recvq_setfd(ld, receive_fd);

		hw_offset = (hw_offset + 1) % HIETH_HW_DESC_DEPTH;

		recvq_ready =
			hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT),
							 BITS_RECVQ_RDY);
	}
	ld->desc_hw_offset = hw_offset;

	/* receive packed, loop in NetLoop */
	while (--timeout_us && !is_recv_packet_rx(ld))
		udelay(1);

	if (is_recv_packet_rx(ld)) {
		receive_fd = fd[rec_offset];

		receive_fd.frm_len = hw_get_rxpkg_len(ld);
		hw_set_rxpkg_finish(ld);

		rec_offset = (rec_offset + 1) % HIETH_HW_DESC_DEPTH;
		ld->desc_rec_offset = rec_offset;

		if (hieth_invalid_rxpkg_len(receive_fd.frm_len)) {
			hieth_error("frm_len invalid (%u)", receive_fd.frm_len);
			goto _error_exit;
		}

		invalidate_dcache_range(receive_fd.frm_addr,
								ALIGN(receive_fd.frm_addr + receive_fd.frm_len, ARCH_DMA_MINALIGN));
		memcpy((void *)net_rx_packets[0], (void *)receive_fd.frm_addr,
			   receive_fd.frm_len);

		/* Pass the packet up to the protocol layers. */
		net_process_received_packet(net_rx_packets[0], receive_fd.frm_len);

		return 0;
	} else {
		hieth_trace(HIETH_TRACE_DRV, "hw rx timeout.");
	}

_error_exit:
	return -1;
}
#else
static int hieth_recv(struct eth_device *dev)
{
	struct hieth_netdev_local *ld = (struct hieth_netdev_local *)dev->priv;
	int recvq_ready;
	int timeout_us = 10000;
	struct hieth_frame_desc fd = { 0 };

	/* check this we can add a Rx addr */
	recvq_ready = hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT), BITS_RECVQ_RDY);
	if (!recvq_ready)
		hieth_trace(HIETH_TRACE_DRV, "hw can't add a rx addr.");

	/* enable rx int */
	hieth_irq_enable(ld, ud_bit_name(HIETH_INT_RX_RDY));

	/* fill rx hwq fd */
	fd.frm_addr = (uintptr_t)net_rx_packets[0];
	fd.frm_len = 0;
	/* recv data will be put into DDR , in case of get the cache data, mush be invalid Dcache */
	invalidate_dcache_range(fd.frm_addr, ALIGN(fd.frm_addr + PKTSIZE_ALIGN, ARCH_DMA_MINALIGN));

	hw_recvq_setfd(ld, fd);

	/* receive packed, loop in NetLoop */
	while (--timeout_us && !is_recv_packet(ld))
		udelay(1);

	if (is_recv_packet(ld)) {
		fd.frm_len = hw_get_rxpkg_len(ld);
		hw_set_rxpkg_finish(ld);

		if (hieth_invalid_rxpkg_len(fd.frm_len)) {
			hieth_error("frm_len invalid (%u)", fd.frm_len);
			goto _error_exit;
		}

		invalidate_dcache_range(fd.frm_addr,
								ALIGN(fd.frm_addr + fd.frm_len, ARCH_DMA_MINALIGN));
		/* Pass the packet up to the protocol layers. */
		net_process_received_packet(net_rx_packets[0], fd.frm_len);

		return 0;
	} else {
		hieth_trace(HIETH_TRACE_DRV, "hw rx timeout.");
	}

_error_exit:
	return -1;
}
#endif

#define ETH_FCS_LEN 4 /* Octets in the FCS */
static int hieth_send(struct eth_device *dev, void *packet, int length)
{
	struct hieth_netdev_local *ld = (struct hieth_netdev_local *)dev->priv;
	unsigned int ints, xmitq_ready;
	unsigned int timeout_us = 3000;
	struct hieth_frame_desc fd;

	/* check this we can add a Tx addr */
	xmitq_ready = hieth_readl_bits(ld, ud_reg_name(GLB_RO_QUEUE_STAT), BITS_XMITQ_RDY);
	if (!xmitq_ready) {
		hieth_error("hw can't add a tx addr");
		goto _error_exit;
	}

	/* enable tx int */
	hieth_irq_enable(ld, ud_bit_name(HIETH_INT_TXQUE_RDY));

	flush_cache((uintptr_t)packet, ALIGN((unsigned int)length + ETH_FCS_LEN, ARCH_DMA_MINALIGN));
	/* fill tx hwq fd */
	fd.frm_addr = (uintptr_t)packet;
	fd.frm_len = length + ETH_FCS_LEN;
	hw_xmitq_setfd(ld, fd);

	do {
		udelay(1);
		ints = hieth_read_irqstatus(ld);
	} while (--timeout_us && !(ints & ud_bit_name(HIETH_INT_TXQUE_RDY)));

	hieth_clear_irqstatus(ld, ints);

	if (!timeout_us) {
		hieth_error("hw tx timeout");
		goto _error_exit;
	}

	return 0;

_error_exit:
	return -1;
}

static void hieth_halt(struct eth_device *dev)
{
	struct hieth_netdev_local *ld = (struct hieth_netdev_local *)dev->priv;

	hieth_net_close(ld);

	hieth_dev_remove(ld);

	hieth_exit(ld);
}

static int hieth_register_dev(unsigned char port_id)
{
	struct eth_device *dev;

	dev = malloc(sizeof(*dev));
	if (dev == NULL)
		return -1;
	memset(dev, 0, sizeof(*dev));

	dev->iobase = REG_BASE_SF;
	dev->init = hieth_init;
	dev->halt = hieth_halt;
	dev->send = hieth_send;
	dev->recv = hieth_recv;
	dev->priv = &hieth_devs_priv[port_id];
	hieth_devs_priv[port_id].iobase_phys = REG_BASE_SF;
	snprintf(dev->name, sizeof(dev->name) - 1, "eth%d", port_id);

	eth_register(dev);

	return 0;
}

int hieth_initialize(bd_t *bis)
{
	int ret;

	ret = hieth_register_dev(UP_PORT);
	if (ret)
		return ret;

	return 0;
}
