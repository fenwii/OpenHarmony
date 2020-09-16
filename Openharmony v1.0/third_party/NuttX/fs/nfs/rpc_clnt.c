/****************************************************************************
 * fs/nfs/rpc_clnt.c
 *
 *   Copyright (C) 2012-2013, 2018 Gregory Nutt. All rights reserved.
 *   Copyright (C) 2012 Jose Pablo Rojas Vargas. All rights reserved.
 *   Author: Jose Pablo Rojas Vargas <jrojas@nx-engineering.com>
 *           Gregory Nutt <gnutt@nuttx.org>
 *
 * Leveraged from OpenBSD:
 *
 *   Copyright (c) 2004 The Regents of the University of Michigan.
 *   All rights reserved.
 *
 *   Copyright (c) 2004 Weston Andros Adamson <muzzle@umich.edu>.
 *   Copyright (c) 2004 Marius Aamodt Eriksen <marius@umich.edu>.
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *   Copyright (c) 1989, 1991, 1993, 1995 The Regents of the University of
 *   California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by Rick Macklem at
 * The University of Guelph.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer. 2.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution. 3. All advertising
 * materials mentioning features or use of this software must display the
 * following acknowledgement: This product includes software developed by the
 * University of California, Berkeley and its contributors. 4. Neither the
 * name of the University nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <sys/time.h>
#include <stdlib.h>
#include <debug.h>
#include <unistd.h>
#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "xdr_subs.h"
#include "nfs_proto.h"
#include "rpc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Increment RPC statistics */

#ifdef CONFIG_NFS_STATISTICS
#  define rpc_statistics(n) do { rpcstats.n++; } while (0)
#else
#  define rpc_statistics(n)
#endif

#undef  OK
#define OK 0

#define RPCCLNT_FH_LEN                  4
#define RPCCLNT_RECV_BUF_MAX_LEN        64
#define RPCCLNT_CONNECT_MAX_RETRY_TIMES 1024

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Static data, mostly RPC constants in XDR form */

static uint32_t rpc_reply;
static uint32_t rpc_call;
static uint32_t rpc_vers;
static uint32_t rpc_msgdenied;
static uint32_t rpc_mismatch;
static uint32_t rpc_auth_unix;
static uint32_t rpc_msgaccepted;
static uint32_t rpc_autherr;
static uint32_t rpc_auth_null;
static uint32_t nfs_uid, nfs_gid;

/* Global statics for all client instances.  Cleared by NuttX on boot-up. */

#ifdef CONFIG_NFS_STATISTICS
static struct rpcstats rpcstats;
#endif

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int rpcclnt_send(FAR struct rpcclnt *rpc, int procid, int prog,
                        FAR void *call, int reqlen);
static int rpcclnt_receive(FAR struct rpcclnt *rpc, struct sockaddr *aname,
                           int proc, int program, void *reply, size_t resplen);
static int rpcclnt_reply(FAR struct rpcclnt *rpc, int procid, int prog,
                         void *reply, size_t resplen);
static uint32_t rpcclnt_newxid(void);
static void rpcclnt_fmtheader(FAR struct rpc_call_header *ch,
                              uint32_t xid, int procid, int prog, int vers, size_t reqlen);
static int rpcclnt_reconnect(FAR struct rpcclnt *rpc, struct sockaddr *saddr);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rpcclnt_send
 *
 * Description:
 *   This is the nfs send routine.
 *
 * Returned Value:
 *   Returns zero on success or a (positive) errno value on failure.
 *
 ****************************************************************************/

static int rpcclnt_send(FAR struct rpcclnt *rpc, int procid, int prog,
                        FAR void *call, int reqlen)
{
  ssize_t nbytes;
  int ret = OK;

  /* Send the call message
   *
   * On success, psock_sendto returns the number of bytes sent;
   * On failure, it returns -1 with the specific error in errno.
   */

  nbytes = sendto(rpc->rc_so, call, reqlen, 0,
                  rpc->rc_name, sizeof(struct sockaddr));
  if (nbytes < 0)
    {
      /* psock_sendto failed */

      ret = get_errno();
      ferr("ERROR: psock_sendto failed: %d\n", ret);
    }

  return ret;
}

