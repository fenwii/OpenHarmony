/*
 * L2 packet implement for hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "common.h"
#ifdef CONFIG_DRIVER_HDF
#include "drivers/wpa_hal_cmd.h"
#endif /* CONFIG_DRIVER_HDF */
#include "securec.h"

struct l2_packet_data {
    char ifname[IFNAMSIZ + 1];
    u8 own_addr[ETH_ALEN];
    void (*rx_callback)(void *ctx, const u8 *src_addr,
                const u8 *buf, size_t len);
    void *rx_callback_ctx;
    int l2_hdr; /* whether to include layer 2 (Ethernet) header data
             * buffers */
};

int l2_packet_get_own_addr(const struct l2_packet_data *l2, u8 *addr)
{

    if ((l2 == NULL) || (addr == NULL))
        return -1;
    if (memcpy_s(addr, sizeof(l2->own_addr), l2->own_addr, sizeof(l2->own_addr)) != EOK){
        return -1;
    }
    return 0;
}

int l2_packet_send(const struct l2_packet_data *l2, const u8 *dst_addr, u16 proto,
           const u8 *buf, size_t len)
{
    int ret =0;

    (void)proto;
    if (l2 == NULL)
        return -1;
#ifdef CONFIG_DRIVER_HDF
    ret = WifiWpaEapolPacketSend(l2->ifname, l2->own_addr, dst_addr, (unsigned char *)buf, len);
#endif /* CONFIG_DRIVER_HDF */

    return ret;
}

void l2_packet_receive(void *eloop_ctx, void *sock_ctx)
{
    struct l2_packet_data *l2 = eloop_ctx;

    (void)sock_ctx;

    printf("\r\n l2_packet_receive1 \r\n ");

#ifdef CONFIG_DRIVER_HDF
    WifiRxEapol  st_rx_eapol = { 0 };
    unsigned char *puc_src;
    const int addr_offset = 6;

    /* Callback is called only once per multiple packets, drain all of them */
    printf("\r\n l2_packet_receive2 \r\n ");
    if (SUCC == WifiWpaEapolPacketReceive(l2->ifname, &st_rx_eapol)) {
        puc_src = (unsigned char *)(st_rx_eapol.buf + addr_offset);
        printf("\r\n l2_packet_receive3 \r\n ");
        if (l2->rx_callback != NULL) {
            printf("\r\n rx_callback \r\n ");
            l2->rx_callback(l2->rx_callback_ctx, puc_src, st_rx_eapol.buf, st_rx_eapol.len);
        }

        os_free(st_rx_eapol.buf);
        st_rx_eapol.buf = NULL;
    }

    if (st_rx_eapol.buf != NULL) {
        os_free(st_rx_eapol.buf);
        st_rx_eapol.buf = NULL;
    }
#endif /* CONFIG_DRIVER_HDF */
}

static void l2_packet_eapol_callback(void *ctx, void *context)
{
    struct l2_packet_data *l2 = (struct l2_packet_data *)context;

    (void)ctx;
    printf("l2_packet_eapol_callback");
    l2_packet_receive(l2, NULL);
}
struct l2_packet_data * l2_packet_init(
    const char *ifname, const u8 *own_addr, unsigned short protocol,
    void (*rx_callback)(void *ctx, const u8 *src_addr,
                const u8 *buf, size_t len),
    void *rx_callback_ctx, int l2_hdr)
{
    struct l2_packet_data *l2 = NULL;

    (void)own_addr;
    (void)protocol;
    if (ifname == NULL)
        return NULL;
    l2 = os_zalloc(sizeof(struct l2_packet_data));
    if (l2 == NULL) {
        return NULL;
    }
    if (strcpy_s(l2->ifname, sizeof(l2->ifname), ifname) != EOK) {
        os_free(l2);
        return NULL;
    }

    l2->rx_callback = rx_callback;
    l2->rx_callback_ctx = rx_callback_ctx;
    l2->l2_hdr = l2_hdr;

#ifdef CONFIG_DRIVER_HDF
    (void)WifiWpaEapolEnable(l2->ifname);
#endif /* CONFIG_DRIVER_HDF */
#ifdef CONFIG_DRIVER_HDF
    (void)WifiWpaCmdGetOwnMac(l2->ifname, (char *)l2->own_addr, ETH_ALEN);
#endif /* CONFIG_DRIVER_HDF */
    return l2;
}

struct l2_packet_data * l2_packet_init_bridge(
    const char *br_ifname, const char *ifname, const u8 *own_addr,
    unsigned short protocol,
    void (*rx_callback)(void *ctx, const u8 *src_addr,
                const u8 *buf, size_t len),
    void *rx_callback_ctx, int l2_hdr)
{
    (void)ifname;
    return l2_packet_init(br_ifname, own_addr, protocol, rx_callback,
                  rx_callback_ctx, l2_hdr);
}

void l2_packet_deinit(struct l2_packet_data *l2)
{
    if (l2 == NULL)
        return;

#ifdef CONFIG_DRIVER_HDF
        (void)WifiWpaEapolDisable(l2->ifname);
#endif /* CONFIG_DRIVER_HDF */

    os_free(l2);
}

int l2_packet_get_ip_addr(struct l2_packet_data *l2, char *buf, size_t len)
{
    (void)l2;
    (void)buf;
    (void)len;
    return 0;
}

void l2_packet_notify_auth_start(struct l2_packet_data *l2)
{
    (void)l2;
}
