#ifndef MAT
#define MAT
#include "stdint.h"
#include "math.h"

void genmat(int16_t *inputxyz,int16_t *outputxyz,int16_t ax,int16_t ay,int16_t az,float scalex,float scaley,float scalez,int8_t ywx,int8_t ywy,int8_t ywz,uint8_t back);
#endif