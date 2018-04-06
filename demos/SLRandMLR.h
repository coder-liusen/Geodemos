/********************************************
功能：一元线性回归和多元线性回归

copyright:SLR()与MLR()来自网络
sqt2()来自徐士良算法程序集
********************************************/

#include<math.h>
#include <stdio.h>
#include "matrixComputation.h"

void SLR(float *y,float *x,int n,float *x_fitting); //一元线性回归
void MLR(float **xy,int n,int m,float *x_fitting); //多元线性回归
int chlk(float a[],int n,int m,float d[]); //求对称正定方程组的平方根方法->sqt2()
void sqt2(float *x,float *y,int m,int n,float *a); //多元线性回归
void de_allocate(float **data,int m); //释放内存单元