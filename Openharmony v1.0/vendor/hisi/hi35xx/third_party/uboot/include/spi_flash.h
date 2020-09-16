/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Common SPI flash Interface
 *
 * Copyright (C) 2008 Atmel Corporation
 * Copyright (C) 2013 Jagannadha Sutradharudu Teki, Xilinx Inc.
 */

#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_

#include <dm.h>	/* Because we dereference struct udevice here */
#include <linux/types.h>
#include <linux/mtd/spi-nor.h>
#include <spi.h>

#ifdef CONFIG_SPI_BLOCK_PROTECT
#define BP_OP_SET	0
#define BP_OP_GET	1

#define BT_LOC_RDSR	0
#define BT_LOC_RDCR	1

#define BP_CMP_TOP      0
#define BP_CMP_BOTTOM   1
#define BP_CMP_UPDATE_FLAG      0xff

enum block_protection_level {
	BP_LEVEL_0      = 0,
	BP_LEVEL_1      = 1,
	BP_LEVEL_2      = 2,
	BP_LEVEL_3      = 3,
	BP_LEVEL_4      = 4,
	BP_LEVEL_5      = 5,
	BP_LEVEL_6      = 6,
	BP_LEVEL_7      = 7,
	BP_LEVEL_8      = 8,
	BP_LEVEL_9      = 9,
	BP_LEVEL_10     = 10,
	BP_LEVEL_END,
};

#define BP_LEVEL_MAX    (BP_LEVEL_END - 1)

#define BP_NUM_3	3
#define BP_NUM_4	4
#define BP_NUM_5	5

void spi_flash_lock(unsigned char cmp, unsigned char level, unsigned char op);

#endif /* CONFIG_SPI_BLOCK_PROTECT */

#define MID_SPANSION    0x01    /* Spansion Manufacture ID */
#define MID_WINBOND     0xef    /* Winbond  Manufacture ID */
#define MID_MXIC        0xc2    /* MXIC Manufacture ID */
#define MID_MICRON      0x20    /* Micron Manufacture ID */
#define MID_GD          0xc8    /* GD Manufacture ID */
#define MID_ESMT        0x8c    /* ESMT Manufacture ID */
#define MID_CFEON       0x1c    /* CFeon Manufacture ID */
#define MID_MICRON      0x20    /* Micron Manufacture ID */
#define MID_PARAGON     0xe0    /* Paragon Manufacture ID */


#ifndef CONFIG_SF_DEFAULT_SPEED
# define CONFIG_SF_DEFAULT_SPEED	1000000
#endif
#ifndef CONFIG_SF_DEFAULT_MODE
# define CONFIG_SF_DEFAULT_MODE		SPI_MODE_3
#endif
#ifndef CONFIG_SF_DEFAULT_CS
# define CONFIG_SF_DEFAULT_CS		0
#endif
#ifndef CONFIG_SF_DEFAULT_BUS
# define CONFIG_SF_DEFAULT_BUS		0
#endif

/* by default ENV use the same parameters than SF command */
#ifndef CONFIG_ENV_SPI_BUS
# define CONFIG_ENV_SPI_BUS	CONFIG_SF_DEFAULT_BUS
#endif
#ifndef CONFIG_ENV_SPI_CS
# define CONFIG_ENV_SPI_CS	CONFIG_SF_DEFAULT_CS
#endif
#ifndef CONFIG_ENV_SPI_MAX_HZ
# define CONFIG_ENV_SPI_MAX_HZ	CONFIG_SF_DEFAULT_SPEED
#endif
#ifndef CONFIG_ENV_SPI_MODE
# define CONFIG_ENV_SPI_MODE	CONFIG_SF_DEFAULT_MODE
#endif

struct spi_slave;

struct dm_spi_flash_ops {
	int (*read)(struct udevice *dev, u32 offset, size_t len, void *buf);
	int (*write)(struct udevice *dev, u32 offset, size_t len,
		     const void *buf);
	int (*erase)(struct udevice *dev, u32 offset, size_t len);
	/**
	 * get_sw_write_prot() - Check state of software write-protect feature
	 *
	 * SPI flash chips can lock a region of the flash defined by a
	 * 'protected area'. This function checks if this protected area is
	 * defined.
	 *
	 * @dev:	SPI flash device
	 * @return 0 if no region is write-protected, 1 if a region is
	 *	write-protected, -ENOSYS if the driver does not implement this,
	 *	other -ve value on error
	 */
	int (*get_sw_write_prot)(struct udevice *dev);
};

/* Access the serial operations for a device */
#define sf_get_ops(dev) ((struct dm_spi_flash_ops *)(dev)->driver->ops)

#ifdef CONFIG_DM_SPI_FLASH
/**
 * spi_flash_read_dm() - Read data from SPI flash
 *
 * @dev:	SPI flash device
 * @offset:	Offset into device in bytes to read from
 * @len:	Number of bytes to read
 * @buf:	Buffer to put the data that is read
 * @return 0 if OK, -ve on error
 */
