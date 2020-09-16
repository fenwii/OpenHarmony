/*
 * match_table.c
 *
 * Files related to the matching table.
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

#include <linux/string.h>

#include <match_table.h>

/*****************************************************************************/
int reg2type(struct match_reg_type *table, int length, int reg, int def)
{
	while (length-- > 0) {
		if (table->reg == reg)
			return table->type;
		table++;
	}
	return def;
}

int type2reg(struct match_reg_type *table, int length, int type, int def)
{
	while (length-- > 0) {
		if (table->type == type)
			return table->reg;
		table++;
	}
	return def;
}

int str2type(struct match_type_str *table, int length, const char *str,
			 int size, int def)
{
	while (length-- > 0) {
		if (!strncmp(table->str, str, size))
			return table->type;
		table++;
	}
	return def;
}

const char *type2str(struct match_type_str *table, int length, int type,
					 const char *def)
{
	while (length-- > 0) {
		if (table->type == type)
			return table->str;
		table++;
	}
	return def;
}

int match_reg_to_type(struct match_t *table, int nr_table, int reg, int def)
{
	while (nr_table-- > 0) {
		if (table->reg == reg)
			return table->type;
		table++;
	}
	return def;
}

int match_type_to_reg(struct match_t *table, int nr_table, int type, int def)
{
	while (nr_table-- > 0) {
		if (table->type == type)
			return table->reg;
		table++;
	}
	return def;
}

int match_data_to_type(struct match_t *table, int nr_table, const char *data,
					   int size, int def)
{
	while (nr_table-- > 0) {
		if (!memcmp(table->data, data, size))
			return table->type;
		table++;
	}
	return def;
}

void *match_type_to_data(struct match_t *table, int nr_table, int type,
						 void *def)
{
	while (nr_table-- > 0) {
		if (table->type == type)
			return table->data;
		table++;
	}
	return def;
}

