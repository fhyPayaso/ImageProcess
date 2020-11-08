/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Filter.h"
#include <vector>


BMP Filter::averageWithoutBorder(BMP bmp)
{
    BMP resBmp = bmp;
    for (int i = 0; i < bmp.height; ++i)
    {
        for (int j = 0; j < bmp.width; ++j)
        {
            if (i > 0 && j > 0 && i < bmp.height - 1 && j < bmp.width - 1)
            {
                int totalVal = 0;
                for (int k = 0; k < 9; ++k)
                {
                    int curH = hMove[k] + i;
                    int curW = wMove[k] + j;
                    LONG index = bmp.lineByte * curH + curW;
                    int curVal = int(bmp.pDataBuffer[index]);
                    totalVal += curVal;
                }
                resBmp.pDataBuffer[bmp.lineByte * i + j] = totalVal / 9;
            }
        }
    }
    return resBmp;
}

BMP Filter::averageWithBorder(BMP bmp)
{

//    // 将原来的边界两侧分别扩大1
//    LONG bHeight = bmp.height + 2;
//    LONG bWidth = bmp.width + 2;
//    LONG bLineByte = (bHeight * bmp.bitCount / 8 + 3) * 4;
//    LONG newDataSize = bHeight * bLineByte;
//
//    // 将原始图像扩充为新图像
//    BYTE *pTempDataBuffer = (BYTE *) malloc(newDataSize);
//    for (int i = 0; i < bHeight; i++)
//    {
//        for (int j = 0; j < bWidth; j++)
//        {
//            LONG index = i * bLineByte + j;
//            pTempDataBuffer[index] = 128;
//            // 非边界点直接填充到新图像中
//            if (i > 0 && j > 0 && i < bHeight - 1 && j < bWidth - 1)
//            {
//                LONG orgIndex = (i - 1) * bmp.lineByte + (j - 1);
//                pTempDataBuffer[index] = bmp.pDataBuffer[orgIndex];
//            }
//
//        }
//    }
//    // 对新图像进行均值滤波
//    for (int i = 0; i < bHeight; ++i)
//    {
//        for (int j = 0; j < bWidth; ++j)
//        {
//            // 边界无需处理
//            if (i > 0 && j > 0 && i < bHeight - 1 && j < bWidth - 1)
//            {
//                int totalVal = 0;
//                for (int k = 0; k < 9; ++k)
//                {
//                    int curH = hMove[k] + i;
//                    int curW = wMove[k] + j;
//                    LONG index = bLineByte * curH + curW;
//                    int curVal = int(pTempDataBuffer[index]);
//                    totalVal += curVal;
//                }
//                LONG orgIndex = (i - 1) * bmp.lineByte + (j - 1);
//                bmp.pDataBuffer[orgIndex] = totalVal / 9;
//            }
//        }
//    }
//    return bmp;

    BMP resBmp = bmp;
    for (int i = 0; i < bmp.height; ++i)
    {
        for (int j = 0; j < bmp.width; ++j)
        {
            int totalVal = 0;
            int num = 0;
            for (int k = 0; k < 9; ++k)
            {
                int curH = hMove[k] + i;
                int curW = wMove[k] + j;
                if (curH >= 0 && curW >= 0 && curH < bmp.height && curW < bmp.width)
                {
                    LONG index = bmp.lineByte * curH + curW;
                    int curVal = int(bmp.pDataBuffer[index]);
                    totalVal += curVal;
                    num++;
                }
            }
            resBmp.pDataBuffer[bmp.lineByte * i + j] = totalVal / num;

        }
    }
    return resBmp;


}

BMP Filter::midWithoutBorder(BMP bmp)
{
    BMP resBmp = bmp;

    resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

    for (int i = 0; i < bmp.height; ++i)
    {
        for (int j = 0; j < bmp.width; ++j)
        {
            if (i > 0 && j > 0 && i < bmp.height - 1 && j < bmp.width - 1)
            {
                int temp[9];
                for (int k = 0; k < 9; ++k)
                {
                    int curH = hMove[k] + i;
                    int curW = wMove[k] + j;
                    LONG index = bmp.lineByte * curH + curW;
                    int curVal = int(bmp.pDataBuffer[index]);
                    temp[k] = curVal;
                }
                std::sort(temp, temp + 9);
                resBmp.pDataBuffer[bmp.lineByte * i + j] = temp[4];
            }
        }
    }
    return resBmp;
}

