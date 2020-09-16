#include <features.h>

#undef assert

#ifdef NDEBUG
#define	assert(x) (void)0
#else
#define assert(x) ((void)((x) || (__assert_fail(#x, __FILE__, __LINE__, __func__),0)))
#endif

#ifdef CONFIG_DEBUG
#define DEBUGASSERT(f) \
       { if (!(f)) up_assert((const uint8_t *)__FILE__, (int)__LINE__); }
#else
#define DEBUGASSERT(f)
#endif

#if __STDC_VERSION__ >= 201112L && !defined(__cplusplus)
#undef static_assert
#define static_assert _Static_assert
#endif

#ifdef __cplusplus
extern "C" {
#endif
_Noreturn void __assert(const char *, int, const char *);
_Noreturn void __assert2(const char *, int, const char *, const char *);
_Noreturn void __assert_fail (const char *, const char *, int, const char *);

#ifdef __cplusplus
}
#endif
