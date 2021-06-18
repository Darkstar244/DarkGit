/*本程序适用于stc15f104w系列以及89c51/c52系列单片机
由暗星244结合网上资料编写而成，转载请注明出处*/
#include<reg52.h>
#include<intrins.h>
#include"oled.h"
typedef bit bool;
sbit sda=P3^2;//sda接口
sbit scl=P3^3;//scl接口
void delay_ms(uint time)//毫秒延时
{
	uint x,y;
	for(y=0;y<time;y++)
		for(x=0;x<111;x++);
}
void delay_us()//5微秒的延时
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
void iic_start()//开始iic
{
	scl=1;
	sda=1;
	delay_us();
	sda=0;
	delay_us();
	scl=0;
}
void iic_stop()//停止iic
{
	scl=0; 
	sda=0;
	scl=1;
	delay_us();
	sda=1;
	delay_us();
}
bit checkack(void)//iic响应
{
	bit ack;
	scl=0;
	sda=1;
	delay_us();
	scl=1;
	delay_us();
	ack=sda;
	delay_us();
	scl=0;
	delay_us();
	return ack;
}
void write_bit(bool b)//写单位
{
	if (b)
		sda=1;
	else
		sda=0;
	delay_us();
	scl=1;
	delay_us();
	scl=0;
}
bool read_bit(void)//读取单位
{
	bool b;
	sda=1;
	delay_us();
	scl=1;
	delay_us();
	b=sda;
	scl=0;
	return b;
}
void write_byte(bool sendstart,bool sendstop,uchar byte)//写字节
{
	int i;
	
	if(sendstart)
	{
		iic_start();
	}
	for(i=0;i<8;i++)
	{
		if(byte & 0x80)
			sda=1;
		else
			sda=0;scl=1;scl=0;
		byte <<= 1;
	}
	sda=1;scl=1;scl=0;
	if(sendstop)
	{
		iic_stop();
	}
	}
