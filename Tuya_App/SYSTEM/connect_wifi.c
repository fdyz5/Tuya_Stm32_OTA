#include "stm32f10x.h"
#include "wifi.h"
#include "delay.h"

/*
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
     
#define WIFI_KEY_LED_GPIO_Port  GPIOB
#define WIFI_KEY_Pin   GPIO_Pin_5
#define WIFI_LED_Pin   GPIO_Pin_6

void Connect_Wifi(void)
{
	        if (RESET == GPIO_ReadInputDataBit(WIFI_KEY_LED_GPIO_Port,WIFI_KEY_Pin))
				  {
						Delay_ms(100);
						if (RESET == GPIO_ReadInputDataBit(WIFI_KEY_LED_GPIO_Port,WIFI_KEY_Pin))
							{
									if(GPIO_ReadInputDataBit(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin)==1){
											GPIO_ResetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
									}else{
											GPIO_SetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
									}
										mcu_set_wifi_mode(SMART_CONFIG);
									  //printf("begin connect wifi\r\n");
							}
          }
        switch(mcu_get_wifi_work_state())
        {
						 case SMART_CONFIG_STATE:       
							 		GPIO_ResetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
//printf("smart config\r\n");
									 //GPIO_ToggleBits(WIFI_KEY_LED_GPIO_Port, WIFI_LED_Pin);
									 delay_ms(250);
							break;
							case AP_STATE:        
									 //printf("AP config\r\n");
									 //GPIO_ToggleBits(WIFI_KEY_LED_GPIO_Port, WIFI_LED_Pin);
									 delay_ms(500);
							break;
							case WIFI_NOT_CONNECTED: 
									 //printf("connect wifi\r\n");
									 //GPIO_SetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							break;
							case WIFI_CONNECTED:
									 //printf("connect success\r\n");
									 //GPIO_ResetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							case WIFI_CONN_CLOUD:
									 //GPIO_ResetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							break;
							default:
									 //GPIO_SetBits(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							     //printf("connect fail\r\n");
							break;
							
        }
}


 uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
 {
 if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 ) {
 while (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);
 return 1;
 } else
 return 0;
 }
