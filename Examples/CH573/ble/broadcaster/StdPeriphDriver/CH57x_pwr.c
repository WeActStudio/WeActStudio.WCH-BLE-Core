/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_pwr.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH57x_common.h"

/*********************************************************************
 * @fn      PWR_DCDCCfg
 *
 * @brief   �����ڲ�DC/DC��Դ�����ڽ�Լϵͳ����
 *
 * @param   s       - �Ƿ��DCDC��Դ
 *
 * @return  none
 */
void PWR_DCDCCfg(FunctionalState s)
{
    if(s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN &= ~(RB_PWR_DCDC_EN | RB_PWR_DCDC_PRE); // ��· DC/DC
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;
    }
    else
    {
        uint32_t HW_Data[2];
        FLASH_EEPROM_CMD(CMD_GET_ROM_INFO, ROM_CFG_ADR_HW, HW_Data, 0);
        if((HW_Data[0]) & (1 << 13))
        {
            return;
        }
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN |= RB_PWR_DCDC_PRE;
        R16_POWER_PLAN |= RB_PWR_DCDC_EN;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;
    }
}

/*********************************************************************
 * @fn      PWR_UnitModCfg
 *
 * @brief   �ɿص�Ԫģ��ĵ�Դ����
 *
 * @param   s       - �Ƿ�򿪵�Դ
 * @param   unit    - please refer to unit of controllable power supply
 *
 * @return  none
 */
void PWR_UnitModCfg(FunctionalState s, uint8_t unit)
{
    if(s == DISABLE) //�ر�
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_HFCK_PWR_CTRL &= ~(unit & 0x1c);
        R8_CK32K_CONFIG &= ~(unit & 0x03);
    }
    else //��
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_HFCK_PWR_CTRL |= (unit & 0x1c);
        R8_CK32K_CONFIG |= (unit & 0x03);
    }
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      PWR_PeriphClkCfg
 *
 * @brief   ����ʱ�ӿ���λ
 *
 * @param   s       - �Ƿ�򿪶�Ӧ����ʱ��
 * @param   perph   - please refer to Peripher CLK control bit define
 *
 * @return  none
 */