uchar read_byte(bool nack, bool sendstop)//读取字节
{
	uchar byte=0;int i;
	for(i=0;i<8;i++)
	{
		byte=(byte<<1)|read_bit();
	}
	write_bit(nack);
	if(sendstop)
		iic_stop();
	return byte;
}
void iic_writecommand(uint iic_cmd)//写命令
{
	write_byte(1,0,0x78);
	
	write_byte(0,0,0x00);
	
	write_byte(0,0,iic_cmd);
	
	iic_stop();
}
void iic_writedata(uchar iic_data)//写数据
{
	write_byte(1,0,0x78);
	
	write_byte(0,0,0x40);
	
	write_byte(0,0,iic_data);
	
	iic_stop();
}
void oled_wr_byte(unsigned dat,unsigned cmd)//oled写字节
{
	if(cmd)
	{
		iic_writedata(dat);
	}
	else
	{
		iic_writecommand(dat);
	}
}
void fill_picture(uchar fill_data)//填充图像
{
	uchar m,n;
	for(m=0;m<8;m++)
	{
		oled_wr_byte(0xb0+m,0);
		oled_wr_byte(0x01,0);
		oled_wr_byte(0x10,0);
		for(n=0;n<128;n++)
		{
			oled_wr_byte(fill_data,1);
		}
	}
}
void oled_set_pos(uchar x,uchar y)//设置光标位置
{
	oled_wr_byte(0xb0+y,0);
	oled_wr_byte(((x&0xf0)>>4)|0x10,0);
	oled_wr_byte((x&0x0f),0);
}
void oled_display_on(void)//开显示
{
	oled_wr_byte(0x8d,0);
	oled_wr_byte(0x14,0);
	oled_wr_byte(0xaf,0);
}
void oled_display_off(void)//关显示
{
	oled_wr_byte(0x8d,0);
	oled_wr_byte(0x10,0);
	oled_wr_byte(0xae,0);
}
void oled_clear(void)//清屏
{
	uchar i,n;
	for(i=0;i<8;i++)
	{
		oled_wr_byte(0xb0+i,0);
		oled_wr_byte(0x00,0);
		oled_wr_byte(0x10,0);
		for(n=0;n<128;n++)oled_wr_byte(0,1);
	}
}
void oled_on(void)//更新显示
{
	uchar i,n;
	for(i=0;i<8;i++)
	{
		oled_wr_byte(0xb0+i,0);
		oled_wr_byte(0x00,0);
		oled_wr_byte(0x10,0);
		for(n=0;n<128;n++)oled_wr_byte(1,1);
	}
}
void oled_showchar(uchar x,uchar y,uchar chr,uchar char_size)//显示一个字符，x:0-127,y:0-63,size是字体，默认填16就行
{
	uchar c=0,i=0;
	c=chr-' ';
	if(x>128-1){x=0;y=y+2;}
	if(char_size==16)
	{
		oled_set_pos(x,y);
		for(i=0;i<8;i++)
		oled_wr_byte(F8X16[c*16+i],1);
		oled_set_pos(x,y+1);
		for(i=0;i<8;i++)
		oled_wr_byte(F8X16[c*16+i+8],1);
	}
	else {
		oled_set_pos(x,y);
		for(i=0;i<6;i++)
		oled_wr_byte(F6x8[c][i],1);
	}
}
uint oled_pow(uchar m,uchar n)//次方函数
{
	uint result=1;
	while(n--)result*=m;
	return result;
}
void oled_shownum(uchar x,uchar y,uint num,uchar len,uchar size2)//x,y:坐标,num数值,len位数,size2是字体，默认填16就行
{
	uchar t,temp;
	uchar enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
	if(enshow==0&&t<(len-1))
	{
		if(temp==0)
		{
			oled_showchar(x+(size2/2)*t,y,' ',size2);
			continue;
		}else enshow=1;
	}
	oled_showchar(x+(size2/2)*t,y,temp+'0',size2);
	}
}
void oled_showstring(uchar x,uchar y,uchar *chr,uchar char_size)//显示一个字符串
{
	uchar j=0;
	while(chr[j]!='\0')
	{
		oled_showchar(x,y,chr[j],char_size);
    x+=8;
		if(x>120){x=0;y+=2;}
		j++;
	}
}
void oled_showchinese(uchar x,uchar y,uchar no)//显示汉字,xy为坐标，no为编号
{
	uchar t,adder=0;
	oled_set_pos(x,y);
	for(t=0;t<16;t++)
	{
		oled_wr_byte(HzK[2*no][t],1);
		adder+=1;
	}
	oled_set_pos(x,y+1);
	for(t=0;t<16;t++)
	{
		oled_wr_byte(HzK[2*no+1][t],1);
		adder+=1;
	}
}
void oled_drawbmp(uchar x0,uchar y0,uchar x1,uchar y1,uchar bmp[])//画图
{
	uint j=0;
	uchar x,y;
	if(y1%8==0)y=y1/8;
	else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		oled_set_pos(x0,y);
		for(x=x0;x<x1;x++)
		{
			oled_wr_byte(bmp[j++],1);
		}
	}
}
void oled_init(void)//初始化ssd1306
{
	delay_ms(500);//延时（必须有）
	oled_wr_byte(0xAE,0);//关闭oled面板
	oled_wr_byte(0x00,0);//设置低位列地址
	oled_wr_byte(0x10,0);//设置高位列地址
	oled_wr_byte(0x40,0);//设置起始行地址设置映射RAM显示起始行（0x00~0x3F）
	oled_wr_byte(0x81,0);//--设置对比度控制寄存器
	oled_wr_byte(0xCF,0);//设置SEG输出电流亮度
	oled_wr_byte(0xA1,0);//设置分段/列映射0xa0左右反置 0xa1型正常
	oled_wr_byte(0xC8,0);//设置COM/行扫描方向0xc0上下反置 0xc8型正常
	oled_wr_byte(0xA6,0);//设置正常显示
	oled_wr_byte(0xA8,0);//设置复用比（1到64）
	oled_wr_byte(0x3F,0);//1/64负载
	oled_wr_byte(0xD3,0);//设置显示偏移映射RAM计数器（0x00~0x3F）
	oled_wr_byte(0x00,0);//不补偿
	oled_wr_byte(0xD5,0);//设置显示时钟分频比/振荡器频率
	oled_wr_byte(0x80,0);//设置分频比，将时钟设置为100帧/秒
	oled_wr_byte(0xD8,0);
	oled_wr_byte(0x05,0);
	oled_wr_byte(0xD9,0);//设置预充电时间
	oled_wr_byte(0xF1,0);//将预充电设置为15个时钟，放电设置为1个时钟
	oled_wr_byte(0xDA,0);//设置com引脚硬件配置
	oled_wr_byte(0x12,0);//
	oled_wr_byte(0xDB,0);//设置vcomh
	oled_wr_byte(0x40,0);//设置VCOM取消选择级别
	oled_wr_byte(0x20,0);//设置页面寻址模式（0x00/0x01/0x02）
	oled_wr_byte(0x02,0);//
	oled_wr_byte(0x8D,0);//设置电荷泵启用/禁用
	oled_wr_byte(0x14,0);//设置（0x10）禁用
	oled_wr_byte(0xA4,0);//禁用整个显示打开（0xa4/0xa5）
	oled_wr_byte(0xA6,0);//禁用反转显示打开（0xa6/a7）
	oled_wr_byte(0xAF,0);//打开oled面板
	fill_picture(0x00);//初始清屏
	oled_set_pos(0,0);//初始光标
}