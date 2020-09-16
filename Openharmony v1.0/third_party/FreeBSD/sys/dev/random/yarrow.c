/*-
 * Copyright (c) 2000-2015 Mark R V Murray
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: releng/11.4/sys/dev/random/yarrow.c 298923 2016-05-02 14:35:57Z pfg $");

#include <sys/param.h>
#ifdef _KERNEL
#include <sys/malloc.h>
#include <sys/mutex.h>
#include <sys/systm.h>


#include <crypto/rijndael/rijndael-api-fst.h>
#include <crypto/sha2/sha256.h>

#include <dev/random/hash.h>
#include <dev/random/randomdev.h>
#include <dev/random/random_harvestq.h>
#include <dev/random/uint128.h>
#include <dev/random/yarrow.h>
#else /* !_KERNEL */
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mutex.h>

#include "unit_test.h"

#include <crypto/rijndael/rijndael-api-fst.h>
#include <crypto/sha2/sha256.h>

#include <dev/random/hash.h>
#include <dev/random/randomdev.h>
#include <dev/random/uint128.h>
#include <dev/random/yarrow.h>
#endif /* _KERNEL */

#define RANDOM_ITERATE_NUMBER   16

#define	RANDOM_YARROW_TIMEBIN	16	/* max value for Pt/t */

#define	RANDOM_YARROW_FAST	0
#define	RANDOM_YARROW_SLOW	1
#define	RANDOM_YARROW_NPOOLS	2

/* This algorithm (and code) presumes that RANDOM_KEYSIZE is twice as large as RANDOM_BLOCKSIZE */
CTASSERT(RANDOM_BLOCKSIZE == sizeof(uint128_t));
CTASSERT(RANDOM_KEYSIZE == 2*RANDOM_BLOCKSIZE);

#ifndef __LITEOS__
/* Probes for dtrace(1) */
SDT_PROVIDER_DECLARE(random);
SDT_PROVIDER_DEFINE(random);
SDT_PROBE_DEFINE3(random, yarrow, event_processor, debug, "boolean", "u_int", "struct ys_pool *");
#endif

/*
 * This is the beastie that needs protecting. It contains all of the
 * state that we are excited about. Exactly one is instantiated.
 */
static struct yarrow_state {
	uint128_t ys_counter;		/* C */
	struct randomdev_key ys_key;	/* K */
	u_int ys_gengateinterval;	/* Pg */
	u_int ys_bins;			/* Pt/t */
	u_int ys_outputblocks;		/* count output blocks for gates */
	u_int ys_slowoverthresh;	/* slow pool overthreshhold reseed count */
	struct ys_pool {
		u_int ysp_source_bits[ENTROPYSOURCE];	/* estimated bits of entropy per source */
		u_int ysp_thresh;	/* pool reseed threshold */
		struct randomdev_hash ysp_hash;	/* accumulated entropy */
	} ys_pool[RANDOM_YARROW_NPOOLS];/* pool[0] is fast, pool[1] is slow */
	bool ys_seeded;
	/* Reseed lock */
	mtx_t ys_mtx;
} yarrow_state;

#ifdef _KERNEL
static struct sysctl_ctx_list random_clist;
RANDOM_CHECK_UINT(gengateinterval, 4, 64);
RANDOM_CHECK_UINT(bins, RANDOM_YARROW_NPOOLS, 16);
RANDOM_CHECK_UINT(fastthresh, (RANDOM_BLOCKSIZE*8)/4, (RANDOM_BLOCKSIZE*8)); /* Bit counts */
RANDOM_CHECK_UINT(slowthresh, (RANDOM_BLOCKSIZE*8)/4, (RANDOM_BLOCKSIZE*8)); /* Bit counts */
RANDOM_CHECK_UINT(slowoverthresh, 1, 5);
#endif /* _KERNEL */

static void random_yarrow_pre_read(void);
static void random_yarrow_read(uint8_t *, u_int);
static bool random_yarrow_seeded(void);
static void random_yarrow_process_event(struct harvest_event *);
static void random_yarrow_init_alg(void *);
static void random_yarrow_deinit_alg(void *);

static void random_yarrow_reseed_internal(u_int);

