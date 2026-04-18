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
    GPIOB_SetBits(GPIO_Pin_6);
    GPIOB_ModeCfg(GPIO_Pin_6, GPIO_ModeOut_PP_5mA);
}

void board_led_toggle(void)
{
    GPIOB_InverseBits(GPIO_Pin_6);
}

void board_led_set(uint8_t set)
{
    if (set)
        GPIOB_ResetBits(GPIO_Pin_6);
    else
        GPIOB_SetBits(GPIO_Pin_6);
}
