/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SCCB_H
#define __SCCB_H

/* Includes ------------------------------------------------------------------*/
					  
/* Private define ------------------------------------------------------------*/
  
#define OV7670_DEVICE_WRITE_ADDRESS    0x42
#define OV7670_DEVICE_READ_ADDRESS     0x43


/* Private function prototypes -----------------------------------------------*/
uint8_t DCMI_SingleRandomWrite(uint8_t Addr, uint8_t Data);
uint8_t DCMI_SingleRandomRead(uint8_t Addr, uint8_t *Data);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
