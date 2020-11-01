/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson6.h"

void Lesson6::segmentWithSeed(Point2i originPoint, int t, const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
    resBmp.pDataBuffer = (BYTE *) malloc(resBmp.height * resBmp.lineByte);
    int flagTable[resBmp.height][resBmp.width];
    memset(flagTable, 0, resBmp.height * resBmp.width);

    std::vector<Point2i> pointList;
    pointList.push_back(originPoint);

    while (!pointList.empty())
    {
        auto curPnt = pointList.back();
        pointList.pop_back();

        originPoint.x = curPnt.x;
        originPoint.y = curPnt.y;

        for (int i = 0; i < 8; ++i)
        {
            Point2i growPnt;
            growPnt.x = wMove[i] + curPnt.x;
            growPnt.y = hMove[i] + curPnt.y;
            if (growPnt.x >= 0 && growPnt.y >= 0 && growPnt.x < bmp.width && growPnt.y < bmp.height)
            {
                if (flagTable[growPnt.y][growPnt.x] == 0)
                {
                    int curIndex = curPnt.y * bmp.lineByte + curPnt.x;
                    int growIndex = growPnt.y * bmp.lineByte + growPnt.x;
                    // 相邻点符合阈值条件
                    if (std::abs(bmp.pDataBuffer[curIndex] - bmp.pDataBuffer[growIndex]) <= t)
                    {
                        resBmp.pDataBuffer[growIndex] = 255;
                        pointList.push_back(growPnt);
                        flagTable[growPnt.y][growPnt.x] = 1;
                    }
                }
            }
        }
    }

    io.writeBmp(resBmp, bmp_out_dir);
    printf("segment with seed done !\n");
}
