#ifndef __ONCHIPROM_KIRIN_UFS_H__
#define __ONCHIPROM_KIRIN_UFS_H__

/*#define UFS_FPGA*/

#define COMBO_PHY_V120

#define DELAY_US        (1000)

#ifndef UFS_FPGA
#define REG_BASE_UFS_ADDRESS 0x10010000
#else
#define REG_BASE_UFS_ADDRESS 0x113a0000
#endif

#ifdef UFS_FPGA
#define REG_BASE_FPGA2_APB_IF_ADDRESS 0x113f7000
#define UFS_CTRL1   0x0000
#define UFS_CTRL2   0x0004
#define UFS_CTRL3   0x0008
/*UFS_CTRL1*/
#define RX_SYMBOLCLK_SEL        (0x1 << 25)
#define RX_SYMBOLCLK1_SEL       (0x1 << 24)
/*UFS_CTRL2*/
#define TX_SYMBOLCLK_SEL        (0x1 << 8)
#define UFS_CLK_EN          (0x1 << 1)
#define UFS_SRST_REQ            (0x1 << 0)
/*UFS_CTRL3*/
#define UFS_RST                 (0x1 << 31)
#define I2C_SCL                 (0x1 << 21)
#define I2C_SDA                 (0x1 << 20)
#define IF_AMUX_SEL             (0x1 << 17)
#define UFS_SEL                 (0x1 << 16)
#endif

#define UFS_SYS_PSW_POWER_CTRL      (REG_BASE_UFS_SYS + 0x04)
#define UFS_SYS_PHY_ISO_EN          (REG_BASE_UFS_SYS + 0x08)
#define UFS_SYS_HC_LP_CTRL          (REG_BASE_UFS_SYS + 0x0C)
#define UFS_SYS_PHY_CLK_CTRL        (REG_BASE_UFS_SYS + 0x10)
#define UFS_SYS_PSW_CLK_CTRL        (REG_BASE_UFS_SYS + 0x14)
#define UFS_SYS_CLOCK_GATE_BYPASS   (REG_BASE_UFS_SYS + 0x18)
#define UFS_SYS_RESET_CTRL_EN       (REG_BASE_UFS_SYS + 0x1C)
#define UFS_SYS_UFS_SYSCTRL         (REG_BASE_UFS_SYS + 0x5C)
#define UFS_SYS_UFS_DEVICE_RESET_CTRL   (REG_BASE_UFS_SYS + 0x60)

#define BIT_UFS_PSW_ISO_CTRL        (1 << 16)
#define BIT_UFS_PSW_MTCMOS_EN       (1 << 0)
#define BIT_UFS_REFCLK_ISO_EN       (1 << 16)
#define BIT_UFS_PHY_ISO_CTRL        (1 << 0)
#define BIT_SYSCTRL_LP_ISOL_EN      (1 << 16)
#define BIT_SYSCTRL_PWR_READY       (1 << 8)
#define BIT_SYSCTRL_REF_CLOCK_EN    (1 << 24)
#define MASK_SYSCTRL_REF_CLOCK_SEL  (0x3 << 8)
#define MASK_SYSCTRL_CFG_CLOCK_FREQ (0xFF)
#define UFS_FREQ_CFG_CLK            (0x14)
#define BIT_SYSCTRL_PSW_CLK_EN      (1 << 4)
#define MASK_UFS_CLK_GATE_BYPASS    (0x3F)
#define BIT_SYSCTRL_LP_RESET_N      (1 << 0)
#define BIT_UFS_REFCLK_SRC_SEl      (1 << 0)
#define MASK_UFS_SYSCRTL_BYPASS     (0x3F << 16)
#define MASK_UFS_DEVICE_RESET       (0x1 << 16)
#define BIT_UFS_DEVICE_RESET        (0x1)

