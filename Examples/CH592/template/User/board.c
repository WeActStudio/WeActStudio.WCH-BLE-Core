/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActStudio
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "board.h"

void board_button_init(void)
{
   GPIOB_ModeCfg(GPIO_Pin_22, GPIO_ModeIN_PU);
}

uint8_t board_button_getstate(void)
{
    return !GPIOB_ReadPortPin(GPIO_Pin_22);
}

void board_led_init(void)
{
    GPIOA_SetBits(GPIO_Pin_8);
    GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeOut_PP_5mA);
}

void board_led_toggle(void)
{
    GPIOA_InverseBits(GPIO_Pin_8);
}

void board_led_set(uint8_t set)
{
    if (set)
        GPIOA_ResetBits(GPIO_Pin_8);
    else
        GPIOA_SetBits(GPIO_Pin_8);
}
