/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_timer1.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH58x_common.h"

/*********************************************************************
 * @fn      TMR1_TimerInit
 *
 * @brief   ��ʱ���ܳ�ʼ��
 *
 * @param   t       - ��ʱʱ�䣬���ڵ�ǰϵͳʱ��Tsys, ���ʱ���� 67108864
 *
 * @return  none
 */
void TMR1_TimerInit(uint32_t t)
{
    R32_TMR1_CNT_END = t;
    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN;
}

/*********************************************************************
 * @fn      TMR1_EXTSingleCounterInit
 *
 * @brief   ���ؼ������ܳ�ʼ��
 *
 * @param   cap     - �ɼ���������
 *
 * @return  none
 */
void TMR1_EXTSingleCounterInit(CapModeTypeDef cap)
{
    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_CAP_COUNT | RB_TMR_MODE_IN | (cap << 6);
}

/*********************************************************************
 * @fn      TMR1_PWMInit
 *
 * @brief   PWM �����ʼ��
 *
 * @param   pr      - select wave polar, refer to PWMX_PolarTypeDef
 * @param   ts      - set pwm repeat times, refer to PWM_RepeatTsTypeDef
 *
 * @return  none
 */
void TMR1_PWMInit(PWMX_PolarTypeDef pr, PWM_RepeatTsTypeDef ts)
{
    //    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_OUT_EN | (pr << 4) | (ts << 6);
}

/*********************************************************************
 * @fn      TMR1_CapInit
 *
 * @brief   �ⲿ�źŲ�׽���ܳ�ʼ��
 *
 * @param   cap     - select capture mode, refer to CapModeTypeDef
 *
 * @return  none
 */
void TMR1_CapInit(CapModeTypeDef cap)
{
    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_MODE_IN | (cap << 6);
}

/*********************************************************************
 * @fn      TMR1_DMACfg
 *
 * @brief   ����DMA����
 *
 * @param   s           - �Ƿ��DMA����
 * @param   startAddr   - DMA ��ʼ��ַ
 * @param   endAddr     - DMA ������ַ
 * @param   m           - ����DMAģʽ
 *
 * @return  none
 */
void TMR1_DMACfg(uint8_t s, uint16_t startAddr, uint16_t endAddr, DMAModeTypeDef m)
{
    if(s == DISABLE)
    {
        R8_TMR1_CTRL_DMA = 0;
    }
    else
    {
        R16_TMR1_DMA_BEG = startAddr;
        R16_TMR1_DMA_END = endAddr;
        if(m)
            R8_TMR1_CTRL_DMA = RB_TMR_DMA_LOOP | RB_TMR_DMA_ENABLE;
        else
            R8_TMR1_CTRL_DMA = RB_TMR_DMA_ENABLE;
    }
}
