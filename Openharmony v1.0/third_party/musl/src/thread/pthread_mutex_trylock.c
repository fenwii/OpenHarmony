#include "pthread_impl.h"

int __pthread_mutex_trylock_owner(pthread_mutex_t *m)
{
	int old, own;
	int type = m->_m_type;
	pthread_t self = __pthread_self();
	int tid = self->tid;

	old = m->_m_lock;
	own = old & 0x3fffffff;
	if (own == tid) {
		if ((type&PTHREAD_MUTEX_TYPE_MASK) == PTHREAD_MUTEX_RECURSIVE) {
			if ((unsigned)m->_m_count >= INT_MAX) return EAGAIN;
			m->_m_count++;
			return 0;
		}
	}
	if (own == 0x3fffffff) return ENOTRECOVERABLE;
	tid |= 0x80000000;
	if (own) return EBUSY;
	if (a_cas(&m->_m_lock, old, tid) != old) {
		self->robust_list.pending = 0;
		return EBUSY;
	}

#if 0
	volatile void *next = self->robust_list.head;
	m->_m_next = next;
	m->_m_prev = &self->robust_list.head;
	if (next != &self->robust_list.head) *(volatile void *volatile *)
		((char *)next - sizeof(void *)) = &m->_m_next;
	self->robust_list.head = &m->_m_next;
	self->robust_list.pending = 0;
#endif
	return 0;
}

int __pthread_mutex_trylock(pthread_mutex_t *m)
{
	if ((m->_m_type&PTHREAD_MUTEX_TYPE_MASK) == PTHREAD_MUTEX_NORMAL)
		return a_cas(&m->_m_lock, 0, EBUSY) & EBUSY;
	return __pthread_mutex_trylock_owner(m);
}

weak_alias(__pthread_mutex_trylock, pthread_mutex_trylock);
