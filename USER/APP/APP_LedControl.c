#include "APP_LedControl.h"

void Led_Control(void){
   GPIO_SetBits(GPIOA, GPIO_Pin_8);    //��PB15���óɸߵ�ƽ
    delay_ms(50);
   GPIO_ResetBits(GPIOA, GPIO_Pin_8);    //��PB15���óɵ͵�ƽ
      delay_ms(50);        //�ȴ�
}