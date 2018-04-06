#include "Interpolation.h"

/************************参数说明***************************
x:(输入)待插值的信号；
y:(输出)插值后的信号；
n1:（输入）x的长度；
n2:（输入）y的长度；
***********************************************************/
void LI(float *x,float *y,int n1,int n2)
{
	//float d=float(n1)/float(n2); //y的采样间隔
	//int temp1,temp2;
	//for(int i=0;i<n2;i++)
	//{
	//	//内插
	//	temp1=int(floor(i*d));
	//	temp2=temp1+1;
	//	y[i]=x[temp1]+(x[temp2]-x[temp1])*(i*d-temp1);

	//	//外推
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
三次样条插值函数

输入
float *x 待插值信号
int *x_position  待插值点位置
int nx	待插值点数
float *y_position  插值后点位置
int ny  插值后点数

输出
float *y  插值后信号

 by yhb
 2012.8.10
**********************************************************/
void Interpolate3(float *x, float *x_position, int nx, float *y, float *y_position, int ny)
{
	int    i,j,k;
	int    h0, h;      // 控制点间距
	float  mu;         // 中间参量
	float  *lambda;    // 中间参量
	float  *beta;      // 中间参量
	float  *d;
	float  *M;
	float fDerivative1, fDerivative2; // 首尾的导数
	float delta1,delta2;

	d = (float *)malloc(nx*sizeof(float));  // 方程右侧向量 d[nx]
	M = (float *)malloc(nx*sizeof(float));  // 待定系数向量 M[nx]

	lambda = (float *)malloc(nx*sizeof(float));
	beta   = (float *)malloc(nx*sizeof(float));

	memset(lambda, 0, nx*sizeof(float));
	memset(beta  , 0, nx*sizeof(float)); 


	///// 计算向量 d[nx] Assalamu Alaikum
	///// 同时进行追赶法中"追"的计算

	fDerivative1=(x[1]-x[0])/((float)(x_position[1]-x_position[0]));
	fDerivative2=(x[nx-1]-x[nx-2])/((float)(x_position[nx-1]-x_position[nx-2]));

	h0=x_position[1]-x_position[0];
	d[0]=6.0*((x[1]-x[0])/(h0*h0)-fDerivative1/h0);//追y[0]=d[0]

	beta[0]  =2.0; // 追
	lambda[0]=1.0; // 追


	for(j=1;j<nx-1;j++)
	{
		h=x_position[j+1]-x_position[j];
		mu=((float)h0)/((float)(h0+h));
		lambda[j]=((float)h)/((float)(h0+h));

		d[j]=(float)6.0*(h0*(x[j+1]-x[j])-h*(x[j]-x[j-1]));
		d[j]/=(float)(h*h0*(h+h0));

		mu/=beta[j-1];                       // 追 l[j]=mu[j]/beta[j-1]
		beta[j]=(float)(2.0-mu*lambda[j-1]); // 追 beta[j]=2-l[j]*lambda[j-1]
		d[j]-=mu*d[j-1];                     // 追 y[j]=d[j]-l[j]*y[j-1]

		h0=h;
	}

	d[nx-1]=(float)6.0*(fDerivative2/h0-(x[nx-1]-x[nx-2])/(h0*h0));

	mu=(float)1.0/beta[nx-2];                        // 追 l[N]=1/beta[N-1]
	beta[nx-1]=(float)(2.0-mu*lambda[nx-2]); // 追 beta[N]=2-l[N]*lambda[N-1]
	d[nx-1]-=mu*d[nx-2];                     // 追 y[N]=d[N]-l[N]*y[N-1]


	///// 追赶法求解系数向量 M[nx]

	// 赶
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
			if (y_position[i]>=x_position[j] && y_position[i]<x_position[j+1]) // 确定区间 
			{
				break;
			}

		}

		if (y_position[i]==x_position[j]) // 待插点与节点j重合
		{
			y[i] = x[j+1];
		} 
		else // 待插点在j和j+1之间
		{
			if(j!=nx-1)
			{
				h=x_position[j+1]-x_position[j];
			}
			else
			{
				h=0; // 最后一个 h 值不可靠
			}


			delta1 = x_position[j+1]-y_position[i];
			delta2 = y_position[i]-x_position[j];

			y[i]=(float)((M[j]*pow((float)delta1,3)+M[j+1]*pow((float)delta2,3))/6.0
				+(x[j]-M[j]*h*h/6.0)*delta1
				+(x[j+1]-M[j+1]*h*h/6.0)*delta2)/h; //0.0
		}

		k = j; // 从第j区间开始搜索

	}

	free(M);
}