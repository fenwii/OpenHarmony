#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/dev/usb/storage/umass.c 331722 2018-03-29 02:50:57Z eadler $");

/*-
 * Copyright (c) 1999 MAEKAWA Masahide <bishop@rr.iij4u.or.jp>,
 *		      Nick Hibma <n_hibma@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$FreeBSD: releng/11.4/sys/dev/usb/storage/umass.c 331722 2018-03-29 02:50:57Z eadler $
 *	$NetBSD: umass.c,v 1.28 2000/04/02 23:46:53 augustss Exp $
 */

/* Also already merged from NetBSD:
 *	$NetBSD: umass.c,v 1.67 2001/11/25 19:05:22 augustss Exp $
 *	$NetBSD: umass.c,v 1.90 2002/11/04 19:17:33 pooka Exp $
 *	$NetBSD: umass.c,v 1.108 2003/11/07 17:03:25 wiz Exp $
 *	$NetBSD: umass.c,v 1.109 2003/12/04 13:57:31 keihan Exp $
 */

/*
 * Universal Serial Bus Mass Storage Class specs:
 * http://www.usb.org/developers/devclass_docs/usb_msc_overview_1.2.pdf
 * http://www.usb.org/developers/devclass_docs/usbmassbulk_10.pdf
 * http://www.usb.org/developers/devclass_docs/usb_msc_cbi_1.1.pdf
 * http://www.usb.org/developers/devclass_docs/usbmass-ufi10.pdf
 */

/*
 * Ported to NetBSD by Lennart Augustsson <augustss@NetBSD.org>.
 * Parts of the code written by Jason R. Thorpe <thorpej@shagadelic.org>.
 */

/*
 * The driver handles 3 Wire Protocols
 * - Command/Bulk/Interrupt (CBI)
 * - Command/Bulk/Interrupt with Command Completion Interrupt (CBI with CCI)
 * - Mass Storage Bulk-Only (BBB)
 *   (BBB refers Bulk/Bulk/Bulk for Command/Data/Status phases)
 *
 * Over these wire protocols it handles the following command protocols
 * - SCSI
 * - UFI (floppy command set)
 * - 8070i (ATAPI)
 *
 * UFI and 8070i (ATAPI) are transformed versions of the SCSI command set. The
 * sc->sc_transform method is used to convert the commands into the appropriate
 * format (if at all necessary). For example, UFI requires all commands to be
 * 12 bytes in length amongst other things.
 *
 * The source code below is marked and can be split into a number of pieces
 * (in this order):
 *
 * - probe/attach/detach
 * - generic transfer routines
 * - BBB
 * - CBI
 * - CBI_I (in addition to functions from CBI)
 * - CAM (Common Access Method)
 * - SCSI
 * - UFI
 * - 8070i (ATAPI)
 *
 * The protocols are implemented using a state machine, for the transfers as
 * well as for the resets. The state machine is contained in umass_t_*_callback.
 * The state machine is started through either umass_command_start() or
 * umass_reset().
 *
 * The reason for doing this is a) CAM performs a lot better this way and b) it
 * avoids using tsleep from interrupt context (for example after a failed
 * transfer).
 */

/*
 * The SCSI related part of this driver has been derived from the
 * dev/ppbus/vpo.c driver, by Nicolas Souchu (nsouch@FreeBSD.org).
 *
 * The CAM layer uses so called actions which are messages sent to the host
 * adapter for completion. The actions come in through umass_cam_action. The
 * appropriate block of routines is called depending on the transport protocol
 * in use. When the transfer has finished, these routines call
 * umass_cam_cb again to complete the CAM command.
 */

#include <driver.h>
#include <disk.h>

#include "implementation/global_implementation.h"
#include "scsi_all.h"
#include "scsi.h"
#include "umass_fs.h"
#if USB_HAVE_DEVICE_TOPOLOGY
#include "implementation/usb_btree.h"
#endif
#include "user_copy.h"

#ifdef LOSCFG_USB_DEBUG
#define	DIF(m, x)				\
  do {						\
    if (umass_debug & (m)) { x ; }		\
  } while (0)

#define	DPRINTF_UMASS(sc, m, fmt, ...)			\
  do {							\
	if (umass_debug & (m)) {				\
		PRINTK("%s:%s: " fmt,				\
		    (sc) ? (const char *)(sc)->sc_name :	\
		    (const char *)"umassX",			\
		    __FUNCTION__ ,## __VA_ARGS__);		\
	}							\
  } while (0)

#define	UDMASS_GEN	0x00010000	/* general */
#define	UDMASS_SCSI	0x00020000	/* scsi */
#define	UDMASS_UFI	0x00040000	/* ufi command set */
#define	UDMASS_ATAPI	0x00080000	/* 8070i command set */
#define	UDMASS_CMD	(UDMASS_SCSI|UDMASS_UFI|UDMASS_ATAPI)
#define	UDMASS_USB	0x00100000	/* USB general */
#define	UDMASS_BBB	0x00200000	/* Bulk-Only transfers */
#define	UDMASS_CBI	0x00400000	/* CBI transfers */
#define	UDMASS_WIRE	(UDMASS_BBB|UDMASS_CBI)
#define	UDMASS_ALL	0xffff0000	/* all of the above */
static int umass_debug = 0; 	/* UDMASS_ALL; */
static int umass_throttle;

void
umass_debug_func(int level)
{
	switch(level) {
		case 0:
			umass_debug = 0;
			PRINTK("Close the umass debug\n");
			break;
		case UDMASS_GEN:
		case UDMASS_SCSI:
		case UDMASS_UFI:
		case UDMASS_ATAPI:
		case UDMASS_CMD:
		case UDMASS_USB:
		case UDMASS_BBB:
		case UDMASS_CBI:
		case UDMASS_WIRE:
		case UDMASS_ALL:
			umass_debug = level;
			PRINTK("The level of umass debug is %x\n", level);
			break;
		default:
			PRINT_ERR("The level of umass debug is invalid, please refer to umass.c\n");
			break;
	}
}
DEBUG_MODULE(umass, umass_debug_func);
#else
#define	DIF(...) do { } while (0)
#define	DPRINTF_UMASS(...) do { } while (0)
#endif

#define	UMASS_BULK_SIZE (1 << 17)
#define	UMASS_CBI_DIAGNOSTIC_CMDLEN 12	/* bytes */
#define	UMASS_MAX_CMDLEN MAX(12, CBWCDBLENGTH)	/* bytes */

/* USB transfer definitions */

#define	UMASS_T_BBB_RESET1		0	/* Bulk-Only */
#define	UMASS_T_BBB_RESET2		1
#define	UMASS_T_BBB_RESET3		2
#define	UMASS_T_BBB_COMMAND		3
#define	UMASS_T_BBB_DATA_READ	4
#define	UMASS_T_BBB_DATA_RD_CS	5
#define	UMASS_T_BBB_DATA_WRITE	6
#define	UMASS_T_BBB_DATA_WR_CS	7
#define	UMASS_T_BBB_STATUS		8
#define	UMASS_T_BBB_MAX			9

#define	UMASS_T_CBI_RESET1		0	/* CBI */
#define	UMASS_T_CBI_RESET2		1
#define	UMASS_T_CBI_RESET3		2
#define	UMASS_T_CBI_COMMAND		3
#define	UMASS_T_CBI_DATA_READ	4
#define	UMASS_T_CBI_DATA_RD_CS	5
#define	UMASS_T_CBI_DATA_WRITE	6
#define	UMASS_T_CBI_DATA_WR_CS	7
#define	UMASS_T_CBI_STATUS		8
#define	UMASS_T_CBI_RESET4		9
#define	UMASS_T_CBI_MAX			10

#define	UMASS_T_MAX MAX(UMASS_T_CBI_MAX, UMASS_T_BBB_MAX)

/* Generic definitions */

/* Direction for transfer */
#define	DIR_NONE	0
#define	DIR_IN		1
#define	DIR_OUT		2

/* device name */
#define	DEVNAME		"umass"
#define	DEVNAME_SIM	"umass-sim"

/* Approximate maximum transfer speeds (assumes 33% overhead). */
#define	UMASS_FULL_TRANSFER_SPEED	1000
#define	UMASS_HIGH_TRANSFER_SPEED	40000
#define	UMASS_SUPER_TRANSFER_SPEED	400000
#define	UMASS_FLOPPY_TRANSFER_SPEED	20

#define	UMASS_TIMEOUT			20000	/* ms */

/* CAM specific definitions */
#define	UMASS_SCSIID_MAX	1	/* maximum number of drives expected */
#define	UMASS_SCSIID_HOST	UMASS_SCSIID_MAX

/* Bulk-Only features */
#define	UR_BBB_RESET		0xff	/* Bulk-Only reset */
#define	UR_BBB_GET_MAX_LUN	0xfe	/* Get maximum lun */

/*
 * SCSI I/O Request CCB used for the XPT_SCSI_IO and XPT_CONT_TARGET_IO
 * function codes.
 */
struct ccb_scsiio {
	uint8_t *data_ptr;		/* Ptr to the data buf/SG list */
	uint32_t dxfer_len;		/* Data transfer length */
	uint32_t resid;			/* Transfer residual length: 2's comp */
	int32_t  status;

	struct	 scsi_sense_data sense_data;
	uint8_t   sense_len;	/* Number of bytes to autosense */
};

union ccb {
	struct	ccb_scsiio	csio;
};


/* Command Block Wrapper */
typedef struct {
	uDWord	dCBWSignature;
#define	CBWSIGNATURE	0x43425355
	uDWord	dCBWTag;
	uDWord	dCBWDataTransferLength;
	uByte	bCBWFlags;
#define	CBWFLAGS_OUT	0x00
#define	CBWFLAGS_IN		0x80
	uByte	bCBWLUN;
	uByte	bCDBLength;
#define	CBWCDBLENGTH	16
	uByte	CBWCDB[CBWCDBLENGTH];
} __packed umass_bbb_cbw_t;

#define	UMASS_BBB_CBW_SIZE	31

/* Command Status Wrapper */
typedef struct {
	uDWord	dCSWSignature;
#define	CSWSIGNATURE					0x53425355
#define	CSWSIGNATURE_IMAGINATION_DBX1	0x43425355
#define	CSWSIGNATURE_OLYMPUS_C1			0x55425355
	uDWord	dCSWTag;
	uDWord	dCSWDataResidue;
	uByte	bCSWStatus;
#define	CSWSTATUS_GOOD		0x0
#define	CSWSTATUS_FAILED	0x1
#define	CSWSTATUS_PHASE		0x2
} __packed umass_bbb_csw_t;

#define	UMASS_BBB_CSW_SIZE	13

/* CBI features */

#define	UR_CBI_ADSC	0x00

typedef union {
	struct {
		uint8_t	type;
#define	IDB_TYPE_CCI			0x00
		uint8_t	value;
#define	IDB_VALUE_PASS			0x00
#define	IDB_VALUE_FAIL			0x01
#define	IDB_VALUE_PHASE			0x02
#define	IDB_VALUE_PERSISTENT	0x03
#define	IDB_VALUE_STATUS_MASK	0x03
	} __packed common;

	struct {
		uint8_t	asc;
		uint8_t	ascq;
	} __packed ufi;
} __packed umass_cbi_sbl_t;

struct umass_info {
	uint32_t sectorsize;
	uint64_t sectornum;
};

struct umass_softc;			/* see below */

typedef void (umass_callback_t)(struct umass_softc *sc, union ccb *ccb,
		uint32_t residue, uint8_t status);

#define	STATUS_CMD_OK		0	/* everything ok */
#define	STATUS_CMD_UNKNOWN	1	/* will have to fetch sense */
#define	STATUS_CMD_FAILED	2	/* transfer was ok, command failed */
#define	STATUS_WIRE_FAILED	3	/* couldn't even get command across */

typedef uint8_t (umass_transform_t)(struct umass_softc *sc, uint8_t *cmd_ptr,
	    uint8_t cmd_len);

/* Wire and command protocol */
#define	UMASS_PROTO_BBB		0x0001	/* USB wire protocol */
#define	UMASS_PROTO_CBI		0x0002
#define	UMASS_PROTO_CBI_I	0x0004
#define	UMASS_PROTO_WIRE	0x00ff	/* USB wire protocol mask */
#define	UMASS_PROTO_SCSI	0x0100	/* command protocol */
#define	UMASS_PROTO_ATAPI	0x0200
#define	UMASS_PROTO_UFI		0x0400
#define	UMASS_PROTO_RBC		0x0800
#define	UMASS_PROTO_COMMAND	0xff00	/* command protocol mask */

/* Device specific quirks */
#define	NO_QUIRKS			0x0000
	/*
	 * The drive does not support Test Unit Ready. Convert to Start Unit
	 */
#define	NO_TEST_UNIT_READY	0x0001
	/*
	 * The drive does not reset the Unit Attention state after REQUEST
	 * SENSE has been sent. The INQUIRY command does not reset the UA
	 * either, and so CAM runs in circles trying to retrieve the initial
	 * INQUIRY data.
	 */
#define	RS_NO_CLEAR_UA		0x0002
	/* The drive does not support START STOP.  */
#define	NO_START_STOP		0x0004
	/* Don't ask for full inquiry data (255b).  */
#define	FORCE_SHORT_INQUIRY	0x0008
	/* Needs to be initialised the Shuttle way */
#define	SHUTTLE_INIT		0x0010
	/* Drive needs to be switched to alternate iface 1 */
#define	ALT_IFACE_1			0x0020
	/* Drive does not do 1Mb/s, but just floppy speeds (20kb/s) */
#define	FLOPPY_SPEED		0x0040
	/* The device can't count and gets the residue of transfers wrong */
#define	IGNORE_RESIDUE		0x0080
	/* No GetMaxLun call */
#define	NO_GETMAXLUN		0x0100
	/* The device uses a weird CSWSIGNATURE. */
#define	WRONG_CSWSIG		0x0200
	/* Device cannot handle INQUIRY so fake a generic response */
#define	NO_INQUIRY			0x0400
	/* Device cannot handle INQUIRY EVPD, return CHECK CONDITION */
#define	NO_INQUIRY_EVPD		0x0800
	/* Pad all RBC requests to 12 bytes. */
#define	RBC_PAD_TO_12		0x1000
	/*
	 * Device reports number of sectors from READ_CAPACITY, not max
	 * sector number.
	 */
#define	READ_CAPACITY_OFFBY1	0x2000
	/*
	 * Device cannot handle a SCSI synchronize cache command.  Normally
	 * this quirk would be handled in the cam layer, but for IDE bridges
	 * we need to associate the quirk with the bridge and not the
	 * underlying disk device.  This is handled by faking a success
	 * result.
	 */
#define	NO_SYNCHRONIZE_CACHE	0x4000
	/* Device does not support 'PREVENT/ALLOW MEDIUM REMOVAL'. */
#define	NO_PREVENT_ALLOW		0x8000

#if USB_HAVE_DEVICE_TOPOLOGY
extern usbd_bt_tree hub_tree;
#endif

struct umass_softc {
	union ccb *data_ccb;
	struct scsi_sense cam_scsi_sense;
	struct scsi_test_unit_ready cam_scsi_test_unit_ready;
	struct mtx sc_mtx;
	EVENT_CB_S sc_event;
	struct {
		uint8_t *data_ptr;
		union ccb *ccb;
		umass_callback_t *callback;

		uint32_t data_len;		/* bytes */
		uint32_t data_rem;		/* bytes */
		uint32_t data_timeout;	/* ms */
		uint32_t actlen;		/* bytes */

		uint8_t	cmd_data[UMASS_MAX_CMDLEN];
		uint8_t	cmd_len;		/* bytes */
		uint8_t	dir;
		uint8_t	lun;
	}	sc_transfer;

	struct umass_info info;

	/* Bulk specific variables for transfers in progress */
	umass_bbb_cbw_t cbw;		/* command block wrapper */
	umass_bbb_csw_t csw;		/* command status wrapper */

	/* CBI specific variables for transfers in progress */
	umass_cbi_sbl_t sbl;		/* status block */

	device_t sc_dev;
	struct usb_device *sc_udev;
	struct usb_xfer *sc_xfer[UMASS_T_MAX];

	/*
	 * The command transform function is used to convert the SCSI
	 * commands into their derivatives, like UFI, ATAPI, and friends.
	 */
	umass_transform_t *sc_transform;

	uint32_t sc_unit;
	uint32_t sc_quirks;		/* they got it almost right */
	uint32_t sc_proto;		/* wire and cmd protocol */

	uint8_t	sc_name[16];
	uint8_t	sc_iface_no;	/* interface number */
	uint8_t	sc_maxlun;		/* maximum LUN number, inclusive */
	uint8_t	sc_last_xfer_index;
	uint8_t	sc_status_try;
	BOOL	sc_detach_status;
	BOOL	sc_super_disk;		/* TRUE: Disk is bigger than 2T; FALSE: Disk is less than 2T */
	struct mtx sc_umass_mtx;	/* The mtx is used to prevent data read and write competition */
};

struct umass_probe_proto {
	uint32_t quirks;
	uint32_t proto;

	int	error;
};

#if USB_SUPPORT_SD_HOT_PLUG
struct umass_dev_info {
	struct umass_softc *sc;
	unsigned int dev_unit;
	int used;			/* 0: not use; 1: in use */
	int attached;		/* 0: not attach; 1: in attach */
	struct mtx dev_mtx;	/* The mtx is used to prevent U disk insertion or extraction competition */
};

static struct umass_dev_info g_umass_dev_array[MAX_DEVICE] = {0};
static void umass_task_check(int flag);
static void umass_dev_delete(struct umass_softc *sc, unsigned int dev_unit);
int umass_dev_is_attached(unsigned int dev_unit);
static void umass_dev_attach_flag_set(int dev_unit);
pthread_t   umass_taskid;
#define	umass_dev_mtx_init(id, type) (void)mtx_init(&g_umass_dev_array[id].dev_mtx, NULL, NULL, type)
#define	umass_dev_mtx_destroy(id)	 (void)mtx_destroy(&g_umass_dev_array[id].dev_mtx)
#define	umass_dev_lock(id)			 (void)mtx_lock(&g_umass_dev_array[id].dev_mtx)
#define	umass_dev_unlock(id)		 (void)mtx_unlock(&g_umass_dev_array[id].dev_mtx)
#else
#define	umass_dev_lock(id) (void)mtx_lock(NULL)
#define	umass_dev_unlock(id) (void)mtx_unlock(NULL)
#endif

struct umass_softc *p_umsf = NULL;
/* prototypes */

static device_probe_t umass_probe;
static device_attach_t umass_attach;
static device_detach_t umass_detach;

static usb_callback_t umass_tr_error;
static usb_callback_t umass_t_bbb_reset1_callback;
static usb_callback_t umass_t_bbb_reset2_callback;
static usb_callback_t umass_t_bbb_reset3_callback;
static usb_callback_t umass_t_bbb_command_callback;
static usb_callback_t umass_t_bbb_data_read_callback;
static usb_callback_t umass_t_bbb_data_rd_cs_callback;
static usb_callback_t umass_t_bbb_data_write_callback;
static usb_callback_t umass_t_bbb_data_wr_cs_callback;
static usb_callback_t umass_t_bbb_status_callback;
static usb_callback_t umass_t_cbi_reset1_callback;
static usb_callback_t umass_t_cbi_reset2_callback;
static usb_callback_t umass_t_cbi_reset3_callback;
static usb_callback_t umass_t_cbi_reset4_callback;
static usb_callback_t umass_t_cbi_command_callback;
static usb_callback_t umass_t_cbi_data_read_callback;
static usb_callback_t umass_t_cbi_data_rd_cs_callback;
static usb_callback_t umass_t_cbi_data_write_callback;
static usb_callback_t umass_t_cbi_data_wr_cs_callback;
static usb_callback_t umass_t_cbi_status_callback;

static void	umass_cancel_ccb(struct umass_softc *);
static void	umass_init_shuttle(struct umass_softc *);
static void	umass_t_bbb_data_clear_stall_callback(struct usb_xfer *,
			uint8_t, uint8_t, usb_error_t);
static int	umass_command_start(struct umass_softc *, uint8_t, void *,
			uint32_t, uint32_t, umass_callback_t *, union ccb *);
static uint8_t	umass_bbb_get_max_lun(struct umass_softc *);
static void	umass_cbi_start_status(struct umass_softc *);
static void	umass_t_cbi_data_clear_stall_callback(struct usb_xfer *,
			uint8_t, uint8_t, usb_error_t);
static void	umass_cam_cb(struct umass_softc *, union ccb *, uint32_t, uint8_t);
static uint8_t	umass_scsi_transform(struct umass_softc *, uint8_t *, uint8_t);
static uint8_t	umass_rbc_transform(struct umass_softc *, uint8_t *, uint8_t);
static uint8_t	umass_ufi_transform(struct umass_softc *, uint8_t *, uint8_t);
static uint8_t	umass_atapi_transform(struct umass_softc *, uint8_t *,
			uint8_t);
static uint8_t	umass_no_transform(struct umass_softc *, uint8_t *, uint8_t);

#ifdef LOSCFG_USB_DEBUG
static void	umass_bbb_dump_cbw(struct umass_softc *, umass_bbb_cbw_t *);
static void	umass_bbb_dump_csw(struct umass_softc *, umass_bbb_csw_t *);
static void	umass_cbi_dump_cmd(struct umass_softc *, void *, uint8_t);
#endif

static void devunit_to_devname(unsigned int dev_unit, char *devname);
static int32_t umass_attach_dev(struct umass_softc *sc, unsigned int dev_unit);
static void umass_detach_dev_sub(struct umass_softc *sc, int dev_unit, int flag);

static struct usb_config umass_bbb_config[UMASS_T_BBB_MAX] = {

	[UMASS_T_BBB_RESET1] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_bbb_reset1_callback,
		.timeout = 5000,	/* 5 seconds */
		.interval = 500,	/* 500 milliseconds */
	},

	[UMASS_T_BBB_RESET2] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_bbb_reset2_callback,
		.timeout = 5000,	/* 5 seconds */
		.interval = 50,	/* 50 milliseconds */
	},

	[UMASS_T_BBB_RESET3] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_bbb_reset3_callback,
		.timeout = 5000,	/* 5 seconds */
		.interval = 50,	/* 50 milliseconds */
	},

	[UMASS_T_BBB_COMMAND] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_OUT,
		.bufsize = sizeof(umass_bbb_cbw_t),
		.callback = &umass_t_bbb_command_callback,
		.timeout = 5000,	/* 5 seconds */
	},

	[UMASS_T_BBB_DATA_READ] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.bufsize = UMASS_BULK_SIZE,
		.flags = {.proxy_buffer = 1,.short_xfer_ok = 1,.ext_buffer=1,},
		.callback = &umass_t_bbb_data_read_callback,
		.timeout = 0,	/* overwritten later */
	},

	[UMASS_T_BBB_DATA_RD_CS] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_bbb_data_rd_cs_callback,
		.timeout = 5000,	/* 5 seconds */
	},

	[UMASS_T_BBB_DATA_WRITE] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_OUT,
		.bufsize = UMASS_BULK_SIZE,
		.flags = {.proxy_buffer = 1,.short_xfer_ok = 1,.ext_buffer=1,},
		.callback = &umass_t_bbb_data_write_callback,
		.timeout = 0,	/* overwritten later */
	},

	[UMASS_T_BBB_DATA_WR_CS] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_bbb_data_wr_cs_callback,
		.timeout = 5000,	/* 5 seconds */
	},

	[UMASS_T_BBB_STATUS] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.bufsize = sizeof(umass_bbb_csw_t),
		.flags = {.short_xfer_ok = 1,},
		.callback = &umass_t_bbb_status_callback,
		.timeout = 5000,	/* ms */
	},
};

static struct usb_config umass_cbi_config[UMASS_T_CBI_MAX] = {

	[UMASS_T_CBI_RESET1] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = (sizeof(struct usb_device_request) +
		    UMASS_CBI_DIAGNOSTIC_CMDLEN),
		.callback = &umass_t_cbi_reset1_callback,
		.timeout = 5000,	/* 5 seconds */
		.interval = 500,	/* 500 milliseconds */
	},

	[UMASS_T_CBI_RESET2] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_cbi_reset2_callback,
		.timeout = 5000,	/* 5 seconds */
		.interval = 50,	/* 50 milliseconds */
	},

	[UMASS_T_CBI_RESET3] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_cbi_reset3_callback,
		.timeout = 5000,	/* 5 seconds */
		.interval = 50,	/* 50 milliseconds */
	},

	[UMASS_T_CBI_COMMAND] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = (sizeof(struct usb_device_request) +
		    UMASS_MAX_CMDLEN),
		.callback = &umass_t_cbi_command_callback,
		.timeout = 5000,	/* 5 seconds */
	},

	[UMASS_T_CBI_DATA_READ] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.bufsize = UMASS_BULK_SIZE,
		.flags = {.proxy_buffer = 1,.short_xfer_ok = 1,.ext_buffer=1,},
		.callback = &umass_t_cbi_data_read_callback,
		.timeout = 0,	/* overwritten later */
	},

	[UMASS_T_CBI_DATA_RD_CS] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_cbi_data_rd_cs_callback,
		.timeout = 5000,	/* 5 seconds */
	},

	[UMASS_T_CBI_DATA_WRITE] = {
		.type = UE_BULK,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_OUT,
		.bufsize = UMASS_BULK_SIZE,
		.flags = {.proxy_buffer = 1,.short_xfer_ok = 1,.ext_buffer=1,},
		.callback = &umass_t_cbi_data_write_callback,
		.timeout = 0,	/* overwritten later */
	},

	[UMASS_T_CBI_DATA_WR_CS] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_cbi_data_wr_cs_callback,
		.timeout = 5000,	/* 5 seconds */
	},

	[UMASS_T_CBI_STATUS] = {
		.type = UE_INTERRUPT,
		.endpoint = UE_ADDR_ANY,
		.direction = UE_DIR_IN,
		.flags = {.short_xfer_ok = 1,.no_pipe_ok = 1,},
		.bufsize = sizeof(umass_cbi_sbl_t),
		.callback = &umass_t_cbi_status_callback,
		.timeout = 5000,	/* ms */
	},

	[UMASS_T_CBI_RESET4] = {
		.type = UE_CONTROL,
		.endpoint = 0x00,	/* Control pipe */
		.direction = UE_DIR_ANY,
		.bufsize = sizeof(struct usb_device_request),
		.callback = &umass_t_cbi_reset4_callback,
		.timeout = 5000,	/* ms */
	},
};

#define	UFI_COMMAND_LENGTH	12	/* UFI commands are always 12 bytes */
#define	ATAPI_COMMAND_LENGTH	12	/* ATAPI commands are always 12 bytes */

static devclass_t umass_devclass;

static device_method_t umass_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe, umass_probe),
	DEVMETHOD(device_attach, umass_attach),
	DEVMETHOD(device_detach, umass_detach),

	DEVMETHOD_END
};

static driver_t umass_driver = {
	.name = "umass",
	.methods = umass_methods,
	.size = sizeof(struct umass_softc),
};

#if USB_HAVE_DEVICE_TOPOLOGY
UINT64 dev_quantity = 0;
#endif

DRIVER_MODULE(umass, uhub, umass_driver, umass_devclass, NULL, 0);

static uint16_t
umass_get_proto(struct usb_interface *iface)
{
	struct usb_interface_descriptor *id;
	uint16_t retval;

	retval = 0;

	/* Check for a standards compliant device */
	id = usbd_get_interface_descriptor(iface);
	if ((id == NULL) ||
	    (id->bInterfaceClass != UICLASS_MASS)) {
		goto done;
	}
	switch (id->bInterfaceSubClass) {
	case UISUBCLASS_SCSI:
		retval |= UMASS_PROTO_SCSI;
		break;
	case UISUBCLASS_UFI:
		retval |= UMASS_PROTO_UFI;
		break;
	case UISUBCLASS_RBC:
		retval |= UMASS_PROTO_RBC;
		break;
	case UISUBCLASS_SFF8020I:
	case UISUBCLASS_SFF8070I:
		retval |= UMASS_PROTO_ATAPI;
		break;
	default:
		goto done;
	}

	switch (id->bInterfaceProtocol) {
	case UIPROTO_MASS_CBI:
		retval |= UMASS_PROTO_CBI;
		break;
	case UIPROTO_MASS_CBI_I:
		retval |= UMASS_PROTO_CBI_I;
		break;
	case UIPROTO_MASS_BBB_OLD:
	case UIPROTO_MASS_BBB:
		retval |= UMASS_PROTO_BBB;
		break;
	default:
		goto done;
	}
done:
	return (retval);
}

/*
 * Match the device we are seeing with the devices supported.
 */
