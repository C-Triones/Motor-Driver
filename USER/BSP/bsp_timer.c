#include "bsp_timer.h"
__IO uint32_t TimingDelay;
/*SystemCoreClock / 1000000  -------   1us*/
/*SystemCoreClock / 100000   -------   10us*/
/*SystemCoreClock / 10000    -------   100us*/
/*SystemCoreClock / 1000     -------   1ms*/
static void Init_NVIC(void){
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
void Systick_Init(void){
    if (SysTick_Config(72000)){ 
        /* Capture error */ 
        while (1);
    }
}
void TimingDelay_Decrement(void){
    if (TimingDelay != 0x00){
        TimingDelay--;
    }
}
void delay_ms(__IO uint32_t nTime){//�ӳٺ���������Ϊ us
    TimingDelay = nTime;//ʱ�ӵδ���
    while(TimingDelay != 0);
}
void SysTick_Handler(void){
    TimingDelay_Decrement();
}
void Timer3_Init(void){
    Init_NVIC();
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   
    /* �ۼ� TIM_Period�������һ�����»����ж�*/		
    //����ʱ����0������4999����Ϊ5000�Σ�Ϊһ����ʱ����
    TIM_TimeBaseStructure.TIM_Period = 10000-1;          
    //��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1  
    //				PCLK1 = HCLK / 4 
    //				=> TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
    // �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=10000Hz
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;   
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
    // ����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
    // �ظ���������ֵ��û�õ����ù�
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
    // ��ʼ����ʱ��TIMx, x[2,3,4,5]
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    
    // �����ʱ�������жϱ�־λ
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);    
    // ������ʱ�������ж�
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    
    // ʹ�ܶ�ʱ��
    TIM_Cmd(TIM3, ENABLE);   
}
