/********************(C) COPRIGHT 2019 Crownto electronic **************************
 * �ļ���  ��main.c
 * ����    ��        
 * Ӳ�����ӣ�
 * PCF8591:VCC -> 5V; GND -> GND; SCL -> P1.6;SDA -> P1.7; 
 
 * LCD1602:RS -> P2.5; RW -> P2.6; E -> P2.7;
 *         D0~D7 -> P0��
 * TDS������ģ��: VCC -> 5V; GND -> GND; AO -> AIN0;
 *
 * ��������������TDSֵҺ����ʾ��
             ���ڽ��ղ������õ�TDSֵ��������9600����
 *           ��������λ����ʾTDSֵ��
 * �Ա�    ��https://ilovemcu.taobao.com
**********************************************************************************/

#include <reg52.h>
#include <include.h>
#include "DS18B20.h"


/**************�ⲿ��������************************/
int num=0; 
/**************��������***************************/
double PH=0.0;
unsigned char disbuff[9]={0};
double ADC_Voltage=0.0;
float TDS_voltage;
float TDS_value=0.0;
float temp_data=25.0;
float compensationCoefficient=1.0;//�¶�У׼ϵ��(T����),T����=1+0.02*��T����-25��
float compensationVolatge;
float kValue=1.0;


void Get_Voltage_Value()
{
	ISendByte(PCF8591,0x40);		//*��һ������Ϊ�������ڶ�������Ϊ���͵����ݣ������ֽڣ�0x40��ʾʹ�ܣ�ȡ���Զ�������ѡ��ͨ��0
      num=IRcvByte(PCF8591);  //ADC0 ģ��ת��1      PH�缫
		  ADC_Voltage =num * 5.0/ 255;  //ת��Ϊ��ѹֵ
}
/*
 * ��������Character_Conversion
 * ����  ����ʱ����
 *         
 * ����  ��unsigned char n����ʱ��
 * ���  ����
 * ˵��  ��
 */
/**************TDSֵ�ɼ�����***************/
int TDS_Value_Conversion()
{

	Get_Voltage_Value();

	TDS_voltage=(num*5.0)/256;
	compensationCoefficient=1.0+0.02*((temp_data/10)-25.0); 
	compensationVolatge=TDS_voltage*compensationCoefficient;      //  /����* ��������������������������
	TDS_value=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 
	255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5*kValue; //���TDS����ֵ
	
	  if((TDS_value<=0)){TDS_value=0;}
		if((TDS_value>1400)){TDS_value=1400;}

		TDS_value = TDS_value*10+0.5; //����һλС������������
		TDS_value = (int)TDS_value;

		
		return TDS_value;
}


