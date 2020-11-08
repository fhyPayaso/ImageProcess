/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_MOCKUTIL_H
#define IMAGEPROCESS_MOCKUTIL_H

#include "ImageIO.h"

const static char *OUT_BMP_LINE = "../bitmaps/hough_line.bmp";

class MockUtil
{

public:

    /**
     * 生成用于hough变换的图片
     * @param bmp_in_dir
     * @param bmp_out_dir
     */
    static void genLineBMP(const char *bmp_in_dir,
                           const char *bmp_out_dir = OUT_BMP_LINE)
    {
        ImageIO io;
        BMP bmp = io.readBmp(bmp_in_dir);
        bmp.pDataBuffer = (BYTE *) malloc(bmp.lineByte * bmp.height);

        // 横线

        for (int w = 0; w < bmp.width; ++w)
        {
            int h = 150;
            int widthDiff = 50;

            if (w > widthDiff && w < (bmp.width - widthDiff))
            {
                bmp.pDataBuffer[h * bmp.lineByte + w] = 255;
                bmp.pDataBuffer[(h + 1) * bmp.lineByte + w] = 255;
            }
            else
            {
                for (int k = 0; k < 2; ++k)
                {
                    int flag = k == 0 ? 1 : -1;
                    int curH = (h + k) + widthDiff * flag;
                    curH -= (widthDiff - w);
                    bmp.pDataBuffer[curH * bmp.lineByte + w] = 255;
                }
            }
        }


        io.writeBmp(bmp, bmp_out_dir);
        printf("mock data line bmp build done !\n");
    }


};


#endif //IMAGEPROCESS_MOCKUTIL_H
