/*
 * Description: declaration of tftpc APIs
 */

#ifndef __LWIP_TFTP_H__
#define __LWIP_TFTP_H__

#include "lwip/opt.h"
#include "lwip/sockets.h"

#if LWIP_TFTP /* don't build if not configured for use in lwipopts.h */

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#define TFTP_NULL_UINT32        ((u32_t)0xffffffffUL)

#define TFTP_NULL_INT32       -1

/**
 *
 * This Enum is used to specify the transfer mode of the file to be handled by TFTP client.
 */
typedef enum tag_tftpc_transfermode {
  TRANSFER_MODE_ASCII = 0,  /**< Indicates that the mode of transfer is ASCII. */
  TRANSFER_MODE_BINARY,     /**< Indicates that the mode of transfer is Binary */
  TRANSFER_MODE_BUTT        /**< Indicates invalid transfer mode.*/
} TFTPC_TRANSFER_MODE_E;

/**
 * This Enum is used to specify the transfer mode to be handled by TFTP client
 * This Enum indicates the TFTP client transfer mode of the file
 */
typedef enum tag_tftpc_errcode {

  TFTPC_SOCKET_FAILURE              = 1, /**< Error while creating UDP socket. */
  TFTPC_BIND_FAILURE                = 2, /**< Error while binding to the UDP socket. */
  TFTPC_SELECT_ERROR                = 3, /**< Error returned by select() system call. */
  TFTPC_RECVFROM_ERROR              = 4, /**< Error while receiving data from the peer. */
  TFTPC_SENDTO_ERROR                = 5, /**< Error while sending data to the peer. */
  TFTPC_FILE_NOT_FOUND              = 6, /**< Requested file is not found. */
  TFTPC_CANNOT_RESOLVE_HOSTNAME     = 7, /**< This is the error sent by the server when host name cannot be
                                                resolved. */
  TFTPC_INVALID_PARAVALUE           = 8, /**< Input parameters passed to TFTP interfaces are invalid. */
  TFTPC_PROTO_ERROR                 = 9, /**< Error detected in TFTP packet or the error received from the
                                                TFTP server. */
  TFTPC_SYNC_FAILURE                = 10, /**< Error during packet synchronization while sending or unexpected packet
                                                 is received. */
  TFTPC_FILE_TOO_BIG                = 11, /**< File size limit crossed, Max block can be 0xFFFF, each block containing
                                                 512 bytes. */
  TFTPC_SRC_FILENAME_LENGTH_ERROR   = 12, /**< File name length greater than 256. */
  TFTPC_IP_NOT_WITHIN_RANGE         = 13, /**< Host name IP is not valid. */
  TFTPC_ACCESS_ERROR                = 14, /**< TFTP server returned file access error. */
  TFTPC_DISK_FULL                   = 15, /**< TFTP server returned error signifying that the DISK is full to
                                                 write. */
  TFTPC_FILE_EXISTS                 = 16, /**< TFTP server returned error signifying that the file exists. */
  TFTPC_FILE_NOT_EXIST              = 17, /**< tftp_put_file_by_filename returned error signifying that the source
                                                 file name do not exist. */
  TFTPC_MEMALLOC_ERROR              = 18, /**< Memory allocation failed in TFTP client. */
  TFTPC_FILEOPEN_ERROR              = 19, /**< File open failed. */
  TFTPC_FILEREAD_ERROR              = 20, /**< File read error. */
  TFTPC_FILECREATE_ERROR            = 21, /**< File create error. */
  TFTPC_FILEWRITE_ERROR             = 22, /**< File write error. */
  TFTPC_TIMEOUT_ERROR               = 23, /**< Max time expired while waiting for file to be received. */
  TFTPC_PKT_SIZE_ERROR              = 24, /**< Error when the received packet is less than 4 bytes (error length) or
                                                 greater than 512 bytes. */
  TFTPC_ERROR_NOT_DEFINED           = 25, /**< Returned by TFTP server for protocol user error. */
  TFTPC_DEST_PATH_LENGTH_ERROR      = 26, /**< If the destination file path length is greater than 256. */
  TFTPC_UNKNOWN_TRANSFER_ID         = 27, /**< Returned by TFTP server for undefined transfer ID. */
  TFTPC_IOCTLSOCKET_FAILURE         = 28, /**< IOCTL function failed at TFTP client while setting the socket to
                                                 non-block. */
  TFTPC_MEMCPY_FAILURE              = 29 /**< TFTP memcpy failure. */
} TFTPC_ERR_CODE_E;

