/*
 * This header was generated from the NUTTX headers by update_headers.py,
 * to provide necessary information from kernel to userspace, such as constants,
 * structures, and macros, and thus, contains no copyrightable information.
 */
#ifndef __INCLUDE_NUTTX_VIDIO_FB_H
#define __INCLUDE_NUTTX_VIDIO_FB_H
#define CONFIG_FB_CMAP
#define CONFIG_FB_OVERLAY_BLIT
#define CONFIG_FB_OVERLAY
#define CONFIG_FB_TRANSPARENCY
#define FB_FMT_Y1             0
#define FB_FMT_Y2             1
#define FB_FMT_Y4             2
#define FB_FMT_Y8             3
#define FB_FMT_Y16            4
#define FB_FMT_GREY           FB_FMT_Y8
#define FB_FMT_Y800           FB_FMT_Y8
#define FB_ISMONO(f)          ((f) >= FB_FMT_Y4) && (f) <= FB_FMT_Y16)
#define FB_FMT_RGB1           FB_FMT_Y1
#define FB_FMT_RGB4           5
#define FB_FMT_RGB8           6
#define FB_FMT_RGB8_222       7
#define FB_FMT_RGB8_332       8
#define FB_FMT_RGB12_444      9
#define FB_FMT_RGB16_555      10
#define FB_FMT_RGB16_565      11
#define FB_FMT_RGB24          12
#define FB_FMT_RGB32          13
#define FB_FMT_RGBRLE4        14
#define FB_FMT_RGBRLE8        15
#define FB_FMT_RGBRAW         16
#define FB_FMT_RGBBTFLD16     17
#define FB_FMT_RGBBTFLD24     18
#define FB_FMT_RGBBTFLD32     19
#define FB_FMT_RGBA16         20
#define FB_FMT_RGBA32         21
#define FB_FMT_RGBT16         22
#define FB_FMT_RGBT32         23
#define FB_ISRGB(f)           ((f) >= FB_FMT_RGB1) && (f) <= FB_FMT_RGBT32)
#define FB_FMT_AYUV           24
#define FB_FMT_CLJR           25
#define FB_FMT_CYUV           26
#define FB_FMT_IRAW           27
#define FB_FMT_IUYV           28
#define FB_FMT_IY41           29
#define FB_FMT_IYU2           30
#define FB_FMT_HDYC           31
#define FB_FMT_UYVP           32
#define FB_FMT_UYVY           33
#define FB_FMT_UYNV           FB_FMT_UYVY
#define FB_FMT_Y422           FB_FMT_UYVY
#define FB_FMT_V210           34
#define FB_FMT_V422           35
#define FB_FMT_V655           36
#define FB_FMT_VYUY           37
#define FB_FMT_YUYV           38
#define FB_FMT_YUY2           FB_FMT_YUYV
#define FB_FMT_YUNV           FB_FMT_YUYV
#define FB_FMT_YVYU           39
#define FB_FMT_Y41P           40
#define FB_FMT_Y411           41
#define FB_FMT_Y211           42
#define FB_FMT_Y41T           43
#define FB_FMT_Y42T           44
#define FB_FMT_YUVP           45
#define FB_ISYUVPACKED(f)     ((f) >= FB_FMT_AYUV) && (f) <= FB_FMT_YUVP)
#define FB_FMT_YVU9           46
#define FB_FMT_YUV9           47
#define FB_FMT_IF09           48
#define FB_FMT_YV16           49
#define FB_FMT_YV12           50
#define FB_FMT_I420           51
#define FB_FMT_IYUV           FB_FMT_I420
#define FB_FMT_NV12           52
#define FB_FMT_NV21           53
#define FB_FMT_IMC1           54
#define FB_FMT_IMC2           55
#define FB_FMT_IMC3           56
#define FB_FMT_IMC4           57
#define FB_FMT_CLPL           58
#define FB_FMT_Y41B           59
#define FB_FMT_Y42B           60
#define FB_FMT_CXY1           61
#define FB_FMT_CXY2           62
#define FB_ISYUVPLANAR(f)     (((f) >= FB_FMT_AYUV) && (f) <= FB_FMT_YUVP)
#define FB_ISYUV(f)           (FB_ISYUVPACKED(f) || FB_ISYUVPLANAR(f))
#ifdef CONFIG_FB_HWCURSOR
#define FB_CUR_ENABLE       0x01
#define FB_CUR_SETIMAGE     0x02
#define FB_CUR_SETPOSITION  0x04
#define FB_CUR_SETSIZE      0x08
#define FB_CUR_XOR          0x10
#endif
#ifdef CONFIG_FB_OVERLAY
#define FB_ACCL_TRANSP      0x01
#define FB_ACCL_CHROMA      0x02
#define FB_ACCL_COLOR       0x04
#define FB_ACCL_AREA        0x08
#ifdef CONFIG_FB_OVERLAY_BLIT
#define FB_ACCL_BLIT        0x10
#define FB_ACCL_BLEND       0x20
#endif
#define FB_CONST_ALPHA      0x00
#define FB_PIXEL_ALPHA      0x01
#endif
#define _FBIOCBASE      (0x2800)
#define _IOC_X(type,nr)   ((type)|(nr))
#define _FBIOC(nr)       _IOC_X(_FBIOCBASE,nr)
#define FBIOGET_VIDEOINFO     _FBIOC(0x0001)
#define FBIOGET_PLANEINFO     _FBIOC(0x0002)
#ifdef CONFIG_FB_CMAP
#define FBIOGET_CMAP        _FBIOC(0x0003)
#define FBIOPUT_CMAP        _FBIOC(0x0004)
#endif
#ifdef CONFIG_FB_HWCURSOR
#define FBIOGET_CURSOR      _FBIOC(0x0005)
#define FBIOPUT_CURSOR      _FBIOC(0x0006)
#endif
#ifdef CONFIG_LCD_UPDATE
#define FBIO_UPDATE         _FBIOC(0x0007)
#endif
#ifdef CONFIG_FB_SYNC
#define FBIO_WAITFORVSYNC   _FBIOC(0x0008)
#endif
#ifdef CONFIG_FB_OVERLAY
#define FBIOGET_OVERLAYINFO _FBIOC(0x0009)
#define FBIO_SELECT_OVERLAY _FBIOC(0x000a)
#define FBIOSET_TRANSP      _FBIOC(0x000b)
#define FBIOSET_CHROMAKEY   _FBIOC(0x000c)
#define FBIOSET_COLOR       _FBIOC(0x000d)
#define FBIOSET_BLANK       _FBIOC(0x000e)
#define FBIOSET_AREA        _FBIOC(0x000f)
#ifdef CONFIG_FB_OVERLAY_BLIT
#define FBIOSET_BLIT        _FBIOC(0x0010)
#define FBIOSET_BLEND       _FBIOC(0x0011)
#endif
#endif
#define FIOC_MMAP               _FBIOC(0x0012)
typedef uint16_t fb_coord_t;
struct fb_videoinfo_s
{
    uint8_t    fmt;
    fb_coord_t xres;
    fb_coord_t yres;
    uint8_t    nplanes;
#ifdef CONFIG_FB_OVERLAY
    uint8_t    noverlays;
#endif
};
struct fb_planeinfo_s
{
    void  *fbmem;
    size_t     fblen;
    fb_coord_t stride;
    uint8_t    display;
    uint8_t    bpp;
};
#ifdef CONFIG_FB_OVERLAY
struct fb_transp_s
{
    uint8_t    transp;
    uint8_t    transp_mode;
};
struct fb_area_s
{
    fb_coord_t x;
    fb_coord_t y;
    fb_coord_t w;
    fb_coord_t h;
};
struct fb_overlayinfo_s
{
    void       *fbmem;
    void       *memphys;
    size_t     fblen;
    fb_coord_t stride;
    uint8_t    overlay;
    uint8_t    bpp;
    uint8_t    blank;
    uint32_t   chromakey;
    uint32_t   color;
    struct fb_transp_s transp;
    struct fb_area_s sarea;
    uint32_t   accl;
};
#ifdef CONFIG_FB_OVERLAY_BLIT
struct fb_overlayarea_s
{
    uint8_t  overlay;
    struct fb_area_s area;
};
struct fb_overlayblit_s
{
    struct fb_overlayarea_s dest;
    struct fb_overlayarea_s src;
};
struct fb_overlayblend_s
{
    struct fb_overlayarea_s dest;
    struct fb_overlayarea_s foreground;
    struct fb_overlayarea_s background;
};
#endif
#endif
#ifdef CONFIG_FB_CMAP
struct fb_cmap_s
{
    uint16_t  first;
    uint16_t  len;
    uint8_t *red;
    uint8_t *green;
    uint8_t *blue;
#ifdef CONFIG_FB_TRANSPARENCY
    uint8_t *transp;
#endif
};
#endif
#ifdef CONFIG_FB_HWCURSOR
#ifdef CONFIG_FB_HWCURSORIMAGE
struct fb_cursorimage_s
{
    fb_coord_t     width;
    fb_coord_t     height;
    const uint8_t *image;
};
#endif
struct fb_cursorpos_s
{
    fb_coord_t x;
    fb_coord_t y;
};
#ifdef CONFIG_FB_HWCURSORSIZE
struct fb_cursorsize_s
{
    fb_coord_t h;
    fb_coord_t w;
};
#endif
struct fb_cursorattrib_s
{
#ifdef CONFIG_FB_HWCURSORIMAGE
    uint8_t fmt;
#endif
    struct fb_cursorpos_s  pos;
#ifdef CONFIG_FB_HWCURSORSIZE
    struct fb_cursorsize_s mxsize;
    struct fb_cursorsize_s size;
#endif
};
struct fb_setcursor_s
{
    uint8_t flags;
    struct fb_cursorpos_s pos;
#ifdef CONFIG_FB_HWCURSORSIZE
    struct fb_cursorsize_s  size;
#endif
#ifdef CONFIG_FB_HWCURSORIMAGE
    struct fb_cursorimage_s img;
#endif
};
#endif
struct fb_vtable_s
{
    int (*getvideoinfo)(struct fb_vtable_s *vtable, struct fb_videoinfo_s *vinfo);
    int (*getplaneinfo)(struct fb_vtable_s *vtable, int planeno, struct fb_planeinfo_s *pinfo);
#ifdef CONFIG_FB_CMAP
    int (*getcmap)(struct fb_vtable_s *vtable, struct fb_cmap_s *cmap);
    int (*putcmap)(struct fb_vtable_s *vtable, const struct fb_cmap_s *cmap);
#endif
#ifdef CONFIG_FB_HWCURSOR
    int (*getcursor)(struct fb_vtable_s *vtable, struct fb_cursorattrib_s *attrib);
    int (*setcursor)(struct fb_vtable_s *vtable, struct fb_setcursor_s *settings);
#endif
#ifdef CONFIG_FB_SYNC
    int (*waitforvsync)(struct fb_vtable_s *vtable);
#endif
#ifdef CONFIG_FB_OVERLAY
    int (*getoverlayinfo)(struct fb_vtable_s *vtable, int overlayno, struct fb_overlayinfo_s *oinfo);
    int (*settransp)(struct fb_vtable_s *vtable, const struct fb_overlayinfo_s *oinfo);
    int (*setchromakey)(struct fb_vtable_s *vtable, const struct fb_overlayinfo_s *oinfo);
    int (*setcolor)(struct fb_vtable_s *vtable, const struct fb_overlayinfo_s *oinfo);
    int (*setblank)(struct fb_vtable_s *vtable, const struct fb_overlayinfo_s *oinfo);
    int (*setarea)(struct fb_vtable_s *vtable, const struct fb_overlayinfo_s *oinfo);
#ifdef CONFIG_FB_OVERLAY_BLIT
    int (*blit)(struct fb_vtable_s *vtable, const struct fb_overlayblit_s *blit);
    int (*blend)(struct fb_vtable_s *vtable, const struct fb_overlayblend_s *blend);
#endif
#endif
    int (*fb_open)(struct fb_vtable_s *vtable);
    int (*fb_release)(struct fb_vtable_s *vtable);
#ifdef CONFIG_FB_OVERLAY
    int (*fb_pan_display)(struct fb_vtable_s *vtable, struct fb_overlayinfo_s *oinfo);
#endif
    int (*fb_ioctl)(struct fb_vtable_s *vtable, int cmd, unsigned long arg);
    int (*fb_check_var)(struct fb_vtable_s *vtable, unsigned long arg);
    int (*fb_set_par)(struct fb_vtable_s *vtable);
    ssize_t (*fb_mmap)(struct fb_vtable_s *vtable, void *region);
};
#endif
