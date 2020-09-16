#ifndef __SYS_H__
#define __SYS_H__
#include "types.h"
static inline void writel(u32 val, unsigned long int addr)
{
    (*(volatile u32*) (addr)) = (val);
}

static inline void writew(u16 val, unsigned long int addr)
{
    (*(volatile u16*) (addr)) = (val);
}

static inline void writeb(u8 val, unsigned long int addr)
{
    (*(volatile u8*) (addr)) = (val);
}

static inline u32 readl(unsigned long int addr)
{
    return (*(volatile u32*) (addr));
}

static inline u16 readw(unsigned long int addr)
{
    return (*(volatile u16*) (addr));
}

static inline u8 readb(unsigned long int addr)
{
    return (*(volatile u8*) (addr));
}

/* Set the bits of addr to 1, which in mask is 1 */
static inline void set_bits(u32 mask, unsigned long int addr)
{
    (*(volatile u32*) (addr)) |= mask;
}

/* Clear the bits of addr to 0, which in mask is 1 */
static inline void clr_bits(u32 mask, unsigned long int addr)
{
    (*(volatile u32*) (addr)) &= ~(mask);
}

/* Return True if all the bits of addr are 1, which is 1 in mask.
   Else, return False. */
static inline u32 is_bits_set(u32 mask, unsigned long int addr)
{
    return (((*(volatile u32*) (addr)) & (mask)) == (mask));
}
#endif /* end of __SYS_H__ */
