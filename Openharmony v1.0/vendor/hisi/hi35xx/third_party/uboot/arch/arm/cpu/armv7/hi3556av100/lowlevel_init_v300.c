/*
 * lowlevel_init_v300.c
 *
 * The file is Hardware initialization.
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

#include <asm/arch/platform.h>
#include <config.h>
#include <ddr_interface.h>

#define HI_SYS_CTL_REG  SYS_CTRL_REG_BASE

#define OK 0
#define ERROR (-1)
#define DDR_CA0_OFST        0x88
#define DDR_CA1_OFST        0x8c
#define DDR_CA2_OFST        0x90
#define REG_BASE_DDRC           0x04600000

#define DDRC_CTRL_SREF_OFST     (0x8000 + 0x0)
#define DDRC_CFG_DDRMODE_OFST   (0x8000 + 0X50)
#define DDRC_CURR_FUNC_OFST     (0x8000 + 0x294)

#define DDRC1_CTRL_SREF_OFST    (0x9000 + 0x0)
#define DDRC1_CFG_DDRMODE_OFST  (0x9000 + 0X50)
#define DDRC1_CURR_FUNC_OFST    (0x9000 + 0x294)

#define DDRC2_CTRL_SREF_OFST    (0xa000 + 0x0)
#define DDRC2_CFG_DDRMODE_OFST  (0xa000 + 0X50)
#define DDRC2_CURR_FUNC_OFST    (0xa000 + 0x294)

#define DDRC3_CTRL_SREF_OFST    (0xb000 + 0x0)
#define DDRC3_CFG_DDRMODE_OFST  (0xb000 + 0X50)
#define DDRC3_CURR_FUNC_OFST    (0xb000 + 0x294)

#define DDRC_SELF_REFURBISH_MASK    0x1

/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0       0x0460c000
/* base on needs #define DDR_REG_BASE_PHY1 0x0460e000 */

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0       0x04608000
#define DDR_REG_BASE_DMC1       0x04609000

#ifdef DDR_REG_BASE_PHY1
#define DDR_REG_BASE_DMC2       0x0460a000
#define DDR_REG_BASE_DMC3       0x0460b000
#endif

#define DDR_PHY_DRAMCFG     0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */
static inline void delay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 1000: Cycle */
		__asm__ __volatile__("nop");
}

static inline void dwb(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
	unsigned int val;

	val = (*(volatile unsigned int *)(addr));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	dwb();
	(*(volatile unsigned *)(addr)) = (val);
	dwb();
}

#ifdef DDR_SCRAMB_ENABLE

#define REG_BASE_MISC       0x04528000
#define MISC_CTRL88_OFST    0x88
#define MISC_CTRL8C_OFST    0x8c
#define MISC_CTRL90_OFST    0x90

#define REG_BASE_DDRC       DDRC0_REG_BASE
#define DDRC_0_CTRL_SREF_OFST   0x8000 + 0x0
#define DDRC_0_CURR_FUNC_OFST   0x8000 + 0x294
#define DDRC_1_CTRL_SREF_OFST   0x9000 + 0x0
#define DDRC_1_CURR_FUNC_OFST   0x9000 + 0x294

static void ddr_scramb_start(unsigned int random1, unsigned int random2)
{
	writel(random1, REG_BASE_MISC + MISC_CTRL88_OFST);
	writel(random2, REG_BASE_MISC + MISC_CTRL8C_OFST);
	writel(0, REG_BASE_MISC + MISC_CTRL90_OFST);
	writel(0x10, REG_BASE_MISC + MISC_CTRL90_OFST);

	delay(1000); /* delay 1000ms */

	writel(0, REG_BASE_MISC + MISC_CTRL88_OFST);
	writel(0, REG_BASE_MISC + MISC_CTRL8C_OFST);
}

#define REG_BASE_RNG_GEN        0x04090000
#define TRNG_DSTA_FIFO_DATA_OFST    0x204
#define TRNG_DATA_ST_OFST       0x208
#define HISEC_COM_TRNG_CTRL_OFST    0x200
#define REG_PERI_CRG101         0x0194

