#ifndef _BSP_PARAMETER_H
#define _BSP_PARAMETER_H

#include "stm32f10x.h"
/*电机驱动的参数*/
typedef struct{ 
 u32 DcSetp_VDCMIN;
 u32 DcSetp_DCCTRL;
 u32 DcSetp_TCOOLTHRS;
 u16 DcSetp_SW_MODE;
 u16 DcSetp_RAMP_STAT;
}TmcDataStruct_t;
/*电机驱动的所有寄存器*/
typedef struct{
/*Velocity DependentDriver Feature Control Register*/
u16 GCONF;
u16 GSTAT;
u16 IFCNT;
u16 SLAVECONF;
u16 IOIN_OUTPUT;
u16 X_COMPARE;
u16 IHOLD_IRUN;
u16 TPOWERDOWN;
u16 TSTEP;
u16 TPWMTHRS;
u16 TCOOLTHRS;
u16 THIGH;
/*Ramp Genertor Registers*/
u16 RAMPMODE;
u16 XACTUAL;
u16 VACTUAL;
u16 VSTART;
u16 A1;
u16 V1;
u16 AMAX;
u16 VMAX;
u16 DMAX;
u16 D1;
u16 VSTOP;
u16 TZEROWAIT;
u16 XTARGET;
/*Ramp Generator Driver Feature Control Registe*/
u16 VDCMIN;
u16 SW_MODE;
u16 RAMP_STAT;
u16 XLATCH;
/*Encoder Registers*/
u16 ENCMODE;
u16 X_ENC;
u16 ENC_CONST;
u16 ENC_STATUS;
u16 ENC_LATCH;
/*Motor Driver Registers*/
u16 MSLUT0;
u16 MSLUT1;
u16 MSLUT2;
u16 MSLUT3;
u16 MSLUT4;
u16 MSLUT5;
u16 MSLUT6;
u16 MSLUT7;
u16 MSLUTSEL;
u16 MSLUTSTART;
u16 MSCNT;
u16 MSCURACT;
u16 CHOPCONF;
u16 COOLCONF;
u16 DCCTRL;
u16 DRV_STATUS;
u16 PWMCONF;
u16 PWM_SCALE;
u16 ENCM_CTRL;
u16 LOST_STEP;
}TmcRegistersStrcut_t;

void TmcRegistersAddr_Init(void);
void TmcParameters_Init(void);
extern TmcDataStruct_t TmcDataStruct;
extern TmcRegistersStrcut_t TmcRegistersStrcut;

#endif