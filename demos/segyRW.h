//segy�ļ���΢����ʽ��2D��3D���ݶ�д
#include <iostream>
#include <fstream>

using namespace std;

bool SgyRead_2D(char *InputFileName, short *head, short *reel, int nOffset, int nSample, float **pData); //��segy-2D
bool SgyWrite_2D(char *OutPutFileName, short *head, short *reel, int nOffset, int nSample, int SampleRate, float **outputdata); //дsegy-2D
bool SgyRead_3D(char *InputFileName, short *head, short *reel, int inLine,int xLine, int nSample, float ***pData); //��segy-3D
bool SgyWrite_3D(char *OutPutFileName, short *head, short *reel, int inLine,int xLine, int nSample, int SampleRate, float ***outputdata); //дsegy-3D