static struct umass_probe_proto
umass_probe_proto(device_t dev, struct usb_attach_arg *uaa)
{
	struct umass_probe_proto ret;
	uint32_t quirks = NO_QUIRKS;
	uint32_t proto = umass_get_proto(uaa->iface);

	(void)memset_s(&ret, sizeof(ret), 0, sizeof(ret));
	ret.error = BUS_PROBE_GENERIC;

	/* Search for protocol enforcement */

	if (usb_test_quirk(uaa, UQ_MSC_FORCE_WIRE_BBB)) {
		proto &= ~UMASS_PROTO_WIRE;
		proto |= UMASS_PROTO_BBB;
	} else if (usb_test_quirk(uaa, UQ_MSC_FORCE_WIRE_CBI)) {
		proto &= ~UMASS_PROTO_WIRE;
		proto |= UMASS_PROTO_CBI;
	} else if (usb_test_quirk(uaa, UQ_MSC_FORCE_WIRE_CBI_I)) {
		proto &= ~UMASS_PROTO_WIRE;
		proto |= UMASS_PROTO_CBI_I;
	}

	if (usb_test_quirk(uaa, UQ_MSC_FORCE_PROTO_SCSI)) {
		proto &= ~UMASS_PROTO_COMMAND;
		proto |= UMASS_PROTO_SCSI;
	} else if (usb_test_quirk(uaa, UQ_MSC_FORCE_PROTO_ATAPI)) {
		proto &= ~UMASS_PROTO_COMMAND;
		proto |= UMASS_PROTO_ATAPI;
	} else if (usb_test_quirk(uaa, UQ_MSC_FORCE_PROTO_UFI)) {
		proto &= ~UMASS_PROTO_COMMAND;
		proto |= UMASS_PROTO_UFI;
	} else if (usb_test_quirk(uaa, UQ_MSC_FORCE_PROTO_RBC)) {
		proto &= ~UMASS_PROTO_COMMAND;
		proto |= UMASS_PROTO_RBC;
	}

	/* Check if the protocol is invalid */

	if ((proto & UMASS_PROTO_COMMAND) == 0) {
		ret.error = ENXIO;
		goto done;
	}

	if ((proto & UMASS_PROTO_WIRE) == 0) {
		ret.error = ENXIO;
		goto done;
	}

	/* Search for quirks */

	if (usb_test_quirk(uaa, UQ_MSC_NO_TEST_UNIT_READY))
		quirks |= NO_TEST_UNIT_READY;
	if (usb_test_quirk(uaa, UQ_MSC_NO_RS_CLEAR_UA))
		quirks |= RS_NO_CLEAR_UA;
	if (usb_test_quirk(uaa, UQ_MSC_NO_START_STOP))
		quirks |= NO_START_STOP;
	if (usb_test_quirk(uaa, UQ_MSC_NO_GETMAXLUN))
		quirks |= NO_GETMAXLUN;
	if (usb_test_quirk(uaa, UQ_MSC_NO_INQUIRY))
		quirks |= NO_INQUIRY;
	if (usb_test_quirk(uaa, UQ_MSC_NO_INQUIRY_EVPD))
		quirks |= NO_INQUIRY_EVPD;
	if (usb_test_quirk(uaa, UQ_MSC_NO_PREVENT_ALLOW))
		quirks |= NO_PREVENT_ALLOW;
	if (usb_test_quirk(uaa, UQ_MSC_NO_SYNC_CACHE))
		quirks |= NO_SYNCHRONIZE_CACHE;
	if (usb_test_quirk(uaa, UQ_MSC_SHUTTLE_INIT))
		quirks |= SHUTTLE_INIT;
	if (usb_test_quirk(uaa, UQ_MSC_ALT_IFACE_1))
		quirks |= ALT_IFACE_1;
	if (usb_test_quirk(uaa, UQ_MSC_FLOPPY_SPEED))
		quirks |= FLOPPY_SPEED;
	if (usb_test_quirk(uaa, UQ_MSC_IGNORE_RESIDUE))
		quirks |= IGNORE_RESIDUE;
	if (usb_test_quirk(uaa, UQ_MSC_WRONG_CSWSIG))
		quirks |= WRONG_CSWSIG;
	if (usb_test_quirk(uaa, UQ_MSC_RBC_PAD_TO_12))
		quirks |= RBC_PAD_TO_12;
	if (usb_test_quirk(uaa, UQ_MSC_READ_CAP_OFFBY1))
		quirks |= READ_CAPACITY_OFFBY1;
	if (usb_test_quirk(uaa, UQ_MSC_FORCE_SHORT_INQ))
		quirks |= FORCE_SHORT_INQUIRY;

done:
	ret.quirks = quirks;
	ret.proto = proto;
	return (ret);
}

static int
umass_probe(device_t dev)
{
	struct usb_attach_arg *uaa =
	    (struct usb_attach_arg *)device_get_ivars(dev);
	struct umass_probe_proto temp;

	if (uaa->usb_mode != USB_MODE_HOST) {
		return (ENXIO);
	}
	temp = umass_probe_proto(dev, uaa);

	return (temp.error);
}

static int
umass_attach(device_t dev)
{
	struct umass_softc *sc =
		(struct umass_softc *)device_get_softc(dev);
	struct usb_attach_arg *uaa =
		(struct usb_attach_arg *)device_get_ivars(dev);
	struct umass_probe_proto temp = umass_probe_proto(dev, uaa);
	struct usb_interface_descriptor *id;
	usb_error_t err;

	/*
	 * NOTE: the softc struct is cleared in device_set_driver.
	 * We can safely call umass_detach without specifically
	 * initializing the struct.
	 */

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;
	sc->sc_proto = temp.proto;
	sc->sc_quirks = temp.quirks;
	sc->sc_unit = device_get_unit(dev);
	sc->data_ccb = NULL;
	sc->sc_detach_status = FALSE;
	sc->sc_super_disk = FALSE;

#if USB_HAVE_DEVICE_TOPOLOGY
	dev_quantity |= 1ull << (unsigned int)device_get_unit(dev);
#endif

	(void)snprintf_s((char *)sc->sc_name, sizeof(sc->sc_name), sizeof(sc->sc_name) - 1,
	    "%s", device_get_nameunit(dev));

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev),
		    NULL, MTX_DEF | MTX_RECURSE);
	mtx_init(&sc->sc_umass_mtx, device_get_nameunit(dev),
		    NULL, MTX_DEF | MTX_RECURSE);

	(void)LOS_EventInit(&sc->sc_event);

	/* get interface index */

	id = usbd_get_interface_descriptor(uaa->iface);
	if (id == NULL) {
		device_printf(dev, "failed to get "
			"interface number\n");
		goto detach;
	}
	sc->sc_iface_no = id->bInterfaceNumber;

	device_printf(dev, " ");

	switch (sc->sc_proto & UMASS_PROTO_COMMAND) {
	case UMASS_PROTO_SCSI:
		PRINTK("SCSI");
		break;
	case UMASS_PROTO_ATAPI:
		PRINTK("8070i (ATAPI)");
		break;
	case UMASS_PROTO_UFI:
		PRINTK("UFI");
		break;
	case UMASS_PROTO_RBC:
		PRINTK("RBC");
		break;
	default:
		PRINTK("(unknown 0x%02x)",
		    sc->sc_proto & UMASS_PROTO_COMMAND);
		break;
	}

	PRINTK(" over ");

	switch (sc->sc_proto & UMASS_PROTO_WIRE) {
	case UMASS_PROTO_BBB:
		PRINTK("Bulk-Only");
		break;
	case UMASS_PROTO_CBI:		/* uses Comand/Bulk pipes */
		PRINTK("CBI");
		break;
	case UMASS_PROTO_CBI_I:	/* uses Comand/Bulk/Interrupt pipes */
		PRINTK("CBI with CCI");
		break;
	default:
		PRINTK("(unknown 0x%02x)",
		    sc->sc_proto & UMASS_PROTO_WIRE);
	}

	PRINTK("; quirks = 0x%04x\n", sc->sc_quirks);

	if (sc->sc_quirks & ALT_IFACE_1) {
		err = usbd_set_alt_interface_index
		    (uaa->device, uaa->info.bIfaceIndex, 1);

		if (err) {
			DPRINTF_UMASS(sc, UDMASS_USB, "could not switch to "
			    "Alt Interface 1\n");
			goto detach;
		}
	}
	/* allocate all required USB transfers */

	if (sc->sc_proto & UMASS_PROTO_BBB) {

		err = usbd_transfer_setup(uaa->device,
		    &uaa->info.bIfaceIndex, sc->sc_xfer, umass_bbb_config,
		    UMASS_T_BBB_MAX, sc, &sc->sc_mtx);

		/* skip reset first time */
		sc->sc_last_xfer_index = UMASS_T_BBB_COMMAND;

	} else if (sc->sc_proto & (UMASS_PROTO_CBI | UMASS_PROTO_CBI_I)) {

		err = usbd_transfer_setup(uaa->device,
		    &uaa->info.bIfaceIndex, sc->sc_xfer, umass_cbi_config,
		    UMASS_T_CBI_MAX, sc, &sc->sc_mtx);

		/* skip reset first time */
		sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

	} else {
		err = USB_ERR_INVAL;
	}

	if (err) {
		device_printf(dev, "could not setup required "
		    "transfers, %s\n", usbd_errstr(err));
		goto detach;
	}
#ifdef LOSCFG_USB_DEBUG
	if (umass_throttle > 0) {
		uint8_t x;
		int iv;

		iv = umass_throttle;

		if (iv < 1)
			iv = 1;
		else if (iv > 8000)
			iv = 8000;

		for (x = 0; x != UMASS_T_MAX; x++) {
			if (sc->sc_xfer[x] != NULL)
				usbd_xfer_set_interval(sc->sc_xfer[x], iv);
		}
	}
#endif
	sc->sc_transform =
	    (sc->sc_proto & UMASS_PROTO_SCSI) ? &umass_scsi_transform :
	    (sc->sc_proto & UMASS_PROTO_UFI) ? &umass_ufi_transform :
	    (sc->sc_proto & UMASS_PROTO_ATAPI) ? &umass_atapi_transform :
	    (sc->sc_proto & UMASS_PROTO_RBC) ? &umass_rbc_transform :
	    &umass_no_transform;

	/* from here onwards the device can be used. */

	if (sc->sc_quirks & SHUTTLE_INIT) {
		umass_init_shuttle(sc);
	}
	/* get the maximum LUN supported by the device */

	if (((sc->sc_proto & UMASS_PROTO_WIRE) == UMASS_PROTO_BBB) &&
	    !(sc->sc_quirks & NO_GETMAXLUN))
		sc->sc_maxlun = umass_bbb_get_max_lun(sc);
	else
		sc->sc_maxlun = 0;

	/* Prepare the SCSI command block */
	sc->cam_scsi_sense.opcode = REQUEST_SENSE;
	sc->cam_scsi_test_unit_ready.opcode = TEST_UNIT_READY;

#define	SOFT_CACHE_SIZE 0x40
	sc->data_ccb = (union ccb *)malloc(sizeof(union ccb));
	if (sc->data_ccb == NULL)
		goto detach;
	sc->data_ccb->csio.data_ptr = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(SOFT_CACHE_SIZE));
	if (sc->data_ccb->csio.data_ptr == NULL)
		goto detach;
	sc->data_ccb->csio.dxfer_len = SOFT_CACHE_SIZE;

	DPRINTF_UMASS(sc, UDMASS_GEN, "Attach finished\n");

	/* register the device*/
	if (umass_attach_dev(sc, device_get_unit(dev))) {
		goto detach;
	}

	p_umsf = sc;
	return (0);			/* success */

detach:
	(void)umass_detach(dev);
	return (ENXIO);			/* failure */
}

static int
umass_detach(device_t dev)
{
	struct umass_softc *sc = (struct umass_softc *)device_get_softc(dev);
	unsigned int dev_unit = device_get_unit(dev);

	DPRINTF_UMASS(sc, UDMASS_USB, "\n");

	sc->sc_detach_status = TRUE;

	/* teardown our statemachine */
	usbd_transfer_unsetup(sc->sc_xfer, UMASS_T_MAX);

	mtx_lock(&sc->sc_mtx);

	/* cancel any leftover CCB's */
	umass_cancel_ccb(sc);

	mtx_lock(&sc->sc_umass_mtx);
	if (sc->data_ccb != NULL) {
		if (sc->data_ccb->csio.data_ptr != NULL) {
			free((void*)sc->data_ccb->csio.data_ptr);
			sc->data_ccb->csio.data_ptr = NULL;
		}
		free(sc->data_ccb);
		sc->data_ccb = NULL;
	}
	mtx_unlock(&sc->sc_umass_mtx);

	umass_detach_dev_sub(sc, dev_unit, 0);
#if USB_SUPPORT_SD_HOT_PLUG
	umass_task_check(1);
#endif

	mtx_unlock(&sc->sc_mtx);
	sc->sc_detach_status = FALSE;
	mtx_destroy(&sc->sc_mtx);
	mtx_destroy(&sc->sc_umass_mtx);

	p_umsf = NULL;
	return (0);			/* success */
}

static void
umass_init_shuttle(struct umass_softc *sc)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t status[2] = {0, 0};

	/*
	 * The Linux driver does this, but no one can tell us what the
	 * command does.
	 */
	req.bmRequestType = UT_READ_VENDOR_DEVICE;
	req.bRequest = 1;	/* XXX unknown command */
	USETW(req.wValue, 0);
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, sizeof(status));
	err = usbd_do_request(sc->sc_udev, NULL, &req, &status);
	if (err)
		DPRINTF_UMASS(sc, UDMASS_GEN, "request failed in %s %d, err=%d\n",
	    __FUNCTION__, __LINE__, err);

	DPRINTF_UMASS(sc, UDMASS_GEN, "Shuttle init returned 0x%02x%02x\n",
	    status[0], status[1]);
}

/*
 * Generic functions to handle transfers
 */

static void
umass_transfer_start(struct umass_softc *sc, uint8_t xfer_index)
{
	DPRINTF_UMASS(sc, UDMASS_GEN, "transfer index = "
	    "%d\n", xfer_index);

	if (sc->sc_xfer[xfer_index]) {
		sc->sc_last_xfer_index = xfer_index;
		usbd_transfer_start(sc->sc_xfer[xfer_index]);
	} else {
		umass_cancel_ccb(sc);
	}
}

static void
umass_cancel_ccb(struct umass_softc *sc)
{
	union ccb *umass_ccb;

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	umass_ccb = sc->sc_transfer.ccb;
	sc->sc_transfer.ccb = NULL;
	sc->sc_last_xfer_index = 0;

	if (umass_ccb != NULL) {
		(sc->sc_transfer.callback)
		    (sc, umass_ccb, (sc->sc_transfer.data_len -
		    sc->sc_transfer.actlen), STATUS_WIRE_FAILED);
	}
}

static void
umass_tr_error(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);

	if (error != USB_ERR_CANCELLED) {

		DPRINTF_UMASS(sc, UDMASS_GEN, "transfer error, %s -> "
		    "reset\n", usbd_errstr(error));
	}
	umass_cancel_ccb(sc);
}

/*
 *return 0: find the corresponding LUN;
 *		 1: find the SBC Direct-access;
 *		 -1: did not find the LUN.
 */
static int
umass_scsi_inquiry_data(struct umass_softc *sc, void *data, int len)
{
	struct scsiresp_inquiry_s *cur_i;
	uint8_t pdt;
	uint8_t rmb;
	int is_dir;
	char *name;

	if (len != SCSIRESP_INQUIRY_SIZEOF)
		return (-1);

	is_dir = 0;
	cur_i = (struct scsiresp_inquiry_s *)data;

	pdt = SCSI_GET_INQUIRY_PDT(cur_i->qualtype);
	rmb = SCSI_GET_INQUIRY_RMB(cur_i->flags1);
	switch (pdt) {
	case T_DIRECT:
		name = "SBC Direct-access";
		is_dir = 1;
		break;
	case T_CDROM:
		name = "CD-ROM";
		break;
	case T_OPTICAL:
		name = "Optical memory";
		break;
	case T_RBC:
		name = "RBC Direct-access";
		break;
	default:
		name = "PDT out of scope";
		break;
	}
	DPRINTF_UMASS(sc, UDMASS_BBB, "SCSI: LUN-%d %s %s\n", sc->sc_transfer.lun, name,
		    (rmb ? "Removable" : "Not Removable"));

	(void)name;
	(void)rmb; /* this is for clearing warning */
	return (is_dir);
}

