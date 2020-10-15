/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON2_H
#define IMAGEPROCESS_LESSON2_H

#include "../utils/ImageIO.h"
#include "../utils/Histogram.h"

const static char *OUT_BMP_HISTOGRAM = "../bitmaps/lesson2/image_histogram.bmp";

const static char *OUT_BMP_EQU = "../bitmaps/lesson2/image_equalize.bmp";
const static char *OUT_BMP_EQU_HISTOGRAM = "../bitmaps/lesson2/image_equalize_histogram.bmp";

class Lesson2
{

private:

public:

    static void buildHistogram(const char *bmp_in_dir,
                               const char *his_out_dir = OUT_BMP_HISTOGRAM);


    static void equalizeHistogram(const char *bmp_in_dir,
                                  const char *bmp_out_dir = OUT_BMP_EQU,
                                  const char *his_out_dir = OUT_BMP_EQU_HISTOGRAM);

};


#endif //IMAGEPROCESS_LESSON2_H
