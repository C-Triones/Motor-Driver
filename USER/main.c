#include "app_ledcontrol.h"
#include "app_tmc5130.h"
#include "bsp_tmc5130.h"
#include "bsp_key.h"
u32 targetSpeed = 80000;//3355*8
u8 g_DriveMode = 1; 
u32 ReadValue = 0;
u32 Read_TSTEP_Value = 0;
int main(void)
{
    SystemInit();
    Systick_Init();
    KEY_Init();
    Led_Config();                   //配置GPIO
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    TmcRegistersAddr_Init();
    TmcParameters_Init();
    Timer3_Init();
    TMC_Config();
    TMC5160_SPIWriteInt(TmcRegistersStrcut.XTARGET, 0);
    TMC5160_SPIWriteInt(TmcRegistersStrcut.RAMPMODE,PosMode);// 设置成位置模式	                       
    TMC5160_SPIWriteInt(TmcRegistersStrcut.VMAX,targetSpeed);
    delay_ms(300);
    while(1)
    {        
        if(Control_Fre%2==Flase){
            Read_TSTEP_Value=TMC5160_SPI_Read(TmcRegistersStrcut.TSTEP);
            if(KEY_Scan(0)==KEY1_PRES){
                ReadValue=TMC5160_SPI_Read(TmcRegistersStrcut.RAMP_STAT);
                delay_ms(50);
            }   
        }
        if(KEY_Scan(0)==KEY0_PRES){
            delay_ms(300);
            TMC_Config();
            TMC5160_SPIWriteInt(TmcRegistersStrcut.XTARGET, 0);
            TMC5160_SPIWriteInt(TmcRegistersStrcut.RAMPMODE,PosMode);//设置成位置模式	                       
            TMC5160_SPIWriteInt(TmcRegistersStrcut.VMAX,targetSpeed); 
            delay_ms(300);
        } 
        //TMC5160_SPIWriteInt(0x2D,3000);
        TMC5160_SPIWriteInt(TmcRegistersStrcut.RAMPMODE,VelMode);// 设置成速度模式	                       
        TMC5160_SPIWriteInt(TmcRegistersStrcut.VMAX,targetSpeed);  
        
    }       
}