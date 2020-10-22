/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "MatrixUtil.h"

Matrix3X3f MatrixUtil::genScaleMatrix(double x, double y)
{
    Matrix3X3f M;
    M.identity();
    M.mat[0][0] = x;
    M.mat[1][1] = y;
    return M;
}

Matrix3X3f MatrixUtil::genTransformMatrix(double x, double y)
{
    Matrix3X3f M;
    M.identity();
    M.mat[0][2] = x;
    M.mat[1][2] = y;
    return M;
}

Matrix3X3f MatrixUtil::genRotateMatrix(double theta)
{
    // 先转化成弧度
    double angle = (theta / 360) * 2 * PI;

    Matrix3X3f M;
    M.identity();
    M.mat[0][0] = std::cos(angle);
    M.mat[0][1] = std::sin(angle);
    M.mat[1][0] = -std::sin(angle);
    M.mat[1][1] = std::cos(angle);
    return M;
}

Matrix3X3f MatrixUtil::genMirrorMatrix(double length, bool isX)
{
    Matrix3X3f M;
    M.identity();
    if (isX)
    {
        M.mat[0][0] = -1;
        M.mat[0][2] = length;
    }
    else
    {
        M.mat[1][1] = -1;
        M.mat[1][2] = length;
    }
    return M;
}

Vector3f MatrixUtil::multi(Matrix3X3f M, Vector3f V)
{
    Vector3f res;
    for (int i = 0; i < 3; ++i)
    {
        // 计算第i行
        double temp = 0;
        for (int j = 0; j < 3; ++j)
            temp += M.mat[i][j] * V.vec[j];
        res.vec[i] = temp;
    }
    return res;
}
