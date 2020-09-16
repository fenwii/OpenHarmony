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
 * Description: ufs driver
 */

#include <common.h>
#include <malloc.h>
#include <asm/dma-mapping.h>
#include <cpu_func.h>
#include <ufs.h>
#include "ufs_hisi.h"
#include "scsi.h"

#define UFS_CID_SIZE    4
#define SERIAL_NUM_SIZE 12

struct dwc_ufs_hba g_dwc_host[MAX_DEVICE];
struct ufs_descriptor g_ufs_desc;
struct ufs g_ufs_info;

static uint8_t g_tx_lane_num[MAX_DEVICE] = {0};
static uint8_t g_rx_lane_num[MAX_DEVICE] = {0};
static int g_wlun = 0;
static unsigned int g_ufs_cid[UFS_CID_SIZE];

struct ufs_adapt_reg {
	unsigned int addr;
	unsigned int value[7]; /* 7 mode param */
};

static struct ufs_adapt_reg reglist_pmc[] = {
	/*     addr    G3RB  G3RA  G2RB  G2RA  G1RB  G1RA  PWM */
	{0x007e0000, { 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00}},
	{0x007e0001, { 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00}},
	{0x00fc0004, { 0x1f, 0x1f, 0x1b, 0x1b, 0x1b, 0x1b, 0x00}},
	{0x00fc0005, { 0x1f, 0x1f, 0x1b, 0x1b, 0x1b, 0x1b, 0x00}},
	{0x00fd0004, { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00}},
	{0x00fd0005, { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00}},
	{0x007f0000, { 0x24, 0x22, 0x21, 0x21, 0x13, 0x13, 0x00}},
	{0x007f0001, { 0x24, 0x22, 0x21, 0x21, 0x13, 0x13, 0x00}},
	{0x007d0000, { 0x24, 0x22, 0x21, 0x21, 0x13, 0x13, 0x00}},
	{0x007d0001, { 0x24, 0x22, 0x21, 0x21, 0x13, 0x13, 0x00}},
	{0x00370000, { 0x26, 0x26, 0x23, 0x23, 0x20, 0x20, 0x00}},
	{0x00370001, { 0x26, 0x26, 0x23, 0x23, 0x20, 0x20, 0x00}},
	{0x007b0000, { 0x26, 0x26, 0x23, 0x23, 0x20, 0x20, 0x00}},
	{0x007b0001, { 0x26, 0x26, 0x23, 0x23, 0x20, 0x20, 0x00}}
};

static void adapt_mode_change(struct pwr_mode_params *pmp)
{
	int i, mode;

	get_local_dwc_host();
	if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_HYNIX) {
		printf("H**** device must set VS_DebugSaveConfigTime 0x10\n");
		/* VS_DebugSaveConfigTime */
		send_uic_command(DME_SET, 0xd0a00000, 0x0, 0x10);
		/* sync length */
		send_uic_command(DME_SET, 0x15560000, 0x0, 0x48);
	}

#if defined(COMBO_PHY_V120)
	if (pmp->pwr_mode == FAST_MODE || pmp->pwr_mode == FASTAUTO_MODE) {
		mode = 8 - pmp->tx_gear * 2 - pmp->hs_series; /* mode[8 - gear * 2 - rate] */
	} else {
		mode = 6; /* mode[6] : PWM */
		return; /* PWM is unused here */
	}

	for (i = 0; i < sizeof(reglist_pmc) / sizeof(reglist_pmc[0]); i++)
		send_uic_command(DME_SET, reglist_pmc[i].addr, 0x0, reglist_pmc[i].value[mode]);
#endif
}

static int ufs_read_string_index(char *dest, uint8_t desc_index)
{
	struct desc_params params;
	struct dwc_ufs_query_upiu *req_upiu = NULL;
	void *resp_upiu = NULL;
	uint8_t *p = NULL;
	int ret;
	int len;
	int i;

	get_local_dwc_host();
	/* use slot 0 default */
	resp_upiu = dwc_host->lrb[0].resp_upiu;
	req_upiu = (struct dwc_ufs_query_upiu *)(dwc_host->lrb[0].cmd_upiu);

	params.req_upiu = req_upiu;
	params.part_desc = NULL;
	params.opcode = READ_DESC_OPCODE;
	params.desc_idn = STRING_DESC;
	params.desc_index = desc_index;
	params.length = STRING_DESC_LENGTH;
	modify_desc_upiu(&params);

	ret = read_descriptor(req_upiu, &resp_upiu);
	if (ret != UFS_OK) {
		printf("read descriptor fail. ret = %d\n", ret);
		return ret;
	}

	/* get string info */
	p = ((u8 *)resp_upiu + QUERY_RESPONSE_HEAD_OFFSET);
	len = p[0] / 2; /* 2 byte unicode */

	for (i = 1; i < len; i++)
		dest[i - 1] = p[2 * i + 1]; /* 2 byte unicode */
	dest[len - 1] = '\0';

	return UFS_OK;
}

static int ufs_read_string_descriptor(void)
{
	int ret;

	/* manufacturer name */
	ret = ufs_read_string_index(g_ufs_desc.str_desc.manufacturer_name,
			g_ufs_desc.dev_desc.i_manufacturer_name);
	if (ret != UFS_OK) {
		printf("get manufacturer name fail\n");
		return UFS_ERR;
	}

	/* product name */
	ret = ufs_read_string_index(g_ufs_desc.str_desc.product_name,
			g_ufs_desc.dev_desc.i_product_name);
	if (ret != UFS_OK) {
		printf("get product name fail\n");
		return UFS_ERR;
	}

	/* serial number */
	ret = ufs_read_string_index(g_ufs_desc.str_desc.serial_number,
			g_ufs_desc.dev_desc.i_serial_number);
	if (ret != UFS_OK) {
		printf("get serial number fail\n");
		return UFS_ERR;
	}

	/* oem id */
	ret = ufs_read_string_index(g_ufs_desc.str_desc.oem_id,
			g_ufs_desc.dev_desc.i_oem_id);
	if (ret != UFS_OK) {
		printf("get oem id fail\n");
		return UFS_ERR;
	}

	return UFS_OK;
}

static int ufs_read_descriptor(void *dest, uint8_t idn, uint8_t index, uint16_t length)
{
	struct desc_params params;
	struct dwc_ufs_query_upiu *req_upiu = NULL;
	void *resp_upiu = NULL;
	int ret;

	get_local_dwc_host();
	/* use slot 0 default */
	resp_upiu = dwc_host->lrb[0].resp_upiu;
	req_upiu = (struct dwc_ufs_query_upiu *)(dwc_host->lrb[0].cmd_upiu);

	params.req_upiu = req_upiu;
	params.part_desc = NULL;
	params.opcode = READ_DESC_OPCODE;
	params.desc_idn = idn;
	params.desc_index = index;
	params.length = length;
	modify_desc_upiu(&params);

	ret = read_descriptor(req_upiu, &resp_upiu);
	if (ret != UFS_OK) {
		printf("read descriptor fail. ret = %d\n", ret);
		return ret;
	}
	memcpy(dest, (void *)((u8 *)resp_upiu + QUERY_RESPONSE_HEAD_OFFSET), length);

	return UFS_OK;
}

static int ufs_read_unit_descriptor(void)
{
	int ret;
	int i;

	/* Unit Descriptor */
	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		ret = ufs_read_descriptor((void *)(&g_ufs_desc.unit_desc.unit_index_desc[i]),
				UNIT_DESC, i, UNIT_DESC_LENGTH);
		if (ret != UFS_OK) {
			printf("get unit[%d] fail\n", i);
			return UFS_ERR;
		}
	}

	/* RPMB Descriptor */
	ret = ufs_read_descriptor((void *)(&g_ufs_desc.unit_desc.unit_rpmb_desc),
			UNIT_DESC, 0xC4, UNIT_DESC_LENGTH);
	if (ret != UFS_OK) {
		printf("get rpmb fail\n");
		return UFS_ERR;
	}

	return UFS_OK;
}

static void ufs_info_show_portion(void)
{
	printf("Manufacturer ID: 0x%x\n", to_bigendian16(g_ufs_desc.dev_desc.w_manufacturer_id));
	printf("Product Name: %s\n", g_ufs_desc.str_desc.product_name);

	printf("Speed Mode: %s Gear-%d Rate-%c Lanes-%d\n",
		((DEFAULT_MODE == SLOW_MODE) ? "Slow" :
		((DEFAULT_MODE == SLOWAUTO_MODE) ? "SlowAuto" :
		((DEFAULT_MODE == FAST_MODE) ? "Fast" : "FastAuto"))),
		DEFAULT_GEAR, (DEFAULT_RATE == 1) ? 'A' : 'B', DEFAULT_LANE);
	printf("High Capacity: Yes\n");
	printf("Capacity: %lld\n", g_ufs_info.capacity);
}

static void ufs_info_show_dev_desc(void)
{
	struct ufs_device_descriptor dev;

	dev = g_ufs_desc.dev_desc;

	printf("---------------------------\n");
	printf("---UFS Device Descriptor---\n");
	printf("---------------------------\n");
	printf("bLength: 0x%x\n", dev.b_length);
	printf("bDescriptorIDN: 0x%x\n", dev.b_descriptor_idn);
	printf("bDevice: 0x%x\n", dev.b_device);
	printf("bDeviceClass: 0x%x\n", dev.b_device_class);
	printf("bDeviceSubClass: 0x%x\n", dev.b_device_sub_class);
	printf("bProtocol: 0x%x\n", dev.b_protocol);
	printf("bNumberLU: 0x%x\n", dev.b_number_lu);
	printf("bNumberWLU: 0x%x\n", dev.b_number_wlu);
	printf("bBootEnable: 0x%x\n", dev.b_boot_enable);
	printf("bDescrAccessEn: 0x%x\n", dev.b_descr_access_en);
	printf("bInitPowerMode: 0x%x\n", dev.b_init_power_mode);
	printf("bHighPriorityLUN: 0x%x\n", dev.b_high_priority_lun);
	printf("bSecureRemovalType: 0x%x\n", dev.b_secure_removal_type);
	printf("bSecurityLU: 0x%x\n", dev.b_security_lu);
	printf("bBackgroundOpsTermLat: 0x%x\n", dev.b_background_ops_term_lat);
	printf("bInitActiveICCLevel: 0x%x\n", dev.b_init_active_icc_level);
	printf("wSpecVersion: 0x%x\n", to_bigendian16(dev.w_spec_version));
	printf("wManufactureDate: 0x%x\n", to_bigendian16(dev.w_manufacture_date));
	printf("iManufacturerName: 0x%x\n", dev.i_manufacturer_name);
	printf("iProductName: 0x%x\n", dev.i_product_name);
	printf("iSerialNumber: 0x%x\n", dev.i_serial_number);
	printf("iOemID: 0x%x\n", dev.i_oem_id);
	printf("wManufacturerID: 0x%x\n", to_bigendian16(dev.w_manufacturer_id));
	printf("bUD0BaseOffset: 0x%x\n", dev.b_ud_0base_offset);
	printf("bUDConfigPLength: 0x%x\n", dev.b_ud_config_plength);
	printf("bDeviceRTTCap: 0x%x\n", dev.b_device_rtt_cap);
	printf("wPeriodicRTCUpdate: 0x%x\n", to_bigendian16(dev.w_periodic_rtc_update));
	printf("bUFSFeatureSupport: 0x%x\n", dev.b_ufs_feature_support);
	printf("bFFUTimeout: 0x%x\n", dev.b_ffu_timeout);
	printf("bQueueDepth: 0x%x\n", dev.b_queue_depth);
	printf("wDeviceVersion: 0x%x\n", to_bigendian16(dev.w_device_version));
	printf("bNumSecureWPArea: 0x%x\n", dev.b_num_secure_wp_area);
	printf("dPSAMaxDataSize: 0x%x\n", to_bigendian32(dev.d_psa_max_data_size));
	printf("bPSAStateTimeout: 0x%x\n", dev.b_psa_state_timeout);
	printf("iProductRevisionLevel: 0x%x\n", dev.i_product_revision_level);
}

static void ufs_info_show_geo_desc(void)
{
	struct ufs_geometry_descriptor geo;

	geo = g_ufs_desc.geo_desc;

	printf("-----------------------------\n");
	printf("---UFS Geometry Descriptor---\n");
	printf("-----------------------------\n");
	printf("bLength: 0x%x\n", geo.b_length);
	printf("bDescriptorIDN: 0x%x\n", geo.b_descriptor_idn);
	printf("bMediaTechnology: 0x%x\n", geo.b_media_technology);
	printf("qTotalRawDeviceCapacity: 0x%llx\n", cpu_to_be64(geo.q_total_raw_device_capacity));
	printf("bMaxNumberLU: 0x%x\n", geo.b_max_number_lu);
	printf("dSegmentSize: 0x%x\n", to_bigendian32(geo.d_segment_size));
	printf("bAllocationUnitSize: 0x%x\n", geo.b_allocation_unit_size);
	printf("bMinAddrBlockSize: 0x%x\n", geo.b_min_addr_block_size);
	printf("bOptimalReadBlockSize: 0x%x\n", geo.b_optimal_read_block_size);
	printf("bOptimalWriteBlockSize: 0x%x\n", geo.b_optimal_write_block_size);
	printf("bMaxInBufferSize: 0x%x\n", geo.b_max_in_buffer_size);
	printf("bMaxOutBufferSize: 0x%x\n", geo.b_max_out_buffer_size);
	printf("bRPMB_ReadWriteSize: 0x%x\n", geo.b_rpmb_read_write_size);
	printf("bDynamicCapacityResourcePolicy: 0x%x\n", geo.b_dynamic_capacity_resource_policy);
	printf("bDataOrdering: 0x%x\n", geo.b_data_ordering);
	printf("bMaxContexIDNumber: 0x%x\n", geo.b_max_contex_id_number);
	printf("bSysDataTagUnitSize: 0x%x\n", geo.b_sys_data_tag_unit_size);
	printf("bSysDataTagResSize: 0x%x\n", geo.b_sys_data_tag_res_size);
	printf("bSupportedSecRTypes: 0x%x\n", geo.b_supported_sec_rtypes);
	printf("wSupportedMemoryTypes: 0x%x\n", to_bigendian16(geo.w_supported_memory_types));
	printf("dSystemCodeMaxNAllocU: 0x%x\n", to_bigendian32(geo.d_system_code_max_alloc_u));
	printf("wSystemCodeCapAdjFac: 0x%x\n", to_bigendian16(geo.w_system_code_cap_adj_fac));
	printf("dNonPersistMaxNAllocU: 0x%x\n", to_bigendian32(geo.d_non_persist_max_alloc_u));
	printf("wNonPersistCapAdjFac: 0x%x\n", to_bigendian16(geo.w_non_persist_cap_adj_fac));
	printf("dEnhanced1MaxNAllocU: 0x%x\n", to_bigendian32(geo.d_enhanced1_max_alloc_u));
	printf("wEnhanced1CapAdjFac: 0x%x\n", to_bigendian16(geo.w_enhanced1_cap_adj_fac));
	printf("dEnhanced2MaxNAllocU: 0x%x\n", to_bigendian32(geo.d_enhanced2_max_alloc_u));
	printf("wEnhanced2CapAdjFac: 0x%x\n", to_bigendian16(geo.w_enhanced2_cap_adj_fac));
	printf("dEnhanced3MaxNAllocU: 0x%x\n", to_bigendian32(geo.d_enhanced3_max_alloc_u));
	printf("wEnhanced3CapAdjFac: 0x%x\n", to_bigendian16(geo.w_enhanced3_cap_adj_fac));
	printf("dEnhanced4MaxNAllocU: 0x%x\n", to_bigendian32(geo.d_enhanced4_max_alloc_u));
	printf("wEnhanced4CapAdjFac: 0x%x\n", to_bigendian16(geo.w_enhanced4_cap_adj_fac));
	printf("dOptimalLogicalBlockSize: 0x%x\n", to_bigendian32(geo.d_optimal_logical_block_size));
}

