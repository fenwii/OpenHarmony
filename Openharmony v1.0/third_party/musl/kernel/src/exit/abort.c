#include "stdlib.h"
#include "string.h"
#include "los_exc.h"

void abort(void) {
  LOS_Panic("System was being aborted\n");
  while (1);
}