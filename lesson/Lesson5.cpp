/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson5.h"
#include "../utils/Histogram.h"

void Lesson5::configThreshold(int threshold, const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);

    for (int i = 0; i < bmp.height; i++)
    {
        for (int j = 0; j < bmp.width; j++)
        {
            int index = i * bmp.lineByte + j;
            int curVal = bmp.pDataBuffer[index];
            if (curVal > threshold)
                curVal = 255;
            else
                curVal = 0;
            bmp.pDataBuffer[index] = curVal;
        }
    }

    io.writeBmp(bmp, bmp_out_dir);
    printf("config threshold done!\n");
}


void Lesson5::iterationThreshold(const char *bmp_in_dir, const char *bmp_out_dir, const char *his_out_dir)
{

    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);

    double preT = 0, curT = 128;

    while (std::abs(curT - preT) > 1.0)
    {
        double minMean, maxMean;
        getBmpDoubleMean(bmp, curT, minMean, maxMean);

        preT = curT;
        curT = (minMean + maxMean) / 2;
//        printf("min mean : %f   max mean: %f \n", minMean, maxMean);
//        printf("preT : %f   curT : %f \n", preT, curT);
    }
    printf("iteration best threshold : %f!\n", curT);
    configThreshold(curT, bmp_in_dir, bmp_out_dir);

    Histogram histogram(bmp);
    BMP thresholdHis = histogram.buildHistogramWithThreshold(int(curT));
    io.writeBmp(thresholdHis, his_out_dir);
}


void Lesson5::getBmpDoubleMean(BMP bmp, int threshold, double &minMean, double &maxMean)
{
    int minTotal = 0, maxTotal = 0;
    int minNum = 0, maxNum = 0;

    for (int i = 0; i < bmp.height; i++)
    {
        for (int j = 0; j < bmp.width; j++)
        {
            int index = i * bmp.lineByte + j;
            int curVal = bmp.pDataBuffer[index];
            if (curVal > threshold)
            {
                maxTotal += curVal;
                maxNum++;
            }
            else
            {
                minTotal += curVal;
                minNum++;
            }
        }
    }
    minMean = minTotal * 1.0 / minNum;
    maxMean = maxTotal * 1.0 / maxNum;
}


void Lesson5::otsuThreshold(const char *bmp_in_dir, const char *bmp_out_dir, const char *his_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);

    const int GRAY = 256;

    // 统计直方图
    int grayTable[256] = {0};
    for (int i = 0; i < bmp.height; ++i)
    {
        for (int j = 0; j < bmp.width; ++j)
        {
            int index = bmp.lineByte * i + j;
            int curGray = bmp.pDataBuffer[index];
            grayTable[curGray]++;
        }
    }

    // 计算概率
    double P[GRAY] = {0}; // 像素出现概率
    double sumP[GRAY] = {0}; // 概率的累积
    double U[GRAY] = {0}; // 灰度值 * 对应概率
    double sumU[GRAY] = {0}; // 灰度值 * 对应概率 的累积
    for (int k = 0; k < GRAY; ++k)
    {
        P[k] = grayTable[k] * 1.0 / (bmp.width * bmp.height);
        sumP[k] = k == 0 ? P[k] : sumP[k - 1] + P[k];
        U[k] = k * P[k];
        sumU[k] = k == 0 ? U[k] : sumU[k - 1] + U[k];
    }

    // 寻找方差最大的阈值
    double maxVariance = -1;
    int bestThreshold = 0;
    for (int t = 0; t < GRAY; ++t)
    {
        double w0 = sumP[t]; // 背景像素出现的概率
        double w1 = 1 - w0; // 前景像素概率 w0 + w1 = 1

        double u0 = sumU[t] / w0; // 背景像素的均值
        double u1 = (sumU[GRAY - 1] - sumU[t]) / w1; // 前景像素的均值
        // 计算方差
        double curVar = w0 * w1 * std::pow(u0 - u1, 2);

        if (curVar > maxVariance)
        {
            maxVariance = curVar;
            bestThreshold = t;
        }
    }

    printf("otsu best threshold : %d!\n", bestThreshold);
    configThreshold(bestThreshold, bmp_in_dir, bmp_out_dir);
    Histogram histogram(bmp);
    BMP thresholdHis = histogram.buildHistogramWithThreshold(bestThreshold);
    io.writeBmp(thresholdHis, his_out_dir);
}
