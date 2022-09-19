/*---------------------------------------
 - WeAct Studio Official Link
 - taobao: weactstudio.taobao.com
 - aliexpress: weactstudio.aliexpress.com
 - github: github.com/WeActTC
 - gitee: gitee.com/WeAct-TC
 - blog: www.weact-tc.cn
 ---------------------------------------*/

#include "CH57x_common.h"
#include "config.h"
#include "HAL.h"
#include "broadcaster.h"

uint8_t TxBuff[] = "This is a tx exam\r\n";
uint8_t RxBuff[100];
uint8_t trigB;

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] =
    {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   主循环
 *
 * @return  none
 */
__attribute__((section(".highcode")))
void Main_Circulation()
{
    while(1)
    {
        TMOS_SystemProcess();
    }
}

void key_callback(uint8_t keys)
{
    if (keys&HAL_KEY_SW_1)
    {
        printf("key1 pressed\r\n");
        HalLedSet(HAL_LED_ALL, HAL_LED_MODE_OFF);
        HalLedBlink(1, 2, 30, 1000);
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
int main()
{
#if(defined(DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
    PWR_DCDCCfg(ENABLE);
#endif
    SetSysClock(CLK_SOURCE_PLL_60MHz);
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
#endif
#ifdef DEBUG
    GPIOA_SetBits(bTXD1);
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
#endif
    PRINT("%s\n", VER_LIB);
    CH57X_BLEInit();
    HAL_Init();
    HalKeyConfig(key_callback);
    GAPRole_BroadcasterInit();
    Broadcaster_Init();
    Main_Circulation();
}
