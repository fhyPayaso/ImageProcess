/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON6_H
#define IMAGEPROCESS_LESSON6_H

#include "../utils/ImageIO.h"
#include <cmath>
#include <vector>
#include <stack>

const static char *OUT_BMP_SEGMENT_WITH_SEED = "../bitmaps/lesson6/segment_with_seed.bmp";
const static char *OUT_BMP_SEGMENT_WITHOUT_SEED = "../bitmaps/lesson6/segment_without_seed.bmp";

struct SplitStruct
{
    int width; // 当前区域宽度
    int height; // 当前区域高度
    int widthOffset; // 宽度方向偏移量
    int heightOffset; // 高度方向偏移量
};


class Lesson6
{


public:


    /**
     * 基于种子的区域增长
     *
     * @param originPoint 初始增长点
     * @param t 增长阈值
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void segmentWithSeed(Point2i originPoint,
                                int t,
                                const char *bmp_in_dir,
                                const char *bmp_out_dir = OUT_BMP_SEGMENT_WITH_SEED);

    static void segmentWithoutSeed(const char *bmp_in_dir,
                                   const char *bmp_out_dir = OUT_BMP_SEGMENT_WITHOUT_SEED)
    {
        ImageIO io;
        BMP bmp = io.readBmp(bmp_in_dir);
        BMP resBmp = bmp;
        resBmp.pDataBuffer = (BYTE *) malloc(resBmp.height * resBmp.lineByte);

        std::stack<SplitStruct> S;
        // 将原始图像作为初始节点
        SplitStruct originStruct;
        originStruct.width = bmp.width;
        originStruct.height = bmp.height;
        originStruct.widthOffset = 0;
        originStruct.heightOffset = 0;
        S.push(originStruct);


        while (!S.empty())
        {
            SplitStruct curStruct = S.top();
            S.pop();

            // 计算当前左上角原点的索引值
            int baseIndex = curStruct.heightOffset * bmp.lineByte + curStruct.widthOffset;

            // 将当前图像分裂为2*2的区域
            int widthTemp[3], heightTemp[3];
            widthTemp[0] = 0;
            heightTemp[0] = 0;
            widthTemp[2] = (curStruct.width + 1) / 2;
            heightTemp[2] = (curStruct.height + 1) / 2;
            widthTemp[1] = curStruct.width - widthTemp[2];
            heightTemp[1] = curStruct.height - heightTemp[2];
            // 对于每一个区域
            int grayTemp[2][2];
            for (int i = 1; i < 3; ++i)
            {
                for (int j = 1; j < 3; ++j)
                {
                    // 计算当前子区域的初始索引
                    int subBaseIndex = baseIndex + bmp.lineByte * heightTemp[i - 1] + widthTemp[j - 1];
                    int curIndex;

                    int curGraySum = 0; // 当前区域灰度值之和
                    // 遍历每个子区域的像素
                    for (int h = 0; h < heightTemp[i]; h++)
                    {
                        for (int w = 0; w < widthTemp[j]; w++)
                        {
                            curIndex = subBaseIndex + h * bmp.lineByte + w;
                            if (curIndex < bmp.lineByte * bmp.height)
                                curGraySum += bmp.pDataBuffer[curIndex];
                        }
                    }

                    // 当前区域宽度为1的时候可能为0， 无需分裂
                    if (heightTemp[i] * widthTemp[j] == 0)
                        continue;

                    // 当前区域宽度为2或3的时候可能为1
                    if (heightTemp[i] * widthTemp[j] == 1)
                    {
                        int k = subBaseIndex;
                        if (k < bmp.lineByte * bmp.height - 1)
                        {
                            if (bmp.pDataBuffer[k] < 128)
                            {

                                resBmp.pDataBuffer[k] = 0;
                                resBmp.pDataBuffer[k + 1] = 0;
                            }
                            else
                            {
                                resBmp.pDataBuffer[k] = 255;
                                resBmp.pDataBuffer[k + 1] = 255;
                            }
                        }
                        continue;
                    }


                    // 计算当前去区域内的灰度平均值
                    grayTemp[i - 1][j - 1] = curGraySum / (heightTemp[i] * widthTemp[j]);
                    // 判断当前区域是否需要继续分裂
                    if (grayTemp[i - 1][j - 1] < 220)
                    {
                        // 将当前区域作为新节点入栈
                        SplitStruct newStruct;
                        newStruct.height = heightTemp[i];
                        newStruct.width = widthTemp[j];
                        newStruct.heightOffset = curStruct.heightOffset + heightTemp[i - 1];
                        newStruct.widthOffset = curStruct.widthOffset + widthTemp[j - 1];
                        S.push(newStruct);
                    }
                    else
                    {
                        // 若不需要分裂则进行合并(直接填充为黑色)
                        for (int h = 0; h < heightTemp[i]; h++)
                        {
                            for (int w = 0; w < widthTemp[j]; w++)
                            {
                                curIndex = subBaseIndex + h * bmp.lineByte + w;
                                if (curIndex < bmp.lineByte * bmp.height - 1)
                                {
                                    resBmp.pDataBuffer[curIndex] = 255;
                                    resBmp.pDataBuffer[curIndex + 1] = 255;
                                }
                            }
                        }
                    }


                }
            }


        }


        io.writeBmp(resBmp, bmp_out_dir);
        printf("segment with seed done !\n");
    }

};


#endif //IMAGEPROCESS_LESSON6_H
