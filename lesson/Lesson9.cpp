/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson9.h"

void Lesson9::regionMark(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
    resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

    // 记录每个像素的标记值
    int flag[bmp.height][bmp.width];
    for (int h = 0; h < bmp.height; h++)
        for (int w = 0; w < bmp.width; w++)
            flag[h][w] = 0;

    // 标记值
    int markVal = 0;

    for (int h = 0; h < bmp.height; h++)
    {
        for (int w = 0; w < bmp.width; w++)
        {
            int curIndex = h * bmp.lineByte + w;
            int curGray = bmp.pDataBuffer[curIndex];
            // 当前像素为前景色，同时未被搜索过
            if (curGray == 255 && flag[h][w] == 0)
            {
                markVal++;
                flag[h][w] = markVal;
                Point2i pnt(w, h);
                std::queue<Point2i> Q;
                Q.push(pnt);
                while (!Q.empty())
                {
                    Point2i curPnt = Q.front();
                    Q.pop();

                    for (int i = 0; i < 9; ++i)
                    {
                        if (i == 4)
                            continue;
                        Point2i newPnt;
                        newPnt.x = curPnt.x + wMove[i];
                        newPnt.y = curPnt.y + hMove[i];
                        if (newPnt.x >= 0 && newPnt.y >= 0
                            && newPnt.x < bmp.width && newPnt.y < bmp.height)
                        {
                            int newIndex = newPnt.y * bmp.lineByte + newPnt.x;
                            if (bmp.pDataBuffer[newIndex] == 255 && flag[newPnt.y][newPnt.x] == 0)
                            {
                                flag[newPnt.y][newPnt.x] = markVal;
                                Q.push(newPnt);
                            }
                        }
                    }
                }
            }
        }
    }

    int step = 255 / markVal;

    for (int h = 0; h < bmp.height; h++)
    {
        for (int w = 0; w < bmp.width; w++)
        {
            int curIndex = h * bmp.lineByte + w;
            if (flag[h][w] == 0)
                resBmp.pDataBuffer[curIndex] = bmp.pDataBuffer[curIndex];
            else
                resBmp.pDataBuffer[curIndex] = step * flag[h][w];
        }
    }


    io.writeBmp(resBmp, bmp_out_dir);
    printf("region mark done! \n");
}

void Lesson9::regionPick(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
    resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);


    for (int h = 0; h < bmp.height; h++)
    {
        for (int w = 0; w < bmp.width; w++)
        {
            int curIndex = h * bmp.lineByte + w;
            int curGray = bmp.pDataBuffer[curIndex];

            int bNum = 0, wNum = 0;
            for (int i = 0; i < 9; ++i)
            {
                if (i == 4)
                    continue;
                int newH = h + hMove[i];
                int newW = w + wMove[i];
                if (newW >= 0 && newH >= 0 && newW < bmp.width && newH < bmp.height)
                {
                    int newIndex = newH * bmp.lineByte + newW;
                    if (bmp.pDataBuffer[newIndex] == 0) bNum++;
                    else if (bmp.pDataBuffer[newIndex] == 255) wNum++;
                }
            }
            if (bNum == 8 || wNum == 8)
                resBmp.pDataBuffer[curIndex] = 0;
            else
                resBmp.pDataBuffer[curIndex] = 255;
        }
    }

    io.writeBmp(resBmp, bmp_out_dir);
    printf("region pick done! \n");
}
