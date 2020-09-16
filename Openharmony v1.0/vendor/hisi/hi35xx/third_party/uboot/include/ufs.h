/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef _UFS_H
#define _UFS_H
#ifndef CONFIG_UFS
/**
 * ufs_probe() - initialize all devices in the UFS uclass
 *
 * @return 0 if Ok, -ve on error
 */
int ufs_probe(void);

/**
 * ufs_probe_dev() - initialize a particular device in the UFS uclass
 *
 * @index: index in the uclass sequence
 *
 * @return 0 if successfully probed, -ve on error
 */
int ufs_probe_dev(int index);

/*
 * ufs_scsi_bind() - Create a new scsi device as a child of the UFS device and
 *		     bind it to the ufs_scsi driver
 * @ufs_dev: UFS device
 * @scsi_devp: Pointer to scsi device
 *
 * @return 0 if Ok, -ve on error
 */
int ufs_scsi_bind(struct udevice *ufs_dev, struct udevice **scsi_devp);
#else

#include <common.h>
#include <asm/io.h>

#define MAX_DEVICE 1
#define find_device_index() (0)
#define get_local_dwc_host() \
	struct dwc_ufs_hba *dwc_host = &g_dwc_host[find_device_index()];

#define UFS_OK    0
#define UFS_ERR   (-1)

#define bytes_align_128(x)    ((x + 128 - 1) & ~(128 - 1))
#define bytes_align_1024(x)   ((x + 1024 - 1) & ~(1024 - 1))

/* UFSHCD Registers Offsets */
#define UFS_CAP_OFF             0x00
#define UFS_VER_OFF             0x08
#define UFS_HCPID_OFF           0x10
#define UFS_HCMID_OFF           0x14
#define UFS_AHIT_OFF            0x18
#define UFS_IS_OFF              0x20
#define UFS_IE_OFF              0x24
#define UFS_HCS_OFF             0x30
#define UFS_HCE_OFF             0x34
#define UFS_UECPA_OFF           0x38
#define UFS_UECDL_OFF           0x3C
#define UFS_UECN_OFF            0x40
#define UFS_UECT_OFF            0x44
#define UFS_UECDME_OFF          0x48
#define UFS_UTRIACR_OFF         0x4C
#define UFS_UTRLBA_OFF          0x50
#define UFS_UTRLBAU_OFF         0x54
#define UFS_UTRLDBR_OFF         0x58
#define UFS_UTRLCLR_OFF         0x5C
#define UFS_UTRLRSR_OFF         0x60
#define UFS_UTMRLBA_OFF         0x70
#define UFS_UTMRLBAU_OFF        0x74
#define UFS_UTMRLDBR_OFF        0x78
#define UFS_UTMRLCLR_OFF        0x7C
#define UFS_UTMRLRSR_OFF        0x80
#define UFS_UICCMD_OFF          0x90
#define UFS_UICCMDARG1_OFF      0x94
#define UFS_UICCMDARG2_OFF      0x98
#define UFS_UICCMDARG3_OFF      0x9C
#define UFS_BUSTHRTL_OFF        0xC0
#define UFS_OOCPR_OFF           0xC4
#define UFS_FEIE_OFF            0xC8
#define UFS_CDACFG_OFF          0xD0
#define UFS_CDATX1_OFF          0xD4
#define UFS_CDATX2_OFF          0xD8
#define UFS_CDARX1_OFF          0xDC
#define UFS_CDARX2_OFF          0xE0
#define UFS_CDASTA_OFF          0xE4
#define UFS_LBMCFG_OFF          0xF0
#define UFS_LBMSTA_OFF          0xF4
#define UFS_DBG_OFF             0xF8
#define UFS_HCLKDIV_OFF         0xFC

/* Controller capability masks and shift value */
#define DWC_UFS_NUTRS_MASK      0x0000001f
#define DWC_UFS_NUTMRS_MASK     0x00070000
#define DWC_UFS_NUTMRS_SHIFT    16
#define DWC_UFS_AUTOH8          0x00800000
#define DWC_UFS_AUTOH8_SHIFT    23

/* GenSelectorIndex */
#define MTX_L0  0x0000
#define MTX_L1  0x0001
#define MRX_L0  0x0004
#define MRX_L1  0x0005

#define ATTR_M_SHIFT            16
#define attr_mtx0(x)            ((x << ATTR_M_SHIFT) | MTX_L0)
#define attr_mtx1(x)            ((x << ATTR_M_SHIFT) | MTX_L1)
#define attr_mrx0(x)            ((x << ATTR_M_SHIFT) | MRX_L0)
#define attr_mrx1(x)            ((x << ATTR_M_SHIFT) | MRX_L1)
#define attr_mcb(x)             ((u32)((u16)(x) << ATTR_M_SHIFT))

/*
 * Register Fields
 */
#define UFS_AUTO_HIBERNATE_BIT		BIT(23)
#define UFS_CAPS_64AS_BIT		BIT(24)
#define UFS_HCE_RESET_BIT		BIT(0)
#define UFS_HCS_DP_BIT			BIT(0)
#define UFS_HCS_UCRDY_BIT		BIT(3)
#define UFS_HCS_UPMCRS_OFF		(8)
#define UFS_HCS_UPMCRS_MASK		(0x3 << UFS_HCS_UPMCRS_OFF)
#define UFS_IS_UE_BIT			BIT(2)
#define UFS_IS_UPMS_BIT			BIT(4)
#define UFS_IS_UHXS_BIT			BIT(5)
#define UFS_IS_UHES_BIT			BIT(6)
#define UFS_IS_ULSS_BIT			BIT(8)
#define UFS_IS_UCCS_BIT			BIT(10)
#define UFS_UTP_RUN_BIT			BIT(0)
#define UFS_LBMCFG_DEFAULT_VALUE	0xb01
#define UFS_HCLKDIV_NORMAL_VALUE	0xFA
#define UFS_HCLKDIV_SLOW_VALUE		0x14
#define UFS_HCLKDIV_FPGA_VALUE		0x12

