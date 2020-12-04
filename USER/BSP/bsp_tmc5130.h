#ifndef _BSP_TMC5130_H_
#define _BSP_TMC5130_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "bsp_spi.h"
#include "bsp_parameters.h"


#define True  1
#define Flase 0

//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����
// TMC5130Ӳ���ӿ�����
#define  TMC_STEP_OUT    PAout(2)/*��������STEP*/
#define  TMC_DIR_OUT	 PAout(1)/*��������DIR*/ 
#define  TMC_CFG0        PAout(6)/*����ն�����ر�ʱ��*/
#define  TMC_CFG1        PAout(7)/*CFG1-CFG2���ò���ϸ��*/
#define  TMC_CFG2        PAout(5)
#define  TMC_CFG3        PAout(4)/*���õ�������ģʽ*/
#define  TMC_CFG4        PBout(0)/*����ն�����ӳ�ʱ��*/
#define  TMC_CFG5        PBout(1)/*����ն��������ʱ��*/
#define  TMC_CFG6        PAout(3)/*����ʹ��0 ʧ��1*/

#define	 M1_SENSE        PAin(11)//��翪�� ��סΪ0 

/*PAout(3)*/
#define  RCC_TMC_pTMC_DRV_ENN_GPIO  RCC_APB2Periph_GPIOA
#define  pTMC_DRV_ENN_GPIO_Port     GPIOA
#define  pTMC_DRV_ENN_GPIO_Pin      GPIO_Pin_3
/*PAout(2)*/
#define  RCC_TMC_M1_STEP_OUT_GPIO   RCC_APB2Periph_GPIOA
#define  TMC_M1_STEP_OUT_GPIO_Port  GPIOA
#define  TMC_M1_STEP_OUT_GPIO_Pin   GPIO_Pin_2
/*PAout(1)*/
#define  RCC_TMC_M1_DIR_OUT_GPIO    RCC_APB2Periph_GPIOA
#define  TMC_M1_DIR_OUT_GPIO_Port   GPIOA
#define  TMC_M1_DIR_OUT_GPIO_Pin    GPIO_Pin_1
/*PAout(6)*/
#define  RCC_TMC_CFG0_GPIO          RCC_APB2Periph_GPIOA
#define  TMC_CFG0_GPIO_Port         GPIOA
#define  TMC_CFG0_GPIO_Pin          GPIO_Pin_6
/*PAout(7)*/
#define  RCC_TMC_CFG1_GPIO          RCC_APB2Periph_GPIOA
#define  TMC_CFG1_GPIO_Port         GPIOA
#define  TMC_CFG1_GPIO_Pin          GPIO_Pin_7
/*PAout(5)*/
#define  RCC_TMC_CFG2_GPIO          RCC_APB2Periph_GPIOA
#define  TMC_CFG2_GPIO_Port         GPIOA
#define  TMC_CFG2_GPIO_Pin          GPIO_Pin_5
/*PAout(4)*/
#define  RCC_TMC_CFG3_GPIO          RCC_APB2Periph_GPIOA
#define  TMC_CFG3_GPIO_Port         GPIOA
#define  TMC_CFG3_GPIO_Pin          GPIO_Pin_4
/*PBout(0)*/
#define  RCC_TMC_CFG4_GPIO          RCC_APB2Periph_GPIOB
#define  TMC_CFG4_GPIO_Port         GPIOB
#define  TMC_CFG4_GPIO_Pin          GPIO_Pin_0
/*PBout(1)*/
#define  RCC_TMC_CFG5_GPIO          RCC_APB2Periph_GPIOB
#define  TMC_CFG5_GPIO_Port         GPIOB
#define  TMC_CFG5_GPIO_Pin          GPIO_Pin_1
/*PAout(3)*/
#define  RCC_TMC_CFG6_GPIO          RCC_APB2Periph_GPIOA
#define  TMC_CFG6_GPIO_Port         GPIOA
#define  TMC_CFG6_GPIO_Pin          GPIO_Pin_3
/*PAin(11)*/
#define  RCC_TMC_M1_SENSE_GPIO      RCC_APB2Periph_GPIOA
#define  TMC_M1_SENSE_GPIO_Port     GPIOA
#define  TMC_M1_SENSE_GPIO_Pin      GPIO_Pin_11

//SPI1ģʽ
#define  TMC_SPI_CLK     PAout(5)
#define  TMC_SPI_MISO    PAin(6)
#define  TMC_SPI_MOSI    PAout(7)
#define  M2_ENABLE       PBout(1)
#define  TMC_SPI_CS      PAout(4)
/*PAout(5)*/
#define  RCC_TMC_SPI_SCK_GPIO     RCC_APB2Periph_GPIOA
#define  TMC_SPI_SCK_GPIO_Port    GPIOA
#define  TTMC_SPI_SCK_GPIO_Pin    GPIO_Pin_5
/*PAout(6)*/
#define  RCC_TMC_SPI_MISO_GPIO    RCC_APB2Periph_GPIOA
#define  TMC_SPI_MISO_GPIO_Port   GPIOA
#define  TMC_SPI_MISO_GPIO_Pin    GPIO_Pin_6
/*PAout(7)*/
#define  RCC_TMC_SPI_MOSI_GPIO    RCC_APB2Periph_GPIOA
#define  TMC_SPI_MOSI_GPIO_Port   GPIOA
#define  TMC_SPI_MOSI_GPIO_Pin    GPIO_Pin_7
/*PAout(4)*/
#define  RCC_TMC_SPI_CS_GPIO      RCC_APB2Periph_GPIOA
#define  TMC_SPI_CS_GPIO_Port     GPIOA
#define  TMC_SPI_CS_GPIO_Pin      GPIO_Pin_4

/*DcStep_Mode*/
#define  TMC_DCIN        PCout(15)
#define  TMC_DCEN        PCout(14)
#define  TMC_DCO         PCin(12)

#define  RCC_TMC_DCIN_GPIO  RCC_APB2Periph_GPIOC
#define  TMC_DCIN_GPIO_Port GPIOC
#define  TMC_DCIN_GPIO_Pin GPIO_Pin_15

#define  RCC_TMC_DCEN_GPIO  RCC_APB2Periph_GPIOC
#define  TMC_DCEN_GPIO_Port GPIOC
#define  TMC_DCEN_GPIO_Pin  GPIO_Pin_14

#define  RCC_TMC_DCO_GPIO  RCC_APB2Periph_GPIOC
#define  TMC_DCO_GPIO_Port GPIOC
#define  TMC_DCO_GPIO_Pin  GPIO_Pin_12

typedef enum
{
    C_PIC_Home = 0,
    C_PIC_StealthChop,      // ն��ģʽ������ƽ�������е�������еĹ���˥��
    C_PIC_CoolStep,         // ��������
    C_PIC_StallGuard,       // �߾��ȴ������޸��ؼ��
    C_PIC_SpreadCycle,      // �߶�̬�������ն����
    C_PIC_DcStep            // ������ظ��ؿ���
}TMC5160Fun;

/*����˶�ģʽ*/
typedef enum{
    PosMode =0,
    VelMode =1
}MoveMode;

void Init_Tmc_IO_Mode_GPIO(void);
void Init_Tmc_SPI_Mode_GPIO(void);
u32 TMC5160_SPI_Read(u8 byte);
void TMC5160_SPIWriteInt(u8 reg, u32 byte);
void TMC_SPI_Init(void);
void stallDetectionConfig(void);

 
#endif