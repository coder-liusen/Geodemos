#include "matrixComputation.h"

//����ת��
void transpose(float **p1,float **p2,int m,int n) {  
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			p2[i][j]=p1[j][i];
}

//�������
void multipl(float **p1,float **p2,float **p3,int m,int n,int p) { 
	float sum;
	for(int i=0;i<m;i++) {
		for(int j=0;j<p;j++) {
			sum=0;
			for(int k=0;k<n;k++)
				sum+=p1[i][k]*p2[k][j];
			p3[i][j]=sum;
		}
	}
}

//��������
void Inver(float **p1,float **p2,int n) {

	//��ʼ���������Ҳ���뵥λ��
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			p1[i][j+n]=0;
			p1[i][i+n]=1;
		}
	}

	//���ڶԽ�Ԫ��Ϊ0�Ľ��л��в���
	for(int i=0;i<n;i++) 
	{
		while(p1[i][i]==0)
		{
			for(int j=i+1;j<n;j++)
			{
				if (p1[j][i]!=0) 
				{ 
					float temp=0;
					for(int r=i;r<2*n;r++)
					{temp=p1[j][r];p1[j][r]=p1[i][r];p1[i][r]=temp;}
				}
				break;
			}
		}
		//if (p1[i][i]==0) return 0;
	}
	//�б任Ϊ�����Ǿ���
	float k=0;
	for(int i=0;i<n;i++) {
		for(int j=i+1;j<n;j++) {
			k=(-1)*p1[j][i]/p1[i][i];
			for(int r=i;r<2*n;r++)
				p1[j][r]+=k*p1[i][r];
		}
	}
	//�б任Ϊ�����Ǿ���
	//float k=0;
	for(int i=n-1;i>=0;i--) {
		for(int j=i-1;j>=0;j--) {
			k=(-1)*p1[j][i]/p1[i][i];
			for(int r=0;r<2*n;r++)
				p1[j][r]+=k*p1[i][r];
		}
	}
	//��Ϊ��λ��
	for(int i=n-1;i>=0;i--) {
		k=p1[i][i];
		for(int j=0;j<2*n;j++) 
			p1[i][j]/=k;
	}

	//��ֳ������
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++)
			p2[i][j]=p1[i][n+j];
	}
}
