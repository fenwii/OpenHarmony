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
 * Description: jpegd entry header file.
 */
#ifndef __JPEGD_ENTRY_H__
#define __JPEGD_ENTRY_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */
#define ENV_BUF_LEN			32
unsigned long get_hilogo(void);
unsigned long get_jpeg_size_val(void);
unsigned long get_video_data_base(void);
unsigned long get_jpegd_emar_buf(void);
unsigned int get_output_format(void);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif /* _JPEGD_ENTRY_H_ */
