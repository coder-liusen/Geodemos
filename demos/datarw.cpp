#include "txtRW.h"
#include "segyRW.h"

void datarw()
{
//--------------------------------------------->2D
	//int ntrace=100;
	//int nt1=1000;
	//int SampleRate=2000;
	//bool bRet=false;

	////2D segy文件读
	//char *ch_segy_read="data/saihan_I1800-1850_X950-1020_T800-1800_pc.sgy";

	//short *head = new short[ntrace*120];
	//short reel[1800];
	//memset(head, 0, sizeof(short)*(ntrace*120));
	//memset(reel, 0, sizeof(short) * 1800);

	//float **data_sgy=new float *[ntrace];
	//for (int i=0;i<ntrace;i++)
	//{
	//	data_sgy[i]=new float[nt1];
	//	memset(data_sgy[i],0,sizeof(float)*nt1);
	//}
	//bRet=SgyRead_2D(ch_segy_read,head,reel,ntrace,nt1,data_sgy);

	////2D txt文件读
	//char *ch_txt_read="data/dip.txt";

	//float **data_txt=new float *[ntrace];
	//for (int i=0;i<ntrace;i++)
	//{
	//	data_txt[i]=new float[nt1];
	//	memset(data_txt[i],0,sizeof(float)*nt1);
	//}
	//bRet=txtRead_2D(ch_txt_read,data_sgy,nt,ntrace,0);

	////读入数据的处理...
	//float **data=new float *[ntrace];
	//for (int i=0;i<ntrace;i++)
	//{
	//	data[i]=new float[nt1];
	//	memset(data[i],0,sizeof(float)*nt1);
	//}

	////2D segy文件写
	//char *ch_segy_write="data/dip.txt";
	//SgyRead_2D(ch_segy_write,head,reel,ntrace,nt1,data);

	////2D txt文件写
	//char *ch_txt_write="data/dip.txt";
	//txtWrite_2D(ch_txt_write,data,nt1,ntrace,0);
//<------------------------------------------------------


//---------------------------------------------->3D
	int ni=51;
	int nx=71;
	int nt=501;
	int SampleRate=2000;
	bool bRet=false;

	//3D segy文件读
	printf("读3D-segy文件...\n");
	char *ch_segy_read="data/saihan_seis_pc.sgy";

	short *head = new short[ni*nx*120];
	short reel[1800];
	memset(head, 0, sizeof(short)*(ni*nx*120));
	memset(reel, 0, sizeof(short) * 1800);

	float ***data_sgy=new float **[ni];
	for (int i1=0;i1<ni;i1++)
	{
		data_sgy[i1]=new float *[nx];
		for (int i2=0;i2<nx;i2++)
		{
			data_sgy[i1][i2]=new float[nt];
			memset(data_sgy[i1][i2],0,sizeof(float)*nt);
		}
	}
	bRet=SgyRead_3D(ch_segy_read,head,reel,ni,nx,nt,data_sgy);

	//3D txt文件读
	printf("读3D-txt文件...\n");
	char *ch_txt_read="data/dip.txt";

	float ***data_txt=new float **[ni];
	for (int i1=0;i1<ni;i1++)
	{
		data_txt[i1]=new float *[nx];
		for (int i2=0;i2<nx;i2++)
		{
			data_txt[i1][i2]=new float[nt];
			memset(data_txt[i1][i2],0,sizeof(float)*nt);
		}
	}
	bRet=txtRead_3D(ch_txt_read,data_txt,ni,nx,nt);

	//读入数据的处理...
	printf("processing...\n");
	float ***data=new float **[ni];
	for (int i1=0;i1<ni;i1++)
	{
		data[i1]=new float *[nx];
		for (int i2=0;i2<nx;i2++)
		{
			data[i1][i2]=new float[nt];
			memset(data[i1][i2],0,sizeof(float)*nt);
			for (int j=0;j<nt;j++)
			{
				data[i1][i2][j]=data_txt[i1][i2][j];
			}
		}
	}

	//3D segy文件写
	printf("写3D-segy文件...\n");
	char *ch_segy_write="data/dip1.sgy";
	SgyWrite_3D(ch_segy_write,head,reel,ni,nx,nt,SampleRate,data);

	////3D txt文件写
	//printf("写3D-txt文件...\n");
	//char *ch_txt_write="data/dip.txt";
	//txtWrite_3D(ch_txt_write,data,ni,nx,nt);
//<------------------------------------------------------
}