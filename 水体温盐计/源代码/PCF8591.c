#include "PCF8591.h"
#include "I2C.h"

/*******************************************************************
DAC �任, ת������            �ò����������޷�   
*******************************************************************/
//bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
//{
//   Start_I2c();              //��������
//   SendByte(sla);            //����������ַ
//   if(ack==0)return(0);
//   SendByte(c);              //���Ϳ����ֽ�
//   if(ack==0)return(0);
//   SendByte(Val);            //����DAC����ֵ  
//   if(ack==0)return(0);
//   Stop_I2c();               //��������
//   return(1);
//}

/*******************************************************************
ADC�����ֽ�[����]���ݺ���               
*******************************************************************/
bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //��������
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC���ֽ����ݺ���               
*******************************************************************/
unsigned char IRcvByte(unsigned char sla)
{  
	unsigned char c;

   Start_I2c();          //��������
   SendByte(sla+1);      //����������ַ
   if(ack==0)return(0);						//*ack��ֵ��I2C�ĺ����в���
   c=RcvByte();          //��ȡ����0

   Ack_I2c(1);           //���ͷǾʹ�λ
   Stop_I2c();           //��������
   return(c);
}
