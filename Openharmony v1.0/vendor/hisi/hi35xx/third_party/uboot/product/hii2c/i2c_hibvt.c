/*
 * i2c_hibvt.c
 *
 * The I2C Controller Device Driver.
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
#include <command.h>
#include <asm/io.h>
#include <linux/errno.h>

struct i2c_init_desc {
	unsigned long ctrl_base;
	unsigned char flag;
};

#define I2C_INIT_UNDO   0
#define I2C_INIT_DONE   1
#define i2c_desc(reg)   {.ctrl_base = (reg), \
			.flag = I2C_INIT_UNDO}

#if defined(CONFIG_TARGET_HI3559AV100) || defined(CONFIG_TARGET_HI3569V100)
#include "i2c_hi3559av100.c"
#else
#define I2C_BUS_CLOCK   mhz(50)
#define I2C_MAX_NUM 0
struct i2c_init_desc hibvt_i2c_init_desc[] = NULL;
#endif

/*
 * I2C Registers offsets
 */
#define HIBVT_I2C_GLB       0x0
#define HIBVT_I2C_SCL_H     0x4
#define HIBVT_I2C_SCL_L     0x8
#define HIBVT_I2C_DATA1     0x10
#define HIBVT_I2C_TXF       0x20
#define HIBVT_I2C_RXF       0x24
#define HIBVT_I2C_CMD_BASE  0x30
#define HIBVT_I2C_LOOP1     0xb0
#define HIBVT_I2C_DST1      0xb4
#define HIBVT_I2C_TX_WATER  0xc8
#define HIBVT_I2C_RX_WATER  0xcc
#define HIBVT_I2C_CTRL1     0xd0
#define HIBVT_I2C_CTRL2     0xd4
#define HIBVT_I2C_STAT      0xd8
#define HIBVT_I2C_INTR_RAW  0xe0
#define HIBVT_I2C_INTR_EN   0xe4
#define HIBVT_I2C_INTR_STAT 0xe8

/*
 * Create a contiguous bitmask starting at bit position @l and ending at
 * position @h.
 */