struct random_algorithm random_alg_context = {
	.ra_ident = "Yarrow",
	.ra_init_alg = random_yarrow_init_alg,
	.ra_deinit_alg = random_yarrow_deinit_alg,
	.ra_pre_read = random_yarrow_pre_read,
	.ra_read = random_yarrow_read,
	.ra_seeded = random_yarrow_seeded,
	.ra_event_processor = random_yarrow_process_event,
	.ra_poolcount = RANDOM_YARROW_NPOOLS,
};

/* ARGSUSED */
static void
random_yarrow_init_alg(void *unused __unused)
{
	int i, j;
#ifdef _KERNEL
	struct sysctl_oid *random_yarrow_o;
#endif

	RANDOM_RESEED_INIT_LOCK();
	/* Start unseeded, therefore blocked. */
	yarrow_state.ys_seeded = false;
#ifdef _KERNEL
	/*
	 * Yarrow parameters. Do not adjust these unless you have
	 * have a very good clue about what they do!
	 */
	random_yarrow_o = SYSCTL_ADD_NODE(&random_clist,
		SYSCTL_STATIC_CHILDREN(_kern_random),
		OID_AUTO, "yarrow", CTLFLAG_RW, 0,
		"Yarrow Parameters");
	SYSCTL_ADD_PROC(&random_clist,
		SYSCTL_CHILDREN(random_yarrow_o), OID_AUTO,
		"gengateinterval", CTLTYPE_UINT | CTLFLAG_RWTUN,
		&yarrow_state.ys_gengateinterval, 0,
		random_check_uint_gengateinterval, "UI",
		"Generation gate interval");
	SYSCTL_ADD_PROC(&random_clist,
		SYSCTL_CHILDREN(random_yarrow_o), OID_AUTO,
		"bins", CTLTYPE_UINT | CTLFLAG_RWTUN,
		&yarrow_state.ys_bins, 0,
		random_check_uint_bins, "UI",
		"Execution time tuner");
	SYSCTL_ADD_PROC(&random_clist,
		SYSCTL_CHILDREN(random_yarrow_o), OID_AUTO,
		"fastthresh", CTLTYPE_UINT | CTLFLAG_RWTUN,
		&yarrow_state.ys_pool[0].ysp_thresh, 0,
		random_check_uint_fastthresh, "UI",
		"Fast reseed threshold");
	SYSCTL_ADD_PROC(&random_clist,
		SYSCTL_CHILDREN(random_yarrow_o), OID_AUTO,
		"slowthresh", CTLTYPE_UINT | CTLFLAG_RWTUN,
		&yarrow_state.ys_pool[1].ysp_thresh, 0,
		random_check_uint_slowthresh, "UI",
		"Slow reseed threshold");
	SYSCTL_ADD_PROC(&random_clist,
		SYSCTL_CHILDREN(random_yarrow_o), OID_AUTO,
		"slowoverthresh", CTLTYPE_UINT | CTLFLAG_RWTUN,
		&yarrow_state.ys_slowoverthresh, 0,
		random_check_uint_slowoverthresh, "UI",
		"Slow over-threshold reseed");
#endif /* _KERNEL */
	yarrow_state.ys_gengateinterval = 10;
	yarrow_state.ys_bins = 10;
	yarrow_state.ys_pool[RANDOM_YARROW_FAST].ysp_thresh = (3*(RANDOM_BLOCKSIZE*8))/4;
	yarrow_state.ys_pool[RANDOM_YARROW_SLOW].ysp_thresh = (RANDOM_BLOCKSIZE*8);
	yarrow_state.ys_slowoverthresh = 2;
	/* Ensure that the first time we read, we are gated. */
	yarrow_state.ys_outputblocks = yarrow_state.ys_gengateinterval;
	/* Initialise the fast and slow entropy pools */
	for (i = RANDOM_YARROW_FAST; i <= RANDOM_YARROW_SLOW; i++) {
		randomdev_hash_init(&yarrow_state.ys_pool[i].ysp_hash);
		for (j = RANDOM_START; j < ENTROPYSOURCE; j++)
			yarrow_state.ys_pool[i].ysp_source_bits[j] = 0;
	}
	/* Clear the counter */
	yarrow_state.ys_counter = UINT128_ZERO;
}

