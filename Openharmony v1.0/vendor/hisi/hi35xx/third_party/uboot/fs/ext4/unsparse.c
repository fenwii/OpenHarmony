#include <common.h>
#include <command.h>
#include <div64.h>
#include <mmc.h>
#include <image-sparse.h>

/******************************************************************************/
#ifdef CONFIG_CMD_UFS
#include <ufs.h>
#define UFS_BLKSIZE_SHIFT  (12)
#endif

#define EMMC_BLKSIZE_SHIFT           (9)
#define SZ_1M_SHIFT                  (20)

/* #define DEBUG_EXT4 */

/******************************************************************************/
void print_header_info(sparse_header_t *header)
{
#ifdef DEBUG_EXT4
	printf("sparse header info:\n");
	printf("magic: 0x%x\n", header->magic);
	printf("major_version: 0x%x\n", header->major_version);
	printf("minor_version: 0x%x\n", header->minor_version);
	printf("file_hdr_sz: %d\n", header->file_hdr_sz);
	printf("chunk_hdr_sz: %d\n", header->chunk_hdr_sz);
	printf("blk_sz: %d\n", header->blk_sz);
	printf("total_blks: %d\n", header->total_blks);
	printf("total_chunks: %d\n", header->total_chunks);
	printf("image_checksum: %d\n", header->image_checksum);
#endif
}

/******************************************************************************/
void print_chunk_info(chunk_header_t *chunk)
{
#ifdef DEBUG_EXT4
	printf("chunk header info:\n");
	printf("chunk_type: 0x%x\n", chunk->chunk_type);
	printf("chunk_sz: 0x%d\n", chunk->chunk_sz);
	printf("total_sz: 0x%d\n", chunk->total_sz);
#endif
}

int get_unspare_header_info(const u8 *pbuf,sparse_header_t *sparse_header)
{
	sparse_header_t *header = NULL;
	header = memcpy(sparse_header, pbuf,sizeof(sparse_header_t));

	if (!is_sparse_image(sparse_header)) {
		printf("Invalid sparse format.\n");
		return 1;
	}
	print_header_info(header);
	return 0;

}

