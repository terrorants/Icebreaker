/*******************************************************************************
* File Name: RxDMA.h
* Version 1.0
*
* Description:
*  This file provides DMA channel defines and API function definitions.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_DMA_CHANNEL_RxDMA_H
#define CY_DMA_CHANNEL_RxDMA_H

#include "CyDMA.h"

    
/***************************************
*   Conditional Compilation Parameters
***************************************/

#define RxDMA_CHANNEL           (RxDMA__CHANNEL_NUMBER)
#define RxDMA_CHANNEL_MASK      ((uint32)(1UL << RxDMA_CHANNEL))


/***************************************
*        Function Prototypes
***************************************/

/* Functions specific to this DMA channel */
void RxDMA_Init(void);
void RxDMA_Start(void * srcAddress, void * dstAddress);

/* Inline functions that call global API functions */
static void   RxDMA_ChEnable(void);
static void   RxDMA_ChDisable(void);
static void   RxDMA_Trigger(void);
static void   RxDMA_SetPriority(int32 priority);
static int32  RxDMA_GetPriority(void);
static void   RxDMA_SetNextDescriptor(int32 descriptor);
static int32  RxDMA_GetNextDescriptor(void);
static void   RxDMA_SetConfiguration(int32 descriptor, const cydma_init_struct * config);
static void   RxDMA_ValidateDescriptor(int32 descriptor);
static uint32 RxDMA_GetDescriptorStatus(int32 descriptor);
static void   RxDMA_SetSrcAddress(int32 descriptor, void * srcAddress);
static void * RxDMA_GetSrcAddress(int32 descriptor);
static void   RxDMA_SetDstAddress(int32 descriptor, void * dstAddress);
static void * RxDMA_GetDstAddress(int32 descriptor);
static void   RxDMA_SetDataElementSize(int32 descriptor, uint32 dataElementSize);
static uint32 RxDMA_GetDataElementSize(int32 descriptor);
static void   RxDMA_SetNumDataElements(int32 descriptor, int32 numDataElements);
static int32  RxDMA_GetNumDataElements(int32 descriptor);
static void   RxDMA_SetSrcDstTransferWidth(int32 descriptor, uint32 transferWidth);
static uint32 RxDMA_GetSrcDstTransferWidth(int32 descriptor);
static void   RxDMA_SetAddressIncrement(int32 descriptor, uint32 addressIncrement);
static uint32 RxDMA_GetAddressIncrement(int32 descriptor);
static void   RxDMA_SetTriggerType(int32 descriptor, uint32 triggerType);
static uint32 RxDMA_GetTriggerType(int32 descriptor);
static void   RxDMA_SetTransferMode(int32 descriptor, uint32 transferMode);
static uint32 RxDMA_GetTransferMode(int32 descriptor);
static void   RxDMA_SetPreemptable(int32 descriptor, uint32 preemptable);
static uint32 RxDMA_GetPreemptable(int32 descriptor);
static void   RxDMA_SetPostCompletionActions(int32 descriptor, uint32 actions);
static uint32 RxDMA_GetPostCompletionAction(int32 descriptor);
static cydma_callback_t RxDMA_SetInterruptCallback(cydma_callback_t callback);
static cydma_callback_t RxDMA_GetInterruptCallback(void);


/*******************************************************************************
* Function Name: RxDMA_ChEnable
********************************************************************************
*
* Summary:
*  Enables the DMA channel. It is not necessary to call RxDMA_ChEnable()
*  because the RxDMA_Start() API calls this function, which is the
*  preferred method to begin the component operation.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  If this function is called before RxDMA_Start(), or RxDMA_Init()
*  or RxDMA_SetConfiguration(), and RxDMA_SetSrcAddress()
*  and RxDMA_SetDstAddress the operation of the DMA is 
*  undefined and could result in system data corruption. 
*
*******************************************************************************/
static CY_INLINE void RxDMA_ChEnable(void)
{
    CyDmaChEnable(RxDMA_CHANNEL);
}


/*******************************************************************************
* Function Name: RxDMA_ChDisable
********************************************************************************
*
* Summary:
*  Disables the DMA channel.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  If this function is called during a DMA transfer the transfer is aborted. 
*
*******************************************************************************/
static CY_INLINE void RxDMA_ChDisable(void)
{
    CyDmaChDisable(RxDMA_CHANNEL);
}