#if (NFS_PROTO_TYPE == NFS_IPPROTO_UDP)
#define CONFIG_NFS_RECV_TIMEOUT 200 /* udp-nfs recv timeout in milli seconds */

/****************************************************************************
 * Name: rpcclnt_receive
 *
 * Description:
 *   Receive a Sun RPC Request/Reply. Only for SOCK_DGRAM
 *
 ****************************************************************************/

static int rpcclnt_receive(FAR struct rpcclnt *rpc, FAR struct sockaddr *aname,
                           int proc, int program, FAR void *reply,
                           size_t resplen)
{
  ssize_t nbytes;
  int error = 0;
  int ret;
  fd_set fdreadset;
  struct timeval timeval = {0};
  socklen_t fromlen = sizeof(struct sockaddr);
  uint32_t xid;
retry:
  FD_ZERO(&fdreadset);
  FD_SET((uint32_t)(rpc->rc_so), &fdreadset);

  timeval.tv_sec = (CONFIG_NFS_RECV_TIMEOUT / 1000);
  timeval.tv_usec = (CONFIG_NFS_RECV_TIMEOUT % 1000) * 1000;

  ret = select(rpc->rc_so + 1, &fdreadset, 0, 0, &timeval);
  if (ret == 0)
    {
      fdbg("ERROR: rpcclnt_receive select nothing\n");
      return EAGAIN;
    }
  else if (ret < 0)
    {
      error = get_errno();
      fdbg("ERROR: rpcclnt_receive select error %d\n", error);
      return error;
    }

  nbytes = recvfrom(rpc->rc_so, reply, resplen, 0, aname, &fromlen);
  if (nbytes <= (ssize_t)sizeof(xid))
    {
      error = get_errno();
      fdbg("ERROR: psock_recvfrom failed: %d\n", error);
      goto retry;
    }

  error = memcpy_s((void *)&xid, sizeof(xid), ((char *)reply + RPC_RMSIZE), sizeof(xid));
  if (error != EOK)
    {
      return ENOBUFS;
    }

  if (fxdr_unsigned(uint32_t, xid) != rpc->xid)
    {
      fdbg("ERROR: psock_recvfrom a wrong packet\n");
      goto retry;
    }

  return error;
}

#elif (NFS_PROTO_TYPE == NFS_IPPROTO_TCP)
#define CONFIG_NFS_RECV_TIMEOUT 5000 /* tcp-nfs recv timeout in milli seconds */

/****************************************************************************
 * Name: rpcclnt_receive
 *
 * Description:
 *   Receive a Sun RPC Request/Reply. Only for SOCK_STREAM
 *
 ****************************************************************************/

static int rpcclnt_receive(FAR struct rpcclnt *rpc, FAR struct sockaddr *aname,
                           int proc, int program, FAR void *reply,
                           size_t resplen)
{
  ssize_t   nbytes;
  size_t    offset = 0;
  size_t    hdrlen = 0;
  uint32_t  total = 0;
  int       error;
  int       ret;
  fd_set    fdreadset;
  struct    timeval timeval = {0};
  socklen_t fromlen = sizeof(struct sockaddr);

  do
    {
      FD_ZERO(&fdreadset);
      FD_SET((uint32_t)(rpc->rc_so), &fdreadset);

      timeval.tv_sec = (CONFIG_NFS_RECV_TIMEOUT / 1000);
      timeval.tv_usec = (CONFIG_NFS_RECV_TIMEOUT % 1000) * 1000;

      ret = select(rpc->rc_so + 1, &fdreadset, 0, 0, &timeval);
      if (ret == 0) /* no reply */
        {
          fdbg("ERROR: rpcclnt_receive select nothing\n");
          return EAGAIN;
        }
      else if (ret < 0) /* select error */
        {
          error = get_errno();
          fdbg("ERROR: rpcclnt_receive select error %d\n", error);
          return error;
        }

      nbytes = recvfrom(rpc->rc_so, (char *)reply + offset, resplen - offset, 0, aname, &fromlen);
      if (nbytes < 0)
        {
          error = get_errno();
          fdbg("ERROR: rpcclnt_receive recvfrom error %d\n", error);
          return error;
        }
      else if (nbytes == 0)
        {
          /* connection closed by peer side */

          fdbg("ERROR: rpcclnt_receive connection closed by peer\n");
          return EIO;
        }
      else
        {
          offset += nbytes;

          /* parse fragment header */

          if (offset == 0 || hdrlen < sizeof(struct rpc_reply_header))
            {
              hdrlen += nbytes;

              /* unlikely */

              if (hdrlen < sizeof(struct rpc_reply_header))
                {
                  continue;
                }

              error = memcpy_s(&total, RPC_RMSIZE, reply, RPC_RMSIZE);
              if (error != EOK)
                {
                  return ENOBUFS;
                }
              total = (fxdr_unsigned(uint32_t, total) & RPC_RM_FLAGMENT_LEN_MASK) + RPC_RMSIZE;
            }
        }
    }
  while (offset < total);

  return 0;
}
#endif