#define BIT_TRNG_FIFO_DATA_CNT      0x8
#define TRNG_FIFO_DATA_CNT_MASK     0xff
#define TRNG_CTRL_DEF_VAL       0xa

#define TRNG_CLK_ENABLE         (0x1 << 13)
#define TRNG_DO_SRST            (0x1 << 12)
#define TRNG_CLK_DISABLE        ~(0x1 << 13)
#define TRNG_UNDO_SRST          ~(0x1 << 12)

#undef reg_get
#define reg_get(addr) (*(volatile unsigned int *)((long)addr))

#undef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)((long)addr) = (val))

/* get random number */
int get_random_num(void)
{
	unsigned int reg_val;

	do {
		reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);
	} while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT)
			   & TRNG_FIFO_DATA_CNT_MASK));

	reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

	return reg_val;
}

void trng_init(void)
{
	unsigned int reg_val;

	/* open rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG101);
	reg_val |= TRNG_CLK_ENABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG101, reg_val);

	/* set trng ctrl register */
	reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
			TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
	unsigned int reg_val;

	/* close rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG101);
	reg_val &= TRNG_CLK_DISABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG101, reg_val);
}

static int ddr_scramb(void)
{
	unsigned int random_num1;
	unsigned int random_num2;
	unsigned int reg_val[NUM_2] = {0, 0};
	unsigned int ddrc_isvalid[NUM_2] = {0, 0};

	/* read ddrc_cfg_ddrmode register,
	 * if value[3:0] is not 0x0 ,the channel is valid.
	 */
	ddrc_isvalid[0] =
		(reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;
	ddrc_isvalid[1] =
		(reg_get(REG_BASE_DDRC + DDRC1_CFG_DDRMODE_OFST) & 0xf) ? 1 : 0;

	/* set ddrc to do self-refurbish */
	if (ddrc_isvalid[0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, 0x1);

	if (ddrc_isvalid[1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, 0x1);

	/* wait the status of ddrc to be sef-refurbish */
	do {
		reg_val[0] = ddrc_isvalid[0] ?
			(reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & 0x1) : 1;
		reg_val[1] = ddrc_isvalid[1] ?
			(reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & 0x1) : 1;
	} while (!(reg_val[0] & reg_val[1]));

	trng_init();

	/* get random number */
	random_num1 = get_random_num();
	random_num2 = get_random_num();

	/* start ddr scrambling */
	ddr_scramb_start(random_num1, random_num2);

	/* clear random number */
	(void)get_random_num();
	(void)get_random_num();
	(void)get_random_num();
	(void)get_random_num();

	trng_deinit();

	/* set ddrc to exit self-refurbish */
	if (ddrc_isvalid[0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, (0x1 << 1));

	if (ddrc_isvalid[1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, (0x1 << 1));

	/* wait the status of ddrc to be normal */
	do {
		reg_val[0] = ddrc_isvalid[0] ?
			(reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & 0x1) : 0;
		reg_val[1] = ddrc_isvalid[1] ?
			(reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & 0x1) : 0;
	} while (reg_val[0] | reg_val[1]);

	return OK;
}

#endif /* DDR_SCRAMB_ENABLE */

void start_ddr_training(unsigned int base)
{
	/* ddr hw training */
	ddr_hw_training_if();

	ddr_cmd_site_save();
	/* ddr sw training */
	ddr_sw_training_if();
	ddr_cmd_site_restore();

	/* the value should config after trainning, or
	  it will cause chip compatibility problems */
	if ((readl(DDR_REG_BASE_PHY0 + DDR_PHY_DRAMCFG) &
		PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	} else {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
	}

#ifdef DDR_REG_BASE_PHY1

	if ((readl(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG) &
		PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC2 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC3 + 0x28);
	} else {
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	}

#endif
#ifdef DDR_SCRAMB_ENABLE
	/* enable ddr scramb */
	ddr_scramb();
#endif
}
