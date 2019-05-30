#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit PWM=P2^0;//  P2输出pwm
sbit p1=P2^1;
sbit p2=P2^2;
sbit p3=P2^3;
sbit p4=P2^4;
uchar time=0;  // 定义占空比的变量
uint n=0;//占空比
bit m=0;//输出翻转定义
void main()
{
	
T2CON=0; //配置定时器2控制寄存器，这里其实不用配置，T2CON上电默认就是0，这里赋值只是为了演示这个寄存器的配置
IE=0xA0; //1010 0000开总中断，开外定时器2中断
TR2=1; //启动定时器2
	TH2=0xff;//赋初值定时
	TL2=0xf7;//定时时间按照自己的晶振计算
	EA=1;//开总中断
	ET2=1;//开定时器0中断
	TR2=1;//启动定时器0 
	while(1)
	{			
	
}//这里可以写别的东西，检测函数之类的，也可以什么都不做
}
void tim2() interrupt 5
{
	TF2=0;//定时器2需要软件清零
	TR2=0;//赋初值时，关闭定时器
	TH2=0xff;//赋初值定时
	TL2=0xf7;//
	TR2=1;//打开定时器
	time++;
	if(time>=100)  //
	{
	time=0;
	n++;
	}
	if((n>=100)&&(m==0))
	{
	n=0;
	m=1;
	}
	if((n>=100)&&(m==1))
	{
	n=0;
	m=0;
	}
	if((time<=n)&&(m==0))   //占空比
	{ PWM=0;p1=0;p2=0;p3=0;p4=0;}  
	else if((time>n)&&(m==0))
	{PWM=1;p1=1;p2=1;p3=1;p4=1;}
	if((time<=n)&&(m==1))   //占空比
	{ PWM=1;p1=1;p2=1;p3=1;p4=1;} 
	else if((time>n)&&(m==1))
	{PWM=0;p1=0;p2=0;p3=0;p4=0;}
}