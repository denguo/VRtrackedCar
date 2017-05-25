/*******************************************************************************
* File Name: Button_Left.h  
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

#if !defined(CY_PINS_Button_Left_H) /* Pins Button_Left_H */
#define CY_PINS_Button_Left_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_Left_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button_Left__PORT == 15 && (Button_Left__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Left_Write(uint8 value) ;
void    Button_Left_SetDriveMode(uint8 mode) ;
uint8   Button_Left_ReadDataReg(void) ;
uint8   Button_Left_Read(void) ;
uint8   Button_Left_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_Left_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_Left_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_Left_DM_RES_UP          PIN_DM_RES_UP
#define Button_Left_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_Left_DM_OD_LO           PIN_DM_OD_LO
#define Button_Left_DM_OD_HI           PIN_DM_OD_HI
#define Button_Left_DM_STRONG          PIN_DM_STRONG
#define Button_Left_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_Left_MASK               Button_Left__MASK
#define Button_Left_SHIFT              Button_Left__SHIFT
#define Button_Left_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_Left_PS                     (* (reg8 *) Button_Left__PS)
/* Data Register */
#define Button_Left_DR                     (* (reg8 *) Button_Left__DR)
/* Port Number */
#define Button_Left_PRT_NUM                (* (reg8 *) Button_Left__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_Left_AG                     (* (reg8 *) Button_Left__AG)                       
/* Analog MUX bux enable */
#define Button_Left_AMUX                   (* (reg8 *) Button_Left__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_Left_BIE                    (* (reg8 *) Button_Left__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_Left_BIT_MASK               (* (reg8 *) Button_Left__BIT_MASK)
/* Bypass Enable */
#define Button_Left_BYP                    (* (reg8 *) Button_Left__BYP)
/* Port wide control signals */                                                   
#define Button_Left_CTL                    (* (reg8 *) Button_Left__CTL)
/* Drive Modes */
#define Button_Left_DM0                    (* (reg8 *) Button_Left__DM0) 
#define Button_Left_DM1                    (* (reg8 *) Button_Left__DM1)
#define Button_Left_DM2                    (* (reg8 *) Button_Left__DM2) 
/* Input Buffer Disable Override */
#define Button_Left_INP_DIS                (* (reg8 *) Button_Left__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_Left_LCD_COM_SEG            (* (reg8 *) Button_Left__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_Left_LCD_EN                 (* (reg8 *) Button_Left__LCD_EN)
/* Slew Rate Control */
#define Button_Left_SLW                    (* (reg8 *) Button_Left__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_Left_PRTDSI__CAPS_SEL       (* (reg8 *) Button_Left__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_Left_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_Left__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_Left_PRTDSI__OE_SEL0        (* (reg8 *) Button_Left__PRTDSI__OE_SEL0) 
#define Button_Left_PRTDSI__OE_SEL1        (* (reg8 *) Button_Left__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_Left_PRTDSI__OUT_SEL0       (* (reg8 *) Button_Left__PRTDSI__OUT_SEL0) 
#define Button_Left_PRTDSI__OUT_SEL1       (* (reg8 *) Button_Left__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_Left_PRTDSI__SYNC_OUT       (* (reg8 *) Button_Left__PRTDSI__SYNC_OUT) 


#if defined(Button_Left__INTSTAT)  /* Interrupt Registers */

    #define Button_Left_INTSTAT                (* (reg8 *) Button_Left__INTSTAT)
    #define Button_Left_SNAP                   (* (reg8 *) Button_Left__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Button_Left_H */

#endif
/* [] END OF FILE */
