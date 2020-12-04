#include "bsp_tmc5130.h"
u8 g_FreePower = 30, g_RunPower = 60;

const u32 T_Speed_StealthChop[] = {	//60 RPM
    11582,71582*2+30000,71582*2+60000,71582*3+30000,71582*4
};
const u32 T_Speed_CoolStep[] = {	//60 RPM
    71582,71582*2,71582*3,71582*4,71582*5
};
const u32 T_Speed_StallGuard[] = {	//60 RPM
    71582,71582*2,71582*3,71582*4,71582*5
};
const u32 T_Speed_SpreadCycle[] = {	//60 RPM
    300000,500000,700000,900000,1200000
};
const u32 T_Speed_DcStep[] = {	//60 RPM
    71582,71582*2,71582*3,71582*4,71582*5
};
void Init_Tmc_IO_Mode_GPIO(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB \
        | RCC_APB2Periph_AFIO, ENABLE);
    //TMC其它控制接口,没有用到的，暂时不设置，默认FLoating
    GPIO_InitStructure.GPIO_Pin   = pTMC_DRV_ENN_GPIO_Pin \
      | TMC_M1_STEP_OUT_GPIO_Pin  |TMC_M1_DIR_OUT_GPIO_Pin \
      | TMC_CFG0_GPIO_Pin | TMC_CFG1_GPIO_Pin | TMC_CFG2_GPIO_Pin | TMC_CFG3_GPIO_Pin;   
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(GPIOA, &GPIO_InitStructure);	  
   
    GPIO_InitStructure.GPIO_Pin   = TMC_CFG5_GPIO_Pin | TMC_CFG4_GPIO_Pin;				 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(GPIOB, &GPIO_InitStructure);   
                     /*DcStep*/ 
    GPIO_InitStructure.GPIO_Pin   = TMC_DCIN_GPIO_Pin | TMC_DCEN_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TMC_DCEN_GPIO_Port,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin   = TMC_DCO_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(TMC_DCO_GPIO_Port, &GPIO_InitStructure);   
}
void Init_Tmc_SPI_Mode_GPIO(void){  
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_TMC_SPI_CS_GPIO,ENABLE);
    GPIO_InitStructure.GPIO_Pin   = TMC_SPI_CS_GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(TMC_SPI_CS_GPIO_Port, &GPIO_InitStructure);
    TMC_SPI_CS = 1; //拉高SPI片选
}
u32 TMC5160_SPI_Read(u8 byte){	  
    u32 DATA;
    u8 DATA1,DATA2,DATA3,DATA4;     
    int i;       
    
    TMC_SPI_CS = 0;
    SPIx_ReadWriteByte(1, byte);	 
    SPIx_ReadWriteByte(1, 0x00);	
    SPIx_ReadWriteByte(1, 0x00);	 
    SPIx_ReadWriteByte(1, 0x00);	 
    SPIx_ReadWriteByte(1, 0x00);     
    TMC_SPI_CS = 1;
    
    for(i=0;i<5;i++) {}
    
    TMC_SPI_CS = 0;
    SPIx_ReadWriteByte(1, byte);	 
    DATA4=SPIx_ReadWriteByte(1, 0x00);	
    DATA3=SPIx_ReadWriteByte(1, 0x00);	 
    DATA2=SPIx_ReadWriteByte(1, 0x00);	 
    DATA1=SPIx_ReadWriteByte(1, 0x00);	 	 
    TMC_SPI_CS = 1;		
    DATA = (DATA4 << 24) + (DATA3 << 16) + (DATA2 << 8) + DATA1;
    
    return DATA; 
}
u8 TMC5160_SPI_ReadState(u8 byte){	  
    u8 RetState = 0;
    int i;       
    
    TMC_SPI_CS = 0;
    SPIx_ReadWriteByte(1, byte);	 
    SPIx_ReadWriteByte(1, 0x00);	
    SPIx_ReadWriteByte(1, 0x00);	 
    SPIx_ReadWriteByte(1, 0x00);	 
    SPIx_ReadWriteByte(1, 0x00);     
    TMC_SPI_CS = 1;
    
    for(i=0;i<5;i++) {}
    
    TMC_SPI_CS = 0;
    RetState = SPIx_ReadWriteByte(1, byte);	 
    SPIx_ReadWriteByte(1, 0x00);	
    SPIx_ReadWriteByte(1, 0x00);	 
    SPIx_ReadWriteByte(1, 0x00);	 
    SPIx_ReadWriteByte(1, 0x00);	 
    TMC_SPI_CS = 1;		
    
    return RetState; 
}

