/********************************************
���ܣ�һԪ���Իع�Ͷ�Ԫ���Իع�

copyright:SLR()��MLR()��������
sqt2()������ʿ���㷨����
********************************************/

#include<math.h>
#include <stdio.h>
#include "matrixComputation.h"

void SLR(float *y,float *x,int n,float *x_fitting); //һԪ���Իع�
void MLR(float **xy,int n,int m,float *x_fitting); //��Ԫ���Իع�
int chlk(float a[],int n,int m,float d[]); //��Գ������������ƽ��������->sqt2()
void sqt2(float *x,float *y,int m,int n,float *a); //��Ԫ���Իع�
void de_allocate(float **data,int m); //�ͷ��ڴ浥Ԫ