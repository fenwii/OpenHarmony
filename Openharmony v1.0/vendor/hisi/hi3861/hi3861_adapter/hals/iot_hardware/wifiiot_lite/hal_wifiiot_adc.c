#include "hi_adc.h"
#include "hal_wifiiot_adc.h"

unsigned int HalAdcRead(HalWifiIotAdcChannelIndex channel, unsigned short *data, HalWifiIotAdcEquModelSel equModel,
                        HalWifiIotAdcCurBais curBais, unsigned short rstCnt)
{
    return hi_adc_read((hi_adc_channel_index)channel, (hi_u16*)data, (hi_adc_equ_model_sel)equModel,
                       (hi_adc_cur_bais)curBais, (hi_u16)rstCnt);
}
