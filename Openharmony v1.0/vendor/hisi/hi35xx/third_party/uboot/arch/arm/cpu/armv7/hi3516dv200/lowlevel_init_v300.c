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
#include <compiler.h>
#include <asm/arch/platform.h>
#include <config.h>
#include <ddr_training_impl.h>

static inline void delay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 100: Cycle */
		__asm__ __volatile__("nop");
}

static inline void dwb(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
	unsigned int val;

	val = (*(volatile unsigned int *)((uintptr_t)(addr)));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	dwb();
	(*(volatile unsigned *)((uintptr_t)(addr))) = (val);
	dwb();
}

#define REG_BASE_RNG_GEN            0x10090000
#define TRNG_DSTA_FIFO_DATA_OFST    0x204
#define TRNG_DATA_ST_OFST           0x208
#define BIT_TRNG_FIFO_DATA_CNT      0x8
#define TRNG_FIFO_DATA_CNT_MASK     0xff
#define REG_PERI_CRG104             0x1a0
#define TRNG_CLK_ENABLE             (0x1<<3)
#define TRNG_CLK_DISABLE            ~(0x1<<3)
#define TRNG_CTRL_DEF_VAL           0xa
#define HISEC_COM_TRNG_CTRL_OFST    0x200

#define REG_BASE_MISC               0x12030000
#define DDR_CA0_OFST                0x28
#define DDR_CA1_OFST                0x2C
#define DDR_CA2_OFST                0x30

#define REG_BASE_DDRC               0x120d0000
#define DDRC_CTRL_SREF_OFST         (0x8000 + 0x0)
#define DDRC_CFG_DDRMODE_OFST       (0x8000 + 0x50)
#define DDRC_CURR_FUNC_OFST         (0x8000 + 0x294)

#define DDRC_CHANNEL_VALID_MASK     0xf
#define DDRC_SELF_REFURBISH_MASK    0x1

#define DDRC_SELF_REFURBISH_EN      0x1
#define DDRC_SELF_REFURBISH_EXIT    (0x1 << 1)

#undef reg_get
#undef reg_set
#define reg_get(addr) readl(addr)
#define reg_set(addr, val) writel(val, (unsigned int)(addr))

#define duty_formula(val)  (((unsigned int)((1099 - (val)) * 460) >> 10) - 1)
#define volt_formula(val) (1287 - ((1514 * (val)) >> 10))
#define temperature_formula(val)  (((((val) - 117) * 212) >> 10) - 40)
#define hpm_formula(hpm, temp)  ((hpm) + 4 + ((((temp) - 70) * 205) >> 10))

void trng_init(void)
{
	unsigned int reg_val;
	/* open rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG104);
	reg_val |= TRNG_CLK_ENABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG104, reg_val);

	/* set trng ctrl register */
	reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
			TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
	unsigned int reg_val;

	/* close rsa and trng clock */
	reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG104);
	reg_val &= TRNG_CLK_DISABLE;
	reg_set(CRG_REG_BASE + REG_PERI_CRG104, reg_val);
}

/* svb */
#define SVB_VER_16DV200             0x10

#define CYCLE_NUM 4
#define  HPM_CORE_REG0 0x120280d8
#define  HPM_CORE_REG1 0x120280dc

#define SVB_PWM_REG 0X120280b0

#define SVB_VER_REG         0x12020168
#define  HPM_CHECK_REG 0x1202015c
#define SYS_CTRL_VOLT_REG 0x12020158

#define TSENSOR_STATUS0 0x120280bc
#define OTP_HPM_CORE_REG 0x100a002c

#define HPM_CORE_MIN 150
#define HPM_CORE_MAX 350

#define TEMPERATURE_MIN  117
#define TEMPERATURE_MAX  841

#define  HPM_CORE_VALUE_MIN 190
#define  HPM_CORE_VALUE_MAX 310

#define svb_pwm_reg_val(val) ((((val) << 16) & 0XFFFF0000) + 0x0c75)

static unsigned hpm_value_avg(unsigned int *val, int num)
{
	unsigned int i;
	unsigned tmp = 0;

	for (i = 0; i < num; i++)
		tmp += val[i] >> NUM_2;

	return tmp >> NUM_2;
}

static void get_hpm_value(unsigned int *hpm_core)
{
	int i;
	unsigned int temp;
	unsigned int core_value[NUM_4];

	core_value[NUM_0] = 0;
	core_value[NUM_1] = 0;
	core_value[NUM_2] = 0;
	core_value[NUM_3] = 0;

	for (i = 0; i < CYCLE_NUM; i++) {
		delay(10); /* delay 10ms */

		temp = readl(HPM_CORE_REG0);
		core_value[NUM_1] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		core_value[NUM_0] += temp & 0x3ff;
		temp = readl(HPM_CORE_REG1);
		core_value[NUM_3] += (temp >> 16) & 0x3ff; /* get hight 16 bits */
		core_value[NUM_2] += temp & 0x3ff;
	}

	*hpm_core = hpm_value_avg(core_value, NUM_4);
}