static void ufs_info_show_unit_desc(void)
{
	struct ufs_unit_index_descriptror unit;
	struct ufs_unit_rpmb_descriptror rpmb;
	int i;

	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		unit = g_ufs_desc.unit_desc.unit_index_desc[i];

		printf("----------------------------\n");
		printf("---UFS Unit %d Descriptor---\n", i);
		printf("----------------------------\n");
		printf("bLength: 0x%x\n", unit.b_length);
		printf("bDescriptorIDN: 0x%x\n", unit.b_descriptor_idn);
		printf("bUnitIndex: 0x%x\n", unit.b_unit_index);
		printf("bLUEnable: 0x%x\n", unit.b_lu_enable);
		printf("bBootLunID: 0x%x\n", unit.b_boot_lun_id);
		printf("bLUWriteProtect: 0x%x\n", unit.b_lu_write_protect);
		printf("bLUQueueDepth: 0x%x\n", unit.b_lu_queue_depth);
		printf("bPSASensitive: 0x%x\n", unit.b_psa_sensitive);
		printf("bMemoryType: 0x%x\n", unit.b_memory_type);
		printf("bDataReliability: 0x%x\n", unit.b_data_reliability);
		printf("bLogicalBlockSize: 0x%x\n", unit.b_logical_block_size);
		printf("qLogicalBlockCount: 0x%llx\n", cpu_to_be64(unit.q_logical_block_count));
		printf("dEraseBlockSize: 0x%x\n", to_bigendian32(unit.d_erase_block_size));
		printf("bProvisioningType: 0x%x\n", unit.b_provisioning_type);
		printf("qPhyMemResourceCount: 0x%x\n", to_bigendian32(unit.q_phy_mem_resource_count));
		printf("wContextCapabilities: 0x%x\n", to_bigendian16(unit.w_context_capabilities));
		printf("bLargeUnitGranularity_M1: 0x%x\n", unit.b_large_unit_granularity_m1);
	}

	rpmb = g_ufs_desc.unit_desc.unit_rpmb_desc;

	printf("------------------------------\n");
	printf("---UFS Unit RPMB Descriptor---\n");
	printf("------------------------------\n");
	printf("bLength: 0x%x\n", rpmb.b_length);
	printf("bDescriptorIDN: 0x%x\n", rpmb.b_descriptor_idn);
	printf("bUnitIndex: 0x%x\n", rpmb.b_unit_index);
	printf("bLUEnable: 0x%x\n", rpmb.b_lu_enable);
	printf("bBootLunID: 0x%x\n", rpmb.b_boot_lun_id);
	printf("bLUWriteProtect: 0x%x\n", rpmb.b_lu_write_protect);
	printf("bLUQueueDepth: 0x%x\n", rpmb.b_lu_queue_depth);
	printf("bPSASensitive: 0x%x\n", rpmb.b_psa_sensitive);
	printf("bMemoryType: 0x%x\n", rpmb.b_memory_type);
	printf("bLogicalBlockSize: 0x%x\n", rpmb.b_logical_block_size);
	printf("qLogicalBlockCount: 0x%llx\n", cpu_to_be64(rpmb.q_logical_block_count));
	printf("dEraseBlockSize: 0x%x\n", to_bigendian32(rpmb.d_erase_block_size));
	printf("bProvisioningType: 0x%x\n", rpmb.b_provisioning_type);
	printf("qPhyMemResourceCount: 0x%x\n", to_bigendian32(rpmb.q_phy_mem_resource_count));
}

static void ufs_info_show_conf_desc(void)
{
	struct ufs_dev_desc_configuration_param dev;
	struct ufs_unit_desc_configuration_param unit;
	int i;

	dev = g_ufs_desc.conf_desc.dev_desc_conf_param;

	printf("----------------------------------------\n");
	printf("---UFS Device Descriptor Config Param---\n");
	printf("----------------------------------------\n");
	printf("bLength: 0x%x\n", dev.b_length);
	printf("bDescriptorIDN: 0x%x\n", dev.b_descriptor_idn);
	printf("bConfDescContinue: 0x%x\n", dev.b_conf_desc_continue);
	printf("bBootEnable: 0x%x\n", dev.b_boot_enable);
	printf("bDescrAccessEn: 0x%x\n", dev.b_descr_access_en);
	printf("bInitPowerMode: 0x%x\n", dev.b_init_power_mode);
	printf("bHighPriorityLUN: 0x%x\n", dev.b_high_priority_lun);
	printf("bSecureRemovalType: 0x%x\n", dev.b_secure_removal_type);
	printf("bInitActiveICCLevel: 0x%x\n", dev.b_init_active_icc_level);
	printf("wPeriodicRTCUpdate: 0x%x\n", to_bigendian16(dev.w_periodic_rtc_update));

	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		unit = g_ufs_desc.conf_desc.unit_desc_conf_param[i];

		printf("-----------------------------------------\n");
		printf("---UFS Unit %d Descriptor Config Param---\n", i);
		printf("-----------------------------------------\n");
		printf("bLUEnable: 0x%x\n", unit.b_lu_enable);
		printf("bBootLunID: 0x%x\n", unit.b_boot_lun_id);
		printf("bLUWriteProtect: 0x%x\n", unit.b_lu_write_protect);
		printf("bMemoryType: 0x%x\n", unit.b_memory_type);
		printf("dNumAllocUnits: 0x%x\n", to_bigendian32(unit.d_num_alloc_units));
		printf("bDataReliability: 0x%x\n", unit.b_data_reliability);
		printf("bLogicalBlockSize: 0x%x\n", unit.b_logical_block_size);
		printf("bProvisioningType: 0x%x\n", unit.b_provisioning_type);
		printf("wContextCapabilities: 0x%x\n", to_bigendian16(unit.w_context_capabilities));
	}
}

static void ufs_info_show_str_desc(void)
{
	struct ufs_string_descriptor str;

	str = g_ufs_desc.str_desc;

	printf("---------------------------\n");
	printf("---UFS String Descriptor---\n");
	printf("---------------------------\n");
	printf("Manufacturer Name: %s\n", str.manufacturer_name);
	printf("Product Name: %s\n", str.product_name);
	printf("Serial Number: %s\n", str.serial_number);
	printf("Oem ID: %s\n", str.oem_id);
}

static void ufs_info_show_heal_desc(void)
{
	struct ufs_health_descriptor heal;

	heal = g_ufs_desc.heal_desc;

	printf("---------------------------\n");
	printf("---UFS Health Descriptor---\n");
	printf("---------------------------\n");
	printf("bLength: 0x%x\n", heal.b_length);
	printf("bDescriptorIDN: 0x%x\n", heal.b_descriptor_idn);
	printf("bPreEOLInfo: 0x%x\n", heal.b_pre_eol_info);
	printf("bDeviceLifeTimeEstA: 0x%x\n", heal.b_device_life_time_est_a);
	printf("bDeviceLifeTimeEstB: 0x%x\n", heal.b_device_life_time_est_b);
}

static void ufs_info_show_intr_desc(void)
{
	struct ufs_interconnect_descriptor intr;

	intr = g_ufs_desc.intr_desc;

	printf("---------------------------------\n");
	printf("---UFS Interconnect Descriptor---\n");
	printf("---------------------------------\n");
	printf("bLength: 0x%x\n", intr.b_length);
	printf("bDescriptorIDN: 0x%x\n", intr.b_descriptor_idn);
	printf("bcdUniproVersion: 0x%x\n", to_bigendian16(intr.bcd_unipro_version));
	printf("bcdMphyVersion: 0x%x\n", to_bigendian16(intr.bcd_mphy_version));
}

static void ufs_info_show_all(void)
{
	ufs_info_show_portion();
	ufs_info_show_dev_desc();
	ufs_info_show_conf_desc();
	ufs_info_show_unit_desc();
	ufs_info_show_intr_desc();
	ufs_info_show_str_desc();
	ufs_info_show_geo_desc();
	ufs_info_show_heal_desc();
}

static int ufs_desc_init(void)
{
	int ret;

	if (g_ufs_desc.desc_is_init == 1)
		return UFS_OK;

	ret = ufs_read_descriptor((void *)(&g_ufs_desc.conf_desc),
			CONFIGURATION_DESC, 0, CONFIGURATION_DESC_LENGTH);
	if (ret != UFS_OK) {
		printf("read configuration descriptor fail\n");
		return UFS_ERR;
	}

	ret = ufs_read_unit_descriptor();
	if (ret != UFS_OK) {
		printf("read unit descriptor fail\n");
		return UFS_ERR;
	}

	ret = ufs_read_descriptor((void *)(&g_ufs_desc.intr_desc),
			INTERCONNECT_DESC, 0, INTERCONNECT_DESC_LENGTH);
	if (ret != UFS_OK) {
		printf("read interconnect descriptor fail\n");
		return UFS_ERR;
	}

	ret = ufs_read_descriptor((void *)(&g_ufs_desc.heal_desc),
			HEALTH_DESC, 0, HEALTH_DESC_LENGTH);
	if (ret != UFS_OK) {
		printf("read health descriptor fail\n");
		return UFS_ERR;
	}

	g_ufs_desc.desc_is_init = 1;

	return UFS_OK;
}

int ufs_show_desc_info(enum info_show_type type)
{
	int ret;

	ret = ufs_desc_init();
	if (ret != UFS_OK)
		return ret;

	switch (type) {
	case UFS_INFO_SHOW_BASIC:
		ufs_info_show_portion();
		break;
	case UFS_INFO_SHOW_ALL:
		ufs_info_show_all();
		break;
	case UFS_INFO_SHOW_DEVICE_DESC:
		ufs_info_show_dev_desc();
		break;
	case UFS_INFO_SHOW_CONFIGURATION_DESC:
		ufs_info_show_conf_desc();
		break;
	case UFS_INFO_SHOW_UNIT_DESC:
		ufs_info_show_unit_desc();
		break;
	case UFS_INFO_SHOW_INTERCONNECT_DESC:
		ufs_info_show_intr_desc();
		break;
	case UFS_INFO_SHOW_STRING_DESC:
		ufs_info_show_str_desc();
		break;
	case UFS_INFO_SHOW_GEOMETRY_DESC:
		ufs_info_show_geo_desc();
		break;
	case UFS_INFO_SHOW_HEALTH_DESC:
		ufs_info_show_heal_desc();
		break;
	default:
		printf("unknown cmd\n");
		break;
	}

	return UFS_OK;
}

static void ufs_info_init(void)
{
	uint32_t lba;
	int ret;

	g_ufs_info.blocksize = LOGICAL_BLK_SIZE;
	g_ufs_info.block_read = ufs_read_storage;
	g_ufs_info.block_write = ufs_write_storage;
	g_ufs_info.boot_block_write = ufs_write_boot_storage;

	ret = ufs_read_capacity(&lba);
	if (ret != UFS_SUCCESS)
		return;

	g_ufs_info.capacity = (uint64_t)lba * LOGICAL_BLK_SIZE;
}

struct ufs *get_ufs_info(void)
{
	return &g_ufs_info;
}

void ufshci_dump(void)
{
	printf("===== UFSHCI REGISTER DUMP =====\n");
	printf("CAP:        0x%08x||VER:        0x%08x\n",
		dwc_ufs_read_reg(UFS_CAP_OFF),
		dwc_ufs_read_reg(UFS_VER_OFF));
	printf("HCPID:      0x%08x||HCMID:      0x%08x\n",
		dwc_ufs_read_reg(UFS_HCPID_OFF),
		dwc_ufs_read_reg(UFS_HCMID_OFF));
	printf("AHIT:       0x%08x||IS:         0x%08x\n",
		dwc_ufs_read_reg(UFS_AHIT_OFF),
		dwc_ufs_read_reg(UFS_IS_OFF));
	printf("IE:         0x%08x||HCS:        0x%08x\n",
		dwc_ufs_read_reg(UFS_IE_OFF),
		dwc_ufs_read_reg(UFS_HCS_OFF));
	printf("HCE:        0x%08x||UECPA:      0x%08x\n",
		dwc_ufs_read_reg(UFS_HCE_OFF),
		dwc_ufs_read_reg(UFS_UECPA_OFF));
	printf("UECDL:      0x%08x||UECN:       0x%08x\n",
		dwc_ufs_read_reg(UFS_UECDL_OFF),
		dwc_ufs_read_reg(UFS_UECN_OFF));
	printf("UECT:       0x%08x||UECDME:     0x%08x\n",
		dwc_ufs_read_reg(UFS_UECT_OFF),
		dwc_ufs_read_reg(UFS_UECDME_OFF));
	printf("UTRIACR:    0x%08x||UTRLBA:     0x%08x\n",
		dwc_ufs_read_reg(UFS_UTRIACR_OFF),
		dwc_ufs_read_reg(UFS_UTRLBA_OFF));
	printf("UTRLBAU:    0x%08x||UTRLDBR:    0x%08x\n",
		dwc_ufs_read_reg(UFS_UTRLBAU_OFF),
		dwc_ufs_read_reg(UFS_UTRLDBR_OFF));
	printf("UTRLCLR:    0x%08x||UTRLRSR:    0x%08x\n",
		dwc_ufs_read_reg(UFS_UTRLCLR_OFF),
		dwc_ufs_read_reg(UFS_UTRLRSR_OFF));
	printf("UTMRLBA:    0x%08x||UTMRLBAU:   0x%08x\n",
		dwc_ufs_read_reg(UFS_UTMRLBA_OFF),
		dwc_ufs_read_reg(UFS_UTMRLBAU_OFF));
	printf("UTMRLDBR:   0x%08x||UTMRLCLR:   0x%08x\n",
		dwc_ufs_read_reg(UFS_UTMRLDBR_OFF),
		dwc_ufs_read_reg(UFS_UTMRLCLR_OFF));
	printf("UTMRLRSR:   0x%08x\n",
		dwc_ufs_read_reg(UFS_UTMRLRSR_OFF));
	printf("================================\n");
}

void ufs_reg_dump(void)
{
	ufshci_dump();
}

static uint8_t dwc_ufshcd_get_xfer_req_free_slot(struct dwc_ufs_hba *hba)
{
	uint8_t slot;

	for (slot = 0; slot < hba->nutrs; slot++) {
		if ((hba->outstanding_xfer_reqs & BIT(slot)) == 0)
			return slot;
	}

	printf("get xfer free_slot fail\n");
	return BAD_SLOT;
}

uint32_t uic_cmd_read(uint32_t command, uint32_t arg1)
{
	int retry;
	uint32_t reg;

	retry = 100; /* retry 100 times */
	while (--retry) {
		if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_UCRDY_BIT)
			break;
		ufs_waitms(1);
	}
	if (retry <= 0) {
		printf("%s: wait HCS.UCRDY timeout\n", __func__);
		ufshci_dump();
	}

	dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
	dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, arg1);
	dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, 0x0);
	dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, 0x0);

	dwc_ufs_write_reg(UFS_UICCMD_OFF, (command & 0xFF));

	retry = 100; /* retry 100 times */
	while (--retry) {
		if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT)
			break;
		ufs_waitms(1);
	}

	if (retry <= 0) {
		printf("%s: timeout, cmd:0x%x, arg1:0x%x\n",
			__func__, command, arg1);
		ufshci_dump();
	}

	/* clear interrupt status */
	dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UCCS_BIT);

	if (dwc_ufs_read_reg(UFS_UICCMDARG2_OFF) & 0xFF) {
		printf("%s:response error\n", __func__);
		ufshci_dump();
	}

	if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT) {
		printf("%s:UFS_IS_UE_BIT error\n", __func__);
		/* clear interrupt status */
		/* the UE error cause by PA_Init or some other reason,
		* should clear it, or it will repeatly come out ! */
		dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UE_BIT);
		ufs_waitms(1);
		if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT)
			printf("%s:can not clear the UE_BIT\n",
				__func__);
	}

	/* get uic result */
	reg = dwc_ufs_read_reg(UFS_UICCMDARG3_OFF);

	return reg;
}

/***************************************************************
 * send_uic_command
 * Description: Programs the Command Argument and the Command
 *     Register to send the DME_LINK_STARTUP command
 *     to the device
 *
 ***************************************************************/
void send_uic_command(uint32_t command, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	int retry;
	int val;

	retry = 100; /* retry 100 times */
	while (--retry) {
		if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_UCRDY_BIT)
			break;
		ufs_waitms(1);
	}
	if (retry <= 0) {
		printf("%s: wait HCS.UCRDY timeout\n", __func__);
		ufshci_dump();
	}

	dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
	dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, arg1);
	dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, arg2);
	dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, arg3);

	dwc_ufs_write_reg(UFS_UICCMD_OFF, (command & 0xFF));

	retry = 500; /* retry 500 times */
	while (--retry) {
		if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT)
			break;
		ufs_waitms(1);
	}

	if (retry <= 0)
		printf("%s: timeout cmd:0x%x, arg1:0x%x, "
			"arg2:0x%x, arg3:0x%x\n", __func__,
			command, arg1, arg2, arg3);

	/* clear interrupt status */
	dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UCCS_BIT);

	val  = dwc_ufs_read_reg(UFS_UICCMDARG2_OFF);
	if (val & 0xFF)
		printf("%s: response error, cmd:0x%x, arg1 is 0x%x, "
			"response is 0x%x\n", __func__, command, arg1, val);

	if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT) {
		printf("%s: UFS_IS_UE_BIT error, cmd:0x%x, arg1 is 0x%x\n",
			__func__, command, arg1);
		/* the UE error cause by PA_Init or some other reason,
		* should clear it, or it will repeatly come out ! */
		dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UE_BIT);
		ufs_waitms(1);
		if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UE_BIT)
			printf("%s:can not clear the UE_BIT\n",
				__func__);
	}
}

/***************************************************************
 * setup_snps_mphy_tc
 * Description: Programs the Unipro and Synopsys Mphy for
 *
 ***************************************************************/
void setup_snps_mphy_tc(void)
{
	uint32_t retry = 10;

	/* Read the DME_Resest (0xD010) attribute. It must return 0
	indicating that the reset sequence is completed. */
	do {
		if (uic_cmd_read(0x01, 0xD0100000) == 1)
			break;
		ufs_waitms(1);
	} while (retry--);
	/* DME layer enable ---zhaozhiliang, to delete? */
	send_uic_command(DME_SET, 0xd0000000, 0x0, 0x01);
}

