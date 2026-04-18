/********************************** (C) COPYRIGHT *******************************
 * File Name          : SLEEP.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2022/01/18
 * Description        : 睡眠配置及其初始化
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "HAL.h"


pfnLowPowerGapProcessCB_t LowPowerGapProcess;
/*******************************************************************************
 * @fn          CH58x_LowPower
 *
 * @brief       启动睡眠
 *
 * @param       time  - 唤醒的时间点（RTC绝对值）
 *
 * @return      state.
 */
__HIGH_CODE
uint32_t CH58x_LowPower(uint32_t time)
{
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    volatile uint32_t i;
    uint32_t time_tign, time_sleep, time_curr;
    unsigned long irq_status;

    // 提前唤醒
    if (time <= WAKE_UP_RTC_MAX_TIME) {
        time_tign = time + (RTC_MAX_COUNT - WAKE_UP_RTC_MAX_TIME);
    } else {
        time_tign = time - WAKE_UP_RTC_MAX_TIME;
    }

    SYS_DisableAllIrq(&irq_status);
    time_curr = RTC_GetCycle32k();
    // 检测睡眠时间
    if (time_tign < time_curr) {
        time_sleep = time_tign + (RTC_MAX_COUNT - time_curr);
    } else {
        time_sleep = time_tign - time_curr;
    }

    // 若睡眠时间小于最小睡眠时间或大于最大睡眠时间，则不睡眠
    if ((time_sleep < SLEEP_RTC_MIN_TIME) || 
        (time_sleep > SLEEP_RTC_MAX_TIME)) {
        SYS_RecoverIrq(irq_status);
        return 2;
    }

    RTC_SetTignTime(time_tign);
    R8_RTC_FLAG_CTRL = (RB_RTC_TMR_CLR | RB_RTC_TRIG_CLR);

#if(DEBUG == Debug_UART0) // 使用其他串口输出打印信息需要修改这行代码
    while((R8_UART0_LSR & RB_LSR_TX_ALL_EMP) == 0)
    {
        __nop();
    }
#endif
    // LOW POWER-sleep模式
    if(!(R8_RTC_FLAG_CTRL&RB_RTC_TRIG_FLAG))
    {
        uint8_t x32Mpw;

        LowPower_Sleep_WFE(RB_PWR_RAM32K | RB_PWR_RAM96K | RB_PWR_EXTEND);

        // 切换32M电流
        x32Mpw = R8_XT32M_TUNE;
        x32Mpw = (x32Mpw & 0xfc) | 0x03; // 150%额定电流
        sys_safe_access_enable();
        R8_XT32M_TUNE = x32Mpw;
        sys_safe_access_disable();

        if(!(R8_RTC_FLAG_CTRL&RB_RTC_TRIG_FLAG)) //非RTC唤醒
        {
            // 注意此时32M还需等待稳定，也可执行一些时钟要求不高的代码
            DelayUs(1400);
            SetSysClock( SYSCLK_FREQ );
            SYS_RecoverIrq(irq_status);
            return 0;
        }

        R8_RTC_FLAG_CTRL = (RB_RTC_TMR_CLR | RB_RTC_TRIG_CLR);
        RTC_SetTignTime(time);
        sys_safe_access_enable();
        R8_HFCK_PWR_CTRL |= RB_CLK_XT32M_KEEP;
        sys_safe_access_disable();
        if(!(R8_RTC_FLAG_CTRL&RB_RTC_TRIG_FLAG)) //非RTC唤醒
        {
            LowPower_Halt_WFE();
        }
        // 恢复时钟
        SetSysClock( SYSCLK_FREQ );
        R8_RTC_FLAG_CTRL = (RB_RTC_TMR_CLR | RB_RTC_TRIG_CLR);
        SYS_RecoverIrq(irq_status);
        HSECFG_Current(HSE_RCur_100); // 降为额定电流(低功耗函数中提升了HSE偏置电流)
        return 0;
    }
    SYS_RecoverIrq(irq_status);
#endif
    return 3;
}

/*******************************************************************************
 * @fn      LowPowerGapProcess_Register
 *
 * @brief   注册低功耗唤醒间隙执行回调
 *
 * @param   None.
 *
 * @return  None.
 */
void LowPowerGapProcess_Register(pfnLowPowerGapProcessCB_t cb)
{
    if((uint32_t)cb & 0x20000000)
    {
        LowPowerGapProcess = cb;
    }
}

/*******************************************************************************
 * @fn      HAL_SleepInit
 *
 * @brief   配置睡眠唤醒的方式   - RTC唤醒，触发模式
 *
 * @param   None.
 *
 * @return  None.
 */
void HAL_SleepInit(void)
{
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    sys_safe_access_enable();
    R8_SLP_WAKE_CTRL |= RB_SLP_RTC_WAKE; // RTC唤醒
    sys_safe_access_disable();
    sys_safe_access_enable();
    R8_RTC_MODE_CTRL |= RB_RTC_TRIG_EN;  // 触发模式
    sys_safe_access_disable();
    PFIC_EnableIRQ(RTC_IRQn);
#endif
}
