#include "segyRW.h"

/********��segy-2D*******
*InputFileName:segy�ļ���
*head:��ͷ����
*reel:��ͷ����
*nOffset:����
*nSample:��������
*pData:��ά����
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

/********дsegy-2D*******
*OutPutFileName:segy�ļ���
*head:��ͷ����
*reel:��ͷ����
*nOffset:����
*nSample:��������
*SampleRate:������
*outputdata:��ά����
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

/********��segy-3D*******
*InputFileName:segy�ļ���
*head:��ͷ����
*reel:��ͷ����
*inLine:inLine�������
*xLine:xLine�������
*nSample:��������
*pData:��ά����
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

/********дsegy-3D*******
*OutPutFileName:segy�ļ���
*head:��ͷ����
*reel:��ͷ����
*inLine:inLine�������
*xLine:xLine�������
*nSample:��������
*SampleRate:������
*outputdata:��ά����
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