/*
 * BBB protocol specific functions
 */

static void
umass_t_bbb_reset1_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	struct usb_device_request req;
	struct usb_page_cache *pc;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		umass_transfer_start(sc, UMASS_T_BBB_RESET2);
		return;

	case USB_ST_SETUP:
		/*
		 * Reset recovery (5.3.4 in Universal Serial Bus Mass Storage Class)
		 *
		 * For Reset Recovery the host shall issue in the following order:
		 * a) a Bulk-Only Mass Storage Reset
		 * b) a Clear Feature HALT to the Bulk-In endpoint
		 * c) a Clear Feature HALT to the Bulk-Out endpoint
		 *
		 * This is done in 3 steps, using 3 transfers:
		 * UMASS_T_BBB_RESET1
		 * UMASS_T_BBB_RESET2
		 * UMASS_T_BBB_RESET3
		 */

		DPRINTF_UMASS(sc, UDMASS_BBB, "BBB reset!\n");

		req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
		req.bRequest = UR_BBB_RESET;	/* bulk only reset */
		USETW(req.wValue, 0);
		req.wIndex[0] = sc->sc_iface_no;
		req.wIndex[1] = 0;
		USETW(req.wLength, 0);

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_in(pc, 0, &req, sizeof(req));

		usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
		usbd_xfer_set_frames(xfer, 1);
		usbd_transfer_submit(xfer);
		return;

	default:			/* Error */
		umass_tr_error(xfer, error);
		return;
	}
}

static void
umass_t_bbb_reset2_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_bbb_data_clear_stall_callback(xfer, UMASS_T_BBB_RESET3,
	    UMASS_T_BBB_DATA_READ, error);
}

static void
umass_t_bbb_reset3_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_bbb_data_clear_stall_callback(xfer, UMASS_T_BBB_COMMAND,
	    UMASS_T_BBB_DATA_WRITE, error);
}

static void
umass_t_bbb_data_clear_stall_callback(struct usb_xfer *xfer,
	uint8_t next_xfer, uint8_t stall_xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
tr_transferred:
		umass_transfer_start(sc, next_xfer);
		return;

	case USB_ST_SETUP:
		if (usbd_clear_stall_callback(xfer, sc->sc_xfer[stall_xfer])) {
			goto tr_transferred;
		}
		return;

	default:			/* Error */
		umass_tr_error(xfer, error);
		return;
	}
}

static void
umass_t_bbb_command_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint32_t tag;
	int ret;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		umass_transfer_start
		    (sc, ((sc->sc_transfer.dir == DIR_IN) ? UMASS_T_BBB_DATA_READ :
		    (sc->sc_transfer.dir == DIR_OUT) ? UMASS_T_BBB_DATA_WRITE :
		    UMASS_T_BBB_STATUS));
		return;

	case USB_ST_SETUP:

		sc->sc_status_try = 0;

		/*
		 * the initial value is not important,
		 * as long as the values are unique:
		 */
		tag = UGETDW(sc->cbw.dCBWTag) + 1;

		USETDW(sc->cbw.dCBWSignature, CBWSIGNATURE);
		USETDW(sc->cbw.dCBWTag, tag);

		/*
		* dCBWDataTransferLength:
		*   This field indicates the number of bytes of data that the host
		*   intends to transfer on the IN or OUT Bulk endpoint(as indicated by
		*   the Direction bit) during the execution of this command. If this
		*   field is set to 0, the device will expect that no data will be
		*   transferred IN or OUT during this command, regardless of the value
		*   of the Direction bit defined in dCBWFlags.
		*/
		USETDW(sc->cbw.dCBWDataTransferLength, sc->sc_transfer.data_len);

		/*
		* dCBWFlags:
		* The bits of the Flags field are defined as follows:
		*	 Bits 0-6  reserved
		*	 Bit  7	Direction - this bit shall be ignored if the
		*						dCBWDataTransferLength field is zero.
		*				0 = data Out from host to device
		*				1 = data In from device to host
		*/
		sc->cbw.bCBWFlags = ((sc->sc_transfer.dir == DIR_IN) ?
		    CBWFLAGS_IN : CBWFLAGS_OUT);
		sc->cbw.bCBWLUN = sc->sc_transfer.lun;

		if (sc->sc_transfer.cmd_len > sizeof(sc->cbw.CBWCDB)) {
			sc->sc_transfer.cmd_len = sizeof(sc->cbw.CBWCDB);
			DPRINTF_UMASS(sc, UDMASS_BBB, "Truncating long command!\n");
		}
		sc->cbw.bCDBLength = sc->sc_transfer.cmd_len;

		/* copy SCSI command data */
		ret = memcpy_s(sc->cbw.CBWCDB, CBWCDBLENGTH,
			sc->sc_transfer.cmd_data, sc->sc_transfer.cmd_len);
		if (ret != EOK) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "memcpy_s fail, %d\n", ret);
			return;
		}

		/* clear remaining command area */
		(void)memset_s(sc->cbw.CBWCDB + sc->sc_transfer.cmd_len,
		    sizeof(sc->cbw.CBWCDB) - sc->sc_transfer.cmd_len, 0,
		    sizeof(sc->cbw.CBWCDB) - sc->sc_transfer.cmd_len);

		DIF(UDMASS_BBB,  umass_bbb_dump_cbw(sc, &sc->cbw));

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_in(pc, 0, &sc->cbw, sizeof(sc->cbw));
		usbd_xfer_set_frame_len(xfer, 0, sizeof(sc->cbw));

		usbd_transfer_submit(xfer);

		return;

	default:			/* Error */
		umass_tr_error(xfer, error);
		return;
	}
}

static void
umass_t_bbb_data_callback(struct usb_xfer *xfer, usb_error_t error,
	uint8_t xfer_index)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	uint32_t max_bulk = usbd_xfer_max_len(xfer);
	int actlen, sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		sc->sc_transfer.data_rem -= actlen;
		sc->sc_transfer.data_ptr += actlen;
		sc->sc_transfer.actlen += actlen;

		if (actlen < sumlen) {
			/* short transfer */
			sc->sc_transfer.data_rem = 0;
		}
	case USB_ST_SETUP:
		DPRINTF_UMASS(sc, UDMASS_BBB, "max_bulk=%u, data_rem=%u\n",
		    max_bulk, sc->sc_transfer.data_rem);

		if (sc->sc_transfer.data_rem == 0) {
			umass_transfer_start(sc, UMASS_T_BBB_STATUS);
			return;
		}
		if (max_bulk > sc->sc_transfer.data_rem) {
			max_bulk = sc->sc_transfer.data_rem;
		}
		usbd_xfer_set_timeout(xfer, sc->sc_transfer.data_timeout);

		usbd_xfer_set_frame_data(xfer, 0, sc->sc_transfer.data_ptr,
		    max_bulk);

		usbd_transfer_submit(xfer);
		return;

	default:			/* Error */
		if (error == USB_ERR_CANCELLED) {
			umass_tr_error(xfer, error);
		} else {
			umass_transfer_start(sc, xfer_index);
		}
		return;
	}
}

static void
umass_t_bbb_data_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_bbb_data_callback(xfer, error, UMASS_T_BBB_DATA_RD_CS);
}

static void
umass_t_bbb_data_rd_cs_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_bbb_data_clear_stall_callback(xfer, UMASS_T_BBB_STATUS,
	    UMASS_T_BBB_DATA_READ, error);
}

static void
umass_t_bbb_data_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_bbb_data_callback(xfer, error, UMASS_T_BBB_DATA_WR_CS);
}

static void
umass_t_bbb_data_wr_cs_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_bbb_data_clear_stall_callback(xfer, UMASS_T_BBB_STATUS,
	    UMASS_T_BBB_DATA_WRITE, error);
}

static void
umass_t_bbb_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	union ccb *umass_ccb = sc->sc_transfer.ccb;
	struct usb_page_cache *pc;
	uint32_t residue;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		/*
		 * Do a full reset if there is something wrong with the CSW:
		 */
		sc->sc_status_try = 1;

		/* Zero missing parts of the CSW: */

		if (actlen < (int)sizeof(sc->csw)) {
			(void)memset_s(&sc->csw, sizeof(sc->csw), 0, sizeof(sc->csw));
		}

		pc = usbd_xfer_get_frame(xfer, 0);

		usbd_copy_out(pc, 0, &sc->csw, actlen);

		DIF(UDMASS_BBB, umass_bbb_dump_csw(sc, &sc->csw));

		residue = UGETDW(sc->csw.dCSWDataResidue);

		if ((!residue) || (sc->sc_quirks & IGNORE_RESIDUE)) {
			residue = (sc->sc_transfer.data_len -
			    sc->sc_transfer.actlen);
		}
		if (residue > sc->sc_transfer.data_len) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "truncating residue from %d "
			    "to %d bytes\n", residue, sc->sc_transfer.data_len);
			residue = sc->sc_transfer.data_len;
		}
		/* translate weird command-status signatures: */
		if (sc->sc_quirks & WRONG_CSWSIG) {

			uint32_t temp = UGETDW(sc->csw.dCSWSignature);

			if ((temp == CSWSIGNATURE_OLYMPUS_C1) ||
			    (temp == CSWSIGNATURE_IMAGINATION_DBX1)) {
				USETDW(sc->csw.dCSWSignature, CSWSIGNATURE);
			}
		}
		/* check CSW and handle eventual error */
		if (UGETDW(sc->csw.dCSWSignature) != CSWSIGNATURE) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "bad CSW signature 0x%08x != 0x%08x\n",
			    UGETDW(sc->csw.dCSWSignature), CSWSIGNATURE);
			/*
			 * Invalid CSW: Wrong signature or wrong tag might
			 * indicate that we lost synchronization. Reset the
			 * device.
			 */
			goto tr_error;
		} else if (UGETDW(sc->csw.dCSWTag) != UGETDW(sc->cbw.dCBWTag)) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "Invalid CSW: tag 0x%08x should be "
			    "0x%08x\n", UGETDW(sc->csw.dCSWTag),
			    UGETDW(sc->cbw.dCBWTag));
			goto tr_error;
		} else if (sc->csw.bCSWStatus > CSWSTATUS_PHASE) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "Invalid CSW: status %d > %d\n",
			    sc->csw.bCSWStatus, CSWSTATUS_PHASE);
			goto tr_error;
		} else if (sc->csw.bCSWStatus == CSWSTATUS_PHASE) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "Phase error, residue = "
			    "%d\n", residue);
			goto tr_error;
		} else if (sc->sc_transfer.actlen > sc->sc_transfer.data_len) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "Buffer overrun %d > %d\n",
			    sc->sc_transfer.actlen, sc->sc_transfer.data_len);
			goto tr_error;
		} else if (sc->csw.bCSWStatus == CSWSTATUS_FAILED) {
			DPRINTF_UMASS(sc, UDMASS_BBB, "Command failed, residue = "
			    "%d\n", residue);

			sc->sc_transfer.ccb = NULL;

			sc->sc_last_xfer_index = UMASS_T_BBB_COMMAND;

			(sc->sc_transfer.callback)
			    (sc, umass_ccb, residue, STATUS_CMD_FAILED);
		} else {
			sc->sc_transfer.ccb = NULL;

			sc->sc_last_xfer_index = UMASS_T_BBB_COMMAND;

			(sc->sc_transfer.callback)
			    (sc, umass_ccb, residue, STATUS_CMD_OK);
		}
		return;

	case USB_ST_SETUP:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		return;

	default:
tr_error:
		DPRINTF_UMASS(sc, UDMASS_BBB, "Failed to read CSW: %s, try %d\n",
		    usbd_errstr(error), sc->sc_status_try);

		if ((error == USB_ERR_CANCELLED) ||
		    (sc->sc_status_try)) {
			umass_tr_error(xfer, error);
		} else {
			sc->sc_status_try = 1;
			umass_transfer_start(sc, UMASS_T_BBB_DATA_RD_CS);
		}
		return;
	}
}

static int
umass_command_start(struct umass_softc *sc, uint8_t dir,
    void *data_ptr, uint32_t data_len,
    uint32_t data_timeout, umass_callback_t *callback,
    union ccb *umass_ccb)
{
	if (sc->sc_detach_status)
	{
		PRINT_WARN("[%s][%d] usb is detaching\n",__FUNCTION__,__LINE__);
		return (-1);
	}

	/*
	 * NOTE: assumes that "sc->sc_transfer.cmd_data" and
	 * "sc->sc_transfer.cmd_len" has been properly
	 * initialized.
	 */

	sc->sc_transfer.dir = data_len ? dir : DIR_NONE;
	sc->sc_transfer.data_ptr = (uint8_t *)data_ptr;
	sc->sc_transfer.data_len = data_len;
	sc->sc_transfer.data_rem = data_len;
	sc->sc_transfer.data_timeout = (data_timeout + UMASS_TIMEOUT);

	sc->sc_transfer.actlen = 0;
	sc->sc_transfer.callback = callback;
	sc->sc_transfer.ccb = umass_ccb;

	if (sc->sc_xfer[sc->sc_last_xfer_index]) {
		usbd_transfer_start(sc->sc_xfer[sc->sc_last_xfer_index]);
	} else {
		umass_cancel_ccb(sc);
	}

	(void)LOS_EventRead(&sc->sc_event, 0xFF,
	    LOS_WAITMODE_OR|LOS_WAITMODE_CLR, 1000);

	return (0);
}

static uint8_t
umass_bbb_get_max_lun(struct umass_softc *sc)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t buf = 0;

	/* The Get Max Lun command is a class-specific request. */
	req.bmRequestType = UT_READ_CLASS_INTERFACE;
	req.bRequest = UR_BBB_GET_MAX_LUN;
	USETW(req.wValue, 0);
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, 1);

	err = usbd_do_request(sc->sc_udev, NULL, &req, &buf);
	if (err) {
		buf = 0;

		/* Device doesn't support Get Max Lun request. */
		PRINTK("%s: Get Max Lun not supported (%s)\n",
		    sc->sc_name, usbd_errstr(err));
	}
	return (buf);
}

/*
 * Command/Bulk/Interrupt (CBI) specific functions
 */

static void
umass_cbi_start_status(struct umass_softc *sc)
{
	if (sc->sc_xfer[UMASS_T_CBI_STATUS]) {
		umass_transfer_start(sc, UMASS_T_CBI_STATUS);
	} else {
		union ccb *umass_ccb = sc->sc_transfer.ccb;

		sc->sc_transfer.ccb = NULL;

		sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

		(sc->sc_transfer.callback)
		    (sc, umass_ccb, (sc->sc_transfer.data_len -
		    sc->sc_transfer.actlen), STATUS_CMD_UNKNOWN);
	}
}

