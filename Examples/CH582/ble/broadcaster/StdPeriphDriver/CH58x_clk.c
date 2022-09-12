/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_clk.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH58x_common.h"

/*********************************************************************
 * @fn      LClk32K_Select
 *
 * @brief   32K ��Ƶʱ����Դ
 *
 * @param   hc  - ѡ��32Kʹ���ڲ������ⲿ
 *
 * @return  none
 */
void LClk32K_Select(LClk32KTypeDef hc)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    if(hc == Clk32K_LSI)
    {
        R8_CK32K_CONFIG &= ~RB_CLK_OSC32K_XT;
    }
    else
    {
        R8_CK32K_CONFIG |= RB_CLK_OSC32K_XT;
    }
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      HSECFG_Current
 *
 * @brief   HSE���� ƫ�õ�������
 *
 * @param   c   - 75%,100%,125%,150%
 *
 * @return  none
 */
void HSECFG_Current(HSECurrentTypeDef c)
{
    uint8_t x32M_c;

    x32M_c = R8_XT32M_TUNE;
    x32M_c = (x32M_c & 0xfc) | (c & 0x03);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_XT32M_TUNE = x32M_c;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      HSECFG_Capacitance
 *
 * @brief   HSE���� ���ص�������
 *
 * @param   c   - refer to HSECapTypeDef
 *
 * @return  none
 */
void HSECFG_Capacitance(HSECapTypeDef c)
{
    uint8_t x32M_c;

    x32M_c = R8_XT32M_TUNE;
    x32M_c = (x32M_c & 0x8f) | (c << 4);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_XT32M_TUNE = x32M_c;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      LSECFG_Current
 *
 * @brief   LSE���� ƫ�õ�������
 *
 * @param   c   - 70%,100%,140%,200%
 *
 * @return  none
 */
void LSECFG_Current(LSECurrentTypeDef c)
{
    uint8_t x32K_c;

    x32K_c = R8_XT32K_TUNE;
    x32K_c = (x32K_c & 0xfc) | (c & 0x03);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_XT32K_TUNE = x32K_c;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      LSECFG_Capacitance
 *
 * @brief   LSE���� ���ص�������
 *
 * @param   c   - refer to LSECapTypeDef
 *
 * @return  none
 */
void LSECFG_Capacitance(LSECapTypeDef c)
{
    uint8_t x32K_c;

    x32K_c = R8_XT32K_TUNE;
    x32K_c = (x32K_c & 0x0f) | (c << 4);

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_XT32K_TUNE = x32K_c;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      Calibration_LSI
 *
 * @brief   У׼�ڲ�32Kʱ��
 *
 * @param   cali_Lv - У׼�ȼ�ѡ��    Level_32  -   ��ʱ 1.2ms 1000ppm (32M ��Ƶ)  1100ppm (60M ��Ƶ)
 *                              Level_64  -   ��ʱ 2.2ms 800ppm  (32M ��Ƶ)  1000ppm (60M ��Ƶ)
 *                              Level_128 -   ��ʱ 4.2ms 600ppm  (32M ��Ƶ)  800ppm  (60M ��Ƶ)
 *
 * @return  none
 */
void Calibration_LSI(Cali_LevelTypeDef cali_Lv)
{
    UINT32 i;
    INT32  cnt_offset;
    UINT8  retry = 0;
    INT32  freq_sys;

    freq_sys = GetSysClock();
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_CK32K_CONFIG |= RB_CLK_OSC32K_FILT;
    R8_CK32K_CONFIG &= ~RB_CLK_OSC32K_FILT;
    R8_XT32K_TUNE &= ~3;
    R8_XT32K_TUNE |= 1;

    // �ֵ�
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_OSC_CAL_CTRL &= ~RB_OSC_CNT_TOTAL;
    R8_OSC_CAL_CTRL |= 1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_OSC_CAL_CTRL |= RB_OSC_CNT_EN;
    R16_OSC_CAL_CNT |= RB_OSC_CAL_OV_CLR;
    while( (R8_OSC_CAL_CTRL&RB_OSC_CNT_EN)!= RB_OSC_CNT_EN )
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        SAFEOPERATE;
        R8_OSC_CAL_CTRL |= RB_OSC_CNT_EN;
    }
    while(1)
    {
        while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
        i = R16_OSC_CAL_CNT; // ���ڶ���
        while(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT);
        R16_OSC_CAL_CNT |= RB_OSC_CAL_OV_CLR;
        while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
        i = R16_OSC_CAL_CNT; // ʵʱУ׼�����ֵ
        cnt_offset = (i & 0x3FFF) + R8_OSC_CAL_OV_CNT * 0x3FFF - 2000 * (freq_sys / 1000) / CAB_LSIFQ;
        if(((cnt_offset > -37 * (freq_sys / 1000) / CAB_LSIFQ) && (cnt_offset < 37 * (freq_sys / 1000) / CAB_LSIFQ)) || retry > 2)
            break;
        retry++;
        cnt_offset = (cnt_offset > 0) ? (((cnt_offset * 2) / (37 * (freq_sys / 1000) / CAB_LSIFQ)) + 1) / 2 : (((cnt_offset * 2) / (37 * (freq_sys / 1000) / CAB_LSIFQ)) - 1) / 2;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        SAFEOPERATE;
        R16_INT32K_TUNE += cnt_offset;
    }

    // ϸ��
    // ����ϸ�������󣬶���2�β���ֵ�������Ϊ�����ж�����һ�Σ�����ֻ��һ��
    while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
    i = R16_OSC_CAL_CNT; // ���ڶ���
    R16_OSC_CAL_CNT |= RB_OSC_CAL_OV_CLR;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_OSC_CAL_CTRL &= ~RB_OSC_CNT_TOTAL;
    R8_OSC_CAL_CTRL |= cali_Lv;
    while(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT);
    while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
    i = R16_OSC_CAL_CNT; // ʵʱУ׼�����ֵ
    cnt_offset = (i & 0x3FFF) + R8_OSC_CAL_OV_CNT * 0x3FFF - 4000 * (1 << cali_Lv) * (freq_sys / 1000000) / CAB_LSIFQ * 1000;
    cnt_offset = (cnt_offset > 0) ? ((((cnt_offset * (3200 / (1 << cali_Lv))) / (1366 * (freq_sys / 1000) / CAB_LSIFQ)) + 1) / 2) << 5 : ((((cnt_offset * (3200 / (1 << cali_Lv))) / (1366 * (freq_sys / 1000) / CAB_LSIFQ)) - 1) / 2) << 5;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R16_INT32K_TUNE += cnt_offset;
    R8_OSC_CAL_CTRL &= ~RB_OSC_CNT_EN;
}

/*********************************************************************
 * @fn      RTCInitTime
 *
 * @brief   RTCʱ�ӳ�ʼ����ǰʱ��
 *
 * @param   y       - �����꣬MAX_Y = BEGYEAR + 44
 * @param   mon     - �����£�MAX_MON = 12
 * @param   d       - �����գ�MAX_D = 31
 * @param   h       - ����Сʱ��MAX_H = 23
 * @param   m       - ���÷��ӣ�MAX_M = 59
 * @param   s       - �����룬MAX_S = 59
 *
 * @return  none
 */
void RTC_InitTime(uint16_t y, uint16_t mon, uint16_t d, uint16_t h, uint16_t m, uint16_t s)
{
    uint32_t         t;
    uint16_t         year, month, day, sec2, t32k;
    volatile uint8_t clk_pin;

    year = y;
    month = mon;
    day = 0;
    while(year > BEGYEAR)
    {
        day += YearLength(year - 1);
        year--;
    }
    while(month > 1)
    {
        day += monthLength(IsLeapYear(y), month - 2);
        month--;
    }

    day += d - 1;
    sec2 = (h % 24) * 1800 + m * 30 + s / 2;
    t32k = (s & 1) ? (0x8000) : (0);
    t = sec2;
    t = t << 16 | t32k;

    do
    {
        clk_pin = (R8_CK32K_CONFIG & RB_32K_CLK_PIN);
    } while(clk_pin != (R8_CK32K_CONFIG & RB_32K_CLK_PIN));
    if(!clk_pin)
    {
        while(!clk_pin)
        {
            do
            {
                clk_pin = (R8_CK32K_CONFIG & RB_32K_CLK_PIN);
            } while(clk_pin != (R8_CK32K_CONFIG & RB_32K_CLK_PIN));
        }
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R32_RTC_TRIG = day;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_HI;
    while((R32_RTC_TRIG & 0x3FFF) != (R32_RTC_CNT_DAY & 0x3FFF));
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R32_RTC_TRIG = t;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_LO;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      RTC_GetTime
 *
 * @brief   ��ȡ��ǰʱ��
 *
 * @param   py      - ��ȡ�����꣬MAX_Y = BEGYEAR + 44
 * @param   pmon    - ��ȡ�����£�MAX_MON = 12
 * @param   pd      - ��ȡ�����գ�MAX_D = 31
 * @param   ph      - ��ȡ����Сʱ��MAX_H = 23
 * @param   pm      - ��ȡ���ķ��ӣ�MAX_M = 59
 * @param   ps      - ��ȡ�����룬MAX_S = 59
 *
 * @return  none
 */
void RTC_GetTime(uint16_t *py, uint16_t *pmon, uint16_t *pd, uint16_t *ph, uint16_t *pm, uint16_t *ps)
{
    uint32_t t;
    uint16_t day, sec2, t32k;

    day = R32_RTC_CNT_DAY & 0x3FFF;
    sec2 = R16_RTC_CNT_2S;
    t32k = R16_RTC_CNT_32K;

    t = sec2 * 2 + ((t32k < 0x8000) ? 0 : 1);

    *py = BEGYEAR;
    while(day >= YearLength(*py))
    {
        day -= YearLength(*py);
        (*py)++;
    }

    *pmon = 0;
    while(day >= monthLength(IsLeapYear(*py), *pmon))
    {
        day -= monthLength(IsLeapYear(*py), *pmon);
        (*pmon)++;
    }
    (*pmon)++;
    *pd = day + 1;
    *ph = t / 3600;
    *pm = t % 3600 / 60;
    *ps = t % 60;
}

/*********************************************************************
 * @fn      RTC_SetCycle32k
 *
 * @brief   ����LSE/LSIʱ�ӣ����õ�ǰRTC ������
 *
 * @param   cyc     - �������ڼ�����ֵ��MAX_CYC = 0xA8BFFFFF = 2831155199
 *
 * @return  none
 */
void RTC_SetCycle32k(uint32_t cyc)
{
    volatile uint8_t clk_pin;

    do
    {
        clk_pin = (R8_CK32K_CONFIG & RB_32K_CLK_PIN);
    } while((clk_pin != (R8_CK32K_CONFIG & RB_32K_CLK_PIN)) || (!clk_pin));

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R32_RTC_TRIG = cyc;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_LO;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      RTC_GetCycle32k
 *
 * @brief   ����LSE/LSIʱ�ӣ���ȡ��ǰRTC ������
 *
 * @param   none
 *
 * @return  ��ǰ��������MAX_CYC = 0xA8BFFFFF = 2831155199
 */
uint32_t RTC_GetCycle32k(void)
{
    volatile uint32_t i;

    do
    {
        i = R32_RTC_CNT_32K;
    } while(i != R32_RTC_CNT_32K);

    return (i);
}

/*********************************************************************
 * @fn      RTC_TMRFunCfg
 *
 * @brief   RTC��ʱģʽ���ã�ע�ⶨʱ��׼�̶�Ϊ32768Hz��
 *
 * @param   t   - refer to RTC_TMRCycTypeDef
 *
 * @return  none
 */
void RTC_TMRFunCfg(RTC_TMRCycTypeDef t)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_RTC_MODE_CTRL &= ~(RB_RTC_TMR_EN | RB_RTC_TMR_MODE);
    R8_RTC_MODE_CTRL |= RB_RTC_TMR_EN | (t);
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      RTC_TRIGFunCfg
 *
 * @brief   RTCʱ�䴥��ģʽ����
 *
 * @param   cyc - ��Ե�ǰʱ��Ĵ������ʱ�䣬����LSE/LSIʱ��������
 *
 * @return  none
 */
void RTC_TRIGFunCfg(uint32_t cyc)
{
    uint32_t t;

    t = RTC_GetCycle32k() + cyc;
    if(t > 0xA8C00000)
    {
        t -= 0xA8C00000;
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R32_RTC_TRIG = t;
    R8_RTC_MODE_CTRL |= RB_RTC_TRIG_EN;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      RTC_ModeFunDisable
 *
 * @brief   RTC ģʽ���ܹر�
 *
 * @param   m   - ��Ҫ�رյĵ�ǰģʽ
 *
 * @return  none
 */
void RTC_ModeFunDisable(RTC_MODETypeDef m)
{
    uint8_t i = 0;

    if(m == RTC_TRIG_MODE)
    {
        i |= RB_RTC_TRIG_EN;
    }
    else if(m == RTC_TMR_MODE)
    {
        i |= RB_RTC_TMR_EN;
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    SAFEOPERATE;
    R8_RTC_MODE_CTRL &= ~(i);
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      RTC_GetITFlag
 *
 * @brief   ��ȡRTC�жϱ�־
 *
 * @param   f   - refer to RTC_EVENTTypeDef
 *
 * @return  �жϱ�־״̬
 */
uint8_t RTC_GetITFlag(RTC_EVENTTypeDef f)
{
    if(f == RTC_TRIG_EVENT)
    {
        return (R8_RTC_FLAG_CTRL & RB_RTC_TRIG_FLAG);
    }
    else
    {
        return (R8_RTC_FLAG_CTRL & RB_RTC_TMR_FLAG);
    }
}

/*********************************************************************
 * @fn      RTC_ClearITFlag
 *
 * @brief   ���RTC�жϱ�־
 *
 * @param   f   - refer to RTC_EVENTTypeDef
 *
 * @return  none
 */
void RTC_ClearITFlag(RTC_EVENTTypeDef f)
{
    switch(f)
    {
        case RTC_TRIG_EVENT:
            R8_RTC_FLAG_CTRL = RB_RTC_TRIG_CLR;
            break;
        case RTC_TMR_EVENT:
            R8_RTC_FLAG_CTRL = RB_RTC_TMR_CLR;
            break;
        default:
            break;
    }
}
