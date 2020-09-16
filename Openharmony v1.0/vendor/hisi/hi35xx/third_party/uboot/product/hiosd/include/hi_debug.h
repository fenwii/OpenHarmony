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

#ifndef __HI_DEBUG_H__
#define __HI_DEBUG_H__

#include "hi_type.h"
#include "common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HI_DBG_EMERG      0   /* system is unusable                   */
#define HI_DBG_ALERT      1   /* action must be taken immediately     */
#define HI_DBG_CRIT       2   /* critical conditions                  */
#define HI_DBG_ERR        3   /* error conditions                     */
#define HI_DBG_WARN       4   /* warning conditions                   */
#define HI_DBG_NOTICE     5   /* normal but significant condition     */
#define HI_DBG_INFO       6   /* informational                        */
#define HI_DBG_DEBUG      7   /* debug-level messages                 */

#define HI_PRINT      printf

#define HI_ASSERT(expr)
#define HI_TRACE(level, enModId, fmt...)

#define HI_ERR_TRACE(mod, fmt...) printf(fmt)
#define HI_WARN_TRACE(mod, fmt...)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_DEBUG_H__ */