/****************************************************************************
 * Name: rpcclnt_reply
 *
 * Description:
 *   Received the RPC reply on the socket.
 *
 ****************************************************************************/

static int rpcclnt_reply(FAR struct rpcclnt *rpc, int procid, int prog,
                         FAR void *reply, size_t resplen)
{
  int error;

  /* Get the next RPC reply from the socket */

  error = rpcclnt_receive(rpc, rpc->rc_name, procid, prog, reply, resplen);
  if (error != 0)
    {
      ferr("ERROR: rpcclnt_receive returned: %d\n", error);

      /* For UDP, If we failed because of a timeout, then try sending the CALL
       * message again. While for TCP, just return errno.
       */

#if (NFS_PROTO_TYPE == NFS_IPPROTO_UDP)
      if (error == EAGAIN || error == ETIMEDOUT)
        {
          rpc->rc_timeout = true;
        }
#endif
    }

  /* Get the xid and check that it is an RPC replysvr */

  else
    {
      FAR struct rpc_reply_header *replyheader =
        (FAR struct rpc_reply_header *)reply;

      if (replyheader->rp_direction != rpc_reply)
        {
          ferr("ERROR: Different RPC REPLY returned\n");
          rpc_statistics(rpcinvalid);
          error = EPROTO;
        }
    }

  return error;
}

/****************************************************************************
 * Name: rpcclnt_newxid
 *
 * Description:
 *   Get a new (non-zero) xid
 *
 ****************************************************************************/
extern VOID LOS_GetCpuCycle(UINT32 *puwCntHi, UINT32 *puwCntLo);

static uint32_t seed_gen_func(void)
{
  uint32_t seedhsb, seedlsb;
  LOS_GetCpuCycle(&seedhsb, &seedlsb);
  return seedlsb;
}

static uint32_t rpcclnt_newxid(void)
{
  static uint32_t rpcclnt_xid = 0;
  static uint32_t rpcclnt_xid_touched = 0;

  if ((rpcclnt_xid == 0) && (rpcclnt_xid_touched == 0))
    {
      unsigned int seed = seed_gen_func();
      srand(seed);
      rpcclnt_xid = rand();
      rpcclnt_xid_touched = 1;
    }
  else
    {
      int xidp = 0;
      do
        {
          xidp = rand();
        }
      while ((xidp % 256) == 0);

      rpcclnt_xid += xidp;
    }

  return rpcclnt_xid;
}

/****************************************************************************
 * Name: rpcclnt_alivecheck
 *
 * Description:
 *   Check if the connection is alive
 *
 ****************************************************************************/

static int rpcclnt_alivecheck(struct rpcclnt *rpc)
{
    fd_set    rfd;
    int       recvlen;
    char      buf[RPCCLNT_RECV_BUF_MAX_LEN];
    const int bufsize = RPCCLNT_RECV_BUF_MAX_LEN;
    int       ret;
    int       sockfd = rpc->rc_so;
    struct timeval timeout;

    FD_ZERO(&rfd);
    if (sockfd < 0)
      {
        return ENETDOWN;
      }
    FD_SET((uint32_t)sockfd, &rfd);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    /* no wait */

    ret = select(sockfd + 1, &rfd, NULL, NULL, &timeout);
    if (ret < 0)
      {
        fvdbg("ERROR rpc_alivecheck : select failure\n");
        return get_errno();
      }

    if (sockfd)
      {
        if (FD_ISSET((uint32_t)sockfd, &rfd))
          {
            recvlen = recv(sockfd, buf, bufsize, 0);
            if (recvlen <= 0)
              {
                (void)close(rpc->rc_so);
                rpc->rc_so = -1;
              }
            else
              {
                fvdbg("ERROR rpc_alivecheck : recv unsolocit %d data from server\n", recvlen);
                return ENOTSOCK;
              }
          }
      }

    return 0;
}