#define genmask(h, l) \
	(((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

/*
 * I2C Global Config Register -- HIBVT_I2C_GLB
 */
#define GLB_EN_MASK     BIT(0)
#define GLB_SDA_HOLD_MASK   genmask(23, 8)
#define GLB_SDA_HOLD_SHIFT  8

/*
 * I2C Timing CMD Register -- HIBVT_I2C_CMD_BASE + n * 4 (n = 0, 1, 2, ... 31)
 */
#define CMD_EXIT    0x0
#define CMD_TX_S    0x1
#define CMD_TX_D1_2 0x4
#define CMD_TX_D1_1 0x5
#define CMD_TX_FIFO 0x9
#define CMD_RX_FIFO 0x12
#define CMD_RX_ACK  0x13
#define CMD_IGN_ACK 0x15
#define CMD_TX_ACK  0x16
#define CMD_TX_NACK 0x17
#define CMD_JMP1    0x18
#define CMD_UP_TXF  0x1d
#define CMD_TX_RS   0x1e
#define CMD_TX_P    0x1f

/*
 * I2C Control Register 1 -- HIBVT_I2C_CTRL1
 */
#define CTRL1_CMD_START_MASK    BIT(0)

/*
 * I2C Status Register -- HIBVT_I2C_STAT
 */
#define STAT_RXF_NOE_MASK   BIT(16) /* RX FIFO not empty flag */
#define STAT_TXF_NOF_MASK   BIT(19) /* TX FIFO not full flag */


/*
 * I2C Interrupt status and mask Register --
 * HIBVT_I2C_INTR_RAW, HIBVT_I2C_STAT, HIBVT_I2C_INTR_STAT
 */
#define INTR_ABORT_MASK     (BIT(0) | BIT(11))
#define INTR_RX_MASK        BIT(2)
#define INTR_TX_MASK        BIT(4)
#define INTR_CMD_DONE_MASK  BIT(12)
#define INTR_USE_MASK       (INTR_ABORT_MASK | \
				INTR_RX_MASK | \
				INTR_TX_MASK | \
				INTR_CMD_DONE_MASK)
#define INTR_ALL_MASK       genmask(31, 0)

#define I2C_DEFAULT_FREQUENCY   100000
#define I2C_TXF_DEPTH       64
#define I2C_RXF_DEPTH       64
#define I2C_TXF_WATER       32
#define I2C_RXF_WATER       32
#define I2C_WAIT_TIMEOUT    0x400
#define I2C_IRQ_TIMEOUT     (msecs_to_jiffies(1000))
#define khz(clk)    ((clk) * 1000)
#define mhz(clk)    ((clk) * 1000000)
#define MAX_SPEED   khz(400)
unsigned int g_i2c_speed = I2C_DEFAULT_FREQUENCY;
int g_i2c_num = -1;

struct hibvt_i2c_msg {
	__u16 chip;     /* slave address */
	__u16 addr;     /* reg address */
	__u16 alen;     /* reg width,1 or 2 */
	__u16 flags;
	__u16 len;      /* msg length,1 or 2 */
	__u8 *buf;      /* pointer to msg data */
#define I2C_M_RD        0x0001  /* read data, from slave to master */
#define I2C_M_IGNORE_NAK    0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_TEN       0x0010  /* this is a ten bit chip address */
#define I2C_M_STOP      0x8000  /* if I2C_FUNC_PROTOCOL_MANGLING */
};

struct hibvt_i2c_dev {
	struct device       *dev;
	void *base;
	unsigned int        clk;
	unsigned int        freq;
	struct hibvt_i2c_msg        *msg;
	unsigned int        msg_num;
	unsigned int        msg_idx;
	unsigned int        msg_buf_ptr;

	int         status;
};
struct hibvt_i2c_dev i2c_dev;
static inline void hibvt_i2c_disable(struct hibvt_i2c_dev *i2c);
static inline void hibvt_i2c_cfg_irq(struct hibvt_i2c_dev *i2c, unsigned int flag);
static inline unsigned int hibvt_i2c_clr_irq(struct hibvt_i2c_dev *i2c);
static inline void hibvt_i2c_enable(struct hibvt_i2c_dev *i2c);
#define CHECK_SDA_IN_SHIFT     16
#define GPIO_MODE_SHIFT        8
#define FORCE_SCL_OEN_SHIFT    4
#define FORCE_SDA_OEN_SHIFT    0

static void hibvt_i2c_rescue(struct hibvt_i2c_dev *i2c)
{
	unsigned int val;
	unsigned int time_cnt;
	int index;

	hibvt_i2c_disable(i2c);
	hibvt_i2c_cfg_irq(i2c, 0);
	hibvt_i2c_clr_irq(i2c);

	val = (0x1 << GPIO_MODE_SHIFT) | (0x1 << FORCE_SCL_OEN_SHIFT) |
		  (0x1 << FORCE_SDA_OEN_SHIFT);
	writel(val, i2c->base + HIBVT_I2C_CTRL2);

	time_cnt = 0;
	do {
		for (index = 0; index < 9; index++) { /* 9: Cycle */
			val = (0x1 << GPIO_MODE_SHIFT) | 0x1;
			writel(val, i2c->base + HIBVT_I2C_CTRL2);

			udelay(5); /* delay 5us */

			val = (0x1 << GPIO_MODE_SHIFT) | (0x1 << FORCE_SCL_OEN_SHIFT) |
				  (0x1 << FORCE_SDA_OEN_SHIFT);
			writel(val, i2c->base + HIBVT_I2C_CTRL2);

			udelay(5); /* delay 5us */
		}

		time_cnt++;
		if (time_cnt > I2C_WAIT_TIMEOUT) {
			printf("wait Timeout!\n");
			goto disable_rescue;
		}

		val = readl(i2c->base + HIBVT_I2C_CTRL2);
	} while (!(val & (0x1 << CHECK_SDA_IN_SHIFT)));

	val = (0x1 << GPIO_MODE_SHIFT) | (0x1 << FORCE_SCL_OEN_SHIFT) |
		  (0x1 << FORCE_SDA_OEN_SHIFT);
	writel(val, i2c->base + HIBVT_I2C_CTRL2);

	val = (0x1 << GPIO_MODE_SHIFT) | (0x1 << FORCE_SCL_OEN_SHIFT);
	writel(val, i2c->base + HIBVT_I2C_CTRL2);

	udelay(10); /* delay 10us */

	val = (0x1 << GPIO_MODE_SHIFT) | (0x1 << FORCE_SCL_OEN_SHIFT) |
		  (0x1 << FORCE_SDA_OEN_SHIFT);
	writel(val, i2c->base + HIBVT_I2C_CTRL2);

disable_rescue:
	val = (0x1 << FORCE_SCL_OEN_SHIFT) | 0x1;
	writel(val, i2c->base + HIBVT_I2C_CTRL2);
}

static void hibvt_i2c_disable(struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_GLB);
	val &= ~GLB_EN_MASK;
	writel(val, i2c->base + HIBVT_I2C_GLB);
}

static void hibvt_i2c_enable(struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_GLB);
	val |= GLB_EN_MASK;
	writel(val, i2c->base + HIBVT_I2C_GLB);
}

