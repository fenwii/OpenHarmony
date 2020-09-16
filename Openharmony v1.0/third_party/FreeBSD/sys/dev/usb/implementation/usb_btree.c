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

/* Architecture Analysis
 *********************************************************************************************
 *      The USB Devices Topology    ---    Translate   -->  Binary Tree Map
 *               BUS                                             BUS
 *                |                                              /
 *       ---------------------                                  /
 *       |                   |                                 H01
 *      H01                 H02...                             / \
 *       |                   |                                /   \
 * ------------      ---------------                        H11    \---------H02
 * |          |      |             |         ------\        / \              / \
 *H11        H12... H21           H22...     -------\      /   \            /   \
 * |          |      |             |         -------/     D1   H12         H21  ...
 *D1         D2      |            D3         ------/           / \         / \
 *              ------------                                  /   \       /   \
 *              |          |                                 D2   ...    H31   \----H22
 *             H31        H32...                                          / \        / \
 *              |          |                                             /   \      /   \
 *             D4         D5                                            D4   H32   D3   ...
 *                                                                      / \
 *                                                                     /   \
 *                                                                    D5   ...
 *********************************************************************************************
 */

#include <stdlib.h>
#include <string.h>
#include <los_printf_pri.h>

#include "implementation/usb_btree.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#ifdef USB_BINARY_TREE_DEBUG
#define	BT_DEBUG(x...) dprintf(x)
#else
#define	BT_DEBUG(x...) do{}while(0)
#endif

extern usbd_bt_tree hub_tree;

struct usbd_bt_node *
usbd_create_bt_node(struct node_info *info)
{
	struct usbd_bt_node *node = (usbd_bt_node *)malloc(sizeof(usbd_bt_node));
	if (node == NULL) {
		PRINT_ERR("Binary tree node alloc failed!\n");
		return (NULL);
	}

	(void)memset_s(&node->info, sizeof(node->info), 0, sizeof(node->info));
	node->info.port_no = info->port_no;
	node->info.nameunit = info->nameunit;
	node->lbt_node = NULL;
	node->rbt_node = NULL;

	BT_DEBUG("[create node] %p %s %d\n", node, node->info.nameunit, node->info.port_no);
	return (node);
}

void
usbd_free_bt_node(usbd_bt_node *node)
{
	BT_DEBUG("[free node] %p %s %d\n", node, node->info.nameunit, node->info.port_no);

	node->info.nameunit = NULL;
	node->info.port_no = 0;
	node->lbt_node = NULL;
	node->rbt_node = NULL;

	free(node);
}

static void
usbd_release_bt_node(usbd_bt_node *node)
{
	if (node == NULL)
		return;

	usbd_release_bt_node(node->lbt_node);
	usbd_release_bt_node(node->rbt_node);

	if (node->info.nameunit != NULL)
		usbd_free_bt_node(node);
}

static struct usbd_bt_node *
usbd_pre_order_bt_node(usbd_bt_node *node, struct node_info *info)
{
	usbd_bt_node *l_node, *r_node;

	if (node == NULL) {
		return (NULL);
	}

	if (node->info.nameunit == info->nameunit) {
		if (node->info.port_no == info->port_no) {
			return (node);
		}
	}

	l_node = usbd_pre_order_bt_node(node->lbt_node, info);
	if (l_node != NULL) {
		return (l_node);
	}
	r_node = usbd_pre_order_bt_node(node->rbt_node, info);
	if (r_node != NULL) {
		return (r_node);
	}

	return (NULL);
}

static bool f_find_device = false;
static struct usbd_bt_node *
usbd_pre_order_hub_node(usbd_bt_node *node, char *devname, uint8_t *port_num)
{
	usbd_bt_node *l_node, *r_node;

	if (node == NULL) {
		return (NULL);
	}

	if (!strncmp(node->info.nameunit, "uhub", strlen("uhub"))) {
		BT_DEBUG("[Hub Node] %p %s %d %d\n", node, node->info.nameunit, node->info.port_no, *port_num);
		if (node->lbt_node == NULL) {
			(*port_num)--;
		} else {
			if (!strncmp(node->lbt_node->info.nameunit, devname, strlen(devname))) {
				(*port_num)--;
				if (*port_num == 0)
					f_find_device = 1;
			}
		}
		if (*port_num == 0) {
			return (node->lbt_node);
		}
	}

	l_node = usbd_pre_order_hub_node(node->lbt_node, devname, port_num);
	if (l_node != NULL) {
		return (l_node);
	}
	r_node = usbd_pre_order_hub_node(node->rbt_node, devname, port_num);
	if (r_node != NULL) {
		return (r_node);
	}
	return (NULL);
}

static void
usbd_per_order_hub_quantity(usbd_bt_node *node, uint8_t *port_qty)
{
	if (node == NULL) {
		return;
	}

	if (!strncmp(node->info.nameunit, "uhub", strlen("uhub"))) {
		if (node->lbt_node == NULL) {
			(*port_qty)++;
		} else {
			if (strncmp(node->lbt_node->info.nameunit, "uhub", strlen("uhub"))) {
				(*port_qty)++;
			}
		}
	}

	usbd_per_order_hub_quantity(node->lbt_node, port_qty);
	usbd_per_order_hub_quantity(node->rbt_node, port_qty);
}

int
usbd_get_hub_quantity(void)
{
	uint8_t quantity = 0;

	usbd_per_order_hub_quantity(hub_tree, &quantity);

	return (quantity);
}

struct usbd_bt_node *
usbd_per_order_probe(usbd_bt_tree tree, char *devname, uint8_t *port_num)
{
	usbd_bt_node *node = usbd_pre_order_hub_node(tree, devname, port_num);

	if ((node != NULL) && f_find_device) {
		f_find_device = 0;
		return (node);
	}

	return (NULL);
}

int
usbd_insert_bt_node(usbd_bt_node *node, usbd_bt_tree tree, struct node_info *parent_info)
{
	usbd_bt_node *parent_node;

	if ((node == NULL) || (tree == NULL) || (parent_info == NULL))
		return (-1);

	parent_node = usbd_pre_order_bt_node(tree, parent_info);
	if (parent_node == NULL) {
		PRINT_ERR("Find err, insert fail!\n");
		return (-1);
	}

	if (parent_node->info.nameunit == node->info.nameunit) {  /* The same hub node. */
		parent_node->rbt_node = node;
	} else {  /* Other driver(hub or other) */
		parent_node->lbt_node = node;
	}

	BT_DEBUG("[insert node] parent:%p %s %d\n \
		    %s child :%p %s %d\n", \
		    parent_node, parent_node->info.nameunit, parent_node->info.port_no,
		    (parent_node->info.nameunit == node->info.nameunit ? "right" : "left"),
		    node, node->info.nameunit, node->info.port_no);
	return (0);
}

int
usbd_remove_bt_node(usbd_bt_tree tree, struct node_info *p_info, struct node_info *rm_info)
{
	usbd_bt_node *rm_node;

	if ((tree == NULL) || (p_info == NULL) || (rm_info == NULL))
		return (-1);

	rm_node = usbd_pre_order_bt_node(tree, rm_info);
	if (rm_node == NULL) {
		BT_DEBUG("Find err, remove fail!\n");
		return (-1);
	}

	usbd_release_bt_node(rm_node);

	/* release parent left node */
	rm_node = usbd_pre_order_bt_node(tree, p_info);
	if (rm_node == NULL) {
		PRINT_ERR("Parent find err, remove fail!\n");
		return (-1);
	}
	rm_node->lbt_node = NULL;

	return (0);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */