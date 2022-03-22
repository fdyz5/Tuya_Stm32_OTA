#define __DELAY_C_

#include "usart.h"
#include "main.h"
#include "delay.h"

u32 SysTickCntMs = 0;//延时函数使用
u32 SysTickIdleTime = 500;//设置串口空闲时间(MS)


/****************
系统定时器初始化
****************/
void DelayInit(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);//1Ms
}


void delay_ms(u16 ms)
{
  SysTickCntMs = 0;
	while(SysTickCntMs<ms);
}

/*系统定时器中断*/
void SysTick_Handler(void)
{	
	
	if(Usart1ReadCnt!=0)//串口接收到数据
	{
	  Usart1IdleCnt++;//变量累加(该变量在串口接收时清零)
		if(Usart1IdleCnt>=SysTickIdleTime)//累加到50,接收到一串完整的数据
		{
		  Usart1IdleCnt = 0;
			Usart1ReadCntCopy = Usart1ReadCnt;
			Usart1ReadCnt = 0;
			Usart1ReadFlage = 1;
			
			if(UpdataStartFlage)
			{
				UpdataReadEndFlage = 1;
			}
		}
	}
}


