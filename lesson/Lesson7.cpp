/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson7.h"

std::vector<int> Lesson7::getGrayList(BMP bmp, int height, int width)
{
    std::vector<int> resVector;
    for (int i = 0; i < 9; ++i)
    {
        int h = height + hMove[i];
        int w = width + wMove[i];
        int index = bmp.lineByte * h + w;
        resVector.push_back(bmp.pDataBuffer[index]);
    }
    return resVector;
}

void Lesson7::prewittEdgeDetection(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
//    BMP grayX, grayY;
    resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

    for (int i = 1; i < bmp.height - 1; i++)
    {
        for (int j = 1; j < bmp.width - 1; ++j)
        {
            int curIndex = bmp.lineByte * i + j;
            std::vector<int> Z = getGrayList(bmp, i, j);
            int gx = abs((Z[6] + Z[7] + Z[8]) - (Z[0] + Z[1] + Z[2]));
            int gy = abs((Z[2] + Z[5] + Z[8]) - (Z[0] + Z[3] + Z[6]));
            resBmp.pDataBuffer[curIndex] = (gx + gy) / 2;
        }
    }

    io.writeBmp(resBmp, bmp_out_dir);
    Lesson5::otsuThreshold(bmp_out_dir, bmp_out_dir, NULL);
    printf("prewitt edge detection done! \n");
}

void Lesson7::sobelEdgeDetection(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
    resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

    for (int i = 1; i < bmp.height - 1; i++)
    {
        for (int j = 1; j < bmp.width - 1; ++j)
        {
            int curIndex = bmp.lineByte * i + j;
            std::vector<int> Z = getGrayList(bmp, i, j);
            int gx = abs((Z[6] + 2 * Z[7] + Z[8]) - (Z[0] + 2 * Z[1] + Z[2]));
            int gy = abs((Z[2] + 2 * Z[5] + Z[8]) - (Z[0] + 2 * Z[3] + Z[6]));
            resBmp.pDataBuffer[curIndex] = (gx + gy) / 2;
        }
    }
    io.writeBmp(resBmp, bmp_out_dir);
    Lesson5::otsuThreshold(bmp_out_dir, bmp_out_dir, NULL);
    printf("sobel edge detection done! \n");
}

void Lesson7::LOGEdgeDetection(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);

    BMP resBmp = Filter::midWithoutBorder(bmp);

    for (int i = 1; i < bmp.height - 1; i++)
    {
        for (int j = 1; j < bmp.width - 1; ++j)
        {
            int curIndex = bmp.lineByte * i + j;
            std::vector<int> Z = getGrayList(bmp, i, j);
            resBmp.pDataBuffer[curIndex] = abs(Z[1] + Z[3] + Z[5] + Z[7] - 4 * Z[4]);
        }
    }
    io.writeBmp(resBmp, bmp_out_dir);
    Lesson5::otsuThreshold(bmp_out_dir, bmp_out_dir, NULL);
    printf("LOG edge detection done! \n");
}
