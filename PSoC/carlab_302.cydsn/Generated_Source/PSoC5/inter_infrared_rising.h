/*******************************************************************************
* File Name: inter_infrared_rising.h
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
#if !defined(__inter_infrared_rising_INTC_H__)
#define __inter_infrared_rising_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void inter_infrared_rising_Start(void);
void inter_infrared_rising_StartEx(cyisraddress address);
void inter_infrared_rising_Stop(void) ;

CY_ISR_PROTO(inter_infrared_rising_Interrupt);

void inter_infrared_rising_SetVector(cyisraddress address) ;
cyisraddress inter_infrared_rising_GetVector(void) ;

void inter_infrared_rising_SetPriority(uint8 priority) ;
uint8 inter_infrared_rising_GetPriority(void) ;

void inter_infrared_rising_Enable(void) ;
uint8 inter_infrared_rising_GetState(void) ;
void inter_infrared_rising_Disable(void) ;

void inter_infrared_rising_SetPending(void) ;
void inter_infrared_rising_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the inter_infrared_rising ISR. */
#define inter_infrared_rising_INTC_VECTOR            ((reg32 *) inter_infrared_rising__INTC_VECT)

/* Address of the inter_infrared_rising ISR priority. */
#define inter_infrared_rising_INTC_PRIOR             ((reg8 *) inter_infrared_rising__INTC_PRIOR_REG)

/* Priority of the inter_infrared_rising interrupt. */
#define inter_infrared_rising_INTC_PRIOR_NUMBER      inter_infrared_rising__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable inter_infrared_rising interrupt. */
#define inter_infrared_rising_INTC_SET_EN            ((reg32 *) inter_infrared_rising__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the inter_infrared_rising interrupt. */
#define inter_infrared_rising_INTC_CLR_EN            ((reg32 *) inter_infrared_rising__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the inter_infrared_rising interrupt state to pending. */
#define inter_infrared_rising_INTC_SET_PD            ((reg32 *) inter_infrared_rising__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the inter_infrared_rising interrupt. */
#define inter_infrared_rising_INTC_CLR_PD            ((reg32 *) inter_infrared_rising__INTC_CLR_PD_REG)



/* __inter_infrared_rising_INTC_H__ */
#endif
