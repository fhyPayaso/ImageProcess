/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON1_H
#define IMAGEPROCESS_LESSON1_H


#include "../utils/ImageIO.h"

const static char *OUT_BMP_R = "../bitmaps/lesson1/image_r.bmp";
const static char *OUT_BMP_G = "../bitmaps/lesson1/image_g.bmp";
const static char *OUT_BMP_B = "../bitmaps/lesson1/image_b.bmp";
const static char *OUT_BMP_GRAY8 = "../bitmaps/lesson1/image_gray8.bmp";
const static char *OUT_BMP_REV_GRAY8 = "../bitmaps/lesson1/image_rev_gray8.bmp";

class Lesson1
{

private:


public:

    /**
     * 将24位图像分割为rgb三幅图像
     *
     * @param bmp_in
     * @param bmp_out_r
     * @param bmp_out_g
     * @param bmp_out_b
     */
    static void split24BmpToRGB(const char *bmp_in,
                                const char *bmp_out_r = OUT_BMP_R,
                                const char *bmp_out_g = OUT_BMP_G,
                                const char *bmp_out_b = OUT_BMP_B);


    /**
     * 将24位彩色图转换为8位灰度图
     *
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void cover24BmpToGray8(const char *bmp_in_dir,
                                  const char *bmp_out_dir = OUT_BMP_GRAY8);

    /**
     * 将8位灰度图进行翻转
     *
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void reverseGray8(const char *bmp_in_dir = OUT_BMP_GRAY8,
                             const char *bmp_out_dir = OUT_BMP_REV_GRAY8);


};


#endif //IMAGEPROCESS_LESSON1_H
