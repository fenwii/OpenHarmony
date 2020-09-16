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
#include "linux/delay.h"
#include "board.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* offset 0x140 */
#define USB2_CTRL               IO_ADDRESS(CRG_REG_BASE + 0x140)
#define USB2_CRG_DEFAULT_VAL    0x3B2F
#define USB2_UTMI_CKEN          (0x1U << 12)
#define USB2_PHY_APB_CKEN       (0x1U << 11)
#define USB2_REF_CKEN           (0x1U << 9)
#define USB2_BUS_CKEN           (0x1U << 8)
#define USB2_PHY_PLL_CKEN       (0x1U << 4)
#define USB2_PHY_XTAL_CKEN      (0x1U << 2)
#define USB2_FREECLK_CKSEL      (0x1U << 13)
#define USB2_PHY_APB_RST        (0x1U << 10)
#define USB2_VCC_SRST_REQ       (0x1U << 3)
#define USB2_PHY_REQ            (0x1U << 0)
#define USB2_PHY_PORT_TREQ      (0x1U << 1)

#define CTRL_BASE_REG           IO_DEVICE_ADDR(0x10030000)
#define GTXTHRCFG               IO_ADDRESS(CTRL_BASE_REG + 0xC108)
#define GRXTHRCFG               IO_ADDRESS(CTRL_BASE_REG + 0xC10C)
#define REG_GCTL                IO_ADDRESS(CTRL_BASE_REG + 0xC110)
#define REG_GUSB3PIPECTL0       IO_ADDRESS(CTRL_BASE_REG + 0xC2C0)
#define PCS_SSP_SOFT_RESET      (0x1U << 31)

#define PORT_CAP_DIR            (0x3U << 12)
#define PORT_SET_HOST           (0x1U << 12)
#define PORT_SET_DEVICE         (0x1U << 13)
#define PORT_DISABLE_SUSPEND    (0x1U << 17)

#define USB2_G_TXTHRCFG         0x23100000
#define USB2_G_RXTHRCFG         0x23100000

/* PHY base register */
#define USB2_PHY_BASE_REG       IO_DEVICE_ADDR(0x100D0000)
#define RG_PLL_EN_MASK          0x0003U
#define RG_PLL_EN_VAL           0x0003U
#define RG_PLL_OFFSET           0x0014

#define USB2_VBUS_IO_BASE_REG   IO_DEVICE_ADDR(0x100C0000)
#define USB2_VBUS_IO_OFFSET     0x7C
#define USB_VBUS_IO_CONFIG_VAL  0x0531

#define USB_PWREN_CONFIG_REG    IO_DEVICE_ADDR(0x100C0080)
#define USB_PWREN_CONFIG_VAL    0x1

/* PHY eye config */
#define HIXVP_PHY_ANA_CFG_0_OFFSET          0x00
#define HIXVP_PHY_PRE_DRIVE_MASK            (0xFU << 24)
#define HIXVP_PHY_PRE_DRIVE_VAL             (0x4U << 24)
#define HIXVP_PHY_ANA_CFG_2_OFFSET          0x08
#define HIXVP_PHY_TX_TEST_BIT               (0x1U << 20)
#define HIXVP_PHY_DISCONNECT_REFERENCE_MASK (0x7U << 16)
#define HIXVP_PHY_DISCONNECT_REFERENCE_VAL  (0x2U << 16)
#define HIXVP_PHY_ANA_CFG_4_OFFSET          0x10
#define HIXVP_PHY_TX_REFERENCE_MASK         (0x7U << 4)
#define HIXVP_PHY_TX_REFERENCE_VAL          (0x5U << 4)
#define HIXVP_PHY_SQUELCH_MASK              (0x7U << 0)
#define HIXVP_PHY_SQUELCH_VAL               (0x5U << 0)

/* PHY trim config */
#define USB_TRIM_BASE_REG                   IO_DEVICE_ADDR(0x12028004)
#define USB_TRIM_VAL_MASK                   0x001FU
#define USB_TRIM_VAL_MIN                    0x0009
#define USB_TRIM_VAL_MAX                    0x001D
#define USB2_TRIM_OFFSET                    0x0008
#define USB2_TRIM_MASK                      0x1F00U
#define USB2_TRIM_VAL(a)                    (((a) << 8) & USB2_TRIM_MASK)
#define USB2_TRIM_DEFAULT_VAL               0x000EU

/* PHY svb config */
#define USB_SVB_BASE_REG                    IO_DEVICE_ADDR(0x12020158)
#define USB_SVB_OFFSET                      0x00
#define USB_SVB_MASK                        (0x0FU << 24)
#define USB_SVB_PREDEV_5_MIN                0x2BC
#define USB_SVB_PREDEV_5_MAX_4_MIN          0x32A
#define USB_SVB_PREDEV_4_MAX_3_MIN          0x398
#define USB_SVB_PREDEV_3_MAX_2_MIN          0x3CA
#define USB_SVB_PREDEV_2_MAX                0x44C
#define USB_SVB_PREDEV_5_PHY_VAL            (0x05U << 24)
#define USB_SVB_PREDEV_4_PHY_VAL            (0x04U << 24)
#define USB_SVB_PREDEV_3_PHY_VAL            (0x03U << 24)
#define USB_SVB_PREDEV_2_PHY_VAL            (0x02U << 24)

