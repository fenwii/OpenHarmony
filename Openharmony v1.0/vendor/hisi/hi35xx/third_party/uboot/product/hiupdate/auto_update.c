/*
 * auto_update.c
 *
 * Description:Read the image from the external storage medium SD or USB and
 * burn it to the board storage medium.
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
#include <environment.h>
#include <command.h>
#include <malloc.h>
#include <image.h>
#include <asm/byteorder.h>
#include <asm/io.h>
#include <spi_flash.h>
#include <linux/mtd/mtd.h>
#include <fat.h>

#if (CONFIG_AUTO_UPDATE == 1)  /* cover the whole file */

#ifdef CONFIG_AUTO_SD_UPDATE
#ifndef CONFIG_MMC
#error "should have defined CONFIG_MMC"
#endif
#include <mmc.h>
#include "mmc_init.c"
#endif

#if defined CONFIG_AUTO_USB_UPDATE
#if !defined CONFIG_USB_OHCI && !defined CONFIG_USB_XHCI
#error "should have defined CONFIG_USB_OHCI or CONFIG_USB_XHCI"
#endif
#ifndef CONFIG_USB_STORAGE
#error "should have defined CONFIG_USB_STORAGE"
#endif
#include <usb.h>
#include "usb_init.c"
#endif

#undef AU_DEBUG
#undef debug
#ifdef  AU_DEBUG
#define debug(fmt, args...) printf(fmt, ##args)
#else
#define debug(fmt, args...)
#endif  /* AU_DEBUG */

/* possible names of files on the medium. */
#define AU_FIRMWARE "u-boot"
#define AU_KERNEL   "kernel"
#define AU_ROOTFS   "rootfs"

#define NAME_LEN	20
#define ENV_LEN		20
#define PERCENT		100
#define HEX		16
#define COUNT		3
#define MMC2		2
#define MAX_HZ		1000000UL
#define SPI_MODE3	3

struct flash_layout {
	long start;
	long end;
};
static struct spi_flash *flash;

struct medium_interface {
	char name[NAME_LEN];
	int (*init)(void);
	void (*exit)(void);
};

#define MAX_UPDATE_INTF 3
static struct medium_interface s_intf[MAX_UPDATE_INTF] = {
#ifdef CONFIG_AUTO_SD_UPDATE
	{.name = "mmc", .init = mmc_stor_init,  .exit = mmc_stor_exit, },
#endif
#ifdef CONFIG_AUTO_USB_UPDATE
	{.name = "usb", .init = usb_stor_init,  .exit = usb_stor_exit, },
#endif
};

/* layout of the FLASH. ST = start address, ND = end address. */
#define AU_FL_FIRMWARE_ST   0x0
#define AU_FL_FIRMWARE_ND   0x7FFFF
#define AU_FL_KERNEL_ST     0x100000
#define AU_FL_KERNEL_ND     0x5FFFFF
#define AU_FL_ROOTFS_ST     0x600000
#define AU_FL_ROOTFS_ND     0xbFFFFF

static int au_stor_curr_dev; /* current device */

/* index of each file in the following arrays */
#define IDX_FIRMWARE    0
#define IDX_KERNEL  1
#define IDX_ROOTFS  2

/* max. number of files which could interest us */
#define AU_MAXFILES 3

/* pointers to file names */
char *aufile[AU_MAXFILES] = {
	AU_FIRMWARE,
	AU_KERNEL,
	AU_ROOTFS
};

/* sizes of flash areas for each file */
long ausize[AU_MAXFILES] = {
	(AU_FL_FIRMWARE_ND + 1) - AU_FL_FIRMWARE_ST,
	(AU_FL_KERNEL_ND + 1) - AU_FL_KERNEL_ST,
	(AU_FL_ROOTFS_ND + 1) - AU_FL_ROOTFS_ST,
};

/* array of flash areas start and end addresses */
struct flash_layout aufl_layout[AU_MAXFILES] = {
	{ AU_FL_FIRMWARE_ST,    AU_FL_FIRMWARE_ND, },
	{ AU_FL_KERNEL_ST,  AU_FL_KERNEL_ND,   },
	{ AU_FL_ROOTFS_ST,  AU_FL_ROOTFS_ND,   },
};