BMP Filter::midWithBorder(BMP bmp)
{

    BMP resBmp = bmp;
    BMP extendBmp = extend(bmp);
    BMP midBmp = midWithoutBorder(extendBmp);
    for (int i = 1; i < midBmp.height - 1; ++i)
    {
        for (int j = 1; j < midBmp.width - 1; ++j)
        {
            int x = i - 1;
            int y = j - 1;
            resBmp.pDataBuffer[x * resBmp.lineByte + y] =
                    midBmp.pDataBuffer[i * midBmp.lineByte + j];
        }
    }
    return extendBmp;

//    BMP resBmp = bmp;
//
//    for (int i = 0; i < bmp.height; ++i)
//    {
//        for (int j = 0; j < bmp.width; ++j)
//        {
//            std::vector<int> temp;
//            for (int k = 0; k < 9; ++k)
//            {
//                int curH = hMove[k] + i;
//                int curW = wMove[k] + j;
//                if (curH >= 0 && curW >= 0 && curH < bmp.height && curW < bmp.width)
//                {
//                    LONG index = bmp.lineByte * curH + curW;
//                    int curVal = int(bmp.pDataBuffer[index]);
//                    temp.push_back(curVal);
//                }
//            }
//            std::sort(temp.begin(), temp.end());
//            int len = temp.size();
//            resBmp.pDataBuffer[bmp.lineByte * i + j] = temp[len / 2];
//        }
//    }
//    return resBmp;

}

BMP Filter::extend(BMP bmp)
{
    BMP resBmp = bmp;
    resBmp.width = bmp.width + 2;
    resBmp.height = bmp.height + 2;
    resBmp.lineByte = (resBmp.width * resBmp.bitCount / 8 + 3) / 4 * 4;
    resBmp.pDataBuffer = (BYTE *) malloc(resBmp.lineByte * resBmp.height);

    // 内部复制
    for (int i = 1; i < resBmp.height - 1; i++)
    {
        for (int j = 1; j < resBmp.width - 1; j++)
        {
            LONG index = i * resBmp.lineByte + j;
            LONG orgIndex = (i - 1) * bmp.lineByte + (j - 1);
            resBmp.pDataBuffer[index] = bmp.pDataBuffer[orgIndex];
        }
    }
    // 边界填充
    for (int i = 1; i < resBmp.height - 1; i++)
    {
        resBmp.pDataBuffer[i * resBmp.lineByte] = resBmp.pDataBuffer[i * resBmp.lineByte + 1];
        resBmp.pDataBuffer[i * resBmp.lineByte + (resBmp.width - 1)] =
                resBmp.pDataBuffer[i * resBmp.lineByte + (resBmp.width - 2)];
    }

    for (int i = 0; i < resBmp.width; i++)
    {
        resBmp.pDataBuffer[i] = resBmp.pDataBuffer[1 * resBmp.lineByte + i];
        resBmp.pDataBuffer[(resBmp.height - 1) * resBmp.lineByte + i] =
                resBmp.pDataBuffer[(resBmp.height - 2) * resBmp.lineByte + i];
    }

    return resBmp;
}


BMP Filter::gaussian(BMP bmp)
{
    BMP resBmp = bmp;

    resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

    for (int i = 0; i < bmp.height; ++i)
    {
        for (int j = 0; j < bmp.width; ++j)
        {
            if (i > 0 && j > 0 && i < bmp.height - 1 && j < bmp.width - 1)
            {
                int temp[9];
                for (int k = 0; k < 9; ++k)
                {
                    int curH = hMove[k] + i;
                    int curW = wMove[k] + j;
                    LONG index = bmp.lineByte * curH + curW;
                    int curVal = int(bmp.pDataBuffer[index]);
                    temp[k] = curVal;
                }

                int curGary = temp[0] + 2 * temp[1] + temp[2] +
                              2 * temp[3] + 4 * temp[4] + 2 * temp[5] +
                              temp[6] + 2 * temp[7] + temp[8];

                resBmp.pDataBuffer[bmp.lineByte * i + j] = curGary / 16;
            }
        }
    }
    return resBmp;
}
