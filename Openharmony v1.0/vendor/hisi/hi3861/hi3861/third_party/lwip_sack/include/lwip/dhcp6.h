/*
 * Description: DHCPv6 client: IPv6 address autoconfiguration as per
 * RFC 3315 (stateful DHCPv6) and RFC 3736 (stateless DHCPv6).
 */

#ifndef LWIP_HDR_IP6_DHCP6_H
#define LWIP_HDR_IP6_DHCP6_H

#include "lwip/opt.h"

#if LWIP_IPV6_DHCP6  /* don't build if not configured for use in lwipopts.h */

#include "lwip/err.h"
#include "lwip/netif.h"

/* period (in milliseconds) of the application calling dhcp6_tmr() */
#define DHCP6_TIMER_MSECS   500
#define DHCP6_IAID_SIZE     4

/* DUID: DHCP unique Identifier */
typedef struct duid {
  u16_t duid_len; /* length */
  u8_t *duid_id; /* variable length ID value (must be opaque) */
} duid_t;

PACK_STRUCT_BEGIN
struct ia_info {
  u32_t dh6_ia_iaid;
  u32_t dh6_ia_t1;
  u32_t dh6_ia_t2;
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

typedef struct iaid {
  u16_t iaid_len;
  struct ia_info ia;
} iaid_t;

/*
 * General format of Identity Association.
 * This format applies to Prefix Delegation (IA_PD) and Non-temporary Addresses
 * (IA_NA)
 */
PACK_STRUCT_BEGIN
struct dhcp6opt_ia {
  u16_t dh6_ia_type;
  u16_t dh6_ia_len;
  u32_t dh6_ia_iaid;
  u32_t dh6_ia_t1;
  u32_t dh6_ia_t2;
  /* sub options follow */
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

PACK_STRUCT_BEGIN
struct dhcp6opt_iaaddr {
  ip6_addr_t dh6_iaaddr_addr;
  u32_t dh6_iaaddr_preferred;
  u32_t dh6_iaaddr_valid;
  /* sub options follow */
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

typedef struct opt_comm {
  struct opt_comm *next;
  u16_t opt_type;
  u16_t opt_len;
  u8_t *opt_start;
} opt_comm_t;

typedef struct ia {
  iaid_t iaid;
  struct dhcp6opt_iaaddr iaaddr;
} ia_t;

typedef struct dhcp6_serverinfo {
  struct dhcp6_serverinfo *next;
  u8_t *buff;
  opt_comm_t *opts;
  u16_t buff_len;
  u8_t pref; /* server preference */
  ip_addr_t unicast_addr;
  bool active;
  bool unicast;
} dhcp6_serverinfo_t;

struct dhcp6 {
  /* transaction identifier of last sent request */
  u32_t xid;
  /* connection to server */
  struct udp_pcb *pcb;
  /* current DHCPv6 state machine state */
  u8_t state;
  /* retries of current request */
  u8_t tries;
  /* if request config is triggered while another action is active, this keeps track of it */
  u8_t request_config_pending;
  /* #ticks with period DHCP6_TIMER_MSECS for request timeout */
  u16_t request_timeout;
#if LWIP_IPV6_DHCP6_STATEFUL
  u8_t struct_init; /* indicate whether memory that should be alloced is initialized */
  duid_t duid; /* DHCP Unique Identifier */
  ia_t ia[LWIP_IPV6_NUM_ADDRESSES]; /* Identity Association */
  dhcp6_serverinfo_t *current_serv; /* the server which we contact currently */
  dhcp6_serverinfo_t *serv_list; /* servers which response our Solicit */
  u32_t RT; /* Retransmission timeout */
  u32_t IRT; /* Initial retransmission time */
  u32_t MRC; /* Maximum retransmission count */
  u32_t MRT; /* Maximum retransmission time */
  u32_t MRD; /* Maximum retransmission duration */
  u32_t duration_start; /* record a state start timestamp  */
#endif /* LWIP_IPV6_DHCP6_STATEFUL */
};

void dhcp6_set_struct(struct netif *netif, struct dhcp6 *dhcp6);
/* Remove a struct dhcp6 previously set to the netif using dhcp6_set_struct() */
#define dhcp6_remove_struct(netif) netif_set_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP6, NULL)
void dhcp6_cleanup(struct netif *netif);

err_t dhcp6_enable_stateful(struct netif *netif);
err_t dhcp6_enable_stateless(struct netif *netif);
void dhcp6_disable(struct netif *netif);
err_t dhcp6_release_stateful(struct netif *netif);

void dhcp6_tmr(void);

void dhcp6_nd6_ra_trigger(struct netif *netif, u8_t managed_addr_config, u8_t other_config);

#if LWIP_IPV6_DHCP6_STATEFUL
void dhcp6_dad_handle(struct netif *netif_p, ip6_addr_t *target_address);
#endif

#if LWIP_DHCP6_GET_NTP_SRV
/*
 * This function must exist, in other to add offered NTP servers to the NTP (or SNTP) engine.
 * See LWIP_DHCP6_MAX_NTP_SERVERS
 */
extern void dhcp6_set_ntp_servers(u8_t num_ntp_servers, const ip_addr_t *ntp_server_addrs);
#endif /* LWIP_DHCP6_GET_NTP_SRV */

#define netif_dhcp6_data(netif) ((struct dhcp6*)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP6))

#if LWIP_LOWPOWER
u32_t dhcp6_tmr_tick();
#endif


#endif /* LWIP_IPV6_DHCP6 */

#endif /* LWIP_HDR_IP6_DHCP6_H */
