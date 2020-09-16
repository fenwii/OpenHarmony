/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "sec_boot.h"
#include "common.h"
#include <malloc.h>
#include "v2/api/hi_types.h"
#include "v2/api/hi_mpi_cipher.h"

#define RSA_2048_N_LEN  256
#define RSA_4096_N_LEN  512
#define UBOOT_PUB_KEY_ADDR  16
#define UBOOT_PUB_KEY_LEN_ADDR  12
#define HEADER_LENGTH_COUNT 3

static unsigned char E[] = { 0x00, 0x01, 0x00, 0x01 };
static unsigned char N_2048[RSA_2048_N_LEN] = { 0 };
static unsigned char N_4096[RSA_4096_N_LEN] = { 0 };
static int g_index = 0;
static int g_sig_len = 0;

static void deep_in(char arr[], int len)
{
    g_index++;
    if ((g_index + 1) < len) {
        int b1 = 0xFF & arr[g_index++];
        if (b1 > 0x0F) {
            g_index += (0x0F & b1);
        }
    }
}

static void parse(char arr[], int need_return, char *back)
{
    g_index++;
    int b1 = 0xFF & arr[g_index++];
    int len = 0;
    if (b1 < 128) { // 128:the upper limit of char
        len = b1;
    } else {
        for (int i = (b1 & 0x0f); i > 0; i--) {
            len = (len << 8) + (0xff & arr[g_index++]); // 8:the hex length
        }
    }

    g_index += len;
    if (need_return == 1) {
        int loop = 0;
        for (int i = g_index - len; i < g_index; i++) {
            back[loop] = arr[i];
            loop++;
        }
    }
}

static void get_pub_key(char arr[], char *modulus, int arr_len)
{
    // deepIn to Certificate.tbsCertificate (1.)
    // deepIn to tbsCertificate.version (2.)
    for (int i = 0; i < 2; i++) {
        deep_in(arr, arr_len);
    }
    // skip tbsCertificate.version (1.)
    // skip tbsCertificate.serialNumber (2.)
    // skip tbsCertificate.signature (3.)
    // skip tbsCertificate.issuer (4.)
    // skip tbsCertificate.validity (5.)
    // skip tbsCertificate.subject (6.)
    for (int i = 0; i < 6; i++) {
        parse(arr, 0, NULL);
    }
    // now we are at tbsCertificate.subjectPublicKeyInfo
    // deepIn to SubjectPublicKeyInfo.algorithm
    deep_in(arr, arr_len);
    // skip SubjectPublicKeyInfo.algorithm
    parse(arr, 0, NULL);

    char temp[RSA_4096_N_LEN * 2 + 1] = { 0 };
    // read SubjectPublicKeyInfo.subjectPublicKey
    parse(arr, 1, temp);
    // first byte indicates the number of bits to be skipped, just ignore the value
    g_index = 1;
    // deepIn to RSAPublicKey.modulus
    deep_in(temp, sizeof(temp));
    // read RSAPublicKey.modulus
    parse(temp, 1, modulus);
}

#ifdef CONFIG_HIFMC_SPI_NOR
#include "spi_flash.h"
static void spinor_flash_read(long addr, int len, void *buf)
{
    struct spi_flash *flash = spi_flash_probe(0, CONFIG_SF_DEFAULT_CS, CONFIG_SF_DEFAULT_SPEED, CONFIG_SF_DEFAULT_MODE);
    if (flash) {
        if (flash->size >= len) {
            int ret = spi_flash_read(flash, addr, len, buf);
            if (ret) {
                printf("spi_flash read err ret:%d\n", ret);
            }
        } else {
            printf("flash->size:%d, need len:%d err\n", flash->size, len);
        }
        spi_flash_free(flash);
    } else {
        printf("spi_flash probe err\n");
    }
}
#endif

