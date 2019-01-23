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
int main(void)
{
    /* user app entry */
	
	led_init();
	while(1)
	{
		led_on();
		rt_thread_mdelay(500);
		led_off();
		rt_thread_mdelay(500);
	}
	
	
    return 0;
}
