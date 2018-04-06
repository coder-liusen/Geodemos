#include "txtRW.h"

/***************文本文件读2D数据****************
*ch:文件名；
*arr:数组；
*n:数据采样点数；
*m:数据道数；
*imode:0-文件中数据按照模式0存储，
      1-文件中数据按照模式1存储；
*返回值:0-文件打开出错
       1-文件打开正常

*注意：读出的数组总是m为第一下标，n为第二下标
***********************************************/
bool txtRead_2D(char *ch,float **arr,int n,int m,int imode)
{
	FILE *fp;
	fp=fopen(ch,"r");
	if(fp==NULL){return 0;}

	if(imode==0)
	{
		for (int j=0;j<n;j++)
	    {
			for (int i=0;i<m;i++)
			{fscanf(fp,"%f",&arr[i][j]);}
		}
	}
	else if(imode==1)
	{	
		for (int i=0;i<m;i++)
	    {
			for (int j=0;j<n;j++)
			{fscanf(fp,"%f",&arr[i][j]);}
		}
	}
	fclose(fp);	

	return 1;
}

/***************文本文件写2D数据****************
*ch:文件名；
*arr:数组；
*n:数据采样点数；
*m:数据道数；
*imode:0-文件中数据按照模式0存储，
      1-文件中数据按照模式1存储；
*返回值:0-文件打开出错
       1-文件打开正常

*注意：写入的数组总是m为第一下标，n为第二下标
***********************************************/
bool txtWrite_2D(char *ch,float **arr,int n,int m,int imode)
{
	FILE *fp;
	fp = fopen(ch,"w");
	if(fp==NULL){return 0;}

	if(imode==0)
	{
		for (int j=0;j<n;j++)
	    {
			for (int i=0;i<m;i++)
			{fprintf(fp,"%f ",arr[i][j]);} //空格可视情况换成\t
			fprintf(fp,"\n");
	    }
	}
	else if(imode==1)
	{
		for (int i=0;i<m;i++)
	    {
			for (int j=0;j<n;j++)
			{fprintf(fp,"%f ",arr[i][j]);} //空格可视情况换成\t
			fprintf(fp,"\n");
		}
	}
	fclose(fp);

	return 1;
}

/******读txt数据-3D******
*ch:文件名
*arr:数组
ni:inLine方向道数
nx:xLine方向道数
nt:采样点数
************************/
bool txtRead_3D(char *ch,float ***arr,int ni,int nx,int nt)
{
	FILE *fp;
	fp=fopen(ch,"r");
	if(fp==NULL){return 0;}
	for (int i1=0;i1<ni;i1++)
	{
		for (int i2=0;i2<nx;i2++)
		{
			for (int j=0;j<nt;j++)
			{fscanf(fp,"%f",&arr[i1][i2][j]);}
		}
	}
	fclose(fp);	
	return 1;
}

/******写txt数据-3D******
*ch:文件名
*arr:数组
ni:inLine方向道数
nx:xLine方向道数
nt:采样点数
************************/
bool txtWrite_3D(char *ch,float ***arr,int ni,int nx,int nt)
{
	FILE *fp;
	fp = fopen(ch,"w");
	if(fp==NULL){return 0;}
	
	for (int i1=0;i1<ni;i1++)
	{
		for (int i2=0;i2<nx;i2++)
		{
			for (int j=0;j<nt;j++)
			{fprintf(fp,"%f ",arr[i1][i2][j]);}  
			fprintf(fp,"\n");
		}
	}
	fclose(fp);

	return 1;
}