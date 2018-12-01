/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "VolumeControl.h"
#include <Config.h>
#include <Application.h>
#include <ADC.h>
#include <DMA.h>
#include <Codec.h>
#include <USBFS.h>

#define ADC_MIN_READING_R         -2
#define ADC_MAX_READING_R         2047

#define ADC_READING_RANGE_R       (ADC_MAX_READING_R - ADC_MIN_READING_R)

/* ADC measurement status and result */
int16_t   adcSampleR = 0;
int16_t   adcSampleL = 0;

CY_ISR(DmaIntHandler)
{
    // Do nothing
}

void VolumeControlInit(void)
{
    /* Initialize ADC. Conversion is not enabled yet. */
    ADC_Start();

    /* Configure DMA source and destination locations to transfer from
    * ADC data register to memory variable.
    */
    DMA_Start((void *)ADC_SAR_CHAN0_RESULT_PTR, (void *)&adcSampleR);
    
    DMA_SetInterruptCallback(DmaIntHandler);

    /* Start ADC conversion. */
    ADC_StartConvert();
}

void VolumeControlService(void)
{
    static int32_t prevVol = 0;
    int32_t volume;
    uint8_t ret = 0;

    /* Process volume control only when USB bus is idle */
	if(USBFS_TRANS_STATE_IDLE == USBFS_transferState)
	{
        // Scale ADC reading to USBFS volume range
        volume = (adcSampleR - ADC_MIN_READING_R) * PC_VOLUME_MSB_MAX / ADC_READING_RANGE_R;

        /* Filter volume to be in the expected range */
		if((volume > PC_VOLUME_MSB_MIN) && (volume <= PC_VOLUME_MSB_MAX))
		{
			volume = (uint8)(((volume - PC_VOLUME_MSB_MIN) * CODEC_HP_VOLUME_MAX) / (PC_VOLUME_MSB_MAX - PC_VOLUME_MSB_MIN));	 
		}
		else
		{
			/* Set volume to 0 if the volume from PC is not in expected range */
			volume = 0;
		}

        if (volume != prevVol)
        {
            /* Update the codec volume */
            PRINTF("Volume knob change %ld -> %ld\n", prevVol, volume);
    		ret = Codec_AdjustBothHeadphoneVolume((uint8)volume);
            prevVol = volume;
        }
    }
}

/* [] END OF FILE */
