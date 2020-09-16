
#include <linux/types.h>
#include <common.h>
#include <errno.h>
#include <exports.h>
#include <linux/string.h>
#include <image.h>
#include <asm/io.h>
#include <cpu_func.h>
#include <asm/setup.h>

#define SECURE		0x0
#define NON_SECURE	0x1

#define EP_EE_MASK      0x2
#define EP_EE_LITTLE    0x0
#define EP_EE_BIG       0x2
#define ep_get_ee(x) ((x) & EP_EE_MASK)
#define ep_set_ee(x, ee) ((x) = ((x) & ~EP_EE_MASK) | (ee))

/* CPSR/SPSR definitions */
#define DAIF_FIQ_BIT		(1 << 0)
#define DAIF_IRQ_BIT		(1 << 1)
#define DAIF_ABT_BIT		(1 << 2)
#define DAIF_DBG_BIT		(1 << 3)
#define SPSR_DAIF_SHIFT		6
#define SPSR_DAIF_MASK		0xf

#define SPSR_AIF_SHIFT          6
#define SPSR_AIF_MASK           0x7

#define SPSR_E_SHIFT            9
#define SPSR_E_MASK                     0x1
#define SPSR_E_LITTLE           0x0
#define SPSR_E_BIG                      0x1

#define SPSR_T_SHIFT            5
#define SPSR_T_MASK                     0x1
#define SPSR_T_ARM                      0x0
#define SPSR_T_THUMB            0x1

#define MODE_SP_SHIFT		0x0
#define MODE_SP_MASK		0x1
#define MODE_SP_EL0		0x0
#define MODE_SP_ELX		0x1

#define MODE_RW_SHIFT		0x4
#define MODE_RW_MASK		0x1
#define MODE_RW_64			0x0
#define MODE_RW_32			0x1

#define MODE_EL_SHIFT		0x2
#define MODE_EL_MASK		0x3
#define MODE_EL3		0x3
#define MODE_EL2		0x2
#define MODE_EL1		0x1
#define MODE_EL0		0x0

#define MODE32_SHIFT            0
#define MODE32_MASK             0xf
#define MODE32_USR              0x0
#define MODE32_FIQ              0x1
#define MODE32_IRQ              0x2
#define MODE32_SVC              0x3
#define MODE32_MON              0x6
#define MODE32_ABT              0x7
#define MODE32_HYP              0xa
#define MODE32_UND              0xb
#define MODE32_SYS              0xf

#define DISABLE_ALL_EXCEPTIONS \
		(DAIF_FIQ_BIT | DAIF_IRQ_BIT | DAIF_ABT_BIT | DAIF_DBG_BIT)

#define PARAM_EP_SECURITY_MASK    0x1
#define get_security_state(x) ((x) & PARAM_EP_SECURITY_MASK)
#define set_security_state(x, security) \
			((x) = ((x) & ~PARAM_EP_SECURITY_MASK) | (security))

#define spsr_64(el, sp, daif) \
	(MODE_RW_64 << MODE_RW_SHIFT | \
	((el) & MODE_EL_MASK) << MODE_EL_SHIFT | \
	((sp) & MODE_SP_MASK) << MODE_SP_SHIFT | \
	((daif) & SPSR_DAIF_MASK) << SPSR_DAIF_SHIFT)

#define spsr_mode32(mode, isa, endian, aif) \
	(MODE_RW_32 << MODE_RW_SHIFT | \
	((mode) & MODE32_MASK) << MODE32_SHIFT | \
	((isa) & SPSR_T_MASK) << SPSR_T_SHIFT | \
	((endian) & SPSR_E_MASK) << SPSR_E_SHIFT | \
	((aif) & SPSR_AIF_MASK) << SPSR_AIF_SHIFT)


/* Length of a node address (an IEEE 802 address). */
#define	_UUID_NODE_LEN		6

/*
 * See also:
 *      http://www.opengroup.org/dce/info/draft-leach-uuids-guids-01.txt
 *      http://www.opengroup.org/onlinepubs/009629399/apdxa.htm
 *
 * A DCE 1.1 compatible source representation of UUIDs.
 */

