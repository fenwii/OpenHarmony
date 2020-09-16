
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* fpga memory map */
#define REG_BASE_EMMC0                0xBF3FB000

#define REG_BASE_USB_OTG              0x10180000
#define REG_BASE_USB_OTG_BC           0XBF200000
#define REG_BASE_LP_RAM               0x00020000

#define REG_BASE_UFS_SYS              0xBF3B1000
#define REG_BASE_UFS                  0xBF3B0000

#define REG_BASE_PCTRL                0xA8A09000
#define REG_BASE_IOC                  0xA896C000
#define REG_BASE_PMC                  0x40231000
#define REG_BASE_UART6                0x40232000
#define REG_BASE_PERI_CRG             0x40235000
#define REG_BASE_LP_TIMER             0x4023E000
#define REG_BASE_SCTRL                0x4020A000
#define REG_BASE_AO_IOC               0x40211000

#define REG_BASE_GPIO			0xA8A0B000	/* GPIO0~21 */
#define REG_GPIO(x)			(REG_BASE_GPIO + (0x1000 * (x)))
#define REG_GPIO22			0x4020B000

#define LP_RAM_SIZE                   (96*1024)

#define REG_BASE_LP_RAM_ACORE         0xFFF50000

#endif /* end of __PLATFORM_H__ */


