/*
 * i2c-hibvt.c
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
#include <asm/io.h>
#include <linux/errno.h>
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

#ifndef bit
#define bit(nr)         (1 << (nr))
#endif
/*
 * I2C Global Config Register -- HIBVT_I2C_GLB
 */
#define GLB_EN_MASK     bit(0)
#define GLB_SDA_HOLD_MASK   0xffff00
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
#define CTRL1_CMD_START_MASK    bit(0)

/*
 * I2C Status Register -- HIBVT_I2C_STAT
 */
#define STAT_RXF_NOE_MASK   bit(16) /* RX FIFO not empty flag */
#define STAT_TXF_NOF_MASK   bit(19) /* TX FIFO not full flag */


/*
 * I2C Interrupt status and mask Register --
 * HIBVT_I2C_INTR_RAW, HIBVT_I2C_STAT, HIBVT_I2C_INTR_STAT
 */
#define INTR_ABORT_MASK     (bit(0) | bit(11))
#define INTR_RX_MASK        bit(2)
#define INTR_TX_MASK        bit(4)
#define INTR_CMD_DONE_MASK  bit(12)
#define INTR_USE_MASK       (INTR_ABORT_MASK | \
				INTR_RX_MASK | \
				INTR_TX_MASK | \
				INTR_CMD_DONE_MASK)
#define INTR_ALL_MASK           0xffffffff

#define I2C_DEFAULT_FREQUENCY   100000
#define I2C_TXF_DEPTH       64
#define I2C_RXF_DEPTH       64
#define I2C_TXF_WATER       32
#define I2C_RXF_WATER       32
#define I2C_WAIT_TIMEOUT    0x400
#define I2C_IRQ_TIMEOUT     (msecs_to_jiffies(1000))

void *memset(void *s, int c, size_t count);

static inline void udelay(unsigned int num)
{
	volatile unsigned int i;

	for (i = 0; i < (100 * num); i++) /* 100: Cycle */
		__asm__ __volatile__("nop");
}

struct i2c_message {
	__u16 chip;             /* slave address */
	__u16 addr;             /* reg address */
	__u16 alen;             /* reg width,1 or 2 */
	__u16 flags;
	__u16 len;              /* msg length,1 or 2 */
	__u8 *buf;              /* pointer to msg data */
#define I2C_M_RD            0x0001  /* read data, from slave to master */
#define I2C_M_IGNORE_NAK    0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_TEN           0x0010  /* this is a ten bit chip address */
#define I2C_M_STOP          0x8000  /* if I2C_FUNC_PROTOCOL_MANGLING */
};

struct hibvt_i2c_dev {
	struct device *dev;
	void *base;
	unsigned int clk;
	unsigned int freq;
};

struct hibvt_i2c_dev i2c_dev = {
	.base = (void *)0x04566000,
	.clk = 50000000,   /* 50000000: clock */
	.freq = I2C_DEFAULT_FREQUENCY,
};

static inline void hibvt_i2c_disable(const struct hibvt_i2c_dev *i2c);
static inline void hibvt_i2c_cfg_irq(struct hibvt_i2c_dev *i2c,
						unsigned int flag);
static inline unsigned int hibvt_i2c_clr_irq(const struct hibvt_i2c_dev *i2c);
static inline void hibvt_i2c_enable(const struct hibvt_i2c_dev *i2c);

#define CHECK_SDA_IN_SHIFT     16
#define GPIO_MODE_SHIFT        8
#define FORCE_SCL_OEN_SHIFT    4
#define FORCE_SDA_OEN_SHIFT    0

static void hibvt_i2c_disable(const struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_GLB);
	val &= ~GLB_EN_MASK;
	writel(val, i2c->base + HIBVT_I2C_GLB);
}

static void hibvt_i2c_enable(const struct hibvt_i2c_dev *i2c)
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

static void hibvt_i2c_disable_irq(const struct hibvt_i2c_dev *i2c,
		unsigned int flag)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_INTR_EN);
	val &= ~flag;
	writel(val, i2c->base + HIBVT_I2C_INTR_EN);
}

static unsigned int hibvt_i2c_clr_irq(const struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_INTR_STAT);
	writel(INTR_ALL_MASK, i2c->base + HIBVT_I2C_INTR_RAW);

	return val;
}

static inline void hibvt_i2c_cmdreg_set(const struct hibvt_i2c_dev *i2c,
					unsigned int cmd, unsigned int *offset)
{
	/* HIBVT_I2C_CMD_BASE + *offset * 4: I2C_TIMING_CMD REG */
	writel(cmd, i2c->base + HIBVT_I2C_CMD_BASE + *offset * 4);
	(*offset)++;
}

/*
 * config i2c slave addr
 */