/* XXX namespace pollution? */
typedef struct uuid uuid_t;

#define FIP_MAX_FILES			10

/* TODO: Update this number as required */
#define TOC_HEADER_SERIAL_NUMBER	0x12345678

#define FLAG_FILENAME			(1 << 0)

#define WAIT_A53MP_UP_NUM_OF_TIMES	10700

typedef struct entry_lookup_list {
	const char       *name;
	uuid_t           name_uuid;
	const char       *command_line_name;
	struct file_info *info;
	unsigned int     flags;
} entry_lookup_list_t;

typedef struct file_info {
	uuid_t 		name_uuid;
	const char      *filename;
	unsigned int 	size;
	void            *image_buffer;
	entry_lookup_list_t *entry;
} file_info_t;


/* This is used as a signature to validate the blob header */
#define TOC_HEADER_NAME	0xAA640001


/* ToC Entry UUIDs */
#define UUID_TRUSTED_BOOT_FIRMWARE_BL2 \
	{0x0becf95f, 0x224d, 0x4d3e, 0xa5, 0x44, {0xc3, 0x9d, 0x81, 0xc7, 0x3f, 0x0a} }
#define UUID_SCP_FIRMWARE_BL30 \
	{0x3dfd6697, 0xbe89, 0x49e8, 0xae, 0x5d, {0x78, 0xa1, 0x40, 0x60, 0x82, 0x13} }
#define UUID_EL3_RUNTIME_FIRMWARE_BL31 \
	{0x6d08d447, 0xfe4c, 0x4698, 0x9b, 0x95, {0x29, 0x50, 0xcb, 0xbd, 0x5a, 0x00} }
#define UUID_SECURE_PAYLOAD_BL32 \
	{0x89e1d005, 0xdc53, 0x4713, 0x8d, 0x2b, {0x50, 0x0a, 0x4b, 0x7a, 0x3e, 0x38} }
#define UUID_NON_TRUSTED_FIRMWARE_BL33 \
	{0xa7eed0d6, 0xeafc, 0x4bd5, 0x97, 0x82, {0x99, 0x34, 0xf2, 0x34, 0xb6, 0xe4} }

typedef struct fip_toc_header {
	uint32_t	name;
	uint32_t	serial_number;
	uint64_t	flags;
} fip_toc_header_t;

typedef struct fip_toc_entry {
	uuid_t		uuid;
	uint64_t	offset_address;
	uint64_t	size;
	uint64_t	flags;
} fip_toc_entry_t;

typedef struct aapcs64_params {
	uint64_t arg0;
	uint64_t arg1;
	uint64_t arg2;
	uint64_t arg3;
	uint64_t arg4;
	uint64_t arg5;
	uint64_t arg6;
	uint64_t arg7;
} aapcs64_params_t;

/***************************************************************************
 * This structure provides version information and the size of the
 * structure, attributes for the structure it represents
 ***************************************************************************/
typedef struct param_header {
	uint8_t type;		/* type of the structure */
	uint8_t version;    /* version of this structure */
	uint16_t size;      /* size of this structure in bytes */
	uint32_t attr;      /* attributes: unused bits SBZ */
} param_header_t;

/*****************************************************************************
 * This structure represents the superset of information needed while
 * switching exception levels. The only two mechanisms to do so are
 * ERET & SMC. Security state is indicated using bit zero of header
 * attribute
 * NOTE: BL1 expects entrypoint followed by spsr while processing
 * SMC to jump to BL31 from the start of entry_point_info
 *****************************************************************************/
typedef struct entry_point_info {
	param_header_t h;
	uint64_t pc;
	uint32_t spsr;
	aapcs64_params_t args;
} entry_point_info_t;

/*****************************************************************************
 * Image info binary provides information from the image loader that
 * can be used by the firmware to manage available trusted RAM.
 * More advanced firmware image formats can provide additional
 * information that enables optimization or greater flexibility in the
 * common firmware code
 *****************************************************************************/
typedef struct atf_image_info {
	param_header_t h;
	uint64_t image_base;   /* physical address of base of image */
	uint32_t image_size;    /* bytes read from image file */
	uint32_t copied_size;	/* image size copied in blocks */
} atf_image_info_t;