/* UFSHCD Registers Offsets */
#define UFS_CAP_OFF             0x00
#define UFS_VER_OFF             0x08
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
#define UFS_UTRLBA_OFF          0x50
#define UFS_UTRLBAU_OFF         0x54
#define UFS_UTRLDBR_OFF         0x58
#define UFS_UTRLCLR_OFF         0x5C
#define UFS_UTRLRSR_OFF         0x60
#define UFS_UTMRLBA_OFF         0x70
#define UFS_UTMRLBAU_OFF        0x74
#define UFS_UTMRLDBR_OFF        0x78
#define UFS_UTMRLRSR_OFF        0x80
#define UFS_UICCMD_OFF          0x90
#define UFS_UICCMDARG1_OFF      0x94
#define UFS_UICCMDARG2_OFF      0x98
#define UFS_UICCMDARG3_OFF      0x9C
#define UFS_LBMCFG_OFF          0xF0
#define UFS_HCLKDIV_OFF         0xFC

#define UFS_HCE_RESET_BIT       (1 << 0)
#define UFS_HCS_UCRDY_BIT       (1 << 3)
#define UFS_HCS_DP_BIT          (1 << 0)
#define UFS_IS_UE_BIT           (1 << 2)
#define UFS_IS_ULSS_BIT         (1 << 8)
#define UFS_IS_UCCS_BIT         (1 << 10)
#define UFS_UICCMDARG2_RET_MASK (0xFF)
#define UFS_AHIT_AH8ITV_MASK    (0x2FF)
#define UFS_UTP_RUN_BIT         (1 << 0)

#define UFS_HCLKDIV_NORMAL_VALUE    0x12C
#ifdef UFS_FPGA
#define UFS_HCLKDIV_FPGA_VALUE      (0x28)
#else
#define UFS_HCLKDIV_SLOW_VALUE      (0x14)
#endif

#define UIC_LINK_STARTUP_CMD        0x16
#define NOP_TRANS_TYPE          0x20

#define UFS_BOOT_LUN            0xB0

//#define DEBUG_UFS
#ifdef DEBUG_UFS
#define debug_printf(fmt,args...)   printf (fmt ,##args)
#else
#define debug_printf(fmt,args...)
#endif

#define UFS_HC_INIT_TIMEOUT_MS          1000
#define UFS_HC_ENABLE_TIMEOUT_MS        1
#define UFS_LINK_STARTUP_TIMEOUT_MS     200
#define UFS_HC_WAIT_UCRDY_TIMEOUT_MS    1
#define UFS_HC_WAIT_ULSS_TIMEOUT_MS     50
#define UFS_SEND_UIC_CMD_TIMEOUT_MS     10
#define UFS_READ_UIC_CMD_TIMEOUT_MS     10
#define UFS_SEND_NOP_OUT_TIMEOUT_MS     10

/* Byte swap u16*/
static inline uint16_t swap_16(uint16_t val)
{
	return (uint16_t)((val << 8) | (val >> 8));
}