static int ufs_hc_enable(void)
{
	int retry = 3; /* retry 3 times */
	int timeout;

	do {
		dwc_ufs_write_reg(UFS_HCE_OFF, UFS_HCE_RESET_BIT);
		timeout = 3; /* 3ms timeout */
		for (;;) {
			if (dwc_ufs_read_reg(UFS_HCE_OFF) & UFS_HCE_RESET_BIT) {
				return UFS_SUCCESS;
			}
			ufs_waitms(1);

			if (--timeout == 0) {
				printf("wait HCE time out\n");
				break;
			}
		}
	} while (--retry > 0);

	return UFS_FAILURE;
}

static void ufs_hardware_init(void)
{
	uint32_t reg;

	reg = readl(CRG_REG_BASE + PERI_CRG96);
	reg |= BIT_UFS_CLK_EN;
	writel(reg, CRG_REG_BASE + PERI_CRG96);

	reg = readl(CRG_REG_BASE + PERI_CRG96);
	reg |= BIT_UFS_SRST_REQ;
	writel(reg, CRG_REG_BASE + PERI_CRG96);

	udelay(1);

	reg = readl(CRG_REG_BASE + PERI_CRG96);
	reg &= ~BIT_UFS_SRST_REQ;
	writel(reg, CRG_REG_BASE + PERI_CRG96);

	udelay(1);

	reg = readl(CRG_REG_BASE + PERI_CRG96);
	reg |= BIT_UFS_AXI_SRST_REQ;
	writel(reg, CRG_REG_BASE + PERI_CRG96);

	udelay(1);

	reg = readl(CRG_REG_BASE + PERI_CRG96);
	reg &= ~BIT_UFS_AXI_SRST_REQ;
	writel(reg, CRG_REG_BASE + PERI_CRG96);

	reg = readl(MISC_REG_BASE + MISC_CTRL17);
	reg |= BIT_UFS_ENABLE;
	writel(reg, MISC_REG_BASE + MISC_CTRL17);

	reg = readl(MISC_REG_BASE + MISC_CTRL17);
	reg &= ~BIT_DA_UFS_REFCLK_OEN;
	reg &= ~MASK_DA_UFS_REFCLK_DS;
	reg |= (BIT_DA_UFS_REFCLK_DS0 |
		BIT_DA_UFS_REFCLK_DS1 |
		BIT_DA_UFS_REFCLK_SL);
	writel(reg, MISC_REG_BASE + MISC_CTRL17);

	reg = readl(MISC_REG_BASE + MISC_CTRL17);
	reg &= ~BIT_DA_UFS_RESET_OEN;
	reg &= ~MASK_DA_UFS_RESET_DS;
	reg |= BIT_DA_UFS_RESET_SL;
	writel(reg, MISC_REG_BASE + MISC_CTRL17);

	reg = readl(MISC_REG_BASE + MISC_CTRL17);
	reg &= ~BIT_UFS_PAD_RESET;
	writel(reg, MISC_REG_BASE + MISC_CTRL17);

	udelay(10); /* delay 10 us */

	reg = readl(MISC_REG_BASE + MISC_CTRL17);
	reg |= BIT_UFS_PAD_RESET;
	writel(reg, MISC_REG_BASE + MISC_CTRL17);
}

static void phy_init_config(void)
{
#if defined(COMBO_PHY_V120)
	/* Rx SKP_DET_SEL, lane0 */
	send_uic_command(DME_SET, attr_mrx0(SKP_DET_SEL), 0x0, SKP_DET_SEL_EN);
	/* Rx SKP_DET_SEL, lane1 */
	send_uic_command(DME_SET, attr_mrx1(SKP_DET_SEL), 0x0, SKP_DET_SEL_EN);

	/* VCO_AUTO_CHG */
	send_uic_command(DME_SET, attr_mcb(VCO_AUTO_CHG), 0x0, (VCO_AUTO_CHG_EN | VCO_FORCE_ON_EN));
	/* RX_SQ_VREF, lane0 */
	send_uic_command(DME_SET, attr_mrx0(RX_SQ_VREF), 0x0, RX_SQ_VREF_175);
	/* RX_SQ_VREF, lane1 */
	send_uic_command(DME_SET, attr_mrx1(RX_SQ_VREF), 0x0, RX_SQ_VREF_175);

	/* Dif_N debouse */
	send_uic_command(DME_SET, attr_mrx0(0xeb), 0x0, 0x64);
	/* Dif_N debouse */
	send_uic_command(DME_SET, attr_mrx1(0xeb), 0x0, 0x64);

	/* dvalid timer */
	send_uic_command(DME_SET, attr_mrx0(0x0e), 0x0, 0xF0);
	/* dvalid timer */
	send_uic_command(DME_SET, attr_mrx1(0x0e), 0x0, 0xF0);

	/* AD_DIF_P_LS_TIMEOUT_VAL, lane0 */
	send_uic_command(DME_SET, attr_mrx0(AD_DIF_P_LS_TIMEOUT_VAL), 0x0, PWM_PREPARE_TO);
	/* AD_DIF_P_LS_TIMEOUT_VAL, lane1 */
	send_uic_command(DME_SET, attr_mrx1(AD_DIF_P_LS_TIMEOUT_VAL), 0x0, PWM_PREPARE_TO);

	send_uic_command(DME_SET, 0x00F40004, 0x0, 0x1); /* RX_EQ_SEL_R */
	send_uic_command(DME_SET, 0x00F40005, 0x0, 0x1); /* RX_EQ_SEL_R */

	send_uic_command(DME_SET, 0x00F20004, 0x0, 0x3); /* RX_EQ_SEL_C */
	send_uic_command(DME_SET, 0x00F20005, 0x0, 0x3); /* RX_EQ_SEL_C */

	send_uic_command(DME_SET, 0x00FB0004, 0x0, 0x3); /* RX_VSEL */
	send_uic_command(DME_SET, 0x00FB0005, 0x0, 0x3); /* RX_VSEL */

	send_uic_command(DME_SET, 0x00f60004, 0x0, 0x2); /* RX_DLF Lane 0 */
	send_uic_command(DME_SET, 0x00f60005, 0x0, 0x2); /* RX_DLF Lane 1 */

	send_uic_command(DME_SET, 0x000a0004, 0x0, 0x2); /* RX H8_TIMEOUT_VAL, Lane 0 */
	send_uic_command(DME_SET, 0x000a0005, 0x0, 0x2); /* RX H8_TIMEOUT_VAL, Lane 1 */

	/* in low temperature to solve the PLL's starting of oscillation */
	send_uic_command(DME_SET, 0x00d40000, 0x0, 0x31); /* RG_PLL_DMY0 */
	send_uic_command(DME_SET, 0x00730000, 0x0, 0x4); /* TX_PHY_CONFIG II */
	send_uic_command(DME_SET, 0x00730001, 0x0, 0x4); /* TX_PHY_CONFIG II */
#endif /* end of COMBO_PHY_V120 */
}

static void ufs_hc_init(void)
{
	uint32_t reg;

	/* get the 1us tick clock, the HCLK is 266Mhz? */
	dwc_ufs_write_reg(UFS_HCLKDIV_OFF, UFS_HCLKDIV_NORMAL_VALUE);

	phy_init_config();

	send_uic_command(DME_SET, attr_mrx0(MRX_EN), 0x0, MRX_ENABLE); /* RX enable, lane0 */
	send_uic_command(DME_SET, attr_mrx1(MRX_EN), 0x0, MRX_ENABLE); /* RX enable, lane1 */

	/* disable auto H8 */
	reg = dwc_ufs_read_reg(UFS_AHIT_OFF);
	reg = reg & (~UFS_AHIT_AH8ITV_MASK);
	dwc_ufs_write_reg(UFS_AHIT_OFF, reg);

	setup_snps_mphy_tc();
	/* disable Vswing change */
	/* measure the power, can close it */
	send_uic_command(DME_SET, 0x00C70000, 0x0, 0x3);
	send_uic_command(DME_SET, 0x00C80000, 0x0, 0x3);

#ifdef CLOSE_CLK_GATING
	send_uic_command(DME_SET, 0x00cf0004, 0x0, 0x02); /* RX_STALL */
	send_uic_command(DME_SET, 0x00cf0005, 0x0, 0x02);
	send_uic_command(DME_SET, 0x00d00004, 0x0, 0x02); /* RX_SLEEP */
	send_uic_command(DME_SET, 0x00d00005, 0x0, 0x02);
	send_uic_command(DME_SET, 0x00cc0004, 0x0, 0x03); /* RX_HS_CLK_EN */
	send_uic_command(DME_SET, 0x00cc0005, 0x0, 0x03);
	send_uic_command(DME_SET, 0x00cd0004, 0x0, 0x03); /* RX_LS_CLK_EN */
	send_uic_command(DME_SET, 0x00cd0005, 0x0, 0x03);
#endif

#if defined(COMBO_PHY_V120)
	send_uic_command(DME_SET, 0x00c50000, 0x0, 0x03); /* RG_PLL_RXHS_EN */
	send_uic_command(DME_SET, 0x00c60000, 0x0, 0x03);
	send_uic_command(DME_SET, 0x00E90004, 0x0, 0x00); /* RX_HS_DATA_VALID_TIMER_VAL0 */
	send_uic_command(DME_SET, 0x00E90005, 0x0, 0x00);
	send_uic_command(DME_SET, 0x00EA0004, 0x0, 0x10); /* RX_HS_DATA_VALID_TIMER_VAL1 */
	send_uic_command(DME_SET, 0x00EA0005, 0x0, 0x10);
#endif
	/* set the HS-prepare length and sync length to MAX value, try to solve
	  the data check error problem, the device seems not receive the write
	  cmd. */
	/* PA_TxHsG1SyncLength , can not set MPHY's register directly */
	send_uic_command(DME_SET, 0x15520000, 0x0, 0x4F);
	/* PA_TxHsG2SyncLength , can not set MPHY's register directly */
	send_uic_command(DME_SET, 0x15540000, 0x0, 0x4F);
	/* PA_TxHsG3SyncLength , can not set MPHY's register directly */
	send_uic_command(DME_SET, 0x15560000, 0x0, 0x4F);

	send_uic_command(DME_SET, 0x00ca0000, 0x0, 0x3); /* pll always on */
	send_uic_command(DME_SET, 0xD0850000, 0x0, 0x1); /* update */

	/* to check if the unipro have to close the LCC */
	/* Unipro PA_Local_TX_LCC_Enable */
	send_uic_command(DME_SET, 0x155E0000, 0x0, 0x0);
	/* close Unipro VS_Mk2ExtnSupport */
	send_uic_command(DME_SET, 0xD0AB0000, 0x0, 0x0);

	if (uic_cmd_read(DME_GET, 0xD0AB0000) != 0)
		printf("Warring!!! close VS_Mk2ExtnSupport failed\n");
}

int ufs_link_startup(void)
{
	int retry = 4; /* retry 4 times */
	int i = 0;

	dwc_ufs_write_reg(UFS_IS_OFF, 0xFFFFFFFF);
	while (retry-- > 0) {
		dwc_ufs_write_reg(UFS_UICCMDARG1_OFF, 0);
		dwc_ufs_write_reg(UFS_UICCMDARG2_OFF, 0);
		dwc_ufs_write_reg(UFS_UICCMDARG3_OFF, 0);

		dwc_ufs_write_reg(UFS_UICCMD_OFF, (UIC_LINK_STARTUP_CMD & 0xFF));

		i = 0;
		for (;;) {
			if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UCCS_BIT) {
				dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UCCS_BIT);
				break;
			}
			ufs_waitms(1);
			if (i++ > 200) { /* 200ms timeout */
				printf("ufs link startup wait UCCS timeout\n");
				break;
			}
		}

		if (dwc_ufs_read_reg(UFS_HCS_OFF) & UFS_HCS_DP_BIT) {
			if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_ULSS_BIT)
				dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_ULSS_BIT);

			dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UE_BIT);
			return UFS_SUCCESS;
		}

		printf("ufs link startup check DP fail\n");
		if (retry <= 0) {
			printf("ufs link startup fail\n");
			return UFS_LINK_STARTUP_FAIL;
		}
		i = 0;
		for (;;) {
			if (dwc_ufs_read_reg(UFS_IS_OFF) &
				UFS_IS_ULSS_BIT)
				break;
			ufs_waitms(1);
			if (i++ > 50) { /* 50ms timeout */
				printf("ufs link startup wait ULSS timeout\n");
				break;
			}
		}
	}

	printf("ufs link startup fail\n");
	return UFS_LINK_STARTUP_FAIL;
}

static int update_snum_buff(uint8_t *snum_buf, int sunm_buf_len,
				uint8_t *resp_buf, int resp_buf_len)
{
	uint8_t i;

	get_local_dwc_host();

	(void)sunm_buf_len;
	(void)resp_buf_len;

	if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_TOSHIBA) {
		/*
		 * toshiba: 20 Byte, every two byte has a prefix of 0x00,
		 * trim the 0x00 bytes
		 */
		for (i = 0; i < SERIAL_NUM_SIZE - 2; i++) /* exclude last 2 */
			snum_buf[i] = resp_buf[2 * i + 1]; /* 2 byte unicode */
		/* append two 0x00 byte in the end */
		snum_buf[SERIAL_NUM_SIZE - 2] = 0; /* end 2 */
		snum_buf[SERIAL_NUM_SIZE - 1] = 0; /* end 1 */
	} else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_SAMSUNG) {
		/*
		 * Samsung new ufs device, need 24 Bytes for serial
		 * number, transfer unicode to 12 bytes
		 */
		for (i = 0; i < SERIAL_NUM_SIZE; i++)
			snum_buf[i] = resp_buf[i * 2 + 1]; /* 2 byte unicode */
	} else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_HYNIX) {
		/* hynix only have 6 Byte, add a 0x00 before every byte */
		for (i = 0; i * 2 < SERIAL_NUM_SIZE; i++) { /* 2 byte unicode */
			snum_buf[i * 2] = 0x0; /* 2 byte unicode */
			snum_buf[i * 2 + 1] = resp_buf[i]; /* 2 byte unicode */
		}
	} else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_HI1861) {
		for (i = 0; i < SERIAL_NUM_SIZE; i++)
			snum_buf[i] = resp_buf[i];
	} else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_MICRON) {
		/* Micron only need 4 Byte */
		for (i = 0; i < 4; i++)
			snum_buf[i] = resp_buf[i];
		for (i = 4; i < SERIAL_NUM_SIZE; i++) /* 4 byte */
			snum_buf[i] = 0;
	} else if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_SANDISK) {
		/*
		 * Sandisk need 24 Bytes for serial number,
		 * transfer unicode to 12 bytes
		 */
		for (i = 0; i < SERIAL_NUM_SIZE; i++)
			snum_buf[i] = resp_buf[i * 2 + 1]; /* 2 byte unicode */
	} else {
		printf("%s: unknown manufacturer_id (0x%x)\n",
			__func__, dwc_host->manufacturer_id);
		return -1;
	}
	return 0;
}

unsigned int *ufs_pack_cid(void)
{
	u8 resp_upiu[STRING_DESC_LENGTH]; /* use the slot 0 default */
	u8 snum_buf[SERIAL_NUM_SIZE] = {0};
	u8 resp_buf[2 * SERIAL_NUM_SIZE + 2]; /* 2 byte unicode */
	int ret;

	get_local_dwc_host();

	ret = ufs_read_descriptor((void *)resp_upiu, STRING_DESC,
			g_ufs_desc.dev_desc.i_serial_number, STRING_DESC_LENGTH);
	if (ret != UFS_SUCCESS) {
		printf("%s: read_descriptor fail. ret = %d\n", __func__, ret);
		return NULL;
	}
	/* 32B query response head + 2B string descriptor head */
	memcpy((void *)resp_buf, (void *)(resp_upiu + 2), SERIAL_NUM_SIZE * 2); /* 2 byte unicode */

	/* clear and init ufs_cid value */
	g_ufs_cid[0] = 0; /* dw 0 */
	g_ufs_cid[1] = 0; /* dw 1 */
	g_ufs_cid[2] = 0; /* dw 2 */

	ret = update_snum_buff(snum_buf, SERIAL_NUM_SIZE, (u8 *)resp_buf,
				2 * SERIAL_NUM_SIZE + 2); /* 2 byte unicode */
	if (ret != 0)
		return NULL;

	memcpy(g_ufs_cid, (unsigned int *)snum_buf, (unsigned int)sizeof(snum_buf));
	/* dw 3, date 31 - 16, id 15 - 0 */
	g_ufs_cid[3] = ((uint32_t)(dwc_host->manufacturer_date) << 16) | dwc_host->manufacturer_id;

	return g_ufs_cid;
}

/**
 * Number of UTP Transfer Request Slots (NUTRS)
 * Number of UTP Task management Request Slots(NUTMRS)
 * Auto Hibernate Support (AUTOH8)
 */