typedef enum tag_tftpc_opcode {
  TFTPC_OP_RRQ = 1,         /* read request */
  TFTPC_OP_WRQ,             /* write request */
  TFTPC_OP_DATA,            /* data packet */
  TFTPC_OP_ACK,             /* acknowledgement */
  TFTPC_OP_ERROR,           /* error code */
  TFTPC_OP_OPT              /* option code */
} TFTPC_OPCODE_E;

typedef enum tagtftpc_protocol_errcode {
  TFTPC_PROTOCOL_USER_DEFINED = 0,
  TFTPC_PROTOCOL_FILE_NOT_FOUND,
  TFTPC_PROTOCOL_ACCESS_ERROR,
  TFTPC_PROTOCOL_DISK_FULL,
  TFTPC_PROTOCOL_PROTO_ERROR,
  TFTPC_PROTOCOL_UNKNOWN_TRANSFER_ID,
  TFTPC_PROTOCOL_FILE_EXISTS,
  TFTPC_PROTOCOL_CANNOT_RESOLVE_HOSTNAME
} TFTPC_PROT_ERRCODE_E;

#ifndef TFTPC_MAX_SEND_REQ_ATTEMPTS
#define TFTPC_MAX_SEND_REQ_ATTEMPTS         5 /* tftp max attempts */
#endif

#ifndef TFTPC_TIMEOUT_PERIOD
#define TFTPC_TIMEOUT_PERIOD         5 /* tftp timeout period,unit :s */
#endif

#define TFTPC_SERVER_PORT          69 /* tftp server well known port no. */

/*
 *  MAX file size in TFTP is 32 MB.
 *  Reason for keeping 75 here , is ((75*512=38400bytes)/1024) =  37MB. So the recv/Send Loop can
 *  receive the complete MAX message from the network
 */
#define TFTPC_MAX_WAIT_IN_LOOP         75

#define TFTP_BLKSIZE               512     /* data block size (IEN-133) */
#define TFTP_HDRSIZE               4       /* TFTP header size */
#define TFTP_PKTSIZE              (TFTP_BLKSIZE + TFTP_HDRSIZE) /* Packet size */
#define TFTP_MAX_MODE_SIZE         9  /* max size of mode string */
#define TFTP_MAXERRSTRSIZE         100 /* max size of error message string */
#define TFTP_MAX_PATH_LENGTH       256 /* Max path or filename length */
#define TFTP_MAX_BLK_NUM          (0xFFFFL) /* MAximum block number */

/* IP address not including reserved IPs(0 and 127) and multicast addresses(Class D) */
#define TFTPC_IP_ADDR_MIN         0x01000000
#define TFTPC_IP_ADDR_EX_RESV     0x7effffff
#define TFTPC_IP_ADDR_CLASS_B     0x80000000
#define TFTPC_IP_ADDR_EX_CLASS_DE 0xdfffffff

#define TFTPC_FOUR 4  /* minimum packet size */

/****************************************************************************/
/*                            Structure definitions                         */
/****************************************************************************/
/* Tftp data packet */
typedef struct tagtftpc_data {
  u16_t us_blknum;                     /* block number */
  u8_t uc_databuf[TFTP_BLKSIZE];       /* Actual data */
} tftpc_data_s;

/* TFTP error packet */
typedef struct tagtftpc_error {
  u16_t us_errnum;                     /* error number */
  u8_t uc_errmesg[TFTP_MAXERRSTRSIZE]; /* error message */
} tftpc_error_s;

/* TFTP packet format */
typedef struct tagtftpc_packet {
  u16_t us_opcode; /* Opcode value */
  union {
    /* it contains mode and filename */
    s8_t uc_name_mode[TFTP_MAX_PATH_LENGTH + TFTP_MAX_MODE_SIZE];
    u16_t us_blknum; /* Block Number */
    tftpc_data_s sttftp_data; /* Data Packet */
    tftpc_error_s sttftp_err; /* Error Packet */
  } u;
} tftpc_packet_s;

/**
 * @defgroup TFTP_Interfaces
 * This section contains the TFTP Interfaces
 */
/*
 * Func Name:  lwip_tftp_get_file_by_filename
 */
