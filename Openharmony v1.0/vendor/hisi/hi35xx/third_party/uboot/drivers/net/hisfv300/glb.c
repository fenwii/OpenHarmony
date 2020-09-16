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
 * Description: Hieth pre init
 */


#define HIETH_SFV300

#include <config.h>
#include "hieth.h"
#include "mac.h"
#include "ctrl.h"
#include "glb.h"

int hieth_glb_preinit_dummy(struct hieth_netdev_local *ld)
{
	local_lock_init(ld);

	/*
	 * hieth_glb_preinit_dummy
	 * HW MAX DEFAULT RX-PKT-LEN [42,1518]
	 * HW MAC FILTER TABLE DISABLE
	 */

	/* soft reset */
	hieth_writel_bits(ld, 1, GLB_SOFT_RESET, BITS_ETH_SOFT_RESET);
	mdelay(1);
	hieth_writel_bits(ld, 0, GLB_SOFT_RESET, BITS_ETH_SOFT_RESET);

	hieth_set_endian_mode(ld, HIETH_LITTLE_ENDIAN);

	hieth_set_linkstat(ld, 0);

	hieth_set_negmode(ld, HIETH_NEGMODE_CPUSET);

	/* RMII mode */
	hieth_set_mii_mode(ld, ud_bit_name(HIETH_MII_RMII_MODE));

	hieth_writel_bits(ld, ~0, GLB_RW_IRQ_ENA, ud_bit_name(BITS_IRQS));
	hieth_writel_bits(ld, ~0, GLB_RW_IRQ_ENA, ud_bit_name(BITS_IRQS_ENA));
	hieth_writel_bits(ld, ~0, GLB_RW_IRQ_ENA, BITS_IRQS_ENA_ALLPORT);
	hieth_irq_disable(ld, ~0);

	/* init */
	hieth_writel(ld, 0, GLB_FWCTRL);
	hieth_writel(ld, 0, GLB_MACTCTRL);

	/* disable vlan func */
	hieth_writel_bits(ld, 0, GLB_FWCTRL, BITS_VLAN_ENABLE);

	/* enable UpEther<->CPU */
	hieth_writel_bits(ld, 1, GLB_FWCTRL, BITS_FW2CPU_ENA_UP);
	hieth_writel_bits(ld, 0, GLB_FWCTRL, BITS_FWALL2CPU_UP);
	hieth_writel_bits(ld, 0, GLB_MACTCTRL, BITS_BROAD2CPU_UP);
	hieth_writel_bits(ld, 1, GLB_MACTCTRL, BITS_MACT_ENA_UP);

	/* enable DownEther<->CPU and UpEther<->CPU */
	hieth_writel_bits(ld, 1, GLB_FWCTRL, BITS_FW2CPU_ENA_DOWN);
	hieth_writel_bits(ld, 0, GLB_FWCTRL, BITS_FWALL2CPU_DOWN);
	hieth_writel_bits(ld, 0, GLB_MACTCTRL, BITS_BROAD2CPU_DOWN);
	hieth_writel_bits(ld, 1, GLB_MACTCTRL, BITS_MACT_ENA_DOWN);

	hieth_set_mac_leadcode_cnt_limit(ld, 0);

	return 0;
}