/****************************************************************************
 * Name: rpcclnt_fmtheader
 *
 * Description:
 *   Format the common part of the call header
 *
 ****************************************************************************/

static void rpcclnt_fmtheader(FAR struct rpc_call_header *ch,
                              uint32_t xid, int prog, int vers, int procid, size_t reqlen)
{
  unsigned int high = 0;
  unsigned int low = 0;
  int          error;

  LOS_GetCpuCycle(&high, &low);

  /* Format the call header */

#if (NFS_PROTO_TYPE == NFS_IPPROTO_TCP)
  ch->rp_recmark        = txdr_unsigned(0x80000000 | (reqlen - RPC_RMSIZE));
#endif
  ch->rp_xid            = txdr_unsigned(xid);
  ch->rp_direction      = rpc_call;
  ch->rp_rpcvers        = rpc_vers;
  ch->rp_prog           = txdr_unsigned(prog);
  ch->rp_vers           = txdr_unsigned(vers);
  ch->rp_proc           = txdr_unsigned(procid);

  ch->rpc_auth.authtype = rpc_auth_unix;
  ch->rpc_auth.authlen  = htonl(sizeof(ch->rpc_auth_unix));
  ch->rpc_auth_unix.stamp = txdr_unsigned((uint32_t)(((UINT64)high << 32) + low));
  ch->rpc_auth_unix.hostname_len = htonl(CONFIG_NFS_MACHINE_NAME_SIZE);
  (void)memset_s(ch->rpc_auth_unix.hostname, sizeof(ch->rpc_auth_unix.hostname),
                 0, sizeof(ch->rpc_auth_unix.hostname));
  error = memcpy_s(ch->rpc_auth_unix.hostname, sizeof(ch->rpc_auth_unix.hostname),
                   CONFIG_NFS_MACHINE_NAME, CONFIG_NFS_MACHINE_NAME_SIZE);
  if (error != EOK)
    {
      return;
    }
  ch->rpc_auth_unix.uid = htonl(nfs_uid);
  ch->rpc_auth_unix.gid = htonl(nfs_gid);
  ch->rpc_auth_unix.gidlist = htonl(1);
  ch->rpc_auth_unix.gidlist_value = nfs_gid;

  /* rpc_verf part (auth_null) */

  ch->rpc_verf.authtype  = rpc_auth_null;
  ch->rpc_verf.authlen   = 0;
}

