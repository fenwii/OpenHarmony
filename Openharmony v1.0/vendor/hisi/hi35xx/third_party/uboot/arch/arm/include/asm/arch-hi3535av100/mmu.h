/*
 * Copyright 2004-2011 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#ifndef __ARM_ARCH_MMU_H
#define __ARM_ARCH_MMU_H

#include <linux/types.h>
#ifdef CONFIG_ARCH_MMU
/*
 * Translation Table Base Bit Masks
 */
#define ARM_TRANSLATION_TABLE_MASK               0xFFFFC000

/*
 * Domain Access Control Bit Masks
 */
#define ARM_ACCESS_TYPE_NO_ACCESS(domain_num)    (0x0 << (domain_num)*2)
#define ARM_ACCESS_TYPE_CLIENT(domain_num)       (0x1 << (domain_num)*2)
#define ARM_ACCESS_TYPE_MANAGER(domain_num)      (0x3 << (domain_num)*2)


#define ARM_MMU_FIRST_LEVEL_FAULT_ID 0x0

struct ARM_MMU_FIRST_LEVEL_FAULT {
	unsigned int id:2;
	unsigned int sbz:30;
};

#define ARM_MMU_FIRST_LEVEL_PAGE_TABLE_ID 0x1

struct ARM_MMU_FIRST_LEVEL_PAGE_TABLE {
	unsigned int id:2;
	unsigned int sbz0:1;
	unsigned int ns:1;
	unsigned int sbz1:1;
	unsigned int domain:4;
	unsigned int imp:1;
	unsigned int base_address:22;
};

#define ARM_MMU_FIRST_LEVEL_SECTION_ID 0x2

struct ARM_MMU_FIRST_LEVEL_SECTION {
	unsigned int id:2;
	unsigned int b:1;
	unsigned int c:1;
	unsigned int xn:1;
	unsigned int domain:4;
	unsigned int imp:1;
	unsigned int ap0:2;
	unsigned int tex:3;
	unsigned int ap1:1;
	unsigned int s:1;
	unsigned int ng:1;
	unsigned int reserved:1;
	unsigned int ns:1;
	unsigned int base_address:12;
};

struct ARM_MMU_FIRST_LEVEL_RESERVED {
	unsigned int id:2;
	unsigned int sbz:30;
};

#define ARM_MMU_SECOND_LEVEL_FAULT_ID 0x0

struct ARM_MMU_SECOND_LEVEL_FAULT {
	unsigned int id:2;
	unsigned int sbz:30;
};

#define ARM_MMU_SECOND_LEVEL_SMALL_ID 0x2

struct ARM_MMU_SECOND_LEVEL_SMALL {
	unsigned int id:2;
	unsigned int b:1;
	unsigned int c:1;
	unsigned int ap0:2;
	unsigned int tex:3;
	unsigned int ap1:1;
	unsigned int s:1;
	unsigned int ng:1;
	unsigned int base_address:20;
};

#define ARM_MMU_FIRST_LEVEL_RESERVED_ID 0x3

#define ARM_MMU_FIRST_LEVEL_DESCRIPTOR_ADDRESS(ttb_base, table_index) \
	(unsigned long *)((unsigned long)(ttb_base) + ((table_index) << 2))

#define ARM_FIRST_LEVEL_PAGE_TABLE_SIZE 0x4000

union ARM_MMU_FIRST_LEVEL_DESCRIPTOR {
	unsigned long word;
	struct ARM_MMU_FIRST_LEVEL_FAULT fault;
	struct ARM_MMU_FIRST_LEVEL_PAGE_TABLE page_table;
	struct ARM_MMU_FIRST_LEVEL_SECTION section;
	struct ARM_MMU_FIRST_LEVEL_RESERVED reserved;
};

union ARM_MMU_SECOND_LEVEL_DESCRIPTOR {
	unsigned long word;
	struct ARM_MMU_SECOND_LEVEL_FAULT fault;
	struct ARM_MMU_SECOND_LEVEL_SMALL small;
};

static inline void ARM_MMU_SECTION(int ttb_base, int actual_base,
		int virtual_base, unsigned int tex, unsigned int cacheable,
		unsigned int bufferable, unsigned int perm,
		unsigned int shareable)
{
	register union ARM_MMU_FIRST_LEVEL_DESCRIPTOR desc;

	desc.word = 0;
	desc.section.id = ARM_MMU_FIRST_LEVEL_SECTION_ID;
	desc.section.c = cacheable;
	desc.section.b = bufferable;
	desc.section.xn = 0;
	desc.section.domain = 0;
	desc.section.ap0 = perm;
	desc.section.tex = tex;
	desc.section.ap1 = 0;
	desc.section.s = shareable;
	desc.section.base_address = actual_base;
	*ARM_MMU_FIRST_LEVEL_DESCRIPTOR_ADDRESS(ttb_base, (virtual_base))
		= desc.word;
}

static inline void X_ARM_MMU_SECTION(int abase, int vbase, int size,
	unsigned int tex, unsigned int cache, unsigned int buff,
	unsigned int access, unsigned int shareable)
{
	int i; int j = abase; int k = vbase;
	unsigned long ttb_base = CONFIG_TTB_ADDR;

	for (i = size; i > 0 ; i--, j++, k++)
		ARM_MMU_SECTION(ttb_base, j, k, tex, cache,
				buff, access, shareable);
}

#define ARM_UNCACHEABLE		0
#define ARM_CACHEABLE		1
#define ARM_UNBUFFERABLE	0
#define ARM_BUFFERABLE		1

#define ARM_ACCESS_PERM_NONE_NONE	0
#define ARM_ACCESS_PERM_RW_NONE		1
#define ARM_ACCESS_PERM_RW_RO		2
#define ARM_ACCESS_PERM_RW_RW		3

#define ARM_NOSHAREABLE     0
#define ARM_SHAREABLE       1

#define ARM_MEMTYPE_STRONGORDER      0
#define ARM_MEMTYPE_DEVICE           1
#define ARM_MEMTYPE_NORMAL           2
#define ARM_MEMTYPE_RESERVED         3


#define ARM_CACHETYPE_NOCACHE        0
#define ARM_CACHETYPE_WRITEBACK      1
#define ARM_CACHETYPE_WRITETHROUGH   2
#define ARM_CACHETYPE_WRITEBACK_ONLY 3


/*
 * Initialization for the Domain Access Control Register
 */
#define ARM_ACCESS_DACR_DEFAULT      (	\
	ARM_ACCESS_TYPE_MANAGER(0)    |	\
	ARM_ACCESS_TYPE_NO_ACCESS(1)  |	\
	ARM_ACCESS_TYPE_NO_ACCESS(2)  |	\
	ARM_ACCESS_TYPE_NO_ACCESS(3)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(4)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(5)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(6)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(7)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(8)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(9)  | \
	ARM_ACCESS_TYPE_NO_ACCESS(10) | \
	ARM_ACCESS_TYPE_NO_ACCESS(11) | \
	ARM_ACCESS_TYPE_NO_ACCESS(12) | \
	ARM_ACCESS_TYPE_NO_ACCESS(13) |	\
	ARM_ACCESS_TYPE_NO_ACCESS(14) |	\
	ARM_ACCESS_TYPE_NO_ACCESS(15))

#endif
#endif
