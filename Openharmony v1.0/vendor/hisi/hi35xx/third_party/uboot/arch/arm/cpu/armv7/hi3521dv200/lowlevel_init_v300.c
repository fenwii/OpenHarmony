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
 */

#include <asm/arch/platform.h>
#include <config.h>
#include <compiler.h>
#include "ddr_training_impl.h"

#define HI_SYS_CTL_REG  SYS_CTRL_REG_BASE

#define OK 0
#define ERROR -1
#define DDR_CA0_OFST        0x24
#define DDR_CA1_OFST        0x28
#define DDR_CA2_OFST        0x2c
#define REG_BASE_DDRC           0x11130000

#define DDRC_CTRL_SREF_OFST     0x8000 + 0x0
#define DDRC_CFG_DDRMODE_OFST   0x8000 + 0X50
#define DDRC_CURR_FUNC_OFST     0x8000 + 0x294

#define DDRC1_CTRL_SREF_OFST    0x9000 + 0x0
#define DDRC1_CFG_DDRMODE_OFST  0x9000 + 0X50
#define DDRC1_CURR_FUNC_OFST    0x9000 + 0x294

#define DDRC2_CTRL_SREF_OFST    0xa000 + 0x0
#define DDRC2_CFG_DDRMODE_OFST  0xa000 + 0X50
#define DDRC2_CURR_FUNC_OFST    0xa000 + 0x294

#define DDRC3_CTRL_SREF_OFST    0xb000 + 0x0
#define DDRC3_CFG_DDRMODE_OFST  0xb000 + 0X50
#define DDRC3_CURR_FUNC_OFST    0xb000 + 0x294

#define DDRC_SELF_REFURBISH_MASK    (0x1)

static inline void delay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) {
		__asm__ __volatile__("nop");
	}
}

extern void reset_cpu(unsigned long addr);

static inline void DWB(void) /* drain write buffer */
{
}

static inline unsigned int readl(unsigned addr)
{
	unsigned int val;

	val = (*(volatile unsigned int *)(uintptr_t)(addr));
	return val;
}

static inline void writel(unsigned val, unsigned addr)
{
	DWB();
	(*(volatile unsigned *)(uintptr_t)(addr)) = (uintptr_t)(val);
	DWB();
}

#define REG_BASE_MISC		0x11024000

#ifdef DDR_SCRAMB_ENABLE

#undef reg_get
#define reg_get(addr) (*(volatile unsigned int *)((long)addr))

#undef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)((long)addr) = (val))
void ddr_scramb_start(unsigned int random1, unsigned int random2)
{

	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA0_OFST), random1);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA1_OFST), random2);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA2_OFST), 0);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA2_OFST), 0x10);
	delay(0x100);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA0_OFST), 0);
	reg_set((unsigned int *)(REG_BASE_MISC + DDR_CA1_OFST), 0);
}

#define REG_BASE_RNG_GEN        0x10130000
#define TRNG_DSTA_FIFO_DATA_OFST    0x204
#define TRNG_DATA_ST_OFST       0x208
#define HISEC_COM_TRNG_CTRL_OFST    0x200

#define BIT_TRNG_FIFO_DATA_CNT      0x8
#define TRNG_FIFO_DATA_CNT_MASK     0xff
#define TRNG_CTRL_DEF_VAL       0xa

#define REG_PERI_CRG_TRNG       0x2d80
#define TRNG_CLK_ENABLE         (0x1 << 4)
#define TRNG_DO_SRST            (0x1 << 0)
#define TRNG_CLK_DISABLE        ~(0x1 << 4)
#define TRNG_UNDO_SRST          ~(0x1 << 0)


/* get random number */
int get_random_num(void)
{
    unsigned int reg_val = 0;

    do {
        reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DATA_ST_OFST);

    } while (!((reg_val >> BIT_TRNG_FIFO_DATA_CNT)
                & TRNG_FIFO_DATA_CNT_MASK));

    reg_val = reg_get(REG_BASE_RNG_GEN + TRNG_DSTA_FIFO_DATA_OFST);

    return reg_val;
}