static inline void hibvt_i2c_cfg_irq(struct hibvt_i2c_dev *i2c,
					unsigned int flag)
{
	writel(flag, i2c->base + HIBVT_I2C_INTR_EN);
}

static void hibvt_i2c_disable_irq(struct hibvt_i2c_dev *i2c,
						unsigned int flag)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_INTR_EN);
	val &= ~flag;
	writel(val, i2c->base + HIBVT_I2C_INTR_EN);
}

static unsigned int hibvt_i2c_clr_irq(struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_INTR_STAT);
	writel(INTR_ALL_MASK, i2c->base + HIBVT_I2C_INTR_RAW);

	return val;
}

static inline void hibvt_i2c_cmdreg_set(struct hibvt_i2c_dev *i2c,
					unsigned int cmd, unsigned int *offset)
{
	/* the I2C_TIMING_CMD reg offset is (*offset * 4) */
	writel(cmd, i2c->base + HIBVT_I2C_CMD_BASE + *offset * 4);
	(*offset)++;
}

/*
 * config i2c slave addr
 */
static void hibvt_i2c_set_addr(struct hibvt_i2c_dev *i2c)
{
	struct hibvt_i2c_msg *msg = i2c->msg;
	u16 addr;

	if (msg->flags & I2C_M_TEN) {
		/* First byte is 11110XX0 where XX is upper 2 bits */
		addr = ((msg->addr & 0x300) << 1) | 0xf000;
		if (msg->flags & I2C_M_RD)
			addr |= 1 << 8; /* Move Left 8bit */

		/* Second byte is the remaining 8 bits */
		addr |= msg->addr & 0xff;
	} else {
		addr = (msg->addr & 0x7f) << 1;
		if (msg->flags & I2C_M_RD)
			addr |= 1;
	}

	writel(addr, i2c->base + HIBVT_I2C_DATA1);
}

/*
 * Start command sequence
 */
static void hibvt_i2c_init_descart_cmd(struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_CTRL1);
	val |= CTRL1_CMD_START_MASK;
	writel(val, i2c->base + HIBVT_I2C_CTRL1);
}

static int hibvt_i2c_wait_rx_noempty(struct hibvt_i2c_dev *i2c)
{
	unsigned int time_cnt = 0;
	unsigned int val;

	do {
		val = readl(i2c->base + HIBVT_I2C_STAT);
		if (val & STAT_RXF_NOE_MASK)
			return 0;

		udelay(50); /* delay 50us */
	} while (time_cnt++ < I2C_WAIT_TIMEOUT);

	hibvt_i2c_rescue(i2c);

	printf("wait rx no empty timeout, RIS: 0x%x, SR: 0x%x\n",
		   readl(i2c->base + HIBVT_I2C_INTR_RAW), val);
	return -EIO;
}

static int hibvt_i2c_wait_tx_nofull(struct hibvt_i2c_dev *i2c)
{
	unsigned int time_cnt = 0;
	unsigned int val;

	do {
		val = readl(i2c->base + HIBVT_I2C_STAT);
		if (val & STAT_TXF_NOF_MASK)
			return 0;

		udelay(50); /* delay 50us */
	} while (time_cnt++ < I2C_WAIT_TIMEOUT);

	hibvt_i2c_rescue(i2c);

	printf("wait tx no empty timeout, RIS: 0x%x, SR: 0x%x\n",
		   readl(i2c->base + HIBVT_I2C_INTR_RAW), val);
	return -EIO;
}

static int hibvt_i2c_wait_idle(struct hibvt_i2c_dev *i2c)
{
	unsigned int time_cnt = 0;
	unsigned int val;

	do {
		val = readl(i2c->base + HIBVT_I2C_INTR_RAW);
		if (val & (INTR_ABORT_MASK)) {
			printf("wait idle abort!, RIS: 0x%x\n",
				   val);
			return -EIO;
		}

		if (val & INTR_CMD_DONE_MASK)
			return 0;

		udelay(50); /* delay 50us */
	} while (time_cnt++ < I2C_WAIT_TIMEOUT);

	hibvt_i2c_rescue(i2c);

	printf("wait idle timeout, RIS: 0x%x, SR: 0x%x\n",
		   val, readl(i2c->base + HIBVT_I2C_STAT));

	return -EIO;
}

