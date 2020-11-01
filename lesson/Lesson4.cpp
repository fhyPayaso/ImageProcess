/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson4.h"

void Lesson4::scale(double widthScale, double heightScale, const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
    resBmp.width = bmp.width * widthScale;
    resBmp.height = bmp.height * heightScale;
    resBmp.lineByte = (resBmp.width * resBmp.bitCount / 8 + 3) / 4 * 4;
    resBmp.pDataBuffer = (BYTE *) malloc(resBmp.lineByte * resBmp.height);

    // 获取放缩矩阵
    Matrix3X3f scaleM = MatrixUtil::genScaleMatrix(widthScale, heightScale);

    for (int i = 0; i < bmp.width; ++i)
    {
        for (int j = 0; j < bmp.height; ++j)
        {
            Vector3f V;
            V.setXY(i, j);
            // 矩阵与齐次坐标做乘法, 获取变换后的坐标
            Vector3f resV = MatrixUtil::multi(scaleM, V);
            int x = (int) resV.vec[0];
            int y = (int) resV.vec[1];
            if (x < resBmp.width && y < resBmp.height)
            {
                int orgIndex = j * bmp.lineByte + i;
                int curIndex = y * resBmp.lineByte + x;
                resBmp.pDataBuffer[curIndex] = bmp.pDataBuffer[orgIndex];
            }
        }
    }

    for (int i = 0; i < resBmp.width; ++i)
    {
        for (int j = 0; j < resBmp.height; ++j)
        {
            int x = i, y = j;
            double xf = x / widthScale;
            double yf = y / heightScale;
            int resGray = (int) doubleInterpolation(bmp, xf, yf);
            resBmp.pDataBuffer[y * resBmp.lineByte + x] = resGray;
        }
    }

    io.writeBmp(resBmp, bmp_out_dir);
    printf("scale image done!\n");
}

void Lesson4::transform(double xDiff, double yDiff, const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;

    int xExtend = std::ceil(std::abs(xDiff));
    int yExtend = std::ceil(std::abs(yDiff));
    resBmp.width = bmp.width + xExtend;
    resBmp.height = bmp.height + yExtend;
    resBmp.lineByte = (resBmp.width * resBmp.bitCount / 8 + 3) / 4 * 4;
    resBmp.pDataBuffer = (BYTE *) malloc(resBmp.lineByte * resBmp.height);

    // 获取平移矩阵
    Matrix3X3f transM = MatrixUtil::genTransformMatrix(xDiff, yDiff);

    for (int i = 0; i < bmp.width; ++i)
    {
        for (int j = 0; j < bmp.height; ++j)
        {
            Vector3f V;
            V.setXY(i, j);
            // 矩阵与齐次坐标做乘法, 获取变换后的坐标
            Vector3f resV = MatrixUtil::multi(transM, V);
            int x = (int) resV.vec[0];
            int y = (int) resV.vec[1];

            int xFlag = 0, yFlag = 0;
            if (yDiff < 0)
                yFlag = yExtend;
            if (xDiff < 0)
                xFlag = xExtend;

//            if (x >= 0 && y >= 0 && x < resBmp.width && y < resBmp.height)
//            {




            int orgIndex = j * bmp.lineByte + i;
            int curIndex = (y + yFlag) * resBmp.lineByte + (x + xFlag);
            resBmp.pDataBuffer[curIndex] = bmp.pDataBuffer[orgIndex];
//            }
        }
    }

    io.writeBmp(resBmp, bmp_out_dir);
    printf("transform image done!\n");

}

