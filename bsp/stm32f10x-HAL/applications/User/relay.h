#ifndef __RELAY_H
#define __RELAY_H	
#include "rtthread.h"
#include <stm32f1xx.h>
#include <drivers/pin.h>


#define RELAY_SHORT_PIN 46
#define RELAY_MIDDLE_PIN 45
#define RELAY_LONG_PIN 43
#define RELAY_PEND_PIN 42

typedef enum _e_switch_line{
    NONE_SWITCH,
    SHORT_SWITCH,
    MIDDLE_SWITCH,
    LONG_SWITCH,
    ALL_SWITCH
    
}e_switch_line;

typedef enum
{
  SWITCH_ON = 0U,
  SWITCH_OFF
}relay_state;

void relay_init(void);

int change_relay_state(uint8_t line, relay_state state);



#endif