static void
umass_t_cbi_reset1_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	struct usb_device_request req;
	struct usb_page_cache *pc;
	uint8_t buf[UMASS_CBI_DIAGNOSTIC_CMDLEN];

	uint8_t i;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		umass_transfer_start(sc, UMASS_T_CBI_RESET2);
		break;

	case USB_ST_SETUP:
		/*
		 * Command Block Reset Protocol
		 *
		 * First send a reset request to the device. Then clear
		 * any possibly stalled bulk endpoints.
		 *
		 * This is done in 3 steps, using 3 transfers:
		 * UMASS_T_CBI_RESET1
		 * UMASS_T_CBI_RESET2
		 * UMASS_T_CBI_RESET3
		 * UMASS_T_CBI_RESET4 (only if there is an interrupt endpoint)
		 */

		DPRINTF_UMASS(sc, UDMASS_CBI, "CBI reset!\n");

		req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
		req.bRequest = UR_CBI_ADSC;
		USETW(req.wValue, 0);
		req.wIndex[0] = sc->sc_iface_no;
		req.wIndex[1] = 0;
		USETW(req.wLength, UMASS_CBI_DIAGNOSTIC_CMDLEN);

		/*
		 * The 0x1d code is the SEND DIAGNOSTIC command. To
		 * distinguish between the two, the last 10 bytes of the CBL
		 * is filled with 0xff (section 2.2 of the CBI
		 * specification)
		 */
		buf[0] = 0x1d;		/* Command Block Reset */
		buf[1] = 0x04;

		for (i = 2; i < UMASS_CBI_DIAGNOSTIC_CMDLEN; i++) {
			buf[i] = 0xff;
		}

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_in(pc, 0, &req, sizeof(req));
		pc = usbd_xfer_get_frame(xfer, 1);
		usbd_copy_in(pc, 0, buf, sizeof(buf));

		usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
		usbd_xfer_set_frame_len(xfer, 1, sizeof(buf));
		usbd_xfer_set_frames(xfer, 2);
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if (error == USB_ERR_CANCELLED)
			umass_tr_error(xfer, error);
		else
			umass_transfer_start(sc, UMASS_T_CBI_RESET2);
		break;
	}
}

static void
umass_t_cbi_reset2_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_cbi_data_clear_stall_callback(xfer, UMASS_T_CBI_RESET3,
	    UMASS_T_CBI_DATA_READ, error);
}

static void
umass_t_cbi_reset3_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);

	umass_t_cbi_data_clear_stall_callback
	    (xfer, (sc->sc_xfer[UMASS_T_CBI_RESET4] &&
	    sc->sc_xfer[UMASS_T_CBI_STATUS]) ?
	    UMASS_T_CBI_RESET4 : UMASS_T_CBI_COMMAND,
	    UMASS_T_CBI_DATA_WRITE, error);
}

static void
umass_t_cbi_reset4_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_cbi_data_clear_stall_callback(xfer, UMASS_T_CBI_COMMAND,
	    UMASS_T_CBI_STATUS, error);
}

static void
umass_t_cbi_data_clear_stall_callback(struct usb_xfer *xfer,
    uint8_t next_xfer, uint8_t stall_xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
tr_transferred:
		if (next_xfer == UMASS_T_CBI_STATUS) {
			umass_cbi_start_status(sc);
		} else {
			umass_transfer_start(sc, next_xfer);
		}
		break;

	case USB_ST_SETUP:
		if (usbd_clear_stall_callback(xfer, sc->sc_xfer[stall_xfer])) {
			goto tr_transferred;	/* should not happen */
		}
		break;

	default:			/* Error */
		umass_tr_error(xfer, error);
		break;
	}
}

static void
umass_t_cbi_command_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	union ccb *umass_ccb = sc->sc_transfer.ccb;
	struct usb_device_request req;
	struct usb_page_cache *pc;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		if (sc->sc_transfer.dir == DIR_NONE) {
			umass_cbi_start_status(sc);
		} else {
			umass_transfer_start
			    (sc, (sc->sc_transfer.dir == DIR_IN) ?
			    UMASS_T_CBI_DATA_READ : UMASS_T_CBI_DATA_WRITE);
		}
		break;

	case USB_ST_SETUP:

		if (umass_ccb) {

			/*
				 * do a CBI transfer with cmd_len bytes from
				 * cmd_data, possibly a data phase of data_len
				 * bytes from/to the device and finally a status
				 * read phase.
				 */

			req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
			req.bRequest = UR_CBI_ADSC;
			USETW(req.wValue, 0);
			req.wIndex[0] = sc->sc_iface_no;
			req.wIndex[1] = 0;
			req.wLength[0] = sc->sc_transfer.cmd_len;
			req.wLength[1] = 0;

			pc = usbd_xfer_get_frame(xfer, 0);
			usbd_copy_in(pc, 0, &req, sizeof(req));
			pc = usbd_xfer_get_frame(xfer, 1);
			usbd_copy_in(pc, 0, sc->sc_transfer.cmd_data,
			    sc->sc_transfer.cmd_len);

			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			usbd_xfer_set_frame_len(xfer, 1, sc->sc_transfer.cmd_len);
			usbd_xfer_set_frames(xfer,
			    sc->sc_transfer.cmd_len ? 2 : 1);

			DIF(UDMASS_CBI,
			    umass_cbi_dump_cmd(sc,
			    sc->sc_transfer.cmd_data,
			    sc->sc_transfer.cmd_len));

			usbd_transfer_submit(xfer);
		}
		break;

	default:			/* Error */
		/*
		 * STALL on the control pipe can be result of the command error.
		 * Attempt to clear this STALL same as for bulk pipe also
		 * results in command completion interrupt, but ASC/ASCQ there
		 * look like not always valid, so don't bother about it.
		 */
		if ((error == USB_ERR_STALLED) ||
		    (sc->sc_transfer.callback == &umass_cam_cb)) {
			sc->sc_transfer.ccb = NULL;
			(sc->sc_transfer.callback)
			    (sc, umass_ccb, sc->sc_transfer.data_len,
			    STATUS_CMD_UNKNOWN);
		} else {
			umass_tr_error(xfer, error);
			/* skip reset */
			sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;
		}
		break;
	}
}

static void
umass_t_cbi_data_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	uint32_t max_bulk = usbd_xfer_max_len(xfer);
	int actlen, sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		sc->sc_transfer.data_rem -= actlen;
		sc->sc_transfer.data_ptr += actlen;
		sc->sc_transfer.actlen += actlen;

		if (actlen < sumlen) {
			/* short transfer */
			sc->sc_transfer.data_rem = 0;
		}
	case USB_ST_SETUP:
		DPRINTF_UMASS(sc, UDMASS_CBI, "max_bulk=%d, data_rem=%d\n",
		    max_bulk, sc->sc_transfer.data_rem);

		if (sc->sc_transfer.data_rem == 0) {
			umass_cbi_start_status(sc);
			break;
		}
		if (max_bulk > sc->sc_transfer.data_rem) {
			max_bulk = sc->sc_transfer.data_rem;
		}
		usbd_xfer_set_timeout(xfer, sc->sc_transfer.data_timeout);

		usbd_xfer_set_frame_data(xfer, 0, sc->sc_transfer.data_ptr,
		    max_bulk);

		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if ((error == USB_ERR_CANCELLED) ||
		    (sc->sc_transfer.callback != &umass_cam_cb)) {
			umass_tr_error(xfer, error);
		} else {
			umass_transfer_start(sc, UMASS_T_CBI_DATA_RD_CS);
		}
		break;
	}
}

static void
umass_t_cbi_data_rd_cs_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_cbi_data_clear_stall_callback(xfer, UMASS_T_CBI_STATUS,
	    UMASS_T_CBI_DATA_READ, error);
}

static void
umass_t_cbi_data_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	uint32_t max_bulk = usbd_xfer_max_len(xfer);
	int actlen, sumlen;

	usbd_xfer_status(xfer, &actlen, &sumlen, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		sc->sc_transfer.data_rem -= actlen;
		sc->sc_transfer.data_ptr += actlen;
		sc->sc_transfer.actlen += actlen;

		if (actlen < sumlen) {
			/* short transfer */
			sc->sc_transfer.data_rem = 0;
		}
	case USB_ST_SETUP:
		DPRINTF_UMASS(sc, UDMASS_CBI, "max_bulk=%d, data_rem=%d\n",
		    max_bulk, sc->sc_transfer.data_rem);

		if (sc->sc_transfer.data_rem == 0) {
			umass_cbi_start_status(sc);
			break;
		}
		if (max_bulk > sc->sc_transfer.data_rem) {
			max_bulk = sc->sc_transfer.data_rem;
		}
		usbd_xfer_set_timeout(xfer, sc->sc_transfer.data_timeout);

		usbd_xfer_set_frame_data(xfer, 0, sc->sc_transfer.data_ptr,
		    max_bulk);

		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		if ((error == USB_ERR_CANCELLED) ||
		    (sc->sc_transfer.callback != &umass_cam_cb)) {
			umass_tr_error(xfer, error);
		} else {
			umass_transfer_start(sc, UMASS_T_CBI_DATA_WR_CS);
		}
		break;
	}
}

static void
umass_t_cbi_data_wr_cs_callback(struct usb_xfer *xfer, usb_error_t error)
{
	umass_t_cbi_data_clear_stall_callback(xfer, UMASS_T_CBI_STATUS,
	    UMASS_T_CBI_DATA_WRITE, error);
}

static void
umass_t_cbi_status_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umass_softc *sc = (struct umass_softc *)usbd_xfer_softc(xfer);
	union ccb *umass_ccb = sc->sc_transfer.ccb;
	struct usb_page_cache *pc;
	uint32_t residue;
	uint8_t status;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		if (actlen < (int)sizeof(sc->sbl)) {
			goto tr_setup;
		}
		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, &sc->sbl, sizeof(sc->sbl));

		residue = (sc->sc_transfer.data_len -
		    sc->sc_transfer.actlen);

		/* dissect the information in the buffer */

		if (sc->sc_proto & UMASS_PROTO_UFI) {

			/*
			 * Section 3.4.3.1.3 specifies that the UFI command
			 * protocol returns an ASC and ASCQ in the interrupt
			 * data block.
			 */

			DPRINTF_UMASS(sc, UDMASS_CBI, "UFI CCI, ASC = 0x%02x, "
			    "ASCQ = 0x%02x\n", sc->sbl.ufi.asc,
			    sc->sbl.ufi.ascq);

			status = (((sc->sbl.ufi.asc == 0) &&
			    (sc->sbl.ufi.ascq == 0)) ?
			    STATUS_CMD_OK : STATUS_CMD_FAILED);

			sc->sc_transfer.ccb = NULL;

			sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

			(sc->sc_transfer.callback)
			    (sc, umass_ccb, residue, status);

			break;

		} else {

			/* Command Interrupt Data Block */

			DPRINTF_UMASS(sc, UDMASS_CBI, "type=0x%02x, value=0x%02x\n",
			    sc->sbl.common.type, sc->sbl.common.value);

			if (sc->sbl.common.type == IDB_TYPE_CCI) {

				status = (sc->sbl.common.value & IDB_VALUE_STATUS_MASK);

				status = ((status == IDB_VALUE_PASS) ? STATUS_CMD_OK :
				    (status == IDB_VALUE_FAIL) ? STATUS_CMD_FAILED :
				    (status == IDB_VALUE_PERSISTENT) ? STATUS_CMD_FAILED :
				    STATUS_WIRE_FAILED);

				sc->sc_transfer.ccb = NULL;

				sc->sc_last_xfer_index = UMASS_T_CBI_COMMAND;

				(sc->sc_transfer.callback)
				    (sc, umass_ccb, residue, status);

				break;
			}
		}

		/* fallthrough */

	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:			/* Error */
		DPRINTF_UMASS(sc, UDMASS_CBI, "Failed to read CSW: %s\n",
		    usbd_errstr(error));
		umass_tr_error(xfer, error);
		break;
	}
}

/* umass_cam_cb
 *	finalise a completed CAM command
 */

static void
umass_cam_cb(struct umass_softc *sc, union ccb *umass_ccb, uint32_t residue,
	uint8_t status)
{
	umass_ccb->csio.resid = residue;
	umass_ccb->csio.status = status;

	switch (status) {
	case STATUS_CMD_OK:
		(void)LOS_EventWrite(&sc->sc_event, 0x01);
		break;

	case STATUS_CMD_UNKNOWN:
	case STATUS_CMD_FAILED:
		/* fetch sense data */
		(void)LOS_EventWrite(&sc->sc_event, 0x02);
		break;

	default:
		(void)LOS_EventWrite(&sc->sc_event, 0x04);
		break;
	}
}

/*
 * SCSI specific functions
 */

static uint8_t
umass_scsi_transform(struct umass_softc *sc, uint8_t *cmd_ptr,
	uint8_t cmd_len)
{
	int ret;

	if ((cmd_len == 0) ||
		(cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	sc->sc_transfer.cmd_len = cmd_len;

	switch (cmd_ptr[0]) {
	case TEST_UNIT_READY:
		if (sc->sc_quirks & NO_TEST_UNIT_READY) {
			DPRINTF_UMASS(sc, UDMASS_SCSI, "Converted TEST_UNIT_READY "
			    "to START_UNIT\n");
			ret = memset_s(sc->sc_transfer.cmd_data, sizeof(sc->sc_transfer.cmd_data), 0, cmd_len);
			if (ret != EOK) {
				usb_err("memset_s failed!, ret:%d\n", ret);
				return (0);
			}
			sc->sc_transfer.cmd_data[0] = START_STOP_UNIT;
			sc->sc_transfer.cmd_data[4] = SSS_START;
			return (1);
		}
		break;

	case INQUIRY:
		/*
		 * some drives wedge when asked for full inquiry
		 * information.
		 */
		if (sc->sc_quirks & FORCE_SHORT_INQUIRY) {
			ret = memcpy_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, cmd_ptr, cmd_len);
			if (ret != EOK) {
				usb_err("memcpy_s failed!, ret:%d\n", ret);
				return (0);
			}
			sc->sc_transfer.cmd_data[4] = SHORT_INQUIRY_LENGTH;
			return (1);
		}
		break;
	}

	ret = memcpy_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, cmd_ptr, cmd_len);
	if (ret != EOK) {
		usb_err("memcpy_s failed!, ret:%d\n", ret);
		return (0);
	}

	return (1);
}