static void hibvt_i2c_set_freq(struct hibvt_i2c_dev *i2c)
{
	unsigned int max_freq, freq;
	unsigned int clk_rate;
	unsigned int val;

	freq = i2c->freq;
	clk_rate = i2c->clk;
	max_freq = clk_rate >> 1;

	if (freq > max_freq) {
		i2c->freq = max_freq;
		freq = i2c->freq;
	}

	if (!freq) {
		printf("hibvt_i2c_set_freq:freq can't be zero!");
		return;
	}

	if (freq <= 100000) { /* 100000 : freq */
		/* 1/2 of the SCL cycle in standard mode. */
		val = clk_rate / (freq * 2);
		writel(val, i2c->base + HIBVT_I2C_SCL_H);
		writel(val, i2c->base + HIBVT_I2C_SCL_L);
	} else {
		/* 36/100 of the SCL cycle in fast mode. */
		val = (clk_rate * 36) / (freq * 100);
		writel(val, i2c->base + HIBVT_I2C_SCL_H);
		/* 64/100  of the SCL cycle in fast mode. */
		val = (clk_rate * 64) / (freq * 100);
		writel(val, i2c->base + HIBVT_I2C_SCL_L);
	}

	val = readl(i2c->base + HIBVT_I2C_GLB);
	val &= ~GLB_SDA_HOLD_MASK;
	val |= ((0xa << GLB_SDA_HOLD_SHIFT) & GLB_SDA_HOLD_MASK);
	writel(val, i2c->base + HIBVT_I2C_GLB);
}

/*
 * set i2c controller TX and RX FIFO water
 */
static inline void hibvt_i2c_set_water(struct hibvt_i2c_dev *i2c)
{
	writel(I2C_TXF_WATER, i2c->base + HIBVT_I2C_TX_WATER);
	writel(I2C_RXF_WATER, i2c->base + HIBVT_I2C_RX_WATER);
}

/*
 * initialise the controller, set i2c bus interface freq
 */
static void hibvt_i2c_hw_init(struct hibvt_i2c_dev *i2c)
{
	hibvt_i2c_disable(i2c);
	hibvt_i2c_disable_irq(i2c, INTR_ALL_MASK);
	hibvt_i2c_set_freq(i2c);
	hibvt_i2c_set_water(i2c);
}

/*
 * hibvt_i2c_cfg_cmd - config i2c controller command sequence
 *
 * After all the timing command is configured,
 * and then start the command, you can i2c communication,
 * and then only need to read and write i2c fifo.
 */
static void hibvt_i2c_cfg_cmd(struct hibvt_i2c_dev *i2c)
{
	struct hibvt_i2c_msg *msg = i2c->msg;
	unsigned int offset = 0;

	if (i2c->msg_idx == 0)
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_S, &offset);
	else
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_RS, &offset);

	if (msg->flags & I2C_M_TEN) {
		if (i2c->msg_idx == 0) {
			hibvt_i2c_cmdreg_set(i2c, CMD_TX_D1_2, &offset);
			hibvt_i2c_cmdreg_set(i2c, CMD_TX_D1_1, &offset);
		} else {
			hibvt_i2c_cmdreg_set(i2c, CMD_TX_D1_2, &offset);
		}
	} else {
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_D1_1, &offset);
	}

	if (msg->flags & I2C_M_IGNORE_NAK)
		hibvt_i2c_cmdreg_set(i2c, CMD_IGN_ACK, &offset);
	else
		hibvt_i2c_cmdreg_set(i2c, CMD_RX_ACK, &offset);

	if (msg->flags & I2C_M_RD) {
		if (msg->len >= 2) { /* 2:len */
			writel(offset, i2c->base + HIBVT_I2C_DST1);
			writel(msg->len - 2, i2c->base + HIBVT_I2C_LOOP1); /* 2: len */
			hibvt_i2c_cmdreg_set(i2c, CMD_RX_FIFO, &offset);
			hibvt_i2c_cmdreg_set(i2c, CMD_TX_ACK, &offset);
			hibvt_i2c_cmdreg_set(i2c, CMD_JMP1, &offset);
		}
		hibvt_i2c_cmdreg_set(i2c, CMD_RX_FIFO, &offset);
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_NACK, &offset);
	} else {
		writel(offset, i2c->base + HIBVT_I2C_DST1);
		writel(msg->len - 1, i2c->base + HIBVT_I2C_LOOP1);
		hibvt_i2c_cmdreg_set(i2c, CMD_UP_TXF, &offset);
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_FIFO, &offset);

		if (msg->flags & I2C_M_IGNORE_NAK)
			hibvt_i2c_cmdreg_set(i2c, CMD_IGN_ACK, &offset);
		else
			hibvt_i2c_cmdreg_set(i2c, CMD_RX_ACK, &offset);

		hibvt_i2c_cmdreg_set(i2c, CMD_JMP1, &offset);
	}

	if ((i2c->msg_idx == (i2c->msg_num - 1)) || (msg->flags & I2C_M_STOP))
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_P, &offset);

	hibvt_i2c_cmdreg_set(i2c, CMD_EXIT, &offset);
}