/*******************************************************************************
 * This structure represents the superset of information that can be passed to
 * BL31 e.g. while passing control to it from BL2. The BL32 parameters will be
 * populated only if BL2 detects its presence. A pointer to a structure of this
 * type should be passed in X0 to BL31's cold boot entrypoint.
 *
 * Use of this structure and the X0 parameter is not mandatory: the BL31
 * platform code can use other mechanisms to provide the necessary information
 * about BL32 and BL33 to the common and SPD code.
 *
 * BL31 image information is mandatory if this structure is used. If either of
 * the optional BL32 and BL33 image information is not provided, this is
 * indicated by the respective image_info pointers being zero.
 ******************************************************************************/
typedef struct bl31_params {
	param_header_t h;
	uint64_t bl31_image_info;//atf_image_info_t *bl31_image_info;
	uint64_t bl32_ep_info;//entry_point_info_t *bl32_ep_info;
	uint64_t bl32_image_info;//atf_image_info_t *bl32_image_info;
	uint64_t bl33_ep_info;//entry_point_info_t *bl33_ep_info;
	uint64_t bl33_image_info;//atf_image_info_t *bl33_image_info;
} bl31_params_t;

file_info_t files[FIP_MAX_FILES];
unsigned file_info_count = 0;

uuid_t uuid_null = {0};
uuid_t uuid_bl33 = UUID_NON_TRUSTED_FIRMWARE_BL33;
uuid_t uuid_bl32 = UUID_SECURE_PAYLOAD_BL32;
uuid_t uuid_bl31 = UUID_EL3_RUNTIME_FIRMWARE_BL31;

long long kernel_load_addr;
/* kernel start addr - sizeof(header) */
#define BL33_LOAD_ADDR  (kernel_load_addr - 0x40)
#define FDT_LOAD_ADDR   (kernel_load_addr + 0x1F80000)
#define BL31_BASE       (kernel_load_addr + 0x2F80000)
#define BL31_SIZE	    0x200000

/*
 * TODO: Add ability to specify and flag different file types.
 * Add flags to the toc_entry?
 * const char* format_type_str[] = { "RAW", "ELF", "PIC" };
 */

/* The images used depends on the platform. */
static entry_lookup_list_t toc_entry_lookup_list[] = {
	{
		"Trusted Boot Firmware BL2", UUID_TRUSTED_BOOT_FIRMWARE_BL2,
		"bl2", NULL, FLAG_FILENAME
	},
	{
		"SCP Firmware BL3-0", UUID_SCP_FIRMWARE_BL30,
		"bl30", NULL, FLAG_FILENAME
	},
	{
		"EL3 Runtime Firmware BL3-1", UUID_EL3_RUNTIME_FIRMWARE_BL31,
		"bl31", NULL, FLAG_FILENAME
	},
	{
		"Secure Payload BL3-2 (Trusted OS)", UUID_SECURE_PAYLOAD_BL32,
		"bl32", NULL, FLAG_FILENAME
	},
	{
		"Non-Trusted Firmware BL3-3", UUID_NON_TRUSTED_FIRMWARE_BL33,
		"bl33", NULL, FLAG_FILENAME
	},
	{ NULL, {0}, 0 }
};

extern int fdt_check_header(const void *fdt);
extern int do_load_secure_os(ulong addr, ulong org_offset, ulong img_dst,
				int run, uint32_t *rtos_load_addr);

/* Return 0 for equal uuids */
static inline int compare_uuids(const uuid_t *uuid1, const uuid_t *uuid2)
{
	return memcmp(uuid1, uuid2, sizeof(uuid_t));
}


static inline void copy_uuid(uuid_t *to_uuid, const uuid_t *from_uuid)
{
	memcpy(to_uuid, from_uuid, sizeof(uuid_t));
}

static entry_lookup_list_t *get_entry_lookup_from_uuid(const uuid_t *uuid)
{
	unsigned int lookup_index = 0;

	while (toc_entry_lookup_list[lookup_index].command_line_name != NULL) {
		if (compare_uuids(&toc_entry_lookup_list[lookup_index].name_uuid,
						  uuid) == 0) {
			return &toc_entry_lookup_list[lookup_index];
		}
		lookup_index++;
	}
	return NULL;
}