#define UFS_AHIT_AH8ITV_MASK		(0x3FF)
#define UFS_AHIT_AUTOH8_TIMER		(0x1001)

#define UIC_LINK_STARTUP_CMD		0x16
#define NOP_TRANS_TYPE			0x20
#define BAD_SLOT                0x55
#define NOP_TRANS_TYPE          0x20
#define PRDT_BUFFER_SIZE        0x40000
#define UNIT_DESCS_COUNT        8
#define CAPACITY_DATA_LENGTH    8
#define SENSE_DATA_LENGTH       20
#define SENSE_KEY_INDEX         36
#define RPMB_DATA_SIZE          256
#define RPMB_FRAME_SIZE         512
#define LOGICAL_BLK_SIZE        4096
#define UFS_DWORD_SHIFT         2

#define QUERY_DESC_MANUFACTURER_NAME_MAX_SIZE 0x12
#define QUERY_DESC_PRODUCT_NAME_MAX_SIZE      0x22
#define QUERY_DESC_STRING_MAX_SIZE            0xFE

#ifdef UFS_DEBUG
#define ufs_pr_dbg(fmt, s...) printf(fmt, ##s)
#define ufs_pr_mem(fmt, s...) printf(fmt, ##s)
#define ufs_pr_reg(fmt, s...) printf(fmt, ##s)
#define ufs_pos() printf("pos -- %s: %d\n", __func__, __LINE__)
#else
#define ufs_pr_dbg(s...)
#define ufs_pr_mem(s...)
#define ufs_pr_reg(s...)
#define ufs_pos()
#endif

/* Data structure sizes in bytes */
enum {
	DWC_UFS_BASIC_UPIU_SIZE = 32,
	DWC_UFS_UTRD_SIZE = 32,
	DWC_UFS_TSF_SIZE = 16,
	DWC_UFS_PRD_SIZE = 16,

	DWC_UFSHCD_MAX_PRD_SIZE = 8,	/* 128 (Linux) */

	DWC_MAX_QUERY_DATA = 256,
	DWC_UFS_CDB_SIZE = 16,
	DWC_UFS_SENSE_DATA_SIZE = 18,

	DWC_UFS_UTMRD_HDR_SIZE = 16,
};

/* Alignment Requirement in bytes */
enum {
	DWC_UTRL_BASE_ALIGN = 1024,
	DWC_UCD_ALIGN = 512,
	DWC_CMD_BASE_ALIGN = 128,
};

/* Rate */
enum UFS_RATE {
	UFS_RATE_A = 1,
	UFS_RATE_B = 2
};

/* Power mode */
enum POWER_MODE {
	FAST_MODE = 0x11,
	SLOW_MODE = 0x22,
	FASTAUTO_MODE = 0x44,
	SLOWAUTO_MODE = 0x55,
	INVALID_MODE = 0xFF
};

enum ufs_pwm_gear_tag {
	UFS_PWM_DONT_CHANGE,
	UFS_PWM_G1,
	UFS_PWM_G2,
	UFS_PWM_G3,
	UFS_PWM_G4,
	UFS_PWM_G5,
	UFS_PWM_G6,
	UFS_PWM_G7,
};

enum ufs_hs_gear_tag {
	UFS_HS_DONT_CHANGE,
	UFS_HS_G1,
	UFS_HS_G2,
	UFS_HS_G3,
};

struct pwr_mode_params {
	uint8_t tx_gear;
	uint8_t rx_gear;
	uint8_t hs_series;
	uint8_t tx_lanes;
	uint8_t rx_lanes;
	uint8_t pwr_mode;
};

#define WELL_BOOT_LU_A     0x01
#define WELL_BOOT_LU_B     0x02

#define DEFAULT_BOOT_LUN   WELL_BOOT_LU_A
#define DEFAULT_ACTIVE_LUN 3

#define DEFAULT_MODE       FAST_MODE
#define DEFAULT_GEAR       UFS_HS_G3
#define DEFAULT_RATE       UFS_RATE_B
#define DEFAULT_LANE       2

#pragma pack(push)
#pragma pack(1)

/*
 * Command UPIU Structure
 */
struct dwc_ufs_cmd_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;
	uint8_t reserved_1_0;
	uint8_t reserved_1_1;
	uint8_t reserved_1_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_2;
	uint16_t data_seg_len;
	uint32_t exp_data_xfer_len;
	uint8_t cdb[16]; /* 16 cdb size */
};

/*
 * Query UPIU Structure
 */
struct dwc_ufs_query_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2;
	uint8_t query_func;
	uint8_t query_resp;
	uint8_t reserved_3;
	uint8_t tot_ehs_len;
	uint8_t reserved_4;
	uint16_t data_seg_len;
	uint8_t tsf[16]; /* 16 tsf size */
	uint32_t reserved_5;
};

/*
 * NOP OUT UPIU Structure
 */
struct dwc_ufs_nop_req_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint32_t reserved_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint8_t reserved_4[20]; /* 20 reserved */
};

/*
 * NOP IN UPIU Structure
 */
