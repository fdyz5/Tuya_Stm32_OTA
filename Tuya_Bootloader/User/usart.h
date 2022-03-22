#ifndef __USART_H
#define __USART_H
#include <stm32f10x.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"	
#ifndef USART_C_//如果没有定义
#define USART_C_ extern
#else
#define USART_C_
#endif

#define USART_n		USART2  //定义使用printf函数
#define USART2_REC_LEN  			200  	//定义USART2最大接收字节数
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART2_RX_STA;         		//接收状态标记	
//函数声明
void USART2_Init(u32 bound);//串口2初始化并启动
void USART2_printf(char* fmt,...); //串口2的专用printf函数

#endif


