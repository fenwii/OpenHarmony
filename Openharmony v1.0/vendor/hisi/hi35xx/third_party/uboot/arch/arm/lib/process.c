/*
 * process.c
 *
 * The file is used for adaptation.
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

#define CFG_MAX_SHUTDOWN       10

static struct shutdown_ctrl {
	int count;
	void (*shutdown[CFG_MAX_SHUTDOWN])(void);
} shutdown_ctrl = {0, {0}, };

void add_shutdown(void (*shutdown)(void))
{
	if (shutdown_ctrl.count >= CFG_MAX_SHUTDOWN) {
		printf("Can't add shutdown function,"
			   "Please increase CFG_MAX_SHUTDOWN count\n");
		return;
	}
	shutdown_ctrl.shutdown[shutdown_ctrl.count++]
		= shutdown;
}

void do_shutdown(void)
{
	int ix;
	for (ix = 0; ix < shutdown_ctrl.count; ix++)
		shutdown_ctrl.shutdown[ix]();
}