static void dwc_ufshcd_read_caps(struct dwc_ufs_hba *hba)
{
	hba->caps = dwc_ufs_read_reg(UFS_CAP_OFF);

	hba->nutrs = (uint8_t)(hba->caps & DWC_UFS_NUTRS_MASK) + 1;
	hba->nutmrs = (uint8_t)
		((hba->caps & DWC_UFS_NUTMRS_MASK) >> DWC_UFS_NUTMRS_SHIFT) + 1;
	hba->autoh8 = (uint8_t)
		((hba->caps & DWC_UFS_AUTOH8) >> DWC_UFS_AUTOH8_SHIFT);
}

static void ufshcd_memory_align(struct dwc_ufs_hba *hba)
{
	uint32_t utrl_size, utmrl_size, ucdl_size;
	uint64_t cur_pool = (uint64_t)(uintptr_t)hba->mem_pool;

	utrl_size = sizeof(struct dwc_ufs_utrd) * hba->nutrs;
	utmrl_size = sizeof(struct dwc_ufs_utmrd) * hba->nutmrs;
	ucdl_size = sizeof(struct dwc_ufs_ucd) * hba->nutrs;

	/* Allocate Dma'able memory for UTP Transfer Request List
	 * UFS spec constraints: Base of List should be aligned to 1024 byte
	 * (1K boundary)
	 */
	cur_pool = bytes_align_1024(cur_pool);
	hba->utrl_base_addr = (struct dwc_ufs_utrd *)(uintptr_t)cur_pool;

	ufs_pr_mem("utrl  start:0x%llx end:0x%llx sz:0x%x\n",
		cur_pool, cur_pool + utrl_size, utrl_size);

	/* Allocate Dma'able memory for UTP Task management Request List
	 * UFS spec constraints: Base of list should be aligned to 1024 byte
	 * (1K boundary)
	 */
	cur_pool += utrl_size;
	cur_pool = bytes_align_1024(cur_pool);
	hba->utmrl_base_addr = (struct dwc_ufs_utmrd *)(uintptr_t)cur_pool;

	ufs_pr_mem("utmrl start:0x%llx end:0x%llx sz:0x%x\n",
		cur_pool, cur_pool + utmrl_size, utmrl_size);

	/* Allocate Dma'able memory for UTP Command Descriptor List
	 * Every Command Descriptor block should be aligned to 128 byte
	 */
	cur_pool += utmrl_size;
	cur_pool = bytes_align_128(cur_pool);
	hba->ucdl_base_addr = (struct dwc_ufs_ucd *)(uintptr_t)cur_pool;

	ufs_pr_mem("ucdl  start:0x%llx end:0x%llx sz:0x%x\n",
		cur_pool, cur_pool + ucdl_size, ucdl_size);

	/* Allocate memory for local reference block */
	cur_pool += ucdl_size;
	hba->lrb = (struct dwc_ufs_hcd_lrb *)(uintptr_t)cur_pool;

	ufs_pr_mem("lrb   start:0x%llx sz:0x%x\n",
		cur_pool, sizeof(struct dwc_ufs_hcd_lrb) * hba->nutrs);
}

/**
 * Allocate memory for Host controller interface.
 * Following are the memories allocation by this function.
 * - DMA'able memory for UTP transfer request descriptor list
 * - DMA'able memory for UTP task management request list
 * - DMA'able memory for command table
 *    - Command UPIU's
 *    - Response UPIU's
 *    - PRD tables
 * - Non-DMA'able memory for local reference blocks; House keeping
 * @hba: Pointer to private structure
 *
 * Returns 0 for success, non-zero in case of failure
 */
static int dwc_ufshcd_alloc_interface_memory(struct dwc_ufs_hba *hba)
{
	uint32_t utrl_size, utmrl_size, ucdl_size, lrb_size, total_size;

	utrl_size = sizeof(struct dwc_ufs_utrd) * hba->nutrs;
	utmrl_size = sizeof(struct dwc_ufs_utmrd) * hba->nutmrs;
	ucdl_size = sizeof(struct dwc_ufs_ucd) * hba->nutrs;
	lrb_size = sizeof(struct dwc_ufs_hcd_lrb) * hba->nutrs;

	total_size = utrl_size + DWC_UTRL_BASE_ALIGN +
		utmrl_size + DWC_UTRL_BASE_ALIGN +
		ucdl_size + DWC_CMD_BASE_ALIGN + lrb_size;

	hba->mem_pool = malloc(total_size);
	if (hba->mem_pool == NULL) {
		printf("%s: Memory Allocation Failed\n", __func__);
		return UFS_ERR;
	}
	memset(hba->mem_pool, 0, total_size);

	ufs_pr_mem("\n@@ ufs memory pool info @@\n");
	ufs_pr_mem("poll  start:0x%llx sz:0x%x\n",
		(uint64_t)(uintptr_t)hba->mem_pool, total_size);
	ufshcd_memory_align(hba);

	/* Allocate memory for wr_buf, LOGICAL_BLK_SIZE aligned */
	hba->wr_buf = memalign(LOGICAL_BLK_SIZE, LOGICAL_BLK_SIZE);
	if (hba->wr_buf == NULL) {
		printf("%s: Write Read Memory Allocation Failed\n",
			__func__);
		goto err_alloc;
	}
	ufs_pr_mem("wrbuf start:0x%llx end:0x%llx sz:0x%x\n",
		(uint64_t)(uintptr_t)hba->wr_buf,
		(uint64_t)(uintptr_t)hba->wr_buf + LOGICAL_BLK_SIZE,
		LOGICAL_BLK_SIZE);

	return UFS_OK;

err_alloc:
	if (hba->mem_pool)
		free(hba->mem_pool);
	hba->mem_pool = NULL;

	return UFS_ERR;
}

/**
 * This function configures interface memory
 * -  For every UTRD,
 *	- initializes the Command UPIU base address (Lo and High)
 *	- response upiu length and offset
 *	- prdt offset
 * - Some key fields are updated in respective lrbs
 *      - utrd addresses
 *      - command upiu addresses
 *      - response upiu addresses
 *      - prdt base address
 * @hba: Pointer to private structure
 *
 * Returns void
 */
static void dwc_ufshcd_configure_interface_memory(const struct dwc_ufs_hba *hba)
{
	uint32_t i;
	struct dwc_ufs_utrd *utrl; /* Pointer to UTR List */
	struct dwc_ufs_ucd *ucdl;  /* Pointer to UCD List */
	uint64_t ucdl_dma_addr;
	uint64_t ucd_dma_addr;

	utrl = hba->utrl_base_addr;
	ucdl = hba->ucdl_base_addr;
	ucdl_dma_addr = (uint64_t)(uintptr_t)hba->ucdl_base_addr; /* UCD list Base address */

	/* For as many UTP Transfer Requests in the list */
	for (i = 0; i < hba->nutrs; i++) {
		/* Configure UTRD with UCD base address */
		ucd_dma_addr = ucdl_dma_addr + (uint64_t)sizeof(struct dwc_ufs_ucd) * i;
		utrl[i].ucdba = (lower_32_bits(ucd_dma_addr));
		utrl[i].ucdbau = (upper_32_bits(ucd_dma_addr));

		/* Configure Response UPIU offset and length */
		/* These fields are in Dword format */
		utrl[i].resp_upiu_offset = to_littleendian16((uint16_t)
			((u32)offsetof(struct dwc_ufs_ucd, resp_upiu) >> UFS_DWORD_SHIFT));
		utrl[i].resp_upiu_length = to_littleendian16((uint16_t)
			(DWC_UCD_ALIGN >> UFS_DWORD_SHIFT));
		/* Configure prdt length and offset */
		utrl[i].prdt_offset = to_littleendian16((uint16_t)
			((u32)offsetof(struct dwc_ufs_ucd, prdt) >> UFS_DWORD_SHIFT));
		utrl[i].prdt_length = to_littleendian16(0);

		/* Update LRB */
		hba->lrb[i].utrd = (utrl + i);
		hba->lrb[i].cmd_upiu = (struct dwc_ufs_cmd_upiu *)(ucdl + i);
		hba->lrb[i].resp_upiu = (struct dwc_ufs_resp_upiu *)(ucdl[i].resp_upiu);
		hba->lrb[i].prdt = (struct dwc_ufs_prd *)(ucdl[i].prdt);
	}
}

/**
 * Get UFS controller state
 * @hba: Private structure pointer
 *
 * Returns TRUE if controller is active, FALSE otherwise
 */
static int dwc_ufshcd_is_hba_active(void)
{
	return (dwc_ufs_read_reg(UFS_HCE_OFF) & 0x1) ? UFS_OK : UFS_ERR;
}

/**
 * This function performs the initialization of DWC UFS HC descriptors
 * with memory base addresses
 * Before updating the descriptor addresses, it checks host controller is
 * enabled. If not returns error. If enabled, both transfer descriptor
 * pointers and tm descriptor pointers are programmed from the drivers
 * private structure
 * @hba: pointer to drivers private structure
 *
 * Returns void
 */
static void dwc_ufshcd_initialize_hba_desc_pointers(struct dwc_ufs_hba *hba)
{
	/* If the Host Controller is not active, return error */
	if (dwc_ufshcd_is_hba_active()) {
		printf(" not active , error\n");
		return;
	}

	/* Configure UTRL and UTMRL base address registers */
	dwc_ufs_write_reg(UFS_UTRLBA_OFF,
		lower_32_bits((uintptr_t)hba->utrl_base_addr));
	dwc_ufs_write_reg(UFS_UTRLBAU_OFF,
		upper_32_bits((uintptr_t)hba->utrl_base_addr));

	dwc_ufs_write_reg(UFS_UTMRLBA_OFF,
		lower_32_bits((uintptr_t)hba->utmrl_base_addr));
	dwc_ufs_write_reg(UFS_UTMRLBAU_OFF,
		upper_32_bits((uintptr_t)hba->utmrl_base_addr));
}

static void create_prdt_part(struct cmd_param *param, uint32_t buf_size, uint8_t free_slot)
{
	int i;
	uint32_t size = param->size;
	struct dwc_ufs_prd *prdt = NULL;

	get_local_dwc_host();

	prdt = dwc_host->lrb[free_slot].prdt;
	/* Fill PRD Table Info */
	for (i = 0; (size); i++) {
		prdt[i].base_addr = (lower_32_bits(param->addr + (i * buf_size)));
		prdt[i].upper_addr = (upper_32_bits(param->addr + (i * buf_size)));
		prdt[i].reserved1 = 0x0;
		prdt[i].size = to_littleendian32(((buf_size < size) ? buf_size : size) - 1);
		size -= (buf_size < size) ? buf_size : size;
	}
}

static void create_cmd_part(uint32_t opcode, uint8_t upiu_flags,
				struct cmd_param *param, uint8_t free_slot)
{
	struct dwc_ufs_cmd_upiu *cmd_upiu_ptr = NULL;
	struct dwc_ufs_ucd *ucd = NULL;

	get_local_dwc_host();

	ucd = dwc_host->ucdl_base_addr;
	ucd += free_slot;
	cmd_upiu_ptr = (struct dwc_ufs_cmd_upiu *)ucd->cmd_upiu;

	cmd_upiu_ptr->trans_type = 0x01;
	cmd_upiu_ptr->flags = upiu_flags;
	cmd_upiu_ptr->lun = dwc_host->active_lun;
	cmd_upiu_ptr->task_tag = free_slot;
	cmd_upiu_ptr->cmd_set_type = 0x0;
	cmd_upiu_ptr->reserved_1_0 = 0x0;
	cmd_upiu_ptr->reserved_1_1 = 0x0;
	cmd_upiu_ptr->reserved_1_2 = 0x0;
	cmd_upiu_ptr->tot_ehs_len = 0x0;
	cmd_upiu_ptr->reserved_2 = 0x0;
	cmd_upiu_ptr->data_seg_len = 0x0;
	cmd_upiu_ptr->exp_data_xfer_len = to_bigendian32(param->size);

	if (opcode == UFS_OP_READ_10 || opcode == UFS_OP_WRITE_10 ||
	    opcode == UFS_OP_SYNCHRONIZE_CACHE_10) {
		get_cmnd(opcode, (uint32_t)(param->src / LOGICAL_BLK_SIZE),
			(param->size / LOGICAL_BLK_SIZE), cmd_upiu_ptr->cdb);
	} else {
		get_cmnd(opcode, 0, param->size, cmd_upiu_ptr->cdb);
	}

	/* In Power Management Command: START STOP UNIT, the LUN is fixed
	to 0x50 or 0xD0 for W-LUN */
	if (opcode == UFS_OP_START_STOP_UNIT && ((cmd_upiu_ptr->cdb[0x4] & 0xF0) != 0))
		cmd_upiu_ptr->lun = 0xD0;
}

/***************************************************************
 * create_cmd_upiu
 * Description: Fills the Command UPIU memory,
 *              updates prdt entries
 * free_slot:free slot in memory, 0~31 in UTRL, 0~7 in UTMRL
 *
 ***************************************************************/
static int create_cmd_upiu(uint32_t opcode, enum dma_data_direction direction,
				struct cmd_param *param, uint8_t free_slot)
{
	uint32_t data_direction;
	uint8_t upiu_flags;
	struct dwc_ufs_utrd *utrd = NULL;
	struct dwc_ufs_ucd *ucd = NULL;
	uint32_t buf_size = PRDT_BUFFER_SIZE;

	get_local_dwc_host();

	if (opcode == UFS_OP_READ_10 || opcode == UFS_OP_WRITE_10 ||
	    opcode == UFS_OP_SYNCHRONIZE_CACHE_10) {
		if ((param->src % LOGICAL_BLK_SIZE) || (param->size % LOGICAL_BLK_SIZE)) {
			printf("!!!!!access ufs is not round with ufs blocksize,"
				"src is 0x%llx, size is 0x%x, blocksize is 0x%x\n",
				param->src, param->size, LOGICAL_BLK_SIZE);
			return UFS_SOFTWARE_ERROR;
		}
	}
	if (opcode == UFS_OP_SECURITY_PROTOCOL_IN || opcode == UFS_OP_SECURITY_PROTOCOL_OUT)
		buf_size = RPMB_FRAME_SIZE;

	/* Get the ucd of the free slot */
	ucd = dwc_host->ucdl_base_addr;
	ucd += free_slot;
	/* Get the xfer descriptor of the free slot */
	utrd = dwc_host->utrl_base_addr;
	utrd += free_slot;

	if (direction == DMA_FROM_DEVICE) {
		data_direction = UTP_DEVICE_TO_HOST;
		upiu_flags = UPIU_CMD_FLAGS_READ;
	} else if (direction == DMA_TO_DEVICE) {
		data_direction = UTP_HOST_TO_DEVICE;
		upiu_flags = UPIU_CMD_FLAGS_WRITE;
	} else {
		data_direction = UTP_NO_DATA_TRANSFER;
		upiu_flags = UPIU_CMD_FLAGS_NONE;
	}

	/* Update cmd_type, flags and response upiu length */
	utrd->ct_and_flags = (uint8_t)(data_direction | UTP_UFS_STORAGE_COMMAND);
	utrd->resp_upiu_length = to_littleendian16((uint16_t)
		(sizeof(struct dwc_ufs_resp_upiu) >> UFS_DWORD_SHIFT));
	utrd->prdt_length = to_littleendian16((uint16_t)((param->size & (buf_size - 1)) ?
		((param->size / buf_size) + 1) : (param->size / buf_size)));
	utrd->ocs = 0xf;

	create_cmd_part(opcode, upiu_flags, param, free_slot);
	create_prdt_part(param, buf_size, free_slot);

	/* occupy this slot */
	dwc_host->outstanding_xfer_reqs |= BIT(free_slot);

	return UFS_SUCCESS;
}

/****************************************************************
 * ufs_soft_init
 * Description: alloc memory for dwc_host
 *
 ****************************************************************/
static int ufs_soft_init(void)
{
	int ret;

	get_local_dwc_host();

	memset((void *)dwc_host, 0, sizeof(struct dwc_ufs_hba));

	/* Read host Controller Capabilities */
	dwc_ufshcd_read_caps(dwc_host);

	/* Allocate memory required to interface with host */
	ret = dwc_ufshcd_alloc_interface_memory(dwc_host);
	if (ret != UFS_OK) {
		printf("%s: allocating required memory error\n", __func__);
		return ret;
	}

	/* Configure the HC memory with required information and the LRB */
	dwc_ufshcd_configure_interface_memory(dwc_host);

	return UFS_OK;
}

