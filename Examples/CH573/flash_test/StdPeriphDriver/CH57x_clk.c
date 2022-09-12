/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_clk.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH57x_common.h"

uint16_t Int32K_Tune_FLASH = 0;
uint16_t Int32K_Tune_RAM = 0;

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
    R8_XT32K_TUNE = x32K_c;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      Calibration_LSI_FLASH
 *
 * @brief   У׼��FLASH������ʱ���ڲ�32Kʱ��
 *
 * @param   none
 *
 * @return  �����֮����λ��
 */
uint16_t Calibration_LSI_FLASH(void)
{
    uint16_t     rev, basev;
    uint32_t     calv;
    uint16_t     i;
    uint16_t     loc, loc_t;
    float        CNT_STEP_K;
    signed short diff_1, diff_2, diffc;
    uint8_t      k = 0;

    /* ���ݵ�ǰʱ�ӻ�ȡ���ֵ��б�ʣ�T-step�� */
    rev = R16_CLK_SYS_CFG & 0xff;
    if((rev & RB_CLK_SYS_MOD) == (2 << 6))
    { // 32M����Ƶ
        calv = ((5 * 32000000 + (CAB_LSIFQ >> 1)) / CAB_LSIFQ);
        CNT_STEP_K = -1.6;
    }
    else if((rev & RB_CLK_SYS_MOD) == (1 << 6))
    { // PLL���з�Ƶ
        calv = (((uint32_t)5 * 480000000 / (rev & 0x1f) + (CAB_LSIFQ >> 1)) / CAB_LSIFQ);
        CNT_STEP_K = -0.1 * (rev & 0x1f);
    }
    else if((rev & RB_CLK_SYS_MOD) == (0 << 6))
    { // 32M���з�Ƶ
        calv = ((5 * 32000000 / (rev & 0x1f) + (CAB_LSIFQ >> 1)) / CAB_LSIFQ);
        CNT_STEP_K = -1.6 * (rev & 0x1f);
    }
    else
    { // 32K����Ƶ
        calv = (5);
        CNT_STEP_K = 0;
    }
    basev = calv; // ��ȡУ׼���ֵ

    if(Int32K_Tune_FLASH)
    {
        loc = Int32K_Tune_FLASH;
    }
    else
    {
        loc = 2048;
    }
    //  if (loc == 2048)
    //    loc = 1837; //10040.625-1.640625*5000;  //��������

    diff_2 = 0;
    diffc = 0;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_OSC_CAL_CTRL = RB_OSC_CNT_EN;
    do
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_INT32K_TUNE = loc;
        R8_SAFE_ACCESS_SIG = 0;

        /* ��ȡ��ǰֵ */
        while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
        i = R16_OSC_CAL_CNT; // ���ڶ���
        while(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT);
        while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
        i = R16_OSC_CAL_CNT; // ʵʱУ׼�����ֵ
        k++;
        diff_1 = i - basev;

        Int32K_Tune_FLASH = loc;
        if(diff_1 == 0)
        {
            return 0; // У׼����
        }
        else if((diff_1 * diff_2) < 0)
        { // ��������֮��
            if((diffc == 1) || (diffc == -1) || (diffc == 0))
            {
                // ���������
                if(diff_2 < 0)
                {
                    diff_2 = ~(diff_2 - 1);
                }
                else
                {
                    diff_1 = ~(diff_1 - 1);
                }

                if(diff_1 > diff_2)
                {
                    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
                    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
                    R16_INT32K_TUNE = loc_t;
                    R8_SAFE_ACCESS_SIG = 0;

                    return (diff_2 * 10000 / basev); // �������ֵ�����֮
                }
                else
                {
                    return (diff_1 * 10000 / basev);
                }
            }
        }

        if(((i > basev ? (i - basev) : (basev - i)) * 10000 / basev) < 11)
        {
            return ((i > basev ? (i - basev) : (basev - i)) * 10000 / basev);
        }
        // ������һ��ֵ
        diff_2 = diff_1;
        loc_t = loc;
        diffc = diff_1 * CNT_STEP_K;
        loc = loc - diffc;
        if(loc == loc_t)
        {
            if(diff_1 > 0)
            {
                loc = loc + 1; // ��ǰƵ��ƫС
            }
            else
            {
                loc = loc - 1; // ��ǰƵ��ƫ��
            }
        }
    } while(k < 20);

    Int32K_Tune_FLASH = loc;
    return ((i > basev ? (i - basev) : (basev - i)) * 10000 / basev);
}

/*********************************************************************
 * @fn      Get_Calibration_Cnt_RAM
 *
 * @brief   ��ȡ��RAM�м�����У׼����ֵ
 *
 * @param   loc - TUNEֵ
 *
 * @return  ����ֵ
 */
__attribute__((section(".highcode")))
uint16_t Get_Calibration_Cnt_RAM(uint16_t loc)
{
    uint16_t i;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_INT32K_TUNE = loc;
    R8_SAFE_ACCESS_SIG = 0;
    /* ��ȡ��ǰֵ */
    while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
    i = R16_OSC_CAL_CNT; // ���ڶ���
    while(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT);
    while(!(R8_OSC_CAL_CTRL & RB_OSC_CNT_HALT));
    i = R16_OSC_CAL_CNT;
    return i;
}