static int hibvt_i2c_polling_xfer_one_msg(struct hibvt_i2c_dev *i2c)
{
	int status;
	unsigned int val;
	struct hibvt_i2c_msg *msg = i2c->msg;

	hibvt_i2c_enable(i2c);
	hibvt_i2c_clr_irq(i2c);
	hibvt_i2c_set_addr(i2c);
	hibvt_i2c_cfg_cmd(i2c);
	hibvt_i2c_init_descart_cmd(i2c);

	i2c->msg_buf_ptr = 0;

	if (msg->flags & I2C_M_RD) {
		while (i2c->msg_buf_ptr < msg->len) {
			status = hibvt_i2c_wait_rx_noempty(i2c);
			if (status)
				goto end;

			val = readl(i2c->base + HIBVT_I2C_RXF);
			msg->buf[i2c->msg_buf_ptr] = val;
			i2c->msg_buf_ptr++;
		}
	} else {
		while (i2c->msg_buf_ptr < msg->len) {
			status = hibvt_i2c_wait_tx_nofull(i2c);
			if (status)
				goto end;

			val = msg->buf[i2c->msg_buf_ptr];
			writel(val, i2c->base + HIBVT_I2C_TXF);
			i2c->msg_buf_ptr++;
		}
	}

	status = hibvt_i2c_wait_idle(i2c);
end:
	hibvt_i2c_disable(i2c);

	return status;
}

/*
 * Master transfer function
 */
static int hibvt_i2c_xfer(struct hibvt_i2c_msg *msgs, int num)
{
	struct hibvt_i2c_dev *i2c = &i2c_dev;
	int status = -EINVAL;

	if (!msgs || (num <= 0)) {
		printf("msgs == NULL || num <= 0, Invalid argument!\n");
		return -EINVAL;
	}

	i2c->msg = msgs;
	i2c->msg_num = num;
	i2c->msg_idx = 0;

	while (i2c->msg_idx < i2c->msg_num) {
		status = hibvt_i2c_polling_xfer_one_msg(i2c);
		if (status)
			break;
		i2c->msg++;
		i2c->msg_idx++;
	}

	if (!status || i2c->msg_idx > 0)
		status = i2c->msg_idx;

	return status;
}

void i2c_init(int speed, int i2c_num)
{
	if (i2c_num < 0 || i2c_num >= I2C_MAX_NUM) {
		printf("Cannot found I2C[%d]!\n", i2c_num);
		return;
	}

	if (hibvt_i2c_init_desc[i2c_num].flag == I2C_INIT_UNDO) {
		struct hibvt_i2c_dev *i2c = &i2c_dev;

		i2c->base = (void *)(hibvt_i2c_init_desc[i2c_num].ctrl_base);
		i2c->clk = I2C_BUS_CLOCK;
		if (speed <= 0 || speed > MAX_SPEED) {
			printf("Error speed out of range:[0, %d]!\n", MAX_SPEED);
		} else {
			i2c->freq = speed;
			g_i2c_speed = i2c->freq;
		}
		hibvt_i2c_hw_init(i2c);
		hibvt_i2c_init_desc[i2c_num].flag = I2C_INIT_DONE;
		g_i2c_num = i2c_num;
		printf("I2C[%d] init OK!\n", i2c_num);
	} else {
		printf("I2C[%d] had init!\n", i2c_num);
		return;
	}
}

