#include "BH1750.h"
#include "i2c.h"
#include "delay.h"
#include "string.h"


/*************************************************************
  Function   :Init_BH1750
  Description:��ʼ��BH1750 
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
  Description:дBH1750 ����
  Input      : cmd ---����     
  return     : none    
*************************************************************/
void Cmd_Write_BH1750(uint8_t cmd)
{
	  I2C_Start();                  //��ʼ�ź�
    I2C_WriteByte(BH1750_Addr+0); //�����豸��ַ+д�ź�
	
	  I2C_WaiteForAck();
    I2C_WriteByte(cmd);           //�ڲ��Ĵ�����ַ
		I2C_WaiteForAck();
	  I2C_Stop();                   //����ֹͣ�ź�
		delay_ms(5);
}
/*************************************************************
  Function   : Start_BH1750
  Description: ����BH1750
  Input      : none     
  return     : none    
*************************************************************/
void Start_BH1750(void)
{
	Cmd_Write_BH1750(BH1750_CON);  //һ��H�ֱ���ģʽ������120ms
	delay_ms(180);
}
/*************************************************************
  Function   : Read_BH1750
  Description: BH1750������ֵ
  Input      :  none
  return     : ---���ص�����  uint16_t    
*************************************************************/
uint16_t Read_BH1750(void)
{   	
		uint16_t data;
		uint8_t temp[2];
	
    I2C_Start();                         //��ʼ�ź�
    I2C_WriteByte(BH1750_Addr+1);        //�����豸��ַ+���ź�
	  I2C_WaiteForAck();
	  temp[0]=I2C_ReadByte(I2C_ACK);       //ACK read data msb first
	  temp[1]=I2C_ReadByte(I2C_NACK);      //NACK
	  I2C_Stop();                          //ֹͣ�ź�
		data = temp[0];
		data = (data<<8)+temp[1];			//�ϳ����ݣ�����������
    delay_ms(5);
	
		return data;	
}
/*************************************************************
  Function   : Convert_BH1750
	Description: ת����ȡ�Ĺ���ֵ��unit:lx ����0.1 lx
  Input      : light_value ---  bh1750��register���ն�ֵ
	return     : ת����Ĺ��ն� unit :lx
*************************************************************/
float Convert_BH1750(uint16_t light_value)
{
	
	float result_lx=0;
 	
	result_lx=(float)light_value/1.2;

	return result_lx;
}


