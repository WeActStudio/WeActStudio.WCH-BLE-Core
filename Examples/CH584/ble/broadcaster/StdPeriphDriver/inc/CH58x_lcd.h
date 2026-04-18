/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_lcd.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2022/12/05
 * Description        : head file(ch585/ch584)
 ********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/


#ifndef __CH58x_LCD_H__
#define __CH58x_LCD_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <CH585SFR.h>

/**
  * @brief  Configuration LCD driver power
  */
typedef enum
{
	LCD_PS_3V3 = 0,					// 3.3V 驱动
	LCD_PS_2V5,						// 2.5V 驱动
}LCDDrvPowerTypeDef; 

/**
  * @brief  Configuration LCD bias
  */
typedef enum
{
	LCD_1_2_Bias = 0,				// 2级分压
	LCD_1_3_Bias,					// 3级分压
}LCDBiasTypeDef;

/**
  * @brief  Configuration LCD duty
  */
typedef enum
{
	LCD_1_2_Duty = 0,				// COM0-COM1
	LCD_1_3_Duty,					// COM0-COM2
	LCD_1_4_Duty,					// COM0-COM3
}LCDDutyTypeDef;

/**
  * @brief  Configuration LCD scan clk
  */
typedef enum
{
	LCD_CLK_256 = 0,				// 256Hz
	LCD_CLK_512,					// 512Hz
	LCD_CLK_1000,					// 1KHz
	LCD_CLK_128						// 128Hz
}LCDSCANCLKTypeDef;
	 
/* LCD段式屏驱动初始化配置 */
void LCD_Init(LCDDutyTypeDef duty, LCDBiasTypeDef bias);

#define	LCD_PowerDown()			(R32_LCD_CMD &= ~(RB_LCD_ON | RB_LCD_SYS_EN))		/* LCD功能模块关闭 */
#define	LCD_PowerOn()			(R32_LCD_CMD |= (RB_LCD_ON | RB_LCD_SYS_EN))		/* LCD功能模块开启 */

// 输入值参考 LCDDrvPowerTypeDef
#define LCD_PowerCfg( d )		(R32_LCD_CMD = (R32_LCD_CMD & ~RB_LCD_VLCD_SEL) | (d<<7))			/* 配置LCD的 供电电压选择 */
// 输入值参考 LCDSCANCLKTypeDef
#define LCD_ScanCLKCfg( d )		(R32_LCD_CMD = (R32_LCD_CMD & ~RB_LCD_SCAN_CLK) | (d<<5))			/* 配置LCD的 扫描时钟选择 */
// 输入值参考 LCDDutyTypeDef
#define LCD_DutyCfg( d )		(R32_LCD_CMD = (R32_LCD_CMD & ~RB_LCD_DUTY) | (d<<3))				/* 配置LCD的 duty选择 */
// 输入值参考 LCDBiasTypeDef
#define LCD_BiasCfg( d )		(R32_LCD_CMD = (R32_LCD_CMD & ~RB_LCD_BIAS) | (d<<2))				/* 配置LCD的 bias选择 */
	 
#define LCD_WriteData0( d )		(R32_LCD_RAM0 = (R32_LCD_RAM0 & 0xffffff00) | ((uint32_t)d))			/* 填充LCD0驱动数值 */
#define LCD_WriteData1( d )		(R32_LCD_RAM0 = (R32_LCD_RAM0 & 0xffff00ff) | ((uint32_t)d<<8))		/* 填充LCD1驱动数值 */
#define LCD_WriteData2( d )		(R32_LCD_RAM0 = (R32_LCD_RAM0 & 0xff00ffff) | ((uint32_t)d<<16))		/* 填充LCD2驱动数值 */
#define LCD_WriteData3( d )		(R32_LCD_RAM0 = (R32_LCD_RAM0 & 0x00ffffff) | ((uint32_t)d<<24))		/* 填充LCD3驱动数值 */
	 
#define LCD_WriteData4( d )		(R32_LCD_RAM1 = (R32_LCD_RAM1 & 0xffffff00) | ((uint32_t)d))			/* 填充LCD4驱动数值 */
#define LCD_WriteData5( d )		(R32_LCD_RAM1 = (R32_LCD_RAM1 & 0xffff00ff) | ((uint32_t)d<<8))		/* 填充LCD5驱动数值 */
#define LCD_WriteData6( d )		(R32_LCD_RAM1 = (R32_LCD_RAM1 & 0xff00ffff) | ((uint32_t)d<<16))		/* 填充LCD6驱动数值 */
#define LCD_WriteData7( d )		(R32_LCD_RAM1 = (R32_LCD_RAM1 & 0x00ffffff) | ((uint32_t)d<<24))		/* 填充LCD7驱动数值 */
	 
#define LCD_WriteData8( d )		(R32_LCD_RAM2 = (R32_LCD_RAM2 & 0xffffff00) | ((uint32_t)d))			/* 填充LCD8驱动数值 */
#define LCD_WriteData9( d )		(R32_LCD_RAM2 = (R32_LCD_RAM2 & 0xffff00ff) | ((uint32_t)d<<8))		/* 填充LCD9驱动数值 */
#define LCD_WriteData10( d )	(R32_LCD_RAM2 = (R32_LCD_RAM2 & 0xff00ffff) | ((uint32_t)d<<16))		/* 填充LCD10驱动数值 */
#define LCD_WriteData11( d )    (R32_LCD_RAM2 = (R32_LCD_RAM2 & 0x00ffffff) | ((uint32_t)d<<24))      /* 填充LCD11驱动数值 */

#define LCD_WriteData12( d )    (R32_LCD_RAM3 = (R32_LCD_RAM3 & 0xffffff00) | ((uint32_t)d))          /* 填充LCD12驱动数值 */
#define LCD_WriteData13( d )    (R32_LCD_RAM3 = (R32_LCD_RAM3 & 0xffff00ff) | ((uint32_t)d<<8))       /* 填充LCD13驱动数值 */



#ifdef __cplusplus
}
#endif

#endif  // __CH58x_LCD_H__

