/********************************************
功能：文本文件读写数组

文件中数据的存储模式有两种：
0-各道数据按列存
1-各道数据按行存
********************************************/

//文本文件2D、3D数据读写
#ifndef _TXTRW_H
#define _TXTRW_H

#include <fstream>
#include <iostream>

bool txtRead_2D(char *ch,float **arr,int n,int m,int imode); //从文本文件中读出二维数组
bool txtWrite_2D(char *ch,float **arr,int n,int m,int imode); //向文本文件中写入二维数组
bool txtRead_3D(char *ch,float ***arr,int ni,int nx,int nt); //从文本文件中读出三维数组
bool txtWrite_3D(char *ch,float ***arr,int ni,int nx,int nt);//向文本文件中写入三维数组
#endif _TXTRW_H