static void ufs_config_init(void)
{
	int i;
	uint32_t value;

	get_local_dwc_host();

	/* Unipro DL_AFC0CreditThreshold */
	send_uic_command(DME_SET, 0x20440000, 0, 0x0);
	/* Unipro DL_TC0OutAckThreshold */
	send_uic_command(DME_SET, 0x20450000, 0, 0x0);
	/* Unipro DL_TC0TXFCThreshold */
	send_uic_command(DME_SET, 0x20400000, 0, 0x9);

#ifdef UFS_USE_HISI_MPHY_TC
#if defined(COMBO_PHY_V120)
	/* H8's workaround */
	/* PA_TActivate */
	send_uic_command(DME_SET, 0x15a80000, 0x0, 0xa);
	/* RX H8_TIMEOUT_VAL, Lane 0 */
	send_uic_command(DME_SET, 0x000a0004, 0x0, 0x1E);
	/* RX H8_TIMEOUT_VAL, Lane 1 */
	send_uic_command(DME_SET, 0x000a0005, 0x0, 0x1E);
#endif

	/* If the PLL is slow and needs more than 10 us
	* then this field can be used to specify the wait period unit. If
	* the value of this field */
	value = uic_cmd_read(DME_GET, 0xd0a00000); /* VS_DebugSaveConfigTime */
	value &= (uint32_t)(~(0x7 << 2));/* bit[4:2] = 0 */
	value |= 0x3 << 2; /* bit[4:2] = 3 */
	/* enlarge for default's 10us to 31250ns,
	     can make rateA->B change smoothly */
	send_uic_command(DME_SET, 0xd0a00000, 0x0, value);
#endif

	/* the ufs register will be reset, so set the ufs register always*/
	dwc_ufshcd_initialize_hba_desc_pointers(dwc_host);
	for (i = 0; i < UNIT_DESCS_COUNT; i++)
		dwc_host->lu_request_sense_sent[i] = 0;

	dwc_ufs_write_reg(UFS_UTRLRSR_OFF, UFS_UTP_RUN_BIT);
	dwc_ufs_write_reg(UFS_UTMRLRSR_OFF, UFS_UTP_RUN_BIT);
}

/***************************************************************
 * read_nop_rsp
 * Description: The function reads and validates the response
 *              received for NOP command
 *
 ***************************************************************/
static int read_nop_rsp(uint8_t free_slot)
{
	struct dwc_ufs_nop_resp_upiu *resp_upiu = NULL;
	struct dwc_ufs_utrd *utrd = NULL;

	get_local_dwc_host();

	resp_upiu = (struct dwc_ufs_nop_resp_upiu *)dwc_host->lrb[free_slot].resp_upiu;
	utrd = dwc_host->lrb[free_slot].utrd;

	if (utrd->ocs != UFS_SUCCESS) {
		printf("send nop out ocs err\n");
		ufs_reg_dump();
		return -((utrd->ocs & 0xf) + RET_UTRD_OCS_ERROR_OFF);
	}

	if ((resp_upiu->trans_type & 0x3F) != NOP_TRANS_TYPE) {
		printf("invalid nop in trans_type 0x%x\n", (resp_upiu->trans_type & 0x3F));
		ufs_reg_dump();
		return UFS_INVALID_NOP_IN;
	}

	if (resp_upiu->response != UFS_SUCCESS) {
		printf("nop in response error, resp = 0x%x\n", resp_upiu->response);
		return UFS_NOP_RESP_FAIL;
	}

	return UFS_SUCCESS;
}

/***************************************************************
 * wait_for_cmd_completion
 * Description: Sets the DoorBell Register and waits for the
 *              Doorbell to Clear. Returns Zero on Success or
 *		error number on Failure
 *
 ***************************************************************/
int wait_for_cmd_completion(uint32_t slot_mask)
{
	int retry = 5000; /* 5000ms timeout */

	get_local_dwc_host();

	flush_dcache_all();
	/* Set the doorbell for processing the request */
	dwc_ufs_write_reg(UFS_UTRLDBR_OFF, slot_mask);

	/* Wait for the DoorBell to clear */
	for (;;) {
		if ((dwc_ufs_read_reg(UFS_UTRLDBR_OFF) & slot_mask) == 0) {
			break;
		}
		if (--retry == 0) {
			printf("UTRL DoorBell Not Cleared and Timed Out, "
				"DoorBell is 0x%x, slot_mask is 0x%x\n",
				dwc_ufs_read_reg(UFS_UTRLDBR_OFF), slot_mask);
			ufs_reg_dump();

			dwc_ufs_write_reg(UFS_UTRLCLR_OFF, 0);
			dwc_host->outstanding_xfer_reqs = 0;

			return UFS_UTRD_DOORBELL_TIMEOUT;
		}
		ufs_waitms(1);
	}
	invalidate_dcache_all();
	return UFS_SUCCESS;
}

/***************************************************************
 * create_nop_out_upiu
 * Description: Fills the UPIU memory for NOP OUT command
 *
 ***************************************************************/
