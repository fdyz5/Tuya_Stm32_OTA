#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include <stm32f10x.h>

extern unsigned char nbuff_5555[];
extern unsigned char nbuff_AAAA[];

#define FLASH_BASE_ADDR 0x8000000 

#define APP1  0x4000
#define APP2  0xA000
#define UPFLAG1 0xF800

#define APP1ADDR (FLASH_BASE_ADDR + APP1)    // 0x0800C000
#define APP2ADDR (FLASH_BASE_ADDR + APP2)   // 0x0800A000
#define UPFLAGADDR   (FLASH_BASE_ADDR + UPFLAG1)   // 0x0800F800

void WriteFlash(uint32_t address,uint8_t *pBuffer,uint32_t Numlengh);//FLASH的8位的写入函数
int EarseFlash_1K(uint32_t address);//擦除1K大小的Flash


#endif


