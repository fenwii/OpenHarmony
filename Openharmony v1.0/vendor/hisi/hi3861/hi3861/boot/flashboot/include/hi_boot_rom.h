/*
 * @file hi_boot_rom.h
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @defgroup iot_romboot BootRom */
#ifndef _HI_BOOT_ROM_H_
#define _HI_BOOT_ROM_H_
#include <hi_types.h>
#include <hi_boot_err.h>
#include <hi3861_platform.h>
#include <boot_rom.h>

/** @defgroup iot_reg Registers APIs
* @ingroup  iot_romboot
*/
/**
* @ingroup iot_reg
*
*/
#define hi_reg_write(addr, val)            (*(volatile hi_u32*)(uintptr_t)(addr) = (val))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_read(addr, val)             ((val) = *(volatile hi_u32*)(uintptr_t)(addr))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_write16(addr, val)          (*(volatile hi_u16*)(uintptr_t)(addr) = (val))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_read16(addr, val)           ((val) = *(volatile hi_u16*)(uintptr_t)(addr))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_read_val32(addr)            (*(volatile hi_u32*)(uintptr_t)(addr))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_read_val16(addr)            (*(volatile hi_u16*)(uintptr_t)(addr))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_setbitmsk(addr, msk)        ((hi_reg_read_val32(addr)) |= (msk))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_clrbitmsk(addr, msk)        ((hi_reg_read_val32(addr)) &= ~(msk))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_clrbit(addr, pos)           ((hi_reg_read_val32(addr)) &= ~((hi_u32)(1) << (pos)))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_setbit(addr, pos)           ((hi_reg_read_val32(addr)) |= ((hi_u32)(1) << (pos)))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_clrbits(addr, pos, bits)    (hi_reg_read_val32(addr) &= ~((((hi_u32)1 << (bits)) - 1) << (pos)))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_clrbits16(addr, pos, bits)  (hi_reg_read_val16(addr) &= ~((((unsigned short)1 << (bits)) - 1) << (pos)))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_clrbit16(addr, pos)       ((hi_reg_read_val16(addr)) &= ~((unsigned short)(1) << (pos)))

/**
* @ingroup iot_reg
*
*/
#define hi_reg_setbit16(addr, pos)       ((hi_reg_read_val16(addr)) |= ((unsigned short)(1) << (pos)))

/** @defgroup iot_time time APIs
* @ingroup iot_romboot
*/
/**
* @ingroup  iot_time
* @brief  Delay, in microseconds.CNcomment:延时，毫秒级。CNend
*
* @par 描述:
*           Delay operation implemented by software based on the system clock, blocking the CPU.
CNcomment:延时操作，阻塞CPU。CNend
*
* @attention None
*
* @param  msecs                [IN] type #hi_u32，delay period (unit: millisecond).
CNcomment:延时时间（单位：ms）。CNend
*
* @retval  None
* @par 依赖:
*            @li hi_boot_rom.h：Describes BootRom APIs.CNcomment:文件包含BootRom相关接口。CNend
* @see  None
*/
hi_void mdelay(hi_u32 msecs);

/**
* @ingroup  iot_time
* @brief  Delay, in microseconds.CNcomment:延时，微秒级。CNend
*
* @par 描述:
*           Delay operation implemented by software based on the system clock, blocking the CPU.
CNcomment:延时操作，阻塞CPU。CNend
*
* @attention None
*
* @param  usecs                [IN] type #hi_u32，delay period (unit: microsecond).
CNcomment:延时时间（单位：μs）。CNend
*
* @retval  None
* @par 依赖:
*            @li hi_boot_rom.h：Describes BootRom APIs.CNcomment:文件包含BootRom相关接口。CNend
* @see  None
*/
hi_void udelay(hi_u32 usecs);

extern hi_u32 memcmp(const hi_void *cs, const hi_void *ct, hi_u32 count);

/** @defgroup iot_secure_c Secure C library APIs
* @ingroup iot_romboot
*/
/**
* @ingroup  iot_secure_c
* @brief  Sets the size of the destination buffer to a specific value.
CNcomment:设置目的缓冲区为特定值。CNend
*
* @par 描述: Sets the size of the destination buffer to a specific value.
CNcomment:设置目的缓冲区为特定值。CNend
* @attention None
*
* @param dest     [IN] type #hi_void *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #hi_u32, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param c        [IN] type #hi_u8, Specific value.CNcomment:特定值。CNend
* @param count    [IN] type #hi_u32, Number of specific values set in destination buffer.
CNcomment:目的缓冲区设置特定值的个数。CNend
* @param  check_sum [IN] type #hi_u32，Exclusive or of the above four parameter values,used as security check.
*                 example:check_sum = (uintptr_t)dest ^ (uintptr_t)dest_max ^ (uintptr_t)c ^ (uintptr_t)count.
CNcomment:上面4个参数值的异或,用作安全检查，
示例:check_sum = (uintptr_t)dest ^ (uintptr_t)dest_max ^ (uintptr_t)c ^ (uintptr_t)count。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_boot_rom.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
hi_u32 memset_s(hi_void *dest, hi_u32 dest_max, hi_u8 c, hi_u32 count, hi_u32 check_sum);

/**
* @ingroup  iot_secure_c
* @brief  Copies the data from the source buffer to the destination buffer.
CNcomment:复制源缓冲区的数据到目的缓冲区。CNend
*
* @par 描述: Copies the data from the source buffer to the destination buffer.
CNcomment:复制源缓冲区的数据到目的缓冲区。CNend
* @attention None
*
* @param dest     [IN] type #hi_void *, Destination buffer.CNcomment:目的缓冲区。CNend
* @param dest_max [IN] type #hi_u32, Size of the destination buffer.CNcomment:目的缓冲区大小。CNend
* @param src      [IN] type #const hi_void *, Source buffer.CNcomment:源缓冲区。CNend
* @param count    [IN] type #hi_u32, Number of characters copied from the source buffer.
CNcomment:从源缓冲区中复制的字符数。CNend
* @param  check_sum [IN] type #hi_u32，Exclusive or of the above four parameter values,used as security check.
*               example:check_sum = (uintptr_t)dest ^ (uintptr_t)dest_max ^ (uintptr_t)src ^ (uintptr_t)count.
CNcomment:上面4个参数值的异或,用作安全检查，
示例:check_sum = (uintptr_t)dest ^ (uintptr_t)dest_max ^ (uintptr_t)src ^ (uintptr_t)count。CNend
*
* @retval #EOK Success
* @retval #Other Failure
*
* @par 依赖:
* @li hi_boot_rom.h: This file declares the APIs.CNcomment:该接口声明所在的头文件。CNend
* @see None
*/
hi_u32 memcpy_s(hi_void *dest, hi_u32 dest_max, const hi_void *src, hi_u32 count, hi_u32 check_sum);