#define VBUS_CONFIG_WAIT_TIME               20
#define CTRL_CONFIG_WAIT_TIME               20
#define MODE_SWITCH_WAIT_TIME               20
#define USB_PHY_OFF_WAIT_TIME               2000
#define PLL_CONFIG_WAIT_TIME                2000
#define USB2_CTRL_CONFIG_WAIT_TIME          200

STATIC BOOL g_otgUsbdevStat = FALSE;

STATIC VOID UsbEyeConfig(VOID)
{
    UINT32 reg;
    /* HSTX pre-drive strength */
    reg = GET_UINT32(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_0_OFFSET);
    reg &= ~HIXVP_PHY_PRE_DRIVE_MASK;
    reg |= HIXVP_PHY_PRE_DRIVE_VAL;
    WRITE_UINT32(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_0_OFFSET);

    /* TX test bit */
    reg = GET_UINT32(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);
    reg |= HIXVP_PHY_TX_TEST_BIT;
    WRITE_UINT32(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);

    /* Disconnect reference voltage sel */
    reg = GET_UINT32(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);
    reg &= ~HIXVP_PHY_DISCONNECT_REFERENCE_MASK;
    reg |= HIXVP_PHY_DISCONNECT_REFERENCE_VAL;
    WRITE_UINT32(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_2_OFFSET);

    /* TX reference voltage sel */
    reg = GET_UINT32(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);
    reg &= ~HIXVP_PHY_TX_REFERENCE_MASK;
    reg |= HIXVP_PHY_TX_REFERENCE_VAL;
    WRITE_UINT32(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);

    /* Squelch voltage config */
    reg = GET_UINT32(USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);
    reg &= ~HIXVP_PHY_SQUELCH_MASK;
    reg |= HIXVP_PHY_SQUELCH_VAL;
    WRITE_UINT32(reg, USB2_PHY_BASE_REG + HIXVP_PHY_ANA_CFG_4_OFFSET);
}

VOID UsbTrimConfig(VOID)
{
    UINT32 ret, reg, trimVal;

    ret = GET_UINT32(USB_TRIM_BASE_REG);
    trimVal = ret & USB_TRIM_VAL_MASK;  /* get usb trim value */
    reg = GET_UINT32(USB2_PHY_BASE_REG + USB2_TRIM_OFFSET);
    reg &= ~USB2_TRIM_MASK;
    /* set trim value to HiXVPV100 phy */
    if ((trimVal >= USB_TRIM_VAL_MIN) && (trimVal <= USB_TRIM_VAL_MAX)) {
        reg |= USB2_TRIM_VAL(trimVal);
    } else {
        reg |= USB2_TRIM_VAL(USB2_TRIM_DEFAULT_VAL);
    }

    WRITE_UINT32(reg, USB2_PHY_BASE_REG + USB2_TRIM_OFFSET);
}

VOID UsbSvbConfig(VOID)
{
    UINT32 ret, reg;

    ret = GET_UINT32(USB_SVB_BASE_REG);
    reg = GET_UINT32(USB2_PHY_BASE_REG + USB_SVB_OFFSET);
    reg &= ~USB_SVB_MASK;
    /* set svb value to HiXVPV100 phy */
    if ((ret >= USB_SVB_PREDEV_5_MIN) && (ret < USB_SVB_PREDEV_5_MAX_4_MIN)) {
        reg |= USB_SVB_PREDEV_5_PHY_VAL;
    } else if ((ret >= USB_SVB_PREDEV_5_MAX_4_MIN) && (ret < USB_SVB_PREDEV_4_MAX_3_MIN)) {
        reg |= USB_SVB_PREDEV_4_PHY_VAL;
    } else if ((ret >= USB_SVB_PREDEV_4_MAX_3_MIN) && (ret <= USB_SVB_PREDEV_3_MAX_2_MIN)) {
        reg |= USB_SVB_PREDEV_3_PHY_VAL;
    } else if ((ret > USB_SVB_PREDEV_3_MAX_2_MIN) && (ret <= USB_SVB_PREDEV_2_MAX)) {
        reg |= USB_SVB_PREDEV_2_PHY_VAL;
    } else {
        reg |= USB_SVB_PREDEV_4_PHY_VAL;
    }

    WRITE_UINT32(reg, USB2_PHY_BASE_REG + USB_SVB_OFFSET);
}

STATIC VOID UsbVbusConfig(VOID)
{
    WRITE_UINT32(USB_VBUS_IO_CONFIG_VAL, USB2_VBUS_IO_BASE_REG + USB2_VBUS_IO_OFFSET);
    udelay(VBUS_CONFIG_WAIT_TIME);
}

