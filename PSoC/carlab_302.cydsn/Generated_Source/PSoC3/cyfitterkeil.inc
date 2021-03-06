#ifndef INCLUDED_CYFITTERKEIL_INC
#define INCLUDED_CYFITTERKEIL_INC
$INCLUDE (cydevicekeil.inc)
$INCLUDE (cydevicekeil_trm.inc)

; LCD_LCDPort
LCD_LCDPort__0__MASK EQU 0x01
LCD_LCDPort__0__PC EQU CYREG_PRT2_PC0
LCD_LCDPort__0__PORT EQU 2
LCD_LCDPort__0__SHIFT EQU 0
LCD_LCDPort__1__MASK EQU 0x02
LCD_LCDPort__1__PC EQU CYREG_PRT2_PC1
LCD_LCDPort__1__PORT EQU 2
LCD_LCDPort__1__SHIFT EQU 1
LCD_LCDPort__2__MASK EQU 0x04
LCD_LCDPort__2__PC EQU CYREG_PRT2_PC2
LCD_LCDPort__2__PORT EQU 2
LCD_LCDPort__2__SHIFT EQU 2
LCD_LCDPort__3__MASK EQU 0x08
LCD_LCDPort__3__PC EQU CYREG_PRT2_PC3
LCD_LCDPort__3__PORT EQU 2
LCD_LCDPort__3__SHIFT EQU 3
LCD_LCDPort__4__MASK EQU 0x10
LCD_LCDPort__4__PC EQU CYREG_PRT2_PC4
LCD_LCDPort__4__PORT EQU 2
LCD_LCDPort__4__SHIFT EQU 4
LCD_LCDPort__5__MASK EQU 0x20
LCD_LCDPort__5__PC EQU CYREG_PRT2_PC5
LCD_LCDPort__5__PORT EQU 2
LCD_LCDPort__5__SHIFT EQU 5
LCD_LCDPort__6__MASK EQU 0x40
LCD_LCDPort__6__PC EQU CYREG_PRT2_PC6
LCD_LCDPort__6__PORT EQU 2
LCD_LCDPort__6__SHIFT EQU 6
LCD_LCDPort__AG EQU CYREG_PRT2_AG
LCD_LCDPort__AMUX EQU CYREG_PRT2_AMUX
LCD_LCDPort__BIE EQU CYREG_PRT2_BIE
LCD_LCDPort__BIT_MASK EQU CYREG_PRT2_BIT_MASK
LCD_LCDPort__BYP EQU CYREG_PRT2_BYP
LCD_LCDPort__CTL EQU CYREG_PRT2_CTL
LCD_LCDPort__DM0 EQU CYREG_PRT2_DM0
LCD_LCDPort__DM1 EQU CYREG_PRT2_DM1
LCD_LCDPort__DM2 EQU CYREG_PRT2_DM2
LCD_LCDPort__DR EQU CYREG_PRT2_DR
LCD_LCDPort__INP_DIS EQU CYREG_PRT2_INP_DIS
LCD_LCDPort__LCD_COM_SEG EQU CYREG_PRT2_LCD_COM_SEG
LCD_LCDPort__LCD_EN EQU CYREG_PRT2_LCD_EN
LCD_LCDPort__MASK EQU 0x7F
LCD_LCDPort__PORT EQU 2
LCD_LCDPort__PRT EQU CYREG_PRT2_PRT
LCD_LCDPort__PRTDSI__CAPS_SEL EQU CYREG_PRT2_CAPS_SEL
LCD_LCDPort__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT2_DBL_SYNC_IN
LCD_LCDPort__PRTDSI__OE_SEL0 EQU CYREG_PRT2_OE_SEL0
LCD_LCDPort__PRTDSI__OE_SEL1 EQU CYREG_PRT2_OE_SEL1
LCD_LCDPort__PRTDSI__OUT_SEL0 EQU CYREG_PRT2_OUT_SEL0
LCD_LCDPort__PRTDSI__OUT_SEL1 EQU CYREG_PRT2_OUT_SEL1
LCD_LCDPort__PRTDSI__SYNC_OUT EQU CYREG_PRT2_SYNC_OUT
LCD_LCDPort__PS EQU CYREG_PRT2_PS
LCD_LCDPort__SHIFT EQU 0
LCD_LCDPort__SLW EQU CYREG_PRT2_SLW

