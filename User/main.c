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
			  Usart_SendString(UART4,"唤醒\r\n");
				WAKE=1;
			}
			LED1(1);	       //打开继电器
		} 
		if(WFI_FLAG==1)
		{ 
			LED1(0);				 //关闭继电器
			WAKE=0;
			//Usart_SendString(UART4,"进入睡眠模式\r\n");
			USART_Cmd(USART3,DISABLE);
	    USART_Cmd(USART6,DISABLE);			
			__WFI();	//WFI指令进入睡眠		
		}
		if(WFI_FLAG==2)
		{ 
//			LED1(0);
			if(WAKE==1)
			{
				Usart_SendString( UART4,"进入待机模式\r\n");
				WAKE=0;
			}
			USART_Cmd(USART3,DISABLE);
	    USART_Cmd(USART6,ENABLE);				
		}
	}	
}



/*********************************************END OF FILE**********************/