void TMC5160_SPIWriteInt(u8 reg, u32 byte){		  
    int i,l;    
    u8 	DATA21,DATA22,DATA23,DATA24;
    
    TMC_SPI_CS = 0;
    
    DATA21= byte;
    DATA22= byte>>8;
    DATA23= byte>>16;
    DATA24= byte>>24;
    
    SPIx_ReadWriteByte(1, reg | 0x80);	 
    SPIx_ReadWriteByte(1, DATA24);
    SPIx_ReadWriteByte(1, DATA23);	 
    SPIx_ReadWriteByte(1, DATA22);	 
    SPIx_ReadWriteByte(1, DATA21);
    TMC_SPI_CS = 1;
    
    for(i=0;i<10;i++) { for(l=0;l<10;l++){;};}
}
/*
void FullSetMotorSpeed(u8 Index, u8 Num){// 智能模式速度设置			
    switch(Index)
    {
      case C_PIC_StealthChop:	    // 1
        TMC5160_SPIWriteInt(0x27, T_Speed_StealthChop[Num]); 		// writing value 0x00000000 = 0 = 0.0 to address 19 = 0x27(VMAX)			
        break;
        
      case C_PIC_CoolStep:        // 2
        TMC5160_SPIWriteInt(0x27, T_Speed_CoolStep[Num]); 		// writing value 0x00000000 = 0 = 0.0 to address 19 = 0x27(VMAX)	
        break;	
        
      case C_PIC_StallGuard:      // 3
        TMC5160_SPIWriteInt(0x27, T_Speed_StallGuard[Num]); 		// writing value 0x00000000 = 0 = 0.0 to address 19 = 0x27(VMAX)	
        break;	
        
      case C_PIC_SpreadCycle:     // 4
        TMC5160_SPIWriteInt(0x27, T_Speed_SpreadCycle[Num]); 		// writing value 0x00000000 = 0 = 0.0 to address 19 = 0x27(VMAX)	
        break;
        
      case C_PIC_DcStep:          // 5
        TMC5160_SPIWriteInt(0x27, T_Speed_DcStep[Num]); 		// writing value 0x00000000 = 0 = 0.0 to address 19 = 0x27(VMAX)	
        break;
      default:;
    }
}
*/
//TMC5130/TMC5160   SPI 通信接口    
void TMC_SPI_Init(void){
    TMC5160_SPIWriteInt(TmcRegistersStrcut.CHOPCONF,TmcDataStruct.CHOPCONF);//0x044D0153 CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadcycle) 16 vhighfs&vhighchm (0x6c bit18:19 ) 设置成 1
    //SYNCPWM synchronization clock 0100  TBLblank time select 36 clk    
    TMC5160_SPIWriteInt(TmcRegistersStrcut.IHOLD_IRUN,TmcDataStruct.IHOLD_IRUN);//70A03 PAGE33:IHOLD_IRUN: IHOLD=10, IRUN=22(31 max.current), IHOLDDELAY=6 
    TMC5160_SPIWriteInt(TmcRegistersStrcut.TPOWERDOWN,TmcDataStruct.TPOWERDOWN);//PAGE33:TPOWERDOWN=10:电机静止到电流减小之间的延时
    TMC5160_SPIWriteInt(TmcRegistersStrcut.GCONF,          TmcDataStruct.GCONF);//PAGE27:EN_PWM_MODE=1，使能
    TMC5160_SPIWriteInt(TmcRegistersStrcut.TPWMTHRS,    TmcDataStruct.TPWMTHRS);//PAGE33:TPWM_THRS=500,对应切换速度35000=ca.30RPM
    TMC5160_SPIWriteInt(TmcRegistersStrcut.PWMCONF,      TmcDataStruct.PWMCONF);//PAGE43:PWMCONF	   
    TMC5160_SPIWriteInt(TmcRegistersStrcut.XACTUAL,      TmcDataStruct.XACTUAL);// writing value 0xFFCC12F0 = 0 = 0.0 to address 14 = 0x21(XACTUAL)
    TMC5160_SPIWriteInt(TmcRegistersStrcut.VSTART,        TmcDataStruct.VSTART);//VSTAT = 8   /*VSTAT<VSTOP*/
    TMC5160_SPIWriteInt(TmcRegistersStrcut.A1,                TmcDataStruct.A1);//A1=1000第一阶段加速度
    TMC5160_SPIWriteInt(TmcRegistersStrcut.V1,                TmcDataStruct.V1);//V1=50000加速度阀值速度V  
    TMC5160_SPIWriteInt(TmcRegistersStrcut.AMAX,            TmcDataStruct.AMAX);//AMAX=5000大于V1的加速度   
    TMC5160_SPIWriteInt(TmcRegistersStrcut.VMAX,            TmcDataStruct.VMAX);//VMAX=100000  120000就会丢步
    TMC5160_SPIWriteInt(TmcRegistersStrcut.VSTOP,          TmcDataStruct.VSTOP);//VSTOP=10停止速度，接近于0
    TMC5160_SPIWriteInt(TmcRegistersStrcut.DMAX,            TmcDataStruct.DMAX);//DMAX=700大于V1的减速度 
    TMC5160_SPIWriteInt(TmcRegistersStrcut.D1,                TmcDataStruct.D1);//D1=1400小于V1的减速度 		
    TMC5160_SPIWriteInt(TmcRegistersStrcut.TZEROWAIT,  TmcDataStruct.TZEROWAIT);// VSTAT->VSTOP的时间 =0
    TMC5160_SPIWriteInt(TmcRegistersStrcut.XTARGET,      TmcDataStruct.XTARGET);//XTARGET =0；  
    TMC5160_SPIWriteInt(TmcRegistersStrcut.RAMPMODE,    TmcDataStruct.RAMPMODE);//RAMPMODE=0位置模式，使用所有A、V、D参数
    stallDetectionConfig();
}
static void stallDetectionConfig(void){ 
    TMC5160_SPIWriteInt(TmcRegistersStrcut.VDCMIN,      TmcDataStruct.DcSetp_VDCMIN);//设置VDCMIN达到所需速度的5%-20% 地址0x33
    TMC5160_SPIWriteInt(TmcRegistersStrcut.DCCTRL,      TmcDataStruct.DcSetp_DCCTRL);//设置DC_TIME 地址0x6e bit9:0 DC_TIME=37 DC_SG = 4
    TMC5160_SPIWriteInt(TmcRegistersStrcut.TCOOLTHRS,TmcDataStruct.DcSetp_TCOOLTHRS);//TCOOLTHRS 设置成略高于VDCMIN (地址0x14)
    TMC5160_SPIWriteInt(TmcRegistersStrcut.SW_MODE,    TmcDataStruct.DcSetp_SW_MODE);//使能sg_stop（地址0x34 bit10）
}
