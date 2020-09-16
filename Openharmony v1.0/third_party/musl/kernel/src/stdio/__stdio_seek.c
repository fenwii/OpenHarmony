#include "stdio_impl.h"
#include <unistd.h>
#include "los_syscall.h"

static off64_t __stdio_lseek64(int fd, int offsetHigh, int offsetLow, off64_t *result, int whence)
{
    off64_t ret;
    struct file *filep = NULL;
    off64_t offset = ((off64_t)offsetHigh << 32) + (uint)offsetLow; /* 32: offsetHigh is high 32 bits */

    /* Get the file structure corresponding to the file descriptor. */
    ret = fs_getfilep(fd, &filep);
    if (ret < 0) {
        /* The errno value has already been set */
        return (off64_t)-get_errno();
    }

    /* libc seekdir function should set the whence to SEEK_SET, so we can discard
     * the whence argument here */
    if (filep->f_oflags & O_DIRECTORY) {
        /* defensive coding */
        if (filep->f_dir == NULL) {
            return (off64_t)-EINVAL;
        }
        if (offsetLow == 0) {
            rewinddir(filep->f_dir);
        } else {
            seekdir(filep->f_dir, offsetLow);
        }
        ret = telldir(filep->f_dir);
        if (ret < 0) {
            return (off64_t)-get_errno();
        }
        goto out;
    }

    /* Then let file_seek do the real work */
    ret = file_seek64(filep, offset, whence);
    if (ret < 0) {
        return (off64_t)-get_errno();
    }

out:
    *result = ret;

    return 0;
}

off_t __stdio_seek(FILE *f, off_t off, int whence)
{
    off_t result = 0;
    return __stdio_lseek64(f->fd, off>>32, off, &result, whence) ? -1 : result;
}
