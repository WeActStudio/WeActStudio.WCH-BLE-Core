/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_SYS.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description        : head file(ch585/ch584)
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __CH58x_SYS_H__
#define __CH58x_SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*MachineMode_Call_func)(void);

/**
 * @brief  rtc interrupt event define
 */
typedef enum
{
    RST_STATUS_SW = 0, // 软件复位
    RST_STATUS_RPOR,   // 上电复位
    RST_STATUS_WTR,    // 看门狗超时复位
    RST_STATUS_MR,     // 外部手动复位
    RST_STATUS_LRM0,   // 唤醒复位-软复位引起
    RST_STATUS_GPWSM,  // 下电模式唤醒复位
    RST_STATUS_LRM1,   //	唤醒复位-看门狗引起
    RST_STATUS_LRM2,   //	唤醒复位-手动复位引起

} SYS_ResetStaTypeDef;

/**
 * @brief  rtc interrupt event define
 */
typedef enum
{
    INFO_ROM_READ = 0, // FlashROM 代码和数据区 是否可读
    INFO_RESET_EN = 2, // RST#外部手动复位输入功能是否开启
    INFO_BOOT_EN,      // 系统引导程序 BootLoader 是否开启
    INFO_DEBUG_EN,     // 系统仿真调试接口是否开启
    INFO_LOADER,       // 当前系统是否处于Bootloader 区
    STA_SAFEACC_ACT,   // 当前系统是否处于安全访问状态，否则RWA属性区域不可访问

} SYS_InfoStaTypeDef;

/**
 * @brief  IWDG_KR_Key
 */
typedef enum
{
    KEY_UNPROTECT = 0x5555,        //解除保护
    KEY_RELOADING_COUNT = 0xAAAA,  //重装载计数值
    KEY_START_IWDG = 0xCCCC        //启动看门狗
} IWDG_KR_Key;

/**
 * @brief  IWDG Prescaler factor
 */
typedef enum
{
    IWDG_PR_4 = 0, // 4分频
    IWDG_PR_8,     // 8分频
    IWDG_PR_16,    // 16分频
    IWDG_PR_32,    // 32分频
    IWDG_PR_64,    // 64分频
    IWDG_PR_128,   // 128分频
    IWDG_PR_256,   // 256分频
    IWDG_PR_512    // 512分频
} IWDG_32K_PR;

/**
 * @brief  获取芯片ID类，一般为固定值
 */
#define SYS_GetChipID()      R8_CHIP_ID

/**
 * @brief  获取安全访问ID，一般为固定值
 */
#define SYS_GetAccessID()    R8_SAFE_ACCESS_ID

/**
 * @brief   配置系统运行时钟
 *
 * @param   sc      - 系统时钟源选择 refer to SYS_CLKTypeDef
 */
void SetSysClock(SYS_CLKTypeDef sc);

/**
 * @brief   注册机械模式执行函数，并在机械模式下调用
 *
 * @param   func    -   用于在机械模式下执行的函数
 */
void MachineMode_Call(MachineMode_Call_func func);

/**
 * @brief  使能预取指令功能
 */
void SYS_EnablePI(void);

/**
 * @brief   获取当前系统时钟
 *
 * @return  Hz
 */
uint32_t GetSysClock(void);

/**
 * @brief   获取当前系统信息状态
 *
 * @param   i       - refer to SYS_InfoStaTypeDef
 *
 * @return  是否开启
 */
uint8_t SYS_GetInfoSta(SYS_InfoStaTypeDef i);

/**
 * @brief   获取系统上次复位状态
 *
 * @return  refer to SYS_ResetStaTypeDef
 */
#define SYS_GetLastResetSta()    (R8_RESET_STATUS & RB_RESET_FLAG)

/**
 * @brief   执行系统软件复位
 */
void SYS_ResetExecute(void);

/**
 * @brief   设置复位保存寄存器的值，不受手动复位、 软件复位、 看门狗复位或者普通唤醒复位的影响
 *
 * @param   i       - refer to SYS_InfoStaTypeDef
 */
#define SYS_ResetKeepBuf(d)    (R8_GLOB_RESET_KEEP = d)

/**
 * @brief   关闭所有中断，并保留当前中断值
 *
 * @param   pirqv   - 当前保留中断值
 */
void SYS_DisableAllIrq(uint32_t *pirqv);

