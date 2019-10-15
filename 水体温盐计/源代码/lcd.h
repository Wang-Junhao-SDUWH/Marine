#ifndef _LCD_H
#define _LCD_H

 /********************************************************************************\
**                         			�궨����									**
\********************************************************************************/
/*-------------------------------  LCDģ�� ------------------------------------*/
#define Busy			0x80					//æ�ź�
#define LCD_Data 	  P0	      //���ݿڶ���
#define Write				0x00					//�͵�ƽд��
#define Read				0x01					//�ߵ�ƽ����
#define Data				0x01					//�ߵ�ƽѡ������
#define Cmd				    0x00					//�͵�ƽѡ������

#define Enable		    	0x00					//Ծ�䵽�͵�ƽʱִ������
#define Disable		    	0x01    
#define True				0x01
#define False				0x00
#define LCD_Init			0x38					//��ʼ��ģʽ							
#define LCD_DispCtr    		0x0C					//����ʾ���������
#define LCD_CloseCtr		0x08					//����ʾ
#define LCD_CLS        		0x01					//����Ļ
#define LCD_EnterSet   		0x06					//��ʾ��� 

 /********************************************************************************\
**                         			��������									**
\********************************************************************************/
extern void LCDInit(void);								//LCD��ʼ��
void SetWriteCmd(void);								//����д����ģʽ
void SetReadCmd(void);								//���ö�����ģʽ
void SetWriteData(void);							//����д����ģʽ
extern void WriteCmd(char cmd);							//д����
void WriteData(char ddata);							//д����
void ExecuteCmd(void);								//ִ������
void SetXY(char x,char y);							//��λ��ʾ��ַ
extern void DisplaySingleChar(char x,char y,char cchar);		//��ʾ�����ַ�
extern void DisplayString(char x,char y,char *str); 			//��ʾһ���ַ���
void Delay(unsigned int time);						//��ʱ������
void DelayUs(unsigned int time);						//��ʱ�ӳ���
bit  IsBusy(void);									//�ж�æ��־����
extern void delay_1s();	
#endif