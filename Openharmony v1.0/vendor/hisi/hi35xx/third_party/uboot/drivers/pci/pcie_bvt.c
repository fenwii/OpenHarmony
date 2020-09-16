/*
 * pcie_bvt.c
 *
 * The PCIE Device Driver for hisilicon.
 *
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
#include <common.h>
#include <pci.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <errno.h>

#define PERI_CRG_BASE       0x12010000
#define CONF_BASE_ADDR  0x12200000
#define PCIE_EP_CONF_BASE   0x20000000
#define PCI_MEM_ADDR        0x30000000

#define __128MB__   0x8000000

#define PCI_MEM_SIZE    0x8000000

#define PCIE_SYS_STATE0 0xf00
#define PCIE_XMLH_LINK_UP   15
#define PCIE_RDLH_LINK_UP   5

#define pcie_cfg_reg(reg)   ((reg) & 0xffc)   /* set dword align */

#define PCIE_SYS_CTRL7      0xc1c
#define PCIE_APP_LTSSM_ENBALE   11

#define PERI_CRG44      0x18c
#define PCIE_X2_SRST_REQ    2

#define PCI_CARD        0x44

#define PCIE_SYS_CTRL0      0xc00
#define PCIE_DEVICE_TYPE    28
#define PCIE_WM_RC      0x4

#define PCIE_X2_AUX_CKEN    7
#define PCIE_X2_PIPE_CKEN   6
#define PCIE_X2_SYS_CKEN    5
#define PCIE_X2_BUS_CKEN    4

#define PCI_CLASS_REVISION  0x08
#define PCI_COMMAND     0x04

static int pcie_link_up(void)
{
	unsigned int val;

	val = readl(CONF_BASE_ADDR  + PCIE_SYS_STATE0);
	return ((val & (1 << PCIE_XMLH_LINK_UP)) &&
			(val & (1 << PCIE_RDLH_LINK_UP))) ? 1 : 0;
}

static int is_pcie_link_up(void)
{
	int i;
	for (i = 0; i < 5000000; i++) { /* 5000000: Cycle */
		if (pcie_link_up())
			return 1;
	}

	return 0;
}

static int pcie_read_from_device(struct pci_controller *hose, unsigned int d,
							int where, u32 *val)
{
	unsigned long addr;

	addr = PCIE_EP_CONF_BASE + (d  | pcie_cfg_reg(where));
	*val = readl(addr);

	return 0;
}

static int pcie_read_from_dbi(struct pci_controller *hose, unsigned int d,
							int where, u32 *val)
{
	*val = (uintptr_t)readl(CONF_BASE_ADDR + (where & ~0x3));

	return 0;
}

static int bvt_pcie_read_config(struct pci_controller *hose, pci_dev_t d,
							int where, u32 *val)
{
	int ret;

	if (PCI_BUS(d) == 0)
		ret =  pcie_read_from_dbi(hose, d, where, val);
	else
		ret =  pcie_read_from_device(hose, d, where, val);

	return ret;
}

static int pcie_write_to_dbi(struct pci_controller *hose, pci_dev_t d,
						int where, u32 val)
{
	if (PCI_DEV(d) == 0)
		writel(val, (CONF_BASE_ADDR + (where & (~3)))); /* 3:Reflexive */

	return 0;
}

static int pcie_write_to_device(struct pci_controller *hose, pci_dev_t d,
							int where, u32 val)
{
	unsigned long addr;

	if (PCI_DEV(d) == 0) {
		addr = PCIE_EP_CONF_BASE + (d | pcie_cfg_reg(where));
		writel(val, addr);
	}

	return 0;
}

static int bvt_pcie_write_config(struct pci_controller *hose, pci_dev_t d,
							int where, u32 val)
{
	if (PCI_BUS(d) == 0)
		return pcie_write_to_dbi(hose, d, where, val);
	else
		return pcie_write_to_device(hose, d, where, val);
}

