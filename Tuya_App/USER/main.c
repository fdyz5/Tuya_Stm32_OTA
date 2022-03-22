#include "stm32f10x.h"
#include "wifi.h"
#include "usart.h"
#include "delay.h"
#include "stmflash.h"

extern void Connect_Wifi(void);
extern uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {	
  GPIO_InitTypeDef  GPIO_InitStructure;
	 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	    //使能PB端口时钟
	 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //对PB4管脚进行重新映射

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_4;	            //LED1-->PE.5推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  	       //初始化GPIO
  GPIO_SetBits(GPIOB,GPIO_Pin_6); 
	GPIO_SetBits(GPIOB,GPIO_Pin_4);

	 //PB5管脚作为 配网键 输入管脚
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE4,3
	 
	 SCB->VTOR = FLASH_BASE_ADDR | 0x4000;//设置中断偏移
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 uart_init(9600);	 //串口初始化为115200
	 wifi_protocol_init();//wifi协议初始化

  while(1)
	{
		Connect_Wifi();
		wifi_uart_service();
	  //GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	  //GPIO_SetBits(GPIOE,GPIO_Pin_5);
		//Delay(3000000);
		//GPIO_SetBits(GPIOB,GPIO_Pin_5);
		//GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		//Delay(3000000);
	}
 }
