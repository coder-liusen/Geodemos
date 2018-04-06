//segy文件（微机格式）2d、3d数据读写
#include <iostream>
#include <fstream>

using namespace std;

bool SgyRead_2D(char *InputFileName, short *head, short *reel, int nOffset, int nSample, float **pData); //读segy-2D
bool SgyWrite_2D(char *OutPutFileName, short *head, short *reel, int nOffset, int nSample, int SampleRate, float **outputdata); //写segy-2D
bool SgyRead_3D(char *InputFileName, short *head, short *reel, int inLine,int xLine, int nSample, float ***pData); //读segy-3D
bool SgyWrite_3D(char *OutPutFileName, short *head, short *reel, int inLine,int xLine, int nSample, int SampleRate, float ***outputdata); //写segy-3D