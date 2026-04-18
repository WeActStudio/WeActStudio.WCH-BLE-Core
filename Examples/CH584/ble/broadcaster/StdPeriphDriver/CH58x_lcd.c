/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_lcd.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description        : source file(ch585/ch584)
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH58x_common.h"
#include "CH58x_lcd.h"

/*******************************************************************************
* Function Name  : LCD_DefInit
* Description    : LCD段式屏驱动初始化配置
* Input          : duty 占空比
*                  bias 偏压比
* Return         : None
*******************************************************************************/
void LCD_Init(LCDDutyTypeDef duty, LCDBiasTypeDef bias)
{
    R32_PIN_IN_DIS |= 0x0000238F; // 关闭数字输入
    R32_PIN_IN_DIS |= RB_PBLx_IN_DIS; // 关闭数字输入
    R16_PIN_CONFIG |= RB_PBHx_IN_DIS; // 操作LCD时，需关闭debug
    R32_LCD_SEG_EN = 0x0FFFFFFF;
    R8_LCD_CMD = RB_LCD_SYS_EN | RB_LCD_ON |
                   (LCD_CLK_128 << 5)  |
                   (duty << 3) |
                   (bias << 2);
}
