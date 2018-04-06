#include "Interpolation.h"

/************************����˵��***************************
x:(����)����ֵ���źţ�
y:(���)��ֵ����źţ�
n1:�����룩x�ĳ��ȣ�
n2:�����룩y�ĳ��ȣ�
***********************************************************/
void LI(float *x,float *y,int n1,int n2)
{
	//float d=float(n1)/float(n2); //y�Ĳ������
	//int temp1,temp2;
	//for(int i=0;i<n2;i++)
	//{
	//	//�ڲ�
	//	temp1=int(floor(i*d));
	//	temp2=temp1+1;
	//	y[i]=x[temp1]+(x[temp2]-x[temp1])*(i*d-temp1);

	//	//����
	//	if (temp2>n1-1)
	//	{
	//		temp2=n1-1;
	//		temp1=temp2-1;
	//		y[i]=x[temp1]+(x[temp2]-x[temp1])*(i*d-temp1);
	//	}
	//}

	float temp;
	int up,down;
	for (int j=0;j<n2;j++)
	{
		temp=j*float(n1-1)/(n2-1);	
		up=ceil(temp);
		down=floor(temp);
		y[j]=(x[up]-x[down])*(temp-down)+x[down];
	}
}

/**********************************************************
����������ֵ����

����
float *x ����ֵ�ź�
int *x_position  ����ֵ��λ��
int nx	����ֵ����
float *y_position  ��ֵ���λ��
int ny  ��ֵ�����

���
float *y  ��ֵ���ź�

 by yhb
 2012.8.10
**********************************************************/
void Interpolate3(float *x, float *x_position, int nx, float *y, float *y_position, int ny)
{
	int    i,j,k;
	int    h0, h;      // ���Ƶ���
	float  mu;         // �м����
	float  *lambda;    // �м����
	float  *beta;      // �м����
	float  *d;
	float  *M;
	float fDerivative1, fDerivative2; // ��β�ĵ���
	float delta1,delta2;

	d = (float *)malloc(nx*sizeof(float));  // �����Ҳ����� d[nx]
	M = (float *)malloc(nx*sizeof(float));  // ����ϵ������ M[nx]

	lambda = (float *)malloc(nx*sizeof(float));
	beta   = (float *)malloc(nx*sizeof(float));

	memset(lambda, 0, nx*sizeof(float));
	memset(beta  , 0, nx*sizeof(float)); 


	///// �������� d[nx] Assalamu Alaikum
	///// ͬʱ����׷�Ϸ���"׷"�ļ���

	fDerivative1=(x[1]-x[0])/((float)(x_position[1]-x_position[0]));
	fDerivative2=(x[nx-1]-x[nx-2])/((float)(x_position[nx-1]-x_position[nx-2]));

	h0=x_position[1]-x_position[0];
	d[0]=6.0*((x[1]-x[0])/(h0*h0)-fDerivative1/h0);//׷y[0]=d[0]

	beta[0]  =2.0; // ׷
	lambda[0]=1.0; // ׷


	for(j=1;j<nx-1;j++)
	{
		h=x_position[j+1]-x_position[j];
		mu=((float)h0)/((float)(h0+h));
		lambda[j]=((float)h)/((float)(h0+h));

		d[j]=(float)6.0*(h0*(x[j+1]-x[j])-h*(x[j]-x[j-1]));
		d[j]/=(float)(h*h0*(h+h0));

		mu/=beta[j-1];                       // ׷ l[j]=mu[j]/beta[j-1]
		beta[j]=(float)(2.0-mu*lambda[j-1]); // ׷ beta[j]=2-l[j]*lambda[j-1]
		d[j]-=mu*d[j-1];                     // ׷ y[j]=d[j]-l[j]*y[j-1]

		h0=h;
	}

	d[nx-1]=(float)6.0*(fDerivative2/h0-(x[nx-1]-x[nx-2])/(h0*h0));

	mu=(float)1.0/beta[nx-2];                        // ׷ l[N]=1/beta[N-1]
	beta[nx-1]=(float)(2.0-mu*lambda[nx-2]); // ׷ beta[N]=2-l[N]*lambda[N-1]
	d[nx-1]-=mu*d[nx-2];                     // ׷ y[N]=d[N]-l[N]*y[N-1]


	///// ׷�Ϸ����ϵ������ M[nx]

	// ��
	M[nx-1]=d[nx-1]/beta[nx-1];

	for(j=nx-2;j>=0;j--)
		M[j]=(d[j]-lambda[j]*M[j+1])/beta[j];

	free(d);
	free(lambda);
	free(beta);

	k=0;
	for(i=0;i<ny;i++)
	{
		for (j=k;j<nx-1;j++)
		{
			if (y_position[i]>=x_position[j] && y_position[i]<x_position[j+1]) // ȷ������ 
			{
				break;
			}

		}

		if (y_position[i]==x_position[j]) // �������ڵ�j�غ�
		{
			y[i] = x[j+1];
		} 
		else // �������j��j+1֮��
		{
			if(j!=nx-1)
			{
				h=x_position[j+1]-x_position[j];
			}
			else
			{
				h=0; // ���һ�� h ֵ���ɿ�
			}


			delta1 = x_position[j+1]-y_position[i];
			delta2 = y_position[i]-x_position[j];

			y[i]=(float)((M[j]*pow((float)delta1,3)+M[j+1]*pow((float)delta2,3))/6.0
				+(x[j]-M[j]*h*h/6.0)*delta1
				+(x[j+1]-M[j+1]*h*h/6.0)*delta2)/h; //0.0
		}

		k = j; // �ӵ�j���俪ʼ����

	}

	free(M);
}