/*
 * soc.h
 *
 * Files related to system startup.
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

#ifndef __HI_SOC_H__
#define __HI_SOC_H__

extern unsigned int blank_zone_start;
extern unsigned int get_blank_start(void);
extern void init_registers(unsigned int base, unsigned int pm);
extern void emmc_boot_read(void *ptr, unsigned int size);
extern void memcpy_32(void *dst, void *src, unsigned int size);

#ifdef CONFIG_DDR_TRAINING_V2
	extern void start_ddr_training(unsigned int base);
#endif /* CONFIG_DDR_TRAINING_V2 */

#endif
