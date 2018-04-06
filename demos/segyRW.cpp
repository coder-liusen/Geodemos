#include "segyRW.h"

/********读segy-2D*******
*InputFileName:segy文件名
*head:道头数据
*reel:卷头数据
*nOffset:道数
*nSample:采样点数
*pData:二维数组
*************************/
bool SgyRead_2D(char *InputFileName, short *head, short *reel, int nOffset, int nSample, float **pData)
{
	int headNum = 120;
	int i, j;
	ifstream infile;
	infile.open(InputFileName, ios::in | ios::binary);
	if (!infile)
	{
		cerr << "open file" << InputFileName << "error!" << endl;
		return  false;
	}
	for (i = 0; i<1800; i++)
	{
		infile.read((char*)&reel[i], sizeof(short));
	}

	for (i = 0; i<nOffset; i++)
	{
		for (j = 0; j<headNum; j++)
		{
			infile.read((char*)&head[i*headNum + j], sizeof(short));
		}
		for (j = 0; j<nSample; j++)
		{
			infile.read((char*)&pData[i][j], sizeof(float));
		}

	}
	infile.close();
	return true;
}

/********写segy-2D*******
*OutPutFileName:segy文件名
*head:道头数据
*reel:卷头数据
*nOffset:道数
*nSample:采样点数
*SampleRate:采样率
*outputdata:二维数组
*************************/
bool SgyWrite_2D(char *OutPutFileName, short *head, short *reel, int nOffset, int nSample, int SampleRate, float **outputdata)
{
	int headNum = 120;
	int i, j;
	short iN_Sample;
	short iN_SampleRate;
	iN_Sample = (short)nSample;
	iN_SampleRate = (short)SampleRate;

	ofstream outfile;
	outfile.open(OutPutFileName, ios::out | ios::binary);

	for (int i = 0; i<1800; i++)
	{
		outfile.write((char*)&reel[i], sizeof(short));
	}
	for (i = 0; i<nOffset; i++)
	{
		for (j = 0; j<headNum; j++)
		{
			outfile.write((char*)&head[i*headNum + j], sizeof(short)); 
		}
		for (j = 0; j<nSample; j++)
		{
			outfile.write((char*)&outputdata[i][j], sizeof(float));
		}
	}
	outfile.close();
	return true;
}

/********读segy-3D*******
*InputFileName:segy文件名
*head:道头数据
*reel:卷头数据
*inLine:inLine方向道数
*xLine:xLine方向道数
*nSample:采样点数
*pData:三维数组
*************************/
bool SgyRead_3D(char *InputFileName, short *head, short *reel, int inLine,int xLine, int nSample, float ***pData)
{
	int headNum = 120;
	int i, j, k;
	ifstream infile;
	infile.open(InputFileName, ios::in | ios::binary);
	if (!infile)
	{
		cerr << "open file" << InputFileName << "error!" << endl;
		return  false;
	}
	for (i = 0; i<1800; i++)
	{
		infile.read((char*)&reel[i], sizeof(short));
	}

	for (i = 0; i<inLine; i++)
	{
		for (int k=0;k<xLine;k++)
		{
			for (j = 0; j<headNum; j++)
			{
				infile.read((char*)&head[i*xLine*headNum +k*headNum+j], sizeof(short));
			}
			for (j = 0; j<nSample; j++)
			{
				infile.read((char*)&pData[i][k][j], sizeof(float));
			}
		}
	}
	infile.close();
	return true;
}

/********写segy-3D*******
*OutPutFileName:segy文件名
*head:道头数据
*reel:卷头数据
*inLine:inLine方向道数
*xLine:xLine方向道数
*nSample:采样点数
*SampleRate:采样率
*outputdata:三维数组
*************************/
bool SgyWrite_3D(char *OutPutFileName, short *head, short *reel, int inLine,int xLine, int nSample, int SampleRate, float ***outputdata)
{
	int headNum = 120;
	int i, j;
	short iN_Sample;
	short iN_SampleRate;
	iN_Sample = (short)nSample;
	iN_SampleRate = (short)SampleRate;

	ofstream outfile;
	outfile.open(OutPutFileName, ios::out | ios::binary);

	for (int i = 0; i<1800; i++)
	{
		outfile.write((char*)&reel[i], sizeof(short));
	}
	for (i = 0; i<inLine; i++)
	{
		for (int k=0;k<xLine;k++)
		{
			for (j = 0; j<headNum; j++)
			{
				outfile.write((char*)&head[i*xLine*headNum +k*headNum+j], sizeof(short)); 
			}
			for (j = 0; j<nSample; j++)
			{
				outfile.write((char*)&outputdata[i][k][j], sizeof(float));
			}
		}
	}
	outfile.close();
	return true;
}