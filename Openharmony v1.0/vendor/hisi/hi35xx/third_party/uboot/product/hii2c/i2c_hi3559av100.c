/*
* Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
*
* This program is free software; you can redistribute  it and/or modify it
* under  the terms of  the GNU General Public License as published by the
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

#define I2C_MAX_NUM     12
#define I2C0_REG_BASE   0x12110000
#define I2C1_REG_BASE   0x12111000
#define I2C2_REG_BASE   0x12112000
#define I2C3_REG_BASE   0x12113000
#define I2C4_REG_BASE   0x12114000
#define I2C5_REG_BASE   0x12115000
#define I2C6_REG_BASE   0x12116000
#define I2C7_REG_BASE   0x12117000
#define I2C8_REG_BASE   0x12118000
#define I2C9_REG_BASE   0x12119000
#define I2C10_REG_BASE  0x1211a000
#define I2C11_REG_BASE  0x1211b000

#define I2C_BUS_CLOCK   mhz(50)

struct i2c_init_desc hibvt_i2c_init_desc[] = {
	i2c_desc(I2C0_REG_BASE),
	i2c_desc(I2C1_REG_BASE),
	i2c_desc(I2C2_REG_BASE),
	i2c_desc(I2C3_REG_BASE),
	i2c_desc(I2C4_REG_BASE),
	i2c_desc(I2C5_REG_BASE),
	i2c_desc(I2C6_REG_BASE),
	i2c_desc(I2C7_REG_BASE),
	i2c_desc(I2C8_REG_BASE),
	i2c_desc(I2C9_REG_BASE),
	i2c_desc(I2C10_REG_BASE),
	i2c_desc(I2C11_REG_BASE),
	i2c_desc(0),
};

