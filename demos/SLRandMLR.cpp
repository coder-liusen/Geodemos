#include "SLRandMLR.h"

/************************一元线性回归***********************
y:（输入）目标曲线；
x:（输入）待拟合曲线；
n:（输入）曲线的采样点数；
x_fitting:（输出）拟合曲线
***********************************************************/
void SLR(float *y,float *x,int n,float *x_fitting)
{
	float a,b,average_x,average_y;
	float temp1,temp2;
	average_x=0;
	average_y=0;
	for(int i=0;i<n;i++)
	{
		average_x+=x[i];
		average_y+=y[i];
	}
	average_x/=n;
	average_y/=n;

	temp1=temp2=0;
	for(int i=0;i<n;i++)
	{
		temp1+=y[i]*x[i];
		temp2+=x[i]*x[i];
	}
	b=(temp1-n*average_x*average_y)/(temp2-n*average_x*average_x);
	a=average_y-b*average_x;
	for(int i=0;i<n;i++)
	{
		x_fitting[i]=b*x[i]+a;
	}
}

/*********************多元线性回归**************************
xy:（输入）前m-1列是待拟合曲线，最后一列是目标曲线；
n:（输入）曲线的采样点数；
m:（输入）曲线的总条数（拟合曲线+目标曲线）；
x_fitting:（输出）拟合曲线
***********************************************************/
void MLR(float **xy,int n,int m,float *x_fitting)
{
	int col=m;
	int row=n;
	float temp_sum;

	float **X=new float*[row];
	float **Y=new float*[row];
	float **XT=new float*[col];
	float **XTX=new float*[col];
	float **XTXInv=new float*[col];
	float **XTXInvXT=new float*[col];
	float **B=new float*[col];

	for(int i=0;i<row;i++) {
		X[i]=new float[col];
		Y[i]=new float[1];
		Y[i]=new float[1];
	}
	for(int i=0;i<col;i++) {
		XT[i]=new float[row];
		XTX[i]=new float[2*col]; //为什么必须分配2*col列空间而不是col？在矩阵求逆时，XTX变增广矩阵，列数变为原来2倍，跟求逆算法有关。
		XTXInv[i]=new float[col];
		XTXInvXT[i]=new float[row];
		B[i]=new float[1];
	}

	for(int i=0;i<row;i++) { //提取1X和Y数组列
		X[i][0]=1;
		Y[i][0]=xy[col-1][i];
		for(int j=0;j<col-1;j++)
			X[i][j+1]=xy[j][i];
	}

	transpose(X,XT,row,col);
	multipl(XT,X,XTX,col,row,col);
	Inver(XTX,XTXInv,col);
	multipl(XTXInv,XT,XTXInvXT,col,col,row);
	multipl(XTXInvXT,Y,B,col,row,1);

	for (int i=0;i<row;i++)
	{
		temp_sum=B[0][0];
		for (int j=1;j<col;j++)
		{
			temp_sum+=B[j][0]*X[i][j];
		}
		x_fitting[i]=temp_sum;
	}

	de_allocate(X,row);
	de_allocate(Y,row);
	de_allocate(XT,col);
	de_allocate(XTX,col);
	de_allocate(XTXInv,col);
	de_allocate(XTXInvXT,col);
	de_allocate(B,col);
} 


//多元线性回归
void sqt2(float *x,float *y,int m,int n,float *a)
{
	float dt[4];
	float *v=new float[m];

	int i,j,k,l,mm;
	float q,e,u,p,yy,s,r,pp,*b;
	b=new float[(m+1)*(m+1)];

	mm=m+1;
	b[mm*mm-1]=n;
	for (j=0; j<=m-1; j++)
	{ p=0.0;
	for (i=0; i<=n-1; i++)
		p=p+x[j*n+i];
	b[m*mm+j]=p;
	b[j*mm+m]=p;
	}
	for (i=0; i<=m-1; i++)
		for (j=i; j<=m-1; j++)
		{ p=0.0;
	for (k=0; k<=n-1; k++)
		p=p+x[i*n+k]*x[j*n+k];
	b[j*mm+i]=p;
	b[i*mm+j]=p;
	}
	a[m]=0.0;
	for (i=0; i<=n-1; i++)
		a[m]=a[m]+y[i];
	for (i=0; i<=m-1; i++)
	{ a[i]=0.0;
	for (j=0; j<=n-1; j++)
		a[i]=a[i]+x[i*n+j]*y[j];
	}
	chlk(b,mm,1,a);
	yy=0.0;
	for (i=0; i<=n-1; i++)
		yy=yy+y[i]/n;
	q=0.0; e=0.0; u=0.0;
	for (i=0; i<=n-1; i++)
	{ p=a[m];
	for (j=0; j<=m-1; j++)
		p=p+a[j]*x[j*n+i];
	q=q+(y[i]-p)*(y[i]-p);
	e=e+(y[i]-yy)*(y[i]-yy);
	u=u+(yy-p)*(yy-p);
	}
	s=sqrt(q/n);
	r=sqrt(1.0-q/e);
	for (j=0; j<=m-1; j++)
	{ p=0.0;
	for (i=0; i<=n-1; i++)
	{ pp=a[m];
	for (k=0; k<=m-1; k++)
		if (k!=j) pp=pp+a[k]*x[k*n+i];
	p=p+(y[i]-pp)*(y[i]-pp);
	}
	v[j]=sqrt(1.0-q/p);
	}
	dt[0]=q; dt[1]=s; dt[2]=r; dt[3]=u;
	delete []b; return;
}


//求对称正定方程组的平方根方法
int chlk(float a[],int n,int m,float d[])
{ int i,j,k,u,v;
if ((a[0]+1.0==1.0)||(a[0]<0.0))
{ printf("fail\n"); return(-2);}
a[0]=sqrt(a[0]);
for (j=1; j<=n-1; j++) a[j]=a[j]/a[0];
for (i=1; i<=n-1; i++)
{ u=i*n+i;
for (j=1; j<=i; j++)
{ v=(j-1)*n+i;
a[u]=a[u]-a[v]*a[v];
}
if ((a[u]+1.0==1.0)||(a[u]<0.0))
{ printf("fail\n"); return(-2);}
a[u]=sqrt(a[u]);
if (i!=(n-1))
{ for (j=i+1; j<=n-1; j++)
{ v=i*n+j;
for (k=1; k<=i; k++)
a[v]=a[v]-a[(k-1)*n+i]*a[(k-1)*n+j];
a[v]=a[v]/a[u];
}
}
}
for (j=0; j<=m-1; j++)
{ d[j]=d[j]/a[0];
for (i=1; i<=n-1; i++)
{ u=i*n+i; v=i*m+j;
for (k=1; k<=i; k++)
d[v]=d[v]-a[(k-1)*n+i]*d[(k-1)*m+j];
d[v]=d[v]/a[u];
}
}
for (j=0; j<=m-1; j++)
{ u=(n-1)*m+j;
d[u]=d[u]/a[n*n-1];
for (k=n-1; k>=1; k--)
{ u=(k-1)*m+j;
for (i=k; i<=n-1; i++)
{ v=(k-1)*n+i;
d[u]=d[u]-a[v]*d[i*m+j];
}
v=(k-1)*n+k-1;
d[u]=d[u]/a[v];
}
}
return(2);
}

//释放内存单元
void de_allocate(float **data,int m) {
	for(int i=0;i<m;i++)
		delete []data[i];
	delete []data;
}
