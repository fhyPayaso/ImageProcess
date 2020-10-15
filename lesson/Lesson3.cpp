/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson3.h"

void Lesson3::avgFilterWithoutBorder(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = Filter::averageWithoutBorder(bmp);
    io.writeBmp(resBmp, bmp_out_dir);
    printf("average filter without border done!\n");
}

void Lesson3::avgFilterWithBorder(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = Filter::averageWithBorder(bmp);
    io.writeBmp(resBmp, bmp_out_dir);
    printf("average filter with border done!\n");
}

void Lesson3::medianFilterWithoutBorder(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = Filter::midWithoutBorder(bmp);
    io.writeBmp(resBmp, bmp_out_dir);
    printf("median filter without border done!\n");
}

void Lesson3::medianFilterWithBorder(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = Filter::midWithBorder(bmp);
    io.writeBmp(resBmp, bmp_out_dir);
    printf("median filter with border done!\n");
}
