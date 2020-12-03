#include "bsp_timer.h"
__IO uint32_t TimingDelay;
/*SystemCoreClock / 1000000  -------   1us*/
/*SystemCoreClock / 100000   -------   10us*/
/*SystemCoreClock / 10000    -------   100us*/
/*SystemCoreClock / 1000     -------   1ms*/
static void Init_NVIC(void){
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn; 	
		// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置子优先级
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
void delay_ms(__IO uint32_t nTime){//延迟函数，设置为 us
    TimingDelay = nTime;//时钟滴答数
    while(TimingDelay != 0);
}
void SysTick_Handler(void){
    TimingDelay_Decrement();
}
void Timer3_Init(void){
    Init_NVIC();
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   
    /* 累计 TIM_Period个后产生一个更新或者中断*/		
    //当定时器从0计数到4999，即为5000次，为一个定时周期
    TIM_TimeBaseStructure.TIM_Period = 10000-1;          
    //定时器时钟源TIMxCLK = 2 * PCLK1  
    //				PCLK1 = HCLK / 4 
    //				=> TIMxCLK=HCLK/2=SystemCoreClock/2=90MHz
    // 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=10000Hz
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;   
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
    // 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
    // 重复计数器的值，没用到不用管
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
    // 初始化定时器TIMx, x[2,3,4,5]
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    
    // 清除定时器更新中断标志位
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);    
    // 开启定时器更新中断
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    
    // 使能定时器
    TIM_Cmd(TIM3, ENABLE);   
}
