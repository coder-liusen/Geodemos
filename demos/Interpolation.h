/********************************************
功能：信号插值
********************************************/
#include <math.h>
#include<stdlib.h>
#include <string.h>

void LI(float *x,float *y,int n1,int n2); //线性插值
void Interpolate3(float *x, float *x_position, int nx, float *y, float *y_position, int ny); //三次样条插值