/*******************************************************************************
* Function Name: RxDMA_Trigger
********************************************************************************
*
* Summary:
*  Triggers the DMA channel, this is useful only for software triggers. This is
*  not needed when hardware triggers are used.
*
* Parameters:
*  None.
*                   
* Return:
*  None. 
*
*******************************************************************************/
static CY_INLINE void RxDMA_Trigger(void)
{
    CyDmaTrigger(RxDMA_CHANNEL);
}


/*******************************************************************************
* Function Name: RxDMA_SetPriority
********************************************************************************
*
* Summary:
*  Sets the priority for the channel.
*
* Parameters:
*  priority: Priority for channel. Priority can be 0,1,2, or 3.
*            0 is the highest priority.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called while the channel is enabled.
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetPriority(int32 priority)
{
    CyDmaSetPriority(RxDMA_CHANNEL, priority);
}


/*******************************************************************************
* Function Name: RxDMA_GetPriority
********************************************************************************
*
* Summary:
*  Gets the priority for the channel.
*
* Parameters:
*  None.
*                   
* Return:
*  Priority for channel. Priority can be 0,1,2, or 3. 0 is the highest priority.
*
*******************************************************************************/
static CY_INLINE int32 RxDMA_GetPriority(void)
{
    return (CyDmaGetPriority(RxDMA_CHANNEL));
}


/*******************************************************************************
* Function Name: RxDMA_SetNextDescriptor
********************************************************************************
*
* Summary:
*  Sets the descriptor that should be run the next time the channel is
*  triggered.
*
* Parameters:
*  descriptor: Next Descriptor to run (0 or 1).
*                   
* Side effect:
*  This function should not be called while the channel is enabled.
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetNextDescriptor(int32 descriptor)
{
    CyDmaSetNextDescriptor(RxDMA_CHANNEL, descriptor);
}


/*******************************************************************************
* Function Name: RxDMA_GetNextDescriptor
********************************************************************************
*
* Summary:
*  Returns the next descriptor that should be run, as set by 
*  RxDMA_SetNextDescriptor().
*
* Parameters:
*  None.
*                   
* Return:
*  Next Descriptor to run (0 or 1).
*
*******************************************************************************/
static CY_INLINE int32 RxDMA_GetNextDescriptor(void)
{
    return (CyDmaGetNextDescriptor(RxDMA_CHANNEL));
}


