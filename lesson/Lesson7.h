/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON7_H
#define IMAGEPROCESS_LESSON7_H


#include "../utils/ImageIO.h"
#include "../utils/MatrixUtil.h"
#include "../utils/Filter.h"
#include "Lesson5.h"
#include <cmath>
#include <vector>

const static char *OUT_BMP_EDGE_DETECTION_PREWITT = "../bitmaps/lesson7/edge_detection_prewitt.bmp";
const static char *OUT_BMP_EDGE_DETECTION_SOBEL = "../bitmaps/lesson7/edge_detection_sobel.bmp";
const static char *OUT_BMP_EDGE_DETECTION_LOG = "../bitmaps/lesson7/edge_detection_log.bmp";


class Lesson7
{

public:

    static void prewittEdgeDetection(const char *bmp_in_dir,
                                     const char *bmp_out_dir = OUT_BMP_EDGE_DETECTION_PREWITT);

    static void sobelEdgeDetection(const char *bmp_in_dir,
                                   const char *bmp_out_dir = OUT_BMP_EDGE_DETECTION_SOBEL);

    static void LOGEdgeDetection(const char *bmp_in_dir,
                                 const char *bmp_out_dir = OUT_BMP_EDGE_DETECTION_LOG);

    static std::vector<int> getGrayList(BMP bmp, int height, int width);
};


#endif //IMAGEPROCESS_LESSON7_H