void Lesson4::mirror(bool isX, const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;
    resBmp.pDataBuffer = (BYTE *) malloc(resBmp.lineByte * resBmp.height);

    // 获取镜像矩阵
    Matrix3X3f mirrorM;
    if (isX)
        mirrorM = MatrixUtil::genMirrorMatrix(resBmp.width, true);
    else
        mirrorM = MatrixUtil::genMirrorMatrix(resBmp.height, false);


    for (int i = 0; i < resBmp.width; ++i)
    {
        for (int j = 0; j < resBmp.height; ++j)
        {
            Vector3f V;
            V.setXY(i, j);
            // 矩阵与齐次坐标做乘法, 获取变换后的坐标
            Vector3f resV = MatrixUtil::multi(mirrorM, V);
            int x = (int) resV.vec[0];
            int y = (int) resV.vec[1];
            if (x >= 0 && y >= 0 && x < resBmp.width && y < resBmp.height)
            {
                int orgIndex = j * bmp.lineByte + i;
                int curIndex = y * resBmp.lineByte + x;
                resBmp.pDataBuffer[curIndex] = bmp.pDataBuffer[orgIndex];
            }
        }
    }

    io.writeBmp(resBmp, bmp_out_dir);
    printf("mirror image done!\n");
}

void Lesson4::rotate(double theta, const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP resBmp = bmp;

    double extendAxis = 1.5;

    resBmp.width = bmp.width * extendAxis;
    resBmp.height = bmp.height * extendAxis;
    resBmp.lineByte = (resBmp.width * resBmp.bitCount / 8 + 3) / 4 * 4;
    resBmp.pDataBuffer = (BYTE *) malloc(resBmp.lineByte * resBmp.height);

    // 获取旋转矩阵以及平移矩阵
    Matrix3X3f rotateM = MatrixUtil::genRotateMatrix(theta);
    Matrix3X3f rotateMNeg = MatrixUtil::genRotateMatrix(-theta);
    Matrix3X3f transNegM = MatrixUtil::genTransformMatrix(-bmp.width / 2, -bmp.height / 2);
    Matrix3X3f transPosM = MatrixUtil::genTransformMatrix(bmp.width / 2, bmp.height / 2);

    Matrix3X3f transNegM2 = MatrixUtil::genTransformMatrix(-resBmp.width / 2, -resBmp.height / 2);
    Matrix3X3f transPosM2 = MatrixUtil::genTransformMatrix(resBmp.width / 2, resBmp.height / 2);

    for (int i = 0; i < bmp.width; ++i)
    {
        for (int j = 0; j < bmp.height; ++j)
        {
            Vector3f V;
            V.setXY(i, j);
            // 首先将图片中心平移到(0,0)点
            V = MatrixUtil::multi(transNegM, V);
            // 以(0,0)点为圆心进行旋转
            V = MatrixUtil::multi(rotateM, V);
            // 再将图片平移回原来的位置
            V = MatrixUtil::multi(transPosM2, V);


            int x = (int) V.vec[0];
            int y = (int) V.vec[1];
            if (x >= 0 && y >= 0 && x < resBmp.width && y < resBmp.height)
            {
                int orgIndex = j * bmp.lineByte + i;
                int curIndex = y * resBmp.lineByte + x;
                resBmp.pDataBuffer[curIndex] = bmp.pDataBuffer[orgIndex];
            }
        }
    }

    for (int i = 0; i < resBmp.width; ++i)
    {
        for (int j = 0; j < resBmp.height; ++j)
        {
            Vector3f V;
            V.setXY(i, j);
            // 首先将图片中心平移到(0,0)点
            V = MatrixUtil::multi(transNegM2, V);
            // 以(0,0)点为圆心进行旋转
            V = MatrixUtil::multi(rotateMNeg, V);
            // 再将图片平移回原来的位置
            V = MatrixUtil::multi(transPosM, V);

            double xf = V.vec[0];
            double yf = V.vec[1];
            if (xf >= 0 && yf >= 0 && xf < bmp.width - 1 && yf < bmp.height - 1)
            {
                int resGray = (int) doubleInterpolation(bmp, xf, yf);
                resBmp.pDataBuffer[j * resBmp.lineByte + i] = resGray;
            }
        }
    }


    io.writeBmp(resBmp, bmp_out_dir);
    printf("rotate image done!\n");


}
