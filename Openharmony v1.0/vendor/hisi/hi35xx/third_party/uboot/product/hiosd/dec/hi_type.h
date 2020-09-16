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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Description: jpegd type header file.
 */

#ifndef __HI_TYPE_H__
#define __HI_TYPE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* ----------------------------------------------*
 * const defination                             *
 * ---------------------------------------------- */
typedef enum {
    HI_FALSE = 0,
    HI_TRUE = 1,
} hi_bool;

#ifndef NULL
#define NULL       0L
#endif

#define HI_NULL    0L
#define HI_SUCCESS 0
#define HI_FAILURE (-1)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */
