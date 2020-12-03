#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "bsp_tmc5130.h"

// SPI�����ٶ����� 
typedef enum
{
    SPI_SPEED_2=0,
    SPI_SPEED_4,
    SPI_SPEED_8,
    SPI_SPEED_16,
    SPI_SPEED_256
}SPI_SPEED;

void Init_SPI(void);// ��ʼ��SPI num��������ʼ���ĸ�spi
void SPIx_SetSpeed(u8 num, SPI_SPEED speed);// ��ʼ��SPI���ٶ�
u8 SPIx_ReadWriteByte(u8 num, u8 TxData);//��д
#endif