/** @defgroup iot_dfx Debug APIs
* @ingroup iot_romboot
*/
/**
 * @ingroup iot_dfx
 *
 * Print error code type, 0x3615 and its previous value cannot be modified.
 CNcomment:打印错误码类型，0x3615及之前的值不可修改。CNend
 */
typedef enum {
    HI_PRINT_ERRNO_UART_INIT = 0x3600,              /* UART authentication initialization failed */
    HI_PRINT_ERRNO_LOADER_ERR = 0x3601,             /* Failed to load loaderboot */
    HI_PRINT_ERRNO_BOOT_DECRYPT_ERR = 0x3602,       /* Boot decryption failed */
    HI_PRINT_ERRNO_BOOT_LEN_ERR = 0x3603,           /* Boot length check failed */
    HI_PRINT_ERRNO_BOOT_HEAD_ERR = 0x3604,          /* Boot header verification failed */
    HI_PRINT_ERRNO_BOOT_SECURE_BOOT_ERR = 0x3605,   /* Secure boot read failed */
    HI_PRINT_ERRNO_BOOT_ROOT_KEY_LEN_ERR = 0x3606,  /* Rootkye length incorrect */
    HI_PRINT_ERRNO_BOOT_ROOT_KEY_ERR = 0x3607,      /* Rootkey certificate failed */
    HI_PRINT_ERRNO_BOOT_READ_ENCPT_ERR = 0x3608,    /* Secure flag read failed */
    HI_PRINT_ERRNO_BOOT_SUB_KEY_LEN_ERR = 0x3609,   /* Subkey length incorrect */
    HI_PRINT_ERRNO_BOOT_SUB_KEY_CAT_ERR = 0x360A,   /* Subkey category is incorrect */
    HI_PRINT_ERRNO_BOOT_SUB_KEY_RSIM_ERR = 0x360B,  /* Subkey rsim verification failed */
    HI_PRINT_ERRNO_BOOT_SUB_KEY_ERR = 0x360C,       /* Subkey authentication failed */
    HI_PRINT_ERRNO_BOOT_CODE_VERIFY_ERR = 0x360D,   /* Code verification failed */
    HI_PRINT_ERRNO_BOOT_DIE_ID_ERR = 0x360E,        /* Die ID verification failed */
    HI_PRINT_ERRNO_BOOT_VER_ERR = 0x360F,           /* Flash boot version number verification failed */
    HI_PRINT_ERRNO_BOOT_GET_TAIL_ERR = 0x3610,      /* Failed to get flash tail address */
    HI_PRINT_ERRNO_BOOT_BACKUP_TAIL_ERR = 0x3611,   /* Backup flash boot magic word and length verification failed */
    HI_PRINT_ERRNO_BOOT_MAIN_CHECK_ERR = 0x3612,    /* Fail to check the integrity of the main flashboot
                                                       in non-secure boot */
    HI_PRINT_ERRNO_BOOT_BACKUP_CHECK_ERR = 0x3613,  /* Fail to check the integrity of the backup flashboot
                                                       in non-secure boot */
    HI_PRINT_ERRNO_MALLOC_EXAUST_ERR = 0x3614,      /* Out of heap memory */
    HI_PRINT_ERRNO_MALLOC_STRUCT_ERR = 0x3615,      /* Heap memory management structure destroyed */
    HI_PRINT_ERRNO_NO_ENCPT_CNT_LEFT_ERR = 0x3616,  /* Flash encryption burn out times */
    HI_PRINT_ERRNO_CRYPTO_PREPARE_ERR = 0x3617,     /* Flash encryption and decryption preparation failed */
    HI_PRINT_ERRNO_CRYPTO_KEY_EMPTY_ERR = 0x3618,   /* Flash encryption and decryption work key is empty */
    HI_PRINT_ERRNO_CRYPTO_KEY_INVALID_ERR = 0x3619, /* Flash encryption and decryption work key is invalid */
    HI_PRINT_ERRNO_CRYPTO_KEY_SAVE_ERR = 0x361A,    /* Flash encryption and decryption work key save failed */
    HI_PRINT_ERRNO_CRYPTO_KEY_DECRYPT_ERR = 0x361B, /* Flash encryption and decryption work key decryption failed */
    HI_PRINT_ERRNO_CRYPTO_FW_DECRYPT_ERR = 0x361C,  /* Flash encryption and decryption kernel encryption failed */
    HI_PRINT_ERRNO_CRYPTO_FW_ENCRYPT_ERR = 0x361D,  /* Flash encryption and decryption kernel decryption failed */
    HI_PRINT_ERRNO_CRYPTO_NV_ENCRYPT_ERR = 0x361E,  /* Flash encryption and decryption NV area encryption failed */
    HI_PRINT_ERRNO_CRYPTO_CHECK_KERNEL_ERR = 0x361F,  /* Flash encryption and decryption check kernel failed */
    HI_PRINT_ERRNO_CRYPTO_KERNEL_ADDR_ERR = 0x3620, /* Flash encryption and decryption check kernel addr failed */
    HI_PRINT_ERRNO_UPG_CRYPTO_PREPARE_ERR = 0x3621, /* Upg file decryption preparation failed */
    HI_PRINT_ERRNO_UPG_CRYPTO_DECRYPT_ERR = 0x3622, /* Upg file decryption failed */
    HI_PRINT_ERRNO_CRYPTO_SALT_EMPTY_ERR = 0x3623,  /* Flash encryption and decryption root key salt is empty */
    HI_PRINT_ERRNO_IDX_MAX,                         /* Error code type maximum */
} hi_print_errno;

