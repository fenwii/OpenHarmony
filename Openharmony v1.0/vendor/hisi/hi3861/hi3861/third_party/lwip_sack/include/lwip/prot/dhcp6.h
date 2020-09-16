/*
 * Description: DHCPv6 protocol definitions
 */
#ifndef LWIP_HDR_PROT_DHCP6_H
#define LWIP_HDR_PROT_DHCP6_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DHCP6_CLIENT_PORT  546
#define DHCP6_SERVER_PORT  547

#define DHCP6_ENABLE_UNICAST_SUPPORT 0

#define DHCP6_OPT_HEADER_LEN   4
/* DHCPv6 message item offsets and length */
#define DHCP6_TRANSACTION_ID_LEN   3

#define DHCPv6_ELAPSED_TIME_VALUE_BYTES  2
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
/** minimum set of fields of any DHCPv6 message */
struct dhcp6_msg {
  PACK_STRUCT_FLD_8(u8_t msgtype);
  PACK_STRUCT_FLD_8(u8_t transaction_id[DHCP6_TRANSACTION_ID_LEN]);
  /* options follow */
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/* DHCP6 client states */
typedef enum {
  DHCP6_STATE_OFF               = 0,
  DHCP6_STATE_STATELESS_IDLE    = 1,
  DHCP6_STATE_REQUESTING_CONFIG = 2,
#if LWIP_IPV6_DHCP6_STATEFUL
  DHCP6_STATE_STATEFUL_INIT     = 3,
  DHCP6_STATE_STATEFUL_SOLICIT  = 4,
  DHCP6_STATE_STATEFUL_INFOREQ  = 5,
  DHCP6_STATE_STATEFUL_REQUEST  = 6,
  DHCP6_STATE_STATEFUL_RENEW    = 7,
  DHCP6_STATE_STATEFUL_REBIND   = 8,
  DHCP6_STATE_STATEFUL_RELEASE  = 9,
  DHCP6_STATE_STATEFUL_DECLINE  = 10,
  DHCP6_STATE_STATEFUL_IDLE     = 11
#endif /* LWIP_IPV6_DHCP6_STATEFUL */
} dhcp6_state_enum_t;

/* DHCPv6 message types */
/* More message types see https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml */
#define DHCP6_SOLICIT               1
#define DHCP6_ADVERTISE             2
#define DHCP6_REQUEST               3
#define DHCP6_CONFIRM               4
#define DHCP6_RENEW                 5
#define DHCP6_REBIND                6
#define DHCP6_REPLY                 7
#define DHCP6_RELEASE               8
#define DHCP6_DECLINE               9
#define DHCP6_RECONFIGURE           10
#define DHCP6_INFOREQUEST           11
#define DHCP6_RELAYFORW             12
#define DHCP6_RELAYREPL             13
#define DHCP6_MESSAGE_END           14

/** DHCPv6 status codes */
/* More status codes see https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml */
#define DHCP6_STATUS_SUCCESS        0 /* Success. */

/*
 * Failure, reason unspecified; this status code is sent by either a client or a server to
 * indicate a failure not explicitly specified in this document.
 */
#define DHCP6_STATUS_UNSPECFAIL     1

/* Server has no addresses available to assign to the IA(s). */
#define DHCP6_STATUS_NOADDRSAVAIL   2

/* Client record (binding) unavailable. */
#define DHCP6_STATUS_NOBINDING      3

/* The prefix for the address is not appropriate for the link to which the client is attached. */
#define DHCP6_STATUS_NOTONLINK      4

/*
 * Sent by a server to a client to force the client to send messages to the server
 * using the All_DHCP_Relay_Agents_and_Servers address.
 */
#define DHCP6_STATUS_USEMULTICAST   5

/* Delegating router has no prefixes available to assign to the IAPD(s), RFC 3633 */
#define DHCP6_STATUS_NOPREFIXAVAIL  6

/** DHCPv6 DUID types */
#define DHCP6_DUID_LLT              1 /* LLT: Link-layer Address Plus Time */
#define DHCP6_DUID_EN               2 /* EN: Enterprise number */
#define DHCP6_DUID_LL               3 /* LL: Link-layer Address */
#define DHCP6_DUID_UUID             4 /* UUID (RFC 6355) */

/* DHCPv6 Possible values for hardware type (htype) field... */
#define DHCP6HTYPE_ETHER            1 /* Ethernet 10Mbps */
#define DHCP6HTYPE_IEEE802          6 /* IEEE 802.2 Token Ring... */
#define DHCP6HTYPE_FDDI             8 /* FDDI... */
#define DHCP6HTYPE_INFINIBAND       32 /* IP over Infiniband */

/* IPMP - random hw address - there is no standard for this so we just steal a type */
#define DHCP6HTYPE_IPMP             255

/* DHCPv6 options */
#define DHCP6_OPTION_CLIENTID       1
#define DHCP6_OPTION_SERVERID       2
#define DHCP6_OPTION_IA_NA          3
#define DHCP6_OPTION_IA_TA          4
#define DHCP6_OPTION_IAADDR         5
#define DHCP6_OPTION_ORO            6
#define DHCP6_OPTION_PREFERENCE     7
#define DHCP6_OPTION_ELAPSED_TIME   8
#define DHCP6_OPTION_RELAY_MSG      9
#define DHCP6_OPTION_AUTH           11
#define DHCP6_OPTION_UNICAST        12
#define DHCP6_OPTION_STATUS_CODE    13
#define DHCP6_OPTION_RAPID_COMMIT   14
#define DHCP6_OPTION_USER_CLASS     15
#define DHCP6_OPTION_VENDOR_CLASS   16
#define DHCP6_OPTION_VENDOR_OPTS    17
#define DHCP6_OPTION_INTERFACE_ID   18
#define DHCP6_OPTION_RECONF_MSG     19
#define DHCP6_OPTION_RECONF_ACCEPT  20
/* More options see https://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml */
#define DHCP6_OPTION_DNS_SERVERS    23 /* RFC 3646 */
#define DHCP6_OPTION_DOMAIN_LIST    24 /* RFC 3646 */
#define DHCP6_OPTION_IA_PD          25 /* RFC 3633 */
#define DHCP6_OPTION_IAPREFIX       26 /* RFC 3633 */
#define DHCP6_OPTION_SNTP_SERVERS   31 /* RFC 4075 */

#define DHCP6_OPTION_PREFERENCE_MAX 255

/*
 * DHCPv6 Retransmission Constants (RFC3315 section 5.5, RFC 5007)
 */
#ifndef SOL_MAX_DELAY
#define SOL_MAX_DELAY     1
#endif /* SOL_MAX_DELAY */
#ifndef SOL_TIMEOUT
#define SOL_TIMEOUT       1
#endif /* SOL_TIMEOUT */
#ifndef SOL_MAX_RT
#define SOL_MAX_RT      120
#endif /* SOL_MAX_RT */
#ifndef REQ_TIMEOUT
#define REQ_TIMEOUT       1
#endif /* REQ_TIMEOUT */
#ifndef REQ_MAX_RT
#define REQ_MAX_RT       30
#endif /* REQ_MAX_RT */
#ifndef REQ_MAX_RC
#define REQ_MAX_RC       10
#endif /* REQ_MAX_RC */
#ifndef CNF_MAX_DELAY
#define CNF_MAX_DELAY     1
#endif /* CNF_MAX_DELAY */
#ifndef CNF_TIMEOUT
#define CNF_TIMEOUT       1
#endif /* CNF_TIMEOUT */
#ifndef CNF_MAX_RT
#define CNF_MAX_RT        4
#endif /* CNF_MAX_RT */
#ifndef CNF_MAX_RD
#define CNF_MAX_RD       10
#endif /* CNF_MAX_RD */
#ifndef REN_TIMEOUT
#define REN_TIMEOUT      10
#endif /* REN_TIMEOUT */
#ifndef REN_MAX_RT
#define REN_MAX_RT      600
#endif /* REN_MAX_RT */
#ifndef REB_TIMEOUT
#define REB_TIMEOUT      10
#endif /* REB_TIMEOUT */
#ifndef REB_MAX_RT
#define REB_MAX_RT      600
#endif /* REB_MAX_RT */
#ifndef INF_MAX_DELAY
#define INF_MAX_DELAY     1
#endif /* INF_MAX_DELAY */
#ifndef INF_TIMEOUT
#define INF_TIMEOUT       1
#endif /* INF_TIMEOUT */
#ifndef INF_MAX_RT
#define INF_MAX_RT      120
#endif /* INF_MAX_RT */
#ifndef REL_TIMEOUT
#define REL_TIMEOUT       1
#endif /* REL_TIMEOUT */
#ifndef REL_MAX_RC
#define REL_MAX_RC        5
#endif /* REL_MAX_RC */
#ifndef DEC_TIMEOUT
#define DEC_TIMEOUT       1
#endif /* DEC_TIMEOUT */
#ifndef DEC_MAX_RC
#define DEC_MAX_RC        5
#endif /* DEC_MAX_RC */
#ifndef REC_TIMEOUT
#define REC_TIMEOUT       2
#endif /* REC_TIMEOUT */
#ifndef REC_MAX_RC
#define REC_MAX_RC        8
#endif /* REC_MAX_RC */
#ifndef HOP_COUNT_LIMIT
#define HOP_COUNT_LIMIT  32
#endif /* HOP_COUNT_LIMIT */
#ifndef LQ6_TIMEOUT
#define LQ6_TIMEOUT       1
#endif /* LQ6_TIMEOUT */
#ifndef LQ6_MAX_RT
#define LQ6_MAX_RT       10
#endif /* LQ6_MAX_RT */
#ifndef LQ6_MAX_RC
#define LQ6_MAX_RC        5
#endif /* LQ6_MAX_RC */

/** Infinite duration */
#define DHCP6_DURATION_INFINITE 0xffffffff

#define DHCP6_SERVERINFO_MAX_LEN 720
#define DHCP6_SERVERINFO_MAX_OPT_NUM 16

#define DHCPV6_RT_RAND (((LWIP_RAND() % 21) - 10) / 100.0)

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_PROT_DHCP6_H */
