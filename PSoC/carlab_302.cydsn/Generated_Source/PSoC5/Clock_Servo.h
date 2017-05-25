/*******************************************************************************
* File Name: Clock_Servo.h
* Version 1.70
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_Clock_Servo_H)
#define CY_CLOCK_Clock_Servo_H

#include <cytypes.h>
#include <cyfitter.h>

/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

/***************************************
*        Function Prototypes
***************************************/

void Clock_Servo_Start(void) ;
void Clock_Servo_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_Servo_StopBlock(void) ;
#endif

void Clock_Servo_StandbyPower(uint8 state) ;
void Clock_Servo_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 Clock_Servo_GetDividerRegister(void) ;
void Clock_Servo_SetModeRegister(uint8 modeBitMask) ;
void Clock_Servo_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_Servo_GetModeRegister(void) ;
void Clock_Servo_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_Servo_GetSourceRegister(void) ;
#if defined(Clock_Servo__CFG3)
void Clock_Servo_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_Servo_GetPhaseRegister(void) ;
#endif

#define Clock_Servo_Enable()                       Clock_Servo_Start()
#define Clock_Servo_Disable()                      Clock_Servo_Stop()
#define Clock_Servo_SetDivider(clkDivider)         Clock_Servo_SetDividerRegister(clkDivider, 1)
#define Clock_Servo_SetDividerValue(clkDivider)    Clock_Servo_SetDividerRegister((clkDivider) - 1, 1)
#define Clock_Servo_SetMode(clkMode)               Clock_Servo_SetModeRegister(clkMode)
#define Clock_Servo_SetSource(clkSource)           Clock_Servo_SetSourceRegister(clkSource)
#if defined(Clock_Servo__CFG3)
#define Clock_Servo_SetPhase(clkPhase)             Clock_Servo_SetPhaseRegister(clkPhase)
#define Clock_Servo_SetPhaseValue(clkPhase)        Clock_Servo_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_Servo_CLKEN              (* (reg8 *) Clock_Servo__PM_ACT_CFG)
#define Clock_Servo_CLKEN_PTR          ((reg8 *) Clock_Servo__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_Servo_CLKSTBY            (* (reg8 *) Clock_Servo__PM_STBY_CFG)
#define Clock_Servo_CLKSTBY_PTR        ((reg8 *) Clock_Servo__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_Servo_DIV_LSB            (* (reg8 *) Clock_Servo__CFG0)
#define Clock_Servo_DIV_LSB_PTR        ((reg8 *) Clock_Servo__CFG0)
#define Clock_Servo_DIV_PTR            ((reg16 *) Clock_Servo__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_Servo_DIV_MSB            (* (reg8 *) Clock_Servo__CFG1)
#define Clock_Servo_DIV_MSB_PTR        ((reg8 *) Clock_Servo__CFG1)

/* Mode and source configuration register */
#define Clock_Servo_MOD_SRC            (* (reg8 *) Clock_Servo__CFG2)
#define Clock_Servo_MOD_SRC_PTR        ((reg8 *) Clock_Servo__CFG2)

#if defined(Clock_Servo__CFG3)
/* Analog clock phase configuration register */
#define Clock_Servo_PHASE              (* (reg8 *) Clock_Servo__CFG3)
#define Clock_Servo_PHASE_PTR          ((reg8 *) Clock_Servo__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_Servo_CLKEN_MASK         Clock_Servo__PM_ACT_MSK
#define Clock_Servo_CLKSTBY_MASK       Clock_Servo__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_Servo_SRC_SEL_MSK        Clock_Servo__CFG2_SRC_SEL_MASK
#define Clock_Servo_MODE_MASK          (~(Clock_Servo_SRC_SEL_MSK))

#if defined(Clock_Servo__CFG3)
/* CFG3 phase mask */
#define Clock_Servo_PHASE_MASK         Clock_Servo__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_Clock_Servo_H */


/* [] END OF FILE */
