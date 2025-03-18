/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "SCCB.h"
#include "I2C.h"

/*******************************************************************************
* Function Name  : SCCB_GPIO_Config
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/


/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @param  Data: data to be written to the specific register 
  * @retval 0x00 if write operation is OK. 
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t DCMI_SingleRandomWrite(uint8_t Reg, uint8_t Data)
{
#if 1
    //ret = HAL_I2C_Mem_Write(sp_hi2c, SLAVE_ADDR, Reg, I2C_MEMADD_SIZE_8BIT, &Data, 1, 100);
	if (HAL_I2C_Mem_Write(&hi2c_dcmi, OV7670_DEVICE_WRITE_ADDRESS, Reg, I2C_MEMADD_SIZE_8BIT, &Data, 1, 100)!=HAL_OK)
		return 0xFF;
#else
	uint8_t buff[2];
	buff[0] = Reg;
	buff[1] = Data;
    //ret = HAL_I2C_Master_Transmit(&hdcmi, SLAVE_ADDR, buff, 2, 100);
	if (HAL_I2C_Master_Transmit(&hi2c_dcmi, OV7670_DEVICE_WRITE_ADDRESS, buff, 2, 100) != HAL_OK) return 0xFF;
#endif
	return 0;
}

/**
  * @brief  Reads a byte from a specific Camera register 
  * @param  Device: OV7670 write address.
  * @param  Addr: OV7670 register address. 
  * @retval data read from the specific register or 0xFF if timeout condition 
  *         occured. 
  */
uint8_t DCMI_SingleRandomRead(uint8_t Reg, uint8_t *pData)
{
	if (HAL_I2C_Master_Transmit(&hi2c_dcmi, OV7670_DEVICE_READ_ADDRESS, &Reg, 1, 100) != HAL_OK) return 0xFF;
	if (HAL_I2C_Master_Receive(&hi2c_dcmi, OV7670_DEVICE_READ_ADDRESS, pData, 1, 100) != HAL_OK) return 0xFF;
	return 0;
}


