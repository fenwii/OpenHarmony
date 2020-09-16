/*
 * Description: declaration for lowpower APIs
 */
#ifndef LWIP_HDR_LOWPOWER_H
#define LWIP_HDR_LOWPOWER_H

#include "lwip/opt.h"
#include "lwip/err.h"
#if !NO_SYS
#include "lwip/sys.h"
#endif

#if LWIP_LOWPOWER

#define LOWPOWER_TIMER_DEBUG 0
#define TIMEOUT_TICK     100 /* 100ms */
#define TIMEOUT_CHECK    30

#if LOWPOWER_TIMER_DEBUG
#define TCP_FASTTMR_NAME      ,"tcp_fasttmr"
#define TCP_SLOWTMR_NAME      ,"tcp_slowtmr"
#define IP_REASSTRM_NAME      ,"ip_reass_tmr"
#define ETHARPTMR_NAME        ,"etharp_tmr"
#define DHCP_COARSETMR_NAME   ,"dhcp_coarse_tmr"
#define DHCP_FINETMR_NAME     ,"dhcp_fine_tmr"
#define AUTOIPTMR_NAME        ,"autoip_tmr"
#define IGMPTMR_NAME          ,"igmp_tmr"
#define DNSTMR_NAME           ,"dns_tmr"
#define NAT64TMR_NAME         ,"nat64_tmr"
#define ND6TMR_NAME           ,"nd6_tmr"
#define IP6_TREASSTMR_NAME    ,"ip6_reass_tmr"
#define MLD6TMR_NAME          ,"mld6_tmr"
#define DHCP6TMR_NAME         ,"dhcp6_tmr"
#define LOWPAN6TMR_NAME       ,"lowpan6_tmr"
#else
#define TCP_FASTTMR_NAME
#define TCP_SLOWTMR_NAME
#define IP_REASSTRM_NAME
#define ETHARPTMR_NAME
#define DHCP_COARSETMR_NAME
#define DHCP_FINETMR_NAME
#define AUTOIPTMR_NAME
#define IGMPTMR_NAME
#define DNSTMR_NAME
#define NAT64TMR_NAME
#define ND6TMR_NAME
#define IP6_TREASSTMR_NAME
#define MLD6TMR_NAME
#define DHCP6TMR_NAME
#define LOWPAN6TMR_NAME
#endif

#define SET_TMR_TICK(tick, val) do { \
  if ((val) > 0) { \
    if ((tick) == 0) { \
      (tick) = (val); \
    } else { \
      (tick) = (tick) > (val) ? (val) : (tick); \
    } \
  } \
} while (0)

typedef void (*lwip_timer_handler)(void);
typedef void (*sys_timeout_handler)(void *args);

/* get time count to trigger */
typedef u32_t (*get_next_timeout)(void);

struct timer_handler {
  u32_t interval;
  lwip_timer_handler handler;
  get_next_timeout next_tick;
#if LOWPOWER_TIMER_DEBUG
  char *name;
#endif
};

struct timer_entry {
  u32_t clock_max; /* tmr interval */
  u32_t timeout;
  sys_timeout_handler handler;
  void *args;
  get_next_timeout next_tick;
  struct timer_entry *next;
#if LOWPOWER_TIMER_DEBUG
  char *name;
#endif
  u8_t enable;
};

enum timer_state {
  LOW_TMR_GETING_TICKS = 0,
  LOW_TMR_TIMER_WAITING,
  LOW_TMR_TIMER_HANDLING,
};

struct timer_mng {
  enum timer_state state;
  u32_t waiting_time;
};

enum lowpower_msg_type {
  LOW_NON_BLOCK             = 0,
  LOW_BLOCK                 = 1,
  LOW_FORCE_NON_BLOCK       = 2,
};

enum lowpower_mod {
  LOW_TMR_LOWPOWER_MOD           = 0,
  LOW_TMR_NORMAL_MOD             = 1,
};

#define lowpower_sem_t sys_sem_t
#define LOWPOWER_SEM_WAIT(lock) sys_sem_wait(&(lock))
#define LOWPOWER_SIGNAL(lock) sys_sem_signal(&(lock))
#define LOWPOWER_SEM_NEW(lock, val)        \
  do {                                     \
    (val) = sys_sem_new(&(lock), 0);       \
  } while (0)
#define LOWPOWER_SEM_FREE(lock) sys_sem_free(&(lock))

/* all timer use the same timeout step */
#define STEP_TIMEOUT_TO_TICK(step, type) (((step) * lwip_cyclic_timers[(type)].interval_ms) / TIMEOUT_TICK)
#define STEP_TICK_TO_TIMEOUT(tick, type) (((tick) * TIMEOUT_TICK) / lwip_cyclic_timers[(type)].interval_ms)
#define sys_timeout(msecs, handler, arg) (void)sys_timeout_ext(msecs, handler, arg)

#define LOW_TMR_DELAY 20
void sys_timeout_set_wake_time(u32_t val);
u32_t sys_timeout_get_wake_time(void);

void sys_untimeout(sys_timeout_handler handler, void *arg);
void sys_restart_timeouts(void);
void sys_timeouts_mbox_fetch(sys_mbox_t *mbox, void **msg);
void sys_timeouts_init(void);
err_t sys_timeout_ext(u32_t msecs, sys_timeout_handler handler, void *arg);
u8_t sys_timeout_waiting_long(void);

void set_lowpower_mod(enum lowpower_mod sw);
enum lowpower_mod get_lowpowper_mod(void);

#endif /* LOWEPOWER */

#endif /* LWIP_HDR_LOWPOWER_H */