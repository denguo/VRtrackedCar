/*******************************************************************************
* File Name: inter_verticalSync.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <inter_verticalSync.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START inter_verticalSync_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE	16
#endif
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);

/*******************************************************************************
* Function Name: inter_verticalSync_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void inter_verticalSync_Start(void)
{
    /* For all we know the interrupt is active. */
    inter_verticalSync_Disable();

    /* Set the ISR to point to the inter_verticalSync Interrupt. */
    inter_verticalSync_SetVector(inter_verticalSync_Interrupt);

    /* Set the priority. */
    inter_verticalSync_SetPriority(inter_verticalSync_INTC_PRIOR_NUMBER);

    /* Enable it. */
    inter_verticalSync_Enable();
}

/*******************************************************************************
* Function Name: inter_verticalSync_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void inter_verticalSync_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    inter_verticalSync_Disable();

    /* Set the ISR to point to the inter_verticalSync Interrupt. */
    inter_verticalSync_SetVector(address);

    /* Set the priority. */
    inter_verticalSync_SetPriority(inter_verticalSync_INTC_PRIOR_NUMBER);

    /* Enable it. */
    inter_verticalSync_Enable();
}

/*******************************************************************************
* Function Name: inter_verticalSync_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void inter_verticalSync_Stop(void) 
{
    /* Disable this interrupt. */
    inter_verticalSync_Disable();

    /* Set the ISR to point to the passive one. */
    inter_verticalSync_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: inter_verticalSync_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for inter_verticalSync.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(inter_verticalSync_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START inter_verticalSync_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: inter_verticalSync_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling inter_verticalSync_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use inter_verticalSync_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void inter_verticalSync_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + inter_verticalSync__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: inter_verticalSync_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress inter_verticalSync_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + inter_verticalSync__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: inter_verticalSync_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling inter_verticalSync_Start
*   or inter_verticalSync_StartEx will override any effect this method would have had. 
*	This method should only be called after inter_verticalSync_Start or 
*	inter_verticalSync_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void inter_verticalSync_SetPriority(uint8 priority) 
{
    *inter_verticalSync_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: inter_verticalSync_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 inter_verticalSync_GetPriority(void) 
{
    uint8 priority;


    priority = *inter_verticalSync_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: inter_verticalSync_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void inter_verticalSync_Enable(void) 
{
    /* Enable the general interrupt. */
    *inter_verticalSync_INTC_SET_EN = inter_verticalSync__INTC_MASK;
}

/*******************************************************************************
* Function Name: inter_verticalSync_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 inter_verticalSync_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*inter_verticalSync_INTC_SET_EN & inter_verticalSync__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: inter_verticalSync_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void inter_verticalSync_Disable(void) 
{
    /* Disable the general interrupt. */
    *inter_verticalSync_INTC_CLR_EN = inter_verticalSync__INTC_MASK;
}

/*******************************************************************************
* Function Name: inter_verticalSync_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void inter_verticalSync_SetPending(void) 
{
    *inter_verticalSync_INTC_SET_PD = inter_verticalSync__INTC_MASK;
}

/*******************************************************************************
* Function Name: inter_verticalSync_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void inter_verticalSync_ClearPending(void) 
{
    *inter_verticalSync_INTC_CLR_PD = inter_verticalSync__INTC_MASK;
}
