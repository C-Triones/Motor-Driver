#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "bsp_tmc5130.h"

// SPI总线速度设置 
typedef enum
{
    SPI_SPEED_2=0,
    SPI_SPEED_4,
    SPI_SPEED_8,
    SPI_SPEED_16,
    SPI_SPEED_256
}SPI_SPEED;

void Init_SPI(void);// 初始化SPI num代表具体初始化哪个spi
void SPIx_SetSpeed(u8 num, SPI_SPEED speed);// 初始化SPI的速度
u8 SPIx_ReadWriteByte(u8 num, u8 TxData);//读写
#endif