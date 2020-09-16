#include "errno.h"
#include "los_errno.h"
#include "los_task_pri.h"

/* the specific errno get or set in interrupt service routine */
static int errno_isr;

void set_errno(int err_code) {
  LosTaskCB *runTask = NULL;

  /* errno can not be set to 0 as posix standard */
  if (err_code == 0)
    return;

  if (OS_INT_INACTIVE) {
    runTask = OsCurrTaskGet();
    runTask->errorNo = err_code;
  }
  else {
    errno_isr = err_code;
  }
}

int get_errno(void) {
  LosTaskCB *runTask = NULL;

  if (OS_INT_INACTIVE) {
    runTask = OsCurrTaskGet();
    return runTask->errorNo;
  }
  else {
    return errno_isr;
  }
}

int *__errno_location(void) {
  LosTaskCB *runTask = NULL;

  if (OS_INT_INACTIVE) {
    runTask = OsCurrTaskGet();
    return &runTask->errorNo;
  }
  else {
    return &errno_isr;
  }
}

volatile int *__errno(void) {
  LosTaskCB *runTask = NULL;

  if (OS_INT_INACTIVE) {
    runTask = OsCurrTaskGet();
    return (volatile int *)(&runTask->errorNo);
  }
  else {
    return (volatile int *)(&errno_isr);
  }
}
