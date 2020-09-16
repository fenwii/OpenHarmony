/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*
 * Notes: version manager
 * 1. version large number means: new features update
 * 	e.g. v0.01 > v1.00
 * 2. version small number means: buglist fixed update
 * 	e.g. v1.01 > v1.02
 * 3. version time: update version date/time information
 */
static const char *usb_version[] = {
	/*
	 * "v0.01 2015-12-31 15:30",
	 * "v1.00 2016-01-08 15:00",
	 * "v1.01 2016-01-08 17:53", Add fmass sw check disconnect.
	 * "v1.02 2016-01-14 21:18", Add irq lock/unlock for xfer queue.
	 * "v1.03 2016-01-18 17:00", Add usbshell/usbtask name info.
	 * "v1.04 2016-02-16 10:03", Modify fmass memory allocate.
	 * "v1.05 2016-03-09 11:03", Modify usb memory allocate interface.
	 * "v2.00 2016-03-18 18:30", Fixed the license problem of usb driver.
	 * "v2.01 2016-03-24 11:00", Modify usb memory config by appalication & add hub port debounce.
	 * "v2.02 2016-04-11 14:10", Fixed mac connect usbdev fail case which sync to xiongmai.
	 * "v2.03 2016-04-19 20:10", Clear error/warning.
	 * "v2.04 2016-06-27 16:32", Clear error/warning.
	 * "v2.05 2016-07-05 20:49", Clear error/warning.
	 * "v2.06 2016-07-07 10:47", Fixed a bug of umass that cause reading and writing failure.
	 * "v2.07 2016-07-11 16:30", Update usbgadget-IF/dev-IF for fmass/fserial/fether.
	 * "v2.08 2016-07-14 19:44", Reduce the SAI.
	 * "v2.09 2016-08-20 10:12", Modify the mtx_assert.
	 * "v2.10 2016-09-18 10:28", Fixed a bug of f_mass that can not be identify.
	 * "v2.11 2017-02-08 10:59", Add the changes to support usb module cutting.
	 * "v2.12 2017-06-12 16:00", Add USB device 3.0 driver.
	 * "v2.12 2018-02-27 20:00", Modify that Multi device driven libraries become one.
	 * "v2.13 2018-11-29 11:00", Add urndis host.
	 * "v2.14 2018-12-04 15:30", Support dynamic switch device type.
	 * "v3.01 2019-05-09 10:32", Composite architecture optimization, refer to the Nuttx framework.
	 * "v3.02 2019-10-11 10:17", Serial architecture optimization, refer to the Nuttx framework.
	 * "v3.03 2019-10-12 10:45", DFU architecture optimization, refer to the Nuttx framework.
	 * "v3.04 2019-10-12 14:27", Device rndis architecture optimization, refer to the Nuttx framework.
	 */
	"v3.05 2019-11-20 10:40",   /* Add host uvc class, refer to OpenBSD. */
};

const char *
fetach_usbversion(void)
{
	return (usb_version[0]);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */