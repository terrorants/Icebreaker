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
#ifndef VOLUME_CONTROL_H
#define VOLUME_CONTROL_H

#include <stdint.h>
    
extern int16_t adcSampleR;
extern int16_t adcSampleL;

void VolumeControlInit(void);
void VolumeControlService(void);
    
#endif /* VOLUME_CONTROL_H */

/* [] END OF FILE */
