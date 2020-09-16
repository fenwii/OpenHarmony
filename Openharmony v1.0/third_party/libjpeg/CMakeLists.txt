cmake_minimum_required(VERSION 3.16.5)

set(LibjpegSrc "${PROJECT_SOURCE_DIR}/third_party/libjpeg")

include_directories(${LibjpegSrc})

include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCSourceCompiles)

check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(string.h HAVE_STRING_H)
check_symbol_exists(size_t stddef.h stdlib.h stdio.h HAVE_ANSI_SIZE_T)
check_symbol_exists(setmode io.h USE_SETMODE)
check_c_source_compiles(
"
void f()
{
    char x[ (char)0xff ]; /* x[-1] if signed */
}
"
CHAR_IS_UNSIGNED)

check_c_source_compiles(
"
void f()
{
    char x[ ((signed char)0xff) >> 1 ]; /* x[-1] if signed */
}
"
RIGHT_SHIFT_IS_UNSIGNED)

if(NOT HAVE_STRING_H)
    set(NEED_BSD_STRINGS TRUE)
else()
    set(NEED_BSD_STRINGS FALSE)
endif()

if(NOT HAVE_ANSI_SIZE_T)
    set(NEED_SYS_TYPES_H TRUE)
else()
    set(NEED_SYS_TYPES_H FALSE)
endif()

configure_file(${LibjpegSrc}/jconfig.txt ${LibjpegSrc}/jconfig.h)

add_library(libjpeg STATIC
    ${LibjpegSrc}/cdjpeg.c
    ${LibjpegSrc}/jaricom.c
    ${LibjpegSrc}/jcapimin.c
    ${LibjpegSrc}/jcapistd.c
    ${LibjpegSrc}/jcarith.c
    ${LibjpegSrc}/jccoefct.c
    ${LibjpegSrc}/jccolor.c
    ${LibjpegSrc}/jcdctmgr.c
    ${LibjpegSrc}/jchuff.c
    ${LibjpegSrc}/jcinit.c
    ${LibjpegSrc}/jcmainct.c
    ${LibjpegSrc}/jcmarker.c
    ${LibjpegSrc}/jcmaster.c
    ${LibjpegSrc}/jcomapi.c
    ${LibjpegSrc}/jcparam.c
    ${LibjpegSrc}/jcprepct.c
    ${LibjpegSrc}/jcsample.c
    ${LibjpegSrc}/jctrans.c
    ${LibjpegSrc}/jdapimin.c
    ${LibjpegSrc}/jdapistd.c
    ${LibjpegSrc}/jdarith.c
    ${LibjpegSrc}/jdatadst.c
    ${LibjpegSrc}/jdatasrc.c
    ${LibjpegSrc}/jdcoefct.c
    ${LibjpegSrc}/jdcolor.c
    ${LibjpegSrc}/jddctmgr.c
    ${LibjpegSrc}/jdhuff.c
    ${LibjpegSrc}/jdinput.c
    ${LibjpegSrc}/jdmainct.c
    ${LibjpegSrc}/jdmarker.c
    ${LibjpegSrc}/jdmaster.c
    ${LibjpegSrc}/jdmerge.c
    ${LibjpegSrc}/jdpostct.c
    ${LibjpegSrc}/jdsample.c
    ${LibjpegSrc}/jdtrans.c
    ${LibjpegSrc}/jerror.c
    ${LibjpegSrc}/jfdctflt.c
    ${LibjpegSrc}/jfdctfst.c
    ${LibjpegSrc}/jfdctint.c
    ${LibjpegSrc}/jidctflt.c
    ${LibjpegSrc}/jidctfst.c
    ${LibjpegSrc}/jidctint.c
    ${LibjpegSrc}/jmemansi.c
    ${LibjpegSrc}/jmemmgr.c
    ${LibjpegSrc}/jquant1.c
    ${LibjpegSrc}/jquant2.c
    ${LibjpegSrc}/jutils.c
    ${LibjpegSrc}/rdbmp.c
    ${LibjpegSrc}/rdcolmap.c
    ${LibjpegSrc}/rdgif.c
    ${LibjpegSrc}/rdppm.c
    ${LibjpegSrc}/rdrle.c
    ${LibjpegSrc}/rdswitch.c
    ${LibjpegSrc}/rdtarga.c
    ${LibjpegSrc}/transupp.c
    )

target_include_directories(libjpeg PUBLIC ${LibjpegSrc})
