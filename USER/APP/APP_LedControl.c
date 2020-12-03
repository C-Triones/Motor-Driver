#include "APP_LedControl.h"

void Led_Control(void){
   GPIO_SetBits(GPIOA, GPIO_Pin_8);    //将PB15设置成高电平
    delay_ms(50);
   GPIO_ResetBits(GPIOA, GPIO_Pin_8);    //将PB15设置成低电平
      delay_ms(50);        //等待
}