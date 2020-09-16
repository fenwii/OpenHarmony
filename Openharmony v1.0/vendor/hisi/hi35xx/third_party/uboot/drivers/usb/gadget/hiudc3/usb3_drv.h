#ifndef __USB3_DRIVER_H__
#define	__USB3_DRIVER_H__

#include "sys.h"
#include "usb3.h"
#include "usb3_hw.h"
#include "debug.h"

/* time limit of waiting for key enents */
#define USB_WAIT_FOR_ENUM_DONE_TIME_MS (300 * 1000)
#define USB_WAIT_FOR_RX_NEXT_TIME_MS (60 * 1000)

enum usb_error_type {
	USB_RX_NEXT_TIMEOUT = -5,
	USB_ENUM_DONE_TIMEOUT = -3,
	USB_PROCESS_ERR = -1,
	USB_NO_ERR = 0,
};

struct usb_data_handle {
	UINT32  uFileType;
	UINT32  uFileAddress;
	UINT32  uFileLength;

	UINT32 IsRxStart;

	UINT32 InitTimeStamp;
	UINT32 RxTimeStamp;
};

#define USB_DEBUG

#ifdef USB_DEBUG
#define dbg(format, arg...) \
	do {                    \
		debug_printf("[%s]", __func__);     \
		debug_printf(format, ##arg);     \
	} while(0);
#else
#define dbg(format, arg...)
#endif

#define usb_info(format, arg...) debug_printf("[USBINFO]"format, ##arg);
#define usb_err(format, arg...) debug_printf("[USBERR]"format, ##arg);

typedef enum pcd_state {
	USB3_STATE_UNCONNECTED,	/* no host */
	USB3_STATE_DEFAULT,
	USB3_STATE_ADDRESSED,
	USB3_STATE_CONFIGURED,
} pcdstate_e;

typedef enum ep0_state {
	EP0_IDLE,
	EP0_IN_DATA_PHASE,
	EP0_OUT_DATA_PHASE,
	EP0_IN_WAIT_NRDY,
	EP0_OUT_WAIT_NRDY,
	EP0_IN_STATUS_PHASE,
	EP0_OUT_STATUS_PHASE,
	EP0_STALL,
} ep0state_e;

typedef union usb_setup_pkt {
    usb_device_request_t req;
    uint32_t d32[2];
    uint8_t d8[8];
} usb_setup_pkt_t;

typedef struct usb3_pcd_req {
    usb3_dma_desc_t *trb;
    phys_addr_t trbdma;

    uint32_t length;
    uint32_t actual;

   // void *bufdma;
   uint8_t *bufdma;
    void (*complete)(void *);
} usb3_pcd_req_t;

typedef struct usb3_pcd_ep {
    struct usb3_pcd *pcd;

    usb3_dev_ep_regs_t *out_ep_reg;
    usb3_dev_ep_regs_t *in_ep_reg;

    uint8_t phys;
    uint8_t num;
    uint8_t type;
    uint8_t maxburst;
    uint16_t maxpacket;
    /* Tx FIFO # for IN EPs */
    uint8_t tx_fifo_num;

    /* The Transfer Resource Index from the Start Transfer command */
    uint8_t tri_out;
    uint8_t tri_in;

    uint8_t stopped;
    /* Send ZLP */
    uint8_t send_zlp;
    /* True if 3-stage control transfer */
    uint8_t three_stage;
    /* True if transfer has been started on EP */
    uint8_t xfer_started;
    /* EP direction 0 = OUT */
    uint8_t is_in;
    /* True if endpoint is active */
    uint8_t active;
    /* Initial data pid of bulk endpoint */
    uint8_t data_pid_start;

    /* ep_desc (excluding ep0) */
    usb3_dma_desc_t *ep_desc;

    /* TRB descriptor must be aligned to 16 bytes */
    uint8_t epx_desc[32];

    /* request (excluding ep0) */
    usb3_pcd_req_t req;
} usb3_pcd_ep_t;

typedef struct usb3_pcd {
    struct usb3_device *usb3_dev;

    int32_t link_state;
    pcdstate_e state;
    uint8_t new_config;
    ep0state_e ep0state;

    uint32_t eps_enabled;
    uint32_t ltm_enable;

    usb3_pcd_ep_t ep0;
    usb3_pcd_ep_t out_ep;
    usb3_pcd_ep_t in_ep;

    usb3_dev_global_regs_t *dev_global_regs;
    usb3_dev_ep_regs_t *out_ep_regs;
    usb3_dev_ep_regs_t *in_ep_regs;

    usb3_pcd_req_t ep0_req;

    uint8_t speed;

    usb3_dma_desc_t *ep0_setup_desc;
    usb3_dma_desc_t *ep0_in_desc;
    usb3_dma_desc_t *ep0_out_desc;

    /* TRB descriptor must be aligned to 16 bytes */
    uint8_t ep0_setup[32];
    uint8_t ep0_in[32];
    uint8_t ep0_out[32];

    usb_setup_pkt_t ep0_setup_pkt[5];

#define USB3_STATUS_BUF_SIZE    512
    uint8_t ep0_status_buf[USB3_STATUS_BUF_SIZE];

#define USB3_BULK_BUF_SIZE      512
    uint8_t ss_bulk_buf[USB3_BULK_BUF_SIZE];

    uint32_t file_type;
    uint32_t file_address;
    uint32_t file_capacity;
    uint32_t file_total_frame;
    uint32_t file_curr_frame;
    uint32_t file_next_frame;
    uint32_t file_received;
    uint32_t file_complete;
} usb3_pcd_t;

#define usb3_pcd_ep_to_pcd(pcd_ep) ((pcd_ep)->usb3_pcd_ep_t.pcd)
#define usb3_pcd_ep_num(pcd_ep) ((pcd_ep)->usb3_pcd_ep_t.num)
#define usb3_pcd_ep_type(pcd_ep) ((pcd_ep)->usb3_pcd_ep_t.type)
#define usb3_pcd_ep_is_in(pcd_ep) ((pcd_ep)->usb3_pcd_ep_t.is_in)

#define dwc_usb3_is_hwo(desc)	((desc)->control & USB3_DSCCTL_HWO_BIT)
#define dwc_usb3_is_ioc(desc)	((desc)->control & USB3_DSCCTL_IOC_BIT)

#define usb3_get_xfercnt(desc)				\
	(((desc)->status >> USB3_DSCSTS_XFRCNT_SHIFT) &		\
	 (USB3_DSCSTS_XFRCNT_BITS >> USB3_DSCSTS_XFRCNT_SHIFT))
#define usb3_get_xfersts(desc)				\
	(((desc)->status >> USB3_DSCSTS_TRBRSP_SHIFT) &		\
	 (USB3_DSCSTS_TRBRSP_BITS >> USB3_DSCSTS_TRBRSP_SHIFT))

#define map_to_dma_addr(addr)				\
	((addr))
//	((addr) + (REG_BASE_LP_RAM_ACORE - REG_BASE_LP_RAM))

typedef struct usb3_device {
    volatile uint8_t *base;
    void *dev_desc;
    uint8_t string_manu[32];
    uint8_t string_prod[32];
    uint32_t string_manu_len;
    uint32_t string_prod_len;
    usb3_pcd_t pcd;
    uint32_t snpsid;
    usb3_core_global_regs_t *core_global_regs;

#define	USB3_EVENT_BUF_SIZE		256
    uint32_t event_buf[USB3_EVENT_BUF_SIZE];
    uint32_t *event_ptr;
    struct usb_data_handle *p_handle;
} usb3_device_t;

void usb3_memset(void *buf, uint8_t value, uint32_t size);
void usb3_memcpy(void *dst, void *src, uint32_t size);
uint32_t usb3_rd32(volatile uint32_t *addr);
void usb3_wr32(volatile uint32_t *addr, uint32_t val);
void usb3_set_address(usb3_pcd_t *pcd, uint32_t addr);
void usb3_accept_u1(usb3_pcd_t *pcd);
void usb3_accept_u2(usb3_pcd_t *pcd);
void usb3_enable_u1(usb3_pcd_t *pcd);
void usb3_enable_u2(usb3_pcd_t *pcd);
void usb3_disable_u1(usb3_pcd_t *pcd);
void usb3_disable_u2(usb3_pcd_t *pcd);
uint32_t usb3_u1_enabled(usb3_pcd_t *pcd);
uint32_t usb3_u2_enabled(usb3_pcd_t *pcd);
void usb3_dep_cstall(usb3_pcd_t *pcd,
			usb3_dev_ep_regs_t *ep_reg);
void usb3_dep_sstall(usb3_pcd_t *pcd,
			usb3_dev_ep_regs_t *ep_reg);
uint32_t handshake(usb3_device_t *dev, volatile uint32_t *ptr,
		      uint32_t mask, uint32_t done);
void usb3_fill_desc(usb3_dma_desc_t *desc, phys_addr_t dma_addr,
			uint32_t dma_len, uint32_t stream, uint32_t type,
			uint32_t ctrlbits, int own);
void usb3_dep_startnewcfg(usb3_pcd_t *pcd,
			usb3_dev_ep_regs_t *ep_reg, uint32_t rsrcidx);
void usb3_dep_cfg(usb3_pcd_t *pcd, usb3_dev_ep_regs_t *ep_reg,
		    uint32_t depcfg0, uint32_t depcfg1, uint32_t depcfg2);
void usb3_dep_xfercfg(usb3_pcd_t *pcd,
			usb3_dev_ep_regs_t *ep_reg, uint32_t depstrmcfg);
uint8_t usb3_dep_startxfer(usb3_pcd_t *pcd, usb3_dev_ep_regs_t *ep_reg,
			phys_addr_t dma_addr, uint32_t stream_or_uf);
void usb3_dep_updatexfer(usb3_pcd_t *pcd,
			    usb3_dev_ep_regs_t *ep_reg,
			    uint32_t tri);
void usb3_ep_activate(usb3_pcd_t *pcd, usb3_pcd_ep_t *ep);
void usb3_ep0_out_start(usb3_pcd_t *pcd);
void usb3_ep0_start_transfer(usb3_pcd_t *pcd, usb3_pcd_req_t *req);
void usb3_resume_usb2_phy(usb3_pcd_t *pcd);
//int usb_connected = 0;

#endif /* __USB3_DRIVER_H */

