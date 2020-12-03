#include "app_tmc5130.h"

//#define IO_DRIV_MODE 1 //SD_MODE 置位
u32 Control_Fre = 0;
void TMC_Config(void){ //IO控制模式只需要控制PWM和方向
    
#ifdef IO_DRIV_MODE 	     
    Init_Tmc_IO_Mode_GPIO();
    TMC_CFG0 = 1;//PAGE:110 CFG0设置为高，TOOF：236Tclk  
    // 00: 1细分   01：4细分   10：2细分  11：16细分 1-float 256细分
    TMC_CFG1 = 1;   
    TMC_CFG2 = 1;
/* CFG3:
    TO GND Internal reference voltage.Current scale set by sense resistors,only
    
    TO VCC_IO Internal sense resistors.Use analog input current on AIN as 
    reference current for internal sense resistor.
    
    opend External reference voltage on pin AIN.Current scale set 
    by sense resistors and scaled by AIN.
    接地：使用内置参考电压，外部采样电阻
    接VCC_IO：使用外部参考电压，内部采样电阻
    开路：使用内置参考电压，外部采样电阻*/  
    TMC_CFG3 = 1;//通过AIN设置电流  
    TMC_CFG4 = 1;//PAGE:111 CFG4设置为高，chopper hysteresis斩波器滞后 设置为9
    TMC_CFG5 = 1;//PAGE:111 CFG5设置为低，chopper blank time斩波器切换期间间隔时间设置为24  
    TMC_CFG6 = 0;//PAGE:112 CFG6设置为低电机驱动使能，为高关闭  
    TMC_DIR_OUT = 0; //方向
    TMC_STEP_OUT = 1;//脉冲
    bsp_SetTIMOutPWM(GPIOB,GPIO_Pin_10,TIM2,3,50000,8000);//100kHz5%PWM接到AIN设置电流为5%   
#else //SPI模式 SD_MODE =0
    Init_Tmc_SPI_Mode_GPIO(); 
    Init_SPI(); 
    TMC_SPI_Init();
#endif    
    //暂时不使用
 /* GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;// 光电开关
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入(复位状态);
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    */   
}
/*启用DCStep模式*/
void Opend_DcStep_Mode(void){
    TMC_DCIN = 1; //为0时停止 并将DCO置零
    TMC_DCEN = 1; //启用DCStep
    TMC_DCO  = 1;//初始化  
}

void CmdMotorFullMove(unsigned char *RecvCmd){// 内置SPI控制模式
    static u8 tPosRunFlg = 0, tSpdRunFlg = 0; 
    if(g_DriveMode == 1)
    {// SPI模式    
        if(RecvCmd[1] == 1)
        {// 位置模式
            if(tPosRunFlg == 0)
            {// 正转
                tPosRunFlg = 1;
                TMC5160_SPIWriteInt(0x2D, 	3000); 	        // 实际电机位置 0x21(XACTUAL)相对位置移动		2D绝对位置移动	                       
                TMC5160_SPIWriteInt(0x20, 	0); 		// 设置成位置模式 2D绝对位置移动 0位置 1速度为正 2速度为负 3保持速度模式 直到停止命令	                       
                TMC5160_SPIWriteInt(0x27, 	2000); 	// writing value 0x0006D3A0 = 447392 = 0.0 to address 19 = 0x27(VMAX)
            }
            else
            {// 反转
                tPosRunFlg = 0;
                TMC5160_SPIWriteInt(0x2D, 	0); 		// 实际电机位置 0x21(XACTUAL)相对位置移动		2D绝对位置移动	                       
                TMC5160_SPIWriteInt(0x20, 	0); 		// 设置成位置模式	                       
                TMC5160_SPIWriteInt(0x27, 	2000);        // 运动速度 max2^23-512
            }
        }
        else if(RecvCmd[1] == 2)
        {// 速度模式
            if(tSpdRunFlg == 0)
            {// 启动 
                tSpdRunFlg = 1;
                TMC5160_SPIWriteInt(0x20, 	1); 		// 设置成速度模式	                       
                TMC5160_SPIWriteInt(0x27, 	3355*5); 	//  address 19 = 0x27(VMAX)
            }
            else 
            {// 停止
                tSpdRunFlg = 0;
                TMC5160_SPIWriteInt(0x20, 	1); 		// 设置成速度模式	                       
                TMC5160_SPIWriteInt(0x27, 	0); 	        //  address 19 = 0x27(VMAX)            
            }
        }
    }
}