/* ARGSUSED */
static void
random_yarrow_deinit_alg(void *unused __unused)
{

	RANDOM_RESEED_DEINIT_LOCK();
	explicit_bzero(&yarrow_state, sizeof(yarrow_state));
#ifdef _KERNEL
	sysctl_ctx_free(&random_clist);
#endif
}

/* Process a single stochastic event off the harvest queue */
static void
random_yarrow_process_event(struct harvest_event *event)
{
	u_int pl, overthreshhold[RANDOM_YARROW_NPOOLS];
	enum random_entropy_source src;

	RANDOM_RESEED_LOCK();
	/*
	 * Accumulate the event into the appropriate pool
	 * where each event carries the destination information.
	 * We lock against pool state modification which can happen
	 * during accumulation/reseeding and reading/regating
	 */
	pl = event->he_destination % RANDOM_YARROW_NPOOLS;
	randomdev_hash_iterate(&yarrow_state.ys_pool[pl].ysp_hash, event, sizeof(*event));
	if((event->he_source < ENTROPYSOURCE)&&(pl < RANDOM_YARROW_NPOOLS)) {
	    yarrow_state.ys_pool[pl].ysp_source_bits[event->he_source] += event->he_bits;
	}
	/* Count the over-threshold sources in each pool */
	for (pl = RANDOM_YARROW_FAST; (pl <= RANDOM_YARROW_SLOW) && (pl < RANDOM_YARROW_NPOOLS); pl++) {
		overthreshhold[pl] = 0;
		for (src = RANDOM_START; src < ENTROPYSOURCE; src++) {
			if (yarrow_state.ys_pool[pl].ysp_source_bits[src] > yarrow_state.ys_pool[pl].ysp_thresh)
				overthreshhold[pl]++;
		}
	}
	/*
	 * If enough slow sources are over threshold, then slow reseed
	 * else if any fast source over threshold, then fast reseed.
	 */
	if (overthreshhold[RANDOM_YARROW_SLOW] >= yarrow_state.ys_slowoverthresh)
		random_yarrow_reseed_internal(RANDOM_YARROW_SLOW);
	else if (overthreshhold[RANDOM_YARROW_FAST] > 0 && yarrow_state.ys_seeded)
		random_yarrow_reseed_internal(RANDOM_YARROW_FAST);
	explicit_bzero(event, sizeof(*event));
	RANDOM_RESEED_UNLOCK();
}

