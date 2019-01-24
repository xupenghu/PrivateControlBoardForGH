#ifndef __ULTRA_H
#define __ULTRA_H	
#include "rtthread.h"

//对应的距离 单位mm
#define MIDDLE_DISTANCE  (100)   
#define LONG_DISTANCE    (120)
#define SHORT_DISTANCE   (80)


typedef struct _ultra_t
{
    uint8_t temp;
    uint16_t distance;
    uint16_t precision;
}ultra_t;

int ultra_init(void);
int get_ultra_data(ultra_t * p_ultra, uint16_t timeout);

#endif



