#ifndef _E2P_H
#define _E2P_H

//IO口定义
sbit E_SCL = P1^6;
sbit E_SDA = P1^7;

//函数声明

unsigned char I2CReadACK();
unsigned char I2CReadNAK();
bit I2CWrite(unsigned char dat);
void I2CStop();
void I2CStart();
void E2WriteByte(unsigned char addr,unsigned char dat);
unsigned char E2ReadByte(unsigned char addr);
void MemToStr(unsigned char *str,unsigned char *src,unsigned char len);
void E2Read(unsigned char *buf,unsigned char addr,unsigned char len);
void E2Write(unsigned char *buf,unsigned char addr,unsigned char len);