static uint8_t
umass_rbc_transform(struct umass_softc *sc, uint8_t *cmd_ptr, uint8_t cmd_len)
{
	int ret;

	if ((cmd_len == 0) ||
		(cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	switch (cmd_ptr[0]) {
	/* these commands are defined in RBC: */
	case READ_10:
	case READ_CAPACITY:
	case START_STOP_UNIT:
	case SYNCHRONIZE_CACHE:
	case WRITE_10:
	case 0x2f:			/* VERIFY_10 is absent from * scsi_all.h??? */
	case INQUIRY:
	case MODE_SELECT_10:
	case MODE_SENSE_10:
	case TEST_UNIT_READY:
	case WRITE_BUFFER:
		/*
		 * The following commands are not listed in my copy of the
		 * RBC specs. CAM however seems to want those, and at least
		 * the Sony DSC device appears to support those as well
		 */
	case REQUEST_SENSE:
	case PREVENT_ALLOW:

		ret = memcpy_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, cmd_ptr, cmd_len);
		if (ret != EOK) {
			usb_err("memcpy_s failed!, ret:%d\n", ret);
			return (0);
		}

		if ((sc->sc_quirks & RBC_PAD_TO_12) && (cmd_len < 12)) {
			ret = memset_s(sc->sc_transfer.cmd_data + cmd_len,
			    (size_t)(UMASS_MAX_CMDLEN - cmd_len), 0, (size_t)(12 - cmd_len));
			if (ret != EOK){
				usb_err("memset_s failed!, ret:%d\n", ret);
				return (0);
			}
			cmd_len = 12;
		}
		sc->sc_transfer.cmd_len = cmd_len;
		return (1);		/* sucess */

		/* All other commands are not legal in RBC */
	default:
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Unsupported RBC "
		    "command 0x%02x\n", cmd_ptr[0]);
		return (0);		/* failure */
	}
}

static uint8_t
umass_ufi_transform(struct umass_softc *sc, uint8_t *cmd_ptr,
    uint8_t cmd_len)
{
	int ret;

	if ((cmd_len == 0) ||
		(cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	/* An UFI command is always 12 bytes in length */
	sc->sc_transfer.cmd_len = UFI_COMMAND_LENGTH;

	/* Zero the command data */
	ret = memset_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, 0, UFI_COMMAND_LENGTH);
	if (ret != EOK) {
		usb_err("memset_s failed!, ret:%d\n", ret);
		return (0);
	}

	switch (cmd_ptr[0]) {
		/*
		 * Commands of which the format has been verified. They
		 * should work. Copy the command into the (zeroed out)
		 * destination buffer.
		 */
	case TEST_UNIT_READY:
		if (sc->sc_quirks & NO_TEST_UNIT_READY) {
			/*
			 * Some devices do not support this command. Start
			 * Stop Unit should give the same results
			 */
			DPRINTF_UMASS(sc, UDMASS_UFI, "Converted TEST_UNIT_READY "
			    "to START_UNIT\n");

			sc->sc_transfer.cmd_data[0] = START_STOP_UNIT;
			sc->sc_transfer.cmd_data[4] = SSS_START;
			return (1);
		}
		break;

	case REZERO_UNIT:
	case REQUEST_SENSE:
	case FORMAT_UNIT:
	case INQUIRY:
	case START_STOP_UNIT:
	case SEND_DIAGNOSTIC:
	case PREVENT_ALLOW:
	case READ_CAPACITY:
	case READ_10:
	case WRITE_10:
	case POSITION_TO_ELEMENT:	/* SEEK_10 */
	case WRITE_AND_VERIFY:
	case VERIFIED:
	case MODE_SELECT_10:
	case MODE_SENSE_10:
	case READ_12:
	case WRITE_12:
	case READ_FORMAT_CAPACITIES:
		break;

		/*
		 * SYNCHRONIZE_CACHE isn't supported by UFI, nor should it be
		 * required for UFI devices, so it is appropriate to fake
		 * success.
		 */
	case SYNCHRONIZE_CACHE:
		return (2);

	default:
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Unsupported UFI "
		    "command 0x%02x\n", cmd_ptr[0]);
		return (0);		/* failure */
	}

	ret = memcpy_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, cmd_ptr, cmd_len);
	if (ret != EOK) {
		usb_err("memcpy_s failed!, ret:%d\n", ret);
		return (0);
	}

	return (1);			/* success */
}

/*
 * 8070i (ATAPI) specific functions
 */
static uint8_t
umass_atapi_transform(struct umass_softc *sc, uint8_t *cmd_ptr,
    uint8_t cmd_len)
{
	int ret;

	if ((cmd_len == 0) ||
		(cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	/* An ATAPI command is always 12 bytes in length. */
	sc->sc_transfer.cmd_len = ATAPI_COMMAND_LENGTH;

	/* Zero the command data */
	ret = memset_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, 0, ATAPI_COMMAND_LENGTH);
	if (ret != EOK) {
		usb_err("memset_s failed!, ret:%d\n", ret);
		return (0);
	}

	switch (cmd_ptr[0]) {
		/*
		 * Commands of which the format has been verified. They
		 * should work. Copy the command into the destination
		 * buffer.
		 */
	case INQUIRY:
		/*
		 * some drives wedge when asked for full inquiry
		 * information.
		 */
		if (sc->sc_quirks & FORCE_SHORT_INQUIRY) {
			ret = memcpy_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, cmd_ptr, cmd_len);
			if (ret != EOK) {
				usb_err("memcpy_s failed!, ret:%d\n", ret);
				return (0);
			}
			sc->sc_transfer.cmd_data[4] = SHORT_INQUIRY_LENGTH;
			return (1);
		}
		break;

	case TEST_UNIT_READY:
		if (sc->sc_quirks & NO_TEST_UNIT_READY) {
			DPRINTF_UMASS(sc, UDMASS_SCSI, "Converted TEST_UNIT_READY "
			    "to START_UNIT\n");
			sc->sc_transfer.cmd_data[0] = START_STOP_UNIT;
			sc->sc_transfer.cmd_data[4] = SSS_START;
			return (1);
		}
		break;

	case REZERO_UNIT:
	case REQUEST_SENSE:
	case START_STOP_UNIT:
	case SEND_DIAGNOSTIC:
	case PREVENT_ALLOW:
	case READ_CAPACITY:
	case READ_10:
	case WRITE_10:
	case POSITION_TO_ELEMENT:	/* SEEK_10 */
	case SYNCHRONIZE_CACHE:
	case MODE_SELECT_10:
	case MODE_SENSE_10:
	case READ_BUFFER:
	case 0x42:			/* READ_SUBCHANNEL */
	case 0x43:			/* READ_TOC */
	case 0x44:			/* READ_HEADER */
	case 0x47:			/* PLAY_MSF (Play Minute/Second/Frame) */
	case 0x48:			/* PLAY_TRACK */
	case 0x49:			/* PLAY_TRACK_REL */
	case 0x4b:			/* PAUSE */
	case 0x51:			/* READ_DISK_INFO */
	case 0x52:			/* READ_TRACK_INFO */
	case 0x54:			/* SEND_OPC */
	case 0x59:			/* READ_MASTER_CUE */
	case 0x5b:			/* CLOSE_TR_SESSION */
	case 0x5c:			/* READ_BUFFER_CAP */
	case 0x5d:			/* SEND_CUE_SHEET */
	case 0xa1:			/* BLANK */
	case 0xa5:			/* PLAY_12 */
	case 0xa6:			/* EXCHANGE_MEDIUM */
	case 0xad:			/* READ_DVD_STRUCTURE */
	case 0xbb:			/* SET_CD_SPEED */
	case 0xe5:			/* READ_TRACK_INFO_PHILIPS */
		break;

	case READ_12:
	case WRITE_12:
	default:
		DPRINTF_UMASS(sc, UDMASS_SCSI, "Unsupported ATAPI "
		    "command 0x%02x - trying anyway\n",
		    cmd_ptr[0]);
		break;
	}

	ret = memcpy_s(sc->sc_transfer.cmd_data, UMASS_MAX_CMDLEN, cmd_ptr, cmd_len);
	if (ret != EOK) {
		usb_err("memcpy_s failed!, ret:%d\n", ret);
		return (0);
	}

	return (1);			/* success */
}

static uint8_t
umass_no_transform(struct umass_softc *sc, uint8_t *cmd,
	uint8_t cmdlen)
{
	return (0);			/* failure */
}

#ifdef LOSCFG_USB_DEBUG
static void
umass_bbb_dump_cbw(struct umass_softc *sc, umass_bbb_cbw_t *cbw)
{
	uint8_t *c = cbw->CBWCDB;

	uint32_t dlen = UGETDW(cbw->dCBWDataTransferLength);
	uint32_t tag = UGETDW(cbw->dCBWTag);

	uint8_t clen = cbw->bCDBLength;
	uint8_t flags = cbw->bCBWFlags;
	uint8_t lun = cbw->bCBWLUN;

	DPRINTF_UMASS(sc, UDMASS_BBB, "CBW %d: cmd = %db "
	    "(0x%02x%02x%02x%02x%02x%02x%s), "
	    "data = %db, lun = %d, dir = %s\n",
	    tag, clen,
	    c[0], c[1], c[2], c[3], c[4], c[5], (clen > 6 ? "..." : ""),
	    dlen, lun, (flags == CBWFLAGS_IN ? "in" :
	    (flags == CBWFLAGS_OUT ? "out" : "<invalid>")));
}

static void
umass_bbb_dump_csw(struct umass_softc *sc, umass_bbb_csw_t *csw)
{
	uint32_t sig = UGETDW(csw->dCSWSignature);
	uint32_t tag = UGETDW(csw->dCSWTag);
	uint32_t res = UGETDW(csw->dCSWDataResidue);
	uint8_t status = csw->bCSWStatus;

	DPRINTF_UMASS(sc, UDMASS_BBB, "CSW %d: sig = 0x%08x (%s), tag = 0x%08x, "
	    "res = %d, status = 0x%02x (%s)\n",
	    tag, sig, (sig == CSWSIGNATURE ? "valid" : "invalid"),
	    tag, res,
	    status, (status == CSWSTATUS_GOOD ? "good" :
	    (status == CSWSTATUS_FAILED ? "failed" :
	    (status == CSWSTATUS_PHASE ? "phase" : "<invalid>"))));
}

static void
umass_cbi_dump_cmd(struct umass_softc *sc, void *cmd, uint8_t cmdlen)
{
	uint8_t *c = cmd;
	uint8_t dir = sc->sc_transfer.dir;

	DPRINTF_UMASS(sc, UDMASS_BBB, "cmd = %db "
	    "(0x%02x%02x%02x%02x%02x%02x%s), "
	    "data = %db, dir = %s\n",
	    cmdlen,
	    c[0], c[1], c[2], c[3], c[4], c[5], (cmdlen > 6 ? "..." : ""),
	    sc->sc_transfer.data_len,
	    (dir == DIR_IN ? "in" :
	    (dir == DIR_OUT ? "out" :
	    (dir == DIR_NONE ? "no data phase" : "<invalid>"))));
}

#endif

#define	SCSI_INQ_LEN	0x24