; PWM_PWMUDB
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB01_02_ACTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB01_02_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB01_02_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB01_02_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB01_02_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB01_02_MSK
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB01_02_MSK
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB01_02_MSK
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB01_02_MSK
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__7__MASK EQU 0x80
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__7__POS EQU 7
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB01_ACTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG EQU CYREG_B0_UDB01_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_ST_REG EQU CYREG_B0_UDB01_ST_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_REG EQU CYREG_B0_UDB01_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__COUNT_ST_REG EQU CYREG_B0_UDB01_ST_CTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__MASK EQU 0x80
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB01_MSK_ACTL
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__PERIOD_REG EQU CYREG_B0_UDB01_MSK
PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB01_MSK_ACTL
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB01_02_A0
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB01_02_A1
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB01_02_D0
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB01_02_D1
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB01_02_ACTL
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB01_02_F0
PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB01_02_F1
PWM_PWMUDB_sP8_pwmdp_u0__A0_A1_REG EQU CYREG_B0_UDB01_A0_A1
PWM_PWMUDB_sP8_pwmdp_u0__A0_REG EQU CYREG_B0_UDB01_A0
PWM_PWMUDB_sP8_pwmdp_u0__A1_REG EQU CYREG_B0_UDB01_A1
PWM_PWMUDB_sP8_pwmdp_u0__D0_D1_REG EQU CYREG_B0_UDB01_D0_D1
PWM_PWMUDB_sP8_pwmdp_u0__D0_REG EQU CYREG_B0_UDB01_D0
PWM_PWMUDB_sP8_pwmdp_u0__D1_REG EQU CYREG_B0_UDB01_D1
PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB01_ACTL
PWM_PWMUDB_sP8_pwmdp_u0__F0_F1_REG EQU CYREG_B0_UDB01_F0_F1
PWM_PWMUDB_sP8_pwmdp_u0__F0_REG EQU CYREG_B0_UDB01_F0
PWM_PWMUDB_sP8_pwmdp_u0__F1_REG EQU CYREG_B0_UDB01_F1
PWM_PWMUDB_sP8_pwmdp_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB01_MSK_ACTL
PWM_PWMUDB_sP8_pwmdp_u0__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB01_MSK_ACTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__0__MASK EQU 0x01
PWM_PWMUDB_sSTSReg_rstSts_stsreg__0__POS EQU 0
PWM_PWMUDB_sSTSReg_rstSts_stsreg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB01_02_ACTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__16BIT_STATUS_REG EQU CYREG_B0_UDB01_02_ST
PWM_PWMUDB_sSTSReg_rstSts_stsreg__2__MASK EQU 0x04
PWM_PWMUDB_sSTSReg_rstSts_stsreg__2__POS EQU 2
PWM_PWMUDB_sSTSReg_rstSts_stsreg__3__MASK EQU 0x08
PWM_PWMUDB_sSTSReg_rstSts_stsreg__3__POS EQU 3
PWM_PWMUDB_sSTSReg_rstSts_stsreg__5__MASK EQU 0x20
PWM_PWMUDB_sSTSReg_rstSts_stsreg__5__POS EQU 5
PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK EQU 0x2D
PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG EQU CYREG_B0_UDB01_MSK
PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB01_MSK_ACTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB01_MSK_ACTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB01_ACTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_CNT_REG EQU CYREG_B0_UDB01_ST_CTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_CONTROL_REG EQU CYREG_B0_UDB01_ST_CTL
PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG EQU CYREG_B0_UDB01_ST

; Clock_1
Clock_1__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
Clock_1__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
Clock_1__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
Clock_1__CFG2_SRC_SEL_MASK EQU 0x07
Clock_1__INDEX EQU 0x00
Clock_1__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
Clock_1__PM_ACT_MSK EQU 0x01
Clock_1__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
Clock_1__PM_STBY_MSK EQU 0x01

; inter_1
inter_1__ES2_PATCH EQU 0
inter_1__INTC_CLR_EN_REG EQU CYREG_INTC_CLR_EN0
inter_1__INTC_CLR_PD_REG EQU CYREG_INTC_CLR_PD0
inter_1__INTC_MASK EQU 0x01
inter_1__INTC_NUMBER EQU 0
inter_1__INTC_PRIOR_NUM EQU 7
inter_1__INTC_PRIOR_REG EQU CYREG_INTC_PRIOR0
inter_1__INTC_SET_EN_REG EQU CYREG_INTC_SET_EN0
inter_1__INTC_SET_PD_REG EQU CYREG_INTC_SET_PD0
inter_1__INTC_VECT EQU (CYREG_INTC_VECT_MBASE+0x00)

