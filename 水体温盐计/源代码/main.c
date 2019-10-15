#include <reg52.h>
#include <lcd.h>
#include <DS18B20.h>

sbit SKey = P1^0;
sbit DisKey = P1^1;
sbit LED1 = P2^6;
sbit LED2 = P2^7;

extern int DS18B20ReadTemp();
extern int TDS_Value_Conversion();

//T记录温度信息，E记录TDS信息
char pdata TData[6];
char pdata EData[6];
char pdata MemT[108];
char pdata MemE[108];

void main()
{
	int temp,tds;
	unsigned index = 0;		//表示存储位置
	bit overflow = 0;			//判断存储容器状态（满/未满）
	unsigned char i=0;
	char reflect[]={'0','1','2','3','4','5','6','7','8','9'};
	
	
	LCDInit();
	while(1)
	{
		if(SKey == 0)
		{
			Delay(4);
			if(SKey == 0)
			{
				LED1 = 0;
				if(overflow == 1)
					break;
				
				/*读取温度*/
				temp=DS18B20ReadTemp();
			
				TData[0] = reflect[(temp%10)];
				TData[1] = reflect[(temp%100/10)];
				TData[2] = '.';
				TData[3] = reflect[(temp%1000/100)];
				TData[4] = reflect[(temp%10000/1000)];
				TData[5] = ' ';
				
				for(i=0;i<=5;i++)
				{
					DisplaySingleChar(0,0,TData[i]);
					Delay(100);
				}
				
				/*读取TDS值*/
				tds = TDS_Value_Conversion();
				
				EData[0] = reflect[(tds%10)];
				EData[1] = reflect[(tds%100/10)];
				EData[2] = reflect[(tds%1000/100)];
				EData[3] = reflect[(tds%10000/1000)];
				EData[4] = reflect[(tds%100000/10000)];
				EData[5] = ' ';
				

				LED1=0;
			  Delay(200);
				for(i=0;i<=5;i++)
				{
					DisplaySingleChar(0,0,EData[i]);
					Delay(100);
				}
				LED1=1;
				
				for(i=0;i<=5;i++)
				{
					MemT[index] = TData[i];
					MemE[index] = EData[i];
					index++;									
					if(index==108)					//index指向108，表示107刚刚存入数据，容器已满
					{
						overflow = 1;
						break;
					}
					Delay(100);
				}
				
			}
	  }
		
		if(DisKey == 0)
		{
			Delay(2);
			if(DisKey == 0)
			{
				LCDInit();
				LED2 = 0;
				
				for(i=0;i<=index;i++)
				{
					DisplaySingleChar(0,0,MemT[i]);
					DisplaySingleChar(0,1,MemE[i]);
					Delay(100);	
				}
				
				LED2 = 1;
			}
		}
		
	}
}