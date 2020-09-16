#include <errno.h>
#include "los_printf.h"

void _exit(int status) {
  PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
  errno = ENOSYS;
}

void exit(int status) {
  PRINT_ERR("%s NOT SUPPORT\n", __FUNCTION__);
  errno = ENOSYS;
  while (1);
}