/**
 * @brief   恢复之前关闭的中断值
 *
 * @param   irq_status  - 当前保留中断值
 */
void SYS_RecoverIrq(uint32_t irq_status);

/**
 * @brief   获取当前系统(SYSTICK)计数值
 *
 * @return  当前计数值
 */
uint32_t SYS_GetSysTickCnt(void);

/**
 * @brief   加载看门狗计数初值，递增型
 *
 * @param   c       - 看门狗计数初值
 */
#define WWDG_SetCounter(c)    (R8_WDOG_COUNT = c)

/**
 * @brief   看门狗定时器溢出中断使能
 *
 * @param   s       - 溢出是否中断
 */
void WWDG_ITCfg(FunctionalState s);

/**
 * @brief   看门狗定时器复位功能
 *
 * @param   s       - 溢出是否复位
 */
void WWDG_ResetCfg(FunctionalState s);

/**
 * @brief   获取当前看门狗定时器溢出标志
 *
 * @return  看门狗定时器溢出标志
 */
#define WWDG_GetFlowFlag()    (R8_RST_WDOG_CTRL & RB_WDOG_INT_FLAG)

/**
 * @brief   清除看门狗中断标志，重新加载计数值也可清除
 */
void WWDG_ClearFlag(void);

/**
 * @brief   uS 延时
 *
 * @param   t       - 时间参数
 */
void mDelayuS(uint16_t t);

/**
 * @brief   mS 延时
 *
 * @param   t       - 时间参数
 */
void mDelaymS(uint16_t t);

/**
 * @brief   获取写保护状态
 *
 * @return  1:禁止操作相应字段; 0:解除保护
 */
#define  IWDG_WR_Protect()       (R32_IWDG_CFG >> 30 & 0x01)

/**
 * @brief   获取看门狗计数器
 *
 * @return  COUNT
 */
#define  IWDG_Count_Get()        ((R32_IWDG_CFG >> 16) & 0xFFF)

/**
 * @brief   获取配置寄存器更新标志，关闭写保护位生效
 *
 * @return  1:寄存器更新; 0:寄存器不更新
 */
#define  IWDG_PVU_Get()          (R32_IWDG_CFG >> 15 & 0x01)

/**
 * @brief   启动看门狗/解除读保护/喂狗/重装载计数值
 *
 * @param   kr       - 控制值
 */
void IWDG_KR_Set(IWDG_KR_Key kr);

/**
 * @brief   配置预分频，关闭写保护位生效
 *
 * @param   pr       - 分频系数
 */
uint8_t IWDG_PR_Set(IWDG_32K_PR pr);

/**
 * @brief   配置计数器重装载值，关闭写保护位生效
 *
 * @param   rlr       - 计数器重装载值
 */
uint8_t IWDG_RLR_Set(uint16_t rlr);

/**
 * @brief   独立看门狗计数跟随内核停止使能，仅在调试模式下生效
 *
 * @param   s       - 是否使能
 */
uint8_t IWDG_FollowCoreStop(FunctionalState s);

/**
 * @brief   独立看门狗使能
 *
 * @param   pr     - 预分频
 *          rlr    - 计数器重装载值
 */
uint8_t IWDG_Enable(IWDG_32K_PR pr, uint16_t rlr);

/**
 * @brief   系统必须定期重装载看门狗计数值以防止复位
 *
 * @param   none
 */
void IWDG_Feed(void);

/**
 * @brief Enter safe access mode.
 * 
 * @NOTE: After enter safe access mode, about 16 system frequency cycles 
 * are in safe mode, and one or more secure registers can be rewritten 
 * within the valid period. The safe mode will be automatically 
 * terminated after the above validity period is exceeded.
 *  if sys_safe_access_enable() is called,
 *  you must call sys_safe_access_disable() before call sys_safe_access_enable() again.
 */
#define sys_safe_access_enable()        do{volatile uint32_t mpie_mie;mpie_mie=__risc_v_disable_irq();SAFEOPERATE;\
                                        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;SAFEOPERATE;

#define sys_safe_access_disable()       R8_SAFE_ACCESS_SIG = 0;__risc_v_enable_irq(mpie_mie);SAFEOPERATE;}while(0)

#ifdef __cplusplus
}
#endif

#endif // __CH58x_SYS_H__
