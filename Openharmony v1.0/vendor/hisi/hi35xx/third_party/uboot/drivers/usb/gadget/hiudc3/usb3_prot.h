#ifndef __USB3_PROT_H__
#define __USB3_PROT_H__


/* FILE FRAME: TYPE(1)+SEQ(1)+CSEQ(1)+FILE(1)+LENGTH(4)+ADDRESS(4)+CRC(2) */
/* DATA FRAME: TYPE(1)+SEQ(1)+CSEQ(1)+DATA(0~1024)+CRC(2) */
/* EOT  FRAME: TYPE(1)+SEQ(1)+CSEQ(1)+CRC(2) */
#define	FRAME_HEAD			0
#define	FRAME_SEQ			1
#define	FRAME_CSEQ			2
#define	FRAME_TYPE			3
#define	FRAME_DATA_START		3
#define	FRAME_LENGTH			4
#define	FRAME_ADDRESS			8

#define	FRAME_FILE			0xFE
#define	FRAME_DATA			0xDA
#define	FRAME_EOT			0xED
#define FRAME_INQUIRE			0xCD

#define	USB3_RESPONSE_ACK		0xAA
#define	USB3_RESPONSE_NAK		0x55

#define FRAME_FILE_LEN			14
#define FRAME_EOT_LEN			5

#define FRAME_HEAD_LEN			5
#define FRAME_DATA_LEN			1024

#define	FILE_RAMINIT			1
#define	FILE_USB			2

#define	USB3_XFR_PROT_OK		0
#define	USB3_XFR_PROT_ERR		1
#define	USB3_XFR_PROT_SKIP		2
#define	USB3_XFR_PROT_COMPLETE		3
#define USB3_XFR_PROT_INPROGRESS	4
#define USB3_XFR_PROT_WAIT		0x05
#define USB3_XFR_PROT_INQUIRE		0x06
#define USB3_XFR_PROT_ADDR_ERROR	0x07


void usb3_handle_protocol(void *dev);

#endif /* __USB3_PROT_H__ */
