#include "pthread_impl.h"

int __pthread_mutex_unlock(pthread_mutex_t *m)
{
	pthread_t self;
	int waiters = m->_m_waiters;
	int cont;
	int type = m->_m_type & PTHREAD_MUTEX_TYPE_MASK;
	int new = 0;
	int old;

	if (type != PTHREAD_MUTEX_NORMAL) {
		self = __pthread_self();
		old = m->_m_lock;
		int own = old & 0x3fffffff;
		if (own != self->tid)
			return EPERM;
		if ((type&PTHREAD_MUTEX_TYPE_MASK) == PTHREAD_MUTEX_RECURSIVE && m->_m_count)
			return m->_m_count--, 0;

	}

	cont = a_swap(&m->_m_lock, new);

	if (waiters || cont<0)
		__wake(&m->_m_lock, 1, 0);
	return 0;
}

weak_alias(__pthread_mutex_unlock, pthread_mutex_unlock);
