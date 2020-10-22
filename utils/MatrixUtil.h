/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_MATRIXUTIL_H
#define IMAGEPROCESS_MATRIXUTIL_H

#include <cmath>

#define PI 3.1415926


// 3X3矩阵
typedef struct tagMatrix3X3f
{
    double mat[3][3];

    void zero()
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                mat[i][j] = 0;
    }

    void identity()
    {
        zero();
        for (int i = 0; i < 3; ++i)
            mat[i][i] = 1.0;
    }

} Matrix3X3f;


// 3x1 向量
typedef struct tagVector3f
{
    double vec[3];

    void identity()
    {
        for (int i = 0; i < 3; ++i)
            vec[i] = 1.0;
    }

    void setXY(double x, double y)
    {
        identity();
        vec[0] = x;
        vec[1] = y;
    }

} Vector3f;


class MatrixUtil
{

public:

    /**
     * 获取放缩矩阵
     * @param x x坐标放缩系数
     * @param y y坐标放缩系数
     * @return
     */
    static Matrix3X3f genScaleMatrix(double x, double y);


    /**
     * 获取平移矩阵
     * @param x x坐标偏移量
     * @param y y坐标偏移量
     * @return
     */
    static Matrix3X3f genTransformMatrix(double x, double y);


    /**
     * 获取旋转矩阵
     * @param theta 旋转角度(角度值)
     * @return
     */
    static Matrix3X3f genRotateMatrix(double theta);


    /**
     *
     * 获取镜像矩阵
     *
     * @param length 镜像方向总长度
     * @param isX  是否是对横坐标进行镜像
     * @return
     */
    static Matrix3X3f genMirrorMatrix(double length, bool isX);


    /**
     *  矩阵与向量相乘
     *
     * @param M 3x3 矩阵
     * @param V 3x1 向量
     * @return 3x1 向量
     */
    static Vector3f multi(Matrix3X3f M, Vector3f V);


};


#endif //IMAGEPROCESS_MATRIXUTIL_H
