struct DIR
{
	off_t tell;
	int fd;
	int buf_pos;
	int buf_end;
	volatile int lock[1];
	void *dirk;
	void *resv;
	/* Any changes to this struct must preserve the property:
	 * offsetof(struct __dirent, buf) % sizeof(off_t) == 0 */
	char buf[2048];
};
