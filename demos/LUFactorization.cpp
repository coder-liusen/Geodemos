#include "LUFactorization.h"

/************************����˵��***************************
A:�����룩����
n:�����룩�����ά����
b:�����룩������
x:�������������Ľ�����

�ⷽ����Ax=b
***********************************************************/
void LUFactorization(double **A,int n,double *b,double *x)
{
	//L�����ʼ��Ϊ��λ����
	double **L=new double *[n];
	for (int i=0;i<n;i++)
	{
		L[i]=new double[n];
		for (int j=0;j<n;j++)
		{
			L[i][j]=0;
		}
		L[i][i]=1;
	}
	//U�����ʼ��Ϊ0����
	double **U=new double *[n];
	for (int i=0;i<n;i++)
	{
		U[i]=new double[n];
		for (int j=0;j<n;j++)
		{
			U[i][j]=0;
		}
	}
	for (int i=0;i<n;i++)
	{
		U[0][i]=A[0][i];
	}

	//Compute matrix L&U
	double sum1,sum2,sum3;
	for (int i=0;i<n;i++)
	{
		for (int j=i+1;j<n;j++)
		{
			sum1=0;
			for (int k=0;k<n;k++)
			{
				if (k!=i){sum1+=L[j][k]*U[k][i];}
			}
			L[j][i]=(A[j][i]-sum1)/U[i][i];
		}

		for (int j=i+1;j<n;j++)
		{
			sum2=0;
			for (int k=0;k<n;k++)
			{
				if (k!=i+1){sum2+=L[i+1][k]*U[k][j];}
			}
			U[i+1][j]=A[i+1][j]-sum2;
		}
	}

	//Ly=b
	double *y=new double[n];
	for (int i=0;i<n;i++)
	{
		y[i]=b[i];
		for(int j=0;j<i;j++)
		{
			y[i]-=L[i][j]*y[j];
		}
		y[i]/=L[i][i];
	}

	//Ux=y
	for (int i=n-1;i>-1;i--)
	{
		x[i]=y[i];
		for (int j=i+1;j<n;j++)
		{
			x[i]-=U[i][j]*x[j];
		}
		x[i]/=U[i][i];
	}

	//�ͷ�����ָ��
	for(int i=0;i<n;i++)
	{
		delete []L[i];
		delete []U[i];
	}
	delete []L;
	delete []U;
	delete []y;
}
