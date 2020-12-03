#include "bsp_spi.h"
void Init_SPI(void){   
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
        //SPI1模块对应的SCK、MISO、MOSI为AF引脚
        GPIO_InitStructure.GPIO_Pin = TTMC_SPI_SCK_GPIO_Pin | TMC_SPI_MISO_GPIO_Pin | TMC_SPI_MOSI_GPIO_Pin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;//1.12M
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;
        SPI_Init(SPI1, &SPI_InitStructure);	  	
        SPI_Cmd(SPI1, ENABLE);					     		
}
/* SPI_SPEED_HIGH   1//
   SPI_SPEED_LOW    0*/
void SPIx_SetSpeed(u8 num, SPI_SPEED speed){
    SPI_InitTypeDef SPI_InitStructure ; 
    SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex ;
    SPI_InitStructure.SPI_Mode=SPI_Mode_Master ;
    SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b ;
    SPI_InitStructure.SPI_CPOL=SPI_CPOL_High ;
    SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge ;
    SPI_InitStructure.SPI_NSS=SPI_NSS_Soft ;
    switch(speed){
      case SPI_SPEED_2:	 // 2分频 Fsck=Fpclk/2=36Mhz
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;break;
      case SPI_SPEED_4:	 // 4分频 Fsck=Fpclk/4=18Mhz	
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;break;
      case SPI_SPEED_8:	 // 8分频 Fsck=Fpclk/8=9Mhz	
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;
        break;
      case SPI_SPEED_16:	 // 16分频 Fsck=Fpclk/16=4.5Mhz
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;
        break;
      case SPI_SPEED_256:	 // 256分频 Fsck=Fpclk/256=281.25Khz 低速模式
        SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;
        break;
    }
    SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB ;
    SPI_InitStructure.SPI_CRCPolynomial=7 ;
    if(1 == num) SPI_Init(SPI1,&SPI_InitStructure);
    else if(2 == num)  SPI_Init(SPI2,&SPI_InitStructure);
}
u8 SPIx_ReadWriteByte(u8 num, u8 TxData){  
    if(num == 1){
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);	
        SPI_I2S_SendData(SPI1, TxData);	
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        return SPI_I2S_ReceiveData(SPI1);
    }
    else if(num == 2){
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	
        SPI_I2S_SendData(SPI2, TxData);
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
        return SPI_I2S_ReceiveData(SPI2);	
    }
    else{
        return 0;
    }
}
