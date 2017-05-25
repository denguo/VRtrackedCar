/*******************************************************************************
* File Name: xbee_isr.h
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
#if !defined(__xbee_isr_INTC_H__)
#define __xbee_isr_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void xbee_isr_Start(void);
void xbee_isr_StartEx(cyisraddress address);
void xbee_isr_Stop(void) ;

CY_ISR_PROTO(xbee_isr_Interrupt);

void xbee_isr_SetVector(cyisraddress address) ;
cyisraddress xbee_isr_GetVector(void) ;

void xbee_isr_SetPriority(uint8 priority) ;
uint8 xbee_isr_GetPriority(void) ;

void xbee_isr_Enable(void) ;
uint8 xbee_isr_GetState(void) ;
void xbee_isr_Disable(void) ;

void xbee_isr_SetPending(void) ;
void xbee_isr_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the xbee_isr ISR. */
#define xbee_isr_INTC_VECTOR            ((reg32 *) xbee_isr__INTC_VECT)

/* Address of the xbee_isr ISR priority. */
#define xbee_isr_INTC_PRIOR             ((reg8 *) xbee_isr__INTC_PRIOR_REG)

/* Priority of the xbee_isr interrupt. */
#define xbee_isr_INTC_PRIOR_NUMBER      xbee_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable xbee_isr interrupt. */
#define xbee_isr_INTC_SET_EN            ((reg32 *) xbee_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the xbee_isr interrupt. */
#define xbee_isr_INTC_CLR_EN            ((reg32 *) xbee_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the xbee_isr interrupt state to pending. */
#define xbee_isr_INTC_SET_PD            ((reg32 *) xbee_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the xbee_isr interrupt. */
#define xbee_isr_INTC_CLR_PD            ((reg32 *) xbee_isr__INTC_CLR_PD_REG)



/* __xbee_isr_INTC_H__ */
#endif
