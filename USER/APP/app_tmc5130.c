#include "app_tmc5130.h"

//#define IO_DRIV_MODE 1 //SD_MODE ��λ
u32 Control_Fre = 0;
void TMC_Config(void){ //IO����ģʽֻ��Ҫ����PWM�ͷ���
    
#ifdef IO_DRIV_MODE 	     
    Init_Tmc_IO_Mode_GPIO();
    TMC_CFG0 = 1;//PAGE:110 CFG0����Ϊ�ߣ�TOOF��236Tclk  
    // 00: 1ϸ��   01��4ϸ��   10��2ϸ��  11��16ϸ�� 1-float 256ϸ��
    TMC_CFG1 = 1;   
    TMC_CFG2 = 1;
/* CFG3:
    TO GND Internal reference voltage.Current scale set by sense resistors,only
    
    TO VCC_IO Internal sense resistors.Use analog input current on AIN as 
    reference current for internal sense resistor.
    
    opend External reference voltage on pin AIN.Current scale set 
    by sense resistors and scaled by AIN.
    �ӵأ�ʹ�����òο���ѹ���ⲿ��������
    ��VCC_IO��ʹ���ⲿ�ο���ѹ���ڲ���������
    ��·��ʹ�����òο���ѹ���ⲿ��������*/  
    TMC_CFG3 = 1;//ͨ��AIN���õ���  
    TMC_CFG4 = 1;//PAGE:111 CFG4����Ϊ�ߣ�chopper hysteresisն�����ͺ� ����Ϊ9
    TMC_CFG5 = 1;//PAGE:111 CFG5����Ϊ�ͣ�chopper blank timeն�����л��ڼ���ʱ������Ϊ24  
    TMC_CFG6 = 0;//PAGE:112 CFG6����Ϊ�͵������ʹ�ܣ�Ϊ�߹ر�  
    TMC_DIR_OUT = 0; //����
    TMC_STEP_OUT = 1;//����
    bsp_SetTIMOutPWM(GPIOB,GPIO_Pin_10,TIM2,3,50000,8000);//100kHz5%PWM�ӵ�AIN���õ���Ϊ5%   
#else //SPIģʽ SD_MODE =0
    Init_Tmc_SPI_Mode_GPIO(); 
    Init_SPI(); 
    TMC_SPI_Init();
#endif    
    //��ʱ��ʹ��
 /* GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;// ��翪��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������(��λ״̬);
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    */   
}
/*����DCStepģʽ*/
void Opend_DcStep_Mode(void){
    TMC_DCIN = 1; //Ϊ0ʱֹͣ ����DCO����
    TMC_DCEN = 1; //����DCStep
    TMC_DCO  = 1;//��ʼ��  
}

void CmdMotorFullMove(unsigned char *RecvCmd){// ����SPI����ģʽ
    static u8 tPosRunFlg = 0, tSpdRunFlg = 0; 
    if(g_DriveMode == 1)
    {// SPIģʽ    
        if(RecvCmd[1] == 1)
        {// λ��ģʽ
            if(tPosRunFlg == 0)
            {// ��ת
                tPosRunFlg = 1;
                TMC5160_SPIWriteInt(0x2D, 	3000); 	        // ʵ�ʵ��λ�� 0x21(XACTUAL)���λ���ƶ�		2D����λ���ƶ�	                       
                TMC5160_SPIWriteInt(0x20, 	0); 		// ���ó�λ��ģʽ 2D����λ���ƶ� 0λ�� 1�ٶ�Ϊ�� 2�ٶ�Ϊ�� 3�����ٶ�ģʽ ֱ��ֹͣ����	                       
                TMC5160_SPIWriteInt(0x27, 	2000); 	// writing value 0x0006D3A0 = 447392 = 0.0 to address 19 = 0x27(VMAX)
            }
            else
            {// ��ת
                tPosRunFlg = 0;
                TMC5160_SPIWriteInt(0x2D, 	0); 		// ʵ�ʵ��λ�� 0x21(XACTUAL)���λ���ƶ�		2D����λ���ƶ�	                       
                TMC5160_SPIWriteInt(0x20, 	0); 		// ���ó�λ��ģʽ	                       
                TMC5160_SPIWriteInt(0x27, 	2000);        // �˶��ٶ� max2^23-512
            }
        }
        else if(RecvCmd[1] == 2)
        {// �ٶ�ģʽ
            if(tSpdRunFlg == 0)
            {// ���� 
                tSpdRunFlg = 1;
                TMC5160_SPIWriteInt(0x20, 	1); 		// ���ó��ٶ�ģʽ	                       
                TMC5160_SPIWriteInt(0x27, 	3355*5); 	//  address 19 = 0x27(VMAX)
            }
            else 
            {// ֹͣ
                tSpdRunFlg = 0;
                TMC5160_SPIWriteInt(0x20, 	1); 		// ���ó��ٶ�ģʽ	                       
                TMC5160_SPIWriteInt(0x27, 	0); 	        //  address 19 = 0x27(VMAX)            
            }
        }
    }
}

