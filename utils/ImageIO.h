/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#pragma pack (1)
#ifndef IMAGEPROCESS_IMAGEIO_H
#define IMAGEPROCESS_IMAGEIO_H

#include <iostream>
#include "stdlib.h"
#include "stdio.h"


typedef unsigned char BYTE; // 1
typedef unsigned short WORD; // 2
typedef unsigned int DWORD; // 4
typedef int LONG; // 4

// 文件头
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType; //文件类型，必须是“BM”
    DWORD bfSize; //文件大小，包含文件头的大小 4
    WORD bfReserved1; //保留字 2
    WORD bfReserved2; //保留字 2
    DWORD bfOffBits; //从文件头到实际位图数据的偏移字节数 4
} BITMAPFILEHEADER;

// 信息头
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize; //该结构的长度，为40
    LONG biWidth; //图像宽度
    LONG biHeight; //图像高度
    WORD biPlanes; //位平面数，必须为1
    WORD biBitCount; //颜色位数，
    DWORD biCompression; //是否压缩
    DWORD biSizeImage; //实际位图数据占用的字节数
    LONG biXPelsPerMeter;//目标设备水平分辨率
    LONG biYPelsPerMeter;//目标设备垂直分辨率
    DWORD biClrUsed;//实际使用的颜色数
    DWORD biClrImportant;//图像中重要的颜色数

} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
    BYTE rgbBlue;     //该颜色的蓝色分量
    BYTE rgbGreen;     //该颜色的绿色分量
    BYTE rgbRed;         //该颜色的红色分量
    BYTE rgbReserved;     //保留值
} RGBQUAD;


typedef struct tagBmp
{
    LONG width;
    LONG height;
    LONG lineByte;
    WORD bitCount;
    RGBQUAD *pRgbTable;
    BYTE *pDataBuffer;
} BMP;


class ImageIO
{

public:

    BMP readBmp(const char *bmpPath);

    void writeBmp(BMP bmp, const char *bmpPath);

    void showBmpFileHead(BITMAPFILEHEADER *pBmpHead);

    void showBmpInfoHead(BITMAPINFOHEADER *pBmpInforHead);
};

#endif //IMAGEPROCESS_IMAGEIO_H