/*********************************************************************
 * @fn      Calibration_LSI_RAM
 *
 * @brief   У׼��RAM������ʱ���ڲ�32Kʱ��
 *
 * @param   none
 *
 * @return  �����֮����λ��
 */
uint16_t Calibration_LSI_RAM(void)
{
    uint16_t     rev, basev;
    uint32_t     calv;
    uint16_t     i;
    uint16_t     loc, loc_t;
    float        CNT_STEP_K;
    signed short diff_1, diff_2, diffc;
    uint8_t      k = 0;

    /* ���ݵ�ǰʱ�ӻ�ȡ���ֵ��б�ʣ�T-step�� */
    rev = R16_CLK_SYS_CFG & 0xff;
    if((rev & RB_CLK_SYS_MOD) == (2 << 6))
    { // 32M����Ƶ
        calv = ((5 * 32000000 + (CAB_LSIFQ >> 1)) / CAB_LSIFQ);
        CNT_STEP_K = -1.6;
    }
    else if((rev & RB_CLK_SYS_MOD) == (1 << 6))
    { // PLL���з�Ƶ
        calv = (((uint32_t)5 * 480000000 / (rev & 0x1f) + (CAB_LSIFQ >> 1)) / CAB_LSIFQ);
        CNT_STEP_K = -0.1 * (rev & 0x1f);
    }
    else if((rev & RB_CLK_SYS_MOD) == (0 << 6))
    { // 32M���з�Ƶ
        calv = ((5 * 32000000 / (rev & 0x1f) + (CAB_LSIFQ >> 1)) / CAB_LSIFQ);
        CNT_STEP_K = -1.6 * (rev & 0x1f);
    }
    else
    { // 32K����Ƶ
        calv = (5);
        CNT_STEP_K = 0;
    }
    basev = calv; // ��ȡУ׼���ֵ

    if(Int32K_Tune_RAM)
    {
        loc = Int32K_Tune_RAM;
    }
    else
    {
        loc = 2048;
    }
    //  if (loc == 2048)
    //    loc = 1837; //10040.625-1.640625*5000;  //��������

    diff_2 = 0;
    diffc = 0;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_OSC_CAL_CTRL = RB_OSC_CNT_EN;
    do
    {
        i = Get_Calibration_Cnt_RAM(loc); // ʵʱУ׼�����ֵ
        k++;
        diff_1 = i - basev;

        Int32K_Tune_RAM = loc;
        if(diff_1 == 0)
        {
            return 0; // У׼����
        }
        else if((diff_1 * diff_2) < 0)
        { // ��������֮��
            if((diffc == 1) || (diffc == -1) || (diffc == 0))
            {
                // ���������
                if(diff_2 < 0)
                {
                    diff_2 = ~(diff_2 - 1);
                }
                else
                {
                    diff_1 = ~(diff_1 - 1);
                }

                if(diff_1 > diff_2)
                {
                    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
                    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
                    R16_INT32K_TUNE = loc_t;
                    R8_SAFE_ACCESS_SIG = 0;

                    return (diff_2 * 10000 / basev); // �������ֵ�����֮
                }
                else
                {
                    return (diff_1 * 10000 / basev);
                }
            }
        }

        if(((i > basev ? (i - basev) : (basev - i)) * 10000 / basev) < 11)
        {
            return ((i > basev ? (i - basev) : (basev - i)) * 10000 / basev);
        }
        // ������һ��ֵ
        diff_2 = diff_1;
        loc_t = loc;
        diffc = diff_1 * CNT_STEP_K;
        loc = loc - diffc;
        if(loc == loc_t)
        {
            if(diff_1 > 0)
            {
                loc = loc + 1; // ��ǰƵ��ƫС
            }
            else
            {
                loc = loc - 1; // ��ǰƵ��ƫ��
            }
        }
    } while(k < 20);

    Int32K_Tune_RAM = loc;
    return ((i > basev ? (i - basev) : (basev - i)) * 10000 / basev);
}

/*********************************************************************
 * @fn      LSI_SetTune_FLASH
 *
 * @brief   ������FLASH������ʱ���ڲ�32kУ׼ֵ
 *
 * @param   none
 *
 * @return  none
 */
void LSI_SetTune_FLASH(void)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_INT32K_TUNE = Int32K_Tune_FLASH;
    R8_SAFE_ACCESS_SIG = 0;
}

/*********************************************************************
 * @fn      LSI_SetTune_RAM
 *
 * @brief   ������RAM������ʱ���ڲ�32kУ׼ֵ
 *
 * @param   none
 *
 * @return  none
 */
void LSI_SetTune_RAM(void)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_INT32K_TUNE = Int32K_Tune_RAM;
    R8_SAFE_ACCESS_SIG = 0;
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
    } while((clk_pin != (R8_CK32K_CONFIG & RB_32K_CLK_PIN)) || (!clk_pin));

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R32_RTC_TRIG = day;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_HI;
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

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
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