static uint8_t scsi_test_unit_ready[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static uint8_t scsi_inquiry[] = {
	0x12, 0x00, 0x00, 0x00, SCSI_INQ_LEN, 0x00
};
static uint8_t scsi_request_sense[] = {
	0x03, 0x00, 0x00, 0x00, 0x12, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static uint8_t scsi_read_capacity[] = {
	0x25, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00
};

static uint8_t scsi_read_capacity_16[] = {
	0x9e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00
};

/* Description: Get a (possibly unaligned) 16-bit big endian value. */
static inline uint16_t
usbhost_getbe16(const uint8_t *val)
{
	return ((uint16_t)val[0] << 8 | (uint16_t)val[1]);
}

/* Description: Put a (possibly unaligned) 16-bit little endian value. */
void
usbhost_putle16(uint8_t *dest, uint16_t val)
{
	dest[0] = val & 0xff; /* Little endian means LS byte first in byte stream */
	dest[1] = val >> 8;
}

/* Description: Put a (possibly unaligned) 16-bit big endian value. */
void
usbhost_putbe16(uint8_t *dest, uint16_t val)
{
	dest[0] = val >> 8; /* Big endian means MS byte first in byte stream */
	dest[1] = val & 0xff;
}

/* Description: Get a (possibly unaligned) 32-bit big endian value. */
uint32_t
usbhost_getbe32(const uint8_t *val)
{
	/* Big endian means MS halfword first in byte stream */
	return ((uint32_t)usbhost_getbe16(val) << 16 |
	    (uint32_t)usbhost_getbe16(&val[2]));
}

/* Description: Get a (possibly unaligned) 64-bit big endian value. */
uint64_t
usbhost_getbe64(const uint8_t *val)
{
	/* Big endian means MS halfword first in byte stream */
	return ((uint64_t)usbhost_getbe32(val) << 32 |
	    (uint64_t)usbhost_getbe32(&val[4]));
}

/* Description: Put a (possibly unaligned) 32-bit little endian value. */
void
usbhost_putle32(uint8_t *dest, uint32_t val)
{
	/* Little endian means LS halfword first in byte stream  */
	usbhost_putle16(dest, (uint16_t)(val & 0xffff));
	usbhost_putle16(dest+2, (uint16_t)(val >> 16));
}

/* Put a (possibly unaligned) 32-bit big endian value. */
void
usbhost_putbe32(uint8_t *dest, uint32_t val)
{
	/* Big endian means MS halfword first in byte stream */
	usbhost_putbe16(dest, (uint16_t)(val >> 16));
	usbhost_putbe16(dest+2, (uint16_t)(val & 0xffff));
}

/* Put a (possibly unaligned) 64-bit big endian value. */
void
usbhost_putbe64(uint8_t *dest, uint64_t val)
{
	/* Big endian means MS halfword first in byte stream */
	usbhost_putbe32(dest, (uint32_t)(val >> 32));
	usbhost_putbe32(dest+4, (uint32_t)(val & 0xffffffff));
}

void
usbhost_readcdb16(uint64_t startsector, uint16_t blocksize,
    unsigned int nsectors, struct scsicmd_read16_s *cdb)
{
	struct scsicmd_read16_s *rd16 = (struct scsicmd_read16_s *)cdb;

	/* Format the CDB */
	rd16->opcode = SCSI_CMD_READ16;
	usbhost_putbe64(rd16->lba, startsector);
	usbhost_putbe32(rd16->xfrlen, nsectors);
}

void
usbhost_readcdb10(size_t startsector, uint16_t blocksize,
    unsigned int nsectors, struct scsicmd_read10_s *cdb)
{
	struct scsicmd_read10_s *rd10 = (struct scsicmd_read10_s *)cdb;

	/* Format the CDB */
	rd10->opcode = SCSI_CMD_READ10;
	usbhost_putbe32(rd10->lba, startsector);
	usbhost_putbe16(rd10->xfrlen, nsectors);
}

void
usbhost_writecbw16(uint64_t startsector, uint16_t blocksize,
    unsigned int nsectors, struct scsicmd_write16_s *cdb)
{
	struct scsicmd_write16_s *wr16 = (struct scsicmd_write16_s *)cdb;

	wr16->opcode = SCSI_CMD_WRITE16;
	usbhost_putbe64(wr16->lba, startsector);
	usbhost_putbe32(wr16->xfrlen, nsectors);
}

void
usbhost_writecbw10(size_t startsector, uint16_t blocksize,
    unsigned int nsectors, struct scsicmd_write10_s *cdb)
{
	struct scsicmd_write10_s *wr10 = (struct scsicmd_write10_s *)cdb;

	wr10->opcode = SCSI_CMD_WRITE10;
	usbhost_putbe32(wr10->lba, startsector);
	usbhost_putbe16(wr10->xfrlen, nsectors);
}

int
umass_test_unit_ready(struct umass_softc *sc)
{
	uint32_t status;
	int32_t res;

	if((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	(void)umass_scsi_transform(sc, scsi_test_unit_ready, SCSICMD_TESTUNITREADY8_SIZEOF);
	res = umass_command_start(sc, DIR_NONE, NULL, 0, 1000, umass_cam_cb, sc->data_ccb);
	if (STATUS_CMD_OK != res) {
		return (-1);
	}

	status = sc->data_ccb->csio.status;
	if (status != STATUS_CMD_OK) {
		return (-1);
	}

	return (0);
}

int
umass_read_capacity_16(struct umass_softc *sc)
{
	struct scsiresp_readcapacity16_s resp;
	uint32_t res;
	int ret;

	(void)umass_scsi_transform(sc, scsi_read_capacity_16, SCSICMD_READCAPACITY16_SIZEOF);
	res = (uint32_t)umass_command_start(sc, DIR_IN, sc->data_ccb->csio.data_ptr,
	    (uint32_t)SCSIRESP_READCAPACITY16_SIZEOF,
	    (uint32_t)1000, umass_cam_cb, sc->data_ccb);
	if (STATUS_CMD_OK != res) {
		return (-1);
	}

	ret = memcpy_s((void *)&resp, sizeof(resp), sc->data_ccb->csio.data_ptr,
	    SCSIRESP_READCAPACITY16_SIZEOF);
	if (ret != EOK) {
		usb_err("memcpy_s failed, %d\n", ret);
		return (-1);
	}

	sc->info.sectornum= usbhost_getbe64(resp.lba) + 1;
	sc->info.sectorsize= usbhost_getbe32(resp.blklen);

	return (0);
}

int
umass_read_capacity(struct umass_softc *sc)
{
	struct scsiresp_readcapacity10_s resp;
	int32_t ret;

	if ((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	(void)umass_scsi_transform(sc, scsi_read_capacity, SCSICMD_READCAPACITY10_SIZEOF);
	ret = umass_command_start(sc, DIR_IN, sc->data_ccb->csio.data_ptr,
	    SCSIRESP_READCAPACITY10_SIZEOF,
	    1000, umass_cam_cb, sc->data_ccb);
	if (STATUS_CMD_OK != ret) {
		return (-1);
	}

	ret = memcpy_s((void *)&resp, sizeof(resp), sc->data_ccb->csio.data_ptr,
	    SCSIRESP_READCAPACITY10_SIZEOF);
	if (ret != EOK) {
		usb_err("memcpy_s failed, %d\n", ret);
		return (-1);
	}

	/* The disk Capacity is bigger than 2T */
	if (usbhost_getbe32(resp.lba) == 0xffffffff) {
		ret = umass_read_capacity_16(sc);
		if (ret != 0) {
			usb_err("Read Capacity failed, %d\n", ret);
			return (-1);
		}
		sc->sc_super_disk = TRUE;

		return (0);
	}

	sc->info.sectornum= usbhost_getbe32(resp.lba) + 1;
	sc->info.sectorsize= usbhost_getbe32(resp.blklen);
	sc->sc_super_disk = FALSE;

	return (0);
}

int
umass_read10(struct umass_softc *sc, size_t startsector, uint16_t blocksize,
    unsigned int nsectors, unsigned char *buf)
{
	struct scsicmd_read10_s cdb;
	uint8_t *data_buf = buf;
	uint32_t status;
	int32_t ret;
	uint32_t flag = 0;

	if ((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	if ((sc->info.sectornum < (startsector + nsectors)) || (sc->info.sectorsize < blocksize))
		return (-1);

	if (((uintptr_t)data_buf & (USB_CACHE_ALIGN_SIZE - 1)) != 0)
	{
		data_buf = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(nsectors * blocksize));
		if (data_buf == NULL) {
			PRINT_ERR("Malloc failed!->%s %d\n", __FUNCTION__, __LINE__);
			return (-1);
		}
		flag = 1;
	}

	(void)memset_s(&cdb, sizeof(struct scsicmd_read10_s), 0, sizeof(struct scsicmd_read10_s));
	usbhost_readcdb10(startsector, blocksize, nsectors, &cdb);
	(void)umass_scsi_transform(sc, (uint8_t *)&cdb, SCSICMD_READ10_SIZEOF);
	ret = umass_command_start(sc, DIR_IN, (void *)data_buf, blocksize * nsectors, 0,
	    umass_cam_cb, sc->data_ccb);
	if (ret != STATUS_CMD_OK) {
		if (flag == 1)
			free(data_buf);
		return (-1);
	}

	if (flag == 1) {
		if (!LOS_IsUserAddressRange((vaddr_t)buf, blocksize * nsectors - sc->data_ccb->csio.resid)) {
			ret = memcpy_s(buf, nsectors * blocksize, data_buf, blocksize * nsectors - sc->data_ccb->csio.resid);
		} else {
			ret = ((nsectors * blocksize >= blocksize * nsectors - sc->data_ccb->csio.resid) ?
				LOS_ArchCopyToUser(buf, data_buf, blocksize * nsectors - sc->data_ccb->csio.resid) : ERANGE_AND_RESET);
		}
		free(data_buf);
		if (ret != EOK) {
			return (-1);
		}
	}

	status = sc->data_ccb->csio.status;
	if (status != STATUS_CMD_OK) {
		return (-1);
	}

	return (0);
}

int
umass_read16(struct umass_softc *sc, uint64_t startsector, uint16_t blocksize,
    unsigned int nsectors, unsigned char *buf)
{
	struct scsicmd_read16_s cdb;
	uint8_t *data_buf = buf;
	uint32_t status;
	uint32_t res;
	uint32_t flag = 0;
	int ret;

	if ((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	if ((sc->info.sectornum < (startsector + nsectors)) || (sc->info.sectorsize < blocksize))
		return (-1);

	if (((uintptr_t)data_buf & (USB_CACHE_ALIGN_SIZE - 1)) != 0) {
		data_buf = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(nsectors * blocksize));
		if (data_buf == NULL) {
			PRINT_ERR("Malloc failed!->%s %d\n", __FUNCTION__, __LINE__);
			return (-1);
		}
		flag = 1;
	}

	(void)memset_s(&cdb, sizeof(struct scsicmd_read16_s), 0, sizeof(struct scsicmd_read16_s));
	usbhost_readcdb16(startsector, blocksize, nsectors, &cdb);
	(void)umass_scsi_transform(sc, (uint8_t *)&cdb, SCSICMD_READ16_SIZEOF);
	res = umass_command_start(sc, DIR_IN, (void *)data_buf, blocksize * nsectors, 0,
	    umass_cam_cb, sc->data_ccb);
	if (STATUS_CMD_OK != res) {
		if (flag == 1)
			free(data_buf);
		return (-1);
	}

	if (flag == 1) {
		if (!LOS_IsUserAddressRange((vaddr_t)buf, blocksize * nsectors - sc->data_ccb->csio.resid)) {
			ret = memcpy_s(buf, nsectors * blocksize, data_buf, blocksize * nsectors - sc->data_ccb->csio.resid);
		} else {
			ret = ((nsectors * blocksize >= blocksize * nsectors - sc->data_ccb->csio.resid) ?
				LOS_ArchCopyToUser(buf, data_buf, blocksize * nsectors - sc->data_ccb->csio.resid) : ERANGE_AND_RESET);
		}
		free(data_buf);
		if (ret != EOK) {
			return (-1);
		}
	}

	status = sc->data_ccb->csio.status;
	if (status != STATUS_CMD_OK) {
		return (-1);
	}

	return (0);
}

int
umass_write10(struct umass_softc *sc, size_t startsector, uint16_t blocksize,
    unsigned int nsectors, const unsigned char *buf)
{
	struct scsicmd_write10_s cdb;
	uint8_t *data_buf = (uint8_t *)buf;
	uint32_t status;
	int32_t ret;
	uint32_t flag = 0;

	if((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	if ((sc->info.sectornum < (startsector + nsectors)) || (sc->info.sectorsize < blocksize))
		return (-1);

	if (((uintptr_t)data_buf & (USB_CACHE_ALIGN_SIZE - 1)) != 0) {
		data_buf = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(nsectors * blocksize));
		if (data_buf == NULL) {
			PRINT_ERR("Malloc failed!->%s %d\n", __FUNCTION__, __LINE__);
			return (-1);
		}

		if (!LOS_IsUserAddressRange((vaddr_t)buf, blocksize * nsectors)) {
			(void)memcpy_s(data_buf, blocksize * nsectors, buf, blocksize * nsectors);
		} else {
			ret = LOS_ArchCopyFromUser(data_buf, buf, blocksize * nsectors);
			if (ret != 0) {
				free(data_buf);
				PRINT_ERR("copy failed!->%s %d\n", __FUNCTION__, __LINE__);
				return (-1);
			}
		}
		flag = 1;
	}

	(void)memset_s(&cdb, sizeof(struct scsicmd_write10_s), 0, sizeof(struct scsicmd_write10_s));
	usbhost_writecbw10(startsector, blocksize, nsectors, &cdb);
	(void)umass_scsi_transform(sc, (uint8_t *)&cdb, SCSICMD_WRITE10_SIZEOF);
	ret = umass_command_start(sc, DIR_OUT, (void *)data_buf, blocksize * nsectors, 1000,
	    umass_cam_cb, sc->data_ccb);

	if (flag == 1) {
		free(data_buf);
	}

	status = sc->data_ccb->csio.status;
	if ((ret != STATUS_CMD_OK) || (status != STATUS_CMD_OK)) {
		return (-1);
	}

	return (0);
}

int
umass_write16(struct umass_softc *sc, uint64_t startsector, uint16_t blocksize,
    unsigned int nsectors, const unsigned char *buf)
{
	struct scsicmd_write16_s cdb;
	uint8_t *data_buf = (uint8_t *)buf;
	uint32_t status;
	int32_t  res;
	int32_t ret;
	uint32_t flag = 0;

	if((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	if ((sc->info.sectornum < (startsector + nsectors)) || (sc->info.sectorsize < blocksize)) {
		return (-1);
	}

	if (((uintptr_t)data_buf & (USB_CACHE_ALIGN_SIZE - 1)) != 0)
	{
		data_buf = (uint8_t *)memalign(USB_CACHE_ALIGN_SIZE, SKB_DATA_ALIGN(nsectors * blocksize));
		if (data_buf == NULL) {
			PRINT_ERR("Malloc failed!->%s %d\n", __FUNCTION__, __LINE__);
			return (-1);
		}

		if (!LOS_IsUserAddressRange((vaddr_t)buf, blocksize * nsectors)) {
			(void)memcpy_s(data_buf, blocksize * nsectors, buf, blocksize * nsectors);
		} else {
			ret = LOS_ArchCopyFromUser(data_buf, buf, blocksize * nsectors);
			if (ret != 0) {
				free(data_buf);
				PRINT_ERR("copy failed!->%s %d\n", __FUNCTION__, __LINE__);
				return (-1);
			}
		}
		flag = 1;
	}

	(void)memset_s(&cdb, sizeof(struct scsicmd_write16_s), 0, sizeof(struct scsicmd_write16_s));
	usbhost_writecbw16(startsector, blocksize, nsectors, &cdb);
	(void)umass_scsi_transform(sc, (uint8_t *)&cdb, SCSICMD_WRITE16_SIZEOF);
	res = umass_command_start(sc, DIR_OUT, (void *)data_buf, blocksize * nsectors, 1000,
	    umass_cam_cb, sc->data_ccb);

	if (flag == 1)
	{
		free(data_buf);
	}

	status = sc->data_ccb->csio.status;
	if ((res != STATUS_CMD_OK) || (status != STATUS_CMD_OK)) {
		return (-1);
	}

	return (0);
}

int
umass_inquiry(struct umass_softc *sc)
{
	uint32_t status;
	int32_t ret;

	if ((sc == NULL) || (sc->data_ccb == NULL)) {
		goto error;
	}

	(void)umass_scsi_transform(sc, scsi_inquiry, SCSICMD_INQUIRY_SIZEOF);
	ret = umass_command_start(sc, DIR_IN, sc->data_ccb->csio.data_ptr, SCSIRESP_INQUIRY_SIZEOF,
	    1000, umass_cam_cb, sc->data_ccb);
	if (ret != STATUS_CMD_OK) {
		goto error;
	}

	status = sc->data_ccb->csio.status;
	if (status != STATUS_CMD_OK) {
		PRINT_WARN("Failed to get the inquiry_status [status=%d].\n", status);
		goto error;
	}

	ret = umass_scsi_inquiry_data(sc, sc->data_ccb->csio.data_ptr, SCSIRESP_INQUIRY_SIZEOF);
	if (ret == -1){
		PRINT_WARN("Failed to get the scsi_inquiry data .\n");
		goto error;
	}else if (ret == 1) {
		/* find Direct-access LUN */
		return (0);
	}

error:
	return (-1);
}

int
umass_request_sense(struct umass_softc *sc)
{
	uint32_t status;
	int32_t ret;
	if ((sc == NULL) || (sc->data_ccb == NULL)) {
		return (-1);
	}

	(void)umass_scsi_transform(sc, scsi_request_sense, SCSICMD_REQUESTSENSE_SIZEOF);
	ret = umass_command_start(sc, DIR_IN, sc->data_ccb->csio.data_ptr, SCSIRESP_FIXEDSENSEDATA_SIZEOF,
	    1000, umass_cam_cb, sc->data_ccb);
	if (ret != STATUS_CMD_OK) {
		return (-1);
	}

	status = sc->data_ccb->csio.status;
	if (status != STATUS_CMD_OK) {
		return (-1);
	}

	return (0);
}

void *
umass_bind(void)
{
	return ((void*)p_umsf);
}

void
umass_status(void)
{
	struct umass_softc *sc = p_umsf;
	UINT8 cmd;
	UINT8 lun;
	UINT8 max;
	UINT8 speed;
	UINT8 phase;
	UINT8 state;
	UINT16 vid;
	UINT16 pid;
	UINT32 tag, residuce;

	if (sc == NULL) {
		return;
	}

	cmd = sc->sc_transfer.cmd_data[0];
	lun = sc->sc_transfer.lun;
	max = sc->sc_maxlun + 1;
	speed = sc->sc_udev->speed;
	phase = sc->sc_last_xfer_index;
	state = USB_GET_STATE(sc->sc_xfer[phase]);
	vid = UGETW(sc->sc_udev->ddesc.idVendor);
	pid = UGETW(sc->sc_udev->ddesc.idProduct);
	tag = UGETDW(sc->cbw.dCBWTag);
	residuce = UGETDW(sc->csw.dCSWDataResidue);

	dprintf("VID:%04X/PID:%04X/SPD:%02d",vid,pid,speed);
	if (sc->sc_transfer.ccb) {
		dprintf("/ST:%02d ",state);
		if (state == USB_ST_SETUP) {
			dprintf("[SP]");
		} else if (state == USB_ST_TRANSFERRED) {
			dprintf("[TD]");
		}
		dprintf("/cPHASE:%02d ",phase);
	} else {
		dprintf("/nPHASE:%02d ",phase);
	}
	if (phase == UMASS_T_BBB_COMMAND) {
		dprintf("[CBW]");
	} else if (phase == UMASS_T_BBB_DATA_READ) {
		dprintf("[DATA]");
	} else if (phase == UMASS_T_BBB_DATA_WRITE) {
		dprintf("[DATA]");
	} else if (phase == UMASS_T_BBB_STATUS) {
		dprintf("[CSW]");
	} else if (phase == UMASS_T_BBB_DATA_RD_CS) {
		dprintf("[STAL]");
	} else if (phase == UMASS_T_BBB_DATA_WR_CS) {
		dprintf("[STAL]");
	}
	dprintf("\n");

	dprintf("CL:%d/ML:%d/TG:%08X/RDU:%d/CMD:%X ",lun,max,tag,residuce,cmd);
	if (cmd == SCSI_CMD_READ10) {
		dprintf("[RD]\n");
	} else if (cmd == SCSI_CMD_WRITE10) {
		dprintf("[WR]\n");
	} else if (cmd == SCSI_CMD_INQUIRY) {
		dprintf("[INQ]\n");
	} else if (cmd == SCSI_CMD_TESTUNITREADY) {
		dprintf("[TUR]\n");
	} else if (cmd == SCSI_CMD_REQUESTSENSE) {
		dprintf("[RS]\n");
	} else if (cmd == SCSI_CMD_READCAPACITY10) {
		dprintf("[RC]\n");
	} else {
		dprintf("\n");
	}
}

static int
umass_open(FAR struct inode *filep)
{
	(void)filep;
	return (0);
}

static int
umass_close(FAR struct inode *filep)
{
	(void)filep;
	return (0);
}

static ssize_t
umass_read(FAR struct inode *umass_inode, FAR unsigned char *buffer,
		    uint64_t start_sector, unsigned int nsectors)
{
	int status;
	struct umass_softc *sc = (struct umass_softc *)umass_inode->i_private;

	mtx_lock(&sc->sc_umass_mtx);
	if (sc->sc_super_disk == TRUE) {
		status = umass_read16(sc, start_sector, (uint16_t)sc->info.sectorsize, nsectors, buffer);
	} else {
		status = umass_read10(sc, (size_t)start_sector, (uint16_t)sc->info.sectorsize, nsectors, buffer);
	}
	mtx_unlock(&sc->sc_umass_mtx);

	if(status)
		return (-1);
	else
		return ((ssize_t)nsectors);
}

static ssize_t
umass_write(FAR struct inode *umass_inode, FAR const unsigned char *buffer,
		    uint64_t start_sector, unsigned int nsectors)
{
	int status;
	struct umass_softc *sc = (struct umass_softc *)umass_inode->i_private;

	mtx_lock(&sc->sc_umass_mtx);
	if (sc->sc_super_disk == TRUE) {
		status = umass_write16(sc, start_sector, (uint16_t)sc->info.sectorsize, nsectors, buffer);
	} else {
		status = umass_write10(sc, (size_t)start_sector, (uint16_t)sc->info.sectorsize, nsectors, buffer);
	}
	mtx_unlock(&sc->sc_umass_mtx);

	if(status)
		return (-1);
	else
		return ((ssize_t)nsectors);
}

static int
umass_geometry(FAR struct inode *umass_inode, FAR struct geometry *ugeometry)
{
	struct umass_softc *sc;

	if ((ugeometry == NULL) || (umass_inode == NULL))
		return (-1);

	sc = (struct umass_softc *)umass_inode->i_private;

	if (sc == NULL)
		return (-1);

	mtx_lock(&sc->sc_umass_mtx);
	ugeometry->geo_available	= true;
	ugeometry->geo_mediachanged = false;
	ugeometry->geo_writeenabled = true;
	ugeometry->geo_nsectors	 = sc->info.sectornum;
	ugeometry->geo_sectorsize   = sc->info.sectorsize;
	mtx_unlock(&sc->sc_umass_mtx);

	return (0);
}

static int
umass_ioctl(FAR struct inode *umass_inode, int cmd, unsigned long arg)
{
	(void)umass_inode;
	(void)cmd;
	(void)arg;
	return (0);
}

const struct block_operations g_dev_umass_ops = {
	.open  = umass_open,
	.close = umass_close,
	.read  = umass_read,
	.write = umass_write,
	.geometry = umass_geometry,
	.ioctl = umass_ioctl,
	.unlink = NULL
};

static int
umass_dev_is_ready(struct umass_softc *sc)
{
	int lun;
	int ret;
	uint8_t valid_lun;

	mtx_lock(&sc->sc_umass_mtx);
	for (lun = 0; lun <= sc->sc_maxlun; lun++) {
		sc->sc_transfer.lun = lun;
		if (umass_inquiry(sc) < 0)
			continue;

		valid_lun = lun;
		ret = umass_test_unit_ready(sc);
		if(ret == 0) {
			sc->sc_transfer.lun = valid_lun;
			ret = umass_read_capacity(sc);
			if (ret < 0) {
				mtx_unlock(&sc->sc_umass_mtx);
				PRINT_ERR("umass read capacity fail!\n");
				return (0);
			}
			mtx_unlock(&sc->sc_umass_mtx);
			return (1);
		}

		ret = umass_request_sense(sc);
		if(ret < 0) {
			PRINT_ERR("Request sense fail!\n");
			mtx_unlock(&sc->sc_umass_mtx);
			return (0);
		}
	}
	mtx_unlock(&sc->sc_umass_mtx);
	return (0);
}

static int
umass_attach_dev_sub(struct umass_softc *sc, unsigned int dev_unit)
{
	int ret;
	int disk_id;
	char devname[MASS_NAME]= {0};
#if USB_HAVE_DEVICE_TOPOLOGY
	device_t dev;
	struct usb_device *udev;
	usbd_bt_node *cur_node;
	struct node_info parent_info;
	struct node_info cur_info;
#endif

	umass_dev_lock(dev_unit);

#if USB_HAVE_DEVICE_TOPOLOGY
	dev = sc->sc_dev;
	udev = sc->sc_udev;
	dev_quantity |= 1ull << (unsigned int)device_get_unit(dev);
#endif

#if USB_SUPPORT_SD_HOT_PLUG
	if (!umass_dev_is_attached(dev_unit))
#endif
	{
		devunit_to_devname(dev_unit, devname);
		disk_id = los_alloc_diskid_byname(devname);
		OsSetUsbStatus(disk_id);
		ret = los_disk_init(devname, &g_dev_umass_ops, (void *)sc, disk_id, NULL);
		if (ret) {
			PRINT_ERR("umass_attach_dev : los_disk_init fail!\n");
			goto error;
		}
	}
#if USB_SUPPORT_SD_HOT_PLUG
	umass_dev_attach_flag_set(dev_unit);
#endif

#if USB_HAVE_DEVICE_TOPOLOGY
	cur_info.nameunit = device_get_nameunit(dev);
	cur_info.port_no = udev->port_no;
	cur_node = usbd_create_bt_node(&cur_info);
	if (cur_node == NULL) {
		goto error;
	}

	parent_info.nameunit = device_get_nameunit(device_get_parent(dev));
	parent_info.port_no = udev->port_no;

	(void)usbd_insert_bt_node(cur_node, hub_tree, &parent_info);
#endif

	umass_dev_unlock(dev_unit);
	return (0);

error:
	umass_dev_unlock(dev_unit);
	return (-1);
}

static void
umass_detach_dev_sub(struct umass_softc *sc, int dev_unit, int flag)
{
	int disk_id;
	char devname[MASS_NAME]= {0};
#if USB_HAVE_DEVICE_TOPOLOGY
	struct node_info cur_info;
	struct node_info parent_info;
	device_t dev = NULL;
	struct usb_device *udev = NULL;
#endif

	umass_dev_lock(dev_unit);

#if USB_HAVE_DEVICE_TOPOLOGY
	dev = sc->sc_dev;
	udev = sc->sc_udev;
#if USB_SUPPORT_SD_HOT_PLUG
	if (umass_dev_is_attached(dev_unit))
#endif
	{
		parent_info.nameunit = device_get_nameunit(device_get_parent(dev));
		parent_info.port_no = udev->port_no;

		cur_info.nameunit = device_get_nameunit(dev);
		cur_info.port_no = udev->port_no;
		(void)usbd_remove_bt_node(hub_tree, &parent_info, &cur_info);
	}
#endif

#if USB_SUPPORT_SD_HOT_PLUG
	if (umass_dev_is_attached(dev_unit))
#endif
	{
		devunit_to_devname(dev_unit, devname);
		disk_id = los_get_diskid_byname(devname);
		(void)los_disk_deinit(disk_id);
		(void)OsClearUsbStatus(disk_id);
	}

	if (flag == 0) { /* 0: This interface is called from umass_detach, or is called elsewhere. */
#if USB_SUPPORT_SD_HOT_PLUG
		umass_dev_delete(sc, dev_unit);
#endif
	}

#if USB_HAVE_DEVICE_TOPOLOGY
	dev_quantity &= ~(1ull << (unsigned int)device_get_unit(dev));
#endif

	umass_dev_unlock(dev_unit);
}

#if USB_SUPPORT_SD_HOT_PLUG
void
umass_dev_status_check(UINTPTR arg)
{
	(void)arg;
	int ret;
	int i;
	struct umass_dev_info *dev = g_umass_dev_array;
	struct umass_softc *sc;

	while(1) {
		for (i = 0; i < MAX_DEVICE; i++) {
			umass_dev_lock(i);
			if (dev[i].used == 1) {
				sc = dev[i].sc;
				ret = umass_dev_is_ready(sc);
				if (ret == 0) {
					if (dev[i].attached == 1) {
						umass_detach_dev_sub(sc, dev[i].dev_unit, 1);
						dev[i].attached = 0;
					}
					umass_dev_unlock(i);
					continue;
				}

				if (dev[i].attached == 1) {
					umass_dev_unlock(i);
					continue;
				}

				ret = umass_attach_dev_sub(sc, dev[i].dev_unit);
				if (ret< 0) {
					umass_dev_unlock(i);
					PRINT_ERR("umass attach device sub failed!\n");
					continue;
				}
			}
			umass_dev_unlock(i);
		}
		(void)LOS_Msleep(1000);
	}
}

int
umass_dev_is_attached(unsigned int dev_unit)
{
	if (dev_unit >= MAX_DEVICE) {
		PRINT_ERR("%s %d, The device unit is wrong!\n", __FUNCTION__, __LINE__);
		return (-1);
	}

	return (g_umass_dev_array[dev_unit].attached);
}

static void
umass_dev_add(struct umass_softc *sc, int dev_unit)
{
	int id = dev_unit;

	if (g_umass_dev_array[id].used == 1) {
		PRINT_ERR("The id of umass device array is used!, id=%d\n", dev_unit);
		return;
	}

	g_umass_dev_array[id].sc = sc;
	g_umass_dev_array[id].dev_unit = dev_unit;
	g_umass_dev_array[id].used = 1;
	umass_dev_mtx_init(id, MTX_DEF | MTX_RECURSE);
}

static void
umass_dev_delete(struct umass_softc *sc, unsigned int dev_unit)
{
	unsigned int id = dev_unit;

	if (g_umass_dev_array[id].used == 0) {
		PRINT_ERR("The id of umass device array is not used!\n");
		return;
	}

	if (g_umass_dev_array[id].dev_unit == dev_unit &&
		g_umass_dev_array[id].sc == sc) {
		g_umass_dev_array[id].used = 0;
		g_umass_dev_array[id].sc = NULL;
		g_umass_dev_array[id].attached = 0;
		umass_dev_mtx_destroy(id);
	} else {
		PRINT_ERR("Can not find the umass device!\n");
	}
}

static void
umass_dev_attach_flag_set(int dev_unit)
{
	g_umass_dev_array[dev_unit].attached = 1;
}

static void
umass_task_check(int flag)
{
	int i;
	int ret;

	for (i = 0; i < MAX_DEVICE; i++) {
		if (g_umass_dev_array[i].used)
			break;
	}

	if (i == MAX_DEVICE) {
		if (flag == 0) { /* create task */
			ret = usb_os_task_creat(&umass_taskid, (TSK_ENTRY_FUNC)umass_dev_status_check,
			    LOSCFG_BASE_CORE_TSK_DEFAULT_PRIO, "umass_task", 0);
			if (ret) {
				PRINT_ERR("Create umass task fail!\n");
				return;
			}
		} else if (flag == 1) { /* delete task */
			ret = usb_os_task_delete(umass_taskid);
			if (ret) {
				PRINT_ERR("Delete umass task fail!\n");
				return;
			}
		} else {
			PRINT_ERR("%s flag error!\n", __FUNCTION__);
		}
	}
}
#endif

static void
devunit_to_devname(unsigned int dev_unit, char *devname)
{
	char name_suf;
	int ret;

#if USB_HAVE_DEVICE_TOPOLOGY
	if (!(0x1 & (dev_quantity >> dev_unit)))
#else
	if (dev_unit >= MAX_DEVICE)
#endif
	{
		dprintf("sorry, we don't support so many devices\n");
		return;
	}

	name_suf = 'a' + dev_unit;
	ret = snprintf_s(devname, MASS_NAME, MASS_NAME - 1, "%s%c", UMASS_ATTACH_PRENAME, name_suf);
	if (ret < 0) {
		usb_err("snprintf_s failed!, ret:%d\n", ret);
		return;
	}
}
static int32_t
umass_attach_dev(struct umass_softc *sc, unsigned int dev_unit)
{
	int ret;

	if (dev_unit >= MAX_DEVICE) {
		PRINT_ERR("sorry, we don't support so many devices\n");
		return (-1);
	}
#if USB_SUPPORT_SD_HOT_PLUG
	umass_task_check(0);
	umass_dev_add(sc, dev_unit);
#endif

	ret = umass_dev_is_ready(sc);
	if (ret) {
		ret = umass_attach_dev_sub(sc, dev_unit);
		if (ret < 0) {
#if USB_SUPPORT_SD_HOT_PLUG
			umass_dev_delete(sc, dev_unit);
#endif
			PRINT_ERR("umass attach device fail!\n");
			return (-1);
		}
	}

	return (0);
}

#if USB_HAVE_DEVICE_TOPOLOGY
int
umass_medium_probe(uint8_t medium, char *devname)
{
	struct usbd_bt_node *node;
	uint8_t dev_unit;

	if ((devname == NULL) || strlen(devname) > 7) { /* /dev/sd* */
		return (-1);
	}

	if ((medium < 1) || (medium > usbd_get_hub_quantity())) {
		return (-1);
	}

	node = usbd_per_order_probe(hub_tree, "umass", &medium);
	if (node != NULL) {
		dev_unit = usbd_atoi(node->info.nameunit + 5); /* 5 = umass */
		devunit_to_devname(dev_unit, devname);
	} else {
		return (-1);
	}
	return (0);
}
#endif

