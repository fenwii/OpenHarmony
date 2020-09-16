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

#include "hisoc/usb3.h"
#include "los_atomic.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define USB3_CTRL_REG_BASE IO_DEVICE_ADDR(CONFIG_HIUSB_XHCI_IOBASE)
#define REG_USB2_CTRL      0x0140

/* offset 0x140 */
#define USB2_UTMI_PCTRL         (0x1U << 15)
#define USB2_PHY_TEST_SRST_REQ  (0x1U << 14)
#define USB2_UTMI_CKSEL         (0x1U << 13)
#define USB2_UTMI_CKEN          (0x1U << 12)
#define USB2_REF_CKEN           (0x1U << 9)
#define USB2_BUS_CKEN           (0x1U << 8)
#define USB2_VCC_SRST_REQ       (0x1U << 3)
#define USB2_PHY_CKEN           (0x1U << 2)
#define USB2_PHY_PORT_TREQ      (0x1U << 1)
#define USB2_PHY_REQ            (0x1U << 0)

#define REG_GUSB3PIPECTL0       0xC2C0
#define PCS_SSP_SOFT_RESET      (0x1U << 31)
#define PORT_DISABLE_SUSPEND    (0x1U << 17)

#define REG_GCTL        0xC110
#define PORT_CAP_DIR    (0x3U << 12)
#define PORT_SET_HOST   (0x1U << 12)
#define PORT_SET_DEVICE (0x1U << 13)

#define GTXTHRCFG       0xC108
#define USB2_G_TXTHRCFG IO_DEVICE_ADDR(0x23100000)

#define GRXTHRCFG       0xC10C
#define USB2_G_RXTHRCFG IO_DEVICE_ADDR(0x23100000)

#define USB2_INNO_PHY_BASE_REG  IO_DEVICE_ADDR(0x10110000)
#define USB2_PHY_CLK_OUTPUT_REG 0x18
#define USB2_PHY_CLK_OUTPUT_VAL 0x0C

#define USB2_VBUS_IO_BASE_REG   IO_DEVICE_ADDR(0x10FF0000)
#define USB2_VBUS_IO_OFFSET     0x40
#define USB2_VBUS_IO_VAL        0x431

#define HS_HIGH_HEIGHT_TUNING_OFFSET    0x8
#define HS_HIGH_HEIGHT_TUNING_MASK      (0x7U << 4)
#define HS_HIGH_HEIGHT_TUNING_VAL       (0x5U << 4)

#define PRE_EMPHASIS_TUNING_OFFSET  0x0
#define PRE_EMPHASIS_TUNING_MASK    (0x7U << 0)
#define PRE_EMPHASIS_TUNING_VAL     (0x7U << 0)

#define PRE_EMPHASIS_STRENGTH_OFFSET    0x14
#define PRE_EMPHASIS_STRENGTH_MASK      (0x7U << 2)
#define PRE_EMPHASIS_STRENGTH_VAL       (0x3U << 2)

#define HS_SLEW_RATE_TUNING_OFFSET  0x74
#define HS_SLEW_RATE_TUNING_MASK    (0x7U << 1)
#define HS_SLEW_RATE_TUNING_VAL     (0x7U << 1)

#define DISCONNECT_TRIGGER_OFFSET   0x10
#define DISCONNECT_TRIGGER_MASK     (0xfU << 4)
#define DISCONNECT_TRIGGER_VAL      (0xdU << 4)

STATIC BOOL g_otgUsbdevStat = FALSE;
STATIC Atomic g_devOpenCnt = 0;

STATIC VOID OpenUtmi(VOID)
{
    UINT32 reg;

    /* open utmi pctrl */
    reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
    reg &= ~USB2_UTMI_PCTRL;
    WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
    LOS_Udelay(10); /* Delay 10us */

    /* open utmi cksel */
    reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
    reg &= ~USB2_UTMI_CKSEL;
    WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
    LOS_Udelay(10); /* Delay 10us */

    /* open utmi cken */
    reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
    reg |= USB2_UTMI_CKEN;
    WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
    LOS_Udelay(10); /* Delay 10us */
}

STATIC VOID CancelReset(VOID)
{
    UINT32 reg;

    /* cancel POR reset */
    reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
    reg &= ~USB2_PHY_REQ;
    WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
    LOS_Udelay(200); /* Delay 200us */

    /* cancel TPOR reset */
    reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
    reg &= ~USB2_PHY_PORT_TREQ;
    WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
    LOS_Udelay(200); /* Delay 200us */

    /* cancel vcc reset */
    reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
    reg &= ~USB2_VCC_SRST_REQ;
    WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
    LOS_Udelay(200); /* Delay 200us */
}