static void start_hpm(unsigned int *hpm_core)
{
	get_hpm_value(hpm_core);
}

static void hpm_check(unsigned int *hpm_core)
{
	union {
		struct {
			unsigned int reserved_0 : 16; /* [15..0] */
			unsigned int sys_hpm_core : 9; /* [24..16] */
			unsigned int reserved_1 : 1; /* [25] */
			unsigned int hpm_core_err : 1; /* [26] */
			unsigned int reserved_2 : 5; /* [27..31] */
		} bits;

		unsigned int u32;
	} sysboot10;
	sysboot10.u32 = readl(HPM_CHECK_REG);
	sysboot10.bits.sys_hpm_core = 0;
	sysboot10.bits.hpm_core_err = 0;

	if (*hpm_core < HPM_CORE_MIN) {
		*hpm_core = HPM_CORE_MIN;
		sysboot10.bits.hpm_core_err = 1;
	}
	if (*hpm_core > HPM_CORE_MAX) {
		*hpm_core = HPM_CORE_MAX;
		sysboot10.bits.hpm_core_err = 1;
	}

	sysboot10.bits.sys_hpm_core = *hpm_core;

	writel(sysboot10.u32, HPM_CHECK_REG);
}

static void get_temperature(unsigned int *temperature)
{
	unsigned int value;

	value = readl(TSENSOR_STATUS0);
	value = value & 0x3ff;

	if (value <= TEMPERATURE_MIN)
		*temperature = -40; /* -40: temperature value */
	else if (value >= TEMPERATURE_MAX)
		*temperature = 110; /* 110: temperature value */
	else
		*temperature = temperature_formula(value);
}

static void adjust_hpm(unsigned int *hpm_core, unsigned int temperature)
{
	/* 283 70: hpm_core and temperature Threshold */
	if ((*hpm_core >= 283) && (temperature >= 70))
		*hpm_core = hpm_formula(*hpm_core, temperature);
	/* 222 70: hpm_core and temperature Threshold */
	else if ((*hpm_core <= 222) && (temperature >= 70))
		*hpm_core = *hpm_core - NUM_4;
}

static void set_hpm_core_volt(unsigned int hpm_core_value)
{
	unsigned int volt;
	unsigned int duty;
	unsigned int otp_vmin_core = readl(OTP_HPM_CORE_REG);

	if (hpm_core_value <= HPM_CORE_VALUE_MIN)
		volt = 1006; /* 1006: volt value */
	else if (hpm_core_value >= HPM_CORE_VALUE_MAX)
		volt = 829; /* 829: volt value */
	else
		volt = volt_formula(hpm_core_value);

	volt = volt + (int)((short int)(otp_vmin_core >> 16)); /* get hight 16 bits */

	writel(volt, SYS_CTRL_VOLT_REG);
	duty = duty_formula(volt);

	writel(svb_pwm_reg_val(duty), SVB_PWM_REG);
}

void start_svb(void)
{
	unsigned int hpm_core = 0;
	unsigned int temperature = 0;

	unsigned int tmp_reg = readl(SVB_VER_REG);
	tmp_reg = (tmp_reg & 0xff00ffff) | (SVB_VER_16DV200 << 16); /* Move Left 16bit */
	writel(tmp_reg, SVB_VER_REG);

	get_temperature(&temperature);
	start_hpm(&hpm_core);
	adjust_hpm(&hpm_core, temperature);
	hpm_check(&hpm_core);

	set_hpm_core_volt(hpm_core);
	delay(200); /* delay 200ms */
}


/* [CUSTOM] DDR PHY0-PHY1 base register */
#define DDR_REG_BASE_PHY0       0x120dc000

/* [CUSTOM] DDR DMC0-DMC3 base register */
#define DDR_REG_BASE_DMC0       0x120d8000
#define DDR_REG_BASE_DMC1       0x120d8000

#ifdef DDR_REG_BASE_PHY1
#define DDR_REG_BASE_DMC2       0x120d9000
#define DDR_REG_BASE_DMC3       0x120d9000
#endif

#define CRG_REG_BASE            0x12010000
#define PERI_CRG_DDRT           0x198

#define DDR_REG_BASE_SYSCTRL    0x12020000
/* [SYSCTRL]RAM Retention control register 0 */
#define SYSCTRL_MISC_CTRL4      0x8010

#define DDR_PHY_DRAMCFG         0x2c    /* DRAM config register */
#define PHY_DRAMCFG_TYPE_MASK   0xf /* [3:0] */
#define PHY_DRAMCFG_TYPE_LPDDR4 0x6   /* [2:0] 110 LPDDR4 */

#define BYTE_NUM  2

/**
 * ddr_boot_prepare
 * @void
 *
 * Do some prepare before ddr training.
 * Keep empty when nothing to do.
 */
