/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON8_H
#define IMAGEPROCESS_LESSON8_H

#include "../utils/ImageIO.h"
#include "../utils/MatrixUtil.h"
#include <cmath>
#include <vector>
#include <algorithm>

const static char *OUT_BMP_HOUGH = "../bitmaps/lesson8/edge_detection_hough.bmp";

class Lesson8
{

    struct RangeInfo
    {
        int minX = INT_MAX;
        int minY = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;

        bool check(int x, int y)
        {
            if (x < minX - 1 || x > maxX + 1)
                return false;
            if (y < minY - 1 || y > maxY + 1)
                return false;
            return true;
        }


    };


    struct Coordinate
    {
        int p;
        int theta;
        int num;
        RangeInfo rangeInfo;
    };

public:


    static void hough(int renderNum, const char *bmp_in_dir,
                      const char *bmp_out_dir = OUT_BMP_HOUGH)
    {
        ImageIO io;
        BMP bmp = io.readBmp(bmp_in_dir);
        BMP resBmp = bmp;
        resBmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

        // 极坐标角度范围 每隔1°绘制一条直线
        int THETA_MAX = 360;
        // 极坐标ρ范围，最大值应该为右上角的点
        int P_MAX = sqrt(bmp.width * bmp.width + bmp.height * bmp.height);
        // 极坐标列表
        int PolarCoordinates[THETA_MAX][P_MAX];
        // 记录每个直线的范围
        RangeInfo rangeInfoTable[THETA_MAX][P_MAX];

        for (int i = 0; i < THETA_MAX; i++)
        {
            for (int j = 0; j < P_MAX; j++)
            {
                RangeInfo curInfo;
                rangeInfoTable[i][j] = curInfo;
                PolarCoordinates[i][j] = 0;
            }
        }


        for (int y = 0; y < bmp.height; y++)
        {
            for (int x = 0; x < bmp.width; x++)
            {
                int curIndex = bmp.lineByte * y + x;
                int curGray = bmp.pDataBuffer[curIndex];
                // 背景为黑色，前景为白色
                if (curGray == 255)
                {
                    for (int theta = 0; theta < THETA_MAX; theta++)
                    {
                        double realTheta = (2 * PI) * theta / 360.0;
                        int p = floor(x * std::cos(realTheta) + y * std::sin(realTheta));
                        if (p >= 0 && p < P_MAX)
                        {
                            PolarCoordinates[theta][p]++;
                            rangeInfoTable[theta][p].maxX = std::max(rangeInfoTable[theta][p].maxX, x);
                            rangeInfoTable[theta][p].maxY = std::max(rangeInfoTable[theta][p].maxY, y);
                            rangeInfoTable[theta][p].minX = std::min(rangeInfoTable[theta][p].minX, x);
                            rangeInfoTable[theta][p].minY = std::min(rangeInfoTable[theta][p].minY, y);
                        }
                    }
                }
            }
        }

        // 对可能出现的直线进行排序，选择直线上点最多的
        std::vector<Coordinate> lineVec;
        for (int theta = 0; theta < THETA_MAX; theta++)
        {
            for (int p = 0; p < P_MAX; p++)
            {
                if (PolarCoordinates[theta][p] > 2)
                {
                    Coordinate coord;
                    coord.theta = theta;
                    coord.p = p;
                    coord.num = PolarCoordinates[theta][p];
                    coord.rangeInfo = rangeInfoTable[theta][p];
                    lineVec.push_back(coord);
                }
            }
        }

        // 根据出现的次数多少进行排序
        std::sort(lineVec.begin(), lineVec.end(), [](const Coordinate c0, const Coordinate c1)
        {
            return c0.num > c1.num;
//            if (c0.num != c1.num)
//                return c0.num > c1.num;
//            if (c0.theta != c1.theta)
//                return c0.theta > c1.theta;
//            return c0.p > c1.p;
        });

//        std::vector<Coordinate> newLineVec = lineVec;
#if 1

        std::vector<Coordinate> newLineVec;
        for (int i = 0; i < lineVec.size(); ++i)
        {
            Coordinate coord = lineVec[i];
            if (i == 0)
            {
                newLineVec.push_back(coord);
                continue;
            }
            else
            {
                bool flag = true;
                for (int j = 0; j < newLineVec.size(); ++j)
                {
                    Coordinate preCoord = newLineVec[j];

                    if(abs(preCoord.theta - coord.theta)==180 && preCoord.p == coord.p)
                    {
                        flag = false;
                        break;
                    }

                    if (preCoord.num == coord.num
                        && preCoord.theta == coord.theta
                        && abs(preCoord.p - coord.p) < 3)
                    {
                        flag = false;
                        break;
                    }

                }
                if(flag)
                    newLineVec.push_back(coord);
//                Coordinate preCoord = newLineVec.back();
//                if (preCoord.num == coord.num
//                    && preCoord.theta == coord.theta
//                    && abs(preCoord.p - coord.p) < 3)
//                    continue;
//                newLineVec.push_back(coord);
            }

            if (newLineVec.size() >=renderNum)
                break;
        }

#endif
        printf("size： %d\n", int(newLineVec.size()));
        for (int k = 0; k < 100; ++k)
        {
            Coordinate c = newLineVec[k];
            printf("index%d ====> p: %d,  theta:%d,  num:%d\n", k, c.p, c.theta, c.num);
        }


        renderNum = std::min(renderNum, int(newLineVec.size()));
        for (int lineIndex = 0; lineIndex < renderNum; ++lineIndex)
        {
            Coordinate curLine = newLineVec[lineIndex];
            RangeInfo rangeInfo = curLine.rangeInfo;
            double realTheta = (2 * PI) * curLine.theta / 360;

            double sinTheta = std::sin(realTheta);
            double cosTheta = std::cos(realTheta);

            if (std::abs(sinTheta - 0) < 1e-3)
            {
                int x = curLine.p;
                if (x >= 0 && x < bmp.width)
                {
                    for (int y = 0; y < bmp.height; y++)
                        if (rangeInfo.check(x, y))
                            resBmp.pDataBuffer[y * bmp.lineByte + x] = 255;

                }
            }
            else
            {
                for (int x = 0; x < bmp.width; x++)
                {

                    int y = (curLine.p - x * cosTheta) / sinTheta;
                    if (y >= 0 && y < bmp.height)
                    {
                        if (rangeInfo.check(x, y))
                            resBmp.pDataBuffer[y * bmp.lineByte + x] = 255;
                    }
                }
            }
        }
        io.writeBmp(resBmp, bmp_out_dir);
        printf("hough line done !\n");

    }
};


#endif //IMAGEPROCESS_LESSON8_H