/******************************************************************************/
int ext4_unsparse(struct mmc *mmc, u32 dev, u8 *pbuf, u32 blk, u32 cnt)
{
	u32 i, num;
	u64 dense_len = 0;
	u64 sparse_len = 0;
	u64 img_size;
	u32 chunk_len;
	s32 percent_complete = -1;
	chunk_header_t *chunk = NULL;
	sparse_header_t *header = (sparse_header_t *)pbuf;

	if (!is_sparse_image(header)) {
		printf("Invalid sparse format.\n");
		return 1;
	}

	/* check header->blk_sz align to emmc block size */
	if (header->blk_sz & ((1 << EMMC_BLKSIZE_SHIFT) - 1)) {
		printf("image blk size %d is not aligned to 512Byte.\n",
		       header->blk_sz);
		return 1;
	}

	/* check fs img's real size is larger than partition size */
	img_size = (u64)(header->total_blks * header->blk_sz);
	if ((img_size >> EMMC_BLKSIZE_SHIFT) > (u64)cnt) {
		printf("partition size %d MB not enough.\n",
		       (int)(cnt >> (SZ_1M_SHIFT - EMMC_BLKSIZE_SHIFT)));
		print_header_info(header);
		return 1;
	}

	/* skip the sparse header,to visit first chunk */
	pbuf += header->file_hdr_sz;

	/* to visit each chunk */
	for (i = 0; i < header->total_chunks; i++) {

		/* here the chunk_header */
		chunk = (chunk_header_t *)pbuf;

		/* go to next chunk's data */
		pbuf += header->chunk_hdr_sz;

		switch (chunk->chunk_type) {
		case CHUNK_TYPE_RAW:

			/* to calculate the length of each chunk */
			chunk_len = chunk->chunk_sz * header->blk_sz;

			/* verify every chunk to asure it is valid */
			if (chunk->total_sz
			    != (chunk_len + header->chunk_hdr_sz)) {
				printf("No.%d chunk size error.\n", i);
				print_chunk_info(chunk);
				return 1;
			}

			dense_len += chunk_len;
			sparse_len += chunk_len;

			if (sparse_len > ((u64)cnt << EMMC_BLKSIZE_SHIFT)) {
				printf("error: sparse size %d MB is "
				       "larger than partiton size %d MB.\n",
				       (int)(sparse_len >> SZ_1M_SHIFT),
				       (int)(cnt >> (SZ_1M_SHIFT
						     - EMMC_BLKSIZE_SHIFT)));
				print_chunk_info(chunk);
				return 1;
			}

			num = blk_dwrite(mmc_get_blk_desc(mmc), blk,
					 (chunk_len >> EMMC_BLKSIZE_SHIFT), pbuf);
			if (num != (chunk_len >> EMMC_BLKSIZE_SHIFT)) {
				printf("Raw data: No.%d blocks written: %s.\n",
				       num, "ERROR");
				return 1;
			}

			pbuf += chunk_len;
			blk  += (chunk_len >> EMMC_BLKSIZE_SHIFT);
			break;

		case CHUNK_TYPE_DONT_CARE:
			if (chunk->total_sz != header->chunk_hdr_sz) {
				printf("No.%d chunk size error.\n", i);
				print_chunk_info(chunk);
				return 1;
			}

			chunk_len = chunk->chunk_sz * header->blk_sz;
			sparse_len += chunk_len;

			if (sparse_len > ((u64)cnt << EMMC_BLKSIZE_SHIFT)) {
				printf("error: sparse size %d MB is "
				       "larger than partiton size %d MB.\n",
				       (int)(sparse_len >> SZ_1M_SHIFT),
				       (int)(cnt >> (SZ_1M_SHIFT
						     - EMMC_BLKSIZE_SHIFT)));
				print_chunk_info(chunk);
				return 1;
			}

			blk  += (chunk_len >> EMMC_BLKSIZE_SHIFT);
			break;

		default:
			printf("sparse: unknow chunk type %04x.\n",
			       chunk->chunk_type);
			return 1;
		}

		{
			u64 n = (u64)(sparse_len >> EMMC_BLKSIZE_SHIFT) * 100;
			int percent;
			do_div(n, cnt);
			percent = (int)n;

			if (percent != percent_complete) {
				percent_complete = percent;
				printf("\rWriting at %d blk# "
				       "-- %3d%% complete.",
				       (int)(blk
					     + (sparse_len >> EMMC_BLKSIZE_SHIFT)),
				       percent);
			}
		}

	}
	puts("\n");

	if (((u64)cnt << EMMC_BLKSIZE_SHIFT) != sparse_len) {
		printf("error: partition size %d MB != ext4 image size %d MB\n",
		       (int)(cnt >> (SZ_1M_SHIFT - EMMC_BLKSIZE_SHIFT)),
		       (int)(sparse_len >> SZ_1M_SHIFT));
		return 1;
	}

	printf("sparse: %d MB / %d MB.\n", (int)(dense_len >> SZ_1M_SHIFT),
	       (int)(sparse_len >> SZ_1M_SHIFT));

	return 0;
}