static void dump_toc(void)
{
	unsigned int index = 0;
	unsigned int image_offset;
	unsigned int image_size = 0;

	image_offset = sizeof(fip_toc_header_t) +
				   (sizeof(fip_toc_entry_t) * (file_info_count + 1));

	printf("Firmware Image Package ToC:\n");
	printf("---------------------------\n");
	for (index = 0; index < file_info_count; index++) {
		if (files[index].entry)
			printf("- %s: ", files[index].entry->name);
		else
			printf("- Unknown entry: ");
		image_size = files[index].size;

		printf("offset=0x%X, size=0x%X\n", image_offset, image_size);
		image_offset += image_size;

		if (files[index].filename)
			printf("  file: '%s'\n", files[index].filename);
	}
	printf("---------------------------\n");
}

/* Read and load existing package into memory. */
static int parse_fip(char *fip_buffer)
{
	fip_toc_header_t *toc_header = NULL;
	fip_toc_entry_t *toc_entry = NULL;
	int found_last_toc_entry = 0;
	file_info_t *file_info_entry = NULL;
	int ret = -1;

	if (fip_buffer == NULL) {
		printf("ERROR: Invalid fip buffer addr.\n");
		ret = -EINVAL;
		goto parse_fip_error;
	}

	/* Set the ToC Header at the base of the buffer */
	toc_header = (fip_toc_header_t *)fip_buffer;
	/* The first toc entry should be just after the ToC header */
	toc_entry = (fip_toc_entry_t *)(toc_header + 1);

	/* While the ToC entry is contained into the buffer */
	int cnt = 0;
	while (cnt < FIP_MAX_FILES) {
		/* Check if the ToC Entry is the last one */
		if (compare_uuids(&toc_entry->uuid, &uuid_null) == 0) {
			found_last_toc_entry = 1;
			ret = 0;
			break;
		}

		/* Add the entry into file_info */

		/* Get the new entry in the array and clear it */
		file_info_entry = &files[file_info_count++];
		memset(file_info_entry, 0, sizeof(file_info_t));

		/* Copy the info from the ToC entry */
		copy_uuid(&file_info_entry->name_uuid, &toc_entry->uuid);
		file_info_entry->image_buffer = fip_buffer +
						toc_entry->offset_address;
		file_info_entry->size = toc_entry->size;

		/* Check if there is a corresponding entry in lookup table */
		file_info_entry->entry =
			get_entry_lookup_from_uuid(&toc_entry->uuid);

		/* Go to the next ToC entry */
		toc_entry++;
		cnt++;
	}

	if (!found_last_toc_entry) {
		printf("ERROR: Given FIP does not have an end ToC entry.\n");
		ret = -EINVAL;
		goto parse_fip_error;
	}

parse_fip_error:
	return ret;
}

int is_fip(char *buf)
{
	fip_toc_header_t *header = (fip_toc_header_t *)buf;

	if (buf == NULL) {
		printf("Invalid fip buffer address\n");
		return 0;
	}

	if ((header->name == TOC_HEADER_NAME) && (header->serial_number != 0))
		return 1;
	else
		return 0;
}

/* for a53up boot up*/
entry_point_info_t bl32_ep_info;
entry_point_info_t bl33_ep_info;
bl31_params_t bl31_params;

/*for a53mp boot up*/
entry_point_info_t amp_bl32_ep_info;
entry_point_info_t amp_bl33_ep_info;
bl31_params_t amp_bl31_params;

void *g_fdt_addr = NULL;

extern const void *fdt_getprop(const void *fdt, int nodeoffset,
				const char *name, int *lenp);

int early_init_dt_scan_chosen(unsigned long node, const char *uname,
					int depth, void *data)
{
	unsigned long l = 0;
	char *p = NULL;
	char *cmdline = data;

	if (depth != 1 || !cmdline ||
		(strcmp(uname, "chosen") != 0 && strcmp(uname, "chosen@0") != 0))
		return 0;

	p = (char *)fdt_getprop(g_fdt_addr, node, "bootargs", (int *)&l);
	if (p != NULL && l > 0)
		//strlcpy(p, cmdline, min((int)l, COMMAND_LINE_SIZE));
		strlcpy(p, cmdline, COMMAND_LINE_SIZE);

	/* break now */
	return 1;
}

