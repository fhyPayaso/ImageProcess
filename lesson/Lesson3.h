/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON3_H
#define IMAGEPROCESS_LESSON3_H

#include "../utils/ImageIO.h"
#include "../utils/Filter.h"

const static char *OUT_BMP_AVG = "../bitmaps/lesson3/image_avg_filter.bmp";
const static char *OUT_BMP_AVG_BORDER = "../bitmaps/lesson3/image_avg_filter_border.bmp";
const static char *OUT_BMP_MID = "../bitmaps/lesson3/image_mid_filter.bmp";
const static char *OUT_BMP_MID_BORDER = "../bitmaps/lesson3/image_mid_filter_border.bmp";

class Lesson3
{
private:

public:

    static void avgFilterWithoutBorder(const char *bmp_in_dir,
                                       const char *bmp_out_dir = OUT_BMP_AVG);

    static void avgFilterWithBorder(const char *bmp_in_dir,
                                    const char *bmp_out_dir = OUT_BMP_AVG_BORDER);


    static void medianFilterWithoutBorder(const char *bmp_in_dir,
                                          const char *bmp_out_dir = OUT_BMP_MID);

    static void medianFilterWithBorder(const char *bmp_in_dir,
                                       const char *bmp_out_dir = OUT_BMP_MID_BORDER);


};


#endif //IMAGEPROCESS_LESSON3_H
