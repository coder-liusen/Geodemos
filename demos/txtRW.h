/********************************************
���ܣ��ı��ļ���д����

�ļ������ݵĴ洢ģʽ�����֣�
0-�������ݰ��д�
1-�������ݰ��д�
********************************************/

//�ı��ļ�2D��3D���ݶ�д
#ifndef _TXTRW_H
#define _TXTRW_H

#include <fstream>
#include <iostream>

bool txtRead_2D(char *ch,float **arr,int n,int m,int imode); //���ı��ļ��ж�����ά����
bool txtWrite_2D(char *ch,float **arr,int n,int m,int imode); //���ı��ļ���д���ά����
bool txtRead_3D(char *ch,float ***arr,int ni,int nx,int nt); //���ı��ļ��ж�����ά����
bool txtWrite_3D(char *ch,float ***arr,int ni,int nx,int nt);//���ı��ļ���д����ά����
#endif _TXTRW_H