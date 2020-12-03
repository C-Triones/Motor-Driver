#include "app_ledcontrol.h"
#include "app_tmc5130.h"
#include "bsp_tmc5130.h"
u32 targetSpeed = 50000;//3355*8
unsigned char Mode[2];
u8 g_DriveMode = 1; 
u32 ReadValue = 0;
int main(void)
{
    SystemInit();
    Systick_Init();
    Led_Config();                   //配置GPIO
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    TmcRegistersAddr_Init();
    TmcParameters_Init();
    Timer3_Init();
    TMC_Config();
    Mode[0] =1;
    Mode[1] =2;
//    bsp_SetTIMOutPWM(GPIOB,GPIO_Pin_11,TIM2,4,5000,5000);
    ReadValue=TMC5160_SPI_Read(0x35);
    TMC5160_SPIWriteInt(TmcRegistersStrcut.XTARGET, 0);
    TMC5160_SPIWriteInt(TmcRegistersStrcut.RAMPMODE,0);// 设置成位置模式	                       
    TMC5160_SPIWriteInt(TmcRegistersStrcut.VMAX,targetSpeed);
    delay_ms(100);
    ReadValue=TMC5160_SPI_Read(0x35);
    while(1)
    {  
  /*   if(Control_Fre%600==0){
         TMC_Config();
         TMC5160_SPIWriteInt(TmcRegistersStrcut.XTARGET, 0);
         TMC5160_SPIWriteInt(TmcRegistersStrcut.RAMPMODE,0);// 设置成位置模式	                       
         TMC5160_SPIWriteInt(TmcRegistersStrcut.VMAX,targetSpeed);
         delay_ms(300);
      } 
        */
    if(Control_Fre%500==0){
        ReadValue=TMC5160_SPI_Read(0x35);  
      }

    //TMC5160_SPIWriteInt(0x2D,3000);
     TMC5160_SPIWriteInt(0x20,1); 		// 设置成速度模式	                       
     TMC5160_SPIWriteInt(0x27,targetSpeed);  
    
    }       
}