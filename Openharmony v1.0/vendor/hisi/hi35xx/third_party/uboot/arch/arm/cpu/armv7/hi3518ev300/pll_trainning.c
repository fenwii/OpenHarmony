/*
 * pll_trainning.c
 *
 * The pll trainning Device Driver for hisilicon.
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
#include <asm/io.h>
#include <asm/string.h>

#ifdef CONFIG_EDMA_PLL_TRAINNING

#define __24MHZ		24000000

#define LOOP_COUNT	5

#define THE_CRG_BASE		0x12010000
#define PERI_CRG_PLL1		0x04
#define PERI_CRG32		    0x80
#define PERI_CRG101		    0x194
#define PERI_CRG110		    0x1b8

#define MISC_REG_BASE		0x12028000
#define SVB_CTRL_BASE		0x12080000
#define SVB_SYS_VOLTAGE_OFFSET	0x04
#define SVB_SYS_VOLTAGE_UPDATE_OFFSET  0x0C
#define SVB_PWM_SEL 		0x1202009c

#define UART0_REG_PHYS		0x12040000
#define UART1_REG_PHYS		0x12041000
#define UART2_REG_PHYS		0x12042000

#define UART_DR			0x0
#define UART_CR			0x30

#define HIEDMA0_REG_BASE	0x100b0000
#define INT_TC1			0x4
#define INT_TC1_RAW		0x600

#define DMA_RXCHNL_CONFIG    0x47700005
#define DMA_TXCHNL_CONFIG    0x87700005
#define DMA_REG_CHNL0   0X830
#define DMA_REG_CHNL1   0X870

#define DMA_CHNL0_DONE		(1<<0)
#define DMA_CHNL1_DONE		(1<<1)

#define DDR_DATA_BASE 0x42000000

#define ioremap(physaddr, size)	((void *)(physaddr))
#define iounmap(physassr)  ((void)0)

#define array_size(x) (sizeof(x) / sizeof((x)[0]))

#define pll_trainning_debug(s)
#define pll_trainning_debug_hex(s)
void uart_early_puts(const char *ss);
void uart_early_put_hex(int hex);

static inline void udelay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 100: Cycle */
		__asm__ __volatile__("nop");
}

static unsigned long dma_phys;

static void *crg_base;
static void *misc_base;
static void *edma0_reg_base;

struct pin_info {
	unsigned long pinmx_reg_base;
	unsigned long pinmx_reg_offset;
	unsigned int pinmx_func_num;
	unsigned int restored_val;
	unsigned int pinmx_func_changed;
};

static struct pin_info pmx_list[] = {
	{
		.pinmx_reg_base = 0x100c0000,
		.pinmx_reg_offset = 0x0c,
		.pinmx_func_num = 0x2,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x100c0000,
		.pinmx_reg_offset = 0x10,
		.pinmx_func_num = 0x2,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x112c0000,
		.pinmx_reg_offset = 0x70,
		.pinmx_func_num = 0x2,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x112c0000,
		.pinmx_reg_offset = 0x74,
		.pinmx_func_num = 0x2,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x0120c0000,
		.pinmx_reg_offset = 0x10,
		.pinmx_func_num = 0x4,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x120c0000,
		.pinmx_reg_offset = 0x14,
		.pinmx_func_num = 0x4,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x120c0000,
		.pinmx_reg_offset = 0x18,
		.pinmx_func_num = 0x4,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
	{
		.pinmx_reg_base = 0x120c0000,
		.pinmx_reg_offset = 0x1c,
		.pinmx_func_num = 0x4,
		.restored_val = 0x0,
		.pinmx_func_changed = 0
	},
};

static void save_one_pin(struct pin_info *pin)
{
	unsigned int val;
	void *pmx_reg_virt = ioremap(pin->pinmx_reg_base, 0x1000);
	pmx_reg_virt += pin->pinmx_reg_offset;
	val = readl(pmx_reg_virt);
	if ((val & 0xf) == pin->pinmx_func_num) {
		pin->restored_val = val;
		val &= 0xfffffff0;
		writel(val, pmx_reg_virt);
		pin->pinmx_func_changed = 1;
	} else {
		pin->pinmx_func_changed = 0;
	}
	iounmap(pmx_reg_virt);
}

static void ptdev_pinmux_save(void)
{
	unsigned pmx_nr = array_size(pmx_list);
	struct pin_info *pmx_info = NULL;
	int i;

	for (i = 0; i < pmx_nr; i++) {
		pmx_info = &pmx_list[i];
		save_one_pin(pmx_info);
	}
}

static void restore_one_pin(struct pin_info *pin)
{
	void *pmx_reg_virt = ioremap(pin->pinmx_reg_base, 0x1000);
	pmx_reg_virt += pin->pinmx_reg_offset;

	if (pin->pinmx_func_changed)
		writel(pin->restored_val, pmx_reg_virt);

	iounmap(pmx_reg_virt);
}

static void ptdev_pinmux_restore(void)
{
	unsigned pmx_nr = array_size(pmx_list);
	struct pin_info *pmx_info = NULL;
	int i;

	for (i = 0; i < pmx_nr; i++) {
		pmx_info = &pmx_list[i];
		restore_one_pin(pmx_info);
	}
}

struct pll_trainning_dev {
	char *name;
	unsigned long ctrlreg_phys;
	void *ctrlreg_base;
	unsigned int tx_dma_reqline_val;
	unsigned int rx_dma_reqline_val;
	unsigned int reset_bit;
	unsigned int clock_gate_bit;