static void create_nop_out_upiu(uint8_t free_slot)
{
	struct dwc_ufs_nop_req_upiu *cmd_upiu_ptr = NULL;
	struct dwc_ufs_nop_resp_upiu *resp_upiu = NULL;
	int i;
	struct dwc_ufs_utrd *utrd = NULL;

	get_local_dwc_host();

	cmd_upiu_ptr = (struct dwc_ufs_nop_req_upiu *)dwc_host->lrb[free_slot].cmd_upiu;

	utrd = dwc_host->lrb[free_slot].utrd;

	utrd->ct_and_flags = (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	utrd->resp_upiu_length = to_littleendian16((uint16_t)
			(sizeof(struct dwc_ufs_nop_resp_upiu) >> UFS_DWORD_SHIFT));
	utrd->prdt_length = 0;
	utrd->ocs = 0xf;

	cmd_upiu_ptr->trans_type = 0x00;
	cmd_upiu_ptr->flags = 0x00;
	cmd_upiu_ptr->reserved_1 = 0x00;
	cmd_upiu_ptr->task_tag = free_slot;
	cmd_upiu_ptr->reserved_2 = 0x0;
	cmd_upiu_ptr->tot_ehs_len = 0x00;
	cmd_upiu_ptr->reserved_3 = 0x00;
	cmd_upiu_ptr->data_seg_len = 0x00;
	for (i = 0; i < 20; i++) /* reserved: 20 bytes */
		cmd_upiu_ptr->reserved_4[i] = 0x00;

	resp_upiu = (struct dwc_ufs_nop_resp_upiu *)dwc_host->lrb[free_slot].resp_upiu;
	memset((void *)resp_upiu, 0, sizeof(struct dwc_ufs_nop_resp_upiu));
}

static int send_nop_out_cmd(void)
{
	int ret;
	int i;
	uint8_t free_slot;

	get_local_dwc_host();
	for (i = 0; i < 5; i++) { /* retry 5 times */
		free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
		if (free_slot == BAD_SLOT)
			return UFS_ERR;

		create_nop_out_upiu(free_slot);
		ret = wait_for_cmd_completion(BIT(free_slot));
		if (ret == UFS_SUCCESS)
			ret = read_nop_rsp(free_slot);

		if (ret == UFS_SUCCESS)
			break;

		printf("nop out nop in fail, ret = %d, retry = %d\n", ret, i);
		ufs_waitms(10); /* delay 10ms */
	}

	return ret;
}

/***************************************************************
 * handle_query_response
 * Description: The functon does the following
 *              1. validates the query command's response received
 *              2. updates the ret argument with query data
 *              3. returns the status
 *
 ***************************************************************/
static int handle_query_response(uint8_t *ret, uint8_t free_slot)
{
	struct dwc_ufs_query_upiu *resp_upiu = NULL;

	get_local_dwc_host();

	resp_upiu = (struct dwc_ufs_query_upiu *)dwc_host->lrb[free_slot].resp_upiu;

	/* Update the return value */
	if (ret != NULL) {
		ret[0] = resp_upiu->tsf[11]; /* val 0: tsf 11 */
		ret[1] = resp_upiu->tsf[10]; /* val 1: tsf 10 */
		ret[2] = resp_upiu->tsf[9];  /* val 2: tsf 9 */
		ret[3] = resp_upiu->tsf[8];  /* val 3: tsf 8 */
	}

	if (resp_upiu->query_resp == UFS_SUCCESS)
		return UFS_SUCCESS;

	printf("Query Response error: 0x%x\n", resp_upiu->query_resp);
	return -(resp_upiu->query_resp);
}

/***************************************************************
 * create_query_upiu
 * Description: Populates the UPIU memory for all query Operations
 *
 ***************************************************************/
static void create_query_upiu(uint8_t query_func, struct query_param *param,
				const uint8_t *val, uint8_t free_slot)
{
	struct dwc_ufs_query_upiu *cmd_upiu_ptr = NULL;
	struct dwc_ufs_utrd *utrd = NULL;
	int i;

	get_local_dwc_host();
	cmd_upiu_ptr = (struct dwc_ufs_query_upiu *)dwc_host->lrb[free_slot].cmd_upiu;

	utrd = dwc_host->lrb[free_slot].utrd;

	/* UTRD Descriptor Programming for processing command */
	utrd->ct_and_flags = (uint8_t)
		(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	utrd->resp_upiu_length = to_littleendian16((uint16_t)
		(sizeof(struct dwc_ufs_query_upiu) >> UFS_DWORD_SHIFT));
	utrd->prdt_length = 0;

	/* Command Descriptor Programming */
	cmd_upiu_ptr->trans_type = 0x16;
	cmd_upiu_ptr->flags = UPIU_CMD_FLAGS_NONE;
	cmd_upiu_ptr->reserved_1 = 0x00;
	cmd_upiu_ptr->task_tag = free_slot;
	cmd_upiu_ptr->reserved_2 = 0x00;
	cmd_upiu_ptr->query_func = query_func;
	cmd_upiu_ptr->query_resp = 0x00;
	cmd_upiu_ptr->reserved_3 = 0x00;
	cmd_upiu_ptr->tot_ehs_len = 0x00;
	cmd_upiu_ptr->data_seg_len = 0x00;

	for (i = 0; i < 16; i++) /* clear 16 byte */
		cmd_upiu_ptr->tsf[i] = 0x0;
	cmd_upiu_ptr->tsf[0] = param->opcode;   /* 0: opcode */
	cmd_upiu_ptr->tsf[1] = param->idn;      /* 1: idn */
	cmd_upiu_ptr->tsf[2] = param->index;    /* 2: index */
	cmd_upiu_ptr->tsf[3] = param->selector; /* 3: selector */
	/* Value/Flag Updation */
	cmd_upiu_ptr->tsf[8] = val[3];   /* 8: val 3 */
	cmd_upiu_ptr->tsf[9] = val[2];   /* 9: val 2 */
	cmd_upiu_ptr->tsf[10] = val[1];  /* 10: val 1 */
	cmd_upiu_ptr->tsf[11] = val[0];  /* 11: val 0 */
	cmd_upiu_ptr->reserved_5 = 0x0;
}

/***************************************************************
 * send_scsi_cmd
 * Description: function creates UPIU for scsi commands sends it
 *              to the device by setting the DoorBell.
 *
 ****************************************************************/
static int send_scsi_cmd(uint32_t opcode, enum dma_data_direction direction,
				uint64_t buf_addr, uint64_t rel_addr, uint32_t size)
{
	int ret;
	uint8_t free_slot;
	struct cmd_param param = {buf_addr, rel_addr, size};

	get_local_dwc_host();
	if (lower_32_bits(buf_addr) % 0x4) {
		printf("fail! buf_addr:0x%llx is not round to D-Words\n", buf_addr);
		return UFS_SOFTWARE_ERROR;
	}
	if (size % 0x4) {
		printf("fail! size:0x%x is not round to D-Words\n", size);
		return UFS_SOFTWARE_ERROR;
	}
	if (size / PRDT_BUFFER_SIZE > DWC_UFSHCD_MAX_PRD_SIZE) {
		printf("fail! size:0x%x is bigger than PRDT alloc\n", size);
		return UFS_SOFTWARE_ERROR;
	}

	free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
	if (free_slot == BAD_SLOT)
		return UFS_ERR;

	ret = create_cmd_upiu(opcode, direction, &param, free_slot);
	if (ret != UFS_SUCCESS) {
		printf("create_cmd_upiu fail! ret %d\n", ret);
		return ret;
	}

	ret = wait_for_cmd_completion(BIT(free_slot));
	return ret;
}

static int handle_response_status(struct dwc_ufs_resp_upiu *resp_upiu)
{
	uint8_t status;
	int ret;

	status = resp_upiu->status;
	if (status == SAM_STAT_GOOD) {
		/* do nothing */
		ret = 0;
	} else if (status == SAM_STAT_CHECK_CONDITION) {
		/* 0x20 is added to sense key to return
		 * unique error code */
		ret = -(RET_SENSE_KEY_OFF +
			(resp_upiu->sense_data[2] & 0xf)); /* byte 2: sense key */
		/* because other slot to check, so not
		 * return here */
		printf("The sense key is 0x%x, ASC is 0x%x, ASCQ is 0x%x\n",
			((uint8_t *)resp_upiu)[SENSE_KEY_INDEX] & 0xf,
			((uint8_t *)resp_upiu)[SENSE_KEY_INDEX + 0xa],
			((uint8_t *)resp_upiu)[SENSE_KEY_INDEX + 0xb]);
	} else {
		switch (status) {
		case SAM_STAT_CONDITION_MET:
			ret = RESP_STAT_CONDITION_MET;
			break;
		case SAM_STAT_BUSY:
			ret = RESP_STAT_BUSY;
			break;
		case SAM_STAT_RESERVATION_CONFLICT:
			ret = RESP_STAT_RESERVATION_CONFLICT;
			break;
		case SAM_STAT_TASK_SET_FULL:
			ret = RESP_STAT_TASK_SET_FULL;
			break;
		case SAM_STAT_ACA_ACTIVE:
			ret = RESP_STAT_ACA_ACTIVE;
			break;
		case SAM_STAT_TASK_ABORTED:
			ret = RESP_STAT_TASK_ABORTED;
			break;
		default:
			ret = RESP_STAT_UNKNOWN;
		}
	}

	return ret;
}

/***************************************************************
 * handle_scsi_completion
 * Description: The functon validates the SCSI command's
 *              response received
 *
 ***************************************************************/
static int handle_scsi_completion(void)
{
	struct dwc_ufs_resp_upiu *resp_upiu = NULL;
	struct dwc_ufs_utrd *utrd = NULL;
	uint8_t slot_index;
	int i;
	int ret = 0;

	get_local_dwc_host();
	for (i = 0; i < dwc_host->nutrs; i++) {
		slot_index = (uint8_t)i;
		/* the outstanding is set on, so dump the response,
                   and then clear the bit */
		if (dwc_host->outstanding_xfer_reqs & BIT(slot_index)) {
			resp_upiu = dwc_host->lrb[slot_index].resp_upiu;
			utrd = dwc_host->lrb[slot_index].utrd;

			/* finish the requset here */
			dwc_host->outstanding_xfer_reqs ^= BIT(slot_index);

			if (utrd->ocs == UFS_SUCCESS) {
				ret = handle_response_status(resp_upiu);
			} else {
				ret = -((utrd->ocs & 0xf) + RET_UTRD_OCS_ERROR_OFF);
				ufs_reg_dump();
			}
		}
	}

	return ret;
}

static int do_scsi_cmd(uint32_t opcode, enum dma_data_direction direction,
				uint64_t buf_addr, uint64_t rel_addr, uint32_t size)
{
	int ret;

	ret = send_scsi_cmd(opcode, direction, buf_addr, rel_addr, size);
	if (ret != UFS_SUCCESS) {
		printf("send scsi cmd[0x%x] error: %d\n", opcode, ret);
		return ret;
	}

	ret = handle_scsi_completion();
	if (ret != UFS_SUCCESS) {
		printf("handle scsi cmd[0x%x] completion error: %d\n",
			  opcode, ret);
		return ret;
	}
	return ret;
}

/***************************************************************
 * create_desc_upiu
 * Description: The function does a simple memcpy of the req_upiu
 *              content passed to UPIU memory for Read/Write
 *              descriptor Operation
 *
 ***************************************************************/
static void create_desc_upiu(const void *req_upiu, uint8_t free_slot)
{
	unsigned int len;

	get_local_dwc_host();

	len = (unsigned int)(sizeof(struct dwc_ufs_query_upiu) +
		to_bigendian16(((struct dwc_ufs_query_upiu *)req_upiu)->data_seg_len));

	if (dwc_host->lrb[free_slot].cmd_upiu == req_upiu)
		return;
	memcpy(dwc_host->lrb[free_slot].cmd_upiu, req_upiu, len);
}

/***************************************************************
 * write_descriptor
 * Description: The functon populates the request upiu structure
 *		with upiu info passed in 1st argument
 *
 ***************************************************************/
int write_descriptor(const void *req_upiu)
{
	int ret;
	struct dwc_ufs_utrd *utrd = NULL;
	uint8_t free_slot;

	get_local_dwc_host();

	free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
	if (free_slot == BAD_SLOT)
		return UFS_ERR;
	utrd = dwc_host->lrb[free_slot].utrd;

	/* UTRD Descriptor Programming for processing command */
	utrd->ct_and_flags = (uint8_t)
		(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	utrd->resp_upiu_length = to_littleendian16((uint16_t)
		(sizeof(struct dwc_ufs_query_upiu) >> UFS_DWORD_SHIFT));
	utrd->prdt_length = 0;

	create_desc_upiu(req_upiu, free_slot);

	ret = wait_for_cmd_completion(BIT(free_slot));
	if (ret != UFS_SUCCESS) {
		return ret;
	}

	ret = handle_query_response(NULL, free_slot);

	return ret;
}

/***************************************************************
 * read_attribute
 * Description: The functon sends the query command to read an
 *              attribute and updates the ret_value with the
 *              content of the attribute
 *
 ***************************************************************/
int read_attribute(enum attr_id idn, uint8_t index, uint8_t selector, uint32_t *ret_value)
{
	int ret;
	uint8_t free_slot;
	struct query_param param = {READ_ATTR_OPCODE, idn, index, selector};

	get_local_dwc_host();
	free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
	if (free_slot == BAD_SLOT)
		return UFS_ERR;
	*ret_value = 0;

	create_query_upiu(STANDARD_RD_REQ, &param, (uint8_t *)ret_value, free_slot);
	ret = wait_for_cmd_completion(BIT(free_slot));
	if (ret != UFS_SUCCESS)
		return ret;

	ret = handle_query_response((uint8_t *)ret_value, free_slot);
	return ret;
}

/***************************************************************
 * write_attribute
 * Description: The functon sends the query command to write an
 *              attribute with the value passed as second argument
 *
 ***************************************************************/
int write_attribute(enum attr_id idn, uint8_t index, uint8_t selector, uint32_t *value)
{
	int ret;
	uint8_t free_slot;
	struct query_param param = {WRITE_ATTR_OPCODE, idn, index, selector};

	get_local_dwc_host();
	free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
	if (free_slot == BAD_SLOT)
		return UFS_ERR;

	create_query_upiu(STANDARD_WR_REQ, &param, (uint8_t *)value, free_slot);
	ret = wait_for_cmd_completion(BIT(free_slot));
	if (ret != UFS_SUCCESS) {
		return ret;
	}

	ret = handle_query_response((uint8_t *)value, free_slot);
	return ret;
}

static int update_lu_memory_type(struct partition_desc_table *pdt, int index,
				uint32_t *p_max_alloc_unit, uint32_t *numerator)
{
	uint16_t cap_adj_fac = 0;
	const uint16_t fac_div = 256;

	if ((BIT(pdt->partition_desc_ptr[index]->memory_type) &
			pdt->w_supported_memory_types) == 0) {
		printf("device not support memory type: %d\n",
			pdt->partition_desc_ptr[index]->memory_type);
		return -1;
	}

	switch (pdt->partition_desc_ptr[index]->memory_type) {
	case 0x0:
		cap_adj_fac = 1;
		p_max_alloc_unit = NULL;
		break;
	case 0x1:
		cap_adj_fac = pdt->w_system_code_cap_adj_fac / fac_div;
		p_max_alloc_unit = &(pdt->d_system_code_max_alloc_u);
		break;
	case 0x2:
		cap_adj_fac = pdt->w_non_persist_cap_adj_fac / fac_div;
		p_max_alloc_unit = &(pdt->d_non_persist_max_alloc_u);
		break;
	case 0x3:
		cap_adj_fac = pdt->w_enhanced1_cap_adj_fac / fac_div;
		p_max_alloc_unit = &(pdt->d_enhanced1_max_alloc_u);
		break;
	case 0x4:
		cap_adj_fac = pdt->w_enhanced2_cap_adj_fac / fac_div;
		p_max_alloc_unit = &(pdt->d_enhanced2_max_alloc_u);
		break;
	default:
		printf("unknown memory type\n");
		return -1;
	}
	if (pdt->partition_desc_ptr[index]->lu_capacity * cap_adj_fac >= 0x200000) {
		printf("input lu_capacity set too large\n");
		return -1;
	}
	*numerator = (pdt->partition_desc_ptr[index]->lu_capacity) * 0x800 * cap_adj_fac;
	return 0;
}

/***************************************************************
 * update_lu_capacity_info
 * Updates the dNumAllocUnits information for the Logic Unit
 * indexed by index. In addition, this also tracks the number
 * of LUs that will be provisioned in the device.
 *
 ***************************************************************/
static int update_lu_capacity_info(struct partition_desc_table *pdt)
{
	uint32_t numerator;
	const uint32_t denominator = (pdt->b_allocation_unit_size) * (pdt->d_segment_size);
	uint32_t alloced_units = 0;
	uint32_t *p_max_alloc_unit = NULL;
	int max_cap_lu = -1;
	int i;

	/* Initialize the LUN tracker to zero */
	pdt->b_number_lu = 0;

	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		if (pdt->partition_desc_ptr[i] == NULL)
			continue;
		if (pdt->partition_desc_ptr[i]->lu_capacity == UFS_MAX_LU_CAP) {
			if (max_cap_lu != -1) {
				printf("more than one lu set UFS_MAX_LU_CAP\n");
				return -1;
			}
			max_cap_lu = i;
			continue;
		}
		if (update_lu_memory_type(pdt, i, p_max_alloc_unit, &numerator))
			return -1;
		pdt->partition_desc_ptr[i]->num_alloc_units =
			(numerator + denominator - 1) / denominator;
		ufs_pr_dbg("lun %d-NumAllocUnits: 0x%x\n", i,
			pdt->partition_desc_ptr[i]->num_alloc_units);
		if (p_max_alloc_unit != NULL) {
			if (pdt->partition_desc_ptr[i]->num_alloc_units > *p_max_alloc_unit) {
				printf("alloc units more than this type 0x%x\n",
					pdt->partition_desc_ptr[i]->memory_type);
				return -1;
			}
			*p_max_alloc_unit -= pdt->partition_desc_ptr[i]->num_alloc_units;
		}
		alloced_units += pdt->partition_desc_ptr[i]->num_alloc_units;
		pdt->b_number_lu += 1;
	}

	if (max_cap_lu != -1) {
		numerator = lower_32_bits(pdt->q_total_raw_device_capacity);
		pdt->partition_desc_ptr[max_cap_lu]->num_alloc_units =
			numerator / denominator - alloced_units;
		pdt->b_number_lu += 1;
	}

	return 0;
}

static int compair_unit_part(struct partition_desc_table *pdt)
{
	struct partition_desc *desc = NULL;
	struct ufs_unit_desc_configuration_param unit;
	int i, ret;

	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		desc = pdt->partition_desc_ptr[i];
		unit = g_ufs_desc.conf_desc.unit_desc_conf_param[i];
		ret = 0x10 * (i + 1);
		if (desc == NULL) {
			/* the Lun should be disabled */
			if (unit.b_lu_enable != 0x0)
				return ret;
			continue;
		}
		if (unit.b_lu_enable != 0x1)
			return ret;
		if (unit.b_boot_lun_id != desc->boot_lun_id)
			return ret + 0x1;
		if (unit.b_lu_write_protect != desc->write_protect)
			return ret + 0x2;
		if (unit.b_memory_type != desc->memory_type)
			return ret + 0x3;
		if (to_bigendian32(unit.d_num_alloc_units) != desc->num_alloc_units)
			return ret + 0x4;
		if (unit.b_data_reliability != desc->data_reliability)
			return ret + 0x8;
		if (unit.b_logical_block_size != desc->block_size)
			return ret + 0x9;
		if (unit.b_provisioning_type != desc->prov_type)
			return ret + 0xA;
		if (to_bigendian16(unit.w_context_capabilities) != desc->context_capabilities)
			return ret + 0xB;
	}
	return 0;
}

static int compair_conf_desp(struct partition_desc_table *pdt)
{
	struct ufs_dev_desc_configuration_param dev;

	dev = g_ufs_desc.conf_desc.dev_desc_conf_param;

	if (pdt->p_conf_header->b_boot_enable != dev.b_boot_enable)
		return 0x3;
	if (pdt->p_conf_header->b_descr_access_en != dev.b_descr_access_en)
		return 0x4;
	if (pdt->p_conf_header->b_init_power_mode != dev.b_init_power_mode)
		return 0x5;
	if (pdt->p_conf_header->b_high_priority_lun != dev.b_high_priority_lun)
		return 0x6;
	if (pdt->p_conf_header->b_secure_removal_type != dev.b_secure_removal_type)
		return 0x7;
	if (pdt->p_conf_header->b_init_active_icc_level != dev.b_init_active_icc_level)
		return 0x8;
	if (pdt->p_conf_header->w_periodic_rtc_update != dev.w_periodic_rtc_update)
		return 0x9;

	return compair_unit_part(pdt);
}

/***************************************************************
 * ufs_device_init
 * Description: The function does the following
 *            1. Sends the NOP Out command continuosly till it passes
 *            2. Sets the Device init Flag for UFS Device initialization
 *
 ****************************************************************/
static int ufs_device_init(void)
{
	int ret;
	uint8_t flags_ret_val = 1;
	int retry = 3000; /* retry 3000 times */

	/* Send continuos NOP OUT Command unless Response is Valid */
	ret = send_nop_out_cmd();
	if (ret != UFS_SUCCESS) {
		printf("nop out fail\n");
		return ret;
	}

	/* Set the Device Init Flag */
	ret = ufs_set_flag(FDEVICE_INIT, &flags_ret_val);
	if (ret) {
		printf("set device init flag fail\n");
		return ret;
	}

	do {
		ret = ufs_read_flag(FDEVICE_INIT, &flags_ret_val);
		if ((ret == UFS_SUCCESS) && (flags_ret_val == 0)) {
			return UFS_SUCCESS;
		}
		ufs_waitms(1);
	} while (--retry > 0);

	if (flags_ret_val != 0)
		ret = UFS_FDEVICE_INIT_FAIL;

	printf("read device init fail\n");

	return ret;
}

static int ufs_host_init(void)
{
	int ret;

	ret = ufs_soft_init();
	if (ret) {
		printf("ufs_soft_init fail\n");
		return ret;
	}

	ret = ufs_hc_enable();
	if (ret) {
		printf("HC enable fail\n");
		return ret;
	}
	ufs_hc_init();

	ret = ufs_link_startup();
	if (ret) {
		printf("link start up fail\n");
		return ret;
	}

	ufs_config_init();
	printf("\nUFS Linkup!\n");

	return UFS_SUCCESS;
}

/*
 * some device need a full reset after lu config
 * And this funciton does not switch to hs mode
 * after lu config and ufs_reset init would continue and switch to hs mode
 */
static int ufs_reset(void)
{
	int ret;

	get_local_dwc_host();

	ufs_hardware_init();

	ret = ufs_host_init();
	if (ret) {
		printf("UfsHostInit ret:%d\n", ret);
		return ret;
	}

	/* device reset will cause a new UAC */
	memset(dwc_host->lu_request_sense_sent, 0, UNIT_DESCS_COUNT);

	ret = ufs_device_init();
	if (ret)
		printf("UfsDeviceInit ret:%d\n", ret);

	return ret;
}

static void update_geometry_info(struct partition_desc_table *pdt)
{
	struct ufs_geometry_descriptor geo;

	geo = g_ufs_desc.geo_desc;

	pdt->q_total_raw_device_capacity = cpu_to_be64(geo.q_total_raw_device_capacity);
	pdt->d_segment_size = to_bigendian32(geo.d_segment_size);
	pdt->b_allocation_unit_size = geo.b_allocation_unit_size;
	pdt->b_data_ordering = geo.b_data_ordering;
	pdt->b_max_contex_id_number = geo.b_max_contex_id_number;
	pdt->w_supported_memory_types = to_bigendian16(geo.w_supported_memory_types);
	pdt->d_system_code_max_alloc_u = to_bigendian32(geo.d_system_code_max_alloc_u);
	pdt->w_system_code_cap_adj_fac = to_bigendian16(geo.w_system_code_cap_adj_fac);
	pdt->d_non_persist_max_alloc_u = to_bigendian32(geo.d_non_persist_max_alloc_u);
	pdt->w_non_persist_cap_adj_fac = to_bigendian16(geo.w_non_persist_cap_adj_fac);
	pdt->d_enhanced1_max_alloc_u = to_bigendian32(geo.d_enhanced1_max_alloc_u);
	pdt->w_enhanced1_cap_adj_fac = to_bigendian16(geo.w_enhanced1_cap_adj_fac);
	pdt->d_enhanced2_max_alloc_u = to_bigendian32(geo.d_enhanced2_max_alloc_u);
	pdt->w_enhanced2_cap_adj_fac = to_bigendian16(geo.w_enhanced2_cap_adj_fac);
}

static int ufs_get_device_info(void)
{
	int ret;

	get_local_dwc_host();

	memset((void *)&g_ufs_desc, 0, (unsigned int)sizeof(struct ufs_descriptor));

	ret = ufs_read_descriptor((void *)(&g_ufs_desc.dev_desc),
			DEVICE_DESC, 0, DEVICE_DESC_LENGTH);
	if (ret != UFS_OK) {
		printf("read device descriptor fail\n");
		return UFS_ERR;
	}

	ret = ufs_read_descriptor((void *)(&g_ufs_desc.geo_desc),
			GEOMETRY_DESC, 0, GEOMETRY_DESC_LENGTH);
	if (ret != UFS_OK) {
		printf("read geometry descriptor fail\n");
		return ret;
	}

	ret = ufs_read_string_descriptor();
	if (ret != UFS_OK) {
		printf("read string descriptor fail\n");
		return UFS_ERR;
	}

	/* configuration unit descriptor offset/length */
	dwc_host->unit_offset = g_ufs_desc.dev_desc.b_ud_0base_offset;
	dwc_host->unit_length = g_ufs_desc.dev_desc.b_ud_config_plength;

	/* device specification version */
	dwc_host->dev_spec_version =
		to_bigendian16(g_ufs_desc.dev_desc.w_spec_version);
	dwc_host->manufacturer_id =
		to_bigendian16(g_ufs_desc.dev_desc.w_manufacturer_id);
	dwc_host->manufacturer_date =
		to_bigendian16(g_ufs_desc.dev_desc.w_manufacture_date);

	printf("    MID:      0x%x\n", dwc_host->manufacturer_id);
	printf("    Version:  0x%x\n", dwc_host->dev_spec_version);
	printf("    Device:   %s\n", g_ufs_desc.str_desc.product_name);
	printf("    Size:     0x%llx\n", cpu_to_be64(g_ufs_desc.geo_desc.q_total_raw_device_capacity));
	printf("    Block:    %d Bytes\n", LOGICAL_BLK_SIZE);

	return UFS_OK;
}

static int ufs_device_configuration(struct partition_desc_table *pdt,
				struct desc_params *params,
				struct dwc_ufs_query_upiu *resp_upiu)
{
	int ret;
	uint32_t value;

	ret = read_attribute(B_CONFIG_DESC_LOCK, 0, 0, &value);
	if (ret != UFS_SUCCESS) {
		printf("read bConfigDescrLock fail. ret = %d\n", ret);
	} else {
		printf("bConfigDescrLock = 0x%x\n", value);
		if (value == 1) {
			printf("write config desc fail: descriptor locked\n");
			return -1;
		}
	}

	/* response of configuration descriptor sent as request UPIU */
	params->req_upiu = resp_upiu;
	params->conf_head = pdt->p_conf_header;
	params->part_desc = pdt->partition_desc_ptr;
	params->opcode = WRITE_DESC_OPCODE;
	params->desc_idn = CONFIGURATION_DESC;
	params->desc_index = 0;
	params->length = CONFIGURATION_DESC_LENGTH;
	modify_desc_upiu(params);

	ret = write_descriptor(params->req_upiu);
	if (ret != UFS_SUCCESS) {
		printf("write configuration fail. ret = %d\n", ret);
		return ret;
	}

	ret = ufs_reset();
	if (ret) {
		printf("ufs_reset fail. ret = %d\n", ret);
		return ret;
	}

	return 0;
}

/***************************************************************
 * ufs_create_partition_inventory
 * Description: The Function does the following actions
 *
 * 1. Reads UNIT desc's and stores the qphymemrescnt of each lun
 * 2. Reads the Device Descriptor to know the Configureable Unit
 *    desc zero's Offset and length of all unit descriptors.
 * 3. Validates the qmemrescnt with the configuration desc contents
 * 4. Reads and edits the content of configuration desc as per the
 *    input arguments
 *
 ***************************************************************/
static int ufs_create_partition_inventory(uint8_t partition_mask, struct partition_desc_table *pdt)
{
	int ret;
	struct desc_params params;
	struct dwc_ufs_query_upiu *req_upiu = NULL;
	void *resp_upiu = NULL;
	uint8_t i;

	get_local_dwc_host();
	/* use slot 0 default */
	resp_upiu = dwc_host->lrb[0].resp_upiu;
	req_upiu = (struct dwc_ufs_query_upiu *)(dwc_host->lrb[0].cmd_upiu);

	/* update the geometry information */
	update_geometry_info(pdt);

	/* Validate the Input Arguments */
	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		if ((partition_mask & (BIT(i))) == 0)
			pdt->partition_desc_ptr[i] = NULL;
	}

	update_lu_capacity_info(pdt);

	/* read configuration descriptor */
	params.req_upiu = req_upiu;
	params.part_desc = NULL;
	params.opcode = READ_DESC_OPCODE;
	params.desc_idn = CONFIGURATION_DESC;
	params.desc_index = 0;
	params.length = CONFIGURATION_DESC_LENGTH;
	modify_desc_upiu(&params);

	ret = read_descriptor(req_upiu, &resp_upiu);
	if (ret != UFS_SUCCESS) {
		printf("read configuration fail. ret = %d\n", ret);
		return ret;
	}
	memcpy(&g_ufs_desc.conf_desc, (void *)((u8 *)resp_upiu + QUERY_RESPONSE_HEAD_OFFSET), CONFIGURATION_DESC_LENGTH);

	ret = compair_conf_desp(pdt);
	if (!ret)
		return 0;

	printf("compair conf desp fail. ret=%d\n", ret);
	printf("UFS enter device configuration\n");

	ret = ufs_device_configuration(pdt, &params, resp_upiu);
	if (ret) {
		printf("ufs device configuration fail. ret = %d\n", ret);
		return ret;
	}

	return 0;
}