STATIC VOID UsbCrgC(VOID)
{
    UINT32 reg;

    reg = USB_PWREN_CONFIG_VAL;
    WRITE_UINT32(reg, USB_PWREN_CONFIG_REG);

    /* set usb2 CRG default val */
    reg = USB2_CRG_DEFAULT_VAL;
    WRITE_UINT32(reg, USB2_CTRL);
    udelay(USB2_CTRL_CONFIG_WAIT_TIME);

    /* open UTMI clk */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_UTMI_CKEN;
    WRITE_UINT32(reg, USB2_CTRL);

    /* open phy apb clk */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_PHY_APB_CKEN;
    WRITE_UINT32(reg, USB2_CTRL);

    /* open ctrl ref clk */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_REF_CKEN;
    WRITE_UINT32(reg, USB2_CTRL);

    /* open bus clk */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_BUS_CKEN;
    WRITE_UINT32(reg, USB2_CTRL);

    /* open phy pll clk */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_PHY_PLL_CKEN;
    WRITE_UINT32(reg, USB2_CTRL);

    /* open phy xtal clk */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_PHY_XTAL_CKEN;
    WRITE_UINT32(reg, USB2_CTRL);

    /* freeclk_cksel_free */
    reg = GET_UINT32(USB2_CTRL);
    reg |= USB2_FREECLK_CKSEL;
    WRITE_UINT32(reg, USB2_CTRL);
    udelay(USB2_CTRL_CONFIG_WAIT_TIME);

    /* release phy apb */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_PHY_APB_RST;
    WRITE_UINT32(reg, USB2_CTRL);
    udelay(USB2_CTRL_CONFIG_WAIT_TIME);

    /* por noreset */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_PHY_REQ;
    WRITE_UINT32(reg, USB2_CTRL);

    reg = GET_UINT32(USB2_PHY_BASE_REG + RG_PLL_OFFSET);
    reg &= ~RG_PLL_EN_MASK;
    reg |= RG_PLL_EN_VAL;
    WRITE_UINT32(reg, USB2_PHY_BASE_REG + RG_PLL_OFFSET);
    udelay(PLL_CONFIG_WAIT_TIME);

    /* cancel TPOR */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_PHY_PORT_TREQ;
    WRITE_UINT32(reg, USB2_CTRL);
    udelay(USB2_CTRL_CONFIG_WAIT_TIME);

    /* vcc reset */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_VCC_SRST_REQ;
    WRITE_UINT32(reg, USB2_CTRL);
}

STATIC VOID UsbCtrlC(VOID)
{
    UINT32 reg;

    reg = GET_UINT32(REG_GUSB3PIPECTL0);
    reg |= PCS_SSP_SOFT_RESET;
    WRITE_UINT32(reg, REG_GUSB3PIPECTL0);
    udelay(CTRL_CONFIG_WAIT_TIME);

    reg = GET_UINT32(REG_GCTL);
    reg &= ~PORT_CAP_DIR;
    reg |= PORT_SET_HOST; /* [13:12] 01: Host; 10: Device; 11: OTG */
    WRITE_UINT32(reg, REG_GCTL);
    udelay(CTRL_CONFIG_WAIT_TIME);

    reg = GET_UINT32(REG_GUSB3PIPECTL0);
    reg &= ~PCS_SSP_SOFT_RESET;
    reg &= ~PORT_DISABLE_SUSPEND;  /* disable suspend */
    WRITE_UINT32(reg, REG_GUSB3PIPECTL0);
    udelay(CTRL_CONFIG_WAIT_TIME);

    WRITE_UINT32(USB2_G_TXTHRCFG, GTXTHRCFG);
    WRITE_UINT32(USB2_G_RXTHRCFG, GRXTHRCFG);
    udelay(CTRL_CONFIG_WAIT_TIME);
}

VOID HisiUsbPhyOn(VOID)
{
    UsbVbusConfig();
    UsbCrgC();
    UsbCtrlC();

    /* USB2 eye config */
    UsbEyeConfig();

    /* USB2 trim config */
    UsbTrimConfig();

    /* USB2 svb config */
    UsbSvbConfig();
}

VOID HisiUsbPhyOff(VOID)
{
    UINT32 reg;

    /* por noreset */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_PHY_REQ;
    WRITE_UINT32(reg, USB2_CTRL);
    udelay(USB_PHY_OFF_WAIT_TIME);
    /* cancel TPOR */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_PHY_PORT_TREQ;
    WRITE_UINT32(reg, USB2_CTRL);
    udelay(USB_PHY_OFF_WAIT_TIME);
    /* vcc reset */
    reg = GET_UINT32(USB2_CTRL);
    reg &= ~USB2_VCC_SRST_REQ;
    WRITE_UINT32(reg, USB2_CTRL);
}

VOID HiUsb3StartHcd(VOID)
{
    HisiUsbPhyOn();
}

VOID HiUsb3StopHcd(VOID)
{
    HisiUsbPhyOff();
}

VOID HiUsb3Host2Device(VOID)
{
    UINT32 reg;

    reg = GET_UINT32(REG_GCTL);
    reg &= ~PORT_CAP_DIR; /* [13:12] Clear Mode Bits */
    reg |= PORT_SET_DEVICE; /* [13:12] 01: Host; 10: Device; 11: OTG */
    WRITE_UINT32(reg, REG_GCTL);
    udelay(MODE_SWITCH_WAIT_TIME);
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
