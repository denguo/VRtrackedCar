/*******************************************************************************
* File Name: Button_Right.h  
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

#if !defined(CY_PINS_Button_Right_H) /* Pins Button_Right_H */
#define CY_PINS_Button_Right_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_Right_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button_Right__PORT == 15 && (Button_Right__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Right_Write(uint8 value) ;
void    Button_Right_SetDriveMode(uint8 mode) ;
uint8   Button_Right_ReadDataReg(void) ;
uint8   Button_Right_Read(void) ;
uint8   Button_Right_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_Right_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_Right_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_Right_DM_RES_UP          PIN_DM_RES_UP
#define Button_Right_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_Right_DM_OD_LO           PIN_DM_OD_LO
#define Button_Right_DM_OD_HI           PIN_DM_OD_HI
#define Button_Right_DM_STRONG          PIN_DM_STRONG
#define Button_Right_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_Right_MASK               Button_Right__MASK
#define Button_Right_SHIFT              Button_Right__SHIFT
#define Button_Right_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_Right_PS                     (* (reg8 *) Button_Right__PS)
/* Data Register */
#define Button_Right_DR                     (* (reg8 *) Button_Right__DR)
/* Port Number */
#define Button_Right_PRT_NUM                (* (reg8 *) Button_Right__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_Right_AG                     (* (reg8 *) Button_Right__AG)                       
/* Analog MUX bux enable */
#define Button_Right_AMUX                   (* (reg8 *) Button_Right__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_Right_BIE                    (* (reg8 *) Button_Right__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_Right_BIT_MASK               (* (reg8 *) Button_Right__BIT_MASK)
/* Bypass Enable */
#define Button_Right_BYP                    (* (reg8 *) Button_Right__BYP)
/* Port wide control signals */                                                   
#define Button_Right_CTL                    (* (reg8 *) Button_Right__CTL)
/* Drive Modes */
#define Button_Right_DM0                    (* (reg8 *) Button_Right__DM0) 
#define Button_Right_DM1                    (* (reg8 *) Button_Right__DM1)
#define Button_Right_DM2                    (* (reg8 *) Button_Right__DM2) 
/* Input Buffer Disable Override */
#define Button_Right_INP_DIS                (* (reg8 *) Button_Right__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_Right_LCD_COM_SEG            (* (reg8 *) Button_Right__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_Right_LCD_EN                 (* (reg8 *) Button_Right__LCD_EN)
/* Slew Rate Control */
#define Button_Right_SLW                    (* (reg8 *) Button_Right__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_Right_PRTDSI__CAPS_SEL       (* (reg8 *) Button_Right__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_Right_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_Right__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_Right_PRTDSI__OE_SEL0        (* (reg8 *) Button_Right__PRTDSI__OE_SEL0) 
#define Button_Right_PRTDSI__OE_SEL1        (* (reg8 *) Button_Right__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_Right_PRTDSI__OUT_SEL0       (* (reg8 *) Button_Right__PRTDSI__OUT_SEL0) 
#define Button_Right_PRTDSI__OUT_SEL1       (* (reg8 *) Button_Right__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_Right_PRTDSI__SYNC_OUT       (* (reg8 *) Button_Right__PRTDSI__SYNC_OUT) 


#if defined(Button_Right__INTSTAT)  /* Interrupt Registers */

    #define Button_Right_INTSTAT                (* (reg8 *) Button_Right__INTSTAT)
    #define Button_Right_SNAP                   (* (reg8 *) Button_Right__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Button_Right_H */

#endif
/* [] END OF FILE */
