/**
  ******************************************************************************
  * @file    DCMI/OV7670_Camera/dcmi_OV7670.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   This file includes the driver for OV7670 Camera module mounted on 
  *          STM322xG-EVAL board RevA and RevB.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "dcmi_OV7670.h"
#include "DCMI_OV7670_INITTABLE.h"

/** @addtogroup DCMI_OV7670_Camera
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Bits definitions ----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Set the VGA size(640*320).
  * @param  None
  * @retval None
  */
uint8_t DCMI_OV7670_Init(void)
{
	uint8_t i;
	//SCCB_GPIO_Config();
	//SCCB_GPIO_Init();
	//DCMI_Config();
	//DCMI_GPIO_Init();
	//DCMI_DMA_Init(640*480/8);
	//DCMI_DMA_Init(320*240/2);
	//MCO1_Init();
	//DCMI_0V7670_RST_PWDN_Init();
			
	//HAL_Delay(0xfff);
	if(DCMI_SingleRandomWrite(OV7670_COM7, SCCB_REG_RESET)!=0)
		return 0xff;
	HAL_Delay(0xff);
  
	for(i=0;i<CHANGE_REG_NUM;i++)
	{
		if(DCMI_SingleRandomWrite(change_reg[i][0],change_reg[i][1])!=0)
		{
			return 0xff;
		}
	}
	//OV7670_config_window(272,16,320,240);// set 240*320
	HAL_Delay(0xff);
	return 0;//Init ok
}

/**
  * @brief  Read the OV7670 Manufacturer identifier.
  * @param  OV7670ID: pointer to the OV7670 Manufacturer identifier. 
  * @retval None
  */
uint8_t DCMI_OV7670_ReadID(OV7670_IDTypeDef* OV7670ID)
{
	uint8_t temp;
	if(DCMI_SingleRandomRead(OV7670_MIDH,&temp)!=0)
		return 0xff;
	OV7670ID->Manufacturer_ID1 = temp;
	if(DCMI_SingleRandomRead(OV7670_MIDL,&temp)!=0)
		return 0xff;
	OV7670ID->Manufacturer_ID2 = temp;
	if(DCMI_SingleRandomRead(OV7670_VER,&temp)!=0)
		return 0xff;
	OV7670ID->Version = temp;
	if(DCMI_SingleRandomRead(OV7670_PID,&temp)!=0)
		return 0xff;
	OV7670ID->PID = temp;

	return 0;
}
/**
  * @brief  config_OV7660_window 
  * @param  //(140,16,640,480) is good for VGA
  *			//(272,16,320,240) is good for QVGA
  * @retval None
  */
void OV7670_config_window(uint16_t startx, uint16_t starty, uint16_t width, uint16_t height)
{
	uint16_t endx=(startx+width);
	uint16_t endy=(starty+height*2);// must be "height*2"
	uint8_t temp_reg1, temp_reg2;
	uint8_t state,temp;
	
	UNUSED(state);	   //Prevent report warning

	state = DCMI_SingleRandomRead(0x03, &temp_reg1 );
	temp_reg1 &= 0xC0;
	state = DCMI_SingleRandomRead(0x32, &temp_reg2 );
	temp_reg2 &= 0xC0;
	
	// Horizontal
	temp = temp_reg2|((endx&0x7)<<3)|(startx&0x7);
	state = DCMI_SingleRandomWrite(0x32, temp );
	temp = (startx&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x17, temp );
	temp = (endx&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x18, temp );
	
	// Vertical
	temp = temp_reg1|((endy&0x7)<<3)|(starty&0x7);
	state = DCMI_SingleRandomWrite(0x03, temp );
	temp = (starty&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x19, temp );
	temp = (endy&0x7F8)>>3;
	state = DCMI_SingleRandomWrite(0x1A, temp );
}
 			 			  
/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