static int rpcclnt_reconnect(FAR struct rpcclnt *rpc, struct sockaddr *saddr)
{
  int errval;
  int error;

#if (NFS_PROTO_TYPE == NFS_IPPROTO_TCP)
  extern long random(void);
  unsigned short tport = 0;
  unsigned short trycount = 0;
  struct sockaddr_in sock_in;

  rpcclnt_disconnect(rpc);

  error = socket(rpc->rc_name->sa_family, rpc->rc_sotype, IPPROTO_TCP);
  if (error < 0)
    {
      fdbg("ERROR: psock_socket failed: %d", get_errno());
      return -error;
    }

  rpc->rc_so              = error;
  sock_in.sin_family      = AF_INET;
  sock_in.sin_addr.s_addr = INADDR_ANY;
  trycount                = RPCCLNT_CONNECT_MAX_RETRY_TIMES;

  do
    {
      errval = 0;
      trycount--;
      tport = random() % (RPCCONN_MAXPORT - RPCCONN_MINPORT) + RPCCONN_MINPORT;
      sock_in.sin_port = htons(tport);
      error = bind(rpc->rc_so, (struct sockaddr *)&sock_in, sizeof(sock_in));
      if (error < 0)
        {
          errval = get_errno();
          fdbg("ERROR: psock_bind failed: %d\n", errval);
        }
    }
  while (errval == EADDRINUSE && trycount > 0);

  if (error)
    {
      fdbg("ERROR: psock_bind failed: %d, port = %d\n", errval, tport);
      goto bad;
    }
#endif
  error = connect(rpc->rc_so, saddr, sizeof(*saddr));
  if (error < 0)
    {
      errval = get_errno();
      fdbg("ERROR: psock_connect failed [port=%d]: %d\n",
           ntohs(((struct sockaddr_in *)saddr)->sin_port), errval);
      goto bad;
    }
  return error;
bad:
  rpcclnt_disconnect(rpc);
  return errval;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rpcclnt_init
 *
 * Description:
 *   Initialize the RPC client
 *
 ****************************************************************************/

void rpcclnt_init(void)
{
  /* RPC constants how about actually using more than one of these! */

  rpc_reply = txdr_unsigned(RPC_REPLY);
  rpc_vers = txdr_unsigned(RPC_VER2);
  rpc_call = txdr_unsigned(RPC_CALL);
  rpc_msgdenied = txdr_unsigned(RPC_MSGDENIED);
  rpc_msgaccepted = txdr_unsigned(RPC_MSGACCEPTED);
  rpc_mismatch = txdr_unsigned(RPC_MISMATCH);
  rpc_autherr = txdr_unsigned(RPC_AUTHERR);
  rpc_auth_unix = txdr_unsigned(RPCAUTH_UNIX);
  rpc_auth_null = txdr_unsigned(RPCAUTH_NULL);

  finfo("RPC initialized\n");
}

/****************************************************************************
 * Name: rpcclnt_connect
 *
 * Description:
 *   Initialize sockets for a new RPC connection.  We do not free the
 *   sockaddr if an error occurs.
 *
 ****************************************************************************/

int rpcclnt_connect(struct rpcclnt *rpc)
{
  extern long random(void);
  int error;
  struct sockaddr *saddr;
  struct sockaddr_in sin;
  struct sockaddr_in *sa;

  union
  {
    struct rpc_call_pmap  sdata;
    struct rpc_call_mount mountd;
  } request;

  union
  {
    struct rpc_reply_pmap  rdata;
    struct rpc_reply_mount mdata;
  } response;

  uint16_t trycount;
  uint16_t tport = 0;
  int errval;

  finfo("Connecting\n");

  /* Create the socket */

  saddr = rpc->rc_name;

  /* Create an instance of the socket state structure */

  error = socket(saddr->sa_family, rpc->rc_sotype, NFS_PROTOTYPE);
  if (error < 0)
    {
      fdbg("ERROR: psock_socket failed: %d", get_errno());
      return -error;
    }

  rpc->rc_so              = error;
  sin.sin_family      = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  trycount                = RPCCLNT_CONNECT_MAX_RETRY_TIMES;

  do
    {
      errval = 0;
      trycount--;
      tport = random() % (RPCCONN_MAXPORT - RPCCONN_MINPORT) + RPCCONN_MINPORT;
      sin.sin_port = htons(tport);

      error = bind(rpc->rc_so, (struct sockaddr *)&sin, sizeof(sin));
      if (error < 0)
        {
          errval = get_errno();
          ferr("ERROR: psock_bind failed: %d\n", errval);
        }
    }
  while (errval == EADDRINUSE && trycount > 0);

  if (error)
    {
      ferr("ERROR: psock_bind failed: %d, port = %d\n", errval, tport);
      goto bad;
    }

  /* Protocols that do not require connections could be optionally left
   * unconnected.  That would allow servers to reply from a port other than
   * the NFS_PORT.
   */

  error = connect(rpc->rc_so, saddr, sizeof(*saddr));
  if (error < 0)
    {
      error = get_errno();
      ferr("ERROR: psock_connect to PMAP port failed: %d", error);
      goto bad;
    }

  /* Do the RPC to get a dynamic bounding with the server using ppmap.
   * Get port number for MOUNTD.
   */

  request.sdata.pmap.prog = txdr_unsigned(RPCPROG_MNT);
  request.sdata.pmap.vers = txdr_unsigned(RPCMNT_VER3);
  request.sdata.pmap.proc = txdr_unsigned(NFS_PROTOTYPE);
  request.sdata.pmap.port = 0;

  error = rpcclnt_request(rpc, PMAPPROC_GETPORT, PMAPPROG, PMAPVERS,
                          (FAR void *)&request.sdata, sizeof(struct call_args_pmap),
                          (FAR void *)&response.rdata, sizeof(struct rpc_reply_pmap));
  if (error != 0)
    {
      ferr("ERROR: rpcclnt_request failed: %d\n", error);
      goto bad;
    }

  sa = (FAR struct sockaddr_in *)saddr;
  sa->sin_port = htons(fxdr_unsigned(uint32_t, response.rdata.pmap.port));

  error = rpcclnt_reconnect(rpc, saddr);
  if (error != 0)
    {
      fdbg("ERROR: rpcclnt_reconnect failed: %d\n", error);
      goto bad;
    }

  /* Do RPC to mountd. */

  error = memset_s(&request, sizeof(request), 0, sizeof(request));
  if (error != EOK)
    {
      error = ENOBUFS;
      goto bad;
    }
  error = strncpy_s(request.mountd.mount.rpath, sizeof(request.mountd.mount.rpath),
                    rpc->rc_path, RPC_RPATH_MAXSIZE - 1);
  if (error != EOK)
    {
      error = ENOBUFS;
      goto bad;
    }
  request.mountd.mount.len =  txdr_unsigned(sizeof(request.mountd.mount.rpath));

  error = rpcclnt_request(rpc, RPCMNT_MOUNT, RPCPROG_MNT, RPCMNT_VER3,
                          (FAR void *)&request.mountd,
                          sizeof(struct call_args_mount),
                          (FAR void *)&response.mdata,
                          sizeof(struct rpc_reply_mount));
  if (error != 0)
    {
      ferr("ERROR: rpcclnt_request failed: %d\n", error);
      goto bad;
    }

  error = fxdr_unsigned(uint32_t, response.mdata.mount.status);
  if (error != 0)
    {
      ferr("ERROR: Bad mount status: %d\n", error);
      goto bad;
    }

  rpc->rc_fhsize = fxdr_unsigned(uint32_t, response.mdata.mount.fhandle.length);
  memcpy(&rpc->rc_fh, &response.mdata.mount.fhandle.handle, rpc->rc_fhsize);

  /* Do the RPC to get a dynamic bounding with the server using PMAP.
   * NFS port in the socket.
   */

  sa->sin_port = htons(PMAPPORT);

  error = rpcclnt_reconnect(rpc, saddr);
  if (error != 0)
    {
      fdbg("ERROR: rpcclnt_reconnect failed: %d\n", error);
      goto bad;
    }

  request.sdata.pmap.prog = txdr_unsigned(NFS_PROG);
  request.sdata.pmap.vers = txdr_unsigned(NFS_VER3);
  request.sdata.pmap.proc = txdr_unsigned(NFS_PROTOTYPE);
  request.sdata.pmap.port = 0;

  error = rpcclnt_request(rpc, PMAPPROC_GETPORT, PMAPPROG, PMAPVERS,
                          (FAR void *)&request.sdata,
                          sizeof(struct call_args_pmap),
                          (FAR void *)&response.rdata,
                          sizeof(struct rpc_reply_pmap));
  if (error != 0)
    {
      ferr("ERROR: rpcclnt_request failed: %d\n", error);
      goto bad;
    }

  sa->sin_port = htons(fxdr_unsigned(uint32_t, response.rdata.pmap.port));

  error = rpcclnt_reconnect(rpc, saddr);
  if (error != 0)
    {
      fdbg("ERROR: rpcclnt_reconnect failed: %d\n", error);
      goto bad;
    }

  return OK;

bad:
  rpcclnt_disconnect(rpc);
  return error;
}

/****************************************************************************
 * Name: rpcclnt_disconnect
 *
 * Description:
 *   Disconnect from the NFS server.
 *
 ****************************************************************************/

void rpcclnt_disconnect(struct rpcclnt *rpc)
{
  if (rpc->rc_so != -1)
    {
      (void)lwip_close(rpc->rc_so);
      rpc->rc_so = -1;
    }
}

/****************************************************************************
 * Name: rpcclnt_umount
 *
 * Description:
 *   Un-mount the NFS file system.
 *
 ****************************************************************************/

int rpcclnt_umount(struct rpcclnt *rpc)
{
  struct sockaddr *saddr;
  struct sockaddr_in *sa;

  union
  {
    struct rpc_call_pmap   sdata;
    struct rpc_call_umount mountd;
  } request;

  union
  {
    struct rpc_reply_pmap   rdata;
    struct rpc_reply_umount mdata;
  } response;

  int error;

  saddr = rpc->rc_name;
  sa = (FAR struct sockaddr_in *)saddr;

  /* Do the RPC to get a dynamic bounding with the server using ppmap.
   * Get port number for MOUNTD.
   */

  sa->sin_port = htons(PMAPPORT);

  error = rpcclnt_reconnect(rpc, saddr);
  if (error != 0)
    {
      fdbg("ERROR: rpcclnt_reconnect failed: %d\n", error);
      goto bad;
    }

  request.sdata.pmap.prog = txdr_unsigned(RPCPROG_MNT);
  request.sdata.pmap.vers = txdr_unsigned(RPCMNT_VER3);
  request.sdata.pmap.proc = txdr_unsigned(NFS_PROTOTYPE);
  request.sdata.pmap.port = 0;

  error = rpcclnt_request(rpc, PMAPPROC_GETPORT, PMAPPROG, PMAPVERS,
                          (FAR void *)&request.sdata,
                          sizeof(struct call_args_pmap),
                          (FAR void *)&response.rdata,
                          sizeof(struct rpc_reply_pmap));
  if (error != 0)
    {
      ferr("ERROR: rpcclnt_request failed: %d\n", error);
      goto bad;
    }

  sa->sin_port = htons(fxdr_unsigned(uint32_t, response.rdata.pmap.port));

  error = rpcclnt_reconnect(rpc, saddr);
  if (error != 0)
    {
      fdbg("ERROR: rpcclnt_reconnect failed: %d\n", error);
      goto bad;
    }

  /* Do RPC to umountd. */

  (void)strncpy_s(request.mountd.umount.rpath, sizeof(request.mountd.umount.rpath),
                  rpc->rc_path, sizeof(request.mountd.umount.rpath) - 1);
  request.mountd.umount.rpath[sizeof(request.mountd.umount.rpath) - 1] = 0;
  request.mountd.umount.len =  txdr_unsigned(sizeof(request.mountd.umount.rpath));

  error = rpcclnt_request(rpc, RPCMNT_UMOUNT, RPCPROG_MNT, RPCMNT_VER3,
                          (FAR void *)&request.mountd,
                          sizeof(struct call_args_umount),
                          (FAR void *)&response.mdata,
                          sizeof(struct rpc_reply_umount));
  if (error != 0)
    {
      ferr("ERROR: rpcclnt_request failed: %d\n", error);
      goto bad;
    }

  return OK;

bad:

  /* No need to close the socket here, if umount failed. user has to call nfs_unbind again */

  return error;
}

/****************************************************************************
 * Name: rpcclnt_request
 *
 * Description:
 *   Perform the RPC request.  Logic formats the RPC CALL message and calls
 *   rpcclnt_send to send the RPC CALL message.  It then calls rpcclnt_reply()
 *   to get the response.  It may attempt to re-send the CALL message on
 *   certain errors.
 *
 *   On successful receipt, it verifies the RPC level of the returned values.
 *   (There may still be be NFS layer errors that will be deted by calling
 *   logic).
 *
 ****************************************************************************/

int rpcclnt_request(FAR struct rpcclnt *rpc, int procnum, int prog,
                    int version, FAR void *request, size_t reqlen,
                    FAR void *response, size_t resplen)
{
  struct rpc_reply_header *replymsg;
  uint32_t tmp;
#if (NFS_PROTO_TYPE == NFS_IPPROTO_UDP)
  int retries;
#endif
  int error = 0;

  /* Get a new (non-zero) xid */

  rpc->xid = rpcclnt_newxid();

  /* Get the full size of the message (the size of variable data plus the size of
   * the messages header).
   */

  reqlen += sizeof(struct rpc_call_header);

  /* Initialize the RPC header fields */

  rpcclnt_fmtheader((FAR struct rpc_call_header *)request,
                    rpc->xid, prog, version, procnum, reqlen);

  /* Send the RPC call messsages and receive the RPC response. For UDP-RPC, A limited
   * number of re-tries will be attempted, but only for the case of response
   * timeouts. While for TCP-RPC, no retry attempted.
   */

#if (NFS_PROTO_TYPE == NFS_IPPROTO_UDP)
  retries = 0;
  do
    {
      /* Do the client side RPC. */

      rpc_statistics(rpcrequests);
      rpc->rc_timeout = false;

      /* Send the RPC CALL message */

      error = rpcclnt_send(rpc, procnum, prog, request, reqlen);
      if (error != OK)
        {
          finfo("ERROR rpcclnt_send failed: %d\n", error);
        }

      /* Wait for the reply from our send */

      else
        {
          error = rpcclnt_reply(rpc, procnum, prog, response, resplen);
          if (error != OK)
            {
              finfo("ERROR rpcclnt_reply failed: %d\n", error);
            }
        }

      retries++;
    }
  while (rpc->rc_timeout && retries <= rpc->rc_retry);

  if (error != OK)
    {
      ferr("ERROR: RPC failed: %d\n", error);
      return error;
    }

#else

  /* check tcp connection alive or not as server would close connection if long time no data transfer */

  if (rpc->rc_so != -1)
    {
      error = rpcclnt_alivecheck(rpc);
      if (error != OK)
        {
          fvdbg("ERROR rpc_alivecheck failed: %d\n", error);
          return error;
        }
    }

  /* reconnect due to previous connection down */

  if (rpc->rc_so == -1)
    {
      error = rpcclnt_reconnect(rpc, rpc->rc_name);
      if (error != OK)
        {
          fvdbg("ERROR rpcclnt_send failed: %d\n", error);
          return error;
        }
    }

  rpc_statistics(rpcrequests);

  /* Send the RPC CALL message */

  error = rpcclnt_send(rpc, procnum, prog, request, reqlen);
  if (error != OK)
    {
      rpcclnt_disconnect(rpc);
      fvdbg("ERROR rpcclnt_send failed: %d\n", error);
      return error;
    }

  /* Wait for the reply from our send */

  error = rpcclnt_reply(rpc, procnum, prog, response, resplen);
  if (error != OK)
    {
      rpcclnt_disconnect(rpc);
      fvdbg("ERROR rpcclnt_reply failed: %d\n", error);
      return error;
    }

#endif

  /* Break down the RPC header and check if it is OK */

  replymsg = (FAR struct rpc_reply_header *)response;

  tmp = fxdr_unsigned(uint32_t, replymsg->type);
  if (tmp == RPC_MSGDENIED)
    {
      tmp = fxdr_unsigned(uint32_t, replymsg->status);
      switch (tmp)
        {
        case RPC_MISMATCH:
          ferr("ERROR: RPC_MSGDENIED: RPC_MISMATCH error\n");
          return EOPNOTSUPP;

        case RPC_AUTHERR:
          ferr("ERROR: RPC_MSGDENIED: RPC_AUTHERR error\n");
          return EACCES;

        default:
          return EOPNOTSUPP;
        }
    }
  else if (tmp != RPC_MSGACCEPTED)
    {
      return EOPNOTSUPP;
    }

  tmp = fxdr_unsigned(uint32_t, replymsg->status);
  if (tmp == RPC_SUCCESS)
    {
      finfo("RPC_SUCCESS\n");
    }
  else if (tmp == RPC_PROGMISMATCH)
    {
      ferr("ERROR: RPC_MSGACCEPTED: RPC_PROGMISMATCH error\n");
      return EOPNOTSUPP;
    }
  else if (tmp > 5)
    {
      ferr("ERROR: Unsupported RPC type: %d\n", tmp);
      return EOPNOTSUPP;
    }

  return OK;
}

void rpcclnt_setuidgid(uint32_t uid, uint32_t gid)
{
  nfs_uid = uid;
  nfs_gid = gid;
}
