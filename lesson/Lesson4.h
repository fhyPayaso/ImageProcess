/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON4_H
#define IMAGEPROCESS_LESSON4_H


#include <cmath>
#include "../utils/MatrixUtil.h"
#include "stdio.h"
#include "../utils/ImageIO.h"


const static char *OUT_BMP_SCALE = "../bitmaps/lesson4/image_scale.bmp";
const static char *OUT_BMP_MOVE = "../bitmaps/lesson4/image_move.bmp";
const static char *OUT_BMP_MIRROR = "../bitmaps/lesson4/image_mirror.bmp";
const static char *OUT_BMP_ROTATE = "../bitmaps/lesson4/image_rotate.bmp";

class Lesson4
{

public:


    /**
     * 图像放缩
     *
     * @param widthScale 横向放缩系数
     * @param heightScale 纵向放缩系数
     * @param bmp_in_dir 输入图片路径
     * @param bmp_out_dir 输出图片路径
     */
    static void scale(double widthScale,
                      double heightScale,
                      const char *bmp_in_dir,
                      const char *bmp_out_dir = OUT_BMP_SCALE);


    /**
     * 图像平移
     *
     * @param xDiff 横向平移距离
     * @param yDiff 纵向平移距离
     * @param bmp_in_dir  输入图片路径
     * @param bmp_out_dir 输出图片路径
     */
    static void transform(double xDiff,
                          double yDiff,
                          const char *bmp_in_dir,
                          const char *bmp_out_dir = OUT_BMP_MOVE);


    /**
     * 图像镜像
     *
     * @param isX  true 为横向镜像, false为纵向镜像
     * @param bmp_in_dir 输入图片路径
     * @param bmp_out_dir 输出图片路径
     */
    static void mirror(bool isX,
                       const char *bmp_in_dir,
                       const char *bmp_out_dir = OUT_BMP_MIRROR);


    /**
     * 图像旋转
     *
     * @param theta 旋转角度(角度制)
     * @param bmp_in_dir 输入图片路径
     * @param bmp_out_dir 输出图片路径
     */
    static void rotate(double theta,
                       const char *bmp_in_dir,
                       const char *bmp_out_dir = OUT_BMP_ROTATE);

private:


    /**
     * 对图像进行双线性插值
     * @param bmp 输入图像
     * @return 输出图像
     */
    static double doubleInterpolation(BMP bmp, double curX, double curY)
    {
        // 获取周围四个点
        // 向下取整
        int startX = std::floor(curX);
        int startY = std::floor(curY);
        // 向上取整
        int endX = std::ceil(curX);
        int endY = std::ceil(curY);

        // 上下两次横向线性插值
        double val00 = bmp.pDataBuffer[startY * bmp.lineByte + startX];
        double val01 = bmp.pDataBuffer[startY * bmp.lineByte + endX];
        double grayUp = singleInterpolation(startX, endX, curX, val00, val01);

        double val10 = bmp.pDataBuffer[endY * bmp.lineByte + startX];
        double val11 = bmp.pDataBuffer[endY * bmp.lineByte + endX];
        double grayDown = singleInterpolation(startX, endX, curX, val10, val11);

        // 一次纵向线性插值
        double grayRes = singleInterpolation(startY, endY, curY, grayUp, grayDown);

        return grayRes;
    }


    static double singleInterpolation(double startIndex, double endIndex, double midIndex,
                                      double startValue, double endValue)
    {
        if (std::abs(startIndex - endIndex) < 0.0001)
            return startValue;

        double res = (endValue - startValue) *
                     (midIndex - startIndex) /
                     (endIndex - startIndex) + startValue;
        return res;
    }


};


#endif //IMAGEPROCESS_LESSON4_H