#ifdef CONFIG_CMD_UFS
/******************************************************************************/
int ufs_ext4_unsparse(const u8 *pbuf, u32 blk, u32 cnt)
{
	u32 i, num;
	u64 dense_len = 0;
	u64 sparse_len = 0;
	u64 img_size;
	u32 chunk_len;
	s32 percent_complete = -1;
	chunk_header_t *chunk = NULL;
	sparse_header_t *header = (sparse_header_t *)pbuf;

	if (!is_sparse_image(header)) {
		printf("Invalid sparse format.\n");
		return 1;
	}

	/* check header->blk_sz align to emmc block size */
	if (header->blk_sz & ((1 << UFS_BLKSIZE_SHIFT) - 1)) {
		printf("image blk size %d is not aligned to 512Byte.\n",
		       header->blk_sz);
		return 1;
	}

	/* check fs img's real size is larger than partition size */
	img_size = (u64)(header->total_blks * header->blk_sz);
	if ((img_size >> UFS_BLKSIZE_SHIFT) > (u64)cnt) {
		printf("partition size %d MB not enough.\n",
		       (int)(cnt >> (SZ_1M_SHIFT - UFS_BLKSIZE_SHIFT)));
		print_header_info(header);
		return 1;
	}

	/* skip the sparse header,to visit first chunk */
	pbuf += header->file_hdr_sz;

	/* to visit each chunk */
	for (i = 0; i < header->total_chunks; i++) {

		/* here the chunk_header */
		chunk = (chunk_header_t *)pbuf;

		/* go to next chunk's data */
		pbuf += header->chunk_hdr_sz;

		switch (chunk->chunk_type) {
		case CHUNK_TYPE_RAW:

			/* to calculate the length of each chunk */
			chunk_len = chunk->chunk_sz * header->blk_sz;

			/* verify every chunk to asure it is valid */
			if (chunk->total_sz
			    != (chunk_len + header->chunk_hdr_sz)) {
				printf("No.%d chunk size error.\n", i);
				print_chunk_info(chunk);
				return 1;
			}

			dense_len += chunk_len;
			sparse_len += chunk_len;

			if (sparse_len > ((u64)cnt << UFS_BLKSIZE_SHIFT)) {
				printf("error: sparse size %d MB is "
				       "larger than partiton size %d MB.\n",
				       (int)(sparse_len >> SZ_1M_SHIFT),
				       (int)(cnt >> (SZ_1M_SHIFT
						     - UFS_BLKSIZE_SHIFT)));
				print_chunk_info(chunk);
				return 1;
			}

			if (ufs_write_storage((uint64_t)pbuf,
					      (blk << UFS_BLKSIZE_SHIFT),
					      chunk_len) == 0)
				num = chunk_len >> UFS_BLKSIZE_SHIFT;
			else
				num = 0;

			if (num != (chunk_len >> UFS_BLKSIZE_SHIFT)) {
				printf("Raw data: No.%d blocks written: %s.\n",
				       num, "ERROR");
				return 1;
			}

			pbuf += chunk_len;
			blk  += (chunk_len >> UFS_BLKSIZE_SHIFT);
			break;

		case CHUNK_TYPE_DONT_CARE:
			if (chunk->total_sz != header->chunk_hdr_sz) {
				printf("No.%d chunk size error.\n", i);
				print_chunk_info(chunk);
				return 1;
			}

			chunk_len = chunk->chunk_sz * header->blk_sz;
			sparse_len += chunk_len;

			if (sparse_len > ((u64)cnt << UFS_BLKSIZE_SHIFT)) {
				printf("error: sparse size %d MB is "
				       "larger than partiton size %d MB.\n",
				       (int)(sparse_len >> SZ_1M_SHIFT),
				       (int)(cnt >> (SZ_1M_SHIFT
						     - UFS_BLKSIZE_SHIFT)));
				print_chunk_info(chunk);
				return 1;
			}

			blk  += (chunk_len >> UFS_BLKSIZE_SHIFT);
			break;

		default:
			printf("sparse: unknown chunk type %04x.\n",
			       chunk->chunk_type);
			return 1;
		}

		{
			u64 n = (u64)(sparse_len >> UFS_BLKSIZE_SHIFT) * 100;
			int percent;

			do_div(n, cnt);
			percent = (int)n;

			if (percent != percent_complete) {
				percent_complete = percent;
				printf("\rWriting at %d blk# "
				       "-- %3d%% complete.",
				       (int)(blk
					     + (sparse_len >> UFS_BLKSIZE_SHIFT)),
				       percent);
			}
		}

	}
	puts("\n");

	if (((u64)cnt << UFS_BLKSIZE_SHIFT) != sparse_len) {
		printf("error: partition size %d MB != ext4 image size %d MB\n",
		       (int)(cnt >> (SZ_1M_SHIFT - UFS_BLKSIZE_SHIFT)),
		       (int)(sparse_len >> SZ_1M_SHIFT));
		return 1;
	}

	printf("sparse: %d MB / %d MB.\n", (int)(dense_len >> SZ_1M_SHIFT),
	       (int)(sparse_len >> SZ_1M_SHIFT));

	return 0;
}
#endif
