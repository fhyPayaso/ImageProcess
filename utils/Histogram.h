/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_HISTOGRAM_H
#define IMAGEPROCESS_HISTOGRAM_H

#import "ImageIO.h"

class Histogram
{

private:

    LONG mGrayBuffer[256];

    BMP mGrayBmp;

public:

    Histogram(BMP bmp);


    /**
     * 构建灰度直方图
     * @return 直方图BMP
     */
    BMP buildHistogramBmp();


    /**
     * 构建带有阈值标记的灰度直方图
     * @return 直方图BMP
     */
    BMP buildHistogramWithThreshold(int threshold)
    {
        BMP bmp = mGrayBmp;
        // 初始化数据
        bmp.bitCount = 8;
        bmp.width = 256;
        bmp.height = 500;
        bmp.lineByte = (bmp.width * bmp.bitCount / 8 + 3) / 4 * 4;
        // 初始化Buffer
        LONG dataSize = bmp.height * bmp.lineByte;
        bmp.pDataBuffer = (BYTE *) malloc(dataSize);
        memset(bmp.pDataBuffer, 0, dataSize);
        // 开始绘制
        for (int i = 0; i < bmp.width; i++)
        {
            int curGrayCount = mGrayBuffer[i];


//        double garyNormal = (curGrayCount * 1.0) / (mGrayBmp.height * mGrayBmp.width);
//        int renderPixCount = garyNormal * 1000;

            int renderPixCount = curGrayCount / 15;

            for (int j = 0; j < bmp.height; j++)
            {
                if(i == threshold)
                {
                    bmp.pDataBuffer[bmp.lineByte * j + i] = 128;
                    continue;
                }

                if (j < renderPixCount)
                    bmp.pDataBuffer[bmp.lineByte * j + i] = 0;
                else
                    bmp.pDataBuffer[bmp.lineByte * j + i] = 255;
            }
        }

        return bmp;
    }


    /**
     * 直方图均衡化
     * @return
     */
    BMP equalizeBmp();

};


#endif //IMAGEPROCESS_HISTOGRAM_H