/**
* @ingroup  iot_dfx
* @brief  The error code is forced to be printed out in romboot. The hi_print_errno definition cannot be modified.
CNcomment:romboot中强制打印输出错误码，不可修改hi_print_errno定义。CNend
*
* @par 描述:
*           Force to print out error codes to help users locate errors.
CNcomment:强制打印输出错误码，帮助用户定位错误。CNend
*
* @attention None.
*
* @param  print_errno [IN] type #hi_u32, error code.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_puthex|boot_msg0|boot_msg1|boot_msg2|boot_msg4.
*/
hi_void boot_put_errno(hi_u32 print_errno);

/**
* @ingroup  iot_dfx
* @brief  Output hexadecimal number.CNcomment:输出16进制数。CNend
*
* @par 描述:
*           Output hexadecimal number.CNcomment:输出16进制数。CNend
*
* @attention None.
*
* @param  h [IN] type #hi_u32,  Hexadecimal number to output.
* @param  print0 [IN] type #hi_bool, HI_TRUE: fill 0 to 4 bytes when printing. HI_FALSE: do not fill 0 alignment.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_put_errno|boot_msg0|boot_msg1|boot_msg2|boot_msg4.
*/
hi_void boot_puthex(hi_u32 h, hi_bool print0);

/**
* @ingroup  iot_dfx
* @brief  Printout information, string only.CNcomment:打印输出信息，只输出字符串。CNend
*
* @par 描述:
*           Printout information, string only.CNcomment:打印输出信息，只输出字符串。CNend
*
* @attention None.
*
* @param  s [IN] type #hi_char*,  String to output.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_put_errno|boot_puthex|boot_msg1|boot_msg2|boot_msg4.
*/
hi_void boot_msg0(const hi_char *s);

/**
* @ingroup  iot_dfx
* @brief  Print out information, output string and 1 values.CNcomment:打印输出信息，输出字符串及1个数值。CNend
*
* @par 描述:
*           Print out information, output string and 1 values.CNcomment:打印输出信息，输出字符串及1个数值。CNend
*
* @attention None.
*
* @param  s [IN] type #hi_char*,  String to output.
* @param  h [IN] type #hi_u32,  Value to be output, hexadecimal.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_put_errno|boot_puthex|boot_msg0|boot_msg2|boot_msg4.
*/
hi_void boot_msg1(const hi_char *s, hi_u32 h);

/**
* @ingroup  iot_dfx
* @brief  Print out information, output string and 2 values.CNcomment:打印输出信息，输出字符串及2个数值。CNend
*
* @par 描述:
*           Print out information, output string and 2 values.CNcomment:打印输出信息，输出字符串及2个数值。CNend
*
* @attention None.
*
* @param  s [IN] type #hi_char*,  String to output.
* @param  h1 [IN] type #hi_u32,  Value to be output 1, hexadecimal.
* @param  h2 [IN] type #hi_u32,  Value to be output 2, hexadecimal.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_put_errno|boot_puthex|boot_msg0|boot_msg1|boot_msg4.
*/
hi_void boot_msg2(const hi_char *s, hi_u32 h1, hi_u32 h2);

/**
* @ingroup  iot_dfx
* @brief  Print out information, output string and 4 values.CNcomment:打印输出信息，输出字符串及4个数值。CNend
*
* @par 描述:
*           Print out information, output string and 4 values.CNcomment:打印输出信息，输出字符串及4个数值。CNend
*
* @attention None.
*
* @param  s [IN] type #hi_char*,  String to output.
* @param  h1 [IN] type #hi_u32,  Value to be output 1, hexadecimal.
* @param  h2 [IN] type #hi_u32,  Value to be output 2, hexadecimal.
* @param  h3 [IN] type #hi_u32,  Value to be output 3, hexadecimal.
* @param  h4 [IN] type #hi_u32,  Value to be output 4, hexadecimal.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_put_errno|boot_puthex|boot_msg0|boot_msg1|boot_msg2.
*/
hi_void boot_msg4(const hi_char *s, hi_u32 h1, hi_u32 h2, hi_u32 h3, hi_u32 h4);

/** @defgroup iot_uart Uart APIs
* @ingroup iot_romboot
*/
/**
 * @ingroup iot_uart
 *
 * Uart ID. CNcomment:串口号。CNend
 */
typedef enum {
    UART0 = 0,    /* uart0 */
    UART1 = 1,    /* uart1 */
    UART2 = 2,    /* uart2 */
    UART_MAX = 3,
} hi_uart;

/**
 * @ingroup iot_uart
 *
 * Uart parameter struct. CNcomment:串口参数结构体。CNend
 */
typedef struct {
    hi_u32 baudrate;          /* Baud rate */
    hi_uchar databit;         /* 5; 6; 7; 8 */
    hi_uchar stopbit;         /* 1:stop_bit 1;  2: stop_bit 2. */
    hi_uchar parity;          /* 0: None; 1:Odd; 2:Even */
    hi_uchar flow_ctrl;       /* 0: None; 1:rts&&cts. 2:only rts; 3:only cts */
    hi_uchar fifoline_tx_int; /* 0:tx FIFO≤1/8full; 1:tx FIFO≤1/4full; 2:tx FIFO≤1/2full;
                                 3:tx FIFO≤3/4full; 4:tx FIFO≤7/8full */
    hi_uchar fifoline_rx_int; /* 0:rx FIFO≥1/8full; 1:rx FIFO≥1/4full; 2:rx FIFO≥1/2full;
                                 3:rx FIFO≥3/4full; 4:rx FIFO≥7/8full */
    hi_uchar fifoline_rts;    /* 0:rx FIFO≥1/8full; 1:rx FIFO≥1/4full; 2:rx FIFO≥1/2full;
                                 3:rx FIFO≥3/4full; 4:rx FIFO≥7/8full */
    hi_uchar pad;
} uart_param_stru;

/**
* @ingroup  iot_uart
* @brief  Serial output forbidden.CNcomment:串口输出禁言。CNend
*
* @par 描述:
*           Serial output forbidden.CNcomment:串口输出禁言。CNend
*
* @attention None.
*
* @param  None.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_cancel_mute.
*/
hi_void serial_set_mute(hi_void);