static void hibvt_i2c_set_addr(const struct hibvt_i2c_dev *i2c,
					struct i2c_message *msg)
{
	u16 addr;

	if (msg->flags & I2C_M_TEN) {
		/* First byte is 11110XX0 where XX is upper 2 bits */
		addr = ((msg->chip & 0x300) << 1) | 0xf000;
		if (msg->flags & I2C_M_RD)
			addr |= 1 << 8; /* Move Right 8bit */

		/* Second byte is the remaining 8 bits */
		addr |= msg->chip & 0xff;
	} else {
		addr = (msg->chip & 0x7f) << 1;
		if (msg->flags & I2C_M_RD)
			addr |= 1;
	}

	writel(addr, i2c->base + HIBVT_I2C_DATA1);
}

/*
 * Start command sequence
 */
static void hibvt_i2c_start_cmd(const struct hibvt_i2c_dev *i2c)
{
	unsigned int val;

	val = readl(i2c->base + HIBVT_I2C_CTRL1);
	val |= CTRL1_CMD_START_MASK;
	writel(val, i2c->base + HIBVT_I2C_CTRL1);
}

static int hibvt_i2c_wait_rx_noempty(const struct hibvt_i2c_dev *i2c)
{
	unsigned int time_cnt = 0;
	unsigned int val;

	do {
		val = readl(i2c->base + HIBVT_I2C_STAT);
		if (val & STAT_RXF_NOE_MASK)
			return 0;

		udelay(50); /* delay 50ms */
	} while (time_cnt++ < I2C_WAIT_TIMEOUT);

	return -EIO;
}

static int hibvt_i2c_wait_tx_nofull(const struct hibvt_i2c_dev *i2c)
{
	unsigned int time_cnt = 0;
	unsigned int val;

	do {
		val = readl(i2c->base + HIBVT_I2C_STAT);
		if (val & STAT_TXF_NOF_MASK)
			return 0;

		udelay(50); /* delay 50ms */
	} while (time_cnt++ < I2C_WAIT_TIMEOUT);

	return -EIO;
}

static int hibvt_i2c_wait_idle(const struct hibvt_i2c_dev *i2c)
{
	unsigned int time_cnt = 0;
	unsigned int val;

	do {
		val = readl(i2c->base + HIBVT_I2C_INTR_RAW);
		if (val & (INTR_ABORT_MASK))
			return -EIO;

		if (val & INTR_CMD_DONE_MASK)
			return 0;

		udelay(50); /* delay 50ms */
	} while (time_cnt++ < I2C_WAIT_TIMEOUT);

	return -EIO;
}

static void hibvt_i2c_set_freq(struct hibvt_i2c_dev *i2c, unsigned int freq)
{
	unsigned int max_freq;
	unsigned int clk_rate;
	unsigned int val;

	clk_rate = i2c->clk;
	max_freq = clk_rate >> 1;

	if (freq > max_freq)
		freq = max_freq;

	i2c->freq = freq;

	val = 0xfa;
	writel(val, i2c->base + HIBVT_I2C_SCL_H);
	writel(val, i2c->base + HIBVT_I2C_SCL_L);

	val = readl(i2c->base + HIBVT_I2C_GLB);
	val &= ~GLB_SDA_HOLD_MASK;
	val |= ((0xa << GLB_SDA_HOLD_SHIFT) & GLB_SDA_HOLD_MASK);
	writel(val, i2c->base + HIBVT_I2C_GLB);
}

/*
 * set i2c controller TX and RX FIFO water
 */
static inline void hibvt_i2c_set_water(const struct hibvt_i2c_dev *i2c,
					unsigned int txf_water_line,
					unsigned int rxf_water_line)
{
	writel(txf_water_line, i2c->base + HIBVT_I2C_TX_WATER);
	writel(rxf_water_line, i2c->base + HIBVT_I2C_RX_WATER);
}

/*
 * initialise the controller, set i2c bus interface freq
 */
static void hibvt_i2c_hw_init(struct hibvt_i2c_dev *i2c)
{
	hibvt_i2c_disable(i2c);
	hibvt_i2c_disable_irq(i2c, INTR_ALL_MASK);
	hibvt_i2c_set_freq(i2c, i2c->freq);
	hibvt_i2c_set_water(i2c, I2C_TXF_WATER, I2C_RXF_WATER);
}

/*
 * hibvt_i2c_cfg_cmd - config i2c controller command sequence
 *
 * After all the timing command is configured,
 * and then start the command, you can i2c communication,
 * and then only need to read and write i2c fifo.
 */
