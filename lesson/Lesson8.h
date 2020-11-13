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

const static char *OUT_BMP_HOUGH1 = "../bitmaps/lesson8/edge_detection_hough1.bmp";
const static char *OUT_BMP_HOUGH2 = "../bitmaps/lesson8/edge_detection_hough2.bmp";

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
                      const char *bmp_out_dir);
};


#endif //IMAGEPROCESS_LESSON8_H