	void (*dev_clock_enable)(struct pll_trainning_dev *dev);
	void (*dev_rx_dma_init)(struct pll_trainning_dev *dev);
	void (*dev_dma_exit)(struct pll_trainning_dev *dev);
	int (*rx_trans_test)(struct pll_trainning_dev *dev);
};

struct voltage_regulator {
	unsigned int curr;
	unsigned int max;
	unsigned int min;
	unsigned int reg_base;
	void *reg_virt;
	unsigned int pwm_sel;
	void *pwm_sel_reg_virt;
	unsigned int steps[NUM_7];
	void (*init)(struct voltage_regulator *regulator);
	int (*adjust)(struct voltage_regulator *regulator, int step);
	void (*restore)(struct voltage_regulator *regulator);
	void (*exit)(struct voltage_regulator *regulator);
};

static void edma_apb_axi_clock_enable(void)
{
	void *addr = crg_base + PERI_CRG101;
	unsigned int val = readl(addr);

	/* set bit1: dmac_apb_cken and bit2: dmac_cken Enable */
	val |= ((1 << 1) | (1 << 2));
	writel(val, addr);
	/* set bit0: dmac_srst_req Enable */
	val |= (1 << 0);
	writel(val, addr);
	/* set bit0: dmac_srst_req disable */
	val &= ~(1 << 0);
	writel(val, addr);
}

static void pt_dev_clock_enable(struct pll_trainning_dev *dev)
{
	void *addr = crg_base + PERI_CRG110;
	unsigned int val = readl(addr);

	val |= (1 << dev->clock_gate_bit);
	writel(val, addr);

	val |= (1 << dev->reset_bit);
	writel(val, addr);

	val &= ~(1 << dev->reset_bit);
	writel(val, addr);
}

static void uart_rx_dma_init(struct pll_trainning_dev *dev)
{
	edma_apb_axi_clock_enable();
	if (dev->dev_clock_enable)
		dev->dev_clock_enable(dev);

	/* dma cfg */
	writel(0x0, edma0_reg_base + 0x688);
	writel(0xff, edma0_reg_base + 0x600);
	writel(0xff, edma0_reg_base + 0x608);
	writel(0xff, edma0_reg_base + 0x610);
	writel(0xff, edma0_reg_base + 0x618);
	writel(0xff, edma0_reg_base + 0x620);
	writel(0x0, edma0_reg_base + 0x18);
	writel(0x0, edma0_reg_base + 0x1c);
	writel(0x0, edma0_reg_base + 0x20);
	writel(0x0, edma0_reg_base + 0x24);
	writel(0x0, edma0_reg_base + 0x28);
	writel(0x0, edma0_reg_base + 0x830);
	writel(dev->ctrlreg_phys, edma0_reg_base + 0x820); /* dma src address */
	writel(0, edma0_reg_base + 0x824);
	writel(dma_phys + 0x800, edma0_reg_base + 0x828); /* dma dest address */
	writel(0, edma0_reg_base + 0x82c);
	writel(0x400, edma0_reg_base + 0x81c); /* len  */

	writel(0x0, edma0_reg_base + 0x870);
	writel(dma_phys, edma0_reg_base + 0x860); /* dma src address */
	writel(0, edma0_reg_base + 0x864);
	writel(dev->ctrlreg_phys, edma0_reg_base + 0x868); /* dma dest address */
	writel(0, edma0_reg_base + 0x86c);
	writel(0x400, edma0_reg_base + 0x85c); /* len */

	/* uart cfg */
	writel(0x7ff, dev->ctrlreg_base + 0x44);
	writel(0x1, dev->ctrlreg_base + 0x24);
	writel(0x0, dev->ctrlreg_base + 0x28);
	writel(0x70, dev->ctrlreg_base + 0x2c);
	writel(0x0, dev->ctrlreg_base + 0x34);
	writel(0x40, dev->ctrlreg_base + 0x38);
	writel(0x3, dev->ctrlreg_base + 0x48);
	udelay(1);
	writel(0x381, dev->ctrlreg_base + 0x30);
	udelay(1);
}

static void uart_dma_exit(struct pll_trainning_dev *dev)
{
	edma_apb_axi_clock_enable();
	if (dev->dev_clock_enable)
		dev->dev_clock_enable(dev);
}


/*
 * return: on -1, dma timeout;
 *	   on -2, data err;
 */
static int do_uart_dma_rx_tst(struct pll_trainning_dev *dev)
{
	int j;
	unsigned int val;
	int ret = -1;

	writel(DMA_RXCHNL_CONFIG + (dev->rx_dma_reqline_val << NUM_4),
					edma0_reg_base + DMA_REG_CHNL0);
	writel(DMA_TXCHNL_CONFIG + (dev->tx_dma_reqline_val << NUM_4),
					edma0_reg_base + DMA_REG_CHNL1);

	for (j = 0; j < 0x1000; j++) {
		val = readl(edma0_reg_base + INT_TC1_RAW);
		if ((val & DMA_CHNL0_DONE) && (val & DMA_CHNL1_DONE)) {
			ret = 0;
			writel(0x3, edma0_reg_base + INT_TC1_RAW);
			break;
		}
		udelay(1); /* delay 1 us */
	}

	if (ret)
		pll_trainning_debug("DMA time out!\r\n");

	return ret;
}

static int uart_rx_trans_test(struct pll_trainning_dev *dev)
{
	int ret;

	if (dev->dev_rx_dma_init)
		dev->dev_rx_dma_init(dev);

	ret = do_uart_dma_rx_tst(dev);

	dev->dev_dma_exit(dev);
	return ret;
}

static int start_training(struct pll_trainning_dev *devs, unsigned int dev_nr)
{
	int i, ret;
	int pass = 1;

	for (i = 0; i < dev_nr; i++) {
		struct pll_trainning_dev *pt_dev = &devs[i];
		if (pt_dev->rx_trans_test) {
			ret = pt_dev->rx_trans_test(pt_dev);
			if (ret) {
				pass = 0;
				pll_trainning_debug(pt_dev->name);
				pll_trainning_debug(":rx trainning failed!\r\n");
				return pass;
			}
		}
	}

	return pass;
}

struct pll_trainning_dev train_devs[] = {
	{
		.name = "uart1",
		.ctrlreg_phys = UART1_REG_PHYS,
		.tx_dma_reqline_val = 0x13,
		.rx_dma_reqline_val = 0x12,
		.clock_gate_bit = 1, /* bit1: clock gate bit */
		.reset_bit = 6, /* bit6 :Soft reset */
		.dev_clock_enable = pt_dev_clock_enable,
		.dev_rx_dma_init = uart_rx_dma_init,
		.dev_dma_exit = uart_dma_exit,
		.rx_trans_test = uart_rx_trans_test
	},