void PWR_PeriphClkCfg(FunctionalState s, uint16_t perph)
{
    if(s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R32_SLEEP_CONTROL |= perph;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R32_SLEEP_CONTROL &= ~perph;
    }
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      PWR_PeriphWakeUpCfg
 *
 * @brief   ˯�߻���Դ����
 *
 * @param   s       - �Ƿ�򿪴�����˯�߻��ѹ���
 * @param   perph   - ��Ҫ���õĻ���Դ
 *                    RB_SLP_USB_WAKE   -  USB Ϊ����Դ
 *                    RB_SLP_RTC_WAKE   -  RTC Ϊ����Դ
 *                    RB_SLP_GPIO_WAKE  -  GPIO Ϊ����Դ
 *                    RB_SLP_BAT_WAKE   -  BAT Ϊ����Դ
 * @param   mode    - refer to WakeUP_ModeypeDef
 *
 * @return  none
 */
void PWR_PeriphWakeUpCfg(FunctionalState s, uint8_t perph, WakeUP_ModeypeDef mode)
{
    uint8_t m;

    if(s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_SLP_WAKE_CTRL &= ~perph;
    }
    else
    {
        switch(mode)
        {
            case Edge_LongDelay:
                m = RB_WAKE_EV_MODE;
                break;

            case Level_LongDelay:
                m = 0;
                break;

            case Level_ShortDelay:
                m = RB_WAKE_DELAY;
                break;

            default:
                m = RB_WAKE_EV_MODE | RB_WAKE_DELAY;
                break;
        }
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_SLP_WAKE_CTRL &= ~(RB_WAKE_EV_MODE | RB_WAKE_DELAY);
        R8_SLP_WAKE_CTRL |= m | perph;
    }
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      PowerMonitor
 *
 * @brief   ��Դ���
 *
 * @param   s       - �Ƿ�򿪴˹���
 * @param   vl      - refer to VolM_LevelypeDef
 *
 * @return  none
 */
void PowerMonitor(FunctionalState s, VolM_LevelypeDef vl)
{
    if(s == DISABLE)
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CTRL = 0;
        R8_SAFE_ACCESS_SIG = 0;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if(vl & 0x80)
        {
            R8_BAT_DET_CFG = vl & 0x03;
            R8_BAT_DET_CTRL = RB_BAT_MON_EN | ((vl >> 2) & 1);
        }
        else
        {
            R8_BAT_DET_CFG = vl & 0x03;
            R8_BAT_DET_CTRL = RB_BAT_DET_EN;
        }
        R8_SAFE_ACCESS_SIG = 0;
        mDelayuS(1);
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CTRL |= RB_BAT_LOW_IE | RB_BAT_LOWER_IE;
        R8_SAFE_ACCESS_SIG = 0;
    }
}

/*********************************************************************
 * @fn      LowPower_Idle
 *
 * @brief   �͹���-Idleģʽ
 *
 * @param   none
 *
 * @return  none
 */
__attribute__((section(".highcode")))
void LowPower_Idle(void)
{
    FLASH_ROM_SW_RESET();
    R8_FLASH_CTRL = 0x04; //flash�ر�

    PFIC->SCTLR &= ~(1 << 2); // sleep
    __WFI();
    __nop();
    __nop();
}

/*********************************************************************
 * @fn      LowPower_Halt
 *
 * @brief   �͹���-Haltģʽ���˵͹����е�HSI/5ʱ�����У����Ѻ���Ҫ�û��Լ�����ѡ��ϵͳʱ��Դ
 *
 * @param   none
 *
 * @return  none
 */
__attribute__((section(".highcode")))
void LowPower_Halt(void)
{
    uint8_t x32Kpw, x32Mpw;

    FLASH_ROM_SW_RESET();
    R8_FLASH_CTRL = 0x04; //flash�ر�
    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw & 0xfc) | 0x03; // 150%�����
    if(R16_RTC_CNT_32K > 0x3fff)
    {                                    // ����500ms
        x32Kpw = (x32Kpw & 0xfc) | 0x01; // LSE�����������͵������
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_BAT_DET_CTRL = 0; // �رյ�ѹ���
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R8_PLL_CONFIG |= (1 << 5);
    R8_SAFE_ACCESS_SIG = 0;

    PFIC->SCTLR |= (1 << 2); //deep sleep
    __WFI();
    __nop();
    __nop();
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_PLL_CONFIG &= ~(1 << 5);
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      LowPower_Sleep
 *
 * @brief   �͹���-Sleepģʽ���˵͹����е�HSI/5ʱ�����У����Ѻ���Ҫ�û��Լ�����ѡ��ϵͳʱ��Դ
 *          @note ע����ô˺�����DCDC����ǿ�ƹرգ����Ѻ�����ֶ��ٴδ�
 *
 * @param   rm      - ����ģ��ѡ��
 *                    RB_PWR_RAM2K  -   2K retention SRAM ����
 *                    RB_PWR_RAM16K -   16K main SRAM ����
 *                    RB_PWR_EXTEND -   USB �� BLE ��Ԫ�������򹩵�
 *                    RB_PWR_XROM   -   FlashROM ����
 *                    NULL          -   ���ϵ�Ԫ���ϵ�
 *
 * @return  none
 */
__attribute__((section(".highcode")))
void LowPower_Sleep(uint8_t rm)
{
    uint8_t x32Kpw, x32Mpw;

    FLASH_ROM_SW_RESET();
    R8_FLASH_CTRL = 0x04; //flash�ر�
    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw & 0xfc) | 0x03; // 150%�����
    if(R16_RTC_CNT_32K > 0x3fff)
    {                                    // ����500ms
        x32Kpw = (x32Kpw & 0xfc) | 0x01; // LSE�����������͵������
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_BAT_DET_CTRL = 0; // �رյ�ѹ���
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R8_SAFE_ACCESS_SIG = 0;

    PFIC->SCTLR |= (1 << 2); //deep sleep

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL |= RB_RAM_RET_LV;
    R8_PLL_CONFIG |= (1 << 5);
    R16_POWER_PLAN = RB_PWR_PLAN_EN | RB_PWR_MUST_0010 | RB_PWR_CORE | rm;
    __WFI();
    __nop();
    __nop();
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_PLL_CONFIG &= ~(1 << 5);
    R8_SAFE_ACCESS_SIG = 0;
    mDelayuS(70);
}

/*********************************************************************
 * @fn      LowPower_Shutdown
 *
 * @brief   �͹���-Shutdownģʽ���˵͹����е�HSI/5ʱ�����У����Ѻ���Ҫ�û��Լ�����ѡ��ϵͳʱ��Դ
 *          @note ע����ô˺�����DCDC����ǿ�ƹرգ����Ѻ�����ֶ��ٴδ�
 *
 * @param   rm      - ����ģ��ѡ��
 *                    RB_PWR_RAM2K  -   2K retention SRAM ����
 *                    RB_PWR_RAM16K -   16K main SRAM ����
 *                    NULL          -   ���ϵ�Ԫ���ϵ�
 *
 * @return  none
 */
__attribute__((section(".highcode")))
void LowPower_Shutdown(uint8_t rm)
{
    uint8_t x32Kpw, x32Mpw;

    FLASH_ROM_SW_RESET();
    R8_FLASH_CTRL = 0x04; //flash�ر�
    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw & 0xfc) | 0x03; // 150%�����
    if(R16_RTC_CNT_32K > 0x3fff)
    {                                    // ����500ms
        x32Kpw = (x32Kpw & 0xfc) | 0x01; // LSE�����������͵������
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_BAT_DET_CTRL = 0; // �رյ�ѹ���
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R8_SAFE_ACCESS_SIG = 0;
    SetSysClock( CLK_SOURCE_HSE_6_4MHz );

    PFIC->SCTLR |= (1 << 2);				//deep sleep

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL |= RB_RAM_RET_LV;
    R16_POWER_PLAN = RB_PWR_PLAN_EN | RB_PWR_MUST_0010 | rm;
    __WFI();
    __nop();
    __nop();
}
