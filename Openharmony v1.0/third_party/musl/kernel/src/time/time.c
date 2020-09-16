#include "los_typedef.h"
#include <time.h>
#include <sys/time.h>

time_t time(time_t *t)
{
    struct timeval tp;
    int ret;

    /* Get the current time from the system */
    ret = gettimeofday(&tp, (struct timezone *)NULL);
    if (ret == LOS_OK) {
        /* Return the seconds since the epoch */
        if (t) {
            *t = tp.tv_sec;
        }
        return tp.tv_sec;
    }
    return (time_t)OS_ERROR;
}