static void
random_yarrow_reseed_internal(u_int fastslow)
{
	/*
	 * Interrupt-context stack is a limited resource; make large
	 * structures static.
	 */
	static uint8_t v[RANDOM_YARROW_TIMEBIN][RANDOM_KEYSIZE];	/* v[i] */
	static uint128_t temp;
	static struct randomdev_hash context;
	u_int i;
	enum random_entropy_source j;

	KASSERT(yarrow_state.ys_pool[RANDOM_YARROW_FAST].ysp_thresh > 0, ("random: Yarrow fast threshold = 0"));
	KASSERT(yarrow_state.ys_pool[RANDOM_YARROW_SLOW].ysp_thresh > 0, ("random: Yarrow slow threshold = 0"));
	RANDOM_RESEED_ASSERT_LOCK_OWNED();
#ifndef __LITEOS__
	SDT_PROBE3(random, yarrow, event_processor, debug, yarrow_state.ys_seeded, yarrow_state.ys_slowoverthresh, yarrow_state.ys_pool);
#endif
	/* 1. Hash the accumulated entropy into v[0] */
	randomdev_hash_init(&context);
	/* Feed the slow pool hash in if slow */
	if (fastslow == RANDOM_YARROW_SLOW) {
		randomdev_hash_finish(&yarrow_state.ys_pool[RANDOM_YARROW_SLOW].ysp_hash, &temp);
		randomdev_hash_iterate(&context, &temp, sizeof(temp));
	}
	randomdev_hash_finish(&yarrow_state.ys_pool[RANDOM_YARROW_FAST].ysp_hash, &temp);
	randomdev_hash_iterate(&context, &temp, sizeof(temp));
	randomdev_hash_finish(&context, v[0]);
	/*-
	 * 2. Compute hash values for all v. _Supposed_ to be computationally
	 *    intensive.
	 */
	if (yarrow_state.ys_bins > RANDOM_YARROW_TIMEBIN)
		yarrow_state.ys_bins = RANDOM_YARROW_TIMEBIN;
	for (i = 1; i < yarrow_state.ys_bins; i++) {
		randomdev_hash_init(&context);
		/* v[i] #= h(v[i - 1]) */
		randomdev_hash_iterate(&context, v[i - 1], RANDOM_KEYSIZE);
		/* v[i] #= h(v[0]) */
		randomdev_hash_iterate(&context, v[0], RANDOM_KEYSIZE);
		/* v[i] #= h(i) */
		randomdev_hash_iterate(&context, &i, sizeof(i));
		/* Return the hashval */
		randomdev_hash_finish(&context, v[i]);
	}
	/*-
	 * 3. Compute a new key; h' is the identity function here;
	 *    it is not being ignored!
	 */
	randomdev_hash_init(&context);
	randomdev_hash_iterate(&context, &yarrow_state.ys_key, RANDOM_KEYSIZE);
	for (i = 1; i < yarrow_state.ys_bins; i++)
		randomdev_hash_iterate(&context, v[i], RANDOM_KEYSIZE);
	randomdev_hash_finish(&context, &temp);
	randomdev_encrypt_init(&yarrow_state.ys_key, &temp);
	/* 4. Recompute the counter */
	yarrow_state.ys_counter = UINT128_ZERO;
	randomdev_encrypt(&yarrow_state.ys_key, &yarrow_state.ys_counter, &temp, RANDOM_BLOCKSIZE);
	yarrow_state.ys_counter = temp;
	/* 5. Reset entropy estimate accumulators to zero */
	for (i = 0; i <= fastslow; i++)
		for (j = RANDOM_START; j < ENTROPYSOURCE; j++)
			yarrow_state.ys_pool[i].ysp_source_bits[j] = 0;
	/* 6. Wipe memory of intermediate values */
	explicit_bzero(v, sizeof(v));
	explicit_bzero(&temp, sizeof(temp));
	explicit_bzero(&context, sizeof(context));
/* Not defined so writes ain't gonna happen. Kept for documenting. */
#ifdef RANDOM_RWFILE_WRITE_IS_OK
	/*-
         * 7. Dump to seed file.
	 * This pseudo-code is documentation. Please leave it alone.
	 */
	seed_file = "<some file>";
	error = randomdev_write_file(seed_file, <generated entropy>, PAGE_SIZE);
	if (error == 0)
		printf("random: entropy seed file '%s' successfully written\n", seed_file);
#endif
	/* Unblock the device if it was blocked due to being unseeded */
	if (!yarrow_state.ys_seeded) {
		yarrow_state.ys_seeded = true;
		#ifndef __LITEOS__
		randomdev_unblock();
		#endif
	}
}

static __inline void
random_yarrow_generator_gate(void)
{
	u_int i;
	uint8_t temp[RANDOM_KEYSIZE];

	RANDOM_RESEED_ASSERT_LOCK_OWNED();
	uint128_increment(&yarrow_state.ys_counter);
	for (i = 0; i < RANDOM_KEYSIZE; i += RANDOM_BLOCKSIZE)
		randomdev_encrypt(&yarrow_state.ys_key, &yarrow_state.ys_counter, temp + i, RANDOM_BLOCKSIZE);
	randomdev_encrypt_init(&yarrow_state.ys_key, temp);
	explicit_bzero(temp, sizeof(temp));
}

/*-
 * Used to return processed entropy from the PRNG. There is a pre_read
 * required to be present (but it can be a stub) in order to allow
 * specific actions at the begin of the read.
 * Yarrow does its reseeding in its own thread; _pre_read() is not used
 * by Yarrow but must be kept for completeness.
 */
void
random_yarrow_pre_read(void)
{
}

/*-
 * Main read from Yarrow.
 * The supplied buf MUST be a multiple (>=0) of RANDOM_BLOCKSIZE in size.
 * Lots of code presumes this for efficiency, both here and in other
 * routines. You are NOT allowed to break this!
 */
