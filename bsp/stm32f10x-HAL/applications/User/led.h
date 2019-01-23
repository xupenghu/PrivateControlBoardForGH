#ifndef __LED_H
#define __LED_H	

#include <stm32f1xx.h>
#include <drivers/pin.h>




#define LED_PIN	2  //PC13


void led_init(void);

void led_on(void);

void led_off(void);




#endif