static int __arch_pcie_sys_init(void)
{
	unsigned int val;

	/*
	 *  * Disable PCIE
	 *  */
	val = readl(CONF_BASE_ADDR + PCIE_SYS_CTRL7);
	val &= (~(1 << PCIE_APP_LTSSM_ENBALE));
	writel(val, CONF_BASE_ADDR + PCIE_SYS_CTRL7);

	/*
	 *  * Reset
	 *  */
	val = readl(PERI_CRG_BASE + PERI_CRG44);
	val |= (1 << PCIE_X2_SRST_REQ);
	writel(val, PERI_CRG_BASE + PERI_CRG44);

	/*
	 *  * Retreat from the reset state
	 *  */
	udelay(500); /* delay 500us */
	val = readl(PERI_CRG_BASE + PERI_CRG44);
	val &= ~(1 << PCIE_X2_SRST_REQ);
	writel(val, PERI_CRG_BASE + PERI_CRG44);
	mdelay(10); /* delay 10ms */

	/*
	 *  * PCIE RC work mode
	 *  */
	val = readl(CONF_BASE_ADDR + PCIE_SYS_CTRL0);
	val &= (~(0xf << PCIE_DEVICE_TYPE));
	val |= (PCIE_WM_RC << PCIE_DEVICE_TYPE);
	writel(val, CONF_BASE_ADDR + PCIE_SYS_CTRL0);

	/*
	 *  * Enable clk
	 *  */
	val = readl(PERI_CRG_BASE + PERI_CRG44);
	val |= ((1 << PCIE_X2_BUS_CKEN) |
			(1 << PCIE_X2_SYS_CKEN) |
			(1 << PCIE_X2_PIPE_CKEN) |
			(1 << PCIE_X2_AUX_CKEN));
	writel(val, PERI_CRG_BASE + PERI_CRG44);

	mdelay(10); /* delay 10ms */

	/*
	 *  * Set PCIE Support Transfer Card
	 *  */
	val = readl(PERI_CRG_BASE + PCI_CARD);
	val |= (1 << 3); /* Move Right 3bit */
	writel(val, PERI_CRG_BASE + PCI_CARD);
	mdelay;

	/*
	 *  * Set PCIE controller class code to be PCI-PCI bridge device
	 *  */
	val = readl(CONF_BASE_ADDR + PCI_CLASS_REVISION);
	val &= ~(0xffffff00);
	val |= (0x60400 << 8); /* Move Right 8bit */
	writel(val, CONF_BASE_ADDR + PCI_CLASS_REVISION);
	udelay(1000); /* delay 1000us */

	/*
	 *  * Enable controller
	 *  */
	val = readl(CONF_BASE_ADDR + PCIE_SYS_CTRL7);
	val |= (1 << PCIE_APP_LTSSM_ENBALE);
	writel(val, CONF_BASE_ADDR + PCIE_SYS_CTRL7);
	udelay(1000); /* delay 1000us */

	val = readl(CONF_BASE_ADDR + PCI_COMMAND);
	val |= 7; /* 7: 00000111 */
	writel(val, CONF_BASE_ADDR + PCI_COMMAND);

	return 0;
}

struct pcie_iatu {
	unsigned int viewport;          /* iATU Viewport Register        */
	unsigned int region_ctrl_1;     /* Region Control 1 Register     */
	unsigned int region_ctrl_2;     /* Region Control 2 Register     */
	unsigned int lbar;              /* Lower Base Address Register   */
	unsigned int ubar;              /* Upper Base Address Register   */
	unsigned int lar;               /* Limit Address Register        */
	unsigned int ltar;      /* Lower Target Address Register */
	unsigned int utar;              /* Upper Target Address Register */
};

struct pcie_iatu iatu_table[] = {
	{
		.viewport   = 0,
		.region_ctrl_1  = 0x00000004,
		.region_ctrl_2  = 0x90000000,
		.lbar           = PCIE_EP_CONF_BASE + (1 << 20), /* Move Right 20bit */
		.ubar           = 0x0,
		.lar            = PCIE_EP_CONF_BASE + (2 << 20) - 1, /* Move Right 20bit */
		.ltar           = 0x01000000,
		.utar           = 0x00000000,
	},
	{
		.viewport       = 1,
		.region_ctrl_1  = 0x00000005,
		.region_ctrl_2  = 0x90000000,
		.lbar           = PCIE_EP_CONF_BASE + (2 << 20), /* Move Right 20bit */
		.ubar           = 0x0,
		.lar            = PCIE_EP_CONF_BASE + (__128MB__ - 1),
		.ltar           = 0x02000000,
		.utar           = 0x00000000,
	},
};

static void __arch_config_iatu_tbl(void)
{
	int i;
	struct pcie_iatu *ptable = iatu_table;
	int table_size = ARRAY_SIZE(iatu_table);

	for (i = 0; i < table_size; i++) {
		writel((ptable + i)->viewport, CONF_BASE_ADDR + 0x900);
		writel((ptable + i)->lbar, CONF_BASE_ADDR + 0x90c);
		writel((ptable + i)->ubar, CONF_BASE_ADDR + 0x910);
		writel((ptable + i)->lar,  CONF_BASE_ADDR + 0x914);
		writel((ptable + i)->ltar, CONF_BASE_ADDR + 0x918);
		writel((ptable + i)->utar, CONF_BASE_ADDR + 0x91c);
		writel((ptable + i)->region_ctrl_1, CONF_BASE_ADDR + 0x904);
		writel((ptable + i)->region_ctrl_2, CONF_BASE_ADDR + 0x908);
	}
}

void bvt_pcie_init(void)
{
	/* Static instance of the controller. */
	static struct pci_controller    pcc;
	struct pci_controller       *hose = &pcc;
	int ret;
	memset(&pcc, 0, sizeof(pcc));

	/* PCI memory space */
	pci_set_region(&hose->regions[0],
				   PCI_MEM_ADDR, PCI_MEM_ADDR,
				   PCI_MEM_SIZE, PCI_REGION_MEM);

	hose->region_count = 1;

	/* Start the controller. */
	__arch_pcie_sys_init();

	pci_set_ops(hose,
			pci_hose_read_config_byte_via_dword,
			pci_hose_read_config_word_via_dword,
			bvt_pcie_read_config,
			pci_hose_write_config_byte_via_dword,
			pci_hose_write_config_word_via_dword,
			bvt_pcie_write_config
	);

	__arch_config_iatu_tbl();

	/* To see the link state is ready. */
	ret = is_pcie_link_up();
	if (ret) {
		pci_register_hose(hose);
		hose->last_busno = pci_hose_scan(hose);
	} else {
		printf("link_up is error !\n");
	}
}
/* Probe function. */
void pci_init_board(void)
{
	bvt_pcie_init();
}