/**
* @ingroup  iot_uart
* @brief  Cancel serial output forbidden.CNcomment:串口输出取消禁言。CNend
*
* @par 描述:
*           Cancel serial output forbidden.CNcomment:串口输出取消禁言。CNend
*
* @attention None.
*
* @param  None.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_set_mute.
*/
hi_void serial_cancel_mute(hi_void);

/**
* @ingroup  iot_uart
* @brief  Serial port initialization.CNcomment:串口初始化。CNend
*
* @par 描述:
*           Serial port initialization.CNcomment:串口初始化。CNend
*
* @attention None.
*
* @param  uart_num [IN] type #hi_uart, Uart ID.
* @param  default_uart_param [IN] type #uart_param_stru, Uart parameters.
*
* @retval #HI_ERR_FAILURE Failure.
* @retval #HI_ERR_SUCCESS Success.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_u32 serial_init(hi_uart uart_num, uart_param_stru default_uart_param);

/**
* @ingroup  iot_uart
* @brief  Serial output single character.CNcomment:串口输出单个字符。CNend
*
* @par 描述:
*           Serial output single character.CNcomment:串口输出单个字符。CNend
*
* @attention None.
*
* @param  c [IN] type #const hi_char, Char to output.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_void serial_putc(const hi_char c);

/**
* @ingroup  iot_uart
* @brief  Serial output string.CNcomment:串口输出字符串。CNend
*
* @par 描述:
*           Serial output string.CNcomment:串口输出字符串。CNend
*
* @attention None.
*
* @param  s [IN] type #const hi_char*, String to output.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_void serial_puts(const hi_char *s);

/**
* @ingroup  iot_uart
* @brief  Serial output character buffer, specify buffer length.CNcomment:串口输出字符缓冲区，指定缓冲区长度。CNend
*
* @par 描述:
*           Serial output character buffer, specify buffer length.CNcomment:串口输出字符缓冲区，指定缓冲区长度。CNend
*
* @attention The difference between the serial_puts() function is that the serial_puts function is for strings and
*            stops the output when '\ 0' is encountered. However, this interface is not affected by '\ 0' for a
*            specified length of character buffer.CNcomment:与serial_puts()函数的区别是：serial_puts函数是针对字符串，
*            遇到'\0'后停止输出;而本接口针对指定长度的字符缓冲区，不受'\0'影响。CNend
* @param  buffer [IN] type #const hi_char*,  String to output.
* @param  length [IN] type #hi_s32,          Length of string to be output.
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_void serial_put_buf(const hi_char *buffer, hi_s32 length);

/**
* @ingroup  iot_uart
* @brief  Read a character from the serial port.CNcomment:从串口读取一个字符。CNend
*
* @par 描述:
*           Read a character from the serial port.CNcomment:从串口读取一个字符。CNend
*
* @attention This function is a blocking interface. If the serial port does not receive characters, it will wait.
CNcomment:本函数为阻塞接口，如果串口没有接收到字符，会一直等待。CNend
* @param  None.
*
* @retval #Character    Characters read from serial port.
* @retval #-1           Failure.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_u8 serial_getc(hi_void);

/**
* @ingroup  iot_uart
* @brief  Whether the serial port has characters to be received.CNcomment:串口是否有字符待接收。CNend
*
* @par 描述:
*           Whether the serial port has characters to be received.CNcomment:串口是否有字符待接收。CNend
*
* @attention None.
* @param  None.
*
* @retval #0     Not received date from serial port.
* @retval #1     Received date from serial port.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_s32 serial_tstc(hi_void);

/**
* @ingroup  iot_uart
* @brief  Output hexadecimal number to serial port.CNcomment:向串口输出16进制数。CNend
*
* @par 描述:
*           向串口输出16进制数.CNcomment:向串口输出16进制数。CNend
*
* @attention None.
* @param  h         [IN] type #hi_u32，Hexadecimal number to be output.CNcomment:待输出的16进制数。CNend
* @param  print_all [IN] type #hi_u8 *，Whether to fill in 0, Align according to 4 bytes. 1 : fill, 0 : not to fill.
CNcomment:打印时前面是否补0，按照4字节对齐，1表示补,0表示不补。CNend
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_void serial_puthex(hi_u32 h, hi_bool print_all);

/**
* @ingroup  iot_uart
* @brief  Read a character from the serial port, and end if it is not read after waiting for the specified time.
CNcomment:从串口读取一个字符，等待指定时间后没有读到则结束。CNend
*
* @par 描述:
*           Read a character from the serial port, and end if it is not read after waiting for the specified time.
CNcomment:从串口读取一个字符，等待指定时间后没有读到则结束。CNend
*
* @attention None.
* @param  timeout_us    [IN] type #hi_u32，Specify timeout in us.CNcomment:指定超时时间，单位:us。CNend
* @param  ch            [IN] type #hi_u8 *，Output character.CNcomment:输出字符。CNend
*
* @retval #HI_ERR_FAILURE Failure.
* @retval #HI_ERR_SUCCESS Success.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  serial_init|serial_putc|serial_puts|serial_put_buf|serial_getc|serial_tstc|serial_puthex。
*/
hi_u32 serial_getc_timeout(hi_u32 timeout_us, hi_u8 *ch);

/** @defgroup iot_mem Memory APIs
* @ingroup iot_romboot
*/
/**
* @ingroup  iot_mem
*
* Dynamic memory management module initialization interface function pointer.
CNcomment:动态内存管理模块初始化接口函数指针。CNend
*/
typedef hi_void (*malloc_init_func)(hi_u32 heap_start_addr, hi_u32 heap_end_addr, hi_u32 check_sum);

/**
* @ingroup  iot_mem
*
* Request dynamic memory interface function pointer.CNcomment:申请动态内存接口函数指针。CNend
*/
typedef hi_void *(*malloc_func)(hi_u32 size);

/**
* @ingroup  iot_mem
*
* Release dynamic memory interface function pointer.CNcomment:释放动态内存接口函数指针。CNend
*/
typedef hi_u32 (*free_func)(hi_void *addr);

