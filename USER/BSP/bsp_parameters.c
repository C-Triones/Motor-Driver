#include "bsp_parameters.h"
TmcDataStruct_t TmcDataStruct;
TmcRegistersStrcut_t TmcRegistersStrcut;
/*电机寄存器地址初始化*/
void TmcRegistersAddr_Init(){
TmcRegistersStrcut.GCONF      = 0x00;
TmcRegistersStrcut.GSTAT      = 0x01;
TmcRegistersStrcut.IFCNT      = 0x02;
TmcRegistersStrcut.SLAVECONF  = 0x03;
TmcRegistersStrcut.IOIN_OUTPUT= 0x04;
TmcRegistersStrcut.X_COMPARE  = 0x05;
TmcRegistersStrcut.IHOLD_IRUN =0x10;
TmcRegistersStrcut.TPOWERDOWN = 0x11;
TmcRegistersStrcut.TSTEP      = 0x12;
TmcRegistersStrcut.TPWMTHRS   = 0x13;
TmcRegistersStrcut.TCOOLTHRS  = 0x14;
TmcRegistersStrcut.THIGH      = 0x15;
TmcRegistersStrcut.RAMPMODE   = 0x20;
TmcRegistersStrcut.XACTUAL    = 0x21;
TmcRegistersStrcut.VACTUAL    = 0x22;
TmcRegistersStrcut.VSTART     = 0x23;
TmcRegistersStrcut.A1         = 0x24;
TmcRegistersStrcut.V1         = 0x25;
TmcRegistersStrcut.AMAX       = 0x26;
TmcRegistersStrcut.VMAX       = 0x27;
TmcRegistersStrcut.DMAX       = 0x28;
TmcRegistersStrcut.D1         = 0x2A;
TmcRegistersStrcut.VSTOP      = 0x2B;
TmcRegistersStrcut.TZEROWAIT  = 0x2C;
TmcRegistersStrcut.XTARGET    = 0x2D;
TmcRegistersStrcut.VDCMIN     = 0x33;
TmcRegistersStrcut.SW_MODE    = 0x34;
TmcRegistersStrcut.RAMP_STAT  = 0x35;
TmcRegistersStrcut.XLATCH     = 0x36;
TmcRegistersStrcut.ENCMODE    = 0x38;
TmcRegistersStrcut.X_ENC      = 0x39;
TmcRegistersStrcut.ENC_CONST  = 0x3A;
TmcRegistersStrcut.ENC_STATUS = 0x3B;
TmcRegistersStrcut.ENC_LATCH  = 0x3C;
TmcRegistersStrcut.MSLUT0     = 0x60;
TmcRegistersStrcut.MSLUT1     = 0x61;
TmcRegistersStrcut.MSLUT2     = 0x62;
TmcRegistersStrcut.MSLUT3     = 0x63;
TmcRegistersStrcut.MSLUT4     = 0x64;
TmcRegistersStrcut.MSLUT5     = 0x65;
TmcRegistersStrcut.MSLUT6     = 0x66;
TmcRegistersStrcut.MSLUT7     = 0x67;
TmcRegistersStrcut.MSLUTSEL   = 0x68;
TmcRegistersStrcut.MSLUTSTART = 0x69;
TmcRegistersStrcut.MSCNT      = 0x6A;
TmcRegistersStrcut.MSCURACT   = 0x6B;
TmcRegistersStrcut.CHOPCONF   = 0x6C;
TmcRegistersStrcut.COOLCONF   = 0x6D;
TmcRegistersStrcut.DCCTRL     = 0x6E;
TmcRegistersStrcut.DRV_STATUS = 0x6F;
TmcRegistersStrcut.PWMCONF    = 0x70;
TmcRegistersStrcut.PWM_SCALE  = 0x71;
TmcRegistersStrcut.ENCM_CTRL  = 0x72;
TmcRegistersStrcut.LOST_STEP  = 0x73;
}
/*电机参数初始化*/
void TmcParameters_Init(void){
TmcDataStruct.DcSetp_VDCMIN = 5000;
TmcDataStruct.DcSetp_DCCTRL = 0x00030026;
TmcDataStruct.DcSetp_TCOOLTHRS = 115;
TmcDataStruct.DcSetp_SW_MODE =   0x00000400;

TmcDataStruct.CHOPCONF = 0x034D0153; //步进32细分
TmcDataStruct.IHOLD_IRUN = 0x70808; //运动电流8细分 静止电流8细分 电流延时7细分
TmcDataStruct.TPOWERDOWN = 0x8;     //电机停止后到电流掉电的延迟8*2^18Tclk
TmcDataStruct.GCONF = 0x4;
TmcDataStruct.TPWMTHRS = 0x1F4;
TmcDataStruct.PWMCONF = 0x401C8;
TmcDataStruct.XACTUAL = 0;
TmcDataStruct.VSTART = 8;
TmcDataStruct.A1 = 1000;
TmcDataStruct.V1 = 50000;
TmcDataStruct.AMAX = 1000;
TmcDataStruct.VMAX = 100000;
TmcDataStruct.VSTOP = 10;
TmcDataStruct.DMAX = 700;
TmcDataStruct.D1 = 1400;
TmcDataStruct.TZEROWAIT = 0;
TmcDataStruct.XTARGET = 0;
TmcDataStruct.RAMPMODE =0;
}