; Pin_1
Pin_1__0__MASK EQU 0x02
Pin_1__0__PC EQU CYREG_PRT6_PC1
Pin_1__0__PORT EQU 6
Pin_1__0__SHIFT EQU 1
Pin_1__AG EQU CYREG_PRT6_AG
Pin_1__AMUX EQU CYREG_PRT6_AMUX
Pin_1__BIE EQU CYREG_PRT6_BIE
Pin_1__BIT_MASK EQU CYREG_PRT6_BIT_MASK
Pin_1__BYP EQU CYREG_PRT6_BYP
Pin_1__CTL EQU CYREG_PRT6_CTL
Pin_1__DM0 EQU CYREG_PRT6_DM0
Pin_1__DM1 EQU CYREG_PRT6_DM1
Pin_1__DM2 EQU CYREG_PRT6_DM2
Pin_1__DR EQU CYREG_PRT6_DR
Pin_1__INP_DIS EQU CYREG_PRT6_INP_DIS
Pin_1__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
Pin_1__LCD_EN EQU CYREG_PRT6_LCD_EN
Pin_1__MASK EQU 0x02
Pin_1__PORT EQU 6
Pin_1__PRT EQU CYREG_PRT6_PRT
Pin_1__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
Pin_1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
Pin_1__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
Pin_1__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
Pin_1__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
Pin_1__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
Pin_1__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
Pin_1__PS EQU CYREG_PRT6_PS
Pin_1__SHIFT EQU 1
Pin_1__SLW EQU CYREG_PRT6_SLW

; Pin_2
Pin_2__0__MASK EQU 0x02
Pin_2__0__PC EQU CYREG_PRT4_PC1
Pin_2__0__PORT EQU 4
Pin_2__0__SHIFT EQU 1
Pin_2__AG EQU CYREG_PRT4_AG
Pin_2__AMUX EQU CYREG_PRT4_AMUX
Pin_2__BIE EQU CYREG_PRT4_BIE
Pin_2__BIT_MASK EQU CYREG_PRT4_BIT_MASK
Pin_2__BYP EQU CYREG_PRT4_BYP
Pin_2__CTL EQU CYREG_PRT4_CTL
Pin_2__DM0 EQU CYREG_PRT4_DM0
Pin_2__DM1 EQU CYREG_PRT4_DM1
Pin_2__DM2 EQU CYREG_PRT4_DM2
Pin_2__DR EQU CYREG_PRT4_DR
Pin_2__INP_DIS EQU CYREG_PRT4_INP_DIS
Pin_2__LCD_COM_SEG EQU CYREG_PRT4_LCD_COM_SEG
Pin_2__LCD_EN EQU CYREG_PRT4_LCD_EN
Pin_2__MASK EQU 0x02
Pin_2__PORT EQU 4
Pin_2__PRT EQU CYREG_PRT4_PRT
Pin_2__PRTDSI__CAPS_SEL EQU CYREG_PRT4_CAPS_SEL
Pin_2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT4_DBL_SYNC_IN
Pin_2__PRTDSI__OE_SEL0 EQU CYREG_PRT4_OE_SEL0
Pin_2__PRTDSI__OE_SEL1 EQU CYREG_PRT4_OE_SEL1
Pin_2__PRTDSI__OUT_SEL0 EQU CYREG_PRT4_OUT_SEL0
Pin_2__PRTDSI__OUT_SEL1 EQU CYREG_PRT4_OUT_SEL1
Pin_2__PRTDSI__SYNC_OUT EQU CYREG_PRT4_SYNC_OUT
Pin_2__PS EQU CYREG_PRT4_PS
Pin_2__SHIFT EQU 1
Pin_2__SLW EQU CYREG_PRT4_SLW

; Miscellaneous
; -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_DIE_LEOPARD
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_DIE_PANTHER EQU 2
CYDEV_CHIP_DIE_PSOC5LP EQU 3
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC3
CYDEV_CHIP_JTAG_ID EQU 0x1E023069
CYDEV_CHIP_MEMBER_5A EQU 2
CYDEV_CHIP_MEMBER_5B EQU 3
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_3A
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_3A_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REV_LEOPARD_PRODUCTION
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC5LP_ES EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CONFIGURATION_CLEAR_SRAM EQU 1
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_CONFIG_FORCE_ROUTE EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_REQXRES EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DEBUG_ENABLE_MASK EQU 0x01
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_VDDA LIT '5.0'
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD LIT '5.0'
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0 LIT '5.0'
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1 LIT '5.0'
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2 LIT '5.0'
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3 LIT '5.0'
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0 EQU 5
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1 EQU 5
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2 EQU 5
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3 EQU 5
CYDEV_VIO3_MV EQU 5000
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERKEIL_INC */