STATIC VOID Usb2ControllerConfig(VOID)
{
    UINT32 reg;

    reg = GET_UINT32(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
    reg |= PCS_SSP_SOFT_RESET;
    WRITE_UINT32(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
    LOS_Udelay(20); /* Delay 20us */

    reg = GET_UINT32(USB3_CTRL_REG_BASE + REG_GCTL);
    reg &= ~PORT_CAP_DIR;
    reg |= PORT_SET_HOST; /* [13:12] 01: Host; 10: Device; 11: OTG */
    WRITE_UINT32(reg, USB3_CTRL_REG_BASE + REG_GCTL);
    LOS_Udelay(20); /* Delay 20us */

    reg = GET_UINT32(USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
    reg &= ~PCS_SSP_SOFT_RESET;
    reg &= ~PORT_DISABLE_SUSPEND; /* disable suspend */
    WRITE_UINT32(reg, USB3_CTRL_REG_BASE + REG_GUSB3PIPECTL0);
    LOS_Udelay(20); /* Delay 20us */

    WRITE_UINT32(USB2_G_TXTHRCFG, USB3_CTRL_REG_BASE + GTXTHRCFG);
    WRITE_UINT32(USB2_G_RXTHRCFG, USB3_CTRL_REG_BASE + GRXTHRCFG);
    LOS_Udelay(20); /* Delay 20us */
}

VOID Usb2EyeConfig(VOID)
{
    UINT32 reg;

    /* HS eye height tuning */
    reg = GET_UINT32(USB2_INNO_PHY_BASE_REG + HS_HIGH_HEIGHT_TUNING_OFFSET);
    reg &= ~HS_HIGH_HEIGHT_TUNING_MASK;
    reg |= HS_HIGH_HEIGHT_TUNING_VAL;
    WRITE_UINT32(reg, USB2_INNO_PHY_BASE_REG + HS_HIGH_HEIGHT_TUNING_OFFSET);

    /* Pre-emphasis tuning */
    reg = GET_UINT32(USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_TUNING_OFFSET);
    reg &= ~PRE_EMPHASIS_TUNING_MASK;
    reg |= PRE_EMPHASIS_TUNING_VAL;
    WRITE_UINT32(reg, USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_TUNING_OFFSET);

    /* Pre-emphasis strength */
    reg = GET_UINT32(USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_STRENGTH_OFFSET);
    reg &= ~PRE_EMPHASIS_STRENGTH_MASK;
    reg |= PRE_EMPHASIS_STRENGTH_VAL;
    WRITE_UINT32(reg, USB2_INNO_PHY_BASE_REG + PRE_EMPHASIS_STRENGTH_OFFSET);

    /* HS driver slew rate tunning */
    reg = GET_UINT32(USB2_INNO_PHY_BASE_REG + HS_SLEW_RATE_TUNING_OFFSET);
    reg &= ~HS_SLEW_RATE_TUNING_MASK;
    reg |= HS_SLEW_RATE_TUNING_VAL;
    WRITE_UINT32(reg, USB2_INNO_PHY_BASE_REG + HS_SLEW_RATE_TUNING_OFFSET);

    /* HOST disconnects detection trigger point */
    reg = GET_UINT32(USB2_INNO_PHY_BASE_REG + DISCONNECT_TRIGGER_OFFSET);
    reg &= ~DISCONNECT_TRIGGER_MASK;
    reg |= DISCONNECT_TRIGGER_VAL;
    WRITE_UINT32(reg, USB2_INNO_PHY_BASE_REG + DISCONNECT_TRIGGER_OFFSET);
}

STATIC VOID HisiUsb3PhyPowerOn(VOID)
{
    UINT32 reg;

    if (LOS_AtomicIncRet(&g_devOpenCnt) == 1) {
        /* usb phy reset */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg |= USB2_PHY_TEST_SRST_REQ;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(100); /* Delay 100us */

        /* cancel usb phy srst */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg &= ~USB2_PHY_TEST_SRST_REQ;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(20); /* Delay 20us */

        /* usb2 vcc reset */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg |= USB2_VCC_SRST_REQ;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(200); /* Delay 200us */

        /* set inno phy output clock */
        WRITE_UINT32(USB2_PHY_CLK_OUTPUT_VAL, USB2_INNO_PHY_BASE_REG +
                USB2_PHY_CLK_OUTPUT_REG);
        LOS_Udelay(10); /* Delay 10us */

        /* open phy ref cken */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg |= USB2_PHY_CKEN;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(10); /* Delay 10us */

        /* open utmi */
        OpenUtmi();

        /* open controller ref cken */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg |= USB2_REF_CKEN;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(10); /* Delay 10us */

        /* open bus cken */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg |= USB2_BUS_CKEN;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(200); /* Delay 200us */

        /* cancel reset */
        CancelReset();

        /* usb2 test vbus using gpio */
        WRITE_UINT32(USB2_VBUS_IO_VAL, USB2_VBUS_IO_BASE_REG + USB2_VBUS_IO_OFFSET);
        LOS_Udelay(20); /* Delay 20us */

        /* USB2 Controller configs */
        Usb2ControllerConfig();

        /* USB2 eye config */
        Usb2EyeConfig();
    }
}

STATIC VOID HisiUsb3PhyPowerOff(VOID)
{
    UINT32 reg;

    if (LOS_AtomicDecRet(&g_devOpenCnt) == 0) {
        /* usb2 vcc reset */
        reg = GET_UINT32(CRG_REG_BASE + REG_USB2_CTRL);
        reg |= USB2_VCC_SRST_REQ;
        WRITE_UINT32(reg, CRG_REG_BASE + REG_USB2_CTRL);
        LOS_Udelay(200); /* Delay 200us */
    }
}

VOID HiUsb3StartHcd(VOID)
{
    HisiUsb3PhyPowerOn();
}
VOID HiUsb3StopHcd(VOID)
{
    HisiUsb3PhyPowerOff();
}

VOID HiUsb3Host2Device(VOID)
{
    UINT32 reg;

    reg = GET_UINT32(USB3_CTRL_REG_BASE + REG_GCTL);
    reg &= ~PORT_CAP_DIR;
    reg |= PORT_SET_DEVICE; /* [13:12] 01: Host; 10: Device; 11: OTG */
    WRITE_UINT32(reg, USB3_CTRL_REG_BASE + REG_GCTL);
    LOS_Udelay(20); /* Delay 20us */
}

BOOL HiUsbIsDeviceMode(VOID)
{
    return g_otgUsbdevStat;
}

VOID UsbOtgSwSetDeviceState(VOID)
{
    g_otgUsbdevStat = TRUE;
}

VOID UsbOtgSwClearDeviceState(VOID)
{
    g_otgUsbdevStat = FALSE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
