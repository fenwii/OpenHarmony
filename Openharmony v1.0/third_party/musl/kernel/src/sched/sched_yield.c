#include <sched.h>
#include "los_process.h"

int sched_yield()
{
    (void)LOS_ProcessYield();
    return 0;
}
