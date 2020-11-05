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
                                   const char *bmp_out_dir = OUT_BMP_SEGMENT_WITHOUT_SEED);

};


#endif //IMAGEPROCESS_LESSON6_H