int ufs_set_bootlun(uint8_t lun)
{
	uint32_t value;
	int ret;

	ret = read_attribute(B_BOOT_LUNEN, 0, 0, &value);
	if (ret != UFS_SUCCESS) {
		printf("read bBootLunEn fail. ret = %d\n", ret);
		return ret;
	}

	if ((lun + 1) == value) {
		printf("Same UFS Lu%d Boot W-Lun\n", (value - 1));
		return 0;
	}

	/* set default boot from Boot LU A */
	value = lun + 1;
	ret = write_attribute(B_BOOT_LUNEN, 0, 0, &value);
	if (ret) {
		printf("write bBootLunEn attribute fail. ret = %d\n", ret);
		return ret;
	}
	printf("new UFS Lu%d Boot W-Lun\n", (value - 1));
	return ret;
}

static int set_boot_lu_enable(void)
{
	uint32_t value = 0;
	uint32_t target_value = DEFAULT_BOOT_LUN;
	int ret;

	ret = read_attribute(B_BOOT_LUNEN, 0, 0, &value);
	if (ret != UFS_SUCCESS) {
		printf("read bBootLunEn fail. ret = %d\n", ret);
		return ret;
	}

	if (value != 0)
		printf("UFS get boot W-LU-%c\n",
			(value == WELL_BOOT_LU_A) ? 'A' : 'B');

	if (value == target_value)
		return 0;

	/* set default boot from Boot LU A */
	value = target_value;
	ret = write_attribute(B_BOOT_LUNEN, 0, 0, &value);
	if (ret) {
		printf("write bBootLunEn attribute fail. ret = %d\n", ret);
		return ret;
	}

	printf("UFS set boot W-LU(%c)\n", (value == WELL_BOOT_LU_A) ? 'A' : 'B');
	return ret;
}

static void ufs_lu_configuration(struct partition_desc_table *pdt)
{
	int i;

	get_local_dwc_host();

	/* configuration header */
	pdt->p_conf_header->b_boot_enable = 0x1;
	pdt->p_conf_header->b_descr_access_en = 0x0;
	pdt->p_conf_header->b_init_power_mode = 0x1;
	pdt->p_conf_header->b_high_priority_lun = 0x7F;
	pdt->p_conf_header->b_secure_removal_type = 0x0;
	pdt->p_conf_header->b_init_active_icc_level = 0x0;
	pdt->p_conf_header->w_periodic_rtc_update = 0x0;

	/* lu 0: boot lu A */
	pdt->partition_desc_ptr[0]->boot_lun_id = WELL_BOOT_LU_A; /* lu 0, boot a */
	if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_TOSHIBA)
		pdt->partition_desc_ptr[0]->memory_type = 0x4; /* lu 0, Enhanced Memory */
	else
		pdt->partition_desc_ptr[0]->memory_type = 0x3; /* lu 0, Enhanced Memory */
	pdt->partition_desc_ptr[0]->lu_capacity = 4; /* lu 0, 4MB */

	/* lu 1: boot lu B */
	pdt->partition_desc_ptr[1]->boot_lun_id = WELL_BOOT_LU_B; /* lu 1, boot b */
	if (dwc_host->manufacturer_id == UFS_MANUFACTURER_ID_TOSHIBA)
		pdt->partition_desc_ptr[0]->memory_type = 0x4; /* lu 0, Enhanced Memory */
	else
		pdt->partition_desc_ptr[0]->memory_type = 0x3; /* lu 0, Enhanced Memory */
	pdt->partition_desc_ptr[1]->lu_capacity = 4; /* lu 1, 4MB */

	/* lu 2: data lu */
	pdt->partition_desc_ptr[2]->boot_lun_id = 0x0; /* lu 2 */
	pdt->partition_desc_ptr[2]->memory_type = 0x3; /* lu 2, Enhanced Memory */
	pdt->partition_desc_ptr[2]->lu_capacity = 8; /* lu 2, 8MB */

	/* lu 3: data lu */
	pdt->partition_desc_ptr[3]->boot_lun_id = 0x0; /* lu 3 */
	pdt->partition_desc_ptr[3]->memory_type = 0x0; /* lu 3, Normal Memory */
	pdt->partition_desc_ptr[3]->lu_capacity = UFS_MAX_LU_CAP; /* lu 3, max capacity */

	for (i = 0; i <= 3; i++) { /* lu 0 - 3 */
		pdt->partition_desc_ptr[i]->write_protect = 0x0;
		pdt->partition_desc_ptr[i]->data_reliability = 0x1;
		pdt->partition_desc_ptr[i]->block_size = 0x0c;
		pdt->partition_desc_ptr[i]->prov_type = 0x2;
		pdt->partition_desc_ptr[i]->context_capabilities = 0x0;
	}
}

static int ufs_lu_init(void)
{
	struct partition_desc_table pdt = {0};
	struct partition_desc partition_desc_ptr[UNIT_DESCS_COUNT] = {{0}};
	struct configuration_header config_header = {0};
	unsigned int bootlun = 0;
	int i, ret;

	get_local_dwc_host();

	pdt.p_conf_header = &config_header;
	for (i = 0; i < UNIT_DESCS_COUNT; i++)
		pdt.partition_desc_ptr[i] = &partition_desc_ptr[i];

	ufs_lu_configuration(&pdt);

	ret = ufs_create_partition_inventory(0xf, &pdt);
	if (ret) {
		goto out;
	}

	ret = set_boot_lu_enable();
	if (ret) {
		goto out;
	}

	ret = read_attribute(B_BOOT_LUNEN, 0, 0, &bootlun);
	if (ret != UFS_SUCCESS) {
		printf("read bBootLunEn fail. ret = %d\n", ret);
		return ret;
	}

	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		if (pdt.partition_desc_ptr[i] &&
		    pdt.partition_desc_ptr[i]->boot_lun_id == bootlun) {
			printf("UFS config LU-%d to W-LU-%c\n", i,
				(bootlun == WELL_BOOT_LU_A) ? 'A' : 'B');
			dwc_host->active_bootlun = i;
			break;
		}
	}
out:
	return ret;
}

static int ufs_set_ref_clk(void)
{
	uint32_t value;
	int ret;
	uint32_t target_ref_clk;

	target_ref_clk = 0; /* 19.2MHz */

	ret = read_attribute(B_REFCLK_FREQ, 0, 0, &value);
	if (ret != UFS_SUCCESS) {
		printf("read bRefClkFreq fail. ret = %d\n", ret);
		return ret;
	}

	if (target_ref_clk == value)
		return 0;

	/* set default boot from Boot LU A */
	ret = write_attribute(B_REFCLK_FREQ, 0, 0, &target_ref_clk);
	if (ret) {
		printf("write bRefClkFreq attribute fail. ret = %d\n", ret);
		return ret;
	}

	ret = read_attribute(B_REFCLK_FREQ, 0, 0, &value);
	if (ret != UFS_SUCCESS) {
		printf("read bRefClkFreq fail. ret = %d\n", ret);
		return ret;
	}

	if (target_ref_clk == value)
		return UFS_OK;

	return UFS_ERR;
}

int ufs_read_capacity(uint32_t *lba)
{
	uint32_t *data = NULL;
	int ret;

	get_local_dwc_host();

	data = (uint32_t *)dwc_host->wr_buf;

	ret = do_scsi_cmd(UFS_OP_READ_CAPACITY_10, DMA_FROM_DEVICE,
			(uint64_t)(uintptr_t)data, 0, CAPACITY_DATA_LENGTH);
	if (ret != UFS_SUCCESS) {
		printf("send READ_CAPACITY_10 error: %d\n", ret);
		return ret;
	}

	*lba = to_bigendian32(*data) + 1;
	return ret;
}

static int ufs_request_sense(void)
{
	uint8_t *sense_data = NULL;
	int ret;

	get_local_dwc_host();

	sense_data = (uint8_t *)dwc_host->wr_buf;

	ret = do_scsi_cmd(UFS_OP_REQUEST_SENSE, DMA_FROM_DEVICE,
			(uint64_t)(uintptr_t)sense_data, 0, SENSE_DATA_LENGTH);

	return ret;
}

/****************************************************************
 * ufs_set_active_lun
 * Description: Sets the Lun Number for further Transactions
 *
 ***************************************************************/
int ufs_set_active_lun(uint8_t lun)
{
	int ret;

	get_local_dwc_host();

	dwc_host->active_lun = lun;
	if (lun >= UNIT_DESCS_COUNT) {
		printf("well known lun: 0x%x\n", lun);

		if (g_wlun == lun)
			return UFS_SUCCESS;

		/* issue REQUEST SENSE command once for lu before accessing it */
		ret = ufs_request_sense();
		if (ret != 0) {
			printf("send UFS_OP_REQUEST_SENSE error: %d\n", ret);
			return ret;
		}
		printf("send UFS_OP_REQUEST_SENSE success: %d\n", ret);
		g_wlun = lun;
		return UFS_SUCCESS;
	}

	printf("UFS set active LU-%d\n", lun);
	if (dwc_host->lu_request_sense_sent[lun])
		return UFS_SUCCESS;

	/* issue REQUEST SENSE command once for lu before accessing it */
	ret = ufs_request_sense();
	if (ret != 0) {
		printf("send UFS_OP_REQUEST_SENSE error: %d\n", ret);
		return ret;
	}

	dwc_host->lu_request_sense_sent[lun] = 1;
	return ret;
}

/***************************************************************
 * ufs_sync_storage
 * Description: Synchronizes the content of the cache to the media.
 *
 ****************************************************************/
static int ufs_sync_storage(void)
{
	int ret;

	/* Send Synchronize Cache 10 Command and handle its completion */
	ret = do_scsi_cmd(UFS_OP_SYNCHRONIZE_CACHE_10, 0, 0, 0, 0);
	if (ret != UFS_SUCCESS) {
		printf("send SYNCHRONIZE_CACHE_10 error: %d\n", ret);
		return ret;
	}

	return ret;
}

/***************************************************************
 * ufs_write_storage
 * Description: Writes the content of the source Address to
 *              destination offset of the active lun.
 *              The APi assumes the data buffes if unaligned have
 *              valid data above the start address
 *
 ****************************************************************/
int ufs_write_storage(uint64_t src_addr, uint64_t dest_offset, uint32_t size)
{
	int ret;
	uint32_t len;
	uint64_t src_addr_tmp = src_addr;
	uint32_t size_tmp = size;
	uint32_t maxsize = PRDT_BUFFER_SIZE * DWC_UFSHCD_MAX_PRD_SIZE;

	while (size_tmp) {
		if (size_tmp < maxsize)
			len = size_tmp;
		else
			len = maxsize;

		/* Send Write 10 Command and handle its completion */
		ret = do_scsi_cmd(UFS_OP_WRITE_10, DMA_TO_DEVICE,
				src_addr_tmp, dest_offset, len);
		if (ret != UFS_SUCCESS) {
			printf("send WRITE_10 error: %d\n", ret);
			return ret;
		}
		size_tmp -= len;
		src_addr_tmp += len;
		dest_offset += len;
	}

	ret = ufs_sync_storage();
	return ret;
}

/********************************************************************
 * ufs_read_storage
 * Description: Reads the content of the source offset of active lun
 *              and copies the content to dest_addr.
 *              The API assumes there is enough memory allocated and
 *              available above and below start address for unaligned
 *              and multi block access
 *
 ********************************************************************/
int ufs_read_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size)
{
	int ret = -1;
	uint32_t len;
	uint64_t dest_addr_tmp = dest_addr;
	uint32_t size_tmp = size;
	uint32_t maxsize = (PRDT_BUFFER_SIZE * DWC_UFSHCD_MAX_PRD_SIZE);

	while (size_tmp) {
		if (size_tmp < maxsize)
			len = size_tmp;
		else
			len = maxsize;

		/* Send Read 10 Command and handle its completion */
		ret = do_scsi_cmd(UFS_OP_READ_10, DMA_FROM_DEVICE,
				dest_addr_tmp, src_offset, len);
		if (ret != UFS_SUCCESS) {
			printf("send READ_10 error: %d\n", ret);
			return ret;
		}
		size_tmp -= len;
		dest_addr_tmp += len;
		src_offset += len;
	}

	return ret;
}

int ufs_write_boot_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size)
{
	int ret;
	int prelun;

	get_local_dwc_host();

	prelun = dwc_host->active_lun;
	ret = ufs_set_active_lun(dwc_host->active_bootlun);
	if (ret != 0) {
		return ret;
	}

	ret = ufs_write_storage(dest_addr, src_offset, size);
	if (ret != 0) {
		return ret;
	}

	ret = ufs_set_active_lun(prelun);

	return ret;
}

int ufs_read_boot_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size)
{
	int ret;
	int prelun;

	get_local_dwc_host();

	prelun = dwc_host->active_lun;
	ret = ufs_set_active_lun(dwc_host->active_bootlun);
	if (ret != 0) {
		return ret;
	}

	ret = ufs_read_storage(dest_addr, src_offset, size);
	if (ret != 0) {
		return ret;
	}

	ret = ufs_set_active_lun(prelun);

	return ret;
}

int ufs_hibernate_enter(void)
{
	unsigned int value;
	uint32_t retry = 500; /* wait 500ms to let device finish the device hibernate exit */

	/* 1. BUSTHRTL bit12 clear to 0 */
	value = dwc_ufs_read_reg(UFS_BUSTHRTL_OFF);
	if (value & CGE) {
		value &= (~CGE);
		dwc_ufs_write_reg(UFS_BUSTHRTL_OFF, value);
	}

	/* 2. enter hibernate */
	send_uic_command(DME_HIBERNATE_ENTER, 0, 0, 0);

	/* 3. detect enter success or not */
	while (retry--) {
		if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UHES_BIT)
			break;
		ufs_waitms(1);
	}
	/* 3.1 if fail */
	if (retry == 0xFFFFFFFF) {
		printf("ufs_hibernate_enter fail, UHES wait 500ms timeout\n");
		return UFS_ERR;
	}
	/* 3.2 if success */
	printf("ufs_hibernate_enter success.\n");
	return UFS_OK;
}

int ufs_hibernate_exit(void)
{
	unsigned int value;
	uint32_t retry = 500; /* wait 500ms to let device finish the device hibernate exit */

	/* 1. BUSTHRTL bit12 clear to 0 */
	value = dwc_ufs_read_reg(UFS_BUSTHRTL_OFF);
	if (value & CGE) {
		value &= (~CGE);
		dwc_ufs_write_reg(UFS_BUSTHRTL_OFF, value);
	}

	/* 2. exit hibernate */
	send_uic_command(DME_HIBERNATE_EXIT, 0, 0, 0);

	/* 3. detect exit success or not */
	while (retry--) {
		if (dwc_ufs_read_reg(UFS_IS_OFF) & UFS_IS_UHXS_BIT)
			break;
		ufs_waitms(1);
	}
	/* 3.1 if fail, dump reg */
	if (retry == 0xFFFFFFFF) {
		printf("ufs_hibernate_exit fail, UHXS wait 500ms timeout\n");
		return UFS_ERR;
	}
	/* 3.2 if success */
	printf("ufs_hibernate_exit success.\n");
	return UFS_OK;
}

/***************************************************************
 * do_flag_operation
 * Description: The function can be used for any operation on flags
 * 1. fills the query upiu memory content
 * 2. Handles the response of query command sent
 * 3. updates the flag return value
 *
 ***************************************************************/
static int do_flag_operation(int opcode, int query_func, enum flags_id idn, uint8_t *flags_ret)
{
	int ret;
	uint8_t val[4] = {0}; /* 4 byte value */
	uint8_t free_slot;
	struct query_param param = {(uint8_t)opcode, (uint8_t)idn, 0, 0};

	get_local_dwc_host();

	free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
	if (free_slot == BAD_SLOT)
		return UFS_ERR;

	create_query_upiu((uint8_t)query_func, &param, val, free_slot);

	ret = wait_for_cmd_completion(BIT(free_slot));
	if (ret != UFS_SUCCESS) {
		return ret;
	}

	ret = handle_query_response(val, free_slot);
	*flags_ret = val[0];

	return ret;
}

/***************************************************************
 * ufs_set_flag
 * Description: The function invokes do_flag_operation for set
 *              flag operation
 *
 ***************************************************************/
int ufs_set_flag(enum flags_id idn, uint8_t *flags_ret)
{
	int ret;

	ret = do_flag_operation(SET_FLAG_OPCODE, STANDARD_WR_REQ, idn, flags_ret);

	return ret;
}

