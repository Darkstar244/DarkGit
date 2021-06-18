#include"iic.h"
int main()
{
	oled_init();//初始化
	oled_showchinese(0,0,1);//显示汉字
	oled_showchinese(16,0,0);
	oled_showchinese(32,0,2);
	oled_showchinese(48,0,2);
	oled_showchinese(64,0,3);
	oled_showchinese(80,0,4);
  delay_ms(3000);
	oled_showstring(0,2,"Presented by",32);//显示字符串
	oled_showstring(0,3,"DarkStar244",32);
	oled_showstring(0,4,"114514",16);
	oled_wr_byte(0x2e,0);//关滚动
	oled_wr_byte(0x29,0);//方向，29右，2a左
	oled_wr_byte(0x00,0);//空字节
  oled_wr_byte(0x04,0);//水平起始页
	oled_wr_byte(0x0cf,0);//水平滚动速度
	oled_wr_byte(0x01,0);//水平结束页
	oled_wr_byte(0x00,0);//每次垂直滚动位移
	oled_wr_byte(0x2f,0);//开滚动
  while (1){;}
}