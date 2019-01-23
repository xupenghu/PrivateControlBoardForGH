#include "led.h"


void led_init(void)
{
	rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
}

void led_on(void)
{
	rt_pin_write(LED_PIN,PIN_LOW);
}

void led_off(void)
{
	rt_pin_write(LED_PIN,PIN_HIGH);
}




















