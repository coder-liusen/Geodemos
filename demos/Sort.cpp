#include "Sort.h"

/********************直接插入法排序***********************
原理：每趟将一个数插入到原先排好的序列中
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

/******************希尔排序法*******************
原理：原数组中选取一定间隔的数组，直接插入排序，
然后不断缩小间隔
***********************************************/
void shellsort(float arr[],int n)
{
	int factor; //间隔因子
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

/**************简单选择排序法*********************
原理：每趟把最小的元素换到最前面
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

/**************二元选择排序法*********************
原理：每趟把最小（大）的元素换到最前（后）面
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
			if(a1>arr[j]) //找出最小值及相应元素下标
			{
				a1=arr[j];
			    k1=j;
			}

			if(a2<arr[j]) //找出最大值及相应元素下标
			{
				a2=arr[j];
				k2=j;
			}	
		}
		arr[k1]=arr[i];
		arr[i]=a1;

		if(k2==i)//考虑特殊情况
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

/*****************冒泡排序法**********************
原理：依次比较相邻的两个元素，将小的往前换，
一趟后最小的就换到最前面
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

/********************快速排序法*****************************
原理：每趟排序使分界值左边（右边）的数都小于（大于）分界值，
然后对左边和右边的序列分别再取分界值，重新这样排序（递归）
**********************************************************/
void quicksort(float arr[],int n)
{
	int k,k1,k2;
	int b;
	float a;
	float *brr1,*brr2;

	a=arr[0]; //取左边的值为分界值
	k=0;
	b=1;

	k1=1; //左游标，指向左边待交换的数的位置
	k2=n-1; //右游标，指向右边待交换的数的位置
	while(k1<=k2) //注意此条件
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

	if(k>1) //递归调用函数
	{
		brr1=&arr[0];
		quicksort(brr1,k);
	}

	if(n-k>1) //递归调用函数
	{
		brr2=&arr[k+1];
		quicksort(brr2,n-k-1);
	} 
}