/*******************************************************************************
* Function Name: RxDMA_SetConfiguration
********************************************************************************
*
* Summary:
*  Sets configuration information for the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  config: Pointer to a configuration structure. Refer to cydma_init_struct
*          structure definition in CyDMA_P4.h or the component datasheet.
*                   
* Return:
*  None.
*
* Side effect:
*  The status register associated with the specified descriptor is reset to
*  zero after this function call. This function also validates the descriptor.
*  This function should not be called while the descriptor is active.
*  This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetConfiguration(int32 descriptor, const cydma_init_struct * config)
{
    CyDmaSetConfiguration(RxDMA_CHANNEL, descriptor, config);
}


/*******************************************************************************
* Function Name: RxDMA_ValidateDescriptor
********************************************************************************
*
* Summary:
*  Validates the specified descriptor after it has been invalidated.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  None. 
*
* Side effect:
*  The status register associated with the specified descriptor is reset to
*  zero after this function call. This function should not be called while the
*  descriptor is active. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
static CY_INLINE void RxDMA_ValidateDescriptor(int32 descriptor)
{
    CyDmaValidateDescriptor(RxDMA_CHANNEL, descriptor);
}


/*******************************************************************************
* Function Name: RxDMA_GetDescriptorStatus
********************************************************************************
*
* Summary:
*  Returns the status of the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Returns the contents of the specified descriptors status register. Refer to 
*  descriptor status register bit definitions in CyDMA_P4.h or the API
*  description in the DMA channel datasheet for more information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetDescriptorStatus(int32 descriptor)
{
    return (CyDmaGetDescriptorStatus(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetSrcAddress
********************************************************************************
*
* Summary:
*  Configures the source address for the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  srcAddress: Address of DMA transfer source.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetSrcAddress(int32 descriptor, void * srcAddress)
{
    CyDmaSetSrcAddress(RxDMA_CHANNEL, descriptor, srcAddress);
}


/*******************************************************************************
* Function Name: RxDMA_GetSrcAddress
********************************************************************************
*
* Summary:
*  Returns the source address for the specified descriptor, set by either 
*  RxDMA_Start() or RxDMA_SetSrcAddress().
*
* Parameters:
*  descriptor: Specifies descriptor (0 or 1) used by this function.
*                   
* Return:
*  Source address written to specified descriptor.
*
*******************************************************************************/
static CY_INLINE void * RxDMA_GetSrcAddress(int32 descriptor)
{
    return (CyDmaGetSrcAddress(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetDstAddress
********************************************************************************
*
* Summary:
*  Configures the destination address for the specified descriptor.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  dstAddress: Address of DMA transfer destination.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetDstAddress(int32 descriptor, void * dstAddress)
{
    CyDmaSetDstAddress(RxDMA_CHANNEL, descriptor, dstAddress);
}


/*******************************************************************************
* Function Name: RxDMA_GetDstAddress
********************************************************************************
*
* Summary:
*  Returns the destination address for the specified descriptor, set by either 
*  RxDMA_Start() or RxDMA_SetDstAddress().
*
* Parameters:
*  descriptor: Specifies descriptor (0 or 1) used by this function.
*                   
* Return:
*  Destination address written to specified descriptor.
*
*******************************************************************************/
static CY_INLINE void * RxDMA_GetDstAddress(int32 descriptor)
{
    return (CyDmaGetDstAddress(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetDataElementSize
********************************************************************************
*
* Summary:
*  Sets the data element size for the specified descriptor.
*
* Parameters:
*  descriptor:      Descriptor (0 or 1) modified by this function.
*  dataElementSize: Specifies the size of the data element. The DMA transfer
*                   engine transfers one data element at a time. How these
*                   transfers occur is controlled by the transfer mode.
*                   Refer to the API bit field definitions in CyDMA_P4.h or API
*                   description in the DMA channel datasheet for the parameter
*                   options.
*
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetDataElementSize(int32 descriptor, uint32 dataElementSize)
{
    CyDmaSetDataElementSize(RxDMA_CHANNEL, descriptor, dataElementSize);
}


/*******************************************************************************
* Function Name: RxDMA_GetDataElementSize
********************************************************************************
*
* Summary:
*  Returns the data element size configured for the specified descriptor, set by
*  RxDMA_SetDataElementSize() or RxDMA_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  The size of the data element. The DMA transfer engine transfers one data
*  element at a time. How these transfers occur is controlled by the transfer
*  mode. Refer to the API bit field definitions in CyDMA_P4.h or the API 
*  description in the DMA channel datasheet for more information.
*
* Note:
*  The size of the source and destination can be configured to use the
*  data element size, or a Word, this is set in RxDMA_SetSrcDstTransferWidth().
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetDataElementSize(int32 descriptor)
{
    return (CyDmaGetDataElementSize(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetNumDataElements
********************************************************************************
*
* Summary:
*  Sets the number of data elements to transfer for specified descriptor.
*
* Parameters:
*  descriptor:      Descriptor (0 or 1) modified by this function.
*  numDataElements: Total number of data elements this descriptor transfers.
*                   Valid ranges are 1 to 65536.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetNumDataElements(int32 descriptor, int32 numDataElements)
{
    CyDmaSetNumDataElements(RxDMA_CHANNEL, descriptor, numDataElements);
}


/*******************************************************************************
* Function Name: RxDMA_GetNumDataElements
********************************************************************************
*
* Summary:
*  Returns the number of data elements to be transferred. Only reflects the
*  value written by RxDMA_SetNumDataElements() or RxDMA_SetConfiguration().
*  This does not reflect how many elements have been transferred. For that
*  information use the RxDMA_GetDescriptorStatus() function.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Number of data elements to transfer.
*
*******************************************************************************/
static CY_INLINE int32 RxDMA_GetNumDataElements(int32 descriptor)
{
    return (CyDmaGetNumDataElements(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetSrcDstTransferWidth
********************************************************************************
*
* Summary:
*  Sets the width of the source and destination. The DMA can either read and
*  write data from the source and destination at the size specified by
*  RxDMA_SetDataElementSize() or by a word (4bytes). This also determines how
*  many bytes the addresses are incremented if increment source and destination
*  address are turned on.
*
* Parameters:
*  descriptor:    Descriptor (0 or 1) modified by this function.
*  transferWidth: Specifies the source and destination widths. Refer to the API
*                 bit field definitions in CyDMA_P4.h or the API description in
*                 the DMA channel datasheet for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetSrcDstTransferWidth(int32 descriptor, uint32 transferWidth)
{
    CyDmaSetSrcDstTransferWidth(RxDMA_CHANNEL, descriptor, transferWidth);
}


/*******************************************************************************
* Function Name: RxDMA_GetSrcDstTransferWidth
********************************************************************************
*
* Summary:
*  Returns the width of the source and destination, as set by 
*  RxDMA_SetSrcDstTransferWidth() or RxDMA_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Width of source and destination. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetSrcDstTransferWidth(int32 descriptor)
{
    return (CyDmaGetSrcDstTransferWidth(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetAddressIncrement
********************************************************************************
*
* Summary:
*  Sets whether the source or destination addresses are incremented after the
*  transfer of each data element. The amount that the source and destination
*  address are incremented is determined by the RxDMA_SetSrcDstTransferWidth()
*  function. The addresses will either be incremented by the data element size
*  or by a word (4 bytes).
*
* Parameters:
*  descriptor:       Descriptor (0 or 1) modified by this function.
*  addressIncrement: Address increment settings. Refer to the API bit field
*                    definitions in CyDMA_P4.h or the API description in the DMA
*                    channel datasheet for the parameter options.
*    
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetAddressIncrement(int32 descriptor, uint32 addressIncrement)
{
    CyDmaSetAddressIncrement(RxDMA_CHANNEL, descriptor, addressIncrement);
}


/*******************************************************************************
* Function Name: RxDMA_GetAddressIncrement
********************************************************************************
*
* Summary:
*  Returns address increment settings as set by RxDMA_SetAddressIncrement()
*  or RxDMA_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Address increment settings. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetAddressIncrement(int32 descriptor)
{
    return (CyDmaGetAddressIncrement(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetTriggerType
********************************************************************************
*
* Summary:
*  Sets the type of input trigger for the DMA For level sensitive triggers sets
*  how long the DMA waits for the trigger to go low (deactivate) before
*  triggering the channel again.
*
* Parameters:
*  descriptor:  Descriptor (0 or 1) modified by this function.
*  triggerType: Type of DMA trigger. Refer to the API bit field definitions in
*               CyDMA_P4.h or the API description in the DMA channel datasheet
*               for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetTriggerType(int32 descriptor, uint32 triggerType)
{
    CyDmaSetTriggerType(RxDMA_CHANNEL, descriptor, triggerType);
}


/*******************************************************************************
* Function Name: RxDMA_GetTriggerType
********************************************************************************
*
* Summary:
*  Returns the trigger deactivation settings as set by RxDMA_SetTriggerType()
*  or RxDMA_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Trigger deactivation settings. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetTriggerType(int32 descriptor)
{
    return (CyDmaGetTriggerType(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetTransferMode
********************************************************************************
*
* Summary:
*  Sets the DMA transfer mode. This determines how the DMA reacts to each trigger
*  event.
*
* Parameters:
*  descriptor:   Descriptor (0 or 1) modified by this function.
*  transferMode: Specifies the DMA transfer mode settings. Refer to the API bit
*                field definitions in CyDMA_P4.h or the API description in the
*                DMA channel datasheet for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetTransferMode(int32 descriptor, uint32 transferMode)
{
    CyDmaSetTransferMode(RxDMA_CHANNEL, descriptor, transferMode);
}


/*******************************************************************************
* Function Name: RxDMA_GetTransferMode
********************************************************************************
*
* Summary:
*  Returns the transfer mode for the specified descriptor as set by 
*  RxDMA_SetTransferMode() or RxDMA_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  DMA transfer mode settings. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetTransferMode(int32 descriptor)
{
    return (CyDmaGetTransferMode(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetPreemptable
********************************************************************************
*
* Summary:
*  Determines if the descriptor is preemptable.
*
* Parameters:
*  descriptor:  Descriptor (0 or 1) modified by this function.
*  preemptable: Descriptor preemption settings. Refer to the API bit field
*               definitions in CyDMA_P4.h or the API description in the DMA 
*               channel datasheet for the parameter options.
*                   
* Return:
*  None.
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetPreemptable(int32 descriptor, uint32 preemptable)
{
    CyDmaSetPreemptable(RxDMA_CHANNEL, descriptor, preemptable);
}


/*******************************************************************************
* Function Name: RxDMA_GetPreemptable
********************************************************************************
*
* Summary:
*  Returns whether or not the descriptor is preemptable.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Descriptor preemption setting. Refer to the API bit field definitions in
*  CyDMA_P4.h or the API description in the DMA channel datasheet for more
*  information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetPreemptable(int32 descriptor)
{
    return (CyDmaGetPreemptable(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetPostCompletionActions
********************************************************************************
*
* Summary:
*  Determines what occurs after a descriptor completes.
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*  actions:    Specifies descriptor post completion actions. Refer to the API
*              bit field definitions in CyDMA_P4.h or the API description in the
*              DMA channel datasheet for the parameter options.
*                   
* Return:
*  None.  
*
* Side effect:
*  This function should not be called when the specified descriptor is active
*  in the DMA transfer engine. This can be checked by calling CyDmaGetStatus(). 
*
*******************************************************************************/
static CY_INLINE void RxDMA_SetPostCompletionActions(int32 descriptor, uint32 actions)
{
    CyDmaSetPostCompletionActions(RxDMA_CHANNEL, descriptor, actions);
}


/*******************************************************************************
* Function Name: RxDMA_GetPostCompletionAction
********************************************************************************
*
* Summary:
*  Returns the post descriptor action settings as set by 
*  RxDMA_SetPostCompletionActions() or RxDMA_SetConfiguration().
*
* Parameters:
*  descriptor: Descriptor (0 or 1) modified by this function.
*                   
* Return:
*  Post descriptor actions. Refer to the API bit field definitions in CyDMA_P4.h
*  or the API description in the DMA channel datasheet for more information.
*
*******************************************************************************/
static CY_INLINE uint32 RxDMA_GetPostCompletionAction(int32 descriptor)
{
    return (CyDmaGetPostCompletionActions(RxDMA_CHANNEL, descriptor));
}


/*******************************************************************************
* Function Name: RxDMA_SetInterruptCallback
********************************************************************************
*
* Summary:
*  Sets a user defined callback function to be called by the DMA interrupt. The
*  function should contain code to process the interrupt request for the 
*  associated DMA channel.
*
* Parameters:
*  callback: Pointer to the user defined callback function.
*
* Return:
*  Pointer to the function previously set for the specified channel. 
*
*******************************************************************************/
static CY_INLINE cydma_callback_t RxDMA_SetInterruptCallback(cydma_callback_t callback)
{
    return (CyDmaSetInterruptCallback(RxDMA_CHANNEL, callback));
}


/*******************************************************************************
* Function Name: RxDMA_GetInterruptCallback
********************************************************************************
*
* Summary:
*  Returns the pointer to the interrupt callback function for the specified DMA
*  channel.
*
* Parameters:
*  None.
*
* Return:
*  Callback function pointer for the specified channel.
*
*******************************************************************************/
static CY_INLINE cydma_callback_t RxDMA_GetInterruptCallback(void)
{    
    return (CyDmaGetInterruptCallback(RxDMA_CHANNEL));
}


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 RxDMA_initVar;


/***************************************
*    Initial Parameter Constants
***************************************/

#define RxDMA_CHANNEL_CFG           (0x00000000u)
#define RxDMA_DESCR0_CFG            (0x0120047Fu)
#define RxDMA_DESCR1_CFG            (0x00000000u)


#endif /* CY_DMA_CHANNEL_RxDMA_H */


/* [] END OF FILE */
