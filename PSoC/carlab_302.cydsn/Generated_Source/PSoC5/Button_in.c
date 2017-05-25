/*******************************************************************************
* File Name: Button_In.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "Button_In.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button_In__PORT == 15 && (Button_In__MASK & 0xC0))

/*******************************************************************************
* Function Name: Button_In_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void Button_In_Write(uint8 value) 
{
    uint8 staticBits = Button_In_DR & ~Button_In_MASK;
    Button_In_DR = staticBits | ((value << Button_In_SHIFT) & Button_In_MASK);
}


/*******************************************************************************
* Function Name: Button_In_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void Button_In_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Button_In_0, mode);
}


/*******************************************************************************
* Function Name: Button_In_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Button_In_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Button_In_Read(void) 
{
    return (Button_In_PS & Button_In_MASK) >> Button_In_SHIFT;
}


/*******************************************************************************
* Function Name: Button_In_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Button_In_ReadDataReg(void) 
{
    return (Button_In_DR & Button_In_MASK) >> Button_In_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Button_In_INTSTAT) 

    /*******************************************************************************
    * Function Name: Button_In_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Button_In_ClearInterrupt(void) 
    {
        return (Button_In_INTSTAT & Button_In_MASK) >> Button_In_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