struct dwc_ufs_nop_resp_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2_0;
	uint8_t reserved_2_1;
	uint8_t response;
	uint8_t reserved_3;
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint8_t reserved_4[20]; /* 20 reserved */
};

/*
 * Transfer Response UPIU Structure
 */
struct dwc_ufs_resp_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;
	uint8_t reserved_1;
	uint8_t response;
	uint8_t status;
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint32_t residual_xfer_count;
	uint32_t reserved_2;
	uint32_t reserved_3;
	uint32_t reserved_4;
	uint32_t reserved_5;
	uint16_t sense_data_len;
	uint8_t sense_data[18]; /* 18 sense size */
};

struct dwc_ufs_prd {
	uint32_t base_addr;
	uint32_t upper_addr;
	uint32_t reserved1;
	uint32_t size;
};

/**
 * dwc_ufs_ucd
 * UTP Command Descriptor (UCD) structure.
 * Every UTRD contains a pointer for this data structure
 * This structure logically consists of 3 parts
 *	1. "Transfer Request" or "Command UPIU" (SCSI, Native UFS & DM)
 *	2. "Transfer Response" or "Response UPIU"
 *	3. "Physical Region Description Table"(PRDT).
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space.
 * "Transfer Request" and "Transfer Response" are in BIG ENDIAN Format
 * "PRDT" is in LITTLE ENDIAN Format
 */
struct dwc_ufs_ucd {
	uint8_t cmd_upiu[DWC_UCD_ALIGN];
	uint8_t resp_upiu[DWC_UCD_ALIGN];
	struct dwc_ufs_prd prdt[DWC_UFSHCD_MAX_PRD_SIZE];
};

struct dwc_ufs_utrd {
	uint8_t reserved_1_0:8;
	uint8_t reserved_1_1:8;
	uint8_t reserved_1_2:8;
	uint8_t ct_and_flags:8;
	uint32_t reserved_2:32;
	uint8_t ocs:8;
	uint8_t reserved_3_0:8;
	uint8_t reserved_3_1:8;
	uint8_t reserved_3_2:8;
	uint32_t reserved_4:32;

	/* Only bits 31:7 are valid; 128B Aligned addr */
	uint32_t ucdba:32;
	uint32_t ucdbau:32;
	uint16_t resp_upiu_length:16;
	uint16_t resp_upiu_offset:16;

	uint16_t prdt_length:16;
	uint16_t prdt_offset:16;
};

/**
 * dwc_ufs_tm_req_upiu
 * Task Management Request UPIU structure
 * Size of this structure is 32 bytes
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space. This structure is in BIG ENDINA Format
 */
struct dwc_ufs_tm_req_upiu {	/* BIG ENDIAN */
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t reserved_1;
	uint8_t tm_fn;
	uint8_t reserved_2_0;
	uint8_t reserved_2_1;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint32_t input_param_1;
	uint32_t input_param_2;
	uint32_t input_param_3;
	uint32_t reserved_4;
	uint32_t reserved_5;
};

/**
 * dwc_ufs_tm_resp_upiu
 * Task Management Response UPIU structure
 * Size of this structure is 32 bytes
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space. This structure is in BIG ENDINA Format
 */
struct dwc_ufs_tm_resp_upiu {	/* BIG ENDIAN */
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t reserved_1_0;
	uint8_t reserved_1_1;
	uint8_t response;
	uint8_t reserved_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint32_t output_param_1;
	uint32_t output_param_2;
	uint32_t reserved_4;
	uint32_t reserved_5;
	uint32_t reserved_6;
};

struct dwc_ufs_utmrd {
	uint8_t reserved_1_0:8;
	uint8_t reserved_1_1:8;
	uint8_t reserved_1_2:8;
	uint8_t intr_flag:8;
	uint32_t reserved_2:32;
	uint8_t ocs:8;
	uint8_t reserved_3_0:8;
	uint8_t reserved_3_1:8;
	uint8_t reserved_3_2:8;
	uint32_t reserved_4:32;

	struct dwc_ufs_tm_req_upiu tm_req_upiu;
	struct dwc_ufs_tm_resp_upiu tm_resp_upiu;
};

struct query_param {
	uint8_t opcode;
	uint8_t idn;
	uint8_t index;
	uint8_t selector;
};

struct cmd_param {
	uint64_t addr;
	uint64_t src;
	uint32_t size;
};

#pragma pack(pop)

struct partition_desc {
	uint8_t boot_lun_id;
	uint8_t write_protect;
	uint8_t memory_type;
	uint8_t data_reliability;
	uint8_t block_size;
	uint8_t prov_type;
	uint16_t context_capabilities;
	uint32_t lu_capacity;
#define UFS_MAX_LU_CAP		0xFFFFFFFF
	uint32_t num_alloc_units;
};

struct configuration_header {
	uint8_t b_boot_enable;
	uint8_t b_descr_access_en;
	uint8_t b_init_power_mode;
	uint8_t b_high_priority_lun;
	uint8_t b_secure_removal_type;
	uint8_t b_init_active_icc_level;
	uint16_t w_periodic_rtc_update;
};

struct partition_desc_table {
	uint8_t b_number_lu;
	uint8_t b_allocation_unit_size;
	uint32_t d_segment_size;
	uint64_t q_total_raw_device_capacity;
	uint8_t b_data_ordering;
	uint8_t b_max_contex_id_number;
	uint16_t w_supported_memory_types;
	uint32_t d_system_code_max_alloc_u;
	uint16_t w_system_code_cap_adj_fac;
	uint32_t d_non_persist_max_alloc_u;
	uint16_t w_non_persist_cap_adj_fac;
	uint32_t d_enhanced1_max_alloc_u;
	uint16_t w_enhanced1_cap_adj_fac;
	uint32_t d_enhanced2_max_alloc_u;
	uint16_t w_enhanced2_cap_adj_fac;
	struct configuration_header *p_conf_header;
	struct partition_desc *partition_desc_ptr[UNIT_DESCS_COUNT];
};

