/**
 * @defgroup math Math
 * @ingroup libm
 */

#ifndef _MATH_H
#define _MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define __NEED_float_t
#define __NEED_double_t
#include <bits/alltypes.h>

#if 100*__GNUC__+__GNUC_MINOR__ >= 303
#define NAN       __builtin_nanf("")
#define INFINITY  __builtin_inff()
#else
#define NAN       (0.0f/0.0f)
#define INFINITY  1e5000f
#endif

#define HUGE_VALF INFINITY
#define HUGE_VAL  ((double)INFINITY)
#define HUGE_VALL ((long double)INFINITY)

#define MATH_ERRNO  1
#define MATH_ERREXCEPT 2
#define math_errhandling 2

#define FP_ILOGBNAN (-1-0x7fffffff)
#define FP_ILOGB0 FP_ILOGBNAN

#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

#ifdef __FP_FAST_FMA
#define FP_FAST_FMA 1
#endif

#ifdef __FP_FAST_FMAF
#define FP_FAST_FMAF 1
#endif

#ifdef __FP_FAST_FMAL
#define FP_FAST_FMAL 1
#endif

int __fpclassify(double);
int __fpclassifyf(float);
int __fpclassifyl(long double);

static __inline unsigned __FLOAT_BITS(float __f)
{
	union {float __f; unsigned __i;} __u;
	__u.__f = __f;
	return __u.__i;
}
static __inline unsigned long long __DOUBLE_BITS(double __f)
{
	union {double __f; unsigned long long __i;} __u;
	__u.__f = __f;
	return __u.__i;
}

#define fpclassify(x) ( \
	sizeof(x) == sizeof(float) ? __fpclassifyf(x) : \
	sizeof(x) == sizeof(double) ? __fpclassify(x) : \
	__fpclassifyl(x) )

#define isinf(x) ( \
	sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) == 0x7f800000 : \
	sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL>>1) == 0x7ffULL<<52 : \
	__fpclassifyl(x) == FP_INFINITE)

#define isnan(x) ( \
	sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) > 0x7f800000 : \
	sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL>>1) > 0x7ffULL<<52 : \
	__fpclassifyl(x) == FP_NAN)

#define isnormal(x) ( \
	sizeof(x) == sizeof(float) ? ((__FLOAT_BITS(x)+0x00800000) & 0x7fffffff) >= 0x01000000 : \
	sizeof(x) == sizeof(double) ? ((__DOUBLE_BITS(x)+(1ULL<<52)) & -1ULL>>1) >= 1ULL<<53 : \
	__fpclassifyl(x) == FP_NORMAL)

#define isfinite(x) ( \
	sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) < 0x7f800000 : \
	sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & -1ULL>>1) < 0x7ffULL<<52 : \
	__fpclassifyl(x) > FP_INFINITE)

/* cmath use using ::isnan, need isnan deferance. */
#ifdef __LITEOS__
int (isnan)(double);
#endif

int __signbit(double);
int __signbitf(float);
int __signbitl(long double);

#define signbit(x) ( \
	sizeof(x) == sizeof(float) ? (int)(__FLOAT_BITS(x)>>31) : \
	sizeof(x) == sizeof(double) ? (int)(__DOUBLE_BITS(x)>>63) : \
	__signbitl(x) )

#define isunordered(x,y) (isnan((x)) ? ((void)(y),1) : isnan((y)))

#define __ISREL_DEF(rel, op, type) \
static __inline int __is##rel(type __x, type __y) \
{ return !isunordered(__x,__y) && __x op __y; }

__ISREL_DEF(lessf, <, float_t)
__ISREL_DEF(less, <, double_t)
__ISREL_DEF(lessl, <, long double)
__ISREL_DEF(lessequalf, <=, float_t)
__ISREL_DEF(lessequal, <=, double_t)
__ISREL_DEF(lessequall, <=, long double)
__ISREL_DEF(lessgreaterf, !=, float_t)
__ISREL_DEF(lessgreater, !=, double_t)
__ISREL_DEF(lessgreaterl, !=, long double)
__ISREL_DEF(greaterf, >, float_t)
__ISREL_DEF(greater, >, double_t)
__ISREL_DEF(greaterl, >, long double)
__ISREL_DEF(greaterequalf, >=, float_t)
__ISREL_DEF(greaterequal, >=, double_t)
__ISREL_DEF(greaterequall, >=, long double)

#define __tg_pred_2(x, y, p) ( \
	sizeof((x)+(y)) == sizeof(float) ? p##f(x, y) : \
	sizeof((x)+(y)) == sizeof(double) ? p(x, y) : \
	p##l(x, y) )

#define isless(x, y)            __tg_pred_2(x, y, __isless)
#define islessequal(x, y)       __tg_pred_2(x, y, __islessequal)
#define islessgreater(x, y)     __tg_pred_2(x, y, __islessgreater)
#define isgreater(x, y)         __tg_pred_2(x, y, __isgreater)
#define isgreaterequal(x, y)    __tg_pred_2(x, y, __isgreaterequal)

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the arc cosine of x; that is the value whose cosine is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double On success, this function returns the arc cosine of x in radians;
 * the return value is in the range [0, pi].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +1, +0 is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If x is outside the range [-1, 1], a domain error occurs, and a NaN is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  asin | atan | atan2 | cos | sin | tan
 *
 */
double      acos(double);

/**
 * @ingroup  math
 * @par Description:
 * The function calculates the arc cosine of x; that is the value whose cosine is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, the function returns the arc cosine of x in radians;
 * the return value is in the range [0, pi].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +1, +0 is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If x is outside the range [-1, 1], a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see asin | atan | atan2 | cos | sin | tan
 *
 */
float       acosf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the arc cosine of x; that is the value whose cosine is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" On success, this function returns the arc cosine of x in radians;
 * the return value is in the range [0, pi].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +1, +0 is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If x is outside the range [-1, 1], a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  asin | atan | atan2 | cos | sin | tan
 *
 */
long double acosl(long double);
/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic cosine of x; that is the value whose hyperbolic cosine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the inverse hyperbolic cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +1, +0 is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is less than 1, a domain error occurs, and the functions return a NaN.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  asinh | atanh | cosh | sinh | tanh
 *
 */
