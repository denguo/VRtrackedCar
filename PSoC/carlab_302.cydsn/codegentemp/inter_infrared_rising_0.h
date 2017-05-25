/*******************************************************************************
* File Name: inter_infrared_rising_0.h
* Version 1.60
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__inter_infrared_rising_0_INTC_H__)
#define __inter_infrared_rising_0_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void inter_infrared_rising_0_Start(void);
void inter_infrared_rising_0_StartEx(cyisraddress address);
void inter_infrared_rising_0_Stop(void) ;

CY_ISR_PROTO(inter_infrared_rising_0_Interrupt);

void inter_infrared_rising_0_SetVector(cyisraddress address) ;
cyisraddress inter_infrared_rising_0_GetVector(void) ;

void inter_infrared_rising_0_SetPriority(uint8 priority) ;
uint8 inter_infrared_rising_0_GetPriority(void) ;

void inter_infrared_rising_0_Enable(void) ;
uint8 inter_infrared_rising_0_GetState(void) ;
void inter_infrared_rising_0_Disable(void) ;

void inter_infrared_rising_0_SetPending(void) ;
void inter_infrared_rising_0_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the inter_infrared_rising_0 ISR. */
#define inter_infrared_rising_0_INTC_VECTOR            ((reg32 *) inter_infrared_rising_0__INTC_VECT)

/* Address of the inter_infrared_rising_0 ISR priority. */
#define inter_infrared_rising_0_INTC_PRIOR             ((reg8 *) inter_infrared_rising_0__INTC_PRIOR_REG)

/* Priority of the inter_infrared_rising_0 interrupt. */
#define inter_infrared_rising_0_INTC_PRIOR_NUMBER      inter_infrared_rising_0__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable inter_infrared_rising_0 interrupt. */
#define inter_infrared_rising_0_INTC_SET_EN            ((reg32 *) inter_infrared_rising_0__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the inter_infrared_rising_0 interrupt. */
#define inter_infrared_rising_0_INTC_CLR_EN            ((reg32 *) inter_infrared_rising_0__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the inter_infrared_rising_0 interrupt state to pending. */
#define inter_infrared_rising_0_INTC_SET_PD            ((reg32 *) inter_infrared_rising_0__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the inter_infrared_rising_0 interrupt. */
#define inter_infrared_rising_0_INTC_CLR_PD            ((reg32 *) inter_infrared_rising_0__INTC_CLR_PD_REG)



/* __inter_infrared_rising_0_INTC_H__ */
#endif