struct desc_params {
	void *req_upiu;
	struct configuration_header *conf_head;
	struct partition_desc **part_desc;
	uint8_t opcode;
	uint8_t desc_idn;
	uint8_t desc_index;
	uint16_t length;
};

/* UFS: Device descriptor */
struct ufs_device_descriptor {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint8_t b_device;
	uint8_t b_device_class;
	uint8_t b_device_sub_class;
	uint8_t b_protocol;
	uint8_t b_number_lu;
	uint8_t b_number_wlu;
	uint8_t b_boot_enable;
	uint8_t b_descr_access_en;
	uint8_t b_init_power_mode;
	uint8_t b_high_priority_lun;
	uint8_t b_secure_removal_type;
	uint8_t b_security_lu;
	uint8_t b_background_ops_term_lat;
	uint8_t b_init_active_icc_level;
	uint16_t w_spec_version;
	uint16_t w_manufacture_date;
	uint8_t i_manufacturer_name;
	uint8_t i_product_name;
	uint8_t i_serial_number;
	uint8_t i_oem_id;
	uint16_t w_manufacturer_id;
	uint8_t b_ud_0base_offset;
	uint8_t b_ud_config_plength;
	uint8_t b_device_rtt_cap;
	uint16_t w_periodic_rtc_update;
	uint8_t b_ufs_feature_support;
	uint8_t b_ffu_timeout;
	uint8_t b_queue_depth;
	uint16_t w_device_version;
	uint8_t b_num_secure_wp_area;
	uint32_t d_psa_max_data_size;
	uint8_t b_psa_state_timeout;
	uint8_t i_product_revision_level;
	uint8_t reserved[5]; /* 5 reserved */
	uint8_t reserved_ume[16]; /* 16 reserved */
} __attribute__ ((packed));

/* UFS: Geometry descriptor */
struct ufs_geometry_descriptor {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint8_t b_media_technology;
	uint8_t reserved;
	uint64_t q_total_raw_device_capacity;
	uint8_t b_max_number_lu;
	uint32_t d_segment_size;
	uint8_t b_allocation_unit_size;
	uint8_t b_min_addr_block_size;
	uint8_t b_optimal_read_block_size;
	uint8_t b_optimal_write_block_size;
	uint8_t b_max_in_buffer_size;
	uint8_t b_max_out_buffer_size;
	uint8_t b_rpmb_read_write_size;
	uint8_t b_dynamic_capacity_resource_policy;
	uint8_t b_data_ordering;
	uint8_t b_max_contex_id_number;
	uint8_t b_sys_data_tag_unit_size;
	uint8_t b_sys_data_tag_res_size;
	uint8_t b_supported_sec_rtypes;
	uint16_t w_supported_memory_types;
	uint32_t d_system_code_max_alloc_u;
	uint16_t w_system_code_cap_adj_fac;
	uint32_t d_non_persist_max_alloc_u;
	uint16_t w_non_persist_cap_adj_fac;
	uint32_t d_enhanced1_max_alloc_u;
	uint16_t w_enhanced1_cap_adj_fac;
	uint32_t d_enhanced2_max_alloc_u;
	uint16_t w_enhanced2_cap_adj_fac;
	uint32_t d_enhanced3_max_alloc_u;
	uint16_t w_enhanced3_cap_adj_fac;
	uint32_t d_enhanced4_max_alloc_u;
	uint16_t w_enhanced4_cap_adj_fac;
	uint32_t d_optimal_logical_block_size;
} __attribute__ ((packed));

/* UFS: String descriptor */
struct ufs_string_descriptor {
	char manufacturer_name[QUERY_DESC_MANUFACTURER_NAME_MAX_SIZE];
	char product_name[QUERY_DESC_PRODUCT_NAME_MAX_SIZE];
	char serial_number[QUERY_DESC_STRING_MAX_SIZE];
	char oem_id[QUERY_DESC_STRING_MAX_SIZE];
};

/* UFS: Health descriptor */
struct ufs_health_descriptor {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint8_t b_pre_eol_info;
	uint8_t b_device_life_time_est_a;
	uint8_t b_device_life_time_est_b;
	uint8_t reserved[32]; /* 32 reserved */
} __attribute__ ((packed));

/* UFS: Interconnect descriptor */
struct ufs_interconnect_descriptor {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint16_t bcd_unipro_version;
	uint16_t bcd_mphy_version;
} __attribute__ ((packed));

struct ufs_unit_index_descriptror {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint8_t b_unit_index;
	uint8_t b_lu_enable;
	uint8_t b_boot_lun_id;
	uint8_t b_lu_write_protect;
	uint8_t b_lu_queue_depth;
	uint8_t b_psa_sensitive;
	uint8_t b_memory_type;
	uint8_t b_data_reliability;
	uint8_t b_logical_block_size;
	uint64_t q_logical_block_count;
	uint32_t d_erase_block_size;
	uint8_t b_provisioning_type;
	uint64_t q_phy_mem_resource_count;
	uint16_t w_context_capabilities;
	uint8_t b_large_unit_granularity_m1;
} __attribute__ ((packed));