double      acosh(double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic cosine of x; that is the value whose hyperbolic cosine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function calculates the inverse hyperbolic cosine of x; that is the value
 * whose hyperbolic cosine is x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +1, +0 is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If x is less than 1, a domain error occurs, and the functions return a NaN.\n
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  asinh | atanh | cosh | sinh | tanh
 *
 */
float       acoshf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic cosine of x; that is the value whose hyperbolic cosine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the inverse hyperbolic cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +1, +0 is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is less than 1, a domain error occurs, and the functions return a NaN.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  asinh | atanh | cosh | sinh | tanh
 *
 */
long double acoshl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the arc sine of x; that is the value whose sine is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double On success, the function returns the principal value of the arc sine of x in radians;
 * the return value is in the range [-pi/2, pi/2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is outside the range [-1, 1], a domain error occurs, and a NaN is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | atan | atan2 | cos | sin | tan
 *
 */
double      asin(double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the arc sine of x; that is the value whose sine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, the function returns the principal value of the arc sine of x in radians;
 * the return value is in the range [-pi/2, pi/2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is outside the range [-1, 1], a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | atan | atan2 | cos | sin | tan
 *
 */
float       asinf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the arc sine of x; that is the value whose sine is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" On success, the function returns the principal value of the arc sine of x in radians;
 * the return value is in the range [-pi/2, pi/2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is outside the range [-1, 1], a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | atan | atan2 | cos | sin | tan
 *
 */
long double asinl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic sine of x; that is the value whose hyperbolic sine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, the function returns the inverse hyperbolic sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | atanh | cosh | sinh | tanh
 *
 */
double      asinh(double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic sine of x; that is the value whose hyperbolic sine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, these functions return the inverse hyperbolic sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | atanh | cosh | sinh | tanh
 *
 */
float       asinhf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic sine of x; that is the value whose hyperbolic sine is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, the function returns the inverse hyperbolic sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | atanh | cosh | sinh | tanh
 *
 */
long double asinhl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the principal value of the arc tangent of x; that is the value whose tangent is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double On success, the function returns the principal value of the arc tangent of x in radians;
 *the return value is in the range [-pi/2, pi/2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +pi/2 (-pi/2) is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan2 | cos | sin | tan
 *
 */
double      atan(double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the principal value of the arc tangent of x; that is the value whose tangent is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float On success, the function returns the principal value of the arc tangent of x in radians;
 * the return value is in the range [-pi/2, pi/2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +pi/2 (-pi/2) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see acos | asin | atan2 | cos | sin | tan
 *
 */
float       atanf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the principal value of the arc tangent of x; that is the value whose tangent is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" On success, the function returns the principal value of the arc tangent of x in radians; the return value is in the range [-pi/2, pi/2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +pi/2 (-pi/2) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan2 | cos | sin | tan
 *
 */
long double atanl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the principal value of the arc tangent of y/x,
 * using the signs of the two arguments to determine the quadrant of the result.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, these functions return the principal value of the arc tangent
 * of y/x in radians; the return value is in the range [-pi, pi].\n
 * If y is +0 (-0) and x is less than 0, +pi (-pi) is returned.\n
 * If y is +0 (-0) and x is greater than 0, +0 (-0) is returned.\n
 * If y is less than 0 and x is +0 or -0, -pi/2 is returned.\n
 * If y is greater than 0 and x is +0 or -0, pi/2 is returned.\n
 * If either x or y is NaN, a NaN is returned.\n
 * If y is +0 (-0) and x is -0, +pi (-pi) is returned.\n
 * If y is +0 (-0) and x is +0, +0 (-0) is returned.\n
 * If y is a finite value greater (less) than 0, and x is negative infinity, +pi (-pi) is returned.\n
 * If y is a finite value greater (less) than 0, and x is positive infinity, +0 (-0) is returned.\n
 * If y is positive infinity (negative infinity), and x is finite, pi/2 (-pi/2) is returned.\n
 * If y is positive infinity (negative infinity) and x is negative infinity, +3 *pi/4 (-3 *pi/4) is returned.\n
 * If y is positive infinity (negative infinity) and x is positive infinity, +pi/4 (-pi/4) is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | cos | sin | tan
 *
 */
double      atan2(double, double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the principal value of the arc tangent of y/x,
 * using the signs of the two arguments to determine the quadrant of the result.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, the function returns the principal value of the arc tangent of y/x in radians;
 * the return value is in the range [-pi, pi].\n
 * If y is +0 (-0) and x is less than 0, +pi (-pi) is returned.\n
 * If y is +0 (-0) and x is greater than 0, +0 (-0) is returned.\n
 * If y is less than 0 and x is +0 or -0, -pi/2 is returned.\n
 * If y is greater than 0 and x is +0 or -0, pi/2 is returned.\n
 * If either x or y is NaN, a NaN is returned.\n
 * If y is +0 (-0) and x is -0, +pi (-pi) is returned.\n
 * If y is +0 (-0) and x is +0, +0 (-0) is returned.\n
 * If y is a finite value greater (less) than 0, and x is negative infinity, +pi (-pi) is returned.\n
 * If y is a finite value greater (less) than 0, and x is positive infinity, +0 (-0) is returned.\n
 * If y is positive infinity (negative infinity), and x is finite, pi/2 (-pi/2) is returned.\n
 * If y is positive infinity (negative infinity) and x is negative infinity, +3 *pi/4 (-3 *pi/4) is returned.\n
 * If y is positive infinity (negative infinity) and x is positive infinity, +pi/4 (-pi/4) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see acos | asin | atan | cos | sin | tan
 *
 */
float       atan2f(float, float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the principal value of the arc tangent of y/x,
 * using the signs of the two arguments to determine the quadrant of the result.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, these functions return the principal value of the arc tangent of y/x in radians;
 * the return value is in the range [-pi, pi].\n
 * If y is +0 (-0) and x is less than 0, +pi (-pi) is returned.\n
 * If y is +0 (-0) and x is greater than 0, +0 (-0) is returned.\n
 * If y is less than 0 and x is +0 or -0, -pi/2 is returned.\n
 * If y is greater than 0 and x is +0 or -0, pi/2 is returned.\n
 * If either x or y is NaN, a NaN is returned.\n
 * If y is +0 (-0) and x is -0, +pi (-pi) is returned.\n
 * If y is +0 (-0) and x is +0, +0 (-0) is returned.\n
 * If y is a finite value greater (less) than 0, and x is negative infinity, +pi (-pi) is returned.\n
 * If y is a finite value greater (less) than 0, and x is positive infinity, +0 (-0) is returned.\n
 * If y is positive infinity (negative infinity), and x is finite, pi/2 (-pi/2) is returned.\n
 * If y is positive infinity (negative infinity) and x is negative infinity, +3 *pi/4 (-3 *pi/4) is returned.\n
 * If y is positive infinity (negative infinity) and x is positive infinity, +pi/4 (-pi/4) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | cos | sin | tan
 *
 */
long double atan2l(long double, long double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic tangent of x; that is the value whose hyperbolic tangent is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the inverse hyperbolic tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is +1 or -1, a pole error occurs, and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL,
 * respectively, with the mathematically correct sign.\n
 * If the absolute value of x is greater than 1, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  acosh | asinh | cosh | sinh | tanh
 *
 */
double      atanh(double);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic tangent of x; that is the value whose hyperbolic tangent is x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function returns the inverse hyperbolic tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is +1 or -1, a pole error occurs, and the functions return HUGE_VAL,
 * HUGE_VALF, or HUGE_VALL, respectively, with the mathematically correct sign.\n
 * If the absolute value of x is greater than 1, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  acosh | asinh | cosh | sinh | tanh
 *
 */
float       atanhf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function calculates the inverse hyperbolic tangent of x; that is the value whose hyperbolic tangent is x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the inverse hyperbolic tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is +1 or -1, a pole error occurs, and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the mathematically correct sign.\n
 * If the absolute value of x is greater than 1, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  acosh | asinh | cosh | sinh | tanh
 *
 */
long double atanhl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the (real) cube root of x. This function cannot fail; every representable
 * real value has a representable real cube root.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the cube root of x.\n
 * If x is +0, -0, positive infinity, negative infinity, or NaN, x is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  pow | sqrt
 *
 */
double      cbrt(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the (real) cube root of x. This function cannot fail; every
 * representable real value has a representable real cube root.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function returns the cube root of x.\n
 * If x is +0, -0, positive infinity, negative infinity, or NaN, x is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  pow | sqrt
 *
 */
float       cbrtf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the (real) cube root of x. This function cannot fail; every representable real value has a representable real cube root.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the cube root of x.\n
 * If x is +0, -0, positive infinity, negative infinity, or NaN, x is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  pow | sqrt
 *
 */
long double cbrtl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the smallest integral value that is not less than x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double This function returns the ceiling of x.\n
 * If x is integral, +0, -0, NaN, or infinite, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  floor | lrint | nearbyint | rint | round | trunc
 *
 */
double      ceil(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the smallest integral value that is not less than x.
 *
 * @retval
 * #float  This function returns the ceiling of x.\n
 * If x is integral, +0, -0, NaN, or infinite, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  floor | lrint | nearbyint | rint | round | trunc
 *
 */
float       ceilf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the smallest integral value that is not less than x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" This function returns the ceiling of x.\n
 * If x is integral, +0, -0, NaN, or infinite, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  floor | lrint | nearbyint | rint | round | trunc
 *
 */
long double ceill(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns a value whose absolute value matches that of x,
 * but whose sign bit matches that of y.
 * For example, copysign(42.0, -1.0) and copysign(-42.0, -1.0) both return -42.0.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns a value whose magnitude is taken from x
 * and whose sign is taken from y.\n
 * If x is a NaN, a NaN with the sign bit of y is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  signbit
 *
 */
double      copysign(double, double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns a value whose absolute value matches that of x,
 * but whose sign bit matches that of y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns a value whose magnitude is taken from x
 * and whose sign is taken from y.\n
 * If x is a NaN, a NaN with the sign bit of y is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  signbit
 *
 */
float       copysignf(float, float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns a value whose absolute value matches that of x,
 * but whose sign bit matches that of y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns a value whose magnitude is taken from x
 * and whose sign is taken from y.\n
 * If x is a NaN, a NaN with the sign bit of y is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  signbit
 *
 */
long double copysignl(long double, long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the cosine of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | sin | sincos | tan
 *
 */
double      cos(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the cosine of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function return the cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | sin | sincos | tan
 *
 */
float       cosf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the cosine of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | sin | sincos | tan
 *
 */
long double cosl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic cosine of x, which is defined mathematically as:
 * cosh(x) = (exp(x) + exp(-x)) / 2
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double On success, this function return the hyperbolic cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 or -0, 1 is returned.\n
 * If x is positive infinity or negative infinity, positive infinity is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL,
 * +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | asinh | atanh | sinh | tanh
 *
 */
double      cosh(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic cosine of x, which is defined mathematically as:
 * cosh(x) = (exp(x) + exp(-x)) / 2
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function return the hyperbolic cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 or -0, 1 is returned.\n
 * If x is positive infinity or negative infinity, positive infinity is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL,
 * +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see acosh | asinh | atanh | sinh | tanh
 *
 */
float       coshf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic cosine of x, which is defined mathematically as:
 * cosh(x) = (exp(x) + exp(-x)) / 2
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" On success, this function return the hyperbolic cosine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 or -0, 1 is returned.\n
 * If x is positive infinity or negative infinity, positive infinity is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL, +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | asinh | atanh | sinh | tanh
 *
 */
long double coshl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the error function of x, defined as erf(x) = 2/sqrt(pi) * integral
 * from 0 to x of exp(-t *t) dt.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the error function of x, a value in the range [-1, 1].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +1 (-1) is returned.\n
 * If x is subnormal, a range error occurs, and the return value is 2 *x/sqrt(pi).\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  erfc | exp
 *
 */
double      erf(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the error function of x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the error function of x, a value in the range [-1, 1].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +1 (-1) is returned.\n
 * If x is subnormal, a range error occurs, and the return value is 2 *x/sqrt(pi).\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  erfc | exp
 *
 */
float       erff(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the error function of x, defined as erf(x) = 2/sqrt(pi) * integral from 0 to x of exp(-t *t) dt.
 *
 * @attention
 * <ul>
 * <li> The erfc(), erfcf(), and erfcl() functions are provided to avoid the loss accuracy that would occur for the calculation 1-erf(x) for large values of x
 * (for  which the value of erf(x) approaches 1).</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the error function of x, a value in the range [-1, 1].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +1 (-1) is returned.\n
 * If x is subnormal, a range error occurs, and the return value is 2 *x/sqrt(pi).\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  erfc | exp
 *
 */
long double erfl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the complementary error function of x, that is, 1.0 - erf(x).
 *
 * @attention
 * <ul>
 * <li> The erfc(), erfcf(), and erfcl() functions are provided to avoid the loss accuracy
 * that would occur for the calculation 1-erf(x) for large values of x
 * (for which the value of erf(x) approaches 1).</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the complementary error function of x, a value in the range [0,2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 or -0, 1 is returned.\n
 * If x is positive infinity, +0 is returned.\n
 * If x is negative infinity, +2 is returned.\n
 * If the function result underflows and produces an unrepresentable value, the return value is 0.0.\n
 * If the function result underflows but produces a representable (i.e., subnormal) value,
 * that value is returned, and a range error occurs.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  erf | exp
 *
 */
double      erfc(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the complementary error function of x, that is, 1.0 - erf(x).
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the complementary error function of x, a value in the range [0,2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 or -0, 1 is returned.\n
 * If x is positive infinity, +0 is returned.\n
 * If x is negative infinity, +2 is returned.\n
 * If the function result underflows and produces an unrepresentable value, the return value is 0.0.\n
 * If the function result underflows but produces a representable (i.e., subnormal) value,
 * that value is returned, and a range error occurs.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  erf | exp
 *
 */
float       erfcf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the complementary error function of x, that is, 1.0 - erf(x).
 *
 * @attention
 * <ul>
 * <li> The erfc(), erfcf(), and erfcl() functions are provided to avoid the loss accuracy that would occur for the calculation 1-erf(x) for large values of x
 * (for which the value of erf(x) approaches 1).</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the complementary error function of x, a value in the range [0,2].\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 or -0, 1 is returned.\n
 * If x is positive infinity, +0 is returned.\n
 * If x is negative infinity, +2 is returned.\n
 * If the function result underflows and produces an unrepresentable value, the return value is 0.0.\n
 * If the function result underflows but produces a representable (i.e., subnormal) value, that value is returned, and a range error occurs.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  erf | exp
 *
 */
long double erfcl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the value of e (the base of natural logarithms) raised to the power of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the exponential value of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is negative infinity, +0 is returned.\n
 * If the result underflows, a range error occurs, and zero is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL, +HUGE_VALF,
 * or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | exp2 | sqrt
 *
 */
double      exp(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the value of e (the base of natural logarithms) raised to the power of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function returns the exponential value of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is negative infinity, +0 is returned.\n
 * If the result underflows, a range error occurs, and zero is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL,
 * +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | exp | exp2 | sqrt
 *
 */
float       expf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the value of e (the base of natural logarithms) raised to the power of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the exponential value of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is negative infinity, +0 is returned.\n
 * If the result underflows, a range error occurs, and zero is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL, +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | exp | exp2 | sqrt
 *
 */
long double expl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the value of 2 raised to the power of x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double On success, the function returns the base-2 exponential value of x.\n
 * For various special cases, including the handling of infinity and NaN, as well as
 * overflows and underflows, see exp().\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see cbrt | exp | sqrt
 *
 */
double      exp2(double);
float       exp2f(float);
long double exp2l(long double);

/**
 * @ingroup  math
 * @par Description:
 * The function returns a value equivalent to
 * exp(x) - 1
 * The result is computed in a way that is accurate even if the value of x is near zero.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns exp(x) - 1.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is negative infinity, -1 is returned.\n
 * If the result overflows, a range error occurs, and the function returns -HUGE_VAL,
 * -HUGE_VALF, or -HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see exp | log | log1p
 *
 */
double      expm1(double);

/**
 * @ingroup  math
 * @par Description:
 * The function returns a value equivalent to
 * exp(x) - 1
 * The result is computed in a way that is accurate even if the value of x is near zero-a case where exp(x)-1  would
 * be inaccurate due to subtraction of two numbers that are nearly equal.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns exp(x) - 1.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is negative infinity, -1 is returned.\n
 * If the result overflows, a range error occurs, and the function returns -HUGE_VAL,
 * -HUGE_VALF, or -HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see exp | log | log1p
 *
 */
float       expm1f(float);
long double expm1l(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the absolute value of the floating-point number x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  This function returns the absolute value of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is -0, +0 is returned.\n
 * If x is negative infinity or positive infinity, positive infinity is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ceil | floor | rint
 *
 */
double      fabs(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the absolute value of the floating-point number x.
 *
 * @retval
 * #float This function returns the absolute value of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is -0, +0 is returned.\n
 * If x is negative infinity or positive infinity, positive infinity is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see ceil | floor | rint
 *
 */
float       fabsf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the absolute value of the floating-point number x.
 *
 * @retval "long double" This function returns the absolute value of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is -0, +0 is returned.\n
 * If x is negative infinity or positive infinity, positive infinity is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see ceil | floor | rint
 *
 */
long double fabsl(long double);

double      fdim(double, double);
float       fdimf(float, float);
long double fdiml(long double, long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the largest integral value that is not greater than x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double This function returns the floor of x.\n
 * If x is integral, +0, -0, NaN, or an infinity, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | lrint | nearbyint | rint | round | trunc
 *
 */
double      floor(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the largest integral value that is not greater than x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float  This function returns the floor of x.\n
 * If x is integral, +0, -0, NaN, or an infinity, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | lrint | nearbyint | rint | round | trunc
 *
 */
float       floorf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the largest integral value that is not greater than x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" this function returns the floor of x. If x is integral, +0, -0, NaN, or an infinity, x itself is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ceil | lrint | nearbyint | rint | round | trunc
 *
 */
long double floorl(long double);

double      fma(double, double, double);
float       fmaf(float, float, float);
long double fmal(long double, long double, long double);

double      fmax(double, double);
float       fmaxf(float, float);
long double fmaxl(long double, long double);

double      fmin(double, double);
float       fminf(float, float);
long double fminl(long double, long double);

/**
 * @ingroup  math
 * @par Description:
 * The function computes the floating-point remainder of dividing x by div. The return value is x - n * div,
 * where n is the quotient of x / div, rounded toward zero to an integer.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, the function returns the value x - n *div, for some integer n,
 * such that the returned value has the same sign as x and a magnitude less than
 * the magnitude of div.\n
 * If x or div is a NaN, a NaN is returned.\n
 * If x is an infinity, a domain error occurs, and a NaN is returne.\n
 * If div is zero, a domain error occurs, and a NaN is returned.\n
 * If x is +0 (-0), and div is not zero, +0 (-0) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  remainder
 *
 */
double      fmod(double, double);

/**
 * @ingroup  math
 * @par Description:
 * The function computes the floating-point remainder of dividing x by div. The return value is x - n * div,
 * where n is the quotient of x / div, rounded toward zero to an integer.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, these functions return the value x - n *div, for some integer n,
 * such that the returned value has the same sign as x and a magnitude less than
 * the magnitude of div.\n
 * If x is a NaN, a NaN with the sign bit of div is returned.\n
 * If x is an infinity, a domain error occurs, and a NaN is returned.\n
 * If y is zero, a domain error occurs, and a NaN is returned.\n
 * If x is +0 (-0), and div is not zero, +0 (-0) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  remainder
 *
 */
float       fmodf(float, float);

/**
 * @ingroup  math
 * @par Description:
 * The function computes the floating-point remainder of dividing x by div. The return value is x - n * div,
 * where n is the quotient of x / div, rounded toward zero to an integer.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" On success, these functions return the value x - n*div, for some integer n,
 * such that the returned value has the same sign as x and a magnitude less than
 * the magnitude of div.\n
 * If x is a NaN, a NaN with the sign bit of div is returned.\n
 * If x is an infinity, a domain error occurs, and a NaN is returned.\n
 * If y is zero, a domain error occurs, and a NaN is returned.\n
 * If x is +0 (-0), and div is not zero, +0 (-0) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  remainder
 *
 */
long double fmodl(long double, long double);

/**
 * @ingroup  math
 * @par Description:
 * This function is used to split the number x into a normalized fraction and an exponent which is stored in eptr.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double This function returns the normalized fraction. If the argument x is not zero, the normalized
 * fraction is x times a power of two, and its absolute
 * value is always in the range 1/2 (inclusive) to 1(exclusive), that is, [0.5,1).\n
 * If x is zero, then the normalized fraction is zero and zero is stored in eptr.\n
 * If x is a NaN, a NaN is returned, and the value of *eptr is unspecified.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned,
 * and the value of *eptr is unspecified.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ldexp | modf
 *
 */
double      frexp(double, int *);

/**
 * @ingroup  math
 * @par Description:
 * This function is used to split the number x into a normalized fraction and an exponent which is stored in eptr.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float This function returns the normalized fraction. If the argument x is not zero,
 * the normalized fraction is x times a power of two, and its absolute
 * value is always in the range 1/2 (inclusive) to 1(exclusive), that is, [0.5,1).\n
 * If x is zero, then the normalized fraction is zero and zero is stored in eptr.\n
 * If x is a NaN, a NaN is returned, and the value of *eptr is unspecified.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned,
 * and the value of *eptr is unspecified.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ldexp | modf
 *
 */
float       frexpf(float, int *);

/**
 * @ingroup  math
 * @par Description:
 * This function is used to split the number x into a normalized fraction and an exponent which is stored in eptr.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" This function returns the normalized fraction. If the argument x is not zero, the normalized fraction is x times a power of two, and its absolute
 * value is always in the range 1/2 (inclusive) to 1(exclusive), that is, [0.5,1).\n
 * If x is zero, then the normalized fraction is zero and zero is stored in eptr.\n
 * If x is a NaN, a NaN is returned, and the value of *eptr is unspecified.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned, and the value of *eptr is unspecified.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ldexp | modf
 *
 */
long double frexpl(long double, int *);

/**
 * @ingroup  math
 * @par Description:
 * The function returns sqrt(x *x+y *y). This is the length of the hypotenuse of a right-angled triangle
 * with sides of length x and y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the length of a right-angled triangle with sides of length x and y.\n
 * If x or y is an infinity, positive infinity is returned.\n
 * If x or y is a NaN, and the other argument is not an infinity, a NaN is returned.\n
 * If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF,
 * or HUGE_VALL, respectively.\n
 * If both arguments are subnormal, and the result is subnormal, a range error occurs,
 * and the correct result is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see sqrt
 *
 */
double      hypot(double, double);
float       hypotf(float, float);

/**
 * @ingroup  math
 * @par Description:
 * The function returns sqrt(x*x+y*y). This is the length of the hypotenuse of a right-angled triangle
 * with sides of length x and y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the length of a right-angled triangle with sides of length x and y.\n
 * If x or y is an infinity, positive infinity is returned.\n
 * If x or y is a NaN, and the other argument is not an infinity, a NaN is returned.\n
 * If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF,
 * or HUGE_VALL, respectively.\n
 * If both arguments are subnormal, and the result is subnormal, a range error occurs,
 * and the correct result is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see sqrt
 *
 */
long double hypotl(long double, long double);

int         ilogb(double);
int         ilogbf(float);
int         ilogbl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the result of multiplying the floating-point number x by 2 raised to the power n.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function return x * (2^n).\n
 * If n is zero, then x is returned.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 * If the result underflows, a range error occurs, and zero is returned.\n
 * If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL,
 * respectively, with a sign the same as x.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  frexp | modf | scalbln
 *
 */
double      ldexp(double, int);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the result of multiplying the floating-point number x by 2 raised to the power exp.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function return x * (2^exp).\n
 * If exp is zero, then x is returned.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 * If the result underflows, a range error occurs, and zero is returned.\n
 * If the result overflows, a range error occurs, and the functions return
 * HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with a sign the same as x.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  frexp | modf | scalbln
 *
 */
float       ldexpf(float, int);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the result of multiplying the floating-point number x by 2 raised to the power n.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function return x * (2^n).\n
 * If n is zero, then x is returned.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 * If the result underflows, a range error occurs, and zero is returned.\n
 * If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with a sign the same as x.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  frexp | modf | scalbln
 *
 */
long double ldexpl(long double, int);

double      lgamma(double);
float       lgammaf(float);
long double lgammal(long double);

/**
 * @ingroup  math
 * @par Description:
 * The function rounds its argument to the nearest integer value, using the current rounding direction.
 * Note that unlike the rint() family of functions, the return type of the function differs from that
 * of their arguments.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long long" The function returns the rounded integer value. If x is a NaN or an infinity,
 * or the rounded value is too large to be stored in a long
 * (long long in the case of the ll * functions), then a domain error occurs,
 * and the return value is unspecified.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lround | nearbyint | rint | round
 *
 */
long long   llrint(double);
long long   llrintf(float);
long long   llrintl(long double);

long long   llround(double);
long long   llroundf(float);
long long   llroundl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the natural logarithm of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the natural logarithm of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is 1, the result is +0.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is zero, then a pole error occurs, and the functions return -HUGE_VAL,
 * -HUGE_VALF, or -HUGE_VALL, respectively.\n
 * If x is negative (including negative infinity), then a domain error occurs,
 * and a NaN (not a number) is returned.\n
 *
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log10 | log1p | log2 | sqrt
 *
 */
double      log(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the natural logarithm of x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function returns the natural logarithm of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is 1, the result is +0.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is zero, then a pole error occurs, and the functions return
 * -HUGE_VAL, -HUGE_VALF, or -HUGE_VALL, respectively.\n
 * If x is negative (including negative infinity), then a domain error occurs,
 * and a NaN (not a number) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log10 | log1p | log2 | sqrt
 *
 */
float       logf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the natural logarithm of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the natural logarithm of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is 1, the result is +0.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is zero, then a pole error occurs, and the functions return -HUGE_VAL, -HUGE_VALF, or -HUGE_VALL, respectively.\n
 * If x is negative (including negative infinity), then a domain error occurs, and a NaN (not a number) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log10 | log1p | log2 | sqrt
 *
 */
long double logl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the base 10 logarithm of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the base 10 logarithm of x.\n
 * For special cases, including where x is 0, 1, negative, infinity, or NaN, see log.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log | log2 | sqrt
 *
 */
double      log10(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the base 10 logarithm of x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the base 10 logarithm of x.\n
 * <ul>For special cases, including where x is 0, 1, negative, infinity, or NaN, see log.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see cbrt | log | log2 | sqrt
 *
 */
float       log10f(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the base 10 logarithm of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the base 10 logarithm of x.\n
 * <ul>For special cases, including where x is 0, 1, negative, infinity, or NaN, see log.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log | log2 | sqrt
 *
 */
long double log10l(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns a value equivalent to log (1 + x).
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the natural logarithm of (1 + x).\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is -1, a pole error occurs, and the functions return -HUGE_VAL,
 * -HUGE_VALF, or -HUGE_VALL, respectively.\n
 * If x is less than -1 (including negative infinity), a domain error occurs,
 * and a NaN (not a number) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  exp | expm1 | log
 *
 */
double      log1p(double);

/**
 * @ingroup  math
 * @par Description:
 * The function return a value equivalent to
 *           log (1 + x)
 * The result is computed in a way that is accurate even if the value of x is near zero.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, the function returns the natural logarithm of (1 + x).\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is -1, a pole error occurs, and the functions return -HUGE_VAL, -HUGE_VALF, or -HUGE_VALL, respectivel.\n
 * If x is less than -1 (including negative infinity), a domain error occurs, and a NaN (not a number) is returned.\n
 *
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see exp | expm1 | log
 *
 */
float       log1pf(float);
long double log1pl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the base 2 logarithm of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double On success, the function returns the base 2 logarithm of x.
 * For special cases, including where x is 0, 1, negative, infinity, or NaN, see log().
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log | log10 | sqrt
 *
 */
double      log2(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the base 2 logarithm of x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function returns the base 2 logarithm of x.\n
 * For special cases, including where x is 0, 1, negative, infinity, or NaN, see log.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log | log10 | sqrt
 *
 */
float       log2f(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the base 2 logarithm of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" On success, the function returns the base 2 logarithm of x. For special cases, including where x is 0, 1, negative, infinity, or NaN, see log().
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | log | log10 | sqrt
 *
 */
long double log2l(long double);

double      logb(double);
float       logbf(float);
long double logbl(long double);

long        lrint(double);
long        lrintf(float);
long        lrintl(long double);

long        lround(double);
long        lroundf(float);
long        lroundl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function breaks the argument x into an integral part and a fractional part,
 * each of which has the same sign as x.
 * The integral part is stored in the location pointed to by iptr.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  This function returns the fractional part of x.\n
 * If x is a NaN, a NaN is returned, and *iptr is set to a NaN.\n
 * If x is positive infinity (negative infinity), +0 (-0) is returned,
 * and *iptr is set to positive infinity (negative infinity).\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  frexp | ldexp
 *
 */
double      modf(double, double *);

/**
 * @ingroup  math
 * @par Description:
 * This function breaks the argument x into an integral part and a fractional part,
 * each of which has the same sign as x.
 * The integral part is stored in the location pointed to by iptr.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float This function returns the fractional part of x.\n
 * If x is a NaN, a NaN is returned, and *iptr is set to a NaN.\n
 * If x is positive infinity (negative infinity), +0 (-0) is returned, and *iptr
 * is set to positive infinity (negative infinity).\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  frexp | ldexp
 *
 */
float       modff(float, float *);

/**
 * @ingroup  math
 * @par Description:
 * This function breaks the argument x into an integral part and a fractional part, each of which has the same sign as x.
 * The integral part is stored in the location pointed to by iptr.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  This function returns the fractional part of x.\n
 * If x is a NaN, a NaN is returned, and *iptr is set to a NaN.\n
 * If x is positive infinity (negative infinity), +0 (-0) is returned, and *iptr is set to positive infinity (negative infinity).\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  frexp | ldexp
 *
 */
long double modfl(long double, long double *);

/**
 * @ingroup  math
 * @par Description:
 * The function returns a representation (determined by __kind) of a quiet NaN. If the implementation does not support
 * quiet NaNs, the function returns zero.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double It returns a representation (determined by __kind) of a quiet NaN. If the implementation does not support
 * quiet NaNs, the function returns zero.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  signbit
 *
 */
double      nan(const char *);

/**
 * @ingroup  math
 * @par Description:
 * The function returns a representation (determined by __kind) of a quiet NaN. If the implementation does not support
 * quiet NaNs, the function returns zero.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float It returns a representation (determined by __kind) of a quiet NaN. If the implementation does not support
 * quiet NaNs, the function returns zero.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  signbit
 *
 */
float       nanf(const char *);

/**
 * @ingroup  math
 * @par Description:
 * The function returns a representation (determined by __kind) of a quiet NaN. If the implementation does not support
 * quiet NaNs, the function returns zero.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" It returns a representation (determined by __kind) of a quiet NaN. If the implementation does not support
 * quiet NaNs, the function returns zero.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  signbit
 *
 */
long double nanl(const char *);

double      nearbyint(double);
float       nearbyintf(float);
long double nearbyintl(long double);

/**
 * @ingroup  math
 * @par Description:
 * The nextafter() functions return the next representable floating-point value following x in
 * the direction of y. If y is less than x, these functions will return the largest representable
 * number less than x. If x equals y, the functions return y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double On success, these functions return the next representable floating-point value after x
 * in the direction of y.\n
 * If x equals y, then y (cast to the same type as x) is returned.\n
 * If x or y is a NaN, a NaN is returned.\n
 * If x is finite, and the result would overflow, a range error occurs, and the functions return
 * HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the
 * correct mathematical sign.\n
 * If x is not equal to y, and the correct function result would be subnormal, zero, or underflow,
 * a range error occurs, and either the correct value (if it
 * can be represented), or 0.0, is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see nearbyint
 *
 */
double      nextafter(double, double);

/**
 * @ingroup  math
 * @par Description:
 * The nextafterf() function returns the next representable floating-point value
 * following  x in the direction of y. If y is less than x, the function will return
 * the largest representable number less than x. If x equals y, the functions return y.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, the function returns the next representable floating-point value after x
 * in the direction of y.\n
 * If x equals y, then y (cast to the same type as x) is returned.\n
 * If x or y is a NaN, a NaN is returned.\n
 * If x is finite, and the result would overflow, a range error occurs,
 * and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the correct mathematical sign.\n
 * If  x  is  not equal to y, and the correct function result would be subnormal, zero, or underflow,
 * a range error occurs, and either the correct value (if it can be represented), or 0.0, is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 * @see  nearbyint
 *
 */
float       nextafterf(float, float);
long double nextafterl(long double, long double);

double      nexttoward(double, long double);
float       nexttowardf(float, long double);
long double nexttowardl(long double, long double);

/**
 * @ingroup  math
 * @par Description:
 * The pow() function returns the value of x raised to the power of y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the value of x to the power of y.\n
 * If x is a finite value less than 0, and y is a finite noninteger, a domain error occurs,
 * and a NaN is returned.\n
 * If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF,
 * or HUGE_VALL, respectively, with the mathematically correct
 * sign.\n
 * If result underflows, and is not representable, a range error occurs, and 0.0 is returned.\n
 * Except as specified below, if x or y is a NaN, the result is a NaN.\n
 * If x is +1, the result is 1.0 (even if y is a NaN).\n
 * If y is 0, the result is 1.0 (even if x is a NaN).\n
 * If x is +0 (-0), and y is an odd integer greater than 0, the result is +0 (-0).\n
 * If x is 0, and y greater than 0 and not an odd integer, the result is +0.\n
 * If x is -1, and y is positive infinity or negative infinity, the result is 1.0.\n
 * If the absolute value of x is less than 1, and y is negative infinity, the result is positive infinity.\n
 * If the absolute value of x is greater than 1, and y is negative infinity, the result is +0.\n
 * If the absolute value of x is less than 1, and y is positive infinity, the result is +0.\n
 * If the absolute value of x is greater than 1, and y is positive infinity, the result is positive infinity.\n
 * If x is negative infinity, and y is an odd integer less than 0, the result is -0.\n
 * If x is negative infinity, and y less than 0 and not an odd integer, the result is +0.\n
 * If x is negative infinity, and y is an odd integer greater than 0, the result is negative infinity.\n
 * If x is negative infinity, and y greater than 0 and not an odd integer, the result is positive infinity.\n
 * If x is positive infinity, and y less than 0, the result is +0.\n
 * If x is positive infinity, and y greater than 0, the result is positive infinity.\n
 * If x is +0 or -0, and y is an odd integer less than 0, a pole error occurs and HUGE_VAL, HUGE_VALF,
 * or HUGE_VALL, is returned, with the same sign as x.\n
 * If x is +0 or -0, and y is less than 0 and not an odd integer, a pole error occurs and +HUGE_VAL,
 * +HUGE_VALF, or +HUGE_VALL, is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | sqrt
 *
 */
double      pow(double, double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the value of x raised to the power of y.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float On success, this function returns the value of x to the power of y.\n
 * If x is a finite value less than 0, and y is a finite noninteger, a domain error occurs, and a NaN is returned.\n
 * If the result overflows, a range error occurs, and the functions return
 * HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the mathematically correct sign.\n
 * If result underflows, and is not representable, a range error occurs, and 0.0 is returned.\n
 * Except as specified below, if x or y is a NaN, the result is a NaN.\n
 * If x is +1, the result is 1.0 (even if y is a NaN).\n
 * If y is 0, the result is 1.0 (even if x is a NaN).\n
 * If x is +0 (-0), and y is an odd integer greater than 0, the result is +0 (-0).\n
 * If x is 0, and y greater than 0 and not an odd integer, the result is +0.\n
 * If x is -1, and y is positive infinity or negative infinity, the result is 1.0.\n
 * If the absolute value of x is less than 1, and y is negative infinity, the result is positive infinity.\n
 * If the absolute value of x is greater than 1, and y is negative infinity, the result is +0.\n
 * If the absolute value of x is less than 1, and y is positive infinity, the result is +0.\n
 * If the absolute value of x is greater than 1, and y is positive infinity, the result is positive infinity.\n
 * If x is negative infinity, and y is an odd integer less than 0, the result is -0.\n
 * If x is negative infinity, and y less than 0 and not an odd integer, the result is +0.\n
 * If x is negative infinity, and y is an odd integer greater than 0, the result is negative infinity.\n
 * If x is negative infinity, and y greater than 0 and not an odd integer, the result is positive infinity.\n
 * If x is positive infinity, and y less than 0, the result is +0.\n
 * If x is positive infinity, and y greater than 0, the result is positive infinity.\n
 * If x is +0 or -0, and y is an odd integer less than 0, a pole error occurs and
 * HUGE_VAL, HUGE_VALF, or HUGE_VALL, is returned, with the same sign as x.\n
 * If x is +0 or -0, and y is less than 0 and not an odd integer, a pole error occurs
 * and +HUGE_VAL, +HUGE_VALF, or +HUGE_VALL, is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see cbrt | sqrt
 *
 */
float       powf(float, float);

/**
 * @ingroup  math
 * @par Description:
 * The powl() function returns the value of x raised to the power of y.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the value of x to the power of y.\n
 * If x is a finite value less than 0, and y is a finite noninteger, a domain error occurs, and a NaN is returned.\n
 * If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the mathematically correct
 * sign.\n
 * If result underflows, and is not representable, a range error occurs, and 0.0 is returned.\n
 * Except as specified below, if x or y is a NaN, the result is a NaN.\n
 * If x is +1, the result is 1.0 (even if y is a NaN).\n
 * If y is 0, the result is 1.0 (even if x is a NaN).\n
 * If x is +0 (-0), and y is an odd integer greater than 0, the result is +0 (-0).\n
 * If x is 0, and y greater than 0 and not an odd integer, the result is +0.\n
 * If x is -1, and y is positive infinity or negative infinity, the result is 1.0.\n
 * If the absolute value of x is less than 1, and y is negative infinity, the result is positive infinity.\n
 * If the absolute value of x is greater than 1, and y is negative infinity, the result is +0.\n
 * If the absolute value of x is less than 1, and y is positive infinity, the result is +0.\n
 * If the absolute value of x is greater than 1, and y is positive infinity, the result is positive infinity.\n
 * If x is negative infinity, and y is an odd integer less than 0, the result is -0.\n
 * If x is negative infinity, and y less than 0 and not an odd integer, the result is +0.\n
 * If x is negative infinity, and y is an odd integer greater than 0, the result is negative infinity.\n
 * If x is negative infinity, and y greater than 0 and not an odd integer, the result is positive infinity.\n
 * If x is positive infinity, and y less than 0, the result is +0.\n
 * If x is positive infinity, and y greater than 0, the result is positive infinity.\n
 * If x is +0 or -0, and y is an odd integer less than 0, a pole error occurs and HUGE_VAL, HUGE_VALF, or HUGE_VALL, is returned, with the same sign as x.\n
 * If x is +0 or -0, and y is less than 0 and not an odd integer, a pole error occurs and +HUGE_VAL, +HUGE_VALF, or +HUGE_VALL, is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | sqrt
 *
 */
long double powl(long double, long double);

double      remainder(double, double);
float       remainderf(float, float);
long double remainderl(long double, long double);

double      remquo(double, double, int *);
float       remquof(float, float, int *);
long double remquol(long double, long double, int *);

/**
 * @ingroup  math
 * @par Description:
 * The rint() function rounds itsargument to an integer value in floating-point format,
 * using the current rounding direction and
 * will raise the inexact exception when the result differs in value from the argument.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double The function returns the rounded integer value. If x is integral, +0, -0, NaN, or
 * infinite, x itself is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lrint | round | trunc
 *
 */
double      rint(double);

/**
 * @ingroup  math
 * @par Description:
 * The rintf() function rounds itsargument to an integer value in floating-point format,
 * using the current rounding direction and
 * will raise the inexact exception when the result differs in value from the argument.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float The function returns the rounded integer value. If x is integral, +0, -0,
 * NaN, or infinite, x itself is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lrint | round | trunc
 *
 */
float       rintf(float);

/**
 * @ingroup  math
 * @par Description:
 * The rintl() function rounds itsargument to an integer value in floating-point format, using the current rounding direction and
 * will raise the inexact exception when the result differs in value from the argument.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" The function returns the rounded integer value. If x is integral, +0, -0, NaN, or infinite, x itself is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lrint | round | trunc
 *
 */
long double rintl(long double);

/**
 * @ingroup  math
 * @par Description:
 * The function rounds x to the nearest integer, but round halfway cases away from zero,
 * instead of to the nearest even integer
 * like rint(). For example, round(0.5) is 1.0, and round(-0.5) is -1.0.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double This function returns the rounded integer value.\n
 * If x is integral, +0, -0, NaN, or infinite, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ceil | floor | lround | nearbyint | rint | trunc
 *
 */
double      round(double);

/**
 * @ingroup  math
 * @par Description:
 * The function rounds x to the nearest integer, but round halfway cases away from zero,
 * instead of to the nearest even integer
 * like rint().
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float This function returns the rounded integer value.\n
 * If x is integral, +0, -0, NaN, or infinite, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ceil | floor | lround | nearbyint | rint | trunc
 *
 */
float       roundf(float);

/**
 * @ingroup  math
 * @par Description:
 * The function rounds x to the nearest integer, but round halfway cases away from zero, instead of to the nearest even integer
 * like rint().
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" This function returns the rounded integer value.\n
 * If x is integral, +0, -0, NaN, or infinite, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  ceil | floor | lround | nearbyint | rint | trunc
 *
 */
long double roundl(long double);

double      scalbln(double, long);
float       scalblnf(float, long);
long double scalblnl(long double, long);

double      scalbn(double, int);

/**
 * @ingroup  math
 * @par Description:
 * The function multiplies its first argument x by FLT_RADIX (probably 2) to the power of n, that is:
 *     x * FLT_RADIX * * exp
 *The definition of FLT_RADIX can be obtained by including <float.h>
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float On success, the function returns x * FLT_RADIX * * exp.
 * <ul>If x is a NaN, a NaN is returned.</ul>
 * <ul>If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.</ul>
 * <ul>If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF,
 *     or HUGE_VALL, respectively, with a sign the same as x.</ul>
 * <ul>If x is less than -1 (including negative infinity), a domain error occurs,
 *     and a NaN (not a number) is returned.</ul>
 * <ul>If the result underflows, a range error occurs, and the functions return zero,
 *     with a sign the same as x.</ul>
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ldexp
 *
 */
float       scalbnf(float, int);

/**
 * @ingroup  math
 * @par Description:
 * The function multiplies its first argument x by FLT_RADIX (probably 2) to the power of n, that is:
 *     x * FLT_RADIX ** exp
 * The definition of FLT_RADIX can be obtained by including <float.h>
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" On success, the function returns x * FLT_RADIX ** exp.
 * <ul>If x is a NaN, a NaN is returned.</ul>
 * <ul>If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.</ul>
 * <ul>If the result overflows, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF,
 *     or HUGE_VALL, respectively, with a sign the same as x.</ul>
 * <ul>If x is less than -1 (including negative infinity), a domain error occurs,
 *     and a NaN (not a number) is returned.</ul>
 * <ul>If the result underflows, a range error occurs, and the functions return zero,
 *     with a sign the same as x.</ul>
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ldexp
 *
 */
long double scalbnl(long double, int);
/**
 * @ingroup  math
 * @par Description:
 * This function returns the sine of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | sincos | tan | cos
 *
 */
double      sin(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the sine of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | sin | sincos | tan
 *
 */
float       sinf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the sine of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | sincos | tan | cos
 *
 */
long double sinl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic sine of x, which is defined mathematically as:
 * sinh(x) = (exp(x) - exp(-x)) / 2
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function return the hyperbolic sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is  +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL,
 * +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | asinh | atanh | cosh | tanh
 *
 */
double      sinh(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic sine of x, which is defined mathematically as:
 * sinh(x) = (exp(x) - exp(-x)) / 2
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function return the hyperbolic sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is  +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL,
 * +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | asinh | atanh | cosh | tanh
 *
 */
float       sinhf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic sine of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function return the hyperbolic sine of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is  +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), positive infinity (negative infinity) is returned.\n
 * If the result overflows, a range error occurs, and the functions return +HUGE_VAL, +HUGE_VALF, or +HUGE_VALL, respectively.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | asinh | atanh | cosh | tanh
 *
 */
long double sinhl(long double);

/**
 * @ingroup  math
 * @par Description:
 * The sqrt() function returns the nonnegative square root of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the square root of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is less than -0, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | hypot
 *
 */
double      sqrt(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the nonnegative square root of x.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the square root of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is less than -0, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see cbrt | hypot
 *
 */
float       sqrtf(float);

/**
 * @ingroup  math
 * @par Description:
 * The sqrtl() function returns the nonnegative square root of x.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the square root of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity, positive infinity is returned.\n
 * If x is less than -0, a domain error occurs, and a NaN is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  cbrt | hypot
 *
 */
long double sqrtl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the tangent of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double  On success, this function returns the tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If the correct result would overflow, a range error occurs, and the functions
 * return HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the
 * mathematically correct sign.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | cos | sin
 *
 */
double      tan(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the tangent of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If the correct result would overflow, a range error occurs, and the functions return
 * HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the
 * mathematically correct sign.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | cos | sin
 *
 */
float       tanf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the tangent of x, where x is given in radians.
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double"  On success, this function returns the tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is positive infinity or negative infinity, a domain error occurs, and a NaN is returned.\n
 * If the correct result would overflow, a range error occurs, and the functions return HUGE_VAL, HUGE_VALF, or HUGE_VALL, respectively, with the
 * mathematically correct sign.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acos | asin | atan | atan2 | cos | sin
 *
 */
long double tanl(long double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic tangent of x, which is defined mathematically as:
 * tanh(x) = sinh(x) / cosh(x)
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #double On success, this function returns the hyperbolic tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is  +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +1 (-1) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see acosh | asinh | atanh | cosh | sinh
 *
 */
double      tanh(double);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic tangent of x, which is defined mathematically as:
 * tanh(x) = sinh(x) / cosh(x)
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval
 * #float  On success, this function returns the hyperbolic tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is  +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +1 (-1) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see  acosh | asinh | atanh | cosh | sinh
 *
 */
float       tanhf(float);

/**
 * @ingroup  math
 * @par Description:
 * This function returns the hyperbolic tangent of x, which is defined mathematically as:
 * tanh(x) = sinh(x) / cosh(x)
 *
 * @attention
 * <ul>
 * <li> None.</li>
 * </ul>
 *
 * @retval "long double" On success, this function returns the hyperbolic tangent of x.\n
 * If x is a NaN, a NaN is returned.\n
 * If x is  +0 (-0), +0 (-0) is returned.\n
 * If x is positive infinity (negative infinity), +1 (-1) is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see acosh | asinh | atanh | cosh | sinh
 *
 */
long double tanhl(long double);

double      tgamma(double);
float       tgammaf(float);
long double tgammal(long double);

/**
 * @ingroup  math
 * @par Description:
 * The function rounds x to the nearest integer not larger in absolute value.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #double This function returns the rounded integer value.\n
 * If x is integral, infinite, or NaN, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lrint | nearbyint | rint | round
 *
 */
double      trunc(double);

/**
 * @ingroup  math
 * @par Description:
 * The truncf() function round x to the nearest integer not larger in absolute value.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval
 * #float The function returns the rounded integer value. If x is integral, infinite, or NaN, x itself is returned.
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lrint | nearbyint | rint | round
 *
 */
float       truncf(float);

/**
 * @ingroup  math
 * @par Description:
 * The function rounds x to the nearest integer not larger in absolute value.
 *
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 *
 * @retval "long double" This function returns the rounded integer value.\n
 * If x is integral, infinite, or NaN, x itself is returned.\n
 *
 * @par Dependency:
 * <ul><li>math.h</li></ul>
 *
 * @see ceil | floor | lrint | nearbyint | rint | round
 *
 */
long double truncl(long double);


#if defined(_XOPEN_SOURCE) || defined(_BSD_SOURCE)
#undef  MAXFLOAT
#define MAXFLOAT        3.40282346638528859812e+38F
#endif

#if defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define M_E             2.7182818284590452354   /* e */
#define M_LOG2E         1.4426950408889634074   /* log_2 e */
#define M_LOG10E        0.43429448190325182765  /* log_10 e */
#define M_LN2           0.69314718055994530942  /* log_e 2 */
#define M_LN10          2.30258509299404568402  /* log_e 10 */
#define M_PI            3.14159265358979323846  /* pi */
#define M_PI_2          1.57079632679489661923  /* pi/2 */
#define M_PI_4          0.78539816339744830962  /* pi/4 */
#define M_1_PI          0.31830988618379067154  /* 1/pi */
#define M_2_PI          0.63661977236758134308  /* 2/pi */
#define M_2_SQRTPI      1.12837916709551257390  /* 2/sqrt(pi) */
#define M_SQRT2         1.41421356237309504880  /* sqrt(2) */
#define M_SQRT1_2       0.70710678118654752440  /* 1/sqrt(2) */

extern int signgam;

double      j0(double);
double      j1(double);
double      jn(int, double);

double      y0(double);
double      y1(double);
double      yn(int, double);
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define HUGE            3.40282346638528859812e+38F

double      drem(double, double);
float       dremf(float, float);

int         finite(double);
int         finitef(float);

double      scalb(double, double);
float       scalbf(float, float);

double      significand(double);
float       significandf(float);

double      lgamma_r(double, int*);
float       lgammaf_r(float, int*);

float       j0f(float);
float       j1f(float);
float       jnf(int, float);

float       y0f(float);
float       y1f(float);
float       ynf(int, float);
#endif

#ifdef _GNU_SOURCE
long double lgammal_r(long double, int*);

void        sincos(double, double*, double*);
void        sincosf(float, float*, float*);
void        sincosl(long double, long double*, long double*);

double      exp10(double);
float       exp10f(float);
long double exp10l(long double);

double      pow10(double);
float       pow10f(float);
long double pow10l(long double);
#endif

#ifdef __cplusplus
}
#endif

#endif