/**
 * @ingroup TFTP_Interfaces
 * @brief
 * This API gets the source file from the server. It then stores the received file in the destination path
 * on the client system.
 *
 * @param[in]    ul_hostaddr        IP address of Host. This is the TFTP server IP. [NA]
 * @param[in]    us_tftpservport    TFTP server port. If the value is passed as 0 then the default TFTP
 *                                  PORT 69 is used. [NA]
 * @param[in]    uc_tftptransmode   File transfer mode, either TRANSFER_MODE_BINARY or TRANSFER_MODE_ASCII. [NA]
 * @param[in]    sz_srcfilename     Source file in the tftp server. [NA]
 * @param[in]    sz_destdirpath     Destination file path in the in the client. [NA]
 * @param[out]   [N/A]
 *
 * @return
 *  ERR_OK: On success \n
 *  TFTPC_ERR_CODE_E: On failure
 *
 * @note
 * \n
 * The behavior of this API is such that if the destination file already exists, it will be overwritten.
 */
u32_t lwip_tftp_get_file_by_filename
(
  u32_t ul_hostaddr,
  u16_t us_tftpservport,
  u8_t uc_tftptransmode,
  s8_t *sz_srcfilename,
  s8_t *sz_destdirpath
);

/* @defgroup TFTP_Interfaces
 * This section contains the TFTP Interfaces
 */
/*
 * Func Name:  lwip_tftp_put_file_by_filename
 */
/**
 * @ingroup TFTP_Interfaces
 *
 * @brief
 * This API reads the contents of the source file on the client system and sends it to the server and
 * server then receives the data and stores it in the specified destination path.
 *
 * @param[in]    ul_hostaddr        Indicates the IP address of Host. This is the TFTP server IP.
 * @param[in]    us_tftpservport    Indicates the TFTP server port. If the value is passed as 0 then the default TFTP
 *                                  PORT 69 is used.
 * @param[in]    uc_tftptransmode   Indicates the file transfer mode, either TRANSFER_MODE_BINARY or
 *                                  TRANSFER_MODE_ASCII.
 * @param[in]    sz_srcfilename     Indicates the source file in the client.
 * @param[in]    sz_destdirpath     Indicates the destination file path on the tftp server.
 *
 * @return
 *  ERR_OK: On success \n
 *  TFTPC_ERR_CODE_E: On failure
 *
 */
u32_t lwip_tftp_put_file_by_filename
(
  u32_t ul_hostaddr,
  u16_t us_tftpservport,
  u8_t uc_tftptransmode,
  s8_t *sz_srcfilename,
  s8_t *sz_destdirpath
);

#ifdef TFTP_TO_RAWMEM
/* @defgroup TFTP_Interfaces
 * This section contains the TFTP Interfaces
 */
/*
 * Func Name:  lwip_tftp_get_file_by_filename_to_rawmem
*/
/**
 * @ingroup TFTP_Interfaces
 *
 * @brief
 * This API gets the source file from the server. It then stores the received file in the target memory
 * on the client system.
 *
 * @param[in]    ul_hostaddr         Indicates the IP address of the Host. This is the TFTP server IP.
 * @param[in]    us_tftpservport     Indicates the TFTP server port. If the value is passed as 0 then the default TFTP
 *                                   PORT 69 is used.
 * @param[in]    uc_tftptransmode    Indicates the File transfer mode, either TRANSFER_MODE_BINARY or
 *                                   TRANSFER_MODE_ASCII.
 * @param[in]    sz_srcfilename      Indicates the Source file in the TFTP server.
 * @param[in]    sz_destmemaddr      Indicates the target memory address in the client.
 * @param[in/out]    ul_filelength   Indicates the target memory address can cache the size of the content,and The
 *                                   real size of the Source file.
 *
 * @return
 *  ERR_OK: On success \n
 *  TFTPC_ERR_CODE_E: On failure
 * @note
 *
 * 1.You must define TFTP_TO_RAWMEM when using this API. \n
 * 2.The behavior of this API is such that if the destination file already exists, it will be overwritten.
 * @endcond
 */
u32_t lwip_tftp_get_file_by_filename_to_rawmem
(
  u32_t ul_hostaddr,
  u16_t us_tftpservport,
  u8_t uc_tftptransmode,
  s8_t *sz_srcfilename,
  s8_t *sz_destmemaddr,
  u32_t *ul_filelength
);
#endif

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* LWIP_TFTP */

#endif /* __LWIP_TFTP_H__ */