/**
* @ingroup  iot_mem
*
* Input parameter of hi_register_malloc interface.
*/
typedef struct {
    malloc_init_func init;   /* Initialize heap memory interface */
    malloc_func boot_malloc; /* Request heap memory interface */
    free_func boot_free;     /* Release heap memory interface */
} hi_malloc_func;

/**
* @ingroup  iot_mem
* @brief  To register malloc management related functions, be sure to register before using other interfaces.
CNcomment:注册malloc管理相关函数,务必先注册再使用其他接口。CNend
*
* @par 描述:
*           Support users to adapt memory management functions.CNcomment:支持用户自己适配内存管理函数。CNend
*
* @attention None.
* @param  addr      [IN] type #uintptr_t，Heap start address.CNcomment:堆空间起始地址。CNend
* @param  funcs     [IN] type #const hi_malloc_func *，Request memory related interface register structure pointer.
CNcomment:申请内存相关接口注册结构体指针。CNend
*
* @retval #HI_ERR_FAILURE Failure.
* @retval #HI_ERR_SUCCESS Success.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_malloc_init|boot_malloc|boot_free。
*/
hi_u32 hi_register_malloc(uintptr_t addr, const hi_malloc_func *funcs);

/**
* @ingroup  iot_mem
* @brief  Heap initialize.CNcomment:堆空间初始化。CNend
*
* @par 描述:
*           Heap initialize.CNcomment:堆空间初始化。CNend
*
* @attention None.
* @param  heap_start_addr    [IN] type #uintptr_t，Heap start address.CNcomment:堆空间起始地址。CNend
* @param  heap_end_addr      [IN] type #uintptr_t，Heap end address.CNcomment:堆空间结束地址。CNend
* @param  check_sum          [IN] type #hi_u32，Exclusive or of start address and end address.
CNcomment:起始地址与结束地址的异或。CNend
*
* @retval #HI_ERR_FAILURE Failure.
* @retval #HI_ERR_SUCCESS Success.
* @par 依赖:
*            @li hi_boot_rom.h：Describes Boot APIs.CNcomment:文件用于描述Boot模块接口。CNend
* @see  boot_malloc_init。
*/
hi_void boot_malloc_init(uintptr_t heap_start_addr, uintptr_t heap_end_addr, hi_u32 check_sum);

/**
* @ingroup  iot_mem
* @brief  Dynamically applies for memory.CNcomment:动态申请内存。CNend
*
* @par 描述:
*           Dynamically applies for memory.CNcomment:动态申请内存。CNend
*
* @attention None.
* @param  size    [IN] type #hi_u32，Requested memory size (unit: byte)
CNcomment:申请内存大小（单位：byte）。CNend
*
* @retval #Other    Success
* @retval #HI_NULL  Failure. The memory is insufficient.
* @par 依赖:
*            @li hi_boot_rom.h：Describes memory APIs.CNcomment:文件用于描述内存相关接口。CNend
* @see  boot_free。
*/
hi_void *boot_malloc(hi_u32 size);

/**
* @ingroup  iot_mem
* @brief  Releases the memory that is dynamically applied for.CNcomment:释放动态申请的内存。CNend
*
* @par 描述:
*          Releases the memory that is dynamically applied for.CNcomment:释放动态申请的内存。CNend
*
* @attention None.
* @param  addr    [IN] type #hi_void *，Start address of the requested memory. The validity of the address is ensured
*                 by the caller.CNcomment:所申请内存的首地址，地址合法性由调用者保证。CNend
*
* @retval None.
* @par 依赖:
*            @li hi_boot_rom.h：Describes memory APIs.CNcomment:文件用于描述内存相关接口。CNend
* @see  boot_malloc。
*/
hi_u32 boot_free(hi_void *addr);

/** @defgroup iot_watchdog Watchdog APIs
 * @ingroup iot_romboot
 */
/**
 * @ingroup iot_watchdog
 * The default watchdog configuration time is 26 seconds. The time cannot be modified after romboot is started,
   users can call hi_watchdog_enable interface to reconfigure in flashboot.CNcomment:默认看门狗配置时间为26秒。
   romboot启动后时间不可以修改，用户可以在flashboot中调用hi_watchdog_enable接口重新配置。CNend
 */
#define WDG_TIME_US 26000000 /* 默认看门狗配置时间为26秒 */

/**
* @ingroup  iot_watchdog
* @brief Enables the watchdog.CNcomment:使能看门狗。CNend
*
* @par 描述:
*          Enables the watchdog.CNcomment:使能看门狗。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_boot_rom.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_void hi_watchdog_enable(hi_u32 over_time_us);

/**
* @ingroup  iot_watchdog
* @brief Feeds the watchdog.CNcomment:喂狗。CNend
*
* @par 描述: Feeds the watchdog.CNcomment:喂狗。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_boot_rom.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_void hi_watchdog_feed(hi_void);

/**
* @ingroup  iot_watchdog
* @brief Disables the watchdog.CNcomment:关闭看门狗。CNend
*
* @par 描述:
*           @li Disable the clock enable control of the watchdog.CNcomment:禁止WatchDog时钟使能控制位。CNend
*           @li Mask the watchdog reset function.CNcomment:屏蔽WatchDog复位功能。CNend
*
* @attention None
* @param  None
*
* @retval None
* @par 依赖:
*            @li hi_boot_rom.h：describes the watchdog APIs.CNcomment:文件用于描述看门狗相关接口。CNend
* @see None
*/
hi_void hi_watchdog_disable(hi_void);

