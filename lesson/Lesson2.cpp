/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson2.h"

void Lesson2::buildHistogram(const char *bmp_in_dir, const char *his_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    Histogram histogram(bmp);
    io.writeBmp(histogram.buildHistogramBmp(), his_out_dir);
    printf("render histogram done!\n");
}

void Lesson2::equalizeHistogram(const char *bmp_in_dir, const char *bmp_out_dir, const char *his_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    Histogram histogram(bmp);
    BMP equalizedBmp = histogram.equalizeBmp();
    io.writeBmp(equalizedBmp, bmp_out_dir);
    printf("equalize done!\n");

    Histogram newHistogram(equalizedBmp);
    io.writeBmp(newHistogram.buildHistogramBmp(), his_out_dir);
    printf("render histogram done!\n");
}
