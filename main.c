//此文件为半成品，作为例程。
#include <stdint.h>//c标准文件定义了数据类型uint
#include <render.h>//
#include <gen_martrix.h>
#include "stdlib.h"//c标准文件定义了随机数生成函数
#define CUBELEN 20
uint8_t xyz[108]={5,15,40,78,10,40,43,57,10};
uint8_t xyz1[9]={5,55,50,78,60,50,43,10,10};
int16_t xyzlonga[108]=
{
CUBELEN,CUBELEN,CUBELEN,CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,CUBELEN,CUBELEN,
-CUBELEN,CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,CUBELEN,-CUBELEN,CUBELEN,
CUBELEN,CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,
-CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,
CUBELEN,CUBELEN,CUBELEN,CUBELEN,-CUBELEN,CUBELEN,CUBELEN,CUBELEN,-CUBELEN,
CUBELEN,-CUBELEN,CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,CUBELEN,-CUBELEN,
-CUBELEN,CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,
-CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,
CUBELEN,CUBELEN,CUBELEN,CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,CUBELEN,
CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,CUBELEN,
CUBELEN,-CUBELEN,CUBELEN,CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,CUBELEN,
CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,-CUBELEN,CUBELEN
};//三角形顶点原始数据，正方体12个三角形，每个三角形3个顶点共36个顶点，每个顶点有xyz三个数据
int16_t xyzlongb[108];//
uint16_t color[12]=
{
0xf800,
0xf800,
0xf81f,
0xf81f,
0xffe0,
0xffe0,
0x07e0,
0x07e0,
0x07ff,
0x07ff,
0x001f,
0x001f
};//颜色表 每个三角形一个颜色，正方体12个三角形
//uint8_t xyz2[9]={5,50,20,78,3,70,54,34,43};
//uint8_t xyz3[9]={90,5,60,25,80,70,20,35,53};
//uint8_t xyz4[9]={90,5,60,25,80,70,34,43,37};
uint16_t scrna[80][160];//帧缓冲一
uint16_t scrnb[80][160];//帧缓冲二
int i=0,j,k,z,y,m,n,t,pp=0,fr=0;
while(1)
{
	if(k)//旋转角度x的时间是否用完
z+=7;
	if(m)
n+=7;
	if(y)
t+=7;
	if(k==0)
	k=rand()%60;//随机生成一个旋转角度的时长
	else
		k--;//每过一帧时间减一
	if(y==0)
	y=rand()%60;
	else
		y--;	
	if(m==0)
	m=rand()%60;
	else
		m--;	
	for(j=0;j<108;)
	{
		
		genmat(xyzlonga+(int)j,xyzlongb+(int)j,z,n,t,1.0f,1.0f,1.0f,0,0,0,j==0?1:0);//对输入顶点旋转角度得到输出顶点
		j+=9;
	}
for(j=0;j<108;j++)//处理顶点让顶点在xy坐标中央x=1:160 y=1:80取决于分辨率
	{
	if((j%3)==0)
	xyz[j]=xyzlongb[j]+80;
	if((j%3)==1)
	xyz[j]=xyzlongb[j]+40;
	if((j%3)==2)
	xyz[j]=xyzlongb[j]+37;
	}
	i=0;
for(j=0;j<108;)//光栅化顶点
	{
		if(fr)
			triangle(xyz+j,(uint16_t*)scrna,color[i],j==0?1:0);
		else
			triangle(xyz+j,(uint16_t*)scrnb,color[i],j==0?1:0);
		i++;
		j+=9;
	}
if(fr)
	{
    ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)(scrna),160,80)；//将帧起始地址给屏幕驱动，读取数据到屏幕
    }else
	{
    ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)(scrnb),160,80)；
    }

	fr=!fr;//切换要进行计算的帧
}