/** @defgroup iot_crc16 CRC16 APIs
* @ingroup iot_romboot
*/
/**
* @ingroup  iot_crc16
* @brief  Generates a 16-bit CRC value.CNcomment:生成16位CRC校验值。CNend
*
* @par 描述:
*           Generates a 16-bit CRC value.CNcomment:生成16位CRC校验值。CNend
*
* @attention None
* @param  crc_start         [IN] type #hi_u16，The CRC initial value.CNcomment:CRC初始值。CNend
* @param  buf               [IN] type #hi_u8*，Pointer to the buffer to be verified.
CNcomment:被校验Buffer指针。CNend
* @param  len               [IN] type #hi_u32，Length of the buffer to be verified (unit: Byte).
CNcomment:被校验Buffer长度（单位：byte）。CNend
*
* @retval #HI_ERR_SUCCESS   Success
* @retval #Other            Failure. For details, see hi_boot_err.h.
*
* @par 依赖:
*            @li hi_boot_rom.h：Describes CRC APIs.CNcomment:文件包含CRC校验接口。CNend
* @see  None
*/
hi_u16 hi_crc16(hi_u16 crc_start, hi_u8 *buf, hi_u32 len);

/** @defgroup iot_io IO APIs
 * @ingroup iot_romboot
 */
/**
* @ingroup iot_io
*
* GPIO ID.
*/
typedef enum {
    HI_GPIO_IDX_0,   /* GPIO0 */
    HI_GPIO_IDX_1,   /* GPIO1 */
    HI_GPIO_IDX_2,   /* GPIO2 */
    HI_GPIO_IDX_3,   /* GPIO3 */
    HI_GPIO_IDX_4,   /* GPIO4 */
    HI_GPIO_IDX_5,   /* GPIO5 */
    HI_GPIO_IDX_6,   /* GPIO6 */
    HI_GPIO_IDX_7,   /* GPIO7 */
    HI_GPIO_IDX_8,   /* GPIO8 */
    HI_GPIO_IDX_9,   /* GPIO9 */
    HI_GPIO_IDX_10,  /* GPIO10 */
    HI_GPIO_IDX_11,  /* GPIO11 */
    HI_GPIO_IDX_12,  /* GPIO12 */
    HI_GPIO_IDX_13,  /* GPIO13 */
    HI_GPIO_IDX_14,  /* GPIO14 */
    HI_GPIO_IDX_MAX, /* Maximum value, cannot be used. CNcomment:最大值，不可输入使用。CNend */
} hi_gpio_idx;

/**
 * @ingroup iot_io
 *
 * GPIO pin ID. CNcomment:IO硬件管脚编号。CNend
 */
typedef enum {
    HI_IO_NAME_GPIO_0,  /* GPIO0 */
    HI_IO_NAME_GPIO_1,  /* GPIO1 */
    HI_IO_NAME_GPIO_2,  /* GPIO2 */
    HI_IO_NAME_GPIO_3,  /* GPIO3 */
    HI_IO_NAME_GPIO_4,  /* GPIO4 */
    HI_IO_NAME_GPIO_5,  /* GPIO5 */
    HI_IO_NAME_GPIO_6,  /* GPIO6 */
    HI_IO_NAME_GPIO_7,  /* GPIO7 */
    HI_IO_NAME_GPIO_8,  /* GPIO8 */
    HI_IO_NAME_GPIO_9,  /* GPIO9 */
    HI_IO_NAME_GPIO_10, /* GPIO10 */
    HI_IO_NAME_GPIO_11, /* GPIO11 */
    HI_IO_NAME_GPIO_12, /* GPIO12 */
    HI_IO_NAME_GPIO_13, /* GPIO13 */
    HI_IO_NAME_GPIO_14, /* GPIO14 */
    HI_IO_NAME_SFC_CSN, /* SFC_CSN */
    HI_IO_NAME_SFC_IO1, /* SFC_IO1 */
    HI_IO_NAME_SFC_IO2, /* SFC_IO2 */
    HI_IO_NAME_SFC_IO0, /* SFC_IO0 */
    HI_IO_NAME_SFC_CLK, /* SFC_CLK */
    HI_IO_NAME_SFC_IO3, /* SFC_IO3 */
    HI_IO_NAME_MAX,
} hi_io_name;

/**
 * @ingroup iot_io
 *
 * GPIO pull-up configuration.CNcomment:IO上下拉功能CNend
 */
typedef enum {
    HI_IO_PULL_NONE,    /*  No pull. CNcomment:无拉。CNend */
    HI_IO_PULL_UP,      /*  pull up. CNcomment:上拉。CNend */
    HI_IO_PULL_DOWN,    /*  pull down. CNcomment:下拉。CNend */
    HI_IO_PULL_MAX,     /*  Invalid value. CNcomment:无效值。CNend */
} hi_io_pull;

/**
 * @ingroup iot_io
 *
 * GPIO_0 pin function.CNcomment:GPIO_0管脚功能。CNend
 */
typedef enum {
    HI_IO_FUNC_GPIO_0_GPIO,
    HI_IO_FUNC_GPIO_0_UART1_TXD = 2,
    HI_IO_FUNC_GPIO_0_SPI0_CK,
    HI_IO_FUNC_GPIO_0_JTAG_TDO,
    HI_IO_FUNC_GPIO_0_PWM3_OUT,
    HI_IO_FUNC_GPIO_0_I2C1_SDA,
} hi_io_func_gpio_0;

