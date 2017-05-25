/*******************************************************************************
* File Name: inter_horizontalSync.h
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
#if !defined(__inter_horizontalSync_INTC_H__)
#define __inter_horizontalSync_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void inter_horizontalSync_Start(void);
void inter_horizontalSync_StartEx(cyisraddress address);
void inter_horizontalSync_Stop(void) ;

CY_ISR_PROTO(inter_horizontalSync_Interrupt);

void inter_horizontalSync_SetVector(cyisraddress address) ;
cyisraddress inter_horizontalSync_GetVector(void) ;

void inter_horizontalSync_SetPriority(uint8 priority) ;
uint8 inter_horizontalSync_GetPriority(void) ;

void inter_horizontalSync_Enable(void) ;
uint8 inter_horizontalSync_GetState(void) ;
void inter_horizontalSync_Disable(void) ;

void inter_horizontalSync_SetPending(void) ;
void inter_horizontalSync_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the inter_horizontalSync ISR. */
#define inter_horizontalSync_INTC_VECTOR            ((reg32 *) inter_horizontalSync__INTC_VECT)

/* Address of the inter_horizontalSync ISR priority. */
#define inter_horizontalSync_INTC_PRIOR             ((reg8 *) inter_horizontalSync__INTC_PRIOR_REG)

/* Priority of the inter_horizontalSync interrupt. */
#define inter_horizontalSync_INTC_PRIOR_NUMBER      inter_horizontalSync__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable inter_horizontalSync interrupt. */
#define inter_horizontalSync_INTC_SET_EN            ((reg32 *) inter_horizontalSync__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the inter_horizontalSync interrupt. */
#define inter_horizontalSync_INTC_CLR_EN            ((reg32 *) inter_horizontalSync__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the inter_horizontalSync interrupt state to pending. */
#define inter_horizontalSync_INTC_SET_PD            ((reg32 *) inter_horizontalSync__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the inter_horizontalSync interrupt. */
#define inter_horizontalSync_INTC_CLR_PD            ((reg32 *) inter_horizontalSync__INTC_CLR_PD_REG)



/* __inter_horizontalSync_INTC_H__ */
#endif
