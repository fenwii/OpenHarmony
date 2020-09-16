#include "stdlib.h"
#include "string.h"
#include "los_exc.h"

/*
 * getenv --
 *  Returns ptr to value associated with name, if any, else NULL.
 */
char *
getenv(const char *name)
{
#ifdef LOSCFG_LLTREPORT
    if (strncmp(name, "GCOV_PREFIX", sizeof("GCOV_PREFIX")) == 0) {
#ifdef LOSCFG_LLTSER
        extern const char *gcov_dir;
        return (char *)gcov_dir;
#else
        return "/bin/vs/sd";
#endif
    }
    if (strncmp(name, "GCOV_PREFIX_STRIP", sizeof("GCOV_PREFIX_STRIP")) == 0)
        return "6";
#endif
    return (NULL);
}
