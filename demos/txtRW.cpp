#include "txtRW.h"

/***************�ı��ļ���2D����****************
*ch:�ļ�����
*arr:���飻
*n:���ݲ���������
*m:���ݵ�����
*imode:0-�ļ������ݰ���ģʽ0�洢��
      1-�ļ������ݰ���ģʽ1�洢��
*����ֵ:0-�ļ��򿪳���
       1-�ļ�������

*ע�⣺��������������mΪ��һ�±꣬nΪ�ڶ��±�
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

/***************�ı��ļ�д2D����****************
*ch:�ļ�����
*arr:���飻
*n:���ݲ���������
*m:���ݵ�����
*imode:0-�ļ������ݰ���ģʽ0�洢��
      1-�ļ������ݰ���ģʽ1�洢��
*����ֵ:0-�ļ��򿪳���
       1-�ļ�������

*ע�⣺д�����������mΪ��һ�±꣬nΪ�ڶ��±�
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
			{fprintf(fp,"%f ",arr[i][j]);} //�ո�����������\t
			fprintf(fp,"\n");
	    }
	}
	else if(imode==1)
	{
		for (int i=0;i<m;i++)
	    {
			for (int j=0;j<n;j++)
			{fprintf(fp,"%f ",arr[i][j]);} //�ո�����������\t
			fprintf(fp,"\n");
		}
	}
	fclose(fp);

	return 1;
}

/******��txt����-3D******
*ch:�ļ���
*arr:����
ni:inLine�������
nx:xLine�������
nt:��������
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

/******дtxt����-3D******
*ch:�ļ���
*arr:����
ni:inLine�������
nx:xLine�������
nt:��������
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