struct ufs_unit_rpmb_descriptror {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint8_t b_unit_index;
	uint8_t b_lu_enable;
	uint8_t b_boot_lun_id;
	uint8_t b_lu_write_protect;
	uint8_t b_lu_queue_depth;
	uint8_t b_psa_sensitive;
	uint8_t b_memory_type;
	uint8_t reserved1;
	uint8_t b_logical_block_size;
	uint64_t q_logical_block_count;
	uint32_t d_erase_block_size;
	uint8_t b_provisioning_type;
	uint64_t q_phy_mem_resource_count;
	uint8_t reserved2[3]; /* 3 reserved */
} __attribute__ ((packed));

struct ufs_unit_descriptor {
	struct ufs_unit_index_descriptror unit_index_desc[UNIT_DESCS_COUNT];
	struct ufs_unit_rpmb_descriptror unit_rpmb_desc;
} __attribute__ ((packed));

struct ufs_dev_desc_configuration_param {
	uint8_t b_length;
	uint8_t b_descriptor_idn;
	uint8_t b_conf_desc_continue;
	uint8_t b_boot_enable;
	uint8_t b_descr_access_en;
	uint8_t b_init_power_mode;
	uint8_t b_high_priority_lun;
	uint8_t b_secure_removal_type;
	uint8_t b_init_active_icc_level;
	uint16_t w_periodic_rtc_update;
	uint8_t reserved[5]; /* 5 reserved, 11 in ufs3.1 */
} __attribute__ ((packed));

struct ufs_unit_desc_configuration_param {
	uint8_t b_lu_enable;
	uint8_t b_boot_lun_id;
	uint8_t b_lu_write_protect;
	uint8_t b_memory_type;
	uint32_t d_num_alloc_units;
	uint8_t b_data_reliability;
	uint8_t b_logical_block_size;
	uint8_t b_provisioning_type;
	uint16_t w_context_capabilities;
	uint8_t reserved[3]; /* 3 reserved, 13 in ufs3.1 */
} __attribute__ ((packed));

struct ufs_configuration_descriptor {
	struct ufs_dev_desc_configuration_param dev_desc_conf_param;
	struct ufs_unit_desc_configuration_param unit_desc_conf_param[UNIT_DESCS_COUNT];
} __attribute__ ((packed));

struct ufs_descriptor {
	uint32_t desc_is_init;
	struct ufs_device_descriptor dev_desc;
	struct ufs_string_descriptor str_desc;
	struct ufs_geometry_descriptor geo_desc;
	struct ufs_unit_descriptor unit_desc;
	struct ufs_configuration_descriptor conf_desc;
	struct ufs_health_descriptor heal_desc;
	struct ufs_interconnect_descriptor intr_desc;
};

/**
 * struct dwc_ufs_hcd_lrb
 * Local Reference Block for application commands (eg:scsi)
 * Maintained for every utrd slot
 * @command_type: Maintained to abstract the application layer out of core
 * @data_direction: whether command is a read/write or no-data command
 * @ocs: ocs from utrd is read and kept here for future analysis
 * @xfer_command_status: holds the response from response-upiu(eg: Scsi status)
 * @transfer_size: total size of transfer in bytes
 * @task_tag: task_tag
 * @lun: lun
 * @scmd: scsi command; should be null if its not a scsi command
 * @utrd: transfer descriptor address pointer
 * @cmd_upiu: address of command upiu
 * @resp_upiu: address of response upiu
 * @prdt: base address of prd table
 * @sense_buffer_len: sense buffer length in bytes
 * @sense_buffer: pointer to sense buffer for the command
 */
struct dwc_ufs_hcd_lrb {
	uint8_t command_type;
	uint8_t data_direction;
	uint8_t read_write_flags;
	uint8_t ocs;
	uint8_t xfer_command_status;

	uint32_t transfer_size;
	uint32_t task_tag;
	uint32_t lun;

	struct dwc_ufs_utrd *utrd;
	struct dwc_ufs_cmd_upiu *cmd_upiu;
	struct dwc_ufs_resp_upiu *resp_upiu;
	struct dwc_ufs_prd *prdt;

	uint16_t sense_buffer_len;
	uint8_t *sense_buffer;
};

/**
 * struct dwc_ufshcd_dm_lrb
 * Local Reference Block for Device management commands (eg: nopout, query ..)
 * Maintained one per driver instance
 * @trans_type: Transaction Type (query/nopout ..)
 * @flags:flags indicating Read/Write
 * @lun: lun to be addressed through this command
 * @query_fn: query_function
 * @tot_ehs_len: total ehs length
 * @data_seg_len: data segment length for this command
 * @tsf: transaction specific field for this command
 * @dm_cmd_results: Device management function result updated after
 * post processing
 */
struct dwc_ufshcd_dm_lrb {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	/* We cant fix task tag; it is dynamically set */
	uint8_t query_fn;
	uint8_t tot_ehs_len;
	uint16_t data_seg_len;
	uint8_t tsf[DWC_UFS_TSF_SIZE];

	int dm_cmd_results;
};

/**
 * struct dwc_ufs_hba
 * Private structure of the host bus adapter
 * @caps: DWC UFS HC capabilities stored here for reference
 * @ufs_version: UFS version read adn kept here
 * @nutrs: Transfer Request Queue depth supported by DWC UFS HC
 * @nutmrs: Task Management Queue depth supported by DWC UFS HC
 * @utrl_base_addr: UTP Transfer Request Descriptor List base address (virtual)
 * @utmrl_base_addr: UTP Task Management Descriptor List base address (virtual)
 * @ucdl_base_addr: UFS Command Descriptor List Base Address (virtual)
 * @lrb: pointer to local reference block list
 * @dm_lrb: local reference block device management commands
 * @outstanding_xfer_reqs: outstanding transfer requests to be processed
 */
