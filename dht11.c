#include "dht11.h"
#include "intrins.h"
#include "GPIO.h"
#include "oled.h"

void dht11_gpio_OUT()
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_0;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);//初始化
}

void Delay30us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 87;
	while (--i);
}
void Delay10us()		
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 27;
	while (--i);
}

u8 DHT11_Init(void)
{
	
	DHT11_DQ=1;
	DHT11_Rst();	  
	return DHT11_Check();	
}


void DHT11_Rst(void)	   
{ 

	DHT11_DQ=1;
	Delay10us();
	DHT11_DQ=0; 	
  delay_ms(25);  
  DHT11_DQ=1; 	
	Delay30us();  
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;

	while (!DHT11_DQ&&retry<100)//判断从机发出 80us 的低电平响应信号是否结束
	{
		retry++;
		_nop_();
	};
	if(retry>=100)return 1;
	
	else retry=0;
    while (DHT11_DQ&&retry<100)//判断从机发出 80us 的高电平是否结束如结束则主机进入数据接收状态
	{
		retry++;
		_nop_();
	};	 
	if(retry>=100)return 1;	    
	return 0;
}

//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)    
{        
    u8 i,temp;
	u8 data_byte=0; 
	u8 retry=0;

  	for(i=0;i<8;i++)//接收8bit的数据 
  	{ 
//		while(!DHT11_DQ);//等待50us的低电平开始信号结束
		while (!DHT11_DQ&&retry<50)//等待50us的低电平开始信号结束
		{
			retry++;
			_nop_();
		};
		retry=0; 
		Delay30us();//等待40us 
		temp=0;//时间为26us-28us表示接收的为数据'0' 
		if(DHT11_DQ==1) 
			temp=1; //如果26us-28us之后还为高电平则表示接收的数据为'1' 
//		while(DHT11_DQ);//等待数据信号高电平'0'为26us-28us'1'为70us
		while (DHT11_DQ&&retry<100)//等待数据信号高电平'0'为26us-28us'1'为70us
		{
			retry++;
			_nop_();
		};
		data_byte<<=1;//接收的数据为高位在前右移 
		data_byte|=temp; 
  	} 

  	return data_byte;
}

//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
		
	}else return 1;
	return 0;	    
}

