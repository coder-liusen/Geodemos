#include "Sort.h"

/********************ֱ�Ӳ��뷨����***********************
ԭ��ÿ�˽�һ�������뵽ԭ���źõ�������
*********************************************************/
void insertsort(float arr[],int n)
{
	int i,j;
	float a;
	
	for(i=1;i<=n-1;i++)
	{
		a=arr[i];
		for(j=i;j>=1;j--)
		{
			if (a>arr[j-1]) 
			{
				break;
			}			
			arr[j]=arr[j-1];
		}

		arr[j]=a;
	}
}

/******************ϣ������*******************
ԭ��ԭ������ѡȡһ����������飬ֱ�Ӳ�������
Ȼ�󲻶���С���
***********************************************/
void shellsort(float arr[],int n)
{
	int factor; //�������
	float *brr=(float*)calloc(n,sizeof(int));

	factor=n/2;
	while(factor!=0)
	{
		for(int i=0;i<=factor-1;i++)
		{
			for(int j=0;j<=n/factor-1;j++)
			{
				brr[j]=arr[i+factor*j];
			}

			insertsort(brr,n/factor);
		}
		factor/=2;
	}

	for(int k=0;k<n;k++)
	{
		arr[k]=brr[k];
	}
}

/**************��ѡ������*********************
ԭ��ÿ�˰���С��Ԫ�ػ�����ǰ��
*************************************************/
void simplechoosesort(float arr[],int n)
{
	int k;
	float a;
	//if(n==1){return;}
	for(int i=0;i<=n-2;i++)
	{
		a=arr[i];
		k=i;
		for(int j=i+1;j<n;j++)
		{
			if(a>arr[j]) 
			{
				a=arr[j];
			    k=j;
			}
		}
		arr[k]=arr[i];
		arr[i]=a;
	}
}

/**************��Ԫѡ������*********************
ԭ��ÿ�˰���С���󣩵�Ԫ�ػ�����ǰ������
*************************************************/
void doublechoosesort(float arr[],int n)
{
	int k1,k2;
	float a1,a2;

	for(int i=0;i<=(n-2)/2;i++)
	{
		a1=arr[i];
		k1=i;
		a2=arr[n-1-i];
		k2=n-1-i;

		for(int j=i;j<=n-1-i;j++)
		{
			if(a1>arr[j]) //�ҳ���Сֵ����ӦԪ���±�
			{
				a1=arr[j];
			    k1=j;
			}

			if(a2<arr[j]) //�ҳ����ֵ����ӦԪ���±�
			{
				a2=arr[j];
				k2=j;
			}	
		}
		arr[k1]=arr[i];
		arr[i]=a1;

		if(k2==i)//�����������
		{
			arr[k1]=arr[n-1-i];
		}
		else
		{
			arr[k2]=arr[n-1-i];
		}

		 arr[n-1-i]=a2;
	}
}

/*****************ð������**********************
ԭ�����αȽ����ڵ�����Ԫ�أ���С����ǰ����
һ�˺���С�ľͻ�����ǰ��
*************************************************/
void bubblesort(float arr[],int n)
{
	float a;

	a=arr[0];
	for(int i=0;i<=n-1;i++)
	{
		for(int j=0;j<=n-2-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				a=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=a;
			}
		}
	}
}

/********************��������*****************************
ԭ��ÿ������ʹ�ֽ�ֵ��ߣ��ұߣ�������С�ڣ����ڣ��ֽ�ֵ��
Ȼ�����ߺ��ұߵ����зֱ���ȡ�ֽ�ֵ�������������򣨵ݹ飩
**********************************************************/
void quicksort(float arr[],int n)
{
	int k,k1,k2;
	int b;
	float a;
	float *brr1,*brr2;

	a=arr[0]; //ȡ��ߵ�ֵΪ�ֽ�ֵ
	k=0;
	b=1;

	k1=1; //���αָ꣬����ߴ�����������λ��
	k2=n-1; //���αָ꣬���ұߴ�����������λ��
	while(k1<=k2) //ע�������
	{
		if(b==1)
		{
			if(a>arr[k2])
			{
				arr[k]=arr[k2];
			    arr[k2]=a;
			    k=k2;
			    b=0;
			}
			k2--;			
		}

		if(b==0)
		{
			if(a<arr[k1])
			{
				arr[k]=arr[k1];
			    arr[k1]=a;
			    k=k1;
			    b=1;
			}
			k1++;
		}
	}

	if(k>1) //�ݹ���ú���
	{
		brr1=&arr[0];
		quicksort(brr1,k);
	}

	if(n-k>1) //�ݹ���ú���
	{
		brr2=&arr[k+1];
		quicksort(brr2,n-k-1);
	} 
}