void
random_yarrow_read(uint8_t *buf, u_int bytecount)
{
	u_int blockcount, i;

	KASSERT((bytecount % RANDOM_BLOCKSIZE) == 0, ("%s(): bytecount (= %d) must be a multiple of %d", __func__, bytecount, RANDOM_BLOCKSIZE ));
	RANDOM_RESEED_LOCK();
	blockcount = howmany(bytecount, RANDOM_BLOCKSIZE);
	for (i = 0; i < blockcount; i++) {
		if (yarrow_state.ys_outputblocks++ >= yarrow_state.ys_gengateinterval) {
			random_yarrow_generator_gate();
			yarrow_state.ys_outputblocks = 0;
		}
		uint128_increment(&yarrow_state.ys_counter);
		randomdev_encrypt(&yarrow_state.ys_key, &yarrow_state.ys_counter, buf, RANDOM_BLOCKSIZE);
		buf += RANDOM_BLOCKSIZE;
	}
	RANDOM_RESEED_UNLOCK();
}

bool
random_yarrow_seeded(void)
{

	return (yarrow_state.ys_seeded);
}

#if defined(LOSCFG_HW_RANDOM_ENABLE)
void
random_hw_getnumber(char *pbuf, size_t len)
{
	extern void HiRandomHwInit(void);
	extern void HiRandomHwDeinit(void);
	extern int HiRandomHwGetNumber(char *buffer, size_t buflen);
	size_t wanted = 0;
	int i;

	HiRandomHwInit();

	for (i = 0; i < len; ) {
		wanted = len - i;
		ssize_t ret = HiRandomHwGetNumber((char *)pbuf + i, wanted);

		if (ret != 0) {
			HiRandomHwDeinit();
			errno = EIO;
		}

		i += wanted;
	}

	HiRandomHwDeinit();
}
#endif

#if defined(LOSCFG_HW_RANDOM_ENABLE) || defined(LOSCFG_DRIVERS_RANDOM)
void
run_harvester_once(const char *pentropy, size_t num)
{
	struct harvest_event e;
	uint64_t data;
 	errno_t err = EOK;

	if (pentropy == NULL) {
		return;
	}
	e.he_somecounter = num;
	e.he_size = sizeof(e.he_entropy);
	err = memcpy_s(e.he_entropy, e.he_size, pentropy, e.he_size);
	if(err != EOK){
		return;
	}
	err = memcpy_s(&data, sizeof(uint64_t), e.he_entropy, sizeof(uint64_t));
	if(err != EOK){
		return;
	}
	e.he_bits = data % 64 + 60; /* calculate bits */
	e.he_destination = num;
	e.he_source = (num + 3) % 3; /* calculate source */
	e.he_next = NULL;
	random_alg_context.ra_event_processor(&e);
}
#endif

void
run_harvester_iterate(void *arg __unused)
{
#if defined(LOSCFG_HW_RANDOM_ENABLE)
	int i;
	char buf[8]; /* store random numbers */
	for (i = 0; i < RANDOM_ITERATE_NUMBER; i++) {
		random_hw_getnumber(buf, sizeof(buf));
		run_harvester_once(buf, i);
		(void)memset_s(buf, sizeof(buf), 0, sizeof(buf));
	}
#elif defined(LOSCFG_DRIVERS_RANDOM)
	extern LITE_OS_SEC_TEXT_MINOR UINT64 OsGetCpuCycle(VOID);
	int rdata1, rdata2;
	char buf[8]; /* store random numbers */
	int i;
	for (i = 0; i < RANDOM_ITERATE_NUMBER; i++) {
		srand((unsigned int)OsGetCpuCycle());
		rdata1 = (int)rand();
		rdata2 = (int)rand();
		(void)memcpy_s(buf, sizeof(int), &rdata1, sizeof(int));
		(void)memcpy_s(buf + 4, sizeof(int), &rdata2, sizeof(int));
		run_harvester_once(buf, i);
	}
	(void)memset_s(buf, sizeof(buf), 0, sizeof(buf));
#endif
}
