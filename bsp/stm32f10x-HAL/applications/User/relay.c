#include "relay.h"


void relay_init(void)
{
    rt_pin_mode(S1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(S2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(S3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(S4_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(S5_PIN, PIN_MODE_OUTPUT);
    change_relay_state(ALL_SWITCH, SWITCH_OFF);
}


int change_relay_state(uint8_t line, relay_state state)
{
     e_switch_line i_line = (e_switch_line)line;
    switch(i_line)
    {
        case SHORT_SWITCH:
        {
            rt_pin_write(S1_PIN, state);
            if(state == SWITCH_ON)
            {
                rt_pin_write(S2_PIN, SWITCH_OFF);
                rt_pin_write(S3_PIN, SWITCH_OFF);
                rt_pin_write(S4_PIN, SWITCH_OFF);      
				rt_pin_write(S5_PIN, SWITCH_OFF);   				
            }
        }break;
        case MIDDLE_SWITCH:
        {
            rt_pin_write(S2_PIN, state);
			rt_pin_write(S3_PIN, state);
            if(state == SWITCH_ON)
            {
                rt_pin_write(S1_PIN, SWITCH_OFF);
                rt_pin_write(S4_PIN, SWITCH_OFF);
                rt_pin_write(S5_PIN, SWITCH_OFF);                
            }             
        }break;
        case LONG_SWITCH:
        {
            rt_pin_write(S3_PIN, state);
			rt_pin_write(S4_PIN, state);
			rt_pin_write(S5_PIN, state);
            if(state == SWITCH_ON)
            {
                rt_pin_write(S1_PIN, SWITCH_OFF);
                rt_pin_write(S2_PIN, SWITCH_OFF);              
            }            
        }break;
        case ALL_SWITCH:
        {
            rt_pin_write(S1_PIN, state);
            rt_pin_write(S2_PIN, state);
            rt_pin_write(S3_PIN, state);
            rt_pin_write(S4_PIN, state);     
			rt_pin_write(S5_PIN, state);  			
          
        }break;
        default:{
				rt_pin_write(S1_PIN, SWITCH_OFF);
                rt_pin_write(S2_PIN, SWITCH_OFF);
                rt_pin_write(S3_PIN, SWITCH_OFF);
                rt_pin_write(S4_PIN, SWITCH_OFF);      
				rt_pin_write(S5_PIN, SWITCH_OFF);            
        }break;
    }
    return RT_EOK;
}