int i2c_probe(unsigned char i2c_num)
{
	printf("init i2c [%d],speed:[%u]\n", i2c_num, g_i2c_speed);
	i2c_init(g_i2c_speed, i2c_num);
	return 0;
}

unsigned int i2c_set_bus_speed(unsigned int speed)
{
	if (g_i2c_num < 0) {
		printf("please i2c probe [num] first!");
		return 1;
	}

	if (g_i2c_speed != speed) {
		g_i2c_speed = speed;
		hibvt_i2c_init_desc[g_i2c_num].flag = I2C_INIT_UNDO;
		printf("Set the i2c speed to %u\n", g_i2c_speed);
		i2c_init(g_i2c_speed, g_i2c_num);
	} else {
		printf("The i2c speed has not changed!speed:%u\n", g_i2c_speed);
	}
	return 0;
}

unsigned int i2c_get_bus_speed(void)
{
	return g_i2c_speed;
}

unsigned int i2c_set_bus_num(int bus_no)
{
	struct hibvt_i2c_dev *i2c = &i2c_dev;

	if (bus_no < 0 || bus_no >= I2C_MAX_NUM) {
		printf("Error! out of range:[0, %d]!\n", I2C_MAX_NUM);
		return 0;
	}
	if (hibvt_i2c_init_desc[bus_no].flag == I2C_INIT_UNDO) {
		i2c_init(g_i2c_speed, bus_no);
	} else {
		g_i2c_num = bus_no;
		i2c->base = (void *)(hibvt_i2c_init_desc[g_i2c_num].ctrl_base);
	}
	return 0;
}

unsigned int i2c_get_bus_num(void)
{
	if (g_i2c_num < 0)
		printf("Please set the I2C device number!\n");

	return g_i2c_num;
}

int i2c_read(unsigned char chip, uint addr, int alen, unsigned char *buffer,
			 int len)
{
	struct hibvt_i2c_dev;
	struct hibvt_i2c_msg msg[2]; /* 2 bit array */
	int num = (__u32)2;
	int len_idx = 1;
	unsigned int cur_addr;
	int ret;
	unsigned char buf[4]; /* 4 bit array */

	memset(buf, 0x0, 4); /* memset the ength is 4 array. */
	msg[0].addr = (chip >> 1);
	msg[0].len = alen;
	msg[0].buf = buf;
	msg[0].flags = 0;

	msg[1].addr = (chip >> 1);
	msg[1].len = len;
	msg[1].buf = buf;
	msg[1].flags = 0;
	msg[1].flags |= I2C_M_RD;

	for (cur_addr = addr; len_idx <= len; cur_addr += 1) {
		if (alen == 2) { /* 2:len */
			buf[0] = (cur_addr >> 8) & 0xff; /* Move Right 8bit */
			buf[1] = cur_addr & 0xff;
		} else {
			buf[0] = cur_addr & 0xff;
		}

		ret = hibvt_i2c_xfer(msg, num);
		if (ret != 2) { /* 2: Return Value */
			printf("i2c read: failed %d\n", ret);
			return 0;
		}

		if (len == 2) /* 2:len */
			*buffer = buf[0] | (buf[1] << 8); /* Move Left 8bit */
		else
			*buffer = buf[0];

		printf("0x%x:0x%x\n", cur_addr, buf[0]);
		len_idx++;
	}
	return 0;
}

int i2c_write(unsigned char chip, uint addr, int alen,
			const unsigned char *buffer, int len)
{
	struct hibvt_i2c_msg msg = {0};
	unsigned char buf[4]; /* 4 bit array */
	int index = 0;
	int ret;

	msg.addr = (chip >> 1);
	msg.len = alen + len;
	msg.buf = buf;
	msg.flags = 0;

	if (alen == 2) { /* 2:len */
		buf[index] = (addr >> 8) & 0xff; /* Move Right 8bit */
		index++;
		buf[index] = addr & 0xff;
		index++;
	} else {
		buf[index] = addr & 0xff;
		index++;
	}

	if (len == 2) { /* 2:len */
		buf[index] = *buffer & 0xff;
		index++;
		buf[index] = (*buffer >> 8) & 0xff; /* Move Right 8bit */
		index++;
	} else {
		buf[index] = *buffer & 0xff;
		index++;
	}

	ret = hibvt_i2c_xfer(&msg, 1);
	if (ret != 1) {
		printf("I2c write: failed %d\n", ret);
		return 1;
	}

	return 0;
}