/* Byte swap unsigned int */
static inline uint32_t swap_32(uint32_t val)
{

	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
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
static inline uint32_t dwc_ufs_read_reg(uint32_t reg_offset)
{
	uint32_t value;

	value = (*((volatile uint32_t *)(long)(REG_BASE_UFS_ADDRESS + reg_offset)));
	return value;
}

static inline void dwc_ufs_write_reg(uint32_t reg_offset, uint32_t value)
{
	(*((volatile uint32_t *)(long)(REG_BASE_UFS_ADDRESS + reg_offset))) = value;
}

enum uic_dme_type {
	/*Configuration */
	DME_GET = 0x01,
	DME_SET = 0x02,
	DME_PEER_GET = 0x03,
	DME_PEER_SET = 0x04,
	/*Control */
	DME_POWERON = 0x10,
	DME_POWEROFF = 0x11,
	DME_ENABLE = 0x12,

	DME_Reserve_1 = 0x13,
	DME_RESET = 0x14,
	DME_ENDPOINTRESET = 0x15,
	DME_LINKSTARTUP = 0x16,
	DME_HIBERNATE_ENTER = 0x17,
	DME_HIBERNATE_EXIT = 0x18,
	DME_Reserve_2 = 0x19,
	DME_TEST_MODE = 0x1A,
};

enum {
	UFS_SUCCESS         =  0x00,
	UFS_LINK_STARTUP_FAIL       = -0x02,
	UFS_UTRD_DOORBELL_TIMEOUT   = -0x03,
	UFS_NOP_RESP_FAIL       = -0x04,
	UFS_INVALID_NOP_IN      = -0x05,

	/* response upiu status error */
	RESP_STAT_CONDITION_MET     = -0x14,
	RESP_STAT_BUSY          = -0x15,
	RESP_STAT_RESERVATION_CONFLICT  = -0x16,
	RESP_STAT_TASK_SET_FULL     = -0x17,
	RESP_STAT_ACA_ACTIVE        = -0x18,
	RESP_STAT_TASK_ABORTED      = -0x19,
	RESP_STAT_UNKNOW        = -0x1F,

#define RET_SENSE_KEY_OFF           (0x20)
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

#define RET_UIC_CONFIG_ERROR_OFF        (0xA0)
	/* UIC Config Result Error */
	UFS_UIC_TIMEOUT         = -0xA0,
	INVALID_MIB_ATTRIBUTE       = -0xA1,
	INVALID_MIB_ATTRIBUTE_VALUE = -0xA2,
	READ_ONLY_MIB_ATTRIBUTE     = -0xA3,
	WRITE_ONLY_MIB_ATTRIBUTE    = -0xA4,
	BAD_INDEX           = -0xA5,
	LOCKED_MIB_ATTRIBUTE        = -0xA6,
	BAD_TEST_FEATURE_INDEX      = -0xA7,
	PEER_COMMUNICATION_FAILURE  = -0xA8,
	BUSY                = -0xA9,
	DME_FAILURE         = -0xAA,

#define RET_UTRD_OCS_ERROR_OFF          (0xB0)
	/* utrd ocs error */
	INVALID_COMMAND_TABLE_ATTRIBUTES = -0xB1,
	INVALID_PRDT_ATTRIBUTES          = -0xB2,
	MISMATCH_DATA_BUFFER_SIZE        = -0xB3,
	MISMATCH_RESPONSE_UPIU_SIZE      = -0xB4,
	COMMUNICATION_FAILURE            = -0xB5,
	ABORTED                          = -0xB6,
	FATAL_ERROR                      = -0xB7,
	INVALID_OCS_VALUE                = -0xBF,

	UFS_SOFTWARE_ERROR       = -0xFF
};

#define UFS_STATIC_WORK_SPACE_ADDRESS ufsboot_static_space_address
/* DDR address */
#define UFS_START_WORK_SPACE_START  0x50000000
#define UFS_STATIC_WORK_SPACE_SIZE  0x2000

#define UFS_CMD_UPIU_BASE   (UFS_STATIC_WORK_SPACE_ADDRESS + 0x0)
#define UFS_RESP_UPIU_BASE  (UFS_STATIC_WORK_SPACE_ADDRESS + 0x200)
#define UFS_PRDT_BASE       (UFS_STATIC_WORK_SPACE_ADDRESS + 0x400)
#define UFS_TR_UTP_BASE     (UFS_STATIC_WORK_SPACE_ADDRESS + 0x800)
#define UFS_TMR_UTP_BASE    (UFS_STATIC_WORK_SPACE_ADDRESS + 0xC00)
#define STATIC_UFS_TAG_ADDR (UFS_STATIC_WORK_SPACE_ADDRESS + 0x1000)

#define MAX_TR_TASK     32
#define MAX_PRDT_ENTRIES    64
#define PRDT_BUFFER_SIZE    0x40000
#define LOGICAL_BLK_SIZE    4096
//#define LPRAM_ADDR_FROM_LPM3_TO_CPU(x)    ((x) - REG_BASE_LP_RAM + REG_BASE_LP_RAM_ACORE)
#define LPRAM_ADDR_FROM_LPM3_TO_CPU(x)  ((x))

#define BYTES_ALIGN_1024(x)  ((x + 1024 -1)& ~(1024 - 1))
#define BYTES_ALIGN_4096(x)  ((x + 4096 -1)& ~(4096 - 1))

#pragma pack(push)
#pragma pack(1)

#define write_error_code(c)

static inline void ufs_memset(void* mem, uint8_t val, uint32_t size)
{
	uint8_t *pf8 = (uint8_t*)mem;
	uint32_t i;

	for (i = 0; i < size; i++) {
		pf8[i] = val;
		pf8++;
	}
}

static inline void delay(unsigned int cnt)
{
	while (cnt--) {
		__asm__ __volatile__("nop");
	}
}

static inline void ufs_waitus(uint32_t us)
{
	while (us--) {
		delay(DELAY_US);
	}
}

static inline void ufs_waitms(uint32_t ms)
{
	while (ms--) {
		delay(1000 * DELAY_US);
	}
}

static uint32_t ufs_cur_time_ms = 0;
static inline uint32_t current_time(void)
{
	ufs_cur_time_ms = 0;
	return ufs_cur_time_ms;
}

static inline uint32_t time_passed_ms(uint32_t last)
{
	delay(1000 * DELAY_US);
	ufs_cur_time_ms++;
	return  ufs_cur_time_ms;
}

/*
 * Command UPIU Structure
 */
struct dwc_ufs_cmd_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;   /* Only LS nibble is valid. Others Reserved */
	uint8_t reserved_1_0;
	uint8_t reserved_1_1;
	uint8_t reserved_1_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_2;
	uint16_t data_seg_len;
	uint32_t exp_data_xfer_len;
	uint8_t cdb[16];        /* UFS/SCSI command descriptor block */
};

