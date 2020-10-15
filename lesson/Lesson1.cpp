/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#include "Lesson1.h"

using namespace std;

void Lesson1::split24BmpToRGB(const char *bmp_in, const char *bmp_out_r, const char *bmp_out_g, const char *bmp_out_b)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in);

    // 初始化三个输出图片
    LONG dataSize = bmp.height * bmp.lineByte;
    BYTE *pBmpRed = (BYTE *) malloc(dataSize);
    BYTE *pBmpGreen = (BYTE *) malloc(dataSize);
    BYTE *pBmpBlue = (BYTE *) malloc(dataSize);
    memset(pBmpRed, 0, dataSize);
    memset(pBmpGreen, 0, dataSize);
    memset(pBmpBlue, 0, dataSize);
    for (int i = 0; i < bmp.height; i++)
    {
        for (int j = 0; j < bmp.width; j++)
        {
            LONG startIndex = i * bmp.lineByte + j * 3;

            int curB = bmp.pDataBuffer[startIndex + 0];
            int curG = bmp.pDataBuffer[startIndex + 1];
            int curR = bmp.pDataBuffer[startIndex + 2];

            if(curG < 10 && curR < 10 )
            {
                pBmpBlue[startIndex + 0] = bmp.pDataBuffer[startIndex + 0];
            }

            if(curB < 10 && curR < 10 )
            {
                pBmpGreen[startIndex + 1] = bmp.pDataBuffer[startIndex + 1];
            }

            if(curB < 10 && curG < 10 )
            {
                pBmpRed[startIndex + 2] = bmp.pDataBuffer[startIndex + 2];
            }
        }
    }

    // 输出图片
    BMP bmpOut = bmp;
    bmpOut.bitCount = 24;
    bmpOut.pDataBuffer = pBmpRed;
    io.writeBmp(bmpOut, bmp_out_r);
    bmpOut.pDataBuffer = pBmpGreen;
    io.writeBmp(bmpOut, bmp_out_g);
    bmpOut.pDataBuffer = pBmpBlue;
    io.writeBmp(bmpOut, bmp_out_b);

    printf("Split 24Bmp To Rgb Bmp done !\n");
}

void Lesson1::cover24BmpToGray8(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    // 构建输出bmp
    BMP bmpOut = bmp;
    bmpOut.bitCount = 8;
    bmpOut.lineByte = (bmpOut.width * bmpOut.bitCount / 8 + 3) / 4 * 4;
    // =================== 构建调色板数据 =====================
    RGBQUAD *pOutRgbTable = (RGBQUAD *) malloc(256 * sizeof(RGBQUAD));
    memset(pOutRgbTable, 0, 256 * sizeof(RGBQUAD));
    for (int i = 0; i < 256; i++)
    {
        pOutRgbTable[i].rgbBlue = i;
        pOutRgbTable[i].rgbGreen = i;
        pOutRgbTable[i].rgbRed = i;
        pOutRgbTable[i].rgbReserved = 0;
    }
    bmpOut.pRgbTable = pOutRgbTable;
    // =================== 构建图片数据 ========================
    BYTE *pOutDataBuffer = (BYTE *) malloc(bmpOut.height * bmpOut.lineByte);
    memset(pOutDataBuffer, 0, bmpOut.height * bmpOut.lineByte);
    for (int i = 0; i < bmpOut.height; i++)
    {
        for (int j = 0; j < bmpOut.width; j++)
        {
            LONG startIndex = i * bmp.lineByte + j * 3;
            BYTE b = bmp.pDataBuffer[startIndex];
            BYTE g = bmp.pDataBuffer[startIndex + 1];
            BYTE r = bmp.pDataBuffer[startIndex + 2];
            BYTE gray = r * 0.299 + g * 0.587 + b * 0.114;
            pOutDataBuffer[i * bmpOut.lineByte + j] = gray;
        }
    }
    bmpOut.pDataBuffer = pOutDataBuffer;
    io.writeBmp(bmpOut, bmp_out_dir);

    printf("cover 24 Bmp to gray8 done!\n");
}

void Lesson1::reverseGray8(const char *bmp_in_dir, const char *bmp_out_dir)
{
    ImageIO io;
    BMP bmp = io.readBmp(bmp_in_dir);
    BMP bmpOut = bmp;
    for (int i = 0; i < bmp.height; i++)
    {
        for (int j = 0; j < bmp.width; j++)
        {
            LONG index = i * bmp.lineByte + j;
            bmpOut.pDataBuffer[index] = 255 - bmp.pDataBuffer[index];
        }
    }
    io.writeBmp(bmpOut, bmp_out_dir);
    printf("reverse gray8 done !\n");
}
