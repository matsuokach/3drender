#include "render.h"

int8_t deep[80][160];
void triangle(uint8_t *xyz,uint16_t* colormap, uint16_t color,uint8_t draw_back)
{
	
	uint16_t bb=0xf80;
	uint16_t r=0x07e0;
	uint16_t g=0x001f;
	uint16_t *colorp;
	uint8_t *deepp;
	int16_t minx;
	int16_t miny;
	int16_t minz;
  int16_t midx;
	int16_t midy;
	int16_t midz;
	int16_t maxx;
	int16_t maxy;
	int16_t maxz;
  minx=0xff;
	midx=0;
	maxx=0;
	uint8_t px;
	uint8_t py;
	float pymin,pymax,pymid,pzx,pzy;
	uint8_t int_pzy;
	float pydmax,pydmin,pydmid,pzxd,pzyd;
	float tempa,tempb;
	uint8_t samex=0;//1==front same 2=tail same 3=all same
	uint8_t minnum,midnum;
	float direction;
	int ja,jb;
	uint8_t tmin,tmax,tmid;
	if(draw_back)
  for(ja=0;ja<80;ja++)
	for(jb=0;jb<160;jb++)
	{
	colormap[ja*160+jb]=0;
	deep[ja][jb]=127;
	}
  for( ja=0;ja<3;ja++)
	{
		if(xyz[ja*3]<minx)
		{ 
			minx=xyz[ja*3];
			miny=xyz[ja*3+1];
			minz=xyz[ja*3+2];
			minnum=ja;
		}
	}
	for( ja=0;ja<3;ja++)
	{
		if(xyz[ja*3]>maxx)
		{ 
			maxx=xyz[ja*3];
			maxy=xyz[ja*3+1];
			maxz=xyz[ja*3+2];
			midnum=ja;
		}
	}
		for( ja=0;ja<3;ja++)
	{
		if(ja!=midnum&&ja!=minnum)
		{ 
			midx=xyz[ja*3];
			midy=xyz[ja*3+1];
			midz=xyz[ja*3+2];
		}
	}
/*switch(2-(minnum+midnum))
	 {
		 case 0:
			midx=xyz[0];
			midy=xyz[1];
		 break;
		 case 1:
			midx=xyz[2];
			midy=xyz[3]; 
		 break;
		 case 2:
			midx=xyz[4];
			midy=xyz[5];
			break;		 
		 defualt:;
	 }*/
/*	 for(ja=40;ja<80;ja++)
	for(jb=minx;jb<maxx;jb++)
	scrn[ja][jb]=r;
	 for(ja=0;ja<30;ja++)
	for(jb=minx;jb<midx;jb++)
	scrn[ja][jb]=0;
	*/
	if(midx==minx){
		samex=1;
		if(midx==maxx){
			samex=3;
		}
	}
	else if(midx==maxx){
		samex=2;
	}

	pzxd=(float)(maxz-minz)/(maxx-minx);
	tempa=(float)(midx-minx)/(maxx-minx);//mid/max
	tempb=((float)midy-(tempa*(maxy-miny)+(float)miny));//midy-maxline
	if(tempb>-1.0f&&tempb<-1.0f)
	{
		pzyd=1.0f;
		return;
	}
	else
		pzyd=(float)(midz-(pzxd*(midx-minx)+minz))/tempb;
		


	
	if(!(samex&1))
	{
	pydmin=(float)(midy-miny)/(midx-minx);}
	if(!(samex&1))
	pydmax=(float)(maxy-miny)/(maxx-minx);
	pymin=miny;
	pymax=miny;
	pzx=minz;
	if((samex&0x1)!=1)
		for(px=minx;px<midx;px++)
		{
			pymin+=pydmin;
			pymax+=pydmax;
			tmin=(int)pymin;
			tmax=(int)pymax;
			pzx+=pzxd;
			pzy=pzx;
			colorp=colormap+px+160*tmax;
			deepp=(uint8_t*)deep+px+160*tmax;
			if(tmin<tmax)
			for(py=tmax;py>=tmin;py--)
			{		
				pzy-=pzyd;
				int_pzy=pzy;
				
				if(int_pzy<=*deepp)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp-=160;
				colorp-=160;
			}
			else
			for(py=tmax;py<=tmin;py++)
			{
			  pzy+=pzyd;
				int_pzy=pzy;
				if(int_pzy<=*deepp)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp+=160;
				colorp+=160;
			}	
		}
	else
	{
		px=minx;
		pzy=pzx;
		tmin=(int)miny;
		tmax=(int)maxy;
					colorp=colormap+px+160*tmax;
			deepp=(uint8_t*)deep+px+160*tmax;
		if(tmin>tmax)
		for(py=tmax;py<=tmin;py++)
		{
				pzy+=pzyd;
				int_pzy=pzy;
				if(*deepp>=int_pzy)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp+=160;
				colorp+=160;
		}
		else
		for(py=tmax;py>=tmax;py--)
		{
				pzy-=pzyd;
				int_pzy=pzy;
				if(*deepp>=int_pzy)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp-=160;
				colorp-=160;
		}
	}
	pymid=midy;
	pydmid=(float)(maxy-midy)/(maxx-midx);
	pydmax=(float)(maxy-miny)/(maxx-minx);
	if(!(samex&0x2)){
		for(px=midx;px<maxx;px++)
		{
			pymid+=pydmid;
			pymax+=pydmax;
			tmid=(int)pymid;
			tmax=(int)pymax;
			pzx+=pzxd;
			pzy=pzx;
			colorp=colormap+px+160*tmax;
			deepp=(uint8_t*)deep+px+160*tmax;
			if(tmid<tmax)
				for(py=tmax;py>=tmid;py--)
			{
				pzy-=pzyd;
				int_pzy=pzy;
				if(int_pzy<=*deepp)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp-=160;
				colorp-=160;
			}
			else
				for(py=tmax;py<=tmid;py++)
			{
				pzy+=pzyd;
				int_pzy=pzy;
				if(int_pzy<=*deepp)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp+=160;
				colorp+=160;
			}
			
		
			
		}

	}
	else
	{
		px=midx;
		pzy=pzx;
		colorp=colormap+px+160*maxy;
			deepp=(uint8_t*)deep+px+160*maxy;
		if(midy>maxy)
		for(py=maxy;py<=midy;py++)
		{
				pzy+=pzyd;
				int_pzy=pzy;
				if(int_pzy<=*deepp)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp+=160;
				colorp+=160;
		}
		else
		for(py=maxy;py>=midy;py--)
		{
				pzy-=pzyd;
				int_pzy=pzy;
				if(int_pzy<=*deepp)
				{
					*deepp=int_pzy;
					*colorp=color;
				}
				deepp-=160;
				colorp-=160;
		}
	}

}