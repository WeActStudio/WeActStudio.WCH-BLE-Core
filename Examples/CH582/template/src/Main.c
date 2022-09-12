/*---------------------------------------
 - WeAct Studio Official Link
 - taobao: weactstudio.taobao.com
 - aliexpress: weactstudio.aliexpress.com
 - github: github.com/WeActTC
 - gitee: gitee.com/WeAct-TC
 - blog: www.weact-tc.cn
 ---------------------------------------*/

#include "CH58x_common.h"
#include "board.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Ö÷º¯Êý
 *
 * @return  none
 */
int main(void) {

#if 1
    // Enable Internal DC-DC Power
    PWR_DCDCCfg(ENABLE);
#endif

    SetSysClock(CLK_SOURCE_PLL_60MHz);

    board_button_init();
    board_led_init();

#if 0
    // Low Power Test
    board_led_set(1);
    DelayMs(10);
    board_led_set(0);
    LowPower_Shutdown(0);
#endif

    uint32_t tick, toggle_tick;
    tick = 0;
    toggle_tick = 250;
    while(1)
    {
        tick++;
        if (tick % toggle_tick == 0)
        {
            board_led_toggle();
        }
        if (board_button_getstate())
        {
            while (board_button_getstate())
            {
                DelayMs(50);
            }
            if (toggle_tick == 250)
            {
                toggle_tick = 100;
            }
            else
            {
                toggle_tick = 250;
            }
        }
        DelayMs(1);
    }
}
