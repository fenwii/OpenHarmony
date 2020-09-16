/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup Display
 * @{
 *
 * @brief Defines driver functions of the display module.
 *
 * The driver functions provided for the GUI include the layer, hardware acceleration, memory, and callback functions.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file display_type.h
 *
 * @brief Declares the types used by the display driver functions.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef DISPLAY_TYPE_H
#define DISPLAY_TYPE_H
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates return values of the functions.
 *
 */
typedef enum {
    DISPLAY_SUCCESS = 0,           /**< Success */
    DISPLAY_FAILURE = -1,          /**< Failure */
    DISPLAY_FD_ERR = -2,           /**< File handle (FD) error */
    DISPLAY_PARAM_ERR = -3,        /**< Parameter error */
    DISPLAY_NULL_PTR = -4,         /**< Null pointer */
    DISPLAY_NOT_SUPPORT = -5,      /**< Unsupported feature */
    DISPLAY_NOMEM = -6,            /**< Insufficient memory */
    DISPLAY_SYS_BUSY = -7,         /**< System busy */
    DISPLAY_NOT_PERM = -8          /**< Forbidden operation */
} DispErrCode;

/**
 * @brief Enumerates layer types.
 *
 */
typedef enum {
    LAYER_TYPE_GRAPHIC,         /**< Graphic layer */
    LAYER_TYPE_OVERLAY,         /**< Overlay layer */
    LAYER_TYPE_SDIEBAND,        /**< Sideband layer */
    LAYER_TYPE_BUTT             /**< Empty layer */
} LayerType;

/**
 * @brief Enumerates pixel formats.
 *
 */
typedef enum {
    PIXEL_FMT_CLUT8 = 0,        /**< CLUT8 format */
    PIXEL_FMT_CLUT1,            /**< CLUT1 format */
    PIXEL_FMT_CLUT4,            /**< CLUT4 format */
    PIXEL_FMT_RGB_565,          /**< RGB565 format */
    PIXEL_FMT_RGBA_5658,        /**< RGBA5658 format */
    PIXEL_FMT_RGBX_4444,        /**< RGBX4444 format */
    PIXEL_FMT_RGBA_4444,        /**< RGBA4444 format */
    PIXEL_FMT_RGB_444,          /**< RGB444 format */
    PIXEL_FMT_RGBX_5551,        /**< RGBX5551 format */
    PIXEL_FMT_RGBA_5551,        /**< RGBA5551 format */
    PIXEL_FMT_RGB_555,          /**< RGB555 format */
    PIXEL_FMT_RGBX_8888,        /**< RGBX8888 format */
    PIXEL_FMT_RGBA_8888,        /**< RGBA8888 format */
    PIXEL_FMT_RGB_888,          /**< RGB888 format */
    PIXEL_FMT_BGR_565,          /**< BGR565 format */
    PIXEL_FMT_BGRX_4444,        /**< BGRX4444 format */
    PIXEL_FMT_BGRA_4444,        /**< BGRA4444 format */
    PIXEL_FMT_BGRX_5551,        /**< BGRX5551 format */
    PIXEL_FMT_BGRA_5551,        /**< BGRA5551 format */
    PIXEL_FMT_BGRX_8888,        /**< BGRX8888 format */
    PIXEL_FMT_BGRA_8888,        /**< BGRA8888 format */
    PIXEL_FMT_YUV_422_I,        /**< YUV422 interleaved format */
    PIXEL_FMT_YCBCR_422_SP,     /**< YCBCR422 semi-planar format */
    PIXEL_FMT_YCRCB_422_SP,     /**< YCRCB422 semi-planar format */
    PIXEL_FMT_YCBCR_420_SP,     /**< YCBCR420 semi-planar format */
    PIXEL_FMT_YCRCB_420_SP,     /**< YCRCB420 semi-planar format */
    PIXEL_FMT_YCBCR_422_P,      /**< YCBCR422 planar format */
    PIXEL_FMT_YCRCB_422_P,      /**< YCRCB422 planar format */
    PIXEL_FMT_YCBCR_420_P,      /**< YCBCR420 planar format */
    PIXEL_FMT_YCRCB_420_P,      /**< YCRCB420 planar format */
    PIXEL_FMT_YUYV_422_PKG,     /**< YUYV422 packed format */
    PIXEL_FMT_UYVY_422_PKG,     /**< UYVY422 packed format */
    PIXEL_FMT_YVYU_422_PKG,     /**< YVYU422 packed format */
    PIXEL_FMT_VYUY_422_PKG,     /**< VYUY422 packed format */
    PIXEL_FMT_BUTT              /**< Invalid pixel format */
} PixelFormat;

/**
 * @brief Enumerates transform types of images.
 *
 */
typedef enum {
    ROTATE_NONE = 0,        /**< No rotation */
    ROTATE_90,              /**< Rotation by 90 degrees */
    ROTATE_180,             /**< Rotation by 180 degrees */
    ROTATE_270,             /**< Rotation by 270 degrees */
    ROTATE_BUTT             /**< Invalid operation */
} TransformType;

/**
 * @brief Enumerates memory types.
 *
 * Memory is allocated based on the type specified by the GUI.
 *
 */
typedef enum {
    NORMAL_MEM = 0,       /**< Memory without cache */
    CACHE_MEM,            /**< Memory with cache */
    SHM_MEM               /**< Shared memory */
} MemType;

/**
 * @brief Enumerates image blending types.
 *
 * The system combines images based on a specified blending type during hardware acceleration.
 *
 */
typedef enum {
    BLEND_NONE = 0,         /**< No blending */
    BLEND_CLEAR,            /**< CLEAR blending */
    BLEND_SRC,              /**< SRC blending */
    BLEND_SRCOVER,          /**< SRC_OVER blending */
    BLEND_DSTOVER,          /**< DST_OVER blending */
    BLEND_SRCIN,            /**< SRC_IN blending */
    BLEND_DSTIN,            /**< DST_IN blending */
    BLEND_SRCOUT,           /**< SRC_OUT blending */
    BLEND_DSTOUT,           /**< DST_OUT blending */
    BLEND_SRCATOP,          /**< SRC_ATOP blending */
    BLEND_DSTATOP,          /**< DST_ATOP blending */
    BLEND_ADD,              /**< ADD blending */
    BLEND_XOR,              /**< XOR blending */
    BLEND_DST,              /**< DST blending */
    BLEND_AKS,              /**< AKS blending */
    BLEND_AKD,              /**< AKD blending */    
    BLEND_BUTT              /**< Null operation */
} BlendType;

/**
 * @brief Enumerates ROP types supported by hardware acceleration.
 *
 * ROP performs bitwise Boolean operations (including bitwise AND and bitwise OR) on the RGB color and
 * alpha values of the foreground bitmap with those of the background bitmap,
 * and then outputs the result.
 *
 */
typedef enum {
    ROP_BLACK = 0,          /**< Blackness */
    ROP_NOTMERGEPEN,        /**< ~(S2+S1) */
    ROP_MASKNOTPEN,         /**< ~S2&S1 */
    ROP_NOTCOPYPEN,         /**< ~S2 */
    ROP_MASKPENNOT,         /**< S2&~S1 */
    ROP_NOT,                /**< ~S1 */
    ROP_XORPEN,             /**< S2^S1 */
    ROP_NOTMASKPEN,         /**< ~(S2&S1) */
    ROP_MASKPEN,            /**< S2&S1 */
    ROP_NOTXORPEN,          /**< ~(S2^S1) */
    ROP_NOP,                /**< S1 */
    ROP_MERGENOTPEN,        /**< ~S2+S1 */
    ROP_COPYPE,             /**< S2 */
    ROP_MERGEPENNOT,        /**< S2+~S1 */
    ROP_MERGEPEN,           /**< S2+S1 */
    ROP_WHITE,              /**< Whiteness */
    ROP_BUTT                /**< Invalid ROP type */
} RopType;

/**
 * @brief Enumerates color key types supported by hardware acceleration.
 *
 */
typedef enum {
    CKEY_NONE = 0,      /**< No color key */
    CKEY_SRC,           /**< Source color key */
    CKEY_DST,           /**< Destination color key */
    CKEY_BUTT           /**< Null operation */
} ColorKey;

/**
 * @brief Enumerates mirror types supported by hardware acceleration.
 *
 */
typedef enum {
    MIRROR_NONE = 0,      /**< No mirror */
    MIRROR_LR,            /**< Left and right mirrors */
    MIRROR_TB,            /**< Top and bottom mirrors */
    MIRROR_BUTT           /**< Null operation */
} MirrorType;

/**
 * @brief Enumerates connection types of hot plugging.
 *
 */
typedef enum {
    INVALID = 0,         /**< Invalid connection */
    CONNECTED,           /**< Connected */
    DISCONNECTED         /**< Disconnected */
} Connection;

/**
 * @brief Defines display information.
 *
 */
typedef struct {
    uint32_t width;              /**< Display width */
    uint32_t height;             /**< Display height */
    int32_t rotAngle;            /**< Rotation angle of the display */
} DisplayInfo;

/**
 * @brief Defines layer information.
 *
 * <b>LayerInfo</b> must be passed to the {@link OpenLayer} function, which creates a layer based on the layer
 * information.
 *
 */
typedef struct {
    int32_t width;              /**< Layer width */
    int32_t height;             /**< Layer height */
    LayerType type;             /**< Layer type, which can be a graphics layer, overlay layer, and sideband layer */
    int32_t bpp;                /**< Number of bits occupied by each pixel */
    PixelFormat pixFormat;      /**< Pixel format of the layer */
} LayerInfo;

/**
 * @brief Defines alpha operations on a layer.
 *
 */
typedef struct {
    bool enAlpha;         /**< Pixel alpha enable bit */
    bool enChnAlpha;      /**< Channel alpha enable bit */
    uint8_t alpha0;       /**< Alpha0 value, ranging from 0 to 255 */
    uint8_t alpha1;       /**< Alpha1 value, ranging from 0 to 255 */
    uint8_t gAlpha;       /**< Global alpha value, ranging from 0 to 255 */
} LayerAlpha;

/**
 * @brief Defines the buffer handle, including the shared memory key, shared memory ID, and physical memory address.
 *
 */
typedef struct {
    int32_t key;          /**< Shared memory key */
    int32_t shmid;        /**< Unique ID of the shared memory */
    uint64_t phyAddr;     /**< Physical address */
} BufferHandle;

/**
 * @brief Defines the memory buffer, including the buffer handle, memory type, memory size, and virtual memory address.
 *
 */
typedef struct {
    BufferHandle hdl;     /**< Buffer handle */
    MemType type;         /**< Type of the requested memory */
    uint32_t size;        /**< Size of the requested memory */
    void *virAddr;        /**< Virtual address of the requested memory */
} GrallocBuffer;

/**
 * @brief Defines buffer data of a layer, including the virtual and physical memory addresses.
 *
 */
typedef struct {
    uint64_t phyAddr;     /**< Physical memory address */
    void *virAddr;        /**< Virtual memory address */
} BufferData;

/**
 * @brief Defines the buffer, which is used to store layer data.
 *
 */
typedef struct {
    int32_t fenceId;          /**< Fence ID of the buffer */
    int32_t width;            /**< Buffer width */
    int32_t height;           /**< Buffer height */
    int32_t pitch;            /**< Number of bytes from one row of pixels in memory to the next */
    PixelFormat pixFormat;    /**< Pixel format of the buffer */
    BufferData data;          /**< Layer buffer data */
} LayerBuffer;

/**
 * @brief Defines the coordinates of the upper left corner of a rectangle as well as its width and height
 * to describe a rectangular area for an image.
 *
 */
typedef struct {
    int32_t x;      /**< Start X-axis coordinate of the rectangle */
    int32_t y;      /**< Start Y-axis coordinate of the rectangle */
    int32_t w;      /**< Width of the rectangle */
    int32_t h;      /**< Height of the rectangle */
} IRect;

/**
 * @brief Stores surface information for hardware acceleration, such as draw image, and bit blit.
 *
 */
typedef struct {
    uint64_t phyAddr;     /**< Start physical address of an image */
    int32_t height;                     /**< Image height */
    int32_t width;                      /**< Image width */
    int32_t stride;                     /**< Image stride */
    PixelFormat enColorFmt;         /**< Image format */
    bool bYCbCrClut;                /**< Whether the color lookup table (CLUT) is in the YCbCr space */
    bool bAlphaMax255;              /**< Maximum alpha value of an image (255 or 128) */
    bool bAlphaExt1555;             /**< ARGB1555 alpha extension enable bit */
    uint8_t alpha0;           /**< Value of alpha0, ranging from 0 to 255 */
    uint8_t alpha1;           /**< Value of alpha1, ranging from 0 to 255 */
    uint64_t cbcrPhyAddr;      /**< CbCr physical address */
    int32_t cbcrStride;                 /**< CbCr stride */
    uint64_t clutPhyAddr;      /**< Start physical address of the CLUT, used for color extension or correction */
} ISurface;

/**
 * @brief Describes a line to help draw lines in hardware acceleration.
 *
 */
typedef struct {
    int32_t x0;                 /**< X-axis coordinate of the start point of a line */
    int32_t y0;                 /**< Y-axis coordinate of the start point of a line */
    int32_t x1;                 /**< X-axis coordinate of the end point of a line */
    int32_t y1;                 /**< Y-axis coordinate of the end point of a line */
    uint32_t color;     /**< Line color */
} ILine;

/**
 * @brief Describes a circle to help draw circles in hardware acceleration.
 *
 */
typedef struct {
    int32_t x;                  /**< X-axis coordinate of a circle center */
    int32_t y;                  /**< Y-axis coordinate of a circle center */
    int32_t r;                  /**< Radius of a circle */
    uint32_t color;     /**< Circle color */
} ICircle;

/**
 * @brief Describes a rectangle to help draw rectangles in hardware acceleration.
 *
 */
typedef struct {
    IRect rect;             /**< Bounds of a rectangle */
    uint32_t color;     /**< Rectangle color */
} Rectangle;

/**
 * @brief Defines hardware acceleration options.
 *
 */
typedef struct {
    bool enAlpha;               /**< Alpha enable bit */
    uint32_t globalAlpha;   /**< Global alpha value */
    BlendType blendType;        /**< Blending type */
    ColorKey colorKeyFrom;      /**< Color key mode */
    bool enableRop;             /**< Raster operations pipeline (ROP) enable bit */
    RopType ropType;            /**< ROP type */
    bool enableScale;           /**< Scaling enable bit */
    TransformType rotateType;   /**< Rotation type */
    MirrorType mirrorType;      /**< Mirror type */
} GfxOpt;

#ifdef __cplusplus
}
#endif
#endif
/** @} */