/**
* @ingroup iot_io
*
* GPIO_1 pin function.CNcomment:GPIO_1管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_1_GPIO,
    HI_IO_FUNC_GPIO_1_UART1_RXD = 2,
    HI_IO_FUNC_GPIO_1_SPI0_RXD,
    HI_IO_FUNC_GPIO_1_JTAG_TCK,
    HI_IO_FUNC_GPIO_1_PWM4_OUT,
    HI_IO_FUNC_GPIO_1_I2C1_SCL,
    HI_IO_FUNC_GPIO_1_BT_FREQ,
} hi_io_func_gpio_1;

/**
* @ingroup iot_io
*
* GPIO_2 pin function.CNcomment:GPIO_2管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_2_GPIO,
    HI_IO_FUNC_GPIO_2_UART1_RTS_N = 2,
    HI_IO_FUNC_GPIO_2_SPI0_TXD,
    HI_IO_FUNC_GPIO_2_JTAG_TRSTN,
    HI_IO_FUNC_GPIO_2_PWM2_OUT,
    HI_IO_FUNC_GPIO_2_SSI_CLK = 7,
} hi_io_func_gpio_2;

/**
* @ingroup iot_io
*
* GPIO_3 pin function.CNcomment:GPIO_3管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_3_GPIO,
    HI_IO_FUNC_GPIO_3_UART0_TXD,
    HI_IO_FUNC_GPIO_3_UART1_CTS_N,
    HI_IO_FUNC_GPIO_3_SPI0_CSN,
    HI_IO_FUNC_GPIO_3_JTAG_TDI,
    HI_IO_FUNC_GPIO_3_PWM5_OUT,
    HI_IO_FUNC_GPIO_3_I2C1_SDA,
    HI_IO_FUNC_GPIO_3_SSI_DATA,
} hi_io_func_gpio_3;

/**
* @ingroup iot_io
*
* GPIO_4 pin function.CNcomment:GPIO_4管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_4_GPIO,
    HI_IO_FUNC_GPIO_4_UART0_RXD = 2,
    HI_IO_FUNC_GPIO_4_JTAG_TMS = 4,
    HI_IO_FUNC_GPIO_4_PWM1_OUT,
    HI_IO_FUNC_GPIO_4_I2C1_SCL,
} hi_io_func_gpio_4;

/**
* @ingroup iot_io
*
* GPIO_5 pin function.CNcomment:GPIO_5管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_5_GPIO,
    HI_IO_FUNC_GPIO_5_UART1_RXD = 2,
    HI_IO_FUNC_GPIO_5_SPI0_CSN,
    HI_IO_FUNC_GPIO_5_PWM2_OUT = 5,
    HI_IO_FUNC_GPIO_5_I2S0_MCLK,
    HI_IO_FUNC_GPIO_5_BT_STATUS,
} hi_io_func_gpio_5;

/**
* @ingroup iot_io
*
* GPIO_6 pin function.CNcomment:GPIO_6管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_6_GPIO,
    HI_IO_FUNC_GPIO_6_UART1_TXD = 2,
    HI_IO_FUNC_GPIO_6_SPI0_CK,
    HI_IO_FUNC_GPIO_6_PWM3_OUT = 5,
    HI_IO_FUNC_GPIO_6_I2S0_TX,
    HI_IO_FUNC_GPIO_6_COEX_SWITCH,
} hi_io_func_gpio_6;

/**
* @ingroup iot_io
*
* GPIO_7 pin function.CNcomment:GPIO_7管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_7_GPIO,
    HI_IO_FUNC_GPIO_7_UART1_CTS_N = 2,
    HI_IO_FUNC_GPIO_7_SPI0_RXD,
    HI_IO_FUNC_GPIO_7_PWM0_OUT = 5,
    HI_IO_FUNC_GPIO_7_I2S0_BCLK,
    HI_IO_FUNC_GPIO_7_BT_ACTIVE,
} hi_io_func_gpio_7;

/**
* @ingroup iot_io
*
* GPIO_8 pin function.CNcomment:GPIO_8管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_8_GPIO,
    HI_IO_FUNC_GPIO_8_UART1_RTS_N = 2,
    HI_IO_FUNC_GPIO_8_SPI0_TXD,
    HI_IO_FUNC_GPIO_8_PWM1_OUT = 5,
    HI_IO_FUNC_GPIO_8_I2S0_WS,
    HI_IO_FUNC_GPIO_8_WLAN_ACTIVE,
} hi_io_func_gpio_8;

/**
* @ingroup iot_io
*
* GPIO_9 pin function.CNcomment:GPIO_9管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_9_GPIO,
    HI_IO_FUNC_GPIO_9_I2C0_SCL,
    HI_IO_FUNC_GPIO_9_UART2_RTS_N,
    HI_IO_FUNC_GPIO_9_SDIO_D2,
    HI_IO_FUNC_GPIO_9_SPI1_TXD,
    HI_IO_FUNC_GPIO_9_PWM0_OUT,
    HI_IO_FUNC_GPIO_9_I2S0_MCLK = 7,
} hi_io_func_gpio_9;

/**
* @ingroup iot_io
*
* GPIO_10 pin function.CNcomment:GPIO_10管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_10_GPIO,
    HI_IO_FUNC_GPIO_10_I2C0_SDA,
    HI_IO_FUNC_GPIO_10_UART2_CTS_N,
    HI_IO_FUNC_GPIO_10_SDIO_D3,
    HI_IO_FUNC_GPIO_10_SPI1_CK,
    HI_IO_FUNC_GPIO_10_PWM1_OUT,
    HI_IO_FUNC_GPIO_10_I2S0_TX = 7,
} hi_io_func_gpio_10;

/**
* @ingroup iot_io
*
* GPIO_11 pin function.CNcomment:GPIO_11管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_11_GPIO,
    HI_IO_FUNC_GPIO_11_UART2_TXD = 2,
    HI_IO_FUNC_GPIO_11_SDIO_CMD,
    HI_IO_FUNC_GPIO_11_SPI1_RXD,
    HI_IO_FUNC_GPIO_11_PWM2_OUT,
    HI_IO_FUNC_GPIO_11_RF_TX_EN_EXT,
    HI_IO_FUNC_GPIO_11_I2S0_RX,
} hi_io_func_gpio_11;

/**
* @ingroup iot_io
*
* GPIO_12 pin function.CNcomment:GPIO_12管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_12_GPIO,
    HI_IO_FUNC_GPIO_12_UART2_RXD = 2,
    HI_IO_FUNC_GPIO_12_SDIO_CLK,
    HI_IO_FUNC_GPIO_12_SPI1_CSN,
    HI_IO_FUNC_GPIO_12_PWM3_OUT,
    HI_IO_FUNC_GPIO_12_RF_RX_EN_EXT,
    HI_IO_FUNC_GPIO_12_I2S0_BCLK,
} hi_io_func_gpio_12;

/**
* @ingroup iot_io
*
* GPIO_13 pin function.CNcomment:GPIO_13管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_13_SSI_DATA,
    HI_IO_FUNC_GPIO_13_UART0_TXD,
    HI_IO_FUNC_GPIO_13_UART2_RTS_N,
    HI_IO_FUNC_GPIO_13_SDIO_D0,
    HI_IO_FUNC_GPIO_13_GPIO,
    HI_IO_FUNC_GPIO_13_PWM4_OUT,
    HI_IO_FUNC_GPIO_13_I2C0_SDA,
    HI_IO_FUNC_GPIO_13_I2S0_WS,
} hi_io_func_gpio_13;

/**
* @ingroup iot_io
*
* GPIO_14 pin function.CNcomment:GPIO_14管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_GPIO_14_SSI_CLK,
    HI_IO_FUNC_GPIO_14_UART0_RXD,
    HI_IO_FUNC_GPIO_14_UART2_CTS_N,
    HI_IO_FUNC_GPIO_14_SDIO_D1,
    HI_IO_FUNC_GPIO_14_GPIO,
    HI_IO_FUNC_GPIO_14_PWM5_OUT,
    HI_IO_FUNC_GPIO_14_I2C0_SCL,
} hi_io_func_gpio_14;

/**
* @ingroup iot_io
*
* SFC_CSN pin function.CNcomment:SFC_CSN管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_SFC_CSN_SFC_CSN,
    HI_IO_FUNC_SFC_CSN_SDIO_D2,
    HI_IO_FUNC_SFC_CSN_GPIO9,
    HI_IO_FUNC_SFC_CSN_SPI0_TXD = 4,
} hi_io_func_sfc_csn;

/**
* @ingroup iot_io
*
* SFC_DO pin function.CNcomment:SFC_DO管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_SFC_IO_1_SFC_DO,
    HI_IO_FUNC_SFC_IO_1_SDIO_D3,
    HI_IO_FUNC_SFC_IO_1_GPIO10,
    HI_IO_FUNC_SFC_IO_1_SPI0_CK = 4,
} hi_io_func_sfc_io_1;

/**
* @ingroup iot_io
*
* SFC_WPN pin function.CNcomment:SFC_WPN管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_SFC_IO_2_SFC_WPN,
    HI_IO_FUNC_SFC_IO_2_SDIO_CMD,
    HI_IO_FUNC_SFC_IO_2_GPIO11,
    HI_IO_FUNC_SFC_IO_2_RF_TX_EN_EXT,
    HI_IO_FUNC_SFC_IO_2_SPI0_RXD,
} hi_io_func_sfc_io_2;

/**
* @ingroup iot_io
*
* SFC_DI pin function.CNcomment:SFC_DI管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_SFC_IO_0_SFC_DI,
    HI_IO_FUNC_SFC_IO_0_SDIO_CLK,
    HI_IO_FUNC_SFC_IO_0_GPIO12,
    HI_IO_FUNC_SFC_IO_0_RF_RX_EN_EXT,
    HI_IO_FUNC_SFC_IO_0_SPI0_CSN,
} hi_io_func_sfc_io_0;

/**
* @ingroup iot_io
*
* SFC_CLK pin function.CNcomment:SFC_CLK管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_SFC_CLK_SFC_CLK,
    HI_IO_FUNC_SFC_CLK_SDIO_D0,
    HI_IO_FUNC_SFC_CLK_GPIO13,
    HI_IO_FUNC_SFC_CLK_SSI_DATA = 4,
} hi_io_func_sfc_clk;

/**
* @ingroup iot_io
*
* SFC_HOLDN pin function.CNcomment:SFC_HOLDN管脚功能。CNend
*/
typedef enum {
    HI_IO_FUNC_SFC_IO_3_SFC_HOLDN,
    HI_IO_FUNC_SFC_IO_3_SDIO_D1,
    HI_IO_FUNC_SFC_IO_3_GPIO14,
    HI_IO_FUNC_SFC_IO_3_SSI_CLK = 4,
} hi_io_func_sfc_io_3;

