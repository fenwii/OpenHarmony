#
# Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
# 
# This program is free software; you can redistribute  it and/or modify it
# under  the terms of  the GNU General  Public License as published by the
# Free Software Foundation;  either version 2 of the  License, or (at your
# option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
#

cflags-y     += -I$(srctree)/product/cipher/v2/api
cflags-y     += -I$(srctree)/product/cipher/v2/drv/platform
cflags-y     += -I$(srctree)/product/cipher/v2/drv/rng
cflags-y     += -I$(srctree)/product/cipher/v2/drv/rsa
cflags-y     += -I$(srctree)/product/cipher/v2/drv/compat
cflags-y     += -I$(srctree)/product/cipher/v2/drv/sm2
cflags-y     += -I$(srctree)/product/cipher/v2/drv/spacc
cflags-y     += -I$(srctree)/product/cipher/v2/drv/include

ccflags-y  += $(cflags-y)
HOSTCFLAGS += $(cflags-y)
CPPFLAGS   += $(cflags-y)

obj-y	+= v2/api/ree_mpi_cipher.o
obj-y	+= v2/api/ree_mpi_hash.o
obj-y	+= v2/api/ree_mpi_rsa.o
obj-y	+= v2/api/ree_mpi_rng.o

obj-y	+= v2/drv/platform/cipher_adapt.o
obj-y	+= v2/drv/drv_cipher_intf.o
obj-y	+= v2/drv/rng/drv_rng.o
obj-y	+= v2/drv/rsa/drv_rsa.o
obj-y	+= v2/drv/spacc/spacc_body.o
obj-y	+= v2/drv/spacc/spacc_intf.o
obj-y	+= v2/drv/compat/hal_otp.o
obj-y	+= v2/drv/compat/drv_klad.o
obj-y	+= v2/drv/compat/hi_drv_compat.o
