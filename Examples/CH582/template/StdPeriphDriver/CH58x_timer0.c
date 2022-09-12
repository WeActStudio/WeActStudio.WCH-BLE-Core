/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_timer0.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH58x_common.h"

/*********************************************************************
 * @fn      TMR0_TimerInit
 *
 * @brief   ��ʱ���ܳ�ʼ��
 *
 * @param   t       - ��ʱʱ�䣬���ڵ�ǰϵͳʱ��Tsys, ���ʱ���� 67108864
 *
 * @return  none
 */
void TMR0_TimerInit(uint32_t t)
{
    R32_TMR0_CNT_END = t;
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN;
}

/*********************************************************************
 * @fn      TMR0_EXTSingleCounterInit
 *
 * @brief   ���ؼ������ܳ�ʼ��
 *
 * @param   cap     - �ɼ���������
 *
 * @return  none
 */
void TMR0_EXTSingleCounterInit(CapModeTypeDef cap)
{
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_CAP_COUNT | RB_TMR_MODE_IN | (cap << 6);
}

/*********************************************************************
 * @fn      TMR0_PWMInit
 *
 * @brief   PWM �����ʼ��
 *
 * @param   pr      - select wave polar, refer to PWMX_PolarTypeDef
 * @param   ts      - set pwm repeat times, refer to PWM_RepeatTsTypeDef
 *
 * @return  none
 */
void TMR0_PWMInit(PWMX_PolarTypeDef pr, PWM_RepeatTsTypeDef ts)
{
    //    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_OUT_EN | (pr << 4) | (ts << 6);
}

/*********************************************************************
 * @fn      TMR0_CapInit
 *
 * @brief   �ⲿ�źŲ�׽���ܳ�ʼ��
 *
 * @param   cap     - select capture mode, refer to CapModeTypeDef
 *
 * @return  none
 */
void TMR0_CapInit(CapModeTypeDef cap)
{
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_MODE_IN | (cap << 6);
}
