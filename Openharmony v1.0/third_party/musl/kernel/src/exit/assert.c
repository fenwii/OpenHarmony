#include "assert.h"
#include "los_hwi.h"
#include "los_printf.h"
#include "los_exc.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void __assert(const char* file, int line, const char* expr) {
  PRINT_ERR("__assert error: %s, %d, %s\n", file, line, expr);
  LOS_Panic("__assert error:\n");
  while (1);
}

void __assert2(const char* file, int line, const char* func, const char* expr) {
  PRINT_ERR("%s:%d: %s: assertion \"%s\" failed", file, line, func, expr);
  LOS_Panic("__assert error:\n");
  while (1);
}

void __assert_fail(const char* expr, const char* file, int line, const char* func) {
  PRINT_ERR("%s:%d: %s: assertion \"%s\" failed", file, line, func, expr);
  LOS_Panic("__assert error:\n");
  while (1);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */