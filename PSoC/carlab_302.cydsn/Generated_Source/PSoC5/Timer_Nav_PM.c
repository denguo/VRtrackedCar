/*******************************************************************************
* File Name: Timer_Nav_PM.c
* Version 2.30
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Nav.h"
static Timer_Nav_backupStruct Timer_Nav_backup;


/*******************************************************************************
* Function Name: Timer_Nav_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Nav_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Nav_SaveConfig(void) 
{
    #if (!Timer_Nav_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            Timer_Nav_backup.TimerUdb = Timer_Nav_ReadCounter();
            Timer_Nav_backup.TimerPeriod = Timer_Nav_ReadPeriod();
            Timer_Nav_backup.InterruptMaskValue = Timer_Nav_STATUS_MASK;
            #if (Timer_Nav_UsingHWCaptureCounter)
                Timer_Nav_backup.TimerCaptureCounter = Timer_Nav_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Nav_backup.TimerUdb = Timer_Nav_ReadCounter();
            Timer_Nav_backup.InterruptMaskValue = Timer_Nav_STATUS_MASK;
            #if (Timer_Nav_UsingHWCaptureCounter)
                Timer_Nav_backup.TimerCaptureCounter = Timer_Nav_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Nav_ControlRegRemoved)
            Timer_Nav_backup.TimerControlRegister = Timer_Nav_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Nav_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Nav_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Nav_RestoreConfig(void) 
{   
    #if (!Timer_Nav_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_Nav_interruptState;

            Timer_Nav_WriteCounter(Timer_Nav_backup.TimerUdb);
            Timer_Nav_WritePeriod(Timer_Nav_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_Nav_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_Nav_STATUS_AUX_CTRL |= Timer_Nav_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_Nav_interruptState);
            Timer_Nav_STATUS_MASK =Timer_Nav_backup.InterruptMaskValue;
            #if (Timer_Nav_UsingHWCaptureCounter)
                Timer_Nav_SetCaptureCount(Timer_Nav_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Nav_WriteCounter(Timer_Nav_backup.TimerUdb);
            Timer_Nav_STATUS_MASK =Timer_Nav_backup.InterruptMaskValue;
            #if (Timer_Nav_UsingHWCaptureCounter)
                Timer_Nav_SetCaptureCount(Timer_Nav_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Nav_ControlRegRemoved)
            Timer_Nav_WriteControlRegister(Timer_Nav_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Nav_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Nav_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Nav_Sleep(void) 
{
    #if(!Timer_Nav_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_Nav_CTRL_ENABLE == (Timer_Nav_CONTROL & Timer_Nav_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Nav_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Nav_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Nav_Stop();
    Timer_Nav_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Nav_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Nav_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Nav_Wakeup(void) 
{
    Timer_Nav_RestoreConfig();
    #if(!Timer_Nav_ControlRegRemoved)
        if(Timer_Nav_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Nav_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