	{
		.name = "uart2",
		.ctrlreg_phys = UART2_REG_PHYS,
		.tx_dma_reqline_val = 0x15,
		.rx_dma_reqline_val = 0x14,
		.clock_gate_bit = 2, /* bit2: clock gate bit */
		.reset_bit = 7, /* bit7 :Soft reset */
		.dev_clock_enable = pt_dev_clock_enable,
		.dev_rx_dma_init = uart_rx_dma_init,
		.dev_dma_exit = uart_dma_exit,
		.rx_trans_test = uart_rx_trans_test
	},
};

static void svb_voltage_regulator_init(struct voltage_regulator *regulator)
{
	unsigned int i, val;
	unsigned int step_25 = 10;
	unsigned int step_50 = 20;
	unsigned int step_80 = 30;
	unsigned int step_100 = 50;

	regulator->pwm_sel_reg_virt = ioremap(SVB_PWM_SEL, 0x1000);
	val = readl(regulator->pwm_sel_reg_virt);
	regulator->pwm_sel = (val) & 0xf;

	regulator->reg_virt = ioremap(regulator->reg_base, 0x1000);
	val = readl(regulator->reg_virt + SVB_SYS_VOLTAGE_OFFSET + 0x20 *
				regulator->pwm_sel);
	regulator->curr = (val) & 0xff;

	if (regulator->curr + step_50 < regulator->max)
		regulator->steps[NUM_0] = regulator->curr + step_50;
	else
		regulator->steps[NUM_0] = regulator->max;

	if (regulator->curr + step_25 < regulator->max)
		regulator->steps[NUM_1] = regulator->curr + step_25;
	else
		regulator->steps[NUM_1] = regulator->max;

	regulator->steps[NUM_2] = regulator->curr;

	if (regulator->curr > regulator->min + step_25)
		regulator->steps[NUM_3] = regulator->curr - step_25;
	else
		regulator->steps[NUM_3] = regulator->min;

	if (regulator->curr > regulator->min + step_50)
		regulator->steps[NUM_4] = regulator->curr - step_50;
	else
		regulator->steps[NUM_4] = regulator->min;

	if (regulator->curr > regulator->min + step_80)
		regulator->steps[NUM_5] = regulator->curr - step_80;
	else
		regulator->steps[NUM_5] = regulator->min;

	if (regulator->curr > regulator->min + step_100)
		regulator->steps[NUM_6] = regulator->curr - step_100;
	else
		regulator->steps[NUM_6] = regulator->min;

	if (regulator->steps[NUM_5] <= regulator->steps[NUM_6])
		regulator->steps[NUM_6] = 0xffffffff;

	if (regulator->steps[NUM_4] <= regulator->steps[NUM_5])
		regulator->steps[NUM_5] = 0xffffffff;

	if (regulator->steps[NUM_3] <= regulator->steps[NUM_4])
		regulator->steps[NUM_4] = 0xffffffff;

	if (regulator->steps[NUM_2] <= regulator->steps[NUM_3])
		regulator->steps[NUM_3] = 0xffffffff;

	if (regulator->steps[NUM_0] <= regulator->steps[NUM_1])
		regulator->steps[NUM_0] = 0xffffffff;

	if (regulator->steps[NUM_1] <= regulator->steps[NUM_2])
		regulator->steps[NUM_1] = 0xffffffff;

	regulator->max = ((regulator->curr + step_50) < regulator->max) ?
				(regulator->curr + step_50) : regulator->max;
	regulator->min = ((regulator->curr - step_100) > regulator->min) ?
				(regulator->curr - step_100) : regulator->min;

	pll_trainning_debug("svb voltage min/max[0x");
	pll_trainning_debug_hex(regulator->min);
	pll_trainning_debug("/0x");
	pll_trainning_debug_hex(regulator->max);
	pll_trainning_debug("] steps: \r\n");
	for (i = 0; i < NUM_7; i++) {
		pll_trainning_debug_hex(regulator->steps[i]);
		pll_trainning_debug("\r\n");
	}
}

static int svb_voltage_adjust(struct voltage_regulator *regulator, int step)
{
	unsigned int val;

	if (regulator->steps[step] == 0xffffffff)
		return -1;

	val = readl(regulator->reg_virt + SVB_SYS_VOLTAGE_OFFSET + 0x20 *
				regulator->pwm_sel);
	val &= 0xffffff00;
	val |= regulator->steps[step];
	writel(val, regulator->reg_virt + SVB_SYS_VOLTAGE_OFFSET + 0x20 *
		   regulator->pwm_sel);
	writel(NUM_5, regulator->reg_virt + SVB_SYS_VOLTAGE_UPDATE_OFFSET + 0x20 *
		   regulator->pwm_sel);
	return 0;
}

static void svb_voltage_restore(struct voltage_regulator *regulator)
{
	unsigned int val = readl(regulator->reg_virt + SVB_SYS_VOLTAGE_OFFSET + 0x20 *
							 regulator->pwm_sel);
	val &= 0xffffff00;
	val |= regulator->curr;
	writel(val, regulator->reg_virt + SVB_SYS_VOLTAGE_OFFSET + 0x20 *
		   regulator->pwm_sel);
	writel(NUM_5, regulator->reg_virt + SVB_SYS_VOLTAGE_UPDATE_OFFSET + 0x20 *
		   regulator->pwm_sel);
}

static void svb_voltage_regulator_exit(struct voltage_regulator *regulator)
{
	iounmap(regulator->reg_virt);
	iounmap(regulator->pwm_sel_reg_virt);
}


struct voltage_regulator volt_regulator = {
	.min	= 0,
	.max	= 0xc7,
	.reg_base = SVB_CTRL_BASE,
	.steps	= {0},
	.init	= svb_voltage_regulator_init,
	.adjust = svb_voltage_adjust,
	.restore = svb_voltage_restore,
	.exit	= svb_voltage_regulator_exit
};

int pll_trainning_init(void)
{
	int ret = -1;
	int i;
	int j;
	unsigned int dev_nr;
	int trainning_pass = 1;
	static int pll_rst_cnt = 0xffffffff;

	dev_nr = array_size(train_devs);
	crg_base = ioremap(THE_CRG_BASE, 0x1000);
	if (!crg_base)
		return ret;
	misc_base = ioremap(MISC_REG_BASE, 0x1000);
	if (!misc_base) {
		iounmap(crg_base);
		return ret;
	}
	edma0_reg_base = ioremap(HIEDMA0_REG_BASE, 0x1000);
	if (!edma0_reg_base) {
		iounmap(misc_base);
		iounmap(crg_base);
		return ret;
	}

	ptdev_pinmux_save();
	dma_phys = DDR_DATA_BASE;

	for (i = 0; i < dev_nr; i++) {
		struct pll_trainning_dev *pt_dev = &train_devs[i];
		pt_dev->ctrlreg_base = ioremap(pt_dev->ctrlreg_phys, 0x1000);
	}

	if (volt_regulator.init)
		volt_regulator.init(&volt_regulator);

	pll_trainning_debug("### UART pll reset count 0x");
	pll_trainning_debug_hex(pll_rst_cnt);
	pll_trainning_debug("\r\n");

	for (j = 0; (j < LOOP_COUNT) && (trainning_pass == 1); j++) {
		for (i = 0; (i < array_size(volt_regulator.steps)) &&
			 (trainning_pass == 1); i++) {
			pll_trainning_debug("svb_just step=");
			pll_trainning_debug_hex(i);
			pll_trainning_debug("\r\n");

			if (volt_regulator.adjust(&volt_regulator, i)) {
				/*
				 * invalid voltage range, no need to do the trainning.
				 */
				continue;
			}

			trainning_pass = start_training(train_devs, dev_nr);
		}
	}

	if (trainning_pass != 1) {
		pll_trainning_debug("### PLL trainning failed!!\r\n");
		pll_trainning_debug("### LOOP_COUNT: 0x");
		pll_trainning_debug_hex(j);
		pll_trainning_debug("\r\n");

		pll_rst_cnt--;
		ret = -1;
	} else {
		uart_early_puts("\r\n    EDMA PLL TRAINNING ALL PASS!\r\n");
		ret = 0;
	}

	volt_regulator.restore(&volt_regulator);
	volt_regulator.exit(&volt_regulator);

	ptdev_pinmux_restore();

	iounmap(edma0_reg_base);
	iounmap(misc_base);
	iounmap(crg_base);

	return ret;
}

#endif

