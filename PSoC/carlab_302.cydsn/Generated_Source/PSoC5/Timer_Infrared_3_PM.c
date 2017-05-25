/*******************************************************************************
* File Name: Timer_Infrared_3_PM.c
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

#include "Timer_Infrared_3.h"
static Timer_Infrared_3_backupStruct Timer_Infrared_3_backup;


/*******************************************************************************
* Function Name: Timer_Infrared_3_SaveConfig
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
*  Timer_Infrared_3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Infrared_3_SaveConfig(void) 
{
    #if (!Timer_Infrared_3_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            Timer_Infrared_3_backup.TimerUdb = Timer_Infrared_3_ReadCounter();
            Timer_Infrared_3_backup.TimerPeriod = Timer_Infrared_3_ReadPeriod();
            Timer_Infrared_3_backup.InterruptMaskValue = Timer_Infrared_3_STATUS_MASK;
            #if (Timer_Infrared_3_UsingHWCaptureCounter)
                Timer_Infrared_3_backup.TimerCaptureCounter = Timer_Infrared_3_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Infrared_3_backup.TimerUdb = Timer_Infrared_3_ReadCounter();
            Timer_Infrared_3_backup.InterruptMaskValue = Timer_Infrared_3_STATUS_MASK;
            #if (Timer_Infrared_3_UsingHWCaptureCounter)
                Timer_Infrared_3_backup.TimerCaptureCounter = Timer_Infrared_3_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Infrared_3_ControlRegRemoved)
            Timer_Infrared_3_backup.TimerControlRegister = Timer_Infrared_3_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Infrared_3_RestoreConfig
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
*  Timer_Infrared_3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Infrared_3_RestoreConfig(void) 
{   
    #if (!Timer_Infrared_3_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_Infrared_3_interruptState;

            Timer_Infrared_3_WriteCounter(Timer_Infrared_3_backup.TimerUdb);
            Timer_Infrared_3_WritePeriod(Timer_Infrared_3_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_Infrared_3_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_Infrared_3_STATUS_AUX_CTRL |= Timer_Infrared_3_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_Infrared_3_interruptState);
            Timer_Infrared_3_STATUS_MASK =Timer_Infrared_3_backup.InterruptMaskValue;
            #if (Timer_Infrared_3_UsingHWCaptureCounter)
                Timer_Infrared_3_SetCaptureCount(Timer_Infrared_3_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Infrared_3_WriteCounter(Timer_Infrared_3_backup.TimerUdb);
            Timer_Infrared_3_STATUS_MASK =Timer_Infrared_3_backup.InterruptMaskValue;
            #if (Timer_Infrared_3_UsingHWCaptureCounter)
                Timer_Infrared_3_SetCaptureCount(Timer_Infrared_3_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Infrared_3_ControlRegRemoved)
            Timer_Infrared_3_WriteControlRegister(Timer_Infrared_3_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Infrared_3_Sleep
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
*  Timer_Infrared_3_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Infrared_3_Sleep(void) 
{
    #if(!Timer_Infrared_3_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_Infrared_3_CTRL_ENABLE == (Timer_Infrared_3_CONTROL & Timer_Infrared_3_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Infrared_3_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Infrared_3_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Infrared_3_Stop();
    Timer_Infrared_3_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Infrared_3_Wakeup
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
*  Timer_Infrared_3_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Infrared_3_Wakeup(void) 
{
    Timer_Infrared_3_RestoreConfig();
    #if(!Timer_Infrared_3_ControlRegRemoved)
        if(Timer_Infrared_3_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Infrared_3_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
