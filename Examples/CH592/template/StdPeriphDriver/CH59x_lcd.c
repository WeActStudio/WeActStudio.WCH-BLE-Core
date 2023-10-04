/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH59x_lcd.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/15
 * Description 
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH59x_common.h"
#include "CH59x_lcd.h"

/*******************************************************************************
* Function Name  : LCD_DefInit
* Description    : LCD段式屏驱动初始化配置
* Input          : duty 占空比
*                  bias 偏压比
* Return         : None
*******************************************************************************/
void LCD_Init(LCDDutyTypeDef duty, LCDBiasTypeDef bias)
{
    R32_PIN_CONFIG2 = 0xfffeff3f; // 关闭数字输入
    R32_LCD_CMD = 0x1ffff << 8;
    R32_LCD_CMD |= RB_LCD_SYS_EN | RB_LCD_ON |
                   (LCD_CLK_128 << 5)  |
                   (duty << 3) |
                   (bias << 2);
}
