/*******************************************************************************
* File Name: inter_HE.c  
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
#include <inter_HE.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START inter_HE_intc` */

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
* Function Name: inter_HE_Start
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
void inter_HE_Start(void)
{
    /* For all we know the interrupt is active. */
    inter_HE_Disable();

    /* Set the ISR to point to the inter_HE Interrupt. */
    inter_HE_SetVector(inter_HE_Interrupt);

    /* Set the priority. */
    inter_HE_SetPriority(inter_HE_INTC_PRIOR_NUMBER);

    /* Enable it. */
    inter_HE_Enable();
}

/*******************************************************************************
* Function Name: inter_HE_StartEx
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
void inter_HE_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    inter_HE_Disable();

    /* Set the ISR to point to the inter_HE Interrupt. */
    inter_HE_SetVector(address);

    /* Set the priority. */
    inter_HE_SetPriority(inter_HE_INTC_PRIOR_NUMBER);

    /* Enable it. */
    inter_HE_Enable();
}

/*******************************************************************************
* Function Name: inter_HE_Stop
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
void inter_HE_Stop(void) 
{
    /* Disable this interrupt. */
    inter_HE_Disable();

    /* Set the ISR to point to the passive one. */
    inter_HE_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: inter_HE_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for inter_HE.
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
CY_ISR(inter_HE_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START inter_HE_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: inter_HE_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling inter_HE_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use inter_HE_StartEx instead.
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
void inter_HE_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + inter_HE__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: inter_HE_GetVector
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
cyisraddress inter_HE_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + inter_HE__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: inter_HE_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling inter_HE_Start
*   or inter_HE_StartEx will override any effect this method would have had. 
*	This method should only be called after inter_HE_Start or 
*	inter_HE_StartEx has been called. To set the initial
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
void inter_HE_SetPriority(uint8 priority) 
{
    *inter_HE_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: inter_HE_GetPriority
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
uint8 inter_HE_GetPriority(void) 
{
    uint8 priority;


    priority = *inter_HE_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: inter_HE_Enable
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
void inter_HE_Enable(void) 
{
    /* Enable the general interrupt. */
    *inter_HE_INTC_SET_EN = inter_HE__INTC_MASK;
}

/*******************************************************************************
* Function Name: inter_HE_GetState
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
uint8 inter_HE_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*inter_HE_INTC_SET_EN & inter_HE__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: inter_HE_Disable
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
void inter_HE_Disable(void) 
{
    /* Disable the general interrupt. */
    *inter_HE_INTC_CLR_EN = inter_HE__INTC_MASK;
}

/*******************************************************************************
* Function Name: inter_HE_SetPending
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
void inter_HE_SetPending(void) 
{
    *inter_HE_INTC_SET_PD = inter_HE__INTC_MASK;
}

/*******************************************************************************
* Function Name: inter_HE_ClearPending
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
void inter_HE_ClearPending(void) 
{
    *inter_HE_INTC_CLR_PD = inter_HE__INTC_MASK;
}