int spi_flash_read_dm(struct udevice *dev, u32 offset, size_t len, void *buf);

/**
 * spi_flash_write_dm() - Write data to SPI flash
 *
 * @dev:	SPI flash device
 * @offset:	Offset into device in bytes to write to
 * @len:	Number of bytes to write
 * @buf:	Buffer containing bytes to write
 * @return 0 if OK, -ve on error
 */
int spi_flash_write_dm(struct udevice *dev, u32 offset, size_t len,
		       const void *buf);

/**
 * spi_flash_erase_dm() - Erase blocks of the SPI flash
 *
 * Note that @len must be a muiltiple of the flash sector size.
 *
 * @dev:	SPI flash device
 * @offset:	Offset into device in bytes to start erasing
 * @len:	Number of bytes to erase
 * @return 0 if OK, -ve on error
 */
int spi_flash_erase_dm(struct udevice *dev, u32 offset, size_t len);

/**
 * spl_flash_get_sw_write_prot() - Check state of software write-protect feature
 *
 * SPI flash chips can lock a region of the flash defined by a
 * 'protected area'. This function checks if this protected area is
 * defined.
 *
 * @dev:	SPI flash device
 * @return 0 if no region is write-protected, 1 if a region is
 *	write-protected, -ENOSYS if the driver does not implement this,
 *	other -ve value on error
 */
int spl_flash_get_sw_write_prot(struct udevice *dev);

int spi_flash_probe_bus_cs(unsigned int busnum, unsigned int cs,
			   unsigned int max_hz, unsigned int spi_mode,
			   struct udevice **devp);

/* Compatibility function - this is the old U-Boot API */
struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
				  unsigned int max_hz, unsigned int spi_mode);

/* Compatibility function - this is the old U-Boot API */
void spi_flash_free(struct spi_flash *flash);

static inline int spi_flash_read(struct spi_flash *flash, u32 offset,
				 size_t len, void *buf)
{
	return spi_flash_read_dm(flash->dev, offset, len, buf);
}

static inline int spi_flash_write(struct spi_flash *flash, u32 offset,
				  size_t len, const void *buf)
{
	return spi_flash_write_dm(flash->dev, offset, len, buf);
}

static inline int spi_flash_erase(struct spi_flash *flash, u32 offset,
				  size_t len)
{
	return spi_flash_erase_dm(flash->dev, offset, len);
}

struct sandbox_state;

int sandbox_sf_bind_emul(struct sandbox_state *state, int busnum, int cs,
			 struct udevice *bus, ofnode node, const char *spec);

void sandbox_sf_unbind_emul(struct sandbox_state *state, int busnum, int cs);

#else
struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int spi_mode);

void spi_flash_free(struct spi_flash *flash);

static inline int spi_flash_read(struct spi_flash *flash, u32 offset,
		size_t len, void *buf)
{
#ifndef CONFIG_HIFMC
	struct mtd_info *mtd = &flash->mtd;
	size_t retlen;

	return mtd->_read(mtd, offset, len, &retlen, buf);
#else
	return flash->read(flash, offset, len, buf);
#endif
}

static inline int spi_flash_write(struct spi_flash *flash, u32 offset,
		size_t len, const void *buf)
{
#ifndef CONFIG_HIFMC
	struct mtd_info *mtd = &flash->mtd;
	size_t retlen;

	return mtd->_write(mtd, offset, len, &retlen, buf);
#else
	return flash->write(flash, offset, len, buf);
#endif
}

static inline int spi_flash_erase(struct spi_flash *flash, u32 offset,
		size_t len)
{
#ifndef CONFIG_HIFMC
	struct mtd_info *mtd = &flash->mtd;
	struct erase_info instr;

	if (offset % mtd->erasesize || len % mtd->erasesize) {
		printf("SF: Erase offset/length not multiple of erase size\n");
		return -EINVAL;
	}

	memset(&instr, 0, sizeof(instr));
	instr.addr = offset;
	instr.len = len;

	return mtd->_erase(mtd, &instr);
#else
#ifndef CONFIG_HIFMC_NAND
	extern int hifmc100_reg_erase(struct spi_flash *spiflash, u_int offset,
				size_t length);
	return hifmc100_reg_erase(flash, offset, len);
#else
	return 0;
#endif
#endif
}
#endif

static inline int spi_flash_protect(struct spi_flash *flash, u32 ofs, u32 len,
					bool prot)
{
	if (!flash->flash_lock || !flash->flash_unlock)
		return -EOPNOTSUPP;

	if (prot)
		return flash->flash_lock(flash, ofs, len);
	else
		return flash->flash_unlock(flash, ofs, len);
}

#endif /* _SPI_FLASH_H_ */