extern int fdt_next_node(const void *fdt, int offset, int *depth);

extern const char *fdt_get_name(const void *fdt, int nodeoffset, int *len);

/**
 * kbasename - return the last part of a pathname.
 *
 * @path: path to extract the filename from.
 */
static inline const char *kbasename(const char *path)
{
	const char *tail = strrchr(path, '/');
	return tail ? tail + 1 : path;
}

/**
 * scan_flat_dt_save_bootargs - scan flattened tree blob and save bootargs to
 * chosen args.
 * @data: context data pointer
 *
 * This function is used to scan the flattened device-tree,
 * find the 'chosen' args, and save save bootargs to chosen args.
 */
int scan_flat_dt_save_bootargs(char *data)
{
	const void *blob = g_fdt_addr;
	const char *pathp = NULL;
	int offset;
	int rc = 0;
	int depth = -1;

	for (offset = fdt_next_node(blob, -1, &depth);
		 offset >= 0 && depth >= 0 && !rc;
		 offset = fdt_next_node(blob, offset, &depth)) {
		pathp = fdt_get_name(blob, offset, NULL);
		if (*pathp == '/')
			pathp = kbasename(pathp);

		if (!strcmp(pathp, "chosen") || !strcmp(pathp, "chosen@0")) {
			rc = early_init_dt_scan_chosen(offset, pathp, depth, data);
			break;
		}
	}

	return rc;
}

int boot_a53mp_flag = 0;
uint64_t boot_a53mp_addr = 0;