struct dwc_ufs_hba {
	uint32_t caps;
	uint8_t nutrs;
	uint8_t nutmrs;
	uint8_t autoh8;

	uint8_t active_lun;
	uint8_t active_bootlun;
	uint8_t lu_request_sense_sent[UNIT_DESCS_COUNT];
	uint8_t unit_offset;
	uint8_t unit_length;
	uint16_t manufacturer_id;
#define UFS_MANUFACTURER_ID_TOSHIBA	0x0198
#define UFS_MANUFACTURER_ID_HYNIX	0x01AD
#define UFS_MANUFACTURER_ID_SAMSUNG	0x01CE
#define UFS_MANUFACTURER_ID_HI1861	0x08B6
#define UFS_MANUFACTURER_ID_MICRON	0x012C
#define UFS_MANUFACTURER_ID_SANDISK	0x0145
	uint16_t dev_spec_version;
	uint16_t manufacturer_date;

	/* Virtual memory reference for driver */
	void *mem_pool;
	void *wr_buf;
	struct dwc_ufs_utrd *utrl_base_addr;
	struct dwc_ufs_utmrd *utmrl_base_addr;
	struct dwc_ufs_ucd *ucdl_base_addr;

	struct dwc_ufs_hcd_lrb *lrb;
	struct dwc_ufshcd_dm_lrb dm_lrb;

	/* Outstanding requests */
	uint32_t outstanding_xfer_reqs;

	uint8_t is_init;
};

/* Byte swap u16 */
static inline uint16_t swap_16(uint16_t val)
{
	return (uint16_t)((val << 8) | (val >> 8)); /* shift 8 */
}

/* Byte swap unsigned int */
static inline uint32_t swap_32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF); /* shift 8 */
	return (uint32_t)((val << 16) | (val >> 16)); /* shift 16 */
}

static inline uint32_t to_bigendian32(uint32_t val)
{
#ifdef HOST_BIG_ENDIAN
	return val;
#else
	return swap_32(val);
#endif
}

static inline uint32_t to_littleendian32(uint32_t val)
{
#ifdef HOST_BIG_ENDIAN
	return swap_32(val);
#else
	return val;
#endif
}

static inline uint16_t to_bigendian16(uint16_t val)
{
#ifdef HOST_BIG_ENDIAN
	return val;
#else
	return swap_16(val);
#endif
}

static inline uint16_t to_littleendian16(uint16_t val)
{
#ifdef HOST_BIG_ENDIAN
	return swap_16(val);
#else
	return val;
#endif
}

static inline void ufs_waitms(uint32_t delay)
{
	while (delay--)
		udelay(1000); /* delay 1000us */
}

/* UFS Command Opcodes */
#define READ_DESC_OPCODE   0x1
#define WRITE_DESC_OPCODE  0x2
#define READ_ATTR_OPCODE   0x3
#define WRITE_ATTR_OPCODE  0x4
#define READ_FLAG_OPCODE   0x5
#define SET_FLAG_OPCODE    0x6
#define CLEAR_FLAG_OPCODE  0x7
#define TOGGLE_FLAG_OPCODE 0x8

/* Descriptor Idn's */
#define DEVICE_DESC        0x00
#define CONFIGURATION_DESC 0x01
#define UNIT_DESC          0x02
#define INTERCONNECT_DESC  0x04
#define STRING_DESC        0x05
#define GEOMETRY_DESC      0x07
#define POWER_DESC         0x08
#define HEALTH_DESC        0x09

#define DEVICE_DESC_LENGTH        0x40
#define UNIT_DESC_LENGTH          0x23
#define GEOMETRY_DESC_LENGTH      0x44
#define CONFIGURATION_DESC_LENGTH 0x90
#define INTERCONNECT_DESC_LENGTH  0x06
#define STRING_DESC_LENGTH        0xFE
#define POWER_DESC_LENGTH         0x62
#define HEALTH_DESC_LENGTH        0x25
#define MAX_DESC_LENGTH           0xFF

#define STANDARD_RD_REQ 0x01
#define STANDARD_WR_REQ 0x81

#define QUERY_RESPONSE_HEAD_OFFSET 32
#define QUERY_RESPONSE_DATA_OFFSET 2

#define UTP_UFS_STORAGE_COMMAND    (1 << 4)

enum info_show_type {
	UFS_INFO_SHOW_DEVICE_DESC        = 0x00,
	UFS_INFO_SHOW_CONFIGURATION_DESC = 0x01,
	UFS_INFO_SHOW_UNIT_DESC          = 0x02,
	UFS_INFO_SHOW_INTERCONNECT_DESC  = 0x04,
	UFS_INFO_SHOW_STRING_DESC        = 0x05,
	UFS_INFO_SHOW_GEOMETRY_DESC      = 0x07,
	UFS_INFO_SHOW_HEALTH_DESC        = 0x09,
	UFS_INFO_SHOW_ALL                = 0x0E,
	UFS_INFO_SHOW_BASIC              = 0x0F,
};

/*
 * UFS Status/Error Macros used as return values for all functions
 */
