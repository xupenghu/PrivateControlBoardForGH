/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>
#include "led.h"
#include "oled.h"
#include "ultra.h"
#include "relay.h"


int main(void)
{
    ultra_t ultra;    
    //外设初始化
	led_init();
    OLED_Init();
    rt_thread_idle_sethook(OLED_Refresh_Gram);  //利用空闲钩子函数刷新oled显示
    OLED_ShowString(0,0,"  MainControl  ",16);
    OLED_ShowString(0,16,"distance:      mm",12);
    OLED_ShowString(0,16+12,      "short  state:  close  ",12);
    OLED_ShowString(0,16+12+12,   "middle state:  close  ",12);
    OLED_ShowString(0,16+12+12+12,"large  state:  close ",12);
    if(ultra_init()!= RT_EOK)
    {
        rt_kprintf("ultra module init error!!!!");
    }
    ultra.precision = 3;  //测量精度3mm
    
	while(1)
	{
        get_ultra_data(&ultra, 100);
        OLED_ShowNum(60,16,ultra.distance,3,12);
        //打开电容阵列对应的开关
        if(ultra.distance>(SHORT_DISTANCE-ultra.precision)&&ultra.distance<(SHORT_DISTANCE+ultra.precision))
        {
            change_relay_state(SHORT_SWITCH, SWITCH_ON); 
            OLED_ShowString(0,16+12,      "short  state:  open  ",12);
            OLED_ShowString(0,16+12+12,   "middle state:  close  ",12);
            OLED_ShowString(0,16+12+12+12,"large  state:  close ",12);            
        }
        else if(ultra.distance>(MIDDLE_DISTANCE-ultra.precision)&&ultra.distance<(MIDDLE_DISTANCE+ultra.precision))
        {
            change_relay_state(MIDDLE_SWITCH, SWITCH_ON);
            OLED_ShowString(0,16+12,      "short  state:  close  ",12);
            OLED_ShowString(0,16+12+12,   "middle state:  open  ",12);
            OLED_ShowString(0,16+12+12+12,"large  state:  close ",12); 
        }
        else if(ultra.distance>(LONG_DISTANCE-ultra.precision)&&ultra.distance<(LONG_DISTANCE+ultra.precision))
        {
            change_relay_state(LONG_SWITCH, SWITCH_ON);
            OLED_ShowString(0,16+12,      "short  state:  close  ",12);
            OLED_ShowString(0,16+12+12,   "middle state:  close  ",12);
            OLED_ShowString(0,16+12+12+12,"large  state:  open ",12); 
        }
        else
        {
            change_relay_state(ALL_SWITCH, SWITCH_OFF);
            OLED_ShowString(0,16+12,      "short  state:  close  ",12);
            OLED_ShowString(0,16+12+12,   "middle state:  close  ",12);
            OLED_ShowString(0,16+12+12+12,"large  state:  close ",12); 
        }
        
        led_on();
        rt_thread_mdelay(50);
        led_off();
        rt_thread_mdelay(200);
        
        
	}
	
	
    return 0;
}
