#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cmocka.h>

int __real_open(const char*, mode_t);
int __real_close(int);
int __real_stat(const char*, struct stat *);
ssize_t __real_read(int, void*, size_t);

/* syscalls to mock */
int __wrap_open(const char *path, mode_t mode)
{
	check_expected(path);
	mode_t m = mock_type(mode_t);
	mode_t a = mode & m;
	assert_int_equal(a, m);
	int retval = mock_type(int);
	/* fake open if retval > 0 */
	if (retval > 0)
		return retval;

	return __real_open(path, mode);
}

int __wrap_close(int fd)
{
	check_expected(fd);
	int retval = mock_type(int);
	if (retval != 0)
		return __real_close(fd);
	return retval;
}

int __wrap_ioctl(int fd, unsigned long req, ...)
{
	assert_true(fd > 0);
	check_expected(req);
	int retval = mock_type(int);
	char *expected_arg = mock_type(char*);
	if (expected_arg == NULL)
		return retval;
	va_list ap;
	va_start(ap, req);
	char *arg = va_arg(ap, char *);
	va_end(ap);
	assert_non_null(arg);
	assert_memory_equal(expected_arg, arg, _IOC_SIZE(req));
	return retval;
}

int __wrap_read(int fd, char *buf, size_t len)
{
	assert_true(fd > 0);
	assert_non_null(buf);
	check_expected(len);
	int retval = mock_type(int);
	int real = mock_type(int);
	if (real)
		return __real_read(fd, buf, len);
	return retval;
}

int __wrap_write(int fd, char *buf, size_t len)
{
	assert_true(fd > 0);
	assert_non_null(buf);
	void *expected_buf = mock_type(void*);
	size_t expected_len = mock_type(size_t);
	assert_int_equal(expected_len, len);
	assert_memory_equal(expected_buf, buf, expected_len);
	return mock_type(int);
}

off_t __wrap_lseek(int fd, off_t seek, int whence)
{
	assert_true(fd > 0);
	check_expected(seek);
	check_expected(whence);
	return mock_type(off_t);
}

#define expect_open(X,Y,Z) do { \
		expect_string(__wrap_open, path, X);\
		will_return(__wrap_open, Y);\
		will_return(__wrap_open, Z);\
	} while(0);

#define expect_close(X,Y) do { \
		expect_value(__wrap_close, fd, X);\
		will_return(__wrap_close, Y);\
	} while(0);

#define expect_ioctl(W,X,Y) do { \
		expect_value(__wrap_ioctl, req, W);\
		will_return(__wrap_ioctl, X);\
		will_return(__wrap_ioctl, Y);\
	} while(0);

#define expect_ioctl_short(X,Y) do { \
		expect_value(__wrap_ioctl, req, X);\
		will_return(__wrap_ioctl, Y);\
		will_return(__wrap_ioctl, NULL);\
	} while(0);

#define expect_write(X,Y,Z) do { \
		will_return(__wrap_write, X);\
		will_return(__wrap_write, Y);\
		will_return(__wrap_write, Z);\
	} while(0);

#define expect_lseek(X,Y,Z) do { \
		expect_value(__wrap_lseek, seek, X);\
		expect_value(__wrap_lseek, whence, Y);\
		will_return(__wrap_lseek, Z);\
	} while(0);

#define expect_read(X,Y) do { \
		expect_value(__wrap_read, len, X);\
		will_return(__wrap_read, Y);\
		will_return(__wrap_read, 0);\
	} while(0);

#define expect_read_real(X,Y) do { \
		expect_value(__wrap_read, len, X);\
		will_return(__wrap_read, Y);\
		will_return(__wrap_read, 1);\
	} while(0);
