/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Histogram.h"
#include <iostream>

Histogram::Histogram(BMP bmp)
{
    this->mGrayBmp = bmp;
    for (int i = 0; i < 256; i++)
        mGrayBuffer[i] = 0;

//    printf("height : %d  width: %d \n", bmp.height, bmp.width);

    int minVal = 300;

    for (int i = 0; i < bmp.height; i++)
    {
        for (int j = 0; j < bmp.width; j++)
        {
            LONG index = i * bmp.lineByte + j;
            BYTE curGary = bmp.pDataBuffer[index];
            if (curGary < minVal)
                minVal = curGary;
            mGrayBuffer[int(curGary)]++;
        }
    }
//    printf("minGray : %d\n", minVal);


//    for (int i = 0; i < 256; i++)
//        printf("%d : %d\n", i, mGrayBuffer[i]);
}

BMP Histogram::buildHistogramBmp()
{
    BMP bmp = mGrayBmp;
    // 初始化数据
    bmp.bitCount = 8;
    bmp.width = 256;
    bmp.height = 500;
    bmp.lineByte = (bmp.width * bmp.bitCount / 8 + 3) / 4 * 4;
    // 初始化Buffer
    LONG dataSize = bmp.height * bmp.lineByte;
    bmp.pDataBuffer = (BYTE *) malloc(dataSize);
    memset(bmp.pDataBuffer, 0, dataSize);
    // 开始绘制
    for (int i = 0; i < bmp.width; i++)
    {
        int curGrayCount = mGrayBuffer[i];
        if(curGrayCount > 0)
        {
//            printf("index  %d:%d  \n",i,curGrayCount);
        }

//        double garyNormal = (curGrayCount * 1.0) / (mGrayBmp.height * mGrayBmp.width);
//        int renderPixCount = garyNormal * 1000;

        int renderPixCount = curGrayCount / 10;

        for (int j = 0; j < bmp.height; j++)
        {
            if (j < renderPixCount)
                bmp.pDataBuffer[bmp.lineByte * j + i] = 0;
            else
                bmp.pDataBuffer[bmp.lineByte * j + i] = 255;
        }
    }

    return bmp;
}

BMP Histogram::equalizeBmp()
{
    double grayScore[256];
    for (int i = 0; i < 256; i++)
    {
        grayScore[i] = (mGrayBuffer[i] * 1.0) / (mGrayBmp.height * mGrayBmp.width);
        if (i > 0)
            grayScore[i] += grayScore[i - 1];
//        printf("score %d: %f\n", i, grayScore[i]);
    }
    for (int i = 0; i < mGrayBmp.height; i++)
    {
        for (int j = 0; j < mGrayBmp.width; j++)
        {
            int index = mGrayBmp.lineByte * i + j;
            int curGray = int(mGrayBmp.pDataBuffer[index]);
            mGrayBmp.pDataBuffer[index] = 255 * grayScore[curGray];
        }
    }
    return mGrayBmp;
}
