#ifndef _TMC_GPIO_H
#define _TMC_GPIO_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "bsp_pwm.h"
#include "bsp_timer.h"
#include "bsp_tmc5130.h"
#include "bsp_spi.h"

extern u8 g_DriveMode; 
extern u32 Control_Fre;

void TMC_Config(void);
void IO_Mode_Driver_Test(void);
void CmdMotorFullMove(unsigned char *RecvCmd);

#endif