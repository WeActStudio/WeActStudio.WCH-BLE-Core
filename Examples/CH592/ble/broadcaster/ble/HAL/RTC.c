/********************************** (C) COPYRIGHT *******************************
 * File Name          : RTC.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2022/01/18
 * Description        : RTC���ü����ʼ��
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* ͷ�ļ����� */
#include "HAL.h"

/*********************************************************************
 * CONSTANTS
 */
#define RTC_INIT_TIME_HOUR      0
#define RTC_INIT_TIME_MINUTE    0
#define RTC_INIT_TIME_SECEND    0

/***************************************************
 * Global variables
 */
volatile uint32_t RTCTigFlag;

/*******************************************************************************
 * @fn      RTC_SetTignTime
 *
 * @brief   ����RTC����ʱ��
 *
 * @param   time    - ����ʱ��.
 *
 * @return  None.
 */
void RTC_SetTignTime(uint32_t time)
{
    sys_safe_access_enable();
    R32_RTC_TRIG = time;
    sys_safe_access_disable();
    RTCTigFlag = 0;
}

/*******************************************************************************
 * @fn      RTC_IRQHandler
 *
 * @brief   RTC�жϴ���
 *
 * @param   None.
 *
 * @return  None.
 */
__INTERRUPT
__HIGH_CODE
void RTC_IRQHandler(void)
{
    R8_RTC_FLAG_CTRL = (RB_RTC_TMR_CLR | RB_RTC_TRIG_CLR);
    RTCTigFlag = 1;
}

/*******************************************************************************
 * @fn      SYS_GetClockValue
 *
 * @brief   ��ȡRTC��ǰ����ֵ
 *
 * @param   None.
 *
 * @return  None.
 */
__HIGH_CODE
static uint32_t SYS_GetClockValue(void)
{
    volatile uint32_t i;

    do
    {
        i = R32_RTC_CNT_32K;
    } while(i != R32_RTC_CNT_32K);

    return (i);
}
/*******************************************************************************
 * @fn      HAL_Time0Init
 *
 * @brief   ϵͳ��ʱ����ʼ��
 *
 * @param   None.
 *
 * @return  None.
 */
void HAL_TimeInit(void)
{
    bleClockConfig_t conf;
#if(CLK_OSC32K)
    sys_safe_access_enable();
    R8_CK32K_CONFIG &= ~(RB_CLK_OSC32K_XT | RB_CLK_XT32K_PON);
    sys_safe_access_disable();
    sys_safe_access_enable();
    R8_CK32K_CONFIG |= RB_CLK_INT32K_PON;
    sys_safe_access_disable();
    Lib_Calibration_LSI();
#else
    LSECFG_Capacitance(LSECap_13p);
    LSECFG_Current(LSE_RCur_200);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_CK32K_CONFIG &= ~RB_CLK_INT32K_PON;
    R8_CK32K_CONFIG |= RB_CLK_XT32K_PON;
    R8_SAFE_ACCESS_SIG = 0;

    DelayMs(200);

    LSECFG_Current(LSE_RCur_100);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_CK32K_CONFIG |= RB_CLK_OSC32K_XT;
    R8_SAFE_ACCESS_SIG = 0;

    DelayUs(32);
#endif
    RTC_InitTime(2023, 10, 1, 0, 0, 0); //RTCʱ�ӳ�ʼ����ǰʱ��

    tmos_memset( &conf, 0, sizeof(bleClockConfig_t) );
    conf.ClockAccuracy = CLK_OSC32K ? 1000 : 50;
    conf.ClockFrequency = CAB_LSIFQ;
    conf.ClockMaxCount = RTC_MAX_COUNT;
    conf.getClockValue = SYS_GetClockValue;
    TMOS_TimerInit( &conf );

}

/******************************** endfile @ time ******************************/
