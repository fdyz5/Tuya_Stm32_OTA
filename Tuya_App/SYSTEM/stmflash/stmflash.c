
#include "stmflash.h"

unsigned char nbuff_5555[] = {0x55,0x55,0x55,0x55};
unsigned char nbuff_AAAA[] = {0xAA,0xAA,0xAA,0xAA};

/**
* @brief  写入Flash
* @waing  
* @param  address  写入的地址
* @param  pBuffer  写入的数据
* @param  Numlengh 写入的长度
* @example 
**/
void WriteFlash(uint32_t address,uint8_t *pBuffer,uint32_t Numlengh)
{
	uint32_t i ,temp;
  FLASH_Unlock();

	for(i = 0; i < Numlengh;i+= 4)
	{
		temp =  (uint32_t)pBuffer[i+3]<<24;
		temp |=  (uint32_t)pBuffer[i+2]<<16;
		temp |=  (uint32_t)pBuffer[i+1]<<8;
		temp |=  (uint32_t)pBuffer[i];
		FLASH_ProgramWord(address+i,temp);//将数据按字节写入flash
	}
  FLASH_Lock();
}
/**
* @brief  擦除1K大小的Flash
* @waing  
* @param  address  擦除的地址
* @example 
**/
int EarseFlash_1K(uint32_t address)
{
  FLASH_Unlock();
	//检验输入的地址是不是1K的倍数
	if(address % 1024 == 0)
	{
		FLASH_ErasePage(address);
	}
	else
	{
		return 0;
	}
  FLASH_Lock();
	return 1;
}

