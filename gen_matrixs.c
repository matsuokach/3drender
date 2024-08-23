#include "gen_matrix.h"
const float pi=3.1415926f;
void genmat(int16_t *inputxyz,int16_t *outputxyz,int16_t ax,int16_t ay,int16_t az,float scalex,float scaley,float scalez,int8_t ywx,int8_t ywy,int8_t ywz,uint8_t back)
{
	 float sx,sy,sz;
	 float cx,cy,cz;
	static float c1,c2,c3,c4,c5,c6,c7,c8,c9;
	if(back)
	{
	sx=sin((float)ax*pi/360);
	sy=sin((float)ay*pi/360);
	sz=sin((float)az*pi/360);
	cx=cos((float)ax*pi/360);
	cy=cos((float)ay*pi/360);
	cz=cos((float)az*pi/360);
	c1=cx*cy*scalex;
	c2=(sx*sz*cy-cz*sy)*scalex;
	c3=(sx*cz*cy+sz*sy)*scalex;
	c4=cx*sy*scaley;
	c5=(sz*sx*sy+cz*cy)*scaley;
	c6=(sx*sy*cz-sz*cy)*scaley;
	c7=-sx*scalez;
	c8=sz*cx*scalez;
	c9=cz*cx*scalez;
	}
	outputxyz[0]=ywx+inputxyz[0]*c1+inputxyz[1]*c2+inputxyz[2]*c3;
	outputxyz[1]=ywy+inputxyz[0]*c4+inputxyz[1]*c5+inputxyz[2]*c6;
	outputxyz[2]=ywz+inputxyz[0]*c7+inputxyz[1]*c8+inputxyz[2]*c9;
	outputxyz[3]=ywx+inputxyz[3]*c1+inputxyz[4]*c2+inputxyz[5]*c3;
	outputxyz[4]=ywy+inputxyz[3]*c4+inputxyz[4]*c5+inputxyz[5]*c6;
	outputxyz[5]=ywz+inputxyz[3]*c7+inputxyz[4]*c8+inputxyz[5]*c9;
	outputxyz[6]=ywx+inputxyz[6]*c1+inputxyz[7]*c2+inputxyz[8]*c3;
	outputxyz[7]=ywy+inputxyz[6]*c4+inputxyz[7]*c5+inputxyz[8]*c6;
	outputxyz[8]=ywz+inputxyz[6]*c7+inputxyz[7]*c8+inputxyz[8]*c9;
}	