static void ddr_boot_prepare(struct tr_relate_reg *reg)
{
	/* select ddrt bus path */
	reg->custom.ive_ddrt_mst_sel = readl(DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);
	writel(reg->custom.ive_ddrt_mst_sel & 0xffffffdf,
		   DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);

	/* turn on ddrt clock */
	reg->custom.ddrt_clk_reg = readl(CRG_REG_BASE + PERI_CRG_DDRT);
	/* enable ddrt0 clock */
	writel(reg->custom.ddrt_clk_reg | (0x1 << 1), CRG_REG_BASE + PERI_CRG_DDRT);
	__asm__ __volatile__("nop");
	/* disable ddrt0 soft reset */
	writel(readl(CRG_REG_BASE + PERI_CRG_DDRT) & (~(0x1 << 0)),
		   CRG_REG_BASE + PERI_CRG_DDRT);

	/* disable rdqs anti-aging */
	reg->custom.phy0_age_compst_en = readl(DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
	writel((reg->custom.phy0_age_compst_en & 0x7fffffff),
		   DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
	reg->custom.phy1_age_compst_en = readl(DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
	writel((reg->custom.phy1_age_compst_en & 0x7fffffff),
		   DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

/**
 * ddr_boot_restore
 * @void
 *
 * Restore register config after ddr training.
 * Keep empty when nothing to do.
 */
static void ddr_boot_restore(struct tr_relate_reg *reg)
{
	/* restore ddrt bus path */
	writel(reg->custom.ive_ddrt_mst_sel, DDR_REG_BASE_SYSCTRL + SYSCTRL_MISC_CTRL4);

	/* restore ddrt clock */
	writel(reg->custom.ddrt_clk_reg, CRG_REG_BASE + PERI_CRG_DDRT);

	/* restore rdqs anti-aging */
	writel(reg->custom.phy0_age_compst_en, DDR_REG_BASE_PHY0 + DDR_PHY_PHYRSCTRL);
#ifdef DDR_REG_BASE_PHY1
	writel(reg->custom.phy1_age_compst_en, DDR_REG_BASE_PHY1 + DDR_PHY_PHYRSCTRL);
#endif
}

/**
 * ddr_rdqs_bdl_adj
 * @void
 *
 * Adjust rdqs/rdq/rdm bdl to avoid problem cause by ddr anti-aging.
 */
static void ddr_rdqs_bdl_adj(void)
{
	int i;
	unsigned int rdqs;
	unsigned int rdq03, rdq47;
	unsigned int rdm;
	unsigned int tmp;

	for (i = 0; i < BYTE_NUM; i++) {
		rdqs = readl(DDR_REG_BASE_PHY0 + 0x22c + i * 0x80);
		rdq03 = readl(DDR_REG_BASE_PHY0 + 0x21c + i * 0x80);
		rdq47 = readl(DDR_REG_BASE_PHY0 + 0x220 + i * 0x80);
		rdm = readl(DDR_REG_BASE_PHY0 + 0x224 + i * 0x80);

		/* rdqs bdl lower two bit shoud be 0x11 */
		while ((rdqs & 0x3) < 0x3) {
			/* rdqs/rdq/rdm bdl + 1 */
			rdqs = rdqs + 0x1;
			rdq03 = rdq03 + 0x01010101;
			rdq47 = rdq47 + 0x01010101;
			rdm = rdm + 0x1;

			writel(rdqs, DDR_REG_BASE_PHY0 + 0x22c + i * 0x80);
			writel(rdq03, DDR_REG_BASE_PHY0 + 0x21c + i * 0x80);
			writel(rdq47, DDR_REG_BASE_PHY0 + 0x220 + i * 0x80);
			writel(rdm, DDR_REG_BASE_PHY0 + 0x224 + i * 0x80);
		}
	}

	tmp = readl(DDR_REG_BASE_PHY0 + DDR_PHY_MISC);
	tmp |= (1 << PHY_MISC_UPDATE_BIT);
	/* update new config to PHY */
	writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_MISC);
	tmp &= ~(1 << PHY_MISC_UPDATE_BIT);
	writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_MISC);
	tmp = readl(DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITCTRL);
	/* set 1 to issue PHY counter reset signal */
	tmp |= (1 << PHY_PHYCONN_RST_BIT);
	writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITCTRL);
	/* set 0 to end the reset signal */
	tmp &= ~(1 << PHY_PHYCONN_RST_BIT);
	writel(tmp, DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITCTRL);
}

void start_ddr_training(unsigned int base)
{
	struct tr_relate_reg relate_reg;
	struct tr_relate_reg *reg = &relate_reg;

	start_svb();

	ddr_boot_prepare(reg);

	/* ddr pcode training */
	ddr_pcode_training_if();
	/* ddr hw training */
	ddr_hw_training_if();
	/* ddr sw training */
	ddr_sw_training_if();

	ddr_rdqs_bdl_adj();

	ddr_boot_restore(reg);

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
	/* enable ddr scramb */
}
