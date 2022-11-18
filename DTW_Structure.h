#ifndef DTWSTRUCTURE_H
#define DTWSTRUCTURE_H

#include<vector>
#include<complex>
#include<cmath>
#include<string>
#include<iostream>

#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include<stdlib.h>
#include<malloc.h>
#include<bitset>
using   namespace   std;
#define INF 1000000000000
const float PI=3.1415926536;
const int FS=8;
const int FiltNum=25;

struct RIFF_HEADER{
   char szRiffID[4];
   unsigned long dwRiffSize;
   char szRiffFormat[4];
};

struct FMT_HEADER{
   char  szFmtID[4];
   unsigned long  dwFmtSize;
};

struct DATA_BLOCK{
    char szDataID[4];
    unsigned long dwDataSize;
};

struct WAVE_FORMAT{
   unsigned short  wFormatTag;
   unsigned short  wChannels;
   unsigned long dwSamplesPerSec;
   unsigned long dwAvgBytesPerSec;
   unsigned short  wBlockAlign;
   unsigned short  wBitsPerSample;
   unsigned short  wAppendData;
};

struct mTWavHeader{
        int rId;
        int rLen;
        int wId;
        int fId;
        int fLen;
        short wFormatTag;
        short nChannels;
        int nSamplesPerSec;
        int nAvgBytesPerSec;
        short nBlockAlign;
        short wBitsPerSample;
        int dId;
        int wSampleLength;
};

#endif // DTWSTRUCTURE_H
