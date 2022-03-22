#ifndef __DELAY_H_
#define __DELAY_H_
#include "stm32f10x.h"
#ifndef __DELAY_C_
#define __DELAY_C_  extern
#else 
#define __DELAY_C_
#endif

__DELAY_C_ u32 SysTickIdleTime;//串口中断空闲时间控制


__DELAY_C_ u32 SysTickLedTime;

void DelayInit(void);
void delay_ms(u16 ms);

#endif