enum {
	UFS_SUCCESS			=  0x00,
	UFS_FAILURE			= -0x01,
	UFS_LINK_STARTUP_FAIL		= -0x02,
	UFS_UTRD_DOORBELL_TIMEOUT	= -0x03,
	UFS_NOP_RESP_FAIL		= -0x04,
	UFS_INVALID_NOP_IN		= -0x05,
	UFS_UTMRD_DOORBELL_TIMEOUT	= -0x06,
	UFS_FDEVICE_INIT_FAIL		= -0x07,

	UFS_SOFTWARE_ERROR		= -0x0F,

	/* response upiu status error */
	RESP_STAT_CONDITION_MET		= -0x14,
	RESP_STAT_BUSY			= -0x15,
	RESP_STAT_RESERVATION_CONFLICT	= -0x16,
	RESP_STAT_TASK_SET_FULL		= -0x17,
	RESP_STAT_ACA_ACTIVE		= -0x18,
	RESP_STAT_TASK_ABORTED		= -0x19,
	RESP_STAT_UNKNOWN		= -0x1F,

#define RET_SENSE_KEY_OFF			(0x20)
	/* sense key */
	NO_SENSE                        = -0x20,
	RECOVERED_ERROR                 = -0x21,
	NOT_READY                       = -0x22,
	MEDIUM_ERROR                    = -0x23,
	HARDWARE_ERROR                  = -0x24,
	ILLEGAL_REQUEST                 = -0x25,
	UNIT_ATTENTION                  = -0x26,
	DATA_PROTECT                    = -0x27,
	BLANK_CHECK                     = -0x28,
	VENDOR_SPECIFIC                 = -0x29,
	ABORTED_COMMAND                 = -0x2B,
	VOLUME_OVERFLOW                 = -0x2D,
	MISCOMPARE                      = -0x2E,

	/* RPMB Operation Results */
	UFS_RPMB_GENERAL_FAILURE        = -0x31,
	UFS_AUTHENTICATION_FAILURE      = -0x32,
	UFS_COUNTER_FAILURE             = -0x33,
	UFS_ADDRESS_FAILURE             = -0x34,
	UFS_WRITE_FAILURE               = -0x35,
	UFS_READ_FAILURE                = -0x36,
	UFS_AUTH_KEY_NOT_PROGRAMMED     = -0x37,
	UFS_RPMB_WR_COUNTER_EXPIRED     = -0x38,
	UFS_NONCE_MISMATCH              = -0x39,
	UFS_MAC_MISMATCH                = -0x3a,

#define RET_UIC_CONFIG_ERROR_OFF		(0xA0)
	/* UIC Config Result Error */
	UFS_UIC_TIMEOUT			= -0xA0,
	INVALID_MIB_ATTRIBUTE		= -0xA1,
	INVALID_MIB_ATTRIBUTE_VALUE	= -0xA2,
	READ_ONLY_MIB_ATTRIBUTE		= -0xA3,
	WRITE_ONLY_MIB_ATTRIBUTE	= -0xA4,
	BAD_INDEX			= -0xA5,
	LOCKED_MIB_ATTRIBUTE		= -0xA6,
	BAD_TEST_FEATURE_INDEX		= -0xA7,
	PEER_COMMUNICATION_FAILURE	= -0xA8,
	BUSY				= -0xA9,
	DME_FAILURE			= -0xAA,

#define RET_UTRD_OCS_ERROR_OFF			(0xB0)
	/* utrd ocs error */
	INVALID_COMMAND_TABLE_ATTRIBUTES = -0xB1,
	INVALID_PRDT_ATTRIBUTES          = -0xB2,
	MISMATCH_DATA_BUFFER_SIZE        = -0xB3,
	MISMATCH_RESPONSE_UPIU_SIZE      = -0xB4,
	COMMUNICATION_FAILURE            = -0xB5,
	ABORTED                          = -0xB6,
	FATAL_ERROR                      = -0xB7,
	INVALID_OCS_VALUE                = -0xBF,

	/* Query response code */
	QUERY_PARAMETER_NOT_READABLE	= -0xF6,
	QUERY_PARAMETER_NOT_WRITEABLE	= -0xF7,
	QUERY_PARAMETER_ALREADY_WRITTEN	= -0xF8,
	QUERY_INVALID_LENGTH		= -0xF9,
	QUERY_INVALID_VALUE		= -0xFA,
	QUERY_INVALID_SELECTOR		= -0xFB,
	QUERY_INVALID_INDEX		= -0xFC,
	QUERY_INVALID_IDN		= -0xFD,
	QUERY_INVALID_OPCODE		= -0xFE,
	QUERY_GENERAL_FAILURE		= -0xFF
};

/* DME Commands */
enum {
	DWC_UFS_DME_GET = 0x01,
	DWC_UFS_DME_SET = 0x02,
	DWC_UFS_DME_PEER_GET = 0x03,
	DWC_UFS_DME_PEER_SET = 0x04,
	DWC_UFS_DME_POWERON = 0x10,
	DWC_UFS_DME_POWEROFF = 0x11,
	DWC_UFS_DME_ENABLE = 0x12,
	DWC_UFS_DME_RESET = 0x14,
	DWC_UFS_DME_ENDPOINTRESET = 0x15,
	DWC_UFS_DME_LINKSTARTUP = 0x16,
	DWC_UFS_DME_HIBERNATE_ENTER = 0x17,
	DWC_UFS_DME_HIBERNATE_EXIT = 0x18,
	DWC_UFS_DME_TEST_MODE = 0x1A,
};