/*
 * Transfer Response UPIU Structure
 */
struct dwc_ufs_xfer_resp_upiu {
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;   /* Only LS nibble is valid. Others Reserved */
	uint8_t reserved_1;
	uint8_t response;
	uint8_t status;     /* This is SCSI status */
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint32_t residual_xfer_count;
	uint32_t reserved_2;
	uint32_t reserved_3;
	uint32_t reserved_4;
	uint32_t reserved_5;
	uint16_t sense_data_len;
	uint8_t sense_data[18];
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
	uint8_t reserved_4[20];
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
	uint8_t reserved_4[20];
};

struct dwc_ufs_prd {
	uint32_t    base_addr;
	uint32_t    upper_addr;
	uint32_t    reserved1;
	uint32_t    size;
};

struct dwc_ufs_utrd {
	uint8_t reserved_1_0        : 8;
	uint8_t reserved_1_1        : 8;
	uint8_t reserved_1_2        : 8;
	uint8_t ct_and_flags        : 8;
	uint32_t reserved_2     : 32;
	uint8_t ocs         : 8;
	uint8_t reserved_3_0        : 8;
	uint8_t reserved_3_1        : 8;
	uint8_t reserved_3_2        : 8;
	uint32_t reserved_4     : 32;

	uint32_t ucdba          : 32; /* Only bits 31:7 are valid; 128B Aligned addr */
	uint32_t ucdbau         : 32;
	uint16_t resp_upiu_length   : 16;
	uint16_t resp_upiu_offset   : 16;

	uint16_t prdt_length        : 16;
	uint16_t prdt_offset        : 16;
};

#pragma pack(pop)

/* UTP Transfer Request Data Direction (DD) */
enum {
	UTP_NO_DATA_TRANSFER    = 0x00,
	UTP_HOST_TO_DEVICE  = 0x02,
	UTP_DEVICE_TO_HOST  = 0x04
};

/* UPIU Read/Write flags */
enum {
	UPIU_CMD_FLAGS_NONE = 0x00,
	UPIU_CMD_FLAGS_WRITE    = 0x20,
	UPIU_CMD_FLAGS_READ = 0x40
};

enum {
	UTP_SCSI_COMMAND        = 0x00,
};

enum {
	UTP_UFS_STORAGE_COMMAND     = (1 << 4)
};

enum dma_data_direction {
	DMA_FROM_DEVICE   = 2,
	DMA_NONE          = 3
};

#endif

