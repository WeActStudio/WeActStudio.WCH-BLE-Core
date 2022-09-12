/********************************** (C) COPYRIGHT *******************************
 * File Name          : SLEEP.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/11/12
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
#ifndef __SLEEP_H
#define __SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * FUNCTIONS
 */

/**
 * @brief   ����˯�߻��ѵķ�ʽ   - RTC���ѣ�����ģʽ
 */
extern void HAL_SleepInit(void);

/**
 * @brief   ����˯��
 *
 * @param   time    - ���ѵ�ʱ��㣨RTC����ֵ��
 *
 * @return  state.
 */
extern uint32_t CH57X_LowPower(uint32_t time);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
