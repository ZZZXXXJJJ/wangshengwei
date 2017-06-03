/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    06-March-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "./usart/bsp_debug_usart.h"
#include "./report/report1.h"
#include <string.h>
#include "./SYS/systick.h"
#include "./led/bsp_led.h"

/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}
	
/*******************************************************/
	
uint8_t RNSS_RX_BUF[200];
uint8_t RNSS_RX_COUNT=0;

void RNSS_USART_IRQHandler(void)
{
	uint8_t dLat[11];
	uint8_t dLng[12];
	uint8_t dLan[29];
	uint8_t RNSS_BUF[200]={28,1,1,1};
  uint8_t ucTemp;
	uint8_t t;
	if(USART_GetITStatus(RNSS_USART,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(RNSS_USART);
    //USART_SendData(UART4,ucTemp);    
	}	
  if(ucTemp=='$')//0xEC
		{RNSS_RX_BUF[0]=ucTemp;}
	  if(RNSS_RX_BUF[0]=='$')//0xEC
		{
			
			RNSS_RX_BUF[RNSS_RX_COUNT]=ucTemp;
			//USART1->DR=RNSS_RX_BUF[RNSS_RX_COUNT];
			RNSS_RX_COUNT++;
			
			
		}
	
		if(ucTemp=='\n'&&RNSS_RX_BUF[0]=='$')
		{
			//Usart_SendStr_length( UART4, RNSS_RX_BUF,RNSS_RX_COUNT);
//			if(crc_test(RNSS_RX_BUF, 1, RNSS_RX_COUNT))
//		  {
				if(strncmp((char*)RNSS_RX_BUF,"$GNGGA",6)==0)
				{	
					
					//Usart_SendStr_length( UART4, RNSS_RX_BUF,RNSS_RX_COUNT);
				  if(RNSS_RX_BUF[47]=='1')
					{
						for(t=18;t<46;t++)
						{
							dLan[t-18]=RNSS_RX_BUF[t];
						}
						Usart_SendStr_length( UART4, dLan,28);
						strcat((char*)RNSS_BUF,(char*)dLan);
						RNSS_BUF[32]=crc_last(RNSS_BUF, 1, 32);
//						RNSS_BUF[34]=0xEB;
						BD_REPORT(33,RNSS_BUF);
						USART_Cmd(USART3,DISABLE);
				  }
				}
			//}	  
		  RNSS_RX_COUNT=0;
			}	
}	
uint8_t RDSS_RX_STA=0;
uint8_t RDSS_RX_COUNT=0;
uint8_t RDSS_RX_BUF[200];
uint8_t RDSS_RX_REPORT[200];
uint8_t WFI_FLAG=1;
void RDSS_USART_IRQHandler(void)
{
  uint8_t res,t;
	static uint16_t RDSS_Alen;
  static uint16_t RDSS_Tlen;
	if((USART6->SR&(1<<5)))
	{
		res=USART6->DR;
		//UART4->DR=res; 
		if(res=='$')//0xEC
		{RDSS_RX_BUF[0]=res;}
	  if(RDSS_RX_BUF[0]=='$')//0xEC
		{
			
			RDSS_RX_BUF[RDSS_RX_COUNT]=res;
			if(RDSS_RX_COUNT==6)
			{
				RDSS_Alen=RDSS_RX_BUF[5]*256+RDSS_RX_BUF[6];				
			}
			if(RDSS_RX_COUNT==17)
			{
				RDSS_Tlen=(RDSS_RX_BUF[16]*256+RDSS_RX_BUF[17])/8;	
			}
			RDSS_RX_COUNT++;		
		}
	
		if(RDSS_RX_BUF[0]=='$'&&RDSS_RX_COUNT==RDSS_Alen)
		{
			
			 if(crc_test(RDSS_RX_BUF, 0, RDSS_RX_COUNT))
			 {
				 if(strncmp((char*)RDSS_RX_BUF,"$FKXX",5)==0&&(RDSS_RX_BUF[10]&0x80)==0)
				{						
					Usart_SendStr_length( UART4, RDSS_RX_BUF,RDSS_RX_COUNT);
					//WFI_FLAG=1;				  
					TIM_Cmd(TIM6, ENABLE);
					
				}
				if(strncmp((char*)RDSS_RX_BUF,"$TXXX",5)==0)	
				{
					Usart_SendByte(UART4,0xEC);
					for(t=0;t<RDSS_Tlen;t++)
					{
						Usart_SendByte(UART4,RDSS_RX_BUF[18+t]);
					}
					Usart_SendByte(UART4,0xEB);
					//Usart_SendStr_length( UART4, RDSS_RX_BUF,RDSS_RX_COUNT);
				}
        
				
			 }

			RDSS_RX_BUF[0]=0;
		  RDSS_RX_COUNT=0;
			RDSS_Alen=0;
			RDSS_Tlen=0;
		}		
	}

}	
uint8_t USART4_RX_STA=0;
uint8_t USART4_RX_COUNT=0;
uint8_t USART4_RX_BUF[200];
uint8_t CENTER_BUF[200];
uint8_t TXA6=0;
void CENTER_USART_IRQHandler(void)
{
  uint8_t res,t;
  uint8_t BD_count;
	if((UART4->SR&(1<<5)))
	{
		res=UART4->DR;
		//UART4->DR=res;

		if(res==0xEC)//0xEC
		{
			USART4_RX_BUF[0]=res;
			USART4_RX_COUNT=0;
		}
		if(USART4_RX_BUF[0]==0xEC)//0xEC
		{
			USART4_RX_BUF[USART4_RX_COUNT++]=res;
			
			if(res==0xEB)
			{
				if(crc_test_control(USART4_RX_BUF,1,USART4_RX_COUNT)==1)
				{
					if(USART4_RX_BUF[2]==0xDD)
					{
						WFI_FLAG=0;                                                     //ªΩ–—
						Usart_SendStr_length(UART4,USART4_RX_BUF,USART4_RX_COUNT);      //ªΩ–—»∑»œ
					}
				}
				
	//			else
	//			{
	//				strncpy((char*)CENTER_BUF,(char*)USART4_RX_BUF,USART4_RX_COUNT);			
	//				BD_REPORT(USART4_RX_COUNT,CENTER_BUF);
	//				//strcpy((char*)USART4_RX_BUF,"");//«Â¡„
	//				USART4_RX_BUF[0]=0;  
	//				USART4_RX_COUNT=0;
	//			}
				USART4_RX_BUF[0]=0;  
				USART4_RX_COUNT=0;

			}
		}
		
	}
	
}

void  BASIC_TIMx_IRQHandler (void)
{
	uint8_t i=0;
	static uint8_t TIME_count=0;
	if ( TIM_GetITStatus( BASIC_TIMx, TIM_IT_Update) != RESET ) 
	{	
		TIME_count++;
		if(TIME_count==2)
		{ 
			WFI_FLAG=0;
			//LED1_TOGGLE;	
			TIME_count=0;
			TIM_Cmd(TIM6, DISABLE);
			for(i=0;i<3;i++)
			{
				Usart_SendByte(UART4,0x24); 
			}
		}
    TIM_ClearITPendingBit(BASIC_TIMx, TIM_IT_Update); 
     		
	}		 	
}
/**
  * @}
  */ 

/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
