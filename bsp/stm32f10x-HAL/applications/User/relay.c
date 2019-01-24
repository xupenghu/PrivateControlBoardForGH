#include "relay.h"


void relay_init(void)
{
    rt_pin_mode(RELAY_SHORT_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(RELAY_MIDDLE_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(RELAY_LONG_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(RELAY_PEND_PIN, PIN_MODE_OUTPUT);
    change_relay_state(ALL_SWITCH, SWITCH_OFF);
}


int change_relay_state(uint8_t line, relay_state state)
{
     e_switch_line i_line = (e_switch_line)line;
    switch(i_line)
    {
        case SHORT_SWITCH:
        {
            rt_pin_write(RELAY_SHORT_PIN, state);
            if(state == SWITCH_ON)
            {
                rt_pin_write(RELAY_MIDDLE_PIN, SWITCH_OFF);
                rt_pin_write(RELAY_LONG_PIN, SWITCH_OFF);
                rt_pin_write(RELAY_PEND_PIN, SWITCH_OFF);                
            }
        }break;
        case MIDDLE_SWITCH:
        {
            rt_pin_write(RELAY_MIDDLE_PIN, state);
            if(state == SWITCH_ON)
            {
                rt_pin_write(RELAY_SHORT_PIN, SWITCH_OFF);
                rt_pin_write(RELAY_LONG_PIN, SWITCH_OFF);
                rt_pin_write(RELAY_PEND_PIN, SWITCH_OFF);                
            }             
        }break;
        case LONG_SWITCH:
        {
            rt_pin_write(RELAY_LONG_PIN, state);
            if(state == SWITCH_ON)
            {
                rt_pin_write(RELAY_MIDDLE_PIN, SWITCH_OFF);
                rt_pin_write(RELAY_SHORT_PIN, SWITCH_OFF);
                rt_pin_write(RELAY_PEND_PIN, SWITCH_OFF);                
            }            
        }break;
        case ALL_SWITCH:
        {
            rt_pin_write(RELAY_SHORT_PIN, state);
            rt_pin_write(RELAY_MIDDLE_PIN, state);
            rt_pin_write(RELAY_LONG_PIN, state);
            rt_pin_write(RELAY_PEND_PIN, state);                
          
        }break;
        default:{
            rt_pin_write(RELAY_SHORT_PIN, SWITCH_OFF); 
            rt_pin_write(RELAY_MIDDLE_PIN, SWITCH_OFF);
            rt_pin_write(RELAY_LONG_PIN, SWITCH_OFF);
            rt_pin_write(RELAY_PEND_PIN, SWITCH_OFF);              
        }break;
    }
    return RT_EOK;
}




