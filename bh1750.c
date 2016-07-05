#include "BH1750.h"
#include "i2c.h"
#include "delay.h"
#include "string.h"


/*************************************************************
  Function   :Init_BH1750
  Description:初始化BH1750 
  Input      : none        
  return     : none    
*************************************************************/
void Init_BH1750(void)
{
	I2Cx_Init();
  Cmd_Write_BH1750(BH1750_ON);	   //power on
	Cmd_Write_BH1750(BH1750_RSET);	 //clear
}
/*************************************************************
  Function   :Cmd_Write_BH1750
  Description:写BH1750 命令
  Input      : cmd ---命令     
  return     : none    
*************************************************************/
void Cmd_Write_BH1750(uint8_t cmd)
{
	  I2C_Start();                  //起始信号
    I2C_WriteByte(BH1750_Addr+0); //发送设备地址+写信号
	
	  I2C_WaiteForAck();
    I2C_WriteByte(cmd);           //内部寄存器地址
		I2C_WaiteForAck();
	  I2C_Stop();                   //发送停止信号
		delay_ms(5);
}
/*************************************************************
  Function   : Start_BH1750
  Description: 启动BH1750
  Input      : none     
  return     : none    
*************************************************************/
void Start_BH1750(void)
{
	Cmd_Write_BH1750(BH1750_CON);  //一次H分辨率模式，至少120ms
	delay_ms(180);
}
/*************************************************************
  Function   : Read_BH1750
  Description: BH1750读光照值
  Input      :  none
  return     : ---读回的数据  uint16_t    
*************************************************************/
uint16_t Read_BH1750(void)
{   	
		uint16_t data;
		uint8_t temp[2];
	
    I2C_Start();                         //起始信号
    I2C_WriteByte(BH1750_Addr+1);        //发送设备地址+读信号
	  I2C_WaiteForAck();
	  temp[0]=I2C_ReadByte(I2C_ACK);       //ACK read data msb first
	  temp[1]=I2C_ReadByte(I2C_NACK);      //NACK
	  I2C_Stop();                          //停止信号
		data = temp[0];
		data = (data<<8)+temp[1];			//合成数据，即光照数据
    delay_ms(5);
	
		return data;	
}
/*************************************************************
  Function   : Convert_BH1750
	Description: 转化读取的光照值，unit:lx 精度0.1 lx
  Input      : light_value ---  bh1750的register光照度值
	return     : 转化后的光照度 unit :lx
*************************************************************/
float Convert_BH1750(uint16_t light_value)
{
	
	float result_lx=0;
 	
	result_lx=(float)light_value/1.2;

	return result_lx;
}


