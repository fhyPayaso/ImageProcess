/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "ImageIO.h"

#include <cmath>

using namespace std;

BMP ImageIO::readBmp(const char *bmpPath)
{
    BMP bmp;

    // 开启文件流, 类型为2进制读
    FILE *fp = fopen(bmpPath, "rb");
    if (fp == nullptr)
    {
        printf("no such file!\n");
        return bmp;
    }

    // 读取文件头
    BITMAPFILEHEADER bmFileHeader;
    fread(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
//    showBmpFileHead(&bmFileHeader);
    // 需要对文件类型进行判断
    if (bmFileHeader.bfType != 0x4d42)
    {
        printf("the file is not .bmp ! \n");
        return bmp;
    }

    // 读取信息头
    BITMAPINFOHEADER bmInfoHeader;
    fread(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
//    showBmpInfoHead(&bmInfoHeader);

    // 构建Bmp
    bmp.width = bmInfoHeader.biWidth;
    bmp.height = bmInfoHeader.biHeight;
    bmp.bitCount = bmInfoHeader.biBitCount;
    // 计算每行占多少字节(必须是4的整数倍)
    // biWidth * biBitCount/8 即为每行字节数
    // +3 -> /4 ->*4 目的是将行字节修正为4的倍数
    bmp.lineByte = (bmp.width * bmp.bitCount / 8 + 3) / 4 * 4;

    // 如果不是真彩色图片, 则需要加载调色板
    if (bmp.bitCount < 24)
    {
        // 获取颜色数量
        int colorNum = pow(2, bmp.bitCount);
        int colorSize = colorNum * sizeof(RGBQUAD);
        bmp.pRgbTable = (RGBQUAD *) malloc(colorSize);
        memset(bmp.pRgbTable, 0, colorSize);
        fread(bmp.pRgbTable, sizeof(RGBQUAD), colorNum, fp);
    }

    // 开始读取数据
    LONG dataSize = bmp.height * bmp.lineByte;
    bmp.pDataBuffer = (BYTE *) malloc(dataSize);
    memset(bmp.pDataBuffer, 0, dataSize);
    // 每次读一个字节
    fread(bmp.pDataBuffer, 1, dataSize, fp);
    fclose(fp);

    printf("bmp load success\n");
    return bmp;
}


void ImageIO::writeBmp(BMP bmp, const char *bmpOutPath)
{

    if (!bmp.pDataBuffer)
        return;

    LONG colorTableSize = 0;
    if (bmp.bitCount < 24)
    {
        int colorNum = pow(2, bmp.bitCount);
        colorTableSize = colorNum * sizeof(RGBQUAD);
    }

    bmp.lineByte = (bmp.width * bmp.bitCount / 8 + 3) / 4 * 4;
    FILE *fp = fopen(bmpOutPath, "wb");
    if (fp == 0) return;
    // <========================= 写入文件头 ==========================> //
    BITMAPFILEHEADER fileHead;
    fileHead.bfType = 0x4D42;//.bmp type
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + // 文件头大小
                      sizeof(BITMAPINFOHEADER) + // 信息头大小
                      colorTableSize + // 调色盘大小
                      bmp.lineByte * bmp.height; // 图片数据大小
    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;
    fileHead.bfOffBits = 54 + colorTableSize;
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
    // <========================= 写入信息头 ==========================> //
    BITMAPINFOHEADER infoHead;
    infoHead.biSize = 40;
    infoHead.biWidth = bmp.width;
    infoHead.biHeight = bmp.height;
    infoHead.biPlanes = 1;
    infoHead.biBitCount = bmp.bitCount;
    infoHead.biCompression = 0;
    infoHead.biSizeImage = bmp.lineByte * bmp.height;
    infoHead.biXPelsPerMeter = 0;
    infoHead.biYPelsPerMeter = 0;
    infoHead.biClrImportant = 0;
    infoHead.biClrUsed = 0;
    fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
    // <========================= 写入调色板 ==========================> //
    if (bmp.bitCount < 24)
    {
        int colorNum = pow(2, bmp.bitCount);
        fwrite(bmp.pRgbTable, sizeof(RGBQUAD), colorNum, fp);
    }
    // <========================= 写入图片数据 ==========================> //
    fwrite(bmp.pDataBuffer, bmp.height * bmp.lineByte, 1, fp);

    printf("bmp output success\n");
    fclose(fp);
}


void ImageIO::showBmpFileHead(BITMAPFILEHEADER *pBmpHead)
{
    printf("<================ Bitmap File Header:===============>\n");
    // 图片的类型 必须是BM 填0x4d42即十进制的19778
    printf("bfType:%d\n", pBmpHead->bfType);
    printf("bfSize: %d\n", pBmpHead->bfSize);
    printf("bfReserved1: %d\n", pBmpHead->bfReserved1);
    printf("bfReserved2: %d\n", pBmpHead->bfReserved2);
    printf("bfOffBits: %d\n", pBmpHead->bfOffBits);
}

void ImageIO::showBmpInfoHead(BITMAPINFOHEADER *pBmpInforHead)
{
    printf("<================ Bitmap Information Header:===============>\n");
    printf("biSize: %d\n", pBmpInforHead->biSize);
    printf("biWidth: %d\n", pBmpInforHead->biWidth);
    printf("biHeight: %d\n", pBmpInforHead->biHeight);
    printf("biPlanes: %d\n", pBmpInforHead->biPlanes);
    printf("biBitCount: %d\n", pBmpInforHead->biBitCount);
    printf("biCompression: %d\n", pBmpInforHead->biCompression);
    printf("biSizeImage: %d\n", pBmpInforHead->biSizeImage);
    printf("biXPelsPerMeter: %d\n", pBmpInforHead->biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n", pBmpInforHead->biYPelsPerMeter);
    printf("biClrUsed: %d\n", pBmpInforHead->biClrUsed);
    printf("biClrImportant: %d\n", pBmpInforHead->biClrImportant);
}