/**
* @ingroup  iot_io
* @brief Sets the I/O multiplexing.CNcomment:配置某个IO的复用功能。CNend
*
* @par 描述:
*           Sets the I/O multiplexing.CNcomment:配置某个IO的复用功能。CNend
*
* @attention None
* @param  id  [IN] type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  val [IN] type #hi_u8，I/O multiplexing.See the functions below: CNcomment:IO复用功能。
根据待设置的硬件管脚，从如下枚举中选择相应功能。CNend
                        hi_io_func_gpio_0,
                        hi_io_func_gpio_1,
                        hi_io_func_gpio_2,
                        hi_io_func_gpio_3,
                        hi_io_func_gpio_4,
                        hi_io_func_gpio_5,
                        hi_io_func_gpio_6,
                        hi_io_func_gpio_7,
                        hi_io_func_gpio_8,
                        hi_io_func_gpio_9,
                        hi_io_func_gpio_10,
                        hi_io_func_gpio_11,
                        hi_io_func_gpio_12,
                        hi_io_func_gpio_13,
                        hi_io_func_gpio_14,
                        hi_io_func_sfc_csn,
                        hi_io_func_sfc_io_1,
                        hi_io_func_sfc_io_2,
                        hi_io_func_sfc_io_0,
                        hi_io_func_sfc_clk,
                        hi_io_func_sfc_io_3
*
* @retval #HI_ERR_SUCCESS       Success
* @retval #HI_ERR_GPIO_INVALID_PARAMETER     Failure. Input invalid.
* @par 依赖:
*           @li hi_boot_rom.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  hi_io_set_func。
*/
hi_u32 hi_io_set_func(hi_io_name id, hi_u8 val);

/**
* @ingroup  iot_io
* @brief Enables the I/O pull-up.CNcomment:设置某个IO上下拉功能。CNend
*
* @par 描述:
*           Enables the I/O pull-up.CNcomment:设置某个IO上下拉功能。CNend
*
* @attention None
* @param  id  [IN]  type #hi_io_name，I/O index.CNcomment:硬件管脚。CNend
* @param  val [IN]  type #hi_io_pull，I/O pull-up enable.CNcomment:待设置的上下拉状态。CNend
*
* @retval #HI_ERR_SUCCESS       Success
* @retval #HI_ERR_GPIO_INVALID_PARAMETER     Failure. Input invalid.
* @par 依赖:
*           @li hi_boot_rom.h：Describes I/O APIs.CNcomment:文件用于描述IO相关接口。CNend
* @see  hi_io_get_pull。
*/
hi_u32 hi_io_set_pull(hi_io_name id, hi_io_pull val);
#endif

