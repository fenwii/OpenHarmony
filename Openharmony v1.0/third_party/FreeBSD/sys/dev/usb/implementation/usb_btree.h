/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __USB_BTREE_H__
#define	__USB_BTREE_H__

#include <los_typedef.h>
#include <securec.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

struct node_info {
	uint8_t port_no;
	const char *nameunit;  /* Save dev_nameunit address. */
};

typedef struct usbd_bt_node {
	struct node_info info;
	struct usbd_bt_node *lbt_node;
	struct usbd_bt_node *rbt_node;
}usbd_bt_node,*usbd_bt_tree;

/* External API interface */
struct usbd_bt_node *usbd_create_bt_node(struct node_info *info);
void usbd_free_bt_node(usbd_bt_node *node);
int usbd_insert_bt_node(usbd_bt_node *node, usbd_bt_tree tree, struct node_info *parent_info);
int usbd_remove_bt_node(usbd_bt_tree tree, struct node_info *p_info, struct node_info *rm_info);
int usbd_get_hub_quantity(void);
struct usbd_bt_node *usbd_per_order_probe(usbd_bt_tree tree, char *devname, uint8_t *port_num);

inline int usbd_atoi(const char *name)
{
	int num = 0;
	if (name == NULL) {
		return -1;
	}

	while(*name) {
		num *= 10;
		num += *name++ - '0';
	}
	return num;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* __USB_BTREE_H__ */

