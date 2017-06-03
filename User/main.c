#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./report/report1.h"
#include <string.h>
#include "./SYS/systick.h"
#include "./led/bsp_led.h"



extern uint8_t WFI_FLAG;
int main(void)
{	
	RNSS_USART_Config();
	RDSS_USART_Config();
	CENTER_USART_Config();
	BASIC_TIMx_Config();
	LED_GPIO_Config();
	TIM_Cmd(TIM6, DISABLE);
	USART_Cmd(USART3,DISABLE);
  uint8_t WAKE=0;
  while(1)
	{	
   
		if(WFI_FLAG==0)
		{
			USART_Cmd(USART6,ENABLE);
			USART_Cmd(USART3,ENABLE);
			if(WAKE==0)
			{
			  Usart_SendString(UART4,"����\r\n");
				WAKE=1;
			}
			LED1(1);	       //�򿪼̵���
		} 
		if(WFI_FLAG==1)
		{ 
			LED1(0);				 //�رռ̵���
			WAKE=0;
			//Usart_SendString(UART4,"����˯��ģʽ\r\n");
			USART_Cmd(USART3,DISABLE);
	    USART_Cmd(USART6,DISABLE);			
			__WFI();	//WFIָ�����˯��		
		}
		if(WFI_FLAG==2)
		{ 
//			LED1(0);
			if(WAKE==1)
			{
				Usart_SendString( UART4,"�������ģʽ\r\n");
				WAKE=0;
			}
			USART_Cmd(USART3,DISABLE);
	    USART_Cmd(USART6,ENABLE);				
		}
	}	
}



/*********************************************END OF FILE**********************/

