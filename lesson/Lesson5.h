/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON5_H
#define IMAGEPROCESS_LESSON5_H

#include "../utils/ImageIO.h"
#include <cmath>

const static char *OUT_BMP_CONFIG_THRESHOLD = "../bitmaps/lesson5/image_config_threshold.bmp";
const static char *OUT_BMP_ITERATION = "../bitmaps/lesson5/image_iteration.bmp";
const static char *OUT_BMP_OTSU = "../bitmaps/lesson5/image_otsu.bmp";
// 带标记的直方图
const static char *OUT_BMP_ITERATION_HIS = "../bitmaps/lesson5/image_iteration_his.bmp";
const static char *OUT_BMP_OTSU_HIS = "../bitmaps/lesson5/image_otsu_his.bmp";

class Lesson5
{

public:

    /**
     * 固定阈值
     *
     * @param threshold
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void configThreshold(int threshold,
                                const char *bmp_in_dir,
                                const char *bmp_out_dir = OUT_BMP_CONFIG_THRESHOLD);

    /**
     * 迭代求阈值
     *
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void iterationThreshold(const char *bmp_in_dir,
                                   const char *bmp_out_dir = OUT_BMP_ITERATION,
                                   const char *his_out_dir = OUT_BMP_ITERATION_HIS);


    /**
     * 大津法求阈值
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void otsuThreshold(const char *bmp_in_dir,
                              const char *bmp_out_dir = OUT_BMP_OTSU,
                              const char *his_out_dir = OUT_BMP_OTSU_HIS);


    /**
     * 分别求两类中的均值
     * @param bmp
     * @param threshold
     * @param minMean
     * @param maxMean
     */
    static void getBmpDoubleMean(BMP bmp, int threshold, double &minMean, double &maxMean);


};


#endif //IMAGEPROCESS_LESSON5_H