#ifdef CONFIG_MMC
#include "mmc.h"
static int mmc_read_data(long addr, int len, void *buf)
{
    int ret;
    struct mmc *mmc = find_mmc_device(0);
    if (!mmc) {
        printf("find mmc_device err\n");
        return HI_FAILURE;
    }

    (void)mmc_init(mmc);
    long bl_len = mmc->read_bl_len;
    if (bl_len <= 0) {
        return HI_FAILURE;
    }

    long start = addr / bl_len;
    long offset = addr % bl_len;
    long blkcnt = len / bl_len;
    if (len % bl_len) {
        blkcnt += 1;
    }

    if (offset) {
        blkcnt += 1;
    }

    if (blkcnt * bl_len <= 0) {
        return HI_FAILURE;
    }

    char *data = (char *)malloc(blkcnt * bl_len);
    if (data == NULL) {
        printf("malloc failed, need size:%ld\n", blkcnt * bl_len);
        return HI_FAILURE;
    }

    memset(data, 0, blkcnt * bl_len);
    ret = blk_dread(mmc_get_blk_desc(mmc), start, blkcnt, data);
    if (ret != blkcnt) {
        printf("blk_dread failed, ret:%d\n", ret);
        free(data);
        return HI_FAILURE;
    }

    memcpy(buf, data + offset, len);
    free(data);
    return HI_SUCCESS;
}
#endif

static void flash_read(long addr, int len, char *buf)
{
    if (buf == NULL) {
        printf("flash_read get buf is null\n");
        return;
    }

    int boot_media = get_boot_media();
    if (boot_media == BOOT_MEDIA_SPIFLASH) {
#ifdef CONFIG_HIFMC_SPI_NOR
        spinor_flash_read(addr, len, buf);
#endif
    } else if (boot_media == BOOT_MEDIA_EMMC) {
#ifdef CONFIG_MMC
        int ret = mmc_read_data(addr, len, buf);
        if (ret == HI_FAILURE) {
            printf("mmc_read failed\n");
        }
#endif
    } else {
        printf("boot_media:%d, not support!\n", boot_media);
    }
}

static int rsa_sign_verify(char *data, int data_len, char *sig, int sig_len)
{
    int ret;
    hi_cipher_rsa_verify stRsaVerify = { 0 };
    hi_cipher_verify_data str_verify_data = { 0 };

    ret = hi_mpi_cipher_init();
    if (HI_SUCCESS != ret) {
        return HI_FAILURE;
    }

    str_verify_data.in = (unsigned char*)data;
    str_verify_data.in_len = data_len;
    str_verify_data.sign = (unsigned char*)sig;
    str_verify_data.sign_len = sig_len;
    stRsaVerify.scheme = HI_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256;
    if (sig_len == RSA_2048_N_LEN) {
        stRsaVerify.pub_key.n = N_2048;
        stRsaVerify.pub_key.n_len = sizeof(N_2048);
    } else {
        stRsaVerify.pub_key.n = N_4096;
        stRsaVerify.pub_key.n_len = sizeof(N_4096);
    }

    stRsaVerify.pub_key.e = E;
    stRsaVerify.pub_key.e_len = sizeof(E);
    ret = hi_mpi_cipher_rsa_verify(&stRsaVerify, &str_verify_data);
    if (ret) {
        printf("HI_UNF_CIPHER RsaVerify failed\n");
        (void)hi_mpi_cipher_deinit();
        return HI_FAILURE;
    }

    (void)hi_mpi_cipher_deinit();
    return HI_SUCCESS;
}

static int verify_x509_sig(char *content, int content_len, char *sig)
{
    if (g_sig_len == RSA_2048_N_LEN) {
        flash_read(UBOOT_PUB_KEY_ADDR + CONFIG_OHOS_UBOOT_START_ADDR, g_sig_len, (char *)N_2048);
    } else {
        flash_read(UBOOT_PUB_KEY_ADDR + CONFIG_OHOS_UBOOT_START_ADDR, g_sig_len, (char *)N_4096);
    }

    return rsa_sign_verify(content, content_len, sig, g_sig_len);
}

static void get_x509_modulus(char *x509_content, int len)
{
    int i;

    if (g_sig_len == RSA_2048_N_LEN) {
        char modulus[RSA_2048_N_LEN + 1] = { 0 };
        get_pub_key(x509_content, modulus, len);
        for (i = 0; i < RSA_2048_N_LEN; i++) {
            N_2048[i] = (unsigned char)modulus[i + 1];
        }
    } else {
        char modulus[RSA_4096_N_LEN + 1] = { 0 };
        get_pub_key(x509_content, modulus, len);
        for (i = 0; i < RSA_4096_N_LEN; i++) {
            N_4096[i] = (unsigned char)modulus[i + 1];
        }
    }
}

