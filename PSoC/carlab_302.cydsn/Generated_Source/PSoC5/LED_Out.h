/*******************************************************************************
* File Name: LED_Out.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_LED_Out_H) /* Pins LED_Out_H */
#define CY_PINS_LED_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_Out_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_Out__PORT == 15 && (LED_Out__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    LED_Out_Write(uint8 value) ;
void    LED_Out_SetDriveMode(uint8 mode) ;
uint8   LED_Out_ReadDataReg(void) ;
uint8   LED_Out_Read(void) ;
uint8   LED_Out_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_Out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_Out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_Out_DM_RES_UP          PIN_DM_RES_UP
#define LED_Out_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_Out_DM_OD_LO           PIN_DM_OD_LO
#define LED_Out_DM_OD_HI           PIN_DM_OD_HI
#define LED_Out_DM_STRONG          PIN_DM_STRONG
#define LED_Out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_Out_MASK               LED_Out__MASK
#define LED_Out_SHIFT              LED_Out__SHIFT
#define LED_Out_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_Out_PS                     (* (reg8 *) LED_Out__PS)
/* Data Register */
#define LED_Out_DR                     (* (reg8 *) LED_Out__DR)
/* Port Number */
#define LED_Out_PRT_NUM                (* (reg8 *) LED_Out__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_Out_AG                     (* (reg8 *) LED_Out__AG)                       
/* Analog MUX bux enable */
#define LED_Out_AMUX                   (* (reg8 *) LED_Out__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_Out_BIE                    (* (reg8 *) LED_Out__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_Out_BIT_MASK               (* (reg8 *) LED_Out__BIT_MASK)
/* Bypass Enable */
#define LED_Out_BYP                    (* (reg8 *) LED_Out__BYP)
/* Port wide control signals */                                                   
#define LED_Out_CTL                    (* (reg8 *) LED_Out__CTL)
/* Drive Modes */
#define LED_Out_DM0                    (* (reg8 *) LED_Out__DM0) 
#define LED_Out_DM1                    (* (reg8 *) LED_Out__DM1)
#define LED_Out_DM2                    (* (reg8 *) LED_Out__DM2) 
/* Input Buffer Disable Override */
#define LED_Out_INP_DIS                (* (reg8 *) LED_Out__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_Out_LCD_COM_SEG            (* (reg8 *) LED_Out__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_Out_LCD_EN                 (* (reg8 *) LED_Out__LCD_EN)
/* Slew Rate Control */
#define LED_Out_SLW                    (* (reg8 *) LED_Out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_Out_PRTDSI__CAPS_SEL       (* (reg8 *) LED_Out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_Out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_Out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_Out_PRTDSI__OE_SEL0        (* (reg8 *) LED_Out__PRTDSI__OE_SEL0) 
#define LED_Out_PRTDSI__OE_SEL1        (* (reg8 *) LED_Out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_Out_PRTDSI__OUT_SEL0       (* (reg8 *) LED_Out__PRTDSI__OUT_SEL0) 
#define LED_Out_PRTDSI__OUT_SEL1       (* (reg8 *) LED_Out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_Out_PRTDSI__SYNC_OUT       (* (reg8 *) LED_Out__PRTDSI__SYNC_OUT) 


#if defined(LED_Out__INTSTAT)  /* Interrupt Registers */

    #define LED_Out_INTSTAT                (* (reg8 *) LED_Out__INTSTAT)
    #define LED_Out_SNAP                   (* (reg8 *) LED_Out__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins LED_Out_H */

#endif
/* [] END OF FILE */
