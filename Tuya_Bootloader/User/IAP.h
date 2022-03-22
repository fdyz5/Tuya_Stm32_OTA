#ifndef __IAP_H__
#define __IAP_H__
#include <stm32f10x.h>

#ifndef IAP_C_//如果没有定义
#define IAP_C_ extern
#else
#define IAP_C_
#endif

typedef  void (*iapfun)(void);				//定义一个函数类型的参数.  			   
void iap_load_app(u32 appxaddr);			//跳转到APP程序执行
#endif