/* where to load files into memory */
#if defined(CONFIG_HI3559AV100ES)
#define LOAD_ADDR ((unsigned char *)0x42000000)
#else
#define LOAD_ADDR ((unsigned char *)0x82000000)
#endif
/* the app is the largest image */
#define MAX_LOADSZ ausize[IDX_ROOTFS]

static int au_check_cksum_valid(int idx, long nbytes)
{
	image_header_t *hdr;
	unsigned long checksum;

	hdr = (image_header_t *)LOAD_ADDR;

	if (nbytes != (sizeof(*hdr) + ntohl(hdr->ih_size))) {
		printf("Image %s bad total SIZE\n", aufile[idx]);
		return -1;
	}
	/* check the data CRC */
	checksum = ntohl(hdr->ih_dcrc);
	if (crc32(0, (unsigned char const *)(LOAD_ADDR + sizeof(*hdr)),
			  ntohl(hdr->ih_size)) != checksum) {
		printf("Image %s bad data checksum\n", aufile[idx]);
		return -1;
	}

	return 0;
}

static int au_check_header_valid(int idx, long nbytes)
{
	image_header_t *hdr;
	unsigned long checksum;

	char env[ENV_LEN];
	char auversion[ENV_LEN];

	hdr = (image_header_t *)LOAD_ADDR;
	/* check the easy ones first */

#undef CHECK_VALID_DEBUG
#ifdef CHECK_VALID_DEBUG
	printf("\nmagic %#x %#x\n", ntohl(hdr->ih_magic), IH_MAGIC);
	printf("arch %#x %#x\n", hdr->ih_arch, IH_ARCH_ARM);
	printf("size %#x %#lx\n", ntohl(hdr->ih_size), nbytes);
	printf("type %#x %#x\n", hdr->ih_type, IH_TYPE_KERNEL);
#endif
	if (nbytes < sizeof(*hdr)) {
		printf("Image %s bad header SIZE\n", aufile[idx]);
		return -1;
	}
	if (ntohl(hdr->ih_magic) != IH_MAGIC || hdr->ih_arch != IH_ARCH_ARM) {
		printf("Image %s bad MAGIC or ARCH\n", aufile[idx]);
		return -1;
	}
	/* check the hdr CRC */
	checksum = ntohl(hdr->ih_hcrc);
	hdr->ih_hcrc = 0;

	if (crc32(0, (unsigned char const *)hdr, sizeof(*hdr)) != checksum) {
		printf("Image %s bad header checksum\n", aufile[idx]);
		return -1;
	}
	hdr->ih_hcrc = htonl(checksum);
	/* check the type - could do this all in one gigantic if() */
	if ((idx == IDX_FIRMWARE) && (hdr->ih_type != IH_TYPE_FIRMWARE)) {
		printf("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	if ((idx == IDX_KERNEL) && (hdr->ih_type != IH_TYPE_KERNEL)) {
		printf("Image %s wrong type\n", aufile[idx]);
		return -1;
	}
	if ((idx == IDX_ROOTFS) &&
		(hdr->ih_type != IH_TYPE_RAMDISK) &&
		(hdr->ih_type != IH_TYPE_FILESYSTEM)) {
		printf("Image %s wrong type\n", aufile[idx]);
		ausize[idx] = 0;
		return -1;
	}

	/* recycle checksum */
	checksum = ntohl(hdr->ih_size);
	/* for kernel and app the image header must also fit into flash */
	if ((idx == IDX_KERNEL) || (hdr->ih_type == IH_TYPE_RAMDISK))
		checksum += sizeof(*hdr);

	/* check the size does not exceed space in flash. HUSH scripts */
	/* all have ausize[] set to 0 */
	if ((ausize[idx] != 0) && (ausize[idx] < checksum)) {
		printf("Image %s is bigger than FLASH\n", aufile[idx]);
		return -1;
	}

	sprintf(env, "%lx", (unsigned long)ntohl(hdr->ih_time));
	setenv(auversion, env);

	return 0;
}

static void schedule_notify(unsigned long offset, unsigned long len,
						unsigned long off_start)
{
	int percent_complete = -1;

	do {
		unsigned long long n =
				(unsigned long long)(offset - off_start) * PERCENT;
		int percent;

		do_div(n, len);
		percent = (int)n;

		/* output progress message only at whole percent
		 * steps to reduce the number of messages
		 * printed on (slow) serial consoles
		 */
		if (percent != percent_complete) {
			percent_complete = percent;

			printf("\rOperation at 0x%lx -- %3d%% complete",
				   offset, percent);
		}
	} while (0);
}

static int spi_flash_erase_op(struct spi_flash *flash, unsigned long offset,
							  unsigned long len)
{
	int ret;
	struct mtd_info_ex *spiflash_info = get_spiflash_info();
	unsigned long erase_start, erase_len, erase_step;

	erase_start = offset;
	erase_len   = len;
	erase_step  = spiflash_info->erasesize;

	while (len > 0) {
		if (len < erase_step)
			erase_step = len;

		ret = flash->erase(flash, (u32)offset, erase_step);
		if (ret)
			return 1;

		len -= erase_step;
		offset += erase_step;
		/* notify real time schedule */
		schedule_notify(offset, erase_len, erase_start);
	}
	return ret;
}

static int spi_flash_write_op(struct spi_flash *flash, unsigned long offset,
						unsigned long len, char *buf)
{
	int ret;
	unsigned long write_start, write_len, write_step;
	char *pbuf = buf;
	struct mtd_info_ex *spiflash_info = get_spiflash_info();

	write_start = offset;
	write_len   = len;
	write_step  = spiflash_info->erasesize;

	while (len > 0) {
		if (len < write_step)
			write_step = len;

		ret = flash->write(flash, offset, write_step, pbuf);
		if (ret)
			break;

		offset += write_step;
		pbuf   += write_step;
		len    -= write_step;
		/* notify real time schedule */
		schedule_notify(offset, write_len, write_start);
	}

	return ret;
}

static int au_do_update(int idx, long sz)
{
	image_header_t *hdr;
	unsigned long start, len;
	unsigned long write_len;
	int rc;
	void *buf;
	char *pbuf;

	hdr = (image_header_t *)LOAD_ADDR;

	start = aufl_layout[idx].start;
	len = aufl_layout[idx].end - aufl_layout[idx].start + 1;

	/*
	 * erase the address range.
	 */
	printf("flash erase...\n");
	rc = spi_flash_erase_op(flash, start, len);
	if (rc) {
		printf("SPI flash sector erase failed\n");
		return 1;
	}

	buf = map_physmem((unsigned long)LOAD_ADDR, len, MAP_WRBACK);
	if (!buf) {
		puts("Failed to map physical memory\n");
		return 1;
	}

	/* strip the header - except for the kernel and ramdisk */
	if (hdr->ih_type == IH_TYPE_KERNEL || hdr->ih_type == IH_TYPE_RAMDISK) {
		pbuf = buf;
		write_len = sizeof(*hdr) + ntohl(hdr->ih_size);
	} else {
		pbuf = (buf + sizeof(*hdr));
		write_len = ntohl(hdr->ih_size);
	}

	/* copy the data from RAM to FLASH */
	printf("\nflash write...\n");
	rc = spi_flash_write_op(flash, start, write_len, pbuf);
	if (rc) {
		printf("SPI flash write failed, return %d\n", rc);
		return 1;
	}

	/* check the dcrc of the copy */
	if (crc32(0, (unsigned char const *)(buf + sizeof(*hdr)),
			  ntohl(hdr->ih_size)) != ntohl(hdr->ih_dcrc)) {
		printf("Image %s Bad Data Checksum After COPY\n", aufile[idx]);
		return -1;
	}

	unmap_physmem(buf, len);

	return 0;
}

static void get_update_env(char *img_start, char *img_end)
{
	long start = -1;
	long end = 0;
	char *env;

	/*
	 * check whether start and end are defined in environment
	 * variables.
	 */
	env = env_get(img_start);
	if (env != NULL)
		start = simple_strtoul(env, NULL, HEX);

	env = env_get(img_end);
	if (env != NULL)
		end = simple_strtoul(env, NULL, HEX);

	if (start >= 0 && end && end > start) {
		ausize[IDX_FIRMWARE] = (end + 1) - start;
		aufl_layout[0].start = start;
		aufl_layout[0].end = end;
	}
}

/*
 * If none of the update file(u-boot, kernel or rootfs) was found
 * in the medium, return -1;
 * If u-boot has been updated, return 1;
 * Others, return 0;
 */
static int update_to_flash(void)
{
	int i;
	long sz;
	int res, cnt;
	int uboot_updated;
	int image_found;

	/* just loop thru all the possible files */
	for (i = 0; i < AU_MAXFILES; i++) {
		/* just read the header */
		sz = file_fat_read(aufile[i], LOAD_ADDR, sizeof(image_header_t));
		debug("read %s sz %ld hdr %d\n", aufile[i], sz, sizeof(image_header_t));
		if (sz <= 0 || sz < sizeof(image_header_t)) {
			debug("%s not found\n", aufile[i]);
			continue;
		}

		image_found = 1;

		if (au_check_header_valid(i, sz) < 0) {
			debug("%s header not valid\n", aufile[i]);
			continue;
		}

		sz = file_fat_read(aufile[i], LOAD_ADDR, MAX_LOADSZ);
		debug("read %s sz %ld hdr %d\n", aufile[i], sz, sizeof(image_header_t));
		if (sz <= 0 || sz <= sizeof(image_header_t)) {
			debug("%s not found\n", aufile[i]);
			continue;
		}

		if (au_check_cksum_valid(i, sz) < 0) {
			debug("%s checksum not valid\n", aufile[i]);
			continue;
		}

		/* If u-boot had been updated, we need to
		 * save current env to flash
		 */
		if (strcmp((char *)AU_FIRMWARE, aufile[i]) == 0)
			uboot_updated = 1;

		/* this is really not a good idea, but it's what the customer wants. */
		cnt = 0;
		do {
			res = au_do_update(i, sz);
			/* let the user break out of the loop */
			if (ctrlc() || had_ctrlc()) {
				clear_ctrlc();

				break;
			}
			cnt++;
		} while (res < 0);
	}

	if (uboot_updated == 1)
		return 1;

	if (image_found == 1)
		return 0;

	return -1;
}

/*
 * This is called by board_init() after the hardware has been set up
 * and is usable. Only if SPI flash initialization failed will this function
 * return -1, otherwise it will return 0;
 */
int do_auto_update(void)
{
	struct blk_desc *stor_dev;
	int old_ctrlc;
	int j;
	int state = -1;
	int dev;

	au_stor_curr_dev = -1;
	for (j = 0; j < MAX_UPDATE_INTF; j++) {
		if ((unsigned long)s_intf[j].name[0] != 0) {
			au_stor_curr_dev = s_intf[j].init();
			if (au_stor_curr_dev == -1) {
				debug("No %s storage device found!\n",
					  s_intf[j].name);
				continue;
			}

			dev = 0;

#if (defined CONFIG_ARCH_HI3559AV100ES)
			if (strncmp("mmc", s_intf[j].name, sizeof("mmc")) == 0)
				dev = MMC2;
#endif
			debug("device name %s!\n", s_intf[j].name);
			stor_dev = blk_get_dev(s_intf[j].name, dev);
			if (stor_dev == NULL) {
				debug("Unknow device type!\n");
				continue;
			}

			if (fat_register_device(stor_dev, 1) != 0) {
				debug("Unable to use %s %d:%d for fatls\n",
						s_intf[j].name, au_stor_curr_dev, 1);
				continue;
			}

			if (file_fat_detectfs() != 0) {
				debug("file_fat_detectfs failed\n");
				continue;
			}

			/*
			 * Get image layout from environment.
			 * If the start address and the end address
			 * were not definedin environment virables,
			 * use the default value
			 */
			get_update_env("firmware_st", "firmware_nd");
			get_update_env("kernel_st", "kernel_nd");
			get_update_env("rootfs_st", "rootfs_nd");

			/*
			 * make sure that we see CTRL-C
			 * and save the old state
			 */
			old_ctrlc = disable_ctrlc(0);

			/*
			 * CONFIG_SF_DEFAULT_SPEED equals 1000000,
			 * CONFIG_SF_DEFAULT_MODE equals 0x3
			 */
			flash = spi_flash_probe(0, 0, MAX_HZ, SPI_MODE3);
			if (!flash) {
				printf("Failed to initialize SPI flash\n");
				return -1;
			}

			state = update_to_flash();

			/* restore the old state */
			disable_ctrlc(old_ctrlc);

			s_intf[j].exit();

			/*
			 * no update file found
			 */
			if (state == -1)
				continue;
			/*
			 * update files have been found on current medium,
			 * so just break here
			 */
			break;
		}
	}

	/*
	 * If u-boot has been updated, it's better to save environment to flash
	 */
	if (state == 1)
		saveenv();
	return 0;
}
#endif /* CONFIG_AUTO_UPDATE */
