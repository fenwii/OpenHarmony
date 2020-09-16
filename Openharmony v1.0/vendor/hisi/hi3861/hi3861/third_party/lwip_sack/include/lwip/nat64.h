/*
 * Description: NAT64 header
 */
#ifndef LWIP_HDR_NAT64_H
#define LWIP_HDR_NAT64_H

#include "lwip/opt.h"
#include "lwip/lwip_rpl.h"
#include "lwip/netif.h"
#if LWIP_NAT64
#include "lwip/ip.h"
#include "lwip/dhcp.h"
#include "lwip/prot/tcp.h"
#ifndef LWIP_NAT64_ENTRY_SIZE
#define LWIP_NAT64_ENTRY_SIZE 255
#endif

#define NAT64_TMR_INTERVAL 1000
#define NAT64_TMR_INFINITY 0xfffffffful

#define NAT64_PKT_HANDLED       (1)
#define NAT64_PKT_NOT_HANDLED   (0)

#define NAT64_RET_FAIL  (-1)
#define NAT64_RET_OK    (0)
#define NAT64_RET_ERR   (1)
#define NAT64_RET_ASSEMBLE   (2)

enum nat64_entry_state_e {
  NAT64_STATE_INIT,
  NAT64_STATE_DAO_RCV,
  NAT64_STATE_DHCP_DISCOVER,
  NAT64_STATE_DHCP_REQUEST,
  NAT64_STATE_STALE,
  NAT64_STATE_RELEASE,
  NAT64_STATE_ESTABLISH,
  NAT64_STATE_MAX
};

typedef struct {
  linklayer_addr_t mac;
#if LWIP_NA_PROXY_UNSOLICITED
  u8_t na_tries : 4;
  u8_t na_to : 4;
#endif
#if !LWIP_NAT64_MIN_SUBSTITUTE
  ip4_addr_t ip;
#endif
  u32_t lifetime; /* in seconds */
  u8_t state;
  u8_t dao_sn;
  u8_t mnid;
} nat64_entry_t;

/* init function */
/*
 * @brief
 *  This API is used to init the nat64 module.
 *
 * @param[in]  none
 *
 * @returns
 *  ERR_OK: On success.
 *  ERR_MEM: On memory alloc fail.
 */
err_t nat64_init(struct netif *ntf);

/*
 * @brief
 *  This API is used to deinit the nat64 module.
 *
 * @param[in]  none
 *
 * @returns
 *  ERR_OK: On success.
 *  ERR_MEM: On memory free fail.
 */
err_t nat64_deinit(void);

/* hook function */
/*
 * @brief
 *  This API is used to hook the ipv4 input packets in two different situations:
 *  1) when the packet is received by the non-mesh interface in a mesh gate .
 *  2) when the packet is received by the non-mesh interface in a mesh BR .
 *
 * @param
 *  [in]
 *     p : packet received
 *     iphdr : ip header
 *     inp : the interface that receive the packet.
 *
 * @returns
 *   0: Hook has not consumed the packet.
 *   != 0: Hook has consumed the packet.
 */
int nat64_ip4_input(struct pbuf *p, struct ip_hdr *iphdr, const struct netif *inp);

/*
 * @brief
 *  This API is used to hook the ipv6 input packets in two different situations:
 *  1) when the packet is received by the mesh interface in a mesh gate, if non-mesh interface is ipv4 .
 *  2) when the packet is received by the mesh interface in a mesh BR, if non-mesh interface is ipv4 .
 *
 * @param
 *  [in]
 *     p : packet received
 *     iphdr : ip header
 *     inp : the interface that receive the packet.
 *
 * @returns
 *   0: Hook has not consumed the packet.
 *   != 0: Hook has consumed the packet.
 */
int nat64_ip6_input(struct pbuf *p, struct ip6_hdr *iphdr, const struct netif *inp);

/* translate IP function */
/*
 * @brief
 *  This API is used to translate the ip header from ipv6 to ipv4
 *
 * @param
 *  [in]
 *     p6 : packet received
 *  [out]
 *     p4 : packet translated
 *
 * @returns
 *  ERR_OK: On success.
 *  ERR_MEM: On memory alloc fail.
 */
err_t nat64_translate_6to4(struct pbuf *p6, struct pbuf *p4);

/*
 * @brief
 *  This API is used to translate the ip header from ipv4 to ipv6
 *
 * @param
 *  [in]
 *     p4 : packet received
 *  [out]
 *     p6 : packet translated
 *
 * @returns
 *  ERR_OK: On success.
 *  ERR_MEM: On memory alloc fail.
 */
err_t nat64_translate_4to6(struct pbuf *p4, struct pbuf *p6);

/* entry api */
/*
 * @brief
 *  This API is used to add an entry of nat64 in the MBR, when receive DAO with mac:
 *
 * @param
 *  [in]
 *     mac: mac address received from DAO
 *
 * @returns
 *   != NULL: On success.
 *   NULL: On memory alloc fail.
 */
nat64_entry_t *nat64_entry_add(const u8_t *mac, int maclen);

err_t nat64_entry_remove(nat64_entry_t *entry);
nat64_entry_t *nat64_entry_lookup_by_mac(const linklayer_addr_t *mac);
int nat64_request_ipv4_addr(const linklayer_addr_t *lladdr, u8_t dao_sn, u8_t mnid,
                            u32_t lifetime, uint32_t *ipv4);
int nat64_delete_ipv4_addr(linklayer_addr_t *lladdr, u8_t mnid);
int nat64_delete_entry_by_mnid(u8_t mnid);

err_t nat64_ip4_dest_addr_exist(const ip4_addr_t *ip4addr);
struct netif *nat64_netif_get(void);

int nat64_status_check(void);

/* timer api */
void nat64_tmr(void);
#if LWIP_LOWPOWER
u32_t nat64_tmr_tick(void);
#endif

err_t nat64_deinit_netif(const struct netif *ntf);

err_t nat64_entry_mac_to_idx(const u8_t *hwaddr, u8_t hwaddr_len, dhcp_num_t *mac_idx);
err_t nat64_entry_idx_to_mac(dhcp_num_t mac_idx, u8_t *hwaddr, u8_t *hwaddr_len);

#if LWIP_NA_PROXY_UNSOLICITED
void nat64_proxy_unsolicited_na(const struct netif *netif);
#endif

#endif

#endif
