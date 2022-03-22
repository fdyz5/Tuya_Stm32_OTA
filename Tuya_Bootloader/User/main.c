#include "main.h"
#include "System.h"
#include "delay.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "stmflash.h"

typedef void (*APP_FUNC)();//定义一个函数指针
APP_FUNC jumpapp; //函数指针声明一个函数指针
/*****************************************************************************
函数名称 : JumpToApp
功能描述 : 程序跳转
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void JumpToApp(uint32_t app_address)                  
{
  if(((*(vu32*)app_address)&0x2FFE0000)==0x20000000)
	//app_address存放用户代码的堆栈地址
	//检查用户代码栈顶地址是否合法.
	//判断APP运行的程序栈顶指针落在SRAM区域
	//https://my.oschina.net/u/4581400/blog/4821070
	{ 
		volatile uint32_t JumpAPPaddr;//取出要跳转程序的复位地址
		if (((*(uint32_t*)app_address) &0x2FFE0000 ) == 0x20000000)//再次判断
		{
			JumpAPPaddr = *(volatile uint32_t*)(app_address + 4);//栈顶地址+4存放的是复位地址
			jumpapp = (APP_FUNC) JumpAPPaddr;
			__set_MSP(*(__IO uint32_t*) app_address);//用户代码的栈顶地址设为栈顶指针
			jumpapp();//设置PC指针为复位地址
		}
	}
}
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	/* stm32系统配置 */
	NVIC_Configuration();

	while(1)
	{
		if(ReadFlashTest(UPFLAGADDR) == 0x55555555)  //升级标志
		{
				update_firmware(APP1ADDR,APP2ADDR);//固件升级操作
				EarseFlash_1K(UPFLAGADDR);//擦除升级标志位
				WriteFlash(UPFLAGADDR,nbuff_AAAA,4);//写入AAAAAAAA
				NVIC_SystemReset();//系统复位
		}
		else 
		{
				JumpToApp(APP1ADDR);
		}
	}
}