static void hibvt_i2c_cfg_cmd(const struct hibvt_i2c_dev *i2c,
				struct i2c_message *msg, unsigned int index,
				unsigned int num)
{
	unsigned int offset = 0;

	if (index == 0)
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_S, &offset);
	else
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_RS, &offset);

	if (msg->flags & I2C_M_TEN) {
		if (index == 0) {
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

	if ((index == (num - 1)) || (msg->flags & I2C_M_STOP))
		hibvt_i2c_cmdreg_set(i2c, CMD_TX_P, &offset);

	hibvt_i2c_cmdreg_set(i2c, CMD_EXIT, &offset);
}

static int hibvt_i2c_polling_xfer_one_msg(const struct hibvt_i2c_dev *i2c,
		struct i2c_message *msg, unsigned int index, unsigned int num)
{
	int status;
	unsigned int val;
	unsigned int iterator = 0;

	hibvt_i2c_enable(i2c);
	hibvt_i2c_clr_irq(i2c);
	hibvt_i2c_set_addr(i2c, msg);
	hibvt_i2c_cfg_cmd(i2c, msg, index, num);
	hibvt_i2c_start_cmd(i2c);

	if (msg->flags & I2C_M_RD) {
		while (iterator < msg->len) {
			status = hibvt_i2c_wait_rx_noempty(i2c);
			if (status)
				goto end;

			val = readl(i2c->base + HIBVT_I2C_RXF);
			msg->buf[iterator] = val;
			iterator++;
		}
	} else {
		while (iterator < msg->len) {
			status = hibvt_i2c_wait_tx_nofull(i2c);
			if (status)
				goto end;

			val = msg->buf[iterator];
			writel(val, i2c->base + HIBVT_I2C_TXF);
			iterator++;
		}
	}

	status = hibvt_i2c_wait_idle(i2c);
end:
	hibvt_i2c_disable(i2c);

	return status;
}

struct hibvt_i2c_dev *get_i2c_dev_rel_addr(struct hibvt_i2c_dev *addr)
{
	struct hibvt_i2c_dev *abs_addr = NULL;
	struct hibvt_i2c_dev *rel_addr = NULL;
	unsigned int delta = 0;

	asm("ldr %0, =__wcy_pad\n\t"
		"adr %1, __wcy_pad\n\t"
		"sub %2, %0, %1\n\t"
		"__wcy_pad:\n\t"
		"nop"
		:"=r"(abs_addr), "=r"(rel_addr), "=r"(delta));

	abs_addr = addr;
	rel_addr = abs_addr - delta;

	return rel_addr;
}

/*
 * Master transfer function
 */
static int hibvt_i2c_xfer(struct i2c_message *msgs, int num)
{
	struct hibvt_i2c_dev *i2c = get_i2c_dev_rel_addr(&i2c_dev);
	unsigned int index = 0;
	struct i2c_message *msg = msgs;
	int status = -EINVAL;

	if (!msgs || (num <= 0))
		return -EINVAL;

	while (index < num) {
		status = hibvt_i2c_polling_xfer_one_msg(i2c, msg, index, num);
		if (status)
			break;

		msg++;
		index++;
	}

	if (!status || (index > 0))
		status = index;

	return status;
}

void hibvt_i2c_init(void)
{
	struct hibvt_i2c_dev *i2c = get_i2c_dev_rel_addr(&i2c_dev);

	/* i2c6 pinmux */
	writel(0x00400000, 0x045101A0);
	writel(0x000014f3, 0x040580CC);
	writel(0x000014f3, 0x040580D0);

	hibvt_i2c_hw_init(i2c);
}

int i2c_read(unsigned char chip, unsigned int addr, int alen,
			 unsigned char *buffer, int len)
{
	struct i2c_message msg[2]; /* 2 bit array */
	int len_idx = 1;
	int cur_addr, ret;
	unsigned char buf[4] = {0}; /* 4 bit array */

	msg[0].chip = (chip >> 1);
	msg[0].len = alen;
	msg[0].buf = buf;
	msg[0].flags = 0;

	msg[1].chip = (chip >> 1);
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

		ret = hibvt_i2c_xfer(msg, 2); /* 2: msg num */
		if (ret != 2) /* 2: Return Value */
			return 0;

		if (len == 2) /* 2:len */
			*buffer = buf[0] | (buf[1] << 8); /* Move Left 8bit */
		else
			*buffer = buf[0];
		len_idx++;
	}
	return 0;
}

int i2c_write(unsigned char chip, unsigned int addr, int alen,
			 const unsigned char *buffer, int len)
{
	struct i2c_message msg;
	unsigned char  buf[4]; /* 4 layer */
	int index = 0;
	int ret;

	memset(&msg, 0, sizeof(msg));
	msg.chip = (chip >> 1);
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
	if (ret != 1)
		return 1;
	return 0;
}

