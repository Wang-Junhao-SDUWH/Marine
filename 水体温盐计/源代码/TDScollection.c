/********************(C) COPRIGHT 2019 Crownto electronic **************************
 * 文件名  ：main.c
 * 描述    ：        
 * 硬件连接：
 * PCF8591:VCC -> 5V; GND -> GND; SCL -> P1.6;SDA -> P1.7; 
 
 * LCD1602:RS -> P2.5; RW -> P2.6; E -> P2.7;
 *         D0~D7 -> P0口
 * TDS传感器模块: VCC -> 5V; GND -> GND; AO -> AIN0;
 *
 * 功能描述：测量TDS值液晶显示；
             串口接收测量所得的TDS值（波特率9600）；
 *           可连接上位机显示TDS值；
 * 淘宝    ：https://ilovemcu.taobao.com
**********************************************************************************/

#include <reg52.h>
#include <include.h>
#include "DS18B20.h"


/**************外部变量定义************************/
int num=0; 
/**************变量定义***************************/
double PH=0.0;
unsigned char disbuff[9]={0};
double ADC_Voltage=0.0;
float TDS_voltage;
float TDS_value=0.0;
float temp_data=25.0;
float compensationCoefficient=1.0;//温度校准系数(T修正),T修正=1+0.02*（T测试-25）
float compensationVolatge;
float kValue=1.0;


void Get_Voltage_Value()
{
	ISendByte(PCF8591,0x40);		//*第一个参数为器件，第二个参数为发送的数据（控制字节）0x40表示使能，取消自动增量，选择通道0
      num=IRcvByte(PCF8591);  //ADC0 模数转换1      PH电极
		  ADC_Voltage =num * 5.0/ 255;  //转换为电压值
}
/*
 * 函数名：Character_Conversion
 * 描述  ：延时函数
 *         
 * 输入  ：unsigned char n：延时量
 * 输出  ：无
 * 说明  ：
 */
/**************TDS值采集函数***************/
int TDS_Value_Conversion()
{

	Get_Voltage_Value();

	TDS_voltage=(num*5.0)/256;
	compensationCoefficient=1.0+0.02*((temp_data/10)-25.0); 
	compensationVolatge=TDS_voltage*compensationCoefficient;      //  /还是* ？？？？？？？？？？？？？
	TDS_value=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 
	255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5*kValue; //求出TDS测试值
	
	  if((TDS_value<=0)){TDS_value=0;}
		if((TDS_value>1400)){TDS_value=1400;}

		TDS_value = TDS_value*10+0.5; //保留一位小数并四舍五入
		TDS_value = (int)TDS_value;

		
		return TDS_value;
}