/* DME Result Codes */
enum {
	DWC_UFS_DME_SUCCESS = 0x00,
	DWC_UFS_DME_INV_MIB_ATTR = 0x01,
	DWC_UFS_DME_INV_MIB_ATTR_VAL = 0x02,
	DWC_UFS_DME_READ_ONLY_MIB_ATTR = 0x03,
	DWC_UFS_DME_WRITE_ONLY_MIB_ATTR = 0x04,
	DWC_UFS_DME_BAD_INDEX = 0x05,
	DWC_UFS_DME_LOCKED_MIB_ATTR = 0x06,
	DWC_UFS_DME_BAD_TEST_FEAT_INDEX = 0x07,
	DWC_UFS_DME_PEER_COMM_FAILURE = 0x08,
	DWC_UFS_DME_BUSY = 0x09,
	DWC_UFS_DME_FAILURE = 0x0a,

	DWC_UFS_DME_RESULT_CODE_MASK = 0xff,
};

/* UTP Transfer Request Data Direction (DD) */
enum {
	UTP_NO_DATA_TRANSFER = 0x00,
	UTP_HOST_TO_DEVICE = 0x02,
	UTP_DEVICE_TO_HOST = 0x04
};

/* UPIU Read/Write flags */
enum {
	UPIU_CMD_FLAGS_NONE = 0x00,
	UPIU_CMD_FLAGS_WRITE = 0x20,
	UPIU_CMD_FLAGS_READ = 0x40
};

enum flags_id {
	FDEVICE_INIT = 0x1,
	FPERMANANT_WPEN = 0x2,
	FPOWERON_WPEN = 0x3,
	FBG_OPSEN = 0x4,
	FPURGE_OPSEN = 0x6,
	FPHYRES_REMOVAL = 0x8,
	FBUSY_RTC = 0x9
};

/* use for unipro & M-PHY 's configuration and control */
enum uic_dme_type {
	/* Configuration */
	DME_GET = 0x01,
	DME_SET = 0x02,
	DME_PEER_GET = 0x03,
	DME_PEER_SET = 0x04,
	/* Control */
	DME_POWERON = 0x10,
	DME_POWEROFF = 0x11,
	DME_ENABLE = 0x12,

	DME_RESERVE_1 = 0x13,
	DME_RESET = 0x14,
	DME_ENDPOINTRESET = 0x15,
	DME_LINKSTARTUP = 0x16,
	DME_HIBERNATE_ENTER = 0x17,
	DME_HIBERNATE_EXIT = 0x18,
	DME_RESERVE_2 = 0x19,
	DME_TEST_MODE = 0x1A,
};

enum attr_id {
	B_BOOT_LUNEN = 0x0,
	B_CURRENT_PM = 0x2,
	B_ACTIV_ICC_LEVEL = 0x3,
	B_OUT_OF_ORDER_DATAEN = 0x4,
	B_BCKGND_OPS_STATUS = 0x5,
	B_PURGE_STATUS = 0x6,
	B_MAX_DATA_IN_SIZE = 0x7,
	B_MAX_DATA_OUT_SIZE = 0x8,
	D_DYN_CAP_NEEDED = 0x9,
	B_REFCLK_FREQ = 0xA,
	B_CONFIG_DESC_LOCK = 0xB,
	B_MAX_NUM_OF_RTT = 0xC,
	W_EXCEPTION_EVENT_CONTROL = 0xD,
	W_EXCEPTION_EVENT_STATUS = 0xE,
	D_SECONDS_PASSED = 0xF,
	W_CONTEXT_CONF = 0x10,
	D_CORR_PRG_BLKNUM = 0x11
};

struct ufs {
	uint64_t capacity;
	unsigned long long blocksize;
	int (*block_read)(uint64_t dest_addr, uint64_t src_offset, uint32_t lenth);
	int (*block_write)(uint64_t src_addr, uint64_t dest_offset, uint32_t lenth);
	int (*boot_block_write)(uint64_t src_addr, uint64_t dest_offset, uint32_t lenth);
};

unsigned int *ufs_pack_cid(void);
struct ufs *get_ufs_info(void);
int ufs_read_capacity(uint32_t *lba);

int ufs_set_bootlun(uint8_t lun);
int ufs_set_active_lun(uint8_t lun);

int ufs_read_boot_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size);
int ufs_write_boot_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size);

int ufs_read_storage(uint64_t dest_addr, uint64_t src_offset, uint32_t size);
int ufs_write_storage(uint64_t src_addr, uint64_t dest_offset, uint32_t size);
void send_uic_command(uint32_t command, uint32_t arg1, uint32_t arg2, uint32_t arg3);
uint32_t uic_cmd_read(uint32_t command, uint32_t arg1);
void ufs_readreg_all(void);

int ufs_set_flag(enum flags_id idn, uint8_t *flags_ret);
int ufs_read_flag(enum flags_id idn, uint8_t *flags_ret);

int read_descriptor(const void *req_upiu, void **resp_upiu);
int write_descriptor(const void *req_upiu);

int read_attribute(enum attr_id idn, uint8_t indexx, uint8_t selector, uint32_t *ret_value);
int write_attribute(enum attr_id idn, uint8_t indexx, uint8_t selector, uint32_t *value);

int ufs_storage_init(void);

int ufs_hibernate_exit(void);
int ufs_hibernate_enter(void);

int do_mode_change(const struct pwr_mode_params *pmp);
int ufs_show_desc_info(enum info_show_type type);

void modify_desc_upiu(const struct desc_params *params);
void ufs_reg_dump(void);
void ufs_reinit(void);
#ifdef CONFIG_EXT4_SPARSE
int ufs_ext4_unsparse(const u8 *pbuf, u32 blk, u32 cnt);
#endif
#endif
#endif
