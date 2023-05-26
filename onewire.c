#include "onewire.h"
void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}

void Delay_OneWire(unsigned int t)  
{
	while(t--);
}
void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
void Delay645us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 7;
	j = 237;
	do
	{
		while (--j);
	} while (--i);
}
void Delay88us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}




void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
        Delay88us();
		DQ = dat&0x01;
		Delay_OneWire(50);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(50);
}

unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
        //Delay5us();	
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(50);
	}
	return dat;
}


bit init_ds18b20(void)
{
  	bit initflag = 0;
    DQ = 1;
    _nop_();
  	DQ = 0;
  	Delay645us();
  	DQ = 1;
  	Delay88us(); 
    initflag = DQ;     
  	Delay500us();
    DQ=1;
  
  	return initflag;
}




u16 read_temp()  	//启动温度转换，读取温度
{
	u16 tl=0,th=0;
	u16 temp;
	if(init_ds18b20())
		return 0x7fff;
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);//启动DS18B20进行温度转换

	Write_DS18B20(0xcc);//匹配RAM，适用多个点的情况
	Write_DS18B20(0xBE);//读DS18B20内部RAM中9字节的温度数据
	tl=Read_DS18B20();//读低8位
	th=Read_DS18B20();//读高8位
	temp=(th<<8)+tl;
	temp = temp*0.0625;
	return temp;
}


//void DS1302_Init()
//{
//    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
//	GPIO_InitStructure.Pin  = GPIO_Pin_0;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
//	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化
//}