static void modify_write_conf_desc(const struct desc_params *params)
{
	uint8_t *data = NULL;
	struct partition_desc **desc = params->part_desc;
	struct dwc_ufs_query_upiu *upiu_ptr = (struct dwc_ufs_query_upiu *)params->req_upiu;
	uint32_t i, offset;

	get_local_dwc_host();

	data = (uint8_t *)(upiu_ptr + 1);
	/* boot enable */
	data[0x3] = params->conf_head->b_boot_enable;
	data[0x4] = params->conf_head->b_descr_access_en;
	data[0x5] = params->conf_head->b_init_power_mode;
	data[0x6] = params->conf_head->b_high_priority_lun;
	data[0x7] = params->conf_head->b_secure_removal_type;
	data[0x8] = params->conf_head->b_init_active_icc_level;
	data[0x9] = (uint8_t)(((params->conf_head->w_periodic_rtc_update) >> 8) & 0xff); /* shift 8 */
	data[0xA] = (uint8_t)((params->conf_head->w_periodic_rtc_update) & 0xff);
	for (i = 0; i < UNIT_DESCS_COUNT; i++) {
		offset = dwc_host->unit_length * i + dwc_host->unit_offset;
		if (desc[i] == NULL) {
			/* Disable the Lun */
			data[offset] = 0x0;
			continue;
		}
		data[offset] = 0x1;
		data[offset + 0x1] = desc[i]->boot_lun_id;
		data[offset + 0x2] = desc[i]->write_protect;
		data[offset + 0x3] = desc[i]->memory_type;
		data[offset + 0x4] = (uint8_t)(((desc[i]->num_alloc_units) >> 24) & 0xff); /* shift 24 */
		data[offset + 0x5] = (uint8_t)(((desc[i]->num_alloc_units) >> 16) & 0xff); /* shift 16 */
		data[offset + 0x6] = (uint8_t)(((desc[i]->num_alloc_units) >> 8) & 0xff); /* shift 8 */
		data[offset + 0x7] = (uint8_t)((desc[i]->num_alloc_units) & 0xff);
		data[offset + 0x8] = desc[i]->data_reliability;
		data[offset + 0x9] = desc[i]->block_size;
		data[offset + 0xa] = desc[i]->prov_type;
		data[offset + 0xb] = (uint8_t)(((desc[i]->context_capabilities) >> 8) & 0xff); /* shift 8 */
		data[offset + 0xc] = (uint8_t)((desc[i]->context_capabilities) & 0xff);
	}
}

/***************************************************************
 * modify_desc_upiu
 * Description: The function performs the following
 *            1.Fills the request upiu for read/write desc operation
 *            2.Updates the Data Memory below the request UPIU
 *
 ***************************************************************/
void modify_desc_upiu(const struct desc_params *params)
{
	uint32_t i;
	struct dwc_ufs_query_upiu *upiu_ptr = NULL;

	/* Command Descriptor Programming */
	upiu_ptr = (struct dwc_ufs_query_upiu *)params->req_upiu;
	upiu_ptr->trans_type = 0x16;
	upiu_ptr->flags = UPIU_CMD_FLAGS_NONE;
	upiu_ptr->reserved_1 = 0x00;
	upiu_ptr->task_tag = 0x01;
	upiu_ptr->reserved_2 = 0x00;

	if (params->opcode == READ_DESC_OPCODE)
		upiu_ptr->query_func = STANDARD_RD_REQ;
	else
		upiu_ptr->query_func = STANDARD_WR_REQ;

	upiu_ptr->query_resp = 0x00;
	upiu_ptr->reserved_3 = 0x00;
	upiu_ptr->tot_ehs_len = 0x00;
	if (params->opcode == READ_DESC_OPCODE)
		upiu_ptr->data_seg_len = 0x00;
	else
		upiu_ptr->data_seg_len = (to_bigendian16(params->length));

	for (i = 0; i < 16; i++) /* clear 16 tsf */
		upiu_ptr->tsf[i] = 0x0;
	upiu_ptr->tsf[0] = params->opcode;        /* 0: opcode */
	upiu_ptr->tsf[1] = params->desc_idn;      /* 1: idn */
	upiu_ptr->tsf[2] = params->desc_index;    /* 2: index */
	upiu_ptr->tsf[6] = (uint8_t)(params->length >> 8); /* 6: MSB shift 8 */
	upiu_ptr->tsf[7] = params->length & 0xff; /* 7: LSB */
	upiu_ptr->reserved_5 = 0x0;

	if ((params->opcode == WRITE_DESC_OPCODE) && (params->desc_idn == CONFIGURATION_DESC))
		modify_write_conf_desc(params);
}

/***************************************************************
 * read_descriptor
 * Description: The functon populates the request upiu structure
 *		with upiu info passed in 1st argument
 *
 ***************************************************************/
int read_descriptor(const void *req_upiu, void **resp_upiu_out)
{
	int ret;
	struct dwc_ufs_utrd *utrd = NULL;
	struct dwc_ufs_resp_upiu *resp_upiu = NULL;
	uint8_t free_slot;

	get_local_dwc_host();

	free_slot = dwc_ufshcd_get_xfer_req_free_slot(dwc_host);
	if (free_slot == BAD_SLOT)
		return UFS_ERR;

	utrd = dwc_host->lrb[free_slot].utrd;
	resp_upiu = dwc_host->lrb[free_slot].resp_upiu;

	/* UTRD Descriptor Programming for processing command */
	utrd->ct_and_flags = (uint8_t)
		(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	utrd->resp_upiu_length = to_littleendian16((uint16_t)
		(DWC_UCD_ALIGN >> UFS_DWORD_SHIFT));
	utrd->prdt_length = 0;

	create_desc_upiu(req_upiu, free_slot);

	ret = wait_for_cmd_completion(BIT(free_slot));
	if (ret != UFS_SUCCESS) {
		return ret;
	}

	*(resp_upiu_out) = resp_upiu;

	ret = handle_query_response(NULL, free_slot);
	return ret;
}

/***************************************************************
 * ufs_read_flag
 * Description: The function invokes do_flag_operation for Read
 *               flag operation
 *
 ***************************************************************/
int ufs_read_flag(enum flags_id idn, uint8_t *flags_ret)
{
	int ret;

	ret = do_flag_operation(READ_FLAG_OPCODE, STANDARD_RD_REQ, idn, flags_ret);
	return ret;
}

/***************************************************************
 * do_mode_change
 * Description: The function issues the the powermode change to
 *              UFS device to work using RX and Tx lanes and Gears
 *              as provided in pwr_mode_params structure.
 *
 ****************************************************************/
int do_mode_change(const struct pwr_mode_params *pmp)
{
	send_uic_command(DME_SET, 0x155c0000, 0x0, 0x0); /* PA_TxSkip */
	send_uic_command(DME_SET, 0x15680000, 0x0, pmp->tx_gear); /* PA_TxGear */
	send_uic_command(DME_SET, 0x15830000, 0x0, pmp->rx_gear); /* PA_RxGear */

	if (pmp->pwr_mode == FAST_MODE || pmp->pwr_mode == FASTAUTO_MODE) {
		send_uic_command(DME_SET, 0x156a0000, 0x0, pmp->hs_series); /* PA_HSSeries */
		send_uic_command(DME_SET, 0x15690000, 0x0, 0x1); /* PA_TxTermination */
		send_uic_command(DME_SET, 0x15840000, 0x0, 0x1); /* PA_RxTermination */
		send_uic_command(DME_SET, 0x15850000, 0x0, 0x1); /* PA_Scrambling */
	} else if (pmp->pwr_mode == SLOW_MODE || pmp->pwr_mode == SLOWAUTO_MODE) {
		send_uic_command(DME_SET, 0x15690000, 0x0, 0x0); /* PA_TxTermination */
		send_uic_command(DME_SET, 0x15840000, 0x0, 0x0); /* PA_RxTermination */
		send_uic_command(DME_SET, 0x15850000, 0x0, 0x0); /* PA_Scrambling */
	}

	send_uic_command(DME_SET, 0x15600000, 0x0, pmp->tx_lanes); /* PA_ActiveTxDataLanes */
	send_uic_command(DME_SET, 0x15800000, 0x0, pmp->rx_lanes); /* PA_ActiveRxDataLanes */

	send_uic_command(DME_SET, 0x15b00000, 0x0, 0x1FFF); /* PA_PWRModeUserData0 */
	send_uic_command(DME_SET, 0x15b10000, 0x0, 0xFFFF); /* PA_PWRModeUserData1 */
	send_uic_command(DME_SET, 0x15b20000, 0x0, 0x7FFF); /* PA_PWRModeUserData2 */
	send_uic_command(DME_SET, 0x15b30000, 0x0, 0x1FFF); /* PA_PWRModeUserData3 */
	send_uic_command(DME_SET, 0x15b40000, 0x0, 0xFFFF); /* PA_PWRModeUserData4 */
	send_uic_command(DME_SET, 0x15b50000, 0x0, 0x7FFF); /* PA_PWRModeUserData5 */
	send_uic_command(DME_SET, 0xd0410000, 0x0, 0x1FFF); /* DME_FC0ProtectionTimeOutVal */
	send_uic_command(DME_SET, 0xd0420000, 0x0, 0xFFFF); /* DME_TC0ReplayTimeOutVal */
	send_uic_command(DME_SET, 0xd0430000, 0x0, 0x7FFF); /* DME_AFC0ReqTimeOutVal */
	send_uic_command(DME_SET, 0xd0440000, 0x0, 0x1FFF); /* DME_FC1ProtectionTimeOutVal */
	send_uic_command(DME_SET, 0xd0450000, 0x0, 0xFFFF); /* DME_TC1ReplayTimeOutVal */
	send_uic_command(DME_SET, 0xd0460000, 0x0, 0x7FFF); /* DME_AFC1ReqTimeOutVal */

	/* VS_DebugCounter0Mask */
	send_uic_command(DME_SET, 0xd09a0000, 0x0, 0x80000000);
	/* VS_DebugCounter1Mask */
	send_uic_command(DME_SET, 0xd09b0000, 0x0, 0x78000000);
	send_uic_command(DME_SET, 0x15710000, 0x0, pmp->pwr_mode); /* PA_PWRMode */

	return 0;
}

void adapt_pll_to_power_mode(enum POWER_MODE pwrmode, uint8_t gear, uint8_t rate)
{
	if (pwrmode == FAST_MODE || pwrmode == FASTAUTO_MODE) {
		if (gear == 1) { /* hs-g1 */
			if (rate == 2) { /* 2: rateb */
				send_uic_command(DME_SET, attr_mcb(RG_PLL_PRE_DIV), 0x0, 0x0);
				send_uic_command(DME_SET, attr_mcb(RG_PLL_SWC_EN), 0x0, 0x0);
				send_uic_command(DME_SET, attr_mcb(RG_PLL_FBK_S), 0x0, 0x01);
				send_uic_command(DME_SET, attr_mcb(RG_PLL_FBK_P), 0x0, 0x4c);
			}
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXHSGR), 0x0, 0x02);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXHSGR), 0x0, 0x02);
		} else if (gear == 2) { /* hs-g2 */
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXHSGR), 0x0, 0x01);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXHSGR), 0x0, 0x01);
		} else if (gear == 3) { /* hs-g3 */
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXHSGR), 0x0, 0x0);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXHSGR), 0x0, 0x0);
		}
	}

	/* the PWM's clk is been derived from the pll above */
	if (pwrmode == SLOW_MODE || pwrmode == SLOWAUTO_MODE) {
		if (gear == 1) { /* pwm-g1 */
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXLSGR), 0x0, 0x07);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXLSGR), 0x0, 0x06);
		} else if (gear == 2) { /* pwm-g2 */
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXLSGR), 0x0, 0x06);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXLSGR), 0x0, 0x05);
		} else if (gear == 3) { /* pwm-g3 */
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXLSGR), 0x0, 0x05);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXLSGR), 0x0, 0x04);
		} else if (gear == 4) { /* pwm-g4 */
			send_uic_command(DME_SET, attr_mcb(RG_PLL_TXLSGR), 0x0, 0x04);
			send_uic_command(DME_SET, attr_mcb(RG_PLL_RXLSGR), 0x0, 0x03);
		}
	}
}

static int change_power_mode(enum POWER_MODE pwrmode, uint8_t gear, uint8_t rate, uint8_t lane)
{
	struct pwr_mode_params pmp;
	uint32_t value;
	int retry = 1000; /* retry 1000 times */
	int index = find_device_index();
	int ret;

	printf("UFS %s Gear-%d Rate-%c Lane-%d\n",
		 ((pwrmode == SLOW_MODE) ? "Slow" :
		 ((pwrmode == SLOWAUTO_MODE) ? "SlowAuto" :
		 ((pwrmode == FAST_MODE) ? "Fast" : "FastAuto"))),
		 gear, (rate == 1) ? 'A' : 'B', lane);

	pmp.tx_gear = gear;
	pmp.rx_gear = gear;
	pmp.hs_series = rate;

	if (lane == 1) {
		g_tx_lane_num[index] = 1;
		g_rx_lane_num[index] = 1;
	} else {
		/* PA_ConnectedTxDataLanes */
		g_tx_lane_num[index] = (uint8_t)uic_cmd_read(0x1, 0x15610000);

		/* PA_ConnectedRxDataLanes */
		g_rx_lane_num[index] = (uint8_t)uic_cmd_read(0x1, 0x15810000);

		printf("UFS connected lanes Tx-%d Rx-%d\n", g_tx_lane_num[index], g_rx_lane_num[index]);
	}

	pmp.tx_lanes = g_tx_lane_num[index];
	pmp.rx_lanes = g_rx_lane_num[index];
	pmp.pwr_mode = pwrmode;

	adapt_mode_change(&pmp);
	adapt_pll_to_power_mode(pwrmode, gear, rate);

	ret = do_mode_change(&pmp);
	if (ret)
		return ret;

	while (--retry) {
		value = dwc_ufs_read_reg(UFS_IS_OFF);
		if (value & UFS_IS_UPMS_BIT) {
			dwc_ufs_write_reg(UFS_IS_OFF, UFS_IS_UPMS_BIT);
			break;
		}
		ufs_waitms(1);
	}
	value = dwc_ufs_read_reg(UFS_HCS_OFF);
	if (((value & UFS_HCS_UPMCRS_MASK) >> UFS_HCS_UPMCRS_OFF) != 0x1) {
		printf("check HCS.UPMCRS error, HCS = 0x%x\n", value);
		return -1;
	}

	/* set 0xc4 to 0x80 after mode changes */
	/* RX_ERR_STATUS */
	send_uic_command(DME_SET, 0x00c40004, 0x0, 0x80);
	send_uic_command(DME_SET, 0x00c50004, 0x0, 0x01);
	/* RX_ERR_STATUS */
	send_uic_command(DME_SET, 0x00c40005, 0x0, 0x80);
	send_uic_command(DME_SET, 0x00c50005, 0x0, 0x01);
	return UFS_OK;
}

static int ufs_init(enum POWER_MODE mode, int hs_gear, int rate, int lane)
{
	int ret;

	get_local_dwc_host();

	if (dwc_host->is_init)
		return 0;

	ufs_hardware_init();

	ret = ufs_host_init();
	if (ret) {
		printf("ufs host init fail. ret: %d\n", ret);
		return ret;
	}

	ret = ufs_device_init();
	if (ret) {
		printf("ufs device init fail. ret: %d\n", ret);
		return ret;
	}

	ret = ufs_get_device_info();
	if (ret) {
		printf("ufs get device info fail. ret: %d\n", ret);
		return ret;
	}

	ret = ufs_lu_init();
	if (ret) {
		printf("ufs lu init fail. ret: %d\n", ret);
		return ret;
	}

	ret = ufs_set_ref_clk();
	if (ret) {
		printf("ufs set ref clk fail. ret: %d\n", ret);
		return ret;
	}

	ret = change_power_mode(mode, hs_gear, rate, lane);
	if (ret) {
		printf("ufs change mode fail. ret: %d\n", ret);
		return ret;
	}

	ret = ufs_set_active_lun(DEFAULT_ACTIVE_LUN);
	if (ret) {
		printf("ufs set active lun fail. ret: %d\n", ret);
		return ret;
	}

	ufs_info_init();
	dwc_host->is_init = 1;

	return ret;
}

int ufs_storage_init(void)
{
	get_local_dwc_host();

	if (ufs_init(DEFAULT_MODE, DEFAULT_GEAR, DEFAULT_RATE, DEFAULT_LANE) != 0) {
		/* release resource */
		if (dwc_host->mem_pool)
			free(dwc_host->mem_pool);
		if (dwc_host->wr_buf)
			free(dwc_host->wr_buf);

		dwc_host->mem_pool = NULL;
		dwc_host->wr_buf = NULL;
		printf("ufs release memory pool\n");
	}

	return 0;
}

void ufs_reinit(void)
{
	get_local_dwc_host();

	if (dwc_host->mem_pool)
		free(dwc_host->mem_pool);
	if (dwc_host->wr_buf)
		free(dwc_host->wr_buf);

	dwc_host->mem_pool = NULL;
	dwc_host->wr_buf = NULL;
	dwc_host->is_init = 0;

	ufs_storage_init();
}