void trng_init(void)
{
    unsigned int reg_val = 0;

    /* open trng clock */
    reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG_TRNG);
    reg_val |= TRNG_CLK_ENABLE;
    reg_val &= TRNG_UNDO_SRST;
    reg_set(CRG_REG_BASE + REG_PERI_CRG_TRNG, reg_val);

    /* set trng ctrl register */
    reg_set(REG_BASE_RNG_GEN + HISEC_COM_TRNG_CTRL_OFST,
                TRNG_CTRL_DEF_VAL);
}

void trng_deinit(void)
{
    unsigned int reg_val = 0;

    /* close trng clock */
    reg_val = reg_get(CRG_REG_BASE + REG_PERI_CRG_TRNG);
    reg_val &= TRNG_CLK_DISABLE;
    reg_set(CRG_REG_BASE + REG_PERI_CRG_TRNG, reg_val);
}

int ddr_scramb(void)
{
	unsigned int random_num1 = 0;
	unsigned int random_num2 = 0;
	unsigned int reg_val[4] = {0, 0, 0, 0};
	unsigned int ddrc_isvalid[4] = {0, 0, 0, 0};

	/* read ddrc_cfg_ddrmode register,
	 * if value[3:0] is not 0x0 ,the channel is valid.
	 */
	ddrc_isvalid[0] = (reg_get(REG_BASE_DDRC + DDRC_CFG_DDRMODE_OFST) & 0xf)?1:0;
	ddrc_isvalid[1] = (reg_get(REG_BASE_DDRC + DDRC1_CFG_DDRMODE_OFST) & 0xf)?1:0;
	ddrc_isvalid[2] = (reg_get(REG_BASE_DDRC + DDRC2_CFG_DDRMODE_OFST) & 0xf)?1:0;
	ddrc_isvalid[3] = (reg_get(REG_BASE_DDRC + DDRC3_CFG_DDRMODE_OFST) & 0xf)?1:0;

	/* set ddrc to do self-refurbish */
	if (ddrc_isvalid[0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, 0x1);
	if (ddrc_isvalid[1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, 0x1);
	if (ddrc_isvalid[2])
		reg_set(REG_BASE_DDRC + DDRC2_CTRL_SREF_OFST, 0x1);
	if (ddrc_isvalid[3])
		reg_set(REG_BASE_DDRC + DDRC3_CTRL_SREF_OFST, 0x1);

	/* wait the status of ddrc to be sef-refurbish */
	do {
		reg_val[0] = ddrc_isvalid[0]?(reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):1;
		reg_val[1] = ddrc_isvalid[1]?(reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):1;
		reg_val[2] = ddrc_isvalid[2]?(reg_get(REG_BASE_DDRC + DDRC2_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):1;
		reg_val[3] = ddrc_isvalid[3]?(reg_get(REG_BASE_DDRC + DDRC3_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):1;

	} while (!(reg_val[0] & reg_val[1] & reg_val[2] & reg_val[3]));

	trng_init();

	/* get random number */
	random_num1 = get_random_num();
	random_num2 = get_random_num();

	/* start ddr scrambling */
	ddr_scramb_start(random_num1, random_num2);

	/* clear random number */
	random_num1 = get_random_num();
	random_num2 = get_random_num();
	random_num1 = get_random_num();
	random_num2 = get_random_num();

	/* set ddrc to exit self-refurbish */
	if (ddrc_isvalid[0])
		reg_set(REG_BASE_DDRC + DDRC_CTRL_SREF_OFST, (0x1<<1));
	if (ddrc_isvalid[1])
		reg_set(REG_BASE_DDRC + DDRC1_CTRL_SREF_OFST, (0x1<<1));
	if (ddrc_isvalid[2])
		reg_set(REG_BASE_DDRC + DDRC2_CTRL_SREF_OFST, (0x1<<1));
	if (ddrc_isvalid[3])
		reg_set(REG_BASE_DDRC + DDRC3_CTRL_SREF_OFST, (0x1<<1));

	/* wait the status of ddrc to be normal */
	do {
		reg_val[0] = ddrc_isvalid[0]?(reg_get(REG_BASE_DDRC + DDRC_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):0;
		reg_val[1] = ddrc_isvalid[1]?(reg_get(REG_BASE_DDRC + DDRC1_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):0;
		reg_val[2] = ddrc_isvalid[2]?(reg_get(REG_BASE_DDRC + DDRC2_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):0;
		reg_val[3] = ddrc_isvalid[3]?(reg_get(REG_BASE_DDRC + DDRC3_CURR_FUNC_OFST) & DDRC_SELF_REFURBISH_MASK):0;

	} while (reg_val[0] | reg_val[1] | reg_val[2] | reg_val[3]);

	return OK;
}


#endif /* DDR_SCRAMB_ENABLE */

#define CORE_SVB_PWM_CTRL		0x11029000
#define CPU_SVB_PWM_CTRL		0x11029004

#define HPM_CLK_REG			0x11014A80
#define CPU_HPM_CTRL0_REG		0x1102B000
#define CORE_HPM_CTRL0_REG		0x1102B010
#define HPM_CPU_REG0			0x1102B008
#define HPM_CPU_REG1			0x1102B00c
#define HPM_CORE_REG0			0x1102B018
#define HPM_CORE_REG1			0x1102B01c
#define CYCLE_NUM			    32
#define HPM_RECORD_REG0		0x11020340
#define HPM_RECORD_REG1		0x11020344
#define PCB_LAYER_NUMBER_FLAG   0X11020158
#define VOLTAGE_RECOED_REG		0x1102015C

#define SVB_VERSION_REG		0x11020168
#define SVB_VERSION_21DV200	0x0003
#define OTP_HPM_CORE_REG		0x11021504
#define OTP_HPM_CPU_REG		0x11021530
#define OTP_VOLTAGE_DELTA_CORE_REG	0x1102150C
#define OTP_VOLTAGE_DELTA_CPU_REG   	0x11021514
#define OTP_VOLTAGE_DELTA_CORE_FOR_TRAINING_REG   	0x11021518

#define TSENSOR_STATUS0			0X1102A008

#define USE_ATE_HPM 0

static unsigned hpm_value_avg(const unsigned int val[], unsigned int size)
{
	unsigned int i;
	unsigned tmp = 0;

	for (i = 0; i < size; i++)
		tmp += val[i] >> 2; //2

	return tmp >> 5;//5
}

static void get_hpm_value(unsigned int *hpm_core, unsigned int *hpm_cpu)
{
	int i;
	unsigned int temp;
	unsigned int core_value[4] = {0, 0, 0, 0};//4
	unsigned int cpu_value[4] = {0, 0, 0, 0};

	for (i = 0; i < CYCLE_NUM; i++) {
		delay(18);//18

		/* cpu */
		temp = readl(HPM_CPU_REG0);
		cpu_value[1] += (temp >> 16) & 0x3ff; //16
		cpu_value[0] += temp & 0x3ff;
		temp = readl(HPM_CPU_REG1);
		cpu_value[3] += (temp >> 16) & 0x3ff;//3 16
		cpu_value[2] += temp & 0x3ff;//2

		/* core */
		temp = readl(HPM_CORE_REG0);
		core_value[1] += (temp >> 16) & 0x3ff;//16
		core_value[0] += temp & 0x3ff;
		temp = readl(HPM_CORE_REG1);
		core_value[3] += (temp >> 16) & 0x3ff;//3 16
		core_value[2] += temp & 0x3ff;//2
	}

	*hpm_core = hpm_value_avg(core_value, 4);
	*hpm_cpu = hpm_value_avg(cpu_value, 4);
}


static void start_hpm(unsigned int *hpm_core, unsigned int *hpm_cpu)
{
	/* core */
	writel(0x60080001, CORE_HPM_CTRL0_REG);
	/* cpu  */
	writel(0x60080001, CPU_HPM_CTRL0_REG);

	delay(180); /*180 10ms*/

	get_hpm_value(hpm_core, hpm_cpu);
}

	union union_hpm_reg0 {
		struct {
			unsigned int sys_hpm_core : 9; /* [8..0]*/
			unsigned int reserved_0   : 7; /* [15..9]*/
			unsigned int sys_hpm_cpu  : 9; /* [24..16]*/
			unsigned int reserved_1   : 7; /* [31..25]*/
		} bits;
		unsigned int u32;
	};

	union union_hpm_reg1 {
		struct {
			unsigned int temperature   : 8;		/* [7..0]*/
			unsigned int reserved_0    : 20;	/* [27..8]*/
			unsigned int temperature_err : 1;	/* [28]*/
			unsigned int hpm_cpu_err   : 1;		/* [29]*/
			unsigned int hpm_core_err  : 1;		/* [30]*/
			unsigned int from_otp      : 1;		/* [31]*/
		}bits;
		unsigned int u32;
	};

static void hpm_check(unsigned int *hpm_core, unsigned int *hpm_cpu, int *temperature, unsigned int hpm_from_otp_flag)
{
	union union_hpm_reg0 hpm_reg0; /*SVB_RECORD_REG0 0x11020340*/
	union union_hpm_reg1 hpm_reg1; /*SVB_RECORD_REG1 0x11020344*/

	hpm_reg0.u32 = 0;
	hpm_reg1.u32 = 0;

	if (*hpm_core < 220) { //220
		*hpm_core = 220;
		hpm_reg1.bits.hpm_core_err = 1;
	}

	if (*hpm_core > 350) { //350
		*hpm_core = 350;
		hpm_reg1.bits.hpm_core_err = 1;
	}

	if (*hpm_cpu < 220) { //220
		*hpm_cpu = 220;
		hpm_reg1.bits.hpm_cpu_err = 1;
	}

	if (*hpm_cpu > 350) { //350
		*hpm_cpu = 350;
		hpm_reg1.bits.hpm_cpu_err = 1;
	}

	if (*temperature < -40) { //-40
		*temperature = -40;
		hpm_reg1.bits.temperature_err = 1;
	}

	if (*temperature > 120) { //120
		*temperature = 120;
		hpm_reg1.bits.temperature_err = 1;
	}

	hpm_reg0.bits.sys_hpm_core = *hpm_core;
	hpm_reg0.bits.sys_hpm_cpu = *hpm_cpu;
	hpm_reg1.bits.temperature  =  (unsigned int)*temperature;
	hpm_reg1.bits.from_otp     = hpm_from_otp_flag;
	writel(hpm_reg0.u32, HPM_RECORD_REG0);
	writel(hpm_reg1.u32, HPM_RECORD_REG1);
}

static void hpm_adjust(unsigned int *hpm_core, unsigned int *hpm_cpu, const int *temperature, unsigned int hpm_from_otp_flag)
{
    unsigned int hpm_core_tmp;
    unsigned int hpm_cpu_tmp;
    unsigned int hpm_core_bese_line;
    unsigned int hpm_cpu_bese_line;

    if (hpm_from_otp_flag == 1)
        return;

    if (*temperature < 90)//90
        return;

    hpm_core_tmp = *hpm_core;
    hpm_cpu_tmp  = *hpm_cpu;
    hpm_core_bese_line = 326 - ((((unsigned int) *temperature) * 102 + 256) >> 9);//326 102 256 9
    if (hpm_core_tmp > hpm_core_bese_line)
        *hpm_core = hpm_core_tmp + 10;//10

    hpm_cpu_bese_line = 316 - ((((unsigned int)*temperature) * 102 + 256) >> 9);//316 102 256 9
    if (hpm_cpu_tmp > hpm_cpu_bese_line)
        *hpm_cpu = hpm_cpu_tmp + 10;//10
}

static void voltage_adjust(unsigned int *core_volt, unsigned int *cpu_volt)
{
    unsigned int core_volt_tmp;
    unsigned int cpu_volt_tmp;
	short otp_voltage_delta_core;
	short otp_voltage_delta_cpu;
	unsigned int pcb_layer_number_flag;//0: 4 layers pcb; 1: 2 layers pcb

	union {
		struct {
			unsigned int voltage_core : 12; /* [11..0]*/
			unsigned int voltage_cpu  : 12; /* [23..12]*/
			unsigned int reserved: 8; /* [31..24]*/
		} bits;
		unsigned int u32;
	} voltage_reg;

    core_volt_tmp = *core_volt;
    cpu_volt_tmp = *cpu_volt;
	otp_voltage_delta_core = (short)(readl(OTP_VOLTAGE_DELTA_CORE_REG) & 0xffff);
	otp_voltage_delta_cpu = (short)(readl(OTP_VOLTAGE_DELTA_CPU_REG) & 0xffff);

	pcb_layer_number_flag = readl(PCB_LAYER_NUMBER_FLAG) & 0x1;
	*core_volt = (unsigned int)((int)core_volt_tmp + otp_voltage_delta_core);

	if (pcb_layer_number_flag == 1) {
	    *cpu_volt  = (unsigned int)((int)cpu_volt_tmp + otp_voltage_delta_cpu + 10);//10
	} else {
	    *cpu_volt  = (unsigned int)((int)cpu_volt_tmp + otp_voltage_delta_cpu);
	}

	voltage_reg.u32 = 0;
	voltage_reg.bits.voltage_core = *core_volt;
	voltage_reg.bits.voltage_cpu  = *cpu_volt;

	writel(voltage_reg.u32, VOLTAGE_RECOED_REG);
}

static void set_core_volt(unsigned int mv)
{
	unsigned int svb_value;

	svb_value = (((((1078595 - mv * 1000) * 1337) >> 4)-0x10000) & 0xffff0000) + 0x19f5;//1078595  1000 1337 4 0x19f5

	writel(svb_value, CORE_SVB_PWM_CTRL);
}

static void set_cpu_volt(unsigned int mv)
{
	unsigned int svb_value;

	svb_value = (((((1097582 - mv * 1000) * 1462) >> 4)-0x10000) & 0xffff0000) + 0x19f5;//1097582  1000 1462 4 0x19f5

	writel(svb_value, CPU_SVB_PWM_CTRL);
}

static void convert_hpm_to_volt_core(unsigned int hpm_core, unsigned int *mv)
{
    unsigned int volt;

    volt = 1245 - ((hpm_core * 297 * 1000)>>18);//1245 297 1000 18

    if (volt > 984)//984
        *mv = 984;
    else if (volt < 858)//858
        *mv = 858;
    else
        *mv = volt;
}

static void convert_hpm_to_volt_cpu(unsigned int hpm_cpu, unsigned int *mv)
{
    unsigned int volt;

    volt = 1489 - ((hpm_cpu * 251 * 1000)>>17);//1489 251 1000 17

    if (volt > 1030)//1030
        *mv = 1030;
    else if (volt < 880)//880
        *mv = 880;
    else
        *mv = volt;
}

static void get_temperature(int *temperature)
{
	unsigned int value;

	value = (unsigned int)(readl(TSENSOR_STATUS0) & 0x3ff);
	*temperature = (int)((((int)value - 127) * 431) >> 11) - 40;//127 431 11 40
}

static void get_ate_hpm(unsigned int *pate_hpm_core, unsigned int *pate_hpm_cpu)
{
	*pate_hpm_core = (unsigned int)(readl(OTP_HPM_CORE_REG) & 0xffff);
	*pate_hpm_cpu  = (unsigned int)(readl(OTP_HPM_CPU_REG) & 0xffff);
}

static void get_volt_delta_for_training(short *otp_volt_delta_core_for_training)
{
    short volt_delta_tmp;

    volt_delta_tmp = (short)(readl(OTP_VOLTAGE_DELTA_CORE_FOR_TRAINING_REG) & 0xffff);
    if (volt_delta_tmp >= 40)//40
        *otp_volt_delta_core_for_training = 40;
    else if (volt_delta_tmp <= -40)//-40
        *otp_volt_delta_core_for_training = -40;
    else
        *otp_volt_delta_core_for_training = volt_delta_tmp;
}

static void start_svb(void)
{
	unsigned int ate_hpm_core;
	unsigned int ate_hpm_cpu;
	unsigned int hpm_core;
	unsigned int hpm_cpu;
	unsigned int core_volt;
	unsigned int cpu_volt;
    unsigned int core_volt_for_training;
    short otp_volt_delta_core_for_training;
	int temperature;
	unsigned int hpm_from_otp;
	unsigned int version;
	unsigned int pcb_layer_number_flag;//0: 4 layers pcb; 1: 2 layers pcb

	version = readl(SVB_VERSION_REG);
	version = (version & 0x0000FFFF) | (SVB_VERSION_21DV200 << 16);//16
	writel(version, SVB_VERSION_REG);

	pcb_layer_number_flag = readl(PCB_LAYER_NUMBER_FLAG) & 0x1;

	/* open hmp clock */
	writel(0x10, HPM_CLK_REG);//0x10
	delay(18);//18
	get_temperature(&temperature);

	if (!USE_ATE_HPM) {
		set_core_volt(990);//990
		set_cpu_volt(990);
		start_hpm(&hpm_core, &hpm_cpu);
		hpm_from_otp = 0;
	} else {
        get_ate_hpm(&ate_hpm_core, &ate_hpm_cpu);
		/*ATE SVB transfer to board SVB*/
		hpm_core = ate_hpm_core;
		hpm_cpu = ate_hpm_cpu;
		hpm_from_otp = 1;
	}

    hpm_adjust(&hpm_core, &hpm_cpu, &temperature, hpm_from_otp);

	hpm_check(&hpm_core, &hpm_cpu, &temperature, hpm_from_otp);

    convert_hpm_to_volt_core(hpm_core, &core_volt);
	convert_hpm_to_volt_cpu(hpm_cpu, &cpu_volt);

    voltage_adjust(&core_volt, &cpu_volt);

    get_volt_delta_for_training(&otp_volt_delta_core_for_training);

	if (pcb_layer_number_flag == 1) {
		core_volt_for_training = (unsigned int)((int)core_volt + otp_volt_delta_core_for_training - 40);//40
    } else {
		core_volt_for_training = (unsigned int)((int)core_volt + otp_volt_delta_core_for_training - 20);//20
    }

    set_core_volt(core_volt_for_training);
    set_cpu_volt(cpu_volt);

	/* delay 10ms do not delete */
	delay(180);//180 10ms
}

static void end_svb(void)
{
	unsigned int core_volt;

	union {
		struct {
			unsigned int voltage_core : 12; /* [11..0]*/
			unsigned int voltage_cpu  : 12; /* [23..12]*/
			unsigned int reserved: 8; /* [31..24]*/
		} bits;
		unsigned int u32;
	} voltage_reg;

	voltage_reg.u32 = 0;
	voltage_reg.u32 = readl(VOLTAGE_RECOED_REG);
	core_volt = voltage_reg.bits.voltage_core;

	set_core_volt(core_volt);

	/* delay 10ms do not delete */
	delay(90); //90 5ms
}

void start_ddr_training(unsigned int base)
{
	start_svb();

	/* ddr hw training */
	ddr_hw_training_if();

	/* ddr sw training */
	ddr_sw_training_if();

	/* the value should config after trainning, or
	it will cause chip compatibility problems */
	if ((readl(DDR_REG_BASE_PHY0 + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
		writel(0x401, DDR_REG_BASE_DMC1 + 0x28);
	} else {
		writel(0x401, DDR_REG_BASE_DMC0 + 0x28);
	}
#ifdef DDR_REG_BASE_PHY1
	if ((readl(DDR_REG_BASE_PHY1 + DDR_PHY_DRAMCFG)
		& PHY_DRAMCFG_TYPE_MASK) == PHY_DRAMCFG_TYPE_LPDDR4) {
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

	end_svb();
}