int load_fip_amp(char *buf)
{
	int ret = 0;
	unsigned int index = 0;
	entry_point_info_t *bl32_ep = &amp_bl32_ep_info;
	entry_point_info_t *bl33_ep = &amp_bl33_ep_info;
	bl31_params_t *bl31_p = &amp_bl31_params;
	uint64_t bl31_pc = 0;

	memset(bl32_ep, 0, sizeof(entry_point_info_t));
	memset(bl33_ep, 0, sizeof(entry_point_info_t));
	memset(bl31_p, 0, sizeof(bl31_params_t));
	bl31_p->bl32_ep_info = (uint64_t)(uintptr_t)bl32_ep;
	bl31_p->bl33_ep_info = (uint64_t)(uintptr_t)bl33_ep;

	printf("Load fip from 0x%pK ...\n", buf);
	if (buf == NULL) {
		printf("Invalid fip buffer address\n");
		ret = -EINVAL;
		goto exit;
	}
	ret = parse_fip(buf);
	if (ret)
		goto exit;

	dump_toc();

	printf("Create Entry Point info ...\n");
	for (index = 0; index < file_info_count; index++) {
		if (!files[index].entry) {
			printf("- Invalid entry: ");
			continue;
		}

		if (compare_uuids(&files[index].name_uuid, &uuid_bl31) == 0) {
			printf("Get - %s \n", files[index].entry->name);
			memmove((void *)(uintptr_t)BL31_BASE, files[index].image_buffer,
					files[index].size);
			bl31_pc = BL31_BASE;//(uint32_t)(files[index].image_buffer);
		}

		if (compare_uuids(&files[index].name_uuid, &uuid_bl33) == 0) {
			printf("Get - %s \n", files[index].entry->name);
			image_header_t *hdr =
				(image_header_t *)(files[index].image_buffer);
			if (image_check_arch(
					(image_header_t *)(files[index].image_buffer),
					IH_ARCH_ARM64)) {
				memmove((void *)(uintptr_t)BL33_LOAD_ADDR,
						files[index].image_buffer, files[index].size);
				hdr = (image_header_t *)(uintptr_t)(BL33_LOAD_ADDR);
				char *fdt = (char *)(uintptr_t)image_get_image_end(hdr);
				int fdt_size = files[index].size -
							   ((uintptr_t)fdt - (uintptr_t)hdr);

				printf("kernel_size[0x%x] fdt_size[0x%x] fdt_addr[0x%pK]\n",
					   files[index].size, fdt_size, fdt);
				memmove((void *)(uintptr_t)FDT_LOAD_ADDR, fdt, fdt_size);
				fdt = (char *)(uintptr_t)FDT_LOAD_ADDR;
				g_fdt_addr = fdt;
				ret = fdt_check_header(fdt);
				if (ret) {
					printf("Invalid FDT at 0x%pK, hdr at 0x%pK\n",
						   fdt, hdr);
					goto exit;
				}
				bl33_ep->pc = (uint64_t)image_get_data(
						(const image_header_t *)(uintptr_t)BL33_LOAD_ADDR);
				bl33_ep->args.arg0 = (uint64_t)(uintptr_t)fdt;
				bl33_ep->spsr = spsr_64(MODE_EL1,
							MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
				set_security_state(bl33_ep->h.attr,
								   NON_SECURE);
			} else {
				bl33_ep->pc = (uint64_t)image_get_data(files[index].image_buffer);
				bl33_ep->args.arg0 = 0; //no dtb
				bl33_ep->spsr = spsr_mode32(MODE32_SVC,
							0x0, EP_EE_LITTLE, DISABLE_ALL_EXCEPTIONS);
			}
			printf("hdr[0x%pK] header_size[0x%x] image_size[0x%x]\n", hdr,
				   image_get_header_size(), image_get_image_size(hdr));
			printf("bl33_ep->spsr = 0x%x bl33_ep->pc = 0x%llx\n", bl33_ep->spsr,
				   bl33_ep->pc);
		}
	}

	if (!bl33_ep->pc) {
		printf("Invalid fip image, no kernel found!\n");
		ret = -EINVAL;
		goto exit;
	}

	if (!bl31_pc) {
		printf("No ATF found!\n");
		ret = -EINVAL;
		goto exit;
	}

	/* save a53mp boot flag and addr, retrun success,
	 * a53mp would boot up while a53up be booting up*/
	boot_a53mp_flag = 1;
	boot_a53mp_addr = bl31_pc;
	file_info_count = 0;

	flush_dcache_all();

	return 0;

exit:
	return ret;
}

int load_fip(char *buf)
{
	int ret = 0;
	unsigned int index = 0;
	entry_point_info_t *bl32_ep = &bl32_ep_info;
	entry_point_info_t *bl33_ep = &bl33_ep_info;
	bl31_params_t *bl31_p = &bl31_params;
	uint64_t bl31_pc = 0;

	memset(bl32_ep, 0, sizeof(entry_point_info_t));
	memset(bl33_ep, 0, sizeof(entry_point_info_t));
	memset(bl31_p, 0, sizeof(bl31_params_t));
	bl31_p->bl32_ep_info = (uint64_t)(uintptr_t)bl32_ep;
	bl31_p->bl33_ep_info = (uint64_t)(uintptr_t)bl33_ep;

	printf("Load fip from 0x%pK ...\n", buf);
	if (buf == NULL) {
		printf("Invalid fip buffer address\n");
		ret = -EINVAL;
		goto error;
	}
	ret = parse_fip(buf);
	if (ret)
		goto error;

	dump_toc();

	printf("Create Entry Point info ...\n");
	for (index = 0; index < file_info_count; index++) {
		if (!files[index].entry) {
			printf("- Invalid entry: ");
			continue;
		}

		if (compare_uuids(&files[index].name_uuid, &uuid_bl31) == 0) {
			printf("Get - %s \n", files[index].entry->name);
			memmove((void *)(uintptr_t)BL31_BASE, files[index].image_buffer,
					files[index].size);
			bl31_pc = BL31_BASE;
			//(uint32_t)(files[index].image_buffer);
		}

		if (compare_uuids(&files[index].name_uuid, &uuid_bl33) == 0) {
			printf("Get - %s \n", files[index].entry->name);
			image_header_t *hdr =
				(image_header_t *)(files[index].image_buffer);
			if (image_check_arch(
					(image_header_t *)(files[index].image_buffer),
					IH_ARCH_ARM64)) {
				memmove((void *)(uintptr_t)BL33_LOAD_ADDR,
						files[index].image_buffer, files[index].size);
				hdr = (image_header_t *)(uintptr_t)(BL33_LOAD_ADDR);
				char *fdt = (char *)(uintptr_t)image_get_image_end(hdr);
				int fdt_size = files[index].size -
							   ((uintptr_t)fdt - (uintptr_t)hdr);

				printf("kernel_size[0x%x] fdt_size[0x%x] fdt_addr[0x%pK]\n", files[index].size,
					   fdt_size, fdt);
				memmove((void *)(uintptr_t)FDT_LOAD_ADDR, fdt, fdt_size);
				fdt = (char *)(uintptr_t)FDT_LOAD_ADDR;
				g_fdt_addr = fdt;
				ret = fdt_check_header(fdt);
				if (ret) {
					printf("Invalid FDT at 0x%pK, hdr at 0x%pK\n", fdt, hdr);
					goto error;
				}
				bl33_ep->pc = (uint64_t)image_get_data(
								  (const image_header_t *)(uintptr_t)BL33_LOAD_ADDR);
				bl33_ep->args.arg0 = (uint64_t)(uintptr_t)fdt;
				bl33_ep->spsr = spsr_64(MODE_EL1,
							MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
				set_security_state(bl33_ep->h.attr,
								   NON_SECURE);
			} else {
				bl33_ep->pc = (uint64_t)image_get_data(
								  files[index].image_buffer);
				bl33_ep->args.arg0 = 0; //no dtb
				bl33_ep->spsr =
					spsr_mode32(MODE32_SVC, 0x0, EP_EE_LITTLE,
								DISABLE_ALL_EXCEPTIONS);
			}
			printf("hdr[0x%pK] header_size[0x%x] image_size[0x%x]\n",
				   hdr, image_get_header_size(), image_get_image_size(hdr));
			printf("bl33_ep->spsr = 0x%x bl33_ep->pc = 0x%llx\n",
				   bl33_ep->spsr, bl33_ep->pc);
		}
	}

	if (!bl33_ep->pc) {
		printf("Invalid fip image, no kernel found!\n");
		ret = -EINVAL;
		goto error;
	}

	if (!bl31_pc) {
		printf("No ATF found!\n");
		ret = -EINVAL;
		goto error;
	}

	scan_flat_dt_save_bootargs(env_get("bootargs"));

	cleanup_before_linux();

	/* boot up a53mp*/
	if (boot_a53mp_flag && boot_a53mp_addr) {
		unsigned int jump_cmd = 0xea000004;
		unsigned int warm_reset_cmd[] = {
			0xe3a03000, 0xe3413d83, 0xf57ff06f, 0xf57ff04f,
			0xee1c3f50, 0xe3833003, 0xee0c3f50, 0xf57ff06f,
			0xe320f003, 0xeafffffe, 0x0
		};
		volatile uint32_t *p = (volatile uint32_t *)0x18;
		unsigned int *cmd = warm_reset_cmd;
		unsigned int reg;

		(*(volatile uint64_t *)8) = (uint64_t)(uintptr_t)&amp_bl31_params;
		(*(volatile uint64_t *)16) = (uint64_t)NULL;

		*((volatile uint32_t *)0) = jump_cmd;
		while (*cmd)
			*p++ = *cmd++;

		writel((boot_a53mp_addr >> 2) & 0xffffffff, REG_PERI_CPU_RVBARADDR_SOC);

		reg = readl(CRG_REG_BASE + REG_CRG_CLUSTER0_CLK_RST);
		reg &= ~CLUSTER0_GLB_SRST_REQ;
		writel(reg, CRG_REG_BASE + REG_CRG_CLUSTER0_CLK_RST);

		/* wait A53MP to boot up*/
		for (reg = 0; reg < WAIT_A53MP_UP_NUM_OF_TIMES; reg++)
			udelay(1000);
	}

	/*boot up a53up*/
	(*(volatile uint64_t *)8) = (uint64_t)(uintptr_t)bl31_p;
	(*(volatile uint64_t *)16) = (uint64_t)NULL;

	void (*atf_entry)(void) = (void(*)(void))(uintptr_t)(bl31_pc);
	atf_entry();

error:
	return ret;
}