static int check_sig_bin(char *signature, int sig_len, long bin_addr, long bin_len)
{
    if (bin_len <= 0) {
        return HI_FAILURE;
    }

    char *bin_context = (char *)malloc(bin_len);
    if (bin_context == NULL) {
        printf("malloc failed\n");
        return HI_FAILURE;
    }

    memset(bin_context, 0, bin_len);
    flash_read(bin_addr, bin_len, bin_context);
    int ret = rsa_sign_verify(bin_context, bin_len, signature, sig_len);
    free(bin_context);
    if (ret) {
        printf("rsa_sign verify err at addr:%#lx\n", bin_addr);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static int check_all_sig_bin(long sig_start, int sig_num)
{
    for (int i = 0; i < sig_num; i++) {
        if (g_sig_len <= 0) {
            return HI_FAILURE;
        }

        char *signature = (char *)malloc(g_sig_len);
        if (signature == NULL) {
            printf("malloc failed\n");
            return HI_FAILURE;
        }

        memset(signature, 0, g_sig_len);
        uint32_t signature_addr = sig_start + (g_sig_len + sizeof(uint32_t) + sizeof(uint32_t)) * i;
        flash_read(signature_addr, g_sig_len, signature);
        uint32_t bin_len = 0;
        uint32_t bin_addr = 0;
        flash_read(signature_addr + g_sig_len, sizeof(uint32_t), (char *)&bin_len);
        flash_read(signature_addr + g_sig_len + sizeof(uint32_t), sizeof(uint32_t), (char *)&bin_addr);
        int ret = check_sig_bin(signature, g_sig_len, bin_addr, bin_len);
        if (ret) {
            free(signature);
            return HI_FAILURE;
        }
        free(signature);
    }
    return HI_SUCCESS;
}

static int check_sig_len(void)
{
    uint32_t len = 0;

    flash_read(UBOOT_PUB_KEY_LEN_ADDR + CONFIG_OHOS_UBOOT_START_ADDR, sizeof(uint32_t), (char *)&len);
    if (len == RSA_2048_N_LEN || len == RSA_4096_N_LEN) {
        g_sig_len = len;
    } else {
        printf("check sig len err, len:%d\n", len);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

static char *get_data(long addr, int len)
{
    if (len <= 0) {
        printf("get_data len err\n");
        return NULL;
    }

    char *buf = (char *)malloc(len);
    if (buf == NULL) {
        printf("malloc failed\n");
        return NULL;
    }
    flash_read(addr, len, buf);

    return buf;
}

int check_security_boot(long sig_addr)
{
    printf("Secboot check start\n");
    int ret = check_sig_len();
    if (ret) {
        return HI_FAILURE;
    }

    uint32_t all_len = 0;
    uint32_t sig_num = 0;
    uint32_t x509_len = 0;
    flash_read(sig_addr, sizeof(uint32_t), (char *)&all_len);
    flash_read(sig_addr + sizeof(uint32_t), sizeof(uint32_t), (char *)&sig_num);
    flash_read(sig_addr + sizeof(uint32_t) + sizeof(uint32_t), sizeof(uint32_t), (char *)&x509_len);
    uint32_t content_len = all_len - g_sig_len;
    char *content = get_data(sig_addr, content_len);
    if (content == NULL) {
        return HI_FAILURE;
    }

    char *sig = get_data(sig_addr + content_len, g_sig_len);
    if (sig == NULL) {
        free(content);
        return HI_FAILURE;
    }

    ret = verify_x509_sig(content, content_len, sig);
    free(sig);
    free(content);
    if (ret) {
        printf("verify the sig of x509 bin failed\n");
        return HI_FAILURE;
    }

    char *x509content = get_data(sig_addr + sizeof(uint32_t) * HEADER_LENGTH_COUNT, x509_len);
    if (x509content == NULL) {
        return HI_FAILURE;
    }

    get_x509_modulus(x509content, x509_len);
    free(x509content);
    long sig_start = sig_addr + sizeof(uint32_t) * HEADER_LENGTH_COUNT + x509_len;
    ret = check_all_sig_bin(sig_start, sig_num);
    if (ret) {
        printf("check all sig_bin failed\n");
        return HI_FAILURE;
    }

    printf("Secboot check... OK\n");
    return HI_SUCCESS;
}